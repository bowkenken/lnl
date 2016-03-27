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
* $Id: curs.c,v 1.99 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* curses のラッパー
***************************************************************/

#define	CURS_C
#include	"inc.h"

/***************************************************************
* 変数定義
***************************************************************/

static bool_t	g_flg_screen_size_auto;
static long	g_screen_size_col;
static long	g_screen_size_row;
static long	g_screen_size_message;
static bool_t	g_flg_resize_map;
check_memory_def( check_memory_curs_c_g_flg_screen_size_auto )

/* エスケープ・シーケンスを使って反転属性を描画するか? */
#define	FLG_PRINT_REVERSE	0

/* 描画が可能かどうかのデプス・フラグ */
static long	flg_curs, flg_curs_draw;
/* カラー描画可能フラグ */
static bool_t	flg_color;
/* 現在の描画属性 */
static curs_attr_t	g_current_attr;
check_memory_def( check_memory_curs_c_flg_curs )

/* 描画属性のデフォルト値 */
/* 列び順を変たら curs_attr_n_t も修整すること */

static curs_attr_t	g_curs_attr[CURS_ATTR_N_MAX_N] = {
	{ 0, N_MSG_ATTR_NORMAL,
		COLOR_WHITE, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_REV,
		COLOR_WHITE, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_ERR,
		COLOR_RED, COLOR_BLACK, A_BOLD, },

	{ 0, N_MSG_ATTR_MENU_NORMAL,
		COLOR_WHITE, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_MENU_DIS,
		COLOR_YELLOW, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_MENU_SEL,
		COLOR_WHITE, COLOR_BLACK, A_REVERSE, },

	{ 0, N_MSG_ATTR_MAP_CRSR,
		COLOR_GREEN, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_MAP_SQUARE,
		COLOR_MAGENTA, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_WALL,
		COLOR_WHITE, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_MAP_FLOOR,
		COLOR_WHITE, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_MAP_DOOR,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_STAIRS,
		COLOR_CYAN, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_MAP_TRAP,
		COLOR_RED, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_MNSTR,
		COLOR_RED, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_NPC,
		COLOR_CYAN, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_MAP_PET,
		COLOR_WHITE, COLOR_BLACK, A_REVERSE, },

	{ 0, N_MSG_ATTR_MAP_ITEM,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_WPN,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_ARMOR,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_POTION,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_SCROLL,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_STICK,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_ACCE,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_INST,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_LIGHT,
		COLOR_YELLOW, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_SPIKE,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_FOOD,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MAP_ITEM_CHEST,
		COLOR_GREEN, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_MAP_ITEM_RARE_GOODS,
		COLOR_GREEN, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_MAP_ITEM_BONE,
		COLOR_WHITE, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_MAP_ITEM_COIN,
		COLOR_GREEN, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_MAP_ITEM_JUNK,
		COLOR_WHITE, COLOR_BLACK, A_NORMAL, },

	{ 0, N_MSG_ATTR_MBR_1,
		COLOR_RED, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_MBR_2,
		COLOR_GREEN, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_MBR_3,
		COLOR_BLUE, COLOR_BLACK, A_BOLD | A_REVERSE, },
	{ 0, N_MSG_ATTR_MBR_4,
		COLOR_CYAN, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_MBR_5,
		COLOR_MAGENTA, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_MBR_6,
		COLOR_YELLOW, COLOR_BLACK, A_REVERSE, },

	{ 0, N_MSG_ATTR_FX_MBR_PLUS,
		COLOR_CYAN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_FX_MBR_MINUS,
		COLOR_RED, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_FX_MBR_CRTCL,
		COLOR_RED, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_FX_MNSTR_PLUS,
		COLOR_RED, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_FX_MNSTR_MINUS,
		COLOR_CYAN, COLOR_BLACK, A_NORMAL, },
	{ 0, N_MSG_ATTR_FX_MNSTR_CRTCL,
		COLOR_CYAN, COLOR_BLACK, A_REVERSE, },
	{ 0, N_MSG_ATTR_VFX,
		COLOR_YELLOW, COLOR_BLACK, A_BOLD, },

	{ 0, N_MSG_ATTR_HEAT,
		COLOR_RED, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_COLD,
		COLOR_BLUE, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_MIND,
		COLOR_GREEN, COLOR_BLACK, A_BOLD, },
	{ 0, N_MSG_ATTR_ACID,
		COLOR_YELLOW, COLOR_BLACK, A_BOLD, },
};
check_memory_def( check_memory_curs_c_g_curs_attr )

/***************************************************************
* 初期化
***************************************************************/

void	init_curs( void )
{
	set_flg_screen_size_auto( TRUE );
	set_screen_size_col( 80 );
	set_screen_size_row( 24 );
	set_screen_size_message( 24 - (20 + 1) );
	set_flg_resize_map( FALSE );

	flg_curs = 0;
	flg_curs_draw = 0;
	curs_attrset_dflt();
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_curs( void )
{
}

/***************************************************************
* 表示色の初期化
* return : 色が使えるか
***************************************************************/

bool_t	init_curs_color( void )
{
	long	n;

	flg_color = TRUE;

	if( g_flg_gui && !g_flg_cui ){
		flg_color = TRUE;
		for( n = 0; n < CURS_ATTR_N_MAX_N; n++ ){
			short	pair_n;

			pair_n = n + 1;
			init_curs_color_pair( &(g_curs_attr[n]), pair_n );
			g_curs_attr[n].color_pair_n = pair_n;
		}
		return TRUE;
	}

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
# if	defined( HAVE_HAS_COLORS )
	if( g_flg_cui && !has_colors() ){
		flg_color = FALSE;
		return FALSE;
	}
# else	/* HAVE_HAS_COLORS */
	flg_color = FALSE;
	return FALSE;
# endif	/* HAVE_HAS_COLORS */

# if	defined( HAVE_START_COLOR )
	if( g_flg_cui && (start_color() != OK) ){
		flg_color = FALSE;
		return FALSE;
	}
# else	/* HAVE_START_COLOR */
	flg_color = FALSE;
	return FALSE;
# endif	/* HAVE_START_COLOR */
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

	flg_color = TRUE;
	for( n = 0; n < CURS_ATTR_N_MAX_N; n++ ){
		short	pair_n;

		pair_n = n + 1;
		init_curs_color_pair( &(g_curs_attr[n]), pair_n );
		g_curs_attr[n].color_pair_n = pair_n;
	}
	return TRUE;
}

/***************************************************************
* カラー・ペアの初期化
* curs_attr_t *p : 描画モード
* short pair_n : カラー・ペア
* return : 色が使えるか
***************************************************************/

bool_t	init_curs_color_pair( curs_attr_t *p, short pair_n )
{
#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( !flg_color )
		return FALSE;

# ifdef	HAVE_INIT_PAIR
	if( g_flg_cui )
		init_pair( pair_n, p->fg, p->bg );
# endif	/* HAVE_INIT_PAIR */
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

	p->color_pair_n = pair_n;

	return TRUE;
}

/***************************************************************
* 描画出来るか調べる
* return : 描画出来るか
***************************************************************/

bool_t	chk_curs_draw( void )
{
	if( flg_curs_draw <= 0 )
		return FALSE;

	if( g_flg_gui )
		return TRUE;

	if( !g_flg_cui )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 描画フラグを有効
***************************************************************/

void	ena_curs_draw( void )
{
	flg_curs_draw++;
}

/***************************************************************
* 描画フラグを無効
***************************************************************/

void	dis_curs_draw( void )
{
	flg_curs_draw--;
}

/***************************************************************
* 端末設定が有効か調べる
* return : 端末設定が有効か
***************************************************************/

bool_t	chk_curs( void )
{
	if( !g_flg_use_curs )
		return FALSE;

	if( flg_curs <= 0 )
		return FALSE;

	if( g_flg_gui )
		return TRUE;

	if( !g_flg_cui )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 端末設定を有効
***************************************************************/

void	ena_curs( void )
{
	if( g_flg_cui && chk_curs() ){
		curs_noecho();
		curs_cbreak();
		curs_raw();
	}
}

/***************************************************************
* 端末設定を無効
***************************************************************/

void	dis_curs( void )
{
	if( g_flg_cui && chk_curs() ){
		curs_noraw();
		curs_nocbreak();
		curs_echo();
	}
}

/***************************************************************
* 端末設定をクリア
* WINDOW *win : ウィンドウ
* bool_t bf : 1行スクロールするか
***************************************************************/

void	curs_clearok( WINDOW *win, bool_t bf )
{
	flg_curs++;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( flg_curs == 1 ){
		if( chk_curs() ){
			if( g_flg_cui ){
				clearok( win, bf );
			}
			ena_curs();
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */
}

/***************************************************************
* 端末設定を初期化
***************************************************************/

void	curs_initscr( void )
{
	flg_curs++;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( flg_curs == 1 ){
		if( chk_curs() ){
			if( g_flg_cui ){
				initscr();
			}
			ena_curs();
			init_curs_color();
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */
}

/***************************************************************
* 端末の利用を終了
***************************************************************/

void	curs_endwin( void )
{
	if( flg_curs == 1 ){

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
		if( chk_curs() ){
			dis_curs();
			if( g_flg_cui ){
				endwin();
			}
		}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

#ifdef	D_DOS
		curs_move( get_screen_row() - 1, 0 );
#endif	/* D_DOS */

	}

	flg_curs--;
}

/***************************************************************
* キー・パッドを利用
* WINDOW *win : ウィンドウ
* bool_t bf : 1行スクロールするか
***************************************************************/

void	curs_keypad( WINDOW *win, bool_t bf )
{
#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( g_flg_use_keypad ){
		if( chk_curs() ){
# ifdef	HAVE_KEYPAD
			if( g_flg_cui ){
				keypad( win, bf );
			}
# endif	/* HAVE_KEYPAD */
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */
}

/***************************************************************
* 画面を描画
***************************************************************/

void	curs_refresh( void )
{
	if( !chk_curs_draw() )
		return;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		if( g_flg_cui ){
			refresh();
			return;
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

	if( g_flg_cui )
		fflush( OUT_FP );
}

/***************************************************************
* 現在の描画モードを取得
* return : 現在の描画モード
***************************************************************/

curs_attr_t	get_current_attr( void )
{
	return g_current_attr;
}

/***************************************************************
* デフォルトの描画モードを設定
***************************************************************/

void	curs_attrset_dflt( void )
{
	curs_attrset_dir( &(g_curs_attr[CURS_ATTR_N_NORMAL]) );
}

/***************************************************************
* 指定した番号で描画モードを設定
* curs_attr_n_t n : 描画モード番号
***************************************************************/

void	curs_attrset_n( curs_attr_n_t n )
{
	curs_attrset_dir( &(g_curs_attr[n]) );
}

/***************************************************************
* 現在の描画モードを設定
* curs_attr_t *attr : 描画モード
***************************************************************/

void	curs_attrset_dir( curs_attr_t *attr )
{
	long	tmp_attr;

	g_current_attr = *attr;

	if( !chk_curs_draw() )
		return;

	tmp_attr = 0;
#ifdef	D_DOS
	tmp_attr = attr_dos( attr );
#else	/* D_DOS */
	tmp_attr = COLOR_PAIR( attr->color_pair_n );
	tmp_attr |= attr->attr;
#endif	/* D_DOS */

	curs_attrset( tmp_attr );
}

/***************************************************************
* 描画モードを設定
* long at : 数値化した描画モード
***************************************************************/

void	curs_attrset( long at )
{
	if( !chk_curs_draw() )
		return;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
# ifdef	HAVE_ATTRSET
		if( g_flg_cui ){
			attrset( at );
		}
# endif	/* HAVE_ATTRSET */
		return;
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

#if	D_DOS
	if( g_flg_cui ){
		HANDLE hStdOut;
		WORD wAttributes;

		hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
		wAttributes = (WORD)at;
		SetConsoleTextAttribute(hStdOut, wAttributes);
		return;
	}
#endif	/* D_DOS */

#if	FLG_PRINT_REVERSE
	if( g_flg_cui ){
		if( chk_flg( at, A_REVERSE ) )
			fprintf( OUT_FP, "\033[43m" );
		else
			fprintf( OUT_FP, "\033[m" );
	}
#endif	/* FLG_PRINT_REVERSE */
}

/***************************************************************
* 描画モードを有効
* long at : 数値化した描画モード
***************************************************************/

void	curs_attron( long at )
{
	if( !chk_curs_draw() )
		return;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
# ifdef	HAVE_ATTRON
		if( g_flg_cui ){
			attron( at );
		}
# endif	/* HAVE_ATTRON */
		return;
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

#if	FLG_PRINT_REVERSE
	if( g_flg_cui ){
		if( chk_flg( at, A_REVERSE ) )
			fprintf( OUT_FP, "\033[43m" );
	}
#endif	/* FLG_PRINT_REVERSE */
}

/***************************************************************
* 描画モードを無効
* long at : 数値化した描画モード
***************************************************************/

void	curs_attroff( long at )
{
	if( !chk_curs_draw() )
		return;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
# ifdef	HAVE_ATTROFF
		if( g_flg_cui ){
			attroff( at );
		}
# endif	/* HAVE_ATTROFF */
		return;
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

#if	FLG_PRINT_REVERSE
	if( g_flg_cui ){
		if( chk_flg( at, A_REVERSE ) )
			fprintf( OUT_FP, "\033[m" );
	}
#endif	/* FLG_PRINT_REVERSE */
}

/***************************************************************
* 描画モードのテーブル取得
* return : 描画モードのテーブル
***************************************************************/

curs_attr_t	*get_curs_attr( void )
{
	return g_curs_attr;
}

/***************************************************************
* 入力キーの表示を有効
***************************************************************/

void	curs_echo( void )
{
#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		if( g_flg_cui ){
			echo();
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */
}

/***************************************************************
* 入力キーの表示を無効
***************************************************************/

void	curs_noecho( void )
{
#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		if( g_flg_cui ){
			noecho();
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */
}

/***************************************************************
* 中断キーを有効
***************************************************************/

void	curs_cbreak( void )
{
#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		if( g_flg_cui ){
			cbreak();
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */
}

/***************************************************************
* 中断キーを無効
***************************************************************/

void	curs_nocbreak( void )
{
#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		if( g_flg_cui ){
			nocbreak();
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */
}

/***************************************************************
* 入力行編集を有効
***************************************************************/

void	curs_raw( void )
{
#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		if( g_flg_cui ){
			raw();
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */
}

/***************************************************************
* 入力行編集を無効
***************************************************************/

void	curs_noraw( void )
{
#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		if( g_flg_cui ){
			noraw();
		}
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */
}

/***************************************************************
* カーソルを移動
* int scrn_y : 行
* int scrn_x : 列
***************************************************************/

void	curs_move( int scrn_y, int scrn_x )
{
	if( scrn_x < SCREEN_MIN_X )
		return;
	if( scrn_y < SCREEN_MIN_Y )
		return;
	if( scrn_x > get_screen_col() - 1 )
		return;
	if( scrn_y > get_screen_row() - 1 )
		return;

#ifndef	D_DOS
	if( !chk_curs_draw() )
		return;
#endif	/* ! D_DOS */

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		if( g_flg_cui ){
			move( scrn_y, scrn_x );
		}
		return;
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

#ifdef	D_DOS
	if( g_flg_cui ){
		COORD	scrn_pos;

		scrn_pos.X = scrn_x;
		scrn_pos.Y = scrn_y;
		SetConsoleCursorPosition(
				GetStdHandle( STD_OUTPUT_HANDLE ),
				scrn_pos );
		return;
	}
#endif	/* D_DOS */

	if( g_flg_cui )
		fprintf( OUT_FP, "\033[%d;%dH", scrn_y + 1, scrn_x + 1 );
}

/***************************************************************
* ウィンドウに文字列を描画
* char *s : フォーマット文字列
* ... : 表示するオプション
***************************************************************/

void	curs_printw( char *s, ... )
{
	va_list	argptr;

	if( !g_flg_cui )
		return;

	if( !chk_curs_draw() )
		return;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		va_start( argptr, s );
		vwprintw( stdscr, s, argptr );
		va_end( argptr );

		return;
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

	va_start( argptr, s );
	vfprintf( OUT_FP, s, argptr );
	va_end( argptr );
}

/***************************************************************
* 画面をクリア
***************************************************************/

void	curs_clear( void )
{
	if( !chk_curs_draw() )
		return;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		if( g_flg_cui ){
			curs_attrset_dflt();
			clear();
		}
		return;
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

#ifdef	D_X68K
	if( g_flg_cui ){
		fprintf( OUT_FP, "\032" );
	}
	return;
#endif	/* D_X68K */

	if( g_flg_cui ){
		long	i;
		const long	max_n = get_screen_row();

		curs_move( 0, 0 );
		for( i = 0; i < max_n; i++ )
			fprintf( OUT_FP, "%*s", SCREEN_WIDTH, " " );
	}
}

/***************************************************************
* 1文字入力
* return : 文字
***************************************************************/

int	curs_getch( void )
{
	int	c;
	bool_t	flg_getc = FALSE;

	if( g_gui_key_kind != GUI_KEY_KIND_CONSOLE )
		return call_key_get_char();
	if( !g_flg_cui ){
		sleep_msec( 10 );
		return '\0';
	}

	c = '\0';

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )

	if( !flg_getc ){
		if( chk_curs() ){
			c = getch();
			flg_getc = TRUE;
		}
	}

#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

#ifdef	D_DOS

	if( !flg_getc ){
		c = getch();
		flg_getc = TRUE;
	}

#else	/* D_DOS */

	if( !flg_getc ){
		c = getchar();
		flg_getc = TRUE;
	}

#endif	/* D_DOS */

	return c;
}

/***************************************************************
* 文字列入力
* char *s : 文字列を返す
* int len : 最大文字数
***************************************************************/

void	curs_getnstr( char *s, int len )
{
	static char	buf[255 + 1];

	if( !g_flg_cui ){
		sleep_msec( 10 );
		return;
	}

	s[0] = '\0';

	if( !chk_curs_draw() )
		return;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
# ifdef	HAVE_GETNSTR
		getnstr( s, len );
		return;
# endif	/* HAVE_GETNSTR */
	}
#endif	/* HAVE_NCURSES_H || HAVE_CURSES_H */

	fgets( buf, sizeof( buf ) - 1, stdin );
	str_nz_cpy( s, buf, len );
}

/***************************************************************
* カラー・モードか調べる
* return : カラー・モードか
***************************************************************/

bool_t	chk_color( void )
{
	return flg_color;
}

/***************************************************************
* 画面の横文字数を調べる
* return : 横文字数
***************************************************************/

long	get_screen_col( void )
{
	if( !g_flg_cui )
		return SCREEN_WIDTH;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		return COLS;
	}
#endif

#ifdef	D_DOS
	{
		CONSOLE_SCREEN_BUFFER_INFO cInfo;

		GetConsoleScreenBufferInfo(
				GetStdHandle( STD_OUTPUT_HANDLE ),
				&cInfo );
		return( cInfo.srWindow.Right - cInfo.srWindow.Left + 1 );
	}
#endif	/* D_DOS */

	if( !chk_flg_screen_size_auto() )
		return get_screen_size_col();

	return SCREEN_WIDTH;
}

/***************************************************************
* 画面の縦行数を調べる
* return : 縦行数
***************************************************************/

long	get_screen_row( void )
{
	if( !g_flg_cui )
		return SCREEN_HEIGHT;

#if	defined( HAVE_NCURSES_H ) || defined( HAVE_CURSES_H )
	if( chk_curs() ){
		return LINES;
	}
#endif

#ifdef	D_DOS
	{
		CONSOLE_SCREEN_BUFFER_INFO cInfo;

		GetConsoleScreenBufferInfo(
				GetStdHandle( STD_OUTPUT_HANDLE ),
				&cInfo );
		return( cInfo.srWindow.Bottom - cInfo.srWindow.Top + 1 );
	}
#endif	/* D_DOS */

	if( !chk_flg_screen_size_auto() )
		return get_screen_size_row();

	return SCREEN_HEIGHT;
}

/***************************************************************
* マップの横文字数を調べる
* return : 横文字数
***************************************************************/

long	get_map_col( void )
{
	if( chk_flg_resize_map() ){
		long	n;

		n = get_screen_col();
		n -= SCREEN_WIDTH - (WIN_MAP_DRAW_MAX_X + 1);
		return n;
	} else {
		return( WIN_MAP_DRAW_WIDTH );
	}

	return 1;
}

/***************************************************************
* マップの縦行数を調べる
* return : 縦行数
***************************************************************/

long	get_map_row( void )
{
	if( chk_flg_resize_map() ){
		long	n;

		n = get_screen_row();
		n -= 1;
		n -= get_screen_size_message();
		n -= get_stat_bar_row();
		return n;
	} else {
		return( WIN_MAP_DRAW_HEIGHT );
	}

	return 1;
}

/***************************************************************
* メッセージの横文字数を調べる
* return : 横文字数
***************************************************************/

long	get_message_col( void )
{
	return get_screen_col();
}

/***************************************************************
* メッセージの縦行数を調べる
* return : 縦行数
***************************************************************/

long	get_message_row( void )
{
	if( chk_flg_resize_map() ){
		return get_screen_size_message();
	} else {
		long	n;

		n = get_screen_row();
		n -= WIN_MAP_DRAW_HEIGHT + 1;
		n -= get_stat_bar_row();
		return n;
	}

	return 1;
}

/***************************************************************
* ステータス・バーの横文字数を調べる
* return : 横文字数
***************************************************************/

long	get_stat_bar_col( void )
{
	return get_screen_col() - 1;
}

/***************************************************************
* ステータス・バーの縦行数を調べる
* return : 縦行数
***************************************************************/

long	get_stat_bar_row( void )
{
	return calc_stat_bar_line_n();
}

/***************************************************************
* 画面サイズの自動設定が有効か調べる
* return : 有効か?
***************************************************************/

bool_t	chk_flg_screen_size_auto( void )
{
	return g_flg_screen_size_auto;
}

/***************************************************************
* 画面サイズの自動設定を有効／無効にする
* bool_t flg : 有効／無効
***************************************************************/

void	set_flg_screen_size_auto( bool_t flg )
{
	if( flg )
		g_flg_screen_size_auto = TRUE;
	else
		g_flg_screen_size_auto = FALSE;
}

/***************************************************************
* 画面の最大横文字数の設定値を返す
* return : 最大横文字数
***************************************************************/

long	get_screen_size_col( void )
{
	return g_screen_size_col;
}

/***************************************************************
* 画面の最大横文字数を設定
* long n : 最大横文字数
***************************************************************/

void	set_screen_size_col( long n )
{
	if( n < SCREEN_SIZE_MIN_COL )
		n = SCREEN_SIZE_MIN_COL;
	if( n > SCREEN_SIZE_MAX_COL )
		n = SCREEN_SIZE_MAX_COL;

	g_screen_size_col = n;
}

/***************************************************************
* 画面の最大縦行数の設定値を返す
* return : 最大縦行数
***************************************************************/

long	get_screen_size_row( void )
{
	return g_screen_size_row;
}

/***************************************************************
* 画面の最大縦行数を設定
* long n : 最大縦行数
***************************************************************/

void	set_screen_size_row( long n )
{
	if( n < SCREEN_SIZE_MIN_ROW )
		n = SCREEN_SIZE_MIN_ROW;
	if( n > SCREEN_SIZE_MAX_ROW )
		n = SCREEN_SIZE_MAX_ROW;

	g_screen_size_row = n;
}

/***************************************************************
* 画面の最大メッセージ行数の設定値を返す
* return : 最大メッセージ行数
***************************************************************/

long	get_screen_size_message( void )
{
	return g_screen_size_message;
}

/***************************************************************
* 画面の最大メッセージ行数を設定
* long n : 最大メッセージ行数
***************************************************************/

void	set_screen_size_message( long n )
{
	if( n < SCREEN_SIZE_MIN_ROW )
		n = SCREEN_SIZE_MIN_ROW;
	if( n > SCREEN_SIZE_MAX_ROW )
		n = SCREEN_SIZE_MAX_ROW;

	g_screen_size_message = n;
}

/***************************************************************
* マップのサイズが可変か調べる
* return : 可変か?
***************************************************************/

bool_t	chk_flg_resize_map( void )
{
	return g_flg_resize_map;
}

/***************************************************************
* マップのサイズが可変か設定する
* bool_t flg : 可変か?
***************************************************************/

void	set_flg_resize_map( bool_t flg )
{
	if( flg )
		g_flg_resize_map = TRUE;
	else
		g_flg_resize_map = FALSE;
}

/***************************************************************
* 描画モードを比較
* curs_attr_t *a : 描画モード
* curs_attr_t *b : 描画モード
* return : 描画モードが同じか?
***************************************************************/

bool_t	cmp_attr( curs_attr_t *a, curs_attr_t *b )
{
	if( a == NULL )
		return FALSE;
	if( b == NULL )
		return FALSE;

	if( a->color_pair_n != b->color_pair_n )
		return FALSE;
	if( a->fg != b->fg )
		return FALSE;
	if( a->bg != b->bg )
		return FALSE;
	if( a->attr != b->attr )
		return FALSE;

	return TRUE;
}

/***************************************************************
* DOS 用の色の変換
* curs_attr_t *attr : 描画モード
* return : 色
***************************************************************/

int	attr_dos( curs_attr_t *attr )
{
	int	a;

	if( attr == NULL )
		return 0;

	a = 0;

#ifdef	D_DOS
	{
		short	fg, bg;

		fg = 0;
		bg = 0;

		if( chk_flg( attr->attr, A_BOLD ) )
			a |= FOREGROUND_INTENSITY;

		if( chk_flg( attr->attr, A_REVERSE ) ){
			bg = attr->fg;
			fg = attr->bg;
		} else {
			fg = attr->fg;
			bg = attr->bg;
		}

		switch( fg ){
		case COLOR_BLACK:
			break;
		case COLOR_RED:
			a |= FOREGROUND_RED;
			break;
		case COLOR_GREEN:
			a |= FOREGROUND_GREEN;
			break;
		case COLOR_YELLOW:
			a |= FOREGROUND_RED;
			a |= FOREGROUND_GREEN;
			break;
		case COLOR_BLUE:
			a |= FOREGROUND_BLUE;
			break;
		case COLOR_MAGENTA:
			a |= FOREGROUND_RED;
			a |= FOREGROUND_BLUE;
			break;
		case COLOR_CYAN:
			a |= FOREGROUND_GREEN;
			a |= FOREGROUND_BLUE;
			break;
		case COLOR_WHITE:
			a |= FOREGROUND_RED;
			a |= FOREGROUND_GREEN;
			a |= FOREGROUND_BLUE;
			break;
		}

		switch( bg ){
		case COLOR_BLACK:
			break;
		case COLOR_RED:
			a |= BACKGROUND_RED;
			break;
		case COLOR_GREEN:
			a |= BACKGROUND_GREEN;
			break;
		case COLOR_YELLOW:
			a |= BACKGROUND_RED;
			a |= BACKGROUND_GREEN;
			break;
		case COLOR_BLUE:
			a |= BACKGROUND_BLUE;
			break;
		case COLOR_MAGENTA:
			a |= BACKGROUND_RED;
			a |= BACKGROUND_BLUE;
			break;
		case COLOR_CYAN:
			a |= BACKGROUND_GREEN;
			a |= BACKGROUND_BLUE;
			break;
		case COLOR_WHITE:
			a |= BACKGROUND_RED;
			a |= BACKGROUND_GREEN;
			a |= BACKGROUND_BLUE;
			break;
		}
	}
#endif	/* D_DOS */

	return a;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_curs_c( void )
{
	check_memory( check_memory_curs_c_g_flg_screen_size_auto,
			"curs.c: " );
	check_memory( check_memory_curs_c_flg_curs,
			"curs.c: " );
	check_memory( check_memory_curs_c_g_curs_attr,
			"curs.c: " );
}
