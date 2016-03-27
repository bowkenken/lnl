/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ����ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�����
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�����ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ����Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: gfile.c,v 1.218 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �ե�����������
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************/

#include	"gfile-tab.h"

/***************************************************************
* �ե���������ν����
***************************************************************/

void	init_game_file( void )
{
	const char	*home, *s;

	g_rc_lex_num_mode = 0;

	g_game_data_save_n = 0;
	g_randm_seed_save = get_randm_seed();

	/* �ۡ��ࡦ�ǥ��쥯�ȥ������ */

	home = get_home_dir();

	if( !chk_exist_dir( home ) ){
		print_err( MSG_ERR_HOME_DIR, home );
		exit_game( EXIT_FAILURE );
	}

	/* �����ࡦ�ǥ��쥯�ȥ������ */

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
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_game_file( void )
{
}

/***************************************************************
* �ǥ��쥯�ȥ�ν����
* char *home : �ۡ��ࡦ�ǥ��쥯�ȥ�
* char *dir : �ǥ��쥯�ȥ�
* bool_t flg_GPL : �����ɽ�����뤫?
* return : �ǥ��쥯�ȥ�Υե�ѥ�(���顼�ʤ�NULL)
***************************************************************/

char	*init_dir_game( const char *home, const char *dir, bool_t flg_GPL )
{
	char	*name;

	/* �����ࡦ�ǥ��쥯�ȥ������ */
	name = cat_path( home, dir );

	if( chk_exist_dir( name ) )
		return name;

	/* ̵����� GPL ��ɽ�� */
	if( flg_GPL )
		about_game( TRUE );

	/* ̵����к�� */
	if( make_dir( name ) )
		return name;

	return NULL;
}

/***************************************************************
* �ۡ��ࡦ�ǥ��쥯�ȥ��õ��
* return : �ۡ��ࡦ�ǥ��쥯�ȥ�
***************************************************************/

const char	*get_home_dir( void )
{
	const char	*home;

	home = call_get_home_dir();
	if( home != NULL )
		return home;

	home = getenv( STR_ENV_HOME );

	/* ̵����Х����ȥǥ��쥯�ȥ� */
	if( (home == NULL) || (home[0] == '\0') )
		home = STR_DIR_NAME_CUR;

	return home;
}

/***************************************************************
* �����ࡦ�ǡ������ե�����Υƥ����ȤΥѥ����֤�
* char *path : �ѥ����֤�
* long n : �ǡ���������å��ֹ�
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
* �����ࡦ�ǡ������ե�����ΥХ��ʥ�Υѥ����֤�
* char *path : �ѥ����֤�
* long n : �ǡ���������å��ֹ�
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
* �����ࡦ�ǡ������ե����������Υѥ����֤�
* char *path : �ѥ����֤�
* long n : �ǡ���������å��ֹ�
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
* �����ࡦ�ǡ������ե�����Υ�ץ쥤�Υѥ����֤�
* char *path : �ѥ����֤�
* long n : �ǡ���������å��ֹ�
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
* �Х�����ݡ��ȤΥƥ����ȤΥѥ����֤�
* char *path : �ѥ����֤�
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
* �Х�����ݡ��ȤΥХ��ʥ�Υѥ����֤�
* char *path : �ѥ����֤�
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
* �Х�����ݡ��Ȥ�����Υѥ����֤�
* char *path : �ѥ����֤�
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
* �Х�����ݡ��ȤΥ�ץ쥤�Υѥ����֤�
* char *path : �ѥ����֤�
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
* �����ࡦ�ǡ������ե�����Υ����ץ�
* char type : 'r' = �꡼�� , 'w' = �饤��
* long n : �ǡ���������å��ֹ�
* bool_t flg_txt : �ƥ����ȡ��⡼�ɤ�?
* return : �ե����롦�ݥ���
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
* ���������ꡦ�ե�����Υ����ץ�
* char type : 'r' = �꡼�� , 'w' = �饤��
* long n : �ǡ���������å��ֹ�
* return : �ե����롦�ݥ���
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
* ��ץ쥤���ե�����Υ����ץ�
* char type : 'r' = �꡼�� , 'w' = �饤��
* long n : �ǡ���������å��ֹ�
* return : �ե����롦�ݥ���
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
* ��ץ쥤���ե�����κ��
* long n : �ǡ���������å��ֹ�
***************************************************************/

void	remove_replay_file( long n )
{
	FILE	*fp;

	fp = open_game_replay( 'w', n );

	if( fp != NULL )
		fclose( fp );
}

/***************************************************************
* �ե����뤫�� 1 ʸ���ɤ߹���
* FILE *fp : �ե�����
* bool_t flg_chk_eof : �ե�����ν�λ������å����뤫?
* return : �ɤ߹����ʸ��
***************************************************************/

long	load_char( FILE *fp, bool_t flg_chk_eof )
{
	return rc_lex_getc( fp, flg_chk_eof, TRUE );
}

/***************************************************************
* �ե����뤫�� 1 ���ɤ߹���(�����Ԥȥ����Ȥ����Ф�)
* FILE *fp : �ե�����
* bool_t flg_chk_eof : �ե�����ν�λ������å����뤫?
* return : �ɤ߹������
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
* �ե����뤫�� 1 ���ɤ߹���
* FILE *fp : �ե�����
* bool_t flg_chk_eof : �ե�����ν�λ������å����뤫?
* return : �ɤ߹������
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
* ����������Υե�����̾������
* char *name : �ե�����̾�����긵
* return : ���ꤵ�줿�ե�����̾
***************************************************************/

char	*set_rc_lex_file_name( char *name )
{
	str_nz_cpy( g_rc_lex_file_name, name, FILE_NAME_MAX_LEN );

	return g_rc_lex_file_name;
}

/***************************************************************
* ����������Υե�����̾���֤�
* return : �ե�����̾
***************************************************************/

char	*get_rc_lex_file_name( void )
{
	return g_rc_lex_file_name;
}

/***************************************************************
* ����������θ��ߤι��ֹ������
* return : ���ֹ�
***************************************************************/

long	clr_rc_lex_line( void )
{
	g_rc_lex_line = 1;

	return g_rc_lex_line;
}

/***************************************************************
* ����������θ��ߤι��ֹ�򥤥󥯥���Ȥ���
* return : ���ֹ�
***************************************************************/

long	inc_rc_lex_line( void )
{
	g_rc_lex_line++;

	return g_rc_lex_line;
}

/***************************************************************
* ����������θ��ߤι��ֹ��ǥ�����Ȥ���
* return : ���ֹ�
***************************************************************/

long	dec_rc_lex_line( void )
{
	g_rc_lex_line--;

	return g_rc_lex_line;
}

/***************************************************************
* ����������θ��ߤι��ֹ���֤�
* return : ���ֹ�
***************************************************************/

long	get_rc_lex_line( void )
{
	return g_rc_lex_line;
}

/***************************************************************
* ����������Υ��顼���֤�����
* bool_t flg : ���ꤹ�륨�顼����
* return : ���顼����
***************************************************************/

bool_t	set_rc_lex_err( bool_t flg )
{
	g_flg_rc_lex_err = flg;

	return g_flg_rc_lex_err;
}

/***************************************************************
* ����������Υ��顼���֤��֤�
* return : ���顼����
***************************************************************/

bool_t	get_rc_lex_err( void )
{
	return g_flg_rc_lex_err;
}

/***************************************************************
* �ե�����λ�����Ϥ򤹤�
* FILE *fp : �ե�����
* rc_union_t *u : ������ϤΥ����å�
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* return : �ȡ�����
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
* ������Ϥ���ä��� 1 �ȡ������᤹
* FILE *fp : �ե�����
* rc_union_t *u : ������ϤΥ����å�
* rc_token_t t : �ȡ�����
***************************************************************/

void	rc_unlex( FILE *fp, const rc_union_t *u, rc_token_t t )
{
	g_un_token = t;
	g_un_union = *u;
}

/***************************************************************
* �ե������ 1 ʸ����������Ϥ���
* FILE *fp : �ե�����
* rc_union_t *u : ������ϤΥ����å�
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* return : �ȡ�����
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
		/* ʸ����������λ� */
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
* �ե������ʸ����������Ϥ���
* FILE *fp : �ե�����
* rc_union_t *u : ������ϤΥ����å�
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* return : �ȡ�����
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
* �ե������ 8 �ʿ��������Ϥ���
* FILE *fp : �ե�����
* long len : ����ʸ����
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* return : ����
***************************************************************/

long	rc_lex_oct( FILE *fp, long len, bool_t flg_err_exit )
{
	return rc_lex_digit( fp, 8, len, flg_err_exit );
}

/***************************************************************
* �ե������ 10 �ʿ��������Ϥ���
* FILE *fp : �ե�����
* long len : ����ʸ����
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* return : ����
***************************************************************/

long	rc_lex_dec( FILE *fp, long len, bool_t flg_err_exit )
{
	return rc_lex_digit( fp, 10, len, flg_err_exit );
}

/***************************************************************
* �ե������ 16 �ʿ��������Ϥ���
* FILE *fp : �ե�����
* long len : ����ʸ����
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* return : ����
***************************************************************/

long	rc_lex_hex_dec( FILE *fp, long len, bool_t flg_err_exit )
{
	return rc_lex_digit( fp, 16, len, flg_err_exit );
}

/***************************************************************
* �ե������ n �ʿ��������Ϥ���
* FILE *fp : �ե�����
* long base : ���
* long len : ����ʸ����
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* return : ����
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
* �ե�����μ��̻Ҥ������Ϥ���
* FILE *fp : �ե�����
* rc_union_t *u : ������ϤΥ����å�
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
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
* �ե����뤫�� 1 ʸ���ɤ߹���
* FILE *fp : �ե�����
* bool_t flg_chk_eof : �ե�����ν���������å����뤫?
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* return : �ɤ߹����ʸ��
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
* ������Ϥ���ä��� 1 ʸ���᤹
* FILE *fp : �ե�����
* long c : �᤹ʸ��
***************************************************************/

void	rc_lex_ungetc( FILE *fp, long c )
{
	if( c == '\n' )
		dec_rc_lex_line();

	un_load_crypt_c( fp, c );
}

/***************************************************************
* �Хå��åס��ե������̾�����դ��Ѥ���
* char *fname : �ե�����̾
* return : �դ��Ѥ�����?
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
* ����ǥå������饢�󥫡����������Ѵ�
* long idx : ����ǥå���
* return : ���󥫡�������
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
* ���󥫡����������饤��ǥå������Ѵ�
* chr_kind_t k : ���󥫡�������
* return : ����ǥå���
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
* ����ǥå������饭��饯�����μ�����Ѵ�
* long idx : ����ǥå���
* return : ����饯�����μ���
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
* ����饯�����μ��फ�饤��ǥå������Ѵ�
* chr_kind_t k : ����饯�����μ���
* return : ����ǥå���
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
* ����ǥå���������С������֤��Ѵ�
* long idx : ����ǥå���
* return : ���С�������
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
* ���С������֤��饤��ǥå������Ѵ�
* position_kind_t k : ���С������֤μ���
* return : ����ǥå���
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
* ����ǥå�������ᥤ���²���Ѵ�
* long idx : ����ǥå���
* return : �ᥤ���²
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
* �ᥤ���²���饤��ǥå������Ѵ�
* main_race_t k : �ᥤ���²
* return : ����ǥå���
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
* ����ǥå������饵�ּ�²���Ѵ�
* long idx : ����ǥå���
* return : ���ּ�²
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
* ���ּ�²���饤��ǥå������Ѵ�
* sub_race_t k : ���ּ�²
* return : ����ǥå���
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
* ����ǥå����������̤��Ѵ�
* long idx : ����ǥå���
* return : ����
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
* ���̤��饤��ǥå������Ѵ�
* sex_t k : ����
* return : ����ǥå���
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
* ����ǥå�������ǽ���ͤؤ��Ѵ��ơ��֥�����ǿ����֤�
* return : ���ǿ�
***************************************************************/

long	get_abl_kind_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_abl_trans_tab );
	max_idx /= sizeof( g_abl_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* ����ǥå�������ǽ���ͤ��Ѵ�
* long idx : ����ǥå���
* return : ǽ����
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
* ǽ���ͤ��饤��ǥå������Ѵ�
* abl_kind_t k : ǽ����
* return : ����ǥå���
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
* ����ǥå��������⤭���μ�����Ѵ�
* long idx : ����ǥå���
* return : �⤭���μ���
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
* �⤭���μ��फ�饤��ǥå������Ѵ�
* move_kind_t k : �⤭���μ���
* return : ����ǥå���
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
* ����ǥå��������⤭���ǡ����μ���ؤ��Ѵ��ơ��֥�����ǿ����֤�
* return : ���ǿ�
***************************************************************/

long	get_move_ls_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_move_ls_trans_tab );
	max_idx /= sizeof( g_move_ls_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* ����ǥå��������⤭���ǡ����μ�����Ѵ�
* long idx : ����ǥå���
* return : �⤭���ǡ����μ���
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
* �⤭���ǡ����μ��फ�饤��ǥå������Ѵ�
* move_ls_kind_t k : �⤭���ǡ����μ���
* return : ����ǥå���
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
* ����ǥå������饢���������Ѵ�
* long idx : ����ǥå���
* return : ���������
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
* ��������󤫤饤��ǥå������Ѵ�
* act_kind_t k : ���������
* return : ����ǥå���
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
* ����ǥå������饿�����åȤμ�����Ѵ�
* long idx : ����ǥå���
* return : �������åȤμ���
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
* �������åȤμ��फ�饤��ǥå������Ѵ�
* trgt_kind_t k : �������åȤμ���
* return : ����ǥå���
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
* ����ǥå�������ֹ礤���Ѵ�
* long idx : ����ǥå���
* return : �ֹ礤
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
* �ֹ礤���饤��ǥå������Ѵ�
* dist_t k : �ֹ礤
* return : ����ǥå���
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
* ����ǥå������饿�����åȤμ�����Ѵ�
* long idx : ����ǥå���
* return : �������åȤμ���
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
* �������åȤμ��फ�饤��ǥå������Ѵ�
* auto_mark_trgt_t k : �������åȤμ���
* return : ����ǥå���
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
* ����ǥå�������ֹ礤���Ѵ�
* long idx : ����ǥå���
* return : �ֹ礤
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
* �ֹ礤���饤��ǥå������Ѵ�
* auto_mark_dist_t k : �ֹ礤
* return : ����ǥå���
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
* ����ǥå�����������Ѵ�
* long idx : ����ǥå���
* return : ���
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
* ��狼�饤��ǥå������Ѵ�
* auto_mark_act_t k : ���
* return : ����ǥå���
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
* ����ǥå�����������Ѵ�
* long idx : ����ǥå���
* return : ���
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
* ��狼�饤��ǥå������Ѵ�
* auto_mark_cond_t k : ���
* return : ����ǥå���
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
* ����ǥå�������ǥե���Ȥμ�����Ѵ�
* long idx : ����ǥå���
* return : �ǥե���Ȥμ���
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
* �ǥե���Ȥμ��फ�饤��ǥå������Ѵ�
* dflt_auto_mark_t k : �ǥե���Ȥμ���
* return : ����ǥå���
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
* ����ǥå�������ȿ�����Ѵ�
* long idx : ����ǥå���
* return : ȿ��
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
* ȿ�����饤��ǥå������Ѵ�
* attitude_t k : ȿ��
* return : ����ǥå���
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
* ����ǥå������饢���ƥ�μ�����Ѵ�
* long idx : ����ǥå���
* return : �����ƥ�μ���
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
* �����ƥ�μ��फ�饤��ǥå������Ѵ�
* item_kind_t k : �����ƥ�μ���
* return : ����ǥå���
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
* ����ǥå������饭���������ƥ�μ�����Ѵ�
* long idx : ����ǥå���
* return : �����������ƥ�μ���
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
* �����������ƥ�μ��फ�饤��ǥå������Ѵ�
* star_drop_kind_t k : �����������ƥ�μ���
* return : ����ǥå���
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
* ����ǥå����������μ�����Ѵ�
* long idx : ����ǥå���
* return : ���μ���
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
* ���μ��फ�饤��ǥå������Ѵ�
* wpn_kind_t k : ���μ���
* return : ����ǥå���
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
* ����ǥå�������ݤμ�����Ѵ�
* long idx : ����ǥå���
* return : �ݤμ���
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
* �ݤμ��फ�饤��ǥå������Ѵ�
* bow_kind_t k : �ݤμ���
* return : ����ǥå���
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
* ����ǥå��������ɶ�μ�����Ѵ�
* long idx : ����ǥå���
* return : �ɶ�μ���
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
* �ɶ�μ��फ�饤��ǥå������Ѵ�
* armor_kind_t k : �ɶ�μ���
* return : ����ǥå���
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
* ����ǥå������� RAF ���μ�����Ѵ�
* long idx : ����ǥå���
* return : �ɶ�μ���
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
* RAF ���μ��फ�饤��ǥå������Ѵ�
* wpn_kind_t k : �ɶ�μ���
* return : ����ǥå���
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
* ����ǥå������� RAF �ɶ�μ�����Ѵ�
* long idx : ����ǥå���
* return : �ɶ�μ���
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
* RAF �ɶ�μ��फ�饤��ǥå������Ѵ�
* armor_kind_t k : �ɶ�μ���
* return : ����ǥå���
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
* ����ǥå����������μ���ؤ��Ѵ��ơ��֥�����ǿ����֤�
* return : ���ǿ�
***************************************************************/

long	get_potion_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_potion_trans_tab );
	max_idx /= sizeof( g_potion_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* ����ǥå����������μ�����Ѵ�
* long idx : ����ǥå���
* return : ���μ���
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
* ���μ��फ�饤��ǥå������Ѵ�
* potion_kind_t k : ���μ���
* return : ����ǥå���
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
* ����ǥå������鴬ʪ�μ���ؤ��Ѵ��ơ��֥�����ǿ����֤�
* return : ���ǿ�
***************************************************************/

long	get_scroll_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_scroll_trans_tab );
	max_idx /= sizeof( g_scroll_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* ����ǥå������鴬ʪ�μ�����Ѵ�
* long idx : ����ǥå���
* return : ��ʪ�μ���
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
* ��ʪ�μ��फ�饤��ǥå������Ѵ�
* scroll_kind_t k : ��ʪ�μ���
* return : ����ǥå���
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
* ����ǥå��������μ�����Ѵ�
* long idx : ����ǥå���
* return : ��μ���
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
* ��μ��फ�饤��ǥå������Ѵ�
* stick_kind_t k : ��μ���
* return : ����ǥå���
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
* ����ǥå������饢��������μ�����Ѵ�
* long idx : ����ǥå���
* return : ����������μ���
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
* ����������μ��फ�饤��ǥå������Ѵ�
* acce_kind_t k : ����������μ���
* return : ����ǥå���
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
* ����ǥå���������ؤμ�����Ѵ�
* long idx : ����ǥå���
* return : ���ؤμ���
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
* ���ؤμ��फ�饤��ǥå������Ѵ�
* ring_kind_t k : ���ؤμ���
* return : ����ǥå���
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
* ����ǥå����������μ�����Ѵ�
* long idx : ����ǥå���
* return : ����μ���
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
* ����μ��फ�饤��ǥå������Ѵ�
* amulet_kind_t k : ����μ���
* return : ����ǥå���
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
* ����ǥå���������ؤμ�����Ѵ�
* long idx : ����ǥå���
* return : ���ؤμ���
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
* ���ؤμ��फ�饤��ǥå������Ѵ�
* necklace_kind_t k : ���ؤμ���
* return : ����ǥå���
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
* ����ǥå�������ڴ�μ�����Ѵ�
* long idx : ����ǥå���
* return : �ڴ�μ���
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
* �ڴ�μ��फ�饤��ǥå������Ѵ�
* inst_kind_t k : �ڴ�μ���
* return : ����ǥå���
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
* ����ǥå���������μ�����Ѵ�
* long idx : ����ǥå���
* return : ���μ���
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
* ���μ��फ�饤��ǥå������Ѵ�
* anthology_kind_t k : ���μ���
* return : ����ǥå���
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
* ����ǥå�������������μ�����Ѵ�
* long idx : ����ǥå���
* return : ������μ���
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
* ������μ��फ�饤��ǥå������Ѵ�
* light_kind_t k : ������μ���
* return : ����ǥå���
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
* ����ǥå�������˾�ߤ�����μ�����Ѵ�
* long idx : ����ǥå���
* return : ˾�ߤ�����μ���
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
* ˾�ߤ�����μ��फ�饤��ǥå������Ѵ�
* wish_level_t k : ˾�ߤ�����μ���
* return : ����ǥå���
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
* ����ǥå������鿩���μ�����Ѵ�
* long idx : ����ǥå���
* return : �����μ���
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
* �����μ��फ�饤��ǥå������Ѵ�
* food_kind_t k : �����μ���
* return : ����ǥå���
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
* ����ǥå����������μ�����Ѵ�
* long idx : ����ǥå���
* return : ����μ���
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
* ����μ��फ�饤��ǥå������Ѵ�
* tobacco_kind_t k : ����μ���
* return : ����ǥå���
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
* ����ǥå����������Υ֥��ɤ��Ѵ�
* long idx : ����ǥå���
* return : ����Υ֥���
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
* ����Υ֥��ɤ��饤��ǥå������Ѵ�
* tobacco_brand_t k : ����Υ֥��ɤμ���
* return : ����ǥå���
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
* ����ǥå�������ѥ��פμ�����Ѵ�
* long idx : ����ǥå���
* return : �ѥ��פμ���
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
* �ѥ��פμ��फ�饤��ǥå������Ѵ�
* pipe_kind_t k : �ѥ��פμ���
* return : ����ǥå���
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
* ����ǥå�������쥢�����å��μ�����Ѵ�
* long idx : ����ǥå���
* return : �쥢�����å��μ���
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
* �쥢�����å��μ��फ�饤��ǥå������Ѵ�
* rare_goods_kind_t k : �쥢�����å��μ���
* return : ����ǥå���
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
* ����ǥå������饳����μ�����Ѵ�
* long idx : ����ǥå���
* return : ������μ���
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
* ������μ��फ�饤��ǥå������Ѵ�
* coin_kind_t k : ������μ���
* return : ����ǥå���
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
* ����ǥå��������ʸ�μ���ؤ��Ѵ��ơ��֥�����ǿ����֤�
* return : ���ǿ�
***************************************************************/

long	get_spell_kind_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_spell_trans_tab );
	max_idx /= sizeof( g_spell_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* ����ǥå��������ʸ�μ�����Ѵ�
* long idx : ����ǥå���
* return : ��ʸ�μ���
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
* ��ʸ�μ��फ�饤��ǥå������Ѵ�
* spell_kind_t k : ��ʸ�μ���
* return : ����ǥå���
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
* ����ǥå��������󥹥����μ�����Ѵ�
* long idx : ����ǥå���
* return : ��󥹥����μ���
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
* ��󥹥����μ��फ�饤��ǥå������Ѵ�
* mnstr_kind_t k : ��󥹥����μ���
* return : ����ǥå���
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
* ����ǥå�������櫤μ�����Ѵ�
* long idx : ����ǥå���
* return : 櫤μ���
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
* 櫤μ��फ�饤��ǥå������Ѵ�
* trap_kind_t k : 櫤μ���
* return : ����ǥå���
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
* ����ǥå���������̤μ�����Ѵ�
* long idx : ����ǥå���
* return : ���̤μ���
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
* ���̤μ��फ�饤��ǥå������Ѵ�
* fx_kind_t k : ���̤μ���
* return : ����ǥå���
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
* ����ǥå����������μ�����Ѵ�
* long idx : ����ǥå���
* return : ����μ���
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
* ����μ��फ�饤��ǥå������Ѵ�
* request_kind_t k : ����μ���
* return : ����ǥå���
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
* ����ǥå�������ɲ��������μ���ؤ��Ѵ��ơ��֥�����ǿ����֤�
* return : ���ǿ�
***************************************************************/

long	get_stay_inn_kind_trans_tab_max_n( void )
{
	long	max_idx;

	max_idx = sizeof( g_stay_inn_kind_trans_tab );
	max_idx /= sizeof( g_stay_inn_kind_trans_tab[0] );

	return max_idx;
}

/***************************************************************
* ����ǥå�������ɲ��������μ�����Ѵ�
* long idx : ����ǥå���
* return : �ɲ��������μ���
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
* �ɲ��������μ��फ�饤��ǥå������Ѵ�
* stay_inn_kind_t k : �ɲ��������μ���
* return : ����ǥå���
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
* �ե�����򥳥ԡ�����
* const char *src : ���ԡ����ե�ѥ�
* const char *dst : ���ԡ���ե�ѥ�
* return : ���顼��̵���ä���?
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
* �ѥ��ȥե�����̾��Ĥʤ��ƥե�ѥ��ˤ���
* char *path : �ѥ�
* char *file : �ե�����̾
* return : �ե�ѥ�
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
* �ե����뤬¸�ߤ��뤫Ĵ�٤�
* char *s : �ե�����̾
* return : ¸�ߤ�����?
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
* �ǥ��쥯�ȥ꤬¸�ߤ��뤫Ĵ�٤�
* char *s : �ǥ��쥯�ȥ�̾
* return : ¸�ߤ�����?
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
* �ǥ��쥯�ȥ�򷡤�
* char *s : �ǥ��쥯�ȥ�̾
* return : ���顼��̵���ä���?
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
* �ǥ��쥯�ȥ�� 1 �ķ���
* char *s : �ǥ��쥯�ȥ�̾
* return : ���顼��̵���ä���?
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
* ʸ�����������Ȥʤ饨�������פ���
* const long c : �Ѵ�����ʸ��
* return : �Ѵ����ʸ����
***************************************************************/

char	*cv_esc_quote_c( const long c )
{
	static char	buf[TOKEN_MAX_LEN + 1];

	buf[0] = (unsigned char)c;
	buf[1] = '\0';

	return( cv_esc_quote_str( buf ) );
}

/***************************************************************
* ʸ������Υ������Ȥ򥨥������פ���
* const char *str : �Ѵ�����ʸ����
* return : �Ѵ����ʸ����
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
* ʸ������Υ���ȥ��롦�����ɤ򥨥������פ���
* �������ȤϽ������ʤ�
* const char *str : �Ѵ�����ʸ����
* return : �Ѵ����ʸ����
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
* �Ź沽�����������
* long n : ����μ�
* return : ����μ�
***************************************************************/

long	srandm_crypt( long n )
{
	g_randm_crypt_seed = n;

	return g_randm_crypt_seed;
}

/***************************************************************
* ʸ����Ź沽����
* long c : ʸ��
* return : �Ź沽����ʸ��
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
* ������Ϥȹ�ʸ���Ϥ�����
* char *path : �ե�����Υե�ѥ�
* bool_t flg_txt : �ƥ����ȡ��⡼�ɤ�?
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
* �Ź沽�⡼�ɤ�����
* bool_t flg_txt : �ƥ����ȡ��⡼�ɤ�?
***************************************************************/

void	set_flg_crypt_txt( bool_t flg_txt )
{
	g_flg_crypt_txt = flg_txt;
}

/***************************************************************
* �Ź沽�⡼�ɤ����ꤷ�ƥ��ɳ���
* FILE *fp : �ե�����
* bool_t flg_txt : �ƥ����ȡ��⡼�ɤ�?
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
* �Ź沽�⡼�ɤ����ꤷ�ƥ����ֳ���
* FILE *fp : �ե�����
* bool_t flg_txt : �ƥ����ȡ��⡼�ɤ�?
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
* �������ν����
***************************************************************/

void	reset_save_crypt_tab( void )
{
	g_tab_lev = 0;
}

/***************************************************************
* ������������
* FILE *fp : �ե�����
* long n : ������������������
* return : ������������������
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
* �������դ��� printf
* FILE *fp : �ե�����
* const char *s : �ե����ޥå�
* ... : ����
* return : ������������������
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
* �Ź沽ʸ�������
* FILE *fp : �ե�����
* const char *s : �ե����ޥå�
* ... : ����
* return : ������������������
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
* �Ź沽ʸ��������
* FILE *fp : �ե�����
* char *buf : ʸ�����������
* long n : ʸ����κ���Ĺ
* return : ʸ�����Ĺ��
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
* �Ź沽ʸ������
* FILE *fp : �ե�����
* return : ���Ϥ���ʸ��
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
* �Ź沽ʸ�����Ϥμ��ä�
* FILE *fp : �ե�����
* long c : ���ä�ʸ��
***************************************************************/

void	un_load_crypt_c( FILE *fp, long c )
{
	g_un_c = c;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_gfile_c( void )
{
}
