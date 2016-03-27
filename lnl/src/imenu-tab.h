/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ����ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�����
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�����ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ����Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: imenu-tab.h,v 1.18 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	IMENU_TAB_H
#define	IMENU_TAB_H

/* ����¾�Υ�˥塼 */

menu_t	ls_menu_srch[1 + 4 + MBR_MAX_N + 1];
menu_t	ls_menu_formation[1 + 1 + MBR_MAX_N + 1];

menu_t	ls_menu_position[] = {
	{
		"/position",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/position/title",
		"<Title>",
		'\0',
		"",
		N_MSG_MENU_POSITION, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/position/forward",
		"<RadioItem>",
		'F',
		"",
		N_MSG_MENU_POSITION_FORWARD, "",
		cb_menu_position_sel, (void *)POSITION_KIND_FORWARD,
		FLG_NULL,
	},
	{
		"/position/halfback",
		"<RadioItem>",
		'H',
		"",
		N_MSG_MENU_POSITION_HALFBACK, "",
		cb_menu_position_sel, (void *)POSITION_KIND_HALFBACK,
		FLG_NULL,
	},
	{
		"/position/back",
		"<RadioItem>",
		'B',
		"",
		N_MSG_MENU_POSITION_BACK, "",
		cb_menu_position_sel, (void *)POSITION_KIND_BACK,
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

menu_t	ls_menu_move_crsr[] = {
	{
		"/cursor",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* cursor move begin */
	{
		"/cursor/move",
		"<Branch>",
		'M',
		"",
		N_MSG_MENU_CRSR_MOVE, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/cursor/move/south west",
		"<Item>",
		'B',
		"1 b",
		N_MSG_MENU_CRSR_MOVE_DOWN_LEFT, "",
		cb_menu_crsr_move, (void *)1,
		FLG_NULL,
	},
	{
		"/cursor/move/south",
		"<Item>",
		'J',
		"^N s 2 j",
		N_MSG_MENU_CRSR_MOVE_DOWN, "",
		cb_menu_crsr_move, (void *)2,
		FLG_NULL,
	},
	{
		"/cursor/move/south east",
		"<Item>",
		'N',
		"3 n",
		N_MSG_MENU_CRSR_MOVE_DOWN_RIGHT, "",
		cb_menu_crsr_move, (void *)3,
		FLG_NULL,
	},
	{
		"/cursor/move/west",
		"<Item>",
		'H',
		"^B a 4 h",
		N_MSG_MENU_CRSR_MOVE_LEFT, "",
		cb_menu_crsr_move, (void *)4,
		FLG_NULL,
	},
	{
		"/cursor/move/east",
		"<Item>",
		'L',
		"^F d 6 l",
		N_MSG_MENU_CRSR_MOVE_RIGHT, "",
		cb_menu_crsr_move, (void *)6,
		FLG_NULL,
	},
	{
		"/cursor/move/north west",
		"<Item>",
		'Y',
		"7 y",
		N_MSG_MENU_CRSR_MOVE_UP_LEFT, "",
		cb_menu_crsr_move, (void *)7,
		FLG_NULL,
	},
	{
		"/cursor/move/north",
		"<Item>",
		'K',
		"^P w 8 k",
		N_MSG_MENU_CRSR_MOVE_UP, "",
		cb_menu_crsr_move, (void *)8,
		FLG_NULL,
	},
	{
		"/cursor/move/north east",
		"<Item>",
		'U',
		"9 u",
		N_MSG_MENU_CRSR_MOVE_UP_RIGHT, "",
		cb_menu_crsr_move, (void *)9,
		FLG_NULL,
	},
	{
		"/cursor/move/abs",
		"<Item>",
		'A',
		"%",
		N_MSG_MENU_CRSR_MOVE_ABS, "",
		cb_menu_crsr_move_abs, NULL,
		FLG_NULL,
	},
	{
		"/cursor/move/stop",
		"<Item>",
		'S',
		"|",
		N_MSG_MENU_CRSR_MOVE_STOP, "",
		cb_menu_crsr_move_stop, NULL,
		FLG_NULL,
	},
/* cursor move end */
/* cursor quick move begin */
	{
		"/cursor/quick move",
		"<Branch>",
		'Q',
		"",
		N_MSG_MENU_CRSR_QUICK_MOVE, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/cursor/quick move/south west",
		"<Item>",
		'B',
		"B",
		N_MSG_MENU_CRSR_QUICK_MOVE_DOWN_LEFT, "",
		cb_menu_crsr_quick_move, (void *)1,
		FLG_NULL,
	},
	{
		"/cursor/quick move/south",
		"<Item>",
		'J',
		"J",
		N_MSG_MENU_CRSR_QUICK_MOVE_DOWN, "",
		cb_menu_crsr_quick_move, (void *)2,
		FLG_NULL,
	},
	{
		"/cursor/quick move/south east",
		"<Item>",
		'N',
		"N",
		N_MSG_MENU_CRSR_QUICK_MOVE_DOWN_RIGHT, "",
		cb_menu_crsr_quick_move, (void *)3,
		FLG_NULL,
	},
	{
		"/cursor/quick move/west",
		"<Item>",
		'H',
		"H",
		N_MSG_MENU_CRSR_QUICK_MOVE_LEFT, "",
		cb_menu_crsr_quick_move, (void *)4,
		FLG_NULL,
	},
	{
		"/cursor/quick move/east",
		"<Item>",
		'L',
		"L",
		N_MSG_MENU_CRSR_QUICK_MOVE_RIGHT, "",
		cb_menu_crsr_quick_move, (void *)6,
		FLG_NULL,
	},
	{
		"/cursor/quick move/north west",
		"<Item>",
		'Y',
		"Y",
		N_MSG_MENU_CRSR_QUICK_MOVE_UP_LEFT, "",
		cb_menu_crsr_quick_move, (void *)7,
		FLG_NULL,
	},
	{
		"/cursor/quick move/north",
		"<Item>",
		'K',
		"K",
		N_MSG_MENU_CRSR_QUICK_MOVE_UP, "",
		cb_menu_crsr_quick_move, (void *)8,
		FLG_NULL,
	},
	{
		"/cursor/quick move/north east",
		"<Item>",
		'U',
		"U",
		N_MSG_MENU_CRSR_QUICK_MOVE_UP_RIGHT, "",
		cb_menu_crsr_quick_move, (void *)9,
		FLG_NULL,
	},
/* cursor quick move end */
	{
		"/cursor/individual square",
		"<Branch>",
		'V',
		"t",
		N_MSG_MENU_CRSR_IND_SQUARE, "",
		cb_menu_crsr_ind_square, NULL,
		FLG_NULL,
	},
/* cursor scroll begin */
	{
		"/cursor/scroll",
		"<Branch>",
		'S',
		"",
		N_MSG_MENU_CRSR_SCROLL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/cursor/scroll/south west",
		"<Item>",
		'B',
		"",
		N_MSG_MENU_CRSR_SCROLL_DOWN_LEFT, "",
		cb_menu_crsr_scroll, (void *)1,
		FLG_NULL,
	},
	{
		"/cursor/scroll/south",
		"<Item>",
		'J',
		"",
		N_MSG_MENU_CRSR_SCROLL_DOWN, "",
		cb_menu_crsr_scroll, (void *)2,
		FLG_NULL,
	},
	{
		"/cursor/scroll/south east",
		"<Item>",
		'N',
		"",
		N_MSG_MENU_CRSR_SCROLL_DOWN_RIGHT, "",
		cb_menu_crsr_scroll, (void *)3,
		FLG_NULL,
	},
	{
		"/cursor/scroll/west",
		"<Item>",
		'H',
		"",
		N_MSG_MENU_CRSR_SCROLL_LEFT, "",
		cb_menu_crsr_scroll, (void *)4,
		FLG_NULL,
	},
	{
		"/cursor/scroll/east",
		"<Item>",
		'L',
		"",
		N_MSG_MENU_CRSR_SCROLL_RIGHT, "",
		cb_menu_crsr_scroll, (void *)6,
		FLG_NULL,
	},
	{
		"/cursor/scroll/north west",
		"<Item>",
		'Y',
		"",
		N_MSG_MENU_CRSR_SCROLL_UP_LEFT, "",
		cb_menu_crsr_scroll, (void *)7,
		FLG_NULL,
	},
	{
		"/cursor/scroll/north",
		"<Item>",
		'K',
		"",
		N_MSG_MENU_CRSR_SCROLL_UP, "",
		cb_menu_crsr_scroll, (void *)8,
		FLG_NULL,
	},
	{
		"/cursor/scroll/north east",
		"<Item>",
		'U',
		"",
		N_MSG_MENU_CRSR_SCROLL_UP_RIGHT, "",
		cb_menu_crsr_scroll, (void *)9,
		FLG_NULL,
	},
/* cursor scroll end */
	{
		"/cursor/move member",
		"<Branch>",
		'P',
		"@",
		N_MSG_MENU_CRSR_MOVE_MBR, "",
		cb_menu_crsr_move_mbr, NULL,
		FLG_NULL,
	},
	{
		"/cursor/center",
		"<Item>",
		'C',
		"^L",
		N_MSG_MENU_CRSR_CENTER, "",
		cb_menu_crsr_center, NULL,
		FLG_NULL,
	},
/* cursor next position begin */
	{
		"/cursor/next position",
		"<Branch>",
		'N',
		"",
		N_MSG_MENU_CRSR_NEXT_POS, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/cursor/next position/member",
		"<Item>",
		'P',
		"P",
		N_MSG_MENU_CRSR_NEXT_POS_MBR, "",
		cb_menu_crsr_next_pos_mbr, NULL,
		FLG_NULL,
	},
	{
		"/cursor/next position/monster",
		"<Item>",
		'X',
		"^I X",
		N_MSG_MENU_CRSR_NEXT_POS_MNSTR, "",
		cb_menu_crsr_next_pos_mnstr, NULL,
		FLG_NULL,
	},
	{
		"/cursor/next position/item",
		"<Item>",
		'I',
		"I",
		N_MSG_MENU_CRSR_NEXT_POS_ITEM, "",
		cb_menu_crsr_next_pos_item, NULL,
		FLG_NULL,
	},
	{
		"/cursor/next position/door",
		"<Item>",
		'D',
		"D",
		N_MSG_MENU_CRSR_NEXT_POS_DOOR, "",
		cb_menu_crsr_next_pos_door, NULL,
		FLG_NULL,
	},
	{
		"/cursor/next position/object",
		"<Item>",
		'O',
		"O",
		N_MSG_MENU_CRSR_NEXT_POS_OBJ, "",
		cb_menu_crsr_next_pos_obj, NULL,
		FLG_NULL,
	},
	{
		"/cursor/next position/square",
		"<Item>",
		'V',
		"V",
		N_MSG_MENU_CRSR_NEXT_POS_SQUARE, "",
		cb_menu_crsr_next_pos_square, NULL,
		FLG_NULL,
	},
	{
		"/cursor/next position/all",
		"<Item>",
		'A',
		"A",
		N_MSG_MENU_CRSR_NEXT_POS_ALL, "",
		cb_menu_crsr_next_pos_all, NULL,
		FLG_NULL,
	},
	{
		"/cursor/next position/prev",
		"<Item>",
		'R',
		"R",
		N_MSG_MENU_CRSR_PREV_POS, "",
		cb_menu_crsr_prev_pos, NULL,
		FLG_NULL,
	},
/* cursor next position end */
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

menu_t	ls_menu_mbr_flg[MBR_ITEM_MAX_N + 4];

menu_t	ls_menu_lang_ls[LANG_KIND_MAX_N * 2];

menu_t	ls_menu_color[2 + 1 + CURS_ATTR_N_MAX_N + 10 + 1];
menu_t	ls_menu_color_sel[] = {
	{
		"/color",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* FG */
	{
		"/color/fg",
		"<Branch>",
		'F',
		"",
		N_MSG_MENU_FG, "",
		cb_menu_fg_init, NULL,
		FLG_NULL,
	},
	{
		"/color/fg/black",
		"<Item>",
		'K',
		"",
		N_MSG_MENU_COLOR_BLACK, "",
		cb_menu_fg, (void *)COLOR_BLACK,
		FLG_NULL,
	},
	{
		"/color/fg/red",
		"<Item>",
		'R',
		"",
		N_MSG_MENU_COLOR_RED, "",
		cb_menu_fg, (void *)COLOR_RED,
		FLG_NULL,
	},
	{
		"/color/fg/green",
		"<Item>",
		'G',
		"",
		N_MSG_MENU_COLOR_GREEN, "",
		cb_menu_fg, (void *)COLOR_GREEN,
		FLG_NULL,
	},
	{
		"/color/fg/yellow",
		"<Item>",
		'Y',
		"",
		N_MSG_MENU_COLOR_YELLOW, "",
		cb_menu_fg, (void *)COLOR_YELLOW,
		FLG_NULL,
	},
	{
		"/color/fg/blue",
		"<Item>",
		'B',
		"",
		N_MSG_MENU_COLOR_BLUE, "",
		cb_menu_fg, (void *)COLOR_BLUE,
		FLG_NULL,
	},
	{
		"/color/fg/magenta",
		"<Item>",
		'M',
		"",
		N_MSG_MENU_COLOR_MAGENTA, "",
		cb_menu_fg, (void *)COLOR_MAGENTA,
		FLG_NULL,
	},
	{
		"/color/fg/cyan",
		"<Item>",
		'C',
		"",
		N_MSG_MENU_COLOR_CYAN, "",
		cb_menu_fg, (void *)COLOR_CYAN,
		FLG_NULL,
	},
	{
		"/color/fg/white",
		"<Item>",
		'W',
		"",
		N_MSG_MENU_COLOR_WHITE, "",
		cb_menu_fg, (void *)COLOR_WHITE,
		FLG_NULL,
	},
/* BG */
	{
		"/color/bg",
		"<Branch>",
		'B',
		"",
		N_MSG_MENU_BG, "",
		cb_menu_bg_init, NULL,
		FLG_NULL,
	},
	{
		"/color/bg/black",
		"<Item>",
		'K',
		"",
		N_MSG_MENU_COLOR_BLACK, "",
		cb_menu_bg, (void *)COLOR_BLACK,
		FLG_NULL,
	},
	{
		"/color/bg/red",
		"<Item>",
		'R',
		"",
		N_MSG_MENU_COLOR_RED, "",
		cb_menu_bg, (void *)COLOR_RED,
		FLG_NULL,
	},
	{
		"/color/bg/green",
		"<Item>",
		'G',
		"",
		N_MSG_MENU_COLOR_GREEN, "",
		cb_menu_bg, (void *)COLOR_GREEN,
		FLG_NULL,
	},
	{
		"/color/bg/yellow",
		"<Item>",
		'Y',
		"",
		N_MSG_MENU_COLOR_YELLOW, "",
		cb_menu_bg, (void *)COLOR_YELLOW,
		FLG_NULL,
	},
	{
		"/color/bg/blue",
		"<Item>",
		'B',
		"",
		N_MSG_MENU_COLOR_BLUE, "",
		cb_menu_bg, (void *)COLOR_BLUE,
		FLG_NULL,
	},
	{
		"/color/bg/magenta",
		"<Item>",
		'M',
		"",
		N_MSG_MENU_COLOR_MAGENTA, "",
		cb_menu_bg, (void *)COLOR_MAGENTA,
		FLG_NULL,
	},
	{
		"/color/bg/cyan",
		"<Item>",
		'C',
		"",
		N_MSG_MENU_COLOR_CYAN, "",
		cb_menu_bg, (void *)COLOR_CYAN,
		FLG_NULL,
	},
	{
		"/color/bg/white",
		"<Item>",
		'W',
		"",
		N_MSG_MENU_COLOR_WHITE, "",
		cb_menu_bg, (void *)COLOR_WHITE,
		FLG_NULL,
	},
/* Attr */
	{
		"/color/attribute",
		"<Branch>",
		'A',
		"",
		N_MSG_MENU_ATTR, "",
		cb_menu_attr_init, NULL,
		FLG_NULL,
	},
	{
		"/color/attribute/underline",
		"<CheckItem>",
		'U',
		"",
		N_MSG_MENU_UNDERLINE, "",
		cb_menu_attr, (void *)A_UNDERLINE,
		FLG_NULL,
	},
	{
		"/color/attribute/reverse",
		"<CheckItem>",
		'R',
		"",
		N_MSG_MENU_REVERSE, "",
		cb_menu_attr, (void *)A_REVERSE,
		FLG_NULL,
	},
	{
		"/color/attribute/blink",
		"<CheckItem>",
		'L',
		"",
		N_MSG_MENU_BLINK, "",
		cb_menu_attr, (void *)A_BLINK,
		FLG_NULL,
	},
	{
		"/color/attribute/bold",
		"<CheckItem>",
		'B',
		"",
		N_MSG_MENU_BOLD, "",
		cb_menu_attr, (void *)A_BOLD,
		FLG_NULL,
	},
/* End */
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

menu_t	ls_menu_crsr_ptn[1 + 1 + CRSR_PTN_MAX_N + 1];
menu_t	ls_menu_user[
	1 + 1
	+ (1 * USER_MENU_MAX_N)
	+ (2 * USER_MENU_MAX_N / MENU_MAX_N_PER_PAGE)
	+ 7 + 1];
menu_t	ls_menu_user_edit[
	1 + 1
	+ (1 * USER_MENU_MAX_N)
	+ (2 * USER_MENU_MAX_N / MENU_MAX_N_PER_PAGE)
	+ 7 + 1];

#endif	/* IMENU_TAB_H */
