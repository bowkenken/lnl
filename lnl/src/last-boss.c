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
* $Id: last-boss.c,v 1.96 2014/01/08 01:01:27 bowkenken Exp $
***************************************************************/

/***************************************************************
* ラスボス
***************************************************************/

#define	LAST_BOSS_C
#include	"inc.h"

/***************************************************************
* 定数定義
***************************************************************/

#define	FRAME_SKIP_MAX	4

/***************************************************************
* 変数定義
***************************************************************/

static const long	EXEL_JUMP_MAX_Y = AREA_MAX_Y;
static const long	EXEL_ENTER_WAIT_FRAME_N = 4;
static const long	EXEL_HYPER_PERFECT_WAIT_FRAME_N = 20;
static const long	EXEL_HYPER_NORMAL_WAIT_FRAME_N = 40;

static const long	EXELER_ENTER_WAIT_FRAME_N = 4;
static const long	EXELER_HYPER_PERFECT_WAIT_FRAME_N = 20;
static const long	EXELER_HYPER_NORMAL_WAIT_FRAME_N = 40;

static const long	REDRAW_ALL_WAIT_FRAME_N = 40;
static const long	ANIM_XEX_EARTHQUAKE_GUI_FRAME_N = 1;
static const long	ANIM_XEX_EARTHQUAKE_CUI_FRAME_N = 6;
static const long	ANIM_XEX_EARTHQUAKE_MAX_SEC = 20;
static const long	XX_ENTER_WAIT = 3;

static const long	XX_CORE_OFFSET_X = 0;
static const long	XX_CORE_OFFSET_Y = 2;

check_memory_def( check_memory_last_boss_c_EXEL_JUMP_MAX_Y )

/***************************************************************
* XX
***************************************************************/

#include	"last-boss-tab.h"

static pos_t	xx_pos;
static pos_t	g_core;
static last_boss_ptn_t	last_boss_ptn_bg;
static last_boss_ptn_t	last_boss_ptn_fg;
static long	g_frame_skip;

check_memory_def( check_memory_last_boss_c_xx_pos )

/* 関節 */

static last_boss_joint_t	*joint_skull;
static last_boss_joint_t	*joint_skull_to_jaw;
static last_boss_joint_t	*joint_jaw_to_skull;
static last_boss_joint_t	*joint_jaw_to_skull_open;
static last_boss_joint_t	*joint_body;
static last_boss_joint_t	*joint_body_to_upper_arm_left;
static last_boss_joint_t	*joint_body_to_upper_arm_right;
static last_boss_joint_t	*joint_upper_arm_to_body_left;
static last_boss_joint_t	*joint_upper_arm_to_body_right;
static last_boss_joint_t	*joint_upper_arm_to_fore_arm_left;
static last_boss_joint_t	*joint_upper_arm_to_fore_arm_right;
static last_boss_joint_t	*joint_fore_arm_to_upper_arm_left;
static last_boss_joint_t	*joint_fore_arm_to_upper_arm_right;
static last_boss_joint_t	*joint_fore_arm_to_upper_arm_slap_left;
static last_boss_joint_t	*joint_fore_arm_to_upper_arm_slap_right;
static last_boss_joint_t	*joint_fore_arm_to_hand_left;
static last_boss_joint_t	*joint_fore_arm_to_hand_right;
static last_boss_joint_t	*joint_fore_arm_to_hand_slap_left;
static last_boss_joint_t	*joint_fore_arm_to_hand_slap_right;
static last_boss_joint_t	*joint_hand_to_fore_arm_left;
static last_boss_joint_t	*joint_hand_to_fore_arm_right;
static last_boss_joint_t	*joint_hand_to_fore_arm_slap_left;
static last_boss_joint_t	*joint_hand_to_fore_arm_slap_right;

check_memory_def( check_memory_last_boss_c_joint_skull )

static pos_t	pos_skull;
static pos_t	pos_jaw;
static pos_t	pos_jaw_open;
static pos_t	pos_body;
static pos_t	pos_upper_arm_left;
static pos_t	pos_upper_arm_right;
static pos_t	pos_fore_arm_left;
static pos_t	pos_fore_arm_right;
static pos_t	pos_fore_arm_slap_left;
static pos_t	pos_fore_arm_slap_right;
static pos_t	pos_hand_left;
static pos_t	pos_hand_right;
static pos_t	pos_hand_slap_left;
static pos_t	pos_hand_slap_right;

check_memory_def( check_memory_last_boss_c_pos_skull )

static bool_t	flg_open_xx_jaw;
static bool_t	flg_slap_xx_arm_left;
static bool_t	flg_slap_xx_arm_right;

check_memory_def( check_memory_last_boss_c_flg_open_xx_jaw )

/***************************************************************
* XX の火熱攻撃
***************************************************************/

static const long	XX_HEAT_ANIME_N = 1;

/* 爆風の間隔 */
static const long	XX_HEAT_DY = 3;
static const long	XX_HEAT_BLAST_ANIME_N = 5;
check_memory_def( check_memory_last_boss_c_XX_HEAT_DY )

static const long	XX_HEAT_WAIT_FRAME_N = 3;
check_memory_def( check_memory_last_boss_c_XX_HEAT_WAIT_FRAME_N )

static blast_t	xx_blast_heat[] = {
	{
		0, 0, 0, 0,
		' ',
		{
			"**",
			"",
		},
	},
	{
		0, 0, 0, 0,
		' ',
		{
			"  **  ",
			"******",
			"  **  ",
			"",
		},
	},
	{
		0, 0, 0, 0,
		' ',
		{
			"    **    ",
			"  ******  ",
			"**********",
			"  ******  ",
			"    **    ",
			"",
		},
	},
	{
		0, 0, 0, 0,
		' ',
		{
			"  **  ",
			"******",
			"  **  ",
			"",
		},
	},
};
check_memory_def( check_memory_last_boss_c_xx_blast_heat )

/***************************************************************
* XX の水冷攻撃
***************************************************************/

static const rate_t	XX_COLD_LASER_MAX_LEN = 10;
static const rate_t	XX_COLD_LASER_ADD_LEN = 1;
check_memory_def( check_memory_last_boss_c_XX_COLD_LASER_MAX_LEN )

static const long	XX_COLD_BIT_WAIT_FRAME_N = 3;
static const long	XX_COLD_NEXT_WAIT_FRAME_N = 10;
static const long	XX_COLD_LASER_WAIT_FRAME_N = 3;
static const long	XX_COLD_END_WAIT_FRAME_N = 20;
check_memory_def( check_memory_last_boss_c_XX_COLD_BIT_WAIT_FRAME_N )

static const char	*xx_laser[MBR_MAX_N] = {
	"|",
	"|",
	"\\",
	"/",
	"-",
	"-",
};
check_memory_def( check_memory_last_boss_c_xx_laser )

static pos_t	xx_laser_dxy[MBR_MAX_N] = {
	{ +-0,  +1 },
	{ +-0,  +1 },
	{  +1,  +1 },
	{  -1,  +1 },
	{  +1, +-0 },
	{  -1, +-0 },
};
check_memory_def( check_memory_last_boss_c_xx_laser_dxy )

static blast_t	xx_bit[MBR_MAX_N] = {
	{
		0, 0, 0, 0,
		' ',
		{
			"\\ /",
			" O ",
			" | ",
			"",
		},
	},
	{
		0, 0, 0, 0,
		' ',
		{
			"\\ /",
			" O ",
			" | ",
			"",
		},
	},
	{
		0, 0, 0, 0,
		' ',
		{
			" | ",
			"-O ",
			"  \\",
			"",
		},
	},
	{
		0, 0, 0, 0,
		' ',
		{
			" | ",
			" O-",
			"/  ",
			"",
		},
	},
	{
		0, 0, 0, 0,
		' ',
		{
			"\\  ",
			" O-",
			"/  ",
			"",
		},
	},
	{
		0, 0, 0, 0,
		' ',
		{
			"  /",
			"-O ",
			"  \\",
			"",
		},
	},
};
check_memory_def( check_memory_last_boss_c_xx_bit )

/***************************************************************
* XX の風心攻撃
***************************************************************/

static const rate_t	XX_MIND_ADD_RATE = 10;
check_memory_def( check_memory_last_boss_c_XX_MIND_ADD_RATE )

static const long	XX_MIND_ANIME_N = 3;
static const long	XX_MIND_WAIT_FRAME_N = 3;
check_memory_def( check_memory_last_boss_c_XX_MIND_ANIME_N )

static const char	*xx_refract_head = "**";
static const char	*xx_refract_image = "oo";
check_memory_def( check_memory_last_boss_c_xx_refract_head )

static void xx_mind_refract( xx_mind_t *xx_mind );
static void xx_mind_move( xx_mind_t *xx_mind );
static void xx_mind_draw( xx_mind_t *xx_mind );

/***************************************************************
* XX の土酸攻撃
***************************************************************/

static const long	XX_ACID_ANIME_N = 1;

static const long	XX_ACID_MAX_Q = 18;
check_memory_def( check_memory_last_boss_c_XX_ACID_MAX_Q )

static const long	XX_ACID_WAIT_FRAME_N = 3;
check_memory_def( check_memory_last_boss_c_XX_ACID_WAIT_FRAME_N )

#define	XX_ACID_HOMING_V	(1 * XX_ACID_HOMING_FIX_POINT)
static pos_t	xx_homing_bgn_v[MBR_MAX_N] = {
	{ 0, -XX_ACID_HOMING_V },
	{ 0, -XX_ACID_HOMING_V },
	{ -XX_ACID_HOMING_V, -XX_ACID_HOMING_V },
	{ +XX_ACID_HOMING_V, -XX_ACID_HOMING_V },
	{ -XX_ACID_HOMING_V, 0 },
	{ +XX_ACID_HOMING_V, 0 },
};
check_memory_def( check_memory_last_boss_c_xx_homing_bgn_v )

static const char	*xx_homing_head = "OO";
static const char	*xx_homing_image = "oo";
static const char	*xx_homing_tail = "++";
check_memory_def( check_memory_last_boss_c_xx_homing_head )

static bool_t xx_acid_chk_end( xx_acid_t *xx_acid );
static void xx_acid_move( xx_acid_t *xx_acid );
static void xx_acid_draw( xx_acid_t *xx_acid );

/***************************************************************
* XX の回転弾攻撃
***************************************************************/

static const long	XX_ROTATION_ANIME_N = 1;
static const long	XX_ROTATION_WAIT_FRAME_N = 6;
check_memory_def( check_memory_last_boss_c_XX_ROTATION_ANIME_N )

static const char	*xx_rotation_str = "o";
check_memory_def( check_memory_last_boss_c_xx_rotation_str )

/***************************************************************
* XX の渦巻き弾攻撃
***************************************************************/

static const long	XX_WHIRL_ANIME_N = 1;
static const long	XX_WHIRL_WAIT_FRAME_N = 3;
check_memory_def( check_memory_last_boss_c_XX_WHIRL_ANIME_N )

static const char	*xx_whirl_str = "x";
check_memory_def( check_memory_last_boss_c_xx_whirl_str )

/***************************************************************
* XX の扇弾攻撃
***************************************************************/

static const long	XX_FAN_ANIME_N = 1;
static const long	XX_FAN_WAIT_FRAME_N = 3;
check_memory_def( check_memory_last_boss_c_XX_FAN_ANIME_N )

static const char	*xx_fan_str = "*";
check_memory_def( check_memory_last_boss_c_xx_fan_str )

/***************************************************************
* XX の平手打ち攻撃
***************************************************************/

static const long	XX_SLAP_ANIME_N = 1;
static const long	XX_SLAP_WAIT_FRAME_N = 60;
check_memory_def( check_memory_last_boss_c_XX_SLAP_WAIT_FRAME_N )

static attack_t	xx_attack_slap[] = {
	{ ATTACK_KIND_XX_SLAP, 1, FALSE, TRUE,
		WPN_HIT_UNARMED, WPN_CRTCL_UNARMED, WPN_DAM_UNARMED,
		RESI_KIND_KNOC, 1, 1,
		FX_KIND_NULL, 0,
		SPELL_KIND_NULL,
		EXTENT_KIND_NULL, N_MSG_NULL, },
	{ ATTACK_KIND_NULL, 0, FALSE, FALSE,
		0, 0, 0,
		RESI_KIND_MAX_N, 1, 1,
		FX_KIND_NULL, 0,
		SPELL_KIND_NULL,
		EXTENT_KIND_NULL, N_MSG_NULL, },
};
check_memory_def( check_memory_last_boss_c_xx_attack_slap )

/***************************************************************
* 初期化
***************************************************************/

void	init_last_boss( void )
{
	g_frame_skip = 1;
	g_flg_skip_demo_cut_in = FALSE;

	flg_open_xx_jaw = FALSE;
	flg_slap_xx_arm_left = FALSE;
	flg_slap_xx_arm_right = FALSE;

	init_last_boss_parts( &last_boss_parts_skull );
	init_last_boss_parts( &last_boss_parts_jaw );
	init_last_boss_parts( &last_boss_parts_body );
	init_last_boss_parts( &last_boss_parts_upper_arm_left );
	init_last_boss_parts( &last_boss_parts_upper_arm_right );
	init_last_boss_parts( &last_boss_parts_fore_arm_left );
	init_last_boss_parts( &last_boss_parts_fore_arm_right );
	init_last_boss_parts( &last_boss_parts_fore_arm_slap_left );
	init_last_boss_parts( &last_boss_parts_fore_arm_slap_right );
	init_last_boss_parts( &last_boss_parts_hand_left );
	init_last_boss_parts( &last_boss_parts_hand_right );
	init_last_boss_parts( &last_boss_parts_hand_slap_left );
	init_last_boss_parts( &last_boss_parts_hand_slap_right );

	/* 関節の座標を計算 */

	/* 頭と顎 */

	joint_skull_to_jaw = get_joint( &last_boss_parts_skull,
			JOINT_CHR_SKULL_TO_JAW );
	if( joint_skull_to_jaw == NULL )
		return;

	joint_jaw_to_skull = get_joint( &last_boss_parts_jaw,
			JOINT_CHR_SKULL_TO_JAW );
	if( joint_jaw_to_skull == NULL )
		return;

	joint_jaw_to_skull_open = get_joint( &last_boss_parts_jaw,
			JOINT_CHR_JAW_TO_SKULL_OPEN );
	if( joint_jaw_to_skull_open == NULL )
		return;

	/* 頭と胴体 */

	joint_skull = get_joint( &last_boss_parts_skull,
			JOINT_CHR_SKULL_TO_BODY );
	if( joint_skull == NULL )
		return;

	joint_body = get_joint( &last_boss_parts_body,
			JOINT_CHR_SKULL_TO_BODY );
	if( joint_body == NULL )
		return;

	/* 胴体と左上腕 */

	joint_body_to_upper_arm_left = get_joint(
			&last_boss_parts_body,
			JOINT_CHR_BODY_TO_UPPER_ARM_LEFT );
	if( joint_body_to_upper_arm_left == NULL )
		return;

	joint_upper_arm_to_body_left = get_joint(
			&last_boss_parts_upper_arm_left,
			JOINT_CHR_BODY_TO_UPPER_ARM_LEFT );
	if( joint_upper_arm_to_body_left == NULL )
		return;

	/* 左上腕と前腕 */

	joint_upper_arm_to_fore_arm_left = get_joint(
			&last_boss_parts_upper_arm_left,
			JOINT_CHR_UPPER_ARM_TO_FORE_ARM_LEFT );
	if( joint_upper_arm_to_fore_arm_left == NULL )
		return;

	joint_fore_arm_to_upper_arm_left = get_joint(
			&last_boss_parts_fore_arm_left,
			JOINT_CHR_UPPER_ARM_TO_FORE_ARM_LEFT );
	if( joint_fore_arm_to_upper_arm_left == NULL )
		return;

	joint_fore_arm_to_upper_arm_slap_left = get_joint(
			&last_boss_parts_fore_arm_slap_left,
			JOINT_CHR_UPPER_ARM_TO_FORE_ARM_SLAP_LEFT );
	if( joint_fore_arm_to_upper_arm_slap_left == NULL )
		return;

	/* 左前腕と手 */

	joint_fore_arm_to_hand_left = get_joint(
			&last_boss_parts_fore_arm_left,
			JOINT_CHR_FORE_ARM_TO_HAND_LEFT );
	if( joint_fore_arm_to_hand_left == NULL )
		return;

	joint_hand_to_fore_arm_left = get_joint(
			&last_boss_parts_hand_left,
			JOINT_CHR_FORE_ARM_TO_HAND_LEFT );
	if( joint_hand_to_fore_arm_left == NULL )
		return;

	joint_fore_arm_to_hand_slap_left = get_joint(
			&last_boss_parts_fore_arm_slap_left,
			JOINT_CHR_FORE_ARM_TO_HAND_SLAP_LEFT );
	if( joint_fore_arm_to_hand_slap_left == NULL )
		return;

	joint_hand_to_fore_arm_slap_left = get_joint(
			&last_boss_parts_hand_slap_left,
			JOINT_CHR_FORE_ARM_TO_HAND_SLAP_LEFT );
	if( joint_hand_to_fore_arm_slap_left == NULL )
		return;

	/* 胴体と右上腕 */

	joint_body_to_upper_arm_right = get_joint(
			&last_boss_parts_body,
			JOINT_CHR_BODY_TO_UPPER_ARM_RIGHT );
	if( joint_body_to_upper_arm_right == NULL )
		return;

	joint_upper_arm_to_body_right = get_joint(
			&last_boss_parts_upper_arm_right,
			JOINT_CHR_BODY_TO_UPPER_ARM_RIGHT );
	if( joint_upper_arm_to_body_right == NULL )
		return;

	/* 右上腕と前腕 */

	joint_upper_arm_to_fore_arm_right = get_joint(
			&last_boss_parts_upper_arm_right,
			JOINT_CHR_UPPER_ARM_TO_FORE_ARM_RIGHT );
	if( joint_upper_arm_to_fore_arm_right == NULL )
		return;

	joint_fore_arm_to_upper_arm_right = get_joint(
			&last_boss_parts_fore_arm_right,
			JOINT_CHR_UPPER_ARM_TO_FORE_ARM_RIGHT );
	if( joint_fore_arm_to_upper_arm_right == NULL )
		return;

	joint_fore_arm_to_upper_arm_slap_right = get_joint(
			&last_boss_parts_fore_arm_slap_right,
			JOINT_CHR_UPPER_ARM_TO_FORE_ARM_SLAP_RIGHT );
	if( joint_fore_arm_to_upper_arm_slap_right == NULL )
		return;

	/* 右前腕と手 */

	joint_fore_arm_to_hand_right = get_joint(
			&last_boss_parts_fore_arm_right,
			JOINT_CHR_FORE_ARM_TO_HAND_RIGHT );
	if( joint_fore_arm_to_hand_right == NULL )
		return;

	joint_hand_to_fore_arm_right = get_joint(
			&last_boss_parts_hand_right,
			JOINT_CHR_FORE_ARM_TO_HAND_RIGHT );
	if( joint_hand_to_fore_arm_right == NULL )
		return;

	joint_fore_arm_to_hand_slap_right = get_joint(
			&last_boss_parts_fore_arm_slap_right,
			JOINT_CHR_FORE_ARM_TO_HAND_SLAP_RIGHT );
	if( joint_fore_arm_to_hand_slap_right == NULL )
		return;

	joint_hand_to_fore_arm_slap_right = get_joint(
			&last_boss_parts_hand_slap_right,
			JOINT_CHR_FORE_ARM_TO_HAND_SLAP_RIGHT );
	if( joint_hand_to_fore_arm_slap_right == NULL )
		return;
}

/***************************************************************
* XX のパターンのパーツを初期化
* last_boss_parts_t *parts : パーツ
***************************************************************/

void	init_last_boss_parts( last_boss_parts_t *parts )
{
	long	x, y;
	char	mjr, mnr;
	last_boss_joint_t	*joint;

	if( parts == NULL )
		return;

	for( y = 0; y < MAP_MAX_Y; y++ ){
		if( parts->ptn[y] == NULL )
			break;

		for( x = 0; x < MAP_MAX_X; x++ ){
			mjr = parts->ptn[y][x * 2 + 0];
			if( mjr == '\0' )
				break;
			if( mjr != g_joint_chr )
				continue;

			mnr = parts->ptn[y][x * 2 + 1];
			if( mnr == '\0' )
				break;

			joint = get_joint( parts, mnr );
			if( joint == NULL )
				continue;

			joint->x = x;
			joint->y = y;
		}
	}
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_last_boss( void )
{
}

/***************************************************************
* ラスト・ステージで呪文が使えるか調べる
* spell_kind_t spell_kind : 呪文の種類
* return : 呪文が使えるか
***************************************************************/

bool_t	chk_last_boss_can_spell( spell_kind_t spell_kind )
{
	long	i;

	if( get_scene() != SCENE_N_LAST_BOSS )
		return TRUE;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( last_boss_no_spell_ls[i] == SPELL_KIND_NULL )
			break;

		if( last_boss_no_spell_ls[i] == spell_kind )
			return FALSE;
	}

	return TRUE;
}

/***************************************************************
* デモ中かチェック
* return : デモ中か?
***************************************************************/

bool_t	chk_last_boss_demo( void )
{
	if( get_scene() != SCENE_N_LAST_BOSS )
		return FALSE;

	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
		return FALSE;
	case LAST_SCENE_N_ENCOUNTER:
		return FALSE;
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
		return TRUE;
	case LAST_SCENE_N_EXEL:
		return FALSE;
	case LAST_SCENE_N_EXEL_ENTER:
	case LAST_SCENE_N_EXEL_CUT_IN:
	case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_CUT_OUT:
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
		return TRUE;
	case LAST_SCENE_N_EXEL_BATTLE:
		return FALSE;
	case LAST_SCENE_N_EXEL_DIE:
		return TRUE;
	case LAST_SCENE_N_EXELER:
		return FALSE;
	case LAST_SCENE_N_EXELER_CUT_IN:
	case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_CUT_OUT:
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
		return TRUE;
	case LAST_SCENE_N_EXELER_BATTLE:
		return FALSE;
	case LAST_SCENE_N_EXELER_DIE:
		return TRUE;
	case LAST_SCENE_N_XEX:
		return FALSE;
	case LAST_SCENE_N_XEX_CUT_IN:
	case LAST_SCENE_N_XEX_WORDS:
	case LAST_SCENE_N_XEX_CUT_OUT:
	case LAST_SCENE_N_XEX_CUT_END:
		return TRUE;
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
		return TRUE;
	case LAST_SCENE_N_XX_BATTLE:
		return FALSE;
	case LAST_SCENE_N_XX_DIE:
		return TRUE;
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* デモ中に描画が可能かチェック
* return : 描画が可能か?
***************************************************************/

bool_t	chk_draw_last_boss( void )
{
	if( get_scene() != SCENE_N_LAST_BOSS )
		return TRUE;

	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
		return TRUE;
	case LAST_SCENE_N_ENCOUNTER:
		return TRUE;
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
		return FALSE;
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
		return TRUE;
	case LAST_SCENE_N_EXEL:
	case LAST_SCENE_N_EXEL_ENTER:
		return TRUE;
	case LAST_SCENE_N_EXEL_CUT_IN:
	case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_CUT_OUT:
		return FALSE;
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
	case LAST_SCENE_N_EXEL_BATTLE:
	case LAST_SCENE_N_EXEL_DIE:
		return TRUE;
	case LAST_SCENE_N_EXELER:
		return TRUE;
	case LAST_SCENE_N_EXELER_CUT_IN:
	case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_CUT_OUT:
		return FALSE;
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
	case LAST_SCENE_N_EXELER_BATTLE:
	case LAST_SCENE_N_EXELER_DIE:
		return TRUE;
	case LAST_SCENE_N_XEX:
		return TRUE;
	case LAST_SCENE_N_XEX_CUT_IN:
	case LAST_SCENE_N_XEX_WORDS:
	case LAST_SCENE_N_XEX_CUT_OUT:
		return FALSE;
	case LAST_SCENE_N_XEX_CUT_END:
		return TRUE;
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
	case LAST_SCENE_N_XX_BATTLE:
	case LAST_SCENE_N_XX_DIE:
		return TRUE;
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		return TRUE;
	}

	return TRUE;
}

/***************************************************************
* シーンに応じてデモを描画
***************************************************************/

void	draw_last_boss( void )
{
	long	sc;
	bool_t	flg_next_cui, flg_next_gui;
	mnstr_t	*p;

	if( get_scene() != SCENE_N_LAST_BOSS )
		return;

	sc = get_last_scene();
	flg_next_gui = call_demo_last_boss_check_done();
	flg_next_cui = TRUE;

	switch( (last_scene_n_t)sc ){
	case LAST_SCENE_N_NULL:
		break;
	case LAST_SCENE_N_ENTER:
		flg_next_cui = FALSE;
		break;
	case LAST_SCENE_N_ENCOUNTER:
		scroll_last_boss();
		draw_exel();
		draw_exeler();
		draw_xex();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
		break;
	case LAST_SCENE_N_ENCOUNTER_WORDS:
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_1 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_2 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_3 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_4 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_5 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_6 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_7 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_8 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_9 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_ENCOUNTER_XEX_10 );
		draw_words_exel( MSG_WORDS_LAST_BOSS_ENCOUNTER_EXEL_1 );
		draw_words_exeler( MSG_WORDS_LAST_BOSS_ENCOUNTER_EXELER_1 );
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXEL:
		scroll_last_boss();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXEL_ENTER:
		set_vfx_wait( _100_PERCENT );
		draw_exel_enter();
		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXEL_CUT_IN:
		break;
	case LAST_SCENE_N_EXEL_WORDS:
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		draw_words_exel( MSG_WORDS_LAST_BOSS_EXEL_1 );
		break;
	case LAST_SCENE_N_EXEL_CUT_OUT:
		break;
	case LAST_SCENE_N_EXEL_CUT_END:
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXEL_HYPER:
		draw_exel_hyper();
		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXEL_BATTLE:
		p = get_last_boss( LAST_BOSS_KIND_EXEL );
		if( p == NULL ){
			flg_next_cui = TRUE;
			break;
		}
		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			flg_next_cui = TRUE;
		} else {
			flg_next_cui = FALSE;
		}
		break;
	case LAST_SCENE_N_EXEL_DIE:
		draw_words_exel( MSG_WORDS_LAST_BOSS_EXEL_DIE_1 );

		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXELER:
		scroll_last_boss();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXELER_CUT_IN:
		break;
	case LAST_SCENE_N_EXELER_WORDS:
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		draw_words_exeler( MSG_WORDS_LAST_BOSS_EXELER_1 );
		draw_words_exeler( MSG_WORDS_LAST_BOSS_EXELER_2 );
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXELER_CUT_OUT:
		break;
	case LAST_SCENE_N_EXELER_CUT_END:
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXELER_ENTER:
		draw_exeler_enter();
		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXELER_HYPER:
		draw_exeler_hyper();
		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_EXELER_BATTLE:
		p = get_last_boss( LAST_BOSS_KIND_EXELER );
		if( p == NULL ){
			flg_next_cui = TRUE;
			break;
		}
		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			flg_next_cui = TRUE;
		} else {
			flg_next_cui = FALSE;
		}
		break;
	case LAST_SCENE_N_EXELER_DIE:
		draw_words_exeler( MSG_WORDS_LAST_BOSS_EXELER_DIE_1 );

		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_XEX:
		scroll_last_boss();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_XEX_CUT_IN:
		break;
	case LAST_SCENE_N_XEX_WORDS:
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		draw_words_xex( MSG_WORDS_LAST_BOSS_XEX_1 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_XEX_2 );
		draw_words_xex( MSG_WORDS_LAST_BOSS_XEX_3 );
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_XEX_CUT_OUT:
		break;
	case LAST_SCENE_N_XEX_CUT_END:
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_XX_ENTER:
		draw_xx_enter();
		break;
	case LAST_SCENE_N_XX_WORDS:
		set_xx_enter();

		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		draw_words_xx( MSG_WORDS_LAST_BOSS_XX_1 );
		draw_words_xx( MSG_WORDS_LAST_BOSS_XX_2 );
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );

		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_XX_BATTLE:
		p = get_last_boss( LAST_BOSS_KIND_XX );
		if( p == NULL ){
			flg_next_cui = TRUE;
			break;
		}
		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			flg_next_cui = TRUE;
		} else {
			flg_next_cui = FALSE;
		}
		break;
	case LAST_SCENE_N_XX_DIE:
		scroll_last_boss();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );

		draw_words_xx( MSG_WORDS_LAST_BOSS_XX_DIE_1 );

		redraw_all();
		wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
		break;
	case LAST_SCENE_N_END:
		ending();
		break;
	case LAST_SCENE_N_MAX_N:
		flg_next_cui = FALSE;
		break;
	}

	if( flg_next_cui && flg_next_gui ){
		sc++;
		if( sc > LAST_SCENE_N_END )
			sc = LAST_SCENE_N_END;

		call_demo_last_boss_reset();
		change_last_scene( (last_scene_n_t)sc );
	}
}

/***************************************************************
* エクセルの台詞を表示
* const char *str : 台詞
***************************************************************/

void	draw_words_exel( const char *str )
{
	print_words( MSG_MNSTR_EXEL, MALE, str, str );
	draw_words( MSG_MNSTR_EXEL, str );
}

/***************************************************************
* エクセラーの台詞を表示
* const char *str : 台詞
***************************************************************/

void	draw_words_exeler( const char *str )
{
	print_words( MSG_MNSTR_EXELER, FEMALE, str, str );
	draw_words( MSG_MNSTR_EXELER, str );
}

/***************************************************************
* ゼクスの台詞を表示
* const char *str : 台詞
***************************************************************/

void	draw_words_xex( const char *str )
{
	print_words( MSG_MNSTR_XEX, MALE, str, str );
	draw_words( MSG_MNSTR_XEX, str );
}

/***************************************************************
* トゥエンティースの台詞を表示
* const char *str : 台詞
***************************************************************/

void	draw_words_xx( const char *str )
{
	print_words( MSG_MNSTR_XX, MALE, str, str );
	draw_words( MSG_MNSTR_XX, str );
}

/***************************************************************
* エクセルの描画
***************************************************************/

void	draw_exel( void )
{
	mnstr_t	*p;

	p = get_last_boss( LAST_BOSS_KIND_EXEL );
	set_map_chr( p );
	draw_mnstr( p );
}

/***************************************************************
* エクセルの登場デモ
***************************************************************/

void	draw_exel_enter( void )
{
	mnstr_t	*p, *p2, *p3;
	long	x, y;
	long	bgn_x, bgn_y;
	pos_t	end_pos;
	long	dy;

	p = get_last_boss( LAST_BOSS_KIND_EXEL );
	if( p == NULL )
		return;
	p2 = get_last_boss( LAST_BOSS_KIND_EXELER );
	p3 = get_last_boss( LAST_BOSS_KIND_XEX );

	end_pos = get_map_event_pos( MAP_EVENT_LAST_BOSS_BATTLE_BOSS );
	bgn_x = p->x;
	bgn_y = p->y;

	for( dy = 0; dy < EXEL_JUMP_MAX_Y; dy++ ){
		x = bgn_x;
		y = bgn_y - dy;

		set_pos_last_boss( p, x, y );
		set_map_chr( p2 );
		set_map_chr( p3 );

		draw_mnstr( p );
		draw_mnstr( p2 );
		draw_mnstr( p3 );
		call_pcg_dun_draw_turn( FALSE );
		wait_clock( EXEL_ENTER_WAIT_FRAME_N );
	}

	for( dy = EXEL_JUMP_MAX_Y; dy >= 0; dy-- ){
		x = end_pos.x;
		y = end_pos.y - dy;

		set_pos_last_boss( p, x, y );
		set_map_chr( p2 );
		set_map_chr( p3 );

		draw_mnstr( p );
		draw_mnstr( p2 );
		draw_mnstr( p3 );
		call_pcg_dun_draw_turn( FALSE );
		wait_clock( EXEL_ENTER_WAIT_FRAME_N );
	}
}

/***************************************************************
* エクセルの大型化のデモ
***************************************************************/

void	draw_exel_hyper( void )
{
	mnstr_t	*p;
	long	x, y;
	long	i;

	p = get_last_boss( LAST_BOSS_KIND_EXEL );
	if( p == NULL )
		return;

	for( i = HYPER_BOSS_NORMAL; i <= HYPER_BOSS_PERFECT; i++ ){
		/* 通常サイズ */

		x = p->x;
		y = p->y;
		clr_map_chr( p );

		p->work.hyper_boss = (hyper_boss_t)i;
		p->work.flg_hyper_boss = FALSE;

		p->x = x;
		p->y = y;
		set_map_chr( p );

		draw_mnstr( p );
		call_pcg_dun_draw_turn( FALSE );
		wait_clock( EXEL_HYPER_NORMAL_WAIT_FRAME_N );

		/* 大型化 */

		x = p->x;
		y = p->y;
		clr_map_chr( p );

		p->work.hyper_boss = (hyper_boss_t)i;
		p->work.flg_hyper_boss = TRUE;

		p->x = x;
		p->y = y;
		set_map_chr( p );

		draw_mnstr( p );
		call_pcg_dun_draw_turn( FALSE );
		wait_clock( EXEL_HYPER_PERFECT_WAIT_FRAME_N );
	}
}

/***************************************************************
* エクセラーの描画
***************************************************************/

void	draw_exeler( void )
{
	mnstr_t	*p;

	p = get_last_boss( LAST_BOSS_KIND_EXELER );
	set_map_chr( p );
	draw_mnstr( p );
}

/***************************************************************
* エクセラーの登場デモ
***************************************************************/

void	draw_exeler_enter( void )
{
	const long	d = 16;
	const long	aavx = 2;
	const long	ivx = +16;
	const long	avy = +3;
	pos_t	end_pos;
	long	pre_sgn_x, sgn_x;
	long	avx;
	long	vx, vy;
	long	xx, yy;
	long	x, y;
	mnstr_t	*p, *p2, *p3;
	bool_t	flg_end;

	p = get_last_boss( LAST_BOSS_KIND_EXELER );
	if( p == NULL )
		return;
	p2 = get_last_boss( LAST_BOSS_KIND_EXEL );
	p3 = get_last_boss( LAST_BOSS_KIND_XEX );

	end_pos = get_map_event_pos( MAP_EVENT_LAST_BOSS_BATTLE_BOSS );

	vx = ivx;
	xx = p->x * d;
	yy = p->y * d;
	pre_sgn_x = -1;

	flg_end = FALSE;
	while( !flg_end ){
		sgn_x = sgn_l( (end_pos.x * d) - xx );
		avx = aavx * sgn_x;
		vx += avx;
		xx += vx;
		x = xx / d;

		vy = avy;
		yy += vy;
		y = yy / d;

		if( y >= end_pos.y ){
			y = end_pos.y;
			if( x == end_pos.x )
				flg_end = TRUE;
			if( pre_sgn_x != sgn_x )
				flg_end = TRUE;
		}
		if( flg_end ){
			x = end_pos.x;
			y = end_pos.y;
		}
		pre_sgn_x = sgn_x;

		set_pos_last_boss( p, x, y );
		set_map_chr( p2 );
		set_map_chr( p3 );

		draw_mnstr( p );
		draw_mnstr( p2 );
		draw_mnstr( p3 );
		call_pcg_dun_draw_turn( FALSE );
		wait_clock( EXELER_ENTER_WAIT_FRAME_N );
	}
}

/***************************************************************
* エクセラーの大型化のデモ
***************************************************************/

void	draw_exeler_hyper( void )
{
	mnstr_t	*p;
	long	x, y;
	long	i;

	p = get_last_boss( LAST_BOSS_KIND_EXELER );
	if( p == NULL )
		return;

	for( i = 0; i < 4; i++ ){
		/* 通常サイズ */

		x = p->x;
		y = p->y;
		clr_map_chr( p );

		p->work.hyper_boss = HYPER_BOSS_NORMAL;
		p->work.flg_hyper_boss = FALSE;

		p->x = x;
		p->y = y;
		set_map_chr( p );

		draw_mnstr( p );
		call_pcg_dun_draw_turn( FALSE );
		wait_clock( EXELER_HYPER_NORMAL_WAIT_FRAME_N );

		/* 大型化 */

		x = p->x;
		y = p->y;
		clr_map_chr( p );

		p->work.hyper_boss = HYPER_BOSS_PERFECT;
		p->work.flg_hyper_boss = TRUE;

		p->x = x;
		p->y = y;
		set_map_chr( p );

		draw_mnstr( p );
		call_pcg_dun_draw_turn( FALSE );
		wait_clock( EXELER_HYPER_PERFECT_WAIT_FRAME_N );
	}
}

/***************************************************************
* ゼクスの描画
***************************************************************/

void	draw_xex( void )
{
	mnstr_t	*p;

	p = get_last_boss( LAST_BOSS_KIND_XEX );
	set_map_chr( p );
	draw_mnstr( p );
}

/***************************************************************
* エクセルとエクセラーの登場デモの座標設定
***************************************************************/

void	set_pos_last_boss( mnstr_t *p, long x, long y )
{
	dun_t	*dun;

	dun = get_dun();

	if( clip_pos( p->x, p->y ) )
		clr_map_chr( p );

	if( clip_pos( x, y ) ){
		p->x = x;
		p->y = y;
		if( dun->map.chr.mjr[y][x] == FACE_MJR_NULL ){
			set_map_chr( p );
		} else {
			p->x = MAP_DEL_X;
			p->y = MAP_DEL_Y;
		}
	} else {
		p->x = MAP_DEL_X;
		p->y = MAP_DEL_Y;
	}
}

/***************************************************************
* ゲートを開く
***************************************************************/

void	open_last_boss_gate( void )
{
	dun_t	*dun;
	long	i;

	call_game_sound_play( SOUND_KIND_EVENT_GATE, 1 );

	dun = get_dun();
	for( i = 0; i < dun->door_n; i++ ){
		dun->door[i].flg &= ~(FLG_DOOR_JAMMED | FLG_DOOR_BROKEN);
		dun->door[i].flg &= ~(FLG_DOOR_SECRET | FLG_DOOR_GATE);

		open_door( i );
	}
}

/***************************************************************
* ラスボスのデモを開始
***************************************************************/

void	event_begin_last_boss( long x, long y )
{
	if( get_last_scene() >= LAST_SCENE_N_ENCOUNTER )
		return;

	scroll_last_boss();
	change_last_scene( LAST_SCENE_N_ENCOUNTER );
}

/***************************************************************
* ラスボスのデモに合わせてマップをスクロール
***************************************************************/

void	scroll_last_boss( void )
{
	pos_t	pos;

	appear_party_map_event( MAP_EVENT_LAST_BOSS_BATTLE_PARTY );
	wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );

	pos = get_map_event_pos( MAP_EVENT_LAST_BOSS_SCROLL_MAP );
	scroll_map( pos.x, pos.y );
	call_pcg_dun_scroll( pos.x, pos.y );
	wait_frame_gui( REDRAW_ALL_WAIT_FRAME_N );
}

/***************************************************************
* XX の登場のデモ
***************************************************************/

void	draw_xx_enter( void )
{
	pos_t	*draw, pre_draw, base_draw;
	pos_t	room_pos;
	long	line_top_y, line_bottom_y;
	time_t	bgn_time;
	bool_t	flg_end;
	last_boss_joint_t	*core_joint;
	dun_t	*dun;
	long	i, j;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;
	pre_draw.x = draw->x;
	pre_draw.y = draw->y;

	base_draw.x = draw->x;
	base_draw.y = draw->y;
	if( base_draw.x < 1 )
		base_draw.x = 1;
	if( base_draw.y < 1 )
		base_draw.y = 1;
	if( base_draw.x > (MAP_MAX_X - AREA_MAX_X - 1) )
		base_draw.x = (MAP_MAX_X - AREA_MAX_X - 1);
	if( base_draw.y > (MAP_MAX_Y - AREA_MAX_Y - 1) )
		base_draw.y = (MAP_MAX_Y - AREA_MAX_Y - 1);

	room_pos = get_map_event_pos( MAP_EVENT_LAST_BOSS_SCROLL_MAP );
	if( !clip_pos( room_pos.x, room_pos.y ) )
		return;

	line_top_y = 0;
	line_bottom_y = MAP_MAX_Y - 1;

	bgn_time = time( NULL );
	flg_end = FALSE;

	call_game_sound_play( SOUND_KIND_EVENT_EARTHQUAKE, 20 );

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		/* 床が崩れる */

		for( j = 0; j < 4; j++ ){
			flg_end = draw_xex_breakdown();
			if( flg_end )
				break;
		}
		if( flg_end )
			break;

		chk_die_all_last_boss();

		/* 画面外の床が崩れる */

		if( line_top_y < room_pos.y ){
			draw_xex_breakdown_line( line_top_y );
			line_top_y++;
		}
		if( line_bottom_y > (room_pos.y + AREA_MAX_Y - 1) ){
			draw_xex_breakdown_line( line_bottom_y );
			line_bottom_y--;
		}

		/* 画面を揺らす */

		draw_xex_earthquake( draw, base_draw );

		if( g_flg_cui )
			redraw_map_force();
		call_pcg_dun_scroll( draw->x, draw->y );

		if( g_flg_gui )
			wait_clock( ANIM_XEX_EARTHQUAKE_GUI_FRAME_N );
		else
			wait_clock( ANIM_XEX_EARTHQUAKE_CUI_FRAME_N );

		if( difftime( time( NULL ), bgn_time )
				> ANIM_XEX_EARTHQUAKE_MAX_SEC ){
			break;
		}
	}

	/* 残りの床が崩れる */

	draw_xex_breakdown_all_field();

	/* 溶岩 */

	line_top_y = room_pos.y + (AREA_MAX_Y / 2);
	line_bottom_y = line_top_y + 1;

	bgn_time = time( NULL );

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( (line_top_y < 0) && (MAP_MAX_Y <= line_bottom_y) )
			break;

		/* 溶岩の出現 */

		draw_xex_lava( line_top_y );
		draw_xex_lava( line_bottom_y );
		line_top_y--;
		line_bottom_y++;

		/* ラスボスを描画 */

		if( xx_pos.y > room_pos.y ){
			if( g_flg_cui ){
				if( (i % XX_ENTER_WAIT) == 0 ){
					xx_pos.y -= 1;
				}
			} else {
					xx_pos.y -= 1;
			}
		}
		set_last_boss_ptn();

		/* 画面を揺らす */

		draw_xex_earthquake( draw, base_draw );

		if( g_flg_cui )
			redraw_map_force();
		call_pcg_dun_scroll( draw->x, draw->y );

		if( g_flg_gui )
			wait_clock( ANIM_XEX_EARTHQUAKE_GUI_FRAME_N );
		else
			wait_clock( ANIM_XEX_EARTHQUAKE_CUI_FRAME_N );

		if( difftime( time( NULL ), bgn_time )
				> ANIM_XEX_EARTHQUAKE_MAX_SEC ){
			break;
		}
	}

	xx_pos.x = room_pos.x + (AREA_MAX_X / 2);
	xx_pos.y = room_pos.y + AREA_MAX_Y;

	bgn_time = time( NULL );

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		/* ラスボスを描画 */

		if( xx_pos.y <= room_pos.y ){
			break;
		} else {
			if( g_flg_cui ){
				if( (i % XX_ENTER_WAIT) == 0 ){
					xx_pos.y -= 1;
				}
			} else {
					xx_pos.y -= 1;
			}
		}
		set_last_boss_ptn();

		/* 画面を揺らす */

		draw_xex_earthquake( draw, base_draw );

		if( g_flg_cui )
			redraw_map_force();
		call_pcg_dun_scroll( draw->x, draw->y );

		if( g_flg_gui )
			wait_clock( ANIM_XEX_EARTHQUAKE_GUI_FRAME_N );
		else
			wait_clock( ANIM_XEX_EARTHQUAKE_CUI_FRAME_N );

		if( difftime( time( NULL ), bgn_time )
				> ANIM_XEX_EARTHQUAKE_MAX_SEC ){
			break;
		}
	}

	call_game_sound_stop();

	/* 画面の位置を元に戻す */

	draw->x = pre_draw.x;
	draw->y = pre_draw.y;
	call_pcg_dun_scroll( draw->x, draw->y );

	/* ボスを削除 */

	die_all_last_boss();

	/* ラスボスを描画 */

	xx_pos.x = room_pos.x + (AREA_MAX_X / 2);
	xx_pos.y = room_pos.y;
	set_last_boss_ptn();

	/* ラスボスを生成 */

	core_joint = get_joint( &last_boss_parts_skull,
			JOINT_CHR_ATTACK_SKULL );
	if( core_joint == NULL ){
		g_core.x = xx_pos.x + XX_CORE_OFFSET_X;
		g_core.y = xx_pos.y + XX_CORE_OFFSET_Y;
	} else {
		g_core.x = pos_skull.x + core_joint->x;
		g_core.y = pos_skull.y + core_joint->y;
	}
	dun = get_dun();
	make_mnstr( g_core.x, g_core.y, TRUE, dun->lev, MNSTR_KIND_XX );

	/* マップを描画 */

	redraw_map_force();
}

/***************************************************************
* XX の登場のデモを端折る
***************************************************************/

void	set_xx_enter( void )
{
	pos_t	room_pos;
	last_boss_joint_t	*core_joint;
	dun_t	*dun;
	long	i;

	if( get_last_boss( LAST_BOSS_KIND_XX ) != NULL )
		return;

	/* 残りの床が崩れる */

	draw_xex_breakdown_all_field();

	/* 溶岩の出現 */

	for( i = 0; i < MAP_MAX_Y; i++ )
		draw_xex_lava( i );

	/* 画面の位置を元に戻す */

	scroll_last_boss();

	/* ボスを削除 */

	die_all_last_boss();

	/* ラスボスを描画 */

	room_pos = get_map_event_pos( MAP_EVENT_LAST_BOSS_SCROLL_MAP );
	if( clip_pos( room_pos.x, room_pos.y ) ){
		xx_pos.x = room_pos.x + (AREA_MAX_X / 2);
		xx_pos.y = room_pos.y;
	} else {
		xx_pos.x = AREA_MAX_X * 2;
		xx_pos.y = AREA_MAX_Y * 1;
	}
	set_last_boss_ptn();

	/* ラスボスを生成 */

	core_joint = get_joint( &last_boss_parts_skull,
			JOINT_CHR_ATTACK_SKULL );
	if( core_joint == NULL ){
		g_core.x = xx_pos.x + XX_CORE_OFFSET_X;
		g_core.y = xx_pos.y + XX_CORE_OFFSET_Y;
	} else {
		g_core.x = pos_skull.x + core_joint->x;
		g_core.y = pos_skull.y + core_joint->y;
	}
	dun = get_dun();
	make_mnstr( g_core.x, g_core.y, TRUE, dun->lev, MNSTR_KIND_XX );

	/* マップを描画 */

	redraw_map_force();
}

/***************************************************************
* 床の崩壊
* return : 崩壊が終了したか?
***************************************************************/

bool_t	draw_xex_breakdown( void )
{
	dun_t	*dun;
	pos_t	room_pos;
	long	n;
	long	xx, yy;
	long	nx, ny;
	long	mx, my;

	dun = get_dun();

	room_pos = get_map_event_pos( MAP_EVENT_LAST_BOSS_SCROLL_MAP );
	if( !clip_pos( room_pos.x, room_pos.y ) )
		return TRUE;

	n = 0;
	mx = MAP_DEL_X;
	my = MAP_DEL_Y;

	for( yy = 0; yy < AREA_MAX_Y; yy++ ){
		for( xx = 0; xx < AREA_MAX_X; xx++ ){
			nx = room_pos.x + xx;
			ny = room_pos.y + yy;
			if( !chk_xex_breakdown_field( nx, ny ) )
				continue;

			n++;
			if( !per_randm( n ) )
				continue;

			mx = nx;
			my = ny;
		}
	}
	if( !clip_pos( mx, my ) )
		return TRUE;
	if( n <= 0 )
		return TRUE;

	dun->map.obj.mjr[my][mx] = FACE_MJR_FLOOR;
	dun->map.obj.mnr[my][mx] = FACE_MNR_HOLE;
	dun->map.obj.flg[my][mx] &= ~(FLG_MAP_OBJ_PASS);
	dun->map.obj.flg[my][mx] |= (FLG_MAP_OBJ_FIND | FLG_MAP_OBJ_LOOK);

	return FALSE;
}

/***************************************************************
* 指定座標の床が崩壊できるか調べる
* long x : X 座標
* long y : Y 座標
* return : 崩壊できるか?
***************************************************************/

bool_t	chk_xex_breakdown_field( long x, long y )
{
	pos_t	party_pos;
	dun_t	*dun;

	if( !clip_pos( x, y ) )
		return FALSE;

	party_pos = get_map_event_pos( MAP_EVENT_LAST_BOSS_BATTLE_PARTY );
	if( !clip_pos( party_pos.x, party_pos.y ) )
		return TRUE;

	dun = get_dun();
	if( dun->map.obj.mjr[y][x] == FACE_MJR_FLOOR )
		if( dun->map.obj.mnr[y][x] == FACE_MNR_HOLE )
			return FALSE;
	if( dun->map.sect[y][x] == LAST_BOSS_SAFE_SECT )
		return FALSE;
	if( labs( x - party_pos.x ) <= 2 )
		if( labs( y - party_pos.y ) <= 2 )
			return FALSE;

	return TRUE;
}

/***************************************************************
* 1 行単位の床の崩壊
* long y : Y 座標
***************************************************************/

void	draw_xex_breakdown_line( long y )
{
	dun_t	*dun;
	long	x;

	dun = get_dun();

	for( x = 0; x < MAP_MAX_X; x++ ){
		if( !clip_pos( x, y ) )
			break;

		dun->map.obj.mjr[y][x] = FACE_MJR_FLOOR;
		dun->map.obj.mnr[y][x] = FACE_MNR_HOLE;
		dun->map.obj.flg[y][x] &= ~(FLG_MAP_OBJ_PASS);
		dun->map.obj.flg[y][x] |= (FLG_MAP_OBJ_FIND
				| FLG_MAP_OBJ_LOOK);
	}
}

/***************************************************************
* 全ての床の崩壊
***************************************************************/

void	draw_xex_breakdown_all_field( void )
{
	dun_t	*dun;
	long	xx, yy;

	dun = get_dun();

	for( yy = 0; yy < MAP_MAX_Y; yy++ ){
		for( xx = 0; xx < MAP_MAX_X; xx++ ){
			if( !clip_pos( xx, yy ) )
				continue;
			if( !chk_xex_breakdown_field( xx, yy ) )
				continue;

			dun->map.obj.mjr[yy][xx] = FACE_MJR_FLOOR;
			dun->map.obj.mnr[yy][xx] = FACE_MNR_HOLE;
			dun->map.obj.flg[yy][xx] &= ~(FLG_MAP_OBJ_PASS);
			dun->map.obj.flg[yy][xx] |= (FLG_MAP_OBJ_FIND
					| FLG_MAP_OBJ_LOOK);
		}
	}
}

/***************************************************************
* 地震
* pos_t *draw : マップの表示位置データ
* pos_t base_draw : 基準座標
***************************************************************/

void	draw_xex_earthquake( pos_t *draw, pos_t base_draw )
{
	long	x, y;

	if( draw == NULL )
		return;

	x = base_draw.x + randm( 5 ) - 2;
	y = base_draw.y + randm( 5 ) - 2;
	if( x < 0 )
		x = 0;
	if( y < 0 )
		y = 0;
	if( x > MAP_MAX_X - (get_map_col() / 2) )
		x = MAP_MAX_X - (get_map_col() / 2);
	if( y > MAP_MAX_Y - get_map_row() )
		y = MAP_MAX_Y - get_map_row();

	draw->x = x;
	draw->y = y;
}

/***************************************************************
* 1 行単位で奈落を溶岩に変える
* long y : Y 座標
***************************************************************/

void	draw_xex_lava( long y )
{
	dun_t	*dun;
	long	x;

	dun = get_dun();

	for( x = 0; x < MAP_MAX_X; x++ ){
		if( !clip_pos( x, y ) )
			break;
		if( dun->map.obj.mjr[y][x] != FACE_MJR_FLOOR )
			continue;
		if( dun->map.obj.mnr[y][x] != FACE_MNR_HOLE )
			continue;

		dun->map.obj.mjr[y][x] = FACE_MJR_WATER;
		dun->map.obj.mnr[y][x] = FACE_MNR_LAVA;
		dun->map.obj.flg[y][x] &= ~(FLG_MAP_OBJ_PASS);
		dun->map.obj.flg[y][x] |= (FLG_MAP_OBJ_FIND
				| FLG_MAP_OBJ_LOOK);
	}
}

/***************************************************************
* 全てのラスボスに対して死ぬか調べる
***************************************************************/

void	chk_die_all_last_boss( void )
{
	long	i;

	for( i = 0; i < LAST_BOSS_KIND_MAX_N; i++ ){
		if( i == LAST_BOSS_KIND_XX )
			continue;

		chk_die_last_boss( (last_boss_kind_t)i );
	}
}

/***************************************************************
* ラスボスが死ぬか調べる
* last_boss_kind_t kind : ラスボスの種類
***************************************************************/

void	chk_die_last_boss( last_boss_kind_t kind )
{
	dun_t	*dun;
	mnstr_t	*p;

	dun = get_dun();

	p = get_last_boss( kind );
	if( p == NULL )
		return;

	if( chk_flg_or( p->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( !clip_pos( p->x, p->y ) )
		return;
	if( dun->map.obj.mjr[p->y][p->x] == FACE_MJR_FLOOR )
		if( dun->map.obj.mnr[p->y][p->x] != FACE_MNR_HOLE )
			return;

	die_chr( p, TRUE, FALSE, FALSE );
}

/***************************************************************
* 全てのラスボスを殺す
***************************************************************/

void	die_all_last_boss( void )
{
	mnstr_t	*p;
	long	i;

	for( i = 0; i < LAST_BOSS_KIND_MAX_N; i++ ){
		if( i == LAST_BOSS_KIND_XX )
			continue;

		p = get_last_boss( (last_boss_kind_t)i );
		if( p == NULL )
			continue;

		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD ) ){
			continue;
		}

		die_chr( p, TRUE, FALSE, FALSE );
	}
}

/***************************************************************
* 指定の座標が XX の一部か調べる
* long x : X 座標
* long y : Y 座標
* return : XX の一部か?
***************************************************************/

bool_t	chk_xx_pos( long x, long y )
{
	dun_t	*dun;

	dun = get_dun();

	if( dun->map.obj.mjr[y][x] != FACE_MJR_WATER )
		return FALSE;
	if( dun->map.obj.mnr[y][x] != FACE_MNR_LAVA )
		return FALSE;
	if( get_scene() != SCENE_N_LAST_BOSS )
		return FALSE;
	if( get_last_scene() != LAST_SCENE_N_XX_BATTLE )
		return FALSE;

	return TRUE;
}

/***************************************************************
* XX に攻撃が届くか調べる
* long x : X 座標
* long y : Y 座標
* return : 攻撃が届くか?
***************************************************************/

bool_t	chk_xx_range( void )
{
	if( get_scene() != SCENE_N_LAST_BOSS )
		return FALSE;
	if( get_last_scene() != LAST_SCENE_N_XX_BATTLE )
		return FALSE;

	return TRUE;
}

/***************************************************************
* XX のパターンをマップにセット
***************************************************************/

void	set_last_boss_ptn( void )
{
	long	len;

	/* XX のレイヤーをリセット */

	reset_last_boss_ptn( &last_boss_ptn_bg );
	reset_last_boss_ptn( &last_boss_ptn_fg );

	/* パーツの座標を計算 */

	/* 頭 */

	len = str_len_std( last_boss_parts_skull.ptn[0] );
	pos_skull.x = xx_pos.x - (len / 2 / 2);
	pos_skull.y = xx_pos.y;

	/* 顎 */

	pos_jaw.x = pos_skull.x
			+ joint_skull_to_jaw->x
			- joint_jaw_to_skull->x;
	pos_jaw.y = pos_skull.y
			+ joint_skull_to_jaw->y
			- joint_jaw_to_skull->y;

	/* 開いた顎 */

	pos_jaw_open.x = pos_skull.x
			+ joint_skull_to_jaw->x
			- joint_jaw_to_skull_open->x;
	pos_jaw_open.y = pos_skull.y
			+ joint_skull_to_jaw->y
			- joint_jaw_to_skull_open->y;

	/* 胴体 */

	pos_body.x = pos_skull.x + joint_skull->x - joint_body->x;
	pos_body.y = pos_skull.y + joint_skull->y - joint_body->y;

	/* 左上腕 */

	pos_upper_arm_left.x = pos_body.x
			+ joint_body_to_upper_arm_left->x
			- joint_upper_arm_to_body_left->x;
	pos_upper_arm_left.y = pos_body.y
			+ joint_body_to_upper_arm_left->y
			- joint_upper_arm_to_body_left->y;

	/* 右上腕 */

	pos_upper_arm_right.x = pos_body.x
			+ joint_body_to_upper_arm_right->x
			- joint_upper_arm_to_body_right->x;
	pos_upper_arm_right.y = pos_body.y
			+ joint_body_to_upper_arm_right->y
			- joint_upper_arm_to_body_right->y;

	/* 左前腕 */

	pos_fore_arm_left.x = pos_upper_arm_left.x
			+ joint_upper_arm_to_fore_arm_left->x
			- joint_fore_arm_to_upper_arm_left->x;
	pos_fore_arm_left.y = pos_upper_arm_left.y
			+ joint_upper_arm_to_fore_arm_left->y
			- joint_fore_arm_to_upper_arm_left->y;

	/* 左前腕 (平手打ち) */

	pos_fore_arm_slap_left.x = pos_upper_arm_left.x
			+ joint_upper_arm_to_fore_arm_left->x
			- joint_fore_arm_to_upper_arm_slap_left->x;
	pos_fore_arm_slap_left.y = pos_upper_arm_left.y
			+ joint_upper_arm_to_fore_arm_left->y
			- joint_fore_arm_to_upper_arm_slap_left->y;

	/* 右前腕 */

	pos_fore_arm_right.x = pos_upper_arm_right.x
			+ joint_upper_arm_to_fore_arm_right->x
			- joint_fore_arm_to_upper_arm_right->x;
	pos_fore_arm_right.y = pos_upper_arm_right.y
			+ joint_upper_arm_to_fore_arm_right->y
			- joint_fore_arm_to_upper_arm_right->y;

	/* 右前腕 (平手打ち) */

	pos_fore_arm_slap_right.x = pos_upper_arm_right.x
			+ joint_upper_arm_to_fore_arm_right->x
			- joint_fore_arm_to_upper_arm_slap_right->x;
	pos_fore_arm_slap_right.y = pos_upper_arm_right.y
			+ joint_upper_arm_to_fore_arm_right->y
			- joint_fore_arm_to_upper_arm_slap_right->y;

	/* 左手 */

	pos_hand_left.x = pos_fore_arm_left.x
			+ joint_fore_arm_to_hand_left->x
			- joint_hand_to_fore_arm_left->x;
	pos_hand_left.y = pos_fore_arm_left.y
			+ joint_fore_arm_to_hand_left->y
			- joint_hand_to_fore_arm_left->y;

	/* 左手 (平手打ち) */

	pos_hand_slap_left.x = pos_fore_arm_slap_left.x
			+ joint_fore_arm_to_hand_slap_left->x
			- joint_hand_to_fore_arm_slap_left->x;
	pos_hand_slap_left.y = pos_fore_arm_slap_left.y
			+ joint_fore_arm_to_hand_slap_left->y
			- joint_hand_to_fore_arm_slap_left->y;

	/* 右手 */

	pos_hand_right.x = pos_fore_arm_right.x
			+ joint_fore_arm_to_hand_right->x
			- joint_hand_to_fore_arm_right->x;
	pos_hand_right.y = pos_fore_arm_right.y
			+ joint_fore_arm_to_hand_right->y
			- joint_hand_to_fore_arm_right->y;

	/* 右手 (平手打ち) */

	pos_hand_slap_right.x = pos_fore_arm_slap_right.x
			+ joint_fore_arm_to_hand_slap_right->x
			- joint_hand_to_fore_arm_slap_right->x;
	pos_hand_slap_right.y = pos_fore_arm_slap_right.y
			+ joint_fore_arm_to_hand_slap_right->y
			- joint_hand_to_fore_arm_slap_right->y;

	/* パーツをセット */

	/* 胴体 */
	set_last_boss_parts(
			get_last_boss_ptn_bg(),
			&last_boss_parts_body,
			pos_body.x, pos_body.y );

	/* 顎 */

	if( flg_open_xx_jaw ){
		set_last_boss_parts(
				get_last_boss_ptn_bg(),
				&last_boss_parts_jaw,
				pos_jaw_open.x, pos_jaw_open.y );
	} else {
		set_last_boss_parts(
				get_last_boss_ptn_bg(),
				&last_boss_parts_jaw,
				pos_jaw.x, pos_jaw.y );
	}

	/* 頭 */
	set_last_boss_parts(
			get_last_boss_ptn_bg(),
			&last_boss_parts_skull,
			pos_skull.x, pos_skull.y );

	/* 左上腕 */
	set_last_boss_parts(
			get_last_boss_ptn_bg(),
			&last_boss_parts_upper_arm_left,
			pos_upper_arm_left.x, pos_upper_arm_left.y );

	/* 右上腕 */
	set_last_boss_parts(
			get_last_boss_ptn_bg(),
			&last_boss_parts_upper_arm_right,
			pos_upper_arm_right.x, pos_upper_arm_right.y );

	/* 左前腕 */
	if( flg_slap_xx_arm_left ){
		set_last_boss_parts(
				get_last_boss_ptn_fg(),
				&last_boss_parts_fore_arm_slap_left,
				pos_fore_arm_slap_left.x,
				pos_fore_arm_slap_left.y );
	} else {
		set_last_boss_parts(
				get_last_boss_ptn_fg(),
				&last_boss_parts_fore_arm_left,
				pos_fore_arm_left.x,
				pos_fore_arm_left.y );
	}

	/* 右前腕 */
	if( flg_slap_xx_arm_right ){
		set_last_boss_parts(
				get_last_boss_ptn_fg(),
				&last_boss_parts_fore_arm_slap_right,
				pos_fore_arm_slap_right.x,
				pos_fore_arm_slap_right.y );
	} else {
		set_last_boss_parts(
				get_last_boss_ptn_fg(),
				&last_boss_parts_fore_arm_right,
				pos_fore_arm_right.x,
				pos_fore_arm_right.y );
	}

	/* 左手 */
	if( flg_slap_xx_arm_left ){
		set_last_boss_parts(
				get_last_boss_ptn_fg(),
				&last_boss_parts_hand_slap_left,
				pos_hand_slap_left.x,
				pos_hand_slap_left.y );
	} else {
		set_last_boss_parts(
				get_last_boss_ptn_fg(),
				&last_boss_parts_hand_left,
				pos_hand_left.x,
				pos_hand_left.y );
	}

	/* 右手 */
	if( flg_slap_xx_arm_right ){
		set_last_boss_parts(
				get_last_boss_ptn_fg(),
				&last_boss_parts_hand_slap_right,
				pos_hand_slap_right.x,
				pos_hand_slap_right.y );
	} else {
		set_last_boss_parts(
				get_last_boss_ptn_fg(),
				&last_boss_parts_hand_right,
				pos_hand_right.x,
				pos_hand_right.y );
	}
}

/***************************************************************
* XX のアゴが開いているかを返す
* bool_t flg_open_jaw : 開いているか?
***************************************************************/

bool_t	get_open_xx_jaw( void )
{
	return flg_open_xx_jaw;
}

/***************************************************************
* XX のアゴを開閉
* bool_t flg_open_jaw : アゴを開くか?
***************************************************************/

void	set_open_xx_jaw( bool_t flg_open_jaw )
{
	flg_open_xx_jaw = flg_open_jaw;

	set_last_boss_ptn();
	if( g_flg_cui )
		redraw_map_force();
}

/***************************************************************
* XX の左腕が平手打ち中かを返す
* return : 平手打ち中か?
***************************************************************/

bool_t	get_slap_xx_arm_left( void )
{
	return flg_slap_xx_arm_left;
}

/***************************************************************
* XX の右腕が平手打ち中かを返す
* return : 平手打ち中か?
***************************************************************/

bool_t	get_slap_xx_arm_right( void )
{
	return flg_slap_xx_arm_right;
}

/***************************************************************
* XX の左腕の平手打ちを設定
* bool_t flg_slap_arm : 平手打ちをするか?
***************************************************************/

void	set_slap_xx_arm_left( bool_t flg_slap_arm )
{
	flg_slap_xx_arm_left = flg_slap_arm;

	set_last_boss_ptn();
	redraw_map_force();
}

/***************************************************************
* XX の右腕の平手打ちを設定
* bool_t flg_slap_arm : 平手打ちをするか?
***************************************************************/

void	set_slap_xx_arm_right( bool_t flg_slap_arm )
{
	flg_slap_xx_arm_right = flg_slap_arm;

	set_last_boss_ptn();
	redraw_map_force();
}

/***************************************************************
* パーツの関節を返す
* last_boss_parts_t *parts : パーツ
* char mnr : 関節の顔文字
* return : パーツの関節
***************************************************************/

last_boss_joint_t	*get_joint( last_boss_parts_t *parts, char mnr )
{
	long	j;

	if( parts == NULL )
		return NULL;

	for( j = 0; j < JOINT_MAX_N; j++ ){
		if( mnr == parts->joint[j].joint_mnr )
			return &(parts->joint[j]);
	}

	return NULL;
}

/***************************************************************
* XX の頭の攻撃ポイントの座標を返す
* pos_t *p : 座標を返す
***************************************************************/

void	get_attack_skull_pos( pos_t *p )
{
	last_boss_joint_t	*joint;

	if( p == NULL )
		return;

	joint = get_joint( &last_boss_parts_skull,
			JOINT_CHR_ATTACK_SKULL );
	if( joint == NULL ){
		p->x = xx_pos.x;
		p->y = xx_pos.y;
	} else {
		p->x = pos_skull.x + joint->x;
		p->y = pos_skull.y + joint->y;
	}
}

/***************************************************************
* XX のアゴの攻撃ポイントの座標を返す
* pos_t *p : 座標を返す
***************************************************************/

void	get_attack_jaw_pos( pos_t *p )
{
	last_boss_joint_t	*joint;

	if( p == NULL )
		return;

	joint = get_joint( &last_boss_parts_jaw,
			JOINT_CHR_ATTACK_JAW );
	if( joint == NULL ){
		p->x = xx_pos.x;
		p->y = xx_pos.y;
	} else {
		p->x = pos_jaw.x + joint->x;
		p->y = pos_jaw.y + joint->y;
	}
}

/***************************************************************
* XX のパターンのパーツをマップにセット
* const last_boss_parts_t *parts : XX のパターンのパーツ
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	set_last_boss_parts(
	last_boss_ptn_t *ptn,
	last_boss_parts_t *parts,
	long x, long y
)
{
	long	xx, yy;
	long	ptn_x, ptn_y;
	char	mjr, mnr, transmit_chr;
	curs_attr_n_t	attr_n;
	curs_attr_t	*attr_dflt;

	if( ptn == NULL )
		return;
	if( parts == NULL )
		return;

	attr_n = CURS_ATTR_N_MAP_NORMAL;
	attr_dflt = get_curs_attr();

	transmit_chr = ptn->transmit_chr;

	ptn_y = y;
	for( yy = 0; yy < MAP_MAX_Y; yy++, ptn_y++ ){
		if( !clip_y( ptn_y ) )
			continue;
		if( parts->ptn[yy] == NULL )
			break;

		ptn_x = x;
		for( xx = 0; xx < MAP_MAX_X; xx++, ptn_x++ ){
			if( !clip_x( ptn_x ) )
				continue;

			mjr = parts->ptn[yy][xx * 2 + 0];
			if( mjr == '\0' )
				break;
			mnr = parts->ptn[yy][xx * 2 + 1];
			if( mnr == '\0' )
				mnr = transmit_chr;

			do {
				last_boss_joint_t	*joint;

				if( mjr != g_joint_chr )
					break;
				joint = get_joint( parts, mnr );
				if( joint == NULL )
					break;

				mjr = joint->mjr;
				mnr = joint->mnr;
				break;
			} while( 0 );

			if( mjr != transmit_chr )
				ptn->mjr[ptn_y][ptn_x] = mjr;
			if( mnr != transmit_chr )
				ptn->mnr[ptn_y][ptn_x] = mnr;
			if( (mjr != transmit_chr)
					|| (mnr != transmit_chr) ){
				ptn->attr[ptn_y][ptn_x]
						= attr_dflt[attr_n];
			}

			mnr = parts->ptn[yy][xx * 2 + 1];
			if( mnr == '\0' )
				break;
		}
	}
}

/***************************************************************
* XX のパターンをリセット
* last_boss_ptn *ptn : XX のパターン
***************************************************************/

void	reset_last_boss_ptn( last_boss_ptn_t *ptn )
{
	long	x, y;
	curs_attr_n_t	attr_n;
	curs_attr_t	*attr_dflt;

	if( get_scene() != SCENE_N_LAST_BOSS )
		return;
	if( ptn == NULL )
		return;

	ptn->transmit_chr = g_transmit_chr;
	attr_n = CURS_ATTR_N_MAP_NORMAL;
	attr_dflt = get_curs_attr();

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			ptn->mjr[y][x] = ptn->transmit_chr;
			ptn->mnr[y][x] = ptn->transmit_chr;
			ptn->flg[y][x] = FLG_NULL;
			ptn->attr[y][x] = attr_dflt[attr_n];
		}
	}
}

/***************************************************************
* ラスボスの背景で綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_last_boss_bg( long x, long y, long dx, long dy )
{
	set_map_total_last_boss( get_last_boss_ptn_bg(), x, y, dx, dy );
}

/***************************************************************
* ラスボスの前景で綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_last_boss_fg( long x, long y, long dx, long dy )
{
	set_map_total_last_boss( get_last_boss_ptn_fg(), x, y, dx, dy );
}

/***************************************************************
* ラスボスで綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_last_boss(
	last_boss_ptn_t *ptn,
	long x, long y, long dx, long dy
)
{
	dun_t	*dun;
	long	bx, by;
	long	ex, ey;
	long	xx, yy;
	char	mjr, mnr;
	flg_map_t	flg;
	curs_attr_t	attr;

	if( get_scene() != SCENE_N_LAST_BOSS )
		return;
	if( ptn == NULL )
		return;

	dun = get_dun();

	bx = x;
	by = y;
	ex = x + dx - 1;
	ey = y + dy - 1;
	if( bx < 0 )
		bx = 0;
	if( by < 0 )
		by = 0;
	if( ex > MAP_MAX_X - 1 )
		ex = MAP_MAX_X - 1;
	if( ey > MAP_MAX_Y - 1 )
		ey = MAP_MAX_Y - 1;

	for( yy = by; yy <= ey; yy++ ){
		for( xx = bx; xx <= ex; xx++ ){
			mjr = ptn->mjr[yy][xx];
			mnr = ptn->mnr[yy][xx];
			flg = ptn->flg[yy][xx];
			attr = ptn->attr[yy][xx];

			if( mjr != ptn->transmit_chr )
				dun->map.total.mjr[yy][xx] = mjr;
			if( mnr != ptn->transmit_chr )
				dun->map.total.mnr[yy][xx] = mnr;
			if( (mjr != ptn->transmit_chr)
					|| (mnr != ptn->transmit_chr) ){
				dun->map.total.flg[yy][xx] = flg;
				dun->map.attr[yy][xx] = attr;
			}
		}
	}
}

/***************************************************************
* XX の背景のパターンを返す
* return : XX のパターン
***************************************************************/

last_boss_ptn_t	*get_last_boss_ptn_bg( void )
{
	return &last_boss_ptn_bg;
}

/***************************************************************
* XX の前景のパターンを返す
* return : XX のパターン
***************************************************************/

last_boss_ptn_t	*get_last_boss_ptn_fg( void )
{
	return &last_boss_ptn_fg;
}

/***************************************************************
* XX の位置を返す
* return : XX のパターン
***************************************************************/

pos_t	get_xx_pos( void )
{
	return xx_pos;
}

/***************************************************************
* GUI の描画待ち
* long frame : 待ちフレーム数
***************************************************************/

void	wait_frame_gui( long frame )
{
	if( g_flg_gui )
		wait_frame( frame );
}

/***************************************************************
* XX のアクション
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	act_mnstr_xx( mnstr_t *p )
{
	xx_act_kind_t	kind;
	party_t	*pty;
	long	m;

	clr_map_chr( p );
	p->x = g_core.x;
	p->y = g_core.y;
	set_map_chr( p );

	pty = get_party();
	kind = (xx_act_kind_t)(randm( XX_ACT_KIND_MAX_N - 1 ) + 1);

	g_frame_skip = FRAME_SKIP_MAX
			* (_100_PERCENT - get_vfx_wait())
			/ _100_PERCENT
			+ 1;
	if( g_frame_skip < 1 )
		g_frame_skip = 1;
	if( g_frame_skip > FRAME_SKIP_MAX )
		g_frame_skip = FRAME_SKIP_MAX;

#if	0
	if( g_flg_debug )
		kind = XX_ACT_KIND_COLD;
#endif

	switch( kind ){
	case XX_ACT_KIND_NULL:
	case XX_ACT_KIND_MAX_N:
		break;
	case XX_ACT_KIND_HEAT:
		print_msg( FLG_NULL, MSG_FMT_SPELL_XX_HEAT, p->name );
		xx_act_heat( p );
		xx_spell( p, SPELL_KIND_FIRE_BALL );
		break;
	case XX_ACT_KIND_COLD:
		print_msg( FLG_NULL, MSG_FMT_SPELL_XX_COLD, p->name );
		xx_act_cold( p );
		xx_spell( p, SPELL_KIND_ICE_BLIZZARD );
		break;
	case XX_ACT_KIND_MIND:
		print_msg( FLG_NULL, MSG_FMT_SPELL_XX_MIND, p->name );
		xx_act_mind( p );
		xx_spell( p, SPELL_KIND_MIND_STORM );
		break;
	case XX_ACT_KIND_ACID:
		print_msg( FLG_NULL, MSG_FMT_SPELL_XX_ACID, p->name );
		xx_act_acid( p );
		xx_spell( p, SPELL_KIND_ACID_RAIN );
		break;
	case XX_ACT_KIND_PARALYZE:
		print_msg( FLG_NULL, MSG_FMT_SPELL_XX_PARALYZE, p->name );
		xx_act_rotation( p );
		xx_spell( p, SPELL_KIND_PARALYZE );
		break;
	case XX_ACT_KIND_POISON:
		print_msg( FLG_NULL, MSG_FMT_SPELL_XX_POISON, p->name );
		xx_act_whirl( p );
		xx_spell( p, SPELL_KIND_POISON );
		break;
	case XX_ACT_KIND_SLEEP:
		print_msg( FLG_NULL, MSG_FMT_SPELL_XX_SLEEP, p->name );
		xx_act_fan( p );
		xx_spell( p, SPELL_KIND_SLEEP );
		break;
	case XX_ACT_KIND_SLAP:
		xx_act_slap( p );
		for( m = 0; m < MBR_MAX_N; m++ )
			fight_bash( p, pty->mbr[m], xx_attack_slap );
		break;
	}

	call_pcg_dun_set_xx_attack( XX_ACT_KIND_NULL, NULL );
	redraw_map();
}

/***************************************************************
* XX のアクションの効果音
* xx_act_kind_t kind : アクションの種類
***************************************************************/

void	play_sound_xx( xx_act_kind_t kind )
{
	sound_kind_t	sk;

	sk = SOUND_KIND_NULL;

	switch( kind ){
	case XX_ACT_KIND_NULL:
	case XX_ACT_KIND_MAX_N:
		break;
	case XX_ACT_KIND_HEAT:
	case XX_ACT_KIND_COLD:
	case XX_ACT_KIND_MIND:
	case XX_ACT_KIND_ACID:
		sk = SOUND_KIND_FIGHT_ATTACK_LAST_BOSS_ATTACK;
		break;
	case XX_ACT_KIND_PARALYZE:
	case XX_ACT_KIND_POISON:
	case XX_ACT_KIND_SLEEP:
		sk = SOUND_KIND_FIGHT_ATTACK_LAST_BOSS_WEAKEN;
		break;
	case XX_ACT_KIND_SLAP:
		sk = SOUND_KIND_FIGHT_ATTACK_LAST_BOSS_SLAP;
		break;
	}

	call_game_sound_play( sk, 1 );
}

/***************************************************************
* XX の呪文攻撃
* mnstr_t *p : XX のキャラクタ・データ
* spell_kind_t kind : 呪文の種類
***************************************************************/

void	xx_spell( mnstr_t *p, spell_kind_t kind )
{
	party_t	*pty;
	fx_t	*fx;
	long	i;

	pty = get_party();
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		chr_cast_spell_sub( p, FALSE,
				get_spell_tab( kind ),
				_100_PERCENT,
				pty->mbr[i]->x, pty->mbr[i]->y,
				TRGT_KIND_MBR, pty->mbr[i] );

		/* 効果時間を 1 ターンにする */

		if( kind == SPELL_KIND_PARALYZE ){
			fx = srch_fx( &(pty->mbr[i]->fx),
					FX_KIND_PARALYZE );
			if( fx != NULL )
				fx->turn = 1 + 1;
		}
		if( kind == SPELL_KIND_SLEEP ){
			fx = srch_fx( &(pty->mbr[i]->fx),
					FX_KIND_SLEEP );
			if( fx != NULL )
				fx->turn = 1 + 1;
		}
	}
}

/***************************************************************
* XX の火熱攻撃
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_heat( mnstr_t *p )
{
	long	i;

	set_open_xx_jaw( TRUE );

	for( i = 0; i < XX_HEAT_ANIME_N; i++ ){
		play_sound_xx( XX_ACT_KIND_HEAT );
		xx_act_heat_draw( p );
	}

	redraw_map();

	set_open_xx_jaw( FALSE );
}

/***************************************************************
* XX の火熱攻撃の描画
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_heat_draw( mnstr_t *p )
{
	long	blast_max_n;
	pos_t	bgn;
	long	end_y;
	xx_heat_t	xx_heat;
	long	n, m;
	long	i;

	blast_max_n = sizeof( xx_blast_heat ) / sizeof( xx_blast_heat[0] );
	for( i = 0; i < blast_max_n; i++ )
		set_blast_size( &(xx_blast_heat[i]) );

	get_attack_jaw_pos( &bgn );
	xx_heat.head_x = bgn.x;
	xx_heat.head_y = bgn.y;

	for( n = 0; n < XX_HEAT_MAX_N; n++ ){
		xx_heat.blast_n[n] = -1;
		xx_heat.blast_m[n] = 0;
	}

	end_y = bgn.y + AREA_MAX_Y + (blast_max_n * XX_HEAT_BLAST_ANIME_N);

	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( xx_heat.head_y > end_y )
			break;

		if( g_flg_text_mode || (g_flg_cui && !g_flg_gui) )
			if( (i % g_frame_skip) == 0 )
				redraw_map();

		if( (xx_heat.head_y % XX_HEAT_DY) == 0 ){
			n = (xx_heat.head_y / XX_HEAT_DY) % XX_HEAT_MAX_N;
			xx_heat.blast_n[n] = 0;
			xx_heat.blast_x[n] = xx_heat.head_x;
			xx_heat.blast_y[n] = xx_heat.head_y;
		}

		for( n = 0; n < XX_HEAT_MAX_N; n++ ){
			if( xx_heat.blast_n[n] <= -1 )
				continue;

			xx_heat.blast_m[n] = xx_heat.blast_n[n]
					/ XX_HEAT_BLAST_ANIME_N;
			m = xx_heat.blast_m[n];
			if( m >= blast_max_n )
				continue;

			if( (i % g_frame_skip) == 0 ){
				draw_blast_cui( CHR_KIND_MBR,
						xx_heat.blast_x[n],
						xx_heat.blast_y[n],
						&(xx_blast_heat[m]),
						NULL,
						"XX" );
			}

			xx_heat.blast_n[n]++;
		}

		if( (i % g_frame_skip) == 0 ){
			call_pcg_dun_set_xx_attack(
					XX_ACT_KIND_HEAT, &xx_heat );
			call_pcg_dun_draw_turn( TRUE );

			wait_clock( XX_HEAT_WAIT_FRAME_N );
		}

		xx_heat.head_y++;
	}
}

/***************************************************************
* XX の水冷攻撃
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_cold( mnstr_t *p )
{
	play_sound_xx( XX_ACT_KIND_COLD );
	xx_act_cold_draw( p );

	redraw_map();
}

/***************************************************************
* XX の水冷攻撃の描画
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_cold_draw( mnstr_t *p )
{
	xx_cold_t	xx_cold;
	pos_t	bgn;
	pos_t	*draw;
	party_t	*pty;
	long	n;
	long	i, j;

	/* 初期化 */

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	pty = get_party();

	xx_cold.laser_len = 0;
	for( n = 0; n < MBR_MAX_N; n++ )
		set_blast_size( &(xx_bit[n]) );

	/* 移動先 */

	n = 0;
	xx_cold.bit_mx[n] = pty->mbr[n]->x;
	xx_cold.bit_my[n] = pty->mbr[n]->y - XX_COLD_LASER_MAX_LEN;
	n++;
	xx_cold.bit_mx[n] = pty->mbr[n]->x;
	xx_cold.bit_my[n] = pty->mbr[n]->y - XX_COLD_LASER_MAX_LEN;
	n++;
	xx_cold.bit_mx[n] = pty->mbr[n]->x - XX_COLD_LASER_MAX_LEN / 2;
	xx_cold.bit_my[n] = pty->mbr[n]->y - XX_COLD_LASER_MAX_LEN;
	n++;
	xx_cold.bit_mx[n] = pty->mbr[n]->x + XX_COLD_LASER_MAX_LEN / 2;
	xx_cold.bit_my[n] = pty->mbr[n]->y - XX_COLD_LASER_MAX_LEN;
	n++;
	xx_cold.bit_mx[n] = pty->mbr[n]->x - XX_COLD_LASER_MAX_LEN / 2;
	xx_cold.bit_my[n] = pty->mbr[n]->y;
	n++;
	xx_cold.bit_mx[n] = pty->mbr[n]->x + XX_COLD_LASER_MAX_LEN / 2;
	xx_cold.bit_my[n] = pty->mbr[n]->y;
	n++;

	/* 現在位置 */

	get_attack_skull_pos( &bgn );
	for( n = 0; n < MBR_MAX_N; n++ ){
		xx_cold.bit_x[n] = bgn.x;
		xx_cold.bit_y[n] = bgn.y;
	}

	/* ビットの移動の描画 */

	for( i = 0; i < LOOP_MAX_100; i++ ){
		bool_t	flg_next;

		if( g_flg_text_mode || (g_flg_cui && !g_flg_gui) )
			redraw_map();

		flg_next = TRUE;
		for( n = 0; n < MBR_MAX_N; n++ ){
			long	d;

			if( !clip_pos( xx_cold.bit_mx[n],
					xx_cold.bit_my[n] ) ){
				continue;
			}

			d = sgn_l( xx_cold.bit_mx[n] - xx_cold.bit_x[n] );
			xx_cold.bit_x[n] += d;

			d = sgn_l( xx_cold.bit_my[n] - xx_cold.bit_y[n] );
			xx_cold.bit_y[n] += d;

			if( xx_cold.bit_x[n] != xx_cold.bit_mx[n] )
				flg_next = FALSE;
			if( xx_cold.bit_y[n] != xx_cold.bit_my[n] )
				flg_next = FALSE;

			draw_blast_cui( CHR_KIND_NULL,
					xx_cold.bit_x[n],
					xx_cold.bit_y[n],
					&(xx_bit[n]),
					NULL,
					NULL );
		}

		if( (i % g_frame_skip) == 0 ){
			call_pcg_dun_set_xx_attack(
					XX_ACT_KIND_COLD, &xx_cold );
			call_pcg_dun_draw_turn( TRUE );

			wait_clock( XX_COLD_BIT_WAIT_FRAME_N );
		}

		if( flg_next )
			break;
	}

	wait_clock( XX_COLD_NEXT_WAIT_FRAME_N );

	/* レーザー発射の描画 */

	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( g_flg_text_mode || (g_flg_cui && !g_flg_gui) )
			if( (i % g_frame_skip) == 0 )
				redraw_map();

		for( n = 0; n < MBR_MAX_N; n++ ){
			if( !clip_pos( xx_cold.bit_mx[n],
					xx_cold.bit_my[n] ) ){
				continue;
			}

			curs_attrset_n( CURS_ATTR_N_COLD );
			for( j = 0; j < xx_cold.laser_len; j++ ){
				long	x, y;

				x = xx_cold.bit_x[n] - draw->x;
				y = xx_cold.bit_y[n] - draw->y;
				x = x * 2 + 1;
				x += (xx_laser_dxy[n].x * j);
				y += (xx_laser_dxy[n].y * j);

				if( g_flg_text_mode )
					curs_attrset_n( CURS_ATTR_N_COLD );

				if( g_flg_gui && g_flg_text_mode ){
					print_vfx( FALSE, x, y, MSG_S,
							xx_laser[n] );
				} else {
					print_vfx_cui( FALSE, x, y, MSG_S,
							xx_laser[n] );
				}
			}
			curs_attrset_dflt();

			if( (i % g_frame_skip) == 0 ){
				draw_blast_cui( CHR_KIND_NULL,
						xx_cold.bit_x[n],
						xx_cold.bit_y[n],
						&(xx_bit[n]),
						NULL,
						NULL );
			}
		}

		if( (i % g_frame_skip) == 0 ){
			call_pcg_dun_set_xx_attack(
					XX_ACT_KIND_COLD, &xx_cold );
			call_pcg_dun_draw_turn( TRUE );

			wait_clock( XX_COLD_LASER_WAIT_FRAME_N );
		}

		xx_cold.laser_len += XX_COLD_LASER_ADD_LEN;
		if( xx_cold.laser_len > XX_COLD_LASER_MAX_LEN )
			break;
	}

	wait_clock( XX_COLD_END_WAIT_FRAME_N );
}

/***************************************************************
* XX の水冷攻撃のレーザーの移動方向を返す
* return : 移動方向
***************************************************************/

pos_t	*get_xx_laser_dxy( void )
{
	return xx_laser_dxy;
}

/***************************************************************
* XX の風心攻撃
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_mind( mnstr_t *p )
{
	play_sound_xx( XX_ACT_KIND_MIND );
	xx_act_mind_draw( p );

	redraw_map();
}

/***************************************************************
* XX の風心攻撃の描画
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_mind_draw( mnstr_t *p )
{
	xx_mind_t	xx_mind;
	pos_t	bgn;
	long	m, n, i;

	/* 初期化 */

	xx_mind.rate = 0;
	xx_mind.anime_n = 0;
	xx_mind.refract_idx = 0;

	get_attack_skull_pos( &bgn );

	for( m = 0; m < MBR_MAX_N; m++ ){
		for( n = 0; n < XX_MIND_IMAGE_MAX_N; n++ ){
			xx_mind.refract_x[m][n] = bgn.x;
			xx_mind.refract_y[m][n] = bgn.y;
		}
		xx_mind.refract_bgn_x[m] = bgn.x;
		xx_mind.refract_bgn_y[m] = bgn.y;
		xx_mind.refract_end_x[m] = bgn.x;
		xx_mind.refract_end_y[m] = bgn.y;
	}

	xx_mind_refract( &xx_mind );

	/* 描画 */

	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( g_flg_text_mode || (g_flg_cui && !g_flg_gui) )
			if( (i % g_frame_skip) == 0 )
				redraw_map();

		/* 移動先決定 */

		if( xx_mind.rate >= _100_PERCENT ){
			xx_mind.anime_n++;
			if( xx_mind.anime_n > XX_MIND_ANIME_N )
				break;

			xx_mind_refract( &xx_mind );
		}

		xx_mind_move( &xx_mind );
		if( (i % g_frame_skip) == 0 )
			xx_mind_draw( &xx_mind );

		if( (i % g_frame_skip) == 0 ){
			call_pcg_dun_set_xx_attack(
					XX_ACT_KIND_MIND, &xx_mind );
			call_pcg_dun_draw_turn( TRUE );

			wait_clock( XX_MIND_WAIT_FRAME_N );
		}

		xx_mind.rate += XX_MIND_ADD_RATE;
		xx_mind.refract_idx++;
		xx_mind.refract_idx %= XX_MIND_IMAGE_MAX_N;
	}
}

/***************************************************************
* XX の風心攻撃の屈折
* xx_mind_t *xx_mind : 風心攻撃のデータ
***************************************************************/

static void xx_mind_refract( xx_mind_t *xx_mind )
{
	pos_t	room_pos;
	party_t	*pty;
	long	x, y;
	long	m;

	room_pos = get_map_event_pos( MAP_EVENT_LAST_BOSS_SCROLL_MAP );
	if( !clip_pos( room_pos.x, room_pos.y ) )
		return;

	pty = get_party();

	xx_mind->rate = (rate_t)0;

	for( m = 0; m < MBR_MAX_N; m++ ){
		xx_mind->refract_bgn_x[m] = xx_mind->refract_end_x[m];
		xx_mind->refract_bgn_y[m] = xx_mind->refract_end_y[m];

		if( xx_mind->anime_n >= (XX_MIND_ANIME_N - 1) ){
			x = pty->mbr[m]->x;
			y = pty->mbr[m]->y;
		} else {
			x = room_pos.x + randm( AREA_MAX_X );
			y = room_pos.y + randm( AREA_MAX_Y );
		}
		xx_mind->refract_end_x[m] = x;
		xx_mind->refract_end_y[m] = y;
	}
}

/***************************************************************
* XX の風心攻撃の移動
* xx_mind_t *xx_mind : 風心攻撃のデータ
***************************************************************/

static void xx_mind_move( xx_mind_t *xx_mind )
{
	long	x, y;
	long	m, n;

	for( m = 0; m < MBR_MAX_N; m++ ){
		x = xx_mind->refract_end_x[m];
		x -= xx_mind->refract_bgn_x[m];
		x = x * xx_mind->rate / _100_PERCENT;
		x += xx_mind->refract_bgn_x[m];

		y = xx_mind->refract_end_y[m];
		y -= xx_mind->refract_bgn_y[m];
		y = y * xx_mind->rate / _100_PERCENT;
		y += xx_mind->refract_bgn_y[m];

		n = xx_mind->refract_idx;
		xx_mind->refract_x[m][n] = x;
		xx_mind->refract_y[m][n] = y;
	}
}

/***************************************************************
* XX の風心攻撃の描画
* xx_mind_t *xx_mind : 風心攻撃のデータ
***************************************************************/

static void xx_mind_draw( xx_mind_t *xx_mind )
{
	pos_t	*draw;
	long	idx;
	long	x, y;
	const char	*str;
	long	m, n;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	curs_attrset_n( CURS_ATTR_N_MIND );
	for( m = 0; m < MBR_MAX_N; m++ ){
		for( n = XX_MIND_IMAGE_MAX_N - 1; n >= 0; n-- ){
			idx = (xx_mind->refract_idx + n)
					% XX_MIND_IMAGE_MAX_N;

			x = xx_mind->refract_x[m][idx] - draw->x;
			y = xx_mind->refract_y[m][idx] - draw->y;
			x *= 2;

			if( n == 0 )
				str = xx_refract_head;
			else
				str = xx_refract_image;

			if( g_flg_text_mode )
				curs_attrset_n( CURS_ATTR_N_MIND );

			if( g_flg_gui && g_flg_text_mode )
				print_vfx( FALSE, x, y, MSG_S, str );
			else
				print_vfx_cui( FALSE, x, y, MSG_S, str );
		}
	}
	curs_attrset_dflt();
}

/***************************************************************
* XX の土酸攻撃
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_acid( mnstr_t *p )
{
	long	i;

	set_open_xx_jaw( TRUE );

	for( i = 0; i < XX_ACID_ANIME_N; i++ ){
		play_sound_xx( XX_ACT_KIND_ACID );
		xx_act_acid_draw( p );
	}

	redraw_map();

	set_open_xx_jaw( FALSE );
}

/***************************************************************
* XX の土酸攻撃の描画
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_acid_draw( mnstr_t *p )
{
	xx_acid_t	xx_acid;
	party_t	*pty;
	pos_t	bgn;
	long	mx, my;
	long	fix;
	long	m, n, i;

	/* 初期化 */

	fix = XX_ACID_HOMING_FIX_POINT;

	xx_acid.homing_idx = 0;

	get_attack_jaw_pos( &bgn );
	bgn.y += 1;
	bgn.x *= fix;
	bgn.y *= fix;

	mx = 0;
	my = 0;
	pty = get_party();
	for( m = 0; m < MBR_MAX_N; m++ ){
		if( clip_pos( pty->mbr[m]->x, pty->mbr[m]->y ) ){
			mx = pty->mbr[m]->x * fix;
			my = pty->mbr[m]->y * fix;
			break;
		}
	}

	for( m = 0; m < MBR_MAX_N; m++ ){
		for( n = 0; n < XX_ACID_IMAGE_MAX_N; n++ ){
			xx_acid.homing_x[m][n] = bgn.x;
			xx_acid.homing_y[m][n] = bgn.y;
		}

		if( clip_pos( pty->mbr[m]->x, pty->mbr[m]->y ) ){
			xx_acid.homing_mx[m] = pty->mbr[m]->x;
			xx_acid.homing_my[m] = pty->mbr[m]->y;
			xx_acid.homing_mx[m] *= fix;
			xx_acid.homing_my[m] *= fix;
		} else {
			xx_acid.homing_mx[m] = mx;
			xx_acid.homing_my[m] = my;
		}
	}

	for( m = 0; m < MBR_MAX_N; m++ ){
		xx_acid.homing_vx[m] = xx_homing_bgn_v[m].x;
		xx_acid.homing_vy[m] = xx_homing_bgn_v[m].y;
	}

	/* 描画 */

	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( g_flg_text_mode || (g_flg_cui && !g_flg_gui) )
			if( (i % g_frame_skip) == 0 )
				redraw_map();

		if( xx_acid_chk_end( &xx_acid ) )
			break;

		xx_acid_move( &xx_acid );
		if( (i % g_frame_skip) == 0 )
			xx_acid_draw( &xx_acid );

		if( (i % g_frame_skip) == 0 ){
			call_pcg_dun_set_xx_attack(
					XX_ACT_KIND_ACID, &xx_acid );
			call_pcg_dun_draw_turn( TRUE );

			wait_clock( XX_ACID_WAIT_FRAME_N );
		}

		xx_acid.homing_idx++;
		xx_acid.homing_idx %= XX_ACID_IMAGE_MAX_N;
	}
}

/***************************************************************
* XX の土酸攻撃の移動
* xx_acid_t *xx_acid : 風心攻撃のデータ
***************************************************************/

static bool_t xx_acid_chk_end( xx_acid_t *xx_acid )
{
	long	head;
	long	dx, dy;
	long	m;
	const long adj = XX_ACID_HOMING_FIX_POINT * 110 / _100_PERCENT;

	head = xx_acid->homing_idx;

	for( m = 0; m < MBR_MAX_N; m++ ){
		dx = labs( xx_acid->homing_mx[m]
				- xx_acid->homing_x[m][head] );
		dy = labs( xx_acid->homing_my[m]
				- xx_acid->homing_y[m][head] );
		if( dx > adj )
			return FALSE;
		if( dy > adj )
			return FALSE;
	}

	return TRUE;
}

/***************************************************************
* XX の土酸攻撃の移動
* xx_acid_t *xx_acid : 風心攻撃のデータ
***************************************************************/

static void xx_acid_move( xx_acid_t *xx_acid )
{
	long	head, prev;
	long	x, y;
	long	mx, my;
	long	vx, vy;
	long	m_vx, m_vy;
	long	r_vx, r_vy;
	long	l_vx, l_vy;
	long	xx, yy;
	long	dx, dy;
	long	d_vec;
	double	q;
	long	fix;
	long	adj;
	long	m;

	fix = XX_ACID_HOMING_FIX_POINT;

	for( m = 0; m < MBR_MAX_N; m++ ){
		head = xx_acid->homing_idx;
		prev = xx_acid->homing_idx + XX_ACID_IMAGE_MAX_N - 1;
		prev %= XX_ACID_IMAGE_MAX_N;

		xx_acid->homing_x[m][head] = xx_acid->homing_x[m][prev];
		xx_acid->homing_y[m][head] = xx_acid->homing_y[m][prev];
		x = xx_acid->homing_x[m][head];
		y = xx_acid->homing_y[m][head];
		mx = xx_acid->homing_mx[m];
		my = xx_acid->homing_my[m];
		vx = xx_acid->homing_vx[m];
		vy = xx_acid->homing_vy[m];

		xx = mx - x;
		yy = my - y;
		xx = xx * xx / fix;
		yy = yy * yy / fix;
		d_vec = (long)sqrt( (double)(xx + yy) );
		if( d_vec == 0 ){
			m_vx = 0;
			m_vy = 0;
		} else {
			xx = mx - x;
			yy = my - y;
			m_vx = xx * XX_ACID_HOMING_V / fix / d_vec;
			m_vy = yy * XX_ACID_HOMING_V / fix / d_vec;
		}

		q = XX_ACID_MAX_Q * DBL_PI / 180.0;
		/* 右旋回の角度上限 */
		r_vx = cos( q ) * vx - sin( q ) * vy;
		r_vy = sin( q ) * vx + cos( q ) * vy;
		/* 左旋回の角度上限 */
		l_vx = cos( q ) * vx + sin( q ) * vy;
		l_vy = -sin( q ) * vx + cos( q ) * vy;

		if( ((vx * m_vx) + (vy * m_vy))
				> ((vx * r_vx) + (vy * r_vy)) ){
			vx = m_vx;
			vy = m_vy;
		} else {
			dx = mx - x;
			dy = my - y;
			if( ((dx * r_vx) + (dy * r_vy))
					> ((dx * l_vx) + (dy * l_vy)) ){
				/* 右旋回 */
				vx = r_vx;
				vy = r_vy;
			} else {
				/* 左旋回 */
				vx = l_vx;
				vy = l_vy;
			}
		}

		xx_acid->homing_vx[m] = vx;
		xx_acid->homing_vy[m] = vy;
		xx_acid->homing_x[m][head] += vx;
		xx_acid->homing_y[m][head] += vy;

		/* 目標に近付いたら吸いつく */

		adj = fix * 150 / _100_PERCENT;
		dx = labs( xx_acid->homing_mx[m]
				- xx_acid->homing_x[m][head] );
		dy = labs( xx_acid->homing_my[m]
				- xx_acid->homing_y[m][head] );
		if( (dx <= adj) && (dy <= adj) ){
			xx_acid->homing_x[m][head] = xx_acid->homing_mx[m];
			xx_acid->homing_y[m][head] = xx_acid->homing_my[m];
		}
	}
}

/***************************************************************
* XX の土酸攻撃の描画
* xx_acid_t *xx_acid : 風心攻撃のデータ
***************************************************************/

static void xx_acid_draw( xx_acid_t *xx_acid )
{
	pos_t	*draw;
	const char	*str;
	long	idx;
	long	fix;
	long	x, y;
	long	m, n;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	fix = XX_ACID_HOMING_FIX_POINT;

	curs_attrset_n( CURS_ATTR_N_ACID );
	for( m = 0; m < MBR_MAX_N; m++ ){
		for( n = XX_ACID_IMAGE_MAX_N - 1; n >= 0; n-- ){
			idx = (xx_acid->homing_idx + n)
					% XX_ACID_IMAGE_MAX_N;
			x = (xx_acid->homing_x[m][idx] / fix) - draw->x;
			y = (xx_acid->homing_y[m][idx] / fix) - draw->y;
			x *= 2;

			if( n == 0 )
				str = xx_homing_head;
			else if( n == (XX_ACID_IMAGE_MAX_N - 1) )
				str = xx_homing_tail;
			else
				str = xx_homing_image;

			if( g_flg_text_mode )
				curs_attrset_n( CURS_ATTR_N_ACID );

			if( g_flg_gui && g_flg_text_mode )
				print_vfx( FALSE, x, y, MSG_S, str );
			else
				print_vfx_cui( FALSE, x, y, MSG_S, str );
		}
	}
	curs_attrset_dflt();
}

/***************************************************************
* XX の回転弾攻撃
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_rotation( mnstr_t *p )
{
	set_open_xx_jaw( TRUE );

	play_sound_xx( XX_ACT_KIND_PARALYZE );
	xx_act_rotation_draw( p );

	redraw_map();

	set_open_xx_jaw( FALSE );
}

/***************************************************************
* XX の回転弾攻撃の描画
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_rotation_draw( mnstr_t *p )
{
	xx_rotation_t	xx_rotation;
	pos_t	*draw;
	pos_t	jaw;
	long	sg;
	long	q;
	double	rad;
	long	x, y;
	long	anime_n;
	bool_t	flg_end;
	long	r, n, i;

	/* 初期化 */

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	get_attack_jaw_pos( &jaw );
	jaw.x += 1;
	jaw.y += 1;

	for( r = 0; r < XX_ROTATION_RING_MAX_N; r++ ){
		xx_rotation.flg_move[r] = FALSE;
		xx_rotation.q[r] = 0;
		xx_rotation.r[r] = 0;
	}
	xx_rotation.flg_move[0] = TRUE;

	/* 描画 */

	anime_n = 0;
	flg_end = FALSE;
	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( flg_end )
			break;

		for( r = 0; r < XX_ROTATION_RING_MAX_N; r++ ){
			if( !xx_rotation.flg_move[r] )
				continue;

			for( n = 0; n < XX_ROTATION_MAX_N; n++ ){
				q = n * XX_ROTATION_Q;
				q += xx_rotation.q[r];
				q = (q % 360 + 360) % 360;

				rad = (double)q * DBL_PI / 180.0;

				x = jaw.x + xx_rotation.r[r] * cos( rad );
				y = jaw.y + xx_rotation.r[r] * sin( rad );
				xx_rotation.x[r][n] = x;
				xx_rotation.y[r][n] = y;
			}
		}

		if( g_flg_text_mode || (g_flg_cui && !g_flg_gui) )
			if( (i % g_frame_skip) == 0 )
				redraw_map();

		curs_attrset_n( CURS_ATTR_N_COLD );
		for( r = 0; r < XX_ROTATION_RING_MAX_N; r++ ){
			if( !xx_rotation.flg_move[r] )
				continue;

			for( n = 0; n < XX_ROTATION_MAX_N; n++ ){
				x = xx_rotation.x[r][n];
				y = xx_rotation.y[r][n];
				x -= draw->x;
				y -= draw->y;
				x *= 2;

				if( g_flg_text_mode )
					curs_attrset_n( CURS_ATTR_N_COLD );

				if( g_flg_gui && g_flg_text_mode ){
					print_vfx( FALSE, x, y, MSG_S,
							xx_rotation_str );
				} else {
					print_vfx_cui( FALSE, x, y, MSG_S,
							xx_rotation_str );
				}
			}
		}
		curs_attrset_dflt();

		if( (i % g_frame_skip) == 0 ){
			call_pcg_dun_set_xx_attack(
					XX_ACT_KIND_PARALYZE,
					&xx_rotation );
			call_pcg_dun_draw_turn( TRUE );

			wait_clock( XX_ROTATION_WAIT_FRAME_N );
		}

		sg = +1;
		for( r = 0; r < XX_ROTATION_RING_MAX_N; r++ ){
			sg *= -1;

			if( !xx_rotation.flg_move[r] )
				continue;

			/* 移動 */

			q = xx_rotation.q[r];
			q += sg * XX_ROTATION_VQ;
			q = (q % 360 + 360) % 360;
			xx_rotation.q[r] = q;

			xx_rotation.r[r] += XX_ROTATION_VR;

			/* 発射 */

			do {
				long	nr;

				if( xx_rotation.r[r] < XX_ROTATION_NEXT_R )
					break;
				if( anime_n >= XX_ROTATION_ANIME_N )
					break;
				nr = (r + 1) % XX_ROTATION_RING_MAX_N;
				if( xx_rotation.flg_move[nr] )
					break;

				xx_rotation.flg_move[nr] = TRUE;
				xx_rotation.r[nr] = 0;
				break;
			} while( 0 );

			/* 停止 */

			if( xx_rotation.r[r] > XX_ROTATION_MAX_R ){
				xx_rotation.flg_move[r] = FALSE;
				xx_rotation.r[r] = 0;
				if( r == 0 ){
					anime_n++;
				}
			}
		}

		/* 終了判定 */

		flg_end = TRUE;
		for( r = 0; r < XX_ROTATION_RING_MAX_N; r++ ){
			if( anime_n < XX_ROTATION_ANIME_N ){
				flg_end = FALSE;
				break;
			}
			if( xx_rotation.flg_move[r] ){
				flg_end = FALSE;
				break;
			}
		}
	}
}

/***************************************************************
* XX の渦巻き弾攻撃
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_whirl( mnstr_t *p )
{
	set_open_xx_jaw( TRUE );

	play_sound_xx( XX_ACT_KIND_POISON );
	xx_act_whirl_draw( p );

	redraw_map();

	set_open_xx_jaw( FALSE );
}

/***************************************************************
* XX の渦巻き弾攻撃の描画
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_whirl_draw( mnstr_t *p )
{
	xx_whirl_t	xx_whirl;
	pos_t	*draw;
	pos_t	jaw;
	double	rad;
	long	x, y;
	long	anime_n;
	bool_t	flg_end;
	long	n, i;

	/* 初期化 */

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	get_attack_jaw_pos( &jaw );
	jaw.x += 1;
	jaw.y += 1;

	xx_whirl.head_n = 0;
	for( n = 0; n < XX_WHIRL_MAX_N; n++ ){
		xx_whirl.flg_move[n] = FALSE;
		xx_whirl.q[n] = XX_WHIRL_Q * n;
		xx_whirl.r[n] = 0;
	}

	/* 描画 */

	anime_n = 0;
	flg_end = FALSE;
	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( flg_end )
			break;

		for( n = 0; n < XX_WHIRL_MAX_N; n++ ){
			if( !xx_whirl.flg_move[n] )
				continue;

			rad = (double)xx_whirl.q[n] * DBL_PI / 180.0;

			x = jaw.x + xx_whirl.r[n] * cos( rad );
			y = jaw.y + xx_whirl.r[n] * sin( rad );
			xx_whirl.x[n] = x;
			xx_whirl.y[n] = y;
		}

		if( g_flg_text_mode || (g_flg_cui && !g_flg_gui) )
			if( (i % g_frame_skip) == 0 )
				redraw_map();

		curs_attrset_n( CURS_ATTR_N_HEAT );
		for( n = 0; n < XX_WHIRL_MAX_N; n++ ){
			if( !xx_whirl.flg_move[n] )
				continue;

			x = xx_whirl.x[n];
			y = xx_whirl.y[n];
			x -= draw->x;
			y -= draw->y;
			x *= 2;

			if( g_flg_text_mode )
				curs_attrset_n( CURS_ATTR_N_HEAT );

			if( g_flg_gui && g_flg_text_mode ){
				print_vfx( FALSE, x, y, MSG_S,
						xx_whirl_str );
			} else {
				print_vfx_cui( FALSE, x, y, MSG_S,
						xx_whirl_str );
			}
		}
		curs_attrset_dflt();

		if( (i % g_frame_skip) == 0 ){
			call_pcg_dun_set_xx_attack(
					XX_ACT_KIND_POISON, &xx_whirl );
			call_pcg_dun_draw_turn( TRUE );

			wait_clock( XX_WHIRL_WAIT_FRAME_N );
		}

		/* 発射 */

		if( anime_n < XX_WHIRL_ANIME_N ){
			xx_whirl.head_n++;
			xx_whirl.head_n %= XX_WHIRL_MAX_N;
			xx_whirl.flg_move[xx_whirl.head_n] = TRUE;
		}

		/* 停止 */

		for( n = 0; n < XX_WHIRL_MAX_N; n++ ){
			if( xx_whirl.flg_move[n] )
				xx_whirl.r[n] += XX_WHIRL_VR;

			if( xx_whirl.r[n] > XX_WHIRL_MAX_R ){
				xx_whirl.flg_move[n] = FALSE;
				xx_whirl.r[n] = 0;
				if( n == 0 ){
					anime_n++;
				}
			}
		}

		/* 終了判定 */

		flg_end = TRUE;
		for( n = 0; n < XX_WHIRL_MAX_N; n++ ){
			if( anime_n < XX_WHIRL_ANIME_N ){
				flg_end = FALSE;
				break;
			}
			if( xx_whirl.flg_move[n] ){
				flg_end = FALSE;
				break;
			}
		}
	}
}

/***************************************************************
* XX の扇弾攻撃
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_fan( mnstr_t *p )
{
	play_sound_xx( XX_ACT_KIND_SLEEP );
	xx_act_fan_draw( p );

	redraw_map();
}

/***************************************************************
* XX の扇弾攻撃の描画
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_fan_draw( mnstr_t *p )
{
	xx_fan_t	xx_fan;
	pos_t	*draw;
	pos_t	skull;
	long	q;
	double	rad;
	long	x, y;
	long	anime_n;
	bool_t	flg_end;
	long	n, w, i;

	/* 初期化 */

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	get_attack_skull_pos( &skull );

	for( n = 0; n < XX_FAN_MAX_N; n++ ){
		xx_fan.flg_move[n] = FALSE;
		xx_fan.r[n] = 0;
	}
	for( w = 0; w < XX_FAN_MAX_WAY; w++ ){
		q = 90 - (XX_FAN_Q * (XX_FAN_MAX_WAY / 2));
		q += w * XX_FAN_Q;
		xx_fan.q[w] = q;
	}
	xx_fan.flg_move[0] = TRUE;

	/* 描画 */

	anime_n = 0;
	flg_end = FALSE;
	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( flg_end )
			break;

		for( n = 0; n < XX_FAN_MAX_N; n++ ){
			if( !xx_fan.flg_move[n] )
				continue;

			for( w = 0; w < XX_FAN_MAX_WAY; w++ ){
				rad = (double)xx_fan.q[w] * DBL_PI / 180.0;

				x = skull.x + xx_fan.r[n] * cos( rad );
				y = skull.y + xx_fan.r[n] * sin( rad );
				xx_fan.x[n][w] = x;
				xx_fan.y[n][w] = y;
			}
		}

		if( g_flg_text_mode || (g_flg_cui && !g_flg_gui) )
			if( (i % g_frame_skip) == 0 )
				redraw_map();

		curs_attrset_n( CURS_ATTR_N_MIND );
		for( n = 0; n < XX_FAN_MAX_N; n++ ){
			if( !xx_fan.flg_move[n] )
				continue;

			for( w = 0; w < XX_FAN_MAX_WAY; w++ ){
				x = xx_fan.x[n][w];
				y = xx_fan.y[n][w];
				x -= draw->x;
				y -= draw->y;
				x *= 2;

				if( g_flg_text_mode )
					curs_attrset_n( CURS_ATTR_N_MIND );

				if( g_flg_gui && g_flg_text_mode ){
					print_vfx( FALSE, x, y, MSG_S,
							xx_fan_str );
				} else {
					print_vfx_cui( FALSE, x, y, MSG_S,
							xx_fan_str );
				}
			}
		}
		curs_attrset_dflt();

		if( (i % g_frame_skip) == 0 ){
			call_pcg_dun_set_xx_attack(
					XX_ACT_KIND_SLEEP, &xx_fan );
			call_pcg_dun_draw_turn( TRUE );

			wait_clock( XX_FAN_WAIT_FRAME_N );
		}

		/* 移動 */

		for( n = 0; n < XX_FAN_MAX_N; n++ ){
			if( !xx_fan.flg_move[n] )
				continue;

			xx_fan.r[n] += XX_FAN_VR;
		}

		/* 発射 */

		do {
			long	nr;

			nr = (i / XX_FAN_DR) % XX_FAN_MAX_N;
			if( anime_n >= XX_FAN_ANIME_N )
				break;
			if( xx_fan.flg_move[nr] )
				break;

			xx_fan.flg_move[nr] = TRUE;
			xx_fan.r[nr] = 0;
			break;
		} while( 0 );

		/* 停止 */

		for( n = 0; n < XX_FAN_MAX_N; n++ ){
			if( !xx_fan.flg_move[n] )
				continue;

			if( xx_fan.r[n] > XX_FAN_MAX_R ){
				xx_fan.flg_move[n] = FALSE;
				xx_fan.r[n] = 0;
				if( n == 0 ){
					anime_n++;
				}
			}
		}

		/* 終了判定 */

		flg_end = TRUE;
		for( n = 0; n < XX_FAN_MAX_N; n++ ){
			if( anime_n < XX_FAN_ANIME_N ){
				flg_end = FALSE;
				break;
			}
			if( xx_fan.flg_move[n] ){
				flg_end = FALSE;
				break;
			}
		}
	}
}

/***************************************************************
* XX の平手打ち攻撃
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_slap( mnstr_t *p )
{
	long	i;

	for( i = 0; i < XX_SLAP_ANIME_N; i++ ){
		play_sound_xx( XX_ACT_KIND_SLAP );
		xx_act_slap_draw( p );
	}

	redraw_map();
}

/***************************************************************
* XX の平手打ち攻撃の描画
* mnstr_t *p : XX のキャラクタ・データ
***************************************************************/

void	xx_act_slap_draw( mnstr_t *p )
{
	set_slap_xx_arm_left( TRUE );
	wait_clock( XX_SLAP_WAIT_FRAME_N );
	set_slap_xx_arm_left( FALSE );

	set_slap_xx_arm_right( TRUE );
	wait_clock( XX_SLAP_WAIT_FRAME_N );
	set_slap_xx_arm_right( FALSE );

	wait_clock( XX_SLAP_WAIT_FRAME_N );
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_last_boss_c( void )
{
	check_memory( check_memory_last_boss_c_EXEL_JUMP_MAX_Y,
			"last-boss.c: EXEL_JUMP_MAX_Y" );
	check_memory( check_memory_last_boss_c_xx_pos,
			"last-boss.c: xx_pos" );
	check_memory( check_memory_last_boss_c_joint_skull,
			"last-boss.c: joint_skull" );
	check_memory( check_memory_last_boss_c_pos_skull,
			"last-boss.c: pos_skull" );
	check_memory( check_memory_last_boss_c_flg_open_xx_jaw,
			"last-boss.c: flg_open_xx_jaw" );
	check_memory( check_memory_last_boss_c_XX_HEAT_DY,
			"last-boss.c: XX_HEAT_DY" );
	check_memory( check_memory_last_boss_c_XX_HEAT_WAIT_FRAME_N,
			"last-boss.c: XX_HEAT_WAIT_FRAME_N" );
	check_memory( check_memory_last_boss_c_xx_blast_heat,
			"last-boss.c: xx_blast_heat" );
	check_memory( check_memory_last_boss_c_XX_COLD_LASER_MAX_LEN,
			"last-boss.c: XX_COLD_LASER_MAX_LEN" );
	check_memory( check_memory_last_boss_c_XX_COLD_BIT_WAIT_FRAME_N,
			"last-boss.c: XX_COLD_BIT_WAIT_FRAME_N" );
	check_memory( check_memory_last_boss_c_xx_laser,
			"last-boss.c: xx_laser" );
	check_memory( check_memory_last_boss_c_xx_laser_dxy,
			"last-boss.c: xx_laser_dxy" );
	check_memory( check_memory_last_boss_c_xx_bit,
			"last-boss.c: xx_bit" );
	check_memory( check_memory_last_boss_c_XX_MIND_ADD_RATE,
			"last-boss.c: XX_MIND_ADD_RATE" );
	check_memory( check_memory_last_boss_c_XX_MIND_ANIME_N,
			"last-boss.c: XX_MIND_ANIME_N" );
	check_memory( check_memory_last_boss_c_xx_refract_head,
			"last-boss.c: xx_refract_head" );
	check_memory( check_memory_last_boss_c_XX_ACID_MAX_Q,
			"last-boss.c: XX_ACID_MAX_Q" );
	check_memory( check_memory_last_boss_c_XX_ACID_WAIT_FRAME_N,
			"last-boss.c: XX_ACID_WAIT_FRAME_N" );
	check_memory( check_memory_last_boss_c_xx_homing_bgn_v,
			"last-boss.c: xx_homing_bgn_v" );
	check_memory( check_memory_last_boss_c_xx_homing_head,
			"last-boss.c: xx_homing_head" );
	check_memory( check_memory_last_boss_c_XX_ROTATION_ANIME_N,
			"last-boss.c: XX_ROTATION_ANIME_N" );
	check_memory( check_memory_last_boss_c_xx_rotation_str,
			"last-boss.c: xx_rotation_str" );
	check_memory( check_memory_last_boss_c_XX_WHIRL_ANIME_N,
			"last-boss.c: XX_WHIRL_ANIME_N" );
	check_memory( check_memory_last_boss_c_xx_whirl_str,
			"last-boss.c: xx_whirl_str" );
	check_memory( check_memory_last_boss_c_XX_FAN_ANIME_N,
			"last-boss.c: XX_FAN_ANIME_N" );
	check_memory( check_memory_last_boss_c_xx_fan_str,
			"last-boss.c: xx_fan_str" );
	check_memory( check_memory_last_boss_c_XX_SLAP_WAIT_FRAME_N,
			"last-boss.c: XX_SLAP_WAIT_FRAME_N" );
	check_memory( check_memory_last_boss_c_xx_attack_slap,
			"last-boss.c: xx_attack_slap" );
}
