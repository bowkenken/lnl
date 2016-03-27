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
* $Id: trap.c,v 1.82 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* 罠
***************************************************************/

#define	TRAP_C
#include	"inc.h"

/***************************************************************/

/* 1 にすると特定の罠だけをつくる(デバッグ用) */

#if	0
# ifndef	D_TEST_TRAP_KIND
#  define	D_TEST_TRAP_KIND	TRAP_KIND_CHUTE
# endif
#endif

/* 解除の難易度 */

#define	TRAP_DIFFICULTY_LEV_RATE	RATE_LEV_PER_DUN_LEV
#define	TRAP_DIFFICULTY_LEV_ADD	1

/* トラップ部屋 */

/* 出現する最低階 */
#define	TRAP_ROOM_DUN_LEV_MIN_N	30
/* 出現率 */
#define	TRAP_ROOM_RATE	((rate_t)3)
/* 仕掛けられている数 */
#define	TRAP_ROOM_N	32

/* 落し穴のダメージ */

/* 最大 HP の % */
#define	PIT_DAM_RATE	((rate_t)25)
#define	PIT_DAM_ADD	1

/* 同じ近さの半径と判定される距離 */
#define	TRAP_NEAR_R	4

/***************************************************************
* グローバル変数
***************************************************************/

/* プール */
static trap_t	trap_buf[TRAP_MAX_N];
/* フリー・メモリのヘッダ */
static trap_t	trap_free;
/* 迷宮の割り当てメモリのヘッダ */
static trap_t	dun_trap_asgn;

check_memory_def( check_memory_trap_c_trap_buf )

/* データ・テーブルの最大数 */
static long	trap_tab_max_n;

/* データ・テーブル */
static trap_tab_t	trap_tab[] = {
	{
		TRAP_KIND_SLEEP,
		N_MSG_TRAP_SLEEP, NULL,
		100, FACE_MNR_TRAP_SLEEP,
		1, DUN_MAX_LEV_BASE, -1,
		TRUE,
	},
	{
		TRAP_KIND_ARW,
		N_MSG_TRAP_ARW, NULL,
		100, FACE_MNR_TRAP_ARW,
		2, DUN_MAX_LEV_BASE, -1,
		TRUE,
	},
	{
		TRAP_KIND_POISON_DARTS,
		N_MSG_TRAP_POISON_DARTS, NULL,
		100, FACE_MNR_TRAP_POISON_DARTS,
		3, DUN_MAX_LEV_BASE, -1,
		TRUE,
	},
	{
		TRAP_KIND_BOMB,
		N_MSG_TRAP_BOMB, NULL,
		100, FACE_MNR_TRAP_BOMB,
		10, DUN_MAX_LEV_BASE, -1,
		TRUE,
	},
	{
		TRAP_KIND_TELEPORT_PARTY,
		N_MSG_TRAP_TELEPORT_PARTY, NULL,
		100, FACE_MNR_TRAP_TELEPORT_PARTY,
		20, DUN_MAX_LEV_BASE, -1,
		TRUE,
	},
	{
		TRAP_KIND_TELEPORT,
		N_MSG_TRAP_TELEPORT, NULL,
		100, FACE_MNR_TRAP_TELEPORT,
		30, DUN_MAX_LEV_BASE, -1,
		TRUE,
	},
	{
		TRAP_KIND_PIT,
		N_MSG_TRAP_PIT, NULL,
		100, FACE_MNR_TRAP_PIT,
		4, DUN_MAX_LEV_BASE, -1,
		TRUE,
	},
	{
		TRAP_KIND_CHUTE,
		N_MSG_TRAP_CHUTE, NULL,
		80, FACE_MNR_TRAP_CHUTE,
		10, DUN_MAX_LEV_BASE, -1,
		TRUE,
	},
	{
		TRAP_KIND_SANCTUARY,
		N_MSG_TRAP_SANCTUARY, NULL,
		0, FACE_MNR_TRAP_SANCTUARY,
		DUN_MAX_LEV_BASE, DUN_MAX_LEV_BASE, 0,
		FALSE,
	},
	{
		TRAP_KIND_NULL,
		N_MSG_NULL, NULL,
		0, FACE_MNR_NULL,
		DUN_MAX_LEV_BASE, DUN_MAX_LEV_BASE, 0,
		TRUE,
	},
};
check_memory_def( check_memory_trap_c_trap_tab )

/* 罠が魔法を発動する時のダミーのキャラクタ */
chr_t	g_dmy_chr;
check_memory_def( check_memory_trap_c_g_dmy_chr )

/***************************************************************
* 罠の初期化
***************************************************************/

void	init_trap( void )
{
	long	i;

	trap_tab_max_n = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( trap_tab[i].kind == TRAP_KIND_NULL )
			break;
		trap_tab[i].name = MSG( trap_tab[i].name_n );
	}
	trap_tab_max_n = i;

	dun_trap_asgn.prev = &dun_trap_asgn;
	dun_trap_asgn.next = &dun_trap_asgn;

	i = 0;
	trap_free.next = &(trap_buf[i]);
	trap_buf[i].prev = &trap_free;
	trap_buf[i].next = &(trap_buf[i + 1]);
	for( i++; i < TRAP_MAX_N - 1; i++ ){
		trap_buf[i].prev = &(trap_buf[i - 1]);
		trap_buf[i].next = &(trap_buf[i + 1]);
	}
	trap_buf[i].prev = &(trap_buf[i - 1]);
	trap_buf[i].next = &trap_free;
	trap_free.prev = &(trap_buf[i]);
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_trap( void )
{
}

/***************************************************************
* マップ上の罠を全てリセットする
***************************************************************/

void	reset_trap( void )
{
	trap_t	*p, *end;

	end = &dun_trap_asgn;
	for( p = end->next->next; p->prev != end; p = p->next )
		free_trap( p->prev );
}

/***************************************************************
* 罠を創る
* long x : X 座標
* long y : Y 座標
* long dun_lev : 迷宮レベル
* return : 創った罠
***************************************************************/

trap_t	*make_trap( long x, long y, long dun_lev )
{
	dun_t	*dun;
	bool_t	flg_boss;
	trap_t	*trap;
	long	n;
	long	i;

	dun = get_dun();

	flg_boss = chk_boss_dun_lev( dun->lev );

	if( clip_pos( x, y ) ){
		if( dun->map.obj.mjr[y][x] != FACE_MJR_FLOOR )
			return NULL;
		if( dun->map.obj.mnr[y][x] != FACE_MNR_FLOOR )
			return NULL;
	}

	n = 0;
	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( trap_tab_max_n );

#ifdef	D_TEST_TRAP_KIND
		if( g_flg_debug ){
			if( D_TEST_TRAP_KIND != TRAP_KIND_NULL ){
				if( trap_tab[n].kind == D_TEST_TRAP_KIND ){
					break;
				} else {
					continue;
				}
			}
		}
#endif

		if( trap_tab[n].kind == TRAP_KIND_NULL )
			continue;
		if( trap_tab[n].kind == TRAP_KIND_CHUTE )
			if( flg_boss )
				continue;
		if( !rate_randm( trap_tab[n].rate ) )
			continue;
		if( labs( dun_lev ) < trap_tab[n].min_lev )
			continue;
		if( labs( dun_lev ) > trap_tab[n].max_lev )
			continue;
		if( sgn_l( dun_lev ) != trap_tab[n].sgn_lev )
			continue;

		break;
	}
	if( i <= 0 )
		return NULL;

	trap = alloc_trap();
	if( trap == NULL )
		return NULL;

	do {
		if( !make_trap_alloc( dun_lev, trap, n ) )
			break;
		if( clip_pos( x, y ) )
			if( !set_trap( x, y, trap ) )
				break;

		/* 成功 */

		return trap;
	} while( 0 );

	/* 失敗 */

	free_trap( trap );

	return NULL;
}

/***************************************************************
* 種類を指定して罠を創る
* trap_kind_t kind : 罠の種類
* long x : X 座標
* long y : Y 座標
* long dun_lev : 迷宮レベル
* return : 創った罠
***************************************************************/

trap_t	*make_trap_std( trap_kind_t kind, long x, long y, long dun_lev )
{
	long	tab_n;
	trap_t	*trap;

	tab_n = get_trap_tab_n( kind );
	if( tab_n <= -1 )
		return NULL;

	trap = alloc_trap();
	if( trap == NULL )
		return NULL;

	do {
		if( !make_trap_alloc( dun_lev, trap, tab_n ) )
			break;
		if( clip_pos( x, y ) )
			if( !set_trap( x, y, trap ) )
				break;

		/* 成功 */

		return trap;
	} while( 0 );

	/* 失敗 */

	free_trap( trap );

	return NULL;
}

/***************************************************************
* 割り当て済みのメモリで罠を創る
* long dun_lev : 迷宮レベル
* trap_t *trap : 作成先
* long tab_n : データ・テーブルのインデックス
* return : 成功したか?
***************************************************************/

bool_t	make_trap_alloc( long dun_lev, trap_t *trap, long tab_n )
{
	long	difficulty;

	if( trap == NULL )
		return FALSE;

	trap->kind = trap_tab[tab_n].kind;
	trap->x = MAP_DEL_X;
	trap->y = MAP_DEL_Y;
	trap->lev = dun_lev;

	difficulty = labs( dun_lev );
	difficulty *= TRAP_DIFFICULTY_LEV_RATE;
	difficulty /= _100_PERCENT;
	difficulty += TRAP_DIFFICULTY_LEV_ADD;
	trap->difficulty = difficulty;

	trap->flg_chked = FALSE;
	trap->cx = +-0;
	trap->cy = +-0;
	trap->tab = get_trap_tab( trap_tab[tab_n].kind );

	return TRUE;
}

/***************************************************************
* 罠を仕掛ける
* long x : X 座標
* long y : Y 座標
* trap_t *trap : 罠
* return : 成功したか?
***************************************************************/

bool_t	set_trap( long x, long y, trap_t *trap )
{
	dun_t	*dun = get_dun();

	if( trap == NULL )
		return FALSE;

	if( !clip_pos( x, y ) )
		return FALSE;
	if( dun->map.obj.mjr[y][x] != FACE_MJR_FLOOR )
		return FALSE;
	if( dun->map.obj.mnr[y][x] != FACE_MNR_FLOOR )
		return FALSE;

	trap->x = x;
	trap->y = y;

	dun->map.obj.mjr[y][x] = FACE_MJR_TRAP;
	dun->map.obj.mnr[y][x] = FACE_MNR_NULL;
	dun->map.obj.flg[y][x] |= FLG_MAP_OBJ_PASS | FLG_MAP_OBJ_LOOK;
	dun->map.obj.flg[y][x] |= FLG_MAP_OBJ_LOOK_FLOOR;

	set_trap_face_mnr( trap );

	ins_ls_trap( &dun_trap_asgn, trap );

	return TRUE;
}

/***************************************************************
* 罠のマイナーの顔文字を設定
* trap_t *trap : 罠
* return : 成功したか?
***************************************************************/

bool_t	set_trap_face_mnr( trap_t *trap )
{
	dun_t	*dun = get_dun();
	long	x, y;

	if( trap == NULL )
		return FALSE;
	if( trap->tab == NULL )
		return FALSE;

	x = trap->x;
	y = trap->y;

	if( !clip_pos( x, y ) )
		return FALSE;
	if( dun->map.obj.mjr[y][x] != FACE_MJR_TRAP )
		return FALSE;

	if( chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_LOOK_FLOOR ) ){
		dun->map.obj.mnr[y][x] = FACE_MNR_NULL;
	} else if( trap->flg_chked ){
		dun->map.obj.mnr[y][x] = trap->tab->mnr;
	} else {
		dun->map.obj.mnr[y][x] = FACE_MNR_NULL;
	}

	draw_trap( trap );

	return TRUE;
}

/***************************************************************
* トラップ部屋を創る
* long area_x : X エリア座標
* long area_y : Y エリア座標
* long dun_lev : 迷宮レベル
***************************************************************/

void	make_chk_trap_room( long dun_lev )
{
	long	x, y;

	if( labs( dun_lev ) < TRAP_ROOM_DUN_LEV_MIN_N )
		return;
	if( !rate_randm( TRAP_ROOM_RATE ) )
		return;

	x = randm( AREA_MAP_MAX_X );
	y = randm( AREA_MAP_MAX_Y );

	make_trap_room( x, y, dun_lev );
}

/***************************************************************
* トラップ部屋に複数の罠を創る
* long area_x : X エリア座標
* long area_y : Y エリア座標
* long dun_lev : 迷宮レベル
***************************************************************/

void	make_trap_room( long area_x, long area_y, long dun_lev )
{
	dun_t	*dun = get_dun();
	trap_t	*trap;
	long	item_n, item_max_n;
	long	mx, my;
	long	n;
	long	i;

	n = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( n >= TRAP_ROOM_N )
			break;

		mx = area_x * AREA_MAX_X + randm( AREA_MAX_X );
		my = area_y * AREA_MAX_Y + randm( AREA_MAX_Y );

		if( dun->map.obj.mjr[my][mx] != FACE_MJR_FLOOR )
			continue;
		if( dun->map.obj.mnr[my][mx] != FACE_MNR_FLOOR )
			continue;

		trap = make_trap( mx, my, dun_lev );
		if( trap != NULL )
			n++;
	}

	item_n = 0;
	item_max_n = roll_dice( DUN_ITEM_TRAP_ROOM_AVE_N, TRUE );
	for( i = 0; i < LOOP_MAX_10000; i++ ){
		if( item_n >= item_max_n )
			break;

		mx = area_x * AREA_MAX_X + randm( AREA_MAX_X );
		my = area_y * AREA_MAX_Y + randm( AREA_MAX_Y );
		if( make_item( mx, my, dun->lev ) != ITEM_KIND_NULL )
			item_n++;
	}
}

/***************************************************************
* 宝箱の罠を調べる
* item_t *chest : 宝箱
* chr_t *chr : 調べるキャラクタ
* rate_t rate : 罠の発動率
***************************************************************/

void	chk_trap_chest( item_t *chest, chr_t *chr, rate_t rate )
{
	bool_t	flg_free;

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chest == NULL )
		return;
	if( chest->kind != ITEM_KIND_CHEST )
		return;

	if( !rate_randm( rate ) ){
		call_game_sound_play( SOUND_KIND_TRAP_SAFE, 1 );
		return;
	}

	flg_free = TRUE;
	if( chest->dat.chest.trap != NULL )
		if( chest->dat.chest.trap->kind == TRAP_KIND_CHUTE )
			flg_free = FALSE;

	call_game_sound_play( SOUND_KIND_TRAP_CAUGHT, 1 );
	caught_trap( chest->dat.chest.trap, chr );

	if( flg_free )
		free_trap_chest( chest );
}

/***************************************************************
* キャラクタが罠に掛かったか調べる
* chr_t *chr : 調べるキャラクタ
* chr_t *thief : 罠の回避をサポートするキャラクタ
***************************************************************/

void	chk_trap( chr_t *chr, chr_t *thief )
{
	trap_t	*trap;
	dun_t	*dun = get_dun();

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;
	if( chk_flg( chr->stat, FLG_STAT_FLY ) )
		return;
	if( !chk_can_act_chr( chr ) )
		return;

	if( chr->x == chr->pre_turn_x )
		if( chr->y == chr->pre_turn_y )
			return;

	if( thief == NULL )
		thief = chr;

	if( dun->map.obj.mjr[chr->y][chr->x] != FACE_MJR_TRAP )
		return;
	if( dun->map.obj.mnr[chr->y][chr->x] == FACE_MNR_TRAP_SANCTUARY )
		return;

	trap = get_trap( chr->x, chr->y );
	if( trap == NULL )
		return;

	if( is_mbr( chr ) ){
		find_trap( trap );
	} else {
		if( chk_flg( chr->flg_map, FLG_MAP_CHR_FIND ) )
			find_trap( trap );
	}

	if( chr_roll( thief, ABL_KIND_THI, ABL_KIND_AGI,
			trap->difficulty ) ){
		if( is_mbr( chr ) || is_pet( chr ) )
			call_game_sound_play( SOUND_KIND_TRAP_SAFE, 1 );

		curs_attrset_chr( chr, +1, FALSE );
		print_msg_mbr( chr, FLG_NULL, MSG_NOT_TRAPPED, chr->name );
		curs_attrset_dflt();
	} else {
		caught_trap( trap, chr );
	}
}

/***************************************************************
* 罠を発見した
* trap_t *trap : 罠
***************************************************************/

void	find_trap( trap_t *trap )
{
	dun_t	*dun = get_dun();

	if( trap == NULL )
		return;

	if( !clip_pos( trap->x, trap->y ) )
		return;

	dun->map.obj.flg[trap->y][trap->x] &= ~FLG_MAP_OBJ_LOOK_FLOOR;
	dun->map.obj.flg[trap->y][trap->x] |= FLG_MAP_OBJ_FIND;
	draw_trap( trap );
}

/***************************************************************
* 罠を発動する
* trap_t *trap : 罠
* chr_t *chr : 罠を発動させたキャラクタ
***************************************************************/

void	caught_trap( trap_t *trap, chr_t *chr )
{
	long	lev;
	long	i;

	if( trap == NULL )
		return;
	if( trap->tab == NULL )
		return;
	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	if( is_mbr( chr ) || is_pet( chr ) )
		call_game_sound_play( SOUND_KIND_TRAP_CAUGHT, 1 );

	if( is_mbr( chr ) ){
		find_trap( trap );
	} else {
		if( chk_flg( chr->flg_map, FLG_MAP_CHR_FIND ) )
			find_trap( trap );
	}

	if( trap->tab->flg_draw_msg ){
		curs_attrset_chr( chr, -1, FALSE );
		print_msg_mbr( chr, FLG_NULL, MSG_TRAPPED,
				chr->name, trap->tab->name );
		curs_attrset_dflt();
	}

	g_dmy_chr.kind = CHR_KIND_NULL;
	str_nz_cpy( g_dmy_chr.name, trap->tab->name, CHR_NAME_MAX_BYTE );
	g_dmy_chr.x = trap->x;
	g_dmy_chr.y = trap->y;
	g_dmy_chr.trgt.kind = get_trgt_kind_from_chr( chr );
	g_dmy_chr.trgt.x = chr->x;
	g_dmy_chr.trgt.y = chr->y;
	g_dmy_chr.trgt.true_x = g_dmy_chr.trgt.x;
	g_dmy_chr.trgt.true_y = g_dmy_chr.trgt.y;
	g_dmy_chr.trgt.p = chr;
	g_dmy_chr.flg_chr = FLG_NULL;
	g_dmy_chr.flg_map = FLG_NULL;
	g_dmy_chr.attitude = ATTITUDE_ENEMY;
	lev = calc_trap_lev( trap );
	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		g_dmy_chr.abl.lev[i].n = lev;
		g_dmy_chr.abl.lev[i].max = lev;
		g_dmy_chr.abl.lev[i].add = 0;
	}

	switch( trap->kind ){
	case TRAP_KIND_NULL:
	case TRAP_KIND_MAX_N:
		return;
	case TRAP_KIND_SLEEP:
		chr_cast_spell_spread( &g_dmy_chr, TRUE,
				get_spell_tab( SPELL_KIND_SLEEP ),
				_100_PERCENT );
		break;
	case TRAP_KIND_ARW:
		set_trap_arw_pos( chr, &g_dmy_chr.x, &g_dmy_chr.y );
		chr_cast_spell_normal( &g_dmy_chr, TRUE,
				get_spell_tab( SPELL_KIND_MAGIC_MISSILE ),
				_100_PERCENT );
		break;
	case TRAP_KIND_POISON_DARTS:
		chr_cast_spell_normal( &g_dmy_chr, TRUE,
				get_spell_tab( SPELL_KIND_POISON_CLOUD ),
				_100_PERCENT );
		break;
	case TRAP_KIND_BOMB:
		chr_cast_spell_spread( &g_dmy_chr, TRUE,
				get_spell_tab( SPELL_KIND_MAGIC_MISSILE ),
				_100_PERCENT );
		break;
	case TRAP_KIND_TELEPORT_PARTY:
		if( (is_mbr( chr )) || is_pet( chr ) )
			teleport_party();
		break;
	case TRAP_KIND_TELEPORT:
		teleport_chr( chr );
		break;
	case TRAP_KIND_PIT:
		caught_trap_pit( chr );
		break;
	case TRAP_KIND_CHUTE:
		caught_trap_chute( chr );
		break;
	case TRAP_KIND_SANCTUARY:
		break;
	}
}

/***************************************************************
* 弓矢の罠の矢を発射する壁の座標を決める
* chr_t *chr : 罠を発動させたキャラクタ
* long *x : X 座標を返す
* long *y : Y 座標を返す
***************************************************************/

void	set_trap_arw_pos( chr_t *chr, long *x, long *y )
{
	dun_t	*dun = get_dun();
	long	mx, my;
	long	nx, ny;
	long	i;

	if( chr == NULL )
		return;

	*x = chr->x;
	*y = chr->y;

	switch( randm( 4 ) ){
	default:
	case 0:
		mx = chr->x;
		my = (chr->y / AREA_MAX_Y) * AREA_MAX_Y;
		break;
	case 1:
		mx = (chr->x / AREA_MAX_X) * AREA_MAX_X;
		my = chr->y;
		break;
	case 2:
		mx = chr->x;
		my = (chr->y / AREA_MAX_Y) * AREA_MAX_Y;
		my += AREA_MAX_Y - 1;
		break;
	case 3:
		mx = (chr->x / AREA_MAX_X) * AREA_MAX_X;
		mx += AREA_MAX_X - 1;
		my = chr->y;
		break;
	}

	nx = chr->x;
	ny = chr->y;
	for( i = max_l( AREA_MAX_X, AREA_MAX_Y ); i >= 0; i-- ){
		nx += sgn_l( mx - chr->x );
		ny += sgn_l( my - chr->y );
		if( !clip_pos( nx, ny ) )
			break;
		if( !chk_flg( dun->map.obj.flg[ny][nx],
				FLG_MAP_OBJ_PASS ) ){
			break;
		}
		*x = nx;
		*y = ny;
	}
}

/***************************************************************
* 落し穴の罠を発動
* chr_t *chr : 罠を発動させたキャラクタ
***************************************************************/

void	caught_trap_pit( chr_t *chr )
{
	long	dam;

	if( chr == NULL )
		return;

	dam = calc_max_hp( chr ) * PIT_DAM_RATE / _100_PERCENT;
	dam += PIT_DAM_ADD;

	add_hp( chr, -dam, TRUE, FALSE );
}

/***************************************************************
* シュートの罠を発動
* chr_t *chr : 罠を発動させたキャラクタ
***************************************************************/

void	caught_trap_chute( chr_t *chr )
{
	bool_t	flg_party;

	if( chr == NULL )
		return;

	flg_party = FALSE;
	if( is_mbr( chr ) )
		flg_party = TRUE;
	if( chr->kind == CHR_KIND_MNSTR )
		if( is_pet( chr ) )
			flg_party = TRUE;

	if( flg_party )
		up_dun( -1 );
}

/***************************************************************
* 罠を解除する
* trap_t *trap : 罠
***************************************************************/

void	disarm_trap( trap_t *p )
{
	dun_t	*dun;

	if( p == NULL )
		return;

	call_game_sound_play( SOUND_KIND_TRAP_DISARM, 1 );

	dun = get_dun();

	dun->map.obj.mjr[p->y][p->x] = FACE_MJR_FLOOR;
	dun->map.obj.mnr[p->y][p->x] = FACE_MNR_FLOOR;
	draw_map( p->x, p->y, 1, 1 );

	free_trap( p );
}

/***************************************************************
* 範囲内の罠を発見する
* long x : X 座標
* long y : Y 座標
* long r : 半径
***************************************************************/

void	detect_trap( long x, long y, long r )
{
	trap_t	*p;

	for( p = dun_trap_asgn.next; p != &dun_trap_asgn; p = p->next ){
		if( p->x < (x - r) )
			continue;
		if( p->x > (x + r) )
			continue;
		if( p->y < (y - r) )
			continue;
		if( p->y > (y + r) )
			continue;

		find_trap( p );
	}
}

/***************************************************************
* マップの指定座標の罠が通り抜け可能か調べる
* long x : X 座標
* long y : Y 座標
* return : 通り抜け可能か?
***************************************************************/

bool_t	chk_through_trap( long x, long y )
{
	dun_t	*dun = get_dun();

	if( dun->map.obj.mjr[y][x] != FACE_MJR_TRAP )
		return TRUE;
	if( dun->map.obj.mnr[y][x] == FACE_MNR_TRAP_SANCTUARY )
		return TRUE;

	return FALSE;
}

/***************************************************************
* マップの指定座標に聖域が有るか調べる
* long x : X 座標
* long y : Y 座標
* return : 聖域が有るか?
***************************************************************/

bool_t	chk_map_sanctuary( long x, long y )
{
	dun_t	*dun = get_dun();

	if( dun->map.obj.mjr[y][x] != FACE_MJR_TRAP )
		return FALSE;
	if( dun->map.obj.mnr[y][x] != FACE_MNR_TRAP_SANCTUARY )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 罠の能力値のレベルを計算する
* trap_t *p : 罠
* return : 罠の能力値のレベル
***************************************************************/

long	calc_trap_lev( trap_t *p )
{
	long	lev;

	if( p == NULL )
		return 1;

	lev = labs( p->lev ) * RATE_LEV_PER_DUN_LEV / _100_PERCENT;

	if( lev < 1 )
		lev = 1;

	return lev;
}

/***************************************************************
* 罠をリストにリンクする
* trap_t *ls : 罠のリスト
* trap_t *p : リンクする罠
***************************************************************/

void	ins_ls_trap( trap_t *ls, trap_t *p )
{
	if( ls == NULL )
		return;
	if( p == NULL )
		return;

	if( p->prev != NULL )
		p->prev->next = p->next;
	if( p->next != NULL )
		p->next->prev = p->prev;

	p->prev = ls->prev;
	p->next = ls;

	if( ls->prev != NULL )
		ls->prev->next = p;
	ls->prev = p;
}

/***************************************************************
* 罠を割り当てる
* return : 割り当てた罠
***************************************************************/

trap_t	*alloc_trap( void )
{
	trap_t	*p, dmy;

	p = get_trap_free_next();
	if( p == NULL )
		return NULL;

	p->kind = TRAP_KIND_NULL;
	p->x = MAP_DEL_X;
	p->y = MAP_DEL_Y;

	/* 一時的なトラップリストにぶら下げる */

	dmy.prev = &dmy;
	dmy.next = &dmy;

	ins_ls_trap( &dmy, p );

	p->prev = NULL;
	p->next = NULL;

	return p;
}

/***************************************************************
* 宝箱の罠の割り当てを解放
* item_t *chest : 宝箱
***************************************************************/

void	free_trap_chest( item_t *chest )
{
	if( chest == NULL )
		return;
	if( chest->kind != ITEM_KIND_CHEST )
		return;

	free_trap( chest->dat.chest.trap );
	chest->dat.chest.trap = NULL;
}

/***************************************************************
* 罠の割り当てを解放
* trap_t *p : 罠
***************************************************************/

void	free_trap( trap_t *p )
{
	trap_t	*ls;

	ls = get_trap_free_next();
	if( ls == NULL )
		return;

	ins_ls_trap( ls, p );
}

/***************************************************************
* 罠のフリー・メモリの最初の要素を返す
* return : 罠
***************************************************************/

trap_t	*get_trap_free_next( void )
{
	if( trap_free.next == &trap_free )
		return NULL;

	return trap_free.next;
}

/***************************************************************
* 迷宮の割り当てメモリのヘッダを返す
* return : ヘッダ
***************************************************************/

trap_t	*get_dun_trap_asgn( void )
{
	return &dun_trap_asgn;
}

/***************************************************************
* 指定座標の罠を検索
* long x : X 座標
* long y : Y 座標
* return : 罠
***************************************************************/

trap_t	*get_trap( long x, long y )
{
	trap_t	*p;

	for( p = dun_trap_asgn.next; p != &dun_trap_asgn; p = p->next ){
		if( p == NULL )
			return NULL;

		if( (p->x == x) && (p->y == y) )
			return p;
	}

	return NULL;
}

/***************************************************************
* キャラクタに一番近い罠を検索
* chr_t *chr : キャラクタ
* act_kind_t act_kind : アクション
* return : 罠
***************************************************************/

trap_t	*get_trap_nearest( chr_t *chr, act_kind_t act_kind )
{
	trap_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;

	if( chr == NULL )
		return NULL;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( p = dun_trap_asgn.next; p != &dun_trap_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( p == NULL )
			break;
		if( !chk_get_trap( chr, act_kind, p ) )
			continue;

		tmp_r = labs( p->x - chr->x ) + labs( p->y - chr->y );
		if( tmp_r > min_r )
			continue;

		pos1.x = p->x;
		pos1.y = p->y;
		pos2.x = chr->x;
		pos2.y = chr->y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( tmp_r < min_r ){
			n = 0;
			min_r = tmp_r;
		} else if( tmp_r == min_r ){
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/***************************************************************
* キャラクタに近い罠を検索
* chr_t *chr : キャラクタ
* act_kind_t act_kind : アクション
* return : 罠
***************************************************************/

trap_t	*get_trap_near( chr_t *chr, act_kind_t act_kind )
{
	trap_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;

	if( chr == NULL )
		return NULL;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( p = dun_trap_asgn.next; p != &dun_trap_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( p == NULL )
			break;
		if( !chk_get_trap( chr, act_kind, p ) )
			continue;

		tmp_r = labs( p->x - chr->x ) + labs( p->y - chr->y );
		if( tmp_r > min_r )
			continue;

		pos1.x = p->x;
		pos1.y = p->y;
		pos2.x = chr->x;
		pos2.y = chr->y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( tmp_r < min_r ){
			n = 0;
			min_r = tmp_r;
		} else if( (tmp_r - min_r) <= TRAP_NEAR_R ){
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/***************************************************************
* どのキャラクタもマークしていない罠を検索
* chr_t *chr : キャラクタ
* act_kind_t act_kind : アクション
* return : 罠
***************************************************************/

trap_t	*get_trap_disperse( chr_t *chr, act_kind_t act_kind )
{
	trap_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	long	x, y;

	if( chr == NULL )
		return NULL;

	x = chr->x;
	y = chr->y;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( p = dun_trap_asgn.next; p != &dun_trap_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( p == NULL )
			break;
		if( !chk_get_trap( chr, act_kind, p ) )
			continue;

		tmp_r = labs( p->x - x ) + labs( p->y - y );
		if( tmp_r > min_r )
			continue;

		pos1.x = p->x;
		pos1.y = p->y;
		pos2.x = x;
		pos2.y = y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( tmp_r < min_r ){
			if( is_mbr( chr ) )
				if( chk_already_mark( p, chr ) )
					continue;
			n = 0;
			min_r = tmp_r;
		} else if( tmp_r == min_r ){
			if( is_mbr( chr ) )
				if( chk_already_mark( p, chr ) )
					continue;
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/***************************************************************
* キャラクタに見えている罠をランダムに検索
* chr_t *chr : キャラクタ
* act_kind_t act_kind : アクション
* return : 罠
***************************************************************/

trap_t	*get_trap_randm( chr_t *chr, act_kind_t act_kind )
{
	trap_t	*p, *ret_p;
	long	n;

	if( chr == NULL )
		return NULL;

	ret_p = NULL;
	n = 0;
	for( p = dun_trap_asgn.next; p != &dun_trap_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( p == NULL )
			break;
		if( !chk_get_trap( chr, act_kind, p ) )
			continue;

		pos1.x = p->x;
		pos1.y = p->y;
		pos2.x = chr->x;
		pos2.y = chr->y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		/* 見つけた */
		n++;
		if( randm( n ) == 0 )
			ret_p = p;
	}

	return ret_p;
}

/***************************************************************
* 識別されている罠を検索
* chr_t *chr : キャラクタ
* act_kind_t act_kind : アクション
* return : 罠
***************************************************************/

trap_t	*get_trap_identified( chr_t *chr, act_kind_t act_kind )
{
	return get_trap_identified_sub( chr, act_kind, TRUE );
}

/***************************************************************
* 識別されていない罠を検索
* chr_t *chr : キャラクタ
* act_kind_t act_kind : アクション
* return : 罠
***************************************************************/

trap_t	*get_trap_un_identified( chr_t *chr, act_kind_t act_kind )
{
	return get_trap_identified_sub( chr, act_kind, FALSE );
}

/***************************************************************
* 識別条件付きで罠を検索
* chr_t *chr : キャラクタ
* act_kind_t act_kind : アクション
* return : 罠
***************************************************************/

trap_t	*get_trap_identified_sub(
	chr_t *chr, act_kind_t act_kind,
	bool_t flg_identified
)
{
	trap_t	*p, *ret_p, *sub_ret_p;
	long	min_r, tmp_r;
	long	n, sub_n;
	long	x, y;

	if( chr == NULL )
		return NULL;

	x = chr->x;
	y = chr->y;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	sub_ret_p = NULL;
	sub_n = 0;
	for( p = dun_trap_asgn.next; p != &dun_trap_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( p == NULL )
			break;
		if( !chk_get_trap( chr, act_kind, p ) )
			continue;

		if( flg_identified ){
			if( !p->flg_chked )
				continue;
		} else {
			if( p->flg_chked )
				continue;
		}

		tmp_r = labs( p->x - x ) + labs( p->y - y );
		if( tmp_r > min_r )
			continue;

		pos1.x = p->x;
		pos1.y = p->y;
		pos2.x = x;
		pos2.y = y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		/* 全てすでにマーク済の時の予備 */
		sub_n++;
		if( randm( sub_n ) == 0 )
			sub_ret_p = p;

		if( tmp_r < min_r ){
			if( is_mbr( chr ) )
				if( chk_already_mark( p, chr ) )
					continue;
			n = 0;
			min_r = tmp_r;
		} else if( tmp_r == min_r ){
			if( is_mbr( chr ) )
				if( chk_already_mark( p, chr ) )
					continue;
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	if( ret_p == NULL )
		ret_p = sub_ret_p;

	return ret_p;
}

/***************************************************************
* 罠を検索可能か調べる
* chr_t *chr : キャラクタ
* act_kind_t act_kind : アクション
* trap_t *p : 罠
* return : 検索可能か?
***************************************************************/

bool_t	chk_get_trap( chr_t *chr, act_kind_t act_kind, trap_t *p )
{
	dun_t	*dun;

	dun = get_dun();

	if( p == NULL )
		return FALSE;
	if( !clip_pos( p->x, p->y ) )
		return FALSE;
	if( dun->map.obj.mjr[p->y][p->x] != FACE_MJR_TRAP )
		return FALSE;

	if( is_mbr( chr ) ){
		if( !chk_flg( dun->map.obj.flg[p->y][p->x],
				FLG_MAP_OBJ_FIND ) ){
			return FALSE;
		}
		if( chk_flg( dun->map.obj.flg[p->y][p->x],
				FLG_MAP_OBJ_LOOK_FLOOR ) ){
			return FALSE;
		}
		if( chk_flg( dun->map.obj.flg[p->y][p->x],
				FLG_MAP_OBJ_LOOK_WALL ) ){
			return FALSE;
		}
		if( !chk_mark_trap( p, act_kind ) )
			return FALSE;
	}

	return TRUE;
}

/***************************************************************
* 罠をマーク出来るアクションかチェック
* trap_t *p : 罠
* act_kind_t act_kind : アクション
* return : マーク出来るか?
***************************************************************/

bool_t	chk_mark_trap( trap_t *p, act_kind_t act_kind )
{
	if( p == NULL )
		return FALSE;

	switch( act_kind ){
	case ACT_KIND_TRAP_DISARM:
	case ACT_KIND_TRAP_BREAK:
	case ACT_KIND_TRAP_CHK:
		return TRUE;
	default:
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* 罠のデータ・テーブルを検索
* trap_kind_t kind : 罠の種類
* return : データ・テーブル
***************************************************************/

trap_tab_t	*get_trap_tab( trap_kind_t kind )
{
	long	n;

	n = get_trap_tab_n( kind );
	if( n <= -1 )
		return NULL;

	return( &(trap_tab[n]) );
}

/***************************************************************
* 罠のデータ・テーブルのインデックスを検索
* trap_kind_t kind : 罠の種類
* return : データ・テーブルのインデックス
***************************************************************/

long	get_trap_tab_n( trap_kind_t kind )
{
	long	i;

	for( i = 0; i < LOOP_MAX_1000; i++ )
		if( trap_tab[i].kind == kind )
			return i;

	return -1;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_trap_c( void )
{
	check_memory( check_memory_trap_c_trap_buf,
			"trap.c: trap_buf" );
	check_memory( check_memory_trap_c_trap_tab,
			"trap.c: trap_tab" );
	check_memory( check_memory_trap_c_g_dmy_chr,
			"trap.c: g_dmy_chr" );
}
