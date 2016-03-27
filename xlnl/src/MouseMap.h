/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* 本プログラムはフリー・ソフトウェアです。
* あなたは、 Free Software Foundation が公表した
*  GNU 一般公有使用許諾の「バージョン２」
* 或はそれ以降の各バージョンの中からいずれかを選択し、
* そのバージョンが定める条項に従って本プログラムを
* 再頒布または変更することができます。
* 
* 本プログラムは有用とは思いますが、頒布にあたっては、
* 市場性及び特定目的適合性についての暗黙の保証を含めて,
* いかなる保証も行ないません。
* 詳細については GNU 一般公有使用許諾書をお読みください。
* 
* あなたは、本プログラムと一緒に GNU 一般公有使用許諾書
* の写しを受け取っているはずです。そうでない場合は、
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* へ手紙を書いてください。
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
