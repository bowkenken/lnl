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
* $Id: request.c,v 1.121 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ���ΰ���
***************************************************************/

#define	REQUEST_C
#include	"inc.h"

/***************************************************************/

/* �����ǥХå����뤫? */
#if	1
# define	FLG_DEBUG_REQUEST	1
#else
# define	FLG_DEBUG_REQUEST	0
#endif

/* ����Υ�˥塼���ꥹ�ȤΥڡ���������ι��ܿ� */
#define	MENU_REQUEST_N_PER_PAGE	10

/* �����ʿ�Ѵ��� */
#define	REQUEST_RARE_GOODS_AVE_LIMIT	7
#define	REQUEST_TAME_MNSTR_AVE_LIMIT	7
#define	REQUEST_RESCUE_AVE_LIMIT	7
#define	REQUEST_TOUR_GUIDE_AVE_LIMIT	10
#define	REQUEST_EXTERMINATE_AVE_LIMIT	10
#define	REQUEST_REVENGE_AVE_LIMIT	12
#define	REQUEST_WANTED_CRIMINAL_AVE_LIMIT	12

/* ��ñ�ʰ���γ��� */
#define	REQUEST_DUN_MIN_LEV_EASY	1
#define	REQUEST_DUN_MAX_LEV_EASY	50
/* ���̤ΰ���γ��� */
#define	REQUEST_DUN_MIN_LEV_NORMAL	10
#define	REQUEST_DUN_MAX_LEV_NORMAL	50
/* ����γ������ϰ� */
#define	REQUEST_DUN_RANGE_LEV	2
/* ��ã�����˲ä������γ��� */
#define	REQUEST_DUN_ADD_LEV	1

/* NPC �������������Ψ */
#define	REQUEST_NPC_CONTRACT_RATE	20

/* õ�����륢���ƥ���󥹥��������Ψ */
#define	REQUEST_RARE_GOODS_DROP_RATE	((rate_t)30)

/* ����ץ��ΰ���Υ�󥹥�����ʿ�ѿ� */
#define	REQUEST_TAME_MNSTR_MNSTR_AVE_N	4
/* �Ѹ�����ΰ�����ݤ��٤���󥹥�����ʿ�ѿ� */
#define	REQUEST_TOUR_GUIDE_MNSTR_AVE_N	4
/* ��󥹥����༣�ΰ�����ݤ��٤���󥹥�����ʿ�ѿ� */
#define	REQUEST_EXTERMINATE_MNSTR_AVE_N	4

/* ¾�ΰ���ꥹ�Ȥ򸫤���μ���� */
#define	REQUEST_REFRESH_PRIZE	((gold_t)(1 * MBR_MAX_N))

/* ����̾��ɽ�����ʸ���� */
#define	REQUEST_NAME_MIN_LEN	14

/***************************************************************
* ������󽷤ζ�ȷи��ͤ�Ψ
***************************************************************/

#define	REQUEST_RARE_GOODS_GOLD_RATE	((rate_t)2000)
#define	REQUEST_RARE_GOODS_EXP_RATE	((rate_t)400)

#define	REQUEST_TAME_MNSTR_GOLD_RATE	((rate_t)1000)
#define	REQUEST_TAME_MNSTR_EXP_RATE	((rate_t)400)

#define	REQUEST_RESCUE_GOLD_RATE	((rate_t)2000)
#define	REQUEST_RESCUE_EXP_RATE	((rate_t)800)

#define	REQUEST_TOUR_GUIDE_GOLD_RATE	((rate_t)3000)
#define	REQUEST_TOUR_GUIDE_EXP_RATE	((rate_t)400)

#define	REQUEST_EXTERMINATE_GOLD_RATE	((rate_t)2000)
#define	REQUEST_EXTERMINATE_EXP_RATE	((rate_t)800)

#define	REQUEST_REVENGE_GOLD_RATE	((rate_t)1000)
#define	REQUEST_REVENGE_EXP_RATE	((rate_t)1200)

#define	REQUEST_WANTED_CRIMINAL_GOLD_RATE	((rate_t)3000)
#define	REQUEST_WANTED_CRIMINAL_EXP_RATE	((rate_t)800)

#define	REQUEST_PENALTY_RATE	((rate_t)10)

/***************************************************************
* ������󽷤Υ����ƥ�
***************************************************************/

scroll_kind_t	ls_reward_scroll[] = {
	SCROLL_KIND_POW_UP_WPN_HIT,
	SCROLL_KIND_POW_UP_WPN_CRTCL,
	SCROLL_KIND_POW_UP_WPN_DAM,
	SCROLL_KIND_POW_UP_ARMOR_DEF,
	SCROLL_KIND_POW_UP_ARMOR_CRTCL,
	SCROLL_KIND_POW_UP_ARMOR_AC,

	SCROLL_KIND_NULL,
};
check_memory_def( check_memory_request_c_ls_reward_scroll )

/***************************************************************
* �����Х��ѿ�
***************************************************************/

/* ����Υǡ������ꥹ�� */
check_memory_def( check_memory_request_c_g_request_pre )
static request_t	g_request[REQUEST_MAX_N];
check_memory_def( check_memory_request_c_g_request )

/* ����Υ�˥塼 */
static menu_t	ls_menu_request[1 + REQUEST_MAX_N * 2];
check_memory_def( check_memory_request_c_ls_menu_request )

/***************************************************************
* ����Υơ��֥�
***************************************************************/

#include	"request-tab.h"

/***************************************************************
* ����ν����
***************************************************************/

void	init_request( void )
{
	long	i;

	for( i = 0; i < REQUEST_MAX_N; i++ )
		g_request[i].kind = REQUEST_KIND_NULL;
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_request( void )
{
}

/***************************************************************
* ����������Ϥ�
***************************************************************/

void	make_request_all( void )
{
	long	request_n, request_max_n;
	long	i;

	request_n = get_request_n();
	request_max_n = roll_dice( REQUEST_AVE_N, TRUE );
	for( i = request_n; i < request_max_n; i++ )
		make_request_randm();

	chk_request_limit();
	chk_request_npc_contract();
}

/***************************************************************
* ������������Ϥ�
* return : ����
***************************************************************/

request_t	*make_request_randm( void )
{
	request_t	*req;

	req = alloc_request();
	if( req == NULL )
		return NULL;

	switch( randm( REQUEST_KIND_MAX_N ) ){
	case REQUEST_KIND_NULL:
		break;
	case REQUEST_KIND_RARE_GOODS:
		if( make_request_rare_goods( req ) != NULL )
			return req;
		break;
	case REQUEST_KIND_TAME_MNSTR:
		if( make_request_tame_mnstr( req ) != NULL )
			return req;
		break;
	case REQUEST_KIND_RESCUE:
		if( make_request_rescue( req ) != NULL )
			return req;
		break;
	case REQUEST_KIND_TOUR_GUIDE:
		if( make_request_tour_guide( req ) != NULL )
			return req;
		break;
	case REQUEST_KIND_EXTERMINATE:
		if( make_request_exterminate( req ) != NULL )
			return req;
		break;
	case REQUEST_KIND_REVENGE:
		if( make_request_revenge( req ) != NULL )
			return req;
		break;
	case REQUEST_KIND_WANTED_CRIMINAL:
		if( make_request_wanted_criminal( req ) != NULL )
			return req;
		break;
	case REQUEST_KIND_MAX_N:
		break;
	}

	free_request( req );
	return NULL;
}

/***************************************************************
* �����ƥ�õ���ΰ�����Ϥ�
* request_t *req : ������Ϥ���
* return : ����
***************************************************************/

request_t	*make_request_rare_goods( request_t *req )
{
	long	dun_lev, dun_max_lev;
	mnstr_tab_t	*tab;
	mnstr_lev_tab_t	*lev_tab;
	long	limit;

	if( req == NULL )
		return NULL;

	dun_max_lev = get_request_dun_max_lev_easy();
	dun_lev = REQUEST_DUN_MIN_LEV_EASY;
	dun_lev += randm( dun_max_lev - REQUEST_DUN_MIN_LEV_EASY );

	tab = get_mnstr_tab_rand( -dun_lev );
	if( tab == NULL )
		return NULL;
	lev_tab = get_mnstr_lev_tab( tab->mnstr_kind, dun_lev );
	if( lev_tab == NULL )
		return NULL;

	req->flg_mnstr_is_npc = FALSE;
	req->mnstr_kind = tab->mnstr_kind;
	req->idx_mnstr_name = -1;

	req->dun_min_lev = -lev_tab->min_lev;
	req->dun_max_lev = -min_l( lev_tab->max_lev, dun_max_lev );
	req->dun_true_lev = req->dun_max_lev;

	limit = roll_dice( REQUEST_RARE_GOODS_AVE_LIMIT, TRUE );
	req->limit = get_game_day() + limit;

	if( per_randm( 2 ) ){
		req->client_sex = FEMALE;
	} else {
		req->client_sex = MALE;
	}

	req->prize = calc_mnstr_gold( labs( req->dun_max_lev ),
			REQUEST_RARE_GOODS_GOLD_RATE );
	req->exp = calc_mnstr_exp( req->mnstr_kind,
			labs( req->dun_max_lev ) );
	req->exp *= REQUEST_RARE_GOODS_EXP_RATE;
	req->exp /= _100_PERCENT;

	/**/
	req->kind = REQUEST_KIND_RARE_GOODS;

	req->idx_fmt = get_ls_n_msg_idx_randm( g_rare_goods_tab );
	set_request_msg( req );
	set_request_heading( req );

	return req;
}

/***************************************************************
* ����ץ��ΰ�����Ϥ�
* request_t *req : ������Ϥ���
* return : ����
***************************************************************/

request_t	*make_request_tame_mnstr( request_t *req )
{
	mnstr_tab_t	*tab;
	long	limit;
	long	dun_max_lev;

	if( req == NULL )
		return NULL;

	dun_max_lev = get_request_dun_max_lev_easy();
	set_request_dun_lev( req,
			REQUEST_DUN_MIN_LEV_EASY,
			dun_max_lev,
			REQUEST_DUN_RANGE_LEV );

	tab = get_mnstr_tab_friendly();
	if( tab == NULL )
		return NULL;

	req->flg_mnstr_is_npc = FALSE;
	req->mnstr_kind = tab->mnstr_kind;
	req->idx_mnstr_name = -1;
	req->mnstr_n = REQUEST_TAME_MNSTR_MNSTR_AVE_N;
	req->mnstr_n = roll_dice( req->mnstr_n, TRUE );

	limit = roll_dice( REQUEST_TAME_MNSTR_AVE_LIMIT, TRUE );
	req->limit = get_game_day() + limit;

	if( per_randm( 2 ) ){
		req->client_sex = FEMALE;
	} else {
		req->client_sex = MALE;
	}

	req->prize = calc_mnstr_gold( labs( req->dun_max_lev ),
			REQUEST_TAME_MNSTR_GOLD_RATE );
	req->exp = calc_mnstr_exp( MNSTR_KIND_NULL,
			labs( req->dun_max_lev ) );
	req->exp *= REQUEST_TAME_MNSTR_EXP_RATE;
	req->exp /= _100_PERCENT;

	/**/
	req->kind = REQUEST_KIND_TAME_MNSTR;

	req->idx_fmt = get_ls_n_msg_idx_randm( g_tame_mnstr_tab );
	set_request_msg( req );
	set_request_heading( req );

	return req;
}

/***************************************************************
* �߽��ΰ�����Ϥ�
* request_t *req : ������Ϥ���
* return : ����
***************************************************************/

request_t	*make_request_rescue( request_t *req )
{
	long	limit;
	long	dun_max_lev;

	if( req == NULL )
		return NULL;

	dun_max_lev = get_request_dun_max_lev_normal();
	set_request_dun_lev( req,
			REQUEST_DUN_MIN_LEV_NORMAL,
			dun_max_lev,
			REQUEST_DUN_RANGE_LEV );

	limit = roll_dice( REQUEST_RESCUE_AVE_LIMIT, TRUE );
	req->limit = get_game_day() + limit;

	if( per_randm( 2 ) ){
		req->client_sex = FEMALE;
	} else {
		req->client_sex = MALE;
	}
	if( per_randm( 2 ) ){
		req->rescue_trgt_sex = FEMALE;
	} else {
		req->rescue_trgt_sex = MALE;
	}
	req->rescue_trgt_kind = get_npc_kind_randm();

	req->prize = calc_mnstr_gold( labs( req->dun_max_lev ),
			REQUEST_RESCUE_GOLD_RATE );
	req->exp = calc_mnstr_exp( MNSTR_KIND_NULL,
			labs( req->dun_max_lev ) );
	req->exp *= REQUEST_RESCUE_EXP_RATE;
	req->exp /= _100_PERCENT;

	/**/
	req->kind = REQUEST_KIND_RESCUE;

	req->idx_fmt = get_ls_n_msg_idx_randm( g_rescue_tab );
	set_request_msg( req );
	set_request_heading( req );

	return req;
}

/***************************************************************
* �Ѹ�����ΰ�����Ϥ�
* request_t *req : ������Ϥ���
* return : ����
***************************************************************/

request_t	*make_request_tour_guide( request_t *req )
{
	long	dun_lev;
	mnstr_tab_t	*tab;
	mnstr_lev_tab_t	*lev_tab;
	long	limit;
	long	dun_max_lev;

	if( req == NULL )
		return NULL;

	dun_max_lev = get_request_dun_max_lev_easy();
	dun_lev = REQUEST_DUN_MIN_LEV_EASY;
	dun_lev += randm( dun_max_lev - REQUEST_DUN_MIN_LEV_EASY );

	tab = get_mnstr_tab_rand( -dun_lev );
	if( tab == NULL )
		return NULL;
	lev_tab = get_mnstr_lev_tab( tab->mnstr_kind, dun_lev );
	if( lev_tab == NULL )
		return NULL;

	req->flg_mnstr_is_npc = FALSE;
	req->mnstr_kind = tab->mnstr_kind;
	req->idx_mnstr_name = -1;
	req->mnstr_n = REQUEST_TOUR_GUIDE_MNSTR_AVE_N;
	req->mnstr_n = roll_dice( req->mnstr_n, TRUE );
	req->mnstr_exterminate_n = 0;

	req->dun_min_lev = -lev_tab->min_lev;
	req->dun_max_lev = -min_l( lev_tab->max_lev, dun_max_lev );
	req->dun_true_lev = req->dun_max_lev;

	limit = roll_dice( REQUEST_TOUR_GUIDE_AVE_LIMIT, TRUE );
	req->limit = get_game_day() + limit;

	if( per_randm( 2 ) ){
		req->client_sex = FEMALE;
	} else {
		req->client_sex = MALE;
	}

	req->prize = calc_mnstr_gold( labs( req->dun_max_lev ),
			REQUEST_TOUR_GUIDE_GOLD_RATE );
	req->exp = calc_mnstr_exp( req->mnstr_kind,
			labs( req->dun_max_lev ) );
	req->exp *= REQUEST_TOUR_GUIDE_EXP_RATE;
	req->exp /= _100_PERCENT;

	/**/
	req->kind = REQUEST_KIND_TOUR_GUIDE;

	req->idx_fmt = get_ls_n_msg_idx_randm( g_tour_guide_tab );
	set_request_msg( req );
	set_request_heading( req );

	return req;
}

/***************************************************************
* ��󥹥����༣�ΰ�����Ϥ�
* request_t *req : ������Ϥ���
* return : ����
***************************************************************/

request_t	*make_request_exterminate( request_t *req )
{
	long	dun_lev;
	mnstr_tab_t	*tab;
	mnstr_lev_tab_t	*lev_tab;
	long	limit;
	long	dun_max_lev;

	if( req == NULL )
		return NULL;

	dun_max_lev = get_request_dun_max_lev_normal();
	dun_lev = REQUEST_DUN_MIN_LEV_NORMAL;
	dun_lev += randm( dun_max_lev - REQUEST_DUN_MIN_LEV_NORMAL );

	tab = get_mnstr_tab_rand( -dun_lev );
	if( tab == NULL )
		return NULL;
	if( tab->mnstr_kind == MNSTR_KIND_NULL )
		return NULL;
	lev_tab = get_mnstr_lev_tab( tab->mnstr_kind, dun_lev );
	if( lev_tab == NULL )
		return NULL;

	req->flg_mnstr_is_npc = FALSE;
	req->mnstr_kind = tab->mnstr_kind;
	req->idx_mnstr_name = -1;
	req->mnstr_n = REQUEST_EXTERMINATE_MNSTR_AVE_N;
	req->mnstr_n = roll_dice( req->mnstr_n, TRUE );
	req->mnstr_exterminate_n = 0;

	req->dun_min_lev = -lev_tab->min_lev;
	req->dun_max_lev = -min_l( lev_tab->max_lev, dun_max_lev );
	req->dun_true_lev = req->dun_max_lev;

	limit = roll_dice( REQUEST_EXTERMINATE_AVE_LIMIT, TRUE );
	req->limit = get_game_day() + limit;

	if( per_randm( 2 ) ){
		req->client_sex = FEMALE;
	} else {
		req->client_sex = MALE;
	}

	req->prize = calc_mnstr_gold( labs( req->dun_max_lev ),
			REQUEST_EXTERMINATE_GOLD_RATE );
	req->exp = calc_mnstr_exp( req->mnstr_kind,
			labs( req->dun_max_lev ) );
	req->exp *= REQUEST_EXTERMINATE_EXP_RATE;
	req->exp /= _100_PERCENT;

	/**/
	req->kind = REQUEST_KIND_EXTERMINATE;

	req->idx_fmt = get_ls_n_msg_idx_randm( g_exterminate_tab );
	set_request_msg( req );
	set_request_heading( req );

	return req;
}

/***************************************************************
* ��Ƥ���ΰ�����Ϥ�
* request_t *req : ������Ϥ���
* return : ����
***************************************************************/

request_t	*make_request_revenge( request_t *req )
{
	long	limit;
	long	dun_max_lev;

	if( req == NULL )
		return NULL;

	dun_max_lev = get_request_dun_max_lev_normal();
	set_request_dun_lev( req,
			REQUEST_DUN_MIN_LEV_NORMAL,
			dun_max_lev,
			REQUEST_DUN_RANGE_LEV );

	req->flg_mnstr_is_npc = TRUE;
	req->mnstr_kind = get_npc_kind_randm();
	req->idx_mnstr_name = -1;
	req->mnstr_n = 0;
	req->mnstr_exterminate_n = 0;

	limit = roll_dice( REQUEST_REVENGE_AVE_LIMIT, TRUE );
	req->limit = get_game_day() + limit;

	if( per_randm( 2 ) ){
		req->client_sex = FEMALE;
	} else {
		req->client_sex = MALE;
	}
	if( per_randm( 2 ) ){
		req->mnstr_sex = FEMALE;
	} else {
		req->mnstr_sex = MALE;
	}

	req->prize = calc_mnstr_gold( labs( req->dun_max_lev ),
			REQUEST_REVENGE_GOLD_RATE );
	req->exp = calc_mnstr_exp( req->mnstr_kind,
			labs( req->dun_max_lev ) );
	req->exp *= REQUEST_REVENGE_EXP_RATE;
	req->exp /= _100_PERCENT;

	/**/
	req->kind = REQUEST_KIND_REVENGE;

	req->idx_fmt = get_ls_n_msg_idx_randm( g_revenge_tab );
	set_request_msg( req );
	set_request_heading( req );

	return req;
}

/***************************************************************
* �޶��ΰ�����Ϥ�
* request_t *req : ������Ϥ���
* return : ����
***************************************************************/

request_t	*make_request_wanted_criminal( request_t *req )
{
	long	limit;
	long	dun_max_lev;

	if( req == NULL )
		return NULL;

	dun_max_lev = get_request_dun_max_lev_normal();
	set_request_dun_lev( req,
			REQUEST_DUN_MIN_LEV_NORMAL,
			dun_max_lev,
			REQUEST_DUN_RANGE_LEV );

	req->flg_mnstr_is_npc = TRUE;
	req->mnstr_kind = get_npc_kind_randm();
	req->idx_mnstr_name = -1;
	req->mnstr_n = 0;
	req->mnstr_exterminate_n = 0;

	limit = roll_dice( REQUEST_WANTED_CRIMINAL_AVE_LIMIT, TRUE );
	req->limit = get_game_day() + limit;

	if( per_randm( 2 ) ){
		req->client_sex = FEMALE;
	} else {
		req->client_sex = MALE;
	}
	if( per_randm( 2 ) ){
		req->mnstr_sex = FEMALE;
	} else {
		req->mnstr_sex = MALE;
	}

	req->prize = calc_mnstr_gold( labs( req->dun_max_lev ),
			REQUEST_WANTED_CRIMINAL_GOLD_RATE );
	req->exp = calc_mnstr_exp( req->mnstr_kind,
			labs( req->dun_max_lev ) );
	req->exp *= REQUEST_WANTED_CRIMINAL_EXP_RATE;
	req->exp /= _100_PERCENT;

	/**/
	req->kind = REQUEST_KIND_WANTED_CRIMINAL;

	req->idx_fmt = get_ls_n_msg_idx_randm( g_wanted_criminal_tab );
	set_request_msg( req );
	set_request_heading( req );

	return req;
}

/***************************************************************
* ������ NPC ���Ϥ�
* request_t *req : ������Ϥ���
* mnstr_kind_t kind : �����μ���
* bool_t flg_now : ���������Ϥ뤫?(�µ�����Ϥ���)
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	make_client( request_t *req, mnstr_kind_t kind, bool_t flg_now )
{
	mbr_t	*owner;
	pet_t	*npc;
	char	*name, *words_name;
	sex_t	sex, words_sex;
	long	npc_dun_lev;
	char	*msg_female, *msg_male;
	bool_t	flg_no_mark;

	/* ���顼��ȯ�����������������֤� */
	/* ����饯�����Ϥ�ɬ�פ�̵�����ϥ��顼�ǤϤʤ� */

	if( req == NULL )
		return FALSE;

	owner = get_mbr_randm( MAP_DEL_X, MAP_DEL_Y );
	if( owner == NULL )
		return FALSE;

	if( calc_pet_n() >= PET_MAX_N ){
		print_msg( FLG_MSG_ERR,
				MSG_ERR_MENU_REQUEST_CAN_NOT_JOIN_PET );
		return FALSE;
	}

	name = MSG_MNSTR_UNKNOWN;
	sex = FEMALE;
	npc_dun_lev = 1;
	msg_female = MSG_NULL;
	msg_male = MSG_NULL;
	flg_no_mark = FALSE;

	words_name = MSG_MNSTR_UNKNOWN;
	words_sex = FEMALE;

	switch( req->kind ){
	case REQUEST_KIND_NULL:
	case REQUEST_KIND_RARE_GOODS:
		return TRUE;
	case REQUEST_KIND_TAME_MNSTR:
		if( !flg_now )
			return TRUE;
		name = cv_idx_to_mnstr_name( req );
		sex = req->mnstr_sex;
		npc_dun_lev = 5;
		msg_female = MSG_WORDS_REQUEST_TAME_MNSTR_JOIN_FEMALE;
		msg_male = MSG_WORDS_REQUEST_TAME_MNSTR_JOIN_MALE;
		flg_no_mark = FALSE;

		words_name = owner->name;
		words_sex = owner->sex.cur;
		break;
	case REQUEST_KIND_RESCUE:
		if( !flg_now )
			return TRUE;
		name = cv_idx_to_rescue_trgt_name( req );
		sex = req->rescue_trgt_sex;
		npc_dun_lev = 5;
		msg_female = MSG_WORDS_REQUEST_RESCUE_JOIN_FEMALE;
		msg_male = MSG_WORDS_REQUEST_RESCUE_JOIN_MALE;
		flg_no_mark = TRUE;

		words_name = name;
		words_sex = sex;
		break;
	case REQUEST_KIND_TOUR_GUIDE:
		name = cv_idx_to_client_name( req );
		sex = req->client_sex;
		npc_dun_lev = 5;
		msg_female = MSG_WORDS_REQUEST_TOUR_GUIDE_JOIN_FEMALE;
		msg_male = MSG_WORDS_REQUEST_TOUR_GUIDE_JOIN_MALE;
		flg_no_mark = TRUE;

		words_name = name;
		words_sex = sex;
		break;
	case REQUEST_KIND_EXTERMINATE:
		return TRUE;
	case REQUEST_KIND_REVENGE:
		name = cv_idx_to_client_name( req );
		sex = req->client_sex;
		npc_dun_lev = req->dun_max_lev;
		msg_female = MSG_WORDS_REQUEST_REVENGE_JOIN_FEMALE;
		msg_male = MSG_WORDS_REQUEST_REVENGE_JOIN_MALE;
		flg_no_mark = FALSE;

		words_name = name;
		words_sex = sex;
		break;
	case REQUEST_KIND_WANTED_CRIMINAL:
	case REQUEST_KIND_MAX_N:
		return TRUE;
	}

	npc = make_pet( npc_dun_lev, kind, owner );
	if( npc == NULL )
		return FALSE;

	str_nz_cpy( npc->name, name, CHR_NAME_MAX_BYTE );
	npc->sex.org = sex;
	npc->sex.cur = sex;
	npc->work.request = req;
	npc->flg_chr &= ~(FLG_CHR_CAN_DEL);
	if( flg_no_mark )
		npc->flg_chr |= FLG_CHR_NO_MARK_MNSTR;

	if( !join_pet( npc ) ){
		print_msg( FLG_MSG_ERR,
				MSG_ERR_MENU_REQUEST_CAN_NOT_JOIN_PET );
		die_chr( npc, FALSE, FALSE, TRUE );
		return FALSE;
	}

	if( (msg_female != NULL) && (msg_male != NULL) ){
		print_words_win( words_name, words_sex,
				msg_female, msg_male, npc->name );
		redraw_all();
	}
	print_msg( FLG_NULL, MSG_JOIN_CHR, npc->name );

	return TRUE;
}

/***************************************************************
* ����κ��糬�ؤ���ã��������ͭ���ϰ�����֤�(���٥�)
* long dun_max_lev : ���糬��
* return : ���糬��
***************************************************************/

long	get_request_dun_max_lev_easy( void )
{
	return get_request_dun_max_lev(
			REQUEST_DUN_MIN_LEV_EASY,
			REQUEST_DUN_MAX_LEV_EASY );
}

/***************************************************************
* ����κ��糬�ؤ���ã��������ͭ���ϰ�����֤�(���̤Υ�٥�)
* long dun_max_lev : ���糬��
* return : ���糬��
***************************************************************/

long	get_request_dun_max_lev_normal( void )
{
	return get_request_dun_max_lev(
			REQUEST_DUN_MIN_LEV_NORMAL,
			REQUEST_DUN_MAX_LEV_NORMAL );
}

/***************************************************************
* ����κ��糬�ؤ���ã��������ͭ���ϰ�����֤�
* long dun_max_lev : ���糬��
* return : ���糬��
***************************************************************/

long	get_request_dun_max_lev( long dun_min_lev, long dun_max_lev )
{
	party_t	*pty = get_party();
	long	sign_lev, dun_lev;
	long	i;

	sign_lev = sgn_l( dun_max_lev );
	dun_max_lev = labs( dun_max_lev );
	dun_min_lev = labs( dun_min_lev );

	dun_lev = dun_min_lev;

	for( i = 0; i < MBR_MAX_N; i++ ){
		long	floor, base, lev;

		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST ) ){
			continue;
		}

		floor = labs( pty->mbr[i]->dun_max_lev_floor );
		base = labs( pty->mbr[i]->dun_max_lev_base );
		lev = max_l( floor, base );
		lev += REQUEST_DUN_ADD_LEV;

		dun_lev = max_l( dun_lev, lev );
	}

	dun_lev = min_l( dun_lev, dun_max_lev );

	return( sign_lev * dun_lev );
}

/***************************************************************
* ����γ��ؤ�����������
* request_t *req : ����
* long min_lev : �Ǿ���
* long max_lev : ���糬
* long range_lev : ���ؤ��ϰ�
***************************************************************/

void	set_request_dun_lev(
	request_t *req,
	long min_lev, long max_lev, long range_lev
)
{
	long	lev, true_range_lev;

	if( req == NULL )
		return;

	min_lev = labs( min_lev );
	max_lev = labs( max_lev );
	range_lev = labs( range_lev );

	if( max_lev < min_lev ){
		long	n;

		n = max_lev;
		max_lev = min_lev;
		min_lev = n;
	}

	lev = min_lev + randm( max_lev - min_lev );
	true_range_lev = randm( range_lev ) + 1;

	req->dun_min_lev = -lev;
	req->dun_max_lev = -(lev + (true_range_lev - 1));
	req->dun_true_lev = -(lev + randm( true_range_lev ));
}

/***************************************************************
* �ꥹ�Ȥ����å�����������������
* n_msg_t ls[] : �ꥹ��
* return : ��å�����
***************************************************************/

n_msg_idx_t	get_ls_n_msg_idx_randm( n_msg_t ls[] )
{
	n_msg_idx_t	i;

	if( ls == NULL )
		return 0;

	for( i = 0; i < LOOP_MAX_4000; i++ )
		if( ls[i] == N_MSG_NULL )
			break;
	if( i <= 0 )
		return 0;

	return( randm( i ) );
}

/***************************************************************
* ����Υ��꡼�������Ƥ�(�ǥե�����ͤ����ꤹ��)
* return : ����
***************************************************************/

request_t	*alloc_request( void )
{
	long	i;

	for( i = 0; i < REQUEST_MAX_N; i++ )
		if( g_request[i].kind == REQUEST_KIND_NULL )
			break;
	if( i >= REQUEST_MAX_N )
		return NULL;

	g_request[i].kind = REQUEST_KIND_NULL;
	g_request[i].dun_min_lev = 0;
	g_request[i].dun_max_lev = 0;
	g_request[i].dun_true_lev = 0;
	g_request[i].prize = 0;
	g_request[i].exp = 0;
	g_request[i].limit = 0;
	g_request[i].flg_contract = FALSE;
	g_request[i].flg_contract_mbr = FALSE;
	g_request[i].idx_contract_name = -1;
	g_request[i].contract_sex = FEMALE;
	g_request[i].flg_finish = FALSE;

	g_request[i].rare_goods_kind = RARE_GOODS_KIND_NULL;
	g_request[i].flg_mnstr_is_npc = FALSE;
	g_request[i].mnstr_kind = MNSTR_KIND_NULL;
	g_request[i].mnstr_n = 1;
	g_request[i].mnstr_exterminate_n = 0;

	g_request[i].heading[0] = '\0';
	g_request[i].msg[0] = '\0';

	g_request[i].idx_client_name = -1;
	g_request[i].idx_mnstr_name = -1;
	g_request[i].idx_rescue_trgt_name = -1;
	g_request[i].idx_client_family_name = -1;
	g_request[i].idx_client_mate_name = -1;

	if( per_randm( 2 ) ){
		g_request[i].client_sex = FEMALE;
	} else {
		g_request[i].client_sex = MALE;
	}
	if( per_randm( 2 ) ){
		g_request[i].mnstr_sex = FEMALE;
	} else {
		g_request[i].mnstr_sex = MALE;
	}
	if( per_randm( 2 ) ){
		g_request[i].rescue_trgt_sex = FEMALE;
	} else {
		g_request[i].rescue_trgt_sex = MALE;
	}
	if( g_request[i].client_sex == MALE ){
		g_request[i].client_family_sex = FEMALE;
	} else {
		g_request[i].client_family_sex = MALE;
	}
	if( per_randm( 2 ) ){
		g_request[i].client_mate_sex = FEMALE;
	} else {
		g_request[i].client_mate_sex = MALE;
	}

	g_request[i].rescue_trgt_kind = MNSTR_KIND_NULL;

	g_request[i].idx_when_1 = -1;
	g_request[i].idx_when_2 = -1;

	g_request[i].idx_weapon = -1;

	return( &(g_request[i]) );
}

/***************************************************************
* ����Υ��꡼�����
* request_t *req : ����
***************************************************************/

void	free_request( request_t *req )
{
	if( req == NULL )
		return;

	req->kind = REQUEST_KIND_NULL;
}

/***************************************************************
* ����Υꥹ�Ȥ��֤�
* return : ����Υꥹ��
***************************************************************/

request_t	*get_request_ls( void )
{
	return g_request;
}

/***************************************************************
* �ꥹ�Ȥ���ͭ���ʰ���ο��������
* return : ����ο�
***************************************************************/

long	get_request_n( void )
{
	long	n;
	long	i;

	n = 0;
	for( i = 0; i < REQUEST_MAX_N; i++ )
		if( g_request[i].kind != REQUEST_KIND_NULL )
			n++;

	return n;
}

/***************************************************************
* ����μ����̾�����֤�
* request_kind_t kind : ����μ���
* return : ����μ����̾��
***************************************************************/

char	*get_request_kind_name( request_kind_t kind )
{
	switch( kind ){
	case REQUEST_KIND_NULL:
		break;
	case REQUEST_KIND_RARE_GOODS:
		return MSG_REQUEST_KIND_RARE_GOODS;
	case REQUEST_KIND_TAME_MNSTR:
		return MSG_REQUEST_KIND_TAME_MNSTR;
	case REQUEST_KIND_RESCUE:
		return MSG_REQUEST_KIND_RESCUE;
	case REQUEST_KIND_TOUR_GUIDE:
		return MSG_REQUEST_KIND_TOUR_GUIDE;
	case REQUEST_KIND_EXTERMINATE:
		return MSG_REQUEST_KIND_EXTERMINATE;
	case REQUEST_KIND_REVENGE:
		return MSG_REQUEST_KIND_REVENGE;
	case REQUEST_KIND_WANTED_CRIMINAL:
		return MSG_REQUEST_KIND_WANTED_CRIMINAL;
	case REQUEST_KIND_MAX_N:
		break;
	}

	return MSG_NULL;
}

/***************************************************************
* ����δ����ڤ������å�����
***************************************************************/

void	chk_request_limit( void )
{
	long	i;

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		request_t	*req;

		req = &(g_request[i]);
		if( req->kind == REQUEST_KIND_NULL )
			continue;
		if( req->limit >= get_game_day() )
			continue;

		if( req->flg_contract && req->flg_contract_mbr ){
			char	*name;
			mbr_t	*mbr;

			chk_request_limit_client( req );

			name = get_request_kind_name( req->kind );
			mbr = get_mbr_randm( MAP_DEL_X, MAP_DEL_Y );

			curs_attrset_chr( mbr, -1, TRUE );
			print_msg( FLG_NULL, MSG_REQUEST_LIMIT, name );
			curs_attrset_dflt();

			fx_energy_drain_all_mbr( TRUE );
		}

		free_request( req );
	}
}

/***************************************************************
* ����δ����ڤ�� NPC ���̤��
* request_t *req : ����
* return : �̤줿��?
***************************************************************/

bool_t	chk_request_limit_client( request_t *req )
{
	pet_t	*npc;
	mnstr_t	*mnstr;
	bool_t	flg_trans_mnstr;

	if( req == NULL )
		return FALSE;
	if( req->kind == REQUEST_KIND_NULL )
		return FALSE;
	if( !req->flg_contract )
		return FALSE;

	npc = get_npc_request( req );
	if( npc == NULL )
		return FALSE;

	if( chk_flg_or( npc->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
		print_msg( FLG_NULL, MSG_NOT_JOIN_CHR, npc->name );
		remove_pet( npc );
		return TRUE;
	}

	flg_trans_mnstr = FALSE;
	switch( req->kind ){
	case REQUEST_KIND_NULL:
	case REQUEST_KIND_RARE_GOODS:
		return FALSE;
	case REQUEST_KIND_TAME_MNSTR:
		return TRUE;	/* FALSE �ǤϤʤ� */
	case REQUEST_KIND_RESCUE:
		print_words_win( npc->name, npc->sex.cur,
				MSG_WORDS_REQUEST_RESCUE_LIMIT_FEMALE,
				MSG_WORDS_REQUEST_RESCUE_LIMIT_MALE,
				npc->name );
		flg_trans_mnstr = TRUE;
		break;
	case REQUEST_KIND_TOUR_GUIDE:
		print_words_win( npc->name, npc->sex.cur,
				MSG_WORDS_REQUEST_TOUR_GUIDE_LIMIT_FEMALE,
				MSG_WORDS_REQUEST_TOUR_GUIDE_LIMIT_MALE,
				npc->name );
		flg_trans_mnstr = FALSE;
		break;
	case REQUEST_KIND_EXTERMINATE:
		return FALSE;
	case REQUEST_KIND_REVENGE:
		print_words_win( npc->name, npc->sex.cur,
				MSG_WORDS_REQUEST_REVENGE_LIMIT_FEMALE,
				MSG_WORDS_REQUEST_REVENGE_LIMIT_MALE,
				npc->name );
		flg_trans_mnstr = TRUE;
		break;
	case REQUEST_KIND_WANTED_CRIMINAL:
	case REQUEST_KIND_MAX_N:
		return FALSE;
	}

	redraw_all();

	/* �̤�� */

	print_msg( FLG_NULL, MSG_NOT_JOIN_CHR, npc->name );

	if( flg_trans_mnstr ){
		if( clip_pos( npc->x, npc->y ) ){
			long	x, y;

			mnstr = make_mnstr( MAP_DEL_X, MAP_DEL_Y, FALSE,
					req->dun_max_lev, npc->mnstr_kind );
			x = npc->x;
			y = npc->y;
			if( !clip_pos( x, y ) ){
				x = randm( MAP_MAX_X );
				y = randm( MAP_MAX_Y );
			}
			put_chr( mnstr, x, y );
		} else {
			mnstr = NULL;
		}
		if( mnstr != NULL ){
			str_nz_cpy( mnstr->name, npc->name,
					CHR_NAME_MAX_BYTE );
			mnstr->sex.org = npc->sex.cur;
			mnstr->sex.cur = mnstr->sex.org;
		}
	}

	remove_pet( npc );

	return TRUE;
}

/***************************************************************
* ����� NPC ���������������å�
***************************************************************/

void	chk_request_npc_contract( void )
{
	chk_clr_request_npc_contract();
	chk_set_request_npc_contract();
}

/***************************************************************
* NPC ���������������
***************************************************************/

void	chk_clr_request_npc_contract( void )
{
	long	i;

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		if( g_request[i].kind == REQUEST_KIND_NULL )
			continue;
		if( !g_request[i].flg_contract )
			continue;
		if( g_request[i].flg_contract_mbr )
			continue;

		/**/

		g_request[i].kind = REQUEST_KIND_NULL;
	}
}

/***************************************************************
* NPC ��������˰���������
***************************************************************/

void	chk_set_request_npc_contract( void )
{
	long	i;

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		n_msg_idx_t	idx;
		sex_t	sex;

		if( g_request[i].kind == REQUEST_KIND_NULL )
			continue;
		if( g_request[i].flg_contract )
			continue;
		if( !rate_randm( REQUEST_NPC_CONTRACT_RATE ) )
			continue;

		/**/

		if( per_randm( 2 ) ){
			idx = get_ls_n_msg_idx_randm( g_ls_npc_name_female );
			sex = FEMALE;
		} else {
			idx = get_ls_n_msg_idx_randm( g_ls_npc_name_male );
			sex = MALE;
		}

		chr_contract_request( &(g_request[i]),
				CHR_KIND_MNSTR, idx, sex );
	}
}

/***************************************************************
* ����Υ�å�����������
* request_t *req : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	set_request_msg( request_t *req )
{
	static char	buf[REQUEST_MSG_MAX_BYTE + 1];
	static char	str_contract[REQUEST_MSG_MAX_BYTE + 1];
	char	*fmt;
	long	buf_idx, fmt_idx;

	if( req == NULL )
		return FALSE;

	fmt = cv_idx_to_request_fmt( req );

	buf[0] = '\0';
	for( buf_idx = 0, fmt_idx = 0; buf_idx < REQUEST_MSG_MAX_BYTE - 2;
			buf_idx++, fmt_idx++ ){
		if( fmt[fmt_idx] == '\0' ){
			break;
		} else if( fmt[fmt_idx] == '\\' ){
			buf_idx--;
		} else if( fmt[fmt_idx] & 0x80 ){
			buf[buf_idx] = fmt[fmt_idx];
		} else if( fmt[fmt_idx] == '$' ){
			if( fmt[fmt_idx + 1] == '$' ){
				buf[buf_idx] = fmt[fmt_idx];
				fmt_idx++;
			} else if( fmt[fmt_idx + 1] != '{' ){
				buf[buf_idx] = fmt[fmt_idx];
			} else {
				set_request_msg_var(
						req,
						&(buf[buf_idx]), &buf_idx,
						&(fmt[fmt_idx]), &fmt_idx );
			}
		} else {
			buf[buf_idx] = fmt[fmt_idx];
		}
	}
	buf[buf_idx] = '\0';

	if( req->flg_contract ){
		char	*name;

		if( req->flg_contract_mbr )
			name = MSG_NPC_NAME_YOU_KIMIRA;
		else
			name = cv_idx_to_contract_name( req );

		sn_printf( str_contract, REQUEST_MSG_MAX_BYTE,
				MSG_REQUEST_CONTRACT_FMT, name );
	} else {
		str_nz_cpy( str_contract,
				MSG_REQUEST_DO_NOT_CONTRACT,
				REQUEST_MSG_MAX_BYTE );
	}
	str_max_n_cat( buf, "\n", REQUEST_MSG_MAX_BYTE );
	str_max_n_cat( buf, str_contract, REQUEST_MSG_MAX_BYTE );

	str_nz_cpy( req->msg, buf, REQUEST_MSG_MAX_BYTE );

	return TRUE;
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��
* request_t *req : ����
* char *buf : Ÿ����
* long *buf_idx : Ÿ������ʸ���������
* char *fmt : �ѿ�����Ƭ����
* long *fmt_idx : �ѿ���ʸ���������
***************************************************************/

void	set_request_msg_var(
	request_t *req,
	char *buf, long *buf_idx,
	char *fmt, long *fmt_idx
)
{
	char	*tail, *arg;
	long	len, max_len;
	long	i;

	if( buf == NULL )
		return;
	if( fmt == NULL )
		return;
	if( buf_idx == NULL )
		return;
	if( fmt_idx == NULL )
		return;

	buf[0] = '\0';

	fmt += 2;

	tail = strchr( fmt, '}' );
	if( tail == NULL )
		return;
	max_len = tail - fmt;

	arg = strchr( fmt, ':' );
	if( arg == NULL ){
		len = max_len;
	} else {
		len = arg - fmt;
		if( len < max_len ){
			arg++;
		} else {
			len = max_len;
			arg = NULL;
		}
	}

	*fmt_idx += 2;

	for( i = 0; i < LOOP_MAX_4000; i++ ){
		if( g_request_msg_var[i].name == NULL )
			break;
		if( strncmp( fmt, g_request_msg_var[i].name, len ) == 0 ){
			g_request_msg_var[i].func( req, buf, arg );
			*buf_idx += str_len_std( buf ) - 1;
			*fmt_idx += max_len + 1 - 1;
			break;
		}
	}
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(�Ǿ���)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_dun_min_lev(
	request_t *req, char *buf, char *arg
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	sn_printf( buf, REQUEST_MSG_MAX_BYTE, "%ld", req->dun_min_lev );
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(���糬)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_dun_max_lev(
	request_t *req, char *buf, char *arg
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	sn_printf( buf, REQUEST_MSG_MAX_BYTE, "%ld", req->dun_max_lev );
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(���ؤ��ϰ�)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_dun_lev_range(
	request_t *req, char *buf, char *arg
)
{
	static char	str_min[32 * CHAR_MAX_LEN_UTF_8 + 1];
	static char	str_max[32 * CHAR_MAX_LEN_UTF_8 + 1];
	long	max_len = 32 * CHAR_MAX_LEN_UTF_8;

	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	if( req->dun_min_lev >= +1 ){
		sn_printf( str_min, max_len, MSG_FLOOR_FMT,
				labs( req->dun_min_lev ) );
	} else if( req->dun_min_lev <= -1 ){
		sn_printf( str_min, max_len, MSG_BASE_FMT,
				labs( req->dun_min_lev ) );
	} else {
		sn_printf( str_min, max_len, MSG_S, MSG_GROUND );
	}

	if( req->dun_max_lev >= +1 ){
		sn_printf( str_max, max_len, MSG_FLOOR_FMT,
				labs( req->dun_max_lev ) );
	} else if( req->dun_max_lev <= -1 ){
		sn_printf( str_max, max_len, MSG_BASE_FMT,
				labs( req->dun_max_lev ) );
	} else {
		sn_printf( str_max, max_len, MSG_S, MSG_GROUND );
	}

	if( req->dun_min_lev == req->dun_max_lev ){
		sn_printf( buf, max_len, MSG_REQUEST_DUN_LEV, str_max );
	} else {
		sn_printf( buf, max_len, MSG_REQUEST_DUN_LEV_RANGE,
				str_min, str_max );
	}
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(�����)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_client(
	request_t *req, char *buf, char *arg
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	if( req->client_sex == FEMALE ){
		set_request_msg_var_ls( req, buf,
				&(req->idx_client_name),
				g_ls_npc_name_female, FALSE );
	} else {
		set_request_msg_var_ls( req, buf,
				&(req->idx_client_name),
				g_ls_npc_name_male, FALSE );
	}
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(õ�����륢���ƥ�)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_rare_goods(
	request_t *req, char *buf, char *arg
)
{
	rare_goods_tab_t	*tab;

	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	if( req->rare_goods_kind == RARE_GOODS_KIND_NULL )
		req->rare_goods_kind = get_rare_goods_randm();

	tab = get_rare_goods_tab( req->rare_goods_kind );
	if( tab == NULL )
		return;

	sn_printf( buf, REQUEST_MSG_MAX_BYTE,
			MSG_REQUEST_VAR_QUOTE, tab->name );
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(��󥹥���)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_mnstr(
	request_t *req, char *buf, char *arg
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	if( req->flg_mnstr_is_npc ){
		if( req->mnstr_sex == FEMALE ){
			set_request_msg_var_ls( req, buf,
					&(req->idx_mnstr_name),
					g_ls_npc_name_female, TRUE );
		} else {
			set_request_msg_var_ls( req, buf,
					&(req->idx_mnstr_name),
					g_ls_npc_name_male, TRUE );
		}
	} else {
		mnstr_tab_t	*tab;

		tab = get_mnstr_tab( req->mnstr_kind, req->dun_true_lev );
		if( tab == NULL ){
			sn_printf( buf, REQUEST_MSG_MAX_BYTE,
					MSG_REQUEST_VAR_QUOTE,
					MSG_MNSTR_UNKNOWN );
		} else {
			sn_printf( buf, REQUEST_MSG_MAX_BYTE,
					MSG_REQUEST_VAR_QUOTE,
					tab->name );
		}
	}
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(��󥹥����ο�)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_mnstr_n(
	request_t *req, char *buf, char *arg
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	sn_printf( buf, REQUEST_MSG_MAX_BYTE,
			MSG_REQUEST_MNSTR_N, req->mnstr_n );
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(�߽����� NPC)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_rescue_trgt(
	request_t *req, char *buf, char *arg
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	if( req->rescue_trgt_sex == FEMALE ){
		set_request_msg_var_ls( req, buf,
				&(req->idx_rescue_trgt_name),
				g_ls_npc_name_female, TRUE );
	} else {
		set_request_msg_var_ls( req, buf,
				&(req->idx_rescue_trgt_name),
				g_ls_npc_name_male, TRUE );
	}
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(�����β�²)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_client_family(
	request_t *req, char *buf, char *arg
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	if( req->client_sex == MALE ){
		/* ����礬�����ʤ��²�Ϻ��� */
		req->client_family_sex = FEMALE;
	} else {
		/* ����礬�����ʤ��²������ */
		req->client_family_sex = MALE;
	}

	if( req->client_family_sex == FEMALE ){
		set_request_msg_var_ls( req, buf,
				&(req->idx_client_family_name),
				g_ls_family_female, FALSE );
	} else {
		set_request_msg_var_ls( req, buf,
				&(req->idx_client_family_name),
				g_ls_family_male, FALSE );
	}
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(���������)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_client_mate(
	request_t *req, char *buf, char *arg
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	if( req->client_mate_sex == FEMALE ){
		set_request_msg_var_ls( req, buf,
				&(req->idx_client_mate_name),
				g_ls_npc_name_female, FALSE );
	} else {
		set_request_msg_var_ls( req, buf,
				&(req->idx_client_mate_name),
				g_ls_npc_name_male, FALSE );
	}
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(���֥��롼�� A)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_when_1(
	request_t *req, char *buf, char *arg
)
{
	n_msg_t	*ls_msg;

	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	ls_msg = g_ls_when_a;
	if( arg != NULL ){
		switch( arg[0] ){
		case 'a':
			ls_msg = g_ls_when_a;
			break;
		case 'b':
			ls_msg = g_ls_when_b;
			break;
		}
	}

	set_request_msg_var_ls( req, buf,
			&(req->idx_when_1),
			ls_msg, FALSE );
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(���֥��롼�� B)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_when_2(
	request_t *req, char *buf, char *arg
)
{
	n_msg_t	*ls_msg;

	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	ls_msg = g_ls_when_a;
	if( arg != NULL ){
		switch( arg[0] ){
		case 'a':
			ls_msg = g_ls_when_a;
			break;
		case 'b':
			ls_msg = g_ls_when_b;
			break;
		}
	}

	set_request_msg_var_ls( req, buf,
			&(req->idx_when_2),
			ls_msg, FALSE );
}

/***************************************************************
* ����Υ�å��������ѿ���Ÿ��(���)
* request_t *req : ����
* char *buf : Ÿ����
* char *arg : �ѿ��ΰ���
***************************************************************/

void	set_request_msg_var_weapon(
	request_t *req, char *buf, char *arg
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;

	set_request_msg_var_ls( req, buf,
			&(req->idx_weapon),
			g_ls_weapon, FALSE );
}

/***************************************************************
* ����Υ�å��������ѿ���ꥹ�Ȥ���Ÿ��
* request_t *req : ����
* char *buf : Ÿ����
* n_msg_idx_t *n_msg_idx : �ꥹ�ȤΥ���ǥå���
* n_msg_t ls_msg[] : �ꥹ��
* bool_t flg_quote : �������ƥ��󥰤��뤫?
***************************************************************/

void	set_request_msg_var_ls(
	request_t *req, char *buf,
	n_msg_idx_t *n_msg_idx, n_msg_t ls_msg[],
	bool_t flg_quote
)
{
	if( buf == NULL )
		return;
	buf[0] = '\0';
	if( req == NULL )
		return;
	if( n_msg_idx == NULL )
		return;
	if( ls_msg == NULL )
		return;

	if( *n_msg_idx <= -1 )
		*n_msg_idx = get_ls_n_msg_idx_randm( ls_msg );

	if( flg_quote ){
		sn_printf( buf, REQUEST_MSG_MAX_BYTE,
				MSG_REQUEST_VAR_QUOTE,
				MSG( ls_msg[*n_msg_idx] ) );
	} else {
		sn_printf( buf, REQUEST_MSG_MAX_BYTE,
				MSG_S,
				MSG( ls_msg[*n_msg_idx] ) );
	}
}

/***************************************************************
* ����Υꥹ�Ⱦ�θ��Ф�������
* request_t *req : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	set_request_heading( request_t *req )
{
	char	*str_contract;
	char	*name;
	long	len;

	if( req == NULL )
		return FALSE;

	if( req->flg_finish ){
		str_contract = MSG_REQUEST_CONTRACT_FINISH;
	} else if( req->flg_contract ){
		if( req->flg_contract_mbr ){
			str_contract = MSG_REQUEST_CONTRACT_YOU;
		} else {
			str_contract = MSG_REQUEST_CONTRACT_OTHER;
		}
	} else {
		str_contract = MSG_REQUEST_CONTRACT_STILL;
	}

	name = get_request_kind_name( req->kind );
	len = get_pading_len( name, REQUEST_NAME_MIN_LEN );

	sn_printf( req->heading, MENU_MSG_MAX_BYTE,
			MSG_REQUEST_HEADING_FMT,
			str_contract,
			len,
			name,
			req->dun_max_lev,
			req->limit - get_game_day(),
			fmt_gold( req->prize ) );

	return TRUE;
}

/***************************************************************
* ����饯������������������
* request_t *req : ����
* chr_kind_t kind : ����饯���μ���
* n_msg_idx_t n_idx_name : NPC ��̾���ꥹ�ȤΥ���ǥå���
* sex_t sex : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	chr_contract_request(
	request_t *req,
	chr_kind_t kind, n_msg_idx_t n_idx_name, sex_t sex
)
{
	if( req == NULL )
		return FALSE;

	if( req->kind == REQUEST_KIND_NULL )
		return FALSE;
	if( req->flg_contract )
		return FALSE;

	/**/

	if( kind == CHR_KIND_MBR ){
		if( !make_client( req, get_npc_kind_randm(), FALSE ) )
			return FALSE;

		req->idx_contract_name = -1;
		req->contract_sex = FEMALE;
		req->flg_contract_mbr = TRUE;
	} else if( kind == CHR_KIND_MNSTR ){
		req->idx_contract_name = n_idx_name;
		req->contract_sex = sex;
		req->flg_contract_mbr = FALSE;
	} else {
		return FALSE;
	}

	req->flg_contract = TRUE;

	return TRUE;
}

/***************************************************************
* ��ɸ�Υ���饯����ȯ���������ΰ���ؤαƶ�������å�
* chr_t *chr : ȯ�����줿����饯��
***************************************************************/

void	chk_find_request_chr( chr_t *chr )
{
	request_t	*req;
	pet_t	*npc;
	mbr_t	*mbr;
	char	*msg_fema, *msg_male;

	if( chr == NULL )
		return;

	/* �������������Ƥ��뤫? */

	req = chr->work.request;
	if( req == NULL )
		return;
	if( !req->flg_contract )
		return;
	if( !req->flg_contract_mbr )
		return;

	/* ȯ����������饯����������ܿͤ��ä���̤��� */

	npc = get_npc_request( req );
	if( (npc != NULL) && cmp_chr( npc, chr ) )
		return;

	mbr = get_mbr_randm( MAP_DEL_X, MAP_DEL_Y );
	if( mbr == NULL )
		return;

	switch( req->kind ){
	case REQUEST_KIND_NULL:
		break;
	case REQUEST_KIND_RARE_GOODS:
		break;
	case REQUEST_KIND_TAME_MNSTR:
		msg_fema = MSG_WORDS_REQUEST_TAME_MNSTR_FIND_FEMALE;
		msg_male = MSG_WORDS_REQUEST_TAME_MNSTR_FIND_MALE;

		print_words_win( mbr->name, mbr->sex.cur,
				msg_fema, msg_male );
		break;
	case REQUEST_KIND_RESCUE:
		msg_fema = MSG_WORDS_REQUEST_RESCUE_FIND_FEMALE;
		msg_male = MSG_WORDS_REQUEST_RESCUE_FIND_MALE;

		print_words_win( mbr->name, mbr->sex.cur,
				msg_fema, msg_male );
		break;
	case REQUEST_KIND_TOUR_GUIDE:
		break;
	case REQUEST_KIND_EXTERMINATE:
		break;
	case REQUEST_KIND_REVENGE:
		if( !chk_watch_request_client( req ) )
			break;

		msg_fema = MSG_WORDS_REQUEST_REVENGE_FIND_FEMALE;
		msg_male = MSG_WORDS_REQUEST_REVENGE_FIND_MALE;

		print_words_win( cv_idx_to_client_name( req ),
				req->client_sex,
				msg_fema,
				msg_male,
				cv_idx_to_mnstr_name( req ) );
		break;
	case REQUEST_KIND_WANTED_CRIMINAL:
		msg_fema = MSG_WORDS_REQUEST_WANTED_CRIMINAL_FIND_FEMALE;
		msg_male = MSG_WORDS_REQUEST_WANTED_CRIMINAL_FIND_MALE;

		print_words_win( mbr->name, mbr->sex.cur,
				msg_fema,
				msg_male,
				cv_idx_to_mnstr_name( req ) );
		break;
	case REQUEST_KIND_MAX_N:
		break;
	}

	redraw_all();
}

/***************************************************************
* �������������
* request_t *req : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	finish_request( request_t *req )
{
	party_t	*pty = get_party();

	if( req == NULL )
		return FALSE;
	if( req->kind == REQUEST_KIND_NULL )
		return FALSE;
	if( req->flg_finish )
		return FALSE;

	call_game_sound_play( SOUND_KIND_REQUEST_FINISH, 1 );

	req->flg_finish = TRUE;

	curs_attrset_chr( pty->mbr[0], +1, TRUE );
	print_msg( FLG_NULL, MSG_REQUEST_FINISH,
			get_request_kind_name( req->kind ) );
	curs_attrset_dflt();

	return TRUE;
}

/***************************************************************
* ������Ԥ���
* request_t *req : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	dont_finish_request( request_t *req )
{
	if( req == NULL )
		return FALSE;

	if( req->kind == REQUEST_KIND_NULL )
		return FALSE;
	if( !req->flg_finish )
		return FALSE;

	req->flg_finish = FALSE;

	return TRUE;
}

/***************************************************************
* ����饯�����������ΰ���ؤαƶ�������å�
* chr_t *chr : ��������饯��
***************************************************************/

void	chk_finish_request_chr_dead( chr_t *chr )
{
	request_t	*req;

	if( chr == NULL )
		return;

	chk_finish_request_exterminate( chr->mnstr_kind, 1,
			REQUEST_KIND_TOUR_GUIDE, FALSE );
	chk_finish_request_exterminate( chr->mnstr_kind, 1,
			REQUEST_KIND_EXTERMINATE, TRUE );

	put_request_rare_goods( chr );

	req = chr->work.request;
	if( req == NULL )
		return;

	switch( req->kind ){
	case REQUEST_KIND_NULL:
		break;
	case REQUEST_KIND_RARE_GOODS:
	case REQUEST_KIND_TAME_MNSTR:
	case REQUEST_KIND_RESCUE:
	case REQUEST_KIND_TOUR_GUIDE:
	case REQUEST_KIND_EXTERMINATE:
		break;
	case REQUEST_KIND_REVENGE:
		chk_finish_request_revenge( req, chr );
		break;
	case REQUEST_KIND_WANTED_CRIMINAL:
		chk_finish_request_wanted_criminal( req );
		break;
	case REQUEST_KIND_MAX_N:
		break;
	}
}

/***************************************************************
* ����饯�����������ΰ���ؤαƶ�������å�(�����ƥ�õ��)
***************************************************************/

void	chk_finish_request_rare_goods( void )
{
	party_t	*pty = get_party();
	long	i, j;

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		if( g_request[i].kind == REQUEST_KIND_NULL )
			continue;
		if( g_request[i].kind != REQUEST_KIND_RARE_GOODS )
			continue;
		if( !g_request[i].flg_contract )
			continue;
		if( !g_request[i].flg_contract_mbr )
			continue;

		dont_finish_request( &(g_request[i]) );

		for( j = 0; j < MBR_MAX_N; j++ ){
			if( chk_mbr_have_rare_goods(
					pty->mbr[j],
					g_request[i].rare_goods_kind,
					g_request[i].mnstr_kind,
					FALSE ) ){
				finish_request( &(g_request[i]) );
				break;
			}
		}
	}
}

/***************************************************************
* �����ã������ NPC ���ѡ��ƥ��˲ä��
* request_t *req : ����
* mnstr_t *npc : NPC
* return : NPC ���ѡ��ƥ��˲ä�ä���?
***************************************************************/

bool_t	chk_finish_request_join( request_t *req, mnstr_t *npc )
{
	if( req == NULL )
		return FALSE;
	if( req->flg_finish )
		return FALSE;
	if( !req->flg_contract )
		return FALSE;
	if( !req->flg_contract_mbr )
		return FALSE;
	if( npc == NULL )
		return FALSE;

	switch( req->kind ){
	case REQUEST_KIND_NULL:
	case REQUEST_KIND_RARE_GOODS:
		return FALSE;
	case REQUEST_KIND_TAME_MNSTR:
	case REQUEST_KIND_RESCUE:
		break;
	case REQUEST_KIND_TOUR_GUIDE:
	case REQUEST_KIND_EXTERMINATE:
	case REQUEST_KIND_REVENGE:
	case REQUEST_KIND_WANTED_CRIMINAL:
	case REQUEST_KIND_MAX_N:
		return FALSE;
	}

	if( !make_client( npc->work.request, npc->mnstr_kind, TRUE ) )
		return FALSE;

	die_chr( npc, FALSE, FALSE, TRUE );
	finish_request( req );

	return TRUE;
}

/***************************************************************
* ��󥹥������������ΰ���ؤαƶ�������å�(��󥹥����༣)
* mnstr_kind_t mnstr_kind : ��󥹥����μ���
* long add : �ݤ������Υ����󥿤�­����
* request_kind_t req_kind : ����μ���
* bool_t flg_dec_add : 
*   TRUE  : �ƥ����󥿤�­��������������­�����򸺤餹
*   FALSE : ���ƤΥ����󥿤�Ʊ������­��
***************************************************************/

void	chk_finish_request_exterminate(
	mnstr_kind_t mnstr_kind,
	long add,
	request_kind_t req_kind,
	bool_t flg_dec_add
)
{
	long	i;

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		request_t	*req;

		if( add < 0 )
			break;

		if( g_request[i].kind == REQUEST_KIND_NULL )
			continue;
		if( g_request[i].kind != req_kind )
			continue;
		if( !g_request[i].flg_contract )
			continue;
		if( !g_request[i].flg_contract_mbr )
			continue;
		if( g_request[i].mnstr_kind != mnstr_kind )
			continue;
		if( (req_kind == REQUEST_KIND_TOUR_GUIDE)
				|| (req_kind == REQUEST_KIND_REVENGE) ){
			if( !chk_watch_request_client( &(g_request[i]) ) ){
				continue;
			}
		}

		req = &(g_request[i]);
		req->mnstr_exterminate_n += add;
		if( flg_dec_add )
			add = req->mnstr_exterminate_n - req->mnstr_n;
		if( req->mnstr_exterminate_n >= req->mnstr_n ){
			req->mnstr_exterminate_n = req->mnstr_n;
			finish_request( req );
		}
	}
}

/***************************************************************
* ����饯�����������ΰ���ؤαƶ�������å�(��Ƥ��)
* request_t *req : ����
* return : ���꤬����������?
***************************************************************/

bool_t	chk_finish_request_revenge( request_t *req, chr_t *chr )
{
	pet_t	*npc;

	if( req == NULL )
		return FALSE;
	if( req->kind != REQUEST_KIND_REVENGE )
		return FALSE;
	if( is_pet( chr ) )
		return FALSE;

	npc = get_npc_request( req );
	if( npc == NULL )
		return FALSE;
	if( cmp_chr( npc, chr ) )
		return FALSE;

	if( !chk_watch_request_client( req ) ){
		free_request( req );
		return FALSE;
	}

	print_words_win( npc->name, npc->sex.cur,
			MSG_WORDS_REQUEST_REVENGE_FINISH_FEMALE,
			MSG_WORDS_REQUEST_REVENGE_FINISH_MALE );
	redraw_all();

	finish_request( req );

	return TRUE;
}

/***************************************************************
* ����饯�����������ΰ���ؤαƶ�������å�(�޶��)
* request_t *req : ����
* return : ���꤬����������?
***************************************************************/

bool_t	chk_finish_request_wanted_criminal( request_t *req )
{
	if( req == NULL )
		return FALSE;
	if( req->kind != REQUEST_KIND_WANTED_CRIMINAL )
		return FALSE;

	if( req->flg_contract && req->flg_contract_mbr ){
		finish_request( req );
		return TRUE;
	} else {
		free_request( req );
		return FALSE;
	}
}

/***************************************************************
* �����������Ƥΰ�����Ĥ���
* chr_kind_t chr_kind : PC �� NPC ��?
***************************************************************/

void	close_all_request( chr_kind_t chr_kind )
{
	long	i;

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		if( g_request[i].kind == REQUEST_KIND_NULL )
			continue;
		if( !g_request[i].flg_contract )
			continue;

		/**/

		close_request( &(g_request[i]), chr_kind );
	}
}

/***************************************************************
* ��������������Ĥ���
* request_t *req : ����
* chr_kind_t chr_kind : PC �� NPC ��?
* return : ���꤬����������?
***************************************************************/

bool_t	close_request( request_t *req, chr_kind_t chr_kind )
{
	party_t	*pty = get_party();
	sex_t	master_sex;
	const char	*master_name;
	long	i;

	if( req == NULL )
		return FALSE;

	if( req->kind == REQUEST_KIND_NULL )
		return FALSE;
	if( !req->flg_contract )
		return FALSE;
	if( !req->flg_finish )
		return FALSE;

	if( chr_kind == CHR_KIND_MBR ){
		if( !req->flg_contract_mbr )
			return FALSE;
	} else {
		if( req->flg_contract_mbr )
			return FALSE;
	}

	/* OK */

	if( chr_kind != CHR_KIND_MBR )
		return TRUE;

	/* �����ƥ������˼��Ϥ� */

	if( req->kind == REQUEST_KIND_RARE_GOODS ){
		for( i = 0; i < MBR_MAX_N; i++ ){
			if( chk_mbr_have_rare_goods( pty->mbr[i],
					req->rare_goods_kind,
					req->mnstr_kind, TRUE ) ){
			}
		}
	}

	not_join_all_client( req, TRUE );

	/* ��å�������ɽ�� */

	master_sex = get_npc_sex_shop( SHOP_N_BAR );
	master_name = get_npc_name_shop( SHOP_N_BAR, master_sex );

	print_words_win( master_name, master_sex,
			MSG_WORDS_REQUEST_CLOSE_1_FEMALE,
			MSG_WORDS_REQUEST_CLOSE_1_MALE );

	add_party_gold( req->prize );
	give_party_reward_item_randm();
	exp_party( req->exp, FALSE, TRUE );

	print_words_win( master_name, master_sex,
			MSG_WORDS_REQUEST_CLOSE_2_FEMALE,
			MSG_WORDS_REQUEST_CLOSE_2_MALE );

	/* end */

	redraw_all();

	req->kind = REQUEST_KIND_NULL;

	return TRUE;
}

/***************************************************************
* ������ʥ����ƥ���󽷤Ȥ��ƥѡ��ƥ���Ϳ����
***************************************************************/

void	give_party_reward_item_randm()
{
	scroll_kind_t	kind;
	long	n;
	long	tab_n;
	item_t	*item;
	long	i;

	kind = SCROLL_KIND_NULL;
	n = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls_reward_scroll[i] == SCROLL_KIND_NULL )
			break;

		n++;
		if( per_randm( n ) )
			kind = ls_reward_scroll[i];
	}
	if( kind == SCROLL_KIND_NULL )
		return;

	tab_n = get_scroll_tab_n( get_scroll_tab( kind ) );
	item = make_item_scroll( -1, tab_n );
	item->flg |= (FLG_ITEM_DETECTED | FLG_ITEM_IDENTIFIED);
	item->flg &= ~(FLG_ITEM_CURSED);
	set_item_name( item );

	if( !give_party_reward_item( item ) )
		del_item( item );
}

/***************************************************************
* ����Υ����ƥ���󽷤Ȥ��ƥѡ��ƥ���Ϳ����
* item_t *item : �����ƥ�
* return : Ϳ����줿��?
***************************************************************/

bool_t	give_party_reward_item( item_t *item )
{
	return give_party_item( item, TRUE, TRUE );
}

/***************************************************************
* ����礬��ɸ���ݤ��Τ򸫤Ƥ��뤫?
* request_t *req : ����
* return : ���Ƥ��뤫?
***************************************************************/

bool_t	chk_watch_request_client( request_t *req )
{
	long	i;
	pet_t	*npc;
	pet_t	**party_npc = get_party_pet();

	if( req == NULL )
		return FALSE;
	if( (req->kind != REQUEST_KIND_TOUR_GUIDE)
			&& (req->kind != REQUEST_KIND_REVENGE) ){
		return FALSE;
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		npc = party_npc[i];

		if( npc == NULL )
			continue;
		if( chk_flg_or( npc->stat,
				(FLG_STAT_NOT_EXIST | FLG_STAT_DEAD) ) ){
			continue;
		}
		if( npc->work.request != req )
			continue;

		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* �ط��������Ƥΰ������̤��
* request_t *req : ����
* bool_t flg_success : ���꤬����������?
***************************************************************/

void	not_join_all_client( request_t *req, bool_t flg_success )
{
	long	i;
	pet_t	*npc;
	pet_t	**ls_npc = get_ls_pet();

	if( req == NULL )
		return;

	for( i = 0; i < LS_PET_MAX_N; i++ ){
		npc = ls_npc[i];

		if( npc == NULL )
			continue;
		if( chk_flg_or( npc->stat, FLG_STAT_NOT_EXIST ) )
			continue;
		if( npc->work.request != req )
			continue;

		not_join_client( req, npc, flg_success );
	}
}

/***************************************************************
* �������̤��
* request_t *req : ����
* pet_t *npc : �����
* bool_t flg_success : ���꤬����������?
***************************************************************/

void	not_join_client( request_t *req, pet_t *npc, bool_t flg_success )
{
	char	*msg_female, *msg_male;

	if( npc == NULL )
		return;

	msg_female = NULL;
	msg_male = NULL;

	switch( req->kind ){
	case REQUEST_KIND_NULL:
	case REQUEST_KIND_RARE_GOODS:
		return;
	case REQUEST_KIND_TAME_MNSTR:
		/* ưʪ������ʤ� */
		break;	/* return �ǤϤʤ� */
	case REQUEST_KIND_RESCUE:
		msg_female = MSG_WORDS_REQUEST_RESCUE_FINISH_FEMALE,
		msg_male = MSG_WORDS_REQUEST_RESCUE_FINISH_MALE;
		break;
	case REQUEST_KIND_TOUR_GUIDE:
		msg_female = MSG_WORDS_REQUEST_TOUR_GUIDE_FINISH_FEMALE,
		msg_male = MSG_WORDS_REQUEST_TOUR_GUIDE_FINISH_MALE;
		break;
	case REQUEST_KIND_EXTERMINATE:
		return;
	case REQUEST_KIND_REVENGE:
		msg_female = MSG_WORDS_REQUEST_REVENGE_FINISH_FEMALE,
		msg_male = MSG_WORDS_REQUEST_REVENGE_FINISH_MALE;
		break;
	case REQUEST_KIND_WANTED_CRIMINAL:
	case REQUEST_KIND_MAX_N:
		return;
	}

	if( flg_success && (msg_female != NULL) && (msg_male != NULL) ){
		print_words_win( npc->name, npc->sex.cur,
				msg_female, msg_male );
	}

	redraw_all();

	print_msg( FLG_NULL, MSG_NOT_JOIN_CHR, npc->name );
	npc->gold = 0;
	remove_pet( npc );
}

/***************************************************************
* ����Υ��֥������Ȥ��µܤ��֤�
***************************************************************/

void	put_request_all_obj( void )
{
	put_request_item();
	put_request_mnstr();
}

/***************************************************************
* ����Υ쥢�����å����µܤ��֤�
* chr_t *chr : �쥢�����å�����äƤ�����󥹥���
***************************************************************/

void	put_request_rare_goods( chr_t *chr )
{
	dun_t	*dun = get_dun();
	long	tab_n;
	item_t	*item;
	long	i;

	if( chr == NULL )
		return;

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		if( g_request[i].kind == REQUEST_KIND_NULL )
			continue;
		if( g_request[i].kind != REQUEST_KIND_RARE_GOODS )
			continue;
		if( g_request[i].flg_finish )
			continue;
		if( g_request[i].mnstr_kind != chr->mnstr_kind )
			continue;
		if( sgn_l( g_request[i].dun_min_lev ) != sgn_l( dun->lev ) )
			continue;
		if( sgn_l( g_request[i].dun_max_lev ) != sgn_l( dun->lev ) )
			continue;
		if( labs( g_request[i].dun_min_lev ) > labs( dun->lev ) )
			continue;
		if( labs( g_request[i].dun_max_lev ) < labs( dun->lev ) )
			continue;

		if( !rate_randm( REQUEST_RARE_GOODS_DROP_RATE ) )
			continue;

		/* ��ɸ�Υ����ƥ������ */

		tab_n = get_rare_goods_tab_n( get_rare_goods_tab(
				g_request[i].rare_goods_kind ) );
		if( tab_n <= -1 )
			continue;

		item = make_item_rare_goods( dun->lev, tab_n );
		if( item == NULL )
			continue;

		item->dat.rare_goods.mnstr_kind = chr->mnstr_kind;
		put_item( item, chr->x, chr->y, PUT_ITEM_R, FALSE );
	}
}

/***************************************************************
* ����Υ����ƥ���µܤ��֤�
***************************************************************/

void	put_request_item( void )
{
}

/***************************************************************
* ����Υ�󥹥������µܤ��֤�
***************************************************************/

void	put_request_mnstr( void )
{
	dun_t	*dun = get_dun();
	long	i;

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		mnstr_kind_t	mnstr_kind;
		char	*name;
		sex_t	sex;
		bool_t	flg_make_npc, flg_hungry;
		mnstr_t	*p;

		if( g_request[i].kind == REQUEST_KIND_NULL )
			continue;
		if( g_request[i].flg_finish )
			continue;
		if( g_request[i].dun_true_lev != dun->lev )
			continue;

		mnstr_kind = MNSTR_KIND_NULL;
		name = MSG_MNSTR_UNKNOWN;
		sex = MALE;
		flg_make_npc = FALSE;
		flg_hungry = FALSE;

		switch( g_request[i].kind ){
		case REQUEST_KIND_TAME_MNSTR:
			if( g_request[i].mnstr_kind == MNSTR_KIND_NULL )
				continue;
			mnstr_kind = g_request[i].mnstr_kind;
			name = cv_idx_to_mnstr_name( &(g_request[i]) );
			sex = g_request[i].mnstr_sex;
			flg_make_npc = TRUE;
			flg_hungry = TRUE;
			break;
		case REQUEST_KIND_RESCUE:
			if( g_request[i].idx_rescue_trgt_name <= -1 )
				continue;
			mnstr_kind = g_request[i].rescue_trgt_kind;
			name = cv_idx_to_rescue_trgt_name( &(g_request[i]) );
			sex = g_request[i].rescue_trgt_sex;
			flg_make_npc = TRUE;
			flg_hungry = FALSE;
			break;
		case REQUEST_KIND_REVENGE:
		case REQUEST_KIND_WANTED_CRIMINAL:
			if( g_request[i].mnstr_kind == MNSTR_KIND_NULL )
				continue;
			mnstr_kind = g_request[i].mnstr_kind;
			name = cv_idx_to_mnstr_name( &(g_request[i]) );
			sex = g_request[i].mnstr_sex;
			flg_make_npc = FALSE;
			flg_hungry = FALSE;
			break;
		case REQUEST_KIND_NULL:
		case REQUEST_KIND_RARE_GOODS:
		case REQUEST_KIND_TOUR_GUIDE:
		case REQUEST_KIND_EXTERMINATE:
		case REQUEST_KIND_MAX_N:
			continue;
		}

		/* ��ɸ�Υ�󥹥��������� */

		p = make_mnstr( MAP_DEL_X, MAP_DEL_Y, FALSE,
				dun->lev, mnstr_kind );
		if( p == NULL )
			continue;

		if( flg_make_npc ){
			p->attitude = ATTITUDE_MATE;
		} else {
			p->attitude = ATTITUDE_ENEMY;
		}
		str_nz_cpy( p->name, name, CHR_NAME_MAX_BYTE );
		p->work.request = &(g_request[i]);
		p->sex.org = sex;
		p->sex.cur = sex;
		if( flg_hungry ){
			p->fx_data.stomach.rate
					= p->fx_data.stomach.hungry_rate;
		}

		if( g_flg_debug && FLG_DEBUG_REQUEST ){
			mbr_t	*mbr;

			mbr = get_mbr_randm( MAP_DEL_X, MAP_DEL_Y );
			if( mbr != NULL ){
				put_chr( p, mbr->x, mbr->y );
				return;
			}
		}
		put_chr( p, randm( MAP_MAX_X ), randm( MAP_MAX_Y ) );
	}
}

/***************************************************************
* ����饯�� ������ط��Υڥå�(NPC)��?
* chr_t *chr : ��˥塼���ꥹ��
* return : �ڥå�(NPC)��?
***************************************************************/

bool_t	is_client( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;
	if( !is_pet( chr ) )
		return FALSE;
	if( chr->work.request == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* �ѡ��ƥ��������Ƥ������ꥹ�ȤΥ�˥塼������
* menu_t **pp : ��˥塼���ꥹ��
* menu_t **dflt : ��˥塼�Υǥե���ȹ���
* return : ��˥塼�ΰ�ư��
***************************************************************/

char	*cb_menu_request_mbr( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );

	return( set_menu_request( pp, dflt,
			cb_menu_sel_request_mbr, TRUE ) );
}

/***************************************************************
* ���ΰ���ꥹ�ȤΥ�˥塼������
* menu_t **pp : ��˥塼���ꥹ��
* menu_t **dflt : ��˥塼�Υǥե���ȹ���
* return : ��˥塼�ΰ�ư��
***************************************************************/

char	*cb_menu_request_bar( menu_t **pp, menu_t **dflt )
{
	chk_finish_request_rare_goods();
	close_all_request( CHR_KIND_MBR );

	return( set_menu_request( pp, dflt,
			cb_menu_sel_request_bar, FALSE ) );
}

/***************************************************************
* ����ꥹ�ȤΥ�˥塼������
* menu_t **pp : ��˥塼���ꥹ��
* menu_t **dflt : ��˥塼�Υǥե���ȹ���
* menu_call_back_t cb : ����������Υ����롦�Хå��ؿ�
* bool_t flg_mbr : ���С��������Ƥ������ʳ������åפ��뤫?
* return : ��˥塼�ΰ�ư��
***************************************************************/

char	*set_menu_request(
	menu_t **pp, menu_t **dflt,
	menu_call_back_t cb, bool_t flg_mbr
)
{
	menu_t	*ls;
	long	n;
	long	i, k;

	ls = ls_menu_request;
	k = 0;

	str_nz_cpy( ls[k].path, "/request", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/request/--", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_BAR_REQUEST, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	n = 0;
	for( i = 0; i < REQUEST_MAX_N; i++ ){
		if( g_request[i].kind <= REQUEST_KIND_NULL )
			continue;
		if( g_request[i].kind >= REQUEST_KIND_MAX_N )
			continue;

		/* ���С��������Ƥ������ʳ������åפ��� */
		if( !g_request[i].flg_contract_mbr )
			if( flg_mbr )
				continue;

		set_request_heading( &(g_request[i]) );

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN, "/request/%ld", i );
		str_nz_cpy( ls[k].kind, "<OpenWinItem>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A'
				+ (n % MENU_REQUEST_N_PER_PAGE));
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, g_request[i].heading,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb;
		ls[k].arg = &(g_request[i]);
		ls[k].flg = FLG_NULL;
		k++;
		n++;

		if( ((n % MENU_REQUEST_N_PER_PAGE) == 0) && !flg_mbr ){
			str_nz_cpy( ls[k].path, "/request/Refresh",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[k].kind, "<Branch>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = 'Z';
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_NULL;
			sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
					MSG_MENU_REQUEST_REFRESH,
					fmt_gold( REQUEST_REFRESH_PRIZE ) );
			ls[k].call_back = cb_menu_request_refresh;
			ls[k].arg = NULL;
			ls[k].flg = FLG_NULL;
			k++;
		}

		if( (n % MENU_REQUEST_N_PER_PAGE) == 0 ){
			str_nz_cpy( ls[k].path, "/request/--",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[k].kind, "<PageSeparator>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = '\0';
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_NULL;
			ls[k].msg[0] = '\0';
			ls[k].call_back = NULL;
			ls[k].arg = NULL;
			ls[k].flg = FLG_NULL;
			k++;
		}
	}
	if( !flg_mbr ){
		str_nz_cpy( ls[k].path, "/request/Refresh",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'Z';
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
				MSG_MENU_REQUEST_REFRESH,
				fmt_gold( REQUEST_REFRESH_PRIZE ) );
		ls[k].call_back = cb_menu_request_refresh;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;
	}
	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	if( n <= 0 ){
		print_msg( FLG_MSG_ERR, MSG_ERR_MENU_REQUEST );
		return STR_MENU_CANCEL;
	}

	return NULL;
}

/***************************************************************
* �ѡ��ƥ��������Ƥ�������ɽ��
* menu_t **pp : ��˥塼���ꥹ��
* menu_t **dflt : ��˥塼�Υǥե���ȹ���
* return : ��˥塼�ΰ�ư��
***************************************************************/

char	*cb_menu_sel_request_mbr( menu_t **pp, menu_t **dflt )
{
	request_t	*req;

	req = (request_t *)((*pp)->arg);
	if( req == NULL )
		return STR_MENU_ERR;

	set_request_msg( req );
	draw_request( req );

	return STR_MENU_CANCEL;
}

/***************************************************************
* ���ΰ����ɽ��
* menu_t **pp : ��˥塼���ꥹ��
* menu_t **dflt : ��˥塼�Υǥե���ȹ���
* return : ��˥塼�ΰ�ư��
***************************************************************/

char	*cb_menu_sel_request_bar( menu_t **pp, menu_t **dflt )
{
	request_t	*req;
	bool_t	flg_yes = FALSE;

	req = (request_t *)((*pp)->arg);
	if( req == NULL )
		return STR_MENU_ERR;

	set_request_msg( req );
	draw_request( req );

	if( req->flg_finish )
		return STR_MENU_CANCEL;
	if( req->flg_contract ){
		if( req->flg_contract_mbr ){
			flg_yes = ask_cancel_request( req );
		}
	} else {
		flg_yes = ask_contract_request( req );
	}

	if( flg_yes )
		return "/bar/request";

	return STR_MENU_CANCEL;
}

/***************************************************************
* ����Υꥹ�Ȥ��ե�å��夷�ƿ�����ʪ�����촹����
* menu_t **pp : ��˥塼���ꥹ��
* menu_t **dflt : ��˥塼�Υǥե���ȹ���
* return : ��˥塼�ΰ�ư��
***************************************************************/

char	*cb_menu_request_refresh( menu_t **pp, menu_t **dflt )
{
	ask_t	ask;
	long	i;

	/* �ץ쥤�䡼�˳�ǧ���� */

	ask = exec_menu_ask( MSG_TTL_MENU_REQUEST_REFRESH_ASK,
			ASK_NO, TRUE );

	if( ask != ASK_YES )
		return STR_MENU_CANCEL;

	/* ����Υꥹ�Ȥ��ե�å��� */

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		if( g_request[i].kind == REQUEST_KIND_NULL )
			continue;

		/* ���С��������Ƥ������ϥ����åפ��� */
		if( g_request[i].flg_contract
				&& g_request[i].flg_contract_mbr ){
			continue;
		}

		free_request( &(g_request[i]) );
	}

	make_request_all();

	/* ��������ʧ�� */

	sub_party_gold( REQUEST_REFRESH_PRIZE );

	return "/bar/request";
}

/***************************************************************
* ���������뤫�ץ쥤�䡼�����Ф���
* request_t *req : ����
* return : ������������?
***************************************************************/

bool_t	ask_contract_request( request_t *req )
{
	ask_t	ask;
	sex_t	master_sex;
	const char	*master_name;

	if( req == NULL )
		return FALSE;

	ask = exec_menu_ask( MSG_TTL_MENU_REQUEST_MBR_CONTRACT,
			ASK_NO, TRUE );

	if( ask != ASK_YES )
		return FALSE;

	if( !chr_contract_request( req, CHR_KIND_MBR, -1, FEMALE ) )
		return FALSE;

	master_sex = get_npc_sex_shop( SHOP_N_BAR );
	master_name = get_npc_name_shop( SHOP_N_BAR, master_sex );
	print_words_win( master_name, master_sex,
			MSG_WORDS_REQUEST_CONTRACT_FEMALE,
			MSG_WORDS_REQUEST_CONTRACT_MALE );

	return TRUE;
}

/***************************************************************
* ����򥭥�󥻥뤹�뤫�ץ쥤�䡼�����Ф���
* request_t *req : ����
* return : ����򥭥�󥻥뤷����?
***************************************************************/

bool_t	ask_cancel_request( request_t *req )
{
	char	msg[MENU_MSG_MAX_BYTE + 1];
	gold_t	penalty;
	ask_t	ask;
	sex_t	master_sex;
	const char	*master_name;

	if( req == NULL )
		return FALSE;

	penalty = req->prize * REQUEST_PENALTY_RATE / _100_PERCENT;

	sn_printf( msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_REQUEST_MBR_CANCEL,
			fmt_gold( penalty ) );
	ask = exec_menu_ask( msg, ASK_NO, TRUE );
	if( ask != ASK_YES )
		return FALSE;

	if( get_party_gold() < penalty ){
		print_msg( FLG_MSG_ERR, MSG_ERR_MENU_REQUEST_MBR_CANCEL,
				fmt_gold( penalty - get_party_gold() ) );
		return FALSE;
	}
	sub_party_gold( penalty );

	not_join_all_client( req, FALSE );

	master_sex = get_npc_sex_shop( SHOP_N_BAR );
	master_name = get_npc_name_shop( SHOP_N_BAR, master_sex );
	print_words_win( master_name, master_sex,
			MSG_WORDS_REQUEST_CANCEL_FEMALE,
			MSG_WORDS_REQUEST_CANCEL_MALE );

	req->flg_contract = FALSE;
	req->flg_contract_mbr = FALSE;

	return TRUE;
}

/***************************************************************
* ����Υꥹ�ȤΥ���ǥå��������å��������Ѵ�
* request_t *req : ����
* return : ��å�����
***************************************************************/

char	*cv_idx_to_request_fmt( request_t *req )
{
	if( req == NULL )
		return( MSG_NULL );
	if( req->idx_fmt <= -1 )
		return( MSG_NULL );

	switch( req->kind ){
	case REQUEST_KIND_NULL:
		return( MSG_NULL );
	case REQUEST_KIND_TAME_MNSTR:
		return( MSG( g_tame_mnstr_tab[req->idx_fmt] ) );
	case REQUEST_KIND_RESCUE:
		return( MSG( g_rescue_tab[req->idx_fmt] ) );
	case REQUEST_KIND_REVENGE:
		return( MSG( g_revenge_tab[req->idx_fmt] ) );
	case REQUEST_KIND_WANTED_CRIMINAL:
		return( MSG( g_wanted_criminal_tab[req->idx_fmt] ) );
	case REQUEST_KIND_RARE_GOODS:
		return( MSG( g_rare_goods_tab[req->idx_fmt] ) );
	case REQUEST_KIND_TOUR_GUIDE:
		return( MSG( g_tour_guide_tab[req->idx_fmt] ) );
	case REQUEST_KIND_EXTERMINATE:
		return( MSG( g_exterminate_tab[req->idx_fmt] ) );
	case REQUEST_KIND_MAX_N:
		return( MSG_NULL );
	}

	return( MSG_NULL );
}

/***************************************************************
* ���������� NPC �Υꥹ�ȤΥ���ǥå������� NPC ��̾�����Ѵ�
* request_t *req : ����
* return : NPC ��̾��
***************************************************************/

char	*cv_idx_to_contract_name( request_t *req )
{
	n_msg_t	n_msg;

	if( req == NULL )
		return( MSG_MNSTR_UNKNOWN );

	if( req->contract_sex == FEMALE ){
		n_msg = g_ls_npc_name_female[req->idx_contract_name];
	} else {
		n_msg = g_ls_npc_name_male[req->idx_contract_name];
	}

	return( MSG( n_msg ) );
}

/***************************************************************
* ������ NPC �Υꥹ�ȤΥ���ǥå������� NPC ��̾�����Ѵ�
* request_t *req : ����
* return : NPC ��̾��
***************************************************************/

char	*cv_idx_to_client_name( request_t *req )
{
	n_msg_t	n_msg;

	if( req == NULL )
		return( MSG_MNSTR_UNKNOWN );

	if( req->client_sex == FEMALE ){
		n_msg = g_ls_npc_name_female[req->idx_client_name];
	} else {
		n_msg = g_ls_npc_name_male[req->idx_client_name];
	}

	return( MSG( n_msg ) );
}

/***************************************************************
* ��󥹥����� NPC �Υꥹ�ȤΥ���ǥå������� NPC ��̾�����Ѵ�
* request_t *req : ����
* return : NPC ��̾��
***************************************************************/

char	*cv_idx_to_mnstr_name( request_t *req )
{
	if( req == NULL )
		return( MSG_MNSTR_UNKNOWN );

	if( req->flg_mnstr_is_npc ){
		n_msg_t	n_msg;

		if( req->mnstr_sex == FEMALE ){
			n_msg = g_ls_npc_name_female[req->idx_mnstr_name];
		} else {
			n_msg = g_ls_npc_name_male[req->idx_mnstr_name];
		}

		return( MSG( n_msg ) );
	} else {
		mnstr_tab_t	*tab;

		tab = get_mnstr_tab( req->mnstr_kind, req->dun_true_lev );

		return( tab->name );
	}

	return( MSG_MNSTR_UNKNOWN );
}

/***************************************************************
* �߽���ɸ�� NPC �Υꥹ�ȤΥ���ǥå������� NPC ��̾�����Ѵ�
* request_t *req : ����
* return : NPC ��̾��
***************************************************************/

char	*cv_idx_to_rescue_trgt_name( request_t *req )
{
	n_msg_t	n_msg;

	if( req == NULL )
		return( MSG_MNSTR_UNKNOWN );

	if( req->rescue_trgt_sex == FEMALE ){
		n_msg = g_ls_npc_name_female[req->idx_rescue_trgt_name];
	} else {
		n_msg = g_ls_npc_name_male[req->idx_rescue_trgt_name];
	}

	return( MSG( n_msg ) );
}

/***************************************************************
* �����β�²�� NPC �Υꥹ�ȤΥ���ǥå������� NPC ��̾�����Ѵ�
* request_t *req : ����
* return : NPC ��̾��
***************************************************************/

char	*cv_idx_to_client_family_name( request_t *req )
{
	n_msg_t	n_msg;

	if( req == NULL )
		return( MSG_MNSTR_UNKNOWN );

	if( req->client_family_sex == FEMALE ){
		n_msg = g_ls_npc_name_female[req->idx_client_family_name];
	} else {
		n_msg = g_ls_npc_name_male[req->idx_client_family_name];
	}

	return( MSG( n_msg ) );
}

/***************************************************************
* ��������֤� NPC �Υꥹ�ȤΥ���ǥå������� NPC ��̾�����Ѵ�
* request_t *req : ����
* return : NPC ��̾��
***************************************************************/

char	*cv_idx_to_client_mate_name( request_t *req )
{
	n_msg_t	n_msg;

	if( req == NULL )
		return( MSG_MNSTR_UNKNOWN );

	if( req->client_mate_sex == FEMALE ){
		n_msg = g_ls_npc_name_female[req->idx_client_mate_name];
	} else {
		n_msg = g_ls_npc_name_male[req->idx_client_mate_name];
	}

	return( MSG( n_msg ) );
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_request_c( void )
{
	check_memory( check_memory_request_c_ls_reward_scroll,
			"request.c: ls_reward_scroll" );
	check_memory( check_memory_request_c_g_request_pre,
			"request.c: g_request pre" );
	check_memory( check_memory_request_c_g_request,
			"request.c: g_request" );
	check_memory( check_memory_request_c_ls_menu_request,
			"request.c: ls_menu_request" );
}
