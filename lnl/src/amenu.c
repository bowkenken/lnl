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
* $Id: amenu.c,v 1.121 2014/03/01 23:48:01 bowkenken Exp $
***************************************************************/

/***************************************************************
* 作戦(自動マーク)
***************************************************************/

#define	AMENU_C
#include	"inc.h"

/***************************************************************/

/* 階層移動などでメニューをリセットするか? */
#define	FLG_RESET_MENU	0

#define	STR_TTL_AUTO_MARK_SPLIT_NAME	" - "
#define	STR_TTL_AUTO_MARK_SPLIT_CODE	"\n"

/***************************************************************/

static auto_mark_t	ls_auto_mark
		[LS_MBR_MAX_N][AUTO_MARK_MAX_N][POSITION_KIND_MAX_N];
check_memory_def( check_memory_amenu_c_ls_auto_mark )
static bool_t	ls_flg_ena_auto_mark[AUTO_MARK_MAX_N];
check_memory_def( check_memory_amenu_c_ls_flg_ena_auto_mark )

static auto_mark_t	clip_board_large[LS_MBR_MAX_N][POSITION_KIND_MAX_N];
check_memory_def( check_memory_amenu_c_clip_board_large )
static auto_mark_t	clip_board_small;
check_memory_def( check_memory_amenu_c_clip_board_small )

static auto_mark_appoint_item_t	clip_board_large_item
		[LS_MBR_MAX_N][AUTO_MARK_APPOINT_ITEM_MAX_N];
check_memory_def( check_memory_amenu_c_clip_board_large_item )
static auto_mark_appoint_item_t	clip_board_small_item
		[AUTO_MARK_APPOINT_ITEM_MAX_N];
check_memory_def( check_memory_amenu_c_clip_board_small_item )

static char	msg_ttl_auto_mark[AUTO_MARK_MAX_N]
		[MSG_TTL_AUTO_MARK_MAX_BYTE + 1];
check_memory_def( check_memory_amenu_c_msg_ttl_auto_mark )
static char	clip_board_ttl
		[MSG_TTL_AUTO_MARK_MAX_BYTE + 1];
check_memory_def( check_memory_amenu_c_clip_board_ttl )

static long	auto_mark_cur_n;
static mbr_t	*g_sel_mbr;
check_memory_def( check_memory_amenu_c_auto_mark_cur_n )

static auto_mark_t	dflt_auto_mark_fight = {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_ACT_FIGHT,
	AUTO_MARK_COND_NEAREST,
	"",
	FLG_AUTO_MARK_EDIT_CONT,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_fight_prio = {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_ACT_FIGHT,
	AUTO_MARK_COND_NEAREST,
	"",
	FLG_AUTO_MARK_EDIT_PRIORITY | FLG_AUTO_MARK_EDIT_CONT,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_throw = {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_DIST_MEDIUM,
	AUTO_MARK_ACT_THROW,
	AUTO_MARK_COND_NEAREST,
	"",
	FLG_NULL,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_throw_prio = {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_DIST_MEDIUM,
	AUTO_MARK_ACT_THROW,
	AUTO_MARK_COND_NEAREST,
	"",
	FLG_AUTO_MARK_EDIT_PRIORITY | FLG_AUTO_MARK_EDIT_CONT,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_fight_far = {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_DIST_FAR,
	AUTO_MARK_ACT_FIGHT,
	AUTO_MARK_COND_NEAREST,
	"",
	FLG_NULL,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_fight_far_prio = {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_DIST_FAR,
	AUTO_MARK_ACT_FIGHT,
	AUTO_MARK_COND_NEAREST,
	"",
	FLG_AUTO_MARK_EDIT_PRIORITY | FLG_AUTO_MARK_EDIT_CONT,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_fight_all = {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_ACT_FIGHT,
	AUTO_MARK_COND_DISPERSE,
	"",
	FLG_AUTO_MARK_EDIT_CONT,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_fight_all_prio = {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_ACT_FIGHT,
	AUTO_MARK_COND_DISPERSE,
	"",
	FLG_AUTO_MARK_EDIT_PRIORITY | FLG_AUTO_MARK_EDIT_CONT,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_item_all = {
	AUTO_MARK_TRGT_ITEM,
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_ACT_PICK_UP,
	AUTO_MARK_COND_DISPERSE,
	"",
	FLG_AUTO_MARK_EDIT_PRIORITY | FLG_AUTO_MARK_EDIT_CONT,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_item_own = {
	AUTO_MARK_TRGT_ITEM,
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_ACT_PICK_UP,
	AUTO_MARK_COND_OWN,
	"",
	FLG_AUTO_MARK_EDIT_PRIORITY | FLG_AUTO_MARK_EDIT_CONT,
	DFLT_AUTO_MARK_NULL,
};

static auto_mark_t	dflt_auto_mark_clear = {
	AUTO_MARK_TRGT_CLEAR,
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_ACT_FIGHT,
	AUTO_MARK_COND_DISPERSE,
	"",
	FLG_AUTO_MARK_EDIT_PRIORITY,
	DFLT_AUTO_MARK_NULL,
};

check_memory_def( check_memory_amenu_c_dflt_auto_mark_fight )

static auto_mark_appoint_item_t	auto_mark_appoint_item
		[LS_MBR_MAX_N][AUTO_MARK_MAX_N]
		[AUTO_MARK_APPOINT_ITEM_MAX_N];
check_memory_def( check_memory_amenu_c_auto_mark_appoint_item )

static auto_mark_appoint_item_t	auto_mark_appoint_item_dflt
		[AUTO_MARK_APPOINT_ITEM_MAX_N] = {
	{ FACE_MJR_WEAPON, FACE_MNR_KNIFE, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_SHORT_SWORD, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_LONG_SWORD, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_SABRE, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_RAPIER, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_HAND_AXE, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_BATTLE_AXE, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_SPEAR, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_LANCE, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_FLAIL, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_MACE, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_HAMMER, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_GLAIVE, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_KNUCKLE, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_BOW, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_ARW, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_STONE, TRUE },
	{ FACE_MJR_WEAPON, FACE_MNR_DAGGER, TRUE },

	{ FACE_MJR_ARMOR, FACE_MNR_ARMOR_SHIELD, TRUE },
	{ FACE_MJR_ARMOR, FACE_MNR_ARMOR_HEAD, TRUE },
	{ FACE_MJR_ARMOR, FACE_MNR_ARMOR_BODY, TRUE },
	{ FACE_MJR_ARMOR, FACE_MNR_ARMOR_ARM, TRUE },
	{ FACE_MJR_ARMOR, FACE_MNR_ARMOR_FEET, TRUE },
	{ FACE_MJR_ARMOR, FACE_MNR_ARMOR_ABOUT_BODY, TRUE },

	{ FACE_MJR_POTION, FACE_MNR_NULL, TRUE },

	{ FACE_MJR_SCROLL, FACE_MNR_NULL, TRUE },

	{ FACE_MJR_STICK, FACE_MNR_WAND, TRUE },
	{ FACE_MJR_STICK, FACE_MNR_ROD, TRUE },
	{ FACE_MJR_STICK, FACE_MNR_STAFF, TRUE },

	{ FACE_MJR_ACCESSORY, FACE_MNR_RING, TRUE },
	{ FACE_MJR_ACCESSORY, FACE_MNR_AMULET, TRUE },
	{ FACE_MJR_ACCESSORY, FACE_MNR_NECKLACE, TRUE },

	{ FACE_MJR_FOOD, FACE_MNR_NULL, TRUE },

	{ FACE_MJR_CHEST, FACE_MNR_NULL, FALSE },

	{ FACE_MJR_COIN, FACE_MNR_NULL, TRUE },

	{ FACE_MJR_GEM, FACE_MNR_NULL, TRUE },

	{ FACE_MJR_MISC, FACE_MNR_INST, TRUE },
	{ FACE_MJR_MISC, FACE_MNR_ANTHOLOGY, TRUE },
	{ FACE_MJR_MISC, FACE_MNR_LIGHT, TRUE },
	{ FACE_MJR_MISC, FACE_MNR_SPIKE, TRUE },
	{ FACE_MJR_MISC, FACE_MNR_TOBACCO, TRUE },
	{ FACE_MJR_MISC, FACE_MNR_PIPE, TRUE },
	{ FACE_MJR_MISC, FACE_MNR_RARE_GOODS, TRUE },
	{ FACE_MJR_MISC, FACE_MNR_BONE_GOOD, FALSE },
	{ FACE_MJR_MISC, FACE_MNR_BONE_EVIL, FALSE },
	{ FACE_MJR_MISC, FACE_MNR_JUNK, FALSE },

	{ FACE_MJR_NULL, FACE_MNR_NULL, FALSE },
};
check_memory_def( check_memory_amenu_c_auto_mark_appoint_item_dflt )

/***************************************************************/

#include	"amenu-tab.h"

/***************************************************************
* 初期化
***************************************************************/

void	init_auto_menu( void )
{
	long	i, k;

	g_sel_mbr = NULL;
	auto_mark_cur_n = 0;

	reset_ls_flg_ena_auto_mark();
	init_auto_mark_all_appoint();
	init_auto_mark_all_mbr();

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
			clip_board_large[i][k] = ls_auto_mark[i][0][k];
		}

		for( k = 0; k < AUTO_MARK_APPOINT_ITEM_MAX_N; k++ ){
			clip_board_large_item[i][k]
					= auto_mark_appoint_item[i][0][k];
		}
	}

	clip_board_small = ls_auto_mark[0][0][0];
	str_nz_cpy( clip_board_ttl,
			msg_ttl_auto_mark[0],
			MSG_TTL_AUTO_MARK_MAX_BYTE );
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_auto_menu( void )
{
	long	i, k;

#if	FLG_RESET_MENU
	g_sel_mbr = NULL;
	auto_mark_cur_n = 0;
#endif

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		clip_board_large[i][POSITION_KIND_FORWARD]
				= dflt_auto_mark_fight;
		clip_board_large[i][POSITION_KIND_HALFBACK]
				= dflt_auto_mark_throw;
		clip_board_large[i][POSITION_KIND_BACK]
				= dflt_auto_mark_fight;

		for( k = 0; k < AUTO_MARK_APPOINT_ITEM_MAX_N; k++ ){
			clip_board_large_item[i][k]
					= auto_mark_appoint_item_dflt[k];
		}
	}

	clip_board_small = dflt_auto_mark_fight;
	for( k = 0; k < AUTO_MARK_APPOINT_ITEM_MAX_N; k++ ){
		clip_board_small_item[k]
				= auto_mark_appoint_item_dflt[k];
	}

	str_nz_cpy( clip_board_ttl, "",
			MSG_TTL_AUTO_MARK_MAX_BYTE );
}

/***************************************************************
* 有効フラグをリセット
***************************************************************/

void	reset_ls_flg_ena_auto_mark()
{
	long	j;

	for( j = 0; j < AUTO_MARK_MAX_N; j++ )
		ls_flg_ena_auto_mark[j] = FALSE;
}

/***************************************************************
* すべてのメンバーのアイテムの種類の初期化
***************************************************************/

void	init_auto_mark_all_appoint( void )
{
	long	i;

	for( i = 0; i < LS_MBR_MAX_N; i++ )
		init_auto_mark_appoint( i );
}

/***************************************************************
* メンバーのアイテムの種類の初期化
***************************************************************/

void	init_auto_mark_appoint( long ls_mbr_n )
{
	long	i, j, k;

	i = ls_mbr_n;

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		for( k = 0; k < AUTO_MARK_APPOINT_ITEM_MAX_N; k++ ){
			auto_mark_appoint_item_t	*a;

			a = &(auto_mark_appoint_item_dflt[k]);
			auto_mark_appoint_item[i][j][k] = *a;
		}
	}
}

/***************************************************************
* すべてのメンバーの初期化
***************************************************************/

void	init_auto_mark_all_mbr( void )
{
	long	i;

	for( i = 0; i < LS_MBR_MAX_N; i++ )
		init_auto_mark_mbr( i );
}

/***************************************************************
* メンバーの初期化
* long ls_mbr_n : メンバーのリスト番号
***************************************************************/

void	init_auto_mark_mbr( long ls_mbr_n )
{
	long	src_bgn_idx, dst_bgn_idx, idx_n;
	const long	max_item = AUTO_MARK_APPOINT_ITEM_MAX_N;
	long	i, j, k;

	/* 初期化 */

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
			ls_auto_mark[ls_mbr_n][j][k] = dflt_auto_mark_clear;
			ls_auto_mark[ls_mbr_n][j][k].dflt
					= DFLT_AUTO_MARK_NULL;
		}
		str_nz_cpy( msg_ttl_auto_mark[j],
				MSG_NAME_DFLT_AUTO_MARK_CLEAR,
				MSG_TTL_AUTO_MARK_MAX_BYTE );
		ls_flg_ena_auto_mark[j] = FALSE;
	}

	src_bgn_idx = DFLT_AUTO_MARK_MAX_N - DFLT_AUTO_MARK_MIN_N;
	j = src_bgn_idx;

	/* 戦闘(追加) */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_FIGHT,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_FIGHT;
	ls_flg_ena_auto_mark[j] = TRUE;
	j++;

	/* 戦闘(全員) */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_FIGHT_PRIO,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_FIGHT_PRIO;
	ls_flg_ena_auto_mark[j] = TRUE;
	j++;

	/* 接近戦闘(追加) */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_FIGHT_NO_THROW,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_FIGHT_NO_THROW;
	ls_flg_ena_auto_mark[j] = TRUE;
	j++;

	/* 接近戦闘(全員) */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_FIGHT_NO_THROW_PRIO,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_FIGHT_NO_THROW_PRIO;
	ls_flg_ena_auto_mark[j] = TRUE;
	j++;

	/* 殲滅戦(追加) */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_FIGHT_ALL,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_FIGHT_ALL;
	ls_flg_ena_auto_mark[j] = TRUE;
	j++;

	/* 殲滅戦(全員) */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_FIGHT_ALL_PRIO,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_FIGHT_ALL_PRIO;
	ls_flg_ena_auto_mark[j] = TRUE;
	j++;

	/* 全てのアイテム */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_ITEM_ALL,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_ITEM_ALL;
	ls_flg_ena_auto_mark[j] = TRUE;
	j++;

	/* 持っているアイテム */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_ITEM_OWN,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_ITEM_OWN;
	ls_flg_ena_auto_mark[j] = TRUE;
	j++;

	/* 退却 */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_RETREAT,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_flg_ena_auto_mark[j] = TRUE;
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_RETREAT;
	j++;

	/* 解除 */

	str_nz_cpy( msg_ttl_auto_mark[j],
			MSG_NAME_DFLT_AUTO_MARK_CLEAR,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
			= DFLT_AUTO_MARK_CLEAR;
	ls_flg_ena_auto_mark[j] = TRUE;
	j++;

	idx_n = j - src_bgn_idx;

	/* デフォルトを設定 */

	set_dflt_auto_mark_mbr( ls_mbr_n );

	/* デフォルトのコピーを先頭に作成 */

	dst_bgn_idx = 0;
	i = ls_mbr_n;

	for( j = 0; j < idx_n; j++ ){
		long	src, dst;

		src = src_bgn_idx + j;
		dst = dst_bgn_idx + j;

		str_nz_cpy( msg_ttl_auto_mark[dst],
				msg_ttl_auto_mark[src],
				MSG_TTL_AUTO_MARK_MAX_BYTE );
		for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
			ls_auto_mark[i][dst][k]
					= ls_auto_mark[i][src][k];
			ls_auto_mark[i][dst][k].dflt
					= DFLT_AUTO_MARK_NULL;
		}
		for( k = 0; k < max_item; k++ ){
			auto_mark_appoint_item[i][dst][k]
					= auto_mark_appoint_item[i][src][k];
		}
		ls_flg_ena_auto_mark[dst] = ls_flg_ena_auto_mark[src];
	}
}

/***************************************************************
* 新規メンバーの初期化
* long ls_mbr_n : メンバーのリスト番号
***************************************************************/

void	init_auto_mark_new_mbr( long ls_mbr_n )
{
	long	j, k;

	/* 初期化 */

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		if( ls_auto_mark[ls_mbr_n][j][POSITION_KIND_NULL].dflt
				!= DFLT_AUTO_MARK_NULL ){
			continue;
		}

		for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
			ls_auto_mark[ls_mbr_n][j][k] = dflt_auto_mark_clear;
		}
	}
}

/***************************************************************
* メンバーのデフォルトの自動マークを設定
* long ls_mbr_n : メンバーのリスト番号
***************************************************************/

void	set_dflt_auto_mark_mbr( long ls_mbr_n )
{
	auto_mark_t	*ls;
	long	n;

	for( n = DFLT_AUTO_MARK_NULL + 1; n < DFLT_AUTO_MARK_MAX_N; n++ ){
		ls = srch_dflt_auto_mark( ls_mbr_n, (dflt_auto_mark_t)n );
		if( ls != NULL ){
			set_dflt_auto_mark( ls_mbr_n, ls );
		}
	}
}

/***************************************************************
* デフォルトの自動マークを設定
* long ls_mbr_n : メンバーのリスト番号
* auto_mark_t *ls : 自動マーク
***************************************************************/

void	set_dflt_auto_mark( long ls_mbr_n, auto_mark_t ls[] )
{
	auto_mark_t	*forward, *halfback, *back;

	if( ls == NULL )
		return;

	forward = &dflt_auto_mark_clear;
	halfback = &dflt_auto_mark_clear;
	back = &dflt_auto_mark_clear;

	switch( ls->dflt ){
	case DFLT_AUTO_MARK_NULL:
	case DFLT_AUTO_MARK_MAX_N:
		return;
	case DFLT_AUTO_MARK_FIGHT:
		/* 戦闘(追加) */
		forward = &dflt_auto_mark_fight;
		halfback = &dflt_auto_mark_throw;
		back = &dflt_auto_mark_fight_far;
		break;
	case DFLT_AUTO_MARK_FIGHT_PRIO:
		/* 戦闘(全員) */
		forward = &dflt_auto_mark_fight_prio;
		halfback = &dflt_auto_mark_throw_prio;
		back = &dflt_auto_mark_fight_far_prio;
		break;
	case DFLT_AUTO_MARK_FIGHT_NO_THROW:
		/* 接近戦闘(追加) */
		forward = &dflt_auto_mark_fight;
		halfback = &dflt_auto_mark_fight;
		back = &dflt_auto_mark_fight_far;
		break;
	case DFLT_AUTO_MARK_FIGHT_NO_THROW_PRIO:
		/* 接近戦闘(全員) */
		forward = &dflt_auto_mark_fight_prio;
		halfback = &dflt_auto_mark_fight_prio;
		back = &dflt_auto_mark_fight_far_prio;
		break;
	case DFLT_AUTO_MARK_FIGHT_ALL:
		/* 殲滅戦(追加) */
		forward = &dflt_auto_mark_fight_all;
		halfback = &dflt_auto_mark_fight_all;
		back = &dflt_auto_mark_fight_all;
		break;
	case DFLT_AUTO_MARK_FIGHT_ALL_PRIO:
		/* 殲滅戦(全員) */
		forward = &dflt_auto_mark_fight_all_prio;
		halfback = &dflt_auto_mark_fight_all_prio;
		back = &dflt_auto_mark_fight_all_prio;
		break;
	case DFLT_AUTO_MARK_ITEM_ALL:
		/* 全てのアイテム */
		forward = &dflt_auto_mark_item_all;
		halfback = &dflt_auto_mark_item_all;
		back = &dflt_auto_mark_item_all;
		break;
	case DFLT_AUTO_MARK_ITEM_OWN:
		/* 持っているアイテム */
		forward = &dflt_auto_mark_item_own;
		halfback = &dflt_auto_mark_item_own;
		back = &dflt_auto_mark_item_own;
		break;
	case DFLT_AUTO_MARK_RETREAT:
		/* 退却 */
		forward = &dflt_auto_mark_clear;
		halfback = &dflt_auto_mark_clear;
		back = &dflt_auto_mark_clear;
		break;
	case DFLT_AUTO_MARK_CLEAR:
		/* 解除 */
		forward = &dflt_auto_mark_clear;
		halfback = &dflt_auto_mark_clear;
		back = &dflt_auto_mark_clear;
		break;
	}

	ls[POSITION_KIND_FORWARD] = *forward;
	ls[POSITION_KIND_HALFBACK] = *halfback;
	ls[POSITION_KIND_BACK] = *back;

	ls[POSITION_KIND_FORWARD].dflt = ls[POSITION_KIND_NULL].dflt;
	ls[POSITION_KIND_HALFBACK].dflt = ls[POSITION_KIND_NULL].dflt;
	ls[POSITION_KIND_BACK].dflt = ls[POSITION_KIND_NULL].dflt;
}

/***************************************************************
* デフォルトの自動マークを検索
* long ls_mbr_n : メンバーのリスト番号
* dflt_auto_mark_t n : デフォルトの自動マークの種類
***************************************************************/

auto_mark_t	*srch_dflt_auto_mark( long ls_mbr_n, dflt_auto_mark_t n )
{
	long	j;

	for( j = 0; j < AUTO_MARK_MAX_N; j++ )
		if( ls_auto_mark[ls_mbr_n][j][0].dflt == n )
			return ls_auto_mark[ls_mbr_n][j];

	return NULL;
}

/***************************************************************
* 設定のバージョナップ
* long ls_mbr_n : メンバーのリスト番号
***************************************************************/

void	ver_up_auto_mark_1_0_4( long ls_mbr_n )
{
	long	j;
	char	*msg_no_throw = MSG_NAME_DFLT_AUTO_MARK_FIGHT_NO_THROW;
	char	*msg_no_throw_prio
			= MSG_NAME_DFLT_AUTO_MARK_FIGHT_NO_THROW_PRIO;

	j = 0;

	/* 空きを探す */

	for( ; j < AUTO_MARK_MAX_N; j++ ){
		if( ls_auto_mark[ls_mbr_n][j][0].trgt
				== AUTO_MARK_TRGT_CLEAR ){
			break;
		}
	}

	/* 殲滅戦(追加) */

	if( j < AUTO_MARK_MAX_N ){
		ls_auto_mark[ls_mbr_n][j][0] = dflt_auto_mark_fight_all;
		str_nz_cpy( msg_ttl_auto_mark[j],
				MSG_NAME_DFLT_AUTO_MARK_FIGHT_ALL,
				MSG_TTL_AUTO_MARK_MAX_BYTE );
	}
	j++;

	/* 空きを探す */

	for( ; j < AUTO_MARK_MAX_N; j++ ){
		if( ls_auto_mark[ls_mbr_n][j][0].trgt == AUTO_MARK_TRGT_CLEAR )
			break;
	}

	/* 殲滅戦(全員) */

	if( j < AUTO_MARK_MAX_N ){
		ls_auto_mark[ls_mbr_n][j][0] = dflt_auto_mark_fight_all_prio;
		str_nz_cpy( msg_ttl_auto_mark[j],
				MSG_NAME_DFLT_AUTO_MARK_FIGHT_ALL_PRIO,
				MSG_TTL_AUTO_MARK_MAX_BYTE );
	}
	j++;

	/* 接近戦闘(追加)を探す */

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		if( strcmp( msg_ttl_auto_mark[j],
				msg_no_throw ) == 0 ){
			break;
		}
	}

	/* 接近戦闘(追加) */

	if( j < AUTO_MARK_MAX_N ){
		switch( ls_mbr_n ){
		default:
		case 0:
		case 1:
		case 2:
		case 3:
			ls_auto_mark[ls_mbr_n][j][0]
					= dflt_auto_mark_fight;
			break;
		case 4:
		case 5:
			ls_auto_mark[ls_mbr_n][j][0]
					= dflt_auto_mark_fight_far;
			break;
		}
	}

	/* 接近戦闘(全員)を探す */

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		if( strcmp( msg_ttl_auto_mark[j],
				msg_no_throw_prio ) == 0 ){
			break;
		}
	}

	/* 接近戦闘(全員) */

	if( j < AUTO_MARK_MAX_N ){
		switch( ls_mbr_n ){
		default:
		case 0:
		case 1:
		case 2:
		case 3:
			ls_auto_mark[ls_mbr_n][j][0]
					= dflt_auto_mark_fight_prio;
			break;
		case 4:
		case 5:
			ls_auto_mark[ls_mbr_n][j][0]
					= dflt_auto_mark_fight_far_prio;
			break;
		}
	}
}

/***************************************************************
* 設定のバージョナップ
* long ls_mbr_n : メンバーのリスト番号
***************************************************************/

void	ver_up_auto_mark_1_1_1( long ls_mbr_n )
{
	init_auto_mark_appoint( ls_mbr_n );
}

/***************************************************************
* 設定のバージョナップ
* long ls_mbr_n : メンバーのリスト番号
***************************************************************/

void	ver_up_auto_mark_1_1_3( void )
{
	long	j;

	for( j = 0; j < AUTO_MARK_MAX_N; j++ )
		cv_msg_ttl_auto_mark( msg_ttl_auto_mark[j] );
}

/***************************************************************
* 設定のバージョナップ
***************************************************************/

void	ver_up_auto_mark_1_2_35( void )
{
	long	n, m;
	long	ls_mbr_n;
	const char	*name;

	/* デフォルトの作戦を追加 */

	for( n = DFLT_AUTO_MARK_NULL + 1; n < DFLT_AUTO_MARK_MAX_N; n++ ){
		m = AUTO_MARK_MAX_N - (DFLT_AUTO_MARK_MAX_N - n);
		ls_flg_ena_auto_mark[m] = TRUE;
		for( ls_mbr_n = 0; ls_mbr_n < LS_MBR_MAX_N; ls_mbr_n++ ){
			auto_mark_t	*ls;

			ls = ls_auto_mark[ls_mbr_n][m];
			ls[POSITION_KIND_NULL].dflt = (dflt_auto_mark_t)n;
			set_dflt_auto_mark( ls_mbr_n, ls );
		}

		name = MSG_NAME_DFLT_AUTO_MARK_CLEAR;
		switch( n ){
		case DFLT_AUTO_MARK_NULL:
		case DFLT_AUTO_MARK_MAX_N:
			break;
		case DFLT_AUTO_MARK_FIGHT:
			/* 戦闘(追加) */
			name = MSG_NAME_DFLT_AUTO_MARK_FIGHT;
			break;
		case DFLT_AUTO_MARK_FIGHT_PRIO:
			/* 戦闘(全員) */
			name = MSG_NAME_DFLT_AUTO_MARK_FIGHT_PRIO;
			break;
		case DFLT_AUTO_MARK_FIGHT_NO_THROW:
			/* 接近戦闘(追加) */
			name = MSG_NAME_DFLT_AUTO_MARK_FIGHT_NO_THROW;
			break;
		case DFLT_AUTO_MARK_FIGHT_NO_THROW_PRIO:
			/* 接近戦闘(全員) */
			name = MSG_NAME_DFLT_AUTO_MARK_FIGHT_NO_THROW_PRIO;
			break;
		case DFLT_AUTO_MARK_FIGHT_ALL:
			/* 殲滅戦(追加) */
			name = MSG_NAME_DFLT_AUTO_MARK_FIGHT_ALL;
			break;
		case DFLT_AUTO_MARK_FIGHT_ALL_PRIO:
			/* 殲滅戦(全員) */
			name = MSG_NAME_DFLT_AUTO_MARK_FIGHT_ALL_PRIO;
			break;
		case DFLT_AUTO_MARK_ITEM_ALL:
			/* 全てのアイテム */
			name = MSG_NAME_DFLT_AUTO_MARK_ITEM_ALL;
			break;
		case DFLT_AUTO_MARK_ITEM_OWN:
			/* 持っているアイテム */
			name = MSG_NAME_DFLT_AUTO_MARK_ITEM_OWN;
			break;
		case DFLT_AUTO_MARK_RETREAT:
			/* 退却 */
			name = MSG_NAME_DFLT_AUTO_MARK_RETREAT;
			break;
		case DFLT_AUTO_MARK_CLEAR:
			/* 解除 */
			name = MSG_NAME_DFLT_AUTO_MARK_CLEAR;
			break;
		}
		str_nz_cpy( msg_ttl_auto_mark[m], name,
				MSG_TTL_AUTO_MARK_MAX_BYTE );
	}

	/* 先頭へ並べ替え */

	for( n = DFLT_AUTO_MARK_MAX_N - 1; n > DFLT_AUTO_MARK_NULL; n-- ){
		m = AUTO_MARK_MAX_N - 1;
		arrange_auto_mark( m, -1 );
	}
}

/***************************************************************
* 設定のバージョナップ
***************************************************************/

void	ver_up_auto_mark_1_2_36( void )
{
	long	i, j, k;

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
			if( ls_auto_mark[i][j][0].dflt
					!= DFLT_AUTO_MARK_NULL ){
				continue;
			}

			for( k = 1; k < POSITION_KIND_MAX_N; k++ ){
				ls_auto_mark[i][j][k]
						= ls_auto_mark[i][j][0];
			}
		}
	}

	for( i = 0; i < LS_MBR_MAX_N; i++ )
		set_dflt_auto_mark_mbr( i );
}

/***************************************************************
* タイトルの区切り文字列を " - " から "\n" に変換
* char *ttl : タイトル
***************************************************************/

void	cv_msg_ttl_auto_mark( char *ttl )
{
	const char	old_split[] = " - ";
	char	work_left[MSG_TTL_AUTO_MARK_MAX_BYTE + 1];
	char	work_right[MSG_TTL_AUTO_MARK_MAX_BYTE + 1];
	char	*p;

	/* タイトルから " - " の左側を取り出す */

	str_nz_cpy( work_left, ttl, MSG_TTL_AUTO_MARK_MAX_BYTE );
	p = strstr( work_left, old_split );
	if( p != NULL )
		*p = '\0';

	str_trim_tail( work_left, " \t\n" );

	/* タイトルから " - " の右側を取り出す */

	p = strstr( ttl, old_split );
	if( p == NULL ){
		work_right[0] = '\0';
	} else {
		long	len;

		len = str_len_std( old_split );
		str_nz_cpy( work_right, &(p[len]),
				MSG_TTL_AUTO_MARK_MAX_BYTE );
	}

	/* タイトルに書き戻す */

	ttl[0] = '\0';
	str_max_n_cat( ttl, work_left,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	str_max_n_cat( ttl, STR_TTL_AUTO_MARK_SPLIT_CODE,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	str_max_n_cat( ttl, work_right,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
}

/***************************************************************
* メニューを設定
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*menu_auto_mark( menu_t **pp, menu_t **dflt )
{
	*dflt = NULL;

	set_menu_auto_mark( dflt );

	*pp = ls_menu_auto_mark;

	return NULL;
}

/***************************************************************
* メニューのリストを設定
* menu_t **dflt : メニューのデフォルト
***************************************************************/

void	set_menu_auto_mark( menu_t **dflt )
{
	long	left_max_len;
	menu_t	*p;
	char	buf[MSG_TTL_AUTO_MARK_MAX_BYTE + 1];
	char	key;
	long	i, k;

	p = ls_menu_auto_mark;
	k = 0;
	key = 'A';

	str_nz_cpy( p[k].path, "/auto mark", MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	p[k].accel_key = '\0';
	p[k].short_key[0] = '\0';
	p[k].msg[0] = '\0';
	p[k].call_back = NULL;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	left_max_len = 1;
	for( i = 0; i < AUTO_MARK_MAX_N; i++ ){
		long	len;

		len = str_len_draw( get_msg_ttl_auto_mark_info( i ) );
		left_max_len = max_l( left_max_len, len );
	}
	if( left_max_len > MSG_TTL_AUTO_MARK_INFO_MAX_LEN )
		left_max_len = MSG_TTL_AUTO_MARK_INFO_MAX_LEN;

	for( i = 0; i < AUTO_MARK_MAX_N; i++ ){
		if( (i % AUTO_MARK_N_PER_PAGE) == 0 ){
			str_nz_cpy( p[k].path, "/auto mark/title",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( p[k].kind, "<Title>",
					MENU_KIND_MAX_LEN );
			p[k].accel_key = '\0';
			p[k].short_key[0] = '\0';
			str_nz_cpy( p[k].msg, MSG_TTL_MENU_AUTO_MARK,
					MENU_MSG_MAX_BYTE );
			p[k].call_back = NULL;
			p[k].arg = NULL;
			p[k].flg = FLG_NULL;
			k++;
		}

		if( i == auto_mark_cur_n )
			*dflt = &(p[k]);

		if( ls_flg_ena_auto_mark[i] ){
			int	len;

			len = get_pading_len( get_msg_ttl_auto_mark_info( i ),
					left_max_len );
			sn_printf( buf, MSG_TTL_AUTO_MARK_MAX_BYTE,
					"%*s%s%s",
					len,
					get_msg_ttl_auto_mark_info( i ),
					STR_TTL_AUTO_MARK_SPLIT_NAME,
					get_msg_ttl_auto_mark_hint( i ) );
		} else {
			int	len;

			len = get_pading_len( MSG_MENU_AUTO_MARK_NULL,
					left_max_len );
			sn_printf( buf, MSG_TTL_AUTO_MARK_MAX_BYTE,
					"%*s%s%s",
					len,
					MSG_MENU_AUTO_MARK_NULL,
					STR_TTL_AUTO_MARK_SPLIT_NAME,
					MSG_MENU_AUTO_MARK_NULL );
		}

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"/auto mark/%ld", i );
		str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		p[k].accel_key = key;
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, buf, MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_exec;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;
		key++;

		if( (i != 0) && ((i % AUTO_MARK_N_PER_PAGE)
				== (AUTO_MARK_N_PER_PAGE - 1)) ){
			str_nz_cpy( p[k].path, "/auto mark/sel edit",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( p[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
			p[k].accel_key = 'Z';
			p[k].short_key[0] = '\0';
			str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_EDIT,
					MENU_MSG_MAX_BYTE );
			p[k].call_back = cb_menu_auto_mark_sel_edit;
			p[k].arg = NULL;
			p[k].flg = FLG_NULL;
			k++;

			str_nz_cpy( p[k].path, "/auto mark/--",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( p[k].kind, "<PageSeparator>",
					MENU_KIND_MAX_LEN );
			p[k].accel_key = '\0';
			p[k].short_key[0] = '\0';
			p[k].n_msg = N_MSG_NULL;
			p[k].msg[0] = '\0';
			p[k].call_back = NULL;
			p[k].arg = NULL;
			p[k].flg = FLG_NULL;
			k++;

			key = 'A';
		}
	}
	p[k].path[0] = '\0';
}

/***************************************************************
* メニューで編集が選択された時に呼ばれる
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_sel_edit( menu_t **pp, menu_t **dflt )
{
	*dflt = NULL;

	set_menu_auto_mark_sel_edit( dflt );

	*pp = ls_menu_auto_mark_sel_edit;

	return NULL;
}

/***************************************************************
* 編集メニューのリストを設定
* menu_t **dflt : メニューのデフォルト
***************************************************************/

void	set_menu_auto_mark_sel_edit( menu_t **dflt )
{
	long	left_max_len;
	menu_t	*p;
	char	buf[MSG_TTL_AUTO_MARK_MAX_BYTE + 1];
	char	key;
	long	i, k;

	p = ls_menu_auto_mark_sel_edit;
	k = 0;
	key = 'A';

	str_nz_cpy( p[k].path, "/sel edit", MENU_PATH_MAX_LEN );
	str_nz_cpy( p[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	p[k].accel_key = '\0';
	p[k].short_key[0] = '\0';
	p[k].msg[0] = '\0';
	p[k].call_back = NULL;
	p[k].arg = NULL;
	p[k].flg = FLG_NULL;
	k++;

	left_max_len = 1;
	for( i = 0; i < AUTO_MARK_MAX_N; i++ ){
		long	len;

		len = str_len_draw( get_msg_ttl_auto_mark_info( i ) );
		left_max_len = max_l( left_max_len, len );
	}
	if( left_max_len > MSG_TTL_AUTO_MARK_INFO_MAX_LEN )
		left_max_len = MSG_TTL_AUTO_MARK_INFO_MAX_LEN;

	for( i = 0; i < AUTO_MARK_MAX_N; i++ ){
		long	kk;

		if( (i != 0) && ((i % AUTO_MARK_N_PER_PAGE) == 0) ){
			str_nz_cpy( p[k].path, "/sel edit/--",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( p[k].kind, "<PageSeparator>",
					MENU_KIND_MAX_LEN );
			p[k].accel_key = '\0';
			p[k].short_key[0] = '\0';
			p[k].n_msg = N_MSG_NULL;
			p[k].msg[0] = '\0';
			p[k].call_back = NULL;
			p[k].arg = NULL;
			p[k].flg = FLG_NULL;
			k++;

			key = 'A';
		}

		if( (i % AUTO_MARK_N_PER_PAGE) == 0 ){
			str_nz_cpy( p[k].path, "/sel edit/title",
					MENU_PATH_MAX_LEN );
			str_nz_cpy( p[k].kind, "<Title>",
					MENU_KIND_MAX_LEN );
			p[k].accel_key = '\0';
			p[k].short_key[0] = '\0';
			str_nz_cpy( p[k].msg,
					MSG_TTL_MENU_AUTO_MARK_SEL_EDIT,
					MENU_MSG_MAX_BYTE );
			p[k].call_back = NULL;
			p[k].arg = NULL;
			p[k].flg = FLG_NULL;
			k++;
		}

		if( i == auto_mark_cur_n )
			*dflt = &(p[k]);

		kk = k;

		if( ls_flg_ena_auto_mark[i] ){
			int	len;

			len = get_pading_len( get_msg_ttl_auto_mark_info( i ),
					left_max_len );
			sn_printf( buf, MSG_TTL_AUTO_MARK_MAX_BYTE,
					"%*s%s%s",
					len,
					get_msg_ttl_auto_mark_info( i ),
					STR_TTL_AUTO_MARK_SPLIT_NAME,
					get_msg_ttl_auto_mark_hint( i ) );
		} else {
			int	len;

			len = get_pading_len( MSG_MENU_AUTO_MARK_NULL,
					left_max_len );
			sn_printf( buf, MSG_TTL_AUTO_MARK_MAX_BYTE,
					"%*s%s%s",
					len,
					MSG_MENU_AUTO_MARK_NULL,
					STR_TTL_AUTO_MARK_SPLIT_NAME,
					MSG_MENU_AUTO_MARK_NULL );
		}

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"/sel edit/%ld", i );
		str_nz_cpy( p[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		p[k].accel_key = key;
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, buf, MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_sel_edit_sel;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;
		key++;

#if	0
		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/exec", p[kk].path );
		str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'X';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_EXEC,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_exec;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;
#endif

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/edit", p[kk].path );
		str_nz_cpy( p[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'E';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_EDIT,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_edit;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/edit name", p[kk].path );
		str_nz_cpy( p[k].kind, "<OpenWinItem>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'N';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_EDIT_NAME,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_edit_name;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/copy", p[kk].path );
		str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'W';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_COPY_L,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_copy_large;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/paste", p[kk].path );
		str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'Y';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_PASTE_L,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_paste_large;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/remove", p[kk].path );
		str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'R';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_REMOVE,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_remove;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/arrange up", p[kk].path );
		str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'U';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_ARRANGE_UP,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_arrange_up;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/arrange down", p[kk].path );
		str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'D';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_ARRANGE_DOWN,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_arrange_down;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/arrange top", p[kk].path );
		str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'T';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_ARRANGE_TOP,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_arrange_top;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;

		sn_printf( p[k].path, MENU_PATH_MAX_LEN,
				"%s/arrange bottom", p[kk].path );
		str_nz_cpy( p[k].kind, "<Item>", MENU_KIND_MAX_LEN );
		p[k].accel_key = 'B';
		p[k].short_key[0] = '\0';
		str_nz_cpy( p[k].msg, MSG_MENU_AUTO_MARK_ARRANGE_BOTTOM,
				MENU_MSG_MAX_BYTE );
		p[k].call_back = cb_menu_auto_mark_arrange_bottom;
		p[k].arg = (void *)i;
		p[k].flg = FLG_NULL;
		k++;
	}
	p[k].path[0] = '\0';
}

/***************************************************************
* メニューでスロットが選択された時に呼ばれる
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_sel_edit_sel( menu_t **pp, menu_t **dflt )
{
	auto_mark_cur_n = (long)((*pp)->arg);

	return NULL;
}

/***************************************************************
* メニューで実行が選択された時に呼ばれる
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_exec( menu_t **pp, menu_t **dflt )
{
	party_t	*pty = get_party();
	long	n;
	long	i;

	n = (long)((*pp)->arg);
	if( !chk_flg_ena_auto_mark( n ) )
		return STR_MENU_CANCEL;

	if( auto_mark_cur_n != n ){
		auto_mark_cur_n = n;

		for( i = 0; i < MBR_MAX_N; i++ ){
			set_auto_mark_cont( pty->mbr[i] );
		}
	}

	for( i = 0; i < MBR_MAX_N; i++ )
		exec_menu_auto_mark( pty->mbr[i] );

	return NULL;
}

/***************************************************************
* 強制的にマークしなおすなら連続マークを解除
* mbr_t *mbr : メンバー
***************************************************************/

void	set_auto_mark_cont( mbr_t *mbr )
{
	auto_mark_t	*p;

	if( mbr == NULL )
		return;

	p = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);
	if( chk_flg( p->flg, FLG_AUTO_MARK_EDIT_PRIORITY ) )
		mbr->flg_chr &= ~(FLG_CHR_AUTO_MARK_CONT);
}

/***************************************************************
* メニューを実行する
* mbr_t *mbr : メンバー
* return : 成功か失敗か
***************************************************************/

bool_t	exec_menu_auto_mark( mbr_t *mbr )
{
	auto_mark_t	*am;
	bool_t	flg_clr;

	if( mbr == NULL )
		return FALSE;
	if( chk_flg_or( mbr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return FALSE;

	am = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);

	/* すでにマークしているか？ */
	if( !chk_flg( am->flg, FLG_AUTO_MARK_EDIT_PRIORITY ) )
		if( mbr->act.kind != ACT_KIND_NULL )
			return FALSE;

	flg_clr = FALSE;
	switch( am->trgt ){
	case AUTO_MARK_TRGT_MNSTR:
		if( !exec_menu_auto_mark_mnstr( mbr ) )
			flg_clr = TRUE;
		break;
	case AUTO_MARK_TRGT_ITEM:
		if( !exec_menu_auto_mark_item( mbr ) )
			flg_clr = TRUE;
		break;
	case AUTO_MARK_TRGT_DOOR:
		if( !exec_menu_auto_mark_door( mbr ) )
			flg_clr = TRUE;
		break;
	case AUTO_MARK_TRGT_TRAP:
		if( !exec_menu_auto_mark_trap( mbr ) )
			flg_clr = TRUE;
		break;
	case AUTO_MARK_TRGT_MBR:
		if( !exec_menu_auto_mark_mbr( mbr ) )
			flg_clr = TRUE;
		break;
	case AUTO_MARK_TRGT_UNCHANGE:
		flg_clr = FALSE;
		break;
	case AUTO_MARK_TRGT_CLEAR:
		flg_clr = TRUE;
		break;
	}

	if( chk_flg( am->flg, FLG_AUTO_MARK_EDIT_CONT ) ){
		mbr->flg_chr |= FLG_CHR_AUTO_MARK_CONT;
	} else {
		mbr->flg_chr &= ~(FLG_CHR_AUTO_MARK_CONT);
	}

	if( flg_clr )
		clr_chr_trgt_act( mbr, TRUE );

	set_key_buf_str_head( am->macro );

	return TRUE;
}

/***************************************************************
* モンスターを対象にメニューを実行する
* mbr_t *mbr : メンバー
* return : 成功か失敗か
***************************************************************/

bool_t	exec_menu_auto_mark_mnstr( mbr_t *mbr )
{
	auto_mark_t	*am;
	mnstr_t	*mnstr;
	dist_t	dist;
	act_kind_t	act_kind;

	if( mbr == NULL )
		return FALSE;

	am = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);

	switch( am->act ){
	case AUTO_MARK_ACT_FIGHT:
		act_kind = ACT_KIND_MNSTR_FIGHT;
		break;
	case AUTO_MARK_ACT_THROW:
		act_kind = ACT_KIND_MNSTR_THROW;
		break;
	case AUTO_MARK_ACT_STEAL:
		act_kind = ACT_KIND_MNSTR_STEAL;
		break;
	case AUTO_MARK_ACT_TAIL:
		act_kind = ACT_KIND_MNSTR_TAIL;
		break;
	case AUTO_MARK_ACT_PICK_UP:
	case AUTO_MARK_ACT_OPEN:
	case AUTO_MARK_ACT_CLOSE:
	case AUTO_MARK_ACT_JAM:
	case AUTO_MARK_ACT_DISARM:
	case AUTO_MARK_ACT_BREAK:
	case AUTO_MARK_ACT_PEEP:
	case AUTO_MARK_ACT_CHK:
	default:
		return FALSE;
	}

	/* モンスターを探す */
	mnstr = NULL;
	switch( am->cond ){
	case AUTO_MARK_COND_NEAREST:
		mnstr = get_mnstr_nearest( mbr->x, mbr->y );
		break;
	case AUTO_MARK_COND_DISPERSE:
		mnstr = get_mnstr_disperse( mbr );
		if( mnstr == NULL )
			mnstr = get_mnstr_randm( mbr->x, mbr->y );
		break;
	case AUTO_MARK_COND_STAGGER:
	case AUTO_MARK_COND_OWN:
	case AUTO_MARK_COND_IDENTIFIED:
	case AUTO_MARK_COND_UN_IDENTIFIED:
		return FALSE;
	case AUTO_MARK_COND_HP_MIN:
		mnstr = get_mnstr_hp_min( mbr->x, mbr->y );
		break;
	case AUTO_MARK_COND_HP_MAX:
		mnstr = get_mnstr_hp_max( mbr->x, mbr->y );
		break;
	case AUTO_MARK_COND_MP_MIN:
		mnstr = get_mnstr_mp_min( mbr->x, mbr->y );
		break;
	case AUTO_MARK_COND_MP_MAX:
		mnstr = get_mnstr_mp_max( mbr->x, mbr->y );
		break;
	}
	if( mnstr == NULL )
		return FALSE;

	/* 間合いをセット */
	switch( am->dist ){
	case AUTO_MARK_DIST_NEAR:
		dist = DIST_NEAR;
		break;
	case AUTO_MARK_DIST_MEDIUM:
		dist = DIST_MEDIUM;
		break;
	case AUTO_MARK_DIST_FAR:
		dist = DIST_FAR;
		break;
	default:
		return FALSE;
	}

	/* アクションをセット */
	set_chr_act( mbr, act_kind, NULL, NULL, 0, 0 );

	/* モンスターをマークする */
	mark_mnstr( mbr, mnstr, dist );

	draw_mbr_stat( mbr );

	set_flg_mbr_find_mnstr( TRUE );
	call_game_sound_play( SOUND_KIND_FIGHT_FIND_MEMBER, 1 );

	return TRUE;
}

/***************************************************************
* アイテムを対象にメニューを実行する
* mbr_t *mbr : メンバー
* return : 成功か失敗か
***************************************************************/

bool_t	exec_menu_auto_mark_item( mbr_t *mbr )
{
	auto_mark_t	*am;
	item_t	*item;
	dist_t	dist;
	act_kind_t	act_kind;

	if( mbr == NULL )
		return FALSE;

	am = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);

	switch( am->act ){
	case AUTO_MARK_ACT_FIGHT:
	case AUTO_MARK_ACT_THROW:
	case AUTO_MARK_ACT_STEAL:
	case AUTO_MARK_ACT_TAIL:
		return FALSE;
	case AUTO_MARK_ACT_PICK_UP:
		act_kind = ACT_KIND_ITEM_PICK_UP;
		break;
	case AUTO_MARK_ACT_OPEN:
		act_kind = ACT_KIND_ITEM_OPEN;
		break;
	case AUTO_MARK_ACT_CLOSE:
	case AUTO_MARK_ACT_JAM:
		return FALSE;
	case AUTO_MARK_ACT_DISARM:
		act_kind = ACT_KIND_ITEM_DISARM;
		break;
	case AUTO_MARK_ACT_BREAK:
		act_kind = ACT_KIND_ITEM_BREAK;
		break;
	case AUTO_MARK_ACT_PEEP:
		return FALSE;
	case AUTO_MARK_ACT_CHK:
		act_kind = ACT_KIND_ITEM_CHK;
		break;
	default:
		return FALSE;
	}

	/* アイテムを探す */
	item = NULL;
	switch( am->cond ){
	case AUTO_MARK_COND_NEAREST:
		item = get_item_nearest( mbr, act_kind, TRUE );
		break;
	case AUTO_MARK_COND_DISPERSE:
		item = get_item_disperse( mbr, act_kind, TRUE );
		if( item == NULL )
			item = get_item_randm( mbr, act_kind, TRUE );
		break;
	case AUTO_MARK_COND_STAGGER:
		return FALSE;
	case AUTO_MARK_COND_OWN:
		item = get_item_own( mbr, act_kind, TRUE );
		break;
	case AUTO_MARK_COND_IDENTIFIED:
		item = get_item_identified( mbr, act_kind, TRUE );
		break;
	case AUTO_MARK_COND_UN_IDENTIFIED:
		item = get_item_un_identified( mbr, act_kind, TRUE );
		break;
	case AUTO_MARK_COND_HP_MIN:
	case AUTO_MARK_COND_HP_MAX:
	case AUTO_MARK_COND_MP_MIN:
	case AUTO_MARK_COND_MP_MAX:
		return FALSE;
	}
	if( item == NULL )
		return FALSE;

	/* 間合いをセット */
	switch( am->dist ){
	case AUTO_MARK_DIST_NEAR:
		dist = DIST_NEAR;
		break;
	case AUTO_MARK_DIST_MEDIUM:
		dist = DIST_MEDIUM;
		break;
	case AUTO_MARK_DIST_FAR:
		dist = DIST_FAR;
		break;
	default:
		return FALSE;
	}

	/* アクションをセット */
	set_chr_act( mbr, act_kind, NULL, NULL, 0, 0 );

	/* アイテムをマークする */
	mark_item( mbr, item, dist );

	draw_mbr_stat( mbr );

	return TRUE;
}

/***************************************************************
* ドアを対象にメニューを実行する
* mbr_t *mbr : メンバー
* return : 成功か失敗か
***************************************************************/

bool_t	exec_menu_auto_mark_door( mbr_t *mbr )
{
	auto_mark_t	*am;
	door_t	*door;
	dist_t	dist;
	act_kind_t	act_kind;

	if( mbr == NULL )
		return FALSE;

	am = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);

	switch( am->act ){
	case AUTO_MARK_ACT_FIGHT:
	case AUTO_MARK_ACT_THROW:
	case AUTO_MARK_ACT_STEAL:
	case AUTO_MARK_ACT_TAIL:
	case AUTO_MARK_ACT_PICK_UP:
		return FALSE;
	case AUTO_MARK_ACT_OPEN:
		act_kind = ACT_KIND_DOOR_OPEN;
		break;
	case AUTO_MARK_ACT_CLOSE:
		act_kind = ACT_KIND_DOOR_CLOSE;
		break;
	case AUTO_MARK_ACT_JAM:
		act_kind = ACT_KIND_DOOR_JAM;
		break;
	case AUTO_MARK_ACT_DISARM:
		act_kind = ACT_KIND_DOOR_DISARM;
		break;
	case AUTO_MARK_ACT_BREAK:
		act_kind = ACT_KIND_DOOR_BREAK;
		break;
	case AUTO_MARK_ACT_PEEP:
		act_kind = ACT_KIND_DOOR_PEEP;
		break;
	case AUTO_MARK_ACT_CHK:
		act_kind = ACT_KIND_DOOR_CHK;
		break;
	default:
		return FALSE;
	}

	/* ドアを探す */
	door = NULL;
	switch( am->cond ){
	case AUTO_MARK_COND_NEAREST:
		door = get_door_nearest( mbr->x, mbr->y, act_kind );
		break;
	case AUTO_MARK_COND_DISPERSE:
		door = get_door_disperse( mbr, act_kind );
		if( door == NULL )
			door = get_door_randm( mbr->x, mbr->y, act_kind );
		break;
	case AUTO_MARK_COND_STAGGER:
	case AUTO_MARK_COND_OWN:
	case AUTO_MARK_COND_IDENTIFIED:
	case AUTO_MARK_COND_UN_IDENTIFIED:
	case AUTO_MARK_COND_HP_MIN:
	case AUTO_MARK_COND_HP_MAX:
	case AUTO_MARK_COND_MP_MIN:
	case AUTO_MARK_COND_MP_MAX:
		return FALSE;
	}
	if( door == NULL )
		return FALSE;

	/* 間合いをセット */
	switch( am->dist ){
	case AUTO_MARK_DIST_NEAR:
		dist = DIST_NEAR;
		break;
	case AUTO_MARK_DIST_MEDIUM:
		dist = DIST_MEDIUM;
		break;
	case AUTO_MARK_DIST_FAR:
		dist = DIST_FAR;
		break;
	default:
		return FALSE;
	}

	/* アクションをセット */
	set_chr_act( mbr, act_kind, NULL, NULL, 0, 0 );

	/* ドアをマークする */
	mark_door( mbr, door, dist );

	draw_mbr_stat( mbr );

	return TRUE;
}

/***************************************************************
* 罠を対象にメニューを実行する
* mbr_t *mbr : メンバー
* return : 成功か失敗か
***************************************************************/

bool_t	exec_menu_auto_mark_trap( mbr_t *mbr )
{
	auto_mark_t	*am;
	trap_t	*trap;
	dist_t	dist;
	act_kind_t	act_kind;

	if( mbr == NULL )
		return FALSE;

	am = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);

	switch( am->act ){
	case AUTO_MARK_ACT_FIGHT:
	case AUTO_MARK_ACT_THROW:
	case AUTO_MARK_ACT_STEAL:
	case AUTO_MARK_ACT_TAIL:
	case AUTO_MARK_ACT_PICK_UP:
	case AUTO_MARK_ACT_OPEN:
	case AUTO_MARK_ACT_CLOSE:
	case AUTO_MARK_ACT_JAM:
		return FALSE;
	case AUTO_MARK_ACT_DISARM:
		act_kind = ACT_KIND_TRAP_DISARM;
		break;
	case AUTO_MARK_ACT_BREAK:
		act_kind = ACT_KIND_TRAP_BREAK;
		break;
	case AUTO_MARK_ACT_PEEP:
		return FALSE;
	case AUTO_MARK_ACT_CHK:
		act_kind = ACT_KIND_TRAP_CHK;
		break;
	default:
		return FALSE;
	}

	/* 罠を探す */
	trap = NULL;
	switch( am->cond ){
	case AUTO_MARK_COND_NEAREST:
		trap = get_trap_nearest( mbr, act_kind );
		break;
	case AUTO_MARK_COND_DISPERSE:
		trap = get_trap_disperse( mbr, act_kind );
		if( trap == NULL )
			trap = get_trap_randm( mbr, act_kind );
		break;
	case AUTO_MARK_COND_STAGGER:
	case AUTO_MARK_COND_OWN:
		return FALSE;
	case AUTO_MARK_COND_IDENTIFIED:
		trap = get_trap_identified( mbr, act_kind );
		break;
	case AUTO_MARK_COND_UN_IDENTIFIED:
		trap = get_trap_un_identified( mbr, act_kind );
		break;
	case AUTO_MARK_COND_HP_MIN:
	case AUTO_MARK_COND_HP_MAX:
	case AUTO_MARK_COND_MP_MIN:
	case AUTO_MARK_COND_MP_MAX:
		return FALSE;
	}
	if( trap == NULL )
		return FALSE;

	/* 間合いをセット */
	switch( am->dist ){
	case AUTO_MARK_DIST_NEAR:
		dist = DIST_NEAR;
		break;
	case AUTO_MARK_DIST_MEDIUM:
		dist = DIST_MEDIUM;
		break;
	case AUTO_MARK_DIST_FAR:
		dist = DIST_FAR;
		break;
	default:
		return FALSE;
	}

	/* アクションをセット */
	set_chr_act( mbr, act_kind, NULL, NULL, 0, 0 );

	/* 罠をマークする */
	mark_trap( mbr, trap, dist );

	draw_mbr_stat( mbr );

	return TRUE;
}

/***************************************************************
* メンバーを対象にメニューを実行する
* mbr_t *mbr : メンバー
* return : 成功か失敗か
***************************************************************/

bool_t	exec_menu_auto_mark_mbr( mbr_t *mbr )
{
	auto_mark_t	*am;
	mbr_t	*p;
	dist_t	dist;
	act_kind_t	act_kind;

	if( mbr == NULL )
		return FALSE;

	am = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);

	/* メンバーを探す */
	p = NULL;
	switch( am->cond ){
	case AUTO_MARK_COND_NEAREST:
		p = get_mbr_nearest( mbr->x, mbr->y );
		break;
	case AUTO_MARK_COND_DISPERSE:
		p = get_mbr_disperse( mbr );
		if( p == NULL )
			p = get_mbr_randm( mbr->x, mbr->y );
		break;
	case AUTO_MARK_COND_STAGGER:
		p = get_mbr_stagger( mbr );
		break;
	case AUTO_MARK_COND_OWN:
	case AUTO_MARK_COND_IDENTIFIED:
	case AUTO_MARK_COND_UN_IDENTIFIED:
		return FALSE;
	case AUTO_MARK_COND_HP_MIN:
		p = get_mbr_hp_min();
		break;
	case AUTO_MARK_COND_HP_MAX:
		p = get_mbr_hp_max();
		break;
	case AUTO_MARK_COND_MP_MIN:
		p = get_mbr_mp_min();
		break;
	case AUTO_MARK_COND_MP_MAX:
		p = get_mbr_mp_max();
		break;
	}
	if( p == NULL )
		return FALSE;

	/* 間合いをセット */
	switch( am->dist ){
	case AUTO_MARK_DIST_NEAR:
		dist = DIST_NEAR;
		break;
	case AUTO_MARK_DIST_MEDIUM:
		dist = DIST_MEDIUM;
		break;
	case AUTO_MARK_DIST_FAR:
		dist = DIST_FAR;
		break;
	default:
		return FALSE;
	}

	switch( am->act ){
	case AUTO_MARK_ACT_FIGHT:
		act_kind = ACT_KIND_MBR_FIGHT;
		break;
	case AUTO_MARK_ACT_THROW:
		act_kind = ACT_KIND_MBR_THROW;
		break;
	case AUTO_MARK_ACT_STEAL:
		act_kind = ACT_KIND_MBR_STEAL;
		break;
	case AUTO_MARK_ACT_TAIL:
		act_kind = ACT_KIND_MBR_TAIL;
		break;
	case AUTO_MARK_ACT_PICK_UP:
	case AUTO_MARK_ACT_OPEN:
	case AUTO_MARK_ACT_CLOSE:
	case AUTO_MARK_ACT_JAM:
	case AUTO_MARK_ACT_DISARM:
	case AUTO_MARK_ACT_BREAK:
	case AUTO_MARK_ACT_PEEP:
	case AUTO_MARK_ACT_CHK:
		return FALSE;
	default:
		return FALSE;
	}

	/* アクションをセット */
	set_chr_act( mbr, act_kind, NULL, NULL, 0, 0 );

	/* メンバーをマークする */
	mark_mbr( mbr, p, dist );

	draw_mbr_stat( mbr );

	return TRUE;
}

/***************************************************************
* メニューで編集が選択された時に呼ばれる
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_edit( menu_t **pp, menu_t **dflt )
{
	char	*str_goto;

	auto_mark_cur_n = (long)((*pp)->arg);
	ls_flg_ena_auto_mark[auto_mark_cur_n] = TRUE;
	set_menu_auto_mark( dflt );
	set_menu_auto_mark_sel_edit( dflt );

	while( 1 ){
		str_goto = exec_menu_sel_mbr(
				&g_sel_mbr, NULL, TRUE, FALSE );
		if( str_goto != NULL )
			return str_goto;

		while( 1 ){
			str_goto = exec_menu(
					ls_menu_auto_mark_edit,
					NULL, NULL );
			set_menu_auto_mark( dflt );
			set_menu_auto_mark_sel_edit( dflt );

			if( str_goto == NULL )
				continue;
			if( strcmp( str_goto, STR_MENU_ERR ) == 0 )
				return STR_MENU_ERR;
			if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
				break;
		}
	}

	return STR_MENU_ERR;
}

/***************************************************************
* 編集メニューを初期化
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_edit_init(
	menu_t **pp, menu_t **dflt
)
{
	auto_mark_t	*am;
	menu_t	*p;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	/* タイトル */
	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_AUTO_MARK_EDIT,
			get_msg_ttl_auto_mark_info( auto_mark_cur_n ),
			g_sel_mbr->name );

	/* 配置 */
	p = srch_menu( *pp, "position" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_MENU_AUTO_MARK_EDIT_POSITION,
			get_msg_menu_auto_mark_edit_position( g_sel_mbr ) );

	/* 対象 */
	p = srch_menu( *pp, "target" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_MENU_AUTO_MARK_EDIT_TRGT,
			get_msg_menu_auto_mark_edit_trgt( g_sel_mbr ) );

	/* 間合い */
	p = srch_menu( *pp, "dist" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_MENU_AUTO_MARK_EDIT_DIST,
			get_msg_menu_auto_mark_edit_dist( g_sel_mbr ) );

	/* 行動 */
	p = srch_menu( *pp, "action" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_MENU_AUTO_MARK_EDIT_ACT,
			get_msg_menu_auto_mark_edit_act( g_sel_mbr ) );

	/* 条件 */
	p = srch_menu( *pp, "condition" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_MENU_AUTO_MARK_EDIT_COND,
			get_msg_menu_auto_mark_edit_cond( g_sel_mbr ) );

	/* アイテム種別 */
	if( am->trgt == AUTO_MARK_TRGT_ITEM ){
		clr_flg_menu( *pp, "appoint item", FLG_MENU_HIDDEN );
	} else {
		set_flg_menu( *pp, "appoint item", FLG_MENU_HIDDEN );
	}

	/* マクロ */

	/* 連続マーク */
	if( chk_flg( am->flg, FLG_AUTO_MARK_EDIT_CONT ) ){
		set_chk_on_menu( *pp, "continue" );
	} else {
		set_chk_off_menu( *pp, "continue" );
	}

	/* 現在の設定より優先 */
	if( chk_flg( am->flg, FLG_AUTO_MARK_EDIT_PRIORITY ) ){
		set_chk_on_menu( *pp, "priority" );
	} else {
		set_chk_off_menu( *pp, "priority" );
	}

	return NULL;
}

/***************************************************************
* 編集メニューの配置を選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_position( menu_t **pp, menu_t **dflt )
{
	exec_menu_position( g_sel_mbr );

	return NULL;
}

/***************************************************************
* 編集メニューの対象を初期化
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_trgt_init(
	menu_t **pp, menu_t **dflt
)
{
	menu_t	*p;
	char	*s;

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_AUTO_MARK_TRGT,
			get_msg_ttl_auto_mark_info( auto_mark_cur_n ),
			g_sel_mbr->name );

	s = NULL;
	switch( ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind].trgt ){
	case AUTO_MARK_TRGT_MNSTR:
		s = "monster";
		break;
	case AUTO_MARK_TRGT_ITEM:
		s = "item";
		break;
	case AUTO_MARK_TRGT_DOOR:
		s = "door";
		break;
	case AUTO_MARK_TRGT_TRAP:
		s = "trap";
		break;
	case AUTO_MARK_TRGT_MBR:
		s = "member";
		break;
	case AUTO_MARK_TRGT_UNCHANGE:
		s = "unchange";
		break;
	case AUTO_MARK_TRGT_CLEAR:
		s = "clear";
		break;
	}

	*dflt = srch_menu( *pp, s );

	return NULL;
}

/***************************************************************
* 編集メニューの対象を選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_trgt( menu_t **pp, menu_t **dflt )
{
	auto_mark_t	*am;
	auto_mark_trgt_t	trgt;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return NULL;
	}

	trgt = (auto_mark_trgt_t)(long)((*pp)->arg);
	am->trgt = trgt;

	switch( trgt ){
	case AUTO_MARK_TRGT_MNSTR:
		am->act = AUTO_MARK_ACT_FIGHT;
		break;
	case AUTO_MARK_TRGT_ITEM:
		am->act = AUTO_MARK_ACT_PICK_UP;
		break;
	case AUTO_MARK_TRGT_DOOR:
		am->act = AUTO_MARK_ACT_OPEN;
		break;
	case AUTO_MARK_TRGT_TRAP:
		am->act = AUTO_MARK_ACT_DISARM;
		break;
	case AUTO_MARK_TRGT_MBR:
		am->act = AUTO_MARK_ACT_TAIL;
		break;
	case AUTO_MARK_TRGT_UNCHANGE:
	case AUTO_MARK_TRGT_CLEAR:
		break;
	}

	return NULL;
}

/***************************************************************
* 編集メニューの間合いを初期化
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_dist_init(
	menu_t **pp, menu_t **dflt
)
{
	auto_mark_t	*am;
	menu_t	*p;
	char	*s;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->trgt == AUTO_MARK_TRGT_UNCHANGE )
		return STR_MENU_CANCEL;
	if( am->trgt == AUTO_MARK_TRGT_CLEAR )
		return STR_MENU_CANCEL;

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_AUTO_MARK_DIST,
			get_msg_ttl_auto_mark_info( auto_mark_cur_n ),
			g_sel_mbr->name );

	s = NULL;
	switch( am->dist ){
	case AUTO_MARK_DIST_NEAR:
		s = "near";
		break;
	case AUTO_MARK_DIST_MEDIUM:
		s = "medium";
		break;
	case AUTO_MARK_DIST_FAR:
		s = "far";
		break;
	}

	*dflt = srch_menu( *pp, s );

	return NULL;
}

/***************************************************************
* 編集メニューの間合いを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_dist( menu_t **pp, menu_t **dflt )
{
	auto_mark_t	*am;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return NULL;
	}

	am->dist = (auto_mark_dist_t)(long)((*pp)->arg);

	return NULL;
}

/***************************************************************
* 編集メニューの行動を初期化
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_act_init( menu_t **pp, menu_t **dflt )
{
	auto_mark_t	*am;
	menu_t	*p;
	char	*s;

	clr_flg_menu( *pp, NULL, FLG_MENU_ALL );

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->trgt == AUTO_MARK_TRGT_UNCHANGE )
		return STR_MENU_CANCEL;
	if( am->trgt == AUTO_MARK_TRGT_CLEAR )
		return STR_MENU_CANCEL;

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_AUTO_MARK_ACT,
			get_msg_ttl_auto_mark_info( auto_mark_cur_n ),
			g_sel_mbr->name );

	s = NULL;
	switch( am->act ){
	case AUTO_MARK_ACT_FIGHT:
		s = "fight";
		break;
	case AUTO_MARK_ACT_THROW:
		s = "throw";
		break;
	case AUTO_MARK_ACT_STEAL:
		s = "steal";
		break;
	case AUTO_MARK_ACT_TAIL:
		s = "tail";
		break;
	case AUTO_MARK_ACT_PICK_UP:
		s = "pick up";
		break;
	case AUTO_MARK_ACT_OPEN:
		s = "open";
		break;
	case AUTO_MARK_ACT_CLOSE:
		s = "close";
		break;
	case AUTO_MARK_ACT_JAM:
		s = "jam";
		break;
	case AUTO_MARK_ACT_DISARM:
		s = "disarm";
		break;
	case AUTO_MARK_ACT_BREAK:
		s = "break";
		break;
	case AUTO_MARK_ACT_PEEP:
		s = "peep";
		break;
	case AUTO_MARK_ACT_CHK:
		s = "check";
		break;
	}

	*dflt = srch_menu( *pp, s );

	/* 対象に応じてメニュー項目の無効化 */

	set_flg_menu( *pp, "fight", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "throw", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "steal", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "tail", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "pick up", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "open", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "close", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "jam", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "disarm", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "break", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "peep", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "search", FLG_MENU_HIDDEN );

	switch( am->trgt ){
	case AUTO_MARK_TRGT_MNSTR:
		clr_flg_menu( *pp, "fight", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "throw", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "steal", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "tail", FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_ITEM:
		clr_flg_menu( *pp, "pick up", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "open", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "disarm", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "break", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "search", FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_DOOR:
		clr_flg_menu( *pp, "open", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "close", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "jam", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "disarm", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "break", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "peep", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "search", FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_TRAP:
		clr_flg_menu( *pp, "disarm", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "break", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "search", FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_MBR:
		clr_flg_menu( *pp, "fight", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "throw", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "steal", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "tail", FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_UNCHANGE:
	case AUTO_MARK_TRGT_CLEAR:
		return STR_MENU_CANCEL;
	}

	if( chk_flg( (*dflt)->flg, FLG_MENU_HIDDEN ) )
		*dflt = NULL;

	return NULL;
}

/***************************************************************
* 編集メニューの行動を選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_act( menu_t **pp, menu_t **dflt )
{
	auto_mark_t	*am;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return NULL;
	}

	am->act = (auto_mark_act_t)(long)((*pp)->arg);

	return NULL;
}

/***************************************************************
* 編集メニューの条件を初期化
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_cond_init(
	menu_t **pp, menu_t **dflt
)
{
	auto_mark_t	*am;
	char	*s;
	menu_t	*p;

	clr_flg_menu( *pp, NULL, FLG_MENU_ALL );

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->trgt == AUTO_MARK_TRGT_UNCHANGE )
		return STR_MENU_CANCEL;
	if( am->trgt == AUTO_MARK_TRGT_CLEAR )
		return STR_MENU_CANCEL;

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_AUTO_MARK_COND,
			get_msg_ttl_auto_mark_info( auto_mark_cur_n ),
			g_sel_mbr->name );

	/* デフォルトのカーソル位置設定 */

	s = NULL;
	switch( am->cond ){
	case AUTO_MARK_COND_NEAREST:
		s = "nearest";
		break;
	case AUTO_MARK_COND_DISPERSE:
		s = "disperse";
		break;
	case AUTO_MARK_COND_STAGGER:
		s = "stagger";
		break;
	case AUTO_MARK_COND_OWN:
		s = "own";
		break;
	case AUTO_MARK_COND_IDENTIFIED:
		s = "identified";
		break;
	case AUTO_MARK_COND_UN_IDENTIFIED:
		s = "unidentified";
		break;
	case AUTO_MARK_COND_HP_MIN:
		s = "hp min";
		break;
	case AUTO_MARK_COND_HP_MAX:
		s = "hp max";
		break;
	case AUTO_MARK_COND_MP_MIN:
		s = "mp min";
		break;
	case AUTO_MARK_COND_MP_MAX:
		s = "mp max";
		break;
	}
	*dflt = srch_menu( *pp, s );

	/* 対象に応じてメニュー項目の無効化 */

	set_flg_menu( *pp, "nearest", FLG_MENU_HIDDEN );
	set_flg_menu( *pp,"disperse",  FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "stagger", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "own", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "identified", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "unidentified", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "hp min", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "hp max", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "mp min", FLG_MENU_HIDDEN );
	set_flg_menu( *pp, "mp max", FLG_MENU_HIDDEN );

	switch( am->trgt ){
	case AUTO_MARK_TRGT_DOOR:
		clr_flg_menu( *pp, "nearest", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp,"disperse",  FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_TRAP:
		clr_flg_menu( *pp, "nearest", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp,"disperse",  FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "identified", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "unidentified", FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_ITEM:
		clr_flg_menu( *pp, "nearest", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp,"disperse",  FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "own", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "identified", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "unidentified", FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_MNSTR:
		clr_flg_menu( *pp, "nearest", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp,"disperse",  FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "hp min", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "hp max", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "mp min", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "mp max", FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_MBR:
		clr_flg_menu( *pp, "nearest", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp,"disperse",  FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "stagger", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "hp min", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "hp max", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "mp min", FLG_MENU_HIDDEN );
		clr_flg_menu( *pp, "mp max", FLG_MENU_HIDDEN );
		break;
	case AUTO_MARK_TRGT_UNCHANGE:
	case AUTO_MARK_TRGT_CLEAR:
		return STR_MENU_ERR;
	}

	if( (*dflt != NULL) && chk_flg( (*dflt)->flg, FLG_MENU_HIDDEN ) )
		*dflt = NULL;

	p = srch_menu( *pp, "title" );
	if( p == NULL )
		return STR_MENU_ERR;
	sn_printf( p->msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_AUTO_MARK_COND,
			get_msg_ttl_auto_mark_info( auto_mark_cur_n ),
			g_sel_mbr->name );

	return NULL;
}

/***************************************************************
* 編集メニューの条件を選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_cond( menu_t **pp, menu_t **dflt )
{
	auto_mark_t	*am;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return NULL;
	}

	am->cond = (auto_mark_cond_t)(long)((*pp)->arg);

	return NULL;
}

/***************************************************************
* 編集メニューのアイテム種類別を選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_appoint_item(
	menu_t **pp, menu_t **dflt
)
{
	menu_t	*ls;
	long	k;
	auto_mark_appoint_item_t	*apo;
	long	i;

	if( ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind].trgt
			!= AUTO_MARK_TRGT_ITEM ){
		return STR_MENU_CANCEL;
	}

	ls = ls_menu_appoint_item;
	k = 0;

	str_nz_cpy( ls[k].path, "/appoint item",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/appoint item/title",
			MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>",
			MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	sn_printf( ls[k].msg, MENU_MSG_MAX_BYTE,
			MSG_TTL_MENU_AUTO_MARK_APPOINT_ITEM_MJR,
			get_msg_ttl_auto_mark_info( auto_mark_cur_n ),
			g_sel_mbr->name );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	apo = get_auto_mark_appoint_item( g_sel_mbr );
	if( apo == NULL )
		return STR_MENU_ERR;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		char	*ret;

		if( apo->mjr == FACE_MJR_NULL )
			break;

		ret = set_menu_auto_mark_appoint_item(
				ls, &k, (char)('A' + i), &apo );
		if( ret != NULL )
			return ret;
	}
	ls[k].path[0] = '\0';

	*pp = ls;
	*dflt = NULL;

	return NULL;
}

/***************************************************************
* 編集メニューのアイテム種類別を設定
* menu_t *ls : メニュー
* long *k : 設定中のメニュー項目番号
* char mjr_key : 選択キー
* auto_mark_appoint_item_t **apo : アイテム種類別のデータ
* return : メニューの移動先
***************************************************************/

char	*set_menu_auto_mark_appoint_item(
	menu_t *ls, long *k, char mjr_key,
	auto_mark_appoint_item_t **apo
)
{
	char	mjr;
	char	mnr_key;

	mjr = (*apo)->mjr;

	sn_printf( ls[*k].path, MENU_PATH_MAX_LEN,
			"/appoint item/%c", mjr );
	str_nz_cpy( ls[*k].kind, "<Branch>",
			MENU_KIND_MAX_LEN );
	ls[*k].accel_key = mjr_key;
	ls[*k].short_key[0] = '\0';
	ls[*k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[*k].msg, get_item_mjr_name( mjr ),
			MENU_MSG_MAX_BYTE );
	ls[*k].call_back = cb_menu_auto_mark_appoint_item_init;
	ls[*k].arg = (void *)(*apo);
	ls[*k].flg = FLG_NULL;
	(*k)++;

	mnr_key = 'A';
	for( ; (*apo)->mjr != FACE_MJR_NULL; (*apo)++ ){
		char	*name;

		if( (*apo)->mjr != mjr )
			break;

		name = get_item_mnr_name( mjr, (*apo)->mnr );
		if( strcmp( name, MSG_ITEM_MNR_NAME_ERR ) == 0 )
			continue;
		if( strcmp( name, MSG_NULL ) == 0 )
			continue;

		sn_printf( ls[*k].path, MENU_PATH_MAX_LEN,
				"/appoint item/%c/%c",
				(*apo)->mjr, (*apo)->mnr );
		str_nz_cpy( ls[*k].kind, "<CheckItem>",
				MENU_KIND_MAX_LEN );
		ls[*k].accel_key = mnr_key;
		ls[*k].short_key[0] = '\0';
		ls[*k].n_msg = N_MSG_NULL;
		str_nz_cpy( ls[*k].msg, name, MENU_MSG_MAX_BYTE );
		ls[*k].call_back = cb_menu_auto_mark_appoint_item_mnr;
		ls[*k].arg = (void *)(*apo);
		ls[*k].flg = FLG_NULL;
		(*k)++;

		mnr_key++;
	}

	return NULL;
}

/***************************************************************
* 編集メニューのアイテム種類別を初期化
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_appoint_item_init(
	menu_t **pp, menu_t **dflt
)
{
	auto_mark_appoint_item_t	*apo;
	char	mjr;
	char	sub_path[MENU_PATH_MAX_LEN + 1];

	apo = (auto_mark_appoint_item_t *)((*pp)->arg);
	mjr = apo->mjr;

	for( ; apo->mjr != FACE_MJR_NULL; apo++ ){
		if( apo->mjr != mjr )
			break;

		sn_printf( sub_path, MENU_PATH_MAX_LEN,
				"%c", apo->mnr );
		if( apo->flg_ena )
			set_chk_on_menu( *pp, sub_path );
		else
			set_chk_off_menu( *pp, sub_path );
	}

	return NULL;
}

/***************************************************************
* 編集メニューのアイテム種類別の詳細を選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_appoint_item_mnr(
	menu_t **pp, menu_t **dflt
)
{
	auto_mark_appoint_item_t	*apo;

	if( ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind].dflt
			!= DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return STR_MENU_CANCEL;
	}

	apo = (auto_mark_appoint_item_t *)((*pp)->arg);
	apo->flg_ena = !apo->flg_ena;

	return STR_MENU_CANCEL;
}

/***************************************************************
* 編集メニューのマクロを設定
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_edit_macro_bind( menu_t **pp, menu_t **dflt )
{
	auto_mark_t	*am;
	char	*cmd;
	static char	msg_cmd[WIN_MSG_DRAW_WIDTH + 1];
	static char	buf_cmd[MACRO_MAX_LEN + 1];
	long	x, y;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return STR_MENU_CANCEL;
	}

	/* 設定前のマクロを表示 */

	cmd = am->macro;
	print_msg( FLG_NULL, MSG_GETS_AUTO_MARK_EDIT_MACRO_TTL, cmd );

	/* プロンプトを表示 */

	sn_printf( msg_cmd, WIN_MSG_DRAW_WIDTH,
			MSG_GETS_AUTO_MARK_EDIT_MACRO_CMD,
			MACRO_MAX_LEN );
	print_msg( FLG_NULL, msg_cmd );

	/* マクロをユーザから入力 */

	x = str_len_draw( msg_cmd );
	y = get_screen_row() - 1;
	str_nz_cpy( buf_cmd, cmd, MACRO_MAX_LEN );

	if( game_gets( x, y, msg_cmd, buf_cmd, MACRO_MAX_LEN, FALSE ) ){
		long	len;

		/* 末尾の改行を取り除く */

		len = str_len_std( buf_cmd );
		if( len >= 1 )
			if( buf_cmd[len - 1] == '\n' )
				buf_cmd[len - 1] = '\0';

		/* 入力が無いならキャンセル */

		if( buf_cmd[0] == '\0' )
			return STR_MENU_CANCEL;
	} else {
		/* エラーならキャンセル */
		return STR_MENU_CANCEL;
	}

	/* マクロを設定 */

	str_nz_cpy( cmd, buf_cmd, MACRO_MAX_LEN );

	print_msg( FLG_NULL, MSG_MENU_AUTO_MARK_EDIT_MACRO_DONE, cmd );

	return STR_MENU_CANCEL;
}

/***************************************************************
* 編集メニューのマクロを設定
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_edit_macro_reg_macro(
	menu_t **pp, menu_t **dflt
)
{
	auto_mark_t	*am;
	char	*cmd, *reg_cmd;
	char	*msg;
	ask_t	ask;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return STR_MENU_CANCEL;
	}

	/* 設定前のマクロを表示 */

	cmd = am->macro;
	print_msg( FLG_NULL, MSG_GETS_AUTO_MARK_EDIT_MACRO_TTL, cmd );

	/* 確認する */

	msg = MSG_TTL_MENU_AUTO_MARK_EDIT_MACRO_REG_MACRO;

	ask = exec_menu_ask( msg, ASK_NO, TRUE );
	if( ask == ASK_ERR )
		return STR_MENU_ERR;
	if( ask != ASK_YES )
		return STR_MENU_CANCEL;

	/* マクロを設定 */

	reg_cmd = get_reg_macro();
	if( reg_cmd == NULL )
		return STR_MENU_CANCEL;

	str_nz_cpy( cmd, reg_cmd, MACRO_MAX_LEN );

	print_msg( FLG_NULL, MSG_MENU_AUTO_MARK_EDIT_MACRO_DONE, cmd );

	return STR_MENU_CANCEL;
}

/***************************************************************
* 編集メニューの連続マークを設定
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_cont( menu_t **pp, menu_t **dflt )
{
	auto_mark_t	*am;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return STR_MENU_CANCEL;
	}

	am->flg ^= FLG_AUTO_MARK_EDIT_CONT;

	return STR_MENU_CANCEL;
}

/***************************************************************
* 編集メニューの優先を設定
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_priority( menu_t **pp, menu_t **dflt )
{
	auto_mark_t	*am;

	am = &(ls_auto_mark[g_sel_mbr->ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return STR_MENU_CANCEL;
	}

	am->flg ^= FLG_AUTO_MARK_EDIT_PRIORITY;

	return STR_MENU_CANCEL;
}

/***************************************************************
* 大分類コピー・メニューを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_copy_large( menu_t **pp, menu_t **dflt )
{
	long	n;
	long	i, k;

	n = (long)((*pp)->arg);

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			clip_board_large[i][k] = ls_auto_mark[i][n][k];

		for( k = 0; k < AUTO_MARK_APPOINT_ITEM_MAX_N; k++ ){
			clip_board_large_item[i][k]
					= auto_mark_appoint_item[i][n][k];
		}

		str_nz_cpy( clip_board_ttl,
				msg_ttl_auto_mark[n],
				MSG_TTL_AUTO_MARK_MAX_BYTE );
	}

	print_msg( FLG_NULL, MSG_MENU_AUTO_MARK_DONE_COPY );

	return STR_MENU_CANCEL;
}

/***************************************************************
* 大分類ペースト・メニューを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_paste_large( menu_t **pp, menu_t **dflt )
{
	long	n;
	long	i, k;

	n = (long)((*pp)->arg);

	if( ls_auto_mark[0][n][0].dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return STR_MENU_CANCEL;
	}

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
			ls_auto_mark[i][n][k] = clip_board_large[i][k];
			ls_auto_mark[i][n][k].dflt = DFLT_AUTO_MARK_NULL;
		}

		for( k = 0; k < AUTO_MARK_APPOINT_ITEM_MAX_N; k++ ){
			auto_mark_appoint_item[i][n][k]
					= clip_board_large_item[i][k];
		}

		str_nz_cpy( msg_ttl_auto_mark[n],
				clip_board_ttl,
				MSG_TTL_AUTO_MARK_MAX_BYTE );
	}
	ls_flg_ena_auto_mark[n] = TRUE;

	set_menu_auto_mark( dflt );
	set_menu_auto_mark_sel_edit( dflt );

	print_msg( FLG_NULL, MSG_MENU_AUTO_MARK_DONE_PASTE );

	return STR_MENU_CANCEL;
}

/***************************************************************
* 小分類コピー・メニューを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_copy_small( menu_t **pp, menu_t **dflt )
{
	long	k;

	clip_board_small = ls_auto_mark[g_sel_mbr->ls_mbr_n]
			[auto_mark_cur_n][g_sel_mbr->position_kind];

	for( k = 0; k < AUTO_MARK_APPOINT_ITEM_MAX_N; k++ ){
		clip_board_small_item[k]
				= auto_mark_appoint_item
				[g_sel_mbr->ls_mbr_n][auto_mark_cur_n][k];
	}

	print_msg( FLG_NULL, MSG_MENU_AUTO_MARK_DONE_COPY );

	return STR_MENU_CANCEL;
}

/***************************************************************
* 小分類ペースト・メニューを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_paste_small( menu_t **pp, menu_t **dflt )
{
	auto_mark_t	*am;
	long	ls_mbr_n;
	long	k;

	ls_mbr_n = g_sel_mbr->ls_mbr_n;
	am = &(ls_auto_mark[ls_mbr_n][auto_mark_cur_n]
			[g_sel_mbr->position_kind]);

	if( am->dflt != DFLT_AUTO_MARK_NULL ){
		print_msg( FLG_MSG_ERR, MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
		return STR_MENU_CANCEL;
	}

	*am = clip_board_small;
	am->dflt = DFLT_AUTO_MARK_NULL;

	for( k = 0; k < AUTO_MARK_APPOINT_ITEM_MAX_N; k++ ){
		auto_mark_appoint_item[ls_mbr_n]
				[auto_mark_cur_n][k]
				= clip_board_small_item[k];
	}

	ls_flg_ena_auto_mark[auto_mark_cur_n] = TRUE;

	set_menu_auto_mark( dflt );
	set_menu_auto_mark_sel_edit( dflt );

	print_msg( FLG_NULL, MSG_MENU_AUTO_MARK_DONE_PASTE );

	return "/edit";
}

/***************************************************************
* メニューで名前の編集が選択された時に呼ばれる
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_edit_name( menu_t **pp, menu_t **dflt )
{
	long	n;
	static char	info[MSG_TTL_AUTO_MARK_INFO_MAX_BYTE + 1];
	static char	hint[MSG_TTL_AUTO_MARK_HINT_MAX_BYTE + 1];

	n = (long)((*pp)->arg);

	str_nz_cpy( info, get_msg_ttl_auto_mark_info( n ),
			MSG_TTL_AUTO_MARK_INFO_MAX_BYTE );
	str_nz_cpy( hint, get_msg_ttl_auto_mark_hint( n ),
			MSG_TTL_AUTO_MARK_HINT_MAX_BYTE );

	wipe_all();
	gets_auto_mark_info( info );
	gets_auto_mark_hint( hint );
	redraw_all();

	msg_ttl_auto_mark[n][0] = '\0';
	str_max_n_cat( msg_ttl_auto_mark[n],
			info,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	str_max_n_cat( msg_ttl_auto_mark[n],
			STR_TTL_AUTO_MARK_SPLIT_CODE,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	str_max_n_cat( msg_ttl_auto_mark[n],
			hint,
			MSG_TTL_AUTO_MARK_MAX_BYTE );

	set_menu_auto_mark( dflt );
	set_menu_auto_mark_sel_edit( dflt );

	return "/auto mark/sel edit";
}

/***************************************************************
* 削除メニューを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_remove( menu_t **pp, menu_t **dflt )
{
	ask_t	ask;
	long	n;
	long	i, k;

	n = (long)((*pp)->arg);

	/* デフォルトは削除できない */

	if( ls_auto_mark[0][n][0].dflt != DFLT_AUTO_MARK_NULL ){
		/* ただし、ダブっている時は出来る */

		if( !chk_dup_dflt_auto_mark( ls_auto_mark[0][n][0].dflt ) ){
			print_msg( FLG_MSG_ERR,
					MSG_MENU_AUTO_MARK_CAN_NOT_EDIT );
			return STR_MENU_CANCEL;
		}
	}

	ask = exec_menu_ask( MSG_TTL_MENU_AUTO_MARK_ASK_REMOVE,
			ASK_NO, TRUE );
	if( ask == ASK_ERR )
		return STR_MENU_ERR;
	if( ask != ASK_YES )
		return STR_MENU_CANCEL;

	/* 削除 */

	ls_flg_ena_auto_mark[n] = FALSE;
	for( i = 0; i < LS_MBR_MAX_N; i++ )
		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			ls_auto_mark[i][n][k].dflt = DFLT_AUTO_MARK_NULL;

	set_menu_auto_mark( dflt );
	set_menu_auto_mark_sel_edit( dflt );
	print_msg( FLG_NULL, MSG_MENU_AUTO_MARK_DONE_REMOVE );

	return STR_MENU_CANCEL;
}

/***************************************************************
* 1 つ上へ並べ換えメニューを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_arrange_up( menu_t **pp, menu_t **dflt )
{
	char	*ret;

	ret = menu_auto_mark_arrange_1( (long)((*pp)->arg), -1 );

	set_menu_auto_mark( dflt );
	set_menu_auto_mark_sel_edit( dflt );

	return ret;
}

/***************************************************************
* 1 つ下へ並べ換えメニューを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_arrange_down( menu_t **pp, menu_t **dflt )
{
	char	*ret;

	ret = menu_auto_mark_arrange_1( (long)((*pp)->arg), +1 );

	set_menu_auto_mark( dflt );
	set_menu_auto_mark_sel_edit( dflt );

	return ret;
}

/***************************************************************
* 先頭へ並べ換えメニューを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_arrange_top( menu_t **pp, menu_t **dflt )
{
	char	*ret;

	ret = menu_auto_mark_arrange( (long)((*pp)->arg), -1 );

	set_menu_auto_mark( dflt );
	set_menu_auto_mark_sel_edit( dflt );

	return ret;
}

/***************************************************************
* 末尾へ並べ換えメニューを選択した時
* menu_t **pp : メニュー
* menu_t **dflt : メニューのデフォルト
* return : メニューの移動先
***************************************************************/

char	*cb_menu_auto_mark_arrange_bottom( menu_t **pp, menu_t **dflt )
{
	char	*ret;

	ret = menu_auto_mark_arrange( (long)((*pp)->arg), +1 );

	set_menu_auto_mark( dflt );
	set_menu_auto_mark_sel_edit( dflt );

	return ret;
}

/***************************************************************
* メニューの並べ換え (1 つ分)
* long n : 開始位置
* long d : 先頭(-1)/末尾(+1)
* return : メニューの移動先
***************************************************************/

char	*menu_auto_mark_arrange_1( long n, long d )
{
	if( !arrange_auto_mark_1( n, d ) )
		return STR_MENU_ERR;

	if( d <= -1 ){
		print_msg( FLG_NULL,
				MSG_MENU_AUTO_MARK_DONE_ARRANGE_UP );
	} else {
		print_msg( FLG_NULL,
				MSG_MENU_AUTO_MARK_DONE_ARRANGE_DOWN );
	}

	return "/auto mark/sel edit";
}

/***************************************************************
* メニューの並べ換え
* long n : 開始位置
* long d : 先頭(-1)/末尾(+1)
* return : メニューの移動先
***************************************************************/

char	*menu_auto_mark_arrange( long n, long d )
{
	if( !arrange_auto_mark( n, d ) )
		return STR_MENU_ERR;

	if( d <= -1 ){
		print_msg( FLG_NULL,
				MSG_MENU_AUTO_MARK_DONE_ARRANGE_TOP );
	} else {
		print_msg( FLG_NULL,
				MSG_MENU_AUTO_MARK_DONE_ARRANGE_BOTTOM );
	}

	return "/auto mark/sel edit";
}

/***************************************************************
* メニューの並べ換え (1 つ分)
* long n : 開始位置
* long d : 先頭(-1)/末尾(+1)
* return : 成功したか?
***************************************************************/

bool_t	arrange_auto_mark_1( long n, long d )
{
	long	i, k;
	bool_t	flg;
	auto_mark_t	am[POSITION_KIND_MAX_N];
	auto_mark_appoint_item_t	item[AUTO_MARK_APPOINT_ITEM_MAX_N];
	const long	max_item = AUTO_MARK_APPOINT_ITEM_MAX_N;
	char	buf[MSG_TTL_AUTO_MARK_MAX_BYTE + 1];

	if( d == 0 )
		return FALSE;
	if( (n + d) < 0 )
		return FALSE;
	if( (n + d) >= AUTO_MARK_MAX_N )
		return FALSE;

	/**/

	flg = ls_flg_ena_auto_mark[n];
	ls_flg_ena_auto_mark[n] = ls_flg_ena_auto_mark[n + d];
	ls_flg_ena_auto_mark[n + d] = flg;

	/**/

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			am[k] = ls_auto_mark[i][n][k];
		for( k = 0; k < max_item; k++ ){
			item[k] = auto_mark_appoint_item[i][n][k];
		}

		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			ls_auto_mark[i][n][k] = ls_auto_mark[i][n + d][k];
		for( k = 0; k < max_item; k++ ){
			auto_mark_appoint_item[i][n][k]
					= auto_mark_appoint_item
					[i][n + d][k];
		}

		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			ls_auto_mark[i][n + d][k] = am[k];
		for( k = 0; k < max_item; k++ ){
			auto_mark_appoint_item[i][n + d][k] = item[k];
		}
	}

	/**/

	str_nz_cpy( buf, get_msg_ttl_auto_mark_code( n ),
			MSG_TTL_AUTO_MARK_MAX_BYTE );

	str_nz_cpy( get_msg_ttl_auto_mark_code( n ),
			get_msg_ttl_auto_mark_code( n + d ),
			MSG_TTL_AUTO_MARK_MAX_BYTE );

	str_nz_cpy( get_msg_ttl_auto_mark_code( n + d ), buf,
			MSG_TTL_AUTO_MARK_MAX_BYTE );

	/**/

	auto_mark_cur_n = n + d;

	return TRUE;
}

/***************************************************************
* メニューの並べ換え
* long n : 開始位置
* long d : 先頭(-1)/末尾(+1)
* return : 成功したか?
***************************************************************/

bool_t	arrange_auto_mark( long n, long d )
{
	long	i, j, k;
	bool_t	flg;
	auto_mark_t	am[POSITION_KIND_MAX_N];
	auto_mark_appoint_item_t	item[AUTO_MARK_APPOINT_ITEM_MAX_N];
	auto_mark_appoint_item_t	item_tmp;
	const long	max_item = AUTO_MARK_APPOINT_ITEM_MAX_N;
	char	buf[MSG_TTL_AUTO_MARK_MAX_BYTE + 1];

	if( d <= -1 )
		d = -1;
	else if( d >= +1 )
		d = +1;
	else
		return FALSE;

	/**/

	flg = ls_flg_ena_auto_mark[n];

	if( d <= -1 ){
		for( j = n - 1; j >= 0; j-- ){
			ls_flg_ena_auto_mark[j + 1]
					= ls_flg_ena_auto_mark[j];
		}

		ls_flg_ena_auto_mark[0] = flg;
	} else {
		for( j = n + 1; j < AUTO_MARK_MAX_N; j++ ){
			ls_flg_ena_auto_mark[j - 1]
					= ls_flg_ena_auto_mark[j];
		}

		ls_flg_ena_auto_mark[j - 1] = flg;
	}

	/**/

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			am[k] = ls_auto_mark[i][n][k];

		for( k = 0; k < max_item; k++ ){
			item[k] = auto_mark_appoint_item[i][n][k];
		}

		if( d <= -1 ){
			for( j = n - 1; j >= 0; j-- ){
				for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
					ls_auto_mark[i][j + 1][k]
							= ls_auto_mark
							[i][j][k];
				}

				for( k = 0; k < max_item; k++ ){
					item_tmp = auto_mark_appoint_item
							[i][j][k];
					auto_mark_appoint_item[i][j + 1][k]
							= item_tmp;
				}
			}

			for( k = 0; k < POSITION_KIND_MAX_N; k++ )
				ls_auto_mark[i][0][k] = am[k];

			for( k = 0; k < max_item; k++ ){
				auto_mark_appoint_item
						[i][0][k]
						= item[k];
			}
		} else {
			for( j = n + 1; j < AUTO_MARK_MAX_N; j++ ){
				for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
					ls_auto_mark[i][j - 1][k]
							= ls_auto_mark
							[i][j][k];
				}

				for( k = 0; k < max_item; k++ ){
					item_tmp = auto_mark_appoint_item
							[i][j][k];
					auto_mark_appoint_item[i][j - 1][k]
							= item_tmp;
				}
			}

			for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
				ls_auto_mark[i][AUTO_MARK_MAX_N - 1][k]
						= am[k];
			}

			for( k = 0; k < max_item; k++ ){
				auto_mark_appoint_item
						[i][AUTO_MARK_MAX_N - 1][k]
						= item[k];
			}
		}
	}

	/**/

	str_nz_cpy( buf, get_msg_ttl_auto_mark_code( n ),
			MSG_TTL_AUTO_MARK_MAX_BYTE );

	if( d <= -1 ){
		for( j = n - 1; j >= 0; j-- ){
			str_nz_cpy( get_msg_ttl_auto_mark_code( j + 1 ),
					get_msg_ttl_auto_mark_code( j ),
					MSG_TTL_AUTO_MARK_MAX_BYTE );
		}

		str_nz_cpy( get_msg_ttl_auto_mark_code( 0 ), buf,
				MSG_TTL_AUTO_MARK_MAX_BYTE );
	} else {
		for( j = n + 1; j < AUTO_MARK_MAX_N; j++ ){
			str_nz_cpy( get_msg_ttl_auto_mark_code( j - 1 ),
					get_msg_ttl_auto_mark_code( j ),
					MSG_TTL_AUTO_MARK_MAX_BYTE );
		}

		str_nz_cpy( get_msg_ttl_auto_mark_code( j - 1 ), buf,
				MSG_TTL_AUTO_MARK_MAX_BYTE );
	}

	/**/

	return TRUE;
}

/***************************************************************
* メニューを 1 つ分並べ換え(メンバー単位)
* long ls_mbr_n : メンバー
* long d : 先頭(-1)/末尾(+1)
* return : 成功したか?
***************************************************************/

bool_t	arrange_auto_mark_mbr_1( long n, long d )
{
	long	j, k;
	auto_mark_t	am[AUTO_MARK_MAX_N][POSITION_KIND_MAX_N];
	auto_mark_appoint_item_t	item
			[AUTO_MARK_MAX_N]
			[AUTO_MARK_APPOINT_ITEM_MAX_N];
	const long	max_item = AUTO_MARK_APPOINT_ITEM_MAX_N;

	if( d == 0 )
		return FALSE;
	if( (n + d) < 0 )
		return FALSE;
	if( (n + d) >= AUTO_MARK_MAX_N )
		return FALSE;

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			am[j][k] = ls_auto_mark[n][j][k];

		for( k = 0; k < max_item; k++ ){
			item[j][k] = auto_mark_appoint_item[n][j][k];
		}
	}

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			ls_auto_mark[n][j][k] = ls_auto_mark[n + d][j][k];

		for( k = 0; k < max_item; k++ ){
			auto_mark_appoint_item[n][j][k]
					= auto_mark_appoint_item
					[n + d][j][k];
		}
	}

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			ls_auto_mark[n + d][j][k] = am[j][k];

		for( k = 0; k < max_item; k++ ){
			auto_mark_appoint_item[n + d][j][k] = item[j][k];
		}
	}

	return TRUE;
}

/***************************************************************
* メニューの並べ換え(メンバー単位)
* long ls_mbr_n : メンバー
* long d : 先頭(-1)/末尾(+1)
* return : 成功したか?
***************************************************************/

bool_t	arrange_auto_mark_mbr( long ls_mbr_n, long d )
{
	long	i, j, k;
	auto_mark_t	am[AUTO_MARK_MAX_N][POSITION_KIND_MAX_N];
	auto_mark_appoint_item_t	item
			[AUTO_MARK_MAX_N]
			[AUTO_MARK_APPOINT_ITEM_MAX_N];
	auto_mark_appoint_item_t	item_tmp;
	const long	max_item = AUTO_MARK_APPOINT_ITEM_MAX_N;
	mbr_t	**ls_mbr;

	if( d <= -1 )
		d = -1;
	else if( d >= +1 )
		d = +1;
	else
		return FALSE;

	ls_mbr = get_ls_mbr();

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			am[j][k] = ls_auto_mark[ls_mbr_n][j][k];

		for( k = 0; k < max_item; k++ ){
			item[j][k] = auto_mark_appoint_item[ls_mbr_n][j][k];
		}
	}

	if( d <= -1 ){
		for( i = ls_mbr_n; i > 0; i-- ){
			for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
				for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
					ls_auto_mark[i][j][k] = ls_auto_mark
							[i - 1][j][k];
				}

				for( k = 0; k < max_item; k++ ){
					item_tmp = auto_mark_appoint_item
							[i - 1][j][k];
					auto_mark_appoint_item[i][j][k]
							= item_tmp;
				}
			}
		}
	} else {
		for( i = ls_mbr_n; i < LS_MBR_MAX_N - 1; i++ ){
			if( chk_flg( ls_mbr[i + 1]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}
			for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
				for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
					ls_auto_mark[i][j][k] = ls_auto_mark
							[i + 1][j][k];
				}

				for( k = 0; k < max_item; k++ ){
					item_tmp = auto_mark_appoint_item
							[i + 1][j][k];
					auto_mark_appoint_item[i][j][k]
							= item_tmp;
				}
			}
		}
	}

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		for( k = 0; k < POSITION_KIND_MAX_N; k++ )
			ls_auto_mark[i][j][k] = am[j][k];

		for( k = 0; k < max_item; k++ ){
			auto_mark_appoint_item[i][j][k] = item[j][k];
		}
	}

	return TRUE;
}

/***************************************************************
* メニューの削除(メンバー単位)
* long ls_mbr_n : メンバー
* return : 成功したか?
***************************************************************/

bool_t	remove_auto_mark_mbr( long ls_mbr_n )
{
	return arrange_auto_mark_mbr( ls_mbr_n, +1 );
}

/***************************************************************
* デフォルトの自動マークがダブっているか調べる
* dflt_auto_mark_t n : デフォルトの自動マークの種類
* return : ダブっているか
***************************************************************/

bool_t	chk_dup_dflt_auto_mark( dflt_auto_mark_t n )
{
	long	dup_n;
	long	j;

	dup_n = 0;

	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		if( !ls_flg_ena_auto_mark[j] )
			continue;

		if( ls_auto_mark[0][j][0].dflt == n )
			dup_n++;
	}

	if( dup_n >= 2 )
		return TRUE;
	else
		return FALSE;
}

/***************************************************************
* 配置から配置の文字列へ変換
* mbr_t *mbr : メンバー
* return : 対象のメニュー文字列
***************************************************************/

char	*get_msg_menu_auto_mark_edit_position( mbr_t *mbr )
{
	switch( mbr->position_kind ){
	case POSITION_KIND_NULL:
	case POSITION_KIND_MAX_N:
		break;
	case POSITION_KIND_FORWARD:
		return MSG_MENU_POSITION_FORWARD;
	case POSITION_KIND_HALFBACK:
		return MSG_MENU_POSITION_HALFBACK;
	case POSITION_KIND_BACK:
		return MSG_MENU_POSITION_BACK;
	}

	return MSG_NOT_NULL;
}

/***************************************************************
* 対象から対象の文字列へ変換
* mbr_t *mbr : メンバー
* return : 対象のメニュー文字列
***************************************************************/

char	*get_msg_menu_auto_mark_edit_trgt( mbr_t *mbr )
{
	switch( ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind].trgt ){
	case AUTO_MARK_TRGT_MNSTR:
		return MSG_MENU_AUTO_MARK_TRGT_MNSTR;
	case AUTO_MARK_TRGT_ITEM:
		return MSG_MENU_AUTO_MARK_TRGT_ITEM;
	case AUTO_MARK_TRGT_DOOR:
		return MSG_MENU_AUTO_MARK_TRGT_DOOR;
	case AUTO_MARK_TRGT_TRAP:
		return MSG_MENU_AUTO_MARK_TRGT_TRAP;
	case AUTO_MARK_TRGT_MBR:
		return MSG_MENU_AUTO_MARK_TRGT_MBR;
	case AUTO_MARK_TRGT_UNCHANGE:
		return MSG_MENU_AUTO_MARK_TRGT_UNCHANGE;
	case AUTO_MARK_TRGT_CLEAR:
		return MSG_MENU_AUTO_MARK_TRGT_CLEAR;
	}

	return MSG_NOT_NULL;
}

/***************************************************************
* 間合いから間合いの文字列へ変換
* mbr_t *mbr : メンバー
* return : 間合いのメニュー文字列
***************************************************************/

char	*get_msg_menu_auto_mark_edit_dist( mbr_t *mbr )
{
	auto_mark_t	*am;

	am = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);

	if( (am->trgt == AUTO_MARK_TRGT_UNCHANGE)
			|| (am->trgt ==AUTO_MARK_TRGT_CLEAR) ){
		return MSG_MENU_AUTO_MARK_INVALID;
	}

	switch( am->dist ){
	case AUTO_MARK_DIST_NEAR:
		return MSG_MENU_AUTO_MARK_DIST_NEAR;
	case AUTO_MARK_DIST_MEDIUM:
		return MSG_MENU_AUTO_MARK_DIST_MEDIUM;
	case AUTO_MARK_DIST_FAR:
		return MSG_MENU_AUTO_MARK_DIST_FAR;
	}

	return MSG_NOT_NULL;
}

/***************************************************************
* 行動から行動の文字列へ変換
* mbr_t *mbr : メンバー
* return : 行動のメニュー文字列
***************************************************************/

char	*get_msg_menu_auto_mark_edit_act( mbr_t *mbr )
{
	auto_mark_t	*am;

	am = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);

	if( (am->trgt == AUTO_MARK_TRGT_UNCHANGE)
			|| (am->trgt ==AUTO_MARK_TRGT_CLEAR) ){
		return MSG_MENU_AUTO_MARK_INVALID;
	}

	switch( am->act ){
	case AUTO_MARK_ACT_FIGHT:
		return MSG_MENU_AUTO_MARK_ACT_FIGHT;
	case AUTO_MARK_ACT_THROW:
		return MSG_MENU_AUTO_MARK_ACT_THROW;
	case AUTO_MARK_ACT_STEAL:
		return MSG_MENU_AUTO_MARK_ACT_STEAL;
	case AUTO_MARK_ACT_TAIL:
		return MSG_MENU_AUTO_MARK_ACT_TAIL;
	case AUTO_MARK_ACT_PICK_UP:
		return MSG_MENU_AUTO_MARK_ACT_PICK_UP;
	case AUTO_MARK_ACT_OPEN:
		return MSG_MENU_AUTO_MARK_ACT_OPEN;
	case AUTO_MARK_ACT_CLOSE:
		return MSG_MENU_AUTO_MARK_ACT_CLOSE;
	case AUTO_MARK_ACT_JAM:
		return MSG_MENU_AUTO_MARK_ACT_JAM;
	case AUTO_MARK_ACT_DISARM:
		return MSG_MENU_AUTO_MARK_ACT_DISARM;
	case AUTO_MARK_ACT_BREAK:
		return MSG_MENU_AUTO_MARK_ACT_BREAK;
	case AUTO_MARK_ACT_PEEP:
		return MSG_MENU_AUTO_MARK_ACT_PEEP;
	case AUTO_MARK_ACT_CHK:
		return MSG_MENU_AUTO_MARK_ACT_CHK;
	}

	return MSG_NOT_NULL;
}

/***************************************************************
* 条件から条件の文字列へ変換
* mbr_t *mbr : メンバー
* return : 条件のメニュー文字列
***************************************************************/

char	*get_msg_menu_auto_mark_edit_cond( mbr_t *mbr )
{
	auto_mark_t	*am;

	am = &(ls_auto_mark[mbr->ls_mbr_n][auto_mark_cur_n]
			[mbr->position_kind]);

	if( (am->trgt == AUTO_MARK_TRGT_UNCHANGE)
			|| (am->trgt ==AUTO_MARK_TRGT_CLEAR) ){
		return MSG_MENU_AUTO_MARK_INVALID;
	}

	switch( am->cond ){
	case AUTO_MARK_COND_NEAREST:
		return MSG_MENU_AUTO_MARK_COND_NEAREST;
	case AUTO_MARK_COND_DISPERSE:
		return MSG_MENU_AUTO_MARK_COND_DISPERSE;
	case AUTO_MARK_COND_STAGGER:
		return MSG_MENU_AUTO_MARK_COND_STAGGER;
	case AUTO_MARK_COND_OWN:
		return MSG_MENU_AUTO_MARK_COND_OWN;
	case AUTO_MARK_COND_IDENTIFIED:
		return MSG_MENU_AUTO_MARK_COND_IDENTIFIED;
	case AUTO_MARK_COND_UN_IDENTIFIED:
		return MSG_MENU_AUTO_MARK_COND_UN_IDENTIFIED;
	case AUTO_MARK_COND_HP_MIN:
		return MSG_MENU_AUTO_MARK_COND_HP_MIN;
	case AUTO_MARK_COND_HP_MAX:
		return MSG_MENU_AUTO_MARK_COND_HP_MAX;
	case AUTO_MARK_COND_MP_MIN:
		return MSG_MENU_AUTO_MARK_COND_MP_MIN;
	case AUTO_MARK_COND_MP_MAX:
		return MSG_MENU_AUTO_MARK_COND_MP_MAX;
	}

	return MSG_NOT_NULL;
}

/***************************************************************
* 現在の自動マークの番号を返す
* return : 現在の自動マークの番号
***************************************************************/

long	get_auto_mark_cur_n( void )
{
	return auto_mark_cur_n;
}

/***************************************************************
* 現在の自動マークのアイテム種類別を返す
* return : 現在の自動マークのアイテム種類別
***************************************************************/

auto_mark_appoint_item_t	*get_auto_mark_appoint_item( mbr_t *mbr )
{
	long	n;

	if( mbr == NULL )
		return NULL;

	n = get_auto_mark_cur_n();

	return auto_mark_appoint_item[mbr->ls_mbr_n][n];
}

/***************************************************************
* 自動マークのタイトルの内部文字列を返す
* long n : 自動マークの番号
* return : 自動マークのタイトルの内部文字列
***************************************************************/

char	*get_msg_ttl_auto_mark_code( long n )
{
	return msg_ttl_auto_mark[n];
}

/***************************************************************
* 自動マークのタイトルの名前の文字列を返す
* long n : 自動マークの番号
* return : 自動マークのタイトルの名前の文字列
***************************************************************/

char	*get_msg_ttl_auto_mark_name( long n )
{
	static char	str[MSG_TTL_AUTO_MARK_MAX_BYTE + 1];

	str[0] = '\0';
	str_max_n_cat( str, get_msg_ttl_auto_mark_info( n ),
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	str_max_n_cat( str, STR_TTL_AUTO_MARK_SPLIT_NAME,
			MSG_TTL_AUTO_MARK_MAX_BYTE );
	str_max_n_cat( str, get_msg_ttl_auto_mark_hint( n ),
			MSG_TTL_AUTO_MARK_MAX_BYTE );

	return str;
}

/***************************************************************
* 自動マークのタイトルの詳細文字列を返す
* long n : 自動マークの番号
* return : 自動マークのタイトルの詳細文字列
***************************************************************/

char	*get_msg_ttl_auto_mark_info( long n )
{
	static char	str[MSG_TTL_AUTO_MARK_INFO_MAX_BYTE + 1];
	char	*ttl, *p;

	ttl = msg_ttl_auto_mark[n];

	p = strstr( ttl, STR_TTL_AUTO_MARK_SPLIT_CODE );
	if( p == NULL ){
		str_nz_cpy( str, ttl, MSG_TTL_AUTO_MARK_INFO_MAX_BYTE );
	} else {
		long	len;

		len = p - ttl;
		if( len < 0 )
			len = 0;
		if( len > MSG_TTL_AUTO_MARK_INFO_MAX_BYTE )
			len = MSG_TTL_AUTO_MARK_INFO_MAX_BYTE;

		str_nz_cpy( str, ttl, len );
	}

	return str;
}

/***************************************************************
* 自動マークのタイトルのヒント文字列を返す
* long n : 自動マークの番号
* return : 自動マークのタイトルのヒント文字列
***************************************************************/

char	*get_msg_ttl_auto_mark_hint( long n )
{
	static char	str[MSG_TTL_AUTO_MARK_HINT_MAX_BYTE + 1];
	char	*ttl, *p;

	ttl = msg_ttl_auto_mark[n];

	p = strstr( ttl, STR_TTL_AUTO_MARK_SPLIT_CODE );
	if( p == NULL ){
		str[0] = '\0';
	} else {
		long	len;

		len = str_len_std( STR_TTL_AUTO_MARK_SPLIT_CODE );
		str_nz_cpy( str, &(p[len]), MSG_TTL_AUTO_MARK_HINT_MAX_BYTE );
	}

	return str;
}

/***************************************************************
* 自動マークのデータ配列を返す
* long ls_mbr_n : メンバー・リストの番号
* long auto_mark_n : 自動マークのスロット番号
* position_kind_t position_kind : メンバーの配置
* return : 自動マークのデータ配列を返す
***************************************************************/

auto_mark_t	*get_auto_mark(
	long ls_mbr_n, long auto_mark_n, position_kind_t position_kind
)
{
	if( ls_mbr_n < 0 )
		return NULL;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return NULL;
	if( auto_mark_n < 0 )
		return NULL;
	if( auto_mark_n >= AUTO_MARK_MAX_N )
		return NULL;
	if( position_kind < 0 )
		return NULL;
	if( position_kind >= POSITION_KIND_MAX_N )
		return NULL;

	return( &(ls_auto_mark[ls_mbr_n][auto_mark_n][position_kind]) );
}

/***************************************************************
* 自動マークのデータが有効か調べる
* long n : 自動マークの番号
* return : 有効か?
***************************************************************/

bool_t	chk_flg_ena_auto_mark( long n )
{
	if( n < 0 )
		return FALSE;
	if( n >= AUTO_MARK_MAX_N )
		return FALSE;

	return ls_flg_ena_auto_mark[n];
}

/***************************************************************
* 自動マークのデータが有効か設定する
* long n : 自動マークの番号
* bool_t flg : 有効か?
***************************************************************/

void	set_flg_ena_auto_mark( long n, bool_t flg )
{
	if( n < 0 )
		return;
	if( n >= AUTO_MARK_MAX_N )
		return;

	ls_flg_ena_auto_mark[n] = flg;
}

/***************************************************************
* 自動マークのアイテムのデータ配列を返す
* long ls_mbr_n : メンバー・リストの番号
* n : 自動マークの番号
* return : 自動マークのアイテムのデータ配列を返す
***************************************************************/

auto_mark_appoint_item_t	*get_ls_auto_mark_appoint_item(
	long ls_mbr_n, long n
)
{
	if( ls_mbr_n < 0 )
		return NULL;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return NULL;
	if( n < 0 )
		return NULL;
	if( n >= AUTO_MARK_MAX_N )
		return NULL;

	return( auto_mark_appoint_item[ls_mbr_n][n] );
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_amenu_c( void )
{
	check_memory( check_memory_amenu_c_ls_auto_mark,
			"amenu.c: ls_auto_mark" );
	check_memory( check_memory_amenu_c_ls_flg_ena_auto_mark,
			"amenu.c: ls_flg_ena_auto_mark" );
	check_memory( check_memory_amenu_c_clip_board_large,
			"amenu.c: clip_board_large" );
	check_memory( check_memory_amenu_c_clip_board_small,
			"amenu.c: clip_board_small" );
	check_memory( check_memory_amenu_c_clip_board_large_item,
			"amenu.c: clip_board_large_item" );
	check_memory( check_memory_amenu_c_clip_board_small_item,
			"amenu.c: clip_board_small_item" );
	check_memory( check_memory_amenu_c_msg_ttl_auto_mark,
			"amenu.c: msg_ttl_auto_mark" );
	check_memory( check_memory_amenu_c_clip_board_ttl,
			"amenu.c: clip_board_ttl" );
	check_memory( check_memory_amenu_c_auto_mark_cur_n,
			"amenu.c: auto_mark_cur_n" );
	check_memory( check_memory_amenu_c_dflt_auto_mark_fight,
			"amenu.c: dflt_auto_mark_fight" );
	check_memory( check_memory_amenu_c_auto_mark_appoint_item,
			"amenu.c: auto_mark_appoint_item" );
	check_memory( check_memory_amenu_c_auto_mark_appoint_item_dflt,
			"amenu.c: auto_mark_appoint_item_dflt" );
}
