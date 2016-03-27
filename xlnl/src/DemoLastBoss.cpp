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
* $Id: DemoLastBoss.cpp,v 1.14 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ラスボスのデモ
////////////////////////////////////////////////////////////////

#define DEMO_LAST_BOSS_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

// カットイン画像のディレクトリ
#define STR_CUT_IN_DIR_NAME_EXEL	"exel/"
#define STR_CUT_IN_DIR_NAME_EXELER	"exeler/"
#define STR_CUT_IN_DIR_NAME_XEX	"xex/"

static const long nCutInMaxFrame = TIMER_FRAME * 60 / 60;
static const long nCutOutMaxFrame = TIMER_FRAME * 60 / 60;

#ifdef	D_MFC
static const long skipFrameLastBoss = 1;
#else
static const long skipFrameLastBoss = 6;
#endif

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

DemoLastBoss::DemoLastBoss()
{
	frame = 0;
	flagDone = false;
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

DemoLastBoss::~DemoLastBoss()
{
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void DemoLastBoss::init()
{
	// カットイン画像を読み込む

	CutInExel.init( STR_CUT_IN_DIR_NAME_EXEL );
	CutInExeler.init( STR_CUT_IN_DIR_NAME_EXELER );
	CutInXex.init( STR_CUT_IN_DIR_NAME_XEX );

	CutInExel.setPos( -125, 0, -50, 0 );
	CutInExeler.setPos( +125, 0, +50, 0 );
	CutInXex.setPos( 0, -125, 0, -50 );

	reset();
}

////////////////////////////////////////////////////////////////
// デモのリセット
////////////////////////////////////////////////////////////////

void DemoLastBoss::reset()
{
	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
	case LAST_SCENE_N_ENCOUNTER:
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	//case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
	case LAST_SCENE_N_EXEL:
	case LAST_SCENE_N_EXEL_ENTER:
	case LAST_SCENE_N_EXEL_CUT_IN:
	//case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_CUT_OUT:
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
	case LAST_SCENE_N_EXEL_BATTLE:
	//case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER:
	case LAST_SCENE_N_EXELER_CUT_IN:
	//case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_CUT_OUT:
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
	case LAST_SCENE_N_EXELER_BATTLE:
	//case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX:
	case LAST_SCENE_N_XEX_CUT_IN:
	//case LAST_SCENE_N_XEX_WORDS:
	case LAST_SCENE_N_XEX_CUT_OUT:
	case LAST_SCENE_N_XEX_CUT_END:
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
	case LAST_SCENE_N_XX_BATTLE:
	case LAST_SCENE_N_XX_DIE:
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		frame = 0;
		break;
	case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX_WORDS:
		frame = nCutInMaxFrame;
		break;
	}

	flagDone = false;
}

////////////////////////////////////////////////////////////////
// デモの描画
// return : 描画が終了したか?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::draw()
{
	// 1 度しか実行しないシーンは必ず true を返す
	bool flag = true;

	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
	case LAST_SCENE_N_ENCOUNTER:
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
		flag = drawCutIn( true, true, true );
		break;
	case LAST_SCENE_N_ENCOUNTER_WORDS:
		drawCutIn( true, true, true );
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
		flag = drawCutOut( true, true, true );
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
	case LAST_SCENE_N_EXEL:
	case LAST_SCENE_N_EXEL_ENTER:
		break;
	case LAST_SCENE_N_EXEL_CUT_IN:
		flag = drawCutIn( true, false, false );
		break;
	case LAST_SCENE_N_EXEL_WORDS:
		drawCutIn( true, false, false );
		break;
	case LAST_SCENE_N_EXEL_CUT_OUT:
		flag = drawCutOut( true, false, false );
		break;
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
	case LAST_SCENE_N_EXEL_BATTLE:
	case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER:
		break;
	case LAST_SCENE_N_EXELER_CUT_IN:
		flag = drawCutIn( false, true, false );
		break;
	case LAST_SCENE_N_EXELER_WORDS:
		drawCutIn( false, true, false );
		break;
	case LAST_SCENE_N_EXELER_CUT_OUT:
		flag = drawCutOut( false, true, false );
		break;
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
	case LAST_SCENE_N_EXELER_BATTLE:
	case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX:
		break;
	case LAST_SCENE_N_XEX_CUT_IN:
		flag = drawCutIn( false, false, true );
		break;
	case LAST_SCENE_N_XEX_WORDS:
		drawCutIn( false, false, true );
		break;
	case LAST_SCENE_N_XEX_CUT_OUT:
		flag = drawCutOut( false, false, true );
		break;
	case LAST_SCENE_N_XEX_CUT_END:
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
	case LAST_SCENE_N_XX_BATTLE:
	case LAST_SCENE_N_XX_DIE:
		break;
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		break;
	}

	flagDone = flag;
	return flagDone;
}

////////////////////////////////////////////////////////////////
// カットインの描画
// return : 描画が終了したか?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::drawCutIn(
	bool flagExel, bool flagExeler, bool flagXex
)
{
	if( flagExel )
		CutInExel.drawCutIn( frame, nCutInMaxFrame );
	if( flagExeler )
		CutInExeler.drawCutIn( frame, nCutInMaxFrame );
	if( flagXex )
		CutInXex.drawCutIn( frame, nCutInMaxFrame );

	return incFrame( nCutInMaxFrame );
}

////////////////////////////////////////////////////////////////
// カットアウトの描画
// return : 描画が終了したか?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::drawCutOut(
	bool flagExel, bool flagExeler, bool flagXex
)
{
	if( flagExel )
		CutInExel.drawCutOut( frame, nCutOutMaxFrame );
	if( flagExeler )
		CutInExeler.drawCutOut( frame, nCutOutMaxFrame );
	if( flagXex )
		CutInXex.drawCutOut( frame, nCutOutMaxFrame );

	return incFrame( nCutOutMaxFrame );
}

////////////////////////////////////////////////////////////////
// フレームを進める
// long maxFrame : 最後のフレーム
// return : 最後のフレームに達したか?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::incFrame( long maxFrame )
{
	frame++;

	if( frame > maxFrame ){
		frame = maxFrame;
		return true;
	} else {
		return false;
	}
}

////////////////////////////////////////////////////////////////
// フレームを間引くか調べる
// return : 間引くか?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::checkSkipFrame()
{
	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
	case LAST_SCENE_N_ENCOUNTER:
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	//case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
	case LAST_SCENE_N_EXEL:
	case LAST_SCENE_N_EXEL_ENTER:
	case LAST_SCENE_N_EXEL_CUT_IN:
	//case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_CUT_OUT:
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
	case LAST_SCENE_N_EXEL_BATTLE:
	//case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER:
	case LAST_SCENE_N_EXELER_CUT_IN:
	//case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_CUT_OUT:
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
	case LAST_SCENE_N_EXELER_BATTLE:
	//case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX:
	case LAST_SCENE_N_XEX_CUT_IN:
	//case LAST_SCENE_N_XEX_WORDS:
	case LAST_SCENE_N_XEX_CUT_OUT:
	case LAST_SCENE_N_XEX_CUT_END:
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
	case LAST_SCENE_N_XX_BATTLE:
	case LAST_SCENE_N_XX_DIE:
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		break;
	case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX_WORDS:
		if( (frame % skipFrameLastBoss) != 0 )
			return true;
		else
			return false;
		break;
	}
	return false;
}

////////////////////////////////////////////////////////////////
// デモの描画が終了したか調べる
// return : デモの描画が終了したか?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::checkDone()
{
	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
	case LAST_SCENE_N_ENCOUNTER:
	//case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	case LAST_SCENE_N_ENCOUNTER_WORDS:
	//case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
	case LAST_SCENE_N_EXEL:
	case LAST_SCENE_N_EXEL_ENTER:
	//case LAST_SCENE_N_EXEL_CUT_IN:
	case LAST_SCENE_N_EXEL_WORDS:
	//case LAST_SCENE_N_EXEL_CUT_OUT:
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
	case LAST_SCENE_N_EXEL_BATTLE:
	case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER:
	//case LAST_SCENE_N_EXELER_CUT_IN:
	case LAST_SCENE_N_EXELER_WORDS:
	//case LAST_SCENE_N_EXELER_CUT_OUT:
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
	case LAST_SCENE_N_EXELER_BATTLE:
	case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX:
	//case LAST_SCENE_N_XEX_CUT_IN:
	case LAST_SCENE_N_XEX_WORDS:
	//case LAST_SCENE_N_XEX_CUT_OUT:
	case LAST_SCENE_N_XEX_CUT_END:
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
	case LAST_SCENE_N_XX_BATTLE:
	case LAST_SCENE_N_XX_DIE:
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		flagDone = true;
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
	case LAST_SCENE_N_EXEL_CUT_IN:
	case LAST_SCENE_N_EXEL_CUT_OUT:
	case LAST_SCENE_N_EXELER_CUT_IN:
	case LAST_SCENE_N_EXELER_CUT_OUT:
	case LAST_SCENE_N_XEX_CUT_IN:
	case LAST_SCENE_N_XEX_CUT_OUT:
		break;
	}

	return flagDone;
}
