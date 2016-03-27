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
* $Id: amenu.h,v 1.26 2014/03/01 23:48:01 bowkenken Exp $
***************************************************************/

#ifndef	AMENU_H
#define	AMENU_H

/***************************************************************
* ��ư�ޡ���
***************************************************************/

/* ��ư�ޡ����κ���� */
#define	AUTO_MARK_N_PER_PAGE	10
#define	AUTO_MARK_PAGE_N	6
#define	AUTO_MARK_MAX_N		(AUTO_MARK_N_PER_PAGE * AUTO_MARK_PAGE_N)

/* �����ȥ�κ���ʸ���� */
#define	MSG_TTL_AUTO_MARK_MAX_LEN	64
#define	MSG_TTL_AUTO_MARK_MAX_BYTE	\
	(MSG_TTL_AUTO_MARK_MAX_LEN * CHAR_MAX_LEN_UTF_8)
#define	MSG_TTL_AUTO_MARK_INFO_MAX_LEN	30
#define	MSG_TTL_AUTO_MARK_INFO_MAX_BYTE	\
	(MSG_TTL_AUTO_MARK_INFO_MAX_LEN * CHAR_MAX_LEN_UTF_8)
#define	MSG_TTL_AUTO_MARK_HINT_MAX_LEN	30
#define	MSG_TTL_AUTO_MARK_HINT_MAX_BYTE	\
	(MSG_TTL_AUTO_MARK_HINT_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* �����ƥ�μ���κ���� */
#define	AUTO_MARK_APPOINT_ITEM_MAX_N	64

/* ���С������֤��饻�����Ѥμ�ư�ޡ���������å��ֹ���Ѵ�������β��� */
#define	AUTO_MARK_POSITION_MUL	1000

/***************************************************************
* �ե饰
* ���֤��Ѥ�����ϥ����֡��ǡ����⽤������
***************************************************************/

/* �ޡ���������˺Ƥӥޡ������ʤ��� */
#define	FLG_AUTO_MARK_EDIT_CONT	(1 << 0)

/* ���Ǥ˥ޡ������Ƥ��Ƥ⶯��Ū�˥ޡ������ʤ��� */
#define	FLG_AUTO_MARK_EDIT_PRIORITY	(1 << 1)

/***************************************************************
* �о�
***************************************************************/

typedef enum {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_TRGT_ITEM,
	AUTO_MARK_TRGT_DOOR,
	AUTO_MARK_TRGT_TRAP,
	AUTO_MARK_TRGT_MBR,
	AUTO_MARK_TRGT_UNCHANGE,
	AUTO_MARK_TRGT_CLEAR,
} auto_mark_trgt_t;

/***************************************************************
* �ֹ礤
***************************************************************/

typedef enum {
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_DIST_MEDIUM,
	AUTO_MARK_DIST_FAR,
} auto_mark_dist_t;

/***************************************************************
* ���������
***************************************************************/

typedef enum {
	AUTO_MARK_ACT_FIGHT,
	AUTO_MARK_ACT_THROW,
	AUTO_MARK_ACT_STEAL,
	AUTO_MARK_ACT_TAIL,
	AUTO_MARK_ACT_PICK_UP,
	AUTO_MARK_ACT_BREAK,
	AUTO_MARK_ACT_OPEN,
	AUTO_MARK_ACT_CLOSE,
	AUTO_MARK_ACT_JAM,
	AUTO_MARK_ACT_DISARM,
	AUTO_MARK_ACT_PEEP,
	AUTO_MARK_ACT_CHK,
} auto_mark_act_t;

/***************************************************************
* ���
***************************************************************/

typedef enum {
	/* ��äȤ�ᤤʪ */
	AUTO_MARK_COND_NEAREST,

	/* �Ф餱�� */
	AUTO_MARK_COND_DISPERSE,

	/* ����Ƥ�����С� */
	AUTO_MARK_COND_STAGGER,

	/* Ʊ��ʪ����äƤ��� */
	AUTO_MARK_COND_OWN,

	/* ���̺� */
	AUTO_MARK_COND_IDENTIFIED,

	/* ̤���� */
	AUTO_MARK_COND_UN_IDENTIFIED,

	/* 1 �� HP �ξ��ʤ� */
	AUTO_MARK_COND_HP_MIN,

	/* 1 �� HP ��¿�� */
	AUTO_MARK_COND_HP_MAX,

	/* 1 �� MP �ξ��ʤ� */
	AUTO_MARK_COND_MP_MIN,

	/* 1 �� MP ��¿�� */
	AUTO_MARK_COND_MP_MAX,
} auto_mark_cond_t;

/***************************************************************
* �ǥե���Ȥμ�ư�ޡ����μ���
***************************************************************/

typedef enum {
	DFLT_AUTO_MARK_NULL,

	/* ��Ʈ(�ɲ�) */
	DFLT_AUTO_MARK_FIGHT,
	/* ��Ʈ(����) */
	DFLT_AUTO_MARK_FIGHT_PRIO,

	/* �ܶ���Ʈ(�ɲ�) */
	DFLT_AUTO_MARK_FIGHT_NO_THROW,
	/* �ܶ���Ʈ(����) */
	DFLT_AUTO_MARK_FIGHT_NO_THROW_PRIO,

	/* ������(�ɲ�) */
	DFLT_AUTO_MARK_FIGHT_ALL,
	/* ������(����) */
	DFLT_AUTO_MARK_FIGHT_ALL_PRIO,

	/* ���ƤΥ����ƥ� */
	DFLT_AUTO_MARK_ITEM_ALL,
	/* ���äƤ��륢���ƥ� */
	DFLT_AUTO_MARK_ITEM_OWN,

	/* ��� */
	DFLT_AUTO_MARK_RETREAT,
	/* ��� */
	DFLT_AUTO_MARK_CLEAR,

	DFLT_AUTO_MARK_MAX_N,
	DFLT_AUTO_MARK_MIN_N = DFLT_AUTO_MARK_FIGHT,
} dflt_auto_mark_t;

/***************************************************************
* ��ư�ޡ���
***************************************************************/

typedef struct {
	auto_mark_trgt_t	trgt;
	auto_mark_dist_t	dist;
	auto_mark_act_t	act;
	auto_mark_cond_t	cond;
	char	macro[MACRO_MAX_LEN + 1];
	unsigned long	flg;

	dflt_auto_mark_t	dflt;
} auto_mark_t;

#endif	/* AMENU_H */
