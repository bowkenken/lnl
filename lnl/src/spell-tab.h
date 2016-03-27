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
* $Id: spell-tab.h,v 1.27 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	SPELL_TAB_H
#define	SPELL_TAB_H

/***************************************************************
* 呪文のメニュー・データ
***************************************************************/

#include	"menu.h"
#include	"spell-prot.h"

spell_tab_t	spell_tab[] = {
#include	"spell-gen-tab.h"
};

menu_t	ls_menu_spell[] = {
	{
		"/spell",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* 呪文記録 */
	{
		"/spell/reg spell",
		"<Item>",
		ACCEL_KEY_REG_SPELL,
		"",
		N_MSG_NULL, "",
		cb_menu_reg_spell, NULL,
		FLG_NULL,
	},

	{
		"/spell/reg spell remark",
		"<OpenWinItem>",
		ACCEL_KEY_REG_SPELL_REMARK,
		"",
		N_MSG_NULL, "",
		cb_menu_reg_spell_remark, NULL,
		FLG_NULL,
	},
/* [基本魔法] */
	{
		"/spell/MAG",
		"<Branch>",
		'M',
		"",
		N_MSG_MAG, "",
		cb_menu_dflt_spell_mag, NULL,
		FLG_NULL,
	},
/* [基本魔法] 一般 */
	{
		"/spell/MAG/title misc",
		"<Title>",
		'\0',
		"",
		N_MSG_MAG_MISC, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/MAG/light",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_LIGHT, "",
		cb_menu_spell, (void *)SPELL_KIND_LIGHT,
		FLG_NULL,
	},

	{
		"/spell/MAG/darkness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DARKNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_DARKNESS,
		FLG_NULL,
	},

	{
		"/spell/MAG/store_light",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STORE_LIGHT, "",
		cb_menu_spell, (void *)SPELL_KIND_STORE_LIGHT,
		FLG_NULL,
	},

	{
		"/spell/MAG/short_teleport_party",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SHORT_TELEPORT_PARTY, "",
		cb_menu_spell, (void *)SPELL_KIND_SHORT_TELEPORT_PARTY,
		FLG_NULL,
	},

	{
		"/spell/MAG/teleport_party",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_TELEPORT_PARTY, "",
		cb_menu_spell, (void *)SPELL_KIND_TELEPORT_PARTY,
		FLG_NULL,
	},

	{
		"/spell/MAG/teleport",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_TELEPORT, "",
		cb_menu_spell, (void *)SPELL_KIND_TELEPORT,
		FLG_NULL,
	},

	{
		"/spell/MAG/recall",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RECALL, "",
		cb_menu_spell, (void *)SPELL_KIND_RECALL,
		FLG_NULL,
	},

	{
		"/spell/MAG/knock",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_KNOCK, "",
		cb_menu_spell, (void *)SPELL_KIND_KNOCK,
		FLG_NULL,
	},

	{
		"/spell/MAG/lock",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_LOCK, "",
		cb_menu_spell, (void *)SPELL_KIND_LOCK,
		FLG_NULL,
	},

	{
		"/spell/MAG/disarm_trap",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DISARM_TRAP, "",
		cb_menu_spell, (void *)SPELL_KIND_DISARM_TRAP,
		FLG_NULL,
	},

	{
		"/spell/MAG/animate_objects",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ANIMATE_OBJECTS, "",
		cb_menu_spell, (void *)SPELL_KIND_ANIMATE_OBJECTS,
		FLG_NULL,
	},

	{
		"/spell/MAG/shelter",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SHELTER, "",
		cb_menu_spell, (void *)SPELL_KIND_SHELTER,
		FLG_NULL,
	},

	{
		"/spell/MAG/create_food",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CREATE_FOOD, "",
		cb_menu_spell, (void *)SPELL_KIND_CREATE_FOOD,
		FLG_NULL,
	},

	{
		"/spell/MAG/no_learn misc",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/MAG/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [基本魔法] 探知 */
	{
		"/spell/MAG/title detect",
		"<Title>",
		'\0',
		"",
		N_MSG_MAG_DETECT, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/MAG/identify_item",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_IDENTIFY_ITEM, "",
		cb_menu_spell, (void *)SPELL_KIND_IDENTIFY_ITEM,
		FLG_NULL,
	},

	{
		"/spell/MAG/identify_all_item",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_IDENTIFY_ALL_ITEM, "",
		cb_menu_spell, (void *)SPELL_KIND_IDENTIFY_ALL_ITEM,
		FLG_NULL,
	},

	{
		"/spell/MAG/searching",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SEARCHING, "",
		cb_menu_spell, (void *)SPELL_KIND_SEARCHING,
		FLG_NULL,
	},

	{
		"/spell/MAG/analyze_dweomer",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ANALYZE_DWEOMER, "",
		cb_menu_spell, (void *)SPELL_KIND_ANALYZE_DWEOMER,
		FLG_NULL,
	},

	{
		"/spell/MAG/detect_magic",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_MAGIC, "",
		cb_menu_spell, (void *)SPELL_KIND_DETECT_MAGIC,
		FLG_NULL,
	},

	{
		"/spell/MAG/detect_item",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_ITEM, "",
		cb_menu_spell, (void *)SPELL_KIND_DETECT_ITEM,
		FLG_NULL,
	},

	{
		"/spell/MAG/detect_doors",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_DOORS, "",
		cb_menu_spell, (void *)SPELL_KIND_DETECT_DOORS,
		FLG_NULL,
	},

	{
		"/spell/MAG/detect_traps",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_TRAPS, "",
		cb_menu_spell, (void *)SPELL_KIND_DETECT_TRAPS,
		FLG_NULL,
	},

	{
		"/spell/MAG/detect_monster",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DETECT_MONSTER, "",
		cb_menu_spell, (void *)SPELL_KIND_DETECT_MONSTER,
		FLG_NULL,
	},

	{
		"/spell/MAG/sense_invisible",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SENSE_INVISIBLE, "",
		cb_menu_spell, (void *)SPELL_KIND_SENSE_INVISIBLE,
		FLG_NULL,
	},

	{
		"/spell/MAG/no_learn detect",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/MAG/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [基本魔法] 状態変化 */
	{
		"/spell/MAG/title change status",
		"<Title>",
		'\0',
		"",
		N_MSG_MAG_CHANGE_STAT, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/MAG/fly",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FLY, "",
		cb_menu_spell, (void *)SPELL_KIND_FLY,
		FLG_NULL,
	},

	{
		"/spell/MAG/feather_fall",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FEATHER_FALL, "",
		cb_menu_spell, (void *)SPELL_KIND_FEATHER_FALL,
		FLG_NULL,
	},

	{
		"/spell/MAG/vanish",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_VANISH, "",
		cb_menu_spell, (void *)SPELL_KIND_VANISH,
		FLG_NULL,
	},

	{
		"/spell/MAG/darkvision",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DARKVISION, "",
		cb_menu_spell, (void *)SPELL_KIND_DARKVISION,
		FLG_NULL,
	},

	{
		"/spell/MAG/passwall",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_PASSWALL, "",
		cb_menu_spell, (void *)SPELL_KIND_PASSWALL,
		FLG_NULL,
	},

	{
		"/spell/MAG/dispel_magic",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DISPEL_MAGIC, "",
		cb_menu_spell, (void *)SPELL_KIND_DISPEL_MAGIC,
		FLG_NULL,
	},

	{
		"/spell/MAG/mirror_image",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MIRROR_IMAGE, "",
		cb_menu_spell, (void *)SPELL_KIND_MIRROR_IMAGE,
		FLG_NULL,
	},

	{
		"/spell/MAG/polymorph_other",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POLYMORPH_OTHER, "",
		cb_menu_spell, (void *)SPELL_KIND_POLYMORPH_OTHER,
		FLG_NULL,
	},

	{
		"/spell/MAG/polymorph_self",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POLYMORPH_SELF, "",
		cb_menu_spell, (void *)SPELL_KIND_POLYMORPH_SELF,
		FLG_NULL,
	},

	{
		"/spell/MAG/stealth",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STEALTH, "",
		cb_menu_spell, (void *)SPELL_KIND_STEALTH,
		FLG_NULL,
	},

	{
		"/spell/MAG/no_learn change status",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/MAG/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [戦闘魔法] */
	{
		"/spell/SOR",
		"<Branch>",
		'O',
		"",
		N_MSG_SOR, "",
		cb_menu_dflt_spell_sor, NULL,
		FLG_NULL,
	},
/* [戦闘魔法] 攻撃 */
	{
		"/spell/SOR/title attack",
		"<Title>",
		'\0',
		"",
		N_MSG_SOR_ATTACK, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/SOR/magic_missile",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MAGIC_MISSILE, "",
		cb_menu_spell, (void *)SPELL_KIND_MAGIC_MISSILE,
		FLG_NULL,
	},

	{
		"/spell/SOR/fire_ball",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FIRE_BALL, "",
		cb_menu_spell, (void *)SPELL_KIND_FIRE_BALL,
		FLG_NULL,
	},

	{
		"/spell/SOR/ice_blizzard",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ICE_BLIZZARD, "",
		cb_menu_spell, (void *)SPELL_KIND_ICE_BLIZZARD,
		FLG_NULL,
	},

	{
		"/spell/SOR/mind_storm",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MIND_STORM, "",
		cb_menu_spell, (void *)SPELL_KIND_MIND_STORM,
		FLG_NULL,
	},

	{
		"/spell/SOR/acid_rain",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ACID_RAIN, "",
		cb_menu_spell, (void *)SPELL_KIND_ACID_RAIN,
		FLG_NULL,
	},

	{
		"/spell/SOR/lightning_bolt",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_LIGHTNING_BOLT, "",
		cb_menu_spell, (void *)SPELL_KIND_LIGHTNING_BOLT,
		FLG_NULL,
	},

	{
		"/spell/SOR/poison_cloud",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POISON_CLOUD, "",
		cb_menu_spell, (void *)SPELL_KIND_POISON_CLOUD,
		FLG_NULL,
	},

	{
		"/spell/SOR/death_spell",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DEATH_SPELL, "",
		cb_menu_spell, (void *)SPELL_KIND_DEATH_SPELL,
		FLG_NULL,
	},

	{
		"/spell/SOR/word_of_destruction",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WORD_OF_DESTRUCTION, "",
		cb_menu_spell, (void *)SPELL_KIND_WORD_OF_DESTRUCTION,
		FLG_NULL,
	},
	{
		"/spell/SOR/no_learn attack",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/SOR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [戦闘魔法] 防御 */
	{
		"/spell/SOR/title defense",
		"<Title>",
		'\0',
		"",
		N_MSG_SOR_DEFENSE, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/SOR/magic_shield",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MAGIC_SHIELD, "",
		cb_menu_spell, (void *)SPELL_KIND_MAGIC_SHIELD,
		FLG_NULL,
	},

	{
		"/spell/SOR/mage_armor",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MAGE_ARMOR, "",
		cb_menu_spell, (void *)SPELL_KIND_MAGE_ARMOR,
		FLG_NULL,
	},

	{
		"/spell/SOR/stoneskin",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STONESKIN, "",
		cb_menu_spell, (void *)SPELL_KIND_STONESKIN,
		FLG_NULL,
	},

	{
		"/spell/SOR/iron_body",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_IRON_BODY, "",
		cb_menu_spell, (void *)SPELL_KIND_IRON_BODY,
		FLG_NULL,
	},

	{
		"/spell/SOR/spell_resistance",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SPELL_RESISTANCE, "",
		cb_menu_spell, (void *)SPELL_KIND_SPELL_RESISTANCE,
		FLG_NULL,
	},

	{
		"/spell/SOR/counter_magic",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_COUNTER_MAGIC, "",
		cb_menu_spell, (void *)SPELL_KIND_COUNTER_MAGIC,
		FLG_NULL,
	},

	{
		"/spell/SOR/no_learn defense",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/SOR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [戦闘魔法] 状態異常 */
	{
		"/spell/SOR/title weaken status",
		"<Title>",
		'\0',
		"",
		N_MSG_SOR_WEAKEN_STAT, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/SOR/stone",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STONE, "",
		cb_menu_spell, (void *)SPELL_KIND_STONE,
		FLG_NULL,
	},

	{
		"/spell/SOR/paralyze",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_PARALYZE, "",
		cb_menu_spell, (void *)SPELL_KIND_PARALYZE,
		FLG_NULL,
	},

	{
		"/spell/SOR/poison",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POISON, "",
		cb_menu_spell, (void *)SPELL_KIND_POISON,
		FLG_NULL,
	},

	{
		"/spell/SOR/confusion",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CONFUSION, "",
		cb_menu_spell, (void *)SPELL_KIND_CONFUSION,
		FLG_NULL,
	},

	{
		"/spell/SOR/blindness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_BLINDNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_BLINDNESS,
		FLG_NULL,
	},

	{
		"/spell/SOR/sleep",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SLEEP, "",
		cb_menu_spell, (void *)SPELL_KIND_SLEEP,
		FLG_NULL,
	},

	{
		"/spell/SOR/silence",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SILENCE, "",
		cb_menu_spell, (void *)SPELL_KIND_SILENCE,
		FLG_NULL,
	},

	{
		"/spell/SOR/fear",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FEAR, "",
		cb_menu_spell, (void *)SPELL_KIND_FEAR,
		FLG_NULL,
	},

	{
		"/spell/SOR/hallucination",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_HALLUCINATION, "",
		cb_menu_spell, (void *)SPELL_KIND_HALLUCINATION,
		FLG_NULL,
	},

	{
		"/spell/SOR/charm",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CHARM, "",
		cb_menu_spell, (void *)SPELL_KIND_CHARM,
		FLG_NULL,
	},

	{
		"/spell/SOR/no_learn weaken status",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/SOR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [援護魔法] */
	{
		"/spell/ENC",
		"<Branch>",
		'E',
		"",
		N_MSG_ENC, "",
		cb_menu_dflt_spell_enc, NULL,
		FLG_NULL,
	},
/* [援護魔法] 能力値強化 */
	{
		"/spell/ENC/title strengthen ability",
		"<Title>",
		'\0',
		"",
		N_MSG_ENC_STRENGTHEN_ABL, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/ENC/sharpness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SHARPNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_SHARPNESS,
		FLG_NULL,
	},

	{
		"/spell/ENC/strength",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_STRENGTH, "",
		cb_menu_spell, (void *)SPELL_KIND_STRENGTH,
		FLG_NULL,
	},

	{
		"/spell/ENC/quickness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_QUICKNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_QUICKNESS,
		FLG_NULL,
	},

	{
		"/spell/ENC/brainy",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_BRAINY, "",
		cb_menu_spell, (void *)SPELL_KIND_BRAINY,
		FLG_NULL,
	},

	{
		"/spell/ENC/wise",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WISE, "",
		cb_menu_spell, (void *)SPELL_KIND_WISE,
		FLG_NULL,
	},

	{
		"/spell/ENC/attractive",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ATTRACTIVE, "",
		cb_menu_spell, (void *)SPELL_KIND_ATTRACTIVE,
		FLG_NULL,
	},

	{
		"/spell/ENC/no_learn strengthen ability",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/ENC/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [援護魔法] 強化 */
	{
		"/spell/ENC/title strengthen misc",
		"<Title>",
		'\0',
		"",
		N_MSG_ENC_STRENGTHEN_MISC, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/ENC/power_up_hp",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_POWER_UP_HP, "",
		cb_menu_spell, (void *)SPELL_KIND_POWER_UP_HP,
		FLG_NULL,
	},

	{
		"/spell/ENC/haste",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_HASTE, "",
		cb_menu_spell, (void *)SPELL_KIND_HASTE,
		FLG_NULL,
	},

	{
		"/spell/ENC/no_learn strengthen misc",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/ENC/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [援護魔法] 能力値弱体 */
	{
		"/spell/ENC/title weaken ability",
		"<Title>",
		'\0',
		"",
		N_MSG_ENC_WEAKEN_ABL, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/ENC/dullness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DULLNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_DULLNESS,
		FLG_NULL,
	},

	{
		"/spell/ENC/weakness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WEAKNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_WEAKNESS,
		FLG_NULL,
	},

	{
		"/spell/ENC/slowness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SLOWNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_SLOWNESS,
		FLG_NULL,
	},

	{
		"/spell/ENC/brainless",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_BRAINLESS, "",
		cb_menu_spell, (void *)SPELL_KIND_BRAINLESS,
		FLG_NULL,
	},

	{
		"/spell/ENC/foolish",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_FOOLISH, "",
		cb_menu_spell, (void *)SPELL_KIND_FOOLISH,
		FLG_NULL,
	},

	{
		"/spell/ENC/unattractive",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_UNATTRACTIVE, "",
		cb_menu_spell, (void *)SPELL_KIND_UNATTRACTIVE,
		FLG_NULL,
	},

	{
		"/spell/ENC/no_learn weaken ability",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/ENC/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [援護魔法] 弱体 */
	{
		"/spell/ENC/title weaken misc",
		"<Title>",
		'\0',
		"",
		N_MSG_ENC_WEAKEN_MISC, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/ENC/energy_drain",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ENERGY_DRAIN, "",
		cb_menu_spell, (void *)SPELL_KIND_ENERGY_DRAIN,
		FLG_NULL,
	},

	{
		"/spell/ENC/slow",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SLOW, "",
		cb_menu_spell, (void *)SPELL_KIND_SLOW,
		FLG_NULL,
	},

	{
		"/spell/ENC/hunger",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_HUNGER, "",
		cb_menu_spell, (void *)SPELL_KIND_HUNGER,
		FLG_NULL,
	},

	{
		"/spell/ENC/cancellation",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CANCELLATION, "",
		cb_menu_spell, (void *)SPELL_KIND_CANCELLATION,
		FLG_NULL,
	},

	{
		"/spell/ENC/no_learn weaken misc",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/ENC/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [召喚魔法] */
	{
		"/spell/SUM",
		"<Branch>",
		'U',
		"",
		N_MSG_SUM, "",
		cb_menu_dflt_spell_sum, NULL,
		FLG_NULL,
	},
/* [召喚魔法] 召喚 */
	{
		"/spell/SUM/title summon",
		"<Title>",
		'\0',
		"",
		N_MSG_SUM_SUMMON, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/SUM/skeleton_warrior",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SKELETON_WARRIOR, "",
		cb_menu_spell, (void *)SPELL_KIND_SKELETON_WARRIOR,
		FLG_NULL,
	},

	{
		"/spell/SUM/summon_unicorn",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_UNICORN, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_UNICORN,
		FLG_NULL,
	},

	{
		"/spell/SUM/summon_efreet",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_EFREET, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_EFREET,
		FLG_NULL,
	},

	{
		"/spell/SUM/summon_djinni",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_DJINNI, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_DJINNI,
		FLG_NULL,
	},

	{
		"/spell/SUM/summon_phoenix",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_PHOENIX, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_PHOENIX,
		FLG_NULL,
	},

	{
		"/spell/SUM/summon_bone",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_BONE, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_BONE,
		FLG_NULL,
	},

	{
		"/spell/SUM/summon_random",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_RANDOM, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_RANDOM,
		FLG_NULL,
	},

	{
		"/spell/SUM/create_undead",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CREATE_UNDEAD, "",
		cb_menu_spell, (void *)SPELL_KIND_CREATE_UNDEAD,
		FLG_NULL,
	},

	{
		"/spell/SUM/dismissal",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DISMISSAL, "",
		cb_menu_spell, (void *)SPELL_KIND_DISMISSAL,
		FLG_NULL,
	},

	{
		"/spell/SUM/no_learn summon",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/SUM/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [僧侶呪文] */
	{
		"/spell/PRI",
		"<Branch>",
		'P',
		"",
		N_MSG_PRI, "",
		cb_menu_dflt_spell_pri, NULL,
		FLG_NULL,
	},
/* [僧侶呪文] 回復 */
	{
		"/spell/PRI/title cure",
		"<Title>",
		'\0',
		"",
		N_MSG_PRI_CURE, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_hp_light",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_HP_LIGHT, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_HP_LIGHT,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_hp_moderate",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_HP_MODERATE, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_HP_MODERATE,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_hp_serious",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_HP_SERIOUS, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_HP_SERIOUS,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_hp_max",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_HP_MAX, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_HP_MAX,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_mp",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_MP, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_MP,
		FLG_NULL,
	},

	{
		"/spell/PRI/transfer_mp",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_TRANSFER_MP, "",
		cb_menu_spell, (void *)SPELL_KIND_TRANSFER_MP,
		FLG_NULL,
	},

	{
		"/spell/PRI/regeneration",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_REGENERATION, "",
		cb_menu_spell, (void *)SPELL_KIND_REGENERATION,
		FLG_NULL,
	},

	{
		"/spell/PRI/restore_experience",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RESTORE_EXPERIENCE, "",
		cb_menu_spell, (void *)SPELL_KIND_RESTORE_EXPERIENCE,
		FLG_NULL,
	},

	{
		"/spell/PRI/resurrection",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RESURRECTION, "",
		cb_menu_spell, (void *)SPELL_KIND_RESURRECTION,
		FLG_NULL,
	},

	{
		"/spell/PRI/heal",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_HEAL, "",
		cb_menu_spell, (void *)SPELL_KIND_HEAL,
		FLG_NULL,
	},

	{
		"/spell/PRI/no_learn cure",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/PRI/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [僧侶呪文] 状態回復 */
	{
		"/spell/PRI/title cure status",
		"<Title>",
		'\0',
		"",
		N_MSG_PRI_CURE_STAT, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_status",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_STATUS, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_STATUS,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_stone",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_STONE, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_STONE,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_paralyze",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_PARALYZE, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_PARALYZE,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_blindness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_BLINDNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_BLINDNESS,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_poison",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_POISON, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_POISON,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_confusion",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_CONFUSION, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_CONFUSION,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_silence",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_SILENCE, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_SILENCE,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_sleep",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_SLEEP, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_SLEEP,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_fear",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_FEAR, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_FEAR,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_hallucination",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_HALLUCINATION, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_HALLUCINATION,
		FLG_NULL,
	},

	{
		"/spell/PRI/cure_charm",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CURE_CHARM, "",
		cb_menu_spell, (void *)SPELL_KIND_CURE_CHARM,
		FLG_NULL,
	},

	{
		"/spell/PRI/no_learn cure status",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/PRI/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [僧侶呪文] 抵抗 */
	{
		"/spell/PRI/title resist",
		"<Title>",
		'\0',
		"",
		N_MSG_PRI_RESIST, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/PRI/protection",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_PROTECTION, "",
		cb_menu_spell, (void *)SPELL_KIND_PROTECTION,
		FLG_NULL,
	},

	{
		"/spell/PRI/resist_physical",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RESIST_PHYSICAL, "",
		cb_menu_spell, (void *)SPELL_KIND_RESIST_PHYSICAL,
		FLG_NULL,
	},

	{
		"/spell/PRI/resist_heat",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RESIST_HEAT, "",
		cb_menu_spell, (void *)SPELL_KIND_RESIST_HEAT,
		FLG_NULL,
	},

	{
		"/spell/PRI/resist_cold",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RESIST_COLD, "",
		cb_menu_spell, (void *)SPELL_KIND_RESIST_COLD,
		FLG_NULL,
	},

	{
		"/spell/PRI/resist_mind",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RESIST_MIND, "",
		cb_menu_spell, (void *)SPELL_KIND_RESIST_MIND,
		FLG_NULL,
	},

	{
		"/spell/PRI/resist_acid",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RESIST_ACID, "",
		cb_menu_spell, (void *)SPELL_KIND_RESIST_ACID,
		FLG_NULL,
	},

	{
		"/spell/PRI/resist_electricity",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RESIST_ELECTRICITY, "",
		cb_menu_spell, (void *)SPELL_KIND_RESIST_ELECTRICITY,
		FLG_NULL,
	},

	{
		"/spell/PRI/resist_poison",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RESIST_POISON, "",
		cb_menu_spell, (void *)SPELL_KIND_RESIST_POISON,
		FLG_NULL,
	},

	{
		"/spell/PRI/no_learn resist",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/PRI/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [僧侶呪文] 神聖 */
	{
		"/spell/PRI/title holy",
		"<Title>",
		'\0',
		"",
		N_MSG_PRI_HOLY, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/PRI/bless",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_BLESS, "",
		cb_menu_spell, (void *)SPELL_KIND_BLESS,
		FLG_NULL,
	},

	{
		"/spell/PRI/remove_curse",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_REMOVE_CURSE, "",
		cb_menu_spell, (void *)SPELL_KIND_REMOVE_CURSE,
		FLG_NULL,
	},

	{
		"/spell/PRI/dispel_undead",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DISPEL_UNDEAD, "",
		cb_menu_spell, (void *)SPELL_KIND_DISPEL_UNDEAD,
		FLG_NULL,
	},

	{
		"/spell/PRI/escape",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_ESCAPE, "",
		cb_menu_spell, (void *)SPELL_KIND_ESCAPE,
		FLG_NULL,
	},

	{
		"/spell/PRI/sanctuary",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SANCTUARY, "",
		cb_menu_spell, (void *)SPELL_KIND_SANCTUARY,
		FLG_NULL,
	},

	{
		"/spell/PRI/wish",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WISH, "",
		cb_menu_spell, (void *)SPELL_KIND_WISH,
		FLG_NULL,
	},

	{
		"/spell/PRI/no_learn holy",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/PRI/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [精霊術]  */
	{
		"/spell/SHA",
		"<Branch>",
		'H',
		"",
		N_MSG_SHA, "",
		cb_menu_dflt_spell_sha, NULL,
		FLG_NULL,
	},
/* [精霊術] 攻撃 */
	{
		"/spell/SHA/title weak elemental",
		"<Title>",
		'\0',
		"",
		N_MSG_SHA_WEAK, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/SHA/weak_fire_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WEAK_FIRE_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_WEAK_FIRE_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/weak_water_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WEAK_WATER_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_WEAK_WATER_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/weak_air_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WEAK_AIR_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_WEAK_AIR_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/weak_earth_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WEAK_EARTH_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_WEAK_EARTH_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/weak_light_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WEAK_LIGHT_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_WEAK_LIGHT_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/weak_dark_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_WEAK_DARK_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_WEAK_DARK_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/no_learn weak elemental",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/SHA/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [精霊術] 召喚 */
	{
		"/spell/SHA/title summon elemental",
		"<Title>",
		'\0',
		"",
		N_MSG_SHA_SUMMON, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_fire_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_FIRE_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_FIRE_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_water_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_WATER_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_WATER_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_air_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_AIR_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_AIR_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_earth_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_EARTH_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_EARTH_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_will_o_wisp",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_WILL_O_WISP, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_WILL_O_WISP,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_shade",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_SHADE, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_SHADE,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_salamander",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_SALAMANDER, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_SALAMANDER,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_undine",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_UNDINE, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_UNDINE,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_sylph",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_SYLPH, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_SYLPH,
		FLG_NULL,
	},

	{
		"/spell/SHA/summon_gnome",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUMMON_GNOME, "",
		cb_menu_spell, (void *)SPELL_KIND_SUMMON_GNOME,
		FLG_NULL,
	},

	{
		"/spell/SHA/dismissal_elemental",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_DISMISSAL_ELEMENTAL, "",
		cb_menu_spell, (void *)SPELL_KIND_DISMISSAL_ELEMENTAL,
		FLG_NULL,
	},

	{
		"/spell/SHA/no_learn summon elemental",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/SHA/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [呪歌]  */
	{
		"/spell/BAR",
		"<Branch>",
		'B',
		"",
		N_MSG_BAR, "",
		cb_menu_dflt_spell_bar, NULL,
		FLG_NULL,
	},
/* [呪歌] 回復 */
	{
		"/spell/BAR/title cure",
		"<Title>",
		'\0',
		"",
		N_MSG_BAR_CURE, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_cure_hp",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_CURE_HP, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_CURE_HP,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_cure_mp",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_CURE_MP, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_CURE_MP,
		FLG_NULL,
	},

	{
		"/spell/BAR/no_learn cure",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/BAR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [呪歌] 能力値強化 */
	{
		"/spell/BAR/title strengthen ability",
		"<Title>",
		'\0',
		"",
		N_MSG_BAR_STRENGTHEN_ABL, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_sharpness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_SHARPNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_SHARPNESS,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_strength",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_STRENGTH, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_STRENGTH,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_quickness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_QUICKNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_QUICKNESS,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_brainy",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_BRAINY, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_BRAINY,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_wise",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_WISE, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_WISE,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_attractive",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_ATTRACTIVE, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_ATTRACTIVE,
		FLG_NULL,
	},

	{
		"/spell/BAR/no_learn strengthen ability",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/BAR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [呪歌] 能力値弱体 */
	{
		"/spell/BAR/title weaken ability",
		"<Title>",
		'\0',
		"",
		N_MSG_BAR_WEAKEN_ABL, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_dullness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_DULLNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_DULLNESS,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_weakness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_WEAKNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_WEAKNESS,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_slowness",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_SLOWNESS, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_SLOWNESS,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_brainless",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_BRAINLESS, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_BRAINLESS,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_foolish",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_FOOLISH, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_FOOLISH,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_unattractive",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_UNATTRACTIVE, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_UNATTRACTIVE,
		FLG_NULL,
	},

	{
		"/spell/BAR/no_learn weaken ability",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/BAR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [呪歌] 状態抵抗 */
	{
		"/spell/BAR/title resist status",
		"<Title>",
		'\0',
		"",
		N_MSG_BAR_RESI_STAT, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_stone",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_STONE, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_STONE,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_paralyze",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_PARALYZE, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_PARALYZE,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_poison",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_POISON, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_POISON,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_confusion",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_CONFUSION, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_CONFUSION,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_blind",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_BLIND, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_BLIND,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_sleep",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_SLEEP, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_SLEEP,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_silence",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_SILENCE, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_SILENCE,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_fear",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_FEAR, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_FEAR,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_hallucination",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_HALLUCINATION, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_HALLUCINATION,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_charm",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_CHARM, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_CHARM,
		FLG_NULL,
	},

	{
		"/spell/BAR/song_resi_stat_drunk",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SONG_RESI_STAT_DRUNK, "",
		cb_menu_spell, (void *)SPELL_KIND_SONG_RESI_STAT_DRUNK,
		FLG_NULL,
	},

	{
		"/spell/BAR/no_learn resist status",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/BAR/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [忍術] */
	{
		"/spell/NIN",
		"<Branch>",
		'N',
		"",
		N_MSG_NIN, "",
		cb_menu_dflt_spell_nin, NULL,
		FLG_NULL,
	},
/* [忍術] 天変地異 */
	{
		"/spell/NIN/title disaster",
		"<Title>",
		'\0',
		"",
		N_MSG_NIN_DISASTER, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/NIN/typhoon",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_TYPHOON, "",
		cb_menu_spell, (void *)SPELL_KIND_TYPHOON,
		FLG_NULL,
	},

	{
		"/spell/NIN/conflagration",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_CONFLAGRATION, "",
		cb_menu_spell, (void *)SPELL_KIND_CONFLAGRATION,
		FLG_NULL,
	},

	{
		"/spell/NIN/earthquake",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_EARTHQUAKE, "",
		cb_menu_spell, (void *)SPELL_KIND_EARTHQUAKE,
		FLG_NULL,
	},

	{
		"/spell/NIN/thundercloud",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_THUNDERCLOUD, "",
		cb_menu_spell, (void *)SPELL_KIND_THUNDERCLOUD,
		FLG_NULL,
	},

	{
		"/spell/NIN/inundation",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_INUNDATION, "",
		cb_menu_spell, (void *)SPELL_KIND_INUNDATION,
		FLG_NULL,
	},

	{
		"/spell/NIN/no_learn disaster",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/NIN/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/* [忍術] 体術 */
	{
		"/spell/NIN/title misc",
		"<Title>",
		'\0',
		"",
		N_MSG_NIN_MISC, "",
		NULL, NULL,
		FLG_NULL,
	},

	{
		"/spell/NIN/substitute",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_SUBSTITUTE, "",
		cb_menu_spell, (void *)SPELL_KIND_SUBSTITUTE,
		FLG_NULL,
	},

	{
		"/spell/NIN/burning_hands",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_BURNING_HANDS, "",
		cb_menu_spell, (void *)SPELL_KIND_BURNING_HANDS,
		FLG_NULL,
	},

	{
		"/spell/NIN/rally",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_RALLY, "",
		cb_menu_spell, (void *)SPELL_KIND_RALLY,
		FLG_NULL,
	},

	{
		"/spell/NIN/iron_man",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_IRON_MAN, "",
		cb_menu_spell, (void *)SPELL_KIND_IRON_MAN,
		FLG_NULL,
	},

	{
		"/spell/NIN/mind_reading",
		"<Branch>",
		'\0',
		"",
		N_MSG_SPELL_MIND_READING, "",
		cb_menu_spell, (void *)SPELL_KIND_MIND_READING,
		FLG_NULL,
	},

	{
		"/spell/NIN/no_learn misc",
		"<Item>",
		ACCEL_KEY_NO_LEARN,
		"",
		N_MSG_SPELL_NO_LEARN, "",
		cb_menu_spell_no_learn, NULL,
		FLG_NULL,
	},

	{
		"/spell/NIN/--",
		"<PageSeparator>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
/**/
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

menu_t	ls_menu_spell_extent[] = {
	{
		"/spell extent",
		"<Branch>",
		'\0',
		"",
		N_MSG_NULL, "",
		NULL, NULL,
		FLG_NULL,
	},
	{
		"/spell extent/normal",
		"<Item>",
		'N',
		"",
		N_MSG_MENU_SPELL_EXTENT_NORMAL, "",
		cb_menu_spell_extent, (void *)EXTENT_KIND_NORMAL,
		FLG_NULL,
	},
	{
		"/spell extent/spread",
		"<Item>",
		'S',
		"",
		N_MSG_MENU_SPELL_EXTENT_SPREAD, "",
		cb_menu_spell_extent, (void *)EXTENT_KIND_SPREAD,
		FLG_NULL,
	},
	{
		"/spell extent/mass",
		"<Item>",
		'M',
		"",
		N_MSG_MENU_SPELL_EXTENT_MASS, "",
		cb_menu_spell_extent, (void *)EXTENT_KIND_MASS,
		FLG_NULL,
	},
	{
		"/spell extent/limit",
		"<Item>",
		'H',
		"",
		N_MSG_MENU_SPELL_EXTENT_LIMIT, "",
		cb_menu_spell_extent, (void *)EXTENT_KIND_LIMIT,
		FLG_NULL,
	},
	{
		"/spell extent/half",
		"<Item>",
		'H',
		"",
		N_MSG_MENU_SPELL_EXTENT_HALF, "",
		cb_menu_spell_extent, (void *)EXTENT_KIND_HALF,
		FLG_NULL,
	},
	{
		"/spell extent/double",
		"<Item>",
		'D',
		"",
		N_MSG_MENU_SPELL_EXTENT_DOUBLE, "",
		cb_menu_spell_extent, (void *)EXTENT_KIND_DOUBLE,
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

#endif	/* SPELL_TAB_H */
