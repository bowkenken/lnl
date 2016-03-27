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
* $Id: menu-tab.h,v 1.30 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MENU_TAB_H
#define	MENU_TAB_H

/* メニュー */

#if	0
char	*menu_kind_ls[] = {
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
#endif

#if	0
typedef struct menu_t {
	/* 木構造のパス */
	char	path[MENU_PATH_MAX_LEN + 1];
	/* 項目の種類 */
	char	kind[MENU_KIND_MAX_LEN + 1];

	/* 直接選択のキー */
	unsigned char	key;
	/* ショート・カット・キー */
	char	accel_key[MENU_ACCEL_KEY_MAX_LEN + 1];

	/* 項目名 */
	n_msg_t	n_msg;
	char	msg[MENU_MSG_MAX_BYTE + 1];

	/* コール・バック関数 */
	menu_call_back_t	call_back;
	/* コール・バック関数への引数 */
	void	*arg;

	/* フラグ */
	unsigned long	flg;
} menu_t;
#endif

/* メニューリスト */

menu_t	ls_menu_ask[] = {
	{
		"/ask",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		cb_menu_ask_init, NULL,
		FLG_NULL,
	},
	{
		"/ask/title",
		"<Title>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/ask/yes",
		"<Item>",
		'Y',
		"",
		N_MSG_MENU_YES, "",
		cb_menu_ask_yes, NULL,
		FLG_NULL,
	},
	{
		"/ask/no",
		"<Item>",
		'N',
		"",
		N_MSG_MENU_NO, "",
		cb_menu_ask_no, NULL,
		FLG_NULL,
	},
	{
		"",
		"",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
};

menu_t	ls_menu_macro_func[
	1 + 1 + (6 * KEY_N_FUNC_MAX_N)
	+ (KEY_N_FUNC_MAX_N / MENU_MACRO_FUNC_MAX_N_PER_PAGE)
	+ 1
];

menu_t	ls_menu_macro_mouse[
	1 + 1 + (6 * KEY_N_MOUSE_MAX_N)
	+ (2 * KEY_N_MOUSE_MAX_N / MENU_MACRO_MOUSE_MAX_N_PER_PAGE)
	+ 1
];

menu_t	ls_menu_macro_joystick[
	1 + 1 + (6 * KEY_N_JOYSTICK_MAX_N)
	+ (2 * KEY_N_JOYSTICK_MAX_N / MENU_MACRO_JOYSTICK_MAX_N_PER_PAGE)
	+ 1
];

#endif	/* MENU_TAB_H */
