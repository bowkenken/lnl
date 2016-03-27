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
* $Id: dun.c,v 1.168 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* 迷宮
***************************************************************/

#define	DUN_C
#include	"inc.h"

/***************************************************************/

/* 通路の幅 */
#define	PATH_WIDTH	3

/* 通路を表すエリアの種類 */
#define	AREA_PATH	-1

/* 上り階段の数 */
#define	STAIRS_UP_MAX_N	2

/* 下り階段の数 */
#define	STAIRS_DOWN_MAX_N	2

/* ラスト・ステージの階段の数 */
#define	STAIRS_LAST_BOSS_MAX_N	2

/* 上り下り出来る判定の階段までの距離 */
#define	STAIRS_MAX_R	2

/* 現在の階層を冒険している NPC の平均数 */
#define	DUN_NPC_AVE_N	6

/* (NPC の平均数) - (階層) / ? */
#define	DUN_NPC_DIV_N	4

/* 1番近いドアを探す時、同じ距離にあると判断する距離 */
#define	DOOR_NEAR_R	4

#define	LAST_BOSS_ROOM_PTN_MAX_N	3

/***************************************************************
* 確率
***************************************************************/

/* エリアに明かりが点いている最大の確率 */
#define	LIGHTED_ROOM_MAX_RATE	((rate_t)80)

/* エリアが部屋になる確率 */
#define	RATE_ROOM	((rate_t)50)

/* ドアが開いている確率 */
#define	RATE_DOOR_OPEN	((rate_t)10)

/* ドアが固定されている確率 */
#define	RATE_DOOR_JAMMED	((rate_t)5)

/* ドアが壊れている確率 */
#define	RATE_DOOR_BROKEN	((rate_t)1)

/* 十字路が隠れている確率 */
#define	RATE_HIDE_CROSS_PATH	((rate_t)80)

/* 固定モンスターのミミックがただの宝箱でない確率 */
#define	MIMIC_RATE	((rate_t)50)

/***************************************************************
* 変数定義
***************************************************************/

static dun_t	dun;
check_memory_def( check_memory_dun_c_dun )

static area_t	g_room_ptn_max_n, g_boss_room_ptn_max_n;
check_memory_def( check_memory_dun_c_g_room_ptn_max_n )

static crsr_ptn_t	g_crsr_ptn_usr[CRSR_PTN_MAX_N];
check_memory_def( check_memory_dun_c_g_crsr_ptn_usr )
static crsr_ptn_t	g_main_crsr_ptn;
check_memory_def( check_memory_dun_c_g_main_crsr_ptn )
static crsr_ptn_t	g_sub_crsr_ptn;
check_memory_def( check_memory_dun_c_g_sub_crsr_ptn )
static long	g_main_crsr_ptn_n;
static long	g_sub_crsr_ptn_n;
static long	g_crsr_ptn_max_n;
check_memory_def( check_memory_dun_c_g_main_crsr_ptn_n )

static long	g_nest_flg_dun;
check_memory_def( check_memory_dun_c_g_nest_flg_dun )

/***************************************************************
* データ・ファイル
***************************************************************/

#include	"dun-tab.h"
#include	"crsr-ptn.h"

/***************************************************************
* 迷宮の初期化
***************************************************************/

void	init_dun( void )
{
	g_nest_flg_dun = make_nest_flg();
	bgn_nest_flg( g_nest_flg_dun );

	g_room_ptn_max_n = sizeof( room_ptn )
			/ sizeof( room_ptn_t );
	g_boss_room_ptn_max_n = sizeof( boss_room_ptn )
			/ sizeof( room_ptn_t );

	reset_dun( FALSE );

	end_nest_flg( g_nest_flg_dun );
}

/***************************************************************
* カーソルの初期化
***************************************************************/

void	init_crsr_ptn( void )
{
	long	i;

	g_main_crsr_ptn_n = 0;
	g_sub_crsr_ptn_n = 1;

	if( load_crsr_ptn( g_crsr_ptn_usr, &g_crsr_ptn_max_n ) ){
		for( i = 0; i < g_crsr_ptn_max_n; i++ )
			set_crsr_ptn( &(g_crsr_ptn_usr[i]),
					&(g_crsr_ptn_usr[i]) );
	} else {
		g_crsr_ptn_max_n = sizeof( crsr_ptn_dflt )
				/ sizeof( crsr_ptn_dflt[0] );

		for( i = 0; i < g_crsr_ptn_max_n; i++ ){
			set_crsr_ptn( &(crsr_ptn_dflt[i]),
					&(crsr_ptn_dflt[i]) );
			g_crsr_ptn_usr[i] = crsr_ptn_dflt[i];
		}
	}

	reset_crsr_ptn();
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_dun( void )
{
}

/***************************************************************
* カーソル・パターンの最大数を返す
* return : カーソル・パターンの最大数
***************************************************************/

long	get_crsr_ptn_max_n( void )
{
	return g_crsr_ptn_max_n;
}

/***************************************************************
* カーソル・パターンの最大数を設定
* long n : カーソル・パターンの最大数
* return : 以前のカーソル・パターンの最大数
***************************************************************/

long	set_crsr_ptn_max_n( long n )
{
	long	prev;

	prev = g_crsr_ptn_max_n;
	g_crsr_ptn_max_n = n;

	return prev;
}

/***************************************************************
* カーソルの現在のパターン
* return : カーソルの現在のパターン
***************************************************************/

long	get_main_crsr_ptn_n( void )
{
	return g_main_crsr_ptn_n;
}

/***************************************************************
* カーソルの現在のパターン番号を設定
* long n : カーソル・パターン番号
* return : 以前のカーソル・パターン番号
***************************************************************/

long	set_main_crsr_ptn_n( long n )
{
	long	prev;

	prev = g_main_crsr_ptn_n;
	g_main_crsr_ptn_n = n;

	return prev;
}

/***************************************************************
* カーソルの現在のパターン
* return : カーソルの現在のパターン
***************************************************************/

long	get_sub_crsr_ptn_n( void )
{
	return g_sub_crsr_ptn_n;
}

/***************************************************************
* カーソルの現在のパターン番号を設定
* long n : カーソル・パターン番号
* return : 以前のカーソル・パターン番号
***************************************************************/

long	set_sub_crsr_ptn_n( long n )
{
	long	prev;

	prev = g_sub_crsr_ptn_n;
	g_sub_crsr_ptn_n = n;

	return prev;
}

/***************************************************************
* カーソル・パターンをリセット
***************************************************************/

void	reset_crsr_ptn( void )
{
	long	main_n, sub_n, max_n;

	max_n = get_crsr_ptn_max_n();
	if( max_n <= 0 )
		return;

	main_n = get_main_crsr_ptn_n() % max_n;
	sub_n = get_sub_crsr_ptn_n() % max_n;

	set_crsr_ptn( &g_main_crsr_ptn, &(g_crsr_ptn_usr[main_n]) );
	set_crsr_ptn( &g_sub_crsr_ptn, &(g_crsr_ptn_usr[sub_n]) );
}

/***************************************************************
* 迷宮をリセット
* bool_t flg_wall : マップを壁で埋めるか?
***************************************************************/

void	reset_dun( bool_t flg_wall )
{
	long	x, y;

	bgn_nest_flg( g_nest_flg_dun );

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			dun.map.sect[y][x] = 'z';

			if( flg_wall ){
				dun.map.obj.mjr[y][x] = FACE_MJR_WALL;
				dun.map.obj.mnr[y][x] = FACE_MNR_WALL;
				dun.map.obj.flg[y][x] = FLG_NULL;
			} else {
				dun.map.obj.mjr[y][x] = FACE_MJR_FLOOR;
				dun.map.obj.mnr[y][x] = FACE_MNR_FLOOR;
				dun.map.obj.flg[y][x] = (FLG_MAP_OBJ_PASS
						| FLG_MAP_OBJ_LOOK);
			}

			dun.map.chr.mjr[y][x] = FACE_MJR_NULL;
			dun.map.chr.mnr[y][x] = FACE_MNR_NULL;
			dun.map.chr.flg[y][x] = FLG_NULL;

			dun.map.total.mjr[y][x] = dun.map.obj.mjr[y][x];
			dun.map.total.mnr[y][x] = dun.map.obj.mnr[y][x];
			dun.map.total.flg[y][x] = FLG_NULL;

			dun.map.light_depth_obj[y][x] = 0;
			dun.map.light_depth_chr[y][x] = 0;

			dun.map.chr_p[y][x] = NULL;
		}
	}

	for( y = 0; y < AREA_MAP_MAX_Y; y++ ){
		for( x = 0; x < AREA_MAP_MAX_X; x++ ){
			dun.area[y][x] = AREA_PATH;
		}
	}

	dun.door_n = 0;

	reset_map_event();
	clr_gui_vfx_all();

	end_nest_flg( g_nest_flg_dun );
}

/***************************************************************
* カーソル・パターンを返す
* reutrn : カーソル・パターン
***************************************************************/

crsr_ptn_t	*get_main_crsr_ptn( void )
{
	return &g_main_crsr_ptn;
}

/***************************************************************
* サブ・カーソル・パターンを返す
* reutrn : サブ・カーソル・パターン
***************************************************************/

crsr_ptn_t	*get_sub_crsr_ptn( void )
{
	return &g_sub_crsr_ptn;
}

/***************************************************************
* カーソル・パターンを設定
* crsr_ptn_t *dst : 設定先パターン
* crsr_ptn_t *src : 参照元パターン
* reutrn : 設定が成功したか?
***************************************************************/

bool_t	set_crsr_ptn( crsr_ptn_t *dst, crsr_ptn_t *src )
{
	long	max_len;
	long	y;

	if( src == NULL )
		return FALSE;
	if( dst == NULL )
		return FALSE;

	*dst = *src;

	max_len = 0;
	for( y = 0; y < CRSR_PTN_MAX_Y_LEN; y++ ){
		long	len;

		if( dst->face[y][0] == '\0' )
			break;

		len = str_len_std( dst->face[y] ) / 2;
		max_len = max_l( max_len, len );
	}
	dst->x_len = max_len;
	dst->y_len = y;
	src->x_len = max_len;
	src->y_len = y;

	dst->x = -(dst->x_len / 2);
	dst->y = -(dst->y_len / 2);
	src->x = -(src->x_len / 2);
	src->y = -(src->y_len / 2);

	return TRUE;
}

/***************************************************************
* 迷宮を上り下りして街に帰る
***************************************************************/

void	up_dun_town( void )
{
	up_dun( -dun.lev );
}

/***************************************************************
* 迷宮を上り下りする
* long d : 上り階数(+)、下り階数(-)
***************************************************************/

void	up_dun( long d )
{
	party_t	*pty = get_party();
	long	i;

	dun.lev += d;

	if( dun.lev > +DUN_MAX_LEV_FLOOR )
		dun.lev = +DUN_MAX_LEV_FLOOR;
	if( dun.lev < -DUN_MAX_LEV_BASE )
		dun.lev = -DUN_MAX_LEV_BASE;

	if( g_flg_init ){
		if( get_flg_no_save() )
			menu_save_n( TRUE, SAVE_N_AUTO );
		else
			menu_save_n( FALSE, SAVE_N_AUTO );
	}

	up_dun_msg();

	/* メンバーの到達階層を更新 */

	for( i = 0; i < MBR_MAX_N; i++ ){
		/* 地上 */
		if( sgn_l( dun.lev ) >= +1 ){
			if( pty->mbr[i]->dun_max_lev_floor
					< labs( dun.lev ) ){
				pty->mbr[i]->dun_max_lev_floor
						= labs( dun.lev );
			}
		}
		/* 地下 */
		if( sgn_l( dun.lev ) <= -1 ){
			if( pty->mbr[i]->dun_max_lev_base
					< labs( dun.lev ) ){
				pty->mbr[i]->dun_max_lev_base
						= labs( dun.lev );
			}
		}
	}

	reset_all( TRUE );
}

/***************************************************************
* 迷宮を上り下りした際のメッセージの表示とシーン切り替え
***************************************************************/

void	up_dun_msg( void )
{
	if( sgn_l( dun.lev ) >= +1 ){
		print_msg( FLG_NULL, MSG_UP_DOWN_DUN_FLOOR,
				labs( dun.lev ) );
		change_scene( SCENE_N_DUN );
	} else if( sgn_l( dun.lev ) <= -1 ){
		print_msg( FLG_NULL, MSG_UP_DOWN_DUN_BASE,
				labs( dun.lev ) );
		change_scene( SCENE_N_DUN );
	} else {
		print_msg( FLG_NULL, MSG_UP_DOWN_DUN_GROUND );
		change_scene( SCENE_N_TOWN );
	}
}

/***************************************************************
* ラスボスの階層に入る
***************************************************************/

void	enter_last_boss_dun( void )
{
	change_last_scene( LAST_SCENE_N_ENTER );
	reset_all( TRUE );
	set_map_event_tab( last_boss_map_event_tab );
}

/***************************************************************
* 迷宮を初期化(乱数の種も設定)
* bool_t flg_appear : パーティの出現処理をするか?
***************************************************************/

void	reset_all_save( bool_t flg_appear )
{
	srandm( g_randm_seed_save );

	reset_all( TRUE );
}

/***************************************************************
* 迷宮を初期化
* bool_t flg_appear : パーティの出現処理をするか?
***************************************************************/

void	reset_all( bool_t flg_appear )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		clr_chr_trgt_act( pty->mbr[i], FALSE );

	bgn_nest_flg( g_nest_flg_dun );

	garbage_collection_all_item();
	reset_trap();
	reset_mnstr();
	reset_spell();
	release_all_mbr();

	clr_map_all_mbr();
	clr_map_all_pet();

	if( get_scene() == SCENE_N_LAST_BOSS ){
		make_dun_last_boss();
		appear_party_last_boss();
	} else if( dun.lev == 0 ){
		make_town();
		if( flg_appear ){
			if( !appear_party_town() )
				appear_party();
		}
	} else {
		make_dun();
		if( flg_appear ){
			appear_party();
		}
	}
	put_request_all_obj();

	end_nest_flg( g_nest_flg_dun );

	call_pcg_dun_reset();
	redraw_all();
}

/***************************************************************
* 迷宮を自動生成
***************************************************************/

void	make_dun( void )
{
	long	x, y;
	bool_t	flg_boss;
	long	item_n, item_max_n;
	long	mnstr_n, mnstr_max_n;
	long	npc_n, npc_max_n;
	long	trap_n, trap_max_n;
	long	i, j;

	bgn_nest_flg( g_nest_flg_dun );

	/* 初期化 */

	reset_dun( TRUE );

	x = randm( AREA_MAP_MAX_X );
	y = randm( AREA_MAP_MAX_Y );
	flg_boss = make_area_boss( boss_room_ptn,
			g_boss_room_ptn_max_n, x, y );

	/* 部屋を造る */

	for( y = 0; y < AREA_MAP_MAX_Y; y++ ){
		for( x = 0; x < AREA_MAP_MAX_X; x++ ){
			make_area( room_ptn, g_room_ptn_max_n, x, y );
		}
	}

	/* 通路を造る */

	for( y = 0; y < AREA_MAP_MAX_Y; y++ ){
		for( x = 0; x < AREA_MAP_MAX_X; x++ ){
			if( dun.area[y][x] == AREA_PATH ){
				make_path( x, y );
			}
		}
	}

	/* 水平 */

	for( y = 0; y < AREA_MAP_MAX_Y; y++ ){
		for( x = 0; x < AREA_MAP_MAX_X - 1; x++ ){
			if( !chk_room( x, y ) )
				continue;
			if( chk_room( x + 1, y ) )
				connect_room( x, y, +1, 0 );
		}
	}

	/* 垂直 */

	for( y = 0; y < AREA_MAP_MAX_Y - 1; y++ ){
		for( x = 0; x < AREA_MAP_MAX_X; x++ ){
			if( !chk_room( x, y ) )
				continue;
			if( chk_room( x, y + 1 ) )
				connect_room( x, y, 0, +1 );
		}
	}

	/* 十字路に隠しドアを創る */

	for( y = 0; y < AREA_MAP_MAX_Y; y++ ){
		for( x = 0; x < AREA_MAP_MAX_X; x++ ){
			if( !chk_room( x, y ) ){
				make_hide_cross_path( x, y );
			}
		}
	}

	/* マップの端を壁にする */

	make_fence();

	/* 上り階段を造る */

	for( i = 0; i < STAIRS_UP_MAX_N; i++ )
		make_stairs_randm( FACE_MJR_STAIRS_UP );

	/* 下り階段を造る */

	if( !flg_boss ){
		for( i = 0; i < STAIRS_DOWN_MAX_N; i++ ){
			make_stairs_randm( FACE_MJR_STAIRS_DOWN );
		}
	}

	/* ラスボスへの階段を造る */

	if( labs( dun.lev ) >= labs( DUN_LEV_LAST_BOSS_STAIRS ) )
		for( i = 0; i < STAIRS_LAST_BOSS_MAX_N; i++ )
			make_stairs_randm( FACE_MNR_STAIRS_LAST_BOSS );

	/* 固定アイテム */

	item_n = 0;

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			if( dun.map.obj.mjr[y][x] != FACE_ROOM_PTN_ITEM )
				continue;

			dun.map.obj.mjr[y][x] = FACE_MJR_FLOOR;
			dun.map.obj.mnr[y][x] = FACE_MNR_FLOOR;
			dun.map.obj.flg[y][x] = (FLG_MAP_OBJ_PASS
					| FLG_MAP_OBJ_LOOK);
			if( make_item( x, y, dun.lev )
					!= ITEM_KIND_NULL ){
				item_n++;
			}
		}
	}

	/* ミミック */

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			if( dun.map.obj.mjr[y][x] != FACE_ROOM_PTN_MIMIC )
				continue;

			dun.map.obj.mjr[y][x] = FACE_MJR_FLOOR;
			dun.map.obj.mnr[y][x] = FACE_MNR_FLOOR;
			dun.map.obj.flg[y][x] |= (FLG_MAP_OBJ_PASS
					| FLG_MAP_OBJ_LOOK);
			if( rate_randm( MIMIC_RATE ) ){
				make_mnstr( x, y, TRUE, dun.lev,
						MNSTR_KIND_MIMIC );
			} else {
				item_t	*item;

				item = make_item_chest( dun.lev,
						get_chest_n( dun.lev ),
						TRUE );
				if( item == NULL )
					continue;
				if( !put_item( item, x, y, 1, FALSE ) ){
					del_item( item );
					continue;
				}
			}
		}
	}

	/* 固定モンスター */

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			mnstr_kind_t	mnstr_kind;
			char	mjr, mnr;

			mjr = dun.map.obj.mjr[y][x];
			mnr = dun.map.obj.mnr[y][x];

			/* GOD は置けない */
			if( !isalpha( mjr ) )
				continue;

			dun.map.obj.mjr[y][x] = FACE_MJR_FLOOR;
			dun.map.obj.mnr[y][x] = FACE_MNR_FLOOR;
			dun.map.obj.flg[y][x] |= (FLG_MAP_OBJ_PASS
					| FLG_MAP_OBJ_LOOK);

			mnstr_kind = get_mnstr_kind_from_face( mjr, mnr );
			if( mnstr_kind == MNSTR_KIND_NULL )
				continue;

			make_mnstr( x, y, TRUE, dun.lev, mnstr_kind );
		}
	}

	/* 固定罠 */

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			if( dun.map.obj.mjr[y][x] != FACE_ROOM_PTN_TRAP )
				continue;

			dun.map.obj.mjr[y][x] = FACE_MJR_FLOOR;
			dun.map.obj.mnr[y][x] = FACE_MNR_FLOOR;
			dun.map.obj.flg[y][x] |= (FLG_MAP_OBJ_PASS
					| FLG_MAP_OBJ_LOOK);

			make_trap( x, y, dun.lev );
		}
	}

	/* ランダムアイテム */

	item_max_n = roll_dice( DUN_ITEM_AVE_N, TRUE );

	for( i = 0; i < LOOP_MAX_10000; i++ ){
		if( item_n >= item_max_n )
			break;

		x = 1 + randm( MAP_MAX_X - 2 );
		y = 1 + randm( MAP_MAX_Y - 2 );
		if( make_item( x, y, dun.lev ) != ITEM_KIND_NULL )
			item_n++;
	}
	item_max_n = item_n;

	/* ランダムモンスター */

	mnstr_max_n = roll_dice( MNSTR_AVE_N, TRUE );
	if( mnstr_max_n > MNSTR_MAX_N )
		mnstr_max_n = MNSTR_MAX_N;

	mnstr_n = 0;
	for( i = 0; i < LOOP_MAX_4000; i++ ){
		if( mnstr_n >= mnstr_max_n )
			break;

		x = 1 + randm( MAP_MAX_X - 2 );
		y = 1 + randm( MAP_MAX_Y - 2 );
		if( make_mnstr_rand( x, y, FALSE, dun.lev ) != NULL )
			mnstr_n++;
	}

	/* ランダムな NPC */

	npc_max_n = roll_dice( DUN_NPC_AVE_N, FALSE );
	npc_max_n -= labs( dun.lev ) / DUN_NPC_DIV_N;

	if( npc_max_n > (MNSTR_MAX_N - mnstr_n) )
		npc_max_n = (MNSTR_MAX_N - mnstr_n);
	if( npc_max_n < 0 )
		npc_max_n = 0;

	npc_n = 0;
	for( i = 0; i < LOOP_MAX_4000; i++ ){
		if( npc_n >= npc_max_n )
			break;

		x = 1 + randm( MAP_MAX_X - 2 );
		y = 1 + randm( MAP_MAX_Y - 2 );

		if( make_npc_rand( x, y, 0 ) != NULL )
			npc_n++;
	}

	/* ランダムな罠 */

	trap_max_n = roll_dice( TRAP_AVE_N, TRUE );
	if( trap_max_n > TRAP_MAX_N )
		trap_max_n = TRAP_MAX_N;

	trap_n = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		trap_t	*trap;

		x = 0;
		y = 0;
		for( j = 0; j < LOOP_MAX_100; j++ ){
			x = 1 + randm( MAP_MAX_X - 2 );
			y = 1 + randm( MAP_MAX_Y - 2 );
			if( dun.map.obj.mjr[y][x] != FACE_MJR_FLOOR )
				continue;
			if( dun.map.obj.mnr[y][x] != FACE_MNR_FLOOR )
				continue;

			break;
		}

		trap = make_trap( x, y, dun.lev );
		if( trap != NULL )
			trap_n++;
		if( trap_n >= trap_max_n )
			break;
	}

	/* トラップ部屋 */

	make_chk_trap_room( dun.lev );

	if( flg_boss ){
		curs_attrset_chr( get_mbr_randm( MAP_DEL_X, MAP_DEL_Y ),
				-1, FALSE );
		print_msg( FLG_NULL, MSG_FEEL_BOSS );
		curs_attrset_dflt();
	}

	end_nest_flg( g_nest_flg_dun );
}

/***************************************************************
* ラスボスの階層を生成
***************************************************************/

void	make_dun_last_boss( void )
{
	long	x, y;
	long	i;

	bgn_nest_flg( g_nest_flg_dun );

	/* 初期化 */

	reset_dun( TRUE );

	/* 部屋を造る */

	x = AREA_MAP_MAX_X / 2;
	y = AREA_MAP_MAX_Y - LAST_BOSS_ROOM_PTN_MAX_N;
	if( y < 0 )
		y = 0;

	for( i = 0; i < LAST_BOSS_ROOM_PTN_MAX_N; i++ ){
		make_area_last_boss( &(last_boss_room_ptn[i]),
				(area_t)1, x, y );
		y++;
	}

	/* マップの端を壁にする */

	make_fence();

	/* 固定モンスター */

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			mnstr_kind_t	mnstr_kind;
			char	mjr, mnr;

			mjr = dun.map.obj.mjr[y][x];
			mnr = dun.map.obj.mnr[y][x];

			/* GOD は置けない */
			if( !isalpha( mjr ) )
				continue;

			dun.map.obj.mjr[y][x] = FACE_MJR_FLOOR;
			dun.map.obj.mnr[y][x] = FACE_MNR_FLOOR;
			dun.map.obj.flg[y][x] |= (FLG_MAP_OBJ_PASS
					| FLG_MAP_OBJ_LOOK);

			mnstr_kind = get_mnstr_kind_from_face( mjr, mnr );
			if( mnstr_kind == MNSTR_KIND_NULL )
				continue;

			make_mnstr( x, y, TRUE, dun.lev, mnstr_kind );
		}
	}

	/**/

	end_nest_flg( g_nest_flg_dun );
}

/***************************************************************
* 迷宮の外枠の壁を生成
***************************************************************/

void	make_fence( void )
{
	long	n;

	for( n = 0; n < MAP_MAX_Y; n++ ){
		if( dun.map.obj.mnr[n][0] == FACE_MNR_GATE )
			continue;

		dun.map.obj.mjr[n][0] = FACE_MJR_WALL;
		dun.map.obj.mnr[n][0] = FACE_MNR_WALL;
		dun.map.obj.flg[n][0] &= ~(FLG_MAP_OBJ_PASS
				| FLG_MAP_OBJ_LOOK);
	}
	for( n = 0; n < MAP_MAX_Y; n++ ){
		if( dun.map.obj.mnr[n][MAP_MAX_X - 1] == FACE_MNR_GATE )
			continue;

		dun.map.obj.mjr[n][MAP_MAX_X - 1] = FACE_MJR_WALL;
		dun.map.obj.mnr[n][MAP_MAX_X - 1] = FACE_MNR_WALL;
		dun.map.obj.flg[n][MAP_MAX_X - 1] &= ~(FLG_MAP_OBJ_PASS
				| FLG_MAP_OBJ_LOOK);
	}

	for( n = 0; n < MAP_MAX_X; n++ ){
		if( dun.map.obj.mnr[0][n] == FACE_MNR_GATE )
			continue;

		dun.map.obj.mjr[0][n] = FACE_MJR_WALL;
		dun.map.obj.mnr[0][n] = FACE_MNR_WALL;
		dun.map.obj.flg[0][n] &= ~(FLG_MAP_OBJ_PASS
				| FLG_MAP_OBJ_LOOK);
	}
	for( n = 0; n < MAP_MAX_X; n++ ){
		if( dun.map.obj.mnr[MAP_MAX_Y - 1][n] == FACE_MNR_GATE )
			continue;

		dun.map.obj.mjr[MAP_MAX_Y - 1][n] = FACE_MJR_WALL;
		dun.map.obj.mnr[MAP_MAX_Y - 1][n] = FACE_MNR_WALL;
		dun.map.obj.flg[MAP_MAX_Y - 1][n] &= ~(FLG_MAP_OBJ_PASS
				| FLG_MAP_OBJ_LOOK);
	}
}

/***************************************************************
* 迷宮の部屋を生成
* room_ptn_t *ptn : 部屋のパターン
* area_t max_n : 部屋のパターンの最大数
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	make_area( room_ptn_t *ptn, area_t max_n, long x, long y )
{
	long	i;
	long	flg;

	if( dun.area[y][x] != AREA_PATH )
		return;

	if( !chk_rate_room( dun.lev ) )
		return;

	for( i = 0; i < (max_n * LOOP_MAX_100); i++ ){
		area_t	n;

		n = (area_t)randm( max_n );
		if( labs( dun.lev ) < ptn[n].min_lev )
			continue;
		if( labs( dun.lev ) > ptn[n].max_lev )
			continue;
		if( sgn_l( dun.lev ) != ptn[n].sgn_lev )
			continue;

		flg = randm( 8 ) / 2;	/* 垂直・水平フラグ */
		set_room( ptn, n, x, y, flg );
		break;
	}
}

/***************************************************************
* 迷宮の中ボス部屋を生成
* room_ptn_t *ptn : 部屋のパターン
* area_t max_n : 部屋のパターンの最大数
* long x : X 座標
* long y : Y 座標
***************************************************************/

bool_t	make_area_boss( room_ptn_t *ptn, area_t max_n, long x, long y )
{
	long	n;

	if( dun.area[y][x] != AREA_PATH )
		return FALSE;
	if( dun.lev == 0 )
		return FALSE;
	if( !chk_boss_dun_lev( dun.lev ) )
		return FALSE;

	n = labs( dun.lev ) / DUN_LEV_BOSS;
	n = (n - 1 + max_n) % max_n;

	set_room( ptn, (area_t)n, x, y, FLG_NULL );

	return TRUE;
}

/***************************************************************
* 迷宮のラスボスの部屋を生成
* room_ptn_t *ptn : 部屋のパターン
* area_t max_n : 部屋のパターンの最大数
* long x : X 座標
* long y : Y 座標
***************************************************************/

bool_t	make_area_last_boss( room_ptn_t *ptn, area_t max_n, long x, long y )
{
	if( dun.area[y][x] != AREA_PATH )
		return FALSE;

	set_room( ptn, (area_t)0, x, y, FLG_NULL );

	return TRUE;
}

/***************************************************************
* 指定の迷宮の階層に中ボスが出るかチェック
* long dun_lev : 迷宮の階層
* return : 中ボスが出るか?
***************************************************************/

bool_t	chk_boss_dun_lev( long dun_lev )
{
	return( (labs( dun_lev ) % DUN_LEV_BOSS) == 0 );
}

/***************************************************************
* 部屋を迷宮に置く
* room_ptn_t *room : 部屋のパターン
* area_t n : 部屋のパターン番号
* long x : X 座標
* long y : Y 座標
* long flg_rev : 上下、左右の反転フラグ
***************************************************************/

void	set_room( room_ptn_t *room, area_t n, long x, long y, long flg_rev )
{
	long	i, j, ii, jj;
	long	mx, my;
	char	mjr, mnr;
	flg_map_t	flg;
	sect_t	sect;
	flg_map_t	flg_light;

	dun.area[y][x] = n;
	flg_light = chk_lighted_room();

	for( i = 0; i < AREA_MAX_Y; i++ ){
		for( j = 0; j < AREA_MAX_X; j++ ){
			if( chk_flg( flg_rev, 0x02 ) )
				ii = AREA_MAX_Y - 1 - i;
			else
				ii = i;

			if( chk_flg( flg_rev, 0x01 ) )
				jj = AREA_MAX_X - 1 - j;
			else
				jj = j;

			mx = x * AREA_MAX_X + jj;
			my = y * AREA_MAX_Y + ii;

			/* 部屋のパターンを読み込む */

			mjr = room[n].ptn[i][j * 2 + 0];
			mnr = room[n].ptn[i][j * 2 + 1];
			sect = room[n].sect[i][j];

			/* 空白は穴にする */

			if( mjr == FACE_MJR_NULL ){
				mjr = FACE_MJR_FLOOR;
				mnr = FACE_MNR_HOLE;
			}

			/* 部屋のパターンを書き込む */

			dun.map.obj.mjr[my][mx] = mjr;
			dun.map.obj.mnr[my][mx] = mnr;
			dun.map.obj.flg[my][mx] = FLG_NULL;
			dun.map.sect[my][mx] = sect;

			/* フラグを書き込む */

			flg = FLG_MAP_OBJ_PASS;
			switch( mjr ){
			case FACE_MJR_FLOOR:
				if( mnr == FACE_MNR_HOLE )
					flg &= ~(FLG_MAP_OBJ_PASS);
				else
					flg |= FLG_MAP_OBJ_PASS;
				flg |= FLG_MAP_OBJ_LOOK;
				break;
			case FACE_MJR_DOOR_OPEN:
				flg |= (FLG_MAP_OBJ_PASS
						| FLG_MAP_OBJ_LOOK);
				break;
			case FACE_MJR_WALL:
			case FACE_MJR_DOOR_CLOSE:
				flg &= ~(FLG_MAP_OBJ_PASS
						| FLG_MAP_OBJ_LOOK);
				break;
			default:
				flg |= (FLG_MAP_OBJ_PASS
						| FLG_MAP_OBJ_LOOK);
			}
			dun.map.obj.flg[my][mx] = flg;

			/* マップ・イベントの座標を設定 */

			if( (mjr == FACE_MJR_FLOOR) && isalnum( mnr ) )
				set_map_event_pos( mnr, mx, my );

			/* 明かりを設定 */

			if( flg_light )
				dun.map.light_depth_obj[my][mx] = 1;
			else
				dun.map.light_depth_obj[my][mx] = 0;
		}
	}

	/* 固定的なドア */

	for( i = 0; i < AREA_MAX_Y; i++ ){
		for( j = 0; j < AREA_MAX_X; j++ ){
			mx = x * AREA_MAX_X + j;
			my = y * AREA_MAX_Y + i;
			if( dun.map.obj.mjr[my][mx]
					== FACE_MJR_DOOR_OPEN ){
				make_door_room( mx, my );
			} else if( dun.map.obj.mjr[my][mx]
					== FACE_MJR_DOOR_CLOSE ){
				make_door_room( mx, my );
			}
		}
	}
}

/***************************************************************
* 部屋に明かりがついているか乱数で決める
* return : 部屋に明かりがついているか
***************************************************************/

bool_t	chk_lighted_room( void )
{
	rate_t	rate;

	if( get_scene() == SCENE_N_LAST_BOSS )
		return TRUE;

	rate = LIGHTED_ROOM_MAX_RATE - (randm( labs( dun.lev ) ) * 2);

	if( rate <= 0 )
		return FALSE;
	return rate_randm( rate );
}

/***************************************************************
* 通路に明かりがついているか乱数で決める
* return : 通路に明かりがついているか
***************************************************************/

bool_t	chk_lighted_path( void )
{
	rate_t	rate;

	rate = 40 - (randm( labs( dun.lev ) ) * 2);

	if( rate <= 0 )
		return FALSE;
	return rate_randm( rate );
}

/***************************************************************
* 通路を生成
* long area_x : X 座標
* long area_y : Y 座標
***************************************************************/

void	make_path( long area_x, long area_y )
{
	long	bgn_x, bgn_y, end_x, end_y;
	long	bend_x, bend_y;
	long	mx, my;

	mx = area_x * AREA_MAX_X;
	my = area_y * AREA_MAX_Y;


	/* 水平方向に通路をつなぐ */

	/* 隣の通路のＹ座標 */
	bgn_y = chk_extend_path_h( area_x, area_y, -1 );
	/* 隣の通路のＹ座標 */
	end_y = chk_extend_path_h( area_x, area_y, +1 );
	/* 折れ曲がるＸ座標 */
	bend_x = 1 + randm( AREA_MAX_X - PATH_WIDTH + 1 - 2 );

	line_path( mx + 0, my + bgn_y, mx + bend_x, my + bgn_y,
			SECT_PATH_H );
	line_path( mx + bend_x, my + bgn_y, mx + bend_x, my + end_y,
			SECT_PATH_H );
	line_path( mx + bend_x, my + end_y,
			mx + AREA_MAX_X - PATH_WIDTH, my + end_y,
			SECT_PATH_H );

	if( chk_room( area_x - 1, area_y ) ){
		finish_path( mx + 0,
				my + bgn_y, -1, 0 );
	}
	if( chk_room( area_x + 1, area_y ) ){
		finish_path( mx + AREA_MAX_Y - PATH_WIDTH,
				my + end_y, +1, 0 );
	}


	/* 垂直方向に通路をつなぐ */

	/* 隣の通路のＸ座標 */
	bgn_x = chk_extend_path_v( area_x, area_y, -1 );
	/* 隣の通路のＸ座標 */
	end_x = chk_extend_path_v( area_x, area_y, +1 );
	/* 折れ曲がるＹ座標 */
	bend_y = 1 + randm( AREA_MAX_Y - PATH_WIDTH + 1 - 2 );

	line_path( mx + bgn_x, my + 0, mx + bgn_x, my + bend_y,
			SECT_PATH_V );
	line_path( mx + bgn_x, my + bend_y, mx + end_x, my + bend_y,
			SECT_PATH_V );
	line_path( mx + end_x, my + bend_y,
			mx + end_x, my + AREA_MAX_Y - PATH_WIDTH,
			SECT_PATH_V );

	if( chk_room( area_x, area_y - 1 ) ){
		finish_path( mx + bgn_x,
				my + 0, 0, -1 );
	}
	if( chk_room( area_x, area_y + 1 ) ){
		finish_path( mx + end_x,
				my + AREA_MAX_Y - PATH_WIDTH, 0, +1 );
	}

	if( chk_lighted_path() ){
		on_light_area( area_x * AREA_MAX_X,
				area_y * AREA_MAX_Y, FALSE );
	}
}

/***************************************************************
* 隣のエリアから通路が伸びているか調べる（東西）
* long ax : エリアの X 座標
* long ay : エリアの Y 座標
* long d : 東(+)、西(-)の指定
* return : 隣のエリアの通路のY 座標
***************************************************************/

long	chk_extend_path_h( long ax, long ay, long d )
{
	long	i;
	long	map_x, map_y;

	/* はみ出たら */
	if( ((ax + d) < 0) || (AREA_MAP_MAX_X <= (ax + d)) )
		return( 1 + randm( AREA_MAX_Y - PATH_WIDTH + 1 - 2 ) );

	if( d <= -1 )
		map_x = (ax + d) * AREA_MAX_X + (AREA_MAX_X - 1);
	else
		map_x = (ax + d) * AREA_MAX_X + 0;

	for( i = 0; i < AREA_MAX_Y - PATH_WIDTH + 1; i++ ){
		map_y = ay * AREA_MAX_Y + i;

		if( dun.map.obj.mjr[map_y][map_x] == FACE_MJR_FLOOR ){
			return i;
		}
	}

	/* ランダムに決めたＹ座標 */
	return( 1 + randm( AREA_MAX_Y - PATH_WIDTH + 1 - 2 ) );
}

/***************************************************************
* 隣のエリアから通路が伸びているか調べる（南北）
* long ax : エリアの X 座標
* long ay : エリアの Y 座標
* long d : 南(+)、北(-)の指定
* return : 隣のエリアの通路の X 座標
***************************************************************/

long	chk_extend_path_v( long ax, long ay, long d )
{
	long	i;
	long	map_x, map_y;

	/* はみ出たら */
	if( ((ay + d) < 0) || (AREA_MAP_MAX_Y <= (ay + d)) )
		return( 1 + randm( AREA_MAX_X - PATH_WIDTH + 1 - 2 ) );

	if( d <= -1 )
		map_y = (ay + d) * AREA_MAX_Y + (AREA_MAX_Y - 1);
	else
		map_y = (ay + d) * AREA_MAX_Y + 0;

	for( i = 0; i < AREA_MAX_X - PATH_WIDTH + 1; i++ ){
		map_x = ax * AREA_MAX_X + i;

		if( dun.map.obj.mjr[map_y][map_x] == FACE_MJR_FLOOR ){
			return i;
		}
	}

	/* ランダムに決めたＸ座標 */
	return( 1 + randm( AREA_MAX_X - PATH_WIDTH + 1 - 2 ) );
}

/***************************************************************
* 指定のエリアが部屋かどうかチェック
* long ax : エリアの X 座標
* long ay : エリアの Y 座標
* return : 部屋か?
***************************************************************/

bool_t	chk_room( long ax, long ay )
{
	if( ax < 0 )
		return FALSE;
	if( ax >= AREA_MAP_MAX_X )
		return FALSE;
	if( ay < 0 )
		return FALSE;
	if( ay >= AREA_MAP_MAX_Y )
		return FALSE;

	if( dun.area[ay][ax] == AREA_PATH )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 通路の先端を部屋の中まで伸ばす
* long mx : X 座標
* long my : Y 座標
* long dx : 通路を掘る方向、東(+)西(-)
* long dy : 通路を掘る方向、南(+)北(-)
***************************************************************/

void	finish_path( long mx, long my, long dx, long dy )
{
	long	i;

	if( dx < 0 ){	/* 左の時 */
		for( i = 0; i < AREA_MAX_X; i++ ){
			if( chk_finish_path( mx, my, -1, 0 ) )
				break;

			/* 通路を伸ばす */
			put_path( mx, my, -1, 0, SECT_PATH_DFLT );
			mx--;
		}
	} else if( dx > 0 ){	/* 右の時 */
		for( i = 0; i < AREA_MAX_X; i++ ){
			if( chk_finish_path( mx, my, +1, 0 ) )
				break;

			/* 通路を伸ばす */
			put_path( mx, my, +1, 0, SECT_PATH_DFLT );
			mx++;
		}
	} else if( dy < 0 ){	/* 上の時 */
		for( i = 0; i < AREA_MAX_Y; i++ ){
			if( chk_finish_path( mx, my, 0, -1 ) )
				break;

			/* 通路を伸ばす */
			put_path( mx, my, 0, -1, SECT_PATH_DFLT );
			my--;
		}
	} else if( dy > 0 ){	/* 下の時 */
		for( i = 0; i < AREA_MAX_Y; i++ ){
			if( chk_finish_path( mx, my, 0, +1 ) )
				break;

			/* 通路を伸ばす */
			put_path( mx, my, 0, +1, SECT_PATH_DFLT );
			my++;
		}
	}
}

/***************************************************************
* 通路の先端が部屋の中まで掘れたかチェック
* long mx : X 座標
* long my : Y 座標
* long dx : 通路を掘る方向、東(+)西(-)
* long dy : 通路を掘る方向、南(+)北(-)
* return : 堀終ったか?
***************************************************************/

bool_t	chk_finish_path( long mx, long my, long dx, long dy )
{
	long	i;
	bool_t	flg;

	if( dx < 0 ){
		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my + i][mx + dx]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, -1, 0 );
			return TRUE;
		}

		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my - 1][mx + i]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, 0, -1 );
			return TRUE;
		}

		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my + PATH_WIDTH][mx + i]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, 0, +1 );
			return TRUE;
		}
	} else if( dx > 0 ){
		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my + i][mx + dx + PATH_WIDTH - 1]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, +1, 0 );
			return TRUE;
		}

		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my - 1][mx - i + PATH_WIDTH - 1]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, 0, -1 );
			return TRUE;
		}

		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my + PATH_WIDTH]
					[mx - i + PATH_WIDTH - 1]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
 			make_door_path( mx, my, 0, +1 );
			return TRUE;
		}
	} else if( dy < 0 ){
		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my + dy][mx + i]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, 0, -1 );
			return TRUE;
		}

		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my + i][mx - 1]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, -1, 0 );
			return TRUE;
		}

		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my + i][mx + PATH_WIDTH]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, +1, 0 );
			return TRUE;
		}
	} else if( dy > 0 ){
		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my + dy + PATH_WIDTH - 1][mx + i]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, 0, +1 );
			return TRUE;
		}

		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my - i + PATH_WIDTH - 1][mx - 1]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, -1, 0 );
			return TRUE;
		}

		flg = TRUE;
		for( i = 0; i < PATH_WIDTH; i++ ){
			if( dun.map.obj.mjr[my - i + PATH_WIDTH - 1]
					[mx + PATH_WIDTH]
					!= FACE_MJR_FLOOR ){
				flg = FALSE;
				break;
			}
		}
		if( flg ){
			make_door_path( mx, my, +1, 0 );
			return TRUE;
		}
	}

	return FALSE;
}

/***************************************************************
* 隣り合った部屋どうしをつなげる
* long ax : エリアの X 座標
* long ay : エリアの Y 座標
* long dx : 通路を掘る方向、東(+)西(-)
* long dy : 通路を掘る方向、南(+)北(-)
***************************************************************/

void	connect_room( long ax, long ay, long dx, long dy )
{
	long	mx, my;

	if( dx < 0 ){
		/* 左の時 */
		my = ay * AREA_MAX_Y + 1
				+ randm( AREA_MAX_Y - PATH_WIDTH - 2 );

		mx = ax * AREA_MAX_X - 1;
		finish_path( mx, my, -1, 0 );
		mx = ax * AREA_MAX_X - PATH_WIDTH + 1;
		finish_path( mx, my, +1, 0 );
	} else if( dx > 0 ){
		/* 右の時 */
		my = ay * AREA_MAX_Y + 1
				+ randm( AREA_MAX_Y - PATH_WIDTH - 2 );

		mx = ax * AREA_MAX_X + AREA_MAX_X - 1;
		finish_path( mx, my, -1, 0 );
		mx = ax * AREA_MAX_X + AREA_MAX_X - PATH_WIDTH + 1;
		finish_path( mx, my, +1, 0 );
	} else if( dy < 0 ){
		/* 上の時 */
		mx = ax * AREA_MAX_X + 1
				+ randm( AREA_MAX_X - PATH_WIDTH - 2 );

		my = ay * AREA_MAX_Y - 1;
		finish_path( mx, my, 0, -1 );
		my = ay * AREA_MAX_Y - PATH_WIDTH + 1;
		finish_path( mx, my, 0, +1 );
	} else if( dy > 0 ){
		/* 下の時 */
		mx = ax * AREA_MAX_X + 1
				+ randm( AREA_MAX_X - PATH_WIDTH - 2 );

		my = ay * AREA_MAX_Y + AREA_MAX_Y - 1;
		finish_path( mx, my, 0, -1 );
		my = ay * AREA_MAX_Y + AREA_MAX_Y - PATH_WIDTH + 1;
		finish_path( mx, my, 0, +1 );
	}
}

/***************************************************************
* 通路の先にドアを生成
* long mx : X 座標
* long my : Y 座標
* long dx : 方向、東(+)西(-)
* long dy : 方向、南(+)北(-)
***************************************************************/

void	make_door_path( long mx, long my, long dx, long dy )
{
	if( dx < 0 ){
		make_door( mx, my,
				mx + 1,
				my + PATH_WIDTH - 1,
				FACE_MNR_NULL );
	}
	if( dx > 0 ){
		make_door( mx + 1, my,
				mx + PATH_WIDTH - 1,
				my + PATH_WIDTH - 1,
				FACE_MNR_NULL );
	}
	if( dy < 0 ){
		make_door( mx, my,
				mx + PATH_WIDTH - 1,
				my + 1,
				FACE_MNR_NULL);
	}
	if( dy > 0 ){
		make_door( mx, my + 1,
				mx + PATH_WIDTH - 1,
				my + PATH_WIDTH - 1,
				FACE_MNR_NULL );
	}
}

/***************************************************************
* マップ・テーブルで設定された固定ドアを生成
* long mx : X 座標
* long my : Y 座標
***************************************************************/

void	make_door_room( long mx, long my )
{
	long	dx, dy;
	long	i;

	/* すでに登録ずみか */
	if( (mx - 1) >= 0 )
		if( dun.map.obj.mjr[my][mx - 1] == FACE_MJR_DOOR_CLOSE )
			return;
	if( (my - 1) >= 0 )
		if( dun.map.obj.mjr[my - 1][mx] == FACE_MJR_DOOR_CLOSE )
			return;


	for( i = 0; i < AREA_MAX_X; i++ ){
		if( dun.map.obj.mjr[my][mx + i] != FACE_MJR_DOOR_CLOSE ){
			break;
		}
	}
	dx = i - 1;
	if( dx < 0 )
		return;

	for( i = 0; i < AREA_MAX_Y; i++ ){
		if( dun.map.obj.mjr[my + i][mx] != FACE_MJR_DOOR_CLOSE ){
			break;
		}
	}
	dy = i - 1;
	if( dy < 0 )
		return;

	make_door( mx, my, mx + dx, my + dy, dun.map.obj.mnr[my][mx] );
}

/***************************************************************
* ドアを生成
* long bx : 始点 X 座標
* long by : 始点 Y 座標
* long ex : 終点 X 座標
* long ey : 終点 Y 座標
* char mnr : マイナーの顔文字
* return : 生成したドア
***************************************************************/

door_t	*make_door( long bx, long by, long ex, long ey, char mnr )
{
	flg_door_t	flg;

	flg = FLG_NULL;

	if( get_scene() == SCENE_N_LAST_BOSS ){
		flg |= FLG_DOOR_SECRET;
		if( mnr == FACE_MNR_GATE )
			flg |= FLG_DOOR_GATE;
	} else if( mnr == FACE_MNR_NULL ){
		if( chk_rate_door_open( dun.lev ) )
			flg |= FLG_DOOR_OPEN;

		if( chk_rate_door_jammed( dun.lev ) )
			flg |= FLG_DOOR_JAMMED;

		if( chk_rate_door_broken( dun.lev ) )
			flg |= FLG_DOOR_BROKEN;

		if( chk_rate_door_secret( dun.lev ) )
			flg |= FLG_DOOR_SECRET;

		flg &= ~(FLG_DOOR_CHKED);
	} else if( mnr == FACE_MNR_GATE ){
		flg |= FLG_DOOR_GATE;
	} else if( mnr == FACE_MNR_WINDOW ){
		mnr = FACE_MNR_WINDOW;
	} else if( chk_face_window( bx, by, ex, ey ) ){
		mnr = FACE_MNR_WINDOW;
	} else {
		flg |= FLG_DOOR_SHOP;
	}

	return make_door_flg( bx, by, ex, ey, mnr, flg );
}

/***************************************************************
* ドアを窓にするか調べる
* long bx : 始点 X 座標
* long by : 始点 Y 座標
* long ex : 終点 X 座標
* long ey : 終点 Y 座標
* return : 窓にするか?
***************************************************************/

bool_t	chk_face_window( long bx, long by, long ex, long ey )
{
	long	x, y;

	if( dun.lev != 0 )
		return FALSE;

	for( y = by; y <= ey; y++ ){
		if( !clip_pos( bx - 1, y ) )
			return FALSE;
		if( dun.map.obj.mjr[y][bx - 1] != FACE_MJR_WALL )
			return FALSE;

		if( !clip_pos( ex + 1, y ) )
			return FALSE;
		if( dun.map.obj.mjr[y][ex + 1] != FACE_MJR_WALL )
			return FALSE;
	}

	for( x = bx; x <= ex; x++ ){
		if( !clip_pos( x, by - 1 ) )
			return FALSE;
		if( dun.map.obj.mjr[by - 1][x] != FACE_MJR_WALL )
			return FALSE;

		if( !clip_pos( x, ey + 1 ) )
			return FALSE;
		if( dun.map.obj.mjr[ey + 1][x] != FACE_MJR_WALL )
			return FALSE;
	}

	return TRUE;
}

/***************************************************************
* フラグを指定してドアを生成
* long bx : 始点 X 座標
* long by : 始点 Y 座標
* long ex : 終点 X 座標
* long ey : 終点 Y 座標
* char mnr : マイナーの顔文字
* flg_door_t flg : ドアのフラグ
* return : 生成したドア
***************************************************************/

door_t	*make_door_flg(
	long bx, long by,
	long ex, long ey,
	char mnr, flg_door_t flg
)
{
	long	i;
	long	tmp;
	long	dx, dy;
	long	n;

	if( dun.door_n >= DOOR_MAX_N )
		return NULL;

	n = dun.door_n;

	if( bx > ex ){
		tmp = bx;
		bx = ex;
		ex = tmp;
	}
	if( by > ey ){
		tmp = by;
		by = ey;
		ey = tmp;
	}

	if( mnr == FACE_MNR_GATE ){
		if( bx < 0 )
			bx = 0;
		if( ex > MAP_MAX_X - 1 )
			ex = MAP_MAX_X - 1;
		if( by < 0 )
			by = 0;
		if( ey > MAP_MAX_Y - 1 )
			ey = MAP_MAX_Y - 1;
	} else {
		if( bx < 1 )
			bx = 1;
		if( ex > MAP_MAX_X - 2 )
			ex = MAP_MAX_X - 2;
		if( by < 1 )
			by = 1;
		if( ey > MAP_MAX_Y - 2 )
			ey = MAP_MAX_Y - 2;
	}

	dx = ex - bx + 1;
	dy = ey - by + 1;
	if( dx <= 0 )
		return NULL;
	if( dy <= 0 )
		return NULL;

	/* 指定の位置にすでに大きいドアがあるなら return */
	for( i = 0; i < n; i++ ){
		if( bx < dun.door[i].x )
			continue;
		if( by < dun.door[i].y )
			continue;
		if( (dun.door[i].x + dun.door[i].dx) < (bx + dx) )
			continue;
		if( (dun.door[i].y + dun.door[i].dy) < (by + dy) )
			continue;

		return NULL;
	}

	/* 指定の位置にすでに小さいドアがあるなら削除 */
	for( i = 0; i < n; i++ ){
		if( dun.door[i].x < bx )
			continue;
		if( dun.door[i].y < by )
			continue;
		if( (bx + dx) < (dun.door[i].x + dun.door[i].dx) )
			continue;
		if( (by + dy) < (dun.door[i].y + dun.door[i].dy) )
			continue;

		dun.door[i].x = MAP_DEL_X;
		dun.door[i].y = MAP_DEL_Y;
		dun.door[i].dx = 0;
		dun.door[i].dy = 0;
	}

	dun.door[n].n = n;
	dun.door[n].x = bx;
	dun.door[n].y = by;
	dun.door[n].dx = dx;
	dun.door[n].dy = dy;
	dun.door[n].flg = flg;
	dun.door[n].mnr = mnr;

	dun.door_n++;

	set_face_door( n );

	return( &(dun.door[n]) );
}

/***************************************************************
* ドアの状態によって、フラグや顔文字を設定
* long dr_n : ドア番号
***************************************************************/

void	set_face_door( long dr_n )
{
	door_t	*p;
	char	mjr, mnr;
	flg_map_t	flg;
	long	i, j;

	p = &(dun.door[dr_n]);

	mjr = FACE_MJR_DOOR_CLOSE;
	mnr = FACE_MNR_DOOR_NORM;
	flg = FLG_NULL;

	/* if 文の順番に注意 */

	if( chk_flg( p->flg, FLG_DOOR_OPEN ) ){
		mjr = FACE_MJR_DOOR_OPEN;
		flg |= (FLG_MAP_OBJ_PASS | FLG_MAP_OBJ_LOOK);
	}

	if( chk_flg( p->flg, FLG_DOOR_JAMMED ) )
		mnr = FACE_MNR_DOOR_JAMMED;

	if( chk_flg( p->flg, FLG_DOOR_CHKED ) )
		flg |= FLG_MAP_OBJ_FIND;
	else
		mnr = FACE_MNR_DOOR_NORM;

	if( chk_flg( p->flg, FLG_DOOR_BROKEN ) ){
		p->flg |= FLG_DOOR_OPEN;
		mjr = FACE_MJR_DOOR_OPEN;
		mnr = FACE_MNR_DOOR_BROKEN;
		flg |= (FLG_MAP_OBJ_PASS | FLG_MAP_OBJ_LOOK);;
	}

	if( chk_face_window( p->x, p->y,
			(p->x + p->dx - 1), (p->y + p->dy - 1) ) ){
		mnr = FACE_MNR_WINDOW;
	}

	if( chk_flg( p->flg, FLG_DOOR_SECRET ) ){
		p->flg &= ~(FLG_DOOR_OPEN);
		mjr = FACE_MJR_DOOR_CLOSE;
		mnr = FACE_MNR_DOOR_SECRET;
		flg &= ~(FLG_MAP_OBJ_PASS | FLG_MAP_OBJ_LOOK);
		flg |= FLG_MAP_OBJ_LOOK_WALL;
	}

	if( chk_flg( p->flg, FLG_DOOR_SHOP ) ){
		mjr = FACE_MJR_DOOR_CLOSE;
		/* mnr は make_door() で設定済み */
		mnr = p->mnr;
		flg &= ~(FLG_MAP_OBJ_PASS | FLG_MAP_OBJ_LOOK);
		flg |= FLG_MAP_OBJ_FIND;
	}

	if( chk_find_door( dr_n ) )
		flg |= FLG_MAP_OBJ_FIND;
	if( dun.lev == 0 )
		flg |= FLG_MAP_OBJ_FIND;

	if( chk_flg( p->flg, FLG_DOOR_GATE ) ){
		mjr = FACE_MJR_DOOR_CLOSE;
		mnr = FACE_MNR_GATE;
		flg &= ~(FLG_MAP_OBJ_PASS | FLG_MAP_OBJ_LOOK);
		flg |= FLG_MAP_OBJ_FIND;
	}

	/**/

	p->mjr = mjr;
	p->mnr = mnr;
	for( i = 0; i < p->dy; i++ ){
		for( j = 0; j < p->dx; j++ ){
			long	x, y;

			x = p->x + j;
			y = p->y + i;
			dun.map.obj.mjr[y][x] = mjr;
			dun.map.obj.mnr[y][x] = mnr;
			dun.map.obj.flg[y][x] = flg;
		}
	}
}

/***************************************************************
* ドアが発見されているか調べる
* long dr_n : ドア番号
* return : ドアが発見されているか?
***************************************************************/

bool_t	chk_find_door( long dr_n )
{
	long	i, j;

	for( i = 0; i < dun.door[dr_n].dy; i++ ){
		for( j = 0; j < dun.door[dr_n].dx; j++ ){
			long	x, y;

			x = dun.door[dr_n].x + j;
			y = dun.door[dr_n].y + i;
			if( chk_flg( dun.map.obj.flg[y][x],
					FLG_MAP_OBJ_FIND ) ){
				return TRUE;
			}
		}
	}

	return FALSE;
}

/***************************************************************
* ドアを壊す
* long dr_n : ドア番号
* return : ドアが壊せたか?
***************************************************************/

bool_t	break_door( chr_t *chr, long dr_n )
{
	if( chk_flg( dun.door[dr_n].flg, FLG_DOOR_SHOP ) ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_DOOR_BREAK_SHOP );
		return FALSE;
	}
	if( chk_flg( dun.door[dr_n].flg, FLG_DOOR_GATE ) ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_DOOR_BREAK_SHOP );
		return FALSE;
	}
	if( chk_flg( dun.door[dr_n].flg, FLG_DOOR_BROKEN ) ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_DOOR_BREAK_BROKEN );
		return FALSE;
	}

	dun.door[dr_n].flg |= FLG_DOOR_BROKEN | FLG_DOOR_OPEN;
	set_face_door( dr_n );
	draw_door( dr_n );

	return TRUE;
}

/***************************************************************
* ドアの隣接座標を返す
* pos_t *pos : 座標を返す先
* door_t *dr : ドア
* chr_t *chr : キャラクタ
***************************************************************/

void	get_near_pos_door( pos_t *pos, door_t *dr, chr_t *chr )
{
	if( pos == NULL )
		return;
	if( dr == NULL )
		return;
	if( chr == NULL )
		return;

	pos->x = dr->x;
	pos->y = dr->y;

	/* ドアの１ブロックとなり */
	if( chr->x < dr->x )
		pos->x = dr->x - 1;
	else if( (dr->x + dr->dx - 1) < chr->x )
		pos->x = (dr->x + dr->dx - 1) + 1;

	if( chr->y < dr->y )
		pos->y = dr->y - 1;
	else if( (dr->y + dr->dy - 1) < chr->y )
		pos->y = (dr->y + dr->dy - 1) + 1;
}

/***************************************************************
* エリア内の十字路に隠しドアを生成する
* long ax : エリアの X 座標
* long ay : エリアの Y 座標
* return : 成功したか?
***************************************************************/

bool_t	make_hide_cross_path( long ax, long ay )
{
	long	x, y;
	bool_t	ret;

	if( chk_room( ax, ay ) )
		return FALSE;

	if( !chk_rate_hide_cross_path( dun.lev ) )
		return FALSE;

	ret = FALSE;

	for( y = 0; y < AREA_MAX_Y; y++ ){
		for( x = 0; x < AREA_MAX_X; x++ ){
			long	mx, my;

			mx = ax * AREA_MAX_X + x;
			my = ay * AREA_MAX_Y + y;
			if( chk_cross_path( mx, my ) ){
				hide_cross_path( mx, my );
				ret = TRUE;
			}
		}
	}

	return ret;
}

/***************************************************************
* 隠しドアを生成できる十字路か調べる
* long mx : X 座標
* long my : Y 座標
* return : 生成できるか?
***************************************************************/

bool_t	chk_cross_path( long mx, long my )
{
	long	x, y;
	long	i, j;

	if( !clip_pos( mx - 1, my - 1 ) )
		return FALSE;
	if( !clip_pos( mx + 1, my + 1 ) )
		return FALSE;

	for( i = 0; i < PATH_WIDTH; i++ ){
		for( j = 0; j < PATH_WIDTH; j++ ){
			x = mx + j;
			y = my + i;
			if( dun.map.obj.mjr[y][x] != FACE_MJR_FLOOR ){
				return FALSE;
			}
		}
	}

	for( i = 0; i < PATH_WIDTH; i++ ){
		x = mx + i;
		y = my - 1;
		if( dun.map.obj.mjr[y][x] != FACE_MJR_FLOOR )
			return FALSE;

		x = mx + i;
		y = my + PATH_WIDTH;
		if( dun.map.obj.mjr[y][x] != FACE_MJR_FLOOR )
			return FALSE;

		x = mx - 1;
		y = my + i;
		if( dun.map.obj.mjr[y][x] != FACE_MJR_FLOOR )
			return FALSE;

		x = mx + PATH_WIDTH;
		y = my + i;
		if( dun.map.obj.mjr[y][x] != FACE_MJR_FLOOR )
			return FALSE;
	}

	x = mx - 1;
	y = my - 1;
	if( dun.map.obj.mjr[y][x] == FACE_MJR_FLOOR )
		return FALSE;

	x = mx + PATH_WIDTH;
	y = my - 1;
	if( dun.map.obj.mjr[y][x] == FACE_MJR_FLOOR )
		return FALSE;

	x = mx - 1;
	y = my + PATH_WIDTH;
	if( dun.map.obj.mjr[y][x] == FACE_MJR_FLOOR )
		return FALSE;

	x = mx + PATH_WIDTH;
	y = my + PATH_WIDTH;
	if( dun.map.obj.mjr[y][x] == FACE_MJR_FLOOR )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 十字路に隠しドアを生成する
* long mx : X 座標
* long my : Y 座標
***************************************************************/

void	hide_cross_path( long mx, long my )
{
	long	bx, by, ex, ey;
	long	x, y;
	char	mnr;
	flg_door_t	flg;

	mnr = FACE_MNR_NULL;
	flg = FLG_DOOR_SECRET;
	flg &= ~(FLG_DOOR_OPEN);

	if( randm( 2 ) == 0 ){
		/* 西にドアをつくる */
		bx = mx - 1;
		ex = mx - 1;
		by = my;
		ey = my + PATH_WIDTH - 1;
		make_door_flg( bx, by, ex, ey, mnr, flg );

		/* 東にドアをつくる */
		bx = mx + PATH_WIDTH;
		ex = mx + PATH_WIDTH;
		by = my;
		ey = my + PATH_WIDTH - 1;
		make_door_flg( bx, by, ex, ey, mnr, flg );

		for( y = my; y < my + PATH_WIDTH; y++ ){
			for( x = mx; x < mx + PATH_WIDTH; x++ ){
				dun.map.sect[y][x] = SECT_PATH_V;
			}
		}
	} else {
		/* 北にドアをつくる */
		bx = mx;
		ex = mx + PATH_WIDTH - 1;
		by = my - 1;
		ey = my - 1;
		make_door_flg( bx, by, ex, ey, mnr, flg );

		/* 南にドアをつくる */
		bx = mx;
		ex = mx + PATH_WIDTH - 1;
		by = my + PATH_WIDTH;
		ey = my + PATH_WIDTH;
		make_door_flg( bx, by, ex, ey, mnr, flg );

		for( y = my; y < my + PATH_WIDTH; y++ ){
			for( x = mx; x < mx + PATH_WIDTH; x++ ){
				dun.map.sect[y][x] = SECT_PATH_H;
			}
		}
	}
}

/***************************************************************
* 階段をランダムに生成する
* char face : 階段の種類の顔文字
***************************************************************/

void	make_stairs_randm( char face )
{
	long	x, y;
	long	i;

	for( i = 0; i < LOOP_MAX_4000; i++ ){
		x = randm( MAP_MAX_X );
		y = randm( MAP_MAX_Y );

		if( dun.map.obj.mjr[y][x] != FACE_MJR_FLOOR )
			continue;
		if( dun.map.obj.mnr[y][x] != FACE_MNR_FLOOR )
			continue;

		make_stairs( x, y, face );
		break;
	}
}

/***************************************************************
* 中心の座標を指定して、床を探してから階段を生成する
* long x : X 座標
* long y : Y 座標
* char face : 階段の種類の顔文字
***************************************************************/

void	make_stairs( long x, long y, char face )
{
	const long	max_r = MAP_MAX_X;
	long	r;

	for( r = 0; r < max_r; r++ ){
		long	dx, dy;

		for( dx = -r, dy = -r; dx <= +r; dx++ )
			if( make_stairs_sub( x + dx, y + dy, face ) )
				return;

		for( dx = +r, dy = -r; dy <= +r; dy++ )
			if( make_stairs_sub( x + dx, y + dy, face ) )
				return;

		for( dx = +r, dy = +r; dx >= -r; dx-- )
			if( make_stairs_sub( x + dx, y + dy, face ) )
				return;

		for( dx = -r, dy = +r; dy >= -r; dy-- )
			if( make_stairs_sub( x + dx, y + dy, face ) )
				return;
	}
}

/***************************************************************
* 座標を指定して、階段を生成する
* long x : X 座標
* long y : Y 座標
* char face : 階段の種類の顔文字
* return : エラーが無かったか?
***************************************************************/

bool_t	make_stairs_sub( long x, long y, char face )
{
	char	mjr, mnr;

	if( !clip_pos( x, y ) )
		return FALSE;
	if( dun.map.obj.mjr[y][x] != FACE_MJR_FLOOR )
		return FALSE;
	if( dun.map.obj.mnr[y][x] != FACE_MNR_FLOOR )
		return FALSE;

	if( face == FACE_MNR_STAIRS_LAST_BOSS ){
		mjr = FACE_MJR_STAIRS_LAST_BOSS;
		mnr = FACE_MNR_STAIRS_LAST_BOSS;
	} else if( (face == FACE_MJR_STAIRS_DOWN)
			|| (face == FACE_MNR_STAIRS_DOWN) ){
		if( labs( dun.lev ) >= labs( DUN_MAX_LEV_BASE ) )
			return TRUE;

		mjr = FACE_MJR_STAIRS_DOWN;
		mnr = FACE_MNR_STAIRS_DOWN;
	} else {
		if( labs( dun.lev ) >= labs( DUN_MAX_LEV_FLOOR ) )
			return TRUE;

		mjr = FACE_MJR_STAIRS_UP;
		mnr = FACE_MNR_STAIRS_UP;
	}

	dun.map.obj.mjr[y][x] = mjr;
	dun.map.obj.mnr[y][x] = mnr;

	return TRUE;
}

/***************************************************************
* 石像を生成する
* long x : X 座標
* long y : Y 座標
* long dun_lev : 迷宮の階層
* bool_t flg_self : キャラクタのいる位置に生成する
* return : 生成できたか?
***************************************************************/

bool_t	set_statue( long x, long y, long dun_lev, bool_t flg_self )
{
	long	ix, iy;

	if( dun.map.obj.mjr[y][x] != FACE_MJR_FLOOR )
		return FALSE;
	if( dun.map.obj.mnr[y][x] != FACE_MNR_FLOOR )
		return FALSE;
	if( !flg_self && (dun.map.chr.mjr[y][x] != FACE_MJR_NULL) )
		return FALSE;

	dun.map.obj.mjr[y][x] = FACE_MJR_WALL;
	dun.map.obj.mnr[y][x] = FACE_MNR_STATUE;
	dun.map.obj.flg[y][x] = FLG_NULL;

	ix = x + randm( 3 ) - 1;
	iy = y + randm( 3 ) - 1;
	make_item( ix, iy, dun_lev );

	return TRUE;
}

/***************************************************************
* マップの各レイヤーから綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total( long x, long y, long dx, long dy )
{
	pos_t	*main_crsr = get_main_crsr();
	pos_t	*sub_crsr = get_sub_crsr();
	crsr_ptn_t	*main_ptn = get_main_crsr_ptn();
	crsr_ptn_t	*sub_ptn = get_sub_crsr_ptn();

	/* 背景 */
	set_map_total_water( x, y, dx, dy );
	set_map_total_last_boss_bg( x, y, dx, dy );
	set_map_total_bg( x, y, dx, dy );

	/* カーソルの属性 */
	set_map_total_crsr_attr( sub_crsr, sub_ptn, x, y, dx, dy );
	set_map_total_crsr_attr( main_crsr, main_ptn, x, y, dx, dy );

	/* オブジェクト */
	set_map_total_obj( x, y, dx, dy );

	/* アンカー */
	set_map_total_square( x, y, dx, dy );

	/* モンスターとメンバー */
	set_map_total_chr( x, y, dx, dy );
	set_map_total_last_boss_fg( x, y, dx, dy );

	/* カーソルのパターン */
	set_map_total_crsr_ptn( sub_crsr, sub_ptn, x, y, dx, dy );
	set_map_total_crsr_ptn( main_crsr, main_ptn, x, y, dx, dy );
}

/***************************************************************
* 背景マップの水地形から綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_water( long x, long y, long dx, long dy )
{
	long	bx, by;
	long	ex, ey;
	long	xx, yy;
	char	mjr, mnr;
	curs_attr_n_t	attr_n;
	curs_attr_t	*attr_dflt;

	attr_dflt = get_curs_attr();

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
			set_face_from_map_obj(
					TRUE, xx, yy, &mjr, &mnr,
					FALSE );
			if( mjr != FACE_MJR_WATER )
				continue;

			attr_n = get_curs_attr_n_map_obj(
					mjr, mnr, FLG_NULL );

			dun.map.total.mjr[yy][xx] = mjr;
			dun.map.total.mnr[yy][xx] = mnr;
			dun.map.total.flg[yy][xx] = FLG_NULL;
			dun.map.attr[yy][xx] = attr_dflt[attr_n];
		}
	}
}

/***************************************************************
* 背景マップから綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_bg( long x, long y, long dx, long dy )
{
	long	bx, by;
	long	ex, ey;
	long	xx, yy;
	char	mjr, mnr;
	curs_attr_n_t	attr_n;
	curs_attr_t	*attr_dflt;

	attr_dflt = get_curs_attr();

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
			set_face_from_map_obj(
					TRUE, xx, yy, &mjr, &mnr,
					FALSE );
			if( mjr == FACE_MJR_WATER )
				continue;

			attr_n = get_curs_attr_n_map_obj(
					mjr, mnr, FLG_NULL );

			dun.map.total.mjr[yy][xx] = mjr;
			dun.map.total.mnr[yy][xx] = mnr;
			dun.map.total.flg[yy][xx] = FLG_NULL;
			dun.map.attr[yy][xx] = attr_dflt[attr_n];
		}
	}
}

/***************************************************************
* 背景マップの見かけの顔文字を返す
* bool_t flg_chk_find : 見つかっているかチェックするか?
* long x : X 座標
* long y : Y 座標
* char *mjr : メジャーの顔文字を返す
* char *mnr : マイナーの顔文字を返す
***************************************************************/

void	set_face_from_map_obj(
	bool_t flg_chk_find,
	long x, long y, char *mjr, char *mnr,
	bool_t flg_gui
)
{
	flg_map_t	flg;
	long	dep;

	if( mjr == NULL )
		return;
	if( mnr == NULL )
		return;
	if( !clip_pos( x, y ) )
		return;

	*mjr = dun.map.obj.mjr[y][x];
	*mnr = dun.map.obj.mnr[y][x];
	flg = dun.map.obj.flg[y][x];
	dep = calc_light_depth( x, y );

	if( (*mjr == FACE_MJR_FLOOR) && (*mnr == FACE_MNR_HOLE) ){
		if( !flg_gui ){
			*mjr = FACE_MJR_NULL;
			*mnr = FACE_MNR_NULL;
		}
	}
	if( chk_flg( flg, FLG_MAP_OBJ_LOOK_WALL ) ){
		*mjr = FACE_MJR_WALL;
		*mnr = FACE_MNR_WALL;
	}
	if( chk_flg( flg, FLG_MAP_OBJ_LOOK_FLOOR ) ){
		*mjr = FACE_MJR_FLOOR;
		*mnr = FACE_MNR_FLOOR;
	}

	if( (*mjr == FACE_MJR_FLOOR) && isalnum( *mnr ) )
		*mnr = FACE_MNR_NULL;

	if( flg_chk_find ){
		if( (*mjr == FACE_MJR_FLOOR) && (dep <= 0) ){
			*mjr = FACE_MJR_NULL;
			*mnr = FACE_MNR_NULL;
		}
		if( !chk_flg( flg, FLG_MAP_OBJ_FIND ) ){
			*mjr = FACE_MJR_NULL;
			*mnr = FACE_MNR_NULL;
		}
	}
}

/***************************************************************
* カーソルの属性マップから綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_crsr_attr(
	pos_t *crsr, crsr_ptn_t *ptn, long x, long y, long dx, long dy
)
{
	long	i, j;
	long	xx, yy;
	curs_attr_n_t	attr_n;
	curs_attr_t	*attr_dflt;

	if( crsr == NULL )
		return;
	if( ptn == NULL )
		return;
	if( !clip_pos( crsr->x, crsr->y ) )
		return;

	if( (crsr->x + ptn->x + ptn->x_len - 1) < x )
		return;
	if( (crsr->y + ptn->y + ptn->y_len - 1) < y )
		return;
	if( (crsr->x + ptn->x) > (x + dx - 1) )
		return;
	if( (crsr->y + ptn->y) > (y + dy - 1) )
		return;

	attr_dflt = get_curs_attr();
	attr_n = CURS_ATTR_N_MAP_CRSR;
	for( i = 0; i < ptn->y_len; i++ ){
		yy = crsr->y + ptn->y + i;
		if( !clip_y( yy ) )
			continue;

		for( j = 0; j < ptn->x_len; j++ ){
			long	c;

			xx = crsr->x + ptn->x + j;
			if( !clip_x( xx ) )
				continue;

			c = ptn->face[i][j * 2 + 0];
			if( c != ptn->transmit_chr )
				dun.map.attr[yy][xx] = attr_dflt[attr_n];

			c = ptn->face[i][j * 2 + 1];
			if( c != ptn->transmit_chr )
				dun.map.attr[yy][xx] = attr_dflt[attr_n];
		}
	}
}

/***************************************************************
* オブジェクトのマップから綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_obj( long x, long y, long dx, long dy )
{
	long	i, j;
	long	xx, yy;
	char	mjr, mnr;
	flg_map_t	flg;
	long	dep;
	curs_attr_n_t	attr_n;
	curs_attr_t	*attr_dflt;

	attr_dflt = get_curs_attr();

	for( i = 0; i < dy; i++ ){
		yy = y + i;
		if( !clip_y( yy ) )
			continue;

		for( j = 0; j < dx; j++ ){
			xx = x + j;
			if( !clip_x( xx ) )
				continue;

			mjr = dun.map.obj.mjr[yy][xx];
			mnr = dun.map.obj.mnr[yy][xx];
			flg = dun.map.obj.flg[yy][xx];
			dep = calc_light_depth( xx, yy );

			if( mjr == FACE_MJR_FLOOR )
				continue;
			if( mjr == FACE_MJR_WALL )
				continue;
			if( mjr == FACE_MJR_WATER )
				continue;
			if( chk_flg( flg, FLG_MAP_OBJ_LOOK_WALL ) )
				continue;
			if( chk_flg( flg, FLG_MAP_OBJ_LOOK_FLOOR ) )
				continue;
			if( (mjr == FACE_MJR_FLOOR) && (dep <= 0) )
				continue;
			if( !chk_flg( flg, FLG_MAP_OBJ_FIND ) )
				continue;

			attr_n = get_curs_attr_n_map_obj(
					mjr, mnr, FLG_NULL );

			dun.map.total.mjr[yy][xx] = mjr;
			dun.map.total.mnr[yy][xx] = mnr;
			dun.map.total.flg[yy][xx] = FLG_NULL;
			dun.map.attr[yy][xx] = attr_dflt[attr_n];
		}
	}
}

/***************************************************************
* アンカーのマップから綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_square( long x, long y, long dx, long dy )
{
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		set_map_total_square_n( i, x, y, dx, dy );
}

/***************************************************************
* アンカーのマップから綜合レイヤーを更新する
* long mbr_n : メンバー番号
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_square_n(
	long mbr_n, long x, long y, long dx, long dy
)
{
	long	sq_x, sq_y;
	party_t	*pty;
	curs_attr_t	*attr_dflt;

	get_square_mbr_map_pos( mbr_n, &sq_x, &sq_y );
	if( !clip_pos( sq_x, sq_y ) )
		return;
	if( sq_x < x )
		return;
	if( sq_y < y )
		return;
	if( sq_x > (x + dx - 1) )
		return;
	if( sq_y > (y + dy - 1) )
		return;

	pty = get_party();
	dun.map.total.mjr[sq_y][sq_x] = FACE_MJR_SQUARE;
	if( chk_flg( pty->mbr[mbr_n]->stat, FLG_STAT_NOT_EXIST ) )
		dun.map.total.mnr[sq_y][sq_x] = FACE_MNR_NULL;
	else
		dun.map.total.mnr[sq_y][sq_x] = pty->mbr[mbr_n]->face.mnr;

	attr_dflt = get_curs_attr();
	dun.map.attr[sq_y][sq_x] = attr_dflt[CURS_ATTR_N_MAP_SQUARE];
}

/***************************************************************
* モンスターとメンバーのマップから綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_chr( long x, long y, long dx, long dy )
{
	long	bx, by;
	long	ex, ey;
	long	xx, yy;

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
			set_map_total_chr_1( xx, yy );
		}
	}
}

/***************************************************************
* モンスターとメンバーのマップから綜合レイヤーを更新する (1 キャラ)
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	set_map_total_chr_1( long x, long y )
{
	char	mjr, mnr;
	flg_map_t	flg, flg_total;
	bool_t	flg_rev_rev;
	chr_t	*chr_p;
	curs_attr_n_t	attr_n;
	curs_attr_t	*attr_dflt;

	attr_dflt = get_curs_attr();

	flg_total = dun.map.total.flg[y][x];

	mjr = dun.map.chr.mjr[y][x];
	mnr = dun.map.chr.mnr[y][x];
	flg = dun.map.chr.flg[y][x];
	chr_p = dun.map.chr_p[y][x];
	attr_n = CURS_ATTR_N_NORMAL;
	flg_rev_rev = FALSE;

	if( mjr == FACE_MJR_NULL ){
		return;
	} else if( chr_p == NULL ){
		return;
	} else if( is_mbr( chr_p ) ){
		mbr_t	*p;

		/* メンバーだったら */

		p = get_mbr( x, y );
		if( p != NULL ){
			attr_n = (curs_attr_n_t)
					(CURS_ATTR_N_MBR_1 + p->mbr_n);
		}
		/* 透明なら */
		if( chk_flg( flg, FLG_MAP_CHR_INVISIBLE ) ){
			flg_rev_rev = TRUE;
		}
	} else if( is_pet( chr_p ) ){
		pet_t	*p;

		/* ペットだったら */

		p = get_pet( x, y );
		if( p != NULL )
			attr_n = CURS_ATTR_N_MAP_PET;
		/* 透明なら */
		if( chk_flg( flg, FLG_MAP_CHR_INVISIBLE ) )
			flg_rev_rev = TRUE;
	} else if( chr_p->kind == CHR_KIND_MNSTR ){
		/* モンスターだったら */

		/* 見つかっていなければ */
		if( !chk_flg( flg, FLG_MAP_CHR_FIND ) )
			return;
		/* 透明なら */
		if( chk_flg( flg, FLG_MAP_CHR_INVISIBLE ) )
			return;

		if( chk_flg( flg, FLG_MAP_CHR_NPC ) ){
			attr_n = CURS_ATTR_N_MAP_NPC;
		} else {
			attr_n = CURS_ATTR_N_MAP_MNSTR;
		}
	} else {
		return;
	}

	dun.map.total.mjr[y][x] = mjr;
	dun.map.total.mnr[y][x] = mnr;
	dun.map.total.flg[y][x] = flg_total;
	dun.map.attr[y][x] = attr_dflt[attr_n];
	if( flg_rev_rev )
		dun.map.attr[y][x].attr ^= A_REVERSE;
}

/***************************************************************
* カーソルのパターンのマップから綜合レイヤーを更新する
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
***************************************************************/

void	set_map_total_crsr_ptn(
	pos_t *crsr, crsr_ptn_t *ptn,
	long x, long y, long dx, long dy
)
{
	long	i, j;
	long	xx, yy;

	if( crsr == NULL )
		return;
	if( ptn == NULL )
		return;
	if( !clip_pos( crsr->x, crsr->y ) )
		return;

	if( (crsr->x + ptn->x + ptn->x_len - 1) < x )
		return;
	if( (crsr->y + ptn->y + ptn->y_len - 1) < y )
		return;
	if( (crsr->x + ptn->x) > (x + dx - 1) )
		return;
	if( (crsr->y + ptn->y) > (y + dy - 1) )
		return;

	for( i = 0; i < ptn->y_len; i++ ){
		yy = crsr->y + ptn->y + i;
		if( !clip_y( yy ) )
			continue;

		for( j = 0; j < ptn->x_len; j++ ){
			long	c;

			xx = crsr->x + ptn->x + j;
			if( !clip_x( xx ) )
				continue;

			/* 下に有るアトリビュートで描画する */

			c = ptn->face[i][j * 2 + 0];
			if( c == '\0' )
				break;
			if( c != ptn->transmit_chr )
				dun.map.total.mjr[yy][xx] = (char)c;

			c = ptn->face[i][j * 2 + 1];
			if( c == '\0' )
				break;
			if( c != ptn->transmit_chr )
				dun.map.total.mnr[yy][xx] = (char)c;
		}
	}
}

/***************************************************************
* オブジェクトの描画モードを返す
* char mjr : メジャーの顔文字
* char mnr : マイナーの顔文字
* flg_map_t flg : マップ・フラグ
* return : 描画モード
***************************************************************/

curs_attr_n_t	get_curs_attr_n_map_obj(
	char mjr, char mnr, flg_map_t flg
)
{
	if( chk_flg( flg, FLG_MAP_OBJ_LOOK_FLOOR ) )
		return CURS_ATTR_N_MAP_FLOOR;
	if( chk_flg( flg, FLG_MAP_OBJ_LOOK_WALL ) )
		return CURS_ATTR_N_MAP_WALL;

	switch( mjr ){
	case FACE_MJR_WALL:
		switch( mnr ){
		case FACE_MNR_WALL:
		case FACE_MNR_STATUE:
			return CURS_ATTR_N_MAP_WALL;
		case FACE_MNR_STREETLAMP:
			return CURS_ATTR_N_MAP_ITEM_LIGHT;
		case FACE_MNR_BOOT_UNIT:
			return CURS_ATTR_N_MAP_NPC;
		}
		return CURS_ATTR_N_MAP_WALL;
	case FACE_MJR_FLOOR:
		switch( mnr ){
		case FACE_MNR_FLOOR:
		case FACE_MNR_HOLE:
			return CURS_ATTR_N_MAP_FLOOR;
		}
		return CURS_ATTR_N_MAP_FLOOR;
	case FACE_MJR_WATER:
		switch( mnr ){
		case FACE_MNR_PUDDLE:
		case FACE_MNR_SHALLOWS:
		case FACE_MNR_OFFING:
			return CURS_ATTR_N_COLD;
		case FACE_MNR_LAVA:
			return CURS_ATTR_N_HEAT;
		}
		return CURS_ATTR_N_COLD;
	case FACE_MJR_MOUNTAIN:
		switch( mnr ){
		case FACE_MNR_MOUNTAIN:
		case FACE_MNR_HILL:
			return CURS_ATTR_N_ACID;
		}
		return CURS_ATTR_N_ACID;
	case FACE_MJR_DOOR_CLOSE:
	case FACE_MJR_DOOR_OPEN:
		switch( mnr ){
		case FACE_MNR_DOOR_NORM:
		case FACE_MNR_DOOR_JAMMED:
		case FACE_MNR_DOOR_BROKEN:
		case FACE_MNR_DOOR_SECRET:
		case FACE_MNR_GATE:
		case FACE_MNR_SHOP_INN:
		case FACE_MNR_SHOP_BAR:
		case FACE_MNR_SHOP_WPN:
		case FACE_MNR_SHOP_ARMOR:
		case FACE_MNR_SHOP_MAGIC:
		case FACE_MNR_SHOP_TEMPLE:
		case FACE_MNR_SHOP_ALCHEMY:
		case FACE_MNR_SHOP_MUSIC:
		case FACE_MNR_SHOP_GROCERY:
		case FACE_MNR_SHOP_RESTAURANT:
		case FACE_MNR_SHOP_TEAROOM:
		case FACE_MNR_SHOP_TOBACCO:
		case FACE_MNR_SHOP_PET_SHOP:
		case FACE_MNR_WINDOW:
			return CURS_ATTR_N_MAP_DOOR;
		}
		return CURS_ATTR_N_MAP_DOOR;
	case FACE_MJR_STAIRS_UP:
	case FACE_MJR_STAIRS_DOWN:
		switch( mnr ){
		case FACE_MNR_NULL:
		case FACE_MNR_STAIRS_UP:
		case FACE_MNR_STAIRS_DOWN:
		case FACE_MNR_STAIRS_LAST_BOSS:
			return CURS_ATTR_N_MAP_STAIRS;
		}
		return CURS_ATTR_N_MAP_STAIRS;
	case FACE_MJR_TRAP:
		switch( mnr ){
		case FACE_MNR_NULL:
		case FACE_MNR_TRAP_SLEEP:
		case FACE_MNR_TRAP_ARW:
		case FACE_MNR_TRAP_POISON_DARTS:
		case FACE_MNR_TRAP_BOMB:
		case FACE_MNR_TRAP_TELEPORT_PARTY:
		case FACE_MNR_TRAP_TELEPORT:
		case FACE_MNR_TRAP_PIT:
		case FACE_MNR_TRAP_CHUTE:
			return CURS_ATTR_N_MAP_TRAP;
		case FACE_MNR_TRAP_SANCTUARY:
			return CURS_ATTR_N_FX_MBR_PLUS;
		}
		return CURS_ATTR_N_MAP_TRAP;
	case FACE_MJR_SQUARE:
		return CURS_ATTR_N_MAP_SQUARE;

	case FACE_MJR_WEAPON:
		return CURS_ATTR_N_MAP_ITEM_WPN;
	case FACE_MJR_ARMOR:
		return CURS_ATTR_N_MAP_ITEM_ARMOR;
	case FACE_MJR_POTION:
		return CURS_ATTR_N_MAP_ITEM_POTION;
	case FACE_MJR_SCROLL:
		return CURS_ATTR_N_MAP_ITEM_SCROLL;
	case FACE_MJR_STICK:
		return CURS_ATTR_N_MAP_ITEM_STICK;
	case FACE_MJR_ACCESSORY:
		return CURS_ATTR_N_MAP_ITEM_ACCE;
	case FACE_MJR_FOOD:
		return CURS_ATTR_N_MAP_ITEM_FOOD;
	case FACE_MJR_CHEST:
		return CURS_ATTR_N_MAP_ITEM_CHEST;
	case FACE_MJR_COIN:
	case FACE_MJR_GEM:
		return CURS_ATTR_N_MAP_ITEM_COIN;

	case FACE_MJR_MISC:
		switch( mnr ){
		case FACE_MNR_LIGHT:
			return CURS_ATTR_N_MAP_ITEM_LIGHT;
		case FACE_MNR_SPIKE:
			return CURS_ATTR_N_MAP_ITEM_SPIKE;
		case FACE_MNR_RARE_GOODS:
			return CURS_ATTR_N_MAP_ITEM_RARE_GOODS;
		case FACE_MNR_BONE_GOOD:
		case FACE_MNR_BONE_EVIL:
			return CURS_ATTR_N_MAP_ITEM_BONE;
		case FACE_MNR_JUNK:
		case FACE_MNR_TOBACCO:
		case FACE_MNR_PIPE:
		case FACE_MNR_DISPOSAL:
			return CURS_ATTR_N_MAP_ITEM_JUNK;
		case FACE_MNR_ANTHOLOGY:
		case FACE_MNR_INST:
		case FACE_MNR_INST_STRINGED:
		case FACE_MNR_INST_WOODWIND:
		case FACE_MNR_INST_BRASS:
		case FACE_MNR_INST_PERCUSSION:
		case FACE_MNR_INST_MISC:
			return CURS_ATTR_N_MAP_ITEM_INST;
		}
		return CURS_ATTR_N_MAP_NORMAL;
	}

	return CURS_ATTR_N_MAP_NORMAL;
}

/***************************************************************
* 線状に通路を生成
* long x1 : 始点 X 座標
* long y1 : 始点 Y 座標
* long x2 : 終点 X 座標
* long y2 : 終点 Y 座標
* sect_t sect : セクション文字
***************************************************************/

void	line_path( long x1, long y1, long x2, long y2, sect_t sect )
{
	long	i;

	if( y1 == y2 ){	/* 水平 */
		if( x1 > x2 ){
			long	xx;

			xx = x1;
			x1 = x2;
			x2 = xx;
		}
		for( i = x1; i <= x2; i++ ){
			put_path( i, y1, +1, 0, sect );
		}
	} else if( x1 == x2 ){	/* 垂直 */
		if( y1 > y2 ){
			long	yy;

			yy = y1;
			y1 = y2;
			y2 = yy;
		}
		for( i = y1; i <= y2; i++ ){
			put_path( x1, i, 0, +1, sect );
		}
	}
}

/***************************************************************
* 指定座標に通路を生成
* long x : X 座標
* long y : Y 座標
* long dx : 幅
* long dy : 高さ
* sect_t sect : セクション文字
***************************************************************/

void	put_path( long x, long y, long dx, long dy, sect_t sect )
{
	long	i, j;
	sect_t	dflt_sect;
	long	xx, yy;


	if( dx < 0 ){
		dflt_sect = SECT_PATH_W;
	} else if( dx > 0 ){
		dflt_sect = SECT_PATH_E;
	} else if( dy < 0 ){
		dflt_sect = SECT_PATH_N;
	} else if( dy > 0 ){
		dflt_sect = SECT_PATH_S;
	} else {
		dflt_sect = SECT_PATH_N;
	}

	if( sect == SECT_PATH_DFLT )
		sect = dflt_sect;

	for( i = 0; i < PATH_WIDTH; i++ ){
		yy = y + i;
		for( j = 0; j < PATH_WIDTH; j++ ){
			xx = x + j;
			dun.map.sect[yy][xx] = sect;

			if( dun.map.obj.mjr[yy][xx] != FACE_MJR_WALL ){
				continue;
			}

			dun.map.obj.mjr[yy][xx] = FACE_MJR_FLOOR;
			dun.map.obj.mnr[yy][xx] = FACE_MNR_FLOOR;
			dun.map.obj.flg[yy][xx] |= (FLG_MAP_OBJ_PASS
					| FLG_MAP_OBJ_LOOK);
		}
	}
}

/***************************************************************
* ドアを開ける
* long n : ドア番号
* return : ドアが開いたか?
***************************************************************/

bool_t	open_door( long n )
{
	flg_door_t	flg;

	if( n < 0 )
		return FALSE;
	if( n >= dun.door_n )
		return FALSE;

	flg = dun.door[n].flg;

	if( chk_flg_or( flg, FLG_DOOR_SECRET | FLG_DOOR_JAMMED ) )
		return FALSE;
	if( chk_flg( flg, FLG_DOOR_GATE ) )
		return FALSE;

	dun.door[n].flg |= FLG_DOOR_OPEN;
	set_face_door( n );

	draw_door( n );

	return TRUE;
}

/***************************************************************
* ドアを閉じる
* long n : ドア番号
* return : ドアが閉じたか?
***************************************************************/

bool_t	close_door( long n )
{
	flg_door_t	flg;
	long	i, j;

	if( n < 0 )
		return FALSE;
	if( n >= dun.door_n )
		return FALSE;

	flg = dun.door[n].flg;

	if( chk_flg( flg, FLG_DOOR_SECRET ) )
		return FALSE;
	if( chk_flg( flg, FLG_DOOR_OPEN ) )
		if( chk_flg_or( flg, FLG_DOOR_JAMMED | FLG_DOOR_BROKEN ) )
			return FALSE;
	if( chk_flg( flg, FLG_DOOR_GATE ) )
		return FALSE;

	/* キャラクターがドアの上にいるか */
	for( i = 0; i < dun.door[n].dy; i++ ){
		for( j = 0; j < dun.door[n].dx; j++ ){
			long	x, y;

			x = dun.door[n].x + j;
			y = dun.door[n].y + i;
			if( dun.map.chr.mjr[y][x] != FACE_MJR_NULL ){
				return FALSE;
			}
		}
	}

	dun.door[n].flg &= ~FLG_DOOR_OPEN;
	set_face_door( n );

	draw_door( n );

	return TRUE;
}

/***************************************************************
* ドアを固定
* long n : ドア番号
* return : ドアが固定できたか?
***************************************************************/

bool_t	jam_door( long n )
{
	if( n < 0 )
		return FALSE;
	if( n >= dun.door_n )
		return FALSE;

	if( chk_flg( dun.door[n].flg, FLG_DOOR_SECRET ) )
		return FALSE;
	if( chk_flg( dun.door[n].flg, FLG_DOOR_BROKEN ) ){
		print_msg( FLG_NULL, MSG_ERR_DOOR_JAM_BROKEN );
		return FALSE;
	}
	if( chk_flg( dun.door[n].flg, FLG_DOOR_JAMMED ) ){
		print_msg( FLG_NULL, MSG_ERR_DOOR_JAM_JAMMED );
		return FALSE;
	}
	if( chk_flg( dun.door[n].flg, FLG_DOOR_GATE ) )
		return FALSE;

	dun.door[n].flg |= FLG_DOOR_JAMMED;
	dun.door[n].flg |= FLG_DOOR_CHKED;
	set_face_door( n );

	draw_door( n );

	return TRUE;
}

/***************************************************************
* ドアの固定を解除
* long n : ドア番号
* return : ドアの固定を解除できたか?
***************************************************************/

bool_t	disarm_door( long n )
{
	if( n < 0 )
		return FALSE;
	if( n >= dun.door_n )
		return FALSE;

	if( chk_flg( dun.door[n].flg, FLG_DOOR_SECRET ) )
		return FALSE;
	if( chk_flg( dun.door[n].flg, FLG_DOOR_BROKEN ) ){
		print_msg( FLG_NULL, MSG_ERR_DOOR_DISARM_BROKEN );
		return FALSE;
	}
	if( !chk_flg( dun.door[n].flg, FLG_DOOR_JAMMED ) ){
		print_msg( FLG_NULL, MSG_ERR_DOOR_DISARM_NOT_JAM );
		return FALSE;
	}
	if( chk_flg( dun.door[n].flg, FLG_DOOR_GATE ) )
		return FALSE;

	dun.door[n].flg &= ~(FLG_DOOR_JAMMED);
	dun.door[n].flg |= FLG_DOOR_CHKED;
	set_face_door( n );

	draw_door( n );

	return TRUE;
}

/***************************************************************
* ドアを調べる
* long n : ドア番号
* return : ドアを調べられたか?
***************************************************************/

bool_t	srch_door( long n )
{
	if( n < 0 )
		return FALSE;
	if( n >= dun.door_n )
		return FALSE;

	dun.door[n].flg |= FLG_DOOR_CHKED;
	dun.door[n].flg &= ~(FLG_DOOR_SECRET);
	set_face_door( n );

	draw_door( n );

	return TRUE;
}

/***************************************************************
* 指定範囲のドアを調べる
* long x : X 座標
* long y : Y 座標
* long r : 半径
***************************************************************/

void	detect_door( long x, long y, long r )
{
	long	n;

	for( n = 0; n < dun.door_n; n++ ){
		if( (dun.door[n].x + dun.door[n].dx - 1) < (x - r) )
			continue;
		if( (x + r) < dun.door[n].x )
			continue;
		if( (dun.door[n].y + dun.door[n].dy - 1) < (y - r) )
			continue;
		if( (y + r) < dun.door[n].y )
			continue;

		srch_door( n );
	}
}

/***************************************************************
* 指定座標のマップを発見する
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	find_obj( long x, long y )
{
	long	i, j;
	long	sx, sy;
	flg_map_t	flg;
	long	dep;
	bool_t	flg_redraw;

	flg_redraw = FALSE;

	for( i = -1; i <= +1; i++ ){
		sy = y + i;
		if( !clip_y( sy ) )
			continue;
		for( j = -1; j <= +1; j++ ){
			sx = x + j;
			if( !clip_x( sx ) )
				continue;

			flg = dun.map.obj.flg[sy][sx];
			dep = dun.map.light_depth_obj[sy][sx];
			if( !chk_flg( flg, FLG_MAP_OBJ_FIND ) && (dep > 0) ){
				find_obj_fill( sx, sy );
				flg_redraw = TRUE;
			}
		}
	}

	if( flg_redraw )
		redraw_map();
}

/***************************************************************
* 明かりのついているセクションに入った時に、
* そのセクションを全て発見する
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	find_obj_fill( long x, long y )
{
	long	ax, ay;
	long	sx, sy;
	long	dx, dy;
	sect_t	sect;

	ax = x / AREA_MAX_X * AREA_MAX_X;
	ay = y / AREA_MAX_Y * AREA_MAX_Y;
	sect = dun.map.sect[y][x];

	for( dy = 0; dy < AREA_MAX_Y; dy++ ){
		sy = ay + dy;
		for( dx = 0; dx < AREA_MAX_X; dx++ ){
			sx = ax + dx;

			if( dun.map.sect[sy][sx] != sect )
				continue;
			if( !chk_flg( dun.map.obj.flg[sy][sx],
					FLG_MAP_OBJ_LOOK ) ){
				continue;
			}

			find_obj_fill_field( sx, sy );
		}
	}
}

/***************************************************************
* 指定セクションを発見する
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	find_obj_fill_field( long x, long y )
{
	long	i, j;
	long	sx, sy;

	for( i = -1; i <= +1; i++ ){
		sy = y + i;
		if( !clip_y( sy ) )
			continue;
		for( j = -1; j <= +1; j++ ){
			sx = x + j;
			if( !clip_x( sx ) )
				continue;

			dun.map.obj.flg[sy][sx] |= FLG_MAP_OBJ_FIND;
		}
	}
}

/***************************************************************
* エリアの明かりをつける
* long x : X 座標
* long y : Y 座標
* bool_t flg_find : 発見するか?
***************************************************************/

void	on_light_area( long x, long y, bool_t flg_find )
{
	turn_light_area( x, y, TRUE, flg_find );
}

/***************************************************************
* エリアの明かりを消す
* long x : X 座標
* long y : Y 座標
* bool_t flg_find : 発見するか?
***************************************************************/

void	off_light_area( long x, long y, bool_t flg_find )
{
	turn_light_area( x, y, FALSE, flg_find );
}

/***************************************************************
* エリアの明かりをつけたり消したりする
* long x : X 座標
* long y : Y 座標
* bool_t flg_on : つけるか消すか?
* bool_t flg_find : 発見するか?
***************************************************************/

void	turn_light_area( long x, long y, bool_t flg_on, bool_t flg_find )
{
	sect_t	sect;
	long	ax, ay;
	long	dx, dy;

	sect = dun.map.sect[y][x];

	ax = ((int)(x / AREA_MAX_X)) * AREA_MAX_X;
	ay = ((int)(y / AREA_MAX_Y)) * AREA_MAX_Y;
	for( dy = 0; dy < AREA_MAX_Y; dy++ ){
		for( dx = 0; dx < AREA_MAX_X; dx++ ){
			turn_light_field( ax + dx, ay + dy, sect,
					flg_on, flg_find );
		}
	}

	redraw_map();
}

/***************************************************************
* 指定座標の明かりをつけたり消したりする
* long x : X 座標
* long y : Y 座標
* sect_t sect : セクション文字
* bool_t flg_on : つけるか消すか?
* bool_t flg_find : 発見するか?
***************************************************************/

void	turn_light_field(
	long x, long y, sect_t sect, bool_t flg_on, bool_t flg_find
)
{
	long	dx, dy;
	long	sx, sy;
	bool_t	flg_on_depth;

	sx = 0;
	sy = 0;
	for( dy = -1; dy <= +1; dy++ ){
		sy = y + dy;
		if( !clip_y( sy ) )
			continue;

		for( dx = -1; dx <= +1; dx++ ){
			sx = x + dx;
			if( !clip_x( sx ) )
				continue;

			if( dun.map.sect[sy][sx] != sect )
				continue;

			if( !chk_flg( dun.map.obj.flg[sy][sx],
					FLG_MAP_OBJ_LOOK ) )
				continue;

			if( chk_flg( dun.map.obj.flg[sy][sx],
					FLG_MAP_OBJ_LOOK_WALL ) )
				continue;

			/**/

			flg_on_depth = turn_light_obj( x, y, flg_on );
			if( flg_on_depth && flg_find )
				dun.map.obj.flg[y][x] |= FLG_MAP_OBJ_FIND;
			return;
		}
	}
}

/***************************************************************
* ドアの明かりをつけたり消したりする
* door_t *dr : ドア
* bool_t flg_on : つけるか消すか?
* bool_t flg_find : 発見するか?
***************************************************************/

void	turn_light_door( door_t *dr, bool_t flg_on, bool_t flg_find )
{
	long	dx, dy;

	for( dy = 0; dy < dr->dy; dy++ ){
		for( dx = 0; dx < dr->dx; dx++ ){
			long	sx, sy;
			bool_t	flg_on_depth;

			sx = dr->x + dx;
			sy = dr->y + dy;

			flg_on_depth = turn_light_obj( sx, sy, flg_on );
			if( flg_on_depth && flg_find )
				dun.map.obj.flg[sy][sx] |= FLG_MAP_OBJ_FIND;
		}
	}

	draw_door( dr->n );
}

/***************************************************************
* 固定オブジェクトによる明かりをつけたり消したりする
* long x : X 座標
* long y : Y 座標
* bool_t flg_on : つけるか消すか?
* return : 明るくなったか?
***************************************************************/

bool_t	turn_light_obj( long x, long y, bool_t flg_on )
{
	if( flg_on )
		dun.map.light_depth_obj[y][x]++;
	else
		dun.map.light_depth_obj[y][x]--;

	return( dun.map.light_depth_obj[y][x] > 0 );
}

/***************************************************************
* キャラクタによる明かりをつけたり消したりする
* long x : X 座標
* long y : Y 座標
* bool_t flg_on : つけるか消すか?
* return : 明るくなったか?
***************************************************************/

bool_t	turn_light_chr( long x, long y, bool_t flg_on )
{
	if( flg_on )
		dun.map.light_depth_chr[y][x]++;
	else
		dun.map.light_depth_chr[y][x]--;

	return( dun.map.light_depth_chr[y][x] > 0 );
}

/***************************************************************
* 指定座標の明るさの深さを調べる
* long x : X 座標
* long y : Y 座標
* return : 明るさの深さ
***************************************************************/

long	calc_light_depth( long x, long y )
{
	long	depth;

	depth = 0;
	depth += dun.map.light_depth_obj[y][x];
	depth += dun.map.light_depth_chr[y][x];

	return depth;
}

/***************************************************************
* 2点間の視線が通っているか（見えているか）調べる
* pos_t *pos1 : 始点座標
* pos_t *pos2 : 終点座標
* return : 視線が通っているか?
***************************************************************/

bool_t	chk_find( pos_t *pos1, pos_t *pos2 )
{
	long	x1, y1, x2, y2, e;
	long	dx2, dy2, sgn_y;
	long	x, y;

	if( pos1->x < pos2->x ){
		x1 = pos1->x;
		y1 = pos1->y;
		x2 = pos2->x;
		y2 = pos2->y;
	} else {
		x1 = pos2->x;
		y1 = pos2->y;
		x2 = pos1->x;
		y2 = pos1->y;
	}

	dx2 = 2 * (x2 - x1);
	dy2 = 2 * labs( y2 - y1 );
	if( y1 <= y2 )
		sgn_y = +1;
	else
		sgn_y = -1;
	e = -(x2 - x1);
	x = x1;
	y = y1;

	for( ; x <= x2; x++ ){
		if( e < 0 ){
			if( !chk_find_pos( x, y ) )
				return FALSE;
		} else {
			do {
				y += sgn_y;
				if( sgn_y >= +1 ){
					if( y > y2 )
						break;
				} else {
					if( y < y2 )
						break;
				}
				e -= dx2;
				if( !chk_find_pos( x, y ) )
					return FALSE;
			} while( e >= 0 );
		}
		e += dy2;
	}

	return TRUE;
}

/***************************************************************
* 視線が通るか（見えるか）調べる
* long x : X 座標
* long y : Y 座標
* return : 視線が通るか?
***************************************************************/

bool_t	chk_find_pos( long x, long y )
{
	if( !clip_pos( x, y ) )
		return FALSE;

	if( chk_flg( dun.map.obj.flg[y][x], FLG_MAP_OBJ_LOOK ) )
		return TRUE;

	return FALSE;
}

/***************************************************************
* 迷宮のデータを返す
* return : 迷宮のデータ
***************************************************************/

dun_t	*get_dun( void )
{
	return &dun;
}

/***************************************************************
* 迷宮の現在の階層を返す
* return : 現在の階層
***************************************************************/

long	get_dun_lev( void )
{
	return dun.lev;
}

/***************************************************************
* 指定座標にあるドアのデータを返す
* long x : X 座標
* long y : Y 座標
* return : ドアのデータ
***************************************************************/

door_t	*get_door( long x, long y )
{
	long	i;
	door_t	*dr;

	if( !clip_pos( x, y ) )
		return NULL;

	for( i = 0; i < dun.door_n; i++ ){
		dr = &(dun.door[i]);
		if( x < dr->x )
			continue;
		if( x > dr->x + dr->dx - 1 )
			continue;
		if( y < dr->y )
			continue;
		if( y > dr->y + dr->dy - 1 )
			continue;
		if( dun.map.obj.mjr[y][x] != dr->mjr )
			continue;
		if( dun.map.obj.mnr[y][x] != dr->mnr )
			continue;

		return dr;
	}

	return NULL;
}

/***************************************************************
* 指定座標に1番近いドアのデータを返す
* long x : X 座標
* long y : Y 座標
* act_kind_t act_kind : ドアに対するアクション
* return : ドアのデータ
***************************************************************/

door_t	*get_door_nearest( long x, long y, act_kind_t act_kind )
{
	long	dr_n;
	door_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( dr_n = 0; dr_n < dun.door_n; dr_n++ ){
		pos_t	pos1, pos2;
		long	dx, dy;

		p = &(dun.door[dr_n]);

		if( !chk_mark_door( p, act_kind ) )
			continue;
		if( !chk_find_door( dr_n ) )
			continue;

		set_door_pos_chk_find( p, x, y, &pos1, &dx, &dy );
		tmp_r = dx + dy;
		if( tmp_r > min_r )
			continue;

		pos2.x = x;
		pos2.y = y;
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
* 指定座標になるべく近いドアのデータを返す
* long x : X 座標
* long y : Y 座標
* act_kind_t act_kind : ドアに対するアクション
* return : ドアのデータ
***************************************************************/

door_t	*get_door_near( long x, long y, act_kind_t act_kind )
{
	long	dr_n;
	door_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( dr_n = 0; dr_n < dun.door_n; dr_n++ ){
		pos_t	pos1, pos2;
		long	dx, dy;

		p = &(dun.door[dr_n]);

		if( !chk_mark_door( p, act_kind ) )
			continue;
		if( !chk_find_door( dr_n ) )
			continue;

		set_door_pos_chk_find( p, x, y, &pos1, &dx, &dy );
		tmp_r = dx + dy;

		pos2.x = x;
		pos2.y = y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( tmp_r < min_r ){
			n = 0;
			min_r = tmp_r;
		} else if( (tmp_r - min_r) <= DOOR_NEAR_R ){
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/***************************************************************
* パーティ内で、ばらけたドアのデータを返す
* mbr_t *mbr : メンバー
* act_kind_t act_kind : ドアに対するアクション
* return : ドアのデータ
***************************************************************/

door_t	*get_door_disperse( mbr_t *mbr, act_kind_t act_kind )
{
	long	dr_n;
	door_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	long	x, y;

	x = mbr->x;
	y = mbr->y;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( dr_n = 0; dr_n < dun.door_n; dr_n++ ){
		pos_t	pos1, pos2;
		long	dx, dy;

		p = &(dun.door[dr_n]);

		if( !chk_mark_door( p, act_kind ) )
			continue;
		if( !chk_find_door( dr_n ) )
			continue;

		set_door_pos_chk_find( p, x, y, &pos1, &dx, &dy );
		tmp_r = dx + dy;
		if( tmp_r > min_r )
			continue;

		if( chk_already_mark( p, mbr ) )
			continue;
		pos2.x = x;
		pos2.y = y;
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
* 見えている範囲内で、ランダムにドアのデータを返す
* long x : X 座標
* long y : Y 座標
* act_kind_t act_kind : ドアに対するアクション
* return : ドアのデータ
***************************************************************/

door_t	*get_door_randm( long x, long y, act_kind_t act_kind )
{
	long	dr_n;
	door_t	*p, *ret_p;
	long	n;

	ret_p = NULL;
	n = 0;
	for( dr_n = 0; dr_n < dun.door_n; dr_n++ ){
		pos_t	pos1, pos2;
		long	dx, dy;

		p = &(dun.door[dr_n]);

		if( !chk_mark_door( p, act_kind ) )
			continue;
		if( !chk_find_door( dr_n ) )
			continue;

		set_door_pos_chk_find( p, x, y, &pos1, &dx, &dy );

		pos2.x = x;
		pos2.y = y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		n++;
		if( randm( n ) == 0 )
			ret_p = p;
	}

	return ret_p;
}

/***************************************************************
* 街の住民に近い、ランダムなドアのデータを返す
* long x : X 座標
* long y : Y 座標
* long r : 半径
* return : ドアのデータ
***************************************************************/

door_t	*get_door_towner( long x, long y, long r )
{
	door_t	*ret, *dr;
	long	n;
	long	xx, yy;
	long	dx, dy;
	char	mjr;

	ret = NULL;
	n = 0;
	for( dy = -r; dy <= +r; dy++ ){
		yy = y + dy;
		if( !clip_y( yy ) )
			continue;

		for( dx = -r; dx <= +r; dx++ ){
			xx = x + dx;
			if( !clip_x( xx ) )
				continue;

			mjr = dun.map.obj.mjr[yy][xx];
			if( mjr != FACE_MJR_DOOR_OPEN )
				if( mjr != FACE_MJR_DOOR_CLOSE )
					continue;

			dr = get_door( xx, yy );
			if( dr != NULL ){
				n++;
				if( per_randm( n ) ){
					ret = dr;
				}
			}
		}
	}

	return ret;
}

/***************************************************************
* 指定のドアと座標から視線チェックに使う座標と距離を返す
* door_t *p : ドア
* long x : 視点の x 座標
* long y : 視点の y 座標
* pos_t *pos : 視線チェックに使う座標を返す
* long *dx : x 方向の距離を返す
* long *dy : y 方向の距離を返す
***************************************************************/

void	set_door_pos_chk_find(
	door_t *p, long x, long y, pos_t *pos, long *dx, long *dy
)
{
	if( p == NULL )
		return;
	if( pos == NULL )
		return;
	if( dx == NULL )
		return;
	if( dy == NULL )
		return;

	if( p->x > x ){
		*dx = labs( p->x - x );
		pos->x = p->x - 1;
	} else if( (p->x + p->dx - 1) < x ){
		*dx = labs( x - (p->x + p->dx - 1) );
		pos->x = p->x + p->dx - 1 + 1;
	} else {
		*dx = labs( p->x - x );
		pos->x = x;
	}

	if( p->y > y ){
		*dy = labs( p->y - y );
		pos->y = p->y - 1;
	} else if( (p->y + p->dy - 1) < y ){
		*dy = labs( y - (p->y + p->dy - 1) );
		pos->y = p->y + p->dy - 1 + 1;
	} else {
		*dy = labs( p->y - y );
		pos->y = y;
	}
}

/***************************************************************
* 指定のドアに対して、アクションが実行可能か調べる
* door_t *p : ドア
* act_kind_t act_kind : ドアに対するアクション
* return : アクションが実行可能か?
***************************************************************/

bool_t	chk_mark_door( door_t *p, act_kind_t act_kind )
{
	switch( act_kind ){
	case ACT_KIND_DOOR_OPEN:
		if( chk_flg( p->flg, FLG_DOOR_OPEN ) )
			return FALSE;
		break;
	case ACT_KIND_DOOR_CLOSE:
		if( !chk_flg( p->flg, FLG_DOOR_OPEN ) )
			return FALSE;
		break;
	case ACT_KIND_DOOR_JAM:
		if( chk_flg( p->flg, FLG_DOOR_JAMMED ) )
			return FALSE;
		break;
	case ACT_KIND_DOOR_DISARM:
		if( !chk_flg( p->flg, FLG_DOOR_CHKED ) )
			break;
		if( !chk_flg( p->flg, FLG_DOOR_JAMMED ) )
			return FALSE;
		break;
	case ACT_KIND_DOOR_BREAK:
		if( chk_flg( p->flg, FLG_DOOR_BROKEN ) )
			return FALSE;
		break;
	case ACT_KIND_DOOR_PEEP:
		if( chk_flg( p->flg, FLG_DOOR_OPEN ) )
			return FALSE;
		break;
	case ACT_KIND_DOOR_CHK:
		if( chk_flg( p->flg, FLG_DOOR_CHKED ) )
			return FALSE;
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* 階段を上る
* return : 上がれたか?
***************************************************************/

bool_t	up_stairs( void )
{
	if( !chk_party_no_mbr( FALSE ) )
		return FALSE;

	if( !chk_stairs( FACE_MJR_STAIRS_UP ) ){
		print_msg( FLG_NULL, MSG_ERR_STAIRS_UP );
		return FALSE;
	}

	call_game_sound_play( SOUND_KIND_STAIRS_UP, 1 );

	print_msg( FLG_NULL, MSG_UP_DUN );
	up_dun( +1 );

	return TRUE;
}

/***************************************************************
* 階段を下る
* return : 下れたか?
***************************************************************/

bool_t	down_stairs( void )
{
	if( !chk_party_no_mbr( FALSE ) )
		return FALSE;

	if( !chk_stairs( FACE_MJR_STAIRS_DOWN ) ){
		print_msg( FLG_NULL, MSG_ERR_STAIRS_DOWN );
		return FALSE;
	}

	call_game_sound_play( SOUND_KIND_STAIRS_DOWN, 1 );

	print_msg( FLG_NULL, MSG_DOWN_DUN );
	up_dun( -1 );

	return TRUE;
}

/***************************************************************
* ラスボスへの階段を下る
* return : 下れたか?
***************************************************************/

bool_t	down_stairs_last_boss( void )
{
	if( !chk_party_no_mbr( FALSE ) )
		return FALSE;

	if( !chk_stairs( FACE_MNR_STAIRS_LAST_BOSS ) ){
		print_msg( FLG_NULL, MSG_ERR_STAIRS_DOWN );
		return FALSE;
	}

	if( !chk_enter_last_stage() ){
		print_msg( FLG_NULL, MSG_ERR_STAIRS_DOWN_LAST_BOSS_1 );
		print_msg( FLG_NULL, MSG_ERR_STAIRS_DOWN_LAST_BOSS_2 );
		return FALSE;
	}

	print_msg( FLG_NULL, MSG_DOWN_DUN );
	enter_last_boss_dun();

	return TRUE;
}

/***************************************************************
* 階段を上り下り出来るか調べる
* long face : 階段の種類の顔文字
* return : 上り下り出来るか?
***************************************************************/

bool_t	chk_stairs( long face )
{
	char	mjr, mnr;
	party_t	*pty;
	bool_t	flg;
	long	i;
	long	x, y;

	if( face == FACE_MNR_STAIRS_LAST_BOSS ){
		mjr = FACE_MJR_STAIRS_LAST_BOSS;
		mnr = FACE_MNR_STAIRS_LAST_BOSS;
	} else if( (face == FACE_MJR_STAIRS_DOWN)
			|| (face == FACE_MNR_STAIRS_DOWN) ){
		mjr = FACE_MJR_STAIRS_DOWN;
		mnr = FACE_MNR_STAIRS_DOWN;
	} else {
		mjr = FACE_MJR_STAIRS_UP;
		mnr = FACE_MNR_STAIRS_UP;
	}

	pty = get_party();

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		flg = FALSE;
		for( y = -STAIRS_MAX_R; y <= +STAIRS_MAX_R; y++ ){
			for( x = -STAIRS_MAX_R; x <= +STAIRS_MAX_R; x++ ){
				long	mx, my;

				mx = pty->mbr[i]->x + x;
				my = pty->mbr[i]->y + y;
				if( dun.map.obj.mjr[my][mx] != mjr )
					continue;
				if( dun.map.obj.mnr[my][mx] != mnr )
					continue;

				flg = TRUE;
				break;
			}
		}
		if( !flg )
			return FALSE;
	}

	return TRUE;
}

/***************************************************************
* マップをスクロール
* long x : 視点の x 座標
* long y : 視点の y 座標
***************************************************************/

void	scroll_map( long x, long y )
{
	pos_t	*draw;

	draw = get_map_draw_pos();
	draw->x = x;
	draw->y = y;

	chk_scroll( TRUE );
	redraw_map();
}

/***************************************************************
* 顔文字を指定してマップを検索
* char face_mjr : メジャーの顔文字
* char face_mnr : マイナーの顔文字
* long *x : 開始 X 座標 - 1 を指定する。X 座標を返す。
* long *y : 開始 Y 座標を指定する。Y 座標を返す。
* return : 見つかったか?
***************************************************************/

bool_t	srch_map_obj( char face_mjr, char face_mnr, long *x, long *y )
{
	long	xx, yy;

	if( (*x == MAP_DEL_X) || (*y == MAP_DEL_Y) ){
		xx = 0;
		yy = 0;
	} else {
		xx = *x + 1;
		yy = *y;
	}

	for( ; yy < MAP_MAX_Y; yy++, xx = 0 ){
		for( ; xx < MAP_MAX_X; xx++ ){
			if( face_mjr != '\0' )
				if( dun.map.obj.mjr[yy][xx] != face_mjr )
					continue;
			if( face_mnr != '\0' )
				if( dun.map.obj.mnr[yy][xx] != face_mnr )
					continue;

			*x = xx;
			*y = yy;

			return TRUE;
		}
	}

	return FALSE;
}

/***************************************************************
* 指定座標が壁か調べる
* long x : X 座標
* long y : Y 座標
* return : 壁か?
***************************************************************/

bool_t	is_map_wall( long x, long y )
{
	if( !clip_x( x ) )
		return TRUE;
	if( !clip_y( y ) )
		return TRUE;
	if( dun.map.obj.mjr[y][x] == FACE_MJR_WALL )
		return TRUE;
	if( chk_flg( dun.map.obj.flg[y][x], FLG_MAP_OBJ_LOOK_WALL ) )
		return TRUE;

	return FALSE;
}

/***************************************************************
* 指定座標がマップの有効範囲内か調べる
* long x : X 座標
* long y : Y 座標
* return : マップの有効範囲内か?
***************************************************************/

bool_t	clip_pos( long x, long y )
{
	if( !clip_x( x ) )
		return FALSE;
	if( !clip_y( y ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 指定の X 座標がマップの有効範囲内か調べる
* long n : X 座標
* return : マップの有効範囲内か?
***************************************************************/

bool_t	clip_x( long n )
{
	if( n == MAP_DEL_X )
		return FALSE;
	if( n < 0 )
		return FALSE;
	if( n >= MAP_MAX_X )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 指定の Y 座標がマップの有効範囲内か調べる
* long n : Y 座標
* return : マップの有効範囲内か?
***************************************************************/

bool_t	clip_y( long n )
{
	if( n == MAP_DEL_Y )
		return FALSE;
	if( n < 0 )
		return FALSE;
	if( n >= MAP_MAX_Y )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 指定座標がマップの表示範囲内か調べる
* long x : X 座標
* long y : Y 座標
* return : マップの表示範囲内か?
***************************************************************/

bool_t	clip_draw_pos( long x, long y )
{
	if( !clip_draw_x( x ) )
		return FALSE;
	if( !clip_draw_y( y ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 指定の X 座標がマップの表示範囲内か調べる
* long n : X 座標
* return : マップの表示範囲内か?
***************************************************************/

bool_t	clip_draw_x( long n )
{
	pos_t	*draw;

	if( n == MAP_DEL_X )
		return FALSE;

	if( g_flg_cui ){
		draw = get_map_draw_pos();
		if( (n <= (draw->x + (get_map_col() / 2) - 1))
				&& (draw->x <= n) ){
			return TRUE;
		}
	}
	if( g_flg_gui ){
		if( call_pcg_dun_clip_win_x( n, FALSE ) )
			return TRUE;
	}

	return FALSE;
}

/***************************************************************
* 指定の Y 座標がマップの表示範囲内か調べる
* long n : Y 座標
* return : マップの表示範囲内か?
***************************************************************/

bool_t	clip_draw_y( long n )
{
	pos_t	*draw;

	if( n == MAP_DEL_Y )
		return FALSE;

	if( g_flg_cui ){
		draw = get_map_draw_pos();
		if( (n <= (draw->y + get_map_row() - 1))
				&& (draw->y <= n) ){
			return TRUE;
		}
	}
	if( g_flg_gui ){
		if( call_pcg_dun_clip_win_y( n, FALSE ) )
			return TRUE;
	}

	return FALSE;
}

/***************************************************************
* エリアを部屋にするか通路にするかランダムで決める
* long dun_lev : 迷宮の階層
* return : 部屋にするか?
***************************************************************/

bool_t	chk_rate_room( long dun_lev )
{
	return rate_randm( RATE_ROOM );
}

/***************************************************************
* ドアを開くか閉じるかランダムで決める
* long dun_lev : 迷宮の階層
* return : ドアを開くか?
***************************************************************/

bool_t	chk_rate_door_open( long dun_lev )
{
	return rate_randm( RATE_DOOR_OPEN );
}

/***************************************************************
* ドアを固定するかランダムで決める
* long dun_lev : 迷宮の階層
* return : ドアを固定するか?
***************************************************************/

bool_t	chk_rate_door_jammed( long dun_lev )
{
	return rate_randm( RATE_DOOR_JAMMED );
}

/***************************************************************
* ドアを壊すかランダムで決める
* long dun_lev : 迷宮の階層
* return : ドアを壊すか?
***************************************************************/

bool_t	chk_rate_door_broken( long dun_lev )
{
	return rate_randm( RATE_DOOR_BROKEN );
}

/***************************************************************
* ドアを隠すかランダムで決める
* long dun_lev : 迷宮の階層
* return : ドアを隠すか?
***************************************************************/

bool_t	chk_rate_door_secret( long dun_lev )
{
	return rate_randm( labs( dun_lev ) * 4 );
}

/***************************************************************
* 十字路のドアを隠すかランダムで決める
* long dun_lev : 迷宮の階層
* return : ドアを隠すか?
***************************************************************/

bool_t	chk_rate_hide_cross_path( long dun_lev )
{
	return rate_randm( RATE_HIDE_CROSS_PATH );
}

/***************************************************************
* カーソル位置のキャラクタ・レイヤーのメジャー顔文字を返す
* return : メジャーの顔文字
***************************************************************/

char	get_chr_mjr_crsr( void )
{
	return get_chr_crsr( TRUE );
}

/***************************************************************
* カーソル位置のキャラクタ・レイヤーのマイナー顔文字を返す
* return : マイナーの顔文字
***************************************************************/

char	get_chr_mnr_crsr( void )
{
	return get_chr_crsr( FALSE );
}

/***************************************************************
* カーソル位置のキャラクタ・レイヤーの顔文字を返す
* bool_t flg_mjr : メジャーの顔文字か?
* return : 顔文字
***************************************************************/

char	get_chr_crsr( bool_t flg_mjr )
{
	char	face;
	pos_t	*crsr = get_main_crsr();

	if( flg_mjr )
		face = FACE_MJR_NULL;
	else
		face = FACE_MNR_NULL;

	if( crsr == NULL )
		return face;

	if( !clip_x( crsr->x ) )
		return face;
	if( !clip_y( crsr->y ) )
		return face;

	if( flg_mjr )
		return( dun.map.chr.mjr[crsr->y][crsr->x] );
	else
		return( dun.map.chr.mnr[crsr->y][crsr->x] );
}

/***************************************************************
* 迷宮が変更中か調べる
* return : 変更中か?
***************************************************************/

long	chk_nest_flg_dun( void )
{
	return chk_nest_flg( g_nest_flg_dun );
}

/***************************************************************
* 迷宮関係のデータをセーブ
* return : セーブ出来たか?
***************************************************************/

bool_t	save_dun( void )
{
	if( !save_crsr_ptn( g_crsr_ptn_usr, g_crsr_ptn_max_n ) ){
		print_msg( FLG_NULL, MSG_S, MSG_ERR_SAVE_CRSR_PTN );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_dun_c( void )
{
	check_memory( check_memory_dun_c_dun,
			"dun.c: dun" );
	check_memory( check_memory_dun_c_g_room_ptn_max_n,
			"dun.c: g_room_ptn_max_n" );
	check_memory( check_memory_dun_c_g_crsr_ptn_usr,
			"dun.c: g_crsr_ptn_usr" );
	check_memory( check_memory_dun_c_g_main_crsr_ptn,
			"dun.c: g_main_crsr_ptn" );
	check_memory( check_memory_dun_c_g_sub_crsr_ptn,
			"dun.c: g_sub_crsr_ptn" );
	check_memory( check_memory_dun_c_g_main_crsr_ptn_n,
			"dun.c: g_main_crsr_ptn_n" );
	check_memory( check_memory_dun_c_g_nest_flg_dun,
			"dun.c: g_nest_flg_dun" );
}
