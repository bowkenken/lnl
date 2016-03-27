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
* $Id: town.c,v 1.166 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#define	TOWN_C
#include	"inc.h"

/***************************************************************
* 街
***************************************************************/

#define	TOWNER_AVE_N	64

#define	FLOOR_IS_FIND_NIGHT	1
#define	FLG_RESET_RESI_STAY_INN	0

/***************************************************************
* 店の営業時間
***************************************************************/

#define	OPEN_TURN_BAR	( 0 * TURN_PER_HOUR)
#define	CLOSE_TURN_BAR	(24 * TURN_PER_HOUR)
#define	OPEN_TURN_INN	( 0 * TURN_PER_HOUR)
#define	CLOSE_TURN_INN	(24 * TURN_PER_HOUR)
#define	OPEN_TURN_WPN	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_WPN	(19 * TURN_PER_HOUR)
#define	OPEN_TURN_ARMOR	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_ARMOR	(19 * TURN_PER_HOUR)
#define	OPEN_TURN_MAGIC	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_MAGIC	(19 * TURN_PER_HOUR)
#define	OPEN_TURN_TEMPLE	( 0 * TURN_PER_HOUR)
#define	CLOSE_TURN_TEMPLE	(24 * TURN_PER_HOUR)
#define	OPEN_TURN_ALCHEMY	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_ALCHEMY	(19 * TURN_PER_HOUR)
#define	OPEN_TURN_MUSIC	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_MUSIC	(17 * TURN_PER_HOUR)
#define	OPEN_TURN_GROCERY	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_GROCERY	(19 * TURN_PER_HOUR)
#define	OPEN_TURN_RESTAURANT	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_RESTAURANT	(19 * TURN_PER_HOUR)
#define	OPEN_TURN_TEAROOM	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_TEAROOM	(19 * TURN_PER_HOUR)
#define	OPEN_TURN_TOBACCO	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_TOBACCO	(19 * TURN_PER_HOUR)
#define	OPEN_TURN_PET_SHOP	( 7 * TURN_PER_HOUR)
#define	CLOSE_TURN_PET_SHOP	(19 * TURN_PER_HOUR)

/***************************************************************
* 売り物のアイテムの強さを迷宮の階層に換算した値
***************************************************************/

#define	ART_LEVEL_WPN	-20
#define	ART_LEVEL_ARMOR	-10
#define	ART_LEVEL_POTION	-10
#define	ART_LEVEL_SCROLL	-10
#define	ART_LEVEL_STICK	-10
#define	ART_LEVEL_ACCE	-10
#define	ART_LEVEL_INST	-10
#define	ART_LEVEL_ANTHOLOGY	-10
#define	ART_LEVEL_LIGHT	-10
#define	ART_LEVEL_FOOD	-10
#define	ART_LEVEL_CHEST	-10
#define	ART_LEVEL_TOBACCO	-10
#define	ART_LEVEL_PIPE	-10
#define	ART_LEVEL_DISPOSAL	-10
#define	ART_LEVEL_SPIKE	-10

/***************************************************************
* 物価
***************************************************************/

#define	PRICE_NOT_IDENTIFIED_RATE	((rate_t)80)

#define	CHARGE_STAY_INN_STAY	((gold_t)50)
#define	CHARGE_STAY_INN_SHORT_STAY	((gold_t)50)

/* 武器 */

#define	PRICE_WPN_MIN	50
#define	PRICE_WPN_RATE	((rate_t)10)
#define	PRICE_WPN_BASE	-3000

#define	PRICE_WPN_HIT_MUL	4
#define	PRICE_WPN_CRTCL_MUL	2
#define	PRICE_WPN_DAM_MUL	4

#define	PRICE_WPN_HIT_BASE	-0
#define	PRICE_WPN_CRTCL_BASE	-0
#define	PRICE_WPN_DAM_BASE	-0

#define	PRICE_WPN_ADD_HIT_MUL	500
#define	PRICE_WPN_ADD_CRTCL_MUL	500
#define	PRICE_WPN_ADD_DAM_MUL	500

#define	PRICE_WPN_ADD_HIT_BASE	0
#define	PRICE_WPN_ADD_CRTCL_BASE	0
#define	PRICE_WPN_ADD_DAM_BASE	0

#define	PRICE_WPN_MUL_TYPE_MUL	500
#define	PRICE_WPN_MUL_TYPE_BASE	0

#define	PRICE_WPN_SLAYER	2000
#define	PRICE_WPN_RANDM_ART	2000

#define	PRICE_DAGGER_DIV	400
#define	PRICE_ARW_DIV	500
#define	PRICE_WPN_NOT_SPEND	500

/* 矢 */

#define	PRICE_ARW_ADD_HIT_MUL	1
#define	PRICE_ARW_ADD_CRTCL_MUL	1
#define	PRICE_ARW_ADD_DAM_MUL	1

#define	PRICE_ARW_MUL_TYPE_MUL	1

#define	PRICE_ARW_SLAYER	10

/* 防具 */

#define	PRICE_ARMOR_RATE	((rate_t)4)
#define	PRICE_ARMOR_BASE	0

#define	PRICE_ARMOR_DEF_MUL	2
#define	PRICE_ARMOR_CRTCL_MUL	1
#define	PRICE_ARMOR_AC_MUL	3

#define	PRICE_ARMOR_DEF_BASE	-0
#define	PRICE_ARMOR_CRTCL_BASE	-0
#define	PRICE_ARMOR_AC_BASE	-0

#define	PRICE_ARMOR_ADD_DEF_MUL	500
#define	PRICE_ARMOR_ADD_CRTCL_MUL	500
#define	PRICE_ARMOR_ADD_AC_MUL	500

#define	PRICE_ARMOR_ADD_DEF_BASE	0
#define	PRICE_ARMOR_ADD_CRTCL_BASE	0
#define	PRICE_ARMOR_ADD_AC_BASE	0

#define	PRICE_ARMOR_RANDM_ART	2000

/* 楽器 */

#define	PRICE_INST_BASE	1000
#define	PRICE_INST_LIMIT	3000
#define	PRICE_INST_SPELL	5000

/* その他 */

#define	PRICE_ANTHOLOGY	2000
#define	PRICE_SPIKE	10
#define	PRICE_CHEST	500
#define	PRICE_DISPOSAL	10

/* 寺院 */

#define	PRICE_TEMPLE_REMOVE_CURSE	50
#define	PRICE_TEMPLE_CURE_STATUS_MUL	10
#define	PRICE_TEMPLE_CURE_STATUS_ADD	50
#define	PRICE_TEMPLE_RESURRECTION_MUL	20
#define	PRICE_TEMPLE_RESURRECTION_ADD	100
#define	PRICE_TEMPLE_SMOKER_ADD_RATE	((rate_t)100)
#define	PRICE_TEMPLE_CONTRIBUTION_PRICE_MUL	100
#define	PRICE_TEMPLE_CONTRIBUTION_PRICE_MIN	((gold_t)100)

/* 割り引きセール */

#define	DAY_OF_WEEK_DISCOUNT	DAY_OF_WEEK_PHYS
#define	DISCOUNT_RATE	((rate_t)10)

#define	DISCOUNT_BEGIN_HOUR	6
#define	DISCOUNT_OPEN_HOUR	10
#define	DISCOUNT_END_HOUR	12

#define	DISCOUNT_QUEUE_R	4

discount_queue_t	g_discount_queue;
check_memory_def( check_memory_town_c_g_discount_queue )

/***************************************************************
* その他
***************************************************************/

/* 風呂場をのぞかれる確率 */
#define	MBR_IS_MOLESTED_RATE	((rate_t)10)

/* 迷宮への階段の半径 */
#define	TOWN_STAIRS_R	1

/* XPM 形式の画像の透明色 */
#define	STR_XPM_COL_NONE	"None"

/***************************************************************
* 各データ・テーブル
***************************************************************/

#include	"town-ptn.xpm"
#include	"town-tab.h"
#include	"rumor-tab.h"

/***************************************************************
* グローバル変数
***************************************************************/

static town_ptn_t	town_ptn, town_ptn_trans;
check_memory_def( check_memory_town_c_town_ptn )

static long	g_morning_glow_n, g_evening_glow_n;
check_memory_def( check_memory_town_c_g_morning_glow_n )

static bool_t	g_flg_night;
check_memory_def( check_memory_town_c_g_flg_night )

/***************************************************************
* 街を初期化
***************************************************************/

void	init_town( void )
{
	reset_glow();

	init_town_ptn_col_tab();

	load_town_ptn( &town_ptn );
	if( trans_town_ptn( &town_ptn_trans, &town_ptn ) )
		town_ptn = town_ptn_trans;

	clr_discount();
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_town( void )
{
}

/***************************************************************
* 朝焼け／夕焼けをリセット
***************************************************************/

void	reset_glow( void )
{
	g_morning_glow_n = 4;
	g_evening_glow_n = 4;
	g_flg_night = chk_night();

	chk_morning_glow( get_turn() );
	chk_evening_glow( get_turn() );
}

/***************************************************************
* パターンの色テーブルを初期化
***************************************************************/

void	init_town_ptn_col_tab( void )
{
	long	i, max_i;

	max_i = LOOP_MAX_1000;

	for( i = 0; i < max_i; i++){
		if( town_ptn_col_tab[i].mjr != FACE_MJR_NULL )
			continue;
		if( town_ptn_col_tab[i].mnr != FACE_MNR_NULL )
			continue;
		break;
	}
	if( i < max_i )
		town_ptn_col_tab_max_n = i;
	else
		town_ptn_col_tab_max_n = 0;
}

/***************************************************************
* パターンをデフォルトで上書き
* town_ptn_t *ptn : パターン
* return : エラーが無かったか？
***************************************************************/

bool_t	set_town_ptn_dflt( town_ptn_t *ptn )
{
	long	i;
	long	n;

	if( ptn == NULL )
		return FALSE;

	n = 0;

	if( !set_town_ptn_init( ptn ) )
		return FALSE;

	if( !set_town_ptn_head( ptn, town_ptn_xpm[n] ) )
		return FALSE;
	n++;

	for( i = 0; i < ptn->col_n; i++ ){
		if( !set_town_ptn_col( ptn, town_ptn_xpm[n] ) )
			return FALSE;
		n++;
	}

	if( !set_town_ptn_col_count( ptn ) )
		return FALSE;

	for( i = 0; i < MAP_MAX_Y; i++ ){
		if( !set_town_ptn_map( ptn, town_ptn_xpm[n], i ) )
			return FALSE;
		n++;
	}

	return TRUE;
}

/***************************************************************
* パターンを初期化
* town_ptn_t *ptn : パターン
* return : エラーが無かったか？
***************************************************************/

bool_t	set_town_ptn_init( town_ptn_t *ptn )
{
	long	i;

	if( ptn == NULL )
		return FALSE;

	for( i = 0; i < TOWN_PTN_COL_MAX_N; i++){
		ptn->col_mjr[i] = '\0';
		ptn->col_mnr[i] = '\0';
	}

	return TRUE;
}

/***************************************************************
* パターンのヘッダを読み込む
* town_ptn_t *ptn : パターン
* char *s : ヘッダ文字列
* return : エラーが無かったか？
***************************************************************/

bool_t	set_town_ptn_head( town_ptn_t *ptn, char *s )
{
	long	x, y;
	long	col_n, col_str_len;

	if( ptn == NULL )
		return FALSE;
	if( s == NULL )
		return FALSE;

	sscanf( s, "%ld %ld %ld %ld", &x, &y, &col_n, &col_str_len );

	if( x != MAP_MAX_X ){
		print_err( MSG_ERR_TOWN_MAP_X_SIZE, x, MAP_MAX_X );
		return FALSE;
	}
	if( y != MAP_MAX_Y ){
		print_err( MSG_ERR_TOWN_MAP_Y_SIZE, y, MAP_MAX_Y );
		return FALSE;
	}
	if( (col_str_len != 1) && (col_str_len != 2) ){
		print_err( MSG_ERR_TOWN_MAP_STR_LEN, col_str_len );
		return FALSE;
	}

	ptn->col_n = col_n;
	ptn->col_str_len = col_str_len;

	return TRUE;
}

/***************************************************************
* パターンの色テーブルを読み込む
* town_ptn_t *ptn : パターン
* char *s : 色テーブルの文字列 (1 行分)
* return : エラーが無かったか？
***************************************************************/

bool_t	set_town_ptn_col( town_ptn_t *ptn, char *s )
{
	long	col_code;
	char	col_chr, col_chr_dmy;
	town_ptn_col_tab_t	*col_tab;
	long	col_tab_max_n;
	long	i;

	if( ptn == NULL )
		return FALSE;
	if( s == NULL )
		return FALSE;

	col_tab = get_town_ptn_col_tab();
	col_tab_max_n = get_town_ptn_col_tab_max_n();

	if( strstr( s, STR_XPM_COL_NONE ) != NULL )
		return TRUE;

	if( ptn->col_str_len == 1 ){
		sscanf( s, "%c c #%lx", &col_chr, &col_code );
	} else if( ptn->col_str_len == 2 ){
		sscanf( s, "%c%c c #%lx",
				&col_chr, &col_chr_dmy, &col_code );
	} else {
		return FALSE;
	}
	if( col_chr > TOWN_PTN_COL_MAX_N )
		return FALSE;

	for( i = 0; i < col_tab_max_n; i++ )
		if( col_code == col_tab[i].col_code )
			break;
	if( i >= col_tab_max_n )
		return FALSE;

	if( ptn->col_str_len == 1 ){
		ptn->col_mjr[(unsigned)col_chr] = col_tab[i].mjr;
		ptn->col_mnr[(unsigned)col_chr] = col_tab[i].mnr;
	}

	return TRUE;
}

/***************************************************************
* パターンの色数を数える
* town_ptn_t *ptn : パターン
* return : エラーが無かったか？
***************************************************************/

bool_t	set_town_ptn_col_count( town_ptn_t *ptn )
{
	long	i;
	long	n;

	if( ptn == NULL )
		return FALSE;

	n = 0;
	for( i = 0; i < TOWN_PTN_COL_MAX_N; i++ ){
		if( ptn->col_mjr[i] == '\0' )
			continue;
		if( ptn->col_mnr[i] == '\0' )
			continue;

		n++;
	}

	ptn->col_n = n;

	return TRUE;
}

/***************************************************************
* パターンのマップ・データを読み込む
* town_ptn_t *ptn : パターン
* char *s : マップ・データの文字列 (1 行分)
* long y : マップの Y 座標 (行数)
* return : エラーが無かったか？
***************************************************************/

bool_t	set_town_ptn_map( town_ptn_t *ptn, char *s, long y )
{
	long	x;

	if( ptn == NULL )
		return FALSE;
	if( s == NULL )
		return FALSE;

	if( (ptn->col_str_len != 1) && (ptn->col_str_len != 2) )
		return FALSE;

	for( x = 0; x < MAP_MAX_X; x++ ){
		if( ptn->col_str_len == 1 ){
			ptn->map_mjr[y][x] = s[x];
			ptn->map_mnr[y][x] = '\0';
		} else if( ptn->col_str_len == 2 ){
			ptn->map_mjr[y][x] = s[x * 2];
			ptn->map_mnr[y][x] = s[x * 2 + 1];
		}
	}

	return TRUE;
}

/***************************************************************
* パターンのマップ・データの 1 キャラクタあたりの文字数を
* 1 文字から 2 文字に変換
* town_ptn_t *dst : 変換後のパターン
* town_ptn_t *src : 変換前のパターン
* return : エラーが無かったか？
***************************************************************/

bool_t	trans_town_ptn( town_ptn_t *dst, town_ptn_t *src )
{
	long	col_tab_max_n;
	long	x, y;

	if( dst == NULL )
		return FALSE;
	if( src == NULL )
		return FALSE;

	if( src->col_str_len == 2 )
		return FALSE;

	col_tab_max_n = get_town_ptn_col_tab_max_n();

	if( col_tab_max_n > TOWN_PTN_COL_MAX_N )
		return FALSE;

	set_town_ptn_init( dst );

	dst->col_str_len = 2;
	dst->col_n = 0;

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			unsigned char	c;

			c = src->map_mjr[y][x];
			dst->map_mjr[y][x] = src->col_mjr[c];
			dst->map_mnr[y][x] = src->col_mnr[c];
		}
	}

	return TRUE;
}

/***************************************************************
* 街を生成
***************************************************************/

void	make_town( void )
{
	long	npc_n, npc_max_n;
	long	n;
	long	i;

	reset_dun( TRUE );

	make_town_ptn();

	reset_shop_face_ls();
	if( !chk_shop_face_ls() ){
		print_err( MSG_S, MSG_ERR_TOWN_MAP_SHOP );

		back_up_town_ptn();
		set_town_ptn_dflt( &town_ptn );
		save_town_ptn( &town_ptn );

		if( trans_town_ptn( &town_ptn_trans, &town_ptn ) )
			town_ptn = town_ptn_trans;

		make_town_ptn();
	}

	/* マップの端を壁にする */

	make_fence();

	/* 朝日と夕日をリセット */

	reset_glow();

	/* 街灯を灯す */

	make_streetlamp();

	/* 店の売りものを用意 */

	reset_item_town();

	for( n = 0; n < LOOP_MAX_1000; n++ )
		if( !make_art_town( SHOP_N_BAR,
				&(art_ls_bar[n]) ) )
			break;
	for( n = 0; n < LOOP_MAX_1000; n++ )
		if( !make_art_town( SHOP_N_WPN,
				&(art_ls_wpn[n]) ) )
			break;
	for( n = 0; n < LOOP_MAX_1000; n++ )
		if( !make_art_town( SHOP_N_ARMOR,
				&(art_ls_armor[n]) ) )
			break;
	for( n = 0; n < LOOP_MAX_1000; n++ )
		if( !make_art_town( SHOP_N_ALCHEMY,
				&(art_ls_alchemy[n]) ) )
			break;
	for( n = 0; n < LOOP_MAX_1000; n++ )
		if( !make_art_town( SHOP_N_MUSIC,
				&(art_ls_music[n]) ) )
			break;
	for( n = 0; n < LOOP_MAX_1000; n++ )
		if( !make_art_town( SHOP_N_GROCERY,
				&(art_ls_grocery[n]) ) )
			break;
	for( n = 0; n < LOOP_MAX_1000; n++ )
		if( !make_art_town( SHOP_N_RESTAURANT,
				&(art_ls_restaurant[n]) ) )
			break;
	for( n = 0; n < LOOP_MAX_1000; n++ )
		if( !make_art_town( SHOP_N_TEAROOM,
				&(art_ls_tearoom[n]) ) )
			break;
	for( n = 0; n < LOOP_MAX_1000; n++ )
		if( !make_art_town( SHOP_N_TOBACCO,
				&(art_ls_tobacco[n]) ) )
			break;

	/* 住人を創る */

	npc_max_n = roll_dice( TOWNER_AVE_N, TRUE );
	if( npc_max_n > MNSTR_MAX_N )
		npc_max_n = MNSTR_MAX_N;

	npc_n = 0;
	for( i = 0; i < LOOP_MAX_4000; i++ ){
		long	x, y;

		if( npc_n >= npc_max_n )
			break;

		x = 1 + randm( MAP_MAX_X - 2 );
		y = 1 + randm( MAP_MAX_Y - 2 );

		if( make_npc_rand( x, y, 0 ) != NULL )
			npc_n++;
	}

	/* 依頼 */

	make_request_all();
}

/***************************************************************
* 街のパターンからマップを生成
***************************************************************/

void	make_town_ptn( void )
{
	dun_t *dun = get_dun();
	long	x, y;
	long	i;

	for( y = 0; y < MAP_MAX_Y; y++ )
		for( x = 0; x < MAP_MAX_X; x++ )
			make_field_town( &town_ptn, x, y );

	x = MAP_DEL_X;
	y = MAP_DEL_Y;
	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( !srch_map_obj( FACE_MJR_STAIRS_DOWN,
				FACE_MNR_STAIRS_DOWN, &x, &y ) ){
			break;
		}

		extend_stairs( x, y );
	}

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			char	mjr, mnr;

			mjr = dun->map.obj.mjr[y][x];
			if( mjr != FACE_MJR_DOOR_CLOSE )
				continue;
			mnr = dun->map.obj.mnr[y][x];

			make_door_town( x, y, mnr );
		}
	}
}

/***************************************************************
* 指定座標のマップのを生成
* town_ptn_t *ptn : パターン
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	make_field_town( town_ptn_t *ptn, long x, long y )
{
	dun_t *dun;
	char	mjr, mnr;
	flg_map_t	flg;
	bool_t	flg_light;
	unsigned char	idx;

	dun = get_dun();

	if( ptn->col_str_len == 1 ){
		idx = ptn->map_mjr[y][x];
		mjr = ptn->col_mjr[idx];
		mnr = ptn->col_mnr[idx];
	} else if( ptn->col_str_len == 2 ){
		mjr = ptn->map_mjr[y][x];
		mnr = ptn->map_mnr[y][x];
	} else {
		mjr = FACE_MJR_WALL;
		mnr = FACE_MNR_WALL;
	}
	flg = FLG_MAP_OBJ_FIND;
	flg_light = TRUE;

	switch( mjr ){
	case FACE_MJR_NULL:
		mjr = FACE_MJR_FLOOR;
		mnr = FACE_MNR_HOLE;
		if( chk_night() ){
			if( FLOOR_IS_FIND_NIGHT )
				flg |= FLG_MAP_OBJ_FIND;
			else
				flg &= ~(FLG_MAP_OBJ_FIND);
			flg_light = FALSE;
		}
		break;
	case FACE_MJR_WALL:
		break;
	case FACE_MJR_FLOOR:
		if( chk_night() ){
			if( FLOOR_IS_FIND_NIGHT )
				flg |= FLG_MAP_OBJ_FIND;
			else
				flg &= ~(FLG_MAP_OBJ_FIND);
			flg_light = FALSE;
		}
		if( mnr != FACE_MNR_HOLE )
			flg |= FLG_MAP_OBJ_PASS;
		flg |= FLG_MAP_OBJ_LOOK;
		break;
	case FACE_MJR_DOOR_OPEN:
		mjr = FACE_MJR_DOOR_CLOSE;
		break;
	case FACE_MJR_DOOR_CLOSE:
		break;
	case FACE_MJR_STAIRS_UP:
	case FACE_MJR_STAIRS_DOWN:
		flg |= FLG_MAP_OBJ_PASS | FLG_MAP_OBJ_LOOK;
		break;
	default:
		print_msg( FLG_NULL, MSG_S, MSG_ERR_TOWN_MAP );
	}

	dun->map.obj.mjr[y][x] = mjr;
	dun->map.obj.mnr[y][x] = mnr;
	dun->map.obj.flg[y][x] = flg;
	if( flg_light )
		dun->map.light_depth_obj[y][x] = 1;
	else
		dun->map.light_depth_obj[y][x] = 0;
	dun->map.sect[y][x] = SECT_NULL;
}

/***************************************************************
* 階段を拡張
* long x : X 座標
* long y : Y 座標
* return : エラーが無かったか？
***************************************************************/

bool_t	extend_stairs( long x, long y )
{
	dun_t	*dun = get_dun();
	char	mjr;
	long	xr, yr;
	long	xx, yy;

	if( dun->map.obj.mjr[y][x] != FACE_MJR_STAIRS_UP )
		if( dun->map.obj.mjr[y][x] != FACE_MJR_STAIRS_DOWN )
			return FALSE;
	if( dun->map.obj.mnr[y][x] != FACE_MNR_STAIRS_UP )
		if( dun->map.obj.mnr[y][x] != FACE_MNR_STAIRS_DOWN )
			return FALSE;

	mjr = dun->map.obj.mjr[y][x];

	for( yr = -TOWN_STAIRS_R; yr <= +TOWN_STAIRS_R; yr++ ){
		for( xr = -TOWN_STAIRS_R; xr <= +TOWN_STAIRS_R; xr++ ){
			xx = x + xr;
			yy = y + yr;
			if( !clip_pos( xx, yy ) )
				continue;

			if( dun->map.obj.mjr[yy][xx] != FACE_MJR_FLOOR )
				continue;
			if( dun->map.obj.mnr[yy][xx] != FACE_MNR_FLOOR )
				continue;

			dun->map.obj.mjr[yy][xx] = mjr;
			dun->map.obj.mnr[yy][xx] = FACE_MNR_NULL;
		}
	}

	return TRUE;
}

/***************************************************************
* 街灯を生成
***************************************************************/

void	make_streetlamp( void )
{
	dun_t	*dun = get_dun();
	long	x, y;

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			char	mjr, mnr;

			mjr = dun->map.obj.mjr[y][x];
			mnr = dun->map.obj.mnr[y][x];
			if( mjr != FACE_MJR_WALL )
				continue;
			if( mnr != FACE_MNR_STREETLAMP )
				continue;

			on_streetlamp( x, y );
		}
	}
}

/***************************************************************
* 街灯の明かりを灯す
* long x : X 座標
* long y : Y 座標
***************************************************************/

void	on_streetlamp( long x, long y )
{
	dun_t	*dun = get_dun();
	long	dx, dy;

	for( dy = -STREETLAMP_R; dy <= +STREETLAMP_R; dy++ ){
		for( dx = -STREETLAMP_R; dx <= +STREETLAMP_R; dx++ ){
			long	xx, yy;

			xx = x + dx;
			yy = y + dy;
			if( !clip_pos( xx, yy ) )
				continue;

			dun->map.light_depth_obj[yy][xx]++;
		}
	}
}

/***************************************************************
* 店の商品を生成
* shop_n_t shop_n : 店番号
* void *art_ls : 商品データ・リスト（配列）
* return : 生成したか？
***************************************************************/

bool_t	make_art_town( shop_n_t shop_n, void *art_ls )
{
	item_kind_t	item_kind;
	long	ave_stock;
	long	tab_n;
	item_t	*item, *asgn;
	wpn_kind_t	wpn_kind;
	armor_kind_t	armor_kind;
	potion_kind_t	potion_kind;
	scroll_kind_t	scroll_kind;
	stick_kind_t	stick_kind;
	spell_kind_t	spell_kind;
	ring_kind_t	ring_kind;
	amulet_kind_t	amulet_kind;
	necklace_kind_t	necklace_kind;
	inst_kind_t	inst_kind;
	anthology_kind_t	anthology_kind;
	light_kind_t	light_kind;
	food_kind_t	food_kind;
	tobacco_kind_t	tobacco_kind;
	tobacco_brand_t	tobacco_brand;
	pipe_kind_t	pipe_kind;
	art_ls_bar_t	*art_bar;
	art_ls_wpn_t	*art_wpn;
	art_ls_armor_t	*art_armor;
	art_ls_alchemy_t	*art_alchemy;
	art_ls_music_t	*art_music;
	art_ls_grocery_t	*art_grocery;
	art_ls_restaurant_t	*art_restaurant;
	art_ls_tearoom_t	*art_tearoom;
	art_ls_tobacco_t	*art_tobacco;
	long	lev;

	/**/

	item_kind = ITEM_KIND_NULL;
	ave_stock = 0;
	tab_n = 0;

	wpn_kind = WPN_KIND_NULL;
	armor_kind = ARMOR_KIND_NULL;
	potion_kind = POTION_KIND_NULL;
	scroll_kind = SCROLL_KIND_NULL;
	stick_kind = STICK_KIND_NULL;
	spell_kind = SPELL_KIND_NULL;
	ring_kind = RING_KIND_NULL;
	amulet_kind = AMULET_KIND_NULL;
	necklace_kind = NECKLACE_KIND_NULL;
	inst_kind = INST_KIND_NULL;
	anthology_kind = ANTHOLOGY_KIND_NULL;
	light_kind = LIGHT_KIND_NULL;
	food_kind = FOOD_KIND_NULL;
	tobacco_kind = TOBACCO_KIND_NULL;
	tobacco_brand = TOBACCO_BRAND_NULL;
	pipe_kind = PIPE_KIND_NULL;

	item = NULL;

	switch( shop_n ){
	case SHOP_N_NULL:
	case SHOP_N_MAX_N:
		return FALSE;
	case SHOP_N_BAR:
		art_bar = (art_ls_bar_t *)art_ls;
		item_kind = art_bar->kind;
		ave_stock = art_bar->ave_stock;
		food_kind = art_bar->food;
		potion_kind = art_bar->potion;
		break;
	case SHOP_N_INN:
		return FALSE;
	case SHOP_N_WPN:
		art_wpn = (art_ls_wpn_t *)art_ls;
		item_kind = art_wpn->kind;
		ave_stock = art_wpn->ave_stock;
		wpn_kind = art_wpn->wpn;
		break;
	case SHOP_N_ARMOR:
		art_armor = (art_ls_armor_t *)art_ls;
		item_kind = art_armor->kind;
		ave_stock = art_armor->ave_stock;
		armor_kind = art_armor->armor;
		break;
	case SHOP_N_MAGIC:
	case SHOP_N_TEMPLE:
		return FALSE;
	case SHOP_N_ALCHEMY:
		art_alchemy = (art_ls_alchemy_t *)art_ls;
		item_kind = art_alchemy->kind;
		ave_stock = art_alchemy->ave_stock;
		potion_kind = art_alchemy->potion;
		scroll_kind = art_alchemy->scroll;
		stick_kind = art_alchemy->stick;
		spell_kind = art_alchemy->spell;
		ring_kind = art_alchemy->ring;
		amulet_kind = art_alchemy->amulet;
		necklace_kind = art_alchemy->necklace;
		break;
	case SHOP_N_MUSIC:
		art_music = (art_ls_music_t *)art_ls;
		item_kind = art_music->kind;
		ave_stock = art_music->ave_stock;
		inst_kind = art_music->inst;
		anthology_kind = art_music->anthology;
		break;
	case SHOP_N_GROCERY:
		art_grocery = (art_ls_grocery_t *)art_ls;
		item_kind = art_grocery->kind;
		ave_stock = art_grocery->ave_stock;
		potion_kind = art_grocery->potion;
		food_kind = art_grocery->food;
		tobacco_kind = art_grocery->tobacco;
		tobacco_brand = art_grocery->tobacco_brand;
		light_kind = art_grocery->light;
		break;
	case SHOP_N_RESTAURANT:
		art_restaurant = (art_ls_restaurant_t *)art_ls;
		item_kind = art_restaurant->kind;
		ave_stock = art_restaurant->ave_stock;
		food_kind = art_restaurant->food;
		potion_kind = art_restaurant->potion;
		break;
	case SHOP_N_TEAROOM:
		art_tearoom = (art_ls_tearoom_t *)art_ls;
		item_kind = art_tearoom->kind;
		ave_stock = art_tearoom->ave_stock;
		potion_kind = art_tearoom->potion;
		break;
	case SHOP_N_TOBACCO:
		art_tobacco = (art_ls_tobacco_t *)art_ls;
		item_kind = art_tobacco->kind;
		ave_stock = art_tobacco->ave_stock;
		tobacco_kind = art_tobacco->tobacco;
		tobacco_brand = art_tobacco->tobacco_brand;
		pipe_kind = art_tobacco->pipe;
		break;
	case SHOP_N_PET_SHOP:
		return FALSE;
	}

	if( item_kind == ITEM_KIND_NULL )
		return FALSE;

	switch( item_kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
	case ITEM_KIND_COIN:
	case ITEM_KIND_JUNK:
		return TRUE;
	case ITEM_KIND_WPN:
		tab_n = get_wpn_tab_n( get_wpn_tab( wpn_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		lev = sgn_l( ART_LEVEL_WPN );
		lev *= randm( labs( ART_LEVEL_WPN ) ) + 1;
		item = make_item_wpn( lev, tab_n, FALSE );
		if( item == NULL )
			return FALSE;
		item->n = item->tab.wpn->ave_n;
		break;
	case ITEM_KIND_ARMOR:
		tab_n = get_armor_tab_n( get_armor_tab( armor_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_armor( ART_LEVEL_ARMOR, tab_n, FALSE );
		if( item == NULL )
			return FALSE;
		break;
	case ITEM_KIND_POTION:
		tab_n = get_potion_tab_n( get_potion_tab( potion_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_potion( ART_LEVEL_POTION, tab_n );
		if( item == NULL )
			return FALSE;
		break;
	case ITEM_KIND_SCROLL:
		tab_n = get_scroll_tab_n( get_scroll_tab( scroll_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_scroll( ART_LEVEL_SCROLL, tab_n );
		if( item == NULL )
			return FALSE;
		break;
	case ITEM_KIND_STICK:
		tab_n = get_stick_tab_n( get_stick_tab(
				stick_kind, spell_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_stick( ART_LEVEL_STICK, tab_n );
		if( item == NULL )
			return FALSE;
		item->dat.stick.n = calc_stick_use_n(
				stick_kind,
				ART_LEVEL_STICK,
				item->tab.stick->use_n, FALSE );
		break;
	case ITEM_KIND_ACCE:
		tab_n = get_acce_tab_n( get_acce_tab(
				ring_kind,
				amulet_kind,
				necklace_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_acce( ART_LEVEL_ACCE, tab_n );
		if( item == NULL )
			return FALSE;
		break;
	case ITEM_KIND_INST:
		tab_n = get_inst_tab_n( get_inst_tab( inst_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_inst( ART_LEVEL_INST, tab_n, FALSE );
		if( item == NULL )
			return FALSE;
		break;
	case ITEM_KIND_ANTHOLOGY:
		tab_n = get_anthology_tab_n( get_anthology_tab(
				anthology_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_anthology( ART_LEVEL_ANTHOLOGY, tab_n );
		if( item == NULL )
			return FALSE;
		break;
	case ITEM_KIND_LIGHT:
		tab_n = get_light_tab_n( get_light_tab(
				light_kind, WISH_LEVEL_NULL ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_light( ART_LEVEL_LIGHT, tab_n );
		if( item == NULL )
			return FALSE;
		item->dat.light.turn = item->tab.light->max_turn;
		break;
	case ITEM_KIND_SPIKE:
		item = make_item_spike( ART_LEVEL_SPIKE );
		if( item == NULL )
			return FALSE;
		item->n = SPIKE_AVE_N;
		break;
	case ITEM_KIND_FOOD:
		tab_n = get_food_tab_n( get_food_tab( food_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_food( ART_LEVEL_FOOD, tab_n );
		if( item == NULL )
			return FALSE;
		item->n = 1;
		break;
	case ITEM_KIND_CHEST:
		item = make_item_chest( ART_LEVEL_CHEST,
				get_chest_n( ART_LEVEL_CHEST ), TRUE );
		if( item == NULL )
			return FALSE;
		break;
	case ITEM_KIND_TOBACCO:
		tab_n = get_tobacco_tab_n( get_tobacco_tab(
				tobacco_kind, tobacco_brand ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_tobacco( ART_LEVEL_TOBACCO, tab_n );
		if( item == NULL )
			return FALSE;
		item->n = item->tab.tobacco->ave_n;
		break;
	case ITEM_KIND_PIPE:
		tab_n = get_pipe_tab_n( get_pipe_tab( pipe_kind ) );
		if( tab_n <= -1 )
			return TRUE;
		item = make_item_pipe( ART_LEVEL_PIPE, tab_n );
		if( item == NULL )
			return FALSE;
		if( chk_flg( item->tab.pipe->flg, FLG_PIPE_CONSUMPTION ) )
			item->n = item->tab.pipe->ave_n;
		break;
	case ITEM_KIND_DISPOSAL:
		item = make_item_disposal( ART_LEVEL_DISPOSAL );
		if( item == NULL )
			return FALSE;
		break;
	case ITEM_KIND_RARE_GOODS:
		return TRUE;
	case ITEM_KIND_BONE:
		return TRUE;
	}

	if( ave_stock == 1 )
		item->stock = 1;
	else
		item->stock = roll_dice( ave_stock, TRUE );
	if( (item->kind == ITEM_KIND_WPN)
			&& (item->dat.wpn.slayer != FACE_MJR_NULL) ){
		item->stock = 1;
	}
	if( item->stock <= 0 ){
		del_item( item );
		return TRUE;
	}

	item->flg |= FLG_ITEM_DETECTED | FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_CURSED);
	set_item_name( item );

	asgn = NULL;
	switch( shop_n ){
	case SHOP_N_NULL:
	case SHOP_N_MAX_N:
	case SHOP_N_INN:
		return TRUE;
	case SHOP_N_BAR:
		asgn = get_shop_bar_item_asgn();
		break;
	case SHOP_N_WPN:
		asgn = get_shop_wpn_item_asgn();
		break;
	case SHOP_N_ARMOR:
		asgn = get_shop_armor_item_asgn();
		break;
	case SHOP_N_MAGIC:
		return TRUE;
	case SHOP_N_TEMPLE:
		asgn = get_shop_temple_item_asgn();
		break;
	case SHOP_N_ALCHEMY:
		asgn = get_shop_alchemy_item_asgn();
		break;
	case SHOP_N_MUSIC:
		asgn = get_shop_music_item_asgn();
		break;
	case SHOP_N_GROCERY:
		asgn = get_shop_grocery_item_asgn();
		break;
	case SHOP_N_RESTAURANT:
		asgn = get_shop_restaurant_item_asgn();
		break;
	case SHOP_N_TEAROOM:
		asgn = get_shop_tearoom_item_asgn();
		break;
	case SHOP_N_TOBACCO:
		asgn = get_shop_tobacco_item_asgn();
		break;
	case SHOP_N_PET_SHOP:
		return TRUE;
	}
	ins_ls_item( asgn, item );

	return TRUE;
}

/***************************************************************
* 街のドアを生成
* long mx : X 座標
* long my : Y 座標
* char mnr : マイナーの顔文字
***************************************************************/

void	make_door_town( long mx, long my, char mnr )
{
	dun_t *dun;
	long	dx, dy;
	long	i;

	dun = get_dun();

	/* すでに登録ずみか */
	if( clip_x( mx - 1 ) )
		if( dun->map.obj.mjr[my][mx - 1] == FACE_MJR_DOOR_CLOSE )
			return;
	if( clip_x( my - 1 ) )
		if( dun->map.obj.mjr[my - 1][mx] == FACE_MJR_DOOR_CLOSE )
			return;


	for( i = 0; i < AREA_MAX_X; i++ )
		if( dun->map.obj.mjr[my][mx + i] != FACE_MJR_DOOR_CLOSE )
			break;
	dx = i - 1;
	if( dx < 0 )
		return;

	for( i = 0; i < AREA_MAX_Y; i++ )
		if( dun->map.obj.mjr[my + i][mx] != FACE_MJR_DOOR_CLOSE )
			break;
	dy = i - 1;
	if( dy < 0 )
		return;

	make_door( mx, my, mx + dx, my + dy, mnr );
}

/***************************************************************
* 全ての店がマップ上に有るかチェックするデータをリセット
***************************************************************/

void	reset_shop_face_ls( void )
{
	dun_t *dun = get_dun();
	long	i, j;

	for( i = 0; i < g_shop_face_ls_max_n; i++ )
		g_shop_face_ls[i].flg = FALSE;

	for( i = 0; i < MAP_MAX_Y; i++ ){
		for( j = 0; j < MAP_MAX_X; j++ ){
			char	mjr, mnr;

			mjr = dun->map.obj.mjr[i][j];
			if( mjr != FACE_MJR_DOOR_CLOSE )
				continue;
			mnr = dun->map.obj.mnr[i][j];

			set_shop_face_ls( mnr );
		}
	}
}

/***************************************************************
* 店がマップ上に有るかどうかのフラグをセット
* char mnr : マイナーの顔文字
***************************************************************/

bool_t	set_shop_face_ls( char mnr )
{
	long	i;

	for( i = 0; i < g_shop_face_ls_max_n; i++ ){
		if( g_shop_face_ls[i].mnr == mnr ){
			if( g_shop_face_ls[i].flg ){
				return FALSE;
			} else {
				g_shop_face_ls[i].flg = TRUE;
				return TRUE;
			}
		}
	}

	return FALSE;
}

/***************************************************************
* 全ての店がマップ上に有るかチェック
* return : 全ての店がマップ上に有るか?
***************************************************************/

bool_t	chk_shop_face_ls( void )
{
	long	i;

	for( i = 0; i < g_shop_face_ls_max_n; i++ )
		if( !g_shop_face_ls[i].flg )
			return FALSE;

	return TRUE;
}

/***************************************************************
* パーティを街に出現させる
* return : 出現できたか?
***************************************************************/

bool_t	appear_party_town( void )
{
	party_t	*pty;
	long	n;
	long	x, y;

	pty = get_party();

	for( n = 0; n < MBR_MAX_N; n++ ){
		lost_trgt( pty->mbr[n] );
		clr_chr_trgt_act( pty->mbr[n], FALSE );
	}

	x = MAP_DEL_X;
	y = MAP_DEL_Y;
	if( !srch_map_obj( FACE_MJR_STAIRS_DOWN,
			FACE_MNR_STAIRS_DOWN, &x, &y ) ){
		return FALSE;
	}
	set_square_pos( x, y, FALSE );
	set_square_pos( x, y, TRUE );

	clr_map_all_mbr();
	clr_map_all_pet();

	for( n = 0; n < MBR_MAX_N; n++ ){
		long	nx, ny;

		if( chk_flg_or( pty->mbr[n]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
			continue;

		get_square_mbr_abs_pos( n, &nx, &ny );
		put_chr( pty->mbr[n], nx, ny );
	}

	reset_mbr_dir();
	appear_all_pet();

	next_pos_square( 0 );
	scroll_center_appear_party();
	set_flg_find_all_mnstr();

	redraw_all();

	return TRUE;
}

/***************************************************************
* パーティをナビで移動
* shop_n_t shop_n : 店番号
* return : 移動できたか?
***************************************************************/

bool_t	navi_party( shop_n_t shop_n )
{
	door_t	*dr;

	dr = get_shop_door( shop_n );
	if( dr == NULL )
		return FALSE;

	add_turn( NAVI_ADD_TURN_N );
	print_msg( FLG_NULL, MSG_NAVI_PARTY, get_shop_name( shop_n ) );

	open_door_shop( dr->n );
	exec_all_phase();

	return TRUE;
}

/***************************************************************
* パーティをナビで階段へ移動
* return : 移動できたか?
***************************************************************/

bool_t	navi_party_stairs()
{
	if( !appear_party_town() )
		return FALSE;

	add_turn( NAVI_ADD_TURN_N );
	print_msg( FLG_NULL, MSG_NAVI_PARTY, MSG_NAVI_PARTY_STAIRS );

	return TRUE;
}

/***************************************************************
* 店に入るためのパーティのアクションを設定
* long n : ドア番号
* return : エラーが無かったか？
***************************************************************/

bool_t	open_door_shop( long n )
{
	dun_t	*dun;
	party_t	*pty;

	dun = get_dun();

	if( n < 0 )
		return FALSE;
	if( n >= dun->door_n )
		return FALSE;
	if( !chk_flg( dun->door[n].flg, FLG_DOOR_SHOP ) )
		return FALSE;

	pty = get_party();
	pty->act.kind = ACT_KIND_SHOP;
	pty->act.p = NULL;
	pty->act.n = dun->map.obj.mnr[dun->door[n].y][dun->door[n].x];
	pty->act.n2 = n;

	return TRUE;
}

/***************************************************************
* パーティが店に入る
* return : エラーが無かったか？
***************************************************************/

bool_t	enter_shop( void )
{
	party_t	*pty;
	char	face_mnr;
	long	dr_n;
	shop_n_t	shop_n;

	pty = get_party();

	set_flg_exit_shop( TRUE );

	if( pty->act.kind != ACT_KIND_SHOP )
		return FALSE;

	clr_party_act();

	face_mnr = (char)(pty->act.n);
	dr_n = (long)(pty->act.n2);

	shop_n = get_shop_n( face_mnr );
	if( !chk_shop_open( shop_n, TRUE ) )
		return FALSE;

	clr_map_all_mbr();
	clr_map_all_pet();

	set_cur_shop_n( shop_n );
	change_scene( SCENE_N_SHOP );

	say_welcome_shop_msg( shop_n );

	while( 1 ){
		switch( face_mnr ){
		case FACE_MNR_SHOP_INN:
			menu_inn();
			break;
		case FACE_MNR_SHOP_BAR:
			menu_bar();
			break;
		case FACE_MNR_SHOP_TEMPLE:
			menu_shop_sel_mbr( shop_n, TRUE );
			break;
		case FACE_MNR_SHOP_RESTAURANT:
			menu_restaurant();
			break;
		case FACE_MNR_SHOP_WPN:
		case FACE_MNR_SHOP_ARMOR:
		case FACE_MNR_SHOP_MAGIC:
		case FACE_MNR_SHOP_ALCHEMY:
		case FACE_MNR_SHOP_MUSIC:
		case FACE_MNR_SHOP_GROCERY:
		case FACE_MNR_SHOP_TEAROOM:
		case FACE_MNR_SHOP_TOBACCO:
		case FACE_MNR_SHOP_PET_SHOP:
			menu_shop_sel_mbr( shop_n, FALSE );
			break;
		default:
			return FALSE;
		}

		if( chk_not_exist_all_mbr() ){
			print_msg( FLG_MSG_ERR, MSG_S,
					MSG_ERR_NOT_EXIST_ALL_MBR );
		} else {
			if( get_flg_exit_shop() )
				party_exit_shop( dr_n );
			break;
		}
	}

	return TRUE;
}

/***************************************************************
* パーティが店から出る
* long dr_n : ドア番号
***************************************************************/

void	party_exit_shop( long dr_n )
{
	long	seed;
	dun_t	*dun;
	party_t	*pty;
	long	x, y;
	long	dx, dy;
	bool_t	flg_force;
	long	i, j;

	seed = get_randm_seed();

	dun = get_dun();
	pty = get_party();

	for( i = 0; i < MBR_MAX_N; i++ )
		clr_chr_trgt_act( pty->mbr[i], FALSE );

	flg_force = TRUE;
	for( i = 0; i < 4; i++ ){
		switch( i ){
		default:
		case 0:
			x = dun->door[dr_n].x;
			y = dun->door[dr_n].y + dun->door[dr_n].dy;
			break;
		case 1:
			x = dun->door[dr_n].x - 3;
			y = dun->door[dr_n].y;
			break;
		case 2:
			x = dun->door[dr_n].x;
			y = dun->door[dr_n].y - 3;
			break;
		case 3:
			x = dun->door[dr_n].x + dun->door[dr_n].dx;
			y = dun->door[dr_n].y;
			break;
		}

		flg_force = FALSE;
		for( dy = 0; dy < 3; dy++ ){
			for( dx = 0; dx < 3; dx++ ){
				if( !chk_flg( dun->map.obj.flg
						[y + dy][x + dx],
						FLG_MAP_OBJ_PASS ) ){
					flg_force = TRUE;
					break;
				}
			}
			if( flg_force )
				break;
		}

		if( !flg_force )
			break;
	}

	if( flg_force ){
		/* 無理矢理に出る */

		if( !appear_party_town() )
			appear_party();
	} else {
		/* 普通に出る */

		set_square_pos( x + 1, y + 1, FALSE );
		clr_map_all_mbr();

		for( j = 0; j < MBR_MAX_N; j++ ){
			long	x, y;

			get_square_mbr_abs_pos( j, &x, &y );
			put_chr( pty->mbr[j], x, y );
		}

		reset_mbr_dir();
		appear_all_pet();
	}

	next_pos_square( 0 );
	scroll_center_appear_party();
	set_flg_find_all_mnstr();
	wipe_menu();

	get_square_pos( &x, &y, FALSE );
	move_crsr_abs( x, y );

	if( dun->door[dr_n].mnr != FACE_MNR_SHOP_BAR )
		add_turn( SHOP_ADD_TURN_N );

	change_scene( SCENE_N_TOWN );
	set_cur_shop_n( SHOP_N_NULL );

	srandm( seed );
}

/***************************************************************
* 店長のあいさつ
* shop_n_t shop_n : 店番号
***************************************************************/

void	say_welcome_shop_msg( shop_n_t shop_n )
{
	sex_t	sex;
	const char	*name;

	sex = get_npc_sex_shop( shop_n );
	name = get_npc_name_shop( shop_n, sex );

	switch( shop_n ){
	case SHOP_N_NULL:
	case SHOP_N_MAX_N:
		break;
	case SHOP_N_INN:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_INN_FEMALE,
				MSG_WORDS_WELCOME_SHOP_INN_MALE );
		break;
	case SHOP_N_BAR:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_BAR_FEMALE,
				MSG_WORDS_WELCOME_SHOP_BAR_MALE );
		break;
	case SHOP_N_WPN:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_WPN_FEMALE,
				MSG_WORDS_WELCOME_SHOP_WPN_MALE );
		break;
	case SHOP_N_ARMOR:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_ARMOR_FEMALE,
				MSG_WORDS_WELCOME_SHOP_ARMOR_MALE );
		break;
	case SHOP_N_MAGIC:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_MAGIC_FEMALE,
				MSG_WORDS_WELCOME_SHOP_MAGIC_MALE );
		break;
	case SHOP_N_TEMPLE:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_TEMPLE_FEMALE,
				MSG_WORDS_WELCOME_SHOP_TEMPLE_MALE );
		break;
	case SHOP_N_ALCHEMY:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_ALCHEMY_FEMALE,
				MSG_WORDS_WELCOME_SHOP_ALCHEMY_MALE );
		break;
	case SHOP_N_MUSIC:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_MUSIC_FEMALE,
				MSG_WORDS_WELCOME_SHOP_MUSIC_MALE );
		break;
	case SHOP_N_GROCERY:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_GROCERY_FEMALE,
				MSG_WORDS_WELCOME_SHOP_GROCERY_MALE );
		break;
	case SHOP_N_RESTAURANT:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_RESTAURANT_FEMALE,
				MSG_WORDS_WELCOME_SHOP_RESTAURANT_MALE );
		break;
	case SHOP_N_TEAROOM:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_TEAROOM_FEMALE,
				MSG_WORDS_WELCOME_SHOP_TEAROOM_MALE );
		break;
	case SHOP_N_TOBACCO:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_TOBACCO_FEMALE,
				MSG_WORDS_WELCOME_SHOP_TOBACCO_MALE );
		break;
	case SHOP_N_PET_SHOP:
		print_words( name, sex,
				MSG_WORDS_WELCOME_SHOP_PET_SHOP_FEMALE,
				MSG_WORDS_WELCOME_SHOP_PET_SHOP_MALE );
		break;
	}
}

/***************************************************************
* 店長の名前を返す
* shop_n_t shop_n : 店番号
* sex_t sex : 店長の性別
* return : 店長の名前
***************************************************************/

const char	*get_npc_name_shop( shop_n_t shop_n, sex_t sex )
{
	if( sex == FEMALE ){
		switch( shop_n ){
		case SHOP_N_NULL:
		case SHOP_N_MAX_N:
			return MSG_NPC_NAME_SHOP_NULL_FEMALE;
		case SHOP_N_INN:
			return MSG_NPC_NAME_SHOP_INN_FEMALE;
		case SHOP_N_BAR:
			return MSG_NPC_NAME_SHOP_BAR_FEMALE;
		case SHOP_N_WPN:
			return MSG_NPC_NAME_SHOP_WPN_FEMALE;
		case SHOP_N_ARMOR:
			return MSG_NPC_NAME_SHOP_ARMOR_FEMALE;
		case SHOP_N_MAGIC:
			return MSG_NPC_NAME_SHOP_MAGIC_FEMALE;
		case SHOP_N_TEMPLE:
			return MSG_NPC_NAME_SHOP_TEMPLE_FEMALE;
		case SHOP_N_ALCHEMY:
			return MSG_NPC_NAME_SHOP_ALCHEMY_FEMALE;
		case SHOP_N_MUSIC:
			return MSG_NPC_NAME_SHOP_MUSIC_FEMALE;
		case SHOP_N_GROCERY:
			return MSG_NPC_NAME_SHOP_GROCERY_FEMALE;
		case SHOP_N_RESTAURANT:
			return MSG_NPC_NAME_SHOP_RESTAURANT_FEMALE;
		case SHOP_N_TEAROOM:
			return MSG_NPC_NAME_SHOP_TEAROOM_FEMALE;
		case SHOP_N_TOBACCO:
			return MSG_NPC_NAME_SHOP_TOBACCO_FEMALE;
		case SHOP_N_PET_SHOP:
			return MSG_NPC_NAME_SHOP_PET_SHOP_FEMALE;
		}
	} else {
		switch( shop_n ){
		case SHOP_N_NULL:
		case SHOP_N_MAX_N:
			return MSG_NPC_NAME_SHOP_NULL_MALE;
		case SHOP_N_INN:
			return MSG_NPC_NAME_SHOP_INN_MALE;
		case SHOP_N_BAR:
			return MSG_NPC_NAME_SHOP_BAR_MALE;
		case SHOP_N_WPN:
			return MSG_NPC_NAME_SHOP_WPN_MALE;
		case SHOP_N_ARMOR:
			return MSG_NPC_NAME_SHOP_ARMOR_MALE;
		case SHOP_N_MAGIC:
			return MSG_NPC_NAME_SHOP_MAGIC_MALE;
		case SHOP_N_TEMPLE:
			return MSG_NPC_NAME_SHOP_TEMPLE_MALE;
		case SHOP_N_ALCHEMY:
			return MSG_NPC_NAME_SHOP_ALCHEMY_MALE;
		case SHOP_N_MUSIC:
			return MSG_NPC_NAME_SHOP_MUSIC_MALE;
		case SHOP_N_GROCERY:
			return MSG_NPC_NAME_SHOP_GROCERY_MALE;
		case SHOP_N_RESTAURANT:
			return MSG_NPC_NAME_SHOP_RESTAURANT_MALE;
		case SHOP_N_TEAROOM:
			return MSG_NPC_NAME_SHOP_TEAROOM_MALE;
		case SHOP_N_TOBACCO:
			return MSG_NPC_NAME_SHOP_TOBACCO_MALE;
		case SHOP_N_PET_SHOP:
			return MSG_NPC_NAME_SHOP_PET_SHOP_MALE;
		}
	}

	return MSG_NPC_NAME_SHOP_NULL_MALE;
}

/***************************************************************
* 店長の性別を返す
* shop_n_t shop_n : 店番号
* return : 性別の名前
***************************************************************/

sex_t	get_npc_sex_shop( shop_n_t shop_n )
{
	switch( shop_n ){
	case SHOP_N_NULL:
	case SHOP_N_MAX_N:
		break;
	case SHOP_N_INN:
		return MALE;
	case SHOP_N_BAR:
		return MALE;
	case SHOP_N_WPN:
		return MALE;
	case SHOP_N_ARMOR:
		return MALE;
	case SHOP_N_MAGIC:
		return MALE;
	case SHOP_N_TEMPLE:
		return MALE;
	case SHOP_N_ALCHEMY:
		return FEMALE;
	case SHOP_N_MUSIC:
		return FEMALE;
	case SHOP_N_GROCERY:
		return MALE;
	case SHOP_N_RESTAURANT:
		return MALE;
	case SHOP_N_TEAROOM:
		return FEMALE;
	case SHOP_N_TOBACCO:
		return FEMALE;
	case SHOP_N_PET_SHOP:
		return FEMALE;
	}

	return MALE;
}

/***************************************************************
* パーティが酒場に入る
***************************************************************/

void	party_enter_bar( void )
{
	door_t	*dr;

	dr = get_shop_door( SHOP_N_BAR );
	if( dr == NULL )
		return;

	open_door_shop( dr->n );
	enter_shop();
}

/***************************************************************
* パーティが酒場から出る
***************************************************************/

void	party_exit_bar( void )
{
	door_t	*dr;
	long	seed;

	seed = get_randm_seed();

	dr = get_shop_door( SHOP_N_BAR );
	if( dr == NULL )
		return;

	srandm( seed );

	party_exit_shop( dr->n );
}

/***************************************************************
* 店の営業時間中か調べる
* shop_n_t shop_n : 店番号
* bool_t flg_print : メッセージを表示するか?
* return : 店の営業時間中か?
***************************************************************/

bool_t	chk_shop_open( shop_n_t shop_n, bool_t flg_print )
{
	long	turn, open_turn, close_turn;
	bool_t	ret;

	turn = get_turn();
	open_turn = (24 * TURN_PER_HOUR);
	close_turn = (0 * TURN_PER_HOUR);

	switch( shop_n ){
	case SHOP_N_NULL:
	case SHOP_N_MAX_N:
		break;
	case SHOP_N_INN:
		open_turn = OPEN_TURN_INN;
		close_turn = CLOSE_TURN_INN;
		break;
	case SHOP_N_BAR:
		open_turn = OPEN_TURN_BAR;
		close_turn = CLOSE_TURN_BAR;
		break;
	case SHOP_N_WPN:
		open_turn = OPEN_TURN_WPN;
		close_turn = CLOSE_TURN_WPN;
		break;
	case SHOP_N_ARMOR:
		open_turn = OPEN_TURN_ARMOR;
		close_turn = CLOSE_TURN_ARMOR;
		break;
	case SHOP_N_MAGIC:
		open_turn = OPEN_TURN_MAGIC;
		close_turn = CLOSE_TURN_MAGIC;
		break;
	case SHOP_N_TEMPLE:
		open_turn = OPEN_TURN_TEMPLE;
		close_turn = CLOSE_TURN_TEMPLE;
		break;
	case SHOP_N_ALCHEMY:
		open_turn = OPEN_TURN_ALCHEMY;
		close_turn = CLOSE_TURN_ALCHEMY;
		break;
	case SHOP_N_MUSIC:
		open_turn = OPEN_TURN_MUSIC;
		close_turn = CLOSE_TURN_MUSIC;
		break;
	case SHOP_N_GROCERY:
		open_turn = OPEN_TURN_GROCERY;
		close_turn = CLOSE_TURN_GROCERY;
		break;
	case SHOP_N_RESTAURANT:
		open_turn = OPEN_TURN_RESTAURANT;
		close_turn = CLOSE_TURN_RESTAURANT;
		break;
	case SHOP_N_TEAROOM:
		open_turn = OPEN_TURN_TEAROOM;
		close_turn = CLOSE_TURN_TEAROOM;
		break;
	case SHOP_N_TOBACCO:
		open_turn = OPEN_TURN_TOBACCO;
		close_turn = CLOSE_TURN_TOBACCO;
		break;
	case SHOP_N_PET_SHOP:
		open_turn = OPEN_TURN_PET_SHOP;
		close_turn = CLOSE_TURN_PET_SHOP;
		break;
	}

	ret = TRUE;
	if( turn < open_turn )
		ret = FALSE;
	if( turn > close_turn )
		ret = FALSE;

	if( !ret && flg_print ){
		print_msg( FLG_MSG_ERR, MSG_ERR_SHOP_CLOSE,
				get_shop_name( shop_n ),
				open_turn / TURN_PER_HOUR,
				close_turn / TURN_PER_HOUR );
	}

	return ret;
}

/***************************************************************
* 商品をまとめ売りするか調べる
* item_t *item : 商品
* return : まとめ売りするか?
***************************************************************/

bool_t	chk_package_item( item_t *item )
{
	if( item == NULL )
		return FALSE;

	switch( item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		return FALSE;
	case ITEM_KIND_WPN:
		if( chk_flg( item->tab.wpn->flg, FLG_WPN_TAB_ARW ) )
			return TRUE;
		return FALSE;
	case ITEM_KIND_ARMOR:
	case ITEM_KIND_POTION:
	case ITEM_KIND_SCROLL:
	case ITEM_KIND_STICK:
	case ITEM_KIND_ACCE:
	case ITEM_KIND_INST:
	case ITEM_KIND_ANTHOLOGY:
	case ITEM_KIND_LIGHT:
	case ITEM_KIND_FOOD:
	case ITEM_KIND_CHEST:
	case ITEM_KIND_DISPOSAL:
	case ITEM_KIND_RARE_GOODS:
	case ITEM_KIND_COIN:
	case ITEM_KIND_JUNK:
		return FALSE;
	case ITEM_KIND_SPIKE:
	case ITEM_KIND_TOBACCO:
	case ITEM_KIND_BONE:
		return TRUE;
	case ITEM_KIND_PIPE:
		if( chk_flg( item->tab.pipe->flg, FLG_PIPE_CONSUMPTION ) )
			return TRUE;
		return FALSE;
	}
	return FALSE;
}

/***************************************************************
* 宿屋に泊る
***************************************************************/

void	stay_inn( stay_inn_kind_t kind )
{
	bool_t flg_short_stay, flg_mews;
	party_t	*pty = get_party();
	pet_t	**pet = get_party_pet();
	long	turn;
	fx_t	*fx;
	long	i, j;

	/* 統計を取る */
	update_playing_report_staying_inn_party( kind );

	flg_short_stay = (kind == STAY_INN_KIND_SHORT);
	flg_mews = (kind == STAY_INN_KIND_MEWS);

	if( flg_short_stay ){
		turn = 12 * TURN_PER_HOUR;
	} else {
		turn = TURN_A_DAY - (get_turn() % TURN_A_DAY);
		turn += 7 * TURN_PER_HOUR;
	}

	dec_turn_fx_all_mbr( turn );

	for( i = 0; i < MBR_MAX_N; i++ ){
		mbr_t	*mbr;

		mbr = pty->mbr[i];

		if( chk_flg_or( mbr->stat, 0
				| FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD
				| FLG_STAT_STONE ) ){
			continue;
		}

		/* 統計を取る */
		update_playing_report_staying_inn_mbr(
				mbr->ls_mbr_n, kind );

		if( !flg_mews ){
			/* 毒におかされていなければ HP を回復する */
			fx = srch_fx( &(mbr->fx), FX_KIND_POISON );
			if( fx == NULL ){
				mbr->abl.hp.n = mbr->abl.hp.max;
			}
		}

		/* MP を回復する */
		mbr->abl.mp.n = mbr->abl.mp.max;

		if( FLG_RESET_RESI_STAY_INN ){
			/* 耐性値をリセット */
			for( j = 0; j < RESI_KIND_MAX_N; j++ ){
				reset_mbr_resi( mbr );
				mbr->resi[j].n = get_resi_max(
						mbr, (resi_kind_t)j );
			}
		}

		/* 酔いがさめる */
		mbr->fx_data.drunk_rate = (rate_t)0;

		/* 呪歌をおぼえる */
		learn_spell_bar( mbr );

		/* 食事をとる */
		/* take_meal_fill_chr( mbr ); */

		/* 吸い殻を片付ける */
		clean_all_disposal( mbr );

		/* 統計を取る */
		update_playing_report_staying_inn_mbr( mbr->ls_mbr_n, kind );
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet[i] == NULL )
			continue;
		if( chk_flg_or( pet[i]->stat, 0
				| FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD
				| FLG_STAT_STONE ) ){
			continue;
		}

		/* 毒におかされていなければ HP を回復する */
		fx = srch_fx( &(pet[i]->fx), FX_KIND_POISON );
		if( fx == NULL ){
			pet[i]->abl.hp.n = pet[i]->abl.hp.max;
		}

		/* MP を回復する */
		pet[i]->abl.mp.n = pet[i]->abl.mp.max;

		/* 耐性値をリセット */
		for( j = 0; j < RESI_KIND_MAX_N; j++ ){
			reset_pet_resi( pet[i] );
			pet[i]->resi[j].n = get_resi_max(
					pet[i], (resi_kind_t)j );
		}

		/* 酔いがさめる */
		pet[i]->fx_data.drunk_rate = (rate_t)0;

		/* 食事をとる */
		take_meal_fill_chr( pet[i] );
	}

	/* 統計を取る */
	update_playing_report_staying_inn_party( kind );

	reset_turn( get_turn() + turn );
	reset_all( FALSE );
	reset_glow();

	if( flg_short_stay ){
		print_msg( FLG_NULL, MSG_S, MSG_MENU_INN_DO_SHORT_STAY );
	} else {
		print_msg( FLG_NULL, MSG_S, MSG_MENU_INN_DO_STAY );
	}
	print_msg( FLG_NULL, MSG_MENU_INN_CALENDAR,
			get_calendar_str() );

	if( chk_discount() ){
		sex_t	sex;
		const char	*name;

		sex = get_npc_sex_shop( SHOP_N_INN );
		name = get_npc_name_shop( SHOP_N_INN, sex );

		print_words( name, sex,
				MSG_WORDS_DISCOUNT_DAY_FEMALE,
				MSG_WORDS_DISCOUNT_DAY_MALE,
				get_shop_name( g_discount_queue.shop_n ) );
	}
}

/***************************************************************
* キャラクタが風呂に入る
* chr_t *chr : キャラクタ
***************************************************************/

void	take_bath( chr_t *chr )
{
	long	j;

	if( chr == NULL )
		return;

	print_msg( FLG_NULL, MSG_TAKE_BATH, chr->name );

	if( !is_mbr( chr ) )
		return;

	print_words( chr->name, chr->sex.cur,
			MSG_WORDS_TAKE_BATH_FAMALE,
			MSG_WORDS_TAKE_BATH_MALE );

	/* 痴漢にのぞかれた */

	if( rate_randm( MBR_IS_MOLESTED_RATE ) ){
		print_msg( FLG_NULL, MSG_CHR_IS_MOLESTED,
				chr->name );

		print_words( chr->name, chr->sex.cur,
				MSG_WORDS_CHR_IS_MOLESTED_FAMALE,
				MSG_WORDS_CHR_IS_MOLESTED_MALE );
	}

	/* 耐性値をリセット */

	for( j = 0; j < RESI_KIND_MAX_N; j++ ){
		reset_mbr_resi( chr );
		chr->resi[j].n = get_resi_max(
				chr, (resi_kind_t)j );
	}
}

/***************************************************************
* アイテムの商品名をつける
* mbr_t *mbr : メンバー
* item_t *art : 商品
* deal_kind_t kind : 取り引きの種類
* return : エラーが無かったか？
***************************************************************/

bool_t	set_art_name( mbr_t *mbr, item_t *art, deal_kind_t kind )
{
	party_t	*pty;

	if( mbr == NULL )
		return FALSE;
	if( art == NULL )
		return FALSE;

	pty = get_party();

	if( kind == DEAL_KIND_SALE_EQUIP ){
		long	i, j;

		for( i = 0; i < MBR_MAX_N; i++ ){
			item_t	*p;

			p = get_mbr_item_asgn_equip( pty->mbr[i] );
			if( p == NULL )
				continue;

			for( j = 0; j < EQUIP_KIND_MAX_N; j++ ){
				if( art == &(p[j]) ){
					set_art_name_equip( pty->mbr[i],
							art,
							(equip_kind_t)j );
					return TRUE;
				}
			}
		}
	}

	strcpy( art->art_name, art->name );

	return TRUE;
}

/***************************************************************
* 装備の商品名をつける
* mbr_t *mbr : メンバー
* item_t *art : 商品
* equip_kind_t eq : 装備の種類
* return : エラーが無かったか？
***************************************************************/

bool_t	set_art_name_equip( mbr_t *mbr, item_t *art, equip_kind_t eq )
{
	char	*eq_name;

	if( mbr == NULL )
		return FALSE;
	if( art == NULL )
		return FALSE;

	switch( eq ){
	case EQUIP_KIND_WIELDING:
		eq_name = MSG_EQUIP_WIELDING;
		break;
	case EQUIP_KIND_SHIELD:
		eq_name = MSG_EQUIP_SHIELD;
		break;
	case EQUIP_KIND_BOW:
		eq_name = MSG_EQUIP_BOW;
		break;
	case EQUIP_KIND_ARW:
		eq_name = MSG_EQUIP_ARW;
		break;
	case EQUIP_KIND_HEAD:
		eq_name = MSG_EQUIP_HEAD;
		break;
	case EQUIP_KIND_NECK:
		eq_name = MSG_EQUIP_NECK;
		break;
	case EQUIP_KIND_BODY:
		eq_name = MSG_EQUIP_BODY;
		break;
	case EQUIP_KIND_ARM:
		eq_name = MSG_EQUIP_ARM;
		break;
	case EQUIP_KIND_RIGHT_HAND:
		eq_name = MSG_EQUIP_RIGHT_HAND;
		break;
	case EQUIP_KIND_LEFT_HAND:
		eq_name = MSG_EQUIP_LEFT_HAND;
		break;
	case EQUIP_KIND_FEET:
		eq_name = MSG_EQUIP_FEET;
		break;
	case EQUIP_KIND_ABOUT_BODY:
		eq_name = MSG_EQUIP_ABOUT_BODY;
		break;
	case EQUIP_KIND_LIGHT_SOURCE:
		eq_name = MSG_EQUIP_LIGHT_SOURCE;
		break;
	case EQUIP_KIND_MAX_N:
	default:
		eq_name = NULL;
		break;
	}
	if( eq_name != NULL ){
		sn_printf( art->art_name, ITEM_ART_NAME_MAX_BYTE,
				MSG_FMT_ART_NAME_EQUIP,
				get_equip_ttl_max_len(), eq_name,
				art->name );
	} else {
		strcpy( art->art_name, art->name );
	}

	return TRUE;
}

/***************************************************************
* メンバーが料金を支払えるか調べる
* mbr_t *mbr : メンバー
* gold_t price : 料金
* return : 料金を支払えるか?
***************************************************************/

bool_t	chk_pay( mbr_t *mbr, gold_t price )
{
	gold_t	gold;

	if( mbr == NULL )
		return FALSE;

	gold = get_chr_gold( mbr );

	if( gold < price ){
		print_msg( FLG_MSG_ERR, MSG_ERR_MENU_WANTING,
				mbr->name, fmt_gold( price - gold ) );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* 商品の値段を計算
* shop_n_t shop_n : 店番号
* item_t *item : 商品
* deal_kind_t deal_kind : 取り引きの種類
* return : 商品の値段
***************************************************************/

gold_t	get_price( shop_n_t shop_n, item_t *item, deal_kind_t deal_kind )
{
	gold_t	price;

	if( item == NULL )
		return( (gold_t)0 );

	price = (gold_t)0;

	switch( item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		price = (gold_t)0;
		break;
	case ITEM_KIND_WPN:
		price = get_price_wpn( item );
		break;
	case ITEM_KIND_ARMOR:
		price = get_price_armor( item );
		break;
	case ITEM_KIND_POTION:
		if( item->tab.potion != NULL )
			price = item->tab.potion->price;
		break;
	case ITEM_KIND_SCROLL:
		if( item->tab.scroll != NULL )
			price = item->tab.scroll->price;
		break;
	case ITEM_KIND_STICK:
		price = get_price_stick( item );
		break;
	case ITEM_KIND_ACCE:
		if( item->tab.acce != NULL )
			price = item->tab.acce->price;
		break;
	case ITEM_KIND_INST:
		price = get_price_inst( item );
		break;
	case ITEM_KIND_ANTHOLOGY:
		price = PRICE_ANTHOLOGY;
		break;
	case ITEM_KIND_LIGHT:
		price = get_price_light( item );
		break;
	case ITEM_KIND_SPIKE:
		price = PRICE_SPIKE;
		break;
	case ITEM_KIND_FOOD:
		if( item->tab.food != NULL )
			price = item->tab.food->price;
		break;
	case ITEM_KIND_CHEST:
		price = PRICE_CHEST;
		break;
	case ITEM_KIND_TOBACCO:
		if( item->tab.tobacco != NULL )
			price = item->tab.tobacco->price;
		break;
	case ITEM_KIND_PIPE:
		if( item->tab.pipe != NULL )
			price = item->tab.pipe->price;
		break;
	case ITEM_KIND_DISPOSAL:
		price = PRICE_DISPOSAL;
		break;
	case ITEM_KIND_RARE_GOODS:
		price = (gold_t)0;
		break;
	case ITEM_KIND_BONE:
		price = (gold_t)0;
		break;
	case ITEM_KIND_COIN:
		price = (gold_t)1;
		break;
	case ITEM_KIND_JUNK:
		price = (gold_t)0;
		break;
	}

	if( !chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) )
		price = price * PRICE_NOT_IDENTIFIED_RATE / _100_PERCENT;
	if( chk_flg( item->flg, FLG_ITEM_CURSED ) )
		price = (gold_t)0;

	price *= item->n;

	price = discount( price, shop_n, deal_kind );

	return price;
}

/***************************************************************
* 商品の値段を割引く
* gold_t price : 割引前の値段
* shop_n_t shop_n : 店番号
* deal_kind_t deal_kind : 取り引きの種類
* return : 割引後の値段
***************************************************************/

gold_t	discount( gold_t price, shop_n_t shop_n, deal_kind_t deal_kind )
{
	switch( deal_kind ){
	case DEAL_KIND_BUY:
		if( chk_discount() && (shop_n == g_discount_queue.shop_n) )
			price -= price * DISCOUNT_RATE / _100_PERCENT;
		break;
	case DEAL_KIND_SALE_ITEM:
	case DEAL_KIND_SALE_EQUIP:
		price /= 2;
		if( chk_discount() && (shop_n == g_discount_queue.shop_n) )
			price += price * DISCOUNT_RATE / _100_PERCENT;
		break;
	}
	if( price < 1 )
		price = 1;

	return price;
}

/***************************************************************
* 武器の値段を計算
* item_t *item : 商品
* return : 値段
***************************************************************/

gold_t	get_price_wpn( item_t *item )
{
	gold_t	price;
	long	mul_type;
	rate_t	hit, crtcl, dam;
	ratio_t	ratio;
	rate_t	arw_hit, arw_crtcl, arw_dam;
	bool_t	flg_dag, flg_arw;
	long	i;

	if( item == NULL )
		return( (gold_t)0 );
	if( item->kind != ITEM_KIND_WPN )
		return( (gold_t)0 );
	if( item->tab.wpn == NULL )
		return( (gold_t)0 );
	if( chk_flg( item->flg, FLG_ITEM_CURSED) )
		return( (gold_t)0 );

	price = 0;

	/* 基本の値段 */

	flg_dag = FALSE;
	flg_arw = FALSE;
	arw_hit = 0;
	arw_crtcl = 0;
	arw_dam = 0;
	if( item->tab.wpn->bow_kind == BOW_KIND_DAGGER ){
		if( chk_flg( item->tab.wpn->flg, FLG_WPN_TAB_NOT_SPEND ) )
			price += PRICE_WPN_NOT_SPEND;
		else
			flg_dag = TRUE;
	} else if( chk_flg( item->tab.wpn->flg, FLG_WPN_TAB_ARW ) ){
		flg_arw = TRUE;
		arw_hit = 70;
		arw_crtcl = 70;
		arw_dam = 70;
	}

	hit = 0;
	crtcl = 0;
	dam = 0;
	ratio = 0;
	mul_type = 0;
	for( i = 0; i < WPN_ATTACK_MAX_N; i++ ){
		if( item->tab.wpn->attack[i].kind == ATTACK_KIND_NULL )
			break;
		hit += (item->tab.wpn->attack[i].hit + arw_hit)
				* item->tab.wpn->attack[i].ratio;
		crtcl += (item->tab.wpn->attack[i].crtcl + arw_crtcl)
				* item->tab.wpn->attack[i].ratio;
		dam += (item->tab.wpn->attack[i].dam + arw_dam)
				* item->tab.wpn->attack[i].ratio;
		ratio += item->tab.wpn->attack[i].ratio;
		mul_type++;
	}
	if( ratio <= 0 )
		return( (gold_t)0 );

	hit /= ratio;
	crtcl /= ratio;
	dam /= ratio;

	hit *= hit;
	crtcl *= crtcl;
	dam *= dam;

	price += hit * PRICE_WPN_HIT_MUL;
	price += crtcl * PRICE_WPN_CRTCL_MUL;
	price += dam * PRICE_WPN_DAM_MUL;

	price += PRICE_WPN_HIT_BASE;
	price += PRICE_WPN_CRTCL_BASE;
	price += PRICE_WPN_DAM_BASE;

	price = price * PRICE_WPN_RATE / _100_PERCENT;
	price += PRICE_WPN_BASE;

	/* 強化の度合で修整 */

	if( item->dat.wpn.add_hit < 0 )
		return( (gold_t)0 );
	if( item->dat.wpn.add_crtcl < 0 )
		return( (gold_t)0 );
	if( item->dat.wpn.add_dam < 0 )
		return( (gold_t)0 );

	if( flg_arw ){
		price += item->dat.wpn.add_hit * PRICE_ARW_ADD_HIT_MUL;
		price += item->dat.wpn.add_crtcl * PRICE_ARW_ADD_CRTCL_MUL;
		price += item->dat.wpn.add_dam * PRICE_ARW_ADD_DAM_MUL;
	} else {
		price += item->dat.wpn.add_hit * PRICE_WPN_ADD_HIT_MUL;
		price += item->dat.wpn.add_crtcl * PRICE_WPN_ADD_CRTCL_MUL;
		price += item->dat.wpn.add_dam * PRICE_WPN_ADD_DAM_MUL;

		if( item->dat.wpn.add_hit > 0 )
			price += PRICE_WPN_ADD_HIT_BASE;
		if( item->dat.wpn.add_crtcl > 0 )
			price += PRICE_WPN_ADD_CRTCL_BASE;
		if( item->dat.wpn.add_dam > 0 )
			price += PRICE_WPN_ADD_DAM_BASE;
	}

	/* 複数の攻撃タイプ */

	if( mul_type >= 2 ){
		if( flg_arw ){
			price += (mul_type - 1) * PRICE_ARW_MUL_TYPE_MUL;
		} else {
			price += (mul_type - 1) * PRICE_WPN_MUL_TYPE_MUL
					+ PRICE_WPN_MUL_TYPE_BASE;
		}
	}

	/* (旧)スレイヤー属性 */

	if( item->dat.wpn.slayer != FACE_MJR_NULL ){
		if( flg_arw ){
			price += PRICE_ARW_SLAYER;
		} else {
			price += PRICE_WPN_SLAYER;
		}
	}

	/* ランダム・アーティファクト */

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( item->dat.wpn.randm_art[i].kind
				== WPN_RANDM_ART_KIND_NULL ){
			break;
		}
		price += PRICE_WPN_RANDM_ART;
	}

	/* ダガー（投げナイフ） */

	if( flg_dag ){
		price = price / PRICE_DAGGER_DIV;
	} else if( flg_arw ){
		price = price / PRICE_ARW_DIV;
	}

	if( flg_dag || flg_arw ){
		if( price < 1 )
			price = 1;
	} else {
		if( price < PRICE_WPN_MIN )
			price = PRICE_WPN_MIN;
	}

	return price;
}

/***************************************************************
* 防具の値段を計算
* item_t *item : 商品
* return : 値段
***************************************************************/

gold_t	get_price_armor( item_t *item )
{
	gold_t	price, def, crtcl, ac;
	long	i;

	if( item == NULL )
		return( (gold_t)0 );
	if( item->kind != ITEM_KIND_ARMOR )
		return( (gold_t)0 );
	if( item->tab.armor == NULL )
		return( (gold_t)0 );

	price = 0;

	/* 基本の値段 */

	def = item->tab.armor->def;
	def *= item->tab.armor->def;
	def *= item->tab.armor->def;
	def *= PRICE_ARMOR_DEF_MUL;

	crtcl = item->tab.armor->crtcl;
	crtcl *= item->tab.armor->crtcl;
	crtcl *= item->tab.armor->crtcl;
	crtcl *= PRICE_ARMOR_CRTCL_MUL;

	ac = item->tab.armor->ac;
	ac *= item->tab.armor->ac;
	ac *= item->tab.armor->ac;
	ac *= PRICE_ARMOR_AC_MUL;

	price += def + crtcl + ac;

	if( item->tab.armor->def > 0 )
		price += PRICE_ARMOR_DEF_BASE;
	if( item->tab.armor->crtcl > 0 )
		price += PRICE_ARMOR_CRTCL_BASE;
	if( item->tab.armor->ac > 0 )
		price += PRICE_ARMOR_AC_BASE;

	price = price * PRICE_ARMOR_RATE / _100_PERCENT;
	price += PRICE_ARMOR_BASE;

	/* 強化の度合で修整 */

	if( item->dat.armor.add_def < 0 )
		return( (gold_t)0 );
	if( item->dat.armor.add_crtcl < 0 )
		return( (gold_t)0 );
	if( item->dat.armor.add_ac < 0 )
		return( (gold_t)0 );

	price += item->dat.armor.add_def * PRICE_ARMOR_ADD_DEF_MUL;
	price += item->dat.armor.add_crtcl * PRICE_ARMOR_ADD_CRTCL_MUL;
	price += item->dat.armor.add_ac * PRICE_ARMOR_ADD_AC_MUL;

	if( item->dat.armor.add_def < 0 )
		price += PRICE_ARMOR_ADD_DEF_BASE;
	if( item->dat.armor.add_crtcl < 0 )
		price += PRICE_ARMOR_ADD_CRTCL_BASE;
	if( item->dat.armor.add_ac < 0 )
		price += PRICE_ARMOR_ADD_AC_BASE;

	/* ランダム・アーティファクト */

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( item->dat.armor.randm_art[i].kind
				== ARMOR_RANDM_ART_KIND_NULL ){
			break;
		}
		price += PRICE_ARMOR_RANDM_ART;
	}

	/* データ・テーブル上の補正 */

	price = price * item->tab.armor->rate_price / _100_PERCENT;
	price += item->tab.armor->add_price;

	/**/

	return price;
}

/***************************************************************
* 魔法の杖の値段を計算
* item_t *item : 商品
* return : 値段
***************************************************************/

gold_t	get_price_stick( item_t *item )
{
	gold_t	price;

	if( item == NULL )
		return( (gold_t)0 );
	if( item->kind != ITEM_KIND_STICK )
		return( (gold_t)0 );
	if( item->tab.stick == NULL )
		return( (gold_t)0 );

	price = item->tab.stick->price;
	price *= item->dat.stick.n;

	switch( item->dat.stick.kind ){
	case STICK_KIND_NULL:
		price = 0;
		break;
	case STICK_KIND_WAND:
		price *= 1;
		break;
	case STICK_KIND_ROD:
		price *= 2;
		break;
	case STICK_KIND_STAFF:
		price *= 3;
		break;
	case STICK_KIND_MAX_N:
		price = 0;
		break;
	}

	/**/

	return price;
}

/***************************************************************
* 楽器の値段を計算
* item_t *item : 商品
* return : 値段
***************************************************************/

gold_t	get_price_inst( item_t *item )
{
	gold_t	price;

	if( item == NULL )
		return( (gold_t)0 );
	if( item->kind != ITEM_KIND_INST )
		return( (gold_t)0 );
	if( item->tab.inst == NULL )
		return( (gold_t)0 );

	price = PRICE_INST_BASE;

	if( item->dat.inst.flg_limit )
		price += PRICE_INST_LIMIT;

	if( item->dat.inst.spell_kind != SPELL_KIND_NULL )
		price += PRICE_INST_SPELL;

	/**/

	return price;
}

/***************************************************************
* 明かりの値段を計算
* item_t *item : 商品
* return : 値段
***************************************************************/

gold_t	get_price_light( item_t *item )
{
	gold_t	price;

	if( item == NULL )
		return( (gold_t)0 );
	if( item->kind != ITEM_KIND_LIGHT )
		return( (gold_t)0 );
	if( item->tab.light == NULL )
		return( (gold_t)0 );

	price = item->tab.light->base_price;

	price += item->tab.light->fill_price
			* item->dat.light.turn / item->tab.light->max_turn;

	/**/

	return price;
}

/***************************************************************
* 宿屋の料金を計算
* bool_t flg_short_stay : 休憩か?
* return : 料金
***************************************************************/

gold_t	get_price_inn( bool_t flg_short_stay )
{
	gold_t	price;

	if( flg_short_stay )
		price = CHARGE_STAY_INN_SHORT_STAY;
	else
		price = CHARGE_STAY_INN_STAY;

	price = discount( price, SHOP_N_INN, DEAL_KIND_BUY );

	return price;
}

/***************************************************************
* 寺院の解呪の料金を計算
* mbr_t *mbr : メンバー
* return : 料金
***************************************************************/

gold_t	get_price_temple_remove_curse( mbr_t *mbr )
{
	gold_t	price;

	if( mbr == NULL )
		return( (gold_t)0 );

	price = PRICE_TEMPLE_REMOVE_CURSE;

	price = discount( price, SHOP_N_TEMPLE, DEAL_KIND_BUY );

	return price;
}

/***************************************************************
* 寺院の状態回復の料金を計算
* mbr_t *mbr : メンバー
* return : 料金
***************************************************************/

gold_t	get_price_temple_cure_status( mbr_t *mbr )
{
	gold_t	price;
	rate_t	smoker;

	if( mbr == NULL )
		return( (gold_t)0 );

	price = get_specialist_lev( mbr );
	price *= PRICE_TEMPLE_CURE_STATUS_MUL;
	price += PRICE_TEMPLE_CURE_STATUS_ADD;

	smoker = mbr->fx_data.nicotine.poisoning_rate;
	smoker *= PRICE_TEMPLE_SMOKER_ADD_RATE;
	smoker /= _100_PERCENT;

	price += price * smoker / _100_PERCENT;

	price = discount( price, SHOP_N_TEMPLE, DEAL_KIND_BUY );

	return price;
}

/***************************************************************
* 寺院の復活の料金を計算
* mbr_t *mbr : メンバー
* return : 料金
***************************************************************/

gold_t	get_price_temple_resurrection( mbr_t *mbr )
{
	gold_t	price;
	rate_t	smoker;

	if( mbr == NULL )
		return( (gold_t)0 );

	price = get_specialist_lev( mbr );
	price *= PRICE_TEMPLE_RESURRECTION_MUL;
	price += PRICE_TEMPLE_RESURRECTION_ADD;

	smoker = mbr->fx_data.nicotine.poisoning_rate;
	smoker *= PRICE_TEMPLE_SMOKER_ADD_RATE;
	smoker /= _100_PERCENT;

	price += price * smoker / _100_PERCENT;

	price = discount( price, SHOP_N_TEMPLE, DEAL_KIND_BUY );

	return price;
}

/***************************************************************
* 寺院の寄付の料金を計算
* mbr_t *mbr : メンバー
* return : 料金
***************************************************************/

gold_t	get_price_temple_contribution( mbr_t *mbr )
{
	gold_t	price;

	price = get_lev( mbr, ABL_KIND_PRI );
	price *= PRICE_TEMPLE_CONTRIBUTION_PRICE_MUL;

	if( price < PRICE_TEMPLE_CONTRIBUTION_PRICE_MIN )
		price = PRICE_TEMPLE_CONTRIBUTION_PRICE_MIN;

	price = discount( price, SHOP_N_TEMPLE, DEAL_KIND_BUY );

	return price;
}

/***************************************************************
* 店の顔文字から店番号に変換
* char face_mnr : 店の顔文字
* return : 店番号
***************************************************************/

shop_n_t	get_shop_n( char face_mnr )
{
	switch( face_mnr ){
	case FACE_MNR_SHOP_INN:
		return SHOP_N_INN;
	case FACE_MNR_SHOP_BAR:
		return SHOP_N_BAR;
	case FACE_MNR_SHOP_WPN:
		return SHOP_N_WPN;
	case FACE_MNR_SHOP_ARMOR:
		return SHOP_N_ARMOR;
	case FACE_MNR_SHOP_MAGIC:
		return SHOP_N_MAGIC;
	case FACE_MNR_SHOP_TEMPLE:
		return SHOP_N_TEMPLE;
	case FACE_MNR_SHOP_ALCHEMY:
		return SHOP_N_ALCHEMY;
	case FACE_MNR_SHOP_MUSIC:
		return SHOP_N_MUSIC;
	case FACE_MNR_SHOP_GROCERY:
		return SHOP_N_GROCERY;
	case FACE_MNR_SHOP_RESTAURANT:
		return SHOP_N_RESTAURANT;
	case FACE_MNR_SHOP_TEAROOM:
		return SHOP_N_TEAROOM;
	case FACE_MNR_SHOP_TOBACCO:
		return SHOP_N_TOBACCO;
	case FACE_MNR_SHOP_PET_SHOP:
		return SHOP_N_PET_SHOP;
	}

	return SHOP_N_INN;
}

/***************************************************************
* 店番号から店の顔文字に変換
* shop_n_t n : 店番号
* return : 店の顔文字
***************************************************************/

char	get_shop_mnr_face( shop_n_t n )
{
	switch( n ){
	case SHOP_N_NULL:
	case SHOP_N_MAX_N:
		break;
	case SHOP_N_INN:
		return FACE_MNR_SHOP_INN;
	case SHOP_N_BAR:
		return FACE_MNR_SHOP_BAR;
	case SHOP_N_WPN:
		return FACE_MNR_SHOP_WPN;
	case SHOP_N_ARMOR:
		return FACE_MNR_SHOP_ARMOR;
	case SHOP_N_MAGIC:
		return FACE_MNR_SHOP_MAGIC;
	case SHOP_N_TEMPLE:
		return FACE_MNR_SHOP_TEMPLE;
	case SHOP_N_ALCHEMY:
		return FACE_MNR_SHOP_ALCHEMY;
	case SHOP_N_MUSIC:
		return FACE_MNR_SHOP_MUSIC;
	case SHOP_N_GROCERY:
		return FACE_MNR_SHOP_GROCERY;
	case SHOP_N_RESTAURANT:
		return FACE_MNR_SHOP_RESTAURANT;
	case SHOP_N_TEAROOM:
		return FACE_MNR_SHOP_TEAROOM;
	case SHOP_N_TOBACCO:
		return FACE_MNR_SHOP_TOBACCO;
	case SHOP_N_PET_SHOP:
		return FACE_MNR_SHOP_PET_SHOP;
	}

	return FACE_MNR_NULL;
}

/***************************************************************
* 店番号から店の名前に変換
* shop_n_t n : 店番号
* return : 店の名前
***************************************************************/

char	*get_shop_name( shop_n_t shop_n )
{
	switch( shop_n ){
	case SHOP_N_NULL:
	case SHOP_N_MAX_N:
		return MSG_NULL;
	case SHOP_N_BAR:
		return MSG_NAME_BAR;
	case SHOP_N_INN:
		return MSG_NAME_INN;
	case SHOP_N_WPN:
		return MSG_NAME_WPN;
	case SHOP_N_ARMOR:
		return MSG_NAME_ARMOR;
	case SHOP_N_MAGIC:
		return MSG_NAME_MAGIC;
	case SHOP_N_TEMPLE:
		return MSG_NAME_TEMPLE;
	case SHOP_N_ALCHEMY:
		return MSG_NAME_ALCHEMY;
	case SHOP_N_MUSIC:
		return MSG_NAME_MUSIC;
	case SHOP_N_GROCERY:
		return MSG_NAME_GROCERY;
	case SHOP_N_RESTAURANT:
		return MSG_NAME_RESTAURANT;
	case SHOP_N_TEAROOM:
		return MSG_NAME_TEAROOM;
	case SHOP_N_TOBACCO:
		return MSG_NAME_TOBACCO;
	case SHOP_N_PET_SHOP:
		return MSG_NAME_PET_SHOP;
	}

	return MSG_NULL;
}

/***************************************************************
* 朝焼けでマップを初期化
* long turn : ターン
***************************************************************/

void	set_map_sunshine( void )
{
	dun_t	*dun = get_dun();
	bool_t	flg_on_light;
	long	x, y;

	if( dun->lev != 0 )
		return;
	if( g_flg_night && chk_night() )
		return;
	if( !g_flg_night && !chk_night() )
		return;

	g_flg_night = chk_night();

	flg_on_light = !g_flg_night;
	if( chk_morning() )
		flg_on_light = FALSE;
	if( chk_evening() )
		flg_on_light = TRUE;

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			if( dun->map.obj.mjr[y][x] != FACE_MJR_FLOOR )
				continue;

			if( flg_on_light ){
				dun->map.obj.flg[y][x] |= FLG_MAP_OBJ_FIND;
				dun->map.light_depth_obj[y][x] = 1;
			} else {
				dun->map.obj.flg[y][x] &= ~(FLG_MAP_OBJ_FIND);
				dun->map.light_depth_obj[y][x] = 0;
			}
		}
	}

	/* 街灯を灯す */

	make_streetlamp();
}

/***************************************************************
* 朝焼けのチェック
* long turn : ターン
***************************************************************/

void	chk_morning_glow( long turn )
{
	dun_t	*dun = get_dun();
	long	n, next_morning_glow_n;

	if( dun->lev != 0 )
		return;

	next_morning_glow_n = get_glow_n( turn, TRUE );

	if( g_morning_glow_n > (next_morning_glow_n + 1) )
		g_morning_glow_n = 0;

	for( n = g_morning_glow_n; n <= next_morning_glow_n; n++ ){
		switch( n ){
		case 0:
			set_map_glow( +0, +0, TRUE );
			g_morning_glow_n++;
			break;
		case 1:
			set_map_glow( +1, +1, TRUE );
			g_morning_glow_n++;
			break;
		case 2:
			set_map_glow( +1, +0, TRUE );
			g_morning_glow_n++;
			break;
		case 3:
			set_map_glow( +0, +1, TRUE );
			g_morning_glow_n++;
			break;
		case 4:
			break;
		}
	}
}

/***************************************************************
* 夕焼けのチェック
* long turn : ターン
***************************************************************/

void	chk_evening_glow( long turn )
{
	dun_t	*dun = get_dun();
	long	n, next_evening_glow_n;

	if( dun->lev != 0 )
		return;

	next_evening_glow_n = get_glow_n( turn, FALSE );

	if( g_evening_glow_n > (next_evening_glow_n + 1) )
		g_evening_glow_n = 0;

	for( n = g_evening_glow_n; n <= next_evening_glow_n; n++ ){
		switch( n ){
		case 0:
			set_map_glow( +0, +0, FALSE );
			g_evening_glow_n++;
			break;
		case 1:
			set_map_glow( +1, +1, FALSE );
			g_evening_glow_n++;
			break;
		case 2:
			set_map_glow( +1, +0, FALSE );
			g_evening_glow_n++;
			break;
		case 3:
			set_map_glow( +0, +1, FALSE );
			g_evening_glow_n++;
			break;
		case 4:
			break;
		}
	}
}

/***************************************************************
* 朝／夕焼けの度合を返す
* long turn : ターン
* bool_t flg_morning : 朝焼けか?
* return : 朝／夕焼けの度合
***************************************************************/

long	get_glow_n( long turn, bool_t flg_morning )
{
	long	hour, n;
	long	i;

	if( flg_morning )
		hour = MORNING_HOUR * TURN_PER_HOUR;
	else
		hour = EVENING_HOUR * TURN_PER_HOUR;

	if( turn < hour )
		return 4;

	for( i = 0; i < 4; i++ ){
		n = hour + (TURN_PER_HOUR * (i + 1) / 4);
		if( turn < n )
			return i;
	}

	return 4;
}

/***************************************************************
* 朝／夕焼けを描画
* long dx : X 軸の朝焼けの相対位置
* long dy : Y 軸の朝焼けの相対位置
* bool_t flg_morning : 朝焼けか?
***************************************************************/

void	set_map_glow( long dx, long dy, bool_t flg_morning )
{
	dun_t	*dun = get_dun();
	long	x, y;

	for( y = 0; y < MAP_MAX_Y; y += 2 ){
		for( x = 0; x < MAP_MAX_X; x += 2 ){
			long	xx, yy;

			xx = x + dx;
			yy = y + dy;

			if( dun->map.obj.mjr[yy][xx] != FACE_MJR_FLOOR )
				continue;

			if( flg_morning )
				dun->map.light_depth_obj[yy][xx]++;
			else
				dun->map.light_depth_obj[yy][xx]--;

			if( calc_light_depth( xx, yy ) > 0 ){
				dun->map.obj.flg[yy][xx]
						|= FLG_MAP_OBJ_FIND;
			} else {
				dun->map.obj.flg[yy][xx]
						&= ~(FLG_MAP_OBJ_FIND);
			}
		}
	}

	redraw_map();
}

/***************************************************************
* 酒場の噂を表示
* shop_n_t n : 店番号
***************************************************************/

void	hear_rumor( shop_n_t shop_n )
{
	sex_t	sex;
	long	latest_n, randm_n, tab_n;
	long	n;
	long	i;

	if( shop_n != SHOP_N_BAR )
		return;

	if( per_randm( 2 ) )
		sex = FEMALE;
	else
		sex = MALE;

	randm_n = -1;
	latest_n = -1;
	n = 0;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( rumor_tab[i].n_msg_female == N_MSG_NULL )
			break;
		if( rumor_tab[i].n_msg_male == N_MSG_NULL )
			break;

		if( rumor_tab[i].flg_open ){
			n++;
			if( per_randm( n ) ){
				randm_n = i;
			}

			if( rumor_tab[i].flg_latest ){
				latest_n = i;
			}
		}
	}

	if( latest_n > -1 )
		tab_n = latest_n;
	else if( randm_n > -1 )
		tab_n = randm_n;
	else
		return;

	rumor_tab[tab_n].flg_latest = FALSE;

	print_words( MSG_NPC_NAME_BAR_CUSTOMER, sex,
			MSG( rumor_tab[tab_n].n_msg_female ),
			MSG( rumor_tab[tab_n].n_msg_male ) );
}

/***************************************************************
* 金を支払う
* chr_t *chr : キャラクタ
* gold_t price : 代金
***************************************************************/

void	paying_gold( chr_t *chr, gold_t price )
{
	add_chr_gold( chr, -price );
}

/***************************************************************
* 金の支払いを受ける
* chr_t *chr : キャラクタ
* gold_t price : 代金
***************************************************************/

void	paid_gold( chr_t *chr, gold_t price )
{
	add_chr_gold( chr, +price );
}

/***************************************************************
* 割引中か調べる
* return : 割引中か?
***************************************************************/

bool_t	chk_discount( void )
{
	if( !chk_discount_day() )
		return FALSE;
	if( !chk_discount_turn() )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 割引の日か調べる
* return : 割引の日か?
***************************************************************/

bool_t	chk_discount_day( void )
{
	long	day;

	day = get_game_day();

	if( (day % DAY_OF_WEEK_MAX_N) == DAY_OF_WEEK_DISCOUNT ){
		if( g_discount_queue.shop_n == SHOP_N_NULL ){
			set_discount();
		}
		return TRUE;
	} else {
		if( g_discount_queue.shop_n != SHOP_N_NULL ){
			clr_discount();
		}
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* 割引中のターンか調べる
* return : 割引中のターンか?
***************************************************************/

bool_t	chk_discount_turn()
{
	long	turn;

	turn = get_turn();

	if( g_discount_queue.shop_n == SHOP_N_NULL )
		return FALSE;
	if( g_discount_queue.flg_sold_out )
		return FALSE;

	if( turn < (DISCOUNT_BEGIN_HOUR * TURN_PER_HOUR) )
		return FALSE;
	if( turn > (DISCOUNT_END_HOUR * TURN_PER_HOUR) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 割引の日で営業時間中か調べる
* return : 営業時間中か?
***************************************************************/

bool_t	chk_discount_open()
{
	long	turn;

	turn = get_turn();

	if( !chk_discount_turn() )
		return FALSE;

	if( turn < (DISCOUNT_OPEN_HOUR * TURN_PER_HOUR) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 割引中の店のドアか調べる
* door_t *dr : ドア
* return : 割引中の店か?
***************************************************************/

bool_t	chk_discount_door( door_t *dr )
{
	if( dr == NULL )
		return FALSE;

	if( dr != g_discount_queue.door )
		return FALSE;

	return TRUE;
}

/***************************************************************
* キャラクタが行列中か調べる
* chr_t *chr : キャラクタ
* return : 行列中か?
***************************************************************/

bool_t	chk_queue_chr( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( chr->trgt.kind != TRGT_KIND_QUEUE )
		return FALSE;

	return TRUE;
}

/***************************************************************
* キャラクタが行列に引き寄せられるか調べる
* chr_t *chr : キャラクタ
* return : 引き寄せられるか?
***************************************************************/

bool_t	chk_discount_mark( chr_t *chr )
{
	long	dx, dy;

	if( chr == NULL )
		return FALSE;

	if( chr->trgt.kind == TRGT_KIND_QUEUE )
		return TRUE;
	if( !chk_discount() )
		return FALSE;
	if( chk_discount_open() )
		return FALSE;

	if( g_discount_queue.n + 1 > get_discount_queue_max_n( chr ) )
		return FALSE;

	dx = g_discount_queue.pos[g_discount_queue.n].x - chr->x;
	dy = g_discount_queue.pos[g_discount_queue.n].y - chr->y;
	if( labs( dx ) > DISCOUNT_QUEUE_R )
		return FALSE;
	if( labs( dy ) > DISCOUNT_QUEUE_R )
		return FALSE;

	mark_discount_queue( chr );
	return TRUE;
}

/***************************************************************
* 割引セールのを設定
***************************************************************/

void	set_discount( void )
{
	door_t	*dr;

	g_discount_queue.shop_n = (shop_n_t)randm( SHOP_N_MAX_N );
	g_discount_queue.flg_sold_out = FALSE;

	dr = get_shop_door( g_discount_queue.shop_n );
	if( dr == NULL )
		return;
	g_discount_queue.door = dr;

	set_discount_queue( dr );
}

/***************************************************************
* 割引セールのを解除
***************************************************************/

void	clr_discount( void )
{
	g_discount_queue.shop_n = SHOP_N_NULL;
	g_discount_queue.door = NULL;
	g_discount_queue.flg_sold_out = TRUE;
}

/***************************************************************
* 割引セールを売り切れに設定
***************************************************************/

void	set_discount_sold_out()
{
	g_discount_queue.flg_sold_out = TRUE;
}

/***************************************************************
* 行列の位置を設定
* door_t *dr : ドア
* return : 設定できたか?
***************************************************************/

bool_t	set_discount_queue( door_t *dr )
{
	dun_t	*dun = get_dun();
	long	x, y;
	long	dx, dy;
	bool_t	ret;
	long	i;

	do {
		dx = 0;
		dy = -1;
		x = dr->x - 1;
		y = dr->y;
		if( chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_PASS ) )
			break;

		dx = 0;
		dy = +1;
		x = dr->x + dr->dx;
		y = dr->y;
		if( chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_PASS ) )
			break;

		dx = +1;
		dy = 0;
		x = dr->x;
		y = dr->y - 1;
		if( chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_PASS ) )
			break;

		dx = -1;
		dy = 0;
		x = dr->x;
		y = dr->y + dr->dy;
		if( chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_PASS ) )
			break;

		return FALSE;
	} while( 0 );

	ret = TRUE;

	g_discount_queue.n = 0;
	for( i = 0; i < DISCOUNT_QUEUE_MAX_N; i++ ){
		g_discount_queue.pos[i].x = x;
		g_discount_queue.pos[i].y = y;
		g_discount_queue.chr[i] = NULL;
		x += dx;
		y += dy;
		if( !clip_pos( x, y ) ){
			ret = FALSE;
			continue;
		}

		if( dx <= -1 ){
			if( chk_flg( dun->map.obj.flg[y - 1][x],
					FLG_MAP_OBJ_PASS ) ){
				dx = 0;
				dy = -1;
			}
		} else if( dx >= +1 ){
			if( chk_flg( dun->map.obj.flg[y + 1][x],
					FLG_MAP_OBJ_PASS ) ){
				dx = 0;
				dy = +1;
			}
		} else if( dy <= -1 ){
			if( chk_flg( dun->map.obj.flg[y][x + 1],
					FLG_MAP_OBJ_PASS ) ){
				dx = +1;
				dy = 0;
			}
		} else if( dy >= +1 ){
			if( chk_flg( dun->map.obj.flg[y][x - 1],
					FLG_MAP_OBJ_PASS ) ){
				dx = -1;
				dy = 0;
			}
		}
	}

	return ret;
}

/***************************************************************
* 行列のデータを返す
* return : 行列のデータ
***************************************************************/

discount_queue_t	*get_discount_queue( void )
{
	return &g_discount_queue;
}

/***************************************************************
* 行列の人数を返す
* chr_t *chr : キャラクタ
* return : 行列の人数
***************************************************************/

long	get_discount_queue_n( chr_t *chr )
{
	if( g_discount_queue.n + 1 > get_discount_queue_max_n( chr ) )
		return -1;

	return g_discount_queue.n;
}

/***************************************************************
* 行列の最長人数を返す
* chr_t *chr : キャラクタ
* return : 行列の最長人数
***************************************************************/

long	get_discount_queue_max_n( chr_t *chr )
{
	if( is_mbr( chr ) )
		return DISCOUNT_QUEUE_MAX_N;
	else
		return DISCOUNT_QUEUE_MAX_N - MBR_MAX_N;
}

/***************************************************************
* 行列を進めるか調べる
***************************************************************/

void	chk_discount_queue( void )
{
	long	i;

	for( i = 0; i < g_discount_queue.n; i++ ){
		chr_t	*chr;

		chr = g_discount_queue.chr[i];
		if( chr == NULL )
			continue;

		if( chr->trgt.kind != TRGT_KIND_QUEUE )
			dec_discount_queue( i );
	}
}

/***************************************************************
* キャラクタが行列をやめたか調べる
* chr_t *chr : キャラクタ
***************************************************************/

void	chk_clr_chr_discount_queue( chr_t *chr )
{
	if( chr == NULL )
		return;
	if( chr->trgt.kind != TRGT_KIND_QUEUE )
		return;

	if( chk_discount() )
		return;

	dec_discount_queue( chr->trgt.n );
	clr_chr_trgt_act( chr, FALSE );
}

/***************************************************************
* 行列中のキャラクタが店に入ったか調べる
* chr_t *chr : キャラクタ
***************************************************************/

void	chk_enter_discount_shop( chr_t *chr )
{
	if( chr == NULL )
		return;
	if( chr->trgt.kind != TRGT_KIND_QUEUE )
		return;

	if( !chk_discount() )
		return;
	if( !chk_discount_open() )
		return;

	dec_discount_queue( chr->trgt.n );
	set_chr_act( chr, ACT_KIND_DOOR_OPEN, NULL, NULL, 0, 0 );
	mark_door( chr, g_discount_queue.door, DIST_NEAR );
}

/***************************************************************
* キャラクタが行列にならぶ
* chr_t *chr : キャラクタ
***************************************************************/

void	inc_discount_queue( chr_t *chr )
{
	if( chr == NULL )
		return;
	if( g_discount_queue.n + 1 > get_discount_queue_max_n( chr ) )
		return;

	g_discount_queue.chr[g_discount_queue.n] = chr;
	g_discount_queue.n++;

	if( is_mbr( chr ) )
		print_msg( FLG_NULL, MSG_INC_DISCOUNT_QUEUE, chr->name );
}

/***************************************************************
* 行列を進める
* long n : 行列の順番
***************************************************************/

void	dec_discount_queue( long n )
{
	long	i;

	if( n <= 0 )
		return;

	for( i = n + 1; i < g_discount_queue.n; i++ ){
		if( g_discount_queue.chr[i] == NULL )
			continue;

		g_discount_queue.chr[i]->trgt.n = i - 1;
		g_discount_queue.chr[i - 1] = g_discount_queue.chr[i];
	}
	g_discount_queue.chr[i - 1] = NULL;

	g_discount_queue.n--;
	if( g_discount_queue.n < 0 )
		g_discount_queue.n = 0;
}

/***************************************************************
* パーティが店の中に居るか調べる
***************************************************************/

bool_t	chk_party_in_shop( void )
{
	if( get_cur_shop_n() != SHOP_N_NULL )
		return TRUE;

	if( get_scene() == SCENE_N_SHOP )
		return TRUE;

	return FALSE;
}

/***************************************************************
* 店番号から店のドアに変換
* shop_n_t n : 店番号
***************************************************************/

door_t	*get_shop_door( shop_n_t n )
{
	dun_t	*dun = get_dun();
	char	mnr;
	door_t	*dr;
	long	i;

	mnr = get_shop_mnr_face( n );

	for( i = 0; i < dun->door_n; i++ ){
		dr = &(dun->door[i]);
		if( dr->mnr == mnr )
			return dr;
	}

	return NULL;
}

/***************************************************************
* パターンの色テーブルを返す
* return : パターンの色テーブル
***************************************************************/

town_ptn_col_tab_t	*get_town_ptn_col_tab( void )
{
	return town_ptn_col_tab;
}

/***************************************************************
* パターンの色テーブルの最大数を返す
* return : パターンの色テーブルの最大数
***************************************************************/

long	get_town_ptn_col_tab_max_n( void )
{
	return town_ptn_col_tab_max_n;
}

/***************************************************************
* ペット・ショップのペットのリストを返す
* return : ペットのリスト
***************************************************************/

art_ls_pet_shop_t	*get_art_ls_pet_shop( void )
{
	return art_ls_pet_shop;
}

/***************************************************************
* 街データをセーブ
* return : エラーが無かったか？
***************************************************************/

bool_t	save_town( void )
{
	if( !save_town_ptn( &town_ptn ) ){
		print_msg( FLG_MSG_ERR, MSG_S, MSG_ERR_SAVE_TOWN_PTN );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_town_c( void )
{
	check_memory( check_memory_town_c_g_discount_queue,
			"town.c: g_discount_queue" );
	check_memory( check_memory_town_c_town_ptn,
			"town.c: town_ptn" );
	check_memory( check_memory_town_c_g_morning_glow_n,
			"town.c: g_morning_glow_n" );
	check_memory( check_memory_town_c_g_flg_night,
			"town.c: g_flg_night" );
}
