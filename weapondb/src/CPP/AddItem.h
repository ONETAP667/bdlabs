//---------------------------------------------------------------------------

#ifndef AddItemH
#define AddItemH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
  TButton *btn1;
  TButton *btn2;
  TLabeledEdit *lbledt2;
  TUpDown *ud1;
  TLabeledEdit *lbledt3;
  TLabel *lbl1;
  TDBLookupListBox *dblklstItemDescription;
  TLabeledEdit *lbledt4;
  TDBLookupListBox *dblklst1;
  TLabel *lbl2;
  TDBLookupListBox *dblklstSpecialDescription;
  TLabel *lbl211;
  void __fastcall dblklstItemDescriptionClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
