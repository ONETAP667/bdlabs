//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "DashboardFrm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TDashBoardForm *DashBoardForm;
//---------------------------------------------------------------------------
__fastcall TDashBoardForm::TDashBoardForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TDashBoardForm::LoadMarketStats()
{
    qMarket->Close();

    UnicodeString sql =
        L"SELECT "
        " COUNT(*) FILTER (WHERE \"Canceled\"=FALSE) AS total_deals, "
        " SUM(\"Price\") FILTER (WHERE \"Canceled\"=FALSE) AS total_turnover, "
        " AVG(\"Price\") FILTER (WHERE \"Canceled\"=FALSE) AS avg_price "
        "FROM \"Transactions\" t "
        "WHERE t.\"Canceled\"=FALSE " ;
      if( chk2->Checked )
        sql += L"  AND t.\"Date\" BETWEEN :d1 AND :d2 ";

    // Фильтр по пользователю (в сделках)
    if ( chk1->Checked )
        sql += L" AND (t.\"SellerID\"=(SELECT \"ID\" FROM \"Users\" WHERE \"Username\"=:uname) "
               "OR  t.\"BuyerID\"=(SELECT \"ID\" FROM \"Users\" WHERE \"Username\"=:uname)) ";

    qMarket->SQL->Text = sql;

     if( chk2->Checked )
     {
       qMarket->ParamByName("d1")->AsDate = dpFrom->Date;
      qMarket->ParamByName("d2")->AsDate = dpTo->Date + 1;
      }
    if ( chk1->Checked )
        qMarket->ParamByName("uname")->AsString = cbUser->Text;

    qMarket->Open();

    lblMarket->Caption = "\n Deals: " + qMarket->FieldByName("total_deals")->AsString +
						 "  Turnover: " + qMarket->FieldByName("total_turnover")->AsString +
						 "  Average Price: " + qMarket->FieldByName("avg_price")->AsString;
}

void TDashBoardForm::LoadUserInventory()
{
//    qUsers->Close();
//    qUsers->SQL->Text =
//        "SELECT u.\"Username\", COUNT(i.\"ID\") AS items_count, SUM(i.\"Price\") AS total_value "
//        "FROM \"Users\" u "
//        "LEFT JOIN \"Items\" i ON i.\"OwnerID\" = u.\"ID\" "
//        "GROUP BY u.\"Username\" "
//        "ORDER BY total_value DESC NULLS LAST";
//    qUsers->Open();
qUsers->Close();

    UnicodeString sql =
        "SELECT u.\"Username\", COUNT(i.\"ID\") AS items_count, SUM(i.\"Price\") AS total_value "
        "FROM \"Users\" u "
        "LEFT JOIN \"Items\" i ON i.\"OwnerID\" = u.\"ID\" "
        "WHERE 1=1 ";

    if ( chk1->Checked )
        sql += " AND u.\"Username\" = :uname ";

    sql +=
        "GROUP BY u.\"Username\" "
        "ORDER BY total_value DESC NULLS LAST";

    qUsers->SQL->Text = sql;

    if ( chk1->Checked ) // 0 — "Все"
        qUsers->ParamByName("uname")->AsString = cbUser->Text;

    qUsers->Open();
}

void TDashBoardForm::LoadDealsChart()
{
//    qDeals->Close();
//    qDeals->SQL->Text =
//        "SELECT DATE(\"Date\") AS day, COUNT(*) AS deals "
//        "FROM \"Transactions\" "
//        "WHERE \"Canceled\"=FALSE "
//        "GROUP BY day ORDER BY day";
//    qDeals->Open();
//
//    Series1->Clear();  // вместо seriesDeals
//
//    while (!qDeals->Eof)
//    {
//        Series1->Add(
//            qDeals->FieldByName("deals")->AsInteger,
//            qDeals->FieldByName("day")->AsString
//        );
//        qDeals->Next();
//    }
    qDeals->Close();

    UnicodeString sql =
        "SELECT DATE(\"Date\") AS day, COUNT(*) AS deals "
        "FROM \"Transactions\" "
        "WHERE \"Canceled\"=FALSE ";

   // Фильтр по диапазону дат
    if( chk2->Checked )
       sql += " AND \"Date\" BETWEEN :d1 AND :d2 ";

    sql += "GROUP BY day ORDER BY day";

    qDeals->SQL->Text = sql;

    if( chk2->Checked )
    {
      qDeals->ParamByName("d1")->AsDate = dpFrom->Date;
      qDeals->ParamByName("d2")->AsDate = dpTo->Date + 1; // включает конец дня
    }
    qDeals->Open();
    Series1->Clear();
    while (!qDeals->Eof)
    {
        Series1->Add(
            qDeals->FieldByName("deals")->AsInteger,
            qDeals->FieldByName("day")->AsString
        );
        qDeals->Next();
    }
}

void __fastcall TDashBoardForm::btnRefreshClick(TObject *Sender)
{
    LoadMarketStats();
    LoadUserInventory();
    LoadDealsChart();
}
//---------------------------------------------------------------------------

void TDashBoardForm::loadUsers()
{
//    cbUser->Items->Add("All") ;
//    fdqrySvc->Connection = conn;
    fdqrySvc->SQL->Text = "SELECT \"Username\" FROM \"Users\" ORDER BY \"Username\"";
    fdqrySvc->Open();

    while(!fdqrySvc->Eof)
    {
        cbUser->Items->Add(fdqrySvc->FieldByName("Username")->AsString);
        fdqrySvc->Next();
    }
    fdqrySvc->Close();
    cbUser->ItemIndex = 0;

//    btnApplyFiltersClick(nullptr);
}
void __fastcall TDashBoardForm::chk1Click(TObject *Sender)
{
 if( chk1->Checked )
 {
   cbUser->Enabled = true ;
   FocusControl( cbUser ) ;
//   if( Visible )
//      cbUser->DropDown = true ;
 }
 else
   cbUser->Enabled = false ;
}
//---------------------------------------------------------------------------

void __fastcall TDashBoardForm::chk2Click(TObject *Sender)
{
   grp2->Enabled =  chk2->Checked ;
}
//---------------------------------------------------------------------------

void TDashBoardForm::init()
{
  if( cbUser->Items->Count > 0 )
     return ;
  loadUsers() ;
  loadItemsFilterLists() ;
  chk1Click( NULL ) ;
  chk2Click( NULL ) ;
  btnRefreshClick( NULL ) ;
  loadPriceTrend() ;
}


void TDashBoardForm::loadItemsFilterLists()
{
    fdqrySvc->SQL->Text = "SELECT \"TypeID\", \"Description\" FROM \"ItemTypes\" ORDER BY \"Description\"";
    fdqrySvc->Open();
    cbType->Items->Add("All");
    while (!fdqrySvc->Eof) {
        cbType->Items->AddObject(fdqrySvc->FieldByName("Description")->AsString,
                                 (TObject*)fdqrySvc->FieldByName("TypeID")->AsInteger);
        fdqrySvc->Next();
    }
    cbType->ItemIndex = 0;

    fdqrySvc->SQL->Text = "SELECT \"WeaponID\", \"Weapon\" FROM \"WeaponIDToWeapon\" ORDER BY \"Weapon\"";
    fdqrySvc->Open();
    cbWeapon->Items->Add("All");
    while (!fdqrySvc->Eof) {
        cbWeapon->Items->AddObject(fdqrySvc->FieldByName("Weapon")->AsString,
                                   (TObject*)fdqrySvc->FieldByName("WeaponID")->AsInteger);
        fdqrySvc->Next();
    }
    cbWeapon->ItemIndex = 0;

    fdqrySvc->SQL->Text = "SELECT \"SpecialID\", \"Category\" FROM \"SpecialToCategory\" ORDER BY \"Category\"";
    fdqrySvc->Open();
    cbSpecial->Items->Add("All");
    while (!fdqrySvc->Eof) {
        cbSpecial->Items->AddObject(fdqrySvc->FieldByName("Category")->AsString,
                                   (TObject*)fdqrySvc->FieldByName("SpecialID")->AsInteger);
        fdqrySvc->Next();
   }
   cbSpecial->ItemIndex = 0;
}

void TDashBoardForm::loadPriceTrend()
{
    qPriceTrend->Close();

    // --- Основной SQL в подзапросе (чтобы FireDAC не ломал WINDOW) ---
    UnicodeString sql =
        "SELECT * FROM ( "
        "    SELECT "
        "        i.\"ID\" AS ItemID, "
        "        i.\"Nametag\", "
        "        FIRST_VALUE(t.\"Price\") OVER w AS first_price, "
        "        LAST_VALUE(t.\"Price\") OVER w AS last_price, "
        "        AVG(t.\"Price\") OVER w AS avg_price, "
        "        (LAST_VALUE(t.\"Price\") OVER w - FIRST_VALUE(t.\"Price\") OVER w) AS price_change, "
        "        ROUND( (LAST_VALUE(t.\"Price\") OVER w - FIRST_VALUE(t.\"Price\") OVER w) "
        "               * 100.0 / NULLIF(FIRST_VALUE(t.\"Price\") OVER w, 0), 2) AS change_percent "
        "    FROM \"Transactions\" t "
        "    JOIN \"Items\" i ON i.\"ID\" = t.\"ItemID\" "
        "    WHERE t.\"Canceled\" = FALSE ";

    // --------------------------------
    //      ФИЛЬТРЫ ТВОИХ КОНТРОЛОВ
    // --------------------------------

    // Поиск по имени
    if (!edSearch->Text.IsEmpty())
        sql += " AND LOWER(i.\"Nametag\") LIKE LOWER(:search) ";

    // Тип
    if (cbType->ItemIndex > 0)
        sql += " AND i.\"Type\" = :type ";

    // Оружие
    if (cbWeapon->ItemIndex > 0)
        sql += " AND i.\"Weapon\" = :weapon ";

    // Категория (Special)
    if (cbSpecial->ItemIndex > 0)
        sql += " AND i.\"Special\" = :special ";

    // Закрываем подзапрос
    sql +=
        "    WINDOW w AS ( "
        "        PARTITION BY t.\"ItemID\" "
        "        ORDER BY t.\"Date\" "
        "        ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING "
        "    ) "
        ") sub ";

    // -------------------------
    //      СОРТИРОВКА
    // -------------------------

    sql += " ORDER BY ";

    switch (cbOrder->ItemIndex)
    {
        case 0:  sql += " price_change DESC"; break;  // Рост цены
        case 1:  sql += " price_change ASC";  break;  // Падение
        case 2:  sql += " avg_price DESC";    break;  // Дорогие
        case 3:  sql += " avg_price ASC";     break;  // Дешевые
        case 4:  sql += " Nametag ASC";       break;  // Алфавит
        default: sql += " price_change DESC"; break;
    }

    // Устанавливаем SQL
    qPriceTrend->SQL->Text = sql;

    // -------------------------
    //      ПАРАМЕТРЫ
    // -------------------------

    if (!edSearch->Text.IsEmpty())
        qPriceTrend->ParamByName("search")->AsString =
            "%" + edSearch->Text + "%";

    if (cbType->ItemIndex > 0)
        qPriceTrend->ParamByName("type")->AsInteger =
            (int)cbType->Items->Objects[cbType->ItemIndex];

    if (cbWeapon->ItemIndex > 0)
        qPriceTrend->ParamByName("weapon")->AsInteger =
            (int)cbWeapon->Items->Objects[cbWeapon->ItemIndex];

    if (cbSpecial->ItemIndex > 0)
        qPriceTrend->ParamByName("special")->AsInteger =
            (int)cbSpecial->Items->Objects[cbSpecial->ItemIndex];

    qPriceTrend->Open();
}

void __fastcall TDashBoardForm::btnRefresh1Click(TObject *Sender)
{
  loadPriceTrend() ;
}
//---------------------------------------------------------------------------

void __fastcall TDashBoardForm::qMarketBeforeOpen(TDataSet *DataSet)
{
   logSQLs( DataSet, "Open" ) ;
}
//---------------------------------------------------------------------------

void __fastcall TDashBoardForm::cbTypeChange(TObject *Sender)
{
  if( chk3->Checked == true )
     loadPriceTrend() ;
}
//---------------------------------------------------------------------------

