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
* $Id: scene.c,v 1.23 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �������ڤ��ؤ�
***************************************************************/

#define	SCENE_C
#include	"inc.h"

/***************************************************************
* �ѿ����
***************************************************************/

static scene_n_t	scene_n;
check_memory_def( check_memory_scene_c_scene_n )
static last_scene_n_t	last_scene_n;
check_memory_def( check_memory_scene_c_last_scene_n )

/***************************************************************
* ������ν����
***************************************************************/

void	init_scene( void )
{
	scene_n = SCENE_N_NULL;
	last_scene_n = LAST_SCENE_N_NULL;
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_scene( void )
{
}

/***************************************************************
* �����˱����ƥ�������ڤ��ؤ���
***************************************************************/

void	chk_change_scene( void )
{
	switch( scene_n ){
	case SCENE_N_NULL:
		break;
	case SCENE_N_INIT:
	case SCENE_N_TITLE:
	case SCENE_N_OPENING:
		break;
	case SCENE_N_TOWN:
		chk_change_scene_town();
		break;
	case SCENE_N_SHOP:
		break;
	case SCENE_N_DUN:
		chk_change_scene_dun();
		break;
	case SCENE_N_BATTLE:
		chk_change_scene_battle();
		break;
	case SCENE_N_BATTLE_BOSS:
		chk_change_scene_battle_boss();
		break;
	case SCENE_N_LAST_BOSS:
		break;
	case SCENE_N_GAME_OVER:
	case SCENE_N_GAME_OVER_WAIT:
	case SCENE_N_GAME_OVER_END:
	case SCENE_N_ENDING:
	case SCENE_N_ENDING_EPILOGUE:
	case SCENE_N_ENDING_SPACE:
	case SCENE_N_ENDING_STAFF_ROLL:
	case SCENE_N_ENDING_END:
	case SCENE_N_SEL_MBR_GRAPH:
		break;
	case SCENE_N_MAX_N:
		break;
	}
}

/***************************************************************
* �����˱����ƥ�������ڤ��ؤ��� (����)
***************************************************************/

void	chk_change_scene_town( void )
{
	chk_change_scene_dun();
}

/***************************************************************
* �����˱����ƥ�������ڤ��ؤ��� (�µ���)
***************************************************************/

void	chk_change_scene_dun( void )
{
	if( scene_srch_boss() ){
		change_scene( SCENE_N_BATTLE_BOSS );
		return;
	}

	if( scene_srch_battle() ){
		change_scene( SCENE_N_BATTLE );
		return;
	}
}

/***************************************************************
* �����˱����ƥ�������ڤ��ؤ��� (��Ʈ��)
***************************************************************/

void	chk_change_scene_battle( void )
{
	dun_t	*dun;

	if( scene_n != SCENE_N_BATTLE )
		return;
	if( scene_srch_battle() )
		return;

	/* ��Ʈ����λ���� */

	dun = get_dun();
	if( dun->lev == 0 )
		change_scene( SCENE_N_TOWN );
	else
		change_scene( SCENE_N_DUN );
}

/***************************************************************
* �����˱����ƥ�������ڤ��ؤ��� (�ܥ�����)
***************************************************************/

void	chk_change_scene_battle_boss( void )
{
	dun_t	*dun;

	if( scene_n != SCENE_N_BATTLE_BOSS )
		return;
	if( scene_srch_boss() )
		return;

	/* �ܥ��郎��λ���� */

	dun = get_dun();
	if( dun->lev == 0 )
		change_scene( SCENE_N_TOWN );
	else
		change_scene( SCENE_N_DUN );
}

/***************************************************************
* �������ܥ����椫Ĵ�٤�
* return : �ܥ����椫?
***************************************************************/

bool_t	scene_srch_boss( void )
{
	dun_t	*dun;
	mnstr_t	*mns_head, *mns_p;

	dun = get_dun();
	if( dun->lev == 0 )
		return FALSE;
	if( (dun->lev % DUN_LEV_BOSS ) != 0 )
		return FALSE;

	/* �ܥ���õ�� */

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next->next; mns_p != NULL;
			mns_p = mns_p->next ){
		mnstr_t	*pp;

		pp = mns_p->prev;
		if( pp == mns_head )
			break;

		if( pp->kind != CHR_KIND_MNSTR )
			continue;
		if( pp->mnstr_tab == NULL )
			continue;
		if( !(pp->mnstr_tab->flg_boss) )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( !clip_pos( pp->x, pp->y ) )
			continue;
		if( !chk_flg( dun->map.chr.flg[pp->y][pp->x],
				FLG_MAP_CHR_FIND ) ){
			continue;
		}

		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ��������Ʈ�椫Ĵ�٤�
* return : �ܥ����椫?
***************************************************************/

bool_t	scene_srch_battle( void )
{
	party_t	*pty;
	long	i;

	/* ��Ʈ��Υ��С������뤫õ�� */

	pty = get_party();
	for( i = 0; i < MBR_MAX_N; i++ ){
		mbr_t	*pp;

		pp = pty->mbr[i];

		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( pp->trgt.kind != TRGT_KIND_MNSTR )
			if( pp->trgt.kind != TRGT_KIND_MNSTR_NULL )
				continue;
		if( pp->act.kind != ACT_KIND_MNSTR_FIGHT )
			if( pp->act.kind != ACT_KIND_MNSTR_THROW )
				continue;

		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ��������ڤ��ؤ���
* scene_n_t n : ������
* return : �ڤ괹����줿������
***************************************************************/

scene_n_t	change_scene( scene_n_t n )
{
	return change_scene_sub( n, FALSE );
}

/***************************************************************
* ��������ڤ��ؤ��� (GUI)
* scene_n_t n : ������
* return : �ڤ괹����줿������
***************************************************************/

scene_n_t	change_scene_gui( scene_n_t n )
{
	return change_scene_sub( n, TRUE );
}

/***************************************************************
* ��������ڤ��ؤ���
* scene_n_t n : ������
* bool_t flg_gui : GUI ����ƤФ줿��?
* return : �ڤ괹����줿������
***************************************************************/

scene_n_t	change_scene_sub( scene_n_t n, bool_t flg_gui )
{
	if( n <= SCENE_N_NULL )
		return SCENE_N_NULL;
	if( n >= SCENE_N_MAX_N )
		return SCENE_N_NULL;

	scene_n = n;

	call_game_music_play_scene( flg_gui );

	return scene_n;
}

/***************************************************************
* ��������֤�
* return : �������ֹ�
***************************************************************/

scene_n_t	get_scene( void )
{
	return scene_n;
}

/***************************************************************
* �饹�ܥ��Υ�������ڤ��ؤ���
* last_scene_n_t n : �饹�ܥ��Υ�����
* return : �ڤ괹����줿�饹�ܥ��Υ�����
***************************************************************/

last_scene_n_t	change_last_scene( last_scene_n_t n )
{
	return change_last_scene_sub( n, FALSE );
}

/***************************************************************
* �饹�ܥ��Υ�������ڤ��ؤ��� (GUI)
* last_scene_n_t n : �饹�ܥ��Υ�����
* return : �ڤ괹����줿�饹�ܥ��Υ�����
***************************************************************/

last_scene_n_t	change_last_scene_gui( last_scene_n_t n )
{
	return change_last_scene_sub( n, TRUE );
}

/***************************************************************
* �饹�ܥ��Υ�������ڤ��ؤ���
* last_scene_n_t n : �饹�ܥ��Υ�����
* bool_t flg_gui : GUI ����ƤФ줿��?
* return : �ڤ괹����줿�饹�ܥ��Υ�����
***************************************************************/

last_scene_n_t	change_last_scene_sub( last_scene_n_t n, bool_t flg_gui )
{
	if( n < LAST_SCENE_N_NULL )
		return LAST_SCENE_N_NULL;
	if( n >= LAST_SCENE_N_MAX_N )
		return LAST_SCENE_N_NULL;

	scene_n = SCENE_N_LAST_BOSS;
	last_scene_n = n;

	call_demo_last_boss_reset();
	call_game_music_play_scene( flg_gui );

	return last_scene_n;
}

/***************************************************************
* �饹�ܥ��Υ�������֤�
***************************************************************/

last_scene_n_t	get_last_scene( void )
{
	return last_scene_n;
}

/***************************************************************
* ���ߤΥ����󤬻���Υ��롼�פ��ɤ���Ĵ�٤�
***************************************************************/

bool_t	chk_scene_group( scene_group_n_t group_n )
{
	switch( scene_n ){
	case SCENE_N_NULL:
		if( group_n == SCENE_GROUP_N_NULL )
			return TRUE;
		if( group_n == SCENE_GROUP_N_INIT )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_INIT:
		if( group_n == SCENE_GROUP_N_INIT )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_TITLE:
		if( group_n == SCENE_GROUP_N_TITLE )
			return TRUE;
		if( group_n == SCENE_GROUP_N_DEMO )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_OPENING:
		if( group_n == SCENE_GROUP_N_DEMO )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_SKIP )
			return TRUE;
		break;
	case SCENE_N_TOWN:
		if( group_n == SCENE_GROUP_N_PLAYING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_SHOP:
		if( group_n == SCENE_GROUP_N_PLAYING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_DUN:
		if( group_n == SCENE_GROUP_N_PLAYING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_BATTLE:
		if( group_n == SCENE_GROUP_N_PLAYING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_BATTLE )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_BATTLE_BOSS:
		if( group_n == SCENE_GROUP_N_PLAYING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_BATTLE )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_LAST_BOSS:
		if( group_n == SCENE_GROUP_N_PLAYING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_BATTLE )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_GAME_OVER:
		if( group_n == SCENE_GROUP_N_GAME_OVER )
			return TRUE;
		if( group_n == SCENE_GROUP_N_GAME_END )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_GAME_OVER_WAIT:
		if( group_n == SCENE_GROUP_N_GAME_OVER )
			return TRUE;
		if( group_n == SCENE_GROUP_N_GAME_END )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_GAME_OVER_END:
		if( group_n == SCENE_GROUP_N_GAME_OVER )
			return TRUE;
		if( group_n == SCENE_GROUP_N_GAME_END )
			return TRUE;
		if( group_n == SCENE_GROUP_N_DEMO )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_SKIP )
			return TRUE;
		break;
	case SCENE_N_ENDING:
		if( group_n == SCENE_GROUP_N_ENDING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_DEMO )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_ENDING_EPILOGUE:
		if( group_n == SCENE_GROUP_N_ENDING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_DEMO )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_ENDING_SPACE:
		if( group_n == SCENE_GROUP_N_ENDING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_SPACE )
			return TRUE;
		if( group_n == SCENE_GROUP_N_DEMO )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_ENDING_STAFF_ROLL:
		if( group_n == SCENE_GROUP_N_ENDING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_SPACE )
			return TRUE;
		if( group_n == SCENE_GROUP_N_DEMO )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_NOT_SKIP )
			return TRUE;
		break;
	case SCENE_N_ENDING_END:
		if( group_n == SCENE_GROUP_N_ENDING )
			return TRUE;
		if( group_n == SCENE_GROUP_N_SPACE )
			return TRUE;
		if( group_n == SCENE_GROUP_N_GAME_END )
			return TRUE;
		if( group_n == SCENE_GROUP_N_DEMO )
			return TRUE;
		if( group_n == SCENE_GROUP_N_CAN_SKIP )
			return TRUE;
		break;
	case SCENE_N_SEL_MBR_GRAPH:
		if( group_n == SCENE_GROUP_N_SEL_GRAPH )
			return TRUE;
		break;
	case SCENE_N_MAX_N:
		break;
	}

	return FALSE;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_scene_c( void )
{
	check_memory( check_memory_scene_c_scene_n,
			"scene.c: scene_n" );
	check_memory( check_memory_scene_c_last_scene_n,
			"scene.c: last_scene_n" );
}
