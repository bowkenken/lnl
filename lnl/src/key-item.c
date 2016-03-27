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
* $Id: key-item.c,v 1.11 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* キー・アイテム
***************************************************************/

#define	KEY_ITEM_C
#include	"inc.h"

/***************************************************************
* 変数定義
***************************************************************/

/***************************************************************
* 星の雫
***************************************************************/

/* パーティが手に入れた星の雫 */
static bool_t	g_ls_flg_party_have_star_drop[STAR_DROP_KIND_MAX_N];
check_memory_def( check_memory_key_item_c_g_ls_flg_party_have_star_drop )

/* 星の雫の名前 */
static n_msg_t	g_ls_star_drop_name[STAR_DROP_KIND_MAX_N] = {
	N_MSG_STAR_DROP_ELEC,
	N_MSG_STAR_DROP_PHYS,
	N_MSG_STAR_DROP_HEAT,
	N_MSG_STAR_DROP_COLD,
	N_MSG_STAR_DROP_MIND,
	N_MSG_STAR_DROP_ACID,
	N_MSG_STAR_DROP_POIS,
};
check_memory_def( check_memory_key_item_c_g_ls_star_drop_name )

/***************************************************************
* 起動装置
***************************************************************/

/* 動き出した起動装置 */
static bool_t	g_ls_flg_drive_boot_unit[STAR_DROP_KIND_MAX_N];
check_memory_def( check_memory_key_item_c_g_ls_flg_drive_boot_unit )

/***************************************************************
* 初期化
***************************************************************/

void	init_key_item( void )
{
	long	i;

	for( i = 0; i < STAR_DROP_KIND_MAX_N; i++ ){
		g_ls_flg_party_have_star_drop[i] = FALSE;
		g_ls_flg_drive_boot_unit[i] = FALSE;
	}

	if( g_flg_debug )
		init_key_item_debug();
}

/***************************************************************
* デバッグ時の初期化
***************************************************************/

void	init_key_item_debug( void )
{
	long	i;

	for( i = 0; i < BOOT_UNIT_MAX_N; i++ )
		g_ls_flg_party_have_star_drop[i] = TRUE;
}

/***************************************************************
* 星の雫を持っているか調べる
* star_drop_kind_t kind : 星の雫の種類
* return : 星の雫を持っているか?
***************************************************************/

bool_t	chk_key_item( star_drop_kind_t kind )
{
	if( kind < 0 )
		return FALSE;
	if( kind >= STAR_DROP_KIND_MAX_N )
		return FALSE;

	return g_ls_flg_party_have_star_drop[kind];
}

/***************************************************************
* 星の雫を持っているか設定
* star_drop_kind_t kind : 星の雫の種類
* bool_t flg_have : 星の雫を持っているか?
***************************************************************/

void	set_key_item( star_drop_kind_t kind, bool_t flg_have )
{
	if( kind < 0 )
		return;
	if( kind >= STAR_DROP_KIND_MAX_N )
		return;

	g_ls_flg_party_have_star_drop[kind] = flg_have;
}

/***************************************************************
* パーティが星界へ入れるか調べる
* return : 星界へ入れるか?
***************************************************************/

bool_t	chk_enter_last_stage( void )
{
	long	i;

	for( i = 0; i < BOOT_UNIT_MAX_N; i++ )
		if( !g_ls_flg_party_have_star_drop[i] )
			return FALSE;

	return TRUE;
}

/***************************************************************
* 起動装置のイベント
***************************************************************/

void	event_boot_unit( long x, long y )
{
	dun_t	*dun;
	char	mnr;
	long	n;
	const char	*name;
	long	i;

	if( get_last_scene() != LAST_SCENE_N_ENTER )
		return;

	if( !clip_pos( x, y ) )
		return;
	dun = get_dun();
	mnr = dun->map.obj.mnr[y][x];

	n = mnr - '0';
	if( n < 0 )
		return;
	if( n >= BOOT_UNIT_MAX_N )
		return;
	if( g_ls_flg_drive_boot_unit[n] )
		return;
	if( !g_ls_flg_party_have_star_drop[n] )
		return;

	/* 起動装置を作動 */

	name = MSG( g_ls_star_drop_name[n] );
	print_msg( FLG_NULL, MSG_DRIVE_BOOT_UNIT, name );

	g_ls_flg_drive_boot_unit[n] = TRUE;

	for( i = 0; i < BOOT_UNIT_MAX_N; i++ )
		if( !g_ls_flg_drive_boot_unit[i] )
			break;
	if( i >= BOOT_UNIT_MAX_N )
		open_last_boss_gate();
	else
		call_game_sound_play( SOUND_KIND_EVENT_DRIVE, 1 );
}

/***************************************************************
* 星の雫の名前を返す
* star_drop_kind_t kind : 星の雫の種類
* return : 星の雫の名前
***************************************************************/

const char	*get_key_item_name( star_drop_kind_t kind )
{
	if( kind < 0 )
		return "";
	if( kind >= STAR_DROP_KIND_MAX_N )
		return "";

	return MSG( g_ls_star_drop_name[kind] );
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_key_item_c( void )
{
	check_memory( check_memory_key_item_c_g_ls_flg_party_have_star_drop,
			"key-item.c: g_ls_flg_party_have_star_drop" );
	check_memory( check_memory_key_item_c_g_ls_star_drop_name,
			"key-item.c: g_ls_star_drop_name" );
	check_memory( check_memory_key_item_c_g_ls_flg_drive_boot_unit,
			"key-item.c: g_ls_flg_drive_boot_unit" );
}
