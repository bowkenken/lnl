/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ������ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�������
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�������ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ������Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: spell-kind.h,v 1.20 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	SPELL_KIND_H
#define	SPELL_KIND_H

/* ��ʸ�μ��� */

typedef enum {
	SPELL_KIND_NULL,
/* MAG */
	SPELL_KIND_MAG_MIN_N,
	SPELL_KIND_LIGHT,
	SPELL_KIND_DARKNESS,
	SPELL_KIND_STORE_LIGHT,
	SPELL_KIND_SHORT_TELEPORT_PARTY,
	SPELL_KIND_TELEPORT_PARTY,
	SPELL_KIND_TELEPORT,
	SPELL_KIND_RECALL,
	SPELL_KIND_KNOCK,
	SPELL_KIND_LOCK,
	SPELL_KIND_DISARM_TRAP,
	SPELL_KIND_ANIMATE_OBJECTS,
	SPELL_KIND_SHELTER,
	SPELL_KIND_CREATE_FOOD,
	SPELL_KIND_IDENTIFY_ITEM,
	SPELL_KIND_IDENTIFY_ALL_ITEM,
	SPELL_KIND_SEARCHING,
	SPELL_KIND_ANALYZE_DWEOMER,
	SPELL_KIND_DETECT_ITEM,
	SPELL_KIND_DETECT_DOORS,
	SPELL_KIND_DETECT_TRAPS,
	SPELL_KIND_DETECT_MAGIC,
	SPELL_KIND_DETECT_MONSTER,
	SPELL_KIND_SENSE_INVISIBLE,
	SPELL_KIND_FLY,
	SPELL_KIND_FEATHER_FALL,
	SPELL_KIND_VANISH,
	SPELL_KIND_DARKVISION,
	SPELL_KIND_PASSWALL,
	SPELL_KIND_DISPEL_MAGIC,
	SPELL_KIND_MIRROR_IMAGE,
	SPELL_KIND_POLYMORPH_OTHER,
	SPELL_KIND_POLYMORPH_SELF,
	SPELL_KIND_STEALTH,
	SPELL_KIND_MAG_MAX_N,
/* SOR */
	SPELL_KIND_SOR_MIN_N,
	SPELL_KIND_MAGIC_MISSILE,
	SPELL_KIND_FIRE_BALL,
	SPELL_KIND_ICE_BLIZZARD,
	SPELL_KIND_MIND_STORM,
	SPELL_KIND_ACID_RAIN,
	SPELL_KIND_LIGHTNING_BOLT,
	SPELL_KIND_POISON_CLOUD,
	SPELL_KIND_DEATH_SPELL,
	SPELL_KIND_WORD_OF_DESTRUCTION,
	SPELL_KIND_MAGE_ARMOR,
	SPELL_KIND_MAGIC_SHIELD,
	SPELL_KIND_STONESKIN,
	SPELL_KIND_IRON_BODY,
	SPELL_KIND_SPELL_RESISTANCE,
	SPELL_KIND_COUNTER_MAGIC,
	SPELL_KIND_STONE,
	SPELL_KIND_PARALYZE,
	SPELL_KIND_POISON,
	SPELL_KIND_CONFUSION,
	SPELL_KIND_BLINDNESS,
	SPELL_KIND_SLEEP,
	SPELL_KIND_SILENCE,
	SPELL_KIND_FEAR,
	SPELL_KIND_HALLUCINATION,
	SPELL_KIND_CHARM,
	SPELL_KIND_SOR_MAX_N,
/* ENC */
	SPELL_KIND_ENC_MIN_N,
	SPELL_KIND_SHARPNESS,
	SPELL_KIND_STRENGTH,
	SPELL_KIND_QUICKNESS,
	SPELL_KIND_BRAINY,
	SPELL_KIND_WISE,
	SPELL_KIND_ATTRACTIVE,
	SPELL_KIND_POWER_UP_HP,
	SPELL_KIND_HASTE,
	SPELL_KIND_DULLNESS,
	SPELL_KIND_WEAKNESS,
	SPELL_KIND_SLOWNESS,
	SPELL_KIND_BRAINLESS,
	SPELL_KIND_FOOLISH,
	SPELL_KIND_UNATTRACTIVE,
	SPELL_KIND_ENERGY_DRAIN,
	SPELL_KIND_SLOW,
	SPELL_KIND_HUNGER,
	SPELL_KIND_CANCELLATION,
	SPELL_KIND_ENC_MAX_N,
/* SUM */
	SPELL_KIND_SUM_MIN_N,
	SPELL_KIND_SKELETON_WARRIOR,
	SPELL_KIND_SUMMON_UNICORN,
	SPELL_KIND_SUMMON_EFREET,
	SPELL_KIND_SUMMON_DJINNI,
	SPELL_KIND_SUMMON_PHOENIX,
	SPELL_KIND_SUMMON_BONE,
	SPELL_KIND_SUMMON_RANDOM,
	SPELL_KIND_CREATE_UNDEAD,
	SPELL_KIND_DISMISSAL,
	SPELL_KIND_SUM_MAX_N,
/* PRI */
	SPELL_KIND_PRI_MIN_N,
	SPELL_KIND_CURE_HP_LIGHT,
	SPELL_KIND_CURE_HP_MODERATE,
	SPELL_KIND_CURE_HP_SERIOUS,
	SPELL_KIND_CURE_HP_MAX,
	SPELL_KIND_REGENERATION,
	SPELL_KIND_CURE_MP,
	SPELL_KIND_TRANSFER_MP,
	SPELL_KIND_RESTORE_EXPERIENCE,
	SPELL_KIND_RESURRECTION,
	SPELL_KIND_HEAL,
	SPELL_KIND_CURE_STATUS,
	SPELL_KIND_CURE_STONE,
	SPELL_KIND_CURE_PARALYZE,
	SPELL_KIND_CURE_POISON,
	SPELL_KIND_CURE_CONFUSION,
	SPELL_KIND_CURE_BLINDNESS,
	SPELL_KIND_CURE_SLEEP,
	SPELL_KIND_CURE_SILENCE,
	SPELL_KIND_CURE_FEAR,
	SPELL_KIND_CURE_HALLUCINATION,
	SPELL_KIND_CURE_CHARM,
	SPELL_KIND_PROTECTION,
	SPELL_KIND_RESIST_PHYSICAL,
	SPELL_KIND_RESIST_HEAT,
	SPELL_KIND_RESIST_COLD,
	SPELL_KIND_RESIST_ACID,
	SPELL_KIND_RESIST_MIND,
	SPELL_KIND_RESIST_ELECTRICITY,
	SPELL_KIND_RESIST_POISON,
	SPELL_KIND_BLESS,
	SPELL_KIND_REMOVE_CURSE,
	SPELL_KIND_DISPEL_UNDEAD,
	SPELL_KIND_ESCAPE,
	SPELL_KIND_SANCTUARY,
	SPELL_KIND_WISH,
	SPELL_KIND_PRI_MAX_N,
/* SHA */
	SPELL_KIND_SHA_MIN_N,
	SPELL_KIND_WEAK_FIRE_ELEMENTAL,
	SPELL_KIND_WEAK_WATER_ELEMENTAL,
	SPELL_KIND_WEAK_AIR_ELEMENTAL,
	SPELL_KIND_WEAK_EARTH_ELEMENTAL,
	SPELL_KIND_WEAK_LIGHT_ELEMENTAL,
	SPELL_KIND_WEAK_DARK_ELEMENTAL,
	SPELL_KIND_SUMMON_FIRE_ELEMENTAL,
	SPELL_KIND_SUMMON_SALAMANDER,
	SPELL_KIND_SUMMON_WATER_ELEMENTAL,
	SPELL_KIND_SUMMON_UNDINE,
	SPELL_KIND_SUMMON_AIR_ELEMENTAL,
	SPELL_KIND_SUMMON_SYLPH,
	SPELL_KIND_SUMMON_EARTH_ELEMENTAL,
	SPELL_KIND_SUMMON_GNOME,
	SPELL_KIND_SUMMON_WILL_O_WISP,
	SPELL_KIND_SUMMON_SHADE,
	SPELL_KIND_DISMISSAL_ELEMENTAL,
	SPELL_KIND_SHA_MAX_N,
/* BAR */
	SPELL_KIND_BAR_MIN_N,
	SPELL_KIND_SONG_CURE_HP,
	SPELL_KIND_SONG_CURE_MP,
	SPELL_KIND_SONG_SHARPNESS,
	SPELL_KIND_SONG_STRENGTH,
	SPELL_KIND_SONG_QUICKNESS,
	SPELL_KIND_SONG_BRAINY,
	SPELL_KIND_SONG_WISE,
	SPELL_KIND_SONG_ATTRACTIVE,
	SPELL_KIND_SONG_DULLNESS,
	SPELL_KIND_SONG_WEAKNESS,
	SPELL_KIND_SONG_SLOWNESS,
	SPELL_KIND_SONG_BRAINLESS,
	SPELL_KIND_SONG_FOOLISH,
	SPELL_KIND_SONG_UNATTRACTIVE,
	SPELL_KIND_SONG_RESI_STAT_STONE,
	SPELL_KIND_SONG_RESI_STAT_PARALYZE,
	SPELL_KIND_SONG_RESI_STAT_POISON,
	SPELL_KIND_SONG_RESI_STAT_CONFUSION,
	SPELL_KIND_SONG_RESI_STAT_BLIND,
	SPELL_KIND_SONG_RESI_STAT_SLEEP,
	SPELL_KIND_SONG_RESI_STAT_SILENCE,
	SPELL_KIND_SONG_RESI_STAT_FEAR,
	SPELL_KIND_SONG_RESI_STAT_HALLUCINATION,
	SPELL_KIND_SONG_RESI_STAT_CHARM,
	SPELL_KIND_SONG_RESI_STAT_DRUNK,
	SPELL_KIND_BAR_MAX_N,
/* NIN */
	SPELL_KIND_NIN_MIN_N,
	SPELL_KIND_TYPHOON,	/* ����-���� */
	SPELL_KIND_CONFLAGRATION,	/* ����-�к� */
	SPELL_KIND_EARTHQUAKE,	/* ����-�Ͽ� */
	SPELL_KIND_THUNDERCLOUD,	/* ����-��� */
	SPELL_KIND_INUNDATION,	/* ����-���� */

	SPELL_KIND_SUBSTITUTE,	/* ����-���� */
	SPELL_KIND_BURNING_HANDS,	/* ����-��� */
	SPELL_KIND_RALLY,	/* ����-���ڽ��� */
	SPELL_KIND_IRON_MAN,	/* ����-Ŵ�� */
	SPELL_KIND_MIND_READING,	/* ����-�����߿� */
	SPELL_KIND_NIN_MAX_N,
/* ANC */
	SPELL_KIND_ANC_MIN_N,
	SPELL_KIND_NOTHING,
	SPELL_KIND_POLTERGEIST,
	SPELL_KIND_ANC_MAX_N,
/* end */
	SPELL_KIND_MAX_N,
} spell_kind_t;

/* STRINGED - ���� */
#define	SPELL_KIND_BAR_CURE_MIN_N	SPELL_KIND_SONG_CURE_HP
#define	SPELL_KIND_BAR_CURE_MAX_N	SPELL_KIND_SONG_CURE_MP
/* WOODWIND - ǽ���Ͷ��� */
#define	SPELL_KIND_BAR_STRENGTHEN_ABL_MIN_N	SPELL_KIND_SONG_SHARPNESS
#define	SPELL_KIND_BAR_STRENGTHEN_ABL_MAX_N	SPELL_KIND_SONG_ATTRACTIVE
/* BRASS - ǽ���ͼ��� */
#define	SPELL_KIND_BAR_WEAKEN_ABL_MIN_N	SPELL_KIND_SONG_DULLNESS
#define	SPELL_KIND_BAR_WEAKEN_ABL_MAX_N	SPELL_KIND_SONG_UNATTRACTIVE
/* PERCUSSION - ������ */
#define	SPELL_KIND_BAR_RESI_STAT_MIN_N	SPELL_KIND_SONG_RESI_STAT_STONE
#define	SPELL_KIND_BAR_RESI_STAT_MAX_N	SPELL_KIND_SONG_RESI_STAT_DRUNK

/* ��ʸ�θ����ϰ� */

typedef enum {
	EXTENT_KIND_NULL,
	EXTENT_KIND_NORMAL,	/* �̾� */
	EXTENT_KIND_SPREAD,	/* ����ͭ�� */
	EXTENT_KIND_MASS,	/* ���� */
	EXTENT_KIND_LIMIT,	/* ���� */
	EXTENT_KIND_HALF,	/* ����Ⱦ�� */
	EXTENT_KIND_DOUBLE,	/* �������� */
	EXTENT_KIND_MAX_N,
} extent_kind_t;

#endif	/* SPELL_KIND_H */