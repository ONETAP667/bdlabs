//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserParsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditUserForm *EditUserForm;
//---------------------------------------------------------------------------
__fastcall TEditUserForm::TEditUserForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEditUserForm::lbledt1Change(TObject *Sender)
{
  btn1->Enabled = lbledt1->Text.Trim().Length() > 0 ;
}
//---------------------------------------------------------------------------
