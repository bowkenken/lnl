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
* $Id: item.h,v 1.107 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	ITEM_H
#define	ITEM_H

/***************************************************************
* �����ƥ�
***************************************************************/

#include	"spell.h"
#include	"trap.h"

#include	"item-kind.h"
#include	"item-randm-art.h"

/**/

/* ���С��λ��Ƥ����� */
#define	MBR_ITEM_MAX_N	16
/* �µܤ�����Ƥ���ʿ�ѿ� */
#define	DUN_ITEM_AVE_N	16
/* �����������Ƥ���ʿ�ѿ� */
#define	DUN_ITEM_TRAP_ROOM_AVE_N	4

/* �����ƥ�̾�κ���ʸ���� */
#define	ITEM_NAME_MAX_LEN	60
#define	ITEM_NAME_MAX_BYTE	\
	(ITEM_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* ���ʤΥ����ƥ�̾�κ���ʸ���� */
#define	ITEM_ART_NAME_MAX_LEN	(ITEM_NAME_MAX_LEN + 16)
#define	ITEM_ART_NAME_MAX_BYTE	\
	(ITEM_ART_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* ��ʪ�Υ����ȥ�κ��粻��� */
#define	SCROLL_TTL_SYLLABLE_MAX_N	4
/* ��ʪ�Υ����ȥ�κ���ʸ���� */
#define	SCROLL_TTL_MAX_LEN	50
#define	SCROLL_TTL_MAX_BYTE	\
	(SCROLL_TTL_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* ţ��ʿ���ܿ� */
#define	SPIKE_AVE_N	11

/* �����ƥ�����̤�������˴����֤��Ƥ�������򤱤����Ⱦ�� */
#define	PUT_ITEM_R	MAP_MAX_X

/* �����ƥ��«�ͤ������� */
#define	BUNDLE_MAX_N	12	/* �̾異���ƥ� */
#define	BUNDLE_SPIKE_MAX_N	99	/* ţ */
#define	BUNDLE_WPN_MAX_N	99	/* ��� */

/* �����ƥब�����Ƥ���Ψ */
#define	CURSE_ITEM_RATE	((rate_t)30)

/* ��Ȣ�����äƤ��륢���ƥ�κǾ��� */
#define	CHEST_HOLD_MIN_N	4
/* ��Ȣ�����äƤ��륢���ƥ�κ���� */
#define	CHEST_HOLD_MAX_N	8
/* �������٤���Ȣ�κ���� */
#define	CAN_CARRY_CHEST_MAX_N	1

/* �����ƥ�δ� */

#define	FACE_MJR_WEAPON	')'
#define	FACE_MNR_KNIFE	'n'
#define	FACE_MNR_SHORT_SWORD	's'
#define	FACE_MNR_LONG_SWORD	'w'
#define	FACE_MNR_SABRE	'b'
#define	FACE_MNR_RAPIER	'r'
#define	FACE_MNR_HAND_AXE	'a'
#define	FACE_MNR_BATTLE_AXE	'x'
#define	FACE_MNR_SPEAR	'p'
#define	FACE_MNR_LANCE	'l'
#define	FACE_MNR_FLAIL	'f'
#define	FACE_MNR_MACE	'm'
#define	FACE_MNR_HAMMER	'h'
#define	FACE_MNR_GLAIVE	'g'
#define	FACE_MNR_KNUCKLE	'k'
#define	FACE_MNR_BOW	'-'
#define	FACE_MNR_ARW	'|'
#define	FACE_MNR_STONE	','
#define	FACE_MNR_DAGGER	'+'

#define	FACE_MJR_ARMOR	']'
#define	FACE_MNR_ARMOR_SHIELD	's'
#define	FACE_MNR_ARMOR_HEAD	'h'
#define	FACE_MNR_ARMOR_BODY	'b'
#define	FACE_MNR_ARMOR_ARM	'a'
#define	FACE_MNR_ARMOR_FEET	'f'
#define	FACE_MNR_ARMOR_ABOUT_BODY	'm'

#define	FACE_MJR_POTION	'!'
#define	FACE_MJR_SCROLL	'?'

#define	FACE_MJR_STICK	'-'
#define	FACE_MNR_WAND	'w'
#define	FACE_MNR_ROD	'r'
#define	FACE_MNR_STAFF	's'

#define	FACE_MJR_ACCESSORY	'='
#define	FACE_MNR_RING	'r'
#define	FACE_MNR_AMULET	'a'
#define	FACE_MNR_NECKLACE	'n'

#define	FACE_MJR_FOOD	':'

#define	FACE_MJR_CHEST	'&'

#define	FACE_MJR_COIN	'$'

#define	FACE_MJR_GEM	'*'

#define	FACE_MJR_MISC	'\"'
#define	FACE_MNR_ANTHOLOGY	'a'
#define	FACE_MNR_LIGHT	'l'
#define	FACE_MNR_SPIKE	's'
#define	FACE_MNR_TOBACCO	't'
#define	FACE_MNR_PIPE	'p'
#define	FACE_MNR_DISPOSAL	'd'
#define	FACE_MNR_RARE_GOODS	'!'
#define	FACE_MNR_BONE_GOOD	'+'
#define	FACE_MNR_BONE_EVIL	'x'
#define	FACE_MNR_JUNK	'*'

#define	FACE_MJR_INST	FACE_MJR_MISC
#define	FACE_MNR_INST	'i'
#define	FACE_MNR_INST_STRINGED	'S'
#define	FACE_MNR_INST_WOODWIND	'W'
#define	FACE_MNR_INST_BRASS	'B'
#define	FACE_MNR_INST_PERCUSSION	'P'
#define	FACE_MNR_INST_MISC	'M'

/**/

#define	WPN_ATTACK_MAX_N	4

#define	ITEM_THROW_RANGE_MAX_R	30
#define	STICK_RANGE_R	40

/* ���ζ��� */

#define	WPN_HIT_RANK_AAA	((rate_t)+30)
#define	WPN_HIT_RANK_AA	((rate_t)+25)
#define	WPN_HIT_RANK_A	((rate_t)+20)
#define	WPN_HIT_RANK_B	((rate_t)+15)
#define	WPN_HIT_RANK_C	((rate_t)+10)
#define	WPN_HIT_RANK_D	((rate_t)+5)
#define	WPN_HIT_RANK_E	((rate_t)+0)

#define	WPN_HIT_KATANA	((rate_t)100)
#define	WPN_HIT_L_SWORD	((rate_t)100)
#define	WPN_HIT_FLAIL	((rate_t)90)
#define	WPN_HIT_BOW	((rate_t)80)
#define	WPN_HIT_DAGGER	((rate_t)80)
#define	WPN_HIT_SPEAR	((rate_t)70)
#define	WPN_HIT_POLE	((rate_t)70)
#define	WPN_HIT_RAPIER	((rate_t)60)
#define	WPN_HIT_S_SWORD	((rate_t)50)
#define	WPN_HIT_HAMMER	((rate_t)50)
#define	WPN_HIT_MACE	((rate_t)40)
#define	WPN_HIT_AXE	((rate_t)30)
#define	WPN_HIT_KNIFE	((rate_t)20)
#define	WPN_HIT_KNUCKLE	((rate_t)10)
#define	WPN_HIT_UNARMED	((rate_t)10)

#define	WPN_DAM_RANK_AAA	((rate_t)+30)
#define	WPN_DAM_RANK_AA	((rate_t)+25)
#define	WPN_DAM_RANK_A	((rate_t)+20)
#define	WPN_DAM_RANK_B	((rate_t)+15)
#define	WPN_DAM_RANK_C	((rate_t)+10)
#define	WPN_DAM_RANK_D	((rate_t)+5)
#define	WPN_DAM_RANK_E	((rate_t)+0)

#define	WPN_DAM_AXE	((rate_t)100)
#define	WPN_DAM_POLE	((rate_t)70)
#define	WPN_DAM_L_SWORD	((rate_t)70)
#define	WPN_DAM_KATANA	((rate_t)70)
#define	WPN_DAM_HAMMER	((rate_t)60)
#define	WPN_DAM_SPEAR	((rate_t)60)
#define	WPN_DAM_S_SWORD	((rate_t)50)
#define	WPN_DAM_MACE	((rate_t)50)
#define	WPN_DAM_FLAIL	((rate_t)50)
#define	WPN_DAM_RAPIER	((rate_t)50)
#define	WPN_DAM_BOW	((rate_t)50)
#define	WPN_DAM_KNIFE	((rate_t)40)
#define	WPN_DAM_DAGGER	((rate_t)40)
#define	WPN_DAM_KNUCKLE	((rate_t)20)
#define	WPN_DAM_UNARMED	((rate_t)10)

#define	WPN_CRTCL_KATANA	((rate_t)100)
#define	WPN_CRTCL_KNIFE	((rate_t)90)
#define	WPN_CRTCL_DAGGER	((rate_t)90)
#define	WPN_CRTCL_AXE	((rate_t)80)
#define	WPN_CRTCL_RAPIER	((rate_t)70)
#define	WPN_CRTCL_SPEAR	((rate_t)70)
#define	WPN_CRTCL_POLE	((rate_t)70)
#define	WPN_CRTCL_HAMMER	((rate_t)60)
#define	WPN_CRTCL_L_SWORD	((rate_t)50)
#define	WPN_CRTCL_BOW	((rate_t)50)
#define	WPN_CRTCL_S_SWORD	((rate_t)40)
#define	WPN_CRTCL_MACE	((rate_t)40)
#define	WPN_CRTCL_FLAIL	((rate_t)30)
#define	WPN_CRTCL_KNUCKLE	((rate_t)10)
#define	WPN_CRTCL_UNARMED	((rate_t)10)

#define	POTION_PRICE_A	1000
#define	POTION_PRICE_B	800
#define	POTION_PRICE_C	600
#define	POTION_PRICE_D	400
#define	POTION_PRICE_E	200

#define	SCROLL_PRICE_S	10000
#define	SCROLL_PRICE_A	1000
#define	SCROLL_PRICE_B	800
#define	SCROLL_PRICE_C	600
#define	SCROLL_PRICE_D	400
#define	SCROLL_PRICE_E	200

#define	STICK_PRICE_A	1000
#define	STICK_PRICE_B	800
#define	STICK_PRICE_C	600
#define	STICK_PRICE_D	400
#define	STICK_PRICE_E	200

#define	ACCE_PRICE_A	50000
#define	ACCE_PRICE_B	40000
#define	ACCE_PRICE_C	30000
#define	ACCE_PRICE_D	20000
#define	ACCE_PRICE_E	10000

/***************************************************************/

/* �������� */

/* ���֤��Ѥ�����ϥ����֡��ǡ����⽤������ */
typedef enum {
	EQUIP_KIND_WIELDING,
	EQUIP_KIND_SHIELD,
	EQUIP_KIND_BOW,
	EQUIP_KIND_ARW,
	EQUIP_KIND_HEAD,
	EQUIP_KIND_NECK,
	EQUIP_KIND_BODY,
	EQUIP_KIND_ABOUT_BODY,
	EQUIP_KIND_ARM,
	EQUIP_KIND_RIGHT_HAND,
	EQUIP_KIND_LEFT_HAND,
	EQUIP_KIND_FEET,
	EQUIP_KIND_LIGHT_SOURCE,

	EQUIP_KIND_MAX_N,
	EQUIP_KIND_NULL = EQUIP_KIND_WIELDING,
} equip_kind_t;

/* ���μ��� */

typedef enum {
	WPN_KIND_NULL,
/* �ʥ��� */
	WPN_KIND_KNIFE,
	WPN_KIND_KRIS_KNIFE,
	WPN_KIND_MAIN_GAUCHE,
	WPN_KIND_SWORD_BREAKER,
	WPN_KIND_KATAR,
	WPN_KIND_JAMADHAR,
	WPN_KIND_KUKRI,
/* ���硼�ȡ������� */
	WPN_KIND_SHORT_SWORD,
	WPN_KIND_GLADIUS,
/* ��󥰡������� */
	WPN_KIND_LONG_SWORD,
	WPN_KIND_BROAD_SWORD,
	WPN_KIND_BASTARD_SWORD,
	WPN_KIND_CLAYMORE,
	WPN_KIND_GREAT_SWORD,
/* �����٥� */
	WPN_KIND_SABRE,
	WPN_KIND_SHAMSHIR,
	WPN_KIND_TALWAR,
	WPN_KIND_FALCHION,
	WPN_KIND_CUTLASS,
	WPN_KIND_SHOTEL,
	WPN_KIND_KATANA,
	WPN_KIND_WAKIZASHI,
/* �쥤�ԥ� */
	WPN_KIND_RAPIER,
	WPN_KIND_ESTOC,
/* �ϥ�ɡ����å��� */
	WPN_KIND_HAND_AXE,
	WPN_KIND_FRANCISCA,
	WPN_KIND_BHUJ,
/* �Хȥ롦���å��� */
	WPN_KIND_BATTLE_AXE,
	WPN_KIND_BROAD_AXE,
	WPN_KIND_GREAT_AXE,
/* ���ԥ� */
	WPN_KIND_SPEAR,
	WPN_KIND_PILUM,
	WPN_KIND_PIKE,
	WPN_KIND_JAVELIN,
	WPN_KIND_TRIDENT,
/* ��� */
	WPN_KIND_LANCE,
	WPN_KIND_LANCE_OF_LONGINUS,
/* �ե쥤�� */
	WPN_KIND_LIGHT_FLAIL,
	WPN_KIND_HEAVY_FLAIL,
	WPN_KIND_MORNINGSTAR,
	WPN_KIND_NUNCHAKUS,
/* �ᥤ�� */
	WPN_KIND_WOODEN_CLUB,
	WPN_KIND_QUARTER_STAFF,
	WPN_KIND_LIGHT_MACE,
	WPN_KIND_HEAVY_MACE,
/* �ϥ�ޡ� */
	WPN_KIND_WAR_HAMMER,
	WPN_KIND_WAR_PICK,
	WPN_KIND_ZAGHNOL,
	WPN_KIND_BEC_DE_CORBIN,
/* ���쥤�� */
	WPN_KIND_PARTIZAN,
	WPN_KIND_POLEAXE,
	WPN_KIND_GLAIVE,
	WPN_KIND_HALBERD,
	WPN_KIND_CHAUVE_SOURIS,
	WPN_KIND_CORSESCA,
	WPN_KIND_SCYTHE,
	WPN_KIND_FAUCHARD,
	WPN_KIND_GUISARME,
/* �ʥå��� */
	WPN_KIND_BRASS_KNUCKLE,
	WPN_KIND_BAGH_NAKH,
/* �� */
	WPN_KIND_SLING,
	WPN_KIND_SHORT_BOW,
	WPN_KIND_LONG_BOW,
	WPN_KIND_COMPOSITE_BOW,
	WPN_KIND_LIGHT_CROSS_BOW,
	WPN_KIND_HEAVY_CROSS_BOW,
	WPN_KIND_BLOW_GUN,
/* �� */
	WPN_KIND_STONE,
	WPN_KIND_BULLET,
	WPN_KIND_ARW,
	WPN_KIND_BOLT,
	WPN_KIND_NEEDLE,
/* ������ */
	WPN_KIND_DAGGER,
	WPN_KIND_DARTS,
	WPN_KIND_SHURIKEN,
	WPN_KIND_BOOMERANG,
/* ��󥰡�������(�����ƥ��ե�����) */
	WPN_KIND_EXCALIBUR,
/**/
	WPN_KIND_MAX_N,
} wpn_kind_t;

/* �ݤμ��� */

typedef enum {
	BOW_KIND_NULL,
	BOW_KIND_BOW,
	BOW_KIND_CROSS_BOW,
	BOW_KIND_SLING,
	BOW_KIND_BLOW_GUN,
	BOW_KIND_DAGGER,
	BOW_KIND_MAX_N,
} bow_kind_t;

/* �ɶ�μ��� */

#define	FACE_MNR_ARMOR_SHIELD	's'
#define	FACE_MNR_ARMOR_HEAD	'h'
#define	FACE_MNR_ARMOR_BODY	'b'
#define	FACE_MNR_ARMOR_ARM	'a'
#define	FACE_MNR_ARMOR_FEET	'f'
#define	FACE_MNR_ARMOR_ABOUT_BODY	'm'
typedef enum {
	ARMOR_KIND_NULL,
/* �� */
	ARMOR_KIND_BUCKLER_SHIELD,
	ARMOR_KIND_ROUND_SHIELD,
	ARMOR_KIND_KITE_SHIELD,
	ARMOR_KIND_HEATER_SHIELD,
/* Ƭ������ */
	ARMOR_KIND_LEATHER_CAP,
	ARMOR_KIND_METAL_CAP,
	ARMOR_KIND_SALLET,
	ARMOR_KIND_CLOSE_HELMET,
	ARMOR_KIND_SILVER_CROWN,
	ARMOR_KIND_GOLDEN_CROWN,
	ARMOR_KIND_JEWELED_CROWN,
/* ƹ�Τ����� */
	ARMOR_KIND_ROBE,
	ARMOR_KIND_SOFT_LEATHER_ARMOR,
	ARMOR_KIND_HARD_LEATHER_ARMOR,
	ARMOR_KIND_RING_MAIL,
	ARMOR_KIND_SCALE_MAIL,
	ARMOR_KIND_LAMELLAR_ARMOR,
	ARMOR_KIND_CHAIN_MAIL,
	ARMOR_KIND_PLATE_ARMOR,
/* �Ӥ����� */
	ARMOR_KIND_LEATHER_GLOVES,
	ARMOR_KIND_GAUNTLETS,
/* ­������ */
	ARMOR_KIND_LEATHER_BOOTS,
	ARMOR_KIND_GREAVE,
/* ��������� */
	ARMOR_KIND_CLOAK,
/* ƹ�Τ�����(�����ƥ��ե�����) */
	ARMOR_KIND_RED_DRAGON_SCALE,
	ARMOR_KIND_BLUE_DRAGON_SCALE,
	ARMOR_KIND_YELLOW_DRAGON_SCALE,
	ARMOR_KIND_GREEN_DRAGON_SCALE,
	ARMOR_KIND_WHITE_DRAGON_SCALE,
	ARMOR_KIND_BLACK_DRAGON_SCALE,
	ARMOR_KIND_COPPER_DRAGON_SCALE,
	ARMOR_KIND_SILVER_DRAGON_SCALE,
	ARMOR_KIND_GOLD_DRAGON_SCALE,
	ARMOR_KIND_MITHRIL_CHAIN,
/* �Ӥ�����(�����ƥ��ե�����) */
	ARMOR_KIND_GAUNTLETS_OF_POW_UP_HIT,
	ARMOR_KIND_GAUNTLETS_OF_POW_DOWN_HIT,
	ARMOR_KIND_GAUNTLETS_OF_POW_UP_WPN_CRTCL,
	ARMOR_KIND_GAUNTLETS_OF_POW_DOWN_WPN_CRTCL,
	ARMOR_KIND_GAUNTLETS_OF_POW_UP_DAM,
	ARMOR_KIND_GAUNTLETS_OF_POW_DOWN_DAM,
/* ­������(�����ƥ��ե�����) */
	ARMOR_KIND_SPEED_BOOTS,
	ARMOR_KIND_SLOW_BOOTS,
/**/
	ARMOR_KIND_MAX_N,
} armor_kind_t;

/* ���μ��� */

typedef enum {
	POTION_KIND_NULL,
	POTION_KIND_WATER,
	POTION_KIND_MILK,
	POTION_KIND_RED_WINE,
	POTION_KIND_WHITE_WINE,
	POTION_KIND_ROSE_WINE,
	POTION_KIND_ALE,
	POTION_KIND_BRANDY,
	POTION_KIND_RUM,
	POTION_KIND_COFFE,
	POTION_KIND_ICE_COFFE,
	POTION_KIND_TEA,
	POTION_KIND_MILK_TEA,
	POTION_KIND_LEMON_TEA,
	POTION_KIND_ICE_TEA,
	POTION_KIND_ICE_MILK_TEA,
	POTION_KIND_ICE_LEMON_TEA,
	POTION_KIND_APPLE_JUICE,
	POTION_KIND_GRAPE_JUICE,
	POTION_KIND_ORANGE_JUICE,
	POTION_KIND_BLACK_BERRY_JUICE,
	POTION_KIND_CRAN_BERRY_JUICE,
	POTION_KIND_RASP_BERRY_JUICE,
	POTION_KIND_STRAW_BERRY_JUICE,
	POTION_KIND_OIL,
	POTION_KIND_STONE,
	POTION_KIND_PARALYZE,
	POTION_KIND_POISON,
	POTION_KIND_CONFUSION,
	POTION_KIND_BLIND,
	POTION_KIND_SLEEP,
	POTION_KIND_SILENCE,
	POTION_KIND_FEAR,
	POTION_KIND_HALLUCINATION,
	POTION_KIND_CHARM,
	POTION_KIND_FLY,
	POTION_KIND_VANISH,
	POTION_KIND_IRON_BODY,
	POTION_KIND_PASSWALL,
	POTION_KIND_SENSE_INVISIBLE,
	POTION_KIND_RESI_PHYS,
	POTION_KIND_RESI_HEAT,
	POTION_KIND_RESI_COLD,
	POTION_KIND_RESI_ACID,
	POTION_KIND_RESI_MIND,
	POTION_KIND_RESI_ELEC,
	POTION_KIND_RESI_POIS,
	POTION_KIND_SHARPNESS,
	POTION_KIND_DULLNESS,
	POTION_KIND_STRENGTH,
	POTION_KIND_WEAKNESS,
	POTION_KIND_QUICKNESS,
	POTION_KIND_SLOWNESS,
	POTION_KIND_BRAINY,
	POTION_KIND_BRAINLESS,
	POTION_KIND_WISE,
	POTION_KIND_FOOLISH,
	POTION_KIND_ATTRACTIVE,
	POTION_KIND_UNATTRACTIVE,
	POTION_KIND_POW_UP_HP,
	POTION_KIND_SPEED_UP,
	POTION_KIND_SPEED_DOWN,
	POTION_KIND_CURE_LEV,
	POTION_KIND_CURE_HP_LIGHT,
	POTION_KIND_CURE_HP_MODERATE,
	POTION_KIND_CURE_HP_SERIOUS,
	POTION_KIND_CURE_HP_MAX,
	POTION_KIND_CURE_POISON,
	POTION_KIND_CURE_STATUS,
	POTION_KIND_DETECT_MNSTR,
	POTION_KIND_MAX_N,
} potion_kind_t;

/* ��ʪ�μ��� */

typedef enum {
	SCROLL_KIND_NULL,
	SCROLL_KIND_SLEEP,
	SCROLL_KIND_IDENTIFY_ITEM,
	SCROLL_KIND_IDENTIFY_ALL_ITEM,
	SCROLL_KIND_DETECT_ITEM,
	SCROLL_KIND_TELEPORT,
	SCROLL_KIND_POW_UP_WPN_HIT,
	SCROLL_KIND_POW_UP_WPN_CRTCL,
	SCROLL_KIND_POW_UP_WPN_DAM,
	SCROLL_KIND_POW_UP_ARMOR_DEF,
	SCROLL_KIND_POW_UP_ARMOR_CRTCL,
	SCROLL_KIND_POW_UP_ARMOR_AC,
	SCROLL_KIND_PROTECT_ARMOR,
	SCROLL_KIND_BOOMERANG,
	SCROLL_KIND_REMOVE_CURSE,
	SCROLL_KIND_RECALL,
	SCROLL_KIND_TYPHOON,
	SCROLL_KIND_CONFLAGRATION,
	SCROLL_KIND_EARTHQUAKE,
	SCROLL_KIND_THUNDERCLOUD,
	SCROLL_KIND_INUNDATION,
	SCROLL_KIND_SUBSTITUTE,
	SCROLL_KIND_BURNING_HANDS,
	SCROLL_KIND_RALLY,
	SCROLL_KIND_IRON_MAN,
	SCROLL_KIND_MIND_READING,
	SCROLL_KIND_MAX_N,
} scroll_kind_t;

/* ��μ��� */

typedef enum {
	STICK_KIND_NULL,
	STICK_KIND_WAND,
	STICK_KIND_ROD,
	STICK_KIND_STAFF,
	STICK_KIND_MAX_N,
} stick_kind_t;

/* ����������μ��� */

typedef enum {
	ACCE_KIND_NULL,
	ACCE_KIND_RING,
	ACCE_KIND_AMULET,
	ACCE_KIND_NECKLACE,
	ACCE_KIND_MAX_N,
} acce_kind_t;

/* ���ؤμ��� */

typedef enum {
	RING_KIND_NULL,
	RING_KIND_SLOW_DIGESTION,
	RING_KIND_TELEPORT_PARTY,
	RING_KIND_TELEPORT,
	RING_KIND_SHARPNESS,
	RING_KIND_DULLNESS,
	RING_KIND_STRENGTH,
	RING_KIND_WEAKNESS,
	RING_KIND_QUICKNESS,
	RING_KIND_SLOWNESS,
	RING_KIND_BRAINY,
	RING_KIND_BRAINLESS,
	RING_KIND_WISE,
	RING_KIND_FOOLISH,
	RING_KIND_ATTRACTIVE,
	RING_KIND_UNATTRACTIVE,
	RING_KIND_CURE_HP,
	RING_KIND_CURE_MP,
	RING_KIND_DRAIN_HP,
	RING_KIND_DRAIN_MP,
	RING_KIND_MAX_N,
} ring_kind_t;

/* ����μ��� */

typedef enum {
	AMULET_KIND_NULL,
	AMULET_KIND_RESI_STAT_DEAD,
	AMULET_KIND_RESI_STAT_STONE,
	AMULET_KIND_RESI_STAT_PARALYZE,
	AMULET_KIND_RESI_STAT_POISON,
	AMULET_KIND_RESI_STAT_CONFUSION,
	AMULET_KIND_RESI_STAT_BLIND,
	AMULET_KIND_RESI_STAT_SLEEP,
	AMULET_KIND_RESI_STAT_SILENCE,
	AMULET_KIND_RESI_STAT_FEAR,
	AMULET_KIND_RESI_STAT_HALLUCINATION,
	AMULET_KIND_RESI_STAT_CHARM,
	AMULET_KIND_RESI_STAT_DRUNK,
	AMULET_KIND_RESI_STAT_FLY,
	AMULET_KIND_RESI_STAT_VANISH,
	AMULET_KIND_RESI_STAT_IRON_BODY,
	AMULET_KIND_RESI_STAT_PASSWALL,
	AMULET_KIND_RESI_STAT_SENSE_INVISIBLE,
	AMULET_KIND_MAX_N,
} amulet_kind_t;

/* ���ؤμ��� */

typedef enum {
	NECKLACE_KIND_NULL,
	NECKLACE_KIND_RESI_PHYS,
	NECKLACE_KIND_RESI_HEAT,
	NECKLACE_KIND_RESI_COLD,
	NECKLACE_KIND_RESI_ACID,
	NECKLACE_KIND_RESI_MIND,
	NECKLACE_KIND_RESI_ELEC,
	NECKLACE_KIND_RESI_POIS,
	NECKLACE_KIND_CURSE_PHYS,
	NECKLACE_KIND_CURSE_HEAT,
	NECKLACE_KIND_CURSE_COLD,
	NECKLACE_KIND_CURSE_ACID,
	NECKLACE_KIND_CURSE_MIND,
	NECKLACE_KIND_CURSE_ELEC,
	NECKLACE_KIND_CURSE_POIS,
	NECKLACE_KIND_MAX_N,
} necklace_kind_t;

/* �ڴ�μ��� */

typedef enum {
	INST_KIND_NULL,

	/* STRINGED - ���� */
	INST_KIND_VIOLIN,
	INST_KIND_VIOLA,
	INST_KIND_CELLO,
	INST_KIND_DOUBLEBASS,
	INST_KIND_HARP,
	INST_KIND_MANDOLIN,
	INST_KIND_BANJO,
	INST_KIND_SITAR,

	/* WOODWIND - ǽ���Ͷ��� */
	INST_KIND_FLUTE,
	INST_KIND_CLARINET,
	INST_KIND_BASS_CLARINET,
	INST_KIND_PICCOLO,
	INST_KIND_OBOE,
	INST_KIND_BASSOON,
	INST_KIND_SAXOPHONE,

	/* BRASS - ǽ���ͼ��� */
	INST_KIND_TRUMPET,
	INST_KIND_TROMBONE,
	INST_KIND_FLUGELHORN,
	INST_KIND_CORNET,
	INST_KIND_HORN,
	INST_KIND_TUBA,
	INST_KIND_SOUSAPHONE,
	INST_KIND_BUGLE,

	/* PERCUSSION - ������ */
	INST_KIND_BASS_DRUM,
	INST_KIND_TENOR_DRUM,
	INST_KIND_SNARE_DRUM,
	INST_KIND_TOM_TOM,
	INST_KIND_CONGAS,
	INST_KIND_TIMPANI,
	INST_KIND_CYMBAL,
	INST_KIND_GONG,
	INST_KIND_MARACA,
	INST_KIND_TRIANGLE,
	INST_KIND_CASTANETS,
	INST_KIND_TUBULAR_BELLS,
	INST_KIND_XYLOPHONE,

	/* MISC - ���� */
	INST_KIND_ACCORDION,
	INST_KIND_BAGPIPE,
	INST_KIND_HARMONICA,
	INST_KIND_KAZOO,

	INST_KIND_MAX_N,
} inst_kind_t;

/* ���μ��� */

typedef enum {
	ANTHOLOGY_KIND_NULL,
	ANTHOLOGY_KIND_CURE,
	ANTHOLOGY_KIND_STRENGTHEN_ABL,
	ANTHOLOGY_KIND_WEAKEN_ABL,
	ANTHOLOGY_KIND_RESI_STAT,
	ANTHOLOGY_KIND_MAX_N,
} anthology_kind_t;

/* ������μ��� */

typedef enum {
	LIGHT_KIND_NULL,
	LIGHT_KIND_TORCH,
	LIGHT_KIND_LANTERN,
	LIGHT_KIND_LAMP,
	LIGHT_KIND_MAX_N,
} light_kind_t;

/* �����μ��� */

typedef enum {
	FOOD_KIND_NULL,
	FOOD_KIND_PRESERVED,
	FOOD_KIND_SAUSAGE,
	FOOD_KIND_BACON,
	FOOD_KIND_CHIPPED_BEEF,
	FOOD_KIND_CORNED_BEEF,
	FOOD_KIND_BREAD,
	FOOD_KIND_BROWN_BREAD,
	FOOD_KIND_TOAST,
	FOOD_KIND_PANCAKE,
	FOOD_KIND_SALAD,
	FOOD_KIND_POTATO_SALAD,
	FOOD_KIND_SCRAMBLED_EGGS,
	FOOD_KIND_FRIED_EGGS,
	FOOD_KIND_HARD_BOILED_EGGS,
	FOOD_KIND_SOFT_BOILED_EGGS,
	FOOD_KIND_BEEF_STEAK,
	FOOD_KIND_PORK_SAUTE,
	FOOD_KIND_FRIED_CHICKEN,
	FOOD_KIND_FRIED_FISH,
	FOOD_KIND_FRIED_POTATO,
	FOOD_KIND_STEWED_BEEF,
	FOOD_KIND_CONSOMME,
	FOOD_KIND_POTAGE,
	FOOD_KIND_SOUP_OF_TURNIP,
	FOOD_KIND_APPLE_PIE,
	FOOD_KIND_APPLE,
	FOOD_KIND_GRAPE,
	FOOD_KIND_ORANGE,
	FOOD_KIND_PEAR,
	FOOD_KIND_GRAPEFRUIT,
	FOOD_KIND_PLUM,
	FOOD_KIND_PEACH,
	FOOD_KIND_APRICOT,
	FOOD_KIND_BLACK_BERRY,
	FOOD_KIND_CRAN_BERRY,
	FOOD_KIND_RASP_BERRY,
	FOOD_KIND_STRAW_BERRY,
	FOOD_KIND_MAX_N,
} food_kind_t;

/* �ѥ��פ�Ȥ����ɤ����Υե饰 */

typedef unsigned long	flg_tobacco_t;
#define	FLG_TOBACCO_USE_PIPE	(1 << 0)	/* �Ȥ� */
#define	FLG_TOBACCO_CAN_USE_PIPE	(1 << 1)	/* �Ȥ�Я������ */

/* ����μ��� */

typedef enum {
	TOBACCO_KIND_NULL,
	TOBACCO_KIND_CIGARET,
	TOBACCO_KIND_CIGAR,
	TOBACCO_KIND_CUT_TOBACCO,
	TOBACCO_KIND_SNUFF_TOBACCO,
	TOBACCO_KIND_CHEWING_TOBACCO,
	TOBACCO_KIND_ABSTAIN_GUM,
	TOBACCO_KIND_MAX_N,
} tobacco_kind_t;

/* ����Υ֥��� */

typedef enum {
	TOBACCO_BRAND_NULL,

	/* CIGARET */
	TOBACCO_BRAND_HELLO,
	TOBACCO_BRAND_SUN_SHINE,
	TOBACCO_BRAND_CHERRY_TREE,
	TOBACCO_BRAND_GOLDEN_RAT,
	TOBACCO_BRAND_AIR_SHIT,
	TOBACCO_BRAND_HOP,
	TOBACCO_BRAND_PIECE,
	TOBACCO_BRAND_HARPY,
	TOBACCO_BRAND_HIGH_LIGHT,
	TOBACCO_BRAND_SHOOTING_STARS,
	TOBACCO_BRAND_WILD_NINE,
	TOBACCO_BRAND_WILD_NINE_MENTHOL,
	TOBACCO_BRAND_LODGE,
	TOBACCO_BRAND_LODGE_MENTHOL,
	TOBACCO_BRAND_CANCER,
	TOBACCO_BRAND_CANCER_MENTHOL,
	TOBACCO_BRAND_FRONT_LINE,
	TOBACCO_BRAND_FRONT_LINE_MENTHOL,
	TOBACCO_BRAND_MARCO_POLO,
	TOBACCO_BRAND_CAMELLIA,
	TOBACCO_BRAND_GOOD_LUCK,
	TOBACCO_BRAND_BAD_GUY,

	/* CIGAR */
	TOBACCO_BRAND_ARCADIA,
	TOBACCO_BRAND_GLORIA,
	TOBACCO_BRAND_VULCAN,
	TOBACCO_BRAND_PONY,
	TOBACCO_BRAND_KEITH,
	TOBACCO_BRAND_LUMBERJACK,
	TOBACCO_BRAND_CORONA,
	TOBACCO_BRAND_HALF_CORONA,
	TOBACCO_BRAND_CRYSTAL,

	/* CUT TOBACCO */
	TOBACCO_BRAND_FOREST_BRANDY,
	TOBACCO_BRAND_SILK_ROAD,
	TOBACCO_BRAND_PROMENADE,
	TOBACCO_BRAND_BIG_HORN,
	TOBACCO_BRAND_ROCKING_CHAIR,
	TOBACCO_BRAND_VANILLA,
	TOBACCO_BRAND_WILD_MANGO,
	TOBACCO_BRAND_KENTUCKY_BIRD,
	TOBACCO_BRAND_ORIENT,
	TOBACCO_BRAND_FUJI,

	/* SNUFF TOBACCO */
	TOBACCO_BRAND_DOGGY_APRICOT,
	TOBACCO_BRAND_DOGGY_WHISKY,
	TOBACCO_BRAND_DOGGY_HONEY,
	TOBACCO_BRAND_DOGGY_SPEARMINT,
	TOBACCO_BRAND_DOGGY_PEPPERMINT,
	TOBACCO_BRAND_DOGGY_VANILLA,
	TOBACCO_BRAND_DOGGY_MENTHOL,
	TOBACCO_BRAND_DOGGY_CITRUS,
	TOBACCO_BRAND_DOGGY_SHERRY,

	/* CHEWING TOBACCO */
	TOBACCO_BRAND_ROSE_PREMIUM,
	TOBACCO_BRAND_ROSE_VANILLA,
	TOBACCO_BRAND_ROSE_MENTHOL,

	/* ABSTAIN GUM */
	TOBACCO_BRAND_NICOTIME,

	TOBACCO_BRAND_MAX_N,
} tobacco_brand_t;

/* �ѥ��פΥե饰 */

typedef unsigned long	flg_pipe_t;
#define	FLG_PIPE_CONSUMPTION	(1 << 0)	/* ������ */

/* �ѥ��פμ��� */

typedef enum {
	PIPE_KIND_NULL,
	PIPE_KIND_PIPE,
	PIPE_KIND_KISEL,
	PIPE_KIND_CIGARET_HOLDER,
	PIPE_KIND_MAX_N,
} pipe_kind_t;

/* õ�������ƥ�μ��� */

typedef enum {
	RARE_GOODS_KIND_NULL,
	RARE_GOODS_KIND_DAEMON_SCORE,
	RARE_GOODS_KIND_VAMPIRES_CROSS,
	RARE_GOODS_KIND_SCHWARZSCHILD_DAEMON,
	RARE_GOODS_KIND_REASON_OF_DECLINE,
	RARE_GOODS_KIND_GARGOYLES_TEARS,
	RARE_GOODS_KIND_FLUTE_OF_MADONNA,
	RARE_GOODS_KIND_THE_ART_OF_WAR,
	RARE_GOODS_KIND_TICKET_TO_PARADISE,
	RARE_GOODS_KIND_CALL_OF_HADES,
	RARE_GOODS_KIND_MEMORIES_OF_THE_GOLDEN_AGE,
	RARE_GOODS_KIND_ISNT_REALIZED,
	RARE_GOODS_KIND_MAX_N,
} rare_goods_kind_t;

/* ������μ��� */

typedef enum {
	COIN_KIND_NULL,
	COIN_KIND_GOLD,
	COIN_KIND_SILVER,
	COIN_KIND_COPPER,
	COIN_KIND_MAX_N,
} coin_kind_t;

/***************************************************************/


typedef struct {
	/* �����ƥ�κ����̾�����ֹ�ꥹ�ȤΥ���ǥå��� */
	n_msg_idx_t	name_idx;

	/* �����ƥ�κ�������˻Ȥ��Ƥ��뤫 */
	bool_t	flg_used;
} ls_identified_t;

/* ���Υե饰 */

typedef unsigned long	flg_wpn_tab_t;

#define	FLG_WPN_TAB_BOW	(1 << 0)	/* �� */
#define	FLG_WPN_TAB_ARW	(1 << 1)	/* �� */
#define	FLG_WPN_TAB_TWO_HANDED	(1 << 2)	/* ɬ��ξ����� */
#define	FLG_WPN_TAB_CAN_TWO_HANDED	(1 << 3)	/* ξ�������ǽ */
#define	FLG_WPN_TAB_RET	(1 << 4)	/* ��������ä���� */
#define	FLG_WPN_TAB_BUNDLE	(1 << 5)	/* «�ͤ��� */
#define	FLG_WPN_TAB_NOT_SPEND	(1 << 6)	/* ���񤷤ʤ� */
/* �֡����� */
#define	FLG_WPN_TAB_BOOMERANG	\
		(FLG_WPN_TAB_ARW | FLG_WPN_TAB_RET | FLG_WPN_TAB_BUNDLE)
/* ��ڳ��� */
#define	FLG_WPN_TAB_THROW	\
		(FLG_WPN_TAB_ARW | FLG_WPN_TAB_NOT_SPEND)

/* �����ƥ�Υե饰 */

typedef unsigned long	flg_item_t;

#define	FLG_ITEM_DETECTED	(1 << 0)	/* ȯ���� */
#define	FLG_ITEM_IDENTIFIED	(1 << 1)	/* ���̺� */
#define	FLG_ITEM_CURSED	(1 << 2)	/* �����Ƥ��� */
#define	FLG_ITEM_PROTECTED	(1 << 3)	/* �ɸ����ˡ�������äƤ��� */

/* �ƥ����ƥ�Υǡ��� */

typedef struct {
	wpn_kind_t	kind;
	long	add_hit;	/* �����Ͻ��� */
	long	add_crtcl;	/* ����ƥ����뽤�� */
	long	add_dam;	/* ���᡼������ */
	char	slayer;	/* ���᡼���ܲ� (�ߴ����ݻ��Τ���θŤ�����) */
	wpn_randm_art_t	randm_art[WPN_RANDM_ART_LS_MAX_N + 1];
	flg_wpn_tab_t	flg;	/* �ե饰 */
} wpn_t;

typedef struct {
	armor_kind_t	kind;
	long	add_def;	/* �ɸ��Ͻ��� */
	long	add_crtcl;	/* ����ƥ����뽤�� */
	long	add_ac;	/* �����ޡ����饹���� */
	armor_randm_art_t	randm_art[ARMOR_RANDM_ART_LS_MAX_N + 1];
} armor_t;

typedef struct {
	potion_kind_t	kind;
} potion_t;

typedef struct {
	scroll_kind_t	kind;
} scroll_t;

typedef struct {
	stick_kind_t	kind;
	spell_kind_t	spell_kind;
	long	n;
} stick_t;

typedef struct {
	acce_kind_t	kind;
	ring_kind_t	ring_kind;
	amulet_kind_t	amulet_kind;
	necklace_kind_t	necklace_kind;
} acce_t;

typedef struct {
	inst_kind_t	kind;	/* �ڴ�μ��� */
	bool_t	flg_limit;	/* ���Τ��оݤ�������뤫 */
	spell_kind_t	spell_kind;	/* �ɲäǽŤͳݤ��������� */
} inst_t;

typedef struct {
	anthology_kind_t	kind;	/* ���μ��� */
} anthology_t;

typedef struct {
	light_kind_t	kind;
	long	turn;
	wish_level_t	wish_level;
	long	wish_n;
	bool_t	flg_used;
} light_t;

typedef struct {
	food_kind_t	kind;
} food_t;

typedef struct {
	struct item_t	*contents;	/* ��̣�Υꥹ�� */
	long	ref;	/* ���ȿ� */
	trap_t	*trap;	/* � */
} chest_t;

typedef struct {
	tobacco_kind_t	kind;
	tobacco_brand_t	brand;	/* �֥��� */
	long	turn;	/* �ۤ��Ĥ꥿����� */
} tobacco_t;

typedef struct {
	pipe_kind_t	kind;
	long	turn;	/* �ۤ��Ĥ꥿����� */
	long	consume_turn;	/* ���񥿡���� */
} pipe_t;

typedef struct {
	long	n, max_n;
} disposal_t;

typedef struct {
	rare_goods_kind_t	kind;
	mnstr_kind_t	mnstr_kind;	/* ���äƤ����󥹥����μ��� */
} rare_goods_t;

typedef struct {
	mnstr_tab_t	*mnstr_tab;
	long	dun_lev;
} bone_t;

typedef struct {
	coin_kind_t	kind;
} coin_t;

/***************************************************************/
/* �ơ��֥� */

typedef struct {
	/* ��������̾�� */
	char	*name;
	n_msg_t	name_n;
	/* ���̸��̾�� */
	char	*i_name;
	n_msg_t	i_name_n;

	/* ���� */
	wpn_kind_t	kind;

	/* �и�Ψ */
	rate_t	rate;
	/* ʿ�ѸĿ� */
	long	ave_n;

	/* ���ʤν���Ψ */
	rate_t	rate_price;
	/* ���ʤν��� */
	long	add_price;

	/* �ޥ��ʡ��δ� */
	char	mnr;

	/* �и��� */
	long	min_lev, max_lev, sgn_lev;

	/* �ݤμ��� */
	bow_kind_t	bow_kind;

	/* �ե饰 */
	flg_wpn_tab_t	flg;
	/* ��������ǽ������̵���Υե饰 */
	bool_t	flg_abl[ABL_KIND_MAX_N];

	/* ����Υǡ��� */
	attack_t	attack[WPN_ATTACK_MAX_N + 1];
} wpn_tab_t;

typedef struct {
	/* ��������̾�� */
	char	*name;
	n_msg_t	name_n;
	/* ���̸��̾�� */
	char	*i_name;
	n_msg_t	i_name_n;

	/* ���� */
	armor_kind_t	kind;

	/* ���ʤν���Ψ */
	rate_t	rate_price;
	/* ���ʤν��� */
	long	add_price;

	/* �ޥ��ʡ��δ� */
	char	mnr;

	/* ������������ */
	equip_kind_t	equip_kind;

	/* �����ͤν��� */
	rate_t	up_resi[RESI_KIND_MAX_N];
	/* �ɸ��� */
	rate_t	def, crtcl, ac;

	/* �и��� */
	long	min_lev, max_lev, sgn_lev;

	/* �и�Ψ */
	rate_t	rate;

	/* ��������ǽ������̵���Υե饰 */
	bool_t	flg_abl[ABL_KIND_MAX_N];

	/* �����Ƥ���Ψ */
	rate_t	rate_curse;

	/* �ݸ��Ƥ���ե饰 */
	bool_t	flg_protected;

	/* ǽ���ͽ����ǡ��� */
	modifier_t	modifier;
} armor_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	potion_kind_t	kind;

	/* �и�Ψ */
	rate_t	rate;

	/* �и��� */
	long	min_lev, max_lev, sgn_lev;

	/* ���� */
	gold_t	price;

	/* ��̾ */
	char	*color;
	n_msg_t	color_n;

	/* ���̺ѥե饰 */
	bool_t	flg_identified;
	/* �ǥե���Ȥο���Ȥ�ʤ��ե饰 */
	bool_t	flg_change_color;
} potion_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	scroll_kind_t	kind;

	/* �и�Ψ */
	rate_t	rate;

	/* �и��� */
	long	min_lev, max_lev, sgn_lev;

	/* ���� */
	gold_t	price;

	/* �����ȥ�β���� */
	long	ttl_n;

	/* �����ȥ�β���ꥹ�� */
	n_msg_idx_t	ttl_idx[SCROLL_TTL_SYLLABLE_MAX_N + 1];

	/* �����ȥ� */
	char	ttl[SCROLL_TTL_MAX_BYTE + 1];

	/* ���̺ѥե饰 */
	bool_t	flg_identified;
} scroll_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* �и�Ψ */
	rate_t	rate;

	/* ���Ѳ�ǽ��� */
	long	use_n;

	/* ���� */
	stick_kind_t	kind;

	/* �Ȥ�����ˡ�μ��� */
	spell_kind_t	spell_kind;

	/* �и��� */
	long	min_lev, max_lev, sgn_lev;

	/* ���� */
	gold_t	price;

	/* ���̾ */
	char	*material;
	n_msg_t	material_n;

	/* ���̺ѥե饰 */
	bool_t	flg_identified;
} stick_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	acce_kind_t	kind;
	/* ���ؤμ��� */
	ring_kind_t	ring_kind;
	/* ����μ��� */
	amulet_kind_t	amulet_kind;
	/* ���ؤμ��� */
	necklace_kind_t	necklace_kind;

	/* �и�Ψ */
	rate_t	rate;

	/* �и��� */
	long	min_lev, max_lev, sgn_lev;

	/* ���� */
	gold_t	price;

	/* �ޥ��ʡ��δ� */
	char	mnr;

	/* ������������ */
	equip_kind_t	equip_kind;

	/* ���̾ */
	char	*material;
	n_msg_t	material_n;

	/* ���̺ѥե饰 */
	bool_t	flg_identified;

	/* �����Ƥ���Ψ */
	rate_t	rate_curse;

	/* ǽ���ͽ����ǡ��� */
	modifier_t	modifier;
} acce_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	inst_kind_t	kind;

	/* �ޥ��ʡ��δ� */
	char	mnr;

	/* �����Ƥ���Ψ */
	rate_t	rate_curse;
} inst_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	anthology_kind_t	kind;
} anthology_tab_t;

typedef struct {
	/* ��������̾�� */
	char	*name;
	n_msg_t	name_n;
	/* ���̸��̾�� */
	char	*i_name;
	n_msg_t	i_name_n;

	/* ���� */
	light_kind_t	kind;

	/* �и�Ψ */
	rate_t	rate;

	/* �и��� */
	long	min_lev, max_lev, sgn_lev;

	/* ���� */
	gold_t	base_price, fill_price;

	/* ���Ѳ�ǽ������� */
	long	max_turn;
	/* ����ǽ�ե饰 */
	bool_t	flg_fill;

	/* ��ˡ�Υ��פ�����μ��� */
	wish_level_t	wish_level;
	/* ��ˡ�Υ��פκ�����Ѳ�� */
	long	wish_max_n;
} light_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	food_kind_t	kind;

	/* �и�Ψ */
	rate_t	rate;

	/* ʿ�ѸĿ� */
	long	ave_n;

	/* ���� */
	gold_t	price;

	/* ��ʢ�� */
	rate_t	fill_rate;
} food_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	tobacco_kind_t	kind;
	/* �֥���̾ */
	char	*brand_name;
	n_msg_t	brand_name_n;
	/* �֥��� */
	tobacco_brand_t	brand;

	/* �и�Ψ */
	rate_t	rate;

	/* ʿ�ѸĿ� */
	long	ave_n;

	/* ������� */
	long	turn;

	/* ���� */
	gold_t	price;

	/* �ե饰 */
	flg_tobacco_t	flg;
} tobacco_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	pipe_kind_t	kind;

	/* �и�Ψ */
	rate_t	rate;

	/* ʿ�ѸĿ� */
	long	ave_n;

	/* ���񥿡���� */
	long	consume_turn;

	/* �Ȥ������μ��� */
	tobacco_kind_t	tobacco_kind;

	/* ���� */
	gold_t	price;

	/* �ե饰 */
	flg_pipe_t	flg;
} pipe_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	rare_goods_kind_t	kind;
} rare_goods_tab_t;

typedef struct {
	/* ̾�� */
	char	*name;
	n_msg_t	name_n;

	/* ���� */
	coin_kind_t	kind;

	/* �ޥ��ʡ��δ� */
	char	mnr;

	/* �и�Ψ */
	rate_t	rate;

	/* ���� */
	long	value;
} coin_tab_t;

/* �ͷ��ǽ��Υ */

typedef struct {
	/* ���� */
	item_kind_t	kind;

	/* Ⱦ�� */
	long	r;
} range_tab_t;

/* ��ư�ޡ������륢���ƥ� */

typedef struct {
	char	mjr, mnr;
	bool_t	flg_ena;
} auto_mark_appoint_item_t;

typedef struct {
	stick_kind_t	kind;
	spell_kind_t	spell_kind;
} item_kind_dat_stick_t;

typedef struct {
	tobacco_kind_t	kind;
	tobacco_brand_t	brand;
} item_kind_dat_tobacco_t;

typedef struct {
	wpn_kind_t	wpn;
	armor_kind_t	armor;
	potion_kind_t	potion;
	scroll_kind_t	scroll;
	item_kind_dat_stick_t	stick;
	ring_kind_t	ring;
	amulet_kind_t	amulet;
	necklace_kind_t	necklace;
	inst_kind_t	inst;
	anthology_kind_t	anthology;
	light_kind_t	light;
	wish_level_t	wish_level;
	food_kind_t	food;
	item_kind_dat_tobacco_t	tobacco;
	pipe_kind_t	pipe;
	rare_goods_kind_t	rare_goods;
	coin_kind_t	coin;

	mnstr_kind_t	mnstr;
} item_kind_dat_t;

/***************************************************************/

/* �����ƥ� */

typedef struct item_t {
	/* ��� */
	struct item_t	*next, *prev;
	/* ��ʬ�ե饰 */
	bool_t	flg_garbage;

	/* ̾�� */
	char	name[ITEM_NAME_MAX_BYTE + 1];
	/* ����̾ */
	char	art_name[ITEM_ART_NAME_MAX_BYTE + 1];
	/* ��̾ */
	char	alias[ITEM_NAME_MAX_BYTE + 1];

	/* ���� */
	item_kind_t	kind;

	/* ������������ */
	equip_kind_t	equip_kind;

	/* �� */
	char	mjr, mnr;

	/* ��ɸ */
	long	x, y;

	/* �Ŀ����߸˿� */
	long	n, stock;

	/* �ե饰 */
	flg_item_t	flg;

	/* ������ */
	modifier_t	modifier;

	/* �ơ��֥� */
	union {
		wpn_tab_t	*wpn;
		armor_tab_t	*armor;
		potion_tab_t	*potion;
		scroll_tab_t	*scroll;
		stick_tab_t	*stick;
		acce_tab_t	*acce;
		inst_tab_t	*inst;
		anthology_tab_t	*anthology;
		light_tab_t	*light;
		food_tab_t	*food;
		tobacco_tab_t	*tobacco;
		pipe_tab_t	*pipe;
		rare_goods_tab_t	*rare_goods;
		coin_tab_t	*coin;
	} tab;

	/* �����̥ǡ��� */
	union {
		wpn_t	wpn;
		armor_t	armor;
		potion_t	potion;
		scroll_t	scroll;
		stick_t	stick;
		acce_t	acce;
		inst_t	inst;
		anthology_t	anthology;
		light_t	light;
		food_t	food;
		chest_t	chest;
		tobacco_t	tobacco;
		pipe_t	pipe;
		disposal_t	disposal;
		rare_goods_t	rare_goods;
		bone_t	bone;
		coin_t	coin;
	} dat;
} item_t;

#endif	/* ITEM_H */
