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
* $Id: SelMbrGraph.h,v 1.8 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef SEL_MBR_GRAPH_H
#define SEL_MBR_GRAPH_H	1

////////////////////////////////////////////////////////////////
// メンバーのグラフィック・パターンを選択
////////////////////////////////////////////////////////////////

#include "misc.h"
#include "party.h"
#include "scene.h"
#include "scene-prot.h"

#include "PcgDun.h"

#ifdef D_WS
# include <WSCstring.h>
#endif //D_WS

#ifdef D_GTK
# include "GtkWSCstring.h"
#endif //D_GTK

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif //D_MFC

////////////////////////////////////////////////////////////////

class SelMbrGraph {

private:
	static const long nBaseColorR = 0xdddd;
	static const long nBaseColorG = 0xdddd;
	static const long nBaseColorB = 0xdddd;

	static const long nSelColorR = 0x0000;
	static const long nSelColorG = 0xdddd;
	static const long nSelColorB = 0xdddd;

	static const long nHighColorR = 0xffff;
	static const long nHighColorG = 0xffff;
	static const long nHighColorB = 0xffff;

	static const long nLowColorR = 0xbbbb;
	static const long nLowColorG = 0xbbbb;
	static const long nLowColorB = 0xbbbb;

	static const long nSelBorderW = 3;
	static const long nSelBorderH = 3;

	// 選択中のメンバー
	mbr_t *pMbr;

	// パターン・リストの先頭
	Pcg *pPtnHead;
	// パターンの最大数
	long nPtnMaxN;
	// 選択中のパターン・インデックス
	long nPtnSelN;

	// 切り替える前のシーンのバッカップ
	scene_n_t nPreScene;
	// 切り替える前のマップ表示座標
	long nPreMapX;
	long nPreMapY;

	// パターンの表示サイズ
	long nSizeX, nSizeY;
	long nSizeMaxX, nSizeMaxY;

	// パターン名のフォント
#ifdef D_GTK
	GdkFont *font;
#endif // D_GTK

public:
	SelMbrGraph();
	~SelMbrGraph();

	bool exec( mbr_t *mbr );
	long sel( long sx, long sy );
	void ok();
	void cancel();

	void redraw();
	void draw();

private:
	void close();

	void drawAllChr();
	void drawChr(
		long x, long y, long w, long h,
		Pcg *p, bool flagSel );
	void flush();
};

#endif /* SEL_MBR_GRAPH_H */
