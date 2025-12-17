//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <memory>
#include <System.NetEncoding.hpp>
#include <FireDAC.Stan.Error.hpp>
#include "MainFrm.h"
#include "UserParsForm.h"
#include "ItemsEditor.h"
#include "SelectUser.h"
#include "SelectUserWeaponsForm.h"
#include "DashboardFrm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

FILE* _log ;

bool openLog()
{
  if( _log != NULL )
     return true ;
  char buff[1024] ;
  GetModuleFileNameA( NULL, buff, sizeof( buff ) ) ;
  char* p = strrchr( buff, '.' ) ;
  ++p ;
  *p = 0 ;
  strcat( buff, "log" ) ;
  _log = fopen( buff, "a+t" ) ;
  return _log != NULL  ;
}

void put_log( bool error, const char* fmt, ... )
{
    if( MainForm == NULL )
       return ;
    va_list paramList;
    va_start(paramList, fmt);
    va_end(paramList);
    AnsiString s ;
    s.vprintf( fmt, paramList );
    MainForm->logStr( s, error ) ;
   if( _log )
   {
         fprintf( _log, "%s | %s | %s\n",
                  AnsiString( Now().DateTimeString() ).c_str(),
                  error ? "Error  ": "Message",
                  s.c_str() ) ;
   }
}
//---------------------------------------------------------------------------

FILE* _sqlLog  ;

bool openSQLLog()
{
  if( _sqlLog != NULL )
     return true ;
  char buff[1024] ;
  GetModuleFileNameA( NULL, buff, sizeof( buff ) ) ;
  char* p = strrchr( buff, '.' ) ;
  ++p ;
  *p = 0 ;
  strcat( buff, "sql.log" ) ;
  _sqlLog  = fopen( buff, "a+t" ) ;
  return _sqlLog  != NULL  ;
}

void logSQLs( TDataSet* DataSet, const char* sqlFunc )
{
   if( _sqlLog == NULL )
      return ;
  TFDQuery* q = dynamic_cast<TFDQuery*>(DataSet) ;
  if( q )
    fprintf( _sqlLog,
             "%s | %s. %s: \"%s\"\n",
              AnsiString( Now().DateTimeString() ).c_str(),
              AnsiString( q->Name ).c_str(),
              sqlFunc,
              AnsiString( q->SQL->Text).c_str() ) ;
}
//---------------------------------------------------------------------------

void closeAllLogs()
{
  if( _log )
  {
    fclose( _log ) ;
    _log = NULL ;
  }
  if( _sqlLog )
  {
    fclose( _sqlLog ) ;
    _sqlLog = NULL ;
  }
}
//---------------------------------------------------------------------------

bool checkDBLookupListBoxValue( TForm* owner, TDBLookupListBox* cb, const wchar_t* valName )
{
  if( cb->Enabled == false )
    return true ;
  try{
   int val = cb->KeyValue ;
  }

  catch( const Exception& e )
  {
    UnicodeString msg ;
    msg.printf( L"Select '%s' value!", valName );
    MessageDlg( msg,  mtError, TMsgDlgButtons() << mbOK,  0);
    owner->FocusControl( cb ) ;
    return false ;
  }
  return true ;
}

UnicodeString img2Base64( TImage* img )
{
    std::unique_ptr<TMemoryStream> ms(new TMemoryStream);
    img->Picture->Graphic->SaveToStream(ms.get());
    ms->Position = 0;
    UnicodeString b64 = TNetEncoding::Base64->EncodeBytesToString(
        (const unsigned char*)ms->Memory,
        ms->Size
    );
    return b64 ;
}
//---------------------------------------------------------------------------
bool loadDBBitmap(  TFDQuery* fdqryItems, TImage* ImagePreview,
                                        const wchar_t* field )
{
  std::unique_ptr<TMemoryStream> ms(new TMemoryStream);
//
  TBlobField *bf = (TBlobField*)fdqryItems->FieldByName( field );
  bf->SaveToStream(ms.get());
    ms->Position = 0;
    ImagePreview->Picture->LoadFromStream(ms.get());
  return true ;
}
void base64ToImg( TImage* dest, const UnicodeString& b64 )
{
    TBytes bytes = TNetEncoding::Base64->DecodeStringToBytes(b64);
    std::unique_ptr<TMemoryStream> ms(new TMemoryStream);
    ms->Write(&bytes[0], bytes.Length);
    ms->Position = 0;

    dest->Picture->Graphic->LoadFromStream(ms.get());
}
//---------------------------------------------------------------------------

// Функция коррекции sequence при старте программы
void FixSequenceForTable(
    TFDConnection* conn,
    const String& tableName,
    const String& idField)
{
    std::unique_ptr<TFDQuery> q(new TFDQuery(NULL));
    q->Connection = conn;

    q->SQL->Text =
        "SELECT pg_get_serial_sequence(:tbl, :fld) AS seq";
    q->ParamByName("tbl")->AsString = tableName;
    q->ParamByName("fld")->AsString = idField;
    q->Open();

    if (q->FieldByName("seq")->IsNull)
        return ;

    String seqName = q->FieldByName("seq")->AsString;
    q->Close();

    q->SQL->Text =
        "SELECT setval(:seq, (SELECT COALESCE(MAX(\"" + idField +
		"\"), 1) FROM " + tableName + "), true)";
    q->ParamByName("seq")->AsString = seqName;
    q->Open();
}

//------------------------------------------------------------------------

class TCDBGrid : public TDBGrid
{
  public:
    __property FixedCols ;
};

__fastcall TMainForm::TMainForm(TComponent* Owner)
  : TForm(Owner)
{
// ((TCDBGrid*)dbgrd1)->FixedCols = 2 ;
// dsUsers->AfterScroll = NULL ;
  func="" ;
}

__fastcall TMainForm::~TMainForm()
{
 closeAllLogs() ;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::logStr( const UnicodeString& s, bool error )
{
 TDateTime d = Now() ;

 TListItem* item = lv1->Items->Insert( 0 ) ;
 item->Caption = d.TimeString() ;
 item->SubItems->Add( s ) ;
 item->SubItems->Add( error ? "Error": "Message" ) ;
 if( error )
    item->ImageIndex = 0 ;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::rg1Click(TObject *Sender)
{
  dbgrd3->Enabled = actWeapons->Checked  ;
  fdqryUsersAfterScroll( NULL ) ;
  return ;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::fdqryUsersAfterScroll(TDataSet *DataSet)
{
    if( fdqryUsers->Active)
    {
        // 1. Получаем ключевое значение из главной таблицы (например, ID_Category)
        // Используем AsVariant, чтобы безопасно работать с разными типами
        int val = fdqryUsers->FieldByName(L"ID")->AsInteger ;
        if( val == 0 )
           return  ;

        // 2. Настраиваем и выполняем запрос для детального грида (DBGrid2)
        // ---------------------------------------------------------------

        // Сначала закрываем детальный запрос
        if (fdqryUserItems->Active)
            fdqryUserItems->Close();

        // Устанавливаем SQL-запрос с параметром для связи
        // (Используем AnsiString или UnicodeString в зависимости от версии C++ Builder)
        UnicodeString query =
             L"SELECT i.\"ID\", w.\"Weapon\" AS \"WeaponDescription\", it.\"Description\" AS \"ItemDescription\","
             " i.\"Price\", i.\"Nametag\",s.\"Category\" AS \"SpecialDescription\", \"OwnerID\", \"Type\", p.\"Preview\" AS  \"Preview\""
                  " FROM \"Items\" i "
              " LEFT JOIN \"ItemTypes\" it  ON i.\"Type\" = it.\"TypeID\""
              " LEFT JOIN \"WeaponIDToWeapon\" w  ON i.\"Weapon\" = w.\"WeaponID\""
              " LEFT JOIN \"SpecialToCategory\" s ON i.\"Special\" = s.\"SpecialID\""
              " LEFT JOIN \"ItemPreviews\" p ON i.\"ID\" = p.\"ItemID\""
              " WHERE i.\"OwnerID\" = :OwnerID" ;
        if( actWeapons->Checked  > 0  )
            query += " AND i.\"Type\" = 1;" ;
        else
             query += " ;" ;
        fdqryUserItems->SQL->Text = query  ;
        fdqryUserItems->ParamByName("OwnerID")->AsInteger =  val ;
        fdqryUserItems->Open();
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::chk1Click(TObject *Sender)
{
  fdqryUsersAfterScroll( fdqryUserItems ) ;
}
//---------------------------------------------------------------------------





void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    chkSqlLogClick( NULL );
    chkLogClick( NULL ) ;
    UnicodeString server, database, user, passw ;

    char fileName[260] ;
    GetModuleFileNameA( NULL, fileName, sizeof( fileName ) ) ;
    char* p = strrchr( fileName, '.' ) ;
    *p = 0 ;
    strcat( fileName, ".ini" ) ;

    char buff[260] ;
    GetPrivateProfileStringA( "", "server", "127.0.0.1", buff, sizeof( buff ), fileName );
    server = UnicodeString( buff ) ;

    GetPrivateProfileStringA( "", "database", "WeaponDB", buff, sizeof( buff ), fileName );
    database = UnicodeString( buff ) ;

    GetPrivateProfileStringA( "", "user", "postgres", buff, sizeof( buff ), fileName );
    user = UnicodeString( buff ) ;

    GetPrivateProfileStringA( "", "passw", "7567", buff, sizeof( buff ), fileName );
    passw = UnicodeString( buff );

    con1->Params->Values[ "Server" ] = server ;
    con1->Params->Values[ "Database" ] = database ;
    con1->Params->Values[ "User_Name" ] = user ;
    con1->Params->Values[ "Password" ] = passw ;

    put_log( false, "Start program" ) ;
    con1->Connected = true;
 try
    {
        FixSequenceForTable( con1, "\"Items\"", "ID" );
        FixSequenceForTable( con1, "\"Users\"", "ID" );
		FixSequenceForTable( con1, "\"Transactions\"", "TransactionID" );

        // и любые другие таблицы…
    }
    catch (Exception &e)
    {
		ShowMessage("Error correcting sequence:\n" + e.Message);
    }
    // Настройка FDQuery
    fdqryUsers->Connection  = con1;
    fdqryUsers->Transaction = fdtrans1;
    usersSQL = "SELECT u.\"ID\", u.\"Username\", u.\"Balance\", u.\"DateJoined\", r.\"RestDescription\" as \"Restriction\","
                   " \"Archive\", \"Version\" "
              "FROM \"Users\" u "
                   " LEFT JOIN \"RestrictionType\" r  ON u.\"RestrictionType\" = r.\"ID\" " ;

    fdqryUsers->SQL->Text = usersSQL + " where \"Archive\" = FALSE" ;
    fdqryUsers->Open();

    // Привязка к гриду
    dsUsers->DataSet = fdqryUsers;
    dbgrd1->DataSource   = dsUsers;
    fdpdtsqlUsers->InsertSQL->Text =
        "INSERT INTO \"Users\" (\"Username\", \"Balance\", \"Version\") VALUES (:Username,:Balance, 0)";

    fdpdtsqlUsers->DeleteSQL->Text =
        "DELETE FROM \"Users\" WHERE \"ID\"=:OLD_ID AND \"Version\"=:OLD_Version";

   fdqryUsers->UpdateObject = fdpdtsqlUsers;

   itemsSQL = L"SELECT i.\"ID\", u.\"Username\" AS \"Owner\", i.\"Price\", i.\"Nametag\", it.\"Description\" AS \"ItemDescription\","
   " w.\"Weapon\" AS \"WeaponDescription\", s.\"Category\" AS \"SpecialDescription\", \"OwnerID\", p.\"Preview\" AS  \"Preview\","
   " \"Type\"  FROM \"Items\" i"
     " LEFT JOIN \"Users\" u ON i.\"OwnerID\" = u.\"ID\""
     " LEFT JOIN \"ItemTypes\" it ON i.\"Type\" = it.\"TypeID\""
     " LEFT JOIN \"WeaponIDToWeapon\" w  ON i.\"Weapon\" = w.\"WeaponID\""
     " LEFT JOIN \"SpecialToCategory\" s ON i.\"Special\" = s.\"SpecialID\""
     " LEFT JOIN \"ItemPreviews\" p ON i.\"ID\" = p.\"ItemID\"" ;
   fdqryItems->SQL->Text = itemsSQL ;


   fdqryItems->Open() ;
//   fdpdtsqlItems->DeleteSQL->Text = "DELETE FROM \"Items\" WHERE \"ID\"=:ID";

   transactionSQL = L"SELECT "
              "t.\"TransactionID\", t.\"TransactionID\", t.\"SellerID\",  t.\"BuyerID\", t.\"ItemID\", "
              "s.\"Username\" AS \"SellerName\", "
              "b.\"Username\" AS \"BuyerName\", "
              "i.\"Nametag\" AS \"ItemNametag\", "
              "it.\"Description\" AS \"ItemType\", "
              "t.\"Price\", "
              "t.\"Date\", "
              "t.\"Archive\", "
              "t.\"Canceled\" "

          "FROM \"Transactions\" t "
          "LEFT JOIN \"Users\" s ON t.\"SellerID\" = s.\"ID\" "
          "LEFT JOIN \"Users\" b ON t.\"BuyerID\"  = b.\"ID\" "
          "LEFT JOIN \"Items\" i ON t.\"ItemID\"   = i.\"ID\" "
          "LEFT JOIN \"ItemTypes\" it ON i.\"Type\" = it.\"TypeID\"" ;
  fdqryTransaction->SQL->Text = transactionSQL ;
  fdqryTransaction->Open() ;

  fdpdtsqlItems->DeleteSQL->Text = "DELETE FROM \"Items\" WHERE \"ID\"=:ID";
  fdqryRestriction->SQL->Text = "SELECT \"ID\", \"RestDescription\" FROM \"RestrictionType\";" ;
  fdqrySpecial->SQL->Text = "SELECT \"SpecialID\", \"Category\" FROM \"SpecialToCategory\";" ;
  fdqryItemTypes->SQL->Text = "SELECT \"TypeID\", \"Description\" FROM \"ItemTypes\";" ;
  fdqryWeaponID->SQL->Text = "SELECT \"WeaponID\", \"Weapon\" FROM \"WeaponIDToWeapon\";";

  fdqrySpecial->Open() ;
  fdqryRestriction->Open() ;

  fdqryItemTypes->Open() ;
  fdqryWeaponID->Open()  ;
  rg1Click( NULL ) ;
  pgc1Change( NULL ) ;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::dbnvgr1Click(TObject *Sender, TNavigateBtn Button )
{
 if(  Button == nbInsert )
   actAddUserExecute( NULL ) ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actAddUserExecute(TObject *Sender)
{
  EditUserForm->lbledt1->Text = L"";
  EditUserForm->ud1->Position = 0 ;
  if(EditUserForm->ShowModal() != mrOk)
        return;

    try {
        fdqryUsers->Insert();
        fdqryUsers->FieldByName("Username")->AsString = EditUserForm->lbledt1->Text.Trim();
        fdqryUsers->FieldByName("Balance")->AsInteger  = EditUserForm->ud1->Position;
        fdqryUsers->Post();  // FireDAC сам делает INSERT

        if(!fdtrans1->Active)
            fdtrans1->StartTransaction();
        fdtrans1->Commit();
        put_log( false, "Added user '%s'", AnsiString(EditUserForm->lbledt1->Text).c_str() ) ;
        fdqryUsers->Close();
        fdqryUsers->Open();
    }
    catch(Exception &e)
    {
        if(fdtrans1->Active)
            fdtrans1->Rollback();
		put_log( true, "Error adding User '%s': %s ",
						AnsiString( EditUserForm->lbledt1->Text ).c_str(),
                        AnsiString( e.Message ).c_str()  ) ;
    }
 }
//---------------------------------------------------------------------------


void __fastcall TMainForm::actEditUserExecute(TObject *Sender)
{
  UnicodeString s = fdqryUsers->FieldByName(L"Username")->AsString  ;
  if( s.Length() == 0 )
     return ;
  int bal = fdqryUsers->FieldByName(L"Balance")->AsInteger ;
  EditUserForm->lbledt1->Text = s ;
  EditUserForm->ud1->Position = bal ;
  if( EditUserForm->ShowModal() != mrOk)
        return;
   fdpdtsqlUsers->ModifySQL->Text =
        L"UPDATE \"Users\" SET \"Username\"=:Username,\"Balance\"=:Balance, \"Version\" = \"Version\"+ 1"
                 " WHERE \"ID\" = :OLD_ID AND \"Version\" = :OLD_Version " ;
/*
 "Version"           = "Version" + 1
WHERE

*/
    try {
         if(!fdtrans1->Active)
             fdtrans1->StartTransaction();
         fdqryUsers->Edit();
         fdqryUsers->FieldByName("Username")->AsString = EditUserForm->lbledt1->Text.Trim();
         fdqryUsers->FieldByName("Balance")->AsInteger  = EditUserForm->ud1->Position;
         fdqryUsers->Post();  // FireDAC сам делает INSERT
         fdtrans1->Commit();
         put_log( false, "User's parameters changed", AnsiString( s ).c_str() ) ;
//         fdqryUsers->Close();
//         fdqryUsers->Open();
    }
    catch(Exception &e) {
        if(fdtrans1->Active)
            fdtrans1->Rollback();
		put_log( true, "Error changing User's '%s' parameters: %s ",
                        AnsiString( s ).c_str(),
                        AnsiString( e.Message ).c_str()  ) ;

    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actDeleteUserExecute(TObject *Sender)
{
  UnicodeString s = fdqryUsers->FieldByName(L"Username")->AsString  ;
  if( s.Length() == 0 )
     return ;
  int id = fdqryUsers->FieldByName(L"ID")->AsInteger ;

  UnicodeString msg ;
  msg.printf( L"Delete all user's '%ls' data?", s.c_str() ) ;
  int rc = MessageDlg( msg,  mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,  0);
  if( rc != mrYes )
     return ;
  try {
      if(!fdtrans1->Active)
             fdtrans1->StartTransaction();
      fdqryUsers->Delete() ;
      fdtrans1->Commit();
	  put_log( false, "User '%s', id:%d deleted ", AnsiString( s ).c_str(), id ) ;
  }
  catch(Exception &e) {
    if(fdtrans1->Active)
            fdtrans1->Rollback();
		put_log( true, "Error deleting User '%s', id:%d: %s ",
                        AnsiString( s ).c_str(),
                        id,
                        AnsiString( e.Message ).c_str() ) ;

  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actSoftDeleteUserExecute(TObject *Sender)
{
    archiveUser( true ) ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actRestoreUserExecute(TObject *Sender)
{
    archiveUser( false ) ;
    return ;
}
//---------------------------------------------------------------------------




void __fastcall TMainForm::actAddItemExecute(TObject *Sender)
{
  ItemEditForm->Clear() ;
  if( ItemEditForm->ShowModal() != mrOk )
       return ;
   std::unique_ptr<TMemoryStream> ms(new TMemoryStream);
   if(  ItemEditForm->img1->Picture->Graphic != NULL &&
        ItemEditForm->img1->Picture->Graphic->Empty == false )
    {
        ItemEditForm->img1->Picture->SaveToStream( ms.get() );
        ms->Position = 0;
   }
   int size = ms->Size ;
 /*
  Изначально планировалось добавлять все одним запросом:

   fdqryInsert->SQL->Text =
   L"WITH new_item AS ( INSERT INTO \"Items\" (\"OwnerID\",\"Nametag\",\"Price\",\"Type\",\"Weapon\",\"Special\" )"
    " VALUES (:Owner, :Nametag, :Price, :pType, :WeaponID, :Special )"
    " RETURNING \"ID\" )"
    "INSERT INTO \"ItemPreviews\" (\"ItemID\",\"Preview\") "
    "SELECT \"ID\", :Preview FROM new_item;" ;

  Однако FireDAC на любые модификации данного запроса, вплоть до 16-ричной подстановки данных вместо ":Preview"
  возращал ошибку: "[FireDAC][Phys][PG][libpq] ERROR: syntax error at or near "INSERT""
  Поэтому было принято добавлять данные 2мя запросами, но в рамках одной транзакции
*/
    UnicodeString s = ItemEditForm->lbledt3->Text.Trim() ;
    try
    {
       con1->StartTransaction();
       int NewItemID = 0;

        // 1. Вставка в Items и получение ID
        int type = ItemEditForm->dblklstItemDescription->KeyValue ;
        if( type == WEAPON_TYPE )
        {
          fdqryInsert->SQL->Text =
              L"INSERT INTO \"Items\" (\"OwnerID\",\"Nametag\",\"Price\",\"Type\",\"Weapon\",\"Special\" )"
               "VALUES (:Owner, :Nametag, :Price, :pType, :WeaponID, :Special )"
               " RETURNING \"ID\"";
        }
        else
          fdqryInsert->SQL->Text =
            L"INSERT INTO \"Items\" (\"OwnerID\",\"Nametag\",\"Price\",\"Type\" )"
             " VALUES (:Owner, :Nametag, :Price, :pType )"
             " RETURNING \"ID\"";

        fdqryInsert->Close();
        fdqryInsert->ParamByName("Owner")->AsInteger = 1 ;
        fdqryInsert->ParamByName("Nametag")->AsString = s ;
        fdqryInsert->ParamByName("Price")->AsInteger = ItemEditForm->ud1->Position ;

        fdqryInsert->ParamByName("pType")->AsInteger = type;

        if( type == WEAPON_TYPE )
        {
           int wID = ItemEditForm->dblklst1->KeyValue ;
           int sps = ItemEditForm->dblklstSpecialDescription->KeyValue; ;
           fdqryInsert->ParamByName("WeaponID")->AsInteger = wID ;
           fdqryInsert->ParamByName("Special")->AsInteger = sps ;
        }
        fdqryInsert->Open();
        if (!fdqryInsert->Eof)
        {
          NewItemID = fdqryInsert->FieldByName("ID")->AsInteger;
        }
        fdqryInsert->Close();
        // 2. Добавляем bitmap
		if( NewItemID > 0)
        {
            fdqryPreviews->SQL->Text =
                "INSERT INTO \"ItemPreviews\" (\"ItemID\", \"Preview\")"
                "VALUES (:ItemID, :PreviewData)";

            fdqryPreviews->Close();
            fdqryPreviews->ParamByName("ItemID")->AsInteger = NewItemID;
            auto p = fdqryPreviews->ParamByName("PreviewData");
            p->DataType = ftBlob;
            p->LoadFromStream(ms.get(), ftBlob);

            fdqryPreviews->ExecSQL();
        }
        con1->Commit();
        put_log( false, "Added item '%s'", AnsiString( s ).c_str() ) ;
    }
    catch( const Exception &e)
    {
        con1->Rollback(); // Откат при любой ошибке
		put_log( true, "Error adding Item '%s': %s ",
                        AnsiString( s ).c_str(),
                        AnsiString( e.Message ).c_str() ) ;
    }
   fdqryItems->Close();
   fdqryItems->Open();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::actDeleteItemExecute(TObject *Sender)
{
    int val = fdqryItems->FieldByName(L"OwnerID")->AsInteger ;
    if( val == 0 )
           return  ;

  UnicodeString s = fdqryItems->FieldByName(L"Owner")->AsString  ;
  if( s.Length() == 0 )
     return ;
  UnicodeString name = fdqryItems->FieldByName(L"Nametag")->AsString  ;

   if( val != 1 )
   {
	UnicodeString msg ;
	msg.printf( L"Item '%ls' is already owned by user '%ls' and cannot be deleted!",
                name.c_str(),
                s.c_str() ) ;
    MessageDlg( msg,  mtError, TMsgDlgButtons() << mbOK,  0);
    return ;

   }
  UnicodeString msg ;
  msg.printf( L"Delete new item '%ls'?", name.c_str() ) ;
  int rc = MessageDlg( msg,  mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,  0);
  if( rc != mrYes )
	 return ;

  try{
      if(!fdtrans1->Active)
              fdtrans1->StartTransaction();
      fdqryItems->Delete() ;
      fdtrans1->Commit() ;
      put_log( false, "Deleted item '%s'", AnsiString( name ).c_str() ) ;
   }
   catch( const Exception &e)
   {
       if(fdtrans1->Active)
            fdtrans1->Rollback();
		put_log( true, "Error deleting Item '%s': %s ",
                        AnsiString( name ).c_str(),
                        AnsiString( e.Message ).c_str() ) ;
   }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::actSellToExecute(TObject *Sender)
{
  UnicodeString un, in ;
  in = fdqryItems->FieldByName(L"Nametag")->AsString ;

  int price = fdqryItems->FieldByName(L"Price")->AsInteger ;
  SelectUserForm->ud1->Position = price ;
  if( SelectUserForm->ShowModal() != mrOk )
      return ;
  int Type = fdqryItems->FieldByName(L"Type")->AsInteger ;
  if( Type != WEAPON_TYPE )
    ; // Надо вставить проверку на то, что айтем уже на оружии, и ругнуться

  int itemID = fdqryItems->FieldByName(L"ID")->AsInteger ;
  int sellerID = fdqryItems->FieldByName(L"OwnerID")->AsInteger ;
  if( sellerID == 0 )
           return  ;
  int buyerID = SelectUserForm->dblklst1->KeyValue ;
  if( buyerID == sellerID )
  {
	 MessageDlg( L"Cannot sell items to self!",  mtError, TMsgDlgButtons() << mbOK,  0);
     return ;
  }
  price = SelectUserForm->ud1->Position  ;
  fdqryInsert->SQL->Text = "SELECT \"Username\", \"Balance\", \"Archive\" from \"Users\" where \"ID\" = :ID" ;
  fdqryInsert->ParamByName("ID")->AsInteger = buyerID ;
  try{
//    fdqryInsert->Prepare() ;
    fdqryInsert->Open() ;
    UnicodeString msg ;

    un = fdqryInsert->FieldByName( "Username" )->AsString;

    int bal = fdqryInsert->FieldByName( "Balance" )->AsInteger ;

    if( fdqryInsert->FieldByName( "Archive" )->AsBoolean  == true )
      msg.printf( L"User '%ls' is inactive!",
                  un.c_str() ) ;
    else
      if( bal  < price )
	  msg.printf( L"User '%ls' doesn't have enough balance (%d)!",
                  un.c_str(), bal ) ;
    if( msg.Length() > 0 )
    {
      MessageDlg( msg,  mtError, TMsgDlgButtons() << mbOK,  0);
      return ;
    }

    fdtrans1->StartTransaction();
    fdqryInsert->SQL->Text =
        "INSERT INTO \"Transactions\" (\"SellerID\", \"BuyerID\", \"ItemID\", \"Price\", \"Date\") "
        "VALUES (:seller, :buyer, :item, :price, :a_date)" ;
    fdqryInsert->ParamByName("seller")->AsInteger = sellerID ;
    fdqryInsert->ParamByName("buyer")->AsInteger = buyerID ;
    fdqryInsert->ParamByName("item")->AsInteger = itemID ;
    fdqryInsert->ParamByName("price")->AsInteger = price ;
    fdqryInsert->ParamByName("a_date")->AsDateTime  = Now() ;

    fdqryInsert->ExecSQL();
    fdtrans1->Commit();
	put_log( false, "Item '%s' sold to user '%s' by price %d",
             AnsiString( in ).c_str(),
             AnsiString( un ).c_str(),
             price ) ;
  }
  catch(Exception &e) {
       if(fdtrans1->Active)
            fdtrans1->Rollback();
		put_log( true, "Error selling Item '%s': %s ",
                        AnsiString( in ).c_str(),
                        AnsiString( e.Message ).c_str() ) ;
     return ;
  }
  fdqryItems->Close() ;
  fdqryItems->Open() ;
  fdqryTransaction->Close() ;
  fdqryTransaction->Open() ;
  fdqryUsers->Close() ;
  fdqryUsers->Open() ;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::actDeleteTransactionExecute(TObject *Sender)
{
 int id = fdqryTransaction->FieldByName(L"TransactionID")->AsInteger ;
 if( id == 0 )
    return ;

 bool cancel = fdqryTransaction->FieldByName(L"Canceled")->AsBoolean ;
 if( cancel == false )
 {
	MessageDlg("Only cancelled transactions can be deleted!",  mtError, TMsgDlgButtons() << mbOK, 0);
    return ;
 }
 try {
     fdqryLock->Close();

     fdqryLock->FetchOptions->Unidirectional = true;
     fdqryLock->FetchOptions->Mode = fmAll;
     fdqryLock->FetchOptions->CursorKind = ckForwardOnly;
     fdqryLock->ResourceOptions->CmdExecMode = amBlocking;
//////////////////////////////////////////////////////////////////////////
     fdqryLock->SQL->Text =
         "SELECT 1 FROM \"Transactions\" "
         "WHERE \"TransactionID\" = :ID FOR UPDATE NOWAIT";
     fdqryLock->ParamByName("ID")->AsInteger = id;
     fdqryLock->Open();  // Блокировка строки

     fdqryInsert->SQL->Text = "DELETE FROM \"Transactions\" WHERE \"TransactionID\"=:ID" ;
     fdqryInsert->ParamByName("id")->AsInteger = id ;
     fdtrans1->StartTransaction();
     fdqryInsert->ExecSQL();
     fdtrans1->Commit();
	 put_log( false, "Transaction id: %d deleted",id ) ;
  }
  catch(Exception &e)
  {
        fdtrans1->Rollback();
		put_log( true, "Error deleting Transaction %d: %s ",
                        id,
                        AnsiString( e.Message ).c_str() ) ;
     return ;
  }
 fdqryTransaction->Close() ;
 fdqryTransaction->Open() ;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::actStickUpdate(TObject *Sender)
{
  actStick->Enabled = actWeapons->Checked == 0 ;
}
//---------------------------------------------------------------------------

bool TMainForm::isItemAlreadySticked( int itemID )
{
  //count( SubjectKeyID ) as PCOUNT FROM %ls WHERE
  int cnt = 0 ;
  fdqryInsert->SQL->Text = "SELECT COUNT (\"ItemID\") AS PCount FROM \"StickersOnWeapon\" WHERE \"StickerID\" = :id" ;
  fdqryInsert->ParamByName("id")->AsInteger = itemID ;
  try{
     fdqryInsert->Open() ;
     cnt = fdqryInsert->FieldByName( "PCount" )->AsInteger ;
  }
  catch(Exception &e)
  {
      return false ;
  }
  return cnt > 0 ;
}


void __fastcall TMainForm::actStickExecute(TObject *Sender)
{
//
  int id = fdqryUserItems->FieldByName(L"ID")->AsInteger ;
  int type = fdqryUserItems->FieldByName(L"Type")->AsInteger ;
  if( type == WEAPON_TYPE )
     return ;
  UnicodeString name = fdqryUserItems->FieldByName(L"Nametag")->AsString ;
  if( isItemAlreadySticked( id ) == true )
  {
     UnicodeString msg;
     msg.printf( L"Item '%ls' is already sticked!", name.c_str() ) ;
     MessageDlg( msg,  mtError, TMsgDlgButtons() << mbOK,  0);
     return ;
  }
  int userID = fdqryUsers->FieldByName(L"ID")->AsInteger ;
  int targetID = selectWeapons( userID, WEAPON_TYPE ) ;
  if( targetID == 0 )
     return ;

   fdqryInsert->SQL->Text =
        "INSERT INTO \"StickersOnWeapon\" (\"ItemID\", \"StickerID\", \"PositionX\", \"PositionY\") "
        "VALUES (:weaponID,:itemID, 0.0, 0.0 );" ;
   fdqryInsert->ParamByName("weaponID")->AsInteger = targetID  ;
   fdqryInsert->ParamByName("itemID")->AsInteger = id ;
  try{
       fdtrans1->StartTransaction();
       fdqryInsert->ExecSQL();
       fdtrans1->Commit();
	   put_log( false, "Item '%s' was applied to weapon, id:%d",
               AnsiString( name ).c_str(),
               targetID ) ;
    }
  catch(Exception &e) {
	   put_log( false, "Error applying Item '%s' error: %s ",
                        AnsiString( name ).c_str(),
                        AnsiString( e.Message ).c_str() ) ;
      fdtrans1->Rollback();
     return ;
  }
/*
    "ItemID" integer REFERENCES "Items" ("ID"),
    "StickerID" integer NOT NULL,
    "Preview" text,
    "PositionX" double precision NOT NULL,
    "PositionY" double precision NOT NULL,
*/
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::fdqryUserItemsAfterScroll(TDataSet *DataSet)
{
//  return ;
//   UnicodeString s = fdqryUserItems->FieldByName(L"Preview")->AsString ;
//   if( s.Length() != 0 )
//      base64ToImg( img1, s ) ;
//
   if( actWeapons->Checked  == false  )
   {
       fdqryUserStikers->Close() ;
       return ;
   }
   Variant MasterKey = fdqryUserItems->FieldByName(L"ID")->Value ;
   if( fdqryUserStikers->Active )
       fdqryUserStikers->Close();
   fdqryUserStikers->SQL->Clear();
   UnicodeString query = L"SELECT i.\"ID\",  i.\"Nametag\", i.\"Price\", it.\"Description\" AS \"ItemDescription\",  s.\"Category\" AS \"SpecialDescription\" "
                                "FROM \"Items\" i "
                                "LEFT JOIN \"ItemTypes\" it "
                                "ON i.\"Type\" = it.\"TypeID\" "
                                "LEFT JOIN \"SpecialToCategory\" s "
                                "ON i.\"Special\" = s.\"SpecialID\" "
                                "WHERE i.\"ID\" in ( SELECT \"StickerID\" sw FROM \"StickersOnWeapon\" sw WHERE sw.\"ItemID\" = :WID ) ;" ;

    fdqryUserStikers->SQL->Add( query ) ;
    fdqryUserStikers->ParamByName("WID")->Value =  MasterKey ;
    fdqryUserStikers->Open();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actEditItemExecute(TObject *Sender)
{
   int id = fdqryItems->FieldByName(L"ID")->AsInteger ;
   if( id == 0 )
      return ;
  ItemEditForm->setEditFieRow( fdqryItems ) ;
  if( ItemEditForm->ShowModal() != mrOk )
      return ;

   std::unique_ptr<TMemoryStream> ms(new TMemoryStream);
   ItemEditForm->img1->Picture->SaveToStream( ms.get() );
   int size = ms->Size ;

   UnicodeString nm = ItemEditForm->lbledt3->Text.Trim() ;
   int newPrice =  ItemEditForm->ud1->Position ;
   con1->StartTransaction();
   try
   {
        // -----------------------------------------------------
        // Та же проблема, что и в actAddItemExecute, поэтому изменяем
        // двумя запросами в рамках одной транзакции.
        // -----------------------------------------------------
        fdqryInsert->SQL->Text ="UPDATE \"Items\" SET \"Price\" = :NewPrice, \"Nametag\" = :NewNametag "
                                "WHERE \"ID\" = :ItemID";
        fdqryInsert->Close();


        fdqryInsert->ParamByName("NewPrice")->AsInteger = newPrice;
        fdqryInsert->ParamByName("NewNametag")->AsString = nm;
        fdqryInsert->ParamByName("ItemID")->AsInteger = id;
        fdqryInsert->ExecSQL();
        fdqryPreviews->SQL->Text  ="UPDATE \"ItemPreviews\" SET  \"Preview\" = :NewPreviewData "
            "WHERE \"ItemID\" = :ItemID";
        fdqryPreviews->Close();
        auto p = fdqryPreviews->ParamByName("NewPreviewData");
        p->DataType = ftBlob;
        p->LoadFromStream(ms.get(), ftBlob);
        fdqryPreviews->ParamByName("ItemID")->AsInteger = id;

        fdqryPreviews->ExecSQL();
        con1->Commit();
		put_log( false, "Item '%s', id %d, changed succesfully",
                AnsiString( nm ).c_str(), id) ;
    }
    catch(Exception &e)
    {
        con1->Rollback();
		put_log( true, "Error changing Item '%s', id %d: %s",
                        AnsiString( nm ).c_str(),
                        id,
                        AnsiString( e.Message ).c_str()  ) ;
    }
/*   UnicodeString u1(   L"UPDATE \"Items\" SET \"Nametag\" = :Nametag, \"Price\" =:Price" ) ;
   if( b64.Length() )
      u1 += L", \"Preview\" =:Preview" ;
   u1 += UnicodeString( L" WHERE \"ID\"=" ) + id + L";" ;
   UnicodeString nm = ItemEditForm->lbledt3->Text.Trim() ;

   fdqryInsert->SQL->Text = u1 ;
   try {

       fdqryInsert->ParamByName("Nametag")->AsString = nm;
       fdqryInsert->ParamByName("Price")->AsInteger = ItemEditForm->ud1->Position ;
       if( b64.Length() )
          fdqryInsert->ParamByName("Preview")->AsString = b64;
       fdtrans1->StartTransaction();
       fdqryInsert->ExecSQL();
       fdtrans1->Commit();
        put_log( false, "Item '%s' changed succesfull",
                AnsiString( nm ).c_str()) ;
     }
      catch(Exception &e) {
        put_log( false, "Item '%s' changing error: %s",
                 AnsiString( nm ).c_str(),
                AnsiString( e.Message ).c_str()  ) ;
         if(fdtrans1->Active)
             fdtrans1->Rollback();
    }*/
    fdqryItems->Close();
    fdqryItems->Open();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::fdqryInsertBeforeOpen(TDataSet *DataSet)
{
//
   logSQLs( DataSet, "Open" ) ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::fdqryInsertBeforeExecute( TFDDataSet *DataSet )
{
   logSQLs( DataSet, "Exec" ) ;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::chkLogClick(TObject *Sender)
{
  if( chkLog->Checked )
    openLog() ;
  else
      if( _log )
      {
         fclose( _log ) ;
         _log = NULL ;
      }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::chkSqlLogClick(TObject *Sender)
{
  if( chkSqlLog->Checked )
    openSQLLog() ;
  else
      if( _sqlLog  )
      {
         fclose( _sqlLog  ) ;
         _sqlLog  = NULL ;
      }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::pgc1Change(TObject *Sender)
{
  if( pgc1->ActivePage == ts1 )
  {
    dbimgPreview->DataSource = dsUserItems ;
    dbimgPreview->Visible = true;
  }
  else if( pgc1->ActivePage == ts2 )
       {
         dbimgPreview->DataSource = dsItems ;
         dbimgPreview->Visible = true;
      }
      else
       dbimgPreview->Visible = false ;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::actCanceTransactionExecute(TObject *Sender)
{
 int id = fdqryTransaction->FieldByName(L"TransactionID")->AsInteger ;
 if( id == 0 )
    return ;
 bool cancel = fdqryTransaction->FieldByName(L"Cancelled")->AsBoolean ;
 if( cancel == true  )
    return ;

 try {
     fdqryLock->Close();
//////////////////////////////////////////////////////////////////////////
    fdqryLock->FetchOptions->Unidirectional = true;
    fdqryLock->FetchOptions->Mode = fmAll;
    fdqryLock->FetchOptions->CursorKind = ckForwardOnly;
    fdqryLock->ResourceOptions->CmdExecMode = amBlocking;
//////////////////////////////////////////////////////////////////////////

     fdqryLock->SQL->Text =
        "SELECT 1 FROM \"Transactions\" "
        "WHERE \"TransactionID\" = :ID FOR UPDATE NOWAIT";
    fdqryLock->ParamByName("ID")->AsInteger = id;
    fdqryLock->Open();  // Блокировка строки

    fdqryInsert->SQL->Text = "UPDATE \"Transactions\" SET \"Canceled\" = TRUE WHERE \"TransactionID\" = :id;" ;
    fdqryInsert->ParamByName("id")->AsInteger = id ;
    fdtrans1->StartTransaction();
    fdqryInsert->ExecSQL();
    fdtrans1->Commit();
	put_log( false, "Transaction %d was cancelled",id ) ;
  }
  catch(Exception &e) {
       if(fdtrans1->Active)
            fdtrans1->Rollback();
		put_log( true, "Error cancelling Transaction %d: %s ",
                        id,
                        AnsiString( e.Message ).c_str() ) ;
     return ;
  }
 fdqryTransaction->Close() ;
 fdqryTransaction->Open() ;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::chkAddeFromClick(TObject *Sender)
{
 dtAddedFrom->Enabled = chkAddeFrom->Checked ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::chkAddeToClick(TObject *Sender)
{
 dtAddedTo->Enabled = chkAddeTo->Checked ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::chkPriceClick(TObject *Sender)
{
 grp3->Enabled = chkPrice->Checked ;
}
//---------------------------------------------------------------------------


void TMainForm::getTypeFilter( TStringList* dest )
{
 if( chkWP->Checked )
  dest->Add( L"1" ) ;
 if( chkStk->Checked )
  dest->Add( L"2" ) ;
 if( chkContainer->Checked )
  dest->Add( L"3" ) ;
 if( chkKeychain->Checked )
  dest->Add( L"4" ) ;
}
//---------------------------------------------------------------------------

void addFilterStr( UnicodeString& dest, UnicodeString filterPart  )
{
  if( filterPart.Length() == 0 )
     return ;
  if( dest.Length() )
    dest += " AND " ;
  dest += filterPart ;
}
//---------------------------------------------------------------------------

UnicodeString  TMainForm::makeItemsFilter()
{
  UnicodeString filter  ;
  TStringList* types = new TStringList() ;
  getTypeFilter( types ) ;

  UnicodeString typesFilter ;
  if( types->Count )
   typesFilter = UnicodeString( L"\"Type\" IN( " ) + types->CommaText + L" ) " ;
  delete types ;
  addFilterStr( filter, typesFilter )  ;

  if( chkAddeFrom->Checked )
    addFilterStr( filter, L" \"DateCreated\" >= :dateFrom "  ) ;
  if( chkAddeTo->Checked )
    addFilterStr( filter, L" \"DateCreated\" <= :dateTo "  ) ;

  if( chkPrice->Checked )
   {
     UnicodeString price ;
     if( udItemPriceFrom->Position > 0  )
       price.printf( L" \"Price\" >= %d ", udItemPriceFrom->Position ) ;
     addFilterStr( filter, price  ) ;
     price = L"" ;
     if( udItemPriceTo->Position > 0  )
      price.printf( L" \"Price\" >= %d ", udItemPriceTo->Position ) ;
     addFilterStr( filter, price ) ;
   }
   if( edtItemOwnerMask->Text.Trim().Length() > 0 )
   {
//     UnicodeString s ;
//     s.printf( L"LOWER(\"Owner\") LIKE :OwnerName", edtItemOwnerMask->Text.Trim().c_str() ) ;
     addFilterStr( filter, L" LOWER(u.\"Username\") LIKE :Owner_name " ) ;
   }
   return  filter ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnFilterItemsClick(TObject *Sender)
{
//
  UnicodeString  filter  = makeItemsFilter() ;
  if( filter.Length() > 0 )
  {
     UnicodeString sql = itemsSQL + " WHERE " + filter ;
     fdqryItems->SQL->Text = sql ;
     UnicodeString s = edtItemOwnerMask->Text.Trim().LowerCase();

     if( s.Length() > 0 )
        fdqryItems->ParamByName("Owner_name")->AsString  = s.c_str() ;
    if( chkAddeFrom->Checked )
        fdqryItems->ParamByName("dateFrom")->AsDateTime  = dtAddedFrom->DateTime ;
    if( chkAddeTo->Checked )
        fdqryItems->ParamByName("dateTo")->AsDateTime  = dtAddedTo->DateTime ;
     fdqryItems->Close() ;
     fdqryItems->Open() ;
  }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnAllItemsClick(TObject *Sender)
{
//   if( fdqryItems->SQL->Text == itemsSQL )
//        return ;
//
  fdqryItems->SQL->Text = itemsSQL ;
  fdqryItems->Close() ;
  fdqryItems->Open() ;
//  chkWP->Checked = false ;
//  chkStk->Checked = false ;
//  chkContainer->Checked = false ;
//  chkKeychain->Checked = false ;
//  chkAddeFrom->Checked = false ;
//  chkAddeTo->Checked = false ;
//  chkPrice->Checked = false ;

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::chkJoinedFromClick(TObject *Sender)
{
 dtJoinedFrom->Enabled = chkJoinedFrom->Checked ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::chkJoinedToClick(TObject *Sender)
{
 dtJoinedTo->Enabled = dtJoinedTo->Checked ;
}
//---------------------------------------------------------------------------

UnicodeString  TMainForm::makeUserFilter()
{
  UnicodeString filter  ;

  UnicodeString activeFilter ;
  if( chkInactive->Checked )
     addFilterStr( filter, L" \"Archive\" = TRUE " )  ;
  else
    addFilterStr( filter, L" \"Archive\" = FALSE " )  ;

  if( chkResreicted->Checked )
    addFilterStr( filter, " \"RestrictionType\" <> 0 ")  ;

  if( chkJoinedFrom->Checked )
    addFilterStr( filter, L" \"DateJoined\" >= :dateFrom "  ) ;
  if( chkJoinedTo->Checked )
    addFilterStr( filter, L" \"DateJoined\" <= :dateTo "  ) ;

   UnicodeString price ;
  if( udBalanceFrom->Position > 0  )
       price.printf( L" \"Balance\" >= %d ", udBalanceFrom->Position ) ;
   addFilterStr( filter, price  ) ;
   price = L"" ;
   if( udBalanceTo->Position > 0  )
      price.printf( L" \"Balance\" >= %d ", udBalanceTo->Position ) ;
     addFilterStr( filter, price ) ;

   if( edtUserMask->Text.Trim().Length() > 0 )
   {
     UnicodeString s ;
     s.printf( L"LOWER(\"Username\") LIKE LOWER('%ls')", edtUserMask->Text.Trim().c_str() ) ;
     addFilterStr( filter, s) ;
   }
   return  filter ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnFilterUsersClick(TObject *Sender)
{
//
  UnicodeString  filter  = makeUserFilter() ;
  if( filter.Length() > 0 )
  {
     UnicodeString sql = usersSQL + " WHERE " + filter ;
     fdqryUsers->SQL->Text = sql ;

    if( chkJoinedFrom->Checked )
        fdqryUsers->ParamByName("dateFrom")->AsDateTime  = dtJoinedFrom->DateTime ;
    if( chkJoinedTo->Checked )
        fdqryUsers->ParamByName("dateTo")->AsDateTime  = dtJoinedTo->DateTime ;
     fdqryUsers->Close() ;
     fdqryUsers->Open() ;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnAllUsersClick(TObject *Sender)
{

  UnicodeString  sql = usersSQL + " where \"Archive\" = FALSE " ;
//  if( fdqryUsers->SQL->Text == sql )
//        return ;
//  chkInactive->Checked = false;
  fdqryUsers->SQL->Text = sql ;
  fdqryUsers->Close() ;
  fdqryUsers->Open() ;
//  chkJoinedFrom->Checked = false ;
//  chkJoinedTo->Checked = false ;
//  chkInactive->Checked = false ;
//  chkResreicted->Checked = false ;
}
//---------------------------------------------------------------------------

UnicodeString  TMainForm::makeTrancactionFilter()
{
 UnicodeString  filter ;
 UnicodeString  s ;
/*
              "s.\"Username\" AS \"SellerName\", "
              "b.\"Username\" AS \"BuyerName\", "
              "i.\"Nametag\" AS \"ItemNametag\", "
*/
 if( edtSeller->Text.Trim().Length() )
 {
//    s.printf( L" LOWER(s.\"Username\") LIKE LOWER('%ls') ", edtSeller->Text.Trim().c_str() ) ;
    addFilterStr( filter, L" LOWER(s.\"Username\") LIKE :Seller ") ;
 }

 if( edtByer->Text.Trim().Length() )
 {
//    s.printf( L" LOWER(b.\"Username\") LIKE LOWER('%ls') ", edtByer->Text.Trim().c_str() ) ;
    addFilterStr( filter, L" LOWER(b.\"Username\") LIKE :Buyer") ;
 }

 if( edtItems->Text.Trim().Length() )
 {
//    s.printf( L" LOWER(i.\"Nametag\") LIKE LOWER('%ls') ", edtItems->Text.Trim().c_str() ) ;
    addFilterStr( filter, L" LOWER(i.\"Nametag\") LIKE :Item_name ") ;
 }
  if( chkTrDateFrom->Checked )
    addFilterStr( filter, L" t.\"Date\" >= :dateFrom "  ) ;
  if( chkTrDateTo->Checked )
    addFilterStr( filter, L" t.\"Date\" <= :dateTo "  ) ;

   UnicodeString price ;
  if( udPriceFrom->Position > 0  )
       price.printf( L" \"Price\" >= %d ", udPriceFrom->Position ) ;
   addFilterStr( filter, price  ) ;
   price = L"" ;
   if( udPriceTo->Position > 0  )
      price.printf( L" \"Price\" >= %d ", udPriceTo->Position ) ;

  if( chkTransArchived->Checked == true )
     addFilterStr( filter, L" t.\"Archive\" = FALSE" ) ;
   else
     addFilterStr( filter, L" t.\"Archive\" = TRUE" ) ;

  if( chkTransCancelled->Checked == true )
     addFilterStr( filter, L" t.\"Canceled\" = TRUE" ) ;
  else
     addFilterStr( filter, L" t.\"Canceled\" = FALSE" ) ;
  return filter ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actDashboardExecute(TObject *Sender)
{
  DashBoardForm->init() ;
  DashBoardForm->ShowModal() ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnFilterTransactionsClick(TObject *Sender)
{
  UnicodeString  filter  = makeTrancactionFilter() ;
  if( filter.Length() > 0 )
  {
     UnicodeString sql = transactionSQL + " WHERE " + filter ;
     fdqryTransaction->SQL->Text = sql ;
     UnicodeString s = edtSeller->Text.Trim().LowerCase() ;

     if( s.Length() )
        fdqryTransaction->ParamByName("Seller")->AsString  = s ;

     s = edtByer->Text.Trim().LowerCase() ;
     if( s.Length() )
        fdqryTransaction->ParamByName("Buyer")->AsString  = s ;

     s = edtItems->Text.Trim().LowerCase() ;
     if( s.Length() )
        fdqryTransaction->ParamByName("Item_name")->AsString  = s ;

    if( chkTrDateFrom->Checked )
        fdqryTransaction->ParamByName("dateFrom")->AsDateTime  = dtTrarnsFrom->DateTime ;
    if( chkTrDateTo->Checked )
        fdqryTransaction->ParamByName("dateTo")->AsDateTime  = dtTrarnsTo->DateTime ;
     fdqryTransaction->Close() ;
     fdqryTransaction->Open() ;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnAllTransactionsClick(TObject *Sender)
{
//   if( fdqryTransaction->SQL->Text == transactionSQL )
//        return ;

  fdqryTransaction->SQL->Text = transactionSQL ;
  fdqryTransaction->Close() ;
  fdqryTransaction->Open() ;
//  chkTransArchived->Checked = false ;
//  chkTransCancelled->Checked = false ;
//  chkContainer->Checked = false ;
//  chkKeychain->Checked = false ;
//  chkAddeFrom->Checked = false ;
//  chkAddeTo->Checked = false ;
//  chkPrice->Checked = false ;

}
//---------------------------------------------------------------------------



void __fastcall TMainForm::actPickValueExecute(TObject *Sender)
{
 TDBGrid* grid = getActiveDBGrid() ;
 if( grid == NULL )
    return ;

 UnicodeString val = grid ->SelectedField->AsString ;
 if( val.Length() )
 {
   Clipboard()->Open() ;
   Clipboard()->SetTextBuf( val.c_str() ) ;
   Clipboard()->Close() ;
 }
}
//---------------------------------------------------------------------------

TDBGrid* TMainForm::getActiveDBGrid()
{
  return dynamic_cast<TDBGrid*>( ActiveControl ) ;
}
//---------------------------------------------------------------------------


void TMainForm::archiveTransaction( bool doArchive )
{
   bool in_arch = fdqryTransaction->FieldByName( "Archive" )->AsBoolean ;
   if( in_arch == doArchive )
      return ;

 int id = fdqryTransaction->FieldByName(L"TransactionID")->AsInteger ;
 if( id == 0 )
    return ;
 try {

    fdqryLock->Close();

    fdqryLock->FetchOptions->Unidirectional = true;
    fdqryLock->FetchOptions->Mode = fmAll;
    fdqryLock->FetchOptions->CursorKind = ckForwardOnly;
    fdqryLock->ResourceOptions->CmdExecMode = amBlocking;
//////////////////////////////////////////////////////////////////////////
    fdqryLock->SQL->Text =
        "SELECT 1 FROM \"Transactions\" "
        "WHERE \"TransactionID\" = :ID FOR UPDATE NOWAIT";
    fdqryLock->ParamByName("ID")->AsInteger = id;
    fdqryLock->Open();  // Блокировка строки

    fdqryInsert->Close();
    fdqryInsert->SQL->Text =
        "UPDATE \"Transactions\" SET \"Archive\" = :A WHERE \"TransactionID\" = :ID";
    fdqryInsert->ParamByName("A")->AsBoolean = doArchive;
    fdqryInsert->ParamByName("ID")->AsInteger = id;
     fdtrans1->StartTransaction();
     fdqryInsert->ExecSQL();
     fdtrans1->Commit();
     put_log( false, "Transaction, id: %d was %s",
                     id,
                     doArchive ? "archived" : "restored" ) ;
  }

  catch(Exception &e)
  {
        fdtrans1->Rollback();
        put_log( true, "Transaction, id: %d was %s error: %s ",
                        doArchive ? "archivation" : "restoring",
                        id,
                        AnsiString( e.Message ).c_str() ) ;
     return ;
  }
 fdqryTransaction->Close() ;
 fdqryTransaction->Open() ;
}


void __fastcall TMainForm::actSoftDeleteTransactionExecute(TObject *Sender)
{
    archiveTransaction( true ) ;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::actRestoreTtransactionExecute(TObject *Sender)
{
    archiveTransaction( false ) ;
}
//---------------------------------------------------------------------------

void TMainForm::archiveUser( bool doArchive )
{
   bool in_arch = fdqryUsers->FieldByName( "Archive" )->AsBoolean ;
   if( in_arch == doArchive )
      return ;

   int id = fdqryUsers->FieldByName( "ID" )->AsInteger ;
   AnsiString name = fdqryUsers->FieldByName(L"Username")->AsString  ;
   UnicodeString sql ;
   sql.printf(  L"UPDATE \"Users\" SET \"Archive\" = %ls, \"Version\" = \"Version\" + 1 WHERE \"ID\" = :OLD_ID AND \"Version\" = :OLD_Version",
                       doArchive ? L"TRUE" : L"FALSE"   ) ;

    fdpdtsqlUsers->ModifySQL->Text =  sql ;
    try {
         fdtrans1->StartTransaction();

         fdqryUsers->Edit();
         fdqryUsers->Post();
         fdtrans1->Commit();
         put_log( false, "User, name: \"%s\", id: %d was %s",
                         name.c_str(),
                         id,
                         doArchive ? "archived" : "restored" ) ;
         fdqryUsers->ApplyUpdates(0);
//         fdqryUsers->Close();
//         fdqryUsers->Open();
    }
    catch(Exception &e) {
        if(fdtrans1->Active)
            fdtrans1->Rollback();
         put_log( true, "User, name: \"%s\", id: %d was %s error: %s ",
                          name.c_str(),
                          doArchive ? "archivation" : "restoring",
                          id,
                          AnsiString( e.Message ).c_str() ) ;
    }

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//Обработка ошибок при оптимистичном блокировваннии таблицы "Users"
//---------------------------------------------------------------------------
void __fastcall TMainForm::fdqryUsersUpdateError( TDataSet *ASender, EFDException *AException,
                                                  TFDDatSRow *ARow, TFDUpdateRequest ARequest,
                                                  TFDErrorAction &AAction)
{
    UnicodeString msg = AException->Message;
    if (msg.Pos(L"Record changed") > 0 ||
        msg.Pos(L"Row not found") > 0)
    {
        ShowMessage(
               L"Error: record was changed by another user.\n"
			   "Refresh data to continue."
        );

        AAction = eaSkip;  // или eaFail
        return;
    }
    // Другие ошибки
    ShowMessage( L"Update error: " + AException->Message);
    AAction = eaFail;
}
//---------------------------------------------------------------------------


