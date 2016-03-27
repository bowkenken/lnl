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
* $Id: resi.h,v 1.25 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	RESI_H
#define	RESI_H

/* ������ */

#define	RESI_300	300
#define	RESI_200	200
#define	RESI_150	150
#define	RESI_120	120
#define	RESI_100	100
#define	RESI__80	80
#define	RESI__50	50
#define	RESI__30	30
#define	RESI_PRF	30000	/* �������� */
#define	RESI_PERFECT_N	(RESI_PRF)	/* �������� */
#define	RESI_MAX_N	(RESI_PERFECT_N - 1)	/* ������ */

/* ���֤��Ѥ�����ϥ����֡��ǡ����⽤������ */
typedef enum {
	RESI_KIND_KNOC,	/* ���� */
	RESI_KIND_SLAS,	/* �·� */
	RESI_KIND_STIN,	/* ���� */
	RESI_KIND_HEAT,	/* ��Ǯ */
	RESI_KIND_COLD,	/* ���� */
	RESI_KIND_MIND,	/* ���� */
	RESI_KIND_ACID,	/* �ڻ� */
	RESI_KIND_ELEC,	/* ���� */
	RESI_KIND_POIS,	/* ���� */
	RESI_KIND_MAX_N,
} resi_kind_t;


typedef struct {
	rate_t	n;	/* ������ */
	rate_t	max;	/* ������ */
	rate_t	add_n;	/* ������ */
} resi_t;

#endif	/* RESI_H */
