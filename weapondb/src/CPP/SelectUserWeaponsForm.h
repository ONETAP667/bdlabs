//---------------------------------------------------------------------------

#ifndef SelectUserWeaponsFormH
#define SelectUserWeaponsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <Vcl.DBCtrls.hpp>
//---------------------------------------------------------------------------
class TSelWeaponsForm : public TForm
{
__published:	// IDE-managed Components
  TFDQuery *fdqry1;
  TDataSource *ds1;
  TDBLookupListBox *dblklst1;
  TButton *btn1;
  TButton *btn2;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
  __fastcall TSelWeaponsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelWeaponsForm *SelWeaponsForm;
//---------------------------------------------------------------------------
int selectWeapons( int userID, int weaponType ) ;
#endif
