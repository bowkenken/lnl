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
* $Id: request.c,v 1.121 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* 酒場の依頼
***************************************************************/

#define	REQUEST_C
#include	"inc.h"

/***************************************************************/

/* 依頼をデバッグするか? */
#if	1
# define	FLG_DEBUG_REQUEST	1
#else
# define	FLG_DEBUG_REQUEST	0
#endif

/* 依頼のメニュー・リストのページあたりの項目数 */
#define	MENU_REQUEST_N_PER_PAGE	10

/* 依頼の平均期限 */
#define	REQUEST_RARE_GOODS_AVE_LIMIT	7
#define	REQUEST_TAME_MNSTR_AVE_LIMIT	7
#define	REQUEST_RESCUE_AVE_LIMIT	7
#define	REQUEST_TOUR_GUIDE_AVE_LIMIT	10
#define	REQUEST_EXTERMINATE_AVE_LIMIT	10
#define	REQUEST_REVENGE_AVE_LIMIT	12
#define	REQUEST_WANTED_CRIMINAL_AVE_LIMIT	12

/* 簡単な依頼の階数 */
#define	REQUEST_DUN_MIN_LEV_EASY	1
#define	REQUEST_DUN_MAX_LEV_EASY	50
/* 普通の依頼の階数 */
#define	REQUEST_DUN_MIN_LEV_NORMAL	10
#define	REQUEST_DUN_MAX_LEV_NORMAL	50
/* 依頼の階数の範囲 */
#define	REQUEST_DUN_RANGE_LEV	2
/* 到達階数に加える依頼の階数 */
#define	REQUEST_DUN_ADD_LEV	1

/* NPC が依頼を受ける確率 */
#define	REQUEST_NPC_CONTRACT_RATE	20

/* 探索するアイテムをモンスターが落す確率 */
#define	REQUEST_RARE_GOODS_DROP_RATE	((rate_t)30)

/* キャプモンの依頼のモンスターの平均数 */
#define	REQUEST_TAME_MNSTR_MNSTR_AVE_N	4
/* 観光案内の依頼の倒すべきモンスターの平均数 */
#define	REQUEST_TOUR_GUIDE_MNSTR_AVE_N	4
/* モンスター退治の依頼の倒すべきモンスターの平均数 */
#define	REQUEST_EXTERMINATE_MNSTR_AVE_N	4

/* 他の依頼リストを見る時の手数料 */
#define	REQUEST_REFRESH_PRIZE	((gold_t)(1 * MBR_MAX_N))

/* 依頼名の表示上の文字数 */
#define	REQUEST_NAME_MIN_LEN	14

/***************************************************************
* 依頼の報酬の金と経験値の率
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
* 依頼の報酬のアイテム
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
* グローバル変数
***************************************************************/

/* 依頼のデータ・リスト */
check_memory_def( check_memory_request_c_g_request_pre )
static request_t	g_request[REQUEST_MAX_N];
check_memory_def( check_memory_request_c_g_request )

/* 依頼のメニュー */
static menu_t	ls_menu_request[1 + REQUEST_MAX_N * 2];
check_memory_def( check_memory_request_c_ls_menu_request )

/***************************************************************
* 依頼のテーブル
***************************************************************/

#include	"request-tab.h"

/***************************************************************
* 依頼の初期化
***************************************************************/

void	init_request( void )
{
	long	i;

	for( i = 0; i < REQUEST_MAX_N; i++ )
		g_request[i].kind = REQUEST_KIND_NULL;
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_request( void )
{
}

/***************************************************************
* 依頼を全て創る
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
* 依頼をランダムに創る
* return : 依頼
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
* アイテム探索の依頼を創る
* request_t *req : 依頼の創り先
* return : 依頼
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
* キャプモンの依頼を創る
* request_t *req : 依頼の創り先
* return : 依頼
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
* 救助の依頼を創る
* request_t *req : 依頼の創り先
* return : 依頼
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
* 観光案内の依頼を創る
* request_t *req : 依頼の創り先
* return : 依頼
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
* モンスター退治の依頼を創る
* request_t *req : 依頼の創り先
* return : 依頼
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
* 仇討ちの依頼を創る
* request_t *req : 依頼の創り先
* return : 依頼
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
* 賞金首の依頼を創る
* request_t *req : 依頼の創り先
* return : 依頼
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
* 依頼主の NPC を創る
* request_t *req : 依頼の創り先
* mnstr_kind_t kind : 依頼主の種類
* bool_t flg_now : 今すぐに創るか?(迷宮内で創る場合)
* return : エラーが無かったか?
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

	/* エラーが発生した時だけ偽を返す */
	/* キャラクタを創る必要が無い時はエラーではない */

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
* 依頼の最大階層を到達した事の有る範囲内で返す(低レベル)
* long dun_max_lev : 最大階層
* return : 最大階層
***************************************************************/

long	get_request_dun_max_lev_easy( void )
{
	return get_request_dun_max_lev(
			REQUEST_DUN_MIN_LEV_EASY,
			REQUEST_DUN_MAX_LEV_EASY );
}

/***************************************************************
* 依頼の最大階層を到達した事の有る範囲内で返す(普通のレベル)
* long dun_max_lev : 最大階層
* return : 最大階層
***************************************************************/

long	get_request_dun_max_lev_normal( void )
{
	return get_request_dun_max_lev(
			REQUEST_DUN_MIN_LEV_NORMAL,
			REQUEST_DUN_MAX_LEV_NORMAL );
}

/***************************************************************
* 依頼の最大階層を到達した事の有る範囲内で返す
* long dun_max_lev : 最大階層
* return : 最大階層
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
* 依頼の階層をランダムに設定
* request_t *req : 依頼
* long min_lev : 最小階
* long max_lev : 最大階
* long range_lev : 階層の範囲
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
* リストからメッセージをランダムに選ぶ
* n_msg_t ls[] : リスト
* return : メッセージ
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
* 依頼のメモリーを割り当てる(デフォルト値を設定する)
* return : 依頼
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
* 依頼のメモリーを解放
* request_t *req : 依頼
***************************************************************/

void	free_request( request_t *req )
{
	if( req == NULL )
		return;

	req->kind = REQUEST_KIND_NULL;
}

/***************************************************************
* 依頼のリストを返す
* return : 依頼のリスト
***************************************************************/

request_t	*get_request_ls( void )
{
	return g_request;
}

/***************************************************************
* リストから有効な依頼の数を数える
* return : 依頼の数
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
* 依頼の種類の名前を返す
* request_kind_t kind : 依頼の種類
* return : 依頼の種類の名前
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
* 依頼の期限切れをチェックする
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
* 依頼の期限切れで NPC と別れる
* request_t *req : 依頼
* return : 別れたか?
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
		return TRUE;	/* FALSE ではない */
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

	/* 別れる */

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
* 依頼を NPC が受けたかチェック
***************************************************************/

void	chk_request_npc_contract( void )
{
	chk_clr_request_npc_contract();
	chk_set_request_npc_contract();
}

/***************************************************************
* NPC が受けた依頼を削除
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
* NPC がランダムに依頼を受ける
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
* 依頼のメッセージを生成
* request_t *req : 依頼
* return : エラーが無かったか?
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
* 依頼のメッセージの変数を展開
* request_t *req : 依頼
* char *buf : 展開先
* long *buf_idx : 展開した文字列の末尾
* char *fmt : 変数の先頭位置
* long *fmt_idx : 変数の文字列の末尾
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
* 依頼のメッセージの変数を展開(最小階)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(最大階)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(階層の範囲)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(依頼主)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(探索するアイテム)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(モンスター)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(モンスターの数)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(救助する NPC)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(依頼主の家族)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
		/* 依頼主が男性なら家族は妻等 */
		req->client_family_sex = FEMALE;
	} else {
		/* 依頼主が女性なら家族は夫等 */
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
* 依頼のメッセージの変数を展開(依頼主の仲間)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(時間グループ A)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(時間グループ B)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数を展開(武器)
* request_t *req : 依頼
* char *buf : 展開先
* char *arg : 変数の引数
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
* 依頼のメッセージの変数をリストから展開
* request_t *req : 依頼
* char *buf : 展開先
* n_msg_idx_t *n_msg_idx : リストのインデックス
* n_msg_t ls_msg[] : リスト
* bool_t flg_quote : クオーティングするか?
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
* 依頼のリスト上の見出しを設定
* request_t *req : 依頼
* return : エラーが無かったか?
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
* キャラクタが依頼を引き受ける
* request_t *req : 依頼
* chr_kind_t kind : キャラクタの種類
* n_msg_idx_t n_idx_name : NPC の名前リストのインデックス
* sex_t sex : 性別
* return : エラーが無かったか?
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
* 目標のキャラクタを発見した時の依頼への影響をチェック
* chr_t *chr : 発見されたキャラクタ
***************************************************************/

void	chk_find_request_chr( chr_t *chr )
{
	request_t	*req;
	pet_t	*npc;
	mbr_t	*mbr;
	char	*msg_fema, *msg_male;

	if( chr == NULL )
		return;

	/* 依頼を引き受けているか? */

	req = chr->work.request;
	if( req == NULL )
		return;
	if( !req->flg_contract )
		return;
	if( !req->flg_contract_mbr )
		return;

	/* 発見したキャラクタが依頼者本人だったらぬける */

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
* 依頼を成功する
* request_t *req : 依頼
* return : エラーが無かったか?
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
* 依頼を失敗する
* request_t *req : 依頼
* return : エラーが無かったか?
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
* キャラクタが死んだ時の依頼への影響をチェック
* chr_t *chr : 死んだキャラクタ
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
* キャラクタが死んだ時の依頼への影響をチェック(アイテム探索)
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
* 依頼を達成して NPC がパーティに加わる
* request_t *req : 依頼
* mnstr_t *npc : NPC
* return : NPC がパーティに加わったか?
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
* モンスターが死んだ時の依頼への影響をチェック(モンスター退治)
* mnstr_kind_t mnstr_kind : モンスターの種類
* long add : 倒した数のカウンタに足す数
* request_kind_t req_kind : 依頼の種類
* bool_t flg_dec_add : 
*   TRUE  : 各カウンタに足した数だけ次に足す数を減らす
*   FALSE : 全てのカウンタに同じ数を足す
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
* キャラクタが死んだ時の依頼への影響をチェック(仇討ち)
* request_t *req : 依頼
* return : 依頼が成功したか?
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
* キャラクタが死んだ時の依頼への影響をチェック(賞金首)
* request_t *req : 依頼
* return : 依頼が成功したか?
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
* 成功した全ての依頼を閉じる
* chr_kind_t chr_kind : PC か NPC か?
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
* 成功した依頼を閉じる
* request_t *req : 依頼
* chr_kind_t chr_kind : PC か NPC か?
* return : 依頼が成功したか?
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

	/* アイテムを依頼主に手渡す */

	if( req->kind == REQUEST_KIND_RARE_GOODS ){
		for( i = 0; i < MBR_MAX_N; i++ ){
			if( chk_mbr_have_rare_goods( pty->mbr[i],
					req->rare_goods_kind,
					req->mnstr_kind, TRUE ) ){
			}
		}
	}

	not_join_all_client( req, TRUE );

	/* メッセージを表示 */

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
* ランダムなアイテムを報酬としてパーティに与える
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
* 指定のアイテムを報酬としてパーティに与える
* item_t *item : アイテム
* return : 与えられたか?
***************************************************************/

bool_t	give_party_reward_item( item_t *item )
{
	return give_party_item( item, TRUE, TRUE );
}

/***************************************************************
* 依頼主が目標を倒すのを見ているか?
* request_t *req : 依頼
* return : 見ているか?
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
* 関係する全ての依頼主と別れる
* request_t *req : 依頼
* bool_t flg_success : 依頼が成功したか?
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
* 依頼主と別れる
* request_t *req : 依頼
* pet_t *npc : 依頼主
* bool_t flg_success : 依頼が成功したか?
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
		/* 動物は喋らない */
		break;	/* return ではない */
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
* 依頼のオブジェクトを迷宮に置く
***************************************************************/

void	put_request_all_obj( void )
{
	put_request_item();
	put_request_mnstr();
}

/***************************************************************
* 依頼のレア・グッズを迷宮に置く
* chr_t *chr : レア・グッズを持っていたモンスター
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

		/* 目標のアイテムを生成 */

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
* 依頼のアイテムを迷宮に置く
***************************************************************/

void	put_request_item( void )
{
}

/***************************************************************
* 依頼のモンスターを迷宮に置く
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

		/* 目標のモンスターを生成 */

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
* キャラクタ が依頼関係のペット(NPC)か?
* chr_t *chr : メニュー・リスト
* return : ペット(NPC)か?
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
* パーティが受けている依頼リストのメニューを設定
* menu_t **pp : メニュー・リスト
* menu_t **dflt : メニューのデフォルト項目
* return : メニューの移動先
***************************************************************/

char	*cb_menu_request_mbr( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );

	return( set_menu_request( pp, dflt,
			cb_menu_sel_request_mbr, TRUE ) );
}

/***************************************************************
* 酒場の依頼リストのメニューを設定
* menu_t **pp : メニュー・リスト
* menu_t **dflt : メニューのデフォルト項目
* return : メニューの移動先
***************************************************************/

char	*cb_menu_request_bar( menu_t **pp, menu_t **dflt )
{
	chk_finish_request_rare_goods();
	close_all_request( CHR_KIND_MBR );

	return( set_menu_request( pp, dflt,
			cb_menu_sel_request_bar, FALSE ) );
}

/***************************************************************
* 依頼リストのメニューを設定
* menu_t **pp : メニュー・リスト
* menu_t **dflt : メニューのデフォルト項目
* menu_call_back_t cb : 依頼選択時のコール・バック関数
* bool_t flg_mbr : メンバーが受けている依頼以外スキップするか?
* return : メニューの移動先
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

		/* メンバーが受けている依頼以外スキップする */
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
* パーティが受けている依頼を表示
* menu_t **pp : メニュー・リスト
* menu_t **dflt : メニューのデフォルト項目
* return : メニューの移動先
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
* 酒場の依頼を表示
* menu_t **pp : メニュー・リスト
* menu_t **dflt : メニューのデフォルト項目
* return : メニューの移動先
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
* 依頼のリストをリフレッシュして新しい物と入れ換える
* menu_t **pp : メニュー・リスト
* menu_t **dflt : メニューのデフォルト項目
* return : メニューの移動先
***************************************************************/

char	*cb_menu_request_refresh( menu_t **pp, menu_t **dflt )
{
	ask_t	ask;
	long	i;

	/* プレイヤーに確認する */

	ask = exec_menu_ask( MSG_TTL_MENU_REQUEST_REFRESH_ASK,
			ASK_NO, TRUE );

	if( ask != ASK_YES )
		return STR_MENU_CANCEL;

	/* 依頼のリストをリフレッシュ */

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		if( g_request[i].kind == REQUEST_KIND_NULL )
			continue;

		/* メンバーが受けている依頼はスキップする */
		if( g_request[i].flg_contract
				&& g_request[i].flg_contract_mbr ){
			continue;
		}

		free_request( &(g_request[i]) );
	}

	make_request_all();

	/* 手数料を支払う */

	sub_party_gold( REQUEST_REFRESH_PRIZE );

	return "/bar/request";
}

/***************************************************************
* 依頼を受けるかプレイヤーに選ばせる
* request_t *req : 依頼
* return : 依頼を受けたか?
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
* 依頼をキャンセルするかプレイヤーに選ばせる
* request_t *req : 依頼
* return : 依頼をキャンセルしたか?
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
* 依頼のリストのインデックスからメッセージに変換
* request_t *req : 依頼
* return : メッセージ
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
* 依頼を受けた NPC のリストのインデックスから NPC の名前に変換
* request_t *req : 依頼
* return : NPC の名前
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
* 依頼主の NPC のリストのインデックスから NPC の名前に変換
* request_t *req : 依頼
* return : NPC の名前
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
* モンスターの NPC のリストのインデックスから NPC の名前に変換
* request_t *req : 依頼
* return : NPC の名前
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
* 救助目標の NPC のリストのインデックスから NPC の名前に変換
* request_t *req : 依頼
* return : NPC の名前
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
* 依頼主の家族の NPC のリストのインデックスから NPC の名前に変換
* request_t *req : 依頼
* return : NPC の名前
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
* 依頼主の仲間の NPC のリストのインデックスから NPC の名前に変換
* request_t *req : 依頼
* return : NPC の名前
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
* メモリー・チェック
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
