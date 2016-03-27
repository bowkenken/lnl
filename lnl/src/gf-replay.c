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
* $Id: gf-replay.c,v 1.7 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ファイル入出力 (リプレイ)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* リプレイのロード
* bool_t flg_txt_data : ゲーム・データがテキスト・モードか?
* long n : データ・スロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_replay( bool_t flg_txt_data, long n )
{
	FILE	*fp;
	ver_t	ver;
	bool_t	flg_txt = TRUE;

	if( get_flg_play_replay() )
		return TRUE;

	/* ゲーム・データのロード */

	if( !load_game_data( flg_txt_data, n ) )
		return FALSE;

	/* ファイルのオープン */

	fp = open_game_replay( 'r', n );
	if( fp == NULL )
		return FALSE;

	/* ヘッダの読み込み */

	set_flg_crypt_txt( TRUE );
	load_game_replay_head_ver_1( fp, &ver, flg_txt );
	set_flg_crypt_txt( flg_txt );

	/* バージョンのチェック */

	if( chk_ver_new( &ver,
			GAME_DATA_VER_MJR,
			GAME_DATA_VER_MNR,
			GAME_DATA_VER_PAT ) ){
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_A,
				ver.mjr, ver.mnr, ver.pat );
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_B );

		fclose( fp );
		return FALSE;
	}

	/* データの初期化 */

	reset_load_game_replay( n );

	/* データの読み込み */

	switch( ver.mjr ){
	case 1:
		if( !load_game_replay_ver_1( fp, &ver, flg_txt ) ){
			fclose( fp );
			return FALSE;
		}
		break;
	default:
		fclose( fp );

		print_lex_err( MSG_ERR_FILE_VER_A,
				ver.mjr, ver.mnr, ver.pat );
		print_lex_err( MSG_ERR_FILE_VER_B );

		exit_game( EXIT_FAILURE );
		return FALSE;
		break;
	}

	/* ファイルのクローズ */

	if( fclose( fp ) == EOF )
		return FALSE;

	set_flg_play_replay( TRUE );

	print_msg( FLG_NULL, MSG_LOAD_GAME_REPLAY_SUCCESS, n );

	return TRUE;
}

/***************************************************************
* リプレイのロード前の初期化
* long n : データ・スロット番号
***************************************************************/

void	reset_load_game_replay( long n )
{
	end_reg_replay( SAVE_N_AUTO );
	reset_replay( SAVE_N_AUTO );

	end_reg_replay( get_replay_save_n() );
	reset_replay( get_replay_save_n() );

	reset_replay_slot( REPLAY_SLOT_PLAY );
	bgn_reg_replay_play();

	g_replay_kind_cur = REPLAY_KIND_KEY;
}

/***************************************************************
* リプレイのヘッダのロード(バージョン 1)
* FILE *fp : ファイル
* ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_replay_head_ver_1( FILE *fp, ver_t *ver, bool_t flg_txt )
{
	const long	len_head = str_len_std( STR_GAME_REPLAY_HEAD );
	char	*s;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	ver->mjr = 0;
	ver->mnr = 0;
	ver->pat = 0;

	s = load_line( fp, TRUE );
	if( strncmp( s, STR_GAME_REPLAY_HEAD, len_head ) != 0 ){
		print_lex_err( MSG_S, MSG_ERR_LOAD_GAME_HEAD );
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

	s = load_line( fp, TRUE );

	reset_load_crypt( fp, flg_txt );

	return TRUE;
}

/***************************************************************
* リプレイのロード(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_replay_ver_1( FILE *fp, const ver_t *ver, bool_t flg_txt )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	while( 1 ){
		if( !load_game_replay_parse_ver_1( fp, ver, flg_txt ) )
			break;
	}

	return TRUE;
}

/***************************************************************
* リプレイのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : パースを続けるか?
***************************************************************/

bool_t	load_game_replay_parse_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	rc_token_t	t[MAX_TOKEN];
	rc_union_t	u[MAX_TOKEN];
	bool_t	flg_err_exit, flg_err;
	long	i, j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	flg_err_exit = TRUE;

	for( i = 0; i < MAX_TOKEN; i++ )
		t[i] = RC_TOKEN_EOF;

	for( i = 0; i < MAX_TOKEN; i++ ){
		t[i] = rc_lex( fp, &(u[i]), flg_err_exit );
		if( t[i] == RC_TOKEN_EOF )
			break;
		if( t[i] == '\n' )
			break;
		if( t[i] == RC_TOKEN_ADD_OP ){
			long	sign_n = +1;

			for( j = i + 1; j < MAX_TOKEN; j++ ){
				if( u[i].c == '-' )
					sign_n = -sign_n;

				t[i] = rc_lex( fp, &(u[i]), flg_err_exit );
				if( t[i] != RC_TOKEN_ADD_OP ){
					break;
				}
			}

			if( t[i] == RC_TOKEN_NUM ){
				u[i].n *= sign_n;
			}
		}
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
	} else if( (t[0] == RC_TOKEN_ID) ){
		/* bar, */

		if( !load_game_replay_id_ver_1(
				fp, ver, flg_txt,
				u[0].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_STR)
			&& (t[1] == ',') ){
		/* "baz", */

		if( !load_game_replay_str_ver_1(
				fp, ver, flg_txt,
				u[0].str ) ){
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
* リプレイのパース(識別子 : バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* char *id : 識別子
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_replay_id_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *id
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( id == NULL )
		return FALSE;

	if( strcmp( id, MSG_REPLAY_KIND_KEY ) == 0 ){
		g_replay_kind_cur = REPLAY_KIND_KEY;

		return TRUE;
	} else if( strcmp( id, MSG_REPLAY_KIND_GETS ) == 0 ){
		g_replay_kind_cur = REPLAY_KIND_GETS;

		return TRUE;
	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );

		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* リプレイのパース(文字列 : バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* char *str : 文字列
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_replay_str_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *str
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( str == NULL )
		return FALSE;

	set_replay_str_slot( g_replay_kind_cur, REPLAY_SLOT_PLAY, str );

	return TRUE;
}

/***************************************************************
* リプレイのセーブ
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_replay( void )
{
	bool_t	flg_success = FALSE;
	long	n;

	if( get_flg_play_replay() )
		return TRUE;

	n = SAVE_N_AUTO;
	if( save_game_replay_slot( n ) )
		flg_success = TRUE;

	n = get_replay_save_n();
	if( save_game_replay_slot( n ) )
		flg_success = TRUE;

	if( !flg_success )
		print_msg( FLG_NULL, MSG_CHK_REG_REPLAY_ERR );

	return flg_success;
}

/***************************************************************
* リプレイのセーブ(スロット指定あり)
* long n : データ・スロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_replay_slot( long n )
{
	bool_t	flg_success = FALSE;
	ver_t	ver;

	if( !chk_reg_replay( n ) )
		return FALSE;

	ver.mjr = GAME_DATA_VER_MJR;
	ver.mnr = GAME_DATA_VER_MNR;
	ver.pat = GAME_DATA_VER_PAT;

	switch( ver.mjr ){
	case 1:
		flg_success = save_game_replay_ver_1( &ver,  n );
		break;
	default:
		flg_success = FALSE;
		break;
	}

	if( flg_success && (n != SAVE_N_BUG_REPO) )
		print_msg( FLG_NULL, MSG_SAVE_GAME_REPLAY_SUCCESS, n );

	return flg_success;
}

/***************************************************************
* バグ・レポートのリプレイのセーブ
* return : エラーが無かったか?
***************************************************************/

bool_t	save_bug_repo_replay( void )
{
	bool_t	flg_success = TRUE;

	if( get_flg_play_replay() )
		return TRUE;

	if( !copy_file_bug_repo() )
		flg_success = FALSE;
	if( !save_game_replay_slot( SAVE_N_BUG_REPO ) )
		flg_success = FALSE;

	if( flg_success ){
		print_msg( FLG_NULL, MSG_REPLAY_BUG_REPO_1 );
		print_msg( FLG_NULL, MSG_REPLAY_BUG_REPO_2 );
		print_msg( FLG_NULL, "[%s]", dir_name_bug_repo );
		print_msg( FLG_NULL, "Email : %s", STR_E_MAIL );
	} else {
		print_msg( FLG_NULL, MSG_CHK_REG_REPLAY_ERR );
	}

	return flg_success;
}

/***************************************************************
* バグ・レポートのゲーム・データ・ファイルのコピー
* return : エラーが無かったか?
***************************************************************/

bool_t	copy_file_bug_repo( void )
{
	char	path_src[FILE_NAME_MAX_LEN + 1];
	char	path_dst[FILE_NAME_MAX_LEN + 1];
	long	n;

	n = get_replay_save_n();
	if( n == SAVE_N_AUTO )
		return FALSE;

	/* txt */

	get_path_game_data_txt( path_src, n );
	get_path_bug_repo_txt( path_dst );
	if( !copy_file( path_src, path_dst ) )
		return FALSE;

	/* bin */

	get_path_game_data_bin( path_src, n );
	get_path_bug_repo_bin( path_dst );
	if( !copy_file( path_src, path_dst ) )
		return FALSE;

	/* cnf */

	get_path_game_data_cnf( path_src, n );
	get_path_bug_repo_cnf( path_dst );
	if( !copy_file( path_src, path_dst ) )
		return FALSE;

	/* rep */
	/* empty */

	return TRUE;
}

/***************************************************************
* リプレイのセーブ(バージョン 1)
* const ver_t *ver : ファイルのバージョン
* long n : データ・スロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_replay_ver_1( const ver_t *ver, long n )
{
	FILE	*fp;
	time_t	save_time_buf;
	struct tm	*save_time;
	bool_t	flg_txt = TRUE;

	if( ver == NULL )
		return FALSE;

	fp = open_game_replay( 'w', n );
	if( fp == NULL )
		return FALSE;

	/* header */

	fprintf( fp, "%s%ld.%ld.%ld\n",
			STR_GAME_REPLAY_HEAD,
			ver->mjr, ver->mnr, ver->pat );

	time( &save_time_buf );
	save_time = localtime( &save_time_buf );
	if( save_time == NULL )
		return FALSE;
	fprintf( fp, "%04ld: %04d/%02d/%02d  %02d:%02d:%02d\n",
			g_game_data_save_n,
			save_time->tm_year + 1900,
			save_time->tm_mon + 1,
			save_time->tm_mday,
			save_time->tm_hour,
			save_time->tm_min,
			save_time->tm_sec );

	reset_save_crypt( fp, flg_txt );
	reset_save_crypt_tab();

	/* data */

	if( !save_game_replay_contents( fp, ver, n ) ){
		fclose( fp );
		return FALSE;
	}

	/* footer */

	save_crypt_str( fp, "\n" );
	save_crypt_tab( fp, "// end\n" );

	/* end */

	if( fclose( fp ) == EOF )
		return FALSE;

	return TRUE;
}

/***************************************************************
* リプレイの内容のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* long n : データ・スロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_replay_contents(
	FILE *fp, const ver_t *ver, long n
)
{
	replay_t	*p;
	replay_kind_t	pre_kind;
	char	*msg;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	pre_kind = REPLAY_KIND_MAX_N;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// replay\n" );

	save_crypt_tab( fp, "\n" );
	for( p = get_replay_head( n ); p != NULL; p = p->next ){
		if( p->kind == pre_kind )
			msg = NULL;
		else
			msg = get_msg_replay_kind( p );

		if( (msg != NULL) && (msg[0] != '\0') )
			save_crypt_tab( fp, "%s\n", msg );

		save_crypt_tab( fp, "\t\"%s\",\n",
				cv_esc_quote_str(
				cv_esc_ctrl_str(
				p->buf ) ) );

		pre_kind = p->kind;
	}

	return TRUE;
}
/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_gf_replay_c( void )
{
}
