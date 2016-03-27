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
* $Id: gf-gconf.c,v 1.8 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ファイル入出力 (グラフィック設定)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* グラフィック設定のロード
* char *path : ファイルのフルパス
* return : エラーが無かったか?
***************************************************************/

bool_t	load_graph_conf( char *path )
{
	ver_t	ver;
	FILE	*fp;
	bool_t	flg_err;

	flg_err = TRUE;

	/* ファイルをオープン */

	fp = fopen( path, "r" );
	if( fp == NULL )
		return FALSE;

	reset_load_save( path, TRUE );

	/* ヘッダの読み込み */

	if( !load_graph_conf_head( fp, &ver ) ){
		fclose( fp );
		return TRUE;
	}

	/* バージョンのチェック */

	if( chk_ver_new( &ver,
			GRAPH_CONF_VER_MJR,
			GRAPH_CONF_VER_MNR,
			GRAPH_CONF_VER_PAT ) ){
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_A,
				ver.mjr, ver.mnr, ver.pat );
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_B );

		fclose( fp );
		return TRUE;
	}

	/* データの読み込み */

	switch( ver.mjr ){
	case 1:
		load_graph_conf_data_ver_1( fp, &ver );
		flg_err = get_rc_lex_err();
		break;
	default:
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_A,
				ver.mjr, ver.mnr, ver.pat );
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_B );

		flg_err = TRUE;
		break;
	}

	/* ファイルをクローズ */

	if( fclose( fp ) == EOF )
		return TRUE;

	/* エラー・メッセージを表示 */

	if( flg_err ){
		print_err( MSG_ERR_RC );
		print_err( "'%s'", get_rc_lex_file_name() );
	}

	return TRUE;
}

/***************************************************************
* グラフィック設定のヘッダーのロード
* FILE *fp : ファイル
* ver_t *ver : ファイルのバージョン
* return : エラーが無かったか?
***************************************************************/

bool_t	load_graph_conf_head( FILE *fp, ver_t *ver )
{
	const long	len_head = str_len_std( STR_GRAPH_CONF_HEAD );
	char	*s;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	ver->mjr = 0;
	ver->mnr = 0;
	ver->pat = 0;

	s = load_line( fp, TRUE );
	if( strncmp( s, STR_GRAPH_CONF_HEAD, len_head ) != 0 ){
		print_lex_err( MSG_ERR_LOAD_GRAPH_CONF_HEAD );
		return FALSE;
	}

	/* バージョン・チェック */

	if( str_len_std( s ) < len_head )
		return FALSE;
	s = &(s[len_head]);

	sscanf( s, " %ld.%ld.%ld ", &(ver->mjr), &(ver->mnr), &(ver->pat) );

	if( (ver->mjr == 0) && (ver->mnr == 0) && (ver->pat == 0) )
		return FALSE;

	/**/

	return TRUE;
}

/***************************************************************
* グラフィック設定のデータのロード(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
***************************************************************/

void	load_graph_conf_data_ver_1( FILE *fp, const ver_t *ver )
{
	while( 1 ){
		if( !load_graph_conf_parse_ver_1( fp, ver ) )
			break;
	}
}

/***************************************************************
* グラフィック設定のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* return : エラーが無かったか?
***************************************************************/

bool_t	load_graph_conf_parse_ver_1( FILE *fp, const ver_t *ver )
{
	rc_token_t	t[MAX_TOKEN];
	rc_union_t	u[MAX_TOKEN];
	bool_t	flg_err_exit, flg_err;
	long	i;

	flg_err_exit = FALSE;

	for( i = 0; i < MAX_TOKEN; i++ )
		t[i] = RC_TOKEN_EOF;

	for( i = 0; i < MAX_TOKEN; i++ ){
		t[i] = rc_lex( fp, &(u[i]), flg_err_exit );
		if( t[i] == RC_TOKEN_EOF )
			break;
		if( t[i] == '\n' )
			break;
	}
	if( i >= MAX_TOKEN ){
		for( i = 0; i < LOOP_MAX_100; i++ ){
			rc_token_t	t;
			rc_union_t	u;

			t = rc_lex( fp, &u, flg_err_exit );
			if( t == RC_TOKEN_EOF )
				break;
			if( t == '\n' )
				break;
		}
	}

	flg_err = FALSE;

	if( t[0] == RC_TOKEN_EOF ){
		return FALSE;
	} else if( t[0] == '\n' ){
		return TRUE;
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == '{')
			&& (t[2] == '\n') ){
		/* foo { */

		if( !load_graph_conf_block_begin(
				fp, ver, flg_err_exit,
				u[0].str, 0 ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == '}')
			&& (t[1] == '\n') ){
		/* } */

		if( !load_graph_conf_block_end(
				fp, ver, flg_err_exit,
				"", 0 ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == RC_TOKEN_NUM)
			&& (t[3] == '\n') ){
		/* foo = n */

		if( !load_graph_conf_set_val(
				fp, ver, flg_err_exit,
				u[0].str, u[2].n ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == RC_TOKEN_STR)
			&& (t[3] == '\n') ){
		/* foo = str */

		if( !load_graph_conf_set_str(
				fp, ver, flg_err_exit,
				u[0].str, u[2].str ) ){
			flg_err = TRUE;
		}
	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		flg_err = TRUE;
	}

	if( flg_err ){
		if( flg_err_exit )
			exit_game( EXIT_FAILURE );
		return FALSE;
	} else {
		return TRUE;
	}
}

/***************************************************************
* グラフィック設定のブロックを開始
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_err_exit : エラーで終了するか?
* char *id : ブロック名
* long val : 値
* return : エラーが無かったか?
***************************************************************/

bool_t	load_graph_conf_block_begin(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
)
{
	return call_sel_conf_eval_block_begin();
}

/***************************************************************
* グラフィック設定のブロックを終了
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_err_exit : エラーで終了するか?
* char *id : ブロック名
* long val : 値
* return : エラーが無かったか?
***************************************************************/

bool_t	load_graph_conf_block_end(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
)
{
	return call_sel_conf_eval_block_end();
}

/***************************************************************
* グラフィック設定の変数に数値を設定
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_err_exit : エラーで終了するか?
* char *id : 変数名
* long val : 値
* return : エラーが無かったか?
***************************************************************/

bool_t	load_graph_conf_set_val(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
)
{
#ifdef	D_ALL_GUI
	if( strcmp( id, "scale" ) == 0 ){
		return call_sel_conf_eval_set_num(
				GRAPH_CONF_TOKEN_SCALE, val );

	} else if( strcmp( id, "tile_size_x" ) == 0 ){
		return call_sel_conf_eval_set_num(
				GRAPH_CONF_TOKEN_TILE_SIZE_X, val );

	} else if( strcmp( id, "tile_size_y" ) == 0 ){
		return call_sel_conf_eval_set_num(
				GRAPH_CONF_TOKEN_TILE_SIZE_Y, val );

	} else if( strcmp( id, "text_mode" ) == 0 ){
		return call_sel_conf_eval_set_num(
				GRAPH_CONF_TOKEN_TEXT_MODE, val );

	} else if( strcmp( id, "font_size_point" ) == 0 ){
		return call_sel_conf_eval_set_num(
				GRAPH_CONF_TOKEN_FONT_SIZE_POINT, val );

	} else if( strcmp( id, "font_size_dot" ) == 0 ){
		return call_sel_conf_eval_set_num(
				GRAPH_CONF_TOKEN_FONT_SIZE_DOT, val );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );
		print_lex_err( "'%s'", id );
		return FALSE;
	}

	return FALSE;
#else
	return TRUE;
#endif
}

/***************************************************************
* グラフィック設定の変数に文字列を設定
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_err_exit : エラーで終了するか?
* char *id : 変数名
* long val : 値
* return : エラーが無かったか?
***************************************************************/

bool_t	load_graph_conf_set_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, char *str
)
{
#ifdef	D_ALL_GUI
	if( strcmp( id, "title" ) == 0 ){
		return call_sel_conf_eval_set_str(
				GRAPH_CONF_TOKEN_TITLE, str );

	} else if( strcmp( id, "character_patern" ) == 0 ){
		return call_sel_conf_eval_set_str(
				GRAPH_CONF_TOKEN_CHARACTER_PATERN, str );

	} else if( strcmp( id, "pc_patern" ) == 0 ){
		return call_sel_conf_eval_set_str(
				GRAPH_CONF_TOKEN_PC_PATERN, str );

	} else if( strcmp( id, "monster_patern" ) == 0 ){
		return call_sel_conf_eval_set_str(
				GRAPH_CONF_TOKEN_MONSTER_PATERN, str );

	} else if( strcmp( id, "wall_patern" ) == 0 ){
		return call_sel_conf_eval_set_str(
				GRAPH_CONF_TOKEN_WALL_PATERN, str );

	} else if( strcmp( id, "town_wall_patern" ) == 0 ){
		return call_sel_conf_eval_set_str(
				GRAPH_CONF_TOKEN_TOWN_WALL_PATERN, str );

	} else if( strcmp( id, "dungeon_wall_patern" ) == 0 ){
		return call_sel_conf_eval_set_str(
				GRAPH_CONF_TOKEN_DUNGEON_WALL_PATERN, str );

	} else if( strcmp( id, "door_patern" ) == 0 ){
		return call_sel_conf_eval_set_str(
				GRAPH_CONF_TOKEN_DOOR_PATERN, str );

	} else if( strcmp( id, "signboard_patern" ) == 0 ){
		return call_sel_conf_eval_set_str(
				GRAPH_CONF_TOKEN_SIGNBOARD_PATERN, str );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );

		return FALSE;
	}

	return FALSE;
#else
	return TRUE;
#endif
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_gf_gconf_c( void )
{
}
