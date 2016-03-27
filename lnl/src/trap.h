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
* $Id: trap.h,v 1.40 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	TRAP_H
#define	TRAP_H

/***************************************************************
* �
***************************************************************/

#include	"gmain.h"
#include	"msg.h"

/***************************************************************
* �ǥХå��ѥ����å�
***************************************************************/

/* 1 �ˤ����櫤����̤ˤĤ���(�ǥХå���) */

#if	0
# ifndef	D_TEST_TRAP
#  define	D_TEST_TRAP
# endif
#endif

#ifdef	D_TEST_TRAP
# define	TRAP_AVE_N	512
# define	TRAP_MAX_N	1024
#else
# define	TRAP_AVE_N	12
# define	TRAP_MAX_N	128
#endif

/***************************************************************
* 櫤μ���
***************************************************************/

typedef enum {
	TRAP_KIND_NULL,
	/* ̲���� */
	TRAP_KIND_SLEEP,
	/* ������ */
	TRAP_KIND_ARW,
	/* �ǥ����Ĥ�� */
	TRAP_KIND_POISON_DARTS,
	/* ���Ƥ�� */
	TRAP_KIND_BOMB,
	/* �ѡ��ƥ��ְִ�ư��� */
	TRAP_KIND_TELEPORT_PARTY,
	/* �ְִ�ư��� */
	TRAP_KIND_TELEPORT,
	/* ��� */
	TRAP_KIND_PIT,
	/* ���塼�� */
	TRAP_KIND_CHUTE,
	/* ���� */
	TRAP_KIND_SANCTUARY,
	TRAP_KIND_MAX_N
} trap_kind_t;

/***************************************************************
* 櫤Υǡ������ơ��֥�
***************************************************************/

typedef struct {
	/* ���� */
	trap_kind_t	kind;
	/* ̾���� ID */
	n_msg_t	name_n;
	/* ̾�� */
	char	*name;
	/* �и�Ψ */
	rate_t	rate;
	/* �ޥ��ʡ�����ʸ�� */
	char	mnr;
	/* �и��� */
	long	min_lev, max_lev, sgn_lev;
	/* ��å�������ɽ�����뤫? */
	bool_t	flg_draw_msg;
} trap_tab_t;

/***************************************************************
* 櫤Υǡ���
***************************************************************/

typedef struct trap_t {
	/* ��󥯡��ݥ��� */
	struct trap_t	*next, *prev;

	/* ���� */
	trap_kind_t	kind;
	/* ��ɸ */
	long	x, y;

	/* 櫤Υ�٥� */
	long	lev;
	/* ������񤷤� */
	long	difficulty;
	/* Ĵ�٤��Ƥ��뤫? */
	bool_t	flg_chked;
	/* 櫤��濴�ؤ����к�ɸ */
	bool_t	cx, cy;

	/* �ǡ������ơ��֥� */
	trap_tab_t	*tab;
} trap_t;

#endif	/* TRAP_H */
