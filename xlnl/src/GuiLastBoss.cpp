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
* $Id: GuiLastBoss.cpp,v 1.23 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ラスボスの描画 (GUI)
////////////////////////////////////////////////////////////////

#define GUI_LAST_BOSS_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

struct LastBossJoint {
	long x, y;
};

LastBossJoint jointSkullToJaw = { 125, 32 };
LastBossJoint jointJawToSkull = { 125, 32 };
LastBossJoint jointJawToSkullOpen = { 125, 0 };
LastBossJoint jointSkullToBody = { 125, 338 };
LastBossJoint jointBodyToSkull = { 320, 0 };
LastBossJoint jointBodyToUpperArmLeft = { 634 - 48, 180 };
LastBossJoint jointBodyToUpperArmRight = { 48, 172 };
LastBossJoint jointUpperArmToBodyLeft = { 480 - 360, 76 };
LastBossJoint jointUpperArmToBodyRight = { 360, 76 };
LastBossJoint jointUpperArmToForeArmLeft = { 480 - 120, 436 };
LastBossJoint jointUpperArmToForeArmRight = { 120, 436 };
LastBossJoint jointForeArmToUpperArmLeft = { 96 - 36, 388 };
LastBossJoint jointForeArmToUpperArmRight = { 36, 388 };
LastBossJoint jointForeArmToUpperArmSlapLeft = { 400 - 30, 320 };
LastBossJoint jointForeArmToUpperArmSlapRight = { 30, 320 };
LastBossJoint jointForeArmToHandLeft = { 96 - 60, 20 };
LastBossJoint jointForeArmToHandRight = { 60, 20 };
LastBossJoint jointForeArmToHandSlapLeft = { 50, 110 };
LastBossJoint jointForeArmToHandSlapRight = { 400 - 50, 110 };
LastBossJoint jointHandToForeArmLeft = { 240 - 56, 290 };
LastBossJoint jointHandToForeArmRight = { 56, 290 };
LastBossJoint jointHandToForeArmSlapLeft = { 320 - 90, 320 - 50 };
LastBossJoint jointHandToForeArmSlapRight = { 90, 320 - 50 };

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

GuiLastBoss::GuiLastBoss()
{
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

GuiLastBoss::~GuiLastBoss()
{
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void GuiLastBoss::init()
{
	long r = gPcgDun.nTileSizeRate;
	jointSkullToJaw.x = jointSkullToJaw.x
			* r / _100_PERCENT;
	jointSkullToJaw.y = jointSkullToJaw.y
			* r / _100_PERCENT;
	jointJawToSkull.x = jointJawToSkull.x
			* r / _100_PERCENT;
	jointJawToSkull.y = jointJawToSkull.y
			* r / _100_PERCENT;
	jointJawToSkullOpen.x = jointJawToSkullOpen.x
			* r / _100_PERCENT;
	jointJawToSkullOpen.y = jointJawToSkullOpen.y
			* r / _100_PERCENT;
	jointSkullToBody.x = jointSkullToBody.x
			* r / _100_PERCENT;
	jointSkullToBody.y = jointSkullToBody.y
			* r / _100_PERCENT;
	jointBodyToSkull.x = jointBodyToSkull.x
			* r / _100_PERCENT;
	jointBodyToSkull.y = jointBodyToSkull.y
			* r / _100_PERCENT;
	jointBodyToUpperArmLeft.x = jointBodyToUpperArmLeft.x
			* r / _100_PERCENT;
	jointBodyToUpperArmLeft.y = jointBodyToUpperArmLeft.y
			* r / _100_PERCENT;
	jointBodyToUpperArmRight.x = jointBodyToUpperArmRight.x
			* r / _100_PERCENT;
	jointBodyToUpperArmRight.y = jointBodyToUpperArmRight.y
			* r / _100_PERCENT;
	jointUpperArmToBodyLeft.x = jointUpperArmToBodyLeft.x
			* r / _100_PERCENT;
	jointUpperArmToBodyLeft.y = jointUpperArmToBodyLeft.y
			* r / _100_PERCENT;
	jointUpperArmToBodyRight.x = jointUpperArmToBodyRight.x
			* r / _100_PERCENT;
	jointUpperArmToBodyRight.y = jointUpperArmToBodyRight.y
			* r / _100_PERCENT;
	jointUpperArmToForeArmLeft.x = jointUpperArmToForeArmLeft.x
			* r / _100_PERCENT;
	jointUpperArmToForeArmLeft.y = jointUpperArmToForeArmLeft.y
			* r / _100_PERCENT;
	jointUpperArmToForeArmRight.x = jointUpperArmToForeArmRight.x
			* r / _100_PERCENT;
	jointUpperArmToForeArmRight.y = jointUpperArmToForeArmRight.y
			* r / _100_PERCENT;
	jointForeArmToUpperArmLeft.x = jointForeArmToUpperArmLeft.x
			* r / _100_PERCENT;
	jointForeArmToUpperArmLeft.y = jointForeArmToUpperArmLeft.y
			* r / _100_PERCENT;
	jointForeArmToUpperArmRight.x = jointForeArmToUpperArmRight.x
			* r / _100_PERCENT;
	jointForeArmToUpperArmRight.y = jointForeArmToUpperArmRight.y
			* r / _100_PERCENT;
	jointForeArmToUpperArmSlapLeft.x = jointForeArmToUpperArmSlapLeft.x
			* r / _100_PERCENT;
	jointForeArmToUpperArmSlapLeft.y = jointForeArmToUpperArmSlapLeft.y
			* r / _100_PERCENT;
	jointForeArmToUpperArmSlapRight.x = jointForeArmToUpperArmSlapRight.x
			* r / _100_PERCENT;
	jointForeArmToUpperArmSlapRight.y = jointForeArmToUpperArmSlapRight.y
			* r / _100_PERCENT;
	jointForeArmToHandLeft.x = jointForeArmToHandLeft.x
			* r / _100_PERCENT;
	jointForeArmToHandLeft.y = jointForeArmToHandLeft.y
			* r / _100_PERCENT;
	jointForeArmToHandRight.x = jointForeArmToHandRight.x
			* r / _100_PERCENT;
	jointForeArmToHandRight.y = jointForeArmToHandRight.y
			* r / _100_PERCENT;
	jointForeArmToHandSlapLeft.x = jointForeArmToHandSlapLeft.x
			* r / _100_PERCENT;
	jointForeArmToHandSlapLeft.y = jointForeArmToHandSlapLeft.y
			* r / _100_PERCENT;
	jointForeArmToHandSlapRight.x = jointForeArmToHandSlapRight.x
			* r / _100_PERCENT;
	jointForeArmToHandSlapRight.y = jointForeArmToHandSlapRight.y
			* r / _100_PERCENT;
	jointHandToForeArmLeft.x = jointHandToForeArmLeft.x
			* r / _100_PERCENT;
	jointHandToForeArmLeft.y = jointHandToForeArmLeft.y
			* r / _100_PERCENT;
	jointHandToForeArmRight.x = jointHandToForeArmRight.x
			* r / _100_PERCENT;
	jointHandToForeArmRight.y = jointHandToForeArmRight.y
			* r / _100_PERCENT;
	jointHandToForeArmSlapLeft.x = jointHandToForeArmSlapLeft.x
			* r / _100_PERCENT;
	jointHandToForeArmSlapLeft.y = jointHandToForeArmSlapLeft.y
			* r / _100_PERCENT;
	jointHandToForeArmSlapRight.x = jointHandToForeArmSlapRight.x
			* r / _100_PERCENT;
	jointHandToForeArmSlapRight.y = jointHandToForeArmSlapRight.y
			* r / _100_PERCENT;

	initPcg( &pcgSkull, "last_boss/skull/" );
	initPcg( &pcgJaw, "last_boss/jaw/" );
	initPcg( &pcgBody, "last_boss/body/" );
	initPcg( &pcgUpperArmLeft, "last_boss/upper_arm_left/" );
	initPcg( &pcgUpperArmRight, "last_boss/upper_arm_right/" );
	initPcg( &pcgForeArmLeft, "last_boss/fore_arm_left/" );
	initPcg( &pcgForeArmRight, "last_boss/fore_arm_right/" );
	initPcg( &pcgForeArmSlapLeft, "last_boss/fore_arm_left/slap/" );
	initPcg( &pcgForeArmSlapRight, "last_boss/fore_arm_right/slap/" );
	initPcg( &pcgHandLeft, "last_boss/hand_left/" );
	initPcg( &pcgHandRight, "last_boss/hand_right/" );
	initPcg( &pcgHandSlapLeft, "last_boss/hand_left/slap/" );
	initPcg( &pcgHandSlapRight, "last_boss/hand_right/slap/" );

	xxAttack.kind = XX_ACT_KIND_NULL;
	initPcg( &pcgXxHeat, "last_boss/attack/heat/" );
	initPcg( &pcgXxCold, "last_boss/attack/cold/" );
	initPcg( &pcgXxBit, "last_boss/attack/cold/bit/" );
	initPcg( &pcgXxMind, "last_boss/attack/mind/" );
	initPcg( &pcgXxAcid, "last_boss/attack/acid/" );
	initPcg( &pcgXxRotation, "last_boss/attack/rotation/" );
	initPcg( &pcgXxWhirl, "last_boss/attack/whirl/" );
	initPcg( &pcgXxFan, "last_boss/attack/fan/" );
}

////////////////////////////////////////////////////////////////
// パターンの初期化
// Pcg *pcg : パターン
// WSCstring dirName : 画像のディレクトリ名
////////////////////////////////////////////////////////////////

void GuiLastBoss::initPcg( Pcg *pcg, WSCstring dirName )
{
	// 画像の検索を設定

	WSCstring dir = STR_DEFAULT_GRAPH_DIR_NAME;
	WSCstring ext = STR_GRAPH_FILE_EXT;
	WSCstring pcgPath = dirName;

	FileList::setStrDirSelGraph( dir );
	FileList ls;

	// 画像を検索

	long nFileMaxN = 0;
	long nFileSelN = 0;

	{
		ls.reset( pcgPath, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
		}

		nFileMaxN = j;
	}

	// 画像をランダムに選択

	if( nFileMaxN > 0 )
		nFileSelN = gui_randm( nFileMaxN );
	else
		nFileSelN = -1;

	// 画像を読み込む

	if( nFileSelN > -1 ){
		ls.reset( pcgPath, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
			if( j == nFileSelN ){
				pcg->init( path );
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////
// 描画前の座標計算
////////////////////////////////////////////////////////////////

void GuiLastBoss::setDraw()
{
	if( get_scene() != SCENE_N_LAST_BOSS )
		return;

	last_scene_n_t sc = get_last_scene();
	if( (sc < LAST_SCENE_N_XX_ENTER)
			|| (LAST_SCENE_N_XX_DIE <= sc) ){
		return;
	}

	// 基準座標

	pos_t	pos = get_xx_pos();
	if( !clip_pos( pos.x, pos.y ) )
		return;

	long sizeX = gPcgDun.getTileSizeX( false );
	long sizeY = gPcgDun.getTileSizeY( false );
	long x = (pos.x * sizeX) + (sizeX / 2);
	long y = pos.y * sizeY;

	// 頭の座標

	skullW = pcgSkull.getWidth();
	skullH = pcgSkull.getHeight();
	skullX = x - (skullW / 2);
	skullY = y;

	// アゴの座標

	jawW = pcgJaw.getWidth();
	jawH = pcgJaw.getHeight();
	jawX = skullX
			+ jointSkullToJaw.x
			- jointJawToSkull.x;
	jawY = skullY
			+ jointSkullToJaw.y
			- jointJawToSkull.y;

	// アゴの座標 (開く)

	jawOpenW = pcgJaw.getWidth();
	jawOpenH = pcgJaw.getHeight();
	jawOpenX = skullX
			+ jointSkullToJaw.x
			- jointJawToSkullOpen.x;
	jawOpenY = skullY
			+ jointSkullToJaw.y
			- jointJawToSkullOpen.y;

	// 体の座標

	bodyW = pcgBody.getWidth();
	bodyH = pcgBody.getHeight();
	bodyX = skullX
			+ jointSkullToBody.x
			- jointBodyToSkull.x;
	bodyY = skullY
			+ jointSkullToBody.y
			- jointBodyToSkull.y;

	// 左上腕の座標

	upperArmLeftW = pcgUpperArmLeft.getWidth();
	upperArmLeftH = pcgUpperArmLeft.getHeight();
	upperArmLeftX = bodyX
			+ jointBodyToUpperArmLeft.x
			- jointUpperArmToBodyLeft.x;
	upperArmLeftY = bodyY
			+ jointBodyToUpperArmLeft.y
			- jointUpperArmToBodyLeft.y;

	// 右上腕の座標

	upperArmRightW = pcgUpperArmRight.getWidth();
	upperArmRightH = pcgUpperArmRight.getHeight();
	upperArmRightX = bodyX
			+ jointBodyToUpperArmRight.x
			- jointUpperArmToBodyRight.x;
	upperArmRightY = bodyY
			+ jointBodyToUpperArmRight.y
			- jointUpperArmToBodyRight.y;

	// 左前腕の座標

	foreArmLeftW = pcgForeArmLeft.getWidth();
	foreArmLeftH = pcgForeArmLeft.getHeight();
	foreArmLeftX = upperArmLeftX
			+ jointUpperArmToForeArmLeft.x
			- jointForeArmToUpperArmLeft.x;
	foreArmLeftY = upperArmLeftY
			+ jointUpperArmToForeArmLeft.y
			- jointForeArmToUpperArmLeft.y;

	// 左前腕の座標 (平手打ち)

	foreArmSlapLeftW = pcgForeArmSlapLeft.getWidth();
	foreArmSlapLeftH = pcgForeArmSlapLeft.getHeight();
	foreArmSlapLeftX = upperArmLeftX
			+ jointUpperArmToForeArmLeft.x
			- jointForeArmToUpperArmSlapLeft.x;
	foreArmSlapLeftY = upperArmLeftY
			+ jointUpperArmToForeArmLeft.y
			- jointForeArmToUpperArmSlapLeft.y;

	// 右前腕の座標

	foreArmRightW = pcgForeArmRight.getWidth();
	foreArmRightH = pcgForeArmRight.getHeight();
	foreArmRightX = upperArmRightX
			+ jointUpperArmToForeArmRight.x
			- jointForeArmToUpperArmRight.x;
	foreArmRightY = upperArmRightY
			+ jointUpperArmToForeArmRight.y
			- jointForeArmToUpperArmRight.y;

	// 右前腕の座標 (平手打ち)

	foreArmSlapRightW = pcgForeArmSlapRight.getWidth();
	foreArmSlapRightH = pcgForeArmSlapRight.getHeight();
	foreArmSlapRightX = upperArmRightX
			+ jointUpperArmToForeArmRight.x
			- jointForeArmToUpperArmSlapRight.x;
	foreArmSlapRightY = upperArmRightY
			+ jointUpperArmToForeArmRight.y
			- jointForeArmToUpperArmSlapRight.y;

	// 左手の座標

	handLeftW = pcgHandLeft.getWidth();
	handLeftH = pcgHandLeft.getHeight();
	handLeftX = foreArmLeftX
			+ jointForeArmToHandLeft.x
			- jointHandToForeArmLeft.x;
	handLeftY = foreArmLeftY
			+ jointForeArmToHandLeft.y
			- jointHandToForeArmLeft.y;

	// 左手の座標 (平手打ち)

	handSlapLeftW = pcgHandSlapLeft.getWidth();
	handSlapLeftH = pcgHandSlapLeft.getHeight();
	handSlapLeftX = foreArmSlapLeftX
			+ jointForeArmToHandSlapLeft.x
			- jointHandToForeArmSlapLeft.x;
	handSlapLeftY = foreArmSlapLeftY
			+ jointForeArmToHandSlapLeft.y
			- jointHandToForeArmSlapLeft.y;

	// 右手の座標

	handRightW = pcgHandRight.getWidth();
	handRightH = pcgHandRight.getHeight();
	handRightX = foreArmRightX
			+ jointForeArmToHandRight.x
			- jointHandToForeArmRight.x;
	handRightY = foreArmRightY
			+ jointForeArmToHandRight.y
			- jointHandToForeArmRight.y;

	// 右手の座標 (平手打ち)

	handSlapRightW = pcgHandSlapRight.getWidth();
	handSlapRightH = pcgHandSlapRight.getHeight();
	handSlapRightX = foreArmSlapRightX
			+ jointForeArmToHandSlapRight.x
			- jointHandToForeArmSlapRight.x;
	handSlapRightY = foreArmSlapRightY
			+ jointForeArmToHandSlapRight.y
			- jointHandToForeArmSlapRight.y;
}

////////////////////////////////////////////////////////////////
// 描画 (背景)
////////////////////////////////////////////////////////////////

void GuiLastBoss::drawBg()
{
	if( get_scene() != SCENE_N_LAST_BOSS )
		return;

	last_scene_n_t sc = get_last_scene();
	if( (sc < LAST_SCENE_N_XX_ENTER)
			|| (LAST_SCENE_N_XX_DIE <= sc) ){
		return;
	}

	setDraw();

	// 描画

	drawPcg( &pcgBody, bodyX, bodyY, bodyW, bodyH );

	if( get_open_xx_jaw() ){
		drawPcg( &pcgJaw, jawOpenX, jawOpenY, jawOpenW, jawOpenH );
	} else {
		drawPcg( &pcgJaw, jawX, jawY, jawW, jawH );
	}

	drawPcg( &pcgSkull, skullX, skullY, skullW, skullH );
	drawPcg( &pcgUpperArmLeft,
			upperArmLeftX, upperArmLeftY,
			upperArmLeftW, upperArmLeftH );
	drawPcg( &pcgUpperArmRight,
			upperArmRightX, upperArmRightY,
			upperArmRightW, upperArmRightH );
}

////////////////////////////////////////////////////////////////
// 描画 (前景)
////////////////////////////////////////////////////////////////

void GuiLastBoss::drawFg()
{
	if( get_scene() != SCENE_N_LAST_BOSS )
		return;

	last_scene_n_t sc = get_last_scene();
	if( (sc < LAST_SCENE_N_XX_ENTER)
			|| (LAST_SCENE_N_XX_DIE <= sc) ){
		return;
	}

	setDraw();

	// 描画

	if( get_slap_xx_arm_left() ){
		drawPcg( &pcgForeArmSlapLeft,
				foreArmSlapLeftX, foreArmSlapLeftY,
				foreArmSlapLeftW, foreArmSlapLeftH );

		drawPcg( &pcgHandSlapLeft,
				handSlapLeftX, handSlapLeftY,
				handSlapLeftW, handSlapLeftH );
	} else {
		drawPcg( &pcgForeArmLeft,
				foreArmLeftX, foreArmLeftY,
				foreArmLeftW, foreArmLeftH );

		drawPcg( &pcgHandLeft,
				handLeftX, handLeftY,
				handLeftW, handLeftH );
	}

	if( get_slap_xx_arm_right() ){
		drawPcg( &pcgForeArmSlapRight,
				foreArmSlapRightX, foreArmSlapRightY,
				foreArmSlapRightW, foreArmSlapRightH );

		drawPcg( &pcgHandSlapRight,
				handSlapRightX, handSlapRightY,
				handSlapRightW, handSlapRightH );
	} else {
		drawPcg( &pcgForeArmRight,
				foreArmRightX, foreArmRightY,
				foreArmRightW, foreArmRightH );

		drawPcg( &pcgHandRight,
				handRightX, handRightY,
				handRightW, handRightH );
	}
}

////////////////////////////////////////////////////////////////
// 描画 (背景)
// Pcg *p : パターン
// long x : X 座標
// long y : Y 座標
// long w : 幅
// long h : 高さ
////////////////////////////////////////////////////////////////

void GuiLastBoss::drawPcg( Pcg *p, long x, long y, long w, long h )
{
	if( p == NULL )
		return;

	p->draw( gPcgDun.getWBuf(), x, y, w, h );
}

////////////////////////////////////////////////////////////////
// XX の攻撃の描画データを設定
// xx_act_kind_t kind : 攻撃の種類
// void *p : 攻撃のデータ
////////////////////////////////////////////////////////////////

void GuiLastBoss::setXxAttack( xx_act_kind_t kind, void *p )
{
	if( get_scene() != SCENE_N_LAST_BOSS )
		return;

	last_scene_n_t sc = get_last_scene();
	if( (sc < LAST_SCENE_N_XX_ENTER)
			|| (LAST_SCENE_N_XX_DIE <= sc) ){
		return;
	}

	xxAttack.kind = kind;

	if( p == NULL )
		return;

	switch( kind ){
	case XX_ACT_KIND_NULL:
	case XX_ACT_KIND_MAX_N:
		break;
	case XX_ACT_KIND_HEAT:
		xxAttack.data.heat = *((xx_heat_t *)p);
		break;
	case XX_ACT_KIND_COLD:
		xxAttack.data.cold = *((xx_cold_t *)p);
		break;
	case XX_ACT_KIND_MIND:
		xxAttack.data.mind = *((xx_mind_t *)p);
		break;
	case XX_ACT_KIND_ACID:
		xxAttack.data.acid = *((xx_acid_t *)p);
		break;
	case XX_ACT_KIND_PARALYZE:
		xxAttack.data.rotation = *((xx_rotation_t *)p);
		break;
	case XX_ACT_KIND_POISON:
		xxAttack.data.whirl = *((xx_whirl_t *)p);
		break;
	case XX_ACT_KIND_SLEEP:
		xxAttack.data.fan = *((xx_fan_t *)p);
		break;
	case XX_ACT_KIND_SLAP:
		break;
	}
}

////////////////////////////////////////////////////////////////
// XX の攻撃の描画
// long mapX : X 座標
// long mapY : Y 座標
// long mapW : 幅
// long mapH : 高さ
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GuiLastBoss::drawXxAttack(
	long mapX, long mapY, long mapW, long mapH )
{
	switch( xxAttack.kind ){
	case XX_ACT_KIND_NULL:
	case XX_ACT_KIND_MAX_N:
		break;
	case XX_ACT_KIND_HEAT:
		return drawXxAttackHeat( mapX, mapY, mapW, mapH );
	case XX_ACT_KIND_COLD:
		return drawXxAttackCold( mapX, mapY, mapW, mapH );
	case XX_ACT_KIND_MIND:
		return drawXxAttackMind( mapX, mapY, mapW, mapH );
	case XX_ACT_KIND_ACID:
		return drawXxAttackAcid( mapX, mapY, mapW, mapH );
	case XX_ACT_KIND_PARALYZE:
		return drawXxAttackRotation( mapX, mapY, mapW, mapH );
	case XX_ACT_KIND_POISON:
		return drawXxAttackWhirl( mapX, mapY, mapW, mapH );
	case XX_ACT_KIND_SLEEP:
		return drawXxAttackFan( mapX, mapY, mapW, mapH );
	case XX_ACT_KIND_SLAP:
		break;
	}

	return true;
}

////////////////////////////////////////////////////////////////
// XX の火熱攻撃の描画
// long mapX : X 座標
// long mapY : Y 座標
// long mapW : 幅
// long mapH : 高さ
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GuiLastBoss::drawXxAttackHeat(
	long mapX, long mapY, long mapW, long mapH )
{
	if( !gPcgDun.clipWin( mapX, mapY ) )
		return true;

	const long blast_max_n = 4;
	xx_heat_t &xx_heat = xxAttack.data.heat;

	long sizeX = gPcgDun.getTileSizeX( false );
	long sizeY = gPcgDun.getTileSizeY( false );
	long w = pcgXxHeat.getWidth();
	long h = pcgXxHeat.getHeight() / blast_max_n;

	for( long n = 0; n < XX_HEAT_MAX_N; n++ ){
		if( xx_heat.blast_n[n] <= -1 )
			continue;

		if( mapX > (xx_heat.blast_x[n] + 2) )
			continue;
		if( mapY > (xx_heat.blast_y[n] + 2) )
			continue;
		if( (mapX + mapW) < (xx_heat.blast_x[n] + 2) )
			continue;
		if( (mapY + mapH) < (xx_heat.blast_y[n] + 2) )
			continue;

		long m = xx_heat.blast_m[n];
		if( m >= blast_max_n )
			continue;

		long x = xx_heat.blast_x[n] * sizeX;
		long y = xx_heat.blast_y[n] * sizeY;
		x -= w / 2;
		y -= h / 2;

		long idxX = 0;
		long idxY = m;

		pcgXxHeat.drawIdx( gPcgDun.getWBuf(),
				x, y, w, h,
				idxX, idxY,
				w, h );
	}

	return true;
}

////////////////////////////////////////////////////////////////
// XX の水冷攻撃の描画
// long mapX : X 座標
// long mapY : Y 座標
// long mapW : 幅
// long mapH : 高さ
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GuiLastBoss::drawXxAttackCold(
	long mapX, long mapY, long mapW, long mapH )
{
	if( !gPcgDun.clipWin( mapX, mapY ) )
		return true;

	xx_cold_t &xx_cold = xxAttack.data.cold;

	long sizeX = gPcgDun.getTileSizeX( false );
	long sizeY = gPcgDun.getTileSizeY( false );
	long coldW = pcgXxCold.getWidth();
	long coldH = pcgXxCold.getHeight() / MBR_MAX_N;
	long bitW = pcgXxBit.getWidth();
	long bitH = pcgXxBit.getHeight() / MBR_MAX_N;

	for( long n = 0; n < MBR_MAX_N; n++ ){
		long bitX = xx_cold.bit_x[n] * sizeX;
		long bitY = xx_cold.bit_y[n] * sizeY;
		bitX += (sizeX / 2) - (bitW / 2);
		bitY += (sizeX / 2) - (bitH / 2);

		long bitIdxX = 0;
		long bitIdxY = n;

		for( long j = 0; j < xx_cold.laser_len; j++ ){
			long coldX = xx_cold.bit_x[n] * sizeX;
			long coldY = xx_cold.bit_y[n] * sizeY;
			coldX += (sizeX / 2) - (coldW / 2);
			coldY += (sizeY / 2) - (coldH / 2);
			pos_t *dxy = get_xx_laser_dxy();
			long d = j + 1;
			coldX += (dxy[n].x * d) * sizeX / 2;
			coldY += (dxy[n].y * d) * sizeY;

			long coldIdxX = 0;
			long coldIdxY = n;

			pcgXxCold.drawIdx( gPcgDun.getWBuf(),
					coldX, coldY, coldW, coldH,
					coldIdxX, coldIdxY,
					coldW, coldH );
		}

		pcgXxBit.drawIdx( gPcgDun.getWBuf(),
				bitX, bitY, bitW, bitH,
				bitIdxX, bitIdxY,
				bitW, bitH );
	}

	return true;
}

////////////////////////////////////////////////////////////////
// XX の風心攻撃の描画
// long mapX : X 座標
// long mapY : Y 座標
// long mapW : 幅
// long mapH : 高さ
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GuiLastBoss::drawXxAttackMind(
	long mapX, long mapY, long mapW, long mapH )
{
	if( !gPcgDun.clipWin( mapX, mapY ) )
		return true;

	xx_mind_t &xx_mind = xxAttack.data.mind;

	long sizeX = gPcgDun.getTileSizeX( false );
	long sizeY = gPcgDun.getTileSizeY( false );
	long w = pcgXxMind.getWidth();
	long h = pcgXxMind.getHeight();

	for( long m = 0; m < MBR_MAX_N; m++ ){
		for( long n = XX_MIND_IMAGE_MAX_N - 1; n >= 0; n-- ){
			long idx = (xx_mind.refract_idx + n)
					% XX_MIND_IMAGE_MAX_N;

			if( mapX > xx_mind.refract_x[m][idx] )
				continue;
			if( mapY > xx_mind.refract_y[m][idx] )
				continue;
			if( (mapX + mapW) < xx_mind.refract_x[m][idx] )
				continue;
			if( (mapY + mapH) < xx_mind.refract_y[m][idx] )
				continue;

			long x = xx_mind.refract_x[m][idx] * sizeX;
			long y = xx_mind.refract_y[m][idx] * sizeY;
			x += (sizeX / 2) - (w / 2);
			y += (sizeY / 2) - (h / 2);

			pcgXxMind.draw( gPcgDun.getWBuf(), x, y, w, h );
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////
// XX の土酸攻撃の描画
// long mapX : X 座標
// long mapY : Y 座標
// long mapW : 幅
// long mapH : 高さ
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GuiLastBoss::drawXxAttackAcid(
	long mapX, long mapY, long mapW, long mapH )
{
	if( !gPcgDun.clipWin( mapX, mapY ) )
		return true;

	xx_acid_t &xx_acid = xxAttack.data.acid;

	long sizeX = gPcgDun.getTileSizeX( false );
	long sizeY = gPcgDun.getTileSizeY( false );
	long w = pcgXxAcid.getWidth();
	long h = pcgXxAcid.getHeight();

	long fix = XX_ACID_HOMING_FIX_POINT;

	for( long m = 0; m < MBR_MAX_N; m++ ){
		for( long n = XX_ACID_IMAGE_MAX_N - 1; n >= 0; n-- ){
			long idx = (xx_acid.homing_idx + n)
					% XX_ACID_IMAGE_MAX_N;

			long x = (long)(xx_acid.homing_x[m][idx] / fix);
			long y = (long)(xx_acid.homing_y[m][idx] / fix);

			if( mapX > x )
				continue;
			if( mapY > y )
				continue;
			if( (mapX + mapW) < x )
				continue;
			if( (mapY + mapH) < y )
				continue;

			x = x * sizeX;
			y = y * sizeY;
			x += (sizeX / 2) - (w / 2);
			y += (sizeY / 2) - (h / 2);

			pcgXxAcid.draw( gPcgDun.getWBuf(), x, y, w, h );
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////
// XX の回転弾の攻撃の描画
// long mapX : X 座標
// long mapY : Y 座標
// long mapW : 幅
// long mapH : 高さ
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GuiLastBoss::drawXxAttackRotation(
	long mapX, long mapY, long mapW, long mapH )
{
	if( !gPcgDun.clipWin( mapX, mapY ) )
		return true;

	xx_rotation_t &xx_rotation = xxAttack.data.rotation;

	long sizeX = gPcgDun.getTileSizeX( false );
	long sizeY = gPcgDun.getTileSizeY( false );
	long w = pcgXxRotation.getWidth();
	long h = pcgXxRotation.getHeight();

	for( long r = 0; r < XX_ROTATION_RING_MAX_N; r++ ){
		if( !xx_rotation.flg_move[r] )
			continue;

		for( long n = 0; n < XX_ROTATION_MAX_N; n++ ){
			long x = xx_rotation.x[r][n];
			long y = xx_rotation.y[r][n];

			if( mapX > x )
				continue;
			if( mapY > y )
				continue;
			if( (mapX + mapW) < x )
				continue;
			if( (mapY + mapH) < y )
				continue;

			x = x * sizeX;
			y = y * sizeY;
			x += (sizeX / 2) - (w / 2);
			y += (sizeY / 2) - (h / 2);

			pcgXxRotation.draw( gPcgDun.getWBuf(), x, y, w, h );
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////
// XX の渦巻き弾の攻撃の描画
// long mapX : X 座標
// long mapY : Y 座標
// long mapW : 幅
// long mapH : 高さ
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GuiLastBoss::drawXxAttackWhirl(
	long mapX, long mapY, long mapW, long mapH )
{
	if( !gPcgDun.clipWin( mapX, mapY ) )
		return true;

	xx_whirl_t &xx_whirl = xxAttack.data.whirl;

	long sizeX = gPcgDun.getTileSizeX( false );
	long sizeY = gPcgDun.getTileSizeY( false );
	long w = pcgXxWhirl.getWidth();
	long h = pcgXxWhirl.getHeight();

	for( long n = 0; n < XX_WHIRL_MAX_N; n++ ){
		if( !xx_whirl.flg_move[n] )
			continue;

		long x = xx_whirl.x[n];
		long y = xx_whirl.y[n];

		if( mapX > x )
			continue;
		if( mapY > y )
			continue;
		if( (mapX + mapW) < x )
			continue;
		if( (mapY + mapH) < y )
			continue;

		x = x * sizeX;
		y = y * sizeY;
		x += (sizeX / 2) - (w / 2);
		y += (sizeY / 2) - (h / 2);

		pcgXxWhirl.draw( gPcgDun.getWBuf(), x, y, w, h );
	}

	return true;
}

////////////////////////////////////////////////////////////////
// XX の扇弾の攻撃の描画
// long mapX : X 座標
// long mapY : Y 座標
// long mapW : 幅
// long mapH : 高さ
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GuiLastBoss::drawXxAttackFan(
	long mapX, long mapY, long mapW, long mapH )
{
	if( !gPcgDun.clipWin( mapX, mapY ) )
		return true;

	xx_fan_t &xx_fan = xxAttack.data.fan;

	long sizeX = gPcgDun.getTileSizeX( false );
	long sizeY = gPcgDun.getTileSizeY( false );
	long w = pcgXxFan.getWidth();
	long h = pcgXxFan.getHeight();

	for( long n = 0; n < XX_FAN_MAX_N; n++ ){
		if( !xx_fan.flg_move[n] )
			continue;

		for( long m = 0; m < XX_FAN_MAX_WAY; m++ ){
			long x = xx_fan.x[n][m];
			long y = xx_fan.y[n][m];

			if( mapX > x )
				continue;
			if( mapY > y )
				continue;
			if( (mapX + mapW) < x )
				continue;
			if( (mapY + mapH) < y )
				continue;

			x = x * sizeX;
			y = y * sizeY;
			x += (sizeX / 2) - (w / 2);
			y += (sizeY / 2) - (h / 2);

			pcgXxFan.draw( gPcgDun.getWBuf(), x, y, w, h );
		}
	}

	return true;
}
