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
* $Id: gf-gconf.c,v 1.8 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �ե����������� (����ե��å�����)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* ����ե��å�����Υ���
* char *path : �ե�����Υե�ѥ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_graph_conf( char *path )
{
	ver_t	ver;
	FILE	*fp;
	bool_t	flg_err;

	flg_err = TRUE;

	/* �ե�����򥪡��ץ� */

	fp = fopen( path, "r" );
	if( fp == NULL )
		return FALSE;

	reset_load_save( path, TRUE );

	/* �إå����ɤ߹��� */

	if( !load_graph_conf_head( fp, &ver ) ){
		fclose( fp );
		return TRUE;
	}

	/* �С������Υ����å� */

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

	/* �ǡ������ɤ߹��� */

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

	/* �ե�����򥯥��� */

	if( fclose( fp ) == EOF )
		return TRUE;

	/* ���顼����å�������ɽ�� */

	if( flg_err ){
		print_err( MSG_ERR_RC );
		print_err( "'%s'", get_rc_lex_file_name() );
	}

	return TRUE;
}

/***************************************************************
* ����ե��å�����Υإå����Υ���
* FILE *fp : �ե�����
* ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
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

	/* �С�����󡦥����å� */

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
* ����ե��å�����Υǡ����Υ���(�С������ 1)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
***************************************************************/

void	load_graph_conf_data_ver_1( FILE *fp, const ver_t *ver )
{
	while( 1 ){
		if( !load_graph_conf_parse_ver_1( fp, ver ) )
			break;
	}
}

/***************************************************************
* ����ե��å�����Υѡ���(�С������ 1)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
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
* ����ե��å�����Υ֥�å��򳫻�
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : �֥�å�̾
* long val : ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_graph_conf_block_begin(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
)
{
	return call_sel_conf_eval_block_begin();
}

/***************************************************************
* ����ե��å�����Υ֥�å���λ
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : �֥�å�̾
* long val : ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_graph_conf_block_end(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
)
{
	return call_sel_conf_eval_block_end();
}

/***************************************************************
* ����ե��å�������ѿ��˿��ͤ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : �ѿ�̾
* long val : ��
* return : ���顼��̵���ä���?
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
* ����ե��å�������ѿ���ʸ���������
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : �ѿ�̾
* long val : ��
* return : ���顼��̵���ä���?
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
* ���꡼�������å�
***************************************************************/

void	check_memory_gf_gconf_c( void )
{
}
