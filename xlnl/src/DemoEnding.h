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
* $Id: DemoEnding.h,v 1.12 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_ENDING_H
#define DEMO_ENDING_H	1

////////////////////////////////////////////////////////////////
// ����ǥ��󥰡��ǥ�
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
#include "DemoSpace.h"

////////////////////////////////////////////////////////////////

#define	EPILOGUE_MAX_LEN	40
#define	EPILOGUE_LINE_MAX_N	16

////////////////////////////////////////////////////////////////

class DemoEnding {
public:
	DemoSpace space;

private:
	// ����������Ф줿�����Υե������ֹ�
	long nRandmSel;
	// �����Υե������
	long nMaxFile;
	// ����
	Pcg pcgEpilogue;
	Pcg pcgSpace;

	long frame;
	time_t waitTime;
	bool flagSkipScene;

	// ���˥��Ѻ�ɸ
	long len;
	long x_dot, y_dot;
	long baseX[EPILOGUE_LINE_MAX_N];
	long x[EPILOGUE_LINE_MAX_N][EPILOGUE_MAX_LEN];
	long y[EPILOGUE_LINE_MAX_N][EPILOGUE_MAX_LEN];

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
	DemoEnding();
	~DemoEnding();
	void init();

	bool draw();

	void skipScene();

private:
	void initAnime();

	bool drawEpilogue();
	bool drawSpace( bool flagDrawTheEnd );
	void drawEpilogueStory( long frame );

	void drawString();
	void drawCharStd( long x, long y, const char *str );
	void drawChar(
		long r, long g, long b,
		long x, long y, const char *str );
};

#endif // DEMO_ENDING_H
