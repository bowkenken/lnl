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
* $Id: item.h,v 1.107 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	ITEM_H
#define	ITEM_H

/***************************************************************
* アイテム
***************************************************************/

#include	"spell.h"
#include	"trap.h"

#include	"item-kind.h"
#include	"item-randm-art.h"

/**/

/* メンバーの持てる最大数 */
#define	MBR_ITEM_MAX_N	16
/* 迷宮に落ちている平均数 */
#define	DUN_ITEM_AVE_N	16
/* 罠部屋に落ちている平均数 */
#define	DUN_ITEM_TRAP_ROOM_AVE_N	4

/* アイテム名の最大文字数 */
#define	ITEM_NAME_MAX_LEN	60
#define	ITEM_NAME_MAX_BYTE	\
	(ITEM_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* 商品のアイテム名の最大文字数 */
#define	ITEM_ART_NAME_MAX_LEN	(ITEM_NAME_MAX_LEN + 16)
#define	ITEM_ART_NAME_MAX_BYTE	\
	(ITEM_ART_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* 巻物のタイトルの最大音節数 */
#define	SCROLL_TTL_SYLLABLE_MAX_N	4
/* 巻物のタイトルの最大文字数 */
#define	SCROLL_TTL_MAX_LEN	50
#define	SCROLL_TTL_MAX_BYTE	\
	(SCROLL_TTL_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* 釘の平均本数 */
#define	SPIKE_AVE_N	11

/* アイテムを地面に落した時に既に置いてある場所を避ける最大半径 */
#define	PUT_ITEM_R	MAP_MAX_X

/* アイテムを束ねられる最大数 */
#define	BUNDLE_MAX_N	12	/* 通常アイテム */
#define	BUNDLE_SPIKE_MAX_N	99	/* 釘 */
#define	BUNDLE_WPN_MAX_N	99	/* 武器 */

/* アイテムが呪われている率 */
#define	CURSE_ITEM_RATE	((rate_t)30)

/* 宝箱に入っているアイテムの最小数 */
#define	CHEST_HOLD_MIN_N	4
/* 宝箱に入っているアイテムの最大数 */
#define	CHEST_HOLD_MAX_N	8
/* 持ち運べる宝箱の最大数 */
#define	CAN_CARRY_CHEST_MAX_N	1

/* アイテムの顔 */

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

/* 武器の強さ */

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

/* 装備カ所 */

/* 順番を変える場合はセーブ・データも修整する */
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

/* 武器の種類 */

typedef enum {
	WPN_KIND_NULL,
/* ナイフ */
	WPN_KIND_KNIFE,
	WPN_KIND_KRIS_KNIFE,
	WPN_KIND_MAIN_GAUCHE,
	WPN_KIND_SWORD_BREAKER,
	WPN_KIND_KATAR,
	WPN_KIND_JAMADHAR,
	WPN_KIND_KUKRI,
/* ショート・ソード */
	WPN_KIND_SHORT_SWORD,
	WPN_KIND_GLADIUS,
/* ロング・ソード */
	WPN_KIND_LONG_SWORD,
	WPN_KIND_BROAD_SWORD,
	WPN_KIND_BASTARD_SWORD,
	WPN_KIND_CLAYMORE,
	WPN_KIND_GREAT_SWORD,
/* サーベル */
	WPN_KIND_SABRE,
	WPN_KIND_SHAMSHIR,
	WPN_KIND_TALWAR,
	WPN_KIND_FALCHION,
	WPN_KIND_CUTLASS,
	WPN_KIND_SHOTEL,
	WPN_KIND_KATANA,
	WPN_KIND_WAKIZASHI,
/* レイピア */
	WPN_KIND_RAPIER,
	WPN_KIND_ESTOC,
/* ハンド・アックス */
	WPN_KIND_HAND_AXE,
	WPN_KIND_FRANCISCA,
	WPN_KIND_BHUJ,
/* バトル・アックス */
	WPN_KIND_BATTLE_AXE,
	WPN_KIND_BROAD_AXE,
	WPN_KIND_GREAT_AXE,
/* スピア */
	WPN_KIND_SPEAR,
	WPN_KIND_PILUM,
	WPN_KIND_PIKE,
	WPN_KIND_JAVELIN,
	WPN_KIND_TRIDENT,
/* ランス */
	WPN_KIND_LANCE,
	WPN_KIND_LANCE_OF_LONGINUS,
/* フレイル */
	WPN_KIND_LIGHT_FLAIL,
	WPN_KIND_HEAVY_FLAIL,
	WPN_KIND_MORNINGSTAR,
	WPN_KIND_NUNCHAKUS,
/* メイス */
	WPN_KIND_WOODEN_CLUB,
	WPN_KIND_QUARTER_STAFF,
	WPN_KIND_LIGHT_MACE,
	WPN_KIND_HEAVY_MACE,
/* ハンマー */
	WPN_KIND_WAR_HAMMER,
	WPN_KIND_WAR_PICK,
	WPN_KIND_ZAGHNOL,
	WPN_KIND_BEC_DE_CORBIN,
/* グレイブ */
	WPN_KIND_PARTIZAN,
	WPN_KIND_POLEAXE,
	WPN_KIND_GLAIVE,
	WPN_KIND_HALBERD,
	WPN_KIND_CHAUVE_SOURIS,
	WPN_KIND_CORSESCA,
	WPN_KIND_SCYTHE,
	WPN_KIND_FAUCHARD,
	WPN_KIND_GUISARME,
/* ナックル */
	WPN_KIND_BRASS_KNUCKLE,
	WPN_KIND_BAGH_NAKH,
/* 弓 */
	WPN_KIND_SLING,
	WPN_KIND_SHORT_BOW,
	WPN_KIND_LONG_BOW,
	WPN_KIND_COMPOSITE_BOW,
	WPN_KIND_LIGHT_CROSS_BOW,
	WPN_KIND_HEAVY_CROSS_BOW,
	WPN_KIND_BLOW_GUN,
/* 矢 */
	WPN_KIND_STONE,
	WPN_KIND_BULLET,
	WPN_KIND_ARW,
	WPN_KIND_BOLT,
	WPN_KIND_NEEDLE,
/* ダガー */
	WPN_KIND_DAGGER,
	WPN_KIND_DARTS,
	WPN_KIND_SHURIKEN,
	WPN_KIND_BOOMERANG,
/* ロング・ソード(アーティファクト) */
	WPN_KIND_EXCALIBUR,
/**/
	WPN_KIND_MAX_N,
} wpn_kind_t;

/* 弓の種類 */

typedef enum {
	BOW_KIND_NULL,
	BOW_KIND_BOW,
	BOW_KIND_CROSS_BOW,
	BOW_KIND_SLING,
	BOW_KIND_BLOW_GUN,
	BOW_KIND_DAGGER,
	BOW_KIND_MAX_N,
} bow_kind_t;

/* 防具の種類 */

#define	FACE_MNR_ARMOR_SHIELD	's'
#define	FACE_MNR_ARMOR_HEAD	'h'
#define	FACE_MNR_ARMOR_BODY	'b'
#define	FACE_MNR_ARMOR_ARM	'a'
#define	FACE_MNR_ARMOR_FEET	'f'
#define	FACE_MNR_ARMOR_ABOUT_BODY	'm'
typedef enum {
	ARMOR_KIND_NULL,
/* 楯 */
	ARMOR_KIND_BUCKLER_SHIELD,
	ARMOR_KIND_ROUND_SHIELD,
	ARMOR_KIND_KITE_SHIELD,
	ARMOR_KIND_HEATER_SHIELD,
/* 頭に装備 */
	ARMOR_KIND_LEATHER_CAP,
	ARMOR_KIND_METAL_CAP,
	ARMOR_KIND_SALLET,
	ARMOR_KIND_CLOSE_HELMET,
	ARMOR_KIND_SILVER_CROWN,
	ARMOR_KIND_GOLDEN_CROWN,
	ARMOR_KIND_JEWELED_CROWN,
/* 胴体に装備 */
	ARMOR_KIND_ROBE,
	ARMOR_KIND_SOFT_LEATHER_ARMOR,
	ARMOR_KIND_HARD_LEATHER_ARMOR,
	ARMOR_KIND_RING_MAIL,
	ARMOR_KIND_SCALE_MAIL,
	ARMOR_KIND_LAMELLAR_ARMOR,
	ARMOR_KIND_CHAIN_MAIL,
	ARMOR_KIND_PLATE_ARMOR,
/* 腕に装備 */
	ARMOR_KIND_LEATHER_GLOVES,
	ARMOR_KIND_GAUNTLETS,
/* 足に装備 */
	ARMOR_KIND_LEATHER_BOOTS,
	ARMOR_KIND_GREAVE,
/* 背中に装備 */
	ARMOR_KIND_CLOAK,
/* 胴体に装備(アーティファクト) */
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
/* 腕に装備(アーティファクト) */
	ARMOR_KIND_GAUNTLETS_OF_POW_UP_HIT,
	ARMOR_KIND_GAUNTLETS_OF_POW_DOWN_HIT,
	ARMOR_KIND_GAUNTLETS_OF_POW_UP_WPN_CRTCL,
	ARMOR_KIND_GAUNTLETS_OF_POW_DOWN_WPN_CRTCL,
	ARMOR_KIND_GAUNTLETS_OF_POW_UP_DAM,
	ARMOR_KIND_GAUNTLETS_OF_POW_DOWN_DAM,
/* 足に装備(アーティファクト) */
	ARMOR_KIND_SPEED_BOOTS,
	ARMOR_KIND_SLOW_BOOTS,
/**/
	ARMOR_KIND_MAX_N,
} armor_kind_t;

/* 薬の種類 */

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

/* 巻物の種類 */

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

/* 杖の種類 */

typedef enum {
	STICK_KIND_NULL,
	STICK_KIND_WAND,
	STICK_KIND_ROD,
	STICK_KIND_STAFF,
	STICK_KIND_MAX_N,
} stick_kind_t;

/* アクセサリの種類 */

typedef enum {
	ACCE_KIND_NULL,
	ACCE_KIND_RING,
	ACCE_KIND_AMULET,
	ACCE_KIND_NECKLACE,
	ACCE_KIND_MAX_N,
} acce_kind_t;

/* 指輪の種類 */

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

/* 護符の種類 */

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

/* 首輪の種類 */

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

/* 楽器の種類 */

typedef enum {
	INST_KIND_NULL,

	/* STRINGED - 回復 */
	INST_KIND_VIOLIN,
	INST_KIND_VIOLA,
	INST_KIND_CELLO,
	INST_KIND_DOUBLEBASS,
	INST_KIND_HARP,
	INST_KIND_MANDOLIN,
	INST_KIND_BANJO,
	INST_KIND_SITAR,

	/* WOODWIND - 能力値強化 */
	INST_KIND_FLUTE,
	INST_KIND_CLARINET,
	INST_KIND_BASS_CLARINET,
	INST_KIND_PICCOLO,
	INST_KIND_OBOE,
	INST_KIND_BASSOON,
	INST_KIND_SAXOPHONE,

	/* BRASS - 能力値弱体 */
	INST_KIND_TRUMPET,
	INST_KIND_TROMBONE,
	INST_KIND_FLUGELHORN,
	INST_KIND_CORNET,
	INST_KIND_HORN,
	INST_KIND_TUBA,
	INST_KIND_SOUSAPHONE,
	INST_KIND_BUGLE,

	/* PERCUSSION - 状態抵抗 */
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

	/* MISC - 全て */
	INST_KIND_ACCORDION,
	INST_KIND_BAGPIPE,
	INST_KIND_HARMONICA,
	INST_KIND_KAZOO,

	INST_KIND_MAX_N,
} inst_kind_t;

/* 詩集の種類 */

typedef enum {
	ANTHOLOGY_KIND_NULL,
	ANTHOLOGY_KIND_CURE,
	ANTHOLOGY_KIND_STRENGTHEN_ABL,
	ANTHOLOGY_KIND_WEAKEN_ABL,
	ANTHOLOGY_KIND_RESI_STAT,
	ANTHOLOGY_KIND_MAX_N,
} anthology_kind_t;

/* 明かりの種類 */

typedef enum {
	LIGHT_KIND_NULL,
	LIGHT_KIND_TORCH,
	LIGHT_KIND_LANTERN,
	LIGHT_KIND_LAMP,
	LIGHT_KIND_MAX_N,
} light_kind_t;

/* 食料の種類 */

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

/* パイプを使うかどうかのフラグ */

typedef unsigned long	flg_tobacco_t;
#define	FLG_TOBACCO_USE_PIPE	(1 << 0)	/* 使う */
#define	FLG_TOBACCO_CAN_USE_PIPE	(1 << 1)	/* 使う亊も出来る */

/* 煙草の種類 */

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

/* 煙草のブランド */

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

/* パイプのフラグ */

typedef unsigned long	flg_pipe_t;
#define	FLG_PIPE_CONSUMPTION	(1 << 0)	/* 消耗品 */

/* パイプの種類 */

typedef enum {
	PIPE_KIND_NULL,
	PIPE_KIND_PIPE,
	PIPE_KIND_KISEL,
	PIPE_KIND_CIGARET_HOLDER,
	PIPE_KIND_MAX_N,
} pipe_kind_t;

/* 探索アイテムの種類 */

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

/* コインの種類 */

typedef enum {
	COIN_KIND_NULL,
	COIN_KIND_GOLD,
	COIN_KIND_SILVER,
	COIN_KIND_COPPER,
	COIN_KIND_MAX_N,
} coin_kind_t;

/***************************************************************/


typedef struct {
	/* アイテムの材質の名前の番号リストのインデックス */
	n_msg_idx_t	name_idx;

	/* アイテムの材質が既に使われているか */
	bool_t	flg_used;
} ls_identified_t;

/* 武器のフラグ */

typedef unsigned long	flg_wpn_tab_t;

#define	FLG_WPN_TAB_BOW	(1 << 0)	/* 弓 */
#define	FLG_WPN_TAB_ARW	(1 << 1)	/* 矢 */
#define	FLG_WPN_TAB_TWO_HANDED	(1 << 2)	/* 必ず両手持ち */
#define	FLG_WPN_TAB_CAN_TWO_HANDED	(1 << 3)	/* 両手持ち可能 */
#define	FLG_WPN_TAB_RET	(1 << 4)	/* 外れると戻って来る */
#define	FLG_WPN_TAB_BUNDLE	(1 << 5)	/* 束ねられる */
#define	FLG_WPN_TAB_NOT_SPEND	(1 << 6)	/* 消費しない */
/* ブーメラン */
#define	FLG_WPN_TAB_BOOMERANG	\
		(FLG_WPN_TAB_ARW | FLG_WPN_TAB_RET | FLG_WPN_TAB_BUNDLE)
/* 投擲武器 */
#define	FLG_WPN_TAB_THROW	\
		(FLG_WPN_TAB_ARW | FLG_WPN_TAB_NOT_SPEND)

/* アイテムのフラグ */

typedef unsigned long	flg_item_t;

#define	FLG_ITEM_DETECTED	(1 << 0)	/* 発見済 */
#define	FLG_ITEM_IDENTIFIED	(1 << 1)	/* 識別済 */
#define	FLG_ITEM_CURSED	(1 << 2)	/* 呪われている */
#define	FLG_ITEM_PROTECTED	(1 << 3)	/* 防護の魔法がかかっている */

/* 各アイテムのデータ */

typedef struct {
	wpn_kind_t	kind;
	long	add_hit;	/* 攻撃力修正 */
	long	add_crtcl;	/* クリティカル修正 */
	long	add_dam;	/* ダメージ修正 */
	char	slayer;	/* ダメージ倍加 (互換性維持のための古い実装) */
	wpn_randm_art_t	randm_art[WPN_RANDM_ART_LS_MAX_N + 1];
	flg_wpn_tab_t	flg;	/* フラグ */
} wpn_t;

typedef struct {
	armor_kind_t	kind;
	long	add_def;	/* 防御力修正 */
	long	add_crtcl;	/* クリティカル修正 */
	long	add_ac;	/* アーマ・クラス修正 */
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
	inst_kind_t	kind;	/* 楽器の種類 */
	bool_t	flg_limit;	/* 呪歌の対象を限定出来るか */
	spell_kind_t	spell_kind;	/* 追加で重ね掛けされる呪歌 */
} inst_t;

typedef struct {
	anthology_kind_t	kind;	/* 詩集の種類 */
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
	struct item_t	*contents;	/* 中味のリスト */
	long	ref;	/* 参照数 */
	trap_t	*trap;	/* 罠 */
} chest_t;

typedef struct {
	tobacco_kind_t	kind;
	tobacco_brand_t	brand;	/* ブランド */
	long	turn;	/* 吸い残りターン数 */
} tobacco_t;

typedef struct {
	pipe_kind_t	kind;
	long	turn;	/* 吸い残りターン数 */
	long	consume_turn;	/* 消費ターン数 */
} pipe_t;

typedef struct {
	long	n, max_n;
} disposal_t;

typedef struct {
	rare_goods_kind_t	kind;
	mnstr_kind_t	mnstr_kind;	/* 持っているモンスターの種類 */
} rare_goods_t;

typedef struct {
	mnstr_tab_t	*mnstr_tab;
	long	dun_lev;
} bone_t;

typedef struct {
	coin_kind_t	kind;
} coin_t;

/***************************************************************/
/* テーブル */

typedef struct {
	/* 識別前の名前 */
	char	*name;
	n_msg_t	name_n;
	/* 識別後の名前 */
	char	*i_name;
	n_msg_t	i_name_n;

	/* 種類 */
	wpn_kind_t	kind;

	/* 出現率 */
	rate_t	rate;
	/* 平均個数 */
	long	ave_n;

	/* 値段の修正率 */
	rate_t	rate_price;
	/* 値段の修正 */
	long	add_price;

	/* マイナーの顔 */
	char	mnr;

	/* 出現階 */
	long	min_lev, max_lev, sgn_lev;

	/* 弓の種類 */
	bow_kind_t	bow_kind;

	/* フラグ */
	flg_wpn_tab_t	flg;
	/* 装備時の能力制限無しのフラグ */
	bool_t	flg_abl[ABL_KIND_MAX_N];

	/* 攻撃のデータ */
	attack_t	attack[WPN_ATTACK_MAX_N + 1];
} wpn_tab_t;

typedef struct {
	/* 識別前の名前 */
	char	*name;
	n_msg_t	name_n;
	/* 識別後の名前 */
	char	*i_name;
	n_msg_t	i_name_n;

	/* 種類 */
	armor_kind_t	kind;

	/* 値段の修正率 */
	rate_t	rate_price;
	/* 値段の修正 */
	long	add_price;

	/* マイナーの顔 */
	char	mnr;

	/* 装備する部位 */
	equip_kind_t	equip_kind;

	/* 耐性値の修正 */
	rate_t	up_resi[RESI_KIND_MAX_N];
	/* 防御力 */
	rate_t	def, crtcl, ac;

	/* 出現階 */
	long	min_lev, max_lev, sgn_lev;

	/* 出現率 */
	rate_t	rate;

	/* 装備時の能力制限無しのフラグ */
	bool_t	flg_abl[ABL_KIND_MAX_N];

	/* 呪われている率 */
	rate_t	rate_curse;

	/* 保護されているフラグ */
	bool_t	flg_protected;

	/* 能力値修正データ */
	modifier_t	modifier;
} armor_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	potion_kind_t	kind;

	/* 出現率 */
	rate_t	rate;

	/* 出現階 */
	long	min_lev, max_lev, sgn_lev;

	/* 値段 */
	gold_t	price;

	/* 色名 */
	char	*color;
	n_msg_t	color_n;

	/* 識別済フラグ */
	bool_t	flg_identified;
	/* デフォルトの色を使わないフラグ */
	bool_t	flg_change_color;
} potion_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	scroll_kind_t	kind;

	/* 出現率 */
	rate_t	rate;

	/* 出現階 */
	long	min_lev, max_lev, sgn_lev;

	/* 値段 */
	gold_t	price;

	/* タイトルの音節数 */
	long	ttl_n;

	/* タイトルの音節リスト */
	n_msg_idx_t	ttl_idx[SCROLL_TTL_SYLLABLE_MAX_N + 1];

	/* タイトル */
	char	ttl[SCROLL_TTL_MAX_BYTE + 1];

	/* 識別済フラグ */
	bool_t	flg_identified;
} scroll_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 出現率 */
	rate_t	rate;

	/* 使用可能回数 */
	long	use_n;

	/* 種類 */
	stick_kind_t	kind;

	/* 使える魔法の種類 */
	spell_kind_t	spell_kind;

	/* 出現階 */
	long	min_lev, max_lev, sgn_lev;

	/* 値段 */
	gold_t	price;

	/* 材質名 */
	char	*material;
	n_msg_t	material_n;

	/* 識別済フラグ */
	bool_t	flg_identified;
} stick_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	acce_kind_t	kind;
	/* 指輪の種類 */
	ring_kind_t	ring_kind;
	/* 護符の種類 */
	amulet_kind_t	amulet_kind;
	/* 首輪の種類 */
	necklace_kind_t	necklace_kind;

	/* 出現率 */
	rate_t	rate;

	/* 出現階 */
	long	min_lev, max_lev, sgn_lev;

	/* 値段 */
	gold_t	price;

	/* マイナーの顔 */
	char	mnr;

	/* 装備する部位 */
	equip_kind_t	equip_kind;

	/* 材質名 */
	char	*material;
	n_msg_t	material_n;

	/* 識別済フラグ */
	bool_t	flg_identified;

	/* 呪われている率 */
	rate_t	rate_curse;

	/* 能力値修正データ */
	modifier_t	modifier;
} acce_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	inst_kind_t	kind;

	/* マイナーの顔 */
	char	mnr;

	/* 呪われている率 */
	rate_t	rate_curse;
} inst_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	anthology_kind_t	kind;
} anthology_tab_t;

typedef struct {
	/* 識別前の名前 */
	char	*name;
	n_msg_t	name_n;
	/* 識別後の名前 */
	char	*i_name;
	n_msg_t	i_name_n;

	/* 種類 */
	light_kind_t	kind;

	/* 出現率 */
	rate_t	rate;

	/* 出現階 */
	long	min_lev, max_lev, sgn_lev;

	/* 値段 */
	gold_t	base_price, fill_price;

	/* 使用可能ターン数 */
	long	max_turn;
	/* 補給可能フラグ */
	bool_t	flg_fill;

	/* 魔法のランプの魔神の種類 */
	wish_level_t	wish_level;
	/* 魔法のランプの最大使用回数 */
	long	wish_max_n;
} light_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	food_kind_t	kind;

	/* 出現率 */
	rate_t	rate;

	/* 平均個数 */
	long	ave_n;

	/* 値段 */
	gold_t	price;

	/* 満腹度 */
	rate_t	fill_rate;
} food_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	tobacco_kind_t	kind;
	/* ブランド名 */
	char	*brand_name;
	n_msg_t	brand_name_n;
	/* ブランド */
	tobacco_brand_t	brand;

	/* 出現率 */
	rate_t	rate;

	/* 平均個数 */
	long	ave_n;

	/* ターン数 */
	long	turn;

	/* 値段 */
	gold_t	price;

	/* フラグ */
	flg_tobacco_t	flg;
} tobacco_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	pipe_kind_t	kind;

	/* 出現率 */
	rate_t	rate;

	/* 平均個数 */
	long	ave_n;

	/* 消費ターン数 */
	long	consume_turn;

	/* 使える煙草の種類 */
	tobacco_kind_t	tobacco_kind;

	/* 値段 */
	gold_t	price;

	/* フラグ */
	flg_pipe_t	flg;
} pipe_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	rare_goods_kind_t	kind;
} rare_goods_tab_t;

typedef struct {
	/* 名前 */
	char	*name;
	n_msg_t	name_n;

	/* 種類 */
	coin_kind_t	kind;

	/* マイナーの顔 */
	char	mnr;

	/* 出現率 */
	rate_t	rate;

	/* 価値 */
	long	value;
} coin_tab_t;

/* 射撃可能距離 */

typedef struct {
	/* 種類 */
	item_kind_t	kind;

	/* 半径 */
	long	r;
} range_tab_t;

/* 自動マークするアイテム */

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

/* アイテム */

typedef struct item_t {
	/* リンク */
	struct item_t	*next, *prev;
	/* 処分フラグ */
	bool_t	flg_garbage;

	/* 名前 */
	char	name[ITEM_NAME_MAX_BYTE + 1];
	/* 商品名 */
	char	art_name[ITEM_ART_NAME_MAX_BYTE + 1];
	/* 別名 */
	char	alias[ITEM_NAME_MAX_BYTE + 1];

	/* 種類 */
	item_kind_t	kind;

	/* 装備する部位 */
	equip_kind_t	equip_kind;

	/* 顔 */
	char	mjr, mnr;

	/* 座標 */
	long	x, y;

	/* 個数、在庫数 */
	long	n, stock;

	/* フラグ */
	flg_item_t	flg;

	/* 修正値 */
	modifier_t	modifier;

	/* テーブル */
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

	/* 種類別データ */
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
