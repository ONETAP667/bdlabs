//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "SelectUserWeaponsForm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TSelWeaponsForm *SelWeaponsForm;
//---------------------------------------------------------------------------
__fastcall TSelWeaponsForm::TSelWeaponsForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int selectWeapons( int userID, int weaponType )
{
  SelWeaponsForm->fdqry1->SQL->Text = "SELECT \"ID\", \"Nametag\" FROM \"Items\" WHERE \"Type\"=:Type AND \"OwnerID\" = :id ;";
//
  SelWeaponsForm->fdqry1->ParamByName("Type")->AsInteger = weaponType ;
  SelWeaponsForm->fdqry1->ParamByName("id")->AsInteger = userID ;
  SelWeaponsForm->fdqry1->Open() ;
  int ret = SelWeaponsForm->ShowModal() ;
  if( ret != mrOk )
     return 0 ;
  return SelWeaponsForm->dblklst1->KeyValue ;
}
//---------------------------------------------------------------------------
void __fastcall TSelWeaponsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  Variant v  = dblklst1->KeyValue ;
  if( v == Null )
  {
     MessageDlg( L"Select target weapon!",  mtError, TMsgDlgButtons() << mbOK,  0 );
     ModalResult = mrNone ;
  }
}
//---------------------------------------------------------------------------
