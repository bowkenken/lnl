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
* $Id: fight.h,v 1.39 2014/03/02 00:40:47 bowkenken Exp $
***************************************************************/

#ifndef	FIGHT_H
#define	FIGHT_H

/***************************************************************
* ��Ʈ
***************************************************************/

#include	"spell-kind.h"
#include	"fx.h"
#include	"resi.h"

/***************************************************************/

/* ����ǡ����κ���� */

#define	CHR_ATACK_MAX_N	(4 + 1)

/* ����μ��� */

typedef enum {
	ATTACK_KIND_NULL,
	ATTACK_KIND_SPELL,	/* ��ˡ */
	ATTACK_KIND_SPELL_SELF,	/* ��ˡ */
	ATTACK_KIND_SPELL_FRIEND,	/* ��ˡ */
	ATTACK_KIND_PUNCH,	/* ���� */
	ATTACK_KIND_KICK,	/* ���� */
	ATTACK_KIND_KNOCK,	/* á�� */
	ATTACK_KIND_SLASH,	/* �ڤ� */
	ATTACK_KIND_STING,	/* �ɤ� */
	ATTACK_KIND_MOW,	/* ��ʧ�� */
	ATTACK_KIND_SHOOT,	/* �ͤ� */
	ATTACK_KIND_THROW,	/* �ꤲ�Ĥ��� */
	ATTACK_KIND_BITE,	/* ���� */
	ATTACK_KIND_PECK,	/* �ͤäĤ� */
	ATTACK_KIND_CLAW,	/* �����ߤ� */
	ATTACK_KIND_NIP,	/* ���� */
	ATTACK_KIND_STRANGLE,	/* ����Ĥ��� */
	ATTACK_KIND_TACKLE,	/* �֤Ĥ��� */
	ATTACK_KIND_TOUCH,	/* ����� */
	ATTACK_KIND_INDICATE,	/* �ؤ��� */
	ATTACK_KIND_KISS,	/* ���� */
	ATTACK_KIND_SEDUCE,	/* Ͷ�Ǥ��� */
	ATTACK_KIND_CARESS_BUST,	/* ���򿨤� */
	ATTACK_KIND_CARESS_HIP,	/* ������Ǥ� */
	ATTACK_KIND_CARESS_CROTCH,	/* �Դ֤���Ǥ� */
	ATTACK_KIND_CYBERN_PUNCH,	/* ���ҥѥ�� */
	ATTACK_KIND_CYBERN_KICK,	/* ���ҥ��å� */
	ATTACK_KIND_XX_SLAP,	/* ʿ���Ǥ����� */
	ATTACK_KIND_MAX_N,
} attack_kind_t;

/* �����MON��ǽ��Ȥ��ե饰 */
#define	FLG_ATTACK_MONK	TRUE

/* �����HUN��ǽ��Ȥ��ե饰 */
#define	FLG_ATTACK_THROW	TRUE

/* ����ǡ��� */

typedef struct {
	/* ���� */
	attack_kind_t	kind;

	/* Ψ */
	ratio_t	ratio;

	/* �ꤲ�ե饰����Ʈ�ե饰 */
	bool_t	flg_throw, flg_monk;

	/* ������ */
	rate_t	hit, crtcl, dam;

	/* �񹳤μ��� */
	resi_kind_t	resi_kind;

	/* ����Ⱦ�� */
	long	range_bash, range_throw;

	/* ���ե����� */
	fx_kind_t	fx_kind;
	/* ���ե����ȤΥ������ */
	long	fx_turn;

	/* ȯư�����ʸ */
	spell_kind_t	spell;
	/* ��ʸ�θ����ϰ� */
	extent_kind_t	extent;
	/* ��ʸ����̾ */
	n_msg_t	spell_fmt;
} attack_t;

#endif	/* FIGHT_H */
