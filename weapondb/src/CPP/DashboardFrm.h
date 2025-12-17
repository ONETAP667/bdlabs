//---------------------------------------------------------------------------

#ifndef DashboardFrmH
#define DashboardFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
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
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TDashBoardForm : public TForm
{
__published:	// IDE-managed Components
  TFDQuery *qMarket;
  TFDQuery *qUsers;
  TFDQuery *qDeals;
  TDataSource *dsUsers;
  TDataSource *dsDeals;
  TFDQuery *fdqrySvc;
  TPageControl *pgc1;
  TTabSheet *ts1;
  TPanel *pnl3;
  TButton *btnRefresh;
  TGroupBox *grp1;
  TComboBox *cbUser;
  TPanel *pnl1;
  TLabel *lblMarket;
  TSplitter *spl1;
  TDBGrid *dbgrdUsers;
  TPanel *pnl;
  TPanel *pnl2;
  TChart *chtDeals;
  TFastLineSeries *Series1;
  TCheckBox *chk1;
  TGroupBox *grp2;
  TLabel *lbl2;
  TDateTimePicker *dpFrom;
  TLabel *lbl3;
  TDateTimePicker *dpTo;
  TCheckBox *chk2;
  TTabSheet *ts2;
  TPanel *pnl4;
  TDBGrid *dbgTrend;
  TFDQuery *qPriceTrend;
  TDataSource *dsPriceTrend;
  TPanel *pnl31;
  TButton *btnRefresh1;
  TGroupBox *grp11;
  TComboBox *cbType;
  TLabeledEdit *edSearch;
  TLabel *lbl1;
  TLabel *lbl11;
  TComboBox *cbWeapon;
  TLabel *lbl111;
  TComboBox *cbSpecial;
  TRadioGroup *cbOrder;
  TCheckBox *chk3;
  void __fastcall btnRefreshClick(TObject *Sender);
  void __fastcall chk1Click(TObject *Sender);
  void __fastcall chk2Click(TObject *Sender);
  void __fastcall btnRefresh1Click(TObject *Sender);
  void __fastcall qMarketBeforeOpen(TDataSet *DataSet);
  void __fastcall cbTypeChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TDashBoardForm(TComponent* Owner);
   void init() ;

protected:
   void LoadMarketStats();
   void LoadUserInventory();
   void LoadDealsChart();
   void loadUsers() ;
   void loadItemsFilterLists() ;
   void loadPriceTrend() ;

};
//---------------------------------------------------------------------------
extern PACKAGE TDashBoardForm *DashBoardForm;
//---------------------------------------------------------------------------
#endif
