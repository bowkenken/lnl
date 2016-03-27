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
* $Id: PcgDunTab.h,v 1.40 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef PCG_DUN_TAB_H
#define PCG_DUN_TAB_H	1

////////////////////////////////////////////////////////////////
// パターンのテーブル
////////////////////////////////////////////////////////////////

PcgTab gPcgTabNullTown[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"null/town/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabNullDun[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"null/dungeon/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabFloorTown[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"floor/town/",
	},
	{
		// 水たまり
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		5,
		"floor/town/puddle/",
	},
	{
		// 苔
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		10,
		"floor/town/moss/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabFloorDun[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"floor/dungeon/",
	},
	{
		// 水たまり
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		1,
		"floor/dungeon/puddle/",
	},
	{
		// 苔
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		10,
		"floor/dungeon/moss/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabFloorLast[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"floor/last/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabHole[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"floor/hole/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabWallTown[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"wall/town/",
	},
	{
		// 苔
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		30,
		"wall/town/moss/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabWallDun[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"wall/dungeon/",
	},
	{
		// 苔
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		30,
		"wall/dungeon/moss/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabWallLast[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"wall/last/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabStatue[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		30,
		"statue/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabStreetlampOn[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"streetlamp/on",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabStreetlampOff[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"streetlamp/off",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabBootUnit[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"boot_unit",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabSignboard[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"signboard",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabLava[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"water/lava",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabStairsUpTown[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"stairs/up/town/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabStairsUpDun[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"stairs/up/dungeon/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabStairsDownTown[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"stairs/down/town/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabStairsDownDun[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"stairs/down/dungeon/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabStairsLastBoss[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"stairs/down/last/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabDoorCloseTown[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"door/close/town/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabDoorCloseDun[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"door/close/dungeon/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabDoorOpenTown[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"door/open/town/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabDoorOpenDun[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"door/open/dungeon/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabWindowClose[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"window/close/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabWindowOpen[] = {
	{
		// 普通
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"window/open/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabTrap[] = {
	{
		// 未識別
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_NULL,
		100,
		"trap/",
	},
	{
		// 眠りの罠
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_TRAP_SLEEP,
		100,
		"trap/sleep/",
	},
	{
		// 弓矢の罠
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_TRAP_ARW,
		100,
		"trap/arw/",
	},
	{
		// 毒ダーツの罠
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_TRAP_POISON_DARTS,
		100,
		"trap/poison_darts/",
	},
	{
		// 爆弾の罠
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_TRAP_BOMB,
		100,
		"trap/bomb/",
	},
	{
		// パーティ瞬間移動の罠
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_TRAP_TELEPORT_PARTY,
		100,
		"trap/teleport_party/",
	},
	{
		// 瞬間移動の罠
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_TRAP_TELEPORT,
		100,
		"trap/teleport/",
	},
	{
		// 落し穴
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_TRAP_PIT,
		100,
		"trap/pit/",
	},
	{
		// シュート
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_TRAP_CHUTE,
		100,
		"trap/chute/",
	},
	{
		// 聖域
		MNSTR_KIND_NULL,
		FACE_MJR_TRAP, FACE_MNR_TRAP_SANCTUARY,
		100,
		"trap/sanctuary/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabCrsr[] = {
	{
		// 
		ATTITUDE_MATE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"cursor/main/mate",
	},
	{
		// 
		ATTITUDE_FRIENDLY,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"cursor/main/friendly",
	},
	{
		// 
		ATTITUDE_NEUTRAL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"cursor/main/neutral",
	},
	{
		// 
		ATTITUDE_ENEMY,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"cursor/main/enemy",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabCrsrSub[] = {
	{
		// 
		ATTITUDE_MATE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"cursor/sub/mate",
	},
	{
		// 
		ATTITUDE_FRIENDLY,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"cursor/sub/friendly",
	},
	{
		// 
		ATTITUDE_NEUTRAL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"cursor/sub/neutral",
	},
	{
		// 
		ATTITUDE_ENEMY,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"cursor/sub/enemy",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabSquareParty[] = {
	{
		MNSTR_KIND_NULL,
		FACE_MJR_SQUARE, 'N',
		100,
		"anchor/north",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_SQUARE, 'E',
		100,
		"anchor/east",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_SQUARE, 'S',
		100,
		"anchor/south",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_SQUARE, 'W',
		100,
		"anchor/west",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabSquareMbr[] = {
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"anchor/member",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabItem[] = {
	/* 謎のアイテム */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"item/unknown/",
	},
	/* 武器 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_KNIFE,
		100,
		"item/weapon/knife/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_SHORT_SWORD,
		100,
		"item/weapon/short_sword/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_LONG_SWORD,
		100,
		"item/weapon/long_sword/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_SABRE,
		100,
		"item/weapon/sabre/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_RAPIER,
		100,
		"item/weapon/rapier/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_HAND_AXE,
		100,
		"item/weapon/hand_axe/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_BATTLE_AXE,
		100,
		"item/weapon/battle_axe/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_SPEAR,
		100,
		"item/weapon/spear/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_LANCE,
		100,
		"item/weapon/lance/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_FLAIL,
		100,
		"item/weapon/flail/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_MACE,
		100,
		"item/weapon/mace/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_HAMMER,
		100,
		"item/weapon/hammer/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_GLAIVE,
		100,
		"item/weapon/glaive/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_KNUCKLE,
		100,
		"item/weapon/knuckle/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_BOW,
		100,
		"item/weapon/bow/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_ARW,
		100,
		"item/weapon/arw/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_STONE,
		100,
		"item/weapon/stone/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_WEAPON, FACE_MNR_DAGGER,
		100,
		"item/weapon/dagger/",
	},
	/* 防具 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_ARMOR, FACE_MNR_ARMOR_SHIELD,
		100,
		"item/armor/shield/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_ARMOR, FACE_MNR_ARMOR_HEAD,
		100,
		"item/armor/head/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_ARMOR, FACE_MNR_ARMOR_BODY,
		100,
		"item/armor/body/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_ARMOR, FACE_MNR_ARMOR_ARM,
		100,
		"item/armor/arm/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_ARMOR, FACE_MNR_ARMOR_FEET,
		100,
		"item/armor/feet/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_ARMOR, FACE_MNR_ARMOR_ABOUT_BODY,
		100,
		"item/armor/about_body/",
	},
	/* 薬 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_POTION, FACE_MNR_NULL,
		100,
		"item/potion/",
	},
	/* 巻物 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_SCROLL, FACE_MNR_NULL,
		100,
		"item/scroll/",
	},
	/* 杖 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_STICK, FACE_MNR_WAND,
		100,
		"item/stick/wand/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_STICK, FACE_MNR_ROD,
		100,
		"item/stick/rod/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_STICK, FACE_MNR_STAFF,
		100,
		"item/stick/staff/",
	},
	/* アクセサリ */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_ACCESSORY, FACE_MNR_RING,
		100,
		"item/accessory/ring/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_ACCESSORY, FACE_MNR_AMULET,
		100,
		"item/accessory/amulet/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_ACCESSORY, FACE_MNR_NECKLACE,
		100,
		"item/accessory/necklace/",
	},
	/* 食糧 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_FOOD, FACE_MNR_NULL,
		100,
		"item/food/",
	},
	/* 宝箱 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_CHEST, FACE_MNR_NULL,
		100,
		"item/chest/",
	},
	/* 金貨 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_COIN, FACE_MNR_NULL,
		100,
		"item/coin/",
	},
	/* 宝石 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_GEM, FACE_MNR_NULL,
		100,
		"item/gem/",
	},
	/* その他のアイテム */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_ANTHOLOGY,
		100,
		"item/misc/anthology/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_LIGHT,
		100,
		"item/misc/light/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_SPIKE,
		100,
		"item/misc/spike/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_TOBACCO,
		100,
		"item/misc/tobacco/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_PIPE,
		100,
		"item/misc/pipe/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_DISPOSAL,
		100,
		"item/misc/disposal/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_RARE_GOODS,
		100,
		"item/misc/rare_goods/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_BONE_GOOD,
		100,
		"item/misc/bone/good/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_BONE_EVIL,
		100,
		"item/misc/bone/evil/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_MISC, FACE_MNR_JUNK,
		100,
		"item/misc/junk/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_INST, FACE_MNR_INST,
		100,
		"item/misc/inst/",
	},
	/* 末尾 */
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabMbrDflt = {
	MNSTR_KIND_NULL,
	FACE_MJR_NULL, FACE_MNR_NULL,
	100,
	"character/pc/",
};

PcgTab gPcgTabMbrNull = {
	MNSTR_KIND_NULL,
	FACE_MJR_NULL, FACE_MNR_NULL,
	100,
	"character/pc/",
};

PcgTab gPcgTabMnstr[] = {
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/",
	},
	/* 神 */
	/* ドラゴン */
	{
		MNSTR_KIND_A_GOLD_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/a_gold_dragon/",
	},
	{
		MNSTR_KIND_A_SILVER_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/a_silver_dragon/",
	},
	{
		MNSTR_KIND_A_COPPER_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/a_copper_dragon/",
	},
	{
		MNSTR_KIND_A_RED_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/a_red_dragon/",
	},
	{
		MNSTR_KIND_A_BLUE_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/a_blue_dragon/",
	},
	{
		MNSTR_KIND_A_YELLOW_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/a_yellow_dragon/",
	},
	{
		MNSTR_KIND_A_GREEN_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/a_green_dragon/",
	},
	{
		MNSTR_KIND_A_WHITE_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/a_white_dragon/",
	},
	{
		MNSTR_KIND_A_BLACK_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/a_black_dragon/",
	},
	{
		MNSTR_KIND_M_GOLD_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/m_gold_dragon/",
	},
	{
		MNSTR_KIND_M_SILVER_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/m_silver_dragon/",
	},
	{
		MNSTR_KIND_M_COPPER_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/m_copper_dragon/",
	},
	{
		MNSTR_KIND_M_RED_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/m_red_dragon/",
	},
	{
		MNSTR_KIND_M_BLUE_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/m_blue_dragon/",
	},
	{
		MNSTR_KIND_M_YELLOW_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/m_yellow_dragon/",
	},
	{
		MNSTR_KIND_M_GREEN_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/m_green_dragon/",
	},
	{
		MNSTR_KIND_M_WHITE_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/m_white_dragon/",
	},
	{
		MNSTR_KIND_M_BLACK_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/m_black_dragon/",
	},
	/* 幻獣 */
	{
		MNSTR_KIND_PHOENIX,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/illusory/phoenix/",
	},
	{
		MNSTR_KIND_UNICORN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/illusory/unicorn/",
	},
	{
		MNSTR_KIND_PYON_PYON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/illusory/pyon_pyon/",
	},
	/* 妖精 */
	{
		MNSTR_KIND_LEPRECHAUN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/fairy/leprechaun/",
	},
	/* 精霊 */
	{
		MNSTR_KIND_FIRE_ELEMENTAL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/fire_elemental/",
	},
	{
		MNSTR_KIND_SALAMANDER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/salamander/",
	},
	{
		MNSTR_KIND_WATER_ELEMENTAL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/water_elemental/",
	},
	{
		MNSTR_KIND_UNDINE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/undine/",
	},
	{
		MNSTR_KIND_AIR_ELEMENTAL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/air_elemental/",
	},
	{
		MNSTR_KIND_SYLPH,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/sylph/",
	},
	{
		MNSTR_KIND_EARTH_ELEMENTAL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/earth_elemental/",
	},
	{
		MNSTR_KIND_GNOME,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/gnome/",
	},
	{
		MNSTR_KIND_WILL_O_WISP,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/will_o_wisp/",
	},
	{
		MNSTR_KIND_SHADE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/shade/",
	},
	/* 植物 */
	{
		MNSTR_KIND_VENUS_FLY_TRAP,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/plant/venus_fly_trap/",
	},
	{
		MNSTR_KIND_SLIME,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/plant/slime/",
	},
	{
		MNSTR_KIND_SPORE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/plant/spore/",
	},
	/* 動物 */
	{
		MNSTR_KIND_GIANT_BAT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/animal/giant_bat/",
	},
	{
		MNSTR_KIND_GIANT_RAT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/animal/giant_rat/",
	},
	{
		MNSTR_KIND_GIANT_SNAKE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/animal/giant_snake/",
	},
	{
		MNSTR_KIND_VIPER_SNAKE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/animal/viper_snake/",
	},
	{
		MNSTR_KIND_CAT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/animal/cat/",
	},
	{
		MNSTR_KIND_DOG,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/animal/dog/",
	},
	{
		MNSTR_KIND_WOLF,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/animal/wolf/",
	},
	/* 昆虫 */
	{
		MNSTR_KIND_GIANT_CENTIPEDE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/insect/giant_centipede/",
	},
	{
		MNSTR_KIND_GIANT_BEE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/insect/giant_bee/",
	},
	{
		MNSTR_KIND_GIANT_SCORPION,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/insect/giant_scorpion/",
	},
	{
		MNSTR_KIND_GIANT_ANT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/insect/giant_ant/",
	},
	{
		MNSTR_KIND_GIANT_SPIDER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/insect/giant_spider/",
	},
	{
		MNSTR_KIND_ACID_FLY,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/insect/acid_fly/",
	},
	{
		MNSTR_KIND_GIANT_BEETLE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/insect/giant_beetle/",
	},
	/* 人間 */
	{
		MNSTR_KIND_FIGHTER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/fighter/",
	},
	{
		MNSTR_KIND_MONK,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/monk/",
	},
	{
		MNSTR_KIND_HUNTER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/hunter/",
	},
	{
		MNSTR_KIND_THIEF,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/thief/",
	},
	{
		MNSTR_KIND_WIZARD,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/wizard/",
	},
	{
		MNSTR_KIND_SUMMONER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/summoner/",
	},
	{
		MNSTR_KIND_PRIEST,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/priest/",
	},
	{
		MNSTR_KIND_SHAMAN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/shaman/",
	},
	{
		MNSTR_KIND_BARD,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/bard/",
	},
	{
		MNSTR_KIND_NINJA,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/ninja/",
	},
	{
		MNSTR_KIND_BISHOP,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/bishop/",
	},
	{
		MNSTR_KIND_FARMER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/farmer/",
	},
	{
		MNSTR_KIND_CRAFTSMAN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/craftsman/",
	},
	{
		MNSTR_KIND_MERCHANT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/human/merchant/",
	},
	/* 半人 */
	{
		MNSTR_KIND_HARPY,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/harpy/",
	},
	{
		MNSTR_KIND_ANDRO_SCORPION,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/andro_scorpion/",
	},
	{
		MNSTR_KIND_LAMIA,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/lamia/",
	},
	{
		MNSTR_KIND_CENTAUR,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/centaur/",
	},
	{
		MNSTR_KIND_BIRD_MAN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/bird_man/",
	},
	{
		MNSTR_KIND_WEREWOLF,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/werewolf/",
	},
	{
		MNSTR_KIND_MINOTAUR,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/minotaur/",
	},
	{
		MNSTR_KIND_MEDUSA,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/medusa/",
	},
	/* 巨人 */
	{
		MNSTR_KIND_YETI,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/yeti/",
	},
	{
		MNSTR_KIND_OGRE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/ogre/",
	},
	{
		MNSTR_KIND_TROLL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/troll/",
	},
	{
		MNSTR_KIND_MORMIN_TROLL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/mormin_troll/",
	},
	{
		MNSTR_KIND_FIRE_GIANT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/fire_giant/",
	},
	{
		MNSTR_KIND_FROST_GIANT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/frost_giant/",
	},
	{
		MNSTR_KIND_CLOUD_GIANT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/cloud_giant/",
	},
	{
		MNSTR_KIND_MOUNTAIN_GIANT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/mountain_giant/",
	},
	{
		MNSTR_KIND_CYCLOPS,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/cyclops/",
	},
	/* 巨大生物 */
	/* 水棲生物 */
	/* 魔法生物 */
	{
		MNSTR_KIND_INVISIBLE_STALKER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/invisible_stalker/",
	},
	{
		MNSTR_KIND_GARGOYLE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/gargoyle/",
	},
	{
		MNSTR_KIND_MIMIC,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/mimic/",
	},
	{
		MNSTR_KIND_WOOD_GOLEM,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/wood_golem/",
	},
	{
		MNSTR_KIND_BONE_GOLEM,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/bone_golem/",
	},
	{
		MNSTR_KIND_FLESH_GOLEM,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/flesh_golem/",
	},
	{
		MNSTR_KIND_STONE_GOLEM,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/stone_golem/",
	},
	{
		MNSTR_KIND_IRON_GOLEM,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/iron_golem/",
	},
	{
		MNSTR_KIND_GAS_CLOUD,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/gas_cloud/",
	},
	/* 合成獣 */
	{
		MNSTR_KIND_HIPPOGRIFF,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/compound/hippogriff/",
	},
	{
		MNSTR_KIND_GRIFFON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/compound/griffon/",
	},
	{
		MNSTR_KIND_MANTICORE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/compound/manticore/",
	},
	{
		MNSTR_KIND_CHIMERA,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/compound/chimera/",
	},
	/* アンデッド */
	{
		MNSTR_KIND_POLTERGEIST,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/poltergeist/",
	},
	{
		MNSTR_KIND_SKELETON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/skeleton/",
	},
	{
		MNSTR_KIND_ZOMBIE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/zombie/",
	},
	{
		MNSTR_KIND_GHOUL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/ghoul/",
	},
	{
		MNSTR_KIND_GHOST,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/ghost/",
	},
	{
		MNSTR_KIND_WIGHT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/wight/",
	},
	{
		MNSTR_KIND_MUMMY,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/mummy/",
	},
	{
		MNSTR_KIND_DURAHAN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/durahan/",
	},
	{
		MNSTR_KIND_BANSHEE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/banshee/",
	},
	{
		MNSTR_KIND_WRAITH,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/wraith/",
	},
	{
		MNSTR_KIND_VAMPIRE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/vampire/",
	},
	{
		MNSTR_KIND_SPIRIT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/spirit/",
	},
	/* 妖魔 */
	{
		MNSTR_KIND_KOBOLD,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/kobold/",
	},
	{
		MNSTR_KIND_GOBLIN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/goblin/",
	},
	{
		MNSTR_KIND_GREMLIN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/gremlin/",
	},
	{
		MNSTR_KIND_HOBGOBLIN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/hobgoblin/",
	},
	{
		MNSTR_KIND_ORK,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/ork/",
	},
	{
		MNSTR_KIND_GNOLL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/gnoll/",
	},
	{
		MNSTR_KIND_INCUBUS,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/incubus/",
	},
	{
		MNSTR_KIND_SUCCUBUS,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/succubus/",
	},
	{
		MNSTR_KIND_EFREET,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/efreet/",
	},
	{
		MNSTR_KIND_DJINNI,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil/djinni/",
	},
	/* 魔獣 */
	{
		MNSTR_KIND_RUST_MONSTER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil_beast/rust_monster/",
	},
	{
		MNSTR_KIND_HELLHOUND,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil_beast/hellhound/",
	},
	{
		MNSTR_KIND_HYDRA,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil_beast/hydra/",
	},
	{
		MNSTR_KIND_COCKATRICE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil_beast/cockatrice/",
	},
	{
		MNSTR_KIND_WYVERN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil_beast/wyvern/",
	},
	{
		MNSTR_KIND_CERBERUS,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil_beast/cerberus/",
	},
	{
		MNSTR_KIND_GORGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil_beast/gorgon/",
	},
	{
		MNSTR_KIND_BASILISK,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil_beast/basilisk/",
	},
	/* 悪魔 */
	{
		MNSTR_KIND_IMP,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/imp/",
	},
	{
		MNSTR_KIND_JACK_O_LANTERN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/jack_o_lantern/",
	},
	{
		MNSTR_KIND_LESSER_DAEMON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/lesser_daemon/",
	},
	{
		MNSTR_KIND_GREATER_DAEMON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/greater_daemon/",
	},
	/* ボス */
	{
		MNSTR_KIND_HIGH_RE_HOO,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/giant/high_re_hoo/",
	},
	{
		MNSTR_KIND_GREAT_MINOTAUR,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/great_minotaur/",
	},
	{
		MNSTR_KIND_BILLION_ELEMENTAL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/elemental/billion_elemental/",
	},
	{
		MNSTR_KIND_CYBERN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/magical/cybern/",
	},
	{
		MNSTR_KIND_GIGANTIC_CENTIPEDE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/huge/gigantic_centipede/",
	},
	{
		MNSTR_KIND_MEDUSA_ZOMBIE,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/hybrid/medusa_zombie/",
	},
	{
		MNSTR_KIND_BLACK_UNICORN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/evil_beast/black_unicorn/",
	},
	{
		MNSTR_KIND_VAMPIRE_LORD,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/undead/vampire_lord/",
	},
	{
		MNSTR_KIND_RELATIVISTIC_DAEMON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/relativistic_daemon/",
	},
	{
		MNSTR_KIND_ETERNAL_DRAGON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/dragon/eternal_dragon/",
	},
	/* ラスボス */
	{
		MNSTR_KIND_EXEL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/exel/",
	},
	{
		MNSTR_KIND_EXELER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/exeler/",
	},
	{
		MNSTR_KIND_XEX,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/xex/",
	},
	{
		MNSTR_KIND_XX,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/xx/",
	},
	/**/
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabMnstrHyper[] = {
	{
		MNSTR_KIND_EXEL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/exel/hyper/",
	},
	{
		MNSTR_KIND_EXELER,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"character/monster/devil/exeler/hyper/",
	},
	/**/
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

const long nGuiVfxBashAnimMax = 8;
PcgTab gPcgTabGuiVfxBash[] = {
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/bash/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

const long nGuiVfxBashCrtclAnimMax = 12;
PcgTab gPcgTabGuiVfxBashCrtcl[] = {
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/bash/critical/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabGuiVfxArw[] = {
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/arrow/",
	},
	{
		MNSTR_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabGuiVfxSpell[] = {
	{
		// 殴打
		RESI_KIND_KNOC,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/spell/knock/",
	},
	{
		// 斬撃
		RESI_KIND_SLAS,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/spell/slash/",
	},
	{
		// 刺突
		RESI_KIND_STIN,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/spell/sting/",
	},
	{
		// 火熱
		RESI_KIND_HEAT,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/spell/fire/",
	},
	{
		// 水冷
		RESI_KIND_COLD,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/spell/water/",
	},
	{
		// 風心
		RESI_KIND_MIND,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/spell/air/",
	},
	{
		// 土酸
		RESI_KIND_ACID,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/spell/earth/",
	},
	{
		// 光雷
		RESI_KIND_ELEC,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/spell/light/",
	},
	{
		// 闇毒
		RESI_KIND_POIS,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/spell/dark/",
	},
	{
		RESI_KIND_SLAS,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

PcgTab gPcgTabGuiVfxBlast[] = {
	{
		// 普通
		BLAST_KIND_STD,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/blast/std/",
	},
	{
		// 首切り
		BLAST_KIND_NINJA_CRTCL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/blast/ninja_crtcl/",
	},
	{
		// 破壊の呪文
		BLAST_KIND_WORD_OF_DESTRUCTION,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/blast/word_of_destruction/",
	},
	{
		BLAST_KIND_STD,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

const long nGuiVfxNinjaTyphoonAnimMax = 8;
const long nGuiVfxNinjaConflagrationAnimMax = 10;
const long nGuiVfxNinjaThundercloudAnimMax = 8;
const long nGuiVfxNinjaInundationAnimMax = 8;
PcgTab gPcgTabGuiVfxNinja[] = {
	{
		// 木遁-台風
		SPELL_KIND_TYPHOON,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/ninja/typhoon/",
	},
	{
		// 火遁-火災
		SPELL_KIND_CONFLAGRATION,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/ninja/conflagration/",
	},
	{
		// 金遁-雷雲
		SPELL_KIND_THUNDERCLOUD,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/ninja/thundercloud/",
	},
	{
		// 水遁-洪水
		SPELL_KIND_INUNDATION,
		FACE_MJR_NULL, FACE_MNR_NULL,
		100,
		"vfx/ninja/inundation/",
	},
	{
		SPELL_KIND_NULL,
		FACE_MJR_NULL, FACE_MNR_NULL,
		-1,
		"",
	},
};

#endif /* PCG_DUN_TAB_H */
