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
* $Id: rumor-tab.h,v 1.12 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	RUMOR_TAB_H
#define	RUMOR_TAB_H

/* 酒場の噂 */

typedef struct {
	/* 噂の内容 */
	n_msg_t	n_msg_female, n_msg_male;

	/* 聞く亊が出来るフラグ */
	bool_t	flg_open;

	/* 優先的に聞かれる最新の噂のフラグ */
	bool_t	flg_latest;
} rumor_tab_t;

rumor_tab_t	rumor_tab[] = {
	{
		N_MSG_RUMOR_001_FEMALE,
		N_MSG_RUMOR_001_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_002_FEMALE,
		N_MSG_RUMOR_002_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_003_FEMALE,
		N_MSG_RUMOR_003_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_004_FEMALE,
		N_MSG_RUMOR_004_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_005_FEMALE,
		N_MSG_RUMOR_005_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_006_FEMALE,
		N_MSG_RUMOR_006_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_007_FEMALE,
		N_MSG_RUMOR_007_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_RUMOR_008_FEMALE,
		N_MSG_RUMOR_008_MALE,
		TRUE, FALSE,
	},
	{
		N_MSG_NULL,
		N_MSG_NULL,
		FALSE, FALSE,
	},
};

#endif	/* RUMOR_TAB_H */
