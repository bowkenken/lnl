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
* $Id: skill.c,v 1.18 2014/03/02 02:49:34 bowkenken Exp $
***************************************************************/

/***************************************************************
* ������
***************************************************************/

#define	SKILL_C
#include	"inc.h"

/***************************************************************
* �ѿ����
***************************************************************/

skill_kind_t	skill_group_tab[SKILL_GROUP_KIND_MAX_N]
	[SKILL_PER_GROUP_MAX_N + 1];
check_memory_def( check_memory_skill_c_skill_group_tab )

#include	"skill-tab.h"

/***************************************************************
* �����
***************************************************************/

void	init_skill( void )
{
	init_skill_group_tab();
}

/***************************************************************
* �����롦���롼�ס��ơ��֥�ν����
***************************************************************/

void	init_skill_group_tab( void )
{
	long	i;

	/* ̾�� */

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( skill_tab[i].kind == SKILL_KIND_NULL )
			break;
		if( skill_tab[i].name != NULL )
			continue;

		skill_tab[i].name = MSG( skill_tab[i].n_name );
	}

	/* ������Υ��롼�� */

	for( i = 0; i < SKILL_GROUP_KIND_MAX_N; i++ )
		skill_group_tab[i][0] = SKILL_KIND_NULL;

	/* ������򥰥롼�פ�ʬ�� */

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
* ������θ��̤�Ψ��׻�����
* mbr_t *mbr : ���С�
* skill_kind_t skill_kind : ������μ���
* return : ������θ��̤�Ψ
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
* ������Υ��ָ��̤�Ψ��׻�����
* mbr_t *mbr : ���С�
* skill_kind_t skill_kind : ������μ���
* return : ������Υ��ָ��̤�Ψ
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
* ���ƹ���˻��ä��Ƥ�����С����������
* mbr_t *mbr : ���С�
* return : ���С���
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
* �ɸ�ط��˻��ä��Ƥ�����С����������
* mbr_t *mbr : ���С�
* return : ���С���
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
* ������Υҥ�ȡ���å��������֤�
* skill_kind_t skill_kind : ������μ���
* return : �ҥ�ȡ���å�����
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
* ���С����������ͭ���ˤ��Ƥ��뤫Ĵ�٤�
* mbr_t *mbr : ���С�
* skill_kind_t skill_kind : ������μ���
* return : ͭ����?
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
* ���С��Υ������̾�����֤�
* mbr_t *mbr : ���С�
* long skill_n : �����롦����å��ֹ�
* return : �������̾��
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
* �������̾�����֤�
* skill_kind_t skill_kind : ������μ���
* return : �������̾��
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
* ���С��Υ�����Υ�٥���֤�
* mbr_t *mbr : ���С�
* long skill_n : �����롦����å��ֹ�
* return : ������Υ�٥�
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
* ���С��Υ�����ηи��ͤ��֤�
* mbr_t *mbr : ���С�
* long skill_n : �����롦����å��ֹ�
* return : ������ηи���
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
* ���С��Υ������ɬ�׷и��ͤ��֤�
* mbr_t *mbr : ���С�
* long skill_n : �����롦����å��ֹ�
* return : �������ɬ�׷и���
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
* �����롦���롼�ס��ơ��֥�˥�������ɲ�
* skill_group_kind_t group_kind : �����롦���롼�פμ���
* skill_kind_t skill_kind : ������μ���
* return : �ɲäǤ�����?
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
* ���饹���饹������������
* long class_n : ���饹�ֹ�
* long n : �����롦����å��ֹ�
* return : ����Ǥ�����?
***************************************************************/

bool_t	clr_skill_to_class( long class_n, long skill_n )
{
	return set_skill_to_class( class_n, skill_n, SKILL_KIND_NULL );
}

/***************************************************************
* ���饹�˥����������
* long class_n : ���饹�ֹ�
* long skill_n : �����롦����å��ֹ�
* skill_kind_t skill_kind : ������μ���
* return : ����Ǥ�����?
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
* ���饹�����ꤵ�줿��������֤�
* long class_n : ���饹�ֹ�
* long skill_n : �����롦����å��ֹ�
* return : ������μ���
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
* �������ơ��֥뤫�鸡������
* skill_kind_t skill_kind : ������μ���
* return : �ơ��֥�
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
* �����롦�ơ��֥���֤�
* return : �ơ��֥�
***************************************************************/

skill_tab_t	*get_skill_tab( void )
{
	return skill_tab;
}

/***************************************************************
* �����롦���롼����Υ�����μ�����֤�
* skill_group_kind_t kind : �����롦���롼��
* long n : ����ǥå���
* return : ������μ���
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
* �����롦���롼�פ�̾�����֤�
* skill_group_kind_t kind : �����롦���롼��
* return : �����롦���롼�פ�̾��
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
* ������ηи��ͤγ�꿶���׻�
* class_t *p : ���饹
* skill_kind_t skill_kind : ������μ���
* return : �и��ͤγ�꿶��Ψ
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
* �����ͤ�֥��᡼�������ϡפΥ�����μ�����Ѵ�
* resi_kind_t resi : ������
* return : ������μ���
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
* �����ͤ�������ϡפΥ�����μ�����Ѵ�
* resi_kind_t resi : ������
* return : ������μ���
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
* ���ơ�������֥��ơ����������ϡפΥ�����μ�����Ѵ�
* flg_stat_t stat : ���ơ�����
* return : ������μ���
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
* ���꡼�������å�
***************************************************************/

void	check_memory_skill_c( void )
{
	check_memory( check_memory_skill_c_skill_group_tab,
			"skill.c: skill_group_tab" );
}
