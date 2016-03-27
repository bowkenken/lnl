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
* $Id: pet.c,v 1.76 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ペット・使い魔・召喚獣
***************************************************************/

#define	PET_C
#include	"inc.h"

/***************************************************************/

/* パーティのつれているペットのリスト */
static pet_t	*party_pet[PET_MAX_N];
check_memory_def( check_memory_pet_c_party_pet )

/* 全てのペットのリスト */
static pet_t	*ls_pet[LS_PET_MAX_N + 1];
check_memory_def( check_memory_pet_c_ls_pet )

/* ペットのメモリー・プール */
static pet_t	ls_pet_buf[LS_PET_MAX_N + 1];
check_memory_def( check_memory_pet_c_ls_pet_buf )

/***************************************************************
* ペットの初期化
***************************************************************/

void	init_pet( void )
{
	long	i;

	for( i = 0; i < LS_PET_MAX_N + 1; i++ )
		ls_pet[i] = &(ls_pet_buf[i]);

	for( i = 0; i < LS_PET_MAX_N + 1; i++ ){
		new_pet( ls_pet[i] );
		ls_pet[i]->stat = FLG_STAT_NOT_EXIST;
	}

	for( i = 0; i < PET_MAX_N; i++ )
		party_pet[i] = NULL;

	if( g_flg_debug )
		init_pet_debug();
	else
		init_pet_dflt();
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_pet( void )
{
}

/***************************************************************
* 通常時のペットの初期化
***************************************************************/

void	init_pet_dflt( void )
{
	party_t	*pty = get_party();
	pet_t	*p;
	long	i;

	i = 0;
	p = make_pet( 10, MNSTR_KIND_PYON_PYON, pty->mbr[i] );
	if( p == NULL )
		return;

	str_nz_cpy( p->name, "Pyon Pyon", PET_NAME_MAX_BYTE );
	join_pet( p );
}

/***************************************************************
* デバッグ時のペットの初期化
***************************************************************/

void	init_pet_debug( void )
{
	party_t	*pty = get_party();
	pet_t	*p;
	long	i;

	i = 0;
	p = make_pet( 10, MNSTR_KIND_PYON_PYON, pty->mbr[i] );
	if( p == NULL )
		return;

	str_nz_cpy( p->name, "Pyon Pyon", PET_NAME_MAX_BYTE );
	join_pet( p );
}

/***************************************************************
* ペットを創る
* long dun_lev : ダンジョン・レベル
* pet_kind_t pet_kind : ペットの種類
* chr_t *owner : ペットの飼主
* return : ペット
***************************************************************/

pet_t	*make_pet( long dun_lev, pet_kind_t pet_kind, chr_t *owner )
{
	long	i;
	pet_t	*p;

	p = NULL;
	for( i = 0; i < LS_PET_MAX_N; i++ ){
		if( ls_pet[i] == NULL )
			continue;

		if( chk_flg( ls_pet[i]->stat, FLG_STAT_NOT_EXIST ) ){
			p = ls_pet[i];
			break;
		}
	}
	if( p == NULL )
		return NULL;

	if( make_pet_alloc( p, dun_lev, pet_kind ) == NULL ){
		p->stat = FLG_STAT_NOT_EXIST;
		return NULL;
	}

	p->owner = owner;

	return p;
}

/***************************************************************
* 割り当てたメモリーにペットを創る
* pet_t *p : ペット
* long dun_lev : ダンジョン・レベル
* pet_kind_t pet_kind : ペットの種類
* return : ペット
***************************************************************/

pet_t	*make_pet_alloc( pet_t *p, long dun_lev, pet_kind_t pet_kind )
{
	mnstr_t	*m;

	if( p == NULL )
		return NULL;

	new_pet( p );

	m = make_mnstr_alloc( p, MAP_DEL_X, MAP_DEL_Y, FALSE,
			dun_lev, pet_kind );
	if( m == NULL )
		return NULL;

	p->flg_pet = TRUE;
	p->flg_chr |= FLG_CHR_CAN_DEL;
	p->flg_map |= FLG_MAP_CHR_NPC;
	p->attitude = ATTITUDE_MATE;
	p->owner = NULL;

	set_chr_id( p, get_ls_pet(), LS_PET_MAX_N );

	return p;
}

/***************************************************************
* ペットの作成時のデフォルト値を設定
* pet_t *p : ペット
***************************************************************/

void	new_pet( pet_t *pet )
{
	if( pet == NULL )
		return;

	new_mnstr( pet );
}

/***************************************************************
* ペットの抵抗値をリセット
* pet_t *p : ペット
* return : エラーが無かったか?
***************************************************************/

bool_t	reset_pet_resi( pet_t *pet )
{
	long	k;

	if( pet == NULL )
		return FALSE;
	if( !is_pet( pet ) )
		return FALSE;

	if( pet->mnstr_tab == NULL )
		return FALSE;

	for( k = 0; k < RESI_KIND_MAX_N; k++ )
		pet->resi[k].max = pet->mnstr_tab->resi[k];

	return TRUE;
}

/***************************************************************
* 全てのペットをマップから消す
***************************************************************/

void	clr_map_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ )
		clr_map_chr( party_pet[i] );
}

/***************************************************************
* 全てのペットをマップに出す
***************************************************************/

void	set_map_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ )
		set_map_chr( party_pet[i] );
}

/***************************************************************
* 全てのペットをマップに出現させる
***************************************************************/

void	appear_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == NULL )
			continue;

		appear_pet( party_pet[i] );
	}
}

/***************************************************************
* ペットをマップに出現させる
* pet_t *p : ペット
***************************************************************/

void	appear_pet( pet_t *p )
{
	long	x, y;

	if( p == NULL )
		return;
	if( chk_flg_or( p->stat,
			FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
		return;
	}

	chk_pet_owner( p );

	if( p->owner == NULL ){
		x = MAP_MAX_X / 2;
		y = MAP_MAX_Y / 2;
	} else {
		x = p->owner->x;
		y = p->owner->y;
	}

	put_chr( p, x, y );
	draw_pet( p );
}

/***************************************************************
* 全てのペットの移動フェーズを実行
***************************************************************/

void	move_phase_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;

		chk_pet_owner( pp );
		set_act_mnstr( pp );
		move_phase_chr( pp );
	}
}

/***************************************************************
* 全てのペットの行動フェーズを実行
***************************************************************/

void	act_phase_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;

		act_phase_chr( pp );
		set_modifier( pp );
	}
}

/***************************************************************
* 全てのペットの送還フェーズを実行
***************************************************************/

void	dismissal_phase_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;

		dismissal_phase_chr( pp );
	}
}

/***************************************************************
* ペットの標準的な行動を設定
* pet_t *p : ペット
***************************************************************/

void	set_act_pet_std( pet_t *p )
{
	if( p == NULL )
		return;

	chk_pet_owner( p );
	pet_mark_std( p );

	if( (p->trgt.kind == TRGT_KIND_MNSTR)
			|| (p->trgt.kind == TRGT_KIND_MNSTR_NULL) ){
		mnstr_move_or_atack_std( p );
	}
}

/***************************************************************
* ペットのターゲットを標準的に設定
* pet_t *p : ペット
***************************************************************/

void	pet_mark_std( pet_t *p )
{
	mnstr_t	*mnstr;
	item_t	*item;

	if( p == NULL )
		return;

	clr_chr_trgt_act( p, TRUE );

	if( p->owner == NULL )
		return;

	switch( p->owner->trgt.kind ){
	case TRGT_KIND_NULL:
		break;
	case TRGT_KIND_MBR:
		break;
	case TRGT_KIND_MNSTR:
	case TRGT_KIND_MNSTR_NULL:
		mnstr = (mnstr_t *)(p->owner->trgt.p);
		if( mnstr == NULL )
			break;
		if( mnstr->attitude != ATTITUDE_ENEMY )
			break;

		mark_mnstr( p, mnstr, DIST_NEAR );
		break;
	case TRGT_KIND_ITEM:
		item = (item_t *)(p->owner->trgt.p);
		if( item == NULL )
			break;
		if( p->owner->trgt.dist == DIST_NEAR )
			break;

		set_chr_act( p, ACT_KIND_ITEM_PICK_UP,
				NULL, NULL, 0, 0 );
		mark_item( p, item, DIST_NEAR );
		break;
	case TRGT_KIND_DOOR:
	case TRGT_KIND_TRAP:
	case TRGT_KIND_QUEUE:
	case TRGT_KIND_SQUARE:
	case TRGT_KIND_POS:
	case TRGT_KIND_AUTO:
		break;
	case TRGT_KIND_MAX_N:
		break;
	}
}

/***************************************************************
* 全てのペットについて罠に掛かったかチェック
***************************************************************/

void	chk_trap_all_pet( void )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;

		chk_trap( pp, pp );
	}
}

/***************************************************************
* リストの次のペット番号を返す
* long n : ペットのリスト番号
* long add : リスト番号の進行方向
* return : ペットのリスト番号
***************************************************************/

long	next_ls_pet_n( long n, long add )
{
	long	next_n;
	long	i;

	if( add == 0 )
		return n;

	next_n = n;
	for( i = 0; i < LS_PET_MAX_N; i++ ){
		next_n = (next_n + add + LS_PET_MAX_N) % LS_PET_MAX_N;

		if( ls_pet[next_n] == NULL )
			continue;
		if( chk_flg_or( ls_pet[next_n]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		return next_n;
	}

	return n;
}

/***************************************************************
* パーティのつれているペットのリストを返す
* return : ペットのリスト
***************************************************************/

pet_t	**get_party_pet( void )
{
	return party_pet;
}

/***************************************************************
* 全てのペットのリストを返す
* return : 全てのペットのリスト
***************************************************************/

pet_t	**get_ls_pet( void )
{
	return ls_pet;
}

/***************************************************************
* 指定の座標のペットを検索
* long x : X 座標
* long y : Y 座標
* return : ペット
***************************************************************/

pet_t	*get_pet( long x, long y )
{
	dun_t	*dun = get_dun();
	pet_t	*p;
	long	i;

	if( !clip_pos( x, y ) )
		return NULL;

	if( dun->map.chr.mjr[y][x] == FACE_MJR_NULL )
		return NULL;

	p = dun->map.chr_p[y][x];
	if( (p != NULL) && is_pet( p ) )
		return p;

	for( i = 0; i < PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = party_pet[i];
		if( pp == NULL )
			continue;
		if( chk_flg_or( pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( x < get_chr_left( pp->x, pp->dx ) )
			continue;
		if( x > get_chr_right( pp->x, pp->dx ) )
			continue;
		if( y < get_chr_top( pp->y, pp->dy ) )
			continue;
		if( y > get_chr_bottom( pp->y, pp->dy ) )
			continue;

		return pp;
	}

	return NULL;
}

/***************************************************************
* ペットのペット番号を返す
* pet_t *pet : ペット
* return : ペット番号
***************************************************************/

long	get_pet_n( pet_t *pet )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet == party_pet[i] )
			return i;
	}

	return -1;
}

/***************************************************************
* ペットのペット・リスト番号を返す
* pet_t *pet : ペット
* return : ペット・リスト番号
***************************************************************/

long	get_pet_ls_n( pet_t *pet )
{
	long	i;

	for( i = 0; i < LS_PET_MAX_N; i++ ){
		if( pet == ls_pet[i] )
			return i;
	}

	return -1;
}

/***************************************************************
* 指定の依頼に関係する NPC (ペット)を検索
* request_t *req : 依頼
* return : NPC (ペット)
***************************************************************/

pet_t	*get_npc_request( request_t *req )
{
	long	i;

	for( i = 0; i < LS_PET_MAX_N; i++ ){
		pet_t	*pp;

		pp = ls_pet[i];
		if( pp == NULL )
			continue;
		if( chk_flg_or( pp->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		if( pp->work.request == req )
			return pp;
	}

	return NULL;
}

/***************************************************************
* ペットの飼い主を初期化
* pet_t *p : ペット
***************************************************************/

void	clr_pet_owner( pet_t *p )
{
	party_t	*pty = get_party();
	long	i;

	if( p == NULL )
		return;

	for( i = 0; i < MBR_MAX_N; i++ ){
		chr_t	*chr;

		chr = pty->mbr[i];
		if( chk_flg_or( chr->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( chr->mbr_n == MBR_N_NOT_JOIN )
			continue;

		p->owner = chr;
		break;
	}
}

/***************************************************************
* ペットの飼い主を再設定
* pet_t *p : ペット
***************************************************************/

void	chk_pet_owner( pet_t *p )
{
	if( p == NULL )
		return;

	if( p->owner == NULL ){
		clr_pet_owner( p );
	} else {
		if( chk_flg_or( p->owner->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			clr_pet_owner( p );
		}
		if( p->owner->mbr_n == MBR_N_NOT_JOIN ){
			clr_pet_owner( p );
		}
	}
}

/***************************************************************
* ペットをパーティに加えられるか調べる
* pet_t *p : ペット
* return : 加えられるか?
***************************************************************/

bool_t	chk_can_join_pet( pet_t *p )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == p )
			return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ペットをパーティから外せられるか調べる
* pet_t *p : ペット
* return : 外せられるか?
***************************************************************/

bool_t	chk_can_not_join_pet( pet_t *p )
{
	long	i;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == p )
			return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ペットをパーティに加える
* pet_t *p : ペット
* return : 加えられたか?
***************************************************************/

bool_t	join_pet( pet_t *p )
{
	long	i;

	if( p == NULL )
		return FALSE;
	if( !chk_can_join_pet( p ) )
		return FALSE;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] != NULL )
			continue;

		party_pet[i] = p;
		appear_pet( p );

		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ペットをパーティから外す
* pet_t *p : ペット
* return : 外せられたか?
***************************************************************/

bool_t	not_join_pet( pet_t *p )
{
	long	i;

	if( p == NULL )
		return FALSE;
	if( !chk_can_not_join_pet( p ) )
		return FALSE;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] != p )
			continue;

		clr_map_chr( p );
		draw_pet( p );

		p->pre_x = p->x;
		p->pre_y = p->y;
		p->x = MAP_DEL_X;
		p->y = MAP_DEL_Y;
		party_pet[i] = NULL;

		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* 死んだ召還獣のメモリーを解放
***************************************************************/

void	garbage_collection_all_pet( void )
{
	long	i;
	pet_t	*p;

	for( i = 0; i < PET_MAX_N; i++ ){
		p = party_pet[i];

		if( p == NULL )
			continue;
		if( !chk_flg( p->flg_chr, FLG_CHR_CAN_DISMISSAL ) )
			continue;
		if( !chk_flg( p->stat, FLG_STAT_DEAD ) )
			continue;

		dismissal( p );
	}
}

/***************************************************************
* ペットが死んだ時の処理
* pet_t *p : ペット
* bool_t flg_msg : メッセージを標示するか?
***************************************************************/

void	die_pet( pet_t *p, bool_t flg_msg )
{
	if( p == NULL )
		return;

	if( flg_msg )
		call_game_sound_play( SOUND_KIND_FIGHT_DIE_MEMBER, 1 );
}

/***************************************************************
* ペットを強制的に送還する
* pet_t *p : ペット
***************************************************************/

void	remove_pet( pet_t *p )
{
	if( p == NULL )
		return;
	if( !is_pet( p ) )
		return;

	p->flg_chr |= FLG_CHR_CAN_DISMISSAL;
	dismissal( p );
}

/***************************************************************
* ペットを送還する
* pet_t *p : ペット
* return : 送還出来たか?
***************************************************************/

bool_t	dismissal( pet_t *p )
{
	long	i;

	if( p == NULL )
		return FALSE;
	if( p->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( !chk_flg( p->flg_chr, FLG_CHR_CAN_DISMISSAL ) )
		return FALSE;

	not_join_pet( p );

	for( i = 0; i < PET_MAX_N; i++ )
		if( party_pet[i] == p )
			party_pet[i] = NULL;

	die_chr( p, FALSE, FALSE, FALSE );
	p->stat |= (FLG_STAT_NOT_EXIST | FLG_STAT_DEAD);

	return TRUE;
}

/***************************************************************
* パーティ中のペットの数を数える
* return : ペットの数
***************************************************************/

long	calc_pet_n( void )
{
	long	n;
	long	i;

	n = 0;
	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == NULL )
			continue;
		if( chk_flg( party_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		n++;
	}

	return n;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_pet_c( void )
{
	check_memory( check_memory_pet_c_party_pet,
			"pet.c: party_pet" );
	check_memory( check_memory_pet_c_ls_pet,
			"pet.c: ls_pet" );
	check_memory( check_memory_pet_c_ls_pet_buf,
			"pet.c: ls_pet_buf" );
}
