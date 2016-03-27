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
* $Id: DemoTitle.h,v 1.12 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_TITLE_H
#define DEMO_TITLE_H	1

////////////////////////////////////////////////////////////////
// �����ȥ롦�ǥ�
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

class DemoTitle {
public:

private:
	// ����������Ф줿�����ȥ�����Υե������ֹ�
	long nTitleRandmSelN;
	// �����ȥ�����Υե������
	long nTitleN;
	// �����ȥ�β���
	Pcg pcgTitle;

	// ������̾�Υ��˥��Ѻ�ɸ
	long len;
	long w, h;
	long baseX, baseY;
	long mx[3][16], my[3][16];
	long x[3][16], y[3][16];

#ifdef D_GTK
	// �ե���ȤΥ�������
	GtkStyle *pTitleStyle;
#endif // D_GTK
	
#ifdef D_MAC
	// �ե���ȤΥ�������
	void *pTitleStyle;
#endif // D_MAC
	
#ifdef D_IPHONE
	// �ե���ȤΥ�������
	void *pTitleStyle;
#endif // D_IPHONE
	
#ifdef D_MFC
	// �ե���ȤΥ�������
	void *pTitleStyle;
	LOGFONT mTitleFontDesc;
	CFont *pTitleFont;

	CDir3dText mD3Title;
#endif // D_MFC

public:
	DemoTitle();
	~DemoTitle();
	void init();

	bool draw();

private:
	void initAnime();
	void drawTitle0( long frame );
	void drawTitle1( long frame );
	void drawTitle2( long frame );
	void drawTitle3( long frame );
	void drawTitle4( long frame );
	void drawTitle5( long frame );
	void drawTitle6( long frame );

	void drawTitleString();
	void drawTitleCharStd( long x, long y, char c );
	void drawTitleChar(
		long r, long g, long b,
		long x, long y, char c );
};

#endif // DEMO_TITLE_H
