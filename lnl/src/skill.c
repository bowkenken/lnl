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
* $Id: skill.c,v 1.18 2014/03/02 02:49:34 bowkenken Exp $
***************************************************************/

/***************************************************************
* スキル
***************************************************************/

#define	SKILL_C
#include	"inc.h"

/***************************************************************
* 変数定義
***************************************************************/

skill_kind_t	skill_group_tab[SKILL_GROUP_KIND_MAX_N]
	[SKILL_PER_GROUP_MAX_N + 1];
check_memory_def( check_memory_skill_c_skill_group_tab )

#include	"skill-tab.h"

/***************************************************************
* 初期化
***************************************************************/

void	init_skill( void )
{
	init_skill_group_tab();
}

/***************************************************************
* スキル・グループ・テーブルの初期化
***************************************************************/

void	init_skill_group_tab( void )
{
	long	i;

	/* 名前 */

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( skill_tab[i].kind == SKILL_KIND_NULL )
			break;
		if( skill_tab[i].name != NULL )
			continue;

		skill_tab[i].name = MSG( skill_tab[i].n_name );
	}

	/* スキルのグループ */

	for( i = 0; i < SKILL_GROUP_KIND_MAX_N; i++ )
		skill_group_tab[i][0] = SKILL_KIND_NULL;

	/* スキルをグループに分類 */

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( skill_tab[i].kind == SKILL_KIND_NULL )
			break;
		if( !skill_tab[i].flg_ena )
			continue;

		add_skill_group_tab(
				skill_tab[i].group,
				skill_tab[i].kind );
	}
	if( i != SKILL_KIND_MAX_N - 1 ){
		print_msg( FLG_MSG_ERR, MSG_ERR_INIT_SKILL_GROUP,
				i, SKILL_KIND_MAX_N - 1 );
	}
}

/***************************************************************
* スキルの効果の率を計算する
* mbr_t *mbr : メンバー
* skill_kind_t skill_kind : スキルの種類
* return : スキルの効果の率
***************************************************************/

rate_t	calc_skill_rate( mbr_t *mbr, skill_kind_t skill_kind )
{
	rate_t	rate, rate_eq;
	long	lev;
	long	mbr_n;

	if( mbr == NULL )
		return _100_PERCENT;
	if( skill_kind <= SKILL_KIND_NULL )
		return _100_PERCENT;
	if( skill_kind >= SKILL_KIND_MAX_N )
		return _100_PERCENT;

	if( !chk_ena_skill( mbr, skill_kind ) )
		return _100_PERCENT;

	lev = mbr->abl.lev[ABL_KIND_MAX_N + skill_kind].n;

	rate = _100_PERCENT;

	switch( skill_kind ){
	case SKILL_KIND_NULL:
	case SKILL_KIND_MAX_N:
		break;

	/* SKILL_GROUP_KIND_FIGHT, */
	case SKILL_KIND_ATTACKER:
	case SKILL_KIND_BERSERKER:
	case SKILL_KIND_DEFENDER:
		rate = SKILL_FIGHT_A_BASE_RATE;
		rate += SKILL_FIGHT_A_ADD_RATE * lev;
		break;
	case SKILL_KIND_SENTINEL:
	case SKILL_KIND_ASSASSIN:
	case SKILL_KIND_AEGIS:
		rate = SKILL_FIGHT_B_BASE_RATE;
		rate += SKILL_FIGHT_B_ADD_RATE * lev;
		break;
	case SKILL_KIND_SIEGE:
		if( !is_mbr( mbr ) ){
			rate = _100_PERCENT;
			break;
		}

		mbr_n = calc_skill_siege_mbr_n( mbr );
		rate = _100_PERCENT;
		rate += SKILL_FIGHT_C_MUL_RATE * mbr_n;
		rate += SKILL_FIGHT_C_ADD_RATE * lev;
		break;
	case SKILL_KIND_PHALANX:
		if( !is_mbr( mbr ) ){
			rate = _100_PERCENT;
			break;
		}

		mbr_n = calc_skill_phalanx_mbr_n( mbr );
		rate = _100_PERCENT;
		rate += SKILL_FIGHT_C_MUL_RATE * mbr_n;
		rate += SKILL_FIGHT_C_ADD_RATE * lev;
		break;

	/* SKILL_GROUP_KIND_COMBO, */
	case SKILL_KIND_DOUBLE_ATTACK:
	case SKILL_KIND_COMBO:
	case SKILL_KIND_RAPID_SHOOT:
	case SKILL_KIND_COUNTER:
	case SKILL_KIND_TWO_SWORD_FENCING:
		break;

	/* SKILL_GROUP_KIND_DAM, */
	case SKILL_KIND_DAM_KNOC:
	case SKILL_KIND_DAM_SLAS:
	case SKILL_KIND_DAM_STIN:
	case SKILL_KIND_DAM_HEAT:
	case SKILL_KIND_DAM_COLD:
	case SKILL_KIND_DAM_MIND:
	case SKILL_KIND_DAM_ACID:
	case SKILL_KIND_DAM_ELEC:
	case SKILL_KIND_DAM_POIS:
		rate = SKILL_DAM_BASE_RATE;
		rate += SKILL_DAM_ADD_RATE * lev;
		break;

	/* SKILL_GROUP_KIND_RESI, */
	case SKILL_KIND_RESI_KNOC:
	case SKILL_KIND_RESI_SLAS:
	case SKILL_KIND_RESI_STIN:
	case SKILL_KIND_RESI_HEAT:
	case SKILL_KIND_RESI_COLD:
	case SKILL_KIND_RESI_MIND:
	case SKILL_KIND_RESI_ACID:
	case SKILL_KIND_RESI_ELEC:
	case SKILL_KIND_RESI_POIS:
		rate = SKILL_RESI_BASE_RATE;
		rate += SKILL_RESI_ADD_RATE * lev;
		break;

	/* SKILL_GROUP_KIND_RESI_STAT, */
	case SKILL_KIND_STAT_DEAD:
	case SKILL_KIND_STAT_STONE:
	case SKILL_KIND_STAT_PARALYZE:
	case SKILL_KIND_STAT_POISON:
	case SKILL_KIND_STAT_CONFUSION:
	case SKILL_KIND_STAT_BLIND:
	case SKILL_KIND_STAT_SLEEP:
	case SKILL_KIND_STAT_SILENCE:
	case SKILL_KIND_STAT_CAUGHT:
	case SKILL_KIND_STAT_FEAR:
	case SKILL_KIND_STAT_HALLUCINATION:
	case SKILL_KIND_STAT_CHARM:
	case SKILL_KIND_STAT_FLY:
	case SKILL_KIND_STAT_HUNGRY:
	case SKILL_KIND_STAT_STARVATION:
	case SKILL_KIND_STAT_FAINT:
	case SKILL_KIND_STAT_DRUNK:
	case SKILL_KIND_STAT_VANISH:
	case SKILL_KIND_STAT_IRON_BODY:
	case SKILL_KIND_STAT_PASSWALL:
	case SKILL_KIND_STAT_SENSE_INVISIBLE:
		rate = SKILL_STAT_BASE_N;
		rate += SKILL_STAT_ADD_N * lev;
		break;

	/* SKILL_GROUP_KIND_MISC, */
	case SKILL_KIND_RUN_AWAY:
		rate_eq = calc_rate_equip_flg_msg(
				mbr, ABL_KIND_THI, ABL_KIND_DEX, FALSE );
		if( rate_eq < _100_PERCENT )
			break;

		rate = SKILL_RUN_AWAY_BASE_N;
		rate += SKILL_RUN_AWAY_ADD_N * lev;
		break;
	}

	return rate;
}

/***************************************************************
* スキルのサブ効果の率を計算する
* mbr_t *mbr : メンバー
* skill_kind_t skill_kind : スキルの種類
* return : スキルのサブ効果の率
***************************************************************/

rate_t	calc_skill_sub_rate(
	mbr_t *mbr,
	skill_kind_t main_kind,
	skill_kind_t sub_kind
)
{
	rate_t	rate;

	if( mbr == NULL )
		return _100_PERCENT;
	if( main_kind <= SKILL_KIND_NULL )
		return _100_PERCENT;
	if( main_kind >= SKILL_KIND_MAX_N )
		return _100_PERCENT;
	if( sub_kind <= SKILL_KIND_NULL )
		return _100_PERCENT;
	if( sub_kind >= SKILL_KIND_MAX_N )
		return _100_PERCENT;

	if( !chk_ena_skill( mbr, main_kind ) )
		return _100_PERCENT;

	rate = _100_PERCENT;

	switch( sub_kind ){
	case SKILL_KIND_NULL:
	case SKILL_KIND_MAX_N:
		break;

	/* SKILL_GROUP_KIND_FIGHT, */
	case SKILL_KIND_ATTACKER:
	case SKILL_KIND_BERSERKER:
	case SKILL_KIND_DEFENDER:
		rate = SKILL_FIGHT_A_SUB_BASE_RATE;
		break;
	case SKILL_KIND_SENTINEL:
	case SKILL_KIND_ASSASSIN:
	case SKILL_KIND_AEGIS:
	case SKILL_KIND_SIEGE:
	case SKILL_KIND_PHALANX:
		break;

	/* SKILL_GROUP_KIND_COMBO, */
	case SKILL_KIND_DOUBLE_ATTACK:
	case SKILL_KIND_COMBO:
	case SKILL_KIND_RAPID_SHOOT:
	case SKILL_KIND_COUNTER:
	case SKILL_KIND_TWO_SWORD_FENCING:
		break;

	/* SKILL_GROUP_KIND_DAM, */
	case SKILL_KIND_DAM_KNOC:
	case SKILL_KIND_DAM_SLAS:
	case SKILL_KIND_DAM_STIN:
	case SKILL_KIND_DAM_HEAT:
	case SKILL_KIND_DAM_COLD:
	case SKILL_KIND_DAM_MIND:
	case SKILL_KIND_DAM_ACID:
	case SKILL_KIND_DAM_ELEC:
	case SKILL_KIND_DAM_POIS:
		break;

	/* SKILL_GROUP_KIND_RESI, */
	case SKILL_KIND_RESI_KNOC:
	case SKILL_KIND_RESI_SLAS:
	case SKILL_KIND_RESI_STIN:
	case SKILL_KIND_RESI_HEAT:
	case SKILL_KIND_RESI_COLD:
	case SKILL_KIND_RESI_MIND:
	case SKILL_KIND_RESI_ACID:
	case SKILL_KIND_RESI_ELEC:
	case SKILL_KIND_RESI_POIS:
		break;

	/* SKILL_GROUP_KIND_RESI_STAT, */
	case SKILL_KIND_STAT_DEAD:
	case SKILL_KIND_STAT_STONE:
	case SKILL_KIND_STAT_PARALYZE:
	case SKILL_KIND_STAT_POISON:
	case SKILL_KIND_STAT_CONFUSION:
	case SKILL_KIND_STAT_BLIND:
	case SKILL_KIND_STAT_SLEEP:
	case SKILL_KIND_STAT_SILENCE:
	case SKILL_KIND_STAT_CAUGHT:
	case SKILL_KIND_STAT_FEAR:
	case SKILL_KIND_STAT_HALLUCINATION:
	case SKILL_KIND_STAT_CHARM:
	case SKILL_KIND_STAT_FLY:
	case SKILL_KIND_STAT_HUNGRY:
	case SKILL_KIND_STAT_STARVATION:
	case SKILL_KIND_STAT_FAINT:
	case SKILL_KIND_STAT_DRUNK:
	case SKILL_KIND_STAT_VANISH:
	case SKILL_KIND_STAT_IRON_BODY:
	case SKILL_KIND_STAT_PASSWALL:
	case SKILL_KIND_STAT_SENSE_INVISIBLE:
		break;

	/* SKILL_GROUP_KIND_MISC, */
	case SKILL_KIND_RUN_AWAY:
		break;
	}

	return rate;
}

/***************************************************************
* 一斉攻撃に参加しているメンバー数を数える
* mbr_t *mbr : メンバー
* return : メンバー数
***************************************************************/

long	calc_skill_siege_mbr_n( mbr_t *mbr )
{
	long	n;
	party_t	*pty;
	long	i;

	if( mbr == NULL )
		return 0;
	if( mbr->kind != CHR_KIND_MBR )
		return 0;
	if( chk_flg_or( mbr->stat, FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_CONFUSION
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		return 0;
	}
	if( !clip_pos( mbr->x, mbr->y ) )
		return 0;

	n = 0;
	pty = get_party();
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( i == mbr->mbr_n )
			continue;
		if( chk_flg_or( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD
				| FLG_STAT_STONE
				| FLG_STAT_PARALYZE
				| FLG_STAT_CONFUSION
				| FLG_STAT_SLEEP
				| FLG_STAT_FAINT ) ){
			continue;
		}
		if( !clip_pos( pty->mbr[i]->x, pty->mbr[i]->y ) )
			continue;
		if( labs( pty->mbr[i]->x - mbr->x ) > SIEGE_R )
			continue;
		if( labs( pty->mbr[i]->y - mbr->y ) > SIEGE_R )
			continue;
		if( pty->mbr[i]->trgt.kind != mbr->trgt.kind )
			continue;
		if( pty->mbr[i]->trgt.p != mbr->trgt.p )
			continue;

		n++;
	}

	return n;
}

/***************************************************************
* 防御陣形に参加しているメンバー数を数える
* mbr_t *mbr : メンバー
* return : メンバー数
***************************************************************/

long	calc_skill_phalanx_mbr_n( mbr_t *mbr )
{
	long	n;
	party_t	*pty;
	long	i;

	if( mbr == NULL )
		return 0;
	if( mbr->kind != CHR_KIND_MBR )
		return 0;
	if( chk_flg_or( mbr->stat, FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_CONFUSION
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		return 0;
	}
	if( !clip_pos( mbr->x, mbr->y ) )
		return 0;

	n = 0;
	pty = get_party();
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( i == mbr->mbr_n )
			continue;
		if( chk_flg_or( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD
				| FLG_STAT_STONE
				| FLG_STAT_PARALYZE
				| FLG_STAT_CONFUSION
				| FLG_STAT_SLEEP
				| FLG_STAT_FAINT ) ){
			continue;
		}
		if( !clip_pos( pty->mbr[i]->x, pty->mbr[i]->y ) )
			continue;
		if( labs( pty->mbr[i]->x - mbr->x ) > PHALANX_R )
			continue;
		if( labs( pty->mbr[i]->y - mbr->y ) > PHALANX_R )
			continue;

		n++;
	}

	return n;
}

/***************************************************************
* スキルのヒント・メッセージを返す
* skill_kind_t skill_kind : スキルの種類
* return : ヒント・メッセージ
***************************************************************/

const char	*get_skill_hint( skill_kind_t skill_kind )
{
	static char	str[SKILL_HINT_MAX_BYTE + 1];

	str[0] = '\0';

	if( skill_kind <= SKILL_KIND_NULL )
		return str;
	if( skill_kind >= SKILL_KIND_MAX_N )
		return str;

	switch( skill_kind ){
	case SKILL_KIND_NULL:
	case SKILL_KIND_MAX_N:
		break;

	/* SKILL_GROUP_KIND_FIGHT, */
	case SKILL_KIND_ATTACKER:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_ATTACKER,
				SKILL_FIGHT_A_BASE_RATE,
				SKILL_FIGHT_A_SUB_BASE_RATE );
		break;
	case SKILL_KIND_BERSERKER:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_BERSERKER,
				SKILL_FIGHT_A_BASE_RATE,
				SKILL_FIGHT_A_SUB_BASE_RATE );
		break;
	case SKILL_KIND_DEFENDER:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_DEFENDER,
				SKILL_FIGHT_A_BASE_RATE,
				SKILL_FIGHT_A_SUB_BASE_RATE );
		break;
	case SKILL_KIND_SENTINEL:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_SENTINEL,
				SKILL_FIGHT_B_BASE_RATE );
		break;
	case SKILL_KIND_ASSASSIN:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_ASSASSIN,
				SKILL_FIGHT_B_BASE_RATE );
		break;
	case SKILL_KIND_AEGIS:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_AEGIS,
				SKILL_FIGHT_B_BASE_RATE );
		break;
	case SKILL_KIND_SIEGE:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_SIEGE,
				SKILL_FIGHT_C_MUL_RATE );
		break;
	case SKILL_KIND_PHALANX:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_PHALANX,
				SKILL_FIGHT_C_MUL_RATE );
		break;

	/* SKILL_GROUP_KIND_COMBO, */
	case SKILL_KIND_DOUBLE_ATTACK:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_DOUBLE_ATTACK,
				SKILL_FIG_BASE_RATE );
		break;
	case SKILL_KIND_COMBO:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_COMBO,
				SKILL_MON_BASE_RATE );
		break;
	case SKILL_KIND_RAPID_SHOOT:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_RAPID_SHOOT,
				SKILL_HUN_BASE_RATE );
		break;
	case SKILL_KIND_COUNTER:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_COUNTER,
				SKILL_COUNTER_BASE_RATE );
		break;
	case SKILL_KIND_TWO_SWORD_FENCING:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_TWO_SWORD_FENCING,
				SKILL_TWO_SWORD_FENCING_BASE_RATE );
		break;

	/* SKILL_GROUP_KIND_DAM, */
	case SKILL_KIND_DAM_KNOC:
	case SKILL_KIND_DAM_SLAS:
	case SKILL_KIND_DAM_STIN:
	case SKILL_KIND_DAM_HEAT:
	case SKILL_KIND_DAM_COLD:
	case SKILL_KIND_DAM_MIND:
	case SKILL_KIND_DAM_ACID:
	case SKILL_KIND_DAM_ELEC:
	case SKILL_KIND_DAM_POIS:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_DAM,
				SKILL_DAM_BASE_RATE );
		break;

	/* SKILL_GROUP_KIND_RESI, */
	case SKILL_KIND_RESI_KNOC:
	case SKILL_KIND_RESI_SLAS:
	case SKILL_KIND_RESI_STIN:
	case SKILL_KIND_RESI_HEAT:
	case SKILL_KIND_RESI_COLD:
	case SKILL_KIND_RESI_MIND:
	case SKILL_KIND_RESI_ACID:
	case SKILL_KIND_RESI_ELEC:
	case SKILL_KIND_RESI_POIS:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_RESI,
				SKILL_RESI_BASE_RATE );
		break;

	/* SKILL_GROUP_KIND_RESI_STAT, */
	case SKILL_KIND_STAT_DEAD:
	case SKILL_KIND_STAT_STONE:
	case SKILL_KIND_STAT_PARALYZE:
	case SKILL_KIND_STAT_POISON:
	case SKILL_KIND_STAT_CONFUSION:
	case SKILL_KIND_STAT_BLIND:
	case SKILL_KIND_STAT_SLEEP:
	case SKILL_KIND_STAT_SILENCE:
	case SKILL_KIND_STAT_CAUGHT:
	case SKILL_KIND_STAT_FEAR:
	case SKILL_KIND_STAT_HALLUCINATION:
	case SKILL_KIND_STAT_CHARM:
	case SKILL_KIND_STAT_FLY:
	case SKILL_KIND_STAT_HUNGRY:
	case SKILL_KIND_STAT_STARVATION:
	case SKILL_KIND_STAT_FAINT:
	case SKILL_KIND_STAT_DRUNK:
	case SKILL_KIND_STAT_VANISH:
	case SKILL_KIND_STAT_IRON_BODY:
	case SKILL_KIND_STAT_PASSWALL:
	case SKILL_KIND_STAT_SENSE_INVISIBLE:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_STAT );
				/* SKILL_STAT_BASE_N */
		break;

	/* SKILL_GROUP_KIND_MISC, */
	case SKILL_KIND_RUN_AWAY:
		sn_printf( str, SKILL_HINT_MAX_BYTE,
				MSG_SKILL_HINT_RUN_AWAY,
				SKILL_RUN_AWAY_BASE_N );
		break;
	}

	return str;
}

/***************************************************************
* メンバーがスキルを有効にしているか調べる
* mbr_t *mbr : メンバー
* skill_kind_t skill_kind : スキルの種類
* return : 有効か?
***************************************************************/

bool_t	chk_ena_skill( mbr_t *mbr, skill_kind_t skill_kind )
{
	class_t	*class_tab, *p;
	long	i;

	if( mbr == NULL )
		return FALSE;

	class_tab = get_class_tab();
	if( class_tab == NULL )
		return FALSE;

	p = &(class_tab[mbr->class_n]);

	for( i = 0; i < SKILL_MAX_N; i++ )
		if( p->skill[i] == skill_kind )
			return TRUE;

	return FALSE;
}

/***************************************************************
* メンバーのスキルの名前を返す
* mbr_t *mbr : メンバー
* long skill_n : スキル・スロット番号
* return : スキルの名前
***************************************************************/

const char	*get_skill_name_from_slot( mbr_t *mbr, long skill_n )
{
	skill_kind_t	kind;

	if( mbr == NULL )
		return MSG_SKILL_NAME_NULL;

	kind = get_skill_from_class( mbr->class_n, skill_n );

	return get_skill_name_from_kind( kind );
}

/***************************************************************
* スキルの名前を返す
* skill_kind_t skill_kind : スキルの種類
* return : スキルの名前
***************************************************************/

const char	*get_skill_name_from_kind( skill_kind_t skill_kind )
{
	skill_tab_t	*tab;

	tab = get_skill_n_tab( skill_kind );
	if( tab == NULL )
		return MSG_SKILL_NAME_NULL;

	if( tab->name == NULL )
		tab->name = MSG( tab->n_name );

	return tab->name;
}

/***************************************************************
* メンバーのスキルのレベルを返す
* mbr_t *mbr : メンバー
* long skill_n : スキル・スロット番号
* return : スキルのレベル
***************************************************************/

long	get_skill_lev_from_slot( mbr_t *mbr, long skill_n )
{
	skill_kind_t	kind;

	if( mbr == NULL )
		return 0;

	kind = get_skill_from_class( mbr->class_n, skill_n );
	if( kind == SKILL_KIND_NULL )
		return 0;

	return mbr->abl.lev[ABL_KIND_MAX_N + kind].n;
}

/***************************************************************
* メンバーのスキルの経験値を返す
* mbr_t *mbr : メンバー
* long skill_n : スキル・スロット番号
* return : スキルの経験値
***************************************************************/

long	get_skill_exp_from_slot( mbr_t *mbr, long skill_n )
{
	skill_kind_t	kind;

	if( mbr == NULL )
		return 0;

	kind = get_skill_from_class( mbr->class_n, skill_n );
	if( kind == SKILL_KIND_NULL )
		return 0;

	return mbr->abl.exp[ABL_KIND_MAX_N + kind].n;
}

/***************************************************************
* メンバーのスキルの必要経験値を返す
* mbr_t *mbr : メンバー
* long skill_n : スキル・スロット番号
* return : スキルの必要経験値
***************************************************************/

long	get_skill_need_exp_from_slot( mbr_t *mbr, long skill_n )
{
	skill_kind_t	kind;
	abl_kind_t	abl;
	long	lev;
	long	exp;

	if( mbr == NULL )
		return 0;

	kind = get_skill_from_class( mbr->class_n, skill_n );
	if( kind == SKILL_KIND_NULL )
		return 0;

	lev = get_skill_lev_from_slot( mbr, skill_n );
	abl = (abl_kind_t)(ABL_KIND_MAX_N + kind);
	exp = calc_need_exp( lev + 1, abl );

	return exp;
}

/***************************************************************
* スキル・グループ・テーブルにスキルを追加
* skill_group_kind_t group_kind : スキル・グループの種類
* skill_kind_t skill_kind : スキルの種類
* return : 追加できたか?
***************************************************************/

bool_t	add_skill_group_tab(
	skill_group_kind_t group_kind,
	skill_kind_t skill_kind
)
{
	long	j;

	if( group_kind <= SKILL_GROUP_KIND_NULL )
		return FALSE;
	if( group_kind >= SKILL_GROUP_KIND_MAX_N )
		return FALSE;
	if( skill_kind <= SKILL_KIND_NULL )
		return FALSE;
	if( skill_kind >= SKILL_KIND_MAX_N )
		return FALSE;

	for( j = 0; j < SKILL_PER_GROUP_MAX_N; j++ ){
		if( skill_group_tab[group_kind][j] != SKILL_KIND_NULL )
			continue;

		skill_group_tab[group_kind][j] = skill_kind;
		skill_group_tab[group_kind][j + 1] = SKILL_KIND_NULL;
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* クラスからスキルの設定を解除
* long class_n : クラス番号
* long n : スキル・スロット番号
* return : 解除できたか?
***************************************************************/

bool_t	clr_skill_to_class( long class_n, long skill_n )
{
	return set_skill_to_class( class_n, skill_n, SKILL_KIND_NULL );
}

/***************************************************************
* クラスにスキルを設定
* long class_n : クラス番号
* long skill_n : スキル・スロット番号
* skill_kind_t skill_kind : スキルの種類
* return : 設定できたか?
***************************************************************/

bool_t	set_skill_to_class( long class_n, long skill_n, skill_kind_t kind )
{
	class_t	*tab;

	if( class_n < 0 )
		return FALSE;
	if( class_n >= CLASS_MAX_N )
		return FALSE;
	if( skill_n < 0 )
		return FALSE;
	if( skill_n >= SKILL_MAX_N )
		return FALSE;
	if( kind < SKILL_KIND_NULL )
		return FALSE;
	if( kind >= SKILL_KIND_MAX_N )
		return FALSE;

	tab = get_class_tab();
	if( tab == NULL )
		return FALSE;

	tab[class_n].skill[skill_n] = kind;
	return TRUE;
}

/***************************************************************
* クラスに設定されたスキルを返す
* long class_n : クラス番号
* long skill_n : スキル・スロット番号
* return : スキルの種類
***************************************************************/

skill_kind_t	get_skill_from_class( long class_n, long skill_n )
{
	class_t	*tab;

	if( class_n < 0 )
		return SKILL_KIND_NULL;
	if( class_n >= CLASS_MAX_N )
		return SKILL_KIND_NULL;
	if( skill_n < 0 )
		return SKILL_KIND_NULL;
	if( skill_n >= SKILL_MAX_N )
		return SKILL_KIND_NULL;

	tab = get_class_tab();
	if( tab == NULL )
		return SKILL_KIND_NULL;

	return( tab[class_n].skill[skill_n] );
}

/***************************************************************
* スキルをテーブルから検索する
* skill_kind_t skill_kind : スキルの種類
* return : テーブル
***************************************************************/

skill_tab_t	*get_skill_n_tab( skill_kind_t kind )
{
	long	i;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( skill_tab[i].kind == SKILL_KIND_NULL )
			return NULL;

		if( skill_tab[i].kind == kind )
			return &(skill_tab[i]);
	}

	return NULL;
}

/***************************************************************
* スキル・テーブルを返す
* return : テーブル
***************************************************************/

skill_tab_t	*get_skill_tab( void )
{
	return skill_tab;
}

/***************************************************************
* スキル・グループ中のスキルの種類を返す
* skill_group_kind_t kind : スキル・グループ
* long n : インデックス
* return : スキルの種類
***************************************************************/

skill_kind_t	get_skill_kind_from_group(
	skill_group_kind_t kind, long n
)
{
	if( kind < 0 )
		return SKILL_KIND_NULL;
	if( kind >= SKILL_GROUP_KIND_MAX_N )
		return SKILL_KIND_NULL;
	if( n < 0 )
		return SKILL_KIND_NULL;
	if( n >= SKILL_PER_GROUP_MAX_N )
		return SKILL_KIND_NULL;

	return skill_group_tab[kind][n];
}

/***************************************************************
* スキル・グループの名前を返す
* skill_group_kind_t kind : スキル・グループ
* return : スキル・グループの名前
***************************************************************/

const char	*get_skill_group_name( skill_group_kind_t kind )
{
	switch( kind ){
	case SKILL_GROUP_KIND_NULL:
	case SKILL_GROUP_KIND_MAX_N:
		return MSG_SKILL_GROUP_NAME_NULL;
	case SKILL_GROUP_KIND_FIGHT:
		return MSG_SKILL_GROUP_NAME_FIGHT;
	case SKILL_GROUP_KIND_COMBO:
		return MSG_SKILL_GROUP_NAME_COMBO;
	case SKILL_GROUP_KIND_DAM:
		return MSG_SKILL_GROUP_NAME_DAM;
	case SKILL_GROUP_KIND_RESI:
		return MSG_SKILL_GROUP_NAME_RESI;
	case SKILL_GROUP_KIND_RESI_STAT_1:
		return MSG_SKILL_GROUP_NAME_RESI_STAT_1;
	case SKILL_GROUP_KIND_RESI_STAT_2:
		return MSG_SKILL_GROUP_NAME_RESI_STAT_2;
	case SKILL_GROUP_KIND_MISC:
		return MSG_SKILL_GROUP_NAME_MISC;
	}

	return MSG_SKILL_GROUP_NAME_NULL;
}

/***************************************************************
* スキルの経験値の割り振りを計算
* class_t *p : クラス
* skill_kind_t skill_kind : スキルの種類
* return : 経験値の割り振り率
***************************************************************/

rate_t	calc_skill_exp_rate( class_t *p, skill_kind_t skill_kind )
{
	long	skill_n;
	rate_t	rate;
	long	i;

	if( p == NULL )
		return 0;
	if( skill_kind <= SKILL_KIND_NULL )
		return 0;
	if( skill_kind >= SKILL_KIND_MAX_N )
		return 0;

	skill_n = 0;
	for( i = 0; i < SKILL_MAX_N; i++ )
		if( p->skill[i] != SKILL_KIND_NULL )
			skill_n++;

	if( skill_n <= 0 )
		return 0;

	rate = _100_PERCENT / skill_n;
	return rate;
}

/***************************************************************
* 耐性値を「ダメージ強化系」のスキルの種類に変換
* resi_kind_t resi : 耐性値
* return : スキルの種類
***************************************************************/

skill_kind_t	cv_resi_to_skill_dam( resi_kind_t resi )
{
	switch( resi ){
	case RESI_KIND_KNOC:
		return SKILL_KIND_DAM_KNOC;
	case RESI_KIND_SLAS:
		return SKILL_KIND_DAM_SLAS;
	case RESI_KIND_STIN:
		return SKILL_KIND_DAM_STIN;
	case RESI_KIND_HEAT:
		return SKILL_KIND_DAM_HEAT;
	case RESI_KIND_COLD:
		return SKILL_KIND_DAM_COLD;
	case RESI_KIND_MIND:
		return SKILL_KIND_DAM_MIND;
	case RESI_KIND_ACID:
		return SKILL_KIND_DAM_ACID;
	case RESI_KIND_ELEC:
		return SKILL_KIND_DAM_ELEC;
	case RESI_KIND_POIS:
		return SKILL_KIND_DAM_POIS;
	case RESI_KIND_MAX_N:
		break;
	}

	return SKILL_KIND_NULL;
}

/***************************************************************
* 耐性値を「耐性系」のスキルの種類に変換
* resi_kind_t resi : 耐性値
* return : スキルの種類
***************************************************************/

skill_kind_t	cv_resi_to_skill_resi( resi_kind_t resi )
{
	switch( resi ){
	case RESI_KIND_KNOC:
		return SKILL_KIND_RESI_KNOC;
	case RESI_KIND_SLAS:
		return SKILL_KIND_RESI_SLAS;
	case RESI_KIND_STIN:
		return SKILL_KIND_RESI_STIN;
	case RESI_KIND_HEAT:
		return SKILL_KIND_RESI_HEAT;
	case RESI_KIND_COLD:
		return SKILL_KIND_RESI_COLD;
	case RESI_KIND_MIND:
		return SKILL_KIND_RESI_MIND;
	case RESI_KIND_ACID:
		return SKILL_KIND_RESI_ACID;
	case RESI_KIND_ELEC:
		return SKILL_KIND_RESI_ELEC;
	case RESI_KIND_POIS:
		return SKILL_KIND_RESI_POIS;
	case RESI_KIND_MAX_N:
		break;
	}

	return SKILL_KIND_NULL;
}

/***************************************************************
* ステータスを「ステータス耐性系」のスキルの種類に変換
* flg_stat_t stat : ステータス
* return : スキルの種類
***************************************************************/

skill_kind_t	cv_stat_to_skill_stat( flg_stat_t stat )
{
	if( chk_flg( stat, FLG_STAT_DEAD ) )
		return SKILL_KIND_STAT_DEAD;
	if( chk_flg( stat, FLG_STAT_STONE ) )
		return SKILL_KIND_STAT_STONE;
	if( chk_flg( stat, FLG_STAT_PARALYZE ) )
		return SKILL_KIND_STAT_PARALYZE;
	if( chk_flg( stat, FLG_STAT_POISON ) )
		return SKILL_KIND_STAT_POISON;
	if( chk_flg( stat, FLG_STAT_CONFUSION ) )
		return SKILL_KIND_STAT_CONFUSION;
	if( chk_flg( stat, FLG_STAT_BLIND ) )
		return SKILL_KIND_STAT_BLIND;
	if( chk_flg( stat, FLG_STAT_SLEEP ) )
		return SKILL_KIND_STAT_SLEEP;
	if( chk_flg( stat, FLG_STAT_SILENCE ) )
		return SKILL_KIND_STAT_SILENCE;
	if( chk_flg( stat, FLG_STAT_CAUGHT ) )
		return SKILL_KIND_STAT_CAUGHT;
	if( chk_flg( stat, FLG_STAT_FEAR ) )
		return SKILL_KIND_STAT_FEAR;
	if( chk_flg( stat, FLG_STAT_HALLUCINATION ) )
		return SKILL_KIND_STAT_HALLUCINATION;
	if( chk_flg( stat, FLG_STAT_CHARM ) )
		return SKILL_KIND_STAT_CHARM;
	if( chk_flg( stat, FLG_STAT_FLY ) )
		return SKILL_KIND_STAT_FLY;
	if( chk_flg( stat, FLG_STAT_HUNGRY ) )
		return SKILL_KIND_STAT_HUNGRY;
	if( chk_flg( stat, FLG_STAT_STARVATION ) )
		return SKILL_KIND_STAT_STARVATION;
	if( chk_flg( stat, FLG_STAT_FAINT ) )
		return SKILL_KIND_STAT_FAINT;
	if( chk_flg( stat, FLG_STAT_DRUNK ) )
		return SKILL_KIND_STAT_DRUNK;
	if( chk_flg( stat, FLG_STAT_VANISH ) )
		return SKILL_KIND_STAT_VANISH;
	if( chk_flg( stat, FLG_STAT_IRON_BODY ) )
		return SKILL_KIND_STAT_IRON_BODY;
	if( chk_flg( stat, FLG_STAT_PASSWALL ) )
		return SKILL_KIND_STAT_PASSWALL;
	if( chk_flg( stat, FLG_STAT_SENSE_INVISIBLE ) )
		return SKILL_KIND_STAT_SENSE_INVISIBLE;

	return SKILL_KIND_NULL;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_skill_c( void )
{
	check_memory( check_memory_skill_c_skill_group_tab,
			"skill.c: skill_group_tab" );
}
