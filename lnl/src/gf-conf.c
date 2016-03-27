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
* $Id: gf-conf.c,v 1.38 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �ե����������� (����ե�����)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* ����ե�����Υ���
* return : ����ե����뤬¸�ߤ�����?
***************************************************************/

bool_t	load_game_conf( void )
{
	ver_t	ver;
	FILE	*fp;
	bool_t	flg_err;

	flg_err = TRUE;

	/* ����ե����뤬¸�ߤ��뤫�����å� */

	if( !chk_exist_file( path_name_game_conf ) )
		return FALSE;

	/* �ե�����򥪡��ץ� */

	fp = fopen( path_name_game_conf, "r" );
	if( fp == NULL )
		return FALSE;

	reset_load_save( path_name_game_conf, TRUE );

	/* �إå����ɤ߹��� */

	if( !load_game_conf_head( fp, &ver ) ){
		fclose( fp );
		return TRUE;
	}

	/* �С������Υ����å� */

	if( chk_ver_new( &ver,
			GAME_CONF_VER_MJR,
			GAME_CONF_VER_MNR,
			GAME_CONF_VER_PAT ) ){
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_A,
				ver.mjr, ver.mnr, ver.pat );
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_B );

		fclose( fp );
		return TRUE;
	}

	/* �ǡ������ɤ߹��� */

	switch( ver.mjr ){
	case 1:
		load_game_conf_data_ver_1( fp, &ver );
		flg_err = get_rc_lex_err();
		break;
	default:
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_A,
				ver.mjr, ver.mnr, ver.pat );
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_B );

		flg_err = TRUE;
		break;
	}

	/* �С�����ʥå� */

	if( chk_ver_old( &ver, 1, 0, 15 ) )
		ver_up_game_conf_1_0_15();

	/* �ե�����򥯥��� */

	if( fclose( fp ) == EOF )
		return TRUE;

	/* ���ޥ�ɡ��饤�������ͥ�� */

	overwrite_arg();

	/* ���顼����å�������ɽ�� */

	if( flg_err ){
		print_msg( FLG_MSG_ERR, MSG_ERR_RC );
		print_msg( FLG_MSG_ERR, "'%s'", get_rc_lex_file_name() );
	}

	return TRUE;
}

/***************************************************************
* ����ե�����ΥС�������Ѵ�
***************************************************************/

void	ver_up_game_conf_1_0_15( void )
{
	ver_up_draw_ver_1_2_22();
}

/***************************************************************
* ����ե�����ΥС�������Ѵ�
***************************************************************/

void	ver_up_game_data_cnf_1_2_22( void )
{
	ver_up_draw_ver_1_2_22();
}

/***************************************************************
* ����ե�����Υإå����Υ���
* FILE *fp : �ե�����
* ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_head( FILE *fp, ver_t *ver )
{
	const long	len_head = str_len_std( STR_GAME_CONF_HEAD );
	char	*s;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	ver->mjr = 0;
	ver->mnr = 0;
	ver->pat = 0;

	s = load_line( fp, TRUE );
	if( strncmp( s, STR_GAME_CONF_HEAD, len_head ) != 0 ){
		print_lex_err( MSG_ERR_LOAD_GAME_HEAD );
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
* ����ե�����Υǡ����Υ���(�С������ 1)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
***************************************************************/

void	load_game_conf_data_ver_1( FILE *fp, const ver_t *ver )
{
	while( 1 ){
		if( !load_game_conf_parse_ver_1( fp, ver ) )
			break;
	}
}

/***************************************************************
* ����ե�����Υѡ���(�С������ 1)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_parse_ver_1( FILE *fp, const ver_t *ver )
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
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == RC_TOKEN_NUM)
			&& (t[3] == '\n') ){
		/* foo = n */

		if( !load_game_conf_set_val(
				fp, ver, flg_err_exit,
				u[0].str, u[2].n ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == RC_TOKEN_ADD_OP)
			&& (t[3] == RC_TOKEN_NUM)
			&& (t[4] == '\n') ){
		/* foo = - n */
		long	sg = +1;

		if( u[2].c == '-' )
			sg = -1;
		if( !load_game_conf_set_val(
				fp, ver, flg_err_exit,
				u[0].str, sg * u[3].n ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == RC_TOKEN_STR)
			&& (t[3] == '\n') ){
		/* foo = str */

		if( !load_game_conf_set_str(
				fp, ver, flg_err_exit,
				u[0].str, u[2].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_CHAR)
			&& (t[2] == RC_TOKEN_STR)
			&& (t[3] == '\n') ){
		/* foo c str */

		if( !load_game_conf_id_char_str(
				fp, ver, flg_err_exit,
				u[0].str, u[1].c, u[2].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_NUM)
			&& (t[2] == RC_TOKEN_STR)
			&& (t[3] == '\n') ){
		/* foo n str */

		if( !load_game_conf_id_num_str(
				fp, ver, flg_err_exit,
				u[0].str, u[1].n, u[2].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_STR)
			&& (t[2] == RC_TOKEN_NUM)
			&& (t[3] == RC_TOKEN_STR)
			&& (t[4] == '\n') ){
		/* foo str n str */

		if( !load_game_conf_id_str_num_str(
				fp, ver, flg_err_exit,
				u[0].str, u[1].str, u[2].n, u[3].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_CHAR)
			&& (t[2] == '\n') ){
		/* foo c */

		if( !load_game_conf_id_char(
				fp, ver, flg_err_exit,
				u[0].str, u[1].c ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == '{')
			&& (t[2] == '\n') ){
		/* foo { */

		if( !load_game_conf_id_brace(
				fp, ver, flg_err_exit,
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
* ����ե�������ѿ��˿��ͤ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : �ѿ�̾
* long val : ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_set_val(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
)
{
	long	i;

	if( strcmp( id, "clk_tck" ) == 0 ){
		return load_game_conf_clk_tck( id, val );

	} else if( strcmp( id, "screen_size_auto" ) == 0 ){
		return load_game_conf_screen_size_auto( id, val );

	} else if( strcmp( id, "screen_size_lines" ) == 0 ){
		return load_game_conf_screen_size_row( id, val );

	} else if( strcmp( id, "screen_size_column" ) == 0 ){
		return load_game_conf_screen_size_col( id, val );

	} else if( strcmp( id, "screen_size_row" ) == 0 ){
		return load_game_conf_screen_size_row( id, val );

	} else if( strcmp( id, "screen_size_message" ) == 0 ){
		return load_game_conf_screen_size_message( id, val );

	} else if( strcmp( id, "screen_resize_map" ) == 0 ){
		return load_game_conf_screen_resize_map( id, val );

	} else if( strcmp( id, "cursor_number_main" ) == 0 ){
		return load_game_conf_cursor_number_main( id, val );

	} else if( strcmp( id, "cursor_number_sub" ) == 0 ){
		return load_game_conf_cursor_number_sub( id, val );

	} else if( strcmp( id, "clear_key_buffer_every" ) == 0 ){
		return load_game_conf_clr_key_buf_every( id, val );

	} else if( strcmp( id, "clear_key_buffer_menu" ) == 0 ){
		return load_game_conf_clr_key_buf_menu( id, val );

	} else if( strcmp( id, "space_select" ) == 0 ){
		return load_game_conf_space_select( id, val );

	} else if( strcmp( id, "redraw_every_turn" ) == 0 ){
		return load_game_conf_redraw_every_turn( id, val );

	} else if( strcmp( id, "multiple_message_line" ) == 0 ){
		return load_game_conf_mul_line( id, val );

	} else if( strcmp( id, "status_bar_hint_character" ) == 0 ){
		return load_game_conf_stat_bar_hint_chr( id, val );

	} else if( strcmp( id, "status_bar_hint_object" ) == 0 ){
		return load_game_conf_stat_bar_hint_obj( id, val );

	} else if( strcmp( id, "move_cursor_to_default" ) == 0 ){
		return load_game_conf_move_crsr_dflt( id, val );

	} else if( strcmp( id, "double_click_wait" ) == 0 ){
		return load_game_conf_double_click_wait( id, val );

	} else if( strcmp( id, "music_volume" ) == 0 ){
		return load_game_conf_music_volume( id, val );

	} else if( strcmp( id, "sound_volume" ) == 0 ){
		return load_game_conf_sound_volume( id, val );

	} else if( strcmp( id, "joystick_number" ) == 0 ){
		return load_game_conf_joystick_number( id, val );

	} else if( strcmp( id, "vfx_member_cure" ) == 0 ){
		return load_game_conf_vfx_mbr( FLG_VFX_MBR_CURE, val );

	} else if( strcmp( id, "vfx_member_damage" ) == 0 ){
		return load_game_conf_vfx_mbr( FLG_VFX_MBR_DAM, val );

	} else if( strcmp( id, "vfx_member_critical" ) == 0 ){
		return load_game_conf_vfx_mbr( FLG_VFX_MBR_CRTCL, val );

	} else if( strcmp( id, "vfx_member_arrow" ) == 0 ){
		return load_game_conf_vfx_mbr( FLG_VFX_MBR_ARW, val );

	} else if( strcmp( id, "vfx_monster_cure" ) == 0 ){
		return load_game_conf_vfx_mnstr( FLG_VFX_MNSTR_CURE, val );

	} else if( strcmp( id, "vfx_monster_damage" ) == 0 ){
		return load_game_conf_vfx_mnstr( FLG_VFX_MNSTR_DAM, val );

	} else if( strcmp( id, "vfx_monster_critical" ) == 0 ){
		return load_game_conf_vfx_mnstr( FLG_VFX_MNSTR_CRTCL, val );

	} else if( strcmp( id, "vfx_monster_arrow" ) == 0 ){
		return load_game_conf_vfx_mnstr( FLG_VFX_MNSTR_ARW, val );

	} else if( strcmp( id, "vfx_wait" ) == 0 ){
		return load_game_conf_vfx_wait( id, val );

	} else if( strcmp( id, "attribute_underline" ) == 0 ){
		return load_game_conf_attribute_underline( id, val );

	} else if( strcmp( id, "attribute_reverse" ) == 0 ){
		return load_game_conf_attribute_reverse( id, val );

	} else if( strcmp( id, "attribute_blink" ) == 0 ){
		return load_game_conf_attribute_blink( id, val );

	} else if( strcmp( id, "attribute_bold" ) == 0 ){
		return load_game_conf_attribute_bold( id, val );

	} else if( strcmp( id, "audio_buffer_size" ) == 0 ){
		return load_game_conf_audio_buf_siz( id, val );

	} else if( strcmp( id, "gnome" ) == 0 ){
		return load_game_conf_gnome( id, val );

	} else if( strcmp( id, "set_window_position" ) == 0 ){
		return load_game_conf_set_window_position( id, val );

	}

	for( i = WIN_KIND_NULL + 1; i < WIN_KIND_MAX_N; i++ ){
		const char	*name;

		name = get_win_kind_name( (win_kind_t)i );
		if( name == NULL )
			continue;

		if( strncmp( id, name, str_len_std( name ) ) == 0 ){
			if( load_game_conf_win_pos(
					id, val, (win_kind_t)i ) ){
				return TRUE;
			}
		}
	}

	print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );
	return FALSE;
}

/***************************************************************
* ����ե�������ѿ���ʸ���������
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : �ѿ�̾
* long val : ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_set_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, char *str
)
{
	if( strcmp( id, "language" ) == 0 ){
		return load_game_conf_lang( id, str );

	} else if( strcmp( id, "scroll" ) == 0 ){
		return load_game_conf_scroll( id, str );

	} else if( strcmp( id, "joystick_type" ) == 0 ){
		return load_game_conf_joystick_kind( id, str );

	} else if( strcmp( id, "color" ) == 0 ){
		return load_game_conf_color_name( id, str );

	} else if( strcmp( id, "fg_color" ) == 0 ){
		return load_game_conf_color_fg( id, str );

	} else if( strcmp( id, "bg_color" ) == 0 ){
		return load_game_conf_color_bg( id, str );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );

		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����ե�����Υѡ���(���̻� ʸ�� ʸ����)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : ���̻�
* long c : ʸ��
* char *str : ʸ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_id_char_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long c, char *str
)
{
	if( strcmp( id, "set_key" ) == 0 ){
		return load_game_conf_set_key( id, c, str );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����ե�����Υѡ���(���̻� ���� ʸ����)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : ���̻�
* long n : ����
* char *str : ʸ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_id_num_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long n, char *str
)
{
	if( strcmp( id, "set_macro_func" ) == 0 ){
		return load_game_conf_set_macro_func( id, NULL, n, str );

	} else if( strcmp( id, "set_macro_mouse_click" ) == 0 ){
		return load_game_conf_set_macro_func( id, NULL, n, str );

	} else if( strcmp( id, "set_macro_mouse_double_click" ) == 0 ){
		return load_game_conf_set_macro_func( id, NULL, n, str );

	} else if( strcmp( id, "set_macro_mouse_press_and_click" ) == 0 ){
		return load_game_conf_set_macro_func( id, NULL, n, str );

	} else if( strcmp( id, "set_macro_mouse_press" ) == 0 ){
		return load_game_conf_set_macro_func( id, NULL, n, str );

	} else if( strcmp( id, "set_macro_mouse_release" ) == 0 ){
		return load_game_conf_set_macro_func( id, NULL, n, str );

	} else if( strcmp( id, "set_macro_mouse_motion" ) == 0 ){
		return load_game_conf_set_macro_func( id, NULL, n, str );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����ե�����Υѡ���(���̻� ʸ���� ���� ʸ����)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : ���̻�
* char *str1 : ʸ����
* long n : ����
* char *str2 : ʸ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_id_str_num_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, char *str1, long n, char *str2
)
{
	if( strcmp( id, "set_macro_joystick" ) == 0 ){
		return load_game_conf_set_macro_func( id, str1, n, str2 );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����ե�����Υѡ���(���̻� ʸ��)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : ���̻�
* long c : ʸ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_id_char(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long c
)
{
	if( strcmp( id, "unset_key" ) == 0 ){
		return load_game_conf_unset_key( id, c );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����ե�����Υѡ���(���̻� �֥졼��)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : ���̻�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_id_brace(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id
)
{
	if( strcmp( id, "user_menu" ) == 0 ){
		return load_game_conf_menu( fp, ver, flg_err_exit, id );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����ե�����θ��������
* char *id : ���̻�
* char *str : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_lang( char *id, char *str )
{
	if( strcmp( str, "" ) == 0 )
		return TRUE;

	reset_msg( trans_lang_id_to_kind( str ) );

	set_flg_lang_ls_priority( TRUE );

	return TRUE;
}

/***************************************************************
* ����ե������ clock tick ������
* char *id : ���̻�
* char *str : ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_clk_tck( char *id, long val )
{
	long	*tck;

	tck = get_clk_tck();
	if( tck != NULL )
		*tck = val;

	return TRUE;
}

/***************************************************************
* ����ե�����β��̥�������ư���ꤹ�뤫�ɤ���������
* char *id : ���̻�
* long val : ���̥�������ư���ꤹ�뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_screen_size_auto( char *id, long val )
{
	set_flg_screen_size_auto( val );

	return TRUE;
}

/***************************************************************
* ����ե�����β��̥�����(�Կ�)������
* char *id : ���̻�
* long val : �Կ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_screen_size_col( char *id, long val )
{
	set_screen_size_col( val );

	return TRUE;
}

/***************************************************************
* ����ե�����β��̥�����(�Կ�)������
* char *id : ���̻�
* long val : �Կ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_screen_size_row( char *id, long val )
{
	set_screen_size_row( val );

	return TRUE;
}

/***************************************************************
* ����ե�����β��̥�����(�Կ�)������
* char *id : ���̻�
* long val : �Կ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_screen_size_message( char *id, long val )
{
	set_screen_size_message( val );

	return TRUE;
}

/***************************************************************
* ����ե�����β��̥�����(�Կ�)������
* char *id : ���̻�
* long val : �Կ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_screen_resize_map( char *id, long val )
{
	set_flg_resize_map( val );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ������롦�⡼�ɤ�����
* char *id : ���̻�
* char *str : �������롦�⡼��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_scroll( char *id, char *str )
{
	if( strcmp( str, "page" ) == 0 ){
		set_scroll_page();
	} else if( strcmp( str, "smooth" ) == 0 ){
		set_scroll_smooth();
	} else if( strcmp( str, "center" ) == 0 ){
		set_scroll_center();
	} else {
		return TRUE;
	}

	return TRUE;
}

/***************************************************************
* ����ե�����Υᥤ�󡦥������롦�ѥ������ֹ������
* char *id : ���̻�
* long val : �ѥ������ֹ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_cursor_number_main( char *id, long val )
{
	set_main_crsr_ptn_n( val );
	reset_crsr_ptn();

	return TRUE;
}

/***************************************************************
* ����ե�����Υ��֡��������롦�ѥ������ֹ������
* char *id : ���̻�
* long val : �ѥ������ֹ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_cursor_number_sub( char *id, long val )
{
	set_sub_crsr_ptn_n( val );
	reset_crsr_ptn();

	return TRUE;
}

/***************************************************************
* ���祤���ƥ��å��μ��������
* char *id : ���̻�
* char *str : ���祤���ƥ��å��μ����̾��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_joystick_kind( char *id, char *str )
{
	joy_kind_t	k;

	k = cv_joystick_name_to_kind( str );
	call_game_joystick_set_kind( k );

	return TRUE;
}

/***************************************************************
* ����ե�����ξ�˥������Хåե��򥯥ꥢ���뤫������
* char *id : ���̻�
* long val : �������Хåե��򥯥ꥢ���뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_clr_key_buf_every( char *id, long val )
{
	g_flg_clr_key_buf = (bool_t)val;

	return TRUE;
}

/***************************************************************
* ����ե�����Υ�˥塼���˥������Хåե��򥯥ꥢ���뤫������
* char *id : ���̻�
* long val : �������Хåե��򥯥ꥢ���뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_clr_key_buf_menu( char *id, long val )
{
	g_flg_clr_key_buf_menu = (bool_t)val;

	return TRUE;
}

/***************************************************************
* ����ե�����Υ��ڡ����������ǥ�˥塼�����򤹤�����
* char *id : ���̻�
* long val : ���ڡ����������ǥ�˥塼�����򤹤뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_space_select( char *id, long val )
{
	set_flg_space_select( (bool_t)val );

	return TRUE;
}

/***************************************************************
* ����ե�������西���������̤�����褹������
* char *id : ���̻�
* long val : �����褹�뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_redraw_every_turn( char *id, long val )
{
	set_redraw_every_turn( (bool_t)val );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ�å�������ʣ����ɽ�����뤫������
* char *id : ���̻�
* long val : ʣ����ɽ�����뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_mul_line( char *id, long val )
{
	set_msg_mul_line( (bool_t)val );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ��ơ��������С��Υ���饯���Υҥ�Ȥ�ɽ�����뤫������
* char *id : ���̻�
* long val : ɽ�����뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_stat_bar_hint_chr( char *id, long val )
{
	set_flg_stat_bar_hint_chr( (bool_t)val );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ��ơ��������С��Υ��֥������ȤΥҥ�Ȥ�ɽ�����뤫������
* char *id : ���̻�
* long val : ɽ�����뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_stat_bar_hint_obj( char *id, long val )
{
	set_flg_stat_bar_hint_obj( (bool_t)val );

	return TRUE;
}

/***************************************************************
* ��˥塼�Υǥե���ȹ��ܤإ��������ư��ư���뤫������
* char *id : ���̻�
* long val : ���祤���ƥ��å����ֹ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_move_crsr_dflt( char *id, long val )
{
	set_flg_move_crsr_dflt( (bool_t)val );

	return TRUE;
}

/***************************************************************
* ���֥롦����å��δֳ֤�����
* char *id : ���̻�
* long val : ���֥롦����å��δֳ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_double_click_wait( char *id, long val )
{
	set_cui_mouse_double_click_msec( val );

	return TRUE;
}

/***************************************************************
* BGM �β��̤�����
* char *id : ���̻�
* long val : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_music_volume( char *id, long val )
{
	set_music_volume_rate( val );
	call_game_music_set_volume( get_music_volume_rate() );

	return TRUE;
}

/***************************************************************
* SE �β��̤�����
* char *id : ���̻�
* long val : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_sound_volume( char *id, long val )
{
	set_sound_volume_rate( val );
	call_game_sound_set_volume( get_sound_volume_rate() );

	return TRUE;
}

/***************************************************************
* ���祤���ƥ��å����ֹ������
* char *id : ���̻�
* long val : ���祤���ƥ��å����ֹ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_joystick_number( char *id, long val )
{
	call_game_joystick_sel_joy( (joy_kind_t)val );

	return TRUE;
}

/***************************************************************
* ����ե�����β����Хåե���������������
* char *id : ���̻�
* long val : �����Хåե���������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_audio_buf_siz( char *id, long val )
{
	g_audio_buf_siz = val;

	return TRUE;
}

/***************************************************************
* ����ե������ GNOME ������
* char *id : ���̻�
* long val : ������ɥ����ޥ͡����㤬 GNOME ��?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_gnome( char *id, long val )
{
	g_flg_gnome = val;

	return TRUE;
}

/***************************************************************
* ����ե�����Υ�����ɥ����֤�����򤹤뤫?
* char *id : ���̻�
* long val : ��ɸ�ޤ��ϥ�����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_set_window_position( char *id, long val )
{
	g_flg_set_win_pos = val;

	return TRUE;
}

/***************************************************************
* ����ե�����Υ�����ɥ����֤�����
* char *id : ���̻�
* long val : ��ɸ�ޤ��ϥ�����
* win_kind_t kind : ������ɥ��μ���
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_win_pos( char *id, long val, win_kind_t kind )
{
	const char	*name;
	char	v[TOKEN_MAX_LEN + 1];

	name = get_win_kind_name( kind );
	if( name == NULL )
		return FALSE;

	sn_printf( v, TOKEN_MAX_LEN, "%s_x", name );
	if( strcmp( id, v ) == 0 ){
		call_win_pos_set( kind, &val, NULL, NULL, NULL );
		return TRUE;
	}

	sn_printf( v, TOKEN_MAX_LEN, "%s_y", name );
	if( strcmp( id, v ) == 0 ){
		call_win_pos_set( kind, NULL, &val, NULL, NULL );
		return TRUE;
	}

	sn_printf( v, TOKEN_MAX_LEN, "%s_width", name );
	if( strcmp( id, v ) == 0 ){
		call_win_pos_set( kind, NULL, NULL, &val, NULL );
		return TRUE;
	}

	sn_printf( v, TOKEN_MAX_LEN, "%s_height", name );
	if( strcmp( id, v ) == 0 ){
		call_win_pos_set( kind, NULL, NULL, NULL, &val );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ����ե�����Υ��С��λ�и��̤�ɽ�����뤫������
* flg_vfx_mbr_t flg : ���ꤹ��ե饰
* long val : ���ꤹ�뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_vfx_mbr( flg_vfx_mbr_t flg, long val )
{
	flg_vfx_mbr_t	flg_dst;

	flg_dst = get_flg_vfx_mbr();

	if( val )
		flg_dst |= flg;
	else
		flg_dst &= ~(flg);

	set_flg_vfx_mbr( flg_dst );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ�󥹥����λ�и��̤�ɽ�����뤫������
* flg_vfx_mnstr_t flg : ���ꤹ��ե饰
* long val : ���ꤹ�뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_vfx_mnstr( flg_vfx_mnstr_t flg, long val )
{
	flg_vfx_mbr_t	flg_dst;

	flg_dst = get_flg_vfx_mnstr();

	if( val )
		flg_dst |= flg;
	else
		flg_dst &= ~(flg);

	set_flg_vfx_mnstr( flg_dst );

	return TRUE;
}

/***************************************************************
* ����ե�����λ�и��̤�ɽ�����֤�����
* char *id : ���̻�
* long val : ɽ������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_vfx_wait( char *id, long val )
{
#if	1
	set_vfx_wait( (rate_t)val );

	return TRUE;
#else
	rate_t	ret;

	ret = set_vfx_wait( (rate_t)val );

	/* �ͤ�������褿��? */

	if( ret == val )
		return TRUE;
	else
		return FALSE;
#endif
}

/***************************************************************
* ����ե���������ꤹ����̤ο���̾���򵭲�����
* char *id : ���̻�
* char *name : ����̾��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_color_name( char *id, char *name )
{
	if( id == NULL )
		return FALSE;
	if( name == NULL )
		return FALSE;

	if( strcmp( name, "normal" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_NORMAL;
	if( strcmp( name, "rev" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_REV;
	if( strcmp( name, "reverse" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_REV;
	if( strcmp( name, "err" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_ERR;
	if( strcmp( name, "error" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_ERR;

	if( strcmp( name, "menu_normal" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MENU_NORMAL;
	if( strcmp( name, "menu_dis" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MENU_DIS;
	if( strcmp( name, "menu_disable" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MENU_DIS;
	if( strcmp( name, "menu_sel" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MENU_SEL;
	if( strcmp( name, "menu_select" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MENU_SEL;

	if( strcmp( name, "map_crsr" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_CRSR;
	if( strcmp( name, "map_cursor" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_CRSR;
	if( strcmp( name, "map_square" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_SQUARE;
	if( strcmp( name, "map_anchor" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_SQUARE;
	if( strcmp( name, "map_wall" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_WALL;
	if( strcmp( name, "map_floor" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_FLOOR;
	if( strcmp( name, "map_door" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_DOOR;
	if( strcmp( name, "map_stairs" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_STAIRS;
	if( strcmp( name, "map_trap" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_TRAP;
	if( strcmp( name, "map_mnstr" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_MNSTR;
	if( strcmp( name, "map_monster" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_MNSTR;
	if( strcmp( name, "map_npc" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_NPC;
	if( strcmp( name, "map_pet" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_PET;

	if( strcmp( name, "map_item" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM;
	if( strcmp( name, "map_item_wpn" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_WPN;
	if( strcmp( name, "map_item_weapon" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_WPN;
	if( strcmp( name, "map_item_armor" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_ARMOR;
	if( strcmp( name, "map_item_potion" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_POTION;
	if( strcmp( name, "map_item_scroll" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_SCROLL;
	if( strcmp( name, "map_item_stick" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_STICK;
	if( strcmp( name, "map_item_acce" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_ACCE;
	if( strcmp( name, "map_item_accessory" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_ACCE;
	if( strcmp( name, "map_item_inst" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_INST;
	if( strcmp( name, "map_item_instrument" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_INST;
	if( strcmp( name, "map_item_light" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_LIGHT;
	if( strcmp( name, "map_item_spike" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_SPIKE;
	if( strcmp( name, "map_item_food" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_FOOD;
	if( strcmp( name, "map_item_chest" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_CHEST;
	if( strcmp( name, "map_item_rare_GOODS" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_RARE_GOODS;
	if( strcmp( name, "map_item_rare_goods" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_RARE_GOODS;
	if( strcmp( name, "map_item_bone" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_BONE;
	if( strcmp( name, "map_item_coin" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_COIN;
	if( strcmp( name, "map_item_junk" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MAP_ITEM_JUNK;

	if( strcmp( name, "mbr_1" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_1;
	if( strcmp( name, "mbr_2" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_2;
	if( strcmp( name, "mbr_3" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_3;
	if( strcmp( name, "mbr_4" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_4;
	if( strcmp( name, "mbr_5" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_5;
	if( strcmp( name, "mbr_6" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_6;

	if( strcmp( name, "member_1" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_1;
	if( strcmp( name, "member_2" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_2;
	if( strcmp( name, "member_3" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_3;
	if( strcmp( name, "member_4" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_4;
	if( strcmp( name, "member_5" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_5;
	if( strcmp( name, "member_6" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MBR_6;

	if( strcmp( name, "fx_mbr_plus" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MBR_PLUS;
	if( strcmp( name, "fx_mbr_minus" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MBR_MINUS;
	if( strcmp( name, "fx_mbr_crtcl" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MBR_CRTCL;
	if( strcmp( name, "fx_mnstr_plus" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MNSTR_PLUS;
	if( strcmp( name, "fx_mnstr_minus" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MNSTR_MINUS;
	if( strcmp( name, "fx_mnstr_crtcl" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MNSTR_CRTCL;
	if( strcmp( name, "vfx" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_VFX;

	if( strcmp( name, "fx_member_plus" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MBR_PLUS;
	if( strcmp( name, "fx_member_minus" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MBR_MINUS;
	if( strcmp( name, "fx_member_critical" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MBR_CRTCL;
	if( strcmp( name, "fx_monster_plus" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MNSTR_PLUS;
	if( strcmp( name, "fx_monster_minus" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MNSTR_MINUS;
	if( strcmp( name, "fx_monster_critical" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_FX_MNSTR_CRTCL;

	if( strcmp( name, "heat" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_HEAT;
	if( strcmp( name, "cold" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_COLD;
	if( strcmp( name, "mind" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_MIND;
	if( strcmp( name, "acid" ) == 0 )
		g_crnt_attr_n = CURS_ATTR_N_ACID;

	return TRUE;
}

/***************************************************************
* ����ե���������ʿ�������
* char *id : ���̻�
* char *color : ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_color_fg( char *id, char *color )
{
	curs_attr_t	*attr;

	if( id == NULL )
		return FALSE;
	if( color == NULL )
		return FALSE;

	attr = get_curs_attr();
	if( attr == NULL )
		return FALSE;

	set_fg_color( &(attr[g_crnt_attr_n]),
			cv_name_to_color( color ) );

	return TRUE;
}

/***************************************************************
* ����ե�������طʿ�������
* char *id : ���̻�
* char *color : ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_color_bg( char *id, char *color )
{
	curs_attr_t	*attr;

	if( id == NULL )
		return FALSE;
	if( color == NULL )
		return FALSE;

	attr = get_curs_attr();
	if( attr == NULL )
		return FALSE;

	set_bg_color( &(attr[g_crnt_attr_n]),
			cv_name_to_color( color ) );

	return TRUE;
}

/***************************************************************
* ����ե�����β��̤β���°��������
* char *id : ���̻�
* long val : ����°�������ꤹ�뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_attribute_underline( char *id, long val )
{
	curs_attr_t	*attr;

	if( id == NULL )
		return FALSE;

	attr = get_curs_attr();
	if( attr == NULL )
		return FALSE;

	set_color_attr( &(attr[g_crnt_attr_n]), (bool_t)val, A_UNDERLINE );

	return TRUE;
}

/***************************************************************
* ����ե�����β��̤�ȿž°��������
* char *id : ���̻�
* long val : ȿž°�������ꤹ�뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_attribute_reverse( char *id, long val )
{
	curs_attr_t	*attr;

	if( id == NULL )
		return FALSE;

	attr = get_curs_attr();
	if( attr == NULL )
		return FALSE;

	set_color_attr( &(attr[g_crnt_attr_n]), (bool_t)val, A_REVERSE );

	return TRUE;
}

/***************************************************************
* ����ե�����β��̤�����°��������
* char *id : ���̻�
* long val : ����°�������ꤹ�뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_attribute_blink( char *id, long val )
{
	curs_attr_t	*attr;

	if( id == NULL )
		return FALSE;

	attr = get_curs_attr();
	if( attr == NULL )
		return FALSE;

	set_color_attr( &(attr[g_crnt_attr_n]), (bool_t)val, A_BLINK );

	return TRUE;
}

/***************************************************************
* ����ե�����β��̤ζ�Ĵ°��������
* char *id : ���̻�
* long val : ��Ĵ°�������ꤹ�뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_attribute_bold( char *id, long val )
{
	curs_attr_t	*attr;

	if( id == NULL )
		return FALSE;

	attr = get_curs_attr();
	if( attr == NULL )
		return FALSE;

	set_color_attr( &(attr[g_crnt_attr_n]), (bool_t)val, A_BOLD );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ���������Ƥ�����
* char *id : ���̻�
* long c : ����
* char *str : ������Ƥ�ʸ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_set_key( char *id, long c, char *str )
{
	set_key_tab_char( c, str );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ���������Ƥβ��������
* char *id : ���̻�
* long c : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_unset_key( char *id, long c )
{
	set_key_tab_char( c, NULL );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ���������Ƥ�����
* char *id : ���̻�
* const char *joy : ���祤���ƥ��å��μ��̻�
* long n : ����ǥå���
* const char *macro : �ޥ���
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_set_macro_func(
	char *id, char *joy, long n, char *macro
)
{
	char	*m;

	if( macro == NULL )
		return FALSE;

	m = NULL;
	if( strcmp( id, "set_macro_func" ) == 0 ){
		m = get_macro_func( n );
	} else if( strcmp( id, "set_macro_mouse_click" ) == 0 ){
		m = get_macro_mouse_click( n );
	} else if( strcmp( id, "set_macro_mouse_double_click" ) == 0 ){
		m = get_macro_mouse_d_click( n );
	} else if( strcmp( id, "set_macro_mouse_press_and_click" ) == 0 ){
		m = get_macro_mouse_p_click( n );
	} else if( strcmp( id, "set_macro_mouse_press" ) == 0 ){
		m = get_macro_mouse_press( n );
	} else if( strcmp( id, "set_macro_mouse_release" ) == 0 ){
		m = get_macro_mouse_release( n );
	} else if( strcmp( id, "set_macro_mouse_motion" ) == 0 ){
		m = get_macro_mouse_motion( n );
	} else if( strcmp( id, "set_macro_joystick" ) == 0 ){
		long	j;

		if( joy == NULL )
			return FALSE;

		for( j = 0; j < JOY_KIND_MAX_N; j++ ){
			if( strcmp( joy, cv_joystick_kind_to_name( (joy_kind_t)j ) )
					== 0 ){
				m = get_macro_joystick( j, n );
				break;
			}
		}
		if( j >= JOY_KIND_MAX_N )
			return TRUE;
	} else {
		return FALSE;
	}

	if( m == NULL )
		return FALSE;

	str_nz_cpy( m, macro, MACRO_MAX_LEN );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ桼������˥塼������
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : ���̻�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_menu(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id
)
{
	long	i;

	clr_user_menu();

	for( i = 0; i < USER_MENU_MAX_N; i++ ){
		if( !load_game_conf_menu_line( fp, ver, flg_err_exit, id ) )
			break;
	}

	return TRUE;
}

/***************************************************************
* ����ե�����Υ桼������˥塼�� 1 ���������
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* bool_t flg_err_exit : ���顼�ǽ�λ���뤫?
* char *id : ���̻�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_conf_menu_line(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id
)
{
	rc_token_t	t[MAX_TOKEN];
	rc_union_t	u[MAX_TOKEN];
	long	i;

	for( i = 0; i < MAX_TOKEN; i++ )
		t[i] = RC_TOKEN_EOF;

	do {
		t[0] = rc_lex( fp, &u[0], flg_err_exit );
		if( t[0] == RC_TOKEN_EOF )
			break;
		if( t[0] == '\n' )
			break;

		t[1] = rc_lex( fp, &u[1], flg_err_exit );
		if( t[1] == RC_TOKEN_EOF )
			break;
		if( t[1] == '\n' )
			break;

		t[2] = rc_lex( fp, &u[2], flg_err_exit );
		if( t[2] == RC_TOKEN_EOF )
			break;
		if( t[2] == '\n' )
			break;
	} while( 0 );

	if( t[0] == RC_TOKEN_EOF ){
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		return FALSE;
	} else if( t[0] == '\n' ){
		return TRUE;
	} else if( (t[0] == RC_TOKEN_STR)
			&& (t[1] == RC_TOKEN_STR)
			&& (t[2] == '\n') ){
		add_user_menu( u[0].str, u[1].str );
		return TRUE;
	} else if( (t[0] == '}') && (t[1] == '\n') ){
		/* ��λ */
		return FALSE;
	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����������Υ���
* long n : �ǡ���������å��ֹ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_data_cnf( long n )
{
	FILE	*fp;
	ver_t	ver;
	bool_t	flg_txt = TRUE;

	/* �ե�����Υ����ץ� */

	fp = open_game_data_cnf( 'r', n );
	if( fp == NULL )
		return TRUE;	/* FALSE �ǤϤʤ� */

	/* �إå����ɤ߹��� */

	set_flg_crypt_txt( TRUE );
	load_game_data_head_ver_1( fp, &ver, flg_txt );
	set_flg_crypt_txt( flg_txt );

	/* �С������Υ����å� */

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

	/* �ǡ����ν���� */

	reset_load_game_data_cnf();

	/* �ǡ������ɤ߹��� */

	switch( ver.mjr ){
	case 1:
		if( !load_game_data_cnf_ver_1( fp, &ver ) ){
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

	/* �С�����ʥå� */

	if( chk_ver_old( &ver, 1, 0, 4 ) )
		ver_up_game_data_1_0_4();

	if( chk_ver_old( &ver, 1, 1, 1 ) )
		ver_up_game_data_1_1_1();

	if( chk_ver_old( &ver, 1, 1, 3 ) )
		ver_up_game_data_1_1_3();

	if( chk_ver_old( &ver, 1, 2, 12 ) )
		ver_up_game_data_1_2_12();

	if( chk_ver_old( &ver, 1, 2, 22 ) )
		ver_up_game_data_cnf_1_2_22();

	/* �ե�����Υ����� */

	if( fclose( fp ) == EOF )
		return FALSE;

	/* �ǡ������������������å� */

	if( !chk_load_game_data_cnf() )
		return FALSE;

	/* ���ޥ�ɡ��饤�������ͥ�� */

	overwrite_arg();

	return TRUE;
}

/***************************************************************
* ����������Υ������ν����
***************************************************************/

void	reset_load_game_data_cnf( void )
{
}

/***************************************************************
* ����������Υ��ɻ��Υ����å�
* return : �ǡ����˰۾郎̵���ä���?
***************************************************************/

bool_t	chk_load_game_data_cnf( void )
{
	return TRUE;
}

/***************************************************************
* ����������Υ���(�С������ 1)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_data_cnf_ver_1( FILE *fp, const ver_t *ver )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	while( 1 ){
		if( !load_game_data_cnf_parse_ver_1( fp, ver ) )
			break;
	}

	return TRUE;
}

/***************************************************************
* ����������Υѡ���(�С������ 1)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : �ѡ�����³���뤫?
***************************************************************/

bool_t	load_game_data_cnf_parse_ver_1(
	FILE *fp, const ver_t *ver
)
{
	rc_token_t	t[MAX_TOKEN];
	rc_union_t	u[MAX_TOKEN];
	bool_t	flg_err_exit, flg_err;
	long	i;

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
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == RC_TOKEN_NUM)
			&& (t[3] == '\n') ){
		/* foo = n */

		if( !load_game_conf_set_val(
				fp, ver, flg_err_exit,
				u[0].str, u[2].n ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == RC_TOKEN_ADD_OP)
			&& (t[3] == RC_TOKEN_NUM)
			&& (t[4] == '\n') ){
		/* foo = - n */
		long	sg = +1;

		if( u[2].c == '-' )
			sg = -1;
		if( !load_game_conf_set_val(
				fp, ver, flg_err_exit,
				u[0].str, sg * u[3].n ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == RC_TOKEN_STR)
			&& (t[3] == '\n') ){
		/* foo = str */

		if( !load_game_conf_set_str(
				fp, ver, flg_err_exit,
				u[0].str, u[2].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_CHAR)
			&& (t[2] == RC_TOKEN_STR)
			&& (t[3] == '\n') ){
		/* foo c str */

		if( !load_game_conf_id_char_str(
				fp, ver, flg_err_exit,
				u[0].str, u[1].c, u[2].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_NUM)
			&& (t[2] == RC_TOKEN_STR)
			&& (t[3] == '\n') ){
		/* foo n str */

		if( !load_game_conf_id_num_str(
				fp, ver, flg_err_exit,
				u[0].str, u[1].n, u[2].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_STR)
			&& (t[2] == RC_TOKEN_NUM)
			&& (t[3] == RC_TOKEN_STR)
			&& (t[4] == '\n') ){
		/* foo str n str */

		if( !load_game_conf_id_str_num_str(
				fp, ver, flg_err_exit,
				u[0].str, u[1].str, u[2].n, u[3].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_CHAR)
			&& (t[2] == '\n') ){
		/* foo c */

		if( !load_game_conf_id_char(
				fp, ver, flg_err_exit,
				u[0].str, u[1].c ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == '{')
			&& (t[2] == '\n') ){
		/* foo { */

		if( !load_game_conf_id_brace(
				fp, ver, flg_err_exit,
				u[0].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_NUM)
			&& (t[2] == RC_TOKEN_EQ_OP)
			&& (t[3] == RC_TOKEN_STR)
			&& (t[4] == '\n') ){
		/* foo n = "bar" */

		if( !load_game_data_cnf_id_num_eq_str_ver_1(
				fp, ver,
				u[0].str, u[1].n, u[3].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == '{')
			&& (t[3] == '\n') ){
		/* foo = { */

		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		flg_err = TRUE;
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_NUM)
			&& (t[2] == RC_TOKEN_EQ_OP)
			&& (t[3] == '{')
			&& (t[4] == '\n') ){
		/* foo n = { */

		if( !load_game_data_cnf_block_ver_1(
				fp, ver,
				u[0].str, u[1].n ) ){
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
* ����������Υѡ���(���̻� �� = ʸ���� : �С������ 1)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* char *id : ���̻�
* long n : ��
* char *str : ʸ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_data_cnf_id_num_eq_str_ver_1(
	FILE *fp, const ver_t *ver,
	char *id, long n, char *str
)
{
	bool_t	flg_txt = TRUE;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( id == NULL )
		return FALSE;
	if( str == NULL )
		return FALSE;

	if( strcmp( id, "auto_mark_title" ) == 0 ){
		return( load_game_data_auto_mark_ttl_ver_1(
				fp, ver, flg_txt, n, str ) );
	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );

		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����������Υ֥�å��Υѡ���(�С������ 1)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* char *id : ���̻�
* long n : ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	load_game_data_cnf_block_ver_1(
	FILE *fp, const ver_t *ver,
	char *id, long n
)
{
	bool_t	flg_txt = TRUE;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( id == NULL )
		return FALSE;

	if( strcmp( id, "auto_mark" ) == 0 ){
		return( load_game_data_auto_mark_ls_ver_1(
				fp, ver, flg_txt, n ) );

	} else if( strcmp( id, "auto_mark_appoint_item" ) == 0 ){
		return( load_game_data_auto_mark_appoint_item_ls_ver_1(
				fp, ver, flg_txt, n ) );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );

		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����ե�����Υ�����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf( void )
{
	ver_t	ver;

	ver.mjr = GAME_CONF_VER_MJR;
	ver.mnr = GAME_CONF_VER_MNR;
	ver.pat = GAME_CONF_VER_PAT;

	switch( ver.mjr ){
	case 1:
		return save_game_conf_ver_1( &ver );
		break;
	default:
		return FALSE;
		break;
	}

	return FALSE;
}

/***************************************************************
* ����ե�����Υ�����(�С������ 1)
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_ver_1( const ver_t *ver )
{
	FILE	*fp;

	fp = fopen( path_name_game_conf, "w" );
	if( fp == NULL )
		return FALSE;

	reset_load_save( path_name_game_conf, TRUE );

	/* header */

	fprintf( fp, "%s", STR_GAME_CONF_HEAD );
	fprintf( fp, "%ld.%ld.%ld\n", ver->mjr, ver->mnr, ver->pat );

	/* contents */

	if( !save_game_conf_contents( fp, ver ) ){
		fclose( fp );
		return FALSE;
	}

	/* footer */

	fputs( "\n", fp );
	fputs( "# end\n", fp );

	/* end */

	if( fclose( fp ) == EOF )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ����ե���������ƤΥ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_contents( FILE *fp, const ver_t *ver )
{
	bool_t	flg_err = FALSE;

	flg_err |= !save_game_conf_language( fp, ver );
	flg_err |= !save_game_conf_frame_rate( fp, ver );
	flg_err |= !save_game_conf_screen_size( fp, ver );
	flg_err |= !save_game_conf_scroll( fp, ver );
	flg_err |= !save_game_conf_crsr_ptn_n( fp, ver );
	flg_err |= !save_game_conf_flg( fp, ver );
	flg_err |= !save_game_conf_audio_buf_siz( fp, ver );
	flg_err |= !save_game_conf_gnome( fp, ver );
	flg_err |= !save_game_conf_set_window_position( fp, ver );
	flg_err |= !save_game_conf_win_pos( fp, ver );
	flg_err |= !save_game_conf_mouse( fp, ver );
	flg_err |= !save_game_conf_sound( fp, ver );
	flg_err |= !save_game_conf_joystick( fp, ver );
	flg_err |= !save_game_conf_vfx( fp, ver );
	flg_err |= !save_game_conf_color( fp, ver );
	flg_err |= !save_game_conf_key_tab( fp, ver );
	flg_err |= !save_game_conf_func( fp, ver );
	flg_err |= !save_game_conf_user_menu( fp, ver );

	if( flg_err )
		return FALSE;
	else
		return TRUE;
}

/***************************************************************
* ����ե�����θ���Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_language( FILE *fp, const ver_t *ver )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# language\n" );
	if( get_flg_lang_ls_priority() ){
		fprintf( fp, "language = \"%s\"\n", get_lang_id_next() );
	} else {
		fprintf( fp, "language = \"\"\n" );
	}

	return TRUE;
}

/***************************************************************
* ����ե�����Υե졼�ࡦ�졼�ȤΥ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_frame_rate( FILE *fp, const ver_t *ver )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# frame rate\n" );
	fprintf( fp, "clk_tck = %ld\n",
			(long)(*get_clk_tck()) );

	return TRUE;
}

/***************************************************************
* ����ե�����β��̥������Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_screen_size( FILE *fp, const ver_t *ver )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# screen size\n" );

	fprintf( fp, "screen_size_auto = %ld\n",
			(long)chk_flg_screen_size_auto() );
	fprintf( fp, "screen_size_column = %ld\n",
			(long)get_screen_size_col() );
	fprintf( fp, "screen_size_row = %ld\n",
			(long)get_screen_size_row() );
	fprintf( fp, "screen_size_message = %ld\n",
			(long)get_screen_size_message() );
	fprintf( fp, "screen_resize_map = %ld\n",
			(long)chk_flg_resize_map() );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ������롦�⡼�ɤΥ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_scroll( FILE *fp, const ver_t *ver )
{
	flg_scroll_t	flg;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	flg = get_flg_scroll();

	fprintf( fp, "\n" );
	fprintf( fp, "# scroll mode\n" );
	fprintf( fp, "#  center, smooth or page\n" );

	fprintf( fp, "scroll = " );

	if( chk_flg( flg, FLG_SCROLL_CENTER ) ){
		fprintf( fp, "\"center\"" );
	} else if( chk_flg( flg, FLG_SCROLL_SMOOTH ) ){
		fprintf( fp, "\"smooth\"" );
	} else {
		fprintf( fp, "\"page\"" );
	}

	fprintf( fp, "\n" );

	return TRUE;
}

/***************************************************************
* ����ե�����γƥ������롦�ѥ������ֹ�Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_crsr_ptn_n( FILE *fp, const ver_t *ver )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# number of cursor pattern\n" );
	fprintf( fp, "cursor_number_main = %ld\n",
			(long)get_main_crsr_ptn_n() );
	fprintf( fp, "cursor_number_sub = %ld\n",
			(long)get_sub_crsr_ptn_n() );

	return TRUE;
}

/***************************************************************
* ����ե�����γƥե饰�Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_flg( FILE *fp, const ver_t *ver )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# clear key buffer every time\n" );
	fprintf( fp, "clear_key_buffer_every = %ld\n",
			(long)g_flg_clr_key_buf );

	fprintf( fp, "\n" );
	fprintf( fp, "# clear key buffer menu select\n" );
	fprintf( fp, "clear_key_buffer_menu = %ld\n",
			(long)g_flg_clr_key_buf_menu );

	fprintf( fp, "\n" );
	fprintf( fp, "# It's flag that you chose menu with space bar\n" );
	fprintf( fp, "space_select = %ld\n",
			(long)get_flg_space_select() );

	fprintf( fp, "\n" );
	fprintf( fp, "# redraw every turn\n" );
	fprintf( fp, "redraw_every_turn = %ld\n",
			(long)chk_redraw_every_turn() );

	fprintf( fp, "\n" );
	fprintf( fp, "# multiple message line\n" );
	fprintf( fp, "multiple_message_line = %ld\n",
			(long)chk_msg_mul_line() );

	fprintf( fp, "\n" );
	fprintf( fp, "# draw hint of character on the status bar\n" );
	fprintf( fp, "status_bar_hint_character = %ld\n",
			(long)get_flg_stat_bar_hint_chr() );

	fprintf( fp, "\n" );
	fprintf( fp, "# draw hint of object on the status bar\n" );
	fprintf( fp, "status_bar_hint_object = %ld\n",
			(long)get_flg_stat_bar_hint_obj() );

	return TRUE;
}

/***************************************************************
* ����ե�����β����Хåե����������Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_audio_buf_siz( FILE *fp, const ver_t *ver )
{
	fprintf( fp, "\n" );
	fprintf( fp, "# audio buffer size\n" );
	fprintf( fp, "audio_buffer_size = %ld\n",
			(long)g_audio_buf_siz );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ�����ɥ����֤�����ե饰�Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_gnome( FILE *fp, const ver_t *ver )
{
	fprintf( fp, "\n" );
	fprintf( fp, "# window manager is GNOME\n" );
	fprintf( fp, "gnome = %ld\n",
			(long)g_flg_gnome );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ�����ɥ����֤�����ե饰�Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_set_window_position( FILE *fp, const ver_t *ver )
{
	fprintf( fp, "\n" );
	fprintf( fp, "# set window position\n" );
	fprintf( fp, "set_window_position = %ld\n",
			(long)g_flg_set_win_pos );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ�����ɥ����֤Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_win_pos( FILE *fp, const ver_t *ver )
{
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# window position\n" );
	fprintf( fp, "\n" );

	for( i = WIN_KIND_NULL + 1; i < WIN_KIND_MAX_N; i++ ){
		long	x, y, w, h;
		const char	*name;

		if( !call_win_pos_get( (win_kind_t)i, &x, &y, &w, &h ) )
			continue;
		name = get_win_kind_name( (win_kind_t)i );
		if( name == NULL )
			continue;

		fprintf( fp, "%s_x = %ld\n", name, (long)x );
		fprintf( fp, "%s_y = %ld\n", name, (long)y );
		fprintf( fp, "%s_width = %ld\n", name, (long)w );
		fprintf( fp, "%s_height = %ld\n", name, (long)h );
		fprintf( fp, "\n" );
	}

	return TRUE;
}

/***************************************************************
* ����ե�����Υޥ����Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_mouse( FILE *fp, const ver_t *ver )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# mouse\n" );
	fprintf( fp, "\n" );

	fprintf( fp, "# move cursor to default\n" );
	fprintf( fp, "move_cursor_to_default = %ld\n",
			(long)get_flg_move_crsr_dflt() );
	fprintf( fp, "\n" );

	fprintf( fp, "# double click wait for CUI mouse\n" );
	fprintf( fp, "double_click_wait = %ld\n",
			(long)get_cui_mouse_double_click_msec() );
	fprintf( fp, "\n" );

	return TRUE;
}

/***************************************************************
* ����ե������ BGM/SE �Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_sound( FILE *fp, const ver_t *ver )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# music and sound\n" );
	fprintf( fp, "\n" );

	fprintf( fp, "music_volume = %ld\n",
			(long)get_music_volume_rate() );
	fprintf( fp, "sound_volume = %ld\n",
			(long)get_sound_volume_rate() );
	fprintf( fp, "\n" );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ��祤���ƥ��å��Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_joystick( FILE *fp, const ver_t *ver )
{
	long	n;
	joy_kind_t	kind;
	const char	*name;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# joystick\n" );
	fprintf( fp, "\n" );

	n = call_game_joystick_get_joy();
	kind = (joy_kind_t)call_game_joystick_get_kind();
	name = cv_joystick_kind_to_name( kind );

	fprintf( fp, "joystick_number = %ld\n", (long)n );
	fprintf( fp, "joystick_type = \"%s\"\n", name );
	fprintf( fp, "\n" );

	return TRUE;
}

/***************************************************************
* ����ե�����λ�и��̤Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_vfx( FILE *fp, const ver_t *ver )
{
	flg_vfx_mbr_t	flg_mbr;
	flg_vfx_mnstr_t	flg_mnstr;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# vfx\n" );

	/* ���С� */

	flg_mbr = get_flg_vfx_mbr();
	fprintf( fp, "vfx_member_cure = %ld\n",
			(long)chk_flg( flg_mbr, FLG_VFX_MBR_CURE ) );
	fprintf( fp, "vfx_member_damage = %ld\n",
			(long)chk_flg( flg_mbr, FLG_VFX_MBR_DAM ) );
	fprintf( fp, "vfx_member_critical = %ld\n",
			(long)chk_flg( flg_mbr, FLG_VFX_MBR_CRTCL ) );
	fprintf( fp, "vfx_member_arrow = %ld\n",
			(long)chk_flg( flg_mbr, FLG_VFX_MBR_ARW ) );

	/* ��󥹥��� */

	flg_mnstr = get_flg_vfx_mnstr();
	fprintf( fp, "vfx_monster_cure = %ld\n",
			(long)chk_flg( flg_mnstr, FLG_VFX_MNSTR_CURE ) );
	fprintf( fp, "vfx_monster_damage = %ld\n",
			(long)chk_flg( flg_mnstr, FLG_VFX_MNSTR_DAM ) );
	fprintf( fp, "vfx_monster_critical = %ld\n",
			(long)chk_flg( flg_mnstr, FLG_VFX_MNSTR_CRTCL ) );
	fprintf( fp, "vfx_monster_arrow = %ld\n",
			(long)chk_flg( flg_mnstr, FLG_VFX_MNSTR_ARW ) );

	/* �������� */

	fprintf( fp, "vfx_wait = %ld\n",
			(long)get_vfx_wait() );

	/**/

	return TRUE;
}

/***************************************************************
* ����ե�����ο��Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_color( FILE *fp, const ver_t *ver )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# color\n" );

	save_game_conf_color_sub( fp, "normal",
			CURS_ATTR_N_NORMAL );
	save_game_conf_color_sub( fp, "reverse",
			CURS_ATTR_N_REV );
	save_game_conf_color_sub( fp, "error",
			CURS_ATTR_N_ERR );

	save_game_conf_color_sub( fp, "menu_normal",
			CURS_ATTR_N_MENU_NORMAL );
	save_game_conf_color_sub( fp, "menu_disable",
			CURS_ATTR_N_MENU_DIS );
	save_game_conf_color_sub( fp, "menu_select",
			CURS_ATTR_N_MENU_SEL );

	save_game_conf_color_sub( fp, "map_cursor",
			CURS_ATTR_N_MAP_CRSR );
	save_game_conf_color_sub( fp, "map_anchor",
			CURS_ATTR_N_MAP_SQUARE );
	save_game_conf_color_sub( fp, "map_wall",
			CURS_ATTR_N_MAP_WALL );
	save_game_conf_color_sub( fp, "map_floor",
			CURS_ATTR_N_MAP_FLOOR );
	save_game_conf_color_sub( fp, "map_door",
			CURS_ATTR_N_MAP_DOOR );
	save_game_conf_color_sub( fp, "map_stairs",
			CURS_ATTR_N_MAP_STAIRS );
	save_game_conf_color_sub( fp, "map_trap",
			CURS_ATTR_N_MAP_TRAP );
	save_game_conf_color_sub( fp, "map_monster",
			CURS_ATTR_N_MAP_MNSTR );
	save_game_conf_color_sub( fp, "map_npc",
			CURS_ATTR_N_MAP_NPC );
	save_game_conf_color_sub( fp, "map_pet",
			CURS_ATTR_N_MAP_PET );

	save_game_conf_color_sub( fp, "map_item",
			CURS_ATTR_N_MAP_ITEM );
	save_game_conf_color_sub( fp, "map_item_weapon",
			CURS_ATTR_N_MAP_ITEM_WPN );
	save_game_conf_color_sub( fp, "map_item_armor",
			CURS_ATTR_N_MAP_ITEM_ARMOR );
	save_game_conf_color_sub( fp, "map_item_potion",
			CURS_ATTR_N_MAP_ITEM_POTION );
	save_game_conf_color_sub( fp, "map_item_scroll",
			CURS_ATTR_N_MAP_ITEM_SCROLL );
	save_game_conf_color_sub( fp, "map_item_stick",
			CURS_ATTR_N_MAP_ITEM_STICK );
	save_game_conf_color_sub( fp, "map_item_accessory",
			CURS_ATTR_N_MAP_ITEM_ACCE );
	save_game_conf_color_sub( fp, "map_item_instrument",
			CURS_ATTR_N_MAP_ITEM_INST );
	save_game_conf_color_sub( fp, "map_item_light",
			CURS_ATTR_N_MAP_ITEM_LIGHT );
	save_game_conf_color_sub( fp, "map_item_spike",
			CURS_ATTR_N_MAP_ITEM_SPIKE );
	save_game_conf_color_sub( fp, "map_item_food",
			CURS_ATTR_N_MAP_ITEM_FOOD );
	save_game_conf_color_sub( fp, "map_item_chest",
			CURS_ATTR_N_MAP_ITEM_CHEST );
	save_game_conf_color_sub( fp, "map_item_rare_goods",
			CURS_ATTR_N_MAP_ITEM_RARE_GOODS );
	save_game_conf_color_sub( fp, "map_item_bone",
			CURS_ATTR_N_MAP_ITEM_BONE );
	save_game_conf_color_sub( fp, "map_item_coin",
			CURS_ATTR_N_MAP_ITEM_COIN );
	save_game_conf_color_sub( fp, "map_item_junk",
			CURS_ATTR_N_MAP_ITEM_JUNK );

	save_game_conf_color_sub( fp, "member_1",
			CURS_ATTR_N_MBR_1 );
	save_game_conf_color_sub( fp, "member_2",
			CURS_ATTR_N_MBR_2 );
	save_game_conf_color_sub( fp, "member_3",
			CURS_ATTR_N_MBR_3 );
	save_game_conf_color_sub( fp, "member_4",
			CURS_ATTR_N_MBR_4 );
	save_game_conf_color_sub( fp, "member_5",
			CURS_ATTR_N_MBR_5 );
	save_game_conf_color_sub( fp, "member_6",
			CURS_ATTR_N_MBR_6 );

	save_game_conf_color_sub( fp, "fx_member_plus",
			CURS_ATTR_N_FX_MBR_PLUS );
	save_game_conf_color_sub( fp, "fx_member_minus",
			CURS_ATTR_N_FX_MBR_MINUS );
	save_game_conf_color_sub( fp, "fx_member_critical",
			CURS_ATTR_N_FX_MBR_CRTCL );
	save_game_conf_color_sub( fp, "fx_monster_plus",
			CURS_ATTR_N_FX_MNSTR_PLUS );
	save_game_conf_color_sub( fp, "fx_monster_minus",
			CURS_ATTR_N_FX_MNSTR_MINUS );
	save_game_conf_color_sub( fp, "fx_monster_critical",
			CURS_ATTR_N_FX_MNSTR_CRTCL );
	save_game_conf_color_sub( fp, "vfx",
			CURS_ATTR_N_VFX );

	save_game_conf_color_sub( fp, "heat",
			CURS_ATTR_N_HEAT );
	save_game_conf_color_sub( fp, "cold",
			CURS_ATTR_N_COLD );
	save_game_conf_color_sub( fp, "mind",
			CURS_ATTR_N_MIND );
	save_game_conf_color_sub( fp, "acid",
			CURS_ATTR_N_ACID );

	return TRUE;
}

/***************************************************************
* ����ե�����ο��Υ����֤ζ��̽���
* FILE *fp : �ե�����
* char *name : ����̾��
* curs_attr_n_t attr_n : °�����ֹ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_color_sub(
	FILE *fp, char *name, curs_attr_n_t attr_n
)
{
	curs_attr_t	*attr;

	if( fp == NULL )
		return FALSE;
	if( name == NULL )
		return FALSE;

	attr = get_curs_attr();

	fprintf( fp, "\n" );
	fprintf( fp, "color = \"%s\"\n", cv_esc_quote_str( name ) );

	fprintf( fp, "\tfg_color = \"%s\"\n",
			cv_esc_quote_str( cv_color_to_name(
			attr[attr_n].fg ) ) );

	fprintf( fp, "\tbg_color = \"%s\"\n",
			cv_esc_quote_str( cv_color_to_name(
			attr[attr_n].bg ) ) );

	fprintf( fp, "\tattribute_underline = %d\n",
			chk_flg( attr[attr_n].attr, A_UNDERLINE ) );
	fprintf( fp, "\tattribute_reverse = %d\n",
			chk_flg( attr[attr_n].attr, A_REVERSE ) );
	fprintf( fp, "\tattribute_blink = %d\n",
			chk_flg( attr[attr_n].attr, A_BLINK ) );
	fprintf( fp, "\tattribute_bold = %d\n",
			chk_flg( attr[attr_n].attr, A_BOLD ) );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ桼������˥塼�Υ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_user_menu( FILE *fp, const ver_t *ver )
{
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# define user menu\n" );
	fprintf( fp, "# ex.\n" );
	fprintf( fp, "# user_menu {\n" );
	fprintf( fp, "# \t\"text\" \"command\"\n" );
	fprintf( fp, "# \t\"text\" \"command\"\n" );
	fprintf( fp, "# \t...\n" );
	fprintf( fp, "# }\n" );
	fprintf( fp, "\n" );
	fprintf( fp, "user_menu {\n" );

	for( i = 0; i < USER_MENU_MAX_N; i++ ){
		char	*name, *cmd;

		name = get_user_menu_name( i );
		cmd = get_user_menu_cmd( i );
		if( name == NULL )
			break;
		if( cmd == NULL )
			break;

		fprintf( fp, "\t\"%s\"", cv_esc_quote_str( name ) );
		fprintf( fp, "\t\"%s\"", cv_esc_quote_str( cmd ) );
		fprintf( fp, "\n" );
	}

	fprintf( fp, "}\n" );

	return TRUE;
}

/***************************************************************
* ����ե�����Υ���������ƤΥ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_key_tab( FILE *fp, const ver_t *ver )
{
	char	**key_tab;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	key_tab = get_key_tab();
	if( key_tab == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# bind key\n" );
	fprintf( fp, "# ex.\n" );
	fprintf( fp, "# set_key 'key' \"command\"\n" );
	fprintf( fp, "# unset_key 'key'\n" );
	fprintf( fp, "\n" );

	for( i = 0; i < KEY_TAB_MAX_N; i++ ){
		char	key[15 + 1];

		if( key_tab[i] == NULL )
			continue;

		if( isprint( (char)i ) ){
			sn_printf( key, 15, "%c", (char)i );
		} else if( ('A' - '@' <= i) && (i <= 'Z' - '@') ){
			sn_printf( key, 15, "^%c", (char)(i + '@') );
		} else {
			sn_printf( key, 15, "\\%04o", (char)i );
		}

		fprintf( fp, "set_key '%s'",
				cv_esc_quote_str( key ) );
		fprintf( fp, " \"%s\"\n",
				cv_esc_quote_str( key_tab[i] ) );
	}

	return TRUE;
}

/***************************************************************
* ����ե�����Υ���������ƤΥ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_func( FILE *fp, const ver_t *ver )
{
	long	i, j;
	const char	*m;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	fprintf( fp, "\n" );
	fprintf( fp, "# bind macro to function key\n" );
	fprintf( fp, "# ex.\n" );
	fprintf( fp, "# set_macro_func no. \"command\"\n" );
	fprintf( fp, "\n" );

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		m = get_macro_func( i );
		if( m == NULL )
			break;

		if( !save_game_conf_func_sub( fp, ver,
				"set_macro_func",
				NULL, i, m ) ){
			return FALSE;
		}
	}
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		m = get_macro_mouse_click( i );
		if( m == NULL )
			break;

		if( !save_game_conf_func_sub( fp, ver,
				"set_macro_mouse_click",
				NULL, i, m ) ){
			return FALSE;
		}
	}
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		m = get_macro_mouse_d_click( i );
		if( m == NULL )
			break;

		if( !save_game_conf_func_sub( fp, ver,
				"set_macro_mouse_double_click",
				NULL, i, m ) ){
			return FALSE;
		}
	}
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		m = get_macro_mouse_p_click( i );
		if( m == NULL )
			break;

		if( !save_game_conf_func_sub( fp, ver,
				"set_macro_mouse_press_and_click",
				NULL, i, m ) ){
			return FALSE;
		}
	}
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		m = get_macro_mouse_press( i );
		if( m == NULL )
			break;

		if( !save_game_conf_func_sub( fp, ver,
				"set_macro_mouse_press",
				NULL, i, m ) ){
			return FALSE;
		}
	}
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		m = get_macro_mouse_release( i );
		if( m == NULL )
			break;

		if( !save_game_conf_func_sub( fp, ver,
				"set_macro_mouse_release",
				NULL, i, m ) ){
			return FALSE;
		}
	}
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		m = get_macro_mouse_motion( i );
		if( m == NULL )
			break;

		if( !save_game_conf_func_sub( fp, ver,
				"set_macro_mouse_motion",
				NULL, i, m ) ){
			return FALSE;
		}
	}
	for( j = 0; j < LOOP_MAX_100; j++ ){
		for( i = 0; i < LOOP_MAX_1000; i++ ){
			const char	*joy_name;

			m = get_macro_joystick( j, i );
			if( m == NULL )
				break;

			joy_name = cv_joystick_kind_to_name( (joy_kind_t)j );
			if( joy_name == NULL )
				continue;

			if( !save_game_conf_func_sub( fp, ver,
					"set_macro_joystick",
					joy_name, i, m ) ){
				return FALSE;
			}
		}
	}

	return TRUE;
}

/***************************************************************
* ����ե�����Υ���������ƤΥ�����
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* const char *tag : ���̻�
* const char *joy : ���祤���ƥ��å��μ��̻�
* long n : ����ǥå���
* const char *macro : �ޥ���
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_conf_func_sub(
	FILE *fp,
	const ver_t *ver,
	const char *tag,
	const char *joy,
	long n,
	const char *macro
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( macro == NULL )
		return FALSE;

	if( macro[0] == '\0' )
		return TRUE;

	if( joy == NULL ){
		fprintf( fp, "%s %ld \"%s\"\n",
				tag, n, cv_esc_quote_str( macro ) );
	} else {
		fprintf( fp, "%s \"%s\" %ld \"%s\"\n",
				tag, joy, n, cv_esc_quote_str( macro ) );
	}

	return TRUE;
}

/***************************************************************
* ����������Υ�����(�С������ 1)
* const ver_t *ver : �ե�����ΥС������
* long n : �ǡ���������å��ֹ�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_data_cnf_ver_1( const ver_t *ver, long n )
{
	FILE	*fp;
	time_t	save_time_buf;
	struct tm	*save_time;
	bool_t	flg_txt = TRUE;

	if( ver == NULL )
		return FALSE;

	fp = open_game_data_cnf( 'w', n );
	if( fp == NULL )
		return FALSE;

	/* header */

	fprintf( fp, "%s%ld.%ld.%ld\n",
			STR_GAME_DATA_HEAD,
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

	if( !save_game_data_cnf_contents( fp, ver ) ){
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
* �����ࡦ�ǡ��������ƤΥ�����(�С������ 1)
* FILE *fp : �ե�����
* const ver_t *ver : �ե�����ΥС������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	save_game_data_cnf_contents(
	FILE *fp, const ver_t *ver
)
{
	bool_t	flg_err = FALSE;

	flg_err |= !save_game_conf_contents( fp, ver );
	flg_err |= !save_game_data_auto_mark_ls_ver_1( fp, ver, TRUE );

	if( flg_err )
		return FALSE;
	else
		return TRUE;
}

/***************************************************************
* ����ե�����ΥХå��å�
***************************************************************/

void	back_up_game_conf( void )
{
	rename_back_up_file( path_name_game_conf );
}

/***************************************************************
* ������ɥ���̾�����֤�
* win_kind_t k : ������ɥ��μ���
* return : ������ɥ���̾��
***************************************************************/

const char	*get_win_kind_name( win_kind_t k )
{
	switch( k ){
	case WIN_KIND_NULL:
		break;
	case WIN_KIND_MAP:
		return "window_map";
	case WIN_KIND_SEL_CONF:
		return "window_select_config";
	case WIN_KIND_MENU:
		return "window_menu";
	case WIN_KIND_MESSAGE:
		return "window_message";
	case WIN_KIND_STAT:
		return "window_status";
	case WIN_KIND_STAT_1:
		return "window_status_1";
	case WIN_KIND_STAT_2:
		return "window_status_2";
	case WIN_KIND_STAT_3:
		return "window_status_3";
	case WIN_KIND_STAT_4:
		return "window_status_4";
	case WIN_KIND_STAT_5:
		return "window_status_5";
	case WIN_KIND_STAT_6:
		return "window_status_6";
	case WIN_KIND_INPUT_NUM:
		return "window_input_number";
	case WIN_KIND_INPUT_STRING:
		return "window_input_string";
	case WIN_KIND_WORDS:
		return "window_words";
	case WIN_KIND_REPLAY:
		return "window_replay";
	case WIN_KIND_CLASS_EDIT:
		return "window_class_edit";
	case WIN_KIND_SKILL_EDIT:
		return "window_skill_edit";
	case WIN_KIND_CHR_SHEET:
		return "window_character_sheet";
	case WIN_KIND_MAX_N:
		break;
	}

	return NULL;
}

/***************************************************************
* ���祤���ƥ��å��μ��फ�饸�祤���ƥ��å��μ����̾�����Ѵ�
* joy_kind_t k : ���祤���ƥ��å��μ���
* return : ���祤���ƥ��å��μ����̾��
***************************************************************/

const char	*cv_joystick_kind_to_name( joy_kind_t k )
{
	switch( k ){
	case JOY_KIND_NULL:
		break;
	case JOY_KIND_PS:
		return "ps like";
	case JOY_KIND_SATURN:
		return "saturn like";
	case JOY_KIND_RAP3:
		return "real arcade pro.3";
	case JOY_KIND_MAX_N:
		break;
	}

	return "ps-like";
}

/***************************************************************
* ���祤���ƥ��å��μ����̾�����饸�祤���ƥ��å��μ�����Ѵ�
* const char *name : ���祤���ƥ��å��μ����̾��
* return : ���祤���ƥ��å��μ���
***************************************************************/

joy_kind_t	cv_joystick_name_to_kind( const char *name )
{
	if( name == NULL )
		return JOY_KIND_PS;

	if( strcmp( name, "ps like" ) == 0 )
		return JOY_KIND_PS;
	if( strcmp( name, "saturn like" ) == 0 )
		return JOY_KIND_SATURN;
	if( strcmp( name, "real arcade pro.3" ) == 0 )
		return JOY_KIND_RAP3;

	return JOY_KIND_PS;
}

/***************************************************************
* ���ֹ椫�鿧��ʸ������Ѵ�
* int color : ���ֹ�
* return : ����ʸ����
***************************************************************/

char	*cv_color_to_name( int color )
{
	switch( color ){
	case COLOR_BLACK:
		return "black";
	case COLOR_RED:
		return "red";
	case COLOR_GREEN:
		return "green";
	case COLOR_YELLOW:
		return "yellow";
	case COLOR_BLUE:
		return "blue";
	case COLOR_MAGENTA:
		return "magenta";
	case COLOR_CYAN:
		return "cyan";
	case COLOR_WHITE:
		return "white";
	}

	return "error";
}

/***************************************************************
* ����ʸ���󤫤鿧�ֹ���Ѵ�
* int color : ����ʸ����
* return : ���ֹ�
***************************************************************/

int	cv_name_to_color( char *name )
{
	if( name == NULL )
		return COLOR_WHITE;

	if( strcmp( name, "black" ) == 0 )
		return COLOR_BLACK;
	if( strcmp( name, "red" ) == 0 )
		return COLOR_RED;
	if( strcmp( name, "green" ) == 0 )
		return COLOR_GREEN;
	if( strcmp( name, "yellow" ) == 0 )
		return COLOR_YELLOW;
	if( strcmp( name, "blue" ) == 0 )
		return COLOR_BLUE;
	if( strcmp( name, "magenta" ) == 0 )
		return COLOR_MAGENTA;
	if( strcmp( name, "cyan" ) == 0 )
		return COLOR_CYAN;
	if( strcmp( name, "white" ) == 0 )
		return COLOR_WHITE;

	return COLOR_WHITE;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_gf_conf_c( void )
{
}
