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
* $Id: mnstr-act.c,v 1.36 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ��󥹥����Υ��������
***************************************************************/

#define	MNSTR_ACT_C
#include	"inc.h"

/***************************************************************/

/* ��󥹥���������ۤγ�� */
#define	PICK_GOLD_RATE	((rate_t)10)
/* ��󥹥���������ۤκ����� */
#define	PICK_GOLD_MAX_N	((gold_t)500)

/* ��󥹥��������������� */
#define	INCREASE_RATE_GIANT_RAT	20

/* ���ν�̱���ɥ�������Ψ���西����� */
#define	TOWNER_ENTER_DOOR_RATE	10
/* ���ν�̱���ɥ��������Υ */
#define	TOWNER_ENTER_DOOR_R	3
/* ���ν�̱���ɥ�������Τ������Ψ���西����� */
#define	TOWNER_CANCEL_DOOR_RATE	10

/* ���ν�̱���ɥ�����Ф�Ψ�Σ����ܡ��西����� */
#define	TOWNER_EXIT_DOOR_RATE	((rate_t)2)
/* ���ν�̱���ɥ�����Ф�Ψ�Σ����ܡ���� */
#define	TOWNER_EXIT_DOOR_RATE_DAY	((rate_t)100)
/* ���ν�̱���ɥ�����Ф�Ψ�Σ����ܡ���� */
#define	TOWNER_EXIT_DOOR_RATE_NIGHT	((rate_t)1)

/***************************************************************/

static long	static_set_act_mnstr_giant_rat__increase_turn;
check_memory_def( check_memory_mnstr_act_c_increase_turn )

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_mnstr_act( void )
{
	static_set_act_mnstr_giant_rat__increase_turn = -1;
}

/***************************************************************
* �ƥ�󥹥����ζ��̤Υ��������
***************************************************************/

/***************************************************************
* ���̤Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_std( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* �Ȥ���ξ��Υ�������� */

	if( p->attitude == ATTITUDE_MATE ){
		set_act_pet_std( p );
		return;
	}
	if( p->attitude != ATTITUDE_ENEMY )
		return;

	mnstr_mark_mbr_std( p );

	/* ���С���ȯ�����Ƥ�����Ϲ��⤹�� */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/***************************************************************
* ������Х��ȥ��󥭥�Х��ζ��̤Υ��������
* mnstr_t *p : ��󥹥���
* sex_t sex : ����դ�����饯��������
***************************************************************/

void	set_act_mnstr_cubus( mnstr_t *p, sex_t sex )
{
	if( p == NULL )
		return;

	/* �Ȥ���ξ��Υ�������� */

	if( p->attitude == ATTITUDE_MATE ){
		set_act_pet_std( p );
		return;
	}

	mnstr_mark_mbr_cubus( p, sex );

	/* ���С���ȯ�����Ƥ�����Ϲ��⤹�� */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/***************************************************************
* �ѿȤ����󥹥����ζ��̤Υ��������
* mnstr_t *p : ��󥹥���
* mnstr_kind_t kind : �ѿȤ����󥹥���
* rate_t rate : �ѿȤ���Ψ
***************************************************************/

void	set_act_mnstr_metamorphose(
	mnstr_t *p, mnstr_kind_t kind, rate_t rate
)
{
	mnstr_tab_t	*meta_tab, *tab;

	if( p == NULL )
		return;
	if( p->mnstr_tab == NULL )
		return;

	meta_tab = get_mnstr_tab( kind, 0 );

	tab = NULL;
	if( rate_randm( rate ) ){
		if( (p->face.mjr == p->mnstr_tab->face_mjr)
				&& (p->face.mnr == p->mnstr_tab->face_mnr) ){
			/* �ѿȤ��� */
			tab = meta_tab;
		} else {
			/* ������� */
			tab = p->mnstr_tab;
		}
	}

	if( tab != NULL ){
		/* �ѿȤ��뤫������� */

		p->move = tab->move;
		p->modifier_fx.face_mjr = tab->face_mjr;
		p->modifier_fx.face_mnr = tab->face_mnr;
	}

	if( p->face.mjr == p->mnstr_tab->face_mjr ){
		set_act_mnstr_std( p );
	} else {
		/* �ѿȸ�Υ�������� */

		meta_tab->func( p );
	}
}

/***************************************************************
* ���ν�̱�ζ��̤Υ��������
* mnstr_t *p : ���ν�̱�ʥ�󥹥�����
***************************************************************/

void	set_act_mnstr_towner( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* �߽�����ɬ�פ�ͭ��С�������Υ�������� */

	if( set_act_rescue_trgt( p ) )
		return;

	/* �Ȥ���ξ��Υ�������� */

	if( p->attitude == ATTITUDE_MATE ){
		set_act_pet_std( p );
		return;
	}

	/* ��������Ǥ���ʤ顢������Υ�������� */

	chk_discount_mark( p );
	if( p->trgt.kind == TRGT_KIND_QUEUE )
		return;

	if( p->act.kind == ACT_KIND_DOOR_OPEN ){
		/* �ɥ������륢������� */

		if( rate_randm( TOWNER_CANCEL_DOOR_RATE ) )
			clr_chr_trgt_act( p, FALSE );
	} else {
		set_act_mnstr_std( p );
		set_act_towner_enter_door( p );
	}

	/* �ɥ�����Ф륢������� */

	set_act_towner_exit_door( p );
}

/***************************************************************
* ���ν�̱���ɥ������뤫Ĵ�٤륢�������
* mnstr_t *p : ���ν�̱�ʥ�󥹥�����
***************************************************************/

void	set_act_towner_enter_door( mnstr_t *p )
{
	door_t	*dr;

	if( p == NULL )
		return;
	if( p->act.kind == ACT_KIND_DOOR_OPEN )
		return;
	if( !rate_randm( TOWNER_ENTER_DOOR_RATE ) )
		return;

	dr = get_door_towner( p->x, p->y, TOWNER_ENTER_DOOR_R );
	if( dr == NULL )
		return;
	if( chk_discount_door( dr ) )
		return;

	set_chr_act( p, ACT_KIND_DOOR_OPEN, NULL, NULL, 0, 0 );
	mark_door( p, dr, DIST_NEAR );
}

/***************************************************************
* ���ν�̱���ɥ�����Ф뤫Ĵ�٤륢�������
* mnstr_t *p : ���ν�̱�ʥ�󥹥�����
***************************************************************/

void	set_act_towner_exit_door( mnstr_t *p )
{
	door_t	*dr;

	if( p == NULL )
		return;
	if( p->work.enter_door == NULL )
		return;

	if( !rate_randm( TOWNER_EXIT_DOOR_RATE ) )
		return;
	if( chk_night() ){
		if( !rate_randm( TOWNER_EXIT_DOOR_RATE_NIGHT ) ){
			return;
		}
	} else {
		if( !rate_randm( TOWNER_EXIT_DOOR_RATE_DAY ) ){
			return;
		}
	}

	dr = p->work.enter_door;
	if( dr == NULL )
		return;

	if( get_shop_n( dr->mnr ) == SHOP_N_BAR ){
		long	i, max_n;

		if( clip_pos( p->x, p->y ) ){
			clr_map_chr( p );
			draw_chr( p );
		}

		/* ������ǿ��ʧ�� */

		max_n = roll_dice( 5, FALSE );
		for( i = 0; i < max_n; i++ ){
			drink_liquor( p, LIQUOR_KIND_ALE );
		}
	}

	put_chr( p, dr->x, dr->y );
	p->work.enter_door = NULL;
}

/***************************************************************
* ͧ��Ū�ʥ�󥹥����Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_friendly( mnstr_t *p )
{
	if( p == NULL )
		return;

	if( set_act_tame_mnstr( p ) )
		return;

	set_act_mnstr_std( p );
}

/***************************************************************
* ͧ��Ū�ʥ�󥹥����α��դ����������
* mnstr_t *p : ��󥹥���
* return : �������������ꤷ����?
***************************************************************/

bool_t	set_act_tame_mnstr( mnstr_t *p )
{
	if( p == NULL )
		return FALSE;
	if( p->work.request == NULL )
		return FALSE;
	if( p->work.request->kind != REQUEST_KIND_TAME_MNSTR )
		return FALSE;

	if( p->fx_data.stomach.rate < _100_PERCENT ){
		item_t	*food;

		/* ʢ�����äƤ����� */

		do {
			/* ���դ����� */

			food = get_item_food( p,
					ACT_KIND_ITEM_PICK_UP, FALSE );
			if( food == NULL )
				break;
			if( food->kind != ITEM_KIND_FOOD )
				break;
			if( food->tab.food == NULL )
				break;

			mark_item( p, food, DIST_NEAR );

			if( food->x != p->x )
				break;
			if( food->y != p->y )
				break;

			/* �¤򿩤٤� */

			take_meal_chr( p, food->tab.food->fill_rate );
			del_item( food );
		} while( 0 );
	} else {
		/* ʢ�����äѤ��ˤʤä���� */

		if( chk_flg_work_find_mbr( p ) )
			return FALSE;

		mnstr_mark_mbr_std( p );
		if( chk_flg_work_find_mbr( p ) ){
			/* ����ã�� */
			chk_finish_request_join( p->work.request, p );
		}
	}

	return TRUE;
}

/***************************************************************
* ���ν�̱�ε߽��Υ��������
* mnstr_t *p : ���ν�̱�ʥ�󥹥�����
* return : �������������ꤷ����?
***************************************************************/

bool_t	set_act_rescue_trgt( mnstr_t *p )
{
	bool_t	flg_find;

	/* �߽��оݤ������å� */

	if( p == NULL )
		return FALSE;
	if( p->work.request == NULL )
		return FALSE;
	if( p->work.request->kind != REQUEST_KIND_RESCUE )
		return FALSE;

	/* �߽��о� */

	flg_find = chk_flg_work_find_mbr( p );

	set_chr_act( p, ACT_KIND_MBR_TAIL, NULL, NULL, 0, 0 );
	if( is_pet( p ) )
		mark_mnstr( p, (mnstr_t *)(p->owner->trgt.p), DIST_NEAR );
	else
		mnstr_mark_mbr_std( p );

	if( !flg_find && chk_flg_work_find_mbr( p ) ){
		/* �߽���λ */
		chk_finish_request_join( p->work.request, p );
	}

	return TRUE;
}

/***************************************************************
* �ƥ�󥹥������ȼ��Υ��������
***************************************************************/

/* �� */
/* �ɥ饴�� */

/* ���� */

/***************************************************************
* �ե��˥å����Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_phoenix( mnstr_t *p )
{
	party_t	*pty = get_party();
	long	i;

	if( p == NULL )
		return;

	if( p->attitude != ATTITUDE_MATE ){
		/* �Ȥ���Ǥʤ�������̤Υ�������� */

		set_act_mnstr_std( p );
		return;
	}

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		/* ���С��������֤餻�� */

		if( chk_flg_or( pty->mbr[i]->stat, FLG_STAT_DEAD ) )
			fx_resurrection( pty->mbr[i], TRUE );
	}

	/* �Ĥ�����̤Υ�������� */

	set_act_mnstr_std( p );
}

/***************************************************************
* ��˥�����Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_unicorn( mnstr_t *p )
{
	party_t	*pty = get_party();
	long	i;

	if( p == NULL )
		return;

	if( p->attitude != ATTITUDE_MATE ){
		/* �Ȥ���Ǥʤ�������̤Υ�������� */

		set_act_mnstr_std( p );
		return;
	}

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		/* ���С��ξ��ְ۾��������� */

		fx_cure_all_stat( pty->mbr[i] );
	}

	/* �Ĥ�����̤Υ�������� */

	set_act_mnstr_std( p );
}

/* ���� */

/***************************************************************
* ��ץ饳����Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_leprechaun( mnstr_t *p )
{
	chr_t	*mbr;

	if( p == NULL )
		return;

	/* ���С������ܤ��Ƥ��뤫�����å� */

	mbr = mnstr_mark_mbr_adjoin( p );

	if( mbr != NULL ){
		/* ���С��ζ����� */

		fx_pick_gold( p, mbr, PICK_GOLD_RATE, PICK_GOLD_MAX_N );
		print_msg( FLG_NULL, MSG_MNSTR_DISAPPEAR, p->name );
		teleport_chr( p );
	}

	/* �Ĥ�����̤Υ�������� */

	set_act_mnstr_std( p );
}

/* ���� */

/* ��ʪ */

/***************************************************************
* �������ʥ����ե饤���ȥ�åפΥ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_venus_fly_trap( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* ���ܤ��Ƥ�����С�����ޤ��� */

	if( mnstr_mark_mbr_adjoin( p ) != NULL )
		catch_chr( p, (chr_t *)(p->trgt.p) );

	/* ���С���ȯ�����Ƥ�����Ϲ��⤹�� */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/***************************************************************
* ���饤��Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_slime( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* ���С������ܤ��褦�Ȥ��� */

	if( mnstr_mark_mbr_adjoin( p ) == NULL )
		mnstr_mark_mbr_std( p );

	/* �Ĥ�����̤Υ�������� */

	set_act_mnstr_std( p );
}

/***************************************************************
* ���ݥ��Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_spore( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* ���С������ܤ��Ƥ�����������⤹�� */

	if( mnstr_mark_mbr_adjoin( p ) != NULL )
		mnstr_move_or_atack_std( p );
}

/* ưʪ */

/***************************************************************
* ���㥤����ȡ���åȤΥ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_giant_rat( mnstr_t *p )
{
	long	increase_turn = -1;

	increase_turn = static_set_act_mnstr_giant_rat__increase_turn;

	if( p == NULL )
		return;

	/* �ޤ������̤Υ�������� */

	set_act_mnstr_std( p );

	/* �������� */

	if( increase_turn < get_turn() ){
		if( rate_randm( INCREASE_RATE_GIANT_RAT ) ){
			increase_mnstr( p );
			increase_turn = get_turn();
		}
	}

	static_set_act_mnstr_giant_rat__increase_turn = increase_turn;
}

/* ���� */

/***************************************************************
* ���㥤����ȡ����ѥ������Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_giant_spider( mnstr_t *p )
{
	mbr_t	*mbr;
	bool_t	flg_rel;

	if( p == NULL )
		return;

	mbr = mnstr_mark_mbr_adjoin( p );
	if( mbr == NULL ){
		/* ���ܤ��Ƥ��ʤ��ʤ���С����̤˶��դ� */

		mnstr_mark_mbr_std( p );
	} else {
		/* ���ܤ��Ƥ���ʤ���С�����ޤ��� */

		catch_chr( p, mbr );
	}

	/* ���С���������뤫�����å� */

	if( mbr == NULL )
		flg_rel = TRUE;
	else if( rate_randm( 30 ) )
		flg_rel = TRUE;
	else
		flg_rel = FALSE;

	/* ���С���ȯ�����Ƥ�������� */

	if( chk_flg_work_find_mbr( p ) ){
		/* ���С���������� */
		if( flg_rel )
			release_chr( p );

		/* ���̤˹��⤹�� */
		mnstr_move_or_atack_std( p );
	}
}

/* �ʹ� */

/* Ⱦ�� */

/***************************************************************
* �������դΥ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_werewolf( mnstr_t *p )
{
	/* ����դ��ѿȤ��륢������� */

	set_act_mnstr_metamorphose( p, MNSTR_KIND_WOLF, 10 );
}

/**/

/* ��� */
/* ������ʪ */

/***************************************************************
* ���㥤����ƥ��å�������ƥ��ԡ��ɤΥ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_gigantic_centipede( mnstr_t *p )
{
	chr_t	*l;

	if( p == NULL )
		return;

	/* ��Ƭ�Ǥʤ���У��������ɤ������� */

	l = p->work.link_chr;
	if( l != NULL ){
		if( (l->pre_x != l->x) || (l->pre_y != l->y) )
			mark_pos( p, l->pre_x, l->pre_y, DIST_NEAR );
		p->move.force_kind = MOVE_KIND_STD;
		return;
	}

	/* �Ȥ���ξ��Υ�������� */

	if( p->attitude == ATTITUDE_MATE ){
		set_act_pet_std( p );
		return;
	}
	if( p->attitude != ATTITUDE_ENEMY )
		return;

	mnstr_mark_mbr_std( p );

	/* ���С���ȯ�����Ƥ�����Ϲ��⤹�� */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/* ������ʪ */

/* ��ˡ��ʪ */

/***************************************************************
* ����������Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_gargoyle( mnstr_t *p )
{
	dun_t	*dun = get_dun();

	if( p == NULL )
		return;

	if( chk_flg_work_find_mbr( p ) ){
		/* ���С���ȯ�����Ƥ���������̤˥ޡ������� */

		mnstr_mark_mbr_std( p );
	} else {
		flg_map_t	flg_map;
		chr_t	*mark;

		/* ���Ū��������������̤��ͤˤ��� */
		flg_map = dun->map.obj.flg[p->y][p->x];
		dun->map.obj.flg[p->y][p->x] |= FLG_MAP_OBJ_LOOK;

		/* ���С������ܤ��Ƥ��뤫�����å� */
		mark = mnstr_mark_mbr_adjoin( p );

		/* �����λ����򸵤��᤹ */
		dun->map.obj.flg[p->y][p->x] = flg_map;

		/* ���С������ä���Ѥ�ɽ�� */
		if( mark != NULL ){
			dun->map.obj.mjr[p->y][p->x] = FACE_MJR_FLOOR;
			dun->map.obj.mnr[p->y][p->x] = FACE_MNR_FLOOR;
			dun->map.obj.flg[p->y][p->x]
					= (FLG_MAP_OBJ_PASS
					| FLG_MAP_OBJ_LOOK);
		}
	}

	/* ���С���ȯ�����Ƥ�����Ϲ��⤹�� */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/***************************************************************
* �ߥߥå��Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_mimic( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* ���ܤ��Ƥ�����С�����ޤ��� */

	if( mnstr_mark_mbr_adjoin( p ) != NULL )
		catch_chr( p, (chr_t *)(p->trgt.p) );

	/* ���С���ȯ�����Ƥ�����Ϲ��⤹�� */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/* ������ */

/* ����ǥå� */

/***************************************************************
* ������ѥ����Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_vampire( mnstr_t *p )
{
	/* ���㥤����ȡ��ХåȤ��ѿȤ��륢������� */

	set_act_mnstr_metamorphose( p, MNSTR_KIND_GIANT_BAT, 10 );
}

/* ���� */

/***************************************************************
* ���󥭥�Х��Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_incubus( mnstr_t *p )
{
	/* �����˼���դ� */

	set_act_mnstr_cubus( p, FEMALE );
}

/***************************************************************
* ������Х��Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_succubus( mnstr_t *p )
{
	/* �����˼���դ� */

	set_act_mnstr_cubus( p, MALE );
}

/* ��� */
/* ���� */

/***************************************************************
* ��������Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_exel( mnstr_t *p )
{
	if( p == NULL )
		return;

	if( get_last_scene() != LAST_SCENE_N_EXEL_BATTLE ){
		p->stat |= FLG_STAT_IRON_BODY;
		p->abl.hp.n = p->abl.hp.max;
	} else {
		p->stat &= ~FLG_STAT_IRON_BODY;
		set_act_mnstr_std( p );
	}
}

/***************************************************************
* �������顼�Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_exeler( mnstr_t *p )
{
	if( p == NULL )
		return;

	if( get_last_scene() != LAST_SCENE_N_EXELER_BATTLE ){
		p->stat |= FLG_STAT_IRON_BODY;
		p->abl.hp.n = p->abl.hp.max;
	} else {
		p->stat &= ~FLG_STAT_IRON_BODY;
		set_act_mnstr_std( p );
	}
}

/***************************************************************
* �������Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_xex( mnstr_t *p )
{
	if( p == NULL )
		return;

	p->stat |= FLG_STAT_IRON_BODY;
	p->abl.hp.n = p->abl.hp.max;
}

/***************************************************************
* �ȥ�����ƥ������Υ��������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr_xx( mnstr_t *p )
{
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_mnstr_act_c( void )
{
	check_memory( check_memory_mnstr_act_c_increase_turn,
			"mnstr-act.c: increase_turn" );
}
