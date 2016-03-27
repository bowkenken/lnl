//----------------------------------------------------//
// MWT C++ Application Source File                    //
//      created by WideStudio Application Builder     //
//----------------------------------------------------//
#include <WScom.h>
#include <WSDappDev.h>

//--- OBJECT includes ---//
#include <WSCmainWindow.h>

//--- OBJECT instance variable ---//
WSCmainWindow* MenuWin;

//--- OBJECT src ---//

WSCbase* _create_win_MenuWin(){


  MenuWin = new  WSCmainWindow(NULL,"MenuWin");
      MenuWin->initialize();
  MenuWin->setPropertyV(WSNname,"MenuWin");
  MenuWin->setPropertyV(WSNx,(short)100);
  MenuWin->setPropertyV(WSNy,(short)100);
  MenuWin->setPropertyV(WSNwidth,(unsigned short)400);
  MenuWin->setPropertyV(WSNheight,(unsigned short)400);
  MenuWin->setPropertyV(WSNvis,(WSCbool)1);
    extern void MenuWinInit(WSCbase*);
    MenuWin->addProcedureV("MenuWinInit","MenuWinInit",MenuWinInit,0);

   MenuWin->setVisible(True);
   return MenuWin;
}

//--- end of src ---//
