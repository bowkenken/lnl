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
* $Id: DemoGameOver.h,v 1.7 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_GAME_OVER_H
#define DEMO_GAME_OVER_H	1

////////////////////////////////////////////////////////////////
// �����ࡦ�����С����ǥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/Dir3dText.h"
#endif // D_MFC

#include "Pcg.h"

////////////////////////////////////////////////////////////////

class DemoGameOver {
public:

private:
	// ����������Ф줿�����ࡦ�����С������Υե������ֹ�
	long nGameOverRandmSelN;
	// �����ࡦ�����С������Υե������
	long nGameOverN;
	// �����ࡦ�����С��β���
	Pcg pcgGameOver;

	long frame;
	time_t wait_time;

	// ���˥��Ѻ�ɸ
	long len;
	long w, h;
	long baseX, baseY;
	long mx[3][16], my[3][16];
	long x[3][16], y[3][16];

#ifdef D_GTK
	// �ե���ȤΥ�������
	GtkStyle *pGameOverStyle;
#endif // D_GTK
	
#ifdef D_MAC
	// �ե���ȤΥ�������
//@@@
	void *pGameOverStyle;
#endif // D_IPHONE
	
#ifdef D_IPHONE
	// �ե���ȤΥ�������
//@@@
	void *pGameOverStyle;
#endif // D_IPHONE
	
#ifdef D_MFC
	// �ե���ȤΥ�������
	void *pGameOverStyle;
	LOGFONT mGameOverFontDesc;
	CFont *pGameOverFont;

	CDir3dText mD3GameOver;
#endif // D_MFC

public:
	DemoGameOver();
	~DemoGameOver();
	void init();

	bool draw();

private:
	void initAnime();

	bool drawWait();
	bool drawEnd();

	void drawGameOver( long frame );
	void drawGameOverString();
	void drawGameOverCharStd( long x, long y, char c );
	void drawGameOverChar(
		long r, long g, long b,
		long x, long y, char c );
};

#endif // DEMO_GAME_OVER_H
