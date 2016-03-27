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
* $Id: gf-crsr.c,v 1.9 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �ե����������� (�������롦�ѥ�����)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* �������롦�ѥ�����Υ���
* crsr_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* long *max_n : �ѥ�����κ�����γ�Ǽ��
* return : ���顼��̵���ä���?
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
* �������롦�ѥ�����Υإå��Υ���
* FILE *fp : �ե�����
* crsr_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* return : ���顼��̵���ä���?
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
* �������롦�ѥ�����Τ���¾�Υ���
* FILE *fp : �ե�����
* crsr_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* return : ���顼��̵���ä���?
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
* �������롦�ѥ�����Υǡ����Υ���
* FILE *fp : �ե�����
* crsr_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* return : ���顼��̵���ä���?
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
* �������롦�ѥ�����Υ�����
* crsr_ptn_t *ptn : �ѥ����󡦥ǡ����γ�Ǽ��
* long max_n : �ѥ�����κ����
* return : ���顼��̵���ä���?
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
* �������롦�ѥ�����ΥХå��å�
***************************************************************/

void	back_up_crsr_ptn( void )
{
	rename_back_up_file( path_name_crsr_ptn );
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_gf_crsr_c( void )
{
}
