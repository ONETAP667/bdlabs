//---------------------------------------------------------------------------

#ifndef SelectUserH
#define SelectUserH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSelectUserForm : public TForm
{
__published:	// IDE-managed Components
  TButton *btnOk;
  TButton *btn1;
  TUpDown *ud1;
  TLabeledEdit *lbledt2;
  TLabel *lbl1;
  TDBLookupListBox *dblklst1;
  void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TSelectUserForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectUserForm *SelectUserForm;
//---------------------------------------------------------------------------
#endif
