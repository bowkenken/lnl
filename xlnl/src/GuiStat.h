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
* $Id: GuiStat.h,v 1.20 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_STAT_H
#define GUI_STAT_H	1

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GtkWSCstring.h"
# include "party.h"
#endif // D_GTK

#ifdef D_MAC
# include "MacWSCstring.h"
#endif // D_MAC

#ifdef D_IPHONE
# include "IPhoneWSCstring.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////

class GuiStat {

// �ץ饤�١��ȡ����С��ѿ�
private:

	char mStrPreDunLev[40 + 1];
	char mStrPreTime[40 + 1];
	stat_mode_t mPreMode;

#ifdef D_GTK
	GtkWidget *vBox;
	GtkWidget *handleBox[MBR_MAX_N];
	GtkWidget *toolBar[MBR_MAX_N];
	GtkWidget *vBox2[MBR_MAX_N];
	GtkWidget *hBox1[MBR_MAX_N];
	GtkWidget *btnName[MBR_MAX_N];
	GtkWidget *labelAct[MBR_MAX_N];
	GtkWidget *btnStat[MBR_MAX_N];
	GtkWidget *labelHp[MBR_MAX_N];
	GtkWidget *labelMp[MBR_MAX_N];
	GtkWidget *hBoxHp[MBR_MAX_N];
	GtkWidget *hBoxMp[MBR_MAX_N];

	GtkWidget *vBoxMisc;
	GtkWidget *labelDunLev;
	GtkWidget *labelTime;
	GtkWidget *btnMode;

	GdkGC *mFgGcHp[MBR_MAX_N];
	GdkGC *mFgGcMp[MBR_MAX_N];
	GdkGC *mBgGcHp[MBR_MAX_N];
	GdkGC *mBgGcMp[MBR_MAX_N];
	GdkGC *mFgGcHpMp;
	GdkGC *mBgGcHpMp;

	GtkWidget *mDrawingAreaHp[MBR_MAX_N];
	GtkWidget *mDrawingAreaMp[MBR_MAX_N];
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

// �ѥ֥�å������С��ѿ�
public:

#ifdef D_GTK
	GtkWidget *mStatWin;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mStatWin;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *mStatWin;
#endif // D_IPHONE

#ifdef D_MFC
	CStatWnd *mStatWin;
#endif // D_MFC

// �ѥ֥�å������С��ؿ�
public:

	GuiStat();
	~GuiStat();

	void init();
	void destroy();

	void redraw( bool flagAdj = true, bool flagExpose = false );
	void draw( long n, bool flagExpose = false );
	void drawMisc();

	WSCstring getStatStr( mbr_t *mbr );

// �ץ饤�١��ȡ����С��ؿ�
private:

	void newWin();

	void drawHpMp( long n, bool flagHp );
#ifdef D_GTK
	void newWinMbr( mbr_t *mbr, GtkWidget *vBox );
#endif // D_GTK
};

#endif /* GUI_STAT_H */
