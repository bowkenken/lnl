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
* $Id: rumor-tab.h,v 1.12 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	RUMOR_TAB_H
#define	RUMOR_TAB_H

/* ���α� */

typedef struct {
	/* �������� */
	n_msg_t	n_msg_female, n_msg_male;

	/* ʹ��Я�������ե饰 */
	bool_t	flg_open;

	/* ͥ��Ū��ʹ�����ǿ��α��Υե饰 */
	bool_t	flg_latest;
} rumor_tab_t;

rumor_tab_t	rumor_tab[] = {
	{
		N_MSG_RUMOR_001_FEMALE,
		N_MSG_RUMOR_001_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_002_FEMALE,
		N_MSG_RUMOR_002_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_003_FEMALE,
		N_MSG_RUMOR_003_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_004_FEMALE,
		N_MSG_RUMOR_004_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_005_FEMALE,
		N_MSG_RUMOR_005_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_006_FEMALE,
		N_MSG_RUMOR_006_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_007_FEMALE,
		N_MSG_RUMOR_007_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_008_FEMALE,
		N_MSG_RUMOR_008_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_NULL,
		N_MSG_NULL,
		FALSE, FALSE,
	},
};

#endif	/* RUMOR_TAB_H */
