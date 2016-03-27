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
* $Id: gfile.c,v 1.218 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ファイル入出力
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************/

#include	"gfile-tab.h"

/***************************************************************
* ファイル処理の初期化
***************************************************************/

void	init_game_file( void )
{
	const char	*home, *s;

	g_rc_lex_num_mode = 0;

	g_game_data_save_n = 0;
	g_randm_seed_save = get_randm_seed();

	/* ホーム・ディレクトリを得る */

	home = get_home_dir();

	if( !chk_exist_dir( home ) ){
		print_err( MSG_ERR_HOME_DIR, home );
		exit_game( EXIT_FAILURE );
	}

	/* ゲーム・ディレクトリを得る */

	s = init_dir_game( home, STR_DIR_NAME_GAME, FALSE );
	if( s != NULL )
		str_nz_cpy( dir_name_game, s, FILE_NAME_MAX_LEN );

	s = init_dir_game( home, STR_DIR_NAME_GAME_USR, FALSE );
	if( s != NULL )
		str_nz_cpy( dir_name_usr, s, FILE_NAME_MAX_LEN );

	init_dir_game( home, STR_DIR_NAME_GAME_BAK, FALSE );
	init_dir_game( home, STR_DIR_NAME_GAME_OUT_MAP, FALSE );
	init_dir_game( home, STR_DIR_NAME_GAME_DATA_SAVE, FALSE );

	init_dir_game( home, STR_DIR_NAME_GAME_DATA_TXT, FALSE );
	if( s != NULL )
		str_nz_cpy( dir_name_game_data_txt, s, FILE_NAME_MAX_LEN );
	init_dir_game( home, STR_DIR_NAME_GAME_DATA_BIN, FALSE );
	if( s != NULL )
		str_nz_cpy( dir_name_game_data_bin, s, FILE_NAME_MAX_LEN );
	init_dir_game( home, STR_DIR_NAME_GAME_DATA_CNF, FALSE );
	if( s != NULL )
		str_nz_cpy( dir_name_game_data_cnf, s, FILE_NAME_MAX_LEN );
	init_dir_game( home, STR_DIR_NAME_GAME_DATA_REP, FALSE );
	if( s != NULL )
		str_nz_cpy( dir_name_game_data_rep, s, FILE_NAME_MAX_LEN );
	init_dir_game( home, STR_DIR_NAME_BUG_REPO, FALSE );
	if( s != NULL )
		str_nz_cpy( dir_name_bug_repo, s, FILE_NAME_MAX_LEN );

	str_nz_cpy( path_name_game_conf,
			cat_path( dir_name_usr, STR_FILE_NAME_GAME_CONF ),
			FILE_NAME_MAX_LEN );

	str_nz_cpy( path_name_town_ptn,
			cat_path( dir_name_usr, STR_FILE_NAME_TOWN_PTN ),
			FILE_NAME_MAX_LEN );

	str_nz_cpy( path_name_crsr_ptn,
			cat_path( dir_name_usr, STR_FILE_NAME_CRSR_PTN ),
			FILE_NAME_MAX_LEN );

	if( !chk_exist_file( path_name_game_conf ) )
		about_game( TRUE );
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_game_file( void )
{
}

/***************************************************************
* ディレクトリの初期化
* char *home : ホーム・ディレクトリ
* char *dir : ディレクトリ
* bool_t flg_GPL : 著作権を表示するか?
* return : ディレクトリのフルパス(エラーならNULL)
***************************************************************/

char	*init_dir_game( const char *home, const char *dir, bool_t flg_GPL )
{
	char	*name;

	/* ゲーム・ディレクトリを得る */
	name = cat_path( home, dir );

	if( chk_exist_dir( name ) )
		return name;

	/* 無ければ GPL を表示 */
	if( flg_GPL )
		about_game( TRUE );

	/* 無ければ作る */
	if( make_dir( name ) )
		return name;

	return NULL;
}

/***************************************************************
* ホーム・ディレクトリを探す
* return : ホーム・ディレクトリ
***************************************************************/

const char	*get_home_dir( void )
{
	const char	*home;

	home = call_get_home_dir();
	if( home != NULL )
		return home;

	home = getenv( STR_ENV_HOME );

	/* 無ければカレントディレクトリ */
	if( (home == NULL) || (home[0] == '\0') )
		home = STR_DIR_NAME_CUR;

	return home;
}

/***************************************************************
* ゲーム・データ・ファイルのテキストのパスを返す
* char *path : パスを返す
* long n : データ・スロット番号
***************************************************************/

void	get_path_game_data_txt( char *path, long n )
{
	if( n == SAVE_N_BUG_REPO ){
		get_path_bug_repo_txt( path );
		return;
	}

	sn_printf( path, FILE_NAME_MAX_LEN,
			"%s/%s%02ld%s",
			dir_name_game_data_txt,
			STR_FILE_NAME_GAME_DATA_TXT,
			n,
			STR_EXT_NAME_GAME_DATA_TXT );
}

/***************************************************************
* ゲーム・データ・ファイルのバイナリのパスを返す
* char *path : パスを返す
* long n : データ・スロット番号
***************************************************************/

void	get_path_game_data_bin( char *path, long n )
{
	if( n == SAVE_N_BUG_REPO ){
		get_path_bug_repo_bin( path );
		return;
	}

	sn_printf( path, FILE_NAME_MAX_LEN,
			"%s/%s%02ld%s",
			dir_name_game_data_bin,
			STR_FILE_NAME_GAME_DATA_BIN,
			n,
			STR_EXT_NAME_GAME_DATA_BIN );
}

/***************************************************************
* ゲーム・データ・ファイルの設定のパスを返す
* char *path : パスを返す
* long n : データ・スロット番号
***************************************************************/

void	get_path_game_data_cnf( char *path, long n )
{
	if( n == SAVE_N_BUG_REPO ){
		get_path_bug_repo_cnf( path );
		return;
	}

	sn_printf( path, FILE_NAME_MAX_LEN,
			"%s/%s%02ld%s",
			dir_name_game_data_cnf,
			STR_FILE_NAME_GAME_DATA_CNF,
			n,
			STR_EXT_NAME_GAME_DATA_CNF );
}

/***************************************************************
* ゲーム・データ・ファイルのリプレイのパスを返す
* char *path : パスを返す
* long n : データ・スロット番号
***************************************************************/

void	get_path_game_data_rep( char *path, long n )
{
	if( n == SAVE_N_BUG_REPO ){
		get_path_bug_repo_rep( path );
		return;
	}

	sn_printf( path, FILE_NAME_MAX_LEN,
			"%s/%s%02ld%s",
			dir_name_game_data_rep,
			STR_FILE_NAME_GAME_DATA_REP,
			n,
			STR_EXT_NAME_GAME_DATA_REP );
}

/***************************************************************
* バグ・レポートのテキストのパスを返す
* char *path : パスを返す
***************************************************************/

void	get_path_bug_repo_txt( char *path )
{
	sn_printf( path, FILE_NAME_MAX_LEN,
			"%s/%s%s",
			dir_name_bug_repo,
			STR_FILE_NAME_BUG_REPO_TXT,
			STR_EXT_NAME_BUG_REPO_TXT );
}

/***************************************************************
* バグ・レポートのバイナリのパスを返す
* char *path : パスを返す
***************************************************************/

void	get_path_bug_repo_bin( char *path )
{
	sn_printf( path, FILE_NAME_MAX_LEN,
			"%s/%s%s",
			dir_name_bug_repo,
			STR_FILE_NAME_BUG_REPO_BIN,
			STR_EXT_NAME_BUG_REPO_BIN );
}

/***************************************************************
* バグ・レポートの設定のパスを返す
* char *path : パスを返す
***************************************************************/

void	get_path_bug_repo_cnf( char *path )
{
	sn_printf( path, FILE_NAME_MAX_LEN,
			"%s/%s%s",
			dir_name_bug_repo,
			STR_FILE_NAME_BUG_REPO_CNF,
			STR_EXT_NAME_BUG_REPO_CNF );
}

/***************************************************************
* バグ・レポートのリプレイのパスを返す
* char *path : パスを返す
***************************************************************/

void	get_path_bug_repo_rep( char *path )
{
	sn_printf( path, FILE_NAME_MAX_LEN,
			"%s/%s%s",
			dir_name_bug_repo,
			STR_FILE_NAME_BUG_REPO_REP,
			STR_EXT_NAME_BUG_REPO_REP );
}

/***************************************************************
* ゲーム・データ・ファイルのオープン
* char type : 'r' = リード , 'w' = ライト
* long n : データ・スロット番号
* bool_t flg_txt : テキスト・モードか?
* return : ファイル・ポインタ
***************************************************************/

FILE	*open_game_data( char type, long n, bool_t flg_txt )
{
	char	path[FILE_NAME_MAX_LEN + 1];
	FILE	*fp;

	if( flg_txt ){
		get_path_game_data_txt( path, n );

		if( type == 'r' )
			fp = fopen( path, "r" );
		else if( type == 'w' )
			fp = fopen( path, "w" );
		else
			fp = NULL;
	} else {
		get_path_game_data_bin( path, n );

		if( type == 'r' )
			fp = fopen( path, "rb" );
		else if( type == 'w' )
			fp = fopen( path, "wb" );
		else
			fp = NULL;
	}

	reset_load_save( path, flg_txt );

	return fp;
}

/***************************************************************
* ゲーム設定・ファイルのオープン
* char type : 'r' = リード , 'w' = ライト
* long n : データ・スロット番号
* return : ファイル・ポインタ
***************************************************************/

FILE	*open_game_data_cnf( char type, long n )
{
	char	path[FILE_NAME_MAX_LEN + 1];
	FILE	*fp;

	get_path_game_data_cnf( path, n );

	if( type == 'r' )
		fp = fopen( path, "r" );
	else if( type == 'w' )
		fp = fopen( path, "w" );
	else
		fp = NULL;

	reset_load_save( path, TRUE );

	return fp;
}

/***************************************************************
* リプレイ・ファイルのオープン
* char type : 'r' = リード , 'w' = ライト
* long n : データ・スロット番号
* return : ファイル・ポインタ
***************************************************************/

FILE	*open_game_replay( char type, long n )
{
	char	path[FILE_NAME_MAX_LEN + 1];
	FILE	*fp;

	get_path_game_data_rep( path, n );

	if( type == 'r' )
		fp = fopen( path, "r" );
	else if( type == 'w' )
		fp = fopen( path, "w" );
	else
		fp = NULL;

	reset_load_save( path, TRUE );

	return fp;
}

/***************************************************************
* リプレイ・ファイルの削除
* long n : データ・スロット番号
***************************************************************/

void	remove_replay_file( long n )
{
	FILE	*fp;

	fp = open_game_replay( 'w', n );

	if( fp != NULL )
		fclose( fp );
}

/***************************************************************
* ファイルから 1 文字読み込む
* FILE *fp : ファイル
* bool_t flg_chk_eof : ファイルの終了をチェックするか?
* return : 読み込んだ文字
***************************************************************/

long	load_char( FILE *fp, bool_t flg_chk_eof )
{
	return rc_lex_getc( fp, flg_chk_eof, TRUE );
}

/***************************************************************
* ファイルから 1 行読み込む(空き行とコメントを飛ばす)
* FILE *fp : ファイル
* bool_t flg_chk_eof : ファイルの終了をチェックするか?
* return : 読み込んだ行
***************************************************************/

char	*load_line_skip_spc( FILE *fp, bool_t flg_chk_eof )
{
	char	*s;

	while( !feof( fp ) ){
		s = load_line( fp, flg_chk_eof );

		if( s[0] == '#' )
			continue;
		if( s[strspn( s, " \t\n\r" )] == '\0' )
			continue;

		return s;
	}

	if( flg_chk_eof ){
		fclose( fp );
		print_err( MSG_S, MSG_ERR_LOAD_EOF );
		exit_game( EXIT_FAILURE );
	}

	return NULL;
}

/***************************************************************
* ファイルから 1 行読み込む
* FILE *fp : ファイル
* bool_t flg_chk_eof : ファイルの終了をチェックするか?
* return : 読み込んだ行
***************************************************************/

char	*load_line( FILE *fp, bool_t flg_chk_eof )
{
	static char	buf[BUF_LINE_LEN + 1];

	if( !feof( fp ) ){
		load_crypt_str( fp, buf, BUF_LINE_LEN );

		return buf;
	}

	if( flg_chk_eof ){
		fclose( fp );
		print_err( MSG_S, MSG_ERR_LOAD_EOF );
		exit_game( EXIT_FAILURE );
	}

	return NULL;
}

/***************************************************************
* 字句解析部のファイル名を設定
* char *name : ファイル名の設定元
* return : 設定されたファイル名
***************************************************************/

char	*set_rc_lex_file_name( char *name )
{
	str_nz_cpy( g_rc_lex_file_name, name, FILE_NAME_MAX_LEN );

	return g_rc_lex_file_name;
}

/***************************************************************
* 字句解析部のファイル名を返す
* return : ファイル名
***************************************************************/

char	*get_rc_lex_file_name( void )
{
	return g_rc_lex_file_name;
}

/***************************************************************
* 字句解析部の現在の行番号を初期化
* return : 行番号
***************************************************************/

long	clr_rc_lex_line( void )
{
	g_rc_lex_line = 1;

	return g_rc_lex_line;
}

/***************************************************************
* 字句解析部の現在の行番号をインクリメントする
* return : 行番号
***************************************************************/

long	inc_rc_lex_line( void )
{
	g_rc_lex_line++;

	return g_rc_lex_line;
}

/***************************************************************
* 字句解析部の現在の行番号をデクリメントする
* return : 行番号
***************************************************************/

long	dec_rc_lex_line( void )
{
	g_rc_lex_line--;

	return g_rc_lex_line;
}

/***************************************************************
* 字句解析部の現在の行番号を返す
* return : 行番号
***************************************************************/

long	get_rc_lex_line( void )
{
	return g_rc_lex_line;
}

/***************************************************************
* 字句解析部のエラー状態を設定
* bool_t flg : 設定するエラー状態
* return : エラー状態
***************************************************************/

bool_t	set_rc_lex_err( bool_t flg )
{
	g_flg_rc_lex_err = flg;

	return g_flg_rc_lex_err;
}

/***************************************************************
* 字句解析部のエラー状態を返す
* return : エラー状態
***************************************************************/

bool_t	get_rc_lex_err( void )
{
	return g_flg_rc_lex_err;
}

/***************************************************************
* ファイルの字句解析をする
* FILE *fp : ファイル
* rc_union_t *u : 字句解析のスタック
* bool_t flg_err_exit : エラーで終了するか?
* return : トークン
***************************************************************/

rc_token_t	rc_lex( FILE *fp, rc_union_t *u, bool_t flg_err_exit )
{
	static char	buf[TOKEN_MAX_LEN + 1];
	long	c;
	long	n;

	if( g_un_token != RC_TOKEN_NULL ){
		rc_token_t	pre_t;

		pre_t = g_un_token;
		g_un_token = RC_TOKEN_NULL;
		*u = g_un_union;

		return pre_t;
	}

	while( 1 ){
		c = rc_lex_getc( fp, FALSE, flg_err_exit );

		switch( c ){
		case EOF:
			return RC_TOKEN_EOF;
		case ' ':
		case '\t':
			continue;
		case '\n':
		case '\r':
			return( (rc_token_t)'\n' );
		case '/':
			c = rc_lex_getc( fp, FALSE, flg_err_exit );
			if( c != '/' ){
				rc_lex_ungetc( fp, c );
				c = '/';
				break;
			}
			/* break; */
		case '#':
			while( 1 ){
				load_crypt_str( fp, buf, TOKEN_MAX_LEN );
				if( str_len_std( buf ) != TOKEN_MAX_LEN )
					break;
				if( buf[TOKEN_MAX_LEN - 1] == '\n' )
					break;
			}
			continue;
		case '\'':
			rc_lex_char( fp, u, flg_err_exit );

			c = rc_lex_getc( fp, TRUE, flg_err_exit );
			if( c != '\'' ){
				rc_lex_ungetc( fp, c );
				print_lex_wrn( MSG_S, MSG_ERR_RC_LEX_CHAR );
			}
			return RC_TOKEN_CHAR;
		case '\"':
			return( rc_lex_str( fp, u, flg_err_exit ) );
		case '0':
			if( g_rc_lex_num_mode == 8 ){
				rc_lex_ungetc( fp, c );
				n = rc_lex_oct( fp,
						TOKEN_MAX_LEN,
						flg_err_exit );
			} else if( g_rc_lex_num_mode == 10 ){
				rc_lex_ungetc( fp, c );
				n = rc_lex_dec( fp,
						TOKEN_MAX_LEN,
						flg_err_exit );
			} else if( g_rc_lex_num_mode == 16 ){
				rc_lex_ungetc( fp, c );
				n = rc_lex_hex_dec( fp,
						TOKEN_MAX_LEN,
						flg_err_exit );
			} else {
				c = rc_lex_getc( fp, TRUE, flg_err_exit );

				if( ('0' <= c) && (c <= '7') ){
					rc_lex_ungetc( fp, c );
					n = rc_lex_oct( fp,
							TOKEN_MAX_LEN,
							flg_err_exit );
				} else if( (c == 'x') || (c == 'X') ){
					n = rc_lex_hex_dec( fp,
							TOKEN_MAX_LEN,
							flg_err_exit );
				} else {
					rc_lex_ungetc( fp, c );
					n = 0;
				}
			}

			if( u != NULL )
				u->n = n;
			return RC_TOKEN_NUM;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if( g_rc_lex_num_mode == 8 ){
				rc_lex_ungetc( fp, c );
				n = rc_lex_oct( fp,
						TOKEN_MAX_LEN,
						flg_err_exit );
			} else if( g_rc_lex_num_mode == 16 ){
				rc_lex_ungetc( fp, c );
				n = rc_lex_hex_dec( fp,
						TOKEN_MAX_LEN,
						flg_err_exit );
			} else {
				rc_lex_ungetc( fp, c );
				n = rc_lex_dec( fp,
						TOKEN_MAX_LEN,
						flg_err_exit );
			}

			if( u != NULL )
				u->n = n;
			return RC_TOKEN_NUM;
		case '+':
		case '-':
			if( u != NULL )
				u->c = c;
			return RC_TOKEN_ADD_OP;
		case '=':
			if( u != NULL )
				u->c = c;
			return RC_TOKEN_EQ_OP;
		case '{':
		case '}':
		case ',':
			if( u != NULL )
				u->c = c;
			return( (rc_token_t)c );
		default:
			if( isalpha( c ) || (c == '_') ){
				rc_lex_ungetc( fp, c );
				rc_lex_id( fp, u, flg_err_exit );
				return RC_TOKEN_ID;
			} else {
				break;
			}
		}

		break;
	}

	print_lex_err( MSG_ERR_RC_LEX, (char)c, (long)c );
	if( flg_err_exit )
		exit_game( EXIT_FAILURE );

	return RC_TOKEN_EOF;
}

/***************************************************************
* 字句解析を取り消して 1 トークン戻す
* FILE *fp : ファイル
* rc_union_t *u : 字句解析のスタック
* rc_token_t t : トークン
***************************************************************/

void	rc_unlex( FILE *fp, const rc_union_t *u, rc_token_t t )
{
	g_un_token = t;
	g_un_union = *u;
}

/***************************************************************
* ファイルを 1 文字、字句解析する
* FILE *fp : ファイル
* rc_union_t *u : 字句解析のスタック
* bool_t flg_err_exit : エラーで終了するか?
* return : トークン
***************************************************************/

rc_token_t	rc_lex_char( FILE *fp, rc_union_t *u, bool_t flg_err_exit )
{
	long	c, cc;

	cc = '\0';

	c = rc_lex_getc( fp, TRUE, flg_err_exit );
	if( c == EOF )
		return RC_TOKEN_EOF;

	if( c == '\\' ){
		c = rc_lex_getc( fp, TRUE, flg_err_exit );
		if( c == EOF )
			return RC_TOKEN_EOF;

		switch( c ){
		case '\\':
			cc = '\\';
			break;
		case '0':
			c = rc_lex_getc( fp, TRUE, flg_err_exit );

			if( (c == 'x') || (c == 'X') ){
				cc = rc_lex_hex_dec( fp, 4, flg_err_exit );
			} else {
				rc_lex_ungetc( fp, c );
				cc = rc_lex_oct( fp, 3, flg_err_exit );
			}
			break;
		case 'x':
			cc = rc_lex_hex_dec( fp, 2, flg_err_exit );
			break;
		case 't':
			cc = '\t';
			break;
		case 'r':
			cc = '\r';
			break;
		case 'n':
			cc = '\n';
			break;
		case '\'':
			cc = '\'';
			break;
		case '\"':
			cc = '\"';
			break;
		default:
			cc = c;
			break;
		}
	} else if( c == '^' ){
		c = rc_lex_getc( fp, TRUE, flg_err_exit );
		if( c == EOF )
			return RC_TOKEN_EOF;

		cc = toupper( c ) - '@';
	} else if( c == '\'' ){
		/* 文字定数が空の時 */
		rc_lex_ungetc( fp, c );
		cc = ' ';
	} else {
		cc = c;
	}

	if( u != NULL )
		u->c = cc;
	return RC_TOKEN_CHAR;
}

/***************************************************************
* ファイルの文字列を字句解析する
* FILE *fp : ファイル
* rc_union_t *u : 字句解析のスタック
* bool_t flg_err_exit : エラーで終了するか?
* return : トークン
***************************************************************/

rc_token_t	rc_lex_str( FILE *fp, rc_union_t *u, bool_t flg_err_exit )
{
	rc_union_t	uu;
	long	c;
	long	i;

	for( i = 0; i < TOKEN_MAX_LEN; i++ ){
		rc_token_t	token;

		c = rc_lex_getc( fp, TRUE, flg_err_exit );
		if( c == '\"' )
			break;
		else
			rc_lex_ungetc( fp, c );

		token = rc_lex_char( fp, &uu, flg_err_exit );
		if( token == RC_TOKEN_EOF )
			return RC_TOKEN_EOF;

		if( u != NULL )
		  u->str[i] = (char)(uu.c);
	}

	if( u != NULL )
		u->str[i] = '\0';

	return RC_TOKEN_STR;
}

/***************************************************************
* ファイルの 8 進数を字句解析する
* FILE *fp : ファイル
* long len : 最大文字数
* bool_t flg_err_exit : エラーで終了するか?
* return : 数値
***************************************************************/

long	rc_lex_oct( FILE *fp, long len, bool_t flg_err_exit )
{
	return rc_lex_digit( fp, 8, len, flg_err_exit );
}

/***************************************************************
* ファイルの 10 進数を字句解析する
* FILE *fp : ファイル
* long len : 最大文字数
* bool_t flg_err_exit : エラーで終了するか?
* return : 数値
***************************************************************/

long	rc_lex_dec( FILE *fp, long len, bool_t flg_err_exit )
{
	return rc_lex_digit( fp, 10, len, flg_err_exit );
}

/***************************************************************
* ファイルの 16 進数を字句解析する
* FILE *fp : ファイル
* long len : 最大文字数
* bool_t flg_err_exit : エラーで終了するか?
* return : 数値
***************************************************************/

long	rc_lex_hex_dec( FILE *fp, long len, bool_t flg_err_exit )
{
	return rc_lex_digit( fp, 16, len, flg_err_exit );
}

/***************************************************************
* ファイルの n 進数を字句解析する
* FILE *fp : ファイル
* long base : 基数
* long len : 最大文字数
* bool_t flg_err_exit : エラーで終了するか?
* return : 数値
***************************************************************/

long	rc_lex_digit( FILE *fp, long base, long len, bool_t flg_err_exit )
{
	long	ret, n;
	long	c;
	long	i;

	ret = 0;
	n = 0;
	c = rc_lex_getc( fp, FALSE, flg_err_exit );

	for( i = 0; i < len; i++ ){
		if( ('0' <= c) && (c <= '9') ){
			n = c - '0';
		} else if( ('a' <= c) && (c <= 'z') ){
			n = c - 'a' + 10;
		} else if( ('A' <= c) && (c <= 'Z') ){
			n = c - 'A' + 10;
		} else {
			break;
		}

		if( n >= base )
			break;

		ret *= base;
		ret += n;

		c = rc_lex_getc( fp, FALSE, flg_err_exit );
	}

	rc_lex_ungetc( fp, c );

	return ret;
}

/***************************************************************
* ファイルの識別子を字句解析する
* FILE *fp : ファイル
* rc_union_t *u : 字句解析のスタック
* bool_t flg_err_exit : エラーで終了するか?
***************************************************************/

void	rc_lex_id( FILE *fp, rc_union_t *u, bool_t flg_err_exit )
{
	long	c;
	long	i;

	i = 0;

	while( 1 ){
		c = rc_lex_getc( fp, FALSE, flg_err_exit );

		if( isalpha( c ) || (c == '_') || isdigit( c ) ){
			if( (u != NULL) && (i < TOKEN_MAX_LEN) ){
				u->str[i] = (char)c;
				i++;
			}
		} else {
			rc_lex_ungetc( fp, c );
			break;
		}
	}

	u->str[i] = '\0';
}

/***************************************************************
* ファイルから 1 文字読み込む
* FILE *fp : ファイル
* bool_t flg_chk_eof : ファイルの終わりをチェックするか?
* bool_t flg_err_exit : エラーで終了するか?
* return : 読み込んだ文字
***************************************************************/

long	rc_lex_getc( FILE *fp, bool_t flg_chk_eof, bool_t flg_err_exit )
{
	if( !feof( fp ) )
		return load_crypt_c( fp );

	if( flg_chk_eof ){
		fclose( fp );
		print_lex_err( MSG_S, MSG_ERR_LOAD_EOF );

		if( flg_err_exit )
			exit_game( EXIT_FAILURE );
	}

	return EOF;
}

/***************************************************************
* 字句解析を取り消して 1 文字戻す
* FILE *fp : ファイル
* long c : 戻す文字
***************************************************************/

void	rc_lex_ungetc( FILE *fp, long c )
{
	if( c == '\n' )
		dec_rc_lex_line();

	un_load_crypt_c( fp, c );
}

/***************************************************************
* バッカップ・ファイルの名前を付け変える
* char *fname : ファイル名
* return : 付け変えたか?
***************************************************************/

bool_t	rename_back_up_file( char *fname )
{
	long	i;
	long	path_len;
	char	str_n[15 + 1];
	static char	bak_fname[FILE_NAME_MAX_LEN + 1];

	if( !chk_exist_file( fname ) )
		return FALSE;

	path_len = strrchr( fname, '/' ) - fname + 1;
	if( path_len > FILE_NAME_MAX_LEN )
		path_len = FILE_NAME_MAX_LEN;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		sn_printf( str_n, 15, STR_EXT_NAME_BAK_1, i );

		str_nz_cpy( bak_fname, fname, FILE_NAME_MAX_LEN );
		bak_fname[FILE_NAME_MAX_LEN] = '\0';
		str_max_n_cat( bak_fname, str_n, FILE_NAME_MAX_LEN );
		str_max_n_cat( bak_fname, STR_EXT_NAME_BAK_2,
				FILE_NAME_MAX_LEN );

		if( chk_exist_file( bak_fname ) )
			continue;

		if( rename( fname, bak_fname ) == 0 ){
			print_wrn( MSG_WRN_RENAME, fname, bak_fname );
			return TRUE;
		}
	}

	return FALSE;
}

/***************************************************************
* インデックスからアンカーの方向に変換
* long idx : インデックス
* return : アンカーの方向
***************************************************************/

square_dir_t	trans_idx_to_square_dir( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_square_dir_trans_tab )
			/ sizeof( g_square_dir_trans_tab[0] );

	if( idx < 0 )
		return SQUARE_DIR_NORTH;
	if( idx >= max_idx )
		return SQUARE_DIR_NORTH;

	return( g_square_dir_trans_tab[idx] );
}

/***************************************************************
* アンカーの方向からインデックスに変換
* chr_kind_t k : アンカーの方向
* return : インデックス
***************************************************************/

long	trans_square_dir_to_idx( square_dir_t dir )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_square_dir_trans_tab )
			/ sizeof( g_square_dir_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_square_dir_trans_tab[i] == dir )
			return i;

	return 0;
}

/***************************************************************
* インデックスからキャラクターの種類に変換
* long idx : インデックス
* return : キャラクターの種類
***************************************************************/

chr_kind_t	trans_idx_to_chr_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_chr_trans_tab )
			/ sizeof( g_chr_trans_tab[0] );

	if( idx < 0 )
		return CHR_KIND_NULL;
	if( idx >= max_idx )
		return CHR_KIND_NULL;

	return( g_chr_trans_tab[idx] );
}

/***************************************************************
* キャラクターの種類からインデックスに変換
* chr_kind_t k : キャラクターの種類
* return : インデックス
***************************************************************/

long	trans_chr_kind_to_idx( chr_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_chr_trans_tab )
			/ sizeof( g_chr_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_chr_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからメンバーの配置に変換
* long idx : インデックス
* return : メンバーの配置
***************************************************************/

position_kind_t	trans_idx_to_position_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_position_kind_trans_tab )
			/ sizeof( g_position_kind_trans_tab[0] );

	if( idx < 0 )
		return POSITION_KIND_FORWARD;
	if( idx >= max_idx )
		return POSITION_KIND_FORWARD;

	return( g_position_kind_trans_tab[idx] );
}

/***************************************************************
* メンバーの配置からインデックスに変換
* position_kind_t k : メンバーの配置の種類
* return : インデックス
***************************************************************/

long	trans_position_kind_to_idx( position_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_position_kind_trans_tab )
			/ sizeof( g_position_kind_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_position_kind_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからメイン種族に変換
* long idx : インデックス
* return : メイン種族
***************************************************************/

main_race_t	trans_idx_to_main_race_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_main_race_trans_tab )
			/ sizeof( g_main_race_trans_tab[0] );

	if( idx < 0 )
		return MAIN_RACE_HUMAN;
	if( idx >= max_idx )
		return MAIN_RACE_HUMAN;

	return( g_main_race_trans_tab[idx] );
}

/***************************************************************
* メイン種族からインデックスに変換
* main_race_t k : メイン種族
* return : インデックス
***************************************************************/

long	trans_main_race_kind_to_idx( main_race_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_main_race_trans_tab )
			/ sizeof( g_main_race_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_main_race_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからサブ種族に変換
* long idx : インデックス
* return : サブ種族
***************************************************************/

sub_race_t	trans_idx_to_sub_race_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_sub_race_trans_tab )
			/ sizeof( g_sub_race_trans_tab[0] );

	if( idx < 0 )
		return SUB_RACE_NULL;
	if( idx >= max_idx )
		return SUB_RACE_NULL;

	return( g_sub_race_trans_tab[idx] );
}

/***************************************************************
* サブ種族からインデックスに変換
* sub_race_t k : サブ種族
* return : インデックス
***************************************************************/

long	trans_sub_race_kind_to_idx( sub_race_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_sub_race_trans_tab )
			/ sizeof( g_sub_race_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_sub_race_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから性別に変換
* long idx : インデックス
* return : 性別
***************************************************************/

sex_t	trans_idx_to_sex_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_sex_trans_tab )
			/ sizeof( g_sex_trans_tab[0] );

	if( idx < 0 )
		return SEX_NULL;
	if( idx >= max_idx )
		return SEX_NULL;

	return( g_sex_trans_tab[idx] );
}

/***************************************************************
* 性別からインデックスに変換
* sex_t k : 性別
* return : インデックス
***************************************************************/

long	trans_sex_kind_to_idx( sex_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_sex_trans_tab )
			/ sizeof( g_sex_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_sex_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから能力値への変換テーブルの要素数を返す
* return : 要素数
***************************************************************/

long	get_abl_kind_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_abl_trans_tab );
	max_idx /= sizeof( g_abl_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* インデックスから能力値に変換
* long idx : インデックス
* return : 能力値
***************************************************************/

abl_kind_t	trans_idx_to_abl_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_abl_trans_tab )
			/ sizeof( g_abl_trans_tab[0] );

	if( idx < 0 )
		return( (abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_NULL) );
	if( idx >= max_idx )
		return( (abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_NULL) );

	return( g_abl_trans_tab[idx] );
}

/***************************************************************
* 能力値からインデックスに変換
* abl_kind_t k : 能力値
* return : インデックス
***************************************************************/

long	trans_abl_kind_to_idx( abl_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_abl_trans_tab )
			/ sizeof( g_abl_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_abl_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから歩き方の種類に変換
* long idx : インデックス
* return : 歩き方の種類
***************************************************************/

move_kind_t	trans_idx_to_move_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_move_trans_tab )
			/ sizeof( g_move_trans_tab[0] );

	if( idx < 0 )
		return MOVE_KIND_NULL;
	if( idx >= max_idx )
		return MOVE_KIND_NULL;

	return( g_move_trans_tab[idx] );
}

/***************************************************************
* 歩き方の種類からインデックスに変換
* move_kind_t k : 歩き方の種類
* return : インデックス
***************************************************************/

long	trans_move_kind_to_idx( move_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_move_trans_tab )
			/ sizeof( g_move_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_move_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから歩き方データの種類への変換テーブルの要素数を返す
* return : 要素数
***************************************************************/

long	get_move_ls_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_move_ls_trans_tab );
	max_idx /= sizeof( g_move_ls_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* インデックスから歩き方データの種類に変換
* long idx : インデックス
* return : 歩き方データの種類
***************************************************************/

move_ls_kind_t	trans_idx_to_move_ls_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_move_ls_trans_tab )
			/ sizeof( g_move_ls_trans_tab[0] );

	if( idx < 0 )
		return MOVE_LS_KIND_FIND;
	if( idx >= max_idx )
		return MOVE_LS_KIND_FIND;

	return( g_move_ls_trans_tab[idx] );
}

/***************************************************************
* 歩き方データの種類からインデックスに変換
* move_ls_kind_t k : 歩き方データの種類
* return : インデックス
***************************************************************/

long	trans_move_ls_kind_to_idx( move_ls_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_move_ls_trans_tab )
			/ sizeof( g_move_ls_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_move_ls_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからアクションに変換
* long idx : インデックス
* return : アクション
***************************************************************/

act_kind_t	trans_idx_to_act_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_act_trans_tab )
			/ sizeof( g_act_trans_tab[0] );

	if( idx < 0 )
		return ACT_KIND_NULL;
	if( idx >= max_idx )
		return ACT_KIND_NULL;

	return( g_act_trans_tab[idx] );
}

/***************************************************************
* アクションからインデックスに変換
* act_kind_t k : アクション
* return : インデックス
***************************************************************/

long	trans_act_kind_to_idx( act_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_act_trans_tab )
			/ sizeof( g_act_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_act_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからターゲットの種類に変換
* long idx : インデックス
* return : ターゲットの種類
***************************************************************/

trgt_kind_t	trans_idx_to_trgt_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_trgt_trans_tab )
			/ sizeof( g_trgt_trans_tab[0] );

	if( idx < 0 )
		return TRGT_KIND_NULL;
	if( idx >= max_idx )
		return TRGT_KIND_NULL;

	return( g_trgt_trans_tab[idx] );
}

/***************************************************************
* ターゲットの種類からインデックスに変換
* trgt_kind_t k : ターゲットの種類
* return : インデックス
***************************************************************/

long	trans_trgt_kind_to_idx( trgt_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_trgt_trans_tab )
			/ sizeof( g_trgt_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_trgt_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから間合いに変換
* long idx : インデックス
* return : 間合い
***************************************************************/

dist_t	trans_idx_to_dist_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_dist_trans_tab )
			/ sizeof( g_dist_trans_tab[0] );

	if( idx < 0 )
		return DIST_NEAR;
	if( idx >= max_idx )
		return DIST_NEAR;

	return( g_dist_trans_tab[idx] );
}

/***************************************************************
* 間合いからインデックスに変換
* dist_t k : 間合い
* return : インデックス
***************************************************************/

long	trans_dist_kind_to_idx( dist_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_dist_trans_tab )
			/ sizeof( g_dist_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_dist_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからターゲットの種類に変換
* long idx : インデックス
* return : ターゲットの種類
***************************************************************/

auto_mark_trgt_t	trans_idx_to_am_trgt( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_am_trgt_trans_tab )
			/ sizeof( g_am_trgt_trans_tab[0] );

	if( idx < 0 )
		return AUTO_MARK_TRGT_CLEAR;
	if( idx >= max_idx )
		return AUTO_MARK_TRGT_CLEAR;

	return( g_am_trgt_trans_tab[idx] );
}

/***************************************************************
* ターゲットの種類からインデックスに変換
* auto_mark_trgt_t k : ターゲットの種類
* return : インデックス
***************************************************************/

long	trans_am_trgt_to_idx( auto_mark_trgt_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_am_trgt_trans_tab )
			/ sizeof( g_am_trgt_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_am_trgt_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから間合いに変換
* long idx : インデックス
* return : 間合い
***************************************************************/

auto_mark_dist_t	trans_idx_to_am_dist( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_am_dist_trans_tab )
			/ sizeof( g_am_dist_trans_tab[0] );

	if( idx < 0 )
		return AUTO_MARK_DIST_NEAR;
	if( idx >= max_idx )
		return AUTO_MARK_DIST_NEAR;

	return( g_am_dist_trans_tab[idx] );
}

/***************************************************************
* 間合いからインデックスに変換
* auto_mark_dist_t k : 間合い
* return : インデックス
***************************************************************/

long	trans_am_dist_to_idx( auto_mark_dist_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_am_dist_trans_tab )
			/ sizeof( g_am_dist_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_am_dist_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから条件に変換
* long idx : インデックス
* return : 条件
***************************************************************/

auto_mark_act_t	trans_idx_to_am_act( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_am_act_trans_tab )
			/ sizeof( g_am_act_trans_tab[0] );

	if( idx < 0 )
		return AUTO_MARK_ACT_FIGHT;
	if( idx >= max_idx )
		return AUTO_MARK_ACT_FIGHT;

	return( g_am_act_trans_tab[idx] );
}

/***************************************************************
* 条件からインデックスに変換
* auto_mark_act_t k : 条件
* return : インデックス
***************************************************************/

long	trans_am_act_to_idx( auto_mark_act_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_am_act_trans_tab )
			/ sizeof( g_am_act_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_am_act_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから条件に変換
* long idx : インデックス
* return : 条件
***************************************************************/

auto_mark_cond_t	trans_idx_to_am_cond( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_am_cond_trans_tab )
			/ sizeof( g_am_cond_trans_tab[0] );

	if( idx < 0 )
		return AUTO_MARK_COND_DISPERSE;
	if( idx >= max_idx )
		return AUTO_MARK_COND_DISPERSE;

	return( g_am_cond_trans_tab[idx] );
}

/***************************************************************
* 条件からインデックスに変換
* auto_mark_cond_t k : 条件
* return : インデックス
***************************************************************/

long	trans_am_cond_to_idx( auto_mark_cond_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_am_cond_trans_tab )
			/ sizeof( g_am_cond_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_am_cond_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからデフォルトの種類に変換
* long idx : インデックス
* return : デフォルトの種類
***************************************************************/

dflt_auto_mark_t	trans_idx_to_am_dflt( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_am_dflt_trans_tab )
			/ sizeof( g_am_dflt_trans_tab[0] );

	if( idx < 0 )
		return DFLT_AUTO_MARK_NULL;
	if( idx >= max_idx )
		return DFLT_AUTO_MARK_NULL;

	return( g_am_dflt_trans_tab[idx] );
}

/***************************************************************
* デフォルトの種類からインデックスに変換
* dflt_auto_mark_t k : デフォルトの種類
* return : インデックス
***************************************************************/

long	trans_am_dflt_to_idx( dflt_auto_mark_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_am_dflt_trans_tab )
			/ sizeof( g_am_dflt_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_am_dflt_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから反応に変換
* long idx : インデックス
* return : 反応
***************************************************************/

attitude_t	trans_idx_to_attitude_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_attitude_trans_tab )
			/ sizeof( g_attitude_trans_tab[0] );

	if( idx < 0 )
		return ATTITUDE_MATE;
	if( idx >= max_idx )
		return ATTITUDE_MATE;

	return( g_attitude_trans_tab[idx] );
}

/***************************************************************
* 反応からインデックスに変換
* attitude_t k : 反応
* return : インデックス
***************************************************************/

long	trans_attitude_kind_to_idx( attitude_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_attitude_trans_tab )
			/ sizeof( g_attitude_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_attitude_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからアイテムの種類に変換
* long idx : インデックス
* return : アイテムの種類
***************************************************************/

item_kind_t	trans_idx_to_item_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_item_trans_tab )
			/ sizeof( g_item_trans_tab[0] );

	if( idx < 0 )
		return ITEM_KIND_NULL;
	if( idx >= max_idx )
		return ITEM_KIND_NULL;

	return( g_item_trans_tab[idx] );
}

/***************************************************************
* アイテムの種類からインデックスに変換
* item_kind_t k : アイテムの種類
* return : インデックス
***************************************************************/

long	trans_item_kind_to_idx( item_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_item_trans_tab )
			/ sizeof( g_item_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_item_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからキー・アイテムの種類に変換
* long idx : インデックス
* return : キー・アイテムの種類
***************************************************************/

star_drop_kind_t	trans_idx_to_key_item_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_key_item_trans_tab )
			/ sizeof( g_key_item_trans_tab[0] );

	if( idx < 0 )
		return STAR_DROP_KIND_ELEC;
	if( idx >= max_idx )
		return STAR_DROP_KIND_ELEC;

	return( g_key_item_trans_tab[idx] );
}

/***************************************************************
* キー・アイテムの種類からインデックスに変換
* star_drop_kind_t k : キー・アイテムの種類
* return : インデックス
***************************************************************/

long	trans_key_item_kind_to_idx( star_drop_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_key_item_trans_tab )
			/ sizeof( g_key_item_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_key_item_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから武器の種類に変換
* long idx : インデックス
* return : 武器の種類
***************************************************************/

wpn_kind_t	trans_idx_to_wpn_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_wpn_trans_tab )
			/ sizeof( g_wpn_trans_tab[0] );

	if( idx < 0 )
		return WPN_KIND_NULL;
	if( idx >= max_idx )
		return WPN_KIND_NULL;

	return( g_wpn_trans_tab[idx] );
}

/***************************************************************
* 武器の種類からインデックスに変換
* wpn_kind_t k : 武器の種類
* return : インデックス
***************************************************************/

long	trans_wpn_kind_to_idx( wpn_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_wpn_trans_tab )
			/ sizeof( g_wpn_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_wpn_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから弓の種類に変換
* long idx : インデックス
* return : 弓の種類
***************************************************************/

bow_kind_t	trans_idx_to_bow_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_bow_trans_tab )
			/ sizeof( g_bow_trans_tab[0] );

	if( idx < 0 )
		return BOW_KIND_NULL;
	if( idx >= max_idx )
		return BOW_KIND_NULL;

	return( g_bow_trans_tab[idx] );
}

/***************************************************************
* 弓の種類からインデックスに変換
* bow_kind_t k : 弓の種類
* return : インデックス
***************************************************************/

long	trans_bow_kind_to_idx( bow_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_bow_trans_tab )
			/ sizeof( g_bow_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_bow_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから防具の種類に変換
* long idx : インデックス
* return : 防具の種類
***************************************************************/

armor_kind_t	trans_idx_to_armor_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_armor_trans_tab )
			/ sizeof( g_armor_trans_tab[0] );

	if( idx < 0 )
		return ARMOR_KIND_NULL;
	if( idx >= max_idx )
		return ARMOR_KIND_NULL;

	return( g_armor_trans_tab[idx] );
}

/***************************************************************
* 防具の種類からインデックスに変換
* armor_kind_t k : 防具の種類
* return : インデックス
***************************************************************/

long	trans_armor_kind_to_idx( armor_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_armor_trans_tab )
			/ sizeof( g_armor_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_armor_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから RAF 武器の種類に変換
* long idx : インデックス
* return : 防具の種類
***************************************************************/

wpn_randm_art_kind_t	trans_idx_to_wpn_randm_art_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_wpn_randm_art_trans_tab )
			/ sizeof( g_wpn_randm_art_trans_tab[0] );

	if( idx < 0 )
		return WPN_RANDM_ART_KIND_NULL;
	if( idx >= max_idx )
		return WPN_RANDM_ART_KIND_NULL;

	return( g_wpn_randm_art_trans_tab[idx] );
}

/***************************************************************
* RAF 武器の種類からインデックスに変換
* wpn_kind_t k : 防具の種類
* return : インデックス
***************************************************************/

long	trans_wpn_randm_art_kind_to_idx( wpn_randm_art_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_wpn_randm_art_trans_tab )
			/ sizeof( g_wpn_randm_art_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_wpn_randm_art_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから RAF 防具の種類に変換
* long idx : インデックス
* return : 防具の種類
***************************************************************/

armor_randm_art_kind_t	trans_idx_to_armor_randm_art_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_armor_randm_art_trans_tab )
			/ sizeof( g_armor_randm_art_trans_tab[0] );

	if( idx < 0 )
		return ARMOR_RANDM_ART_KIND_NULL;
	if( idx >= max_idx )
		return ARMOR_RANDM_ART_KIND_NULL;

	return( g_armor_randm_art_trans_tab[idx] );
}

/***************************************************************
* RAF 防具の種類からインデックスに変換
* armor_kind_t k : 防具の種類
* return : インデックス
***************************************************************/

long	trans_armor_randm_art_kind_to_idx( armor_randm_art_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_armor_randm_art_trans_tab )
			/ sizeof( g_armor_randm_art_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_armor_randm_art_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから薬の種類への変換テーブルの要素数を返す
* return : 要素数
***************************************************************/

long	get_potion_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_potion_trans_tab );
	max_idx /= sizeof( g_potion_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* インデックスから薬の種類に変換
* long idx : インデックス
* return : 薬の種類
***************************************************************/

potion_kind_t	trans_idx_to_potion_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_potion_trans_tab )
			/ sizeof( g_potion_trans_tab[0] );

	if( idx < 0 )
		return POTION_KIND_NULL;
	if( idx >= max_idx )
		return POTION_KIND_NULL;

	return( g_potion_trans_tab[idx] );
}

/***************************************************************
* 薬の種類からインデックスに変換
* potion_kind_t k : 薬の種類
* return : インデックス
***************************************************************/

long	trans_potion_kind_to_idx( potion_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_potion_trans_tab )
			/ sizeof( g_potion_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_potion_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから巻物の種類への変換テーブルの要素数を返す
* return : 要素数
***************************************************************/

long	get_scroll_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_scroll_trans_tab );
	max_idx /= sizeof( g_scroll_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* インデックスから巻物の種類に変換
* long idx : インデックス
* return : 巻物の種類
***************************************************************/

scroll_kind_t	trans_idx_to_scroll_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_scroll_trans_tab )
			/ sizeof( g_scroll_trans_tab[0] );

	if( idx < 0 )
		return SCROLL_KIND_NULL;
	if( idx >= max_idx )
		return SCROLL_KIND_NULL;

	return( g_scroll_trans_tab[idx] );
}

/***************************************************************
* 巻物の種類からインデックスに変換
* scroll_kind_t k : 巻物の種類
* return : インデックス
***************************************************************/

long	trans_scroll_kind_to_idx( scroll_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_scroll_trans_tab )
			/ sizeof( g_scroll_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_scroll_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから杖の種類に変換
* long idx : インデックス
* return : 杖の種類
***************************************************************/

stick_kind_t	trans_idx_to_stick_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_stick_trans_tab )
			/ sizeof( g_stick_trans_tab[0] );

	if( idx < 0 )
		return STICK_KIND_NULL;
	if( idx >= max_idx )
		return STICK_KIND_NULL;

	return( g_stick_trans_tab[idx] );
}

/***************************************************************
* 杖の種類からインデックスに変換
* stick_kind_t k : 杖の種類
* return : インデックス
***************************************************************/

long	trans_stick_kind_to_idx( stick_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_stick_trans_tab )
			/ sizeof( g_stick_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_stick_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからアクセサリの種類に変換
* long idx : インデックス
* return : アクセサリの種類
***************************************************************/

acce_kind_t	trans_idx_to_acce_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_acce_trans_tab )
			/ sizeof( g_acce_trans_tab[0] );

	if( idx < 0 )
		return ACCE_KIND_NULL;
	if( idx >= max_idx )
		return ACCE_KIND_NULL;

	return( g_acce_trans_tab[idx] );
}

/***************************************************************
* アクセサリの種類からインデックスに変換
* acce_kind_t k : アクセサリの種類
* return : インデックス
***************************************************************/

long	trans_acce_kind_to_idx( acce_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_acce_trans_tab )
			/ sizeof( g_acce_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_acce_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから指輪の種類に変換
* long idx : インデックス
* return : 指輪の種類
***************************************************************/

ring_kind_t	trans_idx_to_ring_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_ring_trans_tab )
			/ sizeof( g_ring_trans_tab[0] );

	if( idx < 0 )
		return RING_KIND_NULL;
	if( idx >= max_idx )
		return RING_KIND_NULL;

	return( g_ring_trans_tab[idx] );
}

/***************************************************************
* 指輪の種類からインデックスに変換
* ring_kind_t k : 指輪の種類
* return : インデックス
***************************************************************/

long	trans_ring_kind_to_idx( ring_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_ring_trans_tab )
			/ sizeof( g_ring_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_ring_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから護符の種類に変換
* long idx : インデックス
* return : 護符の種類
***************************************************************/

amulet_kind_t	trans_idx_to_amulet_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_amulet_trans_tab )
			/ sizeof( g_amulet_trans_tab[0] );

	if( idx < 0 )
		return AMULET_KIND_NULL;
	if( idx >= max_idx )
		return AMULET_KIND_NULL;

	return( g_amulet_trans_tab[idx] );
}

/***************************************************************
* 護符の種類からインデックスに変換
* amulet_kind_t k : 護符の種類
* return : インデックス
***************************************************************/

long	trans_amulet_kind_to_idx( amulet_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_amulet_trans_tab )
			/ sizeof( g_amulet_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_amulet_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから首輪の種類に変換
* long idx : インデックス
* return : 首輪の種類
***************************************************************/

necklace_kind_t	trans_idx_to_necklace_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_necklace_trans_tab )
			/ sizeof( g_necklace_trans_tab[0] );

	if( idx < 0 )
		return NECKLACE_KIND_NULL;
	if( idx >= max_idx )
		return NECKLACE_KIND_NULL;

	return( g_necklace_trans_tab[idx] );
}

/***************************************************************
* 首輪の種類からインデックスに変換
* necklace_kind_t k : 首輪の種類
* return : インデックス
***************************************************************/

long	trans_necklace_kind_to_idx( necklace_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_necklace_trans_tab )
			/ sizeof( g_necklace_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_necklace_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから楽器の種類に変換
* long idx : インデックス
* return : 楽器の種類
***************************************************************/

inst_kind_t	trans_idx_to_inst_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_inst_trans_tab )
			/ sizeof( g_inst_trans_tab[0] );

	if( idx < 0 )
		return INST_KIND_NULL;
	if( idx >= max_idx )
		return INST_KIND_NULL;

	return( g_inst_trans_tab[idx] );
}

/***************************************************************
* 楽器の種類からインデックスに変換
* inst_kind_t k : 楽器の種類
* return : インデックス
***************************************************************/

long	trans_inst_kind_to_idx( inst_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_inst_trans_tab )
			/ sizeof( g_inst_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_inst_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから詩集の種類に変換
* long idx : インデックス
* return : 詩集の種類
***************************************************************/

anthology_kind_t	trans_idx_to_anthology_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_anthology_trans_tab )
			/ sizeof( g_anthology_trans_tab[0] );

	if( idx < 0 )
		return ANTHOLOGY_KIND_NULL;
	if( idx >= max_idx )
		return ANTHOLOGY_KIND_NULL;

	return( g_anthology_trans_tab[idx] );
}

/***************************************************************
* 詩集の種類からインデックスに変換
* anthology_kind_t k : 詩集の種類
* return : インデックス
***************************************************************/

long	trans_anthology_kind_to_idx( anthology_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_anthology_trans_tab )
			/ sizeof( g_anthology_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_anthology_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから明かりの種類に変換
* long idx : インデックス
* return : 明かりの種類
***************************************************************/

light_kind_t	trans_idx_to_light_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_light_trans_tab )
			/ sizeof( g_light_trans_tab[0] );

	if( idx < 0 )
		return LIGHT_KIND_NULL;
	if( idx >= max_idx )
		return LIGHT_KIND_NULL;

	return( g_light_trans_tab[idx] );
}

/***************************************************************
* 明かりの種類からインデックスに変換
* light_kind_t k : 明かりの種類
* return : インデックス
***************************************************************/

long	trans_light_kind_to_idx( light_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_light_trans_tab )
			/ sizeof( g_light_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_light_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから望みの魔神の種類に変換
* long idx : インデックス
* return : 望みの魔神の種類
***************************************************************/

wish_level_t	trans_idx_to_wish_level( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_wish_level_trans_tab )
			/ sizeof( g_wish_level_trans_tab[0] );

	if( idx < 0 )
		return WISH_LEVEL_NULL;
	if( idx >= max_idx )
		return WISH_LEVEL_NULL;

	return( g_wish_level_trans_tab[idx] );
}

/***************************************************************
* 望みの魔神の種類からインデックスに変換
* wish_level_t k : 望みの魔神の種類
* return : インデックス
***************************************************************/

long	trans_wish_level_to_idx( wish_level_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_wish_level_trans_tab )
			/ sizeof( g_wish_level_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_wish_level_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから食料の種類に変換
* long idx : インデックス
* return : 食料の種類
***************************************************************/

food_kind_t	trans_idx_to_food_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_food_trans_tab )
			/ sizeof( g_food_trans_tab[0] );

	if( idx < 0 )
		return FOOD_KIND_NULL;
	if( idx >= max_idx )
		return FOOD_KIND_NULL;

	return( g_food_trans_tab[idx] );
}

/***************************************************************
* 食料の種類からインデックスに変換
* food_kind_t k : 食料の種類
* return : インデックス
***************************************************************/

long	trans_food_kind_to_idx( food_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_food_trans_tab )
			/ sizeof( g_food_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_food_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから煙草の種類に変換
* long idx : インデックス
* return : 煙草の種類
***************************************************************/

tobacco_kind_t	trans_idx_to_tobacco_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_tobacco_trans_tab )
			/ sizeof( g_tobacco_trans_tab[0] );

	if( idx < 0 )
		return TOBACCO_KIND_NULL;
	if( idx >= max_idx )
		return TOBACCO_KIND_NULL;

	return( g_tobacco_trans_tab[idx] );
}

/***************************************************************
* 煙草の種類からインデックスに変換
* tobacco_kind_t k : 煙草の種類
* return : インデックス
***************************************************************/

long	trans_tobacco_kind_to_idx( tobacco_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_tobacco_trans_tab )
			/ sizeof( g_tobacco_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_tobacco_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから煙草のブランドに変換
* long idx : インデックス
* return : 煙草のブランド
***************************************************************/

tobacco_brand_t	trans_idx_to_tobacco_brand( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_tobacco_brand_trans_tab )
			/ sizeof( g_tobacco_brand_trans_tab[0] );

	if( idx < 0 )
		return TOBACCO_BRAND_NULL;
	if( idx >= max_idx )
		return TOBACCO_BRAND_NULL;

	return( g_tobacco_brand_trans_tab[idx] );
}

/***************************************************************
* 煙草のブランドからインデックスに変換
* tobacco_brand_t k : 煙草のブランドの種類
* return : インデックス
***************************************************************/

long	trans_tobacco_brand_to_idx( tobacco_brand_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_tobacco_brand_trans_tab )
			/ sizeof( g_tobacco_brand_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_tobacco_brand_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからパイプの種類に変換
* long idx : インデックス
* return : パイプの種類
***************************************************************/

pipe_kind_t	trans_idx_to_pipe_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_pipe_trans_tab )
			/ sizeof( g_pipe_trans_tab[0] );

	if( idx < 0 )
		return PIPE_KIND_NULL;
	if( idx >= max_idx )
		return PIPE_KIND_NULL;

	return( g_pipe_trans_tab[idx] );
}

/***************************************************************
* パイプの種類からインデックスに変換
* pipe_kind_t k : パイプの種類
* return : インデックス
***************************************************************/

long	trans_pipe_kind_to_idx( pipe_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_pipe_trans_tab )
			/ sizeof( g_pipe_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_pipe_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからレア・グッズの種類に変換
* long idx : インデックス
* return : レア・グッズの種類
***************************************************************/

rare_goods_kind_t	trans_idx_to_rare_goods_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_rare_goods_trans_tab )
			/ sizeof( g_rare_goods_trans_tab[0] );

	if( idx < 0 )
		return RARE_GOODS_KIND_NULL;
	if( idx >= max_idx )
		return RARE_GOODS_KIND_NULL;

	return( g_rare_goods_trans_tab[idx] );
}

/***************************************************************
* レア・グッズの種類からインデックスに変換
* rare_goods_kind_t k : レア・グッズの種類
* return : インデックス
***************************************************************/

long	trans_rare_goods_kind_to_idx( rare_goods_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_rare_goods_trans_tab )
			/ sizeof( g_rare_goods_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_rare_goods_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからコインの種類に変換
* long idx : インデックス
* return : コインの種類
***************************************************************/

coin_kind_t	trans_idx_to_coin_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_coin_trans_tab )
			/ sizeof( g_coin_trans_tab[0] );

	if( idx < 0 )
		return COIN_KIND_NULL;
	if( idx >= max_idx )
		return COIN_KIND_NULL;

	return( g_coin_trans_tab[idx] );
}

/***************************************************************
* コインの種類からインデックスに変換
* coin_kind_t k : コインの種類
* return : インデックス
***************************************************************/

long	trans_coin_kind_to_idx( coin_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_coin_trans_tab )
			/ sizeof( g_coin_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_coin_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから呪文の種類への変換テーブルの要素数を返す
* return : 要素数
***************************************************************/

long	get_spell_kind_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_spell_trans_tab );
	max_idx /= sizeof( g_spell_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* インデックスから呪文の種類に変換
* long idx : インデックス
* return : 呪文の種類
***************************************************************/

spell_kind_t	trans_idx_to_spell_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_spell_trans_tab )
			/ sizeof( g_spell_trans_tab[0] );

	if( idx < 0 )
		return SPELL_KIND_NULL;
	if( idx >= max_idx )
		return SPELL_KIND_NULL;

	return( g_spell_trans_tab[idx] );
}

/***************************************************************
* 呪文の種類からインデックスに変換
* spell_kind_t k : 呪文の種類
* return : インデックス
***************************************************************/

long	trans_spell_kind_to_idx( spell_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_spell_trans_tab )
			/ sizeof( g_spell_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_spell_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスからモンスターの種類に変換
* long idx : インデックス
* return : モンスターの種類
***************************************************************/

mnstr_kind_t	trans_idx_to_mnstr_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_mnstr_trans_tab )
			/ sizeof( g_mnstr_trans_tab[0] );

	if( idx < 0 )
		return MNSTR_KIND_NULL;
	if( idx >= max_idx )
		return MNSTR_KIND_NULL;

	return( g_mnstr_trans_tab[idx] );
}

/***************************************************************
* モンスターの種類からインデックスに変換
* mnstr_kind_t k : モンスターの種類
* return : インデックス
***************************************************************/

long	trans_mnstr_kind_to_idx( mnstr_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_mnstr_trans_tab )
			/ sizeof( g_mnstr_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_mnstr_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから罠の種類に変換
* long idx : インデックス
* return : 罠の種類
***************************************************************/

trap_kind_t	trans_idx_to_trap_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_trap_trans_tab )
			/ sizeof( g_trap_trans_tab[0] );

	if( idx < 0 )
		return TRAP_KIND_NULL;
	if( idx >= max_idx )
		return TRAP_KIND_NULL;

	return( g_trap_trans_tab[idx] );
}

/***************************************************************
* 罠の種類からインデックスに変換
* trap_kind_t k : 罠の種類
* return : インデックス
***************************************************************/

long	trans_trap_kind_to_idx( trap_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_trap_trans_tab )
			/ sizeof( g_trap_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_trap_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから効果の種類に変換
* long idx : インデックス
* return : 効果の種類
***************************************************************/

fx_kind_t	trans_idx_to_fx_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_fx_trans_tab )
			/ sizeof( g_fx_trans_tab[0] );

	if( idx < 0 )
		return FX_KIND_NULL;
	if( idx >= max_idx )
		return FX_KIND_NULL;

	return( g_fx_trans_tab[idx] );
}

/***************************************************************
* 効果の種類からインデックスに変換
* fx_kind_t k : 効果の種類
* return : インデックス
***************************************************************/

long	trans_fx_kind_to_idx( fx_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_fx_trans_tab )
			/ sizeof( g_fx_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_fx_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから依頼の種類に変換
* long idx : インデックス
* return : 依頼の種類
***************************************************************/

request_kind_t	trans_idx_to_request_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_request_trans_tab )
			/ sizeof( g_request_trans_tab[0] );

	if( idx < 0 )
		return REQUEST_KIND_NULL;
	if( idx >= max_idx )
		return REQUEST_KIND_NULL;

	return( g_request_trans_tab[idx] );
}

/***************************************************************
* 依頼の種類からインデックスに変換
* request_kind_t k : 依頼の種類
* return : インデックス
***************************************************************/

long	trans_request_kind_to_idx( request_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_request_trans_tab )
			/ sizeof( g_request_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_request_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* インデックスから宿屋の部屋の種類への変換テーブルの要素数を返す
* return : 要素数
***************************************************************/

long	get_stay_inn_kind_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_stay_inn_kind_trans_tab );
	max_idx /= sizeof( g_stay_inn_kind_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* インデックスから宿屋の部屋の種類に変換
* long idx : インデックス
* return : 宿屋の部屋の種類
***************************************************************/

stay_inn_kind_t	trans_idx_to_stay_inn_kind( long idx )
{
	long	max_idx;

	max_idx = sizeof( g_stay_inn_kind_trans_tab )
			/ sizeof( g_stay_inn_kind_trans_tab[0] );

	if( idx < 0 )
		return STAY_INN_KIND_MAX_N;
	if( idx >= max_idx )
		return STAY_INN_KIND_MAX_N;

	return( g_stay_inn_kind_trans_tab[idx] );
}

/***************************************************************
* 宿屋の部屋の種類からインデックスに変換
* stay_inn_kind_t k : 宿屋の部屋の種類
* return : インデックス
***************************************************************/

long	trans_stay_inn_kind_to_idx( stay_inn_kind_t k )
{
	long	max_idx;
	long	i;

	max_idx = sizeof( g_stay_inn_kind_trans_tab )
			/ sizeof( g_stay_inn_kind_trans_tab[0] );

	for( i = 0; i < max_idx; i++ )
		if( g_stay_inn_kind_trans_tab[i] == k )
			return i;

	return 0;
}

/***************************************************************
* ファイルをコピーする
* const char *src : コピー元フルパス
* const char *dst : コピー先フルパス
* return : エラーが無かったか?
***************************************************************/

bool_t	copy_file( const char *src, const char *dst )
{
	FILE	*fp_src, *fp_dst;
	bool_t	flg_success = TRUE;
	long	c;

	if( src == NULL )
		return FALSE;
	if( dst == NULL )
		return FALSE;

	fp_src = fopen( src, "rb" );
	if( fp_src == NULL )
		return FALSE;

	fp_dst = fopen( dst, "wb" );
	if( fp_dst == NULL )
		return FALSE;

	while( !feof( fp_src ) ){
		c = getc( fp_src );
		if( c == EOF ){
			if( !feof( fp_src ) )
				flg_success = FALSE;
			break;
		}

		if( putc( c, fp_dst ) == EOF ){
			if( !feof( fp_src ) )
				flg_success = FALSE;
			break;
		}
	}

	if( fclose( fp_dst ) != 0 )
		flg_success = FALSE;
	if( fclose( fp_src ) != 0 )
		flg_success = FALSE;

	return flg_success;
}

/***************************************************************
* パスとファイル名をつなげてフルパスにする
* char *path : パス
* char *file : ファイル名
* return : フルパス
***************************************************************/

char	*cat_path( const char *path, const char *file )
{
	static char	dst[FILE_NAME_MAX_LEN + 1];

	str_nz_cpy( dst, path, FILE_NAME_MAX_LEN );
	str_max_n_cat( dst, STR_SLASH, FILE_NAME_MAX_LEN );
	str_max_n_cat( dst, file, FILE_NAME_MAX_LEN );

	return dst;
}

/***************************************************************
* ファイルが存在するか調べる
* char *s : ファイル名
* return : 存在したか?
***************************************************************/

bool_t	chk_exist_file( const char *s )
{
	FILE	*fp;

	fp = fopen( s, "r" );
	if( fp == NULL )
		return FALSE;

	if( fclose( fp ) == EOF )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ディレクトリが存在するか調べる
* char *s : ディレクトリ名
* return : 存在したか?
***************************************************************/

bool_t	chk_exist_dir( const char *s )
{
	FILE	*fp;

#ifdef	D_DOS
	make_dir( s );
	return TRUE;
#endif	/* D_DOS */

	fp = fopen( s, "r" );
	if( fp == NULL )
		return FALSE;

	if( fclose( fp ) == EOF )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ディレクトリを掘る
* char *s : ディレクトリ名
* return : エラーが無かったか?
***************************************************************/

bool_t	make_dir( const char *path )
{
	char	cur_path[FILE_NAME_MAX_LEN + 1];
	char	*p;

	if( path == NULL )
		return FALSE;

	str_nz_cpy( cur_path, path, FILE_NAME_MAX_LEN );

	p = cur_path;
	while( 1 ){
		p = strchr( p + 1, '/' );
		if( p == NULL )
			break;
		if( *p == '\0' )
			break;

		*p = '\0';
		make_dir_node( cur_path );
		*p = '/';
	}
	make_dir_node( cur_path );

	return TRUE;
}

/***************************************************************
* ディレクトリを 1 つ掘る
* char *s : ディレクトリ名
* return : エラーが無かったか?
***************************************************************/

bool_t	make_dir_node( const char *path )
{
	if( path == NULL )
		return FALSE;
#if	defined( D_DOS )
	if( _mkdir( path ) )
		return TRUE;
	else
		return FALSE;
#elif	defined( HAVE_MKDIR )
	if( mkdir( path, S_IFDIR | 0755 ) == 0 )
		return TRUE;
	else
		return FALSE;
#else
	if( mknod( path, S_IFDIR | 0755, 0 ) == 0 )
		return TRUE;
	else
		return FALSE;
#endif
	return FALSE;
}

/***************************************************************
* 文字がクオートならエスケープする
* const long c : 変換する文字
* return : 変換後の文字列
***************************************************************/

char	*cv_esc_quote_c( const long c )
{
	static char	buf[TOKEN_MAX_LEN + 1];

	buf[0] = (unsigned char)c;
	buf[1] = '\0';

	return( cv_esc_quote_str( buf ) );
}

/***************************************************************
* 文字列中のクオートをエスケープする
* const char *str : 変換する文字列
* return : 変換後の文字列
***************************************************************/

char	*cv_esc_quote_str( const char *str )
{
	static char	buf[TOKEN_MAX_LEN + 1];
	long	src_idx, dst_idx;

	src_idx = 0;
	dst_idx = 0;
	for( src_idx = 0; src_idx < TOKEN_MAX_LEN; src_idx++ ){
		long	c;

		c = str[src_idx];
		if( c == '\0' )
			break;

		if( (c == '\'') || (c == '\"') ){
			buf[dst_idx] = '\\';
			dst_idx++;

			buf[dst_idx] = (char)(c);
		} else if( c == '\n' ){
			buf[dst_idx] = '\\';
			dst_idx++;

			buf[dst_idx] = 'n';
		} else if( c == '\r' ){
			buf[dst_idx] = '\\';
			dst_idx++;

			buf[dst_idx] = 'n';
		} else {
			buf[dst_idx] = str[src_idx];
		}

		dst_idx++;
	}

	buf[dst_idx] = '\0';

	return buf;
}

/***************************************************************
* 文字列中のコントロール・コードをエスケープする
* クオートは処理しない
* const char *str : 変換する文字列
* return : 変換後の文字列
***************************************************************/

char	*cv_esc_ctrl_str( const char *str )
{
	static char	buf[TOKEN_MAX_LEN + 16 + 1];
	long	src_idx, dst_idx;

	buf[0] = '\0';
	if( str == NULL )
		return buf;

	src_idx = 0;
	dst_idx = 0;
	for( src_idx = 0; src_idx < TOKEN_MAX_LEN; src_idx++, dst_idx++ ){
		long	c;

		c = str[src_idx];
		if( c == '\0' )
			break;

		if( c >= 128 ){
			buf[dst_idx] = c;

			src_idx++;
			c = str[src_idx];
			if( c == '\0' )
				break;

			dst_idx++;
			buf[dst_idx] = c;
		} else if( c == '\\' ){
			buf[dst_idx] = '\\';
			dst_idx++;

			buf[dst_idx] = '\\';
		} else if( c == '\n' ){
			buf[dst_idx] = '\\';
			dst_idx++;

			buf[dst_idx] = 'n';
		} else if( c == '\r' ){
			buf[dst_idx] = '\\';
			dst_idx++;

			buf[dst_idx] = 'r';
		} else if( c < ' ' ){
			buf[dst_idx] = '^';
			dst_idx++;

			buf[dst_idx] = (char)(c + '@');
		} else {
			buf[dst_idx] = str[src_idx];
		}
	}

	buf[dst_idx] = '\0';

	return buf;
}

/***************************************************************
* 暗号化用乱数を初期化
* long n : 乱数の種
* return : 乱数の種
***************************************************************/

long	srandm_crypt( long n )
{
	g_randm_crypt_seed = n;

	return g_randm_crypt_seed;
}

/***************************************************************
* 文字を暗号化する
* long c : 文字
* return : 暗号化した文字
***************************************************************/

long	randm_crypt( long c )
{
	long	a;

	if( c == EOF )
		return EOF;

	g_randm_crypt_seed += 15349;
	g_randm_crypt_seed *= 3793;
	g_randm_crypt_seed += 598393;
	a = (g_randm_crypt_seed & 0xffff0000) >> 16;
	g_randm_crypt_seed = ((g_randm_crypt_seed & 0x0000ffff) << 16) + a;
	g_randm_crypt_seed = labs( g_randm_crypt_seed );
	g_randm_crypt_seed += 379;
	g_randm_crypt_seed &= 0x7fffffff;

	c ^= g_randm_crypt_seed;
	c &= 0xff;

	return c;
}

/***************************************************************
* 字句解析と構文解析を初期化
* char *path : ファイルのフルパス
* bool_t flg_txt : テキスト・モードか?
***************************************************************/

void	reset_load_save( char *path, bool_t flg_txt )
{
	g_crypt_sum = 0;
	g_un_c = '\0';
	g_un_token = RC_TOKEN_NULL;

	set_flg_crypt_txt( flg_txt );

	set_rc_lex_file_name( path );
	clr_rc_lex_line();
	set_rc_lex_err( FALSE );
}

/***************************************************************
* 暗号化モードを設定
* bool_t flg_txt : テキスト・モードか?
***************************************************************/

void	set_flg_crypt_txt( bool_t flg_txt )
{
	g_flg_crypt_txt = flg_txt;
}

/***************************************************************
* 暗号化モードを設定してロード開始
* FILE *fp : ファイル
* bool_t flg_txt : テキスト・モードか?
***************************************************************/

void	reset_load_crypt( FILE *fp, bool_t flg_txt )
{
	if( flg_txt ){
		load_line( fp, TRUE );
	} else {
		char	*s;
		long	n;

		s = load_line( fp, TRUE );
		sscanf( s, "bin %ld", &n );
		srandm_crypt( n );
	}
}

/***************************************************************
* 暗号化モードを設定してセーブ開始
* FILE *fp : ファイル
* bool_t flg_txt : テキスト・モードか?
***************************************************************/

void	reset_save_crypt( FILE *fp, bool_t flg_txt )
{
	if( flg_txt ){
		fprintf( fp, "text\n" );
	} else {
		fprintf( fp, "bin %ld\n",
				srandm_crypt( time( NULL ) ) );
	}
}

/***************************************************************
* 字下げの初期化
***************************************************************/

void	reset_save_crypt_tab( void )
{
	g_tab_lev = 0;
}

/***************************************************************
* 字下げの設定
* FILE *fp : ファイル
* long n : 字下げの相対設定値
* return : 字下げの絶対設定値
***************************************************************/

long	set_save_crypt_tab( FILE *fp, long n )
{
	if( n >= +1 )
		save_crypt_tab( fp, "{\n" );

	g_tab_lev += n;

	if( n <= -1 )
		save_crypt_tab( fp, "},\n" );

	return g_tab_lev;
}

/***************************************************************
* 字下げ付きの printf
* FILE *fp : ファイル
* const char *s : フォーマット
* ... : 引数
* return : 字下げの絶対設定値
***************************************************************/

long	save_crypt_tab( FILE *fp, const char *s, ... )
{
	static char	buf[1024 + 1];
	va_list	argptr;
	long	i;

	va_start( argptr, s );
	vsn_printf( buf, 1024, s, argptr );
	va_end( argptr );

	for( i = 0; i < g_tab_lev; i++ )
		save_crypt_str( fp, "\t" );

	save_crypt_str( fp, "%s", buf );

	return g_tab_lev;
}

/***************************************************************
* 暗号化文字列出力
* FILE *fp : ファイル
* const char *s : フォーマット
* ... : 引数
* return : 字下げの絶対設定値
***************************************************************/

long	save_crypt_str( FILE *fp, const char *s, ... )
{
	static char	buf[1024 + 1];
	va_list	argptr;

	va_start( argptr, s );
	vsn_printf( buf, 1024, s, argptr );
	va_end( argptr );

	if( g_flg_crypt_txt ){
		fputs( buf, fp );
	} else {
		long	i;

		for( i = 0; buf[i] != '\0'; i++ ){
			g_crypt_sum += buf[i];

			fputc( randm_crypt( buf[i] ), fp );

			if( buf[i] == '\n' ){
				fputc( g_crypt_sum, fp );
				fputc( randm_crypt( '\n' ), fp );

				g_crypt_sum = 0;
			}
		}
	}

	return g_tab_lev;
}

/***************************************************************
* 暗号化文字列入力
* FILE *fp : ファイル
* char *buf : 文字列の入力先
* long n : 文字列の最大長
* return : 文字列の長さ
***************************************************************/

long	load_crypt_str( FILE *fp, char *buf, long n )
{
	long	c;
	long	i;

	if( feof( fp ) ){
		buf[0] = '\0';
		return 0;
	}

	for( i = 0; i < n; i++ ){
		c = load_crypt_c( fp );
		if( c == EOF )
			c = '\n';

		buf[i] = (char)c;
		if( c == '\n' ){
			return i;
		}
	}

	buf[i] = '\0';
	return i;
}

/***************************************************************
* 暗号化文字入力
* FILE *fp : ファイル
* return : 入力した文字
***************************************************************/

long	load_crypt_c( FILE *fp )
{
	long	c;

	c = load_crypt_c_sub( fp );
	if( c == '\n' )
		inc_rc_lex_line();

	return c;
}

long	load_crypt_c_sub( FILE *fp )
{
	long	c;

	if( feof( fp ) )
		return EOF;

	if( g_un_c != '\0' ){
		c = g_un_c;
		g_un_c = '\0';

		return c;
	}

	c = fgetc( fp );
	if( c == EOF )
		return EOF;

	if( g_flg_crypt_txt ){
		if( c == '\r' ){
			c = fgetc( fp );
			if( c != '\n' ){
				ungetc( c, fp );
			}
			c = '\n';
		}
	} else {
		c = randm_crypt( c );
		g_crypt_sum += (char)c;

		if( (c == '\n') || (c == '\r') ){
			if( fgetc( fp ) == g_crypt_sum ){
				g_crypt_sum = 0;
				randm_crypt( fgetc( fp ) );

				return '\n';
			} else {
				print_err( MSG_S, MSG_ERR_LOAD_BIN );
				exit_game( EXIT_FAILURE );
			}
		}
	}

	return c;
}

/***************************************************************
* 暗号化文字入力の取り消し
* FILE *fp : ファイル
* long c : 取り消す文字
***************************************************************/

void	un_load_crypt_c( FILE *fp, long c )
{
	g_un_c = c;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_gfile_c( void )
{
}
