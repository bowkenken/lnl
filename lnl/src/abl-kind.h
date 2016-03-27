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
* $Id: abl-kind.h,v 1.13 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	ABL_KIND_H
#define	ABL_KIND_H

/* ǽ���� */

typedef enum {
	/* Hit Point(����) */
	ABL_KIND_HP,
	/* Mana Point(����) */
	ABL_KIND_MP,

	/* DEXterity(������) */
	ABL_KIND_DEX,
	/* STRength(������) */
	ABL_KIND_STR,
	/* AGIlity(�Ҿ���) */
	ABL_KIND_AGI,

	/* INTelligence(����) */
	ABL_KIND_INT,
	/* WISdom(Ƚ����) */
	ABL_KIND_WIS,
	/* CHArisma(̥��) */
	ABL_KIND_CHA,

	/* FIGhter(��Ʈ) */
	ABL_KIND_FIG,
	/* MONk(��Ʈ) */
	ABL_KIND_MON,
	/* HUNter(�ͷ�) */
	ABL_KIND_HUN,
	/* THIef(��±) */
	ABL_KIND_THI,

	/* MAGician(������ˡ) */
	ABL_KIND_MAG,
	/* SORcerer(��Ʈ��ˡ) */
	ABL_KIND_SOR,
	/* ENChanter(�ٱ���ˡ) */
	ABL_KIND_ENC,
	/* SUMmoner(������ˡ) */
	ABL_KIND_SUM,

	/* PRIest(����) */
	ABL_KIND_PRI,
	/* SHAman(������ˡ) */
	ABL_KIND_SHA,
	/* BARd(����) */
	ABL_KIND_BAR,
	/* NINja(Ǧ��) */
	ABL_KIND_NIN,

	ABL_KIND_MAX_N,
} abl_kind_t;

#endif	/* ABL_KIND_H */
