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
* $Id: spell.h,v 1.45 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	SPELL_H
#define	SPELL_H

#include	"gmain.h"
#include	"chr.h"
#include	"msg.h"

#include	"spell-kind.h"
#include	"vfx-kind.h"

/**/

/* ��ʸ�λ��Ѳġ��ԲĤΥꥹ�� */

typedef struct {
	spell_kind_t	kind;
	bool_t	flg_cast;
} cast_tab_t;

/* ��ʸ�θ����ϰ� */

typedef unsigned long	flg_extent_t;

#define	FLG_EXTENT_NORMAL	(1 << 0)
#define	FLG_EXTENT_SPREAD	(1 << 1)
#define	FLG_EXTENT_MASS	(1 << 2)
#define	FLG_EXTENT_LIMIT	(1 << 3)
#define	FLG_EXTENT_HALF	(1 << 4)
#define	FLG_EXTENT_DOUBLE	(1 << 5)

#define	FLG_EXTENT_STD	\
		(FLG_EXTENT_NORMAL \
		| FLG_EXTENT_SPREAD \
		| FLG_EXTENT_MASS)
#define	FLG_EXTENT_ATTACK	\
		(FLG_EXTENT_NORMAL \
		| FLG_EXTENT_SPREAD \
		| FLG_EXTENT_MASS \
		| FLG_EXTENT_HALF \
		| FLG_EXTENT_DOUBLE)
#define	FLG_EXTENT_NORMAL_HALF	\
		(FLG_EXTENT_NORMAL \
		| FLG_EXTENT_HALF)
#define	FLG_EXTENT_BAR	\
		(FLG_EXTENT_NORMAL \
		| FLG_EXTENT_LIMIT)

/* ��ʸ�Υǡ��� */

typedef struct {
	spell_kind_t	kind;
	n_msg_t	n_name;
	char	*name;
	long	hp, mp;	/* ���� HP, MP */
	gold_t	gold;	/* ������ */
	rate_t	resi_down;	/* ���������� */
	long	lev;	/* ���Ѳ�ǽ��٥� */
	abl_kind_t	abl;	/* ɬ��ǽ���� */
	flg_extent_t	flg_extent;	/* �����ϰ� */
	bool_t	flg_trgt;	/* �оݤ���ꤹ�롦���ʤ��ե饰 */
	resi_kind_t	resi;	/* �ɸ椹��¦�������� */
	resi_kind_t	resi_vfx;	/* ��и��̼���(������) */
	gold_t	add_price;	/* ���ʤν����� */
	vfx_kind_t	vfx_kind;	/* ��и��� */
} spell_tab_t;

/* �Ǹ�˻Ȥä���ʸ�Υǡ��� */

typedef struct {
	spell_tab_t	*tab;
	extent_kind_t	extent_kind;
	trgt_t	trgt;
} reg_spell_t;

/* ���� HP */

#define	SPELL_HP_S	32
#define	SPELL_HP_A	16
#define	SPELL_HP_B	8
#define	SPELL_HP_C	4
#define	SPELL_HP_D	2

#define	SPELL_HP_1	1
#define	SPELL_HP_0	0

/* ���� MP */

#define	SPELL_MP_SSS	120
#define	SPELL_MP_SS	100
#define	SPELL_MP_S	80
#define	SPELL_MP_AAA	60
#define	SPELL_MP_AA	40
#define	SPELL_MP_A	20
#define	SPELL_MP_BBB	16
#define	SPELL_MP_BB	14
#define	SPELL_MP_B	12
#define	SPELL_MP_CCC	10
#define	SPELL_MP_CC	8
#define	SPELL_MP_C	6
#define	SPELL_MP_DDD	4
#define	SPELL_MP_DD	2
#define	SPELL_MP_D	1

#define	SPELL_MP_SUM_SSS	240
#define	SPELL_MP_SUM_SS	200
#define	SPELL_MP_SUM_S	160
#define	SPELL_MP_SUM_AAA	120
#define	SPELL_MP_SUM_AA	110
#define	SPELL_MP_SUM_A	100
#define	SPELL_MP_SUM_BBB	90
#define	SPELL_MP_SUM_BB	80
#define	SPELL_MP_SUM_B	70
#define	SPELL_MP_SUM_CCC	60
#define	SPELL_MP_SUM_CC	50
#define	SPELL_MP_SUM_C	40
#define	SPELL_MP_SUM_DDD	30
#define	SPELL_MP_SUM_DD	20
#define	SPELL_MP_SUM_D	10

#define	SPELL_MP_1	1
#define	SPELL_MP_0	0

/* ���� GOLD */

#define	SPELL_GOLD_S	((gold_t)10000)
#define	SPELL_GOLD_A	((gold_t)1000)
#define	SPELL_GOLD_B	((gold_t)100)
#define	SPELL_GOLD_C	((gold_t)10)
#define	SPELL_GOLD_D	((gold_t)1)

#define	SPELL_GOLD_1	((gold_t)1)
#define	SPELL_GOLD_0	((gold_t)0)

/* ���������� */

#define	SPELL_RESI_S	((rate_t)20)
#define	SPELL_RESI_A	((rate_t)15)
#define	SPELL_RESI_B	((rate_t)10)
#define	SPELL_RESI_C	((rate_t)5)
#define	SPELL_RESI_D	((rate_t)1)

#define	SPELL_RESI_1	((rate_t)1)
#define	SPELL_RESI_0	((rate_t)0)

#endif	/* SPELL_H */
