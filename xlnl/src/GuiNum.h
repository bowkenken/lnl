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
* $Id: GuiNum.h,v 1.22 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_NUM_H
#define GUI_NUM_H	1

////////////////////////////////////////////////////////////////
// �������ϥ�����ɥ�
////////////////////////////////////////////////////////////////

#define GUI_NUM_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define GUI_NUM_BUTTON_MAX_N	20

////////////////////////////////////////////////////////////////

class GuiNum {

	//////// �ץ饤�١��ȡ����С��ѿ� ////////
private:

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkObject *mHscaleAdjustment;
	GtkWidget *mHscale;

	GtkObject *mNumAdjustment;
	GtkWidget *mNumSpin;

	GtkWidget *mArrowUp[GUI_NUM_BUTTON_MAX_N];
	GtkWidget *mArrowDown[GUI_NUM_BUTTON_MAX_N];
	GtkWidget *mButtonUp[GUI_NUM_BUTTON_MAX_N];
	GtkWidget *mButtonDown[GUI_NUM_BUTTON_MAX_N];
	GtkWidget *mButtonLabel[GUI_NUM_BUTTON_MAX_N];

	GtkWidget *mButtonMin;
	GtkWidget *mButtonClear;
	GtkWidget *mButtonMax;
	GtkWidget *mButtonOk;
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

	//////// �ѥ֥�å������С��ѿ� ////////
public:

#ifdef D_WS
	void *mNumWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mNumWin;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mNumWin;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *mNumWin;
#endif // D_IPHONE

#ifdef D_MFC
	class CInputNumDlg *mNumWin;
#endif // D_MFC

	bool mFlagInitDone;

	volatile long *mPN;
	long mOrg;
	long mMin;
	long mMax;
	long mFigure;

	//////// �ѥ֥�å������С��ؿ� ////////
public:

	GuiNum();
	~GuiNum();
	void init();
	void destroy();

	void draw( volatile long *n, long min, long max, long figure );
	void redraw();
	void wipe();

	void valueChanged( long n );
	void up_down_num_label( long n, long d );
	char up_down_num_char( char c, long d );

	void cvUpDownToN();
	void cvUpDownFromN();
	void okClicked( menu_num_t n );

	//////// �ץ饤�١��ȡ����С��ؿ� ////////
private:

	void newWin();
};

#endif /* GUI_NUM_H */
