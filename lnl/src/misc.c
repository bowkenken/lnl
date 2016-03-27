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
* $Id: misc.c,v 1.51 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ����¾
***************************************************************/

#define	MISC_C
#include	"inc.h"

/***************************************************************/

/* ����μ� */

static long	randm_seed = 1;
check_memory_def( check_memory_misc_c_randm_seed )
static long	randm_seed_gui = 1;
check_memory_def( check_memory_misc_c_randm_seed_gui )

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_misc( void )
{
}

/***************************************************************
* ��ߤ�����򥳥�ޡ��ե����ޥå�ʸ������Ѵ�
* long n : ����
* return : ����ޡ��ե����ޥå�ʸ����
***************************************************************/

char	*fmt_gold( gold_t gold )
{
	return( fmt_num( (long)(gold) ) );
}

/***************************************************************
* ���ͤ򥳥�ޡ��ե����ޥå�ʸ������Ѵ�
* long n : ����
* return : ����ޡ��ե����ޥå�ʸ����
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
* ����ޡ��ե����ޥå�ʸ�������ͤ��Ѵ�
* long n : ����ޡ��ե����ޥå�ʸ����
* return : ����
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
* sprintf �Υѥǥ��󥰤˻��ꤹ��ե����������Ĵ������
* const char *s : �ե����ޥåȤ˻��ꤹ�����
* long min_len : �Ǿ��ե��������
* return : Ĵ�����줿�Ǿ��ե��������
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
* long ���ͤ� +- �������֤�
* long n : ����
* return : ���
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
* 2 �Ĥ� long ���ͤξ����������֤�
* long n1 : ���� 1
* long n2 : ���� 2
* return : ���������ο���
***************************************************************/

long	min_l( long n1, long n2 )
{
	if( n1 < n2 )
		return n1;
	else
		return n2;
}

/***************************************************************
* 2 �Ĥ� long ���ͤ��礭�������֤�
* long n1 : ���� 1
* long n2 : ���� 2
* return : �礭�����ο���
***************************************************************/

long	max_l( long n1, long n2 )
{
	if( n1 > n2 )
		return n1;
	else
		return n2;
}

/***************************************************************
* ����μ������
* long n : ��
***************************************************************/

void	srandm( long n )
{
	randm_seed = n;
	randm_seed_gui = n;
}

/***************************************************************
* ����μ���֤�
* long n : ��
***************************************************************/

long	get_randm_seed( void )
{
	return randm_seed;
}

/***************************************************************
* 0 ��������̤����������֤�
* long n : ������
* return : ���
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
* 0 ��������̤����������֤�
* long n : ������
* return : ���
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
* ����������Ψ(%)�ʲ��ˤʤ뤫?
* long n : �����Ψ(%)
* return : �����Ψ(%)�ʲ���?
***************************************************************/

bool_t	rate_randm( rate_t rate )
{
	return( randm( _100_PERCENT ) < rate );
}

/***************************************************************
* ���������ο���ʬ�� 1 �ˤʤ뤫?
* long n : ����ο���
* return : ����ο���ʬ�� 1 ��?
***************************************************************/

bool_t	per_randm( long per )
{
	return( randm( per ) == 0 );
}

/***************************************************************
* �����Ψ�� 100% ��Ķ����ʬ�ο���������֤�
* rate_t rate : �����Ψ
* return : 100% ��Ķ����ʬ�ο�
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
* 0 ��������̤����������֤� (��ץ쥤�˱ƶ����ʤ� GUI ��)
* long n : ������
* return : ���
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
* ���ͤ�Ψ(%)��������
* rate_t rate : Ψ(%)
* long n : ����
* return : �������Ψ(%)
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
* �С�����󤬻����ͤ��Ť���?
* const ver_t *ver : �С������
* long mjr : �᥸�㡼���С������
* long mnr : �ޥ��ʡ����С������
* long pat : �ѥå�����٥�
* return : �����ͤ��Ť���?
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
* �С�����󤬻����ͤ�꿷������?
* const ver_t *ver : �С������
* long mjr : �᥸�㡼���С������
* long mnr : �ޥ��ʡ����С������
* long pat : �ѥå�����٥�
* return : �����ͤ�꿷������?
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
* �С�����󤬻����ͤ�Ʊ������꿷������?
* const ver_t *ver : �С������
* long mjr : �᥸�㡼���С������
* long mnr : �ޥ��ʡ����С������
* long pat : �ѥå�����٥�
* return : �����ͤ�Ʊ������꿷������?
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
* �С�����󤬻����ͤȰ��פ��뤫?
* const ver_t *ver : �С������
* long mjr : �᥸�㡼���С������
* long mnr : �ޥ��ʡ����С������
* long pat : �ѥå�����٥�
* return : ���פ��뤫?
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
* ʸ����Υ��꡼���ʸ�������֤�
* const char *s : ʸ����
* return : ʸ����
***************************************************************/

long	str_len_std( const char *s )
{
	return( (long)strlen( s ) );
}

/***************************************************************
* ʸ��������ʸ�������ԡ����롣�̥�ʸ����ɬ�����ԡ�����
* char *dst : Ϣ����ʸ����
* const char *src : ���ȸ�ʸ����
* int len : ʸ����
* return : Ϣ���ʸ����
***************************************************************/

char	*str_nz_cpy( char *dst, const char *src, int len )
{
	strncpy( dst, src, len );
	dst[len] = '\0';

	return dst;
}

/***************************************************************
* ʸ��������ʸ������ۤ��ʤ��ͤ�Ϣ�뤹��
* char *dst : Ϣ����ʸ����
* const char *src : ���ȸ�ʸ����
* int len : ʸ����
* return : Ϣ���ʸ����
***************************************************************/

char	*str_max_n_cat( char *dst, const char *src, int len )
{
	return strncat( dst, src, len - strlen( dst ) );
}

/***************************************************************
* ʸ����������ζ���ʸ���������
* char *str : ʸ����
* const char *spc_char : ����ʸ��������
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
* ʸ����Υե����ޥå�
* char *s : ������ʸ����
* long n : ������ʸ�����Ĺ��
* const char *fmt : �ե����ޥå�ʸ����
* ... : �ե����ޥåȤΰ���
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
* ʸ����Υե����ޥå�
* char *s : ������ʸ����
* long n : ������ʸ�����Ĺ��
* const char *fmt : �ե����ޥå�ʸ����
* va_list argptr : �ե����ޥåȤΰ���
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
* �ե饰�λ��ꤷ���ӥåȤ�����Ω�äƤ��뤫Ĵ�٤�
* unsigned long var : �ե饰
* unsigned long flg : Ĵ�٤�ӥå�
* return : ����Ω�äƤ��뤫?
***************************************************************/

bool_t	chk_flg( unsigned long var, unsigned long flg )
{
	return( (var & flg) == flg );
}

/***************************************************************
* �ե饰�λ��ꤷ���ӥåȤ� 1 �ĤǤ�Ω�äƤ��뤫Ĵ�٤�
* unsigned long var : �ե饰
* unsigned long flg : Ĵ�٤�ӥå�
* return : 1 �ĤǤ�Ω�äƤ��뤫?
***************************************************************/

bool_t	chk_flg_or( unsigned long var, unsigned long flg )
{
	return( (var & flg) != 0 );
}

/***************************************************************
* ���顼�������å��դ��Υ��꡼�������
* long size : ������Ƥ���꡼�Υ�����
* bool_t flg_exit : ���顼�ǽ�λ���뤫?
* return : ������Ƥ����꡼
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
* ���꡼�����
* void *p : ����������꡼
***************************************************************/

void	free_mem( void *p )
{
	if( p != NULL )
		free( p );
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_misc_c( void )
{
	check_memory( check_memory_misc_c_randm_seed,
			"misc.c: randm_seed" );
	check_memory( check_memory_misc_c_randm_seed_gui,
			"misc.c: randm_seed_gui" );
}
