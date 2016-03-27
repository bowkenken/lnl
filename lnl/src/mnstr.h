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
* $Id: mnstr.h,v 1.42 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MNSTR_H
#define	MNSTR_H

/***************************************************************
* ��󥹥���
***************************************************************/

#include	"chr.h"
#include	"mnstr-kind.h"

/* ��󥹥����ο� */

/* ����� */
#define	MNSTR_MAX_N	128
/* ʿ�ѽи��� */
#define	MNSTR_AVE_N	16

/* ��󥹥�������ư���롢��Υ�κ� */
#define	MNSTR_MOVE_MAX_X	(AREA_MAX_X * 4 + 0)
#define	MNSTR_MOVE_MAX_Y	(AREA_MAX_Y * 4 + 0)

/* �ᤤ��Ƚ�Ǥ����Υ */
#define	MNSTR_NEAR_R	4

/* ��󥹥�����ɤ�ݤ��ȥ��С��Υ�٥뤬�夬�뤫���ܰ� */
#define	EXP_NEED_KILL_MNSTR_N	20

/* ��󥹥����������ƥ�����Ψ */
#define	ITEM_DROP_RATE_100	((rate_t)100)

#define	ITEM_DROP_RATE_AAA	((rate_t)90)
#define	ITEM_DROP_RATE_AA	((rate_t)80)
#define	ITEM_DROP_RATE_A	((rate_t)70)

#define	ITEM_DROP_RATE_BBB	((rate_t)60)
#define	ITEM_DROP_RATE_BB	((rate_t)50)
#define	ITEM_DROP_RATE_B	((rate_t)40)

#define	ITEM_DROP_RATE_CCC	((rate_t)30)
#define	ITEM_DROP_RATE_CC	((rate_t)20)
#define	ITEM_DROP_RATE_C	((rate_t)10)

#define	ITEM_DROP_RATE_DDD	((rate_t)5)
#define	ITEM_DROP_RATE_DD	((rate_t)3)
#define	ITEM_DROP_RATE_D	((rate_t)1)

#define	ITEM_DROP_RATE_0	((rate_t)0)

/***************************************************************
* �ǡ����������
***************************************************************/

/* ��󥹥����Υǡ��� */

typedef chr_t	mnstr_t;

/* ��󥹥����Τ��ʤ����򹶷⤷�����Υ��ߡ� */

typedef struct {
	long	x, y;
} mnstr_null_t;

/* ��󥹥����νи������Υǡ��� */

typedef struct {
	/* ��󥹥����μ��� */
	mnstr_kind_t	kind;

	/* ȯ�����볬�κǾ�������κ�ʬ */
	long	add_lev, range_lev;

	/* ȯ�����볬�κǾ������� */
	/* ������ؿ��Ǽ�ư�׻����� */
	long	min_lev, max_lev;
} mnstr_lev_tab_t;

/* �饹�ܥ��μ��� */

typedef enum {
	LAST_BOSS_KIND_NULL,
	LAST_BOSS_KIND_EXEL,
	LAST_BOSS_KIND_EXELER,
	LAST_BOSS_KIND_XEX,
	LAST_BOSS_KIND_XX,
	LAST_BOSS_KIND_MAX_N,
} last_boss_kind_t;

#endif	/* MNSTR_H */
