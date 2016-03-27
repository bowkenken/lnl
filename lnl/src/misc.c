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
* $Id: misc.c,v 1.51 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* その他
***************************************************************/

#define	MISC_C
#include	"inc.h"

/***************************************************************/

/* 乱数の種 */

static long	randm_seed = 1;
check_memory_def( check_memory_misc_c_randm_seed )
static long	randm_seed_gui = 1;
check_memory_def( check_memory_misc_c_randm_seed_gui )

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_misc( void )
{
}

/***************************************************************
* 金貨の枚数をコンマ・フォーマット文字列に変換
* long n : 数値
* return : コンマ・フォーマット文字列
***************************************************************/

char	*fmt_gold( gold_t gold )
{
	return( fmt_num( (long)(gold) ) );
}

/***************************************************************
* 数値をコンマ・フォーマット文字列に変換
* long n : 数値
* return : コンマ・フォーマット文字列
***************************************************************/

char	*fmt_num( long n )
{
	long	sg;
	static char	str[32 + 1];
	long	max_len;
	char	*head;
	char	str_tmp[4 + 1];
	long	i;

	sg = sgn_l( n );

	max_len = (sizeof( str ) / sizeof( char )) - 1;

	head = &(str[max_len]);
	*head = '\0';
	head--;

	for( i = 0; i < max_len; i++ ){
		long	n1;

		n1 = labs( n ) % 10;

		sn_printf( str_tmp, 4, "%1ld", (long)n1 );
		head--;
		*head = str_tmp[0];

		n /= 10;
		if( n == 0 )
			break;

		if( (i % 3) == 2 ){
			head--;
			*head = ',';
		}
	}

	if( sg <= -1 ){
		head--;
		*head = '-';
	}

	return head;
}

/***************************************************************
* コンマ・フォーマット文字列を数値に変換
* long n : コンマ・フォーマット文字列
* return : 数値
***************************************************************/

long	un_fmt_num( const char *s )
{
	long	sg, n;
	long	i;

	sg = +1;
	n = 0;

	for( i = 0; i < LOOP_MAX_100; i++, s++ ){
		if( *s == '\0' )
			break;
		if( *s == ',' )
			continue;
		if( *s == '+' )
			continue;
		if( *s == '-' ){
			sg = -sg;
			continue;
		}
		if( !isdigit( *s ) )
			break;

		n *= 10;
		n += *s - '0';
	}

	n *= sg;

	return n;
}

/***************************************************************
* sprintf のパディングに指定するフィールド幅を調整する
* const char *s : フォーマットに指定する引数
* long min_len : 最小フィールド幅
* return : 調整された最小フィールド幅
***************************************************************/

long	get_pading_len( const char *s, long min_len )
{
	long	len;

	if( s == NULL )
		return 0;

	len = str_len_draw( s );
	if( len >= min_len )
		return min_len;

	len = min_len - len;
	len += str_len_std( s );
	return len;
}

/***************************************************************
* long 数値の +- の符号を返す
* long n : 数値
* return : 符号
***************************************************************/

long	sgn_l( long n )
{
	if( n > 0 )
		return +1;
	else if( n < 0 )
		return -1;
	else
		return +-0;
}

/***************************************************************
* 2 つの long 数値の小さい方を返す
* long n1 : 数値 1
* long n2 : 数値 2
* return : 小さい方の数値
***************************************************************/

long	min_l( long n1, long n2 )
{
	if( n1 < n2 )
		return n1;
	else
		return n2;
}

/***************************************************************
* 2 つの long 数値の大きい方を返す
* long n1 : 数値 1
* long n2 : 数値 2
* return : 大きい方の数値
***************************************************************/

long	max_l( long n1, long n2 )
{
	if( n1 > n2 )
		return n1;
	else
		return n2;
}

/***************************************************************
* 乱数の種を初期化
* long n : 種
***************************************************************/

void	srandm( long n )
{
	randm_seed = n;
	randm_seed_gui = n;
}

/***************************************************************
* 乱数の種を返す
* long n : 種
***************************************************************/

long	get_randm_seed( void )
{
	return randm_seed;
}

/***************************************************************
* 0 〜指定値未満の乱数を返す
* long n : 指定値
* return : 乱数
***************************************************************/

long	randm( long n )
{
	long	i, max_i;

	max_i = randm_sub( 3 );
	for( i = 0; i < max_i; i++ )
		randm_sub( n );

	return( randm_sub( n ) );
}

/***************************************************************
* 0 〜指定値未満の乱数を返す
* long n : 指定値
* return : 乱数
***************************************************************/

long	randm_sub( long n )
{
	long	a;

	randm_seed += 15349;
	randm_seed *= 3793;
	randm_seed += 598393;
	a = (randm_seed & 0xffff0000) >> 16;
	randm_seed = ((randm_seed & 0x0000ffff) << 16) + a;
	randm_seed += 379;
	randm_seed = labs( randm_seed );

	if( n > 0 )
		return( randm_seed % n );
	else
		return 0;
}

/***************************************************************
* 乱数が指定の率(%)以下になるか?
* long n : 指定の率(%)
* return : 指定の率(%)以下か?
***************************************************************/

bool_t	rate_randm( rate_t rate )
{
	return( randm( _100_PERCENT ) < rate );
}

/***************************************************************
* 乱数が指定の数値分の 1 になるか?
* long n : 指定の数値
* return : 指定の数値分の 1 か?
***************************************************************/

bool_t	per_randm( long per )
{
	return( randm( per ) == 0 );
}

/***************************************************************
* 指定の率の 100% を超えた分の数の乱数を返す
* rate_t rate : 指定の率
* return : 100% を超えた分の数
***************************************************************/

long	count_randm_rate( rate_t rate )
{
	long	n;
	rate_t	r;

	if( rate < _100_PERCENT )
		return rate_randm( rate );

	n = 0;
	for( r = randm( rate ) + 1; r > 0; r -= _100_PERCENT )
		n++;

	return n;
}

/***************************************************************
* 0 〜指定値未満の乱数を返す (リプレイに影響しない GUI 用)
* long n : 指定値
* return : 乱数
***************************************************************/

long	gui_randm( long n )
{
	long	a;

	randm_seed_gui += 15349;
	randm_seed_gui *= 3793;
	randm_seed_gui += 598393;
	a = (randm_seed_gui & 0xffff0000) >> 16;
	randm_seed_gui = ((randm_seed_gui & 0x0000ffff) << 16) + a;
	randm_seed_gui += 379;
	randm_seed_gui = labs( randm_seed_gui );

	if( n > 0 )
		return( randm_seed_gui % n );
	else
		return 0;
}

/***************************************************************
* 数値で率(%)を修整する
* rate_t rate : 率(%)
* long n : 数値
* return : 修整後の率(%)
***************************************************************/

rate_t	modified_rate( rate_t rate, long n )
{
	if( n >= +1 )
		rate += 20 * labs( n );
	if( n <= -1 )
		rate -= 10 * labs( n );

	if( rate < MODIFIED_MIN_RATE )
		rate = MODIFIED_MIN_RATE;

	return rate;
}

/***************************************************************
* バージョンが指定値より古いか?
* const ver_t *ver : バージョン
* long mjr : メジャー・バージョン
* long mnr : マイナー・バージョン
* long pat : パッチ・レベル
* return : 指定値より古いか?
***************************************************************/

bool_t	chk_ver_old( const ver_t *ver, long mjr, long mnr, long pat )
{
	if( ver == NULL )
		return FALSE;

	if( ver->mjr > mjr )
		return FALSE;
	if( ver->mjr < mjr )
		return TRUE;

	if( ver->mnr > mnr )
		return FALSE;
	if( ver->mnr < mnr )
		return TRUE;

	if( ver->pat > pat )
		return FALSE;
	if( ver->pat < pat )
		return TRUE;

	return FALSE;
}

/***************************************************************
* バージョンが指定値より新しいか?
* const ver_t *ver : バージョン
* long mjr : メジャー・バージョン
* long mnr : マイナー・バージョン
* long pat : パッチ・レベル
* return : 指定値より新しいか?
***************************************************************/

bool_t	chk_ver_new( const ver_t *ver, long mjr, long mnr, long pat )
{
	if( ver == NULL )
		return FALSE;

	if( ver->mjr > mjr )
		return TRUE;
	if( ver->mjr < mjr )
		return FALSE;

	if( ver->mnr > mnr )
		return TRUE;
	if( ver->mnr < mnr )
		return FALSE;

	if( ver->pat > pat )
		return TRUE;
	if( ver->pat < pat )
		return FALSE;

	return FALSE;
}

/***************************************************************
* バージョンが指定値と同じかより新しいか?
* const ver_t *ver : バージョン
* long mjr : メジャー・バージョン
* long mnr : マイナー・バージョン
* long pat : パッチ・レベル
* return : 指定値と同じかより新しいか?
***************************************************************/

bool_t	chk_ver_new_match( const ver_t *ver, long mjr, long mnr, long pat )
{
	if( ver == NULL )
		return FALSE;

	if( ver->mjr > mjr )
		return TRUE;
	if( ver->mjr < mjr )
		return FALSE;

	if( ver->mnr > mnr )
		return TRUE;
	if( ver->mnr < mnr )
		return FALSE;

	if( ver->pat > pat )
		return TRUE;
	if( ver->pat < pat )
		return FALSE;

	return TRUE;
}

/***************************************************************
* バージョンが指定値と一致するか?
* const ver_t *ver : バージョン
* long mjr : メジャー・バージョン
* long mnr : マイナー・バージョン
* long pat : パッチ・レベル
* return : 一致するか?
***************************************************************/

bool_t	chk_ver_match( const ver_t *ver, long mjr, long mnr, long pat )
{
	if( ver == NULL )
		return FALSE;

	if( ver->mjr != mjr )
		return FALSE;
	if( ver->mnr != mnr )
		return FALSE;
	if( ver->pat != pat )
		return FALSE;

	return TRUE;
}

/***************************************************************
* 文字列のメモリー上の文字数を返す
* const char *s : 文字列
* return : 文字数
***************************************************************/

long	str_len_std( const char *s )
{
	return( (long)strlen( s ) );
}

/***************************************************************
* 文字列を指定文字数コピーする。ヌル文字も必ずコピーする
* char *dst : 連結先文字列
* const char *src : 参照元文字列
* int len : 文字数
* return : 連結後文字列
***************************************************************/

char	*str_nz_cpy( char *dst, const char *src, int len )
{
	strncpy( dst, src, len );
	dst[len] = '\0';

	return dst;
}

/***************************************************************
* 文字列を指定文字数を越えない様に連結する
* char *dst : 連結先文字列
* const char *src : 参照元文字列
* int len : 文字数
* return : 連結後文字列
***************************************************************/

char	*str_max_n_cat( char *dst, const char *src, int len )
{
	return strncat( dst, src, len - strlen( dst ) );
}

/***************************************************************
* 文字列の末尾の空白文字を取り除く
* char *str : 文字列
* const char *spc_char : 空白文字の配列
***************************************************************/

void	str_trim_tail( char *str, const char *spc_char )
{
	long	idx, next_idx;
	long	i;

	idx = 0;
	for( i = 0; i < LOOP_MAX_10000; i++ ){
		next_idx = idx + strcspn( &(str[idx]), spc_char );
		if( str[next_idx] == '\0' ){
			if( i == 0 ){
				return;
			} else {
				break;
			}
		}

		idx = next_idx;

		next_idx = idx + strspn( &(str[idx]), spc_char );
		if( str[next_idx] == '\0' )
			break;

		idx = next_idx;
	}

	str[idx] = '\0';
}

/***************************************************************
* 文字列のフォーマット
* char *s : 出力先文字列
* long n : 出力先文字列の長さ
* const char *fmt : フォーマット文字列
* ... : フォーマットの引数
***************************************************************/

void	sn_printf( char *s, long n, const char *fmt, ... )
{
	va_list	argptr;

	if( s == NULL )
		return;
	if( fmt == NULL )
		return;

	va_start( argptr, fmt );
#ifdef	D_GTK
	g_vsnprintf( s, n, fmt, argptr );
	s[n] = '\0';
#else
	vsprintf( s, fmt, argptr );
#endif
	va_end( argptr );
}

/***************************************************************
* 文字列のフォーマット
* char *s : 出力先文字列
* long n : 出力先文字列の長さ
* const char *fmt : フォーマット文字列
* va_list argptr : フォーマットの引数
***************************************************************/

void	vsn_printf( char *s, long n, const char *fmt, va_list argptr )
{
	if( s == NULL )
		return;
	if( fmt == NULL )
		return;

#ifdef	D_GTK
	g_vsnprintf( s, n, fmt, argptr );
	s[n] = '\0';
#else
	vsprintf( s, fmt, argptr );
#endif
}

/***************************************************************
* フラグの指定したビットが全て立っているか調べる
* unsigned long var : フラグ
* unsigned long flg : 調べるビット
* return : 全て立っているか?
***************************************************************/

bool_t	chk_flg( unsigned long var, unsigned long flg )
{
	return( (var & flg) == flg );
}

/***************************************************************
* フラグの指定したビットが 1 つでも立っているか調べる
* unsigned long var : フラグ
* unsigned long flg : 調べるビット
* return : 1 つでも立っているか?
***************************************************************/

bool_t	chk_flg_or( unsigned long var, unsigned long flg )
{
	return( (var & flg) != 0 );
}

/***************************************************************
* エラー・チェック付きのメモリー割り当て
* long size : 割り当てるメモリーのサイズ
* bool_t flg_exit : エラーで終了するか?
* return : 割り当てたメモリー
***************************************************************/

void	*alloc_mem( long size, bool_t flg_exit )
{
	void	*p;

	p = malloc( size );
	if( p == NULL ){
		print_msg( FLG_MSG_ERR, MSG_ERR_ALLOC_MEM, size );

		if( flg_exit ){
			exit_game( EXIT_FAILURE );
		}
	}

	return p;
}

/***************************************************************
* メモリーを解放
* void *p : 解放するメモリー
***************************************************************/

void	free_mem( void *p )
{
	if( p != NULL )
		free( p );
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_misc_c( void )
{
	check_memory( check_memory_misc_c_randm_seed,
			"misc.c: randm_seed" );
	check_memory( check_memory_misc_c_randm_seed_gui,
			"misc.c: randm_seed_gui" );
}
