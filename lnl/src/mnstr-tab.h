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
* $Id: mnstr-tab.h,v 1.20 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MNSTR_TAB_H
#define	MNSTR_TAB_H

#include	"party.h"
#include	"fight.h"
#include	"mnstr-act-prot.h"

/***************************************************************
* ��󥹥����Υǡ������ơ��֥�
***************************************************************/

/* ���㥤����ƥ��å�������ƥ��ԡ��ɤ��Τ�Ĺ�� */
#define	GIGANTIC_CENTIPEDE_LINK_N	8

/***************************************************************
* NPC �Υꥹ��
***************************************************************/

mnstr_kind_t	g_ls_npc_kind[] = {
	MNSTR_KIND_FIGHTER,
	MNSTR_KIND_MONK,
	MNSTR_KIND_HUNTER,
	MNSTR_KIND_THIEF,
	MNSTR_KIND_WIZARD,
	MNSTR_KIND_SUMMONER,
	MNSTR_KIND_PRIEST,
	MNSTR_KIND_SHAMAN,
	MNSTR_KIND_BARD,
	MNSTR_KIND_NINJA,
	MNSTR_KIND_BISHOP,

	MNSTR_KIND_FARMER,
	MNSTR_KIND_CRAFTSMAN,
	MNSTR_KIND_MERCHANT,

	MNSTR_KIND_NULL,
};

/***************************************************************
* ��󥹥������ǡ���
***************************************************************/

mnstr_tab_t	mnstr_tab[] = {
#include	"mnstr-gen-tab.h"
};

#if	0
typedef struct {
	/* ��󥹥����μ��� */
	mnstr_kind_t	kind;

	/* ȯ�����볬�κǾ�������κ�ʬ */
	long	add_lev, range_lev;

	/* ȯ�����볬�κǾ������� */
	/* ������ؿ��Ǽ�ư�׻����� */
	long	min_lev, max_lev;
} mnstr_lev_tab_t;
#endif

/***************************************************************
* ��ܥ��Υꥹ��
***************************************************************/

mnstr_lev_tab_t	mnstr_boss_lev_tab[] = {
	{ MNSTR_KIND_HIGH_RE_HOO,	/* ��� */
		+0, +1, 10, 10, },
	{ MNSTR_KIND_GREAT_MINOTAUR,	/* Ⱦ�� */
		+0, +1, 20, 20, },
	{ MNSTR_KIND_BILLION_ELEMENTAL,	/* ���� */
		+0, +1, 30, 30, },
	{ MNSTR_KIND_CYBERN,	/* ��ˡ��ʪ */
		+0, +1, 40, 40, },
	{ MNSTR_KIND_GIGANTIC_CENTIPEDE,	/* ������ʪ */
		+0, +1, 50, 50, },
	{ MNSTR_KIND_MEDUSA_ZOMBIE,	/* Ⱦ�� */
		+0, +1, 60, 60, },
	{ MNSTR_KIND_BLACK_UNICORN,	/* ��� */
		+0, +1, 70, 70, },
	{ MNSTR_KIND_VAMPIRE_LORD,	/* ����ǥå� */
		+0, +1, 80, 80, },
	{ MNSTR_KIND_RELATIVISTIC_DAEMON,	/* ���� */
		+0, +1, 90, 90, },
	{ MNSTR_KIND_ETERNAL_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +1, 100, 100, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};

/***************************************************************
* �饹�ܥ��Υꥹ��
***************************************************************/

mnstr_lev_tab_t	mnstr_last_boss_lev_tab[] = {
	{ MNSTR_KIND_EXEL,
		+0, +1, 99999, 99999, },
	{ MNSTR_KIND_EXELER,
		+0, +1, 99999, 99999, },
	{ MNSTR_KIND_XEX,
		+0, +1, 99999, 99999, },
	{ MNSTR_KIND_XX,
		+0, +1, 99999, 99999, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};

/***************************************************************
* ��󥹥����νи���ꥹ��
***************************************************************/

#if	FLG_DIVIDE_MNSTR_LEV_TAB_STAGE

mnstr_lev_tab_t	mnstr_lev_tab_stage_town[] = {
	{ MNSTR_KIND_FIGHTER,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_MONK,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_HUNTER,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_THIEF,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_WIZARD,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_SUMMONER,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_PRIEST,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_SHAMAN,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_BARD,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_NINJA,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_BISHOP,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_FARMER,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_CRAFTSMAN,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_MERCHANT,	/* �ʹ� */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};

mnstr_lev_tab_t	mnstr_lev_tab_stage_1[] = {
	{ MNSTR_KIND_GIANT_BAT,	/* ưʪ */
		+0, +0, 1, 3, },
	{ MNSTR_KIND_GIANT_SNAKE,	/* ưʪ */
		+0, +0, 1, 3, },
	{ MNSTR_KIND_GIANT_RAT,	/* ưʪ */
		+0, +0, 2, 4, },
	{ MNSTR_KIND_GIANT_CENTIPEDE,	/* ���� */
		+0, +0, 3, 5, },
	{ MNSTR_KIND_CAT,	/* ưʪ */
		+0, +0, 3, 5, },
	{ MNSTR_KIND_KOBOLD,	/* ���� */
		+0, +0, 4, 6, },
	{ MNSTR_KIND_VIPER_SNAKE,	/* ưʪ */
		+0, +0, 5, 7, },
	{ MNSTR_KIND_DOG,	/* ưʪ */
		+0, +0, 5, 7, },
	{ MNSTR_KIND_GOBLIN,	/* ���� */
		+0, +0, 6, 8, },
	{ MNSTR_KIND_GIANT_BEE,	/* ���� */
		+0, +0, 7, 9, },
	{ MNSTR_KIND_PYON_PYON,	/* ���� */
		+0, +0, 7, 9, },
	{ MNSTR_KIND_GREMLIN,	/* ���� */
		+0, +0, 8, 10, },
	{ MNSTR_KIND_HOBGOBLIN,	/* ���� */
		+0, +0, 9, 11, },
	{ MNSTR_KIND_WOLF,	/* ưʪ */
		+0, +0, 9, 11, },
	{ MNSTR_KIND_GIANT_SCORPION,	/* ���� */
		+0, +0, 10, 12, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_HIGH_RE_HOO, */	/* ��� */

mnstr_lev_tab_t	mnstr_lev_tab_stage_2[] = {
	{ MNSTR_KIND_SKELETON,	/* ����ǥå� */
		+0, +0, 11, 13, },
	{ MNSTR_KIND_ORK,	/* ���� */
		+0, +0, 12, 14, },
	{ MNSTR_KIND_VENUS_FLY_TRAP,	/* ��ʪ */
		+0, +0, 13, 15, },
	{ MNSTR_KIND_ZOMBIE,	/* ����ǥå� */
		+0, +0, 14, 16, },
	{ MNSTR_KIND_OGRE,	/* ��� */
		+0, +0, 15, 17, },
	{ MNSTR_KIND_GIANT_SPIDER,	/* ���� */
		+0, +0, 16, 18, },
	{ MNSTR_KIND_GNOLL,	/* ���� */
		+0, +0, 17, 19, },
	{ MNSTR_KIND_YETI,	/* ��� */
		+0, +0, 18, 20, },
	{ MNSTR_KIND_LEPRECHAUN,	/* ���� */
		+0, +0, 19, 21, },
	{ MNSTR_KIND_HARPY,	/* Ⱦ�� */
		+0, +0, 20, 22, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_GREAT_MINOTAUR, */	/* Ⱦ�� */

mnstr_lev_tab_t	mnstr_lev_tab_stage_3[] = {
	{ MNSTR_KIND_IMP,	/* ���� */
		+0, +0, 21, 23, },
	{ MNSTR_KIND_RUST_MONSTER,	/* ��� */
		+0, +0, 22, 24, },
	{ MNSTR_KIND_GHOUL,	/* ����ǥå� */
		+0, +0, 23, 25, },
	{ MNSTR_KIND_TROLL,	/* ��� */
		+0, +0, 24, 26, },
	{ MNSTR_KIND_SLIME,	/* ��ʪ */
		+0, +0, 25, 27, },
	{ MNSTR_KIND_HIPPOGRIFF,	/* ������ */
		+0, +0, 26, 28, },
	{ MNSTR_KIND_JACK_O_LANTERN,	/* ���� */
		+0, +0, 27, 29, },
	{ MNSTR_KIND_INVISIBLE_STALKER,	/* ��ˡ��ʪ */
		+0, +0, 28, 30, },
	{ MNSTR_KIND_GIANT_ANT,	/* ���� */
		+0, +0, 29, 31, },
	{ MNSTR_KIND_GRIFFON,	/* ������ */
		+0, +0, 30, 32, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_BILLION_ELEMENTAL, */	/* ���� */

mnstr_lev_tab_t	mnstr_lev_tab_stage_4[] = {
	{ MNSTR_KIND_GHOST,	/* ����ǥå� */
		+0, +0, 31, 33, },
	{ MNSTR_KIND_FIRE_ELEMENTAL,	/* ���� */
		+0, +0, 32, 34, },
	{ MNSTR_KIND_MORMIN_TROLL,	/* ��� */
		+0, +0, 33, 35, },
	{ MNSTR_KIND_WATER_ELEMENTAL,	/* ���� */
		+0, +0, 34, 36, },
	{ MNSTR_KIND_ACID_FLY,	/* ���� */
		+0, +0, 35, 37, },
	{ MNSTR_KIND_EARTH_ELEMENTAL,	/* ���� */
		+0, +0, 36, 38, },
	{ MNSTR_KIND_SPORE,	/* ��ʪ */
		+0, +0, 37, 39, },
	{ MNSTR_KIND_AIR_ELEMENTAL,	/* ���� */
		+0, +0, 38, 40, },
	{ MNSTR_KIND_INCUBUS,	/* ���� */
		+0, +0, 39, 41, },
	{ MNSTR_KIND_WEREWOLF,	/* Ⱦ�� */
		+0, +0, 40, 42, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_CYBERN, */	/* ��ˡ��ʪ */

mnstr_lev_tab_t	mnstr_lev_tab_stage_5[] = {
	{ MNSTR_KIND_WOOD_GOLEM,	/* ��ˡ��ʪ */
		+0, +0, 41, 43, },
	{ MNSTR_KIND_ANDRO_SCORPION,	/* Ⱦ�� */
		+0, +0, 42, 44, },
	{ MNSTR_KIND_BONE_GOLEM,	/* ��ˡ��ʪ */
		+0, +0, 43, 45, },
	{ MNSTR_KIND_GIANT_BEETLE,	/* ���� */
		+0, +0, 44, 46, },
	{ MNSTR_KIND_FLESH_GOLEM,	/* ��ˡ��ʪ */
		+0, +0, 45, 47, },
	{ MNSTR_KIND_SUCCUBUS,	/* ���� */
		+0, +0, 46, 48, },
	{ MNSTR_KIND_STONE_GOLEM,	/* ��ˡ��ʪ */
		+0, +0, 47, 49, },
	{ MNSTR_KIND_POLTERGEIST,	/* ����ǥå� */
		+0, +0, 48, 50, },
	{ MNSTR_KIND_IRON_GOLEM,	/* ��ˡ��ʪ */
		+0, +0, 49, 51, },
	{ MNSTR_KIND_LAMIA,	/* Ⱦ�� */
		+0, +0, 50, 52, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_GIGANTIC_CENTIPEDE, */	/* ������ʪ */

mnstr_lev_tab_t	mnstr_lev_tab_stage_6[] = {
	{ MNSTR_KIND_FIRE_GIANT,	/* ��� */
		+0, +0, 51, 53, },
	{ MNSTR_KIND_WILL_O_WISP,	/* ���� */
		+0, +0, 52, 54, },
	{ MNSTR_KIND_SHADE,	/* ���� */
		+0, +0, 53, 55, },
	{ MNSTR_KIND_WIGHT,	/* ����ǥå� */
		+0, +0, 54, 56, },
	{ MNSTR_KIND_CENTAUR,	/* Ⱦ�� */
		+0, +0, 55, 57, },
	{ MNSTR_KIND_FROST_GIANT,	/* ��� */
		+0, +0, 56, 58, },
	{ MNSTR_KIND_MANTICORE,	/* ������ */
		+0, +0, 57, 59, },
	{ MNSTR_KIND_GAS_CLOUD,	/* ��ˡ��ʪ */
		+0, +0, 58, 60, },
	{ MNSTR_KIND_BIRD_MAN,	/* Ⱦ�� */
		+0, +0, 59, 61, },
	{ MNSTR_KIND_WYVERN,	/* ��� */
		+0, +0, 60, 62, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_MEDUSA_ZOMBIE, */	/* Ⱦ�� */

mnstr_lev_tab_t	mnstr_lev_tab_stage_7[] = {
	{ MNSTR_KIND_SALAMANDER,	/* ���� */
		+0, +0, 61, 63, },
	{ MNSTR_KIND_CLOUD_GIANT,	/* ��� */
		+0, +0, 62, 64, },
	{ MNSTR_KIND_UNDINE,	/* ���� */
		+0, +0, 63, 65, },
	{ MNSTR_KIND_MUMMY,	/* ����ǥå� */
		+0, +0, 64, 66, },
	{ MNSTR_KIND_GNOME,	/* ���� */
		+0, +0, 65, 67, },
	{ MNSTR_KIND_UNICORN,	/* ���� */
		+0, +0, 66, 68, },
	{ MNSTR_KIND_SYLPH,	/* ���� */
		+0, +0, 67, 69, },
	{ MNSTR_KIND_GARGOYLE,	/* ��ˡ��ʪ */
		+0, +0, 68, 70, },
	{ MNSTR_KIND_MINOTAUR,	/* Ⱦ�� */
		+0, +0, 69, 71, },
	{ MNSTR_KIND_CHIMERA,	/* ������ */
		+0, +0, 70, 72, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_BLACK_UNICORN, */	/* ��� */

mnstr_lev_tab_t	mnstr_lev_tab_stage_8[] = {
	{ MNSTR_KIND_M_RED_DRAGON,	/* --�ޥ��ʡ����ɥ饴�� */
		+0, +0, 71, 73, },
	{ MNSTR_KIND_M_BLUE_DRAGON,	/* --�ޥ��ʡ����ɥ饴�� */
		+0, +0, 72, 74, },
	{ MNSTR_KIND_M_YELLOW_DRAGON,	/* --�ޥ��ʡ����ɥ饴�� */
		+0, +0, 73, 75, },
	{ MNSTR_KIND_M_GREEN_DRAGON,	/* --�ޥ��ʡ����ɥ饴�� */
		+0, +0, 74, 76, },
	{ MNSTR_KIND_M_WHITE_DRAGON,	/* --�ޥ��ʡ����ɥ饴�� */
		+0, +0, 75, 77, },
	{ MNSTR_KIND_M_BLACK_DRAGON,	/* --�ޥ��ʡ����ɥ饴�� */
		+0, +0, 76, 78, },
	{ MNSTR_KIND_M_COPPER_DRAGON,	/* --�ޥ��ʡ����ɥ饴�� */
		+0, +0, 77, 79, },
	{ MNSTR_KIND_M_SILVER_DRAGON,	/* --�ޥ��ʡ����ɥ饴�� */
		+0, +0, 78, 80, },
	{ MNSTR_KIND_M_GOLD_DRAGON,	/* --�ޥ��ʡ����ɥ饴�� */
		+0, +0, 79, 81, },
	{ MNSTR_KIND_MOUNTAIN_GIANT,	/* ��� */
		+0, +0, 80, 82, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_VAMPIRE_LORD, */	/* ����ǥå� */

mnstr_lev_tab_t	mnstr_lev_tab_stage_9[] = {
	{ MNSTR_KIND_MIMIC,	/* ��ˡ��ʪ */
		+0, +0, 81, 83, },
	{ MNSTR_KIND_BANSHEE,	/* ����ǥå� */
		+0, +0, 82, 84, },
	{ MNSTR_KIND_CYCLOPS,	/* ��� */
		+0, +0, 83, 85, },
	{ MNSTR_KIND_DURAHAN,	/* ����ǥå� */
		+0, +0, 84, 86, },
	{ MNSTR_KIND_MEDUSA,	/* Ⱦ�� */
		+0, +0, 85, 87, },
	{ MNSTR_KIND_WRAITH,	/* ����ǥå� */
		+0, +0, 86, 88, },
	{ MNSTR_KIND_HYDRA,	/* ��� */
		+0, +0, 87, 89, },
	{ MNSTR_KIND_COCKATRICE,	/* ��� */
		+0, +0, 88, 90, },
	{ MNSTR_KIND_CERBERUS,	/* ��� */
		+0, +0, 89, 91, },
	{ MNSTR_KIND_LESSER_DAEMON,	/* ���� */
		+0, +0, 90, 92, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_RELATIVISTIC_DAEMON, */	/* ���� */

mnstr_lev_tab_t	mnstr_lev_tab_stage_10[] = {
	{ MNSTR_KIND_A_RED_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +0, 91, 93, },
	{ MNSTR_KIND_VAMPIRE,	/* ����ǥå� */
		+0, +0, 91, 93, },
	{ MNSTR_KIND_A_BLUE_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +0, 92, 94, },
	{ MNSTR_KIND_GORGON,	/* ��� */
		+0, +0, 92, 94, },
	{ MNSTR_KIND_A_YELLOW_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +0, 93, 95, },
	{ MNSTR_KIND_EFREET,	/* ���� */
		+0, +0, 93, 95, },
	{ MNSTR_KIND_A_GREEN_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +0, 94, 96, },
	{ MNSTR_KIND_DJINNI,	/* ���� */
		+0, +0, 94, 96, },
	{ MNSTR_KIND_A_WHITE_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +0, 95, 97, },
	{ MNSTR_KIND_BASILISK,	/* ��� */
		+0, +0, 95, 97, },
	{ MNSTR_KIND_A_BLACK_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +0, 96, 98, },
	{ MNSTR_KIND_HELLHOUND,	/* ��� */
		+0, +0, 96, 98, },
	{ MNSTR_KIND_A_COPPER_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +0, 97, 99, },
	{ MNSTR_KIND_SPIRIT,	/* ����ǥå� */
		+0, +0, 97, 99, },
	{ MNSTR_KIND_A_SILVER_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +0, 98, 100, },
	{ MNSTR_KIND_GREATER_DAEMON,	/* ���� */
		+0, +0, 98, 100, },
	{ MNSTR_KIND_A_GOLD_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+0, +0, 99, 100, },
	{ MNSTR_KIND_PHOENIX,	/* ���� */
		+0, +0, 100, 100, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_ETERNAL_DRAGON, */	/* ���󥷥���ȡ��ɥ饴�� */

mnstr_lev_tab_t	mnstr_lev_tab[MNSTR_KIND_MAX_N + 1];

#else

mnstr_lev_tab_t	mnstr_lev_tab[] = {
	{ MNSTR_KIND_FIGHTER,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_MONK,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_HUNTER,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_THIEF,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_WIZARD,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_SUMMONER,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_PRIEST,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_SHAMAN,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_BARD,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_NINJA,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_BISHOP,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_FARMER,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_CRAFTSMAN,	/* �ʹ� */
		+0, +1, },
	{ MNSTR_KIND_MERCHANT,	/* �ʹ� */
		+0, +1, },
	/**/

	{ MNSTR_KIND_GIANT_BAT,	/* ưʪ */
		+1, +1, },
	{ MNSTR_KIND_GIANT_SNAKE,	/* ưʪ */
		+0, +1, },
	{ MNSTR_KIND_GIANT_RAT,	/* ưʪ */
		+1, +1, },
	{ MNSTR_KIND_GIANT_CENTIPEDE,	/* ���� */
		+0, +1, },
	{ MNSTR_KIND_KOBOLD,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_VIPER_SNAKE,	/* ưʪ */
		+0, +1, },
	{ MNSTR_KIND_GOBLIN,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_GIANT_BEE,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_GREMLIN,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_HOBGOBLIN,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_CAT,	/* ưʪ */
		+0, +1, },
	{ MNSTR_KIND_DOG,	/* ưʪ */
		+0, +1, },
	{ MNSTR_KIND_WOLF,	/* ưʪ */
		+0, +1, },
	{ MNSTR_KIND_PYON_PYON,	/* ���� */
		+0, +1, },
	{ MNSTR_KIND_SKELETON,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_ORK,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_VENUS_FLY_TRAP,	/* ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_GIANT_SCORPION,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_ZOMBIE,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_YETI,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_RUST_MONSTER,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_GNOLL,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_GIANT_ANT,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_OGRE,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_HARPY,	/* Ⱦ�� */
		+1, +5, },
	{ MNSTR_KIND_LEPRECHAUN,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_GHOUL,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_GIANT_SPIDER,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_SLIME,	/* ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_IMP,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_TROLL,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_INVISIBLE_STALKER,	/* ��ˡ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_MORMIN_TROLL,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_POLTERGEIST,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_ACID_FLY,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_FIRE_ELEMENTAL,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_HIPPOGRIFF,	/* ������ */
		+1, +5, },
	{ MNSTR_KIND_WATER_ELEMENTAL,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_GIANT_BEETLE,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_JACK_O_LANTERN,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_GHOST,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_WOOD_GOLEM,	/* ��ˡ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_GRIFFON,	/* ������ */
		+1, +5, },
	{ MNSTR_KIND_BONE_GOLEM,	/* ��ˡ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_INCUBUS,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_SPORE,	/* ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_ANDRO_SCORPION,	/* Ⱦ�� */
		+1, +5, },
	{ MNSTR_KIND_EARTH_ELEMENTAL,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_AIR_ELEMENTAL,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_LAMIA,	/* Ⱦ�� */
		+1, +5, },
	{ MNSTR_KIND_CENTAUR,	/* Ⱦ�� */
		+1, +5, },
	{ MNSTR_KIND_WIGHT,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_FLESH_GOLEM,	/* ��ˡ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_BIRD_MAN,	/* Ⱦ�� */
		+1, +5, },
	{ MNSTR_KIND_SUCCUBUS,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_MANTICORE,	/* ������ */
		+1, +5, },
	{ MNSTR_KIND_WEREWOLF,	/* Ⱦ�� */
		+1, +5, },
	{ MNSTR_KIND_WILL_O_WISP,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_GAS_CLOUD,	/* ��ˡ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_SHADE,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_MINOTAUR,	/* Ⱦ�� */
		+1, +5, },
	{ MNSTR_KIND_CHIMERA,	/* ������ */
		+1, +5, },
	{ MNSTR_KIND_FIRE_GIANT,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_MUMMY,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_FROST_GIANT,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_GARGOYLE,	/* ��ˡ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_STONE_GOLEM,	/* ��ˡ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_CLOUD_GIANT,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_DURAHAN,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_IRON_GOLEM,	/* ��ˡ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_MOUNTAIN_GIANT,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_SALAMANDER,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_UNDINE,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_MIMIC,	/* ��ˡ��ʪ */
		+1, +5, },
	{ MNSTR_KIND_UNICORN,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_CYCLOPS,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_BANSHEE,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_GNOME,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_SYLPH,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_WYVERN,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_MEDUSA,	/* Ⱦ�� */
		+1, +5, },
	{ MNSTR_KIND_M_RED_DRAGON,	/* �ޥ��ʡ����ɥ饴�� */
		+1, +2, },
	{ MNSTR_KIND_M_BLUE_DRAGON,	/* �ޥ��ʡ����ɥ饴�� */
		+1, +2, },
	{ MNSTR_KIND_M_YELLOW_DRAGON,	/* �ޥ��ʡ����ɥ饴�� */
		+1, +2, },
	{ MNSTR_KIND_M_GREEN_DRAGON,	/* �ޥ��ʡ����ɥ饴�� */
		+1, +2, },
	{ MNSTR_KIND_WRAITH,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_HYDRA,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_LESSER_DAEMON,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_M_WHITE_DRAGON,	/* �ޥ��ʡ����ɥ饴�� */
		+1, +2, },
	{ MNSTR_KIND_M_BLACK_DRAGON,	/* �ޥ��ʡ����ɥ饴�� */
		+1, +2, },
	{ MNSTR_KIND_COCKATRICE,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_CERBERUS,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_VAMPIRE,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_M_COPPER_DRAGON,	/* �ޥ��ʡ����ɥ饴�� */
		+1, +2, },
	{ MNSTR_KIND_M_SILVER_DRAGON,	/* �ޥ��ʡ����ɥ饴�� */
		+1, +2, },
	{ MNSTR_KIND_M_GOLD_DRAGON,	/* �ޥ��ʡ����ɥ饴�� */
		+1, +2, },
	{ MNSTR_KIND_GORGON,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_EFREET,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_DJINNI,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_BASILISK,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_PHOENIX,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_HELLHOUND,	/* ��� */
		+1, +5, },
	{ MNSTR_KIND_SPIRIT,	/* ����ǥå� */
		+1, +5, },
	{ MNSTR_KIND_GREATER_DAEMON,	/* ���� */
		+1, +5, },
	{ MNSTR_KIND_A_RED_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+1, +5, },
	{ MNSTR_KIND_A_BLUE_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+1, +5, },
	{ MNSTR_KIND_A_YELLOW_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+1, +5, },
	{ MNSTR_KIND_A_GREEN_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+1, +5, },
	{ MNSTR_KIND_A_WHITE_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+1, +5, },
	{ MNSTR_KIND_A_BLACK_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+1, +5, },
	{ MNSTR_KIND_A_COPPER_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+1, +5, },
	{ MNSTR_KIND_A_SILVER_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+1, +5, },
	{ MNSTR_KIND_A_GOLD_DRAGON,	/* ���󥷥���ȡ��ɥ饴�� */
		+1, +5, },

	/**/

	{ MNSTR_KIND_NULL,
		+0, +0, },
};

#endif

/***************************************************************
* ���Ǥ� NPC �νи�Ψ�ꥹ��
***************************************************************/

typedef struct {
	mnstr_kind_t	kind;
	ratio_t	ratio;
} towner_tab_t;

towner_tab_t	towner_tab[] = {
	{
		MNSTR_KIND_FIGHTER,
		1,
	},
	{
		MNSTR_KIND_MONK,
		1,
	},
	{
		MNSTR_KIND_HUNTER,
		1,
	},
	{
		MNSTR_KIND_THIEF,
		1,
	},
	{
		MNSTR_KIND_WIZARD,
		1,
	},
	{
		MNSTR_KIND_SUMMONER,
		1,
	},
	{
		MNSTR_KIND_PRIEST,
		1,
	},
	{
		MNSTR_KIND_SHAMAN,
		1,
	},
	{
		MNSTR_KIND_BARD,
		1,
	},
	{
		MNSTR_KIND_NINJA,
		1,
	},
	{
		MNSTR_KIND_BISHOP,
		1,
	},
	{
		MNSTR_KIND_FARMER,
		5,
	},
	{
		MNSTR_KIND_CRAFTSMAN,
		3,
	},
	{
		MNSTR_KIND_MERCHANT,
		1,
	},
	{
		MNSTR_KIND_NULL,
		0,
	},
};

#endif	/* MNSTR_TAB_H */
