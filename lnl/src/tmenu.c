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
* $Id: tmenu.c,v 1.169 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#define	TMENU_C
#include	"inc.h"

/**/

/* 階層移動などでメニューをリセットするか? */
#define	FLG_RESET_MENU	0
/* 魔法を使えなくてもギルドに入れるか? */
#define	FLG_CAN_ENTER_MAGIC_GUILD_NOT_LEARNED	TRUE

/* アイテムを店に売った時に識別するか? */
#define	FLG_IDENTIFY_ITEM_SALE	FALSE

#define	ARTICLE_MAX_N_PER_PAGE	10
#define	ARTICLE_PAGE_MAX_N	MENU_MAX_PAGE
#define	ARTICLE_MAX_N	\
		(ARTICLE_MAX_N_PER_PAGE * ARTICLE_PAGE_MAX_N)

#define	LS_MENU_SHOP_MAX_N	\
		(MENU_MAX_N_PER_PAGE * ARTICLE_PAGE_MAX_N)

#define	LS_MBR_MAX_N_PER_PAGE	12
#define	LS_MBR_PAGE_MAX_N	\
		((LS_MBR_MAX_N + LS_MBR_MAX_N_PER_PAGE - 1)\
		/ LS_MBR_MAX_N_PER_PAGE)

#define	ORDER_MILK_HIGH_LEV	30

/**/

#include	"tmenu-tab.h"

/**/

static mbr_t	*g_sel_mbr, *g_sel_ls_mbr;
check_memory_def( check_memory_tmenu_c_g_sel_mbr )

static shop_n_t	g_shop_n;
static deal_kind_t	g_deal_kind;
static item_t	*g_sel_art;
static long	g_sel_class_n;
check_memory_def( check_memory_tmenu_c_g_shop_n )

static item_t	*g_mbr_order[MBR_MAX_N];
check_memory_def( check_memory_tmenu_c_g_mbr_order )

static menu_t	*g_navi_dflt;
check_memory_def( check_memory_tmenu_c_g_navi_dflt )

/**/

static edit_class_t	static_exec_edit_class__n;
static edit_skill_t	static_exec_edit_skill__n;
check_memory_def( check_memory_tmenu_c_static_exec_edit_class__n )

skill_kind_t	g_sel_skill_kind;
edit_skill_t	g_skill_slot_n;
check_memory_def( check_memory_tmenu_c_g_sel_skill_kind  )

/**/

void	init_town_menu( void )
{
	party_t	*pty = get_party();
	mbr_t	**ls_mbr = get_ls_mbr();

	g_sel_mbr = pty->mbr[0];
	g_sel_ls_mbr = ls_mbr[0];
	g_sel_art = NULL;
	g_sel_class_n = 0;

	g_navi_dflt = NULL;

	g_sel_skill_kind = SKILL_KIND_NULL;
	g_skill_slot_n = EDIT_SKILL_NEXT;
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_town_menu( void )
{
	long	i;

#if	FLG_RESET_MENU
	{
		party_t	*pty = get_party();
		mbr_t	**ls_mbr = get_ls_mbr();
		g_sel_mbr = pty->mbr[0];
		g_sel_ls_mbr = ls_mbr[0];
	}
#endif
	g_shop_n = SHOP_N_NULL;
	g_deal_kind = DEAL_KIND_BUY;
	g_sel_art = NULL;
	g_sel_class_n = 0;

	for( i = 0; i < MBR_MAX_N; i++ )
		g_mbr_order[i] = NULL;

#if	FLG_RESET_MENU
	g_navi_dflt = NULL;
#endif

	/**/

	static_exec_edit_class__n = EDIT_CLASS_NEXT;
	static_exec_edit_skill__n = EDIT_SKILL_NEXT;
}

/**/

char	*menu_shop_sel_mbr( shop_n_t shop_n, bool_t flg_pet )
{
	bool_t	flg_sel_dead;

	g_shop_n = shop_n;
	g_deal_kind = DEAL_KIND_BUY;

	if( g_shop_n == SHOP_N_TEMPLE )
		flg_sel_dead = TRUE;
	else
		flg_sel_dead = FALSE;

	while( 1 ){
		char	ttl[MENU_MSG_MAX_BYTE + 1];
		char	*str_goto;

		sn_printf( ttl, MENU_MSG_MAX_BYTE, MSG_MENU_SHOP_SEL_MBR,
				get_shop_name( g_shop_n ) );

		str_goto = exec_menu_sel_mbr(
				&g_sel_mbr, ttl, flg_sel_dead, flg_pet );
		if( str_goto != NULL )
			return str_goto;

		while( 1 ){
			switch( g_shop_n ){
			case SHOP_N_NULL:
			case SHOP_N_MAX_N:
			case SHOP_N_INN:
			case SHOP_N_BAR:
			case SHOP_N_RESTAURANT:
				return STR_MENU_ERR;
			case SHOP_N_MAGIC:
				str_goto = exec_menu( ls_menu_magic_guild,
						NULL, str_goto );
				break;
			case SHOP_N_TEMPLE:
				str_goto = exec_menu( ls_menu_temple,
						NULL, str_goto );
				break;
			case SHOP_N_WPN:
			case SHOP_N_ARMOR:
			case SHOP_N_ALCHEMY:
			case SHOP_N_MUSIC:
			case SHOP_N_GROCERY:
			case SHOP_N_TEAROOM:
			case SHOP_N_TOBACCO:
				str_goto = menu_shop( g_shop_n, g_sel_mbr,
						str_goto );
				break;
			case SHOP_N_PET_SHOP:
				str_goto = exec_menu( ls_menu_pet_shop,
						NULL, str_goto );
				break;
			}

			if( str_goto == NULL )
				continue;
			if( strcmp( str_goto, STR_MENU_ERR ) == 0 )
				break;
			if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
				break;
		}
	}

	return STR_MENU_ERR;
}

/**/

char	*cb_menu_temple_init( menu_t **pp, menu_t **dflt )
{
	long	len, max_len;
	menu_t	*p;
	gold_t	price;

	max_len = 1;
	for( p = *pp; p->path[0] != '\0'; p++ ){
		if( strcmp( p->kind, "<Item>" ) != 0 )
			continue;

		max_len = max_l( max_len, str_len_draw( MSG( p->n_msg ) ) );
	}

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE, MSG_TTL_MENU_TEMPLE,
			get_shop_name( SHOP_N_TEMPLE ),
			g_sel_mbr->name, fmt_gold( g_sel_mbr->gold ) );

	price = get_price_temple_remove_curse( g_sel_mbr );
	p = srch_menu( *pp, "remove curse" );
	if( p == NULL )
		return STR_MENU_ERR;
	len = get_pading_len( MSG( p->n_msg ), max_len );
	sn_printf( p->msg, MENU_MSG_MAX_BYTE, MSG_FMT_MENU_TEMPLE,
			len, MSG( p->n_msg ), fmt_gold( price ) );

	price = get_price_temple_cure_status( g_sel_mbr );
	p = srch_menu( *pp, "cure status" );
	if( p == NULL )
		return STR_MENU_ERR;
	len = get_pading_len( MSG( p->n_msg ), max_len );
	sn_printf( p->msg, MENU_MSG_MAX_BYTE, MSG_FMT_MENU_TEMPLE,
			len, MSG( p->n_msg ), fmt_gold( price ) );

	price = get_price_temple_resurrection( g_sel_mbr );
	p = srch_menu( *pp, "resurrection" );
	if( p == NULL )
		return STR_MENU_ERR;
	len = get_pading_len( MSG( p->n_msg ), max_len );
	sn_printf( p->msg, MENU_MSG_MAX_BYTE, MSG_FMT_MENU_TEMPLE,
			len, MSG( p->n_msg ), fmt_gold( price ) );

	return NULL;
}

/**/

char	*cb_menu_temple_remove_curse( menu_t **pp, menu_t **dflt )
{
	gold_t	price;
	chr_t	*chr_pay;
	ask_t	ask;

	price = get_price_temple_remove_curse( g_sel_mbr );
	if( is_pet( g_sel_mbr ) )
		chr_pay = g_sel_mbr->owner;
	else
		chr_pay = g_sel_mbr;
	if( !chk_pay( chr_pay, price ) )
		return STR_MENU_CANCEL;

	ask = exec_menu_ask( MSG_TTL_MENU_TEMPLE_REMOVE_CURSE,
			ASK_NO, TRUE );

	switch( ask ){
	case ASK_YES:
		break;
	case ASK_NO:
		return STR_MENU_CANCEL;
	case ASK_CANCEL:
		return STR_MENU_CANCEL;
	case ASK_ERR:
		return STR_MENU_ERR;
	}

	call_game_music_play( MUSIC_KIND_EFFECT, ME_KIND_TEMPLE );

	if( remove_curse( NULL, g_sel_mbr, 0 ) ){
		paying_gold( chr_pay, price );

		print_msg( FLG_NULL,
				MSG_MENU_REMOVE_CURSE,
				g_sel_mbr->name );
	} else {
		print_msg( FLG_MSG_ERR,
				MSG_MENU_REMOVE_CURSE_ERR,
				g_sel_mbr->name );
	}

	return "/temple";
}

/**/

char	*cb_menu_temple_cure_status( menu_t **pp, menu_t **dflt )
{
	gold_t	price;
	chr_t	*chr_pay;
	ask_t	ask;

	price = get_price_temple_cure_status( g_sel_mbr );
	if( is_pet( g_sel_mbr ) )
		chr_pay = g_sel_mbr->owner;
	else
		chr_pay = g_sel_mbr;
	if( !chk_pay( chr_pay, price ) )
		return STR_MENU_CANCEL;

	ask = exec_menu_ask( MSG_TTL_MENU_TEMPLE_CURE_STATUS,
			ASK_NO, TRUE );

	switch( ask ){
	case ASK_YES:
		break;
	case ASK_NO:
		return STR_MENU_CANCEL;
	case ASK_CANCEL:
		return STR_MENU_CANCEL;
	case ASK_ERR:
		return STR_MENU_ERR;
	}

	call_game_music_play( MUSIC_KIND_EFFECT, ME_KIND_TEMPLE );

	if( fx_cure_all_stat( g_sel_mbr ) ){
		paying_gold( chr_pay, price );

		print_msg( FLG_NULL,
				MSG_MENU_CURE_STATUS,
				g_sel_mbr->name );
	} else {
		print_msg( FLG_MSG_ERR,
				MSG_MENU_CURE_STATUS_ERR,
				g_sel_mbr->name );
	}

	return "/temple";
}

/**/

char	*cb_menu_temple_resurrection( menu_t **pp, menu_t **dflt )
{
	gold_t	price;
	chr_t	*chr_pay;
	ask_t	ask;

	if( g_sel_mbr == NULL )
		return STR_MENU_ERR;
	if( chk_flg( g_sel_mbr->stat, FLG_STAT_NOT_EXIST ) )
		return STR_MENU_ERR;

	price = get_price_temple_resurrection( g_sel_mbr );
	if( is_pet( g_sel_mbr ) )
		chr_pay = g_sel_mbr->owner;
	else
		chr_pay = g_sel_mbr;
	if( !chk_pay( chr_pay, price ) )
		return STR_MENU_CANCEL;

	ask = exec_menu_ask( MSG_TTL_MENU_TEMPLE_RESURRECTION,
			ASK_NO, TRUE );

	switch( ask ){
	case ASK_YES:
		break;
	case ASK_NO:
		return STR_MENU_CANCEL;
	case ASK_CANCEL:
		return STR_MENU_CANCEL;
	case ASK_ERR:
		return STR_MENU_ERR;
	}

	call_game_music_play( MUSIC_KIND_EFFECT, ME_KIND_TEMPLE );

	if( !chk_flg( g_sel_mbr->stat, FLG_STAT_DEAD ) ){
		print_msg( FLG_MSG_ERR,
				MSG_MENU_RESURRECTION_ERR,
				g_sel_mbr->name );
		return STR_MENU_CANCEL;
	}

	fx_resurrection( g_sel_mbr, FALSE );

	/* 生き返らなくても支払う */
	paying_gold( chr_pay, price );

	return "/temple";
}

/**/

char	*cb_menu_temple_contribution( menu_t **pp, menu_t **dflt )
{
	gold_t	price, spell_price;
	chr_t	*chr_pay;
	char	*str_goto;
	ask_t	ask;

	if( g_sel_mbr->gold <= 0 )
		return STR_MENU_CANCEL;

	spell_price = get_price_temple_contribution( g_sel_mbr );
	price = spell_price;

	str_goto = exec_menu_sel_num( &price, 1, g_sel_mbr->gold );
	if( str_goto != NULL )
		return str_goto;

	if( is_pet( g_sel_mbr ) )
		chr_pay = g_sel_mbr->owner;
	else
		chr_pay = g_sel_mbr;
	if( !chk_pay( chr_pay, price ) )
		return STR_MENU_CANCEL;

	ask = exec_menu_ask( MSG_TTL_MENU_TEMPLE_CONTRIBUTION,
			ASK_NO, TRUE );

	switch( ask ){
	case ASK_YES:
		break;
	case ASK_NO:
		return STR_MENU_CANCEL;
	case ASK_CANCEL:
		return STR_MENU_CANCEL;
	case ASK_ERR:
		return STR_MENU_ERR;
	}

	call_game_music_play( MUSIC_KIND_EFFECT, ME_KIND_TEMPLE );

	paying_gold( chr_pay, price );
	print_msg( FLG_NULL, MSG_MENU_CONTRIBUTION,
			g_sel_mbr->name, fmt_gold( price ) );
	contribution( g_sel_mbr, price, spell_price );

	return "/temple";
}

/**/

char	*menu_restaurant( void )
{
	g_shop_n = SHOP_N_RESTAURANT;

	return menu_order();
}

/**/

bool_t	chk_shop_order( shop_n_t shop_n )
{
	if( shop_n == SHOP_N_BAR )
		return TRUE;
	if( shop_n == SHOP_N_RESTAURANT )
		return TRUE;

	return FALSE;
}

/**/

char	*menu_order( void )
{
	long	i;
	char	*str_goto;

	g_sel_mbr = NULL;
	g_sel_art = NULL;

	for( i = 0; i < MBR_MAX_N; i++ )
		g_mbr_order[i] = NULL;

	while( 1 ){
		next_g_sel_mbr( FALSE );

		str_goto = menu_order_sel_mbr();
		if( str_goto != NULL ){
			if( strcmp( str_goto, STR_MENU_ERR ) == 0 )
				return NULL;
			if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
				return NULL;
		}
	}

	return STR_MENU_ERR;
}

/**/

char	*menu_order_sel_mbr( void )
{
	party_t	*pty = get_party();
	mbr_t	**mbr;
	menu_t	*p, *dflt;
	long	mbr_n;
	long	i, k;

	p = ls_menu_order_sel_mbr;
	dflt = NULL;

	mbr = pty->mbr;
	mbr_n = 0;
	k = 0;

	str_nz_cpy( p[k].path, "/order", MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	p[k].accel_key = '\0';
	p[k].short_key[0] = '\0';
	p[k].msg[0] = '\0';
	p[k].call_back = NULL;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( p[k].path, "/order/--", MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	p[k].accel_key = '\0';
	p[k].short_key[0] = '\0';
	str_nz_cpy( p[k].msg, MSG_TTL_MENU_ORDER, MENU_MSG_MAX_BYTE );
	p[k].call_back = NULL;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MBR_MAX_N; i++ ){
		char	*name;

		if( chk_flg_or( mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD
				| FLG_STAT_STONE | FLG_STAT_PARALYZE
				| FLG_STAT_CONFUSION | FLG_STAT_SLEEP
				| FLG_STAT_FEAR | FLG_STAT_HALLUCINATION ) ){
			continue;
		}

		if( (g_sel_mbr != NULL) && (g_sel_mbr->mbr_n == i) )
			dflt = &(p[k]);

		sn_printf( p[k].path, MENU_PATH_MAX_LEN, "/order/%ld", i );
		str_nz_cpy( p[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		p[k].accel_key = (char)('A' + i);
		p[k].short_key[0] = '\0';
		if( g_mbr_order[i] == NULL )
			name = MSG_MENU_ORDER_NULL;
		else
			name = g_mbr_order[i]->name;
		sn_printf( p[k].msg, MENU_MSG_MAX_BYTE,
				MSG_MENU_ORDER_MBR, mbr[i]->name, name );
		p[k].call_back = cb_menu_order_sel;
		p[k].arg = mbr[i];
		p[k].flg = FLG_NULL;
		k++;

		mbr_n++;
	}

	if( g_sel_mbr == NULL )
		dflt = &(p[k]);

	str_nz_cpy( p[k].path, "/order/chose", MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
	p[k].accel_key = 'Z';
	p[k].short_key[0] = '\0';
	str_nz_cpy( p[k].msg, MSG_MENU_ORDER_CHOSE, MENU_MSG_MAX_BYTE );
	p[k].call_back = cb_menu_order_chose;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	p[k].path[0] = '\0';

	if( mbr_n <= 0 ){
		print_msg( FLG_MSG_ERR, MSG_ERR_MENU_NOT_EXIST_MBR );
		return STR_MENU_ERR;
	}

	return exec_menu( p, dflt, NULL );
}

/**/

char	*cb_menu_order_sel( menu_t **pp, menu_t **dflt )
{
	char	*str_goto;

	g_sel_mbr = (mbr_t *)((*pp)->arg);

	str_goto = menu_shop( g_shop_n, g_sel_mbr, NULL );
	if( str_goto != NULL )
		if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
			return STR_MENU_CANCEL;

	if( g_sel_mbr == NULL )
		return STR_MENU_ERR;

	g_mbr_order[g_sel_mbr->mbr_n] = g_sel_art;
	return str_goto;
}

/**/

void	next_g_sel_mbr( bool_t flg_loop )
{
	party_t	*pty;
	long	n, m;
	long	i;

	pty = get_party();
	if( g_sel_mbr == NULL )
		n = 0;
	else
		n = g_sel_mbr->mbr_n + 1;

	for( i = 0; i < MBR_MAX_N; i++ ){
		m = n + i;
		if( !flg_loop && (m >= MBR_MAX_N) )
			break;
		m %= MBR_MAX_N;

		if( chk_flg_or( pty->mbr[m]->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD ) ){
			continue;
		}

		g_sel_mbr = pty->mbr[m];
		return;
	}

	g_sel_mbr = NULL;
}

/**/

char	*cb_menu_order_chose( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	bool_t	flg_rumor;
	long	i;

	g_sel_mbr = NULL;

	flg_rumor = FALSE;

	for( i = 0; i < MBR_MAX_N; i++ ){
		item_t	*item, *tmp;
		gold_t	price;

		item = g_mbr_order[i];
		if( item == NULL )
			continue;
		else
			flg_rumor = TRUE;

		price = get_price( g_shop_n, item, DEAL_KIND_BUY );
		if( !chk_pay( pty->mbr[i], price ) )
			continue;

		paying_gold( pty->mbr[i], price );
		call_game_sound_play( SOUND_KIND_SHOP_BUY_DRINK, 2 );

		tmp = alloc_item();
		if( tmp == NULL )
			return STR_MENU_ERR;
		copy_item( tmp, item );
		tmp->stock = 1;

		pty->mbr[i]->x = 1;
		pty->mbr[i]->y = 1;
		if( tmp->kind == ITEM_KIND_FOOD ){
			eat_food( pty->mbr[i], tmp );
		} else if( tmp->kind == ITEM_KIND_POTION ){
			quaff_potion( pty->mbr[i], tmp, TRUE );
			chk_order_milk( pty->mbr[i], g_shop_n, item );
		}
		pty->mbr[i]->x = MAP_DEL_X;
		pty->mbr[i]->y = MAP_DEL_Y;

		item->stock--;
		if( item->stock <= 0 )
			inc_item( item, -item->n );

		g_mbr_order[i] = NULL;
	}

	if( flg_rumor )
		hear_rumor( g_shop_n );

	return "/order";
}

/**/

bool_t	chk_order_milk( mbr_t *mbr, shop_n_t shop_n, item_t *item )
{
	sex_t	sex;

	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( mbr->sex.cur != MALE )
		return FALSE;
	if( shop_n != SHOP_N_BAR )
		return FALSE;
	if( item->dat.potion.kind != POTION_KIND_MILK )
		return FALSE;

	/* 笑われる */

	if( rate_randm( (rate_t)50 ) )
		sex = FEMALE;
	else
		sex = MALE;

	print_words( MSG_NPC_NAME_BAR_CUSTOMER, sex,
			MSG_WORDS_ORDER_MILK_FEMALE,
			MSG_WORDS_ORDER_MILK_MALE );

	/* 高レベルのメッセージ */

	if( get_specialist_lev( mbr ) < ORDER_MILK_HIGH_LEV )
		return TRUE;

	if( rate_randm( (rate_t)50 ) )
		sex = FEMALE;
	else
		sex = MALE;

	print_words( MSG_NPC_NAME_BAR_CUSTOMER, sex,
			MSG_WORDS_ORDER_MILK_HIGH_LEV_FEMALE,
			MSG_WORDS_ORDER_MILK_HIGH_LEV_MALE );

	return TRUE;
}

/**/

char	*menu_shop( shop_n_t shop_n, mbr_t *mbr, char *str_goto )
{
	menu_t	*ls, *dflt;
	long	page;
	long	i, j, k;
	long	key_n;
	item_t	*art_head, *art;
	long	ls_art_n;
	static item_t	*ls_art[ARTICLE_MAX_N];
	char	*buy_sale;
	long	len, max_len;

	if( mbr == NULL )
		return STR_MENU_ERR;

	art_head = get_begin_article( mbr, shop_n, g_deal_kind );
	if( art_head == NULL )
		return STR_MENU_ERR;

	if( g_deal_kind == DEAL_KIND_BUY )
		buy_sale = MSG_BUY;
	else if( g_deal_kind == DEAL_KIND_SALE_ITEM )
		buy_sale = MSG_SALE_ITEM;
	else if( g_deal_kind == DEAL_KIND_SALE_EQUIP )
		buy_sale = MSG_SALE_EQUIP;
	else
		buy_sale = MSG_NULL;

	ls = ls_menu_shop;
	dflt = NULL;
	k = 0;

	str_nz_cpy( ls[k].path, "/shop", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	max_len = 0;
	ls_art_n = 0;
	key_n = 0;
	page = 0;
	for( art = art_head;
			!chk_end_article( art, art_head, g_deal_kind );
			art = get_next_article( art, g_deal_kind ) ){
		if( art == NULL )
			break;
		if( page >= ARTICLE_PAGE_MAX_N )
			break;
		if( art->kind == ITEM_KIND_NULL )
			continue;
		if( !chk_deal_article( art, shop_n, g_deal_kind ) )
			continue;

		if( key_n == 0 ){
			str_nz_cpy( ls[k].path, "/shop/--",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[k].kind, "<Title>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = '\0';
			ls[k].short_key[0] = '\0';
			sn_printf( ls[k].msg,
					MENU_MSG_MAX_BYTE,
					MSG_FMT_MENU_SHOP,
					get_shop_name( shop_n ),
					mbr->name, buy_sale,
					fmt_gold( get_chr_gold( mbr ) ) );
			ls[k].call_back = NULL;
			ls[k].arg = NULL;
			ls[k].flg = FLG_NULL;
			k++;
		}

		set_art_name( mbr, art, g_deal_kind );
		ls_art[ls_art_n] = art;
		ls_art_n++;

		len = str_len_draw( art->art_name );
		max_len = max_l( len, max_len );

		/* menu */

		if( art == g_sel_art )
			dflt = &(ls[k]);

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/shop/%ld", key_n );
		str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + key_n);
		ls[k].short_key[0] = '\0';
		ls[k].msg[0] = '\0';
		ls[k].call_back = cb_menu_shop;
		ls[k].arg = (void *)art;
		ls[k].flg = FLG_NULL;
		k++;

		key_n++;

		if( ls_art_n >= ((page + 1) * ARTICLE_MAX_N_PER_PAGE) ){
			set_ls_menu_shop( &k, g_deal_kind );
			page++;
			key_n = 0;
		}
	}

	if( (ls_art_n != (page * ARTICLE_MAX_N_PER_PAGE)) || page == 0 ){
		str_nz_cpy( ls[k].path, "/shop/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( ls[k].kind, "<Title>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = '\0';
		ls[k].short_key[0] = '\0';
		sn_printf( ls[k].msg,
				MENU_MSG_MAX_BYTE,
				MSG_FMT_MENU_SHOP,
				get_shop_name( shop_n ),
				mbr->name, buy_sale,
				fmt_gold( get_chr_gold( mbr ) ) );
		ls[k].call_back = NULL;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		set_ls_menu_shop( &k, g_deal_kind );
	}

	ls[k].path[0] = '\0';

	/* 商品名に値段をつける */

	for( i = 0, j = 0; i < k; i++ ){
		gold_t	price;
		const char	*str_gold;
		long	len;

		if( ls[i].arg == NULL )
			continue;

		price = get_price( g_shop_n, ls_art[j], g_deal_kind );
		str_gold = fmt_gold( price );
		len = get_pading_len( ls_art[j]->art_name, max_len );

		sn_printf( ls[i].msg,
				MENU_MSG_MAX_BYTE,
				MSG_FMT_ART_NAME,
				len, ls_art[j]->art_name,
				str_gold );
		j++;
	}

	return exec_menu( ls, dflt, str_goto );
}

/**/

void	set_ls_menu_shop( long *k, deal_kind_t deal_kind )
{
	menu_t	*ls;

	ls = ls_menu_shop;

	/* Data */

	str_nz_cpy( ls[*k].path, "/shop/data", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[*k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[*k].accel_key = 'T';
	ls[*k].short_key[0] = '\0';
	str_nz_cpy( ls[*k].msg, MSG_MENU_SHOP_DATA, MENU_MSG_MAX_BYTE );
	ls[*k].call_back = cb_menu_shop_data;
	ls[*k].arg = NULL;
	ls[*k].flg = FLG_NULL;
	(*k)++;

	/* Collect gold */

	str_nz_cpy( ls[*k].path, "/shop/collect gold", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[*k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[*k].accel_key = 'U';
	ls[*k].short_key[0] = '\0';
	str_nz_cpy( ls[*k].msg, MSG_MENU_SHOP_COLLECT_GOLD,
			MENU_MSG_MAX_BYTE );
	ls[*k].call_back = cb_menu_shop_collect_gold;
	ls[*k].arg = NULL;
	ls[*k].flg = FLG_NULL;
	(*k)++;

	/* Divide gold */

	str_nz_cpy( ls[*k].path, "/shop/divide gold", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[*k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[*k].accel_key = 'V';
	ls[*k].short_key[0] = '\0';
	str_nz_cpy( ls[*k].msg, MSG_MENU_SHOP_DIVIDE_GOLD,
			MENU_MSG_MAX_BYTE );
	ls[*k].call_back = cb_menu_shop_divide_gold;
	ls[*k].arg = NULL;
	ls[*k].flg = FLG_NULL;
	(*k)++;

	/* Give gold */

	str_nz_cpy( ls[*k].path, "/shop/give gold", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[*k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[*k].accel_key = 'W';
	ls[*k].short_key[0] = '\0';
	str_nz_cpy( ls[*k].msg, MSG_MENU_SHOP_GIVE_GOLD,
			MENU_MSG_MAX_BYTE );
	ls[*k].call_back = cb_menu_shop_give_gold;
	ls[*k].arg = NULL;
	ls[*k].flg = FLG_NULL;
	(*k)++;

	if( !chk_shop_order( g_shop_n ) ){
		/* Sale equip */
		if( g_deal_kind != DEAL_KIND_SALE_EQUIP ){
			str_nz_cpy( ls[*k].path, "/shop/sale equip",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[*k].kind, "<Item>",
					MENU_KIND_MAX_LEN );
			ls[*k].accel_key = 'X';
			ls[*k].short_key[0] = '\0';
			str_nz_cpy( ls[*k].msg, MSG_MENU_SHOP_SALE_EQUIP,
					MENU_MSG_MAX_BYTE );
			ls[*k].call_back = cb_menu_shop_sale_equip;
			ls[*k].arg = NULL;
			ls[*k].flg = FLG_NULL;
			(*k)++;
		}

		/* Sale item */
		if( g_deal_kind != DEAL_KIND_SALE_ITEM ){
			str_nz_cpy( ls[*k].path, "/shop/sale item",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[*k].kind, "<Item>",
					MENU_KIND_MAX_LEN );
			ls[*k].accel_key = 'Y';
			ls[*k].short_key[0] = '\0';
			str_nz_cpy( ls[*k].msg, MSG_MENU_SHOP_SALE_ITEM,
					MENU_MSG_MAX_BYTE );
			ls[*k].call_back = cb_menu_shop_sale_item;
			ls[*k].arg = NULL;
			ls[*k].flg = FLG_NULL;
			(*k)++;
		}

		/* Buy */
		if( g_deal_kind != DEAL_KIND_BUY ){
			str_nz_cpy( ls[*k].path, "/shop/buy",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[*k].kind, "<Item>",
					MENU_KIND_MAX_LEN );
			ls[*k].accel_key = 'Z';
			ls[*k].short_key[0] = '\0';
			str_nz_cpy( ls[*k].msg, MSG_MENU_SHOP_BUY,
					MENU_MSG_MAX_BYTE );
			ls[*k].call_back = cb_menu_shop_buy;
			ls[*k].arg = NULL;
			ls[*k].flg = FLG_NULL;
			(*k)++;
		}
	}

	/* <PageSeparator> */

	str_nz_cpy( ls[*k].path, "/shop/--", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[*k].kind, "<PageSeparator>", MENU_KIND_MAX_LEN );
	ls[*k].accel_key = '\0';
	ls[*k].short_key[0] = '\0';
	ls[*k].msg[0] = '\0';
	ls[*k].call_back = NULL;
	ls[*k].arg = NULL;
	ls[*k].flg = FLG_NULL;
	(*k)++;
}

/**/

char	*cb_menu_shop_data( menu_t **pp, menu_t **dflt )
{
	return menu_town_mbr_data( MBR_DATA_EDIT_KIND_SHOW, FALSE );
}

/**/

char	*menu_town_mbr_data(
	mbr_data_edit_kind_t edit_kind,
	bool_t flg_ls_mbr
)
{
	mbr_t	**ls_mbr;
	mbr_t	**mbr;
	pet_t	**pet;
	chr_t	*chr;
	long	n;
	long	page_n;
	data_n_t	data_n;

	if( is_pet( g_sel_mbr ) )
		n = MBR_MAX_N + get_pet_n( g_sel_mbr );
	else if( flg_ls_mbr )
		n = g_sel_ls_mbr->ls_mbr_n;
	else
		n = g_sel_mbr->mbr_n;

	ls_mbr = get_ls_mbr();
	mbr = get_party()->mbr;
	pet = get_party_pet();

	if( n <= -1 )
		return STR_MENU_ERR;

	page_n = 0;
	data_n = DATA_N_NEXT_PAGE;

	while( 1 ){
		long	add;
		long	prev_mbr_n;

		if( flg_ls_mbr ){
			prev_mbr_n = ls_mbr[n]->mbr_n;
			not_join_mbr( n, prev_mbr_n );
		}

		if( flg_ls_mbr ){
			chr = ls_mbr[n];
		} else {
			if( n < MBR_MAX_N ){
				chr = mbr[n];
			} else {
				chr = pet[n - MBR_MAX_N];
			}
		}

		add = menu_mbr_data( chr, &page_n, &data_n, edit_kind );

		if( flg_ls_mbr )
			join_mbr( n, prev_mbr_n );
		if( add == 0 )
			break;

		/* メンバー・リストの頭出し */
		if( flg_ls_mbr )
			n = next_ls_mbr( n, add );
		else
			n = next_mbr( n, add );
	}

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_pet_shop_data( menu_t **pp, menu_t **dflt )
{
	return menu_town_pet_data();
}

/**/

char	*menu_town_pet_data( void )
{
	pet_t	**ls_pet;
	chr_t	*chr;
	long	n;
	long	add;
	long	page_n;
	data_n_t	data_n;

	ls_pet = get_ls_pet();

	n = MBR_MAX_N;
	add = +1;
	page_n = 0;
	data_n = DATA_N_NEXT_PAGE;

	while( 1 ){
		/* ペット・リストの頭出し */

		n = next_ls_pet_n( n - MBR_MAX_N, add );
		if( ls_pet[n] == NULL )
			break;
		if( chk_flg( ls_pet[n]->stat, FLG_STAT_NOT_EXIST ) )
			break;
		n += MBR_MAX_N;

		/* データ表示 */

		chr = ls_pet[n - MBR_MAX_N];
		add = menu_mbr_data( chr, &page_n, &data_n,
				MBR_DATA_EDIT_KIND_SHOW );
		if( add == 0 )
			return STR_MENU_CANCEL;
	}

	print_msg( FLG_MSG_ERR, MSG_ERR_MENU_PET_SHOP_DATA );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_shop_collect_gold( menu_t **pp, menu_t **dflt )
{
	collect_gold( g_sel_mbr );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_shop_divide_gold( menu_t **pp, menu_t **dflt )
{
	divide_gold();

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_shop_give_gold( menu_t **pp, menu_t **dflt )
{
	menu_mbr_give_gold( g_sel_mbr );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_shop( menu_t **pp, menu_t **dflt )
{
	item_t	*art;
	gold_t	price;
	long	n, deal_n;

	art = (item_t *)((*pp)->arg);
	g_sel_art = art;

	if( chk_shop_order( g_shop_n ) )
		return "/order";

	chk_item_data( g_sel_art );

	price = get_price( g_shop_n, art, g_deal_kind );
	if( price <= 0 ){
		if( (g_deal_kind == DEAL_KIND_SALE_ITEM)
				|| (g_deal_kind == DEAL_KIND_SALE_EQUIP) ){
			print_msg( FLG_MSG_ERR, MSG_NO_DEAL, art->art_name );
			return STR_MENU_CANCEL;
		}
	}

	n = art->n;

	if( g_deal_kind == DEAL_KIND_BUY ){
		deal_n = menu_shop_buy( g_shop_n, g_sel_mbr, art );
		if( deal_n <= 0 )
			return STR_MENU_CANCEL;

		paying_gold( g_sel_mbr, price * deal_n / n );
		call_game_sound_play( SOUND_KIND_SHOP_BUY, 1 );

	} else if( g_deal_kind == DEAL_KIND_SALE_ITEM ){
		deal_n = menu_shop_sale_item( g_shop_n, g_sel_mbr, art );
		if( deal_n <= 0 )
			return STR_MENU_CANCEL;

		paid_gold( g_sel_mbr, price * deal_n / n );
		call_game_sound_play( SOUND_KIND_SHOP_SALE, 1 );

	} else if( g_deal_kind == DEAL_KIND_SALE_EQUIP ){
		deal_n = menu_shop_sale_equip( g_shop_n, g_sel_mbr, art );
		if( deal_n <= 0 )
			return STR_MENU_CANCEL;

		paid_gold( g_sel_mbr, price * deal_n / n );
		call_game_sound_play( SOUND_KIND_SHOP_SALE, 1 );
	}

	return "/shop";
}

/**/

char	*cb_menu_shop_buy( menu_t **pp, menu_t **dflt )
{
	g_deal_kind = DEAL_KIND_BUY;

	return NULL;
}

/**/

char	*cb_menu_shop_sale_item( menu_t **pp, menu_t **dflt )
{
	g_deal_kind = DEAL_KIND_SALE_ITEM;

	return NULL;
}

/**/

char	*cb_menu_shop_sale_equip( menu_t **pp, menu_t **dflt )
{
	g_deal_kind = DEAL_KIND_SALE_EQUIP;

	return NULL;
}

/**/

long	menu_shop_buy(
	shop_n_t g_shop_n, mbr_t *g_sel_mbr, item_t *item
)
{
	ask_t	ask;
	item_t	*tmp;
	gold_t	price;
	long	n;

	price = get_price( g_shop_n, item, DEAL_KIND_BUY );

	/* 商品名を表示 */
	print_msg( FLG_NULL, MSG_MENU_BUY, item->name );
	if( !chk_pay( g_sel_mbr, price ) )
		return 0;

	/* 本当に買うか確認 */
	ask = exec_menu_ask_no_msg( MSG_TTL_MENU_BUY, ASK_NO, TRUE );
	switch( ask ){
	case ASK_YES:
		break;
	case ASK_NO:
	case ASK_CANCEL:
	case ASK_ERR:
		return 0;
	}

	n = item->n;

	tmp = alloc_item();
	if( tmp == NULL )
		return 0;
	copy_item( tmp, item );
	tmp->stock = 1;

	if( !give_mbr_item( g_sel_mbr, tmp, FALSE ) )
		return 0;

	item->stock--;
	if( item->stock <= 0 )
		inc_item( item, -item->n );

	print_msg( FLG_MSG_NO_MORE,
			MSG_MENU_REACHED_BUY, item->name );

	return n;
}

/**/

long	menu_shop_sale_item(
	shop_n_t shop_n, mbr_t *mbr, item_t *item
)
{
	return menu_shop_sale( shop_n, mbr, item,
			DEAL_KIND_SALE_ITEM, FALSE );
}

/**/

long	menu_shop_sale_equip(
	shop_n_t shop_n, mbr_t *mbr, item_t *item
)
{
	return menu_shop_sale( shop_n, mbr, item,
			DEAL_KIND_SALE_EQUIP, FALSE );
}

/**/

long	menu_shop_sale(
	shop_n_t shop_n, mbr_t *mbr, item_t *item,
	deal_kind_t deal_kind, bool_t flg_auto_sale
)
{
	ask_t	ask;
	item_t	*tmp;
	item_t	*asgn;
	long	n;

	n = 0;

	if( !flg_auto_sale ){
		/* 商品名を表示 */

		print_msg( FLG_NULL, MSG_MENU_SALE, item->name );

		/* 本当に売るか確認 */

		ask = exec_menu_ask_no_msg( MSG_TTL_MENU_SALE,
				ASK_NO, TRUE );
		switch( ask ){
		case ASK_YES:
			break;
		case ASK_NO:
		case ASK_CANCEL:
		case ASK_ERR:
			return 0;
		}
	}

	lost_trgt( item );

	asgn = NULL;

	switch( shop_n ){
	default:
	case SHOP_N_INN:
	case SHOP_N_BAR:
	case SHOP_N_MAGIC:
	case SHOP_N_RESTAURANT:
	case SHOP_N_TEAROOM:
	case SHOP_N_TOBACCO:
		print_msg( FLG_MSG_NO_MORE_PREV | FLG_MSG_NO_MORE_NEXT,
				MSG_NO_DEAL, item->name );
		return 0;
	case SHOP_N_TEMPLE:
		asgn = get_shop_temple_item_asgn();
		break;
	case SHOP_N_WPN:
		asgn = get_shop_wpn_item_asgn();
		break;
	case SHOP_N_ARMOR:
		asgn = get_shop_armor_item_asgn();
		break;
	case SHOP_N_ALCHEMY:
		asgn = get_shop_alchemy_item_asgn();
		break;
	case SHOP_N_MUSIC:
		asgn = get_shop_music_item_asgn();
		break;
	case SHOP_N_GROCERY:
		asgn = get_shop_grocery_item_asgn();
		break;
	}

	print_msg( FLG_MSG_NO_MORE_PREV | FLG_MSG_NO_MORE_NEXT,
			MSG_MENU_REACHED_SALE, item->name );

	if( (asgn == NULL) || chk_flg( item->flg, FLG_ITEM_CURSED ) ){
		if( flg_auto_sale || chk_package_item( item ) ){
			n = item->n;
			del_item( item );
		} else {
			n = 1;
			inc_item( item, -1 );
		}
	} else {
		tmp = alloc_item();
		if( tmp == NULL )
			return 0;
		copy_item( tmp, item );
		tmp->stock = 1;

		if( flg_auto_sale || chk_package_item( item ) ){
			n = item->n;

			ins_ls_item( asgn, tmp );
			inc_item( item, -item->n );
		} else {
			n = 1;

			tmp->n = 1;
			inc_item( tmp, -(tmp->n - 1) );

			ins_ls_item( asgn, tmp );
			inc_item( item, -1 );
		}

#if	FLG_IDENTIFY_ITEM_SALE
		identify_item( tmp );
#endif
	}

	return n;
}

/**/

item_t	*get_begin_article(
	mbr_t *mbr, shop_n_t shop_n, deal_kind_t kind
)
{
	item_t	*art_head;

	if( kind == DEAL_KIND_BUY ){
		switch( shop_n ){
		case SHOP_N_NULL:
		case SHOP_N_MAX_N:
		case SHOP_N_INN:
			return NULL;
		case SHOP_N_BAR:
			art_head = get_shop_bar_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_WPN:
			art_head = get_shop_wpn_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_ARMOR:
			art_head = get_shop_armor_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_MAGIC:
			return NULL;
		case SHOP_N_TEMPLE:
			art_head = get_shop_temple_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_ALCHEMY:
			art_head = get_shop_alchemy_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_MUSIC:
			art_head = get_shop_music_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_GROCERY:
			art_head = get_shop_grocery_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_RESTAURANT:
			art_head = get_shop_restaurant_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_TEAROOM:
			art_head = get_shop_tearoom_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_TOBACCO:
			art_head = get_shop_tobacco_item_asgn();
			if( art_head == NULL )
				return NULL;
			return art_head->next;
			break;
		case SHOP_N_PET_SHOP:
			return NULL;
		}
	} else if( kind == DEAL_KIND_SALE_ITEM ){
		art_head = get_mbr_item_asgn( mbr );
		if( art_head == NULL )
			return NULL;
		return art_head->next;
	} else if( kind == DEAL_KIND_SALE_EQUIP ){
		return get_mbr_item_asgn_equip( mbr );
	}

	return NULL;
}

/**/

item_t	*get_next_article( item_t *art, deal_kind_t kind )
{
	if( art == NULL )
		return NULL;

	if( kind == DEAL_KIND_BUY ){
		return art->next;
	} else if( kind == DEAL_KIND_SALE_ITEM ){
		return art->next;
	} else if( kind == DEAL_KIND_SALE_EQUIP ){
		return( art + 1 );
	}

	return NULL;
}

/**/

bool_t	chk_end_article( item_t *art, item_t *art_head, deal_kind_t kind )
{
	if( art == NULL )
		return TRUE;
	if( art_head == NULL )
		return TRUE;

	switch( kind ){
	default:
		return FALSE;
	case DEAL_KIND_BUY:
	case DEAL_KIND_SALE_ITEM:
		return( art->next == art_head );
	case DEAL_KIND_SALE_EQUIP:
		return( art >= (art_head + EQUIP_KIND_MAX_N) );
	}
}

/**/

bool_t	chk_deal_article(
	item_t *art, shop_n_t shop_n, deal_kind_t deal_kind
)
{
	switch( shop_n ){
	case SHOP_N_NULL:
	case SHOP_N_MAX_N:
	case SHOP_N_INN:
		return FALSE;
	case SHOP_N_BAR:
		if( deal_kind != DEAL_KIND_BUY )
			return FALSE;

		if( art->kind == ITEM_KIND_POTION )
			return TRUE;
		if( art->kind == ITEM_KIND_FOOD )
			return TRUE;
		break;
	case SHOP_N_WPN:
		if( art->kind == ITEM_KIND_WPN )
			return TRUE;
		break;
	case SHOP_N_ARMOR:
		if( art->kind == ITEM_KIND_ARMOR )
			return TRUE;
		break;
	case SHOP_N_MAGIC:
		return FALSE;
	case SHOP_N_TEMPLE:
		return FALSE;
	case SHOP_N_ALCHEMY:
		if( art->kind == ITEM_KIND_POTION )
			return TRUE;
		if( art->kind == ITEM_KIND_SCROLL )
			return TRUE;
		if( art->kind == ITEM_KIND_STICK )
			return TRUE;
		if( art->kind == ITEM_KIND_ACCE )
			return TRUE;
		break;
	case SHOP_N_MUSIC:
		if( art->kind == ITEM_KIND_INST )
			return TRUE;
		if( art->kind == ITEM_KIND_ANTHOLOGY )
			return TRUE;
		break;
	case SHOP_N_GROCERY:
		if( art->kind == ITEM_KIND_LIGHT )
			return TRUE;
		if( art->kind == ITEM_KIND_SPIKE )
			return TRUE;
		if( art->kind == ITEM_KIND_FOOD )
			return TRUE;
		if( art->kind == ITEM_KIND_TOBACCO ){
			if( art->dat.tobacco.kind
					== TOBACCO_KIND_ABSTAIN_GUM ){
				return TRUE;
			}
		}
		if( art->kind == ITEM_KIND_POTION ){
			if( art->dat.potion.kind == POTION_KIND_WATER )
				return TRUE;
			if( art->dat.potion.kind == POTION_KIND_OIL )
				return TRUE;
		}
		break;
	case SHOP_N_RESTAURANT:
		if( deal_kind != DEAL_KIND_BUY )
			return FALSE;

		if( art->kind == ITEM_KIND_POTION )
			return TRUE;
		if( art->kind == ITEM_KIND_FOOD )
			return TRUE;
		break;
	case SHOP_N_TEAROOM:
		if( deal_kind != DEAL_KIND_BUY )
			return FALSE;

		if( art->kind == ITEM_KIND_POTION )
			return TRUE;
		break;
	case SHOP_N_TOBACCO:
		if( deal_kind != DEAL_KIND_BUY )
			return FALSE;

		if( art->kind == ITEM_KIND_TOBACCO )
			return TRUE;
		if( art->kind == ITEM_KIND_PIPE )
			return TRUE;
		if( art->kind == ITEM_KIND_DISPOSAL )
			return TRUE;
		break;
	case SHOP_N_PET_SHOP:
		return FALSE;
	}

	return FALSE;
}

/**/

shop_n_t	get_shop_deal_article( item_t *art, deal_kind_t deal_kind )
{
	long	i;

	for( i = 0; i < SHOP_N_MAX_N; i++ ){
		shop_n_t	shop_n;

		shop_n = (shop_n_t)i;
		if( chk_deal_article( art, shop_n, deal_kind ) )
			return shop_n;
	}

	return SHOP_N_NULL;
}

/**/

char	*menu_bar( void )
{
	g_sel_ls_mbr = get_ls_mbr()[0];

	return exec_menu( ls_menu_bar, NULL, NULL );
}

/**/

char	*cb_menu_bar_order( menu_t **pp, menu_t **dflt )
{
	g_shop_n = SHOP_N_BAR;

	return menu_order();
}

/**/

char	*cb_menu_bar_form( menu_t **pp, menu_t **dflt )
{
	long	i, j, k;
	long	ls_mbr_n;
	mbr_t	**ls_mbr;
	menu_t	*p;

	ls_mbr = get_ls_mbr();
	ls_mbr_n = 0;
	p = ls_menu_bar_form;

	k = 0;
	str_nz_cpy( p[k].path, "/bar form",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	p[k].accel_key = '\0';
	p[k].short_key[0] = '\0';
	p[k].msg[0] = '\0';
	p[k].call_back = cb_menu_bar_form_init;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < LS_MBR_PAGE_MAX_N; i++ ){
		if( chk_flg( ls_mbr[ls_mbr_n]->stat, FLG_STAT_NOT_EXIST ) )
			break;

		str_nz_cpy( p[k].path, "/bar form/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( p[k].kind, "<Title>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = '\0';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_TTL_MENU_BAR_FORM,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = NULL;
		p[k].arg = NULL;
		p[k].flg = FLG_NULL;
		k++;

		for( j = 0; j < LS_MBR_MAX_N_PER_PAGE; j++ ){
			if( ls_mbr_n > LS_MBR_MAX_N )
				return STR_MENU_ERR;

			if( chk_flg( ls_mbr[ls_mbr_n]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}

			sn_printf( p[k].path, MENU_PATH_MAX_LEN,
					"/bar form/%ld", ls_mbr_n );
			str_nz_cpy( p[k].kind, "<CheckItem>",
					MENU_KIND_MAX_LEN );
			p[k].accel_key = (char)('A' + j);
			p[k].short_key[0] = '\0';
			str_nz_cpy( p[k].msg, ls_mbr[ls_mbr_n]->name,
					MENU_MSG_MAX_BYTE );
			p[k].call_back = cb_menu_bar_form_sub;
			p[k].arg = ls_mbr[ls_mbr_n];
			p[k].flg = FLG_NULL;
			k++;

			ls_mbr_n++;
		}

		str_nz_cpy( p[k].path, "/bar form/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( p[k].kind, "<PageSeparator>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = '\0';
		p[k].short_key[0] = '\0';
		p[k].msg[0] = '\0';
		p[k].call_back = NULL;
		p[k].arg = NULL;
		p[k].flg = FLG_NULL;
		k++;
	}
	p[k].path[0] = '\0';

	*pp = p;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_bar_form_init( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;

	for( p = *pp + 1; p->path[0] != '\0'; p++ ){
		mbr_t	*mbr;

		if( strcmp( p->kind, "<CheckItem>" ) != 0 )
			continue;

		mbr = (mbr_t *)(p->arg);

		if( mbr == g_sel_ls_mbr )
			*dflt = p;

		if( mbr->mbr_n == MBR_N_NOT_JOIN ){
			p->flg &= ~(FLG_MENU_CHK_ON);
			p->flg |= FLG_MENU_CHK_OFF;
		} else {
			p->flg |= FLG_MENU_CHK_ON;
			p->flg &= ~(FLG_MENU_CHK_OFF);
		}
	}

	return NULL;
}

/**/

char	*cb_menu_bar_form_sub( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;

	g_sel_ls_mbr = (mbr_t *)((*pp)->arg);
	if( g_sel_ls_mbr == NULL )
		return STR_MENU_ERR;

	*pp = ls_menu_bar_form_sub;
	*dflt = NULL;

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	str_nz_cpy( p->msg, g_sel_ls_mbr->name, MENU_MSG_MAX_BYTE );

	return NULL;
}

/**/

char	*cb_menu_bar_form_sub_init( menu_t **pp, menu_t **dflt )
{
	static char	sub_path[MENU_PATH_MAX_LEN + 1];
	party_t	*pty = get_party();
	long	i;

	clr_flg_menu( *pp, NULL, FLG_MENU_ALL );

	sn_printf( sub_path, MENU_PATH_MAX_LEN,
			"%ld", g_sel_ls_mbr->ls_mbr_n );

	if( g_sel_ls_mbr->mbr_n == MBR_N_NOT_JOIN ){
		set_chk_off_menu( ls_menu_bar_form, sub_path );
		set_flg_menu( *pp, "not join", FLG_MENU_HIDDEN );
	} else {
		set_chk_on_menu( ls_menu_bar_form, sub_path );
		set_flg_menu( *pp, "join", FLG_MENU_HIDDEN );
	}

	for( i = 0; i < MBR_MAX_N; i++ )
		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			break;
	if( i >= MBR_MAX_N )
		set_flg_menu( *pp, "join", FLG_MENU_HIDDEN );

	return NULL;
}

/**/

char	*cb_menu_bar_join( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;
	party_t	*pty;
	long	k;
	long	i, n;

	p = ls_menu_bar_join;

	pty = get_party();

	if( chk_flg( g_sel_ls_mbr->stat, FLG_STAT_NOT_EXIST ) )
		return STR_MENU_ERR;
	if( g_sel_ls_mbr->mbr_n != MBR_N_NOT_JOIN )
		return STR_MENU_ERR;

	k = 0;
	str_nz_cpy( p[k].path, "/join",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	p[k].accel_key = '\0';
	p[k].short_key[0] = '\0';
	p[k].msg[0] = '\0';
	p[k].call_back = cb_menu_bar_join_sub_init;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	n = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		sn_printf( p[k].path, MENU_PATH_MAX_LEN, "/join/%ld", i );
		str_nz_cpy( p[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = (char)('A' + i);
		p[k].short_key[0] = '\0';
		sn_printf( p[k].msg, MENU_MSG_MAX_BYTE, "%ld", i + 1 );
		p[k].call_back = cb_menu_bar_join_sub;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;

		if( !chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			n++;
	}
	p[k].path[0] = '\0';

	if( n >= MBR_MAX_N )
		return STR_MENU_ERR;

	*pp = p;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_bar_join_sub_init( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	i;

	clr_flg_menu( *pp, NULL, FLG_MENU_ALL );

	for( i = 0; i < LOOP_MAX_4000; i++ ){
		long	mbr_n;

		if( (*pp)[i].path[0] == '\0' )
			break;
		if( strcmp( (*pp)[i].kind, "<Item>" ) != 0 )
			continue;

		mbr_n = (long)((*pp)[i].arg);
		if( !chk_flg( pty->mbr[mbr_n]->stat, FLG_STAT_NOT_EXIST ) )
			(*pp)[i].flg |= FLG_MENU_HIDDEN;
	}

	return NULL;
}

/**/

char	*cb_menu_bar_join_sub( menu_t **pp, menu_t **dflt )
{
	static char	sub_path[MENU_PATH_MAX_LEN + 1];
	long	mbr_n;

	if( g_sel_ls_mbr == NULL )
		return STR_MENU_ERR;

	mbr_n = (long)((*pp)->arg);
	join_mbr( g_sel_ls_mbr->ls_mbr_n, mbr_n );

	sn_printf( sub_path, MENU_PATH_MAX_LEN,
			"%ld", g_sel_ls_mbr->ls_mbr_n );
	set_chk_off_menu( ls_menu_bar_form, sub_path );

	next_g_sel_ls_mbr();

	return "/bar/form/form";
}

/**/

char	*cb_menu_bar_not_join( menu_t **pp, menu_t **dflt )
{
	static char	sub_path[MENU_PATH_MAX_LEN + 1];

	if( g_sel_ls_mbr == NULL )
		return STR_MENU_ERR;

	not_join_mbr( g_sel_ls_mbr->ls_mbr_n, g_sel_ls_mbr->mbr_n );

	sn_printf( sub_path, MENU_PATH_MAX_LEN,
			"%ld", g_sel_ls_mbr->ls_mbr_n );
	set_chk_on_menu( ls_menu_bar_form, sub_path );

	next_g_sel_ls_mbr();

	return "/bar/form/form";
}

/**/

void	next_g_sel_ls_mbr( void )
{
	mbr_t	**head;
	long	n;

	head = get_ls_mbr();
	n = g_sel_ls_mbr->ls_mbr_n;

	n++;
	n %= LS_MBR_MAX_N;

	if( chk_flg( head[n]->stat, FLG_STAT_NOT_EXIST ) )
		n = 0;

	g_sel_ls_mbr = head[n];
}

/**/

char	*cb_menu_bar_edit_mbr( menu_t **pp, menu_t **dflt )
{
	long	i, j, k;
	long	ls_mbr_n;
	mbr_t	**ls_mbr;
	menu_t	*p;

	ls_mbr = get_ls_mbr();
	ls_mbr_n = 0;
	p = ls_menu_bar_sel_mbr;

	k = 0;
	str_nz_cpy( p[k].path, "/edit member",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	p[k].accel_key = '\0';
	p[k].short_key[0] = '\0';
	p[k].msg[0] = '\0';
	p[k].call_back = cb_menu_bar_edit_mbr_init;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < LS_MBR_PAGE_MAX_N; i++ ){
		if( chk_flg( ls_mbr[ls_mbr_n]->stat, FLG_STAT_NOT_EXIST ) )
			break;

		str_nz_cpy( p[k].path, "/edit member/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( p[k].kind, "<Title>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = '\0';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_TTL_MENU_BAR_EDIT_MBR,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = NULL;
		p[k].arg = NULL;
		p[k].flg = FLG_NULL;
		k++;

		for( j = 0; j < LS_MBR_MAX_N_PER_PAGE; j++ ){
			if( ls_mbr_n > LS_MBR_MAX_N )
				return STR_MENU_ERR;

			if( chk_flg( ls_mbr[ls_mbr_n]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}

			sn_printf( p[k].path, MENU_PATH_MAX_LEN,
					"/edit member/%ld",
					ls_mbr_n );
			str_nz_cpy( p[k].kind, "<Branch>",
					MENU_KIND_MAX_LEN );
			p[k].accel_key = (char)('A' + j);
			p[k].short_key[0] = '\0';
			str_nz_cpy( p[k].msg, ls_mbr[ls_mbr_n]->name,
					MENU_MSG_MAX_BYTE );
			p[k].call_back = cb_menu_bar_edit_mbr_sub;
			p[k].arg = ls_mbr[ls_mbr_n];
			p[k].flg = FLG_NULL;
			k++;

			ls_mbr_n++;
		}

		str_nz_cpy( p[k].path, "/edit member/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( p[k].kind, "<PageSeparator>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = '\0';
		p[k].short_key[0] = '\0';
		p[k].msg[0] = '\0';
		p[k].call_back = NULL;
		p[k].arg = NULL;
		p[k].flg = FLG_NULL;
		k++;
	}
	p[k].path[0] = '\0';

	*pp = p;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_bar_edit_mbr_init( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;

	for( p = *pp + 1; p->path[0] != '\0'; p++ ){
		mbr_t	*mbr;

		if( strcmp( p->kind, "<Branch>" ) != 0 )
			continue;
		if( p->arg == NULL )
			continue;

		mbr = (mbr_t *)(p->arg);

		if( mbr == g_sel_ls_mbr )
			*dflt = p;
	}

	return NULL;
}

/**/

char	*cb_menu_bar_edit_mbr_sub( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;

	g_sel_ls_mbr = (mbr_t *)((*pp)->arg);
	if( g_sel_ls_mbr == NULL )
		return STR_MENU_ERR;

	*pp = ls_menu_bar_edit_mbr_sub;
	*dflt = NULL;

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_BAR_EDIT_MBR_SUB,
			g_sel_ls_mbr->name );

	return NULL;
}

/**/

char	*cb_menu_bar_data_form( menu_t **pp, menu_t **dflt )
{
	menu_town_mbr_data( MBR_DATA_EDIT_KIND_EDIT, TRUE );

	return "/bar/form/form";
}

/**/

char	*cb_menu_bar_data_edit( menu_t **pp, menu_t **dflt )
{
	menu_town_mbr_data( MBR_DATA_EDIT_KIND_EDIT, TRUE );

	return "/bar/form/edit member/edit member";
}

/**/

char	*cb_menu_bar_arrange_up( menu_t **pp, menu_t **dflt )
{
	menu_bar_arrange_1( g_sel_ls_mbr, -1 );
	return "/bar/form/edit member/edit member";
}

/**/

char	*cb_menu_bar_arrange_down( menu_t **pp, menu_t **dflt )
{
	menu_bar_arrange_1( g_sel_ls_mbr, +1 );
	return "/bar/form/edit member/edit member";
}

/**/

char	*cb_menu_bar_arrange_top( menu_t **pp, menu_t **dflt )
{
	menu_bar_arrange( g_sel_ls_mbr, -1 );
	return "/bar/form/edit member/edit member";
}

/**/

char	*cb_menu_bar_arrange_bottom( menu_t **pp, menu_t **dflt )
{
	menu_bar_arrange( g_sel_ls_mbr, +1 );
	return "/bar/form/edit member/edit member";
}

/**/

void	menu_bar_arrange_1( mbr_t *mbr, long d )
{
	long	trgt_ls_mbr_n;
	mbr_t	**ls_mbr, *tmp_mbr;

	if( mbr == NULL )
		return;

	ls_mbr = get_ls_mbr();
	trgt_ls_mbr_n = mbr->ls_mbr_n;
	if( (trgt_ls_mbr_n + d) < 0 )
		return;
	if( (trgt_ls_mbr_n + d) >= LS_MBR_MAX_N )
		return;
	if( chk_flg( ls_mbr[trgt_ls_mbr_n + d]->stat,
			FLG_STAT_NOT_EXIST ) ){
		return;
	}

	arrange_cast_tab_1( trgt_ls_mbr_n, d );
	arrange_auto_mark_mbr_1( trgt_ls_mbr_n, d );
	arrange_item_1( trgt_ls_mbr_n, d );
	arrange_equip_1( trgt_ls_mbr_n, d );
	arrange_playing_report_1( trgt_ls_mbr_n, d );

	/**/

	tmp_mbr = ls_mbr[trgt_ls_mbr_n];

	ls_mbr[trgt_ls_mbr_n] = ls_mbr[trgt_ls_mbr_n + d];
	ls_mbr[trgt_ls_mbr_n]->ls_mbr_n = trgt_ls_mbr_n;

	ls_mbr[trgt_ls_mbr_n + d] = tmp_mbr;
	ls_mbr[trgt_ls_mbr_n + d]->ls_mbr_n = trgt_ls_mbr_n + d;

	g_sel_ls_mbr = ls_mbr[0];
}

/**/

void	menu_bar_arrange( mbr_t *mbr, long d )
{
	long	trgt_ls_mbr_n;
	mbr_t	**ls_mbr, *tmp_mbr;
	long	i;

	if( mbr == NULL )
		return;

	ls_mbr = get_ls_mbr();
	trgt_ls_mbr_n = mbr->ls_mbr_n;

	arrange_cast_tab( trgt_ls_mbr_n, d );
	arrange_auto_mark_mbr( trgt_ls_mbr_n, d );
	arrange_item( trgt_ls_mbr_n, d );
	arrange_equip( trgt_ls_mbr_n, d );
	arrange_playing_report( trgt_ls_mbr_n, d );

	tmp_mbr = mbr;
	if( d <= -1 ){
		for( i = trgt_ls_mbr_n - 1; i >= 0; i-- ){
			ls_mbr[i + 1] = ls_mbr[i];
			ls_mbr[i + 1]->ls_mbr_n++;
		}

		ls_mbr[0] = tmp_mbr;
		ls_mbr[0]->ls_mbr_n = 0;

		g_sel_ls_mbr = ls_mbr[0];
	} else {
		for( i = trgt_ls_mbr_n + 1; i < LS_MBR_MAX_N; i++ ){
			if( chk_flg( ls_mbr[i]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}

			ls_mbr[i - 1] = ls_mbr[i];
			ls_mbr[i - 1]->ls_mbr_n--;
		}

		ls_mbr[i - 1] = tmp_mbr;
		ls_mbr[i - 1]->ls_mbr_n = i - 1;

		g_sel_ls_mbr = ls_mbr[i - 1];
	}
}

/**/

char	*cb_menu_bar_new_mbr( menu_t **pp, menu_t **dflt )
{
	exec_menu_new_mbr();

	return STR_MENU_CANCEL;
}

/**/

bool_t	exec_menu_new_mbr( void )
{
	mbr_t	**ls_mbr;
	race_t	race;
	long	page_n;
	data_n_t	data_n;
	ask_t	ask;
	long	n;

	ls_mbr = get_ls_mbr();
	for( n = 0; n < LS_MBR_MAX_N; n++ )
		if( chk_flg( ls_mbr[n]->stat, FLG_STAT_NOT_EXIST ) )
			break;
	if( n >= LS_MBR_MAX_N )
		return FALSE;

	race.main = MAIN_RACE_HUMAN;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_HUMAN, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[n], MSG_MENU_NEW_MBR,
			'@', race, MALE, 0, n );

	page_n = 0;
	data_n = DATA_N_NEXT_PAGE;

	while( 1 ){
		menu_mbr_data( ls_mbr[n], &page_n, &data_n,
				MBR_DATA_EDIT_KIND_NEW );
		exec_menu_position( ls_mbr[n] );

		ask = exec_menu_ask( MSG_TTL_MENU_ASK_NEW_MBR,
				ASK_NO, TRUE );
		if( (ask == ASK_YES) || (ask == ASK_NO) )
			break;
		if( ask == ASK_ERR )
			return FALSE;
	}
	if( ask != ASK_YES ){
		ls_mbr[n]->stat |= FLG_STAT_NOT_EXIST;
		return FALSE;
	}

	ls_mbr[n]->fx.prev = &(ls_mbr[n]->fx);
	ls_mbr[n]->fx.next = &(ls_mbr[n]->fx);

	call_pcg_dun_reload_all_mbr();

	return TRUE;
}

/**/

char	*cb_menu_bar_remove_mbr( menu_t **pp, menu_t **dflt )
{
	long	i, j, k;
	long	ls_mbr_n;
	mbr_t	**ls_mbr;
	menu_t	*p;

	ls_mbr = get_ls_mbr();
	ls_mbr_n = 0;
	p = ls_menu_bar_sel_mbr;

	k = 0;
	str_nz_cpy( p[k].path, "/bar remove member",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	p[k].accel_key = '\0';
	p[k].short_key[0] = '\0';
	p[k].msg[0] = '\0';
	p[k].call_back = NULL;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < LS_MBR_PAGE_MAX_N; i++ ){
		if( chk_flg( ls_mbr[ls_mbr_n]->stat, FLG_STAT_NOT_EXIST ) )
			break;

		str_nz_cpy( p[k].path, "/bar remove member/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( p[k].kind, "<Title>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = '\0';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_TTL_MENU_BAR_REMOVE_MBR,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = NULL;
		p[k].arg = NULL;
		p[k].flg = FLG_NULL;
		k++;

		for( j = 0; j < LS_MBR_MAX_N_PER_PAGE; j++ ){
			if( ls_mbr_n > LS_MBR_MAX_N )
				return STR_MENU_ERR;

			if( chk_flg( ls_mbr[ls_mbr_n]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}

			sn_printf( p[k].path, MENU_PATH_MAX_LEN,
					"/bar remove member/%ld",
					ls_mbr_n );
			str_nz_cpy( p[k].kind, "<OpenWinItem>",
					MENU_KIND_MAX_LEN );
			p[k].accel_key = (char)('A' + j);
			p[k].short_key[0] = '\0';
			str_nz_cpy( p[k].msg, ls_mbr[ls_mbr_n]->name,
					MENU_MSG_MAX_BYTE );
			p[k].call_back = cb_menu_bar_remove_mbr_sub;
			p[k].arg = ls_mbr[ls_mbr_n];
			p[k].flg = FLG_NULL;
			k++;

			ls_mbr_n++;
		}

		str_nz_cpy( p[k].path, "/bar remove member/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( p[k].kind, "<PageSeparator>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = '\0';
		p[k].short_key[0] = '\0';
		p[k].msg[0] = '\0';
		p[k].call_back = NULL;
		p[k].arg = NULL;
		p[k].flg = FLG_NULL;
		k++;
	}
	p[k].path[0] = '\0';

	*pp = p;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_bar_remove_mbr_sub( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;
	long	lev;
	ask_t	ask;

	mbr = (mbr_t *)((*pp)->arg);
	if( mbr == NULL )
		return STR_MENU_CANCEL;

	lev = get_specialist_lev( mbr );

	curs_attrset_chr( mbr, -1, TRUE );
	print_msg( FLG_NULL, MSG_MENU_REMOVE_MBR_NAME, mbr->name );
	curs_attrset_dflt();
	print_msg( FLG_NULL, MSG_MENU_REMOVE_MBR_LEV, lev );
	print_msg( FLG_MSG_MORE, MSG_MENU_REMOVE_MBR_GOLD,
			fmt_gold( mbr->gold ) );

	ask = exec_menu_ask( MSG_TTL_MENU_ASK_REMOVE_MBR, ASK_NO, TRUE );
	switch( ask ){
	case ASK_YES:
		curs_attrset_chr( mbr, -1, TRUE );
		print_msg( FLG_NULL, MSG_MENU_REMOVE_MBR, mbr->name );
		curs_attrset_dflt();

		remove_mbr( mbr );
		break;
	case ASK_NO:
	case ASK_CANCEL:
		curs_attrset_chr( mbr, +1, TRUE );
		print_msg( FLG_NULL, MSG_MENU_REMOVE_MBR_CANCEL,
				mbr->name );
		curs_attrset_dflt();

		break;
	case ASK_ERR:
		return STR_MENU_ERR;
	}

	return "/bar/form/edit member/remove member";
}

/**/

char	*cb_menu_bar_edit_class( menu_t **pp, menu_t **dflt )
{
	char	*str_goto;

	while( 1 ){
		str_goto = exec_menu_class( &g_sel_class_n );
		if( str_goto != NULL )
			return str_goto;

		str_goto = exec_menu( ls_menu_bar_sel_edit_class,
				NULL, NULL );

		if( str_goto != NULL )
			return str_goto;
	}
}

/**/

char	*cb_menu_bar_edit_class_sub( menu_t **pp, menu_t **dflt )
{
	return menu_edit_class( g_sel_class_n );
}

/**/

char	*menu_edit_class( long n )
{
	class_t	*p;
	long	add;

	p = get_class_tab();
	if( p == NULL )
		return STR_MENU_ERR;

	while( 1 ){
		add = exec_edit_class( &(p[n]), FALSE );
		if( add == 0 )
			break;

		if( add > 0 ){
			n++;
			if( p[n].name[0] == '\0' )
				n = 0;
		} else {
			n--;
			if( n < 0 ){
				for( n = 0; n < CLASS_MAX_N; n++ )
					if( p[n + 1].name[0] == '\0' )
						break;
			}
		}
	}

	return NULL;
}

/**/

char	*cb_menu_bar_arrange_up_class( menu_t **pp, menu_t **dflt )
{
	arrange_class_1( g_sel_class_n, -1 );

	return NULL;
}

/**/

char	*cb_menu_bar_arrange_down_class( menu_t **pp, menu_t **dflt )
{
	arrange_class_1( g_sel_class_n, +1 );

	return NULL;
}

/**/

char	*cb_menu_bar_arrange_top_class( menu_t **pp, menu_t **dflt )
{
	arrange_class( g_sel_class_n, -1 );

	return NULL;
}

/**/

char	*cb_menu_bar_arrange_bottom_class( menu_t **pp, menu_t **dflt )
{
	arrange_class( g_sel_class_n, +1 );

	return NULL;
}

/**/

char	*cb_menu_bar_edit_skill( menu_t **pp, menu_t **dflt )
{
	char	*str_goto;

	while( 1 ){
		str_goto = exec_menu_class( &g_sel_class_n );
		if( str_goto != NULL )
			return str_goto;

		menu_edit_skill( g_sel_class_n );
	}
}

/**/

char	*menu_edit_skill( long n )
{
	class_t	*p;
	long	add;

	p = get_class_tab();
	if( p == NULL )
		return STR_MENU_ERR;

	while( 1 ){
		add = exec_edit_skill( &(p[n]), FALSE );
		if( add == 0 )
			break;

		if( add > 0 ){
			n++;
			if( p[n].name[0] == '\0' )
				n = 0;
		} else {
			n--;
			if( n < 0 ){
				for( n = 0; n < CLASS_MAX_N; n++ )
					if( p[n + 1].name[0] == '\0' )
						break;
			}
		}
	}

	return NULL;
}

/**/

char	*cb_menu_bar_new_class( menu_t **pp, menu_t **dflt )
{
	class_t	*p;
	long	n;
	long	i;

	p = get_class_tab();
	if( p == NULL )
		return STR_MENU_ERR;

	for( n = 0; n < CLASS_MAX_N; n++ )
		if( p[n].name[0] == '\0' )
			break;
	if( n >= CLASS_MAX_N ){
		print_msg( FLG_MSG_ERR, MSG_S, MSG_ERR_MENU_NEW_CLASS );
		return STR_MENU_ERR;
	}

	str_nz_cpy( p[n].name, MSG_MENU_NEW_CLASS, CLASS_NAME_MAX_BYTE );
	for( i = 0; i < ABL_KIND_MAX_N; i++ )
		p[n].abl_rate[i] = (rate_t)0;
	for( i = 0; i < SKILL_MAX_N; i++ )
		p[n].skill[i] = SKILL_KIND_NULL;

	menu_new_class( n );

	return STR_MENU_CANCEL;
}

/**/

char	*menu_new_class( long n )
{
	class_t	*p;
	long	add;

	p = get_class_tab();
	if( p == NULL )
		return STR_MENU_ERR;

	while( 1 ){
		add = exec_edit_class( &(p[n]), TRUE );
		if( add == 0 )
			break;
	}

	return NULL;
}

/**/

long	exec_edit_class( class_t *org, bool_t flg_new )
{
	edit_class_t	n;
	edit_class_t	prev_n;
	class_t	edit, *work;
	bool_t	flg_sel_add;
	bool_t	flg_sel;

	n = static_exec_edit_class__n;

	if( org == NULL )
		return 0;

	work = &edit;
	*work = *org;

	prev_n = n;
	flg_sel_add = TRUE;

	draw_edit_class_all( org, work, n, flg_sel_add );

	while( 1 ){
		if( n > EDIT_CLASS_MAX_N - 1 )
			n = (edit_class_t)(EDIT_CLASS_NULL + 1);
		if( n < EDIT_CLASS_NULL + 1 )
			n = (edit_class_t)(EDIT_CLASS_MAX_N - 1);

		draw_edit_class( org, work, prev_n, FALSE, flg_sel_add,
				FALSE );
		draw_edit_class( org, work, n, TRUE, flg_sel_add,
				FALSE );
		prev_n = n;

		call_gui_class_edit_draw( work );

		flg_sel = FALSE;

		switch( get_key( g_flg_clr_key_buf_menu ) ){
		case CASE_CANCEL:
		case CASE_EXEC:
			if( exec_menu_ask_edit_class(
					org, work, flg_new ) ){
				call_gui_class_edit_wipe();
				static_exec_edit_class__n = n;
				return 0;
			}
			draw_edit_class_all( org, work, n, flg_sel_add );
			break;
		case ' ':
			if( get_flg_space_select() )
				flg_sel = TRUE;
			break;
		case CASE_ENTER:
			if( !get_flg_space_select() )
				flg_sel = TRUE;
			break;
		case CASE_CRSR_LEFT:
			flg_sel_add = TRUE;
			break;
		case CASE_CRSR_RIGHT:
			flg_sel_add = FALSE;
			break;
		case CASE_CRSR_DOWN:
			n = (edit_class_t)(n + 1);
			break;
		case CASE_CRSR_UP:
			n = (edit_class_t)(n - 1);
			break;
		case 'g':
			exec_back_log();
			break;
		default:
			break;
		}

		if( flg_sel ){
			if( n == EDIT_CLASS_NEXT ){
				if( exec_menu_ask_edit_class(
						org, work, flg_new ) ){
					static_exec_edit_class__n = n;
					return +1;
				}
				draw_edit_class_all( org, work, n,
						flg_sel_add );
			} else if( n == EDIT_CLASS_PREV ){
				if( exec_menu_ask_edit_class(
						org, work, flg_new ) ){
					static_exec_edit_class__n = n;
					return -1;
				}
				draw_edit_class_all( org, work, n,
						flg_sel_add );
			} else if( n == EDIT_CLASS_NAME ){
				draw_edit_class( org, work, n,
						FALSE, flg_sel_add,
						FALSE );
				gets_class_name( work->name );
			} else {
				if( flg_sel_add ){
					menu_edit_class_inc_abl(
							work, n, +1 );
				} else {
					menu_edit_class_inc_abl(
							work, n, -1 );
				}

				draw_edit_class( org, work,
						EDIT_CLASS_TOTAL,
						FALSE, flg_sel_add,
						FALSE );
			}
		}
	}

	static_exec_edit_class__n = n;
	return 0;
}

/**/

long	exec_edit_skill( class_t *org, bool_t flg_new )
{
	edit_skill_t	*pn, prev_n;
	class_t	edit, *work;
	long	slot;
	bool_t	flg_sel;

	g_skill_slot_n = static_exec_edit_skill__n;

	if( org == NULL )
		return 0;

	work = &edit;
	*work = *org;

	pn = &g_skill_slot_n;
	prev_n = *pn;

	draw_edit_skill_all( org, work, *pn );

	while( 1 ){
		if( *pn > EDIT_SKILL_MAX_N - 1 )
			*pn = (edit_skill_t)(EDIT_SKILL_NULL + 1);
		if( *pn < EDIT_SKILL_NULL + 1 )
			*pn = (edit_skill_t)(EDIT_SKILL_MAX_N - 1);

		draw_edit_skill( org, work, prev_n, FALSE, FALSE );
		draw_edit_skill( org, work, *pn, TRUE, FALSE );
		prev_n = *pn;

		call_gui_skill_edit_draw( work );

		flg_sel = FALSE;

		switch( get_key( g_flg_clr_key_buf_menu ) ){
		case CASE_CANCEL:
		case CASE_EXEC:
			if( exec_menu_ask_edit_skill(
					org, work, flg_new ) ){
				call_gui_skill_edit_wipe();
				static_exec_edit_skill__n = *pn;
				return 0;
			}
			draw_edit_skill_all( org, work, *pn );
			break;
		case ' ':
			if( get_flg_space_select() )
				flg_sel = TRUE;
			break;
		case CASE_ENTER:
			if( !get_flg_space_select() )
				flg_sel = TRUE;
			break;
		case CASE_CRSR_LEFT:
		case CASE_CRSR_RIGHT:
			break;
		case CASE_CRSR_DOWN:
			*pn = (edit_skill_t)(*pn + 1);
			break;
		case CASE_CRSR_UP:
			*pn = (edit_skill_t)(*pn - 1);
			break;
		case 'g':
			exec_back_log();
			break;
		default:
			break;
		}

		if( flg_sel ){
			if( *pn == EDIT_SKILL_NEXT ){
				if( exec_menu_ask_edit_skill(
						org, work, flg_new ) ){
					static_exec_edit_skill__n = *pn;
					return +1;
				}
				draw_edit_skill_all( org, work, *pn );
			} else if( *pn == EDIT_SKILL_PREV ){
				if( exec_menu_ask_edit_skill(
						org, work, flg_new ) ){
					static_exec_edit_skill__n = *pn;
					return -1;
				}
				draw_edit_skill_all( org, work, *pn );
			} else if( *pn == EDIT_SKILL_CLASS_NAME ){
				draw_edit_skill( org, work, *pn,
						FALSE, FALSE );
				gets_class_name( work->name );
			} else if( (EDIT_SKILL_A_00 <= *pn)
					&& (*pn <= EDIT_SKILL_A_09) ){
				slot = *pn - EDIT_SKILL_A_00;

				exec_sel_skill_edit( work, slot );
				draw_edit_skill_all( org, work, *pn );
			} else if( (EDIT_SKILL_B_00 <= *pn)
					&& (*pn <= EDIT_SKILL_B_09) ){
				slot = *pn - EDIT_SKILL_B_00
						+ SKILL_PER_PAGE_MAX_N;

				exec_sel_skill_edit( work, slot );
				draw_edit_skill_all( org, work, *pn );
			}
		}
	}

	static_exec_edit_skill__n = *pn;
	return 0;
}

/**/

void	set_edit_skill_n( edit_skill_t n )
{
	g_skill_slot_n = n;
}

/**/

edit_skill_t	get_edit_skill_n( void )
{
	return g_skill_slot_n;
}

/**/

char	*exec_sel_skill_edit( class_t *work, long slot )
{
	char	*ret;
	long	i;

	if( work == NULL )
		return NULL;
	if( slot < 0 )
		return NULL;
	if( slot >= SKILL_MAX_N )
		return NULL;

	ret = exec_sel_skill( &(work->skill[slot]) );

	if( ret != NULL )
		return ret;
	if( work->skill[slot] == SKILL_KIND_NULL )
		return NULL;

	for( i = 0; i < SKILL_MAX_N; i++ ){
		if( i == slot )
			continue;

		if( work->skill[i] == work->skill[slot] )
			work->skill[i] = SKILL_KIND_NULL;
	}

	return NULL;
}

/**/

char	*exec_sel_skill( skill_kind_t *ret_kind )
{
	long	i, j, k;
	menu_t	*p, *dflt;
	skill_kind_t	kind;
	char	*ret;

	p = ls_menu_sel_skill;
	dflt = NULL;

	k = 0;
	str_nz_cpy( p[k].path, "/select skill",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	p[k].accel_key = '\0';
	p[k].short_key[0] = '\0';
	p[k].msg[0] = '\0';
	p[k].call_back = NULL;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	for( i = SKILL_GROUP_KIND_NULL + 1;
			i < SKILL_GROUP_KIND_MAX_N; i++ ){
		str_nz_cpy( p[k].path, "/select skill/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( p[k].kind, "<Title>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = '\0';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg,
				get_skill_group_name( (skill_group_kind_t)i ),
				MENU_MSG_MAX_BYTE );
		p[k].call_back = NULL;
		p[k].arg = NULL;
		p[k].flg = FLG_NULL;
		k++;

		kind = SKILL_KIND_NULL;
		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"/select skill/%ld", k );
		str_nz_cpy( p[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = 'Z';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg,
				get_skill_name_from_kind( kind ),
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_sel_skill;
		p[k].arg = (void *)kind;
		p[k].flg = FLG_NULL;
		k++;

		for( j = 0; j < SKILL_PER_GROUP_MAX_N; j++ ){
			kind = get_skill_kind_from_group(
					(skill_group_kind_t)i, j );
			if( kind == SKILL_KIND_NULL )
				break;

			if( kind == g_sel_skill_kind )
				dflt = &(p[k]);

			sn_printf( p[k].path, MENU_PATH_MAX_LEN,
					"/select skill/%ld", k );
			str_nz_cpy( p[k].kind, "<Item>",
					MENU_KIND_MAX_LEN );
			p[k].accel_key = (char)('A' + j);
			p[k].short_key[0] = '\0';
			str_nz_cpy( p[k].msg,
					get_skill_name_from_kind( kind ),
					MENU_MSG_MAX_BYTE );
			p[k].call_back = cb_menu_sel_skill;
			p[k].arg = (void *)kind;
			p[k].flg = FLG_NULL;
			k++;
		}

		str_nz_cpy( p[k].path, "/select skill/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( p[k].kind, "<PageSeparator>",
				MENU_KIND_MAX_LEN );
		p[k].accel_key = '\0';
		p[k].short_key[0] = '\0';
		p[k].msg[0] = '\0';
		p[k].call_back = NULL;
		p[k].arg = NULL;
		p[k].flg = FLG_NULL;
		k++;
	}
	p[k].path[0] = '\0';

	ret = exec_menu( p, dflt, NULL );
	if( ret != NULL )
		return ret;

	if( ret_kind != NULL )
		*ret_kind = g_sel_skill_kind;
	return NULL;
}

/**/

char	*cb_menu_sel_skill( menu_t **pp, menu_t **dflt )
{
	g_sel_skill_kind = (skill_kind_t)(long)((*pp)->arg);
	return NULL;
}

/**/

char	*cb_menu_bar_remove_class( menu_t **pp, menu_t **dflt )
{
	long	class_n;
	char	*str_goto;
	ask_t	ask;

	class_n = 0;
	str_goto = exec_menu_class( &class_n );
	if( str_goto != NULL )
		return str_goto;

	ask = exec_menu_ask( MSG_TTL_MENU_ASK_REMOVE_CLASS, ASK_NO, TRUE );
	switch( ask ){
	case ASK_YES:
		remove_class( class_n );
		break;
	case ASK_NO:
		break;
	case ASK_CANCEL:
		return STR_MENU_CANCEL;
	case ASK_ERR:
		return STR_MENU_ERR;
	}

	return STR_MENU_CANCEL;
}

/**/

rate_t	calc_abl_total( class_t *p )
{
	rate_t	sum;
	long	abl;

	sum = 0;

	for( abl = 0; abl < ABL_KIND_MAX_N; abl++ )
		sum += p->abl_rate[abl];

	return sum;
}

/**/

bool_t	exec_menu_ask_edit_class(
	class_t *org, class_t *work, bool_t flg_new
)
{
	rate_t	total;
	ask_t	ask;

	total = calc_abl_total( work );

	if( total == _100_PERCENT )
		if( cmp_class( org, work ) )
			return TRUE;

	ask = exec_menu_ask( MSG_TTL_MENU_ASK_EDIT_CLASS, ASK_NO, TRUE );
	switch( ask ){
	case ASK_YES:
	case ASK_NO:
		break;
	case ASK_CANCEL:
	case ASK_ERR:
		return FALSE;	/* Cancel */
	}

	if( ask == ASK_YES ){
		if( total != _100_PERCENT ){
			print_msg( FLG_MSG_ERR | FLG_MSG_MORE, MSG_S,
					MSG_ERR_MENU_EDIT_CLASS );
			return FALSE;	/* Cancel */
		} else {
			*org = *work;
		}
	} else {
		if( flg_new )
			org->name[0] = '\0';
		*work = *org;
	}

	return TRUE;
}

/**/

bool_t	exec_menu_ask_edit_skill(
	class_t *org, class_t *work, bool_t flg_new
)
{
	ask_t	ask;

	if( cmp_class( org, work ) )
		return TRUE;

	ask = exec_menu_ask( MSG_TTL_MENU_ASK_EDIT_CLASS, ASK_NO, TRUE );
	switch( ask ){
	case ASK_YES:
		*org = *work;
		break;
	case ASK_NO:
		*work = *org;
		break;
	case ASK_CANCEL:
	case ASK_ERR:
		return FALSE;	/* Cancel */
	}

	return TRUE;
}

/**/

void	menu_edit_class_inc_abl(
	class_t *p, edit_class_t n, long add
)
{
	rate_t	sum;
	abl_kind_t	abl;

	sum = calc_abl_total( p );
	if( sum + add > _100_PERCENT )
		add = _100_PERCENT - sum;

	abl = ABL_KIND_HP;

	switch( n ){
	case EDIT_CLASS_NULL:
	case EDIT_CLASS_MAX_N:
		return;
	case EDIT_CLASS_TOTAL:
	case EDIT_CLASS_NAME:
	case EDIT_CLASS_PREV:
	case EDIT_CLASS_NEXT:
		return;
/**/
	case EDIT_CLASS_HP:
		abl = ABL_KIND_HP;
		break;
	case EDIT_CLASS_MP:
		abl = ABL_KIND_MP;
		break;
	case EDIT_CLASS_DEX:
		abl = ABL_KIND_DEX;
		break;
	case EDIT_CLASS_STR:
		abl = ABL_KIND_STR;
		break;
	case EDIT_CLASS_AGI:
		abl = ABL_KIND_AGI;
		break;
	case EDIT_CLASS_INT:
		abl = ABL_KIND_INT;
		break;
	case EDIT_CLASS_WIS:
		abl = ABL_KIND_WIS;
		break;
	case EDIT_CLASS_CHA:
		abl = ABL_KIND_CHA;
		break;
	case EDIT_CLASS_FIG:
		abl = ABL_KIND_FIG;
		break;
	case EDIT_CLASS_MON:
		abl = ABL_KIND_MON;
		break;
	case EDIT_CLASS_HUN:
		abl = ABL_KIND_HUN;
		break;
	case EDIT_CLASS_THI:
		abl = ABL_KIND_THI;
		break;
	case EDIT_CLASS_MAG:
		abl = ABL_KIND_MAG;
		break;
	case EDIT_CLASS_SOR:
		abl = ABL_KIND_SOR;
		break;
	case EDIT_CLASS_ENC:
		abl = ABL_KIND_ENC;
		break;
	case EDIT_CLASS_SUM:
		abl = ABL_KIND_SUM;
		break;
	case EDIT_CLASS_PRI:
		abl = ABL_KIND_PRI;
		break;
	case EDIT_CLASS_SHA:
		abl = ABL_KIND_SHA;
		break;
	case EDIT_CLASS_BAR:
		abl = ABL_KIND_BAR;
		break;
	case EDIT_CLASS_NIN:
		abl = ABL_KIND_NIN;
		break;
	}

	p->abl_rate[abl] += add;
	if( p->abl_rate[abl] < ABL_RATE_MIN_N )
		p->abl_rate[abl] = ABL_RATE_MIN_N;
	if( p->abl_rate[abl] > ABL_RATE_MAX_N )
		p->abl_rate[abl] = ABL_RATE_MAX_N;
}

/**/

char	*cb_menu_load_bar( menu_t **pp, menu_t **dflt )
{
	menu_load_bar();

	return NULL;
}

/**/

char	*cb_menu_save_bar( menu_t **pp, menu_t **dflt )
{
	menu_save_bar();

	return NULL;
}

/**/

void	menu_load_start( void )
{
	if( menu_load( FALSE, TRUE ) )
		reset_all_save( FALSE );
}

/**/

void	menu_load_bar( void )
{
	if( menu_load( FALSE, FALSE ) )
		reset_all_save( FALSE );
}

/**/

void	menu_save_bar( void )
{
	if( menu_save( FALSE ) )
		reset_all_save( FALSE );
}

/**/

char	*menu_inn( void )
{
	menu_t	*p;

	/* 一泊 */

	p = srch_menu( ls_menu_inn, "stay" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE, MSG_MENU_INN_STAY,
			fmt_gold( get_price_inn( FALSE ) ) );

	/* 休憩 */

	p = srch_menu( ls_menu_inn, "short stay" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE, MSG_MENU_INN_SHORT_STAY,
			fmt_gold( get_price_inn( TRUE ) ) );

	/* 馬小屋で一泊 */

	p = srch_menu( ls_menu_inn, "stay in mews" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE, MSG_MENU_INN_STAY_IN_MEWS,
			fmt_gold( 0 ) );

	/**/

	return exec_menu( ls_menu_inn, NULL, NULL );
}

/**/

char	*cb_menu_inn_stay( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	bool_t	flg_short;
	stay_inn_kind_t	kind;
	gold_t	price;
	bool_t	flg_pay;
	long	mbr_n;

	flg_short = (bool_t)(long)((*pp)->arg);
	if( flg_short )
		kind = STAY_INN_KIND_SHORT;
	else
		kind = STAY_INN_KIND_LONG;

	price = get_price_inn( flg_short );

	flg_pay = TRUE;
	for( mbr_n = 0; mbr_n < MBR_MAX_N; mbr_n++ ){
		if( chk_flg_or( pty->mbr[mbr_n]->stat, 0
				| FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD
				| FLG_STAT_STONE ) ){
			continue;
		}

		if( !chk_pay( pty->mbr[mbr_n], price ) )
			flg_pay = FALSE;
	}

	if( !flg_pay )
		return STR_MENU_CANCEL;

	for( mbr_n = 0; mbr_n < MBR_MAX_N; mbr_n++ ){
		if( chk_flg_or( pty->mbr[mbr_n]->stat, 0
				| FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD
				| FLG_STAT_STONE ) ){
			continue;
		}

		paying_gold( pty->mbr[mbr_n], price );
	}

	call_game_music_play( MUSIC_KIND_EFFECT, ME_KIND_INN );
	stay_inn( kind );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_inn_short_stay( menu_t **pp, menu_t **dflt )
{
	return cb_menu_inn_stay( pp, dflt );
}

/**/

char	*cb_menu_inn_stay_in_mews( menu_t **pp, menu_t **dflt )
{
	call_game_music_play( MUSIC_KIND_EFFECT, ME_KIND_INN );
	stay_inn( STAY_INN_KIND_MEWS );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_inn_bath( menu_t **pp, menu_t **dflt )
{
	char	*str_goto;
	mbr_t	*mbr;

	str_goto = NULL;
	mbr = NULL;

	while( 1 ){
		str_goto = exec_menu_sel_mbr(
				&mbr, MSG_TTL_MENU_INN_BATH,
				FALSE, TRUE );
		if( str_goto != NULL )
			break;

		take_bath( mbr );
	}

	return str_goto;
}

/**/

char	*cb_menu_magic_guild_init( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls, *p;
	unsigned char	key;
	spell_kind_t	kind;
	spell_tab_t	*tab;
	long	len, max_len;
	bool_t	flg_no_enter;
	gold_t	gold;
	long	i;

	if( g_sel_mbr == NULL )
		return STR_MENU_ERR;

	ls = *pp;

	max_len = 1;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].path[0] == '\0' )
			break;
		if( ls[i].arg == NULL )
			continue;

		kind = (spell_kind_t)(long)(ls[i].arg);
		tab = get_spell_tab( kind );
		if( tab != NULL ){
			len = str_len_draw( tab->name );
			max_len = max_l( len, max_len );
		}
	}

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE, MSG_TTL_MENU_MAGIC_GUILD,
			get_shop_name( SHOP_N_MAGIC ),
			g_sel_mbr->name,
			fmt_gold( g_sel_mbr->gold ) );

	key = 'A';
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].path[0] == '\0' )
			break;
		if( strcmp( ls[i].kind, "<PageSeparator>" ) == 0 ){
			key = 'A';
			continue;
		}
		if( ls[i].accel_key == 'Z' ){
			if( key == 'A' )
				ls[i].flg &= ~FLG_MENU_HIDDEN;
			else
				ls[i].flg |= FLG_MENU_HIDDEN;
			continue;
		}
		if( ls[i].arg == NULL )
			continue;

		/**/

		kind = (spell_kind_t)(long)(ls[i].arg);
		tab = get_spell_tab( kind );

		if( tab == NULL ){
			gold = 0;
			sn_printf( ls[i].msg, MENU_MSG_MAX_BYTE,
					MSG_FMT_MENU_MAGIC_GUILD,
					0, "", 0,
					fmt_gold( 0 ) );
		} else {
			len = get_pading_len( tab->name, max_len );
			gold = get_price_spell( kind );
			sn_printf( ls[i].msg, MENU_MSG_MAX_BYTE,
					MSG_FMT_MENU_MAGIC_GUILD,
					len, tab->name, tab->lev,
					fmt_gold( gold ) );
		}

		if( gold <= 0 ){
			ls[i].flg |= FLG_MENU_HIDDEN;
			ls[i].accel_key = '\0';
			continue;
		}

		if( chk_chr_learned_spell( g_sel_mbr, kind ) ){
			ls[i].flg |= FLG_MENU_HIDDEN;
			ls[i].accel_key = '\0';
		} else {
			ls[i].flg &= ~FLG_MENU_HIDDEN;
			ls[i].accel_key = key;
			key++;
		}
	}

	if( !FLG_CAN_ENTER_MAGIC_GUILD_NOT_LEARNED ){
		flg_no_enter = FALSE;

		if( get_lev( g_sel_mbr, ABL_KIND_MAG ) > 0 ){
			clr_flg_menu( ls, "MAG", FLG_MENU_HIDDEN );
			flg_no_enter = TRUE;
		} else {
			set_flg_menu( ls, "MAG", FLG_MENU_HIDDEN );
		}

		if( get_lev( g_sel_mbr, ABL_KIND_SOR ) > 0 ){
			clr_flg_menu( ls, "SOR", FLG_MENU_HIDDEN );
			flg_no_enter = TRUE;
		} else {
			set_flg_menu( ls, "SOR", FLG_MENU_HIDDEN );
		}

		if( get_lev( g_sel_mbr, ABL_KIND_ENC ) > 0 ){
			clr_flg_menu( ls, "ENC", FLG_MENU_HIDDEN );
			flg_no_enter = TRUE;
		} else {
			set_flg_menu( ls, "ENC", FLG_MENU_HIDDEN );
		}

		if( get_lev( g_sel_mbr, ABL_KIND_SUM ) > 0 ){
			clr_flg_menu( ls, "SUM", FLG_MENU_HIDDEN );
			flg_no_enter = TRUE;
		} else {
			set_flg_menu( ls, "SUM", FLG_MENU_HIDDEN );
		}

		if( !flg_no_enter ){
			print_msg( FLG_MSG_ERR, MSG_ERR_SPELL,
					g_sel_mbr->name );
			return STR_MENU_CANCEL;
		}
	}

	return NULL;
}

/**/

char	*cb_menu_magic_guild( menu_t **pp, menu_t **dflt )
{
	spell_kind_t	kind;
	spell_tab_t	*tab;
	ask_t	ask;

	if( g_sel_mbr == NULL )
		return STR_MENU_ERR;

	kind = (spell_kind_t)(long)((*pp)->arg);
	tab = get_spell_tab( kind );
	if( tab == NULL )
		return STR_MENU_ERR;

	if( get_lev( g_sel_mbr, tab->abl ) < tab->lev ){
		curs_attrset_chr( g_sel_mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_CAN_NOT_LEARN_SPELL,
				g_sel_mbr->name, tab->name );
		curs_attrset_dflt();

		return STR_MENU_CANCEL;
	}

	if( !chk_pay( g_sel_mbr, get_price_spell( kind ) ) )
		return STR_MENU_CANCEL;

	/* 商品名を表示 */
	print_msg( FLG_NULL, MSG_MENU_BUY, tab->name );

	/* 本当に買うか確認 */
	ask = exec_menu_ask_no_msg( MSG_TTL_MENU_BUY, ASK_NO, TRUE );
	switch( ask ){
	case ASK_YES:
		break;
	case ASK_NO:
	case ASK_CANCEL:
	case ASK_ERR:
		return STR_MENU_CANCEL;
	}

	paying_gold( g_sel_mbr, get_price_spell( kind ) );
	call_game_sound_play( SOUND_KIND_SHOP_BUY, 1 );
	set_chr_learned_spell( g_sel_mbr, kind, TRUE );

	return "/magic guild";
}

/**/

char	*cb_menu_magic_guild_no_learn( menu_t **pp, menu_t **dflt )
{
	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_pet_shop_init( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;

	if( g_sel_mbr == NULL )
		return STR_MENU_ERR;

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE, MSG_TTL_MENU_PET_SHOP,
			get_shop_name( SHOP_N_PET_SHOP ),
			g_sel_mbr->name,
			fmt_gold( g_sel_mbr->gold ) );

	return NULL;
}

/**/

char	*cb_menu_pet_shop_take( menu_t **pp, menu_t **dflt )
{
	pet_t	**ls_pet;
	menu_t	*ls;
	long	k;
	long	i, n, max_n;
	char	key;

	ls_pet = get_ls_pet();

	ls = ls_menu_pet_shop_take;
	k = 0;
	key = 'A';
	n = 0;
	max_n = LS_PET_MAX_N;

	str_nz_cpy( ls[k].path, "/pet shop take", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/pet shop take/title", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_PET_SHOP_TAKE,
			get_shop_name( SHOP_N_PET_SHOP ),
			g_sel_mbr->name );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < max_n; i++ ){
		if( ls_pet[i] == NULL )
			continue;
		if( chk_flg( ls_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;
		if( !chk_can_join_pet( ls_pet[i] ) )
			continue;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/pet shop take/%ld", (long)(i + 1) );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL,
		str_nz_cpy( ls[k].msg, ls_pet[i]->name,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_pet_shop_take_sel;
		ls[k].arg = (void *)(ls_pet[i]);
		ls[k].flg = FLG_NULL;
		k++;

		key++;
		n++;

		if( (n % PET_SHOP_PET_N_PER_PAGE) == 0 ){
			str_nz_cpy( ls[k].path,
					"/pet shop take/page separator",
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

			key = 'A';
		}
	}
	ls[k].path[0] = '\0';

	if( n <= 0 ){
		print_msg( FLG_MSG_ERR, MSG_S,
				MSG_ERR_MENU_PET_SHOP_TAKE );
		return STR_MENU_CANCEL;
	}

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_pet_shop_take_sel( menu_t **pp, menu_t **dflt )
{
	pet_t	*pet;

	pet = (pet_t *)((*pp)->arg);
	if( pet == NULL )
		return STR_MENU_ERR;

	pet->owner = g_sel_mbr;
	join_pet( pet );
	print_msg( FLG_NULL, MSG_MENU_PET_SHOP_TAKE_SUCCESS, pet->name );

	return "/pet shop";
}

/**/

char	*cb_menu_pet_shop_leave( menu_t **pp, menu_t **dflt )
{
	pet_t	**party_pet;
	menu_t	*ls;
	long	k;
	long	i, n, max_n;
	char	key;

	party_pet = get_party_pet();

	ls = ls_menu_pet_shop_leave;
	k = 0;
	key = 'A';
	n = 0;
	max_n = PET_MAX_N;

	str_nz_cpy( ls[k].path, "/pet shop leave", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/pet shop leave/title", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_PET_SHOP_LEAVE,
			get_shop_name( SHOP_N_PET_SHOP ),
			g_sel_mbr->name );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < max_n; i++ ){
		if( party_pet[i] == NULL )
			continue;
		if( chk_flg( party_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;
		if( !chk_can_not_join_pet( party_pet[i] ) )
			continue;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/pet shop leave/%ld", (long)(i + 1) );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL,
		str_nz_cpy( ls[k].msg, party_pet[i]->name,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_pet_shop_leave_sel;
		ls[k].arg = (void *)(party_pet[i]);
		ls[k].flg = FLG_NULL;
		k++;

		key++;
		n++;

		if( (n % PET_SHOP_PET_N_PER_PAGE) == 0 ){
			str_nz_cpy( ls[k].path,
					"/pet shop leave/page separator",
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

			key = 'A';
		}
	}
	ls[k].path[0] = '\0';

	if( n <= 0 ){
		print_msg( FLG_MSG_ERR, MSG_S,
				MSG_ERR_MENU_PET_SHOP_LEAVE );
		return STR_MENU_CANCEL;
	}

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_pet_shop_leave_sel( menu_t **pp, menu_t **dflt )
{
	pet_t	*pet;

	pet = (pet_t *)((*pp)->arg);
	if( pet == NULL )
		return STR_MENU_ERR;

	not_join_pet( pet );
	print_msg( FLG_NULL, MSG_MENU_PET_SHOP_LEAVE_SUCCESS, pet->name );

	return "/pet shop";
}

/**/

char	*cb_menu_pet_shop_name( menu_t **pp, menu_t **dflt )
{
	pet_t	**ls_pet;
	menu_t	*ls;
	long	k;
	long	i, n, max_n;
	char	key;
	char	*mnstr_name;

	ls_pet = get_ls_pet();

	ls = ls_menu_pet_shop_name;
	k = 0;
	key = 'A';
	n = 0;
	max_n = LS_PET_MAX_N;

	str_nz_cpy( ls[k].path, "/pet shop name", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/pet shop name/title",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_PET_SHOP_NAME,
			get_shop_name( SHOP_N_PET_SHOP ),
			g_sel_mbr->name );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < max_n; i++ ){
		if( ls_pet[i] == NULL )
			continue;
		if( chk_flg( ls_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		if( ls_pet[i]->mnstr_tab == NULL )
			mnstr_name = MSG_MNSTR_UNKNOWN;
		else
			mnstr_name = ls_pet[i]->mnstr_tab->name;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/pet shop name/%ld", (long)(i + 1) );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL,
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
				MSG_MENU_PET_SHOP_NAME_LS,
				ls_pet[i]->name, mnstr_name );
		ls[k].call_back = cb_menu_pet_shop_name_sel;
		ls[k].arg = (void *)(ls_pet[i]);
		ls[k].flg = FLG_NULL;
		k++;

		key++;
		n++;

		if( (n % PET_SHOP_PET_N_PER_PAGE) == 0 ){
			str_nz_cpy( ls[k].path,
					"/pet shop name/page separator",
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

			key = 'A';
		}
	}
	ls[k].path[0] = '\0';

	if( n <= 0 ){
		print_msg( FLG_MSG_ERR, MSG_S,
				MSG_ERR_MENU_PET_SHOP_NAME );
		return STR_MENU_CANCEL;
	}

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_pet_shop_name_sel( menu_t **pp, menu_t **dflt )
{
	pet_t	*pet;

	pet = (pet_t *)((*pp)->arg);
	if( pet == NULL )
		return STR_MENU_ERR;

	wipe_all();
	if( gets_pet_name( pet ) ){
		print_msg( FLG_NULL, MSG_MENU_PET_SHOP_NAME_SUCCESS,
				pet->name );
	}
	redraw_all();

	return "/pet shop";
}

/**/

char	*cb_menu_pet_shop_remove( menu_t **pp, menu_t **dflt )
{
	pet_t	**ls_pet;
	menu_t	*ls;
	long	k;
	long	i, n, max_n;
	char	key;

	ls_pet = get_ls_pet();

	ls = ls_menu_pet_shop_remove;
	k = 0;
	key = 'A';
	n = 0;
	max_n = LS_PET_MAX_N;

	str_nz_cpy( ls[k].path, "/pet shop remove", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/pet shop remove/title", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_PET_SHOP_REMOVE,
			get_shop_name( SHOP_N_PET_SHOP ),
			g_sel_mbr->name );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < max_n; i++ ){
		if( ls_pet[i] == NULL )
			continue;
		if( chk_flg( ls_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/pet shop remove/%ld", (long)(i + 1) );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL,
		str_nz_cpy( ls[k].msg, ls_pet[i]->name, MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_pet_shop_remove_sel;
		ls[k].arg = (void *)(ls_pet[i]);
		ls[k].flg = FLG_NULL;
		k++;

		key++;
		n++;

		if( (n % PET_SHOP_PET_N_PER_PAGE) == 0 ){
			str_nz_cpy( ls[k].path,
					"/pet shop remove/page separator",
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

			key = 'A';
		}
	}
	ls[k].path[0] = '\0';

	if( n <= 0 ){
		print_msg( FLG_MSG_ERR, MSG_S,
				MSG_ERR_MENU_PET_SHOP_REMOVE );
		return STR_MENU_CANCEL;
	}

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_pet_shop_remove_sel( menu_t **pp, menu_t **dflt )
{
	pet_t	*pet;
	ask_t	ask;

	pet = (pet_t *)((*pp)->arg);
	if( pet == NULL )
		return STR_MENU_ERR;

	curs_attrset_chr( pet, -1, TRUE );
	print_msg( FLG_NULL, MSG_MENU_PET_SHOP_ASK_REMOVE, pet->name );
	curs_attrset_dflt();

	ask = exec_menu_ask_no_msg( MSG_TTL_MENU_PET_SHOP_ASK_REMOVE,
			ASK_NO, TRUE );
	switch( ask ){
	case ASK_YES:
		break;
	case ASK_NO:
	case ASK_CANCEL:
	case ASK_ERR:
		return STR_MENU_CANCEL;
	}

	curs_attrset_chr( pet, -1, TRUE );
	print_msg( FLG_NULL, MSG_MENU_PET_SHOP_REMOVE_SUCCESS, pet->name );
	curs_attrset_dflt();

	remove_pet( pet );

	return "/pet shop";
}

/**/

char	*cb_menu_pet_shop_buy( menu_t **pp, menu_t **dflt )
{
	art_ls_pet_shop_t	*art_ls_pet_shop;
	long	len, max_len;
	const char	*name;
	menu_t	*ls;
	long	k;
	long	i, max_n;
	char	key;

	art_ls_pet_shop = get_art_ls_pet_shop();

	ls = ls_menu_pet_shop_buy;
	k = 0;
	key = 'A';
	max_n = PET_SHOP_PET_MAX_N;

	str_nz_cpy( ls[k].path, "/pet shop buy", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/pet shop buy/title", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE, MSG_TTL_MENU_PET_SHOP,
			get_shop_name( SHOP_N_PET_SHOP ),
			g_sel_mbr->name,
			fmt_gold( g_sel_mbr->gold ) );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	max_len = 1;
	for( i = 0; i < max_n; i++ ){
		if( art_ls_pet_shop[i].kind == MNSTR_KIND_NULL )
			break;

		name = get_mnstr_name( art_ls_pet_shop[i].kind );
		len = str_len_draw( name );
		max_len = max_l( len, max_len );
	}

	for( i = 0; i < max_n; i++ ){
		if( art_ls_pet_shop[i].kind == MNSTR_KIND_NULL )
			break;

		if( (i != 0) && ((i % PET_SHOP_PET_N_PER_PAGE) == 0) ){
			str_nz_cpy( ls[k].path,
					"/pet shop buy/page separator",
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

			key = 'A';
		}

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/pet shop buy/%ld", (long)(i + 1) );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL,
		name = get_mnstr_name( art_ls_pet_shop[i].kind );
		len = get_pading_len( name, max_len );
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
				MSG_FMT_MENU_PET_SHOP,
				len, name,
				fmt_gold( art_ls_pet_shop[i].price ) );
		ls[k].call_back = cb_menu_pet_shop_buy_sel;
		ls[k].arg = (void *)i;
		ls[k].flg = FLG_NULL;
		k++;

		key++;
	}
	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_pet_shop_buy_sel( menu_t **pp, menu_t **dflt )
{
	art_ls_pet_shop_t	*art_ls_pet_shop;
	long	n;
	mnstr_kind_t	kind;
	gold_t	price;
	ask_t	ask;
	pet_t	*pet;

	if( g_sel_mbr == NULL )
		return STR_MENU_ERR;

	art_ls_pet_shop = get_art_ls_pet_shop();

	n = (long)((*pp)->arg);
	kind = art_ls_pet_shop[n].kind;
	if( kind == MNSTR_KIND_NULL )
		return STR_MENU_ERR;

	price = art_ls_pet_shop[n].price;
	if( !chk_pay( g_sel_mbr, price ) )
		return STR_MENU_CANCEL;

	/* 商品名を表示 */
	print_msg( FLG_NULL, MSG_MENU_PET_SHOP_ASK_BUY,
			get_mnstr_name( kind ) );

	ask = exec_menu_ask_no_msg( MSG_TTL_MENU_PET_SHOP_ASK_BUY,
			ASK_NO, TRUE );
	switch( ask ){
	case ASK_YES:
		break;
	case ASK_NO:
	case ASK_CANCEL:
	case ASK_ERR:
		return STR_MENU_CANCEL;
	}

	pet = make_pet( PET_DUN_LEV, kind, g_sel_mbr );
	if( pet == NULL ){
		print_msg( FLG_NULL, MSG_S, MSG_ERR_MENU_PET_SHOP_BUY );
		return STR_MENU_CANCEL;
	}

	pet->flg_chr |= FLG_CHR_CAN_DEL;
	pet->flg_chr &= ~(FLG_CHR_CAN_DISMISSAL);

	join_pet( pet );
	print_msg( FLG_NULL, MSG_MENU_PET_SHOP_BUY_SUCCESS, pet->name );

	paying_gold( g_sel_mbr, price );
	call_game_sound_play( SOUND_KIND_SHOP_BUY, 1 );

	return "/pet shop";
}

/**/

char	*cb_menu_town_init( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_main( *pp );

	return NULL;
}

/**/

char	*cb_menu_navi_init( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls;
	long	k;
	long	i;

	*dflt = NULL;
	ls = ls_menu_navi;
	k = 0;

	str_nz_cpy( ls[k].path, "/navi", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/navi/title", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_TTL_MENU_NAVI, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/navi/stairs", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'Z';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NAVI_PARTY_STAIRS;
	ls[k].msg[0] = '\0';
	ls[k].call_back = cb_menu_navi_stairs;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = SHOP_N_NULL + 1; i < SHOP_N_MAX_N; i++ ){
		char	mnr;
		shop_n_t	n;

		n = (shop_n_t)i;
		mnr = get_shop_mnr_face( n );

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/navi/%c", (char)mnr );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = toupper( mnr );
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL,
		str_nz_cpy( ls[k].msg, get_shop_name( n ),
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_navi;
		ls[k].arg = (void *)n;
		ls[k].flg = FLG_NULL;
		k++;
	}
	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = g_navi_dflt;

	return NULL;
}

/**/

char	*cb_menu_navi( menu_t **pp, menu_t **dflt )
{
	g_navi_dflt = *pp;

	navi_party( (shop_n_t)(long)((*pp)->arg) );

	return NULL;
}

/**/

char	*cb_menu_navi_stairs( menu_t **pp, menu_t **dflt )
{
	g_navi_dflt = *pp;

	navi_party_stairs();

	return NULL;
}

/**/

char	*cb_menu_auto_sale( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls;
	char	*str_goto;

	ls = ls_menu_auto_sale;
	str_goto = NULL;
	g_sel_mbr = NULL;

	while( 1 ){
		str_goto = exec_menu_sel_mbr(
				&g_sel_mbr, MSG_TTL_MENU_AUTO_SALE_SEL_MBR,
				TRUE, FALSE );
		if( str_goto != NULL )
			break;

		while( 1 ){
			if( !set_menu_auto_sale( ls, g_sel_mbr ) )
				return STR_MENU_ERR;

			str_goto = exec_menu( ls, NULL, NULL );
			if( str_goto == NULL )
				continue;
			if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
				break;

			return str_goto;
		}
	}

	if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
		return NULL;

	return str_goto;
}

/**/

bool_t	set_menu_auto_sale( menu_t *ls, mbr_t *mbr )
{
	item_t	*art_head, *item;
	long	len, max_len;
	long	k;
	long	i;

	k = 0;

	str_nz_cpy( ls[k].path, "/auto sale", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/auto sale/title", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_AUTO_SALE, mbr->name );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	art_head = get_mbr_item_asgn( mbr );
	if( art_head == NULL )
		return FALSE;

	max_len = 0;
	item = art_head->next;
	for( i = 1; i < LOOP_MAX_100; i++ ){
		if( item == art_head )
			break;

		set_art_name( mbr, item, DEAL_KIND_SALE_ITEM );

		len = str_len_std( item->art_name );
		max_len = max_l( len, max_len );

		item = item->next;
	}

	item = art_head->next;
	for( i = 0; i < LOOP_MAX_100; i++ ){
		shop_n_t	shop_n;
		gold_t	price;

		if( item == art_head )
			break;

		shop_n = get_shop_deal_article(
				item, DEAL_KIND_SALE_ITEM );
		price = get_price( shop_n, item, DEAL_KIND_SALE_ITEM );

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/auto sale/%ld", i );
		str_nz_cpy( ls[k].kind, "<CheckItem>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = toupper( (char)('A' + i) );
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL,
		len = get_pading_len( item->art_name, max_len );
		sn_printf( ls[k].msg,
				MENU_MSG_MAX_BYTE,
				MSG_FMT_ART_NAME,
				len, item->art_name,
				fmt_gold( price ) );
		ls[k].call_back = cb_menu_auto_sale_chk;
		ls[k].arg = (void *)item;
		ls[k].flg = FLG_MENU_CHK_OFF;
		k++;

		item = item->next;
	}

	str_nz_cpy( ls[k].path, "/auto sale/exec", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<OpenWinItem>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'Z';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_MENU_AUTO_SALE_EXEC;
	ls[k].msg[0] = '\0';
	ls[k].call_back = cb_menu_auto_sale_exec;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	ls[k].path[0] = '\0';

	return TRUE;
}

/**/

char	*cb_menu_auto_sale_chk( menu_t **pp, menu_t **dflt )
{
	set_key_buf_str_head( "2" );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_auto_sale_exec( menu_t **pp, menu_t **dflt )
{
	ask_t	ask;
	menu_t	*ls;
	item_t	*item;
	shop_n_t	shop_n;
	gold_t	price;
	long	sale_n, sale_sum;
	long	i;

	ask = exec_menu_ask( MSG_TTL_MENU_AUTO_SALE_ASK, ASK_NO, TRUE );
	switch( ask ){
	case ASK_YES:
		break;
	case ASK_NO:
	case ASK_CANCEL:
	case ASK_ERR:
		return STR_MENU_CANCEL;
	}

	ls = ls_menu_auto_sale;

	sale_sum = 0;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].path[0] == '\0' )
			break;
		if( ls[i].arg == NULL )
			continue;
		if( !chk_flg( ls[i].flg, FLG_MENU_CHK_ON ) )
			continue;

		item = (item_t *)(ls[i].arg);
		shop_n = get_shop_deal_article( item, DEAL_KIND_SALE_ITEM );
		price = get_price( shop_n, item, DEAL_KIND_SALE_ITEM );

		sale_n = menu_shop_sale( shop_n, g_sel_mbr, item,
				DEAL_KIND_SALE_ITEM, TRUE );

		if( sale_n <= 0 )
			continue;
		if( price <= 0 )
			continue;

		paid_gold( g_sel_mbr, +price );
		sale_sum += sale_n;
	}

	if( sale_sum <= 0 )
		return NULL;

	call_game_sound_play( SOUND_KIND_SHOP_SALE, 1 );

	add_turn( NAVI_ADD_TURN_N + SHOP_ADD_TURN_N );

	return NULL;
}

/**/

shop_n_t	get_cur_shop_n( void )
{
	return g_shop_n;
}

/**/

void	set_cur_shop_n( shop_n_t n )
{
	g_shop_n = n;
}

/**/

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_tmenu_c( void )
{
	check_memory( check_memory_tmenu_c_g_sel_mbr,
			"tmenu.c: g_sel_mbr" );
	check_memory( check_memory_tmenu_c_g_shop_n,
			"tmenu.c: g_shop_n" );
	check_memory( check_memory_tmenu_c_g_mbr_order,
			"tmenu.c: g_mbr_order" );
	check_memory( check_memory_tmenu_c_g_navi_dflt,
			"tmenu.c: g_navi_dflt" );
	check_memory( check_memory_tmenu_c_static_exec_edit_class__n,
			"tmenu.c: static_exec_edit_class__n" );
	check_memory( check_memory_tmenu_c_g_sel_skill_kind,
			"tmenu.c: g_sel_skill_kind" );
}

/**/
