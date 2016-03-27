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
* $Id: DemoCutIn.h,v 1.6 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_CUT_IN_H
#define DEMO_CUT_IN_H

////////////////////////////////////////////////////////////////
// カットイン・デモ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include "GtkWSCstring.h"
#endif /* D_GTK */

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif // D_MFC

#include "Pcg.h"

////////////////////////////////////////////////////////////////

class DemoCutIn {
public:

private:
	// ランダムに選ばれたカットイン画像のファイル番号
	long nFileSelN;
	// カットイン画像のファイル数
	long nFileMaxN;
	// カットインの画像
	Pcg pcg;

	// 描画位置
	// 左(上)端が -100%
	// 中心が 0%
	// 右(下)端が +100%
	rate_t rateBgnX;
	rate_t rateBgnY;
	rate_t rateEndX;
	rate_t rateEndY;

public:
	DemoCutIn();
	~DemoCutIn();
	void init( WSCstring dirName );

	void setPos( rate_t bx, rate_t by, rate_t ex, rate_t ey );

	bool drawCutIn( long frame, long maxFrame );
	bool drawCutOut( long frame, long maxFrame );
	bool draw( long frame, long maxFrame, bool flagCutIn );

private:
};

#endif // DEMO_CUT_IN_H
