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
* $Id: msg.c,v 1.54 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ��å�����
***************************************************************/

#define	MSG_C
#include	"inc.h"

/***************************************************************/

#define	FLG_DFLT_ENGLISH	0

/***************************************************************
* ʸ����
***************************************************************/

#define	STR_S	"%s"
#define	STR_ENV_LANG	"LANG"
#define	STR_SUPPORT_LANG	"Supporting languages are:"
#define	STR_SUPPORT_LANG_LIST	"\t`%s'\n"
#define	STR_ERR_LANG	"Don't support language: LANG=%s"
#define	STR_ERR_REDEFINED_MSG	"Redefined message data: LANG=%s %ld `%s'"
#define	STR_ERR_NOT_DEFINED_MSG	"Don't defined message data: LANG=%s %ld"

/***************************************************************
* ����̾
***************************************************************/

#ifdef	D_DOS
# define	STR_LANG_NAME_ENGLISH	"English"
# define	STR_LANG_NAME_JAPANESE_EUC	"Japanese"
# define	STR_LANG_NAME_JAPANESE_UTF_8	"Japanese"
# define	STR_LANG_NAME_JAPANESE_SJIS	"Japanese"
#else	/* D_DOS */
# define	STR_LANG_NAME_ENGLISH	"English"
# define	STR_LANG_NAME_JAPANESE_EUC	"Japanese (EUC)"
# define	STR_LANG_NAME_JAPANESE_UTF_8	"Japanese (UTF-8)"
# define	STR_LANG_NAME_JAPANESE_SJIS	"Japanese (Shift-JIS)"
#endif	/* D_DOS */

/***************************************************************
* ����
***************************************************************/

/* ����ơ��֥�κ���� */
#define	LANG_TAB_MAX_N	64

/* �ǥե���Ȥθ��� */
#if	FLG_DFLT_ENGLISH
# define	STR_DFLT_LANG	"C"
#elif	defined( D_DOS )
# define	STR_DFLT_LANG	"ja_JP.SJIS"
#elif	defined( D_GTK )
# define	STR_DFLT_LANG	"ja_JP.utf8"
#else
# define	STR_DFLT_LANG	"ja_JP.utf8"
/*# define	STR_DFLT_LANG	"ja_JP.eucJP"*/
#endif

/* ����μ��� */
static lang_kind_t	g_lang_kind, g_lang_kind_next;
check_memory_def( check_memory_msg_c_g_lang_kind )
/* �����������������ͥ�褹�� */
static bool_t	g_flg_lang_ls_priority;
check_memory_def( check_memory_msg_c_g_flg_lang_ls_priority )

/* ����Υǡ����� */
typedef struct {
	char	*id_n;
	char	*name;
	lang_kind_t	kind;
} lang_t;

/* ����Υǡ��� */
static lang_t	lang_tab[LANG_TAB_MAX_N] = {
	{
		"C",
		STR_LANG_NAME_ENGLISH,
		LANG_KIND_ENGLISH,
	},
	{
		"ja_JP.eucJP",
		STR_LANG_NAME_JAPANESE_EUC,
		LANG_KIND_JAPANESE_EUC,
	},
	{
		"ja_JP.ujis",
		STR_LANG_NAME_JAPANESE_EUC,
		LANG_KIND_JAPANESE_EUC,
	},
	{
		"ja_JP.UTF-8",
		STR_LANG_NAME_JAPANESE_UTF_8,
		LANG_KIND_JAPANESE_UTF_8,
	},
	{
		"ja_JP.utf8",
		STR_LANG_NAME_JAPANESE_UTF_8,
		LANG_KIND_JAPANESE_UTF_8,
	},
	{
		"ja_JP.SJIS",
		STR_LANG_NAME_JAPANESE_SJIS,
		LANG_KIND_JAPANESE_SJIS,
	},
	{
		NULL,
		NULL,
		LANG_KIND_MAX_N,
	},
};
check_memory_def( check_memory_msg_c_lang_tab )

/***************************************************************
* ��å�����
***************************************************************/

/* ��å��������ơ��֥�Υǡ����� */

typedef struct {
	n_msg_t	n;
	char	*s;
} msg_t;

/* ��å��������ơ��֥� */

static msg_t	all_lang_msg[LANG_KIND_MAX_N][N_MSG_MAX_N];
check_memory_def( check_memory_msg_c_all_lang_msg )

/* �֥�å� 0 */

#define	SEL_MSG_BLOCK_0
static msg_t	all_lang_msg_0[LANG_KIND_MAX_N]
		[N_MSG__MSG_BLOCK_0_END_ + 1] = {
	{
#include	"msg-eng.h"
	},
	{
#ifdef	D_DOS
# include	"msg-jpn-sjis.h"
#else	/* D_DOS */
# include	"msg-jpn.h"
#endif	/* D_DOS */
	},
	{
#ifdef	D_DOS
# include	"msg-jpn-sjis.h"
#else	/* D_DOS */
# include	"msg-jpn-utf8.h"
#endif	/* D_DOS */
	},
	{
#include	"msg-jpn-sjis.h"
	},
};
#undef	SEL_MSG_BLOCK_0
check_memory_def( check_memory_msg_c_all_lang_msg_0 )

/* �֥�å� 1 */

#define	SEL_MSG_BLOCK_1
static msg_t	all_lang_msg_1[LANG_KIND_MAX_N]
		[N_MSG__MSG_BLOCK_1_END_ - N_MSG__MSG_BLOCK_0_END_ + 1] = {
	{
#include	"msg-eng.h"
	},
	{
#ifdef	D_DOS
# include	"msg-jpn-sjis.h"
#else	/* D_DOS */
# include	"msg-jpn.h"
#endif	/* D_DOS */
	},
	{
#ifdef	D_DOS
# include	"msg-jpn-sjis.h"
#else	/* D_DOS */
# include	"msg-jpn-utf8.h"
#endif	/* D_DOS */
	},
	{
#include	"msg-jpn-sjis.h"
	},
};
#undef	SEL_MSG_BLOCK_1
check_memory_def( check_memory_msg_c_all_lang_msg_1 )

/* ��å����������������Ƥ��ʤ��������å��ѤΥǡ��� */
static bool_t	flg_msg_def[N_MSG_MAX_N];
check_memory_def( check_memory_msg_c_flg_msg_def )

/***************************************************************
* ��å������ν����
***************************************************************/

void	init_msg( void )
{
	bool_t	flg_exit;
	long	block_bgn_n, block_end_n;
	char	*lang;
	long	lang_tab_kind;
	long	l, i, k, m;

	flg_exit = FALSE;

	block_bgn_n = 0;
	block_end_n = N_MSG__MSG_BLOCK_0_END_;
	for( l = 0; l < LANG_KIND_MAX_N; l++ ){
		for( i = block_bgn_n; i <= block_end_n; i++ ){
			long	n;

			n = i - block_bgn_n;
			all_lang_msg[l][i] = all_lang_msg_0[l][n];
		}
	}

	block_bgn_n = N_MSG__MSG_BLOCK_0_END_ + 1;
	block_end_n = N_MSG__MSG_BLOCK_1_END_;
	for( l = 0; l < LANG_KIND_MAX_N; l++ ){
		for( i = block_bgn_n; i <= block_end_n; i++ ){
			long	n;

			n = i - block_bgn_n;
			all_lang_msg[l][i] = all_lang_msg_1[l][n];
		}
	}

	/* �Ķ��ѿ��θ�����ͤ����� */

	if( g_language == NULL ){
		lang = NULL;
#ifdef	HAVE_GETENV
		lang = getenv( STR_ENV_LANG );
#endif
		if( lang == NULL )
			lang = STR_DFLT_LANG;
#ifdef	D_GTK
		if( strcmp( lang, "ja_JP.eucJP" ) == 0 )
			lang = "ja_JP.utf8";
#endif
	} else {
		lang = g_language;
	}
#ifdef	HAVE_SETENV
	setenv( STR_ENV_LANG, lang, 1 );
#endif

#ifdef	HAVE_LOCALE_H
	setlocale( LC_ALL, "" );
#endif

	/* �Ķ��ѿ��ǻ��ꤵ�줿����μ����õ�� */

	g_lang_kind = LANG_KIND_MAX_N;
	lang_tab_kind = 0;
	for( k = 0; k < LANG_TAB_MAX_N; k++ ){
		if( lang_tab[k].id_n == NULL )
			break;

		if( strcmp( lang, lang_tab[k].id_n ) == 0 ){
			g_lang_kind = lang_tab[k].kind;
			lang_tab_kind = k;
			break;
		}
	}
	g_lang_kind_next = g_lang_kind;

	/* ���ꤵ�줿���줬���Ĥ���ʤ��ä��饨�顼 */

	if( g_lang_kind >= LANG_KIND_MAX_N ){
		print_err( STR_ERR_LANG, lang );
		print_err( STR_S, STR_SUPPORT_LANG );
		for( k = 0; k < LANG_TAB_MAX_N; k++ ){
			if( lang_tab[k].id_n == NULL )
				break;

			fprintf( stderr, STR_SUPPORT_LANG_LIST,
					lang_tab[k].id_n );
		}
		fprintf( stderr, "\n" );
		/* exit_game( EXIT_FAILURE ); */

		g_lang_kind = LANG_KIND_ENGLISH;
		g_lang_kind_next = g_lang_kind;
	}

	for( m = 0; m < N_MSG_MAX_N; m++ )
		flg_msg_def[m] = FALSE;

	/* ��å����������������Ƥ��ʤ��������å� */

	for( i = 0; i < N_MSG_MAX_N; i++ ){
		if( all_lang_msg[g_lang_kind][i].s == NULL )
			break;

		m = all_lang_msg[g_lang_kind][i].n;
		if( flg_msg_def[m] ){
			char	*s;

			/* ��å����������������Ƥ��� */
			s = all_lang_msg[g_lang_kind][m].s;
			print_err( STR_ERR_REDEFINED_MSG,
					lang_tab[lang_tab_kind].id_n,
					m, s );
			flg_exit = TRUE;
		}

		/* ��å������򥳥ԡ� */
		ary_msg[m] = all_lang_msg[g_lang_kind][i].s;
		flg_msg_def[m] = TRUE;
	}

	/* ��å��������������Ƥ��뤫�����å� */

	for( m = 0; m < N_MSG_MAX_N; m++ ){
		if( !flg_msg_def[m] ){
			/* ��å��������������Ƥ��ʤ� */
			print_err( STR_ERR_NOT_DEFINED_MSG,
					lang_tab[lang_tab_kind].id_n,
					m );
			flg_exit = TRUE;
		}
	}

	if( flg_exit )
		exit_game( EXIT_FAILURE );
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_msg( void )
{
}

/***************************************************************
* ��å������θ���������
* lang_kind_t kind : ����μ���
***************************************************************/

void	reset_msg( lang_kind_t kind )
{
	n_msg_t	m;
	long	i;

	if( kind < 0 )
		return;
	if( kind >= LANG_KIND_MAX_N )
		return;

	g_lang_kind = kind;
	g_lang_kind_next = kind;

	for( i = 0; i < N_MSG_MAX_N; i++ ){
		if( all_lang_msg[g_lang_kind][i].s == NULL )
			break;

		m = all_lang_msg[g_lang_kind][i].n;
		ary_msg[m] = all_lang_msg[g_lang_kind][i].s;
	}
}

/***************************************************************
* ����μ�����֤�
* return : ����μ���
***************************************************************/

lang_kind_t	get_lang_kind( void )
{
	return g_lang_kind;
}

/***************************************************************
* �Ƽ¹Ը��ͭ���ˤʤ����μ�����֤�
* return : ����μ���
***************************************************************/

lang_kind_t	get_lang_kind_next( void )
{
	return g_lang_kind_next;
}

/***************************************************************
* �Ƽ¹Ը��ͭ���ˤʤ����μ��������
* lang_kind_t kind : ����μ���
* return : ����μ���
***************************************************************/

lang_kind_t	set_lang_kind_next( lang_kind_t kind )
{
	g_lang_kind_next = kind;

	return g_lang_kind_next;
}

/***************************************************************
* �Ƽ¹Ը��ͭ���ˤʤ����� ID ���֤�
* return : ����� ID
***************************************************************/

char	*get_lang_id_next( void )
{
	long	k;

	for( k = 0; k < LANG_TAB_MAX_N; k++ ){
		if( lang_tab[k].id_n == NULL )
			break;

		if( lang_tab[k].kind == g_lang_kind_next ){
			return( lang_tab[k].id_n );
		}
	}

	return( lang_tab[0].id_n );
}

/***************************************************************
* �����������������ͥ�褹�뤫���֤�
* return : ͥ�褹�뤫?
***************************************************************/

bool_t	get_flg_lang_ls_priority( void )
{
	return g_flg_lang_ls_priority;
}

/***************************************************************
* �����������������ͥ�褹�뤫����
* bool_t flg : ͥ�褹�뤫?
* return : ͥ�褹�뤫?
***************************************************************/

bool_t	set_flg_lang_ls_priority( bool_t flg )
{
	g_flg_lang_ls_priority = flg;

	return g_flg_lang_ls_priority;
}

/***************************************************************
* ����μ��फ��̾�����֤�
* lang_kind_t kind : ����μ���
* return : �����̾��
***************************************************************/

char	*get_lang_kind_name( lang_kind_t kind )
{
	long	i;

	if( kind < 0 )
		return MSG_NULL;
	if( kind >= LANG_KIND_MAX_N )
		return MSG_NULL;

	for( i = 0; i < LANG_TAB_MAX_N; i++ ){
		if( lang_tab[i].id_n == NULL )
			break;

		if( lang_tab[i].kind == kind ){
			return( lang_tab[i].name );
		}
	}

	return MSG_NULL;
}

/***************************************************************
* ����� ID ���������֤�
* char *id : ����� ID
* return : ����μ���
***************************************************************/

lang_kind_t	trans_lang_id_to_kind( char *id )
{
	long	k;

	for( k = 0; k < LANG_TAB_MAX_N; k++ ){
		if( lang_tab[k].id_n == NULL )
			break;

		if( strcmp( id, lang_tab[k].id_n ) == 0 ){
			return( lang_tab[k].kind );
		}
	}

	return LANG_KIND_JAPANESE_EUC;
}

/***************************************************************
* ɽ�����ʸ����ʬ����ʸ������ڤ�Ф�
* const char *s : ʸ����
* long draw_len : ʸ����
* return : �ڤ�Ф���ʸ����
***************************************************************/

const char	*cut_utf_str( const char *s, long draw_len )
{
	const long	buf_len = 1024;
	static char	buf[1024 * 8 + 1];
	const char	*head, *tail;

	buf[0] = '\0';

	if( s == NULL )
		return buf;
	if( draw_len <= 0 )
		return buf;

	draw_len = min_l( draw_len, buf_len );
	head = s;
	tail = get_words_line( head, draw_len + 2 );
	if( tail == NULL )
		return buf;

	str_nz_cpy( buf, head, tail - head );
	return buf;
}

/***************************************************************
* ʸ�����ɽ�����ʸ�������֤�
* const char *s : ʸ����
* return : ʸ����
***************************************************************/

long	str_len_draw( const char *s )
{
#ifdef	D_DOS

	return( (long)strlen( s ) );

#else	/* D_DOS */

	switch( get_lang_kind() ){
	case LANG_KIND_ENGLISH:
		return str_len_draw_english( s );
	case LANG_KIND_JAPANESE_EUC:
		return str_len_draw_japanese_euc( s );
	case LANG_KIND_JAPANESE_UTF_8:
		return str_len_draw_japanese_utf_8( s );
	case LANG_KIND_JAPANESE_SJIS:
		return str_len_draw_japanese_sjis( s );
	case LANG_KIND_MAX_N:
		break;
	}

	return( (long)strlen( s ) );

#endif	/* D_DOS */
}

/***************************************************************
* �Ѹ��ʸ�����ɽ�����ʸ�������֤�
* const char *s : ʸ����
* return : ʸ����
***************************************************************/

long	str_len_draw_english( const char *s )
{
	return( (long)strlen( s ) );
}

/***************************************************************
* ���ܸ�(EUC)��ʸ�����ɽ�����ʸ�������֤�
* const char *s : ʸ����
* return : ʸ����
***************************************************************/

long	str_len_draw_japanese_euc( const char *s )
{
	long	len;

	len = 0;

	while( *s != '\0' ){
		unsigned long	c;

		c = (unsigned char)*s;
		if( c >= 0xa0 ){
			len += 2;
			s += 2;
		} else if( c == 0x8e ){
			len += 1;
			s += 2;
		} else if( c == 0x8f ){
			len += 2;
			s += 3;
		} else {
			len += 1;
			s += 1;
		}
	}

	return len;
}

/***************************************************************
* ���ܸ�(UTF-8)��ʸ�����ɽ�����ʸ�������֤�
* const char *s : ʸ����
* return : ʸ����
***************************************************************/

long	str_len_draw_japanese_utf_8( const char *s )
{
	long	len;
	unsigned long	c;

	len = 0;
	while( *s != '\0' ){
		c = (unsigned char)*s;

		if( (c & 0x80) == 0x00 ){
			len++;
			s++;
			continue;
		}

		len += 2;
		s++;
		while( *s != '\0' ){
			c = (unsigned char)*s;

			if( (c & 0xc0) != 0x80 )
				break;

			s++;
		}
	}

	return len;
}

/***************************************************************
* ���ܸ�(Shift-JIS)��ʸ�����ɽ�����ʸ�������֤�
* const char *s : ʸ����
* return : ʸ����
***************************************************************/

long	str_len_draw_japanese_sjis( const char *s )
{
	long	len;

	for( len = 0; *s != '\0'; len++, s++ )
		;

	return len;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_msg_c( void )
{
	check_memory( check_memory_msg_c_g_lang_kind,
			"msg.c: g_lang_kind" );
	check_memory( check_memory_msg_c_g_flg_lang_ls_priority,
			"msg.c: g_flg_lang_ls_priority" );
	check_memory( check_memory_msg_c_lang_tab,
			"msg.c: lang_tab" );
	check_memory( check_memory_msg_c_all_lang_msg,
			"msg.c: all_lang_msg" );
	check_memory( check_memory_msg_c_all_lang_msg_0,
			"msg.c: all_lang_msg_0" );
	check_memory( check_memory_msg_c_all_lang_msg_1,
			"msg.c: all_lang_msg_1" );
	check_memory( check_memory_msg_c_flg_msg_def,
			"msg.c: flg_msg_def" );
}
