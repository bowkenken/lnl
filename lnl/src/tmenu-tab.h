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
* $Id: tmenu-tab.h,v 1.34 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	TMENU_TAB_H
#define	TMENU_TAB_H

/* 街でのメニュー・データ */

#include	"town.h"
#include	"menu.h"
#include	"request.h"

#include	"tmenu-prot.h"
#include	"request-prot.h"

/**/

menu_t	ls_menu_shop[LS_MENU_SHOP_MAX_N + 1];

menu_t	ls_menu_temple[] = {
	{
		"/temple",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		cb_menu_temple_init, NULL,
		FLG_NULL,
	},
	{
		"/temple/title",
		"<Title>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/temple/remove curse",
		"<Item>",
		'C',
		"",
		N_MSG_MENU_TEMPLE_REMOVE_CURSE, "",
		cb_menu_temple_remove_curse, NULL,
		FLG_NULL,
	},
	{
		"/temple/cure status",
		"<Item>",
		'S',
		"",
		N_MSG_MENU_TEMPLE_CURE_STATUS, "",
		cb_menu_temple_cure_status, NULL,
		FLG_NULL,
	},
	{
		"/temple/resurrection",
		"<Item>",
		'R',
		"",
		N_MSG_MENU_TEMPLE_RESURRECTION, "",
		cb_menu_temple_resurrection, NULL,
		FLG_NULL,
	},
	{
		"/temple/contribution",
		"<Item>",
		'O',
		"",
		N_MSG_MENU_TEMPLE_CONTRIBUTION, "",
		cb_menu_temple_contribution, NULL,
		FLG_NULL,
	},
	{
		"/temple/data",
		"<Item>",
		'D',
		"",
		N_MSG_MENU_SHOP_DATA, "",
		cb_menu_shop_data, NULL,
		FLG_NULL,
	},
	{
		"/temple/collect gold",
		"<Item>",
		'L',
		"",
		N_MSG_MENU_SHOP_COLLECT_GOLD, "",
		cb_menu_shop_collect_gold, NULL,
		FLG_NULL,
	},
	{
		"/temple/divide gold",
		"<Item>",
		'V',
		"",
		N_MSG_MENU_SHOP_DIVIDE_GOLD, "",
		cb_menu_shop_divide_gold, NULL,
		FLG_NULL,
	},
	{
		"/temple/give gold",
		"<Item>",
		'G',
		"",
		N_MSG_MENU_SHOP_GIVE_GOLD, "",
		cb_menu_shop_give_gold, NULL,
		FLG_NULL,
	},
	{
		"",
		"",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
};

menu_t	ls_menu_magic_guild[] = {
	{
		"/magic guild",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		cb_menu_magic_guild_init, NULL,
		FLG_NULL,
	},
/* タイトル */
	{
		"/magic guild/title",
		"<Title>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [基本魔法] */
	{
		"/magic guild/MAG",
		"<Branch>",
		'M',
		"",
		N_MSG_MAG, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [基本魔法] 一般 */
	{
		"/magic guild/MAG/title misc",
		"<Title>",
		'\0',
		"",
		N_MSG_MAG_MISC, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/light",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_LIGHT, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_LIGHT,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/darkness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DARKNESS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DARKNESS,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/store_light",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STORE_LIGHT, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_STORE_LIGHT,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/short_teleport_party",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SHORT_TELEPORT_PARTY, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SHORT_TELEPORT_PARTY,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/teleport_party",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_TELEPORT_PARTY, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_TELEPORT_PARTY,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/teleport",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_TELEPORT, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_TELEPORT,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/recall",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RECALL, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_RECALL,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/knock",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_KNOCK, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_KNOCK,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/lock",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_LOCK, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_LOCK,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/disarm_trap",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DISARM_TRAP, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DISARM_TRAP,
		FLG_NULL,
	},
#if	0
	{
		"/magic guild/MAG/animate_objects",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ANIMATE_OBJECTS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_ANIMATE_OBJECTS,
		FLG_NULL,
	},
#endif
	{
		"/magic guild/MAG/shelter",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SHELTER, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SHELTER,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/create_food",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CREATE_FOOD, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_CREATE_FOOD,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/no_learn misc",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [基本魔法] 探知 */
	{
		"/magic guild/MAG/title detect",
		"<Title>",
		'\0',
		"",
		N_MSG_MAG_DETECT, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/identify_item",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_IDENTIFY_ITEM, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_IDENTIFY_ITEM,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/identify_all_item",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_IDENTIFY_ALL_ITEM, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_IDENTIFY_ALL_ITEM,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/searching",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SEARCHING, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SEARCHING,
		FLG_NULL,
	},
#if	0
	{
		"/magic guild/MAG/analyze_dweomer",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ANALYZE_DWEOMER, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_ANALYZE_DWEOMER,
		FLG_NULL,
	},
#endif
#if	0
	{
		"/magic guild/MAG/detect_magic",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_MAGIC, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DETECT_MAGIC,
		FLG_NULL,
	},
#endif
	{
		"/magic guild/MAG/detect_item",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_ITEM, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DETECT_ITEM,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/detect_doors",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_DOORS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DETECT_DOORS,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/detect_traps",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_TRAPS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DETECT_TRAPS,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/detect_monster",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_MONSTER, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DETECT_MONSTER,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/sense_invisible",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SENSE_INVISIBLE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SENSE_INVISIBLE,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/no_learn detect",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [基本魔法] 状態変化 */
	{
		"/magic guild/MAG/title change status",
		"<Title>",
		'\0',
		"",
		N_MSG_MAG_CHANGE_STAT, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/fly",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FLY, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_FLY,
		FLG_NULL,
	},
#if	0
	{
		"/magic guild/MAG/feather_fall",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FEATHER_FALL, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_FEATHER_FALL,
		FLG_NULL,
	},
#endif
	{
		"/magic guild/MAG/vanish",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_VANISH, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_VANISH,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/darkvision",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DARKVISION, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DARKVISION,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/passwall",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_PASSWALL, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_PASSWALL,
		FLG_NULL,
	},
#if	0
	{
		"/magic guild/MAG/dispel_magic",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DISPEL_MAGIC, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DISPEL_MAGIC,
		FLG_NULL,
	},
#endif
#if	0
	{
		"/magic guild/MAG/mirror_image",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MIRROR_IMAGE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_MIRROR_IMAGE,
		FLG_NULL,
	},
#endif
	{
		"/magic guild/MAG/no_learn change status",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [基本魔法] 特殊変化 */
	{
		"/magic guild/MAG/title change special",
		"<Title>",
		'\0',
		"",
		N_MSG_MAG_CHANGE_SPECIAL, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/polymorph_other",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POLYMORPH_OTHER, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_POLYMORPH_OTHER,
		FLG_NULL,
	},
#if	0
	{
		"/magic guild/MAG/polymorph_self",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POLYMORPH_SELF, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_POLYMORPH_SELF,
		FLG_NULL,
	},
#endif
#if	0
	{
		"/magic guild/MAG/stealth",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STEALTH, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_STEALTH,
		FLG_NULL,
	},
#endif
	{
		"/magic guild/MAG/no_learn change special",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/MAG/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [戦闘魔法] */
	{
		"/magic guild/SOR",
		"<Branch>",
		'O',
		"",
		N_MSG_SOR, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [戦闘魔法] 攻撃 */
	{
		"/magic guild/SOR/title attack",
		"<Title>",
		'\0',
		"",
		N_MSG_SOR_ATTACK, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/magic_missile",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MAGIC_MISSILE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_MAGIC_MISSILE,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/fire_ball",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FIRE_BALL, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_FIRE_BALL,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/ice_blizzard",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ICE_BLIZZARD, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_ICE_BLIZZARD,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/mind_storm",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MIND_STORM, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_MIND_STORM,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/acid_rain",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ACID_RAIN, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_ACID_RAIN,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/lightning_bolt",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_LIGHTNING_BOLT, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_LIGHTNING_BOLT,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/poison_cloud",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POISON_CLOUD, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_POISON_CLOUD,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/death_spell",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DEATH_SPELL, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DEATH_SPELL,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/word_of_destruction",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WORD_OF_DESTRUCTION, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_WORD_OF_DESTRUCTION,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/no_learn attack",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [戦闘魔法] 防御 */
	{
		"/magic guild/SOR/title defense",
		"<Title>",
		'\0',
		"",
		N_MSG_SOR_DEFENSE, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/magic_shield",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MAGIC_SHIELD, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_MAGIC_SHIELD,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/mage_armor",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MAGE_ARMOR, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_MAGE_ARMOR,
		FLG_NULL,
	},
#if	0
	{
		"/magic guild/SOR/stoneskin",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STONESKIN, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_STONESKIN,
		FLG_NULL,
	},
#endif
	{
		"/magic guild/SOR/iron_body",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_IRON_BODY, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_IRON_BODY,
		FLG_NULL,
	},
#if	0
	{
		"/magic guild/SOR/spell_resistance",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SPELL_RESISTANCE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SPELL_RESISTANCE,
		FLG_NULL,
	},
#endif
	{
		"/magic guild/SOR/counter_magic",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_COUNTER_MAGIC, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_COUNTER_MAGIC,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/no_learn defense",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [戦闘魔法] ステータス異常 */
	{
		"/magic guild/SOR/title weaken status",
		"<Title>",
		'\0',
		"",
		N_MSG_SOR_WEAKEN_STAT, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/stone",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STONE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_STONE,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/paralyze",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_PARALYZE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_PARALYZE,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/poison",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POISON, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_POISON,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/confusion",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CONFUSION, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_CONFUSION,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/blindness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_BLINDNESS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_BLINDNESS,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/sleep",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SLEEP, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SLEEP,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/silence",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SILENCE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SILENCE,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/fear",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FEAR, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_FEAR,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/hallucination",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_HALLUCINATION, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_HALLUCINATION,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/charm",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CHARM, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_CHARM,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/no_learn weaken status",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/SOR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [援護魔法] */
	{
		"/magic guild/ENC",
		"<Branch>",
		'E',
		"",
		N_MSG_ENC, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [援護魔法] アビリティ強化 */
	{
		"/magic guild/ENC/title strengthen ability",
		"<Title>",
		'\0',
		"",
		N_MSG_ENC_STRENGTHEN_ABL, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/sharpness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SHARPNESS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SHARPNESS,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/strength",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STRENGTH, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_STRENGTH,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/quickness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_QUICKNESS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_QUICKNESS,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/brainy",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_BRAINY, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_BRAINY,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/wise",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WISE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_WISE,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/attractive",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ATTRACTIVE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_ATTRACTIVE,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/no_learn strengthen ability",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [援護魔法] 強化 */
	{
		"/magic guild/ENC/title strengthen misc",
		"<Title>",
		'\0',
		"",
		N_MSG_ENC_STRENGTHEN_MISC, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/power_up_hp",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POWER_UP_HP, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_POWER_UP_HP,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/haste",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_HASTE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_HASTE,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/no_learn strengthen misc",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [援護魔法] アビリティ弱体 */
	{
		"/magic guild/ENC/title weaken ability",
		"<Title>",
		'\0',
		"",
		N_MSG_ENC_WEAKEN_ABL, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/dullness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DULLNESS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DULLNESS,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/weakness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WEAKNESS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_WEAKNESS,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/slowness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SLOWNESS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SLOWNESS,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/brainless",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_BRAINLESS, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_BRAINLESS,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/foolish",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FOOLISH, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_FOOLISH,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/unattractive",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_UNATTRACTIVE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_UNATTRACTIVE,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/no_learn weaken ability",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [援護魔法] 弱体 */
	{
		"/magic guild/ENC/title weaken misc",
		"<Title>",
		'\0',
		"",
		N_MSG_ENC_WEAKEN_MISC, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/energy_drain",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ENERGY_DRAIN, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_ENERGY_DRAIN,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/slow",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SLOW, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SLOW,
		FLG_NULL,
	},
#if	0
	{
		"/magic guild/ENC/hunger",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_HUNGER, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_HUNGER,
		FLG_NULL,
	},
#endif
#if	0
	{
		"/magic guild/ENC/cancellation",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CANCELLATION, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_CANCELLATION,
		FLG_NULL,
	},
#endif
	{
		"/magic guild/ENC/no_learn weaken misc",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/ENC/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [召喚魔法] */
	{
		"/magic guild/SUM",
		"<Branch>",
		'U',
		"",
		N_MSG_SUM, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [召喚魔法] 召喚 */
	{
		"/magic guild/SUM/title summon",
		"<Title>",
		'\0',
		"",
		N_MSG_SUM_SUMMON, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/SUM/skeleton_warrior",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SKELETON_WARRIOR, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SKELETON_WARRIOR,
		FLG_NULL,
	},

	{
		"/magic guild/SUM/summon_unicorn",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_UNICORN, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SUMMON_UNICORN,
		FLG_NULL,
	},

	{
		"/magic guild/SUM/summon_efreet",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_EFREET, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SUMMON_EFREET,
		FLG_NULL,
	},

	{
		"/magic guild/SUM/summon_djinni",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_DJINNI, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SUMMON_DJINNI,
		FLG_NULL,
	},

	{
		"/magic guild/SUM/summon_phoenix",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_PHOENIX, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SUMMON_PHOENIX,
		FLG_NULL,
	},

	{
		"/magic guild/SUM/summon_bone",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_BONE, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SUMMON_BONE,
		FLG_NULL,
	},
#if	0
	{
		"/magic guild/SUM/summon_random",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_RANDOM, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_SUMMON_RANDOM,
		FLG_NULL,
	},
#endif
#if	0
	{
		"/magic guild/SUM/create_undead",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CREATE_UNDEAD, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_CREATE_UNDEAD,
		FLG_NULL,
	},
#endif
	{
		"/magic guild/SUM/dismissal",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DISMISSAL, "",
		cb_menu_magic_guild, (void *)SPELL_KIND_DISMISSAL,
		FLG_NULL,
	},

	{
		"/magic guild/SUM/no_learn summon",
		"<Item>",
		'Z',
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_magic_guild_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/SUM/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [僧侶呪文] */
/* [精霊魔法]  */
/* [呪歌]  */
/* [忍術] */
/*  */
	{
		"/magic guild/collect gold",
		"<Item>",
		'L',
		"",
		N_MSG_MENU_SHOP_COLLECT_GOLD, "",
		cb_menu_shop_collect_gold, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/divide gold",
		"<Item>",
		'V',
		"",
		N_MSG_MENU_SHOP_DIVIDE_GOLD, "",
		cb_menu_shop_divide_gold, NULL,
		FLG_NULL,
	},

	{
		"/magic guild/give gold",
		"<Item>",
		'G',
		"",
		N_MSG_MENU_SHOP_GIVE_GOLD, "",
		cb_menu_shop_give_gold, NULL,
		FLG_NULL,
	},

	{
		"",
		"",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
};

menu_t	ls_menu_order_sel_mbr[1 + 1 + MBR_MAX_N + 1 + 1];

menu_t	ls_menu_bar[] = {
	{
		"/bar",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/bar/title",
		"<Title>",
		'\0',
		"",
		N_MSG_NAME_BAR, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/bar/order",
		"<Branch>",
		'O',
		"",
		N_MSG_MENU_BAR_ORDER, "",
		cb_menu_bar_order, NULL,
		FLG_NULL,
	},
	{
		"/bar/request",
		"<Branch>",
		'R',
		"",
		N_MSG_MENU_BAR_REQUEST, "",
		cb_menu_request_bar, NULL,
		FLG_NULL,
	},
	{
		"/bar/form",
		"<Branch>",
		'V',
		"",
		N_MSG_MENU_BAR_FORM, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/form",
		"<Branch>",
		'V',
		"",
		N_MSG_MENU_BAR_FORM, "",
		cb_menu_bar_form, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/edit member",
		"<Branch>",
		'P',
		"",
		N_MSG_MENU_BAR_EDIT_MBR, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/edit member/edit member",
		"<Branch>",
		'E',
		"",
		N_MSG_MENU_BAR_EDIT_MBR, "",
		cb_menu_bar_edit_mbr, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/edit member/new member",
		"<OpenWinItem>",
		'N',
		"",
		N_MSG_MENU_BAR_NEW_MBR, "",
		cb_menu_bar_new_mbr, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/edit member/remove member",
		"<Branch>",
		'R',
		"",
		N_MSG_MENU_BAR_REMOVE_MBR, "",
		cb_menu_bar_remove_mbr, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/edit class",
		"<Branch>",
		'C',
		"",
		N_MSG_MENU_BAR_EDIT_CLASS, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/edit class/edit class",
		"<Branch>",
		'E',
		"",
		N_MSG_MENU_BAR_EDIT_CLASS, "",
		cb_menu_bar_edit_class, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/edit class/edit skill",
		"<Branch>",
		'S',
		"",
		N_MSG_MENU_BAR_EDIT_SKILL, "",
		cb_menu_bar_edit_skill, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/edit class/new class",
		"<OpenWinItem>",
		'N',
		"",
		N_MSG_MENU_BAR_NEW_CLASS, "",
		cb_menu_bar_new_class, NULL,
		FLG_NULL,
	},
	{
		"/bar/form/edit class/remove class",
		"<Branch>",
		'R',
		"",
		N_MSG_MENU_BAR_REMOVE_CLASS, "",
		cb_menu_bar_remove_class, NULL,
		FLG_NULL,
	},
	{
		"/bar/load",
		"<OpenWinItem>",
		'L',
		"",
		N_MSG_MENU_BAR_LOAD, "",
		cb_menu_load_bar, NULL,
		FLG_NULL,
	},
	{
		"/bar/save",
		"<OpenWinItem>",
		'S',
		"",
		N_MSG_MENU_BAR_SAVE, "",
		cb_menu_save_bar, NULL,
		FLG_NULL,
	},
	{
		"",
		"",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
};

menu_t	ls_menu_bar_form[
		1 + (1 + LS_MBR_PAGE_MAX_N + 1)
		* LS_MBR_MAX_N_PER_PAGE + 1];

menu_t	ls_menu_bar_form_sub[] = {
	{
		"/form",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		cb_menu_bar_form_sub_init, NULL,
		FLG_NULL,
	},
	{
		"/form/title",
		"<Title>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/form/join",
		"<Branch>",
		'J',
		"",
		N_MSG_MENU_BAR_JOIN, "",
		cb_menu_bar_join, NULL,
		FLG_NULL,
	},
	{
		"/form/not join",
		"<Item>",
		'N',
		"",
		N_MSG_MENU_BAR_NOT_JOIN, "",
		cb_menu_bar_not_join, NULL,
		FLG_NULL,
	},
	{
		"/form/data",
		"<OpenWinItem>",
		'P',
		"",
		N_MSG_MENU_CHR_DATA, "",
		cb_menu_bar_data_form, NULL,
		FLG_NULL,
	},
	{
		"",
		"",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
};

menu_t	ls_menu_bar_join[1 + MBR_MAX_N + 1];

menu_t	ls_menu_bar_sel_mbr[
		1 + (1 + LS_MBR_PAGE_MAX_N + 1)
		* LS_MBR_MAX_N_PER_PAGE + 1];

menu_t	ls_menu_bar_edit_mbr_sub[] = {
	{
		"/edit member",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/edit member/title",
		"<Title>",
		'\0',
		"",
		N_MSG_TTL_MENU_BAR_EDIT_MBR, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/edit member/data",
		"<OpenWinItem>",
		'P',
		"",
		N_MSG_MENU_CHR_DATA, "",
		cb_menu_bar_data_edit, NULL,
		FLG_NULL,
	},
	{
		"/edit member/arrange up",
		"<Item>",
		'U',
		"",
		N_MSG_MENU_BAR_ARRANGE_UP, "",
		cb_menu_bar_arrange_up, NULL,
		FLG_NULL,
	},
	{
		"/edit member/arrange down",
		"<Item>",
		'D',
		"",
		N_MSG_MENU_BAR_ARRANGE_DOWN, "",
		cb_menu_bar_arrange_down, NULL,
		FLG_NULL,
	},
	{
		"/edit member/arrange top",
		"<Item>",
		'T',
		"",
		N_MSG_MENU_BAR_ARRANGE_TOP, "",
		cb_menu_bar_arrange_top, NULL,
		FLG_NULL,
	},
	{
		"/edit member/arrange bottom",
		"<Item>",
		'B',
		"",
		N_MSG_MENU_BAR_ARRANGE_BOTTOM, "",
		cb_menu_bar_arrange_bottom, NULL,
		FLG_NULL,
	},
	{
		"",
		"",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
};

menu_t	ls_menu_bar_sel_edit_class[] = {
	{
		"/select edit class",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/select edit class/title",
		"<Title>",
		'\0',
		"",
		N_MSG_TTL_MENU_SEL_EDIT_CLASS, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/select edit class/edit",
		"<OpenWinItem>",
		'E',
		"",
		N_MSG_MENU_BAR_EDIT_CLASS, "",
		cb_menu_bar_edit_class_sub, NULL,
		FLG_NULL,
	},
	{
		"/select edit class/arrange up",
		"<Item>",
		'U',
		"",
		N_MSG_MENU_BAR_ARRANGE_UP_CLASS, "",
		cb_menu_bar_arrange_up_class, NULL,
		FLG_NULL,
	},
	{
		"/select edit class/arrange down",
		"<Item>",
		'D',
		"",
		N_MSG_MENU_BAR_ARRANGE_DOWN_CLASS, "",
		cb_menu_bar_arrange_down_class, NULL,
		FLG_NULL,
	},
	{
		"/select edit class/arrange top",
		"<Item>",
		'T',
		"",
		N_MSG_MENU_BAR_ARRANGE_TOP_CLASS, "",
		cb_menu_bar_arrange_top_class, NULL,
		FLG_NULL,
	},
	{
		"/select edit class/arrange bottom",
		"<Item>",
		'B',
		"",
		N_MSG_MENU_BAR_ARRANGE_BOTTOM_CLASS, "",
		cb_menu_bar_arrange_bottom_class, NULL,
		FLG_NULL,
	},
	{
		"",
		"",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
};

menu_t	ls_menu_inn[] = {
	{
		"/inn",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/inn/title",
		"<Title>",
		'\0',
		"",
		N_MSG_NAME_INN, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/inn/stay",
		"<Item>",
		'S',
		"",
		N_MSG_MENU_INN_STAY, "",
		cb_menu_inn_stay, (void *)FALSE,
		FLG_NULL,
	},
	{
		"/inn/short stay",
		"<Item>",
		'R',
		"",
		N_MSG_MENU_INN_SHORT_STAY, "",
		cb_menu_inn_short_stay, (void *)TRUE,
		FLG_NULL,
	},
	{
		"/inn/stay in mews",
		"<Item>",
		'M',
		"",
		N_MSG_MENU_INN_STAY_IN_MEWS, "",
		cb_menu_inn_stay_in_mews, (void *)FALSE,
		FLG_NULL,
	},
	{
		"/inn/bath",
		"<Branch>",
		'B',
		"",
		N_MSG_MENU_INN_BATH, "",
		cb_menu_inn_bath, NULL,
		FLG_NULL,
	},
	{
		"/inn/divide gold",
		"<Item>",
		'V',
		"",
		N_MSG_MENU_SHOP_DIVIDE_GOLD, "",
		cb_menu_shop_divide_gold, NULL,
		FLG_NULL,
	},
	{
		"",
		"",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
};

menu_t	ls_menu_pet_shop[] = {
	{
		"/pet shop",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		cb_menu_pet_shop_init, NULL,
		FLG_NULL,
	},
	{
		"/pet shop/title",
		"<Title>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/pet shop/data",
		"<OpenWinItem>",
		'D',
		"",
		N_MSG_MENU_PET_SHOP_DATA, "",
		cb_menu_pet_shop_data, NULL,
		FLG_NULL,
	},
	{
		"/pet shop/buy",
		"<Branch>",
		'B',
		"",
		N_MSG_MENU_PET_SHOP_BUY, "",
		cb_menu_pet_shop_buy, NULL,
		FLG_NULL,
	},
	{
		"/pet shop/take",
		"<Branch>",
		'T',
		"",
		N_MSG_MENU_PET_SHOP_TAKE, "",
		cb_menu_pet_shop_take, NULL,
		FLG_NULL,
	},
	{
		"/pet shop/leave",
		"<Branch>",
		'L',
		"",
		N_MSG_MENU_PET_SHOP_LEAVE, "",
		cb_menu_pet_shop_leave, NULL,
		FLG_NULL,
	},
	{
		"/pet shop/name",
		"<Branch>",
		'N',
		"",
		N_MSG_MENU_PET_SHOP_NAME, "",
		cb_menu_pet_shop_name, NULL,
		FLG_NULL,
	},
	{
		"/pet shop/remove",
		"<Branch>",
		'R',
		"",
		N_MSG_MENU_PET_SHOP_REMOVE, "",
		cb_menu_pet_shop_remove, NULL,
		FLG_NULL,
	},
	{
		"",
		"",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
};

#define	PET_SHOP_PAGE_MAX_N	4
#define	PET_SHOP_PET_N_PER_PAGE	16
#define	PET_SHOP_PET_MAX_N	\
	(PET_SHOP_PAGE_MAX_N * PET_SHOP_PET_N_PER_PAGE)

menu_t	ls_menu_pet_shop_take[1 + 1 + (LS_PET_MAX_N * 2) + 1];
menu_t	ls_menu_pet_shop_leave[1 + 1 + (PET_MAX_N * 2) + 1];
menu_t	ls_menu_pet_shop_name[1 + 1 + (LS_PET_MAX_N * 2) + 1];
menu_t	ls_menu_pet_shop_remove[1 + 1 + (LS_PET_MAX_N * 2) + 1];
menu_t	ls_menu_pet_shop_buy[
	1 + 1 + PET_SHOP_PET_MAX_N + PET_SHOP_PAGE_MAX_N + 1];

menu_t	ls_menu_navi[1 + 1 + SHOP_N_MAX_N + 1];
menu_t	ls_menu_auto_sale[1 + 1 + MBR_ITEM_MAX_N + 1 + 1];

menu_t	ls_menu_sel_skill[
	1 + 1 + (SKILL_KIND_MAX_N + SKILL_GROUP_KIND_MAX_N * 3) + 1];

#endif	/* TMENU_TAB_H */
