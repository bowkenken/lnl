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
* $Id: gmain.h,v 1.79 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	GMAIN_H
#define	GMAIN_H

/***************************************************************
* メイン処理
***************************************************************/

#if	defined( D_GTK )
/**/
#elif	defined( D_IPHONE )
# include	"config-iphone.h"
#elif	defined( D_WS )
# include	"config-win.h"
#elif	defined( D_MFC )
# include	"config-dows.h"
#elif	defined( D_DOS )
# include	"lnl-dos/config-dos.h"
#endif

#ifdef	HAVE_CONFIG_H
# include	"config.h"
#endif	/* HAVE_CONFIG_H */

#ifdef	HAVE_STDLIB_H
# include	<stdlib.h>
#endif	/* HAVE_STDLIB_H */

#ifdef	HAVE_STDDEF_H
# include	<stddef.h>
#endif	/* HAVE_STDDEF_H */

#ifdef	HAVE_STDIO_H
# include	<stdio.h>
#endif	/* HAVE_STDIO_H */

#ifdef	HAVE_STDARG_H
# include	<stdarg.h>
#endif	/* HAVE_STDARG_H */

#ifdef	HAVE_LIMITS_H
# include	<limits.h>
#endif	/* HAVE_LIMITS_H */

#ifdef	HAVE_STRING_H
# include	<string.h>
#endif	/* HAVE_STRING_H */

#ifdef	HAVE_STRINGS_H
# include	<strings.h>
#endif	/* HAVE_STRING_H */

#ifdef	HAVE_CTYPE_H
# include	<ctype.h>
#endif	/* HAVE_CTYPE_H */

#ifdef	HAVE_TIME_H
# include	<time.h>
#endif	/* HAVE_TIME_H */

#ifdef	HAVE_MATH_H
# include	<math.h>
#endif	/* HAVE_MATH_H */

#ifdef	HAVE_DIRECT_H
# include <direct.h>
#endif	/* HAVE_DIRECT_H */

#ifdef	HAVE_SYS_STAT_H
# include	<sys/stat.h>
#endif	/* HAVE_SYS_STAT_H */

#ifdef	HAVE_UNISTD_H
# include	<unistd.h>
#endif	/* HAVE_UNISTD_H */

#ifdef	HAVE_GPM_H
# include	<gpm.h>
#endif	/* HAVE_GPM_H */

#ifndef	EXIT_SUCCESS
# define	EXIT_SUCCESS	0
#endif	/* EXIT_SUCCESS */

#ifndef	EXIT_FAILURE
# define	EXIT_FAILURE	1
#endif	/* EXIT_FAILURE */

/***************************************************************/

#if	defined( D_WS ) \
	|| defined( D_GTK ) \
	|| defined( D_IPHONE ) \
	|| defined( D_MFC )
# define	D_ALL_GUI	1
#endif

/***************************************************************/

#include	"misc.h"
#include	"turn.h"
#include	"msg-t.h"

#include	"music-kind.h"
#include	"sound-kind.h"

/***************************************************************
* 型定義
***************************************************************/

/* キー入力をどこから読むか? */

typedef enum {
	GUI_KEY_KIND_CONSOLE,
	GUI_KEY_KIND_CLASS_KEY,
	GUI_KEY_KIND_KEY_BUF_INTERRUPT,
	GUI_KEY_KIND_MAX_N,
} gui_key_kind_t;

/* メモリー・チェック */

#define	CHECK_MEMORY_MAX_LEN	32
#define	CHECK_MEMORY_INIT	{ \
	0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, \
	0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, \
	0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, \
	0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, \
}

typedef unsigned char	check_memory_t[CHECK_MEMORY_MAX_LEN];

#define	check_memory_def( var )	\
	static check_memory_t	var = CHECK_MEMORY_INIT;

/***************************************************************
* 変数定義
***************************************************************/

#include	"extern.h"

#ifdef __cplusplus
extern "C" {
#endif

/* CUI の全モジュールが初期化済みか? */
EXTERN bool_t	g_flg_init;

/* CUI モード */
EXTERN bool_t	g_flg_cui;

/* GUI モード */
EXTERN bool_t	g_flg_gui;

/* CUI マウス・モード */
EXTERN bool_t	g_flg_cui_mouse;

/* CUI マウス・モード時に右と中のボタンを入れ替えるか? */
EXTERN bool_t	g_flg_cui_mouse_swap_btn;

/* 音響のバッファー・サイズの設定をオプションで指定されたか? */
EXTERN long	g_audio_buf_siz_arg_overwrite;

/* 音響のバッファー・サイズの設定をオプションで指定 */
EXTERN long	g_audio_buf_siz_arg;

/* 音響のバッファー・サイズの設定 */
EXTERN long g_audio_buf_siz;

/* ウィンドウ座標の設定をオプションで指定されたか? */
EXTERN bool_t	g_flg_win_pos_arg_overwrite;

/* ウィンドウ・マネージャが GNOME かをオプションで指定 */
EXTERN bool_t	g_flg_gnome_arg;

/* ウィンドウ・マネージャが GNOME か? */
EXTERN bool_t	g_flg_gnome;

/* ウィンドウを表示する時に位置を設定するかをオプションで指定 */
EXTERN bool_t	g_flg_set_win_pos_arg;

/* ウィンドウを表示する時に位置を設定するか? */
EXTERN bool_t	g_flg_set_win_pos;

/* GUI のテキスト表示モード */
EXTERN bool_t	g_flg_text_mode;

/* GUI のテキスト表示モードのフォント・サイズ */
EXTERN long	g_text_mode_point;

/* グラフィック画面の拡大率 */
EXTERN rate_t	g_graph_scale_rate;

/* キー入力をどこから読むか? */
EXTERN gui_key_kind_t	g_gui_key_kind;

/* メッセージの言語 */
EXTERN char	*g_language;

/* キー・バッファのクリアをオプションで指定されたか? */
EXTERN bool_t	g_flg_clr_key_buf_arg_overwrite;

/* キー・バッファのクリアをオプションで指定 */
EXTERN bool_t	g_flg_clr_key_buf_arg;

/* キー・バッファをクリアする */
EXTERN bool_t	g_flg_clr_key_buf;

/* キー・バッファをクリアする（メニュー選択時） */
EXTERN bool_t	g_flg_clr_key_buf_menu;

/* 入力されたキーを表示 */
EXTERN bool_t	g_flg_echo_key;

/* 画面の描画に curses ライブラリを使用する */
EXTERN bool_t	g_flg_use_curs;

/* カーソル・キー等を使用する */
EXTERN bool_t	g_flg_use_keypad;

/* フレーム・レートを計測する */
EXTERN bool_t	g_flg_measure_clk_tck;

/* セーブ・ロード時の乱数の種 */
EXTERN long	g_randm_seed_save;

/* アイテムの受け渡しの時ターンを消費する */
EXTERN bool_t	g_flg_send_item_exec_turn;

/* カット・インのデモをスキップするか? */
EXTERN bool_t	g_flg_skip_demo_cut_in;

/* 星の数 CUI */
EXTERN long	g_cui_star_n;

/* 星の数 GUI */
EXTERN long	g_gui_star_n;

/* デバッグ・モード */
EXTERN bool_t	g_flg_debug;

/* メモリー・チェック */
EXTERN bool_t	g_flg_check_memory;

#ifdef __cplusplus
}
#endif

#endif	/* GMAIN_H */
