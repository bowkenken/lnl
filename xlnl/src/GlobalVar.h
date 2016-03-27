/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* 本プログラムはフリー・ソフトウェアです。
* あなたは、 Free Software Foundation が公表した
*  GNU 一般公有使用許諾の「バージョン２」
* 或はそれ以降の各バージョンの中からいずれかを選択し、
* そのバージョンが定める条項に従って本プログラムを
* 再頒布または変更することができます。
* 
* 本プログラムは有用とは思いますが、頒布にあたっては、
* 市場性及び特定目的適合性についての暗黙の保証を含めて,
* いかなる保証も行ないません。
* 詳細については GNU 一般公有使用許諾書をお読みください。
* 
* あなたは、本プログラムと一緒に GNU 一般公有使用許諾書
* の写しを受け取っているはずです。そうでない場合は、
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* へ手紙を書いてください。
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
// GUI 関係のグローバル変数宣言
////////////////////////////////////////////////////////////////

// グラフィック設定の選択
extern SelConf gSelConf;

// CUI マウス
extern CuiMouse gCuiMouse;

// メニュー・ウィンドウ
extern GuiMenu gGuiMenu;

// メッセージ・ウィンドウ
extern GuiMessage gGuiMessage;

// ステータス・ウィンドウ
extern GuiStat gGuiStat;

// 数値入力ウィンドウ
extern GuiNum gGuiNum;

// 文字列入力・ウィンドウ
extern GuiInputString gGuiInpStr;

// 台詞ウィンドウ
extern GuiWords gGuiWords;

// リプレイ・ウィンドウ
extern GuiReplay gGuiReplay;

// クラス・エディタ・ウィンドウ
extern GuiClassEdit gGuiClassEdit;

// スキル・エディタ・ウィンドウ
extern GuiSkillEdit gGuiSkillEdit;

// キャラクタ・シート・ウィンドウ
extern GuiChrSheet gGuiChrSheet;

// メンバーのグラフィック・パターンを選択
extern SelMbrGraph *gSelMbrGraph;

// ウィンドウの座標
extern WinPos gWinPos[WIN_KIND_MAX_N];

// ダンジョンの全てのキャラクタ管理データ
extern PcgDun gPcgDun;

// BGM の管理
extern GameMusic gMusic;

// SE の管理
extern GameSound gSound;

// ジョイスティックの管理
extern GameJoystick gJoystick;

// キー入力管理データ
extern Key gKey;

// マウスのモーション入力の管理データ
extern MouseMotion gMouseMotion;

// マップ・ウィンドウのドラッグ開始座標
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

// ステータス・ウィンドウ
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
