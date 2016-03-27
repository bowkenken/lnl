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
* $Id: gf-outmap.c,v 1.7 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ファイル入出力 (マップを出力)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* マップを出力するファイル名をユーザから入力する
* char *s : ファイル名の入力先
* return : ファイル名(キャンセルなら NULL)
***************************************************************/

char	*get_out_map_file_name( char *s )
{
	long	i;
	const long	max_i = LOOP_MAX_1000;
	static char	fname[FILE_NAME_MAX_LEN + 1];
	static char	num_s[10 + 1];
	long	y;
	ask_t	ask;

	set_map_total( 0, 0, MAP_MAX_X, MAP_MAX_Y );
	wipe_all();

	/* デフォルトのファイル名を生成 */
	for( i = 0; i < max_i; i++ ){
		sn_printf( num_s, 10, STR_EXT_NAME_OUT_MAP, i );

		str_nz_cpy( fname, dir_name_game, FILE_NAME_MAX_LEN );
		str_max_n_cat( fname, STR_SLASH,
				FILE_NAME_MAX_LEN );
		str_max_n_cat( fname, STR_DIR_NAME_OUT_MAP,
				FILE_NAME_MAX_LEN );
		str_max_n_cat( fname, STR_SLASH,
				FILE_NAME_MAX_LEN );
		str_max_n_cat( fname, STR_FILE_NAME_OUT_MAP,
				FILE_NAME_MAX_LEN );
		str_max_n_cat( fname, num_s,
				FILE_NAME_MAX_LEN );

		if( !chk_exist_file( fname ) )
			break;
	}
	if( i >= max_i )
		return NULL;

	y = 0;
	print_str( 0, y, MSG_OUT_MAP_FILE_1 );
	y++;
	print_str( 0, y, MSG_OUT_MAP_FILE_2, fname );
	y++;

	/* ファイル名を入力 */
	str_nz_cpy( s, fname, FILE_NAME_MAX_LEN );
	game_gets( -1, -1, MSG_OUT_MAP_FILE_1,
			s, FILE_NAME_MAX_LEN, TRUE );

	if( s[0] == '\0' ){
		str_nz_cpy( s, fname, FILE_NAME_MAX_LEN );
	} else if( (s[0] == '/') || (s[0] == '~') ){
		str_nz_cpy( fname, s, FILE_NAME_MAX_LEN );
	} else {
		str_nz_cpy( fname, dir_name_game, FILE_NAME_MAX_LEN );
		str_max_n_cat( fname, STR_SLASH,
				FILE_NAME_MAX_LEN );
		str_max_n_cat( fname, STR_DIR_NAME_OUT_MAP,
				FILE_NAME_MAX_LEN );
		str_max_n_cat( fname, STR_SLASH,
				FILE_NAME_MAX_LEN );
		str_max_n_cat( fname, s,
				FILE_NAME_MAX_LEN );

		str_nz_cpy( s, fname, FILE_NAME_MAX_LEN );
	}

	print_str( 0, y, MSG_OUT_MAP_FILE_3, fname );
	y++;

	/* 本当に出力するか確認をとる */
	ask = exec_menu_ask( MSG_OUT_MAP_FILE_ASK_OK, ASK_NO, FALSE );

	wipe_menu();

	switch( ask ){
	case ASK_YES:
		return s;
	case ASK_NO:
	case ASK_CANCEL:
	case ASK_ERR:
		break;
	}

	return NULL;
}

/***************************************************************
* マップをファイルに出力する
* return : エラーが無かったか?
***************************************************************/

bool_t	out_map_file( void )
{
	static char	fname[FILE_NAME_MAX_LEN + 1];
	long	x, y;
	dun_t	*dun;
	FILE	*fp;

	if( get_out_map_file_name( fname ) == NULL )
		return FALSE;

	fp = fopen( fname, "w" );
	if( fp == NULL )
		return FALSE;

	reset_load_save( fname, TRUE );

	dun = get_dun();

	for( y = 0; y < MAP_MAX_Y; y++ ){
		for( x = 0; x < MAP_MAX_X; x++ ){
			fprintf( fp, "%c%c",
					dun->map.total.mjr[y][x],
					dun->map.total.mnr[y][x] );
		}
		fprintf( fp, "\n" );
	}

	if( fclose( fp ) == EOF )
		return FALSE;

	return TRUE;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_gf_outmap_c( void )
{
}
