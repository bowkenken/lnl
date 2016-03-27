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
* $Id: map-event.c,v 1.8 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* マップ・イベント
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
* マップ・イベントをリセット
***************************************************************/

void	reset_map_event( void )
{
	reset_map_event_func();
	reset_map_event_pos();
}

/***************************************************************
* マップ・イベントのコールバックをリセット
***************************************************************/

void	reset_map_event_func( void )
{
	long	i;

	for( i = 0; i < MAP_EVENT_MAX_N; i++ )
		map_event_func[i] = NULL;
}

/***************************************************************
* マップ・イベントの座標をリセット
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
* マップのイベントをチェックしてコールバックを実行
* long x : X 座標
* long y : Y 座標
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
* イベントのコールバックを実行
* char mnr : マップ・イベント識別文字
* long x : X 座標
* long y : Y 座標
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
* テーブルからコールバックを登録
* map_event_tab_t *tab : テーブル
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
* コールバックを登録
* char mnr : マップ・イベント識別文字
* map_event_func_t func : 登録するコールバック
* return : 先に登録されていたコールバック
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
* コールバックを返す
* char mnr : マップ・イベント識別文字
* return : 登録されているコールバック
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
* イベントの座標を設定
* char mnr : マップ・イベント識別文字
* long x : X 座標
* long y : Y 座標
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
* イベントの座標を返す
* char mnr : マップ・イベント識別文字
* return : イベントの座標
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
* 識別文字からイベント番号に変換
* char mnr : マップ・イベント識別文字
* return : イベント番号
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
* メモリー・チェック
***************************************************************/

void	check_memory_map_event_c( void )
{
	check_memory( check_memory_map_event_c_map_event_func,
			"map-event.c: map_event_func" );
	check_memory( check_memory_map_event_c_map_event_pos,
			"map-event.c: map_event_pos" );
}
