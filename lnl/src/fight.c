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
* $Id: fight.c,v 1.180 2014/03/13 18:30:01 bowkenken Exp $
***************************************************************/

/***************************************************************
* 戦闘
***************************************************************/

#define	FIGHT_C
#include	"inc.h"

/***************************************************************
* レベルと武器、防具の強さ
***************************************************************/

#if	1
/* レベルが低い時ほど強力 */
/* レベルが上がれば上がるほど差が無くなる */
# define	FLG_ITEM_ADD_RATE	1
#else
/* レベルが低い時は差が無い */
/* レベルが上がれば上がるほど強力になる */
# define	FLG_ITEM_ADD_RATE	0
#endif

/***************************************************************
* レベルと武器、防具の強さの基準値
***************************************************************/

/* 攻撃側の当りやすさ */

#define	HIT_ADJ_RATE	((rate_t)100)

/* 攻撃能力の平均値 */

#define	HIT_AVE_N	10
#define	WPN_CRTCL_AVE_N	20
#define	DAM_AVE_N	10

/* 防御能力の平均値 */

#define	DEF_AVE_N	10
#define	ARMOR_CRTCL_AVE_N	10
#define	AC_AVE_N	20

#define	DEF_MIN_RATE	((rate_t)30)

/* 攻撃能力の修正率 */

#define	ADD_HIT_RATE	((rate_t)10)
#define	ADD_WPN_CRTCL_RATE	((rate_t)10)
#define	ADD_DAM_RATE	((rate_t)10)

#define	TWO_HANDED_WPN_ADD_DAM_RATE	((rate_t)120)

/* 防御能力の修正率 */

#define	ADD_DEF_RATE	((rate_t)10)
#define	ADD_ARMOR_CRTCL_RATE	((rate_t)10)
#define	ADD_AC_RATE	((rate_t)10)

/* モンクのレベルを装備に換算する値 */

#define	HIT_MON_MUL	6
#define	HIT_MON_ADD	2
#define	DAM_MON_MUL	6
#define	DAM_MON_ADD	2
#define	DEF_MON_MUL	6
#define	DEF_MON_ADD	2

/* シーフのクリティカル・ヒット率 */

#define	WPN_CRTCL_THF_LEV_RATE	((rate_t)30)
#define	WPN_CRTCL_THF_MAX_RATE	((rate_t)30)

/* 忍者の首切り率 */

#define	NINJA_CRTCL_RATE	((rate_t)150)

/* 「〜殺し」「〜防御」の率 */

#define	KILLER_RATE	((rate_t)150)
#define	BANE_RATE	((rate_t)150)
#define	SLAYER_RATE	((rate_t)150)

#define	BLOCK_RATE	((rate_t)75)
#define	GUARD_RATE	((rate_t)75)
#define	PROTECT_RATE	((rate_t)75)

/* 防御中(何もしていない時)の防御力アップ率 */

#define	DEF_DEF_RATE	((rate_t)150)
#define	DEF_AC_RATE	((rate_t)150)

/* 魔法の杖の攻撃力 */

#define	DAM_STICK_RATE	((rate_t)300)
#define	DAM_STICK_ADD	10

/* 呪文の攻撃力 */

#define	DAM_SPELL_RATE	((rate_t)200)
#define	DAM_SPELL_ADD	10

/* オブジェクトの防御力 */

#define	DOOR_DEF	12
#define	TRAP_DEF	8
#define	ITEM_DEF	6

/* 遠隔攻撃力の距離によって減る率 */

#define	RATE_PER_RANGE	((rate_t)200)

/* メンバー同士の訓練時に入る経験値 */

#define	TRAINING_EXP	1

/***************************************************************
* 素手の場合の攻撃データ
***************************************************************/

static attack_t	mbr_attack_bash[] = {
	{ ATTACK_KIND_PUNCH, 1, FALSE, TRUE,
		WPN_HIT_UNARMED, WPN_CRTCL_UNARMED, WPN_DAM_UNARMED,
		RESI_KIND_KNOC, 1, 1,
		FX_KIND_NULL, 0,
		SPELL_KIND_NULL,
		EXTENT_KIND_NULL, N_MSG_NULL, },
	{ ATTACK_KIND_KICK, 1, FALSE, TRUE,
		WPN_HIT_UNARMED, WPN_CRTCL_UNARMED, WPN_DAM_UNARMED,
		RESI_KIND_KNOC, 1, 1,
		FX_KIND_NULL, 0,
		SPELL_KIND_NULL,
		EXTENT_KIND_NULL, N_MSG_NULL, },
	{ ATTACK_KIND_NULL, 0, FALSE, FALSE,
		0, 0, 0,
		RESI_KIND_MAX_N, 1, 1,
		FX_KIND_NULL, 0,
		SPELL_KIND_NULL,
		EXTENT_KIND_NULL, N_MSG_NULL, },
};
check_memory_def( check_memory_fight_c_mbr_attack_bash )

/***************************************************************
* アイテムを投げる場合の攻撃データ
***************************************************************/

static attack_t	mbr_attack_throw[] = {
	{ ATTACK_KIND_THROW, 1, TRUE, FALSE,
		WPN_HIT_UNARMED, WPN_CRTCL_UNARMED, WPN_DAM_UNARMED,
		RESI_KIND_KNOC, 1, 10,
		FX_KIND_NULL, 0,
		SPELL_KIND_NULL,
		EXTENT_KIND_NULL, N_MSG_NULL, },
	{ ATTACK_KIND_NULL, 0, FALSE, FALSE,
		0, 0, 0,
		RESI_KIND_MAX_N, 1, 1,
		FX_KIND_NULL, 0,
		SPELL_KIND_NULL,
		EXTENT_KIND_NULL, N_MSG_NULL, },
};
check_memory_def( check_memory_fight_c_mbr_attack_throw )

/***************************************************************
* 明かりを投げる場合の攻撃データ
***************************************************************/

static attack_t	mbr_attack_throw_light[] = {
	{ ATTACK_KIND_THROW, 1, TRUE, FALSE,
		WPN_HIT_UNARMED, WPN_CRTCL_UNARMED, WPN_DAM_UNARMED,
		RESI_KIND_HEAT, 1, 10,
		FX_KIND_NULL, 0,
		SPELL_KIND_NULL,
		EXTENT_KIND_NULL, N_MSG_NULL, },
	{ ATTACK_KIND_NULL, 0, FALSE, FALSE,
		0, 0, 0,
		RESI_KIND_MAX_N, 1, 1,
		FX_KIND_NULL, 0,
		SPELL_KIND_NULL,
		EXTENT_KIND_NULL, N_MSG_NULL, },
};
check_memory_def( check_memory_fight_c_mbr_attack_throw_light )

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_fight( void )
{
}

/***************************************************************
* 近接攻撃
* chr_t *chr : 攻撃側キャラクタ
* chr_t *chr2 : 防御側キャラクタ
* attack_t *dflt_attack : デフォルトの攻撃データ
* return : 攻撃成功か?
***************************************************************/

bool_t	fight_bash( chr_t *chr, chr_t *chr2, attack_t *dflt_attack )
{
	attack_t	attack;
	long	d;

	if( chr == NULL )
		return FALSE;
	if( chr2 == NULL )
		return FALSE;

	d = get_trgt_range( chr );

	if( dflt_attack == NULL ){
		if( !set_attack_chr_bash( chr, &attack, 1, FALSE ) )
			return FALSE;
	} else {
		attack = *dflt_attack;
	}

	return fight( chr, chr2, &attack, d );
}

/***************************************************************
* 近接攻撃データを設定
* chr_t *chr : 攻撃側キャラクタ
* attack_t *attack : 攻撃データを返す
* long range : 距離
* bool_t flg_ave : 平均値を返すか?
* return : 攻撃出来るか?
***************************************************************/

bool_t	set_attack_chr_bash(
	chr_t *chr, attack_t *attack, long range, bool_t flg_ave
)
{
	if( is_mbr( chr ) )
		return set_attack_mbr_bash( chr, attack, range, flg_ave );
	if( chr->kind == CHR_KIND_MNSTR )
		return set_attack_mnstr_bash( chr, attack, range, flg_ave );

	return FALSE;
}

/***************************************************************
* メンバーの近接攻撃データを設定
* mbr_t *mbr : 攻撃側メンバー
* attack_t *attack : 攻撃データを返す
* long range : 距離
* bool_t flg_ave : 平均値を返すか?
* return : 攻撃出来るか?
***************************************************************/

bool_t	set_attack_mbr_bash(
	mbr_t *mbr, attack_t *attack, long range, bool_t flg_ave
)
{
	item_t	*eq;
	wpn_tab_t	*wpn_tab;
	attack_t	*p;

	if( attack == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	/* 武器のテーブルを得る */
	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;

	eq = &(eq[EQUIP_KIND_WIELDING]);
	if( eq->kind == ITEM_KIND_WPN )
		wpn_tab = eq->tab.wpn;
	else
		wpn_tab = NULL;

	if( wpn_tab == NULL ){
		/* 素手の場合 */
		p = get_attack( flg_ave, mbr_attack_bash, range,
				FALSE, TRUE, FALSE, FALSE );
		if( p == NULL )
			return FALSE;
		*attack = *p;
	} else {
		/* 武器の場合 */
		p = get_attack( flg_ave, wpn_tab->attack, range,
				TRUE, TRUE, FALSE, FALSE );
		if( p == NULL )
			return FALSE;
		*attack = *p;

		attack->hit += add_hit( eq->dat.wpn.add_hit );
		attack->crtcl += add_wpn_crtcl( eq->dat.wpn.add_crtcl );
		attack->dam += add_dam( eq->dat.wpn.add_dam );
		attack->dam = attack->dam
				* add_dam_two_handed_wpn( mbr, eq )
				/ _100_PERCENT;
	}

	return TRUE;
}

/***************************************************************
* モンスターの近接攻撃データを設定
* mnstr_t *mnstr : 攻撃側モンスター
* attack_t *attack : 攻撃データを返す
* long range : 距離
* bool_t flg_ave : 平均値を返すか?
* return : 攻撃出来るか?
***************************************************************/

bool_t	set_attack_mnstr_bash(
	mnstr_t *mnstr, attack_t *attack, long range, bool_t flg_ave
)
{
	attack_t	*p;

	if( attack == NULL )
		return FALSE;
	if( mnstr == NULL )
		return FALSE;
	if( mnstr->kind != CHR_KIND_MNSTR )
		return FALSE;

	if( mnstr->mnstr_tab == NULL )
		return FALSE;

	p = get_attack( flg_ave, mnstr->mnstr_tab->attack, range,
			TRUE, TRUE, FALSE, FALSE );
	if( p == NULL )
		return FALSE;

	*attack = *p;

	return TRUE;
}

/***************************************************************
* 遠隔攻撃
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* attack_t *dflt_attack : デフォルトの攻撃データ
* return : 攻撃成功か?
***************************************************************/

bool_t	fight_throw( chr_t *o_p, chr_t *d_p, attack_t *dflt_attack )
{
	attack_t	attack;
	long	d;

	if( o_p == NULL )
		return FALSE;

	/* check stick */
	if( chk_fight_zap( o_p ) )
		return fight_zap( o_p );

	d = get_trgt_range( o_p );

	if( dflt_attack == NULL ){
		if( !set_attack_chr_throw( o_p, &attack, d, FALSE ) )
			return FALSE;
	} else {
		attack = *dflt_attack;
	}

	return fight( o_p, d_p, &attack, d );
}

/***************************************************************
* 杖を装備しているかチェック
* mbr_t *mbr : メンバー
* return : 杖を装備しているか?
***************************************************************/

bool_t	chk_fight_zap( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;
	if( eq[EQUIP_KIND_ARW].kind != ITEM_KIND_NULL )
		return FALSE;
	if( eq[EQUIP_KIND_BOW].kind != ITEM_KIND_STICK )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 杖で攻撃
* mbr_t *mbr : メンバー
* return : 攻撃成功か?
***************************************************************/

bool_t	fight_zap( mbr_t *mbr )
{
	item_t	*eq;

	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;

	if( !zap_stick( mbr, &(eq[EQUIP_KIND_BOW]) ) )
		clr_chr_trgt_act( mbr, FALSE );

	return TRUE;
}

/***************************************************************
* 遠隔攻撃データを設定
* chr_t *chr : 攻撃側キャラクタ
* attack_t *attack : 攻撃データを返す
* long range : 距離
* bool_t flg_ave : 平均値を返すか?
* return : 攻撃出来るか?
***************************************************************/

bool_t	set_attack_chr_throw(
	chr_t *chr, attack_t *attack, long range, bool_t flg_ave
)
{
	if( is_mbr( chr ) )
		return set_attack_mbr_throw( chr, attack, range, flg_ave );
	if( chr->kind == CHR_KIND_MNSTR )
		return set_attack_mnstr_throw( chr, attack, range, flg_ave );

	return FALSE;
}

/***************************************************************
* メンバーの遠隔攻撃データを設定
* mbr_t *mbr : 攻撃側メンバー
* attack_t *attack : 攻撃データを返す
* long range : 距離
* bool_t flg_ave : 平均値を返すか?
* return : 攻撃出来るか?
***************************************************************/

bool_t	set_attack_mbr_throw(
	mbr_t *mbr, attack_t *attack, long range, bool_t flg_ave
)
{
	item_t	*eq;
	wpn_tab_t	*bow_tab, *arw_tab;
	attack_t	*p;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;
	if( attack == NULL )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;

	/* 武器のテーブルを得る */

	if( eq[EQUIP_KIND_BOW].kind == ITEM_KIND_WPN )
		bow_tab = eq[EQUIP_KIND_BOW].tab.wpn;
	else
		bow_tab = NULL;
	if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_WPN )
		arw_tab = eq[EQUIP_KIND_ARW].tab.wpn;
	else
		arw_tab = NULL;

	if( chk_dagger( arw_tab ) ){
		/* ダガーの場合 */

		p = get_attack( flg_ave, arw_tab->attack, range,
				FALSE, FALSE, TRUE, FALSE );
		if( p == NULL )
			return FALSE;
		*attack = *p;

		attack->hit += add_hit( eq[EQUIP_KIND_ARW]
				.dat.wpn.add_hit );
		attack->crtcl += add_wpn_crtcl( eq[EQUIP_KIND_ARW]
				.dat.wpn.add_crtcl );
		attack->dam += add_dam( eq[EQUIP_KIND_ARW]
				.dat.wpn.add_dam );
	} else if( chk_bow( arw_tab, bow_tab ) ){
		attack_t	attack_bow, attack_arw;
		/* 弓などの場合 */

		/* bow */

		p = get_attack( flg_ave, bow_tab->attack, range,
				FALSE, FALSE, TRUE, FALSE );
		if( p == NULL )
			return FALSE;
		attack_bow = *p;

		attack_bow.hit += add_hit( eq[EQUIP_KIND_BOW]
				.dat.wpn.add_hit );
		attack_bow.crtcl += add_wpn_crtcl( eq[EQUIP_KIND_BOW]
				.dat.wpn.add_crtcl );
		attack_bow.dam += add_dam( eq[EQUIP_KIND_BOW]
				.dat.wpn.add_dam );

		/* arrow */

		p = get_attack( flg_ave, arw_tab->attack, range,
				FALSE, FALSE, TRUE, FALSE );
		if( p == NULL )
			return FALSE;
		attack_arw = *p;

		attack_arw.hit += add_hit( eq[EQUIP_KIND_ARW]
				.dat.wpn.add_hit );
		attack_arw.crtcl += add_wpn_crtcl( eq[EQUIP_KIND_ARW]
				.dat.wpn.add_crtcl );
		attack_arw.dam += add_dam( eq[EQUIP_KIND_ARW]
				.dat.wpn.add_dam );

		/* sum */

		*attack = attack_bow;
		attack->hit += attack_arw.hit;
		attack->crtcl += attack_arw.crtcl;
		attack->dam += attack_arw.dam;
	} else {
		/* その他のアイテムの場合 */

		if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_LIGHT ){
			p = get_attack( flg_ave,
					mbr_attack_throw_light, range,
					FALSE, FALSE, TRUE, FALSE );
		} else {
			p = get_attack( flg_ave,
					mbr_attack_throw, range,
					FALSE, FALSE, TRUE, FALSE );
		}
		if( p == NULL )
			return FALSE;
		*attack = *p;
	}

	return TRUE;
}

/***************************************************************
* モンスターの遠隔攻撃データを設定
* mnstr_t *mnstr : 攻撃側モンスター
* attack_t *attack : 攻撃データを返す
* long range : 距離
* bool_t flg_ave : 平均値を返すか?
* return : 攻撃出来るか?
***************************************************************/

bool_t	set_attack_mnstr_throw(
	mnstr_t *mnstr, attack_t *attack, long range, bool_t flg_ave
)
{
	attack_t	*p;

	if( mnstr == NULL )
		return FALSE;
	if( mnstr->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( mnstr->mnstr_tab == NULL )
		return FALSE;
	if( attack == NULL )
		return FALSE;

	p = get_attack( flg_ave, mnstr->mnstr_tab->attack, range,
			FALSE, FALSE, TRUE, FALSE );
	if( p == NULL )
		return FALSE;

	*attack = *p;

	return TRUE;
}

/***************************************************************
* 攻撃データの自動選択
* bool_t flg_ave : 平均値か?
* attack_t *ls : 攻撃データのテーブル
* long range : 距離
* bool_t flg_bash : 近接攻撃を選択候補に含むか?
* bool_t flg_monk : 格闘攻撃を選択候補に含むか?
* bool_t flg_throw : 遠隔攻撃を選択候補に含むか?
* bool_t flg_spell : 呪文攻撃を選択候補に含むか?
* return : 選択された攻撃データ
***************************************************************/

attack_t	*get_attack(
	bool_t flg_ave, attack_t *ls, long range,
	bool_t flg_bash, bool_t flg_monk,
	bool_t flg_throw, bool_t flg_spell
)
{
	if( flg_ave ){
		return( get_attack_ave( ls, range,
				flg_bash, flg_monk,
				flg_throw, flg_spell ) );
	} else {
		return( get_attack_randm( ls, range,
				flg_bash, flg_monk,
				flg_throw, flg_spell ) );
	}
}

/***************************************************************
* 平均的な攻撃データの自動選択
* attack_t *ls : 攻撃データのテーブル
* long range : 距離
* bool_t flg_bash : 近接攻撃を選択候補に含むか?
* bool_t flg_monk : 格闘攻撃を選択候補に含むか?
* bool_t flg_throw : 遠隔攻撃を選択候補に含むか?
* bool_t flg_spell : 呪文攻撃を選択候補に含むか?
* return : 選択された攻撃データ
***************************************************************/

attack_t	*get_attack_ave(
	attack_t *ls, long range,
	bool_t flg_bash, bool_t flg_monk,
	bool_t flg_throw, bool_t flg_spell
)
{
	long	i;
	ratio_t	n, sum;
	static attack_t	ave;

	if( ls == NULL )
		return NULL;

	ave.kind = ATTACK_KIND_NULL;
	ave.ratio = 1;
	ave.resi_kind = RESI_KIND_MAX_N;
	ave.flg_throw = flg_throw;
	ave.flg_monk = flg_monk;
	ave.hit = 0;
	ave.crtcl = 0;
	ave.dam = 0;

	sum = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].kind == ATTACK_KIND_NULL )
			break;

		if( ls[i].kind == ATTACK_KIND_SPELL ){
			if( !flg_spell )
				continue;
		} else if( ls[i].kind == ATTACK_KIND_SPELL_SELF ){
			if( !flg_spell )
				continue;
		} else if( ls[i].kind == ATTACK_KIND_SPELL_FRIEND ){
			if( !flg_spell )
				continue;
		} else if( ls[i].flg_monk ){
			if( !flg_monk )
				continue;
		} else if( ls[i].flg_throw ){
			if( !flg_throw )
				continue;
			if( ls[i].range_throw < range )
				continue;
		} else {
			if( !flg_bash )
				continue;
			if( ls[i].range_bash < range )
				continue;
		}

		n = ls[i].ratio;
		sum += n;
		ave.hit += ls[i].hit * n;
		ave.crtcl += ls[i].crtcl * n;
		ave.dam += ls[i].dam * n;

		ave.flg_throw = ls[i].flg_throw;
		ave.flg_monk = ls[i].flg_monk;
	}

	if( sum <= 0 )
		return NULL;

	ave.hit /= sum;
	ave.crtcl /= sum;
	ave.dam /= sum;

	return &ave;
}

/***************************************************************
* ランダムな攻撃データの自動選択
* attack_t *ls : 攻撃データのテーブル
* long range : 距離
* bool_t flg_bash : 近接攻撃を選択候補に含むか?
* bool_t flg_monk : 格闘攻撃を選択候補に含むか?
* bool_t flg_throw : 遠隔攻撃を選択候補に含むか?
* bool_t flg_spell : 呪文攻撃を選択候補に含むか?
* return : 選択された攻撃データ
***************************************************************/

attack_t	*get_attack_randm(
	attack_t *ls, long range,
	bool_t flg_bash, bool_t flg_monk,
	bool_t flg_throw, bool_t flg_spell
)
{
	long	i;
	ratio_t	n, sum;

	if( ls == NULL )
		return NULL;

	sum = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].kind == ATTACK_KIND_NULL )
			break;

		if( ls[i].kind == ATTACK_KIND_SPELL ){
			if( !flg_spell )
				continue;
		} else if( ls[i].kind == ATTACK_KIND_SPELL_SELF ){
			if( !flg_spell )
				continue;
		} else if( ls[i].kind == ATTACK_KIND_SPELL_FRIEND ){
			if( !flg_spell )
				continue;
		} else if( ls[i].flg_monk ){
			if( !flg_monk )
				continue;
		} else if( ls[i].flg_throw ){
			if( !flg_throw )
				continue;
			if( ls[i].range_throw < range )
				continue;
		} else {
			if( !flg_bash )
				continue;
			if( ls[i].range_bash < range )
				continue;
		}

		sum += ls[i].ratio;
	}

	if( sum <= 0 )
		return NULL;

	n = randm( sum );

	sum = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].kind == ATTACK_KIND_NULL )
			break;
		if( ls[i].kind == ATTACK_KIND_SPELL ){
			if( !flg_spell )
				continue;
		} else if( ls[i].kind == ATTACK_KIND_SPELL_SELF ){
			if( !flg_spell )
				continue;
		} else if( ls[i].kind == ATTACK_KIND_SPELL_FRIEND ){
			if( !flg_spell )
				continue;
		} else if( ls[i].flg_monk ){
			if( !flg_monk )
				continue;
		} else if( ls[i].flg_throw ){
			if( !flg_throw )
				continue;
		} else {
			if( !flg_bash )
				continue;
		}

		sum += ls[i].ratio;
		if( sum > n )
			return( &(ls[i]) );
	}

	return NULL;
}

/***************************************************************
* 攻撃力の合計比率を計算
* attack_t *ls : 攻撃データのテーブル
* bool_t flg_bash : 近接攻撃を選択候補に含むか?
* bool_t flg_monk : 格闘攻撃を選択候補に含むか?
* bool_t flg_throw : 遠隔攻撃を選択候補に含むか?
* bool_t flg_spell : 呪文攻撃を選択候補に含むか?
* return : 攻撃力の合計比率
***************************************************************/

ratio_t	calc_attack_sum(
	attack_t *ls,
	bool_t flg_bash, bool_t flg_monk,
	bool_t flg_throw, bool_t flg_spell
)
{
	ratio_t	sum;
	long	i;

	if( ls == NULL )
		return 0;

	sum = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].kind == ATTACK_KIND_NULL )
			break;
		if( ls[i].kind == ATTACK_KIND_SPELL ){
			if( !flg_spell )
				continue;
		} else if( ls[i].kind == ATTACK_KIND_SPELL_SELF ){
			if( !flg_spell )
				continue;
		} else if( ls[i].kind == ATTACK_KIND_SPELL_FRIEND ){
			if( !flg_spell )
				continue;
		} else if( ls[i].flg_monk ){
			if( !flg_monk )
				continue;
		} else if( ls[i].flg_throw ){
			if( !flg_throw )
				continue;
		} else {
			if( !flg_bash )
				continue;
		}

		sum += ls[i].ratio;
	}

	return sum;
}

/***************************************************************
* 戦闘
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* const attack_t *attack : 攻撃データ
* long range : 距離
* return : 攻撃成功か?
***************************************************************/

bool_t	fight(
	chr_t *o_p, chr_t *d_p,
	const attack_t *attack, long range
)
{
	long	attack_n;
	long	hit_n;
	long	i;

	attack_n = calc_attack_n( o_p, attack );

	/* コンボの表示 */

	if( (o_p != NULL) && (attack_n >= 2) ){
		curs_attrset_chr( d_p, -1, FALSE );
		print_msg( FLG_NULL, MSG_FIGHT_COMBO, o_p->name, attack_n );
		curs_attrset_dflt();
	}

	/* begin */
	bgn_sync_vfx_num();

	hit_n = 0;
	for( i = 0; i < attack_n; i++ ){
		if( fight_x_1( o_p, d_p, attack, range, FALSE ) ){
			hit_n++;
		} else if( fight_two_sword_fencing( o_p, d_p,
				attack, range ) ){
			hit_n++;
		}
	}

	/* end */
	end_sync_vfx_num();

	if( hit_n < 1 )
		return FALSE;

	/* カウンター */

	fight_counter( d_p, o_p );

	return TRUE;
}

/***************************************************************
* 攻撃回数を計算
* chr_t *o_p : 攻撃側キャラクタ
* const attack_t *attack : 攻撃データ
* return : 攻撃回数
***************************************************************/

long	calc_attack_n( chr_t *o_p, const attack_t *attack )
{
	if( o_p == NULL )
		return 0;
	if( attack == NULL )
		return 0;

	if( attack->flg_throw )
		return calc_attack_n_hun( o_p, attack );
	else if( attack->flg_monk )
		return calc_attack_n_mon( o_p, attack );
	else
		return calc_attack_n_fig( o_p, attack );
}

/***************************************************************
* 攻撃回数を計算 (近接)
* chr_t *o_p : 攻撃側キャラクタ
* const attack_t *attack : 攻撃データ
* return : 攻撃回数
***************************************************************/

long	calc_attack_n_fig( chr_t *o_p, const attack_t *attack )
{
	abl_kind_t	abl;
	long	lev;
	rate_t	rate;

	if( o_p == NULL )
		return SKILL_COMBO_MIN_N;
	if( !is_mbr( o_p ) )
		return SKILL_COMBO_MIN_N;
	if( attack == NULL )
		return SKILL_COMBO_MIN_N;
	if( attack->flg_throw )
		return SKILL_COMBO_MIN_N;
	if( attack->flg_monk )
		return SKILL_COMBO_MIN_N;

	if( !chk_ena_skill( o_p, SKILL_KIND_DOUBLE_ATTACK ) )
		return SKILL_COMBO_MIN_N;

	abl = (abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DOUBLE_ATTACK);
	lev = get_lev( o_p, abl );
	rate = SKILL_FIG_BASE_RATE;
	rate += SKILL_FIG_ADD_RATE * lev;

	print_msg( FLG_MSG_DEBUG, "FIG combo rate: %ld", rate );

	return count_randm_rate( rate );
}

/***************************************************************
* 攻撃回数を計算 (格闘)
* chr_t *o_p : 攻撃側キャラクタ
* const attack_t *attack : 攻撃データ
* return : 攻撃回数
***************************************************************/

long	calc_attack_n_mon( chr_t *o_p, const attack_t *attack )
{
	abl_kind_t	abl;
	long	lev;
	rate_t	rate;

	if( o_p == NULL )
		return SKILL_COMBO_MIN_N;
	if( !is_mbr( o_p ) )
		return SKILL_COMBO_MIN_N;
	if( attack == NULL )
		return SKILL_COMBO_MIN_N;
	if( !attack->flg_monk )
		return SKILL_COMBO_MIN_N;

	if( !chk_ena_skill( o_p, SKILL_KIND_COMBO ) )
		return SKILL_COMBO_MIN_N;

	abl = (abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_COMBO);
	lev = get_lev( o_p, abl );
	rate = SKILL_MON_BASE_RATE;
	rate += SKILL_MON_ADD_RATE * lev;

	print_msg( FLG_MSG_DEBUG, "MON combo rate: %ld", rate );

	return count_randm_rate( rate );
}

/***************************************************************
* 攻撃回数を計算 (射撃)
* chr_t *o_p : 攻撃側キャラクタ
* const attack_t *attack : 攻撃データ
* return : 攻撃回数
***************************************************************/

long	calc_attack_n_hun( chr_t *o_p, const attack_t *attack )
{
	abl_kind_t	abl;
	long	lev;
	rate_t	rate;

	if( o_p == NULL )
		return SKILL_COMBO_MIN_N;
	if( !is_mbr( o_p ) )
		return SKILL_COMBO_MIN_N;
	if( attack == NULL )
		return SKILL_COMBO_MIN_N;
	if( !attack->flg_throw )
		return SKILL_COMBO_MIN_N;

	if( !chk_ena_skill( o_p, SKILL_KIND_RAPID_SHOOT ) )
		return SKILL_COMBO_MIN_N;

	abl = (abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RAPID_SHOOT);
	lev = get_lev( o_p, abl );
	rate = SKILL_HUN_BASE_RATE;
	rate += SKILL_HUN_ADD_RATE * lev;

	print_msg( FLG_MSG_DEBUG, "HUN combo rate: %ld", rate );

	return count_randm_rate( rate );
}

/***************************************************************
* カウンターの反撃回数を計算
* chr_t *d_p : 反撃側キャラクタ
* return : 反撃回数
***************************************************************/

long	calc_counter_n( chr_t *d_p )
{
	abl_kind_t	abl;
	long	lev;
	rate_t	rate;

	if( d_p == NULL )
		return SKILL_COUNTER_MIN_N;
	if( !is_mbr( d_p ) )
		return SKILL_COUNTER_MIN_N;

	if( !chk_ena_skill( d_p, SKILL_KIND_COUNTER ) )
		return SKILL_COUNTER_MIN_N;

	if( get_def_abl( d_p ) != ABL_KIND_MON )
		return SKILL_COUNTER_MIN_N;

	abl = (abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_COUNTER);
	lev = get_lev( d_p, abl );
	rate = SKILL_COUNTER_BASE_RATE;
	rate += SKILL_COUNTER_ADD_RATE * lev;

	print_msg( FLG_MSG_DEBUG, "counter rate: %ld", rate );

	return count_randm_rate( rate );
}

/***************************************************************
* 二刀流の予備攻撃回数を計算
* chr_t *o_p : 攻撃側キャラクタ
* const attack_t *attack : 攻撃データ
* return : 攻撃回数
***************************************************************/

long	calc_two_sword_fencing_n( chr_t *o_p, const attack_t *attack )
{
	item_t	*eq;
	abl_kind_t	abl;
	long	lev;
	rate_t	rate;
	long	min_n;

	min_n = SKILL_TWO_SWORD_FENCING_MIN_N;

	if( o_p == NULL )
		return min_n;
	if( !is_mbr( o_p ) )
		return min_n;
	if( attack == NULL )
		return min_n;
	if( attack->flg_throw )
		return min_n;
	if( attack->flg_monk )
		return min_n;

	if( !chk_ena_skill( o_p, SKILL_KIND_TWO_SWORD_FENCING ) )
		return min_n;

	eq = get_mbr_item_asgn_equip( (mbr_t *)o_p );
	if( eq == NULL )
		return min_n;
	if( eq[EQUIP_KIND_WIELDING].kind != ITEM_KIND_WPN )
		return min_n;
	if( eq[EQUIP_KIND_SHIELD].kind != ITEM_KIND_WPN )
		return min_n;

	abl = (abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_TWO_SWORD_FENCING);
	lev = get_lev( o_p, abl );
	rate = SKILL_TWO_SWORD_FENCING_BASE_RATE;
	rate += SKILL_TWO_SWORD_FENCING_ADD_RATE * lev;

	print_msg( FLG_MSG_DEBUG, "2 sword rate: %ld", rate );

	return count_randm_rate( rate );
}

/***************************************************************
* 1 回分の戦闘
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* const attack_t *attack : 攻撃データ
* long range : 距離
* bool_t flg_counter : カウンター指定
* return : 攻撃成功か?
***************************************************************/

bool_t	fight_x_1(
	chr_t *o_p, chr_t *d_p,
	const attack_t *attack, long range,
	bool_t flg_counter
)
{
	chr_kind_t	o_k, d_k;
	long	o_hit, o_dam, o_dam_real;
	rate_t	o_crtcl;
	static char	o_name[CHR_NAME_MAX_BYTE + 1];
	static char	d_name[CHR_NAME_MAX_BYTE + 1];
	rate_t	o_skill_dam;
	long	d_def, d_ac;
	rate_t	d_resi;
	abl_val_t	*d_hp;
	long	d_x, d_y;
	rate_t	o_cont, d_cont;
	flg_stat_t	stat;
	item_t	*eq;
	pos_t	bgn, end;
	gui_vfx_t	*gui_vfx;
	long	dir_n;
	bool_t	flg_crtcl, flg_ninja_crtcl;
	bool_t	flg_dead;
	bool_t	flg_d_null;
	bool_t	flg_auto_hit;
	bool_t	flg_serious;
	bool_t	flg_err_range;
	bool_t	flg_catch_food;
	char	mjr, mnr;
	item_t	arw;
	wpn_tab_t	*bow_tab, *arw_tab;
	sound_kind_t	sk;

	if( attack == NULL )
		return FALSE;

	if( o_p == NULL )
		return FALSE;
	else
		o_k = o_p->kind;

	if( d_p == NULL )
		d_k = CHR_KIND_MNSTR;
	else
		d_k = d_p->kind;

	flg_d_null = FALSE;
	if( d_p == NULL ){
		flg_d_null = TRUE;
	} else {
		if( d_k == CHR_KIND_MNSTR )
			if( ((mnstr_t *)d_p)->mnstr_tab == NULL )
				flg_d_null = TRUE;
	}
	if( is_mbr( o_p ) )
		if( ((mbr_t *)o_p)->trgt.kind == TRGT_KIND_MNSTR_NULL )
			flg_d_null = TRUE;

	/* 攻撃側の名前の取得 */

	str_nz_cpy( o_name, o_p->name, CHR_NAME_MAX_BYTE );

	/* 聖域の上では戦闘は出来ない */

	if( (o_p != NULL) && chk_map_sanctuary( o_p->x, o_p->y ) )
		return FALSE;
	if( (d_p != NULL) && chk_map_sanctuary( d_p->x, d_p->y ) )
		return FALSE;

	/* 投げる物が無くなったらキャンセル */

	eq = NULL;
	arw.kind = ITEM_KIND_NULL;
	arw.prev = NULL;
	arw.next = NULL;
	if( attack->flg_throw && (o_k == CHR_KIND_MBR) ){
		eq = get_mbr_item_asgn_equip( (mbr_t *)o_p );
		if( eq != NULL ){
			if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_NULL ){
				print_msg( FLG_MSG_ERR, MSG_ERR_THROW,
						o_name );

				clr_chr_trgt_act( (mbr_t *)o_p, TRUE );

				return FALSE;
			}

			copy_item( &arw, &(eq[EQUIP_KIND_ARW]) );
			arw.n = 1;
		}
	}

	/* 距離のチェック */

	flg_err_range = FALSE;
	if( attack->flg_throw ){
		if( attack->range_throw < range )
			flg_err_range = TRUE;
	} else {
		if( attack->range_bash < range )
			flg_err_range = TRUE;
	}
	if( flg_err_range ){
		print_msg( FLG_MSG_ERR, MSG_ERR_ATTACK_RANGE, o_p->name );

		return FALSE;
	}

	/* 透明化の効果を解除 */

	if( cancel_fx_vanish( o_p ) )
		return FALSE;

	/* 食べ物が当ったか? */

	if( eq == NULL ){
		flg_catch_food = FALSE;
	} else {
		flg_catch_food = chk_mnstr_catch_food(
				d_p, &(eq[EQUIP_KIND_ARW]) );
	}

	/* 手加減 */

	flg_serious = TRUE;
	if( d_p != NULL ){
		if( d_p->attitude == ATTITUDE_MATE ){
			if( o_p->attitude == ATTITUDE_MATE ){
				/* 味方どうしなら手加減する */
				flg_serious = FALSE;
			}
		} else if( flg_catch_food ){
			flg_serious = FALSE;
		} else {
			set_enemy_mnstr_group( o_p, d_p );
		}
	}
	if( chk_flg( get_flg_party(), FLG_PARTY_ACTUAL_FIGHTING ) )
		flg_serious = TRUE;

	/* 防御側の名前とデータの取得 */

	if( flg_d_null ){
		str_nz_cpy( d_name, MSG_NULL, CHR_NAME_MAX_BYTE );
		d_hp = NULL;
		d_x = o_p->trgt.true_x;
		d_y = o_p->trgt.true_y;
	} else {
		str_nz_cpy( d_name, d_p->name, CHR_NAME_MAX_BYTE );
		d_hp = &(d_p->abl.hp);
		d_x = d_p->x;
		d_y = d_p->y;
	}

	/* 攻撃側が戦えるか？ */

	if( o_k == CHR_KIND_MBR )
		stat = ((mbr_t *)o_p)->stat;
	else
		stat = ((mnstr_t *)o_p)->stat;
	if( chk_flg_or( stat, FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_CONFUSION
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		return FALSE;
	}

	/* 防御側が戦えるか？ */

	if( d_k == CHR_KIND_MBR )
		stat = ((mbr_t *)d_p)->stat;
	else if( flg_d_null )
		stat = FLG_NULL;
	else
		stat = ((mnstr_t *)d_p)->stat;
	if( chk_flg_or( stat, FLG_STAT_NOT_EXIST
			| FLG_STAT_STONE
			| FLG_STAT_DEAD ) ){
		return FALSE;
	}
	if( chk_flg_or( stat, FLG_STAT_PARALYZE
			| FLG_STAT_CONFUSION
			| FLG_STAT_BLIND
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		flg_auto_hit = TRUE;
	} else {
		flg_auto_hit = FALSE;
	}

	/* 相手が見えているか？ */

	if( flg_d_null ){
		pos_t	o_pos, d_pos;

		o_pos.x = o_p->x;
		o_pos.y = o_p->y;
		d_pos.x = o_p->trgt.true_x;
		d_pos.y = o_p->trgt.true_y;
		if( !chk_find( &o_pos, &d_pos ) ){
			clr_chr_trgt_act( o_p, FALSE );
			return FALSE;
		}
	} else {
		if( !chk_find_chr( o_p, d_p ) ){
			if( o_k == CHR_KIND_MBR ){
				print_msg( FLG_MSG_ERR,
						MSG_ERR_NOT_FIND,
						o_name, d_name );
			}
			return FALSE;
		}
	}

	print_msg_find( d_p, FLG_NULL, get_msg_attack( attack ),
			o_name, d_name );
	print_msg_find( d_p, FLG_NULL, MSG_FIGHT_RESI_KIND,
			get_resi_name( attack->resi_kind ) );

	bgn.x = o_p->x;
	bgn.y = o_p->y;
	end.x = o_p->trgt.true_x;
	end.y = o_p->trgt.true_y;

	mjr = MNSTR_THROW_MJR;
	mnr = FACE_MNR_NULL;
	gui_vfx = NULL;
	if( attack->flg_throw ){
		sound_kind_t	sk;

		if( o_k == CHR_KIND_MBR )
			sk = SOUND_KIND_FIGHT_ATTACK_THROW_MEMBER;
		else if( o_k == CHR_KIND_MNSTR )
			sk = SOUND_KIND_FIGHT_ATTACK_THROW_MONSTER;
		else
			sk = SOUND_KIND_NULL;
		call_game_sound_play( sk, 1 );
	}

	if( attack->flg_throw && (eq != NULL) ){
		if( eq[EQUIP_KIND_BOW].kind == ITEM_KIND_WPN )
			bow_tab = eq[EQUIP_KIND_BOW].tab.wpn;
		else
			bow_tab = NULL;
		if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_WPN )
			arw_tab = eq[EQUIP_KIND_ARW].tab.wpn;
		else
			arw_tab = NULL;

		mjr = get_item_mjr( &(eq[EQUIP_KIND_ARW]) );
		mnr = get_item_mnr( &(eq[EQUIP_KIND_ARW]) );
		dir_n = calc_dir_n( &bgn, &end );

		if( chk_dagger( arw_tab ) || chk_bow( arw_tab, bow_tab ) )
			gui_vfx = alloc_gui_vfx_arw( dir_n );
		else
			gui_vfx = alloc_gui_vfx_throw_item( mjr, mnr );

		/* 投げる物の描画 */
		vfx_arw( o_k, &bgn, &end, gui_vfx, mjr, ANIM_ARW_LEN );
	} else if( attack->flg_throw && (eq == NULL) ){
		/* 投げる物の描画 */
		mjr = MNSTR_THROW_MJR;
		dir_n = calc_dir_n( &bgn, &end );
		gui_vfx = alloc_gui_vfx_arw( dir_n );

		vfx_arw( o_k, &bgn, &end, gui_vfx, mjr, ANIM_ARW_LEN );
	}

	/* 防御側のデータ */

	d_cont = use_contribution_rate( d_p );

	if( flg_d_null ){
		d_def = 0;
		d_ac = 0;
		d_resi = _100_PERCENT;
	} else {
		d_def = get_def( d_p );
		d_def = roll_dice( d_def, FALSE );
		/* 祝福 */
		d_def += d_def * d_p->fx_data.bless;
		/* 寄付 */
		d_def = d_def * d_cont / _100_PERCENT;
		d_ac = get_ac( d_p );
		if( d_k == CHR_KIND_MBR ){
			if( ((mbr_t *)d_p)->act.kind == ACT_KIND_NULL ){
				/* 何もしていなければ防御 */
				d_def *= DEF_DEF_RATE;
				d_def /= _100_PERCENT;
				d_ac *= DEF_AC_RATE;
				d_ac /= _100_PERCENT;
			}
		}
		d_resi = get_resi_def( d_p, attack->resi_kind );
	}
	if( flg_auto_hit )
		d_def = 0;

	/* 攻撃側のデータ */

	o_cont = use_contribution_rate( o_p );

	o_hit = get_hit( o_p, attack );
	o_hit = roll_dice( o_hit, FALSE );
	/* 祝福 */
	o_hit += o_hit * o_p->fx_data.bless;
	/* 寄付 */
	o_hit = o_hit * o_cont / _100_PERCENT;
	o_hit = o_hit * get_chr_throw_range_rate( o_p, d_p ) / _100_PERCENT;

	o_dam = get_dam( o_p, attack );

	o_crtcl = get_crtcl( o_p, d_p, attack );
	/* 「〜殺し」効果 */
	if( chk_killer( o_p, d_p, attack->flg_throw ) ){
		o_crtcl = o_crtcl * KILLER_RATE / _100_PERCENT;
		print_msg( FLG_MSG_DEBUG, "killer" );
	}
	/* 「〜防御」効果 */
	if( chk_block( o_p, d_p, attack->flg_throw ) ){
		o_crtcl = o_crtcl * BLOCK_RATE / _100_PERCENT;
		print_msg( FLG_MSG_DEBUG, "block" );
	}
	flg_crtcl = rate_randm( o_crtcl );

	if( !flg_d_null ){
		o_dam = roll_dice( o_dam, TRUE );
		o_dam = calc_resi( d_resi, o_dam );
		o_dam -= d_ac;
	}
	if( o_dam <= 0 )
		o_dam = 1;

	/* クリティカル */

	if( flg_crtcl && flg_serious )
		flg_ninja_crtcl = chk_ninja_crtcl( o_p, d_p );
	else
		flg_ninja_crtcl = FALSE;

	/* 「〜殺し」効果 */

	if( chk_bane( o_p, d_p, attack->flg_throw ) ){
		o_hit = o_hit * BANE_RATE / _100_PERCENT;
		print_msg( FLG_MSG_DEBUG, "bane" );
	}
	if( chk_slayer( o_p, d_p, attack->flg_throw ) ){
		o_dam = o_dam * SLAYER_RATE / _100_PERCENT;
		print_msg( FLG_MSG_DEBUG, "slayer" );
	}

	/* 「〜防御」効果 */

	if( chk_guard( o_p, d_p, attack->flg_throw ) ){
		o_hit = o_hit * GUARD_RATE / _100_PERCENT;
		print_msg( FLG_MSG_DEBUG, "guard" );
	}
	if( chk_protect( o_p, d_p, attack->flg_throw ) ){
		o_dam = o_dam * PROTECT_RATE / _100_PERCENT;
		print_msg( FLG_MSG_DEBUG, "protect" );
	}

	/* スキルの「ダメージ強化系」の効果 */

	o_skill_dam = calc_skill_rate( o_p,
			cv_resi_to_skill_dam( attack->resi_kind ) );
	o_dam = o_dam * o_skill_dam / _100_PERCENT;
	if( o_skill_dam != _100_PERCENT ){
		print_msg( FLG_MSG_DEBUG, "skill damage: %ld%%",
				o_skill_dam );
	}

	/* 食べ物が当る */

	if( flg_catch_food ){
		o_hit = 2;
		d_def = 1;
	}

	print_msg( FLG_MSG_DEBUG, "o_hit: %ld, d_def: %ld",
			o_hit, d_def );

	/* あたらなければ */

	if( flg_d_null || (!flg_crtcl && (d_def > o_hit)) ){
		sound_kind_t	sk;

		if( flg_d_null ){
			sk = SOUND_KIND_NULL;
		} else if( is_xx( d_p ) ){
			sk = SOUND_KIND_FIGHT_DEFENSE_MISS_MONSTER_BOSS_LAST;
		} else if( is_mnstr( d_p ) ){
			sk = SOUND_KIND_FIGHT_DEFENSE_MISS_MONSTER;
		} else if( is_mbr( d_p ) ){
			sk = SOUND_KIND_FIGHT_DEFENSE_MISS_MEMBER;
		} else {
			sk = SOUND_KIND_NULL;
		}
		call_game_sound_play( sk, 1 );

		if( flg_d_null ){
			print_msg( FLG_MSG_ERR, MSG_ERR_MNSTR_NULL );
		} else {
			fx_t	*fx;

			fx = srch_fx( &(d_p->fx), FX_KIND_SUBSTITUTE );
			if( fx != NULL ){
				print_msg( FLG_NULL, MSG_FIGHT_SUBSTITUTE,
						d_name );
			}

			print_msg( FLG_NULL, MSG_FIGHT_MISS_STD,
					o_name, d_name );
		}

		do {
			if( o_k != CHR_KIND_MBR )
				break;
			if( eq == NULL )
				break;
			if( !attack->flg_throw )
				break;

			/* 遠隔攻撃の処理 */

			if( chk_come_back_arw( (mbr_t *)o_p ) ){
				/* ブーメランのように戻ってくる */
				vfx_arw( o_k, &end, &bgn, gui_vfx,
						mjr, ANIM_ARW_LEN );
			} else {
				/* 床に落ちる */
				dec_throw( (mbr_t *)o_p, TRUE, d_x, d_y );
			}
		} while( 0 );

		free_gui_vfx( gui_vfx );

		return FALSE;
	}

	free_gui_vfx( gui_vfx );

	/* 矢を消費する */

	do {
		if( !attack->flg_throw )
			break;
		if( eq == NULL )
			break;
		if( o_k != CHR_KIND_MBR )
			break;

		if( flg_d_null ){
			/* 消費せずに落す */
			dec_throw( (mbr_t *)o_p, TRUE, d_x, d_y );
		} else if( (eq[EQUIP_KIND_ARW].kind == ITEM_KIND_WPN)
				&& chk_flg( eq[EQUIP_KIND_ARW].dat.wpn.flg,
				FLG_WPN_TAB_NOT_SPEND ) ){
			/* 消費せずに落す */
			dec_throw( (mbr_t *)o_p, TRUE, d_x, d_y );
		} else {
			dec_throw( (mbr_t *)o_p, FALSE, d_x, d_y );
		}

		break;
	} while( 0 );

	/* 攻撃を弾く */

	if( chk_flg( d_p->stat, FLG_STAT_IRON_BODY ) ){
		curs_attrset_chr( d_p, +1, FALSE );
		print_msg( FLG_NULL, MSG_REPEL_ATTACK,
				d_p->name, o_p->name );
		curs_attrset_dflt();

		return FALSE;
	}

	/* 手加減 */

	if( !flg_serious )
		o_dam = 0;

	/* 魔法の武器しか効かないかチェック */

	if( !flg_crtcl )
		if( chk_magic_protect( o_p, d_p, attack->flg_throw ) )
			o_dam = 0;

	/* ポーションが当った */

	if( (eq != NULL) && (arw.kind == ITEM_KIND_POTION) )
		o_dam = 0;

	/* 食べ物が当った */

	if( flg_catch_food ){
		fx_mnstr_catch_food( d_p, &arw );
		return TRUE;
	}

	/* 攻撃が当った */

	if( o_dam < 0 )
		o_dam = 0;
	if( flg_crtcl )
		o_dam *= 2;

	/* 実際のダメージに修整 */

	o_dam_real = o_dam;
	if( d_hp != NULL)
		if( o_dam_real > d_hp->n )
			o_dam_real = d_hp->n;

	/* 効果音 */

	sk = SOUND_KIND_NULL;
	if( o_dam <= 0 ){
		sk = SOUND_KIND_NULL;
	} else if( flg_ninja_crtcl ){
		if( is_mnstr( d_p ) )
			sk = SOUND_KIND_FIGHT_DEFENSE_CRITICAL_MONSTER;
		else
			sk = SOUND_KIND_FIGHT_DEFENSE_CRITICAL_MEMBER;
	} else if( flg_crtcl ){
		if( is_mnstr( d_p ) )
			sk = SOUND_KIND_FIGHT_DEFENSE_CRITICAL_MONSTER;
		else
			sk = SOUND_KIND_FIGHT_DEFENSE_CRITICAL_MEMBER;
	} else {
		if( is_mnstr( d_p ) )
			sk = SOUND_KIND_FIGHT_DEFENSE_HIT_MONSTER;
		else
			sk = SOUND_KIND_FIGHT_DEFENSE_HIT_MEMBER;
	}
	call_game_sound_play( sk, 1 );

	/* ダメージの表示 */

	if( o_dam <= 0 ){
		;
	} else if( flg_ninja_crtcl ){
		curs_attrset_chr( d_p, -1, TRUE );
		print_msg( FLG_NULL, MSG_FIGHT_CRTCL_NINJA, o_name );
		curs_attrset_dflt();

		vfx_ninja_crtcl( d_p, end.x, end.y );
	} else if( flg_crtcl ){
		curs_attrset_chr( d_p, -1, TRUE );
		print_msg( FLG_NULL, MSG_FIGHT_CRTCL_STD, o_name );
		curs_attrset_dflt();

		vfx_crtcl( d_p, end.x, end.y );

		curs_attrset_chr( d_p, -1, FALSE );
		print_msg( FLG_NULL, MSG_FIGHT_HIT_STD,
				d_name, o_dam_real );
		curs_attrset_dflt();
	} else {
		curs_attrset_chr( d_p, -1, FALSE );
		print_msg( FLG_NULL, MSG_FIGHT_HIT_STD,
				d_name, o_dam_real );
		curs_attrset_dflt();

		vfx_hit( d_p, end.x, end.y );
	}

	/* 攻撃のエフェクト */

	fight_fx( o_p, d_p, attack );

	/* ポーションが当った */

	if( (eq != NULL) && (arw.kind == ITEM_KIND_POTION) ){
		o_dam = 0;

		quaff_potion( (chr_t *)d_p, &arw, FALSE );
	}

	/* 訓練 */

	do {
		abl_kind_t	o_abl, d_abl;
		long	o_lev, d_lev;

		if( flg_serious )
			break;

		if( attack->flg_throw )
			o_abl = ABL_KIND_HUN;
		else if( attack->flg_monk )
			o_abl = ABL_KIND_MON;
		else
			o_abl = ABL_KIND_FIG;
		d_abl = get_def_abl( d_p );

		o_lev = get_lev( o_p, o_abl );
		d_lev = get_lev( d_p, d_abl );

		if( o_lev >= d_lev )
			break;

		exp_chr( (mbr_t *)o_p, TRAINING_EXP, FALSE, TRUE, TRUE );
	} while( 0 );

	/* 追加効果 */

	added_fx( d_p, attack->resi_kind );
	added_fx_wpn_randm_art( o_p, d_p, attack->flg_throw );

	fx_wpn_randm_art_drain( WPN_RANDM_ART_MNR_DRAIN_HP,
			o_p, d_p, o_dam_real, attack->flg_throw );
	fx_wpn_randm_art_drain( WPN_RANDM_ART_MNR_DRAIN_MP,
			o_p, d_p, o_dam_real, attack->flg_throw );
	fx_wpn_randm_art_drain( WPN_RANDM_ART_MNR_DRAIN_EXP,
			o_p, d_p, o_dam_real, attack->flg_throw );

	/* HPを減らす */

	flg_dead = FALSE;
	if( flg_ninja_crtcl )
		flg_dead = TRUE;
	if( (d_hp != NULL) && (d_hp->n <= o_dam) )
		flg_dead = TRUE;

	if( flg_dead ){
		/* 殺した */
		curs_attrset_chr( d_p, -1, TRUE );
		print_msg( FLG_NULL, MSG_FIGHT_KILL_STD, o_name, d_name );
		curs_attrset_dflt();
	}

	if( flg_ninja_crtcl ){
		die_chr( d_p, TRUE, TRUE, TRUE );
	} else {
		add_hp( d_p, -o_dam, TRUE, FALSE );

		/* 統計を取る */

		if( is_mbr( o_p ) && (o_dam > 0) ){
			update_playing_report_making_dam(
			o_p->ls_mbr_n, attack->resi_kind, o_dam );
		}
		if( is_mbr( d_p ) && (o_dam > 0) ){
			update_playing_report_made_dam(
			d_p->ls_mbr_n, attack->resi_kind, o_dam );
		}
	}

	return TRUE;
}

/***************************************************************
* 二刀流による予備攻撃
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* const attack_t *attack : 攻撃データ
* long range : 距離
* return : 攻撃成功か?
***************************************************************/

bool_t	fight_two_sword_fencing(
	chr_t *o_p, chr_t *d_p,
	const attack_t *attack, long range
)
{
	long	attack_n;
	long	j;

	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;
	if( attack == NULL )
		return FALSE;

	attack_n = calc_two_sword_fencing_n( o_p, attack );
	if( attack_n <= 0 )
		return FALSE;

	curs_attrset_chr( d_p, -1, FALSE );
	print_msg( FLG_NULL, MSG_FIGHT_TWO_SWORD_FENCING,
			o_p->name, attack_n );
	curs_attrset_dflt();

	for( j = 0; j < attack_n; j++ )
		if( fight_x_1( o_p, d_p, attack, range, FALSE ) )
			return TRUE;

	return FALSE;
}

/***************************************************************
* カウンターによる反撃
* chr_t *o_p : 攻撃側キャラクタ (反撃側)
* chr_t *d_p : 防御側キャラクタ
* return : 攻撃成功か?
***************************************************************/

bool_t	fight_counter( chr_t *o_p, chr_t *d_p )
{
	long	attack_n;
	attack_t	attack;
	long	d;
	long	hit_n;
	long	i;

	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	attack_n = calc_counter_n( o_p );
	if( attack_n <= 0 )
		return FALSE;

	/* 先に攻撃して来た側 (防御側) の距離で計算する */
	d = get_trgt_range( d_p );

	if( !set_attack_chr_bash( o_p, &attack, 1, FALSE ) )
		return FALSE;

	/* カウンターの表示 */

	curs_attrset_chr( d_p, -1, FALSE );
	print_msg( FLG_NULL, MSG_FIGHT_COUNTER, o_p->name, attack_n );
	curs_attrset_dflt();

	/* begin */
	bgn_sync_vfx_num();

	hit_n = 0;
	for( i = 0; i < attack_n; i++ )
		if( fight_x_1( o_p, d_p, &attack, d, TRUE ) )
			hit_n++;

	/* end */
	end_sync_vfx_num();

	if( hit_n >= 1 )
		return TRUE;
	else
		return FALSE;
}

/***************************************************************
* 呪文攻撃
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* resi_kind_t resi : 抵抗値の種類
* bool_t flg_stick : 魔法の杖か?
* abl_kind_t abl : 使用する能力値の種類
* rate_t rate : ダメージの多さ
* return : 攻撃成功か?
***************************************************************/

bool_t	spell_attack(
	chr_t *o_p, chr_t *d_p,
	resi_kind_t resi, bool_t flg_stick,
	abl_kind_t abl, rate_t rate
)
{
	flg_stat_t	o_stat;
	pos_t	o_pos, d_pos;
	static char	o_name[CHR_NAME_MAX_BYTE + 1];
	static char	d_name[CHR_NAME_MAX_BYTE + 1];
	rate_t	o_skill_dam;
	long	dam;
	long	ac;
	bool_t	flg_serious;

	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL ){
		print_msg( FLG_MSG_ERR, MSG_ERR_MNSTR_NULL );

		if( is_mbr( o_p ) )
			clr_chr_trgt_act( (mbr_t *)o_p, FALSE );

		return FALSE;
	}

	/* 透明化の効果を解除 */

	if( cancel_fx_vanish( o_p ) )
		return FALSE;

	/* 手加減 */

	flg_serious = TRUE;
	if( d_p != NULL ){
		if( d_p->attitude == ATTITUDE_MATE ){
			if( o_p->attitude == ATTITUDE_MATE ){
				/* 味方どうしなら手加減する */
				flg_serious = FALSE;
			}
		} else {
			set_enemy_mnstr_group( o_p, d_p );
		}
	}
	if( chk_flg( get_flg_party(), FLG_PARTY_ACTUAL_FIGHTING ) )
		flg_serious = TRUE;

	/* 攻撃側データ */

	o_stat = o_p->stat;
	o_pos.x = o_p->x;
	o_pos.y = o_p->y;
	str_nz_cpy( o_name, o_p->name, CHR_NAME_MAX_BYTE );

	/* 防御側データ */

	d_pos.x = d_p->x;
	d_pos.y = d_p->y;
	str_nz_cpy( d_name, d_p->name, CHR_NAME_MAX_BYTE );

	/* 攻撃できるか */

	if( chk_flg_or( o_stat, FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_CONFUSION
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		return FALSE;
	}

	/* 見えているか */

	if( !chk_find( &o_pos, &d_pos ) ){
		print_msg( FLG_MSG_ERR, MSG_ERR_NOT_FIND, o_name, d_name );

		return FALSE;
	}

	/* 視覚効果 */

	if( flg_stick ){
		gui_vfx_t	*gui_vfx;
		char	mjr = '*';

		gui_vfx = alloc_gui_vfx_spell( resi );
		vfx_arw( o_p->kind, &o_pos, &d_pos, gui_vfx,
				mjr, ANIM_ARW_LEN );
		free_gui_vfx( gui_vfx );
	}

	/* アーマ・クラス */

	ac = get_ac( d_p );

	/* ダメージの計算 */

	if( flg_stick )
		dam = get_dam_stick( o_p );
	else
		dam = get_dam_spell( o_p, abl, get_sub_abl( abl ) );
	dam = dam * rate / _100_PERCENT;
	dam = roll_dice( dam, TRUE );

	/* スキルの「ダメージ強化系」の効果 */

	o_skill_dam = calc_skill_rate( o_p, cv_resi_to_skill_dam( resi ) );
	dam = dam * o_skill_dam / _100_PERCENT;
	if( o_skill_dam != _100_PERCENT ){
		print_msg( FLG_MSG_DEBUG, "skill damage: %ld%%",
				o_skill_dam );
	}

	dam = calc_resi( get_resi_def( d_p, resi ), dam );
	dam -= ac;
	if( dam < 1 )
		dam = 1;
	if( !flg_serious )
		dam = 0;

	/* ダメージの表示 */

	print_msg_find( d_p, FLG_NULL, MSG_FIGHT_RESI_KIND,
			get_resi_name( resi ) );

	curs_attrset_chr( d_p, -1, FALSE );
	print_msg_find( d_p, FLG_NULL, MSG_FIGHT_HIT_STD, d_name, dam );
	curs_attrset_dflt();

	/* 追加効果 */

	added_fx( d_p, resi );

	/* HPを減らす */

	if( d_p->abl.hp.n <= dam ){
		/* 殺した */
		curs_attrset_chr( d_p, -1, TRUE );
		print_msg( FLG_NULL, MSG_FIGHT_KILL_STD, o_name, d_name );
		curs_attrset_dflt();
	}
	add_hp( d_p, -dam, TRUE, FALSE );

	/* 統計を取る */

	if( is_mbr( o_p ) && (dam > 0) ){
		update_playing_report_making_dam(
				o_p->ls_mbr_n, resi, dam );
	}
	if( is_mbr( d_p ) && (dam > 0) ){
		update_playing_report_made_dam(
				d_p->ls_mbr_n, resi, dam );
	}

	return TRUE;
}

/***************************************************************
* 攻撃の追加効果
* chr_t *chr : キャラクタ
* resi_kind_t resi : 抵抗値の種類
***************************************************************/

void	added_fx( chr_t *chr, resi_kind_t resi )
{
	fx_t	*fx;

	if( chr == NULL )
		return;

	/* 目が覚める */

	fx = srch_fx( &(chr->fx), FX_KIND_SLEEP );
	clr_fx( fx );

	/* 追加効果 */

	switch( resi ){
	case RESI_KIND_KNOC:
	case RESI_KIND_SLAS:
	case RESI_KIND_STIN:
	case RESI_KIND_HEAT:
	case RESI_KIND_COLD:
	case RESI_KIND_MIND:
		break;
	case RESI_KIND_ACID:
		fx_acid( chr );
		break;
	case RESI_KIND_ELEC:
		break;
	case RESI_KIND_POIS:
		fx_poison( chr );
		break;
	case RESI_KIND_MAX_N:
		break;
	}
}

/***************************************************************
* キャラクタの武器のランダム・アーティファクトの追加効果
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* bool_t flg_throw : 飛び道具か?
***************************************************************/

void	added_fx_wpn_randm_art(
	chr_t *o_p, chr_t *d_p,
	bool_t flg_throw
)
{
	item_t	*eq;

	if( o_p == NULL )
		return;
	if( d_p == NULL )
		return;
	if( !is_mbr( o_p ) )
		return;

	eq = get_mbr_item_asgn_equip( (mbr_t *)o_p );
	if( eq == NULL )
		return;

	if( flg_throw ){
		if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_WPN ){
			added_fx_wpn_randm_art_item( o_p, d_p,
					&(eq[EQUIP_KIND_ARW]) );
		}
		if( eq[EQUIP_KIND_BOW].kind == ITEM_KIND_WPN ){
			added_fx_wpn_randm_art_item( o_p, d_p,
					&(eq[EQUIP_KIND_BOW]) );
		}
	} else {
		if( eq[EQUIP_KIND_WIELDING].kind == ITEM_KIND_WPN ){
			added_fx_wpn_randm_art_item( o_p, d_p,
					&(eq[EQUIP_KIND_WIELDING]) );
		}
	}
}

/***************************************************************
* 武器のランダム・アーティファクトの追加効果
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* item_t *item : 攻撃側の武器
***************************************************************/

void	added_fx_wpn_randm_art_item(
	chr_t *o_p, chr_t *d_p,
	item_t *item
)
{
	wpn_randm_art_t	*art;
	abl_kind_t	abl;
	fx_kind_t	fx;
	resi_kind_t	resi;
	flg_stat_t	stat;
	long	i;

	if( item == NULL )
		return;
	if( item->kind != ITEM_KIND_WPN )
		return;
	if( d_p == NULL )
		return;

	abl = get_specialist_abl( o_p );

	art = item->dat.wpn.randm_art;

	for( i = 0; i < WPN_RANDM_ART_LS_MAX_N; i++ ){
		if( art[i].kind == WPN_RANDM_ART_KIND_NULL )
			break;
		if( art[i].kind != WPN_RANDM_ART_KIND_ADD_STAT )
			continue;

		fx = get_wpn_randm_art_add_stat_fx( art[i].mnr );
		if( fx == FX_KIND_NULL )
			continue;

		/* 追加効果に耐性があるかチェック */

		stat = cv_fx_kind_to_flg_stat( fx );
		if( (stat != FLG_STAT_NULL) && chk_resi_stat( d_p, stat ) )
			continue;

		/* 追加効果が抵抗されるかチェック */

		resi = cv_fx_kind_to_resi_kind( fx );
		if( resi >= RESI_KIND_MAX_N )
			continue;

		if( resi_roll( o_p, abl, d_p, resi ) )
			continue;

		/* 追加効果がはじかれるかチェック */

		if( chk_flg( d_p->stat, FLG_STAT_IRON_BODY ) ){
			if( (o_p != NULL) && (d_p != NULL) ){
				curs_attrset_chr( d_p, +1, FALSE );
				print_msg( FLG_NULL, MSG_REPEL_ATTACK,
						d_p->name, o_p->name );
				curs_attrset_dflt();
			}
			continue;
		}

		fx_std( d_p, fx );
	}
}

/***************************************************************
* 攻撃のエフェクト
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* const attack_t *attack : 攻撃データ
***************************************************************/

void	fight_fx( chr_t *o_p, chr_t *d_p, const attack_t *attack )
{
	if( o_p == NULL )
		return;
	if( d_p == NULL )
		return;
	if( attack == NULL )
		return;
	if( attack->fx_kind == FX_KIND_NULL )
		return;

	if( !resi_roll( o_p, ABL_KIND_MAX_N, d_p, attack->resi_kind ) )
		set_fx( d_p, attack->fx_kind, attack->fx_turn );
}

/***************************************************************
* ドアを壊す
* chr_t *chr : キャラクタ
* long dr_n : ドア番号
* return : 壊せたか?
***************************************************************/

bool_t	chr_break_door( chr_t *chr, long dr_n )
{
	long	hit;
	attack_t	attack;
	rate_t	cont;

	if( chr == NULL )
		return FALSE;

	if( set_attack_chr_bash( chr, &attack, 1, FALSE ) )
		hit = get_hit( chr, &attack );
	else
		hit = get_hit( chr, NULL );
	hit = roll_dice( hit, FALSE );

	/* 祝福 */
	hit += hit * chr->fx_data.bless;

	/* 寄付 */
	cont = use_contribution_rate( chr );
	hit = hit * cont / _100_PERCENT;

	if( DOOR_DEF > hit ){
		print_msg_mbr( chr, FLG_MSG_ERR, MSG_ERR_DOOR_BREAK_LEV,
				chr->name );
		return FALSE;
	}

	clr_chr_trgt_act( chr, FALSE );

	if( !break_door( chr, dr_n ) )
		return FALSE;

	print_msg_mbr( chr, FLG_NULL, MSG_DOOR_BREAK, chr->name );

	return TRUE;
}

/***************************************************************
* 罠を壊す
* chr_t *chr : キャラクタ
* trap_t *trap : 罠
* return : 壊せたか?
***************************************************************/

bool_t	chr_break_trap( chr_t *chr, trap_t *trap )
{
	long	hit;
	attack_t	attack;
	rate_t	cont;

	if( chr == NULL )
		return FALSE;

	if( set_attack_chr_bash( chr, &attack, 1, FALSE ) )
		hit = get_hit( chr, &attack );
	else
		hit = get_hit( chr, NULL );
	hit = roll_dice( hit, FALSE );

	/* 祝福 */
	hit += hit * chr->fx_data.bless;

	/* 寄付 */
	cont = use_contribution_rate( chr );
	hit = hit * cont / _100_PERCENT;

	if( TRAP_DEF > hit ){
		print_msg( FLG_MSG_ERR, MSG_ERR_TRAP_BREAK_LEV );

		caught_trap( trap, chr );
	} else {
		print_msg( FLG_NULL, MSG_TRAP_BREAK, chr->name );
		caught_trap( trap, chr );
		free_trap( trap );
	}

	return TRUE;
}

/***************************************************************
* アイテムを壊す
* chr_t *chr : キャラクタ
* item_t *item : アイテム
* return : 壊せたか?
***************************************************************/

bool_t	chr_break_item( chr_t *chr, item_t *item )
{
	long	hit;
	attack_t	attack;
	rate_t	cont;
	char	name[ITEM_NAME_MAX_BYTE + 1];

	if( chr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( item->kind == ITEM_KIND_JUNK ){
		print_msg( FLG_MSG_ERR, MSG_ERR_ITEM_BREAK_BROKEN,
				item->name );

		return TRUE;
	}

	if( set_attack_chr_bash( chr, &attack, 1, FALSE ) )
		hit = get_hit( chr, &attack );
	else
		hit = get_hit( chr, NULL );
	hit = roll_dice( hit, FALSE );

	/* 祝福 */
	hit += hit * chr->fx_data.bless;

	/* 寄付 */
	cont = use_contribution_rate( chr );
	hit = hit * cont / _100_PERCENT;

	if( ITEM_DEF > hit ){
		print_msg( FLG_MSG_ERR, MSG_ERR_ITEM_BREAK_LEV,
				item->name );

		return FALSE;
	}

	str_nz_cpy( name, item->name, ITEM_NAME_MAX_BYTE );

	break_item_contents( item, chr );
	if( break_item( item, TRUE ) )
		print_msg( FLG_NULL, MSG_ITEM_BREAK, chr->name, name );
	else
		print_msg( FLG_MSG_ERR, MSG_ERR_ITEM_BREAK, name );

	draw_item( item );

	return TRUE;
}

/***************************************************************
* 武器のベーン効果が効くか調べる
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* bool_t flg_throw : 飛び道具か?
* return : 効くか?
***************************************************************/

bool_t	chk_bane( chr_t *o_p, chr_t *d_p, bool_t flg_throw )
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( chk_wpn_randm_art( WPN_RANDM_ART_KIND_BANE, d_p->face.mjr,
			o_p, d_p, flg_throw ) ){
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* 武器のキラー効果が効くか調べる
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* bool_t flg_throw : 飛び道具か?
* return : 効くか?
***************************************************************/

bool_t	chk_killer( chr_t *o_p, chr_t *d_p, bool_t flg_throw )
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( chk_wpn_randm_art( WPN_RANDM_ART_KIND_KILLER, d_p->face.mjr,
			o_p, d_p, flg_throw ) ){
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* 武器のスレイヤー効果が効くか調べる
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* bool_t flg_throw : 飛び道具か?
* return : 効くか?
***************************************************************/

bool_t	chk_slayer( chr_t *o_p, chr_t *d_p, bool_t flg_throw )
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( chk_wpn_randm_art( WPN_RANDM_ART_KIND_SLAYER, d_p->face.mjr,
			o_p, d_p, flg_throw ) ){
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* 防具の「〜ガード」効果が効くか調べる
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* bool_t flg_throw : 飛び道具か?
* return : 効くか?
***************************************************************/

bool_t	chk_guard( chr_t *o_p, chr_t *d_p, bool_t flg_throw )
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( chk_armor_randm_art( ARMOR_RANDM_ART_KIND_GUARD,
			o_p->face.mjr, o_p, d_p ) ){
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* 防具の「〜ブロック」効果が効くか調べる
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* bool_t flg_throw : 飛び道具か?
* return : 効くか?
***************************************************************/

bool_t	chk_block( chr_t *o_p, chr_t *d_p, bool_t flg_throw )
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( chk_armor_randm_art( ARMOR_RANDM_ART_KIND_BLOCK,
			o_p->face.mjr, o_p, d_p ) ){
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* 防具の「〜プロテクト」効果が効くか調べる
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* bool_t flg_throw : 飛び道具か?
* return : 効くか?
***************************************************************/

bool_t	chk_protect( chr_t *o_p, chr_t *d_p, bool_t flg_throw )
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( chk_armor_randm_art( ARMOR_RANDM_ART_KIND_PROTECT,
			o_p->face.mjr, o_p, d_p ) ){
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* 魔法の武器以外、効かない敵か調べる
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* bool_t flg_throw : 飛び道具か?
* return : 魔法の武器以外、効かないなら TRUE、効くなら FALSE
***************************************************************/

bool_t	chk_magic_protect( chr_t *o_p, chr_t *d_p, bool_t flg_throw )
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( !chk_flg( d_p->flg_chr, FLG_CHR_MAGIC_PROTECT ) )
		return FALSE;

	do {
		item_t	*eq;

		if( !is_mbr( o_p ) )
			break;

		eq = get_mbr_item_asgn_equip( (mbr_t *)o_p );
		if( eq == NULL )
			break;

		if( flg_throw ){
			if( eq[EQUIP_KIND_ARW].kind != ITEM_KIND_WPN )
				break;
			if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_WPN ){
				if( eq[EQUIP_KIND_ARW].dat.wpn.add_hit > 0 )
					return FALSE;
				if( eq[EQUIP_KIND_ARW].dat.wpn.add_crtcl > 0 )
					return FALSE;
				if( eq[EQUIP_KIND_ARW].dat.wpn.add_dam > 0 )
					return FALSE;
			}
			if( eq[EQUIP_KIND_BOW].kind == ITEM_KIND_WPN ){
				if( eq[EQUIP_KIND_BOW].dat.wpn.add_hit > 0 )
					return FALSE;
				if( eq[EQUIP_KIND_BOW].dat.wpn.add_crtcl > 0 )
					return FALSE;
				if( eq[EQUIP_KIND_BOW].dat.wpn.add_dam > 0 )
					return FALSE;
			}
			break;
		} else {
			if( eq[EQUIP_KIND_WIELDING].kind != ITEM_KIND_WPN )
				break;
			if( eq[EQUIP_KIND_WIELDING].dat.wpn.add_hit > 0 )
				return FALSE;
			if( eq[EQUIP_KIND_WIELDING].dat.wpn.add_crtcl > 0 )
				return FALSE;
			if( eq[EQUIP_KIND_WIELDING].dat.wpn.add_dam > 0 )
				return FALSE;
			break;
		}

		return FALSE;
	} while( 0 );

	curs_attrset_chr( o_p, -1, FALSE );
	print_msg( FLG_NULL, MSG_FIGHT_MAGIC_PROTECT, d_p->name );
	curs_attrset_dflt();

	return TRUE;
}

/***************************************************************
* キャラクタの攻撃力を計算
* chr_t *p : キャラクタ
* const attack_t *attack : 攻撃データ
* return : 攻撃力
***************************************************************/

long	get_hit( chr_t *p, const attack_t *attack )
{
	long	hit, wpn_hit;
	abl_kind_t	abl;

	if( p == NULL )
		return 1;
	if( attack == NULL )
		return 1;

	/* 能力値 */

	wpn_hit = attack->hit;

	if( attack->flg_throw )
		abl = ABL_KIND_HUN;
	else if( attack->flg_monk )
		abl = ABL_KIND_MON;
	else
		abl = ABL_KIND_FIG;

	hit = 0;
	hit += calc_abl_to_val( p, abl );
	hit += calc_abl_to_val( p, ABL_KIND_DEX );
	hit /= 2;

	if( abl == ABL_KIND_MON ){
		long	n;

		n = get_lev( p, abl );
		wpn_hit += HIT_MON_MUL * n;
		if( n > 0 )
			wpn_hit += HIT_MON_ADD;
	}

	if( is_mbr( p ) )
		hit = hit * calc_rate_abl_equip( p, abl ) / _100_PERCENT;

	/* FXの値を加える */

	wpn_hit += p->fx_data.wpn_hit;

#if	FLG_ITEM_ADD_RATE

	hit += HIT_AVE_N * wpn_hit / _100_PERCENT;

#else	/* FLG_ITEM_ADD_RATE */

	hit = hit * wpn_hit / _100_PERCENT;

#endif	/* FLG_ITEM_ADD_RATE */

	hit = hit * HIT_ADJ_RATE / _100_PERCENT;

	/* スキルで修整 */

	hit *= calc_skill_rate( p, SKILL_KIND_ATTACKER );
	hit /= _100_PERCENT;

	hit *= calc_skill_sub_rate( p, SKILL_KIND_BERSERKER,
			SKILL_KIND_ATTACKER );
	hit /= _100_PERCENT;

	hit *= calc_skill_sub_rate( p, SKILL_KIND_DEFENDER,
			SKILL_KIND_ATTACKER );
	hit /= _100_PERCENT;

	hit *= calc_skill_rate( p, SKILL_KIND_SIEGE );
	hit /= _100_PERCENT;

	if( hit < 1 )
		hit = 1;

	return hit;
}

/***************************************************************
* キャラクタのダメージを計算
* chr_t *p : キャラクタ
* const attack_t *attack : 攻撃データ
* return : ダメージ
***************************************************************/

long	get_dam( chr_t *p, const attack_t *attack )
{
	long	dam, wpn_dam;
	abl_kind_t	abl, sub_abl;

	if( p == NULL )
		return 1;
	if( attack == NULL )
		return 1;

	/* 能力値 */

	wpn_dam = attack->dam;

	if( attack->flg_throw ){
		abl = ABL_KIND_HUN;
		sub_abl = ABL_KIND_DEX;
	} else if( attack->flg_monk ){
		abl = ABL_KIND_MON;
		sub_abl = ABL_KIND_STR;
	} else {
		abl = ABL_KIND_FIG;
		sub_abl = ABL_KIND_STR;
	}

	dam = 0;
	dam += calc_abl_to_val( p, abl );
	dam += calc_abl_to_val( p, sub_abl );
	dam /= 2;

	if( abl == ABL_KIND_MON ){
		long	n;

		n = get_lev( p, abl );
		wpn_dam += DAM_MON_MUL * n;
		if( n > 0 )
			wpn_dam += DAM_MON_ADD;
	}

	if( is_mbr( p ) )
		dam = dam * calc_rate_abl_equip( p, abl ) / _100_PERCENT;

	/* FXの値を加える */

	wpn_dam += p->fx_data.wpn_dam;

#if	FLG_ITEM_ADD_RATE

	dam += DAM_AVE_N * wpn_dam / _100_PERCENT;

#else	/* FLG_ITEM_ADD_RATE */

	dam = dam * wpn_dam / _100_PERCENT;

#endif	/* FLG_ITEM_ADD_RATE */

	/* スキルで修整 */

	dam *= calc_skill_rate( p, SKILL_KIND_BERSERKER );
	dam /= _100_PERCENT;

	dam *= calc_skill_sub_rate( p, SKILL_KIND_ATTACKER,
			SKILL_KIND_BERSERKER );
	dam /= _100_PERCENT;

	dam *= calc_skill_sub_rate( p, SKILL_KIND_DEFENDER,
			SKILL_KIND_BERSERKER );
	dam /= _100_PERCENT;

	dam *= calc_skill_rate( p, SKILL_KIND_SIEGE );
	dam /= _100_PERCENT;

	if( dam < 1 )
		dam = 1;

	return dam;
}

/***************************************************************
* キャラクタの防御力を計算
* chr_t *p : キャラクタ
* return : 防御力
***************************************************************/

long	get_def( chr_t *p )
{
	long	def;
	rate_t	armor_def;
	abl_kind_t	abl;

	if( p == NULL )
		return 1;

	/* 能力値 */

	abl = get_def_abl( p );

	def = 0;
	def += calc_abl_to_val( p, abl );
	def += calc_abl_to_val( p, ABL_KIND_AGI );
	def /= 2;

	if( is_mbr( p ) )
		def = def * calc_rate_abl_equip( p, abl ) / _100_PERCENT;

	armor_def = get_armor_def( p, abl );

	if( armor_def < DEF_MIN_RATE )
		armor_def = DEF_MIN_RATE;

	/* FXの値を加える */

	armor_def += p->fx_data.armor_def;

#if	FLG_ITEM_ADD_RATE

	def += DEF_AVE_N * armor_def / _100_PERCENT;

#else	/* FLG_ITEM_ADD_RATE */

	def = def * armor_def / _100_PERCENT;

#endif	/* FLG_ITEM_ADD_RATE */

	/* スキルで修整 */

	def *= calc_skill_rate( p, SKILL_KIND_DEFENDER );
	def /= _100_PERCENT;

	def *= calc_skill_sub_rate( p, SKILL_KIND_ATTACKER,
			SKILL_KIND_DEFENDER );
	def /= _100_PERCENT;

	def *= calc_skill_sub_rate( p, SKILL_KIND_BERSERKER,
			SKILL_KIND_DEFENDER );
	def /= _100_PERCENT;

	def *= calc_skill_rate( p, SKILL_KIND_PHALANX );
	def /= _100_PERCENT;

	if( def < 1 )
		def = 1;

	return def;
}

/***************************************************************
* キャラクタの防御に使う能力値の種類を返す
* chr_t *p : キャラクタ
* return : 能力値の種類
***************************************************************/

abl_kind_t	get_def_abl( chr_t *p )
{
	if( p == NULL )
		return ABL_KIND_FIG;

	if( is_mbr( p ) ){
		item_t	*eq;
		bool_t	*flg_abl;

		eq = get_mbr_item_asgn_equip( (mbr_t *)p );
		if( eq == NULL )
			return ABL_KIND_FIG;

		if( eq[EQUIP_KIND_WIELDING].kind != ITEM_KIND_WPN )
			return ABL_KIND_MON;

		if( eq[EQUIP_KIND_WIELDING].tab.wpn == NULL )
			return ABL_KIND_MON;

		flg_abl = eq[EQUIP_KIND_WIELDING].tab.wpn->flg_abl;
		if( flg_abl[ABL_KIND_MON] )
			return ABL_KIND_MON;
		else
			return ABL_KIND_FIG;
	} else {
		long	lev_fig, lev_mon;

		lev_fig = get_lev( p, ABL_KIND_FIG );
		lev_mon = get_lev( p, ABL_KIND_MON );

		if( lev_fig > lev_mon )
			return ABL_KIND_FIG;
		else
			return ABL_KIND_MON;
	}

	return ABL_KIND_FIG;
}

/***************************************************************
* キャラクタの装備の防御力を計算
* chr_t *p : キャラクタ
* abl_kind_t abl : 能力値の種類
* return : 装備の防御力
***************************************************************/

long	get_armor_def( chr_t *p, abl_kind_t abl )
{
	long	armor_def = 0;

	if( abl == ABL_KIND_MON ){
		long	n;

		n = get_lev( p, abl );
		armor_def += DEF_MON_MUL * n;
		if( n > 0 )
			armor_def += DEF_MON_ADD;

		return armor_def;
	}

	if( is_mbr( p ) ){
		item_t	*eq;
		long	i;

		/* 防具のテーブルを得る */

		eq = get_mbr_item_asgn_equip( (mbr_t *)p );
		if( eq == NULL )
			return 1;

		/* 防具の値を加える */

		for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
			if( eq[i].kind != ITEM_KIND_ARMOR )
				continue;
			if( eq[i].tab.armor == NULL )
				continue;

			armor_def += eq[i].tab.armor->def;
			armor_def += add_def(
					eq[i].dat.armor.add_def );
		}
	} else if( p->kind == CHR_KIND_MNSTR ){
		/* 防具の値を加える */

		armor_def += p->mnstr_tab->def;
		armor_def += add_def( p->add_def );
	}

	/* FXの値を加える */

	armor_def += p->fx_data.armor_def;

	return armor_def;
}

/***************************************************************
* キャラクタのアーマー・クラスを計算
* chr_t *p : キャラクタ
* return : アーマー・クラス
***************************************************************/

long	get_ac( chr_t *p )
{
	long	ac;
	rate_t	armor_ac;

	if( p == NULL )
		return 1;

	ac = 0;
	armor_ac = 0;

	if( is_mbr( p ) ){
		item_t	*eq;
		long	i;

		/* 防具のテーブルを得る */

		eq = get_mbr_item_asgn_equip( (mbr_t *)p );
		if( eq == NULL )
			return 0;

		/* 防具の値を加える */

		for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
			if( eq[i].kind != ITEM_KIND_ARMOR )
				continue;
			if( eq[i].tab.armor == NULL )
				continue;

			armor_ac += eq[i].tab.armor->ac;
			armor_ac += add_ac(
					eq[i].dat.armor.add_ac );
		}
	} else if( p->kind == CHR_KIND_MNSTR ){
		/* 防具の値を加える */

		armor_ac += p->mnstr_tab->ac;
		armor_ac += add_ac( p->add_ac );
	}

	/* FXの値を加える */

	armor_ac += p->fx_data.armor_ac;

#if	FLG_ITEM_ADD_RATE

	ac += AC_AVE_N * armor_ac / _100_PERCENT;

#else	/* FLG_ITEM_ADD_RATE */

	ac = AC_AVE_N;
	ac = ac * armor_ac / _100_PERCENT;

#endif	/* FLG_ITEM_ADD_RATE */

	/* スキルで修整 */

	ac *= calc_skill_rate( p, SKILL_KIND_SENTINEL );
	ac /= _100_PERCENT;

	ac *= calc_skill_rate( p, SKILL_KIND_PHALANX );
	ac /= _100_PERCENT;

	if( ac < 1 )
		ac = 1;

	return ac;
}

/***************************************************************
* クリティカル率を攻撃側から防御側の値を引いて計算
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* const attack_t *attack : 攻撃データ
* return : クリティカル率
***************************************************************/

rate_t	get_crtcl( chr_t *o_p, chr_t *d_p, const attack_t *attack )
{
	rate_t	rate;

	rate = get_wpn_crtcl( o_p, attack );
	rate -= get_armor_crtcl( d_p );

	if( rate < 1 )
		rate = 1;

	return rate;
}

/***************************************************************
* 攻撃側のクリティカル率を計算
* chr_t *p : キャラクタ
* const attack_t *attack : 攻撃データ
* return : クリティカル率
***************************************************************/

rate_t	get_wpn_crtcl( chr_t *p, const attack_t *attack )
{
	rate_t	crtcl, wpn_crtcl, thf;

	if( p == NULL )
		return 1;
	if( attack == NULL )
		return 1;

	/* 能力値 */

	thf = 0;
	thf += get_lev( p, ABL_KIND_THI );
	thf += get_lev( p, ABL_KIND_DEX );
	thf /= 2;
	thf = thf * WPN_CRTCL_THF_LEV_RATE / _100_PERCENT;
	if( thf > WPN_CRTCL_THF_MAX_RATE )
		thf = WPN_CRTCL_THF_MAX_RATE;

	crtcl = thf;

	/* 武器の値を加える */

	wpn_crtcl = attack->crtcl;

	/* FXの値を加える */

	wpn_crtcl += p->fx_data.wpn_crtcl;

#if	FLG_ITEM_ADD_RATE

	crtcl += WPN_CRTCL_AVE_N * wpn_crtcl / _100_PERCENT;

#else	/* FLG_ITEM_ADD_RATE */

	crtcl = crtcl * wpn_crtcl / _100_PERCENT;

#endif	/* FLG_ITEM_ADD_RATE */

	/* スキルで修整 */

	crtcl *= calc_skill_rate( p, SKILL_KIND_ASSASSIN );
	crtcl /= _100_PERCENT;

	if( crtcl < 1 )
		crtcl = 1;

	return crtcl;
}

/***************************************************************
* 防御側のクリティカル率を計算
* chr_t *p : キャラクタ
* return : クリティカル率
***************************************************************/

rate_t	get_armor_crtcl( chr_t *p )
{
	rate_t	crtcl, armor_crtcl;

	if( p == NULL )
		return 1;

	crtcl = 0;
	armor_crtcl = 0;

	if( is_mbr( p ) ){
		item_t	*eq;
		long	i;

		/* 防具のテーブルを得る */

		eq = get_mbr_item_asgn_equip( (mbr_t *)p );
		if( eq == NULL )
			return 0;

		/* 防具の値を加える */

		for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
			if( eq[i].kind != ITEM_KIND_ARMOR )
				continue;
			if( eq[i].tab.armor == NULL )
				continue;

			armor_crtcl += eq[i].tab.armor->crtcl;
			armor_crtcl += add_armor_crtcl(
					eq[i].dat.armor.add_crtcl );
		}
	} else if( p->kind == CHR_KIND_MNSTR ){
		/* 防具の値を加える */

		armor_crtcl += p->mnstr_tab->armor_crtcl;
		armor_crtcl += add_armor_crtcl( p->add_crtcl );
	}

	/* FXの値を加える */

	armor_crtcl += p->fx_data.armor_crtcl;

#if	FLG_ITEM_ADD_RATE

	crtcl += ARMOR_CRTCL_AVE_N * armor_crtcl / _100_PERCENT;

#else	/* FLG_ITEM_ADD_RATE */

	crtcl = ARMOR_CRTCL_AVE_N;
	crtcl = crtcl * armor_crtcl / _100_PERCENT;

#endif	/* FLG_ITEM_ADD_RATE */

	/* スキルで修整 */

	crtcl *= calc_skill_rate( p, SKILL_KIND_AEGIS );
	crtcl /= _100_PERCENT;

	if( crtcl < 1 )
		crtcl = 1;

	return crtcl;
}

/***************************************************************
* 首切りが発生したか調べる
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* return : 首切りが発生したか?
***************************************************************/

bool_t	chk_ninja_crtcl( chr_t *o_p, chr_t *d_p )
{
	abl_kind_t	o_abl_m, o_abl_s;
	abl_kind_t	d_abl_m, d_abl_s;
	long	o_val, d_val;
	long	o_dice, d_dice;

	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( chk_resi_stat( d_p, FLG_STAT_DEAD ) )
		return FALSE;

	o_abl_m = ABL_KIND_NIN;
	o_abl_s = ABL_KIND_DEX;
	o_val = 0;
	o_val += calc_abl_to_val( o_p, o_abl_m );
	o_val += calc_abl_to_val( o_p, o_abl_s );
	o_val /= 2;

	d_abl_m = get_specialist_abl( d_p );
	d_abl_s = ABL_KIND_DEX;
	d_val = 0;
	d_val += calc_abl_to_val( d_p, d_abl_m );
	d_val += calc_abl_to_val( d_p, d_abl_s );
	d_val /= 2;

	if( get_lev( o_p, ABL_KIND_NIN ) <= 0 )
		return FALSE;

	o_val = o_val * NINJA_CRTCL_RATE / _100_PERCENT;

	o_dice = roll_dice( o_val, FALSE );
	d_dice = roll_dice( d_val, FALSE );

	if( o_dice > d_dice )
		return TRUE;
	else
		return FALSE;
}

/***************************************************************
* 攻撃力の修正値を修正率に変換
* long n : 修正値
* return : 修正率
***************************************************************/

rate_t	add_hit( long n )
{
	return( n * ADD_HIT_RATE );
}

/***************************************************************
* 攻撃側のクリティカルの修正値を修正率に変換
* long n : 修正値
* return : 修正率
***************************************************************/

rate_t	add_wpn_crtcl( long n )
{
	return( n * ADD_WPN_CRTCL_RATE );
}

/***************************************************************
* ダメージの修正値を修正率に変換
* long n : 修正値
* return : 修正率
***************************************************************/

rate_t	add_dam( long n )
{
	return( n * ADD_DAM_RATE );
}

/***************************************************************
* 両手持ちの武器かチェックして、ダメージの修正率を返す
* mbr_t *mbr : メンバー
* item_t *wpn : 武器
* return : 修正率
***************************************************************/

rate_t	add_dam_two_handed_wpn( mbr_t *mbr, item_t *wpn )
{
	item_t	*eq;

	if( mbr == NULL )
		return _100_PERCENT;
	if( !is_mbr( mbr ) )
		return _100_PERCENT;
	if( wpn == NULL )
		return _100_PERCENT;
	if( wpn->kind != ITEM_KIND_WPN )
		return _100_PERCENT;

	do {
		if( chk_flg( wpn->tab.wpn->flg,
				FLG_WPN_TAB_TWO_HANDED ) ){
			break;
		}
		if( chk_flg( wpn->tab.wpn->flg,
				FLG_WPN_TAB_CAN_TWO_HANDED ) ){
			break;
		}

		return _100_PERCENT;
	} while( 0 );

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return _100_PERCENT;
	if( eq[EQUIP_KIND_SHIELD].kind != ITEM_KIND_NULL )
		return _100_PERCENT;

	return TWO_HANDED_WPN_ADD_DAM_RATE;
}

/***************************************************************
* 防御力の修正値を修正率に変換
* long n : 修正値
* return : 修正率
***************************************************************/

rate_t	add_def( long n )
{
	return( n * ADD_DEF_RATE );
}

/***************************************************************
* 防御側のクリティカルの修正値を修正率に変換
* long n : 修正値
* return : 修正率
***************************************************************/

rate_t	add_armor_crtcl( long n )
{
	return( n * ADD_ARMOR_CRTCL_RATE );
}

/***************************************************************
* アーマー・クラスの修正値を修正率に変換
* long n : 修正値
* return : 修正率
***************************************************************/

rate_t	add_ac( long n )
{
	return( n * ADD_AC_RATE );
}

/***************************************************************
* 杖によるダメージを計算
* chr_t *p : キャラクタ
* return : 杖によるダメージ
***************************************************************/

long	get_dam_stick( chr_t *p )
{
	abl_kind_t	abl_main, abl_sub;

	long	dam;

	if( p == NULL )
		return 1;

	abl_main = get_specialist_abl( p );
	abl_sub = abl_main;

	dam = 0;
	dam += calc_abl_to_val( p, abl_main );
	dam += calc_abl_to_val( p, abl_sub );
	dam /= 2;

	dam = dam * DAM_STICK_RATE / _100_PERCENT;
	dam += DAM_STICK_ADD;

	if( dam < 1 )
		dam = 1;

	return dam;
}

/***************************************************************
* 呪文によるダメージを計算
* chr_t *p : キャラクタ
* abl_kind_t abl_main : 主能力値の種類
* abl_kind_t abl_sub : 従能力値の種類
* return : 呪文によるダメージ
***************************************************************/

long	get_dam_spell( chr_t *p, abl_kind_t abl_main, abl_kind_t abl_sub )
{
	long	dam;

	if( p == NULL )
		return 1;

	dam = 0;
	dam += calc_abl_to_val( p, abl_main );
	dam += calc_abl_to_val( p, abl_sub );
	dam /= 2;

	dam = dam * DAM_SPELL_RATE / _100_PERCENT;
	dam += DAM_SPELL_ADD;

	if( dam < 1 )
		dam = 1;

	return dam;
}

/***************************************************************
* キャラクタの耐性値を計算
* chr_t *p : キャラクタ
* resi_kind_t resi : 耐性値の種類
* return : キャラクタの耐性値
***************************************************************/

rate_t	get_resi_def( chr_t *p, resi_kind_t resi )
{
	rate_t	n;

	if( p == NULL )
		return _100_PERCENT;

	n = get_resi( p, resi );
	if( n == RESI_PERFECT_N )
		return RESI_PERFECT_N;
	if( n < 1)
		n = 1;

	return n;
}

/***************************************************************
* キャラクタ同士の距離から、飛び道具の攻撃率を計算
* chr_t *o_p : 攻撃側キャラクタ
* chr_t *d_p : 防御側キャラクタ
* return : 飛び道具の攻撃率
***************************************************************/

rate_t	get_chr_throw_range_rate( chr_t *o_p, chr_t *d_p )
{
	rate_t	rate;

	if( o_p == NULL )
		return( (rate_t)0 );
	if( d_p == NULL )
		return( (rate_t)0 );

	if( chk_xx_range() )
		return _100_PERCENT;

	rate = get_throw_range_rate(
			o_p->trgt.true_x, o_p->trgt.true_y,
			d_p->trgt.true_x, d_p->trgt.true_y );

	return rate;
}

/***************************************************************
* ２点間の距離から、飛び道具の攻撃率を計算
* long x1 : 始点X座標
* long y1 : 始点Y座標
* long x2 : 終点X座標
* long y2 : 終点Y座標
* return : 飛び道具の攻撃率
***************************************************************/

rate_t	get_throw_range_rate( long x1, long y1, long x2, long y2 )
{
	long	dx, dy, r;
	rate_t	rate;

	if( !clip_pos( x1, y1 ) )
		return( (rate_t)0 );
	if( !clip_pos( x2, y2 ) )
		return( (rate_t)0 );

	dx = labs( x1 - x2 );
	dy = labs( y1 - y2 );

	r = max_l( dx, dy );

	rate = _100_PERCENT;
	rate -= r * RATE_PER_RANGE / _100_PERCENT;

	print_msg( FLG_MSG_DEBUG, "fight range rate: %ld", rate );

	return rate;
}

/***************************************************************
* 攻撃の種類別のメッセージを返す
* const attack_t *attack : 攻撃データ
* return : 攻撃の種類別のメッセージ
***************************************************************/

char	*get_msg_attack( const attack_t *attack )
{
	switch( attack->kind ){
	case ATTACK_KIND_NULL:
		break;
	case ATTACK_KIND_SPELL:
	case ATTACK_KIND_SPELL_SELF:
	case ATTACK_KIND_SPELL_FRIEND:
		break;
	case ATTACK_KIND_PUNCH:
		return MSG_ATTACK_PUNCH;
	case ATTACK_KIND_KICK:
		return MSG_ATTACK_KICK;
	case ATTACK_KIND_KNOCK:
		return MSG_ATTACK_KNOCK;
	case ATTACK_KIND_SLASH:
		return MSG_ATTACK_SLASH;
	case ATTACK_KIND_STING:
		return MSG_ATTACK_STING;
	case ATTACK_KIND_MOW:
		return MSG_ATTACK_MOW;
	case ATTACK_KIND_SHOOT:
		return MSG_ATTACK_SHOOT;
	case ATTACK_KIND_THROW:
		return MSG_ATTACK_THROW;
	case ATTACK_KIND_BITE:
		return MSG_ATTACK_BITE;
	case ATTACK_KIND_PECK:
		return MSG_ATTACK_PECK;
	case ATTACK_KIND_CLAW:
		return MSG_ATTACK_CLAW;
	case ATTACK_KIND_NIP:
		return MSG_ATTACK_NIP;
	case ATTACK_KIND_STRANGLE:
		return MSG_ATTACK_STRANGLE;
	case ATTACK_KIND_TACKLE:
		return MSG_ATTACK_TACKLE;
	case ATTACK_KIND_TOUCH:
		return MSG_ATTACK_TOUCH;
	case ATTACK_KIND_INDICATE:
		return MSG_ATTACK_INDICATE;
	case ATTACK_KIND_KISS:
		return MSG_ATTACK_KISS;
	case ATTACK_KIND_SEDUCE:
		return MSG_ATTACK_SEDUCE;
	case ATTACK_KIND_CARESS_BUST:
		return MSG_ATTACK_CARESS_BUST;
	case ATTACK_KIND_CARESS_HIP:
		return MSG_ATTACK_CARESS_HIP;
	case ATTACK_KIND_CARESS_CROTCH:
		return MSG_ATTACK_CARESS_CROTCH;
	case ATTACK_KIND_CYBERN_PUNCH:
		return MSG_ATTACK_CYBERN_PUNCH;
	case ATTACK_KIND_CYBERN_KICK:
		return MSG_ATTACK_CYBERN_KICK;
	case ATTACK_KIND_XX_SLAP:
		return MSG_ATTACK_XX_SLAP;
	case ATTACK_KIND_MAX_N:
		break;
	}

	return MSG_NULL;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_fight_c( void )
{
	check_memory( check_memory_fight_c_mbr_attack_bash,
			"fight.c: mbr_attack_bash" );
	check_memory( check_memory_fight_c_mbr_attack_throw,
			"fight.c: mbr_attack_throw" );
	check_memory( check_memory_fight_c_mbr_attack_throw_light,
			"fight.c: mbr_attack_throw_light" );
}
