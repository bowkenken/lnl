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
* $Id: town.h,v 1.29 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	TOWN_H
#define	TOWN_H

#include	"dun.h"
#include	"party.h"
#include	"mnstr.h"

#define	SHOP_ADD_TURN_N	(15 * TURN_PER_MINUTE)
#define	NAVI_ADD_TURN_N	((MAP_MAX_X + MAP_MAX_Y) / 2)

typedef enum {
	SHOP_N_NULL,
	SHOP_N_BAR,
	SHOP_N_INN,
	SHOP_N_WPN,
	SHOP_N_ARMOR,
	SHOP_N_MAGIC,
	SHOP_N_TEMPLE,
	SHOP_N_ALCHEMY,
	SHOP_N_MUSIC,
	SHOP_N_GROCERY,
	SHOP_N_RESTAURANT,
	SHOP_N_TEAROOM,
	SHOP_N_TOBACCO,
	SHOP_N_PET_SHOP,
	SHOP_N_MAX_N,
} shop_n_t;

/* ������������ */

#define	DISCOUNT_QUEUE_MAX_N	(32 + MBR_MAX_N)

typedef struct {
	shop_n_t	shop_n;
	door_t	*door;
	bool_t	flg_sold_out;	/* ����ڤ�ե饰 */
	long	n;
	pos_t	pos[DISCOUNT_QUEUE_MAX_N];	/* ����οͤΰ��� */
	chr_t	*chr[DISCOUNT_QUEUE_MAX_N];	/* ����ο� */
} discount_queue_t;

/**/

#define	TOWN_PTN_COL_MAX_N	64

/* �����ξȤ餹�ϰ� */

#define	STREETLAMP_R	2

/* ���Υޥåס��ǡ��� */

typedef struct {
	long	col_str_len;
	long	col_n;
	unsigned char	col_mjr[TOWN_PTN_COL_MAX_N];
	unsigned char	col_mnr[TOWN_PTN_COL_MAX_N];
	char	map_mjr[MAP_MAX_Y][MAP_MAX_X];
	char	map_mnr[MAP_MAX_Y][MAP_MAX_X];
} town_ptn_t;

typedef struct {
	long	col_code;
	char	mjr, mnr;
} town_ptn_col_tab_t;

/* �ڥåȡ�����åפξ��ʥꥹ�� */

typedef struct {
	mnstr_kind_t	kind;
	gold_t	price;
} art_ls_pet_shop_t;

#endif	/* TOWN_H */
