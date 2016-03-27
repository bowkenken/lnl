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
* $Id: pet.c,v 1.76 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �ڥåȡ��Ȥ��⡦������
***************************************************************/

#define	PET_C
#include	"inc.h"

/***************************************************************/

/* �ѡ��ƥ��ΤĤ�Ƥ���ڥåȤΥꥹ�� */
static pet_t	*party_pet[PET_MAX_N];
check_memory_def( check_memory_pet_c_party_pet )

/* ���ƤΥڥåȤΥꥹ�� */
static pet_t	*ls_pet[LS_PET_MAX_N + 1];
check_memory_def( check_memory_pet_c_ls_pet )

/* �ڥåȤΥ��꡼���ס��� */
static pet_t	ls_pet_buf[LS_PET_MAX_N + 1];
check_memory_def( check_memory_pet_c_ls_pet_buf )

/***************************************************************
* �ڥåȤν����
***************************************************************/

void	init_pet( void )
{
	long	i;

	for( i = 0; i < LS_PET_MAX_N + 1; i++ )
		ls_pet[i] = &(ls_pet_buf[i]);

	for( i = 0; i < LS_PET_MAX_N + 1; i++ ){
		new_pet( ls_pet[i] );
		ls_pet[i]->stat = FLG_STAT_NOT_EXIST;
	}

	for( i = 0; i < PET_MAX_N; i++ )
		party_pet[i] = NULL;

	if( g_flg_debug )
		init_pet_debug();
	else
		init_pet_dflt();
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_pet( void )
{
}

/***************************************************************
* �̾���ΥڥåȤν����
***************************************************************/

void	init_pet_dflt( void )
{
	party_t	*pty = get_party();
	pet_t	*p;
	long	i;

	i = 0;
	p = make_pet( 10, MNSTR_KIND_PYON_PYON, pty->mbr[i] );
	if( p == NULL )
		return;

	str_nz_cpy( p->name, "Pyon Pyon", PET_NAME_MAX_BYTE );
	join_pet( p );
}

/***************************************************************
* �ǥХå����ΥڥåȤν����
***************************************************************/

void	init_pet_debug( void )
{
	party_t	*pty = get_party();
	pet_t	*p;
	long	i;

	i = 0;
	p = make_pet( 10, MNSTR_KIND_PYON_PYON, pty->mbr[i] );
	if( p == NULL )
		return;

	str_nz_cpy( p->name, "Pyon Pyon", PET_NAME_MAX_BYTE );
	join_pet( p );
}

/***************************************************************
* �ڥåȤ��Ϥ�
* long dun_lev : ���󥸥�󡦥�٥�
* pet_kind_t pet_kind : �ڥåȤμ���
* chr_t *owner : �ڥåȤλ���
* return : �ڥå�
***************************************************************/

pet_t	*make_pet( long dun_lev, pet_kind_t pet_kind, chr_t *owner )
{
	long	i;
	pet_t	*p;

	p = NULL;
	for( i = 0; i < LS_PET_MAX_N; i++ ){
		if( ls_pet[i] == NULL )
			continue;

		if( chk_flg( ls_pet[i]->stat, FLG_STAT_NOT_EXIST ) ){
			p = ls_pet[i];
			break;
		}
	}
	if( p == NULL )
		return NULL;

	if( make_pet_alloc( p, dun_lev, pet_kind ) == NULL ){
		p->stat = FLG_STAT_NOT_EXIST;
		return NULL;
	}

	p->owner = owner;

	return p;
}

/***************************************************************
* ������Ƥ����꡼�˥ڥåȤ��Ϥ�
* pet_t *p : �ڥå�
* long dun_lev : ���󥸥�󡦥�٥�
* pet_kind_t pet_kind : �ڥåȤμ���
* return : �ڥå�
***************************************************************/

pet_t	*make_pet_alloc( pet_t *p, long dun_lev, pet_kind_t pet_kind )
{
	mnstr_t	*m;

	if( p == NULL )
		return NULL;

	new_pet( p );

	m = make_mnstr_alloc( p, MAP_DEL_X, MAP_DEL_Y, FALSE,
			dun_lev, pet_kind );
	if( m == NULL )
		return NULL;

	p->flg_pet = TRUE;
	p->flg_chr |= FLG_CHR_CAN_DEL;
	p->flg_map |= FLG_MAP_CHR_NPC;
	p->attitude = ATTITUDE_MATE;
	p->owner = NULL;

	set_chr_id( p, get_ls_pet(), LS_PET_MAX_N );

	return p;
}

/***************************************************************
* �ڥåȤκ������Υǥե�����ͤ�����
* pet_t *p : �ڥå�
***************************************************************/

void	new_pet( pet_t *pet )
{
	if( pet == NULL )
		return;

	new_mnstr( pet );
}

/***************************************************************
* �ڥåȤ����ͤ�ꥻ�å�
* pet_t *p : �ڥå�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	reset_pet_resi( pet_t *pet )
{
	long	k;

	if( pet == NULL )
		return FALSE;
	if( !is_pet( pet ) )
		return FALSE;

	if( pet->mnstr_tab == NULL )
		return FALSE;

	for( k = 0; k < RESI_KIND_MAX_N; k++ )
		pet->resi[k].max = pet->mnstr_tab->resi[k];

	return TRUE;
}

/***************************************************************
* ���ƤΥڥåȤ�ޥåפ���ä�
***************************************************************/

void	clr_map_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ )
		clr_map_chr( party_pet[i] );
}

/***************************************************************
* ���ƤΥڥåȤ�ޥåפ˽Ф�
***************************************************************/

void	set_map_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ )
		set_map_chr( party_pet[i] );
}

/***************************************************************
* ���ƤΥڥåȤ�ޥåפ˽и�������
***************************************************************/

void	appear_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == NULL )
			continue;

		appear_pet( party_pet[i] );
	}
}

/***************************************************************
* �ڥåȤ�ޥåפ˽и�������
* pet_t *p : �ڥå�
***************************************************************/

void	appear_pet( pet_t *p )
{
	long	x, y;

	if( p == NULL )
		return;
	if( chk_flg_or( p->stat,
			FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
		return;
	}

	chk_pet_owner( p );

	if( p->owner == NULL ){
		x = MAP_MAX_X / 2;
		y = MAP_MAX_Y / 2;
	} else {
		x = p->owner->x;
		y = p->owner->y;
	}

	put_chr( p, x, y );
	draw_pet( p );
}

/***************************************************************
* ���ƤΥڥåȤΰ�ư�ե�������¹�
***************************************************************/

void	move_phase_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;

		chk_pet_owner( pp );
		set_act_mnstr( pp );
		move_phase_chr( pp );
	}
}

/***************************************************************
* ���ƤΥڥåȤι�ư�ե�������¹�
***************************************************************/

void	act_phase_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;

		act_phase_chr( pp );
		set_modifier( pp );
	}
}

/***************************************************************
* ���ƤΥڥåȤ����ԥե�������¹�
***************************************************************/

void	dismissal_phase_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;

		dismissal_phase_chr( pp );
	}
}

/***************************************************************
* �ڥåȤ�ɸ��Ū�ʹ�ư������
* pet_t *p : �ڥå�
***************************************************************/

void	set_act_pet_std( pet_t *p )
{
	if( p == NULL )
		return;

	chk_pet_owner( p );
	pet_mark_std( p );

	if( (p->trgt.kind == TRGT_KIND_MNSTR)
			|| (p->trgt.kind == TRGT_KIND_MNSTR_NULL) ){
		mnstr_move_or_atack_std( p );
	}
}

/***************************************************************
* �ڥåȤΥ������åȤ�ɸ��Ū������
* pet_t *p : �ڥå�
***************************************************************/

void	pet_mark_std( pet_t *p )
{
	mnstr_t	*mnstr;
	item_t	*item;

	if( p == NULL )
		return;

	clr_chr_trgt_act( p, TRUE );

	if( p->owner == NULL )
		return;

	switch( p->owner->trgt.kind ){
	case TRGT_KIND_NULL:
		break;
	case TRGT_KIND_MBR:
		break;
	case TRGT_KIND_MNSTR:
	case TRGT_KIND_MNSTR_NULL:
		mnstr = (mnstr_t *)(p->owner->trgt.p);
		if( mnstr == NULL )
			break;
		if( mnstr->attitude != ATTITUDE_ENEMY )
			break;

		mark_mnstr( p, mnstr, DIST_NEAR );
		break;
	case TRGT_KIND_ITEM:
		item = (item_t *)(p->owner->trgt.p);
		if( item == NULL )
			break;
		if( p->owner->trgt.dist == DIST_NEAR )
			break;

		set_chr_act( p, ACT_KIND_ITEM_PICK_UP,
				NULL, NULL, 0, 0 );
		mark_item( p, item, DIST_NEAR );
		break;
	case TRGT_KIND_DOOR:
	case TRGT_KIND_TRAP:
	case TRGT_KIND_QUEUE:
	case TRGT_KIND_SQUARE:
	case TRGT_KIND_POS:
	case TRGT_KIND_AUTO:
		break;
	case TRGT_KIND_MAX_N:
		break;
	}
}

/***************************************************************
* ���ƤΥڥåȤˤĤ���櫤˳ݤ��ä��������å�
***************************************************************/

void	chk_trap_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;

		chk_trap( pp, pp );
	}
}

/***************************************************************
* �ꥹ�Ȥμ��Υڥå��ֹ���֤�
* long n : �ڥåȤΥꥹ���ֹ�
* long add : �ꥹ���ֹ�οʹ�����
* return : �ڥåȤΥꥹ���ֹ�
***************************************************************/

long	next_ls_pet_n( long n, long add )
{
	long	next_n;
	long	i;

	if( add == 0 )
		return n;

	next_n = n;
	for( i = 0; i < LS_PET_MAX_N; i++ ){
		next_n = (next_n + add + LS_PET_MAX_N) % LS_PET_MAX_N;

		if( ls_pet[next_n] == NULL )
			continue;
		if( chk_flg_or( ls_pet[next_n]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		return next_n;
	}

	return n;
}

/***************************************************************
* �ѡ��ƥ��ΤĤ�Ƥ���ڥåȤΥꥹ�Ȥ��֤�
* return : �ڥåȤΥꥹ��
***************************************************************/

pet_t	**get_party_pet( void )
{
	return party_pet;
}

/***************************************************************
* ���ƤΥڥåȤΥꥹ�Ȥ��֤�
* return : ���ƤΥڥåȤΥꥹ��
***************************************************************/

pet_t	**get_ls_pet( void )
{
	return ls_pet;
}

/***************************************************************
* ����κ�ɸ�ΥڥåȤ򸡺�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : �ڥå�
***************************************************************/

pet_t	*get_pet( long x, long y )
{
	dun_t	*dun = get_dun();
	pet_t	*p;
	long	i;

	if( !clip_pos( x, y ) )
		return NULL;

	if( dun->map.chr.mjr[y][x] == FACE_MJR_NULL )
		return NULL;

	p = dun->map.chr_p[y][x];
	if( (p != NULL) && is_pet( p ) )
		return p;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( x < get_chr_left( pp->x, pp->dx ) )
			continue;
		if( x > get_chr_right( pp->x, pp->dx ) )
			continue;
		if( y < get_chr_top( pp->y, pp->dy ) )
			continue;
		if( y > get_chr_bottom( pp->y, pp->dy ) )
			continue;

		return pp;
	}

	return NULL;
}

/***************************************************************
* �ڥåȤΥڥå��ֹ���֤�
* pet_t *pet : �ڥå�
* return : �ڥå��ֹ�
***************************************************************/

long	get_pet_n( pet_t *pet )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet == party_pet[i] )
			return i;
	}

	return -1;
}

/***************************************************************
* �ڥåȤΥڥåȡ��ꥹ���ֹ���֤�
* pet_t *pet : �ڥå�
* return : �ڥåȡ��ꥹ���ֹ�
***************************************************************/

long	get_pet_ls_n( pet_t *pet )
{
	long	i;

	for( i = 0; i < LS_PET_MAX_N; i++ ){
		if( pet == ls_pet[i] )
			return i;
	}

	return -1;
}

/***************************************************************
* ����ΰ���˴ط����� NPC (�ڥå�)�򸡺�
* request_t *req : ����
* return : NPC (�ڥå�)
***************************************************************/

pet_t	*get_npc_request( request_t *req )
{
	long	i;

	for( i = 0; i < LS_PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = ls_pet[i];
		if( pp == NULL )
			continue;
		if( chk_flg_or( pp->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		if( pp->work.request == req )
			return pp;
	}

	return NULL;
}

/***************************************************************
* �ڥåȤλ����������
* pet_t *p : �ڥå�
***************************************************************/

void	clr_pet_owner( pet_t *p )
{
	party_t	*pty = get_party();
	long	i;

	if( p == NULL )
		return;

	for( i = 0; i < MBR_MAX_N; i++ ){
		chr_t	*chr;

		chr = pty->mbr[i];
		if( chk_flg_or( chr->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( chr->mbr_n == MBR_N_NOT_JOIN )
			continue;

		p->owner = chr;
		break;
	}
}

/***************************************************************
* �ڥåȤλ�����������
* pet_t *p : �ڥå�
***************************************************************/

void	chk_pet_owner( pet_t *p )
{
	if( p == NULL )
		return;

	if( p->owner == NULL ){
		clr_pet_owner( p );
	} else {
		if( chk_flg_or( p->owner->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			clr_pet_owner( p );
		}
		if( p->owner->mbr_n == MBR_N_NOT_JOIN ){
			clr_pet_owner( p );
		}
	}
}

/***************************************************************
* �ڥåȤ�ѡ��ƥ��˲ä����뤫Ĵ�٤�
* pet_t *p : �ڥå�
* return : �ä����뤫?
***************************************************************/

bool_t	chk_can_join_pet( pet_t *p )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == p )
			return FALSE;
	}

	return TRUE;
}

/***************************************************************
* �ڥåȤ�ѡ��ƥ����鳰�����뤫Ĵ�٤�
* pet_t *p : �ڥå�
* return : �������뤫?
***************************************************************/

bool_t	chk_can_not_join_pet( pet_t *p )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == p )
			return TRUE;
	}

	return FALSE;
}

/***************************************************************
* �ڥåȤ�ѡ��ƥ��˲ä���
* pet_t *p : �ڥå�
* return : �ä���줿��?
***************************************************************/

bool_t	join_pet( pet_t *p )
{
	long	i;

	if( p == NULL )
		return FALSE;
	if( !chk_can_join_pet( p ) )
		return FALSE;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] != NULL )
			continue;

		party_pet[i] = p;
		appear_pet( p );

		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* �ڥåȤ�ѡ��ƥ����鳰��
* pet_t *p : �ڥå�
* return : ������줿��?
***************************************************************/

bool_t	not_join_pet( pet_t *p )
{
	long	i;

	if( p == NULL )
		return FALSE;
	if( !chk_can_not_join_pet( p ) )
		return FALSE;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] != p )
			continue;

		clr_map_chr( p );
		draw_pet( p );

		p->pre_x = p->x;
		p->pre_y = p->y;
		p->x = MAP_DEL_X;
		p->y = MAP_DEL_Y;
		party_pet[i] = NULL;

		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* �������ԽäΥ��꡼�����
***************************************************************/

void	garbage_collection_all_pet( void )
{
	long	i;
	pet_t	*p;

	for( i = 0; i < PET_MAX_N; i++ ){
		p = party_pet[i];

		if( p == NULL )
			continue;
		if( !chk_flg( p->flg_chr, FLG_CHR_CAN_DISMISSAL ) )
			continue;
		if( !chk_flg( p->stat, FLG_STAT_DEAD ) )
			continue;

		dismissal( p );
	}
}

/***************************************************************
* �ڥåȤ��������ν���
* pet_t *p : �ڥå�
* bool_t flg_msg : ��å�������ɸ�����뤫?
***************************************************************/

void	die_pet( pet_t *p, bool_t flg_msg )
{
	if( p == NULL )
		return;

	if( flg_msg )
		call_game_sound_play( SOUND_KIND_FIGHT_DIE_MEMBER, 1 );
}

/***************************************************************
* �ڥåȤ���Ū�����Ԥ���
* pet_t *p : �ڥå�
***************************************************************/

void	remove_pet( pet_t *p )
{
	if( p == NULL )
		return;
	if( !is_pet( p ) )
		return;

	p->flg_chr |= FLG_CHR_CAN_DISMISSAL;
	dismissal( p );
}

/***************************************************************
* �ڥåȤ����Ԥ���
* pet_t *p : �ڥå�
* return : ���Խ��褿��?
***************************************************************/

bool_t	dismissal( pet_t *p )
{
	long	i;

	if( p == NULL )
		return FALSE;
	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( !chk_flg( p->flg_chr, FLG_CHR_CAN_DISMISSAL ) )
		return FALSE;

	not_join_pet( p );

	for( i = 0; i < PET_MAX_N; i++ )
		if( party_pet[i] == p )
			party_pet[i] = NULL;

	die_chr( p, FALSE, FALSE, FALSE );
	p->stat |= (FLG_STAT_NOT_EXIST | FLG_STAT_DEAD);

	return TRUE;
}

/***************************************************************
* �ѡ��ƥ���ΥڥåȤο��������
* return : �ڥåȤο�
***************************************************************/

long	calc_pet_n( void )
{
	long	n;
	long	i;

	n = 0;
	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == NULL )
			continue;
		if( chk_flg( party_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		n++;
	}

	return n;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_pet_c( void )
{
	check_memory( check_memory_pet_c_party_pet,
			"pet.c: party_pet" );
	check_memory( check_memory_pet_c_ls_pet,
			"pet.c: ls_pet" );
	check_memory( check_memory_pet_c_ls_pet_buf,
			"pet.c: ls_pet_buf" );
}
