//---------------------------------------------------------------------------

#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <FireDAC.Phys.PG.hpp>
#include <FireDAC.Phys.PGDef.hpp>
#include <Vcl.DBCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Datasnap.DBClient.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
  TMainMenu *mm1;
  TMenuItem *U1;
  TMenuItem *ransactions1;
  TPageControl *pgc1;
  TStatusBar *stat1;
  TListView *lv1;
  TSplitter *spl1;
  TTabSheet *ts1;
  TDataSource *dsUsers;
  TFDQuery *fdqryUsers;
  TFDConnection *con1;
  TFDTransaction *fdtrans1;
  TFDQuery *fdqryUserItems;
  TDataSource *dsUserItems;
  TFDQuery *fdqryUserStikers;
  TDataSource *dsStikers;
  TPanel *pnl5;
  TPanel *pnl6;
  TPanel *pnl7;
  TSplitter *spl4;
  TPanel *pnl3;
  TLabel *lbl1;
  TDBGrid *dbgrd1;
  TPanel *pnl8;
  TPanel *pnl9;
  TLabel *lbl3;
  TDBGrid *dbgrd2;
  TSplitter *spl6;
  TPanel *pnl10;
  TLabel *lbl4;
  TDBGrid *dbgrd3;
  TTabSheet *ts2;
  TPanel *pnl1;
  TActionList *actlst1;
  TAction *actAddUser;
  TAction *actEditUser;
  TAction *actDeleteUser;
  TAction *actSoftDeleteUser;
  TAction *actRestoreUser;
  TFDUpdateSQL *fdpdtsqlUsers;
  TMenuItem *Adduser1;
  TMenuItem *Edituser1;
  TMenuItem *N1;
  TMenuItem *ActivateUser1;
  TMenuItem *Deactivateuser1;
  TMenuItem *N2;
  TMenuItem *Deleteuser1;
  TPopupMenu *pm1;
  TMenuItem *Adduser2;
  TMenuItem *Edituser2;
  TMenuItem *N3;
  TMenuItem *Deactivateuser2;
  TMenuItem *ActivateUser2;
  TMenuItem *N4;
  TMenuItem *Deleteuser2;
  TDBGrid *dbgrdItemsTable;
  TDataSource *dsItems;
  TFDQuery *fdqryItems;
  TDataSource *dsItemTypes;
  TDataSource *dsSpecial;
  TFDQuery *fdqryItemTypes;
  TFDQuery *fdqryWeaponID;
  TFDQuery *fdqrySpecial;
  TDataSource *dsWeaponID;
  TDataSource *dsRestriction;
  TFDQuery *fdqryRestriction;
  TMenuItem *Items1;
  TAction *actAddItem;
  TAction *actEditItem;
  TAction *actDeleteItem;
  TMenuItem *AddItem1;
  TMenuItem *EditItem1;
  TMenuItem *N5;
  TMenuItem *DeleteItem1;
  TTabSheet *stuff;
  TPanel *pnl11;
  TPanel *pnl42;
  TDBNavigator *dbnvgr22;
  TDBGrid *dbgrd42;
  TPanel *pnl12;
  TPanel *pnl;
  TPanel *pnl41;
  TDBNavigator *dbnvgr21;
  TDBGrid *dbgrd41;
  TSplitter *spl2;
  TPanel *pnl2;
  TPanel *pnl4;
  TDBNavigator *dbnvgr2;
  TDBGrid *dbgrd4;
  TFDQuery *fdqryInsert;
  TTabSheet *ts3;
  TFDQuery *fdqryTransaction;
  TDataSource *dsTransaction;
  TPanel *pnl13;
  TDBGrid *dbgrdTransactions;
  TAction *actSellTo;
  TPopupMenu *pm2;
  TMenuItem *actSellTo1;
  TMenuItem *N6;
  TMenuItem *AddItem2;
  TMenuItem *EditItem2;
  TMenuItem *N7;
  TMenuItem *Sellto1;
  TMenuItem *N8;
  TMenuItem *Deleteuser3;
  TAction *actDeleteTransaction;
  TAction *actCanceTransaction;
  TMenuItem *Cancel1;
  TMenuItem *N9;
  TMenuItem *Delete1;
  TPopupMenu *pm3;
  TMenuItem *Cancel2;
  TMenuItem *N10;
  TMenuItem *Delete2;
  TAction *actStick;
  TMenuItem *N11;
  TMenuItem *StickonWeapon1;
  TPopupMenu *pm4;
  TMenuItem *StickonWeapon2;
  TPanel *pnl14;
  TPanel *pnl43;
  TDBNavigator *dbnvgr23;
  TDBGrid *dbgrdRestrictions;
  TFDUpdateSQL *fdpdtsqlItems;
  TFDQuery *fdqryPreviews;
  TCheckBox *chkLog;
  TCheckBox *chkSqlLog;
  TPanel *pnl15;
  TLabel *lbl2;
  TDBImage *dbimgPreview;
  TPanel *pnl16;
  TAction *actRestoreTtransaction;
  TAction *actSoftDeleteTransaction;
  TCheckBox *chkJoinedFrom;
  TCheckBox *chkJoinedTo;
  TDateTimePicker *dtJoinedTo;
  TDateTimePicker *dtJoinedFrom;
  TGroupBox *grp31;
  TLabel *lbl511;
  TLabel *lbl52;
  TEdit *edt12;
  TUpDown *udBalanceFrom;
  TUpDown *udBalanceTo;
  TEdit *edt111;
  TEdit *edtUserMask;
  TGroupBox *grpState;
  TCheckBox *chkInactive;
  TCheckBox *chkResreicted;
  TButton *btnFilterUsers;
  TButton *btnAllUsers;
  TAction *actDashboard;
  TMenuItem *Analitics1;
  TMenuItem *Dashboard1;
  TButton *btnFilterTransactions;
  TButton *btnAllTransactions;
  TDateTimePicker *dtTrarnsFrom;
  TGroupBox *grp311;
  TLabel *lbl5111;
  TLabel *lbl521;
  TEdit *edt121;
  TUpDown *udPriceFrom;
  TUpDown *udPriceTo;
  TEdit *edt1111;
  TGroupBox *grpState1;
  TCheckBox *chkTransArchived;
  TCheckBox *chkTransCancelled;
  TCheckBox *chkTrDateFrom;
  TDateTimePicker *dtTrarnsTo;
  TEdit *edtSeller;
  TCheckBox *chkTrDateTo;
  TLabel *Seller;
  TLabel *lbl6;
  TEdit *edtByer;
  TLabel *lbl7;
  TPanel *pnl17;
  TDateTimePicker *dtAddedFrom;
  TButton *btnAllItems;
  TEdit *edtItemOwnerMask;
  TDateTimePicker *dtAddedTo;
  TCheckBox *chkAddeTo;
  TCheckBox *chkAddeFrom;
  TCheckBox *chkPrice;
  TGroupBox *grp3;
  TLabel *lbl51;
  TLabel *lbl5;
  TEdit *edt1;
  TUpDown *udItemPriceFrom;
  TUpDown *udItemPriceTo;
  TEdit *edt11;
  TGroupBox *grp2;
  TCheckBox *chkWP;
  TCheckBox *chkStk;
  TCheckBox *chkContainer;
  TCheckBox *chkKeychain;
  TButton *btnFilterItems;
  TLabel *lbl8;
  TLabel *lbl9;
  TLabel *lbl71;
  TEdit *edtItems;
  TAction *actPickValue;
  TMenuItem *N12;
  TMenuItem *Pickvalue1;
  TMenuItem *N13;
  TMenuItem *Pickvalue2;
  TMenuItem *N14;
  TMenuItem *Pickvalue3;
  TMenuItem *Pickvalue4;
  TMenuItem *N15;
  TMenuItem *actActivate1;
  TAction *actWeapons;
  TFDQuery *fdqryLock;
  TMenuItem *Softdelete1;
  TMenuItem *N16;
  TMenuItem *Softdelete2;
  TMenuItem *N17;
  TMenuItem *Restore1;
	TMenuItem *Weaponsonly1;
	TMenuItem *N18;
	TMenuItem *Weaponsonly2;
	TMenuItem *N19;

  void __fastcall btnFilterItemsClick(TObject *Sender);
  void __fastcall fdqryUsersAfterScroll(TDataSet *DataSet);
  void __fastcall chk1Click(TObject *Sender);
  void __fastcall fdqryUserItemsAfterScroll(TDataSet *DataSet);
  void __fastcall actAddUserExecute(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall dbnvgr1Click(TObject *Sender, TNavigateBtn Button);
  void __fastcall actEditUserExecute(TObject *Sender);
  void __fastcall actDeleteUserExecute(TObject *Sender);
  void __fastcall actSoftDeleteUserExecute(TObject *Sender);
  void __fastcall actRestoreUserExecute(TObject *Sender);
  void __fastcall actAddItemExecute(TObject *Sender);
  void __fastcall actDeleteItemExecute(TObject *Sender);
  void __fastcall actSellToExecute(TObject *Sender);
  void __fastcall actDeleteTransactionExecute(TObject *Sender);
  void __fastcall rg1Click(TObject *Sender);
  void __fastcall actStickUpdate(TObject *Sender);
  void __fastcall actStickExecute(TObject *Sender);
  void __fastcall actEditItemExecute(TObject *Sender);
  void __fastcall fdqryInsertBeforeOpen(TDataSet *DataSet);
  void __fastcall fdqryInsertBeforeExecute(TFDDataSet *DataSet);
  void __fastcall chkLogClick(TObject *Sender);
  void __fastcall chkSqlLogClick(TObject *Sender);
  void __fastcall pgc1Change(TObject *Sender);
  void __fastcall actRestoreTtransactionExecute(TObject *Sender);
  void __fastcall actCanceTransactionExecute(TObject *Sender);
  void __fastcall chkAddeFromClick(TObject *Sender);
  void __fastcall chkAddeToClick(TObject *Sender);
  void __fastcall chkPriceClick(TObject *Sender);
  void __fastcall btnAllItemsClick(TObject *Sender);
  void __fastcall chkJoinedFromClick(TObject *Sender);
  void __fastcall chkJoinedToClick(TObject *Sender);
  void __fastcall btnFilterUsersClick(TObject *Sender);
  void __fastcall btnAllUsersClick(TObject *Sender);
  void __fastcall actDashboardExecute(TObject *Sender);
  void __fastcall btnFilterTransactionsClick(TObject *Sender);
  void __fastcall btnAllTransactionsClick(TObject *Sender);
  void __fastcall actPickValueExecute(TObject *Sender);
  void __fastcall actSoftDeleteTransactionExecute(TObject *Sender);
  void __fastcall fdqryUsersUpdateError(TDataSet *ASender, EFDException *AException, TFDDatSRow *ARow, TFDUpdateRequest ARequest,
          TFDErrorAction &AAction);


private:	// User declarations
public:		// User declarations
  const char* func ;
  __fastcall TMainForm(TComponent* Owner);
  virtual __fastcall ~TMainForm();
  void __fastcall logStr( const UnicodeString& s, bool error  ) ;
  bool isItemAlreadySticked( int itemID ) ;
 protected:
  UnicodeString itemsSQL ;
  UnicodeString usersSQL ;
  UnicodeString transactionSQL ;

  UnicodeString makeItemsFilter() ;
  UnicodeString makeUserFilter() ;
  UnicodeString makeTrancactionFilter() ;
  void getTypeFilter( TStringList* dest ) ;
  void archiveTransaction( bool doArchive ) ;
  void archiveUser( bool doArchive ) ;
  TDBGrid *getActiveDBGrid()  ;
  bool beginLock() ;

 };
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
void put_log( bool error, const char* fmt, ... ) ;
bool checkDBLookupListBoxValue( TForm* owner, TDBLookupListBox* cb, const wchar_t* valName ) ;
bool loadDBBitmap(  TFDQuery* fdqryItems, TImage* ImagePreview,
                                        const wchar_t* field = L"Preview" ) ;
void logSQLs( TDataSet* DataSet, const char* sqlFunc = "Open"  ) ;

//void base64ToImg( TImage* dest, const UnicodeString& b64 ) ;
//UnicodeString img2Base64( TImage* img ) ;

#define WEAPON_TYPE 1

#endif
