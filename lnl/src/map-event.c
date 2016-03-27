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
* $Id: map-event.c,v 1.8 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �ޥåס����٥��
***************************************************************/

#define	MAP_EVENT_C
#include	"inc.h"

/***************************************************************/

#define	MAP_EVENT_MAX_N	(10 + ('z' - 'a' + 1))

static map_event_func_t	map_event_func[MAP_EVENT_MAX_N];
check_memory_def( check_memory_map_event_c_map_event_func )
static pos_t	map_event_pos[MAP_EVENT_MAX_N];
check_memory_def( check_memory_map_event_c_map_event_pos )

/***************************************************************
* �ޥåס����٥�Ȥ�ꥻ�å�
***************************************************************/

void	reset_map_event( void )
{
	reset_map_event_func();
	reset_map_event_pos();
}

/***************************************************************
* �ޥåס����٥�ȤΥ�����Хå���ꥻ�å�
***************************************************************/

void	reset_map_event_func( void )
{
	long	i;

	for( i = 0; i < MAP_EVENT_MAX_N; i++ )
		map_event_func[i] = NULL;
}

/***************************************************************
* �ޥåס����٥�Ȥκ�ɸ��ꥻ�å�
***************************************************************/

void	reset_map_event_pos( void )
{
	long	i;

	for( i = 0; i < MAP_EVENT_MAX_N; i++ ){
		map_event_pos[i].x = MAP_DEL_X;
		map_event_pos[i].y = MAP_DEL_Y;
	}
}

/***************************************************************
* �ޥåפΥ��٥�Ȥ�����å����ƥ�����Хå���¹�
* long x : X ��ɸ
* long y : Y ��ɸ
***************************************************************/

void	chk_map_event( long x, long y )
{
	dun_t	*dun = get_dun();

	if( !clip_pos( x, y ) )
		return;
	if( dun->map.obj.mjr[y][x] != FACE_MJR_FLOOR )
		return;

	exec_map_event( dun->map.obj.mnr[y][x], x, y );
}

/***************************************************************
* ���٥�ȤΥ�����Хå���¹�
* char mnr : �ޥåס����٥�ȼ���ʸ��
* long x : X ��ɸ
* long y : Y ��ɸ
***************************************************************/

void	exec_map_event( char mnr, long x, long y )
{
	map_event_func_t	func;

	func = get_map_event_func( mnr );
	if( func == NULL )
		return;

	(*func)( x, y );
}

/***************************************************************
* �ơ��֥뤫�饳����Хå�����Ͽ
* map_event_tab_t *tab : �ơ��֥�
***************************************************************/

void	set_map_event_tab( map_event_tab_t *tab )
{
	long	i;

	if( tab == NULL )
		return;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( tab[i].mnr == '\0' )
			break;

		set_map_event_func( tab[i].mnr, tab[i].func );
	}
}

/***************************************************************
* ������Хå�����Ͽ
* char mnr : �ޥåס����٥�ȼ���ʸ��
* map_event_func_t func : ��Ͽ���륳����Хå�
* return : �����Ͽ����Ƥ���������Хå�
***************************************************************/

map_event_func_t	set_map_event_func(
	char mnr, map_event_func_t func
)
{
	long	n;
	map_event_func_t	pre;

	n = cv_face_to_map_event_n( mnr );
	if( n < 0 )
		return NULL;

	pre = map_event_func[n];
	map_event_func[n] = func;
	return pre;
}

/***************************************************************
* ������Хå����֤�
* char mnr : �ޥåס����٥�ȼ���ʸ��
* return : ��Ͽ����Ƥ��륳����Хå�
***************************************************************/

map_event_func_t	get_map_event_func( char mnr )
{
	long	n;

	n = cv_face_to_map_event_n( mnr );
	if( n < 0 )
		return NULL;

	return map_event_func[n];
}

/***************************************************************
* ���٥�Ȥκ�ɸ������
* char mnr : �ޥåס����٥�ȼ���ʸ��
* long x : X ��ɸ
* long y : Y ��ɸ
***************************************************************/

void	set_map_event_pos( char mnr, long x, long y )
{
	long	n;

	n = cv_face_to_map_event_n( mnr );
	if( n < 0 )
		return;

	map_event_pos[n].x = x;
	map_event_pos[n].y = y;
}

/***************************************************************
* ���٥�Ȥκ�ɸ���֤�
* char mnr : �ޥåס����٥�ȼ���ʸ��
* return : ���٥�Ȥκ�ɸ
***************************************************************/

pos_t	get_map_event_pos( char mnr )
{
	long	n;
	pos_t	pos;

	pos.x = MAP_DEL_X;
	pos.y = MAP_DEL_Y;

	n = cv_face_to_map_event_n( mnr );
	if( n < 0 )
		return pos;

	return map_event_pos[n];
}

/***************************************************************
* ����ʸ�����饤�٥���ֹ���Ѵ�
* char mnr : �ޥåס����٥�ȼ���ʸ��
* return : ���٥���ֹ�
***************************************************************/

long	cv_face_to_map_event_n( char mnr )
{
	long	n;

	if( ('0' <= mnr) && (mnr <= '9') )
		n = mnr - '0';
	else if( ('a' <= mnr) && (mnr <= 'z') )
		n = mnr - 'a' + 10;
	else
		return -1;

	if( n < 0 )
		return -1;
	if( n >= MAP_EVENT_MAX_N )
		return -1;

	return n;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_map_event_c( void )
{
	check_memory( check_memory_map_event_c_map_event_func,
			"map-event.c: map_event_func" );
	check_memory( check_memory_map_event_c_map_event_pos,
			"map-event.c: map_event_pos" );
}
