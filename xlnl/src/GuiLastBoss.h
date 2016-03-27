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
* $Id: GuiLastBoss.h,v 1.13 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_LAST_BOSS_H
#define GUI_LAST_BOSS_H	1

////////////////////////////////////////////////////////////////
// ラスボスの描画 (GUI)
////////////////////////////////////////////////////////////////

#include "last-boss.h"
#include "last-boss-prot.h"

#include "Pcg.h"

////////////////////////////////////////////////////////////////
// 攻撃
////////////////////////////////////////////////////////////////

union XxAttackData {
	xx_heat_t heat;
	xx_cold_t cold;
	xx_mind_t mind;
	xx_acid_t acid;
	xx_rotation_t rotation;
	xx_whirl_t whirl;
	xx_fan_t fan;
};

struct XxAttack {
	xx_act_kind_t kind;
	XxAttackData data;
};

////////////////////////////////////////////////////////////////

class GuiLastBoss {

	//////// プライベート・メンバー変数 ////////
private:

	// パターン
	Pcg pcgSkull;
	Pcg pcgJaw;
	Pcg pcgBody;
	Pcg pcgUpperArmLeft;
	Pcg pcgUpperArmRight;
	Pcg pcgForeArmLeft;
	Pcg pcgForeArmRight;
	Pcg pcgForeArmSlapLeft;
	Pcg pcgForeArmSlapRight;
	Pcg pcgHandLeft;
	Pcg pcgHandRight;
	Pcg pcgHandSlapLeft;
	Pcg pcgHandSlapRight;

	// XX の攻撃
	XxAttack xxAttack;
	Pcg pcgXxHeat;
	Pcg pcgXxCold;
	Pcg pcgXxBit;
	Pcg pcgXxMind;
	Pcg pcgXxAcid;
	Pcg pcgXxRotation;
	Pcg pcgXxWhirl;
	Pcg pcgXxFan;

	// 頭の座標

	long skullW;
	long skullH;
	long skullX;
	long skullY;

	// アゴの座標

	long jawW;
	long jawH;
	long jawX;
	long jawY;

	// アゴの座標 (開く)

	long jawOpenW;
	long jawOpenH;
	long jawOpenX;
	long jawOpenY;

	// 体の座標

	long bodyW;
	long bodyH;
	long bodyX;
	long bodyY;

	// 左上腕の座標

	long upperArmLeftW;
	long upperArmLeftH;
	long upperArmLeftX;
	long upperArmLeftY;

	// 右上腕の座標

	long upperArmRightW;
	long upperArmRightH;
	long upperArmRightX;
	long upperArmRightY;

	// 左前腕の座標

	long foreArmLeftW;
	long foreArmLeftH;
	long foreArmLeftX;
	long foreArmLeftY;

	// 左前腕の座標 (平手打ち)

	long foreArmSlapLeftW;
	long foreArmSlapLeftH;
	long foreArmSlapLeftX;
	long foreArmSlapLeftY;

	// 右前腕の座標

	long foreArmRightW;
	long foreArmRightH;
	long foreArmRightX;
	long foreArmRightY;

	// 右前腕の座標 (平手打ち)

	long foreArmSlapRightW;
	long foreArmSlapRightH;
	long foreArmSlapRightX;
	long foreArmSlapRightY;

	// 左手の座標

	long handLeftW;
	long handLeftH;
	long handLeftX;
	long handLeftY;

	// 左手の座標 (平手打ち)

	long handSlapLeftW;
	long handSlapLeftH;
	long handSlapLeftX;
	long handSlapLeftY;

	// 右手の座標

	long handRightW;
	long handRightH;
	long handRightX;
	long handRightY;

	// 右手の座標 (平手打ち)

	long handSlapRightW;
	long handSlapRightH;
	long handSlapRightX;
	long handSlapRightY;

	//////// パブリック・メンバー変数 ////////
public:

	//////// パブリック・メンバー関数 ////////
public:

	GuiLastBoss();
	~GuiLastBoss();
	void init();
	void initPcg( Pcg *pcg, WSCstring dirName );

	void setDraw();
	void drawBg();
	void drawFg();
	void drawPcg( Pcg *p, long x, long y, long w, long h );

	void setXxAttack( xx_act_kind_t kind, void *p );
	bool drawXxAttack(
		long mapX, long mapY, long mapW, long mapH );

	//////// プライベート・メンバー関数 ////////
private:

	bool drawXxAttackHeat(
		long mapX, long mapY, long mapW, long mapH );
	bool drawXxAttackCold(
		long mapX, long mapY, long mapW, long mapH );
	bool drawXxAttackMind(
		long mapX, long mapY, long mapW, long mapH );
	bool drawXxAttackAcid(
		long mapX, long mapY, long mapW, long mapH );
	bool drawXxAttackRotation(
		long mapX, long mapY, long mapW, long mapH );
	bool drawXxAttackWhirl(
		long mapX, long mapY, long mapW, long mapH );
	bool drawXxAttackFan(
		long mapX, long mapY, long mapW, long mapH );
};

#endif // GUI_LAST_BOSS_H
