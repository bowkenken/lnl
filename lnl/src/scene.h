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
* $Id: scene.h,v 1.22 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	SCENE_H
#define	SCENE_H

/***************************************************************
* シーン切り替え
***************************************************************/

/* シーンの種類 */

typedef enum {
	SCENE_N_NULL,

	SCENE_N_INIT,
	SCENE_N_TITLE,
	SCENE_N_OPENING,

	SCENE_N_TOWN,
	SCENE_N_SHOP,

	SCENE_N_DUN,
	SCENE_N_BATTLE,
	SCENE_N_BATTLE_BOSS,

	SCENE_N_LAST_BOSS,

	SCENE_N_GAME_OVER,
	SCENE_N_GAME_OVER_WAIT,
	SCENE_N_GAME_OVER_END,

	SCENE_N_ENDING,
	SCENE_N_ENDING_EPILOGUE,
	SCENE_N_ENDING_SPACE,
	SCENE_N_ENDING_STAFF_ROLL,
	SCENE_N_ENDING_END,

	SCENE_N_SEL_MBR_GRAPH,

	SCENE_N_MAX_N,
} scene_n_t;

typedef enum {
	SCENE_GROUP_N_NULL,

	SCENE_GROUP_N_INIT,
	SCENE_GROUP_N_TITLE,

	SCENE_GROUP_N_PLAYING,
	SCENE_GROUP_N_BATTLE,

	SCENE_GROUP_N_GAME_OVER,
	SCENE_GROUP_N_ENDING,
	SCENE_GROUP_N_SPACE,
	SCENE_GROUP_N_GAME_END,

	SCENE_GROUP_N_SEL_GRAPH,

	SCENE_GROUP_N_DEMO,

	SCENE_GROUP_N_CAN_SKIP,
	SCENE_GROUP_N_CAN_NOT_SKIP,

	SCENE_GROUP_N_MAX_N,
} scene_group_n_t;

typedef enum {
	LAST_SCENE_N_NULL,

	LAST_SCENE_N_ENTER,

	LAST_SCENE_N_ENCOUNTER,
	LAST_SCENE_N_ENCOUNTER_CUT_IN,
	LAST_SCENE_N_ENCOUNTER_WORDS,
	LAST_SCENE_N_ENCOUNTER_CUT_OUT,
	LAST_SCENE_N_ENCOUNTER_CUT_END,

	LAST_SCENE_N_EXEL,
	LAST_SCENE_N_EXEL_ENTER,
	LAST_SCENE_N_EXEL_CUT_IN,
	LAST_SCENE_N_EXEL_WORDS,
	LAST_SCENE_N_EXEL_CUT_OUT,
	LAST_SCENE_N_EXEL_CUT_END,
	LAST_SCENE_N_EXEL_HYPER,
	LAST_SCENE_N_EXEL_BATTLE,
	LAST_SCENE_N_EXEL_DIE,

	LAST_SCENE_N_EXELER,
	LAST_SCENE_N_EXELER_CUT_IN,
	LAST_SCENE_N_EXELER_WORDS,
	LAST_SCENE_N_EXELER_CUT_OUT,
	LAST_SCENE_N_EXELER_CUT_END,
	LAST_SCENE_N_EXELER_ENTER,
	LAST_SCENE_N_EXELER_HYPER,
	LAST_SCENE_N_EXELER_BATTLE,
	LAST_SCENE_N_EXELER_DIE,

	LAST_SCENE_N_XEX,
	LAST_SCENE_N_XEX_CUT_IN,
	LAST_SCENE_N_XEX_WORDS,
	LAST_SCENE_N_XEX_CUT_OUT,
	LAST_SCENE_N_XEX_CUT_END,

	LAST_SCENE_N_XX_ENTER,
	LAST_SCENE_N_XX_WORDS,
	LAST_SCENE_N_XX_BATTLE,
	LAST_SCENE_N_XX_DIE,

	LAST_SCENE_N_END,

	LAST_SCENE_N_MAX_N,
} last_scene_n_t;

#endif	/* SCENE_H */
