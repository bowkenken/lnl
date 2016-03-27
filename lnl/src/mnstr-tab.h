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
* $Id: mnstr-tab.h,v 1.20 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MNSTR_TAB_H
#define	MNSTR_TAB_H

#include	"party.h"
#include	"fight.h"
#include	"mnstr-act-prot.h"

/***************************************************************
* モンスターのデータ・テーブル
***************************************************************/

/* ジャイガンティック・センティピードの体の長さ */
#define	GIGANTIC_CENTIPEDE_LINK_N	8

/***************************************************************
* NPC のリスト
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
* モンスター・データ
***************************************************************/

mnstr_tab_t	mnstr_tab[] = {
#include	"mnstr-gen-tab.h"
};

#if	0
typedef struct {
	/* モンスターの種類 */
	mnstr_kind_t	kind;

	/* 発生する階の最小・最大の差分 */
	long	add_lev, range_lev;

	/* 発生する階の最小・最大 */
	/* 初期化関数で自動計算する */
	long	min_lev, max_lev;
} mnstr_lev_tab_t;
#endif

/***************************************************************
* 中ボスのリスト
***************************************************************/

mnstr_lev_tab_t	mnstr_boss_lev_tab[] = {
	{ MNSTR_KIND_HIGH_RE_HOO,	/* 巨人 */
		+0, +1, 10, 10, },
	{ MNSTR_KIND_GREAT_MINOTAUR,	/* 半人 */
		+0, +1, 20, 20, },
	{ MNSTR_KIND_BILLION_ELEMENTAL,	/* 精霊 */
		+0, +1, 30, 30, },
	{ MNSTR_KIND_CYBERN,	/* 魔法生物 */
		+0, +1, 40, 40, },
	{ MNSTR_KIND_GIGANTIC_CENTIPEDE,	/* 巨大生物 */
		+0, +1, 50, 50, },
	{ MNSTR_KIND_MEDUSA_ZOMBIE,	/* 半人 */
		+0, +1, 60, 60, },
	{ MNSTR_KIND_BLACK_UNICORN,	/* 魔獣 */
		+0, +1, 70, 70, },
	{ MNSTR_KIND_VAMPIRE_LORD,	/* アンデッド */
		+0, +1, 80, 80, },
	{ MNSTR_KIND_RELATIVISTIC_DAEMON,	/* 悪魔 */
		+0, +1, 90, 90, },
	{ MNSTR_KIND_ETERNAL_DRAGON,	/* エンシェント・ドラゴン */
		+0, +1, 100, 100, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};

/***************************************************************
* ラスボスのリスト
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
* モンスターの出現順リスト
***************************************************************/

#if	FLG_DIVIDE_MNSTR_LEV_TAB_STAGE

mnstr_lev_tab_t	mnstr_lev_tab_stage_town[] = {
	{ MNSTR_KIND_FIGHTER,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_MONK,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_HUNTER,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_THIEF,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_WIZARD,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_SUMMONER,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_PRIEST,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_SHAMAN,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_BARD,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_NINJA,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_BISHOP,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_FARMER,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_CRAFTSMAN,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_MERCHANT,	/* 人間 */
		+0, +0, 0, 0, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};

mnstr_lev_tab_t	mnstr_lev_tab_stage_1[] = {
	{ MNSTR_KIND_GIANT_BAT,	/* 動物 */
		+0, +0, 1, 3, },
	{ MNSTR_KIND_GIANT_SNAKE,	/* 動物 */
		+0, +0, 1, 3, },
	{ MNSTR_KIND_GIANT_RAT,	/* 動物 */
		+0, +0, 2, 4, },
	{ MNSTR_KIND_GIANT_CENTIPEDE,	/* 昆虫 */
		+0, +0, 3, 5, },
	{ MNSTR_KIND_CAT,	/* 動物 */
		+0, +0, 3, 5, },
	{ MNSTR_KIND_KOBOLD,	/* 妖魔 */
		+0, +0, 4, 6, },
	{ MNSTR_KIND_VIPER_SNAKE,	/* 動物 */
		+0, +0, 5, 7, },
	{ MNSTR_KIND_DOG,	/* 動物 */
		+0, +0, 5, 7, },
	{ MNSTR_KIND_GOBLIN,	/* 妖魔 */
		+0, +0, 6, 8, },
	{ MNSTR_KIND_GIANT_BEE,	/* 昆虫 */
		+0, +0, 7, 9, },
	{ MNSTR_KIND_PYON_PYON,	/* 幻獣 */
		+0, +0, 7, 9, },
	{ MNSTR_KIND_GREMLIN,	/* 妖魔 */
		+0, +0, 8, 10, },
	{ MNSTR_KIND_HOBGOBLIN,	/* 妖魔 */
		+0, +0, 9, 11, },
	{ MNSTR_KIND_WOLF,	/* 動物 */
		+0, +0, 9, 11, },
	{ MNSTR_KIND_GIANT_SCORPION,	/* 昆虫 */
		+0, +0, 10, 12, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_HIGH_RE_HOO, */	/* 巨人 */

mnstr_lev_tab_t	mnstr_lev_tab_stage_2[] = {
	{ MNSTR_KIND_SKELETON,	/* アンデッド */
		+0, +0, 11, 13, },
	{ MNSTR_KIND_ORK,	/* 妖魔 */
		+0, +0, 12, 14, },
	{ MNSTR_KIND_VENUS_FLY_TRAP,	/* 植物 */
		+0, +0, 13, 15, },
	{ MNSTR_KIND_ZOMBIE,	/* アンデッド */
		+0, +0, 14, 16, },
	{ MNSTR_KIND_OGRE,	/* 巨人 */
		+0, +0, 15, 17, },
	{ MNSTR_KIND_GIANT_SPIDER,	/* 昆虫 */
		+0, +0, 16, 18, },
	{ MNSTR_KIND_GNOLL,	/* 妖魔 */
		+0, +0, 17, 19, },
	{ MNSTR_KIND_YETI,	/* 巨人 */
		+0, +0, 18, 20, },
	{ MNSTR_KIND_LEPRECHAUN,	/* 妖精 */
		+0, +0, 19, 21, },
	{ MNSTR_KIND_HARPY,	/* 半人 */
		+0, +0, 20, 22, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_GREAT_MINOTAUR, */	/* 半人 */

mnstr_lev_tab_t	mnstr_lev_tab_stage_3[] = {
	{ MNSTR_KIND_IMP,	/* 悪魔 */
		+0, +0, 21, 23, },
	{ MNSTR_KIND_RUST_MONSTER,	/* 魔獣 */
		+0, +0, 22, 24, },
	{ MNSTR_KIND_GHOUL,	/* アンデッド */
		+0, +0, 23, 25, },
	{ MNSTR_KIND_TROLL,	/* 巨人 */
		+0, +0, 24, 26, },
	{ MNSTR_KIND_SLIME,	/* 植物 */
		+0, +0, 25, 27, },
	{ MNSTR_KIND_HIPPOGRIFF,	/* 合成獣 */
		+0, +0, 26, 28, },
	{ MNSTR_KIND_JACK_O_LANTERN,	/* 悪魔 */
		+0, +0, 27, 29, },
	{ MNSTR_KIND_INVISIBLE_STALKER,	/* 魔法生物 */
		+0, +0, 28, 30, },
	{ MNSTR_KIND_GIANT_ANT,	/* 昆虫 */
		+0, +0, 29, 31, },
	{ MNSTR_KIND_GRIFFON,	/* 合成獣 */
		+0, +0, 30, 32, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_BILLION_ELEMENTAL, */	/* 精霊 */

mnstr_lev_tab_t	mnstr_lev_tab_stage_4[] = {
	{ MNSTR_KIND_GHOST,	/* アンデッド */
		+0, +0, 31, 33, },
	{ MNSTR_KIND_FIRE_ELEMENTAL,	/* 精霊 */
		+0, +0, 32, 34, },
	{ MNSTR_KIND_MORMIN_TROLL,	/* 巨人 */
		+0, +0, 33, 35, },
	{ MNSTR_KIND_WATER_ELEMENTAL,	/* 精霊 */
		+0, +0, 34, 36, },
	{ MNSTR_KIND_ACID_FLY,	/* 昆虫 */
		+0, +0, 35, 37, },
	{ MNSTR_KIND_EARTH_ELEMENTAL,	/* 精霊 */
		+0, +0, 36, 38, },
	{ MNSTR_KIND_SPORE,	/* 植物 */
		+0, +0, 37, 39, },
	{ MNSTR_KIND_AIR_ELEMENTAL,	/* 精霊 */
		+0, +0, 38, 40, },
	{ MNSTR_KIND_INCUBUS,	/* 妖魔 */
		+0, +0, 39, 41, },
	{ MNSTR_KIND_WEREWOLF,	/* 半人 */
		+0, +0, 40, 42, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_CYBERN, */	/* 魔法生物 */

mnstr_lev_tab_t	mnstr_lev_tab_stage_5[] = {
	{ MNSTR_KIND_WOOD_GOLEM,	/* 魔法生物 */
		+0, +0, 41, 43, },
	{ MNSTR_KIND_ANDRO_SCORPION,	/* 半人 */
		+0, +0, 42, 44, },
	{ MNSTR_KIND_BONE_GOLEM,	/* 魔法生物 */
		+0, +0, 43, 45, },
	{ MNSTR_KIND_GIANT_BEETLE,	/* 昆虫 */
		+0, +0, 44, 46, },
	{ MNSTR_KIND_FLESH_GOLEM,	/* 魔法生物 */
		+0, +0, 45, 47, },
	{ MNSTR_KIND_SUCCUBUS,	/* 妖魔 */
		+0, +0, 46, 48, },
	{ MNSTR_KIND_STONE_GOLEM,	/* 魔法生物 */
		+0, +0, 47, 49, },
	{ MNSTR_KIND_POLTERGEIST,	/* アンデッド */
		+0, +0, 48, 50, },
	{ MNSTR_KIND_IRON_GOLEM,	/* 魔法生物 */
		+0, +0, 49, 51, },
	{ MNSTR_KIND_LAMIA,	/* 半人 */
		+0, +0, 50, 52, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_GIGANTIC_CENTIPEDE, */	/* 巨大生物 */

mnstr_lev_tab_t	mnstr_lev_tab_stage_6[] = {
	{ MNSTR_KIND_FIRE_GIANT,	/* 巨人 */
		+0, +0, 51, 53, },
	{ MNSTR_KIND_WILL_O_WISP,	/* 精霊 */
		+0, +0, 52, 54, },
	{ MNSTR_KIND_SHADE,	/* 精霊 */
		+0, +0, 53, 55, },
	{ MNSTR_KIND_WIGHT,	/* アンデッド */
		+0, +0, 54, 56, },
	{ MNSTR_KIND_CENTAUR,	/* 半人 */
		+0, +0, 55, 57, },
	{ MNSTR_KIND_FROST_GIANT,	/* 巨人 */
		+0, +0, 56, 58, },
	{ MNSTR_KIND_MANTICORE,	/* 合成獣 */
		+0, +0, 57, 59, },
	{ MNSTR_KIND_GAS_CLOUD,	/* 魔法生物 */
		+0, +0, 58, 60, },
	{ MNSTR_KIND_BIRD_MAN,	/* 半人 */
		+0, +0, 59, 61, },
	{ MNSTR_KIND_WYVERN,	/* 魔獣 */
		+0, +0, 60, 62, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_MEDUSA_ZOMBIE, */	/* 半人 */

mnstr_lev_tab_t	mnstr_lev_tab_stage_7[] = {
	{ MNSTR_KIND_SALAMANDER,	/* 精霊 */
		+0, +0, 61, 63, },
	{ MNSTR_KIND_CLOUD_GIANT,	/* 巨人 */
		+0, +0, 62, 64, },
	{ MNSTR_KIND_UNDINE,	/* 精霊 */
		+0, +0, 63, 65, },
	{ MNSTR_KIND_MUMMY,	/* アンデッド */
		+0, +0, 64, 66, },
	{ MNSTR_KIND_GNOME,	/* 精霊 */
		+0, +0, 65, 67, },
	{ MNSTR_KIND_UNICORN,	/* 幻獣 */
		+0, +0, 66, 68, },
	{ MNSTR_KIND_SYLPH,	/* 精霊 */
		+0, +0, 67, 69, },
	{ MNSTR_KIND_GARGOYLE,	/* 魔法生物 */
		+0, +0, 68, 70, },
	{ MNSTR_KIND_MINOTAUR,	/* 半人 */
		+0, +0, 69, 71, },
	{ MNSTR_KIND_CHIMERA,	/* 合成獣 */
		+0, +0, 70, 72, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_BLACK_UNICORN, */	/* 魔獣 */

mnstr_lev_tab_t	mnstr_lev_tab_stage_8[] = {
	{ MNSTR_KIND_M_RED_DRAGON,	/* --マイナー・ドラゴン */
		+0, +0, 71, 73, },
	{ MNSTR_KIND_M_BLUE_DRAGON,	/* --マイナー・ドラゴン */
		+0, +0, 72, 74, },
	{ MNSTR_KIND_M_YELLOW_DRAGON,	/* --マイナー・ドラゴン */
		+0, +0, 73, 75, },
	{ MNSTR_KIND_M_GREEN_DRAGON,	/* --マイナー・ドラゴン */
		+0, +0, 74, 76, },
	{ MNSTR_KIND_M_WHITE_DRAGON,	/* --マイナー・ドラゴン */
		+0, +0, 75, 77, },
	{ MNSTR_KIND_M_BLACK_DRAGON,	/* --マイナー・ドラゴン */
		+0, +0, 76, 78, },
	{ MNSTR_KIND_M_COPPER_DRAGON,	/* --マイナー・ドラゴン */
		+0, +0, 77, 79, },
	{ MNSTR_KIND_M_SILVER_DRAGON,	/* --マイナー・ドラゴン */
		+0, +0, 78, 80, },
	{ MNSTR_KIND_M_GOLD_DRAGON,	/* --マイナー・ドラゴン */
		+0, +0, 79, 81, },
	{ MNSTR_KIND_MOUNTAIN_GIANT,	/* 巨人 */
		+0, +0, 80, 82, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_VAMPIRE_LORD, */	/* アンデッド */

mnstr_lev_tab_t	mnstr_lev_tab_stage_9[] = {
	{ MNSTR_KIND_MIMIC,	/* 魔法生物 */
		+0, +0, 81, 83, },
	{ MNSTR_KIND_BANSHEE,	/* アンデッド */
		+0, +0, 82, 84, },
	{ MNSTR_KIND_CYCLOPS,	/* 巨人 */
		+0, +0, 83, 85, },
	{ MNSTR_KIND_DURAHAN,	/* アンデッド */
		+0, +0, 84, 86, },
	{ MNSTR_KIND_MEDUSA,	/* 半人 */
		+0, +0, 85, 87, },
	{ MNSTR_KIND_WRAITH,	/* アンデッド */
		+0, +0, 86, 88, },
	{ MNSTR_KIND_HYDRA,	/* 魔獣 */
		+0, +0, 87, 89, },
	{ MNSTR_KIND_COCKATRICE,	/* 魔獣 */
		+0, +0, 88, 90, },
	{ MNSTR_KIND_CERBERUS,	/* 魔獣 */
		+0, +0, 89, 91, },
	{ MNSTR_KIND_LESSER_DAEMON,	/* 悪魔 */
		+0, +0, 90, 92, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_RELATIVISTIC_DAEMON, */	/* 悪魔 */

mnstr_lev_tab_t	mnstr_lev_tab_stage_10[] = {
	{ MNSTR_KIND_A_RED_DRAGON,	/* エンシェント・ドラゴン */
		+0, +0, 91, 93, },
	{ MNSTR_KIND_VAMPIRE,	/* アンデッド */
		+0, +0, 91, 93, },
	{ MNSTR_KIND_A_BLUE_DRAGON,	/* エンシェント・ドラゴン */
		+0, +0, 92, 94, },
	{ MNSTR_KIND_GORGON,	/* 魔獣 */
		+0, +0, 92, 94, },
	{ MNSTR_KIND_A_YELLOW_DRAGON,	/* エンシェント・ドラゴン */
		+0, +0, 93, 95, },
	{ MNSTR_KIND_EFREET,	/* 妖魔 */
		+0, +0, 93, 95, },
	{ MNSTR_KIND_A_GREEN_DRAGON,	/* エンシェント・ドラゴン */
		+0, +0, 94, 96, },
	{ MNSTR_KIND_DJINNI,	/* 妖魔 */
		+0, +0, 94, 96, },
	{ MNSTR_KIND_A_WHITE_DRAGON,	/* エンシェント・ドラゴン */
		+0, +0, 95, 97, },
	{ MNSTR_KIND_BASILISK,	/* 魔獣 */
		+0, +0, 95, 97, },
	{ MNSTR_KIND_A_BLACK_DRAGON,	/* エンシェント・ドラゴン */
		+0, +0, 96, 98, },
	{ MNSTR_KIND_HELLHOUND,	/* 魔獣 */
		+0, +0, 96, 98, },
	{ MNSTR_KIND_A_COPPER_DRAGON,	/* エンシェント・ドラゴン */
		+0, +0, 97, 99, },
	{ MNSTR_KIND_SPIRIT,	/* アンデッド */
		+0, +0, 97, 99, },
	{ MNSTR_KIND_A_SILVER_DRAGON,	/* エンシェント・ドラゴン */
		+0, +0, 98, 100, },
	{ MNSTR_KIND_GREATER_DAEMON,	/* 悪魔 */
		+0, +0, 98, 100, },
	{ MNSTR_KIND_A_GOLD_DRAGON,	/* エンシェント・ドラゴン */
		+0, +0, 99, 100, },
	{ MNSTR_KIND_PHOENIX,	/* 幻獣 */
		+0, +0, 100, 100, },
	{ MNSTR_KIND_NULL,
		+0, +0, 0, 0, },
};
/* BOSS MNSTR_KIND_ETERNAL_DRAGON, */	/* エンシェント・ドラゴン */

mnstr_lev_tab_t	mnstr_lev_tab[MNSTR_KIND_MAX_N + 1];

#else

mnstr_lev_tab_t	mnstr_lev_tab[] = {
	{ MNSTR_KIND_FIGHTER,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_MONK,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_HUNTER,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_THIEF,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_WIZARD,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_SUMMONER,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_PRIEST,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_SHAMAN,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_BARD,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_NINJA,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_BISHOP,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_FARMER,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_CRAFTSMAN,	/* 人間 */
		+0, +1, },
	{ MNSTR_KIND_MERCHANT,	/* 人間 */
		+0, +1, },
	/**/

	{ MNSTR_KIND_GIANT_BAT,	/* 動物 */
		+1, +1, },
	{ MNSTR_KIND_GIANT_SNAKE,	/* 動物 */
		+0, +1, },
	{ MNSTR_KIND_GIANT_RAT,	/* 動物 */
		+1, +1, },
	{ MNSTR_KIND_GIANT_CENTIPEDE,	/* 昆虫 */
		+0, +1, },
	{ MNSTR_KIND_KOBOLD,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_VIPER_SNAKE,	/* 動物 */
		+0, +1, },
	{ MNSTR_KIND_GOBLIN,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_GIANT_BEE,	/* 昆虫 */
		+1, +5, },
	{ MNSTR_KIND_GREMLIN,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_HOBGOBLIN,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_CAT,	/* 動物 */
		+0, +1, },
	{ MNSTR_KIND_DOG,	/* 動物 */
		+0, +1, },
	{ MNSTR_KIND_WOLF,	/* 動物 */
		+0, +1, },
	{ MNSTR_KIND_PYON_PYON,	/* 幻獣 */
		+0, +1, },
	{ MNSTR_KIND_SKELETON,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_ORK,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_VENUS_FLY_TRAP,	/* 植物 */
		+1, +5, },
	{ MNSTR_KIND_GIANT_SCORPION,	/* 昆虫 */
		+1, +5, },
	{ MNSTR_KIND_ZOMBIE,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_YETI,	/* 巨人 */
		+1, +5, },
	{ MNSTR_KIND_RUST_MONSTER,	/* 魔獣 */
		+1, +5, },
	{ MNSTR_KIND_GNOLL,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_GIANT_ANT,	/* 昆虫 */
		+1, +5, },
	{ MNSTR_KIND_OGRE,	/* 巨人 */
		+1, +5, },
	{ MNSTR_KIND_HARPY,	/* 半人 */
		+1, +5, },
	{ MNSTR_KIND_LEPRECHAUN,	/* 妖精 */
		+1, +5, },
	{ MNSTR_KIND_GHOUL,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_GIANT_SPIDER,	/* 昆虫 */
		+1, +5, },
	{ MNSTR_KIND_SLIME,	/* 植物 */
		+1, +5, },
	{ MNSTR_KIND_IMP,	/* 悪魔 */
		+1, +5, },
	{ MNSTR_KIND_TROLL,	/* 巨人 */
		+1, +5, },
	{ MNSTR_KIND_INVISIBLE_STALKER,	/* 魔法生物 */
		+1, +5, },
	{ MNSTR_KIND_MORMIN_TROLL,	/* 巨人 */
		+1, +5, },
	{ MNSTR_KIND_POLTERGEIST,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_ACID_FLY,	/* 昆虫 */
		+1, +5, },
	{ MNSTR_KIND_FIRE_ELEMENTAL,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_HIPPOGRIFF,	/* 合成獣 */
		+1, +5, },
	{ MNSTR_KIND_WATER_ELEMENTAL,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_GIANT_BEETLE,	/* 昆虫 */
		+1, +5, },
	{ MNSTR_KIND_JACK_O_LANTERN,	/* 悪魔 */
		+1, +5, },
	{ MNSTR_KIND_GHOST,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_WOOD_GOLEM,	/* 魔法生物 */
		+1, +5, },
	{ MNSTR_KIND_GRIFFON,	/* 合成獣 */
		+1, +5, },
	{ MNSTR_KIND_BONE_GOLEM,	/* 魔法生物 */
		+1, +5, },
	{ MNSTR_KIND_INCUBUS,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_SPORE,	/* 植物 */
		+1, +5, },
	{ MNSTR_KIND_ANDRO_SCORPION,	/* 半人 */
		+1, +5, },
	{ MNSTR_KIND_EARTH_ELEMENTAL,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_AIR_ELEMENTAL,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_LAMIA,	/* 半人 */
		+1, +5, },
	{ MNSTR_KIND_CENTAUR,	/* 半人 */
		+1, +5, },
	{ MNSTR_KIND_WIGHT,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_FLESH_GOLEM,	/* 魔法生物 */
		+1, +5, },
	{ MNSTR_KIND_BIRD_MAN,	/* 半人 */
		+1, +5, },
	{ MNSTR_KIND_SUCCUBUS,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_MANTICORE,	/* 合成獣 */
		+1, +5, },
	{ MNSTR_KIND_WEREWOLF,	/* 半人 */
		+1, +5, },
	{ MNSTR_KIND_WILL_O_WISP,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_GAS_CLOUD,	/* 魔法生物 */
		+1, +5, },
	{ MNSTR_KIND_SHADE,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_MINOTAUR,	/* 半人 */
		+1, +5, },
	{ MNSTR_KIND_CHIMERA,	/* 合成獣 */
		+1, +5, },
	{ MNSTR_KIND_FIRE_GIANT,	/* 巨人 */
		+1, +5, },
	{ MNSTR_KIND_MUMMY,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_FROST_GIANT,	/* 巨人 */
		+1, +5, },
	{ MNSTR_KIND_GARGOYLE,	/* 魔法生物 */
		+1, +5, },
	{ MNSTR_KIND_STONE_GOLEM,	/* 魔法生物 */
		+1, +5, },
	{ MNSTR_KIND_CLOUD_GIANT,	/* 巨人 */
		+1, +5, },
	{ MNSTR_KIND_DURAHAN,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_IRON_GOLEM,	/* 魔法生物 */
		+1, +5, },
	{ MNSTR_KIND_MOUNTAIN_GIANT,	/* 巨人 */
		+1, +5, },
	{ MNSTR_KIND_SALAMANDER,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_UNDINE,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_MIMIC,	/* 魔法生物 */
		+1, +5, },
	{ MNSTR_KIND_UNICORN,	/* 幻獣 */
		+1, +5, },
	{ MNSTR_KIND_CYCLOPS,	/* 巨人 */
		+1, +5, },
	{ MNSTR_KIND_BANSHEE,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_GNOME,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_SYLPH,	/* 精霊 */
		+1, +5, },
	{ MNSTR_KIND_WYVERN,	/* 魔獣 */
		+1, +5, },
	{ MNSTR_KIND_MEDUSA,	/* 半人 */
		+1, +5, },
	{ MNSTR_KIND_M_RED_DRAGON,	/* マイナー・ドラゴン */
		+1, +2, },
	{ MNSTR_KIND_M_BLUE_DRAGON,	/* マイナー・ドラゴン */
		+1, +2, },
	{ MNSTR_KIND_M_YELLOW_DRAGON,	/* マイナー・ドラゴン */
		+1, +2, },
	{ MNSTR_KIND_M_GREEN_DRAGON,	/* マイナー・ドラゴン */
		+1, +2, },
	{ MNSTR_KIND_WRAITH,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_HYDRA,	/* 魔獣 */
		+1, +5, },
	{ MNSTR_KIND_LESSER_DAEMON,	/* 悪魔 */
		+1, +5, },
	{ MNSTR_KIND_M_WHITE_DRAGON,	/* マイナー・ドラゴン */
		+1, +2, },
	{ MNSTR_KIND_M_BLACK_DRAGON,	/* マイナー・ドラゴン */
		+1, +2, },
	{ MNSTR_KIND_COCKATRICE,	/* 魔獣 */
		+1, +5, },
	{ MNSTR_KIND_CERBERUS,	/* 魔獣 */
		+1, +5, },
	{ MNSTR_KIND_VAMPIRE,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_M_COPPER_DRAGON,	/* マイナー・ドラゴン */
		+1, +2, },
	{ MNSTR_KIND_M_SILVER_DRAGON,	/* マイナー・ドラゴン */
		+1, +2, },
	{ MNSTR_KIND_M_GOLD_DRAGON,	/* マイナー・ドラゴン */
		+1, +2, },
	{ MNSTR_KIND_GORGON,	/* 魔獣 */
		+1, +5, },
	{ MNSTR_KIND_EFREET,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_DJINNI,	/* 妖魔 */
		+1, +5, },
	{ MNSTR_KIND_BASILISK,	/* 魔獣 */
		+1, +5, },
	{ MNSTR_KIND_PHOENIX,	/* 幻獣 */
		+1, +5, },
	{ MNSTR_KIND_HELLHOUND,	/* 魔獣 */
		+1, +5, },
	{ MNSTR_KIND_SPIRIT,	/* アンデッド */
		+1, +5, },
	{ MNSTR_KIND_GREATER_DAEMON,	/* 悪魔 */
		+1, +5, },
	{ MNSTR_KIND_A_RED_DRAGON,	/* エンシェント・ドラゴン */
		+1, +5, },
	{ MNSTR_KIND_A_BLUE_DRAGON,	/* エンシェント・ドラゴン */
		+1, +5, },
	{ MNSTR_KIND_A_YELLOW_DRAGON,	/* エンシェント・ドラゴン */
		+1, +5, },
	{ MNSTR_KIND_A_GREEN_DRAGON,	/* エンシェント・ドラゴン */
		+1, +5, },
	{ MNSTR_KIND_A_WHITE_DRAGON,	/* エンシェント・ドラゴン */
		+1, +5, },
	{ MNSTR_KIND_A_BLACK_DRAGON,	/* エンシェント・ドラゴン */
		+1, +5, },
	{ MNSTR_KIND_A_COPPER_DRAGON,	/* エンシェント・ドラゴン */
		+1, +5, },
	{ MNSTR_KIND_A_SILVER_DRAGON,	/* エンシェント・ドラゴン */
		+1, +5, },
	{ MNSTR_KIND_A_GOLD_DRAGON,	/* エンシェント・ドラゴン */
		+1, +5, },

	/**/

	{ MNSTR_KIND_NULL,
		+0, +0, },
};

#endif

/***************************************************************
* 街での NPC の出現率リスト
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
