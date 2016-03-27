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
* $Id: draw.h,v 1.79 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	DRAW_H
#define	DRAW_H

/***************************************************************
* 描画
***************************************************************/

#include	<stdio.h>

#include	"pet.h"
#include	"menu.h"
#include	"request.h"

/***************************************************************
* 色
***************************************************************/

/* 体力の数値の色が変わる割合 */
#define	WARNING_HP_RATE_GREEN	((rate_t)100)
#define	WARNING_HP_RATE_YELLOW	((rate_t)50)
#define	WARNING_HP_RATE_RED	((rate_t)25)
/* 魔力の数値の色が変わる割合 */
#define	WARNING_MP_RATE_GREEN	((rate_t)100)
#define	WARNING_MP_RATE_YELLOW	((rate_t)50)
#define	WARNING_MP_RATE_RED	((rate_t)25)

/***************************************************************
* ファイル
***************************************************************/

/* 出力ファイル・ポインタ */
#define	OUT_FP	stdout

/***************************************************************
* スクリーン・サイズ
***************************************************************/

#define	SCREEN_WIDTH	80
#define	SCREEN_HEIGHT	24
#define	SCREEN_MIN_X	0
#define	SCREEN_MIN_Y	0
#define	SCREEN_MAX_X	(SCREEN_WIDTH - 1)
#define	SCREEN_MAX_Y	(SCREEN_HEIGHT - 1)

#define	WIN_MAP_WIDTH	20
#define	WIN_MAP_HEIGHT	20

/***************************************************************
* ウィンドウのサイズ
***************************************************************/

#define	WIN_MAP_DRAW_MIN_X	0
#define	WIN_MAP_DRAW_MIN_Y	0
#define	WIN_MAP_DRAW_WIDTH	(WIN_MAP_WIDTH * 2)
#define	WIN_MAP_DRAW_HEIGHT	WIN_MAP_HEIGHT
#define	WIN_MAP_DRAW_MAX_X	\
		(WIN_MAP_DRAW_MIN_X + WIN_MAP_DRAW_WIDTH - 1)
#define	WIN_MAP_DRAW_MAX_Y	\
		(WIN_MAP_DRAW_MIN_Y + WIN_MAP_DRAW_HEIGHT - 1)

#define	WIN_MENU_DRAW_MIN_X	SCREEN_MIN_X
#define	WIN_MENU_DRAW_MIN_Y	SCREEN_MIN_Y
#define	WIN_MENU_DRAW_WIDTH	\
		(WIN_MENU_DRAW_MAX_X - WIN_MENU_DRAW_MIN_X + 1)
#define	WIN_MENU_DRAW_HEIGHT	\
		(WIN_MENU_DRAW_MAX_Y - WIN_MENU_DRAW_MIN_Y + 1)
#define	WIN_MENU_DRAW_MAX_X	(get_screen_col() - 1)
#define	WIN_MENU_DRAW_MAX_Y	(get_map_row() - 1)

#define	WIN_MSG_DRAW_MIN_X	0
#define	WIN_MSG_DRAW_MIN_Y	(WIN_MAP_DRAW_MAX_Y + 2)
#define	WIN_MSG_DRAW_WIDTH	(SCREEN_WIDTH - 1)
#define	WIN_MSG_DRAW_HEIGHT	1
#define	WIN_MSG_DRAW_MAX_X	\
		(WIN_MSG_DRAW_MIN_X + WIN_MSG_DRAW_WIDTH - 1)
#define	WIN_MSG_DRAW_MAX_Y	\
		(WIN_MSG_DRAW_MIN_Y + WIN_MSG_DRAW_HEIGHT - 1)

#define	WIN_MORE_DRAW_MIN_X	\
		(WIN_MSG_DRAW_MAX_X - WIN_MORE_DRAW_WIDTH + 1)
#define	WIN_MORE_DRAW_MIN_Y	WIN_MSG_DRAW_MIN_Y
#define	WIN_MORE_DRAW_WIDTH	(str_len_draw( MSG_MORE ))

#define	WIN_REQUEST_DRAW_WIDTH	60
#define	WIN_REQUEST_DRAW_MIN_Y	2

#define	WIN_STAT_DRAW_MIN_X	(get_map_col() + 1)
#define	WIN_STAT_DRAW_MIN_Y	0
#define	WIN_STAT_DRAW_WIDTH	(SCREEN_WIDTH / 2 - 2)
#define	WIN_STAT_DRAW_HEIGHT	3
#define	WIN_STAT_DRAW_MAX_X	\
		(WIN_STAT_DRAW_MIN_X + WIN_STAT_DRAW_WIDTH - 1)
#define	WIN_STAT_DRAW_MAX_Y	(WIN_STAT_DRAW_MIN_Y \
		+ ((MBR_MAX_N) * WIN_STAT_DRAW_HEIGHT - 1) - 1)

/***************************************************************
* ステータス表示のモード切り換え
***************************************************************/

typedef enum {
	STAT_MODE_MBR,
	STAT_MODE_PET,

	STAT_MODE_MAX_N,
} stat_mode_t;

/***************************************************************
* メッセージ表示関数のフラグ
***************************************************************/

typedef unsigned long	flg_msg_t;

/* メッセージ */
#define	FLG_MSG_MES	(1 << 0)

/* 警告 */
#define	FLG_MSG_WRN	(1 << 1)

/* エラー */
#define	FLG_MSG_ERR	(1 << 2)

/* 致命的エラー */
#define	FLG_MSG_FAT	(1 << 3)

/* デバッグ時のみ表示 */
#define	FLG_MSG_DEBUG	(1 << 8)

/* 続き待ち */
#define	FLG_MSG_MORE	(1 << 16)

/* 1つ前の続き待ちを無視 */
#define	FLG_MSG_NO_MORE_PREV	(1 << 17)

/* 1つ次の続き待ちを無視 */
#define	FLG_MSG_NO_MORE_NEXT	(1 << 18)

/* 前後の続き待ちを無視 */
#define	FLG_MSG_NO_MORE	(FLG_MSG_NO_MORE_PREV | FLG_MSG_NO_MORE_NEXT)

/***************************************************************
* メッセージ・リスト
***************************************************************/

/* メッセージ・リストの表示行数 */
#define	LS_MSG_DRAW_N	20

/* メッセージの最大行数 */
#define	LS_MSG_MAX_N	(LS_MSG_DRAW_N * 8)

/* メッセージの最大文字数 */
#define	LS_MSG_MAX_LEN	SCREEN_WIDTH
#define	LS_MSG_MAX_BYTE	(LS_MSG_MAX_LEN * CHAR_MAX_LEN_UTF_8)

typedef struct {
	char	msg[LS_MSG_MAX_BYTE + 1];
	curs_attr_t	attr;
} ls_msg_t;

/***************************************************************
* フレーム・レート
***************************************************************/

#define	TIMER_FRAME	4

#define	ANIM_FRAME_N	((long)(1.0 * 60.0))

#define	ANIM_FRAME_N_BLAST_STD	((long)(0.5 * 60.0))
#define	ANIM_FRAME_N_BLAST_DESTRUCTION	((long)(2.0 * 60.0))
#define	ANIM_FRAME_N_BLAST_NINJA_CRTCL	((long)(1.5 * 60.0))

/***************************************************************
* ビジュアル・エフェクト
***************************************************************/

/* ビジュアル・エフェクトのマップの消去文字 */
#define	MAP_VFX_NULL	'\0'

/***************************************************************
* ビジュアル・エフェクトのフィルター
***************************************************************/

typedef unsigned long	flg_vfx_mbr_t;
typedef unsigned long	flg_vfx_mnstr_t;

#define	FLG_VFX_MBR_CURE	(1 << 0)
#define	FLG_VFX_MBR_DAM	(1 << 1)
#define	FLG_VFX_MBR_CRTCL	(1 << 2)
#define	FLG_VFX_MBR_ARW	(1 << 3)
#define	FLG_VFX_MNSTR_CURE	(1 << 0)
#define	FLG_VFX_MNSTR_DAM	(1 << 1)
#define	FLG_VFX_MNSTR_CRTCL	(1 << 2)
#define	FLG_VFX_MNSTR_ARW	(1 << 3)

/***************************************************************
* 弓矢のビジュアル・エフェクト
***************************************************************/

#define	VFX_ARW_MAX_N	32

#define	ANIM_LINE_LEN	32

#define	ANIM_ARW_LEN	(ANIM_FRAME_N / 4)
#define	MNSTR_THROW_MJR	'*'

/***************************************************************
* ビジュアル・エフェクトの描画待ち時間
***************************************************************/

#define	VFX_WAIT_MIN_N	1
#define	VFX_WAIT_MAX_N	200

/***************************************************************
* GUI のビジュアル・エフェクト
***************************************************************/

/* エフェクトの種類 */
typedef enum {
	GUI_VFX_KIND_NULL,

	GUI_VFX_KIND_BASH,
	GUI_VFX_KIND_ARW,
	GUI_VFX_KIND_THROW_ITEM,
	GUI_VFX_KIND_SPELL,
	GUI_VFX_KIND_BLAST,
	GUI_VFX_KIND_NINJA,

	GUI_VFX_KIND_MAX_N,
} gui_vfx_kind_t;

/* GUI のビジュアル・エフェクトのデータ */
typedef struct gui_vfx_t {
	bool_t	flg_use;

	rate_t	anim_rate;
	bool_t	flg_crtcl;
	gui_vfx_kind_t	kind;
	long	dir_n;
	char	mjr;
	char	mnr;
	resi_kind_t	resi_kind;
	blast_kind_t	blast_kind;
	spell_kind_t	spell_kind;
} gui_vfx_t;

/***************************************************************
* コマンド・キー
***************************************************************/

#define	CMD_KEY_IDLE	'|'
#define	CMD_KEY_CONT_EXEC	','

/***************************************************************
* キー・テーブル
***************************************************************/

/* キー・テーブルのサイズ */
#define	KEY_TAB_MAX_N	512

/***************************************************************
* ファンクション・シーケンス
***************************************************************/

/* ボタン番号からキーへの変換 */

#define	KEY_N_ALL( fn )	(KEY_N_0 + (fn))
#define	KEY_N_FUNC( fn )	(KEY_N_FUNC_0 + (fn))
#define	KEY_N_MOUSE_CLICK( fn )	(KEY_N_MOUSE_CLICK_0 + (fn))
#define	KEY_N_MOUSE_D_CLICK( fn )	(KEY_N_MOUSE_D_CLICK_0 + (fn))
#define	KEY_N_MOUSE_P_CLICK( fn )	(KEY_N_MOUSE_P_CLICK_0 + (fn))
#define	KEY_N_MOUSE_PRESS( fn )	(KEY_N_MOUSE_PRESS_0 + (fn))
#define	KEY_N_MOUSE_RELEASE( fn )	(KEY_N_MOUSE_RELEASE_0 + (fn))
#define	KEY_N_MOUSE_MOTION( fn )	(KEY_N_MOUSE_MOTION_0 + (fn))
#define	KEY_N_JOYSTICK( fn )	(KEY_N_JOYSTICK_0 + (fn))

/* マウスのボタン番号 */

typedef enum {
	KEY_N_MOUSE_0,
	KEY_N_MOUSE_1,
	KEY_N_MOUSE_2,
	KEY_N_MOUSE_3,
	KEY_N_MOUSE_4,
	KEY_N_MOUSE_5,
	KEY_N_MOUSE_6,
	KEY_N_MOUSE_7,
	KEY_N_MOUSE_8,
	KEY_N_MOUSE_9,

	KEY_N_MOUSE_L = KEY_N_MOUSE_0,
	KEY_N_MOUSE_M = KEY_N_MOUSE_1,
	KEY_N_MOUSE_R = KEY_N_MOUSE_2,

	KEY_N_MOUSE_PRESS_L_CLICK_R = KEY_N_MOUSE_0,
	KEY_N_MOUSE_PRESS_R_CLICK_L = KEY_N_MOUSE_1,

	KEY_N_MOUSE_MOTION_LEFT = KEY_N_MOUSE_0,
	KEY_N_MOUSE_MOTION_RIGHT = KEY_N_MOUSE_1,
	KEY_N_MOUSE_MOTION_UP = KEY_N_MOUSE_2,
	KEY_N_MOUSE_MOTION_DOWN = KEY_N_MOUSE_3,
} key_n_mouse_t;

/* ファンクション・シーケンスの範囲（予約領域を含む） */

typedef enum {
	KEY_N_0 = 0x1000,

	KEY_N_FUNC_0 = 0x1000,
	KEY_N_FUNC_MAX = 0x10ff,

	KEY_N_MOUSE_CLICK_0 = 0x1100,
	KEY_N_MOUSE_CLICK_MAX = 0x11ff,

	KEY_N_MOUSE_D_CLICK_0 = 0x1200,
	KEY_N_MOUSE_D_CLICK_MAX = 0x12ff,

	KEY_N_MOUSE_P_CLICK_0 = 0x1300,
	KEY_N_MOUSE_P_CLICK_MAX = 0x13ff,

	KEY_N_MOUSE_PRESS_0 = 0x1400,
	KEY_N_MOUSE_PRESS_MAX = 0x14ff,

	KEY_N_MOUSE_RELEASE_0 = 0x1500,
	KEY_N_MOUSE_RELEASE_MAX = 0x15ff,

	KEY_N_MOUSE_MOTION_0 = 0x1600,
	KEY_N_MOUSE_MOTION_MAX = 0x16ff,

	KEY_N_JOYSTICK_0 = 0x1700,
	KEY_N_JOYSTICK_MAX = 0x17ff,

	KEY_N_MAX = 0x1fff,
} key_n_t;

/* ファンクション・シーケンスの使用しているキーの数 */

#define	KEY_N_FUNC_MAX_N	48
#define	KEY_N_MOUSE_CLICK_MAX_N	10
#define	KEY_N_MOUSE_D_CLICK_MAX_N	10
#define	KEY_N_MOUSE_P_CLICK_MAX_N	10
#define	KEY_N_MOUSE_PRESS_MAX_N	10
#define	KEY_N_MOUSE_RELEASE_MAX_N	10
#define	KEY_N_MOUSE_MOTION_MAX_N	10
#define	KEY_N_JOYSTICK_MAX_N	20

/* キーの先頭のインデックス */

#define	KEY_N_FUNC_HEAD_N	0
#define	KEY_N_MOUSE_HEAD_N	KEY_N_FUNC_MAX_N
#define	KEY_N_JOYSTICK_HEAD_N	(KEY_N_FUNC_MAX_N + KEY_N_MOUSE_MAX_N)

/* マウス・ボタンの最大数 */

#define	KEY_N_MOUSE_MAX_N	(0\
	+ KEY_N_MOUSE_CLICK_MAX_N \
	+ KEY_N_MOUSE_D_CLICK_MAX_N \
	+ KEY_N_MOUSE_P_CLICK_MAX_N \
	+ KEY_N_MOUSE_PRESS_MAX_N \
	+ KEY_N_MOUSE_RELEASE_MAX_N \
	+ KEY_N_MOUSE_MOTION_MAX_N \
	)

/* ファンクション・シーケンスの使用しているキーの最大数 */

#define	KEY_N_MAX_N	(0\
	+ KEY_N_FUNC_MAX_N \
	+ KEY_N_MOUSE_MAX_N \
	+ KEY_N_JOYSTICK_MAX_N \
	)

/***************************************************************
* 表示するメンバー・データの種類
***************************************************************/

typedef enum {
	DATA_N_NULL,

	DATA_N_NAME,
	DATA_N_FACE,
	DATA_N_RACE_STR,
	DATA_N_RACE_NAME,
	DATA_N_SEX,

	DATA_N_HP_VAL,
	DATA_N_MP_VAL,

	DATA_N_VAL_TTL,
	DATA_N_HIT,
	DATA_N_WPN_CRTCL,
	DATA_N_DAM,
	DATA_N_DEF,
	DATA_N_ARMOR_CRTCL,
	DATA_N_AC,
	DATA_N_GOLD,
	DATA_N_TURN,

	DATA_N_STAT_TTL,
	DATA_N_STAT_DEAD,
	DATA_N_STAT_STONE,
	DATA_N_STAT_PARALYZE,
	DATA_N_STAT_POISON,
	DATA_N_STAT_CONFUSION,
	DATA_N_STAT_BLIND,
	DATA_N_STAT_SLEEP,
	DATA_N_STAT_SILENCE,
	DATA_N_STAT_CAUGHT,
	DATA_N_STAT_FEAR,
	DATA_N_STAT_HALLUCINATION,
	DATA_N_STAT_CHARM,
	DATA_N_STAT_FLY,
	DATA_N_STAT_HUNGRY,
	DATA_N_STAT_FAINT,
	DATA_N_STAT_DRUNK,
	DATA_N_STAT_VANISH,
	DATA_N_STAT_IRON_BODY,
	DATA_N_STAT_PASSWALL,
	DATA_N_STAT_SENSE_INVISIBLE,

	DATA_N_STORE_LIGHT,
	DATA_N_GRAPH_FILE,

	DATA_N_LEV_LEFT,
	DATA_N_EXP_LEFT,
	DATA_N_NEED_EXP_LEFT,
	DATA_N_LEV_RIGHT,
	DATA_N_EXP_RIGHT,
	DATA_N_NEED_EXP_RIGHT,

	DATA_N_HP,
	DATA_N_MP,
	DATA_N_DEX,
	DATA_N_STR,
	DATA_N_AGI,
	DATA_N_INT,
	DATA_N_WIS,
	DATA_N_CHA,

	DATA_N_RESI_TTL,
	DATA_N_RESI_TTL_LAWFUL,
	DATA_N_RESI_TTL_NEUTRAL_1,
	DATA_N_RESI_TTL_CHAOTIC,
	DATA_N_RESI_TTL_GOOD,
	DATA_N_RESI_TTL_NEUTRAL_2,
	DATA_N_RESI_TTL_EVIL,
	DATA_N_RESI_KNOC,
	DATA_N_RESI_SLAS,
	DATA_N_RESI_STIN,
	DATA_N_RESI_HEAT,
	DATA_N_RESI_COLD,
	DATA_N_RESI_ACID,
	DATA_N_RESI_MIND,
	DATA_N_RESI_ELEC,
	DATA_N_RESI_POIS,

	DATA_N_CLASS,

	DATA_N_FIG,
	DATA_N_MON,
	DATA_N_HUN,
	DATA_N_THI,
	DATA_N_MAG,
	DATA_N_SOR,
	DATA_N_ENC,
	DATA_N_SUM,
	DATA_N_PRI,
	DATA_N_SHA,
	DATA_N_BAR,
	DATA_N_NIN,

	DATA_N_SKILL_NAME_A,
	DATA_N_SKILL_NAME_B,
	DATA_N_SKILL_LEV,
	DATA_N_SKILL_EXP,
	DATA_N_SKILL_NEED_EXP,

	DATA_N_SKILL_A_00,
	DATA_N_SKILL_A_01,
	DATA_N_SKILL_A_02,
	DATA_N_SKILL_A_03,
	DATA_N_SKILL_A_04,
	DATA_N_SKILL_A_05,
	DATA_N_SKILL_A_06,
	DATA_N_SKILL_A_07,
	DATA_N_SKILL_A_08,
	DATA_N_SKILL_A_09,

	DATA_N_SKILL_B_00,
	DATA_N_SKILL_B_01,
	DATA_N_SKILL_B_02,
	DATA_N_SKILL_B_03,
	DATA_N_SKILL_B_04,
	DATA_N_SKILL_B_05,
	DATA_N_SKILL_B_06,
	DATA_N_SKILL_B_07,
	DATA_N_SKILL_B_08,
	DATA_N_SKILL_B_09,

	DATA_N_ITEM_00,
	DATA_N_ITEM_01,
	DATA_N_ITEM_02,
	DATA_N_ITEM_03,
	DATA_N_ITEM_04,
	DATA_N_ITEM_05,
	DATA_N_ITEM_06,
	DATA_N_ITEM_07,
	DATA_N_ITEM_08,
	DATA_N_ITEM_09,
	DATA_N_ITEM_10,
	DATA_N_ITEM_11,
	DATA_N_ITEM_12,
	DATA_N_ITEM_13,
	DATA_N_ITEM_14,
	DATA_N_ITEM_15,

	DATA_N_EQUIP_WIELDING,
	DATA_N_EQUIP_SHIELD,
	DATA_N_EQUIP_BOW,
	DATA_N_EQUIP_ARW,
	DATA_N_EQUIP_HEAD,
	DATA_N_EQUIP_NECK,
	DATA_N_EQUIP_BODY,
	DATA_N_EQUIP_ABOUT_BODY,
	DATA_N_EQUIP_ARM,
	DATA_N_EQUIP_RIGHT_HAND,
	DATA_N_EQUIP_LEFT_HAND,
	DATA_N_EQUIP_FEET,
	DATA_N_EQUIP_LIGHT_SOURCE,

	DATA_N_SWAP_PAGE_MBR,
	DATA_N_PREV_PAGE,
	DATA_N_NEXT_PAGE,

	DATA_N_MAX_N,
} data_n_t;

/***************************************************************
* 編集するクラス・データの種類
***************************************************************/

typedef enum {
	EDIT_CLASS_NULL,

	EDIT_CLASS_HP,
	EDIT_CLASS_MP,
	EDIT_CLASS_DEX,
	EDIT_CLASS_STR,
	EDIT_CLASS_AGI,
	EDIT_CLASS_INT,
	EDIT_CLASS_WIS,
	EDIT_CLASS_CHA,

	EDIT_CLASS_TOTAL,

	EDIT_CLASS_NAME,

	EDIT_CLASS_FIG,
	EDIT_CLASS_MON,
	EDIT_CLASS_HUN,
	EDIT_CLASS_THI,
	EDIT_CLASS_MAG,
	EDIT_CLASS_SOR,
	EDIT_CLASS_ENC,
	EDIT_CLASS_SUM,
	EDIT_CLASS_PRI,
	EDIT_CLASS_SHA,
	EDIT_CLASS_BAR,
	EDIT_CLASS_NIN,

	EDIT_CLASS_PREV,
	EDIT_CLASS_NEXT,

	EDIT_CLASS_MAX_N,
} edit_class_t;

/***************************************************************
* 編集するスキル・データの種類
***************************************************************/

typedef enum {
	EDIT_SKILL_NULL,

	EDIT_SKILL_A_00,
	EDIT_SKILL_A_01,
	EDIT_SKILL_A_02,
	EDIT_SKILL_A_03,
	EDIT_SKILL_A_04,
	EDIT_SKILL_A_05,
	EDIT_SKILL_A_06,
	EDIT_SKILL_A_07,
	EDIT_SKILL_A_08,
	EDIT_SKILL_A_09,

	EDIT_SKILL_CLASS_NAME,

	EDIT_SKILL_B_00,
	EDIT_SKILL_B_01,
	EDIT_SKILL_B_02,
	EDIT_SKILL_B_03,
	EDIT_SKILL_B_04,
	EDIT_SKILL_B_05,
	EDIT_SKILL_B_06,
	EDIT_SKILL_B_07,
	EDIT_SKILL_B_08,
	EDIT_SKILL_B_09,

	EDIT_SKILL_PREV,
	EDIT_SKILL_NEXT,

	EDIT_SKILL_MAX_N,
} edit_skill_t;

#endif	/* DRAW_H */

