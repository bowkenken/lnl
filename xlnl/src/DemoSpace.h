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
* $Id: DemoSpace.h,v 1.15 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_SPACE_H
#define DEMO_SPACE_H	1

////////////////////////////////////////////////////////////////
// ����ǥ�
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

#define	GUI_STAR_MAX_N	40960
#define	GUI_STAR_DFLT_N	4096
#define NEBULA_MAX_N	16

#ifdef D_GTK
# define	COLOR_TAB_MAX_N	16
#endif // D_GTK

#ifdef D_MFC
# define	COLOR_TAB_MAX_N	16
#endif // D_MFC

////////////////////////////////////////////////////////////////

class DemoSpace {
public:

private:
	// ����������Ф줿�����Υե������ֹ�
	long nRandmSel;
	// �����Υե������
	long nMaxFile;
	// ����
	Pcg pcgSpace;
	Pcg pcgNebula;

	// ���ο�

#ifdef D_GTK
	GdkColor colorTab[COLOR_TAB_MAX_N];
	gboolean colorResult[COLOR_TAB_MAX_N];
#endif // D_GTK

#ifdef D_MFC
	LPDIRECT3DTEXTURE9 texture[COLOR_TAB_MAX_N];
	WSDimage *img[COLOR_TAB_MAX_N];
#endif // D_MFC

	// ���κ�ɸ

	long zv;
	long x[GUI_STAR_MAX_N];
	long y[GUI_STAR_MAX_N];
	long z[GUI_STAR_MAX_N];
	long nx[NEBULA_MAX_N];
	long ny[NEBULA_MAX_N];
	long nz[NEBULA_MAX_N];

	// �����åա�����

	long staffRollY;
	long nStaffRollMaxLen;

#ifdef D_MFC
	long staffRollIdx;
#endif // D_MFC

#ifdef D_GTK
	// �ե���ȤΥ�������
	GtkStyle *pStyle;
#endif // D_GTK
	
#ifdef D_MAC
	// �ե���ȤΥ�������
//@@@
	void *pStyle;
#endif // D_MAC
	
#ifdef D_IPHONE
	// �ե���ȤΥ�������
//@@@
	void *pStyle;
#endif // D_IPHONE
	
#ifdef D_MFC
	// �ե���ȤΥ�������
	void *pStyle;
	LOGFONT mFontDesc;
	CFont *pFont;

	CDir3dText mD3;
#endif // D_MFC

public:
	DemoSpace();
	~DemoSpace();
	void init();

	bool draw( bool flagDrawStaffRoll );
	void addSpeedZ( long zav );

private:
	void initAnime();

	void move();

	void drawStar( long x, long y, long z );
	void drawNebula( Pcg *p, long x, long y, long z );

	void drawStaffRoll();
	void drawTheEnd();
	void drawStaffRollLine( long x, long y, const char *str );
	void drawCharStd( long x, long y, const char *str );
	void drawChar(
		long r, long g, long b,
		long x, long y, const char *str );

	long getStarN();
};

#endif // DEMO_SPACE_H
