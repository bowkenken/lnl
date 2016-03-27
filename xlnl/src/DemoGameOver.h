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
* $Id: DemoGameOver.h,v 1.7 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_GAME_OVER_H
#define DEMO_GAME_OVER_H	1

////////////////////////////////////////////////////////////////
// ゲーム・オーバー・デモ
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
	// ランダムに選ばれたゲーム・オーバー画像のファイル番号
	long nGameOverRandmSelN;
	// ゲーム・オーバー画像のファイル数
	long nGameOverN;
	// ゲーム・オーバーの画像
	Pcg pcgGameOver;

	long frame;
	time_t wait_time;

	// アニメ用座標
	long len;
	long w, h;
	long baseX, baseY;
	long mx[3][16], my[3][16];
	long x[3][16], y[3][16];

#ifdef D_GTK
	// フォントのスタイル
	GtkStyle *pGameOverStyle;
#endif // D_GTK
	
#ifdef D_MAC
	// フォントのスタイル
//@@@
	void *pGameOverStyle;
#endif // D_IPHONE
	
#ifdef D_IPHONE
	// フォントのスタイル
//@@@
	void *pGameOverStyle;
#endif // D_IPHONE
	
#ifdef D_MFC
	// フォントのスタイル
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
