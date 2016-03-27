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
* $Id: ending-ep.c,v 1.14 2014/01/08 01:01:27 bowkenken Exp $
***************************************************************/

/***************************************************************
* ���ԥ���
***************************************************************/

#define	ENDING_EP_C
#include	"inc.h"

/***************************************************************
* �ѿ����
***************************************************************/

static scene_n_t	pre_scene;
static bool_t	g_flg_skip_scene;
check_memory_def( check_memory_ending_ep_c_pre_scene )

#define	EPILOGUE_MAX_LEN	40
#define	EPILOGUE_LINE_MAX_N	16
static const	char *g_str_ending[EPILOGUE_LINE_MAX_N + 1];
check_memory_def( check_memory_ending_ep_c_g_str_ending )
static long	epilogue_len;
static long	g_cur_draw_epilogue_n;
check_memory_def( check_memory_ending_ep_c_epilogue_len )
static long	mx[EPILOGUE_LINE_MAX_N][EPILOGUE_MAX_LEN];
check_memory_def( check_memory_ending_ep_c_mx )
static long	my[EPILOGUE_LINE_MAX_N][EPILOGUE_MAX_LEN];
check_memory_def( check_memory_ending_ep_c_my )

#define	ENDING_EPILOGUE_TIME	45
#define	ENDING_SPACE_TIME	5
static long	frame;
static time_t	wait_time;
check_memory_def( check_memory_ending_ep_c_frame )
static const long FRAME_PER_CHAR = 2;
static const long WAIT_FRAME_CHAR = 10;
check_memory_def( check_memory_ending_ep_c_FRAME_PER_CHAR )

/***************************************************************
* ����ǥ��󥰤ν����
***************************************************************/

void	init_ending( void )
{
	set_flg_skip_scene_ending( FALSE );
	init_space();
	init_epilogue();
}

/***************************************************************
* ���ԥ����ν����
***************************************************************/

void	init_epilogue( void )
{
	long	base_x[EPILOGUE_LINE_MAX_N];
	long	base_y[EPILOGUE_LINE_MAX_N];
	long	i, j, k;

	pre_scene = SCENE_N_ENDING;

	g_cur_draw_epilogue_n = 0;

	wait_time = 0;
	frame = 0;

	k = 0;
	for( i = 0; i < EPILOGUE_LINE_MAX_N; i++ ){
		g_str_ending[i] = &(MSG_EPILOGUE[k]);
		g_str_ending[i + 1] = NULL;

		for( j = 0; j < EPILOGUE_MAX_LEN; j++ ){
			if( MSG_EPILOGUE[k] == '\0' )
				break;
			if( MSG_EPILOGUE[k] == '\n' ){
				k++;
				break;
			}
			k++;
		}
		if( MSG_EPILOGUE[k] == '\0' )
			break;
	}

	epilogue_len = 1;
	for( i = 0; i < EPILOGUE_LINE_MAX_N; i++ ){
		if( g_str_ending[i] == NULL )
			break;

		k = 0;
		j = 0;
		for( ; j < EPILOGUE_MAX_LEN; j++ ){
			if( g_str_ending[i][k] == '\0' )
				break;
			if( g_str_ending[i][k] == '\n' ){
				k++;
				break;
			}

			k += get_next_char_len( &(g_str_ending[i][k]) );
		}

		base_x[i] = (SCREEN_WIDTH - (j * 2)) / 2;
		base_y[i] = SCREEN_HEIGHT / 2;

		epilogue_len = max_l( epilogue_len, j );
	}

	for( i = 0; i < EPILOGUE_LINE_MAX_N; i++ ){
		if( g_str_ending[i] == NULL )
			break;

		for( j = 0; j < epilogue_len; j++ ){
			mx[i][j] = base_x[i] + (j * 2);
			my[i][j] = base_y[i] + i;
		}
	}
}

/***************************************************************
* ����ǥ��󥰲��̤�����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	draw_ending( void )
{
	if( !g_flg_cui ){
		sleep_msec( 100 );
		return TRUE;
	}

	frame++;

	if( get_scene() == SCENE_N_ENDING ){
		pre_scene = SCENE_N_ENDING;
		wipe_all();

		// �������ڤ��ؤ�
		if( !g_flg_gui ){
			wait_time = 0;
			change_scene( SCENE_N_ENDING_EPILOGUE );
		}
	}

	// ���ԥ���

	if( get_scene() == SCENE_N_ENDING_EPILOGUE ){
		// �����
		if( (pre_scene != SCENE_N_ENDING_EPILOGUE)
				|| (wait_time <= 0) ){
			pre_scene = SCENE_N_ENDING_EPILOGUE;
			wait_time = time( NULL ) + ENDING_EPILOGUE_TIME;
			frame = 0;
		}

		// ����
		draw_epilogue();

		if( get_flg_skip_scene_ending()
				|| (time( NULL ) > wait_time) ){
			set_flg_skip_scene_ending( FALSE );
			wipe_all();

			// �������ڤ��ؤ�
			if( !g_flg_gui ){
				wait_time = 0;
				change_scene( SCENE_N_ENDING_SPACE );
			}
		}
	}

	// ����

	if( get_scene() == SCENE_N_ENDING_SPACE ){
		// �����
		if( (pre_scene != SCENE_N_ENDING_SPACE)
				|| (wait_time <= 0) ){
			pre_scene = SCENE_N_ENDING_SPACE;
			wipe_all();
			wait_time = time( NULL ) + ENDING_SPACE_TIME;
			frame = 0;
		}

		// ����
		draw_space( FALSE );

		if( get_flg_skip_scene_ending()
				|| (time( NULL ) > wait_time) ){
			set_flg_skip_scene_ending( FALSE );
			wipe_all();

			// �������ڤ��ؤ�
			if( !g_flg_gui ){
				wait_time = 0;
				change_scene( SCENE_N_ENDING_STAFF_ROLL );
			}
		}
	}

	// �����åա�����

	if( get_scene() == SCENE_N_ENDING_STAFF_ROLL ){
		if( get_flg_skip_scene_ending() ){
			set_flg_skip_scene_ending( FALSE );
			wipe_all();

			// �������ڤ��ؤ�
			if( !g_flg_gui ){
				change_scene( SCENE_N_ENDING_END );
			}
		}

		// ����
		return draw_space( TRUE );
	}

	// The End

	if( get_scene() == SCENE_N_ENDING_END ){
		// �����
		if( pre_scene != SCENE_N_ENDING_END )
			wipe_all();

		// ����
		return draw_space( TRUE );
	}

	return TRUE;
}

/***************************************************************
* ����ǥ��󥰤Υ�����򥹥��å�
* bool_t flg : �����åפ��뤫?
***************************************************************/

void	set_flg_skip_scene_ending( bool_t flg )
{
	g_flg_skip_scene = flg;
}

/***************************************************************
* ����ǥ��󥰤Υ�����򥹥��åפ��뤫Ĵ�٤�
* return : �����åפ��뤫?
***************************************************************/

bool_t	get_flg_skip_scene_ending( void )
{
	return g_flg_skip_scene;
}

/***************************************************************
* ���ԥ���������
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	draw_epilogue( void )
{
	// ���ȡ��꡼������

	draw_epilogue_story( frame );

	set_crsr( 0, 0 );
	sleep_msec( 100 );

	return TRUE;
}

/***************************************************************
* ���ԥ��������� (���ȡ��꡼)
* long frame : ���ߤΥե졼��
***************************************************************/

void	draw_epilogue_story( long frame )
{
	long	n, draw_n;
	long	next_len;
	const char	*p;
	long	i, j, k;

	n = 0;
	draw_n = (frame / FRAME_PER_CHAR) - WAIT_FRAME_CHAR;

	for( i = 0; i < EPILOGUE_LINE_MAX_N; i++ ){
		if( g_str_ending[i] == NULL )
			break;

		k = 0;
		for( j = 0; j < epilogue_len; j++ ){
			if( g_str_ending[i][k] == '\0' )
				break;
			if( g_str_ending[i][k] == '\n' ){
				k++;
				break;
			}

			if( n < g_cur_draw_epilogue_n )
				continue;
			if( n >= draw_n )
				break;

			p = &(g_str_ending[i][k]);
			print_str( mx[i][j], my[i][j],
					get_next_char_str( p ) );

			next_len = get_next_char_len( p );
			k += next_len;
			n += next_len;
		}
	}

	g_cur_draw_epilogue_n = n;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_ending_ep_c( void )
{
	check_memory( check_memory_ending_ep_c_pre_scene,
			"ending-ep.c: pre_scene" );
	check_memory( check_memory_ending_ep_c_g_str_ending,
			"ending-ep.c: g_str_ending" );
	check_memory( check_memory_ending_ep_c_epilogue_len,
			"ending-ep.c: epilogue_len" );
	check_memory( check_memory_ending_ep_c_mx,
			"ending-ep.c: mx" );
	check_memory( check_memory_ending_ep_c_my,
			"ending-ep.c: my" );
	check_memory( check_memory_ending_ep_c_frame,
			"ending-ep.c: frame" );
	check_memory( check_memory_ending_ep_c_FRAME_PER_CHAR,
			"ending-ep.c: FRAME_PER_CHAR" );
}
