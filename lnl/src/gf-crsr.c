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
* $Id: gf-crsr.c,v 1.9 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ファイル入出力 (カーソル・パターン)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* カーソル・パターンのロード
* crsr_ptn_t *ptn : パターン・データの格納先
* long *max_n : パターンの最大数の格納先
* return : エラーが無かったか?
***************************************************************/

bool_t	load_crsr_ptn( crsr_ptn_t *ptn, long *max_n )
{
	FILE	*fp;
	bool_t	ret;

	*max_n = 0;
	ret = TRUE;

	if( !chk_exist_file( path_name_crsr_ptn ) )
		return FALSE;

	fp = fopen( path_name_crsr_ptn, "r" );
	if( fp == NULL )
		return FALSE;

	reset_load_save( path_name_crsr_ptn, TRUE );

	do {
		if( !load_crsr_ptn_head( fp, ptn ) ){
			ret = FALSE;
			break;
		}
		for( *max_n = 0; *max_n < CRSR_PTN_MAX_N; (*max_n)++ ){
			if( !load_crsr_ptn_misc( fp, &(ptn[*max_n]) ) )
				break;
			if( !load_crsr_ptn_data( fp, &(ptn[*max_n]) ) ){
				ret = FALSE;
				break;
			}
		}

		break;
	} while( 0 );

	if( fclose( fp ) == EOF )
		return FALSE;

	return ret;
}

/***************************************************************
* カーソル・パターンのヘッダのロード
* FILE *fp : ファイル
* crsr_ptn_t *ptn : パターン・データの格納先
* return : エラーが無かったか?
***************************************************************/

bool_t	load_crsr_ptn_head( FILE *fp, crsr_ptn_t *ptn )
{
	const long	len_head = str_len_std( STR_CRSR_PTN_HEAD );
	char	*s;

	while( 1 ){
		s = load_line_skip_spc( fp, TRUE );
		if( strncmp( s, STR_CRSR_PTN_HEAD, len_head ) == 0 )
			break;
	}

	return TRUE;
}

/***************************************************************
* カーソル・パターンのその他のロード
* FILE *fp : ファイル
* crsr_ptn_t *ptn : パターン・データの格納先
* return : エラーが無かったか?
***************************************************************/

bool_t	load_crsr_ptn_misc( FILE *fp, crsr_ptn_t *ptn )
{
	char	*s;

	s = load_line_skip_spc( fp, TRUE );
	if( strchr( s, '}' ) != NULL )
		return FALSE;

	s = load_line_skip_spc( fp, TRUE );
	sscanf( s, "%ld, %ld", &(ptn->x), &(ptn->y) );

	s = load_line_skip_spc( fp, TRUE );	/* "size" */

	s = load_line_skip_spc( fp, TRUE );
	s = strchr( s, '\'' );
	if( s == NULL )
		return FALSE;
	s++;
	ptn->transmit_chr = s[0];

	return TRUE;
}

/***************************************************************
* カーソル・パターンのデータのロード
* FILE *fp : ファイル
* crsr_ptn_t *ptn : パターン・データの格納先
* return : エラーが無かったか?
***************************************************************/

bool_t	load_crsr_ptn_data( FILE *fp, crsr_ptn_t *ptn )
{
	char	*s;
	long	x, y, idx;

	while( 1 ){
		s = load_line_skip_spc( fp, TRUE );
		if( strchr( s, '{' ) != NULL )
			break;
	}

	y = 0;
	while( 1 ){
		if( y >= CRSR_PTN_MAX_Y_LEN )
			break;

		s = load_line_skip_spc( fp, TRUE );
		if( strchr( s, '}' ) != NULL )
			break;

		s = strchr( s, '\"' );
		if( s == NULL )
			continue;
		s++;

		idx = 0;
		for( x = 0; x < CRSR_PTN_MAX_X_LEN * 2; x++ ){
			if( s[idx] == '\"' )
				break;
			if( s[idx] == '\\' )
				idx++;

			ptn->face[y][x] = s[idx];
			idx++;
		}
		ptn->face[y][x] = '\0';
		y++;
	}

	s = load_line_skip_spc( fp, TRUE );	/* "}," */

	return TRUE;
}

/***************************************************************
* カーソル・パターンのセーブ
* crsr_ptn_t *ptn : パターン・データの格納元
* long max_n : パターンの最大数
* return : エラーが無かったか?
***************************************************************/

bool_t	save_crsr_ptn( crsr_ptn_t *ptn, long max_n )
{
	FILE	*fp;
	long	x, y;
	long	i;

	fp = fopen( path_name_crsr_ptn, "w" );
	if( fp == NULL )
		return FALSE;

	reset_load_save( path_name_crsr_ptn, TRUE );

	/* header */

	fputs( "#ifndef\tCRSR_PTN_H\n", fp );
	fputs( "#define\tCRSR_PTN_H\n", fp );
	fputs( "\n", fp );
	fputs( "crsr_ptn_t\tcrsr_ptn_dflt[] = {\n", fp );

	for( i = 0; i < max_n; i++ ){
		/* size */

		fputs( "\t{\n", fp );
		fprintf( fp, "\t\t%ld, %ld,\t/* offset x, y */\n",
				ptn[i].x, ptn[i].y );
		fprintf( fp, "\t\t%ld, %ld,\t/* width, height */\n",
				ptn[i].x_len, ptn[i].y_len );
		fprintf( fp, "\t\t'%c',\t/* transmit char */\n",
				(int)ptn[i].transmit_chr );

		/* pattern */

		fputs( "\t\t{\n", fp );
		for( y = 0; y < ptn[i].y_len; y++ ){
			fputs( "\t\t\t\"", fp );
			for( x = 0; x < ptn[i].x_len * 2; x++ ){
				long	c;

				c = ptn[i].face[y][x];

				if( c == '\"' )
					fputc( '\\', fp );

				fputc( c, fp );

				if( c == '\\' )
					fputc( '\\', fp );
			}
			fputs( "\",\n", fp );
		}
		fputs( "\t\t},\n", fp );
		fputs( "\t},\n", fp );
	}

	/* footer */

	fputs( "};\n\n", fp );
	fputs( "#endif\t/* CRSR_PTN_H */\n", fp );

	/* end */

	if( fclose( fp ) == EOF )
		return FALSE;

	return TRUE;
}

/***************************************************************
* カーソル・パターンのバッカップ
***************************************************************/

void	back_up_crsr_ptn( void )
{
	rename_back_up_file( path_name_crsr_ptn );
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_gf_crsr_c( void )
{
}
