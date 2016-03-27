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
* $Id: gf-outmap.c,v 1.7 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �ե����������� (�ޥåפ����)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* �ޥåפ���Ϥ���ե�����̾��桼���������Ϥ���
* char *s : �ե�����̾��������
* return : �ե�����̾(����󥻥�ʤ� NULL)
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

	/* �ǥե���ȤΥե�����̾������ */
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

	/* �ե�����̾������ */
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

	/* �����˽��Ϥ��뤫��ǧ��Ȥ� */
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
* �ޥåפ�ե�����˽��Ϥ���
* return : ���顼��̵���ä���?
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
* ���꡼�������å�
***************************************************************/

void	check_memory_gf_outmap_c( void )
{
}
