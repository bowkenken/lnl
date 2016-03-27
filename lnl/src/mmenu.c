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
* $Id: mmenu.c,v 1.66 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#define	MMENU_C
#include	"inc.h"

/**/

/* 階層移動などでメニューをリセットするか? */
#define	FLG_RESET_MENU	0

#define	LS_CLASS_N_PER_PAGE	16

/**/

static pos_t	g_main_crsr, g_pre_main_crsr;
static pos_t	g_sub_crsr, g_pre_sub_crsr;
check_memory_def( check_memory_mmenu_c_g_main_crsr )

static menu_t	*g_menu_dflt_main;
check_memory_def( check_memory_mmenu_c_g_menu_dflt_main )

static chr_t	*g_sub_sel_mbr;
static abl_kind_t	g_sel_abl;
static race_t	g_sel_race;
static sex_t	g_sel_sex;
static long	g_sel_class_n;
check_memory_def( check_memory_mmenu_c_g_sub_sel_mbr )

static bool_t	g_flg_no_save;
static long	g_sel_save_load_n;
check_memory_def( check_memory_mmenu_c_g_flg_no_save )

static trgt_kind_t	g_sel_obj_trgt_kind;
static chr_kind_t	g_dist_chr_kind;
static dist_t	g_sel_dist;
static act_kind_t	g_sel_act_kind;
check_memory_def( check_memory_mmenu_c_g_sel_obj_trgt_kind )

static long	g_sel_mbr_n;
static item_t	*g_sel_item;
static equip_kind_t	g_sel_equip_kind;
static bool_t	g_flg_equip_self;
check_memory_def( check_memory_mmenu_c_g_sel_mbr_n )

static mbr_t	*g_mark_sel_mbr;
static item_t	*g_mark_sel_item;
static door_t	*g_mark_sel_door;
static trap_t	*g_mark_sel_trap;
check_memory_def( check_memory_mmenu_c_g_mark_sel_mbr )

typedef struct {
	equip_kind_t	kind;
	n_msg_t	n_msg;
} ls_equip_msg_t;

static ls_equip_msg_t	ls_equip_msg[] = {
	{ EQUIP_KIND_WIELDING, N_MSG_MENU_SEL_EQUIP_WIELDING },
	{ EQUIP_KIND_SHIELD, N_MSG_MENU_SEL_EQUIP_SHIELD },
	{ EQUIP_KIND_BOW, N_MSG_MENU_SEL_EQUIP_BOW },
	{ EQUIP_KIND_ARW, N_MSG_MENU_SEL_EQUIP_ARW },
	{ EQUIP_KIND_HEAD, N_MSG_MENU_SEL_EQUIP_HEAD },
	{ EQUIP_KIND_NECK, N_MSG_MENU_SEL_EQUIP_NECK },
	{ EQUIP_KIND_BODY, N_MSG_MENU_SEL_EQUIP_BODY },
	{ EQUIP_KIND_ARM, N_MSG_MENU_SEL_EQUIP_ARM },
	{ EQUIP_KIND_RIGHT_HAND, N_MSG_MENU_SEL_EQUIP_RIGHT_HAND },
	{ EQUIP_KIND_LEFT_HAND, N_MSG_MENU_SEL_EQUIP_LEFT_HAND },
	{ EQUIP_KIND_FEET, N_MSG_MENU_SEL_EQUIP_FEET },
	{ EQUIP_KIND_ABOUT_BODY, N_MSG_MENU_SEL_EQUIP_ABOUT_BODY },
	{ EQUIP_KIND_LIGHT_SOURCE, N_MSG_MENU_SEL_EQUIP_LIGHT_SOURCE },
};
check_memory_def( check_memory_mmenu_c_ls_equip_msg )

/**/

#include	"mmenu-tab.h"

/**/

static long static_cb_menu_item__pre_sel_mbr_n;
check_memory_def( check_memory_mmenu_c_pre_sel_mbr_n )

/**/

void	init_var_main_menu( void )
{
	set_scroll_page();
}

/**/

void	init_main_menu( void )
{
	set_flg_no_save( FALSE );
	next_pos_square( +1 );
	g_pre_main_crsr = g_main_crsr;
	g_pre_sub_crsr = g_sub_crsr;
	g_menu_dflt_main = NULL;
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_main_menu( void )
{
#if	FLG_RESET_MENU
	g_menu_dflt_main = NULL;
#endif

	/**/

	static_cb_menu_item__pre_sel_mbr_n = 0;
}

/**/

char	*exec_menu_sel_mbr(
	mbr_t **mbr, char *ttl,
	bool_t flg_sel_dead, bool_t flg_sel_pet
)
{
	party_t	*pty = get_party();
	pet_t	**pet = get_party_pet();
	menu_t	*ls;
	menu_t	*dflt;
	long	i, k;
	char	*ret;

	if( mbr == NULL )
		return STR_MENU_ERR;

	dflt = NULL;

	ls = ls_menu_mbr;
	k = 0;

	str_nz_cpy( ls[k].path, "/member",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	if( ttl != NULL ){
		str_nz_cpy( ls[k].path, "/member/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( ls[k].kind, "<Title>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = '\0';
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, ttl,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = NULL;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;
	}

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;
		if( !flg_sel_dead )
			if( chk_flg( pty->mbr[i]->stat, FLG_STAT_DEAD ) )
				continue;

		if( *mbr == pty->mbr[i] )
			dflt = &(ls[k]);

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/member/%ld", i );
		str_nz_cpy( ls[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + i);
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, pty->mbr[i]->name,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_sel_mbr;
		ls[k].arg = (void *)(pty->mbr[i]);
		ls[k].flg = FLG_NULL;
		k++;
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		if( !flg_sel_pet )
			break;

		if( pet[i] == NULL )
			continue;
		if( chk_flg( pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;
		if( !flg_sel_dead )
			if( chk_flg( pet[i]->stat, FLG_STAT_DEAD ) )
				continue;

		if( *mbr == pet[i] )
			dflt = &(ls[k]);

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/member/%ld", MBR_MAX_N + i );
		str_nz_cpy( ls[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + MBR_MAX_N + i);
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, pet[i]->name, MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_sel_mbr;
		ls[k].arg = (void *)(pet[i]);
		ls[k].flg = FLG_NULL;
		k++;
	}

	ls[k].path[0] = '\0';

	g_sub_sel_mbr = NULL;
	ret = exec_menu( ls, dflt, NULL );
	if( ret != NULL )
		return ret;

	if( g_sub_sel_mbr == NULL )
		return STR_MENU_ERR;

	*mbr = g_sub_sel_mbr;

	return NULL;
}

/**/

char	*cb_menu_sel_mbr( menu_t **pp, menu_t **dflt )
{
	g_sub_sel_mbr = (chr_t *)((*pp)->arg);

	return NULL;
}

/**/

char	*exec_menu_sel_abl( mbr_t *mbr, abl_kind_t *abl )
{
	menu_t	*ls;
	menu_t	*dflt;
	char	key;
	long	i, k;
	char	*ret;

	if( abl == NULL )
		return STR_MENU_ERR;

	if( chk_flg( mbr->stat, FLG_STAT_NOT_EXIST ) )
		mbr = NULL;

	dflt = NULL;

	ls = ls_menu_abl;
	k = 0;

	str_nz_cpy( ls[k].path, "/ability",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/ability/--",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_TTL_MENU_SEL_ABL,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	key = 'A';

	for( i = ABL_KIND_HP; i < ABL_KIND_MAX_N; i++ ){
		if( i == *abl )
			dflt = &(ls[k]);

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/ability/%ld", i );
		str_nz_cpy( ls[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		if( mbr == NULL ){
			str_nz_cpy( ls[k].msg, get_abl_name( (abl_kind_t)i ),
					MENU_MSG_MAX_BYTE );
		} else {
			sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
					"%-3s: %ld",
					get_abl_name( (abl_kind_t)i ),
					mbr->abl.lev[i].n );
		}
		ls[k].call_back = cb_menu_sel_abl;
		ls[k].arg = (void *)i;
		ls[k].flg = FLG_NULL;
		k++;

		key++;
		if( (i == ABL_KIND_CHA) || (key >= (char)('A' + 12)) ){
			key = 'A';

			str_nz_cpy( ls[k].path, "/ability/--",
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

	ls[k].path[0] = '\0';

	g_sel_abl = ABL_KIND_HP;
	ret = exec_menu( ls, dflt, NULL );
	if( ret != NULL )
		return ret;

	*abl = g_sel_abl;

	return NULL;
}

/**/

char	*cb_menu_sel_abl( menu_t **pp, menu_t **dflt )
{
	g_sel_abl = (abl_kind_t)(long)((*pp)->arg);

	return NULL;
}

/**/

char	*exec_menu_point_crsr( void )
{
	chk_scroll( FALSE );
	redraw_all();

	print_msg( FLG_MSG_NO_MORE, MSG_MENU_POINT_CRSR );

	while( 1 ){
		long	c;

		c = chk_key( g_flg_clr_key_buf, FALSE );
		switch( c ){
		case CASE_CANCEL:
		case CASE_EXEC:
			return STR_MENU_CANCEL;
		case ' ':
			if( get_flg_space_select() )
				return NULL;
			break;
		case CASE_ENTER:
			if( !get_flg_space_select() )
				return NULL;
			break;
		}
	}

	return STR_MENU_ERR;
}

/**/

char	*exec_menu_race( race_t *race )
{
	char	*str_goto;

	g_sel_race = *race;

	while( 1 ){
		str_goto = exec_menu( ls_menu_main_race, NULL, NULL );
		if( str_goto != NULL )
			return str_goto;

		str_goto = exec_menu( ls_menu_sub_race, NULL, NULL );
		if( str_goto == NULL )
			break;
		if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
			continue;

		return str_goto;
	}

	str_nz_cpy( g_sel_race.name, get_race_str_main( &g_sel_race ),
			RACE_NAME_MAX_BYTE );

	*race = g_sel_race;
	return NULL;
}

/**/

char	*cb_menu_main_race( menu_t **pp, menu_t **dflt )
{
	g_sel_race.main = (main_race_t)(long)((*pp)->arg);
	return NULL;
}

/**/

char	*cb_menu_sub_race( menu_t **pp, menu_t **dflt )
{
	g_sel_race.sub = (sub_race_t)(long)((*pp)->arg);
	return NULL;
}

/**/

char	*exec_menu_sex( sex_t *sex )
{
	char	*str_goto;

	g_sel_sex = *sex;

	str_goto = exec_menu( ls_menu_sex, NULL, NULL );
	if( str_goto != NULL )
		return str_goto;

	*sex = g_sel_sex;
	return NULL;
}

/**/

char	*cb_menu_sex( menu_t **pp, menu_t **dflt )
{
	g_sel_sex = (sex_t)(long)((*pp)->arg);
	return NULL;
}

/**/

char	*exec_menu_class( long *class_n )
{
	class_t	*class_tab;
	menu_t	*ls, *dflt;
	long	k;
	char	*str_goto;
	long	i;

	class_tab = get_class_tab();
	ls = ls_menu_class;
	dflt = &(ls[0]);
	k = 0;

	str_nz_cpy( ls[k].path, "/class", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/class/--", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_TTL_MENU_CLASS, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < CLASS_MAX_N; i++ ){
		if( class_tab[i].name[0] == '\0' )
			break;

		if( i == *class_n )
			dflt = &(ls[k]);

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN, "/class/%ld", i );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + (i % LS_CLASS_N_PER_PAGE));
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, class_tab[i].name,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_class;
		ls[k].arg = (void *)i;
		ls[k].flg = FLG_NULL;
		k++;

		if( (i % LS_CLASS_N_PER_PAGE)
				== (LS_CLASS_N_PER_PAGE - 1) ){
			str_nz_cpy( ls[k].path, "/class/--",
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
	ls[k].path[0] = '\0';

	g_sel_class_n = *class_n;

	str_goto = exec_menu( ls, dflt, NULL );
	if( str_goto != NULL )
		return str_goto;

	*class_n = g_sel_class_n;
	return NULL;
}

/**/

char	*cb_menu_class( menu_t **pp, menu_t **dflt )
{
	g_sel_class_n = (long)((*pp)->arg);
	return NULL;
}

/**/

char	*exec_menu_sel_obj( trgt_kind_t *trgt_kind, pos_t pos )
{
	char	*str;

	g_sel_obj_trgt_kind = TRGT_KIND_NULL;

	str = exec_menu( ls_menu_sel_obj, NULL, NULL );
	if( str != NULL )
		return str;

	*trgt_kind = g_sel_obj_trgt_kind;

	return NULL;
}

/**/

char	*cb_menu_main_init( menu_t **pp, menu_t **dflt )
{
	dun_t	*dun = get_dun();

	g_sel_mbr_n = get_mbr_n( g_main_crsr.x, g_main_crsr.y );

	clr_flg_menu( *pp, NULL, FLG_MENU_ALL );

	if( g_sel_mbr_n <= -1 ){
		/* メンバーを指定していない */
		set_flg_menu( *pp, "fight", FLG_MENU_HIDDEN );
	}

	if( dun->lev != 0 ){
		/* 街以外 */
		set_flg_menu( *pp, "town", FLG_MENU_HIDDEN );
	}

	return NULL;
}

/**/

char	*cb_menu_exec( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_main( *pp );

	exec_all_phase();

	return NULL;
}

/**/

char	*cb_menu_auto_mark( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_main( *pp );

	return menu_auto_mark( pp, dflt );
}

/**/

char	*cb_menu_mark( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	trgt_kind_t	trgt_kind_1, trgt_kind_2;
	pos_t	pos1, pos2;
	bool_t	flg_cont;
	char	*str;
	bool_t	flg_ret;

	set_menu_dflt_main( *pp );

	*pp = NULL;

	trgt_kind_1 = TRGT_KIND_NULL;
	trgt_kind_2 = TRGT_KIND_NULL;

	pos1 = g_main_crsr;

	flg_cont = TRUE;
	while( flg_cont ){
		str = exec_menu_sel_obj( &trgt_kind_1, pos1 );
		if( str != NULL )
			return str;

		if( trgt_kind_1 == TRGT_KIND_NULL ){
			if( menu_mark_square( g_main_crsr ) )
				return NULL;
			else
				return STR_MENU_ERR;
		}
		if( trgt_kind_1 == TRGT_KIND_AUTO )
			return NULL;
		if( trgt_kind_1 == TRGT_KIND_MBR ){
			mbr_t	*mbr;

			mbr = get_mbr( pos1.x, pos1.y );
			if( mbr == NULL )
				return STR_MENU_ERR;
			g_sel_mbr_n = mbr->mbr_n;

			/* 以前のターゲットにカーソルを移動 */
			if( pty->mbr[g_sel_mbr_n]->trgt.kind
					!= TRGT_KIND_SQUARE ){
				g_main_crsr.x = pty->mbr[g_sel_mbr_n]
						->trgt.true_x;
				g_main_crsr.y = pty->mbr[g_sel_mbr_n]
						->trgt.true_y;
			}
		}
		while( 1 ){
			str = exec_menu_point_crsr();
			if( str != NULL ){
				g_main_crsr = pos1;
				redraw_all();

				if( strcmp( str, STR_MENU_CANCEL ) == 0 )
					break;
				if( strcmp( str, STR_MENU_ERR ) == 0 )
					return str;
			}
			pos2 = g_main_crsr;

			str = exec_menu_sel_obj( &trgt_kind_2, pos2 );
			if( str != NULL ){
				if( strcmp( str, STR_MENU_CANCEL ) == 0 )
					continue;
				if( strcmp( str, STR_MENU_ERR ) == 0 )
					return str;
			}

			if( trgt_kind_2 == TRGT_KIND_NULL )
				return NULL;
			if( trgt_kind_2 == TRGT_KIND_AUTO )
				return NULL;
			if( trgt_kind_2 == TRGT_KIND_MBR ){
				if( trgt_kind_1 != TRGT_KIND_MBR ){
					mbr_t	*mbr;

					mbr = get_mbr( pos2.x, pos2.y );
					if( mbr == NULL )
						return STR_MENU_ERR;
					g_sel_mbr_n = mbr->mbr_n;
				}
			}

			flg_cont = FALSE;
			break;
		}
	}

	/**/

	flg_ret = FALSE;

	switch( trgt_kind_1 ){
	case TRGT_KIND_NULL:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		return STR_MENU_ERR;
	case TRGT_KIND_MBR:
		flg_ret = menu_switch_mark_mbr(
				trgt_kind_1, pos1, trgt_kind_2, pos2 );
		break;
	case TRGT_KIND_MNSTR:
	case TRGT_KIND_MNSTR_NULL:
		flg_ret = menu_switch_mark_mnstr(
				trgt_kind_1, pos1, trgt_kind_2, pos2 );
		break;
	case TRGT_KIND_ITEM:
		flg_ret = menu_switch_mark_item(
				trgt_kind_1, pos1, trgt_kind_2, pos2 );
		break;
	case TRGT_KIND_DOOR:
		flg_ret = menu_switch_mark_door(
				trgt_kind_1, pos1, trgt_kind_2, pos2 );
		break;
	case TRGT_KIND_TRAP:
		flg_ret = menu_switch_mark_trap(
				trgt_kind_1, pos1, trgt_kind_2, pos2 );
		break;
	case TRGT_KIND_QUEUE:
		return STR_MENU_ERR;
	case TRGT_KIND_SQUARE:
		flg_ret = menu_switch_mark_square(
				trgt_kind_1, pos1, trgt_kind_2, pos2 );
		break;
	case TRGT_KIND_POS:
		flg_ret = menu_switch_mark_pos(
				trgt_kind_1, pos1, trgt_kind_2, pos2 );
		break;
	}

	if( !flg_ret )
		return STR_MENU_ERR;

	return NULL;
}

/**/

char	*cb_menu_sel_obj_init( menu_t **pp, menu_t **dflt )
{
	long	mjr_chr, mjr_obj;
	flg_map_t	flg_chr, flg_obj;
	long	sq_x, sq_y;
	dun_t	*dun = get_dun();

	mjr_chr = dun->map.chr.mjr[g_main_crsr.y][g_main_crsr.x];
	flg_chr = dun->map.chr.flg[g_main_crsr.y][g_main_crsr.x];
	mjr_obj = dun->map.obj.mjr[g_main_crsr.y][g_main_crsr.x];
	flg_obj = dun->map.obj.flg[g_main_crsr.y][g_main_crsr.x];

	clr_flg_menu( *pp, NULL, FLG_MENU_ALL );

	/* メンバー */

	if( mjr_chr != FACE_MJR_MBR )
		set_flg_menu( *pp, "member", FLG_MENU_HIDDEN );

	/* モンスター */

	if( (mjr_chr == FACE_MJR_MBR) || (mjr_chr == FACE_MJR_NULL) )
		set_flg_menu( *pp, "monster", FLG_MENU_HIDDEN );
	if( !chk_flg( flg_chr, FLG_MAP_CHR_FIND ) )
		set_flg_menu( *pp, "monster", FLG_MENU_HIDDEN );
	if( chk_flg( flg_chr, FLG_MAP_CHR_INVISIBLE ) )
		set_flg_menu( *pp, "monster", FLG_MENU_HIDDEN );

	/* ラスボス */

	if( chk_xx_pos( g_main_crsr.x, g_main_crsr.y ) )
		clr_flg_menu( *pp, "monster", FLG_MENU_HIDDEN );

	/* アイテム */

	if( get_item( g_main_crsr.x, g_main_crsr.y ) == NULL )
		set_flg_menu( *pp, "item", FLG_MENU_HIDDEN );

	/* ドア */

	if( (mjr_obj != FACE_MJR_DOOR_CLOSE)
			&& (mjr_obj != FACE_MJR_DOOR_OPEN) ){
		set_flg_menu( *pp, "door", FLG_MENU_HIDDEN );
	}

	/* 罠 */

	if( mjr_obj != FACE_MJR_TRAP )
		set_flg_menu( *pp, "trap", FLG_MENU_HIDDEN );

	/* 見えない */

	if( !chk_flg( flg_obj, FLG_MAP_OBJ_FIND ) ){
		set_flg_menu( *pp, "item", FLG_MENU_HIDDEN );
		set_flg_menu( *pp, "door", FLG_MENU_HIDDEN );
		set_flg_menu( *pp, "trap", FLG_MENU_HIDDEN );
	}
	if( chk_flg( flg_obj, FLG_MAP_OBJ_LOOK_FLOOR ) ){
		set_flg_menu( *pp, "item", FLG_MENU_HIDDEN );
		set_flg_menu( *pp, "door", FLG_MENU_HIDDEN );
		set_flg_menu( *pp, "trap", FLG_MENU_HIDDEN );
	}
	if( chk_flg( flg_obj, FLG_MAP_OBJ_LOOK_WALL ) ){
		set_flg_menu( *pp, "item", FLG_MENU_HIDDEN );
		set_flg_menu( *pp, "door", FLG_MENU_HIDDEN );
		set_flg_menu( *pp, "trap", FLG_MENU_HIDDEN );
	}

	/* アンカー */

	get_square_pos( &sq_x, &sq_y, FALSE );
	if( labs( sq_x - g_main_crsr.x ) > (SQUARE_WIDTH / 2) )
		set_flg_menu( *pp, "square", FLG_MENU_HIDDEN );
	if( labs( sq_y - g_main_crsr.y ) > (SQUARE_HEIGHT / 2) )
		set_flg_menu( *pp, "square", FLG_MENU_HIDDEN );

	/* マーク解除 */

	if( mjr_chr != FACE_MJR_MBR )
		set_flg_menu( *pp, "clear", FLG_MENU_HIDDEN );

	return NULL;
}

/**/

char	*cb_menu_sel_obj( menu_t **pp, menu_t **dflt )
{
	g_sel_obj_trgt_kind = (trgt_kind_t)(long)((*pp)->arg);

	return NULL;
}

/**/

char	*cb_menu_sel_obj_auto( menu_t **pp, menu_t **dflt )
{
	g_sel_obj_trgt_kind = TRGT_KIND_AUTO;

	return menu_auto_mark( pp, dflt );
}

/**/

bool_t	menu_switch_mark_mbr(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
)
{
	switch( trgt_kind_2 ){
	case TRGT_KIND_NULL:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		return FALSE;
	case TRGT_KIND_MBR:
		return menu_mark_mbr( pos1, pos2 );
	case TRGT_KIND_MNSTR:
	case TRGT_KIND_MNSTR_NULL:
		return menu_mark_mnstr( pos1, pos2 );
	case TRGT_KIND_ITEM:
		return menu_mark_item( pos1, pos2 );
	case TRGT_KIND_DOOR:
		return menu_mark_door( pos1, pos2 );
	case TRGT_KIND_TRAP:
		return menu_mark_trap( pos1, pos2 );
	case TRGT_KIND_QUEUE:
		return FALSE;
	case TRGT_KIND_SQUARE:
		return menu_mark_square( pos1 );
	case TRGT_KIND_POS:
		return menu_mark_pos( pos1, pos2 );
	}

	return FALSE;
}

/**/

bool_t	menu_switch_mark_mnstr(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
)
{
	if( trgt_kind_2 == TRGT_KIND_MBR ){
		return menu_mark_mnstr( pos2, pos1 );
	} else if( trgt_kind_2 == TRGT_KIND_SQUARE ){
		party_t	*pty = get_party();
		long	i;
		pos_t	pos3;

		for( i = 0; i < MBR_MAX_N; i++ ){
			if( chk_flg_or( pty->mbr[i]->stat,
					FLG_STAT_NOT_EXIST
					| FLG_STAT_DEAD ) ){
				continue;
			}
			pos3.x = pty->mbr[i]->x;
			pos3.y = pty->mbr[i]->y;
			menu_mark_mnstr( pos3, pos1 );
		}
		return TRUE;
	}

	return FALSE;
}

/**/

bool_t	menu_switch_mark_item(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
)
{
	if( trgt_kind_2 == TRGT_KIND_MBR )
		return menu_mark_item( pos2, pos1 );

	return FALSE;
}

/**/

bool_t	menu_switch_mark_door(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
)
{
	if( trgt_kind_2 == TRGT_KIND_MBR )
		return menu_mark_door( pos2, pos1 );

	return FALSE;
}

/**/

bool_t	menu_switch_mark_trap(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
)
{
	if( trgt_kind_2 == TRGT_KIND_MBR )
		return menu_mark_trap( pos2, pos1 );

	return FALSE;
}

/**/

bool_t	menu_switch_mark_square(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
)
{
	if( trgt_kind_2 == TRGT_KIND_POS ){
		return menu_mark_square_pos( pos2 );
	} else if( trgt_kind_2 == TRGT_KIND_MBR ){
		return menu_mark_square( pos2 );
	} else if( trgt_kind_2 == TRGT_KIND_MNSTR ){
		party_t	*pty = get_party();
		long	i;
		pos_t	pos3;

		for( i = 0; i < MBR_MAX_N; i++ ){
			if( chk_flg_or( pty->mbr[i]->stat,
					FLG_STAT_NOT_EXIST
					| FLG_STAT_DEAD ) ){
				continue;
			}
			pos3.x = pty->mbr[i]->x;
			pos3.y = pty->mbr[i]->y;
			menu_mark_mnstr( pos3, pos2 );
		}
		return TRUE;
	}

	return FALSE;
}

/**/

bool_t	menu_switch_mark_pos(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
)
{
	if( trgt_kind_2 == TRGT_KIND_POS ){
		return menu_mark_square_pos( pos2 );
	} else if( trgt_kind_2 == TRGT_KIND_SQUARE ){
		return menu_mark_square_pos( pos1 );
	} else if( trgt_kind_2 == TRGT_KIND_MBR ){
		return menu_mark_pos( pos2, pos1 );
	}

	return FALSE;
}

/**/

bool_t	menu_mark_mbr( pos_t pos1, pos_t pos2 )
{
	mbr_t	*mbr, *mbr2;
	char	*str;

	str = menu_dist_mbr();
	if( str != NULL )
		return FALSE;

	if( g_dist_chr_kind != CHR_KIND_MBR )
		return FALSE;

	mbr = get_mbr( pos1.x, pos1.y );
	mbr2 = get_mbr( pos2.x, pos2.y );
	if( mbr == NULL )
		return FALSE;
	if( mbr2 == NULL )
		return FALSE;

	if( !set_chr_act( mbr, g_sel_act_kind, NULL, NULL, 0, 0 ) )
		return FALSE;

	mark_mbr( mbr, mbr2, g_sel_dist );
	draw_mbr_stat( mbr );

	return TRUE;
}

/**/

bool_t	menu_mark_mnstr( pos_t pos1, pos_t pos2 )
{
	mbr_t	*mbr;
	mnstr_t	*mnstr;
	char	*str;

	str = menu_dist_mnstr();
	if( str != NULL )
		return FALSE;
	if( g_dist_chr_kind != CHR_KIND_MNSTR )
		return FALSE;

	mbr = get_mbr( pos1.x, pos1.y );
	mnstr = get_mnstr( pos2.x, pos2.y );
	if( mbr == NULL )
		return FALSE;

	if( !set_chr_act( mbr, g_sel_act_kind, NULL, NULL, 0, 0 ) )
		return FALSE;

	mbr->act.dflt_kind_mnstr = mbr->act.kind;
	str_nz_cpy( mbr->act.dflt_msg_mnstr, mbr->act.msg,
			ACT_MSG_MAX_BYTE );

	if( mnstr == NULL )
		mark_mnstr_null( mbr, pos2.x, pos2.y, g_sel_dist );
	else
		mark_mnstr( mbr, mnstr, g_sel_dist );

	draw_mbr_stat( mbr );

	return TRUE;
}

/**/

bool_t	menu_mark_item( pos_t pos1, pos_t pos2 )
{
	g_mark_sel_mbr = get_mbr( pos1.x, pos1.y );
	g_mark_sel_item = get_item( pos2.x, pos2.y );

	if( g_mark_sel_mbr == NULL )
		return FALSE;
	if( g_mark_sel_item == NULL )
		return FALSE;

	exec_menu( ls_menu_mark_item, NULL, NULL );

	return TRUE;
}

/**/

char	*cb_menu_mark_item( menu_t **pp, menu_t **dflt )
{
	act_kind_t	kind;

	kind = (act_kind_t)(long)((*pp)->arg);

	if( !set_chr_act( g_mark_sel_mbr, kind, NULL, NULL, 0, 0 ) )
		return STR_MENU_CANCEL;

	mark_item( g_mark_sel_mbr, g_mark_sel_item, DIST_NEAR );

	draw_mbr_stat( g_mark_sel_mbr );

	return NULL;
}

/**/

bool_t	menu_mark_door( pos_t pos1, pos_t pos2 )
{
	g_mark_sel_mbr = get_mbr( pos1.x, pos1.y );
	g_mark_sel_door = get_door( pos2.x, pos2.y );

	if( g_mark_sel_mbr == NULL )
		return FALSE;
	if( g_mark_sel_door == NULL )
		return FALSE;

	exec_menu( ls_menu_mark_door, NULL, NULL );

	return TRUE;
}

/**/

char	*cb_menu_mark_door( menu_t **pp, menu_t **dflt )
{
	act_kind_t	kind;

	kind = (act_kind_t)(long)((*pp)->arg);

	if( !set_chr_act( g_mark_sel_mbr, kind, NULL, NULL, 0, 0 ) )
		return STR_MENU_CANCEL;

	mark_door( g_mark_sel_mbr, g_mark_sel_door, DIST_NEAR );

	draw_mbr_stat( g_mark_sel_mbr );

	return NULL;
}

/**/

bool_t	menu_mark_trap( pos_t pos1, pos_t pos2 )
{
	g_mark_sel_mbr = get_mbr( pos1.x, pos1.y );
	g_mark_sel_trap = get_trap( pos2.x, pos2.y );

	if( g_mark_sel_mbr == NULL )
		return FALSE;
	if( g_mark_sel_trap == NULL )
		return FALSE;

	exec_menu( ls_menu_mark_trap, NULL, NULL );

	return TRUE;
}

/**/

char	*cb_menu_mark_trap( menu_t **pp, menu_t **dflt )
{
	act_kind_t	kind;

	kind = (act_kind_t)(long)((*pp)->arg);

	if( !set_chr_act( g_mark_sel_mbr, kind, NULL, NULL, 0, 0 ) )
		return STR_MENU_CANCEL;

	mark_trap( g_mark_sel_mbr, g_mark_sel_trap, DIST_NEAR );

	draw_mbr_stat( g_mark_sel_mbr );

	return NULL;
}

/**/

bool_t	menu_mark_square( pos_t pos1 )
{
	mbr_t	*mbr;

	mbr = get_mbr( pos1.x, pos1.y );
	if( mbr == NULL )
		return FALSE;

	mark_square( mbr );
	clr_chr_act( mbr );

	draw_mbr_stat( mbr );

	return TRUE;
}

/**/

bool_t	menu_mark_pos( pos_t pos1, pos_t pos2 )
{
	mbr_t	*mbr;

	mbr = get_mbr( pos1.x, pos1.y );
	if( mbr == NULL )
		return FALSE;

	if( !set_chr_act( mbr, ACT_KIND_NULL, NULL, NULL, 0, 0 ) )
		return FALSE;

	str_nz_cpy( mbr->act.msg, MSG_TRGT_POS, ACT_MSG_MAX_BYTE );
	mark_pos( mbr, pos2.x, pos2.y, DIST_NEAR );

	draw_mbr_stat( mbr );

	return TRUE;
}

/**/

bool_t	menu_mark_square_pos( pos_t pos )
{
	square_t	*sq;
	bool_t	flg_loop;

	print_msg( FLG_NULL, MSG_MENU_MARK_SQUARE_POS );

	sq = get_square_mbr();

	sq->pre_x = sq->x;
	sq->pre_y = sq->y;

	flg_loop = TRUE;
	while( flg_loop ){
		switch( get_key( g_flg_clr_key_buf ) ){
		case CASE_CANCEL:
		case CASE_EXEC:
			return FALSE;
			break;
		case CASE_ENTER:
		case CASE_CRSR_UP:
		case '-':
			sq->dir = SQUARE_DIR_NORTH;
			flg_loop = FALSE;
			break;
		case CASE_CRSR_DOWN:
		case '+':
			sq->dir = SQUARE_DIR_SOUTH;
			flg_loop = FALSE;
			break;
		case CASE_CRSR_LEFT:
		case '/':
			sq->dir = SQUARE_DIR_WEST;
			flg_loop = FALSE;
			break;
		case CASE_CRSR_RIGHT:
		case '*':
			sq->dir = SQUARE_DIR_EAST;
			flg_loop = FALSE;
			break;
		}
	}

	sq->x = pos.x;
	sq->y = pos.y;
	set_square_mbr( sq );
	reset_mbr_dir();

	clr_msg();
	draw_square();

	return TRUE;
}

/**/

char	*menu_dist_mbr( void )
{
	g_dist_chr_kind = CHR_KIND_MBR;
	g_sel_dist = DIST_NEAR;
	g_sel_act_kind = ACT_KIND_NULL;

	return exec_menu( ls_menu_dist, NULL, NULL );
}

/**/

char	*menu_dist_mnstr( void )
{
	g_dist_chr_kind = CHR_KIND_MNSTR;
	g_sel_dist = DIST_NEAR;
	g_sel_act_kind = ACT_KIND_NULL;

	return exec_menu( ls_menu_dist, NULL, NULL );
}

/**/

char	*cb_menu_dist_init( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	char	*dflt_path;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	if( g_sel_mbr_n >= MBR_MAX_N )
		return STR_MENU_ERR;

	g_sel_dist = DIST_NEAR;
	g_sel_act_kind = ACT_KIND_NULL;

	dflt_path = "near";

	if( g_dist_chr_kind == CHR_KIND_MBR ){
		dflt_path = "near";
	} else if( g_dist_chr_kind == CHR_KIND_MNSTR ){
		switch( pty->mbr[g_sel_mbr_n]->trgt.dist ){
		case DIST_NEAR:
			dflt_path = "near";
			break;
		case DIST_MEDIUM:
			dflt_path = "medium";
			break;
		case DIST_FAR:
			dflt_path = "far";
			break;
		}
	} else {
		return STR_MENU_ERR;
	}

	*dflt = srch_menu( *pp, dflt_path );
	if( *dflt == NULL )
		return STR_MENU_ERR;

	return NULL;
}

/**/

char	*cb_menu_dist( menu_t **pp, menu_t **dflt )
{
	char	*dflt_path;

	dflt_path = "tail";

	switch( g_dist_chr_kind ){
	case CHR_KIND_MBR:
		if( strcmp( (char *)((*pp)->arg), "near" ) == 0 ){
			g_sel_dist = DIST_NEAR;
		} else if( strcmp( (char *)((*pp)->arg), "medium" ) == 0 ){
			g_sel_dist = DIST_MEDIUM;
		} else if( strcmp( (char *)((*pp)->arg), "far" ) == 0 ){
			g_sel_dist = DIST_FAR;
		} else {
			return STR_MENU_ERR;
		}
		dflt_path = "tail";
		break;
	case CHR_KIND_MNSTR:
		if( strcmp( (char *)((*pp)->arg), "near" ) == 0 ){
			g_sel_dist = DIST_NEAR;
			dflt_path = "fight";
		} else if( strcmp( (char *)((*pp)->arg), "medium" ) == 0 ){
			g_sel_dist = DIST_MEDIUM;
			dflt_path = "throw";
		} else if( strcmp( (char *)((*pp)->arg), "far" ) == 0 ){
			g_sel_dist = DIST_FAR;
			dflt_path = "tail";
		} else {
			return STR_MENU_ERR;
		}
		break;
	default:
		return STR_MENU_ERR;
	}

	*dflt = srch_menu( *pp, dflt_path );
	if( *dflt == NULL )
		return STR_MENU_ERR;

	return NULL;
}

/**/

char	*cb_menu_dist_act( menu_t **pp, menu_t **dflt )
{
	char	*str_act;

	str_act = (char *)((*pp)->arg);

	if( g_dist_chr_kind == CHR_KIND_MBR ){
		if( strcmp( str_act, "fight" ) == 0 ){
			g_sel_act_kind = ACT_KIND_MBR_FIGHT;
		} else if( strcmp( str_act, "throw" ) == 0 ){
			g_sel_act_kind = ACT_KIND_MBR_THROW;
		} else if( strcmp( str_act, "steal" ) == 0 ){
			g_sel_act_kind = ACT_KIND_MBR_STEAL;
		} else if( strcmp( str_act, "tail" ) == 0 ){
			g_sel_act_kind = ACT_KIND_MBR_TAIL;
		} else {
			return STR_MENU_ERR;
		}
	} else if( g_dist_chr_kind == CHR_KIND_MNSTR ){
		if( strcmp( str_act, "fight" ) == 0 ){
			g_sel_act_kind = ACT_KIND_MNSTR_FIGHT;
		} else if( strcmp( str_act, "throw" ) == 0 ){
			g_sel_act_kind = ACT_KIND_MNSTR_THROW;
		} else if( strcmp( str_act, "steal" ) == 0 ){
			g_sel_act_kind = ACT_KIND_MNSTR_STEAL;
		} else if( strcmp( str_act, "tail" ) == 0 ){
			g_sel_act_kind = ACT_KIND_MNSTR_TAIL;
		} else {
			return STR_MENU_ERR;
		}
	} else {
		return STR_MENU_ERR;
	}

	return NULL;
}

/**/

char	*cb_menu_item( menu_t **pp, menu_t **dflt )
{
	long pre_sel_mbr_n;
	party_t	*pty = get_party();
	menu_t	*ls;
	mbr_t	*mbr;
	long	i, j, k;

	pre_sel_mbr_n = static_cb_menu_item__pre_sel_mbr_n;

	if( g_sel_mbr_n <= -1 )
		g_sel_mbr_n = pre_sel_mbr_n;
	else
		pre_sel_mbr_n = g_sel_mbr_n;
	static_cb_menu_item__pre_sel_mbr_n = pre_sel_mbr_n;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	if( g_sel_mbr_n >= MBR_MAX_N )
		return STR_MENU_ERR;
	mbr = pty->mbr[g_sel_mbr_n];

	if( chk_flg_or( mbr->stat,
			FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		print_msg( FLG_NULL, MSG_ERR_MENU_SEL_ITEM, mbr->name );
		return STR_MENU_CANCEL;
	}

	set_menu_dflt_main( *pp );

	ls = ls_menu_item;
	k = 0;

	str_nz_cpy( ls[k].path, "/item", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = cb_menu_item_init;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MBR_MAX_N; i++ ){
		item_t	*item, *p;

		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		str_nz_cpy( ls[k].path, "/item/--", MENU_PATH_MAX_LEN );
		str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = '\0';
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, pty->mbr[i]->name,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = NULL;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		item = get_mbr_item_asgn( pty->mbr[i] );
		if( item != NULL ){
			p = item->next;
			for( j = 0; j < MBR_ITEM_MAX_N; j++, p = p->next ){
				if( p == item )
					break;

				sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
						"/item/%ld%c",
						i, (char)('A' + j) );
				str_nz_cpy( ls[k].kind, "<Branch>",
						MENU_KIND_MAX_LEN );
				ls[k].accel_key = (char)('A' + j);
				ls[k].short_key[0] = '\0';
				ls[k].n_msg = N_MSG_NULL;
				sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
						" %s", p->name );
				ls[k].call_back = cb_menu_item_sel;
				ls[k].arg = NULL;
				ls[k].flg = FLG_NULL;
				k++;
			}
		}

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/item/%ld%s", i, "equip" );
		str_nz_cpy( ls[k].kind, "<Branch>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'Z';
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, MSG_MENU_ITEM_LS_EQUIP,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_goto_equip;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		str_nz_cpy( ls[k].path, "/item/--", MENU_PATH_MAX_LEN );
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
	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_item_init( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	mbr_n, srch_mbr_n;
	menu_t	*p;
	long	i;

	srch_mbr_n = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( i == g_sel_mbr_n )
			break;
		if( !chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			srch_mbr_n++;
	}

	mbr_n = 0;
	p = *pp;
	for( i = 1; i < LOOP_MAX_4000; i++ ){
		if( p[i].path[0] == '\0' )
			return STR_MENU_ERR;

		if( mbr_n == srch_mbr_n ){
			if( strcmp( p[i].kind, "<Branch>" ) == 0 ){
				*dflt = &(p[i]);
				return NULL;
			}
		}

		if( strcmp( p[i].kind, "<PageSeparator>" ) == 0 )
			mbr_n++;
	}

	return STR_MENU_ERR;
}

/**/

char	*cb_menu_item_sel( menu_t **pp, menu_t **dflt )
{
	char	*node;
	party_t	*pty = get_party();
	long	i, item_idx;
	item_t	*item_head, *item;

	node = strrchr( (*pp)->path, '/' );
	if( node == NULL )
		return STR_MENU_ERR;
	node++;

	g_sel_mbr_n = strtol( node, (char **)NULL, 10 );
	g_sel_item = NULL;

	item_idx = node[1] - 'A';

	item_head = get_mbr_item_asgn( pty->mbr[g_sel_mbr_n] );
	if( item_head == NULL )
		return STR_MENU_ERR;

	item = item_head->next;
	for( i = 0; i < MBR_ITEM_MAX_N; i++ ){
		if( item == item_head )
			return STR_MENU_ERR;
		if( i == item_idx )
			break;
		item = item->next;
	}
	if( i >= MBR_ITEM_MAX_N )
		return STR_MENU_ERR;

	g_sel_item = item;

	*pp = ls_menu_item_sel;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_item_sel_init( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;

	if( chk_flg_or( pty->mbr[g_sel_mbr_n]->stat,
			FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		return menu_item_sel_init_dead( pp, dflt );
	}

	set_flg_menu( *pp, NULL, FLG_MENU_HIDDEN );

	clr_flg_menu( *pp, "equip", FLG_MENU_HIDDEN );
	clr_flg_menu( *pp, "ready throw", FLG_MENU_HIDDEN );
	clr_flg_menu( *pp, "send", FLG_MENU_HIDDEN );
	clr_flg_menu( *pp, "receive", FLG_MENU_HIDDEN );
	clr_flg_menu( *pp, "drop", FLG_MENU_HIDDEN );
	clr_flg_menu( *pp, "alias", FLG_MENU_HIDDEN );
	clr_flg_menu( *pp, "check", FLG_MENU_HIDDEN );

	if( chk_have_chest( pty->mbr[g_sel_mbr_n] ) )
		clr_flg_menu( *pp, "put in chest", FLG_MENU_HIDDEN );

	switch( g_sel_item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		return STR_MENU_ERR;
	case ITEM_KIND_WPN:
	case ITEM_KIND_ARMOR:
		break;
	case ITEM_KIND_POTION:
		clr_flg_menu( *pp, "quaff", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "fill lamp", FLG_MENU_HIDDEN );
		break;
	case ITEM_KIND_SCROLL:
		clr_flg_menu( *pp, "read", FLG_MENU_HIDDEN );
		break;
	case ITEM_KIND_STICK:
		clr_flg_menu( *pp, "zap", FLG_MENU_HIDDEN );
		break;
	case ITEM_KIND_ACCE:
	case ITEM_KIND_INST:
	case ITEM_KIND_ANTHOLOGY:
		break;
	case ITEM_KIND_LIGHT:
		clr_flg_menu( *pp, "rub", FLG_MENU_HIDDEN );
		break;
	case ITEM_KIND_SPIKE:
		break;
	case ITEM_KIND_FOOD:
		clr_flg_menu( *pp, "eat", FLG_MENU_HIDDEN );
		break;
	case ITEM_KIND_CHEST:
		set_flg_menu( *pp, "put in chest", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "list chest", FLG_MENU_HIDDEN );
		break;
	case ITEM_KIND_TOBACCO:
		clr_flg_menu( *pp, "smoke", FLG_MENU_HIDDEN );
		break;
	case ITEM_KIND_PIPE:
		break;
	case ITEM_KIND_DISPOSAL:
		clr_flg_menu( *pp, "dispose", FLG_MENU_HIDDEN );
		break;
	case ITEM_KIND_RARE_GOODS:
	case ITEM_KIND_BONE:
	case ITEM_KIND_COIN:
	case ITEM_KIND_JUNK:
		break;
	}

	return NULL;
}

/**/

char	*menu_item_sel_init_dead( menu_t **pp, menu_t **dflt )
{
	set_flg_menu( *pp, NULL, FLG_MENU_HIDDEN );

	clr_flg_menu( *pp, "receive", FLG_MENU_HIDDEN );
	clr_flg_menu( *pp, "check", FLG_MENU_HIDDEN );

	return NULL;
}

/**/

char	*cb_menu_item_use( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	mbr_t	*mbr;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	mbr = pty->mbr[g_sel_mbr_n];

	if( set_chr_act( mbr, (act_kind_t)(long)((*pp)->arg),
			g_sel_item, NULL, 0, 0 ) ){
		return NULL;
	}
	return STR_MENU_ERR;
}

/**/

char	*cb_menu_item_zap( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	trgt_kind_t	trgt_kind;
	mbr_t	*mbr, *mbr2;
	mnstr_t	*mnstr;
	item_t	*item;
	door_t	*door;
	trap_t	*trap;
	char	*str;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	mbr = pty->mbr[g_sel_mbr_n];

	move_crsr_mbr_trgt( mbr );

	str = exec_menu_point_crsr();
	if( str != NULL )
		return str;

	str = exec_menu_sel_obj( &trgt_kind, g_main_crsr );
	if( str != NULL )
		return str;

	switch( trgt_kind ){
	case TRGT_KIND_NULL:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		return STR_MENU_ERR;
	case TRGT_KIND_MBR:
		mbr2 = get_mbr( g_main_crsr.x, g_main_crsr.y );
		if( mbr2 == NULL )
			return STR_MENU_ERR;

		mark_mbr( mbr, mbr2, DIST_FAR );
		break;
	case TRGT_KIND_MNSTR:
		mnstr = get_mnstr( g_main_crsr.x, g_main_crsr.y );
		if( mnstr == NULL )
			return STR_MENU_ERR;

		mark_mnstr_no_regist( mbr, mnstr, DIST_FAR );
		break;
	case TRGT_KIND_MNSTR_NULL:
	case TRGT_KIND_POS:
		mark_mnstr_null_no_regist(
				mbr, g_main_crsr.x, g_main_crsr.y, DIST_FAR );
		break;
	case TRGT_KIND_ITEM:
		item = get_item( g_main_crsr.x, g_main_crsr.y );
		if( item == NULL )
			return STR_MENU_ERR;

		mark_item( mbr, item, DIST_FAR );
		break;
	case TRGT_KIND_DOOR:
		door = get_door( g_main_crsr.x, g_main_crsr.y );
		if( door == NULL )
			return STR_MENU_ERR;

		mark_door( mbr, door, DIST_FAR );
		break;
	case TRGT_KIND_TRAP:
		trap = get_trap( g_main_crsr.x, g_main_crsr.y );
		if( trap == NULL )
			return STR_MENU_ERR;

		mark_trap( mbr, trap, DIST_FAR );
		break;
	case TRGT_KIND_QUEUE:
	case TRGT_KIND_SQUARE:
		break;
	}

	if( !set_chr_act( mbr, (act_kind_t)(long)((*pp)->arg),
			g_sel_item, NULL, 0, 0 ) ){
		return STR_MENU_ERR;
	}

	return NULL;
}

/**/

char	*cb_menu_item_smoke( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	mbr_t	*mbr;
	char	*ret;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	mbr = pty->mbr[g_sel_mbr_n];

	ret = cb_menu_item_use( pp, dflt );

	if( ret == NULL ){
		mbr->act.n = EQUIP_KIND_HEAD;

		str_nz_cpy( mbr->act.msg, MSG_ACT_TOBACCO_SMOKE,
				ACT_MSG_MAX_BYTE );
	}

	return ret;
}

/**/

char	*cb_menu_item_fill_lamp( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	mbr_t	*mbr;
	item_t	*lamp;
	light_tab_t	*tab;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	mbr = pty->mbr[g_sel_mbr_n];

	lamp = get_mbr_item_asgn_equip( mbr );
	if( lamp == NULL )
		return STR_MENU_ERR;
	lamp = &(lamp[EQUIP_KIND_LIGHT_SOURCE]);

	tab = get_light_tab( lamp->dat.light.kind,
			lamp->dat.light.wish_level );

	if( (lamp->kind != ITEM_KIND_LIGHT) || !tab->flg_fill ){
		print_msg( FLG_NULL, MSG_ERR_FILL_LAMP );
		return STR_MENU_ERR;
	}

	if( !set_chr_act( mbr, (act_kind_t)(long)((*pp)->arg),
			g_sel_item, NULL, 0, 0 ) ){
		return STR_MENU_ERR;
	}

	return NULL;
}

/**/

char	*cb_menu_item_ready_throw( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	mbr_t	*mbr;
	char	*ret;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	mbr = pty->mbr[g_sel_mbr_n];

	ret = cb_menu_item_use( pp, dflt );

	if( ret == NULL )
		mbr->act.n = EQUIP_KIND_ARW;

	return ret;
}

/**/

char	*cb_menu_item_send( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	mbr_t	*mbr;
	mbr_t	*mbr2;
	char	*str;
	long	n;

	if( g_sel_item == NULL )
		return STR_MENU_ERR;
	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;

	mbr = pty->mbr[g_sel_mbr_n];
	mbr2 = mbr;

	/* 誰に送るか選ぶ */
	str = exec_menu_sel_mbr( &mbr2, MSG_TTL_MENU_ITEM_SEND,
			TRUE, FALSE );
	if( str != NULL )
		return str;

	/* 個数を選ぶ */
	n = g_sel_item->n;
	str = exec_menu_sel_num( &n, 1, n );
	if( str != NULL )
		return str;

	if( !set_chr_act( mbr, ACT_KIND_ITEM_SEND,
			g_sel_item, mbr2, n, 0 ) ){
		return STR_MENU_CANCEL;
	}
	mark_mbr( mbr, mbr2, DIST_NEAR );

	if( !g_flg_send_item_exec_turn ){
		send_item( mbr );
		clr_chr_trgt_act( mbr, TRUE );
	}

	return "/item";
}

/**/

char	*cb_menu_item_receive( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	mbr_t	*mbr;
	mbr_t	*mbr2;
	char	*str;
	long	n;

	if( g_sel_item == NULL )
		return STR_MENU_ERR;
	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;

	mbr = pty->mbr[g_sel_mbr_n];
	mbr2 = mbr;

	/* 誰に送るか選ぶ */
	str = exec_menu_sel_mbr( &mbr2, MSG_TTL_MENU_ITEM_RECEIVE,
			TRUE, FALSE );
	if( str != NULL )
		return str;

	/* 個数を選ぶ */
	n = g_sel_item->n;
	str = exec_menu_sel_num( &n, 1, n );
	if( str != NULL )
		return str;

	if( !set_chr_act( mbr2, ACT_KIND_ITEM_RECEIVE,
			g_sel_item, mbr, n, 0 ) ){
		return STR_MENU_CANCEL;
	}
	mark_mbr( mbr2, mbr, DIST_NEAR );

	if( !g_flg_send_item_exec_turn ){
		receive_item( mbr2 );
		clr_chr_trgt_act( mbr2, TRUE );
	}

	return "/item";
}

/**/

char	*cb_menu_item_put_in_chest( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*res;
	party_t	*pty = get_party();
	mbr_t	*mbr;
	item_t	*tmp;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	mbr = pty->mbr[g_sel_mbr_n];

	if( g_sel_item == NULL )
		return STR_MENU_ERR;

	n = g_sel_item->n;
	res = exec_menu_sel_num( &n, 1, g_sel_item->n );
	if( res != NULL )
		return res;

	tmp = alloc_item();
	if( tmp == NULL )
		return STR_MENU_ERR;

	copy_item( tmp, g_sel_item );
	inc_item( tmp, -(tmp->n - n) );

	if( !put_item_in_chest_quick( mbr, tmp ) ){
		del_item( tmp );
		return STR_MENU_CANCEL;
	}

	inc_item( g_sel_item, -n );

	return "/item";
}

/**/

char	*cb_menu_item_ls_chest( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	menu_t	*ls;
	mbr_t	*mbr;
	item_t	*chest, *head, *p;
	long	j, k;

	if( g_sel_item == NULL )
		return STR_MENU_ERR;
	if( g_sel_item->kind != ITEM_KIND_CHEST )
		return STR_MENU_ERR;
	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	if( g_sel_mbr_n >= MBR_MAX_N )
		return STR_MENU_ERR;

	mbr = pty->mbr[g_sel_mbr_n];
	chest = g_sel_item;

	if( chest->dat.chest.trap != NULL ){
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_MENU_LS_CHEST_TRAP,
				chest->name );
		curs_attrset_dflt();

		return STR_MENU_CANCEL;
	}

	if( chk_flg_or( mbr->stat,
			FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		print_msg( FLG_NULL, MSG_ERR_MENU_SEL_ITEM, mbr->name );
		return STR_MENU_CANCEL;
	}

	ls = ls_menu_chest;
	k = 0;

	str_nz_cpy( ls[k].path, "/chest", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/chest/--", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_ITEM_LS_CHEST, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	head = chest->dat.chest.contents;
	p = head->next;
	for( j = 0; j < CHEST_HOLD_MAX_N; j++, p = p->next ){
		if( p == head )
			break;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/chest/%ld", j );
		str_nz_cpy( ls[k].kind, "<OpenWinItem>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + j);
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE, "%s", p->name );
		ls[k].call_back = cb_menu_chest_sel;
		ls[k].arg = (void *)p;
		ls[k].flg = FLG_NULL;
		k++;
	}

	if( j <= 0 ){
		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/chest/%ld", j );
		str_nz_cpy( ls[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + j);
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_ITEM_NO_SEL;
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE, MSG_ITEM_NO_SEL );
		ls[k].call_back = cb_menu_chest_sel;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;
	}

	ls[k].path[0] = '\0';

	while( 1 ){
		char	*res;

		res = exec_menu( ls, NULL, NULL );
		if( res == NULL )
			continue;
		if( strcmp( res, STR_MENU_CANCEL ) == 0 )
			return "/item";

		return res;
	}

	return NULL;
}

/**/

char	*cb_menu_chest_sel( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	mbr_t	*mbr;
	item_t	*item, *tmp;
	long	n;
	char	*res;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	if( g_sel_mbr_n >= MBR_MAX_N )
		return STR_MENU_ERR;

	mbr = pty->mbr[g_sel_mbr_n];
	item = (item_t *)((*pp)->arg);
	if( mbr == NULL )
		return STR_MENU_ERR;
	if( item == NULL )
		return STR_MENU_CANCEL;

	n = item->n;
	res = exec_menu_sel_num( &n, 1, item->n );
	if( res != NULL )
		return res;

	tmp = alloc_item();
	if( tmp == NULL )
		return STR_MENU_ERR;

	copy_item( tmp, item );
	inc_item( tmp, -(tmp->n - n) );

	if( !give_mbr_item( mbr, tmp, FALSE ) ){
		del_item( tmp );
		return STR_MENU_CANCEL;
	}

	inc_item( item, -n );

	return "/item sel/list chest";
}

/**/

char	*cb_menu_item_drop( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*str, *ret;
	party_t	*pty = get_party();
	mbr_t	*mbr;

	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	mbr = pty->mbr[g_sel_mbr_n];

	if( g_sel_item == NULL )
		return STR_MENU_ERR;

	n = g_sel_item->n;
	str = exec_menu_sel_num( &n, 1, g_sel_item->n );
	if( str != NULL )
		return str;

	ret = cb_menu_item_use( pp, dflt );

	if( ret == NULL )
		mbr->act.n = n;

	return ret;
}

/**/

char	*cb_menu_item_alias( menu_t **pp, menu_t **dflt )
{
	if( g_sel_item == NULL )
		return STR_MENU_ERR;

	set_item_alias( g_sel_item );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_item_chk( menu_t **pp, menu_t **dflt )
{
	if( g_sel_item == NULL )
		return STR_MENU_ERR;

	chk_item_data( g_sel_item );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_goto_equip( menu_t **pp, menu_t **dflt )
{
	return "/equip";
}

/**/

long	get_equip_ttl_max_len( void )
{
	long	max_len;
	long	i;

	max_len = 1;
	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		long	len;

		len = str_len_draw( MSG( ls_equip_msg[i].n_msg ) );
		max_len = max_l( max_len, len );
	}

	return max_len;
}

/**/

char	*cb_menu_equip( menu_t **pp, menu_t **dflt )
{
	long	pre_sel_mbr_n = 0;
	party_t	*pty = get_party();
	menu_t	*ls;
	mbr_t	*mbr;
	long	equip_ttl_max_len;
	long	i, j, k;

	if( g_sel_mbr_n <= -1 )
		g_sel_mbr_n = pre_sel_mbr_n;
	else
		pre_sel_mbr_n = g_sel_mbr_n;
	if( g_sel_mbr_n <= -1 )
		return STR_MENU_ERR;
	if( g_sel_mbr_n >= MBR_MAX_N )
		return STR_MENU_ERR;
	mbr = pty->mbr[g_sel_mbr_n];

	if( chk_flg_or( mbr->stat,
			FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		print_msg( FLG_NULL, MSG_ERR_MENU_SEL_EQUIP, mbr->name );
		return STR_MENU_CANCEL;
	}

	set_menu_dflt_main( *pp );

	equip_ttl_max_len = get_equip_ttl_max_len();

	ls = ls_menu_equip;
	k = 0;

	str_nz_cpy( ls[k].path, "/equip",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = cb_menu_equip_init;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MBR_MAX_N; i++ ){
		item_t	*equip;

		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		str_nz_cpy( ls[k].path, "/equip/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( ls[k].kind, "<Title>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = '\0';
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg,
				pty->mbr[i]->name, MENU_MSG_MAX_BYTE );
		ls[k].call_back = NULL;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		equip = get_mbr_item_asgn_equip( pty->mbr[i] );
		for( j = 0; j < EQUIP_KIND_MAX_N; j++ ){
			equip_kind_t	eq_k;
			char	*msg;

			if( equip == NULL )
				break;

			eq_k = ls_equip_msg[j].kind;

			msg = MSG( ls_equip_msg[j].n_msg );

			sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
					"/equip/%ld%c",
					i, (char)('A' + j) );
			str_nz_cpy( ls[k].kind, "<Branch>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = (char)('A' + j);
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_NULL;
			if( equip[eq_k].kind == ITEM_KIND_NULL ){
				sn_printf( ls[k].msg,
						MENU_MSG_MAX_BYTE,
						MSG_FMT_EQUIP_NULL,
						equip_ttl_max_len,
						msg );
			} else {
				sn_printf( ls[k].msg,
						MENU_MSG_MAX_BYTE,
						MSG_FMT_EQUIP,
						equip_ttl_max_len,
						msg,
						equip[eq_k].name );
			}
			ls[k].call_back = cb_menu_equip_sel;
			ls[k].arg = (void *)eq_k;
			ls[k].flg = FLG_NULL;
			k++;
		}

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/equip/%ld%s", i, "item" );
		str_nz_cpy( ls[k].kind, "<Branch>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'Z';
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg,
				MSG_MENU_EQUIP_LS_ITEM,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_goto_item;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		str_nz_cpy( ls[k].path, "/equip/--",
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
	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_equip_init( menu_t **pp, menu_t **dflt )
{
	return cb_menu_item_init( pp, dflt );
}

/**/

char	*cb_menu_equip_sel( menu_t **pp, menu_t **dflt )
{
	char	*node;
	party_t	*pty = get_party();
	item_t	*equip;

	node = strrchr( (*pp)->path, '/' );
	if( node == NULL )
		return STR_MENU_ERR;
	node++;

	g_sel_mbr_n = strtol( node, (char **)NULL, 10 );
	g_sel_item = NULL;
	g_sel_equip_kind = (equip_kind_t)(long)((*pp)->arg);

	equip = get_mbr_item_asgn_equip( pty->mbr[g_sel_mbr_n] );
	if( equip == NULL )
		return STR_MENU_ERR;
	g_sel_item = &(equip[g_sel_equip_kind]);

	*pp = ls_menu_equip_sel;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_equip_sel_init( menu_t **pp, menu_t **dflt )
{
	if( g_sel_item->kind == ITEM_KIND_NULL ){
		set_flg_menu( *pp, "take off self", FLG_MENU_HIDDEN );
		set_flg_menu( *pp, "take off other", FLG_MENU_HIDDEN );
	} else {
		clr_flg_menu( *pp, "take off self", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "take off other", FLG_MENU_HIDDEN );
	}

	return NULL;
}

/**/

char	*cb_menu_equip_wear_sel_self( menu_t **pp, menu_t **dflt )
{
	g_flg_equip_self = TRUE;

	return menu_equip_wear_sel( pp, dflt );
}

/**/

char	*cb_menu_equip_wear_sel_other( menu_t **pp, menu_t **dflt )
{
	g_flg_equip_self = FALSE;

	return menu_equip_wear_sel( pp, dflt );
}

/**/

char	*menu_equip_wear_sel( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	menu_t	*ls;
	item_t	*item, *p;
	long	i, k;

	ls = ls_menu_equip_wear_sel;
	k = 0;

	str_nz_cpy( ls[k].path, "/wear", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = cb_menu_equip_wear_init;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	item = get_mbr_item_asgn( pty->mbr[g_sel_mbr_n] );
	if( item == NULL )
		return STR_MENU_ERR;
	p = item->next;
	for( i = 0; i < MBR_ITEM_MAX_N; i++, p = p->next ){
		if( p == item )
			break;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/wear/%c", (char)('A' + i) );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + i);
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, p->name, MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_equip_wear;
		ls[k].arg = p;
		ls[k].flg = FLG_NULL;
		k++;
	}
	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_equip_wear_init( menu_t **pp, menu_t **dflt )
{
	long	i;
	long	n;

	clr_flg_menu( *pp, NULL, FLG_MENU_ALL );

	/* 選択されたスロットに装備出来ないアイテムは隠す */

	n = 0;
	for( i = 0; i < LOOP_MAX_4000; i++ ){
		item_t	*item;

		if( (*pp)[i].path[0] == '\0' )
			break;

		if( strcmp( (*pp)[i].kind, "<Item>" ) != 0 )
			continue;

		item = (item_t *)((*pp)[i].arg);
		if( chk_equip_kind( item, g_sel_equip_kind ) )
			n++;
		else
			(*pp)[i].flg |= FLG_MENU_HIDDEN;
	}
	if( n <= 0 ){
		print_msg( FLG_NULL, MSG_ERR_EQUIP_SEL_ITEM );
		return STR_MENU_CANCEL;
	}

	return NULL;
}

/**/

char	*cb_menu_equip_wear( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	mbr_t	*mbr, *mbr2;
	act_kind_t	kind;

	if( g_flg_equip_self ){
		if( g_sel_mbr_n <= -1 )
			return STR_MENU_ERR;
		mbr = pty->mbr[g_sel_mbr_n];

		mbr2 = mbr;
	} else {
		char	*ret;

		if( g_sel_mbr_n <= -1 )
			return STR_MENU_ERR;
		mbr2 = pty->mbr[g_sel_mbr_n];

		mbr = mbr2;
		ret = exec_menu_sel_mbr( &mbr,
				MSG_TTL_MENU_EQUIP_WEAR_OTHER,
				FALSE, FALSE );
		if( ret != NULL )
			return ret;
	}

	if( mbr == mbr2 )
		kind = ACT_KIND_EQUIP;
	else
		kind = ACT_KIND_EQUIP_MBR;

	if( !set_chr_act( mbr, kind, (item_t *)((*pp)->arg), mbr2,
			g_sel_equip_kind, 0 ) )
		return STR_MENU_CANCEL;

	if( mbr != mbr2 )
		mark_mbr( mbr, mbr2, DIST_NEAR );

	draw_mbr_stat( mbr );

	return NULL;
}

/**/

char	*cb_menu_equip_take_off_self( menu_t **pp, menu_t **dflt )
{
	g_flg_equip_self = TRUE;

	return menu_equip_take_off( pp, dflt );
}

/**/

char	*cb_menu_equip_take_off_other( menu_t **pp, menu_t **dflt )
{
	g_flg_equip_self = FALSE;

	return menu_equip_take_off( pp, dflt );
}

/**/

char	*menu_equip_take_off( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	mbr_t	*mbr, *mbr2;
	act_kind_t	kind;

	if( g_flg_equip_self ){
		if( g_sel_mbr_n <= -1 )
			return STR_MENU_ERR;
		mbr = pty->mbr[g_sel_mbr_n];

		mbr2 = mbr;
	} else {
		char	*ret;

		if( g_sel_mbr_n <= -1 )
			return STR_MENU_ERR;
		mbr2 = pty->mbr[g_sel_mbr_n];

		mbr = mbr2;
		ret = exec_menu_sel_mbr( &mbr,
				MSG_TTL_MENU_EQUIP_TAKE_OFF_OTHER,
				FALSE, FALSE );
		if( ret != NULL )
			return ret;
	}

	if( mbr == mbr2 )
		kind = ACT_KIND_TAKE_OFF;
	else
		kind = ACT_KIND_TAKE_OFF_MBR;

	if( !set_chr_act( mbr, kind, NULL, mbr2, g_sel_equip_kind, 0 ) )
		return STR_MENU_CANCEL;

	if( mbr != mbr2 )
		mark_mbr( mbr, mbr2, DIST_NEAR );

	draw_mbr_stat( mbr );

	return NULL;
}

/**/

char	*cb_menu_goto_item( menu_t **pp, menu_t **dflt )
{
	return "/item";
}

/**/

char	*cb_menu_move( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_main( *pp );

	menu_move_square();

	return NULL;
}

/**/

void	menu_move_square( void )
{
	square_t	*sq;

	sq = get_square_mbr();

	sq->pre_x = sq->x;
	sq->pre_y = sq->y;

	sq->pre_dir = sq->dir;
	sq->dir = SQUARE_DIR_MAX_N;

	/* 移動元と先の向きに合わせてのアンカーの向きを設定する */

	if( labs( sq->x - g_main_crsr.x ) > labs( sq->y - g_main_crsr.y ) ){
		if( g_main_crsr.x < sq->x ){
			sq->dir = SQUARE_DIR_WEST;
		} else if( g_main_crsr.x > sq->x ){
			sq->dir = SQUARE_DIR_EAST;
		}
	} else {
		if( g_main_crsr.y < sq->y ){
			sq->dir = SQUARE_DIR_NORTH;
		} else if( g_main_crsr.y > sq->y ){
			sq->dir = SQUARE_DIR_SOUTH;
		}
	}

	/* 同じ座標でアンカーを設定した場合 90 度づつ回転する */

	if( sq->dir == SQUARE_DIR_MAX_N ){
		switch( sq->pre_dir ){
		case SQUARE_DIR_NORTH:
			sq->dir = SQUARE_DIR_EAST;
			break;
		case SQUARE_DIR_EAST:
			sq->dir = SQUARE_DIR_SOUTH;
			break;
		case SQUARE_DIR_SOUTH:
			sq->dir = SQUARE_DIR_WEST;
			break;
		case SQUARE_DIR_WEST:
			sq->dir = SQUARE_DIR_NORTH;
			break;
		case SQUARE_DIR_MAX_N:
			sq->dir = SQUARE_DIR_NORTH;
			break;
		}
		if( sq->dir == SQUARE_DIR_MAX_N )
			sq->dir = SQUARE_DIR_NORTH;
	}

	sq->x = g_main_crsr.x;
	sq->y = g_main_crsr.y;
	set_square_mbr( sq );
	reset_mbr_dir();

	draw_square();
}

/**/

char	*cb_menu_fight( menu_t **pp, menu_t **dflt )
{
	bool_t	flg_loop;
	pos_t	pos1, pos2;
	char	*str;
	char	c;

	set_menu_dflt_main( *pp );

	flg_loop = FALSE;
	do {
		pos1 = g_main_crsr;
		c = get_chr_mjr_crsr();
		if( c != FACE_MJR_MBR ){
			mbr_t	*mbr;

			flg_loop = TRUE;

			str = exec_menu_sel_mbr( &mbr, NULL, FALSE, FALSE );
			if( str != NULL )
				return str;
			if( mbr == NULL )
				return STR_MENU_ERR;

			g_sel_mbr_n = mbr->mbr_n;
			pos1.x = mbr->x;
			pos1.y = mbr->y;
		}

		str = exec_menu_point_crsr();
		if( str == NULL ){
			flg_loop = FALSE;
		} else {
			if( strcmp( str, STR_MENU_CANCEL ) == 0 )
				continue;
			else
				return str;
		}

		pos2 = g_main_crsr;
		c = get_chr_mjr_crsr();

		if( c == FACE_MJR_MBR ){
			if( !menu_mark_mbr( pos1, pos2 ) )
				return STR_MENU_ERR;
		} else {
			if( !menu_mark_mnstr( pos1, pos2 ) )
				return STR_MENU_ERR;
		}
	} while( flg_loop );

	*pp = NULL;
	return NULL;
}

/**/

char	*cb_menu_load_wiz( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_wizard( *pp );
	menu_load_wiz();

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_save_wiz( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_wizard( *pp );
	menu_save_wiz();

	return STR_MENU_CANCEL;
}

/**/

void	menu_load_wiz( void )
{
	if( menu_load( TRUE, FALSE ) )
		reset_all_save( TRUE );
}

/**/

void	menu_save_wiz( void )
{
	if( menu_save( TRUE ) )
		reset_all_save( TRUE );
}

/**/

bool_t	menu_load( bool_t flg_txt, bool_t flg_new_game )
{
	long	n;
	ask_t	ask;

	n = menu_sel_save_load( FALSE, flg_txt, flg_new_game );
	if( n == SAVE_N_SEL )
		return FALSE;

	ask = exec_menu_ask( MSG_TTL_MENU_ASK_LOAD, ASK_NO, TRUE );
	if( ask != ASK_YES )
		return FALSE;

	load_game_conf();
	load_game_data( flg_txt, n );
	if( n != SAVE_N_AUTO )
		bgn_reg_replay( SAVE_N_BUG_REPO );

	if( flg_txt )
		set_flg_no_save( TRUE );
	else
		set_flg_no_save( FALSE );

	print_msg( FLG_NULL, MSG_MENU_LOAD_SUCCESS, n );

	return TRUE;
}

/**/

bool_t	menu_save( bool_t flg_txt )
{
	return menu_save_n( flg_txt, SAVE_N_SEL );
}

/**/

bool_t	menu_save_n( bool_t flg_txt, long save_n )
{
	ask_t	ask;

	if( !flg_txt && g_flg_no_save ){
		print_msg( FLG_MSG_ERR, MSG_ERR_MENU_NO_SAVE );
		return FALSE;
	}

	if( save_n == SAVE_N_SEL ){
		save_n = menu_sel_save_load( TRUE, flg_txt, FALSE );

		if( save_n == SAVE_N_AUTO ){
			print_msg( FLG_MSG_ERR,
					MSG_ERR_MENU_SAVE_N_SEL_AUTO );
			return FALSE;
		}

		if( save_n == SAVE_N_SEL )
			return FALSE;
	}

	if( save_n != SAVE_N_AUTO ){
		ask = exec_menu_ask( MSG_TTL_MENU_ASK_SAVE, ASK_NO, TRUE );
		if( ask != ASK_YES )
			return FALSE;
	}

	save_dun();
	save_town();
	save_game_conf();
	save_game_data( flg_txt, save_n );
	if( save_n != SAVE_N_AUTO )
		bgn_reg_replay( SAVE_N_BUG_REPO );

	if( flg_txt )
		print_msg( FLG_NULL, MSG_MENU_SAVE_SUCCESS_TXT, save_n );
	else
		print_msg( FLG_NULL, MSG_MENU_SAVE_SUCCESS_BIN, save_n );

	return TRUE;
}

/**/

long	menu_sel_save_load(
	bool_t flg_save, bool_t flg_txt, bool_t flg_new_game
)
{
	menu_t	*ls;
	menu_t	*dflt;
	char	key;
	long	k;
	char	*ret;
	long	i;

	ls = ls_menu_save_load;
	dflt = NULL;
	k = 0;
	key = 'A';

	str_nz_cpy( ls[k].path, "/save load list", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MENU_SAVE_LOAD_MAX_N; i++ ){
		bool_t	flg_exist_data;
		bool_t	flg_page;

		flg_page = ((i % MENU_SAVE_LOAD_N_PER_PAGE) == 0);

		if( flg_page && (i != 0) ){
			key = 'A';

			str_nz_cpy( ls[k].path,
					"/save load list/page separator",
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

		if( flg_page ){
			set_ttl_menu_save_load( &(ls[k]),
					flg_save, flg_txt );
			k++;
		}

		if( flg_new_game && (i == 0) ){
			str_nz_cpy( ls[k].path,
					"/save load list/new game",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[k].kind, "<Item>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = 'Z';
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_SAVE_LOAD_TTL_NEW_GAME;
			ls[k].msg[0] = '\0';
			ls[k].call_back = cb_menu_new_game;
			ls[k].arg = NULL;
			ls[k].flg = FLG_NULL;
			k++;
		}

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/save load list/%ld", i );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		flg_exist_data = get_save_load_ttl( ls[k].msg, i,
				flg_txt, FALSE );
		ls[k].call_back = cb_menu_save_load;
		if( flg_save || flg_exist_data )
			ls[k].arg = (void *)i;
		else
			ls[k].arg = (void *)-1;
		ls[k].flg = FLG_NULL;
		k++;

		key++;
	}
	ls[k].path[0] = '\0';

	g_sel_save_load_n = SAVE_N_SEL;

	while( 1 ){
		ret = exec_menu( ls, dflt, NULL );

		if( ret == NULL ){
			if( g_sel_save_load_n == SAVE_N_SEL ){
				if( flg_new_game )
					return SAVE_N_SEL;
				if( !flg_save )
					continue;
			} else {
				return g_sel_save_load_n;
			}
		}

		return SAVE_N_SEL;
	}

	return SAVE_N_SEL;
}

/**/

void	set_ttl_menu_save_load(
	menu_t *ls, bool_t flg_save, bool_t flg_txt
)
{
	str_nz_cpy( ls->path, "/save load list/title", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls->kind, "<Title>", MENU_KIND_MAX_LEN );
	ls->accel_key = '\0';
	ls->short_key[0] = '\0';
	ls->n_msg = N_MSG_NULL;
	if( flg_txt ){
		if( flg_save ){
			str_nz_cpy( ls->msg, MSG_MENU_WIZARD_TEXT_SAVE,
					MENU_MSG_MAX_BYTE );
		} else {
			str_nz_cpy( ls->msg, MSG_MENU_WIZARD_TEXT_LOAD,
					MENU_MSG_MAX_BYTE );
		}
	} else {
		if( flg_save ){
			str_nz_cpy( ls->msg, MSG_MENU_BAR_SAVE,
					MENU_MSG_MAX_BYTE );
		} else {
			str_nz_cpy( ls->msg, MSG_MENU_BAR_LOAD,
					MENU_MSG_MAX_BYTE );
		}
	}
	ls->call_back = NULL;
	ls->arg = NULL;
	ls->flg = FLG_NULL;
}

/**/

char	*cb_menu_save_load( menu_t **pp, menu_t **dflt )
{
	if( pp == NULL ){
		g_sel_save_load_n = -1;
		return STR_MENU_ERR;
	}

	g_sel_save_load_n = (long)((*pp)->arg);
	return NULL;
}

/**/

char	*cb_menu_new_game( menu_t **pp, menu_t **dflt )
{
	return NULL;
}

/**/

void	set_flg_no_save( bool_t flg )
{
	g_flg_no_save = flg;
}

/**/

bool_t	get_flg_no_save( void )
{
	return g_flg_no_save;
}

/**/

bool_t	exec_menu_identify_item( mbr_t *mbr )
{
	party_t	*pty = get_party();
	menu_t	*ls;
	menu_t	*dflt;
	char	*ret;
	long	i, j, k;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	if( chk_flg_or( mbr->stat,
			FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		print_msg( FLG_NULL, MSG_ERR_MENU_SEL_ITEM, mbr->name );
		return FALSE;
	}

	ls = ls_menu_identify_item;
	dflt = NULL;
	k = 0;

	str_nz_cpy( ls[k].path, "/identify item",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MBR_MAX_N; i++ ){
		item_t	*item, *p;

		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		str_nz_cpy( ls[k].path, "/identify item/--",
				MENU_PATH_MAX_LEN );
		str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = '\0';
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, pty->mbr[i]->name,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = NULL;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		item = get_mbr_item_asgn( pty->mbr[i] );
		if( item == NULL )
			p = NULL;
		else
			p = item->next;
		j = 0;
		if( (p == NULL) || (p == item) ){
			sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
					"/identify item/no sel %c",
					(char)('A' + i) );
			str_nz_cpy( ls[k].kind, "<Item>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = (char)('A' + j);
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_ITEM_NO_SEL;
			str_nz_cpy( ls[k].msg, MSG_ITEM_NO_SEL,
					MENU_MSG_MAX_BYTE );
			ls[k].call_back = cb_menu_identify_item_no_sel;
			ls[k].arg = (void *)NULL;
			ls[k].flg = FLG_NULL;
			k++;
		}
		for( j = 0; j < MBR_ITEM_MAX_N; j++, p = p->next ){
			if( p == item )
				break;

			if( (pty->mbr[i] == mbr) && (dflt == NULL) )
				dflt = &(ls[k]);

			sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
					"/identify item/%c",
					(char)('A' + j) );
			str_nz_cpy( ls[k].kind, "<Item>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = (char)('A' + j);
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_NULL;
			str_nz_cpy( ls[k].msg, p->name,
					MENU_MSG_MAX_BYTE );
			ls[k].call_back = cb_menu_identify_item;
			ls[k].arg = (void *)p;
			ls[k].flg = FLG_NULL;
			k++;
		}

		str_nz_cpy( ls[k].path, "/identify item/--",
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
	ls[k].path[0] = '\0';

	print_msg( FLG_NULL, MSG_S, MSG_FX_IDENTIFY_ITEM );

	ret = exec_menu( ls, dflt, NULL );
	if( ret == NULL )
		return TRUE;
	if( strcmp( ret, STR_MENU_ERR ) == 0 )
		return FALSE;
	if( strcmp( ret, STR_MENU_CANCEL ) == 0 )
		return FALSE;

	return FALSE;
}

/**/

char	*cb_menu_identify_item( menu_t **pp, menu_t **dflt )
{
	identify_item( (item_t *)((*pp)->arg) );

	return NULL;
}

/**/

char	*cb_menu_identify_item_no_sel( menu_t **pp, menu_t **dflt )
{
	return STR_MENU_CANCEL;
}

/**/

bool_t	exec_menu_resurrection( mbr_t *mbr )
{
	party_t	*pty = get_party();
	pet_t	**pet = get_party_pet();
	menu_t	*ls;
	char	*ret;
	long	dead_mbr_n;
	long	i, k;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	if( chk_flg_or( mbr->stat,
			FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		return FALSE;
	}

	dead_mbr_n = 0;
	ls = ls_menu_resurrection;
	k = 0;

	str_nz_cpy( ls[k].path, "/resurrection",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/resurrection/--",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_TTL_MENU_RESURRECTION,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;
		if( !chk_flg( pty->mbr[i]->stat, FLG_STAT_DEAD ) )
			continue;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/resurrection/%c",
				(char)('A' + i) );
		str_nz_cpy( ls[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + i);
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, pty->mbr[i]->name,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_resurrection;
		ls[k].arg = pty->mbr[i];
		ls[k].flg = FLG_NULL;
		k++;

		dead_mbr_n++;
	}
	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet[i] == NULL )
			continue;
		if( chk_flg( pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;
		if( !chk_flg( pet[i]->stat, FLG_STAT_DEAD ) )
			continue;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/resurrection/%c",
				(char)('A' + i + MBR_MAX_N) );
		str_nz_cpy( ls[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + i + MBR_MAX_N);
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, pet[i]->name, MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_resurrection;
		ls[k].arg = pet[i];
		ls[k].flg = FLG_NULL;
		k++;

		dead_mbr_n++;
	}
	ls[k].path[0] = '\0';

	if( dead_mbr_n <= 0 ){
		print_msg( FLG_NULL, MSG_S,
				MSG_MENU_RESURRECTION_ERR_ALL_MBR );
		return FALSE;
	}

	print_msg( FLG_NULL, MSG_S, MSG_TTL_MENU_RESURRECTION );

	ret = exec_menu( ls, NULL, NULL );
	if( ret == NULL )
		return TRUE;
	if( strcmp( ret, STR_MENU_ERR ) == 0 )
		return FALSE;
	if( strcmp( ret, STR_MENU_CANCEL ) == 0 )
		return FALSE;

	return FALSE;
}

/**/

char	*cb_menu_resurrection( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;

	mbr = (mbr_t *)((*pp)->arg);
	fx_resurrection( mbr, TRUE );

	return NULL;
}

/**/

menu_t	*get_ls_menu_main( void )
{
	return ls_menu_main;
}

/**/

menu_t	*get_ls_menu_sel_obj( void )
{
	return ls_menu_sel_obj;
}

/**/

menu_t	*get_menu_dflt_main( void )
{
	return g_menu_dflt_main;
}

/**/

void	set_menu_dflt_main( menu_t *p )
{
	if( !get_flg_chk_short_key() )
		g_menu_dflt_main = p;
}

/**/

void	update_crsr( void )
{
	draw_main_crsr();
	draw_sub_crsr();

	/* ステータス・バーにヒントを表示 */
	draw_stat_bar();

	reset_crsr();
}

/**/

pos_t	*get_main_crsr( void )
{
	return &g_main_crsr;
}

/**/

pos_t	*get_pre_main_crsr( void )
{
	return &g_pre_main_crsr;
}

/**/

pos_t	*get_sub_crsr( void )
{
	return &g_sub_crsr;
}

/**/

pos_t	*get_pre_sub_crsr( void )
{
	return &g_pre_sub_crsr;
}

/**/

long	get_sel_mbr_n( void )
{
	return g_sel_mbr_n;
}

/**/

void	set_sel_mbr_n( long n )
{
	g_sel_mbr_n = n;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_mmenu_c( void )
{
	check_memory( check_memory_mmenu_c_g_main_crsr,
			"mmenu.c: g_main_crsr" );
	check_memory( check_memory_mmenu_c_g_menu_dflt_main,
			"mmenu.c: g_menu_dflt_main" );
	check_memory( check_memory_mmenu_c_g_sub_sel_mbr,
			"mmenu.c: g_sub_sel_mbr" );
	check_memory( check_memory_mmenu_c_g_flg_no_save,
			"mmenu.c: g_flg_no_save" );
	check_memory( check_memory_mmenu_c_g_sel_obj_trgt_kind,
			"mmenu.c: g_sel_obj_trgt_kind" );
	check_memory( check_memory_mmenu_c_g_sel_mbr_n,
			"mmenu.c: g_sel_mbr_n" );
	check_memory( check_memory_mmenu_c_g_mark_sel_mbr,
			"mmenu.c: g_mark_sel_mbr" );
	check_memory( check_memory_mmenu_c_ls_equip_msg,
			"mmenu.c: ls_equip_msg" );
	check_memory( check_memory_mmenu_c_pre_sel_mbr_n,
			"mmenu.c: pre_sel_mbr_n" );
}

/**/
