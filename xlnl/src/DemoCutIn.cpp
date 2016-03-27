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
* $Id: DemoCutIn.cpp,v 1.10 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// カットイン・デモ
////////////////////////////////////////////////////////////////

#define DEMO_CUT_IN_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

// カットイン画像のディレクトリ
#define STR_CUT_IN_DIR_NAME	"cut_in/"

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

DemoCutIn::DemoCutIn()
{
	nFileSelN = 0;
	nFileMaxN = 0;

	rateBgnX = (rate_t)0;
	rateBgnY = (rate_t)0;
	rateEndX = (rate_t)0;
	rateEndY = (rate_t)0;
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

DemoCutIn::~DemoCutIn()
{
}

////////////////////////////////////////////////////////////////
// 初期化
// WSCstring dirName : 画像のディレクトリ名
////////////////////////////////////////////////////////////////

void DemoCutIn::init( WSCstring dirName )
{
	// カットイン画像の検索を設定

	WSCstring dir = STR_DEFAULT_GRAPH_DIR_NAME;
	WSCstring ext = STR_GRAPH_FILE_EXT;
	WSCstring pcgPath = FileList::jointDir(
			STR_CUT_IN_DIR_NAME, dirName );

	FileList::setStrDirSelGraph( dir );
	FileList ls;

	// カットイン画像を検索

	{
		nFileMaxN = 0;

		ls.reset( pcgPath, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
		}

		nFileMaxN = j;
	}

	// カットイン画像をランダムに選択

	if( nFileMaxN > 0 )
		nFileSelN = gui_randm( nFileMaxN );
	else
		nFileSelN = -1;

	// カットイン画像を読み込む

	if( nFileSelN > -1 ){
		ls.reset( pcgPath, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
			if( j == nFileSelN ){
				pcg.init( path );
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////
// カットイン開始／終了座標を設定
// rate_t bx : 開始 X 座標の率
// rate_t by : 開始 Y 座標の率
// rate_t ex : 終了 X 座標の率
// rate_t ey : 終了 Y 座標の率
////////////////////////////////////////////////////////////////

void DemoCutIn::setPos( rate_t bx, rate_t by, rate_t ex, rate_t ey )
{
	rateBgnX = bx;
	rateBgnY = by;
	rateEndX = ex;
	rateEndY = ey;
}

////////////////////////////////////////////////////////////////
// カットインの描画
// long frame : 現在のフレーム
// long maxFrame : 終了フレーム
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool DemoCutIn::drawCutIn( long frame, long maxFrame )
{
	return draw( frame, maxFrame, true );
}

////////////////////////////////////////////////////////////////
// カットアウトの描画
// long frame : 現在のフレーム
// long maxFrame : 終了フレーム
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool DemoCutIn::drawCutOut( long frame, long maxFrame )
{
	return draw( frame, maxFrame, false );
}

////////////////////////////////////////////////////////////////
// カットイン／アウトの描画
// long frame : 現在のフレーム
// long maxFrame : 終了フレーム
// return : カットイン／アウトが終了したか?
////////////////////////////////////////////////////////////////

bool DemoCutIn::draw( long frame, long maxFrame, bool flagCutIn )
{
	bool flagDone = false;

	if( g_flg_skip_demo_cut_in )
		return true;

	if( frame < 0 )
		frame = 0;
	if( frame > maxFrame ){
		frame = maxFrame;
		flagDone = true;
	}

	if( !flagCutIn )
		frame = maxFrame - frame;

	long x = gPcgDun.getScrollBarX();
	long y = gPcgDun.getScrollBarY();
	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();

	long pcgW = pcg.getWidth();
	long pcgH = pcg.getHeight();
	rate_t rateX = ((rateEndX - rateBgnX) * frame / maxFrame)
			+ rateBgnX;
	rate_t rateY = ((rateEndY - rateBgnY) * frame / maxFrame)
			+ rateBgnY;
	long xx = ((w / 2) * rateX / _100_PERCENT) + ((w - pcgW) / 2);
	long yy = ((h / 2) * rateY / _100_PERCENT) + ((h - pcgH) / 2);
	xx += x;
	yy += y;

	pcg.draw( gPcgDun.getWBuf(), xx, yy, pcgW, pcgH );

	return flagDone;
}
