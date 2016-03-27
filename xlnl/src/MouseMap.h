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
* $Id: MouseMap.h,v 1.13 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef MOUSE_MAP_H
#define MOUSE_MAP_H	1

#ifdef D_GTK
#include <gtk/gtk.h>
#endif // D_GTK

#ifdef D_MFC
#include "xlnl-dows/stdafx.h"
#endif // D_MFC

#include "MouseMotion.h"

#define PRESS_TIMER_FRAME_RATE	30

void initMouseMotionFunc();
void funcMotionPoint(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionDragL(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionLeftR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionRightR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionUpR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionDownR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionClick(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionDoubleClick(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionClickLR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionPress(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void funcMotionRelease(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
void beginPressTimer( MouseMotion::MouseButtonN n );
void endPressTimer( MouseMotion::MouseButtonN n );
#ifdef D_GTK
gint callBackPressTimerGtk( gpointer data );
#endif // D_GTK
void callBackPressTimer( void );
void funcMotionScroll(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
);
bool callFuncKey( long fn, bool flagCheckClear = false );

#endif /* MOUSE_MAP_H */
