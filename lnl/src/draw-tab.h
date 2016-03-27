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
* $Id: draw-tab.h,v 1.28 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	DRAW_TAB_H
#define	DRAW_TAB_H

/* 描画 */

#include	"gmain.h"
#include	"menu.h"

/**/

/* ここから,座標は相対値 */

#define	WIN_STAT_NAME_DRAW_MIN_X	0
#define	WIN_STAT_NAME_DRAW_MIN_Y	0
#define	WIN_STAT_NAME_DRAW_WIDTH	16

#define	WIN_STAT_HP_DRAW_MIN_X	0
#define	WIN_STAT_HP_DRAW_MIN_Y	1
#define	WIN_STAT_HP_DRAW_WIDTH	(2 + 1 + 1 + 2 + 1 \
		+ WIN_STAT_CURE_HP_DRAW_WIDTH \
		+ WIN_STAT_MAX_HP_DRAW_WIDTH \
		+ WIN_STAT_CURE_MP_DRAW_WIDTH \
		+ WIN_STAT_MAX_MP_DRAW_WIDTH)

#define	WIN_STAT_MP_DRAW_MIN_X	\
		(WIN_STAT_HP_DRAW_MIN_X \
		+ 2 + WIN_STAT_CURE_HP_DRAW_WIDTH \
		+ 1 + WIN_STAT_MAX_HP_DRAW_WIDTH + 1)
#define	WIN_STAT_MP_DRAW_MIN_Y	WIN_STAT_HP_DRAW_MIN_Y

#define	WIN_STAT_CURE_HP_DRAW_WIDTH	4
#define	WIN_STAT_CURE_MP_DRAW_WIDTH	4
#define	WIN_STAT_MAX_HP_DRAW_WIDTH	4
#define	WIN_STAT_MAX_MP_DRAW_WIDTH	4

#define	WIN_STAT_ACT_DRAW_MIN_X	(WIN_STAT_NAME_DRAW_WIDTH + 1)
#define	WIN_STAT_ACT_DRAW_MIN_Y	0
#define	WIN_STAT_ACT_DRAW_WIDTH	(38 - WIN_STAT_NAME_DRAW_WIDTH - 1)

#define	WIN_STAT_COND_DRAW_MIN_X	(WIN_STAT_HP_DRAW_WIDTH + 1)
#define	WIN_STAT_COND_DRAW_MIN_Y	1
#define	WIN_STAT_COND_DRAW_WIDTH	(38 - WIN_STAT_HP_DRAW_WIDTH - 1)

#define	WIN_STAT_DUN_LEV_DRAW_MIN_X	0
#define	WIN_STAT_DUN_LEV_DRAW_MIN_Y	0

#define	WIN_STAT_TIME_DRAW_MIN_X	0
#define	WIN_STAT_TIME_DRAW_MIN_Y	1

/* ここまで,座標は相対値 */

/* Data begin */

#define	WIN_MBR_DATA_DRAW_MID_X	41

/* page 1/6 */

#define	WIN_MBR_DATA_NAME_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_NAME_TTL_DRAW_MIN_Y	0

#define	WIN_MBR_DATA_FACE_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_FACE_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_NAME_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_RACE_STR_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_RACE_STR_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_FACE_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_RACE_NAME_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_RACE_NAME_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RACE_STR_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_SEX_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_SEX_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RACE_NAME_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_HP_VAL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_HP_VAL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_SEX_TTL_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_MP_VAL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_MP_VAL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_HP_VAL_DRAW_MIN_Y + 1)

/**/

#define	WIN_MBR_DATA_VAL_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_VAL_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_MP_VAL_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_HIT_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_HIT_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_VAL_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_WPN_CRTCL_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_HIT_TTL_DRAW_MIN_X
#define	WIN_MBR_DATA_WPN_CRTCL_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_VAL_TTL_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_DAM_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_HIT_TTL_DRAW_MIN_X
#define	WIN_MBR_DATA_DAM_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_VAL_TTL_DRAW_MIN_Y + 3)

#define	WIN_MBR_DATA_DEF_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_HIT_TTL_DRAW_MIN_X
#define	WIN_MBR_DATA_DEF_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_VAL_TTL_DRAW_MIN_Y + 4)

#define	WIN_MBR_DATA_ARMOR_CRTCL_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_HIT_TTL_DRAW_MIN_X
#define	WIN_MBR_DATA_ARMOR_CRTCL_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_VAL_TTL_DRAW_MIN_Y + 5)

#define	WIN_MBR_DATA_AC_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_HIT_TTL_DRAW_MIN_X
#define	WIN_MBR_DATA_AC_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_VAL_TTL_DRAW_MIN_Y + 6)


#define	WIN_MBR_DATA_GOLD_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_GOLD_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_AC_TTL_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_TURN_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_TURN_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_GOLD_TTL_DRAW_MIN_Y + 2)


#define	WIN_MBR_DATA_STAT_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_STAT_DRAW_MIN_Y	0

#define	WIN_MBR_DATA_STAT_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_STAT_DRAW_MIN_X
#define	WIN_MBR_DATA_STAT_TTL_DRAW_MIN_Y	\
		WIN_MBR_DATA_STAT_DRAW_MIN_Y

#define	WIN_MBR_DATA_STAT_DEAD_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_DEAD_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_STAT_STONE_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_STONE_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_STAT_PARALYZE_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_PARALYZE_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_STAT_POISON_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_POISON_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_STAT_CONFUSION_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_CONFUSION_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 3)

#define	WIN_MBR_DATA_STAT_BLIND_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_BLIND_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 3)

#define	WIN_MBR_DATA_STAT_SLEEP_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_SLEEP_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 4)

#define	WIN_MBR_DATA_STAT_SILENCE_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_SILENCE_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 4)

#define	WIN_MBR_DATA_STAT_CAUGHT_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_CAUGHT_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 5)

#define	WIN_MBR_DATA_STAT_FEAR_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_FEAR_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 5)

#define	WIN_MBR_DATA_STAT_HALLUCINATION_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_HALLUCINATION_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 6)

#define	WIN_MBR_DATA_STAT_CHARM_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_CHARM_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 6)

#define	WIN_MBR_DATA_STAT_FLY_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_FLY_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 7)

#define	WIN_MBR_DATA_STAT_HUNGRY_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_HUNGRY_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 7)

#define	WIN_MBR_DATA_STAT_FAINT_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_FAINT_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 8)

#define	WIN_MBR_DATA_STAT_DRUNK_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_DRUNK_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 8)

#define	WIN_MBR_DATA_STAT_VANISH_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_VANISH_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 9)

#define	WIN_MBR_DATA_STAT_IRON_BODY_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_IRON_BODY_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 9)

#define	WIN_MBR_DATA_STAT_PASSWALL_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STAT_PASSWALL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 10)

#define	WIN_MBR_DATA_STAT_SENSE_INVISIBLE_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 20)
#define	WIN_MBR_DATA_STAT_SENSE_INVISIBLE_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 10)

#define	WIN_MBR_DATA_STORE_LIGHT_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_STORE_LIGHT_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 11 + 1)

#define	WIN_MBR_DATA_GRAPH_FILE_DRAW_MIN_X	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_X + 0)
#define	WIN_MBR_DATA_GRAPH_FILE_DRAW_MIN_Y	\
		(WIN_MBR_DATA_STAT_DRAW_MIN_Y + 12 + 2)

/* page 2/6 */

/* lev left */

#define	WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_X	(0 + 4)
#define	WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y	2

#define	WIN_MBR_DATA_EXP_TTL_LEFT_DRAW_MIN_X	(0 + 18)
#define	WIN_MBR_DATA_EXP_TTL_LEFT_DRAW_MIN_Y	\
		WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y

#define	WIN_MBR_DATA_NEED_EXP_TTL_LEFT_DRAW_MIN_X	(0 + 25)
#define	WIN_MBR_DATA_NEED_EXP_TTL_LEFT_DRAW_MIN_Y	\
		WIN_MBR_DATA_EXP_TTL_LEFT_DRAW_MIN_Y

/* lev right */

#define	WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_X	\
		(WIN_MBR_DATA_DRAW_MID_X + 4)
#define	WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y	2

#define	WIN_MBR_DATA_EXP_TTL_RIGHT_DRAW_MIN_X	\
		(WIN_MBR_DATA_DRAW_MID_X + 18)
#define	WIN_MBR_DATA_EXP_TTL_RIGHT_DRAW_MIN_Y	\
		WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y

#define	WIN_MBR_DATA_NEED_EXP_TTL_RIGHT_DRAW_MIN_X	\
		(WIN_MBR_DATA_DRAW_MID_X + 25)
#define	WIN_MBR_DATA_NEED_EXP_TTL_RIGHT_DRAW_MIN_Y	\
		WIN_MBR_DATA_EXP_TTL_RIGHT_DRAW_MIN_Y

/* abl 1/2 */

#define	WIN_MBR_DATA_HP_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_HP_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_MP_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_MP_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_DEX_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_DEX_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y + 3)

#define	WIN_MBR_DATA_STR_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_STR_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y + 4)

#define	WIN_MBR_DATA_AGI_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_AGI_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y + 5)

#define	WIN_MBR_DATA_INT_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_INT_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y + 6)

#define	WIN_MBR_DATA_WIS_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_WIS_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y + 7)

#define	WIN_MBR_DATA_CHA_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_CHA_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y + 8)

/* resi */

#define	WIN_MBR_DATA_DRAW_LEFT_LEFT_X	\
		(WIN_MBR_DATA_DRAW_MID_X * 1 / 4 - 1)
#define	WIN_MBR_DATA_DRAW_LEFT_MID_X	\
		(WIN_MBR_DATA_DRAW_MID_X * 2 / 4 - 1)
#define	WIN_MBR_DATA_DRAW_LEFT_RIGHT_X	\
		(WIN_MBR_DATA_DRAW_MID_X * 3 / 4 - 1)

#define	WIN_MBR_DATA_RESI_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_RESI_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_CHA_TTL_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_RESI_TTL_LAWFUL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_LEFT_X
#define	WIN_MBR_DATA_RESI_TTL_LAWFUL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_TTL_DRAW_MIN_Y + 0)
#define	WIN_MBR_DATA_RESI_TTL_NEUTRAL_1_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_MID_X
#define	WIN_MBR_DATA_RESI_TTL_NEUTRAL_1_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_TTL_DRAW_MIN_Y + 0)
#define	WIN_MBR_DATA_RESI_TTL_CHAOTIC_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_RIGHT_X
#define	WIN_MBR_DATA_RESI_TTL_CHAOTIC_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_TTL_DRAW_MIN_Y + 0)

#define	WIN_MBR_DATA_RESI_TTL_GOOD_DRAW_MIN_X	0
#define	WIN_MBR_DATA_RESI_TTL_GOOD_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_TTL_DRAW_MIN_Y + 1)
#define	WIN_MBR_DATA_RESI_TTL_NEUTRAL_2_DRAW_MIN_X	0
#define	WIN_MBR_DATA_RESI_TTL_NEUTRAL_2_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_TTL_DRAW_MIN_Y + 2)
#define	WIN_MBR_DATA_RESI_TTL_EVIL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_RESI_TTL_EVIL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_TTL_DRAW_MIN_Y + 3)

#define	WIN_MBR_DATA_RESI_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_RESI_ELEC_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_LEFT_X
#define	WIN_MBR_DATA_RESI_ELEC_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_DRAW_MIN_Y + 0)

#define	WIN_MBR_DATA_RESI_COLD_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_MID_X
#define	WIN_MBR_DATA_RESI_COLD_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_DRAW_MIN_Y + 0)

#define	WIN_MBR_DATA_RESI_KNOC_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_RIGHT_X
#define	WIN_MBR_DATA_RESI_KNOC_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_DRAW_MIN_Y + 0)

#define	WIN_MBR_DATA_RESI_ACID_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_LEFT_X
#define	WIN_MBR_DATA_RESI_ACID_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_RESI_SLAS_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_MID_X
#define	WIN_MBR_DATA_RESI_SLAS_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_RESI_MIND_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_RIGHT_X
#define	WIN_MBR_DATA_RESI_MIND_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_RESI_STIN_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_LEFT_X
#define	WIN_MBR_DATA_RESI_STIN_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_RESI_HEAT_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_MID_X
#define	WIN_MBR_DATA_RESI_HEAT_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_RESI_POIS_TTL_DRAW_MIN_X	\
		WIN_MBR_DATA_DRAW_LEFT_RIGHT_X
#define	WIN_MBR_DATA_RESI_POIS_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_RESI_DRAW_MIN_Y + 2)

/* Class */

#define	WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_Y	0

/* abl 2/2 */

#define	WIN_MBR_DATA_FIG_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_FIG_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_MON_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_MON_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 2)

#define	WIN_MBR_DATA_HUN_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_HUN_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 3)

#define	WIN_MBR_DATA_THI_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_THI_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 4)

#define	WIN_MBR_DATA_MAG_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_MAG_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 5)

#define	WIN_MBR_DATA_SOR_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_SOR_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 6)

#define	WIN_MBR_DATA_ENC_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_ENC_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 7)

#define	WIN_MBR_DATA_SUM_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_SUM_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 8)

#define	WIN_MBR_DATA_PRI_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_PRI_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 9)

#define	WIN_MBR_DATA_SHA_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_SHA_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 10)

#define	WIN_MBR_DATA_BAR_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_BAR_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 11)

#define	WIN_MBR_DATA_NIN_TTL_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_NIN_TTL_DRAW_MIN_Y	\
		(WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y + 12)

/* page 3/6 4/6 */

/* skill title */

#define	WIN_MBR_DATA_SKILL_NAME_TTL_DRAW_MIN_X	0
#define	WIN_MBR_DATA_SKILL_NAME_TTL_DRAW_MIN_Y	2

#define	WIN_MBR_DATA_SKILL_LEV_TTL_DRAW_MIN_X	\
		(WIN_MBR_DATA_DRAW_MID_X + 4)
#define	WIN_MBR_DATA_SKILL_LEV_TTL_DRAW_MIN_Y	\
		WIN_MBR_DATA_SKILL_NAME_TTL_DRAW_MIN_Y

#define	WIN_MBR_DATA_SKILL_EXP_TTL_DRAW_MIN_X	\
		(WIN_MBR_DATA_DRAW_MID_X + 18)
#define	WIN_MBR_DATA_SKILL_EXP_TTL_DRAW_MIN_Y	\
		WIN_MBR_DATA_SKILL_LEV_TTL_DRAW_MIN_Y

#define	WIN_MBR_DATA_SKILL_NEED_EXP_TTL_DRAW_MIN_X	\
		(WIN_MBR_DATA_DRAW_MID_X + 25)
#define	WIN_MBR_DATA_SKILL_NEED_EXP_TTL_DRAW_MIN_Y	\
		WIN_MBR_DATA_SKILL_LEV_TTL_DRAW_MIN_Y

/* skill */

#define	WIN_MBR_DATA_SKILL_NAME_DRAW_MIN_X	0
#define	WIN_MBR_DATA_SKILL_NAME_DRAW_MIN_Y	\
		(WIN_MBR_DATA_SKILL_NAME_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_SKILL_LEV_DRAW_MIN_X	\
		(WIN_MBR_DATA_DRAW_MID_X + 4 + 2)
#define	WIN_MBR_DATA_SKILL_LEV_DRAW_MIN_Y	\
		(WIN_MBR_DATA_SKILL_LEV_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_SKILL_EXP_DRAW_MIN_X	\
		(WIN_MBR_DATA_DRAW_MID_X + 39 - 11 - 10 - 3)
#define	WIN_MBR_DATA_SKILL_EXP_DRAW_MIN_Y	\
		(WIN_MBR_DATA_SKILL_EXP_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_SKILL_NEED_EXP_DRAW_MIN_X	\
		(WIN_MBR_DATA_DRAW_MID_X + 39 - 10 - 3)
#define	WIN_MBR_DATA_SKILL_NEED_EXP_DRAW_MIN_Y	\
		(WIN_MBR_DATA_SKILL_NEED_EXP_TTL_DRAW_MIN_Y + 1)

#define	WIN_MBR_DATA_SKILL_HINT_DRAW_MIN_X	0
#define	WIN_MBR_DATA_SKILL_HINT_DRAW_MIN_Y	\
		(WIN_MBR_DATA_SKILL_NAME_DRAW_MIN_Y + 10 + 2)

/* page 5/6 6/6 */

#define	WIN_MBR_DATA_ITEM_DRAW_MIN_X	\
		WIN_MBR_DATA_NAME_TTL_DRAW_MIN_X
#define	WIN_MBR_DATA_ITEM_DRAW_MIN_Y	\
		(WIN_MBR_DATA_NAME_TTL_DRAW_MIN_Y + 1)

/* Page */

#define	WIN_MBR_DATA_SWAP_PAGE_MBR_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_SWAP_PAGE_MBR_DRAW_MIN_Y	17
#define	WIN_MBR_DATA_PREV_PAGE_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_PREV_PAGE_DRAW_MIN_Y	18
#define	WIN_MBR_DATA_NEXT_PAGE_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_MBR_DATA_NEXT_PAGE_DRAW_MIN_Y	19

/* Data end */

/* Edit class begin */

#define	WIN_EDIT_CLASS_PREV_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_EDIT_CLASS_PREV_DRAW_MIN_Y	\
		(WIN_MBR_DATA_NEXT_PAGE_DRAW_MIN_Y - 1)

#define	WIN_EDIT_CLASS_NEXT_DRAW_MIN_X	WIN_MBR_DATA_DRAW_MID_X
#define	WIN_EDIT_CLASS_NEXT_DRAW_MIN_Y	\
		(WIN_EDIT_CLASS_PREV_DRAW_MIN_Y + 1)

/* Edit class end */

/* Edit pet begin */

#define	WIN_PET_DATA_NAME_TTL_DRAW_MIN_X	0
#define	WIN_PET_DATA_NAME_TTL_DRAW_MIN_Y	0

/* Edit pet end */

/* Edit auto mark begin */

#define	WIN_AUTO_MARK_INFO_TTL_DRAW_MIN_X	0
#define	WIN_AUTO_MARK_INFO_TTL_DRAW_MIN_Y	0

#define	WIN_AUTO_MARK_HINT_TTL_DRAW_MIN_X	0
#define	WIN_AUTO_MARK_HINT_TTL_DRAW_MIN_Y	\
		(WIN_AUTO_MARK_INFO_TTL_DRAW_MIN_Y + 2)

/* Edit auto mark end */

/***************************************************************/


/* メンバー・データの画面を左右に縦線で区切るか? */

bool_t	flg_mbr_data_draw_v_line[MBR_DATA_PAGE_MAX_N] = {
	TRUE,
	TRUE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
};

/* メンバー・データのカーソルでポイント出来る項目 */

bool_t	flg_sel_data_n[MBR_DATA_EDIT_KIND_MAX_N][DATA_N_MAX_N] = {
	{
		/* 表示のみ */
		/* MBR_DATA_EDIT_KIND_SHOW */

		FALSE,	/* DATA_N_NULL, */

		FALSE,	/* DATA_N_NAME, */
		FALSE,	/* DATA_N_FACE, */
		FALSE,	/* DATA_N_RACE_STR, */
		FALSE,	/* DATA_N_RACE_NAME, */
		FALSE,	/* DATA_N_SEX, */

		FALSE,	/* DATA_N_HP_VAL, */
		FALSE,	/* DATA_N_MP_VAL, */

		FALSE,	/* DATA_N_VAL_TTL, */
		FALSE,	/* DATA_N_HIT, */
		FALSE,	/* DATA_N_WPN_CRTCL, */
		FALSE,	/* DATA_N_DAM, */
		FALSE,	/* DATA_N_DEF, */
		FALSE,	/* DATA_N_ARMOR_CRTCL, */
		FALSE,	/* DATA_N_AC, */
		FALSE,	/* DATA_N_GOLD, */
		FALSE,	/* DATA_N_TURN, */

		FALSE,	/* DATA_N_STAT_TTL, */
		FALSE,	/* DATA_N_STAT_DEAD, */
		FALSE,	/* DATA_N_STAT_STONE, */
		FALSE,	/* DATA_N_STAT_PARALYZE, */
		FALSE,	/* DATA_N_STAT_POISON, */
		FALSE,	/* DATA_N_STAT_CONFUSION, */
		FALSE,	/* DATA_N_STAT_BLIND, */
		FALSE,	/* DATA_N_STAT_SLEEP, */
		FALSE,	/* DATA_N_STAT_SILENCE, */
		FALSE,	/* DATA_N_STAT_CAUGHT, */
		FALSE,	/* DATA_N_STAT_FEAR, */
		FALSE,	/* DATA_N_STAT_HALLUCINATION, */
		FALSE,	/* DATA_N_STAT_CHARM, */
		FALSE,	/* DATA_N_STAT_FLY, */
		FALSE,	/* DATA_N_STAT_HUNGRY, */
		FALSE,	/* DATA_N_STAT_FAINT, */
		FALSE,	/* DATA_N_STAT_DRUNK, */
		FALSE,	/* DATA_N_STAT_VANISH, */
		FALSE,	/* DATA_N_STAT_IRON_BODY, */
		FALSE,	/* DATA_N_STAT_PASSWALL, */
		FALSE,	/* DATA_N_STAT_SENSE_INVISIBLE, */

		FALSE,	/* DATA_N_STORE_LIGHT, */
		TRUE,	/* DATA_N_GRAPH_FILE, */

		FALSE,	/* DATA_N_LEV_LEFT, */
		FALSE,	/* DATA_N_EXP_LEFT, */
		FALSE,	/* DATA_N_NEED_EXP_LEFT, */

		FALSE,	/* DATA_N_LEV_RIGHT, */
		FALSE,	/* DATA_N_EXP_RIGHT, */
		FALSE,	/* DATA_N_NEED_EXP_RIGHT, */

		FALSE,	/* DATA_N_HP, */
		FALSE,	/* DATA_N_MP, */
		FALSE,	/* DATA_N_DEX, */
		FALSE,	/* DATA_N_STR, */
		FALSE,	/* DATA_N_AGI, */
		FALSE,	/* DATA_N_INT, */
		FALSE,	/* DATA_N_WIS, */
		FALSE,	/* DATA_N_CHA, */

		FALSE,	/* DATA_N_RESI_TTL, */
		FALSE,	/* DATA_N_RESI_TTL_LAWFUL, */
		FALSE,	/* DATA_N_RESI_TTL_NEUTRAL_1, */
		FALSE,	/* DATA_N_RESI_TTL_CHAOTIC, */
		FALSE,	/* DATA_N_RESI_TTL_GOOD, */
		FALSE,	/* DATA_N_RESI_TTL_NEUTRAL_2, */
		FALSE,	/* DATA_N_RESI_TTL_EVIL, */
		FALSE,	/* DATA_N_RESI_KNOC, */
		FALSE,	/* DATA_N_RESI_SLAS, */
		FALSE,	/* DATA_N_RESI_STIN, */
		FALSE,	/* DATA_N_RESI_HEAT, */
		FALSE,	/* DATA_N_RESI_COLD, */
		FALSE,	/* DATA_N_RESI_MIND, */
		FALSE,	/* DATA_N_RESI_ACID, */
		FALSE,	/* DATA_N_RESI_ELEC, */
		FALSE,	/* DATA_N_RESI_POIS, */

		FALSE,	/* DATA_N_CLASS, */

		FALSE,	/* DATA_N_FIG, */
		FALSE,	/* DATA_N_MON, */
		FALSE,	/* DATA_N_HUN, */
		FALSE,	/* DATA_N_THI, */
		FALSE,	/* DATA_N_MAG, */
		FALSE,	/* DATA_N_SOR, */
		FALSE,	/* DATA_N_ENC, */
		FALSE,	/* DATA_N_SUM, */
		FALSE,	/* DATA_N_PRI, */
		FALSE,	/* DATA_N_SHA, */
		FALSE,	/* DATA_N_BAR, */
		FALSE,	/* DATA_N_NIN, */

		FALSE,	/* DATA_N_SKILL_NAME_A, */
		FALSE,	/* DATA_N_SKILL_NAME_B, */
		FALSE,	/* DATA_N_SKILL_LEV, */
		FALSE,	/* DATA_N_SKILL_EXP, */
		FALSE,	/* DATA_N_SKILL_NEED_EXP, */

		TRUE,	/* DATA_N_SKILL_A_00, */
		TRUE,	/* DATA_N_SKILL_A_01, */
		TRUE,	/* DATA_N_SKILL_A_02, */
		TRUE,	/* DATA_N_SKILL_A_03, */
		TRUE,	/* DATA_N_SKILL_A_04, */
		TRUE,	/* DATA_N_SKILL_A_05, */
		TRUE,	/* DATA_N_SKILL_A_06, */
		TRUE,	/* DATA_N_SKILL_A_07, */
		TRUE,	/* DATA_N_SKILL_A_08, */
		TRUE,	/* DATA_N_SKILL_A_09, */

		TRUE,	/* DATA_N_SKILL_B_00, */
		TRUE,	/* DATA_N_SKILL_B_01, */
		TRUE,	/* DATA_N_SKILL_B_02, */
		TRUE,	/* DATA_N_SKILL_B_03, */
		TRUE,	/* DATA_N_SKILL_B_04, */
		TRUE,	/* DATA_N_SKILL_B_05, */
		TRUE,	/* DATA_N_SKILL_B_06, */
		TRUE,	/* DATA_N_SKILL_B_07, */
		TRUE,	/* DATA_N_SKILL_B_08, */
		TRUE,	/* DATA_N_SKILL_B_09, */

		TRUE,	/* DATA_N_ITEM_00, */
		TRUE,	/* DATA_N_ITEM_01, */
		TRUE,	/* DATA_N_ITEM_02, */
		TRUE,	/* DATA_N_ITEM_03, */
		TRUE,	/* DATA_N_ITEM_04, */
		TRUE,	/* DATA_N_ITEM_05, */
		TRUE,	/* DATA_N_ITEM_06, */
		TRUE,	/* DATA_N_ITEM_07, */
		TRUE,	/* DATA_N_ITEM_08, */
		TRUE,	/* DATA_N_ITEM_09, */
		TRUE,	/* DATA_N_ITEM_10, */
		TRUE,	/* DATA_N_ITEM_11, */
		TRUE,	/* DATA_N_ITEM_12, */
		TRUE,	/* DATA_N_ITEM_13, */
		TRUE,	/* DATA_N_ITEM_14, */
		TRUE,	/* DATA_N_ITEM_15, */

		TRUE,	/* DATA_N_EQUIP_WIELDING, */
		TRUE,	/* DATA_N_EQUIP_SHIELD, */
		TRUE,	/* DATA_N_EQUIP_BOW, */
		TRUE,	/* DATA_N_EQUIP_ARW, */
		TRUE,	/* DATA_N_EQUIP_HEAD, */
		TRUE,	/* DATA_N_EQUIP_NECK, */
		TRUE,	/* DATA_N_EQUIP_BODY, */
		TRUE,	/* DATA_N_EQUIP_ABOUT_BODY, */
		TRUE,	/* DATA_N_EQUIP_ARM, */
		TRUE,	/* DATA_N_EQUIP_RIGHT_HAND, */
		TRUE,	/* DATA_N_EQUIP_LEFT_HAND, */
		TRUE,	/* DATA_N_EQUIP_FEET, */
		TRUE,	/* DATA_N_EQUIP_LIGHT_SOURCE, */

		TRUE,	/* DATA_N_SWAP_PAGE_MBR, */
		TRUE,	/* DATA_N_PREV_PAGE, */
		TRUE,	/* DATA_N_NEXT_PAGE, */
	},
	{
		/* 編集 */
		/* MBR_DATA_EDIT_KIND_EDIT */

		FALSE,	/* DATA_N_NULL, */

		TRUE,	/* DATA_N_NAME, */
		TRUE,	/* DATA_N_FACE, */
		FALSE,	/* DATA_N_RACE_STR, */
		TRUE,	/* DATA_N_RACE_NAME, */
		FALSE,	/* DATA_N_SEX, */

		FALSE,	/* DATA_N_HP_VAL, */
		FALSE,	/* DATA_N_MP_VAL, */

		FALSE,	/* DATA_N_VAL_TTL, */
		FALSE,	/* DATA_N_HIT, */
		FALSE,	/* DATA_N_WPN_CRTCL, */
		FALSE,	/* DATA_N_DAM, */
		FALSE,	/* DATA_N_DEF, */
		FALSE,	/* DATA_N_ARMOR_CRTCL, */
		FALSE,	/* DATA_N_AC, */
		FALSE,	/* DATA_N_GOLD, */
		FALSE,	/* DATA_N_TURN, */

		FALSE,	/* DATA_N_STAT_TTL, */
		FALSE,	/* DATA_N_STAT_DEAD, */
		FALSE,	/* DATA_N_STAT_STONE, */
		FALSE,	/* DATA_N_STAT_PARALYZE, */
		FALSE,	/* DATA_N_STAT_POISON, */
		FALSE,	/* DATA_N_STAT_CONFUSION, */
		FALSE,	/* DATA_N_STAT_BLIND, */
		FALSE,	/* DATA_N_STAT_SLEEP, */
		FALSE,	/* DATA_N_STAT_SILENCE, */
		FALSE,	/* DATA_N_STAT_CAUGHT, */
		FALSE,	/* DATA_N_STAT_FEAR, */
		FALSE,	/* DATA_N_STAT_HALLUCINATION, */
		FALSE,	/* DATA_N_STAT_CHARM, */
		FALSE,	/* DATA_N_STAT_FLY, */
		FALSE,	/* DATA_N_STAT_HUNGRY, */
		FALSE,	/* DATA_N_STAT_FAINT, */
		FALSE,	/* DATA_N_STAT_DRUNK, */
		FALSE,	/* DATA_N_STAT_VANISH, */
		FALSE,	/* DATA_N_STAT_IRON_BODY, */
		FALSE,	/* DATA_N_STAT_PASSWALL, */
		FALSE,	/* DATA_N_STAT_SENSE_INVISIBLE, */

		FALSE,	/* DATA_N_STORE_LIGHT, */
		TRUE,	/* DATA_N_GRAPH_FILE, */

		FALSE,	/* DATA_N_LEV_LEFT, */
		FALSE,	/* DATA_N_EXP_LEFT, */
		FALSE,	/* DATA_N_NEED_EXP_LEFT, */

		FALSE,	/* DATA_N_LEV_RIGHT, */
		FALSE,	/* DATA_N_EXP_RIGHT, */
		FALSE,	/* DATA_N_NEED_EXP_RIGHT, */

		FALSE,	/* DATA_N_HP, */
		FALSE,	/* DATA_N_MP, */
		FALSE,	/* DATA_N_DEX, */
		FALSE,	/* DATA_N_STR, */
		FALSE,	/* DATA_N_AGI, */
		FALSE,	/* DATA_N_INT, */
		FALSE,	/* DATA_N_WIS, */
		FALSE,	/* DATA_N_CHA, */

		FALSE,	/* DATA_N_RESI_TTL, */
		FALSE,	/* DATA_N_RESI_TTL_LAWFUL, */
		FALSE,	/* DATA_N_RESI_TTL_NEUTRAL_1, */
		FALSE,	/* DATA_N_RESI_TTL_CHAOTIC, */
		FALSE,	/* DATA_N_RESI_TTL_GOOD, */
		FALSE,	/* DATA_N_RESI_TTL_NEUTRAL_2, */
		FALSE,	/* DATA_N_RESI_TTL_EVIL, */
		FALSE,	/* DATA_N_RESI_KNOC, */
		FALSE,	/* DATA_N_RESI_SLAS, */
		FALSE,	/* DATA_N_RESI_STIN, */
		FALSE,	/* DATA_N_RESI_HEAT, */
		FALSE,	/* DATA_N_RESI_COLD, */
		FALSE,	/* DATA_N_RESI_MIND, */
		FALSE,	/* DATA_N_RESI_ACID, */
		FALSE,	/* DATA_N_RESI_ELEC, */
		FALSE,	/* DATA_N_RESI_POIS, */

		TRUE,	/* DATA_N_CLASS, */

		FALSE,	/* DATA_N_FIG, */
		FALSE,	/* DATA_N_MON, */
		FALSE,	/* DATA_N_HUN, */
		FALSE,	/* DATA_N_THI, */
		FALSE,	/* DATA_N_MAG, */
		FALSE,	/* DATA_N_SOR, */
		FALSE,	/* DATA_N_ENC, */
		FALSE,	/* DATA_N_SUM, */
		FALSE,	/* DATA_N_PRI, */
		FALSE,	/* DATA_N_SHA, */
		FALSE,	/* DATA_N_BAR, */
		FALSE,	/* DATA_N_NIN, */

		FALSE,	/* DATA_N_SKILL_NAME_A, */
		FALSE,	/* DATA_N_SKILL_NAME_B, */
		FALSE,	/* DATA_N_SKILL_LEV, */
		FALSE,	/* DATA_N_SKILL_EXP, */
		FALSE,	/* DATA_N_SKILL_NEED_EXP, */

		TRUE,	/* DATA_N_SKILL_A_00, */
		TRUE,	/* DATA_N_SKILL_A_01, */
		TRUE,	/* DATA_N_SKILL_A_02, */
		TRUE,	/* DATA_N_SKILL_A_03, */
		TRUE,	/* DATA_N_SKILL_A_04, */
		TRUE,	/* DATA_N_SKILL_A_05, */
		TRUE,	/* DATA_N_SKILL_A_06, */
		TRUE,	/* DATA_N_SKILL_A_07, */
		TRUE,	/* DATA_N_SKILL_A_08, */
		TRUE,	/* DATA_N_SKILL_A_09, */

		TRUE,	/* DATA_N_SKILL_B_00, */
		TRUE,	/* DATA_N_SKILL_B_01, */
		TRUE,	/* DATA_N_SKILL_B_02, */
		TRUE,	/* DATA_N_SKILL_B_03, */
		TRUE,	/* DATA_N_SKILL_B_04, */
		TRUE,	/* DATA_N_SKILL_B_05, */
		TRUE,	/* DATA_N_SKILL_B_06, */
		TRUE,	/* DATA_N_SKILL_B_07, */
		TRUE,	/* DATA_N_SKILL_B_08, */
		TRUE,	/* DATA_N_SKILL_B_09, */

		TRUE,	/* DATA_N_ITEM_00, */
		TRUE,	/* DATA_N_ITEM_01, */
		TRUE,	/* DATA_N_ITEM_02, */
		TRUE,	/* DATA_N_ITEM_03, */
		TRUE,	/* DATA_N_ITEM_04, */
		TRUE,	/* DATA_N_ITEM_05, */
		TRUE,	/* DATA_N_ITEM_06, */
		TRUE,	/* DATA_N_ITEM_07, */
		TRUE,	/* DATA_N_ITEM_08, */
		TRUE,	/* DATA_N_ITEM_09, */
		TRUE,	/* DATA_N_ITEM_10, */
		TRUE,	/* DATA_N_ITEM_11, */
		TRUE,	/* DATA_N_ITEM_12, */
		TRUE,	/* DATA_N_ITEM_13, */
		TRUE,	/* DATA_N_ITEM_14, */
		TRUE,	/* DATA_N_ITEM_15, */

		TRUE,	/* DATA_N_EQUIP_WIELDING, */
		TRUE,	/* DATA_N_EQUIP_SHIELD, */
		TRUE,	/* DATA_N_EQUIP_BOW, */
		TRUE,	/* DATA_N_EQUIP_ARW, */
		TRUE,	/* DATA_N_EQUIP_HEAD, */
		TRUE,	/* DATA_N_EQUIP_NECK, */
		TRUE,	/* DATA_N_EQUIP_BODY, */
		TRUE,	/* DATA_N_EQUIP_ABOUT_BODY, */
		TRUE,	/* DATA_N_EQUIP_ARM, */
		TRUE,	/* DATA_N_EQUIP_RIGHT_HAND, */
		TRUE,	/* DATA_N_EQUIP_LEFT_HAND, */
		TRUE,	/* DATA_N_EQUIP_FEET, */
		TRUE,	/* DATA_N_EQUIP_LIGHT_SOURCE, */

		TRUE,	/* DATA_N_SWAP_PAGE_MBR, */
		TRUE,	/* DATA_N_PREV_PAGE, */
		TRUE,	/* DATA_N_NEXT_PAGE, */
	},
	{
		/* 新規 */
		/* MBR_DATA_EDIT_KIND_NEW */

		FALSE,	/* DATA_N_NULL, */

		TRUE,	/* DATA_N_NAME, */
		TRUE,	/* DATA_N_FACE, */
		TRUE,	/* DATA_N_RACE_STR, */
		TRUE,	/* DATA_N_RACE_NAME, */
		TRUE,	/* DATA_N_SEX, */

		FALSE,	/* DATA_N_HP_VAL, */
		FALSE,	/* DATA_N_MP_VAL, */

		FALSE,	/* DATA_N_VAL_TTL, */
		FALSE,	/* DATA_N_HIT, */
		FALSE,	/* DATA_N_WPN_CRTCL, */
		FALSE,	/* DATA_N_DAM, */
		FALSE,	/* DATA_N_DEF, */
		FALSE,	/* DATA_N_ARMOR_CRTCL, */
		FALSE,	/* DATA_N_AC, */
		FALSE,	/* DATA_N_GOLD, */
		FALSE,	/* DATA_N_TURN, */

		FALSE,	/* DATA_N_STAT_TTL, */
		FALSE,	/* DATA_N_STAT_DEAD, */
		FALSE,	/* DATA_N_STAT_STONE, */
		FALSE,	/* DATA_N_STAT_PARALYZE, */
		FALSE,	/* DATA_N_STAT_POISON, */
		FALSE,	/* DATA_N_STAT_CONFUSION, */
		FALSE,	/* DATA_N_STAT_BLIND, */
		FALSE,	/* DATA_N_STAT_SLEEP, */
		FALSE,	/* DATA_N_STAT_SILENCE, */
		FALSE,	/* DATA_N_STAT_CAUGHT, */
		FALSE,	/* DATA_N_STAT_FEAR, */
		FALSE,	/* DATA_N_STAT_HALLUCINATION, */
		FALSE,	/* DATA_N_STAT_CHARM, */
		FALSE,	/* DATA_N_STAT_FLY, */
		FALSE,	/* DATA_N_STAT_HUNGRY, */
		FALSE,	/* DATA_N_STAT_FAINT, */
		FALSE,	/* DATA_N_STAT_DRUNK, */
		FALSE,	/* DATA_N_STAT_VANISH, */
		FALSE,	/* DATA_N_STAT_IRON_BODY, */
		FALSE,	/* DATA_N_STAT_PASSWALL, */
		FALSE,	/* DATA_N_STAT_SENSE_INVISIBLE, */

		FALSE,	/* DATA_N_STORE_LIGHT, */
		TRUE,	/* DATA_N_GRAPH_FILE, */

		FALSE,	/* DATA_N_LEV_LEFT, */
		FALSE,	/* DATA_N_EXP_LEFT, */
		FALSE,	/* DATA_N_NEED_EXP_LEFT, */

		FALSE,	/* DATA_N_LEV_RIGHT, */
		FALSE,	/* DATA_N_EXP_RIGHT, */
		FALSE,	/* DATA_N_NEED_EXP_RIGHT, */

		FALSE,	/* DATA_N_HP, */
		FALSE,	/* DATA_N_MP, */
		FALSE,	/* DATA_N_DEX, */
		FALSE,	/* DATA_N_STR, */
		FALSE,	/* DATA_N_AGI, */
		FALSE,	/* DATA_N_INT, */
		FALSE,	/* DATA_N_WIS, */
		FALSE,	/* DATA_N_CHA, */

		FALSE,	/* DATA_N_RESI_TTL, */
		FALSE,	/* DATA_N_RESI_TTL_LAWFUL, */
		FALSE,	/* DATA_N_RESI_TTL_NEUTRAL_1, */
		FALSE,	/* DATA_N_RESI_TTL_CHAOTIC, */
		FALSE,	/* DATA_N_RESI_TTL_GOOD, */
		FALSE,	/* DATA_N_RESI_TTL_NEUTRAL_2, */
		FALSE,	/* DATA_N_RESI_TTL_EVIL, */
		FALSE,	/* DATA_N_RESI_KNOC, */
		FALSE,	/* DATA_N_RESI_SLAS, */
		FALSE,	/* DATA_N_RESI_STIN, */
		FALSE,	/* DATA_N_RESI_HEAT, */
		FALSE,	/* DATA_N_RESI_COLD, */
		FALSE,	/* DATA_N_RESI_MIND, */
		FALSE,	/* DATA_N_RESI_ACID, */
		FALSE,	/* DATA_N_RESI_ELEC, */
		FALSE,	/* DATA_N_RESI_POIS, */

		TRUE,	/* DATA_N_CLASS, */

		FALSE,	/* DATA_N_FIG, */
		FALSE,	/* DATA_N_MON, */
		FALSE,	/* DATA_N_HUN, */
		FALSE,	/* DATA_N_THI, */
		FALSE,	/* DATA_N_MAG, */
		FALSE,	/* DATA_N_SOR, */
		FALSE,	/* DATA_N_ENC, */
		FALSE,	/* DATA_N_SUM, */
		FALSE,	/* DATA_N_PRI, */
		FALSE,	/* DATA_N_SHA, */
		FALSE,	/* DATA_N_BAR, */
		FALSE,	/* DATA_N_NIN, */

		FALSE,	/* DATA_N_SKILL_NAME_A, */
		FALSE,	/* DATA_N_SKILL_NAME_B, */
		FALSE,	/* DATA_N_SKILL_LEV, */
		FALSE,	/* DATA_N_SKILL_EXP, */
		FALSE,	/* DATA_N_SKILL_NEED_EXP, */

		TRUE,	/* DATA_N_SKILL_A_00, */
		TRUE,	/* DATA_N_SKILL_A_01, */
		TRUE,	/* DATA_N_SKILL_A_02, */
		TRUE,	/* DATA_N_SKILL_A_03, */
		TRUE,	/* DATA_N_SKILL_A_04, */
		TRUE,	/* DATA_N_SKILL_A_05, */
		TRUE,	/* DATA_N_SKILL_A_06, */
		TRUE,	/* DATA_N_SKILL_A_07, */
		TRUE,	/* DATA_N_SKILL_A_08, */
		TRUE,	/* DATA_N_SKILL_A_09, */

		TRUE,	/* DATA_N_SKILL_B_00, */
		TRUE,	/* DATA_N_SKILL_B_01, */
		TRUE,	/* DATA_N_SKILL_B_02, */
		TRUE,	/* DATA_N_SKILL_B_03, */
		TRUE,	/* DATA_N_SKILL_B_04, */
		TRUE,	/* DATA_N_SKILL_B_05, */
		TRUE,	/* DATA_N_SKILL_B_06, */
		TRUE,	/* DATA_N_SKILL_B_07, */
		TRUE,	/* DATA_N_SKILL_B_08, */
		TRUE,	/* DATA_N_SKILL_B_09, */

		TRUE,	/* DATA_N_ITEM_00, */
		TRUE,	/* DATA_N_ITEM_01, */
		TRUE,	/* DATA_N_ITEM_02, */
		TRUE,	/* DATA_N_ITEM_03, */
		TRUE,	/* DATA_N_ITEM_04, */
		TRUE,	/* DATA_N_ITEM_05, */
		TRUE,	/* DATA_N_ITEM_06, */
		TRUE,	/* DATA_N_ITEM_07, */
		TRUE,	/* DATA_N_ITEM_08, */
		TRUE,	/* DATA_N_ITEM_09, */
		TRUE,	/* DATA_N_ITEM_10, */
		TRUE,	/* DATA_N_ITEM_11, */
		TRUE,	/* DATA_N_ITEM_12, */
		TRUE,	/* DATA_N_ITEM_13, */
		TRUE,	/* DATA_N_ITEM_14, */
		TRUE,	/* DATA_N_ITEM_15, */

		TRUE,	/* DATA_N_EQUIP_WIELDING, */
		TRUE,	/* DATA_N_EQUIP_SHIELD, */
		TRUE,	/* DATA_N_EQUIP_BOW, */
		TRUE,	/* DATA_N_EQUIP_ARW, */
		TRUE,	/* DATA_N_EQUIP_HEAD, */
		TRUE,	/* DATA_N_EQUIP_NECK, */
		TRUE,	/* DATA_N_EQUIP_BODY, */
		TRUE,	/* DATA_N_EQUIP_ABOUT_BODY, */
		TRUE,	/* DATA_N_EQUIP_ARM, */
		TRUE,	/* DATA_N_EQUIP_RIGHT_HAND, */
		TRUE,	/* DATA_N_EQUIP_LEFT_HAND, */
		TRUE,	/* DATA_N_EQUIP_FEET, */
		TRUE,	/* DATA_N_EQUIP_LIGHT_SOURCE, */

		TRUE,	/* DATA_N_SWAP_PAGE_MBR, */
		TRUE,	/* DATA_N_PREV_PAGE, */
		TRUE,	/* DATA_N_NEXT_PAGE, */
	},
};

/* メンバーのデータの表示するページ番号 */

#define	P_NULL	0x00
#define	P_ALL	0xff
#define	P1	0x01
#define	P2	0x02
#define	P3	0x04
#define	P4	0x08
#define	P5	0x10
#define	P6	0x20

long	data_page_n_tab[] = {
	P_NULL,	/* DATA_N_NULL, */

	P_ALL,	/* DATA_N_NAME, */
	P1,	/* DATA_N_FACE, */
	P1,	/* DATA_N_RACE_STR, */
	P1,	/* DATA_N_RACE_NAME, */
	P1,	/* DATA_N_SEX, */

	P1,	/* DATA_N_HP_VAL, */
	P1,	/* DATA_N_MP_VAL, */

	P1,	/* DATA_N_VAL_TTL, */
	P1,	/* DATA_N_HIT, */
	P1,	/* DATA_N_WPN_CRTCL, */
	P1,	/* DATA_N_DAM, */
	P1,	/* DATA_N_DEF, */
	P1,	/* DATA_N_ARMOR_CRTCL, */
	P1,	/* DATA_N_AC, */
	P1,	/* DATA_N_GOLD, */
	P1,	/* DATA_N_TURN, */

	P1,	/* DATA_N_STAT_TTL, */
	P1,	/* DATA_N_STAT_DEAD, */
	P1,	/* DATA_N_STAT_STONE, */
	P1,	/* DATA_N_STAT_PARALYZE, */
	P1,	/* DATA_N_STAT_POISON, */
	P1,	/* DATA_N_STAT_CONFUSION, */
	P1,	/* DATA_N_STAT_BLIND, */
	P1,	/* DATA_N_STAT_SLEEP, */
	P1,	/* DATA_N_STAT_SILENCE, */
	P1,	/* DATA_N_STAT_CAUGHT, */
	P1,	/* DATA_N_STAT_FEAR, */
	P1,	/* DATA_N_STAT_HALLUCINATION, */
	P1,	/* DATA_N_STAT_CHARM, */
	P1,	/* DATA_N_STAT_FLY, */
	P1,	/* DATA_N_STAT_HUNGRY, */
	P1,	/* DATA_N_STAT_FAINT, */
	P1,	/* DATA_N_STAT_DRUNK, */
	P1,	/* DATA_N_STAT_VANISH, */
	P1,	/* DATA_N_STAT_IRON_BODY, */
	P1,	/* DATA_N_STAT_PASSWALL, */
	P1,	/* DATA_N_STAT_SENSE_INVISIBLE, */

	P1,	/* DATA_N_STORE_LIGHT, */
	P1,	/* DATA_N_GRAPH_FILE, */

	P2,	/* DATA_N_LEV_LEFT, */
	P2,	/* DATA_N_EXP_LEFT, */
	P2,	/* DATA_N_NEED_EXP_LEFT, */

	P2,	/* DATA_N_LEV_RIGHT, */
	P2,	/* DATA_N_EXP_RIGHT, */
	P2,	/* DATA_N_NEED_EXP_RIGHT, */

	P2,	/* DATA_N_HP, */
	P2,	/* DATA_N_MP, */
	P2,	/* DATA_N_DEX, */
	P2,	/* DATA_N_STR, */
	P2,	/* DATA_N_AGI, */
	P2,	/* DATA_N_INT, */
	P2,	/* DATA_N_WIS, */
	P2,	/* DATA_N_CHA, */

	P2,	/* DATA_N_RESI_TTL, */
	P2,	/* DATA_N_RESI_TTL_LAWFUL, */
	P2,	/* DATA_N_RESI_TTL_NEUTRAL_1, */
	P2,	/* DATA_N_RESI_TTL_CHAOTIC, */
	P2,	/* DATA_N_RESI_TTL_GOOD, */
	P2,	/* DATA_N_RESI_TTL_NEUTRAL_2, */
	P2,	/* DATA_N_RESI_TTL_EVIL, */
	P2,	/* DATA_N_RESI_KNOC, */
	P2,	/* DATA_N_RESI_SLAS, */
	P2,	/* DATA_N_RESI_STIN, */
	P2,	/* DATA_N_RESI_HEAT, */
	P2,	/* DATA_N_RESI_COLD, */
	P2,	/* DATA_N_RESI_MIND, */
	P2,	/* DATA_N_RESI_ACID, */
	P2,	/* DATA_N_RESI_ELEC, */
	P2,	/* DATA_N_RESI_POIS, */

	P2 | P3 | P4,	/* DATA_N_CLASS, */

	P2,	/* DATA_N_FIG, */
	P2,	/* DATA_N_MON, */
	P2,	/* DATA_N_HUN, */
	P2,	/* DATA_N_THI, */
	P2,	/* DATA_N_MAG, */
	P2,	/* DATA_N_SOR, */
	P2,	/* DATA_N_ENC, */
	P2,	/* DATA_N_SUM, */
	P2,	/* DATA_N_PRI, */
	P2,	/* DATA_N_SHA, */
	P2,	/* DATA_N_BAR, */
	P2,	/* DATA_N_NIN, */

	P3,	/* DATA_N_SKILL_NAME_A, */
	P4,	/* DATA_N_SKILL_NAME_B, */
	P3 | P4,	/* DATA_N_SKILL_LEV, */
	P3 | P4,	/* DATA_N_SKILL_EXP, */
	P3 | P4,	/* DATA_N_SKILL_NEED_EXP, */

	P3,	/* DATA_N_SKILL_A_00, */
	P3,	/* DATA_N_SKILL_A_01, */
	P3,	/* DATA_N_SKILL_A_02, */
	P3,	/* DATA_N_SKILL_A_03, */
	P3,	/* DATA_N_SKILL_A_04, */
	P3,	/* DATA_N_SKILL_A_05, */
	P3,	/* DATA_N_SKILL_A_06, */
	P3,	/* DATA_N_SKILL_A_07, */
	P3,	/* DATA_N_SKILL_A_08, */
	P3,	/* DATA_N_SKILL_A_09, */

	P4,	/* DATA_N_SKILL_B_00, */
	P4,	/* DATA_N_SKILL_B_01, */
	P4,	/* DATA_N_SKILL_B_02, */
	P4,	/* DATA_N_SKILL_B_03, */
	P4,	/* DATA_N_SKILL_B_04, */
	P4,	/* DATA_N_SKILL_B_05, */
	P4,	/* DATA_N_SKILL_B_06, */
	P4,	/* DATA_N_SKILL_B_07, */
	P4,	/* DATA_N_SKILL_B_08, */
	P4,	/* DATA_N_SKILL_B_09, */

	P5,	/* DATA_N_ITEM_00, */
	P5,	/* DATA_N_ITEM_01, */
	P5,	/* DATA_N_ITEM_02 */
	P5,	/* DATA_N_ITEM_03, */
	P5,	/* DATA_N_ITEM_04 */
	P5,	/* DATA_N_ITEM_05, */
	P5,	/* DATA_N_ITEM_06, */
	P5,	/* DATA_N_ITEM_07, */
	P5,	/* DATA_N_ITEM_08, */
	P5,	/* DATA_N_ITEM_09, */
	P5,	/* DATA_N_ITEM_10, */
	P5,	/* DATA_N_ITEM_11, */
	P5,	/* DATA_N_ITEM_12 */
	P5,	/* DATA_N_ITEM_13, */
	P5,	/* DATA_N_ITEM_14 */
	P5,	/* DATA_N_ITEM_15, */

	P6,	/* DATA_N_EQUIP_WIELDING, */
	P6,	/* DATA_N_EQUIP_SHIELD, */
	P6,	/* DATA_N_EQUIP_BOW, */
	P6,	/* DATA_N_EQUIP_ARW, */
	P6,	/* DATA_N_EQUIP_HEAD, */
	P6,	/* DATA_N_EQUIP_NECK, */
	P6,	/* DATA_N_EQUIP_BODY, */
	P6,	/* DATA_N_EQUIP_ABOUT_BODY, */
	P6,	/* DATA_N_EQUIP_ARM, */
	P6,	/* DATA_N_EQUIP_RIGHT_HAND, */
	P6,	/* DATA_N_EQUIP_LEFT_HAND, */
	P6,	/* DATA_N_EQUIP_FEET, */
	P6,	/* DATA_N_EQUIP_LIGHT_SOURCE, */

	P_ALL,	/* DATA_N_SWAP_PAGE_MBR, */
	P_ALL,	/* DATA_N_PREV_PAGE, */
	P_ALL,	/* DATA_N_NEXT_PAGE, */
};

/* 禁則処理 */

typedef struct {
	n_msg_t	n_str;
	char	*str;
} kin_soku_t;

/* 送りの禁則処理 */

kin_soku_t	okuri_tab[] = {
	{ N_MSG_OKURI_00, NULL },
	{ N_MSG_OKURI_01, NULL },
	{ N_MSG_OKURI_02, NULL },
	{ N_MSG_OKURI_03, NULL },
	{ N_MSG_OKURI_04, NULL },
	{ N_MSG_OKURI_05, NULL },
	{ N_MSG_OKURI_06, NULL },
	{ N_MSG_OKURI_07, NULL },
	{ N_MSG_OKURI_08, NULL },
	{ N_MSG_OKURI_09, NULL },
	{ N_MSG_OKURI_10, NULL },
	{ N_MSG_OKURI_11, NULL },
	{ N_MSG_OKURI_12, NULL },
	{ N_MSG_OKURI_13, NULL },
	{ N_MSG_OKURI_14, NULL },
	{ N_MSG_OKURI_15, NULL },
	{ N_MSG_OKURI_16, NULL },
	{ N_MSG_OKURI_17, NULL },
	{ N_MSG_OKURI_18, NULL },
	{ N_MSG_OKURI_19, NULL },
	{ N_MSG_OKURI_20, NULL },
	{ N_MSG_OKURI_21, NULL },
	{ N_MSG_OKURI_22, NULL },
	{ N_MSG_OKURI_23, NULL },
	{ N_MSG_OKURI_24, NULL },
	{ N_MSG_OKURI_25, NULL },
	{ N_MSG_OKURI_26, NULL },
	{ N_MSG_OKURI_27, NULL },
	{ N_MSG_OKURI_28, NULL },
	{ N_MSG_OKURI_29, NULL },
	{ N_MSG_NULL, NULL },
};

/* 禁則処理 */

kin_soku_t	kin_soku_tab[] = {
	{ N_MSG_KIN_SOKU_00, NULL },
	{ N_MSG_KIN_SOKU_01, NULL },
	{ N_MSG_KIN_SOKU_02, NULL },
	{ N_MSG_KIN_SOKU_03, NULL },
	{ N_MSG_KIN_SOKU_04, NULL },
	{ N_MSG_KIN_SOKU_05, NULL },
	{ N_MSG_KIN_SOKU_06, NULL },
	{ N_MSG_KIN_SOKU_07, NULL },
	{ N_MSG_KIN_SOKU_08, NULL },
	{ N_MSG_KIN_SOKU_09, NULL },
	{ N_MSG_KIN_SOKU_10, NULL },
	{ N_MSG_KIN_SOKU_11, NULL },
	{ N_MSG_KIN_SOKU_12, NULL },
	{ N_MSG_KIN_SOKU_13, NULL },
	{ N_MSG_KIN_SOKU_14, NULL },
	{ N_MSG_KIN_SOKU_15, NULL },
	{ N_MSG_KIN_SOKU_16, NULL },
	{ N_MSG_KIN_SOKU_17, NULL },
	{ N_MSG_KIN_SOKU_18, NULL },
	{ N_MSG_KIN_SOKU_19, NULL },
	{ N_MSG_KIN_SOKU_20, NULL },
	{ N_MSG_KIN_SOKU_21, NULL },
	{ N_MSG_KIN_SOKU_22, NULL },
	{ N_MSG_KIN_SOKU_23, NULL },
	{ N_MSG_KIN_SOKU_24, NULL },
	{ N_MSG_KIN_SOKU_25, NULL },
	{ N_MSG_KIN_SOKU_26, NULL },
	{ N_MSG_KIN_SOKU_27, NULL },
	{ N_MSG_KIN_SOKU_28, NULL },
	{ N_MSG_KIN_SOKU_29, NULL },
	{ N_MSG_NULL, NULL },
};

#endif	/* DRAW_TAB_H */
