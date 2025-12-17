//---------------------------------------------------------------------------

#ifndef ItemsEditorH
#define ItemsEditorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
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

//---------------------------------------------------------------------------
class TItemEditForm : public TForm
{
__published:	// IDE-managed Components
  TButton *btn1;
  TButton *btn2;
  TLabeledEdit *lbledt2;
  TUpDown *ud1;
  TLabeledEdit *lbledt3;
  TLabel *lbl1;
  TDBLookupListBox *dblklst1;
  TLabel *lbl2;
  TDBLookupListBox *dblklstSpecialDescription;
  TLabel *lbl211;
  TDBLookupListBox *dblklstItemDescription;
  TImage *img1;
  TLabel *lbl3;
  TButton *btn3;
  TOpenPictureDialog *dlgOpenPic1;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall dblklstItemDescriptionClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall btn3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  bool pictModified ;
  __fastcall TItemEditForm(TComponent* Owner);
  void Clear() ;
  void setEditFieRow( TFDQuery *fdqry ) ;
};
//---------------------------------------------------------------------------
extern PACKAGE TItemEditForm *ItemEditForm;
//---------------------------------------------------------------------------
#endif
