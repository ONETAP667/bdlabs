//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "SelectUser.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TSelectUserForm *SelectUserForm;
//---------------------------------------------------------------------------
__fastcall TSelectUserForm::TSelectUserForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSelectUserForm::FormCreate(TObject *Sender)
{
  dblklst1->ListSource = MainForm->dsUsers ;
  dblklst1->ListField = "Username";
  dblklst1->KeyField = "ID";
}
//---------------------------------------------------------------------------
