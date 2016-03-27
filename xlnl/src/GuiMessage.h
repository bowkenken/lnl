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
* $Id: GuiMessage.h,v 1.28 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_MESSAGE_H
#define GUI_MESSAGE_H	1

////////////////////////////////////////////////////////////////
// ��å�������������ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GtkWSCstring.h"
#endif // D_GTK

#ifdef D_IPHONE
# include "IPhoneWSCstring.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////

class GuiMessage {

	//////// �ץ饤�١��ȡ����С��ѿ� ////////
private:

	bool flagMore;

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mMessageDrawingArea;
	GtkWidget *mMessageHScrollBar;
	GtkWidget *mMessageVScrollBar;
	GtkObject *mMessageHScrollBarAdjustment;
	GtkObject *mMessageVScrollBarAdjustment;

	GdkGC *mFgGc;
	GdkGC *mBgGc;
	GtkStyle *mStyle;
#endif // D_GTK

#ifdef D_MFC
	CClientDC *pDc;
#endif // D_MFC

	//////// �ѥ֥�å������С��ѿ� ////////
public:

	// �Դֳ�
	static const long LINE_INTERVAL = 1;
	long mLsMessageDrawBeginN;
	long mLsMessageDrawN;

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mMessageWin;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mMessageWin;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *mMessageWin;
#endif // D_IPHONE

#ifdef D_MFC
	class CMessageWnd *mMessageWin;
#endif // D_MFC

	//////// �ѥ֥�å������С��ؿ� ////////
public:

	GuiMessage();
	~GuiMessage();

	void init();
	void destroy();

	void setFlagMore( bool flag );

	void redraw();
	void draw( bool flagRedraw );
	void wipe();
	void drawScrollBar();

	void hScroll( long n );
	void vScroll( long n );

	//////// �ץ饤�١��ȡ����С��ؿ� ////////
private:

	void newWin();
};

#endif /* GUI_MESSAGE_H */
