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
* $Id: fx-menu-tab.h,v 1.5 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	FX_MENU_TAB_H
#define	FX_MENU_TAB_H

/* ���ե����ȤΥ�˥塼 */

/* �������� */
menu_t	ls_menu_summon_bone[MBR_ITEM_MAX_N * 2 + 1];

/* ˾�ߤ����� */
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
