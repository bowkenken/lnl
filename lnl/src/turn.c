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
* $Id: turn.c,v 1.48 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ターン
***************************************************************/

#define	TURN_C
#include	"inc.h"

/***************************************************************
* 変数定義
***************************************************************/

static long	g_day, g_turn;
check_memory_def( check_memory_turn_c_g_turn )

/***************************************************************
* ターンの初期化
* return : ターン
***************************************************************/

long	init_turn()
{
	set_game_date( 999, 4, 1 );
	reset_turn( 10 * TURN_PER_HOUR );

	return g_turn;
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_turn( void )
{
}

/***************************************************************
* ターンを設定してリセット
* long n : 設定するターンの絶対値
* return : ターン
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
* ターンを進める
* long n : 進めるターンの相対値
* return : ターン
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
* ターンを 1 つ進める
* return : ターン
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
* ターンを設定
* long n : 設定するターンの絶対値
* return : ターン
***************************************************************/

long	set_turn( long n )
{
	return reset_turn( n );
}

/***************************************************************
* ターンを返す
* return : ターン
***************************************************************/

long	get_turn( void )
{
	return g_turn;
}

/***************************************************************
* 日付を設定してリセット
* return : 日付
***************************************************************/

long	reset_day( void )
{
	for( ; g_turn >= TURN_A_DAY; g_turn -= TURN_A_DAY )
		inc_day();

	return g_day;
}

/***************************************************************
* 日付を 1 日進める
* return : 日付
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
* 年月日で日付を設定
* long year : 年
* long month : 月
* long day : 日
* return : 日付
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
* 日付を設定
* long day : 日付
* return : 日付
***************************************************************/

long	set_game_day( long day )
{
	g_day = day;

	return g_day;
}

/***************************************************************
* 日付を返す
* return : 日付
***************************************************************/

long	get_game_day( void )
{
	return g_day;
}

/***************************************************************
* 現在のターンが昼か調べる
* return : 日の出か?
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
* 現在のターンが日の出か調べる
* return : 日の出か?
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
* 現在のターンが日の入りか調べる
* return : 日の入りか?
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
* 現在のターンが夜か調べる
* return : 夜か?
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
* 現在のターンが、どれくらい日の出の時間なのかの率を返す
* return : 日の出率
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
* 現在のターンが、どれくらい日の入りの時間なのかの率を返す
* return : 日の入り率
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
* 現在のターンのカレンダー文字列を返す
* return : カレンダー文字列
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
* 現在のターンのステータス用カレンダー文字列を返す
* return : ステータス用カレンダー文字列
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
* 現在のターンの曜日文字列を返す
* return : 曜日文字列を返す
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
* 現在の曜日を返す
* return : 曜日
***************************************************************/

day_of_week_t	get_day_of_week( void )
{
	return( (day_of_week_t)(get_game_day() % DAY_OF_WEEK_MAX_N) );
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_turn_c( void )
{
	check_memory( check_memory_turn_c_g_turn,
			"turn.c: g_turn" );
}
