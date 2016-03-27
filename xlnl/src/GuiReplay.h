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
* $Id: GuiReplay.h,v 1.8 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_REPLAY_H
#define GUI_REPLAY_H

////////////////////////////////////////////////////////////////
// ��ץ쥤��������ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////

class GuiReplay {

private:
#ifdef D_GTK
	GtkWidget *mReplayTextScroll;
	GtkWidget *mReplayTextView;

	GtkWidget *mButtonTurn;
	GtkWidget *mButtonKey1;
	GtkWidget *mButtonKey10;
	GtkWidget *mButtonCont;
	GtkWidget *mButtonExit;
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

public:
#ifdef D_WS
	void *mReplayWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mReplayWin;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mReplayWin;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *mReplayWin;
#endif // D_IPHONE

#ifdef D_MFC
	class CReplayWnd *mReplayWin;
#endif // D_MFC

public:
	GuiReplay();
	~GuiReplay();
	void init();
	void destroy();

	void bgn();
	void end();

	void draw();
	void redraw();
	void wipe();

	void turnClicked();
	void key1Clicked();
	void key10Clicked();
	void contClicked();
	void exitClicked();

private:
	void newWin();
};

#endif // GUI_REPLAY_H
