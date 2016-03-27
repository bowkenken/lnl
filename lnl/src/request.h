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
* $Id: request.h,v 1.40 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	REQUEST_H
#define	REQUEST_H

/***************************************************************
* ���ΰ���
***************************************************************/

#include	"item.h"
#include	"chr.h"
#include	"menu.h"

/***************************************************************
* ����ο�
***************************************************************/

/* ����� */
#define	REQUEST_MAX_N	64
/* ʿ�ѿ� */
#define	REQUEST_AVE_N	32

/* �����å������κ���Ĺ */
#define	REQUEST_MSG_MAX_LEN	4096
#define	REQUEST_MSG_MAX_BYTE	\
	(REQUEST_MSG_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/***************************************************************
* ����μ���
***************************************************************/

typedef enum {
	REQUEST_KIND_NULL,

	/* �����ƥ�õ�� */
	REQUEST_KIND_RARE_GOODS,
	/* ����ץ�� */
	REQUEST_KIND_TAME_MNSTR,
	/* �߽� */
	REQUEST_KIND_RESCUE,
	/* �Ѹ����� */
	REQUEST_KIND_TOUR_GUIDE,
	/* ��󥹥����༣ */
	REQUEST_KIND_EXTERMINATE,
	/* ��Ƥ�� */
	REQUEST_KIND_REVENGE,
	/* �޶�� */
	REQUEST_KIND_WANTED_CRIMINAL,

	REQUEST_KIND_MAX_N,
} request_kind_t;

/***************************************************************
* ����Υǡ�����
***************************************************************/

typedef struct request_t {
	/* ���� */
	request_kind_t	kind;
	/* �Ǿ���, ���糬, ��Ū�γ� */
	long	dun_min_lev, dun_max_lev, dun_true_lev;
	/* �޶�� */
	gold_t	prize;
	/* �󽷷и��� */
	long	exp;
	/* �������� */
	long	limit;

	/* ���������ե饰 */
	bool_t	flg_contract;
	/* ���С��ΰ��������ե饰 */
	bool_t	flg_contract_mbr;
	/* ����������������̾�� */
	n_msg_idx_t	idx_contract_name;
	/* �������������������� */
	sex_t	contract_sex;
	/* ã���ե饰 */
	bool_t	flg_finish;

	/* õ�����륢���ƥ�μ��� */
	rare_goods_kind_t	rare_goods_kind;

	/* ��ɸ��Ũ�� NPC ��? */
	bool_t	flg_mnstr_is_npc;
	/* ��ɸ�Υ�󥹥����μ��� */
	mnstr_kind_t	mnstr_kind;
	/* ��ɸ�Υ�󥹥����ο� */
	long	mnstr_n;
	/* �ݤ�����󥹥����ο� */
	long	mnstr_exterminate_n;

	/* �ꥹ�Ⱦ�θ��Ф� */
	char	heading[MENU_MSG_MAX_BYTE + 1];
	/* �����å������Υ���ǥå��� */
	n_msg_idx_t	idx_fmt;
	/* �����å����� */
	char	msg[REQUEST_MSG_MAX_BYTE + 1];

	/* ������̾���Υ���ǥå��� */
	n_msg_idx_t	idx_client_name;
	/* ��󥹥�����̾���Υ���ǥå��� */
	n_msg_idx_t	idx_mnstr_name;
	/* �߽����� NPC ��̾���Υ���ǥå��� */
	n_msg_idx_t	idx_rescue_trgt_name;
	/* �����β�²��̾���Υ���ǥå��� */
	n_msg_idx_t	idx_client_family_name;
	/* ��������֤�̾���Υ���ǥå��� */
	n_msg_idx_t	idx_client_mate_name;
	/* ���������� */
	sex_t	client_sex;
	/* ��󥹥��������� */
	sex_t	mnstr_sex;
	/* �߽����� NPC ������ */
	sex_t	rescue_trgt_sex;
	/* �����β�²������ */
	sex_t	client_family_sex;
	/* ��������֤����� */
	sex_t	client_mate_sex;
	/* �߽����� NPC �μ��� */
	mnstr_kind_t	rescue_trgt_kind;

	/* ����λ��֤Υ���ǥå��� */
	n_msg_idx_t	idx_when_1, idx_when_2;
	/* ��������Υ���ǥå��� */
	n_msg_idx_t	idx_weapon;
} request_t;

#endif	/* REQUEST_H */
