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
* $Id: menu.c,v 1.236 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#define	MENU_C
#include	"inc.h"

/**/

#define	DRAW_MENU_CLR_N	-1

/**/

static long	g_nest_flg_executing_menu;
static bool_t	g_flg_space_select;
static bool_t	g_flg_menu_dflt;
static bool_t	g_flg_chk_menu;
static bool_t	g_flg_chk_short_key;
static long	g_sel_menu_accel_key;
static bool_t	g_flg_move_crsr_dflt;
check_memory_def( check_memory_menu_c_g_nest_flg_executing_menu )

#define	MENU_CURRENT_PATH_MAX_N	8
static long	g_menu_current_path_n;
static char	g_menu_current_path
	[MENU_CURRENT_PATH_MAX_N][MENU_PATH_MAX_LEN + 1];
check_memory_def( check_memory_menu_c_g_menu_current_path_n )

static ask_t	g_sel_ask;
check_memory_def( check_memory_menu_c_g_sel_ask )

static char	*menu_kind_ls[] = {
	/* タイトル */
	"<Title>",

	/* 項目 */
	"<Item>",

	/* チェック項目 */
	"<CheckItem>",

	/* 選択項目 */
	"<RadioItem>",

	/* 別ウィンドウを開く項目 */
	"<OpenWinItem>",

	/* <RadioItem>の区切り */
	"<Separator>",

	/* メニューが複数ページ有る時の区切り */
	"<PageSeparator>",

	/* サブメニュー */
	"<Branch>",

	NULL,
};
check_memory_def( check_memory_menu_c_menu_kind_ls )

menu_t	dummy_menu_close_menu;
check_memory_def( check_memory_menu_c_dummy_menu_close_menu )

/***************************************************************
* ファンクション・キー
***************************************************************/

#define	MENU_MACRO_FUNC_MAX_N_PER_PAGE	12
#define	MENU_MACRO_MOUSE_MAX_N_PER_PAGE	10
#define	MENU_MACRO_JOYSTICK_MAX_N_PER_PAGE	10

static char	g_macro_func
	[KEY_N_FUNC_MAX_N][MACRO_MAX_LEN + 1];
static char	g_macro_mouse_click
	[KEY_N_MOUSE_CLICK_MAX_N][MACRO_MAX_LEN + 1];
static char	g_macro_mouse_d_click
	[KEY_N_MOUSE_D_CLICK_MAX_N][MACRO_MAX_LEN + 1];
static char	g_macro_mouse_p_click
	[KEY_N_MOUSE_P_CLICK_MAX_N][MACRO_MAX_LEN + 1];
static char	g_macro_mouse_press
	[KEY_N_MOUSE_PRESS_MAX_N][MACRO_MAX_LEN + 1];
static char	g_macro_mouse_release
	[KEY_N_MOUSE_RELEASE_MAX_N][MACRO_MAX_LEN + 1];
static char	g_macro_mouse_motion
	[KEY_N_MOUSE_MOTION_MAX_N][MACRO_MAX_LEN + 1];
static char	g_macro_joystick
	[JOY_KIND_MAX_N]
	[KEY_N_JOYSTICK_MAX_N][MACRO_MAX_LEN + 1];
check_memory_def( check_memory_menu_c_g_macro_func )

/* デフォルトのマクロ */
typedef struct {
	char	*key;
	char	*dflt;
} macro_short_key_t;

/* デフォルトのファンクション・キーのテーブル */
static macro_short_key_t	g_ls_short_key_func
		[KEY_N_FUNC_MAX_N] = {
	{ NULL, NULL },	/* F1 */
	{ NULL, NULL },	/* F2 */
	{ NULL, NULL },	/* F3 */
	{ NULL, NULL },	/* F4 */
	{ NULL, "z" },	/* F5 */
	{ NULL, "x" },	/* F6 */
	{ NULL, "c" },	/* F7 */
	{ NULL, "v" },	/* F8 */
	{ NULL, NULL },	/* F9 */
	{ NULL, NULL },	/* F10 */
	{ NULL, NULL },	/* F11 */
	{ NULL, NULL },	/* F12 */
	{ NULL, NULL },	/* F13 */
	{ NULL, NULL },	/* F14 */
	{ NULL, NULL },	/* F15 */
	{ NULL, NULL },	/* F16 */
	{ NULL, NULL },	/* F17 */
	{ NULL, NULL },	/* F18 */
	{ NULL, NULL },	/* F19 */
	{ NULL, NULL },	/* F20 */
};

/* デフォルトのマウス・クリックのテーブル */
static macro_short_key_t	g_ls_short_key_mouse_click
		[KEY_N_MOUSE_CLICK_MAX_N] = {
	{ NULL, "+" },	/* left */
	{ NULL, NULL },	/* middle */
	{ NULL, "." },	/* right */
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
};

/* デフォルトのマウス・ダブル・クリックのテーブル */
static macro_short_key_t	g_ls_short_key_mouse_d_click
		[KEY_N_MOUSE_D_CLICK_MAX_N] = {
	{ NULL, "\n" },	/* left */
	{ NULL, NULL },	/* middle */
	{ NULL, NULL },	/* right */
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
};

/* デフォルトのマウス・両クリックのテーブル */
static macro_short_key_t	g_ls_short_key_mouse_p_click
		[KEY_N_MOUSE_P_CLICK_MAX_N] = {
	{ NULL, "+" },	/* press left & click right */
	{ NULL, "," },	/* press right & click left */
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
};

/* デフォルトのマウス・プレスのテーブル */
static macro_short_key_t	g_ls_short_key_mouse_press
		[KEY_N_MOUSE_PRESS_MAX_N] = {
	{ NULL, NULL },	/* left */
	{ NULL, NULL },	/* middle */
	{ NULL, "," },	/* right */
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
};

/* デフォルトのマウス・リリースのテーブル */
static macro_short_key_t	g_ls_short_key_mouse_release
		[KEY_N_MOUSE_RELEASE_MAX_N] = {
	{ NULL, NULL },	/* left */
	{ NULL, NULL },	/* middle */
	{ NULL, "0" },	/* right */
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
};

/* デフォルトのマウス・モーションのテーブル */
static macro_short_key_t	g_ls_short_key_mouse_motion
		[KEY_N_MOUSE_MOTION_MAX_N] = {
	{ NULL, "/" },	/* left */
	{ NULL, "*" },	/* right */
	{ NULL, "-" },	/* up */
	{ NULL, "+" },	/* down */
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
};

/* デフォルトのジョイスティック・ボタンのテーブル */
static macro_short_key_t	g_ls_short_key_joystick
		[JOY_KIND_MAX_N][KEY_N_JOYSTICK_MAX_N] = {
	/* JOY_KIND_NULL, */
	{
		{ NULL, NULL },	/* 1 */
		{ NULL, NULL },	/* 2 */
		{ NULL, NULL },	/* 3 */
		{ NULL, NULL },	/* 4 */
		{ NULL, NULL },	/* 5 */
		{ NULL, NULL },	/* 6 */
		{ NULL, NULL },	/* 7 */
		{ NULL, NULL },	/* 8 */
		{ NULL, NULL },	/* 9 */
		{ NULL, NULL },	/* 10 */
		{ NULL, NULL },	/* 11 */
		{ NULL, NULL },	/* 12 */
		{ NULL, NULL },	/* 13 */
		{ NULL, NULL },	/* 14 */
		{ NULL, NULL },	/* 15 */
		{ NULL, NULL },	/* 16 */
		{ NULL, NULL },	/* 17 */
		{ NULL, NULL },	/* 18 */
		{ NULL, NULL },	/* 19 */
		{ NULL, NULL },	/* 20 */
	},
	/* JOY_KIND_PS, */
	{
		{ NULL, "+" },	/* 1 */
		{ NULL, "\n" },	/* 2 */
		{ NULL, "0" },	/* 3 */
		{ NULL, "." },	/* 4 */
		{ NULL, "/" },	/* 5 */
		{ NULL, "*" },	/* 6 */
		{ NULL, "-" },	/* 7 */
		{ NULL, "+" },	/* 8 */
		{ NULL, "\t" },	/* 9 */
		{ NULL, "R" },	/* 10 */
		{ NULL, NULL },	/* 11 */
		{ NULL, NULL },	/* 12 */
		{ NULL, NULL },	/* 13 */
		{ NULL, NULL },	/* 14 */
		{ NULL, NULL },	/* 15 */
		{ NULL, NULL },	/* 16 */
		{ NULL, NULL },	/* 17 */
		{ NULL, NULL },	/* 18 */
		{ NULL, NULL },	/* 19 */
		{ NULL, NULL },	/* 20 */
	},
	/* JOY_KIND_SATURN, */
	{
		{ NULL, "\n" },	/* 1 */
		{ NULL, "0" },	/* 2 */
		{ NULL, "+" },	/* 3 */
		{ NULL, "." },	/* 4 */
		{ NULL, "\t" },	/* 5 */
		{ NULL, "R" },	/* 6 */
		{ NULL, "-" },	/* 7 */
		{ NULL, "/" },	/* 8 */
		{ NULL, "+" },	/* 9 */
		{ NULL, "*" },	/* 10 */
		{ NULL, NULL },	/* 11 */
		{ NULL, NULL },	/* 12 */
		{ NULL, NULL },	/* 13 */
		{ NULL, NULL },	/* 14 */
		{ NULL, NULL },	/* 15 */
		{ NULL, NULL },	/* 16 */
		{ NULL, NULL },	/* 17 */
		{ NULL, NULL },	/* 18 */
		{ NULL, NULL },	/* 19 */
		{ NULL, NULL },	/* 20 */
	},
	/* JOY_KIND_RAP3, */
	{
		{ NULL, "." },	/* 1 */
		{ NULL, "0" },	/* 2 */
		{ NULL, "\n" },	/* 3 */
		{ NULL, "+" },	/* 4 */
		{ NULL, "*" },	/* 5 */
		{ NULL, "/" },	/* 6 */
		{ NULL, "+" },	/* 7 */
		{ NULL, "-" },	/* 8 */
		{ NULL, "\t" },	/* 9 */
		{ NULL, "R" },	/* 10 */
		{ NULL, NULL },	/* 11 */
		{ NULL, NULL },	/* 12 */
		{ NULL, NULL },	/* 13 */
		{ NULL, NULL },	/* 14 */
		{ NULL, NULL },	/* 15 */
		{ NULL, NULL },	/* 16 */
		{ NULL, NULL },	/* 17 */
		{ NULL, NULL },	/* 18 */
		{ NULL, NULL },	/* 19 */
		{ NULL, NULL },	/* 20 */
	},
};
check_memory_def( check_memory_menu_c_g_ls_short_key_func )

static bool_t	g_flg_dup_short_key[256];
check_memory_def( check_memory_menu_c_g_flg_dup_short_key )

/**/

#include	"menu-tab.h"

/***************************************************************/

void	init_var_menu( void )
{
	g_nest_flg_executing_menu = make_nest_flg();
	g_sel_menu_accel_key = '\0';

	clr_menu_current_path();

	set_flg_space_select( FALSE );
	set_flg_menu_dflt( TRUE );
	set_flg_move_crsr_dflt( FALSE );
}

/**/

void	init_menu( void )
{
	long	i, j;

	g_flg_chk_menu = TRUE;
	g_flg_chk_short_key = FALSE;

	chk_dup_short_key();

	for( i = 0; i < KEY_N_FUNC_MAX_N; i++ ){
		init_macro_func( g_macro_func[i],
				g_ls_short_key_func[i].dflt );
	}
	for( i = 0; i < KEY_N_MOUSE_CLICK_MAX_N; i++ ){
		init_macro_func( g_macro_mouse_click[i],
				g_ls_short_key_mouse_click[i].dflt );
	}
	for( i = 0; i < KEY_N_MOUSE_D_CLICK_MAX_N; i++ ){
		init_macro_func( g_macro_mouse_d_click[i],
				g_ls_short_key_mouse_d_click[i].dflt );
	}
	for( i = 0; i < KEY_N_MOUSE_P_CLICK_MAX_N; i++ ){
		init_macro_func( g_macro_mouse_p_click[i],
				g_ls_short_key_mouse_p_click[i].dflt );
	}
	for( i = 0; i < KEY_N_MOUSE_PRESS_MAX_N; i++ ){
		init_macro_func( g_macro_mouse_press[i],
				g_ls_short_key_mouse_press[i].dflt );
	}
	for( i = 0; i < KEY_N_MOUSE_RELEASE_MAX_N; i++ ){
		init_macro_func( g_macro_mouse_release[i],
				g_ls_short_key_mouse_release[i].dflt );
	}
	for( i = 0; i < KEY_N_MOUSE_MOTION_MAX_N; i++ ){
		init_macro_func( g_macro_mouse_motion[i],
				g_ls_short_key_mouse_motion[i].dflt );
	}
	for( j = 0; j < JOY_KIND_MAX_N; j++ ){
		for( i = 0; i < KEY_N_JOYSTICK_MAX_N; i++ ){
			init_macro_func( g_macro_joystick[j][i],
					g_ls_short_key_joystick[j][i]
					.dflt );
		}
	}

	init_ls_menu_macro_func();
	init_ls_menu_macro_mouse();
	init_ls_menu_macro_joystick();
}

/**/

void	init_macro_func( char *macro, const char *dflt )
{
	if( macro == NULL )
		return;

	if( dflt == NULL )
		str_nz_cpy( macro, "", MACRO_MAX_LEN );
	else
		str_nz_cpy( macro, dflt, MACRO_MAX_LEN );
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_menu( void )
{
}

/**/

void	init_ls_menu_macro_func( void )
{
	menu_t	*ls;
	char	key;
	long	i, k;

	ls = ls_menu_macro_func;
	k = 0;

	str_nz_cpy( ls[k].path, "/func", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/func/--", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_MENU_FUNC, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	key = 'A';
	for( i = 0; i < KEY_N_FUNC_MAX_N; i++ ){
		long	fn, dfn;
		long	macro_n;

		fn = i;
		dfn = i + 1;
		macro_n = KEY_N_FUNC_HEAD_N + i;

		if( ((i % MENU_MACRO_FUNC_MAX_N_PER_PAGE) == 0)
				&& (i != 0) ){
			str_nz_cpy( ls[k].path, "/func/page separator",
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
				"/func/%ld", fn );
		str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
				MSG_MENU_FUNC_KEY, dfn );
		ls[k].call_back = NULL;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/func/%ld/--", fn );
		str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = '\0';
		ls[k].short_key[0] = '\0';
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
				MSG_MENU_FUNC_KEY, dfn );
		ls[k].call_back = NULL;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/func/%ld/exec", fn );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'X';
		if( g_ls_short_key_func[fn].key == NULL ){
			sn_printf( ls[k].short_key, MENU_SHORT_KEY_MAX_LEN,
					"&f%ld;", fn );
		} else {
			sn_printf( ls[k].short_key, MENU_SHORT_KEY_MAX_LEN,
					"%s &f%ld;",
					g_ls_short_key_func[fn].key, fn );
		}
		str_nz_cpy( ls[k].msg, MSG_MENU_FUNC_EXEC,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_func_exec;
		ls[k].arg = (void *)macro_n;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/func/%ld/edit", fn );
		str_nz_cpy( ls[k].kind, "<OpenWinItem>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'E';
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, MSG_MENU_FUNC_EDIT,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_func_edit;
		ls[k].arg = (void *)macro_n;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/func/%ld/set reg macro", fn );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'M';
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, MSG_MENU_FUNC_SET_REG_MACRO,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_func_set_reg_macro;
		ls[k].arg = (void *)macro_n;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/func/%ld/unset", fn );
		str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'U';
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, MSG_MENU_FUNC_UNSET,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_func_unset;
		ls[k].arg = (void *)macro_n;
		ls[k].flg = FLG_NULL;
		k++;

		key++;
	}
	ls[k].path[0] = '\0';
}

/**/

void	init_ls_menu_macro_mouse( void )
{
	menu_t	*ls;
	char	key;
	long	i, k;
	long	macro_n;

	ls = ls_menu_macro_mouse;
	k = 0;
	macro_n = KEY_N_MOUSE_HEAD_N;

	str_nz_cpy( ls[k].path, "/mouse", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/mouse/--", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_MENU_MOUSE, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	/* クリック */

	key = 'A';
	for( i = 0; i < KEY_N_MOUSE_CLICK_MAX_N; i++ ){
		init_ls_menu_macro_mouse_sub(
				ls, i, &k, &key, macro_n + i );
	}
	macro_n += KEY_N_MOUSE_CLICK_MAX_N;

	str_nz_cpy( ls[k].path, "/mouse/page separator",
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

	/* ダブル・クリック */

	key = 'A';
	for( i = 0; i < KEY_N_MOUSE_D_CLICK_MAX_N; i++ ){
		init_ls_menu_macro_mouse_sub(
				ls, i, &k, &key, macro_n + i );
	}
	macro_n += KEY_N_MOUSE_D_CLICK_MAX_N;

	str_nz_cpy( ls[k].path, "/mouse/page separator",
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

	/* 両クリック */

	key = 'A';
	for( i = 0; i < KEY_N_MOUSE_P_CLICK_MAX_N; i++ ){
		init_ls_menu_macro_mouse_sub(
				ls, i, &k, &key, macro_n + i );
	}
	macro_n += KEY_N_MOUSE_P_CLICK_MAX_N;

	str_nz_cpy( ls[k].path, "/mouse/page separator",
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

	/* プレス */

	key = 'A';
	for( i = 0; i < KEY_N_MOUSE_PRESS_MAX_N; i++ ){
		init_ls_menu_macro_mouse_sub(
				ls, i, &k, &key, macro_n + i );
	}
	macro_n += KEY_N_MOUSE_PRESS_MAX_N;

	str_nz_cpy( ls[k].path, "/mouse/page separator",
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

	/* リリース */

	key = 'A';
	for( i = 0; i < KEY_N_MOUSE_RELEASE_MAX_N; i++ ){
		init_ls_menu_macro_mouse_sub(
				ls, i, &k, &key, macro_n + i );
	}
	macro_n += KEY_N_MOUSE_RELEASE_MAX_N;

	str_nz_cpy( ls[k].path, "/mouse/page separator",
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

	/* モーション */

	key = 'A';
	for( i = 0; i < KEY_N_MOUSE_MOTION_MAX_N; i++ ){
		init_ls_menu_macro_mouse_sub(
				ls, i, &k, &key, macro_n + i );
	}
	macro_n += KEY_N_MOUSE_MOTION_MAX_N;

	str_nz_cpy( ls[k].path, "/mouse/page separator",
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

	k--;
	ls[k].path[0] = '\0';
}

/**/

void	init_ls_menu_macro_mouse_sub(
	menu_t *ls, long i, long *kp, char *key_p, long macro_n
)
{
	long	k;
	char	key;

	k = *kp;
	key = *key_p;

	if( ((i % MENU_MACRO_MOUSE_MAX_N_PER_PAGE) == 0) && (i != 0) ){
		str_nz_cpy( ls[k].path, "/mouse/page separator",
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
			"/mouse/%ld", macro_n );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = key;
	ls[k].short_key[0] = '\0';
	sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
			get_msg_menu_mouse( macro_n ) );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
			"/mouse/%ld/--", macro_n );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
			get_msg_menu_mouse( macro_n ) );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
			"/mouse/%ld/exec", macro_n );
	str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'X';
	sn_printf( ls[k].short_key, MENU_SHORT_KEY_MAX_LEN,
			get_msg_menu_mouse_short_key( macro_n ) );
	str_nz_cpy( ls[k].msg, MSG_MENU_MOUSE_EXEC,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_func_exec;
	ls[k].arg = (void *)macro_n;
	ls[k].flg = FLG_NULL;
	k++;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
			"/mouse/%ld/edit", macro_n );
	str_nz_cpy( ls[k].kind, "<OpenWinItem>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'E';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_MENU_MOUSE_EDIT,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_func_edit;
	ls[k].arg = (void *)macro_n;
	ls[k].flg = FLG_NULL;
	k++;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
			"/mouse/%ld/set reg macro", macro_n );
	str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'M';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_MENU_MOUSE_SET_REG_MACRO,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_func_set_reg_macro;
	ls[k].arg = (void *)macro_n;
	ls[k].flg = FLG_NULL;
	k++;

	sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
			"/mouse/%ld/unset", macro_n );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = 'U';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_MENU_MOUSE_UNSET,
			MENU_MSG_MAX_BYTE );
	ls[k].call_back = cb_menu_func_unset;
	ls[k].arg = (void *)macro_n;
	ls[k].flg = FLG_NULL;
	k++;

	key++;

	*kp = k;
	*key_p = key;
}

/**/

const char	*get_msg_menu_mouse( long n )
{
	static char	buf[MENU_MSG_MAX_BYTE + 1];
	const char	*str_null = "----";

	if( n < 0 )
		return str_null;

	if( n < KEY_N_FUNC_MAX_N ){
		sn_printf( buf, MENU_MSG_MAX_BYTE,
				MSG_MENU_FUNC_KEY, n + 1 );
		return buf;
	}
	n -= KEY_N_FUNC_MAX_N;

	if( n < KEY_N_MOUSE_CLICK_MAX_N ){
		sn_printf( buf, MENU_MSG_MAX_BYTE,
				MSG_MENU_MOUSE_CLICK, n + 1 );
		return buf;
	}
	n -= KEY_N_MOUSE_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_D_CLICK_MAX_N ){
		sn_printf( buf, MENU_MSG_MAX_BYTE,
				MSG_MENU_MOUSE_D_CLICK, n + 1 );
		return buf;
	}
	n -= KEY_N_MOUSE_D_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_P_CLICK_MAX_N ){
		switch( n ){
		case 0:
			sn_printf( buf, MENU_MSG_MAX_BYTE,
					MSG_MENU_MOUSE_P_CLICK, 1, 3 );
			return buf;
		case 1:
			sn_printf( buf, MENU_MSG_MAX_BYTE,
					MSG_MENU_MOUSE_P_CLICK, 3, 1 );
			return buf;
		}
		return str_null;
	}
	n -= KEY_N_MOUSE_P_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_PRESS_MAX_N ){
		sn_printf( buf, MENU_MSG_MAX_BYTE,
				MSG_MENU_MOUSE_PRESS, n + 1 );
		return buf;
	}
	n -= KEY_N_MOUSE_PRESS_MAX_N;

	if( n < KEY_N_MOUSE_RELEASE_MAX_N ){
		sn_printf( buf, MENU_MSG_MAX_BYTE,
				MSG_MENU_MOUSE_RELEASE, n + 1 );
		return buf;
	}
	n -= KEY_N_MOUSE_RELEASE_MAX_N;

	if( n < KEY_N_MOUSE_MOTION_MAX_N ){
		switch( n ){
		case 0:
			sn_printf( buf, MENU_MSG_MAX_BYTE,
					MSG_MENU_MOUSE_MOTION_LEFT );
			return buf;
		case 1:
			sn_printf( buf, MENU_MSG_MAX_BYTE,
					MSG_MENU_MOUSE_MOTION_RIGHT );
			return buf;
		case 2:
			sn_printf( buf, MENU_MSG_MAX_BYTE,
					MSG_MENU_MOUSE_MOTION_UP );
			return buf;
		case 3:
			sn_printf( buf, MENU_MSG_MAX_BYTE,
					MSG_MENU_MOUSE_MOTION_DOWN );
			return buf;
		}
		return str_null;
	}
	n -= KEY_N_MOUSE_MOTION_MAX_N;

	return str_null;
}

/**/

const char	*get_msg_menu_mouse_short_key( long n )
{
	static char	buf[MENU_SHORT_KEY_MAX_LEN + 1];
	const char	*p;
	long	a;

	if( n < 0 )
		return "";

	if( n < KEY_N_FUNC_MAX_N ){
		a = KEY_N_FUNC( n );
		p = g_ls_short_key_func[n].key;
		if( p == NULL ){
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"&f%ld; &a0x%lx;", n, a );
		} else {
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"%s &f%ld; &a0x%lx;", *p, n, a );
		}
		return buf;
	}
	n -= KEY_N_FUNC_MAX_N;

	if( n < KEY_N_MOUSE_CLICK_MAX_N ){
		a = KEY_N_MOUSE_CLICK( n );
		p = g_ls_short_key_mouse_click[n].key;
		if( p == NULL ){
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"&mc%ld; &a0x%lx;", n, a );
		} else {
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"%s &mc%ld; &a0x%lx;", *p, n, a );
		}
		return buf;
	}
	n -= KEY_N_MOUSE_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_D_CLICK_MAX_N ){
		a = KEY_N_MOUSE_D_CLICK( n );
		p = g_ls_short_key_mouse_d_click[n].key;
		if( p == NULL ){
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"&md%ld; &a0x%lx;", n, a );
		} else {
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"%s &md%ld; &a0x%lx;", *p, n, a );
		}
		return buf;
	}
	n -= KEY_N_MOUSE_D_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_P_CLICK_MAX_N ){
		a = KEY_N_MOUSE_P_CLICK( n );
		p = g_ls_short_key_mouse_p_click[n].key;
		if( p == NULL ){
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"&mb%ld; &a0x%lx;", n, a );
		} else {
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"%s &mb%ld; &a0x%lx;", *p, n, a );
		}
		return buf;
	}
	n -= KEY_N_MOUSE_P_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_PRESS_MAX_N ){
		a = KEY_N_MOUSE_PRESS( n );
		p = g_ls_short_key_mouse_press[n].key;
		if( p == NULL ){
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"&mp%ld; &a0x%lx;", n, a );
		} else {
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"%s &mp%ld; &a0x%lx;", *p, n, a );
		}
		return buf;
	}
	n -= KEY_N_MOUSE_PRESS_MAX_N;

	if( n < KEY_N_MOUSE_RELEASE_MAX_N ){
		a = KEY_N_MOUSE_RELEASE( n );
		p = g_ls_short_key_mouse_release[n].key;
		if( p == NULL ){
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"&mr%ld; &a0x%lx;", n, a );
		} else {
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"%s &mr%ld; &a0x%lx;", *p, n, a );
		}
		return buf;
	}
	n -= KEY_N_MOUSE_RELEASE_MAX_N;

	if( n < KEY_N_MOUSE_MOTION_MAX_N ){
		a = KEY_N_MOUSE_MOTION( n );
		p = g_ls_short_key_mouse_motion[n].key;
		if( p == NULL ){
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"&mm%ld; &a0x%lx;", n, a );
		} else {
			sn_printf( buf, MENU_SHORT_KEY_MAX_LEN,
					"%s &mm%ld; &a0x%lx;", *p, n, a );
		}
		return buf;
	}
	n -= KEY_N_MOUSE_MOTION_MAX_N;

	return "";
}

/**/

void	init_ls_menu_macro_joystick( void )
{
	menu_t	*ls;
	char	key;
	long	i, k;

	ls = ls_menu_macro_joystick;
	k = 0;

	str_nz_cpy( ls[k].path, "/joystick", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/joystick/--", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	str_nz_cpy( ls[k].msg, MSG_MENU_JOYSTICK, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	key = 'A';
	for( i = 0; i < KEY_N_JOYSTICK_MAX_N; i++ ){
		long	fn, dfn;
		long	macro_n;

		fn = i;
		dfn = i + 1;
		macro_n = KEY_N_JOYSTICK_HEAD_N + i;

		if( ((i % MENU_MACRO_JOYSTICK_MAX_N_PER_PAGE) == 0)
				&& (i != 0) ){
			str_nz_cpy( ls[k].path, "/joystick/page separator",
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
				"/joystick/%ld", fn );
		str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = key;
		ls[k].short_key[0] = '\0';
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
				MSG_MENU_JOYSTICK_KEY, dfn );
		ls[k].call_back = NULL;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/joystick/%ld/--", fn );
		str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = '\0';
		ls[k].short_key[0] = '\0';
		sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
				MSG_MENU_JOYSTICK_KEY, dfn );
		ls[k].call_back = NULL;
		ls[k].arg = NULL;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/joystick/%ld/exec", fn );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'X';
		if( g_ls_short_key_joystick[JOY_KIND_PS][fn].key == NULL ){
			sn_printf( ls[k].short_key, MENU_SHORT_KEY_MAX_LEN,
					"&j%ld;", fn );
		} else {
			sn_printf( ls[k].short_key, MENU_SHORT_KEY_MAX_LEN,
					"%s &j%ld;",
					g_ls_short_key_joystick
					[JOY_KIND_PS][fn].key,
					fn );
		}
		str_nz_cpy( ls[k].msg, MSG_MENU_JOYSTICK_EXEC,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_func_exec;
		ls[k].arg = (void *)macro_n;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/joystick/%ld/edit", fn );
		str_nz_cpy( ls[k].kind, "<OpenWinItem>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'E';
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, MSG_MENU_JOYSTICK_EDIT,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_func_edit;
		ls[k].arg = (void *)macro_n;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/joystick/%ld/set reg macro", fn );
		str_nz_cpy( ls[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'M';
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, MSG_MENU_JOYSTICK_SET_REG_MACRO,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_func_set_reg_macro;
		ls[k].arg = (void *)macro_n;
		ls[k].flg = FLG_NULL;
		k++;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/joystick/%ld/unset", fn );
		str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		ls[k].accel_key = 'U';
		ls[k].short_key[0] = '\0';
		str_nz_cpy( ls[k].msg, MSG_MENU_JOYSTICK_UNSET,
				MENU_MSG_MAX_BYTE );
		ls[k].call_back = cb_menu_func_unset;
		ls[k].arg = (void *)macro_n;
		ls[k].flg = FLG_NULL;
		k++;

		key++;
	}
	ls[k].path[0] = '\0';
}

/**/

bool_t	chk_executing_menu( void )
{
	return chk_nest_flg( g_nest_flg_executing_menu );
}

/**/

char	*exec_menu( menu_t *p, menu_t *dflt, char *str_goto )
{
	char	*ret;

	bgn_nest_flg( g_nest_flg_executing_menu );
	ret = exec_menu_sub( p, dflt, str_goto );
	end_nest_flg( g_nest_flg_executing_menu );

	return ret;
}

/**/

char	*exec_menu_sub( menu_t *p, menu_t *dflt, char *str_goto )
{
	bool_t	flg_short = FALSE;
	bool_t	flg_ret = FALSE;

	if( p == NULL )
		return STR_MENU_ERR;

	if( !get_flg_menu_dflt() )
		dflt = NULL;

	chk_err_menu_kind( p );

	/* メニューのパスが指定と一致したら検索モード終了 */

	if( str_goto != NULL ){
		flg_short = TRUE;
		if( strcmp( p->path, str_goto ) == 0 )
			str_goto = NULL;
	}

	/* コール・バック関数を実行 */

	if( p->call_back != NULL ){
		menu_t	*pre_p = p;
		char	*str_goto_call_back;

		str_goto_call_back = p->call_back( &p, &dflt );
		if( !get_flg_menu_dflt() )
			dflt = NULL;

		if( str_goto_call_back != NULL )
			return str_goto_call_back;

		/* メニューのパスが書き換わったら */
		/* パスのルートを変えて実行 */

		if( pre_p != p ){
			char	*ret;

			clr_msg();

			push_menu_current_path( pre_p->path );

			if( str_goto == NULL ){
				ret = exec_menu( p, dflt, str_goto );
			} else {
				long	len;

				len = str_len_std( pre_p->path );
				ret = exec_menu( p, dflt, &(str_goto[len]) );
			}

			pop_menu_current_path();

			return ret;
		}
	}

	if( p == NULL )
		return NULL;
	if( strcmp( p->kind, "<Branch>" ) != 0 )
		return NULL;

	while( 1 ){
		if( str_goto == NULL ){
			dflt = sel_menu( p, dflt );
			if( dflt == NULL )
				return STR_MENU_CANCEL;
			if( dflt == &dummy_menu_close_menu )
				return NULL;

			if( strcmp( dflt->kind, "<CheckItem>" ) == 0 ){
				if( !set_menu_check_item( dflt ) )
					return STR_MENU_ERR;
			} else if( strcmp( dflt->kind, "<RadioItem>" ) == 0 ){
				if( !set_menu_radio_item( p, dflt ) )
					return STR_MENU_ERR;
			}
		} else {
			dflt = srch_goto_menu( p, str_goto );
			if( dflt == NULL ){
				if( flg_ret )
					return str_goto;
				else
					return STR_MENU_ERR;
			}
		}

		clr_msg();
		str_goto = exec_menu( dflt, NULL, str_goto );

		if( str_goto == NULL ){
			return NULL;
		} else if( strcmp( str_goto, STR_MENU_ERR ) == 0 ){
			return STR_MENU_ERR;
		} else if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 ){
			if( flg_short )
				return NULL;
			else
				str_goto = NULL;
		} else {
			flg_ret = TRUE;
		}
	}

	return STR_MENU_ERR;
}

/***************************************************************
* メニューの現在のパスをクリア
***************************************************************/

void	clr_menu_current_path( void )
{
	g_menu_current_path_n = 0;
}

/***************************************************************
* メニューの現在のパスを返す
* return : 現在のパス
***************************************************************/

const char	*get_menu_current_path( void )
{
	static char	path[MENU_PATH_MAX_LEN + 1];
	long	i;

	path[0] = '\0';
	for( i = 0; i < g_menu_current_path_n; i++ ){
		str_max_n_cat( path, g_menu_current_path[i],
				MENU_PATH_MAX_LEN );
	}

	return path;
}

/***************************************************************
* メニューの現在のパスに追加
* const char *path : 追加するパス
***************************************************************/

void	push_menu_current_path( const char *path )
{
	if( g_menu_current_path_n < 0 ){
		g_menu_current_path_n++;
		return;
	}
	if( g_menu_current_path_n >= MENU_CURRENT_PATH_MAX_N ){
		g_menu_current_path_n++;
		return;
	}

	str_nz_cpy( g_menu_current_path[g_menu_current_path_n],
			path, MENU_PATH_MAX_LEN );

	g_menu_current_path_n++;
}

/***************************************************************
* メニューの現在のパスを戻す
***************************************************************/

void	pop_menu_current_path( void )
{
	g_menu_current_path_n--;
}

/***************************************************************
* メニューのデフォルト項目の有効／無効を設定
* return : 有効か?
***************************************************************/

void	set_flg_menu_dflt( bool_t flg )
{
	g_flg_menu_dflt = flg;
}

/**/

/***************************************************************
* メニューのデフォルト項目が有効か?
* return : 有効か?
***************************************************************/

bool_t	get_flg_menu_dflt( void )
{
	return g_flg_menu_dflt;
}

/**/

bool_t	chk_err_menu_kind( menu_t *ls )
{
	bool_t	flg_err_ret;
	long	i, j;

	flg_err_ret = FALSE;

	for( i = 0; i < MENU_MAX_N; i++ ){
		bool_t	flg_ok;

		if( ls[i].path[0] == '\0' )
			break;

		flg_ok = FALSE;

		for( j = 0; j < LOOP_MAX_100; j++ ){
			if( menu_kind_ls[j] == NULL )
				break;

			if( strcmp( ls[i].kind, menu_kind_ls[j] ) == 0 ){
				flg_ok = TRUE;
				break;
			}
		}

		if( !flg_ok ){
			print_msg( FLG_MSG_DEBUG, MSG_ERR_MENU_KIND,
					ls[i].kind );
			flg_err_ret = TRUE;
		}
	}

	return flg_err_ret;
}

/**/

bool_t	set_menu_check_item( menu_t *p )
{
	if( chk_flg( p->flg, FLG_MENU_CHK_ON ) ){
		p->flg &= ~(FLG_MENU_CHK_ON);
		p->flg |= FLG_MENU_CHK_OFF;
	} else if( chk_flg( p->flg, FLG_MENU_CHK_OFF ) ){
		p->flg |= FLG_MENU_CHK_ON;
		p->flg &= ~(FLG_MENU_CHK_OFF);
	} else {
		return FALSE;
	}

	return TRUE;
}

/**/

bool_t	set_menu_radio_item( menu_t *ls, menu_t *p )
{
	long	i;
	const long	max_i = LOOP_MAX_4000;
	long	sep_begin_n, sep_end_n;

	sep_begin_n = 0;
	sep_end_n = 0;

	/* search begin <Separator> */

	for( i = 0; i < max_i; i++ ){
		if( ls[i].path[0] == '\0' )
			return FALSE;
		if( strcmp( ls[i].kind, "<Separator>" ) == 0 )
			sep_begin_n = i;
		if( &(ls[i]) == p )
			break;
	}
	if( i >= max_i )
		return FALSE;

	/* search end <Separator> */

	for( ; i < max_i; i++ ){
		if( ls[i].path[0] == '\0' )
			break;
		if( strcmp( ls[i].kind, "<Separator>" ) == 0 )
			break;
	}
	if( i >= max_i )
		return FALSE;
	sep_end_n = i;

	/* off other <RadioItem> */

	for( i = sep_begin_n; i <= sep_end_n; i++ ){
		if( strcmp( ls[i].kind, "<RadioItem>" ) == 0 ){
			ls[i].flg &= ~(FLG_MENU_CHK_ON);
			ls[i].flg |= FLG_MENU_CHK_OFF;
		}
	}

	/* on selected <RadioItem> */

	p->flg |= FLG_MENU_CHK_ON;
	p->flg &= ~(FLG_MENU_CHK_OFF);

	return TRUE;
}

/**/

ask_t	exec_menu_ask( const char *ttl, ask_t dflt, bool_t can_cancel )
{
	if( ttl != NULL )
		print_msg( FLG_NULL, MSG_S, ttl );

	return exec_menu_ask_no_msg( ttl, dflt, can_cancel );
}

/**/

ask_t	exec_menu_ask_no_msg(
	const char *ttl, ask_t dflt, bool_t can_cancel
)
{
	menu_t	*p;
	char	*str_goto;

	g_sel_ask = dflt;

	p = srch_menu( ls_menu_ask, "title" );
	if( p == NULL )
		return ASK_ERR;

	if( ttl == NULL )
		p->msg[0] = '\0';
	else
		str_nz_cpy( p->msg, ttl, MENU_MSG_MAX_BYTE );

	while( 1 ){
		str_goto = exec_menu( ls_menu_ask, NULL, NULL );

		if( str_goto != NULL ){
			if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
				g_sel_ask = ASK_CANCEL;
		}

		if( !can_cancel && (g_sel_ask == ASK_CANCEL) )
			continue;

		break;
	}

	clr_msg();

	return g_sel_ask;
}

/**/

char	*cb_menu_ask_init( menu_t **pp, menu_t **dflt )
{
	char	*sub_path;

	if( g_sel_ask == ASK_YES )
		sub_path = "yes";
	else
		sub_path = "no";

	*dflt = srch_menu( *pp, sub_path );
	if( *dflt == NULL )
		return STR_MENU_ERR;

	return NULL;
}

/**/

char	*cb_menu_ask_yes( menu_t **pp, menu_t **dflt )
{
	g_sel_ask = ASK_YES;

	return NULL;
}

/**/

char	*cb_menu_ask_no( menu_t **pp, menu_t **dflt )
{
	g_sel_ask = ASK_NO;

	return NULL;
}

/**/

char	*exec_menu_sel_num( long *p, long min, long max )
{
	long	n;
	long	figure;
	long	sel_n;
	char	num[FIGURE_MAX_N];
	const char	*fmt = "%+0*ld";
	long	i;

	if( p == NULL )
		return STR_MENU_ERR;

	n = *p;

	figure = 0;
	if( labs( min ) < labs( max ) )
		i = labs( max );
	else
		i = labs( min );
	for( ; i > 0; i /= 10 )
		figure++;
	if( figure < 1 )
		figure = 1;

	sel_n = 1 + figure + MENU_NUM_OK;
	while( 1 ){
		long	d;
		bool_t	flg_d;
		bool_t	flg_ret;
		char	key;

		sn_printf( num, FIGURE_MAX_N, fmt, (int)(figure + 1), n );

		draw_menu_num( figure, sel_n, num );

		key = get_key_buf_char();
		if( key == '\0' ){
			if( g_flg_gui ){
				call_gui_num_draw( &n, min, max,
						figure );
			}

			key = get_key( g_flg_clr_key_buf_menu );
		}

		d = 0;
		flg_d = FALSE;
		flg_ret = FALSE;

		switch( key ){
		case CASE_CANCEL:
			call_gui_num_wipe();
			return STR_MENU_CANCEL;
		case ' ':
			if( g_flg_space_select ){
				flg_ret = TRUE;
				d = +1;
			}
			break;
		case CASE_ENTER:
			if( !g_flg_space_select ){
				flg_ret = TRUE;
				d = +1;
			}
			break;
		case CASE_EXEC:
			d = +-0;
			flg_d = TRUE;
			break;
		case CASE_CRSR_UP:
			d = +1;
			flg_d = TRUE;
			break;
		case CASE_CRSR_DOWN:
			d = -1;
			flg_d = TRUE;
			break;
		case CASE_CRSR_LEFT:
			sel_n--;
			if( sel_n < 0 ){
				sel_n = 1 + figure + MENU_NUM_MAX_N - 1;
			}
			break;
		case CASE_CRSR_RIGHT:
			sel_n++;
			if( sel_n > 1 + figure + MENU_NUM_MAX_N - 1 )
				sel_n = 0;
			break;
		case '|':
			break;
		case KEY_MENU_NUM_OK:
			sel_n = 1 + figure + MENU_NUM_OK;
			break;
		case KEY_MENU_NUM_CLR:
			sel_n = 1 + figure + MENU_NUM_CLR;
			break;
		case KEY_MENU_NUM_MAX:
			sel_n = 1 + figure + MENU_NUM_MAX;
			break;
		case KEY_MENU_NUM_MIN:
			sel_n = 1 + figure + MENU_NUM_MIN;
			break;
		case KEY_MENU_NUM_SGN:
			sel_n = 0;
			break;
		default:
			if( ('A' <= key) && (key <= 'A' + figure - 1) )
				sel_n = 1 + figure - (key - 'A') - 1;
			break;
		}

		if( flg_d || flg_ret ){
			if( sel_n == 1 + figure + MENU_NUM_OK ){
				if( flg_ret ){
					if( n < min ){
						n = min;
					} else if( n > max ){
						n = max;
					} else {
						*p = n;
						call_gui_num_wipe();
						return NULL;
					}
				}
			} else if( sel_n == 1 + figure + MENU_NUM_MIN ){
				if( flg_ret )
					n = min;
			} else if( sel_n == 1 + figure + MENU_NUM_MAX ){
				if( flg_ret )
					n = max;
			} else if( sel_n == 1 + figure + MENU_NUM_CLR ){
				if( flg_ret )
					n = *p;
			} else if( sel_n == 0 ){
				if( num[0] == '-' )
					num[0] = '+';
				else
					num[0] = '-';

				n = strtol( num, (char **)NULL, 10 );
			} else {
				long	m;

				if( d == +-0 )
					m = 0;
				else
					m = num[sel_n] - '0' + d;

				if( m > 9 )
					m = 0;
				if( m < 0 )
					m = 9;
				num[sel_n] = (char)('0' + m);

				n = strtol( num, (char **)NULL, 10 );
			}
		}
	}

	call_gui_num_wipe();
	return STR_MENU_ERR;
}

/**/

void	sel_menu_clr( draw_menu_t *data )
{
	long	pre_n;

	pre_n = data->sel_n;
	data->sel_n = DRAW_MENU_CLR_N;

	draw_menu( data );

	data->sel_n = pre_n;
}

/**/

menu_t	*sel_menu( menu_t *p, menu_t *dflt )
{
	menu_t	*res;

	res = sel_menu_sub( p, dflt );
	g_sel_menu_accel_key = '\0';

	return res;
}

/**/

menu_t	*sel_menu_sub( menu_t *p, menu_t *dflt )
{
	static draw_menu_t	data;
	menu_t	*tmp_p;
	long	page_sel_n, page_max_n;
	long	n, sel_n, max_n;
	bool_t	flg_head;
	bool_t	flg_set_dflt;
	char	str_path[MENU_PATH_MAX_LEN + 1];
	int	i;

	if( p == NULL )
		return NULL;

	page_sel_n = 0;
	page_max_n = 0;
	sel_n = 0;
	max_n = 0;
	tmp_p = p;
	flg_head = TRUE;

	for( i = 0, n = 0; i < LOOP_MAX_4000; i++ ){
		tmp_p++;
		tmp_p = srch_next_menu( p, tmp_p, TRUE );
		if( tmp_p == NULL )
			break;

		if( flg_head ){
			flg_head = FALSE;
			page_max_n++;
		}

		if( strcmp( tmp_p->kind, "<Title>" ) == 0 ){
			;
		} else if( strcmp( tmp_p->kind, "<Separator>" ) == 0 ){
			;
		} else if( strcmp( tmp_p->kind, "<PageSeparator>" ) == 0 ){
			n = 0;
			flg_head = TRUE;
		} else {
			if( tmp_p == dflt ){
				page_sel_n = page_max_n - 1;
				sel_n = n;
			}

			n++;
		}
	}

	max_n = set_ls_menu( &data, p, page_sel_n );
	if( max_n <= 0 )
		return NULL;

	flg_set_dflt = TRUE;

	while( 1 ){
		long	dx, dy;
		long	key;
		long	i;

		data.sel_n = sel_n;
		data.page_sel_n = page_sel_n;
		data.page_max_n = page_max_n;
		if( page_sel_n == 0 )
			data.flg_min_page = TRUE;
		else
			data.flg_min_page = FALSE;
		if( page_sel_n == page_max_n - 1 )
			data.flg_max_page = TRUE;
		else
			data.flg_max_page = FALSE;

		draw_menu( &data );
		data.flg_redraw = FALSE;
		if( flg_set_dflt ){
			call_set_mouse_dflt_menu( sel_n );
			flg_set_dflt = FALSE;
		}

		dx = 0;
		dy = 0;

		g_sel_menu_accel_key = data.ls[sel_n]->accel_key;
		key = get_key( g_flg_clr_key_buf_menu );

		switch( key ){
		case '\0':
			break;
		default:
			for( i = 0; i < max_n; i++ )
				if( data.ls[i]->accel_key == key )
					break;
			if( i >= max_n )
				break;

			call_game_sound_play(
					SOUND_KIND_MENU_SELECT,
					1 );
			sel_n = i;
			sel_menu_clr( &data );
			return( data.ls[sel_n] );
		case ' ':
			if( g_flg_space_select ){
				/* 項目を選択 */
				call_game_sound_play(
						SOUND_KIND_MENU_SELECT,
						1 );
				sel_menu_clr( &data );
				return( data.ls[sel_n] );
			} else {
				break;
			}
		case CASE_ENTER:
			if( g_flg_space_select ){
				/* メニューを閉じる */
				call_game_sound_play(
						SOUND_KIND_MENU_CANCEL,
						1 );
				sel_menu_clr( &data );
				return NULL;
			} else {
				/* 項目を選択 */
				call_game_sound_play(
						SOUND_KIND_MENU_SELECT,
						1 );
				sel_menu_clr( &data );
				return( data.ls[sel_n] );
			}
		case CASE_CANCEL:
			/* メニューを閉じる */
			call_game_sound_play(
					SOUND_KIND_MENU_CANCEL,
					1 );
			sel_menu_clr( &data );
			return NULL;
		case CASE_CRSR_UP:
			dy = -1;
			break;
		case CASE_CRSR_DOWN:
			dy = +1;
			break;
		case CASE_CRSR_LEFT:
			dx = -1;
			break;
		case CASE_CRSR_RIGHT:
			dx = +1;
			break;
		case CASE_CRSR_UP_LEFT:
			dx = -1;
			dy = -1;
			break;
		case CASE_CRSR_UP_RIGHT:
			dx = +1;
			dy = -1;
			break;
		case CASE_CRSR_DOWN_LEFT:
			dx = -1;
			dy = +1;
			break;
		case CASE_CRSR_DOWN_RIGHT:
			dx = +1;
			dy = +1;
			break;
		case '<':
			dx = 0 - page_sel_n;
			break;
		case '>':
			dx = (page_max_n - 1) - page_sel_n;
			break;
		case '/':
			call_game_sound_play(
					SOUND_KIND_MENU_CANCEL,
					1 );
			return &dummy_menu_close_menu;
			break;
		case 'g':
			call_game_sound_play(
					SOUND_KIND_MENU_SELECT,
					1 );

			exec_back_log();

			call_game_sound_play(
					SOUND_KIND_MENU_CANCEL,
					1 );
			break;
		case MENU_COMMAND_KEY_CHAR:
			str_nz_cpy( str_path, MENU_COMMAND_KEY_STR,
					MENU_PATH_MAX_LEN );
			str_max_n_cat( str_path, get_menu_current_path(),
					MENU_PATH_MAX_LEN );
			str_max_n_cat( str_path, data.ls[sel_n]->path,
					MENU_PATH_MAX_LEN );
			str_max_n_cat( str_path, "\n",
					MENU_PATH_MAX_LEN );

			set_reg_macro( TRUE );
			reg_macro_str( str_path );
			set_reg_macro( FALSE );
			break;
		}

		if( dy != +-0 ){
			sel_n += dy;
			sel_n += max_n;
			sel_n %= max_n;
		}
		if( dx != +-0 ){
			page_sel_n += dx;
			page_sel_n += page_max_n;
			page_sel_n %= page_max_n;

			sel_menu_clr( &data );

			max_n = set_ls_menu( &data, p, page_sel_n );

			if( max_n <= 0 )
				return NULL;
			if( sel_n > max_n - 1 )
				sel_n = max_n - 1;
		}
	}

	return NULL;
}

/**/

long	set_ls_menu(
	draw_menu_t *data,
	menu_t *p,
	long page_sel_n
)
{
	long	n;
	long	page_n;
	menu_t	*tmp_p;
	bool_t	key_tab[256];
	long	i;

	if( p == NULL )
		return 0;

	data->ttl = NULL;
	data->ls[0] = NULL;
	data->sel_n = 0;
	data->prev_sel_n = 0;
	data->page_sel_n = 0;
	data->page_max_n = 0;
	data->flg_min_page = FALSE;
	data->flg_max_page = FALSE;
	data->flg_redraw = TRUE;

	for( i = 0; i < 256; i++ )
		key_tab[i] = FALSE;

	n = 0;
	page_n = 0;
	tmp_p = p;
	for( i = 0; i < LOOP_MAX_4000; i++ ){
		tmp_p++;
		tmp_p = srch_next_menu( p, tmp_p, TRUE );
		if( tmp_p == NULL )
			break;

		if( tmp_p->msg[0] == '\0' )
			str_nz_cpy( tmp_p->msg, MSG( tmp_p->n_msg ),
					MENU_MSG_MAX_BYTE );

		if( page_n == page_sel_n ){
			const char	*fmt = MSG_ERR_MENU_ACCEL_KEY;

			if( strcmp( tmp_p->kind, "<Title>" ) == 0 ){
				data->ttl = tmp_p->msg;
			} else if( strcmp( tmp_p->kind,
					"<Separator>" ) == 0 ){
				;
			} else if( strcmp( tmp_p->kind,
					"<PageSeparator>" ) == 0 ){
				;
			} else {
				do {
					if( !g_flg_debug )
						break;
					if( tmp_p->accel_key == '\0' )
						break;
					if( !key_tab[tmp_p->accel_key] )
						break;

					print_msg( FLG_MSG_ERR,
							fmt,
							tmp_p->accel_key,
							tmp_p->msg );
				} while( 0 );

				key_tab[tmp_p->accel_key] = TRUE;
				data->ls[n] = tmp_p;
				n++;
				data->ls[n] = NULL;
			}
		}
		if( page_n > page_sel_n )
			break;
		if( strcmp( tmp_p->kind, "<PageSeparator>" ) == 0 ){
			if( page_n == page_sel_n )
				break;
			page_n++;
		}
	}

	if( data->sel_n > n )
		data->sel_n = n;

	return n;
}

/**/

menu_t	*srch_menu( menu_t *ls, const char *sub_path )
{
	long	idx;
	menu_t *p;

	if( ls == NULL )
		return NULL;
	if( ls->path[0] == '\0' )
		return NULL;
	if( sub_path == NULL )
		return NULL;

	idx = str_len_std( ls->path ) + 1;
	for( p = &(ls[1]); p->path[0] != '\0'; p++ ){
		p = srch_next_menu( ls, p, FALSE );
		if( p == NULL )
			return NULL;

		if( strcmp( &(p->path[idx]), sub_path ) == 0 )
			return p;
	}

	return NULL;
}

/**/

menu_t	*srch_next_menu(
	menu_t *ls, menu_t *p, bool_t flg_skip_hidden
)
{
	long	idx;

	if( ls == NULL )
		return NULL;
	if( p == NULL )
		return NULL;
	if( ls->path[0] == '\0' )
		return NULL;
	if( p->path[0] == '\0' )
		return NULL;

	if( strcmp( ls->path, "/" ) == 0 )
		idx = 0;
	else
		idx = str_len_std( ls->path );

	for( ; ; p++ ){
		if( p->path[0] == '\0' )
			return NULL;

		if( idx > 0 )
			if( strncmp( ls->path, p->path, idx ) != 0 )
				return NULL;

		if( flg_skip_hidden )
			if( chk_flg( p->flg, FLG_MENU_HIDDEN ) )
				continue;

		if( strchr( &(p->path[idx + 1]), '/' ) == NULL )
			return p;
	}

	return NULL;
}

/**/

menu_t	*srch_goto_menu( menu_t *p, char *str_goto )
{
	long	len_goto;
	menu_t *tmp_p;

	if( p == NULL )
		return NULL;
	if( p->path[0] == '\0' )
		return NULL;
	if( str_goto == NULL )
		return NULL;
	if( strcmp( p->kind, "<Branch>" ) != 0 )
		return NULL;

	len_goto = str_len_std( str_goto );

	for( tmp_p = &p[1]; tmp_p->path[0] != '\0'; tmp_p++ ){
		long	len;

		len = str_len_std( p->path );
		if( strncmp( tmp_p->path, p->path, len ) != 0 )
			return NULL;

		len = str_len_std( tmp_p->path );
		if( strncmp( tmp_p->path, str_goto, len ) == 0 ){
			if( len == len_goto ){
				return tmp_p;
			} else if( len < len_goto ){
				if( str_goto[len] == '/' )
					return tmp_p;
			} else {
				return NULL;
			}
		}
	}

	return NULL;
}

/**/

void	set_chk_on_menu( menu_t *p, char *sub_path )
{
	set_flg_menu( p, sub_path, FLG_MENU_CHK_ON );
	clr_flg_menu( p, sub_path, FLG_MENU_CHK_OFF );
}

/**/

void	set_chk_off_menu( menu_t *p, char *sub_path )
{
	clr_flg_menu( p, sub_path, FLG_MENU_CHK_ON );
	set_flg_menu( p, sub_path, FLG_MENU_CHK_OFF );
}

/**/

bool_t	set_flg_menu( menu_t *p, char *sub_path, unsigned long flg )
{
	return equ_flg_menu( p, sub_path, flg, TRUE );
}

/**/

bool_t	clr_flg_menu( menu_t *p, char *sub_path, unsigned long flg )
{
	return equ_flg_menu( p, sub_path, flg, FALSE );
}

/**/

bool_t	equ_flg_menu(
	menu_t *p, char *sub_path, unsigned long flg, bool_t flg_set
)
{
	static char	path[255 + 1];
	const long	len = sizeof( path ) - 1;
	menu_t	*tmp_p;
	bool_t	flg_find;

	if( p == NULL )
		return FALSE;

	path[0] = '\0';
	if( sub_path != NULL ){
		if( strcmp( p->path, "/" ) != 0 )
			str_nz_cpy( path, p->path, len );
		str_max_n_cat( path, "/", len );
		str_max_n_cat( path, sub_path, len );
	}

	flg_find = FALSE;
	for( tmp_p = &p[1]; tmp_p->path[0] != '\0'; tmp_p++ ){
		tmp_p = srch_next_menu( p, tmp_p, FALSE );
		if( tmp_p == NULL )
			break;

		if( sub_path != NULL )
			if( strcmp( tmp_p->path, path ) != 0 )
				continue;

		if( flg_set )
			tmp_p->flg |= flg;
		else
			tmp_p->flg &= ~flg;

		flg_find = TRUE;
	}

	if( !flg_find && (sub_path != NULL) )
		print_msg( FLG_NULL, MSG_ERR_MENU_SRCH_PATH, path );

	return flg_find;
}

/**/

void	wait_key( bool_t flg_can_move_crsr )
{
	print_msg( FLG_NULL, MSG_WAIT_KEY );

	wait_key_ex( FALSE, flg_can_move_crsr );
}

/**/

void	wait_key_ex( bool_t flg_exec_key, bool_t flg_can_move_crsr )
{
	long	c;

	while( 1 ){
		if( flg_can_move_crsr )
			c = chk_key( g_flg_clr_key_buf, FALSE );
		else
			c = get_key( g_flg_clr_key_buf );

		switch( c ){
		case CASE_CANCEL:
		case ' ':
		case CASE_ENTER:
			return;
		case CASE_EXEC:
			if( flg_exec_key )
				return;
			break;
		default:
			break;
		}
	}
}

/**/

long	chk_key( bool_t flg_clr_key_buf, bool_t flg_chk_menu )
{
	long	c;

	g_flg_chk_menu = flg_chk_menu;

	wipe_menu();
	reset_crsr();

	c = get_key( flg_clr_key_buf );

	if( flg_chk_menu )
		clr_msg();

	switch( c ){
	case '\0':
	case ' ':
	case CASE_CANCEL:
		break;
	case CASE_ENTER:
	case 'M':
	case 'm':
		/* メニューの表示 */
		if( flg_chk_menu ){
			move_all_mbr_trgt();
			clr_menu_current_path();
			exec_menu( get_ls_menu_main(),
					get_menu_dflt_main(), NULL );
			wipe_menu();
		}
		break;

#ifdef	HAVE_LIBCURSES
	case KEY_RESIZE:
		redraw_all();
		break;
#endif	/* HAVE_LIBCURSES */

	default:
		g_flg_chk_short_key = TRUE;

		if( chk_short_key( get_ls_menu_move_crsr(), c ) ){
			wipe_menu();
			break;
		}
		if( flg_chk_menu ){
			if( chk_short_key( get_ls_menu_main(), c ) ){
				wipe_menu();
				break;
			}
			if( chk_short_key( get_ls_menu_sel_obj(), c ) ){
				wipe_menu();
				break;
			}
		}
		if( chk_short_key( get_ls_menu_macro_func(), c ) ){
			wipe_menu();
			break;
		}
		if( chk_short_key( get_ls_menu_macro_mouse(), c ) ){
			wipe_menu();
			break;
		}
		if( chk_short_key( get_ls_menu_macro_joystick(), c ) ){
			wipe_menu();
			break;
		}

		if( flg_chk_menu ){
			print_msg( FLG_NULL, MSG_ERR_CHK_KEY,
					(unsigned char)c, (long)c );
		}
		break;
	}

	if( chk_redraw_every_turn() )
		force_clr_redraw_map();

	if( g_flg_echo_key ){
		if( (c != '\0') && (c != -1) ){
			long	cc;

			if( isprint( c ) )
				cc = c;
			else
				cc = ' ';

			print_msg( FLG_MSG_NO_MORE,
					MSG_ECHO_KEY,
					(unsigned char)cc, (long)c );
		}
	}

	g_flg_chk_short_key = FALSE;

	update_crsr();

	return c;
}

/**/

void	chk_dup_short_key( void )
{
	chk_dup_short_key_init();
	chk_dup_short_key_main( get_ls_menu_move_crsr() );
	chk_dup_short_key_main( get_ls_menu_main() );
	chk_dup_short_key_main( get_ls_menu_sel_obj() );
}

/**/

void	chk_dup_short_key_init( void )
{
	long	i;

	for( i = 0; i < 256; i++ ){
		g_flg_dup_short_key[i] = FALSE;
	}
}

/**/

bool_t	chk_dup_short_key_main( menu_t *ls )
{
	menu_t	*p;

	for( p = ls; p->path[0] != '\0'; p++ ){
		char	*cp;

		for( cp = p->short_key; *cp != '\0'; cp++ ){
			if( isspace( *cp ) ){
				continue;
			} else if( *cp == '\\' ){
				cp++;
				if( *cp == '\0' )
					break;
			} else if( *cp == '^' ){
				cp++;
				if( *cp == '\0' )
					break;

				chk_dup_short_key_sub( *cp - '@', p );
				continue;
			}

			chk_dup_short_key_sub( *cp, p );
		}
	}

	return TRUE;
}

/**/

bool_t	chk_dup_short_key_sub( unsigned char c, menu_t *ls )
{
	if( g_flg_dup_short_key[c] ){
		char	s[8 + 1];

		if( ('A' - '@' <= c) && (c <= 'Z' - '@') )
			sn_printf( s, 8, "^%c", c + '@' );
		else
			sn_printf( s, 8, "%c", c );

		print_err( MSG_ERR_MENU_SHORT_CUT_KEY,
				s, MSG( ls->n_msg ) );
		return FALSE;
	}

	g_flg_dup_short_key[c] = TRUE;

	return TRUE;
}

/**/

bool_t	chk_short_key( menu_t *ls, long c )
{
	bool_t	flg_find = FALSE;
	menu_t	*p;

	if( ls == NULL )
		return FALSE;

	for( p = ls; p->path[0] != '\0'; p++ ){
		char	*cp;

		for( cp = p->short_key; *cp != '\0'; cp++ ){
			if( isspace( *cp ) ){
				continue;
			} else if( *cp == '\\' ){
				cp++;
				if( *cp == '\0' )
					return FALSE;
			} else if( *cp == '^' ){
				cp++;
				if( *cp == '\0' )
					return FALSE;
				if( *cp == '^' ){
					if( c == '^' ){
						flg_find = TRUE;
						break;
					}
				}
				if( *cp - '@' == c ){
					flg_find = TRUE;
					break;
				}
				continue;
			} else if( *cp == '&' ){
				long	f;

				/* Function Key */

				cp++;
				f = get_key_n( cp );
				while( *cp != '\0' ){
					if( isspace( *cp ) )
						break;
					cp++;
				}

				if( f == '\0' )
					continue;
				if( c != f )
					continue;

				flg_find = TRUE;
				break;
			}

			if( *cp == c ){
				flg_find = TRUE;
				break;
			}
		}
		if( flg_find ){
			exec_menu( ls, NULL, p->path );
			return TRUE;
		}
	}

	return FALSE;
}

/**/

menu_t	*get_ls_menu_macro_func( void )
{
	return ls_menu_macro_func;
}

/**/

menu_t	*get_ls_menu_macro_mouse( void )
{
	return ls_menu_macro_mouse;
}

/**/

menu_t	*get_ls_menu_macro_joystick( void )
{
	return ls_menu_macro_joystick;
}

/**/

char	*get_macro_str( long n )
{
	if( n < 0 )
		return g_macro_func[0];

	if( n < KEY_N_FUNC_MAX_N )
		return g_macro_func[n];
	n -= KEY_N_FUNC_MAX_N;

	if( n < KEY_N_MOUSE_CLICK_MAX_N )
		return g_macro_mouse_click[n];
	n -= KEY_N_MOUSE_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_D_CLICK_MAX_N )
		return g_macro_mouse_d_click[n];
	n -= KEY_N_MOUSE_D_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_P_CLICK_MAX_N )
		return g_macro_mouse_p_click[n];
	n -= KEY_N_MOUSE_P_CLICK_MAX_N;

	if( n < KEY_N_MOUSE_PRESS_MAX_N )
		return g_macro_mouse_press[n];
	n -= KEY_N_MOUSE_PRESS_MAX_N;

	if( n < KEY_N_MOUSE_RELEASE_MAX_N )
		return g_macro_mouse_release[n];
	n -= KEY_N_MOUSE_RELEASE_MAX_N;

	if( n < KEY_N_MOUSE_MOTION_MAX_N )
		return g_macro_mouse_motion[n];
	n -= KEY_N_MOUSE_MOTION_MAX_N;

	if( n < KEY_N_JOYSTICK_MAX_N ){
		long	jn;

		jn = call_game_joystick_get_kind();
		return g_macro_joystick[jn][n];
	}
	n -= KEY_N_JOYSTICK_MAX_N;

	return g_macro_func[0];
}

/**/

char	*get_macro_func( long n )
{
	if( n < 0 )
		return NULL;
	if( n >= KEY_N_FUNC_MAX_N )
		return NULL;

	return g_macro_func[n];
}

/**/

char	*get_macro_mouse_click( long n )
{
	if( n < 0 )
		return NULL;
	if( n >= KEY_N_MOUSE_CLICK_MAX_N )
		return NULL;

	return g_macro_mouse_click[n];
}

/**/

char	*get_macro_mouse_d_click( long n )
{
	if( n < 0 )
		return NULL;
	if( n >= KEY_N_MOUSE_D_CLICK_MAX_N )
		return NULL;

	return g_macro_mouse_d_click[n];
}

/**/

char	*get_macro_mouse_p_click( long n )
{
	if( n < 0 )
		return NULL;
	if( n >= KEY_N_MOUSE_P_CLICK_MAX_N )
		return NULL;

	return g_macro_mouse_p_click[n];
}

/**/

char	*get_macro_mouse_press( long n )
{
	if( n < 0 )
		return NULL;
	if( n >= KEY_N_MOUSE_PRESS_MAX_N )
		return NULL;

	return g_macro_mouse_press[n];
}

/**/

char	*get_macro_mouse_release( long n )
{
	if( n < 0 )
		return NULL;
	if( n >= KEY_N_MOUSE_RELEASE_MAX_N )
		return NULL;

	return g_macro_mouse_release[n];
}

/**/

char	*get_macro_mouse_motion( long n )
{
	if( n < 0 )
		return NULL;
	if( n >= KEY_N_MOUSE_MOTION_MAX_N )
		return NULL;

	return g_macro_mouse_motion[n];
}

/**/

char	*get_macro_joystick( long j, long n )
{
	if( j < 0 )
		return NULL;
	if( j >= JOY_KIND_MAX_N )
		return NULL;
	if( n < 0 )
		return NULL;
	if( n >= KEY_N_JOYSTICK_MAX_N )
		return NULL;

	return g_macro_joystick[j][n];
}

/**/

bool_t	get_flg_chk_menu( void )
{
	return g_flg_chk_menu;
}

/**/

bool_t	get_flg_chk_short_key( void )
{
	return g_flg_chk_short_key;
}

/**/

bool_t	get_flg_space_select( void )
{
	return g_flg_space_select;
}

/**/

bool_t	set_flg_space_select( bool_t flg )
{
	g_flg_space_select = flg;

	return g_flg_space_select;
}

/**/

long	get_sel_menu_accel_key( void )
{
	return g_sel_menu_accel_key;
}

/**/

bool_t	get_flg_move_crsr_dflt( void )
{
	return g_flg_move_crsr_dflt;
}

/**/

bool_t	set_flg_move_crsr_dflt( bool_t flg )
{
	g_flg_move_crsr_dflt = flg;

	return g_flg_move_crsr_dflt;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_menu_c( void )
{
	check_memory( check_memory_menu_c_g_nest_flg_executing_menu,
			"menu.c: g_nest_flg_executing_menu" );
	check_memory( check_memory_menu_c_g_menu_current_path_n,
			"menu.c: g_menu_current_path_n" );
	check_memory( check_memory_menu_c_g_sel_ask,
			"menu.c: g_sel_ask" );
	check_memory( check_memory_menu_c_menu_kind_ls,
			"menu.c: menu_kind_ls" );
	check_memory( check_memory_menu_c_dummy_menu_close_menu,
			"menu.c: dummy_menu_close_menu" );
	check_memory( check_memory_menu_c_g_macro_func,
			"menu.c: g_macro_func" );
	check_memory( check_memory_menu_c_g_ls_short_key_func,
			"menu.c: g_ls_short_key_func" );
	check_memory( check_memory_menu_c_g_flg_dup_short_key,
			"menu.c: g_flg_dup_short_key" );
}
