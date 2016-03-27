/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights resortrved.
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
* $Id: chr.c,v 1.347 2014/03/02 02:49:34 bowkenken Exp $
***************************************************************/

/***************************************************************
* キャラクタ
***************************************************************/

#define	CHR_C
#include	"inc.h"

/***************************************************************/

/* 必要経験値の増え方が固定されるレベル */
#define	FLAT_LEV	30

/* 街の住人の移動速度 */
#define	TOWNER_MOVE_RATE	((rate_t)50)
/* 街の住人の方向転換の率 */
#define	TOWNER_TURN_DIR_RATE	((rate_t)20)

/* メンバーの中間の間合いの遊び */
#define	MBR_DIST_MEDIUM_ADJUST_R	1
/* モンスターの中間の間合いとする距離 */
/* (モンスターにはアンカーが無いため) */
#define	MNSTR_DIST_MEDIUM_R	10

/* ドアのサーチの難易度 */
#define	DOOR_SRCH_DIFFICULTY	5
/* ドアの解除の難易度 */
#define	DOOR_DISARM_DIFFICULTY	10

/* 罠のサーチの難易度 */
#define	TRAP_SRCH_DIFFICULTY	10
/* 罠の識別の難易度 */
#define	TRAP_CHK_DIFFICULTY	20

/* 罠の解除に失敗した場合の罠の発動率 */
#define	TRAP_DISARM_FAILURE_RATE	((rate_t)30)
/* 宝箱の罠の解除に失敗した場合の罠の発動率 */
#define	CHEST_DISARM_FAILURE_RATE	((rate_t)30)

/* 罠の解除時に入る経験値をモンスターで表す */
#define	TRAP_MNSTR_KIND	MNSTR_KIND_GIANT_BAT

/* 街の門が開かないメッセージを表示する率 */
/* この確率のチェックがメンバーの人数分行なわれる */
#define	PRINT_ERR_DOOR_GATE_RATE	((rate_t)5)

/* セービング・ロールを行なう側が有利な率 */
#define	ROLL_ADJ_RATE	((rate_t)150)

/* レベルから寄付の消費金額への変換率 */
#define	USE_CONTRIBUTION_RATE	((rate_t)100)
/* 寄付の消費によるセービング・ロールの修整率 */
#define	ROLL_CONTRIBUTION_RATE	((rate_t)120)

/***************************************************************
* 変数定義
***************************************************************/

/* レベル数から経験値への変換の割合と加算値 */
static lev_to_exp_t	lev_to_exp_tab[ABL_KIND_MAX_N + 1] = {
	{ 100, 0 },	/* ABL_KIND_HP, */
	{ 100, 0 },	/* ABL_KIND_MP, */
	{ 100, 0 },	/* ABL_KIND_DEX, */
	{ 100, 0 },	/* ABL_KIND_STR, */
	{ 100, 0 },	/* ABL_KIND_QUI, */
	{ 100, 0 },	/* ABL_KIND_INT, */
	{ 100, 0 },	/* ABL_KIND_WIS, */
	{ 100, 0 },	/* ABL_KIND_CHA, */
	{ 100, 0 },	/* ABL_KIND_FIG, */
	{ 100, 0 },	/* ABL_KIND_MON, */
	{ 100, 0 },	/* ABL_KIND_HUN, */
	{ 100, 0 },	/* ABL_KIND_THI, */
	{ 100, 0 },	/* ABL_KIND_MAG, */
	{ 100, 0 },	/* ABL_KIND_SOR, */
	{ 100, 0 },	/* ABL_KIND_ENC, */
	{ 100, 0 },	/* ABL_KIND_SUM, */
	{ 100, 0 },	/* ABL_KIND_PRI, */
	{ 100, 0 },	/* ABL_KIND_SHA, */
	{ 100, 0 },	/* ABL_KIND_BAR, */
	{ 100, 0 },	/* ABL_KIND_NIN, */

	{ 100, 0 },	/* SKILL, */
};
check_memory_def( check_memory_chr_c_lev_to_exp_tab )

/* レベル数から経験値への変換の割合と加算値(全体) */
static lev_to_exp_t	lev_to_exp_val = {
	800, 0
};
check_memory_def( check_memory_chr_c_lev_to_exp_val )

/* レベル数から値への変換の割合と加算値 */
static lev_to_val_t	lev_to_val_tab[ABL_KIND_MAX_N + 1] = {
	{ 2000, 0 },	/* ABL_KIND_HP, */
	{ 2000, 0 },	/* ABL_KIND_MP, */
	{ 100, 0 },	/* ABL_KIND_DEX, */
	{ 100, 0 },	/* ABL_KIND_STR, */
	{ 100, 0 },	/* ABL_KIND_QUI, */
	{ 100, 0 },	/* ABL_KIND_INT, */
	{ 100, 0 },	/* ABL_KIND_WIS, */
	{ 100, 0 },	/* ABL_KIND_CHA, */
	{ 100, 0 },	/* ABL_KIND_FIG, */
	{ 100, 0 },	/* ABL_KIND_MON, */
	{ 100, 0 },	/* ABL_KIND_HUN, */
	{ 100, 0 },	/* ABL_KIND_THI, */
	{ 100, 0 },	/* ABL_KIND_MAG, */
	{ 100, 0 },	/* ABL_KIND_SOR, */
	{ 100, 0 },	/* ABL_KIND_ENC, */
	{ 100, 0 },	/* ABL_KIND_SUM, */
	{ 100, 0 },	/* ABL_KIND_PRI, */
	{ 100, 0 },	/* ABL_KIND_SHA, */
	{ 100, 0 },	/* ABL_KIND_BAR, */
	{ 100, 0 },	/* ABL_KIND_NIN, */

	{ 100, 0 },	/* SKILL, */
};
check_memory_def( check_memory_chr_c_lev_to_val_tab )

/* マップ奥からソートしたキャラクタのリストの先頭 */
static chr_t	g_sort_chr_head;
check_memory_def( check_memory_chr_c_g_sort_chr_head )

/* ダミーのモンスター */
static mnstr_null_t	mnstr_null[MBR_MAX_N];
check_memory_def( check_memory_chr_c_mnstr_null )

/* モンスターのダミーのアンカー */
static square_t	mnstr_square;
check_memory_def( check_memory_chr_c_mnstr_square )

/* フェーズを実行中か? */
static bool_t	g_flg_run_exec_all_phase;
check_memory_def( check_memory_chr_c_g_flg_run_exec_all_phase )

/* キャラクタが戦闘対象を発見したか? */
static bool_t	g_flg_mbr_find_mnstr;
static bool_t	g_flg_mnstr_find_mbr;
static bool_t	g_flg_boss_find_mbr;
check_memory_def( check_memory_chr_c_g_flg_mbr_find_mnstr )

static bool_t	g_flg_mbr_find_mnstr_pre;
static bool_t	g_flg_mnstr_find_mbr_pre;
static bool_t	g_flg_boss_find_mbr_pre;
check_memory_def( check_memory_chr_c_g_flg_mbr_find_mnstr_pre )

/***************************************************************
* 初期化
***************************************************************/

void	init_chr( void )
{
	g_flg_run_exec_all_phase = FALSE;

	g_flg_mbr_find_mnstr = FALSE;
	g_flg_mnstr_find_mbr = FALSE;
	g_flg_boss_find_mbr = FALSE;

	g_flg_mbr_find_mnstr_pre = FALSE;
	g_flg_mnstr_find_mbr_pre = FALSE;
	g_flg_boss_find_mbr_pre = FALSE;

	init_mnstr();
	init_party();
	init_pet();
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_chr( void )
{
}

/***************************************************************
* フェーズを実行中か調べる
* return : フェーズを実行中か?
***************************************************************/

bool_t	chk_flg_run_exec_all_phase( void )
{
	return g_flg_run_exec_all_phase;
}

/***************************************************************
* 全てのフェーズを実行
***************************************************************/

void	exec_all_phase( void )
{
	g_flg_run_exec_all_phase = TRUE;

	clr_chr_find();

	inc_turn();

	/* mnstr -> party -> pet */
	move_phase_all_mnstr();
	move_phase_all_mbr();
	move_phase_all_pet();

	sort_all_chr( FALSE );

	draw_phase( TRUE );

	/* scene */
	chk_change_scene();

	chk_chr_find();

	/* party -> pet -> mnstr */
	act_phase_all_mbr();
	act_phase_all_pet();
	act_phase_all_mnstr();

	dismissal_phase_all_pet();
	dismissal_phase_all_mnstr();

	/* scene */
	chk_change_scene();

	draw_phase( FALSE );

	chk_trap_party();
	chk_trap_all_pet();
	chk_trap_all_mnstr();

	draw_phase( FALSE );

	garbage_collection_all_pet();
	garbage_collection_all_mnstr();

	act_phase_party();
	chk_party_no_mbr( TRUE );

	last_boss_phase();

	g_flg_run_exec_all_phase = FALSE;
}

/***************************************************************
* キャラクタが攻撃対象を発見したフラグをクリア
***************************************************************/

void	clr_chr_find( void )
{
	g_flg_mbr_find_mnstr_pre = g_flg_mbr_find_mnstr;
	g_flg_mnstr_find_mbr_pre = g_flg_mnstr_find_mbr;
	g_flg_boss_find_mbr_pre = g_flg_boss_find_mbr;

	g_flg_mbr_find_mnstr = FALSE;
	g_flg_mnstr_find_mbr = FALSE;
	g_flg_boss_find_mbr = FALSE;
}

/***************************************************************
* キャラクタが攻撃対象を発見したかチェック
***************************************************************/

void	chk_chr_find( void )
{
	if( chk_flg_boss_find_mbr() ){
		call_game_sound_play(
				SOUND_KIND_FIGHT_FIND_MONSTER_BOSS,
				1 );
	} else if( chk_flg_mnstr_find_mbr() ){
		call_game_sound_play(
				SOUND_KIND_FIGHT_FIND_MONSTER,
				1 );
	} else if( chk_flg_mbr_find_mnstr() ){
		call_game_sound_play(
				SOUND_KIND_FIGHT_FIND_MEMBER,
				1 );
	}
}

/***************************************************************
* メンバーがモンスターを発見したフラグを設定する
* bool_t flg_find : 発見したフラグ
***************************************************************/

void	set_flg_mbr_find_mnstr( bool_t flg_find )
{
	g_flg_mbr_find_mnstr = flg_find;
}

/***************************************************************
* 1 匹以上のモンスターがメンバーを発見したフラグを設定する
* bool_t flg_find : 発見したフラグ
***************************************************************/

void	set_flg_mnstr_find_mbr( bool_t flg_find )
{
	g_flg_mnstr_find_mbr = flg_find;
}

/***************************************************************
* 1 匹以上のボスがメンバーを発見したフラグを設定する
* bool_t flg_find : 発見したフラグ
***************************************************************/

void	set_flg_boss_find_mbr( bool_t flg_find )
{
	g_flg_boss_find_mbr = flg_find;
}

/***************************************************************
* メンバーがモンスターを発見したフラグを返す
* return : 発見したフラグ
***************************************************************/

bool_t	chk_flg_mbr_find_mnstr( void )
{
	return( g_flg_mbr_find_mnstr && !g_flg_mbr_find_mnstr_pre );
}

/***************************************************************
* 1 匹以上のモンスターがメンバーを発見したフラグを返す
* return : 発見したフラグ
***************************************************************/

bool_t	chk_flg_mnstr_find_mbr( void )
{
	return( g_flg_mnstr_find_mbr && !g_flg_mnstr_find_mbr_pre );
}

/***************************************************************
* 1 匹以上のボスがメンバーを発見したフラグを設定を返す
* return : 発見したフラグ
***************************************************************/

bool_t	chk_flg_boss_find_mbr( void )
{
	return( g_flg_boss_find_mbr && !g_flg_boss_find_mbr_pre );
}

/***************************************************************
* ラスボスのフェーズを実行
***************************************************************/

void	last_boss_phase( void )
{
	if( get_scene() != SCENE_N_LAST_BOSS )
		return;

	do {
		draw_last_boss();
		sleep_msec( 100 );
	} while( chk_last_boss_demo() );
}

/***************************************************************
* 描画フェーズを実行
* bool_t flg_first_phase : ターン毎の最初の描画フェーズか?
***************************************************************/

void	draw_phase( bool_t flg_first_phase )
{
	if( flg_first_phase ){
		draw_all_mnstr();
		draw_party();
		draw_all_pet();

		call_pcg_dun_draw_turn( TRUE );
	} else {
		call_pcg_dun_draw_turn( FALSE );
	}
}

/***************************************************************
* キャラクタの移動フェーズを実行
* chr_t *chr : キャラクタ
***************************************************************/

void	move_phase_chr( chr_t *chr )
{
	bool_t	flg_adjoin, flg_move;

	if( chr == NULL )
		return;
	if( chk_flg( chr->stat, FLG_STAT_NOT_EXIST ) ){
		chr->x = MAP_DEL_X;
		chr->y = MAP_DEL_Y;

		return;
	}
	if( chk_flg( chr->stat, FLG_STAT_DEAD ) ){
		if( is_mbr( chr ) ){
			get_square_mbr_map_pos( chr->mbr_n,
					&(chr->x), &(chr->y) );
		} else {
			chr->x = MAP_DEL_X;
			chr->y = MAP_DEL_Y;
		}

		return;
	}
	if( chr->kind == CHR_KIND_MNSTR )
		if( chr->mnstr_kind == MNSTR_KIND_XX )
			return;

	chr->pre_x = chr->x;
	chr->pre_y = chr->y;
	chr->pre_turn_x = chr->x;
	chr->pre_turn_y = chr->y;

	move_chr_trgt( chr );

	if( !chk_can_act_chr( chr ) )
		return;

	flg_adjoin = chk_adjoin_chr_trgt( chr );
	flg_move = FALSE;

	switch( chr->act.kind ){
	case ACT_KIND_MAX_N:
	case ACT_KIND_SHOP:
	case ACT_KIND_TELEPORT_PARTY:
	case ACT_KIND_RECALL:
		break;
	case ACT_KIND_NULL:
	case ACT_KIND_MNSTR_TAIL:
	case ACT_KIND_MBR_TAIL:
		chk_clr_chr_discount_queue( chr );
		chk_enter_discount_shop( chr );
		flg_move = TRUE;
		break;
	case ACT_KIND_MNSTR_FIGHT:
	case ACT_KIND_MBR_FIGHT:
		flg_move = chk_bash_or_move( chr );
		break;
	case ACT_KIND_MNSTR_THROW:
	case ACT_KIND_MBR_THROW:
		if( !flg_adjoin )
			flg_move = TRUE;
		if( chr->move.force_kind == MOVE_KIND_STAGGER )
			flg_move = TRUE;
		break;
	case ACT_KIND_MNSTR_STEAL:
	case ACT_KIND_MBR_STEAL:
		if( !flg_adjoin )
			flg_move = TRUE;
		break;
	case ACT_KIND_DOOR_OPEN:
	case ACT_KIND_DOOR_CLOSE:
	case ACT_KIND_DOOR_JAM:
	case ACT_KIND_DOOR_DISARM:
	case ACT_KIND_DOOR_BREAK:
	case ACT_KIND_DOOR_PEEP:
	case ACT_KIND_DOOR_CHK:
	case ACT_KIND_TRAP_DISARM:
	case ACT_KIND_TRAP_BREAK:
	case ACT_KIND_TRAP_CHK:
	case ACT_KIND_ITEM_PICK_UP:
	case ACT_KIND_ITEM_BREAK:
	case ACT_KIND_ITEM_CHK:
	case ACT_KIND_ITEM_SEND:
	case ACT_KIND_ITEM_RECEIVE:
		if( !flg_adjoin )
			flg_move = TRUE;
		break;
	case ACT_KIND_ITEM_DROP:
		break;
	case ACT_KIND_ITEM_OPEN:
	case ACT_KIND_ITEM_DISARM:
		if( !flg_adjoin )
			flg_move = TRUE;
		break;
	case ACT_KIND_EQUIP_SEL:
	case ACT_KIND_EQUIP:
	case ACT_KIND_TAKE_OFF:
		break;
	case ACT_KIND_EQUIP_MBR:
	case ACT_KIND_TAKE_OFF_MBR:
		if( !flg_adjoin )
			flg_move = TRUE;
		break;
	case ACT_KIND_POTION_QUAFF:
	case ACT_KIND_POTION_FILL:
	case ACT_KIND_SCROLL_READ:
	case ACT_KIND_STICK_ZAP:
	case ACT_KIND_LAMP_RUB:
	case ACT_KIND_FOOD_EAT:
	case ACT_KIND_TOBACCO_DISPOSE:
		break;
	case ACT_KIND_SRCH:
		if( (get_turn() % 2) != chr->act.n )
			flg_move = TRUE;
		break;
	case ACT_KIND_SPELL:
		do {
			spell_tab_t	*spell_tab;

			spell_tab = (spell_tab_t *)(chr->act.p);
			if( (get_turn() % 2) != 0 )
				break;
			if( spell_tab == NULL )
				break;
			if( spell_tab->abl != ABL_KIND_BAR )
				break;

			flg_move = TRUE;
		} while( 0 );
		break;
	}

	if( flg_move )
		move_chr( chr );

	/* キャラクタが動いたら鋼鉄化を解除する */
	/* chk_can_act_chr()ではじかれて機能しないが念のため残してある */

	if( (chr->x != chr->pre_x) || (chr->y != chr->pre_y) ){
		if( chk_flg( chr->stat, FLG_STAT_IRON_BODY ) ){
			fx_t	*fx;

			fx = srch_fx( &(chr->fx), FX_KIND_IRON_BODY );
			if( fx != NULL ){
				clr_fx( fx );
			}

			return;
		}
	}

	if( chr->kind == CHR_KIND_MNSTR )
		set_flg_find_mnstr( chr );
}

/***************************************************************
* キャラクタの行動フェーズを実行
* chr_t *chr : キャラクタ
***************************************************************/

void	act_phase_chr( chr_t *chr )
{
	bool_t	flg_do_act;
	spell_tab_t	*spell_tab;

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	move_chr_trgt( chr );

	if( !chk_can_act_chr( chr ) )
		return;

	/* キャラクタが動いたら鋼鉄化を解除する */
	/* chk_can_act_chr()ではじかれて機能しないが念のため残してある */

	if( chr->act.kind != ACT_KIND_NULL ){
		if( chk_flg( chr->stat, FLG_STAT_IRON_BODY ) ){
			fx_t	*fx;

			fx = srch_fx( &(chr->fx), FX_KIND_IRON_BODY );
			if( fx != NULL ){
				clr_fx( fx );
			}

			return;
		}
	}

	if( (chr->x != chr->pre_x) || (chr->y != chr->pre_y) )
		return;

	flg_do_act = (chr->x == chr->trgt.x) && (chr->y == chr->trgt.y);
	if( chk_xx_range() )
		flg_do_act = TRUE;

	switch( chr->act.kind ){
	case ACT_KIND_MAX_N:
	case ACT_KIND_SHOP:
	case ACT_KIND_TELEPORT_PARTY:
	case ACT_KIND_RECALL:
		break;
	case ACT_KIND_NULL:
	case ACT_KIND_MNSTR_TAIL:
	case ACT_KIND_MBR_TAIL:
		break;
	case ACT_KIND_MNSTR_FIGHT:
	case ACT_KIND_MBR_FIGHT:
		bash_or_move( chr );
		break;
	case ACT_KIND_MNSTR_THROW:
	case ACT_KIND_MBR_THROW:
		if( is_mnstr( chr ) )
			flg_do_act = TRUE;

		if( flg_do_act ){
			if( !chk_range_chr_throw( chr ) ){
				clr_chr_trgt_act( chr, FALSE );
				break;
			}

			if( chr->trgt.kind == TRGT_KIND_MBR ){
				fight_throw( chr, (mbr_t *)(chr->trgt.p),
						NULL );
			} else if( chr->trgt.kind == TRGT_KIND_MNSTR ){
				fight_throw( chr, (mnstr_t *)(chr->trgt.p),
						NULL );
			} else if( chr->trgt.kind == TRGT_KIND_MNSTR_NULL ){
				act_throw_mnstr_null( chr );
			} else {
				clr_chr_trgt_act( chr, FALSE );
			}
		}
		break;
	case ACT_KIND_MNSTR_STEAL:
	case ACT_KIND_MBR_STEAL:
		if( flg_do_act ){
			if( steal( chr, (chr_t *)(chr->trgt.p) ) )
				clr_chr_trgt_act( chr, FALSE );
		}
		break;
	case ACT_KIND_DOOR_OPEN:
		if( flg_do_act ){
			chr_open_door( chr, chr->trgt.n );
		}
		break;
	case ACT_KIND_DOOR_CLOSE:
		if( flg_do_act ){
			chr_close_door( chr, chr->trgt.n );
		}
		break;
	case ACT_KIND_DOOR_JAM:
		if( flg_do_act ){
			chr_jam_door( chr, chr->trgt.n );
		}
		break;
	case ACT_KIND_DOOR_DISARM:
		if( flg_do_act ){
			if( chr_disarm_door( chr, chr->trgt.n ) ){
				clr_chr_trgt_act( chr, FALSE );
			}
		}
		break;
	case ACT_KIND_DOOR_BREAK:
		if( flg_do_act ){
			chr_break_door( chr, chr->trgt.n );
		}
		break;
	case ACT_KIND_DOOR_PEEP:
		if( flg_do_act ){
			chr_peep_door( chr, chr->trgt.n );
		}
		break;
	case ACT_KIND_DOOR_CHK:
		if( flg_do_act ){
			chr_chk_door( chr, chr->trgt.n );
		}
		break;
	case ACT_KIND_TRAP_DISARM:
		if( flg_do_act ){
			if( chr_disarm_trap( chr,
					(trap_t *)(chr->trgt.p) ) ){
				clr_chr_trgt_act( chr, FALSE );
			}
		}
		break;
	case ACT_KIND_TRAP_BREAK:
		if( flg_do_act ){
			if( chr_break_trap( chr,
					(trap_t *)(chr->trgt.p) ) ){
				clr_chr_trgt_act( chr, FALSE );
			}
		}
		break;
	case ACT_KIND_TRAP_CHK:
		if( flg_do_act ){
			if( chr_chk_trap( chr,
					(trap_t *)(chr->trgt.p) ) ){
				clr_chr_trgt_act( chr, FALSE );
			}
		}
		break;
	case ACT_KIND_ITEM_PICK_UP:
		if( flg_do_act ){
			if( pick_up_item( chr, chr->x, chr->y ) )
				clr_chr_trgt_act( chr, FALSE );
			else
				clr_chr_trgt_act( chr, TRUE );
		}
		break;
	case ACT_KIND_ITEM_BREAK:
		if( flg_do_act ){
			if( chr_break_item( chr,
					(item_t *)(chr->trgt.p) ) ){
				clr_chr_trgt_act( chr, FALSE );
			}
		}
		break;
	case ACT_KIND_ITEM_CHK:
		if( flg_do_act ){
			chr_chk_item( chr, (item_t *)(chr->trgt.p) );
			clr_chr_trgt_act( chr, FALSE );
		}
		break;
	case ACT_KIND_ITEM_SEND:
		if( flg_do_act ){
			send_item( chr );
			clr_chr_trgt_act( chr, FALSE );
		}
		break;
	case ACT_KIND_ITEM_RECEIVE:
		if( flg_do_act ){
			receive_item( chr );
			clr_chr_trgt_act( chr, FALSE );
		}
		break;
	case ACT_KIND_ITEM_DROP:
		drop_item( chr->x, chr->y, (item_t *)(chr->act.p),
				chr->act.n );
		clr_chr_trgt_act( chr, TRUE );
		break;
	case ACT_KIND_ITEM_OPEN:
		if( flg_do_act ){
			if( chr_open_item( chr, (item_t *)(chr->trgt.p) ) ){
				call_game_sound_play(
						SOUND_KIND_ITEM_OPEN,
						1 );

				clr_chr_trgt_act( chr, FALSE );
			}
		}
		break;
	case ACT_KIND_ITEM_DISARM:
		if( flg_do_act ){
			if( chr_disarm_item( chr,
					(item_t *)(chr->trgt.p) ) ){
				clr_chr_trgt_act( chr, FALSE );
			}
		}
		break;
	case ACT_KIND_EQUIP_SEL:
		equip_item_sel( chr, (item_t *)chr->act.p );
		break;
	case ACT_KIND_EQUIP:
		equip_item( chr, (item_t *)chr->act.p,
				(equip_kind_t)chr->act.n );
		clr_chr_trgt_act( chr, FALSE );
		break;
	case ACT_KIND_TAKE_OFF:
		take_off_item( chr, (equip_kind_t)chr->act.n );
		clr_chr_trgt_act( chr, FALSE );
		break;
	case ACT_KIND_EQUIP_MBR:
		if( flg_do_act ){
			equip_item( (chr_t *)chr->act.p2,
					(item_t *)chr->act.p,
					(equip_kind_t)chr->act.n );
			clr_chr_trgt_act( chr, FALSE );
		}
		break;
	case ACT_KIND_TAKE_OFF_MBR:
		if( flg_do_act ){
			take_off_item( (chr_t *)chr->act.p2,
					(equip_kind_t)chr->act.n );
			clr_chr_trgt_act( chr, FALSE );
		}
		break;
	case ACT_KIND_POTION_QUAFF:
		call_game_sound_play( SOUND_KIND_ITEM_USE, 1 );

		quaff_potion( chr, (item_t *)chr->act.p, TRUE );
		clr_chr_trgt_act( chr, FALSE );
		break;
	case ACT_KIND_POTION_FILL:
		call_game_sound_play( SOUND_KIND_ITEM_USE, 1 );

		fill_potion( chr, (item_t *)chr->act.p );
		clr_chr_trgt_act( chr, FALSE );
		break;
	case ACT_KIND_SCROLL_READ:
		call_game_sound_play( SOUND_KIND_ITEM_USE, 1 );

		read_scroll( chr, (item_t *)chr->act.p );
		clr_chr_trgt_act( chr, FALSE );
		break;
	case ACT_KIND_STICK_ZAP:
		call_game_sound_play( SOUND_KIND_ITEM_USE, 1 );

		zap_stick( chr, (item_t *)chr->act.p );
		stop_zapping( chr );
		break;
	case ACT_KIND_LAMP_RUB:
		call_game_sound_play( SOUND_KIND_ITEM_USE, 1 );

		rub_lamp( chr, (item_t *)chr->act.p );
		clr_chr_trgt_act( chr, FALSE );
		break;
	case ACT_KIND_FOOD_EAT:
		call_game_sound_play( SOUND_KIND_ITEM_USE, 1 );

		eat_food( chr, (item_t *)chr->act.p );
		clr_chr_trgt_act( chr, FALSE );
		break;
	case ACT_KIND_TOBACCO_DISPOSE:
		dispose_tobacco( chr, (item_t *)chr->act.p );
		clr_chr_trgt_act( chr, FALSE );
		break;
	case ACT_KIND_SRCH:
		chr_srch_obj( chr );
		break;
	case ACT_KIND_SPELL:
		spell_tab = (spell_tab_t *)(chr->act.p);
		chr_cast_spell( chr, spell_tab,
				(char *)(chr->act.p2) );

		if( spell_tab->abl != ABL_KIND_BAR )
			clr_chr_trgt_act( chr, FALSE );
		break;
	}

	if( chr->kind == CHR_KIND_MNSTR )
		if( chr->mnstr_kind == MNSTR_KIND_XX )
			act_mnstr_xx( (mnstr_t *)chr );

	if( chk_flg( chr->stat, FLG_STAT_VANISH ) )
		chr->flg_map |= FLG_MAP_CHR_INVISIBLE;

	if( chr->attitude == ATTITUDE_ENEMY )
		chr->flg_map &= ~FLG_MAP_CHR_NPC;
	else
		chr->flg_map |= FLG_MAP_CHR_NPC;

	chr->pre_act = chr->act;
}

/***************************************************************
* キャラクタの送還フェーズを実行
* chr_t *chr : キャラクタ
***************************************************************/

void	dismissal_phase_chr( chr_t *chr )
{
	if( chr == NULL )
		return;

	if( chr->work.dismissal_turn <= 0 )
		return;

	/* 一定ターンで送還 */

	chr->work.dismissal_turn--;
	if( chr->work.dismissal_turn <= 0 )
		fx_dismissal( chr );
}

/***************************************************************
* キャラクタが行動出来るかを調べる
* chr_t *chr : キャラクタ
* return : キャラクタが行動出来るか
***************************************************************/

bool_t	chk_can_act_chr( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( is_mbr( chr ) )
		return chk_can_act_mbr( chr );
	if( chr->kind == CHR_KIND_MNSTR )
		return chk_can_act_mnstr( chr );

	return FALSE;
}

/***************************************************************
* キャラクタが攻撃するか移動するかを調べる
* chr_t *chr : キャラクタ
* return : キャラクタが移動するなら真
***************************************************************/

bool_t	chk_bash_or_move( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( get_move_kind_rand( chr ) == MOVE_KIND_STAGGER ){
		chr->move.force_kind = MOVE_KIND_STAGGER;
		return TRUE;
	}

	if( chr->move.force_kind == MOVE_KIND_STAGGER )
		return TRUE;

	if( chk_range_chr_bash( chr ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 攻撃か移動を実行
* chr_t *chr : キャラクタ
***************************************************************/

void	bash_or_move( chr_t *chr )
{
	if( chr == NULL )
		return;

	if( chr->trgt.kind == TRGT_KIND_MBR ){
		if( chk_range_chr_bash( chr ) )
			fight_bash( chr, (chr_t *)(chr->trgt.p), NULL );
	} else if( chr->trgt.kind == TRGT_KIND_MNSTR ){
		if( chk_range_chr_bash( chr ) )
			fight_bash( chr, (chr_t *)(chr->trgt.p), NULL );
	} else if( chr->trgt.kind == TRGT_KIND_MNSTR_NULL ){
		dun_t	*dun = get_dun();
		long	x, y;
		long	c;

		x = chr->trgt.x;
		y = chr->trgt.y;
		c = dun->map.chr.mjr[y][x];
		if( c == FACE_MJR_NULL ){
			print_msg_mbr( chr, FLG_NULL, MSG_S,
					MSG_ERR_MNSTR_NULL );
		} else if( c == FACE_MJR_MBR ){
			chr_t	*chr2;

			chr2 = get_mbr( x, y );
			if( chr2 == NULL )
				return;
			if( chr2 == chr )
				return;

			set_chr_act( chr, ACT_KIND_MBR_FIGHT,
					NULL, NULL,
					0, 0 );
			mark_mbr( chr, chr2, DIST_NEAR );
			fight_bash( chr, chr2, NULL );
		} else {
			mnstr_t	*mns;

			mns = get_mnstr( x, y );
			if( mns == NULL )
				return;
			if( mns == chr )
				return;

			mark_mnstr_dflt( chr, mns );
			fight_bash( chr, mns, NULL );
		}
	} else {
		clr_chr_trgt_act( chr, FALSE );
	}
}

/***************************************************************
* モンスターがいない場所を遠隔攻撃
* chr_t *chr : 攻撃する側のキャラクタ
***************************************************************/

void	act_throw_mnstr_null( chr_t *chr )
{
	dun_t	*dun = get_dun();
	mnstr_null_t	*p;
	long	c;

	if( chr == NULL )
		return;
	if( chr->act.kind != ACT_KIND_MNSTR_THROW )
		return;
	if( chr->trgt.kind != TRGT_KIND_MNSTR_NULL )
		return;

	p = (mnstr_null_t *)(chr->trgt.p);
	c = dun->map.chr.mjr[p->y][p->x];

	if( c == FACE_MJR_NULL ){
		fight_throw( chr, NULL, NULL );
	} else if( c == FACE_MJR_MBR ){
		chr_t	*chr2;

		chr2 = get_mbr( p->x, p->y );
		if( chr2 == NULL )
			return;

		set_chr_act( chr, ACT_KIND_MBR_THROW,
				NULL, NULL,
				0, 0 );
		mark_mbr( chr, chr2, DIST_NEAR );
		fight_throw( chr, chr2, NULL );
	} else {
		mnstr_t	*mns;

		mns = get_mnstr( p->x, p->y );
		if( mns == NULL )
			return;

		mark_mnstr_dflt( chr, mns );
		fight_throw( chr, mns, NULL );
	}
}

/***************************************************************
* ふらついているメンバーが肩を貸してもらっているか調べる
* chr_t *chr : キャラクタ
* return : 肩を貸してもらっているなら真
***************************************************************/

bool_t	chk_assist_chr( chr_t *chr )
{
	party_t	*pty = get_party();
	long	i;

	if( chr == NULL )
		return FALSE;
	if( chr->kind != CHR_KIND_MBR )
		return FALSE;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD
				| FLG_STAT_STONE
				| FLG_STAT_PARALYZE
				| FLG_STAT_CONFUSION
				| FLG_STAT_SLEEP
				| FLG_STAT_FAINT ) ){
			continue;
		}
		if( pty->mbr[i]->act.kind != ACT_KIND_MBR_TAIL )
			continue;
		if( pty->mbr[i]->trgt.kind != TRGT_KIND_MBR )
			continue;
		if( (chr_t *)(pty->mbr[i]->trgt.p) != chr )
			continue;
		if( calc_chr_dx( pty->mbr[i], chr ) > 1 )
			continue;
		if( calc_chr_dy( pty->mbr[i], chr ) > 1 )
			continue;

		return TRUE;
	}
	return FALSE;
}

/***************************************************************
* キャラクタが目的地に着いているか調べる
* chr_t *chr : キャラクタ
* return : 目的地に着いているなら真
***************************************************************/

bool_t	chk_adjoin_chr_trgt( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( chk_xx_range() )
		return TRUE;

	if( chr->x != chr->trgt.x )
		return FALSE;
	if( chr->y != chr->trgt.y )
		return FALSE;

	return TRUE;
}

/***************************************************************
* キャラクタをマップから消す
* chr_t *chr : キャラクタ
***************************************************************/

void	clr_map_chr( chr_t *chr )
{
	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( !clip_pos( chr->x, chr->y ) )
		return;

	chr_light_up( chr, FALSE );

	clr_map_chr_dun( chr );

	chr->pre_x = chr->x;
	chr->pre_y = chr->y;
	chr->x = MAP_DEL_X;
	chr->y = MAP_DEL_Y;
}

/***************************************************************
* キャラクタをマップに出す
* chr_t *chr : キャラクタ
***************************************************************/

void	set_map_chr( chr_t *chr )
{
	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( !clip_pos( chr->x, chr->y ) )
		return;

	set_map_chr_dun( chr );

	if( is_mbr( chr ) )
		find_obj( chr->x, chr->y );

	chr_light_up( chr, TRUE );
}

/***************************************************************
* キャラクタのフラグをマップからクリアする
* chr_t *chr : キャラクタ
***************************************************************/

void	clr_map_chr_dun( chr_t *chr )
{
	set_clr_map_chr_dun( chr, FACE_MJR_NULL, FACE_MNR_NULL,
			FLG_NULL );
}

/***************************************************************
* キャラクタのフラグをマップに設定する
* chr_t *chr : キャラクタ
***************************************************************/

void	set_map_chr_dun( chr_t *chr )
{
	set_clr_map_chr_dun( chr, chr->face.mjr, chr->face.mnr,
			chr->flg_map );
}

/***************************************************************
* 指定したキャラクタのフラグをマップに設定する
* chr_t *chr : キャラクタ
* char mjr : メジャー顔文字
* char mnr : マイナー顔文字
* flg_map_t flg : マップ・フラグ
***************************************************************/

void	set_clr_map_chr_dun(
	chr_t *chr, char mjr, char mnr, flg_map_t flg
)
{
	dun_t	*dun = get_dun();
	chr_t	*chr_p;
	long	x, y;
	long	bx, by;
	long	ex, ey;

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( !clip_pos( chr->x, chr->y ) )
		return;

	if( mjr == FACE_MJR_NULL )
		chr_p = NULL;
	else if( mnr == FACE_MNR_NULL )
		chr_p = NULL;
	else
		chr_p = chr;

	bx = get_chr_left( chr->x, chr->dx );
	by = get_chr_top( chr->y, chr->dy );
	ex = get_chr_right( chr->x, chr->dx );
	ey = get_chr_bottom( chr->y, chr->dy );

	for( y = by; y <= ey; y++ ){
		for( x = bx; x <= ex; x++ ){
			if( !clip_pos( x, y ) )
				continue;

			dun->map.chr.mjr[y][x] = mjr;
			dun->map.chr.mnr[y][x] = mnr;
			dun->map.chr.flg[y][x] = flg;
			dun->map.chr_p[y][x] = chr_p;
		}
	}

	if( (chr_p != NULL) && chk_flg( chr->flg_chr, FLG_CHR_HYPER ) )
		set_map_chr_hyper_boss( chr );
}

/***************************************************************
* キャラクタの大型化の状態によってフラグをマップに設定する
* chr_t *chr : キャラクタ
***************************************************************/

void	set_map_chr_hyper_boss( chr_t *chr )
{
	dun_t	*dun = get_dun();
	flg_map_t	flg;
	long	dx, dy;
	long	x, y;
	long	i;

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( !clip_pos( chr->x, chr->y ) )
		return;

	if( !chk_flg( chr->flg_chr, FLG_CHR_HYPER ) )
		return;
	if( chr->work.hyper_boss <= HYPER_BOSS_NULL )
		return;
	if( chr->work.hyper_boss > HYPER_BOSS_PERFECT )
		return;

	flg = FLG_MAP_CHR_INVISIBLE;

	for( dy = -1; dy <= +1; dy++ ){
		for( dx = -1; dx <= +1; dx++ ){
			x = chr->x + dx;
			y = chr->y + dy;

			if( !clip_pos( x, y ) )
				continue;

			if( ((dx == 0) || (dy == 0)) && (dx != dy) )
				dun->map.chr.flg[y][x] |= flg;
			else
				dun->map.chr.flg[y][x] &= ~flg;
		}
	}

	for( i = HYPER_BOSS_PERFECT; i >= HYPER_BOSS_NORMAL; i-- ){
		if( i == chr->work.hyper_boss )
			break;

		x = MAP_DEL_X;
		y = MAP_DEL_Y;

		switch( (hyper_boss_t)i ){
		case HYPER_BOSS_NULL:
		case HYPER_BOSS_NORMAL:
			break;
		case HYPER_BOSS_NW:
			x = chr->x - 1;
			y = chr->y - 1;
			break;
		case HYPER_BOSS_SE:
			x = chr->x + 1;
			y = chr->y + 1;
			break;
		case HYPER_BOSS_NE:
			x = chr->x + 1;
			y = chr->y - 1;
			break;
		case HYPER_BOSS_SW:
			x = chr->x - 1;
			y = chr->y + 1;
			break;
		case HYPER_BOSS_PERFECT:
			break;
		}

		if( !clip_pos( x, y ) )
			continue;

		dun->map.chr.flg[y][x] |= flg;
	}
}

/***************************************************************
* キャラクタを移動
* chr_t *chr : キャラクタ
***************************************************************/

void	move_chr( chr_t *chr )
{
	rate_t	rate;

	if( chr == NULL )
		return;
	if( !clip_pos( chr->x, chr->y ) )
		return;

	for( rate = get_move_rate( chr ); rate > _100_PERCENT;
			rate -= _100_PERCENT ){
		move_chr_sub( chr );
	}

	if( (rate > MODIFIED_MIN_RATE) && rate_randm( rate ) )
		move_chr_sub( chr );
}

/***************************************************************
* キャラクタの移動の種類を選択して移動
* chr_t *chr : キャラクタ
***************************************************************/

void	move_chr_sub( chr_t *chr )
{
	move_kind_t kind;

	if( chr == NULL )
		return;
	if( !clip_pos( chr->x, chr->y ) )
		return;

	chk_chr_force_move( chr );

	kind = chr->move.force_kind;
	chr->move.force_kind = MOVE_KIND_NULL;
	if( kind == MOVE_KIND_NULL )
		kind = get_move_kind_rand( chr );

	switch( kind ){
	case MOVE_KIND_NULL:
	case MOVE_KIND_MAX_N:
		break;
	case MOVE_KIND_STOP:
		break;
	case MOVE_KIND_STD:
		move_chr_std( chr );
		break;
	case MOVE_KIND_STAGGER:
		move_chr_stagger( chr );
		break;
	case MOVE_KIND_TOWNER:
		move_chr_towner( chr );
		break;
	case MOVE_KIND_WANDER:
		move_chr_wander( chr );
		break;
	}

	/* マップの端からの、はみ出しチェック */

	if( clip_pos( chr->x, chr->y ) ){
		long	x, y;

		x = chr->x;
		y = chr->y;
		clr_map_chr( chr );
		chr->x = x;
		chr->y = y;

		if( chr->x < (0 + 1) )
			chr->x = (0 + 1);
		if( chr->y < (0 + 1) )
			chr->y = (0 + 1);

		if( chr->x > (MAP_MAX_X - 2) )
			chr->x = (MAP_MAX_X - 2);
		if( chr->y > (MAP_MAX_Y - 2) )
			chr->y = (MAP_MAX_Y - 2);

		set_map_chr( chr );
	}

	/* マップ・イベントのチェック */

	if( is_mbr( chr ) )
		chk_map_event( chr->x, chr->y );
}

/***************************************************************
* 通常のキャラクタの移動
* chr_t *chr : キャラクタ
***************************************************************/

void	move_chr_std( chr_t *chr )
{
	dun_t	*dun;
	long	x, y;
	long	pre_x, pre_y;
	long	dx, dy;
	long	nx, ny;

	if( chr == NULL )
		return;

	if( chk_flg( chr->stat, FLG_STAT_CAUGHT ) )
		return;

	if( is_mbr( chr ) ){
		move_chr_mbr( chr );
		return;
	}

	dun = get_dun();

	/* 元居た場所をクリア */
	x = chr->x;
	y = chr->y;
	pre_x = chr->pre_x;
	pre_y = chr->pre_y;
	clr_map_chr( chr );
	chr->x = x;
	chr->y = y;
	chr->pre_x = pre_x;
	chr->pre_y = pre_y;

	dx = chr->trgt.x - chr->x;
	dy = chr->trgt.y - chr->y;
	nx = x;
	ny = y;
	do {
		if( (dx == +-0) && (dy == +-0) )
			break;
		if( chk_move_chr_dir( chr, &nx, &ny ) )
			break;
		if( chk_move_chr_far_axis( chr, &nx, &ny ) )
			break;
		if( chk_move_chr_cross_axis( chr, &nx, &ny ) )
			break;

		nx = x;
		ny = y;
		break;
	} while( 0 );

	/* ペットと場所を入れ替わる */

	nx = x + sgn_l( nx - x );
	ny = y + sgn_l( ny - y );

	if( ((nx != x) || (ny != y)) && can_move_chr( chr, nx, ny ) ){
		if( chk_flg( dun->map.chr.flg[ny][nx], FLG_MAP_CHR_NPC ) ){
			chr_t	*npc;

			npc = get_pet( nx, ny );
			if( npc != NULL ){
				clr_map_chr( npc );
				npc->x = x;
				npc->y = y;
				set_map_chr( npc );
			}
		}

		x = nx;
		y = ny;
	}

	chr->x = x;
	chr->y = y;
	set_map_chr( chr );
}

/***************************************************************
* 通常のメンバーの移動
* chr_t *chr : キャラクタ
***************************************************************/

void	move_chr_mbr( chr_t *chr )
{
	dun_t	*dun;
	long	x, y;
	long	nx, ny;
	long	dx, dy;

	if( chr == NULL )
		return;

	if( chk_flg( chr->stat, FLG_STAT_CAUGHT ) )
		return;

	dun = get_dun();

	/* 元居た場所をクリア */
	x = chr->x;
	y = chr->y;
	clr_map_chr( chr );
	chr->x = x;
	chr->y = y;

	dx = chr->trgt.x - x;
	dy = chr->trgt.y - y;

	nx = x + sgn_l( dx );
	ny = y + sgn_l( dy );

	if( !can_move_chr( chr, nx, ny ) ){
		if( dx && dy ){
			if( labs( dx ) > labs( dy ) ){
				if( chk_auto_mnstr(
						chr, nx, y, x, ny ) ){
					dx = 0;
					dy = 0;
				} else if( can_move_chr( chr, nx, y ) ){
					dy = 0;
				} else if( can_move_chr( chr, x, ny ) ){
					dx = 0;
				} else if( chk_auto_door(
						chr, nx, y, x, ny ) ){
					dx = 0;
					dy = 0;
				}
			} else {
				if( chk_auto_mnstr(
						chr, x, ny, nx, y ) ){
					dx = 0;
					dy = 0;
				} else if( can_move_chr( chr, x, ny ) ){
					dx = 0;
				} else if( can_move_chr( chr, nx, y ) ){
					dy = 0;
				} else if( chk_auto_door(
						chr, x, ny, nx, y ) ){
					dx = 0;
					dy = 0;
				}
			}
		} else if( dx ){
			if( chk_auto_mnstr(
					chr, nx, y - 1, nx, y + 1 ) ){
				dx = 0;
				dy = 0;
			} else if( can_move_chr( chr, nx, y - 1 ) ){
				dy = -1;
			} else if( can_move_chr( chr, nx, y + 1 ) ){
				dy = +1;
			} else if( chk_auto_door(
					chr, nx, y - 1, nx, y + 1 ) ){
				dx = 0;
				dy = 0;
			}
		} else if( dy ){
			if( chk_auto_mnstr(
					chr, x - 1, ny, x + 1, ny ) ){
				dx = 0;
				dy = 0;
			} else if( can_move_chr( chr, x - 1, ny ) ){
				dx = -1;
			} else if( can_move_chr( chr, x + 1, ny ) ){
				dx = +1;
			} else if( chk_auto_door(
					chr, x - 1, ny, x + 1, ny ) ){
				dx = 0;
				dy = 0;
			}
		}
	}

	nx = x + sgn_l( dx );
	ny = y + sgn_l( dy );
	if( can_move_chr( chr, nx, ny ) ){
		if( chk_flg( dun->map.chr.flg[ny][nx], FLG_MAP_CHR_NPC ) ){
			chr_t	*npc;

			npc = get_pet( nx, ny );
			if( npc != NULL ){
				clr_map_chr( npc );
				npc->x = x;
				npc->y = y;
				set_map_chr( npc );
			}
		}

		x = nx;
		y = ny;
	}

	chr->x = x;
	chr->y = y;
	set_map_chr( chr );
}

/***************************************************************
* キャラクタの移動チェック (直線的)
* chr_t *chr : キャラクタ
* long *nx : X 軸の移動方向を返す
* long *ny : Y 軸の移動方向を返す
* return : 移動可能か?
***************************************************************/

bool_t	chk_move_chr_dir( chr_t *chr, long *nx, long *ny )
{
	long	x, y;
	long	dx, dy;

	if( chr == NULL )
		return FALSE;

	dx = chr->trgt.x - chr->x;
	dy = chr->trgt.y - chr->y;
	x = chr->x + sgn_l( dx );
	y = chr->y + sgn_l( dy );

	if( (x == chr->pre_x) && (y == chr->pre_y) )
		return FALSE;

	do {
		if( can_move_chr( chr, x, y ) )
			break;
		if( chk_auto_door( chr, x, y, x, y ) ){
			x = chr->x;
			y = chr->y;
			break;
		}

		return FALSE;
	} while( 0 );

	if( nx != NULL )
		*nx = x;
	if( ny != NULL )
		*ny = y;

	return TRUE;
}

/***************************************************************
* キャラクタの移動チェック (水平または垂直)
* chr_t *chr : キャラクタ
* long *nx : X 軸の移動方向を返す
* long *ny : Y 軸の移動方向を返す
* return : 移動可能か?
***************************************************************/

bool_t	chk_move_chr_far_axis( chr_t *chr, long *nx, long *ny )
{
	long	x, y;
	long	dx, dy;

	if( chr == NULL )
		return FALSE;

	dx = chr->trgt.x - chr->x;
	dy = chr->trgt.y - chr->y;
	if( labs( dx ) > labs( dy ) ){
		x = chr->x + sgn_l( dx );
		y = chr->y;
	} else {
		x = chr->x;
		y = chr->y + sgn_l( dy );
	}

	if( (x == chr->pre_x) && (y == chr->pre_y) )
		return FALSE;

	do {
		if( can_move_chr( chr, x, y ) )
			break;
		if( chk_auto_door( chr, x, y, x, y ) ){
			x = chr->x;
			y = chr->y;
			break;
		}

		return FALSE;
	} while( 0 );

	if( nx != NULL )
		*nx = x;
	if( ny != NULL )
		*ny = y;

	return TRUE;
}

/***************************************************************
* キャラクタの移動チェック (直角に交わる軸線上をスキャン)
* chr_t *chr : キャラクタ
* long *nx : X 軸の移動方向を返す
* long *ny : Y 軸の移動方向を返す
* return : 移動可能か?
***************************************************************/

bool_t	chk_move_chr_cross_axis( chr_t *chr, long *nx, long *ny )
{
	long	dx, dy;
	long	lm, lp;
	bool_t	flg_m, flg_p;

	if( chr == NULL )
		return FALSE;

	dx = chr->trgt.x - chr->x;
	dy = chr->trgt.y - chr->y;
	if( labs( dx ) < labs( dy ) ){
		flg_m = chk_move_chr_scan_x( chr, -1, &lm );
		flg_p = chk_move_chr_scan_x( chr, +1, &lp );

		if( flg_m && flg_p ){
			if( lm < lp ){
				if( nx != NULL )
					*nx = chr->x - 1;
				if( ny != NULL )
					*ny = chr->y;
			} else {
				if( nx != NULL )
					*nx = chr->x + 1;
				if( ny != NULL )
					*ny = chr->y;
			}

			return TRUE;
		} else if( flg_m ){
			if( nx != NULL )
				*nx = chr->x - 1;
			if( ny != NULL )
				*ny = chr->y;

			return TRUE;
		} else if( flg_p ){
			if( nx != NULL )
				*nx = chr->x + 1;
			if( ny != NULL )
				*ny = chr->y;

			return TRUE;
		} else {
			return FALSE;
		}
	} else {
		flg_m = chk_move_chr_scan_y( chr, -1, &lm );
		flg_p = chk_move_chr_scan_y( chr, +1, &lp );

		if( flg_m && flg_p ){
			if( lm < lp ){
				if( nx != NULL )
					*nx = chr->x;
				if( ny != NULL )
					*ny = chr->y - 1;
			} else {
				if( nx != NULL )
					*nx = chr->x;
				if( ny != NULL )
					*ny = chr->y + 1;
			}

			return TRUE;
		} else if( flg_m ){
			if( nx != NULL )
				*nx = chr->x;
			if( ny != NULL )
				*ny = chr->y - 1;

			return TRUE;
		} else if( flg_p ){
			if( nx != NULL )
				*nx = chr->x;
			if( ny != NULL )
				*ny = chr->y + 1;

			return TRUE;
		} else {
			return FALSE;
		}
	}

	return FALSE;
}

/***************************************************************
* キャラクタの移動チェック (水平方向をスキャンする)
* chr_t *chr : キャラクタ
* long sx : 方向
* long *lx : 距離を返す
* return : 移動可能か?
***************************************************************/

bool_t	chk_move_chr_scan_x( chr_t *chr, long sx, long *lx )
{
	long	x;
	long	dy;
	long	i;

	if( chr == NULL )
		return FALSE;

	dy = sgn_l( chr->trgt.y - chr->y );
	sx = sgn_l( sx );

	x = chr->x + sx;
	for( i = 0; i < AREA_MAX_X; i++ ){
		if( !can_move_chr( chr, x, chr->y ) )
			return FALSE;

		if( can_move_chr( chr, x, chr->y + dy ) ){
			if( lx != NULL )
				*lx = labs( x - chr->x );

			return TRUE;
		}

		x += sx;
	}

	return FALSE;
}

/***************************************************************
* キャラクタの移動チェック (垂直方向をスキャンする)
* chr_t *chr : キャラクタ
* long sy : 方向
* long *ly : 距離を返す
* return : 移動可能か?
***************************************************************/

bool_t	chk_move_chr_scan_y( chr_t *chr, long sy, long *ly )
{
	long	y;
	long	dx;
	long	i;

	if( chr == NULL )
		return FALSE;

	dx = sgn_l( chr->trgt.x - chr->x );
	sy = sgn_l( sy );

	y = chr->y + sy;
	for( i = 0; i < AREA_MAX_Y; i++ ){
		if( !can_move_chr( chr, chr->x, y ) )
			return FALSE;

		if( can_move_chr( chr, chr->x + dx, y ) ){
			if( ly != NULL )
				*ly = labs( y - chr->y );

			return TRUE;
		}

		y += sy;
	}

	return FALSE;
}

/***************************************************************
* 強制的なキャラクタの移動
* chr_t *chr : キャラクタ
***************************************************************/

void	chk_chr_force_move( chr_t *chr )
{
	if( chr == NULL )
		return;

	if( chk_chr_stagger( chr ) )
		chr->move.force_kind = MOVE_KIND_STAGGER;
	if( chr->trgt.kind == TRGT_KIND_QUEUE )
		chr->move.force_kind = MOVE_KIND_STD;
}

/***************************************************************
* キャラクタがふらつくか調べる
* chr_t *chr : キャラクタ
* retrun : ふらつくなら真
***************************************************************/

bool_t	chk_chr_stagger( chr_t *chr )
{
	if( chk_chr_stagger_sub( chr, FLG_STAT_CONFUSION,
			STAGGER_RATE_CHR_CONFUSION ) ){
		return TRUE;
	}
	if( chk_chr_stagger_sub( chr, FLG_STAT_BLIND,
			STAGGER_RATE_CHR_BLIND ) ){
		return TRUE;
	}
	if( chk_chr_stagger_sub( chr, FLG_STAT_DRUNK,
			STAGGER_RATE_CHR_DRUNK ) ){
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* キャラクタがふらつくか個別に調べる
* chr_t *chr : キャラクタ
* retrun : ふらつくなら真
***************************************************************/

bool_t	chk_chr_stagger_sub( chr_t *chr, flg_stat_t flg, long rate )
{
	if( chr == NULL )
		return FALSE;

	if( !chk_flg( chr->stat, flg ) )
		return FALSE;
	if( !rate_randm( rate ) )
		return FALSE;
	if( chk_assist_chr( chr ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* キャラクタのふらつき移動
* chr_t *chr : キャラクタ
***************************************************************/

void	move_chr_stagger( chr_t *chr )
{
	long	x, y;
	long	dx, dy;
	long	i;

	if( chr == NULL )
		return;

	if( chk_flg( chr->stat, FLG_STAT_CAUGHT ) )
		return;

	/* 元居た場所をクリア */
	x = chr->x;
	y = chr->y;
	clr_map_chr( chr );
	chr->x = x;
	chr->y = y;

	for( i = 0; i < LOOP_MAX_100; i++ ){
		dx = randm( 3 ) - 1;
		dy = randm( 3 ) - 1;
		if( can_move_chr( chr, x + dx, y + dy ) ){
			x += dx;
			y += dy;
			break;
		}
	}

	chr->x = x;
	chr->y = y;
	set_map_chr( chr );
}

/***************************************************************
* キャラクタの徘徊移動
* chr_t *chr : キャラクタ
***************************************************************/

void	move_chr_wander( chr_t *chr )
{
	move_chr_towner( chr );
}

/***************************************************************
* 街の住人の移動
* chr_t *chr : キャラクタ
***************************************************************/

void	move_chr_towner( chr_t *chr )
{
	long	x, y;
	long	nx, ny;
	long	i;

	if( chr == NULL )
		return;

	if( !rate_randm( TOWNER_MOVE_RATE ) )
		return;

	if( chr->act.kind == ACT_KIND_DOOR_OPEN ){
		move_chr_std( chr );
		return;
	}

	/* 元居た場所をクリア */
	x = chr->x;
	y = chr->y;
	clr_map_chr( chr );
	chr->x = x;
	chr->y = y;

	if( rate_randm( TOWNER_TURN_DIR_RATE ) )
		turn_dir_towner( chr );

	for( i = 0; i < LOOP_MAX_200; i++ ){
		if( chr->work.towner_dx == 0 ){
			if( chr->work.towner_dy == 0 ){
				turn_dir_towner( chr );
				continue;
			}
		}

		if( can_move_chr_towner( chr, 2 ) )
			if( can_move_chr_towner( chr, 1 ) )
				break;

		turn_dir_towner( chr );
	}

	nx = x + sgn_l( chr->work.towner_dx ) * 1;
	ny = y + sgn_l( chr->work.towner_dy ) * 1;
	if( can_move_chr( chr, nx, ny ) ){
		x = nx;
		y = ny;
	}

	chr->x = x;
	chr->y = y;
	set_map_chr( chr );
}

/***************************************************************
* 街の住人の移動方向を変える
* chr_t *chr : キャラクタ
***************************************************************/

void	turn_dir_towner( chr_t *chr )
{
	chr->work.towner_dx = randm( 3 ) - 1;
	chr->work.towner_dy = randm( 3 ) - 1;
}

/***************************************************************
* 移動の種類をランダムで返す
* chr_t *chr : キャラクタ
* return : 移動の種類
***************************************************************/

move_kind_t	get_move_kind_rand( chr_t *chr )
{
	move_ls_kind_t	ls_kind;
	ratio_t	sum, n;
	move_kind_t	ret;
	long	i;

	if( chr == NULL )
		return MOVE_KIND_NULL;

	/* 移動グループの切り替え */

	if( is_mbr( chr ) ){
		ls_kind = MOVE_LS_KIND_FIND;
	} else if( chr->attitude == ATTITUDE_MATE ){
		ls_kind = MOVE_LS_KIND_FIND;
	} else {
		/* メンバーを見つけているかどうかで切り替える */
		if( chk_flg_work_find_mbr( chr ) )
			ls_kind = MOVE_LS_KIND_FIND;
		else
			ls_kind = MOVE_LS_KIND_NOT_FIND;
	}

	/* 合計値を求める */

	sum = 0;
	for( i = 0; i < MOVE_LS_MAX_N; i++ ){
		if( chr->move.ls[ls_kind][i].kind == MOVE_KIND_NULL )
			break;

		sum += chr->move.ls[ls_kind][i].ratio;
	}
	if( sum <= 0 )
		return MOVE_KIND_NULL;

	/* ランダムに決める */

	n = randm( sum );

	/* 頭出し */

	ret = MOVE_KIND_NULL;
	sum = 0;
	for( i = 0; i < MOVE_LS_MAX_N; i++ ){
		if( chr->move.ls[ls_kind][i].kind == MOVE_KIND_NULL )
			break;

		sum += chr->move.ls[ls_kind][i].ratio;
		if( n < sum ){
			ret = chr->move.ls[ls_kind][i].kind;
			break;
		}
	}

	return ret;
}

/***************************************************************
* キャラクタが自動でドアを開けるか調べる
* chr_t *chr : キャラクタ
* long x1 : ドアの X座標 1
* long y1 : ドアの Y座標 1
* long x2 : ドアの X座標 2
* long y2 : ドアの Y座標 2
* return : 自動でドアを開けるなら真
***************************************************************/

bool_t	chk_auto_door( chr_t *chr, long x1, long y1, long x2, long y2 )
{
	if( is_mbr( chr ) )
		return chk_auto_door_mbr( chr, x1, y1, x2, y2 );
	if( chr->kind == CHR_KIND_MNSTR )
		return chk_auto_door_mnstr( chr, x1, y1, x2, y2 );

	return FALSE;
}

/***************************************************************
* キャラクタが移動できるか調べる
* chr_t *chr : キャラクタ
* long x : X座標
* long y : Y座標
* return : 移動できるなら真
***************************************************************/

bool_t	can_move_chr( chr_t *chr, long x, long y )
{
	if( chr == NULL )
		return FALSE;

	return can_move_chr_pos( chr, x, y, chr->dx, chr->dy );
}

/***************************************************************
* キャラクタが移動できるか調べる(キャラクタのサイズ指定あり)
* chr_t *chr : キャラクタ
* long x : X座標
* long y : Y座標
* long dx : 横サイズ
* long dy : 縦サイズ
* return : 移動できるなら真
***************************************************************/

bool_t	can_move_chr_pos( chr_t *chr, long x, long y, long dx, long dy )
{
	long	bx, by;
	long	ex, ey;
	long	xx, yy;

	if( !clip_pos( x, y ) )
		return FALSE;

	bx = get_chr_left( x, dx );
	by = get_chr_top( y, dy );
	ex = get_chr_right( x, dx );
	ey = get_chr_bottom( y, dy );

	for( yy = by; yy <= ey; yy++ ){
		for( xx = bx; xx <= ex; xx++ ){
			if( !can_move_chr_sub( chr, xx, yy ) )
				return FALSE;
		}
	}

	return TRUE;
}

/***************************************************************
* キャラクタが移動できるか実際に調べる
* chr_t *chr : キャラクタ
* long x : X座標
* long y : Y座標
* return : 移動できるなら真
***************************************************************/

bool_t	can_move_chr_sub( chr_t *chr, long x, long y )
{
	dun_t	*dun = get_dun();

	/* マップの範囲外 */

	if( !clip_pos( x, y ) )
		return FALSE;

	if( x < (0 + 1) )
		return FALSE;
	if( y < (0 + 1) )
		return FALSE;

	if( x >= (MAP_MAX_X - 1) )
		return FALSE;
	if( y >= (MAP_MAX_Y - 1) )
		return FALSE;

	do {
		if( dun->map.obj.mjr[y][x] != FACE_MJR_TRAP )
			break;
		if( dun->map.chr.mjr[y][x] != FACE_MJR_NULL )
			break;
		if( chr != NULL ){
			if( chr->trgt.kind != TRGT_KIND_POS )
				break;
			if( chr->trgt.true_x != x )
				break;
			if( chr->trgt.true_y != y )
				break;
		}

		/* わざと罠に掛かりに行く時 */
		return TRUE;
	} while( 0 );

	do {
		if( dun->map.obj.mjr[y][x] != FACE_MJR_TRAP )
			break;
		if( chk_through_trap( x, y ) )
			break;
		if( chr != NULL ){
			if( is_mbr( chr ) ){
				if( chk_flg( dun->map.obj.flg[y][x],
						FLG_MAP_OBJ_LOOK_FLOOR ) ){
					break;
				}
				if( chk_flg( dun->map.obj.flg[y][x],
						FLG_MAP_OBJ_LOOK_WALL ) ){
					break;
				}
			}
			if( chk_flg( chr->stat, FLG_STAT_FLY ) )
				break;
			if( !chk_flg( chr->flg_chr, FLG_CHR_AVOID_TRAP ) )
				break;
		}

		/* 自動的に罠を避ける時 */
		return FALSE;
	} while( 0 );

	do {
		if( !chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_PASS ) )
			break;
		if( dun->map.chr.mjr[y][x] != FACE_MJR_NULL )
			break;

		/* 普通に通れる時 */
		return TRUE;
	} while( 0 );

	do {
		if( chr != NULL ){
			if( !chk_flg( chr->stat, FLG_STAT_PASSWALL ) )
				break;
		}
		if( dun->map.chr.mjr[y][x] != FACE_MJR_NULL )
			break;

		/* 壁抜け能力が有る場合 */
		return TRUE;
	} while( 0 );

	do {
		pet_t	*pet;

		if( !chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_PASS ) )
			break;
		if( !chk_flg( dun->map.chr.flg[y][x], FLG_MAP_CHR_NPC ) )
			break;
		if( chr == NULL )
			break;
		if( !is_mbr( chr ) )
			break;
		pet = get_pet( x, y );
		if( pet == NULL )
			break;
		if( pet->dx != 1 )
			break;
		if( pet->dy != 1 )
			break;

		/* ペットと入れかわる時 */
		return TRUE;
	} while( 0 );

	return FALSE;
}

/***************************************************************
* 街の住民が現在の方向に移動できるか調べる
* chr_t *chr : キャラクタ
* long d : 障害物までの距離
* return : 移動できるなら真
***************************************************************/

bool_t	can_move_chr_towner( chr_t *chr, long d )
{
	long	x, y;

	x = chr->x + sgn_l( chr->work.towner_dx ) * d;
	y = chr->y + sgn_l( chr->work.towner_dy ) * d;

	return can_move_chr( chr, x, y );
}

/***************************************************************
* キャラクタが死ぬ
* chr_t *chr : キャラクタ
* bool_t flg_msg : メッセージを標示するか?
* bool_t flg_add_exp : メンバーに経験値が入るか?
* bool_t flg_chk_game_over : ゲーム・オーバーのチェックをするか?
***************************************************************/

void	die_chr(
	chr_t *chr,
	bool_t flg_msg, bool_t flg_add_exp, bool_t flg_chk_game_over
)
{
	dun_t	*dun = get_dun();
	long	bx, by;
	long	ex, ey;

	if( chr == NULL )
		return;

	if( flg_msg ){
		curs_attrset_chr( chr, -1, TRUE );
		print_msg_mbr( chr, FLG_NULL, MSG_DIE_CHR, chr->name );
		curs_attrset_dflt();
	}

	/* キャラクタが死ぬと座標が無効になるので */
	/* 予め座標を保存しておく */
	bx = get_chr_left( chr->x, chr->dx ) - 1;
	by = get_chr_top( chr->y, chr->dy ) - 1;
	ex = get_chr_right( chr->x, chr->dx ) + 1;
	ey = get_chr_bottom( chr->y, chr->dy ) + 1;

	clr_chr_trgt_act( chr, TRUE );
	release_chr( chr );

	if( chk_save_life( chr ) )
		return;

	chr->abl.hp.n = 0;

	chk_die_boss( chr );

	do {
		if( !flg_add_exp )
			break;
		if( chr->kind != CHR_KIND_MNSTR )
			break;
		if( chr->attitude != ATTITUDE_ENEMY )
			break;
		if( is_pet( chr ) )
			break;
		if( chr->mnstr_tab == NULL )
			break;
		if( get_scene() == SCENE_N_LAST_BOSS )
			break;

		if( chr->work.flg_used_energy_drain )
			fx_cure_exp_party();

		exp_party( calc_mnstr_exp( chr->mnstr_kind, dun->lev ),
				FALSE, TRUE );
	} while( 0 );

	chk_finish_request_chr_dead( chr );

	die_mnstr_drop_item( chr );

	/* 以下の処理の呼ぶ順番に注意 */

	/* 元居た場所をクリア */
	clr_map_chr( chr );

	free_fx_all( &(chr->fx) );

	chr->stat |= FLG_STAT_DEAD;
	draw_mbr_stat( chr );

	lost_trgt( chr );
	lost_fx_chr( chr );

	if( is_mbr( chr ) )
		die_mbr( chr, flg_msg, flg_chk_game_over );
	else if( chr->kind == CHR_KIND_MNSTR )
		die_mnstr( chr, flg_msg );

	draw_map( bx, by, ex - bx + 1, ey - by + 1 );
}

/***************************************************************
* キャラクタが死ぬのを免れるか調べる
* chr_t *chr : キャラクタ
* return : 死なないなら真
***************************************************************/

bool_t	chk_save_life( chr_t *chr )
{
	bool_t	ret;

	if( chr == NULL )
		return FALSE;

	if( chr->kind != CHR_KIND_MBR )
		return FALSE;

	ret = FALSE;

	if( ret ){
		add_hp( chr, +calc_max_hp( chr ), TRUE, TRUE );
		draw_mbr_stat( chr );

		curs_attrset_chr( chr, +1, TRUE );
		print_msg( FLG_NULL, MSG_FX_SAVE_LIFE, chr->name );
		curs_attrset_dflt();
	}

	return ret;
}

/***************************************************************
* アイテムを盗む
* chr_t *chr : キャラクタ
* chr_t *trgt : 盗む相手
* return : 盗めたなら真
***************************************************************/

bool_t	steal( chr_t *chr, chr_t *trgt )
{
	bool_t	flg;
	char	item_name[ITEM_NAME_MAX_BYTE + 1];

	if( chr == NULL )
		return FALSE;
	if( trgt == NULL )
		return FALSE;

	if( calc_chr_dx( chr, trgt ) > 1 )
		return FALSE;
	if( calc_chr_dy( chr, trgt ) > 1 )
		return FALSE;

	flg = roll( chr, ABL_KIND_THI, ABL_KIND_DEX,
			trgt, ABL_KIND_THI, ABL_KIND_DEX );
	if( !flg ){
		print_msg( FLG_NULL, MSG_STEAL_ITEM_FAILURE, chr->name );
		return FALSE;
	}

	flg = FALSE;
	if( is_mbr( chr ) ){
		if( is_mbr( trgt ) ){
			flg = mbr_steal_mbr( chr, trgt, item_name );
		} else if( trgt->kind == CHR_KIND_MNSTR ){
			flg = mbr_steal_mnstr( chr, trgt, item_name );
		}
	} else if( chr->kind == CHR_KIND_MNSTR ){
		if( is_mbr( trgt ) ){
			flg = mnstr_steal_mbr( chr, trgt, item_name );
		} else if( trgt->kind == CHR_KIND_MNSTR ){
			flg = mnstr_steal_mnstr( chr, trgt, item_name );
		}
	}
	if( !flg ){
		print_msg( FLG_NULL, MSG_STEAL_ITEM_FAILURE, chr->name );
		return FALSE;
	}

	/* 成功 */

	curs_attrset_chr( chr, +1, FALSE );
	print_msg( FLG_NULL, MSG_STEAL_ITEM_1, chr->name, trgt->name );
	curs_attrset_chr( chr, +1, FALSE );
	print_msg( FLG_NULL, MSG_STEAL_ITEM_2, chr->name, item_name );
	curs_attrset_dflt();

	return TRUE;
}

/***************************************************************
* メンバーがメンバーからアイテムを盗む
* mbr_t *mbr : 盗む側のメンバー
* chr_t *trgt : 盗まれる側のメンバー
* char *item_name : 盗んだアイテムの名前を返す
* return : 盗めたなら真
***************************************************************/

bool_t	mbr_steal_mbr( mbr_t *mbr, chr_t *trgt, char *item_name )
{
	item_t	*item;

	if( mbr == NULL )
		return FALSE;
	if( trgt == NULL )
		return FALSE;
	if( item_name == NULL )
		return FALSE;
	if( trgt->kind != CHR_KIND_MBR )
		return FALSE;

	item = get_item_mbr_randm( trgt->ls_mbr_n );
	if( item == NULL )
		return FALSE;

	str_nz_cpy( item_name, item->name, ITEM_NAME_MAX_BYTE );

	if( !hand_item( mbr, trgt, item, item->n ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* メンバーがモンスターからアイテムを盗む
* mbr_t *mbr : 盗む側のメンバー
* chr_t *trgt : 盗まれる側のモンスター
* char *item_name : 盗んだアイテムの名前を返す
* return : 盗めたなら真
***************************************************************/

bool_t	mbr_steal_mnstr( mbr_t *mbr, chr_t *trgt, char *item_name )
{
	dun_t	*dun = get_dun();
	long	n;
	mnstr_item_n_t	*a;
	item_t	*item;
	long	i;

	if( mbr == NULL )
		return FALSE;
	if( trgt == NULL )
		return FALSE;
	if( item_name == NULL )
		return FALSE;
	if( trgt->kind != CHR_KIND_MNSTR )
		return FALSE;

	if( chk_flg( trgt->work.flg, FLG_WORK_STEAL_END ) )
		return FALSE;

	n = 1;
	a = NULL;
	for( i = 0; i < MNSTR_ITEM_N_MAX_N; i++ ){
		mnstr_item_n_t	*aa;

		aa = &(trgt->mnstr_tab->item_n[i]);
		if( aa->kind == ITEM_KIND_NULL )
			break;

		if( !rate_randm( aa->rate ) )
			continue;

		if( per_randm( n ) ){
			a = aa;
			n++;
		}
	}
	if( a == NULL )
		return FALSE;

	item = make_item_sel( a->kind, a->k1, a->k2, a->k3, dun->lev );
	if( item == NULL )
		return FALSE;

	str_nz_cpy( item_name, item->name, ITEM_NAME_MAX_BYTE );

	if( !give_mbr_item( mbr, item, FALSE ) ){
		del_item( item );
		return FALSE;
	}

	/* 成功 */

	trgt->work.flg |= FLG_WORK_STEAL_END;

	return TRUE;
}

/***************************************************************
* モンスターがメンバーからアイテムを盗む
* mbr_t *mbr : 盗む側のモンスター
* chr_t *trgt : 盗まれる側のメンバー
* char *item_name : 盗んだアイテムの名前を返す
* return : 盗めたなら真
***************************************************************/

bool_t	mnstr_steal_mbr( mnstr_t *mnstr, chr_t *trgt, char *item_name )
{
	if( mnstr == NULL )
		return FALSE;
	if( trgt == NULL )
		return FALSE;
	if( item_name == NULL )
		return FALSE;
	if( trgt->kind != CHR_KIND_MBR )
		return FALSE;

	return FALSE;
}

/***************************************************************
* モンスターがモンスターからアイテムを盗む
* mbr_t *mbr : 盗む側のモンスター
* chr_t *trgt : 盗まれる側のモンスター
* char *item_name : 盗んだアイテムの名前を返す
* return : 盗めたなら真
***************************************************************/

bool_t	mnstr_steal_mnstr( mnstr_t *mnstr, chr_t *trgt, char *item_name )
{
	if( mnstr == NULL )
		return FALSE;
	if( trgt == NULL )
		return FALSE;
	if( item_name == NULL )
		return FALSE;
	if( trgt->kind != CHR_KIND_MNSTR )
		return FALSE;

	return FALSE;
}

/***************************************************************
* 自動的にドアを開ける
* chr_t *chr : キャラクタ
* long x : ドアの X 座標
* long y : ドアの Y 座標
***************************************************************/

void	act_chr_auto_door( chr_t *chr, long x, long y )
{
	door_t	*dr;

	if( chr == NULL )
		return;

	dr = get_door( x, y );
	if( dr == NULL )
		return;

	if( chr->x < (dr->x - 1) )
		return;
	if( (dr->x + dr->dx - 1 + 1) < chr->x )
		return;
	if( chr->y < (dr->y - 1) )
		return;
	if( (dr->y + dr->dy - 1 + 1) < chr->y )
		return;

	chr_open_door( chr, dr->n );
}

/***************************************************************
* キャラクタがドアを開ける
* chr_t *chr : キャラクタ
* long dr_n : ドアの番号
* return : 開けたなら真
***************************************************************/

bool_t	chr_open_door( chr_t *chr, long dr_n )
{
	dun_t	*dun = get_dun();
	flg_map_t	flg;

	if( chr == NULL )
		return FALSE;

	lost_trgt( chr );
	clr_chr_trgt_act( chr, FALSE );

	if( chk_discount_door( &(dun->door[dr_n]) ) ){
		if( chk_discount() ){
			if( !chk_discount_open() ){
				mark_discount_queue( chr );
				return FALSE;
			}
		}
	}

	if( dun->lev == 0 ){
		if( chr->kind != CHR_KIND_MBR ){
			chr_enter_door( chr, &(dun->door[dr_n]) );
			return TRUE;
		}
	}

	if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_SHOP ) ){
		if( is_mbr( chr ) ){
			open_door_shop( dr_n );
			return TRUE;
		}
	}

	if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_OPEN ) )
		return FALSE;

	open_door( dr_n );

	if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_JAMMED )
			&& !chk_flg( dun->door[dr_n].flg,
			FLG_DOOR_OPEN ) ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_DOOR_OPEN_JAMMED );

		return FALSE;
	} else if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_GATE ) ){
		if( rate_randm( PRINT_ERR_DOOR_GATE_RATE ) )
			print_msg( FLG_NULL, MSG_ERR_DOOR_GATE );

		return FALSE;
	} else if( !chk_flg( dun->door[dr_n].flg, FLG_DOOR_OPEN ) ){
		return FALSE;
	}

	flg = dun->map.chr.flg[chr->y][chr->x];
	if( is_mbr( chr ) || is_pet( chr )
			|| chk_flg( flg, FLG_MAP_CHR_FIND ) ){
		call_game_sound_play( SOUND_KIND_DOOR_OPEN, 1 );
	}
	print_msg_mbr( chr, FLG_NULL, MSG_DOOR_OPEN, chr->name );

	return TRUE;
}

/***************************************************************
* キャラクタがドアを閉める
* chr_t *chr : キャラクタ
* long dr_n : ドアの番号
* return : 閉めたなら真
***************************************************************/

bool_t	chr_close_door( chr_t *chr, long dr_n )
{
	dun_t	*dun = get_dun();
	flg_map_t	flg;

	if( chr == NULL )
		return FALSE;

	clr_chr_trgt_act( chr, FALSE );

	if( !chk_flg( dun->door[dr_n].flg, FLG_DOOR_OPEN ) )
		return FALSE;

	close_door( dr_n );

	if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_BROKEN ) ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_DOOR_CLOSE_BROKEN );
		return FALSE;
	} else if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_JAMMED ) ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_DOOR_CLOSE_JAMMED );
		return FALSE;
	} else if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_OPEN ) ){
		return FALSE;
	}

	flg = dun->map.chr.flg[chr->y][chr->x];
	if( is_mbr( chr ) || is_pet( chr )
			|| chk_flg( flg, FLG_MAP_CHR_FIND ) ){
		call_game_sound_play( SOUND_KIND_DOOR_CLOSE, 1 );
	}
	print_msg_mbr( chr, FLG_NULL, MSG_DOOR_CLOSE, chr->name );

	return TRUE;
}

/***************************************************************
* キャラクタがドアを固定
* chr_t *chr : キャラクタ
* long dr_n : ドアの番号
* return : 固定したなら真
***************************************************************/

bool_t	chr_jam_door( chr_t *chr, long dr_n )
{
	item_t	*item = NULL;

	if( chr == NULL )
		return FALSE;

	clr_chr_trgt_act( chr, FALSE );

	if( is_mbr( chr ) ){
		item = get_item_mbr( chr->ls_mbr_n, ITEM_KIND_SPIKE );
		if( item == NULL ){
			print_msg_mbr( chr, FLG_NULL, MSG_ERR_DOOR_JAM_SPIKE,
					MSG_SPIKE );
			return FALSE;
		}
	}

	if( !jam_door( dr_n ) )
		return FALSE;

	if( is_mbr( chr ) ){
		print_msg_mbr( chr, FLG_NULL, MSG_DOOR_JAM, chr->name );
		inc_item( item, -1 );
	}

	return TRUE;
}

/***************************************************************
* キャラクタがドアの固定を解除
* chr_t *chr : キャラクタ
* long dr_n : ドアの番号
* return : マークを解除するかどうか
***************************************************************/

bool_t	chr_disarm_door( chr_t *chr, long dr_n )
{
	if( chr == NULL )
		return TRUE;

	if( !chr_roll( chr, ABL_KIND_THI, ABL_KIND_DEX,
			DOOR_DISARM_DIFFICULTY ) ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_DOOR_DISARM_LEV );

		return FALSE;
	}

	if( !disarm_door( dr_n ) )
		return TRUE;

	print_msg_mbr( chr, FLG_NULL, MSG_DOOR_DISARM, chr->name );

	return TRUE;
}

/***************************************************************
* キャラクタがドアの鍵穴を覗く
* chr_t *chr : キャラクタ
* long dr_n : ドアの番号
***************************************************************/

void	chr_peep_door( chr_t *chr, long dr_n )
{
	if( is_mbr( chr ) )
		mbr_peep_door( chr, dr_n );
}

/***************************************************************
* キャラクタがドアを調べる
* chr_t *chr : キャラクタ
* long dr_n : ドアの番号
***************************************************************/

void	chr_chk_door( chr_t *chr, long dr_n )
{
	dun_t	*dun = get_dun();

	if( chr == NULL )
		return;
	if( chr->kind != CHR_KIND_MBR )
		return;

	if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_SHOP ) ){
		char	*name;

		name = get_shop_name( get_shop_n( dun->door[dr_n].mnr ) );
		print_msg( FLG_NULL, MSG_CHK_DOOR_SHOP, name );
	}

	if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_OPEN ) )
		print_msg( FLG_NULL, MSG_CHK_DOOR_OPEN );
	else
		print_msg( FLG_NULL, MSG_CHK_DOOR_CLOSE );

	if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_JAMMED ) )
		print_msg( FLG_NULL, MSG_CHK_DOOR_JAMMED );

	if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_BROKEN ) )
		print_msg( FLG_NULL, MSG_CHK_DOOR_BROKEN );

	dun->door[dr_n].flg |= FLG_DOOR_CHKED;
	dun->door[dr_n].flg &= ~(FLG_DOOR_SECRET);

	set_face_door( dr_n );
	draw_door( dr_n );

	clr_chr_trgt_act( chr, FALSE );
}

/***************************************************************
* キャラクタが罠を解除
* chr_t *chr : キャラクタ
* trap_t *trap : 罠
* return : マークを解除するかどうか
***************************************************************/

bool_t	chr_disarm_trap( chr_t *chr, trap_t *trap )
{
	return( chr_disarm_trap_abl( chr, trap,
			ABL_KIND_THI, ABL_KIND_DEX ) );
}

/***************************************************************
* キャラクタが罠を解除 (能力値の指定あり)
* chr_t *chr : キャラクタ
* trap_t *trap : 罠
* abl_kind_t abl_main : メイン能力値
* abl_kind_t abl_sub : サブ能力値
* return : マークを解除するかどうか
***************************************************************/

bool_t	chr_disarm_trap_abl(
	chr_t *chr, trap_t *trap,
	abl_kind_t abl_main, abl_kind_t abl_sub
)
{
	dun_t	*dun = get_dun();

	if( chr == NULL )
		return TRUE;
	if( trap == NULL )
		return TRUE;
	if( trap->tab == NULL )
		return TRUE;

	if( chr_roll( chr, abl_main, abl_sub, trap->difficulty ) ){
		/* 成功 */

		disarm_trap( trap );
		print_msg_mbr( chr, FLG_NULL, MSG_TRAP_DISARM,
				chr->name, trap->tab->name );

		if( (abl_main == ABL_KIND_THI)
				|| (abl_sub == ABL_KIND_THI)){
			exp_party( calc_mnstr_exp( TRAP_MNSTR_KIND, dun->lev ),
					FALSE, TRUE );
		}

		return TRUE;
	}

	if( !rate_randm( TRAP_DISARM_FAILURE_RATE ) ){
		/* 罠が発動しない */

		print_msg_mbr( chr, FLG_NULL, MSG_ERR_TRAP_DISARM_LEV );

		return FALSE;
	}

	/* 罠が発動する */

	caught_trap( trap, chr );

	return TRUE;
}

/***************************************************************
* キャラクタが罠を調べる
* chr_t *chr : キャラクタ
* trap_t *trap : 罠
* return : 成功なら真
***************************************************************/

bool_t	chr_chk_trap( chr_t *chr, trap_t *trap )
{
	if( chr == NULL )
		return FALSE;
	if( trap == NULL )
		return FALSE;
	if( trap->tab == NULL )
		return FALSE;

	/* ロール */

	if( !chr_roll( chr, ABL_KIND_THI, ABL_KIND_DEX,
			TRAP_CHK_DIFFICULTY ) ){
		return FALSE;
	}

	/* 成功 */

	print_msg_find( chr, FLG_NULL, MSG_CHK_TRAP, trap->tab->name );

	trap->flg_chked = TRUE;
	set_trap_face_mnr( trap );

	if( is_mbr( chr ) )
		lost_trgt( trap );

	return TRUE;
}

/***************************************************************
* キャラクタがアイテムを開ける
* chr_t *chr : キャラクタ
* item_t *item : アイテム
* return : マークを解除するかどうか
***************************************************************/

bool_t	chr_open_item( chr_t *chr, item_t *item )
{
	if( item == NULL )
		return TRUE;
	if( chr == NULL )
		return TRUE;
	if( item->kind != ITEM_KIND_CHEST )
		return TRUE;

	open_item( item, chr );

	print_msg_mbr( chr, FLG_NULL, MSG_ITEM_OPEN,
			chr->name, item->name );

	return TRUE;
}

/***************************************************************
* キャラクタがアイテムの罠を解除
* chr_t *chr : キャラクタ
* item_t *item : アイテム
* return : マークを解除するかどうか
***************************************************************/

bool_t	chr_disarm_item( chr_t *chr, item_t *item )
{
	return chr_disarm_item_abl( chr, item,
			ABL_KIND_THI, ABL_KIND_DEX );
}

/***************************************************************
* キャラクタがアイテムの罠を解除 (能力値の指定あり)
* chr_t *chr : キャラクタ
* item_t *item : アイテム
* abl_kind_t abl_main : メイン能力値
* abl_kind_t abl_sub : サブ能力値
* return : マークを解除するかどうか
***************************************************************/

bool_t	chr_disarm_item_abl(
	chr_t *chr, item_t *item,
	abl_kind_t abl_main, abl_kind_t abl_sub
)
{
	if( item == NULL )
		return TRUE;
	if( chr == NULL )
		return TRUE;
	if( item->kind != ITEM_KIND_CHEST )
		return TRUE;
	if( item->dat.chest.trap == NULL ){
		print_msg_mbr( chr, FLG_NULL, MSG_ITEM_DISARM_ALREADY,
				item->name );
		return TRUE;
	}

	if( chr_roll( chr, abl_main, abl_sub,
			item->dat.chest.trap->difficulty ) ){
		/* 成功 */

		if( disarm_item( item ) ){
			print_msg_mbr( chr, FLG_NULL, MSG_ITEM_DISARM,
					chr->name, item->name );
		}

		return TRUE;
	}

	if( !rate_randm( CHEST_DISARM_FAILURE_RATE ) ){
		/* 罠が発動しない */

		print_msg_mbr( chr, FLG_NULL, MSG_ERR_ITEM_DISARM_LEV );

		return FALSE;
	}

	/* 罠が発動する */

	chk_trap_chest( item, chr, _100_PERCENT );

	return TRUE;
}

/***************************************************************
* キャラクタがアイテムを調べる
* chr_t *chr : キャラクタ
* item_t *item : アイテム
***************************************************************/

void	chr_chk_item( chr_t *chr, item_t *item )
{
	if( is_mbr( chr ) )
		print_msg( FLG_NULL, MSG_CHK_ITEM, item->name );
}

/***************************************************************
* キャラクタが周りを探す
* chr_t *chr : キャラクタ
***************************************************************/

void	chr_srch_obj( chr_t *chr )
{
	long	dx, dy;
	long	x, y;
	bool_t	flg_find;

	if( chr == NULL )
		return;

	flg_find = FALSE;

	x = chr->x;
	y = chr->y;
	for( dy = -1; dy <= +1; dy++ ){
		if( !clip_y( y + dy ) )
			continue;
		for( dx = -1; dx <= +1; dx++ ){
			if( !clip_x( x + dx ) )
				continue;

			if( chr_srch_obj_sub( chr, x + dx, y + dy ) )
				flg_find = TRUE;
		}
	}

	if( flg_find )
		chr_srch_auto_off( chr );
}

/***************************************************************
* キャラクタが周りを探す(座標あり)
* chr_t *chr : キャラクタ
* long x : X 座標
* long y : Y 座標
* return : 発見したか
***************************************************************/

bool_t	chr_srch_obj_sub( chr_t *chr, long x, long y )
{
	dun_t	*dun = get_dun();
	bool_t	flg_find;
	char	mjr;
	flg_map_t	flg;

	if( chr == NULL )
		return FALSE;

	flg_find = FALSE;

	mjr = dun->map.obj.mjr[y][x];
	flg = dun->map.obj.flg[y][x];

	/* ドア */
	do {
		door_t	*dr;

		/* マップのチェック */

		if( mjr != FACE_MJR_DOOR_CLOSE )
			if( mjr != FACE_MJR_DOOR_OPEN )
				break;

		/* ドアのチェック */

		dr = get_door( x, y );
		if( dr == NULL )
			break;

		if( !chk_flg( dr->flg, FLG_DOOR_SECRET ) )
			break;

		/* 発見のロール */

		if( !chr_roll( chr, ABL_KIND_THI, ABL_KIND_DEX,
				DOOR_SRCH_DIFFICULTY ) ){
			break;
		}

		/* 発見した */

		flg_find = TRUE;
		print_msg( FLG_NULL, MSG_DOOR_SRCH, chr->name );
		srch_door( dr->n );
	} while( 0 );

	/* 罠 */
	do {
		trap_t	*trap;

		/* マップのチェック */

		if( mjr != FACE_MJR_TRAP )
			break;

		/* 罠のチェック */

		trap = get_trap( x, y );
		if( trap == NULL )
			break;

		if( !chk_flg( flg, FLG_MAP_OBJ_LOOK_FLOOR ) )
			break;

		/* 発見のロール */

		if( !chr_roll( chr, ABL_KIND_THI, ABL_KIND_DEX,
				TRAP_SRCH_DIFFICULTY ) ){
			break;
		}

		/* 発見した */

		flg_find = TRUE;
		print_msg( FLG_NULL, MSG_TRAP_SRCH, chr->name );
		find_trap( trap );
	} while( 0 );

	return flg_find;
}

/***************************************************************
* キャラクタが探すのを自動的に止める
* chr_t *chr : キャラクタ
***************************************************************/

void	chr_srch_auto_off( chr_t *chr )
{
	if( chr == NULL )
		return;

	do {
		party_t	*pty = get_party();
		long	i;

		if( chr->kind != CHR_KIND_MBR )
			break;
		if( !chk_flg( pty->flg, FLG_PARTY_SRCH_AUTO_OFF ) )
			break;

		/* 自動解除 */

		for( i = 0; i < MBR_MAX_N; i++ ){
			if( chk_flg_or( pty->mbr[i]->stat,
					FLG_STAT_NOT_EXIST
					| FLG_STAT_DEAD ) ){
				continue;
			}

			if( pty->mbr[i]->act.kind == ACT_KIND_SRCH ){
				clr_chr_trgt_act( pty->mbr[i], FALSE );
			}
		}
	} while( 0 );

	if( chr->kind == CHR_KIND_MNSTR )
		clr_chr_trgt_act( chr, FALSE );
}

/***************************************************************
* キャラクタが街のドアの中に入る
* chr_t *chr : キャラクタ
* door_t *dr : ドアの番号
***************************************************************/

void	chr_enter_door( chr_t *chr, door_t *dr )
{
	if( chr == NULL )
		return;
	if( dr == NULL )
		return;

	lost_trgt( chr );

	clr_map_chr( chr );
	chr->x = MAP_DEL_X;
	chr->y = MAP_DEL_Y;
	draw_chr( chr );

	chr->work.enter_door = dr;
}

/***************************************************************
* キャラクタの目標のデータを更新
* chr_t *chr : キャラクタ
***************************************************************/

void	move_chr_trgt( chr_t *chr )
{
	chr_t	*trgt_chr;
	long	mx, my;
	door_t	*dr;
	bool_t	flg_x, flg_y;
	long	x, y;
	long	dx, dy;
	long	trgt_x, trgt_y;

	if( chr == NULL )
		return;

	switch( chr->trgt.kind ){
	case TRGT_KIND_NULL:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		return;
	case TRGT_KIND_SQUARE:
		get_square_mbr_map_pos( chr->mbr_n,
				&(chr->trgt.x), &(chr->trgt.y) );
		chr->trgt.true_x = chr->trgt.x;
		chr->trgt.true_y = chr->trgt.y;
		break;
	case TRGT_KIND_MBR:
	case TRGT_KIND_MNSTR:
		if( chr->trgt.p == NULL )
			break;
		trgt_chr = (chr_t *)(chr->trgt.p);

		do {
			if( chr->kind != CHR_KIND_MBR)
				break;
			if( trgt_chr->kind != CHR_KIND_MNSTR )
				break;
			if( chk_flg( trgt_chr->flg_map, FLG_MAP_CHR_FIND ) )
				break;

			clr_chr_trgt_act( chr, FALSE );
			break;
		} while( 0 );

		trgt_x = trgt_chr->x;
		trgt_y = trgt_chr->y;
		if( is_mbr( trgt_chr ) ){
			if( chk_flg_or( trgt_chr->stat,
					FLG_STAT_NOT_EXIST
					| FLG_STAT_DEAD ) ){
				get_square_mbr_map_pos( trgt_chr->mbr_n,
						&trgt_x, &trgt_y );
			}
		}
		chr->trgt.true_x = trgt_x;
		chr->trgt.true_y = trgt_y;

		switch( chr->trgt.dist ){
		case DIST_NEAR:
			chr->trgt.x = trgt_x;
			chr->trgt.y = trgt_y;

			if( calc_chr_dx( chr, trgt_chr ) <= 1 )
				chr->trgt.x = chr->x;
			if( calc_chr_dy( chr, trgt_chr ) <= 1 )
				chr->trgt.y = chr->y;
			break;
		case DIST_MEDIUM:
			if( is_mbr( chr ) ){
				get_square_mbr_map_pos( chr->mbr_n,
						&x, &y );
				x += trgt_x;
				y += trgt_y;
				x /= 2;
				y /= 2;
				chr->trgt.x = x;
				chr->trgt.y = y;

				dx = labs( chr->trgt.x - chr->x );
				dy = labs( chr->trgt.y - chr->y );
				if( dx <= MBR_DIST_MEDIUM_ADJUST_R )
					chr->trgt.x = chr->x;
				if( dy <= MBR_DIST_MEDIUM_ADJUST_R )
					chr->trgt.y = chr->y;
			} else {
				dx = labs( chr->x - trgt_x );
				dy = labs( chr->y - trgt_y );

				if( dx <= MNSTR_DIST_MEDIUM_R )
					chr->trgt.x = chr->x;
				else
					chr->trgt.x = trgt_x;
				if( dy <= MNSTR_DIST_MEDIUM_R )
					chr->trgt.y = chr->y;
				else
					chr->trgt.y = trgt_y;
			}
			break;
		case DIST_FAR:
			if( is_mbr( chr ) ){
				get_square_mbr_map_pos( chr->mbr_n,
						&(chr->trgt.x),
						&(chr->trgt.y) );
			} else {
				chr->trgt.x = chr->x;
				chr->trgt.y = chr->y;
			}
			break;
		}
		break;
	case TRGT_KIND_MNSTR_NULL:
		trgt_x = chr->trgt.true_x;
		trgt_y = chr->trgt.true_y;

		switch( chr->trgt.dist ){
		case DIST_NEAR:
			chr->trgt.x = trgt_x;
			chr->trgt.y = trgt_y;

			if( labs( chr->x - trgt_x ) <= 1 )
				chr->trgt.x = chr->x;
			if( labs( chr->y - trgt_y ) <= 1 )
				chr->trgt.y = chr->y;
			break;
		case DIST_MEDIUM:
			if( is_mbr( chr ) ){
				get_square_mbr_map_pos( chr->mbr_n, &x, &y );

				x += trgt_x;
				y += trgt_y;
				x /= 2;
				y /= 2;
				chr->trgt.x = x;
				chr->trgt.y = y;

				dx = labs( chr->trgt.x - chr->x );
				dy = labs( chr->trgt.y - chr->y );
				if( dx <= MBR_DIST_MEDIUM_ADJUST_R )
					chr->trgt.x = chr->x;
				if( dy <= MBR_DIST_MEDIUM_ADJUST_R )
					chr->trgt.y = chr->y;
			} else {
				dx = labs( chr->x - trgt_x );
				dy = labs( chr->y - trgt_y );

				if( dx <= MNSTR_DIST_MEDIUM_R )
					chr->trgt.x = chr->x;
				else
					chr->trgt.x = trgt_x;
				if( dy <= MNSTR_DIST_MEDIUM_R )
					chr->trgt.y = chr->y;
				else
					chr->trgt.y = trgt_y;
			}
			break;
		case DIST_FAR:
			if( is_mbr( chr ) ){
				get_square_mbr_map_pos( chr->mbr_n,
						&(chr->trgt.x),
						&(chr->trgt.y) );
			} else {
				chr->trgt.x = chr->x;
				chr->trgt.y = chr->y;
			}
			break;
		}
		break;
	case TRGT_KIND_TRAP:
		chr->trgt.true_x = ((trap_t *)chr->trgt.p)->x;
		chr->trgt.true_y = ((trap_t *)chr->trgt.p)->y;
		chr->trgt.x = chr->trgt.true_x;
		chr->trgt.y = chr->trgt.true_y;
		if( (labs( chr->trgt.x - chr->x ) <= 1)
				&& (labs( chr->trgt.y - chr->y ) <= 1) ){
			chr->trgt.x = chr->x;
			chr->trgt.y = chr->y;
		}
		break;
	case TRGT_KIND_ITEM:
		break;
	case TRGT_KIND_DOOR:
		mx = chr->x;
		my = chr->y;
		dr = (door_t *)(chr->trgt.p);
		flg_x = FALSE;
		flg_y = FALSE;

		/* ドアの１ブロックとなり */
		if( mx < dr->x ){
			chr->trgt.x = dr->x - 1;
		} else if( (dr->x + dr->dx - 1) < mx ){
			chr->trgt.x = (dr->x + dr->dx - 1) + 1;
		} else {
			chr->trgt.x = chr->x;
			flg_x = TRUE;
		}
		if( my < dr->y ){
			chr->trgt.y = dr->y - 1;
		} else if( (dr->y + dr->dy - 1) < my ){
			chr->trgt.y = (dr->y + dr->dy - 1) + 1;
		} else {
			chr->trgt.y = chr->y;
			flg_y = TRUE;
		}
		if( flg_x && flg_y ){	/* ドアの中に居る時 */
			chr->trgt.x = dr->x - 1;
			chr->trgt.y = dr->y - 1;
		}
		break;
	case TRGT_KIND_QUEUE:
		if( chr->trgt.p != NULL ){
			discount_queue_t	*q;

			q = (discount_queue_t *)(chr->trgt.p);
			chr->trgt.true_x = q->pos[chr->trgt.n].x;
			chr->trgt.true_y = q->pos[chr->trgt.n].y;
			chr->trgt.x = chr->trgt.true_x;
			chr->trgt.y = chr->trgt.true_y;
		}
		break;
	case TRGT_KIND_POS:
		chr->trgt.true_x = chr->trgt.x;
		chr->trgt.true_y = chr->trgt.y;
		break;
	}
}

/***************************************************************
* キャラクタ間の横方向の距離を計算
* chr_t *chr1 : キャラクタ1
* chr_t *chr2 : キャラクタ2
* return : 距離
***************************************************************/

long	calc_chr_dx( chr_t *chr1, chr_t *chr2 )
{
	long	x1, x2;

	if( chr1 == NULL )
		return MAP_MAX_X;
	if( chr2 == NULL )
		return MAP_MAX_X;

	if( chr1->x < chr2->x ){
		x1 = get_chr_right( chr1->x, chr1->dx );
		x2 = get_chr_left( chr2->x, chr2->dx );
	} else if( chr2->x < chr1->x ){
		x1 = get_chr_right( chr2->x, chr2->dx );
		x2 = get_chr_left( chr1->x, chr1->dx );
	} else {
		return 0;
	}

	return( x2 - x1 );
}

/***************************************************************
* キャラクタ間の縦方向の距離を計算
* chr_t *chr1 : キャラクタ1
* chr_t *chr2 : キャラクタ2
* return : 距離
***************************************************************/

long	calc_chr_dy( chr_t *chr1, chr_t *chr2 )
{
	long	y1, y2;

	if( chr1 == NULL )
		return MAP_MAX_Y;
	if( chr2 == NULL )
		return MAP_MAX_Y;

	if( chr1->y < chr2->y ){
		y1 = get_chr_bottom( chr1->y, chr1->dy );
		y2 = get_chr_top( chr2->y, chr2->dy );
	} else if( chr2->y < chr1->y ){
		y1 = get_chr_bottom( chr2->y, chr2->dy );
		y2 = get_chr_top( chr1->y, chr1->dy );
	} else {
		return 0;
	}

	return( y2 - y1 );
}

/***************************************************************
* キャラクタと目標との距離を計算
* chr_t *chr : キャラクタ
* return : 距離
***************************************************************/

long	get_trgt_range( chr_t *chr )
{
	long	dx, dy;

	if( chr == NULL )
		return MAP_MAX_X;

	if( chk_xx_range() )
		return 1;

	if( (chr->trgt.kind == TRGT_KIND_MBR)
			|| (chr->trgt.kind == TRGT_KIND_MNSTR) ){
		chr_t	*trgt = (chr_t *)(chr->trgt.p);

		if( trgt->x < chr->x ){
			dx = get_chr_left( chr->x, chr->dx );
			dx -= get_chr_right( trgt->x, trgt->dx );
		} else {
			dx = get_chr_left( trgt->x, trgt->dx );
			dx -= get_chr_right( chr->x, chr->dx );
		}

		if( trgt->y < chr->y ){
			dy = get_chr_top( chr->y, chr->dy );
			dy -= get_chr_bottom( trgt->y, trgt->dy );
		} else {
			dy = get_chr_top( trgt->y, trgt->dy );
			dy -= get_chr_bottom( chr->y, chr->dy );
		}
	} else {
		if( chr->trgt.true_x < chr->x ){
			dx = get_chr_left( chr->x, chr->dx );
			dx -= chr->trgt.true_x;
		} else {
			dx = chr->trgt.true_x;
			dx -= get_chr_right( chr->x, chr->dx );
		}

		if( chr->trgt.true_y < chr->y ){
			dy = get_chr_top( chr->y, chr->dy );
			dy -= chr->trgt.true_y;
		} else {
			dy = chr->trgt.true_y;
			dy -= get_chr_bottom( chr->y, chr->dy );
		}
	}

	dx = labs( dx );
	dy = labs( dy );

	return( max_l( dx, dy ) );
}

/***************************************************************
* キャラクタの左端の座標を計算
* long x : x 座標
* long dx : 幅
* return : 座標
***************************************************************/

long	get_chr_left( long x, long dx )
{
	if( !clip_x( x ) )
		return MAP_MAX_X;

	return( x - (dx / 2) );
}

/***************************************************************
* キャラクタの上端の座標を計算
* long y : y 座標
* long dy : 高さ
* return : 座標
***************************************************************/

long	get_chr_top( long y, long dy )
{
	if( !clip_y( y ) )
		return MAP_MAX_Y;

	return( y - (dy / 2) );
}

/***************************************************************
* キャラクタの右端の座標を計算
* long x : x 座標
* long dx : 幅
* return : 座標
***************************************************************/

long	get_chr_right( long x, long dx )
{
	if( !clip_x( x ) )
		return -1;

	return( get_chr_left( x, dx ) + dx - 1 );
}

/***************************************************************
* キャラクタの下端の座標を計算
* long y : y 座標
* long dy : 高さ
* return : 座標
***************************************************************/

long	get_chr_bottom( long y, long dy )
{
	if( !clip_y( y ) )
		return -1;

	return( get_chr_top( y, dy ) + dy - 1 );
}

/***************************************************************
* 自動マークを続ける
* chr_t *chr : キャラクタ
* return : 続けたか
***************************************************************/

bool_t	chk_auto_mark_cont( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( chk_flg( chr->flg_chr, FLG_CHR_AUTO_MARK_CONT ) ){
		exec_menu_auto_mark( chr );
		if( chr->act.kind == ACT_KIND_NULL )
			chr->flg_chr &= ~FLG_CHR_AUTO_MARK_CONT;

		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* キャラクタの目標と行動をクリア
* chr_t *chr : キャラクタ
* bool_t flg_force : 強制的
***************************************************************/

void	clr_chr_trgt_act( chr_t *chr, bool_t flg_force )
{
	if( chr == NULL )
		return;

	if( flg_force || !chk_auto_mark_cont( chr ) ){
		clr_chr_trgt( chr );
		clr_chr_act( chr );
	}
}

/***************************************************************
* キャラクタの目標をクリア
* chr_t *chr : キャラクタ
***************************************************************/

void	clr_chr_trgt( chr_t *chr )
{
	if( chr == NULL )
		return;

	if( is_mbr( chr ) ){
		mark_square( chr );
	} else if( is_pet( chr ) ){
		if( chr->owner == NULL ){
			mark_pos( chr, chr->x, chr->y, DIST_NEAR );
		} else {
			mark_mbr( chr, chr->owner, DIST_NEAR );
		}
	} else if( chr->kind == CHR_KIND_MNSTR ){
		if( chr->owner == NULL ){
			mark_pos( chr, chr->x, chr->y, DIST_NEAR );
		} else {
			mark_mnstr( chr, chr->owner, DIST_NEAR );
		}
	}
}

/***************************************************************
* キャラクタの行動を設定
* chr_t *chr : キャラクタ
* act_kind_t kind : 行動の種類
* void *p : ポインタ1
* void *p2 : ポインタ2
* long n : 数値1
* long n2 : 数値2
* return : 成功か
***************************************************************/

bool_t	set_chr_act(
	chr_t *chr, act_kind_t kind,
	void *p, void *p2,
	long n, long n2
)
{
	char	*msg;
	item_t	*item;

	if( chr == NULL )
		return FALSE;
	if( chk_flg( chr->stat, FLG_STAT_NOT_EXIST ) )
		return FALSE;
	if( chk_flg( chr->stat, FLG_STAT_DEAD ) )
		if( kind != ACT_KIND_NULL )
			return FALSE;

	msg = MSG_NULL;
	switch( kind ){
	case ACT_KIND_NULL:
		msg = MSG_ACT_NULL;
		break;
	case ACT_KIND_MNSTR_FIGHT:
		msg = MSG_ACT_MNSTR_FIGHT;
		break;
	case ACT_KIND_MNSTR_THROW:
		msg = MSG_ACT_MNSTR_THROW;
		break;
	case ACT_KIND_MNSTR_STEAL:
		msg = MSG_ACT_MNSTR_STEAL;
		break;
	case ACT_KIND_MNSTR_TAIL:
		msg = MSG_ACT_MNSTR_TAIL;
		break;
	case ACT_KIND_MBR_FIGHT:
		msg = MSG_ACT_MBR_FIGHT;
		break;
	case ACT_KIND_MBR_THROW:
		msg = MSG_ACT_MBR_THROW;
		break;
	case ACT_KIND_MBR_STEAL:
		msg = MSG_ACT_MBR_STEAL;
		break;
	case ACT_KIND_MBR_TAIL:
		msg = MSG_ACT_MBR_TAIL;
		break;
	case ACT_KIND_DOOR_OPEN:
		msg = MSG_ACT_DOOR_OPEN;
		break;
	case ACT_KIND_DOOR_CLOSE:
		msg = MSG_ACT_DOOR_CLOSE;
		break;
	case ACT_KIND_DOOR_JAM:
		msg = MSG_ACT_DOOR_JAM;
		break;
	case ACT_KIND_DOOR_DISARM:
		msg = MSG_ACT_DOOR_DISARM;
		break;
	case ACT_KIND_DOOR_BREAK:
		msg = MSG_ACT_DOOR_BREAK;
		break;
	case ACT_KIND_DOOR_PEEP:
		msg = MSG_ACT_DOOR_PEEP;
		break;
	case ACT_KIND_DOOR_CHK:
		msg = MSG_ACT_DOOR_CHK;
		break;
	case ACT_KIND_TRAP_DISARM:
		msg = MSG_ACT_TRAP_DISARM;
		break;
	case ACT_KIND_TRAP_BREAK:
		msg = MSG_ACT_TRAP_BREAK;
		break;
	case ACT_KIND_TRAP_CHK:
		msg = MSG_ACT_TRAP_CHK;
		break;
	case ACT_KIND_ITEM_PICK_UP:
		msg = MSG_ACT_ITEM_PICK_UP;
		break;
	case ACT_KIND_ITEM_BREAK:
		msg = MSG_ACT_ITEM_BREAK;
		break;
	case ACT_KIND_ITEM_CHK:
		msg = MSG_ACT_ITEM_CHK;
		break;
	case ACT_KIND_ITEM_SEND:
		msg = MSG_ACT_ITEM_SEND;
		break;
	case ACT_KIND_ITEM_DROP:
		msg = MSG_ACT_ITEM_DROP;
		break;
	case ACT_KIND_ITEM_RECEIVE:
		msg = MSG_ACT_ITEM_RECEIVE;
		break;
	case ACT_KIND_ITEM_OPEN:
		msg = MSG_ACT_ITEM_OPEN;
		break;
	case ACT_KIND_ITEM_DISARM:
		msg = MSG_ACT_ITEM_DISARM;
		break;
	case ACT_KIND_EQUIP_SEL:
		msg = MSG_ACT_EQUIP;
		item = (item_t *)p;
		if( is_mbr( chr ) ){
			if( item == NULL )
				return FALSE;
			if( !chk_equip_two_handed_wpn( chr, item,
					item->equip_kind ) ){
				return FALSE;
			}
		}
		break;
	case ACT_KIND_EQUIP:
		msg = MSG_ACT_EQUIP;
		item = (item_t *)p;
		if( is_mbr( chr ) ){
			if( !chk_equip_two_handed_wpn( chr, item,
					(equip_kind_t)n ) ){
				return FALSE;
			}
		}
		break;
	case ACT_KIND_TAKE_OFF:
		msg = MSG_ACT_TAKE_OFF;
		break;
	case ACT_KIND_EQUIP_MBR:
		msg = MSG_ACT_EQUIP_MBR;
		item = (item_t *)p;
		if( is_mbr( chr ) ){
			if( !chk_equip_two_handed_wpn( (chr_t *)p2, item,
					(equip_kind_t)n ) ){
				return FALSE;
			}
		}
		break;
	case ACT_KIND_TAKE_OFF_MBR:
		msg = MSG_ACT_TAKE_OFF_MBR;
		break;
	case ACT_KIND_POTION_QUAFF:
		msg = MSG_ACT_POTION_QUAFF;
		break;
	case ACT_KIND_POTION_FILL:
		msg = MSG_ACT_POTION_FILL;
		break;
	case ACT_KIND_SCROLL_READ:
		msg = MSG_ACT_SCROLL_READ;
		break;
	case ACT_KIND_STICK_ZAP:
		msg = MSG_ACT_STICK_ZAP;
		break;
	case ACT_KIND_LAMP_RUB:
		msg = MSG_ACT_LAMP_RUB;
		break;
	case ACT_KIND_FOOD_EAT:
		msg = MSG_ACT_FOOD_EAT;
		break;
	case ACT_KIND_TOBACCO_DISPOSE:
		msg = MSG_ACT_TOBACCO_DISPOSE;
		break;
	case ACT_KIND_SRCH:
		msg = MSG_ACT_SRCH;
		break;
	case ACT_KIND_SPELL:
		if( p == NULL )
			msg = MSG_ACT_NULL;
		else
			msg = ((spell_tab_t *)p)->name;
		break;
	case ACT_KIND_SHOP:
	case ACT_KIND_TELEPORT_PARTY:
	case ACT_KIND_RECALL:
	case ACT_KIND_MAX_N:
		return FALSE;
	}

	chr->act.kind = kind;
	str_nz_cpy( chr->act.msg, msg, ACT_MSG_MAX_BYTE );
	chr->act.p = p;
	chr->act.p2 = p2;
	chr->act.n = n;
	chr->act.n2 = n2;

	switch( kind ){
	case ACT_KIND_MNSTR_FIGHT:
	case ACT_KIND_MNSTR_THROW:
	case ACT_KIND_MNSTR_STEAL:
	case ACT_KIND_MNSTR_TAIL:
		chr->act.dflt_kind_mnstr = chr->act.kind;
		str_nz_cpy( chr->act.dflt_msg_mnstr, chr->act.msg,
				ACT_MSG_MAX_BYTE );
		break;
	default:
		break;
	}

	draw_mbr_stat( chr );

	return TRUE;
}

/***************************************************************
* キャラクタの行動をクリア
* chr_t *chr : キャラクタ
***************************************************************/

void	clr_chr_act( chr_t *chr )
{
	if( chr == NULL )
		return;

	chr->act.kind = ACT_KIND_NULL;
	str_nz_cpy( chr->act.msg, MSG_ACT_NULL, ACT_MSG_MAX_BYTE );

	draw_mbr_stat( chr );
}

/***************************************************************
* 目標をマークしている全てのキャラクタの目標をクリア
* void *p : 目標
***************************************************************/

void	lost_trgt( void *p )
{
	party_t	*pty = get_party();
	mnstr_t	*mns_head, *mns_p;
	pet_t	**party_pet = get_party_pet();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		mbr_t	*pp;

		pp = pty->mbr[i];

		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( (p == pp->trgt.p) || ( p == pp->act.p ) ){
			clr_chr_trgt_act( pp, TRUE );
			set_auto_mark_cont( pty->mbr[i] );
			exec_menu_auto_mark( pty->mbr[i] );
		}

		if( p == pp->work.link_chr )
			pp->work.link_chr = NULL;
	}

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next->next; mns_p != NULL;
			mns_p = mns_p->next ){
		mnstr_t	*pp;

		pp = mns_p->prev;
		if( pp == mns_head )
			break;

		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( p == pp->trgt.p )
			clr_chr_trgt_act( pp, TRUE );
		if( p == pp->act.p )
			clr_chr_trgt_act( pp, TRUE );

		if( p == pp->work.link_chr )
			pp->work.link_chr = NULL;
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];

		if( pp == NULL )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( p == pp->trgt.p )
			clr_chr_trgt_act( pp, TRUE );
		if( p == pp->act.p )
			clr_chr_trgt_act( pp, TRUE );

		if( p == pp->work.link_chr )
			pp->work.link_chr = NULL;
		if( p == pp->owner )
			chk_pet_owner( pp );
	}

	lost_trgt_reg_spell( p );
}

/***************************************************************
* メンバーをマーク
* chr_t *chr : マークするキャラクタ
* mbr_t *mbr : マークされるメンバー
* dist_t dist : 間合い
***************************************************************/

void	mark_mbr( chr_t *chr, mbr_t *mbr, dist_t dist )
{
	if( chr == NULL )
		return;
	if( mbr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chk_flg( chr->stat, FLG_STAT_CHARM ) )
		return;

	chr->trgt.kind = TRGT_KIND_MBR;
	chr->trgt.p = mbr;
	chr->trgt.n = mbr->mbr_n;
	chr->trgt.x = mbr->x;
	chr->trgt.y = mbr->y;
	chr->trgt.true_x = mbr->x;
	chr->trgt.true_y = mbr->y;
	chr->trgt.dist = dist;
}

/***************************************************************
* モンスターをマーク(間合いを保存しない)
* chr_t *chr : マークするキャラクタ
* mnstr_t *mnstr : マークされるモンスター
* dist_t dist : 間合い
***************************************************************/

void	mark_mnstr_no_regist( chr_t *chr, mnstr_t *mnstr, dist_t dist )
{
	if( chr == NULL )
		return;
	if( mnstr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chk_flg( chr->stat, FLG_STAT_CHARM ) )
		return;
	if( chk_flg( chr->flg_chr, FLG_CHR_NO_MARK_MNSTR ) )
		return;

	chr->trgt.kind = TRGT_KIND_MNSTR;
	chr->trgt.p = mnstr;
	chr->trgt.n = 0;
	chr->trgt.x = mnstr->x;
	chr->trgt.y = mnstr->y;
	chr->trgt.true_x = chr->trgt.x;
	chr->trgt.true_y = chr->trgt.y;
	chr->trgt.dist = dist;

	if( !is_pet( chr ) ){
		print_msg_mbr( chr, FLG_MSG_NO_MORE,
				MSG_FMT_MARK_MNSTR,
				chr->name, mnstr->name );
	}
}

/***************************************************************
* モンスターをマーク(保存した間合いで)
* chr_t *chr : マークするキャラクタ
* mnstr_t *mnstr : マークされるモンスター
***************************************************************/

void	mark_mnstr_dflt( chr_t *chr, mnstr_t *mnstr )
{
	if( chr == NULL )
		return;
	if( mnstr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chk_flg( chr->stat, FLG_STAT_CHARM ) )
		return;
	if( chk_flg( chr->flg_chr, FLG_CHR_NO_MARK_MNSTR ) )
		return;

	mark_mnstr_no_regist( chr, mnstr, chr->trgt.dflt_dist_mnstr );
}

/***************************************************************
* モンスターをマーク
* chr_t *chr : マークするキャラクタ
* mnstr_t *mnstr : マークされるモンスター
* dist_t dist : 間合い
***************************************************************/

void	mark_mnstr( chr_t *chr, mnstr_t *mnstr, dist_t dist )
{
	if( chr == NULL )
		return;
	if( mnstr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chk_flg( chr->stat, FLG_STAT_CHARM ) )
		return;
	if( chk_flg( chr->flg_chr, FLG_CHR_NO_MARK_MNSTR ) )
		return;

	if( chk_queue_chr( mnstr ) ){
		if( chk_discount() ){
			if( !chk_discount_open() ){
				mark_discount_queue( chr );
				return;
			}
		}
	}

	mark_mnstr_no_regist( chr, mnstr, dist );
	chr->trgt.dflt_dist_mnstr = dist;
}

/***************************************************************
* モンスターがいない場所をマーク(間合いを保存しない)
* chr_t *chr : マークするキャラクタ
* long x : X 座標
* long y : Y 座標
* dist_t dist : 間合い
***************************************************************/

void	mark_mnstr_null_no_regist( chr_t *chr, long x, long y, dist_t dist )
{
	if( chr == NULL )
		return;
	if( chr->kind != CHR_KIND_MBR )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chk_flg( chr->stat, FLG_STAT_CHARM ) )
		return;
	if( chk_flg( chr->flg_chr, FLG_CHR_NO_MARK_MNSTR ) )
		return;

	mnstr_null[chr->mbr_n].x = x;
	mnstr_null[chr->mbr_n].y = y;

	chr->trgt.kind = TRGT_KIND_MNSTR_NULL;
	chr->trgt.p = &(mnstr_null[chr->mbr_n]);
	chr->trgt.n = 0;
	chr->trgt.x = mnstr_null[chr->mbr_n].x;
	chr->trgt.y = mnstr_null[chr->mbr_n].y;
	chr->trgt.true_x = chr->trgt.x;
	chr->trgt.true_y = chr->trgt.y;
	chr->trgt.dist = dist;
}

/***************************************************************
* モンスターがいない場所をマーク(保存した間合いで)
* chr_t *chr : マークするキャラクタ
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	mark_mnstr_null_dflt( chr_t *chr, long x, long y )
{
	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chk_flg( chr->stat, FLG_STAT_CHARM ) )
		return;
	if( chk_flg( chr->flg_chr, FLG_CHR_NO_MARK_MNSTR ) )
		return;

	mark_mnstr_null_no_regist( chr, x, y, chr->trgt.dflt_dist_mnstr );
}

/***************************************************************
* モンスターがいない場所をマーク
* chr_t *chr : マークするキャラクタ
* long x : X 座標
* long y : Y 座標
* dist_t dist : 間合い
***************************************************************/

void	mark_mnstr_null( chr_t *chr, long x, long y, dist_t dist )
{
	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chk_flg( chr->stat, FLG_STAT_CHARM ) )
		return;
	if( chk_flg( chr->flg_chr, FLG_CHR_NO_MARK_MNSTR ) )
		return;

	mark_mnstr_null_no_regist( chr, x, y, dist );
	chr->trgt.dflt_dist_mnstr = dist;
}

/***************************************************************
* アイテムをマーク
* chr_t *chr : マークするキャラクタ
* item_t *item : アイテム
* dist_t dist : 間合い
***************************************************************/

void	mark_item( chr_t *chr, item_t *item, dist_t dist )
{
	if( chr == NULL )
		return;
	if( item == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	chr->trgt.kind = TRGT_KIND_ITEM;
	chr->trgt.p = item;
	chr->trgt.n = 0;
	chr->trgt.x = item->x;
	chr->trgt.y = item->y;
	chr->trgt.true_x = chr->trgt.x;
	chr->trgt.true_y = chr->trgt.y;
	chr->trgt.dist = dist;
}

/***************************************************************
* ドアをマーク
* chr_t *chr : マークするキャラクタ
* door_t *dr : ドア
* dist_t dist : 間合い
***************************************************************/

void	mark_door( chr_t *chr, door_t *dr, dist_t dist )
{
	if( chr == NULL )
		return;
	if( dr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	if( chk_discount_door( dr ) ){
		if( chk_discount() ){
			if( !chk_discount_open() ){
				mark_discount_queue( chr );
				return;
			}
		}
	}

	chr->trgt.kind = TRGT_KIND_DOOR;
	chr->trgt.p = dr;
	chr->trgt.n = dr->n;
	chr->trgt.x = dr->x;
	chr->trgt.y = dr->y;
	chr->trgt.true_x = chr->trgt.x;
	chr->trgt.true_y = chr->trgt.y;
	chr->trgt.dist = dist;
}

/***************************************************************
* 罠をマーク
* chr_t *chr : マークするキャラクタ
* trap_t *trap : 罠
* dist_t dist : 間合い
***************************************************************/

void	mark_trap( chr_t *chr, trap_t *trap, dist_t dist )
{
	if( chr == NULL )
		return;
	if( trap == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	chr->trgt.kind = TRGT_KIND_TRAP;
	chr->trgt.p = trap;
	chr->trgt.n = 0;
	chr->trgt.x = trap->x;
	chr->trgt.y = trap->y;
	chr->trgt.true_x = chr->trgt.x;
	chr->trgt.true_y = chr->trgt.y;
	chr->trgt.dist = dist;
}

/***************************************************************
* 割り引きセールの行列に列ぶ(全てのメンバー)
* chr_t *chr : マークするキャラクタ
***************************************************************/

void	mark_discount_queue( chr_t *chr )
{
	if( is_mbr( chr ) ){
		party_t	*pty = get_party();
		long	i;

		for( i = 0; i < MBR_MAX_N; i++ ){
			mark_discount_queue_sub( pty->mbr[i] );
		}
	} else {
		mark_discount_queue_sub( chr );
	}
}

/***************************************************************
* 割り引きセールの行列に列ぶ
* chr_t *chr : マークするキャラクタ
***************************************************************/

void	mark_discount_queue_sub( chr_t *chr )
{
	discount_queue_t	*q;
	long	qn;

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chr->trgt.kind == TRGT_KIND_QUEUE )
		return;

	q = get_discount_queue();
	if( q == NULL )
		return;
	qn = get_discount_queue_n( chr );
	if( qn <= -1 )
		return;

	clr_chr_act( chr );

	chr->trgt.kind = TRGT_KIND_QUEUE;
	chr->trgt.p = q;
	chr->trgt.n = qn;
	chr->trgt.x = q->pos[qn].x;
	chr->trgt.y = q->pos[qn].y;
	chr->trgt.true_x = chr->trgt.x;
	chr->trgt.true_y = chr->trgt.y;
	chr->trgt.dist = DIST_NEAR;

	inc_discount_queue( chr );
}

/***************************************************************
* アンカーをマーク(デフォルトの目標)
* chr_t *chr : マークするキャラクタ
***************************************************************/

void	mark_square( chr_t *chr )
{
	party_t	*pty = get_party();
	pos_t	pos;

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	get_square_mbr_map_pos( chr->mbr_n, &(pos.x), &(pos.y) );

	chr->trgt.kind = TRGT_KIND_SQUARE;
	chr->trgt.p = &(pty->square);
	chr->trgt.n = 0;
	chr->trgt.x = pos.x;
	chr->trgt.y = pos.y;
	chr->trgt.true_x = chr->trgt.x;
	chr->trgt.true_y = chr->trgt.y;
	chr->trgt.dist = DIST_NEAR;
}

/***************************************************************
* 場所をマーク
* chr_t *chr : マークするキャラクタ
* long x : X 座標
* long y : Y 座標
* dist_t dist : 間合い
***************************************************************/

void	mark_pos( chr_t *chr, long x, long y, dist_t dist )
{
	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	chr->trgt.kind = TRGT_KIND_POS;
	chr->trgt.p = NULL;
	chr->trgt.n = 0;
	chr->trgt.x = x;
	chr->trgt.y = y;
	chr->trgt.true_x = chr->trgt.x;
	chr->trgt.true_y = chr->trgt.y;
	chr->trgt.dist = dist;
}

/***************************************************************
* 杖を使うのを止める
* chr_t *chr : キャラクタ
***************************************************************/

void	stop_zapping( chr_t *chr )
{
	if( chr == NULL )
		return;

	clr_chr_trgt_act( chr, FALSE );
}

/***************************************************************
* 周りを探すのを始める
* chr_t *chr : キャラクタ
***************************************************************/

void	chr_srch_begin( chr_t *chr )
{
	if( chr == NULL )
		return;

	set_chr_act( chr, ACT_KIND_SRCH, NULL, NULL, get_turn() % 2, 0 );
}

/***************************************************************
* 周りを探すのを止める
* chr_t *chr : キャラクタ
***************************************************************/

void	chr_srch_end( chr_t *chr )
{
	if( chr == NULL )
		return;

	if( chr->act.kind == ACT_KIND_SRCH )
		clr_chr_trgt_act( chr, FALSE );
}

/***************************************************************
* キャラクタが暗視出来るか調べる
* chr_t *chr : キャラクタ
* return : 暗視出来るか
***************************************************************/

bool_t	chk_infra_vision( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( chr->fx_data.infra_vision > 0 )
		return TRUE;

	if( is_mbr( chr ) ){
		switch( chr->race.main ){
		case MAIN_RACE_HUMAN:
		case MAIN_RACE_HALF_ELF:
			return FALSE;
		case MAIN_RACE_ELF:
		case MAIN_RACE_DWARF:
		case MAIN_RACE_VIVID:
			return TRUE;
		case MAIN_RACE_MAX_N:
			return FALSE;
		}
	}

	return FALSE;
}

/***************************************************************
* キャラクタの周りを照らす
* chr_t *chr : キャラクタ
* long x : X 座標
* long y : Y 座標
* bool_t flg_on : 真なら明かりを点ける、偽なら消す
* return : 照らしたか
***************************************************************/

bool_t	chr_light_up( chr_t *chr, bool_t flg_on )
{
	const long	r = 1;
	long	x, y, bx, by, ex, ey;
	dun_t	*dun;

	if( chr == NULL )
		return FALSE;

	if( !clip_pos( chr->x, chr->y ) )
		return FALSE;

	if( flg_on && chk_flg_or( chr->stat,
			FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
		return FALSE;
	}

	if( is_mbr( chr ) ){
		if( !chk_infra_vision( chr ) ){
			item_t	*lit;

			if( chr->kind != CHR_KIND_MBR )
				return FALSE;

			lit = &(get_mbr_item_asgn_equip( chr )
					[EQUIP_KIND_LIGHT_SOURCE]);
			if( lit == NULL )
				return FALSE;
			if( lit->kind != ITEM_KIND_LIGHT )
				return FALSE;
			if( lit->dat.light.turn <= 0 )
				return FALSE;
		}
	} else if( chr->kind == CHR_KIND_MNSTR ){
		if( chk_flg( chr->flg_chr, FLG_CHR_LIGHT ) ){
			;
		} else if( chk_flg( chr->flg_chr, FLG_CHR_DARK ) ){
			flg_on = !flg_on;
		} else {
			return FALSE;
		}
	}

	bx = get_chr_left( chr->x, chr->dx );
	ex = get_chr_right( chr->x, chr->dx );
	by = get_chr_top( chr->y, chr->dy );
	ey = get_chr_bottom( chr->y, chr->dy );
	if( bx < r )
		bx = r;
	if( by < r )
		by = r;
	if( ex > MAP_MAX_X - 1 - r )
		bx = MAP_MAX_X - 1 - r;
	if( ey > MAP_MAX_Y - 1 - r )
		by = MAP_MAX_Y - 1 - r;

	dun = get_dun();

	for( y = by - r; y <= ey + r; y++ ){
		for( x = bx - r; x <= ex + r; x++ ){
			turn_light_chr( x, y, flg_on );

			if( !flg_on )
				continue;
			if( calc_light_depth( x, y ) <= 0 )
				continue;
			if( chr->kind != CHR_KIND_MBR ){
				if( !chk_flg( dun->map.chr.flg[y][x],
						FLG_MAP_CHR_FIND ) ){
					continue;
				}
			}

			dun->map.obj.flg[y][x] |= FLG_MAP_OBJ_FIND;
		}
	}

	return TRUE;
}

/***************************************************************
* マップにキャラクタを置く
* chr_t *chr : キャラクタ
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	put_chr( chr_t *chr, long x, long y )
{
	long	r, max_r;
	long	i;
	bool_t	flg_break;

	if( chr == NULL )
		return;

	if( !clip_pos( x, y ) )
		return;

	clr_map_chr( chr );

	clr_chr_trgt_act( chr, FALSE );

	chr->x = randm( MAP_MAX_X );
	chr->y = randm( MAP_MAX_Y );

	max_r = max_l( MAP_MAX_X, MAP_MAX_Y );
	flg_break = FALSE;
	for( r = 0; r < max_r; r++ ){
		for( i = 0; i < LOOP_MAX_1000; i++ ){
			long	dx, dy;
			long	xx, yy;

			dx = randm( r * 2 + 1 ) - r;
			dy = randm( r * 2 + 1 ) - r;

			xx = x + dx;
			yy = y + dy;

			if( can_move_chr( chr, xx, yy ) ){
				chr->x = xx;
				chr->y = yy;
				flg_break = TRUE;
				break;
			}
		}
		if( flg_break )
			break;
	}

	set_map_chr( chr );
	if( chr->kind == CHR_KIND_MNSTR )
		set_flg_find_mnstr( chr );

	draw_chr( chr );
}

/***************************************************************
* キャラクタに経験値を与える
* chr_t *chr : キャラクタ
* long exp : 経験値
* bool_t flg_set_max : 経験値を回復不能にするか
* bool_t flg_print_exp : 経験値のメッセージを表示するか
* bool_t flg_print_lev : レベルのメッセージを表示するか
***************************************************************/

void	exp_chr(
	chr_t *chr,
	long exp,
	bool_t flg_set_max,
	bool_t flg_print_exp,
	bool_t flg_print_lev
)
{
	if( chr == NULL )
		return;

	if( flg_print_exp ){
		curs_attrset_chr( chr, exp, FALSE );
		print_msg( FLG_NULL, MSG_EXP_MBR,
				chr->name, fmt_num( exp ) );
		curs_attrset_dflt();
	}

	if( chr->kind == CHR_KIND_MBR ){
		bool_t	flg_draw_lev;

		flg_draw_lev = flg_print_lev;
		if( exp_mbr( chr, exp, flg_set_max,
				flg_print_lev, flg_draw_lev ) ){
			flg_draw_lev = FALSE;
		}

		exp_mbr_skill( chr, exp, flg_set_max,
				flg_print_lev, flg_draw_lev );
	} else {
		exp_mnstr( chr, exp, flg_set_max, flg_print_lev, FALSE );
	}
}

/***************************************************************
* メンバーに経験値を与える
* mbr_t *mbr : メンバー
* long exp : 経験値
* bool_t flg_set_max : 経験値を回復不能にするか
* bool_t flg_print_lev : レベルのメッセージを表示するか
* bool_t flg_draw_lev : レベルの VFX を表示するか
* return : レベルが変化したか?
***************************************************************/

bool_t	exp_mbr(
	mbr_t *mbr,
	long exp,
	bool_t flg_set_max,
	bool_t flg_print_lev,
	bool_t flg_draw_lev
)
{
	long	i, n, mod_n;
	class_t	*class_tab;
	rate_t	rate;
	long	exp_add, exp_mod;

	if( mbr == NULL )
		return FALSE;

	class_tab = get_class_tab();
	if( class_tab == NULL )
		return FALSE;

	rate = 0;
	for( i = 0; i < ABL_KIND_MAX_N; i++ )
		rate += class_tab[mbr->class_n].abl_rate[i];
	if( rate != _100_PERCENT ){
		print_msg( FLG_NULL, MSG_ERR_CLASS_NOT_100_PERCENT,
				class_tab[mbr->class_n].name );
		return FALSE;
	}

	/* 経験値を割り振る */

	exp_mod = exp;
	n = 0;
	mod_n = 0;
	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		rate = class_tab[mbr->class_n].abl_rate[i];
		if( rate > 0 ){
			n++;
			if( per_randm( n ) )
				mod_n = i;
		}
		exp_add = exp * rate / _100_PERCENT;
		exp_mod -= exp_add;
		
	}

	/* 余った経験値をさらに割り振る */

	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		long	exp_n;

		rate = class_tab[mbr->class_n].abl_rate[i];
		exp_add = exp * rate / _100_PERCENT;

		if( i == mod_n )
			exp_n = exp_add + exp_mod;
		else
			exp_n = exp_add;

		exp_n = get_mbr_race_exp( mbr, exp_n, (abl_kind_t)i );
		mbr->abl.exp[i].n += exp_n;

		if( mbr->abl.exp[i].n < 0 )
			mbr->abl.exp[i].n = 0;
		if( mbr->abl.exp[i].n > EXP_MAX )
			mbr->abl.exp[i].n = EXP_MAX;
		if( flg_set_max )
			mbr->abl.exp[i].max = mbr->abl.exp[i].n;
		if( mbr->abl.exp[i].max < mbr->abl.exp[i].n )
			mbr->abl.exp[i].max = mbr->abl.exp[i].n;
	}

	return chk_lev_up( mbr, flg_set_max, flg_print_lev, flg_draw_lev );
}

/***************************************************************
* メンバーのスキルに経験値を与える
* mbr_t *mbr : メンバー
* long exp : 経験値
* bool_t flg_set_max : 経験値を回復不能にするか
* bool_t flg_print_lev : レベルのメッセージを表示するか
* bool_t flg_draw_lev : レベルの VFX を表示するか
* return : レベルが変化したか?
***************************************************************/

bool_t	exp_mbr_skill(
	mbr_t *mbr,
	long exp,
	bool_t flg_set_max,
	bool_t flg_print_lev,
	bool_t flg_draw_lev
)
{
	long	i, j, r;
	skill_kind_t	kind;
	class_t	*class_tab;
	rate_t	rate;
	long	exp_add, exp_pool;
	bool_t	flg_lev_up;

	if( mbr == NULL )
		return FALSE;

	class_tab = get_class_tab();
	if( class_tab == NULL )
		return FALSE;

	/* 経験値を割り振る */

	exp_pool = exp;
	for( i = 0; i < SKILL_MAX_N; i++ ){
		kind = class_tab[mbr->class_n].skill[i];
		if( kind == SKILL_KIND_NULL )
			continue;
		if( exp_pool < 0 )
			break;

		rate = calc_skill_exp_rate(
				&(class_tab[mbr->class_n]), kind );
		exp_add = exp * rate / _100_PERCENT;
		if( exp_add > exp_pool )
			exp_add = exp_pool;

		exp_pool -= exp_mbr_skill_1( mbr, exp_add, kind,
				flg_set_max );
	}

	/* 余った経験値をさらに割り振る */

	r = randm( SKILL_MAX_N );
	for( j = 0; j < SKILL_MAX_N; j++ ){
		i = (r + j) % SKILL_MAX_N;

		kind = class_tab[mbr->class_n].skill[i];
		if( kind == SKILL_KIND_NULL )
			continue;
		if( exp_pool < 0 )
			break;

		exp_pool -= exp_mbr_skill_1( mbr, exp_pool, kind,
				flg_set_max );
	}

	flg_lev_up = chk_lev_up( mbr, flg_set_max,
			flg_print_lev, flg_draw_lev );

	/* 余った経験値を捨てる時は警告する */

	if( (exp_pool > 0) && flg_print_lev ){
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_EXP_MBR_SKILL,
				mbr->name, exp_pool );
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_EXP_MBR_SKILL_HINT );
		curs_attrset_dflt();
	}

	return flg_lev_up;
}

/***************************************************************
* メンバーの指定のスキルに経験値を与える
* mbr_t *mbr : メンバー
* long exp : 経験値
* skill_kind_t kind : スキルの種類
* bool_t flg_set_max : 経験値を回復不能にするか
* return : 実際に増えた経験値
***************************************************************/

long	exp_mbr_skill_1(
	mbr_t *mbr,
	long exp,
	skill_kind_t kind,
	bool_t flg_set_max
)
{
	long	pre_exp, exp_add;
	abl_kind_t	spc_abl;
	long	i;

	if( mbr == NULL )
		return exp;

	i = ABL_KIND_MAX_N + kind;
	pre_exp = mbr->abl.exp[i].n;

	mbr->abl.exp[i].n += (long)exp;

	/* 冒険者レベルより高くできない */
	spc_abl = get_specialist_abl( mbr );
	if( mbr->abl.exp[i].n > mbr->abl.exp[spc_abl].n )
		mbr->abl.exp[i].n = mbr->abl.exp[spc_abl].n;

	if( mbr->abl.exp[i].n < 0 )
		mbr->abl.exp[i].n = 0;
	if( mbr->abl.exp[i].n > EXP_MAX )
		mbr->abl.exp[i].n = EXP_MAX;
	if( flg_set_max )
		mbr->abl.exp[i].max = mbr->abl.exp[i].n;
	if( mbr->abl.exp[i].max < mbr->abl.exp[i].n )
		mbr->abl.exp[i].max = mbr->abl.exp[i].n;

	exp_add = mbr->abl.exp[i].n - pre_exp;
	return exp_add;
}

/***************************************************************
* モンスターに経験値を与える
* mnstr_t *mnstr : モンスター
* long exp : 経験値
* bool_t flg_set_max : 経験値を回復不能にするか
* bool_t flg_print_lev : レベルのメッセージを表示するか
* bool_t flg_draw_lev : レベルの VFX を表示するか
* return : レベルが変化したか?
***************************************************************/

bool_t	exp_mnstr(
	mnstr_t *mnstr,
	long exp,
	bool_t flg_set_max,
	bool_t flg_print_lev,
	bool_t flg_draw_lev
)
{
	long	left_exp;
	rate_t	abl_sum;
	long	left_k, k;
	long	left_n;

	if( mnstr == NULL )
		return FALSE;
	if( mnstr->mnstr_tab == NULL )
		return FALSE;

	left_exp = exp;
	left_n = 0;
	left_k = 0;

	abl_sum = 0;
	for( k = 0; k < ABL_KIND_MAX_N; k++ )
		abl_sum += mnstr->mnstr_tab->abl_lev_rate[k];
	if( abl_sum <= 0 )
		return FALSE;

	for( k = 0; k < ABL_KIND_MAX_N; k++ ){
		rate_t	abl_rate;
		long	e;

		abl_rate = mnstr->mnstr_tab->abl_lev_rate[k];
		if( abl_rate == 0 )
			continue;

		e = exp * abl_rate / abl_sum;
		mnstr->abl.exp[k].n += e;

		if( mnstr->abl.exp[k].n < 0 )
			mnstr->abl.exp[k].n = 0;
		if( mnstr->abl.exp[k].n > EXP_MAX )
			mnstr->abl.exp[k].n = EXP_MAX;
		if( flg_set_max )
			mnstr->abl.exp[k].max = mnstr->abl.exp[k].n;
		if( mnstr->abl.exp[k].max < mnstr->abl.exp[k].n )
			mnstr->abl.exp[k].max = mnstr->abl.exp[k].n;

		left_exp -= e;
		left_n++;
		if( per_randm( left_n ) )
			left_k = k;
	}

	mnstr->abl.exp[left_k].n += left_exp;

	if( mnstr->abl.exp[left_k].n < 0 )
		mnstr->abl.exp[left_k].n = 0;
	if( mnstr->abl.exp[left_k].n > EXP_MAX )
		mnstr->abl.exp[left_k].n = EXP_MAX;
	if( flg_set_max )
		mnstr->abl.exp[left_k].max = mnstr->abl.exp[left_k].n;
	if( mnstr->abl.exp[left_k].max < mnstr->abl.exp[left_k].n )
		mnstr->abl.exp[left_k].max = mnstr->abl.exp[left_k].n;

	return chk_lev_up( mnstr, FALSE, flg_print_lev, flg_draw_lev );
}

/***************************************************************
* キャラクタのレベルの変化を調べる
* chr_t *chr : キャラクタ
* bool_t flg_set_max : 経験値を回復不能にするか
* bool_t flg_print : レベルのメッセージを表示するか
* bool_t flg_draw : レベルの VFX を表示するか
* return : レベルが変化したか?
***************************************************************/

bool_t	chk_lev_up(
	chr_t *chr, bool_t flg_set_max,
	bool_t flg_print, bool_t flg_draw
)
{
	long	i, j;
	long	need_exp;
	bool_t	flg_lev_up, flg_lev_down;

	if( chr == NULL )
		return FALSE;

	flg_lev_up = FALSE;
	flg_lev_down = FALSE;

	for( i = 0; i < ABL_SKILL_MAX_N; i++ ){
		abl_kind_t	n;

		n = (abl_kind_t)i;
		if( n == ABL_KIND_MAX_N + SKILL_KIND_NULL )
			continue;

		if( chr->abl.exp[i].n > EXP_MAX )
			chr->abl.exp[i].n = EXP_MAX;

		for( j = 0; j < ABL_MAX_LEV * 2; j++ ){
			need_exp = calc_need_exp( chr->abl.lev[n].n + 1, n );
			if( chr->abl.exp[i].n < need_exp )
				break;

			if( set_lev_up( chr, n, +1, flg_set_max, flg_print ) )
				flg_lev_up = TRUE;
			else
				break;
		}

		for( j = 0; j < ABL_MAX_LEV * 2; j++ ){
			need_exp = calc_need_exp( chr->abl.lev[n].n - 0, n );
			if( chr->abl.exp[i].n >= need_exp )
				break;

			if( set_lev_up( chr, n, -1, flg_set_max, flg_print ) )
				flg_lev_down = TRUE;
			else
				break;
		}
	}

	if( flg_draw ){
		if( flg_lev_down ){
			draw_lev_up( chr->x, chr->y, -1, chr );
		} else if( flg_lev_up ){
			draw_lev_up( chr->x, chr->y, +1, chr );
		}
	}

	return( flg_lev_up || flg_lev_down );
}

/***************************************************************
* キャラクタのレベルを上下する
* chr_t *chr : キャラクタ
* abl_kind_t abl : 能力値
* long add : レベル
* bool_t flg_set_max : 経験値を回復不能にするか
* bool_t flg_print : レベルのメッセージを表示するか
* return : 上下したか
***************************************************************/

bool_t	set_lev_up(
	chr_t *chr,
	abl_kind_t abl,
	long add,
	bool_t flg_set_max,
	bool_t flg_print )
{
	if( chr == NULL )
		return FALSE;

	chr->abl.lev[abl].n += add;
	if( flg_set_max )
		chr->abl.lev[abl].max = chr->abl.lev[abl].n;
	if( chr->abl.lev[abl].max < chr->abl.lev[abl].n )
		chr->abl.lev[abl].max = chr->abl.lev[abl].n;

	if( abl == ABL_KIND_HP ){
		chr->abl.hp.max = calc_max_hp( chr );
		if( add >= +1 )
			chr->abl.hp.n = chr->abl.hp.max;
		if( chr->abl.hp.n > chr->abl.hp.max )
			chr->abl.hp.n = chr->abl.hp.max;
	}
	if( abl == ABL_KIND_MP ){
		chr->abl.mp.max = calc_max_mp( chr );
		if( add >= +1 )
			chr->abl.mp.n = chr->abl.mp.max;
		if( chr->abl.mp.n > chr->abl.mp.max )
			chr->abl.mp.n = chr->abl.mp.max;
	}

	if( flg_print ){
		curs_attrset_chr( chr, add, TRUE );
		if( add > 0 ){
			call_game_sound_play( SOUND_KIND_LEVEL_UP, 1 );

			print_msg( FLG_NULL, MSG_LEV_UP,
					chr->name,
					get_abl_name( abl ),
					chr->abl.lev[abl].n );
		}
		if( add < 0 ){
			call_game_sound_play( SOUND_KIND_LEVEL_DOWN, 1 );

			print_msg( FLG_NULL, MSG_LEV_DOWN,
					chr->name,
					get_abl_name( abl ),
					chr->abl.lev[abl].n );
		}
		curs_attrset_dflt();
	}

	if( (add < 0) && (chr->abl.lev[abl].n <= 0) ){
		chr->abl.lev[abl].n = 0;
		chr->abl.lev[abl].max = 0;
		return FALSE;
	}

	if( add > 0 )
		learn_spell_sha( chr );

	return TRUE;
}

/***************************************************************
* キャラクタの全ての修正値を設定
* chr_t *chr : キャラクタ
***************************************************************/

void	set_modifier( chr_t *chr )
{
	bool_t	flg_song;
	long	i;

	if( chr == NULL )
		return;

	/* リセット */

	chr->face.mjr = chr->face.mjr_org;
	chr->face.mnr = chr->face.mnr_org;
	chr->sex.cur = chr->sex.org;

	chr->fx_data.wpn_hit = (rate_t)0;
	chr->fx_data.wpn_crtcl = (rate_t)0;
	chr->fx_data.wpn_dam = (rate_t)0;

	chr->fx_data.armor_def = (rate_t)0;
	chr->fx_data.armor_crtcl = (rate_t)0;
	chr->fx_data.armor_ac = (rate_t)0;

	for( i = 0; i < ABL_SKILL_MAX_N; i++ )
		chr->abl.lev[i].add = 0;
	for( i = 0; i < RESI_KIND_MAX_N; i++ )
		chr->resi[i].add_n = 0;
	chr->fx_data.resi_stat = FLG_NULL;

	chr->fx_data.cure_hp.count = 0;
	chr->fx_data.cure_hp.turn = 0;
	chr->fx_data.cure_hp.rate = (rate_t)0;
	chr->fx_data.cure_hp.n = 0;

	chr->fx_data.cure_mp.count = 0;
	chr->fx_data.cure_mp.turn = 0;
	chr->fx_data.cure_mp.rate = (rate_t)0;
	chr->fx_data.cure_mp.n = 0;

	chr->move.speed.n = 0;
	chr->fx_data.stomach.digest_n = 0;
	chr->work.teleport_n = 0;
	chr->work.teleport_party_n = 0;
	chr->fx_data.bless = 0;

	/* 装備の効果をセット */

	set_modifier_fx_data_equip( chr );

	/* エフェクトの値をセット */

	set_modifier_fx_data_fx( chr );

	/* 呪歌の値をセット */

	flg_song = TRUE;
	if( chk_flg( chr->stat, FLG_STAT_CONFUSION ) )
		flg_song = FALSE;
	if( chk_flg( chr->stat, FLG_STAT_SLEEP ) )
		flg_song = FALSE;
	if( chk_flg( chr->stat, FLG_STAT_SILENCE ) )
		flg_song = FALSE;

	if( flg_song )
		set_modifier_fx_data_song( chr );

	/**/

	chr->abl.hp.max = calc_max_hp( chr );
	chr->abl.mp.max = calc_max_mp( chr );

	set_move_rate( chr );
}

/***************************************************************
* キャラクタの装備の修正値を設定
* chr_t *chr : キャラクタ
***************************************************************/

void	set_modifier_fx_data_equip( chr_t *chr )
{
	long	i;

	if( chr == NULL )
		return;

	/* 効果を計算する */

	calc_modifier_equip( chr );

	/* 装備の効果をセット */

	if( chr->modifier_equip.face_mjr != FACE_MJR_NULL )
		chr->face.mjr = chr->modifier_equip.face_mjr;
	if( chr->modifier_equip.face_mnr != FACE_MNR_NULL )
		chr->face.mnr = chr->modifier_equip.face_mnr;
	if( chr->modifier_equip.sex != SEX_NULL )
		chr->sex.cur = chr->modifier_equip.sex;

	chr->fx_data.wpn_hit += chr->modifier_equip.wpn_hit;
	chr->fx_data.wpn_crtcl += chr->modifier_equip.wpn_crtcl;
	chr->fx_data.wpn_dam += chr->modifier_equip.wpn_dam;

	chr->fx_data.armor_def += chr->modifier_equip.armor_def;
	chr->fx_data.armor_crtcl += chr->modifier_equip.armor_crtcl;
	chr->fx_data.armor_ac += chr->modifier_equip.armor_ac;

	for( i = 0; i < ABL_SKILL_MAX_N; i++ )
		chr->abl.lev[i].add += chr->modifier_equip.add_lev[i];
	for( i = 0; i < RESI_KIND_MAX_N; i++ )
		chr->resi[i].add_n += chr->modifier_equip.add_resi_n[i];
	chr->fx_data.resi_stat |= chr->modifier_equip.resi_stat;

	chr->fx_data.cure_hp.count += chr->modifier_equip.cure_hp.count;
	chr->fx_data.cure_hp.turn += chr->modifier_equip.cure_hp.turn;
	chr->fx_data.cure_hp.rate += chr->modifier_equip.cure_hp.rate;
	chr->fx_data.cure_hp.n += chr->modifier_equip.cure_hp.n;

	chr->fx_data.cure_mp.count += chr->modifier_equip.cure_mp.count;
	chr->fx_data.cure_mp.turn += chr->modifier_equip.cure_mp.turn;
	chr->fx_data.cure_mp.rate += chr->modifier_equip.cure_mp.rate;
	chr->fx_data.cure_mp.n += chr->modifier_equip.cure_mp.n;

	chr->move.speed.n += chr->modifier_equip.add_move_speed;
	chr->fx_data.stomach.digest_n
			+= chr->modifier_equip.stomach_digest_n;
	chr->work.teleport_n
			+= chr->modifier_equip.teleport_n;
	chr->work.teleport_party_n
			+= chr->modifier_equip.teleport_party_n;

	if( chr->modifier_equip.bless != 0 )
		chr->fx_data.bless = chr->modifier_equip.bless;

}

/***************************************************************
* キャラクタのエフェクトの修正値を設定
* chr_t *chr : キャラクタ
***************************************************************/

void	set_modifier_fx_data_fx( chr_t *chr )
{
	long	i;

	if( chr == NULL )
		return;

	/* エフェクトの値をセット */

	if( chr->modifier_fx.face_mjr != FACE_MJR_NULL )
		chr->face.mjr = chr->modifier_fx.face_mjr;
	if( chr->modifier_fx.face_mnr != FACE_MNR_NULL )
		chr->face.mnr = chr->modifier_fx.face_mnr;
	if( chr->modifier_fx.sex != SEX_NULL )
		chr->sex.cur = chr->modifier_fx.sex;

	chr->fx_data.wpn_hit += chr->modifier_fx.wpn_hit;
	chr->fx_data.wpn_crtcl += chr->modifier_fx.wpn_crtcl;
	chr->fx_data.wpn_dam += chr->modifier_fx.wpn_dam;

	chr->fx_data.armor_def += chr->modifier_fx.armor_def;
	chr->fx_data.armor_crtcl += chr->modifier_fx.armor_crtcl;
	chr->fx_data.armor_ac += chr->modifier_fx.armor_ac;

	for( i = 0; i < ABL_SKILL_MAX_N; i++ )
		chr->abl.lev[i].add += chr->modifier_fx.add_lev[i];
	for( i = 0; i < RESI_KIND_MAX_N; i++ )
		chr->resi[i].add_n += chr->modifier_fx.add_resi_n[i];
	chr->fx_data.resi_stat |= chr->modifier_fx.resi_stat;

	chr->fx_data.cure_hp.count += chr->modifier_fx.cure_hp.count;
	chr->fx_data.cure_hp.turn += chr->modifier_fx.cure_hp.turn;
	chr->fx_data.cure_hp.rate += chr->modifier_fx.cure_hp.rate;
	chr->fx_data.cure_hp.n += chr->modifier_fx.cure_hp.n;

	chr->fx_data.cure_mp.count += chr->modifier_fx.cure_mp.count;
	chr->fx_data.cure_mp.turn += chr->modifier_fx.cure_mp.turn;
	chr->fx_data.cure_mp.rate += chr->modifier_fx.cure_mp.rate;
	chr->fx_data.cure_mp.n += chr->modifier_fx.cure_mp.n;

	chr->move.speed.n += chr->modifier_fx.add_move_speed;
	chr->fx_data.stomach.digest_n
			+= chr->modifier_fx.stomach_digest_n;
	chr->work.teleport_n
			+= chr->modifier_fx.teleport_n;
	chr->work.teleport_party_n
			+= chr->modifier_fx.teleport_party_n;

	if( chr->modifier_equip.bless != 0 )
		chr->fx_data.bless = chr->modifier_equip.bless;
}

/***************************************************************
* キャラクタの呪歌の修正値を設定
* chr_t *chr : キャラクタ
***************************************************************/

void	set_modifier_fx_data_song( chr_t *chr )
{
	modifier_t	*modifier_song;
	long	i;

	if( chr == NULL )
		return;

	/* 呪歌の値をセット */

	if( is_mbr( chr ) ){
		modifier_song = get_modifier_song_mbr();
	} else if( chr->kind == CHR_KIND_MNSTR ){
		if( is_pet( chr ) ){
			modifier_song = get_modifier_song_pet();
		} else {
			modifier_song = get_modifier_song_mnstr();
		}
	} else {
		modifier_song = get_modifier_song_mnstr();
	}

	if( modifier_song->face_mjr != FACE_MJR_NULL )
		chr->face.mjr = modifier_song->face_mjr;
	if( modifier_song->face_mnr != FACE_MNR_NULL )
		chr->face.mnr = modifier_song->face_mnr;
	if( modifier_song->sex != SEX_NULL )
		chr->sex.cur = modifier_song->sex;

	chr->fx_data.wpn_hit += modifier_song->wpn_hit;
	chr->fx_data.wpn_crtcl += modifier_song->wpn_crtcl;
	chr->fx_data.wpn_dam += modifier_song->wpn_dam;

	chr->fx_data.armor_def += modifier_song->armor_def;
	chr->fx_data.armor_crtcl += modifier_song->armor_crtcl;
	chr->fx_data.armor_ac += modifier_song->armor_ac;

	for( i = 0; i < ABL_SKILL_MAX_N; i++ )
		chr->abl.lev[i].add += modifier_song->add_lev[i];
	for( i = 0; i < RESI_KIND_MAX_N; i++ )
		chr->resi[i].add_n += modifier_song->add_resi_n[i];
	chr->fx_data.resi_stat |= modifier_song->resi_stat;

	chr->fx_data.cure_hp.count += modifier_song->cure_hp.count;
	chr->fx_data.cure_hp.turn += modifier_song->cure_hp.turn;
	chr->fx_data.cure_hp.rate += modifier_song->cure_hp.rate;
	chr->fx_data.cure_hp.n += modifier_song->cure_hp.n;

	chr->fx_data.cure_mp.count += modifier_song->cure_mp.count;
	chr->fx_data.cure_mp.turn += modifier_song->cure_mp.turn;
	chr->fx_data.cure_mp.rate += modifier_song->cure_mp.rate;
	chr->fx_data.cure_mp.n += modifier_song->cure_mp.n;

	chr->move.speed.n += modifier_song->add_move_speed;
	chr->fx_data.stomach.digest_n
			+= modifier_song->stomach_digest_n;
	chr->work.teleport_n
			+= modifier_song->teleport_n;
	chr->work.teleport_party_n
			+= modifier_song->teleport_party_n;

	if( chr->modifier_equip.bless != 0 )
		chr->fx_data.bless = chr->modifier_equip.bless;
}

/***************************************************************
* キャラクタの装備の修正値の合計を計算
* chr_t *chr : キャラクタ
* return : エラーが無かったか
***************************************************************/

bool_t	calc_modifier_equip( chr_t *chr )
{
	item_t	*eq;
	long	i, j;
	modifier_t	*src, *dst;

	if( chr == NULL )
		return FALSE;
	if( chr->kind != CHR_KIND_MBR )
		return FALSE;

	dst = &(chr->modifier_equip);
	if( !reset_modifier( dst ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( chr );
	if( eq == NULL )
		return FALSE;

	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		if( eq[i].kind == ITEM_KIND_NULL )
			continue;

		src = &(eq[i].modifier);

		if( src->face_mjr != FACE_MJR_NULL )
			dst->face_mjr = src->face_mjr;
		if( src->face_mnr != FACE_MNR_NULL )
			dst->face_mnr = src->face_mnr;
		if( src->sex != SEX_NULL )
			dst->sex = src->sex;

		dst->wpn_hit += src->wpn_hit;
		dst->wpn_crtcl += src->wpn_crtcl;
		dst->wpn_dam += src->wpn_dam;

		dst->armor_def += src->armor_def;
		dst->armor_crtcl += src->armor_crtcl;
		dst->armor_ac += src->armor_ac;

		for( j = 0; j < ABL_SKILL_MAX_N; j++ )
			dst->add_lev[j] += src->add_lev[j];
		for( j = 0; j < RESI_KIND_MAX_N; j++ )
			dst->add_resi_n[j] += src->add_resi_n[j];

		dst->cure_hp.count += src->cure_hp.count;
		dst->cure_hp.turn += src->cure_hp.turn;
		dst->cure_hp.rate += src->cure_hp.rate;
		dst->cure_hp.n += src->cure_hp.n;

		dst->cure_mp.count += src->cure_mp.count;
		dst->cure_mp.turn += src->cure_mp.turn;
		dst->cure_mp.rate += src->cure_mp.rate;
		dst->cure_mp.n += src->cure_mp.n;

		dst->add_move_speed += src->add_move_speed;
		dst->stomach_digest_n += src->stomach_digest_n;
		dst->teleport_n += src->teleport_n;
		dst->teleport_party_n += src->teleport_party_n;

		if( src->bless != 0 )
			dst->bless = src->bless;

		dst->resi_stat |= src->resi_stat;
	}

	return TRUE;
}

/***************************************************************
* 修正値を初期化
* modifier_t *m : 修正値
* return : エラーが無かったか
***************************************************************/

bool_t	reset_modifier( modifier_t *m )
{
	long	i;

	if( m == NULL )
		return FALSE;

	m->face_mjr = FACE_MJR_NULL;
	m->face_mnr = FACE_MNR_NULL;
	m->sex = SEX_NULL;

	m->wpn_hit = (rate_t)0;
	m->wpn_crtcl = (rate_t)0;
	m->wpn_dam = (rate_t)0;

	m->armor_def = (rate_t)0;
	m->armor_crtcl = (rate_t)0;
	m->armor_ac = (rate_t)0;

	for( i = 0; i < ABL_SKILL_MAX_N; i++ )
		m->add_lev[i] = 0;
	for( i = 0; i < RESI_KIND_MAX_N; i++ )
		m->add_resi_n[i] = 0;

	m->cure_hp.count = 0;
	m->cure_hp.turn = 0;
	m->cure_hp.rate = (rate_t)0;
	m->cure_hp.n = 0;

	m->cure_mp.count = 0;
	m->cure_mp.turn = 0;
	m->cure_mp.rate = (rate_t)0;
	m->cure_mp.n = 0;

	m->add_move_speed = 0;
	m->stomach_digest_n = 0;
	m->teleport_n = 0;
	m->teleport_party_n = 0;

	m->bless = 0;
	m->resi_stat = FLG_STAT_NULL;

	return TRUE;
}

/***************************************************************
* 装備の修正値を取得
* chr_t *chr : キャラクタ
* modifier_t *m : 修正値を返す
* return : エラーが無かったか
***************************************************************/

bool_t	get_modifier_equip( chr_t *chr, modifier_t *m )
{
	if( chr == NULL )
		return FALSE;
	if( m == NULL )
		return FALSE;

	*m = chr->modifier_equip;

	return TRUE;
}

/***************************************************************
* 装備の修正値を代入
* chr_t *chr : キャラクタ
* modifier_t *m : 修正値
* return : エラーが無かったか
***************************************************************/

bool_t	set_modifier_equip( chr_t *chr, modifier_t *m )
{
	if( chr == NULL )
		return FALSE;
	if( m == NULL )
		return FALSE;

	chr->modifier_equip = *m;

	set_modifier( chr );

	return TRUE;
}

/***************************************************************
* エフェクトの修正値を取得
* chr_t *chr : キャラクタ
* modifier_t *m : 修正値を返す
* return : エラーが無かったか
***************************************************************/

bool_t	get_modifier_fx( chr_t *chr, modifier_t *m )
{
	if( chr == NULL )
		return FALSE;
	if( m == NULL )
		return FALSE;

	*m = chr->modifier_fx;

	return TRUE;
}

/***************************************************************
* エフェクトの修正値を代入
* chr_t *chr : キャラクタ
* modifier_t *m : 修正値
* return : エラーが無かったか
***************************************************************/

bool_t	set_modifier_fx( chr_t *chr, modifier_t *m )
{
	if( chr == NULL )
		return FALSE;
	if( m == NULL )
		return FALSE;

	chr->modifier_fx = *m;

	set_modifier( chr );

	return TRUE;
}

/***************************************************************
* 状態異常を抵抗出来るか調べる(AND 条件)
* chr_t *chr : キャラクタ
* flg_stat_t stat : 状態異常の種類
* return : 抵抗出来るか
***************************************************************/

bool_t	chk_resi_stat( chr_t *chr, flg_stat_t stat )
{
	char	mnr;

	if( chr == NULL )
		return FALSE;

	/* 盲目の時は石化しない */

	if( chk_flg( stat, FLG_STAT_STONE ) )
		if( chk_flg( chr->stat, FLG_STAT_BLIND ) )
			return TRUE;

	/* 現在の耐性を調べる */

	if( chk_flg( chr->fx_data.resi_stat, stat ) )
		return TRUE;

	/* ランダム・アーティファクトの耐性 */

	mnr = cv_flg_stat_to_armor_randm_art_mnr( stat );
	if( (mnr != ' ') && chk_armor_randm_art(
			ARMOR_RANDM_ART_KIND_RESI_STAT,
			mnr, NULL, chr ) ){
		print_msg( FLG_MSG_DEBUG, "resi stat [%c]", (char)mnr );
		return TRUE;
	}

	/* デフォルトの耐性を調べる */

	do {
		if( chr->kind != CHR_KIND_MNSTR )
			break;
		if( chr->mnstr_tab == NULL )
			break;
		if( !chk_flg( chr->mnstr_tab->resi_stat, stat ) )
			break;

		return TRUE;
	} while( 0 );

	return FALSE;
}

/***************************************************************
* 状態異常を抵抗出来るか調べる(OR 条件)
* chr_t *chr : キャラクタ
* flg_stat_t stat : 状態異常の種類
* return : 抵抗出来るか
***************************************************************/

bool_t	chk_resi_stat_or( chr_t *chr, flg_stat_t stat )
{
	modifier_t	*mod;

	if( chr == NULL )
		return FALSE;

	if( chk_flg_or( chr->modifier_equip.resi_stat, stat ) )
		return TRUE;
	if( chk_flg_or( chr->modifier_fx.resi_stat, stat ) )
		return TRUE;

	if( is_mbr( chr ) ){
		mod = get_modifier_song_mbr();
	} else if( chr->kind == CHR_KIND_MNSTR ){
		if( is_pet( chr ) ){
			mod = get_modifier_song_pet();
		} else {
			mod = get_modifier_song_mnstr();
		}
	} else {
		mod = get_modifier_song_mnstr();
	}
	if( (mod != NULL) && chk_flg_or( mod->resi_stat, stat ) ){
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* キャラクタの移動速度を修正
* chr_t *chr : キャラクタ
* return : 移動速度
***************************************************************/

rate_t	set_move_rate( chr_t *chr )
{
	chr->move.speed.rate = modified_rate( chr->move.speed.rate_org,
			chr->move.speed.n );

	return chr->move.speed.rate;
}

/***************************************************************
* キャラクタの移動速度を取得
* chr_t *chr : キャラクタ
* return : 移動速度
***************************************************************/

rate_t	get_move_rate( chr_t *chr )
{
	rate_t	speed, skill_rate;

	speed = chr->move.speed.rate;
	skill_rate = calc_skill_rate( chr, SKILL_KIND_RUN_AWAY );

	speed = speed * skill_rate / _100_PERCENT;

	return speed;
}

/***************************************************************
* 性別の文字列を返す
* sex_t sex : 性別
* return : 性別の文字列
***************************************************************/

const char	*get_sex_name( mnstr_kind_t kind, sex_t sex )
{
	bool_t	flg_mnstr;

	flg_mnstr = TRUE;

	switch( kind ){
	case MNSTR_KIND_NULL:
		flg_mnstr = FALSE;
		break;
	/* 神 */
	/* ドラゴン */
	case MNSTR_KIND_A_GOLD_DRAGON:
	case MNSTR_KIND_A_SILVER_DRAGON:
	case MNSTR_KIND_A_COPPER_DRAGON:
	case MNSTR_KIND_A_RED_DRAGON:
	case MNSTR_KIND_A_BLUE_DRAGON:
	case MNSTR_KIND_A_GREEN_DRAGON:
	case MNSTR_KIND_A_YELLOW_DRAGON:
	case MNSTR_KIND_A_WHITE_DRAGON:
	case MNSTR_KIND_A_BLACK_DRAGON:
	case MNSTR_KIND_M_GOLD_DRAGON:
	case MNSTR_KIND_M_SILVER_DRAGON:
	case MNSTR_KIND_M_COPPER_DRAGON:
	case MNSTR_KIND_M_RED_DRAGON:
	case MNSTR_KIND_M_BLUE_DRAGON:
	case MNSTR_KIND_M_GREEN_DRAGON:
	case MNSTR_KIND_M_YELLOW_DRAGON:
	case MNSTR_KIND_M_WHITE_DRAGON:
	case MNSTR_KIND_M_BLACK_DRAGON:
		flg_mnstr = TRUE;
		break;
	/* 幻獣 */
	case MNSTR_KIND_PHOENIX:
	case MNSTR_KIND_UNICORN:
	case MNSTR_KIND_PYON_PYON:
		flg_mnstr = TRUE;
		break;
	/* 妖精 */
	case MNSTR_KIND_LEPRECHAUN:
		flg_mnstr = FALSE;
		break;
	/* 精霊 */
	case MNSTR_KIND_FIRE_ELEMENTAL:
	case MNSTR_KIND_SALAMANDER:
	case MNSTR_KIND_WATER_ELEMENTAL:
	case MNSTR_KIND_UNDINE:
	case MNSTR_KIND_AIR_ELEMENTAL:
	case MNSTR_KIND_SYLPH:
	case MNSTR_KIND_EARTH_ELEMENTAL:
	case MNSTR_KIND_GNOME:
	case MNSTR_KIND_WILL_O_WISP:
	case MNSTR_KIND_SHADE:
		flg_mnstr = TRUE;
		break;
	/* 植物 */
	case MNSTR_KIND_VENUS_FLY_TRAP:
	case MNSTR_KIND_SLIME:
	case MNSTR_KIND_SPORE:
		flg_mnstr = TRUE;
		break;
	/* 動物 */
	case MNSTR_KIND_GIANT_BAT:
	case MNSTR_KIND_GIANT_RAT:
	case MNSTR_KIND_GIANT_SNAKE:
	case MNSTR_KIND_VIPER_SNAKE:
	case MNSTR_KIND_CAT:
	case MNSTR_KIND_DOG:
	case MNSTR_KIND_WOLF:
		flg_mnstr = TRUE;
		break;
	/* 昆虫 */
	case MNSTR_KIND_GIANT_CENTIPEDE:
	case MNSTR_KIND_GIANT_BEE:
	case MNSTR_KIND_GIANT_SCORPION:
	case MNSTR_KIND_GIANT_ANT:
	case MNSTR_KIND_GIANT_SPIDER:
	case MNSTR_KIND_ACID_FLY:
	case MNSTR_KIND_GIANT_BEETLE:
		flg_mnstr = TRUE;
		break;
	/* 人間 */
	case MNSTR_KIND_FIGHTER:
	case MNSTR_KIND_MONK:
	case MNSTR_KIND_HUNTER:
	case MNSTR_KIND_THIEF:
	case MNSTR_KIND_WIZARD:
	case MNSTR_KIND_SUMMONER:
	case MNSTR_KIND_PRIEST:
	case MNSTR_KIND_SHAMAN:
	case MNSTR_KIND_BARD:
	case MNSTR_KIND_NINJA:
	case MNSTR_KIND_BISHOP:
	case MNSTR_KIND_FARMER:
	case MNSTR_KIND_CRAFTSMAN:
	case MNSTR_KIND_MERCHANT:
		flg_mnstr = FALSE;
		break;
	/* 半人 */
	case MNSTR_KIND_HARPY:
	case MNSTR_KIND_ANDRO_SCORPION:
	case MNSTR_KIND_LAMIA:
	case MNSTR_KIND_CENTAUR:
	case MNSTR_KIND_BIRD_MAN:
	case MNSTR_KIND_WEREWOLF:
	case MNSTR_KIND_MINOTAUR:
	case MNSTR_KIND_MEDUSA:
		flg_mnstr = FALSE;
		break;
	/* 巨人 */
	case MNSTR_KIND_YETI:
	case MNSTR_KIND_OGRE:
	case MNSTR_KIND_TROLL:
	case MNSTR_KIND_MORMIN_TROLL:
	case MNSTR_KIND_FIRE_GIANT:
	case MNSTR_KIND_FROST_GIANT:
	case MNSTR_KIND_CLOUD_GIANT:
	case MNSTR_KIND_MOUNTAIN_GIANT:
	case MNSTR_KIND_CYCLOPS:
		flg_mnstr = FALSE;
		break;
	/* 巨大生物 */
	/* 水棲生物 */
	/* 魔法生物 */
	case MNSTR_KIND_INVISIBLE_STALKER:
		flg_mnstr = FALSE;
		break;
	case MNSTR_KIND_GARGOYLE:
	case MNSTR_KIND_MIMIC:
	case MNSTR_KIND_WOOD_GOLEM:
	case MNSTR_KIND_BONE_GOLEM:
	case MNSTR_KIND_FLESH_GOLEM:
	case MNSTR_KIND_STONE_GOLEM:
	case MNSTR_KIND_IRON_GOLEM:
	case MNSTR_KIND_GAS_CLOUD:
		flg_mnstr = TRUE;
		break;
	/* 合成獣 */
	case MNSTR_KIND_HIPPOGRIFF:
	case MNSTR_KIND_GRIFFON:
	case MNSTR_KIND_MANTICORE:
	case MNSTR_KIND_CHIMERA:
		flg_mnstr = TRUE;
		break;
	/* アンデッド */
	case MNSTR_KIND_POLTERGEIST:
	case MNSTR_KIND_SKELETON:
	case MNSTR_KIND_ZOMBIE:
	case MNSTR_KIND_GHOUL:
	case MNSTR_KIND_GHOST:
	case MNSTR_KIND_WIGHT:
	case MNSTR_KIND_MUMMY:
	case MNSTR_KIND_DURAHAN:
	case MNSTR_KIND_BANSHEE:
	case MNSTR_KIND_WRAITH:
	case MNSTR_KIND_VAMPIRE:
	case MNSTR_KIND_SPIRIT:
		flg_mnstr = FALSE;
		break;
	/* 妖魔 */
	case MNSTR_KIND_KOBOLD:
	case MNSTR_KIND_GNOLL:
	case MNSTR_KIND_GOBLIN:
	case MNSTR_KIND_HOBGOBLIN:
	case MNSTR_KIND_GREMLIN:
	case MNSTR_KIND_ORK:
	case MNSTR_KIND_EFREET:
	case MNSTR_KIND_DJINNI:
		flg_mnstr = FALSE;
		break;
	/* 魔獣 */
	case MNSTR_KIND_RUST_MONSTER:
	case MNSTR_KIND_HELLHOUND:
	case MNSTR_KIND_HYDRA:
	case MNSTR_KIND_COCKATRICE:
	case MNSTR_KIND_WYVERN:
	case MNSTR_KIND_CERBERUS:
	case MNSTR_KIND_GORGON:
	case MNSTR_KIND_BASILISK:
		flg_mnstr = TRUE;
		break;
	/* 悪魔 */
	case MNSTR_KIND_IMP:
		flg_mnstr = FALSE;
		break;
	case MNSTR_KIND_JACK_O_LANTERN:
		flg_mnstr = TRUE;
		break;
	case MNSTR_KIND_SUCCUBUS:
	case MNSTR_KIND_INCUBUS:
		flg_mnstr = FALSE;
		break;
	case MNSTR_KIND_LESSER_DAEMON:
	case MNSTR_KIND_GREATER_DAEMON:
		flg_mnstr = TRUE;
		break;
	/* 中ボス */
	case MNSTR_KIND_HIGH_RE_HOO:
	case MNSTR_KIND_GREAT_MINOTAUR:
		flg_mnstr = FALSE;
		break;
	case MNSTR_KIND_BILLION_ELEMENTAL:
		flg_mnstr = TRUE;
		break;
	case MNSTR_KIND_CYBERN:
		flg_mnstr = FALSE;
		break;
	case MNSTR_KIND_GIGANTIC_CENTIPEDE:
		flg_mnstr = TRUE;
		break;
	case MNSTR_KIND_MEDUSA_ZOMBIE:
		flg_mnstr = FALSE;
		break;
	case MNSTR_KIND_BLACK_UNICORN:
		flg_mnstr = TRUE;
		break;
	case MNSTR_KIND_VAMPIRE_LORD:
		flg_mnstr = FALSE;
		break;
	case MNSTR_KIND_RELATIVISTIC_DAEMON:
	case MNSTR_KIND_ETERNAL_DRAGON:
		flg_mnstr = TRUE;
		break;
	/* ラスボス */
	case MNSTR_KIND_EXEL:
	case MNSTR_KIND_EXELER:
	case MNSTR_KIND_XEX:
		flg_mnstr = FALSE;
		break;
	case MNSTR_KIND_XX:
		flg_mnstr = TRUE;
		break;
	/**/
	case MNSTR_KIND_MAX_N:
		flg_mnstr = TRUE;
		break;
	}

	if( flg_mnstr ){
		if( sex == FEMALE )
			return MSG_FEMALE_MNSTR;
		else
			return MSG_MALE_MNSTR;
	} else {
		if( sex == FEMALE )
			return MSG_FEMALE;
		else
			return MSG_MALE;
	}

	return MSG_FEMALE_MNSTR;
}

/***************************************************************
* 能力値の種類を名前に変換
* abl_kind_t kind : 能力値
* return : 名前
***************************************************************/

char	*get_abl_name( abl_kind_t kind )
{
	switch( (long)kind ){
	case ABL_KIND_HP:
		return MSG_ABL_NAME_HP;
	case ABL_KIND_MP:
		return MSG_ABL_NAME_MP;
	case ABL_KIND_DEX:
		return MSG_ABL_NAME_DEX;
	case ABL_KIND_STR:
		return MSG_ABL_NAME_STR;
	case ABL_KIND_AGI:
		return MSG_ABL_NAME_AGI;
	case ABL_KIND_INT:
		return MSG_ABL_NAME_INT;
	case ABL_KIND_WIS:
		return MSG_ABL_NAME_WIS;
	case ABL_KIND_CHA:
		return MSG_ABL_NAME_CHA;
	case ABL_KIND_FIG:
		return MSG_ABL_NAME_FIG;
	case ABL_KIND_MON:
		return MSG_ABL_NAME_MON;
	case ABL_KIND_HUN:
		return MSG_ABL_NAME_HUN;
	case ABL_KIND_THI:
		return MSG_ABL_NAME_THI;
	case ABL_KIND_MAG:
		return MSG_ABL_NAME_MAG;
	case ABL_KIND_SOR:
		return MSG_ABL_NAME_SOR;
	case ABL_KIND_ENC:
		return MSG_ABL_NAME_ENC;
	case ABL_KIND_SUM:
		return MSG_ABL_NAME_SUM;
	case ABL_KIND_PRI:
		return MSG_ABL_NAME_PRI;
	case ABL_KIND_SHA:
		return MSG_ABL_NAME_SHA;
	case ABL_KIND_BAR:
		return MSG_ABL_NAME_BAR;
	case ABL_KIND_NIN:
		return MSG_ABL_NAME_NIN;
	case ABL_KIND_MAX_N + SKILL_KIND_NULL:
		return MSG_ABL_NAME_NULL;
	case ABL_KIND_MAX_N + SKILL_KIND_ATTACKER:
		return MSG_ABL_NAME_ATTACKER;
	case ABL_KIND_MAX_N + SKILL_KIND_BERSERKER:
		return MSG_ABL_NAME_BERSERKER;
	case ABL_KIND_MAX_N + SKILL_KIND_DEFENDER:
		return MSG_ABL_NAME_DEFENDER;
	case ABL_KIND_MAX_N + SKILL_KIND_SENTINEL:
		return MSG_ABL_NAME_SENTINEL;
	case ABL_KIND_MAX_N + SKILL_KIND_ASSASSIN:
		return MSG_ABL_NAME_ASSASSIN;
	case ABL_KIND_MAX_N + SKILL_KIND_AEGIS:
		return MSG_ABL_NAME_AEGIS;
	case ABL_KIND_MAX_N + SKILL_KIND_SIEGE:
		return MSG_ABL_NAME_SIEGE;
	case ABL_KIND_MAX_N + SKILL_KIND_PHALANX:
		return MSG_ABL_NAME_PHALANX;
	case ABL_KIND_MAX_N + SKILL_KIND_DOUBLE_ATTACK:
		return MSG_ABL_NAME_DOUBLE_ATTACK;
	case ABL_KIND_MAX_N + SKILL_KIND_COMBO:
		return MSG_ABL_NAME_COMBO;
	case ABL_KIND_MAX_N + SKILL_KIND_RAPID_SHOOT:
		return MSG_ABL_NAME_RAPID_SHOOT;
	case ABL_KIND_MAX_N + SKILL_KIND_COUNTER:
		return MSG_ABL_NAME_COUNTER;
	case ABL_KIND_MAX_N + SKILL_KIND_TWO_SWORD_FENCING:
		return MSG_ABL_NAME_TWO_SWORD_FENCING;
	case ABL_KIND_MAX_N + SKILL_KIND_DAM_KNOC:
		return MSG_ABL_NAME_DAM_KNOC;
	case ABL_KIND_MAX_N + SKILL_KIND_DAM_SLAS:
		return MSG_ABL_NAME_DAM_SLAS;
	case ABL_KIND_MAX_N + SKILL_KIND_DAM_STIN:
		return MSG_ABL_NAME_DAM_STIN;
	case ABL_KIND_MAX_N + SKILL_KIND_DAM_HEAT:
		return MSG_ABL_NAME_DAM_HEAT;
	case ABL_KIND_MAX_N + SKILL_KIND_DAM_COLD:
		return MSG_ABL_NAME_DAM_COLD;
	case ABL_KIND_MAX_N + SKILL_KIND_DAM_MIND:
		return MSG_ABL_NAME_DAM_MIND;
	case ABL_KIND_MAX_N + SKILL_KIND_DAM_ACID:
		return MSG_ABL_NAME_DAM_ACID;
	case ABL_KIND_MAX_N + SKILL_KIND_DAM_ELEC:
		return MSG_ABL_NAME_DAM_ELEC;
	case ABL_KIND_MAX_N + SKILL_KIND_DAM_POIS:
		return MSG_ABL_NAME_DAM_POIS;
	case ABL_KIND_MAX_N + SKILL_KIND_RESI_KNOC:
		return MSG_ABL_NAME_RESI_KNOC;
	case ABL_KIND_MAX_N + SKILL_KIND_RESI_SLAS:
		return MSG_ABL_NAME_RESI_SLAS;
	case ABL_KIND_MAX_N + SKILL_KIND_RESI_STIN:
		return MSG_ABL_NAME_RESI_STIN;
	case ABL_KIND_MAX_N + SKILL_KIND_RESI_HEAT:
		return MSG_ABL_NAME_RESI_HEAT;
	case ABL_KIND_MAX_N + SKILL_KIND_RESI_COLD:
		return MSG_ABL_NAME_RESI_COLD;
	case ABL_KIND_MAX_N + SKILL_KIND_RESI_MIND:
		return MSG_ABL_NAME_RESI_MIND;
	case ABL_KIND_MAX_N + SKILL_KIND_RESI_ACID:
		return MSG_ABL_NAME_RESI_ACID;
	case ABL_KIND_MAX_N + SKILL_KIND_RESI_ELEC:
		return MSG_ABL_NAME_RESI_ELEC;
	case ABL_KIND_MAX_N + SKILL_KIND_RESI_POIS:
		return MSG_ABL_NAME_RESI_POIS;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_DEAD:
		return MSG_ABL_NAME_STAT_DEAD;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_STONE:
		return MSG_ABL_NAME_STAT_STONE;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_PARALYZE:
		return MSG_ABL_NAME_STAT_PARALYZE;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_POISON:
		return MSG_ABL_NAME_STAT_POISON;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_CONFUSION:
		return MSG_ABL_NAME_STAT_CONFUSION;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_BLIND:
		return MSG_ABL_NAME_STAT_BLIND;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_SLEEP:
		return MSG_ABL_NAME_STAT_SLEEP;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_SILENCE:
		return MSG_ABL_NAME_STAT_SILENCE;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_CAUGHT:
		return MSG_ABL_NAME_STAT_CAUGHT;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_FEAR:
		return MSG_ABL_NAME_STAT_FEAR;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_HALLUCINATION:
		return MSG_ABL_NAME_STAT_HALLUCINATION;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_CHARM:
		return MSG_ABL_NAME_STAT_CHARM;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_FLY:
		return MSG_ABL_NAME_STAT_FLY;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_HUNGRY:
		return MSG_ABL_NAME_STAT_HUNGRY;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_STARVATION:
		return MSG_ABL_NAME_STAT_STARVATION;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_FAINT:
		return MSG_ABL_NAME_STAT_FAINT;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_DRUNK:
		return MSG_ABL_NAME_STAT_DRUNK;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_VANISH:
		return MSG_ABL_NAME_STAT_VANISH;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_IRON_BODY:
		return MSG_ABL_NAME_STAT_IRON_BODY;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_PASSWALL:
		return MSG_ABL_NAME_STAT_PASSWALL;
	case ABL_KIND_MAX_N + SKILL_KIND_STAT_SENSE_INVISIBLE:
		return MSG_ABL_NAME_STAT_SENSE_INVISIBLE;
	case ABL_KIND_MAX_N + SKILL_KIND_RUN_AWAY:
		return MSG_ABL_NAME_RUN_AWAY;
	case ABL_KIND_MAX_N + SKILL_KIND_MAX_N:
		break;
	}

	return MSG_NULL;
}

/***************************************************************
* メインの能力値からサブの能力値を求める
* abl_kind_t abl_main : メインの能力値
* return : サブの能力値
***************************************************************/

abl_kind_t	get_sub_abl( abl_kind_t abl_main )
{
	switch( abl_main ){
	case ABL_KIND_HP:
		return ABL_KIND_HP;
	case ABL_KIND_MP:
		return ABL_KIND_MP;
	case ABL_KIND_DEX:
		return ABL_KIND_DEX;
	case ABL_KIND_STR:
		return ABL_KIND_STR;
	case ABL_KIND_AGI:
		return ABL_KIND_AGI;
	case ABL_KIND_INT:
		return ABL_KIND_INT;
	case ABL_KIND_WIS:
		return ABL_KIND_WIS;
	case ABL_KIND_CHA:
		return ABL_KIND_CHA;
	case ABL_KIND_FIG:
		return ABL_KIND_FIG;
	case ABL_KIND_MON:
		return ABL_KIND_MON;
	case ABL_KIND_HUN:
		return ABL_KIND_HUN;
	case ABL_KIND_THI:
		return ABL_KIND_THI;
	case ABL_KIND_MAG:
		return ABL_KIND_INT;
	case ABL_KIND_SOR:
		return ABL_KIND_INT;
	case ABL_KIND_ENC:
		return ABL_KIND_INT;
	case ABL_KIND_SUM:
		return ABL_KIND_INT;
	case ABL_KIND_PRI:
		return ABL_KIND_WIS;
	case ABL_KIND_SHA:
		return ABL_KIND_CHA;
	case ABL_KIND_BAR:
		return ABL_KIND_CHA;
	case ABL_KIND_NIN:
		return ABL_KIND_NIN;
	case ABL_KIND_MAX_N:
		break;
	}

	return ABL_KIND_HP;
}

/***************************************************************
* レベルから経験値を計算
* long lev : レベル
* abl_kind_t abl : 能力値の種類
* return : 経験値
***************************************************************/

long	calc_lev_to_exp( long lev, abl_kind_t abl )
{
	double	exp;
	long	i;

	if( lev < 0 )
		return 0;
	if( abl < 0 )
		return 0;
	if( abl >= ABL_SKILL_MAX_N )
		return 0;

	if( abl >= ABL_KIND_MAX_N )
		abl = ABL_KIND_MAX_N;

	exp = 0;
	for( i = 0; i < lev; i++ ){
		long	tmp_lev;
		double	n;

		tmp_lev = i + 1;
		if( tmp_lev > FLAT_LEV )
			tmp_lev = FLAT_LEV;

		n = tmp_lev * tmp_lev;

		n = n * lev_to_exp_tab[abl].mul_lev / _100_PERCENT;
		n = n * lev_to_exp_val.mul_lev / _100_PERCENT;

		n += lev_to_exp_tab[abl].add_lev;
		n += lev_to_exp_val.add_lev;

		exp += n;

		if( exp > NEED_EXP_MAX )
			break;
	}

	if( exp > NEED_EXP_MAX )
		exp = NEED_EXP_MAX;

	return (long)exp;
}

/***************************************************************
* 次のレベルの必要経験値を計算
* long lev : レベル
* abl_kind_t abl : 能力値の種類
* return : 経験値
***************************************************************/

long	calc_need_exp( long lev, abl_kind_t abl )
{
	return calc_lev_to_exp( lev, abl );
}

/***************************************************************
* キャラクタの経験値を取得
* chr_t *chr : キャラクタ
* abl_kind_t abl : 能力値の種類
* return : 経験値
***************************************************************/

long	get_exp( chr_t *chr, abl_kind_t abl )
{
	if( chr == NULL )
		return 0;
	if( abl < 0 )
		return 0;
	if( abl >= ABL_SKILL_MAX_N )
		return 0;

	return( chr->abl.exp[abl].n );
}

/***************************************************************
* 修正を加えたレベルを計算
* chr_t *chr : キャラクタ
* abl_kind_t abl : 能力値の種類
* return : レベル
***************************************************************/

long	get_lev( chr_t *chr, abl_kind_t abl )
{
	if( chr == NULL )
		return 0;
	if( abl < 0 )
		return 0;
	if( abl >= ABL_SKILL_MAX_N )
		return 0;

	return( chr->abl.lev[abl].n + chr->abl.lev[abl].add );
}

/***************************************************************
* レベル・ドレインされる前のレベルを取得
* chr_t *chr : キャラクタ
* abl_kind_t abl : 能力値の種類
* return : レベル
***************************************************************/

long	get_lev_max( chr_t *chr, abl_kind_t abl )
{
	if( chr == NULL )
		return 0;
	if( abl < 0 )
		return 0;
	if( abl >= ABL_SKILL_MAX_N )
		return 0;

	return chr->abl.lev[abl].max;
}

/***************************************************************
* 修正を加えた抵抗値を計算
* chr_t *chr : キャラクタ
* resi_kind_t resi : 抵抗値の種類
* return : 抵抗値
***************************************************************/

rate_t	get_resi( chr_t *chr, resi_kind_t resi )
{
	rate_t	n, max_n;

	if( chr == NULL )
		return _100_PERCENT;
	if( resi < 0 )
		return _100_PERCENT;
	if( resi >= RESI_KIND_MAX_N )
		return _100_PERCENT;

	n = chr->resi[resi].n;
	max_n = get_resi_max( chr, resi );
	if( n > max_n )
		n = max_n;

	return n;
}

/***************************************************************
* 修正を加えた抵抗値の最大値を計算
* chr_t *chr : キャラクタ
* resi_kind_t resi : 抵抗値の種類
* return : 抵抗値の最大値
***************************************************************/

rate_t	get_resi_max( chr_t *chr, resi_kind_t resi )
{
	rate_t	n, a, s;

	if( chr == NULL )
		return _100_PERCENT;
	if( resi < 0 )
		return _100_PERCENT;
	if( resi >= RESI_KIND_MAX_N )
		return _100_PERCENT;

	n = modified_rate( chr->resi[resi].max, chr->resi[resi].add_n );
	a = get_resi_armor( chr, resi );
	s = calc_skill_rate( chr, cv_resi_to_skill_resi( resi ) );

	if( n == RESI_PERFECT_N )
		return RESI_PERFECT_N;
	if( a == RESI_PERFECT_N )
		return RESI_PERFECT_N;
	if( s == RESI_PERFECT_N )
		return RESI_PERFECT_N;

	n = n * a / _100_PERCENT;
	n = n * s / _100_PERCENT;

	return n;
}

/***************************************************************
* 耐性の種類名を返す
* resi_kind_t resi : 抵抗値の種類
* return : 耐性の種類名
***************************************************************/

const char	*get_resi_name( resi_kind_t kind )
{
	switch( kind ){
	case RESI_KIND_KNOC:
		return MSG_MBR_DATA_RESI_KNOC_TTL;
	case RESI_KIND_SLAS:
		return MSG_MBR_DATA_RESI_SLAS_TTL;
	case RESI_KIND_STIN:
		return MSG_MBR_DATA_RESI_STIN_TTL;
	case RESI_KIND_HEAT:
		return MSG_MBR_DATA_RESI_HEAT_TTL;
	case RESI_KIND_COLD:
		return MSG_MBR_DATA_RESI_COLD_TTL;
	case RESI_KIND_MIND:
		return MSG_MBR_DATA_RESI_MIND_TTL;
	case RESI_KIND_ACID:
		return MSG_MBR_DATA_RESI_ACID_TTL;
	case RESI_KIND_ELEC:
		return MSG_MBR_DATA_RESI_ELEC_TTL;
	case RESI_KIND_POIS:
		return MSG_MBR_DATA_RESI_POIS_TTL;
	case RESI_KIND_MAX_N:
		break;
	}

	return "----";
}

/***************************************************************
* レベルが修正されているか調べる
* chr_t *chr : キャラクタ
* abl_kind_t abl : 能力値の種類
* return : 修正されているか
***************************************************************/

bool_t	chk_modified_lev( chr_t *chr, abl_kind_t abl )
{
	if( chr == NULL )
		return TRUE;

	if( chr->abl.lev[abl].add != 0 )
		return TRUE;
	if( chr->abl.lev[abl].n != chr->abl.lev[abl].max )
		return TRUE;

	return FALSE;
}

/***************************************************************
* アビリティから値を計算
* long lev : レベル
* abl_kind_t abl : 能力値の種類
* return : 値
***************************************************************/

long	calc_abl_to_val( chr_t *chr, abl_kind_t abl )
{
	return calc_lev_to_val( get_lev( chr, abl ), abl );
}

/***************************************************************
* レベルから値を計算
* long lev : レベル
* abl_kind_t abl : 能力値の種類
* return : 値
***************************************************************/

long	calc_lev_to_val( long lev, abl_kind_t abl )
{
	rate_t	mul;
	long	add;
	long	val;

	if( abl < 0 )
		return 1;
	if( abl >= ABL_SKILL_MAX_N )
		return 1;

	if( abl >= ABL_KIND_MAX_N )
		abl = ABL_KIND_MAX_N;

	mul = lev_to_val_tab[abl].mul_lev;
	add = lev_to_val_tab[abl].add_lev;

	val = lev * mul / _100_PERCENT;
	val += add;

	if( val < 1 )
		val = 1;

	return val;
}

/***************************************************************
* 最大 HP を計算
* chr_t *chr : キャラクタ
* return : 最大 HP
***************************************************************/

long	calc_max_hp( chr_t *chr )
{
	if( chr == NULL )
		return 1;

	return calc_abl_to_val( chr, ABL_KIND_HP );
}

/***************************************************************
* 最大 MP を計算
* chr_t *chr : キャラクタ
* return : 最大 MP
***************************************************************/

long	calc_max_mp( chr_t *chr )
{
	if( chr == NULL )
		return 1;

	return calc_abl_to_val( chr, ABL_KIND_MP );
}

/***************************************************************
* ダメージを抵抗値で変換
* rate_t resi : 抵抗値
* long n : ダメージ
* return : 変換後のダメージ
***************************************************************/

long	calc_resi( rate_t resi, long n )
{
	if( resi < 1)
		resi = 1;

	if( resi == RESI_PERFECT_N )
		return 0;

	return( (n * _100_PERCENT) / resi );
}

/***************************************************************
* 綜合レベルを計算
* chr_t *chr : キャラクタ
* return : 綜合レベル
***************************************************************/

long	get_generalist_lev( chr_t *chr )
{
	long	lev;
	long	n, max_n;

	if( chr == NULL )
		return 1;

	lev = 0;
	max_n = 0;
	for( n = 0; n < ABL_KIND_MAX_N; n++ ){
		if( n == ABL_KIND_HP )
			continue;
		if( n == ABL_KIND_MP )
			continue;

		max_n++;
		lev += get_lev( chr, (abl_kind_t)n );
	}
	if( max_n > 0 )
		lev /= max_n;
	else
		lev = 0;

	if( lev < 1 )
		lev = 1;

	return lev;
}

/***************************************************************
* 専門レベルを計算
* chr_t *chr : キャラクタ
* return : 綜合レベル
***************************************************************/

long	get_specialist_lev( chr_t *chr )
{
	return( get_lev( chr, get_specialist_abl( chr ) ) );
}

/***************************************************************
* 専門の能力値を求める
* chr_t *chr : キャラクタ
* return : 能力値の種類
***************************************************************/

abl_kind_t	get_specialist_abl( chr_t *chr )
{
	long	lev, max_lev;
	long	exp, max_exp;
	abl_kind_t	ret_n;
	long	i;

	if( chr == NULL )
		return ABL_KIND_FIG;

	ret_n = ABL_KIND_FIG;
	max_lev = 1;
	max_exp = 1;
	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		abl_kind_t	n;
		bool_t	flg_over;

		n = (abl_kind_t)i;

		if( n == ABL_KIND_HP )
			continue;
		if( n == ABL_KIND_MP )
			continue;

		flg_over = FALSE;
		lev = get_lev( chr, n );
		exp = get_exp( chr, n );
		if( lev == max_lev ){
			if( exp > max_exp ){
				flg_over = TRUE;
			}
		} else if( lev > max_lev ){
			flg_over = TRUE;
		}
		if( flg_over ){
			max_lev = lev;
			max_exp = exp;
			ret_n = n;
		}
	}

	return ret_n;
}

/***************************************************************
* キャラクタの向きを返す
* chr_t *chr : キャラクタ
* return : キャラクタの向き
***************************************************************/

chr_dir_idx_t	get_chr_dir_idx( chr_t *chr )
{
	chr_dir_idx_t	dir;

	if( chr == NULL )
		return CHR_DIR_IDX_NULL;

	if( !clip_pos( chr->x, chr->y ) ){
		dir = CHR_DIR_IDX_NULL;
	} else if( !clip_pos( chr->pre_draw_x, chr->pre_draw_y ) ){
		dir = CHR_DIR_IDX_NULL;
	} else {
		long dx = chr->x - chr->pre_draw_x;
		long dy = chr->y - chr->pre_draw_y;

		if( (dx == 0) && (dy == 0) ){
			dir = chr->chr_dir_idx;
		} else if( labs( dx ) > labs( dy ) ){
			if( dx < 0 ){
				dir = CHR_DIR_IDX_W;
			} else {
				dir = CHR_DIR_IDX_E;
			}
		} else if( labs( dx ) < labs( dy ) ){
			if( dy < 0 ){
				dir = CHR_DIR_IDX_N;
			} else {
				dir = CHR_DIR_IDX_S;
			}
		} else {
			dir = chr->chr_dir_idx;
		}
	}

	chr->chr_dir_idx = dir;

	return dir;
}

/***************************************************************
* 全てのキャラクタをマップ奥から順にソート
***************************************************************/

void	sort_all_chr( bool_t flg_gui )
{
	mnstr_t	*head, *p, *pp;
	pet_t	**party_pet = get_party_pet();
	party_t *pty = get_party();
	long	i;

	g_sort_chr_head.sort_chr_next = NULL;

	if( !g_flg_gui )
		return;
	if( g_flg_text_mode )
		return;

	/* モンスター */

	head = get_mnstr_used();
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		sort_chr( &g_sort_chr_head, pp, flg_gui );
	}

	/* ペット */

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == NULL )
			continue;

		sort_chr( &g_sort_chr_head, party_pet[i], flg_gui );
	}

	/* メンバー */

	for( i = 0; i < MBR_MAX_N; i++ ){
		sort_chr( &g_sort_chr_head, pty->mbr[i], flg_gui );
	}
}

/***************************************************************
* キャラクタをマップ奥から順にソート
* chr_t *head : キャラクタのリストの先頭
* chr_t *chr : キャラクタ
***************************************************************/

void	sort_chr( chr_t *head, chr_t *chr, bool_t flg_gui )
{
	chr_t *prev, *next;
	long	i;

	if( !g_flg_gui )
		return;
	if( g_flg_text_mode )
		return;

	if( head == NULL )
		return;
	if( chr == NULL )
		return;

	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( !chk_flg( chr->flg_map, FLG_MAP_CHR_FIND ) )
		return;

	prev = head;
	next = prev->sort_chr_next;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( next == NULL )
			break;
		if( chr->y < next->y )
			break;

		prev = next;
		next = next->sort_chr_next;
	}

	prev->sort_chr_next = chr;
	chr->sort_chr_next = next;
}

/***************************************************************
* ソートされたキャラクタのリストの先頭を返す
* return : キャラクタのリストの先頭
***************************************************************/

chr_t	*get_sort_chr_head( void )
{
	return &g_sort_chr_head;
}

/***************************************************************
* HP を増減
* chr_t *chr : キャラクタ
* long n : 増減する値
* bool_t flg_vfx : 視覚効果を描画するか
* bool_t flg_force : 強制的か
* return : 増減した HP
***************************************************************/

long	add_hp( chr_t *chr, long n, bool_t flg_vfx, bool_t flg_force )
{
	long	pre_hp, add;

	if( chr == NULL )
		return 0;
	if( !flg_force ){
		if( chk_flg_or( chr->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			return 0;
		}
	}

	pre_hp = chr->abl.hp.n;

	chr->abl.hp.n += n;
	if( chr->abl.hp.n > chr->abl.hp.max )
		chr->abl.hp.n = chr->abl.hp.max;
	if( chr->abl.hp.n < 0 )
		chr->abl.hp.n = 0;

	add = chr->abl.hp.n - pre_hp;
	if( add != 0 ){
		if( flg_vfx )
			vfx_num( chr, add );
		draw_mbr_stat( chr );
	}

	if( chr->abl.hp.n <= 0 ){
		if( chr->mnstr_kind == MNSTR_KIND_PHOENIX ){
			chr->abl.hp.n = chr->abl.hp.max;

			curs_attrset_chr( chr, +1, TRUE );
			print_msg( FLG_NULL, MSG_FX_RESURRECTION,
					chr->name );
			curs_attrset_dflt();
		} else {
			die_chr( chr, TRUE, TRUE, TRUE );
			return 0;
		}
	}

	return( chr->abl.hp.n );
}

/***************************************************************
* MP を増減
* chr_t *chr : キャラクタ
* long n : 増減する値
* bool_t flg_vfx : 視覚効果を描画するか
* return : 増減した MP
***************************************************************/

long	add_mp( chr_t *chr, long n, bool_t flg_vfx )
{
	long	pre_mp, add;

	if( chr == NULL )
		return 0;

	pre_mp = chr->abl.mp.n;

	chr->abl.mp.n += n;
	if( chr->abl.mp.n > chr->abl.mp.max )
		chr->abl.mp.n = chr->abl.mp.max;
	if( chr->abl.mp.n < 0 )
		chr->abl.mp.n = 0;

	add = chr->abl.mp.n - pre_mp;
	if( add != 0 ){
		if( flg_vfx )
			vfx_num( chr, add );
		draw_mbr_stat( chr );
	}

	return( chr->abl.mp.n );
}

/***************************************************************
* 抵抗値を増減
* chr_t *chr : キャラクタ
* resi_kind_t kind : 
* long n : 増減する値
* bool_t flg_vfx : 視覚効果を描画するか
* return : 増減した抵抗値
***************************************************************/

rate_t	add_resi( chr_t *chr, resi_kind_t kind, rate_t n, bool_t flg_vfx )
{
	long	pre_resi, add;
	rate_t	resi_max;

	if( chr == NULL )
		return 0;
	if( kind < 0 )
		return 0;
	if( kind >= RESI_KIND_MAX_N )
		return 0;

	pre_resi = chr->resi[kind].n;

	if( chr->resi[kind].n == RESI_PERFECT_N )
		return RESI_PERFECT_N;

	chr->resi[kind].n += n;

	resi_max = get_resi_max( chr, kind );

	if( chr->resi[kind].n < 0 )
		chr->resi[kind].n = 0;
	if( chr->resi[kind].n > resi_max )
		chr->resi[kind].n = resi_max;
	if( chr->resi[kind].n > RESI_MAX_N )
		chr->resi[kind].n = RESI_MAX_N;

	add = chr->resi[kind].n - pre_resi;
	if( add != 0 ){
		if( flg_vfx )
			vfx_num( chr, add );
		draw_mbr_stat( chr );
	}

	return( chr->resi[kind].n );
}

/***************************************************************
* キャラクタの所持金を取得
* chr_t *chr : キャラクタ
* return : 所持金
***************************************************************/

gold_t	get_chr_gold( chr_t *chr )
{
	if( chr == NULL )
		return 0;

	return chr->gold;
}

/***************************************************************
* キャラクタの所持金を増減
* chr_t *chr : キャラクタ
* gold_t gold : 増減値
* return : 増減後の所持金
***************************************************************/

gold_t	add_chr_gold( chr_t *chr, gold_t gold )
{
	if( chr == NULL )
		return 0;

	if( gold > +GOLD_MAX )
		gold = +GOLD_MAX;
	if( gold < -GOLD_MAX )
		gold = -GOLD_MAX;

	chr->gold += gold;

	if( chr->gold > GOLD_MAX )
		chr->gold = GOLD_MAX;
	if( chr->gold < 0 ){
		if( gold > 0 ){
			/* オーバー・フロー */
			chr->gold = GOLD_MAX;
		} else {
			chr->gold = 0;
		}
	}

	/* 統計を取る */

	if( is_mbr( chr ) && (gold < 0) )
		update_playing_report_paying_gold( chr->ls_mbr_n, gold );

	return chr->gold;
}

/***************************************************************
* キャラクタの寄付を使う
* chr_t *chr : キャラクタ
* return : 寄付の効果率
***************************************************************/

rate_t	use_contribution_rate( chr_t *chr )
{
	if( use_contribution( chr, USE_CONTRIBUTION_RATE ) )
		return ROLL_CONTRIBUTION_RATE;

	return _100_PERCENT;
}

/***************************************************************
* キャラクタの寄付を使う
* chr_t *chr : キャラクタ
* rate_t rate : レベル率
* return : 寄付が使えたか?
***************************************************************/

bool_t	use_contribution( chr_t *chr, rate_t rate )
{
	gold_t	gold;

	if( chr == NULL )
		return FALSE;

	gold = (gold_t)(get_specialist_lev( chr ) * rate / _100_PERCENT);
	if( gold < 1 )
		gold = 1;

	if( !chk_pay_contribution( chr, gold ) )
		return FALSE;
	pay_contribution( chr, gold );

	if( !chk_pay_contribution( chr, gold ) ){
		curs_attrset_chr( chr, -1, FALSE );
		print_msg_mbr( chr, FLG_NULL, MSG_EXHAUSTED_CONTRIBUTION,
				chr->name );
		curs_attrset_dflt();
	}

	return TRUE;
}

/***************************************************************
* キャラクタが寄付を消費できるか調べる
* chr_t *chr : キャラクタ
* gold_t gold : 寄付金額
* return : 消費できるか?
***************************************************************/

bool_t	chk_pay_contribution( chr_t *chr, gold_t gold )
{
	if( chr == NULL )
		return FALSE;

	if( chr->contribution < gold )
		return FALSE;

	return TRUE;
}

/***************************************************************
* キャラクタが寄付を消費する
* chr_t *chr : キャラクタ
* gold_t gold : 寄付金額
* return : 消費できたか?
***************************************************************/

bool_t	pay_contribution( chr_t *chr, gold_t gold )
{
	if( chr == NULL )
		return FALSE;

	if( chr->contribution < gold )
		return FALSE;

	chr->contribution -= gold;

	return TRUE;
}

/***************************************************************
* キャラクタの種類と有利不利で描画モードを設定
* chr_t *chr : キャラクタ
* long n : + なら有利、- なら不利
* bool_t flg_crtcl : 特別、または致命的
***************************************************************/

void	curs_attrset_chr( chr_t *chr, long n, bool_t flg_crtcl )
{
	bool_t	flg_mnstr;

	if( chr == NULL )
		return;

	flg_mnstr = FALSE;
	if( chr->kind == CHR_KIND_MNSTR )
		if( chr->attitude == ATTITUDE_ENEMY )
			flg_mnstr = TRUE;

	if( flg_mnstr ){
		if( n >= +1 ){
			if( flg_crtcl ){
				curs_attrset_n( CURS_ATTR_N_FX_MBR_CRTCL );
			} else {
				curs_attrset_n( CURS_ATTR_N_FX_MNSTR_PLUS );
			}
		} else if( n <= -1 ){
			if( flg_crtcl ){
				curs_attrset_n( CURS_ATTR_N_FX_MNSTR_CRTCL );
			} else {
				curs_attrset_n( CURS_ATTR_N_FX_MNSTR_MINUS );
			}
		}
	} else {
		if( n >= +1 ){
			if( flg_crtcl ){
				curs_attrset_n( CURS_ATTR_N_FX_MNSTR_CRTCL );
			} else {
				curs_attrset_n( CURS_ATTR_N_FX_MBR_PLUS );
			}
		} else if( n <= -1 ){
			if( flg_crtcl ){
				curs_attrset_n( CURS_ATTR_N_FX_MBR_CRTCL );
			} else {
				curs_attrset_n( CURS_ATTR_N_FX_MBR_MINUS );
			}
		}
	}
}

/***************************************************************
* キャラクタのアンカーを取得
* chr_t *chr : キャラクタ
* return : アンカー
***************************************************************/

square_t	*get_square( chr_t *chr )
{
	if( is_mbr( chr ) )
		return get_square_mbr();

	return &mnstr_square;
}

/***************************************************************
* キャラクタのアンカーを設定
* chr_t *chr : キャラクタ
* square_t *sq : アンカー
***************************************************************/

void	set_square( chr_t *chr, square_t *sq )
{
	if( is_mbr( chr ) ){
		set_square_mbr( sq );
	} else if( chr->kind == CHR_KIND_MNSTR ){
		mnstr_square = *sq;
	}
}

/***************************************************************
* キャラクタの目標の名前を取得
* trgt_t *trgt : 目標
* return : 名前
***************************************************************/

char	*get_trgt_name( trgt_t *trgt )
{
	if( trgt == NULL )
		return MSG_MNSTR_UNKNOWN;
	if( trgt->p == NULL )
		return MSG_MNSTR_UNKNOWN;

	switch( trgt->kind ){
	case TRGT_KIND_NULL:
		return MSG_MNSTR_UNKNOWN;
	case TRGT_KIND_MBR:
		return ((mbr_t *)trgt->p)->name;
	case TRGT_KIND_MNSTR:
		return ((mnstr_t *)trgt->p)->name;
	case TRGT_KIND_MNSTR_NULL:
		return MSG_MNSTR_UNKNOWN;
	case TRGT_KIND_ITEM:
		return ((item_t *)trgt->p)->name;
	case TRGT_KIND_DOOR:
		return MSG_MENU_SEL_OBJ_DOOR;
	case TRGT_KIND_TRAP:
		return MSG_MENU_SEL_OBJ_TRAP;
	case TRGT_KIND_QUEUE:
		return MSG_MNSTR_UNKNOWN;
	case TRGT_KIND_SQUARE:
		return MSG_MENU_SEL_OBJ_SQUARE;
	case TRGT_KIND_POS:
		return MSG_MNSTR_UNKNOWN;
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		return MSG_MNSTR_UNKNOWN;
	}

	return MSG_MNSTR_UNKNOWN;
}

/***************************************************************
* キャラクタの種類から目標の種類に変換
* chr_t *chr : キャラクタ
* return : 目標の種類
***************************************************************/

trgt_kind_t	get_trgt_kind_from_chr( chr_t *chr )
{
	if( chr == NULL )
		return TRGT_KIND_NULL;

	switch( chr->kind ){
	case CHR_KIND_NULL:
		return TRGT_KIND_NULL;
	case CHR_KIND_MBR:
		return TRGT_KIND_MBR;
	case CHR_KIND_MNSTR:
		return TRGT_KIND_MNSTR;
	}

	return TRGT_KIND_NULL;
}

/***************************************************************
* 目標の種類からキャラクタの種類に変換
* trgt_t *trgt
* return : キャラクタの種類
***************************************************************/

chr_kind_t	get_chr_kind_from_trgt( trgt_t *trgt )
{
	if( trgt == NULL )
		return CHR_KIND_NULL;

	switch( trgt->kind ){
	case TRGT_KIND_NULL:
		break;
	case TRGT_KIND_MBR:
		return CHR_KIND_MBR;
	case TRGT_KIND_MNSTR:
		return CHR_KIND_MNSTR;
	case TRGT_KIND_MNSTR_NULL:
	case TRGT_KIND_ITEM:
	case TRGT_KIND_DOOR:
	case TRGT_KIND_TRAP:
	case TRGT_KIND_QUEUE:
	case TRGT_KIND_SQUARE:
	case TRGT_KIND_POS:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		break;
	}

	return CHR_KIND_NULL;
}

/***************************************************************
* キャラクタをコピー
* chr_t *dst : コピー先キャラクタ
* chr_t *src : コピー元キャラクタ
***************************************************************/

void	copy_chr( chr_t *dst, chr_t *src )
{
	*dst = *src;
}

/***************************************************************
* キャラクタどうしが同じか比較
* chr_t *p1 : キャラクタ 1
* chr_t *p2 : キャラクタ 2
* return : 同じか
***************************************************************/

bool_t	cmp_chr( chr_t *p1, chr_t *p2 )
{
	long	abl;
	long	resi;

	if( p1->kind != p2->kind )
		return FALSE;
	if( strcmp( p1->name, p2->name ) != 0 )
		return FALSE;
#if	0
	if( p1->mbr_n != p2->mbr_n )
		return FALSE;
	if( p1->ls_mbr_n != p2->ls_mbr_n )
		return FALSE;
#endif
	if( p1->face.mjr != p2->face.mjr )
		return FALSE;
	if( p1->face.mnr != p2->face.mnr )
		return FALSE;
#if	0
	if( p1->face.mjr_org != p2->face.mjr_org )
		return FALSE;
	if( p1->face.mnr_org != p2->face.mnr_org )
		return FALSE;
#endif
	if( p1->race.main != p2->race.main )
		return FALSE;
	if( p1->race.sub != p2->race.sub )
		return FALSE;
	if( strcmp( p1->race.name, p2->race.name ) != 0 )
		return FALSE;
	if( p1->sex.cur != p2->sex.cur )
		return FALSE;
#if	0
	if( p1->sex.org != p2->sex.org )
		return FALSE;
#endif
#if	0
	if( p1->x != p2->x )
		return FALSE;
	if( p1->y != p2->y )
		return FALSE;
	if( p1->pre_x != p2->pre_x )
		return FALSE;
	if( p1->pre_y != p2->pre_y )
		return FALSE;
	if( p1->pre_turn_x != p2->pre_turn_x )
		return FALSE;
	if( p1->pre_turn_y != p2->pre_turn_y )
		return FALSE;
#endif
	if( p1->move.speed.rate != p2->move.speed.rate )
		return FALSE;
	if( p1->move.speed.rate_org != p2->move.speed.rate_org )
		return FALSE;
	if( p1->move.speed.n != p2->move.speed.n )
		return FALSE;
	if( p1->move.force_kind != p2->move.force_kind )
		return FALSE;
#if	0
	if( p1->move.ls[] != p2->move.ls[] )
		return FALSE;
#endif

	if( p1->gold != p2->gold )
		return FALSE;
	if( p1->dun_max_lev_floor != p2->dun_max_lev_floor )
		return FALSE;
	if( p1->dun_max_lev_base != p2->dun_max_lev_base )
		return FALSE;
#if	0
	if( p1->trgt != p2->trgt )
		return FALSE;
	if( p1->act != p2->act )
		return FALSE;
#endif
	if( p1->flg_chr != p2->flg_chr )
		return FALSE;
	if( p1->flg_map != p2->flg_map )
		return FALSE;
	if( p1->attitude != p2->attitude )
		return FALSE;
	if( p1->owner != p2->owner )
		return FALSE;
	if( p1->stat != p2->stat )
		return FALSE;
	for( abl = 0; abl < ABL_SKILL_MAX_N; abl++ ){
		if( p1->abl.exp[abl].n != p2->abl.exp[abl].n )
			return FALSE;
		if( p1->abl.exp[abl].max != p2->abl.exp[abl].max )
			return FALSE;
		if( p1->abl.lev[abl].n != p2->abl.lev[abl].n )
			return FALSE;
		if( p1->abl.lev[abl].max != p2->abl.lev[abl].max )
			return FALSE;
#if	0
		if( p1->abl.lev[abl].add != p2->abl.lev[abl].add )
			return FALSE;
#endif
	}
	if( p1->abl.hp.n != p2->abl.hp.n )
		return FALSE;
	if( p1->abl.hp.max != p2->abl.hp.max )
		return FALSE;
	if( p1->abl.mp.n != p2->abl.mp.n )
		return FALSE;
	if( p1->abl.mp.max != p2->abl.mp.max )
		return FALSE;

	if( p1->class_n != p2->class_n )
		return FALSE;

	for( resi = 0; resi < RESI_KIND_MAX_N; resi++ ){
		if( p1->resi[resi].n != p2->resi[resi].n )
			return FALSE;
		if( p1->resi[resi].max != p2->resi[resi].max )
			return FALSE;
#if	0
		if( p1->resi[resi].add != p2->resi[resi].add )
			return FALSE;
#endif
	}

	if( p1->add_def != p2->add_def )
		return FALSE;
	if( p1->add_crtcl != p2->add_crtcl )
		return FALSE;
	if( p1->add_ac != p2->add_ac )
		return FALSE;

#if	0
	if( p1->fx != p2->fx )
		return FALSE;
#endif

	if( p1->fx_data.wpn_hit != p2->fx_data.wpn_hit )
		return FALSE;
	if( p1->fx_data.wpn_crtcl != p2->fx_data.wpn_crtcl )
		return FALSE;
	if( p1->fx_data.wpn_dam != p2->fx_data.wpn_dam )
		return FALSE;

	if( p1->fx_data.armor_def != p2->fx_data.armor_def )
		return FALSE;
	if( p1->fx_data.armor_crtcl != p2->fx_data.armor_crtcl )
		return FALSE;
	if( p1->fx_data.armor_ac != p2->fx_data.armor_ac )
		return FALSE;

	if( p1->fx_data.infra_vision != p2->fx_data.infra_vision )
		return FALSE;

	if( p1->fx_data.infra_vision != p2->fx_data.infra_vision )
		return FALSE;

	if( p1->fx_data.stomach.rate != p2->fx_data.stomach.rate )
		return FALSE;
	if( p1->fx_data.stomach.full_rate
			!= p2->fx_data.stomach.full_rate )
		return FALSE;
	if( p1->fx_data.stomach.digest_p_day
			!= p2->fx_data.stomach.digest_p_day )
		return FALSE;
	if( p1->fx_data.stomach.hungry_rate
			!= p2->fx_data.stomach.hungry_rate )
		return FALSE;
	if( p1->fx_data.stomach.starvation_rate
			!= p2->fx_data.stomach.starvation_rate )
		return FALSE;

	if( p1->fx_data.drunk_rate != p2->fx_data.drunk_rate )
		return FALSE;

	if( p1->fx_data.nicotine.rate != p2->fx_data.nicotine.rate )
		return FALSE;
	if( p1->fx_data.nicotine.poisoning_rate
			!= p2->fx_data.nicotine.poisoning_rate )
		return FALSE;

	if( p1->fx_data.friend_turn != p2->fx_data.friend_turn )
		return FALSE;

	if( p1->fx_data.bless != p2->fx_data.bless )
		return FALSE;

	if( p1->mnstr_kind != p2->mnstr_kind )
		return FALSE;
	if( p1->mnstr_tab != p2->mnstr_tab )
		return FALSE;

	if( p1->flg_pet != p2->flg_pet )
		return FALSE;

	if( p1->work.caught != p2->work.caught )
		return FALSE;

	if( strcmp( p1->graph_name, p2->graph_name ) != 0 )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 装備の能力値への制限率を計算(警告メッセージ有り)
* chr_t *chr : キャラクタ
* abl_kind_t abl_main : メインの能力値
* abl_kind_t abl_sub : サブの能力値
* return : 制限率(少ないほど制限される)
***************************************************************/

rate_t	calc_rate_equip(
	chr_t *chr, abl_kind_t abl_main, abl_kind_t abl_sub
)
{
	return calc_rate_equip_flg_msg( chr, abl_main, abl_sub, TRUE );
}

/***************************************************************
* 装備の能力値への制限率を計算
* chr_t *chr : キャラクタ
* abl_kind_t abl_main : メインの能力値
* abl_kind_t abl_sub : サブの能力値
* bool_t flg_msg : 警告メッセージのフラグ
* return : 制限率(少ないほど制限される)
***************************************************************/

rate_t	calc_rate_equip_flg_msg(
	chr_t *chr, abl_kind_t abl_main, abl_kind_t abl_sub,
	bool_t flg_msg
)
{
	rate_t	rate_eq_main, rate_eq_sub, rate_eq;

	rate_eq_main = calc_rate_abl_equip( chr, abl_main );
	rate_eq_sub = calc_rate_abl_equip( chr, abl_sub );

	if( flg_msg ){
		curs_attrset_chr( chr, -1, FALSE );
		if( rate_eq_main < _100_PERCENT ){
			print_msg_mbr( chr, FLG_NULL,
					MSG_DONT_EXHIBIT_ABL_EQUIP,
					chr->name,
					get_abl_name( abl_main ) );
		}
		curs_attrset_dflt();

		curs_attrset_chr( chr, -1, FALSE );
		if( rate_eq_sub < _100_PERCENT ){
			print_msg_mbr( chr, FLG_NULL,
					MSG_DONT_EXHIBIT_ABL_EQUIP,
					chr->name,
					get_abl_name( abl_sub ) );
		}
		curs_attrset_dflt();
	}

	rate_eq = (rate_eq_main + rate_eq_sub) / 2;

	return rate_eq;
}

/***************************************************************
* キャラクタから別のキャラクタが見えているか調べる
* chr_t *p1 : キャラクタ 1
* chr_t *p2 : キャラクタ 2
* return : 見えているか
***************************************************************/

bool_t	chk_find_chr( chr_t *p1, chr_t *p2 )
{
	pos_t	pos1, pos2;

	if( p1 == NULL)
		return FALSE;
	if( p2 == NULL)
		return FALSE;

	if( chk_flg_or( p1->stat,
			FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_SLEEP
			| FLG_STAT_FAINT ) ){
		return FALSE;
	}

	do {
		if( p1->kind == CHR_KIND_MNSTR )
			if( chk_flg_work_find_mbr( p1 ) )
				break;
		if( chk_flg( p1->stat, FLG_STAT_SENSE_INVISIBLE ) )
			break;

		if( chk_flg( p2->flg_map, FLG_MAP_CHR_INVISIBLE ) )
			return FALSE;
		if( chk_flg( p2->stat, FLG_STAT_VANISH ) )
			return FALSE;

		break;
	} while( 0 );

	if( calc_light_depth( p2->x, p2->y ) <= 0 )
		return FALSE;

	if( is_mbr( p1 ) && (p2->kind == CHR_KIND_MNSTR) ){
		if( labs( p2->x - p1->x ) > MNSTR_MOVE_MAX_X )
			return FALSE;
		if( labs( p2->y - p1->y ) > MNSTR_MOVE_MAX_Y )
			return FALSE;
	}

	pos1.x = p1->x;
	pos1.y = p1->y;
	pos2.x = p2->x;
	pos2.y = p2->y;
	if( !chk_find( &pos1, &pos2 ) )
		return FALSE;

	if( is_mbr( p1 ) && (p2->kind == CHR_KIND_MNSTR) ){
		p2->flg_map |= FLG_MAP_CHR_FIND;
		p2->flg_map &= ~FLG_MAP_CHR_INVISIBLE;
	}

	return TRUE;
}

/***************************************************************
* 全キャラクタの爆風に当ったフラグをクリア
***************************************************************/

void	clr_all_chr_flg_blast( void )
{
	party_t	*pty = get_party();
	mnstr_t	*mns_head, *mns_p;
	pet_t	**party_pet = get_party_pet();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		pty->mbr[i]->work.flg &= ~FLG_WORK_BLAST_END;

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next; mns_p != NULL; mns_p = mns_p->next ){
		if( mns_p == mns_head )
			break;

		mns_p->work.flg &= ~FLG_WORK_BLAST_END;
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == NULL )
			continue;

		party_pet[i]->work.flg &= ~FLG_WORK_BLAST_END;
	}
}

/***************************************************************
* キャラクタがメンバーか調べる
* chr_t *p : キャラクタ
* return : メンバーか?
***************************************************************/

bool_t	is_mbr( chr_t *p )
{
	if( p == NULL )
		return FALSE;

	if( p->kind != CHR_KIND_MBR )
		return FALSE;

	return TRUE;
}

/***************************************************************
* キャラクタがモンスターか調べる
* chr_t *p : キャラクタ
* return : モンスターか?
***************************************************************/

bool_t	is_mnstr( chr_t *p )
{
	if( p == NULL )
		return FALSE;

	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( p->flg_pet )
		return FALSE;

	return TRUE;
}

/***************************************************************
* キャラクタがモンスターか調べる
* chr_t *p : キャラクタ
* return : モンスターか?
***************************************************************/

bool_t	is_mnstr_or_pet( chr_t *p )
{
	if( p == NULL )
		return FALSE;

	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;

	return TRUE;
}

/***************************************************************
* キャラクタがペットか調べる
* chr_t *p : キャラクタ
* return : ペットか?
***************************************************************/

bool_t	is_pet( chr_t *p )
{
	if( p == NULL )
		return FALSE;

	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( !p->flg_pet )
		return FALSE;

	return TRUE;
}

/***************************************************************
* キャラクタのコピー防止 ID をユニークに生成する
* chr_t *chr : キャラクタ
* chr_t **ls : キャラクタのリスト
* long max : リストの最大数
***************************************************************/

void	set_chr_id( chr_t *chr, chr_t **ls, long max )
{
	bool_t	flg_loop;
	long	i;

	do {
		flg_loop = FALSE;

		chr->id1 = calc_chr_id1( chr->name );
		chr->id2 = calc_chr_id2( chr->name );

		for( i = 0; i < max; i++ ){
			if( ls[i] == NULL )
				continue;
			if( ls[i] == chr )
				continue;
			if( chk_flg( ls[i]->stat, FLG_STAT_NOT_EXIST ) )
				continue;

			if( ls[i]->id1 != chr->id1 )
				continue;
			if( ls[i]->id2 != chr->id2 )
				continue;

			flg_loop = TRUE;
			break;
		}
	} while( flg_loop );
}

/***************************************************************
* キャラクタのコピー防止 ID を生成する
* char *name : 名前
* return : ID1
***************************************************************/

long	calc_chr_id1( char *name )
{
	long	n;

	n = (long)time( NULL );
	n &= 0x7fffffff;

	return n;
}

/***************************************************************
* キャラクタのコピー防止 ID を生成する
* char *name : 名前
* return : ID2
***************************************************************/

long	calc_chr_id2( char *name )
{
	const long	max_bit = 24;
	long	bit;
	long	n;
	long	i;

	n = 0;
	bit = max_bit;
	for( i = 0; i < CHR_NAME_MAX_BYTE; i++ ){
		if( name[i] == '\0' )
			break;

		n ^= (name[i] << bit);

		bit -= 8;
		if( bit < 0 ){
			bit = max_bit;
		}
	}

	n ^= randm( 0x7fffffff );

	n &= 0x7fffffff;

	return n;
}

/***************************************************************
* キャラクタどうしの能力値でサイコロを振る
* chr_t *p1 : キャラクタ 1
* abl_kind_t abl_m1 : キャラクタ 1 のメインの能力値
* abl_kind_t abl_s1 : キャラクタ 1 のサブの能力値
* chr_t *p2 : キャラクタ 2
* abl_kind_t abl_m2 : キャラクタ 2 のメインの能力値
* abl_kind_t abl_s2 : キャラクタ 2 のサブの能力値
* return : キャラクタ 1 の方のサイコロが大きいか
***************************************************************/

bool_t	roll(
	chr_t *p1, abl_kind_t abl_m1, abl_kind_t abl_s1,
	chr_t *p2, abl_kind_t abl_m2, abl_kind_t abl_s2
)
{
	rate_t	rate_eq1, rate_eq2;
	rate_t	rate_cont1, rate_cont2;
	rate_t	rate1, rate2;
	long	dice1, dice2;

	if( p1 == NULL )
		return FALSE;
	if( p2 == NULL )
		return FALSE;

	if( is_mbr( p1 ) )
		rate_eq1 = calc_rate_equip( p1, abl_m1, abl_s1 );
	else
		rate_eq1 = _100_PERCENT;
	if( is_mbr( p2 ) )
		rate_eq2 = calc_rate_equip( p1, abl_m2, abl_s2 );
	else
		rate_eq2 = _100_PERCENT;

	/* 祝福 */

	rate_eq1 += p1->fx_data.bless;
	rate_eq2 += p2->fx_data.bless;

	/* 寄付 */

	rate_cont1 = use_contribution_rate( p1 );
	rate_cont2 = use_contribution_rate( p2 );

	/**/

	rate1 = get_lev( p1, abl_m1 );
	rate1 += get_lev( p1, abl_s1 );
	rate1 /= 2;
	rate2 = get_lev( p2, abl_m2 );
	rate2 += get_lev( p2, abl_s2 );
	rate2 /= 2;

	/* 祝福 */

	rate1 = rate1 * rate_eq1 / _100_PERCENT;
	rate2 = rate2 * rate_eq2 / _100_PERCENT;

	/* 寄付 */

	rate1 = rate1 * rate_cont1 / _100_PERCENT;
	rate2 = rate2 * rate_cont2 / _100_PERCENT;

	/**/

	rate1 = rate1 * ROLL_ADJ_RATE / _100_PERCENT;

	if( rate1 < 1 )
		rate1 = 1;
	if( rate2 < 1 )
		rate2 = 1;

	rate1 += ROLL_BASE;
	rate2 += ROLL_BASE;

	dice1 = roll_dice( rate1, FALSE );
	dice2 = roll_dice( rate2, FALSE );

	print_msg_find( p1, FLG_MSG_DEBUG,
			"roll() rate %ld/%ld dice %ld/%ld",
			rate1, rate2, dice1, dice2 );

	return( dice1 >= dice2 );
}

/***************************************************************
* キャラクタの能力値と難易度でサイコロを振る
* chr_t *chr : キャラクタ
* abl_kind_t abl_main : キャラクタのメインの能力値
* abl_kind_t abl_sub : キャラクタのサブの能力値
* long difficulty : 難易度
* return : キャラクタ成功か
***************************************************************/

bool_t	chr_roll(
	chr_t *chr, abl_kind_t abl_main, abl_kind_t abl_sub,
	long difficulty
)
{
	rate_t	rate_eq, rate_cont, rate_chr, rate_dif;
	long	dice_chr, dice_dif;

	if( chr == NULL )
		return FALSE;

	/* 祝福 */

	rate_eq = calc_rate_equip( chr, abl_main, abl_sub );
	rate_eq += chr->fx_data.bless;

	/* 寄付 */

	rate_cont = use_contribution_rate( chr );

	/**/

	rate_chr = get_lev( chr, abl_main );
	rate_chr += get_lev( chr, abl_sub );
	rate_chr /= 2;

	rate_chr = rate_chr * rate_eq / _100_PERCENT;
	rate_chr = rate_chr * rate_cont / _100_PERCENT;
	rate_dif = difficulty;

	rate_chr = rate_chr * ROLL_ADJ_RATE / _100_PERCENT;

	rate_chr += ROLL_BASE;
	rate_dif += ROLL_BASE;

	if( rate_chr < 1 )
		rate_chr = 1;
	if( rate_dif < 1 )
		rate_dif = 1;

	dice_chr = roll_dice( rate_chr, FALSE );
	dice_dif = roll_dice( rate_dif, FALSE );

	print_msg_find( chr, FLG_MSG_DEBUG,
			"chr_roll() rate %ld/%ld dice %ld/%ld",
			rate_chr, rate_dif, dice_chr, dice_dif );

	return( dice_chr >= dice_dif );
}

/***************************************************************
* キャラクタどうしの能力値と抵抗値でサイコロを振る
* chr_t *o_p : 攻撃側のキャラクタ
* abl_kind_t o_abl : 攻撃側のメインの能力値
* chr_t *d_p : 防御側のキャラクタ
* resi_kind_t d_resi : 防御側の抵抗値の種類
* return : 防御成功か
***************************************************************/

bool_t	resi_roll(
	chr_t *o_p, abl_kind_t o_abl,
	chr_t *d_p, resi_kind_t d_resi
)
{
	rate_t	o_rate_cont, d_rate_cont;
	rate_t	o_rate, d_rate;
	long	o_dice, d_dice;

	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( d_resi == RESI_KIND_MAX_N )
		return FALSE;

	if( o_abl == ABL_KIND_MAX_N ){
		o_rate = get_specialist_lev( o_p );
	} else if( o_abl == ABL_SKILL_MAX_N ){
		o_rate = get_specialist_lev( o_p );
	} else {
		abl_kind_t	o_abl_sub;
		long	o_lev;
		rate_t	o_rate_eq;

		o_abl_sub = get_sub_abl( o_abl );

		o_lev = get_lev( o_p, o_abl );
		o_lev += get_lev( o_p, o_abl_sub );
		o_lev /= 2;

		o_rate_eq = calc_rate_equip( o_p, o_abl, o_abl_sub );
		o_rate = o_lev * o_rate_eq / _100_PERCENT;
	}
	o_rate = calc_resi( get_resi( d_p, d_resi ), o_rate );

	d_rate = get_specialist_lev( d_p );

	/* 祝福 */

	o_rate += o_p->fx_data.bless;
	d_rate += d_p->fx_data.bless;

	/* 寄付 */

	o_rate_cont = use_contribution_rate( o_p );
	d_rate_cont = use_contribution_rate( d_p );

	o_rate += o_rate_cont - _100_PERCENT;
	d_rate += d_rate_cont - _100_PERCENT;

	/**/

	o_rate = o_rate * ROLL_ADJ_RATE / _100_PERCENT;

	o_rate += ROLL_BASE;
	d_rate += ROLL_BASE;

	if( o_rate < 1 )
		o_rate = 1;
	if( d_rate < 1 )
		d_rate = 1;

	o_dice = roll_dice( o_rate, FALSE );
	d_dice = roll_dice( d_rate, FALSE );

	print_msg_find( o_p, FLG_MSG_DEBUG,
			"resi_roll() rate %ld/%ld dice %ld/%ld",
			o_rate, d_rate, o_dice, d_dice );

	return( o_dice < d_dice );
}

/***************************************************************
* サイコロを振る
* long n : 最大値の半分
* bool_t flg_add : 最低でも最大値の半分にするか
* return : サイコロの値
***************************************************************/

long	roll_dice( long n, bool_t flg_add )
{
	if( flg_add )
		n += randm( n + 1 );
	else
		n = randm( n + 1 ) + randm( n + 1 );

	if( n < 1 )
		n = 1;

	return n;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_chr_c( void )
{
	check_memory( check_memory_chr_c_lev_to_exp_tab,
			"chr.c: lev_to_exp_tab" );
	check_memory( check_memory_chr_c_lev_to_exp_val,
			"chr.c: lev_to_exp_val" );
	check_memory( check_memory_chr_c_lev_to_val_tab,
			"chr.c: lev_to_val_tab" );
	check_memory( check_memory_chr_c_g_sort_chr_head,
			"chr.c: g_sort_chr_head" );
	check_memory( check_memory_chr_c_mnstr_null,
			"chr.c: mnstr_null" );
	check_memory( check_memory_chr_c_mnstr_square,
			"chr.c: mnstr_square" );
	check_memory( check_memory_chr_c_g_flg_run_exec_all_phase,
			"chr.c: g_flg_run_exec_all_phase" );
	check_memory( check_memory_chr_c_g_flg_mbr_find_mnstr,
			"chr.c: g_flg_mbr_find_mnstr" );
	check_memory( check_memory_chr_c_g_flg_mbr_find_mnstr_pre,
			"chr.c: g_flg_mbr_find_mnstr_pre" );
}
