/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ����ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�����
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�����ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ����Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: GuiLastBoss.h,v 1.13 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_LAST_BOSS_H
#define GUI_LAST_BOSS_H	1

////////////////////////////////////////////////////////////////
// �饹�ܥ������� (GUI)
////////////////////////////////////////////////////////////////

#include "last-boss.h"
#include "last-boss-prot.h"

#include "Pcg.h"

////////////////////////////////////////////////////////////////
// ����
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

	//////// �ץ饤�١��ȡ����С��ѿ� ////////
private:

	// �ѥ�����
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

	// XX �ι���
	XxAttack xxAttack;
	Pcg pcgXxHeat;
	Pcg pcgXxCold;
	Pcg pcgXxBit;
	Pcg pcgXxMind;
	Pcg pcgXxAcid;
	Pcg pcgXxRotation;
	Pcg pcgXxWhirl;
	Pcg pcgXxFan;

	// Ƭ�κ�ɸ

	long skullW;
	long skullH;
	long skullX;
	long skullY;

	// �����κ�ɸ

	long jawW;
	long jawH;
	long jawX;
	long jawY;

	// �����κ�ɸ (����)

	long jawOpenW;
	long jawOpenH;
	long jawOpenX;
	long jawOpenY;

	// �Τκ�ɸ

	long bodyW;
	long bodyH;
	long bodyX;
	long bodyY;

	// �����Ӥκ�ɸ

	long upperArmLeftW;
	long upperArmLeftH;
	long upperArmLeftX;
	long upperArmLeftY;

	// �����Ӥκ�ɸ

	long upperArmRightW;
	long upperArmRightH;
	long upperArmRightX;
	long upperArmRightY;

	// �����Ӥκ�ɸ

	long foreArmLeftW;
	long foreArmLeftH;
	long foreArmLeftX;
	long foreArmLeftY;

	// �����Ӥκ�ɸ (ʿ���Ǥ�)

	long foreArmSlapLeftW;
	long foreArmSlapLeftH;
	long foreArmSlapLeftX;
	long foreArmSlapLeftY;

	// �����Ӥκ�ɸ

	long foreArmRightW;
	long foreArmRightH;
	long foreArmRightX;
	long foreArmRightY;

	// �����Ӥκ�ɸ (ʿ���Ǥ�)

	long foreArmSlapRightW;
	long foreArmSlapRightH;
	long foreArmSlapRightX;
	long foreArmSlapRightY;

	// ����κ�ɸ

	long handLeftW;
	long handLeftH;
	long handLeftX;
	long handLeftY;

	// ����κ�ɸ (ʿ���Ǥ�)

	long handSlapLeftW;
	long handSlapLeftH;
	long handSlapLeftX;
	long handSlapLeftY;

	// ����κ�ɸ

	long handRightW;
	long handRightH;
	long handRightX;
	long handRightY;

	// ����κ�ɸ (ʿ���Ǥ�)

	long handSlapRightW;
	long handSlapRightH;
	long handSlapRightX;
	long handSlapRightY;

	//////// �ѥ֥�å������С��ѿ� ////////
public:

	//////// �ѥ֥�å������С��ؿ� ////////
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

	//////// �ץ饤�١��ȡ����С��ؿ� ////////
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
