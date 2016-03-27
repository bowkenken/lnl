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
* $Id: ending-space.c,v 1.19 2014/01/08 01:01:27 bowkenken Exp $
***************************************************************/

/***************************************************************
* ����ǥ��󥰤α���
***************************************************************/

#define	ENDING_SPACE_C
#include	"inc.h"

/***************************************************************
* �ѿ����
***************************************************************/

/***************************************************************
* ����
***************************************************************/

#define	CUI_STAR_MAX_N	2560
#define	CUI_STAR_DFLT_N	256

static const long XR = 16384;
static const long YR = 16384;
static const long ZR = 256;
static const long Z_SPEED = -1;
check_memory_def( check_memory_ending_space_c_XR )

typedef struct {
	long	x, y, z;
	long	drx, dry;
} star_t;

typedef struct {
	star_t	star[CUI_STAR_MAX_N];
	long	zv;
} space_t;

static space_t	g_space;
check_memory_def( check_memory_ending_space_c_g_space )

/***************************************************************
* �����åա�����
***************************************************************/

static long	g_frame;
static const long	g_roll_frame_n = 5;
check_memory_def( check_memory_ending_space_c_g_frame )

// ʸ���ֳ�
static const long	staff_roll_interval_width = 1;
static const long	staff_roll_interval_height = 2;
check_memory_def( check_memory_ending_space_c_staff_roll_interval_width )

static long	staff_roll_y;
static long	staff_roll_max_len;
check_memory_def( check_memory_ending_space_c_staff_roll_y )

static const long	FLICKER_N = 16;
check_memory_def( check_memory_ending_space_c_FLICKER_N )

#define STR_THE_END	\
	"                 The End                  "

const char	*g_str_staff_roll[] = {
	"            Director  bowkenken",
	" ",
	"         Programming  bowkenken",
	" ",
	"                  Graphic",
	"                  Design",
	"          Characters  [RPG DOT]",
	"               Items  Whitecat",
	"                 Map  REFMAP",
	"              Anchor  kokusi(yujyu)",
	"           Sanctuary  hiyo",
	"      Visual Effects  moja",
	"            Openning  URARA",
	"           Last Boss  naramura",
	"       Denzi's Tiles  Denzi",
	" ",
	"   Ending Photograph  Yoshinori Kamimura",
	" ",
	"    Music Production  Presence of Music",
	"       Sound Effects  OSA at The Match Makers",
	" ",
	"       Super Adviser  nnn",
	"                      lu",
	" ",
	"      Special Thanks  t-oikawa",
	"                      TeaMiKL",
	" ",
	"        L&L - Labyrinths & Legends        ",
	"          Copyright (c) 1993-2014         ",
	"            YOSHIMURA, Tomohiko           ",
	"           All rights reserved.           ",
	" ",
	"URL   : http://lnl.sourceforge.jp/",
	"E-mail: bowkenken@users.sourceforge.jp",
	" ",
	" ",
	"        Presented by  bowkenken",
	" ",
	" ",
	" ",
	" ",
	" ",
	" ",
	" ",
	" ",
	" ",
	" ",
	STR_THE_END,
	NULL,
};
check_memory_def( check_memory_ending_space_c_g_str_staff_roll )

const char *g_str_the_end = STR_THE_END;
check_memory_def( check_memory_ending_space_c_g_str_the_end )

/***************************************************************
* ����ν����
***************************************************************/

void	init_space( void )
{
	long	i;

	g_frame = 0;

	/* ���� */

	g_cui_star_n = CUI_STAR_DFLT_N;

	g_space.zv = Z_SPEED;
	for( i = 0; i < CUI_STAR_MAX_N; i++ ){
		g_space.star[i].x = randm( XR * 2 ) - XR;
		g_space.star[i].y = randm( YR * 2 ) - YR;
		g_space.star[i].z = randm( ZR );
	}

	/* �����åա����� */

	staff_roll_y = -SCREEN_HEIGHT;

	staff_roll_max_len = 1;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		long	len;

		if( g_str_staff_roll[i] == NULL )
			break;
		if( g_str_staff_roll[i][0] == '\0' )
			break;

		len = str_len_draw( g_str_staff_roll[i] );
		if( staff_roll_max_len < len )
			staff_roll_max_len = len;
	}
}

/***************************************************************
* ����Υ��ԡ��ɤ��®
* long azv : ��®��
* return : ®��
***************************************************************/

long	add_z_speed_space( long azv )
{
	g_space.zv += azv;

	return g_space.zv;
}

/***************************************************************
* ����ΰ�ư
***************************************************************/

void	move_space( void )
{
	long	max_n, i;

	max_n = get_star_n();
	for( i = 0; i < max_n; i++ ){
		g_space.star[i].z -= g_space.zv;
		g_space.star[i].z = (g_space.star[i].z % ZR + ZR) % ZR;
	}
}

/***************************************************************
* ���������
* bool_t flg_draw_staff_roll : �����åա���������褹�뤫?
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	draw_space( bool_t flg_draw_staff_roll )
{
	long	sx, sy, sw, sh;
	long	mx, my;
	long	fl;
	long	max_n, i;

	move_space();

	g_frame++;
	do {
		if( !flg_draw_staff_roll )
			break;
		if( get_scene() != SCENE_N_ENDING_STAFF_ROLL )
			break;
		if( (g_frame % g_roll_frame_n) != 0 )
			break;

		staff_roll_y += 1;
		wipe_all();

		break;
	} while( 0 );

	sx = 0;
	sy = 0;
	sw = SCREEN_WIDTH;
	sh = SCREEN_HEIGHT;
	mx = sx + sw / 2;
	my = sy + sh / 2;

	max_n = get_star_n();
	fl = max_n / FLICKER_N;
	if( fl < 1 )
		fl = 1;

	for( i = 0; i < max_n; i++ ){
		long drx, dry;
		long zz;

		zz = g_space.star[i].z + 1;
		drx = mx + g_space.star[i].x / zz / 16;
		dry = my + g_space.star[i].y / zz / 32;

		wipe_star( g_space.star[i].drx, g_space.star[i].dry );
		if( dry < sh )
			draw_star( drx, dry, zz );

		g_space.star[i].drx = drx;
		g_space.star[i].dry = dry;

		if( (i % fl) == 0 )
			if( flg_draw_staff_roll )
				draw_staff_roll();
	}

	if( flg_draw_staff_roll )
		draw_staff_roll();

	set_crsr( 0, 0 );
	sleep_msec( 100 );

	return TRUE;
}

/***************************************************************
* ��������
* long x : X ��ɸ
* long y : Y ��ɸ
* long z : Z ��ɸ
***************************************************************/

void	draw_star( long x, long y, long z )
{
	print_str( x, y, "." );
}

/***************************************************************
* ���ξõ�
* long x : X ��ɸ
* long y : Y ��ɸ
***************************************************************/

void	wipe_star( long x, long y )
{
	print_str( x, y, " " );
}

/***************************************************************
* �����åա����������
***************************************************************/

void	draw_staff_roll( void )
{
	long	sx, sw,sh;
	long	x, y;
	long	i;

	if( get_scene() == SCENE_N_ENDING_END ){
		draw_the_end();
		return;
	}

	sx = 0;
	sw = SCREEN_WIDTH;
	sh = SCREEN_HEIGHT;

	x = (sw - (staff_roll_interval_width * staff_roll_max_len)) / 2;
	x += sx;
	y = 0;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( g_str_staff_roll[i] == NULL )
			break;
		if( g_str_staff_roll[i][0] == '\0' )
			break;

		y = (i * staff_roll_interval_height) - staff_roll_y;

		if( y < 0 )
			continue;
		if( y >= sh )
			continue;

		draw_staff_roll_line( x, y, g_str_staff_roll[i] );
	}

	if( (y <= (sh / 2)) && (get_scene() != SCENE_N_ENDING_END) ){
		if( !g_flg_gui ){
			change_scene( SCENE_N_ENDING_END );
		}
	}
}

/***************************************************************
* The End ������
***************************************************************/

void	draw_the_end( void )
{
	long	sx, sw,sh;
	long	x, y;

	sx = 0;
	sw = SCREEN_WIDTH;
	sh = SCREEN_HEIGHT;

	x = (sw - (staff_roll_interval_width * staff_roll_max_len)) / 2;
	x += sx;
	y = sh / 2;

	draw_staff_roll_line( x, y, g_str_the_end );
}

/***************************************************************
* �����åա������ 1 �Ԥ�����
* long x : X ��ɸ
* long y : Y ��ɸ
* const char *str : 1 ��ʬ�Υ����åա�����
***************************************************************/

void	draw_staff_roll_line( long x, long y, const char *str )
{
	if( x < 0 )
		return;
	if( x >= SCREEN_WIDTH )
		return;
	if( y < 0 )
		return;
	if( y >= SCREEN_HEIGHT )
		return;

	print_str( x, y, MSG_S, str );
}

/***************************************************************
* ���ο����֤�
* return : ���ο�
***************************************************************/

long	get_star_n( void )
{
	if( g_cui_star_n <= 0 )
		return CUI_STAR_DFLT_N;
	if( g_cui_star_n > CUI_STAR_MAX_N )
		return CUI_STAR_MAX_N;

	return g_cui_star_n;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_ending_space_c( void )
{
	check_memory( check_memory_ending_space_c_XR,
			"ending-space.c: XR" );
	check_memory( check_memory_ending_space_c_g_space,
			"ending-space.c: g_space" );
	check_memory( check_memory_ending_space_c_g_frame,
			"ending-space.c: g_frame" );
	check_memory( check_memory_ending_space_c_staff_roll_interval_width,
			"ending-space.c: staff_roll_interval_width" );
	check_memory( check_memory_ending_space_c_staff_roll_y,
			"ending-space.c: staff_roll_y" );
	check_memory( check_memory_ending_space_c_FLICKER_N,
			"ending-space.c: FLICKER_N" );
	check_memory( check_memory_ending_space_c_g_str_staff_roll,
			"ending-space.c: g_str_staff_roll" );
	check_memory( check_memory_ending_space_c_g_str_the_end,
			"ending-space.c: g_str_the_end" );
}
