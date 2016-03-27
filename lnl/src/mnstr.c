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
* $Id: mnstr.c,v 1.238 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ��󥹥���
***************************************************************/

#define	MNSTR_C
#include	"inc.h"

/***************************************************************/

/* ����������μ��դˤ�����ߡ������ο� */
#define	GARGOYLE_STATUE_N	3

/* ��󥹥����λ��äƤ����η׻��˻Ȥ� */
#define	MNSTR_GOLD_MUL_N	12
#define	MNSTR_GOLD_ADD_N	0

/* ��󥹥����ι����Ψ */
#define	MNSTR_DROP_BONE_RATE	((rate_t)20)

/* ���ν�̱��ʿ�ѥ��󥸥�󡦥�٥� */
#define	TOWNER_AVE_DUN_LEV	48

/* ��󥹥����η���ζ��� */

/* ʬ�� */
#define	GROUP_RATE_DENOMINATOR	10
/* ����� */
#define	GROUP_RATE_BASE	50

/* ��󥹥�������֤ޤ��ϼ�ʬ�˲�����ʸ�򾧤��� HP �κ����Ψ */
#define	MNSTR_SPELL_FRIEND_HP_RATE	70

/***************************************************************
* ��󥹥����Υǡ���
***************************************************************/

/* �ס��� */
static mnstr_t	mnstr_buf[MNSTR_MAX_N];
check_memory_def( check_memory_mnstr_c_mnstr_buf )
/* ������ƺ� */
static mnstr_t	mnstr_used;
check_memory_def( check_memory_mnstr_c_mnstr_used )
/* ̤������� */
static mnstr_t	mnstr_free;
check_memory_def( check_memory_mnstr_c_mnstr_free )

/* �饹�ܥ� */
static mnstr_t	*g_last_boss[LAST_BOSS_KIND_MAX_N];
check_memory_def( check_memory_mnstr_c_g_last_boss )

/***************************************************************
* ��󥹥����Υǡ������ơ��֥�
***************************************************************/

#define	FLG_DIVIDE_MNSTR_LEV_TAB_STAGE	1
#include	"mnstr-tab.h"

/***************************************************************
* ��󥹥����ν����
***************************************************************/

void	init_mnstr( void )
{
	bool_t	ls_flg_chk_mnstr_kind[MNSTR_KIND_MAX_N];
	char	*name;
	long	i, max_i;

	max_i = sizeof( mnstr_tab ) / sizeof( mnstr_tab[0] );
	for( i = 0; i < max_i; i++ ){
		if( mnstr_tab[i].mnstr_kind == MNSTR_KIND_NULL )
			break;

		mnstr_tab[i].name = MSG( mnstr_tab[i].name_n );
	}

#if	FLG_DIVIDE_MNSTR_LEV_TAB_STAGE
	{
		long	n;

		n = 0;
		init_mnstr_lev_tab( mnstr_lev_tab_stage_town, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_1, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_2, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_3, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_4, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_5, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_6, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_7, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_8, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_9, &n );
		init_mnstr_lev_tab( mnstr_lev_tab_stage_10, &n );
	}
#else
	{
		long	min_lev, max_lev;

		min_lev = 0;
		max_i = sizeof( mnstr_lev_tab )
				/ sizeof( mnstr_lev_tab[0] );
		for( i = 0; i < max_i; i++ ){
			mnstr_lev_tab_t	*tab;

			tab = &(mnstr_lev_tab[i]);

			if( tab->kind == MNSTR_KIND_NULL )
				break;

			min_lev += tab->add_lev;
			max_lev = min_lev + tab->range_lev - 1;

			tab->min_lev = min_lev;
			tab->max_lev = max_lev;
		}
	}
#endif

	// �����å��ѥơ��֥������

	for( i = 0; i < MNSTR_KIND_MAX_N; i++ )
		ls_flg_chk_mnstr_kind[i] = FALSE;

	// �ܥ�������å�

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( mnstr_boss_lev_tab[i].kind == MNSTR_KIND_NULL )
			break;

		ls_flg_chk_mnstr_kind[mnstr_boss_lev_tab[i].kind] = TRUE;
	}

	// �饹�ܥ�������å�

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( mnstr_last_boss_lev_tab[i].kind == MNSTR_KIND_NULL )
			break;

		ls_flg_chk_mnstr_kind[mnstr_last_boss_lev_tab[i].kind]
				= TRUE;
	}

	// ��ʣ������å�

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( mnstr_lev_tab[i].kind == MNSTR_KIND_NULL )
			break;

		if( ls_flg_chk_mnstr_kind[mnstr_lev_tab[i].kind] ){
			name = get_mnstr_name( mnstr_lev_tab[i].kind );
			print_msg( FLG_MSG_DEBUG,
					MSG_ERR_MNSTR_LEV_TAB_DUP,
					name );
		}
		ls_flg_chk_mnstr_kind[mnstr_lev_tab[i].kind] = TRUE;
	}

	// ̤���������å�

	for( i = MNSTR_KIND_NULL + 1; i < MNSTR_KIND_MAX_N; i++ ){
		if( !ls_flg_chk_mnstr_kind[i] ){
			name = get_mnstr_name( (mnstr_kind_t)i );
			print_msg( FLG_MSG_DEBUG,
					MSG_ERR_MNSTR_LEV_TAB_NOT_DEF,
					name );
		}
	}

	// �ơ��֥�������ͤ��������ͤ�ջ�

	{
		long	pre_lev;

		pre_lev = 0;
		for( i = 0; i < LOOP_MAX_1000; i++ ){
			if( mnstr_lev_tab[i].kind == MNSTR_KIND_NULL )
				break;

			mnstr_lev_tab[i].add_lev = mnstr_lev_tab[i].min_lev
					- pre_lev;
			mnstr_lev_tab[i].range_lev = mnstr_lev_tab[i].max_lev
					- mnstr_lev_tab[i].min_lev + 1;

			pre_lev = mnstr_lev_tab[i].min_lev;
		}
	}

	for( i = 0; i < LAST_BOSS_KIND_MAX_N; i++ )
		g_last_boss[i] = NULL;

	reset_mnstr();
}

/***************************************************************
* ��󥹥����Υ�٥롦�ơ��֥������
***************************************************************/

void	init_mnstr_lev_tab( mnstr_lev_tab_t stage[], long *n )
{
	long	i;

	if( stage == NULL )
		return;
	if( n == NULL )
		return;

	for( i = 0; i < MNSTR_KIND_MAX_N; i++ ){
		if( stage[i].kind == MNSTR_KIND_NULL )
			break;
		if( *n >= MNSTR_KIND_MAX_N )
			break;

		mnstr_lev_tab[*n] = stage[i];
		(*n)++;
	}
	mnstr_lev_tab[*n].kind = MNSTR_KIND_NULL;
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_mnstr( void )
{
}

/***************************************************************
* �ե���ư�����Ȥ����Υ�󥹥����Υꥻ�å�
***************************************************************/

void	reset_mnstr( void )
{
	long	i;

	mnstr_used.next = &mnstr_used;
	mnstr_used.prev = &mnstr_used;

	mnstr_free.next = &mnstr_buf[0];
	mnstr_buf[0].prev = &mnstr_free;
	mnstr_buf[0].next = &mnstr_buf[1];
	for( i = 1; i < MNSTR_MAX_N - 1; i++ ){
		mnstr_buf[i].prev = &(mnstr_buf[i - 1]);
		mnstr_buf[i].next = &(mnstr_buf[i + 1]);
	}
	mnstr_buf[i].prev = &mnstr_buf[i - 1];
	mnstr_buf[i].next = &mnstr_free;
	mnstr_free.prev = &mnstr_buf[i];
}

/***************************************************************
* ��󥹥����κ������Υǥե�����ͤ�����
* mnstr_t *mnstr : ��󥹥���
***************************************************************/

void	new_mnstr( mnstr_t *mnstr )
{
	long	lev;
	long	i;

	reset_modifier( &(mnstr->modifier_equip) );
	reset_modifier( &(mnstr->modifier_fx) );

#if	0
	mnstr->prev = NULL;
	mnstr->next = NULL;
#endif
	mnstr->sort_chr_next = NULL;

	mnstr->kind = CHR_KIND_MNSTR;
	mnstr->name[0] = '0';
	mnstr->id1 = 0;
	mnstr->id2 = 0;
	mnstr->mbr_n = MBR_N_NOT_JOIN;
	mnstr->ls_mbr_n = 0;
	mnstr->position_kind = POSITION_KIND_FORWARD;
	mnstr->face.mjr = FACE_MJR_NULL;
	mnstr->face.mnr = FACE_MNR_NULL;
	mnstr->face.mjr_org = FACE_MJR_NULL;
	mnstr->face.mnr_org = FACE_MNR_NULL;
	mnstr->race.main = MAIN_RACE_HUMAN;
	mnstr->race.sub = SUB_RACE_NULL;
	mnstr->race.name[0] = '0';
	mnstr->sex.cur = MALE;
	mnstr->sex.org = MALE;
	mnstr->x = MAP_DEL_X;
	mnstr->y = MAP_DEL_Y;
	mnstr->pre_x = MAP_DEL_X;
	mnstr->pre_y = MAP_DEL_Y;
	mnstr->pre_turn_x = MAP_DEL_X;
	mnstr->pre_turn_y = MAP_DEL_Y;
	mnstr->pre_draw_x = MAP_DEL_X;
	mnstr->pre_draw_y = MAP_DEL_Y;
	mnstr->dx = 1;
	mnstr->dy = 1;
	mnstr->chr_dir_idx = CHR_DIR_IDX_NULL;

	mnstr->move.speed.rate = _100_PERCENT;
	mnstr->move.speed.rate_org = _100_PERCENT;
	mnstr->move.speed.n = 0;
	mnstr->move.force_kind = MOVE_KIND_NULL;
	for( i = 0; i < MOVE_LS_KIND_MAX_N; i++ ){
		mnstr->move.ls[i][0].kind = MOVE_KIND_NULL;
		mnstr->move.ls[i][0].ratio = 0;
	}

	mnstr->gold = 0;
	mnstr->dun_max_lev_floor = 0;
	mnstr->dun_max_lev_base = 0;

	mnstr->trgt.dist = DIST_NEAR;
	mnstr->trgt.dflt_dist_mnstr = DIST_NEAR;
	mnstr->act.dflt_kind_mnstr
			= ACT_KIND_MNSTR_FIGHT;
	str_nz_cpy( mnstr->act.dflt_msg_mnstr,
			MSG_MENU_MARK_FIGHT, ACT_MSG_MAX_BYTE );
	clr_chr_trgt_act( mnstr, TRUE );
	mnstr->pre_act = mnstr->act;

	mnstr->flg_chr = FLG_NULL;
	mnstr->flg_map = FLG_NULL;
	mnstr->attitude = ATTITUDE_ENEMY;
	mnstr->owner = NULL;
	mnstr->stat = FLG_NULL;

	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		lev = 1;

		mnstr->abl.lev[i].max = lev;
		mnstr->abl.exp[i].max = calc_lev_to_exp(
				lev, (abl_kind_t)i );

		mnstr->abl.lev[i].n = mnstr->abl.lev[i].max;
		mnstr->abl.lev[i].add = 0;
		mnstr->abl.exp[i].n = mnstr->abl.exp[i].max;
	}
	for( ; i < ABL_SKILL_MAX_N; i++ ){
		lev = 0;

		mnstr->abl.lev[i].max = lev;
		mnstr->abl.exp[i].max = calc_lev_to_exp(
				lev, (abl_kind_t)i );

		mnstr->abl.lev[i].n = mnstr->abl.lev[i].max;
		mnstr->abl.lev[i].add = 0;
		mnstr->abl.exp[i].n = mnstr->abl.exp[i].max;
	}
	mnstr->abl.hp.max = calc_max_hp( mnstr );
	mnstr->abl.mp.max = calc_max_mp( mnstr );
	mnstr->abl.hp.n = mnstr->abl.hp.max;
	mnstr->abl.mp.n = mnstr->abl.mp.max;

	mnstr->class_n = 0;

	for( i = 0; i < RESI_KIND_MAX_N; i++ ){
		mnstr->resi[i].n = _100_PERCENT;
		mnstr->resi[i].max = _100_PERCENT;
		mnstr->resi[i].add_n = 0;
	}
	mnstr->add_def = 0;
	mnstr->add_crtcl = 0;
	mnstr->add_ac = 0;

	mnstr->fx.next = &(mnstr->fx);
	mnstr->fx.prev = &(mnstr->fx);

	mnstr->fx_data.wpn_hit = (rate_t)0;
	mnstr->fx_data.wpn_crtcl = (rate_t)0;
	mnstr->fx_data.wpn_dam = (rate_t)0;

	mnstr->fx_data.armor_def = (rate_t)0;
	mnstr->fx_data.armor_crtcl = (rate_t)0;
	mnstr->fx_data.armor_ac = (rate_t)0;

	mnstr->fx_data.cure_hp.turn = 0;
	mnstr->fx_data.cure_hp.rate = 0;
	mnstr->fx_data.cure_hp.n = 0;

	mnstr->fx_data.cure_mp.turn = 0;
	mnstr->fx_data.cure_mp.rate = 0;
	mnstr->fx_data.cure_mp.n = 0;

	mnstr->fx_data.infra_vision = 0;

	mnstr->fx_data.stomach.rate = _100_PERCENT;
	mnstr->fx_data.stomach.full_rate = 100;
	mnstr->fx_data.stomach.digest_p_day = 20;
	mnstr->fx_data.stomach.hungry_rate = 70;
	mnstr->fx_data.stomach.starvation_rate = 30;

	mnstr->fx_data.drunk_rate = 0;

	mnstr->fx_data.nicotine.rate = 0;
	mnstr->fx_data.nicotine.poisoning_rate = 0;

	mnstr->fx_data.friend_turn = 0;

	mnstr->fx_data.bless = 0;

	mnstr->contribution = 0;

	mnstr->mnstr_kind = MNSTR_KIND_NULL;
	mnstr->mnstr_kind_org = MNSTR_KIND_NULL;
	mnstr->mnstr_tab = NULL;
	mnstr->mnstr_tab_org = NULL;

	mnstr->flg_pet = FALSE;

	mnstr->work.flg = FLG_NULL;
	mnstr->work.hyper_boss = HYPER_BOSS_NULL;
	mnstr->work.flg_hyper_boss = FALSE;
	mnstr->work.caught = 0;
	mnstr->work.catch_chr = NULL;
	mnstr->work.link_chr = NULL;
	mnstr->work.teleport_n = 0;
	mnstr->work.teleport_party_n = 0;
	mnstr->work.flg_can_wish = TRUE;
	mnstr->work.request = NULL;
	mnstr->work.towner_dx = 0;
	mnstr->work.towner_dy = 0;
	mnstr->work.enter_door = NULL;
	mnstr->work.dismissal_turn = 0;
	mnstr->work.flg_used_energy_drain = FALSE;
	mnstr->work.sync_vfx_num = 0;
	mnstr->work.sync_vfx_x = MAP_DEL_X;
	mnstr->work.sync_vfx_y = MAP_DEL_Y;

	mnstr->graph_name[0] = '\0';
}

/***************************************************************
* ������ʼ���Υ�󥹥������Ϥ�
* long x : X ��ɸ
* long y : Y ��ɸ
* bool_t flg_fix_pos : ����κ�ɸ���Ϥ�ʤ��ä��饭��󥻥뤹�뤫?
* long dun_lev : ���󥸥��γ���
* return : �Ϥä���󥹥���
***************************************************************/

mnstr_t	*make_mnstr_rand( long x, long y, bool_t flg_fix_pos, long dun_lev )
{
	mnstr_tab_t	*tab;
	mnstr_t	*p;
	long	i, j;

	if( dun_lev == 0 )
		tab = get_towner_tab_rand();
	else
		tab = get_mnstr_tab_rand( dun_lev );
	if( tab == NULL )
		return NULL;

	if( !can_move_mnstr_tab( tab, x, y ) )
		return NULL;

	p = make_mnstr( x, y, flg_fix_pos, dun_lev, tab->mnstr_kind );

	for( i = 1; i < tab->group; i++ ){
		long	nx, ny;
		mnstr_t	*pp;

		for( j = LOOP_MAX_100; j > 0; j-- ){
			nx = x + (randm( 10 + 1 + 10 ) - 10);
			ny = y + (randm( 10 + 1 + 10 ) - 10);
			pp = make_mnstr( nx, ny, flg_fix_pos,
					dun_lev, tab->mnstr_kind );
			if( pp != NULL )
				break;
		}
	}

	return p;
}

/***************************************************************
* ��󥹥������Ϥ�
* long x : X ��ɸ
* long y : Y ��ɸ
* bool_t flg_fix_pos : ����κ�ɸ���Ϥ�ʤ��ä��饭��󥻥뤹�뤫?
* long dun_lev : ���󥸥��γ���
* mnstr_kind_t mnstr_kind : ��󥹥����μ���
* return : �Ϥä���󥹥���
***************************************************************/

mnstr_t	*make_mnstr(
	long x, long y, bool_t flg_fix_pos,
	long dun_lev,
	mnstr_kind_t mnstr_kind
)
{
	mnstr_t	*p;

	p = mnstr_free.next;
	if( p == &mnstr_free )
		return NULL;
	ins_ls_mnstr( &mnstr_used, p );

	new_mnstr( p );

	if( make_mnstr_alloc( p, x, y, flg_fix_pos, dun_lev, mnstr_kind )
			== NULL ){
		die_chr( p, FALSE, FALSE, TRUE );
		return NULL;
	}

	return p;
}

/***************************************************************
* ���ݺѤΥ��꡼�˥�󥹥������Ϥ�
* mnstr_t *p : ��󥹥���
* long x : X ��ɸ
* long y : Y ��ɸ
* bool_t flg_fix_pos : ����κ�ɸ���Ϥ�ʤ��ä��饭��󥻥뤹�뤫?
* long dun_lev : ���󥸥��γ���
* mnstr_kind_t mnstr_kind : ��󥹥����μ���
* return : �Ϥä���󥹥���
***************************************************************/

mnstr_t	*make_mnstr_alloc(
	mnstr_t *p,
	long x, long y, bool_t flg_fix_pos,
	long dun_lev,
	mnstr_kind_t mnstr_kind
)
{
	long	i;
	mnstr_tab_t	*tab;

	if( p == NULL )
		return NULL;
	if( mnstr_kind == MNSTR_KIND_NULL )
		return NULL;

	tab = get_mnstr_tab( mnstr_kind, dun_lev );
	if( tab == NULL )
		return NULL;

	if( clip_pos( x, y ) && flg_fix_pos )
		if( !can_move_mnstr_tab( tab, x, y ) )
			return NULL;

	new_mnstr( p );

	str_nz_cpy( p->name, tab->name, MNSTR_NAME_MAX_BYTE );
	p->x = MAP_DEL_X;
	p->y = MAP_DEL_Y;
	p->pre_x = p->x;
	p->pre_y = p->y;
	p->dx = tab->dx;
	p->dy = tab->dy;
	p->face.mjr = tab->face_mjr;
	p->face.mnr = tab->face_mnr;
	p->face.mjr_org = tab->face_mjr;
	p->face.mnr_org = tab->face_mnr;
	if( per_randm( 2 ) )
		p->sex.org = MALE;
	else
		p->sex.org = FEMALE;
	p->sex.cur = p->sex.org;
	p->move = tab->move;
	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		long	lev;

		lev = calc_mnstr_abl_lev( dun_lev, (abl_kind_t)i, tab );

		p->abl.lev[i].n = lev;
		p->abl.lev[i].max = lev;
		p->abl.lev[i].add = 0;

		p->abl.exp[i].n = calc_need_exp( lev, (abl_kind_t)i );
		p->abl.exp[i].max = p->abl.exp[i].n;
	}
	p->abl.hp.max = calc_max_hp( p );
	p->abl.mp.max = calc_max_mp( p );
	p->abl.hp.n = p->abl.hp.max;
	p->abl.mp.n = p->abl.mp.max;

	for( i = 0; i < RESI_KIND_MAX_N; i++ ){
		p->resi[i].n = tab->resi[i];
		p->resi[i].max = tab->resi[i];
		p->resi[i].add_n = 0;
	}
	p->add_def = 0;
	p->add_crtcl = 0;
	p->add_ac = 0;
	p->gold = calc_mnstr_gold( dun_lev, tab->gold_rate );
	p->flg_chr = tab->flg_chr;
	p->flg_map = FLG_NULL;
	p->attitude = tab->attitude;
	p->stat = tab->stat;
	p->trgt.kind = TRGT_KIND_NULL;
	p->trgt.p = NULL;
	p->trgt.n = 0;
	p->trgt.x = 0;
	p->trgt.y = 0;
	p->trgt.true_x = 0;
	p->trgt.true_y = 0;
	p->fx.next = &(p->fx);
	p->fx.prev = &(p->fx);
	p->mnstr_kind = mnstr_kind;
	p->mnstr_kind_org = mnstr_kind;
	p->mnstr_tab = tab;
	p->mnstr_tab_org = tab;
	p->flg_pet = FALSE;

	p->work.flg = FLG_NULL;
	p->work.flg &= ~(FLG_WORK_FIND_MBR);
	p->work.caught = 0;
	p->work.catch_chr = NULL;
	p->work.towner_dx = randm( 3 ) - 1;
	p->work.towner_dy = randm( 3 ) - 1;
	p->work.enter_door = NULL;

	/**/

	if( chk_flg( p->flg_map, FLG_MAP_CHR_INVISIBLE )
			|| chk_flg( p->stat, FLG_STAT_VANISH ) ){
		p->flg_map |= FLG_MAP_CHR_INVISIBLE;
		p->stat |= FLG_STAT_VANISH;
	}

	if( p->attitude == ATTITUDE_ENEMY )
		p->flg_map &= ~FLG_MAP_CHR_NPC;
	else
		p->flg_map |= FLG_MAP_CHR_NPC;

	put_chr( p, x, y );

	if( !make_mnstr_special( p, dun_lev ) )
		return NULL;

	return p;
}

/***************************************************************
* ��󥹥����������������̤ʽ���
* mnstr_t *p : ��󥹥���
* long dun_lev : ���󥸥��γ���
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	make_mnstr_special( mnstr_t *p, long dun_lev )
{
	static bool_t	flg_link = FALSE;
	bool_t	ret = TRUE;
	mnstr_t	*p2, *pre_p;
	long	n;
	item_t	*chest;
	long	i;

	if( p == NULL )
		return FALSE;

	switch( p->mnstr_kind ){
	default:
		break;
	case MNSTR_KIND_GIGANTIC_CENTIPEDE:
		if( flg_link )
			break;
		flg_link = TRUE;

		pre_p = p;
		for( i = 1; i < GIGANTIC_CENTIPEDE_LINK_N; i++ ){
			p2 = make_mnstr( pre_p->x, pre_p->y + 1, FALSE,
					dun_lev, p->mnstr_kind );
			if( p2 == NULL )
				break;
			mark_mnstr( p2, pre_p, DIST_NEAR );
			p2->work.link_chr = pre_p;

			pre_p = p2;
		}

		flg_link = FALSE;
		break;
	case MNSTR_KIND_GARGOYLE:
		n = 0;
		if( !set_statue( p->x, p->y, dun_lev, TRUE ) ){
			ret = FALSE;
			break;
		}
		n++;

		for( i = 0; i < LOOP_MAX_1000; i++ ){
			long	x, y;

			if( n >= GARGOYLE_STATUE_N )
				break;

			x = p->x / MAP_MAX_X * MAP_MAX_X;
			x += randm( AREA_MAX_X - 2) + 1;
			y = p->y / MAP_MAX_Y * MAP_MAX_Y;
			x += randm( AREA_MAX_Y - 2) + 1;
			if( set_statue( x, y, dun_lev, FALSE ) )
				n++;
		}
		break;
	case MNSTR_KIND_MIMIC:
		if( get_item( p->x, p->y ) != NULL ){
			ret = FALSE;
			break;
		}

		chest = make_item_chest( dun_lev,
				get_chest_n( dun_lev ), TRUE );

		if( chest == NULL ){
			ret = FALSE;
			break;
		}
		if( !put_item( chest, p->x, p->y, 1, FALSE ) ){
			del_item( chest );
			ret = FALSE;
			break;
		}

		break;
	case MNSTR_KIND_EXEL:
		g_last_boss[LAST_BOSS_KIND_EXEL] = p;

		p->flg_chr |= FLG_CHR_HYPER;
		p->work.hyper_boss = HYPER_BOSS_NORMAL;
		p->work.flg_hyper_boss = FALSE;
		break;
	case MNSTR_KIND_EXELER:
		g_last_boss[LAST_BOSS_KIND_EXELER] = p;

		p->flg_chr |= FLG_CHR_HYPER;
		p->work.hyper_boss = HYPER_BOSS_NORMAL;
		p->work.flg_hyper_boss = FALSE;
		break;
	case MNSTR_KIND_XEX:
		g_last_boss[LAST_BOSS_KIND_XEX] = p;
		break;
	case MNSTR_KIND_XX:
		g_last_boss[LAST_BOSS_KIND_XX] = p;
		break;
	}

	return ret;
}

/***************************************************************
* ������ʼ���� NPC ���Ϥ�
* long x : X ��ɸ
* long y : Y ��ɸ
* long dun_lev : ���󥸥��γ���
* return : �Ϥä� NPC
***************************************************************/

mnstr_t	*make_npc_rand( long x, long y, long dun_lev )
{
	mnstr_kind_t	kind;

	kind = get_npc_kind_randm();

	if( dun_lev == 0 )
		dun_lev = TOWNER_AVE_DUN_LEV;
	dun_lev = roll_dice( dun_lev, FALSE );
	if( dun_lev < 1 )
		dun_lev = 1;

	return make_mnstr( x, y, FALSE, dun_lev, kind );
}

/***************************************************************
* ���ƤΥ�󥹥����ΰ�ư�ե�������¹�
***************************************************************/

void	move_phase_all_mnstr( void )
{
	mnstr_t	*head, *p, *pp;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		set_act_mnstr( pp );
		move_phase_chr( pp );
	}
}

/***************************************************************
* ���ƤΥ�󥹥����ι�ư�ե�������¹�
***************************************************************/

void	act_phase_all_mnstr( void )
{
	mnstr_t	*head, *p, *pp;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		act_phase_chr( pp );
		set_modifier( pp );
	}
}

/***************************************************************
* ���ƤΥ�󥹥��������ԥե�������¹�
***************************************************************/

void	dismissal_phase_all_mnstr( void )
{
	mnstr_t	*head, *p, *pp;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		dismissal_phase_chr( pp );
	}
}

/***************************************************************
* ��󥹥����ι�ư���¹Խ�����Υ�ޤǰ�ư������Ĵ�٤�
* mnstr_t *p : ��󥹥���
* return : �¹Խ���뤫?
***************************************************************/

bool_t	chk_can_act_mnstr( mnstr_t *p )
{
	long	i;
	party_t	*party;
	dun_t	*dun;

	party = get_party();
	dun = get_dun();

	if( p == NULL )
		return FALSE;
	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( party->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( labs( p->x - party->mbr[i]->x ) > MNSTR_MOVE_MAX_X )
			continue;
		if( labs( p->y - party->mbr[i]->y ) > MNSTR_MOVE_MAX_Y )
			continue;

		break;
	}
	if( i >= MBR_MAX_N ){
		long	bx, by;
		long	ex, ey;
		long	x, y;

		/* �����С�����Υ��Ƥ����� */

		p->flg_map &= ~FLG_MAP_CHR_FIND;

		bx = get_chr_left( p->x, p->dx );
		by = get_chr_top( p->y, p->dy );
		ex = get_chr_right( p->x, p->dx );
		ey = get_chr_bottom( p->y, p->dy );
		for( y = by; y <= ey; y++ ){
			for( x = bx; x <= ex; x++ ){
				if( !clip_pos( x, y ) )
					continue;

				dun->map.chr.flg[y][x] = p->flg_map;
			}
		}

		/* ���̤���õ� */
		draw_mnstr( p );

		return FALSE;
	}

	if( chk_flg_or( p->stat,
			FLG_STAT_NOT_EXIST | FLG_STAT_DEAD
			| FLG_STAT_STONE | FLG_STAT_PARALYZE
			| FLG_STAT_SLEEP | FLG_STAT_FAINT
			| FLG_STAT_IRON_BODY
			) ){
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ��󥹥����ι�ư������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	set_act_mnstr( mnstr_t *p )
{
	if( p == NULL )
		return;
	if( p->mnstr_tab == NULL )
		return;

	if( p->mnstr_tab->func == NULL )
		set_act_mnstr_std( p );
	else
		p->mnstr_tab->func( p );
}

/***************************************************************
* ��󥹥����Υ������åȤ�ɸ��Ū������
* mnstr_t *p : ��󥹥���
* return : �������åȤ������С�
***************************************************************/

mbr_t	*mnstr_mark_mbr_std( mnstr_t *p )
{
	return mnstr_mark_mbr_common( p, SEX_NULL );
}

/***************************************************************
* ��󥹥����Υ������åȤ����̤���ꤷ��ɸ��Ū������
* mnstr_t *p : ��󥹥���
* sex_t sex : �������åȤ�����
* return : �������åȤ������С�
***************************************************************/

mbr_t	*mnstr_mark_mbr_cubus( mnstr_t *p, sex_t sex )
{
	return mnstr_mark_mbr_common( p, sex );
}

/***************************************************************
* ��󥹥����Υ������åȤ�ɸ��Ū�����ꤹ�붦�̽���
* mnstr_t *p : ��󥹥���
* sex_t sex : �������åȤ�����
* return : �������åȤ������С�
***************************************************************/

mbr_t	*mnstr_mark_mbr_common( mnstr_t *p, sex_t sex )
{
	party_t	*pty = get_party();
	pet_t	**pty_pet = get_party_pet();
	trgt_kind_t	trgt_kind;
	chr_t	*mark_p;
	long	i;
	long	r;

	if( p == NULL )
		return NULL;

	clr_chr_trgt( p );

	trgt_kind = TRGT_KIND_NULL;
	mark_p = NULL;
	r = MAP_MAX_X + MAP_MAX_Y;
	for( i = 0; i < MBR_MAX_N; i++ ){
		long	tmp_r;

		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( !chk_flg_work_find_mbr( p ) ){
			if( !chk_find_chr( p, pty->mbr[i] ) ){
				continue;
			}
		}

		if( sex != SEX_NULL )
			if( sex != pty->mbr[i]->sex.cur )
				continue;

		tmp_r = labs( pty->mbr[i]->x - p->x )
				+ labs( pty->mbr[i]->y - p->y );
		if( tmp_r < r ){
			trgt_kind = TRGT_KIND_MBR;
			mark_p = pty->mbr[i];
			r = tmp_r;
		}
	}
	for( i = 0; i < PET_MAX_N; i++ ){
		long	tmp_r;

		if( pty_pet[i] == NULL )
			continue;

		if( chk_flg_or( pty_pet[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( !chk_flg_work_find_mbr( p ) ){
			if( !chk_find_chr( p, pty_pet[i] ) )
				continue;
		}

		if( sex != SEX_NULL )
			continue;

		tmp_r = labs( pty_pet[i]->x - p->x )
				+ labs( pty_pet[i]->y - p->y );
		if( tmp_r < r ){
			trgt_kind = TRGT_KIND_MNSTR;
			mark_p = pty_pet[i];
			r = tmp_r;
		}
	}
	if( mark_p == NULL ){
		if( sex == SEX_NULL )
			return NULL;
		else
			return mnstr_mark_mbr_common( p, SEX_NULL );
	}

	/* ���Ĥ��� */

	set_flg_work_find_mbr( p, TRUE );

	p->trgt.kind = trgt_kind;
	p->trgt.p = mark_p;
	p->trgt.n = mark_p->mbr_n;
	p->trgt.x = mark_p->x;
	p->trgt.y = mark_p->y;
	p->trgt.true_x = p->trgt.x;
	p->trgt.true_y = p->trgt.y;

	return( (mbr_t *)(p->trgt.p) );
}

/***************************************************************
* ���ܤ�����С��˥�󥹥����Υ������åȤ����ꤹ��
* mnstr_t *p : ��󥹥���
* return : �������åȤ������С�
***************************************************************/

mbr_t	*mnstr_mark_mbr_adjoin( mnstr_t *p )
{
	party_t	*pty = get_party();
	pet_t	**pty_pet = get_party_pet();
	trgt_kind_t	trgt_kind;
	chr_t	*mark_p;
	long	i;

	if( p == NULL )
		return NULL;

	if( p->attitude != ATTITUDE_ENEMY )
		return NULL;
	if( chk_flg( p->stat, FLG_STAT_CHARM ) )
		return NULL;

	trgt_kind = TRGT_KIND_NULL;
	mark_p = NULL;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD
				| FLG_STAT_VANISH ) ){
			continue;
		}

		if( labs( p->x - pty->mbr[i]->x ) > 1 )
			continue;
		if( labs( p->y - pty->mbr[i]->y ) > 1 )
			continue;

		trgt_kind = TRGT_KIND_MBR;
		mark_p = pty->mbr[i];
		break;
	}
	for( i = 0; i < PET_MAX_N; i++ ){
		if( mark_p != NULL )
			break;

		if( pty_pet[i] == NULL )
			break;
		if( chk_flg_or( pty_pet[i]->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD
				| FLG_STAT_VANISH ) ){
			continue;
		}
		if( labs( p->x - pty_pet[i]->x ) > 1 )
			continue;
		if( labs( p->y - pty_pet[i]->y ) > 1 )
			continue;

		trgt_kind = TRGT_KIND_MNSTR;
		mark_p = pty_pet[i];
		break;
	}

	if( mark_p == NULL )
		return NULL;

	/* ���Ĥ��� */

	p->flg_map |= FLG_MAP_CHR_FIND;
	set_flg_work_find_mbr( p, TRUE );

	if( chk_flg( p->flg_map, FLG_MAP_CHR_INVISIBLE )
			|| chk_flg( p->stat, FLG_STAT_VANISH ) ){
		item_t	*item;

		p->flg_map &= ~FLG_MAP_CHR_INVISIBLE;
		p->stat &= ~FLG_STAT_VANISH;
		draw_mnstr( p );

		curs_attrset_chr( mark_p, -1, FALSE );
		print_msg( FLG_NULL, MSG_MBR_FIND_INVISIBLE,
				p->name );
		curs_attrset_dflt();

		call_game_sound_play( SOUND_KIND_ACTION_APPEAR, 1 );

		item = get_item( p->x, p->y );
		if( item != NULL )
			lost_trgt( item );
	}

	p->trgt.kind = trgt_kind;
	p->trgt.p = mark_p;
	p->trgt.n = mark_p->mbr_n;
	p->trgt.x = mark_p->x;
	p->trgt.y = mark_p->y;
	p->trgt.true_x = p->trgt.x;
	p->trgt.true_y = p->trgt.y;

	return( (mbr_t *)(p->trgt.p) );
}

/***************************************************************
* ��󥹥����ΰ�ư�������ɸ��Ū�ʹ�ư������
* mnstr_t *p : ��󥹥���
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	mnstr_move_or_atack_std( mnstr_t *p )
{
	chr_t	*trgt;
	act_kind_t	act_kind;
	attack_t	*ls;
	ratio_t	sum_bash, sum_throw, sum_spell, n;

	if( p == NULL )
		return FALSE;
	if( p->mnstr_tab == NULL )
		return FALSE;
	if( chk_flg( p->stat, FLG_STAT_CHARM ) )
		return FALSE;
	if( (p->trgt.kind != TRGT_KIND_MBR)
			&& (p->trgt.kind != TRGT_KIND_MNSTR) ){
		return FALSE;
	}
	if( p->trgt.p == NULL )
		return FALSE;

	trgt = (chr_t *)(p->trgt.p);
	ls = p->mnstr_tab->attack;

	sum_bash = calc_attack_sum( ls, TRUE, TRUE, FALSE, FALSE );
	sum_throw = calc_attack_sum( ls, FALSE, FALSE, TRUE, FALSE );
	sum_spell = calc_attack_sum( ls, FALSE, FALSE, FALSE, TRUE );

	if( !chk_can_chr_cast_stat( p ) )
		sum_spell = 0;

	n = randm( sum_bash + sum_throw + sum_spell );

	if( n < sum_bash ){
		if( is_mbr( trgt ) )
			act_kind = ACT_KIND_MBR_FIGHT;
		else
			act_kind = ACT_KIND_MNSTR_FIGHT;

		set_chr_act( p, act_kind, trgt, NULL, 0, 0 );
	} else if( n < sum_bash + sum_throw ){
		if( is_mbr( trgt ) )
			act_kind = ACT_KIND_MBR_THROW;
		else
			act_kind = ACT_KIND_MNSTR_THROW;

		set_chr_act( p, act_kind, trgt, NULL, 0, 0 );
	} else {
		bool_t	flg_cast;
		attack_t	*atk;
		long	d;
		chr_t	*friend_chr;

		flg_cast = TRUE;

		d = max_l( labs( p->x - trgt->x ), labs( p->y - trgt->y ) );
		atk = get_attack( FALSE, ls, d,
				FALSE, FALSE, FALSE, TRUE );
		if( atk == NULL )
			return FALSE;

		if( atk->kind == ATTACK_KIND_SPELL_SELF )
			friend_chr = p;
		else if( atk->kind == ATTACK_KIND_SPELL_FRIEND )
			friend_chr = get_mnstr_friend( p, p->x, p->y );
		else
			friend_chr = NULL;

		if( friend_chr == NULL ){
			if( !chk_find_chr( p, trgt ) )
				flg_cast = FALSE;
		} else {
			rate_t	rate;

			rate = friend_chr->abl.hp.n * _100_PERCENT
					/ friend_chr->abl.hp.max;

			if( (rate <= MNSTR_SPELL_FRIEND_HP_RATE)
					&& chk_find_chr( p, friend_chr ) ){
				trgt = friend_chr;
				mark_mnstr( p, friend_chr, DIST_FAR );
			} else {
				flg_cast = FALSE;
			}
		}

		if( flg_cast ){
			set_chr_act( p, ACT_KIND_SPELL,
					get_spell_tab( atk->spell ),
					MSG( atk->spell_fmt ),
					atk->extent, 0 );
		} else {
			if( is_mbr( trgt ) )
				act_kind = ACT_KIND_MBR_FIGHT;
			else
				act_kind = ACT_KIND_MNSTR_FIGHT;

			set_chr_act( p, act_kind, trgt, NULL, 0, 0 );
		}
	}

	return TRUE;
}

/***************************************************************
* ��󥹥����η��������Ũ�ˤޤ魯
* chr_t *o_p : ��˹����ųݤ������Υ���饯��
* chr_t *d_p : �ܤ����Υ���饯��
***************************************************************/

void	set_enemy_mnstr_group( chr_t *o_p, chr_t *d_p )
{
	mnstr_t	*head, *p, *pp;

	if( o_p == NULL )
		return;
	if( d_p == NULL )
		return;

	if( o_p->kind != CHR_KIND_MBR )
		return;
	if( d_p->kind == CHR_KIND_MBR )
		return;
	if( d_p->attitude == ATTITUDE_MATE )
		return;
	if( d_p->attitude == ATTITUDE_ENEMY )
		return;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		if( pp->face.mjr == d_p->face.mjr ){
			pp->attitude = ATTITUDE_ENEMY;
			draw_mnstr( pp );
		}
	}
}

/***************************************************************
* ���ƤΥ�󥹥����Υ������ 1 �Ŀʤ��
***************************************************************/

void	inc_turn_all_mnstr( void )
{
	mnstr_t	*head, *p, *pp;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		pp->fx_data.infra_vision--;
		if( pp->fx_data.infra_vision < 0 )
			pp->fx_data.infra_vision = 0;
	}
}

/***************************************************************
* ��󥹥�����ʬ�󤷤ƿ��򿣤䤹
* mnstr_t *p : ��󥹥���
* return : ʬ�󤷤���?
***************************************************************/

bool_t	increase_mnstr( mnstr_t *p )
{
	long	nx, ny;
	dun_t	*dun;
	mnstr_t	*new_mnstr;

	if( p == NULL )
		return FALSE;

	dun = get_dun();

	nx = p->x + (randm( 3 ) - 1);
	ny = p->y + (randm( 3 ) - 1);

	new_mnstr = make_mnstr( nx, ny, FALSE, dun->lev, p->mnstr_kind );
	if( new_mnstr == NULL )
		return FALSE;

	new_mnstr->attitude = p->attitude;

	return TRUE;
}

/***************************************************************
* ��󥹥������ɥ��򳫤��뤫�����ͤ˹�ư������
* mnstr_t *p : ��󥹥���
* long x1 : 1 ���ܤ� X ��ɸ
* long y1 : 1 ���ܤ� Y ��ɸ
* long x2 : 2 ���ܤ� X ��ɸ
* long y2 : 2 ���ܤ� Y ��ɸ
* return : ��ư�����ꤷ����?
***************************************************************/

bool_t	chk_auto_door_mnstr( mnstr_t *p, long x1, long y1, long x2, long y2 )
{
	if( p == NULL )
		return FALSE;
	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;

	if( chk_flg( p->flg_chr, FLG_CHR_CAN_OPEN_DOOR ) ){
		if( chk_auto_door_mnstr_open( p, x1, y1 ) )
			return TRUE;
		if( chk_auto_door_mnstr_open( p, x2, y2 ) )
			return TRUE;
	} else if( chk_flg( p->flg_chr, FLG_CHR_CAN_BREAK_DOOR ) ){
		if( chk_auto_door_mnstr_break( p, x1, y1 ) )
			return TRUE;
		if( chk_auto_door_mnstr_break( p, x2, y2 ) )
			return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ��󥹥������ɥ��򳫤����ͤ˹�ư������
* mnstr_t *p : ��󥹥���
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��ư�����ꤷ����?
***************************************************************/

bool_t	chk_auto_door_mnstr_open( mnstr_t *p, long x, long y )
{
	dun_t	*dun = get_dun();
	door_t	*dr;

	if( p == NULL )
		return FALSE;
	if( !clip_pos( x, y ) )
		return FALSE;

	if( dun->map.obj.mjr[y][x] != FACE_MJR_DOOR_CLOSE )
		return FALSE;
	if( chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_LOOK_WALL ) )
		return FALSE;

	dr = get_door( x, y );
	if( dr == NULL )
		return FALSE;

	return chr_open_door( p, dr->n );
}

/***************************************************************
* ��󥹥������ɥ�������ͤ˹�ư������
* mnstr_t *p : ��󥹥���
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��ư�����ꤷ����?
***************************************************************/

bool_t	chk_auto_door_mnstr_break( mnstr_t *p, long x, long y )
{
	dun_t	*dun = get_dun();
	door_t	*dr;

	if( p == NULL )
		return FALSE;
	if( !clip_pos( x, y ) )
		return FALSE;

	if( dun->map.obj.mjr[y][x] != FACE_MJR_DOOR_CLOSE )
		return FALSE;
	if( chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_LOOK_WALL ) )
		return FALSE;

	dr = get_door( x, y );
	if( dr == NULL )
		return FALSE;

	return chr_break_door( p, dr->n );
}

/***************************************************************
* ���ƤΥ�󥹥�����ȯ�����줿�������å�����
***************************************************************/

void	set_flg_find_all_mnstr( void )
{
	mnstr_t	*head, *p, *pp;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		set_flg_find_mnstr( pp );
	}
}

/***************************************************************
* ��󥹥�����ȯ�����줿�������å�����
* mnstr_t *p : ��󥹥���
* return : ȯ�����줿��?
***************************************************************/

bool_t	set_flg_find_mnstr( mnstr_t *p )
{
	long	i;
	dun_t	*dun;
	party_t	*pty;
	bool_t	flg_pre_find;
	flg_map_t	flg;
	long	bx, by;
	long	ex, ey;
	long	x, y;

	dun = get_dun();
	pty = get_party();

	if( p == NULL )
		return FALSE;
	if( chk_flg_or( p->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return FALSE;

	/* ȯ��������Ĵ�٤� */

	flg_pre_find = chk_flg( p->flg_map, FLG_MAP_CHR_FIND );
	if( chk_flg( p->flg_map, FLG_MAP_CHR_INVISIBLE ) )
		flg_pre_find = FALSE;

	p->flg_map &= ~FLG_MAP_CHR_FIND;
	flg = p->flg_map;
	for( i = 0; i < MBR_MAX_N; i++ ){
		/* ȯ��������? */
		if( chk_find_chr( pty->mbr[i], p ) ){
			/* ȯ�������ޥåס��ե饰��Ω�Ƥ� */
			p->flg_map |= FLG_MAP_CHR_FIND;
			p->flg_map &= ~FLG_MAP_CHR_INVISIBLE;
			flg = p->flg_map;

			break;
		}
	}

	if( chk_flg( p->flg_map, FLG_MAP_CHR_FIND ) ){
		if( flg_pre_find ){
			return TRUE;
		} else {
			/* �������ɸ�������å� */
			chk_find_request_chr( p );
		}
	}

	bx = get_chr_left( p->x, p->dx );
	by = get_chr_top( p->y, p->dy );
	ex = get_chr_right( p->x, p->dx );
	ey = get_chr_bottom( p->y, p->dy );
	for( y = by; y <= ey; y++ ){
		for( x = bx; x <= ex; x++ ){
			if( !clip_pos( x, y ) )
				continue;

				dun->map.chr.flg[y][x] = flg;
		}
	}

	return( chk_flg( p->flg_map, FLG_MAP_CHR_FIND ) );
}

/***************************************************************
* ��󥹥��������С���ȯ���������֤Υե饰��Ĵ�٤�
* mnstr_t *p : ��󥹥���
* return : ȯ���������֤Υե饰
***************************************************************/

bool_t	chk_flg_work_find_mbr( mnstr_t *p )
{
	if( p == NULL )
		return FALSE;

	return( chk_flg( p->work.flg, FLG_WORK_FIND_MBR ) );
}

/***************************************************************
* ��󥹥��������С���ȯ���������֤Υե饰�����ꤹ��
* mnstr_t *p : ��󥹥���
* bool_t flg : ȯ���������֤Υե饰
***************************************************************/

void	set_flg_work_find_mbr( mnstr_t *p, bool_t flg )
{
	if( p == NULL )
		return;

	if( flg ){
		if( !chk_flg( p->work.flg, FLG_WORK_FIND_MBR ) )
			chk_boss_find_mbr( p );

		p->work.flg |= FLG_WORK_FIND_MBR;
		set_flg_mnstr_find_mbr( TRUE );
	} else {
		p->work.flg &= ~(FLG_WORK_FIND_MBR);
	}
}

/***************************************************************
* �ܥ������С���ȯ���������˥�å�������ɽ������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	chk_boss_find_mbr( mnstr_t *p )
{
	if( p == NULL )
		return;
	if( !is_boss( p ) )
		return;

	set_flg_boss_find_mbr( TRUE );

	curs_attrset_chr( p, +1, TRUE );
	print_msg( FLG_NULL, MSG_BOSS_FIND_MBR, p->name );
	curs_attrset_dflt();

	draw_words( NULL, MSG_BOSS_FIND_MBR, p->name );
	redraw_all();
}

/***************************************************************
* ���ƤΥ�󥹥����ˤĤ���櫤˳ݤ��ä��������å�
***************************************************************/

void	chk_trap_all_mnstr( void )
{
	mnstr_t	*head, *p, *pp;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		chk_trap( pp, pp );
	}
}

/***************************************************************
* ��󥹥������������˥����ƥ���
* mnstr_t *p : ��󥹥���
***************************************************************/

void	die_mnstr_drop_item( mnstr_t *p )
{
	if( p == NULL )
		return;
	if( p->kind != CHR_KIND_MNSTR )
		return;
	if( is_pet( p ) )
		return;

	mnstr_drop_bone( p );
	mnstr_drop_gold( p );
	mnstr_drop_item( p );
}

/***************************************************************
* ��󥹥������������ν���
* mnstr_t *p : ��󥹥���
* bool_t flg_msg : ��å�������ɸ�����뤫?
***************************************************************/

void	die_mnstr( mnstr_t *p, bool_t flg_msg )
{
	if( p == NULL )
		return;
	if( p->kind != CHR_KIND_MNSTR )
		return;

	if( is_pet( p ) ){
		die_pet( p, flg_msg );
		return;
	}

	if( !flg_msg )
		return;

	if( is_xx( p ) ){
		call_game_sound_play(
				SOUND_KIND_FIGHT_DIE_MONSTER_BOSS_LAST,
				1 );
	} else if( p->mnstr_kind == MNSTR_KIND_XEX ){
		;
	} else if( is_boss( p ) ){
		call_game_sound_play(
				SOUND_KIND_FIGHT_DIE_MONSTER_BOSS,
				1 );
	} else {
		call_game_sound_play(
				SOUND_KIND_FIGHT_DIE_MONSTER,
				1 );
	}
}

/***************************************************************
* ������󥹥������ܥ��������å����ƽ����򤹤�
* mnstr_t *p : ��󥹥���
* return : �ܥ����ä���?
***************************************************************/

bool_t	chk_die_boss( mnstr_t *p )
{
	if( !is_boss( p ) )
		return FALSE;

	die_boss( p );

	return TRUE;
}

/***************************************************************
* ��󥹥������ܥ���Ĵ�٤�
* mnstr_t *p : ��󥹥���
* return : �ܥ���?
***************************************************************/

bool_t	is_boss( mnstr_t *p )
{
	if( p == NULL )
		return FALSE;
	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( p->mnstr_tab == NULL )
		return FALSE;
	if( !(p->mnstr_tab->flg_boss) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ��󥹥������饹�ܥ���Ĵ�٤�
* mnstr_t *p : ��󥹥���
* return : �饹�ܥ���?
***************************************************************/

bool_t	is_last_boss( mnstr_t *p )
{
	mnstr_t	*boss;
	long	i;

	if( p == NULL )
		return FALSE;
	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;

	for( i = LAST_BOSS_KIND_NULL; i < LAST_BOSS_KIND_MAX_N; i++ ){
		boss = get_last_boss( (last_boss_kind_t)i );
		if( boss == NULL )
			continue;

		if( p->mnstr_kind == boss->mnstr_kind )
			return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ��󥹥����� XX ��Ĵ�٤�
* mnstr_t *p : ��󥹥���
* return : XX ��?
***************************************************************/

bool_t	is_xx( mnstr_t *p )
{
	if( p == NULL )
		return FALSE;
	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( p->mnstr_kind != MNSTR_KIND_XX )
		return FALSE;

	return TRUE;
}

/***************************************************************
* �ܥ�����󥹥������������ν���
* mnstr_t *m : ��󥹥���
***************************************************************/

void	die_boss( mnstr_t *m )
{
	long	boss_n;
	mnstr_t	*head, *p, *pp;

	if( m == NULL )
		return;

	boss_n = 0;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( pp->mnstr_tab != NULL ){
			if( pp->mnstr_tab->flg_boss ){
				boss_n++;
			}
		}
	}

	if( boss_n <= 1 ){
		/* ��å����� */
		draw_words( NULL, MSG_FIGHT_KILL_BOSS, m->name );

		/* ��ܥ����ݤ����鳬�ʤ������ */
		make_stairs( m->x, m->y, FACE_MJR_STAIRS_DOWN );

		/* �����������ƥ� */
		mnstr_drop_key_item( p );

		redraw_all();
	}
}

/***************************************************************
* ������󥹥����Υ��꡼�����
***************************************************************/

void	garbage_collection_all_mnstr( void )
{
	mnstr_t	*head, *p, *pp;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		if( !chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( is_pet( pp ) )
			continue;

		/* ���꡼����� */

		ins_ls_mnstr( &mnstr_free, pp );
	}
}

/***************************************************************
* ��󥹥������������˶���
* mnstr_t *p : ��󥹥���
***************************************************************/

void	mnstr_drop_gold( mnstr_t *p )
{
	long	n;
	item_t	*coin;

	if( p == NULL )
		return;

	if( p->gold <= 0 )
		return;

	n = get_coin_tab_n( get_coin_tab( COIN_KIND_GOLD ) );
	if( n < 0 )
		return;

	coin = make_item_coin( 1, n );
	if( coin == NULL )
		return;
	coin->n = p->gold;
	set_item_name( coin );

	if( !put_item( coin, p->x, p->y, PUT_ITEM_R, FALSE ) )
		del_item( coin );
}

/***************************************************************
* ��󥹥������������˹����
* mnstr_t *p : ��󥹥���
***************************************************************/

void	mnstr_drop_bone( mnstr_t *p )
{
	dun_t	*dun = get_dun();
	long	max_n;
	long	i;

	if( p == NULL )
		return;
	if( p->mnstr_tab == NULL )
		return;

	if( !rate_randm( MNSTR_DROP_BONE_RATE ) )
		return;

	if( p->mnstr_tab->bone_ave_n <= 0 )
		max_n = 0;
	else
		max_n = roll_dice( p->mnstr_tab->bone_ave_n, FALSE );

	for( i = 0; i < max_n; i++ ){
		item_t	*bone;

		bone = make_item_bone( dun->lev, p->mnstr_tab );
		if( bone == NULL )
			continue;

		if( !put_item( bone, p->x, p->y, PUT_ITEM_R, FALSE ) )
			del_item( bone );
	}
}

/***************************************************************
* ��󥹥������������˥����ƥ���
* mnstr_t *p : ��󥹥���
***************************************************************/

void	mnstr_drop_item( mnstr_t *p )
{
	dun_t	*dun = get_dun();
	long	i, j;

	if( p == NULL )
		return;
	if( p->mnstr_tab == NULL )
		return;

	for( i = 0; i < p->mnstr_tab->item_max_n; i++ )
		make_item( p->x, p->y, dun->lev );

	for( i = 0; i < MNSTR_ITEM_N_MAX_N; i++ ){
		mnstr_item_n_t	*a;

		a = &(p->mnstr_tab->item_n[i]);
		if( a->kind == ITEM_KIND_NULL )
			break;

		for( j = 0; j < a->n; j++ ){
			item_t	*item;

			item = make_item_sel( a->kind,
					a->k1, a->k2, a->k3, dun->lev );
			if( item == NULL )
				continue;

			if( !put_item( item, p->x, p->y, PUT_ITEM_R, FALSE ) )
				del_item( item );
		}
	}
}

/***************************************************************
* �ܥ�����󥹥������������˥����������ƥ���
* mnstr_t *p : ��󥹥���
***************************************************************/

void	mnstr_drop_key_item( mnstr_t *p )
{
	dun_t	*dun = get_dun();
	star_drop_kind_t	kind;
	static char	str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;

	if( p == NULL )
		return;
	if( p->mnstr_tab == NULL )
		return;

	kind = (star_drop_kind_t)
			(labs( dun->lev ) / DUN_LEV_BOSS - 1);
	kind = (star_drop_kind_t)
			((kind + BOOT_UNIT_MAX_N) % BOOT_UNIT_MAX_N);

	if( chk_key_item( kind ) )
		return;

	set_key_item( kind, TRUE );

	sn_printf( str, max_len, MSG_GET_KEY_ITEM,
			get_key_item_name( kind ) );

	print_msg( FLG_NULL, MSG_S, str );
	draw_words( NULL, str );
	redraw_all();
}

/***************************************************************
* ���ƤΥ�󥹥�����ȯ���ȲĻ�ξ��֤ˤ���
***************************************************************/

void	set_find_all_mnstr( void )
{
	mnstr_t	*head, *p, *pp;
	dun_t	*dun = get_dun();
	long	bx, by;
	long	ex, ey;
	long	x, y;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		pp->flg_map |= FLG_MAP_CHR_FIND;
		pp->flg_map &= ~FLG_MAP_CHR_INVISIBLE;

		bx = get_chr_left( pp->x, pp->dx );
		by = get_chr_top( pp->y, pp->dy );
		ex = get_chr_right( pp->x, pp->dx );
		ey = get_chr_bottom( pp->y, pp->dy );
		for( y = by; y <= ey; y++ ){
			for( x = bx; x <= ex; x++ ){
				if( !clip_pos( x, y ) )
					continue;

				dun->map.chr.flg[y][x] = pp->flg_map;
			}
		}
	}
}

/***************************************************************
* ��󥹥������������ؤΥꥹ�Ȥ�ɽ��
***************************************************************/

void	print_ls_mnstr( void )
{
	long	max_dun_lev_base, min_lev, max_lev;
	long	i, max_i;

	/* ���ߤγ����Τ�ʤ����ˤ��� */

	max_dun_lev_base = get_party_dun_max_lev();
	max_dun_lev_base--;

	/* ��󥹥����Υꥹ�Ȥ�ʤ�� */

	min_lev = 0;
	max_i = sizeof( mnstr_lev_tab ) / sizeof( mnstr_lev_tab[0] );
	for( i = 0; i < max_i; i++ ){
		mnstr_tab_t	*tab;

		if( mnstr_lev_tab[i].kind == MNSTR_KIND_NULL )
			break;

		/* ���ؤ������ͤ������ͤ��Ѵ� */

		min_lev += mnstr_lev_tab[i].add_lev;
		max_lev = min_lev + mnstr_lev_tab[i].range_lev - 1;

		/* ���ؤ��ϰϥ����å� */

		if( min_lev > max_dun_lev_base )
			continue;
		if( max_lev > max_dun_lev_base )
			max_lev = max_dun_lev_base;

		/* ��󥹥����Υơ��֥������ */

		tab = get_mnstr_tab( mnstr_lev_tab[i].kind, min_lev );
		if( tab == NULL )
			continue;

		print_msg( FLG_NULL, MSG_LS_MNSTR,
				min_lev, max_lev, tab->name );
	}
}

/***************************************************************
* NPC �μ�����������֤�
* return : NPC �μ���
***************************************************************/

mnstr_kind_t	get_npc_kind_randm( void )
{
	long	n;
	long	i, max_n;

	max_n = sizeof( g_ls_npc_kind ) / sizeof( g_ls_npc_kind[0] );
	for( i = 0; i < max_n; i++ ){
		if( g_ls_npc_kind[i] == MNSTR_KIND_NULL )
			break;
	}
	n = i;
	if( n <= 0 )
		n = 1;
	n = randm( n );

	return g_ls_npc_kind[n];
}

/***************************************************************
* ��󥹥����η���̾���֤�
* char mjr : ��󥹥����Υ᥸�㡼�δ�ʸ��
* return : ��󥹥����η���̾
***************************************************************/

char	*get_mnstr_mjr_name( char mjr )
{
	switch( mjr ){
	case FACE_MJR_MNSTR_GOD:
		return MSG_MNSTR_MJR_NAME_GOD;
	case FACE_MJR_MNSTR_DRAGON:
		return MSG_MNSTR_MJR_NAME_DRAGON;
	case FACE_MJR_MNSTR_ILLUSORY:
		return MSG_MNSTR_MJR_NAME_ILLUSORY;
	case FACE_MJR_MNSTR_FAIRY:
		return MSG_MNSTR_MJR_NAME_FAIRY;
	case FACE_MJR_MNSTR_ELEMENTAL:
		return MSG_MNSTR_MJR_NAME_ELEMENTAL;
	case FACE_MJR_MNSTR_PLANT:
		return MSG_MNSTR_MJR_NAME_PLANT;
	case FACE_MJR_MNSTR_ANIMAL:
		return MSG_MNSTR_MJR_NAME_ANIMAL;
	case FACE_MJR_MNSTR_INSECT:
		return MSG_MNSTR_MJR_NAME_INSECT;
	case FACE_MJR_MNSTR_HUMAN:
		return MSG_MNSTR_MJR_NAME_HUMAN;
	case FACE_MJR_MNSTR_HYBRID:
		return MSG_MNSTR_MJR_NAME_HYBRID;
	case FACE_MJR_MNSTR_GIANT:
		return MSG_MNSTR_MJR_NAME_GIANT;
	case FACE_MJR_MNSTR_HUGE:
		return MSG_MNSTR_MJR_NAME_HUGE;
	case FACE_MJR_MNSTR_AQUATIC:
		return MSG_MNSTR_MJR_NAME_AQUATIC;
	case FACE_MJR_MNSTR_MAGICAL:
		return MSG_MNSTR_MJR_NAME_MAGICAL;
	case FACE_MJR_MNSTR_COMPOUND:
		return MSG_MNSTR_MJR_NAME_COMPOUND;
	case FACE_MJR_MNSTR_UNDEAD:
		return MSG_MNSTR_MJR_NAME_UNDEAD;
	case FACE_MJR_MNSTR_EVIL:
		return MSG_MNSTR_MJR_NAME_EVIL;
	case FACE_MJR_MNSTR_EVIL_BEAST:
		return MSG_MNSTR_MJR_NAME_EVIL_BEAST;
	case FACE_MJR_MNSTR_DEVIL:
		return MSG_MNSTR_MJR_NAME_DEVIL;
	}

	return MSG_MNSTR_MJR_NAME_UNKNOWN;
}

/***************************************************************
* ��󥹥�����̾����ǡ������ơ��֥뤫�鸡��
* mnstr_kind_t mnstr_kind : ��󥹥����μ���
* return : ��󥹥�����̾��
***************************************************************/

char	*get_mnstr_name( mnstr_kind_t mnstr_kind )
{
	mnstr_tab_t	*tab;

	tab = get_mnstr_tab( mnstr_kind, 0 );
	if( tab == NULL )
		return MSG_MNSTR_UNKNOWN;

	return tab->name;
}

/***************************************************************
* ��󥹥����Υǡ������ơ��֥�򸡺�
* mnstr_kind_t mnstr_kind : ��󥹥����μ���
* long dun_lev : ���󥸥��γ���
* return : ��󥹥����Υǡ������ơ��֥�
***************************************************************/

mnstr_tab_t	*get_mnstr_tab( mnstr_kind_t mnstr_kind, long dun_lev )
{
	mnstr_tab_t	*tab;
	long	i, n;

	tab = NULL;
	n = 0;
	for( i = 0; mnstr_tab[i].mnstr_kind != MNSTR_KIND_NULL; i++ ){
		if( mnstr_tab[i].mnstr_kind != mnstr_kind )
			continue;

		n++;
		if( per_randm( n ) )
			tab = &(mnstr_tab[i]);
	}

	return tab;
}

/***************************************************************
* ��󥹥����Υǡ������ơ��֥�������˸���
* long dun_lev : ���󥸥��γ���
* return : ��󥹥����Υǡ������ơ��֥�
***************************************************************/

mnstr_tab_t	*get_mnstr_tab_rand( long dun_lev )
{
	return get_mnstr_tab_rand_sub( dun_lev, FALSE );
}

/***************************************************************
* ��󥹥����Υǡ������ơ��֥�������˸���(���ػ��ꤢ��)
* long dun_lev : ���󥸥��γ���
* return : ��󥹥����Υǡ������ơ��֥�
***************************************************************/

mnstr_tab_t	*get_mnstr_tab_rand_dun_lev( long dun_lev )
{
	return get_mnstr_tab_rand_sub( dun_lev, TRUE );
}

/***************************************************************
* ��󥹥����Υǡ������ơ��֥�������˸������붦�̽���
* long dun_lev : ���󥸥��γ���
* bool_t flg_no_chk_max : ����γ��ؤ�겼�������оݤȤ���
* return : ��󥹥����Υǡ������ơ��֥�
***************************************************************/

mnstr_tab_t	*get_mnstr_tab_rand_sub(
	long dun_lev, bool_t flg_no_chk_max
)
{
	mnstr_kind_t	kind;
	long	loop_lev, lev_offset;
	long	n;
	long	i;

	loop_lev = get_mnstr_lev_tab_max();
	lev_offset = 0;
	for( i = 0; i < LOOP_MAX_10000; i++ ){
		if( (lev_offset + loop_lev) < labs( dun_lev ) )
			lev_offset += loop_lev;
		else
			break;
	}

	kind = MNSTR_KIND_NULL;
	n = 0;
	for( i = 0; i < LOOP_MAX_10000; i++ ){
		mnstr_lev_tab_t	*lev_p;

		lev_p = &(mnstr_lev_tab[i]);

		if( lev_p->kind == MNSTR_KIND_NULL )
			break;

		if( (lev_p->min_lev + lev_offset) > labs( dun_lev ) )
			continue;
		if( (lev_p->max_lev + lev_offset) < labs( dun_lev ) )
			if( !flg_no_chk_max )
				continue;

		n++;
		if( per_randm( n ) ){
			kind = lev_p->kind;
		}
	}

	return get_mnstr_tab( kind, dun_lev );
}

/***************************************************************
* ͧ��Ū�ʥ�󥹥����Υǡ������ơ��֥�������˸���
* return : ��󥹥����Υǡ������ơ��֥�
***************************************************************/

mnstr_tab_t	*get_mnstr_tab_friendly( void )
{
	mnstr_tab_t	*tab;
	long	i, n;

	tab = NULL;
	n = 0;
	for( i = 0; mnstr_tab[i].mnstr_kind != MNSTR_KIND_NULL; i++ ){
		if( mnstr_tab[i].attitude != ATTITUDE_FRIENDLY )
			continue;

		n++;
		if( per_randm( n ) )
			tab = &(mnstr_tab[i]);
	}

	return tab;
}

/***************************************************************
* ���ν�̱�Υǡ������ơ��֥�������˸���
* return : ���ν�̱�Υǡ������ơ��֥�
***************************************************************/

mnstr_tab_t	*get_towner_tab_rand( void )
{
	long	n, sum;
	long	i, max_i;

	max_i = sizeof( towner_tab ) / sizeof( towner_tab[0] );

	sum = 0;
	for( i = 0; i < max_i; i++ ){
		if( towner_tab[i].kind == MNSTR_KIND_NULL )
			break;

		sum += towner_tab[i].ratio;
	}

	n = randm( sum );

	sum = 0;
	for( i = 0; i < max_i; i++ ){
		if( towner_tab[i].kind == MNSTR_KIND_NULL )
			break;

		sum += towner_tab[i].ratio;

		if( n < sum )
			break;
	}
	if( i >= max_i )
		return NULL;

	return get_mnstr_tab( towner_tab[i].kind, 0 );
}

/***************************************************************
* ��󥹥����νи������ơ��֥�Υ롼�פ���ޤǤκ��糬���򸡺�
* return : ���糬��
***************************************************************/

long	get_mnstr_lev_tab_max( void )
{
	long	max_lev;
	long	i;

	max_lev = 0;
	for( i = 0; i < LOOP_MAX_10000; i++ ){
		if( mnstr_lev_tab[i].kind == MNSTR_KIND_NULL )
			break;

		max_lev = mnstr_lev_tab[i].max_lev;
	}

	return max_lev;
}

/***************************************************************
* ��󥹥����νи������ơ��֥�򸡺�
* mnstr_kind_t mnstr_kind : ��󥹥����μ���
* long dun_lev : ���󥸥��γ���
* return : ��󥹥����νи������ơ��֥�
***************************************************************/

mnstr_lev_tab_t	*get_mnstr_lev_tab( mnstr_kind_t mnstr_kind, long dun_lev )
{
	mnstr_lev_tab_t	*tab;
	long	i, max_i, n;

	if( mnstr_kind == MNSTR_KIND_NULL )
		return NULL;

	tab = NULL;
	n = 0;
	max_i = sizeof( mnstr_lev_tab ) / sizeof( mnstr_lev_tab[0] );
	for( i = 0; i < max_i; i++ ){
		mnstr_lev_tab_t	*p;

		p = &(mnstr_lev_tab[i]);
		if( p->kind == MNSTR_KIND_NULL )
			break;

		if( p->kind != mnstr_kind )
			continue;

		/* ���󥸥���٥�˥ޥå����ʤ��ä����ΰ� */
		n++;
		if( per_randm( n ) )
			tab = p;

		if( p->min_lev > labs( dun_lev ) )
			continue;
		if( p->max_lev < labs( dun_lev ) )
			continue;

		/* ���󥸥���٥�˥ޥå����� */
		tab = p;
		break;
	}

	return tab;
}

/***************************************************************
* ��󥹥����Υꥹ�Ȥ�����
* mnstr_t *ls : ��󥹥����Υꥹ��
* mnstr_t *p : ��󥹥���
***************************************************************/

void	ins_ls_mnstr( mnstr_t *ls, mnstr_t *p )
{
	if( ls == NULL )
		return;
	if( ls->prev == NULL )
		return;
	if( ls->next == NULL )
		return;
	if( p == NULL )
		return;
	if( p->prev == NULL )
		return;
	if( p->next == NULL )
		return;

	p->next->prev = p->prev;
	p->prev->next = p->next;

	p->prev = ls->prev;
	p->next = ls;

	ls->prev->next = p;
	ls->prev = p;
}

/***************************************************************
* ��󥹥������ݤ������ηи��ͤ�׻�
* ��󥹥����Υ�٥�Υ롼�פ��θ����
* mnstr_kind_t mnstr_kind : ��󥹥����μ���
* long dun_lev : ���󥸥��γ���
* return : �и���
***************************************************************/

long	calc_mnstr_exp( mnstr_kind_t mnstr_kind, long dun_lev )
{
	long	dun_lev_max, dun_lev_mod;
	long	lev_mul;
	long	exp_max, exp_mod, exp;

	dun_lev = labs( dun_lev );
	dun_lev_max = labs( get_mnstr_lev_tab_max() );
	dun_lev_mod = dun_lev % dun_lev_max;

	lev_mul = dun_lev / dun_lev_max;
	if( lev_mul < 0 )
		lev_mul = 0;

	exp_max = calc_mnstr_exp_sub( mnstr_kind, dun_lev_max );
	exp_mod = calc_mnstr_exp_sub( mnstr_kind, dun_lev_mod );
	exp = (exp_max * lev_mul) + exp_mod;

	return exp;
}

/***************************************************************
* ��󥹥������ݤ������ηи��ͤ�׻�
* mnstr_kind_t mnstr_kind : ��󥹥����μ���
* long dun_lev : ���󥸥��γ���
* return : �и���
***************************************************************/

long	calc_mnstr_exp_sub( mnstr_kind_t mnstr_kind, long dun_lev )
{
	mnstr_tab_t	*tab;
	long	lev;
	long	exp;

	tab = NULL;
	if( mnstr_kind != MNSTR_KIND_NULL )
		tab = get_mnstr_tab( mnstr_kind, dun_lev );

	/* �µܤγ��ؤ���׻� */

	lev = labs( dun_lev ) * RATE_LEV_PER_DUN_LEV / _100_PERCENT;

	exp = calc_need_exp( lev, ABL_KIND_HP );
	exp -= calc_need_exp( lev - 1, ABL_KIND_HP );

	/* ��󥹥�����ɤ�ݤ��ȥ��С��Υ�٥뤬�夬�뤫���ܰ� */

	exp /= EXP_NEED_KILL_MNSTR_N;

	/* ���� */

	if( tab != NULL )
		exp += exp * tab->exp / _100_PERCENT;

	/* ���ο������� */

	if( tab != NULL ){
		exp *= calc_mnstr_group_rate( tab->group );
		exp /= _100_PERCENT;
	}

	/**/

	if( exp < 1 )
		exp = 1;

	exp *= MBR_MAX_N;
	exp = exp * _100_PERCENT / ABL_RATE_MAX_N;

	return exp;
}

/***************************************************************
* ��󥹥������ơ��֥뤫��ºݤΥ�󥹥����Υ�٥��׻�
* long dun_lev : ���󥸥��γ���
* abl_kind_t k : ǽ���ͤμ���
* mnstr_tab_t *tab : ��󥹥������ơ��֥�
* return : ��٥�
***************************************************************/

long	calc_mnstr_abl_lev( long dun_lev, abl_kind_t k, mnstr_tab_t *tab )
{
	rate_t	rate;
	long	lev;

	if( tab == NULL )
		return 0;

	rate = tab->abl_lev_rate[k];

	lev = labs( dun_lev ) * RATE_LEV_PER_DUN_LEV / _100_PERCENT;
	lev = lev * rate / _100_PERCENT;

	/* ���ο��ǥ�٥������ */
	lev = lev * calc_mnstr_group_rate( tab->group ) / _100_PERCENT;

	if( lev < 0 )
		lev = 0;
	if( lev < 1 )
		if( rate > 0 )
			lev = 1;

	return lev;
}

/***************************************************************
* ��󥹥����η���ζ�����׻�
* long group_n : ����ο�
* return : ����ζ�����Ψ
***************************************************************/

rate_t	calc_mnstr_group_rate( long group_n )
{
	long	group_denomi;
	rate_t	group_rate;

	if( group_n < 1 )
		group_n = 1;

	group_denomi = (group_n + GROUP_RATE_DENOMINATOR - 1)
			/ GROUP_RATE_DENOMINATOR;
	group_rate = (_100_PERCENT - GROUP_RATE_BASE) / group_denomi
			+ GROUP_RATE_BASE;

	return group_rate;
}

/***************************************************************
* ��󥹥����ν�����׻�
* long dun_lev : ���󥸥��γ���
* rate_t rate : ���äƤ���Ψ
* return : ��󥹥����ν����
***************************************************************/

gold_t	calc_mnstr_gold( long dun_lev, rate_t rate )
{
	gold_t	gold;

	gold = labs( dun_lev );
	gold *= MNSTR_GOLD_MUL_N;
	gold += MNSTR_GOLD_ADD_N;
	gold = gold * rate / _100_PERCENT;

	return gold;
}

/***************************************************************
* ��󥹥���������κ�ɸ�ذ�ư��ǽ��Ĵ�٤�
* mnstr_tab_t *tab : ��󥹥������ơ��֥�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��ư��ǽ��?
***************************************************************/

bool_t	can_move_mnstr_tab( mnstr_tab_t *tab, long x, long y )
{
	if( tab == NULL )
		return FALSE;

	return can_move_chr_pos( NULL, x, y, tab->dx, tab->dy );
}

/***************************************************************
* ����κ�ɸ�Υ�󥹥����򸡺�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr( long x, long y )
{
	dun_t	*dun = get_dun();
	mnstr_t	*head, *p, *pp;
	pet_t	*pet;

	if( !clip_pos( x, y ) )
		return NULL;

	if( dun->map.chr.mjr[y][x] == FACE_MJR_NULL )
		return NULL;

	p = dun->map.chr_p[y][x];
	if( (p != NULL) && (p->kind == CHR_KIND_MNSTR) )
		return p;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

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

	pet = get_pet( x, y );
	if( pet != NULL )
		return pet;

	/* �饹�ܥ���Ĵ�٤� */

	if( chk_xx_pos( x, y ) )
		return get_last_boss( LAST_BOSS_KIND_XX );

	return NULL;
}

/***************************************************************
* ����κ�ɸ�˰��ֶᤤ��󥹥����򸡺�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_nearest( long x, long y )
{
	mnstr_t	*head, *p, *pp, *ret_p;
	long	min_r, tmp_r;
	long	n;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		if( !chk_flg( pp->flg_map, FLG_MAP_CHR_FIND ) )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( pp->attitude != ATTITUDE_ENEMY )
			continue;

		tmp_r = labs( pp->x - x ) + labs( pp->y - y );
		if( tmp_r < min_r ){
			n = 0;
			min_r = tmp_r;
		} else if( tmp_r == min_r ){
			n++;
			if( randm( n ) != 0 )
				continue;
		} else {
			continue;
		}

		ret_p = pp;
	}

	return ret_p;
}

/***************************************************************
* ����κ�ɸ�����Ū�ᤤ��󥹥����򸡺�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_near( long x, long y )
{
	mnstr_t	*head, *p, *pp, *ret_p;
	long	min_r, tmp_r;
	long	n;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		if( !chk_flg( pp->flg_map, FLG_MAP_CHR_FIND ) )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( pp->attitude != ATTITUDE_ENEMY )
			continue;

		tmp_r = labs( pp->x - x ) + labs( pp->y - y );
		if( tmp_r < min_r ){
			n = 0;
			min_r = tmp_r;
		} else if( (tmp_r - min_r) <= MNSTR_NEAR_R ){
			n++;
			if( randm( n ) != 0 )
				continue;
		} else {
			continue;
		}

		ret_p = pp;
	}

	return ret_p;
}

/***************************************************************
* ���С��˶ᤤ��󥹥�����ѡ��ƥ����ʬ��Ū�ˤʤ��ͤ˸���
* mbr_t *mbr : ���С�
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_disperse( mbr_t *mbr )
{
	mnstr_t	*head, *p, *pp, *ret_p;
	long	min_r, tmp_r;
	long	n;
	long	x, y;

	x = mbr->x;
	y = mbr->y;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	n = 0;
	ret_p = NULL;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		if( !chk_flg( pp->flg_map, FLG_MAP_CHR_FIND ) )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( pp->attitude != ATTITUDE_ENEMY )
			continue;

		tmp_r = labs( pp->x - x ) + labs( pp->y - y );
		if( tmp_r < min_r ){
			if( already_mark_mnstr( pp, mbr ) )
				continue;
			n = 0;
			min_r = tmp_r;
		} else if( tmp_r == min_r ){
			if( already_mark_mnstr( pp, mbr ) )
				continue;
			n++;
			if( randm( n ) != 0 )
				continue;
		} else {
			continue;
		}

		ret_p = pp;
	}

	return ret_p;
}

/***************************************************************
* 1 �� HP �����ʤ���󥹥����򸡺�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_hp_min( long x, long y )
{
	return get_mnstr_hp_mp_min_max( x, y, TRUE, -1 );
}

/***************************************************************
* 1 �� HP ��¿����󥹥����򸡺�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_hp_max( long x, long y )
{
	return get_mnstr_hp_mp_min_max( x, y, TRUE, +1 );
}

/***************************************************************
* 1 �� MP �����ʤ���󥹥����򸡺�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_mp_min( long x, long y )
{
	return get_mnstr_hp_mp_min_max( x, y, FALSE, -1 );
}

/***************************************************************
* 1 �� MP ��¿����󥹥����򸡺�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_mp_max( long x, long y )
{
	return get_mnstr_hp_mp_min_max( x, y, FALSE, +1 );
}

/***************************************************************
* 1 ��(HP/MP)��(¿��/���ʤ�)��󥹥����򸡺�
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_hp_mp_min_max(
	long x, long y, bool_t flg_hp, long min_max
)
{
	mnstr_t	*head, *p, *pp, *ret_p;
	long	min_max_n, tmp_n;
	long	n;

	if( min_max >= +1 )
		min_max_n = 0;
	else if( min_max <= -1 )
		min_max_n = 0x7fffffff;
	else
		return NULL;
	n = 0;
	ret_p = NULL;

	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		if( !chk_flg( pp->flg_map, FLG_MAP_CHR_FIND ) )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( pp->attitude != ATTITUDE_ENEMY )
			continue;

		if( flg_hp )
			tmp_n = pp->abl.hp.n;
		else
			tmp_n = pp->abl.mp.n;

		if( tmp_n == min_max_n ){
			n++;
			if( randm( n ) != 0 )
				continue;
		} else if( (min_max >= +1) && (tmp_n > min_max_n) ){
			min_max_n = tmp_n;
			n = 1;
		} else if( (min_max <= -1) && (tmp_n < min_max_n) ){
			min_max_n = tmp_n;
			n = 1;
		} else {
			continue;
		}

		ret_p = pp;
	}

	return ret_p;
}

/***************************************************************
* ȯ������Ƥ����󥹥����������˸���
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_randm( long x, long y )
{
	mnstr_t	*head, *p, *pp, *ret_p;
	long	n;

	ret_p = NULL;
	n = 0;
	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		if( !chk_flg( pp->flg_map, FLG_MAP_CHR_FIND ) )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( pp->attitude != ATTITUDE_ENEMY )
			continue;

		n++;
		if( randm( n ) == 0 )
			ret_p = pp;
	}

	return ret_p;
}

/***************************************************************
* ������С��ʳ��������󥹥����򥿡����åȤ��Ƥ��뤫Ĵ�٤�
* mnstr_t *mnstr : ��󥹥���
* mbr_t *mbr : ���С�
* return : �������åȤ��Ƥ��뤫?
***************************************************************/

bool_t	already_mark_mnstr( mnstr_t *mnstr, mbr_t *mbr )
{
	party_t	*pty;
	long	i;

	pty = get_party();

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( pty->mbr[i] == mbr )
			continue;

		if( pty->mbr[i]->trgt.p == ((void *)mnstr) )
			return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ȯ������Ƥ����󥹥����������˸�����
* �̥С������(̤����)
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥���
***************************************************************/

mnstr_t	*get_mnstr_randm2( long x, long y )
{
	mnstr_t	*head, *p, *pp;
	long	n, max_n, max_n2;

	max_n = 0;
	max_n2 = 0;
	head = &mnstr_used;
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		if( !chk_flg( pp->flg_map, FLG_MAP_CHR_FIND ) )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		max_n++;

		if( (labs( pp->x - x ) < 1) && (labs( pp->y - y ) < 1) )
			max_n2++;
	}
	if( max_n <= 0 )
		return NULL;

	if( max_n2 == 0 ){
		n = randm( max_n ) + 1;
		head = &mnstr_used;
		for( p = head->next->next; p != NULL; p = p->next ){
			pp = p->prev;
			if( pp == head )
				break;

			if( !chk_flg( pp->flg_map, FLG_MAP_CHR_FIND ) )
				continue;
			if( chk_flg_or( pp->stat,
					FLG_STAT_NOT_EXIST
					| FLG_STAT_DEAD ) ){
				continue;
			}

			n--;
			if( n == 0 )
				return pp;
		}
	} else {
		n = randm( max_n2 ) + 1;
		head = &mnstr_used;
		for( p = head->next->next; p != NULL; p = p->next ){
			pp = p->prev;
			if( pp == head )
				break;

			if( !chk_flg( pp->flg_map, FLG_MAP_CHR_FIND ) )
				continue;
			if( chk_flg_or( pp->stat,
					FLG_STAT_NOT_EXIST
					| FLG_STAT_DEAD ) ){
				continue;
			}

			if( (labs( pp->x - x ) < 1)
					&& (labs( pp->y - y ) < 1) ){
				n--;
				if( n == 0 )
					return pp;
			}
		}
	}

	return NULL;
}

/***************************************************************
* ��󥹥�������֤������˸���
* mnstr_t *p : ��󥹥���
* long x : X ��ɸ
* long y : Y ��ɸ
* return : ��󥹥��������
***************************************************************/

chr_t	*get_mnstr_friend( mnstr_t *p, long x, long y )
{
	if( p == NULL )
		return get_mnstr_hp_min( x, y );

	if( p->attitude == ATTITUDE_ENEMY )
		return get_mnstr_hp_min( x, y );

	return get_mbr_hp_min();
}

/***************************************************************
* ��󥹥����δ�ʸ���������򸡺�
* char mjr : �᥸�㡼�δ�ʸ��
* char mnr : �ޥ��ʡ��δ�ʸ��
* return : ��󥹥����μ���
***************************************************************/

mnstr_kind_t	get_mnstr_kind_from_face( char mjr, char mnr )
{
	long	i;
	long	n;
	mnstr_kind_t	k;

	n = 0;
	k = MNSTR_KIND_NULL;
	for( i = 0; mnstr_tab[i].mnstr_kind != MNSTR_KIND_NULL; i++ ){
		if( mnstr_tab[i].face_mjr != mjr )
			continue;
		if( mnstr_tab[i].face_mnr != mnr )
			continue;

		n++;
		if( per_randm( n ) )
			k = mnstr_tab[i].mnstr_kind;
	}

	return k;
}

/***************************************************************
* �饹�ܥ����֤�
* last_boss_kind_t kind : �饹�ܥ��μ���
* return : �饹�ܥ�
***************************************************************/

mnstr_t	*get_last_boss( last_boss_kind_t kind )
{
	return g_last_boss[kind];
}

/***************************************************************
* ��󥹥����γ�����ƺѥ��꡼���ꥹ�Ȥ��֤�
* return : ��󥹥����Υ��꡼���ꥹ��
***************************************************************/

mnstr_t	*get_mnstr_used( void )
{
	return &mnstr_used;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_mnstr_c( void )
{
	check_memory( check_memory_mnstr_c_mnstr_buf,
			"mnstr.c: mnstr_buf" );
	check_memory( check_memory_mnstr_c_mnstr_used,
			"mnstr.c: mnstr_used" );
	check_memory( check_memory_mnstr_c_mnstr_free,
			"mnstr.c: mnstr_free" );
	check_memory( check_memory_mnstr_c_g_last_boss,
			"mnstr.c: g_last_boss" );
}
