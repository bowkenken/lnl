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
* $Id: DemoEnding.h,v 1.12 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_ENDING_H
#define DEMO_ENDING_H	1

////////////////////////////////////////////////////////////////
// エンディング・デモ
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
	// ランダムに選ばれた画像のファイル番号
	long nRandmSel;
	// 画像のファイル数
	long nMaxFile;
	// 画像
	Pcg pcgEpilogue;
	Pcg pcgSpace;

	long frame;
	time_t waitTime;
	bool flagSkipScene;

	// アニメ用座標
	long len;
	long x_dot, y_dot;
	long baseX[EPILOGUE_LINE_MAX_N];
	long x[EPILOGUE_LINE_MAX_N][EPILOGUE_MAX_LEN];
	long y[EPILOGUE_LINE_MAX_N][EPILOGUE_MAX_LEN];

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
