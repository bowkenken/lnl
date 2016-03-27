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
* $Id: turn.c,v 1.48 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ������
***************************************************************/

#define	TURN_C
#include	"inc.h"

/***************************************************************
* �ѿ����
***************************************************************/

static long	g_day, g_turn;
check_memory_def( check_memory_turn_c_g_turn )

/***************************************************************
* ������ν����
* return : ������
***************************************************************/

long	init_turn()
{
	set_game_date( 999, 4, 1 );
	reset_turn( 10 * TURN_PER_HOUR );

	return g_turn;
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_turn( void )
{
}

/***************************************************************
* ����������ꤷ�ƥꥻ�å�
* long n : ���ꤹ�륿�����������
* return : ������
***************************************************************/

long	reset_turn( long n )
{
	g_turn = n;

	if( g_turn >= 0 )
		g_day += g_turn / TURN_A_DAY;
	else
		g_day -= labs( g_turn ) / TURN_A_DAY + 1;

	g_turn %= TURN_A_DAY;
	g_turn += TURN_A_DAY;
	g_turn %= TURN_A_DAY;

	return g_turn;
}

/***************************************************************
* �������ʤ��
* long n : �ʤ�륿�����������
* return : ������
***************************************************************/

long	add_turn( long n )
{
	long	ret;
	long	i;

	ret = -1;

	for( i = 0; i < n; i++ )
		ret = inc_turn();

	return ret;
}

/***************************************************************
* ������� 1 �Ŀʤ��
* return : ������
***************************************************************/

long	inc_turn( void )
{
	g_turn++;
	draw_misc_stat_time( FALSE );
	reset_day();

	chk_morning_glow( g_turn );
	chk_evening_glow( g_turn );
	chk_discount_day();
	chk_discount_queue();

	inc_turn_all_item();
	inc_turn_all_fx();
	inc_turn_all_mnstr();

	return g_turn;
}

/***************************************************************
* �����������
* long n : ���ꤹ�륿�����������
* return : ������
***************************************************************/

long	set_turn( long n )
{
	return reset_turn( n );
}

/***************************************************************
* ��������֤�
* return : ������
***************************************************************/

long	get_turn( void )
{
	return g_turn;
}

/***************************************************************
* ���դ����ꤷ�ƥꥻ�å�
* return : ����
***************************************************************/

long	reset_day( void )
{
	for( ; g_turn >= TURN_A_DAY; g_turn -= TURN_A_DAY )
		inc_day();

	return g_day;
}

/***************************************************************
* ���դ� 1 ���ʤ��
* return : ����
***************************************************************/

long	inc_day( void )
{
	g_day++;

	inc_day_all_fx();

	chk_request_limit();
	chk_request_npc_contract();

	return g_day;
}

/***************************************************************
* ǯ���������դ�����
* long year : ǯ
* long month : ��
* long day : ��
* return : ����
***************************************************************/

long	set_game_date( long year, long month, long day )
{
	g_day = 0;
	g_day += year * 360;
	g_day += (month - 1) * 30;
	g_day += day - 1;

	return g_day;
}

/***************************************************************
* ���դ�����
* long day : ����
* return : ����
***************************************************************/

long	set_game_day( long day )
{
	g_day = day;

	return g_day;
}

/***************************************************************
* ���դ��֤�
* return : ����
***************************************************************/

long	get_game_day( void )
{
	return g_day;
}

/***************************************************************
* ���ߤΥ������뤫Ĵ�٤�
* return : ���νФ�?
***************************************************************/

bool_t	chk_day( void )
{
	if( chk_morning() )
		return FALSE;
	if( chk_evening() )
		return FALSE;
	if( chk_night() )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ���ߤΥ��������νФ�Ĵ�٤�
* return : ���νФ�?
***************************************************************/

bool_t	chk_morning( void )
{
	long	turn;

	turn = get_turn() % TURN_A_DAY;

	if( turn < (MORNING_HOUR * TURN_PER_HOUR) )
		return FALSE;
	if( turn >= ((MORNING_HOUR + 1) * TURN_PER_HOUR) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ���ߤΥ������������꤫Ĵ�٤�
* return : �������꤫?
***************************************************************/

bool_t	chk_evening( void )
{
	long	turn;

	turn = get_turn() % TURN_A_DAY;

	if( turn < (EVENING_HOUR * TURN_PER_HOUR) )
		return FALSE;
	if( turn >= ((EVENING_HOUR + 1) * TURN_PER_HOUR) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ���ߤΥ������뤫Ĵ�٤�
* return : �뤫?
***************************************************************/

bool_t	chk_night( void )
{
	long	turn;
	long	morning;
	long	evening;

	turn = get_turn() % TURN_A_DAY;
	morning = MORNING_HOUR * TURN_PER_HOUR;
	evening = EVENING_HOUR * TURN_PER_HOUR;

	if( turn < morning )
		return TRUE;
	if( turn >= evening )
		return TRUE;
	return FALSE;
}

/***************************************************************
* ���ߤΥ����󤬡��ɤ줯�餤���νФλ��֤ʤΤ���Ψ���֤�
* return : ���ν�Ψ
***************************************************************/

rate_t	get_morning_rate( void )
{
	long	turn;
	rate_t	rate;

	turn = get_turn() % TURN_A_DAY;

	rate = _100_PERCENT * (turn - (MORNING_HOUR * TURN_PER_HOUR));
	rate /= TURN_PER_HOUR;
	if( rate < 0 )
		rate = 0;
	if( rate > _100_PERCENT )
		rate = _100_PERCENT;

	return rate;
}

/***************************************************************
* ���ߤΥ����󤬡��ɤ줯�餤��������λ��֤ʤΤ���Ψ���֤�
* return : ��������Ψ
***************************************************************/

rate_t	get_evening_rate( void )
{
	long	turn;
	rate_t	rate;

	turn = get_turn() % TURN_A_DAY;

	rate = _100_PERCENT * (turn - (EVENING_HOUR * TURN_PER_HOUR));
	rate /= TURN_PER_HOUR;
	if( rate < 0 )
		rate = 0;
	if( rate > _100_PERCENT )
		rate = _100_PERCENT;

	return rate;
}

/***************************************************************
* ���ߤΥ�����Υ�������ʸ������֤�
* return : ��������ʸ����
***************************************************************/

char	*get_calendar_str( void )
{
	static char	s[127 + 1];
	long	game_day, turn;
	long	year, month, day, hour, minute;
	char	*week;

	game_day = get_game_day();
	turn = get_turn();

	year = (game_day / 360);
	month = (game_day / 30) % 12 + 1;
	day = game_day % 30 + 1;
	hour = (turn / TURN_PER_HOUR) % 24;
	minute = (turn / TURN_PER_MINUTE) % 60;
	week = get_day_of_week_name();

	sn_printf( s, 127, MSG_CALENDAR,
			year, month, day, week, hour, minute );

	return s;
}

/***************************************************************
* ���ߤΥ�����Υ��ơ������ѥ�������ʸ������֤�
* return : ���ơ������ѥ�������ʸ����
***************************************************************/

char	*get_stat_time_str( void )
{
	static char	s[40 + 1];
	long	turn;
	long	hour, minute;

	turn = get_turn();
	hour = (turn / TURN_PER_HOUR) % 24;
	minute = (turn / TURN_PER_MINUTE) % 60;

	sn_printf( s, 40, MSG_STAT_TIME, hour, minute );

	return s;
}

/***************************************************************
* ���ߤΥ����������ʸ������֤�
* return : ����ʸ������֤�
***************************************************************/

char	*get_day_of_week_name( void )
{
	switch( get_day_of_week() ){
	case DAY_OF_WEEK_ELEC:
		return MSG_DAY_OF_WEEK_ELEC;
	case DAY_OF_WEEK_PHYS:
		return MSG_DAY_OF_WEEK_PHYS;
	case DAY_OF_WEEK_HEAT:
		return MSG_DAY_OF_WEEK_HEAT;
	case DAY_OF_WEEK_COLD:
		return MSG_DAY_OF_WEEK_COLD;
	case DAY_OF_WEEK_WIND:
		return MSG_DAY_OF_WEEK_MIND;
	case DAY_OF_WEEK_ACID:
		return MSG_DAY_OF_WEEK_ACID;
	case DAY_OF_WEEK_POIS:
		return MSG_DAY_OF_WEEK_POIS;
	case DAY_OF_WEEK_MAX_N:
		break;
	}

	return MSG_NULL;
}

/***************************************************************
* ���ߤ��������֤�
* return : ����
***************************************************************/

day_of_week_t	get_day_of_week( void )
{
	return( (day_of_week_t)(get_game_day() % DAY_OF_WEEK_MAX_N) );
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_turn_c( void )
{
	check_memory( check_memory_turn_c_g_turn,
			"turn.c: g_turn" );
}
