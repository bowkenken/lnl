/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ����ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�����
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�����ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ����Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: GlobalVar.cpp,v 1.39 2014/02/02 17:49:46 bowkenken Exp $
***************************************************************/

#include "GlobalVar.h"

#include "gmain-prot.h"

SelConf gSelConf;
check_memory_def( check_memory_GlobalVar_cpp_gSelConf )

CuiMouse gCuiMouse;
check_memory_def( check_memory_GlobalVar_cpp_gCuiMouse )
GuiMenu gGuiMenu;
check_memory_def( check_memory_GlobalVar_cpp_gGuiMenu )
GuiMessage gGuiMessage;
check_memory_def( check_memory_GlobalVar_cpp_gGuiMessage )
GuiStat gGuiStat;
check_memory_def( check_memory_GlobalVar_cpp_gGuiStat )
GuiNum gGuiNum;
check_memory_def( check_memory_GlobalVar_cpp_gGuiNum )
GuiInputString gGuiInpStr;
check_memory_def( check_memory_GlobalVar_cpp_gGuiInpStr )
GuiWords gGuiWords;
check_memory_def( check_memory_GlobalVar_cpp_gGuiWords )
GuiReplay gGuiReplay;
check_memory_def( check_memory_GlobalVar_cpp_gGuiReplay )
GuiClassEdit gGuiClassEdit;
check_memory_def( check_memory_GlobalVar_cpp_gGuiClassEdit )
GuiSkillEdit gGuiSkillEdit;
check_memory_def( check_memory_GlobalVar_cpp_gGuiSkillEdit )
GuiChrSheet gGuiChrSheet;
check_memory_def( check_memory_GlobalVar_cpp_gGuiChrSheet )
SelMbrGraph *gSelMbrGraph;
check_memory_def( check_memory_GlobalVar_cpp_gSelMbrGraph )
WinPos gWinPos[WIN_KIND_MAX_N];
check_memory_def( check_memory_GlobalVar_cpp_gWinPos )

PcgDun gPcgDun;
check_memory_def( check_memory_GlobalVar_cpp_gPcgDun )

GameMusic gMusic;
check_memory_def( check_memory_GlobalVar_cpp_gMusic )
GameSound gSound;
check_memory_def( check_memory_GlobalVar_cpp_gSound )
GameJoystick gJoystick;
check_memory_def( check_memory_GlobalVar_cpp_gJoystick )

Key gKey;
check_memory_def( check_memory_GlobalVar_cpp_gKey )

MouseMotion gMouseMotion;
check_memory_def( check_memory_GlobalVar_cpp_gMouseMotion )

long gMapDragBgnX, gMapDragBgnY;
check_memory_def( check_memory_GlobalVar_cpp_gMapDragBgnY )

long nCharWidth;
long nCharHeight;
long nMarginX;
long nMarginY;
check_memory_def( check_memory_GlobalVar_cpp_nMarginY )

#ifdef D_WS
WSCbase *gStatLabel[MBR_MAX_N][STAT_WIN_IDX_MAX_N];
#endif // D_WS

#ifdef D_GTK
GtkWidget *gMapWin;

GtkWidget *gMapButtonContExec;

GtkWidget *gMapDrawingArea;
GtkObject *gMapHScrollBarAdjustment;
GtkObject *gMapVScrollBarAdjustment;
GtkWidget *gMapHScrollBar;
GtkWidget *gMapVScrollBar;
#endif // D_GTK

#ifdef D_MAC
NSLock *gMainLock;
MacMain *gMacMain;
NSWindow *gMainWindow;
NSScrollView *gMainMapScrollView;
MacMapView *gMainMapView;
#endif // D_MAC

#ifdef D_IPHONE
NSLock *gMainLock;
UIWindow *gMainWindow;
MainNaviCon *gMainNaviCon;
MainMapWin *gMainMapWin;
#endif // D_IPHONE

#ifdef D_MFC
volatile bool gFlagInitMfcDone;
bool gFlagExit;
CDir3d g_Dir3d;
#endif // D_MFC

check_memory_def( check_memory_GlobalVar_cpp_Widgets )

////////////////////////////////////////////////////////////////
// GlobalVar.cpp �Υ��꡼�������å�
////////////////////////////////////////////////////////////////

void check_memory_GlobalVar_cpp()
{
	check_memory( check_memory_GlobalVar_cpp_gSelConf,
			"GlobalVar.cpp: gSelConf" );
	check_memory( check_memory_GlobalVar_cpp_gCuiMouse,
			"GlobalVar.cpp: gCuiMouse" );
	check_memory( check_memory_GlobalVar_cpp_gGuiMenu,
			"GlobalVar.cpp: gGuiMenu" );
	check_memory( check_memory_GlobalVar_cpp_gGuiMessage,
			"GlobalVar.cpp: gGuiMessage" );
	check_memory( check_memory_GlobalVar_cpp_gGuiStat,
			"GlobalVar.cpp: gGuiStat" );
	check_memory( check_memory_GlobalVar_cpp_gGuiNum,
			"GlobalVar.cpp: gGuiNum" );
	check_memory( check_memory_GlobalVar_cpp_gGuiInpStr,
			"GlobalVar.cpp: gGuiInpStr" );
	check_memory( check_memory_GlobalVar_cpp_gGuiWords,
			"GlobalVar.cpp: gGuiWords" );
	check_memory( check_memory_GlobalVar_cpp_gGuiReplay,
			"GlobalVar.cpp: gGuiReplay" );
	check_memory( check_memory_GlobalVar_cpp_gGuiClassEdit,
			"GlobalVar.cpp: gGuiClassEdit" );
	check_memory( check_memory_GlobalVar_cpp_gGuiSkillEdit,
			"GlobalVar.cpp: gGuiSkillEdit" );
	check_memory( check_memory_GlobalVar_cpp_gGuiChrSheet,
			"GlobalVar.cpp: gGuiChrSheet" );
	check_memory( check_memory_GlobalVar_cpp_gSelMbrGraph,
			"GlobalVar.cpp: gSelMbrGraph" );
	check_memory( check_memory_GlobalVar_cpp_gWinPos,
			"GlobalVar.cpp: gWinPos" );
	check_memory( check_memory_GlobalVar_cpp_gPcgDun,
			"GlobalVar.cpp: gPcgDun" );
	check_memory( check_memory_GlobalVar_cpp_gMusic,
			"GlobalVar.cpp: gMusic" );
	check_memory( check_memory_GlobalVar_cpp_gSound,
			"GlobalVar.cpp: gSound" );
	check_memory( check_memory_GlobalVar_cpp_gJoystick,
			"GlobalVar.cpp: gJoystick" );
	check_memory( check_memory_GlobalVar_cpp_gKey,
			"GlobalVar.cpp: gKey" );
	check_memory( check_memory_GlobalVar_cpp_gMouseMotion,
			"GlobalVar.cpp: gMouseMotion" );
	check_memory( check_memory_GlobalVar_cpp_gMapDragBgnY,
			"GlobalVar.cpp: gMapDragBgnY" );
	check_memory( check_memory_GlobalVar_cpp_nMarginY,
			"GlobalVar.cpp: nMarginY" );
	check_memory( check_memory_GlobalVar_cpp_Widgets,
			"GlobalVar.cpp: Widgets" );
}
