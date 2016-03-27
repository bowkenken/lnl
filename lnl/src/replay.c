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
* $Id: replay.c,v 1.25 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ��ץ쥤
***************************************************************/

#define	REPLAY_C
#include	"inc.h"

/***************************************************************/

static long	g_replay_save_slot;
check_memory_def( check_memory_replay_c_g_replay_save_slot )

static bool_t	g_flg_reg_replay[REPLAY_SLOT_MAX_N];
check_memory_def( check_memory_replay_c_g_flg_reg_replay )
static long	g_replay_randm_seed[REPLAY_SLOT_MAX_N];
check_memory_def( check_memory_replay_c_g_replay_randm_seed )
static replay_t	*g_replay_head[REPLAY_SLOT_MAX_N];
check_memory_def( check_memory_replay_c_g_replay_head )
static replay_t	*g_replay_cur[REPLAY_SLOT_MAX_N];
check_memory_def( check_memory_replay_c_g_replay_cur )
static replay_t	*g_replay_cur_draw;
check_memory_def( check_memory_replay_c_g_replay_cur_draw )

static bool_t	g_flg_play_replay;
static long	g_play_replay_turn;
static long	g_play_replay_count;
static long	g_play_replay_char;
check_memory_def( check_memory_replay_c_g_flg_play_replay )

static long	g_play_replay_idx;
static long	g_play_replay_idx_draw;
check_memory_def( check_memory_replay_c_g_play_replay_idx )

/***************************************************************
* ��ץ쥤������
***************************************************************/

void	init_replay( void )
{
	long	sn;

	g_replay_save_slot = SAVE_N_AUTO;

	for( sn = REPLAY_SLOT_NULL; sn < REPLAY_SLOT_MAX_N; sn++ ){
		g_flg_reg_replay[sn] = FALSE;
		g_replay_head[sn] = NULL;
		g_replay_cur[sn] = NULL;
	}
	g_replay_cur_draw = NULL;

	g_flg_play_replay = FALSE;
	g_play_replay_turn = -1;
	g_play_replay_count = 0;
	g_play_replay_char = '\0';

	g_play_replay_idx = 0;
	g_play_replay_idx_draw = 0;
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_replay( void )
{
}

/***************************************************************
* ��ץ쥤��ꥻ�å�
* long n : �ǡ���������å��ֹ�
***************************************************************/

void	reset_replay( long n )
{
	replay_slot_t	sn = cv_slot_n( n );

	reset_replay_slot( sn );
}

/***************************************************************
* ��ץ쥤��ꥻ�å�(����åȻ��ꤢ��)
* replay_slot_t sn : ��ץ쥤������å��ֹ�
***************************************************************/

void	reset_replay_slot( replay_slot_t sn )
{
	replay_t	*p, *next;

	if( g_replay_head[sn] == NULL )
		return;

	for( p = g_replay_head[sn]; p != NULL; p = next ){
		next = p->next;
		free_replay( p );
	}

	g_flg_reg_replay[sn] = FALSE;
	g_replay_head[sn] = NULL;
	g_replay_cur[sn] = NULL;
	g_replay_cur_draw = NULL;
}

/***************************************************************
* ��ץ쥤�ε�Ͽ���֤��֤�
* long n : �ǡ���������å��ֹ�
***************************************************************/

bool_t	chk_reg_replay( long n )
{
	replay_slot_t	sn = cv_slot_n( n );

	return g_flg_reg_replay[sn];
}

/***************************************************************
* ��ץ쥤�ε�Ͽ�򳫻�
* long n : �ǡ���������å��ֹ�
***************************************************************/

void	bgn_reg_replay( long n )
{
	replay_slot_t	sn = cv_slot_n( n );

	if( (n != SAVE_N_AUTO) && (n != SAVE_N_BUG_REPO) )
		g_replay_save_slot = n;

	if( g_flg_reg_replay[sn] )
		reset_replay_slot( sn );

	g_replay_randm_seed[sn] = get_randm_seed();

	g_flg_reg_replay[sn] = TRUE;
	if( (n != SAVE_N_AUTO) && (n != SAVE_N_BUG_REPO) )
		print_msg( FLG_NULL, MSG_BGN_REG_REPLAY );
}

/***************************************************************
* ��ץ쥤�Υե������ɤ߹��ߤ򳫻�
***************************************************************/

void	bgn_reg_replay_play( void )
{
	replay_slot_t	sn = REPLAY_SLOT_PLAY;

	if( g_flg_reg_replay[sn] )
		reset_replay_slot( sn );

	g_flg_reg_replay[sn] = TRUE;
}

/***************************************************************
* ��ץ쥤�ε�Ͽ��λ
* long n : �ǡ���������å��ֹ�
***************************************************************/

void	end_reg_replay( long n )
{
	replay_slot_t	sn = cv_slot_n( n );

	if( !g_flg_reg_replay[sn] )
		return;

	g_flg_reg_replay[sn] = FALSE;
	print_msg( FLG_NULL, MSG_END_REG_REPLAY );
}

/***************************************************************
* ��ץ쥤��ʸ�����Ͽ
* replay_kind_t kind : ��ץ쥤�μ���
* char *str : ��������ʸ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	set_replay_str(
	replay_kind_t kind, char *str
)
{
	bool_t	flg_success;
	replay_slot_t	sn;

	flg_success = TRUE;

	sn = REPLAY_SLOT_AUTO;
	if( !set_replay_str_slot( kind, sn, str ) )
		flg_success = FALSE;

	sn = REPLAY_SLOT_BUG_REPO;
	if( !set_replay_str_slot( kind, sn, str ) )
		flg_success = FALSE;

	sn = cv_slot_n( g_replay_save_slot );
	if( !set_replay_str_slot( kind, sn, str ) )
		flg_success = FALSE;

	return flg_success;
}

/***************************************************************
* ��ץ쥤��ʸ�����Ͽ(����åȻ��ꤢ��)
* replay_kind_t kind : ��ץ쥤�μ���
* replay_slot_t sn : ��ץ쥤������å��ֹ�
* char *str : ��������ʸ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	set_replay_str_slot(
	replay_kind_t kind, replay_slot_t sn, char *str
)
{
	long	i;

	if( !g_flg_reg_replay[sn] )
		return TRUE;
	if( str == NULL )
		return FALSE;

	for( i = 0; str[i] != '\0'; i++ ){
		if( !set_replay_char_slot( kind, sn, str[i] ) )
			return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ��ץ쥤�� 1 ʸ����Ͽ
* replay_kind_t kind : ��ץ쥤�μ���
* long c : ��������ʸ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	set_replay_char(
	replay_kind_t kind, long c
)
{
	bool_t	flg_success;
	replay_slot_t	sn;

	flg_success = TRUE;

	sn = REPLAY_SLOT_AUTO;
	if( !set_replay_char_slot( kind, sn, c ) )
		flg_success = FALSE;

	sn = REPLAY_SLOT_BUG_REPO;
	if( !set_replay_char_slot( kind, sn, c ) )
		flg_success = FALSE;

	sn = cv_slot_n( g_replay_save_slot );
	if( !set_replay_char_slot( kind, sn, c ) )
		flg_success = FALSE;

	return flg_success;
}

/***************************************************************
* ��ץ쥤�� 1 ʸ����Ͽ(����åȻ��ꤢ��)
* replay_kind_t kind : ��ץ쥤�μ���
* replay_slot_t sn : ��ץ쥤������å��ֹ�
* long c : ��������ʸ��
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	set_replay_char_slot(
	replay_kind_t kind, replay_slot_t sn, long c
)
{
	if( !g_flg_reg_replay[sn] )
		return TRUE;

	if( !ready_replay( sn, FALSE ) )
		return FALSE;

	if( (KEY_N_0 <= c) && (c <= KEY_N_MAX) )
		return TRUE;

	if( kind != g_replay_cur[sn]->kind ){
		if( !ready_replay( sn, TRUE ) )
			return FALSE;

		g_replay_cur[sn]->kind = kind;
	}

	if( c != '\0' ){
		g_replay_cur[sn]->buf[g_replay_cur[sn]->n] = c;
		g_replay_cur[sn]->n++;
	}
	g_replay_cur[sn]->buf[g_replay_cur[sn]->n] = '\0';

	return TRUE;
}

/***************************************************************
* ��ץ쥤�ε�Ͽ�ν���
* replay_slot_t sn : ��ץ쥤������å��ֹ�
* bool_t flg_break : ����Ū�˹Ԥ�ʬ�䤹�뤫?
* return : ��Ͽ��ǽ��?
***************************************************************/

bool_t	ready_replay( replay_slot_t sn, bool_t flg_break )
{
	if( !g_flg_reg_replay[sn] )
		return FALSE;

	if( g_replay_head[sn] == NULL ){
		g_replay_head[sn] = alloc_replay();
		g_replay_cur[sn] = g_replay_head[sn];

		if( g_replay_head[sn] == NULL )
			return FALSE;

		g_replay_cur[sn]->kind = REPLAY_KIND_KEY;
	}
	if( g_replay_cur[sn] == NULL )
		g_replay_cur[sn] = g_replay_head[sn];

	if( flg_break || (g_replay_cur[sn]->n >= REPLAY_BUF_MAX_LEN) ){
		g_replay_cur[sn]->next = alloc_replay();
		if( g_replay_cur[sn]->next == NULL )
			return FALSE;

		g_replay_cur[sn]->next->kind = g_replay_cur[sn]->kind;
		g_replay_cur[sn] = g_replay_cur[sn]->next;
	}

	return TRUE;
}

/***************************************************************
* ��ץ쥤�������ѥǡ������֤�
* char *buf : �������ꥹ�Ȥ��֤�
* long *idx : ���ߤΥ����ΰ��֤��֤�
* long *len : ���ߤΥ�����Ĺ�����֤�
* return : �������ɬ�פ����뤫?
***************************************************************/

bool_t	get_draw_replay( char *buf, long *idx, long *len )
{
	replay_t	*p, *next_p;
	long	n, next_n;
	bool_t	flg_redraw, flg_set_next;
	char	tmp[1 + 1], *tmp2;
	long	len_tmp2;
	long	i;

	if( buf == NULL )
		return FALSE;
	if( idx == NULL )
		return FALSE;
	if( len == NULL )
		return FALSE;

	buf[0] = '\0';
	*idx = 0;
	*len = 0;

	flg_redraw = FALSE;
	flg_set_next = FALSE;

	p = g_replay_cur_draw;
	n = g_play_replay_idx_draw;
	next_p = p;
	next_n = n;
	if( p == NULL )
		return FALSE;

	for( i = 0; i < SCREEN_WIDTH - 4; i += len_tmp2 ){
		if( str_len_draw( buf ) >= SCREEN_WIDTH )
			break;

		tmp[0] = get_replay_next_key( &p, &n );
		tmp[1] = '\0';
		if( tmp[0] == '\0' )
			break;
		tmp2 = cv_esc_ctrl_str( tmp );
		len_tmp2 = str_len_draw( tmp2 );
		str_max_n_cat( buf, tmp2, SCREEN_WIDTH );

		if( !flg_set_next && (i > (SCREEN_WIDTH / 2)) ){
			flg_set_next = TRUE;
			next_p = p;
			next_n = n;
		}

		/* ���߰��֤�Ƭ�Ф��Ǥ��� */

		if( (p == g_replay_cur[REPLAY_SLOT_PLAY])
				&& (n > g_play_replay_idx)
				&& (*idx == 0) ){
			*idx = i;
			*len = len_tmp2;

			/* ���̤����� 3/4 ��ã����������� */

			if( i > (SCREEN_WIDTH * 3 / 4) ){
				flg_redraw = TRUE;

				g_replay_cur_draw = next_p;
				g_play_replay_idx_draw = next_n;
				p = next_p;
				n = next_n;

				buf[0] = '\0';
				*idx = 0;
				*len = 0;

				i = 0 - len_tmp2;
				continue;
			}
		}
	}

	if( i > SCREEN_WIDTH )
		i = SCREEN_WIDTH;
	buf[i] = '\0';

	return flg_redraw;
}

/***************************************************************
* ��ץ쥤�������ѥǡ������֤� (GUI ��)
* char *buf : �������ꥹ�Ȥ��֤�
* long len : ������Ĺ��
***************************************************************/

void	get_draw_replay_gui( char *buf, long len )
{
	replay_t	*p;
	long	idx;
	long	i;

	if( buf == NULL )
		return;

	buf[0] = '\0';
	p = g_replay_cur[REPLAY_SLOT_PLAY];
	if( p == NULL )
		return;
	idx = g_play_replay_idx;

	for( i = 0; i < len; i++ ){
		char	tmp[1 + 1];

		tmp[0] = get_replay_next_key( &p, &idx );
		tmp[1] = '\0';
		if( tmp[0] == '\0' )
			break;

		str_max_n_cat( buf, cv_esc_ctrl_str( tmp ), len );
	}
}

/***************************************************************
* ��ץ쥤�Υ�����������å�
* g_play_replay_turn, g_play_replay_count, g_play_replay_char
* �Τ��Ť����Ѥ��ʤ���硢���˸ƤФ�� get_replay_key ��
* ��ץ쥤�ν�λ�������֤���
* long c : ��ץ쥤������
***************************************************************/

void	chk_replay_key( long c )
{
	if( !g_flg_play_replay )
		return;

	g_play_replay_char = '\0';

	switch( c ){
	case CASE_EXEC:
		g_play_replay_turn = get_turn();
		break;
	case CASE_ENTER:
	default:
		g_play_replay_count = 1;
		break;
	case ' ':
		g_play_replay_count = 10;
		break;
	case '\0':
	case CMD_KEY_IDLE:
		g_play_replay_char = CMD_KEY_IDLE;
		break;
	case CMD_KEY_CONT_EXEC:
		toggle_continue_exec_mode();
		g_play_replay_char = CMD_KEY_IDLE;
		break;
	case CASE_CANCEL:
	case CASE_EXIT:
	case CASE_SQUARE:
		set_flg_play_replay( FALSE );
		break;
	}
}

/***************************************************************
* ��ץ쥤�ξ��֤˱����ƥ�ץ쥤���������֤�
* return : ��ץ쥤������
***************************************************************/

long	get_replay_key( void )
{
	replay_t	**pp;
	long	*idx;

	if( !g_flg_play_replay )
		return '\0';

	if( g_play_replay_char != '\0' ){
		long	c;

		c = g_play_replay_char;
		g_play_replay_char = '\0';

		return c;
	}

	pp = &(g_replay_cur[REPLAY_SLOT_PLAY]);
	idx = &g_play_replay_idx;

	if( g_play_replay_turn == get_turn() )
		return get_replay_next_key( pp, idx );
	else
		g_play_replay_turn = -1;

	if( g_play_replay_count > 0 ){
		g_play_replay_count--;
		return get_replay_next_key( pp, idx );
	}

	return '\0';
}

/***************************************************************
* ���Υ�ץ쥤���������֤�
* replay_t **pp : 
* long *idx : ���ߤΥ����ΰ��֤��֤�
* return : ��ץ쥤������
***************************************************************/

long	get_replay_next_key( replay_t **pp, long *idx )
{
	long	c;

	if( pp == NULL )
		return '\0';
	if( idx == NULL )
		return '\0';

	if( !g_flg_play_replay )
		return '\0';

	for( ; *pp != NULL; *pp = (*pp)->next, *idx = 0 ){
		c = (*pp)->buf[*idx];
		if( c != '\0' ){
			(*idx)++;
			return c;
		}
	}

	return '\0';
}

/***************************************************************
* ��ץ쥤�κ����ե饰���֤�
* return : �����ե饰
***************************************************************/

bool_t	get_flg_play_replay( void )
{
	return g_flg_play_replay;
}

/***************************************************************
* ��ץ쥤�κ����ե饰������
* bool_t flg : �����ե饰
***************************************************************/

void	set_flg_play_replay( bool_t flg )
{
	g_flg_play_replay = flg;

	if( flg ){
		g_replay_cur[REPLAY_SLOT_PLAY]
				= g_replay_head[REPLAY_SLOT_PLAY];
		g_replay_cur_draw
				= g_replay_head[REPLAY_SLOT_PLAY];

		if( g_replay_head[REPLAY_SLOT_PLAY] != NULL )
			g_replay_head[REPLAY_SLOT_PLAY]->n = 0;

		g_play_replay_turn = -1;
		g_play_replay_count = 0;

		g_play_replay_idx = 0;
		g_play_replay_idx_draw = 0;

		if( g_flg_gui )
			call_gui_replay_bgn();
	} else {
		g_play_replay_turn = -1;
		g_play_replay_count = 0;

		redraw_all();

		if( g_flg_gui )
			call_gui_replay_end();
	}
}

/***************************************************************
* ��ץ쥤�μ���� ID ���֤�
* long n : �ǡ���������å��ֹ�
* return : ��ץ쥤�μ���� ID
***************************************************************/

char	*get_msg_replay_kind( replay_t *p )
{
	if( p == NULL )
		return "";

	switch( p->kind ){
	case REPLAY_KIND_KEY:
		return MSG_REPLAY_KIND_KEY;
		break;
	case REPLAY_KIND_GETS:
		return MSG_REPLAY_KIND_GETS;
		break;
	case REPLAY_KIND_MAX_N:
		break;
	}

	return "";
}

/***************************************************************
* �ǡ���������å��ֹ椫���ץ쥤������å��ֹ���Ѵ�
* long n : �ǡ���������å��ֹ�
* return : ��ץ쥤������å��ֹ�
***************************************************************/

replay_slot_t	cv_slot_n( long n )
{
	if( n == SAVE_N_AUTO )
		return REPLAY_SLOT_AUTO;
	else if( n == SAVE_N_BUG_REPO )
		return REPLAY_SLOT_BUG_REPO;
	else
		return REPLAY_SLOT_STD;
}

/***************************************************************
* ��ץ쥤������μ���֤�
* return : ��ץ쥤������μ�
***************************************************************/

long	get_replay_randm_seed( long n )
{
	replay_slot_t	sn = cv_slot_n( n );

	return g_replay_randm_seed[sn];
}

/***************************************************************
* ��ץ쥤�Υ������ֹ���֤�
* return : ��ץ쥤�Υ������ֹ�
***************************************************************/

long	get_replay_save_n( void )
{
	return g_replay_save_slot;
}

/***************************************************************
* ��ץ쥤���ꥹ�Ȥ���Ƭ���֤�
* long n : �ǡ���������å��ֹ�
* return : ��ץ쥤���ꥹ�Ȥ���Ƭ
***************************************************************/

replay_t	*get_replay_head( long n )
{
	replay_slot_t	sn = cv_slot_n( n );

	return g_replay_head[sn];
}

/***************************************************************
* ��ץ쥤�Υ��꡼�������
* return : ���꡼
***************************************************************/

replay_t	*alloc_replay( void )
{
	replay_t	*p;

	p = (replay_t *)alloc_mem( sizeof( replay_t ), FALSE );
	if( p == NULL ){
		end_reg_replay( SAVE_N_AUTO );
		end_reg_replay( SAVE_N_BUG_REPO );
		end_reg_replay( g_replay_save_slot );

		return NULL;
	}

	p->next = NULL;
	p->kind = REPLAY_KIND_KEY;
	p->n = 0;
	p->buf[0] = '\0';

	return p;
}

/***************************************************************
* ��ץ쥤�Υ��꡼����
* replay_t *p : ���꡼
***************************************************************/

void	free_replay( replay_t *p )
{
	free_mem( p );
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_replay_c( void )
{
	check_memory( check_memory_replay_c_g_replay_save_slot,
			"replay.c: g_replay_save_slot" );
	check_memory( check_memory_replay_c_g_flg_reg_replay,
			"replay.c: g_flg_reg_replay" );
	check_memory( check_memory_replay_c_g_replay_randm_seed,
			"replay.c: g_replay_randm_seed" );
	check_memory( check_memory_replay_c_g_replay_head,
			"replay.c: g_replay_head" );
	check_memory( check_memory_replay_c_g_replay_cur,
			"replay.c: g_replay_cur" );
	check_memory( check_memory_replay_c_g_replay_cur_draw,
			"replay.c: g_replay_cur_draw" );
	check_memory( check_memory_replay_c_g_flg_play_replay,
			"replay.c: g_flg_play_replay" );
	check_memory( check_memory_replay_c_g_play_replay_idx,
			"replay.c: g_play_replay_idx" );
}
