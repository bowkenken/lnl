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
* $Id: fx-menu-tab.h,v 1.5 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	FX_MENU_TAB_H
#define	FX_MENU_TAB_H

/* エフェクトのメニュー */

/* 骨の選択 */
menu_t	ls_menu_summon_bone[MBR_ITEM_MAX_N * 2 + 1];

/* 望みの選択 */
menu_t	ls_menu_wish[] = {
	{
		"/wish",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/wish/title",
		"<Title>",
		'\0',
		"",
		N_MSG_TTL_MENU_WISH, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/wish/",
		"<Item>",
		'H',
		"",
		N_MSG_MENU_WISH_CURE_HP, "",
		cb_menu_sel_wish, (void *)WISH_KIND_CURE_HP,
		FLG_NULL,
	},
	{
		"/wish/",
		"<Item>",
		'M',
		"",
		N_MSG_MENU_WISH_CURE_MP, "",
		cb_menu_sel_wish, (void *)WISH_KIND_CURE_MP,
		FLG_NULL,
	},
	{
		"/wish/",
		"<Item>",
		'R',
		"",
		N_MSG_MENU_WISH_RESURRECTION, "",
		cb_menu_sel_wish, (void *)WISH_KIND_RESURRECTION,
		FLG_NULL,
	},
	{
		"/wish/",
		"<Item>",
		'A',
		"",
		N_MSG_MENU_WISH_ARTIFACT, "",
		cb_menu_sel_wish, (void *)WISH_KIND_ARTIFACT,
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

#endif	/* FX_MENU_TAB_H */
