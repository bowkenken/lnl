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
* $Id: menu-tab.h,v 1.30 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MENU_TAB_H
#define	MENU_TAB_H

/* ��˥塼 */

#if	0
char	*menu_kind_ls[] = {
	/* �����ȥ� */
	"<Title>",

	/* ���� */
	"<Item>",

	/* �����å����� */
	"<CheckItem>",

	/* ������� */
	"<RadioItem>",

	/* �̥�����ɥ��򳫤����� */
	"<OpenWinItem>",

	/* <RadioItem>�ζ��ڤ� */
	"<Separator>",

	/* ��˥塼��ʣ���ڡ���ͭ����ζ��ڤ� */
	"<PageSeparator>",

	/* ���֥�˥塼 */
	"<Branch>",

	NULL,
};
#endif

#if	0
typedef struct menu_t {
	/* �ڹ�¤�Υѥ� */
	char	path[MENU_PATH_MAX_LEN + 1];
	/* ���ܤμ��� */
	char	kind[MENU_KIND_MAX_LEN + 1];

	/* ľ������Υ��� */
	unsigned char	key;
	/* ���硼�ȡ����åȡ����� */
	char	accel_key[MENU_ACCEL_KEY_MAX_LEN + 1];

	/* ����̾ */
	n_msg_t	n_msg;
	char	msg[MENU_MSG_MAX_BYTE + 1];

	/* �����롦�Хå��ؿ� */
	menu_call_back_t	call_back;
	/* �����롦�Хå��ؿ��ؤΰ��� */
	void	*arg;

	/* �ե饰 */
	unsigned long	flg;
} menu_t;
#endif

/* ��˥塼�ꥹ�� */

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
