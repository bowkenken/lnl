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
* $Id: last-boss-tab.h,v 1.18 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	LAST_BOSS_TAB_H
#define	LAST_BOSS_TAB_H

/***************************************************************
* ラスボスのデータ・テーブル
***************************************************************/

/* ラスト・ステージで使用不可の呪文 */

static const spell_kind_t	last_boss_no_spell_ls[] = {
/* MAG */
	SPELL_KIND_SHORT_TELEPORT_PARTY,
	SPELL_KIND_TELEPORT_PARTY,
	SPELL_KIND_TELEPORT,
	SPELL_KIND_RECALL,
	SPELL_KIND_SEARCHING,
	SPELL_KIND_DETECT_DOORS,
	SPELL_KIND_FLY,
	SPELL_KIND_PASSWALL,
/* SOR */
/* ENC */
/* SUM */
/* PRI */
	SPELL_KIND_ESCAPE,
	SPELL_KIND_SANCTUARY,
/* SHA */
/* BAR */
/* NIN */
/* ANC */
/* end */
	SPELL_KIND_NULL,
};

/***************************************************************
* ラスボスのパターン
***************************************************************/

static const char	g_transmit_chr = '@';
static const char	g_joint_chr = '&';

#define	JOINT_CHR_END	'\0'
#define	JOINT_CHR_SKULL_TO_JAW	'h'
#define	JOINT_CHR_JAW_TO_SKULL	'h'
#define	JOINT_CHR_JAW_TO_SKULL_OPEN	'j'
#define	JOINT_CHR_SKULL_TO_BODY	'h'
#define	JOINT_CHR_BODY_TO_UPPER_ARM_LEFT	'l'
#define	JOINT_CHR_BODY_TO_UPPER_ARM_RIGHT	'r'
#define	JOINT_CHR_UPPER_ARM_TO_FORE_ARM_LEFT	'm'
#define	JOINT_CHR_UPPER_ARM_TO_FORE_ARM_RIGHT	's'
#define	JOINT_CHR_UPPER_ARM_TO_FORE_ARM_SLAP_LEFT	'm'
#define	JOINT_CHR_UPPER_ARM_TO_FORE_ARM_SLAP_RIGHT	's'
#define	JOINT_CHR_FORE_ARM_TO_HAND_LEFT	'n'
#define	JOINT_CHR_FORE_ARM_TO_HAND_RIGHT	't'
#define	JOINT_CHR_FORE_ARM_TO_HAND_SLAP_LEFT	'o'
#define	JOINT_CHR_FORE_ARM_TO_HAND_SLAP_RIGHT	'u'
#define	JOINT_CHR_ATTACK_SKULL	'A'
#define	JOINT_CHR_ATTACK_JAW	'B'

static last_boss_parts_t	last_boss_parts_skull = {
	{
		{ JOINT_CHR_SKULL_TO_JAW, '_', '_', 0, 0, },
		{ JOINT_CHR_SKULL_TO_BODY, '_', '_', 0, 0, },
		{ JOINT_CHR_ATTACK_SKULL, 'X', 'X', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		"@@__________@@",
		" /          \\ ",
		"/     &A     \\",
		"| ___    ___ |",
		"||   |  |   ||",
		"||__/ /\\ \\__||",
		"\\__   --   __/",
		"@@ |__&h__| @@",
		"@@@@VVVVVV@@@@",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_jaw = {
	{
		{ JOINT_CHR_JAW_TO_SKULL, ' ', ' ', 0, 0, },
		{ JOINT_CHR_JAW_TO_SKULL_OPEN, ' ', ' ', 0, 0, },
		{ JOINT_CHR_ATTACK_JAW, ' ', ' ', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		" |    &j    | ",
		" |    &h    | ",
		" |\\   &B   /| ",
		"@@\\\\AAAAAA//@@",
		"@@ \\______/ @@",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_body = {
	{
		{ JOINT_CHR_SKULL_TO_BODY, '_', '_', 0, 0, },
		{ JOINT_CHR_BODY_TO_UPPER_ARM_LEFT, ' ', ' ', 0, 0, },
		{ JOINT_CHR_BODY_TO_UPPER_ARM_RIGHT, ' ', ' ', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		"@@@@@@@@@@@@@@@@@@<|&h|>@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@<|__|>@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@<|__|>@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@<|__|>@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@<|__|>@@@@@@@@@@@@@@@@@@",
		"@@__@@@@@@@@@@@@@@<|__|>@@@@@@@@@@@@@@__@@",
		" /  \\==============|__|==============/  \\ ",
		"| &r |--/|   \\====|____|====/   |\\--| &l |",
		" \\__/   ||\\________|  |________/||   \\__/ ",
		"@@@@\\   | \\--------|  |--------/ |   /@@@@",
		"@@@@ \\ ||\\_________|  |_________/|| / @@@@",
		"@@@@@@\\| \\---------|  |---------/ |/@@@@@@",
		"@@@@@@ |\\_________/|  |\\_________/| @@@@@@",
		"@@@@@@| \\---------/|  |\\---------/ |@@@@@@",
		"@@@@@@|\\__________/|  |\\__________/|@@@@@@",
		"@@@@@@|\\----------/ \\/ \\----------/|@@@@@@",
		"@@@@@@|\\_________/=|__|=\\_________/|@@@@@@",
		"@@@@@@|\\--------/ @@==@@ \\--------/|@@@@@@",
		"@@@@@@|\\_______/ ==|__|== \\_______/|@@@@@@",
		"@@@@@@|\\------/ @@@@==@@@@ \\------/|@@@@@@",
		"@@@@@@ |\\____/@@===|__|===@@\\____/| @@@@@@",
		"@@@@@@@@\\---/ @@@@@@==@@@@@@ \\---/@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@=|__|=@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@@@==@@@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@=|__|=@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@@@==@@@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@=|__|=@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@@@==@@@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@=|__|=@@@@@@@@@@@@@@@@@@",
		"@@@@@@@@@@@@@@@@@@@@~~@@@@@@@@@@@@@@@@@@@@",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_upper_arm_left = {
	{
		{ JOINT_CHR_BODY_TO_UPPER_ARM_LEFT, ' ', ' ', 0, 0, },
		{ JOINT_CHR_UPPER_ARM_TO_FORE_ARM_LEFT, ' ', '/', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		"@@ __ @@@@@@@@@@@@@@",
		"@@/  \\@@@@@@@@@@@@@@",
		" |&l  | @@@@@@@@@@@@",
		"@@\\_  \\ @@@@@@@@@@@@",
		"@@@@\\  \\@@@@@@@@@@@@",
		"@@@@ \\  \\ @@@@@@@@@@",
		"@@@@@@\\  \\@@@@@@@@@@",
		"@@@@@@ \\  \\ @@@@@@@@",
		"@@@@@@@@\\  \\@@@@@@@@",
		"@@@@@@@@ \\  \\ @@@@@@",
		"@@@@@@@@@@\\  \\@@@@@@",
		"@@@@@@@@@@ \\  \\ @@@@",
		"@@@@@@@@@@@@\\  \\_ @@",
		"@@@@@@@@@@@@ \\   \\@@",
		"@@@@@@@@@@@@ |  &m@@",
		"@@@@@@@@@@@@@@\\_/ @@",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_fore_arm_left = {
	{
		{ JOINT_CHR_UPPER_ARM_TO_FORE_ARM_LEFT, '|', ' ', 0, 0, },
		{ JOINT_CHR_FORE_ARM_TO_HAND_LEFT, ' ', '_', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		"&n_ ",
		"|\\ |",
		"|| |",
		"|| |",
		"|| |",
		"|| |",
		"|| |",
		"|| |",
		"|| |",
		"\\| |",
		"|  |",
		"| |\\",
		"| ||",
		"| ||",
		"&m||",
		"\\_//",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_hand_left = {
	{
		{ JOINT_CHR_FORE_ARM_TO_HAND_LEFT, 'O', 'O', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		"@@@@@@|\\|\\@@@@",
		"@@|\\@@||||@@/|",
		"@@ \\\\ |||| // ",
		"@@@@\\\\||||//@@",
		"@@___\\oooo@@@@",
		" \\----&nOO@@@@",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_fore_arm_slap_left = {
	{
		{ JOINT_CHR_UPPER_ARM_TO_FORE_ARM_SLAP_LEFT,
			' ', '|', 0, 0, },
		{ JOINT_CHR_FORE_ARM_TO_HAND_SLAP_LEFT,
			' ', '\\', 0, 0, },
		{ JOINT_CHR_END,
			' ', ' ', 0, 0, },
	},
	{
		"@@__@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
		" /&o\\__ @@@@@@@@@@@@@@@@@@@@@@@@",
		" \\__  \\\\__@@@@@@@@@@@@@@@@@@@@@@",
		"@@@@\\__  \\\\__ @@@@@@@@@@@@@@@@@@",
		"@@@@@@ \\__  \\\\__@@@@@@@@@@@@@@@@",
		"@@@@@@@@  \\__  \\\\__ @@@@@@@@@@@@",
		"@@@@@@@@@@@@ \\__   \\__@@@@@@@@@@",
		"@@@@@@@@@@@@@@  \\___   \\__@@@@@@",
		"@@@@@@@@@@@@@@@@@@ \\\\__   \\__ @@",
		"@@@@@@@@@@@@@@@@@@@@  \\\\__   \\@@",
		"@@@@@@@@@@@@@@@@@@@@@@@@ \\\\ &m@@",
		"@@@@@@@@@@@@@@@@@@@@@@@@@@\\-- @@",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_hand_slap_left = {
	{
		{ JOINT_CHR_FORE_ARM_TO_HAND_SLAP_LEFT, 'O', 'O', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		"@@@@@@|\\@@@@",
		"@@|\\@@||@@@@",
		" |\\\\\\ || /| ",
		"@@\\\\\\\\||//@@",
		"___\\\\oooO @@",
		"\\----o&oO @@",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_upper_arm_right = {
	{
		{ JOINT_CHR_BODY_TO_UPPER_ARM_RIGHT, ' ', ' ', 0, 0, },
		{ JOINT_CHR_UPPER_ARM_TO_FORE_ARM_RIGHT, '\\', ' ', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		"@@@@@@@@@@@@@@ __ @@",
		"@@@@@@@@@@@@@@/  \\@@",
		"@@@@@@@@@@@@ |  &r| ",
		"@@@@@@@@@@@@ /  _/@@",
		"@@@@@@@@@@@@/  /@@@@",
		"@@@@@@@@@@ /  / @@@@",
		"@@@@@@@@@@/  /@@@@@@",
		"@@@@@@@@ /  / @@@@@@",
		"@@@@@@@@/  /@@@@@@@@",
		"@@@@@@ /  / @@@@@@@@",
		"@@@@@@/  /@@@@@@@@@@",
		"@@@@ /  / @@@@@@@@@@",
		"@@ _/  /@@@@@@@@@@@@",
		"@@/   / @@@@@@@@@@@@",
		"@@&s  | @@@@@@@@@@@@",
		"@@ \\_/@@@@@@@@@@@@@@",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_fore_arm_right = {
	{
		{ JOINT_CHR_UPPER_ARM_TO_FORE_ARM_RIGHT, '_', '/', 0, 0, },
		{ JOINT_CHR_FORE_ARM_TO_HAND_RIGHT, '_', ' ', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		" _&t",
		"| /|",
		"| ||",
		"| ||",
		"| ||",
		"| ||",
		"| ||",
		"| ||",
		"| ||",
		"| |/",
		"|  |",
		"/| |",
		"|| |",
		"|| |",
		"||&s",
		"\\\\_/",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_hand_right = {
	{
		{ JOINT_CHR_FORE_ARM_TO_HAND_RIGHT, 'O', 'O', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		"@@@@/|/|@@@@@@",
		"|\\@@||||@@/|@@",
		" \\\\ |||| // @@",
		"@@\\\\||||//@@@@",
		"@@@@oooo/___@@",
		"@@@@OO&t----/ ",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_fore_arm_slap_right = {
	{
		{ JOINT_CHR_UPPER_ARM_TO_FORE_ARM_SLAP_RIGHT,
			'|', ' ', 0, 0, },
		{ JOINT_CHR_FORE_ARM_TO_HAND_SLAP_RIGHT,
			'/', ' ', 0, 0, },
		{ JOINT_CHR_END,
			' ', ' ', 0, 0, },
	},
	{
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@__@@",
		"@@@@@@@@@@@@@@@@@@@@@@@@ __/&u\\ ",
		"@@@@@@@@@@@@@@@@@@@@@@__//  __/ ",
		"@@@@@@@@@@@@@@@@@@ __//  __/@@@@",
		"@@@@@@@@@@@@@@@@__//  __/ @@@@@@",
		"@@@@@@@@@@@@ __//  __/@@@@@@@@@@",
		"@@@@@@@@@@__/   __/ @@@@@@@@@@@@",
		"@@@@@@ __/  ___/@@@@@@@@@@@@@@@@",
		"@@@@__/  __// @@@@@@@@@@@@@@@@@@",
		"@@ /  __//@@@@@@@@@@@@@@@@@@@@@@",
		"@@&s // @@@@@@@@@@@@@@@@@@@@@@@@",
		"@@ --/@@@@@@@@@@@@@@@@@@@@@@@@@@",
		NULL,
	},
};

static last_boss_parts_t	last_boss_parts_hand_slap_right = {
	{
		{ JOINT_CHR_FORE_ARM_TO_HAND_SLAP_RIGHT, 'O', 'O', 0, 0, },
		{ JOINT_CHR_END, ' ', ' ', 0, 0, },
	},
	{
		"@@@@/|@@@@@@",
		"@@@@||@@/|@@",
		" |\\ || ///| ",
		"@@\\\\||////@@",
		"@@ Oooo//___",
		"@@ O&uo----/",
		NULL,
	},
};

#endif	/* LAST_BOSS_TAB_H */
