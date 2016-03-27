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
* $Id: item-randm-art.h,v 1.12 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	ITEM_RANDM_ART_H
#define	ITEM_RANDM_ART_H

/***************************************************************
* �����ࡦ�����ƥ��ե�����
***************************************************************/

/***************************************************************
* ���
***************************************************************/

#define	WPN_RANDM_ART_LS_MAX_N	32

#define	WPN_RANDM_ART_DUN_LEV_DIV	30

#define	WPN_RANDM_ART_NAME_MAX_N	4

#define	WPN_RANDM_ART_MJR_NULL	' '
#define	WPN_RANDM_ART_MJR_BANE	'B'
#define	WPN_RANDM_ART_MJR_KILLER	'K'
#define	WPN_RANDM_ART_MJR_SLAYER	'S'
#define	WPN_RANDM_ART_MJR_ADD_STAT	'F'
#define	WPN_RANDM_ART_MJR_DRAIN	'D'

#define	WPN_RANDM_ART_MNR_NULL	' '

/*#define	WPN_RANDM_ART_MNR_ADD_STAT_DEAD	'd'*/
#define	WPN_RANDM_ART_MNR_ADD_STAT_STONE	's'
#define	WPN_RANDM_ART_MNR_ADD_STAT_PARALYZE	'y'
#define	WPN_RANDM_ART_MNR_ADD_STAT_POISON	'p'
#define	WPN_RANDM_ART_MNR_ADD_STAT_CONFUSION	'c'
#define	WPN_RANDM_ART_MNR_ADD_STAT_BLIND	'b'
#define	WPN_RANDM_ART_MNR_ADD_STAT_SLEEP	'l'
#define	WPN_RANDM_ART_MNR_ADD_STAT_SILENCE	'i'
/*#define	WPN_RANDM_ART_MNR_ADD_STAT_CAUGHT	'u'*/
#define	WPN_RANDM_ART_MNR_ADD_STAT_FEAR	'e'
#define	WPN_RANDM_ART_MNR_ADD_STAT_HALLUCINATION	'h'
#define	WPN_RANDM_ART_MNR_ADD_STAT_CHARM	'r'
#define	WPN_RANDM_ART_MNR_ADD_STAT_FLY	'f'
/*#define	WPN_RANDM_ART_MNR_ADD_STAT_HUNGRY	'g'*/
/*#define	WPN_RANDM_ART_MNR_ADD_STAT_STARVATION	't'*/
/*#define	WPN_RANDM_ART_MNR_ADD_STAT_FAINT	'a'*/
/*#define	WPN_RANDM_ART_MNR_ADD_STAT_DRUNK	'k'*/
/*#define	WPN_RANDM_ART_MNR_ADD_STAT_VANISH	'v'*/
/*#define	WPN_RANDM_ART_MNR_ADD_STAT_IRON_BODY	'o'*/
#define	WPN_RANDM_ART_MNR_ADD_STAT_PASSWALL	'w'
#define	WPN_RANDM_ART_MNR_ADD_STAT_SENSE_INVISIBLE	'n'

#define	WPN_RANDM_ART_MNR_DRAIN_HP	'h'
#define	WPN_RANDM_ART_MNR_DRAIN_MP	'm'
#define	WPN_RANDM_ART_MNR_DRAIN_EXP	'x'

typedef enum {
	WPN_RANDM_ART_KIND_NULL,

	WPN_RANDM_ART_KIND_BANE,
	WPN_RANDM_ART_KIND_KILLER,
	WPN_RANDM_ART_KIND_SLAYER,
	WPN_RANDM_ART_KIND_ADD_STAT,
	WPN_RANDM_ART_KIND_DRAIN,

	WPN_RANDM_ART_KIND_MAX_N,
} wpn_randm_art_kind_t;

typedef struct {
	wpn_randm_art_kind_t	kind;
	char	mjr, mnr;
} wpn_randm_art_t;

/***************************************************************
* �ɶ�
***************************************************************/

#define	ARMOR_RANDM_ART_LS_MAX_N	5

#define	ARMOR_RANDM_ART_DUN_LEV_DIV	30

#define	ARMOR_RANDM_ART_NAME_MAX_N	4

#define	ARMOR_RANDM_ART_MJR_NULL	' '
#define	ARMOR_RANDM_ART_MJR_GUARD	'G'
#define	ARMOR_RANDM_ART_MJR_BLOCK	'B'
#define	ARMOR_RANDM_ART_MJR_PROTECT	'P'
#define	ARMOR_RANDM_ART_MJR_RESI_STAT	'R'
#define	ARMOR_RANDM_ART_MJR_HEALING	'H'

#define	ARMOR_RANDM_ART_MNR_NULL	' '

#define	ARMOR_RANDM_ART_MNR_RESI_STAT_DEAD	'd'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_STONE	's'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_PARALYZE	'y'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_POISON	'p'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_CONFUSION	'c'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_BLIND	'b'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_SLEEP	'l'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_SILENCE	'i'
/*#define	ARMOR_RANDM_ART_MNR_RESI_STAT_CAUGHT	'u'*/
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_FEAR	'e'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_HALLUCINATION	'h'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_CHARM	'r'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_FLY	'f'
/*#define	ARMOR_RANDM_ART_MNR_RESI_STAT_HUNGRY	'g'*/
/*#define	ARMOR_RANDM_ART_MNR_RESI_STAT_STARVATION	't'*/
/*#define	ARMOR_RANDM_ART_MNR_RESI_STAT_FAINT	'a'*/
/*#define	ARMOR_RANDM_ART_MNR_RESI_STAT_DRUNK	'k'*/
/*#define	ARMOR_RANDM_ART_MNR_RESI_STAT_VANISH	'v'*/
/*#define	ARMOR_RANDM_ART_MNR_RESI_STAT_IRON_BODY	'o'*/
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_PASSWALL	'w'
#define	ARMOR_RANDM_ART_MNR_RESI_STAT_SENSE_INVISIBLE	'n'

#define	ARMOR_RANDM_ART_MNR_HEALING_HP	'h'
#define	ARMOR_RANDM_ART_MNR_HEALING_MP	'm'
#define	ARMOR_RANDM_ART_MNR_HEALING_EXP	'x'

typedef enum {
	ARMOR_RANDM_ART_KIND_NULL,

	ARMOR_RANDM_ART_KIND_GUARD,
	ARMOR_RANDM_ART_KIND_BLOCK,
	ARMOR_RANDM_ART_KIND_PROTECT,
	ARMOR_RANDM_ART_KIND_RESI_STAT,
	ARMOR_RANDM_ART_KIND_HEALING,

	ARMOR_RANDM_ART_KIND_MAX_N,
} armor_randm_art_kind_t;

typedef struct {
	armor_randm_art_kind_t	kind;
	char	mjr, mnr;
} armor_randm_art_t;

#endif	/* ITEM_RANDM_ART_H */
