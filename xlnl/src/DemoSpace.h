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
* $Id: DemoSpace.h,v 1.15 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_SPACE_H
#define DEMO_SPACE_H	1

////////////////////////////////////////////////////////////////
// 宇宙デモ
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
	// ランダムに選ばれた画像のファイル番号
	long nRandmSel;
	// 画像のファイル数
	long nMaxFile;
	// 画像
	Pcg pcgSpace;
	Pcg pcgNebula;

	// 星の色

#ifdef D_GTK
	GdkColor colorTab[COLOR_TAB_MAX_N];
	gboolean colorResult[COLOR_TAB_MAX_N];
#endif // D_GTK

#ifdef D_MFC
	LPDIRECT3DTEXTURE9 texture[COLOR_TAB_MAX_N];
	WSDimage *img[COLOR_TAB_MAX_N];
#endif // D_MFC

	// 星の座標

	long zv;
	long x[GUI_STAR_MAX_N];
	long y[GUI_STAR_MAX_N];
	long z[GUI_STAR_MAX_N];
	long nx[NEBULA_MAX_N];
	long ny[NEBULA_MAX_N];
	long nz[NEBULA_MAX_N];

	// スタッフ・ロール

	long staffRollY;
	long nStaffRollMaxLen;

#ifdef D_MFC
	long staffRollIdx;
#endif // D_MFC

#ifdef D_GTK
	// フォントのスタイル
	GtkStyle *pStyle;
#endif // D_GTK
	
#ifdef D_MAC
	// フォントのスタイル
//@@@
	void *pStyle;
#endif // D_MAC
	
#ifdef D_IPHONE
	// フォントのスタイル
//@@@
	void *pStyle;
#endif // D_IPHONE
	
#ifdef D_MFC
	// フォントのスタイル
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
