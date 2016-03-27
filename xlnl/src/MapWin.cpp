//----------------------------------------------------//
// MWT C++ Application Source File                    //
//      created by WideStudio Application Builder     //
//----------------------------------------------------//
#include <WScom.h>
#include <WSDappDev.h>

//--- OBJECT includes ---//
#include <WSCmainWindow.h>
#include <WSCvscrBar.h>
#include <WSCform.h>
#include <WSCwindow.h>
#include <WSCvbtn.h>
#include <WSCvlabel.h>
#include <WSCvdrawingArea.h>
#include <WSCvifield.h>

//--- OBJECT instance variable ---//
WSCmainWindow* MapWin = NULL;
WSCvscrBar* MapScrollY = NULL;
WSCvscrBar* MapScrollX = NULL;
WSCform* MapForm = NULL;
WSCwindow* MenuWin = NULL;
WSCvbtn* MenuBtnPrevPage = NULL;
WSCvbtn* MenuBtnNextPage = NULL;
WSCvbtn* MenuBtnCancel = NULL;
WSCvlabel* MenuLabelPage = NULL;
WSCwindow* StatWin = NULL;
WSCvdrawingArea* StatWinDrawArea = NULL;
WSCwindow* InpStrWin = NULL;
WSCvlabel* InpStrTtl = NULL;
WSCvifield* InpStrField = NULL;
WSCvbtn* InpStrCancel = NULL;
WSCvbtn* InpStrOk = NULL;

//--- OBJECT src ---//

WSCbase* _create_win_MapWin(){


  MapWin = new  WSCmainWindow(NULL,"MapWin");
      MapWin->initialize();
  MapWin->setPropertyV(WSNname,"MapWin");
  MapWin->setPropertyV(WSNtitleString,"Map");
  MapWin->setPropertyV(WSNx,(short)100);
  MapWin->setPropertyV(WSNy,(short)100);
  MapWin->setPropertyV(WSNwidth,(unsigned short)656);
  MapWin->setPropertyV(WSNheight,(unsigned short)656);
    extern void MapWinInit(WSCbase*);
    MapWin->addProcedureV("MapWinInit","MapWinInit",MapWinInit,0);

  MapScrollY = new  WSCvscrBar(MapWin,"MapScrollY");
      MapScrollY->initialize();
  MapScrollY->setPropertyV(WSNvalue,(unsigned long)640);
  MapScrollY->setPropertyV(WSNorientation,(unsigned char)1);
  MapScrollY->setPropertyV(WSNname,"MapScrollY");
  MapScrollY->setPropertyV(WSNvis,(WSCbool)1);
  MapScrollY->setPropertyV(WSNx,(short)640);
  MapScrollY->setPropertyV(WSNwidth,(unsigned short)16);
  MapScrollY->setPropertyV(WSNheight,(unsigned short)640);
  MapScrollY->setPropertyV(WSNanchorBottom,(unsigned short)16);
  MapScrollY->setPropertyV(WSNanchorTopFlag,(WSCbool)1);
  MapScrollY->setPropertyV(WSNanchorBottomFlag,(WSCbool)1);
  MapScrollY->setPropertyV(WSNanchorRightFlag,(WSCbool)1);
    extern void MapScrollYDraw(WSCbase*);
    MapScrollY->addProcedureV("MapScrollYDraw","MapScrollYDraw",MapScrollYDraw,2);
    extern void MapScrollYValCh(WSCbase*);
    MapScrollY->addProcedureV("MapScrollYValCh","MapScrollYValCh",MapScrollYValCh,3);

  MapScrollX = new  WSCvscrBar(MapWin,"MapScrollX");
      MapScrollX->initialize();
  MapScrollX->setPropertyV(WSNvalue,(unsigned long)640);
  MapScrollX->setPropertyV(WSNname,"MapScrollX");
  MapScrollX->setPropertyV(WSNvis,(WSCbool)1);
  MapScrollX->setPropertyV(WSNy,(short)640);
  MapScrollX->setPropertyV(WSNwidth,(unsigned short)640);
  MapScrollX->setPropertyV(WSNheight,(unsigned short)16);
  MapScrollX->setPropertyV(WSNanchorRight,(unsigned short)16);
  MapScrollX->setPropertyV(WSNanchorBottomFlag,(WSCbool)1);
  MapScrollX->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
  MapScrollX->setPropertyV(WSNanchorRightFlag,(WSCbool)1);
    extern void MapScrollXDraw(WSCbase*);
    MapScrollX->addProcedureV("MapScrollXDraw","MapScrollXDraw",MapScrollXDraw,2);
    extern void MapScrollXValCh(WSCbase*);
    MapScrollX->addProcedureV("MapScrollXValCh","MapScrollXValCh",MapScrollXValCh,3);

  MapForm = new  WSCform(MapWin,"MapForm");
      MapForm->initialize();
  MapForm->setPropertyV(WSNname,"MapForm");
  MapForm->setPropertyV(WSNx,(short)0);
  MapForm->setPropertyV(WSNy,(short)0);
  MapForm->setPropertyV(WSNwidth,(unsigned short)640);
  MapForm->setPropertyV(WSNheight,(unsigned short)640);
  MapForm->setPropertyV(WSNbackPixmap,"/home/dud/gimp/lnl/lnl/error/floor.png");
  MapForm->setPropertyV(WSNvis,(WSCbool)1);
  MapForm->setPropertyV(WSNanchorBottom,(unsigned short)16);
  MapForm->setPropertyV(WSNanchorRight,(unsigned short)16);
  MapForm->setPropertyV(WSNanchorTopFlag,(WSCbool)1);
  MapForm->setPropertyV(WSNanchorBottomFlag,(WSCbool)1);
  MapForm->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
  MapForm->setPropertyV(WSNanchorRightFlag,(WSCbool)1);
    extern void MapFormDraw(WSCbase*);
    MapForm->addProcedureV("MapFormDraw","MapFormDraw",MapFormDraw,9);
    extern void MapFormInit(WSCbase*);
    MapForm->addProcedureV("MapFormInit","MapFormInit",MapFormInit,0);
    extern void MapFormMouseMove(WSCbase*);
    MapForm->addProcedureV("MapFormMouseMove","MapFormMouseMove",MapFormMouseMove,15);
    extern void MapFormMousePress(WSCbase*);
    MapForm->addProcedureV("MapFormMousePress","MapFormMousePress",MapFormMousePress,13);
    extern void MapFormMouseRellease(WSCbase*);
    MapForm->addProcedureV("MapFormMouseRellease","MapFormMouseRellease",MapFormMouseRellease,14);
    extern void MapFormResize(WSCbase*);
    MapForm->addProcedureV("MapFormResize","MapFormResize",MapFormResize,10);

  MenuWin = new  WSCwindow(MapForm,"MenuWin");
      MenuWin->initialize();
  MenuWin->setPropertyV(WSNname,"MenuWin");
  MenuWin->setPropertyV(WSNtitleString,"Menu");
  MenuWin->setPropertyV(WSNwidth,(unsigned short)480);
  MenuWin->setPropertyV(WSNheight,(unsigned short)480);
  MenuWin->setPropertyV(WSNshadowThickness,(unsigned char)2);
    extern void MenuWinInit(WSCbase*);
    MenuWin->addProcedureV("MenuWinInit","MenuWinInit",MenuWinInit,0);

  MenuBtnPrevPage = new  WSCvbtn(MenuWin,"MenuBtnPrevPage");
      MenuBtnPrevPage->initialize();
  MenuBtnPrevPage->setPropertyV(WSNlabelString,"<<");
  MenuBtnPrevPage->setPropertyV(WSNname,"MenuBtnPrevPage");
  MenuBtnPrevPage->setPropertyV(WSNvis,(WSCbool)1);
  MenuBtnPrevPage->setPropertyV(WSNx,(short)4);
  MenuBtnPrevPage->setPropertyV(WSNy,(short)4);
  MenuBtnPrevPage->setPropertyV(WSNwidth,(unsigned short)50);
  MenuBtnPrevPage->setPropertyV(WSNheight,(unsigned short)24);
  MenuBtnPrevPage->setPropertyV(WSNanchorTop,(unsigned short)4);
  MenuBtnPrevPage->setPropertyV(WSNanchorLeft,(unsigned short)4);
  MenuBtnPrevPage->setPropertyV(WSNanchorTopFlag,(WSCbool)1);
  MenuBtnPrevPage->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
    extern void MenuBtnPrevPageActivate(WSCbase*);
    MenuBtnPrevPage->addProcedureV("MenuBtnPrevPageActivate","MenuBtnPrevPageActivate",MenuBtnPrevPageActivate,2);

  MenuBtnNextPage = new  WSCvbtn(MenuWin,"MenuBtnNextPage");
      MenuBtnNextPage->initialize();
  MenuBtnNextPage->setPropertyV(WSNlabelString,">>");
  MenuBtnNextPage->setPropertyV(WSNname,"MenuBtnNextPage");
  MenuBtnNextPage->setPropertyV(WSNvis,(WSCbool)1);
  MenuBtnNextPage->setPropertyV(WSNx,(short)112);
  MenuBtnNextPage->setPropertyV(WSNy,(short)4);
  MenuBtnNextPage->setPropertyV(WSNwidth,(unsigned short)50);
  MenuBtnNextPage->setPropertyV(WSNheight,(unsigned short)24);
  MenuBtnNextPage->setPropertyV(WSNanchorTop,(unsigned short)4);
  MenuBtnNextPage->setPropertyV(WSNanchorLeft,(unsigned short)112);
  MenuBtnNextPage->setPropertyV(WSNanchorTopFlag,(WSCbool)1);
  MenuBtnNextPage->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
    extern void MenuBtnNextPageActivate(WSCbase*);
    MenuBtnNextPage->addProcedureV("MenuBtnNextPageActivate","MenuBtnNextPageActivate",MenuBtnNextPageActivate,2);

  MenuBtnCancel = new  WSCvbtn(MenuWin,"MenuBtnCancel");
      MenuBtnCancel->initialize();
  MenuBtnCancel->setPropertyV(WSNlabelString,"Cancel");
  MenuBtnCancel->setPropertyV(WSNname,"MenuBtnCancel");
  MenuBtnCancel->setPropertyV(WSNvis,(WSCbool)1);
  MenuBtnCancel->setPropertyV(WSNx,(short)166);
  MenuBtnCancel->setPropertyV(WSNy,(short)4);
  MenuBtnCancel->setPropertyV(WSNheight,(unsigned short)24);
  MenuBtnCancel->setPropertyV(WSNanchorTop,(unsigned short)4);
  MenuBtnCancel->setPropertyV(WSNanchorLeft,(unsigned short)166);
  MenuBtnCancel->setPropertyV(WSNanchorTopFlag,(WSCbool)1);
  MenuBtnCancel->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
    extern void MenuBtnCancelActivate(WSCbase*);
    MenuBtnCancel->addProcedureV("MenuBtnCancelActivate","MenuBtnCancelActivate",MenuBtnCancelActivate,2);

  MenuLabelPage = new  WSCvlabel(MenuWin,"MenuLabelPage");
      MenuLabelPage->initialize();
  MenuLabelPage->setPropertyV(WSNlabelString,"/");
  MenuLabelPage->setPropertyV(WSNname,"MenuLabelPage");
  MenuLabelPage->setPropertyV(WSNvis,(WSCbool)1);
  MenuLabelPage->setPropertyV(WSNx,(short)58);
  MenuLabelPage->setPropertyV(WSNy,(short)4);
  MenuLabelPage->setPropertyV(WSNwidth,(unsigned short)50);
  MenuLabelPage->setPropertyV(WSNheight,(unsigned short)24);
  MenuLabelPage->setPropertyV(WSNanchorTop,(unsigned short)4);
  MenuLabelPage->setPropertyV(WSNanchorLeft,(unsigned short)58);
  MenuLabelPage->setPropertyV(WSNanchorTopFlag,(WSCbool)1);
  MenuLabelPage->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);

  StatWin = new  WSCwindow(MapForm,"StatWin");
      StatWin->initialize();
  StatWin->setPropertyV(WSNname,"StatWin");
  StatWin->setPropertyV(WSNtitleString,"Status");
  StatWin->setPropertyV(WSNx,(short)100);
  StatWin->setPropertyV(WSNy,(short)100);
  StatWin->setPropertyV(WSNwidth,(unsigned short)330);
  StatWin->setPropertyV(WSNheight,(unsigned short)576);
  StatWin->setPropertyV(WSNshadowThickness,(unsigned char)2);
  StatWin->setPropertyV(WSNvis,(WSCbool)1);
    extern void StatWinResize(WSCbase*);
    StatWin->addProcedureV("StatWinResize","StatWinResize",StatWinResize,10);

  StatWinDrawArea = new  WSCvdrawingArea(StatWin,"StatWinDrawArea");
      StatWinDrawArea->initialize();
  StatWinDrawArea->setPropertyV(WSNname,"StatWinDrawArea");
  StatWinDrawArea->setPropertyV(WSNvis,(WSCbool)1);
  StatWinDrawArea->setPropertyV(WSNwidth,(unsigned short)330);
  StatWinDrawArea->setPropertyV(WSNheight,(unsigned short)576);
  StatWinDrawArea->setPropertyV(WSNanchorTopFlag,(WSCbool)1);
  StatWinDrawArea->setPropertyV(WSNanchorBottomFlag,(WSCbool)1);
  StatWinDrawArea->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
  StatWinDrawArea->setPropertyV(WSNanchorRightFlag,(WSCbool)1);
    extern void StatWinDAInit(WSCbase*);
    StatWinDrawArea->addProcedureV("StatWinDAInit","StatWinDAInit",StatWinDAInit,0);
    extern void StatWinDADraw(WSCbase*);
    StatWinDrawArea->addProcedureV("StatWinDADraw","StatWinDADraw",StatWinDADraw,9);

  InpStrWin = new  WSCwindow(MapForm,"InpStrWin");
      InpStrWin->initialize();
  InpStrWin->setPropertyV(WSNname,"InpStrWin");
  InpStrWin->setPropertyV(WSNtitleString,"title1");
  InpStrWin->setPropertyV(WSNx,(short)100);
  InpStrWin->setPropertyV(WSNy,(short)100);
  InpStrWin->setPropertyV(WSNwidth,(unsigned short)413);
  InpStrWin->setPropertyV(WSNheight,(unsigned short)209);
  InpStrWin->setPropertyV(WSNshadowThickness,(unsigned char)2);
    extern void InpStrWinInit(WSCbase*);
    InpStrWin->addProcedureV("InpStrWinInit","InpStrWinInit",InpStrWinInit,0);

  InpStrTtl = new  WSCvlabel(InpStrWin,"InpStrTtl");
      InpStrTtl->initialize();
  InpStrTtl->setPropertyV(WSNname,"InpStrTtl");
  InpStrTtl->setPropertyV(WSNvis,(WSCbool)1);
  InpStrTtl->setPropertyV(WSNy,(short)16);
  InpStrTtl->setPropertyV(WSNwidth,(unsigned short)413);
  InpStrTtl->setPropertyV(WSNheight,(unsigned short)32);
  InpStrTtl->setPropertyV(WSNanchorTop,(unsigned short)16);
  InpStrTtl->setPropertyV(WSNanchorTopFlag,(WSCbool)1);
  InpStrTtl->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
  InpStrTtl->setPropertyV(WSNanchorRightFlag,(WSCbool)1);

  InpStrField = new  WSCvifield(InpStrWin,"InpStrField");
      InpStrField->initialize();
  InpStrField->setPropertyV(WSNname,"InpStrField");
  InpStrField->setPropertyV(WSNvis,(WSCbool)1);
  InpStrField->setPropertyV(WSNy,(short)48);
  InpStrField->setPropertyV(WSNwidth,(unsigned short)413);
  InpStrField->setPropertyV(WSNanchorTop,(unsigned short)48);
  InpStrField->setPropertyV(WSNanchorTopFlag,(WSCbool)1);
  InpStrField->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
  InpStrField->setPropertyV(WSNanchorRightFlag,(WSCbool)1);

  InpStrCancel = new  WSCvbtn(InpStrWin,"InpStrCancel");
      InpStrCancel->initialize();
  InpStrCancel->setPropertyV(WSNlabelString,"Cancel");
  InpStrCancel->setPropertyV(WSNname,"InpStrCancel");
  InpStrCancel->setPropertyV(WSNvis,(WSCbool)1);
  InpStrCancel->setPropertyV(WSNx,(short)205);
  InpStrCancel->setPropertyV(WSNy,(short)181);
  InpStrCancel->setPropertyV(WSNheight,(unsigned short)24);
  InpStrCancel->setPropertyV(WSNanchorBottom,(unsigned short)4);
  InpStrCancel->setPropertyV(WSNanchorRight,(unsigned short)108);
  InpStrCancel->setPropertyV(WSNanchorBottomFlag,(WSCbool)1);
  InpStrCancel->setPropertyV(WSNanchorRightFlag,(WSCbool)1);

  InpStrOk = new  WSCvbtn(InpStrWin,"InpStrOk");
      InpStrOk->initialize();
  InpStrOk->setPropertyV(WSNlabelString,"OK");
  InpStrOk->setPropertyV(WSNname,"InpStrOk");
  InpStrOk->setPropertyV(WSNvis,(WSCbool)1);
  InpStrOk->setPropertyV(WSNx,(short)309);
  InpStrOk->setPropertyV(WSNy,(short)181);
  InpStrOk->setPropertyV(WSNheight,(unsigned short)24);
  InpStrOk->setPropertyV(WSNanchorBottom,(unsigned short)4);
  InpStrOk->setPropertyV(WSNanchorRight,(unsigned short)4);
  InpStrOk->setPropertyV(WSNanchorBottomFlag,(WSCbool)1);
  InpStrOk->setPropertyV(WSNanchorRightFlag,(WSCbool)1);

   return MapWin;
}

//--- end of src ---//
