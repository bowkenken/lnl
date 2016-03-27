/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ������ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�������
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�������ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ������Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: crsr-ptn.h,v 1.13 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	CRSR_PTN_H
#define	CRSR_PTN_H

/* ��������Υѥ����󡦥ǡ��� */

crsr_ptn_t	crsr_ptn_dflt[] = {
	{
		-1, -1,
		0, 0,
		'@',
		{
			"@@| @@",
			"- @@- ",
			"@@| @@",
		},
	},
	{
		-1, -1,
		0, 0,
		'@',
		{
			"@\\@@/@",
			"@@@@@@",
			"@/@@\\@",
		},
	},
	{
		-1, +0,
		0, 0,
		'@',
		{
			"@@@@<=",
		},
	},
	{
		+0, +0,
		0, 0,
		'@',
		{
			"@@",
		},
	},
};

#endif	/* CRSR_PTN_H */