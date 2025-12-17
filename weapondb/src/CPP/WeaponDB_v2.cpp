//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("UserParsForm.cpp", EditUserForm);
USEFORM("SelectUserWeaponsForm.cpp", SelWeaponsForm);
USEFORM("ItemsEditor.cpp", ItemEditForm);
USEFORM("MainFrm.cpp", MainForm);
USEFORM("SelectUser.cpp", SelectUserForm);
USEFORM("DashboardFrm.cpp", DashBoardForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
  try
  {
     Application->Initialize();
     Application->MainFormOnTaskBar = true;
     Application->CreateForm(__classid(TMainForm), &MainForm);
     Application->CreateForm(__classid(TEditUserForm), &EditUserForm);
     Application->CreateForm(__classid(TItemEditForm), &ItemEditForm);
     Application->CreateForm(__classid(TSelectUserForm), &SelectUserForm);
     Application->CreateForm(__classid(TSelWeaponsForm), &SelWeaponsForm);
     Application->CreateForm(__classid(TDashBoardForm), &DashBoardForm);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
