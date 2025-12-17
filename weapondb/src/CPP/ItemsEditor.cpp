//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "ItemsEditor.h"
#include "MainFrm.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TItemEditForm *ItemEditForm;
//---------------------------------------------------------------------------
__fastcall TItemEditForm::TItemEditForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TItemEditForm::Clear()
{
 ud1->Position = 10 ;
 lbledt3->Text = L"" ;
 img1->Picture->Assign(NULL);

 dblklstItemDescription->Enabled = true ;
 dblklstItemDescription->KeyValue = 1 ;
 dblklst1->Enabled = true ;
 dblklst1->KeyValue = 1 ;
 dblklstSpecialDescription->Enabled = true ;
 dblklstSpecialDescription->KeyValue = 1 ;
 pictModified = false ;
}

void __fastcall TItemEditForm::FormCreate(TObject *Sender)
{
//DBLookupComboBoxType->DataSource = dsItems;
//DBLookupComboBoxType->DataField = "Type";

// Weapon
  dblklst1->ListSource = MainForm->dsWeaponID ;
  dblklst1->ListField = "Weapon";
  dblklst1->KeyField = "WeaponID";
//DBLookupComboBoxWeapon->DataSource = dsItems;
//DBLookupComboBoxWeapon->DataField = "WeaponID";

// Special
  dblklstSpecialDescription->ListSource = MainForm->dsSpecial;
  dblklstSpecialDescription->ListField = "Category";
  dblklstSpecialDescription->KeyField = "SpecialID";
  //DBLookupComboBoxSpecial->DataSource = dsItems;
 dblklstItemDescription->ListSource = MainForm->dsItemTypes;
 dblklstItemDescription->ListField = "Description";
 dblklstItemDescription->KeyField = "TypeID";
}
//---------------------------------------------------------------------------
void __fastcall TItemEditForm::dblklstItemDescriptionClick(TObject *Sender)
{
 if( dblklstItemDescription->KeyValue != WEAPON_TYPE )
 {
   dblklst1->Enabled = false ;
   dblklstSpecialDescription->Enabled = false ;
 }
 else
 {
   dblklst1->Enabled = true;
   dblklstSpecialDescription->Enabled = true ;
 }

}
//---------------------------------------------------------------------------
void __fastcall TItemEditForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  if( ModalResult != mrOk )
     return ;

  if( checkDBLookupListBoxValue( this, dblklstItemDescription, L"Type" )  == false ||
      checkDBLookupListBoxValue( this, dblklst1, L"Weapon" )  == false ||
      checkDBLookupListBoxValue( this, dblklstSpecialDescription, L"Kind" )  == false )
    {
      ModalResult = mrNone ;
      return ;
    }

  UnicodeString msg ;
  TControl* c = NULL ;
  if( lbledt3->Text.Trim().Length() == 0 )
  {
     msg = L"Fill 'Nametag' field!" ;
     c = lbledt3 ;
  }
  else if( ud1->Position == 0 )
       {
           msg = L"Set price!" ;
           c = lbledt2 ;
       }
       else  if( img1->Picture->Graphic == NULL ||
                  img1->Picture->Graphic->Empty == true )
                     msg = L"Set picture!" ;

  if( msg.Length() > 0 )
  {
     MessageDlg( msg,  mtError, TMsgDlgButtons() << mbOK,  0);
     FocusControl( lbledt2 ) ;
     ModalResult = mrNone ;
  }
}
//---------------------------------------------------------------------------

void __fastcall TItemEditForm::btn3Click(TObject *Sender)
{
 if( dlgOpenPic1->Execute() ==false )
     return ;
 pictModified = true ;
 img1->Picture->LoadFromFile( dlgOpenPic1->FileName ) ;
}
//---------------------------------------------------------------------------

void TItemEditForm::setEditFieRow( TFDQuery *fdqry )
{
  Clear() ;
  dblklstItemDescription->KeyValue = fdqry->FieldByName(L"Type")->Value ;
  dblklstItemDescription->Enabled = false ;
  dblklst1->Enabled = false ;
  dblklstSpecialDescription->Enabled = false ;

  lbledt3->Text = fdqry->FieldByName(L"Nametag")->AsString ;
  ud1->Position =  fdqry->FieldByName(L"Price")->AsInteger ;
  loadDBBitmap(  fdqry,  img1 ) ;
}

