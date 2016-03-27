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
* $Id: GuiMenu.h,v 1.28 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_MENU_H
#define GUI_MENU_H	1

////////////////////////////////////////////////////////////////
// GUI 版メニュー
////////////////////////////////////////////////////////////////

#ifdef D_WS
# include <WSCvbtn.h>
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
#endif // D_GTK

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/MenuWnd.h"
#endif // D_MFC

#include "misc.h"
#include "menu.h"

////////////////////////////////////////////////////////////////

class GuiMenu {

public:

	enum {
		MOUSE_BUTTON_N_NULL,
		MOUSE_BUTTON_N_LEFT,
		MOUSE_BUTTON_N_MIDDLE,
		MOUSE_BUTTON_N_RIGHT,
		MOUSE_BUTTON_N_MAX_N,
	};

// プライベート・メンバー変数
private:

	char cAccelKey[MENU_MAX_N_PER_PAGE];
	long nSelN;

#ifdef D_WS
	WSCvbtn *aBtnMenu[MENU_MAX_N_PER_PAGE];
#endif // D_WS

#ifdef D_GTK
	GtkWidget *vBox;
	GtkWidget *aBtnMenu[MENU_MAX_N_PER_PAGE];
	GtkWidget *btnMenuPrevPage;
	GtkWidget *btnMenuNextPage;
	GtkWidget *btnMenuCancel;
	GtkWidget *btnMenuCancelAll;
	GtkWidget *labelMenuPageN;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *aBtnMenu[MENU_MAX_N_PER_PAGE];
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *aBtnMenu[MENU_MAX_N_PER_PAGE];
#endif // D_IPHONE

#ifdef D_MFC
	CButton *aBtnMenu[MENU_MAX_N_PER_PAGE + 1];
#endif // D_WS

// パブリック・メンバー変数
public:

#ifdef D_WS
	void *mMenuWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mMenuWin;
	long nClickedButton;
	gboolean bFlagEnter;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mMenuWin;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *mMenuWin;
#endif // D_IPHONE

#ifdef D_MFC
	CMenuWnd *mMenuWin;
#endif // D_WS

// パブリック・メンバー関数
public:

	GuiMenu();
	~GuiMenu();
	void init();
	void destroy();

	void draw( draw_menu_t *data );
	void wipe();

	void setMouseDfltMenu( long sel_n );

	void moveMenuCrsr( long nBtn );

	char getAccelKey( long n );
	long getSelN();

// プライベート・メンバー関数
private:
	void newWin();
};

#endif /* GUI_MENU_H */
