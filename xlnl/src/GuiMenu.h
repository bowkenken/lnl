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
* $Id: GuiMenu.h,v 1.28 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_MENU_H
#define GUI_MENU_H	1

////////////////////////////////////////////////////////////////
// GUI �ǥ�˥塼
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

// �ץ饤�١��ȡ����С��ѿ�
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

// �ѥ֥�å������С��ѿ�
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

// �ѥ֥�å������С��ؿ�
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

// �ץ饤�١��ȡ����С��ؿ�
private:
	void newWin();
};

#endif /* GUI_MENU_H */
