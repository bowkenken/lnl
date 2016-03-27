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
* $Id: key-item.c,v 1.11 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �����������ƥ�
***************************************************************/

#define	KEY_ITEM_C
#include	"inc.h"

/***************************************************************
* �ѿ����
***************************************************************/

/***************************************************************
* ���μ�
***************************************************************/

/* �ѡ��ƥ���������줿���μ� */
static bool_t	g_ls_flg_party_have_star_drop[STAR_DROP_KIND_MAX_N];
check_memory_def( check_memory_key_item_c_g_ls_flg_party_have_star_drop )

/* ���μ���̾�� */
static n_msg_t	g_ls_star_drop_name[STAR_DROP_KIND_MAX_N] = {
	N_MSG_STAR_DROP_ELEC,
	N_MSG_STAR_DROP_PHYS,
	N_MSG_STAR_DROP_HEAT,
	N_MSG_STAR_DROP_COLD,
	N_MSG_STAR_DROP_MIND,
	N_MSG_STAR_DROP_ACID,
	N_MSG_STAR_DROP_POIS,
};
check_memory_def( check_memory_key_item_c_g_ls_star_drop_name )

/***************************************************************
* ��ư����
***************************************************************/

/* ư���Ф�����ư���� */
static bool_t	g_ls_flg_drive_boot_unit[STAR_DROP_KIND_MAX_N];
check_memory_def( check_memory_key_item_c_g_ls_flg_drive_boot_unit )

/***************************************************************
* �����
***************************************************************/

void	init_key_item( void )
{
	long	i;

	for( i = 0; i < STAR_DROP_KIND_MAX_N; i++ ){
		g_ls_flg_party_have_star_drop[i] = FALSE;
		g_ls_flg_drive_boot_unit[i] = FALSE;
	}

	if( g_flg_debug )
		init_key_item_debug();
}

/***************************************************************
* �ǥХå����ν����
***************************************************************/

void	init_key_item_debug( void )
{
	long	i;

	for( i = 0; i < BOOT_UNIT_MAX_N; i++ )
		g_ls_flg_party_have_star_drop[i] = TRUE;
}

/***************************************************************
* ���μ�����äƤ��뤫Ĵ�٤�
* star_drop_kind_t kind : ���μ��μ���
* return : ���μ�����äƤ��뤫?
***************************************************************/

bool_t	chk_key_item( star_drop_kind_t kind )
{
	if( kind < 0 )
		return FALSE;
	if( kind >= STAR_DROP_KIND_MAX_N )
		return FALSE;

	return g_ls_flg_party_have_star_drop[kind];
}

/***************************************************************
* ���μ�����äƤ��뤫����
* star_drop_kind_t kind : ���μ��μ���
* bool_t flg_have : ���μ�����äƤ��뤫?
***************************************************************/

void	set_key_item( star_drop_kind_t kind, bool_t flg_have )
{
	if( kind < 0 )
		return;
	if( kind >= STAR_DROP_KIND_MAX_N )
		return;

	g_ls_flg_party_have_star_drop[kind] = flg_have;
}

/***************************************************************
* �ѡ��ƥ�������������뤫Ĵ�٤�
* return : ����������뤫?
***************************************************************/

bool_t	chk_enter_last_stage( void )
{
	long	i;

	for( i = 0; i < BOOT_UNIT_MAX_N; i++ )
		if( !g_ls_flg_party_have_star_drop[i] )
			return FALSE;

	return TRUE;
}

/***************************************************************
* ��ư���֤Υ��٥��
***************************************************************/

void	event_boot_unit( long x, long y )
{
	dun_t	*dun;
	char	mnr;
	long	n;
	const char	*name;
	long	i;

	if( get_last_scene() != LAST_SCENE_N_ENTER )
		return;

	if( !clip_pos( x, y ) )
		return;
	dun = get_dun();
	mnr = dun->map.obj.mnr[y][x];

	n = mnr - '0';
	if( n < 0 )
		return;
	if( n >= BOOT_UNIT_MAX_N )
		return;
	if( g_ls_flg_drive_boot_unit[n] )
		return;
	if( !g_ls_flg_party_have_star_drop[n] )
		return;

	/* ��ư���֤��ư */

	name = MSG( g_ls_star_drop_name[n] );
	print_msg( FLG_NULL, MSG_DRIVE_BOOT_UNIT, name );

	g_ls_flg_drive_boot_unit[n] = TRUE;

	for( i = 0; i < BOOT_UNIT_MAX_N; i++ )
		if( !g_ls_flg_drive_boot_unit[i] )
			break;
	if( i >= BOOT_UNIT_MAX_N )
		open_last_boss_gate();
	else
		call_game_sound_play( SOUND_KIND_EVENT_DRIVE, 1 );
}

/***************************************************************
* ���μ���̾�����֤�
* star_drop_kind_t kind : ���μ��μ���
* return : ���μ���̾��
***************************************************************/

const char	*get_key_item_name( star_drop_kind_t kind )
{
	if( kind < 0 )
		return "";
	if( kind >= STAR_DROP_KIND_MAX_N )
		return "";

	return MSG( g_ls_star_drop_name[kind] );
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_key_item_c( void )
{
	check_memory( check_memory_key_item_c_g_ls_flg_party_have_star_drop,
			"key-item.c: g_ls_flg_party_have_star_drop" );
	check_memory( check_memory_key_item_c_g_ls_star_drop_name,
			"key-item.c: g_ls_star_drop_name" );
	check_memory( check_memory_key_item_c_g_ls_flg_drive_boot_unit,
			"key-item.c: g_ls_flg_drive_boot_unit" );
}
