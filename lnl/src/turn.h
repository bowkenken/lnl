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
* $Id: turn.h,v 1.17 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	TURN_H
#define	TURN_H

/***************************************************************
* ������
***************************************************************/

/* ��������θ�Ĵ�� */
#define	ADJUST_TURN	1

/* ��Υ������ */
#define	TURN_DAYTIME	(TURN_A_DAY / 2)

/* ��Υ������ */
#define	TURN_NIGHT	(TURN_A_DAY / 2)

/* �����Υ������ */
#define	TURN_A_DAY	(24 * TURN_PER_HOUR)

/* �����֤Υ������ */
#define	TURN_PER_HOUR	(60 * TURN_PER_MINUTE)

/* ��ʬ�Υ������ */
#define	TURN_PER_MINUTE	(60 / SECOND_PER_TURN)

/* ����������ÿ� */
#define	SECOND_PER_TURN	10

/* ���νФλ��� */
#define	MORNING_HOUR	6

/* ��������λ��� */
#define	EVENING_HOUR	17

/* ������ */
typedef enum {
	DAY_OF_WEEK_ELEC,
	DAY_OF_WEEK_PHYS,
	DAY_OF_WEEK_HEAT,
	DAY_OF_WEEK_COLD,
	DAY_OF_WEEK_WIND,
	DAY_OF_WEEK_ACID,
	DAY_OF_WEEK_POIS,
	DAY_OF_WEEK_MAX_N,
} day_of_week_t;

#endif	/* TURN_H */
