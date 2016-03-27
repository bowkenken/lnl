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
* $Id: imenu.c,v 1.146 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#define	IMENU_C
#include	"inc.h"

/**/

/* 階層移動などでメニューをリセットするか? */
#define	FLG_RESET_MENU	0
#define	FLG_CONTINUE_EXEC_KEY_IDLE	0
#define	FLG_WIZARD_MENU_HIDDEN	0

#define	MENU_LANG_LS_N_PER_PAGE	10

#define	SCROLL_WIDTH	((get_map_col() / 2) / 2)
#define	SCROLL_HEIGHT	(get_map_row() / 2)

#define	DOUBLE_CLICK_DEFAULT_MSEC	300

/**/

static menu_t	*g_menu_dflt_misc;
static menu_t	*g_menu_dflt_cnf;
static menu_t	*g_menu_dflt_system;
static menu_t	*g_menu_dflt_wizard;
check_memory_def( check_memory_imenu_c_g_menu_dflt_misc )

static mbr_t	*g_sel_mbr;
check_memory_def( check_memory_imenu_c_g_sel_mbr )

static bool_t	g_flg_continue_exec_mode;
check_memory_def( check_memory_imenu_c_g_flg_continue_exec_mode )
static bool_t	g_ls_flg_srch[LS_MBR_MAX_N];
check_memory_def( check_memory_imenu_c_g_ls_flg_srch )

static menu_t	ls_menu_ind_square[1 + 1 + (1 + MBR_MAX_N + 1) + 1];
check_memory_def( check_memory_imenu_c_ls_menu_ind_square )
static menu_t	*g_menu_dflt_ind_square;
check_memory_def( check_memory_imenu_c_g_menu_dflt_ind_square )

static flg_scroll_t	g_flg_scroll;
static next_pos_t	g_next_pos;
static curs_attr_t	*g_sel_attr;
check_memory_def( check_memory_imenu_c_g_flg_scroll )

static long	g_cui_mouse_double_click_msec;
check_memory_def( check_memory_imenu_c_g_cui_mouse_double_click_msec )

static rate_t	g_music_volume_rate;
static rate_t	g_sound_volume_rate;
static bool_t	g_flg_mute_audio;
check_memory_def( check_memory_imenu_c_g_music_volume_rate )

#define	JOYSTICK_SEL_N_MAX_N	10
static menu_t	ls_menu_joystick_sel_n[JOYSTICK_SEL_N_MAX_N * 2];
check_memory_def( check_memory_imenu_c_ls_menu_joystick_sel_n )

#define	USER_MENU_MAX_N_PER_PAGE	(MENU_MAX_N_PER_PAGE - 3)
static long	g_user_menu_n;
check_memory_def( check_memory_imenu_c_g_user_menu_n )
static char	g_user_menu_name[USER_MENU_MAX_N][MENU_MSG_MAX_BYTE + 1];
check_memory_def( check_memory_imenu_c_g_user_menu_cmd )

static long	g_replay_sel_load_n;
check_memory_def( check_memory_imenu_c_g_user_menu_name )
static char	g_user_menu_cmd[USER_MENU_MAX_N][MACRO_MAX_LEN + 1];
check_memory_def( check_memory_imenu_c_g_replay_sel_load_n )
static menu_t	ls_menu_replay_sel_load[MENU_SAVE_LOAD_MAX_N * 2];
check_memory_def( check_memory_imenu_c_ls_menu_replay_sel_load )

static long	*g_page_n;
static data_n_t	*g_data_n;
static mbr_data_edit_kind_t	g_mbr_data_edit_kind;
check_memory_def( check_memory_imenu_c_g_page_n )

/* キャラクタ・シートのページをカーソル・キーでめくるか? */
/* TRUE の場合、カーソル・キーでページ、メニューでメンバーをめくる */
/* FALSE の場合、カーソル・キーでメンバー、メニューでページをめくる */
static bool_t	g_flg_mbr_data_change_page_is_crsr;
check_memory_def( check_memory_imenu_c_g_flg_mbr_data_change_page_is_crsr )

/**/

#include	"imenu-tab.h"

/**/

static long	static_cb_menu_wizard_recall__n;
static long	static_cb_menu_wizard_add_turn__hour;
static long	static_cb_menu_wizard_add_turn__minute;
static long	static_cb_menu_wizard_add_turn__turn;
static long	static_cb_menu_wizard_up_exp__exp;
check_memory_def( check_memory_imenu_c_n )

/**/

void	init_var_misc_menu( void )
{
	g_flg_mbr_data_change_page_is_crsr = TRUE;

	g_cui_mouse_double_click_msec = DOUBLE_CLICK_DEFAULT_MSEC;

	g_music_volume_rate = _100_PERCENT;
	g_sound_volume_rate = _100_PERCENT;
	g_flg_mute_audio = FALSE;

	clr_user_menu();
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_misc_menu( void )
{
	pos_t	*crsr = get_main_crsr();
	party_t *pty = get_party();
	long	i;

#if	FLG_RESET_MENU
	g_menu_dflt_misc = NULL;
	g_menu_dflt_cnf = NULL;
	g_menu_dflt_system = NULL;
	g_menu_dflt_wizard = NULL;
	g_menu_dflt_ind_square = NULL;
#endif

	for( i = 0; i < LS_MBR_MAX_N; i++ )
		g_ls_flg_srch[i] = TRUE;

	g_next_pos.kind = NEXT_POS_KIND_SQUARE;
	g_next_pos.p = &(pty->square);
	g_next_pos.n = 0;
	g_next_pos.x = 0;
	g_next_pos.y = 0;
	crsr->x = 0;
	crsr->y = 0;
	g_flg_mbr_data_change_page_is_crsr = TRUE;

	/**/

	static_cb_menu_wizard_recall__n = 0;
	static_cb_menu_wizard_add_turn__hour = 0;
	static_cb_menu_wizard_add_turn__minute = 0;
	static_cb_menu_wizard_add_turn__turn = 0;
	static_cb_menu_wizard_up_exp__exp = +(100 * 100 * 100);
}

/**/

void	init_misc_menu( void )
{
	long	i;

	g_menu_dflt_misc = NULL;
	g_menu_dflt_cnf = NULL;
	g_menu_dflt_system = NULL;
	g_menu_dflt_wizard = NULL;
	g_menu_dflt_ind_square = NULL;

	g_flg_continue_exec_mode = FALSE;

	for( i = 0; i < LS_MBR_MAX_N; i++ )
		g_ls_flg_srch[i] = TRUE;

	g_data_n = NULL;
	g_mbr_data_edit_kind = MBR_DATA_EDIT_KIND_SHOW;
}

/**/

char	*cb_menu_misc( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_main( *pp );
	*dflt = g_menu_dflt_misc;

	return NULL;
}

/**/

char	*cb_menu_info( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );

	return NULL;
}

/**/

char	*cb_menu_continue_exec( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );
	toggle_continue_exec_mode();

	return NULL;
}

/**/

bool_t	chk_continue_exec_mode( long *c, bool_t *p_flg_clr_key_buf )
{
#if	FLG_CONTINUE_EXEC_KEY_IDLE
	static bool_t	flg_pre_null = TRUE;

	if( !get_continue_exec_mode() )
		return FALSE;

	if( flg_pre_null )
		*c = '.';
	else
		*c = CMD_KEY_IDLE;
	flg_pre_null = !flg_pre_null;

	*p_flg_clr_key_buf = TRUE;

	call_sleep( 1000 * 3 / 60 / 2 );

	return TRUE;
#else
	if( !get_continue_exec_mode() )
		return FALSE;

	*c = '.';
	*p_flg_clr_key_buf = TRUE;

	call_sleep( 1000 * 3 / 60 / 1 );

	return TRUE;
#endif
}

/**/

bool_t	get_continue_exec_mode( void )
{
	return g_flg_continue_exec_mode;
}

/**/

bool_t	toggle_continue_exec_mode( void )
{
	g_flg_continue_exec_mode = !g_flg_continue_exec_mode;

	call_gui_map_cont_exec_set(
			g_flg_continue_exec_mode );

	return g_flg_continue_exec_mode;
}

/**/

bool_t	clr_continue_exec_mode( void )
{
	g_flg_continue_exec_mode = FALSE;

	call_gui_map_cont_exec_set(
			g_flg_continue_exec_mode );

	return g_flg_continue_exec_mode;
}

/**/

char	*cb_menu_stairs( menu_t **pp, menu_t **dflt )
{
	bool_t	flg_up, flg_down, flg_last_boss;

	set_menu_dflt_misc( *pp );

	clr_flg_menu( *pp, NULL, FLG_MENU_ALL );

	flg_up = TRUE;
	flg_down = TRUE;
	flg_last_boss = TRUE;
	if( !chk_stairs( FACE_MJR_STAIRS_UP ) ){
		flg_up = FALSE;
		set_flg_menu( *pp, "up", FLG_MENU_HIDDEN );
	}
	if( !chk_stairs( FACE_MJR_STAIRS_DOWN ) ){
		flg_down = FALSE;
		set_flg_menu( *pp, "down", FLG_MENU_HIDDEN );
	}
	if( !chk_stairs( FACE_MNR_STAIRS_LAST_BOSS ) ){
		flg_last_boss = FALSE;
		set_flg_menu( *pp, "last boss", FLG_MENU_HIDDEN );
	}
	if( !flg_up && !flg_down && !flg_last_boss ){
		print_msg( FLG_NULL, MSG_ERR_STAIRS );
		return STR_MENU_CANCEL;
	}

	*dflt = srch_menu( *pp, "down" );

	return NULL;
}

/**/

char	*cb_menu_stairs_up( menu_t **pp, menu_t **dflt )
{
	up_stairs();

	return NULL;
}

/**/

char	*cb_menu_stairs_down( menu_t **pp, menu_t **dflt )
{
	down_stairs();

	return NULL;
}

/**/

char	*cb_menu_stairs_last_boss( menu_t **pp, menu_t **dflt )
{
	ask_t	ask;

	if( !chk_enter_last_stage() ){
		print_msg( FLG_NULL, MSG_ERR_STAIRS_DOWN_LAST_BOSS_1 );
		print_msg( FLG_NULL, MSG_ERR_STAIRS_DOWN_LAST_BOSS_2 );
		return NULL;
	}

	curs_attrset_chr( get_mbr_randm( MAP_DEL_X, MAP_DEL_Y ),
			-1, FALSE );
	print_msg( FLG_NULL, MSG_FEEL_LAST_BOSS );
	curs_attrset_dflt();

	draw_words( NULL, MSG_FEEL_LAST_BOSS );

	ask = exec_menu_ask( MSG_TTL_MENU_ASK_DOWN_STAIRS_LAST_BOSS,
			ASK_NO, TRUE );

	if( ask != ASK_YES )
		return NULL;

	down_stairs_last_boss();

	return NULL;
}

/**/

char	*cb_menu_srch( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	menu_t	*ls;
	long	i, k;

	set_menu_dflt_misc( *pp );

	ls = ls_menu_srch;
	k = 0;

	str_nz_cpy( ls[k].path, "/search", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = cb_menu_srch_init;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/search/title", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_TTL_MENU_SRCH, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/search/exec", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'X';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_SRCH_EXEC, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_srch_exec;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/search/exec all", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'Y';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_SRCH_EXEC_ALL, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_srch_exec_all;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/search/cancel all", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'Z';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_SRCH_CANCEL_ALL, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_srch_cancel_all;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MBR_MAX_N; i++ ){
		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/search/%ld", i );
		str_nz_cpy( ls[k].kind, "<CheckItem>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + i);
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, pty->mbr[i]->name, MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_srch_sel_mbr;
		ls[k].arg = (void *)i;
		ls[k].flg = FLG_NULL;
		k++;
	}

	str_nz_cpy( ls[k].path, "/search/auto off", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<CheckItem>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'V';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_SRCH_AUTO_OFF, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_srch_auto_off;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_srch_init( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	static char	sub_path[MENU_PATH_MAX_LEN + 1];
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		sn_printf( sub_path, MENU_PATH_MAX_LEN,
				"%ld", i );

		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) ){
			set_flg_menu( *pp, sub_path, FLG_MENU_HIDDEN );
			continue;
		} else {
			clr_flg_menu( *pp, sub_path, FLG_MENU_HIDDEN );
		}

		if( g_ls_flg_srch[pty->mbr[i]->ls_mbr_n] )
			set_chk_on_menu( *pp, sub_path );
		else
			set_chk_off_menu( *pp, sub_path );
	}

	if( chk_flg( pty->flg, FLG_PARTY_SRCH_AUTO_OFF ) )
		set_chk_on_menu( *pp, "auto off" );
	else
		set_chk_off_menu( *pp, "auto off" );

	return NULL;
}

/**/

char	*cb_menu_srch_exec( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( g_ls_flg_srch[pty->mbr[i]->ls_mbr_n] )
			chr_srch_begin( pty->mbr[i] );
		else
			chr_srch_end( pty->mbr[i] );
	}

	return NULL;
}

/**/

char	*cb_menu_srch_exec_all( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		chr_srch_begin( pty->mbr[i] );

	return NULL;
}

/**/

char	*cb_menu_srch_cancel_all( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		chr_srch_end( pty->mbr[i] );

	return NULL;
}

/**/

char	*cb_menu_srch_sel_mbr( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	mbr_n, ls_mbr_n;

	mbr_n = (long)((*pp)->arg);
	ls_mbr_n = pty->mbr[mbr_n]->ls_mbr_n;

	g_ls_flg_srch[ls_mbr_n] = !g_ls_flg_srch[ls_mbr_n];

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_srch_auto_off( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();

	pty->flg ^= FLG_PARTY_SRCH_AUTO_OFF;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_show_map_hint( menu_t **pp, menu_t **dflt )
{
	pos_t	*crsr = get_main_crsr();

	set_menu_dflt_misc( *pp );
	show_map_hint( crsr->x, crsr->y );

	return NULL;
}

/**/

void	show_map_hint( long x, long y )
{
	show_map_hint_chr( x, y );
	show_map_hint_obj( x, y );
}

/**/

void	show_map_hint_chr( long x, long y )
{
	const char	*s;

	s = get_str_map_hint_chr( x, y );
	if( (s != NULL) && (s[0] != '\0') )
		print_msg( FLG_NULL, s );
}

/**/

void	show_map_hint_obj( long x, long y )
{
	const char	*s;

	s = get_str_map_hint_obj( x, y );
	if( (s != NULL) && (s[0] != '\0') )
		print_msg( FLG_NULL, s );
}

/**/

const char	*get_str_map_hint_chr( long x, long y )
{
	static char	buf[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;
	dun_t	*dun;
	char	mjr, mnr;
	flg_map_t	flg;
	char	*msg1, *msg2;
	mbr_t	*mbr;
	mnstr_t	*mnstr;

	if( !clip_pos( x, y ) )
		return "";

	dun = get_dun();
	mjr = dun->map.chr.mjr[y][x];
	mnr = dun->map.chr.mnr[y][x];
	flg = dun->map.chr.flg[y][x];

	if( !chk_flg( flg, FLG_MAP_CHR_FIND ) )
		return "";
	if( chk_flg( flg, FLG_MAP_CHR_INVISIBLE ) )
		return "";

	mbr = get_mbr( x, y );
	mnstr = get_mnstr( x, y );

	msg1 = MSG_NULL;
	msg2 = NULL;

	if( mbr != NULL ){
		msg1 = MSG_MAP_HINT_MBR;
		msg2 = mbr->name;
	} else if( mnstr != NULL ){
		if( is_pet( mnstr ) )
			msg1 = MSG_MAP_HINT_PET;
		else if( chk_flg( mnstr->flg_map, FLG_MAP_CHR_NPC ) )
			msg1 = MSG_MAP_HINT_NPC;
		else
			msg1 = MSG_MAP_HINT_MNSTR;
		msg2 = mnstr->name;
	}

	if( msg2 == NULL ){
		sn_printf( buf, max_len, MSG_MAP_HINT_FMT_CHR,
				x, y, mjr, mnr, msg1 );
	} else {
		sn_printf( buf, max_len, MSG_MAP_HINT_FMT_CHR_SUB,
				x, y, mjr, mnr, msg1, msg2 );
	}

	return buf;
}

/**/

const char	*get_str_map_hint_obj( long x, long y )
{
	static char	buf[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;
	dun_t	*dun;
	char	mjr, mnr;
	flg_map_t	flg;
	char	*msg1, *msg2;
	item_t	*item;
	trap_t	*trap;
	door_t	*door;

	if( !clip_pos( x, y ) )
		return "";

	dun = get_dun();
	mjr = dun->map.obj.mjr[y][x];
	mnr = dun->map.obj.mnr[y][x];
	flg = dun->map.obj.flg[y][x];

	if( !chk_flg( flg, FLG_MAP_OBJ_FIND ) )
		return "";

	item = get_item( x, y );
	trap = get_trap( x, y );
	door = get_door( x, y );

	msg1 = MSG_NULL;
	msg2 = NULL;

	if( chk_flg( flg, FLG_MAP_OBJ_LOOK_FLOOR ) ){
		msg1 = MSG_MAP_HINT_FLOOR;
		mjr = FACE_MJR_FLOOR;
		mnr = FACE_MNR_FLOOR;
	} else if( chk_flg( flg, FLG_MAP_OBJ_LOOK_WALL ) ){
		msg1 = MSG_MAP_HINT_WALL;
		mjr = FACE_MJR_WALL;
		mnr = FACE_MNR_WALL;
	} else if( mjr == FACE_MJR_FLOOR ){
		if( mnr == FACE_MNR_HOLE )
			msg1 = MSG_MAP_HINT_HOLE;
		else
			msg1 = MSG_MAP_HINT_FLOOR;
	} else if( mjr == FACE_MJR_WALL ){
		msg1 = MSG_MAP_HINT_WALL;
		if( mnr == FACE_MNR_STATUE )
			msg2 = MSG_MAP_HINT_STATUE;
		else if( mnr == FACE_MNR_STREETLAMP )
			msg2 = MSG_MAP_HINT_STREETLAMP;
		else
			msg2 = NULL;
	} else if( mjr == FACE_MJR_WATER ){
		msg1 = MSG_MAP_HINT_WATER;
		if( mnr == FACE_MNR_PUDDLE )
			msg2 = MSG_MAP_HINT_PUDDLE;
		else if( mnr == FACE_MNR_SHALLOWS )
			msg2 = MSG_MAP_HINT_SHALLOWS;
		else if( mnr == FACE_MNR_OFFING )
			msg2 = MSG_MAP_HINT_OFFING;
		else if( mnr == FACE_MNR_LAVA )
			msg2 = MSG_MAP_HINT_LAVA;
		else
			msg2 = NULL;
	} else if( item != NULL ){
		msg1 = MSG_MAP_HINT_ITEM,
		msg2 = get_item_mnr_name( item->mjr, item->mnr );
	} else if( trap != NULL ){
		msg1 = MSG_MAP_HINT_TRAP;
		if( trap->flg_chked )
			if( trap->tab != NULL )
				msg2 = trap->tab->name;
	} else if( door != NULL ){
		if( chk_flg( door->flg, FLG_DOOR_SHOP ) ){
			msg1 = MSG_MAP_HINT_SHOP;
			msg2 = get_shop_name( get_shop_n( door->mnr ) );
		} else if( mnr == FACE_MNR_GATE ){
			msg1 = MSG_MAP_HINT_GATE;
		} else if( mnr == FACE_MNR_WINDOW ){
			msg1 = MSG_MAP_HINT_WINDOW;
		} else {
			msg1 = MSG_MAP_HINT_DOOR;
		}
	} else if( mjr == FACE_MJR_STAIRS_UP ){
		msg1 = MSG_MAP_HINT_STAIRS_UP;
	} else if( mjr == FACE_MJR_STAIRS_DOWN ){
		if( mnr == FACE_MNR_STAIRS_LAST_BOSS ){
			msg1 = MSG_MAP_HINT_STAIRS_LAST_BOSS;
		} else {
			msg1 = MSG_MAP_HINT_STAIRS_DOWN;
		}
	}

	if( msg2 == NULL ){
		sn_printf( buf, max_len, MSG_MAP_HINT_FMT_OBJ,
				x, y, mjr, mnr, msg1 );
	} else {
		sn_printf( buf, max_len, MSG_MAP_HINT_FMT_OBJ_SUB,
				x, y, mjr, mnr, msg1, msg2 );
	}

	return buf;
}

/**/

char	*cb_menu_chr_data( menu_t **pp, menu_t **dflt )
{
	pos_t	*crsr = get_main_crsr();
	mbr_t	*mbr;
	pet_t	*pet;
	mnstr_t	*mnstr;

	set_menu_dflt_misc( *pp );

	mbr = get_mbr( crsr->x, crsr->y );
	pet = get_pet( crsr->x, crsr->y );
	mnstr = get_mnstr( crsr->x, crsr->y );

	if( mbr != NULL )
		return menu_sel_mbr_data( mbr->mbr_n );
	else if( pet != NULL )
		return menu_sel_pet_data( get_pet_n( pet ) );
	else if( mnstr != NULL )
		return menu_sel_mnstr_data( mnstr );

	return STR_MENU_CANCEL;
}

/**/

char	*menu_sel_mbr_data( long sel_mbr_n )
{
	mbr_t	**mbr = get_party()->mbr;
	pet_t	**pet = get_party_pet();
	chr_t	*chr;
	long	n;
	long	page_n;
	data_n_t	data_n;

	if( sel_mbr_n <= -1 )
		return STR_MENU_ERR;

	n = sel_mbr_n;
	page_n = 0;
	data_n = DATA_N_NEXT_PAGE;

	while( 1 ){
		long	add;

		if( n < MBR_MAX_N )
			chr = mbr[n];
		else
			chr = pet[n - MBR_MAX_N];

		add = menu_show_mbr_data( chr, &page_n, &data_n );
		if( add == 0 )
			break;

		n = next_mbr( n, add );
	}

	return STR_MENU_CANCEL;
}

/**/

char	*menu_sel_pet_data( long sel_pet_n )
{
	return menu_sel_mbr_data( sel_pet_n + MBR_MAX_N );
}

/**/

long	menu_show_mbr_data( mbr_t *mbr, long *page_n, data_n_t *data_n )
{
	return menu_mbr_data( mbr, page_n, data_n,
			MBR_DATA_EDIT_KIND_SHOW );
}

/**/

long	menu_edit_mbr_data( mbr_t *mbr, long *page_n, data_n_t *data_n )
{
	return menu_mbr_data( mbr, page_n, data_n,
			MBR_DATA_EDIT_KIND_EDIT );
}

/**/

long	menu_mbr_data(
	mbr_t *org_p, long *page_n, data_n_t *data_n,
	mbr_data_edit_kind_t edit_kind
)
{
	long	res;

	res = menu_mbr_data_sub( org_p, page_n, data_n, edit_kind );
	call_gui_chr_sheet_wipe();
	return res;
}

/**/

long	menu_mbr_data_sub(
	mbr_t *org_p, long *page_n, data_n_t *data_n,
	mbr_data_edit_kind_t edit_kind
)
{
	mbr_t	dst_mbr, *mbr_p;
	data_n_t	prev_n;
	long	mbr_dn, page_dn;

	if( org_p == NULL )
		return 0;

	mbr_p = &dst_mbr;
	*mbr_p = *org_p;

	*data_n = next_mbr_data( *page_n, *data_n, +-0, edit_kind );
	prev_n = *data_n;

	g_page_n = page_n;
	g_data_n = data_n;
	g_mbr_data_edit_kind = edit_kind;

	draw_mbr_data_all( org_p, mbr_p, *page_n, edit_kind );

	while( 1 ){
		bool_t	flg_sel, flg_cancel;

		draw_mbr_data( org_p, mbr_p, prev_n, FALSE,
				edit_kind, FALSE );
		draw_mbr_data( org_p, mbr_p, *data_n, TRUE,
				edit_kind, FALSE );
		prev_n = *data_n;
		mbr_dn = 0;
		page_dn = 0;

		flg_sel = FALSE;
		flg_cancel = FALSE;

		switch( get_key( g_flg_clr_key_buf_menu ) ){
		case CASE_CANCEL:
		case CASE_EXEC:
			flg_cancel = TRUE;
			break;
		case ' ':
			if( get_flg_space_select() )
				flg_sel = TRUE;
			break;
		case CASE_ENTER:
			if( get_flg_space_select() )
				flg_cancel = TRUE;
			else
				flg_sel = TRUE;
			break;
		case '/':
		case 'z':
			page_dn -= 1;
			break;
		case '*':
		case 'x':
			page_dn += 1;
			break;
		case '-':
		case 'c':
			mbr_dn -= 1;
			break;
		case '+':
		case 'v':
			mbr_dn += 1;
			break;
		case CASE_CRSR_LEFT:
			if( g_flg_mbr_data_change_page_is_crsr )
				page_dn -= 1;
			else
				mbr_dn -= 1;
			break;
		case CASE_CRSR_RIGHT:
			if( g_flg_mbr_data_change_page_is_crsr )
				page_dn += 1;
			else
				mbr_dn += 1;
			break;
		case CASE_CRSR_DOWN:
			*data_n = next_mbr_data( *page_n, *data_n,
					+1, edit_kind );
			break;
		case CASE_CRSR_UP:
			*data_n = next_mbr_data( *page_n, *data_n,
					-1, edit_kind );
			break;
		case 'g':
			exec_back_log();
			break;
		default:
			break;
		}

		if( flg_sel ){
			draw_mbr_data( org_p, mbr_p, *data_n, FALSE,
					edit_kind, FALSE );
			exec_menu_edit_mbr_data(
					mbr_p, *data_n,
					&mbr_dn, &page_dn );

			if( g_flg_gui )
				call_gui_menu_wipe();
			if( edit_kind == MBR_DATA_EDIT_KIND_NEW ){
				if( *data_n != DATA_N_GRAPH_FILE )
					new_mbr_reset( mbr_p );
				*org_p = *mbr_p;
			}
			redraw_mbr_data( org_p, mbr_p, *page_n, edit_kind );
		}
		if( mbr_dn != 0 ){
			if( exec_menu_ask_edit_mbr_data( org_p, mbr_p ) )
				return mbr_dn;

			redraw_mbr_data( org_p, mbr_p, *page_n, edit_kind );
		}
		if( page_dn != 0 ){
			*page_n += page_dn;
			*page_n += MBR_DATA_PAGE_MAX_N;
			*page_n %= MBR_DATA_PAGE_MAX_N;
			*data_n = next_mbr_data( *page_n, *data_n,
					+-0, edit_kind );
			prev_n = *data_n;
			if( edit_kind == MBR_DATA_EDIT_KIND_NEW ){
				new_mbr_reset( mbr_p );
				*org_p = *mbr_p;
			}

			redraw_mbr_data( org_p, mbr_p, *page_n, edit_kind );
		}
		if( flg_cancel ){
			if( exec_menu_ask_edit_mbr_data( org_p, mbr_p ) )
				return 0;

			redraw_mbr_data( org_p, mbr_p, *page_n, edit_kind );
		}
	}

	return 0;
}

/**/

void	set_data_n( data_n_t data_n )
{
	if( g_data_n == NULL )
		return;

	*g_data_n = data_n;
}

/**/

long	get_mbr_data_page_n( void )
{
	if( g_page_n == NULL )
		return 0;

	return *g_page_n;
}

/**/

void	set_mbr_data_page_n( long n )
{
	if( g_page_n == NULL )
		return;

	*g_page_n = n;
}

/**/

mbr_data_edit_kind_t	get_mbr_data_edit_kind( void )
{
	return g_mbr_data_edit_kind;
}

/**/

void	exec_menu_edit_mbr_data(
	mbr_t *mbr, data_n_t n, long *mbr_dn, long *page_dn
)
{
	item_t	*item_head, *item;
	equip_kind_t	eq_k;
	long	item_n;
	long	i;

	switch( n ){
	case DATA_N_NAME:
		print_msg( FLG_MSG_NO_MORE_NEXT, MSG_GETS_MBR_NAME,
				(long)MBR_NAME_MAX_LEN );
		gets_mbr_name( mbr );
		break;
	case DATA_N_FACE:
		print_msg( FLG_MSG_NO_MORE_NEXT, MSG_GETS_MBR_FACE );
		gets_mbr_face( mbr );
		break;
	case DATA_N_RACE_STR:
		exec_menu_race( &(mbr->race) );
		break;
	case DATA_N_RACE_NAME:
		print_msg( FLG_MSG_NO_MORE_NEXT, MSG_GETS_RACE_NAME,
				(long)RACE_NAME_MAX_LEN );
		gets_race_name( mbr );
		break;
	case DATA_N_SEX:
		exec_menu_sex( &(mbr->sex.cur) );
		break;
	case DATA_N_GRAPH_FILE:
		sel_mbr_graph_file( mbr );
		break;
	case DATA_N_CLASS:
		exec_menu_class( &(mbr->class_n) );
		break;

	case DATA_N_ITEM_00:
	case DATA_N_ITEM_01:
	case DATA_N_ITEM_02:
	case DATA_N_ITEM_03:
	case DATA_N_ITEM_04:
	case DATA_N_ITEM_05:
	case DATA_N_ITEM_06:
	case DATA_N_ITEM_07:
	case DATA_N_ITEM_08:
	case DATA_N_ITEM_09:
	case DATA_N_ITEM_10:
	case DATA_N_ITEM_11:
	case DATA_N_ITEM_12:
	case DATA_N_ITEM_13:
	case DATA_N_ITEM_14:
	case DATA_N_ITEM_15:
		item_n = n - DATA_N_ITEM_00;

		item_head = get_mbr_item_asgn( mbr );
		if( item_head == NULL )
			break;

		item = item_head->next;
		for( i = 0; i < item_n; i++, item = item->next )
			if( item == item_head )
				break;

		if( (i == item_n) && (item != item_head) )
			chk_item_data( item );
		break;

	case DATA_N_EQUIP_WIELDING:
	case DATA_N_EQUIP_SHIELD:
	case DATA_N_EQUIP_BOW:
	case DATA_N_EQUIP_ARW:
	case DATA_N_EQUIP_HEAD:
	case DATA_N_EQUIP_NECK:
	case DATA_N_EQUIP_BODY:
	case DATA_N_EQUIP_ABOUT_BODY:
	case DATA_N_EQUIP_ARM:
	case DATA_N_EQUIP_RIGHT_HAND:
	case DATA_N_EQUIP_LEFT_HAND:
	case DATA_N_EQUIP_FEET:
	case DATA_N_EQUIP_LIGHT_SOURCE:
		item = get_mbr_item_asgn_equip( mbr );
		if( item == NULL )
			break;

		eq_k = (equip_kind_t)(EQUIP_KIND_NULL
				+ (n - DATA_N_EQUIP_WIELDING));

		if( item[eq_k].kind != ITEM_KIND_NULL )
			chk_item_data( &(item[eq_k]) );
		break;

	case DATA_N_SWAP_PAGE_MBR:
		g_flg_mbr_data_change_page_is_crsr
				= !g_flg_mbr_data_change_page_is_crsr;
		break;
	case DATA_N_PREV_PAGE:
		if( g_flg_mbr_data_change_page_is_crsr )
			*mbr_dn -= 1;
		else
			*page_dn -= 1;
		break;
	case DATA_N_NEXT_PAGE:
		if( g_flg_mbr_data_change_page_is_crsr )
			*mbr_dn += 1;
		else
			*page_dn += 1;
		break;
	default:
		break;
	}
}

/**/

bool_t	exec_menu_ask_edit_mbr_data( mbr_t *org_p, mbr_t *mbr_p )
{
	ask_t	ask;

	if( cmp_chr( org_p, mbr_p ) )
		return TRUE;

	ask = exec_menu_ask( MSG_TTL_MENU_ASK_EDIT_MBR, ASK_NO, TRUE );

	if( ask == ASK_YES ){
		*org_p = *mbr_p;
		return TRUE;
	} else if( ask == ASK_NO ){
		*mbr_p = *org_p;
		return TRUE;
	}

	return FALSE;	/* Cancel */
}

/**/

void	sel_mbr_graph_file( mbr_t *mbr )
{
	if( !g_flg_gui ){
		print_msg( FLG_MSG_WRN, MSG_ERR_CHK_GUI );
		return;
	}

	if( call_sel_mbr_graph_begin( mbr ) )
		get_key_wait_cancel_or_exec( TRUE );

	call_sel_mbr_graph_end();
}

/**/

char	*menu_sel_mnstr_data( mnstr_t *mnstr )
{
	long	min_lev, max_lev;
	long	ave_lev;
	long	ave_n;
	long	i;

	if( mnstr == NULL )
		return STR_MENU_ERR;
	if( chk_flg( mnstr->flg_map, FLG_MAP_CHR_INVISIBLE ) )
		return STR_MENU_CANCEL;

	min_lev = ABL_MAX_LEV;
	max_lev = 0;
	ave_lev = 0;
	ave_n = 0;
	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		long	lev;

		lev = get_lev( mnstr, (abl_kind_t)i );
		if( lev > 0 ){
			min_lev = min_l( min_lev, lev );
			max_lev = max_l( max_lev, lev );
			ave_lev += lev;
			ave_n++;
		}
	}
	if( ave_n > 0 )
		ave_lev /= ave_n;

	print_msg( FLG_NULL, MSG_MNSTR_DATA_NAME,
			mnstr->face.mjr, mnstr->face.mnr,
			mnstr->name );
	print_msg( FLG_NULL, MSG_MNSTR_DATA_MJR_NAME,
			mnstr->face.mjr,
			get_mnstr_mjr_name( mnstr->face.mjr ) );
	print_msg( FLG_NULL, MSG_MNSTR_DATA_MAX_LEV,
			mnstr->name, max_lev );
	print_msg( FLG_NULL, MSG_MNSTR_DATA_MIN_LEV,
			mnstr->name, min_lev );
	print_msg( FLG_NULL, MSG_MNSTR_DATA_AVE_LEV,
			mnstr->name, ave_lev );
	print_msg( FLG_NULL, MSG_NULL );

	if( mnstr->attitude == ATTITUDE_MATE ){
		print_msg( FLG_NULL, MSG_MNSTR_DATA_HP,
				mnstr->name,
				mnstr->abl.hp.n, mnstr->abl.hp.max );
		print_msg( FLG_NULL, MSG_MNSTR_DATA_MP,
				mnstr->name,
				mnstr->abl.mp.n, mnstr->abl.mp.max );
		print_msg( FLG_NULL, MSG_NULL );
	}

	if( chk_flg( mnstr->stat, FLG_STAT_DRUNK ) ){
		print_msg( FLG_NULL, MSG_MNSTR_DATA_DRUNK, mnstr->name );
	}

	return NULL;
}

/**/

char	*cb_menu_switch_stat_mode( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );

	switch_stat_mode( +1 );
	redraw_all();

	return NULL;
}

/**/

char	*cb_menu_gold( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );

	clr_flg_menu( *pp, NULL, FLG_MENU_ALL );

	if( get_chr_mjr_crsr() != FACE_MJR_MBR ){
		set_flg_menu( *pp, "collect", FLG_MENU_HIDDEN );
		set_flg_menu( *pp, "give", FLG_MENU_HIDDEN );
	}

	return NULL;
}

/**/

char	*cb_menu_collect_gold( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	sel_mbr_n = get_sel_mbr_n();
	mbr_t	*mbr;

	set_menu_dflt_misc( *pp );

	if( sel_mbr_n <= -1 )
		return STR_MENU_ERR;

	mbr = pty->mbr[sel_mbr_n];

	collect_gold( mbr );

	return NULL;
}

/**/

char	*cb_menu_divide_gold( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );
	divide_gold();

	return NULL;
}

/**/

char	*cb_menu_give_gold( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	sel_mbr_n = get_sel_mbr_n();
	mbr_t	*mbr;

	set_menu_dflt_misc( *pp );

	if( sel_mbr_n <= -1 )
		return STR_MENU_ERR;

	mbr = pty->mbr[sel_mbr_n];

	return menu_mbr_give_gold( mbr );
}

/**/

char	*menu_mbr_give_gold( mbr_t *mbr_from )
{
	mbr_t	*mbr_to;
	gold_t	n, max;
	char	*str;

	if( mbr_from == NULL )
		return STR_MENU_ERR;

	while( 1 ){
		/* 受け取り側 */

		str = exec_menu_sel_mbr( &mbr_to,
				MSG_TTL_MENU_GIVE_GOLD,
				TRUE, TRUE );
		if( str != NULL )
			return str;

		while( 1 ){
			/* 枚数を選ぶ */

			n = 0;
			max = get_chr_gold( mbr_from );
			str = exec_menu_sel_num( &n, 0, max );

			if( str == NULL ){
				/* 渡す */
				give_gold( mbr_from, mbr_to, n );
			} else if( strcmp( str, STR_MENU_CANCEL ) == 0 ){
				break;
			} else {
				return str;
			}
		}
	}

	return NULL;
}

/**/

char	*cb_menu_formation( menu_t **pp, menu_t **dflt )
{
	char	*str;
	mbr_t	*mbr;
	menu_t	*dflt2;

	set_menu_dflt_misc( *pp );

	mbr = NULL;

	while( 1 ){
		str = exec_menu_sel_mbr( &mbr,
				MSG_TTL_MENU_FORMATION_SEL_MBR, TRUE, FALSE );
		if( str != NULL )
			break;
		if( mbr == NULL )
			return STR_MENU_ERR;
		set_sel_mbr_n( mbr->mbr_n );

		set_menu_formation( ls_menu_formation, &dflt2,
				get_sel_mbr_n() );
		str = exec_menu( ls_menu_formation, dflt2, NULL );
		if( str == NULL )
			continue;
		if( strcmp( str, STR_MENU_CANCEL ) != 0 )
			break;
	}

	return str;
}

/**/

void	set_menu_formation( menu_t *ls, menu_t **dflt, long mbr_n )
{
	long	i, k;

	k = 0;

	*dflt = NULL;

	str_nz_cpy( ls[k].path, "/formation", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/formation/title", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_TTL_MENU_FORMATION_SEL_N,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( i == mbr_n )
			*dflt = &(ls[k]);

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/formation/%ld", i );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + i);
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE, "%ld", (i + 1) );
		ls[k].call_back = cb_menu_formation_sel_n;
		ls[k].arg = (void *)i;
		ls[k].flg = FLG_NULL;
		k++;
	}

	ls[k].path[0] = '\0';
}

/**/

char	*cb_menu_formation_sel_n( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	sel_mbr_n = get_sel_mbr_n();
	long	src, dst, i;
	mbr_t	*tmp;

	src = sel_mbr_n;
	dst = (long)((*pp)->arg);

	clr_map_all_mbr();
	for( i = 0; i < MBR_MAX_N; i++ ){
		pty->mbr[i]->x = pty->mbr[i]->pre_x;
		pty->mbr[i]->y = pty->mbr[i]->pre_y;
	}

	if( src == dst ){
		;
	} else if( chk_flg( pty->mbr[dst]->stat, FLG_STAT_NOT_EXIST ) ){
		tmp = pty->mbr[src];
		pty->mbr[src] = pty->mbr[dst];
		pty->mbr[dst] = tmp;
	} else if( src < dst ){
		tmp = pty->mbr[src];
		for( i = src; i < dst; i++ )
			pty->mbr[i] = pty->mbr[i + 1];
		pty->mbr[dst] = tmp;
	} else {
		tmp = pty->mbr[src];
		for( i = src; i > dst; i-- )
			pty->mbr[i] = pty->mbr[i - 1];
		pty->mbr[dst] = tmp;
	}

	for( i = 0; i < MBR_MAX_N; i++ )
		pty->mbr[i]->mbr_n = i;

	set_map_all_mbr();

	return "/misc/formation";
}

/**/

char	*cb_menu_position( menu_t **pp, menu_t **dflt )
{
	char	*str;

	set_menu_dflt_misc( *pp );

	g_sel_mbr = NULL;
	while( 1 ){
		/* メンバーを撰択 */

		str = exec_menu_sel_mbr(
				&g_sel_mbr, MSG_MENU_CRSR_MOVE_MBR,
				TRUE, FALSE );
		if( str != NULL ){
			if( strcmp( str, STR_MENU_CANCEL ) == 0 )
				break;
			else
				return str;
		}
		if( g_sel_mbr == NULL )
			return STR_MENU_ERR;

		/* 配置を撰択 */

		str = exec_menu_position( g_sel_mbr );
		if( str != NULL ){
			if( strcmp( str, STR_MENU_CANCEL ) == 0 )
				continue;
			else
				return str;
		}
	}

	return STR_MENU_CANCEL;
}

/**/

char	*exec_menu_position( mbr_t *mbr )
{
	const char	*pos_path;
	menu_t	*ls, *p;

	g_sel_mbr = mbr;

	pos_path = "";
	switch( mbr->position_kind ){
	case POSITION_KIND_NULL:
	case POSITION_KIND_MAX_N:
		break;
	case POSITION_KIND_FORWARD:
		pos_path = "forward";
		break;
	case POSITION_KIND_HALFBACK:
		pos_path = "halfback";
		break;
	case POSITION_KIND_BACK:
		pos_path = "back";
		break;
	}
	if( pos_path[0] == '\0' )
		return STR_MENU_ERR;

	ls = ls_menu_position;
	p = srch_menu( ls, pos_path );
	set_menu_radio_item( ls, p );

	return exec_menu( ls, p, NULL );
}

/**/

char	*cb_menu_position_sel( menu_t **pp, menu_t **dflt )
{
	if( g_sel_mbr == NULL )
		return STR_MENU_ERR;

	/* 配置を設定 */
	g_sel_mbr->position_kind = (position_kind_t)(long)((*pp)->arg);

	return NULL;
}

/**/

char	*cb_menu_crsr( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );

	*pp = ls_menu_move_crsr;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_crsr_move( menu_t **pp, menu_t **dflt )
{
	pos_t	*crsr = get_main_crsr();

	switch( (long)((*pp)->arg) ){
	case 1:
		crsr->x--;
		crsr->y++;
		break;
	case 2:
		crsr->y++;
		break;
	case 3:
		crsr->x++;
		crsr->y++;
		break;
	case 4:
		crsr->x--;
		break;
	case 6:
		crsr->x++;
		break;
	case 7:
		crsr->x--;
		crsr->y--;
		break;
	case 8:
		crsr->y--;
		break;
	case 9:
		crsr->x++;
		crsr->y--;
		break;
	default:
		return STR_MENU_ERR;
	}
	chk_scroll( TRUE );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_crsr_move_abs( menu_t **pp, menu_t **dflt )
{
	pos_t	pos;

	if( get_key_pos( &pos ) )
		move_crsr_abs( pos.x, pos.y );

	return NULL;
}

/**/

char	*cb_menu_crsr_move_stop( menu_t **pp, menu_t **dflt )
{
	chk_scroll( FALSE );

	return STR_MENU_CANCEL;
}

/**/

void	move_crsr_abs( long x, long y )
{
	pos_t	*crsr = get_main_crsr();

	crsr->x = x;
	crsr->y = y;
	chk_scroll( FALSE );
}

/**/

void	move_crsr_rel( long dx, long dy )
{
	pos_t	*crsr = get_main_crsr();

	crsr->x += dx;
	crsr->y += dy;
	chk_scroll( FALSE );
}

/**/

char	*cb_menu_crsr_quick_move( menu_t **pp, menu_t **dflt )
{
	switch( (long)((*pp)->arg) ){
	case 1:
		jump_crsr( -1, +1 );
		break;
	case 2:
		jump_crsr( 0, +1 );
		break;
	case 3:
		jump_crsr( +1, +1 );
		break;
	case 4:
		jump_crsr( -1, 0 );
		break;
	case 6:
		jump_crsr( +1, 0 );
		break;
	case 7:
		jump_crsr( -1, -1 );
		break;
	case 8:
		jump_crsr( 0, -1 );
		break;
	case 9:
		jump_crsr( +1, -1 );
		break;
	default:
		return STR_MENU_ERR;
	}
	chk_scroll( TRUE );

	return STR_MENU_CANCEL;
}

/**/

void	jump_crsr( long dx, long dy )
{
	pos_t	*crsr = get_main_crsr();
	dun_t	*dun;
	long	mx, my, nx, ny;
	long	mc, nc, emc, enc;
	flg_map_t	mf, nf;
	long	x, y;
	long	c;
	long	i;

	dun = get_dun();

	mx = crsr->x;
	my = crsr->y;
	nx = crsr->x + dx;
	ny = crsr->y + dy;
	if( nx < 0 )
		return;
	if( nx > MAP_MAX_X - 1 )
		return;
	if( ny < 0 )
		return;
	if( ny > MAP_MAX_Y - 1 )
		return;
	mc = dun->map.obj.mjr[my][mx];
	mf = dun->map.obj.flg[my][mx];
	nc = dun->map.obj.mjr[ny][nx];
	nf = dun->map.obj.flg[ny][nx];

	emc = FACE_MJR_NULL;
	enc = FACE_MJR_NULL;
	if( !chk_flg( mf, FLG_MAP_OBJ_FIND )
			|| !chk_flg( nf, FLG_MAP_OBJ_FIND ) ){
		crsr->x += dx;
		crsr->y += dy;
		return;
	} else if( (mc == FACE_MJR_FLOOR) && (nc == FACE_MJR_FLOOR) ){
		emc = FACE_MJR_NULL;
		enc = FACE_MJR_WALL;
	} else if( (mc == FACE_MJR_FLOOR) && (nc == FACE_MJR_WALL) ){
		crsr->x += dx;
		crsr->y += dy;
		return;
	} else if( (mc == FACE_MJR_WALL) && (nc == FACE_MJR_FLOOR) ){
		crsr->x += dx;
		crsr->y += dy;
		return;
	} else if( (mc == FACE_MJR_WALL) && (nc == FACE_MJR_WALL) ){
		emc = FACE_MJR_NULL;
		enc = FACE_MJR_FLOOR;
	}

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		mx += dx;
		my += dy;
		nx += dx;
		ny += dy;
		mc = dun->map.obj.mjr[my][mx];
		mf = dun->map.obj.flg[my][mx];
		nc = dun->map.obj.mjr[ny][nx];
		nf = dun->map.obj.flg[ny][nx];

		if( !chk_flg( mf, FLG_MAP_OBJ_FIND )
				|| !chk_flg( nf, FLG_MAP_OBJ_FIND ) ){
			crsr->x = mx;
			crsr->y = my;
			return;
		}
		if( (emc != FACE_MJR_NULL) && (mc == emc) )
			break;
		if( (enc != FACE_MJR_NULL) && (nc == enc) )
			break;
		if( (emc == FACE_MJR_NULL) && (enc == FACE_MJR_NULL)
				&& (mc != FACE_MJR_NULL) ){
			break;
		}

		for( y = -1; y <= +1; y++ ){
			if( my + y < 0 )
				continue;
			if( my + y > MAP_MAX_Y - 1 )
				continue;

			for( x = -1; x <= +1; x++ ){
				if( mx + x < 0 )
					continue;
				if( mx + x > MAP_MAX_X - 1 )
					continue;

				c = dun->map.obj.mjr[my + y][mx + x];
				if( (c != FACE_MJR_WALL)
						&& (c != FACE_MJR_FLOOR)
						&& (c != FACE_MJR_NULL) ){
					crsr->x = mx;
					crsr->y = my;
					return;
				}

				c = dun->map.chr.mjr[my + y][mx + x];
				if( (c != FACE_MJR_NULL) ){
					crsr->x = mx;
					crsr->y = my;
					return;
				}
			}
		}
	}

	crsr->x = mx;
	crsr->y = my;
}

/**/

char	*cb_menu_crsr_ind_square( menu_t **pp, menu_t **dflt )
{
	bool_t	flg_sel_dead;
	party_t	*pty = get_party();
	menu_t	*ls;
	long	i, k;

	*dflt = g_menu_dflt_ind_square;
	ls = ls_menu_ind_square;
	k = 0;

	flg_sel_dead = TRUE;

	str_nz_cpy( ls[k].path, "/cursor/individual square",
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

	str_nz_cpy( ls[k].path, "/cursor/individual square/--",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_MENU_CRSR_IND_SQUARE,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/cursor/individual square/number",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<OpenWinItem>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'Z';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_MENU_CRSR_IND_SQUARE_NUM,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_crsr_ind_square_num;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;
		if( !flg_sel_dead )
			if( chk_flg( pty->mbr[i]->stat, FLG_STAT_DEAD ) )
				continue;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/cursor/individual square/%ld", i );
		str_nz_cpy( ls[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + i);
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, pty->mbr[i]->name, MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_crsr_ind_square_mbr;
		ls[k].arg = (void *)(pty->mbr[i]);
		ls[k].flg = FLG_NULL;
		k++;
	}

	str_nz_cpy( ls[k].path, "/cursor/individual square/party",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Item>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'V';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_MENU_CRSR_IND_SQUARE_PARTY,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_crsr_ind_square_party;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	ls[k].path[0] = '\0';

	/* 実行 */

	return exec_menu( ls, *dflt, NULL );
}

/**/

char	*cb_menu_crsr_ind_square_num( menu_t **pp, menu_t **dflt )
{
	long	c;

	g_menu_dflt_ind_square = *pp;

	c = get_key( g_flg_clr_key_buf_menu );
	menu_crsr_ind_square_set_mbr( c - '1' );

	return NULL;
}

/**/

char	*cb_menu_crsr_ind_square_mbr( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;

	g_menu_dflt_ind_square = *pp;

	mbr = (mbr_t *)((*pp)->arg);
	if( mbr == NULL )
		return STR_MENU_ERR;

	menu_crsr_ind_square_set_mbr( mbr->mbr_n );

	return NULL;
}

/**/

void	menu_crsr_ind_square_set_mbr( long mbr_n )
{
	pos_t	*crsr;

	if( mbr_n < 0 )
		return;
	if( mbr_n >= MBR_MAX_N )
		return;

	crsr = get_main_crsr();
	if( crsr == NULL )
		return;

	set_square_mbr_ind_pos( mbr_n, crsr->x, crsr->y );
	draw_square();
}

/**/

char	*cb_menu_crsr_ind_square_party( menu_t **pp, menu_t **dflt )
{
	g_menu_dflt_ind_square = *pp;

	menu_move_square();

	return NULL;
}

/**/

char	*cb_menu_crsr_scroll( menu_t **pp, menu_t **dflt )
{
	switch( (long)((*pp)->arg) ){
	case 1:
		crsr_scroll( -1, +1 );
		break;
	case 2:
		crsr_scroll( 0, +1 );
		break;
	case 3:
		crsr_scroll( +1, +1 );
		break;
	case 4:
		crsr_scroll( -1, 0 );
		break;
	case 6:
		crsr_scroll( +1, 0 );
		break;
	case 7:
		crsr_scroll( -1, -1 );
		break;
	case 8:
		crsr_scroll( 0, -1 );
		break;
	case 9:
		crsr_scroll( +1, -1 );
		break;
	default:
		return STR_MENU_ERR;
	}
	chk_scroll( TRUE );

	return STR_MENU_CANCEL;
}

/**/

void	crsr_scroll( long dx, long dy )
{
	pos_t	*crsr = get_main_crsr();
	pos_t	*draw;
	pos_t	*draw_gui;

	draw = get_map_draw_pos();

	/* X */

	draw->x += dx;
	crsr->x += dx;

	if( draw->x < 0 )
		draw->x = 0;
	if( draw->x > MAP_MAX_X - (get_map_col() / 2) )
		draw->x = MAP_MAX_X - (get_map_col() / 2);

	if( crsr->x < 0 )
		crsr->x = 0;
	if( crsr->x > MAP_MAX_X - 1 )
		crsr->x = MAP_MAX_X - 1;

	/* Y */

	draw->y += dy;
	crsr->y += dy;

	if( draw->y < 0 )
		draw->y = 0;
	if( draw->y > MAP_MAX_Y - get_map_row() )
		draw->y = MAP_MAX_Y - get_map_row();

	if( crsr->y < 0 )
		crsr->y = 0;
	if( crsr->y > MAP_MAX_Y - 1 )
		crsr->y = MAP_MAX_Y - 1;

	/* GUI */

	draw_gui = get_map_draw_pos_gui();
	if( draw_gui != NULL )
		call_pcg_dun_scroll( draw_gui->x + dx, draw_gui->y + dy );

	/**/

	redraw_map();
}

/**/

char	*cb_menu_crsr_move_mbr( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;
	char	*str;

	mbr = NULL;
	str = exec_menu_sel_mbr(
			&mbr, MSG_MENU_CRSR_MOVE_MBR,
			FALSE, TRUE );
	if( str != NULL )
		return str;
	if( mbr == NULL )
		return STR_MENU_ERR;

	return menu_crsr_move_mbr( mbr );
}

/**/

char	*menu_crsr_move_mbr_n( long mbr_n )
{
	party_t	*pty = get_party();

	if( mbr_n < 0 )
		return STR_MENU_ERR;
	if( mbr_n >= MBR_MAX_N )
		return STR_MENU_ERR;

	return menu_crsr_move_mbr( pty->mbr[mbr_n] );
}

/**/

char	*menu_crsr_move_mbr( mbr_t *mbr )
{
	pos_t	*crsr = get_main_crsr();

	if( mbr == NULL )
		return STR_MENU_ERR;

	crsr->x = mbr->x;
	crsr->y = mbr->y;
	chk_scroll( TRUE );

	return NULL;
}

/**/

char	*cb_menu_crsr_center( menu_t **pp, menu_t **dflt )
{
	scroll_center();

	return STR_MENU_CANCEL;
}

/**/

void	chk_scroll( bool_t flg_gui )
{
	pos_t	*draw_gui;
	static long	pre_x = -1;
	static long	pre_y = -1;

	if( chk_flg( g_flg_scroll, FLG_SCROLL_SMOOTH ) )
		scroll_smooth();
	else if( chk_flg( g_flg_scroll, FLG_SCROLL_CENTER ) )
		scroll_center();
	else
		scroll_half_page();

	call_key_check_move_crsr();

	draw_gui = get_map_draw_pos_gui();
	if( draw_gui != NULL ){
		if( (pre_x != draw_gui->x) || (pre_y != draw_gui->y) ){
			call_pcg_dun_scroll( draw_gui->x, draw_gui->y );
			pre_x = draw_gui->x;
			pre_y = draw_gui->y;
		}
	}

	update_crsr();
}

/**/

void	scroll_smooth( void )
{
	pos_t	*crsr = get_main_crsr();
	bool_t	flg;
	pos_t	*draw;

	draw = get_map_draw_pos();

	flg = FALSE;

	/* X */

	if( crsr->x < 0 )
		crsr->x = 0;
	if( crsr->x > MAP_MAX_X - 1 )
		crsr->x = MAP_MAX_X - 1;

	if( draw->x > crsr->x ){
		draw->x = crsr->x;
		flg = TRUE;
	}
	if( draw->x < crsr->x - ((get_map_col() / 2) - 1) ){
		draw->x = crsr->x - ((get_map_col() / 2) - 1);
		flg = TRUE;
	}

	/* Y */

	if( crsr->y < 0 )
		crsr->y = 0;
	if( crsr->y > MAP_MAX_Y - 1 )
		crsr->y = MAP_MAX_Y - 1;

	if( draw->y > crsr->y ){
		draw->y = crsr->y;
		flg = TRUE;
	}
	if( draw->y < crsr->y - (get_map_row() - 1) ){
		draw->y = crsr->y - (get_map_row() - 1);
		flg = TRUE;
	}

	/* 画面書き換え */

	if( flg )
		redraw_map();
}

/**/

void	scroll_center( void )
{
	pos_t	*crsr = get_main_crsr();
	pos_t	*draw;

	draw = get_map_draw_pos();

	/* X */

	if( crsr->x < 0 )
		crsr->x = 0;
	if( crsr->x > MAP_MAX_X - 1 )
		crsr->x = MAP_MAX_X - 1;

	draw->x = crsr->x - ((get_map_col() / 2) / 2);
	if( draw->x < 0 )
		draw->x = 0;
	if( draw->x > MAP_MAX_X - (get_map_col() / 2) )
		draw->x = MAP_MAX_X - (get_map_col() / 2);

	/* Y */

	if( crsr->y < 0 )
		crsr->y = 0;
	if( crsr->y > MAP_MAX_Y - 1 )
		crsr->y = MAP_MAX_Y - 1;

	draw->y = crsr->y - (get_map_row() / 2);
	if( draw->y < 0 )
		draw->y = 0;
	if( draw->y > MAP_MAX_Y - get_map_row() )
		draw->y = MAP_MAX_Y - get_map_row();

	redraw_map();
}

/**/

void	scroll_half_page( void )
{
	pos_t	*crsr = get_main_crsr();
	bool_t	flg;
	pos_t	*draw;

	draw = get_map_draw_pos();
	flg = FALSE;

	/* X */

	if( crsr->x < 0 )
		crsr->x = 0;
	if( crsr->x > MAP_MAX_X - 1 )
		crsr->x = MAP_MAX_X - 1;

	while( crsr->x < draw->x ){
		draw->x -= SCROLL_WIDTH;
		flg = TRUE;
		if( draw->x < 0 ){
			draw->x = 0;
			break;
		}
	}

	while( crsr->x > draw->x + (get_map_col() / 2) - 1 ){
		draw->x += SCROLL_WIDTH;
		flg = TRUE;
		if( draw->x > MAP_MAX_X - (get_map_col() / 2) ){
			draw->x = MAP_MAX_X - (get_map_col() / 2);
			break;
		}
	}

	/* Y */

	if( crsr->y < 0 )
		crsr->y = 0;
	if( crsr->y > MAP_MAX_Y - 1 )
		crsr->y = MAP_MAX_Y - 1;

	while( crsr->y < draw->y ){
		draw->y -= SCROLL_WIDTH;
		flg = TRUE;
		if( draw->y < 0 ){
			draw->y = 0;
			break;
		}
	}

	while( crsr->y > draw->y + get_map_row() - 1 ){
		draw->y += SCROLL_HEIGHT;
		flg = TRUE;
		if( draw->y > MAP_MAX_Y - get_map_row() ){
			draw->y = MAP_MAX_Y - get_map_row();
			break;
		}
	}

	/* end */

	if( flg )
		redraw_map();
}

/**/

void	move_crsr_mbr_trgt( mbr_t *mbr )
{
	pos_t	*crsr = get_main_crsr();

	if( mbr == NULL )
		return;

	switch( mbr->trgt.kind ){
	case TRGT_KIND_NULL:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		return;
	case TRGT_KIND_MNSTR:
		crsr->x = ((mnstr_t *)(mbr->trgt.p))->x;
		crsr->y = ((mnstr_t *)(mbr->trgt.p))->y;
		break;
	case TRGT_KIND_MNSTR_NULL:
		crsr->x = ((mnstr_null_t *)(mbr->trgt.p))->x;
		crsr->y = ((mnstr_null_t *)(mbr->trgt.p))->y;
		break;
	case TRGT_KIND_MBR:
		crsr->x = ((mbr_t *)(mbr->trgt.p))->x;
		crsr->y = ((mbr_t *)(mbr->trgt.p))->y;
		break;
	case TRGT_KIND_SQUARE:
	case TRGT_KIND_ITEM:
	case TRGT_KIND_DOOR:
	case TRGT_KIND_TRAP:
	case TRGT_KIND_QUEUE:
	case TRGT_KIND_POS:
		crsr->x = mbr->x;
		crsr->y = mbr->y;
		break;
	}
}

/**/

char	*cb_menu_crsr_next_pos_mbr( menu_t **pp, menu_t **dflt )
{
	next_pos_mbr( +1 );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_crsr_next_pos_mnstr( menu_t **pp, menu_t **dflt )
{
	next_pos_mnstr( +1 );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_crsr_next_pos_item( menu_t **pp, menu_t **dflt )
{
	next_pos_item( +1 );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_crsr_next_pos_door( menu_t **pp, menu_t **dflt )
{
	next_pos_door( +1 );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_crsr_next_pos_obj( menu_t **pp, menu_t **dflt )
{
	next_pos_obj( +1 );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_crsr_next_pos_square( menu_t **pp, menu_t **dflt )
{
	next_pos_square( +1 );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_crsr_next_pos_all( menu_t **pp, menu_t **dflt )
{
	next_pos_all( +1 );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_crsr_prev_pos( menu_t **pp, menu_t **dflt )
{
	prev_pos();

	return STR_MENU_CANCEL;
}

/**/

bool_t	next_pos_mbr( long d )
{
	pos_t	*crsr = get_main_crsr();
	party_t *pty;
	bool_t	flg;
	long	n;
	long	i, j;

	pty = get_party();

	flg = FALSE;
	if( g_next_pos.kind == NEXT_POS_KIND_MBR ){
		if( (crsr->x == g_next_pos.x)
				&& (crsr->y == g_next_pos.y) ){
			n = g_next_pos.n;
			for( i = 0; i < labs( d ); i++ ){
				for( j = 0; j < MBR_MAX_N; j++ ){
					n += sgn_l( d );
					if( n >= MBR_MAX_N ){
						n = 0;
						flg = TRUE;
					} else if( n < 0 ){
						n = MBR_MAX_N - 1;
						flg = TRUE;
					}
					if( !chk_flg_or( pty->mbr[n]->stat,
							FLG_STAT_NOT_EXIST
							| FLG_STAT_DEAD ) ){
						break;
					}
				}
			}
		} else {
			n = g_next_pos.n;
		}
	} else {
		n = 0;
		for( j = 0; j < MBR_MAX_N; j++ ){
			if( n >= MBR_MAX_N ){
				n = 0;
				flg = TRUE;
			}
			if( !chk_flg_or( pty->mbr[n]->stat,
					FLG_STAT_NOT_EXIST
					| FLG_STAT_DEAD ) ){
				break;
			}
			n++;
		}
	}
	g_next_pos.kind = NEXT_POS_KIND_MBR;
	g_next_pos.p = pty->mbr[n];
	g_next_pos.n = n;
	g_next_pos.x = pty->mbr[n]->x;
	g_next_pos.y = pty->mbr[n]->y;

	crsr->x = g_next_pos.x;
	crsr->y = g_next_pos.y;
	chk_scroll( TRUE );

	return flg;
}

/**/

bool_t	next_pos_mnstr( long d )
{
	pos_t	*crsr = get_main_crsr();
	dun_t	*dun;
	pos_t	*draw;
	long	dx, dy;
	long	c;
	flg_map_t	flg;
	bool_t	flg_find;

	dun = get_dun();
	draw = get_map_draw_pos();

	flg = dun->map.chr.flg[crsr->y][crsr->x];
	if( chk_flg( flg, FLG_MAP_CHR_INVISIBLE ) ){
		/* 見えないモンスターなら */
		c = FACE_MJR_NULL;
	} else if( get_pet( crsr->x, crsr->y ) != NULL ){
		c = FACE_MJR_NULL;
	} else {
		c = dun->map.chr.mjr[crsr->y][crsr->x];
	}
	if( (c == FACE_MJR_MBR) || (c == FACE_MJR_NULL) ){
		/* 最初から */
		if( d >= +1 ){
			dx = 0;
			dy = 0;
		} else {
			dx = (get_map_col() / 2) - 1;
			dy = get_map_row() - 1;
		}
	} else {
		flg_map_t	flg;

		/* 現在地から */
		dx = crsr->x - draw->x + d;
		dy = crsr->y - draw->y;

		flg = dun->map.chr.flg[crsr->y][crsr->x];
		if( !chk_flg( flg, FLG_MAP_CHR_FIND ) ){
			if( d >= +1 ){
				dx = 0;
				dy = 0;
			} else {
				dx = (get_map_col() / 2) - 1;
				dy = get_map_row() - 1;
			}
		}
	}

	g_next_pos.kind = NEXT_POS_KIND_MNSTR;
	g_next_pos.p = NULL;
	g_next_pos.n = 0;

	flg_find = FALSE;
	if( next_pos_mnstr_sub( &dx, &dy, d ) ){
		flg_find = FALSE;
	} else {
		if( d >= +1 ){
			dx = 0;
			dy = 0;
		} else {
			dx = (get_map_col() / 2) - 1;
			dy = get_map_row() - 1;
		}
		if( next_pos_mnstr_sub( &dx, &dy, d ) ){
			flg_find = TRUE;
		} else {
			return TRUE;
		}
	}

	g_next_pos.x = draw->x + dx;
	g_next_pos.y = draw->y + dy;

	crsr->x = g_next_pos.x;
	crsr->y = g_next_pos.y;
	chk_scroll( TRUE );

	return flg_find;
}

/**/

bool_t	next_pos_mnstr_sub( long *dx, long *dy, long d )
{
	dun_t	*dun;
	pos_t	*draw;
	long	xx, yy;
	long	c;

	dun = get_dun();
	draw = get_map_draw_pos();

	for( ; *dy < get_map_row(); (*dy) += d ){
		if( *dy < 0 )
			break;

		for( ; *dx < (get_map_col() / 2); (*dx) += d ){
			if( *dx < 0 )
				break;

			xx = draw->x + *dx;
			yy = draw->y + *dy;

			if( chk_flg( dun->map.chr.flg[yy][xx],
					FLG_MAP_CHR_INVISIBLE ) ){
				/* 見えないモンスターなら */
				c = FACE_MJR_NULL;
			} else if( get_pet( xx, yy ) != NULL ){
				c = FACE_MJR_NULL;
			} else {
				c = dun->map.chr.mjr[yy][xx];
			}
			if( (c == FACE_MJR_MBR) || (c == FACE_MJR_NULL) ){
				continue;
			} else {
				if( !chk_flg( dun->map.chr.flg[yy][xx],
						FLG_MAP_OBJ_FIND ) ){
					continue;
				}
				return TRUE;
			}
		}
		if( d >= +1 ){
			*dx = 0;
		} else {
			*dx = (get_map_col() / 2) - 1;
		}
	}
	return FALSE;
}

/**/

bool_t	next_pos_item( long d )
{
	return next_pos_item_obj( d, TRUE );
}

/**/

bool_t	next_pos_obj( long d )
{
	return next_pos_item_obj( d, FALSE );
}

/**/

bool_t	next_pos_item_obj( long d, bool_t flg_item )
{
	pos_t	*crsr = get_main_crsr();
	dun_t	*dun;
	pos_t	*draw;
	long	dx, dy;
	long	c;
	bool_t	flg_ret, flg_reset;

	dun = get_dun();
	draw = get_map_draw_pos();

	flg_reset = FALSE;

	c = dun->map.obj.mjr[crsr->y][crsr->x];
	switch( c ){
	case FACE_MJR_NULL:
	case FACE_MJR_WALL:
	case FACE_MJR_FLOOR:
	case FACE_MJR_DOOR_CLOSE:
	case FACE_MJR_DOOR_OPEN:
		flg_reset = TRUE;
		break;
	case FACE_MJR_STAIRS_UP:
	case FACE_MJR_STAIRS_DOWN:
	case FACE_MJR_TRAP:
		if( flg_item )
			flg_reset = TRUE;
		break;
	default:
		flg_reset = FALSE;
		break;
	}
	if( flg_reset ){
		/* 最初から */
		if( d >= +1 ){
			dx = 0;
			dy = 0;
		} else {
			dx = (get_map_col() / 2) - 1;
			dy = get_map_row() - 1;
		}
	} else {
		/* 現在地から */
		dx = crsr->x - draw->x + d;
		dy = crsr->y - draw->y;

		if( !chk_flg( dun->map.obj.flg[crsr->y][crsr->x],
				FLG_MAP_OBJ_FIND ) ){
			if( d >= +1 ){
				dx = 0;
				dy = 0;
			} else {
				dx = (get_map_col() / 2) - 1;
				dy = get_map_row() - 1;
			}
		}
	}

	g_next_pos.kind = NEXT_POS_KIND_OBJ;
	g_next_pos.p = NULL;
	g_next_pos.n = 0;

	flg_ret = FALSE;
	if( next_pos_item_obj_sub( &dx, &dy, d, flg_item ) ){
		flg_ret = FALSE;
	} else {
		if( d >= +1 ){
			dx = 0;
			dy = 0;
		} else {
			dx = (get_map_col() / 2) - 1;
			dy = get_map_row() - 1;
		}
		if( next_pos_item_obj_sub( &dx, &dy, d, flg_item ) ){
			flg_ret = TRUE;
		} else {
			return TRUE;
		}
	}

	g_next_pos.x = draw->x + dx;
	g_next_pos.y = draw->y + dy;

	crsr->x = g_next_pos.x;
	crsr->y = g_next_pos.y;
	chk_scroll( TRUE );

	return flg_ret;
}

/**/

bool_t	next_pos_item_obj_sub( long *dx, long *dy, long d, bool_t flg_item )
{
	dun_t	*dun;
	pos_t	*draw;
	long	c;

	dun = get_dun();
	draw = get_map_draw_pos();

	for( ; *dy < get_map_row(); (*dy) += d ){
		if( *dy < 0 )
			break;

		for( ; *dx < (get_map_col() / 2); (*dx) += d ){
			if( *dx < 0 )
				break;

			c = dun->map.obj.mjr[draw->y + *dy]
					[draw->x + *dx];
			switch( c ){
			case FACE_MJR_NULL:
			case FACE_MJR_WALL:
			case FACE_MJR_FLOOR:
			case FACE_MJR_DOOR_CLOSE:
			case FACE_MJR_DOOR_OPEN:
				continue;
			case FACE_MJR_STAIRS_UP:
			case FACE_MJR_STAIRS_DOWN:
			case FACE_MJR_TRAP:
				if( flg_item )
					continue;
				/* break; */
			default:
				if( !chk_flg( dun->map.obj.flg[draw->y + *dy]
						[draw->x + *dx],
						FLG_MAP_OBJ_FIND ) ){
					continue;
				}
				return TRUE;
			}
		}
		if( d >= +1 ){
			*dx = 0;
		} else {
			*dx = (get_map_col() / 2) - 1;
		}
	}
	return FALSE;
}

/**/

bool_t	next_pos_door( long d )
{
	pos_t	*crsr = get_main_crsr();
	dun_t	*dun;
	pos_t	*draw;
	long	mx, my;
	long	dr_n;
	long	n;
	bool_t	flg, flg_cont, flg_find;
	long	pre_n;

	dun = get_dun();
	draw = get_map_draw_pos();
	mx = crsr->x;
	my = crsr->y;
	dr_n = dun->door_n;
	flg = FALSE;
	flg_find = FALSE;

	if( dun->door_n <= 0 )
		return TRUE;

	if( g_next_pos.kind == NEXT_POS_KIND_DOOR ){
		pre_n = g_next_pos.n;
		/* カーソルを移動しなかったか? */
		if( (mx == g_next_pos.x) && (my == g_next_pos.y) ){
			n = (g_next_pos.n + d + dr_n) % dr_n;
			flg_cont = TRUE;
		} else {
			/* もう一度同じところをマーク */
			n = g_next_pos.n;
			flg_cont = FALSE;
		}
	} else {
		if( d >= +1 )
			n = 0;
		else
			n = dr_n - 1;
		pre_n = n;

		flg_cont = FALSE;
	}

	do {
		door_t	*dr = &(dun->door[n]);

		/* 一回りしたか`ェック */
		if( flg_cont ){
			if( (d >= +1) && (n == 0) )
				flg = TRUE;
			if( (d <= -1) && (n == dr_n - 1) )
				flg = TRUE;
		}

		if( (dr->x + dr->dx - 1) < draw->x )
			continue;
		if( (dr->y + dr->dy - 1) < draw->y )
			continue;
		if( dr->x > (draw->x + (get_map_col() / 2) - 1) )
			continue;
		if( dr->y > (draw->y + get_map_row() - 1) )
			continue;
		if( chk_flg( dr->flg, FLG_DOOR_SECRET ) )
			continue;

		/* ドアを見つけた */
		flg_find = TRUE;
		g_next_pos.kind = NEXT_POS_KIND_DOOR;
		g_next_pos.p = dr;
		g_next_pos.n = dr->n;

		if( mx < dr->x )
			g_next_pos.x = dr->x;
		else if( (dr->x + dr->dx - 1) < mx )
			g_next_pos.x = dr->x + dr->dx - 1;
		else
			g_next_pos.x = mx;

		if( my < dr->y )
			g_next_pos.y = dr->y;
		else if( (dr->y + dr->dy - 1) < my )
			g_next_pos.y = dr->y + dr->dy - 1;
		else
			g_next_pos.y = my;

		crsr->x = g_next_pos.x;
		crsr->y = g_next_pos.y;
		chk_scroll( TRUE );

		break;
	} while( n = (n + d + dr_n) % dr_n, n != pre_n );

	if( flg_cont && (n == pre_n) )
		flg = TRUE;
	if( !flg_find )
		flg = TRUE;

	return flg;
}

/**/

bool_t	next_pos_square( long d )
{
	pos_t	*crsr = get_main_crsr();
	party_t *pty;
	void	*pre_p;

	pty = get_party();
	pre_p = g_next_pos.p;

	g_next_pos.kind = NEXT_POS_KIND_SQUARE;
	g_next_pos.p = &(pty->square);
	g_next_pos.n = 0;
	g_next_pos.x = pty->square.x;
	g_next_pos.y = pty->square.y;

	crsr->x = g_next_pos.x;
	crsr->y = g_next_pos.y;
	chk_scroll( TRUE );

	return( pre_p == g_next_pos.p );
}

/**/

bool_t	next_pos_all( long d )
{
	bool_t	flg;

	flg = FALSE;
	if( g_next_pos.kind == NEXT_POS_KIND_SQUARE ){
		flg = next_pos_square( +1 );
	}
	if( flg || (g_next_pos.kind == NEXT_POS_KIND_MBR) ){
		flg = next_pos_mbr( +1 );
	}
	if( flg || (g_next_pos.kind == NEXT_POS_KIND_MNSTR) ){
		flg = next_pos_mnstr( +1 );
	}
	if( flg || (g_next_pos.kind == NEXT_POS_KIND_OBJ) ){
		flg = next_pos_obj( +1 );
	}
	if( flg || (g_next_pos.kind == NEXT_POS_KIND_DOOR) ){
		flg = next_pos_door( +1 );
	}
	if( flg ){
		next_pos_square( +1 );
	}

	return flg;
}

/**/

bool_t	prev_pos( void )
{
	bool_t	flg;

	flg = FALSE;
	switch( g_next_pos.kind ){
	case NEXT_POS_KIND_SQUARE:
		flg = next_pos_square( -1 );
		break;
	case NEXT_POS_KIND_MBR:
		flg = next_pos_mbr( -1 );
		break;
	case NEXT_POS_KIND_DOOR:
		flg = next_pos_door( -1 );
		break;
	case NEXT_POS_KIND_OBJ:
		flg = next_pos_obj( -1 );
		break;
	case NEXT_POS_KIND_MNSTR:
		flg = next_pos_mnstr( -1 );
		break;
	}

	return flg;
}

/**/

char	*cb_menu_msg( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );
	return NULL;
}

/**/

char	*cb_menu_back_log( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );

	return exec_back_log();
}

/**/

char	*exec_back_log( void )
{
	long	n, max_n;

	if( !chk_msg_mul_line() )
		return STR_MENU_ERR;

	max_n = get_ls_msg_idx();
	n = max_n;

	print_log_back( max_n );

	while( 1 ){
		switch( get_key( g_flg_clr_key_buf_menu ) ){
		case CASE_CANCEL:
		case CASE_EXEC:
			print_log_back( max_n );
			return STR_MENU_CANCEL;
		case ' ':
			if( get_flg_space_select() ){
				print_log_back( max_n );
				return NULL;
			} else {
				if( n >= max_n )
					continue;
				n += get_ls_msg_line_per_page();
			}
			break;
		case CASE_ENTER:
			if( get_flg_space_select() ){
				print_log_back( max_n );
				return STR_MENU_CANCEL;
			} else {
				print_log_back( max_n );
				return NULL;
			}
			break;
		case CASE_CRSR_UP:
			if( n <= 0 )
				continue;
			n--;
			break;
		case CASE_CRSR_DOWN:
			if( n >= max_n )
				continue;
			n++;
			break;
		case CASE_CRSR_LEFT:
			if( n <= 0 )
				continue;
			n -= get_ls_msg_line_per_page();
			break;
		case CASE_CRSR_RIGHT:
			if( n >= max_n )
				continue;
			n += get_ls_msg_line_per_page();
			break;
		default:
			continue;
		}

		if( n < 0 )
			n = 0;
		if( n > max_n )
			n = max_n;

		print_log_back( n );
	}
}

/**/

char	*cb_menu_ls_msg( menu_t **pp, menu_t **dflt )
{
	long	n, max_n;

	set_menu_dflt_misc( *pp );

	if( chk_msg_mul_line() )
		return cb_menu_back_log( pp, dflt );

	n = 0;
	max_n = get_ls_msg_n();
	draw_ls_msg( n );
	while( 1 ){
		switch( get_key( g_flg_clr_key_buf_menu ) ){
		case CASE_CANCEL:
		case CASE_EXEC:
			return STR_MENU_CANCEL;
		case ' ':
			if( get_flg_space_select() )
				return NULL;
			break;
		case CASE_ENTER:
			if( get_flg_space_select() )
				return STR_MENU_CANCEL;
			else
				return NULL;
			break;
		case CASE_CRSR_UP:
		case CASE_CRSR_LEFT:
			if( n < max_n - LS_MSG_DRAW_N )
				n += LS_MSG_DRAW_N;
			else
				continue;
			break;
		case CASE_CRSR_DOWN:
		case CASE_CRSR_RIGHT:
			n -= LS_MSG_DRAW_N;
			if( n < 0 ){
				n = 0;
				continue;
			}
			break;
		default:
			continue;
		}

		draw_ls_msg( n );
	}

	return STR_MENU_ERR;
}

/**/

char	*cb_menu_scroll_msg( menu_t **pp, menu_t **dflt )
{
	long	add, n;

	set_menu_dflt_misc( *pp );

	add = (long)((*pp)->arg);
	n = add_scroll_msg_idx( add );

	if( chk_msg_mul_line() )
		print_log_back( n );
	else
		draw_ls_msg( n );

	return NULL;
}

/**/

char	*cb_menu_ls_key_item( menu_t **pp, menu_t **dflt )
{
	star_drop_kind_t	kind;
	bool_t	flg_have;
	long	i;

	set_menu_dflt_misc( *pp );

	flg_have = FALSE;

	for( i = 0; i < STAR_DROP_KIND_MAX_N; i++ ){
		kind = (star_drop_kind_t)i;
		if( chk_key_item( kind ) ){
			print_msg( FLG_NULL, MSG_HAVE_KEY_ITEM,
					get_key_item_name( kind ) );
			flg_have = TRUE;
		}
	}

	if( !flg_have )
		print_msg( FLG_NULL, MSG_NOT_HAVE_KEY_ITEM );

	return NULL;
}

/**/

char	*cb_menu_ls_mnstr( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );
	print_ls_mnstr();

	return NULL;
}

/**/

char	*cb_menu_set_dflt_cnf( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_cnf( *pp );
	return NULL;
}

/**/

char	*cb_menu_cnf( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );
	*dflt = g_menu_dflt_cnf;

	if( chk_flg( get_flg_party(), FLG_PARTY_ACTUAL_FIGHTING ) )
		set_chk_on_menu( *pp, "actual fighting" );
	else
		set_chk_off_menu( *pp, "actual fighting" );

	if( get_flg_space_select() )
		set_chk_on_menu( *pp, "space select" );
	else
		set_chk_off_menu( *pp, "space select" );

	return NULL;
}

/**/

char	*cb_menu_mbr_flg( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	menu_t	*ls;
	flg_chr_t	flg;
	char	*ttl;
	menu_call_back_t	cb;
	long	i;
	long	k;

	set_menu_dflt_cnf( *pp );

	flg = (flg_chr_t)(long)((*pp)->arg);
	switch( flg ){
	case FLG_CHR_AUTO_FIGHT:
		ttl = MSG_MENU_AUTO_FIGHT;
		cb = cb_menu_auto_fight;
		break;
	case FLG_CHR_AUTO_DOOR:
		ttl = MSG_MENU_AUTO_DOOR;
		cb = cb_menu_auto_door;
		break;
	case FLG_CHR_AVOID_TRAP:
		ttl = MSG_MENU_AVOID_TRAP;
		cb = cb_menu_avoid_trap;
		break;
	case FLG_CHR_AUTO_RELOAD:
		ttl = MSG_MENU_AUTO_RELOAD;
		cb = cb_menu_auto_reload;
		break;
	default:
		return STR_MENU_ERR;
	}

	ls = ls_menu_mbr_flg;
	k = 0;

	str_nz_cpy( ls[k].path, "/config member flag",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = cb_menu_mbr_flg_init;
	ls[k].arg = (void *)flg;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/config member flag/title",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, ttl, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/config member flag/%ld", i );
		str_nz_cpy( ls[k].kind, "<CheckItem>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + i);
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, pty->mbr[i]->name,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb;
		ls[k].arg = (void *)pty->mbr[i];
		ls[k].flg = FLG_NULL;
		k++;
	}
	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_mbr_flg_init( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	char	str[4 + 1];
	flg_chr_t	flg;
	long	i;

	flg = (flg_chr_t)(long)((*pp)->arg);

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		sn_printf( str, 4, "%ld", i );
		if( chk_flg( pty->mbr[i]->flg_chr, flg ) )
			set_chk_on_menu( *pp, str );
		else
			set_chk_off_menu( *pp, str );
	}

	return NULL;
}

/**/

char	*cb_menu_auto_fight( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;

	mbr = (mbr_t *)((*pp)->arg);
	mbr->flg_chr ^= FLG_CHR_AUTO_FIGHT;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_auto_door( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;

	mbr = (mbr_t *)((*pp)->arg);
	mbr->flg_chr ^= FLG_CHR_AUTO_DOOR;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_avoid_trap( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;

	mbr = (mbr_t *)((*pp)->arg);
	mbr->flg_chr ^= FLG_CHR_AVOID_TRAP;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_auto_reload( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;

	mbr = (mbr_t *)((*pp)->arg);
	mbr->flg_chr ^= FLG_CHR_AUTO_RELOAD;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_actual_fighting( menu_t **pp, menu_t **dflt )
{
	flg_party_t	flg;

	set_menu_dflt_cnf( *pp );

	flg = get_flg_party();
	flg ^= FLG_PARTY_ACTUAL_FIGHTING;
	set_flg_party( flg );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_space_select( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_cnf( *pp );

	set_flg_space_select( !get_flg_space_select() );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_reset_file_config( menu_t **pp, menu_t **dflt )
{
	ask_t	ask;

	ask = exec_menu_ask( MSG_TTL_MENU_RESET_FILE_ASK, ASK_NO, TRUE );

	if( ask == ASK_ERR )
		return STR_MENU_ERR;
	if( ask != ASK_YES )
		return STR_MENU_CANCEL;

	back_up_game_conf();

	print_msg( FLG_MSG_WRN, MSG_RESET_FILE );

	return NULL;
}

/**/

char	*cb_menu_reset_file_crsr_ptn( menu_t **pp, menu_t **dflt )
{
	ask_t	ask;

	ask = exec_menu_ask( MSG_TTL_MENU_RESET_FILE_ASK, ASK_NO, TRUE );

	if( ask == ASK_ERR )
		return STR_MENU_ERR;
	if( ask != ASK_YES )
		return STR_MENU_CANCEL;

	back_up_crsr_ptn();
	set_main_crsr_ptn_n( 0 );
	set_sub_crsr_ptn_n( 0 );

	print_msg( FLG_MSG_WRN, MSG_RESET_FILE );

	return NULL;
}

/**/

char	*cb_menu_reset_file_town_ptn( menu_t **pp, menu_t **dflt )
{
	ask_t	ask;

	ask = exec_menu_ask( MSG_TTL_MENU_RESET_FILE_ASK, ASK_NO, TRUE );

	if( ask == ASK_ERR )
		return STR_MENU_ERR;
	if( ask != ASK_YES )
		return STR_MENU_CANCEL;

	back_up_town_ptn();

	print_msg( FLG_MSG_WRN, MSG_RESET_FILE );

	return NULL;
}

/**/

char	*cb_menu_lang( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_cnf( *pp );

	if( get_flg_lang_ls_priority() )
		set_chk_on_menu( *pp, "list priority" );
	else
		set_chk_off_menu( *pp, "list priority" );

	return NULL;
}

/**/

char	*cb_menu_lang_ls( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls;
	long	i;
	long	k;

	*dflt = NULL;
	ls = ls_menu_lang_ls;
	k = 0;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN, "/lang" );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN, "/lang/title" );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_LANG_LS, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < LANG_KIND_MAX_N; i++ ){
		if( (i != 0) && (i % MENU_LANG_LS_N_PER_PAGE == 0) ){
			str_nz_cpy( ls[k].path, "/lang/page separator",
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

		if( i == get_lang_kind_next() )
			*dflt = &(ls[k]);

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/lang/%ld", (long)i );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A'
				+ (i % MENU_LANG_LS_N_PER_PAGE));
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, get_lang_kind_name( (lang_kind_t)i ),
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_lang_ls_sel;
		ls[k].arg = (void *)i;
		ls[k].flg = FLG_NULL;
		k++;
	}
	ls[k].path[0] = '\0';

	*pp = ls;

	return NULL;
}

/**/

char	*cb_menu_lang_ls_sel( menu_t **pp, menu_t **dflt )
{
	lang_kind_t	kind;

	kind = (lang_kind_t)(long)((*pp)->arg);

	set_lang_kind_next( kind );

	print_msg( FLG_NULL, MSG_SET_LANG, get_lang_kind_name( kind ) );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_lang_ls_priority( menu_t **pp, menu_t **dflt )
{
	set_flg_lang_ls_priority( !get_flg_lang_ls_priority() );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_window( menu_t **pp, menu_t **dflt )
{
	if( chk_redraw_every_turn() )
		set_chk_on_menu( *pp, "redraw every turn" );
	else
		set_chk_off_menu( *pp, "redraw every turn" );

	if( chk_msg_mul_line() )
		set_chk_on_menu( *pp, "multi message" );
	else
		set_chk_off_menu( *pp, "multi message" );

	return NULL;
}

/**/

char	*cb_menu_scroll_init( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;

	if( chk_flg( g_flg_scroll, FLG_SCROLL_CENTER ) ){
		p = srch_menu( *pp, "center" );
		set_menu_radio_item( *pp, p );
	} else if( chk_flg( g_flg_scroll, FLG_SCROLL_SMOOTH ) ){
		p = srch_menu( *pp, "smooth" );
		set_menu_radio_item( *pp, p );
	} else {
		p = srch_menu( *pp, "page" );
		set_menu_radio_item( *pp, p );
	}

	return NULL;
}

/**/

char	*cb_menu_scroll_page( menu_t **pp, menu_t **dflt )
{
	set_scroll_page();

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_scroll_smooth( menu_t **pp, menu_t **dflt )
{
	set_scroll_smooth();

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_scroll_center( menu_t **pp, menu_t **dflt )
{
	set_scroll_center();

	return STR_MENU_CANCEL;
}

/**/

void	set_scroll_page( void )
{
	g_flg_scroll &= ~(FLG_SCROLL_SMOOTH | FLG_SCROLL_CENTER);
}

/**/

void	set_scroll_smooth( void )
{
	g_flg_scroll &= ~(FLG_SCROLL_CENTER);
	g_flg_scroll |= FLG_SCROLL_SMOOTH;

}

/**/

void	set_scroll_center( void )
{
	g_flg_scroll &= ~(FLG_SCROLL_SMOOTH);
	g_flg_scroll |= FLG_SCROLL_CENTER;
}

/**/

char	*cb_menu_redraw_every_turn( menu_t **pp, menu_t **dflt )
{
	set_redraw_every_turn( !chk_redraw_every_turn() );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_mul_msg_line( menu_t **pp, menu_t **dflt )
{
	set_msg_mul_line( !chk_msg_mul_line() );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_stat_bar_init( menu_t **pp, menu_t **dflt )
{
	if( get_flg_stat_bar_hint_chr() )
		set_chk_on_menu( *pp, "hint chr" );
	else
		set_chk_off_menu( *pp, "hint chr" );

	if( get_flg_stat_bar_hint_obj() )
		set_chk_on_menu( *pp, "hint obj" );
	else
		set_chk_off_menu( *pp, "hint obj" );

	return NULL;
}

/**/

char	*cb_menu_stat_bar_hint_chr( menu_t **pp, menu_t **dflt )
{
	set_flg_stat_bar_hint_chr( !get_flg_stat_bar_hint_chr() );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_stat_bar_hint_obj( menu_t **pp, menu_t **dflt )
{
	set_flg_stat_bar_hint_obj( !get_flg_stat_bar_hint_obj() );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_screen_size_init( menu_t **pp, menu_t **dflt )
{
	if( chk_flg_screen_size_auto() )
		set_chk_on_menu( *pp, "auto" );
	else
		set_chk_off_menu( *pp, "auto" );

	if( chk_flg_resize_map() )
		set_chk_on_menu( *pp, "map" );
	else
		set_chk_off_menu( *pp, "map" );

	return NULL;
}

/**/

char	*cb_menu_screen_size_auto( menu_t **pp, menu_t **dflt )
{
	set_flg_screen_size_auto( !chk_flg_screen_size_auto() );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_screen_size_col( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = get_screen_size_col();

	ret = exec_menu_sel_num( &n,
			SCREEN_SIZE_MIN_COL,
			SCREEN_SIZE_MAX_COL );
	if( ret != NULL )
		return ret;

	set_screen_size_col( n );
	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_screen_size_row( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = get_screen_size_row();

	ret = exec_menu_sel_num( &n,
			SCREEN_SIZE_MIN_ROW,
			SCREEN_SIZE_MAX_ROW );
	if( ret != NULL )
		return ret;

	set_screen_size_row( n );
	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_screen_size_message( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = get_screen_size_message();

	ret = exec_menu_sel_num( &n,
			SCREEN_SIZE_MIN_ROW,
			SCREEN_SIZE_MAX_ROW );
	if( ret != NULL )
		return ret;

	set_screen_size_message( n );
	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_screen_size_map( menu_t **pp, menu_t **dflt )
{
	set_flg_resize_map( !chk_flg_resize_map() );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_vfx( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;

	p = srch_menu( *pp, "wait" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_MENU_VFX_WAIT, get_vfx_wait() );

	/* mbr */

	if( chk_flg( get_flg_vfx_mbr(), FLG_VFX_MBR_CURE ) )
		set_chk_on_menu( *pp, "member cure" );
	else
		set_chk_off_menu( *pp, "member cure" );

	if( chk_flg( get_flg_vfx_mbr(), FLG_VFX_MBR_DAM ) )
		set_chk_on_menu( *pp, "member dam" );
	else
		set_chk_off_menu( *pp, "member dam" );

	if( chk_flg( get_flg_vfx_mbr(), FLG_VFX_MBR_CRTCL ) )
		set_chk_on_menu( *pp, "member critical" );
	else
		set_chk_off_menu( *pp, "member critical" );

	if( chk_flg( get_flg_vfx_mbr(), FLG_VFX_MBR_ARW ) )
		set_chk_on_menu( *pp, "member arrow" );
	else
		set_chk_off_menu( *pp, "member arrow" );

	/* mnstr */

	if( chk_flg( get_flg_vfx_mnstr(), FLG_VFX_MNSTR_CURE ) )
		set_chk_on_menu( *pp, "monster cure" );
	else
		set_chk_off_menu( *pp, "monster cure" );

	if( chk_flg( get_flg_vfx_mnstr(), FLG_VFX_MNSTR_DAM ) )
		set_chk_on_menu( *pp, "monster dam" );
	else
		set_chk_off_menu( *pp, "monster dam" );

	if( chk_flg( get_flg_vfx_mnstr(), FLG_VFX_MNSTR_CRTCL ) )
		set_chk_on_menu( *pp, "monster critical" );
	else
		set_chk_off_menu( *pp, "monster critical" );

	if( chk_flg( get_flg_vfx_mnstr(), FLG_VFX_MNSTR_ARW ) )
		set_chk_on_menu( *pp, "monster arrow" );
	else
		set_chk_off_menu( *pp, "monster arrow" );

	return NULL;
}

/**/

char	*cb_menu_vfx_mbr( menu_t **pp, menu_t **dflt )
{
	flg_vfx_mbr_t	flg;

	flg = get_flg_vfx_mbr();
	flg ^= (flg_vfx_mbr_t)(long)((*pp)->arg);
	set_flg_vfx_mbr( flg );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_vfx_mnstr( menu_t **pp, menu_t **dflt )
{
	flg_vfx_mnstr_t	flg;

	flg = get_flg_vfx_mnstr();
	flg ^= (flg_vfx_mnstr_t)(long)((*pp)->arg);
	set_flg_vfx_mnstr( flg );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_vfx_wait( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = get_vfx_wait();

	ret = exec_menu_sel_num( &n, VFX_WAIT_MIN_N, VFX_WAIT_MAX_N );
	if( ret == NULL ){
		set_vfx_wait( (rate_t)n );
		sn_printf( (*pp)->msg, MENU_MSG_MAX_BYTE,
				MSG_MENU_VFX_WAIT, n );
		return STR_MENU_CANCEL;
	}

	return ret;
}

/**/

char	*cb_menu_vfx_measure_clk_tck( menu_t **pp, menu_t **dflt )
{
	measure_clk_tck();

	return NULL;
}

/**/

char	*cb_menu_color( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls;
	curs_attr_t	*attr;
	char	key;
	long	i, k;

	attr = get_curs_attr();
	ls = ls_menu_color;
	k = 0;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN, "/color" );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN, "/color/title" );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_COLOR, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	key = 'A';
	for( i = 0; i < CURS_ATTR_N_MAX_N; i++ ){
		curs_attr_n_t	n;
		bool_t	flg_page;
		unsigned long	flg_menu;

		n = (curs_attr_n_t)i;

		flg_page = FALSE;
		if( n == CURS_ATTR_N_MAP_CRSR )
			flg_page = TRUE;
		if( n == CURS_ATTR_N_MAP_ITEM )
			flg_page = TRUE;
		if( n == CURS_ATTR_N_MBR_1 )
			flg_page = TRUE;
		if( n == CURS_ATTR_N_FX_MBR_PLUS )
			flg_page = TRUE;
		if( n == CURS_ATTR_N_HEAT )
			flg_page = TRUE;
		if( flg_page ){
			str_nz_cpy( ls[k].path, "/color/page separator",
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

		flg_menu = FLG_NULL;
		if( n == CURS_ATTR_N_MAP_ITEM )
			flg_menu = FLG_MENU_HIDDEN;
		if( n == CURS_ATTR_N_MENU_DIS )
			flg_menu = FLG_MENU_HIDDEN;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/color/%ld", (long)i );
		str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, MSG( attr[i].name_n ),
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_color_sel;
		ls[k].arg = (void *)&(attr[i]);
		ls[k].flg = flg_menu;
		k++;
		key++;
	}
	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_color_sel( menu_t **pp, menu_t **dflt )
{
	g_sel_attr = (curs_attr_t *)((*pp)->arg);

	*pp = ls_menu_color_sel;
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_fg_init( menu_t **pp, menu_t **dflt )
{
	menu_color_init( pp, dflt, g_sel_attr->fg );

	return NULL;
}

/**/

char	*cb_menu_bg_init( menu_t **pp, menu_t **dflt )
{
	menu_color_init( pp, dflt, g_sel_attr->bg );

	return NULL;
}

/**/

void	menu_color_init( menu_t **pp, menu_t **dflt, int color )
{
	menu_t	*p;

	p = NULL;

	switch( color ){
	case COLOR_BLACK:
		p = srch_menu( *pp, "black" );
		break;
	case COLOR_RED:
		p = srch_menu( *pp, "red" );
		break;
	case COLOR_GREEN:
		p = srch_menu( *pp, "green" );
		break;
	case COLOR_YELLOW:
		p = srch_menu( *pp, "yellow" );
		break;
	case COLOR_BLUE:
		p = srch_menu( *pp, "blue" );
		break;
	case COLOR_MAGENTA:
		p = srch_menu( *pp, "magenta" );
		break;
	case COLOR_CYAN:
		p = srch_menu( *pp, "cyan" );
		break;
	case COLOR_WHITE:
		p = srch_menu( *pp, "white" );
		break;
	}

	*dflt = p;
}

/**/

char	*cb_menu_fg( menu_t **pp, menu_t **dflt )
{
	set_fg_color( g_sel_attr, (int)((*pp)->arg) );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_bg( menu_t **pp, menu_t **dflt )
{
	set_bg_color( g_sel_attr, (int)((*pp)->arg) );

	return STR_MENU_CANCEL;
}

/**/

void	set_fg_color( curs_attr_t *attr, int color )
{
	if( attr == NULL )
		return;

	if( color == attr->bg )
		attr->bg = attr->fg;

	attr->fg = color;
	init_curs_color_pair( attr, attr->color_pair_n );

	return;
}

/**/

void	set_bg_color( curs_attr_t *attr, int color )
{
	if( attr == NULL )
		return;

	if( color == attr->fg )
		attr->fg = attr->bg;

	attr->bg = color;
	init_curs_color_pair( attr, attr->color_pair_n );

	return;
}

/**/

char	*cb_menu_attr_init( menu_t **pp, menu_t **dflt )
{
	if( chk_flg( g_sel_attr->attr, A_UNDERLINE ) )
		set_chk_on_menu( *pp, "underline" );
	else
		set_chk_off_menu( *pp, "underline" );

	if( chk_flg( g_sel_attr->attr, A_REVERSE ) )
		set_chk_on_menu( *pp, "reverse" );
	else
		set_chk_off_menu( *pp, "reverse" );

	if( chk_flg( g_sel_attr->attr, A_BLINK ) )
		set_chk_on_menu( *pp, "blink" );
	else
		set_chk_off_menu( *pp, "blink" );

	if( chk_flg( g_sel_attr->attr, A_BOLD ) )
		set_chk_on_menu( *pp, "bold" );
	else
		set_chk_off_menu( *pp, "bold" );

	return NULL;
}

/**/

char	*cb_menu_attr( menu_t **pp, menu_t **dflt )
{
	rev_color_attr( g_sel_attr, (chtype_t)((*pp)->arg) );

	return STR_MENU_CANCEL;
}

/**/

void	set_color_attr( curs_attr_t *attr, bool_t flg_on, chtype_t ch )
{
	if( attr == NULL )
		return;

	if( flg_on )
		attr->attr |= ch;
	else
		attr->attr &= ~ch;
}

/**/

void	rev_color_attr( curs_attr_t *attr, chtype_t ch )
{
	if( attr == NULL )
		return;

	attr->attr ^= ch;
}

/**/

char	*cb_menu_crsr_ptn( menu_t **pp, menu_t **dflt )
{
	bool_t	flg_main;
	menu_t	*ls;
	long	k;
	long	i, n, max_n;
	char	key;

	*dflt = NULL;

	flg_main = (bool_t)(long)((*pp)->arg);

	ls = ls_menu_crsr_ptn;
	k = 0;
	key = 'A';
	if( flg_main )
		n = get_main_crsr_ptn_n();
	else
		n = get_sub_crsr_ptn_n();
	max_n = get_crsr_ptn_max_n();

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN, "/cursor" );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN, "/cursor/title" );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_CRSR_PTN, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	for( i = 0; i < max_n; i++ ){
		if( (i != 0) && (i % CRSR_PTN_MAX_N == 0) ){
			str_nz_cpy( ls[k].path, "/cursor/page separator",
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

		if( i == n )
			*dflt = &(ls[k]);

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/cursor/%ld", (long)(i + 1) );
		str_nz_cpy( ls[k].kind, "<RadioItem>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		sn_printf( ls[k].msg, MENU_PATH_MAX_LEN,
				"%ld", (long)(i + 1) );
		if( flg_main )
			ls[k].call_back = cb_menu_main_crsr_ptn_sel;
		else
			ls[k].call_back = cb_menu_sub_crsr_ptn_sel;
		ls[k].arg = (void *)i;
		ls[k].flg = FLG_NULL;
		k++;

		key++;
	}
	ls[k].path[0] = '\0';

	*pp = ls;
	set_menu_radio_item( *pp, *dflt );

	return NULL;
}

/**/

char	*cb_menu_main_crsr_ptn_sel( menu_t **pp, menu_t **dflt )
{
	set_main_crsr_ptn_n( (long)((*pp)->arg) );
	reset_crsr_ptn();

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_sub_crsr_ptn_sel( menu_t **pp, menu_t **dflt )
{
	set_sub_crsr_ptn_n( (long)((*pp)->arg) );
	reset_crsr_ptn();

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_demo( menu_t **pp, menu_t **dflt )
{
	if( g_flg_skip_demo_cut_in )
		set_chk_on_menu( *pp, "cut in" );
	else
		set_chk_off_menu( *pp, "cut in" );

	return NULL;
}

/**/

char	*cb_menu_skip_cut_in( menu_t **pp, menu_t **dflt )
{
	g_flg_skip_demo_cut_in = !g_flg_skip_demo_cut_in;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_star_cui( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = g_cui_star_n;

	ret = exec_menu_sel_num( &n, 0, 1000 * 1000 );
	if( ret == NULL ){
		g_cui_star_n = n;

		return STR_MENU_CANCEL;
	}

	return ret;
}

/**/

char	*cb_menu_star_gui( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = g_gui_star_n;

	ret = exec_menu_sel_num( &n, 0, 1000 * 1000 );
	if( ret == NULL ){
		g_gui_star_n = n;

		return STR_MENU_CANCEL;
	}

	return ret;
}

/**/

char	*cb_menu_key_init( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_cnf( *pp );

	if( g_flg_echo_key )
		set_chk_on_menu( *pp, "echo key" );
	else
		set_chk_off_menu( *pp, "echo key" );

	return NULL;
}

/**/

char	*cb_menu_clr_key_buf_init( menu_t **pp, menu_t **dflt )
{
	if( g_flg_clr_key_buf )
		set_chk_on_menu( *pp, "every" );
	else
		set_chk_off_menu( *pp, "every" );

	if( g_flg_clr_key_buf_menu )
		set_chk_on_menu( *pp, "menu" );
	else
		set_chk_off_menu( *pp, "menu" );

	return NULL;
}

/**/

char	*cb_menu_clr_key_buf_every( menu_t **pp, menu_t **dflt )
{
	g_flg_clr_key_buf = !g_flg_clr_key_buf;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_clr_key_buf_menu( menu_t **pp, menu_t **dflt )
{
	g_flg_clr_key_buf_menu = !g_flg_clr_key_buf_menu;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_echo_key( menu_t **pp, menu_t **dflt )
{
	g_flg_echo_key = !g_flg_echo_key;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_set_key( menu_t **pp, menu_t **dflt )
{
	char	*msg_key = MSG_GETS_SET_KEY_KEY;
	static char	msg_cmd[WIN_MSG_DRAW_WIDTH + 1];
	static char	buf_key[MACRO_MAX_LEN + 1] = "";
	static char	buf_cmd[MACRO_MAX_LEN + 1];
	char	*prev_cmd;
	long	len;
	long	x, y;

	/* key */

	print_msg( FLG_NULL, msg_key );

	x = str_len_draw( msg_key );
	y = get_screen_row() - 1;
	if( !game_gets( x, y, msg_key, buf_key, MACRO_MAX_LEN, FALSE ) )
		return STR_MENU_CANCEL;

	len = str_len_std( buf_key );
	if( len >= 1 )
		if( buf_key[len - 1] == '\n' )
			buf_key[len - 1] = '\0';

	if( buf_key[0] == '\0' )
		return STR_MENU_CANCEL;

	/* command */

	prev_cmd = get_key_tab_cmd( buf_key );
	if( prev_cmd == NULL ){
		print_msg( FLG_NULL, MSG_GETS_SET_KEY_PREV, MSG_NULL );
		str_nz_cpy( buf_cmd, "", MACRO_MAX_LEN );
	} else {
		print_msg( FLG_NULL, MSG_GETS_SET_KEY_PREV, prev_cmd );
		str_nz_cpy( buf_cmd, prev_cmd, MACRO_MAX_LEN );
	}

	sn_printf( msg_cmd, WIN_MSG_DRAW_WIDTH,
			MSG_GETS_SET_KEY_CMD, MACRO_MAX_LEN );
	print_msg( FLG_NULL, msg_cmd );

	x = str_len_draw( msg_cmd );
	y = get_screen_row() - 1;
	if( !game_gets( x, y, msg_cmd, buf_cmd, MACRO_MAX_LEN, FALSE ) )
		return STR_MENU_CANCEL;

	len = str_len_std( buf_cmd );
	if( len >= 1 )
		if( buf_cmd[len - 1] == '\n' )
			buf_cmd[len - 1] = '\0';

	if( buf_cmd[0] == '\0' )
		return STR_MENU_CANCEL;

	/**/

	set_key_tab( buf_key, buf_cmd );

	print_msg( FLG_NULL, MSG_MENU_SET_KEY_DONE, buf_key, buf_cmd );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_set_key_reg_macro( menu_t **pp, menu_t **dflt )
{
	char	*msg_key = MSG_GETS_SET_KEY_KEY;
	static char	buf_key[MACRO_MAX_LEN + 1];
	char	*cmd;
	long	x, y;
	long	len;

	/* key */

	print_msg( FLG_NULL, msg_key );

	x = str_len_draw( msg_key );
	y = get_screen_row() - 1;
	if( !game_gets( x, y, msg_key, buf_key, MACRO_MAX_LEN, FALSE ) )
		return STR_MENU_CANCEL;

	len = str_len_std( buf_key );
	if( len >= 1 )
		if( buf_key[len - 1] == '\n' )
			buf_key[len - 1] = '\0';

	if( buf_key[0] == '\0' )
		return STR_MENU_CANCEL;

	/* command */

	cmd = get_reg_macro();
	if( cmd == NULL )
		return STR_MENU_CANCEL;

	/**/

	set_key_tab( buf_key, cmd );

	print_msg( FLG_NULL, MSG_MENU_SET_KEY_DONE, buf_key, cmd );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_unset_key( menu_t **pp, menu_t **dflt )
{
	char	*msg_key = MSG_GETS_UNSET_KEY_KEY;
	static char	buf_key[MACRO_MAX_LEN + 1];
	long	x, y;
	long	len;

	/* key */

	print_msg( FLG_NULL, msg_key );

	x = str_len_draw( msg_key );
	y = get_screen_row() - 1;
	if( !game_gets( x, y, msg_key, buf_key, MACRO_MAX_LEN, FALSE ) )
		return STR_MENU_CANCEL;

	len = str_len_std( buf_key );
	if( len >= 1 )
		if( buf_key[len - 1] == '\n' )
			buf_key[len - 1] = '\0';

	if( buf_key[0] == '\0' )
		return STR_MENU_CANCEL;

	/**/

	set_key_tab( buf_key, NULL );

	print_msg( FLG_MSG_DEBUG, "unset key '%s'", buf_key );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_func( menu_t **pp, menu_t **dflt )
{
	*pp = get_ls_menu_macro_func();
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_mouse( menu_t **pp, menu_t **dflt )
{
	*pp = get_ls_menu_macro_mouse();
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_func_exec( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*str;
	char	str_ret_m[4 + 1];
	char	str_ret_j[4 + 1];

	str_ret_m[0] = 'M' - '@';
	str_ret_m[1] = '\0';
	str_ret_j[0] = 'J' - '@';
	str_ret_j[1] = '\0';

	n = (long)((*pp)->arg);
	str = get_macro_str( n );

	/* メニューの実行中は特定のキーのみ有効 */

	do {
		if( get_flg_chk_menu() )
			break;

		if( strcmp( str, "\n" ) == 0 )
			break;
		if( strcmp( str, "\r" ) == 0 )
			break;
		if( strcmp( str, "^M" ) == 0 )
			break;
		if( strcmp( str, "^J" ) == 0 )
			break;
		if( strcmp( str, str_ret_m ) == 0 )
			break;
		if( strcmp( str, str_ret_j ) == 0 )
			break;

		if( strcmp( str, "\033" ) == 0 )
			break;
		if( strcmp( str, "^[" ) == 0 )
			break;
		if( strcmp( str, "0" ) == 0 )
			break;
		if( strcmp( str, "." ) == 0 ){
			str = "0";
			break;
		}

		return NULL;
	} while( 0 );

	set_key_buf_str_head( str );

	return NULL;
}

/**/

char	*cb_menu_func_edit( menu_t **pp, menu_t **dflt )
{
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;
	static char	msg[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	static char	buf[MACRO_MAX_LEN + 1];
	const char	*fmt;
	long	n, draw_n;
	long	x, y;
	long	len;

	n = (long)((*pp)->arg);
	draw_n = get_func_draw_n( n );

	/* 現在のコマンドを表示 */

	if( n >= KEY_N_JOYSTICK_HEAD_N )
		fmt = MSG_GETS_JOYSTICK_PREV;
	else if( n >= KEY_N_MOUSE_HEAD_N )
		fmt = MSG_GETS_MOUSE_PREV;
	else
		fmt = MSG_GETS_FUNC_PREV;
	print_msg( FLG_NULL, fmt, get_macro_str( n ) );

	/* コマンド入力を表示 */

	if( n >= KEY_N_JOYSTICK_HEAD_N )
		fmt = MSG_GETS_JOYSTICK_EDIT;
	else if( n >= KEY_N_MOUSE_HEAD_N )
		fmt = MSG_GETS_MOUSE_EDIT;
	else
		fmt = MSG_GETS_FUNC_EDIT;
	sn_printf( msg, max_len, fmt, MACRO_MAX_LEN );
	print_msg( FLG_NULL, MSG_S, msg );

	/* 1 行入力 */

	str_nz_cpy( buf, get_macro_str( n ), MACRO_MAX_LEN );

	x = str_len_draw( msg );
	y = get_screen_row() - 1;
	if( !game_gets( x, y, msg, buf, MACRO_MAX_LEN, FALSE ) )
		return STR_MENU_CANCEL;

	len = str_len_std( buf );
	if( len >= 1 )
		if( buf[len - 1] == '\n' )
			buf[len - 1] = '\0';
	if( buf[0] == '\0' )
		return STR_MENU_CANCEL;

	/* 上書き */

	str_nz_cpy( get_macro_str( n ), buf, MACRO_MAX_LEN );

	/* 上書きを表示 */

	if( n >= KEY_N_JOYSTICK_HEAD_N )
		fmt = MSG_MENU_JOYSTICK_KEY_DONE;
	else if( n >= KEY_N_MOUSE_HEAD_N )
		fmt = MSG_MENU_MOUSE_KEY_DONE;
	else
		fmt = MSG_MENU_FUNC_KEY_DONE;
	print_msg( FLG_NULL, fmt, draw_n, get_macro_str( n ) );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_func_set_reg_macro( menu_t **pp, menu_t **dflt )
{
	static char	msg[WIN_MSG_DRAW_WIDTH + 1];
	const char	*fmt;
	long	n, draw_n;
	char	*cmd;
	ask_t	ask;

	n = (long)((*pp)->arg);
	draw_n = get_func_draw_n( n );

	/* 現在のコマンドを表示 */

	if( n >= KEY_N_JOYSTICK_HEAD_N )
		fmt = MSG_GETS_JOYSTICK_PREV;
	else if( n >= KEY_N_MOUSE_HEAD_N )
		fmt = MSG_GETS_MOUSE_PREV;
	else
		fmt = MSG_GETS_FUNC_PREV;
	print_msg( FLG_NULL, fmt, get_macro_str( n ) );

	/* 上書きを確認 */

	if( n >= KEY_N_JOYSTICK_HEAD_N )
		fmt = MSG_TTL_MENU_JOYSTICK_SET_REG_MACRO;
	else if( n >= KEY_N_MOUSE_HEAD_N )
		fmt = MSG_TTL_MENU_MOUSE_SET_REG_MACRO;
	else
		fmt = MSG_TTL_MENU_FUNC_SET_REG_MACRO;
	sn_printf( msg, WIN_MSG_DRAW_WIDTH, fmt, draw_n );

	ask = exec_menu_ask( msg, ASK_NO, TRUE );
	if( ask == ASK_ERR )
		return STR_MENU_ERR;
	if( ask != ASK_YES )
		return STR_MENU_CANCEL;

	cmd = get_reg_macro();
	if( cmd == NULL )
		return STR_MENU_CANCEL;

	/* 上書き */

	str_nz_cpy( get_macro_str( n ), cmd, MACRO_MAX_LEN );

	/* 上書きを表示 */

	if( n >= KEY_N_JOYSTICK_HEAD_N )
		fmt = MSG_MENU_JOYSTICK_KEY_DONE;
	else if( n >= KEY_N_MOUSE_HEAD_N )
		fmt = MSG_MENU_MOUSE_KEY_DONE;
	else
		fmt = MSG_MENU_FUNC_KEY_DONE;
	print_msg( FLG_NULL, fmt, draw_n, get_macro_str( n ) );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_func_unset( menu_t **pp, menu_t **dflt )
{
	long	n, draw_n;
	const char	*fmt;
	ask_t	ask;

	n = (long)((*pp)->arg);
	draw_n = get_func_draw_n( n );

	/* 現在のコマンドを表示 */

	if( n >= KEY_N_JOYSTICK_HEAD_N )
		fmt = MSG_GETS_JOYSTICK_PREV;
	else if( n >= KEY_N_MOUSE_HEAD_N )
		fmt = MSG_GETS_MOUSE_PREV;
	else
		fmt = MSG_GETS_FUNC_PREV;
	print_msg( FLG_NULL, fmt, get_macro_str( n ) );

	/* ユーザに確認 */

	if( n >= KEY_N_JOYSTICK_HEAD_N )
		fmt = MSG_MENU_JOYSTICK_UNSET_ASK;
	else if( n >= KEY_N_MOUSE_HEAD_N )
		fmt = MSG_MENU_MOUSE_UNSET_ASK;
	else
		fmt = MSG_MENU_FUNC_UNSET_ASK;

	ask = exec_menu_ask( fmt, ASK_NO, TRUE );

	if( ask == ASK_ERR )
		return STR_MENU_ERR;
	if( ask != ASK_YES )
		return STR_MENU_CANCEL;

	/* 解除 */

	str_nz_cpy( get_macro_str( n ), "", MACRO_MAX_LEN );

	/* 解除を表示 */

	if( n >= KEY_N_JOYSTICK_HEAD_N )
		fmt = MSG_MENU_JOYSTICK_UNSET_DONE;
	else if( n >= KEY_N_MOUSE_HEAD_N )
		fmt = MSG_MENU_MOUSE_UNSET_DONE;
	else
		fmt = MSG_MENU_FUNC_UNSET_DONE;
	print_msg( FLG_NULL, fmt, draw_n );

	return STR_MENU_CANCEL;
}

/**/

long	get_func_draw_n( long n )
{
	if( n < 0 )
		return 0;

	if( n < KEY_N_FUNC_MAX_N )
		return n + 1;
	n -= KEY_N_FUNC_MAX_N;

	if( n < KEY_N_MOUSE_CLICK_MAX_N )
		return n + 1;
	n -= KEY_N_MOUSE_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_D_CLICK_MAX_N )
		return n + 1;
	n -= KEY_N_MOUSE_D_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_P_CLICK_MAX_N )
		return n + 1;
	n -= KEY_N_MOUSE_P_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_PRESS_MAX_N )
		return n + 1;
	n -= KEY_N_MOUSE_PRESS_MAX_N;

	if( n < KEY_N_MOUSE_RELEASE_MAX_N )
		return n + 1;
	n -= KEY_N_MOUSE_RELEASE_MAX_N;

	if( n < KEY_N_MOUSE_MOTION_MAX_N )
		return n + 1;
	n -= KEY_N_MOUSE_MOTION_MAX_N;

	if( n < KEY_N_JOYSTICK_MAX_N )
		return n + 1;
	n -= KEY_N_JOYSTICK_MAX_N;

	return 0;
}

/**/

char	*cb_menu_mouse_init( menu_t **pp, menu_t **dflt )
{
	if( get_flg_move_crsr_dflt() )
		set_chk_on_menu( *pp, "move cursor to default" );
	else
		set_chk_off_menu( *pp, "move cursor to default" );

	return NULL;
}

/**/

char	*cb_menu_mouse_move_crsr_dflt( menu_t **pp, menu_t **dflt )
{
	set_flg_move_crsr_dflt( !get_flg_move_crsr_dflt() );

	return STR_MENU_CANCEL;
}

/**/

long	get_cui_mouse_double_click_msec( void )
{
	return g_cui_mouse_double_click_msec;
}

/**/

void	set_cui_mouse_double_click_msec( long msec )
{
	g_cui_mouse_double_click_msec = msec;
}

/**/

char	*cb_menu_mouse_double_click( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = get_cui_mouse_double_click_msec();

	ret = exec_menu_sel_num( &n, 100, 5000 );
	if( ret == NULL ){
		set_cui_mouse_double_click_msec( n );

		return STR_MENU_CANCEL;
	}

	return ret;
}

/**/

char	*cb_menu_audio( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;

	p = srch_menu( *pp, "music volume" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_MENU_MUSIC_VOLUME, g_music_volume_rate );

	p = srch_menu( *pp, "sound volume" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_MENU_SOUND_VOLUME, g_sound_volume_rate );

	if( g_flg_mute_audio )
		set_chk_on_menu( *pp, "mute" );
	else
		set_chk_off_menu( *pp, "mute" );

	return NULL;
}

/**/

char	*cb_menu_music_volume( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = g_music_volume_rate;

	ret = exec_menu_sel_num( &n, 0, _100_PERCENT );
	if( ret == NULL ){
		g_music_volume_rate = n;
		call_game_music_set_volume( g_music_volume_rate );

		return "/misc/config/gui/sound";
	}

	return ret;
}

/**/

char	*cb_menu_sound_volume( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = g_sound_volume_rate;

	ret = exec_menu_sel_num( &n, 0, _100_PERCENT );
	if( ret == NULL ){
		g_sound_volume_rate = n;
		call_game_sound_set_volume( g_sound_volume_rate );

		return "/misc/config/gui/sound";
	}

	return ret;
}

/**/

rate_t	get_music_volume_rate( void )
{
	return g_music_volume_rate;
}

/**/

rate_t	set_music_volume_rate( rate_t rate )
{
	if( rate < 0 )
		rate = 0;
	if( rate > _100_PERCENT )
		rate = _100_PERCENT;

	g_music_volume_rate = rate;

	return g_music_volume_rate;
}

/**/

rate_t	get_sound_volume_rate( void )
{
	return g_sound_volume_rate;
}

/**/

rate_t	set_sound_volume_rate( rate_t rate )
{
	if( rate < 0 )
		rate = 0;
	if( rate > _100_PERCENT )
		rate = _100_PERCENT;

	g_sound_volume_rate = rate;

	return g_sound_volume_rate;
}

/**/

char	*cb_menu_mute_audio( menu_t **pp, menu_t **dflt )
{
	mute_audio( !g_flg_mute_audio );

	return NULL;
}

void	mute_audio( bool_t flg )
{
	if( flg ){
		g_flg_mute_audio = TRUE;
		call_game_music_set_volume( 0 );
		call_game_sound_set_volume( 0 );
	} else {
		g_flg_mute_audio = FALSE;
		call_game_music_set_volume( g_music_volume_rate );
		call_game_sound_set_volume( g_sound_volume_rate );
	}
}

/**/

char	*cb_menu_replay_music( menu_t **pp, menu_t **dflt )
{
	call_game_music_replay();

	return NULL;
}

/**/

char	*cb_menu_set_audio_buf_siz( menu_t **pp, menu_t **dflt )
{
	long	n;
	char	*ret;

	n = g_audio_buf_siz;

	ret = exec_menu_sel_num( &n, 128, 0x7fff );
	if( ret == NULL ){
		g_audio_buf_siz = n;
		print_msg( FLG_NULL, MSG_MENU_CNF_PLZ_RELOAD );

		return "/misc/config/gui/sound";
	}

	return ret;
}

/**/

char	*cb_menu_joystick_sel_n_init( menu_t **pp, menu_t **dflt )
{
	long	joy_n;
	const char	*name;
	menu_t	*ls;
	long	i, k;
	char	key;

	joy_n = call_game_joystick_get_joy();

	ls = ls_menu_joystick_sel_n;
	k = 0;
	key = 'A';

	str_nz_cpy( ls[k].path, "/select joystick",
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

	for( i = 0; i < JOYSTICK_SEL_N_MAX_N; i++ ){
		name = call_game_joystick_get_name( i );
		if( name == NULL ){
			if( i < 1 ){
				print_msg( FLG_MSG_WRN,
						MSG_ERR_MENU_SEL_JOYSTICK );
				return STR_MENU_CANCEL;
			}
			break;
		}

		if( (i != 0) && ((i % USER_MENU_MAX_N_PER_PAGE) == 0) ){
			str_nz_cpy( ls[k].path,
					"/select joystick/page sep",
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

		if( (i % USER_MENU_MAX_N_PER_PAGE) == 0 ){
			str_nz_cpy( ls[k].path, "/select joystick/--",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[k].kind, "<Title>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = '\0';
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_NULL;
			str_nz_cpy( ls[k].msg, MSG_MENU_JOYSTICK_SEL_N,
					MENU_MSG_MAX_BYTE );
			ls[k].call_back = NULL;
			ls[k].arg = NULL;
			ls[k].flg = FLG_NULL;
			k++;
		}

		if( (i == 0) || (i == joy_n) )
			*dflt = &(ls[k]);

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/select joystick/%ld", (long)i );
		str_nz_cpy( ls[k].kind, "<RadioItem>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, name, MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_joystick_sel_n;
		ls[k].arg = (void *)i;
		ls[k].flg = FLG_NULL;
		k++;
		key++;
	}
	ls[k].path[0] = '\0';

	*pp = ls;

	set_menu_radio_item( *pp, *dflt );

	return NULL;
}

/**/

char	*cb_menu_joystick_sel_kind_init( menu_t **pp, menu_t **dflt )
{
	menu_t	*p;

	p = srch_menu( *pp, "ps" );

	switch( (joy_kind_t)call_game_joystick_get_kind() ){
	case JOY_KIND_NULL:
	case JOY_KIND_PS:
	case JOY_KIND_MAX_N:
		p = srch_menu( *pp, "ps" );
		break;
	case JOY_KIND_SATURN:
		p = srch_menu( *pp, "saturn" );
		break;
	case JOY_KIND_RAP3:
		p = srch_menu( *pp, "rap3" );
		break;
	}

	set_menu_radio_item( *pp, p );

	return NULL;
}

/**/

char	*cb_menu_joystick_macro_init( menu_t **pp, menu_t **dflt )
{
	*pp = get_ls_menu_macro_joystick();
	*dflt = NULL;

	return NULL;
}

/**/

char	*cb_menu_joystick_sel_n( menu_t **pp, menu_t **dflt )
{
	long	n;

	n = (long)((*pp)->arg);
	call_game_joystick_sel_joy( n );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_joystick_sel_kind( menu_t **pp, menu_t **dflt )
{
	joy_kind_t	kind;

	kind = (joy_kind_t)(long)((*pp)->arg);
	call_game_joystick_set_kind( kind );

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_user( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls;
	long	i, k;
	char	key;

	set_menu_dflt_cnf( *pp );

	ls = ls_menu_user;
	k = 0;
	key = 'A';

	str_nz_cpy( ls[k].path, "/user menu",
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

	for( i = 0; i < g_user_menu_n; i++ ){
		if( (i != 0) && ((i % USER_MENU_MAX_N_PER_PAGE) == 0) ){
			str_nz_cpy( ls[k].path, "/user menu/page separator",
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

		if( (i % USER_MENU_MAX_N_PER_PAGE) == 0 ){
			str_nz_cpy( ls[k].path, "/user menu/--",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[k].kind, "<Title>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = '\0';
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_NULL;
			str_nz_cpy( ls[k].msg, MSG_MENU_USER,
					MENU_MSG_MAX_BYTE );
			ls[k].call_back = NULL;
			ls[k].arg = NULL;
			ls[k].flg = FLG_NULL;
			k++;
		}

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/user menu/%ld", (long)i );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, g_user_menu_name[i], MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_user_sel;
		ls[k].arg = g_user_menu_cmd[i];
		ls[k].flg = FLG_NULL;
		k++;
		key++;
	}

	str_nz_cpy( ls[k].path, "/user menu/new",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<OpenWinItem>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'T';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_USER_NEW, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_user_new;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/user menu/new reg macro",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<OpenWinItem>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'U';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_USER_NEW_REG_MACRO,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_user_new_reg_macro;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/user menu/arrange up",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'V';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_USER_ARRANGE_UP, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_user_arrange_up;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/user menu/arrange down",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'W';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_USER_ARRANGE_DOWN, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_user_arrange_down;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/user menu/arrange top",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'X';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_USER_ARRANGE_TOP, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_user_arrange_top;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/user menu/arrange bottom",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'Y';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_USER_ARRANGE_BOTTOM, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_user_arrange_bottom;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/user menu/remove",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'Z';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, MSG_MENU_USER_REMOVE, MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_user_remove;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/**/

void	clr_user_menu( void )
{
	g_user_menu_n = 0;
}

/**/

void	add_user_menu( char *name, char *cmd )
{
	if( name == NULL )
		return;
	if( cmd == NULL )
		return;

	str_nz_cpy( g_user_menu_name[g_user_menu_n], name, MENU_MSG_MAX_BYTE );
	str_nz_cpy( g_user_menu_cmd[g_user_menu_n], cmd, MACRO_MAX_LEN );

	g_user_menu_n++;
}

/**/

char	*get_user_menu_name( long n )
{
	if( n < 0 )
		return NULL;
	if( n >= g_user_menu_n )
		return NULL;

	return g_user_menu_name[n];
}

/**/

char	*get_user_menu_cmd( long n )
{
	if( n < 0 )
		return NULL;
	if( n >= g_user_menu_n )
		return NULL;

	return g_user_menu_cmd[n];
}

/**/

char	*cb_menu_user_sel( menu_t **pp, menu_t **dflt )
{
	char	*cmd;

	cmd = (char *)((*pp)->arg);
	set_key_buf_str_head( cmd );

	return NULL;
}

/**/

char	*cb_menu_user_new( menu_t **pp, menu_t **dflt )
{
	return menu_user_new_sub( pp, dflt, FALSE );
}

/**/

char	*cb_menu_user_new_reg_macro( menu_t **pp, menu_t **dflt )
{
	return menu_user_new_sub( pp, dflt, TRUE );
}

/**/

char	*menu_user_new_sub(
	menu_t **pp, menu_t **dflt, bool_t flg_reg_macro
)
{
	const char	*msg_name = MSG_GETS_USER_MENU_NAME;
	static char	msg_cmd[WIN_MSG_DRAW_WIDTH + 1];
	static char	buf_name[MENU_MSG_MAX_BYTE + 1];
	static char	buf_cmd[MACRO_MAX_LEN + 1];
	long	x, y;
	long	len;

	/* name */

	print_msg( FLG_NULL, msg_name );

	x = str_len_draw( msg_name );
	y = get_screen_row() - 1;
	if( !game_gets( x, y, msg_name, buf_name,
			MENU_MSG_MAX_LEN, TRUE ) ){
		return STR_MENU_CANCEL;
	}

	len = str_len_std( buf_name );
	if( len >= 1 )
		if( buf_name[len - 1] == '\n' )
			buf_name[len - 1] = '\0';

	if( buf_name[0] == '\0' )
		return STR_MENU_CANCEL;

	/* command */

	if( flg_reg_macro ){
		char	*macro = get_reg_macro();

		if( macro == NULL )
			return STR_MENU_CANCEL;

		str_nz_cpy( buf_cmd, macro, MACRO_MAX_LEN );
	} else {
		long	len;

		sn_printf( msg_cmd, WIN_MSG_DRAW_WIDTH,
				MSG_GETS_USER_MENU_CMD, MACRO_MAX_LEN );
		print_msg( FLG_NULL, MSG_S, msg_cmd );

		x = str_len_draw( msg_cmd );
		y = get_screen_row() - 1;
		if( !game_gets( x, y, msg_cmd,
				buf_cmd, MACRO_MAX_LEN, FALSE ) ){
			return STR_MENU_CANCEL;
		}

		len = str_len_std( buf_cmd );
		if( len >= 1 )
			if( buf_cmd[len - 1] == '\n' )
				buf_cmd[len - 1] = '\0';

		if( buf_cmd[0] == '\0' )
			return STR_MENU_CANCEL;
	}

	/**/

	add_user_menu( buf_name, buf_cmd );

	print_msg( FLG_NULL, MSG_MENU_USER_NEW_DONE_1, buf_name );
	print_msg( FLG_NULL, MSG_MENU_USER_NEW_DONE_2, buf_cmd );

	return "/misc/config/user menu select";
}

/**/

char	*cb_menu_user_arrange_up( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls = ls_menu_user_edit;

	set_edit_user_menu( ls, cb_menu_user_arrange_up_sel,
			MSG_MENU_USER_ARRANGE_UP );

	exec_menu( ls, NULL, NULL );

	return "/misc/config/user menu select";
}

/**/

char	*cb_menu_user_arrange_down( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls = ls_menu_user_edit;

	set_edit_user_menu( ls, cb_menu_user_arrange_down_sel,
			MSG_MENU_USER_ARRANGE_DOWN );

	exec_menu( ls, NULL, NULL );

	return "/misc/config/user menu select";
}

/**/

char	*cb_menu_user_arrange_top( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls = ls_menu_user_edit;

	set_edit_user_menu( ls, cb_menu_user_arrange_top_sel,
			MSG_MENU_USER_ARRANGE_TOP );

	exec_menu( ls, NULL, NULL );

	return "/misc/config/user menu select";
}

/**/

char	*cb_menu_user_arrange_bottom( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls = ls_menu_user_edit;

	set_edit_user_menu( ls, cb_menu_user_arrange_bottom_sel,
			MSG_MENU_USER_ARRANGE_BOTTOM );

	exec_menu( ls, NULL, NULL );

	return "/misc/config/user menu select";
}

/**/

char	*cb_menu_user_remove( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls = ls_menu_user_edit;

	set_edit_user_menu( ls, cb_menu_user_remove_sel,
			MSG_MENU_USER_REMOVE );

	exec_menu( ls, NULL, NULL );

	return "/misc/config/user menu select";
}

/**/

void	set_edit_user_menu( menu_t *ls, menu_call_back_t func, char *ttl )
{
	long	i, k;
	char	key;

	k = 0;
	key = 'A';

	str_nz_cpy( ls[k].path, "/user menu edit",
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

	for( i = 0; i < g_user_menu_n; i++ ){
		if( (i != 0) && ((i % USER_MENU_MAX_N_PER_PAGE) == 0) ){
			str_nz_cpy( ls[k].path,
					"/user menu edit/page separator",
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

		if( (i % USER_MENU_MAX_N_PER_PAGE) == 0 ){
			str_nz_cpy( ls[k].path, "/user menu edit/--",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[k].kind, "<Title>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = '\0';
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_NULL;
			str_nz_cpy( ls[k].msg, ttl, MENU_MSG_MAX_BYTE );
			ls[k].call_back = NULL;
			ls[k].arg = NULL;
			ls[k].flg = FLG_NULL;
			k++;
		}

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/user menu edit/%ld", k );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[k].msg, g_user_menu_name[i],
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = func;
		ls[k].arg = (void *)i;
		ls[k].flg = FLG_NULL;
		k++;
		key++;
	}

	ls[k].path[0] = '\0';
}

/**/

char	*cb_menu_user_arrange_up_sel( menu_t **pp, menu_t **dflt )
{
	return arrange_menu_user_1( (long)((*pp)->arg), -1 );
}

/**/

char	*cb_menu_user_arrange_down_sel( menu_t **pp, menu_t **dflt )
{
	return arrange_menu_user_1( (long)((*pp)->arg), +1 );
}

/**/

char	*arrange_menu_user_1( long n, long d )
{
	char	name[MENU_MSG_MAX_BYTE + 1];
	char	cmd[MACRO_MAX_LEN + 1];

	if( (n + d) < 0 )
		return NULL;
	if( (n + d) >= g_user_menu_n )
		return NULL;

	str_nz_cpy( name, g_user_menu_name[n], MENU_MSG_MAX_BYTE );
	str_nz_cpy( cmd, g_user_menu_cmd[n], MACRO_MAX_LEN );

	str_nz_cpy( g_user_menu_name[n], g_user_menu_name[n + d],
			MENU_MSG_MAX_BYTE );
	str_nz_cpy( g_user_menu_cmd[n], g_user_menu_cmd[n + d],
			MACRO_MAX_LEN );

	str_nz_cpy( g_user_menu_name[n + d], name, MENU_MSG_MAX_BYTE );
	str_nz_cpy( g_user_menu_cmd[n + d], cmd, MACRO_MAX_LEN );

	return NULL;
}

/**/

char	*cb_menu_user_arrange_top_sel( menu_t **pp, menu_t **dflt )
{
	long	i, n;
	char	name[MENU_MSG_MAX_BYTE + 1];
	char	cmd[MACRO_MAX_LEN + 1];

	n = (long)((*pp)->arg);

	str_nz_cpy( name, g_user_menu_name[n], MENU_MSG_MAX_BYTE );
	str_nz_cpy( cmd, g_user_menu_cmd[n], MACRO_MAX_LEN );

	for( i = n - 1; i >= 0; i-- ){
		str_nz_cpy( g_user_menu_name[i + 1],
				g_user_menu_name[i],
				MENU_MSG_MAX_BYTE );
		str_nz_cpy( g_user_menu_cmd[i + 1],
				g_user_menu_cmd[i],
				MACRO_MAX_LEN );
	}

	str_nz_cpy( g_user_menu_name[0], name, MENU_MSG_MAX_BYTE );
	str_nz_cpy( g_user_menu_cmd[0], cmd, MACRO_MAX_LEN );

	return NULL;
}

/**/

char	*cb_menu_user_arrange_bottom_sel( menu_t **pp, menu_t **dflt )
{
	long	i, n;
	char	name[MENU_MSG_MAX_BYTE + 1];
	char	cmd[MACRO_MAX_LEN + 1];

	n = (long)((*pp)->arg);

	str_nz_cpy( name, g_user_menu_name[n], MENU_MSG_MAX_BYTE );
	str_nz_cpy( cmd, g_user_menu_cmd[n], MACRO_MAX_LEN );

	for( i = n + 1; i < g_user_menu_n; i++ ){
		str_nz_cpy( g_user_menu_name[i - 1],
				g_user_menu_name[i],
				MENU_MSG_MAX_BYTE );
		str_nz_cpy( g_user_menu_cmd[i - 1],
				g_user_menu_cmd[i],
				MACRO_MAX_LEN );
	}

	str_nz_cpy( g_user_menu_name[i - 1], name,
			MENU_MSG_MAX_BYTE );
	str_nz_cpy( g_user_menu_cmd[i - 1], cmd,
			MACRO_MAX_LEN );

	return NULL;
}

/**/

char	*cb_menu_user_remove_sel( menu_t **pp, menu_t **dflt )
{
	long	i, n;

	n = (long)((*pp)->arg);

	for( i = n; i < g_user_menu_n - 1; i++ ){
		str_nz_cpy( g_user_menu_name[i],
				g_user_menu_name[i + 1],
				MENU_MSG_MAX_BYTE );
		str_nz_cpy( g_user_menu_cmd[i],
				g_user_menu_cmd[i + 1],
				MACRO_MAX_LEN );
	}

	g_user_menu_n--;

	return NULL;
}

/**/

char	*cb_menu_set_dflt_system( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_system( *pp );
	return NULL;
}

/**/

char	*cb_menu_system( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_misc( *pp );
	*dflt = g_menu_dflt_system;

#if	FLG_WIZARD_MENU_HIDDEN
	if( g_flg_debug )
		clr_flg_menu( *pp, "wizard", FLG_MENU_HIDDEN );
	else
		set_flg_menu( *pp, "wizard", FLG_MENU_HIDDEN );
#endif

	return NULL;
}

/**/

char	*cb_menu_replay_load( menu_t **pp, menu_t **dflt )
{
	long	n;
	bool_t	flg_text;

	n = menu_replay_sel_load();

	if( n == SAVE_N_SEL )
		return STR_MENU_CANCEL;

	if( g_flg_debug )
		flg_text = TRUE;
	else
		flg_text = FALSE;

	if( load_game_replay( flg_text, n ) ){
		reset_all_save( FALSE );
		if( g_load_slot_n != SAVE_N_AUTO )
			party_exit_bar();

		return NULL;
	}

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_replay_save( menu_t **pp, menu_t **dflt )
{
	if( save_game_replay() )
		return NULL;
	else
		return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_replay_debug( menu_t **pp, menu_t **dflt )
{
	bool_t	flg_text;

	if( g_flg_debug )
		flg_text = TRUE;
	else
		flg_text = FALSE;

	if( load_game_replay( flg_text, SAVE_N_BUG_REPO ) ){
		reset_all_save( FALSE );
		if( g_load_slot_n != SAVE_N_AUTO )
			party_exit_bar();

		return NULL;
	}

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_replay_bug_repo( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_system( *pp );

	if( save_bug_repo_replay() )
		return NULL;
	else
		return STR_MENU_CANCEL;
}

/**/

long	menu_replay_sel_load( void )
{
	menu_t	*ls;
	menu_t	*dflt;
	char	key;
	long	k;
	char	*ret;
	long	i;

	ls = ls_menu_replay_sel_load;
	dflt = NULL;
	k = 0;
	key = 'A';

	str_nz_cpy( ls[k].path, "/replay load list", MENU_PATH_MAX_LEN );
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

		if( (i != 0) && (i % MENU_SAVE_LOAD_N_PER_PAGE == 0) ){
			key = 'A';

			str_nz_cpy( ls[k].path,
					"/replay load list/page separator",
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

		if( i % MENU_SAVE_LOAD_N_PER_PAGE == 0 ){
			str_nz_cpy( ls[k].path,
					"/replay load list/title",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( ls[k].kind, "<Title>",
					MENU_KIND_MAX_LEN );
			ls[k].accel_key = '\0';
			ls[k].short_key[0] = '\0';
			ls[k].n_msg = N_MSG_NULL;
			str_nz_cpy( ls[k].msg, MSG_MENU_REPLAY_LOAD,
					MENU_MSG_MAX_BYTE );
			ls[k].call_back = NULL;
			ls[k].arg = NULL;
			ls[k].flg = FLG_NULL;
			k++;
		}

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/replay load list/%ld", i );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		flg_exist_data = get_save_load_ttl( ls[k].msg, i,
				FALSE, TRUE );
		ls[k].call_back = cb_menu_replay_sel_load;
		if( flg_exist_data )
			ls[k].arg = (void *)i;
		else
			ls[k].arg = (void *)-1;
		ls[k].flg = FLG_NULL;
		k++;

		key++;
	}
	ls[k].path[0] = '\0';

	g_replay_sel_load_n = -1;

	while( 1 ){
		ret = exec_menu( ls, dflt, NULL );

		if( ret == NULL ){
			if( g_replay_sel_load_n <= -1 )
				continue;
			else
				return g_replay_sel_load_n;
		}

		return SAVE_N_SEL;
	}

	return SAVE_N_SEL;
}

/**/

char	*cb_menu_replay_sel_load( menu_t **pp, menu_t **dflt )
{
	if( pp == NULL ){
		g_replay_sel_load_n = -1;
		return STR_MENU_ERR;
	}

	g_replay_sel_load_n = (long)((*pp)->arg);
	return NULL;
}

/**/

char	*cb_menu_command( menu_t **pp, menu_t **dflt )
{
	char	cmd[MENU_COMMAND_MAX_LEN + 1];

	set_menu_dflt_system( *pp );

	cmd[0] = '\0';
	gets_line( MSG_GETS_MENU_COMMAND, cmd, MENU_COMMAND_MAX_LEN );

	return exec_menu( get_ls_menu_main(),
			get_menu_dflt_main(), cmd );
}

/**/

char	*cb_menu_set_dflt_wizard( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_wizard( *pp );
	return NULL;
}

/**/

char	*cb_menu_wizard( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_system( *pp );
	*dflt = g_menu_dflt_wizard;

	if( g_flg_debug )
		return NULL;
	else
		return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_wizard_teleport_party( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_wizard( *pp );
	fx_teleport_party();

	return NULL;
}

/**/

char	*cb_menu_wizard_recall( menu_t **pp, menu_t **dflt )
{
	const long	min_n = -DUN_MAX_LEV_BASE;
	const long	max_n = 0;
	long	n;
	char	*str;

	set_menu_dflt_wizard( *pp );

	n = static_cb_menu_wizard_recall__n;

	print_msg( FLG_NULL, MSG_FX_RECALL_ASK );
	str = exec_menu_sel_num( &n, min_n, max_n );
	redraw_all();
	if( str != NULL )
		return str;

	exec_recall( n );

	static_cb_menu_wizard_recall__n = n;

	return NULL;
}

/**/

char	*cb_menu_wizard_on_light( menu_t **pp, menu_t **dflt )
{
	pos_t	*crsr = get_main_crsr();

	set_menu_dflt_wizard( *pp );

	set_flg_no_save( TRUE );

	on_light_area( crsr->x, crsr->y, TRUE );
	set_flg_find_all_mnstr();
	redraw_map();

	return NULL;
}

/**/

char	*cb_menu_wizard_off_light( menu_t **pp, menu_t **dflt )
{
	pos_t	*crsr = get_main_crsr();

	set_menu_dflt_wizard( *pp );

	set_flg_no_save( TRUE );

	off_light_area( crsr->x, crsr->y, TRUE );
	set_flg_find_all_mnstr();
	redraw_map();

	return NULL;
}

/**/

char	*cb_menu_wizard_add_turn_hour( menu_t **pp, menu_t **dflt )
{
	const long	max_n = 24;
	long	n, turn;
	char	*str;

	n = static_cb_menu_wizard_add_turn__hour;

	str = exec_menu_sel_num( &n, 0, max_n );
	if( str != NULL )
		return str;

	set_flg_no_save( TRUE );

	turn = n * TURN_PER_HOUR;
	reset_turn( get_turn() + turn );

	static_cb_menu_wizard_add_turn__hour = n;
	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_wizard_add_turn_minute( menu_t **pp, menu_t **dflt )
{
	const long	max_n = 60;
	long	n, turn;
	char	*str;

	n = static_cb_menu_wizard_add_turn__minute;

	str = exec_menu_sel_num( &n, 0, max_n );
	if( str != NULL )
		return str;

	set_flg_no_save( TRUE );

	turn = n * TURN_PER_MINUTE;
	reset_turn( get_turn() + turn );

	static_cb_menu_wizard_add_turn__minute = n;
	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_wizard_add_turn_turn( menu_t **pp, menu_t **dflt )
{
	const long	max_n = TURN_A_DAY;
	long	n, turn;
	char	*str;

	n = static_cb_menu_wizard_add_turn__turn;

	str = exec_menu_sel_num( &n, 0, max_n );
	if( str != NULL )
		return str;

	set_flg_no_save( TRUE );

	turn = n;
	reset_turn( get_turn() + turn );

	static_cb_menu_wizard_add_turn__turn = n;
	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_wizard_up_exp( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	pet_t	**pet = get_party_pet();
	const long	n = EXP_MAX;
	long	exp = +(100 * 100 * 100);
	char	*str;
	long	i;

	set_menu_dflt_wizard( *pp );

	exp = static_cb_menu_wizard_up_exp__exp;

	str = exec_menu_sel_num( &exp, -n, +n );
	if( str != NULL )
		return str;
	static_cb_menu_wizard_up_exp__exp = exp;

	set_flg_no_save( TRUE );

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD ) ){
			continue;
		}

		exp_chr( pty->mbr[i], exp, FALSE, TRUE, FALSE );
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet[i] == NULL )
			continue;
		if( chk_flg_or( pet[i]->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD ) ){
			continue;
		}

		exp_chr( pet[i], exp, FALSE, TRUE, FALSE );
	}

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_wizard_up_lev( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;
	abl_kind_t	abl;
	long	lev, min_lev, max_lev;
	long	need_exp;
	char	*str;

	set_menu_dflt_wizard( *pp );

	mbr = NULL;

	while( 1 ){
		/* メンバーやペットを選択 */

		str = exec_menu_sel_mbr(
				&mbr, MSG_MENU_CRSR_MOVE_MBR,
				FALSE, TRUE );
		if( str != NULL ){
			if( strcmp( str, STR_MENU_CANCEL ) == 0 ){
				break;
			} else {
				return str;
			}
		}
		if( mbr == NULL )
			return STR_MENU_ERR;

		while( 1 ){
			/* 能力値を選択 */

			str = exec_menu_sel_abl( mbr, &abl );
			if( str != NULL ){
				if( strcmp( str, STR_MENU_CANCEL ) == 0 ){
					break;
				} else {
					return str;
				}
			}

			lev = mbr->abl.lev[abl].n;
			max_lev = ABL_MAX_LEV;
			if( (ABL_KIND_HP <= abl) && (abl <= ABL_KIND_CHA) )
				min_lev = 1;
			else
				min_lev = 0;

			/* 能力値のレベルを入力 */

			str = exec_menu_sel_num( &lev, min_lev, max_lev );
			if( str != NULL ){
				if( strcmp( str, STR_MENU_CANCEL ) == 0 ){
					continue;
				} else {
					return str;
				}
			}

			/* 能力値のレベルを設定 */

			need_exp = calc_need_exp( lev, abl );
			mbr->abl.exp[abl].n = need_exp;
			chk_lev_up( mbr, TRUE, FALSE, FALSE );
		}
	}

	return NULL;
}

/**/

char	*cb_menu_wizard_scene( menu_t **pp, menu_t **dflt )
{
	scene_n_t	sc;

	sc = (scene_n_t)(long)((*pp)->arg);

	if( sc == SCENE_N_LAST_BOSS )
		enter_last_boss_dun();
	else if( sc == SCENE_N_GAME_OVER )
		game_over();
	else if( sc == SCENE_N_ENDING )
		ending();
	else
		change_scene( sc );

	return NULL;
}

/**/

char	*cb_menu_wizard_last_scene( menu_t **pp, menu_t **dflt )
{
	last_scene_n_t	sc;

	sc = (last_scene_n_t)(long)((*pp)->arg);

	if( get_scene() != SCENE_N_LAST_BOSS )
		enter_last_boss_dun();

	change_last_scene( sc );

	return NULL;
}

/**/

char	*cb_menu_out_map_file( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_system( *pp );

	if( out_map_file() )
		return NULL;

	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_shell( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_system( *pp );
	child_ps();

	return NULL;
}

/**/

char	*cb_menu_about_game( menu_t **pp, menu_t **dflt )
{
	set_menu_dflt_system( *pp );
	about_game( FALSE );

	return NULL;
}

/**/

char	*cb_menu_exit( menu_t **pp, menu_t **dflt )
{
	ask_t	ask;

	set_menu_dflt_system( *pp );
	ask = exec_menu_ask( MSG_TTL_MENU_EXIT, ASK_NO, TRUE );

	if( ask == ASK_YES )
		exit_game( EXIT_SUCCESS );
	if( ask == ASK_ERR )
		return STR_MENU_ERR;

	return STR_MENU_CANCEL;
}

/**/

void	set_menu_dflt_misc( menu_t *p )
{
	if( !get_flg_chk_short_key() )
		g_menu_dflt_misc = p;
}

/**/

void	set_menu_dflt_cnf( menu_t *p )
{
	if( !get_flg_chk_short_key() )
		g_menu_dflt_cnf = p;
}

/**/

void	set_menu_dflt_system( menu_t *p )
{
	if( !get_flg_chk_short_key() )
		g_menu_dflt_system = p;
}

/**/

void	set_menu_dflt_wizard( menu_t *p )
{
	if( !get_flg_chk_short_key() )
		g_menu_dflt_wizard = p;
}

/**/

bool_t	*get_ls_flg_srch( void )
{
	return g_ls_flg_srch;
}

/**/

menu_t	*get_ls_menu_move_crsr( void )
{
	return ls_menu_move_crsr;
}

/**/

flg_scroll_t	get_flg_scroll( void )
{
	return g_flg_scroll;
}

/**/

flg_scroll_t	set_flg_scroll( flg_scroll_t flg )
{
	g_flg_scroll = flg;

	return g_flg_scroll;
}

/**/

bool_t	get_flg_mbr_data_change_page_is_crsr( void )
{
	return g_flg_mbr_data_change_page_is_crsr;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_imenu_c( void )
{
	check_memory( check_memory_imenu_c_g_menu_dflt_misc,
			"imenu.c: g_menu_dflt_misc" );
	check_memory( check_memory_imenu_c_g_sel_mbr,
			"imenu.c: g_sel_mbr" );
	check_memory( check_memory_imenu_c_g_flg_continue_exec_mode,
			"imenu.c: g_flg_continue_exec_mode" );
	check_memory( check_memory_imenu_c_g_ls_flg_srch,
			"imenu.c: g_ls_flg_srch" );
	check_memory( check_memory_imenu_c_ls_menu_ind_square,
			"imenu.c: ls_menu_ind_square" );
	check_memory( check_memory_imenu_c_g_menu_dflt_ind_square,
			"imenu.c: g_menu_dflt_ind_square" );
	check_memory( check_memory_imenu_c_g_flg_scroll,
			"imenu.c: g_flg_scroll" );
	check_memory( check_memory_imenu_c_g_cui_mouse_double_click_msec,
			"imenu.c: g_cui_mouse_double_click_msec" );
	check_memory( check_memory_imenu_c_g_music_volume_rate,
			"imenu.c: g_music_volume_rate" );
	check_memory( check_memory_imenu_c_ls_menu_joystick_sel_n,
			"imenu.c: ls_menu_joystick_sel_n" );
	check_memory( check_memory_imenu_c_g_user_menu_n,
			"imenu.c: g_user_menu_n" );
	check_memory( check_memory_imenu_c_g_user_menu_name,
			"imenu.c: g_user_menu_name" );
	check_memory( check_memory_imenu_c_g_user_menu_cmd,
			"imenu.c: g_user_menu_cmd" );
	check_memory( check_memory_imenu_c_g_replay_sel_load_n,
			"imenu.c: g_replay_sel_load_n" );
	check_memory( check_memory_imenu_c_ls_menu_replay_sel_load,
			"imenu.c: ls_menu_replay_sel_load" );
	check_memory( check_memory_imenu_c_g_page_n,
			"imenu.c: g_page_n" );
	check_memory( check_memory_imenu_c_g_flg_mbr_data_change_page_is_crsr,
			"imenu.c: g_flg_mbr_data_change_page_is_crsr" );
	check_memory( check_memory_imenu_c_n,
			"imenu.c: n" );
}
