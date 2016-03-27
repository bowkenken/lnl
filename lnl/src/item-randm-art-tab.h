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
* $Id: item-randm-art-tab.h,v 1.9 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	ITEM_RANDM_ART_TAB_H
#define	ITEM_RANDM_ART_TAB_H

/***************************************************************
* �����ࡦ�����ƥ��ե����ȤΥǡ������ơ��֥�
***************************************************************/

/***************************************************************
* ���
***************************************************************/

char	wpn_randm_art_mnr_add_stat_tab[] = {
	/*WPN_RANDM_ART_MNR_ADD_STAT_DEAD,*/
	WPN_RANDM_ART_MNR_ADD_STAT_STONE,
	WPN_RANDM_ART_MNR_ADD_STAT_PARALYZE,
	WPN_RANDM_ART_MNR_ADD_STAT_POISON,
	WPN_RANDM_ART_MNR_ADD_STAT_CONFUSION,
	WPN_RANDM_ART_MNR_ADD_STAT_BLIND,
	WPN_RANDM_ART_MNR_ADD_STAT_SLEEP,
	WPN_RANDM_ART_MNR_ADD_STAT_SILENCE,
	/*WPN_RANDM_ART_MNR_ADD_STAT_CAUGHT,*/
	WPN_RANDM_ART_MNR_ADD_STAT_FEAR,
	WPN_RANDM_ART_MNR_ADD_STAT_HALLUCINATION,
	WPN_RANDM_ART_MNR_ADD_STAT_CHARM,
	WPN_RANDM_ART_MNR_ADD_STAT_FLY,
	/*WPN_RANDM_ART_MNR_ADD_STAT_HUNGRY,*/
	/*WPN_RANDM_ART_MNR_ADD_STAT_STARVATION,*/
	/*WPN_RANDM_ART_MNR_ADD_STAT_FAINT,*/
	/*WPN_RANDM_ART_MNR_ADD_STAT_DRUNK,*/
	/*WPN_RANDM_ART_MNR_ADD_STAT_VANISH,*/
	/*WPN_RANDM_ART_MNR_ADD_STAT_IRON_BODY,*/
	WPN_RANDM_ART_MNR_ADD_STAT_PASSWALL,
	WPN_RANDM_ART_MNR_ADD_STAT_SENSE_INVISIBLE,
};

char	wpn_randm_art_mnr_slayer_tab[] = {
	FACE_MJR_MNSTR_GOD,
	FACE_MJR_MNSTR_DRAGON,
	FACE_MJR_MNSTR_ILLUSORY,
	FACE_MJR_MNSTR_FAIRY,
	FACE_MJR_MNSTR_ELEMENTAL,
	FACE_MJR_MNSTR_PLANT,
	FACE_MJR_MNSTR_ANIMAL,
	FACE_MJR_MNSTR_INSECT,
	FACE_MJR_MNSTR_HUMAN,
	FACE_MJR_MNSTR_HYBRID,
	FACE_MJR_MNSTR_GIANT,
	FACE_MJR_MNSTR_HUGE,
	FACE_MJR_MNSTR_AQUATIC,
	FACE_MJR_MNSTR_MAGICAL,
	FACE_MJR_MNSTR_COMPOUND,
	FACE_MJR_MNSTR_UNDEAD,
	FACE_MJR_MNSTR_EVIL,
	FACE_MJR_MNSTR_EVIL_BEAST,
	FACE_MJR_MNSTR_DEVIL,
};

char	wpn_randm_art_mnr_drain_tab[] = {
	WPN_RANDM_ART_MNR_DRAIN_HP,
	WPN_RANDM_ART_MNR_DRAIN_MP,
	WPN_RANDM_ART_MNR_DRAIN_EXP,
};

/***************************************************************
* �ɶ�
***************************************************************/

char	armor_randm_art_mnr_resi_stat_tab[] = {
	ARMOR_RANDM_ART_MNR_RESI_STAT_DEAD,
	ARMOR_RANDM_ART_MNR_RESI_STAT_STONE,
	ARMOR_RANDM_ART_MNR_RESI_STAT_PARALYZE,
	ARMOR_RANDM_ART_MNR_RESI_STAT_POISON,
	ARMOR_RANDM_ART_MNR_RESI_STAT_CONFUSION,
	ARMOR_RANDM_ART_MNR_RESI_STAT_BLIND,
	ARMOR_RANDM_ART_MNR_RESI_STAT_SLEEP,
	ARMOR_RANDM_ART_MNR_RESI_STAT_SILENCE,
	/*ARMOR_RANDM_ART_MNR_RESI_STAT_CAUGHT,*/
	ARMOR_RANDM_ART_MNR_RESI_STAT_FEAR,
	ARMOR_RANDM_ART_MNR_RESI_STAT_HALLUCINATION,
	ARMOR_RANDM_ART_MNR_RESI_STAT_CHARM,
	ARMOR_RANDM_ART_MNR_RESI_STAT_FLY,
	/*ARMOR_RANDM_ART_MNR_RESI_STAT_HUNGRY,*/
	/*ARMOR_RANDM_ART_MNR_RESI_STAT_STARVATION,*/
	/*ARMOR_RANDM_ART_MNR_RESI_STAT_FAINT,*/
	/*ARMOR_RANDM_ART_MNR_RESI_STAT_DRUNK,*/
	/*ARMOR_RANDM_ART_MNR_RESI_STAT_VANISH,*/
	/*ARMOR_RANDM_ART_MNR_RESI_STAT_IRON_BODY,*/
	ARMOR_RANDM_ART_MNR_RESI_STAT_PASSWALL,
	ARMOR_RANDM_ART_MNR_RESI_STAT_SENSE_INVISIBLE,
};

char	armor_randm_art_mnr_protect_tab[] = {
	FACE_MJR_MNSTR_GOD,
	FACE_MJR_MNSTR_DRAGON,
	FACE_MJR_MNSTR_ILLUSORY,
	FACE_MJR_MNSTR_FAIRY,
	FACE_MJR_MNSTR_ELEMENTAL,
	FACE_MJR_MNSTR_PLANT,
	FACE_MJR_MNSTR_ANIMAL,
	FACE_MJR_MNSTR_INSECT,
	FACE_MJR_MNSTR_HUMAN,
	FACE_MJR_MNSTR_HYBRID,
	FACE_MJR_MNSTR_GIANT,
	FACE_MJR_MNSTR_HUGE,
	FACE_MJR_MNSTR_AQUATIC,
	FACE_MJR_MNSTR_MAGICAL,
	FACE_MJR_MNSTR_COMPOUND,
	FACE_MJR_MNSTR_UNDEAD,
	FACE_MJR_MNSTR_EVIL,
	FACE_MJR_MNSTR_EVIL_BEAST,
	FACE_MJR_MNSTR_DEVIL,
};

char	armor_randm_art_mnr_healing_tab[] = {
	ARMOR_RANDM_ART_MNR_HEALING_HP,
	ARMOR_RANDM_ART_MNR_HEALING_MP,
	ARMOR_RANDM_ART_MNR_HEALING_EXP,
};

#endif	/* ITEM_RANDM_ART_TAB_H */
