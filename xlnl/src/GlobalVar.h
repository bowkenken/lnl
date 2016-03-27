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
* $Id: GlobalVar.h,v 1.44 2014/02/02 17:49:46 bowkenken Exp $
***************************************************************/

#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H	1

#ifdef D_WS
# include <WSCvlabel.h>
# include <WSCvdrawingArea.h>
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
# include <gdk-pixbuf/gdk-pixbuf.h>
#endif // D_GTK

#ifdef D_WS
typedef int gint;
typedef long glong;
typedef long GtkWidget;
typedef void *gpointer;
typedef long GdkEventExpose;
typedef long GtkAdjustment;
typedef long GtkButton;
#endif // D_WS

#include "party.h"
#include "draw.h"
#include "SelConf.h"
#include "CuiMouse.h"
#include "GuiMenu.h"
#include "GuiMessage.h"
#include "GuiStat.h"
#include "GuiNum.h"
#include "GuiInputString.h"
#include "GuiWords.h"
#include "GuiReplay.h"
#include "GuiClassEdit.h"
#include "GuiSkillEdit.h"
#include "GuiChrSheet.h"
#include "SelMbrGraph.h"
#include "WinPos.h"
#include "FileList.h"
#include "PcgDun.h"
#include "GameMusic.h"
#include "GameSound.h"
#include "GameJoystick.h"
#include "Key.h"
#include "MouseMotion.h"

#include "draw-prot.h"

#ifdef D_WS
# include "StatWinIdx.h"
#endif // D_WS

#ifdef D_GTK
# include "GuiStat.h"
#endif // D_GTK

#ifdef D_MAC
# import "xlnl_macAppDelegate.h"
# include "main-mac.h"
# include "GuiStat.h"
#endif // D_MAC

#ifdef D_IPHONE
# include "main-iphone.h"
# include "GuiStat.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "xlnl-dows/Dir3d.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////
// GUI �ط��Υ����Х��ѿ����
////////////////////////////////////////////////////////////////

// ����ե��å����������
extern SelConf gSelConf;

// CUI �ޥ���
extern CuiMouse gCuiMouse;

// ��˥塼��������ɥ�
extern GuiMenu gGuiMenu;

// ��å�������������ɥ�
extern GuiMessage gGuiMessage;

// ���ơ�������������ɥ�
extern GuiStat gGuiStat;

// �������ϥ�����ɥ�
extern GuiNum gGuiNum;

// ʸ�������ϡ�������ɥ�
extern GuiInputString gGuiInpStr;

// ��쥦����ɥ�
extern GuiWords gGuiWords;

// ��ץ쥤��������ɥ�
extern GuiReplay gGuiReplay;

// ���饹�����ǥ�����������ɥ�
extern GuiClassEdit gGuiClassEdit;

// �����롦���ǥ�����������ɥ�
extern GuiSkillEdit gGuiSkillEdit;

// ����饯���������ȡ�������ɥ�
extern GuiChrSheet gGuiChrSheet;

// ���С��Υ���ե��å����ѥ����������
extern SelMbrGraph *gSelMbrGraph;

// ������ɥ��κ�ɸ
extern WinPos gWinPos[WIN_KIND_MAX_N];

// ���󥸥������ƤΥ���饯�������ǡ���
extern PcgDun gPcgDun;

// BGM �δ���
extern GameMusic gMusic;

// SE �δ���
extern GameSound gSound;

// ���祤���ƥ��å��δ���
extern GameJoystick gJoystick;

// �������ϴ����ǡ���
extern Key gKey;

// �ޥ����Υ⡼��������Ϥδ����ǡ���
extern MouseMotion gMouseMotion;

// �ޥåס�������ɥ��Υɥ�å����Ϻ�ɸ
extern long gMapDragBgnX, gMapDragBgnY;

//
extern long nCharWidth;
extern long nCharHeight;
extern long nMarginX;
extern long nMarginY;

#ifdef D_WS
extern WSCbase *gStatLabel[MBR_MAX_N][STAT_WIN_IDX_MAX_N];
# endif // D_WS

#ifdef D_GTK
extern GtkWidget *gMapWin;

extern GtkWidget *gMapButtonContExec;

extern GtkWidget *gMapDrawingArea;
extern GtkObject *gMapHScrollBarAdjustment;
extern GtkObject *gMapVScrollBarAdjustment;
extern GtkWidget *gMapHScrollBar;
extern GtkWidget *gMapVScrollBar;

// ���ơ�������������ɥ�
extern GuiStat gGuiStat;
#endif // D_GTK

#ifdef D_MAC
extern NSLock *gMainLock;
extern MacMain *gMacMain;
extern NSWindow *gMainWindow;
extern NSScrollView *gMainMapScrollView;
extern MacMapView *gMainMapView;
#endif // D_MAC

#ifdef D_IPHONE
extern NSLock *gMainLock;
extern UIWindow *gMainWindow;
extern MainNaviCon *gMainNaviCon;
extern MainMapWin *gMainMapWin;
#endif // D_IPHONE

#ifdef D_MFC
extern volatile bool gFlagInitMfcDone;
extern bool gFlagExit;
extern CDir3d g_Dir3d;
#endif // D_MFC

void check_memory_GlobalVar_cpp();

#endif /* GLOBAL_VAR_H */
