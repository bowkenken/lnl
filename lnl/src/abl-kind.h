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
* $Id: abl-kind.h,v 1.13 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	ABL_KIND_H
#define	ABL_KIND_H

/* 能力値 */

typedef enum {
	/* Hit Point(体力) */
	ABL_KIND_HP,
	/* Mana Point(魔力) */
	ABL_KIND_MP,

	/* DEXterity(器用度) */
	ABL_KIND_DEX,
	/* STRength(筋力度) */
	ABL_KIND_STR,
	/* AGIlity(敏捷度) */
	ABL_KIND_AGI,

	/* INTelligence(知力) */
	ABL_KIND_INT,
	/* WISdom(判断力) */
	ABL_KIND_WIS,
	/* CHArisma(魅力) */
	ABL_KIND_CHA,

	/* FIGhter(戦闘) */
	ABL_KIND_FIG,
	/* MONk(格闘) */
	ABL_KIND_MON,
	/* HUNter(射撃) */
	ABL_KIND_HUN,
	/* THIef(盗賊) */
	ABL_KIND_THI,

	/* MAGician(基本魔法) */
	ABL_KIND_MAG,
	/* SORcerer(戦闘魔法) */
	ABL_KIND_SOR,
	/* ENChanter(支援魔法) */
	ABL_KIND_ENC,
	/* SUMmoner(召喚魔法) */
	ABL_KIND_SUM,

	/* PRIest(祈り) */
	ABL_KIND_PRI,
	/* SHAman(精霊魔法) */
	ABL_KIND_SHA,
	/* BARd(呪歌) */
	ABL_KIND_BAR,
	/* NINja(忍術) */
	ABL_KIND_NIN,

	ABL_KIND_MAX_N,
} abl_kind_t;

#endif	/* ABL_KIND_H */
