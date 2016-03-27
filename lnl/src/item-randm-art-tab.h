/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* 本プログラムはフリー・ソフトウェアです。
* あなたは、 Free Software Foundation が公表した
*  GNU 一般公有使用許諾の「バージョン２」
* 或はそれ以降の各バージョンの中からいずれかを選択し、
* そのバージョンが定める条項に従って本プログラムを
* 再頒布または変更することができます。
* 
* 本プログラムは有用とは思いますが、頒布にあたっては、
* 市場性及び特定目的適合性についての暗黙の保証を含めて,
* いかなる保証も行ないません。
* 詳細については GNU 一般公有使用許諾書をお読みください。
* 
* あなたは、本プログラムと一緒に GNU 一般公有使用許諾書
* の写しを受け取っているはずです。そうでない場合は、
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* へ手紙を書いてください。
* 
* $Id: item-randm-art-tab.h,v 1.9 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	ITEM_RANDM_ART_TAB_H
#define	ITEM_RANDM_ART_TAB_H

/***************************************************************
* ランダム・アーティファクトのデータ・テーブル
***************************************************************/

/***************************************************************
* 武器
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
* 防具
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
