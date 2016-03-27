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
* $Id: mnstr-act.c,v 1.36 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* モンスターのアクション
***************************************************************/

#define	MNSTR_ACT_C
#include	"inc.h"

/***************************************************************/

/* モンスターが盗む金額の割合 */
#define	PICK_GOLD_RATE	((rate_t)10)
/* モンスターが盗む金額の最大値 */
#define	PICK_GOLD_MAX_N	((gold_t)500)

/* モンスターが増殖する割合 */
#define	INCREASE_RATE_GIANT_RAT	20

/* 街の住民がドアに入る率（毎ターン） */
#define	TOWNER_ENTER_DOOR_RATE	10
/* 街の住民がドアに入る距離 */
#define	TOWNER_ENTER_DOOR_R	3
/* 街の住民がドアに入るのを諦める率（毎ターン） */
#define	TOWNER_CANCEL_DOOR_RATE	10

/* 街の住民がドアから出る率の１段目（毎ターン） */
#define	TOWNER_EXIT_DOOR_RATE	((rate_t)2)
/* 街の住民がドアから出る率の２段目（昼） */
#define	TOWNER_EXIT_DOOR_RATE_DAY	((rate_t)100)
/* 街の住民がドアから出る率の２段目（夜） */
#define	TOWNER_EXIT_DOOR_RATE_NIGHT	((rate_t)1)

/***************************************************************/

static long	static_set_act_mnstr_giant_rat__increase_turn;
check_memory_def( check_memory_mnstr_act_c_increase_turn )

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_mnstr_act( void )
{
	static_set_act_mnstr_giant_rat__increase_turn = -1;
}

/***************************************************************
* 各モンスターの共通のアクション
***************************************************************/

/***************************************************************
* 共通のアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_std( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* 使い魔の場合のアクション */

	if( p->attitude == ATTITUDE_MATE ){
		set_act_pet_std( p );
		return;
	}
	if( p->attitude != ATTITUDE_ENEMY )
		return;

	mnstr_mark_mbr_std( p );

	/* メンバーを発見している時は攻撃する */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/***************************************************************
* サキュバスとインキュバスの共通のアクション
* mnstr_t *p : モンスター
* sex_t sex : 取り付くキャラクタの性別
***************************************************************/

void	set_act_mnstr_cubus( mnstr_t *p, sex_t sex )
{
	if( p == NULL )
		return;

	/* 使い魔の場合のアクション */

	if( p->attitude == ATTITUDE_MATE ){
		set_act_pet_std( p );
		return;
	}

	mnstr_mark_mbr_cubus( p, sex );

	/* メンバーを発見している時は攻撃する */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/***************************************************************
* 変身するモンスターの共通のアクション
* mnstr_t *p : モンスター
* mnstr_kind_t kind : 変身するモンスター
* rate_t rate : 変身する率
***************************************************************/

void	set_act_mnstr_metamorphose(
	mnstr_t *p, mnstr_kind_t kind, rate_t rate
)
{
	mnstr_tab_t	*meta_tab, *tab;

	if( p == NULL )
		return;
	if( p->mnstr_tab == NULL )
		return;

	meta_tab = get_mnstr_tab( kind, 0 );

	tab = NULL;
	if( rate_randm( rate ) ){
		if( (p->face.mjr == p->mnstr_tab->face_mjr)
				&& (p->face.mnr == p->mnstr_tab->face_mnr) ){
			/* 変身する */
			tab = meta_tab;
		} else {
			/* 元に戻る */
			tab = p->mnstr_tab;
		}
	}

	if( tab != NULL ){
		/* 変身するか元に戻る */

		p->move = tab->move;
		p->modifier_fx.face_mjr = tab->face_mjr;
		p->modifier_fx.face_mnr = tab->face_mnr;
	}

	if( p->face.mjr == p->mnstr_tab->face_mjr ){
		set_act_mnstr_std( p );
	} else {
		/* 変身後のアクション */

		meta_tab->func( p );
	}
}

/***************************************************************
* 街の住民の共通のアクション
* mnstr_t *p : 街の住民（モンスター）
***************************************************************/

void	set_act_mnstr_towner( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* 救助する必要が有れば、そちらのアクション */

	if( set_act_rescue_trgt( p ) )
		return;

	/* 使い魔の場合のアクション */

	if( p->attitude == ATTITUDE_MATE ){
		set_act_pet_std( p );
		return;
	}

	/* 行列に列んでいるなら、そちらのアクション */

	chk_discount_mark( p );
	if( p->trgt.kind == TRGT_KIND_QUEUE )
		return;

	if( p->act.kind == ACT_KIND_DOOR_OPEN ){
		/* ドアに入るアクション */

		if( rate_randm( TOWNER_CANCEL_DOOR_RATE ) )
			clr_chr_trgt_act( p, FALSE );
	} else {
		set_act_mnstr_std( p );
		set_act_towner_enter_door( p );
	}

	/* ドアから出るアクション */

	set_act_towner_exit_door( p );
}

/***************************************************************
* 街の住民がドアに入るか調べるアクション
* mnstr_t *p : 街の住民（モンスター）
***************************************************************/

void	set_act_towner_enter_door( mnstr_t *p )
{
	door_t	*dr;

	if( p == NULL )
		return;
	if( p->act.kind == ACT_KIND_DOOR_OPEN )
		return;
	if( !rate_randm( TOWNER_ENTER_DOOR_RATE ) )
		return;

	dr = get_door_towner( p->x, p->y, TOWNER_ENTER_DOOR_R );
	if( dr == NULL )
		return;
	if( chk_discount_door( dr ) )
		return;

	set_chr_act( p, ACT_KIND_DOOR_OPEN, NULL, NULL, 0, 0 );
	mark_door( p, dr, DIST_NEAR );
}

/***************************************************************
* 街の住民がドアから出るか調べるアクション
* mnstr_t *p : 街の住民（モンスター）
***************************************************************/

void	set_act_towner_exit_door( mnstr_t *p )
{
	door_t	*dr;

	if( p == NULL )
		return;
	if( p->work.enter_door == NULL )
		return;

	if( !rate_randm( TOWNER_EXIT_DOOR_RATE ) )
		return;
	if( chk_night() ){
		if( !rate_randm( TOWNER_EXIT_DOOR_RATE_NIGHT ) ){
			return;
		}
	} else {
		if( !rate_randm( TOWNER_EXIT_DOOR_RATE_DAY ) ){
			return;
		}
	}

	dr = p->work.enter_door;
	if( dr == NULL )
		return;

	if( get_shop_n( dr->mnr ) == SHOP_N_BAR ){
		long	i, max_n;

		if( clip_pos( p->x, p->y ) ){
			clr_map_chr( p );
			draw_chr( p );
		}

		/* 酒を飲んで酔っ払う */

		max_n = roll_dice( 5, FALSE );
		for( i = 0; i < max_n; i++ ){
			drink_liquor( p, LIQUOR_KIND_ALE );
		}
	}

	put_chr( p, dr->x, dr->y );
	p->work.enter_door = NULL;
}

/***************************************************************
* 友好的なモンスターのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_friendly( mnstr_t *p )
{
	if( p == NULL )
		return;

	if( set_act_tame_mnstr( p ) )
		return;

	set_act_mnstr_std( p );
}

/***************************************************************
* 友好的なモンスターの餌付けアクション
* mnstr_t *p : モンスター
* return : アクションを設定したか?
***************************************************************/

bool_t	set_act_tame_mnstr( mnstr_t *p )
{
	if( p == NULL )
		return FALSE;
	if( p->work.request == NULL )
		return FALSE;
	if( p->work.request->kind != REQUEST_KIND_TAME_MNSTR )
		return FALSE;

	if( p->fx_data.stomach.rate < _100_PERCENT ){
		item_t	*food;

		/* 腹が減っている場合 */

		do {
			/* 餌付けする */

			food = get_item_food( p,
					ACT_KIND_ITEM_PICK_UP, FALSE );
			if( food == NULL )
				break;
			if( food->kind != ITEM_KIND_FOOD )
				break;
			if( food->tab.food == NULL )
				break;

			mark_item( p, food, DIST_NEAR );

			if( food->x != p->x )
				break;
			if( food->y != p->y )
				break;

			/* 餌を食べる */

			take_meal_chr( p, food->tab.food->fill_rate );
			del_item( food );
		} while( 0 );
	} else {
		/* 腹がいっぱいになった場合 */

		if( chk_flg_work_find_mbr( p ) )
			return FALSE;

		mnstr_mark_mbr_std( p );
		if( chk_flg_work_find_mbr( p ) ){
			/* 依頼達成 */
			chk_finish_request_join( p->work.request, p );
		}
	}

	return TRUE;
}

/***************************************************************
* 街の住民の救助のアクション
* mnstr_t *p : 街の住民（モンスター）
* return : アクションを設定したか?
***************************************************************/

bool_t	set_act_rescue_trgt( mnstr_t *p )
{
	bool_t	flg_find;

	/* 救助対象かチェック */

	if( p == NULL )
		return FALSE;
	if( p->work.request == NULL )
		return FALSE;
	if( p->work.request->kind != REQUEST_KIND_RESCUE )
		return FALSE;

	/* 救助対象 */

	flg_find = chk_flg_work_find_mbr( p );

	set_chr_act( p, ACT_KIND_MBR_TAIL, NULL, NULL, 0, 0 );
	if( is_pet( p ) )
		mark_mnstr( p, (mnstr_t *)(p->owner->trgt.p), DIST_NEAR );
	else
		mnstr_mark_mbr_std( p );

	if( !flg_find && chk_flg_work_find_mbr( p ) ){
		/* 救助完了 */
		chk_finish_request_join( p->work.request, p );
	}

	return TRUE;
}

/***************************************************************
* 各モンスターの独自のアクション
***************************************************************/

/* 神 */
/* ドラゴン */

/* 幻獣 */

/***************************************************************
* フェニックスのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_phoenix( mnstr_t *p )
{
	party_t	*pty = get_party();
	long	i;

	if( p == NULL )
		return;

	if( p->attitude != ATTITUDE_MATE ){
		/* 使い魔でなければ普通のアクション */

		set_act_mnstr_std( p );
		return;
	}

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		/* メンバーを生き返らせる */

		if( chk_flg_or( pty->mbr[i]->stat, FLG_STAT_DEAD ) )
			fx_resurrection( pty->mbr[i], TRUE );
	}

	/* 残りは普通のアクション */

	set_act_mnstr_std( p );
}

/***************************************************************
* ユニコーンのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_unicorn( mnstr_t *p )
{
	party_t	*pty = get_party();
	long	i;

	if( p == NULL )
		return;

	if( p->attitude != ATTITUDE_MATE ){
		/* 使い魔でなければ普通のアクション */

		set_act_mnstr_std( p );
		return;
	}

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		/* メンバーの状態異常を回復する */

		fx_cure_all_stat( pty->mbr[i] );
	}

	/* 残りは普通のアクション */

	set_act_mnstr_std( p );
}

/* 妖精 */

/***************************************************************
* レプラコーンのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_leprechaun( mnstr_t *p )
{
	chr_t	*mbr;

	if( p == NULL )
		return;

	/* メンバーに隣接しているかチェック */

	mbr = mnstr_mark_mbr_adjoin( p );

	if( mbr != NULL ){
		/* メンバーの金を盗む */

		fx_pick_gold( p, mbr, PICK_GOLD_RATE, PICK_GOLD_MAX_N );
		print_msg( FLG_NULL, MSG_MNSTR_DISAPPEAR, p->name );
		teleport_chr( p );
	}

	/* 残りは普通のアクション */

	set_act_mnstr_std( p );
}

/* 精霊 */

/* 植物 */

/***************************************************************
* ヴィーナス・フライ・トラップのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_venus_fly_trap( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* 隣接しているメンバーを捕まえる */

	if( mnstr_mark_mbr_adjoin( p ) != NULL )
		catch_chr( p, (chr_t *)(p->trgt.p) );

	/* メンバーを発見している時は攻撃する */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/***************************************************************
* スライムのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_slime( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* メンバーに隣接しようとする */

	if( mnstr_mark_mbr_adjoin( p ) == NULL )
		mnstr_mark_mbr_std( p );

	/* 残りは普通のアクション */

	set_act_mnstr_std( p );
}

/***************************************************************
* スポアのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_spore( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* メンバーが隣接している時だけ攻撃する */

	if( mnstr_mark_mbr_adjoin( p ) != NULL )
		mnstr_move_or_atack_std( p );
}

/* 動物 */

/***************************************************************
* ジャイアント・ラットのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_giant_rat( mnstr_t *p )
{
	long	increase_turn = -1;

	increase_turn = static_set_act_mnstr_giant_rat__increase_turn;

	if( p == NULL )
		return;

	/* まずは普通のアクション */

	set_act_mnstr_std( p );

	/* 増殖する */

	if( increase_turn < get_turn() ){
		if( rate_randm( INCREASE_RATE_GIANT_RAT ) ){
			increase_mnstr( p );
			increase_turn = get_turn();
		}
	}

	static_set_act_mnstr_giant_rat__increase_turn = increase_turn;
}

/* 昆虫 */

/***************************************************************
* ジャイアント・スパイダーのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_giant_spider( mnstr_t *p )
{
	mbr_t	*mbr;
	bool_t	flg_rel;

	if( p == NULL )
		return;

	mbr = mnstr_mark_mbr_adjoin( p );
	if( mbr == NULL ){
		/* 隣接していないならメンバー普通に近付く */

		mnstr_mark_mbr_std( p );
	} else {
		/* 隣接しているならメンバーを捕まえる */

		catch_chr( p, mbr );
	}

	/* メンバーを解放するかチェック */

	if( mbr == NULL )
		flg_rel = TRUE;
	else if( rate_randm( 30 ) )
		flg_rel = TRUE;
	else
		flg_rel = FALSE;

	/* メンバーを発見している時だけ */

	if( chk_flg_work_find_mbr( p ) ){
		/* メンバーを解放する */
		if( flg_rel )
			release_chr( p );

		/* 普通に攻撃する */
		mnstr_move_or_atack_std( p );
	}
}

/* 人間 */

/* 半人 */

/***************************************************************
* ワー・ウルフのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_werewolf( mnstr_t *p )
{
	/* ウルフに変身するアクション */

	set_act_mnstr_metamorphose( p, MNSTR_KIND_WOLF, 10 );
}

/**/

/* 巨人 */
/* 巨大生物 */

/***************************************************************
* ジャイガンティック・センティピードのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_gigantic_centipede( mnstr_t *p )
{
	chr_t	*l;

	if( p == NULL )
		return;

	/* 先頭でなければ１つ前を追いかける */

	l = p->work.link_chr;
	if( l != NULL ){
		if( (l->pre_x != l->x) || (l->pre_y != l->y) )
			mark_pos( p, l->pre_x, l->pre_y, DIST_NEAR );
		p->move.force_kind = MOVE_KIND_STD;
		return;
	}

	/* 使い魔の場合のアクション */

	if( p->attitude == ATTITUDE_MATE ){
		set_act_pet_std( p );
		return;
	}
	if( p->attitude != ATTITUDE_ENEMY )
		return;

	mnstr_mark_mbr_std( p );

	/* メンバーを発見している時は攻撃する */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/* 水棲生物 */

/* 魔法生物 */

/***************************************************************
* ガーゴイルのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_gargoyle( mnstr_t *p )
{
	dun_t	*dun = get_dun();

	if( p == NULL )
		return;

	if( chk_flg_work_find_mbr( p ) ){
		/* メンバーを発見している時は普通にマークする */

		mnstr_mark_mbr_std( p );
	} else {
		flg_map_t	flg_map;
		chr_t	*mark;

		/* 一時的に石像を視線が通る様にする */
		flg_map = dun->map.obj.flg[p->y][p->x];
		dun->map.obj.flg[p->y][p->x] |= FLG_MAP_OBJ_LOOK;

		/* メンバーに隣接しているかチェック */
		mark = mnstr_mark_mbr_adjoin( p );

		/* 石像の視線を元に戻す */
		dun->map.obj.flg[p->y][p->x] = flg_map;

		/* メンバーが近寄ったら姿を表す */
		if( mark != NULL ){
			dun->map.obj.mjr[p->y][p->x] = FACE_MJR_FLOOR;
			dun->map.obj.mnr[p->y][p->x] = FACE_MNR_FLOOR;
			dun->map.obj.flg[p->y][p->x]
					= (FLG_MAP_OBJ_PASS
					| FLG_MAP_OBJ_LOOK);
		}
	}

	/* メンバーを発見している時は攻撃する */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/***************************************************************
* ミミックのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_mimic( mnstr_t *p )
{
	if( p == NULL )
		return;

	/* 隣接しているメンバーを捕まえる */

	if( mnstr_mark_mbr_adjoin( p ) != NULL )
		catch_chr( p, (chr_t *)(p->trgt.p) );

	/* メンバーを発見している時は攻撃する */

	if( chk_flg_work_find_mbr( p ) )
		mnstr_move_or_atack_std( p );
}

/* 合成獣 */

/* アンデッド */

/***************************************************************
* ヴァンパイアのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_vampire( mnstr_t *p )
{
	/* ジャイアント・バットに変身するアクション */

	set_act_mnstr_metamorphose( p, MNSTR_KIND_GIANT_BAT, 10 );
}

/* 妖魔 */

/***************************************************************
* インキュバスのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_incubus( mnstr_t *p )
{
	/* 女性に取り付く */

	set_act_mnstr_cubus( p, FEMALE );
}

/***************************************************************
* サキュバスのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_succubus( mnstr_t *p )
{
	/* 男性に取り付く */

	set_act_mnstr_cubus( p, MALE );
}

/* 魔獣 */
/* 悪魔 */

/***************************************************************
* エクセルのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_exel( mnstr_t *p )
{
	if( p == NULL )
		return;

	if( get_last_scene() != LAST_SCENE_N_EXEL_BATTLE ){
		p->stat |= FLG_STAT_IRON_BODY;
		p->abl.hp.n = p->abl.hp.max;
	} else {
		p->stat &= ~FLG_STAT_IRON_BODY;
		set_act_mnstr_std( p );
	}
}

/***************************************************************
* エクセラーのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_exeler( mnstr_t *p )
{
	if( p == NULL )
		return;

	if( get_last_scene() != LAST_SCENE_N_EXELER_BATTLE ){
		p->stat |= FLG_STAT_IRON_BODY;
		p->abl.hp.n = p->abl.hp.max;
	} else {
		p->stat &= ~FLG_STAT_IRON_BODY;
		set_act_mnstr_std( p );
	}
}

/***************************************************************
* ゼクスのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_xex( mnstr_t *p )
{
	if( p == NULL )
		return;

	p->stat |= FLG_STAT_IRON_BODY;
	p->abl.hp.n = p->abl.hp.max;
}

/***************************************************************
* トゥエンティースのアクション
* mnstr_t *p : モンスター
***************************************************************/

void	set_act_mnstr_xx( mnstr_t *p )
{
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_mnstr_act_c( void )
{
	check_memory( check_memory_mnstr_act_c_increase_turn,
			"mnstr-act.c: increase_turn" );
}
