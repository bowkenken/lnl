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
* $Id: item.c,v 1.189 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* アイテム
***************************************************************/

#define	ITEM_C
#include	"inc.h"

/**/

#define	ITEM_MAX_N	((DUN_ITEM_AVE_N * 8) \
		+ (MBR_ITEM_MAX_N * LS_MBR_MAX_N) \
		+ (MNSTR_MAX_N * 4))

#define	ITEM_NEAR_R	4

#if	0
# define	ADD_SLAYER_RATE	((rate_t)1)
#else
# define	ADD_SLAYER_RATE	((rate_t)0)
#endif

#define	FLG_TEST_WPN_ADD	0
#define	FLG_TEST_ARMOR_ADD	0

#define	FLG_RANDM_ART_NAME_MAX_N_DOT	0
#define	FLG_TEST_RANDM_ART	0
#define	TEST_RANDM_ART_N	5
#define	WPN_RANDM_ART_RATE	((rate_t)90)
#define	ARMOR_RANDM_ART_RATE	((rate_t)90)

#define	CHEST_MIN_LEV	5
#define	CHEST_MAX_LEV	DUN_MAX_LEV_BASE
#define	CHEST_HOLD_MAX_LEV	100

#define	COIN_N_MUL	2
#define	COIN_N_ADD	10

#define	BREAK_ITEM_CONTENTS_RATE	10

#define	WPN_MIN_HIT	50
#define	WPN_MAX_HIT	100
#define	WPN_MIN_DAM	50
#define	WPN_MAX_DAM	100
#define	WPN_MIN_CRTCL	5
#define	WPN_MAX_CRTCL	10

#define	ARMOR_RESI_RATE_MUL	1
#define	ARMOR_RESI_RATE_ADD	0
#define	INST_LIMIT_RATE_MUL	1
#define	INST_LIMIT_RATE_ADD	0
#define	INST_SPELL_RATE_MUL	1
#define	INST_SPELL_RATE_ADD	0

#define	STICK_USE_N_WAND_RATE	6
#define	STICK_USE_N_WAND_ADD	6
#define	STICK_USE_N_ROD_RATE	4
#define	STICK_USE_N_ROD_ADD	4
#define	STICK_USE_N_STAFF_RATE	2
#define	STICK_USE_N_STAFF_ADD	2

#define	LIGHT_MAX_TURN_TORCH	3000
#define	LIGHT_MAX_TURN_LANTERN	5000
#define	LIGHT_MAX_TURN_LAMP	5000

#define	DISPOSAL_MAX_N	40

static item_t	item_buf[ITEM_MAX_N];
check_memory_def( check_memory_item_c_item_buf )
static item_t	item_free;
check_memory_def( check_memory_item_c_item_free )
static item_t	mbr_item_asgn[LS_MBR_MAX_N];
check_memory_def( check_memory_item_c_mbr_item_asgn )
static item_t	mbr_item_asgn_equip[LS_MBR_MAX_N][EQUIP_KIND_MAX_N];
check_memory_def( check_memory_item_c_mbr_item_asgn_equip )
static item_t	dun_item_asgn;
static item_t	shop_bar_item_asgn;
static item_t	shop_wpn_item_asgn;
static item_t	shop_armor_item_asgn;
static item_t	shop_temple_item_asgn;
static item_t	shop_alchemy_item_asgn;
static item_t	shop_music_item_asgn;
static item_t	shop_grocery_item_asgn;
static item_t	shop_restaurant_item_asgn;
static item_t	shop_tearoom_item_asgn;
static item_t	shop_tobacco_item_asgn;
check_memory_def( check_memory_item_c_dun_item_asgn )

static long	wpn_tab_max_n;
static long	armor_tab_max_n;
static long	potion_tab_max_n;
static long	scroll_tab_max_n;
static long	stick_tab_max_n;
static long	acce_tab_max_n;
static long	inst_tab_max_n;
static long	anthology_tab_max_n;
static long	light_tab_max_n;
static long	food_tab_max_n;
static long	tobacco_tab_max_n;
static long	pipe_tab_max_n;
static long	rare_goods_tab_max_n;
static long	coin_tab_max_n;
check_memory_def( check_memory_item_c_wpn_tab_max_n )

static n_msg_t	ls_msg_chk_item_data[ABL_KIND_MAX_N] = {
	N_MSG_NULL,
	N_MSG_NULL,

	N_MSG_NULL,
	N_MSG_NULL,
	N_MSG_NULL,

	N_MSG_NULL,
	N_MSG_NULL,
	N_MSG_NULL,

	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_FIG,
	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_MON,
	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_HUN,
	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_THI,

	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_MAG,
	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_SOR,
	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_ENC,
	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_SUM,

	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_PRI,
	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_SHA,
	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_BAR,
	N_MSG_CHK_ITEM_DATA_CAN_NOT_USE_NIN,
};
check_memory_def( check_memory_item_c_ls_msg_chk_item_data )

#include	"item-tab.h"

/**/

void	init_item( void )
{
	long	i;

	reset_item();

	for( i = 0; i < ITEM_KIND_MAX_N; i++ )
		if( item_ratio_tab[i].kind == ITEM_KIND_NULL )
			break;
	if( i != (ITEM_KIND_MAX_N - 1) ){
		print_err( MSG_ERR_ITEM_RATIO, i, ITEM_KIND_MAX_N - 1 );
		exit_game( EXIT_FAILURE );
	}

	/* 武器 */
	init_wpn();

	/* 鎧 */
	init_armor();

	/* 薬 */
	init_potion();

	/* 巻物 */
	init_scroll();

	/* 杖 */
	init_stick();

	/* アクセサリ */
	init_acce();

	/* 楽器 */
	init_inst();

	/* 詩集 */
	init_anthology();

	/* 明り */
	init_light();

	/* 食料 */
	init_food();

	/* 煙草 */
	init_tobacco();

	/* パイプ */
	init_pipe();

	/* 依頼アイテム */
	init_rare_goods();

	/* 骨 */
	init_bone();

	/* 金 */
	init_coin();
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_item( void )
{
}

/**/

void	reset_item( void )
{
	long	i, j;

	i = 0;
	item_free.next = &(item_buf[i]);
	item_buf[i].prev = &item_free;
	item_buf[i].next = &(item_buf[i + 1]);
	for( i++; i < ITEM_MAX_N - 1; i++ ){
		item_buf[i].prev = &(item_buf[i - 1]);
		item_buf[i].next = &(item_buf[i + 1]);
	}
	item_buf[i].prev = &(item_buf[i - 1]);
	item_buf[i].next = &item_free;
	item_free.prev = &item_buf[i];

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		mbr_item_asgn[i].prev = &(mbr_item_asgn[i]);
		mbr_item_asgn[i].next = &(mbr_item_asgn[i]);

		for( j = 0; j < EQUIP_KIND_MAX_N; j++ ){
			mbr_item_asgn_equip[i][j].kind
					= ITEM_KIND_NULL;
		}
	}

	dun_item_asgn.prev = &dun_item_asgn;
	dun_item_asgn.next = &dun_item_asgn;

	init_item_town();
}

/**/

void	close_item( void )
{
	free_mem( color_tab );
	free_mem( wand_material_tab );
	free_mem( rod_material_tab );
	free_mem( staff_material_tab );
	free_mem( ring_material_tab );
	free_mem( amulet_material_tab );
	free_mem( necklace_material_tab );

	color_tab = NULL;
	wand_material_tab = NULL;
	rod_material_tab = NULL;
	staff_material_tab = NULL;
	ring_material_tab = NULL;
	amulet_material_tab = NULL;
	necklace_material_tab = NULL;
}

/**/

void	init_wpn( void )
{
	long	i;

	wpn_tab_max_n = sizeof( wpn_tab ) / sizeof( wpn_tab[0] );
	for( i = 0; i < wpn_tab_max_n; i++ ){
		if( wpn_tab[i].name_n == N_MSG_NULL )
			break;
		wpn_tab[i].name = MSG( wpn_tab[i].name_n );
		wpn_tab[i].i_name = MSG( wpn_tab[i].i_name_n );
	}
	wpn_tab_max_n = i;
}

/**/

void	init_armor( void )
{
	long	i;

	armor_tab_max_n = sizeof( armor_tab ) / sizeof( armor_tab[0] );
	for( i = 0; i < armor_tab_max_n; i++ ){
		if( armor_tab[i].name_n == N_MSG_NULL )
			break;
		armor_tab[i].name = MSG( armor_tab[i].name_n );
		armor_tab[i].i_name = MSG( armor_tab[i].i_name_n );
	}
	armor_tab_max_n = i;
}

/**/

void	init_potion( void )
{
	init_color_tab();

	reset_potion_tab();
	reset_potion_color();
}

/**/

void	init_color_tab( void )
{
	long	i;
	long	mem_siz;

	/* 色インデックス・テーブルのサイズを数える */

	color_tab_max_n = sizeof( color_idx_tab );
	color_tab_max_n /= sizeof( color_idx_tab[0] );

	for( i = 0; i < color_tab_max_n; i++ )
		if( color_idx_tab[i] == N_MSG_NULL )
			break;
	color_tab_max_n = i;

	/* 色テーブルのメモリーを割り当て */

	mem_siz = (color_tab_max_n + 1) * sizeof( ls_identified_t );
	color_tab = (ls_identified_t *)alloc_mem( mem_siz, TRUE );

	/* 色テーブルの初期化 */

	for( i = 0; i < color_tab_max_n; i++ ){
		color_tab[i].name_idx = i;
		color_tab[i].flg_used = FALSE;
	}
	color_tab[i].name_idx = -1;
	color_tab[i].flg_used = TRUE;

	/* 色テーブルをシャッフル */

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		long	n1, n2;
		n_msg_idx_t	idx;

		n1 = randm( color_tab_max_n );
		n2 = randm( color_tab_max_n );

		idx = color_tab[n1].name_idx;
		color_tab[n1].name_idx = color_tab[n2].name_idx;
		color_tab[n2].name_idx = idx;
	}
}

/**/

void	reset_potion_tab( void )
{
	long	i, j;

	/* 薬のテーブルのサイズを数える */

	potion_tab_max_n = sizeof( potion_tab ) / sizeof( potion_tab[0] );
	for( i = 0; i < potion_tab_max_n; i++ )
		if( potion_tab[i].name_n == N_MSG_NULL )
			break;
	potion_tab_max_n = i;

	if( potion_tab_max_n > color_tab_max_n ){
		print_err( MSG_S, MSG_ERR_POTION_COLOR );
		exit_game( EXIT_FAILURE );
	}

	for( i = 0; i < potion_tab_max_n; i++ ){
		if( potion_tab[i].name_n == N_MSG_NULL )
			break;

		/* 薬の名前を初期化 */

		potion_tab[i].name = MSG( potion_tab[i].name_n );

		/* デフォルトの色が無いか? */

		if( potion_tab[i].color_n == N_MSG_NULL )
			continue;

		/* デフォルトの色をセット */

		potion_tab[i].color = MSG( potion_tab[i].color_n );

		/* デフォルトの色を使用済みにする */

		for( j = 0; j < color_tab_max_n; j++ ){
			n_msg_t	color_n;

			color_n = color_idx_tab[color_tab[j].name_idx];
			if( color_n == potion_tab[i].color_n ){
				color_tab[j].flg_used = TRUE;
				break;
			}
		}
	}
}

/**/

void	reset_potion_color( void )
{
	long	i, j;
	long	head;

	head = 0;

	for( i = 0; i < potion_tab_max_n; i++ ){
		/* デフォルトの色が有るか? */

		if( potion_tab[i].color_n != N_MSG_NULL )
			continue;

		for( j = head; j < color_tab_max_n; j++ ){
			n_msg_t	color_n;

			if( color_tab[j].flg_used )
				continue;

			color_n = color_idx_tab[color_tab[j].name_idx];
			potion_tab[i].color = MSG( color_n );

			color_tab[j].flg_used = TRUE;
			head = j;

			break;
		}
		if( potion_tab[i].color == NULL ){
			print_err( MSG_S, MSG_ERR_POTION_COLOR );
			exit_game( EXIT_FAILURE );
		}
	}
}

/**/

void	init_scroll( void )
{
	init_ttl_syllable_tab();
	init_scroll_tab();

	reset_scroll_ttl_syllable();
}

/**/

void	init_ttl_syllable_tab( void )
{
	long	i;

	/* 音節インデックス・テーブルのサイズを数える */

	ttl_syllable_tab_max_n = sizeof( ttl_syllable_idx_tab );
	ttl_syllable_tab_max_n /= sizeof( ttl_syllable_idx_tab[0] );

	for( i = 0; i < ttl_syllable_tab_max_n; i++ )
		if( ttl_syllable_idx_tab[i] == N_MSG_NULL )
			break;
	ttl_syllable_tab_max_n = i;
}

/**/

void	init_scroll_tab( void )
{
	long	i, j;

	/* 巻物のテーブルのサイズを数える */

	scroll_tab_max_n = sizeof( scroll_tab ) / sizeof( scroll_tab[0] );
	for( i = 0; i < scroll_tab_max_n; i++ )
		if( scroll_tab[i].name_n == N_MSG_NULL )
			break;
	scroll_tab_max_n = i;

	for( i = 0; i < scroll_tab_max_n; i++ ){
		if( scroll_tab[i].name_n == N_MSG_NULL )
			break;

		/* 巻物の名前を初期化 */

		scroll_tab[i].name = MSG( scroll_tab[i].name_n );
	}

	/* 巻物の名前をランダムに初期化 */

	for( i = 0; i < scroll_tab_max_n; i++ ){
		long	ttl_n;

		/* 音節の数を乱数で決める */

		ttl_n = randm( SCROLL_TTL_SYLLABLE_MAX_N ) + 1;
		scroll_tab[i].ttl_n = ttl_n;

		/* 音節の数だけまわる */

		for( j = 0; j < ttl_n; j++ ){
			n_msg_idx_t	idx;

			/* 音節の種類を乱数で決める */

			idx = randm( ttl_syllable_tab_max_n );

			scroll_tab[i].ttl_idx[j] = idx;
		}
		scroll_tab[i].ttl_idx[j] = -1;
	}
}

/**/

void	reset_scroll_ttl_syllable( void )
{
	long	i, j;

	for( i = 0; i < scroll_tab_max_n; i++ ){
		long	ttl_n;
		long	len_div;

		len_div = str_len_std( MSG_SCROLL_TTL_SYLLABLE_DIV );
		ttl_n = scroll_tab[i].ttl_n;

		/* 音節の数だけまわる */

		scroll_tab[i].ttl[0] = '\0';
		for( j = 0; j < ttl_n; j++ ){
			n_msg_idx_t	idx;
			char	*msg;
			long	len;

			/* 音節をテーブルから引く */

			idx = scroll_tab[i].ttl_idx[j];
			msg = MSG( ttl_syllable_idx_tab[idx] );

			/* タイトルの残りの長さを得る */

			len = SCROLL_TTL_MAX_BYTE
					- str_len_std( scroll_tab[i].ttl );

			/* タイトルのバッファがいっぱいなら終了 */

			if( j > 0 )
				len -= len_div;
			if( len < str_len_std( msg ) )
				break;

			/* タイトルに音節の区切りを足す */

			if( j > 0 ){
				strcat( scroll_tab[i].ttl,
						MSG_SCROLL_TTL_SYLLABLE_DIV );
			}

			/* タイトルに音節を足す */

			strcat( scroll_tab[i].ttl, msg );
		}
	}
}

/**/

void	init_stick( void )
{
	init_wand_material_tab();
	init_rod_material_tab();
	init_staff_material_tab();

	/**/

	reset_wand_tab();
	reset_rod_tab();
	reset_staff_tab();

	/**/

	reset_wand_material();
	reset_rod_material();
	reset_staff_material();
}

/**/

void	init_wand_material_tab( void )
{
	init_stick_material_tab(
			STICK_KIND_WAND,
			&wand_material_tab_max_n,
			&wand_material_tab,
			stick_material_idx_tab );
}

/**/

void	init_rod_material_tab( void )
{
	init_stick_material_tab(
			STICK_KIND_ROD,
			&rod_material_tab_max_n,
			&rod_material_tab,
			stick_material_idx_tab );
}

/**/

void	init_staff_material_tab( void )
{
	init_stick_material_tab(
			STICK_KIND_STAFF,
			&staff_material_tab_max_n,
			&staff_material_tab,
			stick_material_idx_tab );
}

/**/

void	reset_wand_tab( void )
{
	reset_stick_tab(
			STICK_KIND_WAND,
			&wand_material_tab_max_n,
			wand_material_tab,
			stick_material_idx_tab );
}

/**/

void	reset_rod_tab( void )
{
	reset_stick_tab(
			STICK_KIND_ROD,
			&rod_material_tab_max_n,
			rod_material_tab,
			stick_material_idx_tab );
}

/**/

void	reset_staff_tab( void )
{
	reset_stick_tab(
			STICK_KIND_STAFF,
			&staff_material_tab_max_n,
			staff_material_tab,
			stick_material_idx_tab );
}

/**/

void	reset_wand_material( void )
{
	reset_stick_material(
			STICK_KIND_WAND,
			&wand_material_tab_max_n,
			wand_material_tab,
			stick_material_idx_tab );
}

/**/

void	reset_rod_material( void )
{
	reset_stick_material(
			STICK_KIND_ROD,
			&rod_material_tab_max_n,
			rod_material_tab,
			stick_material_idx_tab );
}

/**/

void	reset_staff_material( void )
{
	reset_stick_material(
			STICK_KIND_STAFF,
			&staff_material_tab_max_n,
			staff_material_tab,
			stick_material_idx_tab );
}

/**/

void	init_stick_material_tab(
	stick_kind_t kind,
	long *max_n,
	ls_identified_t **tab_p, n_msg_t *idx_tab
)
{
	long	i;
	long	mem_siz;
	ls_identified_t	*tab;

	/* 材質インデックス・テーブルのサイズを数える */

	for( i = 0; i < LOOP_MAX_1000; i++ )
		if( idx_tab[i] == N_MSG_NULL )
			break;
	*max_n = i;

	/* 材質テーブルのメモリーを割り当て */

	mem_siz = (*max_n + 1) * sizeof( ls_identified_t );
	tab = (ls_identified_t *)alloc_mem( mem_siz, TRUE );

	/* 材質テーブルの初期化 */

	for( i = 0; i < *max_n; i++ ){
		tab[i].name_idx = i;
		tab[i].flg_used = FALSE;
	}
	tab[i].name_idx = -1;
	tab[i].flg_used = TRUE;

	/* 材質テーブルをシャッフル */

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		long	n1, n2;
		n_msg_idx_t	idx;

		n1 = randm( *max_n );
		n2 = randm( *max_n );

		idx = tab[n1].name_idx;
		tab[n1].name_idx = tab[n2].name_idx;
		tab[n2].name_idx = idx;
	}

	*tab_p = tab;
}

/**/

void	reset_stick_tab(
	stick_kind_t kind,
	long *max_n,
	ls_identified_t *tab, n_msg_t *idx_tab
)
{
	long	i, j;

	/* 杖のテーブルのサイズを数える */

	stick_tab_max_n = sizeof( stick_tab ) / sizeof( stick_tab[0] );
	for( i = 0; i < stick_tab_max_n; i++ ){
		if( stick_tab[i].name_n == N_MSG_NULL )
			break;
	}
	stick_tab_max_n = i;

	for( i = 0; i < stick_tab_max_n; i++ ){
		if( stick_tab[i].name_n == N_MSG_NULL )
			break;
		if( stick_tab[i].kind != kind )
			continue;

		/* 杖の名前を初期化 */

		stick_tab[i].name = MSG( stick_tab[i].name_n );

		/* デフォルトの材質が無いか? */

		if( stick_tab[i].material_n == N_MSG_NULL )
			continue;

		/* デフォルトの材質をセット */

		stick_tab[i].material = MSG( stick_tab[i].material_n );

		/* デフォルトの材質を使用済みにする */

		for( j = 0; j < *max_n; j++ ){
			n_msg_t	material_n;

			material_n = idx_tab[tab[j].name_idx];
			if( material_n == stick_tab[i].material_n ){
				tab[j].flg_used = TRUE;
				break;
			}
		}
	}
}

/**/

void	reset_stick_material(
	stick_kind_t kind,
	long *max_n,
	ls_identified_t *tab, n_msg_t *idx_tab
)
{
	long	i, j;
	long	head;

	head = 0;

	for( i = 0; i < stick_tab_max_n; i++ ){
		/* デフォルトの材質が有るか? */

		if( stick_tab[i].material_n != N_MSG_NULL )
			continue;
		if( stick_tab[i].kind != kind )
			continue;

		for( j = head; j < *max_n; j++ ){
			n_msg_t	material_n;

			if( tab[j].flg_used )
				continue;

			material_n = idx_tab[tab[j].name_idx];
			stick_tab[i].material = MSG( material_n );

			tab[j].flg_used = TRUE;
			head = j;

			break;
		}
		if( stick_tab[i].material == NULL ){
			print_err( MSG_S, MSG_ERR_STICK_MATERIAL );
			exit_game( EXIT_FAILURE );
		}
	}
}

/**/

void	init_acce( void )
{
	init_ring_material_tab();
	init_amulet_material_tab();
	init_necklace_material_tab();

	/**/

	reset_ring_tab();
	reset_amulet_tab();
	reset_necklace_tab();

	/**/

	reset_ring_material();
	reset_amulet_material();
	reset_necklace_material();
}

/**/

void	init_ring_material_tab( void )
{
	init_acce_material_tab(
			ACCE_KIND_RING,
			&ring_material_tab_max_n,
			&ring_material_tab,
			acce_material_idx_tab );
}

/**/

void	init_amulet_material_tab( void )
{
	init_acce_material_tab(
			ACCE_KIND_AMULET,
			&amulet_material_tab_max_n,
			&amulet_material_tab,
			acce_material_idx_tab );
}

/**/

void	init_necklace_material_tab( void )
{
	init_acce_material_tab(
			ACCE_KIND_NECKLACE,
			&necklace_material_tab_max_n,
			&necklace_material_tab,
			acce_material_idx_tab );
}

/**/

void	reset_ring_tab( void )
{
	reset_acce_tab(
			ACCE_KIND_RING,
			&ring_material_tab_max_n,
			ring_material_tab,
			acce_material_idx_tab );
}

/**/

void	reset_amulet_tab( void )
{
	reset_acce_tab(
			ACCE_KIND_AMULET,
			&amulet_material_tab_max_n,
			amulet_material_tab,
			acce_material_idx_tab );
}

/**/

void	reset_necklace_tab( void )
{
	reset_acce_tab(
			ACCE_KIND_NECKLACE,
			&necklace_material_tab_max_n,
			necklace_material_tab,
			acce_material_idx_tab );
}

/**/

void	reset_ring_material( void )
{
	reset_acce_material(
			ACCE_KIND_RING,
			&ring_material_tab_max_n,
			ring_material_tab,
			acce_material_idx_tab );
}

/**/

void	reset_amulet_material( void )
{
	reset_acce_material(
			ACCE_KIND_AMULET,
			&amulet_material_tab_max_n,
			amulet_material_tab,
			acce_material_idx_tab );
}

/**/

void	reset_necklace_material( void )
{
	reset_acce_material(
			ACCE_KIND_NECKLACE,
			&necklace_material_tab_max_n,
			necklace_material_tab,
			acce_material_idx_tab );
}

/**/

void	init_acce_material_tab(
	acce_kind_t kind,
	long *max_n,
	ls_identified_t **tab_p, n_msg_t *idx_tab
)
{
	long	i;
	long	mem_siz;
	ls_identified_t	*tab;

	/* 材質インデックス・テーブルのサイズを数える */

	for( i = 0; i < LOOP_MAX_1000; i++ )
		if( idx_tab[i] == N_MSG_NULL )
			break;
	*max_n = i;

	/* 材質テーブルのメモリーを割り当て */

	mem_siz = (*max_n + 1) * sizeof( ls_identified_t );
	tab = (ls_identified_t *)alloc_mem( mem_siz, TRUE );

	/* 材質テーブルの初期化 */

	for( i = 0; i < *max_n; i++ ){
		tab[i].name_idx = i;
		tab[i].flg_used = FALSE;
	}
	tab[i].name_idx = -1;
	tab[i].flg_used = TRUE;

	/* 材質テーブルをシャッフル */

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		long	n1, n2;
		n_msg_idx_t	idx;

		n1 = randm( *max_n );
		n2 = randm( *max_n );

		idx = tab[n1].name_idx;
		tab[n1].name_idx = tab[n2].name_idx;
		tab[n2].name_idx = idx;
	}

	*tab_p = tab;
}

/**/

void	reset_acce_tab(
	acce_kind_t kind,
	long *max_n,
	ls_identified_t *tab, n_msg_t *idx_tab
)
{
	long	i, j;

	/* アクセサリのテーブルのサイズを数える */

	acce_tab_max_n = sizeof( acce_tab ) / sizeof( acce_tab[0] );
	for( i = 0; i < acce_tab_max_n; i++ ){
		if( acce_tab[i].name_n == N_MSG_NULL )
			break;
	}
	acce_tab_max_n = i;

	for( i = 0; i < acce_tab_max_n; i++ ){
		if( acce_tab[i].name_n == N_MSG_NULL )
			break;
		if( acce_tab[i].kind != kind )
			continue;

		/* アクセサリの名前を初期化 */

		acce_tab[i].name = MSG( acce_tab[i].name_n );

		/* デフォルトの材質が無いか? */

		if( acce_tab[i].material_n == N_MSG_NULL )
			continue;

		/* デフォルトの材質をセット */

		acce_tab[i].material = MSG( acce_tab[i].material_n );

		/* デフォルトの材質を使用済みにする */

		for( j = 0; j < *max_n; j++ ){
			n_msg_t	material_n;

			material_n = idx_tab[tab[j].name_idx];
			if( material_n == acce_tab[i].material_n ){
				tab[j].flg_used = TRUE;
				break;
			}
		}
	}
}

/**/

void	reset_acce_material(
	acce_kind_t kind,
	long *max_n,
	ls_identified_t *tab, n_msg_t *idx_tab
)
{
	long	i, j;
	long	head;

	head = 0;

	for( i = 0; i < acce_tab_max_n; i++ ){
		/* デフォルトの材質が有るか? */

		if( acce_tab[i].material_n != N_MSG_NULL )
			continue;
		if( acce_tab[i].kind != kind )
			continue;

		for( j = head; j < *max_n; j++ ){
			n_msg_t	material_n;

			if( tab[j].flg_used )
				continue;

			material_n = idx_tab[tab[j].name_idx];
			acce_tab[i].material = MSG( material_n );

			tab[j].flg_used = TRUE;
			head = j;

			break;
		}
		if( acce_tab[i].material == NULL ){
			print_err( MSG_S, MSG_ERR_ACCE_MATERIAL );
			exit_game( EXIT_FAILURE );
		}
	}
}

/**/

void	init_inst( void )
{
	long	i;

	inst_tab_max_n = sizeof( inst_tab ) / sizeof( inst_tab[0] );
	for( i = 0; i < inst_tab_max_n; i++ ){
		if( inst_tab[i].name_n == N_MSG_NULL )
			break;

		inst_tab[i].name = MSG( inst_tab[i].name_n );
	}
	inst_tab_max_n = i;
}

/**/

void	init_anthology( void )
{
	long	i;

	anthology_tab_max_n = sizeof( anthology_tab )
			/ sizeof( anthology_tab[0] );
	for( i = 0; i < anthology_tab_max_n; i++ ){
		if( anthology_tab[i].name_n == N_MSG_NULL )
			break;

		anthology_tab[i].name = MSG( anthology_tab[i].name_n );
	}
	anthology_tab_max_n = i;
}

/**/

void	init_light( void )
{
	long	i;

	light_tab_max_n = sizeof( light_tab ) / sizeof( light_tab[0] );
	for( i = 0; i < light_tab_max_n; i++ ){
		if( light_tab[i].name_n == N_MSG_NULL )
			break;

		light_tab[i].name = MSG( light_tab[i].name_n );
		light_tab[i].i_name = MSG( light_tab[i].i_name_n );
	}
	light_tab_max_n = i;
}

/**/

void	init_food( void )
{
	long	i;

	food_tab_max_n = sizeof( food_tab ) / sizeof( food_tab[0] );
	for( i = 0; i < food_tab_max_n; i++ ){
		if( food_tab[i].name_n == N_MSG_NULL )
			break;

		food_tab[i].name = MSG( food_tab[i].name_n );
	}
	food_tab_max_n = i;
}

/**/

void	init_tobacco( void )
{
	long	i;

	tobacco_tab_max_n = sizeof( tobacco_tab ) / sizeof( tobacco_tab[0] );
	for( i = 0; i < tobacco_tab_max_n; i++ ){
		if( tobacco_tab[i].name_n == N_MSG_NULL )
			break;

		tobacco_tab[i].name = MSG( tobacco_tab[i].name_n );
		tobacco_tab[i].brand_name
				= MSG( tobacco_tab[i].brand_name_n );
	}
	tobacco_tab_max_n = i;
}

/**/

void	init_pipe( void )
{
	long	i;

	pipe_tab_max_n = sizeof( pipe_tab ) / sizeof( pipe_tab[0] );
	for( i = 0; i < pipe_tab_max_n; i++ ){
		if( pipe_tab[i].name_n == N_MSG_NULL )
			break;

		pipe_tab[i].name = MSG( pipe_tab[i].name_n );
	}
	pipe_tab_max_n = i;
}

/**/

void	init_rare_goods( void )
{
	long	i;

	rare_goods_tab_max_n = sizeof( rare_goods_tab )
			/ sizeof( rare_goods_tab[0] );
	for( i = 0; i < rare_goods_tab_max_n; i++ ){
		if( rare_goods_tab[i].name_n == N_MSG_NULL )
			break;

		rare_goods_tab[i].name = MSG( rare_goods_tab[i].name_n );
	}
	rare_goods_tab_max_n = i;
}

/**/

void	init_bone( void )
{
}

/**/

void	init_coin( void )
{
	long	i;

	coin_tab_max_n = sizeof( coin_tab ) / sizeof( coin_tab[0] );
	for( i = 0; i < coin_tab_max_n; i++ ){
		if( coin_tab[i].name_n == N_MSG_NULL )
			break;

		coin_tab[i].name = MSG( coin_tab[i].name_n );
	}
	coin_tab_max_n = i;
}

/**/

void	init_item_town( void )
{
	shop_bar_item_asgn.prev = &shop_bar_item_asgn;
	shop_bar_item_asgn.next = &shop_bar_item_asgn;

	shop_wpn_item_asgn.prev = &shop_wpn_item_asgn;
	shop_wpn_item_asgn.next = &shop_wpn_item_asgn;

	shop_armor_item_asgn.prev = &shop_armor_item_asgn;
	shop_armor_item_asgn.next = &shop_armor_item_asgn;

	shop_temple_item_asgn.prev = &shop_temple_item_asgn;
	shop_temple_item_asgn.next = &shop_temple_item_asgn;

	shop_alchemy_item_asgn.prev = &shop_alchemy_item_asgn;
	shop_alchemy_item_asgn.next = &shop_alchemy_item_asgn;

	shop_music_item_asgn.prev = &shop_music_item_asgn;
	shop_music_item_asgn.next = &shop_music_item_asgn;

	shop_grocery_item_asgn.prev = &shop_grocery_item_asgn;
	shop_grocery_item_asgn.next = &shop_grocery_item_asgn;

	shop_restaurant_item_asgn.prev = &shop_restaurant_item_asgn;
	shop_restaurant_item_asgn.next = &shop_restaurant_item_asgn;

	shop_tearoom_item_asgn.prev = &shop_tearoom_item_asgn;
	shop_tearoom_item_asgn.next = &shop_tearoom_item_asgn;

	shop_tobacco_item_asgn.prev = &shop_tobacco_item_asgn;
	shop_tobacco_item_asgn.next = &shop_tobacco_item_asgn;
}

/**/

void	reset_item_town( void )
{
	free_item_ls( &shop_bar_item_asgn );
	free_item_ls( &shop_wpn_item_asgn );
	free_item_ls( &shop_armor_item_asgn );
	free_item_ls( &shop_temple_item_asgn );
	free_item_ls( &shop_alchemy_item_asgn );
	free_item_ls( &shop_music_item_asgn );
	free_item_ls( &shop_grocery_item_asgn );
	free_item_ls( &shop_restaurant_item_asgn );
	free_item_ls( &shop_tearoom_item_asgn );
	free_item_ls( &shop_tobacco_item_asgn );
}

/**/

void	garbage_collection_all_item( void )
{
	mbr_t	**ls_mbr = get_ls_mbr();
	item_t	*head, *p, *next, *prev;
	long	i, j;

	/* 迷宮上の全てのアイテムを削除 */

	head = &dun_item_asgn;
	p = head->next;
	for( i = 0; i < ITEM_MAX_N; i++, p = next ){
		if( p == head )
			break;

		next = p->next;
		del_item( p );
	}

	/* 全てのアイテムのゴミ・フラグを立てる */

	for( i = 0; i < ITEM_MAX_N; i++ )
		item_buf[i].flg_garbage = TRUE;

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		/* メンバーのアイテムのゴミ・フラグをふせる */

		head = get_mbr_item_asgn( ls_mbr[i] );
		if( head == NULL )
			continue;
		p = head->next;
		for( j = 0; j < LOOP_MAX_100; j++, p = p->next ){
			if( p == head )
				break;

			set_flg_item_garbage( p, FALSE );
		}

		/* メンバーの装備のゴミ・フラグをふせる */

		p = get_mbr_item_asgn_equip( ls_mbr[i] );
		if( p == NULL )
			continue;
		for( j = 0; j < EQUIP_KIND_MAX_N; j++ )
			set_flg_item_garbage( &(p[j]), FALSE );
	}

	/* ゴミ・フラグの立っているアイテムをフリー・リンクする */

	head = &item_free;
	prev = head;
	for( i = 0; i < ITEM_MAX_N; i++ ){
		p = &(item_buf[i]);

		if( p->flg_garbage ){
			p->prev = prev;
			p->next = head;
			prev->next = p;
			head->prev = p;

			prev = p;
		}
	}

	/**/

	init_item_town();
}

/**/

void	set_flg_item_garbage( item_t *item, bool_t flg )
{
	item_t	*head, *p;
	long	i;

	if( item == NULL )
		return;

	item->flg_garbage = flg;

	if( item->kind != ITEM_KIND_CHEST )
		return;

	/* 宝箱の中もフラグを設定する */

	head = item->dat.chest.contents;
	if( head == NULL )
		return;

	head->flg_garbage = flg;

	p = head->next;
	for( i = 0; i < LOOP_MAX_100; i++, p = p->next ){
		if( p == NULL )
			break;
		if( p == head )
			break;

		set_flg_item_garbage( p, flg );
	}
}

item_kind_t	make_item( long x, long y, long dun_lev )
{
	item_t	*p;

	p = make_item_sub( dun_lev, FALSE );
	if( p == NULL )
		return ITEM_KIND_NULL;
	if( p->kind == ITEM_KIND_NULL )
		return ITEM_KIND_NULL;

	if( !put_item( p, x, y, PUT_ITEM_R, FALSE ) ){
		del_item( p );
		return ITEM_KIND_NULL;
	}

	return p->kind;
}

/**/

item_t	*make_item_sub( long dun_lev, bool_t flg_chest )
{
	ratio_t	ratio_sum, ratio_rand, ratio_n;
	item_kind_t	kind;
	long	i, j;

	kind = ITEM_KIND_NULL;

	ratio_sum = 0;
	for( j = 0; j < ITEM_KIND_MAX_N + 1; j++ ){
		if( item_ratio_tab[j].kind == ITEM_KIND_NULL )
			break;

		ratio_sum += item_ratio_tab[j].ratio;
	}

	for( i = LOOP_MAX_100; i > 0; i-- ){
		ratio_rand = randm( ratio_sum );
		ratio_n = 0;
		for( j = 0; j < ITEM_KIND_MAX_N; j++ ){
			if( item_ratio_tab[j].kind == ITEM_KIND_NULL )
				break;

			ratio_n += item_ratio_tab[j].ratio;
			if( ratio_n > ratio_rand ){
				kind = item_ratio_tab[j].kind;
				break;
			}
		}

		if( kind != ITEM_KIND_CHEST )
			break;
		if( !flg_chest )
			break;
	}
	if( i <= 0 )
		return NULL;

	switch( kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		break;
	case ITEM_KIND_WPN:
		return make_item_wpn_rand( dun_lev );
	case ITEM_KIND_ARMOR:
		return make_item_armor_rand( dun_lev );
	case ITEM_KIND_POTION:
		return make_item_potion_rand( dun_lev );
	case ITEM_KIND_SCROLL:
		return make_item_scroll_rand( dun_lev );
	case ITEM_KIND_STICK:
		return make_item_stick_rand( dun_lev );
	case ITEM_KIND_ACCE:
		return make_item_acce_rand( dun_lev );
	case ITEM_KIND_INST:
		return make_item_inst_rand( dun_lev );
	case ITEM_KIND_ANTHOLOGY:
		return make_item_anthology_rand( dun_lev );
	case ITEM_KIND_LIGHT:
		return make_item_light_rand( dun_lev );
	case ITEM_KIND_SPIKE:
		return make_item_spike_rand( dun_lev );
	case ITEM_KIND_FOOD:
		return make_item_food_rand( dun_lev );
	case ITEM_KIND_CHEST:
		return make_item_chest_rand( dun_lev );
	case ITEM_KIND_TOBACCO:
		return make_item_tobacco_rand( dun_lev );
	case ITEM_KIND_PIPE:
		return make_item_pipe_rand( dun_lev );
	case ITEM_KIND_DISPOSAL:
		return make_item_disposal_rand( dun_lev );
	case ITEM_KIND_RARE_GOODS:
		return make_item_rare_goods_rand( dun_lev );
	case ITEM_KIND_BONE:
		return make_item_bone_rand( dun_lev );
	case ITEM_KIND_COIN:
		return make_item_coin_rand( dun_lev );
	case ITEM_KIND_JUNK:
		return make_item_junk_rand( dun_lev );
	/* default: */
	}

	return NULL;
}

/**/

item_t	*make_item_wpn_rand( long dun_lev )
{
	long	i;
	long	n;
	bool_t	flg;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( wpn_tab_max_n );
		if( wpn_tab[n].name == NULL )
			continue;
		if( wpn_tab[n].kind == WPN_KIND_NULL )
			continue;
		if( !rate_randm( wpn_tab[n].rate ) )
			continue;
		if( labs( dun_lev ) < wpn_tab[n].min_lev )
			continue;
		if( wpn_tab[n].max_lev < labs( dun_lev ) )
			continue;
		if( sgn_l( dun_lev ) != wpn_tab[n].sgn_lev )
			continue;

		flg = rate_randm( CURSE_ITEM_RATE );

		return make_item_wpn( dun_lev, n, flg );
	}

	return NULL;
}

/**/

item_t	*make_item_wpn( long dun_lev, long n, bool_t curse )
{
	item_t	*item;
	wpn_t	wpn;
	long	ave_n;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	wpn.kind = wpn_tab[n].kind;
	wpn.flg = wpn_tab[n].flg;

	if( curse ){
		wpn.add_hit = -expr_wpn_add_hit( dun_lev );
		wpn.add_crtcl = -expr_wpn_add_crtcl( dun_lev );
		wpn.add_dam = -expr_wpn_add_dam( dun_lev );
	} else {
		wpn.add_hit = expr_wpn_add_hit( dun_lev );
		wpn.add_crtcl = expr_wpn_add_crtcl( dun_lev );
		wpn.add_dam = expr_wpn_add_dam( dun_lev );
	}

	if( !curse && rate_randm( gen_slayer_rate( dun_lev ) ) )
		add_slayer( &wpn, dun_lev );
	else
		wpn.slayer = FACE_MJR_NULL;

	make_item_wpn_randm_art( &wpn, dun_lev );

	item->dat.wpn = wpn;
	item->kind = ITEM_KIND_WPN;
	if( chk_flg( wpn_tab[n].flg, FLG_WPN_TAB_ARW ) )
		item->equip_kind = EQUIP_KIND_ARW;
	else if( chk_flg( wpn_tab[n].flg, FLG_WPN_TAB_BOW ) )
		item->equip_kind = EQUIP_KIND_BOW;
	else
		item->equip_kind = EQUIP_KIND_WIELDING;

	ave_n = wpn_tab[n].ave_n;
	if( ave_n != 1 )
		ave_n = roll_dice( ave_n, TRUE );
	item->n = ave_n;

	item->flg = FLG_NULL;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_IDENTIFIED);
	if( curse )
		item->flg |= FLG_ITEM_CURSED;
	else
		item->flg &= ~(FLG_ITEM_CURSED);
	item->tab.wpn = &(wpn_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

#if	FLG_TEST_WPN_ADD
	print_msg( FLG_MSG_DEBUG,
			"wpn: hit[%ld] crtcl[%ld] dam[%ld]",
			wpn.add_hit, wpn.add_crtcl, wpn.add_dam );
#endif

	return item;
}

/**/

rate_t	gen_slayer_rate( long dun_lev )
{
	return ADD_SLAYER_RATE;
}

/**/

bool_t	add_slayer( wpn_t *wpn, long dun_lev )
{
	mnstr_tab_t	*tab;

	if( wpn == NULL )
		return FALSE;

	tab = get_mnstr_tab_rand( dun_lev );
	if( tab == NULL ){
		wpn->slayer = FACE_MJR_NULL;
		return FALSE;
	}

	wpn->slayer = tab->face_mjr;

	return TRUE;
}

/**/

void	make_item_wpn_randm_art( wpn_t *wpn, long dun_lev )
{
	long	max_n;

	if( wpn == NULL )
		return;

	max_n = gen_wpn_randm_art_n( dun_lev );

#if	FLG_TEST_RANDM_ART
	if( g_flg_debug )
		max_n = randm( TEST_RANDM_ART_N );
#endif

	make_item_wpn_randm_art_n( wpn, max_n );
}

/**/

void	make_item_wpn_randm_art_n( wpn_t *wpn, long max_n )
{
	long	n;
	wpn_randm_art_kind_t	kind;
	long	i;

	if( wpn == NULL )
		return;

	n = 0;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( n >= max_n )
			break;
		if( n >= WPN_RANDM_ART_LS_MAX_N )
			break;

		kind = (wpn_randm_art_kind_t)
				randm( WPN_RANDM_ART_KIND_MAX_N );
		if( kind == WPN_RANDM_ART_KIND_NULL )
			continue;

		add_wpn_randm_art( kind, &(wpn->randm_art[n]) );
		if( !chk_dup_wpn_randm_art( wpn, n ) )
			n++;
	}

	wpn->randm_art[n].kind = WPN_RANDM_ART_KIND_NULL;
	wpn->randm_art[n].mjr = WPN_RANDM_ART_MJR_NULL;
	wpn->randm_art[n].mnr = WPN_RANDM_ART_MNR_NULL;
}

/**/

long	gen_wpn_randm_art_n( long dun_lev )
{
	long	n;

	if( !rate_randm( WPN_RANDM_ART_RATE ) )
		return 0;

	n = labs( dun_lev ) / WPN_RANDM_ART_DUN_LEV_DIV;
	if( n > WPN_RANDM_ART_LS_MAX_N )
		n = WPN_RANDM_ART_LS_MAX_N;

	n = randm( n + 1 );

	return n;
}

/**/

void	add_wpn_randm_art(
	wpn_randm_art_kind_t kind,
	wpn_randm_art_t *art
)
{
	if( art == NULL )
		return;

	art->kind = kind;
	gen_wpn_randm_art_face( kind, &(art->mjr), &(art->mnr) );
}

/**/

void	gen_wpn_randm_art_face(
	wpn_randm_art_kind_t kind,
	char *mjr, char *mnr
)
{
	long	n;

	switch( kind ){
	case WPN_RANDM_ART_KIND_NULL:
	case WPN_RANDM_ART_KIND_MAX_N:
		if( mjr != NULL )
			*mjr = WPN_RANDM_ART_MJR_NULL;
		if( mnr != NULL )
			*mnr = WPN_RANDM_ART_MNR_NULL;
		break;
	case WPN_RANDM_ART_KIND_BANE:
		if( mjr != NULL )
			*mjr = WPN_RANDM_ART_MJR_BANE;

		n = sizeof( wpn_randm_art_mnr_slayer_tab );
		n /= sizeof( wpn_randm_art_mnr_slayer_tab[0] );
		n = randm( n );

		if( mnr != NULL )
			*mnr = tolower( wpn_randm_art_mnr_slayer_tab[n] );
		break;
	case WPN_RANDM_ART_KIND_KILLER:
		if( mjr != NULL )
			*mjr = WPN_RANDM_ART_MJR_KILLER;

		n = sizeof( wpn_randm_art_mnr_slayer_tab );
		n /= sizeof( wpn_randm_art_mnr_slayer_tab[0] );
		n = randm( n );

		if( mnr != NULL )
			*mnr = tolower( wpn_randm_art_mnr_slayer_tab[n] );
		break;
	case WPN_RANDM_ART_KIND_SLAYER:
		if( mjr != NULL )
			*mjr = WPN_RANDM_ART_MJR_SLAYER;

		n = sizeof( wpn_randm_art_mnr_slayer_tab );
		n /= sizeof( wpn_randm_art_mnr_slayer_tab[0] );
		n = randm( n );

		if( mnr != NULL )
			*mnr = tolower( wpn_randm_art_mnr_slayer_tab[n] );
		break;
	case WPN_RANDM_ART_KIND_ADD_STAT:
		if( mjr != NULL )
			*mjr = WPN_RANDM_ART_MJR_ADD_STAT;

		n = sizeof( wpn_randm_art_mnr_add_stat_tab );
		n /= sizeof( wpn_randm_art_mnr_add_stat_tab[0] );
		n = randm( n );

		if( mnr != NULL )
			*mnr = tolower( wpn_randm_art_mnr_add_stat_tab[n] );
		break;
	case WPN_RANDM_ART_KIND_DRAIN:
		if( mjr != NULL )
			*mjr = WPN_RANDM_ART_MJR_DRAIN;

		n = sizeof( wpn_randm_art_mnr_drain_tab );
		n /= sizeof( wpn_randm_art_mnr_drain_tab[0] );
		n = randm( n );

		if( mnr != NULL )
			*mnr = tolower( wpn_randm_art_mnr_drain_tab[n] );
		break;
	}
}

/**/

bool_t	chk_dup_wpn_randm_art( wpn_t *wpn, long n )
{
	long	i;

	for( i = 0; i < WPN_RANDM_ART_LS_MAX_N; i++ ){
		if( i >= n )
			break;

		if( wpn->randm_art[i].kind != wpn->randm_art[n].kind )
			continue;
		if( wpn->randm_art[i].mjr != wpn->randm_art[n].mjr )
			continue;
		if( wpn->randm_art[i].mnr != wpn->randm_art[n].mnr )
			continue;

		return TRUE;
	}

	return FALSE;
}

/**/

item_t	*make_item_armor_rand( long dun_lev )
{
	long	i;
	long	n;
	bool_t	flg;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( armor_tab_max_n );
		if( armor_tab[n].name == NULL )
			continue;
		if( armor_tab[n].kind == ARMOR_KIND_NULL )
			continue;
		if( !rate_randm( armor_tab[n].rate ) )
			continue;
		if( labs( dun_lev ) < armor_tab[n].min_lev )
			continue;
		if( armor_tab[n].max_lev < labs( dun_lev ) )
			continue;
		if( sgn_l( dun_lev ) != armor_tab[n].sgn_lev )
			continue;

		flg = rate_randm( armor_tab[n].rate_curse );

		return make_item_armor( dun_lev, n, flg );
	}

	return NULL;
}

/**/

item_t	*make_item_armor( long dun_lev, long n, bool_t curse )
{
	item_t	*item;
	armor_t	armor;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	armor.kind = armor_tab[n].kind;
	if( curse ){
		armor.add_def = -randm( armor_tab[n].def ) - 1;
		armor.add_crtcl = -randm( armor_tab[n].crtcl ) - 1;
		armor.add_ac = -randm( armor_tab[n].ac ) - 1;
	} else {
		armor.add_def = expr_armor_add_def( dun_lev );
		armor.add_crtcl = expr_armor_add_crtcl( dun_lev );
		armor.add_ac = expr_armor_add_ac( dun_lev );
	}

	make_item_armor_randm_art( &armor, dun_lev );

	item->dat.armor = armor;
	item->kind = ITEM_KIND_ARMOR;
	item->equip_kind = armor_tab[n].equip_kind;
	item->n = 1;

	item->flg = FLG_NULL;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_IDENTIFIED);
	if( curse )
		item->flg |= FLG_ITEM_CURSED;
	else
		item->flg &= ~(FLG_ITEM_CURSED);
	if( armor_tab[n].flg_protected )
		item->flg |= FLG_ITEM_PROTECTED;
	else
		item->flg &= ~(FLG_ITEM_PROTECTED);

	item->modifier = armor_tab[n].modifier;
	item->tab.armor = &(armor_tab[n]);

	if( !curse && rate_randm( gen_armor_resi_rate( dun_lev ) ) ){
		resi_kind_t	resi;

		resi = gen_armor_resi_kind( dun_lev );
		add_armor_resi( item, dun_lev, resi );
	}

	item->alias[0] = '\0';
	set_item_name( item );

#if	FLG_TEST_ARMOR_ADD
	print_msg( FLG_MSG_DEBUG,
			"armor: def[%ld] crtcl[%ld] arm[%ld]",
			armor.add_def, armor.add_crtcl, armor.add_ac );
#endif

	return item;
}

/**/

rate_t	gen_armor_resi_rate( long dun_lev )
{
	rate_t	rate;

	rate = labs( dun_lev );
	rate = rate * ARMOR_RESI_RATE_MUL + ARMOR_RESI_RATE_ADD;
	if( rate > _100_PERCENT )
		rate = _100_PERCENT;

	return rate;
}

/**/

bool_t	add_armor_resi( item_t *p, long dun_lev, resi_kind_t resi )
{
	if( p == NULL )
		return FALSE;
	if( p->kind != ITEM_KIND_ARMOR )
		return FALSE;

	p->modifier.add_resi_n[resi]++;

	return TRUE;
}

/**/

resi_kind_t	gen_armor_resi_kind( long dun_lev )
{
	return( (resi_kind_t)randm( RESI_KIND_MAX_N ) );
}

/**/

void	make_item_armor_randm_art( armor_t *armor, long dun_lev )
{
	long	max_n;

	if( armor == NULL )
		return;

	max_n = gen_armor_randm_art_n( dun_lev );

#if	FLG_TEST_RANDM_ART
	if( g_flg_debug )
		max_n = randm( TEST_RANDM_ART_N );
#endif

	make_item_armor_randm_art_n( armor, max_n );
}

/**/

void	make_item_armor_randm_art_n( armor_t *armor, long max_n )
{
	long	n;
	armor_randm_art_kind_t	kind;
	long	i;

	if( armor == NULL )
		return;

	n = 0;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( n >= max_n )
			break;
		if( n >= ARMOR_RANDM_ART_LS_MAX_N )
			break;

		kind = (armor_randm_art_kind_t)
				randm( ARMOR_RANDM_ART_KIND_MAX_N );
		if( kind == ARMOR_RANDM_ART_KIND_NULL )
			continue;

		add_armor_randm_art( kind, &(armor->randm_art[n]) );
		if( !chk_dup_armor_randm_art( armor, n ) )
			n++;
	}

	armor->randm_art[n].kind = ARMOR_RANDM_ART_KIND_NULL;
	armor->randm_art[n].mjr = ARMOR_RANDM_ART_MJR_NULL;
	armor->randm_art[n].mnr = ARMOR_RANDM_ART_MNR_NULL;
}

/**/

long	gen_armor_randm_art_n( long dun_lev )
{
	long	n;

	if( !rate_randm( ARMOR_RANDM_ART_RATE ) )
		return 0;

	n = labs( dun_lev ) / ARMOR_RANDM_ART_DUN_LEV_DIV;
	if( n > ARMOR_RANDM_ART_LS_MAX_N )
		n = ARMOR_RANDM_ART_LS_MAX_N;

	n = randm( n + 1 );

	return n;
}

/**/

void	add_armor_randm_art(
	armor_randm_art_kind_t kind,
	armor_randm_art_t *art
)
{
	if( art == NULL )
		return;

	art->kind = kind;
	gen_armor_randm_art_face( kind, &(art->mjr), &(art->mnr) );
}

/**/

void	gen_armor_randm_art_face(
	armor_randm_art_kind_t kind,
	char *mjr, char *mnr
)
{
	long	n;
	long	c;

	switch( kind ){
	case ARMOR_RANDM_ART_KIND_NULL:
	case ARMOR_RANDM_ART_KIND_MAX_N:
		if( mjr != NULL )
			*mjr = ARMOR_RANDM_ART_MJR_NULL;
		if( mnr != NULL )
			*mnr = ARMOR_RANDM_ART_MNR_NULL;
		break;
	case ARMOR_RANDM_ART_KIND_GUARD:
		if( mjr != NULL )
			*mjr = ARMOR_RANDM_ART_MJR_GUARD;

		n = sizeof( armor_randm_art_mnr_protect_tab );
		n /= sizeof( armor_randm_art_mnr_protect_tab[0] );
		n = randm( n );

		c = armor_randm_art_mnr_protect_tab[n];
		if( mnr != NULL )
			*mnr = tolower( c );
		break;
	case ARMOR_RANDM_ART_KIND_BLOCK:
		if( mjr != NULL )
			*mjr = ARMOR_RANDM_ART_MJR_BLOCK;

		n = sizeof( armor_randm_art_mnr_protect_tab );
		n /= sizeof( armor_randm_art_mnr_protect_tab[0] );
		n = randm( n );

		c = armor_randm_art_mnr_protect_tab[n];
		if( mnr != NULL )
			*mnr = tolower( c );
		break;
	case ARMOR_RANDM_ART_KIND_PROTECT:
		if( mjr != NULL )
			*mjr = ARMOR_RANDM_ART_MJR_PROTECT;

		n = sizeof( armor_randm_art_mnr_protect_tab );
		n /= sizeof( armor_randm_art_mnr_protect_tab[0] );
		n = randm( n );

		c = armor_randm_art_mnr_protect_tab[n];
		if( mnr != NULL )
			*mnr = tolower( c );
		break;
	case ARMOR_RANDM_ART_KIND_RESI_STAT:
		if( mjr != NULL )
			*mjr = ARMOR_RANDM_ART_MJR_RESI_STAT;

		n = sizeof( armor_randm_art_mnr_resi_stat_tab );
		n /= sizeof( armor_randm_art_mnr_resi_stat_tab[0] );
		n = randm( n );

		c = armor_randm_art_mnr_resi_stat_tab[n];
		if( mnr != NULL )
			*mnr = tolower( c );
		break;
	case ARMOR_RANDM_ART_KIND_HEALING:
		if( mjr != NULL )
			*mjr = ARMOR_RANDM_ART_MJR_HEALING;

		n = sizeof( armor_randm_art_mnr_healing_tab );
		n /= sizeof( armor_randm_art_mnr_healing_tab[0] );
		n = randm( n );

		c = armor_randm_art_mnr_healing_tab[n];
		if( mnr != NULL )
			*mnr = tolower( c );
		break;
	}
}

/**/

bool_t	chk_dup_armor_randm_art( armor_t *armor, long n )
{
	long	i;

	for( i = 0; i < ARMOR_RANDM_ART_LS_MAX_N; i++ ){
		if( i >= n )
			break;

		if( armor->randm_art[i].kind != armor->randm_art[n].kind )
			continue;
		if( armor->randm_art[i].mjr != armor->randm_art[n].mjr )
			continue;
		if( armor->randm_art[i].mnr != armor->randm_art[n].mnr )
			continue;

		return TRUE;
	}

	return FALSE;
}

/**/

item_t	*make_item_potion_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( potion_tab_max_n );
		if( potion_tab[n].name == NULL )
			continue;
		if( potion_tab[n].kind == POTION_KIND_NULL )
			continue;
		if( !rate_randm( potion_tab[n].rate ) )
			continue;
		if( labs( dun_lev ) < potion_tab[n].min_lev )
			continue;
		if( potion_tab[n].max_lev < labs( dun_lev ) )
			continue;
		if( sgn_l( dun_lev ) != potion_tab[n].sgn_lev )
			continue;

		return make_item_potion( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_potion( long dun_lev, long n )
{
	item_t	*item;
	potion_t	potion;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	potion.kind = potion_tab[n].kind;
	item->dat.potion = potion;
	item->kind = ITEM_KIND_POTION;
	item->equip_kind = EQUIP_KIND_ARW;
	item->n = 1;
	item->flg = FLG_NULL;
	item->flg &= ~(FLG_ITEM_DETECTED);
	if( potion_tab[n].flg_identified )
		item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_CURSED);
	item->tab.potion = &(potion_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_scroll_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( scroll_tab_max_n );
		if( scroll_tab[n].name == NULL )
			continue;
		if( scroll_tab[n].kind == SCROLL_KIND_NULL )
			continue;
		if( !rate_randm( scroll_tab[n].rate ) )
			continue;
		if( labs( dun_lev ) < scroll_tab[n].min_lev )
			continue;
		if( scroll_tab[n].max_lev < labs( dun_lev ) )
			continue;
		if( sgn_l( dun_lev ) != scroll_tab[n].sgn_lev )
			continue;

		return make_item_scroll( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_scroll( long dun_lev, long n )
{
	item_t	*item;
	scroll_t	scroll;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	scroll.kind = scroll_tab[n].kind;
	item->dat.scroll = scroll;
	item->kind = ITEM_KIND_SCROLL;
	item->equip_kind = EQUIP_KIND_HEAD;
	item->n = 1;
	item->flg = FLG_NULL;
	item->flg &= ~(FLG_ITEM_DETECTED);
	if( scroll_tab[n].flg_identified )
		item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_CURSED);
	item->tab.scroll = &(scroll_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_stick_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( stick_tab_max_n );
		if( stick_tab[n].name == NULL )
			continue;
		if( stick_tab[n].kind == STICK_KIND_NULL )
			continue;
		if( !rate_randm( stick_tab[n].rate ) )
			continue;
		if( labs( dun_lev ) < stick_tab[n].min_lev )
			continue;
		if( stick_tab[n].max_lev < labs( dun_lev ) )
			continue;
		if( sgn_l( dun_lev ) != stick_tab[n].sgn_lev )
			continue;

		return make_item_stick( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_stick( long dun_lev, long n )
{
	item_t	*item;
	stick_t	stick;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	stick.kind = stick_tab[n].kind;
	stick.spell_kind = stick_tab[n].spell_kind;
	stick.n = calc_stick_use_n( stick_tab[n].kind, dun_lev,
			stick_tab[n].use_n, TRUE );
	item->n = 1;
	item->dat.stick = stick;
	item->kind = ITEM_KIND_STICK;
	item->equip_kind = EQUIP_KIND_BOW;
	item->flg = FLG_NULL;
	item->flg &= ~(FLG_ITEM_DETECTED);
	if( stick_tab[n].flg_identified )
		item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_CURSED);
	item->tab.stick = &(stick_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

long	calc_stick_use_n(
	stick_kind_t kind, long dun_lev, long use_n, bool_t flg_randm
)
{
	dun_lev = labs( dun_lev );

	if( use_n <= -1 ){
		use_n = 1;

		switch( kind ){
		case STICK_KIND_NULL:
			break;
		case STICK_KIND_WAND:
			use_n = dun_lev * STICK_USE_N_WAND_RATE;
			use_n /= _100_PERCENT;
			use_n += STICK_USE_N_WAND_ADD;
			break;
		case STICK_KIND_ROD:
			use_n = dun_lev * STICK_USE_N_ROD_RATE;
			use_n /= _100_PERCENT;
			use_n += STICK_USE_N_ROD_ADD;
			break;
		case STICK_KIND_STAFF:
			use_n = dun_lev * STICK_USE_N_STAFF_RATE;
			use_n /= _100_PERCENT;
			use_n += STICK_USE_N_STAFF_ADD;
			break;
		case STICK_KIND_MAX_N:
			break;
		/* default: */
		}

		if( flg_randm ){
			use_n = roll_dice( use_n, TRUE );
		}
	} else if( use_n == 0 ){
		use_n = 0;
	} else if( use_n == 1 ){
		use_n = 1;
	} else {
		if( flg_randm ){
			use_n = roll_dice( use_n, TRUE );
		}
	}

	return use_n;
}

/**/

item_t	*make_item_acce_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( acce_tab_max_n );
		if( acce_tab[n].name == NULL )
			continue;
		if( acce_tab[n].kind == ACCE_KIND_NULL )
			continue;
		if( !rate_randm( acce_tab[n].rate ) )
			continue;
		if( labs( dun_lev ) < acce_tab[n].min_lev )
			continue;
		if( acce_tab[n].max_lev < labs( dun_lev ) )
			continue;
		if( sgn_l( dun_lev ) != acce_tab[n].sgn_lev )
			continue;

		return make_item_acce( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_acce( long dun_lev, long n )
{
	item_t	*item;
	acce_t	acce;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	acce.kind = acce_tab[n].kind;
	acce.ring_kind = acce_tab[n].ring_kind;
	acce.amulet_kind = acce_tab[n].amulet_kind;
	acce.necklace_kind = acce_tab[n].necklace_kind;
	item->dat.acce = acce;
	item->kind = ITEM_KIND_ACCE;
	item->equip_kind = acce_tab[n].equip_kind;
	item->n = 1;
	item->flg = FLG_NULL;
	item->flg &= ~(FLG_ITEM_DETECTED);
	if( acce_tab[n].flg_identified )
		item->flg |= FLG_ITEM_IDENTIFIED;
	if( rate_randm( acce_tab[n].rate_curse ) )
		item->flg |= FLG_ITEM_CURSED;
	else
		item->flg &= ~(FLG_ITEM_CURSED);
	item->modifier = acce_tab[n].modifier;
	item->tab.acce = &(acce_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_inst_rand( long dun_lev )
{
	long	i;
	long	n;
	bool_t	flg;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( inst_tab_max_n );
		if( inst_tab[n].name == NULL )
			continue;
		if( inst_tab[n].kind == INST_KIND_NULL )
			continue;

		flg = rate_randm( inst_tab[n].rate_curse );
		return make_item_inst( dun_lev, n, flg );
	}

	return NULL;
}

/**/

item_t	*make_item_inst( long dun_lev, long n, bool_t curse )
{
	item_t	*item;
	inst_t	inst;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	inst.kind = inst_tab[n].kind;
	if( !curse && rate_randm( gen_inst_limit_rate( dun_lev ) ) ){
		inst.flg_limit = TRUE;
	} else {
		inst.flg_limit = FALSE;
	}
	if( !curse && rate_randm( gen_inst_spell_rate( dun_lev ) ) ){
		spell_kind_t	spell;

		spell = gen_inst_spell_kind( dun_lev, n );
		add_inst_spell( &inst, dun_lev, spell );
	} else {
		inst.spell_kind = SPELL_KIND_NULL;
	}
	item->n = 1;
	item->dat.inst = inst;
	item->kind = ITEM_KIND_INST;
	item->equip_kind = EQUIP_KIND_WIELDING;
	item->flg = FLG_NULL;
	item->flg &= ~(FLG_ITEM_DETECTED);
	if( curse )
		item->flg |= FLG_ITEM_CURSED;
	else
		item->flg &= ~(FLG_ITEM_CURSED);
	item->tab.inst = &(inst_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

rate_t	gen_inst_limit_rate( long dun_lev )
{
	rate_t	rate;

	rate = labs( dun_lev );
	rate = rate * INST_LIMIT_RATE_MUL + INST_LIMIT_RATE_ADD;
	if( rate > _100_PERCENT )
		rate = _100_PERCENT;

	return rate;
}

/**/

rate_t	gen_inst_spell_rate( long dun_lev )
{
	rate_t	rate;

	rate = labs( dun_lev );
	rate = rate * INST_SPELL_RATE_MUL + INST_SPELL_RATE_ADD;
	if( rate > _100_PERCENT )
		rate = _100_PERCENT;

	return rate;
}

/**/

spell_kind_t	gen_inst_spell_kind( long dun_lev, long tab_n )
{
	long	head, tail, n;

	head = SPELL_KIND_BAR_MIN_N + 1;
	tail = SPELL_KIND_BAR_MAX_N - 1;

	switch( inst_tab[tab_n].mnr ){
	case FACE_MNR_INST_STRINGED:
		/* 回復 */
		head = SPELL_KIND_BAR_CURE_MIN_N;
		tail = SPELL_KIND_BAR_CURE_MAX_N;
		break;
	case FACE_MNR_INST_WOODWIND:
		/* 能力値強化 */
		head = SPELL_KIND_BAR_STRENGTHEN_ABL_MIN_N;
		tail = SPELL_KIND_BAR_STRENGTHEN_ABL_MAX_N;
		break;
	case FACE_MNR_INST_BRASS:
		/* 能力値弱体 */
		head = SPELL_KIND_BAR_WEAKEN_ABL_MIN_N;
		tail = SPELL_KIND_BAR_WEAKEN_ABL_MAX_N;
		break;
	case FACE_MNR_INST_PERCUSSION:
		/* 状態抵抗 */
		head = SPELL_KIND_BAR_RESI_STAT_MIN_N;
		tail = SPELL_KIND_BAR_RESI_STAT_MAX_N;
		break;
	case FACE_MNR_INST_MISC:
		/* 全て */
		head = SPELL_KIND_BAR_MIN_N + 1;
		tail = SPELL_KIND_BAR_MAX_N - 1;
		break;
	default:
		return SPELL_KIND_NULL;
	}

	n = head + randm( tail - head + 1 );
	return( (spell_kind_t)n );
}

/**/

bool_t	add_inst_spell( inst_t *p, long dun_lev, spell_kind_t kind )
{
	if( p == NULL )
		return FALSE;

	p->spell_kind = kind;

	return TRUE;
}

/**/

item_t	*make_item_anthology_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( anthology_tab_max_n );
		if( anthology_tab[n].name == NULL )
			continue;
		if( anthology_tab[n].kind == ANTHOLOGY_KIND_NULL )
			continue;

		return make_item_anthology( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_anthology( long dun_lev, long n )
{
	item_t	*item;
	anthology_t	anthology;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	anthology.kind = anthology_tab[n].kind;
	item->n = 1;
	item->dat.anthology = anthology;
	item->kind = ITEM_KIND_ANTHOLOGY;
	item->equip_kind = EQUIP_KIND_ARW;
	item->flg = FLG_NULL;
	item->flg &= ~(FLG_ITEM_DETECTED);
	item->tab.anthology = &(anthology_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_light_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( light_tab_max_n );
		if( light_tab[n].name == NULL )
			continue;
		if( light_tab[n].kind == LIGHT_KIND_NULL )
			continue;
		if( !rate_randm( light_tab[n].rate ) )
			continue;
		if( labs( dun_lev ) < light_tab[n].min_lev )
			continue;
		if( light_tab[n].max_lev < labs( dun_lev ) )
			continue;
		if( sgn_l( dun_lev ) != light_tab[n].sgn_lev )
			continue;

		return make_item_light( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_light( long dun_lev, long n )
{
	item_t	*item;
	light_t	light;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	light.kind = light_tab[n].kind;
	light.turn = expr_light_turn( light_tab[n].max_turn );
	light.wish_level = light_tab[n].wish_level;
	if( light_tab[n].wish_max_n <= 0 )
		light.wish_n = 0;
	else
		light.wish_n = randm( light_tab[n].wish_max_n ) + 1;
	light.flg_used = FALSE;
	item->dat.light = light;
	item->kind = ITEM_KIND_LIGHT;
	item->equip_kind = EQUIP_KIND_LIGHT_SOURCE;
	item->n = 1;
	item->flg = FLG_NULL;
	item->flg &= ~(FLG_ITEM_IDENTIFIED | FLG_ITEM_DETECTED
			| FLG_ITEM_CURSED);
	item->tab.light = &(light_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_spike_rand( long dun_lev )
{
	return make_item_spike( dun_lev );
}

/**/

item_t	*make_item_spike( long dun_lev )
{
	item_t	*item;
	long	ave_n;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	item->kind = ITEM_KIND_SPIKE;
	item->equip_kind = EQUIP_KIND_ARW;
	ave_n = SPIKE_AVE_N;
	if( ave_n != 1 )
		ave_n = roll_dice( ave_n, TRUE );
	item->n = ave_n;
	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);
	item->tab.wpn = NULL;

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_food_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( food_tab_max_n );
		if( food_tab[n].name == NULL )
			continue;
		if( food_tab[n].kind == FOOD_KIND_NULL )
			continue;
		if( !rate_randm( food_tab[n].rate ) )
			continue;

		return make_item_food( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_food( long dun_lev, long n )
{
	item_t	*item;
	food_t	food;
	long	ave_n;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	food.kind = food_tab[n].kind;
	item->dat.food = food;
	item->kind = ITEM_KIND_FOOD;
	item->equip_kind = EQUIP_KIND_ARW;

	ave_n = food_tab[n].ave_n;
	if( ave_n > 1 )
		ave_n = roll_dice( ave_n, TRUE );
	else
		ave_n = 1;
	item->n = ave_n;

	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);
	item->tab.food = &(food_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_chest_rand( long dun_lev )
{
	if( labs( dun_lev ) < CHEST_MIN_LEV )
		return NULL;
	if( CHEST_MAX_LEV < labs( dun_lev ) )
		return NULL;

	return make_item_chest( dun_lev, get_chest_n( dun_lev ), TRUE );
}

/**/

item_t	*make_item_chest( long dun_lev, long contents_n, bool_t flg_trap )
{
	item_t	*item;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	item = make_item_chest_alloc(
			item, dun_lev, contents_n, flg_trap );

	return item;
}

/**/

item_t	*make_item_chest_alloc(
	item_t *item,
	long dun_lev, long contents_n, bool_t flg_trap
)
{
	item_t	*head;
	long	n;

	head = alloc_item();
	if( head == NULL ){
		free_item( item );
		return NULL;
	}

	/* リストの参照数(item ではなくて head である事に注意) */
	head->kind = ITEM_KIND_NULL;
	head->dat.chest.ref = 1;
	head->prev = head;
	head->next = head;

	item->dat.chest.ref = 0;
	item->dat.chest.contents = head;

	item->kind = ITEM_KIND_CHEST;
	item->equip_kind = EQUIP_KIND_ARW;
	item->n = 1;
	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);

	for( n = 0; n < contents_n; n++ ){
		item_t	*p;

		p = make_item_sub( dun_lev, TRUE );
		if( p == NULL )
			continue;
		if( p->kind == ITEM_KIND_NULL )
			continue;

		ins_ls_item( item->dat.chest.contents, p );
	}

	if( flg_trap ){
		item->dat.chest.trap = make_trap(
				MAP_DEL_X, MAP_DEL_Y, dun_lev );
	} else {
		item->dat.chest.trap = NULL;
	}
	if( item->dat.chest.trap != NULL ){
		item->dat.chest.trap->prev = NULL;
		item->dat.chest.trap->next = NULL;
	}

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_tobacco_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( tobacco_tab_max_n );
		if( tobacco_tab[n].name == NULL )
			continue;
		if( tobacco_tab[n].kind == TOBACCO_KIND_NULL )
			continue;
		if( !rate_randm( tobacco_tab[n].rate ) )
			continue;

		return make_item_tobacco( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_tobacco( long dun_lev, long n )
{
	item_t	*item;
	tobacco_t	tobacco;
	long	ave_n;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	tobacco.kind = tobacco_tab[n].kind;
	tobacco.brand = tobacco_tab[n].brand;
	tobacco.turn = tobacco_tab[n].turn;
	item->dat.tobacco = tobacco;
	item->kind = ITEM_KIND_TOBACCO;
	item->equip_kind = EQUIP_KIND_HEAD;

	ave_n = tobacco_tab[n].ave_n;
	if( ave_n > 1 )
		ave_n = roll_dice( ave_n, TRUE );
	else
		ave_n = 1;
	item->n = ave_n;

	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);
	item->tab.tobacco = &(tobacco_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_pipe_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( pipe_tab_max_n );
		if( pipe_tab[n].name == NULL )
			continue;
		if( pipe_tab[n].kind == PIPE_KIND_NULL )
			continue;
		if( !rate_randm( pipe_tab[n].rate ) )
			continue;

		return make_item_pipe( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_pipe( long dun_lev, long n )
{
	item_t	*item;
	pipe_t	pipe;
	long	ave_n;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	pipe.kind = pipe_tab[n].kind;
	pipe.turn = 0;
	pipe.consume_turn = pipe_tab[n].consume_turn;
	item->dat.pipe = pipe;
	item->kind = ITEM_KIND_PIPE;
	item->equip_kind = EQUIP_KIND_HEAD;

	ave_n = pipe_tab[n].ave_n;
	if( ave_n > 1 )
		ave_n = roll_dice( ave_n, TRUE );
	else
		ave_n = 1;
	item->n = ave_n;

	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);
	item->tab.pipe = &(pipe_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_disposal_rand( long dun_lev )
{
	return make_item_disposal( dun_lev );
}

/**/

item_t	*make_item_disposal( long dun_lev )
{
	item_t	*item;
	disposal_t	disposal;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	disposal.n = 0;
	disposal.max_n = DISPOSAL_MAX_N;
	item->dat.disposal = disposal;
	item->kind = ITEM_KIND_DISPOSAL;
	item->equip_kind = EQUIP_KIND_ARW;
	item->n = 1;

	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);
	item->tab.wpn = NULL;

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_rare_goods_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( rare_goods_tab_max_n );
		if( rare_goods_tab[n].name == NULL )
			continue;
		if( rare_goods_tab[n].kind == RARE_GOODS_KIND_NULL )
			continue;

		return make_item_rare_goods( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_rare_goods( long dun_lev, long n )
{
	item_t	*item;
	rare_goods_t	rare_goods;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	rare_goods.kind = rare_goods_tab[n].kind;
	rare_goods.mnstr_kind = MNSTR_KIND_NULL;
	item->dat.rare_goods = rare_goods;
	item->kind = ITEM_KIND_RARE_GOODS;
	item->equip_kind = EQUIP_KIND_ARW;
	item->n = 1;
	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);
	item->tab.rare_goods = &(rare_goods_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_bone_rand( long dun_lev )
{
	mnstr_tab_t	*tab;

	tab = get_mnstr_tab_rand( dun_lev );
	if( tab == NULL )
		return NULL;

	return make_item_bone( dun_lev, tab );
}

/**/

item_t	*make_item_bone( long dun_lev, mnstr_tab_t *tab )
{
	item_t	*item;
	bone_t	bone;

	if( tab == NULL )
		return NULL;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	bone.mnstr_tab = tab;
	bone.dun_lev = dun_lev;
	item->dat.bone = bone;
	item->kind = ITEM_KIND_BONE;
	item->equip_kind = EQUIP_KIND_ARW;
	item->n = 1;
	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_coin_rand( long dun_lev )
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( coin_tab_max_n );
		if( coin_tab[n].name == NULL )
			continue;
		if( coin_tab[n].kind == COIN_KIND_NULL )
			continue;
		if( !rate_randm( coin_tab[n].rate ) )
			continue;

		return make_item_coin( dun_lev, n );
	}

	return NULL;
}

/**/

item_t	*make_item_coin( long dun_lev, long n )
{
	item_t	*item;
	coin_t	coin;
	long	ave_n;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	coin.kind = coin_tab[n].kind;
	item->dat.coin = coin;
	item->kind = ITEM_KIND_COIN;
	item->equip_kind = EQUIP_KIND_ARW;

	ave_n = (labs( dun_lev ) * COIN_N_MUL) + COIN_N_ADD;
	if( ave_n > 1 )
		ave_n = roll_dice( ave_n, TRUE );
	else
		ave_n = 1;
	item->n = ave_n;

	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);
	item->tab.coin = &(coin_tab[n]);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_junk_rand( long dun_lev )
{
	return make_item_junk( dun_lev );
}

/**/

item_t	*make_item_junk( long dun_lev )
{
	item_t	*item;

	item = alloc_item();
	if( item == NULL )
		return NULL;

	item->kind = ITEM_KIND_JUNK;
	item->equip_kind = EQUIP_KIND_ARW;
	item->n = 1;
	item->flg = FLG_NULL;
	item->flg |= FLG_ITEM_IDENTIFIED;
	item->flg &= ~(FLG_ITEM_DETECTED | FLG_ITEM_CURSED);

	item->alias[0] = '\0';
	set_item_name( item );

	return item;
}

/**/

item_t	*make_item_sel(
	item_kind_t kind,
	long k1, long k2, long k3,
	long dun_lev
)
{
	long	tab_n;
	item_t	*item;
	bool_t	flg_curse;

	tab_n = -1;

	switch( kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		return NULL;
	case ITEM_KIND_WPN:
		tab_n = get_wpn_tab_n( get_wpn_tab(
				(wpn_kind_t)k1 ) );
		break;
	case ITEM_KIND_ARMOR:
		tab_n = get_armor_tab_n( get_armor_tab(
				(armor_kind_t)k1 ) );
		break;
	case ITEM_KIND_POTION:
		tab_n = get_potion_tab_n( get_potion_tab(
				(potion_kind_t)k1 ) );
		break;
	case ITEM_KIND_SCROLL:
		tab_n = get_scroll_tab_n( get_scroll_tab(
				(scroll_kind_t)k1 ) );
		break;
	case ITEM_KIND_STICK:
		tab_n = get_stick_tab_n( get_stick_tab(
				(stick_kind_t)k1,
				(spell_kind_t)k2 ) );
		break;
	case ITEM_KIND_ACCE:
		tab_n = get_acce_tab_n( get_acce_tab(
				(ring_kind_t)k1,
				(amulet_kind_t)k2,
				(necklace_kind_t)k3 ) );
		break;
	case ITEM_KIND_INST:
		tab_n = get_inst_tab_n( get_inst_tab(
				(inst_kind_t)k1 ) );
		break;
	case ITEM_KIND_ANTHOLOGY:
		tab_n = get_anthology_tab_n( get_anthology_tab(
				(anthology_kind_t)k1 ) );
		break;
	case ITEM_KIND_LIGHT:
		tab_n = get_light_tab_n( get_light_tab(
				(light_kind_t)k1,
				(wish_level_t)k2 ) );
		break;
	case ITEM_KIND_SPIKE:
		tab_n = 0;
		break;
	case ITEM_KIND_FOOD:
		tab_n = get_food_tab_n( get_food_tab(
				(food_kind_t)k1 ) );
		break;
	case ITEM_KIND_CHEST:
		tab_n = 0;
		break;
	case ITEM_KIND_TOBACCO:
		tab_n = get_tobacco_tab_n( get_tobacco_tab(
				(tobacco_kind_t)k1,
				(tobacco_brand_t)k2 ) );
		break;
	case ITEM_KIND_PIPE:
		tab_n = get_pipe_tab_n( get_pipe_tab(
				(pipe_kind_t)k1 ) );
		break;
	case ITEM_KIND_DISPOSAL:
		tab_n = 0;
		break;
	case ITEM_KIND_RARE_GOODS:
		tab_n = get_rare_goods_tab_n( get_rare_goods_tab(
				(rare_goods_kind_t)k1 ) );
		break;
	case ITEM_KIND_BONE:
		tab_n = 0;
		break;
	case ITEM_KIND_COIN:
		tab_n = get_coin_tab_n( get_coin_tab(
				(coin_kind_t)k1 ) );
		break;
	case ITEM_KIND_JUNK:
		tab_n = 0;
		break;
	/* default: */
	}

	if( tab_n < 0 )
		return NULL;

	/**/

	item = NULL;
	flg_curse = rate_randm( CURSE_ITEM_RATE );

	switch( kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		return NULL;
	case ITEM_KIND_WPN:
		item = make_item_wpn( dun_lev, tab_n, flg_curse );
		break;
	case ITEM_KIND_ARMOR:
		item = make_item_armor( dun_lev, tab_n, flg_curse );
		break;
	case ITEM_KIND_POTION:
		item = make_item_potion( dun_lev, tab_n );
		break;
	case ITEM_KIND_SCROLL:
		item = make_item_scroll( dun_lev, tab_n );
		break;
	case ITEM_KIND_STICK:
		item = make_item_stick( dun_lev, tab_n );
		break;
	case ITEM_KIND_ACCE:
		item = make_item_acce( dun_lev, tab_n );
		break;
	case ITEM_KIND_INST:
		item = make_item_inst( dun_lev, tab_n, flg_curse );
		break;
	case ITEM_KIND_ANTHOLOGY:
		item = make_item_anthology( dun_lev, tab_n );
		break;
	case ITEM_KIND_LIGHT:
		item = make_item_light( dun_lev, tab_n );
		break;
	case ITEM_KIND_SPIKE:
		item = make_item_spike( dun_lev );
		break;
	case ITEM_KIND_FOOD:
		item = make_item_food( dun_lev, tab_n );
		break;
	case ITEM_KIND_CHEST:
		item = make_item_chest( dun_lev,
				get_chest_n( dun_lev ), TRUE );
		break;
	case ITEM_KIND_TOBACCO:
		item = make_item_tobacco( dun_lev, tab_n );
		break;
	case ITEM_KIND_PIPE:
		item = make_item_pipe( dun_lev, tab_n );
		break;
	case ITEM_KIND_DISPOSAL:
		item = make_item_disposal( dun_lev );
		break;
	case ITEM_KIND_RARE_GOODS:
		item = make_item_rare_goods( dun_lev, tab_n );
		break;
	case ITEM_KIND_BONE:
		item = make_item_bone( dun_lev,
				get_mnstr_tab( (mnstr_kind_t)k1, (long)k2 ) );
		break;
	case ITEM_KIND_COIN:
		item = make_item_coin( dun_lev, tab_n );
		break;
	case ITEM_KIND_JUNK:
		item = make_item_junk( dun_lev );
		break;
	/* default: */
	}

	return item;
}

/***************************************************************
* 武器アーティファクトの望み
* chr_t *chr : キャラクタ
* wish_level_t wish_level : 魔神の種類
* return : 望みが叶えられたか?
***************************************************************/

bool_t	fx_wish_artifact_wpn( chr_t *chr, wish_level_t wish_level )
{
	dun_t	*dun = get_dun();
	long	dun_lev;
	long	raf_n;
	long	n;
	item_t	*item;
	long	i;

	if( chr == NULL )
		return FALSE;

	dun_lev = dun->lev + WPN_RANDM_ART_DUN_LEV_DIV;
	raf_n = labs( dun_lev ) / WPN_RANDM_ART_DUN_LEV_DIV;

	for( i = LOOP_MAX_1000; i > 0; i-- ){
		n = randm( wpn_tab_max_n );
		if( wpn_tab[n].name == NULL )
			continue;
		if( wpn_tab[n].kind == WPN_KIND_NULL )
			continue;

		item = make_item_wpn( dun_lev, n, FALSE );
		if( item == NULL )
			continue;

		make_item_wpn_randm_art_n( &(item->dat.wpn), raf_n );
		identify_item( item );
		set_item_name( item );

		if( give_mbr_item( (mbr_t *)chr, item, TRUE ) ){
			print_msg( FLG_NULL, MSG_GIVE_WISH_ARTIFACT_1,
					chr->name );
			print_msg( FLG_NULL, MSG_GIVE_WISH_ARTIFACT_2,
					item->name );
			return TRUE;
		} else {
			return FALSE;
		}
	}

	return FALSE;
}

/***************************************************************
* 防具アーティファクトの望み
* chr_t *chr : キャラクタ
* wish_level_t wish_level : 魔神の種類
* return : 望みが叶えられたか?
***************************************************************/

bool_t	fx_wish_artifact_armor( chr_t *chr, wish_level_t wish_level )
{
	dun_t	*dun = get_dun();
	long	dun_lev;
	long	raf_n;
	long	n;
	item_t	*item;
	long	i;

	if( chr == NULL )
		return FALSE;

	dun_lev = dun->lev + ARMOR_RANDM_ART_DUN_LEV_DIV;
	raf_n = labs( dun_lev ) / ARMOR_RANDM_ART_DUN_LEV_DIV;

	for( i = LOOP_MAX_1000; i > 0; i-- ){
		n = randm( armor_tab_max_n );
		if( armor_tab[n].name == NULL )
			continue;
		if( armor_tab[n].kind == ARMOR_KIND_NULL )
			continue;

		item = make_item_armor( dun_lev, n, FALSE );
		if( item == NULL )
			continue;

		make_item_armor_randm_art_n( &(item->dat.armor), raf_n );
		identify_item( item );
		set_item_name( item );

		if( give_mbr_item( (mbr_t *)chr, item, TRUE ) ){
			print_msg( FLG_NULL, MSG_GIVE_WISH_ARTIFACT_1,
					chr->name );
			print_msg( FLG_NULL, MSG_GIVE_WISH_ARTIFACT_2,
					item->name );
			return TRUE;
		} else {
			return FALSE;
		}
	}

	return FALSE;
}

/**/

void	set_item_face( item_t *item )
{
	if( item == NULL )
		return;

	item->mjr = FACE_MJR_NULL;
	item->mnr = FACE_MNR_NULL;

	switch( item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		if( g_flg_debug ){
			item->mjr = FACE_MJR_ERR;
			item->mnr = FACE_MNR_ERR;
		} else {
			item->mjr = FACE_MJR_NULL;
			item->mnr = FACE_MNR_NULL;
		}
		break;
	case ITEM_KIND_WPN:
		item->mjr = FACE_MJR_WEAPON;
		item->mnr = item->tab.wpn->mnr;
		break;
	case ITEM_KIND_ARMOR:
		item->mjr = FACE_MJR_ARMOR;
		item->mnr = item->tab.armor->mnr;
		break;
	case ITEM_KIND_POTION:
		item->mjr = FACE_MJR_POTION;
		item->mnr = FACE_MNR_NULL;
		break;
	case ITEM_KIND_SCROLL:
		item->mjr = FACE_MJR_SCROLL;
		item->mnr = FACE_MNR_NULL;
		break;
	case ITEM_KIND_STICK:
		item->mjr = FACE_MJR_STICK;
		if( item->dat.stick.kind == STICK_KIND_WAND )
			item->mnr = FACE_MNR_WAND;
		if( item->dat.stick.kind == STICK_KIND_ROD )
			item->mnr = FACE_MNR_ROD;
		if( item->dat.stick.kind == STICK_KIND_STAFF )
			item->mnr = FACE_MNR_STAFF;
		break;
	case ITEM_KIND_ACCE:
		item->mjr = FACE_MJR_ACCESSORY;
		item->mnr = item->tab.acce->mnr;
		break;
	case ITEM_KIND_INST:
		item->mjr = FACE_MJR_INST;
		item->mnr = FACE_MNR_INST;
		/* item->mnr = item->tab.inst->mnr; */
		break;
	case ITEM_KIND_ANTHOLOGY:
		item->mjr = FACE_MJR_MISC;
		item->mnr = FACE_MNR_ANTHOLOGY;
		break;
	case ITEM_KIND_LIGHT:
		item->mjr = FACE_MJR_MISC;
		item->mnr = FACE_MNR_LIGHT;
		break;
	case ITEM_KIND_SPIKE:
		item->mjr = FACE_MJR_MISC;
		item->mnr = FACE_MNR_SPIKE;
		break;
	case ITEM_KIND_FOOD:
		item->mjr = FACE_MJR_FOOD;
		item->mnr = FACE_MNR_NULL;
		break;
	case ITEM_KIND_CHEST:
		item->mjr = FACE_MJR_CHEST;
		item->mnr = FACE_MNR_NULL;
		break;
	case ITEM_KIND_TOBACCO:
		item->mjr = FACE_MJR_MISC;
		item->mnr = FACE_MNR_TOBACCO;
		break;
	case ITEM_KIND_PIPE:
		item->mjr = FACE_MJR_MISC;
		item->mnr = FACE_MNR_PIPE;
		break;
	case ITEM_KIND_DISPOSAL:
		item->mjr = FACE_MJR_MISC;
		item->mnr = FACE_MNR_DISPOSAL;
		break;
	case ITEM_KIND_RARE_GOODS:
		item->mjr = FACE_MJR_MISC;
		item->mnr = FACE_MNR_RARE_GOODS;
		break;
	case ITEM_KIND_BONE:
		item->mjr = FACE_MJR_MISC;

		if( item->dat.bone.mnstr_tab == NULL ){
			item->mnr = FACE_MNR_BONE_GOOD;
		} else if( item->dat.bone.mnstr_tab->attitude
				== ATTITUDE_ENEMY ){
			item->mnr = FACE_MNR_BONE_EVIL;
		} else {
			item->mnr = FACE_MNR_BONE_GOOD;
		}

		break;
	case ITEM_KIND_COIN:
		item->mjr = FACE_MJR_COIN;
		item->mnr = item->tab.coin->mnr;
		break;
	case ITEM_KIND_JUNK:
		item->mjr = FACE_MJR_MISC;
		item->mnr = FACE_MNR_JUNK;
		break;
	/* default: */
	}
}

/**/

void	set_item_name( item_t *item )
{
	if( item == NULL )
		return;

	set_item_face( item );

	strcpy( item->name, MSG_ITEM_MJR_NAME_ERR );

	switch( item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		strcpy( item->name, MSG_ITEM_MJR_NAME_ERR );
		break;
	case ITEM_KIND_WPN:
		set_item_name_wpn( item );
		break;
	case ITEM_KIND_ARMOR:
		set_item_name_armor( item );
		break;
	case ITEM_KIND_POTION:
		set_item_name_potion( item );
		break;
	case ITEM_KIND_SCROLL:
		set_item_name_scroll( item );
		break;
	case ITEM_KIND_STICK:
		set_item_name_stick( item );
		break;
	case ITEM_KIND_ACCE:
		set_item_name_acce( item );
		break;
	case ITEM_KIND_INST:
		set_item_name_inst( item );
		break;
	case ITEM_KIND_ANTHOLOGY:
		set_item_name_anthology( item );
		break;
	case ITEM_KIND_LIGHT:
		set_item_name_light( item );
		break;
	case ITEM_KIND_SPIKE:
		set_item_name_spike( item );
		break;
	case ITEM_KIND_FOOD:
		set_item_name_food( item );
		break;
	case ITEM_KIND_CHEST:
		set_item_name_chest( item );
		break;
	case ITEM_KIND_TOBACCO:
		set_item_name_tobacco( item );
		break;
	case ITEM_KIND_PIPE:
		set_item_name_pipe( item );
		break;
	case ITEM_KIND_DISPOSAL:
		set_item_name_disposal( item );
		break;
	case ITEM_KIND_RARE_GOODS:
		set_item_name_rare_goods( item );
		break;
	case ITEM_KIND_BONE:
		set_item_name_bone( item );
		break;
	case ITEM_KIND_COIN:
		set_item_name_coin( item );
		break;
	case ITEM_KIND_JUNK:
		set_item_name_junk( item );
		break;
	/* default: */
	}
}

/**/

bool_t	set_item_name_wpn( item_t *item )
{
	wpn_t	*wp;
	const char	*str_name;
	const char	*str_randm_art;
	const char	*str_boomerang;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_WPN )
		return FALSE;
	if( item->tab.wpn == NULL )
		return FALSE;
	if( item->tab.wpn->i_name == NULL )
		return FALSE;

	wp = &(item->dat.wpn);

	str_randm_art = get_wpn_randm_art_name( item );

	if( chk_flg( wp->flg, FLG_WPN_TAB_RET ) )
		str_boomerang = MSG_FLG_BOOMERANG;
	else
		str_boomerang = "";

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.wpn->i_name;
		else
			str_name = item->alias;

		if( wp->slayer == FACE_MJR_NULL ){
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_WPN_IDENTIFIED,
					item->mjr, item->mnr,
					item->n, str_name,
					wp->add_hit,
					wp->add_crtcl,
					wp->add_dam,
					str_randm_art,
					str_boomerang );
		} else {
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_WPN_SLAYER,
					item->mjr, item->mnr,
					item->n, str_name,
					wp->slayer,
					wp->add_hit,
					wp->add_crtcl,
					wp->add_dam,
					str_randm_art,
					str_boomerang );
		}
	} else {
		if( item->alias[0] == '\0' )
			str_name = item->tab.wpn->name;
		else
			str_name = item->alias;

		sn_printf( item->name,
				ITEM_NAME_MAX_BYTE,
				MSG_FMT_WPN_NOT_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name );
	}

	return TRUE;
}

/**/

const char	*get_wpn_randm_art_name( item_t *item )
{
	static char	str[ITEM_NAME_MAX_BYTE + 1];
	wpn_randm_art_t	*art;
	long	n;
	long	i;

	if( item == NULL )
		return "";
	if( item->kind != ITEM_KIND_WPN )
		return "";
	if( item->dat.wpn.randm_art[0].kind == WPN_RANDM_ART_KIND_NULL )
		return "";

	art = item->dat.wpn.randm_art;

	n = 0;
	str[n++] = ' ';
	str[n++] = '{';

	for( i = 0; i < WPN_RANDM_ART_LS_MAX_N; i++ ){
		if( art[i].kind == WPN_RANDM_ART_KIND_NULL )
			break;
		if( art[i].mjr == WPN_RANDM_ART_MJR_NULL )
			break;
		if( art[i].mnr == WPN_RANDM_ART_MNR_NULL )
			break;
	}
	if( i > 99 )
		i = 99;
	str[n++] = '0' + ((i / 10) % 10);
	str[n++] = '0' + (i % 10);

	for( i = 0; i < WPN_RANDM_ART_LS_MAX_N; i++ ){
		if( art[i].kind == WPN_RANDM_ART_KIND_NULL )
			break;
		if( art[i].mjr == WPN_RANDM_ART_MJR_NULL )
			break;
		if( art[i].mnr == WPN_RANDM_ART_MNR_NULL )
			break;

		if( i >= WPN_RANDM_ART_NAME_MAX_N ){
#if	FLG_RANDM_ART_NAME_MAX_N_DOT
			str[n++] = '.';
			str[n++] = '.';
#endif
			break;
		}

		str[n++] = art[i].mjr;
		str[n++] = art[i].mnr;
	}
	str[n++] = '}';
	str[n++] = '\0';

	return str;
}

/**/

bool_t	set_item_name_armor( item_t *item )
{
	armor_t	*ap;
	char	*protect;
	const char	*str_randm_art;
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_ARMOR )
		return FALSE;
	if( item->tab.armor == NULL )
		return FALSE;
	if( item->tab.armor->i_name == NULL )
		return FALSE;

	ap = &(item->dat.armor);

	str_randm_art = get_armor_randm_art_name( item );

	if( chk_flg( item->flg, FLG_ITEM_PROTECTED ) )
		protect = MSG_PROTECTED_ARMOR;
	else
		protect = MSG_NULL;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.armor->i_name;
		else
			str_name = item->alias;

		sn_printf( item->name,
				ITEM_NAME_MAX_BYTE,
				MSG_FMT_ARMOR_IDENTIFIED,
				item->mjr, item->mnr,
				item->n,
				str_name,
				ap->add_def,
				ap->add_crtcl,
				ap->add_ac,
				str_randm_art,
				protect );
	} else {
		if( item->alias[0] == '\0' )
			str_name = item->tab.armor->name;
		else
			str_name = item->alias;

		sn_printf( item->name,
				ITEM_NAME_MAX_BYTE,
				MSG_FMT_ARMOR_NOT_IDENTIFIED,
				item->mjr, item->mnr,
				item->n,
				str_name );
	}

	return TRUE;
}

/**/

const char	*get_armor_randm_art_name( item_t *item )
{
	static char	str[ITEM_NAME_MAX_BYTE + 1];
	armor_randm_art_t	*art;
	long	n;
	long	i;

	if( item == NULL )
		return "";
	if( item->kind != ITEM_KIND_ARMOR )
		return "";
	if( item->dat.armor.randm_art[0].kind == ARMOR_RANDM_ART_KIND_NULL )
		return "";

	art = item->dat.armor.randm_art;

	n = 0;
	str[n++] = ' ';
	str[n++] = '{';

	for( i = 0; i < ARMOR_RANDM_ART_LS_MAX_N; i++ ){
		if( art[i].kind == ARMOR_RANDM_ART_KIND_NULL )
			break;
		if( art[i].mjr == ARMOR_RANDM_ART_MJR_NULL )
			break;
		if( art[i].mnr == ARMOR_RANDM_ART_MNR_NULL )
			break;
	}
	if( i > 99 )
		i = 99;
	str[n++] = '0' + ((i / 10) % 10);
	str[n++] = '0' + (i % 10);

	for( i = 0; i < ARMOR_RANDM_ART_LS_MAX_N; i++ ){
		if( art[i].kind == ARMOR_RANDM_ART_KIND_NULL )
			break;
		if( art[i].mjr == ARMOR_RANDM_ART_MJR_NULL )
			break;
		if( art[i].mnr == ARMOR_RANDM_ART_MNR_NULL )
			break;

		if( i >= ARMOR_RANDM_ART_NAME_MAX_N ){
#if	FLG_RANDM_ART_NAME_MAX_N_DOT
			str[n++] = '.';
			str[n++] = '.';
#endif
			break;
		}

		str[n++] = art[i].mjr;
		str[n++] = art[i].mnr;
	}
	str[n++] = '}';
	str[n++] = '\0';

	return str;
}

/**/

bool_t	set_item_name_potion( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_POTION )
		return FALSE;
	if( item->tab.potion == NULL )
		return FALSE;
	if( item->tab.potion->name == NULL )
		return FALSE;
	if( item->tab.potion->color == NULL )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED )
			|| item->tab.potion->flg_identified ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.potion->name;
		else
			str_name = item->alias;

		item->flg |= FLG_ITEM_IDENTIFIED;
		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_POTION_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name );
	} else {
		if( item->alias[0] == '\0' )
			str_name = item->tab.potion->color;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_POTION_NOT_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name );
	}

	return TRUE;
}

/**/

bool_t	set_item_name_scroll( item_t *item )
{
	const char	*str_name;
	long	lev;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_SCROLL )
		return FALSE;
	if( item->tab.scroll == NULL )
		return FALSE;
	if( item->tab.scroll->name == NULL )
		return FALSE;
	if( item->tab.scroll->ttl == NULL )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED )
			|| item->tab.scroll->flg_identified ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.scroll->name;
		else
			str_name = item->alias;

		item->flg |= FLG_ITEM_IDENTIFIED;

		lev = get_scroll_nin_lev( item->tab.scroll->kind );
		if( lev <= -1 ){
			sn_printf( item->name, ITEM_NAME_MAX_BYTE,
					MSG_FMT_SCROLL_IDENTIFIED,
					item->mjr, item->mnr,
					item->n, str_name );
		} else {
			sn_printf( item->name, ITEM_NAME_MAX_BYTE,
					MSG_FMT_SCROLL_NIN,
					item->mjr, item->mnr,
					item->n, str_name,
					lev );
		}
	} else {
		if( item->alias[0] == '\0' )
			str_name = item->tab.scroll->ttl;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_SCROLL_NOT_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name );
	}

	return TRUE;
}

/**/

long	get_scroll_nin_lev( scroll_kind_t scroll_kind )
{
	spell_kind_t	kind;
	spell_tab_t	*spell_tab;

	kind = SPELL_KIND_NULL;

	switch( scroll_kind ){
	case SCROLL_KIND_TYPHOON:
		kind = SPELL_KIND_TYPHOON;
		break;
	case SCROLL_KIND_CONFLAGRATION:
		kind = SPELL_KIND_CONFLAGRATION;
		break;
	case SCROLL_KIND_EARTHQUAKE:
		kind = SPELL_KIND_EARTHQUAKE;
		break;
	case SCROLL_KIND_THUNDERCLOUD:
		kind = SPELL_KIND_THUNDERCLOUD;
		break;
	case SCROLL_KIND_INUNDATION:
		kind = SPELL_KIND_INUNDATION;
		break;
	case SCROLL_KIND_SUBSTITUTE:
		kind = SPELL_KIND_SUBSTITUTE;
		break;
	case SCROLL_KIND_BURNING_HANDS:
		kind = SPELL_KIND_BURNING_HANDS;
		break;
	case SCROLL_KIND_RALLY:
		kind = SPELL_KIND_RALLY;
		break;
	case SCROLL_KIND_IRON_MAN:
		kind = SPELL_KIND_IRON_MAN;
		break;
	case SCROLL_KIND_MIND_READING:
		kind = SPELL_KIND_MIND_READING;
		break;
	default:
		return -1;
	}

	if( kind == SPELL_KIND_NULL )
		return -1;

	spell_tab = get_spell_tab( kind );
	if( spell_tab == NULL )
		return -1;

	return( spell_tab->lev );
}

/**/

bool_t	set_item_name_stick( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_STICK )
		return FALSE;
	if( item->tab.stick == NULL )
		return FALSE;
	if( item->tab.stick->name == NULL )
		return FALSE;
	if( item->tab.stick->material == NULL )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED )
			|| item->tab.stick->flg_identified ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.stick->name;
		else
			str_name = item->alias;

		item->flg |= FLG_ITEM_IDENTIFIED;
		if( item->dat.stick.kind == STICK_KIND_WAND ){
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_WAND_IDENTIFIED,
					item->mjr, item->mnr,
					item->n,
					str_name,
					item->dat.stick.n );
		}
		if( item->dat.stick.kind == STICK_KIND_ROD ){
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_ROD_IDENTIFIED,
					item->mjr, item->mnr,
					item->n,
					str_name,
					item->dat.stick.n );
		}
		if( item->dat.stick.kind == STICK_KIND_STAFF ){
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_STAFF_IDENTIFIED,
					item->mjr, item->mnr,
					item->n,
					str_name,
					item->dat.stick.n );
		}
	} else {
		if( item->alias[0] == '\0' )
			str_name = item->tab.stick->material;
		else
			str_name = item->alias;

		if( item->dat.stick.kind == STICK_KIND_WAND ){
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_WAND_NOT_IDENTIFIED,
					item->mjr, item->mnr,
					item->n, str_name );
		}
		if( item->dat.stick.kind == STICK_KIND_ROD ){
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_ROD_NOT_IDENTIFIED,
					item->mjr, item->mnr,
					item->n, str_name );
		}
		if( item->dat.stick.kind == STICK_KIND_STAFF ){
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_STAFF_NOT_IDENTIFIED,
					item->mjr, item->mnr,
					item->n, str_name );
		}
	}

	return TRUE;
}

/**/

bool_t	set_item_name_acce( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_ACCE )
		return FALSE;
	if( item->tab.acce == NULL )
		return FALSE;
	if( item->tab.acce->name == NULL )
		return FALSE;
	if( item->tab.acce->material == NULL )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED )
			|| item->tab.acce->flg_identified ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.acce->name;
		else
			str_name = item->alias;

		item->flg |= FLG_ITEM_IDENTIFIED;
		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_ACCE_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name );
	} else {
		if( item->alias[0] == '\0' )
			str_name = item->tab.acce->material;
		else
			str_name = item->alias;

		switch( item->dat.acce.kind ){
		case ACCE_KIND_NULL:
		case ACCE_KIND_MAX_N:
			strcpy( item->name, MSG_ITEM_MJR_NAME_ERR );
			break;
		case ACCE_KIND_RING:
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_RING_NOT_IDENTIFIED,
					item->mjr, item->mnr,
					item->n,
					str_name );
			break;
		case ACCE_KIND_AMULET:
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_AMULET_NOT_IDENTIFIED,
					item->mjr, item->mnr,
					item->n,
					str_name );
			break;
		case ACCE_KIND_NECKLACE:
			sn_printf( item->name,
					ITEM_NAME_MAX_BYTE,
					MSG_FMT_NECKLACE_NOT_IDENTIFIED,
					item->mjr, item->mnr,
					item->n,
					str_name );
			break;
		/* default: */
		}
	}

	return TRUE;
}

/**/

bool_t	set_item_name_inst( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_INST )
		return FALSE;
	if( item->tab.inst == NULL )
		return FALSE;
	if( item->tab.inst->name == NULL )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) ){
		char	*str_limit, *str_tmp;
		static char	str_spell[ITEM_NAME_MAX_BYTE + 1];

		if( item->alias[0] == '\0' )
			str_name = item->tab.inst->name;
		else
			str_name = item->alias;

		if( item->dat.inst.flg_limit )
			str_limit = MSG_INST_LIMIT;
		else
			str_limit = MSG_NULL;

		if( item->dat.inst.spell_kind != SPELL_KIND_NULL ){
			str_tmp = get_spell_name(
					item->dat.inst.spell_kind );
			if( str_tmp == NULL )
				return FALSE;
			sn_printf( str_spell, ITEM_NAME_MAX_BYTE,
					MSG_INST_SPELL, str_tmp );
		} else {
			str_spell[0] = '\0';
		}

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_INST_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name,
				str_limit, str_spell );
	} else {
		if( item->alias[0] == '\0' )
			str_name = item->tab.inst->name;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_INST_NOT_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name );
	}

	return TRUE;
}

/**/

bool_t	set_item_name_anthology( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_ANTHOLOGY )
		return FALSE;
	if( item->tab.anthology == NULL )
		return FALSE;
	if( item->tab.anthology->name == NULL )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.anthology->name;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_ANTHOLOGY_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name );
	} else {
		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_ANTHOLOGY_NOT_IDENTIFIED,
				item->mjr, item->mnr,
				item->n );
	}

	return TRUE;
}

/**/

bool_t	set_item_name_light( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_LIGHT )
		return FALSE;
	if( item->tab.light == NULL )
		return FALSE;
	if( item->tab.light->name == NULL )
		return FALSE;

	if( item->dat.light.flg_used ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.light->i_name;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_LIGHT_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name,
				item->dat.light.turn );
	} else {
		if( item->alias[0] == '\0' )
			str_name = item->tab.light->name;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_LIGHT_NOT_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name,
				item->dat.light.turn );
	}

	return TRUE;
}

/**/

bool_t	set_item_name_spike( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_SPIKE )
		return FALSE;

	if( item->alias[0] == '\0' )
		str_name = MSG_SPIKE;
	else
		str_name = item->alias;

	sn_printf( item->name, ITEM_NAME_MAX_BYTE,
			MSG_FMT_SPIKE_IDENTIFIED,
			item->mjr, item->mnr,
			item->n, str_name );

	return TRUE;
}

/**/

bool_t	set_item_name_food( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_FOOD )
		return FALSE;
	if( item->tab.food == NULL )
		return FALSE;
	if( item->tab.food->name == NULL )
		return FALSE;

	if( item->alias[0] == '\0' )
		str_name = item->tab.food->name;
	else
		str_name = item->alias;

	sn_printf( item->name, ITEM_NAME_MAX_BYTE,
			MSG_FMT_FOOD_IDENTIFIED,
			item->mjr, item->mnr,
			item->n, str_name );

	return TRUE;
}

/**/

bool_t	set_item_name_chest( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_CHEST )
		return FALSE;

	if( item->alias[0] == '\0' )
		str_name = MSG_CHEST;
	else
		str_name = item->alias;

	sn_printf( item->name, ITEM_NAME_MAX_BYTE,
			MSG_FMT_CHEST_IDENTIFIED,
			item->mjr, item->mnr,
			item->n, str_name );

	return TRUE;
}

/**/

bool_t	set_item_name_tobacco( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_TOBACCO )
		return FALSE;
	if( item->tab.tobacco == NULL )
		return FALSE;
	if( item->tab.tobacco->name == NULL )
		return FALSE;
	if( item->tab.tobacco->brand_name == NULL )
		return FALSE;

	if( item->dat.tobacco.turn > 0 ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.tobacco->name;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_TOBACCO_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name,
				item->tab.tobacco->brand_name,
				item->dat.tobacco.turn );
	} else {
		if( item->alias[0] == '\0' )
			str_name = MSG_TOBACCO_STUB;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_TOBACCO_STUB_IDENTIFIED,
				item->mjr, item->mnr,
				item->n,
				str_name );
	}

	return TRUE;
}

/**/

bool_t	set_item_name_pipe( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_PIPE )
		return FALSE;
	if( item->tab.pipe == NULL )
		return FALSE;
	if( item->tab.pipe->name == NULL )
		return FALSE;

	if( item->dat.pipe.consume_turn > 0 ){
		if( item->alias[0] == '\0' )
			str_name = item->tab.pipe->name;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_PIPE_IDENTIFIED,
				item->mjr, item->mnr,
				item->n, str_name,
				item->dat.pipe.turn );
	} else {
		if( item->alias[0] == '\0' )
			str_name = MSG_PIPE_STUB;
		else
			str_name = item->alias;

		sn_printf( item->name, ITEM_NAME_MAX_BYTE,
				MSG_FMT_PIPE_STUB_IDENTIFIED,
				item->mjr, item->mnr,
				item->n,
				str_name );
	}

	return TRUE;
}

/**/

bool_t	set_item_name_disposal( item_t *item )
{
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_DISPOSAL )
		return FALSE;

	sn_printf( item->name, ITEM_NAME_MAX_BYTE,
			MSG_FMT_DISPOSAL_IDENTIFIED,
			item->mjr, item->mnr,
			item->n,
			item->dat.disposal.n,
			item->dat.disposal.max_n );

	return TRUE;
}

/**/

bool_t	set_item_name_rare_goods( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_RARE_GOODS )
		return FALSE;
	if( item->tab.rare_goods == NULL )
		return FALSE;
	if( item->tab.rare_goods->name == NULL )
		return FALSE;

	if( item->alias[0] == '\0' )
		str_name = item->tab.rare_goods->name;
	else
		str_name = item->alias;

	sn_printf( item->name, ITEM_NAME_MAX_BYTE,
			MSG_FMT_RARE_GOODS_IDENTIFIED,
			item->mjr, item->mnr,
			item->n, str_name );

	return TRUE;
}

/**/

bool_t	set_item_name_bone( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_BONE )
		return FALSE;
	if( item->dat.bone.mnstr_tab == NULL )
		return FALSE;
	if( item->dat.bone.mnstr_tab->name == NULL )
		return FALSE;

	if( item->alias[0] == '\0' )
		str_name = item->dat.bone.mnstr_tab->name;
	else
		str_name = item->alias;

	sn_printf( item->name, ITEM_NAME_MAX_BYTE,
			MSG_FMT_BONE_IDENTIFIED,
			item->mjr, item->mnr,
			item->n, str_name );

	return TRUE;
}

/**/

bool_t	set_item_name_coin( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_COIN )
		return FALSE;
	if( item->tab.coin == NULL )
		return FALSE;
	if( item->tab.coin->name == NULL )
		return FALSE;

	if( item->alias[0] == '\0' )
		str_name = item->tab.coin->name;
	else
		str_name = item->alias;

	sn_printf( item->name, ITEM_NAME_MAX_BYTE,
			MSG_FMT_COIN_IDENTIFIED,
			item->mjr, item->mnr,
			item->n, str_name );

	return TRUE;
}

/**/

bool_t	set_item_name_junk( item_t *item )
{
	const char	*str_name;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_JUNK )
		return FALSE;

	if( item->alias[0] == '\0' )
		str_name = MSG_JUNK;
	else
		str_name = item->alias;

	sn_printf( item->name, ITEM_NAME_MAX_BYTE,
			MSG_FMT_JUNK_IDENTIFIED,
			item->mjr, item->mnr,
			item->n, str_name );

	return TRUE;
}

/**/

bool_t	clean_all_disposal( mbr_t *mbr )
{
	item_t	*head, *p, *item;
	long	i;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	head = get_mbr_item_asgn( mbr );
	if( head == NULL )
		return FALSE;
	p = head->next->next;
	for( i = 0; i < MBR_ITEM_MAX_N; i++, p = p->next ){
		item = p->prev;

		if( item == head )
			break;

		if( item->kind == ITEM_KIND_DISPOSAL ){
			item->dat.disposal.n = 0;
			set_item_name( item );
		}
	}

	p = get_mbr_item_asgn_equip( mbr );
	if( p == NULL )
		return FALSE;
	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		item = &(p[i]);

		if( item->kind == ITEM_KIND_DISPOSAL ){
			item->dat.disposal.n = 0;
			set_item_name( item );
		}
	}

	return TRUE;
}

/**/

bool_t	identify_item( item_t *item )
{
	bool_t	ret;

	if( item == NULL )
		return FALSE;

	ret = FALSE;
	switch( item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		return FALSE;
	case ITEM_KIND_WPN:
	case ITEM_KIND_ARMOR:
	case ITEM_KIND_INST:
	case ITEM_KIND_ANTHOLOGY:
	case ITEM_KIND_LIGHT:
	case ITEM_KIND_SPIKE:
	case ITEM_KIND_FOOD:
	case ITEM_KIND_CHEST:
	case ITEM_KIND_TOBACCO:
	case ITEM_KIND_PIPE:
	case ITEM_KIND_DISPOSAL:
	case ITEM_KIND_RARE_GOODS:
	case ITEM_KIND_BONE:
	case ITEM_KIND_COIN:
	case ITEM_KIND_JUNK:
		item->flg |= FLG_ITEM_IDENTIFIED;
		set_item_name( item );
		ret = TRUE;
		break;
	case ITEM_KIND_POTION:
		ret = identify_potion( item );
		break;
	case ITEM_KIND_SCROLL:
		ret = identify_scroll( item );
		break;
	case ITEM_KIND_STICK:
		ret = identify_stick( item );
		break;
	case ITEM_KIND_ACCE:
		ret = identify_acce( item );
		break;
	/* default: */
	}

	set_item_name( item );
	print_msg( FLG_NULL, MSG_FMT_IDENTIFY_ITEM, item->name );

	return ret;
}

/**/

bool_t	identify_potion( item_t *item )
{
	long	i;
	item_t	*p;
	potion_tab_t	*tab;
	party_t	*pty;

	if( item == NULL )
		return FALSE;

	if( item->kind != ITEM_KIND_POTION )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) )
		return FALSE;

	tab = get_potion_tab( item->dat.potion.kind );
	if( tab == NULL )
		return FALSE;
	tab->flg_identified = TRUE;

	pty = get_party();
	if( pty == NULL )
		return FALSE;
	for( i = 0; i < MBR_MAX_N; i++ ){
		item_t	*head;

		head = get_mbr_item_asgn( pty->mbr[i] );
		if( head == NULL )
			continue;

		for( p = head->next; p != head; p = p->next ){
			if( p == NULL )
				break;
			if( p->kind != ITEM_KIND_POTION )
				continue;
			if( p->dat.potion.kind != item->dat.potion.kind )
				continue;

			p->flg |= FLG_ITEM_IDENTIFIED;
			set_item_name( p );
		}
	}

	return TRUE;
}

/**/

bool_t	identify_scroll( item_t *item )
{
	long	i;
	item_t	*p;
	scroll_tab_t	*tab;
	party_t	*pty;

	if( item == NULL )
		return FALSE;

	if( item->kind != ITEM_KIND_SCROLL )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) )
		return FALSE;

	tab = get_scroll_tab( item->dat.scroll.kind );
	if( tab == NULL )
		return FALSE;
	tab->flg_identified = TRUE;

	pty = get_party();
	if( pty == NULL )
		return FALSE;
	for( i = 0; i < MBR_MAX_N; i++ ){
		item_t	*head;

		head = get_mbr_item_asgn( pty->mbr[i] );
		if( head == NULL )
			continue;

		for( p = head->next; p != head; p = p->next ){
			if( p == NULL )
				break;
			if( p->kind != ITEM_KIND_SCROLL )
				continue;
			if( p->dat.scroll.kind != item->dat.scroll.kind )
				continue;

			p->flg |= FLG_ITEM_IDENTIFIED;
			set_item_name( p );
		}
	}

	return TRUE;
}

/**/

bool_t	identify_stick( item_t *item )
{
	long	i;
	item_t	*p;
	stick_tab_t	*tab;
	party_t	*pty;

	if( item == NULL )
		return FALSE;

	if( item->kind != ITEM_KIND_STICK )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) )
		return FALSE;

	tab = get_stick_tab( item->dat.stick.kind,
			item->dat.stick.spell_kind );
	if( tab == NULL )
		return FALSE;
	tab->flg_identified = TRUE;

	pty = get_party();
	if( pty == NULL )
		return FALSE;
	for( i = 0; i < MBR_MAX_N; i++ ){
		item_t	*head;

		head = get_mbr_item_asgn( pty->mbr[i] );
		if( head == NULL )
			continue;

		for( p = head->next; p != head; p = p->next ){
			if( p == NULL )
				break;
			if( p->kind != ITEM_KIND_STICK )
				continue;
			if( p->dat.stick.kind != item->dat.stick.kind )
				continue;
			if( p->dat.stick.spell_kind
					!= item->dat.stick.spell_kind )
				continue;

			p->flg |= FLG_ITEM_IDENTIFIED;
			set_item_name( p );
		}
	}

	return TRUE;
}

/**/

bool_t	identify_acce( item_t *item )
{
	long	i;
	item_t	*p;
	acce_tab_t	*tab;
	party_t	*pty;

	if( item == NULL )
		return FALSE;

	if( item->kind != ITEM_KIND_ACCE )
		return FALSE;

	if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) )
		return FALSE;

	tab = get_acce_tab( item->dat.acce.ring_kind,
			item->dat.acce.amulet_kind,
			item->dat.acce.necklace_kind );
	if( tab == NULL )
		return FALSE;
	tab->flg_identified = TRUE;

	pty = get_party();
	if( pty == NULL )
		return FALSE;
	for( i = 0; i < MBR_MAX_N; i++ ){
		item_t	*head;

		head = get_mbr_item_asgn( pty->mbr[i] );
		if( head == NULL )
			continue;

		for( p = head->next; p != head; p = p->next ){
			if( p == NULL )
				break;
			if( p->kind != ITEM_KIND_ACCE )
				continue;
			if( p->dat.acce.ring_kind
					!= item->dat.acce.ring_kind )
				continue;
			if( p->dat.acce.amulet_kind
					!= item->dat.acce.amulet_kind )
				continue;
			if( p->dat.acce.necklace_kind
					!= item->dat.acce.necklace_kind )
				continue;

			p->flg |= FLG_ITEM_IDENTIFIED;
			set_item_name( p );
		}
	}

	return TRUE;
}

/**/

bool_t	send_item( mbr_t *mbr )
{
	chr_t	*dst, *src;
	item_t	*item;
	long	n;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	dst = (chr_t *)(mbr->act.p2);
	src = mbr;
	item = (item_t *)(mbr->act.p);
	n = mbr->act.n;

	return hand_item( dst, src, item, n );
}

/**/

bool_t	receive_item( mbr_t *mbr )
{
	chr_t	*dst, *src;
	item_t	*item;
	long	n;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	dst = mbr;
	src = (chr_t *)(mbr->act.p2);
	item = (item_t *)(mbr->act.p);
	n = mbr->act.n;

	return hand_item( dst, src, item, n );
}

/**/

bool_t	hand_item( chr_t *dst, chr_t *src, item_t *item, long n )
{
	item_t	*tmp;

	if( dst == NULL )
		return FALSE;
	if( !is_mbr( dst ) )
		return FALSE;
	if( src == NULL )
		return FALSE;
	if( !is_mbr( src ) )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( n > item->n )
		return FALSE;

	lost_trgt( item );

	tmp = alloc_item();
	if( tmp == NULL )
		return FALSE;

	copy_item( tmp, item );
	inc_item( tmp, -(tmp->n - n) );

	if( give_mbr_item( dst, tmp, FALSE ) ){
		inc_item( item, -n );
	} else {
		if( give_mbr_item( src, tmp, TRUE ) )
			inc_item( item, -n );

		return FALSE;
	}

	return TRUE;
}

/**/

bool_t	put_item( item_t *item, long x, long y, long max_r, bool_t flg_mbr )
{
	long	r;
	dun_t	*dun;
	long	pre_x, pre_y;

	if( item == NULL )
		return FALSE;

	dun = get_dun();

	pre_x = item->x;
	pre_y = item->y;

	for( r = 0; r < max_r; r++ ){
		long	randm_n;
		long	dx, dy;

		randm_n = 0;

		for( dx = -r, dy = -r; dx <= +r; dx++ )
			put_item_sub( item, x + dx, y + dy, &randm_n );

		for( dx = +r, dy = -r; dy <= +r; dy++ )
			put_item_sub( item, x + dx, y + dy, &randm_n );

		for( dx = +r, dy = +r; dx >= -r; dx-- )
			put_item_sub( item, x + dx, y + dy, &randm_n );

		for( dx = -r, dy = +r; dy >= -r; dy-- )
			put_item_sub( item, x + dx, y + dy, &randm_n );

		if( randm_n > 0 )
			 break;
	}
	if( r >= max_r ){
		item->x = pre_x;
		item->y = pre_y;
		return FALSE;
	}

	lost_trgt( item );

	ins_ls_item( &dun_item_asgn, item );

	dun->map.obj.mjr[item->y][item->x] = get_item_mjr( item );
	dun->map.obj.mnr[item->y][item->x] = get_item_mnr( item );
	if( flg_mbr )
		dun->map.obj.flg[item->y][item->x] |= FLG_MAP_OBJ_FIND;
	draw_item( item );

	return TRUE;
}

/**/

bool_t	put_item_sub( item_t *item, long x, long y, long *np )
{
	dun_t	*dun;

	if( item == NULL )
		return FALSE;

	if( !clip_pos( x, y ) )
		return FALSE;

	dun = get_dun();
	if( dun->map.obj.mjr[y][x] != FACE_MJR_FLOOR )
		return FALSE;
	if( dun->map.obj.mnr[y][x] != FACE_MNR_FLOOR )
		return FALSE;

	(*np)++;
	if( randm( *np ) == 0 ){
		item->x = x;
		item->y = y;
	}

	return TRUE;
}

/**/

bool_t	put_item_in_chest( item_t *p, long x, long y )
{
	dun_t	*dun;
	item_t	*chest;

	if( p == NULL )
		return FALSE;
	if( p->kind == ITEM_KIND_CHEST )
		return FALSE;	/* 箱の中に箱は入らない */

	dun = get_dun();
	if( dun->map.obj.mjr[y][x] != FACE_MJR_CHEST )
		return FALSE;

	chest = get_item( x, y );
	if( (chest == NULL) || (chest->kind != ITEM_KIND_CHEST) )
		return FALSE;

	if( chest->dat.chest.trap != NULL )
		return FALSE;

	if( count_ls_item( chest->dat.chest.contents, ITEM_KIND_NULL )
			>= CHEST_HOLD_MAX_N ){
		return FALSE;
	}

	p->x = MAP_DEL_X;
	p->y = MAP_DEL_Y;

	ins_ls_item( chest->dat.chest.contents, p );

	return TRUE;
}

/**/

bool_t	drop_item( long x, long y, item_t *item, long n )
{
	item_t	*tmp;

	if( item == NULL )
		return FALSE;

	lost_trgt( item );

	tmp = alloc_item();
	if( tmp == NULL )
		return FALSE;

	copy_item( tmp, item );
	inc_item( tmp, -(tmp->n - n) );

	if( put_item_in_chest( tmp, x, y ) ){
		inc_item( item, -n );
	} else if( put_item( tmp, x, y, PUT_ITEM_R, TRUE ) ){
		inc_item( item, -n );
	} else {
		del_item( tmp );
		return FALSE;
	}

	return TRUE;
}

/**/

bool_t	pick_up_item( mbr_t *mbr, long x, long y )
{
	item_t	*dp;
	dun_t	*dun;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	dp = get_item( x, y );
	if( dp == NULL )
		return FALSE;

	if( chk_flg( mbr->stat, FLG_STAT_FLY ) ){
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_ITEM_FLY, mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}

	set_item_name( dp );

	if( !give_mbr_item( mbr, dp, FALSE ) )
		return FALSE;

	print_msg( FLG_NULL, MSG_ITEM_PICK_UP, mbr->name, dp->name );

	if( dp->kind == ITEM_KIND_RARE_GOODS )
		chk_finish_request_rare_goods();

	dp->x = MAP_DEL_X;
	dp->y = MAP_DEL_Y;

	dun = get_dun();
	dun->map.obj.mjr[y][x] = FACE_MJR_FLOOR;
	dun->map.obj.mnr[y][x] = FACE_MNR_FLOOR;

	lost_trgt( (void *)dp );

	return TRUE;
}

/**/

bool_t	give_party_item(
	item_t *item,
	bool_t flg_force,
	bool_t flg_print
)
{
	party_t	*pty;
	long	i;

	pty = get_party();
	if( pty == NULL )
		return FALSE;

	for( i = 0; i < MBR_MAX_N; i++ )
		if( give_mbr_item_print( pty->mbr[i], item, FALSE, TRUE ) )
			return TRUE;

	if( !flg_force )
		return FALSE;

	for( i = 0; i < MBR_MAX_N; i++ )
		if( give_mbr_item_print( pty->mbr[i], item, TRUE, TRUE ) )
			return TRUE;

	return FALSE;
}

/**/

bool_t	give_mbr_item(
	mbr_t *mbr,
	item_t *item,
	bool_t flg_force
)
{
	return give_mbr_item_print( mbr, item, flg_force, FALSE );
}

/**/

bool_t	give_mbr_item_print(
	mbr_t *mbr,
	item_t *item,
	bool_t flg_force,
	bool_t flg_print
)
{
	item_t	*head;

	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	/* 普通に渡す */

	if( give_mbr_item_sub( mbr, item ) ){
		if( flg_print ){
			print_msg( FLG_NULL, MSG_GIVE_MBR_ITEM,
					mbr->name, item->name );
		}
		return TRUE;
	}

	/* 強制的に渡す */

	if( !flg_force )
		return FALSE;

	/* 床に置く */

	if( put_item( item, mbr->x, mbr->y, PUT_ITEM_R, TRUE ) ){
		if( flg_print ){
			print_msg( FLG_NULL, MSG_DROP_MBR_ITEM,
					mbr->name, item->name );
		}
		return TRUE;
	}

	/* アイテム・リストに強制で追加 */

	head = get_mbr_item_asgn( mbr );
	if( head == NULL )
		return FALSE;
	ins_ls_item( head, item );

	if( flg_print ){
		print_msg( FLG_NULL, MSG_GIVE_MBR_ITEM,
				mbr->name, item->name );
	}
	return TRUE;
}

/**/

bool_t	give_mbr_item_sub( mbr_t *mbr, item_t *item )
{
	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !chk_give_mbr_chest( mbr, item ) ){
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_GIVE_MBR_CHEST, mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}
	if( item->kind == ITEM_KIND_COIN ){
		mbr->gold += (item->n * item->tab.coin->value)
				/ _100_PERCENT;
		del_item( item );

		return TRUE;
	} else {
		item_t	*ls;

		ls = get_mbr_item_asgn( mbr );

		if( chk_ins_sort_item( ls, item, MBR_ITEM_MAX_N ) )
			if( ins_sort_item( ls, item ) )
				return TRUE;

		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_GIVE_MBR_ITEM, mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}

	return FALSE;
}

/**/

bool_t	equip_item_sel( mbr_t *mbr, item_t *item )
{
	item_t	*eq;
	bool_t	flg_r_null, flg_l_null;

	if( item == NULL )
		return FALSE;

	if( item->kind == ITEM_KIND_NULL )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;
	flg_r_null = (eq[EQUIP_KIND_RIGHT_HAND].kind == ITEM_KIND_NULL);
	flg_l_null = (eq[EQUIP_KIND_LEFT_HAND].kind == ITEM_KIND_NULL);

	if( (item->equip_kind == EQUIP_KIND_RIGHT_HAND)
			&& !flg_r_null && flg_l_null ){
		return equip_item( mbr, item, EQUIP_KIND_LEFT_HAND );
	} else if( (item->equip_kind == EQUIP_KIND_LEFT_HAND)
			&& !flg_l_null && flg_r_null ){
		return equip_item( mbr, item, EQUIP_KIND_RIGHT_HAND );
	} else {
		return equip_item( mbr, item, item->equip_kind );
	}

	return FALSE;
}

/**/

bool_t	equip_item( mbr_t *mbr, item_t *item, equip_kind_t kind )
{
	bool_t	ret;

	chr_light_up( mbr, FALSE );
	ret = equip_item_sub( mbr, item, kind );
	chr_light_up( mbr, TRUE );

	return ret;
}

/**/

bool_t	equip_item_sub( mbr_t *mbr, item_t *item, equip_kind_t kind )
{
	item_t	tmp, *eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;
	if( item == NULL )
		return FALSE;

	lost_trgt( item );

	if( !smoke_tobacco( mbr, item ) )
		return FALSE;

	if( !chk_equip_two_handed_wpn( mbr, item, kind ) )
		return FALSE;

	if( (kind == EQUIP_KIND_ARW) && (item->kind == ITEM_KIND_CHEST) ){
		if( count_ls_item( item->dat.chest.contents,
				ITEM_KIND_NULL ) > 0 ){
			print_msg( FLG_NULL, MSG_READY_THROW_CHEST,
					item->name );
		}
	}

	if( chk_singly_equip( item, kind ) ){
		item_t	*tmp;
		const long	n = 1;

		tmp = alloc_item();
		if( tmp == NULL )
			return FALSE;

		copy_item( tmp, item );
		inc_item( tmp, -(tmp->n - n) );

		inc_item( item, -n );
		item = tmp;
	}

	/* 一時的なアイテムリストにぶら下げる */
	tmp.prev = &tmp;
	tmp.next = &tmp;
	ins_ls_item( &tmp, item );

	/* 脱ぐ */
	take_off_item( mbr, kind );

	eq = get_mbr_item_asgn_equip( mbr );
	if( (eq == NULL) || (eq[kind].kind != ITEM_KIND_NULL) ){
		/* 脱げなかったら */
		give_mbr_item( mbr, item, TRUE );
		return FALSE;
	}

	copy_item( &(eq[kind]), item );
	del_item( item );

	set_modifier( mbr );

	/* 統計を取る */
	update_playing_report_wearing_equip( mbr->ls_mbr_n, kind );

	return TRUE;
}

/**/

bool_t	chk_singly_equip( item_t *item, equip_kind_t kind )
{
	if( item == NULL )
		return FALSE;

	if( kind == EQUIP_KIND_ARW )
		return FALSE;

	return TRUE;
}

/**/

bool_t	chk_equip_two_handed_wpn(
	mbr_t *mbr, item_t *item, equip_kind_t kind
)
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;
	if( item == NULL )
		return FALSE;

	/* 二刀流 */

	do {
		if( kind != EQUIP_KIND_SHIELD )
			break;
		if( item->kind != ITEM_KIND_WPN )
			break;
		if( item->tab.wpn == NULL )
			break;
		if( !chk_flg( item->tab.wpn->flg, FLG_WPN_TAB_TWO_HANDED ) )
			break;

		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_EQUIP_TWO_SWORD_FENCING,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	} while( 0 );

	/* 盾 + 両手武器 */

	do {
		if( (kind != EQUIP_KIND_WIELDING)
				&& (kind != EQUIP_KIND_BOW) ){
			break;
		}
		if( item->kind != ITEM_KIND_WPN )
			break;
		if( item->tab.wpn == NULL )
			break;
		if( !chk_flg( item->tab.wpn->flg, FLG_WPN_TAB_TWO_HANDED ) )
			break;

		eq = get_mbr_item_asgn_equip( mbr );
		if( eq == NULL )
			return FALSE;
		if( eq[EQUIP_KIND_SHIELD].kind == ITEM_KIND_NULL )
			break;

		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_EQUIP_TWO_HANDED_WPN,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	} while( 0 );

	/* 両手武器 + 盾 */

	do {
		if( kind != EQUIP_KIND_SHIELD )
			break;

		eq = get_mbr_item_asgn_equip( mbr );
		if( eq == NULL )
			return FALSE;
		eq = &(eq[EQUIP_KIND_WIELDING]);
		if( eq->kind == ITEM_KIND_NULL )
			break;
		if( eq->kind != ITEM_KIND_WPN )
			break;
		if( eq->tab.wpn == NULL )
			break;
		if( !chk_flg( eq->tab.wpn->flg, FLG_WPN_TAB_TWO_HANDED ) )
			break;

		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_EQUIP_TWO_HANDED_WPN,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	} while( 0 );

	/* 両手弓 + 盾 */

	do {
		if( kind != EQUIP_KIND_SHIELD )
			break;

		eq = get_mbr_item_asgn_equip( mbr );
		if( eq == NULL )
			return FALSE;
		eq = &(eq[EQUIP_KIND_BOW]);
		if( eq->kind == ITEM_KIND_NULL )
			break;
		if( eq->kind != ITEM_KIND_WPN )
			break;
		if( eq->tab.wpn == NULL )
			break;
		if( !chk_flg( eq->tab.wpn->flg, FLG_WPN_TAB_TWO_HANDED ) )
			break;

		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_EQUIP_TWO_HANDED_WPN,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	} while( 0 );

	return TRUE;
}

/**/

bool_t	chk_bar_limit_inst( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( !is_mbr( chr ) )
		return TRUE;

	do {
		item_t	*eq;

		eq = get_mbr_item_asgn_equip( (mbr_t *)chr );
		if( eq == NULL )
			break;
		eq = &(eq[EQUIP_KIND_WIELDING]);

		if( eq->kind != ITEM_KIND_INST )
			break;
		if( !eq->dat.inst.flg_limit )
			break;

		/* 限定可 */

		return TRUE;
	} while( 0 );

	/* 限定不可 */

	return FALSE;
}

/**/

bool_t	chk_equip_kind( item_t *item, equip_kind_t kind )
{
	if( item == NULL )
		return FALSE;

	if( kind == EQUIP_KIND_ARW )
		return TRUE;
	if( kind == item->equip_kind )
		return TRUE;
	if( (kind == EQUIP_KIND_SHIELD)
			&& (item->equip_kind == EQUIP_KIND_WIELDING) ){
		return TRUE;
	}
	if( (kind == EQUIP_KIND_RIGHT_HAND)
			|| (kind == EQUIP_KIND_LEFT_HAND) ){
		if( (item->equip_kind == EQUIP_KIND_RIGHT_HAND)
				|| (item->equip_kind
				== EQUIP_KIND_LEFT_HAND) ){
			return TRUE;
		}
	}

	return FALSE;
}

/**/

bool_t	take_off_item( mbr_t *mbr, equip_kind_t kind )
{
	bool_t	ret;

	chr_light_up( mbr, FALSE );
	ret = take_off_item_sub( mbr, kind );
	chr_light_up( mbr, TRUE );

	return ret;
}

/**/

bool_t	take_off_item_sub( mbr_t *mbr, equip_kind_t kind )
{
	item_t	*eq, *tmp;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;
	if( eq[kind].kind == ITEM_KIND_NULL )
		return FALSE;

	clr_chr_trgt_act( mbr, TRUE );

	if( !chk_take_off_curse( mbr, kind ) )
		return FALSE;

	if( !chk_ins_sort_item( get_mbr_item_asgn( mbr ),
			&(eq[kind]), MBR_ITEM_MAX_N ) ){
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_ITEM_FULL, mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}

	lost_trgt( &(eq[kind]) );

	tmp = alloc_item();
	if( tmp == NULL )
		return FALSE;

	copy_item( tmp, &(eq[kind]) );

	give_mbr_item( mbr, tmp, TRUE );

	del_item( &(eq[kind]) );

	return TRUE;
}

/**/

bool_t	chk_take_off_curse( mbr_t *mbr, equip_kind_t kind )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;
	if( eq[kind].kind == ITEM_KIND_NULL )
		return FALSE;

	/* 投げる時は呪われない */
	if( kind == EQUIP_KIND_ARW )
		return TRUE;

	if( chk_flg( eq[kind].flg, FLG_ITEM_CURSED ) ){
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_ITEM_CURSE, eq[kind].name );
		curs_attrset_dflt();

		return FALSE;
	}

	return TRUE;
}

/**/

bool_t	put_item_in_chest_quick( mbr_t *mbr, item_t *item )
{
	item_t	*ls;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !chk_have_chest( mbr ) ){
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_HAVE_NOT_CHEST, mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}

	lost_trgt( item );

	ls = get_mbr_item_asgn( mbr );
	if( chk_ins_sort_item_chest( ls, item ) )
		if( ins_sort_item_chest( ls, item ) )
			return TRUE;

	curs_attrset_chr( mbr, -1, FALSE );
	print_msg( FLG_NULL, MSG_ERR_CHEST_IS_FULL, mbr->name );
	curs_attrset_dflt();

	return FALSE;
}

/**/

bool_t	break_item_fragile( item_t *item, bool_t flg_mbr )
{
	item_t	*end, *p;
	bool_t	ret;

	if( item == NULL )
		return FALSE;

	switch( item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		return FALSE;
	case ITEM_KIND_WPN:
	case ITEM_KIND_ARMOR:
		return FALSE;
	case ITEM_KIND_POTION:
		break_item( item, flg_mbr );
		return TRUE;
	case ITEM_KIND_SCROLL:
	case ITEM_KIND_STICK:
		return FALSE;
	case ITEM_KIND_INST:
		break_item( item, flg_mbr );
		return TRUE;
	case ITEM_KIND_ANTHOLOGY:
	case ITEM_KIND_ACCE:
		return FALSE;
	case ITEM_KIND_LIGHT:
		switch( item->dat.light.kind ){
		case LIGHT_KIND_NULL:
		case LIGHT_KIND_MAX_N:
			return FALSE;
		case LIGHT_KIND_TORCH:
			return FALSE;
		case LIGHT_KIND_LANTERN:
		case LIGHT_KIND_LAMP:
			break_item( item, flg_mbr );
			return TRUE;
		/* default: */
		}
	case ITEM_KIND_SPIKE:
	case ITEM_KIND_FOOD:
		return FALSE;
	case ITEM_KIND_CHEST:
		ret = FALSE;
		end = item->dat.chest.contents;
		for( p = end->next->next; p->prev != end; p = p->next )
			if( break_item_fragile( p->prev, flg_mbr ) )
				ret = TRUE;
		return ret;
	case ITEM_KIND_TOBACCO:
	case ITEM_KIND_PIPE:
	case ITEM_KIND_DISPOSAL:
	case ITEM_KIND_RARE_GOODS:
	case ITEM_KIND_BONE:
	case ITEM_KIND_COIN:
	case ITEM_KIND_JUNK:
		return FALSE;
	/* default: */
	}

	return FALSE;
}

/**/

void	break_item_contents( item_t *chest, mbr_t *mbr )
{
	item_t	*end, *p;

	if( chest == NULL )
		return;
	if( chest->kind != ITEM_KIND_CHEST )
		return;
	if( mbr == NULL )
		return;
	if( !is_mbr( mbr ) )
		return;

	end = chest->dat.chest.contents;
	if( end == NULL )
		return;

	/* 中身を壊す */
	for( p = end->next->next; p->prev != end; p = p->next )
		if( rate_randm( BREAK_ITEM_CONTENTS_RATE ) )
			break_item( p->prev, TRUE );

	if( (chest->x == MAP_DEL_X) || (chest->y == MAP_DEL_Y) ){
		drop_item( mbr->x, mbr->y, chest, chest->n );
	}

	open_item( chest, mbr );
}

/**/

bool_t	break_item( item_t *item, bool_t flg_mbr )
{
	long	x, y;
	item_t	*junk, *ls;

	if( item == NULL )
		return FALSE;
	if( item->kind == ITEM_KIND_JUNK )
		return FALSE;
	if( !chk_can_break_item( item ) )
		return FALSE;

	x = item->x;
	y = item->y;
	ls = item->prev;
	del_item( item );

	/* ガラクタを作る */

	junk = make_item_junk_rand( 1 );

	if( clip_pos( x, y ) ){
		if( !put_item( junk, x, y, PUT_ITEM_R, flg_mbr ) ){
			del_item( junk );
		}
	} else if( ls == NULL ){
		del_item( junk );
	} else {
		ins_ls_item( ls, junk );
	}

	return TRUE;
}

/**/

bool_t	chk_can_break_item( item_t *item )
{
	if( chk_randm_art( item ) )
		return FALSE;
	else
		return TRUE;
}

/**/

bool_t	open_item( item_t *item, mbr_t *mbr )
{
	if( item == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	return open_item_pos( item->x, item->y, item, mbr );
}

/**/

bool_t	open_item_pos( long x, long y, item_t *item, mbr_t *mbr )
{
	item_t	*head, *p;
	bool_t	ret;

	if( (x == MAP_DEL_X) || (y == MAP_DEL_Y) )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_CHEST )
		return FALSE;

	head = item->dat.chest.contents;
	if( head == NULL )
		return FALSE;

	ret = TRUE;
	for( p = head->next->next; p->prev != head; p = p->next )
		if( !put_item( p->prev, x, y, PUT_ITEM_R, TRUE ) )
			ret = FALSE;

	chk_trap_chest( item, mbr, _100_PERCENT );

	return ret;
}

/**/

bool_t	disarm_item( item_t *item )
{
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_CHEST )
		return FALSE;

	free_trap_chest( item );

	return TRUE;
}

/**/

void	set_item_alias( item_t *item )
{
	if( item == NULL )
		return;

	print_msg( FLG_NULL, MSG_CLR_ITEM_ALIAS );

	gets_item_alias( item->alias );
	if( item->alias[0] == ' ' )
		item->alias[0] = '\0';

	set_item_name( item );
}

/**/

void	chk_item_data( item_t *item )
{
	char	*s;

	if( item == NULL )
		return;

	print_msg( FLG_NULL, MSG_CHK_ITEM_DATA_NAME, item->name );

	s = get_item_mnr_name( item->mjr, item->mnr );
	print_msg( FLG_NULL, MSG_CHK_ITEM_DATA_KIND, s );

	switch( item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		break;
	case ITEM_KIND_WPN:
		chk_item_data_wpn( item );
		break;
	case ITEM_KIND_ARMOR:
		chk_item_data_armor( item );
		break;
	case ITEM_KIND_POTION:
	case ITEM_KIND_SCROLL:
	case ITEM_KIND_STICK:
	case ITEM_KIND_ACCE:
	case ITEM_KIND_INST:
	case ITEM_KIND_ANTHOLOGY:
	case ITEM_KIND_LIGHT:
	case ITEM_KIND_SPIKE:
	case ITEM_KIND_FOOD:
	case ITEM_KIND_CHEST:
	case ITEM_KIND_TOBACCO:
	case ITEM_KIND_PIPE:
	case ITEM_KIND_DISPOSAL:
	case ITEM_KIND_RARE_GOODS:
	case ITEM_KIND_BONE:
	case ITEM_KIND_COIN:
	case ITEM_KIND_JUNK:
		break;
	/* default: */
	}
}

/**/

void	chk_item_data_wpn( item_t *item )
{
	mbr_t	*mbr;
	bool_t	flg_monk;
	long	k;

	if( item == NULL )
		return;
	if( item->kind != ITEM_KIND_WPN )
		return;
	if( item->tab.wpn == NULL )
		return;

	if( chk_flg( item->tab.wpn->flg, FLG_WPN_TAB_TWO_HANDED ) )
		print_msg( FLG_NULL, MSG_CHK_ITEM_DATA_TWO_HANDED );
	if( chk_flg( item->tab.wpn->flg, FLG_WPN_TAB_CAN_TWO_HANDED ) )
		print_msg( FLG_NULL, MSG_CHK_ITEM_DATA_CAN_TWO_HANDED );

	flg_monk = FALSE;
	for( k = 0; k < WPN_ATTACK_MAX_N; k++ ){
		if( item->tab.wpn->attack[k].flg_monk ){
			flg_monk = TRUE;
			break;
		}
	}
	if( flg_monk )
		print_msg( FLG_NULL, MSG_CHK_ITEM_DATA_CAN_USE_MON );

	for( k = 0; k < ABL_KIND_MAX_N; k++ ){
		if( item->tab.wpn->flg_abl[k] )
			continue;
		if( ls_msg_chk_item_data[k] == N_MSG_NULL )
			continue;

		mbr = get_mbr_randm( MAP_DEL_X, MAP_DEL_Y );

		curs_attrset_chr( mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG( ls_msg_chk_item_data[k] ) );
		curs_attrset_dflt();
	}

	chk_item_data_wpn_randm_art_ls( item );
}

/**/

void	chk_item_data_wpn_randm_art_ls( item_t *item )
{
	wpn_randm_art_t	*art;
	long	i;

	if( item == NULL )
		return;
	if( item->kind != ITEM_KIND_WPN )
		return;

	art = item->dat.wpn.randm_art;

	for( i = 0; i < WPN_RANDM_ART_LS_MAX_N; i++ ){
		if( art[i].kind == WPN_RANDM_ART_KIND_NULL )
			break;
		if( art[i].mjr == WPN_RANDM_ART_MJR_NULL )
			break;
		if( art[i].mnr == WPN_RANDM_ART_MNR_NULL )
			break;

		chk_item_data_wpn_randm_art( &(art[i]) );
	}
}

/**/

void	chk_item_data_wpn_randm_art( wpn_randm_art_t *art )
{
	const char	*str;

	if( art == NULL )
		return;

	switch( art->kind ){
	case WPN_RANDM_ART_KIND_NULL:
	case WPN_RANDM_ART_KIND_MAX_N:
		break;
	case WPN_RANDM_ART_KIND_BANE:
		str = get_mnstr_mjr_name( toupper( art->mnr ) );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_WPN_RANDM_ART_BANE,
				art->mjr, art->mnr, str );
		break;
	case WPN_RANDM_ART_KIND_KILLER:
		str = get_mnstr_mjr_name( toupper( art->mnr ) );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_WPN_RANDM_ART_KILLER,
				art->mjr, art->mnr, str );
		break;
	case WPN_RANDM_ART_KIND_SLAYER:
		str = get_mnstr_mjr_name( toupper( art->mnr ) );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_WPN_RANDM_ART_SLAYER,
				art->mjr, art->mnr, str );
		break;
	case WPN_RANDM_ART_KIND_ADD_STAT:
		str = get_wpn_randm_art_add_stat_name( art->mnr );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_WPN_RANDM_ART_ADD_STAT,
				art->mjr, art->mnr, str );
		break;
	case WPN_RANDM_ART_KIND_DRAIN:
		str = get_wpn_randm_art_drain_name( art->mnr );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_WPN_RANDM_ART_DRAIN,
				art->mjr, art->mnr, str );
		break;
	}
}

/**/

const char	*get_wpn_randm_art_add_stat_name( char mnr )
{
	switch( mnr ){
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_DEAD:
		return MSG_STAT_DEAD;
	*/
	case WPN_RANDM_ART_MNR_ADD_STAT_STONE:
		return MSG_STAT_STONE;
	case WPN_RANDM_ART_MNR_ADD_STAT_PARALYZE:
		return MSG_STAT_PARALYZE;
	case WPN_RANDM_ART_MNR_ADD_STAT_POISON:
		return MSG_STAT_POISON;
	case WPN_RANDM_ART_MNR_ADD_STAT_CONFUSION:
		return MSG_STAT_CONFUSION;
	case WPN_RANDM_ART_MNR_ADD_STAT_BLIND:
		return MSG_STAT_BLIND;
	case WPN_RANDM_ART_MNR_ADD_STAT_SLEEP:
		return MSG_STAT_SLEEP;
	case WPN_RANDM_ART_MNR_ADD_STAT_SILENCE:
		return MSG_STAT_SILENCE;
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_CAUGHT:
		return MSG_STAT_CAUGHT;
	*/
	case WPN_RANDM_ART_MNR_ADD_STAT_FEAR:
		return MSG_STAT_FEAR;
	case WPN_RANDM_ART_MNR_ADD_STAT_HALLUCINATION:
		return MSG_STAT_HALLUCINATION;
	case WPN_RANDM_ART_MNR_ADD_STAT_CHARM:
		return MSG_STAT_CHARM;
	case WPN_RANDM_ART_MNR_ADD_STAT_FLY:
		return MSG_STAT_FLY;
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_HUNGRY:
		return MSG_STAT_HUNGRY;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_STARVATION:
		return MSG_STAT_STARVATION;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_FAINT:
		return MSG_STAT_FAINT;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_DRUNK:
		return MSG_STAT_DRUNK;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_VANISH:
		return MSG_STAT_VANISH;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_IRON_BODY:
		return MSG_STAT_IRON_BODY;
	*/
	case WPN_RANDM_ART_MNR_ADD_STAT_PASSWALL:
		return MSG_STAT_PASSWALL;
	case WPN_RANDM_ART_MNR_ADD_STAT_SENSE_INVISIBLE:
		return MSG_STAT_SENSE_INVISIBLE;
	}

	return "";
}

/**/

fx_kind_t	get_wpn_randm_art_add_stat_fx( char mnr )
{
	switch( mnr ){
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_DEAD:
		return FX_KIND_DEAD;
	*/
	case WPN_RANDM_ART_MNR_ADD_STAT_STONE:
		return FX_KIND_STONE;
	case WPN_RANDM_ART_MNR_ADD_STAT_PARALYZE:
		return FX_KIND_PARALYZE;
	case WPN_RANDM_ART_MNR_ADD_STAT_POISON:
		return FX_KIND_POISON;
	case WPN_RANDM_ART_MNR_ADD_STAT_CONFUSION:
		return FX_KIND_CONFUSION;
	case WPN_RANDM_ART_MNR_ADD_STAT_BLIND:
		return FX_KIND_BLIND;
	case WPN_RANDM_ART_MNR_ADD_STAT_SLEEP:
		return FX_KIND_SLEEP;
	case WPN_RANDM_ART_MNR_ADD_STAT_SILENCE:
		return FX_KIND_SILENCE;
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_CAUGHT:
		return FX_KIND_CAUGHT;
	*/
	case WPN_RANDM_ART_MNR_ADD_STAT_FEAR:
		return FX_KIND_FEAR;
	case WPN_RANDM_ART_MNR_ADD_STAT_HALLUCINATION:
		return FX_KIND_HALLUCINATION;
	case WPN_RANDM_ART_MNR_ADD_STAT_CHARM:
		return FX_KIND_CHARM;
	case WPN_RANDM_ART_MNR_ADD_STAT_FLY:
		return FX_KIND_FLY;
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_HUNGRY:
		return FX_KIND_HUNGRY;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_STARVATION:
		return FX_KIND_STARVATION;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_FAINT:
		return FX_KIND_FAINT;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_DRUNK:
		return FX_KIND_DRUNK;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_VANISH:
		return FX_KIND_VANISH;
	*/
	/*
	case WPN_RANDM_ART_MNR_ADD_STAT_IRON_BODY:
		return FX_KIND_IRON_BODY;
	*/
	case WPN_RANDM_ART_MNR_ADD_STAT_PASSWALL:
		return FX_KIND_PASSWALL;
	case WPN_RANDM_ART_MNR_ADD_STAT_SENSE_INVISIBLE:
		return FX_KIND_SENSE_INVISIBLE;
	}

	return FX_KIND_NULL;
}

/**/

const char	*get_wpn_randm_art_drain_name( char mnr )
{
	switch( mnr ){
	case WPN_RANDM_ART_MNR_DRAIN_HP:
		return MSG_WPN_RANDM_ART_MNR_DRAIN_HP;
	case WPN_RANDM_ART_MNR_DRAIN_MP:
		return MSG_WPN_RANDM_ART_MNR_DRAIN_MP;
	case WPN_RANDM_ART_MNR_DRAIN_EXP:
		return MSG_WPN_RANDM_ART_MNR_DRAIN_EXP;
	}

	return "";
}

/**/

void	chk_item_data_armor( item_t *item )
{
	long	k;

	if( item == NULL )
		return;
	if( item->kind != ITEM_KIND_ARMOR )
		return;
	if( item->tab.armor == NULL )
		return;

	for( k = 0; k < ABL_KIND_MAX_N; k++ ){
		if( !item->tab.armor->flg_abl[k] ){
			mbr_t	*mbr;

			if( ls_msg_chk_item_data[k] == N_MSG_NULL )
				continue;

			mbr = get_mbr_randm( MAP_DEL_X, MAP_DEL_Y );

			curs_attrset_chr( mbr, -1, FALSE );
			print_msg( FLG_NULL,
					MSG( ls_msg_chk_item_data[k] ) );
			curs_attrset_dflt();
		}
	}

	chk_item_data_armor_randm_art_ls( item );
}

/**/

void	chk_item_data_armor_randm_art_ls( item_t *item )
{
	armor_randm_art_t	*art;
	long	i;

	if( item == NULL )
		return;
	if( item->kind != ITEM_KIND_ARMOR )
		return;

	art = item->dat.armor.randm_art;

	for( i = 0; i < ARMOR_RANDM_ART_LS_MAX_N; i++ ){
		if( art[i].kind == ARMOR_RANDM_ART_KIND_NULL )
			break;
		if( art[i].mjr == ARMOR_RANDM_ART_MJR_NULL )
			break;
		if( art[i].mnr == ARMOR_RANDM_ART_MNR_NULL )
			break;

		chk_item_data_armor_randm_art( &(art[i]) );
	}
}

/**/

void	chk_item_data_armor_randm_art( armor_randm_art_t *art )
{
	const char	*str;

	if( art == NULL )
		return;

	switch( art->kind ){
	case ARMOR_RANDM_ART_KIND_NULL:
	case ARMOR_RANDM_ART_KIND_MAX_N:
		break;
	case ARMOR_RANDM_ART_KIND_GUARD:
		str = get_mnstr_mjr_name( toupper( art->mnr ) );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_ARMOR_RANDM_ART_GUARD,
				art->mjr, art->mnr, str );
		break;
	case ARMOR_RANDM_ART_KIND_BLOCK:
		str = get_mnstr_mjr_name( toupper( art->mnr ) );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_ARMOR_RANDM_ART_BLOCK,
				art->mjr, art->mnr, str );
		break;
	case ARMOR_RANDM_ART_KIND_PROTECT:
		str = get_mnstr_mjr_name( toupper( art->mnr ) );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_ARMOR_RANDM_ART_PROTECT,
				art->mjr, art->mnr, str );
		break;
	case ARMOR_RANDM_ART_KIND_RESI_STAT:
		str = get_armor_randm_art_resi_stat_name( art->mnr );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_ARMOR_RANDM_ART_RESI_STAT,
				art->mjr, art->mnr, str );
		break;
	case ARMOR_RANDM_ART_KIND_HEALING:
		str = get_armor_randm_art_healing_name( art->mnr );
		print_msg( FLG_NULL,
				MSG_CHK_ITEM_DATA_ARMOR_RANDM_ART_HEALING,
				art->mjr, art->mnr, str );
		break;
	}
}

/**/

const char	*get_armor_randm_art_resi_stat_name( char mnr )
{
	switch( mnr ){
	case ARMOR_RANDM_ART_MNR_RESI_STAT_DEAD:
		return MSG_STAT_DEAD;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_STONE:
		return MSG_STAT_STONE;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_PARALYZE:
		return MSG_STAT_PARALYZE;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_POISON:
		return MSG_STAT_POISON;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_CONFUSION:
		return MSG_STAT_CONFUSION;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_BLIND:
		return MSG_STAT_BLIND;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_SLEEP:
		return MSG_STAT_SLEEP;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_SILENCE:
		return MSG_STAT_SILENCE;
	/*
	case ARMOR_RANDM_ART_MNR_RESI_STAT_CAUGHT:
		return MSG_STAT_CAUGHT;
	*/
	case ARMOR_RANDM_ART_MNR_RESI_STAT_FEAR:
		return MSG_STAT_FEAR;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_HALLUCINATION:
		return MSG_STAT_HALLUCINATION;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_CHARM:
		return MSG_STAT_CHARM;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_FLY:
		return MSG_STAT_FLY;
	/*
	case ARMOR_RANDM_ART_MNR_RESI_STAT_HUNGRY:
		return MSG_STAT_HUNGRY;
	*/
	/*
	case ARMOR_RANDM_ART_MNR_RESI_STAT_STARVATION:
		return MSG_STAT_STARVATION;
	*/
	/*
	case ARMOR_RANDM_ART_MNR_RESI_STAT_FAINT:
		return MSG_STAT_FAINT;
	*/
	/*
	case ARMOR_RANDM_ART_MNR_RESI_STAT_DRUNK:
		return MSG_STAT_DRUNK;
	*/
	/*
	case ARMOR_RANDM_ART_MNR_RESI_STAT_VANISH:
		return MSG_STAT_VANISH;
	*/
	/*
	case ARMOR_RANDM_ART_MNR_RESI_STAT_IRON_BODY:
		return MSG_STAT_IRON_BODY;
	*/
	case ARMOR_RANDM_ART_MNR_RESI_STAT_PASSWALL:
		return MSG_STAT_PASSWALL;
	case ARMOR_RANDM_ART_MNR_RESI_STAT_SENSE_INVISIBLE:
		return MSG_STAT_SENSE_INVISIBLE;
	}

	return "";
}

/**/

const char	*get_armor_randm_art_healing_name( char mnr )
{
	switch( mnr ){
	case ARMOR_RANDM_ART_MNR_HEALING_HP:
		return MSG_ARMOR_RANDM_ART_MNR_HEALING_HP;
	case ARMOR_RANDM_ART_MNR_HEALING_MP:
		return MSG_ARMOR_RANDM_ART_MNR_HEALING_MP;
	case ARMOR_RANDM_ART_MNR_HEALING_EXP:
		return MSG_ARMOR_RANDM_ART_MNR_HEALING_EXP;
	}

	return "";
}

/**/

char	cv_flg_stat_to_armor_randm_art_mnr( flg_stat_t stat )
{
	if( chk_flg( stat, FLG_STAT_DEAD ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_DEAD;
	if( chk_flg( stat, FLG_STAT_STONE ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_STONE;
	if( chk_flg( stat, FLG_STAT_PARALYZE ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_PARALYZE;
	if( chk_flg( stat, FLG_STAT_POISON ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_POISON;
	if( chk_flg( stat, FLG_STAT_CONFUSION ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_CONFUSION;
	if( chk_flg( stat, FLG_STAT_BLIND ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_BLIND;
	if( chk_flg( stat, FLG_STAT_SLEEP ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_SLEEP;
	if( chk_flg( stat, FLG_STAT_SILENCE ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_SILENCE;
	if( chk_flg( stat, FLG_STAT_FEAR ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_FEAR;
	if( chk_flg( stat, FLG_STAT_HALLUCINATION ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_HALLUCINATION;
	if( chk_flg( stat, FLG_STAT_CHARM ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_CHARM;
	if( chk_flg( stat, FLG_STAT_FLY ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_FLY;
	/*
	if( chk_flg( stat, FLG_STAT_VANISH ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_VANISH;
	*/
	/*
	if( chk_flg( stat, FLG_STAT_IRON_BODY ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_IRON_BODY;
	*/
	if( chk_flg( stat, FLG_STAT_PASSWALL ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_PASSWALL;
	if( chk_flg( stat, FLG_STAT_SENSE_INVISIBLE ) )
		return ARMOR_RANDM_ART_MNR_RESI_STAT_SENSE_INVISIBLE;

	return ' ';
}

/**/

bool_t	chk_randm_art( item_t *item )
{
	if( item == NULL )
		return FALSE;

	switch( item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		break;
	case ITEM_KIND_WPN:
		if( item->dat.wpn.slayer != FACE_MJR_NULL )
			return TRUE;
		if( item->dat.wpn.randm_art[0].kind
				!= WPN_RANDM_ART_KIND_NULL ){
			return TRUE;
		}
		break;
	case ITEM_KIND_ARMOR:
		if( item->dat.armor.randm_art[0].kind
				!= ARMOR_RANDM_ART_KIND_NULL ){
			return TRUE;
		}
		break;
	case ITEM_KIND_POTION:
	case ITEM_KIND_SCROLL:
	case ITEM_KIND_STICK:
	case ITEM_KIND_ACCE:
	case ITEM_KIND_INST:
	case ITEM_KIND_ANTHOLOGY:
	case ITEM_KIND_LIGHT:
	case ITEM_KIND_SPIKE:
	case ITEM_KIND_FOOD:
	case ITEM_KIND_CHEST:
	case ITEM_KIND_TOBACCO:
	case ITEM_KIND_PIPE:
	case ITEM_KIND_DISPOSAL:
	case ITEM_KIND_RARE_GOODS:
	case ITEM_KIND_BONE:
	case ITEM_KIND_COIN:
	case ITEM_KIND_JUNK:
		break;
	/* default: */
	}

	return FALSE;
}

/**/

rate_t	calc_rate_abl_equip( mbr_t *mbr, abl_kind_t abl )
{
	item_t	*eq;
	rate_t	rate;
	long	kind;

	if( mbr == NULL )
		return 1;
	if( !is_mbr( mbr ) )
		return _100_PERCENT;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return 1;

	rate = _100_PERCENT;
	for( kind = 0; kind < EQUIP_KIND_MAX_N; kind++ ){
		if( eq[kind].kind == ITEM_KIND_NULL ){
			continue;
		} else if( eq[kind].kind == ITEM_KIND_WPN ){
			if( eq[kind].tab.wpn == NULL )
				continue;
			if( !eq[kind].tab.wpn->flg_abl[abl] )
				rate /= 2;
		} else if( eq[kind].kind == ITEM_KIND_ARMOR ){
			if( eq[kind].tab.armor == NULL )
				continue;
			if( !eq[kind].tab.armor->flg_abl[abl] )
				rate /= 2;
		}
	}

	return rate;
}

/**/

bool_t	teleport_item( item_t *item )
{
	dun_t	*dun = get_dun();
	long	i;

	if( item == NULL )
		return FALSE;

	dun->map.obj.mjr[item->y][item->x] = FACE_MJR_FLOOR;
	dun->map.obj.mnr[item->y][item->x] = FACE_MNR_FLOOR;
	draw_map( item->x, item->y, 1, 1 );

	for( i = LOOP_MAX_1000; i > 0; i-- ){
		long	nx, ny;

		nx = 1 + randm( MAP_MAX_X - 2);
		ny = 1 + randm( MAP_MAX_Y - 2);

		if( dun->map.obj.mjr[ny][nx] != FACE_MJR_FLOOR )
			continue;
		if( dun->map.obj.mnr[ny][nx] != FACE_MNR_FLOOR )
			continue;

		/* 新しい位置に移動出来たら */
		item->x = nx;
		item->y = ny;
		break;
	}

	dun->map.obj.mjr[item->y][item->x] = item->mjr;
	dun->map.obj.mnr[item->y][item->x] = item->mnr;
	draw_item( item );

	redraw_all();

	return TRUE;
}

/**/

void	detect_item( long x, long y, long r )
{
	dun_t	*dun;
	item_t	*p;

	dun = get_dun();

	p = dun_item_asgn.next;
	for( ; p != &dun_item_asgn; p = p->next ){
		if( labs( p->x - x ) > r )
			continue;
		if( labs( p->y - y ) > r )
			continue;

		p->flg |= FLG_ITEM_DETECTED;
		dun->map.obj.flg[p->y][p->x] |= FLG_MAP_OBJ_FIND;
		draw_item( p );
	}
}

/**/

bool_t	cmp_item( item_t *p1, item_t *p2 )
{
	if( p1 == NULL )
		return FALSE;
	if( p2 == NULL )
		return FALSE;
	if( p1->kind != p2->kind )
		return FALSE;
	if( p1->equip_kind != p2->equip_kind )
		return FALSE;

	if( (p1->flg & FLG_ITEM_IDENTIFIED)
			!= (p2->flg & FLG_ITEM_IDENTIFIED) )
		return FALSE;
	if( (p1->flg & FLG_ITEM_CURSED)
			!= (p2->flg & FLG_ITEM_CURSED) )
		return FALSE;


	switch( p1->kind ){
	case ITEM_KIND_MAX_N:
	case ITEM_KIND_NULL:
		break;
	case ITEM_KIND_WPN:
		if( p1->tab.wpn != p2->tab.wpn )
			return FALSE;
		if( p1->dat.wpn.kind != p2->dat.wpn.kind )
			return FALSE;
		if( p1->dat.wpn.add_hit != p2->dat.wpn.add_hit )
			return FALSE;
		if( p1->dat.wpn.add_crtcl != p2->dat.wpn.add_crtcl )
			return FALSE;
		if( p1->dat.wpn.add_dam != p2->dat.wpn.add_dam )
			return FALSE;
		if( p1->dat.wpn.slayer != p2->dat.wpn.slayer )
			return FALSE;
		if( p1->dat.wpn.flg != p2->dat.wpn.flg )
			return FALSE;
	case ITEM_KIND_ARMOR:
		if( p1->dat.armor.kind != p2->dat.armor.kind )
			return FALSE;
		if( p1->dat.armor.add_def != p2->dat.armor.add_def )
			return FALSE;
		if( p1->dat.armor.add_crtcl != p2->dat.armor.add_crtcl )
			return FALSE;
		if( p1->dat.armor.add_ac != p2->dat.armor.add_ac )
			return FALSE;
		break;
	case ITEM_KIND_POTION:
		if( p1->tab.potion != p2->tab.potion )
			return FALSE;
		if( p1->dat.potion.kind != p2->dat.potion.kind )
			return FALSE;
		break;
	case ITEM_KIND_SCROLL:
		if( p1->tab.scroll != p2->tab.scroll )
			return FALSE;
		if( p1->dat.scroll.kind != p2->dat.scroll.kind )
			return FALSE;
		break;
	case ITEM_KIND_STICK:
		if( p1->tab.stick != p2->tab.stick )
			return FALSE;
		if( p1->dat.stick.kind != p2->dat.stick.kind )
			return FALSE;
		if( p1->dat.stick.spell_kind != p2->dat.stick.spell_kind )
			return FALSE;
		if( p1->dat.stick.n != p2->dat.stick.n )
			return FALSE;
		break;
	case ITEM_KIND_ACCE:
		if( p1->tab.acce != p2->tab.acce )
			return FALSE;
		if( p1->dat.acce.kind != p2->dat.acce.kind )
			return FALSE;
		break;
	case ITEM_KIND_INST:
		if( p1->tab.inst != p2->tab.inst )
			return FALSE;
		if( p1->dat.inst.kind != p2->dat.inst.kind )
			return FALSE;
		if( p1->dat.inst.flg_limit != p2->dat.inst.flg_limit )
			return FALSE;
		if( p1->dat.inst.spell_kind != p2->dat.inst.spell_kind )
			return FALSE;
		break;
	case ITEM_KIND_ANTHOLOGY:
		if( p1->tab.anthology != p2->tab.anthology )
			return FALSE;
		if( p1->dat.anthology.kind != p2->dat.anthology.kind )
			return FALSE;
		break;
	case ITEM_KIND_LIGHT:
		if( p1->tab.light != p2->tab.light )
			return FALSE;
		if( p1->dat.light.kind != p2->dat.light.kind )
			return FALSE;
		if( p1->dat.light.turn != p2->dat.light.turn )
			return FALSE;
		if( p1->dat.light.wish_level != p2->dat.light.wish_level )
			return FALSE;
		if( p1->dat.light.wish_n != p2->dat.light.wish_n )
			return FALSE;
		if( p1->dat.light.flg_used != p2->dat.light.flg_used )
			return FALSE;
		break;
	case ITEM_KIND_SPIKE:
		break;
	case ITEM_KIND_FOOD:
		if( p1->tab.food != p2->tab.food )
			return FALSE;
		if( p1->dat.food.kind != p2->dat.food.kind )
			return FALSE;
		break;
	case ITEM_KIND_CHEST:
		return FALSE;
	case ITEM_KIND_TOBACCO:
		if( (p1->dat.tobacco.turn <= 0)
				&& (p2->dat.tobacco.turn <= 0) ){
			return TRUE;
		}
		if( p1->tab.tobacco != p2->tab.tobacco )
			return FALSE;
		if( p1->dat.tobacco.kind != p2->dat.tobacco.kind )
			return FALSE;
		if( p1->dat.tobacco.brand != p2->dat.tobacco.brand )
			return FALSE;
		if( p1->dat.tobacco.turn != p2->dat.tobacco.turn )
			return FALSE;
		break;
	case ITEM_KIND_PIPE:
		if( (p1->dat.pipe.consume_turn <= 0)
				&& (p2->dat.pipe.consume_turn <= 0) ){
			return TRUE;
		}
		if( p1->tab.pipe != p2->tab.pipe )
			return FALSE;
		if( p1->dat.pipe.kind != p2->dat.pipe.kind )
			return FALSE;
		if( p1->dat.pipe.turn != p2->dat.pipe.turn )
			return FALSE;
		if( p1->dat.pipe.consume_turn != p2->dat.pipe.consume_turn )
			return FALSE;
		break;
	case ITEM_KIND_DISPOSAL:
		if( p1->dat.disposal.n != p2->dat.disposal.n )
			return FALSE;
		if( p1->dat.disposal.max_n != p2->dat.disposal.max_n )
			return FALSE;
	case ITEM_KIND_RARE_GOODS:
		if( p1->tab.rare_goods != p2->tab.rare_goods )
			return FALSE;
		if( p1->dat.rare_goods.kind != p2->dat.rare_goods.kind )
			return FALSE;
		if( p1->dat.rare_goods.mnstr_kind
				!= p2->dat.rare_goods.mnstr_kind )
			return FALSE;
		break;
	case ITEM_KIND_BONE:
		if( p1->dat.bone.mnstr_tab != p2->dat.bone.mnstr_tab )
			return FALSE;
		if( p1->dat.bone.dun_lev != p2->dat.bone.dun_lev )
			return FALSE;
		break;
	case ITEM_KIND_COIN:
		if( p1->tab.coin != p2->tab.coin )
			return FALSE;
		if( p1->dat.coin.kind != p2->dat.coin.kind )
			return FALSE;
		break;
	case ITEM_KIND_JUNK:
		break;
	/* default: */
	}

	return TRUE;
}

/**/

long	inc_item( item_t *item, long n )
{
	if( item == NULL )
		return -1;
	if( item->kind == ITEM_KIND_NULL )
		return -1;

	item->n += n;
	set_item_name( item );

	if( item->n <= 0 ){
		del_item( item );
		return 0;
	}

	return item->n;
}

/**/

void	inc_turn_all_item( void )
{
	long	i;
	item_t	*lit;
	party_t	*pty;

	pty = get_party();
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		lit = get_mbr_item_asgn_equip( pty->mbr[i] );
		if( lit == NULL )
			continue;
		lit = &(lit[EQUIP_KIND_LIGHT_SOURCE]);
		if( lit->kind != ITEM_KIND_LIGHT )
			continue;

		chr_light_up( pty->mbr[i], FALSE );
		if( lit->dat.light.turn > 0 ){
			lit->dat.light.turn--;
			set_item_name( lit );
		}
		chr_light_up( pty->mbr[i], TRUE );
	}
}

/**/

long	count_mbr_item_n( mbr_t *mbr )
{
	long	n;
	item_t	*p, *head;

	if( mbr == NULL )
		return 0;
	if( !is_mbr( mbr ) )
		return 0;

	head = &(mbr_item_asgn[mbr->ls_mbr_n]);
	n = 0;
	for( p = head->next; p != head; p = p->next )
		n++;

	return n;
}

/**/

long	get_item_bundle( item_t *item )
{
	if( item == NULL )
		return 0;

	switch( item->kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		return 0;
	case ITEM_KIND_WPN:
		if( chk_flg( item->dat.wpn.flg, FLG_WPN_TAB_BUNDLE ) )
			return BUNDLE_WPN_MAX_N;
		else
			return 1;
	case ITEM_KIND_ARMOR:
	case ITEM_KIND_STICK:
	case ITEM_KIND_INST:
	case ITEM_KIND_ANTHOLOGY:
	case ITEM_KIND_CHEST:
	case ITEM_KIND_DISPOSAL:
	case ITEM_KIND_RARE_GOODS:
		return 1;
	case ITEM_KIND_POTION:
	case ITEM_KIND_SCROLL:
	case ITEM_KIND_ACCE:
		return BUNDLE_MAX_N;
	case ITEM_KIND_LIGHT:
		if( item->dat.light.kind == LIGHT_KIND_TORCH )
			return BUNDLE_MAX_N;
		else
			return 1;
	case ITEM_KIND_SPIKE:
		return BUNDLE_SPIKE_MAX_N;
	case ITEM_KIND_FOOD:
	case ITEM_KIND_TOBACCO:
	case ITEM_KIND_PIPE:
	case ITEM_KIND_BONE:
	case ITEM_KIND_COIN:
	case ITEM_KIND_JUNK:
		return BUNDLE_MAX_N;
	/* default: */
	}

	return 0;
}

/**/

bool_t	chk_range_chr_bash( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( is_mbr( chr ) )
		return chk_range_mbr_bash( chr );
	else if( chr->kind == CHR_KIND_MNSTR )
		return chk_range_mnstr_bash( chr );

	return FALSE;
}

/**/

bool_t	chk_range_mbr_bash( chr_t *chr )
{
	item_t	*eq;

	if( chr == NULL )
		return FALSE;
	if( !is_mbr( chr ) )
		return FALSE;
	if( chr->trgt.kind == TRGT_KIND_NULL )
		return FALSE;

	eq = get_mbr_item_asgn_equip( chr );
	if( eq == NULL )
		return FALSE;
	eq = &(eq[EQUIP_KIND_WIELDING]);

	if( (eq->kind == ITEM_KIND_WPN) && (eq->tab.wpn != NULL) ){
		attack_t	*ls;
		long	i;

		ls = eq->tab.wpn->attack;
		for( i = 0; i < LOOP_MAX_1000; i++ ){
			if( ls[i].kind == ATTACK_KIND_NULL )
				break;

			if( chk_range_attack_sub( chr, ls[i].range_bash ) )
				return TRUE;
		}
	} else {
		if( chk_range_attack_sub( chr, 1 ) )
			return TRUE;
	}

	if( chk_xx_range() )
		return TRUE;

	return FALSE;
}

/**/

bool_t	chk_range_mnstr_bash( chr_t *chr )
{
	attack_t	*ls;
	long	i;

	if( chr == NULL )
		return FALSE;
	if( chr->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( chr->trgt.kind == TRGT_KIND_NULL )
		return FALSE;

	ls = chr->mnstr_tab->attack;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].kind == ATTACK_KIND_NULL )
			break;

		if( ls[i].flg_throw )
			continue;

		if( chk_range_attack_sub( chr, ls[i].range_bash ) )
			return TRUE;
	}

	if( chk_xx_range() )
		return TRUE;

	return FALSE;
}

/**/

bool_t	chk_range_chr_throw( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( is_mbr( chr ) )
		return chk_range_mbr_throw( chr );
	else if( chr->kind == CHR_KIND_MNSTR )
		return chk_range_mnstr_throw( chr );

	return FALSE;
}

/**/

bool_t	chk_range_mbr_throw( chr_t *chr )
{
	item_t	*eq;
	long	i, max_i;
	wpn_tab_t	*bow_tab, *arw_tab;
	bool_t	flg_arw;

	if( chr == NULL )
		return FALSE;
	if( !is_mbr( chr ) )
		return FALSE;
	if( chr->trgt.kind == TRGT_KIND_NULL )
		return FALSE;

	eq = get_mbr_item_asgn_equip( chr );
	if( eq == NULL )
		return FALSE;

	/* 魔法の杖 */

	if( eq[EQUIP_KIND_BOW].kind == ITEM_KIND_STICK ){
		if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_NULL ){
			if( chk_range_attack_sub( chr, STICK_RANGE_R ) )
				return TRUE;
		}
	}

	if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_NULL ){
		curs_attrset_chr( chr, -1, FALSE );
		print_msg( FLG_MSG_ERR, MSG_ERR_THROW, chr->name );
		curs_attrset_dflt();

		return FALSE;
	}

	/* 飛び道具 */

	if( eq[EQUIP_KIND_BOW].kind == ITEM_KIND_WPN )
		bow_tab = eq[EQUIP_KIND_BOW].tab.wpn;
	else
		bow_tab = NULL;
	if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_WPN )
		arw_tab = eq[EQUIP_KIND_ARW].tab.wpn;
	else
		arw_tab = NULL;

	flg_arw = FALSE;
	if( chk_dagger( arw_tab ) )
		flg_arw = TRUE;
	if( chk_bow( arw_tab, bow_tab ) )
		flg_arw = TRUE;

	if( flg_arw && (arw_tab != NULL) ){
		attack_t	*ls;

		ls = arw_tab->attack;
		for( i = 0; i < LOOP_MAX_1000; i++ ){
			if( ls[i].kind == ATTACK_KIND_NULL )
				break;

			if( chk_range_attack_sub( chr, ls[i].range_throw ) )
				return TRUE;
		}
	}

	/* その他のアイテム */

	max_i = sizeof( range_tab ) / sizeof( range_tab_t );
	for( i = 0; i < max_i; i++ ){
		if( range_tab[i].kind == eq[EQUIP_KIND_ARW].kind ){
			if( range_tab[i].r < 1 )
				range_tab[i].r = 1;
			if( chk_range_attack_sub( chr, range_tab[i].r ) )
				return TRUE;
		}
	}

	/* エラー */

	curs_attrset_chr( chr, -1, FALSE );
	print_msg_mbr( chr, FLG_MSG_ERR, MSG_ERR_THROW_RANGE, chr->name );
	curs_attrset_dflt();

	return FALSE;
}

/**/

bool_t	chk_range_mnstr_throw( chr_t *chr )
{
	attack_t	*ls;
	long	i;

	if( chr == NULL )
		return FALSE;
	if( chr->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( chr->trgt.kind == TRGT_KIND_NULL )
		return FALSE;

	ls = chr->mnstr_tab->attack;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].kind == ATTACK_KIND_NULL )
			break;

		if( !ls[i].flg_throw )
			continue;

		if( chk_range_attack_sub( chr, ls[i].range_throw ) )
			return TRUE;
	}

	return FALSE;
}

/**/

bool_t	chk_range_attack_sub( chr_t *chr, long r )
{
	long	dr;

	if( chr == NULL )
		return FALSE;

	dr = get_trgt_range( chr );

	if( r >= dr )
		return TRUE;
	else
		return FALSE;
}

/**/

bool_t	drop_arw( long x, long y, item_t *item )
{
	item_t	*tmp;
	const long	n = 1;

	if( item == NULL )
		return FALSE;
	if( item->kind == ITEM_KIND_NULL )
		return FALSE;

	tmp = alloc_item();
	if( tmp == NULL )
		return FALSE;

	copy_item( tmp, item );
	inc_item( tmp, -(tmp->n - n) );
	inc_item( item, -n );

	break_item_fragile( tmp, TRUE );

	if( !put_item( tmp, x, y, PUT_ITEM_R, TRUE ) ){
		del_item( tmp );
		return FALSE;
	}

	return TRUE;
}

/**/

void	dec_throw( mbr_t *mbr, bool_t flg_drop, long x, long y )
{
	item_t	*eq;

	if( mbr == NULL )
		return;
	if( !is_mbr( mbr ) )
		return;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return;
	eq = &(eq[EQUIP_KIND_ARW]);
	if( eq->kind == ITEM_KIND_NULL )
		return;

	if( flg_drop )
		drop_arw( x, y, eq );
	else
		inc_item( eq, -1 );

	if( eq->kind == ITEM_KIND_NULL ){
		if( !reload_arw( mbr ) ){
			curs_attrset_chr( mbr, -1, FALSE );
			print_msg( FLG_NULL, MSG_ERR_THROW, mbr->name );
			curs_attrset_dflt();

			clr_chr_trgt_act( mbr, TRUE );
		}
	}
}

/**/

bool_t	chk_come_back_arw( mbr_t *mbr )
{
	item_t	*eq, *tmp;
	const long	n = 1;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;
	if( eq[EQUIP_KIND_ARW].kind != ITEM_KIND_WPN )
		return FALSE;
	if( !chk_flg( eq[EQUIP_KIND_ARW].dat.wpn.flg, FLG_WPN_TAB_RET ) )
		return FALSE;

	tmp = alloc_item();
	if( tmp == NULL )
		return FALSE;

	copy_item( tmp, &(eq[EQUIP_KIND_ARW]) );
	inc_item( tmp, -(tmp->n - n) );
	inc_item( &(eq[EQUIP_KIND_ARW]), -n );

	give_mbr_item( mbr, tmp, TRUE );

	return TRUE;
}

/**/

bool_t	reload_arw( mbr_t *mbr )
{
	item_t	*p, *end, *eq, *bow;
	bow_kind_t	bow_kind;

	if( !chk_flg( mbr->flg_chr, FLG_CHR_AUTO_RELOAD ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;

	bow = &(eq[EQUIP_KIND_BOW]);
	bow_kind = BOW_KIND_DAGGER;
	if( (bow->kind == ITEM_KIND_WPN) && (bow->tab.wpn != NULL) )
		bow_kind = bow->tab.wpn->bow_kind;

	end = get_mbr_item_asgn( mbr );
	if( end == NULL )
		return FALSE;
	for( p = end->next; p != end; p = p->next ){
		if( p->kind != ITEM_KIND_WPN )
			continue;
		if( !chk_flg( p->dat.wpn.flg, FLG_WPN_TAB_ARW ) )
			continue;
		if( p->tab.wpn == NULL )
			continue;
		if( p->tab.wpn->bow_kind != bow_kind )
			continue;

		if( equip_item( mbr, p, EQUIP_KIND_ARW ) ){
			print_msg( FLG_NULL, MSG_AUTO_RELOAD,
					mbr->name, p->name );
			return TRUE;
		} else {
			return FALSE;
		}
	}

	return FALSE;
}

/**/

char	get_item_mjr( item_t *item )
{
	if( item == NULL ){
		if( g_flg_debug ){
			return FACE_MJR_ERR;
		} else {
			return FACE_MJR_NULL;
		}
	}

	return item->mjr;
}

/**/

char	get_item_mnr( item_t *item )
{
	if( item == NULL ){
		if( g_flg_debug ){
			return FACE_MNR_ERR;
		} else {
			return FACE_MNR_NULL;
		}
	}

	return item->mnr;
}

/**/

wpn_tab_t	*get_wpn_tab( wpn_kind_t kind )
{
	long	n;

	for( n = 0; n < wpn_tab_max_n; n++ ){
		if( wpn_tab[n].kind == kind )
			return &wpn_tab[n];
	}
	return NULL;
}

/**/

wpn_tab_t	*get_wpn_tab_head( void )
{
	return wpn_tab;
}

/**/

armor_tab_t	*get_armor_tab( armor_kind_t kind )
{
	long	n;

	for( n = 0; n < armor_tab_max_n; n++ ){
		if( armor_tab[n].kind == kind )
			return &armor_tab[n];
	}
	return NULL;
}

/**/

armor_tab_t	*get_armor_tab_head( void )
{
	return armor_tab;
}

/**/

potion_tab_t	*get_potion_tab( potion_kind_t kind )
{
	long	n;

	for( n = 0; n < potion_tab_max_n; n++ ){
		if( potion_tab[n].kind == kind )
			return &potion_tab[n];
	}
	return NULL;
}

/**/

potion_tab_t	*get_potion_tab_head( void )
{
	return potion_tab;
}

/**/

scroll_tab_t	*get_scroll_tab( scroll_kind_t kind )
{
	long	n;

	for( n = 0; n < scroll_tab_max_n; n++ ){
		if( scroll_tab[n].kind == kind )
			return &scroll_tab[n];
	}
	return NULL;
}

/**/

scroll_tab_t	*get_scroll_tab_head( void )
{
	return scroll_tab;
}

/**/

stick_tab_t	*get_stick_tab( stick_kind_t kind, spell_kind_t spell )
{
	long	n;

	for( n = 0; n < stick_tab_max_n; n++ ){
		if( stick_tab[n].kind != kind )
			continue;
		if( stick_tab[n].spell_kind != spell )
			continue;

		return &stick_tab[n];
	}
	return NULL;
}

/**/

stick_tab_t	*get_stick_tab_head( void )
{
	return stick_tab;
}

/**/

acce_tab_t	*get_acce_tab(
	ring_kind_t ring_kind,
	amulet_kind_t amulet_kind,
	necklace_kind_t necklace_kind
)
{
	long	n;

	for( n = 0; n < acce_tab_max_n; n++ ){
		if( acce_tab[n].ring_kind != ring_kind )
			continue;
		if( acce_tab[n].amulet_kind != amulet_kind )
			continue;
		if( acce_tab[n].necklace_kind != necklace_kind )
			continue;

		return &acce_tab[n];
	}
	return NULL;
}

/**/

acce_tab_t	*get_acce_tab_head( void )
{
	return acce_tab;
}

/**/

inst_tab_t	*get_inst_tab( inst_kind_t kind )
{
	long	n;

	for( n = 0; n < inst_tab_max_n; n++ ){
		if( inst_tab[n].kind != kind )
			continue;

		return &inst_tab[n];
	}
	return NULL;
}

/**/

inst_tab_t	*get_inst_tab_head( void )
{
	return inst_tab;
}

/**/

anthology_tab_t	*get_anthology_tab( anthology_kind_t kind )
{
	long	n;

	for( n = 0; n < anthology_tab_max_n; n++ ){
		if( anthology_tab[n].kind != kind )
			continue;

		return &anthology_tab[n];
	}
	return NULL;
}

/**/

anthology_tab_t	*get_anthology_tab_head( void )
{
	return anthology_tab;
}

/**/

light_tab_t	*get_light_tab(
	light_kind_t kind,
	wish_level_t wish_level
)
{
	long	n;

	for( n = 0; n < light_tab_max_n; n++ ){
		if( light_tab[n].kind != kind )
			continue;
		if( light_tab[n].wish_level != wish_level )
			continue;

		return &light_tab[n];
	}
	return NULL;
}

/**/

light_tab_t	*get_light_tab_head( void )
{
	return light_tab;
}

/**/

food_tab_t	*get_food_tab( food_kind_t kind )
{
	long	n;

	for( n = 0; n < food_tab_max_n; n++ ){
		if( food_tab[n].kind == kind )
			return &food_tab[n];
	}
	return NULL;
}

/**/

food_tab_t	*get_food_tab_head( void )
{
	return food_tab;
}

/**/

tobacco_tab_t	*get_tobacco_tab( tobacco_kind_t kind, tobacco_brand_t brand )
{
	long	n;

	for( n = 0; n < tobacco_tab_max_n; n++ ){
		if( tobacco_tab[n].kind != kind )
			continue;
		if( tobacco_tab[n].brand != brand )
			continue;

			return &tobacco_tab[n];
	}
	return NULL;
}

/**/

tobacco_tab_t	*get_tobacco_tab_head( void )
{
	return tobacco_tab;
}

/**/

pipe_tab_t	*get_pipe_tab( pipe_kind_t kind )
{
	long	n;

	for( n = 0; n < pipe_tab_max_n; n++ ){
		if( pipe_tab[n].kind == kind )
			return &pipe_tab[n];
	}
	return NULL;
}

/**/

pipe_tab_t	*get_pipe_tab_head( void )
{
	return pipe_tab;
}

/**/

rare_goods_kind_t	get_rare_goods_randm()
{
	long	i;
	long	n;

	for( i = LOOP_MAX_100; i > 0; i-- ){
		n = randm( rare_goods_tab_max_n );
		if( rare_goods_tab[n].name == NULL )
			continue;
		if( rare_goods_tab[n].kind == RARE_GOODS_KIND_NULL )
			continue;

		return( rare_goods_tab[n].kind );
	}

	return RARE_GOODS_KIND_NULL;
}

/**/

rare_goods_tab_t	*get_rare_goods_tab( rare_goods_kind_t kind )
{
	long	n;

	for( n = 0; n < rare_goods_tab_max_n; n++ ){
		if( rare_goods_tab[n].kind == kind )
			return &rare_goods_tab[n];
	}
	return NULL;
}

/**/

rare_goods_tab_t	*get_rare_goods_tab_head( void )
{
	return rare_goods_tab;
}

/**/

coin_tab_t	*get_coin_tab( coin_kind_t kind )
{
	long	n;

	for( n = 0; n < coin_tab_max_n; n++ ){
		if( coin_tab[n].kind == kind )
			return &coin_tab[n];
	}
	return NULL;
}

/**/

coin_tab_t	*get_coin_tab_head( void )
{
	return coin_tab;
}

/**/

long	get_wpn_tab_n( wpn_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < wpn_tab )
		return -1;
	if( p >= wpn_tab + wpn_tab_max_n )
		return -1;

	return( p - wpn_tab );
}

/**/

long	get_armor_tab_n( armor_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < armor_tab )
		return -1;
	if( p >= armor_tab + armor_tab_max_n )
		return -1;

	return( p - armor_tab );
}

/**/

long	get_potion_tab_n( potion_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < potion_tab )
		return -1;
	if( p >= potion_tab + potion_tab_max_n )
		return -1;

	return( p - potion_tab );
}

/**/

long	get_scroll_tab_n( scroll_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < scroll_tab )
		return -1;
	if( p >= scroll_tab + scroll_tab_max_n )
		return -1;

	return( p - scroll_tab );
}

/**/

long	get_stick_tab_n( stick_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < stick_tab )
		return -1;
	if( p >= stick_tab + stick_tab_max_n )
		return -1;

	return( p - stick_tab );
}

/**/

long	get_acce_tab_n( acce_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < acce_tab )
		return -1;
	if( p >= acce_tab + acce_tab_max_n )
		return -1;

	return( p - acce_tab );
}

/**/

long	get_inst_tab_n( inst_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < inst_tab )
		return -1;
	if( p >= inst_tab + inst_tab_max_n )
		return -1;

	return( p - inst_tab );
}

/**/

long	get_anthology_tab_n( anthology_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < anthology_tab )
		return -1;
	if( p >= anthology_tab + anthology_tab_max_n )
		return -1;

	return( p - anthology_tab );
}

/**/

long	get_light_tab_n( light_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < light_tab )
		return -1;
	if( p >= light_tab + light_tab_max_n )
		return -1;

	return( p - light_tab );
}

/**/

long	get_food_tab_n( food_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < food_tab )
		return -1;
	if( p >= food_tab + food_tab_max_n )
		return -1;

	return( p - food_tab );
}

/**/

long	get_tobacco_tab_n( tobacco_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < tobacco_tab )
		return -1;
	if( p >= tobacco_tab + tobacco_tab_max_n )
		return -1;

	return( p - tobacco_tab );
}

/**/

long	get_pipe_tab_n( pipe_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < pipe_tab )
		return -1;
	if( p >= pipe_tab + pipe_tab_max_n )
		return -1;

	return( p - pipe_tab );
}

/**/

long	get_rare_goods_tab_n( rare_goods_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < rare_goods_tab )
		return -1;
	if( p >= rare_goods_tab + rare_goods_tab_max_n )
		return -1;

	return( p - rare_goods_tab );
}

/**/

long	get_coin_tab_n( coin_tab_t *p )
{
	if( p == NULL )
		return -1;
	if( p < coin_tab )
		return -1;
	if( p >= coin_tab + coin_tab_max_n )
		return -1;

	return( p - coin_tab );
}

/**/

item_t	*get_item( long x, long y )
{
	item_t	*p;

	p = dun_item_asgn.next;
	for( ; p != &dun_item_asgn; p = p->next ){
		if( (p->x == x) && (p->y == y) )
			return p;
	}

	return NULL;
}

/**/

void	copy_item( item_t *dst, item_t *src )
{
	item_t	*next, *prev;

	if( src == NULL )
		return;
	if( dst == NULL )
		return;

	prev = dst->prev;
	next = dst->next;

	*dst = *src;

	dst->prev = prev;
	dst->next = next;

	if( src->kind == ITEM_KIND_CHEST )
		inc_chest_ref( src );
}

/**/

void	del_item( item_t *p )
{
	if( p == NULL )
		return;

	lost_trgt( p );

	if( clip_pos( p->x, p->y ) ){
		dun_t	*dun;

		dun = get_dun();
		dun->map.obj.mjr[p->y][p->x] = FACE_MJR_FLOOR;
		dun->map.obj.mnr[p->y][p->x] = FACE_MNR_FLOOR;
	}

	if( p->kind == ITEM_KIND_CHEST )
		dec_chest_ref( p );
	else
		free_item( p );
}

/**/

void	inc_chest_ref( item_t *chest )
{
	item_t	*head;

	if( chest == NULL )
		return;
	if( chest->kind != ITEM_KIND_CHEST )
		return;

	head = chest->dat.chest.contents;
	if( head == NULL )
		return;

	head->dat.chest.ref++;
}

/**/

void	dec_chest_ref( item_t *chest )
{
	item_t	*head;
	item_t	*end, *p;

	if( chest == NULL )
		return;
	if( chest->kind != ITEM_KIND_CHEST )
		return;

	free_trap_chest( chest );

	head = chest->dat.chest.contents;
	if( head == NULL )
		return;

	head->dat.chest.ref--;

	if( head->dat.chest.ref == 0 ){
		end = head;
		for( p = end->next->next; p->prev != end; p = p->next )
			del_item( p->prev );
		free_item( end );
	}

	if( chk_item_is_equip( chest ) )
		chest->kind = ITEM_KIND_NULL;
	else
		free_item( chest );
}

/**/

void	remove_mbr_del_item( long ls_mbr_n )
{
	mbr_t	**ls_mbr;
	item_t	*head, *p, *item;
	long	i, j;

	/* アイテムを削除 */

	ls_mbr = get_ls_mbr();
	head = get_mbr_item_asgn( ls_mbr[ls_mbr_n] );
	if( head != NULL ){
		p = head->next->next;
		for( i = 0; i < MBR_ITEM_MAX_N; i++, p = p->next ){
			if( p == NULL )
				break;

			item = p->prev;

			if( item == head )
				break;

			del_item( item );
		}
	}

	/* 装備を削除 */

	i = ls_mbr_n;
	for( j = 0; j < EQUIP_KIND_MAX_N; j++ )
		del_item( &(mbr_item_asgn_equip[i][j]) );

	/* アイテムのリストをずらす */

	for( i = ls_mbr_n; i < LS_MBR_MAX_N - 1; i++ )
		move_ls_item( &(mbr_item_asgn[i]), &(mbr_item_asgn[i + 1]) );

	mbr_item_asgn[i].prev = &(mbr_item_asgn[i]);
	mbr_item_asgn[i].next = &(mbr_item_asgn[i]);

	/* 装備のリストをずらす */

	for( i = ls_mbr_n; i < LS_MBR_MAX_N - 1; i++ ){
		for( j = 0; j < EQUIP_KIND_MAX_N; j++ ){
			mbr_item_asgn_equip[i][j]
					= mbr_item_asgn_equip[i + 1][j];
		}
	}

	for( j = 0; j < EQUIP_KIND_MAX_N; j++ )
		del_item( &(mbr_item_asgn_equip[i][j]) );
}

/**/

void	move_ls_item( item_t *dst, item_t *src )
{

	if( (src == NULL) || (dst == NULL) )
		return;

	if( src->next == src ){
		src->prev = src;

		*dst = *src;

		dst->prev = dst;
		dst->next = dst;
	} else {
		src->prev->next = dst;
		src->next->prev = dst;

		*dst = *src;

		dst->prev = src->prev;
		dst->next = src->next;
	}
}

/**/

item_t	*alloc_item( void )
{
	item_t	*p, dmy;

	p = get_item_free_next();
	if( p == NULL )
		return NULL;

	p->kind = ITEM_KIND_NULL;
	p->x = MAP_DEL_X;
	p->y = MAP_DEL_Y;

	reset_modifier( &(p->modifier) );

	/* 一時的なアイテムリストにぶら下げる */

	dmy.prev = &dmy;
	dmy.next = &dmy;

	ins_ls_item( &dmy, p );

	p->prev = NULL;
	p->next = NULL;

	return p;
}

/**/

void	free_item_ls( item_t *ls )
{
	item_t	*p, *next;

	if( ls == NULL )
		return;

	for( p = ls->next; p != ls; p = next ){
		next = p->next;
		free_item( p );
	}
}

/**/

void	free_item( item_t *p )
{
	item_t	*ls;

	if( chk_item_is_equip( p ) ){
		p->kind = ITEM_KIND_NULL;
		return;
	}

	ls = get_item_free_next();
	if( ls == NULL )
		return;

	ins_ls_item( ls, p );
}

/**/

void	ins_ls_item( item_t *ls, item_t *p )
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

/**/

bool_t	ins_sort_item( item_t *ls, item_t *item )
{
	long	bundle_n;
	item_t	*p;

	if( ls == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind <= ITEM_KIND_NULL )
		return FALSE;
	if( item->kind >= ITEM_KIND_MAX_N )
		return FALSE;

	lost_trgt( item );

	bundle_n = get_item_bundle( item );

	for( p = ls->next; p != ls; p = p->next ){
		if( p == NULL )
			break;
		if( p == item )
			continue;

		if( cmp_item( p, item ) ){
			if( (p->n + item->n) <= bundle_n ){
				inc_item( p, item->n );
				del_item( item );
				return TRUE;
			}
		}

		if( p->kind > item->kind ){
			ins_ls_item( p, item );
			return TRUE;
		}
	}

	ins_ls_item( ls, item );
	return TRUE;
}

/**/

bool_t	chk_ins_sort_item( item_t *ls, item_t *item, long max_n )
{
	item_t	*p;
	long	bundle_n;
	long	i;

	if( ls == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind <= ITEM_KIND_NULL )
		return FALSE;
	if( item->kind >= ITEM_KIND_MAX_N )
		return FALSE;

	bundle_n = get_item_bundle( item );

	for( i = 0, p = ls->next; p != ls; i++, p = p->next ){
		if( p == NULL )
			break;
		if( p == item )
			continue;

		if( cmp_item( p, item ) )
			if( (p->n + item->n) <= bundle_n )
				return TRUE;
	}

	if( i < max_n )
		return TRUE;

	return FALSE;
}

/**/

bool_t	chk_have_chest( mbr_t *mbr )
{
	item_t	*ls, *p;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	ls = get_mbr_item_asgn( mbr );
	if( ls == NULL )
		return FALSE;

	for( p = ls->next; p != ls; p = p->next ){
		if( p == NULL )
			break;

		if( p->kind == ITEM_KIND_CHEST )
			return TRUE;
	}

	return FALSE;
}

/**/

bool_t	ins_sort_item_chest( item_t *ls, item_t *item )
{
	item_t	*p, *head, *chest;
	long	bundle_n;

	if( ls == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind == ITEM_KIND_CHEST )
		return FALSE;
	if( item->kind <= ITEM_KIND_NULL )
		return FALSE;
	if( item->kind >= ITEM_KIND_MAX_N )
		return FALSE;

	lost_trgt( item );

	bundle_n = get_item_bundle( item );

	for( chest = ls->next; chest != ls; chest = chest->next ){
		if( chest == NULL )
			break;
		if( chest == item )
			continue;
		if( chest->kind != ITEM_KIND_CHEST )
			continue;
		if( chest->dat.chest.trap != NULL )
			continue;

		head = chest->dat.chest.contents;
		if( head == NULL )
			continue;

		for( p = head->next; p != head; p = p->next ){
			if( p == NULL )
				break;
			if( p == item )
				continue;

			if( cmp_item( p, item ) ){
				if( (p->n + item->n) <= bundle_n ){
					inc_item( p, item->n );
					del_item( item );
					return TRUE;
				}
			}

			if( p->kind > item->kind ){
				ins_ls_item( p, item );
				return TRUE;
			}
		}

		ins_ls_item( p, item );
		return TRUE;
	}

	return FALSE;
}

/**/

bool_t	chk_ins_sort_item_chest( item_t *ls, item_t *item )
{
	item_t	*p, *head, *chest;
	long	bundle_n;
	long	i;

	if( ls == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind == ITEM_KIND_CHEST )
		return FALSE;
	if( item->kind <= ITEM_KIND_NULL )
		return FALSE;
	if( item->kind >= ITEM_KIND_MAX_N )
		return FALSE;

	bundle_n = get_item_bundle( item );

	for( chest = ls->next; chest != ls; chest = chest->next ){
		if( chest == NULL )
			break;
		if( chest == item )
			continue;
		if( chest->kind != ITEM_KIND_CHEST )
			continue;
		if( chest->dat.chest.trap != NULL )
			continue;

		head = chest->dat.chest.contents;
		if( head == NULL )
			continue;

		for( p = head->next, i = 0; p != head; p = p->next, i++ ){
			if( p == NULL )
				break;
			if( p == item )
				continue;

			if( cmp_item( p, item ) )
				if( (p->n + item->n) <= bundle_n )
					return TRUE;
		}

		if( i < CHEST_HOLD_MAX_N )
			return TRUE;
	}

	return FALSE;
}

/**/

bool_t	chk_give_mbr_chest( mbr_t *mbr, item_t *item )
{
	long	n;

	if( mbr == NULL )
		return TRUE;
	if( !is_mbr( mbr ) )
		return FALSE;
	if( item == NULL )
		return TRUE;
	if( item->kind != ITEM_KIND_CHEST )
		return TRUE;

	n = count_ls_item( get_mbr_item_asgn( mbr ), ITEM_KIND_CHEST );

	return( n < CAN_CARRY_CHEST_MAX_N );
}

/**/

bool_t	chk_item_is_equip( item_t *p )
{
	long	n;
	mbr_t	**ls_mbr;
	item_t	*eq;

	if( p == NULL )
		return FALSE;

	ls_mbr = get_ls_mbr();
	for( n = 0; n < LS_MBR_MAX_N; n++ ){
		eq = get_mbr_item_asgn_equip( ls_mbr[n] );
		if( eq == NULL )
			continue;

		if( (eq <= p) && (p < eq + EQUIP_KIND_MAX_N) ){
			return TRUE;
		}
	}

	return FALSE;
}

/**/

bool_t	chk_dagger( const wpn_tab_t *arw_tab )
{
	if( arw_tab == NULL )
		return FALSE;
	if( arw_tab->bow_kind != BOW_KIND_DAGGER )
		return FALSE;
	if( !chk_flg( arw_tab->flg, FLG_WPN_TAB_ARW ) )
		return FALSE;

	return TRUE;
}

/**/

bool_t	chk_bow( const wpn_tab_t *arw_tab, const wpn_tab_t *bow_tab )
{
	if( arw_tab == NULL )
		return FALSE;
	if( bow_tab == NULL )
		return FALSE;
	if( arw_tab->bow_kind != bow_tab->bow_kind )
		return FALSE;
	if( !chk_flg( bow_tab->flg, FLG_WPN_TAB_BOW ) )
		return FALSE;
	if( !chk_flg( arw_tab->flg, FLG_WPN_TAB_ARW ) )
		return FALSE;

	return TRUE;
}

/**/

long	count_ls_item( item_t *ls, item_kind_t kind )
{
	item_t	*p;
	long	n;

	if( ls == NULL )
		return 0;

	n = 0;
	for( p = ls->next; p != ls; p = p->next ){
		/* アイテムの種類が指定されていて */
		/* かつ、一致しないか? */
		if( kind != ITEM_KIND_NULL )
			if( p->kind != kind )
				continue;
		n++;
	}

	return n;
}

/**/

void	arrange_item_1( long n, long d )
{
	item_t	tmp_item;

	if( mbr_item_asgn[n + d].next != &(mbr_item_asgn[n + d]) )
		mbr_item_asgn[n + d].next->prev = &(mbr_item_asgn[n]);
	if( mbr_item_asgn[n + d].prev != &(mbr_item_asgn[n + d]) )
		mbr_item_asgn[n + d].prev->next = &(mbr_item_asgn[n]);

	if( mbr_item_asgn[n].next != &(mbr_item_asgn[n]) )
		mbr_item_asgn[n].next->prev = &(mbr_item_asgn[n + d]);
	if( mbr_item_asgn[n].prev != &(mbr_item_asgn[n]) )
		mbr_item_asgn[n].prev->next = &(mbr_item_asgn[n + d]);

	/**/

	if( mbr_item_asgn[n].next == &(mbr_item_asgn[n]) ){
		tmp_item.next = &(tmp_item);
		tmp_item.prev = &(tmp_item);
	} else {
		tmp_item = mbr_item_asgn[n];
	}

	if( mbr_item_asgn[n + d].next == &(mbr_item_asgn[n + d]) ){
		mbr_item_asgn[n].next = &(mbr_item_asgn[n]);
		mbr_item_asgn[n].prev = &(mbr_item_asgn[n]);
	} else {
		mbr_item_asgn[n] = mbr_item_asgn[n + d];
	}

	if( tmp_item.next == &(tmp_item) ){
		mbr_item_asgn[n + d].next = &(mbr_item_asgn[n + d]);
		mbr_item_asgn[n + d].prev = &(mbr_item_asgn[n + d]);
	} else {
		mbr_item_asgn[n + d] = tmp_item;
	}
}

/**/

void	arrange_item( long n, long d )
{
	item_t	tmp_item;
	long	i;

	if( mbr_item_asgn[n].next == &(mbr_item_asgn[n]) ){
		tmp_item.next = &(tmp_item);
		tmp_item.prev = &(tmp_item);
	} else {
		tmp_item = mbr_item_asgn[n];
	}

	if( d <= -1 ){
		for( i = n - 1; i >= 0; i-- ){
			if( mbr_item_asgn[i].next
					!= &(mbr_item_asgn[i]) ){
				mbr_item_asgn[i].next->prev
						= &(mbr_item_asgn[i + 1]);
			}
			if( mbr_item_asgn[i].prev
					!= &(mbr_item_asgn[i]) ){
				mbr_item_asgn[i].prev->next
						= &(mbr_item_asgn[i + 1]);
			}
		}

		if( mbr_item_asgn[n].next
				!= &(mbr_item_asgn[n]) ){
			mbr_item_asgn[n].next->prev
					= &(mbr_item_asgn[0]);
		}
		if( mbr_item_asgn[n].prev
				!= &(mbr_item_asgn[n]) ){
			mbr_item_asgn[n].prev->next
					= &(mbr_item_asgn[0]);
		}

		/**/

		for( i = n - 1; i >= 0; i-- ){
			if( mbr_item_asgn[i].next
					== &(mbr_item_asgn[i]) ){
				mbr_item_asgn[i + 1].next
						= &(mbr_item_asgn[i + 1]);
				mbr_item_asgn[i + 1].prev
						= &(mbr_item_asgn[i + 1]);
			} else {
				mbr_item_asgn[i + 1] = mbr_item_asgn[i];
			}
		}

		if( tmp_item.next == &tmp_item ){
			mbr_item_asgn[0].next = &(mbr_item_asgn[0]);
			mbr_item_asgn[0].prev = &(mbr_item_asgn[0]);
		} else {
			mbr_item_asgn[0] = tmp_item;
		}
	} else {
		mbr_t	**ls_mbr;

		ls_mbr = get_ls_mbr();
		for( i = n + 1; i < LS_MBR_MAX_N; i++ ){
			if( chk_flg( ls_mbr[i]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}

			if( mbr_item_asgn[i].next
					!= &(mbr_item_asgn[i]) ){
				mbr_item_asgn[i].next->prev
						= &(mbr_item_asgn[i - 1]);
			}
			if( mbr_item_asgn[i].prev
					!= &(mbr_item_asgn[i]) ){
				mbr_item_asgn[i].prev->next
						= &(mbr_item_asgn[i - 1]);
			}
		}

		if( mbr_item_asgn[n].next
				!= &(mbr_item_asgn[n]) ){
			mbr_item_asgn[n].next->prev
					= &(mbr_item_asgn[i - 1]);
		}
		if( mbr_item_asgn[n].prev
				!= &(mbr_item_asgn[n]) ){
			mbr_item_asgn[n].prev->next
					= &(mbr_item_asgn[i - 1]);
		}

		/**/

		for( i = n + 1; i < LS_MBR_MAX_N; i++ ){
			if( chk_flg( ls_mbr[i]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}

			if( mbr_item_asgn[i].next == &(mbr_item_asgn[i]) ){
				mbr_item_asgn[i - 1].next
						= &(mbr_item_asgn[i - 1]);
				mbr_item_asgn[i - 1].prev
						= &(mbr_item_asgn[i - 1]);
			} else {
				mbr_item_asgn[i - 1] = mbr_item_asgn[i];
			}
		}

		if( tmp_item.next == &tmp_item ){
			mbr_item_asgn[i - 1].next = &(mbr_item_asgn[i - 1]);
			mbr_item_asgn[i - 1].prev = &(mbr_item_asgn[i - 1]);
		} else {
			mbr_item_asgn[i - 1] = tmp_item;
		}
	}
}

/**/

void	arrange_equip_1( long n, long d )
{
	item_t	tmp_item;
	long	j;

	for( j = 0; j < EQUIP_KIND_MAX_N; j++ ){
		tmp_item = mbr_item_asgn_equip[n][j];

		mbr_item_asgn_equip[n][j] = mbr_item_asgn_equip[n + d][j];

		mbr_item_asgn_equip[n + d][j] = tmp_item;
	}
}

/**/

void	arrange_equip( long n, long d )
{
	item_t	tmp_item;
	long	i, j;

	for( j = 0; j < EQUIP_KIND_MAX_N; j++ ){
		tmp_item = mbr_item_asgn_equip[n][j];

		if( d <= -1 ){
			for( i = n - 1; i >= 0; i-- ){
				mbr_item_asgn_equip[i + 1][j]
						= mbr_item_asgn_equip[i][j];
			}

			mbr_item_asgn_equip[0][j] = tmp_item;
		} else {
			mbr_t	**ls_mbr;

			ls_mbr = get_ls_mbr();
			for( i = n + 1; i < LS_MBR_MAX_N; i++ ){
				if( chk_flg( ls_mbr[i]->stat,
						FLG_STAT_NOT_EXIST ) ){
					break;
				}

				mbr_item_asgn_equip[i - 1][j]
						= mbr_item_asgn_equip[i][j];
			}

			mbr_item_asgn_equip[i - 1][j] = tmp_item;
		}
	}
}

/**/

item_t	*get_item_free_next( void )
{
	if( item_free.next == &item_free )
		return NULL;

	return item_free.next;
}

/**/

item_t	*get_mbr_item_asgn( mbr_t *mbr )
{
	if( mbr == NULL )
		return NULL;
	if( !is_mbr( mbr ) )
		return NULL;

	return &(mbr_item_asgn[mbr->ls_mbr_n]);
}

/**/

item_t	*get_mbr_item_asgn_equip( mbr_t *mbr )
{
	if( mbr == NULL )
		return NULL;
	if( !is_mbr( mbr ) )
		return NULL;

	return mbr_item_asgn_equip[mbr->ls_mbr_n];
}

/**/

item_t	*get_dun_item_asgn( void )
{
	return &dun_item_asgn;
}

/**/

item_t	*get_shop_bar_item_asgn( void )
{
	return &shop_bar_item_asgn;
}

/**/

item_t	*get_shop_wpn_item_asgn( void )
{
	return &shop_wpn_item_asgn;
}

/**/

item_t	*get_shop_armor_item_asgn( void )
{
	return &shop_armor_item_asgn;
}

/**/

item_t	*get_shop_temple_item_asgn( void )
{
	return &shop_temple_item_asgn;
}

/**/

item_t	*get_shop_alchemy_item_asgn( void )
{
	return &shop_alchemy_item_asgn;
}

/**/

item_t	*get_shop_music_item_asgn( void )
{
	return &shop_music_item_asgn;
}

/**/

item_t	*get_shop_grocery_item_asgn( void )
{
	return &shop_grocery_item_asgn;
}

/**/

item_t	*get_shop_restaurant_item_asgn( void )
{
	return &shop_restaurant_item_asgn;
}

/**/

item_t	*get_shop_tearoom_item_asgn( void )
{
	return &shop_tearoom_item_asgn;
}

/**/

item_t	*get_shop_tobacco_item_asgn( void )
{
	return &shop_tobacco_item_asgn;
}

/**/

bool_t	chk_wpn_randm_art(
	wpn_randm_art_kind_t kind,
	char mnr,
	chr_t *o_p,
	chr_t *d_p,
	bool_t flg_throw
)
{
	item_t	*eq;

	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( !is_mbr( o_p ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( (mbr_t *)o_p );
	if( eq == NULL )
		return FALSE;

	if( flg_throw ){
		if( kind == WPN_RANDM_ART_KIND_SLAYER )
			if( eq[EQUIP_KIND_ARW].dat.wpn.slayer == mnr )
				return TRUE;
		if( eq[EQUIP_KIND_ARW].kind == ITEM_KIND_WPN ){
			if( chk_wpn_randm_art_item( kind, mnr, 
					&(eq[EQUIP_KIND_ARW]) ) ){
				return TRUE;
			}
		}

		if( kind == WPN_RANDM_ART_KIND_SLAYER )
			if( eq[EQUIP_KIND_BOW].dat.wpn.slayer == mnr )
				return TRUE;
		if( eq[EQUIP_KIND_BOW].kind == ITEM_KIND_WPN ){
			if( chk_wpn_randm_art_item( kind, mnr, 
					&(eq[EQUIP_KIND_BOW]) ) ){
				return TRUE;
			}
		}
	} else {
		if( kind == WPN_RANDM_ART_KIND_SLAYER )
			if( eq[EQUIP_KIND_WIELDING].dat.wpn.slayer == mnr )
				return TRUE;
		if( eq[EQUIP_KIND_WIELDING].kind == ITEM_KIND_WPN ){
			if( chk_wpn_randm_art_item( kind, mnr, 
					&(eq[EQUIP_KIND_WIELDING]) ) ){
				return TRUE;
			}
		}
	}

	return FALSE;
}

/**/

bool_t	chk_armor_randm_art(
	armor_randm_art_kind_t kind,
	char mnr,
	chr_t *o_p,
	chr_t *d_p
)
{
	item_t	*eq;
	long	i;

	if( d_p == NULL )
		return FALSE;
	if( !is_mbr( d_p ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( (mbr_t *)d_p );
	if( eq == NULL )
		return FALSE;

	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		if( eq[i].kind != ITEM_KIND_ARMOR )
			continue;

		if( chk_armor_randm_art_item( kind, mnr, &(eq[i]) ) )
			return TRUE;
	}

	return FALSE;
}

/**/

bool_t	chk_wpn_randm_art_item(
	wpn_randm_art_kind_t kind,
	char mnr,
	item_t *item
)
{
	wpn_randm_art_t	*art;
	long	i;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_WPN )
		return FALSE;

	art = item->dat.wpn.randm_art;

	for( i = 0; i < WPN_RANDM_ART_LS_MAX_N; i++ ){
		if( art[i].kind == WPN_RANDM_ART_KIND_NULL )
			break;

		if( art[i].kind != kind )
			continue;
		if( toupper( art[i].mnr ) != toupper( mnr ) )
			continue;

		return TRUE;
	}

	return FALSE;
}

/**/

bool_t	chk_armor_randm_art_item(
	armor_randm_art_kind_t kind,
	char mnr,
	item_t *item
)
{
	armor_randm_art_t	*art;
	long	i;

	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_ARMOR )
		return FALSE;

	art = item->dat.armor.randm_art;

	for( i = 0; i < ARMOR_RANDM_ART_LS_MAX_N; i++ ){
		if( art[i].kind == ARMOR_RANDM_ART_KIND_NULL )
			break;

		if( art[i].kind != kind )
			continue;
		if( toupper( art[i].mnr ) != toupper( mnr ) )
			continue;

		return TRUE;
	}

	return FALSE;
}

/**/

rate_t	get_resi_armor( mbr_t *p, resi_kind_t resi )
{
	item_t	*eq;
	rate_t	n;
	long	i;

	if( p == NULL )
		return _100_PERCENT;
	if( !is_mbr( p ) )
		return _100_PERCENT;

	eq = get_mbr_item_asgn_equip( p );
	if( eq == NULL )
		return _100_PERCENT;

	n = _100_PERCENT;

	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		rate_t	a;

		if( eq[i].kind != ITEM_KIND_ARMOR )
			continue;
		if( eq[i].tab.armor == NULL )
			continue;

		a = eq[i].tab.armor->up_resi[resi];
		if( a == RESI_PERFECT_N )
			return RESI_PERFECT_N;

		n += a;
	}

	if( n < 1 )
		n = 1;

	return n;
}

/**/

bool_t	chk_wear_armor( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;

	if( eq[EQUIP_KIND_BODY].kind == ITEM_KIND_NULL )
		return FALSE;

	return TRUE;
}

/**/

spell_kind_t	get_inst_spell_kind( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return SPELL_KIND_NULL;
	if( !is_mbr( mbr ) )
		return SPELL_KIND_NULL;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return SPELL_KIND_NULL;
	eq = &(eq[EQUIP_KIND_WIELDING]);
	if( eq->kind != ITEM_KIND_INST )
		return SPELL_KIND_NULL;

	return( eq->dat.inst.spell_kind );
}

/**/

long	expr_wpn_add_hit( long lev )
{
	/* アイテム作成時の修正値 */

	return( randm( labs( lev ) / 20 + 1 ) );
}

/**/

long	expr_wpn_add_crtcl( long lev )
{
	/* アイテム作成時の修正値 */

	return( randm( labs( lev ) / 20 + 1 ) );
}

/**/

long	expr_wpn_add_dam( long lev )
{
	/* アイテム作成時の修正値 */

	return( randm( labs( lev ) / 20 + 1 ) );
}

/**/

long	expr_armor_add_def( long lev )
{
	/* アイテム作成時の修正値 */

	return( randm( labs( lev ) / 20 + 1 ) );
}

/**/

long	expr_armor_add_crtcl( long lev )
{
	/* アイテム作成時の修正値 */

	return( randm( labs( lev ) / 20 + 1 ) );
}

/**/

long	expr_armor_add_ac( long lev )
{
	/* アイテム作成時の修正値 */

	return( randm( labs( lev ) / 20 + 1 ) );
}

/**/

long	expr_light_turn( long max )
{
	return( randm( max ) );
}

/**/

char	*get_item_mjr_name( char mjr )
{
	switch( mjr ){
	case FACE_MJR_WEAPON:
		return MSG_ITEM_MJR_NAME_WEAPON;
	case FACE_MJR_ARMOR:
		return MSG_ITEM_MJR_NAME_ARMOR;
	case FACE_MJR_POTION:
		return MSG_ITEM_MJR_NAME_POTION;
	case FACE_MJR_SCROLL:
		return MSG_ITEM_MJR_NAME_SCROLL;
	case FACE_MJR_STICK:
		return MSG_ITEM_MJR_NAME_STICK;
	case FACE_MJR_ACCESSORY:
		return MSG_ITEM_MJR_NAME_ACCESSORY;
	case FACE_MJR_FOOD:
		return MSG_ITEM_MJR_NAME_FOOD;
	case FACE_MJR_CHEST:
		return MSG_ITEM_MJR_NAME_CHEST;
	case FACE_MJR_COIN:
		return MSG_ITEM_MJR_NAME_COIN;
	case FACE_MJR_GEM:
		return MSG_ITEM_MJR_NAME_GEM;
	case FACE_MJR_MISC:
		return MSG_ITEM_MJR_NAME_MISC;
	/* default: */
	}

	return MSG_ITEM_MJR_NAME_ERR;
}

/**/

char	*get_item_mnr_name( char mjr, char mnr )
{
	switch( mjr ){
	case FACE_MJR_WEAPON:
		switch( mnr ){
		case FACE_MNR_KNIFE:
			return MSG_ITEM_MNR_NAME_KNIFE;
		case FACE_MNR_SHORT_SWORD:
			return MSG_ITEM_MNR_NAME_SHORT_SWORD;
		case FACE_MNR_LONG_SWORD:
			return MSG_ITEM_MNR_NAME_LONG_SWORD;
		case FACE_MNR_SABRE:
			return MSG_ITEM_MNR_NAME_SABRE;
		case FACE_MNR_RAPIER:
			return MSG_ITEM_MNR_NAME_RAPIER;
		case FACE_MNR_HAND_AXE:
			return MSG_ITEM_MNR_NAME_HAND_AXE;
		case FACE_MNR_BATTLE_AXE:
			return MSG_ITEM_MNR_NAME_BATTLE_AXE;
		case FACE_MNR_SPEAR:
			return MSG_ITEM_MNR_NAME_SPEAR;
		case FACE_MNR_LANCE:
			return MSG_ITEM_MNR_NAME_LANCE;
		case FACE_MNR_FLAIL:
			return MSG_ITEM_MNR_NAME_FLAIL;
		case FACE_MNR_MACE:
			return MSG_ITEM_MNR_NAME_MACE;
		case FACE_MNR_HAMMER:
			return MSG_ITEM_MNR_NAME_HAMMER;
		case FACE_MNR_GLAIVE:
			return MSG_ITEM_MNR_NAME_GLAIVE;
		case FACE_MNR_KNUCKLE:
			return MSG_ITEM_MNR_NAME_KNUCKLE;
		case FACE_MNR_BOW:
			return MSG_ITEM_MNR_NAME_BOW;
		case FACE_MNR_ARW:
			return MSG_ITEM_MNR_NAME_ARW;
		case FACE_MNR_STONE:
			return MSG_ITEM_MNR_NAME_STONE;
		case FACE_MNR_DAGGER:
			return MSG_ITEM_MNR_NAME_DAGGER;
		/* default: */
		}
		break;
	case FACE_MJR_ARMOR:
		switch( mnr ){
		case FACE_MNR_ARMOR_SHIELD:
			return MSG_ITEM_MNR_NAME_ARMOR_SHIELD;
		case FACE_MNR_ARMOR_HEAD:
			return MSG_ITEM_MNR_NAME_ARMOR_HEAD;
		case FACE_MNR_ARMOR_BODY:
			return MSG_ITEM_MNR_NAME_ARMOR_BODY;
		case FACE_MNR_ARMOR_ARM:
			return MSG_ITEM_MNR_NAME_ARMOR_ARM;
		case FACE_MNR_ARMOR_FEET:
			return MSG_ITEM_MNR_NAME_ARMOR_FEET;
		case FACE_MNR_ARMOR_ABOUT_BODY:
			return MSG_ITEM_MNR_NAME_ARMOR_ABOUT_BODY;
		/* default: */
		}
		break;
	case FACE_MJR_POTION:
		return MSG_ITEM_MNR_NAME_POTION;
	case FACE_MJR_SCROLL:
		return MSG_ITEM_MNR_NAME_SCROLL;
	case FACE_MJR_STICK:
		switch( mnr ){
		case FACE_MNR_WAND:
			return MSG_ITEM_MNR_NAME_WAND;
		case FACE_MNR_ROD:
			return MSG_ITEM_MNR_NAME_ROD;
		case FACE_MNR_STAFF:
			return MSG_ITEM_MNR_NAME_STAFF;
		/* default: */
		}
		break;
	case FACE_MJR_ACCESSORY:
		switch( mnr ){
		case FACE_MNR_RING:
			return MSG_ITEM_MNR_NAME_RING;
		case FACE_MNR_AMULET:
			return MSG_ITEM_MNR_NAME_AMULET;
		case FACE_MNR_NECKLACE:
			return MSG_ITEM_MNR_NAME_NECKLACE;
		/* default: */
		}
		break;
	case FACE_MJR_FOOD:
		return MSG_ITEM_MNR_NAME_FOOD;
	case FACE_MJR_CHEST:
		return MSG_ITEM_MNR_NAME_CHEST;
	case FACE_MJR_COIN:
		return MSG_ITEM_MNR_NAME_COIN;
	case FACE_MJR_GEM:
		return MSG_ITEM_MNR_NAME_GEM;
	case FACE_MJR_MISC:
		switch( mnr ){
		case FACE_MNR_INST:
			return MSG_ITEM_MNR_NAME_INST;
		case FACE_MNR_ANTHOLOGY:
			return MSG_ITEM_MNR_NAME_ANTHOLOGY;
		case FACE_MNR_LIGHT:
			return MSG_ITEM_MNR_NAME_LIGHT;
		case FACE_MNR_SPIKE:
			return MSG_ITEM_MNR_NAME_SPIKE;
		case FACE_MNR_TOBACCO:
			return MSG_ITEM_MNR_NAME_TOBACCO;
		case FACE_MNR_PIPE:
			return MSG_ITEM_MNR_NAME_PIPE;
		case FACE_MNR_DISPOSAL:
			return MSG_ITEM_MNR_NAME_DISPOSAL;
		case FACE_MNR_RARE_GOODS:
			return MSG_ITEM_MNR_NAME_RARE_GOODS;
		case FACE_MNR_BONE_GOOD:
			return MSG_ITEM_MNR_NAME_BONE_GOOD;
		case FACE_MNR_BONE_EVIL:
			return MSG_ITEM_MNR_NAME_BONE_EVIL;
		case FACE_MNR_JUNK:
			return MSG_ITEM_MNR_NAME_JUNK;
		/* default: */
		}
		break;
	/* default: */
	}

	if( g_flg_debug ){
		return MSG_ITEM_MNR_NAME_ERR;
	} else {
		return MSG_NULL;
	}
}

/**/

char	*get_item_equip_name( equip_kind_t kind )
{
	switch( kind ){
	case EQUIP_KIND_WIELDING:
		return MSG_EQUIP_WIELDING;
	case EQUIP_KIND_SHIELD:
		return MSG_EQUIP_SHIELD;
	case EQUIP_KIND_BOW:
		return MSG_EQUIP_BOW;
	case EQUIP_KIND_ARW:
		return MSG_EQUIP_ARW;
	case EQUIP_KIND_HEAD:
		return MSG_EQUIP_HEAD;
	case EQUIP_KIND_NECK:
		return MSG_EQUIP_NECK;
	case EQUIP_KIND_BODY:
		return MSG_EQUIP_BODY;
	case EQUIP_KIND_ARM:
		return MSG_EQUIP_ARM;
	case EQUIP_KIND_RIGHT_HAND:
		return MSG_EQUIP_RIGHT_HAND;
	case EQUIP_KIND_LEFT_HAND:
		return MSG_EQUIP_LEFT_HAND;
	case EQUIP_KIND_FEET:
		return MSG_EQUIP_FEET;
	case EQUIP_KIND_ABOUT_BODY:
		return MSG_EQUIP_ABOUT_BODY;
	case EQUIP_KIND_LIGHT_SOURCE:
		return MSG_EQUIP_LIGHT_SOURCE;
	case EQUIP_KIND_MAX_N:
		break;
	}

	return "";
}

/**/

item_t	*get_item_mbr( long ls_mbr_n, item_kind_t kind )
{
	item_t	*p;

	for( p = mbr_item_asgn[ls_mbr_n].next;
			p != &mbr_item_asgn[ls_mbr_n]; p = p->next ){
		if( p->kind == kind )
			return p;
	}

	return NULL;
}

/**/

item_t	*get_item_mbr_randm( long ls_mbr_n )
{
	item_t	*p, *ret;
	long	n;

	ret = NULL;
	n = 1;
	for( p = mbr_item_asgn[ls_mbr_n].next;
			p != &mbr_item_asgn[ls_mbr_n]; p = p->next ){
		if( per_randm( n ) ){
			ret = p;
			n++;
		}
	}

	return ret;
}

/**/

item_t	*get_item_mbr_anthology( mbr_t *mbr, anthology_kind_t kind )
{
	long	ls_mbr_n;
	item_t	*p;

	if( mbr == NULL )
		return NULL;
	if( !is_mbr( mbr ) )
		return NULL;

	ls_mbr_n = mbr->ls_mbr_n;

	for( p = mbr_item_asgn[ls_mbr_n].next;
			p != &mbr_item_asgn[ls_mbr_n]; p = p->next ){
		if( p->kind != ITEM_KIND_ANTHOLOGY )
			continue;
		if( !chk_flg( p->flg, FLG_ITEM_IDENTIFIED ) )
			continue;
		if( p->dat.anthology.kind != kind )
			continue;

		return p;
	}

	return NULL;
}

/**/

item_t	*get_item_nearest(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
)
{
	item_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	dun_t	*dun;

	if( chr == NULL )
		return NULL;

	dun = get_dun();

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( p = dun_item_asgn.next; p != &dun_item_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( !clip_pos( p->x, p->y ) )
			continue;
		if( dun->map.obj.mjr[p->y][p->x] == FACE_MJR_NULL )
			continue;

		if( is_mbr( chr ) ){
			if( !chk_flg( dun->map.obj.flg[p->y][p->x],
					FLG_MAP_OBJ_FIND ) ){
				continue;
			}
			if( !chk_mark_item( p, act_kind ) )
				continue;
			if( flg_auto_menu && !chk_appoint_item( p, chr ) )
				continue;
		}

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

/**/

item_t	*get_item_near(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
)
{
	item_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	dun_t	*dun;

	if( chr == NULL )
		return NULL;

	dun = get_dun();

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( p = dun_item_asgn.next; p != &dun_item_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( !clip_pos( p->x, p->y ) )
			continue;
		if( dun->map.obj.mjr[p->y][p->x] == FACE_MJR_NULL )
			continue;

		if( is_mbr( chr ) ){
			if( !chk_flg( dun->map.obj.flg[p->y][p->x],
					FLG_MAP_OBJ_FIND ) ){
				continue;
			}
			if( !chk_mark_item( p, act_kind ) )
				continue;
			if( flg_auto_menu && !chk_appoint_item( p, chr ) )
				continue;
		}

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
		} else if( (tmp_r - min_r) <= ITEM_NEAR_R ){
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/**/

item_t	*get_item_disperse(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
)
{
	item_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	long	x, y;
	dun_t	*dun;

	if( chr == NULL )
		return NULL;

	x = chr->x;
	y = chr->y;

	dun = get_dun();

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( p = dun_item_asgn.next; p != &dun_item_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( !clip_pos( p->x, p->y ) )
			continue;
		if( dun->map.obj.mjr[p->y][p->x] == FACE_MJR_NULL )
			continue;

		if( is_mbr( chr ) ){
			if( !chk_flg( dun->map.obj.flg[p->y][p->x],
					FLG_MAP_OBJ_FIND ) ){
				continue;
			}
			if( !chk_mark_item( p, act_kind ) )
				continue;
			if( flg_auto_menu && !chk_appoint_item( p, chr ) )
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

/**/

item_t	*get_item_randm(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
)
{
	item_t	*p, *ret_p;
	long	n;
	dun_t	*dun;

	if( chr == NULL )
		return NULL;

	dun = get_dun();

	ret_p = NULL;
	n = 0;
	for( p = dun_item_asgn.next; p != &dun_item_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( !clip_pos( p->x, p->y ) )
			continue;
		if( dun->map.obj.mjr[p->y][p->x] == FACE_MJR_NULL )
			continue;

		if( is_mbr( chr ) ){
			if( !chk_flg( dun->map.obj.flg[p->y][p->x],
					FLG_MAP_OBJ_FIND ) ){
				continue;
			}
			if( !chk_mark_item( p, act_kind ) )
				continue;
			if( flg_auto_menu && !chk_appoint_item( p, chr ) )
				continue;
		}

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

/**/

item_t	*get_item_own(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
)
{
	item_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	long	x, y;
	dun_t	*dun;

	if( chr == NULL )
		return NULL;

	x = chr->x;
	y = chr->y;

	dun = get_dun();

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( p = dun_item_asgn.next; p != &dun_item_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( !clip_pos( p->x, p->y ) )
			continue;
		if( dun->map.obj.mjr[p->y][p->x] == FACE_MJR_NULL )
			continue;

		if( is_mbr( chr ) ){
			if( !chk_flg( dun->map.obj.flg[p->y][p->x],
					FLG_MAP_OBJ_FIND ) ){
				continue;
			}
			if( !chk_mark_item( p, act_kind ) )
				continue;
			if( flg_auto_menu && !chk_appoint_item( p, chr ) )
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

		if( tmp_r < min_r ){
			if( is_mbr( chr ) )
				if( !chk_own_item( p, chr ) )
					continue;
			n = 0;
			min_r = tmp_r;
		} else if( tmp_r == min_r ){
			if( is_mbr( chr ) )
				if( !chk_own_item( p, chr ) )
					continue;
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/**/

item_t	*get_item_identified(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
)
{
	return get_item_identified_sub(
			chr, act_kind, flg_auto_menu, TRUE );
}

/**/

item_t	*get_item_un_identified(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
)
{
	return get_item_identified_sub(
			chr, act_kind, flg_auto_menu, FALSE );
}

/**/

item_t	*get_item_identified_sub(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu,
	bool_t flg_identified
)
{
	item_t	*p, *ret_p, *sub_ret_p;
	long	min_r, tmp_r;
	long	n, sub_n;
	long	x, y;
	dun_t	*dun;

	if( chr == NULL )
		return NULL;

	x = chr->x;
	y = chr->y;

	dun = get_dun();

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	sub_ret_p = NULL;
	sub_n = 0;
	for( p = dun_item_asgn.next; p != &dun_item_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( !clip_pos( p->x, p->y ) )
			continue;
		if( dun->map.obj.mjr[p->y][p->x] == FACE_MJR_NULL )
			continue;

		if( is_mbr( chr ) ){
			if( !chk_flg( dun->map.obj.flg[p->y][p->x],
					FLG_MAP_OBJ_FIND ) ){
				continue;
			}
			if( !chk_mark_item( p, act_kind ) )
				continue;
			if( flg_auto_menu && !chk_appoint_item( p, chr ) )
				continue;
		}

		if( flg_identified ){
			if( !chk_flg( p->flg, FLG_ITEM_IDENTIFIED ) )
				continue;
		} else {
			if( chk_flg( p->flg, FLG_ITEM_IDENTIFIED ) )
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

/**/

item_t	*get_item_food(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
)
{
	item_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	dun_t	*dun;

	if( chr == NULL )
		return NULL;

	dun = get_dun();

	min_r = MAP_MAX_X + MAP_MAX_Y;
	ret_p = NULL;
	n = 0;
	for( p = dun_item_asgn.next; p != &dun_item_asgn; p = p->next ){
		pos_t	pos1, pos2;

		if( p->kind != ITEM_KIND_FOOD )
			continue;

		if( !clip_pos( p->x, p->y ) )
			continue;
		if( dun->map.obj.mjr[p->y][p->x] == FACE_MJR_NULL )
			continue;

		if( is_mbr( chr ) ){
			if( !chk_flg( dun->map.obj.flg[p->y][p->x],
					FLG_MAP_OBJ_FIND ) ){
				continue;
			}
			if( !chk_mark_item( p, act_kind ) )
				continue;
			if( flg_auto_menu && !chk_appoint_item( p, chr ) )
				continue;
		}

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
* 装備している武器をランダムに選ぶ
* item_t *eq : 装備リスト
* return : 選ばれたアイテム
***************************************************************/

item_t	*randm_wpn( item_t *eq )
{
	const long	max_n = 3;
	long	head, i;

	if( eq == NULL )
		return NULL;

	head = randm( max_n );

	for( i = 0; i < max_n; i++ ){
		long	n;
		equip_kind_t	k;

		n = (head + i) % max_n;
		if( n == 0 )
			k = EQUIP_KIND_WIELDING;
		else if( n == 1 )
			k = EQUIP_KIND_BOW;
		else
			k = EQUIP_KIND_ARW;

		if( eq[k].kind == ITEM_KIND_WPN ){
			return( &(eq[k]) );
		}
	}

	return NULL;
}

/***************************************************************
* 装備している防具をランダムに選ぶ
* item_t *eq : 装備リスト
* return : 選ばれたアイテム
***************************************************************/

item_t	*randm_armor( item_t *eq )
{
	long	head, i;

	if( eq == NULL )
		return NULL;

	head = randm( EQUIP_KIND_MAX_N );

	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		equip_kind_t	k;

		k = (equip_kind_t)((head + i) % EQUIP_KIND_MAX_N);
		if( k == EQUIP_KIND_WIELDING )
			continue;
		if( k == EQUIP_KIND_BOW )
			continue;
		if( k == EQUIP_KIND_ARW )
			continue;

		if( eq[k].kind == ITEM_KIND_ARMOR ){
			return( &(eq[k]) );
		}
	}

	return NULL;
}

/**/

bool_t	chk_mark_item( item_t *p, act_kind_t act_kind )
{
	if( p == NULL )
		return FALSE;

	switch( act_kind ){
	case ACT_KIND_ITEM_PICK_UP:
		return TRUE;
	case ACT_KIND_ITEM_BREAK:
		if( p->kind == ITEM_KIND_JUNK )
			return FALSE;
		return TRUE;
	case ACT_KIND_ITEM_CHK:
	case ACT_KIND_ITEM_SEND:
	case ACT_KIND_ITEM_DROP:
	case ACT_KIND_ITEM_RECEIVE:
	case ACT_KIND_ITEM_OPEN:
	case ACT_KIND_ITEM_DISARM:
		return TRUE;
	default:
		return FALSE;
	}

	return FALSE;
}

/**/

bool_t	chk_own_item( item_t *item, mbr_t *mbr )
{
	item_t	*p, *end;
	long	n;

	if( item == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	end = get_mbr_item_asgn( mbr );
	if( end != NULL )
		for( p = end->next; p != end; p = p->next )
			if( cmp_item( p, item ) )
				return TRUE;

	p = get_mbr_item_asgn_equip( mbr );
	if( p != NULL )
		for( n = 0; n < EQUIP_KIND_MAX_N; n++ )
			if( cmp_item( &(p[n]), item ) )
				return TRUE;

	return FALSE;
}

/**/

bool_t	chk_appoint_item( item_t *item, mbr_t *mbr )
{
	auto_mark_appoint_item_t	*apo;
	long	i;

	if( item == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	apo = get_auto_mark_appoint_item( mbr );
	if( apo == NULL )
		return FALSE;

	for( i = 0; i < AUTO_MARK_APPOINT_ITEM_MAX_N; i++ ){
		if( apo[i].mjr != item->mjr )
			continue;
		if( apo[i].mnr != item->mnr )
			continue;

		return( apo[i].flg_ena );
	}

	return FALSE;
}

/**/

bool_t	chk_mbr_have_rare_goods(
	mbr_t *mbr, rare_goods_kind_t kind,
	mnstr_kind_t mnstr_kind,
	bool_t flg_del_item
)
{
	item_t	*end, *p, *pp;
	long	n;
	bool_t	flg_have;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;
	if( chk_flg( mbr->stat, FLG_STAT_NOT_EXIST ) )
		return FALSE;

	flg_have = FALSE;

	end = get_mbr_item_asgn( mbr );
	if( end != NULL ){
		for( p = end->next->next; p->prev != end; p = p->next ){
			pp = p->prev;

			if( pp->kind != ITEM_KIND_RARE_GOODS )
				continue;
			if( pp->dat.rare_goods.kind != kind )
				continue;
			if( pp->dat.rare_goods.mnstr_kind != mnstr_kind )
				continue;

			if( flg_del_item )
				del_item( pp );

			flg_have = TRUE;
		}
	}

	p = get_mbr_item_asgn_equip( mbr );
	for( n = 0; n < EQUIP_KIND_MAX_N; n++ ){
		if( p == NULL )
			break;

		if( p[n].kind != ITEM_KIND_RARE_GOODS )
			continue;
		if( p[n].dat.rare_goods.kind != kind )
			continue;
		if( p[n].dat.rare_goods.mnstr_kind != mnstr_kind )
			continue;

		if( flg_del_item )
			del_item( &(p[n]) );

		flg_have = TRUE;
	}

	return flg_have;
}

/**/

long	get_chest_n( long dun_lev )
{
	long	d_lev, div;
	long	dn, n;

	d_lev = labs( dun_lev ) - CHEST_MIN_LEV;
	if( d_lev < 0 )
		d_lev = 0;

	div = CHEST_HOLD_MAX_LEV - CHEST_MIN_LEV;
	dn = CHEST_HOLD_MAX_N - CHEST_HOLD_MIN_N;

	n = CHEST_HOLD_MIN_N + (dn * d_lev / div);
	if( n > CHEST_HOLD_MAX_N )
		n = CHEST_HOLD_MAX_N;

	return n;
}

/**/

ls_identified_t	*get_color_tab( void )
{
	return color_tab;
}

/**/

n_msg_t	*get_color_idx_tab( void )
{
	return color_idx_tab;
}

/**/

n_msg_t	*get_ttl_syllable_idx_tab( void )
{
	return ttl_syllable_idx_tab;
}

/**/

ls_identified_t	*get_wand_material_tab( void )
{
	return wand_material_tab;
}

/**/

ls_identified_t	*get_rod_material_tab( void )
{
	return rod_material_tab;
}

/**/

ls_identified_t	*get_staff_material_tab( void )
{
	return staff_material_tab;
}

/**/

n_msg_t	*get_stick_material_idx_tab( void )
{
	return stick_material_idx_tab;
}

/**/

ls_identified_t	*get_ring_material_tab( void )
{
	return ring_material_tab;
}

/**/

ls_identified_t	*get_amulet_material_tab( void )
{
	return amulet_material_tab;
}

/**/

ls_identified_t	*get_necklace_material_tab( void )
{
	return necklace_material_tab;
}

/**/

n_msg_t	*get_acce_material_idx_tab( void )
{
	return acce_material_idx_tab;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_item_c( void )
{
	check_memory( check_memory_item_c_item_buf,
			"item.c: item_buf" );
	check_memory( check_memory_item_c_item_free,
			"item.c: item_free" );
	check_memory( check_memory_item_c_mbr_item_asgn,
			"item.c: mbr_item_asgn" );
	check_memory( check_memory_item_c_mbr_item_asgn_equip,
			"item.c: mbr_item_asgn_equip" );
	check_memory( check_memory_item_c_dun_item_asgn,
			"item.c: dun_item_asgn" );
	check_memory( check_memory_item_c_wpn_tab_max_n,
			"item.c: wpn_tab_max_n" );
	check_memory( check_memory_item_c_ls_msg_chk_item_data,
			"item.c: ls_msg_chk_item_data" );
}
