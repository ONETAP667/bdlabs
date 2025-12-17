//---------------------------------------------------------------------------

#ifndef UserParsFormH
#define UserParsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TEditUserForm : public TForm
{
__published:	// IDE-managed Components
  TLabeledEdit *lbledt1;
  TLabeledEdit *lbledt2;
  TUpDown *ud1;
  TButton *btn1;
  TButton *btn2;
  void __fastcall lbledt1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TEditUserForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditUserForm *EditUserForm;
//---------------------------------------------------------------------------
#endif
