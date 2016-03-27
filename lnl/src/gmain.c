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
* $Id: gmain.c,v 1.154 2014/02/02 17:49:33 bowkenken Exp $
***************************************************************/

/***************************************************************
* メイン処理
***************************************************************/

#define	EXTERN

#define	GMAIN_C
#include	"inc.h"

/***************************************************************
* シェル
***************************************************************/

#define	STR_ENV_SHELL	"SHELL"

#ifdef	D_DOS
# define	STR_DFLT_SHELL	"command"
#else	/* D_DOS */
# define	STR_DFLT_SHELL	"sh"
#endif	/* D_DOS */

/***************************************************************
* キーの待ち時間
***************************************************************/

#define	KEY_WAIT_VMIN	0
#define	KEY_WAIT_VTIME	1

/***************************************************************
* 変数定義
***************************************************************/

static long	flg_term;
check_memory_def( check_memory_gmain_c_flg_term )

#if	defined( HAVE_TERMIOS_H )
static struct termios	pre_tbuf;
#elif	defined( HAVE_TERMIO_H )
static struct termio	pre_tbuf;
#endif
check_memory_def( check_memory_gmain_c_pre_tbuf )

/***************************************************************
* 引数
***************************************************************/

#define	OPT_ARG_MAX_LEN	128
#define	STR_OPT	"GCUM:A:N:P:l:es:p:m:cdVvh"

#ifdef	HAVE_GETOPT_LONG
static struct option	long_opt[] = {
	{ "gui",            no_argument,       NULL, 'G' },
	{ "cui",            no_argument,       NULL, 'C' },
	{ "gui-and-cui",    no_argument,       NULL, 'U' },
	{ "cui-mouse",      required_argument, NULL, 'M' },
	{ "audio-buf-size", required_argument, NULL, 'A' },
	{ "gnome",          required_argument, NULL, 'N' },
	{ "set-win-pos",    required_argument, NULL, 'P' },
	{ "language",       required_argument, NULL, 'l' },
	{ "echo-key",       no_argument,       NULL, 'e' },
	{ "use-curses",     required_argument, NULL, 's' },
	{ "use-keypad",     required_argument, NULL, 'p' },
	{ "check-memory",   required_argument, NULL, 'm' },
	{ "measure-clock",  no_argument,       NULL, 'c' },
	{ "debug",          no_argument,       NULL, 'd' },
	{ "version",        no_argument,       NULL, 'V' },
	{ "help",           no_argument,       NULL, 'h' },
	{ 0, 0, 0, 0 }
};
#endif	/* HAVE_GETOPT_LONG */
check_memory_def( check_memory_gmain_c_long_opt )

/***************************************************************
* 使用方
***************************************************************/

char	str_usage[] = {
	"Usage: %s [OPTION]...\n"
	"OPTION:\n"
	"  -G, --gui                 set GUI mode\n"
	"  -C, --cui                 set CUI mode\n"
	"  -U, --gui-and-cui         set GUI and CUI mode\n"
	"  -M, --cui-mouse=FLAG      use CUI mouse\n"
	"                              ON, OFF or SWAP\n"
	"  -A, --audio-buf-size=SIZE set audio buffer size\n"
	"  -N, --gnome=FLAG          window manager is GNOME\n"
	"                              ON or OFF\n"
	"  -P, --set-win-pos=FLAG    set window position\n"
	"                              ON or OFF\n"
	"  -l, --language=LANGUAGE   set language:\n"
	"                              language\n"
	"  -e, --echo-key            echo key\n"
	"  -s, --use-curses=FLAG     use curses library:\n"
	"                              ON or OFF\n"
	"  -p, --use-keypad=FLAG     use cursor key (call keypad):\n"
	"                              ON or OFF\n"
	"  -m, --check-memory=FLAG   check memory:\n"
	"                              ON or OFF\n"
	"  -c, --measure-clock       measure frame rate\n"
#if	defined( DEBUG ) || !defined( NDEBUG )
	"  -d, --debug               debugging mode\n"
#endif
	"  -V, -v, --version         display version and exit\n"
	"  -h, --help                display this help and exit\n"
};
check_memory_def( check_memory_gmain_c_str_usage )

typedef enum {
	OPT_ARG_KIND_FALSE,
	OPT_ARG_KIND_TRUE,
	OPT_ARG_KIND_SWAP,
} opt_arg_kind_t;

/***************************************************************
* ゲーム全体の初期化
***************************************************************/

void	init_game( void )
{
	dun_t	*dun;

	/* 各初期化処理の呼ぶ順番に気を付ける事 */

	g_flg_init = FALSE;

	reset_static();

	init_signal();
	init_scrn();

	srandm( (long)time( NULL ) );

	init_scene();
	init_turn();

	init_msg();
	init_draw();
	init_replay();
	init_playing_report();

	init_game_file();

	init_var_menu();
	init_var_main_menu();
	init_var_misc_menu();

	init_crsr_ptn();

	if( !load_game_conf() )
		g_flg_measure_clk_tck = TRUE;
	overwrite_arg();

	ena_scrn( TRUE );
	ena_curs_draw();
	wipe_all();

	init_dun();
	init_item();
	init_trap();
	init_fx();
	init_spell();
	init_skill();
	init_chr();
	init_town();
	init_menu();
	init_town_menu();
	init_auto_menu();
	init_misc_menu();
	init_main_menu();
	init_request();
	init_key_item();
	init_last_boss();
	init_ending();

	init_mbr_formation();

	if( g_flg_debug )
		init_spell_debug();
	else
		init_spell_dflt();
	init_spell_nin();

	if( g_flg_debug )
		set_flg_no_save( TRUE );

	if( g_flg_measure_clk_tck )
		measure_clk_tck();

	dun = get_dun();
	dun->lev = 0;
	up_dun( 0 );

	g_flg_init = TRUE;
}

/***************************************************************
* 全モジュールのスタティック変数をリセット
***************************************************************/

void	reset_static( void )
{
	reset_static_auto_menu();
	reset_static_chr();
	reset_static_curs();
	reset_static_draw();
	reset_static_dun();
	reset_static_fight();
	reset_static_fx();
	reset_static_game_file();
	reset_static_game_main();
	reset_static_misc_menu();
	reset_static_item();
	reset_static_menu();
	reset_static_misc();
	reset_static_main_menu();
	reset_static_mnstr_act();
	reset_static_mnstr();
	reset_static_msg();
	reset_static_nest_flg();
	reset_static_party();
	reset_static_pet();
	reset_static_replay();
	reset_static_request();
	reset_static_scene();
	reset_static_spell();
	reset_static_town_menu();
	reset_static_town();
	reset_static_trap();
	reset_static_turn();
	reset_static_last_boss();

#if	defined( D_GTK )
#elif	defined( D_WS )
#elif	defined( D_IPHONE )
#elif	defined( D_MFC )
#elif	defined( D_DOS )
	reset_static_main_dos();
#else
	reset_static_main_unix();
#endif
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_game_main( void )
{
}

/***************************************************************
* メイン・ループ
***************************************************************/

void	game_main( void )
{
	call_alloc_autorelease_pool();

	chk_scroll( TRUE );
	redraw_all();
	scroll_center_appear_party();

	if( g_flg_debug ){
		menu_load_wiz();

		if( !g_flg_gui && g_flg_cui )
			change_scene( SCENE_N_TOWN );
	} else {
		print_msg( FLG_NULL, MSG_HINT_CANCEL_MENU_1 );
		print_msg( FLG_NULL, MSG_HINT_CANCEL_MENU_2 );

		menu_load_start();

		if( !g_flg_gui && g_flg_cui )
			change_scene( SCENE_N_TOWN );

		if( g_load_slot_n != SAVE_N_AUTO )
			party_exit_bar();
	}

	call_release_autorelease_pool();

	while( 1 ){
		call_alloc_autorelease_pool();
		chk_key( g_flg_clr_key_buf, TRUE );
		call_release_autorelease_pool();
	}
}

/***************************************************************
* ゲーム・オーバー
***************************************************************/

void	game_over( void )
{
	change_scene( SCENE_N_GAME_OVER );

	print_msg( FLG_MSG_NO_MORE_PREV, MSG_S, MSG_GAME_OVER );
	while( 1 ){
		switch( get_key( FALSE ) ){
		case CASE_EXIT:
			exit_game( EXIT_SUCCESS );
			break;
		}
	}
}

/***************************************************************
* エンディング
***************************************************************/

void	ending( void )
{
	long	c;

	change_scene( SCENE_N_ENDING );

	while( 1 ){
		draw_ending();

		c = get_key_no_wait();
		if( c > 0 ){
			switch( c ){
			case CASE_EXIT:
				exit_game( EXIT_SUCCESS );
				break;
			case 'S':
				set_flg_skip_scene_ending( TRUE );
				call_demo_ending_skip_scene();
				break;
			case CASE_CRSR_UP:
				add_z_speed_space( +1 );
				break;
			case CASE_CRSR_DOWN:
				add_z_speed_space( -1 );
				break;
			}
		}
	}
}

/***************************************************************
* 引数の初期化
***************************************************************/

void	init_arg( void )
{
	g_flg_debug = FALSE;
#ifdef	DEBUG
	g_flg_debug = TRUE;
#endif	/* DEBUG */
#ifdef	NDEBUG
	g_flg_debug = FALSE;
#endif	/* NDEBUG */

	g_flg_cui = TRUE;
	g_flg_gui = FALSE;
	g_flg_cui_mouse = FALSE;
	g_flg_cui_mouse_swap_btn = FALSE;

	g_audio_buf_siz_arg_overwrite = FALSE;
	g_audio_buf_siz_arg = 1024;
	g_audio_buf_siz = 1024;

	g_flg_win_pos_arg_overwrite = FALSE;
	g_flg_gnome_arg = TRUE;
	g_flg_gnome = TRUE;
	g_flg_set_win_pos_arg = TRUE;
	g_flg_set_win_pos = TRUE;

	g_flg_text_mode = FALSE;
	g_text_mode_point = 0;

	g_graph_scale_rate = _100_PERCENT;
	g_gui_key_kind = GUI_KEY_KIND_CONSOLE;

	g_language = NULL;

	g_flg_clr_key_buf_arg_overwrite = FALSE;
	g_flg_clr_key_buf_arg = FALSE;
	g_flg_clr_key_buf = TRUE;
	g_flg_clr_key_buf_menu = TRUE;

	g_flg_echo_key = FALSE;

	g_flg_use_curs = TRUE;
	g_flg_use_keypad = TRUE;

	g_flg_measure_clk_tck = FALSE;
	g_flg_check_memory = TRUE;

	g_flg_send_item_exec_turn = FALSE;
}

/***************************************************************
* 引数の処理
* int argc : 引数の数
* char **argv : 引数のリスト
***************************************************************/

void	chk_arg( int argc, char **argv )
{
	long	len;
	long	mem_size;
#if	!defined( HAVE_GETOPT ) && !defined( HAVE_GETOPT_LONG )
	long	n = 0;
	char	*optarg;
	long	optind = argc;
#endif	/* !defined( HAVE_GETOPT ) && !defined( HAVE_GETOPT_LONG ) */

	if( argv == NULL )
		return;

	while( 1 ){
		long	c;
#ifdef	HAVE_GETOPT_LONG
		int	opt_idx;
#endif	/* HAVE_GETOPT_LONG */

#if	defined( HAVE_GETOPT_LONG )
		c = getopt_long( argc, argv, STR_OPT, long_opt, &opt_idx );
#elif	defined( HAVE_GETOPT )
		c = getopt( argc, argv, STR_OPT );
#else	/* HAVE_GETOPT_LONG */
		n++;
		if( n > argc - 1 )
			break;
		optarg = argv[n + 1];

		if( argv[n][0] == '-' )
			c = argv[n][1];
		else
			continue;
#endif	/* HAVE_GETOPT_LONG */

		if( c <= -1 )
			break;
		switch( c ){
		case 'G':
			g_flg_cui = FALSE;
			g_flg_gui = TRUE;
			break;
		case 'C':
			g_flg_cui = TRUE;
			g_flg_gui = FALSE;
			break;
		case 'U':
			g_flg_cui = TRUE;
			g_flg_gui = TRUE;
			break;
		case 'M':
			chk_opt_flg( optarg, &g_flg_cui_mouse, TRUE );
			if( g_flg_cui_mouse == OPT_ARG_KIND_SWAP ){
				g_flg_cui_mouse = TRUE;
				g_flg_cui_mouse_swap_btn = TRUE;
			} else if( g_flg_cui_mouse ){
				g_flg_cui_mouse = TRUE;
				g_flg_cui_mouse_swap_btn = FALSE;
			} else {
				g_flg_cui_mouse = FALSE;
				g_flg_cui_mouse_swap_btn = FALSE;
			}
			break;
		case 'A':
			g_audio_buf_siz_arg_overwrite = TRUE;
			chk_opt_num( optarg, &g_audio_buf_siz_arg, TRUE );
			break;
		case 'N':
			g_flg_win_pos_arg_overwrite = TRUE;
			chk_opt_flg( optarg, &g_flg_gnome_arg, TRUE );
			break;
		case 'P':
			g_flg_win_pos_arg_overwrite = TRUE;
			chk_opt_flg( optarg, &g_flg_set_win_pos_arg, TRUE );
			break;
		case 'l':
			if( g_language != NULL )
				free_mem( g_language );

			len = str_len_std( optarg );
			mem_size = len * sizeof( char );
			g_language = (char *)alloc_mem( mem_size, TRUE );

			str_nz_cpy( g_language, optarg, len );
			break;
		case 'e':
			g_flg_echo_key = TRUE;
			break;
		case 's':
			chk_opt_flg( optarg, &g_flg_use_curs, TRUE );
			break;
		case 'p':
			chk_opt_flg( optarg, &g_flg_use_keypad, TRUE );
			break;
		case 'm':
			chk_opt_flg( optarg, &g_flg_check_memory, TRUE );
			break;
		case 'c':
			g_flg_measure_clk_tck = TRUE;
			break;
		case 'd':
			g_flg_debug = TRUE;
			break;
		case 'V':
		case 'v':
			version( stdout );
			gexit( EXIT_SUCCESS );
			break;
		case 'h':
			usage( stdout );
			gexit( EXIT_SUCCESS );
			break;
		case '\0':
			break;
		case '?':
		case ':':
		default:
			usage( stderr );
			gexit( EXIT_FAILURE );
			break;
		}
	}

	if( (argc - optind) > 0 ){
		usage( stderr );
		gexit( EXIT_FAILURE );
	}

	if( g_flg_gui || !g_flg_cui )
		g_flg_cui_mouse = FALSE;
}

/***************************************************************
* 数値の引数をチェック
* const char *optarg : オプション文字列
* long *pn : 数値を返す
* bool_t flg_err_exit : エラーで終了するか?
* return : エラーが無かったか?
***************************************************************/

bool_t	chk_opt_num(
	const char *optarg, long *pn, bool_t flg_err_exit
)
{
	do {
		if( optarg == NULL )
			break;
		if( pn == NULL )
			break;
		if( !isdigit( optarg[0] ) )
			break;

		/* 数値が指定された */

		*pn = strtol( optarg, NULL, 0 );

		return TRUE;
		break;
	} while( 0 );

	/* エラー */

	if( flg_err_exit ){
		usage( stderr );
		gexit( EXIT_FAILURE );
	}

	return FALSE;
}

/***************************************************************
* 引数のオン／オフのフラグをチェック
* const char *optarg : オプション文字列
* bool_t *flg : フラグがオンかどうかを返す
* bool_t flg_err_exit : エラーで終了するか?
* return : エラーが無かったか?
***************************************************************/

bool_t	chk_opt_flg(
	const char *optarg, bool_t *flg, bool_t flg_err_exit
)
{
	static char	str[OPT_ARG_MAX_LEN + 1];
	long	i;

	if( optarg == NULL ){
		if( flg_err_exit ){
			usage( stderr );
			gexit( EXIT_FAILURE );
		}

		return FALSE;
	}

	for( i = 0; i < OPT_ARG_MAX_LEN; i++ ){
		if( optarg[i] == '\0' )
			break;
		str[i] = toupper( optarg[i] );
	}
	str[i] = '\0';

	*flg = TRUE;
	if( strcmp( str, "ON" ) == 0 )
		return TRUE;
	if( strcmp( str, "TRUE" ) == 0 )
		return TRUE;
	if( strcmp( str, "T" ) == 0 )
		return TRUE;
	if( strcmp( str, "YES" ) == 0 )
		return TRUE;
	if( strcmp( str, "1" ) == 0 )
		return TRUE;

	*flg = FALSE;
	if( strcmp( str, "OFF" ) == 0 )
		return TRUE;
	if( strcmp( str, "FALSE" ) == 0 )
		return TRUE;
	if( strcmp( str, "NIL" ) == 0 )
		return TRUE;
	if( strcmp( str, "NO" ) == 0 )
		return TRUE;
	if( strcmp( str, "0" ) == 0 )
		return TRUE;

	*flg = OPT_ARG_KIND_SWAP;
	if( strcmp( str, "SWAP" ) == 0 )
		return TRUE;

	*flg = FALSE;

	if( flg_err_exit ){
		usage( stderr );
		gexit( EXIT_FAILURE );
	}

	return FALSE;
}

/***************************************************************
* 引数で指定された設定を上書き
***************************************************************/

void	overwrite_arg()
{
	if( g_flg_clr_key_buf_arg_overwrite ){
		g_flg_clr_key_buf = g_flg_clr_key_buf_arg;
		g_flg_clr_key_buf_menu = g_flg_clr_key_buf_arg;
	}

	if( g_flg_win_pos_arg_overwrite ){
		g_flg_gnome = g_flg_gnome_arg;
		g_flg_set_win_pos = g_flg_set_win_pos_arg;
	}

	if( g_audio_buf_siz_arg_overwrite ){
		g_audio_buf_siz = g_audio_buf_siz_arg;
	}
}

/***************************************************************
* 使用方の表示
* FILE *fp : 出力先ファイル
***************************************************************/

void	usage( FILE *fp )
{
	fprintf( fp, str_usage, STR_FILE_NAME_GAME );
	fflush( fp );
}

/***************************************************************
* ゲームの終了
* long code : 終了コード
***************************************************************/

void	exit_game( long code )
{
	close_game( code );

	gexit( code );
}

/***************************************************************
* ゲームの終了前の処理
* long code : 終了コード
***************************************************************/

void	close_game( long code )
{
	call_close_game_gui();

	close_item();

	if( !g_flg_use_curs )
		curs_move( get_screen_row() - 1, SCREEN_MIN_X );

	reset_scrn();
	fflush( stdout );
	fflush( stderr );

	if( code == 0 )
		version( stdout );
	else
		version( stderr );

	fflush( stdout );
	fflush( stderr );
}

/***************************************************************
* ゲームの説明を表示
***************************************************************/

void	about_game( bool_t flg_init )
{
	static char	tmp[1023 + 1];

#if	defined( D_WS ) || defined( D_GTK ) || defined( D_DOWS )
	if( flg_init )
		return;
#endif

	if( g_flg_gui ){
		const long	max_len = 80 * 40;
		static char	str[80 * 40 + 1];

		sn_printf( str, max_len, MSG_FMT_COPYRIGHT,
				LS_STR_COPYRIGHT );
		str_max_n_cat( str, MSG_ABOUT_GAME, max_len );

		call_gui_words_draw_width( NULL, str, 80 );

		return;
	}

	curs_move( get_map_row() + 1, SCREEN_MIN_X );

	dis_scrn();

	fprintf( OUT_FP, MSG_FMT_COPYRIGHT, LS_STR_COPYRIGHT );
	fprintf( OUT_FP, "\n%s\n", MSG_HIT_ENTER_KEY );
	fflush( OUT_FP );
	fgets( tmp, sizeof( tmp ) - 1, stdin );

	fprintf( OUT_FP, MSG_S, MSG_ABOUT_GAME );
	fprintf( OUT_FP, "\n%s\n", MSG_HIT_ENTER_KEY );
	fflush( OUT_FP );
	fgets( tmp, sizeof( tmp ) - 1, stdin );

	ena_scrn( FALSE );
}

/***************************************************************
* ゲームのバージョンを表示
* FILE *fp : 出力先ファイル
***************************************************************/

void	version( FILE *fp )
{
	fprintf( fp, STR_FMT_COPYRIGHT, LS_STR_COPYRIGHT );
	fflush( fp );
}

/***************************************************************
* シェルを呼び出す
***************************************************************/

void	child_ps( void )
{
#ifdef	D_DOS
	child_ps_dos();
#else	/* D_DOS */
	child_ps_unix();
#endif	/* D_DOS */
}

/***************************************************************
* シグナルの初期化
***************************************************************/

void	init_signal( void )
{
#ifdef	D_X68K
	signal( SIGINT, signal_handler );
	signal( SIGABRT, signal_handler );
	signal( SIGTERM, signal_handler );
#elif	defined( D_DOS )
	signal( SIGINT, signal_handler );
	signal( SIGSEGV, signal_handler );
	signal( SIGABRT, signal_handler );
	signal( SIGTERM, signal_handler );
#else
	signal( SIGHUP, signal_handler );
	signal( SIGINT, signal_handler );
	signal( SIGKILL, signal_handler );
	signal( SIGBUS, signal_handler );
	signal( SIGSEGV, signal_handler );
	signal( SIGABRT, signal_handler );
	signal( SIGTERM, signal_handler );
#endif
}

/***************************************************************
* シグナルの処理ハンドラ
* int sig : シグナル
***************************************************************/

void	signal_handler( int sig )
{
	reset_scrn();

	exit_game( EXIT_FAILURE );
}

/***************************************************************
* 画面の初期化
***************************************************************/

void	init_scrn( void )
{
	init_curs();
	init_term();
}

/***************************************************************
* 画面のリセット
***************************************************************/

void	reset_scrn( void )
{
	while( chk_term() )
		dis_term();

	curs_refresh();
	while( chk_curs() ){
		curs_endwin();
	}
}

/***************************************************************
* 画面の有効化
* bool_t flg_initscr : curses を初期化するか?
***************************************************************/

void	ena_scrn( bool_t flg_initscr )
{
	if( flg_initscr ){
		curs_initscr();
		curs_keypad( stdscr, TRUE );
	} else {
		curs_clearok( stdscr, TRUE );
		curs_refresh();
	}

	ena_term();
}

/***************************************************************
* 画面の無効化
***************************************************************/

void	dis_scrn( void )
{
	dis_term();

	curs_refresh();
	curs_endwin();
}

/***************************************************************
* 端末の初期化
***************************************************************/

void	init_term( void )
{
#ifdef	D_DOS
	init_term_dos();
#else	/* D_DOS */
	init_term_unix();
#endif	/* D_DOS */
}

/***************************************************************
* 端末が有効か調べる
* return : 端末が有効か?
***************************************************************/

bool_t	chk_term( void )
{
#ifdef	D_DOS
	return chk_term_dos();
#else	/* D_DOS */
	return chk_term_unix();
#endif	/* D_DOS */
}

/***************************************************************
* 端末の有効化
***************************************************************/

void	ena_term( void )
{
#ifdef	D_DOS
	ena_term_dos();
#else	/* D_DOS */
	ena_term_unix();
#endif	/* D_DOS */
}

/***************************************************************
* 端末の無効化
***************************************************************/

void	dis_term( void )
{
#ifdef	D_DOS
	dis_term_dos();
#else	/* D_DOS */
	dis_term_unix();
#endif	/* D_DOS */
}

/***************************************************************
* キーの待ちを設定
***************************************************************/

void	set_key_wait( void )
{
#ifdef	D_DOS
	set_key_wait_dos();
#else	/* D_DOS */
	set_key_wait_unix();
#endif	/* D_DOS */
}

/***************************************************************
* キーの待ちを解除
***************************************************************/

void	clr_key_wait( void )
{
#ifdef	D_DOS
	clr_key_wait_dos();
#else	/* D_DOS */
	clr_key_wait_unix();
#endif	/* D_DOS */
}

/***************************************************************
* シェルの呼び出し
***************************************************************/

void	child_ps_unix( void )
{
	char	*shell;

	if( !g_flg_cui )
		return;

	dis_scrn();

	shell = getenv( STR_ENV_SHELL );
	if( shell == NULL )
		shell = STR_DFLT_SHELL;

	fprintf( stdout, MSG_CHILD_PS, shell );
	fflush( stdout );
	system( shell );

	ena_scrn( FALSE );
}

/***************************************************************
* シェルの呼び出し
***************************************************************/

void	child_ps_dos( void )
{
	char	*shell;

	if( !g_flg_cui )
		return;

	dis_scrn();

	shell = getenv( STR_ENV_SHELL );
	if( shell == NULL )
		shell = STR_DFLT_SHELL;

	fprintf( stdout, MSG_CHILD_PS, shell );
	fflush( stdout );
	system( shell );

	ena_scrn( FALSE );
}

/***************************************************************
* 端末の初期化
***************************************************************/

void	init_term_unix( void )
{
	flg_term = 0;
}

/***************************************************************
* 端末が有効か調べる
* return : 端末が有効か?
***************************************************************/

bool_t	chk_term_unix( void )
{
	return( flg_term > 0 );
}

/***************************************************************
* 端末を有効にする
***************************************************************/

void	ena_term_unix( void )
{
	if( !g_flg_cui )
		return;

	flg_term++;

#if	defined( HAVE_TERMIOS_H ) || defined( HAVE_TERMIO_H )
	if( flg_term == 1 ){
		/* 構造体の宣言 */
# if	defined( HAVE_TERMIOS_H )
		struct termios	tbuf;
# elif	defined( HAVE_TERMIO_H )
		struct termio	tbuf;
# endif

		/* 情報のゲット */
# if	defined( HAVE_TERMIOS_H )
		tcgetattr( fileno( stdin ), &tbuf );
# elif	defined( HAVE_TERMIO_H )
		ioctl( 0, TCGETA, &tbuf );
# endif

		/* 情報の編集 */
		pre_tbuf = tbuf;

		tbuf.c_iflag &= ~(INLCR | ICRNL | ISTRIP | IXON | BRKINT);
		tbuf.c_oflag &= ~(OPOST);
		if( g_flg_clr_key_buf ){
			tbuf.c_cc[VMIN] = KEY_WAIT_VMIN;
			tbuf.c_cc[VTIME] = KEY_WAIT_VTIME;
		}
		tbuf.c_lflag &= ~(ICANON | ISIG | ECHO);

		/* ^C を有効にする */
		if( g_flg_debug ){
			tbuf.c_iflag |= BRKINT;
			tbuf.c_lflag |= ISIG;
		}

		/* 情報のセット */
# if	defined( HAVE_TERMIOS_H )
		if( tcsetattr( fileno( stdin ), TCSANOW, &tbuf ) != 0 ){
			fprintf( stderr, MSG_S, MSG_ERR_SET_TTY );
			exit_game( EXIT_FAILURE );
		}
# elif	defined( HAVE_TERMIO_H )
		if( ioctl( 0, TCSETAF, &tbuf ) != 0 ){
			fprintf( stderr, MSG_S, MSG_ERR_SET_TTY );
			exit_game( EXIT_FAILURE );
		}
# endif	/* HAVE_TERMIOS_H */
	}
#endif	/* defined( HAVE_TERMIOS_H ) || defined( HAVE_TERMIO_H ) */
}

/***************************************************************
* 端末を無効にする
***************************************************************/

void	dis_term_unix( void )
{
	if( !g_flg_cui )
		return;

	if( flg_term == 1 ){
#if	defined( HAVE_TERMIOS_H )
		tcsetattr( fileno( stdin ), TCSANOW, &pre_tbuf );
#elif	defined( HAVE_TERMIO_H )
		ioctl( 0, TCSETAF, &pre_tbuf );
#endif
	}

	flg_term--;
}

/***************************************************************
* キーの待ちを設定
***************************************************************/

void	set_key_wait_unix( void )
{
	set_key_wait_vtime( KEY_WAIT_VTIME );
}

/***************************************************************
* キーの待ちを解除
***************************************************************/

void	clr_key_wait_unix( void )
{
	set_key_wait_vtime( 0 );
}

/***************************************************************
* キーの待ち時間を設定
* long wait_vtime : キーの待ち時間
***************************************************************/

void	set_key_wait_vtime( long wait_vtime )
{
#if	defined( HAVE_TERMIOS_H ) || defined( HAVE_TERMIO_H )
	/* 構造体の宣言 */
# if	defined( HAVE_TERMIOS_H )
	struct termios	tbuf;
# elif	defined( HAVE_TERMIO_H )
	struct termio	tbuf;
# endif

	if( !g_flg_cui )
		return;

	/* 情報のゲット */
# if	defined( HAVE_TERMIOS_H )
	tcgetattr( fileno( stdin ), &tbuf );
# elif	defined( HAVE_TERMIO_H )
	ioctl( 0, TCGETA, &tbuf );
# endif

	/* 情報の編集 */
	tbuf.c_cc[VMIN] = 0;
	tbuf.c_cc[VTIME] = wait_vtime;

	/* 情報のセット */
# if	defined( HAVE_TERMIOS_H )
	if( tcsetattr( fileno( stdin ), TCSANOW, &tbuf ) != 0 ){
		fprintf( stderr, MSG_S, MSG_ERR_SET_TTY );
		exit_game( EXIT_FAILURE );
	}
# elif	defined( HAVE_TERMIO_H )
	if( ioctl( 0, TCSETAF, &tbuf ) != 0 ){
		fprintf( stderr, MSG_S, MSG_ERR_SET_TTY );
		exit_game( EXIT_FAILURE );
	}
# endif
#endif
}

/***************************************************************
* 端末の初期化
***************************************************************/

void	init_term_dos( void )
{
	flg_term = 0;
}

/***************************************************************
* 端末が有効か調べる
* return : 端末が有効か?
***************************************************************/

bool_t	chk_term_dos( void )
{
	return( flg_term > 0 );
}

/***************************************************************
* 端末を有効にする
***************************************************************/

void	ena_term_dos( void )
{
	if( !g_flg_cui )
		return;

	flg_term++;
}

/***************************************************************
* 端末を無効にする
***************************************************************/

void	dis_term_dos( void )
{
	if( !g_flg_cui )
		return;

	flg_term--;
}

/***************************************************************
* キーの待ちを設定
***************************************************************/

void	set_key_wait_dos( void )
{
	set_key_wait_vtime( 1 );
}

/***************************************************************
* キーの待ちを解除
***************************************************************/

void	clr_key_wait_dos( void )
{
	set_key_wait_vtime( 0 );
}

/***************************************************************
* メモリー・チェック
* check_memory_t mem : チェックするメモリー
* const char *msg : エラー・メッセージ
***************************************************************/

bool_t	check_memory( check_memory_t mem, const char *msg )
{
	long	i;

	if( mem == NULL )
		return FALSE;
	if( msg == NULL )
		msg = "";

	for( i = 0; i < CHECK_MEMORY_MAX_LEN / 2; i++ ){
		if( (mem[i * 2 + 0] == 0xbe) && (mem[i * 2 + 1] == 0xef) )
			continue;

		print_msg( FLG_MSG_ERR,
				"memory error: %s: [0x%2lx,0x%2lx]",
				msg, mem[i * 2 + 0], mem[i * 2 + 1] );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* 全てのメモリー・チェック
***************************************************************/

void	check_memory_all( void )
{
	check_memory_amenu_c();
	check_memory_chr_c();
	check_memory_curs_c();
	check_memory_draw_c();
	check_memory_dun_c();
	check_memory_ending_ep_c();
	check_memory_ending_space_c();
	check_memory_fight_c();
	check_memory_fx_c();
	check_memory_gf_conf_c();
	check_memory_gf_crsr_c();
	check_memory_gf_gconf_c();
	check_memory_gf_outmap_c();
	check_memory_gf_replay_c();
	check_memory_gf_save_c();
	check_memory_gf_town_c();
	check_memory_gfile_c();
	check_memory_gmain_c();
	check_memory_imenu_c();
	check_memory_item_c();
	check_memory_key_item_c();
	check_memory_last_boss_c();
#if	defined( D_GTK )
#elif	defined( D_IPHONE )
#elif	defined( D_MFC )
#elif	defined( D_DOS )
	check_memory_main_dos_c();
#else
	check_memory_main_unix_c();
#endif
	check_memory_map_event_c();
	check_memory_menu_c();
	check_memory_misc_c();
	check_memory_mmenu_c();
	check_memory_mnstr_act_c();
	check_memory_mnstr_c();
	check_memory_msg_c();
	check_memory_nest_flg_c();
	check_memory_party_c();
	check_memory_pet_c();
	check_memory_play_rep_c();
	check_memory_replay_c();
	check_memory_request_c();
	check_memory_scene_c();
	check_memory_skill_c();
	check_memory_spell_c();
	check_memory_tmenu_c();
	check_memory_town_c();
	check_memory_trap_c();
	check_memory_turn_c();

	check_memory_gui();
}

/***************************************************************
* gmain.c のメモリー・チェック
***************************************************************/

void	check_memory_gmain_c( void )
{
	check_memory( check_memory_gmain_c_flg_term,
			"gmain.c: flg_term" );
	check_memory( check_memory_gmain_c_pre_tbuf,
			"gmain.c: pre_tbuf" );
	check_memory( check_memory_gmain_c_long_opt,
			"gmain.c: long_opt" );
	check_memory( check_memory_gmain_c_str_usage,
			"gmain.c: str_usage" );
}
