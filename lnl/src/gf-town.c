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
* $Id: gf-town.c,v 1.7 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �ե����������� (���ѥ�����)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* ���ѥ�����Υ���
* town_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_town_ptn( town_ptn_t *ptn )
{
	FILE	*fp;

	if( ptn == NULL )
		return FALSE;

	if( !chk_exist_file( path_name_town_ptn ) )
		set_town_ptn_dflt( ptn );

	fp = fopen( path_name_town_ptn, "r" );
	if( fp == NULL )
		return FALSE;

	reset_load_save( path_name_town_ptn, TRUE );

	do {
		if( !load_town_ptn_head( fp, ptn ) )
			break;
		if( !load_town_ptn_col( fp, ptn ) )
			break;
		if( !load_town_ptn_map( fp, ptn ) )
			break;

		/* ���� */

		if( fclose( fp ) == EOF )
			return FALSE;

		return TRUE;
	} while( 0 );

	/* ���顼 */

	if( fclose( fp ) == EOF )
		return FALSE;

	back_up_town_ptn();
	set_town_ptn_dflt( ptn );
	save_town_ptn( ptn );

	return FALSE;
}

/***************************************************************
* ���ѥ�����Υإå��Υ���
* FILE *fp : �ե�����
* town_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_town_ptn_head( FILE *fp, town_ptn_t *ptn )
{
	long	c;
	char	*s;

	if( !set_town_ptn_init( ptn ) )
		return FALSE;

	while( 1 ){
		c = load_char( fp, TRUE );
		if( c == '\"' )
			break;
	}

	s = load_line( fp, TRUE );
	if( !set_town_ptn_head( ptn, s ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ���ѥ�����ο��ơ��֥�Υ���
* FILE *fp : �ե�����
* town_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_town_ptn_col( FILE *fp, town_ptn_t *ptn )
{
	long	i;
	long	c;
	char	*s;

	for( i = 0; i < ptn->col_n; i++ ){
		while( 1 ){
			c = load_char( fp, TRUE );
			if( c == '\"' )
				break;
		}

		s = load_line( fp, TRUE );
		if( !set_town_ptn_col( ptn, s ) )
			return FALSE;
	}

	if( !set_town_ptn_col_count( ptn ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ���ѥ�����ΥޥåפΥ���
* FILE *fp : �ե�����
* town_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_town_ptn_map( FILE *fp, town_ptn_t *ptn )
{
	long	i;
	char	*s, *rchr;
	long	len;

	for( i = 0; i < MAP_MAX_Y; i++ ){
		while( 1 )
			if( load_char( fp, TRUE ) == '\"' )
				break;

		s = load_line( fp, TRUE );

		rchr = strrchr( s, '\"' );
		if( rchr == NULL ){
			print_err( MSG_S, MSG_ERR_LOAD_WQUOTE );
			return FALSE;
		}
		len = rchr - s;
		if( len != MAP_MAX_X * ptn->col_str_len ){
			print_err( MSG_ERR_LOAD_LINE_LEN,
					len, MAP_MAX_X * ptn->col_str_len );
			return FALSE;
		}

		if( !set_town_ptn_map( ptn, s, i ) )
			return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ���ѥ�����Υ�����
* town_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_town_ptn( town_ptn_t *ptn )
{
	long	col_tab_max_n;
	FILE	*fp;
	long	col_n;
	long	i, j;

	col_tab_max_n = get_town_ptn_col_tab_max_n();

	if( (ptn->col_str_len != 1) && (ptn->col_str_len != 2) )
		return FALSE;

	fp = fopen( path_name_town_ptn, "w" );
	if( fp == NULL )
		return FALSE;

	reset_load_save( path_name_town_ptn, TRUE );

	/* header */

	if( ptn->col_str_len == 1 )
		col_n = ptn->col_n;
	else if( ptn->col_str_len == 2 )
		col_n = col_tab_max_n;
	else
		col_n = 0;

	fputs( "/* XPM */\n", fp );
	fputs( "static char\t*town_ptn_xpm[] = {\n", fp );
	fprintf( fp, "\"%d %d %ld %ld\",\n",
			MAP_MAX_X, MAP_MAX_Y, col_n + 1, ptn->col_str_len );

	/* color */

	if( ptn->col_str_len == 1 ){
		fputs( "\" \tc None\",\n", fp );
		save_town_ptn_col_1byte( fp, ptn );
	} else if( ptn->col_str_len == 2 ){
		fputs( "\"  \tc None\",\n", fp );
		save_town_ptn_col_2byte( fp );
	}

	/* data */

	for( i = 0; i < MAP_MAX_Y; i++ ){
		fputs( "\"", fp );
		for( j = 0; j < MAP_MAX_X; j++ ){
			if( ptn->col_str_len == 1 ){
				fprintf( fp, "%c", ptn->map_mjr[i][j] );
			} else if( ptn->col_str_len == 2 ){
				fprintf( fp, "%c%c",
						ptn->map_mjr[i][j],
						ptn->map_mnr[i][j] );
			}
		}
		fputs( "\",\n", fp );
	}
	fputs( "};\n", fp );

	/* end */

	if( fclose( fp ) == EOF )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ���ѥ�����ο��ơ��֥�Υ�����(1 �Х�����)
* FILE *fp : �ե�����
* town_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
***************************************************************/

void	save_town_ptn_col_1byte( FILE *fp, town_ptn_t *ptn )
{
	town_ptn_col_tab_t	*col_tab;
	long	col_tab_max_n;
	long	i, j;

	col_tab = get_town_ptn_col_tab();
	col_tab_max_n = get_town_ptn_col_tab_max_n();

	for( i = 0; i < TOWN_PTN_COL_MAX_N; i++){
		if( ptn->col_mjr[i] == '\0' )
			continue;
		if( ptn->col_mnr[i] == '\0' )
			continue;

		for( j = 0; j < col_tab_max_n; j++){
			if( col_tab[j].mjr != ptn->col_mjr[i] )
				continue;
			if( col_tab[j].mnr != ptn->col_mnr[i] )
				continue;

			fprintf( fp, "\"%c\tc #%06lx\",\n", (char)i,
					col_tab[j].col_code );
		}
	}
}

/***************************************************************
* ���ѥ�����ο��ơ��֥�Υ�����(2 �Х�����)
* FILE *fp : �ե�����
* town_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
***************************************************************/

void	save_town_ptn_col_2byte( FILE *fp )
{
	town_ptn_col_tab_t	*col_tab;
	long	col_tab_max_n;
	long	i;

	col_tab = get_town_ptn_col_tab();
	col_tab_max_n = get_town_ptn_col_tab_max_n();

	for( i = 0; i < col_tab_max_n; i++){
		fprintf( fp, "\"%c%c\tc #%06lx\",\n",
				col_tab[i].mjr, col_tab[i].mnr,
				col_tab[i].col_code );
	}
}

/***************************************************************
* ���ѥ�����ΥХå��å�
***************************************************************/

void	back_up_town_ptn( void )
{
	rename_back_up_file( path_name_town_ptn );
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_gf_town_c( void )
{
}
