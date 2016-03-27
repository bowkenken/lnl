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
* $Id: menu.h,v 1.56 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MENU_H
#define	MENU_H

/* メニュー */

#include	"item.h"
#include	"party.h"
#include	"msg.h"

/***************************************************************/

/**** 戻り値 ****/

#define	STR_MENU_ERR	"# Error"
#define	STR_MENU_CANCEL	".."

/**** メニュー操作用のキー ****/

#define	CASE_ENTER	\
		'M' - '@': case 'J' - '@'
#define	CASE_CANCEL	\
		'G' - '@': case 'H' - '@': case '0': case '\033'
#define	CASE_EXEC	\
		'5': case '.'
#define	CASE_EXIT	\
		'Q': case 'Q' - '@': case 'C' - '@'
#define	CASE_SQUARE	\
		'v': case '+'

#define	CASE_CRSR_UP	\
		'8': case 'k': case 'w': case 'P' - '@'
#define	CASE_CRSR_DOWN	\
		'2': case 'j': case 's': case 'N' - '@'
#define	CASE_CRSR_LEFT	\
		'4': case 'h': case 'a': case 'B' - '@'
#define	CASE_CRSR_RIGHT	\
		'6': case 'l': case 'd': case 'F' - '@'
#define	CASE_CRSR_UP_LEFT	\
		'7': case 'y'
#define	CASE_CRSR_UP_RIGHT	\
		'9': case 'u'
#define	CASE_CRSR_DOWN_LEFT	\
		'1': case 'b'
#define	CASE_CRSR_DOWN_RIGHT	\
		'3': case 'n'

/* 項目の最大文字数 */
#define	MENU_MAX_LEN	(SCREEN_WIDTH - 4)
#define	MENU_MAX_BYTE	(MENU_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* ページあたりの最大項目数 */
#define	MENU_MAX_N_PER_PAGE	18

/* 最大ページ数 */
#define	MENU_MAX_PAGE	32

/* 最大項目数 */
#define	MENU_MAX_N	(MENU_MAX_N_PER_PAGE * MENU_MAX_PAGE)

/**** フラグ ****/

typedef unsigned long	flg_menu_t;

/* 無効 */
#define	FLG_MENU_DIS	(1 << 0)

/* 非表示 */
#define	FLG_MENU_HIDDEN	(1 << 1)

/* チェック・オン */
#define	FLG_MENU_CHK_ON	(1 << 4)

/* チェック・オフ */
#define	FLG_MENU_CHK_OFF	(1 << 5)

#define	FLG_MENU_ALL	\
	(FLG_MENU_DIS | FLG_MENU_HIDDEN \
	| FLG_MENU_CHK_ON | FLG_MENU_CHK_OFF)

/****  ****/

/* メニュー・パスの最大文字数 */
#define	MENU_PATH_MAX_LEN	80

/* 項目の種類の最大文字数 */
#define	MENU_KIND_MAX_LEN	16

/* マクロの最大文字数 */
#define	MACRO_MAX_LEN	256

/* ショート・カット・キーの最大文字数 */
#define	MENU_SHORT_KEY_MAX_LEN	16

/* 項目の最大文字数 */
#define	MENU_MSG_MAX_LEN	80
#define	MENU_MSG_MAX_BYTE	(MENU_MSG_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/**** セーブ・ロード ****/

#define	MENU_SAVE_LOAD_MAX_N	40
#define	MENU_SAVE_LOAD_N_PER_PAGE	10

/**** キャラクタ・シート ****/

/* キャラクタ・シートの最大ページ数 */
#define	MBR_DATA_PAGE_MAX_N	6

/**** ユーザ・メニュー ****/

/* ユーザ・メニューの最大項目数 */
#define	USER_MENU_MAX_N	(MENU_MAX_N_PER_PAGE * 4)

/**** コマンド・メニュー ****/

#define	MENU_COMMAND_KEY_CHAR	':'
#define	MENU_COMMAND_KEY_STR	":"
#define	MENU_COMMAND_MAX_LEN	2048

/**** メニュー選択時のコール・バック関数 ****/

struct menu_t;
typedef char	*(*menu_call_back_t)(
	struct menu_t **pp, struct menu_t **dflt );

/**** マップのスクロール ****/

typedef unsigned long	flg_scroll_t;
#define	FLG_SCROLL_SMOOTH	(1 << 0)
#define	FLG_SCROLL_CENTER	(1 << 1)

/***************************************************************/

/* メニュー */

typedef struct menu_t {
	/* 木構造のパス */
	char	path[MENU_PATH_MAX_LEN + 1];
	/* 項目の種類 */
	char	kind[MENU_KIND_MAX_LEN + 1];

	/* アクセラレータ・キー */
	unsigned char	accel_key;
	/* ショート・カット・キー */
	char	short_key[MENU_SHORT_KEY_MAX_LEN + 1];

	/* 項目名 */
	n_msg_t	n_msg;
	char	msg[MENU_MSG_MAX_BYTE + 1];

	/* コール・バック関数 */
	menu_call_back_t	call_back;
	/* コール・バック関数への引数 */
	void	*arg;

	/* フラグ */
	flg_menu_t	flg;
} menu_t;

typedef struct {
	/* タイトル */
	char	*ttl;

	/* 元のメニューのリスト */
	menu_t	*ls[MENU_MAX_N_PER_PAGE + 1];

	/* 選択されている項目の番号 */
	long	sel_n, prev_sel_n;

	/* ページ数 */
	long	page_sel_n, page_max_n;

	/* 先頭・最終ページである亊のフラグ */
	bool_t	flg_min_page, flg_max_page;

	/* 再描画フラグ */
	bool_t	flg_redraw;
} draw_menu_t;

/* はい・いいえ */

typedef enum {
	ASK_NO,
	ASK_YES,
	ASK_CANCEL,
	ASK_ERR,
} ask_t;

/* 取り引きの種類 */

typedef enum {
	DEAL_KIND_BUY,	/* 買う */
	DEAL_KIND_SALE_ITEM,	/* アイテムを売る */
	DEAL_KIND_SALE_EQUIP,	/* 装備を売る */
} deal_kind_t;

/* 数値入力 */

typedef enum {
	MENU_NUM_MIN,
	MENU_NUM_MAX,
	MENU_NUM_CLR,
	MENU_NUM_OK,
	MENU_NUM_MAX_N
} menu_num_t;

/* 数値入力キー */

#define	KEY_MENU_NUM_OK	'Z'
#define	KEY_MENU_NUM_CLR	'Y'
#define	KEY_MENU_NUM_MAX	'X'
#define	KEY_MENU_NUM_MIN	'W'
#define	KEY_MENU_NUM_SGN	'V'

/* オブジェクト選択 */

typedef enum {
	NEXT_POS_KIND_SQUARE,
	NEXT_POS_KIND_MBR,
	NEXT_POS_KIND_MNSTR,
	NEXT_POS_KIND_DOOR,
	NEXT_POS_KIND_OBJ,
} next_pos_kind_t;

typedef struct {
	next_pos_kind_t	kind;
	void	*p;
	long	n;
	int	x, y;
} next_pos_t;

/* メンバー・データの編集モード */

typedef enum {
	MBR_DATA_EDIT_KIND_SHOW,	/* 表示のみ */
	MBR_DATA_EDIT_KIND_EDIT,	/* 編集 */
	MBR_DATA_EDIT_KIND_NEW,	/* 新規 */
	MBR_DATA_EDIT_KIND_MAX_N,
} mbr_data_edit_kind_t;

#endif	/* MENU_H */
