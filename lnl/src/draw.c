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
* $Id: draw.c,v 1.428 2014/03/13 02:08:15 bowkenken Exp $
***************************************************************/

/***************************************************************
* ����
***************************************************************/

#define	DRAW_C
#include	"inc.h"

/***************************************************************/

#include	"draw-tab.h"

/***************************************************************
* ���顼�μ���
***************************************************************/

/* ��å����� */
#define	STR_MESSAGE	"MESSAGE: %s\n"
/* �ٹ� */
#define	STR_WARNING	"WARNING: %s\n"
/* ���顼 */
#define	STR_ERROR	"ERROR: %s\n"
/* ��̿Ū���顼 */
#define	STR_FATAL	"FATAL: %s\n"

/***************************************************************/

/* �ե졼�ࡦ�졼�� */
#ifndef	CLK_TCK
# define	CLK_TCK	10000
#endif	/* CLK_TCK */

/* �ե졼�ࡦ�졼�Ȥ��¬�����ÿ� */
#define	MEASURE_CLK_TCK_SEC	5

/***************************************************************
* ���ơ�����
***************************************************************/

/* ���ơ�����ɽ���Υ⡼���ڤ괹�� */
static stat_mode_t	g_stat_mode_n;
check_memory_def( check_memory_draw_c_g_stat_mode_n )

/***************************************************************
* ��å��������ꥹ��
***************************************************************/

#define	PRINT_WORDS_LINE_MAX_LEN	(SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8)
#define	PRINT_WORDS_WIDTH	(WIN_MORE_DRAW_MIN_X - WIN_MSG_DRAW_MIN_X)
#define	PRINT_WORDS_BUF_SIZ	(SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 * 12)
#define	PRINT_BUF_SIZ	(SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8)

/* �ꥹ�� */
static ls_msg_t	g_ls_msg[LS_MSG_MAX_N];
check_memory_def( check_memory_draw_c_g_ls_msg )

/* �ꥹ�Ȥθ��߰��� */
static long	g_ls_msg_idx;
/* �ꥹ�ȤιԿ� */
static long	g_ls_msg_n;
/* ��������ԤΥ���ǥå��� */
static long	g_scroll_msg_idx;
/* 1�ԥ⡼�ɤǤΥ�������ԤΥ���ǥå��� */
static long	g_scroll_1_msg_idx;
check_memory_def( check_memory_draw_c_g_ls_msg_idx )

/* ��å��������ɽ������ɬ�פ����뤫? */
static bool_t	g_flg_ls_msg;
/* ��å�������ʣ���ԥ⡼�� */
static bool_t	g_flg_msg_mul_line;
check_memory_def( check_memory_draw_c_g_flg_ls_msg )

/***************************************************************
* ���ơ��������С�
***************************************************************/

/* ���ơ��������С��˥���饯���Υҥ�Ȥ�ɽ�����뤫? */
static bool_t	g_flg_stat_bar_hint_chr;
/* ���ơ��������С��˥��֥������ȤΥҥ�Ȥ�ɽ�����뤫? */
static bool_t	g_flg_stat_bar_hint_obj;
check_memory_def( check_memory_draw_c_g_flg_stat_bar_hint_chr )

/***************************************************************
* ��˥塼
***************************************************************/

/* ��˥塼�Υڡ����ڤ��ؤ��ޡ�����ȿž���褹�뤫? */
#define	FLG_MENU_PAGE_ATTR_REV	FALSE

/* ��˥塼�����褵��ơ��ä�ɬ�פ����뤫? */
static bool_t	flg_draw_menu;
check_memory_def( check_memory_draw_c_flg_draw_menu )

/* �������ϥ�˥塼�ǥޥ���������å��� enter �������Ѵ����뼱���� */
#define	CUI_MOUSE_CLICK_MENU_NUM_ENTER	256

static long	g_cui_mouse_menu_sel_n;
static edit_class_t	g_cui_mouse_edit_class_sel_n;
static edit_skill_t	g_cui_mouse_edit_skill_sel_n;
static bool_t	g_flg_cui_mouse_scroll_menu_num_is_sel;
static bool_t	g_flg_cui_mouse_r_click_menu_num_is_cancel;
check_memory_def( check_memory_draw_c_g_cui_mouse_menu_sel_n )

/***************************************************************/

/* �ޥåפΥ���������� */
static pos_t	map_draw_pos;
/* �ޥåפΥ���������� (GUI) */
static pos_t	map_draw_pos_gui;
check_memory_def( check_memory_draw_c_map_draw_pos )

/* �西���󡢲��̤�����褹�뤫? */
static bool_t	flg_redraw_every_turn;
check_memory_def( check_memory_draw_c_flg_redraw_every_turn )

/***************************************************************
* ��ʸ�Υӥ��奢�롦���ե�����
***************************************************************/

#define	TYPHOON_DUST_MAX_N	24
#define	TYPHOON_SPEED	5
#define	ANIM_TYPHOON_SEC	(4.0)
#define	ANIM_TYPHOON_FRAME_N	(ANIM_FRAME_N * 3 / 100)

#define	ANIM_CONFLAGRATION_SEC	(4.0)
#define	ANIM_CONFLAGRATION_FRAME_N	(ANIM_FRAME_N * 5 / 100)
#define	ANIM_CONFLAGRATION_HEIGHT	(WIN_MAP_DRAW_HEIGHT / 2)

#define	ANIM_EARTHQUAKE_SEC	(4.0)
#define	ANIM_EARTHQUAKE_FRAME_N	(ANIM_FRAME_N * 1 / 10)

#define	ANIM_THUNDER_FRAME_N	(ANIM_FRAME_N * 5 / 100)
#define	ANIM_THUNDER_CLR_FRAME_N	(ANIM_FRAME_N * 20 / 10)
#define	ANIM_THUNDER_HEIGHT	(WIN_MAP_DRAW_HEIGHT / 2)

#define	ANIM_INUNDATION_FRAME_N	(ANIM_FRAME_N * 5 / 100)
#define	ANIM_INUNDATION_CLR_FRAME_N	(ANIM_FRAME_N * 20 / 10)

/***************************************************************
* ����¾�Υӥ��奢�롦���ե�����
***************************************************************/

/* �� */

#define	ANIM_ARW_FRAME_N	\
		((ANIM_FRAME_N * 10 / 10) - ANIM_ARW_CLR_FRAME_N)
#define	ANIM_ARW_CLR_FRAME_N	(ANIM_FRAME_N * 5 / 10)

/* �ҥå� */

#define	ANIM_HIT_FRAME_N	\
		((ANIM_FRAME_N * 4 / 10) - ANIM_HIT_CLR_FRAME_N)
#define	ANIM_HIT_CLR_FRAME_N	(ANIM_FRAME_N * 2 / 10)
#define	ANIM_HIT_WAIT_CLOCK	(ANIM_FRAME_N * 4 / 10)
#define	ANIM_HIT_R	2
#define	STR_ANIM_HIT	"/"

/* ����ƥ����롦�ҥå� */

#define	ANIM_CRTCL_FRAME_N	\
		((ANIM_FRAME_N * 8 / 10) - ANIM_CRTCL_CLR_FRAME_N)
#define	ANIM_CRTCL_CLR_FRAME_N	(ANIM_FRAME_N * 4 / 10)
#define	ANIM_CRTCL_WAIT_CLOCK	(ANIM_FRAME_N * 8 / 10)
#define	ANIM_CRTCL_R	2
#define	STR_ANIM_CRTCL_1	"/"
#define	STR_ANIM_CRTCL_2	"\\"

/* ����¾ */

#define	ANIM_NUM_FRAME_N	(ANIM_FRAME_N * 10 / 10)
#define	ANIM_LEV_UP_FRAME_N	(ANIM_FRAME_N * 20 / 10)

/* ��ʸ */

#define	ANIM_SPELL_LEN	8
#define	ANIM_SPELL_FRAME_N	\
		((ANIM_FRAME_N * 15 / 10) - ANIM_SPELL_CLR_FRAME_N)
#define	ANIM_SPELL_CLR_FRAME_N	(ANIM_FRAME_N * 5 / 10)

/***************************************************************
* �ӥ��奢�롦���ե����Ȥ��ѿ�
***************************************************************/

/* ������Ԥ�����(%) */
static rate_t	vfx_wait;
check_memory_def( check_memory_draw_c_vfx_wait )

/* ���С������褹�륨�ե����ȤΥե��륿�� */
static flg_vfx_mbr_t	flg_vfx_mbr;
/* ��󥹥��������褹�륨�ե����ȤΥե��륿�� */
static flg_vfx_mnstr_t	flg_vfx_mnstr;
check_memory_def( check_memory_draw_c_flg_vfx_mbr )

/* ���ե����Ȥθ��ߤ�ɽ��°�� */
static curs_attr_t	g_vfx_attr;
check_memory_def( check_memory_draw_c_g_vfx_attr )

/* �ե졼�ࡦ�졼�� */
static long	g_clk_tck;
check_memory_def( check_memory_draw_c_g_clk_tck )

/* ���ǤĿ����� VFX ��������褹�뤫? */
static bool_t	g_flg_sync_vfx_num;
check_memory_def( check_memory_draw_c_g_flg_sync_vfx_num )

/***************************************************************
* GUI �Υӥ��奢�롦���ե�����
***************************************************************/

#define	GUI_VFX_POOL_MAX_N	64
#define	GUI_VFX_ANIM_RATE	((rate_t)5)

static gui_vfx_t	g_gui_vfx_pool[GUI_VFX_POOL_MAX_N];
check_memory_def( check_memory_draw_c_g_gui_vfx_pool )

/***************************************************************
* �������Хåե�
***************************************************************/

/* �Хåե��������� */
#define	KEY_BUF_MAX_LEN	1024

/* 1 ʸ���������Ϥ������ᤷ����ʸ�� */
static long	g_un_get_key_c;
check_memory_def( check_memory_draw_c_g_un_get_key_c )

/* ��Ƭ������ */
static long	g_key_buf_head, g_key_buf_tail;
check_memory_def( check_memory_draw_c_g_key_buf_head )
/* �Хåե� */
static char	g_key_buf[KEY_BUF_MAX_LEN];
check_memory_def( check_memory_draw_c_g_key_buf )

/* �������ơ��֥� */
static char	*g_key_tab[KEY_TAB_MAX_N];
check_memory_def( check_memory_draw_c_g_key_tab )

/* �������Ϥ����Ǥ��� */
static bool_t	g_flg_break_key;
check_memory_def( check_memory_draw_c_g_flg_break_key )

#define FLAG_USE_ISCNTRL	0

/***************************************************************
* �ޥ���ε�Ͽ�⡼��
***************************************************************/

#define	REG_MACRO_LEN	MACRO_MAX_LEN

bool_t	g_flg_reg_macro;
long	g_reg_macro_idx;
check_memory_def( check_memory_draw_c_g_flg_reg_macro )
char	g_reg_macro_buf[REG_MACRO_LEN + 1];
check_memory_def( check_memory_draw_c_g_reg_macro_buf )

/***************************************************************
* ����饯��������褹��ɬ�פ����뤫�ɤ����Υե饰
***************************************************************/

#define	USE_FLG_UPDATE_CHR	0

long	g_flg_update_chr[MAP_MAX_Y][MAP_MAX_X];
check_memory_def( check_memory_draw_c_g_flg_update_chr )

/***************************************************************
* ���С����ǡ���
***************************************************************/

#define	DRAW_MBR_DATA_MAX_LEN	255
#define	DRAW_MBR_DATA_MAX_LEN_ADD_LEV	10

data_n_t	g_cui_mouse_mbr_data_cur_n;
long	g_cui_mouse_mbr_data_cur_page_n;
mbr_data_edit_kind_t	g_cui_mouse_mbr_data_edit_kind;
check_memory_def( check_memory_draw_c_g_cui_mouse_mbr_data_cur_n )

/***************************************************************/

#define	GET_KEY_MAX_LEN	127

static flg_msg_t	static_more__prev_flg;
static long	static_more__prev_turn;

static long	static_draw_misc_stat_time__pre_minute;

static long	static_draw_replay__pre_idx = 0;

check_memory_def( check_memory_draw_c_prev_flg )

/***************************************************************
* ����ν����
***************************************************************/

void	init_draw( void )
{
	long	i;

	g_clk_tck = CLK_TCK;

	g_stat_mode_n = STAT_MODE_MBR;

	g_ls_msg_idx = -1;
	g_ls_msg_n = 0;
	g_scroll_msg_idx = -1;
	g_scroll_1_msg_idx = -1;
	g_flg_ls_msg = FALSE;

	g_flg_stat_bar_hint_chr = FALSE;
	g_flg_stat_bar_hint_obj = FALSE;

	flg_draw_menu = FALSE;

	map_draw_pos.x = 0;
	map_draw_pos.y = 0;
	map_draw_pos_gui.x = 0;
	map_draw_pos_gui.y = 0;
	set_redraw_every_turn( FALSE );
	set_msg_mul_line( TRUE );

	vfx_wait = 100;

	g_flg_sync_vfx_num = FALSE;

	flg_vfx_mbr = FLG_NULL;
	flg_vfx_mbr |= FLG_VFX_MBR_CURE;
	flg_vfx_mbr |= FLG_VFX_MBR_DAM;
	flg_vfx_mbr |= FLG_VFX_MBR_CRTCL;
	flg_vfx_mbr |= FLG_VFX_MBR_ARW;

	flg_vfx_mnstr = FLG_NULL;
	flg_vfx_mnstr |= FLG_VFX_MNSTR_CURE;
	flg_vfx_mnstr |= FLG_VFX_MNSTR_DAM;
	flg_vfx_mnstr |= FLG_VFX_MNSTR_CRTCL;
	flg_vfx_mnstr |= FLG_VFX_MNSTR_ARW;

	for( i = 0; i < GUI_VFX_POOL_MAX_N; i++ )
		g_gui_vfx_pool[i].flg_use = FALSE;

	g_cui_mouse_menu_sel_n = 0;
	g_cui_mouse_edit_class_sel_n = EDIT_CLASS_NULL;
	g_cui_mouse_edit_skill_sel_n = EDIT_SKILL_NULL;
	g_cui_mouse_mbr_data_cur_n = (data_n_t)0;
	g_cui_mouse_mbr_data_cur_page_n = 0;
	g_cui_mouse_mbr_data_edit_kind = MBR_DATA_EDIT_KIND_SHOW;
	g_flg_cui_mouse_scroll_menu_num_is_sel = TRUE;
	g_flg_cui_mouse_r_click_menu_num_is_cancel = FALSE;

	for( i = 0; okuri_tab[i].n_str != N_MSG_NULL; i++ )
		okuri_tab[i].str = MSG( okuri_tab[i].n_str );
	okuri_tab[i].str = NULL;

	for( i = 0; kin_soku_tab[i].n_str != N_MSG_NULL; i++ )
		kin_soku_tab[i].str = MSG( kin_soku_tab[i].n_str );
	kin_soku_tab[i].str = NULL;

	/* key */

	set_flg_break_key( FALSE );

	g_un_get_key_c = '\0';

	g_key_buf_head = 0;
	g_key_buf_tail = 0;

	for( i = 0; i < KEY_TAB_MAX_N; i++ )
		g_key_tab[i] = NULL;

	/* macro */

	g_flg_reg_macro = FALSE;
	g_reg_macro_idx = 0;
	g_reg_macro_buf[0] = '\0';
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_draw( void )
{
	static_more__prev_flg = FLG_NULL;
	static_more__prev_turn = -1;

	static_draw_misc_stat_time__pre_minute = 0;

	static_draw_replay__pre_idx = 0;
}

/***************************************************************
* ����ե�����ΥС�������Ѵ�
***************************************************************/

void	ver_up_draw_ver_1_2_22( void )
{
	g_flg_msg_mul_line = TRUE;
	flg_redraw_every_turn = FALSE;

	vfx_wait = _100_PERCENT;

	flg_vfx_mbr = FLG_NULL;
	flg_vfx_mbr |= FLG_VFX_MBR_CURE;
	flg_vfx_mbr |= FLG_VFX_MBR_DAM;
	flg_vfx_mbr |= FLG_VFX_MBR_CRTCL;
	flg_vfx_mbr |= FLG_VFX_MBR_ARW;

	flg_vfx_mnstr = FLG_NULL;
	flg_vfx_mnstr |= FLG_VFX_MNSTR_CURE;
	flg_vfx_mnstr |= FLG_VFX_MNSTR_DAM;
	flg_vfx_mnstr |= FLG_VFX_MNSTR_CRTCL;
	flg_vfx_mnstr |= FLG_VFX_MNSTR_ARW;

	measure_clk_tck();
}

/***************************************************************
* �ե졼�ࡦ�졼�Ȥη�¬
***************************************************************/

void	measure_clk_tck( void )
{
	const long	sec = MEASURE_CLK_TCK_SEC;
	clock_t	bgn_clk, end_clk;

	print_msg( FLG_NULL, MSG_MEASURE_CLK_TCK, sec );

	/* ��¬���� */

	bgn_clk = clock();

	/* ��¬�� */

#ifdef	HAVE_SLEEP
	sleep( sec );
#else
	{
		long	t;

		t = time( NULL ) + sec;

		while( time( NULL ) < t )
			;
	}
#endif

	/* ��¬��λ */

	end_clk = clock();
	g_clk_tck = (end_clk - bgn_clk) / sec;

	print_msg( FLG_NULL, MSG_MEASURE_CLK_TCK_FINISH,
			(long)end_clk, (long)bgn_clk,
			(long)sec, (long)g_clk_tck );
}

/***************************************************************
* �ٹ��ɽ��
* const char *s : �ե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_wrn( const char *s, ... )
{
	va_list	argptr;
	static char	str[PRINT_BUF_SIZ + 1];

	va_start( argptr, s );
	vsn_printf( str, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	dis_scrn();

	if( g_flg_cui ){
		fprintf( stderr, STR_WARNING, str );
		fflush( stderr );
	}

	ena_scrn( FALSE );
}

/***************************************************************
* ���顼��ɽ��
* const char *s : �ե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_err( const char *s, ... )
{
	va_list	argptr;
	static char	str[PRINT_BUF_SIZ + 1];

	va_start( argptr, s );
	vsn_printf( str, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	dis_scrn();

	if( g_flg_cui ){
		fprintf( stderr, STR_ERROR, str );
		fflush( stderr );
	}

	ena_scrn( FALSE );
}

/***************************************************************
* ����������ηٹ��ɽ��
* const char *s : �ե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_lex_wrn( const char *s, ... )
{
	va_list	argptr;
	static char	str[PRINT_BUF_SIZ + 1];

	va_start( argptr, s );
	vsn_printf( str, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	dis_scrn();

	if( g_flg_cui ){
		fprintf( stderr, "%s:%ld: %s\n",
				get_rc_lex_file_name(),
				get_rc_lex_line(), str );
		fflush( stderr );
	}

	ena_scrn( FALSE );
}

/***************************************************************
* ����������Υ��顼��ɽ��
* const char *s : �ե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_lex_err( const char *s, ... )
{
	va_list	argptr;
	static char	str[PRINT_BUF_SIZ + 1];

	set_rc_lex_err( TRUE );

	va_start( argptr, s );
	vsn_printf( str, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	dis_scrn();

	if( g_flg_cui ){
		fprintf( stderr, "%s:%ld: %s\n",
				get_rc_lex_file_name(),
				get_rc_lex_line(), str );
		fflush( stderr );
	}

	ena_scrn( FALSE );
}

/***************************************************************
* ����դ�ɽ�� (����ա�������ɥ���ɽ�����ʤ�)
* const char *name : ̾��
* sex_t sex : ����
* const char *fmt_female : �����Υե����ޥå�
* const char *fmt_male : �����Υե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_words(
	const char *name,
	sex_t sex,
	const char *fmt_female,
	const char *fmt_male,
	...
)
{
	va_list	argptr;
	static char	buf[PRINT_WORDS_BUF_SIZ + 1];

	/* ���̤�ʬ���� */

	va_start( argptr, fmt_male );
	if( sex == FEMALE )
		vsn_printf( buf, PRINT_WORDS_BUF_SIZ, fmt_female, argptr );
	else
		vsn_printf( buf, PRINT_WORDS_BUF_SIZ, fmt_male, argptr );
	va_end( argptr );

	print_words_sub( FALSE, name, buf );
}

/***************************************************************
* ����դ�ɽ�� (����ա�������ɥ���ɽ��)
* const char *name : ̾��
* sex_t sex : ����
* const char *fmt_female : �����Υե����ޥå�
* const char *fmt_male : �����Υե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_words_win(
	const char *name,
	sex_t sex,
	const char *fmt_female,
	const char *fmt_male,
	...
)
{
	va_list	argptr;
	static char	buf[PRINT_WORDS_BUF_SIZ + 1];

	/* ���̤�ʬ���� */

	va_start( argptr, fmt_male );
	if( sex == FEMALE )
		vsn_printf( buf, PRINT_WORDS_BUF_SIZ, fmt_female, argptr );
	else
		vsn_printf( buf, PRINT_WORDS_BUF_SIZ, fmt_male, argptr );
	va_end( argptr );

	print_words_sub( TRUE, name, buf );
}

/***************************************************************
* ����դ�ɽ��
* bool_t flg_draw_win : ����ա�������ɥ���ɽ�����뤫?
* const char *name : ̾��
* const char *buf : �����
***************************************************************/

void	print_words_sub(
	bool_t flg_draw_win,
	const char *name,
	const char *buf
)
{
	static char	line[PRINT_WORDS_LINE_MAX_LEN + 1];
	static char	str_begin[PRINT_WORDS_LINE_MAX_LEN + 1];
	const char	*head, *tail;
	long	max_len, len;

	/* ̾���Υǥե���� */

	if( name == NULL )
		name = MSG_NULL;

	/* 1�Ԥκ���ʸ���� */

	max_len = PRINT_WORDS_WIDTH;
	max_len -= str_len_draw( MSG_WORDS_END );

	/* ����դγ��� */

	str_nz_cpy( str_begin, name, PRINT_WORDS_LINE_MAX_LEN );
	str_max_n_cat( str_begin, MSG_WORDS_BEGIN, PRINT_WORDS_LINE_MAX_LEN );
	len = max_len - str_len_draw( str_begin );

	head = buf;
	while( 1 ){
		/* 1��ʬ�ڤ�Ф� */

		tail = get_words_line( head, len );
		if( tail == NULL )
			break;
		if( head[0] == '\n' )
			head++;

		/* 1��ʬ���ԡ� */

		str_nz_cpy( line, str_begin, PRINT_WORDS_LINE_MAX_LEN );
		strncat( line, head, tail - head );
		if( tail[0] == '\0' ){
			str_max_n_cat( line, MSG_WORDS_END,
					PRINT_WORDS_LINE_MAX_LEN );
		}

		/* ɽ�� */

		print_msg( FLG_NULL, MSG_S, line );

		/* ���ιԤν��� */

		str_nz_cpy( str_begin, MSG_WORDS_NEXT,
				PRINT_WORDS_LINE_MAX_LEN );
		len = max_len - str_len_draw( str_begin );
		head = tail;
	}

	if( flg_draw_win )
		draw_words( name, buf );
}

/***************************************************************
* ����դ��ڤ�Ф��ʶ�§���������
* const char *p : ���ΤΥ����
* long draw_max_n : �ڤ�Ф�����ʸ����
* return : �ڤ�Ф���ʸ����
***************************************************************/

const char	*get_words_line( const char *p, long draw_max_n )
{
	lang_kind_t	k;
	unsigned long	c;
	long	div_n, draw_n, n;
	long	len;
	long	i;

	if( p == NULL )
		return NULL;
	if( *p == '\0' )
		return NULL;

	k = get_lang_kind();

	draw_max_n -= 2;
	draw_max_n = min_l( str_len_draw( p ), draw_max_n );

	div_n = 0;
	draw_n = 0;
	n = 0;
	if( p[0] == '\n' ){
		div_n++;
		draw_n++;
		n++;
	}

	/* �ڤ���ɤ�����õ�� */

	while( draw_n < draw_max_n + 1 ){
		if( p[n] == '\0' ){
			div_n = n;
			break;
		} else if( p[n] == '\n' ){
			div_n = n;
			break;
		}
		switch( k ){
		default:
		case LANG_KIND_ENGLISH:
			if( p[n] == ' ' )
				div_n = n + 1;
			draw_n++;
			n++;
			break;
		case LANG_KIND_JAPANESE_EUC:
			c = (unsigned char)p[n];
			if( c >= 0xa0 ){
				div_n = n;
				draw_n += 2;
				n += 2;
			} else if( c == 0x8e ){
				div_n = n;
				draw_n += 1;
				n += 2;
			} else if( c == 0x8f ){
				div_n = n;
				draw_n += 2;
				n += 3;
			} else {
				div_n = n;
				draw_n += 1;
				n += 1;
			}
			break;
		case LANG_KIND_JAPANESE_UTF_8:
			if( p[n] & 0x80 ){
				div_n = n;
				draw_n += 2;
				n++;

				while( p[n] != '\0' ){
					c = (unsigned char)(p[n] & 0xc0);
					if( c != 0x80 )
						break;
					n++;
				}
			} else {
				div_n = n;
				draw_n++;
				n++;
			}
			break;
		case LANG_KIND_JAPANESE_SJIS:
			if( p[n] & 0x80 ){
				div_n = n;
				draw_n += 2;
				n += 2;
			} else {
				div_n = n;
				draw_n++;
				n++;
			}
			break;
		}
	}

	if( div_n == 0 )
		div_n = draw_max_n;
	p = &(p[div_n]);

	/* ������� */

	for( i = 0; okuri_tab[i].str != NULL; i++ ){
		len = str_len_std( okuri_tab[i].str );
		if( len <= 0 )
			continue;
		if( strncmp( p, okuri_tab[i].str, len ) == 0 )
			return p;
	}

	/* ��§���� */

	for( i = 0; kin_soku_tab[i].str != NULL; i++ ){
		len = str_len_std( kin_soku_tab[i].str );
		if( len <= 0 )
			continue;
		if( strncmp( p, kin_soku_tab[i].str, len ) == 0 )
			return( p + len );
	}

	return p;
}

/***************************************************************
* ʸ����μ���ʸ����������Ф�
* const char *p : ʸ����
* return : ʸ����
***************************************************************/

const char	*get_next_char_str( const char *p )
{
	long	nextLen;
	static char str[16 + 1];

	nextLen = get_next_char_len( p );
	str_nz_cpy( str, p, nextLen );

	return str;
}

/***************************************************************
* ʸ����μ���ʸ���ΥХ��ȿ����֤�
* const char *p : ʸ����
* return : �Х��ȿ�
***************************************************************/

long	get_next_char_len( const char *p )
{
	long	n;
	long	c;

	n = 0;

	if( p[n] == '\0' )
		return n;

	switch( get_lang_kind() ){
	default:
	case LANG_KIND_ENGLISH:
		n++;
		break;
	case LANG_KIND_JAPANESE_EUC:
		c = (unsigned char)p[n];
		if( c >= 0xa0 ){
			n += 2;
		} else if( c == 0x8e ){
			n += 2;
		} else if( c == 0x8f ){
			n += 3;
		} else {
			n += 1;
		}
		break;
	case LANG_KIND_JAPANESE_UTF_8:
		if( p[n] & 0x80 ){
			n++;
			while( p[n] != '\0' ){
				c = (unsigned char)(p[n] & 0xc0);
				if( c != 0x80 )
					break;
				n++;
			}
		} else {
			n++;
		}
		break;
	case LANG_KIND_JAPANESE_SJIS:
		if( p[n] & 0x80 ){
			n += 2;
		} else {
			n++;
		}
		break;
	}

	return n;
}

/***************************************************************
* ����饯�������С����ڥåȤλ���������å�������ɽ��
* chr_t *chr : ����饯��
* flg_msg_t flg : ��å������Υե饰
* const char *s : ��å������Υե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_msg_mbr( chr_t *chr, flg_msg_t flg, const char *s, ... )
{
	va_list	argptr;
	static char	buf[PRINT_BUF_SIZ + 1];

	va_start( argptr, s );
	vsn_printf( buf, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	if( chr == NULL )
		return;

	if( is_mbr( chr ) || is_pet( chr ) )
		print_msg( flg, MSG_S, buf );
}

/***************************************************************
* ����饯���������Ƥ������������å�������ɽ��
* chr_t *chr : ����饯��
* flg_msg_t flg : ��å������Υե饰
* const char *s : ��å������Υե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_msg_find( chr_t *chr, flg_msg_t flg, const char *s, ... )
{
	va_list	argptr;
	static char	buf[PRINT_BUF_SIZ + 1];

	va_start( argptr, s );
	vsn_printf( buf, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	if( chr == NULL )
		return;
	if( !clip_pos( chr->x, chr->y ) )
		return;
	if( !is_mbr( chr ) )
		if( !chk_flg( chr->flg_map, FLG_MAP_CHR_FIND ) )
			return;

	print_msg( flg, MSG_S, buf );
}

/***************************************************************
* ��å�������ɽ��
* flg_msg_t flg : ��å������Υե饰
* const char *s : ��å������Υե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_msg( flg_msg_t flg, const char *s, ... )
{
	va_list	argptr;
	static char	buf[LS_MSG_MAX_BYTE + 1];
	bool_t	flg_mul;

	/* �ե����ޥå� */

	va_start( argptr, s );
	vsn_printf( buf, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	/* �ǥХå����⡼�ɤ�̵�����˥ǥХå�����å������� */
	/* �褿��ɽ�����ʤ� */

	if( !g_flg_debug && chk_flg( flg, FLG_MSG_DEBUG ) )
		return;

	/* ���������Ԥ� */

	flg_mul = chk_msg_mul_line();
	if( !flg_mul )
		more( (flg & ~FLG_MSG_MORE), flg_mul );

	/* ���̤򥯥ꥢ */

	if( chk_curs() )
		wipe_msg();

	/* ���顼���ο� */

	if( chk_flg_or( flg, (FLG_MSG_WRN | FLG_MSG_ERR | FLG_MSG_FAT) ) )
		curs_attrset_n( CURS_ATTR_N_ERR );

	/* ɽ�� */

	if( buf[0] == '\0' ){
		g_flg_ls_msg = FALSE;
	} else {
		g_flg_ls_msg = TRUE;

		g_ls_msg_idx++;
		g_ls_msg_n++;
		if( g_ls_msg_n > LS_MSG_MAX_N )
			g_ls_msg_n = LS_MSG_MAX_N;

		/* ��å��������ꥹ�Ȥ���¸ */

		str_nz_cpy( g_ls_msg[g_ls_msg_idx % LS_MSG_MAX_N].msg,
				buf, LS_MSG_MAX_BYTE );
		g_ls_msg[g_ls_msg_idx % LS_MSG_MAX_N].attr
				= get_current_attr();

		/* ��������Կ��򥯥ꥢ */

		g_scroll_msg_idx = g_ls_msg_idx;
		g_scroll_1_msg_idx = g_ls_msg_idx;

		/* ɽ�� */

		if( flg_mul ){
			/* ʣ���� */
			print_log();
		} else {
			/* 1�� */
			print_str( WIN_MSG_DRAW_MIN_X,
					get_map_row() + 1,
					MSG_FMT_MSG,
					WIN_MSG_DRAW_WIDTH, MSG_NULL );
			print_str( WIN_MSG_DRAW_MIN_X,
					get_map_row() + 1,
					MSG_FMT_MSG,
					WIN_MSG_DRAW_WIDTH, buf );

			call_gui_message_draw();
		}
	}

	if( chk_flg_or( flg, (FLG_MSG_WRN | FLG_MSG_ERR | FLG_MSG_FAT) ) )
		curs_attrset_dflt();

	/* ���������Ԥ� */

	if( chk_flg( flg, FLG_MSG_MORE ) ){
		more( flg, flg_mul );
		if( !flg_mul )
			wipe_msg();
	}
}

/***************************************************************
* 1 ���������ʣ���ԤΥ�å�������ɽ��������˥������Ϥ��Ԥ�
* flg_msg_t flg : ��å������Υե饰
* bool_t flg_mul : ʣ���ԤΥ�å�������?
***************************************************************/

void	more( flg_msg_t flg, bool_t flg_mul )
{
	flg_msg_t	prev_flg;
	long	prev_turn = -1;
	long	turn;
	bool_t	flg_ret;
	long	y;
	curs_attr_t	old_attr;

	/**/

	prev_flg = static_more__prev_flg;
	prev_turn = static_more__prev_turn;

	/**/

	turn = get_turn();

	if( flg_mul )
		y = get_map_row() + 1 + get_message_row() - 1;
	else
		y = get_map_row() + 1;

	/* ���������Ԥ���ɬ�פ������å� */

	flg_ret = FALSE;

	if( flg_mul )
		flg_ret = TRUE;
	if( prev_turn != turn )
		flg_ret = TRUE;
	if( chk_flg( flg, FLG_MSG_NO_MORE_PREV ) )
		flg_ret = TRUE;
	if( chk_flg( prev_flg, FLG_MSG_NO_MORE_NEXT ) )
		flg_ret = TRUE;
	if( chk_flg( flg, FLG_MSG_MORE ) )
		flg_ret = FALSE;

	prev_flg = flg;
	prev_turn = turn;
	static_more__prev_flg = prev_flg;
	static_more__prev_turn = prev_turn;

	if( flg_ret )
		return;

	/* ���������Ԥ�ɽ����Ф� */

	old_attr = get_current_attr();

	curs_attrset_n( CURS_ATTR_N_REV );
	print_str( WIN_MORE_DRAW_MIN_X, y, MSG_MORE );
	call_gui_message_set_flag_more( TRUE );

	/* �������Ϥ��Ԥ� */

	get_key( TRUE );

	/* ���������Ԥ�ɽ����ä� */

	curs_attrset_dflt();
	print_str( WIN_MORE_DRAW_MIN_X, y, MSG_MORE_CLEAR );
	call_gui_message_set_flag_more( FALSE );

	curs_attrset_dir( &old_attr );
}

/***************************************************************
* ��å�������ä�
***************************************************************/

void	wipe_msg( void )
{
	/* ʣ���ԥ⡼�ɤλ���ɬ��̵�� */

	if( chk_msg_mul_line() )
		return;

	/* ��å�������ä� */

	print_str( WIN_MSG_DRAW_MIN_X, get_map_row() + 1,
			MSG_FMT_MSG,
			WIN_MSG_DRAW_WIDTH, MSG_NULL );
}

/***************************************************************
* ��å�������ä�
***************************************************************/

void	clr_msg( void )
{
	print_msg( FLG_MSG_NO_MORE, MSG_NULL );
}

/***************************************************************
* ��å��������ɽ��
***************************************************************/

void	redraw_msg( void )
{
	/* ʣ���ԥ⡼�ɤλ� */

	if( chk_msg_mul_line() ){
		print_log();
		return;
	}

	/* curses�饤�֥���Ȥ�����1�٥��ꥢ���� */

	if( chk_curs() ){
		print_str( WIN_MSG_DRAW_MIN_X, get_map_row() + 1,
				MSG_FMT_MSG,
				WIN_MSG_DRAW_WIDTH, MSG_NULL );
	}

	/* ɽ������ɬ�פ�ͭ�뤫�����å� */

	if( g_ls_msg_idx < 0 )
		return;
	if( !g_flg_ls_msg )
		return;

	/* ɽ������ */

	curs_attrset_dir( &(g_ls_msg[g_ls_msg_idx % LS_MSG_MAX_N].attr) );
	print_str( WIN_MSG_DRAW_MIN_X, get_map_row() + 1,
			MSG_FMT_MSG, WIN_MSG_DRAW_WIDTH,
			g_ls_msg[g_ls_msg_idx % LS_MSG_MAX_N].msg );
	curs_attrset_dflt();
	call_gui_message_draw();
}

/***************************************************************
* 1�ԥ⡼�ɤǤΥ�å������Υ�������
* long add : ��������Կ�
***************************************************************/

void	scroll_1_msg( long add )
{
	add_scroll_1_msg_idx( add );
	print_log_back_1();
}

/***************************************************************
* 1�ԥ⡼�ɤǤΥ�å������Υ�������ԤΥ���ǥå������ͤ�ä���
* long add : �ä���Կ�
* return : �ä�����Υ���ǥå���
***************************************************************/

long	add_scroll_1_msg_idx( long add )
{
	long	max_n;

	g_scroll_1_msg_idx += add;

	max_n = get_ls_msg_idx();
	if( g_scroll_1_msg_idx < 0 )
		g_scroll_1_msg_idx = 0;
	if( g_scroll_1_msg_idx > max_n )
		g_scroll_1_msg_idx = max_n;

	return g_scroll_1_msg_idx;
}

/***************************************************************
* 1�ԥ⡼�ɤǥ�å������򥹥�����ɽ��
***************************************************************/

void	print_log_back_1( void )
{
	long	n;

	/* 1�ԥ⡼�ɤλ�����ͭ�� */

	if( chk_msg_mul_line() )
		return;

	/* curses�饤�֥���Ȥ�����1�٥��ꥢ���� */

	if( chk_curs() ){
		print_str( WIN_MSG_DRAW_MIN_X, get_map_row() + 1,
				MSG_FMT_MSG,
				WIN_MSG_DRAW_WIDTH, MSG_NULL );
	}

	/* ɽ������ɬ�פ�ͭ�뤫�����å� */

	if( g_scroll_1_msg_idx < 0 )
		return;

	/* ɽ������ */

	n = g_scroll_1_msg_idx % LS_MSG_MAX_N;

	curs_attrset_dir( &(g_ls_msg[n].attr) );
	print_str( WIN_MSG_DRAW_MIN_X, get_map_row() + 1,
			MSG_FMT_MSG, WIN_MSG_DRAW_WIDTH,
			g_ls_msg[n].msg );
	curs_attrset_dflt();
	call_gui_message_draw();
}

/***************************************************************
* ʣ���ԥ⡼�ɤǥ�å�������ɽ��
***************************************************************/

void	print_log( void )
{
	print_log_back( g_scroll_msg_idx );
}

/***************************************************************
* ʣ���ԥ⡼�ɤǥ�å��������ɽ��
* long idx : ɽ�����Ϲ�
***************************************************************/

void	print_log_back( long idx )
{
	long	y, max_y;
	long	n;

	max_y = get_map_row() + 1 + get_message_row();
	n = idx - get_ls_msg_line_per_page() + 1;

	curs_attrset_dflt();

	for( y = get_map_row() + 1; y < max_y; y++, n++ ){

		/* ���ꥢ */

		if( chk_curs() ){
			print_str( WIN_MSG_DRAW_MIN_X, y,
					MSG_FMT_MSG, WIN_MSG_DRAW_WIDTH,
					MSG_NULL );
		}

		/* ��Ƭ��;��� */

		if( n < 0 )
			continue;

		/* ɽ�� */

		curs_attrset_dir( &(g_ls_msg[n % LS_MSG_MAX_N].attr) );
		if( chk_curs() ){
			/* curses�饤�֥���Ȥ�����1�٥��ꥢ���� */
			print_str( WIN_MSG_DRAW_MIN_X, y,
					MSG_FMT_MSG, WIN_MSG_DRAW_WIDTH,
					MSG_NULL );
		}
		print_str( WIN_MSG_DRAW_MIN_X, y,
				MSG_FMT_MSG, WIN_MSG_DRAW_WIDTH,
				g_ls_msg[n % LS_MSG_MAX_N].msg );
		curs_attrset_dflt();
	}
	call_gui_message_draw();
}

/***************************************************************
* ��å��������ꥹ�Ȥθ��߰��֤��֤�
* return : ��å��������ꥹ�Ȥθ��߰���
***************************************************************/

long	get_ls_msg_idx( void )
{
	return g_ls_msg_idx;
}

/***************************************************************
* ��å������Υڡ���������ιԿ����֤�
* return : ��å������Υڡ���������ιԿ�
***************************************************************/

long	get_ls_msg_line_per_page( void )
{
	return( get_message_row() );
}

/***************************************************************
* ��å�������ʣ���ԥ⡼�ɤ�����
* bool_t flg : �⡼��
* return : ���ߤΥ⡼��
***************************************************************/

bool_t	set_msg_mul_line( bool_t flg )
{
	g_flg_msg_mul_line = flg;

	return g_flg_msg_mul_line;
}

/***************************************************************
* ��å�������ʣ���ԥ⡼�ɤ��֤�
* return : ���ߤΥ⡼��
***************************************************************/

bool_t	chk_msg_mul_line( void )
{
	return g_flg_msg_mul_line;
}

/***************************************************************
* ��å��������ꥹ�ȤιԿ����֤�
* return : �Կ�
***************************************************************/

long	get_ls_msg_n( void )
{
	return g_ls_msg_n;
}

/***************************************************************
* 1�ԥ⡼�ɤǥ�å������Υ���ɽ��
* long n : ɽ�����Ϲ�
***************************************************************/

void	draw_ls_msg( long n )
{
	long	i;
	long	msg_n;

	flg_draw_menu = TRUE;

	wipe_all();

	for( i = 0; i < LS_MSG_DRAW_N; i++ ){
		if( n + i >= g_ls_msg_n ){
			print_str( WIN_MSG_DRAW_MIN_X,
					LS_MSG_DRAW_N - i - 1,
					MSG_FMT_MSG, WIN_MSG_DRAW_WIDTH,
					MSG_NULL );
		} else {
			msg_n = g_ls_msg_idx - (n + i);
			msg_n += LS_MSG_MAX_N;
			msg_n %= LS_MSG_MAX_N;

			curs_attrset_dir( &(g_ls_msg[msg_n].attr) );
			print_str( WIN_MSG_DRAW_MIN_X,
					LS_MSG_DRAW_N - i - 1,
					MSG_FMT_MSG, WIN_MSG_DRAW_WIDTH,
					MSG_NULL );
			print_str( WIN_MSG_DRAW_MIN_X,
					LS_MSG_DRAW_N - i - 1,
					MSG_FMT_MSG, WIN_MSG_DRAW_WIDTH,
					g_ls_msg[msg_n].msg );
			curs_attrset_dflt();
		}
	}

	print_str( SCREEN_MIN_X, WIN_MAP_DRAW_MAX_Y + 1,
			MSG_S, MSG_H_FRAME );
}

/***************************************************************
* ���߹Ԥ���λ���Կ����Υ�å��������ǡ������֤�
* long idx : ����Կ�
* return : ��å��������ǡ���
***************************************************************/

ls_msg_t	*get_ls_msg( long idx )
{
	long	n;

	if( idx < 0 )
		return NULL;
	if( idx > (g_ls_msg_n - 1) )
		return NULL;

	n = (g_ls_msg_idx - idx + LS_MSG_MAX_N) % LS_MSG_MAX_N;

	return( &(g_ls_msg[n]) );
}

/***************************************************************
* ��å������Υ�������ԤΥ���ǥå������ͤ�ä���
* long add : �ä���Կ�
* return : �ä�����Υ���ǥå���
***************************************************************/

long	add_scroll_msg_idx( long add )
{
	long	max_n;

	g_scroll_msg_idx += add;

	max_n = get_ls_msg_idx();
	if( g_scroll_msg_idx < 0 )
		g_scroll_msg_idx = 0;
	if( g_scroll_msg_idx > max_n )
		g_scroll_msg_idx = max_n;

	return g_scroll_msg_idx;
}

/***************************************************************
* ���ơ��������С���ɽ��
***************************************************************/

void	draw_stat_bar( void )
{
	pos_t	*crsr;
	long	scrn_x, scrn_y, scrn_w;
	const char	*s;

	call_gui_map_print_stat_bar_hint();

	crsr = get_main_crsr();

	scrn_x = 0;
	scrn_y = get_screen_row() - 1;
	scrn_w = get_stat_bar_col() - scrn_x;

	if( get_flg_stat_bar_hint_obj() ){
		print_str( scrn_x, scrn_y, "%*s", scrn_w, " " );

		s = get_str_map_hint_obj( crsr->x, crsr->y );
		if( (s != NULL) && (s[0] != '\0') )
			print_str( scrn_x, scrn_y, "%s", s );

		scrn_y--;
	}

	if( get_flg_stat_bar_hint_chr() ){
		print_str( scrn_x, scrn_y, "%*s", scrn_w, " " );

		s = get_str_map_hint_chr( crsr->x, crsr->y );
		if( (s != NULL) && (s[0] != '\0') )
			print_str( scrn_x, scrn_y, "%s", s );

		scrn_y--;
	}
}

/***************************************************************
* ���ơ��������С��ιԿ����֤�
* return : �Կ�
***************************************************************/

long	calc_stat_bar_line_n( void )
{
	long	n;

	n = 0;
	if( get_flg_stat_bar_hint_chr() )
		n++;
	if( get_flg_stat_bar_hint_obj() )
		n++;

	return n;
}

/***************************************************************
* ���ơ��������С��˥���饯���Υҥ�Ȥ�ɽ�����뤫?
* return : ɽ�����뤫?
***************************************************************/

bool_t	get_flg_stat_bar_hint_chr( void )
{
	return g_flg_stat_bar_hint_chr;
}

/***************************************************************
* ���ơ��������С��˥���饯���Υҥ�Ȥ�ɽ�����뤫������
* bool_t flg : ɽ�����뤫?
***************************************************************/

void	set_flg_stat_bar_hint_chr( bool_t flg )
{
	g_flg_stat_bar_hint_chr = flg;
}

/***************************************************************
* ���ơ��������С��˥��֥������ȤΥҥ�Ȥ�ɽ�����뤫?
* return : ɽ�����뤫?
***************************************************************/

bool_t	get_flg_stat_bar_hint_obj( void )
{
	return g_flg_stat_bar_hint_obj;
}

/***************************************************************
* ���ơ��������С��˥��֥������ȤΥҥ�Ȥ�ɽ�����뤫������
* bool_t flg : ɽ�����뤫?
***************************************************************/

void	set_flg_stat_bar_hint_obj( bool_t flg )
{
	g_flg_stat_bar_hint_obj = flg;
}

/***************************************************************
* ʸ���������
* long scrn_x : ��
* long scrn_y : ��
* const char *s : �ե����ޥå�
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	print_str( long scrn_x, long scrn_y, const char *s, ... )
{
	va_list	argptr;
	static char	buf[PRINT_BUF_SIZ + 1];

	va_start( argptr, s );
	vsn_printf( buf, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	/* ����åԥ� */

	if( scrn_x < SCREEN_MIN_X )
		return;
	if( scrn_y < SCREEN_MIN_Y )
		return;
	if( scrn_x > get_screen_col() - 1 )
		return;
	if( scrn_y > get_screen_row() - 1 )
		return;

	/* RedHat 8, 9 �λ���ɬ�� */
	curs_move( 0, 0 );
	curs_refresh();

	/* ���� */

	curs_move( scrn_y, scrn_x );
	curs_printw( MSG_S, buf );
	curs_refresh();
}

/***************************************************************
* vfx ��ʸ���������
* bool_t flg_gui : GUI �����褹�뤫?
* long scrn_x : ��
* long scrn_y : ��
* const char *s : �ե����ޥå�
* ... : �ե����ޥåȤΰ���
* return : �����ϰ�����ä���?
***************************************************************/

bool_t	print_vfx(
	bool_t flg_gui, long scrn_x, long scrn_y, const char *s, ...
)
{
	va_list	argptr;
	static char	buf[PRINT_BUF_SIZ + 1];
	bool_t	flg_draw;
	dun_t	*dun;
	curs_attr_t	attr;
	long	len;
	long	x, y;
	long	i;

	va_start( argptr, s );
	vsn_printf( buf, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	dun = get_dun();
	attr = get_current_attr();

	if( g_flg_cui )
		print_vfx_cui( flg_gui, scrn_x, scrn_y, MSG_S, buf );
	if( g_flg_gui && flg_gui )
		call_pcg_dun_draw_string( scrn_x, scrn_y, MSG_S, buf );

	flg_draw = FALSE;

	len = str_len_draw( buf );
	x = scrn_x + (map_draw_pos.x * 2);
	y = scrn_y + map_draw_pos.y;
	for( i = 0; i < len; i++ ){
		if( !g_flg_gui || !flg_gui )
			break;

		if( clip_draw_pos( (x + i) / 2, y ) ){
			dun->map.vfx[y][x + i] = buf[i];
			dun->map.attr_vfx[y][x + i] = attr;

			flg_draw = TRUE;
		}
	}

	if( g_flg_gui )
		call_pcg_dun_draw( x / 2, y, (len + 1) / 2, 1, TRUE );

	return flg_draw;
}

/***************************************************************
* vfx ��ʸ��������� (CUI)
* bool_t flg_gui : GUI �����褹�뤫?
* long scrn_x : ��
* long scrn_y : ��
* const char *s : �ե����ޥå�
* ... : �ե����ޥåȤΰ���
* return : �����ϰ�����ä���?
***************************************************************/

bool_t	print_vfx_cui(
	bool_t flg_gui, long scrn_x, long scrn_y, const char *s, ...
)
{
	va_list	argptr;
	static char	buf[PRINT_BUF_SIZ + 1];
	bool_t	flg_draw;
	long	i;

	va_start( argptr, s );
	vsn_printf( buf, PRINT_BUF_SIZ, s, argptr );
	va_end( argptr );

	flg_draw = FALSE;

	if( scrn_y < WIN_MAP_DRAW_MIN_Y )
		return FALSE;
	if( scrn_y > get_map_row() - 1 )
		return FALSE;

	for( i = 0; buf[i] != '\0'; i++ ){
		long	x;

		x = scrn_x + i;
		if( x < WIN_MAP_DRAW_MIN_X )
			continue;
		if( x > get_map_col() - 1 )
			break;

		print_str( x, scrn_y, "%c", buf[i] );
		flg_draw = TRUE;
	}

	return flg_draw;
}

/***************************************************************
* �ޥåפ� vfx �򥯥ꥢ
* long map_x : X��ɸ
* long map_y : Y��ɸ
* long dx : ��
* long dy : �⤵
***************************************************************/

void	wipe_vfx( long map_x, long map_y, long dx, long dy )
{
	long	x, y;
	dun_t	*dun;

	dun = get_dun();

	for( y = map_y; y < map_y + dy; y++ ){
		if( !clip_y( y ) )
			continue;
		for( x = map_x; x < map_x + dx; x++ ){
			if( !clip_x( x ) )
				continue;

			dun->map.vfx[y][x * 2 + 0] = MAP_VFX_NULL;
			dun->map.vfx[y][x * 2 + 1] = MAP_VFX_NULL;
		}
	}
}

/***************************************************************
* �西���󡢲��̤�����褹�뤫����
* bool_t flg : �⡼��
* return : ���ߤΥ⡼��
***************************************************************/

bool_t	set_redraw_every_turn( bool_t flg )
{
	flg_redraw_every_turn = flg;

	return flg_redraw_every_turn;
}

/***************************************************************
* �西���󡢲��̤�����褹�뤫?
* return : ���ߤΥ⡼��
***************************************************************/

bool_t	chk_redraw_every_turn( void )
{
	return flg_redraw_every_turn;
}

/***************************************************************
* ���̤򥯥ꥢ
***************************************************************/

void	wipe_all( void )
{
	curs_clear();
	curs_refresh();
}

/***************************************************************
* ���̤������
***************************************************************/

void	redraw_all( void )
{
	wipe_all();

	redraw_map();
	draw_all_mbr_stat();
	redraw_msg();
	draw_stat_bar();

	/* �ޥ����Υϥ�ɥ��ꥻ�å� */
	call_cui_mouse_reset_handler_tab();
	/* �ޥ����Υϥ�ɥ������ */
	set_cui_mouse_add_handler_map();
	set_cui_mouse_add_handler_msg();
	set_cui_mouse_add_handler_stat();
}

/***************************************************************
* �ޥåפΥޥ������ϥ�ɥ����Ͽ
***************************************************************/

void	set_cui_mouse_add_handler_map( void )
{
	long	mouse_x, mouse_y, mouse_w, mouse_h;

	mouse_x = WIN_MAP_DRAW_MIN_X;
	mouse_y = WIN_MAP_DRAW_MIN_Y;
	mouse_w = get_map_col() + 1;
	mouse_h = get_map_row() + 1;
	call_cui_mouse_add_handler(
			TRUE,
			mouse_x, mouse_y, mouse_w, mouse_h,
			NULL,
			NULL,
			cb_cui_mouse_scroll_map,
			0, "" );
}

/***************************************************************
* ��å������Υޥ������ϥ�ɥ����Ͽ
***************************************************************/

void	set_cui_mouse_add_handler_msg( void )
{
	long	mouse_x, mouse_y, mouse_w, mouse_h;

	mouse_x = WIN_MSG_DRAW_MIN_X;
	mouse_y = get_map_row() + 1;
	mouse_w = get_screen_col() - mouse_x;
	mouse_h = get_message_row();
	call_cui_mouse_add_handler(
			TRUE,
			mouse_x, mouse_y, mouse_w, mouse_h,
			NULL,
			NULL,
			cb_cui_mouse_scroll_msg,
			0, "" );
}

/***************************************************************
* ���ơ������Υޥ������ϥ�ɥ����Ͽ
***************************************************************/

void	set_cui_mouse_add_handler_stat( void )
{
	party_t	*pty;
	pet_t	**pet;
	long	mouse_x, mouse_y, mouse_w, mouse_h;
	long	i;

	pty = get_party();
	pet = get_party_pet();

	switch( get_stat_mode() ){
	case STAT_MODE_MAX_N:
	case STAT_MODE_MBR:
		for( i = 0; i < MBR_MAX_N; i++ ){
			if( pty->mbr[i]->mbr_n == MBR_N_NOT_JOIN )
				continue;
			if( chk_flg( pty->mbr[i]->stat,
					FLG_STAT_NOT_EXIST ) ){
				continue;
			}

			set_cui_mouse_add_handler_mbr_stat( i );
		}
		break;
	case STAT_MODE_PET:
		for( i = 0; i < PET_MAX_N; i++ ){
			if( pet[i] == NULL )
				continue;

			set_cui_mouse_add_handler_mbr_stat(
					MBR_MAX_N + i );
		}
		break;
	}

	/* ���ơ��������⡼�ɤ��ڤ괹�� */

	mouse_x = WIN_STAT_DRAW_MIN_X;
	mouse_y = WIN_STAT_DRAW_MIN_Y + (MBR_MAX_N * WIN_STAT_DRAW_HEIGHT);
	mouse_w = WIN_STAT_DRAW_WIDTH;
	mouse_h = WIN_STAT_DRAW_HEIGHT - 1;

	call_cui_mouse_add_handler(
			TRUE,
			mouse_x, mouse_y, mouse_w, mouse_h,
			cb_cui_mouse_point_dummy,
			cb_cui_mouse_click_switch_stat,
			NULL,
			0, NULL );

	mouse_x = WIN_STAT_DRAW_MIN_X;
	mouse_y = WIN_STAT_DRAW_MIN_Y;;
	mouse_w = WIN_STAT_DRAW_WIDTH;
	mouse_h = (MBR_MAX_N + 1) * WIN_STAT_DRAW_HEIGHT;

	call_cui_mouse_add_handler(
			TRUE,
			mouse_x, mouse_y, mouse_w, mouse_h,
			cb_cui_mouse_point_dummy,
			cb_cui_mouse_click_switch_stat,
			NULL,
			2, NULL );
}

/***************************************************************
* ���С��Υ��ơ������Υޥ������ϥ�ɥ����Ͽ
* long mbr_n : ���С��ֹ�
***************************************************************/

void	set_cui_mouse_add_handler_mbr_stat( long mbr_n )
{
	long	n;
	long	x, y, w, h;
	char	macro[MACRO_MAX_LEN + 1];

	if( mbr_n < MBR_MAX_N )
		n = mbr_n;
	else
		n = mbr_n - MBR_MAX_N;

	/* ̾�� */

	sn_printf( macro, MACRO_MAX_LEN,
			"00000000000000000000"
			":/misc/cursor/cursor/move member\n"
			"%c"
			"0"
			"^M"
			, (char)('A' + mbr_n) );
	x = WIN_STAT_DRAW_MIN_X + WIN_STAT_NAME_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + WIN_STAT_NAME_DRAW_MIN_Y
			+ (n * WIN_STAT_DRAW_HEIGHT);
	w = WIN_STAT_NAME_DRAW_WIDTH;
	h = 1;

	call_cui_mouse_add_handler(
			TRUE,
			x, y, w, h,
			cb_cui_mouse_point_dummy,
			cb_cui_mouse_click_stat,
			NULL,
			mbr_n, macro );

	/* ���� */

	sn_printf( macro, MACRO_MAX_LEN,
			"00000000000000000000"
			":/misc/cursor/cursor/move member\n"
			"%c"
			"0"
			"C"
			, (char)('A' + mbr_n) );
	x = WIN_STAT_DRAW_MIN_X + WIN_STAT_COND_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + WIN_STAT_COND_DRAW_MIN_Y
			+ (n * WIN_STAT_DRAW_HEIGHT);
	w = WIN_STAT_COND_DRAW_WIDTH;
	h = 1;

	call_cui_mouse_add_handler(
			TRUE,
			x, y, w, h,
			cb_cui_mouse_point_dummy,
			cb_cui_mouse_click_stat,
			NULL,
			mbr_n, macro );

	/* HP/MP */

	sn_printf( macro, MACRO_MAX_LEN,
			"00000000000000000000"
			":/misc/cursor/cursor/move member\n"
			"%c"
			"0"
			"C"
			, (char)('A' + mbr_n) );
	x = WIN_STAT_DRAW_MIN_X + WIN_STAT_HP_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + WIN_STAT_HP_DRAW_MIN_Y
			+ (n * WIN_STAT_DRAW_HEIGHT);
	w = WIN_STAT_HP_DRAW_WIDTH;
	h = 1;

	call_cui_mouse_add_handler(
			TRUE,
			x, y, w, h,
			cb_cui_mouse_point_dummy,
			cb_cui_mouse_click_stat,
			NULL,
			mbr_n, macro );
}

/***************************************************************
* �ޥåפ�����
* long map_x : X��ɸ
* long map_y : Y��ɸ
* long dx : ��
* long dy : �⤵
***************************************************************/

void	draw_map( long map_x, long map_y, long dx, long dy )
{
	draw_map_sub( map_x, map_y, dx, dy, FALSE );
}

/***************************************************************
* �ޥåפ����� (GUI �ξ����������)
* long map_x : X��ɸ
* long map_y : Y��ɸ
* long dx : ��
* long dy : �⤵
***************************************************************/

void	draw_map_force( long map_x, long map_y, long dx, long dy )
{
	draw_map_sub( map_x, map_y, dx, dy, TRUE );
}

/***************************************************************
* �ޥåפ����������
* long map_x : X��ɸ
* long map_y : Y��ɸ
* long dx : ��
* long dy : �⤵
* bool_t flgForce : ��������
***************************************************************/

void	draw_map_sub(
	long map_x, long map_y,
	long dx, long dy,
	bool_t flgForce
)
{
	dun_t	*dun;
	long	i, j;
	long	mjr, mnr;
	long	scrn_x, scrn_y, pre_scrn_x;
	long	xx, yy;

	dun = get_dun();

	if( dx < 1 )
		dx = 1;
	if( dy < 1 )
		dy = 1;

#if	0
	/* RedHat 8, 9 �λ�ɬ�� */
	dx += 2;
	dy += 0;
#endif

	wipe_vfx( map_x, map_y, dx, dy );
	set_map_total( map_x, map_y, dx, dy );

	if( g_flg_gui )
		call_pcg_dun_draw( map_x, map_y, dx, dy, flgForce );
	if( !g_flg_cui )
		return;

	for( i = 0; i < dy; i++ ){
		yy = map_y + i;
		if( !clip_y( yy ) )
			continue;

		pre_scrn_x = -128;
		for( j = 0; j < dx; j++ ){
			xx = map_x + j;
			if( !clip_x( xx ) )
				continue;

			/* ����åԥ� */

			scrn_x = (xx - map_draw_pos.x) * 2;
			scrn_y = (yy - map_draw_pos.y);
			if( scrn_y < WIN_MAP_DRAW_MIN_Y )
				break;
			if( scrn_y > get_map_row() - 1 )
				break;
			if( scrn_x < WIN_MAP_DRAW_MIN_X )
				continue;
			if( scrn_x > get_map_col() - 1 )
				break;
			if( (scrn_x - 2) != pre_scrn_x )
				curs_move( scrn_y, scrn_x );

			/* �ޥåפ˥̥�ʸ����ͭ�ä������ˤ��� */

			mjr = dun->map.total.mjr[yy][xx];
			mnr = dun->map.total.mnr[yy][xx];
			if( mjr == '\0' )
				mjr = FACE_MJR_NULL;
			if( mnr == '\0' )
				mnr = FACE_MNR_NULL;

			/* ���� */

			curs_attrset_dir( &(dun->map.attr[yy][xx]) );
			curs_printw( "%c%c", (char)mjr, (char)mnr );

			pre_scrn_x = scrn_x;
		}
	}

	curs_attrset_dflt();

	curs_refresh();
}

/***************************************************************
* �ޥåפ������
***************************************************************/

void	redraw_map( void )
{
	redraw_map_sub( FALSE );
}

/***************************************************************
* �ޥåפ������ (GUI �ξ����������)
***************************************************************/

void	redraw_map_force( void )
{
	redraw_map_sub( TRUE );
}

/***************************************************************
* �ޥåפκ����������
***************************************************************/

void	redraw_map_sub( bool_t flgForce )
{
	pos_t	*draw;
	long	x, y;

	sort_all_chr( FALSE );

	wipe_vfx( 0, 0, MAP_MAX_X, MAP_MAX_Y );
	set_map_total( 0, 0, MAP_MAX_X, MAP_MAX_Y );

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	if( g_flg_gui )
		call_pcg_dun_redraw( TRUE );
	if( !g_flg_cui )
		return;

	/* �ޥåפ������ */

	draw_map( draw->x, draw->y, get_map_col() / 2, get_map_row() );

	/* ��ľ�����Υ�����ɥ��Ȥ����� */

	x = get_map_col();
	y = WIN_MAP_DRAW_MIN_Y;

	for( ; y < get_map_row(); y++ ){
		curs_move( y, x );
		curs_printw( MSG_S, MSG_V_LINE );
	}

	/* ��ʿ�����Υ�����ɥ��Ȥ����� */

	if( get_flg_play_replay() ){
		draw_replay( TRUE );
	} else {
		x = WIN_MAP_DRAW_MIN_X;
		y = get_map_row();

		curs_move( y, x );
		for( ; x < get_map_col(); x++ ){
			curs_printw( MSG_S, MSG_H_LINE );
		}
		curs_printw( MSG_S, MSG_CROSS );
	}

	curs_refresh();
	update_crsr();
}

/***************************************************************
* �ޥåפ�õ�
***************************************************************/

void	wipe_map( void )
{
	long	i;

	for( i = WIN_MAP_DRAW_MIN_Y; i < get_map_row(); i++ ){
		curs_move( i, WIN_MAP_DRAW_MIN_X );
		curs_printw( "%*s", get_map_col(), " " );
	}

	curs_refresh();
}

/***************************************************************
* �ޥåפ�õ�Ƥ��������
***************************************************************/

void	force_clr_redraw_map( void )
{
	pos_t	*draw;
	long	i;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	for( i = 0; i < get_map_row(); i++ ){
		curs_move( WIN_MAP_DRAW_MIN_Y + i, WIN_MAP_DRAW_MIN_X );
		curs_printw( "%*s", get_map_col(), " " );
		curs_refresh();

		draw_map_force( draw->x, draw->y + i,
				get_map_col() / 2, 1 );
		curs_refresh();
	}
}

/***************************************************************
* �ޥåפΥۥ�����Υޥ������ϥ�ɥ�
* long scroll_dir : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_scroll_map(
	long scroll_dir, long n, const char *macro
)
{
	switch( scroll_dir ){
	case 0:
		set_key_buf_str_tail( ":/misc/cursor/cursor/scroll/"
				"west\n" );
		set_key_buf_char_tail( CMD_KEY_IDLE );
		return TRUE;
	case 1:
		set_key_buf_str_tail( ":/misc/cursor/cursor/scroll/"
				"east\n" );
		set_key_buf_char_tail( CMD_KEY_IDLE );
		return TRUE;
	case 2:
		set_key_buf_str_tail( ":/misc/cursor/cursor/scroll/"
				"north\n" );
		set_key_buf_char_tail( CMD_KEY_IDLE );
		return TRUE;
	case 3:
		set_key_buf_str_tail( ":/misc/cursor/cursor/scroll/"
				"south\n" );
		set_key_buf_char_tail( CMD_KEY_IDLE );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ��å������Υۥ�����Υޥ������ϥ�ɥ�
* long scroll_dir : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_scroll_msg(
	long scroll_dir, long n, const char *macro
)
{
	switch( scroll_dir ){
	case 0:
	case 1:
		break;
	case 2:
		if( chk_msg_mul_line() ){
			set_key_buf_str_tail(
					":/misc/info/message/prev\n" );
			set_key_buf_char_tail( CMD_KEY_IDLE );
		} else {
			scroll_1_msg( -1 );
		}
		return TRUE;
	case 3:
		if( chk_msg_mul_line() ){
			set_key_buf_str_tail(
					":/misc/info/message/next\n" );
			set_key_buf_char_tail( CMD_KEY_IDLE );
		} else {
			scroll_1_msg( +1 );
		}
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ���С�����������
***************************************************************/

void	draw_party( void )
{
	party_t	*pty;
	long	i;

	pty = get_party();

	for( i = 0; i < MBR_MAX_N; i++ )
		draw_mbr( pty->mbr[i] );

	draw_square();
}

/***************************************************************
* ���С�������
* mbr_t *p : ���С�
***************************************************************/

void	draw_mbr( mbr_t *p )
{
	draw_chr( p );
}

/***************************************************************
* ���󥫡�������
***************************************************************/

void	draw_square( void )
{
	square_t	*sq;
	long	x, y;
	long	i;

	sq = get_square_mbr();

	/* �ѡ��ƥ������󥫡������� */

	if( clip_pos( sq->pre_x, sq->pre_y ) ){
		x = sq->pre_x - (SQUARE_WIDTH / 2);
		y = sq->pre_y - (SQUARE_HEIGHT / 2);
		draw_map_force( x, y, SQUARE_WIDTH, SQUARE_HEIGHT );
	}
	if( clip_pos( sq->x, sq->y ) ){
		x = sq->x - (SQUARE_WIDTH / 2);
		y = sq->y - (SQUARE_HEIGHT / 2);
		draw_map_force( x, y, SQUARE_WIDTH, SQUARE_HEIGHT );
	}

	/* ���С������󥫡������� */

	for( i = 0; i < MBR_MAX_N; i++ ){
		draw_map_force( sq->chr_pre_pos[i].x,
				sq->chr_pre_pos[i].y, 1, 1 );
		draw_map_force( sq->chr_map_pos[i].x,
				sq->chr_map_pos[i].y, 1, 1 );

		sq->chr_pre_pos[i].x = sq->chr_map_pos[i].x;
		sq->chr_pre_pos[i].y = sq->chr_map_pos[i].y;
	}
}

/***************************************************************
* ���ƤΥ�󥹥���������
***************************************************************/

void	draw_all_mnstr( void )
{
	mnstr_t	*head, *p, *pp;

	head = get_mnstr_used();
	for( p = head->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == head )
			break;

		draw_mnstr( pp );
	}
}

/***************************************************************
* ��󥹥���������
* mnstr_t *p : ��󥹥���
***************************************************************/

void	draw_mnstr( mnstr_t *p )
{
	draw_chr( p );
}

/***************************************************************
* ���ƤΥڥåȤ�����
***************************************************************/

void	draw_all_pet( void )
{
	pet_t	**pet = get_party_pet();
	long	i;

	for( i = 0; i < PET_MAX_N; i++ )
		draw_pet( pet[i] );
}

/***************************************************************
* �ڥåȤ�����
* pet_t *p : �ڥå�
***************************************************************/

void	draw_pet( pet_t *p )
{
	draw_mnstr( p );
}

/***************************************************************
* ����饯��������
* chr_t *chr : ����饯��
***************************************************************/

void	draw_chr( chr_t *chr )
{
	long	bx, by;
	long	ex, ey;
	long	bx2, by2;
	long	ex2, ey2;
#if	USE_FLG_UPDATE_CHR
	long	x, y;
	bool_t	flg_update;
#endif	/* USE_FLG_UPDATE_CHR */

	if( chr == NULL )
		return;

	if( clip_pos( chr->pre_draw_x, chr->pre_draw_y ) ){
		bx = get_chr_left( chr->pre_draw_x, chr->dx ) - 1;
		ex = get_chr_right( chr->pre_draw_x, chr->dx ) + 1;
		by = get_chr_top( chr->pre_draw_y, chr->dy ) - 1;
		ey = get_chr_bottom( chr->pre_draw_y, chr->dy ) + 1;

		if( g_flg_gui ){
			bool_t	flg_pre = TRUE;

			bx2 = call_pcg_dun_get_chr_draw_left(
					chr, flg_pre );
			ex2 = call_pcg_dun_get_chr_draw_right(
					chr, flg_pre );
			by2 = call_pcg_dun_get_chr_draw_top(
					chr, flg_pre );
			ey2 = call_pcg_dun_get_chr_draw_bottom(
					chr, flg_pre );

			if( clip_pos( bx2, by2 ) && clip_pos( ex2, ey2 ) ){
				bx = min_l( bx, bx2 );
				by = min_l( by, by2 );
				ex = max_l( ex, ex2 );
				ey = max_l( ey, ey2 );
			}
		}

#if	USE_FLG_UPDATE_CHR
		flg_update = FALSE;
		for( y = by; y <= ey; y++ ){
			for( x = bx; x <= ex; x++ ){
				if( get_flg_update_chr( x, y ) ){
					flg_update = TRUE;
					break;
				}
			}
		}
		if( flg_update ){
			draw_map( bx, by, ex - bx + 1, ey - by + 1 );

			for( y = by; y <= ey; y++ ){
				for( x = bx; x <= ex; x++ ){
					set_flg_update_chr( x, y, FALSE );
				}
			}
		}
#else	/* USE_FLG_UPDATE_CHR */
		draw_map( bx, by, ex - bx + 1, ey - by + 1 );
#endif	/* USE_FLG_UPDATE_CHR */
	}

	chr->pre_draw_x = chr->x;
	chr->pre_draw_y = chr->y;

	if( chr->kind == CHR_KIND_MNSTR )
		if( !chk_flg( chr->flg_map, FLG_MAP_CHR_FIND ) )
			return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	if( clip_pos( chr->x, chr->y ) ){
		bx = get_chr_left( chr->x, chr->dx ) - 1;
		ex = get_chr_right( chr->x, chr->dx ) + 1;
		by = get_chr_top( chr->y, chr->dy ) - 1;
		ey = get_chr_bottom( chr->y, chr->dy ) + 1;

		if( g_flg_gui ){
			bool_t	flg_pre = FALSE;

			bx2 = call_pcg_dun_get_chr_draw_left(
					chr, flg_pre );
			ex2 = call_pcg_dun_get_chr_draw_right(
					chr, flg_pre );
			by2 = call_pcg_dun_get_chr_draw_top(
					chr, flg_pre );
			ey2 = call_pcg_dun_get_chr_draw_bottom(
					chr, flg_pre );

			if( clip_pos( bx2, by2 ) && clip_pos( ex2, ey2 ) ){
				bx = min_l( bx, bx2 );
				by = min_l( by, by2 );
				ex = max_l( ex, ex2 );
				ey = max_l( ey, ey2 );
			}
		}

#if	USE_FLG_UPDATE_CHR
		flg_update = FALSE;
		for( y = by; y <= ey; y++ ){
			for( x = bx; x <= ex; x++ ){
				if( get_flg_update_chr( x, y ) ){
					flg_update = TRUE;
					break;
				}
			}
		}
		if( flg_update ){
			draw_map( bx, by, ex - bx + 1, ey - by + 1 );

			for( y = by; y <= ey; y++ ){
				for( x = bx; x <= ex; x++ ){
					set_flg_update_chr( x, y, FALSE );
				}
			}
		}
#else	/* USE_FLG_UPDATE_CHR */
		draw_map( bx, by, ex - bx + 1, ey - by + 1 );
#endif	/* USE_FLG_UPDATE_CHR */
	}
}

/***************************************************************
* ����饯���κ�����ե饰������
* long mapX : X ��ɸ
* long mapY : Y ��ɸ
* bool_t flg : �����褹��ɬ�פ����뤫��
***************************************************************/

void	set_flg_update_chr( long mapX, long mapY, bool_t flg )
{
	if( !clip_pos( mapX, mapY ) )
		return;

	if( flg )
		g_flg_update_chr[mapY][mapX] = -1;
	else
		g_flg_update_chr[mapY][mapX] = get_turn();
}

/***************************************************************
* ����饯���κ�����ե饰�μ���
* long mapX : X ��ɸ
* long mapY : Y ��ɸ
* return : �����褹��ɬ�פ����뤫��
***************************************************************/

bool_t	get_flg_update_chr( long mapX, long mapY )
{
	if( !clip_pos( mapX, mapY ) )
		return FALSE;

	return( g_flg_update_chr[mapY][mapX] != get_turn() );
}

/***************************************************************
* �ɥ�������
* long dr_n : �ɥ��ֹ�
***************************************************************/

void	draw_door( long dr_n )
{
	dun_t	*dun;

	dun = get_dun();

	draw_map( dun->door[dr_n].x, dun->door[dr_n].y,
			dun->door[dr_n].dx, dun->door[dr_n].dy );
}

/***************************************************************
* �����ƥ������
* item_t *p : �����ƥ�
***************************************************************/

void	draw_item( item_t *p )
{
	draw_map( p->x, p->y, 1, 1 );
}

/***************************************************************
* 櫤�����
* trap_t *p : �
***************************************************************/

void	draw_trap( trap_t *p )
{
	draw_map( p->x, p->y, 1, 1 );
}

/***************************************************************
* ��˥塼������
* draw_menu_t *data : ��˥塼������ǡ���
***************************************************************/

void	draw_menu( draw_menu_t *data )
{
	long	x, y;
	long	short_cut_x;
	long	height, width;
	long	width_contents, width_short;
	long	len_ttl, len_chk, len_direct, len_v_line, len_line;
	long	len_head_corner, len_foot_corner;
	long	len_foot_left, len_foot;
	long	len_page;
	long	len_open_win, len_branch;
	const long	len_shadow = 2;
	static char	str_contents[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	static char	str_head[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	static char	str_foot[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	static char	str_page[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	char	*str_foot_left, *str_foot_right;
	static char	str_short[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	static char	str_direct[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;
	char	*str_chk, *str_open_win, *str_branch;
	bool_t	flg_use_on_off;
	bool_t	flg_foot_left_rev, flg_foot_right_rev;
	long	mouse_x, mouse_y, mouse_w, mouse_h;
	char	mouse_macro[1 + 1];
	long	i;

	if( data == NULL )
		return;

	flg_draw_menu = TRUE;

	/* Ϣ³�¹Ԥ���� */
	clr_continue_exec_mode();

	if( g_flg_gui )
		call_gui_menu_draw( data );
	if( !g_flg_cui )
		return;

	/* �ޥ����Υϥ�ɥ��ꥻ�å� */

	if( data->flg_redraw && (data->sel_n > -1) )
		call_cui_mouse_reset_handler_tab();

	g_cui_mouse_menu_sel_n = data->sel_n;

	/* ������ɥ������ȹ⤵���Ȥ�� */

	sn_printf( str_direct, max_len,
			MSG_MENU_ACCEL_KEY_FMT, 'A' );
	len_direct = str_len_draw( str_direct );
	len_chk = max_l( str_len_draw( MSG_MENU_FLG_LS_CHK_ON ),
			str_len_draw( MSG_MENU_FLG_LS_CHK_OFF ) );
	len_v_line = str_len_draw( MSG_MENU_V_LINE );
	len_head_corner = str_len_draw( MSG_MENU_CORNER ) * 2;
	len_foot_corner = str_len_draw( MSG_MENU_LEFT_PREV )
			+ str_len_draw( MSG_MENU_RIGHT_NEXT );
	if( data->ttl == NULL )
		len_ttl = 0;
	else
		len_ttl = str_len_draw( data->ttl );

	len_open_win = 0;
	len_branch = 0;
	width_contents = 0;
	width_short = 0;
	height = 0;
	flg_use_on_off = FALSE;
	for( i = 0; i < MENU_MAX_N_PER_PAGE; i++ ){
		long	len, len_open_win_tmp;

		if( data->ls[i] == NULL )
			break;

		len_open_win_tmp = 0;

		if( strcmp( data->ls[i]->kind, "<CheckItem>" ) == 0 ){
			flg_use_on_off = TRUE;
		} else if( strcmp( data->ls[i]->kind, "<RadioItem>" ) == 0 ){
			flg_use_on_off = TRUE;
		} else if( strcmp( data->ls[i]->kind, "<Branch>" ) == 0 ){
			len_branch = str_len_draw( MSG_MENU_KIND_BRANCH );
		} else if( strcmp( data->ls[i]->kind,
				"<OpenWinItem>" ) == 0 ){
			len_open_win = str_len_draw(
					MSG_MENU_KIND_OPEN_WIN_ITEM );
			len_open_win_tmp = len_open_win;
		}

		len = str_len_draw( data->ls[i]->msg );
		len += len_open_win_tmp;
		width_contents = max_l( width_contents, len );

		if( data->ls[i]->short_key[0] != '\0' ){
			sn_printf( str_short, max_len,
					MSG_MENU_SHORT_CUT_KEY_FMT,
					data->ls[i]->short_key );
			len = str_len_draw( str_short );
			width_short = max_l( width_short, len );
		}

		height++;
	}
	if( !flg_use_on_off )
		len_chk = 0;

	width = max_l( len_head_corner, len_foot_corner );
	width -= (len_v_line * 2) + 2;
	width = max_l( width, width_contents + width_short + len_branch );
	width = max_l( width, len_ttl );

	width_contents = width - width_short - len_branch;

	/* ���� */

	str_nz_cpy( str_head, MSG_MENU_CORNER, max_len );

	if( data->ttl != NULL ){
		str_max_n_cat( str_head, data->ttl, max_len );
		len_ttl = str_len_draw( data->ttl );
	}

	strncat( str_head, MSG_MENU_FRAME,
			len_chk + len_direct + 2
			+ width - len_ttl );

	str_max_n_cat( str_head, MSG_MENU_CORNER, max_len );


	/* �ڡ����� */

	sn_printf( str_page, max_len, MSG_MENU_PAGE_FMT,
			data->page_sel_n + 1, data->page_max_n );
	len_page = str_len_draw( str_page );

	/* ���� */

	len_foot = len_chk + len_direct + 2 + (len_v_line * 2)
			+ width - len_foot_corner - len_page;
	if( len_foot > 0 ){
		str_nz_cpy( str_foot, MSG_MENU_FRAME, len_foot );
		str_foot[len_foot] = '\0';	/* ���Τ�ɬ�� */
	} else {
		str_foot[0] = '\0';
	}

	if( data->flg_min_page ){
		str_foot_left = MSG_MENU_LEFT;
		flg_foot_left_rev = FALSE;
	} else {
		str_foot_left = MSG_MENU_LEFT_PREV;
		flg_foot_left_rev = TRUE;
	}
	len_foot_left = str_len_draw( str_foot_left );

	if( data->flg_max_page ){
		str_foot_right = MSG_MENU_RIGHT;
		flg_foot_right_rev = FALSE;
	} else {
		str_foot_right = MSG_MENU_RIGHT_NEXT;
		flg_foot_right_rev = TRUE;
	}

#if	(! FLG_MENU_PAGE_ATTR_REV)
	flg_foot_left_rev = FALSE;
	flg_foot_right_rev = FALSE;
#endif	/* FLG_MENU_PAGE_ATTR_REV */

	/* ���� */

	len_line = width + len_chk + len_direct + (len_v_line * 2) + 2;

	x = WIN_MENU_DRAW_MIN_X;
	y = WIN_MENU_DRAW_MIN_Y;
	x += (WIN_MENU_DRAW_MAX_X - (width + len_chk + len_direct)) / 2;
	y += (WIN_MENU_DRAW_MAX_Y - height) / 2;
	if( x < WIN_MENU_DRAW_MIN_X )
		x = WIN_MENU_DRAW_MIN_X;
	if( y < WIN_MENU_DRAW_MIN_Y )
		y = WIN_MENU_DRAW_MIN_Y;

	/* ���դ����� */
	i = -1;
	print_str( x - len_v_line - len_shadow, y + i,
			MSG_MENU_CLR_FMT, len_line + len_shadow * 2, "" );

	curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
	print_str( x - len_v_line, y - 1, str_head );
	curs_attrset_dflt();

	for( i = 0; data->ls[i] != NULL; i++ ){
		if( !data->flg_redraw )
			if( (i != data->sel_n) && (i != data->prev_sel_n) )
				continue;

		/* ��������졼�������� */
		sn_printf( str_direct, max_len,
				MSG_MENU_ACCEL_KEY_FMT,
				data->ls[i]->accel_key );
		len_direct = str_len_draw( str_direct );

		/* ���硼�ȥ��åȡ����� */
		if( data->ls[i]->short_key[0] == '\0' ){
			str_short[0] = '\0';
		} else {
			sn_printf( str_short, max_len,
					MSG_MENU_SHORT_CUT_KEY_FMT,
					data->ls[i]->short_key );
		}

		/* �����å����ܥå��� */
		if( !flg_use_on_off )
			str_chk = MSG_NULL;
		else if( chk_flg( data->ls[i]->flg, FLG_MENU_CHK_ON ) )
			str_chk = MSG_MENU_FLG_LS_CHK_ON;
		else if( chk_flg( data->ls[i]->flg, FLG_MENU_CHK_OFF ) )
			str_chk = MSG_MENU_FLG_LS_CHK_OFF;
		else
			str_chk = MSG_MENU_FLG_LS_CHK_NULL;
		len_chk = str_len_draw( str_chk );

		/* <Branch> */
		if( strcmp( data->ls[i]->kind, "<Branch>" ) == 0 )
			str_branch = MSG_MENU_KIND_BRANCH;
		else
			str_branch = MSG_NULL;

		/* <OpenWinItem> */
		if( strcmp( data->ls[i]->kind, "<OpenWinItem>" ) == 0 )
			str_open_win = MSG_MENU_KIND_OPEN_WIN_ITEM;
		else
			str_open_win = MSG_NULL;
		len_open_win = str_len_draw( str_open_win );

		print_str( x - len_v_line - len_shadow, y + i,
				MSG_MENU_CLR_FMT,
				len_line + len_shadow * 2, "" );

		/* ��ü������ */
		curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
		print_str( x - len_v_line, y + i,
				MSG_MENU_V_LINE );
		curs_attrset_dflt();

		/* ���ܤ����� */
		sn_printf( str_contents, max_len,
				MSG_MENU_CONTENTS_FMT,
				data->ls[i]->msg,
				len_open_win, str_open_win );

		short_cut_x = x + 1 + len_chk + len_direct + width_contents;

		if( i == data->sel_n ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			print_str( x, y + i, "%*s",
					len_chk + len_direct + width + 2,
					" " );
			print_str( x, y + i,
					MSG_MENU_SELECT_FMT,
					str_chk, str_direct,
					width_contents, str_contents );
			print_str( short_cut_x, y + i,
					MSG_MENU_SELECT_SHORT_CUT_FMT,
					width_short, str_short,
					len_branch, str_branch );
		} else {
			curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
			print_str( x, y + i, "%*s",
					len_chk + len_direct + width + 2,
					" " );
			print_str( x, y + i,
					MSG_MENU_NOT_SELECT_FMT,
					str_chk, str_direct,
					width_contents, str_contents );
			print_str( short_cut_x, y + i,
					MSG_MENU_NOT_SELECT_SHORT_CUT_FMT,
					width_short, str_short,
					len_branch, str_branch );
		}
		curs_attrset_dflt();

		/* ��ü������ */
		curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
		print_str( x + len_chk + len_direct + width + 2, y + i,
				MSG_MENU_V_LINE );
		curs_attrset_dflt();

		/* �ޥ����Υϥ�ɥ������ */

		if( data->flg_redraw && (data->sel_n > -1) ){
			mouse_x = x;
			mouse_y = y + i;
			mouse_w = len_chk + len_direct + width + 2;
			mouse_h = 1;
			mouse_macro[0] = data->ls[i]->accel_key;
			mouse_macro[1] = '\0';

			call_cui_mouse_add_handler(
					TRUE,
					mouse_x, mouse_y, mouse_w, mouse_h,
					cb_cui_mouse_point_menu,
					cb_cui_mouse_click_menu,
					NULL,
					i, mouse_macro );
		}
	}

	/* ���դ����� */

	print_str( x - len_v_line - len_shadow, y + i,
			MSG_MENU_CLR_FMT, len_line + len_shadow * 2, "" );

	/* ���� */

	if( flg_foot_left_rev )
		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
	else
		curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
	print_str( x - len_v_line,
			y + i, str_foot_left );

	/* �ޥ����Υϥ�ɥ������ */

	mouse_x = x - len_v_line;
	mouse_y = y + i;
	mouse_w = str_len_draw( str_foot_left );
	mouse_h = 1;
	call_cui_mouse_add_handler(
			TRUE,
			mouse_x, mouse_y, mouse_w, mouse_h,
			NULL,
			cb_cui_mouse_click_menu_page,
			NULL,
			-1, "" );

	/* �� */

	curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
	print_str( x - len_v_line + len_foot_left,
			y + i, str_foot );

	/* �ڡ����� */

	curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
	print_str( x - len_v_line + len_foot_left + len_foot,
			y + i, str_page );

	/* ���� */

	if( flg_foot_right_rev )
		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
	else
		curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
	print_str( x - len_v_line + len_foot_left + len_foot + len_page,
			y + i, str_foot_right );

	/* �ޥ����Υϥ�ɥ������ */

	mouse_x = x - len_v_line + len_foot_left + len_foot + len_page;
	mouse_y = y + i;
	mouse_w = str_len_draw( str_foot_right );
	mouse_h = 1;
	call_cui_mouse_add_handler(
			TRUE,
			mouse_x, mouse_y, mouse_w, mouse_h,
			NULL,
			cb_cui_mouse_click_menu_page,
			NULL,
			+1, "" );

	/* ������ɥ��� */

	/* �� */
	mouse_x = 0;
	mouse_y = y;
	mouse_w = x;
	mouse_h = i;
	call_cui_mouse_add_handler(
			TRUE,
			mouse_x, mouse_y, mouse_w, mouse_h,
			NULL,
			cb_cui_mouse_click_menu_outside,
			NULL,
			-1, "" );

	/* �� */
	mouse_x = x + len_chk + len_direct + width + 2;
	mouse_y = y;
	mouse_w = get_screen_col() - mouse_x;
	mouse_h = i;
	call_cui_mouse_add_handler(
			TRUE,
			mouse_x, mouse_y, mouse_w, mouse_h,
			NULL,
			cb_cui_mouse_click_menu_outside,
			NULL,
			+1, "" );

	/* �ޥ������ۥ����� */
	set_cui_mouse_add_handler_common_scroll();

	/**/

	curs_attrset_dflt();

	data->prev_sel_n = data->sel_n;
}

/***************************************************************
* ��˥塼���ݥ���ȤΥޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_point_menu( long btn, long n, const char *macro )
{
	long	dn;
	long	i;

	if( g_cui_mouse_menu_sel_n <= -1 )
		return FALSE;

	dn = n - g_cui_mouse_menu_sel_n;

	switch( btn ){
	case 0:
		for( i = 0; i < labs( dn ); i++ ){
			if( dn <= -1 )
				set_key_buf_char_tail( '8' );
			if( dn >= +1 )
				set_key_buf_char_tail( '2' );
		}
		return TRUE;
	case 1:
		break;
	case 2:
		break;
	}

	return FALSE;
}

/***************************************************************
* ��˥塼������å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_menu( long btn, long n, const char *macro )
{
	switch( btn ){
	case 0:
		set_key_buf_str_tail( macro );
		return TRUE;
	case 1:
		set_key_buf_char_tail( ':' );
		return TRUE;
	case 2:
		set_key_buf_char_tail( '0' );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ��˥塼�Υڡ���������å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_menu_page( long btn, long n, const char *macro )
{
	switch( btn ){
	case 0:
		break;
	case 1:
		n = +-0;
		break;
	case 2:
		n = -n;
		break;
	}

	if( n <= -1 ){
		set_key_buf_char_tail( '4' );
		return TRUE;
	}
	if( n >= +1 ){
		set_key_buf_char_tail( '6' );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ��˥塼���ȳ�����å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_menu_outside(
	long btn, long n, const char *macro
)
{
	switch( btn ){
	case 0:
		if( n == +-0 ){
			break;
		} else if( n <= -1 ){
			set_key_buf_char_tail( '4' );
			return TRUE;
		} else if( n >= +1 ){
			set_key_buf_char_tail( '6' );
			return TRUE;
		}
		break;
	case 1:
		break;
	case 2:
		set_key_buf_char_tail( '0' );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* �ޥ������ۥ�����ζ��̤Υޥ������ϥ�ɥ����Ͽ
***************************************************************/

void	set_cui_mouse_add_handler_common_scroll( void )
{
	long	mouse_x, mouse_y, mouse_w, mouse_h;

	mouse_x = SCREEN_MIN_X;
	mouse_y = SCREEN_MIN_Y;
	mouse_w = get_screen_col();
	mouse_h = get_screen_row();
	call_cui_mouse_add_handler(
			TRUE,
			mouse_x, mouse_y, mouse_w, mouse_h,
			cb_cui_mouse_point_dummy,
			cb_cui_mouse_click_common_scroll,
			cb_cui_mouse_scroll_common_scroll,
			0,"" );
}

/***************************************************************
* ���ߡ��Υݥ���ȤΥޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_point_dummy(
	long btn, long n, const char *macro
)
{
	/* �����Υץ쥹�ʡ�Ϣ³������¹ԡ����ˤ��ߤ�ʤ��ʤ�Τ��ɻߤ���٤� */
	/* ���ߡ��Υ��٥�ȡ��ϥ�ɥ� */

	return TRUE;
}

/***************************************************************
* ��������ζ��̤Υ���å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_common_scroll(
	long btn, long n, const char *macro
)
{
	switch( btn ){
	case 0:
		set_key_buf_char_tail( '\n' );
		return TRUE;
	case 1:
		break;
	case 2:
		set_key_buf_char_tail( '0' );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ��������ζ��̤Υۥ�����Υޥ������ϥ�ɥ�
* long scroll_dir : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_scroll_common_scroll(
	long scroll_dir, long n, const char *macro
)
{
	switch( scroll_dir ){
	case 0:
		set_key_buf_char_tail( '4' );
		return TRUE;
	case 1:
		set_key_buf_char_tail( '6' );
		return TRUE;
	case 2:
		set_key_buf_char_tail( '8' );
		return TRUE;
	case 3:
		set_key_buf_char_tail( '2' );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* �������ϥ�˥塼������
* long figure : ��
* long sel_n : ������η�
* char num[] : ����ʸ����
***************************************************************/

void	draw_menu_num( long figure, long sel_n, char num[] )
{
	long	i, n;
	long	x, y;
	long	figure_n;
	long	comma_fmt_len;
	long	width;
	static char	box_str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;
	const long	len_shadow = 2;
	char	str_crsr[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const char	*str_crsr_sel = "****************";
	const char	*str_crsr_no_sel = "                ";
	char	mouse_macro[MACRO_MAX_LEN + 1];

	if( figure <= 0 )
		return;

	flg_draw_menu = TRUE;

	/* Ϣ³�¹Ԥ���� */
	clr_continue_exec_mode();

	if( !g_flg_cui )
		return;

	/* �ޥ����Υϥ�ɥ��ꥻ�å� */
	call_cui_mouse_reset_handler_tab();

	comma_fmt_len = (figure - 1) / 3;

	/* ������ɥ��������Ȥ�� */
	width = 1 + figure + comma_fmt_len
			+ str_len_draw( MSG_MENU_MIN )
			+ str_len_draw( MSG_MENU_MAX )
			+ str_len_draw( MSG_MENU_CLR )
			+ str_len_draw( MSG_MENU_OK );

	x = WIN_MENU_DRAW_MIN_X + (WIN_MENU_DRAW_MAX_X - width) / 2;
	y = WIN_MENU_DRAW_MIN_Y + WIN_MENU_DRAW_MAX_Y / 2;

	str_nz_cpy( box_str, MSG_MENU_CORNER, max_len );
	for( i = 0; i < width; i++ )
		str_max_n_cat( box_str, MSG_MENU_H_LINE, max_len );
	str_max_n_cat( box_str, MSG_MENU_CORNER, max_len );

	/* ������ɥ��αƤ����� */

	for( i = -2; i <= +2; i++ ){
		print_str( x - len_shadow, y + i,
				MSG_MENU_CLR_FMT,
				width + len_shadow * 2, "" );
	}

	/* ������ɥ������� */

	curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
	print_str( x, y - 2, box_str );

	i = 0;
	curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
	print_str( x + i, y - 1, MSG_MENU_V_LINE );
	print_str( x + i, y, MSG_MENU_V_LINE );
	print_str( x + i, y + 1, MSG_MENU_V_LINE );
	i++;

	figure_n = figure;
	for( n = 0; num[n] != '\0'; n++, i++ ){
		if( sel_n == n ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			str_nz_cpy( str_crsr, str_crsr_sel, 1 );
		} else {
			curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
			str_nz_cpy( str_crsr, str_crsr_no_sel, 1 );
		}

		print_str( x + i, y - 1, "%s", str_crsr );
		print_str( x + i, y, "%1c", num[n] );
		print_str( x + i, y + 1, "%s", str_crsr );

		/* �ޥ����Υϥ�ɥ������ */

		if( n == 0 )
			mouse_macro[0] = 'V';
		else
			mouse_macro[0] = (char)('A' + (figure - n));
		mouse_macro[1] = '\0';

		/* �ץ饹 */
		call_cui_mouse_add_handler(
				TRUE,
				(x + i), (y - 1), 1, 1,
				cb_cui_mouse_point_menu_num,
				cb_cui_mouse_click_menu_num,
				NULL,
				+1, mouse_macro );

		/* ���� */
		call_cui_mouse_add_handler(
				TRUE,
				(x + i), (y + 0), 1, 1,
				cb_cui_mouse_point_menu_num,
				cb_cui_mouse_click_menu_num,
				NULL,
				+-0, mouse_macro );

		/* �ޥ��ʥ� */
		call_cui_mouse_add_handler(
				TRUE,
				(x + i), (y + 1), 1, 1,
				cb_cui_mouse_point_menu_num,
				cb_cui_mouse_click_menu_num,
				NULL,
				-1, mouse_macro );

		/* ����� */

		if( (n != 0) && (figure_n > 0)
				&& ((figure_n % 3) == 0) ){
			i++;

			curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
			print_str( x + i, y, "," );
		}
		figure_n--;
	}

	/* min */

	if( sel_n == 1 + figure + MENU_NUM_MIN ){
		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
		str_nz_cpy( str_crsr, str_crsr_sel,
				str_len_draw( MSG_MENU_MIN ) );
	} else {
		curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
		str_nz_cpy( str_crsr, str_crsr_no_sel,
				str_len_draw( MSG_MENU_MIN ) );
	}
	print_str( x + i, y - 1, "%s", str_crsr );
	print_str( x + i, y, MSG_S, MSG_MENU_MIN );
	print_str( x + i, y + 1, "%s", str_crsr );

	/* �ޥ����Υϥ�ɥ������ */
	sn_printf( mouse_macro, MACRO_MAX_LEN, "W" );
	call_cui_mouse_add_handler(
			TRUE,
			(x + i), (y - 1), str_len_draw( MSG_MENU_MIN ), 3,
			cb_cui_mouse_point_menu_num,
			cb_cui_mouse_click_menu_num,
			NULL,
			CUI_MOUSE_CLICK_MENU_NUM_ENTER, mouse_macro );

	i += str_len_draw( MSG_MENU_MIN );

	/* max */

	if( sel_n == 1 + figure + MENU_NUM_MAX ){
		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
		str_nz_cpy( str_crsr, str_crsr_sel,
				str_len_draw( MSG_MENU_MAX ) );
	} else {
		curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
		str_nz_cpy( str_crsr, str_crsr_no_sel,
				str_len_draw( MSG_MENU_MAX ) );
	}
	print_str( x + i, y - 1, "%s", str_crsr );
	print_str( x + i, y, MSG_S, MSG_MENU_MAX );
	print_str( x + i, y + 1, "%s", str_crsr );

	/* �ޥ����Υϥ�ɥ������ */
	sn_printf( mouse_macro, MACRO_MAX_LEN, "X" );
	call_cui_mouse_add_handler(
			TRUE,
			(x + i), (y - 1), str_len_draw( MSG_MENU_MAX ), 3,
			cb_cui_mouse_point_menu_num,
			cb_cui_mouse_click_menu_num,
			NULL,
			CUI_MOUSE_CLICK_MENU_NUM_ENTER, mouse_macro );

	i += str_len_draw( MSG_MENU_MAX );

	/* clr */

	if( sel_n == 1 + figure + MENU_NUM_CLR ){
		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
		str_nz_cpy( str_crsr, str_crsr_sel,
				str_len_draw( MSG_MENU_CLR ) );
	} else {
		curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
		str_nz_cpy( str_crsr, str_crsr_no_sel,
				str_len_draw( MSG_MENU_CLR ) );
	}
	print_str( x + i, y - 1, "%s", str_crsr );
	print_str( x + i, y, MSG_S, MSG_MENU_CLR );
	print_str( x + i, y + 1, "%s", str_crsr );

	/* �ޥ����Υϥ�ɥ������ */
	sn_printf( mouse_macro, MACRO_MAX_LEN, "Y" );
	call_cui_mouse_add_handler(
			TRUE,
			(x + i), (y - 1), str_len_draw( MSG_MENU_CLR ), 3,
			cb_cui_mouse_point_menu_num,
			cb_cui_mouse_click_menu_num,
			NULL,
			CUI_MOUSE_CLICK_MENU_NUM_ENTER, mouse_macro );

	i += str_len_draw( MSG_MENU_CLR );

	/* ok */

	if( sel_n == 1 + figure + MENU_NUM_OK ){
		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
		str_nz_cpy( str_crsr, str_crsr_sel,
				str_len_draw( MSG_MENU_OK ) );
	} else {
		curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
		str_nz_cpy( str_crsr, str_crsr_no_sel,
				str_len_draw( MSG_MENU_OK ) );
	}
	print_str( x + i, y - 1, "%s", str_crsr );
	print_str( x + i, y, MSG_S, MSG_MENU_OK );
	print_str( x + i, y + 1, "%s", str_crsr );

	/* �ޥ����Υϥ�ɥ������ */
	sn_printf( mouse_macro, MACRO_MAX_LEN, "Z" );
	call_cui_mouse_add_handler(
			TRUE,
			(x + i), (y - 1), str_len_draw( MSG_MENU_OK ), 3,
			cb_cui_mouse_point_menu_num,
			cb_cui_mouse_click_menu_num,
			NULL,
			CUI_MOUSE_CLICK_MENU_NUM_ENTER, mouse_macro );

	i += str_len_draw( MSG_MENU_OK );

	/* �� */

	call_cui_mouse_add_handler(
			TRUE,
			SCREEN_MIN_X, SCREEN_MIN_Y,
			get_screen_col(), get_screen_row(),
			cb_cui_mouse_point_dummy,
			cb_cui_mouse_click_menu_num_sel,
			cb_cui_mouse_scroll_menu_num_sel,
			+1, mouse_macro );

	/* ������ɥ������� */

	curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
	print_str( x + i, y - 1, MSG_MENU_V_LINE );
	print_str( x + i, y, MSG_MENU_V_LINE );
	print_str( x + i, y + 1, MSG_MENU_V_LINE );

	curs_attrset_n( CURS_ATTR_N_MENU_NORMAL );
	print_str( x, y + 2, box_str );

	/* end */

	curs_attrset_dflt();
}

/***************************************************************
* �������ϥ�˥塼���ݥ���ȤΥޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_point_menu_num( long btn, long n, const char *macro )
{
	switch( btn ){
	case 0:
		set_key_buf_str_tail( macro );
		return TRUE;
	case 1:
		break;
	case 2:
		break;
	}

	return FALSE;
}

/***************************************************************
* �������ϥ�˥塼������å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_menu_num( long btn, long n, const char *macro )
{
	switch( btn ){
	case 0:
		if( n == CUI_MOUSE_CLICK_MENU_NUM_ENTER ){
			set_key_buf_char_tail( '\n' );
			return TRUE;
		} else if( n >= +1 ){
			set_key_buf_char_tail( '8' );
			return TRUE;
		} else if( n == +-0 ){
			set_key_buf_char_tail( '5' );
			return TRUE;
		} else if( n <= -1 ){
			set_key_buf_char_tail( '2' );
			return TRUE;
		}
		break;
	case 1:
		break;
	case 2:
		set_key_buf_char_tail( '0' );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* �������ϥ�˥塼������Υ���å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_menu_num_sel(
	long btn, long n, const char *macro
)
{
	if( get_flg_cui_mouse_scroll_menu_num_is_sel() ){
		switch( btn ){
		case 0:
			set_key_buf_char_tail( '\n' );
			return TRUE;
		case 1:
			break;
		case 2:
			if( get_flg_cui_mouse_r_click_menu_num_is_cancel() )
				set_key_buf_char_tail( '0' );
			else
				set_key_buf_char_tail( '2' );
			return TRUE;
		}
	} else {
		switch( btn ){
		case 0:
			set_key_buf_char_tail( '4' );
			return TRUE;
		case 1:
			break;
		case 2:
			if( get_flg_cui_mouse_r_click_menu_num_is_cancel() )
				set_key_buf_char_tail( '0' );
			else
				set_key_buf_char_tail( '6' );
			return TRUE;
		}
	}

	return FALSE;
}

/***************************************************************
* �������ϥ�˥塼������Υۥ�����Υޥ������ϥ�ɥ�
* long scroll_dir : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_scroll_menu_num_sel(
	long scroll_dir, long n, const char *macro
)
{
	if( get_flg_cui_mouse_scroll_menu_num_is_sel() ){
		switch( scroll_dir ){
		case 0:
			set_key_buf_char_tail( '4' );
			return TRUE;
		case 1:
			set_key_buf_char_tail( '6' );
			return TRUE;
		case 2:
			set_key_buf_char_tail( '4' );
			return TRUE;
		case 3:
			set_key_buf_char_tail( '6' );
			return TRUE;
		}
	} else {
		switch( scroll_dir ){
		case 0:
			set_key_buf_char_tail( '4' );
			return TRUE;
		case 1:
			set_key_buf_char_tail( '6' );
			return TRUE;
		case 2:
			set_key_buf_char_tail( '\n' );
			return TRUE;
		case 3:
			set_key_buf_char_tail( '2' );
			return TRUE;
		}
	}

	return FALSE;
}

/***************************************************************
* �ۥ�����ǿ������ϥ�˥塼�����򤹤뤫?
* return : ���򤹤뤫?
***************************************************************/

bool_t	get_flg_cui_mouse_scroll_menu_num_is_sel( void )
{
	return g_flg_cui_mouse_scroll_menu_num_is_sel;
}

/***************************************************************
* �ۥ�����ǿ������ϥ�˥塼�����򤹤뤫����
* bool_t flg : ���򤹤뤫?
***************************************************************/

void	set_flg_cui_mouse_scroll_menu_num_is_sel( bool_t flg )
{
	g_flg_cui_mouse_scroll_menu_num_is_sel = flg;
}

/***************************************************************
* ������å��ǿ������ϥ�˥塼�򥭥�󥻥뤹�뤫?
* return : ����󥻥뤹�뤫?
***************************************************************/

bool_t	get_flg_cui_mouse_r_click_menu_num_is_cancel( void )
{
	return g_flg_cui_mouse_r_click_menu_num_is_cancel;
}

/***************************************************************
* ������å��ǿ������ϥ�˥塼�򥭥�󥻥뤹�뤫?
* bool_t flg : ����󥻥뤹�뤫?
***************************************************************/

void	set_flg_cui_mouse_r_click_menu_num_is_cancel( bool_t flg )
{
	g_flg_cui_mouse_r_click_menu_num_is_cancel = flg;
}

/***************************************************************
* ��˥塼���ܤ�������ɥ��򳫤��ʤ顢���ΰ����֤�
* char *kind : ��˥塼���ܤμ���
* return : ����ʸ����
***************************************************************/

char	*get_str_open_win_item( char *kind )
{
	if( strcmp( kind, "<OpenWinItem>" ) == 0 )
		return MSG_MENU_KIND_OPEN_WIN_ITEM;

	return MSG_MENU_KIND_ITEM;
}

/***************************************************************
* ��˥塼���ܤ����֡���˥塼�򳫤��ʤ顢���ΰ����֤�
* char *kind : ��˥塼���ܤμ���
* return : ����ʸ����
***************************************************************/

char	*get_str_branch( char *kind )
{
	if( strcmp( kind, "<Branch>" ) == 0 )
		return MSG_MENU_KIND_BRANCH;

	return MSG_MENU_KIND_ITEM;
}

/***************************************************************
* ��˥塼��õ��
* return : �õ����?
***************************************************************/

bool_t	wipe_menu( void )
{
	if( flg_draw_menu ){
		/* �ޥ����Υϥ�ɥ��ꥻ�å� */
		call_cui_mouse_reset_handler_tab();

		/* ��˥塼��õ��ɬ�פ�ͭ���� */

		call_gui_menu_wipe();

		flg_draw_menu = FALSE;
		redraw_all();

		return TRUE;
	} else {
		/* ��˥塼��õ��ɬ�פ�̵����� */

		return FALSE;
	}
}

/***************************************************************
* ���ƤΥ��С��Ȥ���¾�Υ��ơ�������ɽ��
***************************************************************/

void	draw_all_mbr_stat( void )
{
	party_t	*pty;
	pet_t	**pet;
	long	i;

	if( g_flg_gui )
		call_gui_stat_redraw();
	if( !g_flg_cui )
		return;

	pty = get_party();
	pet = get_party_pet();

	switch( get_stat_mode() ){
	case STAT_MODE_MAX_N:
	case STAT_MODE_MBR:
		for( i = 0; i < MBR_MAX_N; i++ )
			draw_mbr_stat( pty->mbr[i] );
		break;
	case STAT_MODE_PET:
		for( i = 0; i < PET_MAX_N; i++ )
			draw_mbr_stat( pet[i] );
		break;
	}

	draw_misc_stat();
}

/***************************************************************
* ���С��Υ��ơ�������ɽ��
* mbr_t *mbr : ���С�
***************************************************************/

void	draw_mbr_stat( mbr_t *mbr )
{
	long	x, y;
	long	mbr_n;
	curs_attr_t	*attr_p, attr;
	rate_t	hp_rate, mp_rate;

	/* ���С��������å� */

	if( mbr != NULL ){
		switch( get_stat_mode() ){
		case STAT_MODE_MAX_N:
		case STAT_MODE_MBR:
			if( !is_mbr( mbr ) )
				return;
			break;
		case STAT_MODE_PET:
			if( !is_pet( mbr ) )
				return;
			break;
		}
	}

	if( mbr == NULL ){
		mbr_n = MBR_N_NOT_JOIN;
	} else if( is_mbr( mbr ) ){
		mbr_n = mbr->mbr_n;
		if( (mbr_n < 0) || (MBR_MAX_N <= mbr_n) )
			return;
	} else if( is_pet( mbr ) ){
		mbr_n = get_pet_n( mbr );
	} else {
		return;
	}

	if( g_flg_gui )
		call_gui_stat_draw( mbr_n );
	if( !g_flg_cui )
		return;

	/* ���襢�ȥ�ӥ塼�Ȥ����� */

	attr_p = get_curs_attr();
	if( attr_p == NULL )
		return;

	attr = attr_p[CURS_ATTR_N_MAP_NPC];
	attr.attr &= ~(A_REVERSE);

	if( mbr == NULL ){
		attr_p = &(attr_p[CURS_ATTR_N_MAP_NPC]);
		attr = *attr_p;
		attr.attr &= ~(A_REVERSE);
	} else if( is_mbr( mbr ) ){
		attr_p = &(attr_p[CURS_ATTR_N_MBR_1]);
		attr = attr_p[mbr_n];
		attr.attr &= ~(A_REVERSE);
	} else if( is_pet( mbr ) ){
		attr_p = &(attr_p[CURS_ATTR_N_MAP_PET]);
		attr = *attr_p;
		attr.attr &= ~(A_REVERSE);
	}

	/* ������ɥ��Ȥ����� */

	x = WIN_STAT_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + (mbr_n * WIN_STAT_DRAW_HEIGHT) + 2;
	print_str( x, y, MSG_S, MSG_STAT_FRAME );

	/* ���С��������ʤ��Ȥ������褷��ȴ���� */

	if( mbr == NULL ){
		return;
	} else if( is_mbr( mbr ) ){
		if( mbr_n == MBR_N_NOT_JOIN ){
			return;
		}
	}

	if( chk_flg( mbr->stat, FLG_STAT_NOT_EXIST ) ){
		y = WIN_STAT_DRAW_MIN_Y;
		y += mbr_n * WIN_STAT_DRAW_HEIGHT;
		for( ; y <= WIN_STAT_DRAW_MAX_Y; y++ ){
			x = WIN_STAT_DRAW_MIN_X;
			for( ; x <= WIN_STAT_DRAW_MAX_X; x++ ){
				print_str( x, y, " " );
			}
		}

		return;
	}

	/* ̾�� */

	x = WIN_STAT_DRAW_MIN_X + WIN_STAT_NAME_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + WIN_STAT_NAME_DRAW_MIN_Y
			+ (mbr_n * WIN_STAT_DRAW_HEIGHT);
	curs_attrset_dir( &attr );
	print_str( x, y, "%-*s ", WIN_STAT_NAME_DRAW_WIDTH, mbr->name );
	curs_attrset_dflt();

	/* HP */

	hp_rate = mbr->abl.hp.n * _100_PERCENT / mbr->abl.hp.max;
	if( hp_rate <= WARNING_HP_RATE_YELLOW )
		curs_attrset_chr( mbr, -1, FALSE );

	x = WIN_STAT_DRAW_MIN_X + WIN_STAT_HP_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + WIN_STAT_HP_DRAW_MIN_Y
			+ (mbr_n * WIN_STAT_DRAW_HEIGHT);
	print_str( x, y, "HP%*d/%*d ",
			WIN_STAT_CURE_HP_DRAW_WIDTH,
			mbr->abl.hp.n,
			WIN_STAT_MAX_HP_DRAW_WIDTH,
			mbr->abl.hp.max );

	curs_attrset_dflt();

	/* MP */

	mp_rate = mbr->abl.mp.n * _100_PERCENT / mbr->abl.mp.max;
	if( mp_rate <= WARNING_MP_RATE_YELLOW )
		curs_attrset_chr( mbr, -1, FALSE );

	x = WIN_STAT_DRAW_MIN_X + WIN_STAT_MP_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + WIN_STAT_MP_DRAW_MIN_Y
			+ (mbr_n * WIN_STAT_DRAW_HEIGHT);
	print_str( x, y, "MP%*d/%*d ",
			WIN_STAT_CURE_MP_DRAW_WIDTH,
			mbr->abl.mp.n,
			WIN_STAT_MAX_MP_DRAW_WIDTH,
			mbr->abl.mp.max );

	curs_attrset_dflt();

	/* ��������� */

	x = WIN_STAT_DRAW_MIN_X + WIN_STAT_ACT_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + WIN_STAT_ACT_DRAW_MIN_Y
			+ (mbr_n * WIN_STAT_DRAW_HEIGHT);

	print_str( x, y, "%-*s", WIN_STAT_ACT_DRAW_WIDTH, mbr->act.msg );

	/* ��Ĵ */

	x = WIN_STAT_DRAW_MIN_X + WIN_STAT_COND_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + WIN_STAT_COND_DRAW_MIN_Y
			+ (mbr_n * WIN_STAT_DRAW_HEIGHT);

	print_str( x, y, "%-*s", WIN_STAT_COND_DRAW_WIDTH, "" );

	if( chk_flg( mbr->stat, FLG_STAT_DEAD ) )
		print_str( x, y, MSG_S, MSG_STAT_DEAD );

	else if( chk_flg( mbr->stat, FLG_STAT_STONE ) )
		print_str( x, y, MSG_S, MSG_STAT_STONE );

	else if( chk_flg( mbr->stat, FLG_STAT_FAINT ) )
		print_str( x, y, MSG_S, MSG_STAT_FAINT );

	else if( chk_flg( mbr->stat, FLG_STAT_PARALYZE ) )
		print_str( x, y, MSG_S, MSG_STAT_PARALYZE );

	else if( chk_flg( mbr->stat, FLG_STAT_POISON ) )
		print_str( x, y, MSG_S, MSG_STAT_POISON );

	else if( chk_flg( mbr->stat, FLG_STAT_CONFUSION ) )
		print_str( x, y, MSG_S, MSG_STAT_CONFUSION );

	else if( chk_flg( mbr->stat, FLG_STAT_BLIND ) )
		print_str( x, y, MSG_S, MSG_STAT_BLIND );

	else if( chk_flg( mbr->stat, FLG_STAT_SLEEP ) )
		print_str( x, y, MSG_S, MSG_STAT_SLEEP );

	else if( chk_flg( mbr->stat, FLG_STAT_SILENCE ) )
		print_str( x, y, MSG_S, MSG_STAT_SILENCE );

	else if( chk_flg( mbr->stat, FLG_STAT_CAUGHT ) )
		print_str( x, y, MSG_S, MSG_STAT_CAUGHT );

	else if( chk_flg( mbr->stat, FLG_STAT_FEAR ) )
		print_str( x, y, MSG_S, MSG_STAT_FEAR );

	else if( chk_flg( mbr->stat, FLG_STAT_HALLUCINATION ) )
		print_str( x, y, MSG_S, MSG_STAT_HALLUCINATION );

	else if( chk_flg( mbr->stat, FLG_STAT_CHARM ) )
		print_str( x, y, MSG_S, MSG_STAT_CHARM );

	else if( chk_flg( mbr->stat, FLG_STAT_DRUNK ) )
		print_str( x, y, MSG_S, MSG_STAT_DRUNK );

	else if( chk_flg( mbr->stat, FLG_STAT_FLY ) )
		print_str( x, y, MSG_S, MSG_STAT_FLY );

	else if( chk_flg( mbr->stat, FLG_STAT_VANISH ) )
		print_str( x, y, MSG_S, MSG_STAT_VANISH );

	else if( chk_flg( mbr->stat, FLG_STAT_IRON_BODY ) )
		print_str( x, y, MSG_S, MSG_STAT_IRON_BODY );

	else if( chk_flg( mbr->stat, FLG_STAT_PASSWALL ) )
		print_str( x, y, MSG_S, MSG_STAT_PASSWALL );

	else if( chk_flg( mbr->stat, FLG_STAT_SENSE_INVISIBLE ) )
		print_str( x, y, MSG_S, MSG_STAT_SENSE_INVISIBLE );

	else if( chk_flg( mbr->stat, FLG_STAT_STARVATION ) )
		print_str( x, y, MSG_S, MSG_STAT_STARVATION );

	else if( chk_flg( mbr->stat, FLG_STAT_HUNGRY ) )
		print_str( x, y, MSG_S, MSG_STAT_HUNGRY );
}

/***************************************************************
* ����¾�Υ��ơ�������ɽ��
***************************************************************/

void	draw_misc_stat( void )
{
	party_t	*pty = get_party();
	long	x, y;

	if( g_flg_gui )
		call_gui_stat_redraw();
	if( !g_flg_cui )
		return;

	/* ���� */

	x = WIN_STAT_DRAW_MIN_X
			+ WIN_STAT_DUN_LEV_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y
			+ MBR_MAX_N * WIN_STAT_DRAW_HEIGHT
			+ WIN_STAT_DUN_LEV_DRAW_MIN_Y;

	print_str( x, y + 0, "%*s", WIN_STAT_DRAW_WIDTH, " " );
	print_str( x, y + 1, "%*s", WIN_STAT_DRAW_WIDTH, " " );

	print_str( x, y, MSG_S, get_stat_dun_lev_str() );

	/* ���� */

	draw_misc_stat_time( TRUE );

	/* ��������� */

	x = WIN_STAT_DRAW_MIN_X + WIN_STAT_ACT_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y + WIN_STAT_ACT_DRAW_MIN_Y
			+ (MBR_MAX_N * WIN_STAT_DRAW_HEIGHT);

	print_str( x, y, "%-*s", WIN_STAT_ACT_DRAW_WIDTH, pty->act.msg );

	/* ������ɥ��� */

	x = WIN_STAT_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y
			+ MBR_MAX_N * WIN_STAT_DRAW_HEIGHT + 2;
	for( ; x <= WIN_STAT_DRAW_MAX_X; x++ ){
		print_str( x, y, "-" );
	}

	draw_replay( TRUE );
}

/***************************************************************
* ���ơ�����ɽ���Υ⡼���ڤ괹��
* long add : �ڤ괹����
***************************************************************/

void	switch_stat_mode( long add )
{
	long	n;

	n = g_stat_mode_n;

	n += add;
	n %= STAT_MODE_MAX_N;
	n += STAT_MODE_MAX_N;
	n %= STAT_MODE_MAX_N;

	g_stat_mode_n = (stat_mode_t)n;
}

/***************************************************************
* ���ơ�����ɽ���Υ⡼�ɤ��֤�
* return : �⡼��
***************************************************************/

stat_mode_t	get_stat_mode( void )
{
	return g_stat_mode_n;
}

/***************************************************************
* ���С������ơ������Υ���å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_stat( long btn, long n, const char *macro )
{
	switch( btn ){
	case 0:
		set_key_buf_str_tail( macro );
		return TRUE;
	case 1:
	case 2:
		break;
	}

	return FALSE;
}

/***************************************************************
* ���ơ�������ɽ���ڤ괹���Υ���å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_switch_stat(
	long btn, long n, const char *macro
)
{
	if( btn == n ){
		set_key_buf_char_tail( 'Z' );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ���ơ������γ��ؤ�ʸ������֤�
***************************************************************/

const char	*get_stat_dun_lev_str( void )
{
	dun_t	*dun;
	static char	buf[40 + 1];
	long	max_len = 40;

	dun = get_dun();

	buf[0] = '\0';

	if( get_scene() == SCENE_N_LAST_BOSS ){
		sn_printf( buf, max_len, MSG_STAT_DUN_LEV_LAST_STAGE );
	} else if( sgn_l( dun->lev ) >= +1 ){
		sn_printf( buf, max_len, MSG_STAT_DUN_LEV_FLOOR,
				labs( dun->lev ) );
	} else if( sgn_l( dun->lev ) <= -1 ){
		sn_printf( buf, max_len, MSG_STAT_DUN_LEV_BASE,
				labs( dun->lev ) );
	} else {
		sn_printf( buf, max_len, MSG_STAT_DUN_LEV_GROUND,
				labs( dun->lev ) );
	}

	return buf;
}

/***************************************************************
* ����¾�Υ��ơ������λ��֤�ɽ��
* bool_t flg_force : ����Ū��ɽ��
***************************************************************/

void	draw_misc_stat_time( bool_t flg_force )
{
	long	pre_minute;
	long	minute;
	long	x, y;

	pre_minute = static_draw_misc_stat_time__pre_minute;

	/* ���֤��Ѥ�äƤʤ����ɽ�����ʤ� */

	if( !flg_force ){
		minute = get_turn() / TURN_PER_MINUTE;
		if( pre_minute == minute )
			return;
		pre_minute = minute;
	}

	/* ���� */

	x = WIN_STAT_DRAW_MIN_X
			+ WIN_STAT_TIME_DRAW_MIN_X;
	y = WIN_STAT_DRAW_MIN_Y
			+ MBR_MAX_N * WIN_STAT_DRAW_HEIGHT
			+ WIN_STAT_TIME_DRAW_MIN_Y;

	if( g_flg_gui )
		call_gui_stat_redraw();
	if( g_flg_cui )
		print_str( x, y, MSG_S, get_stat_time_str() );

	static_draw_misc_stat_time__pre_minute = pre_minute;
}

/***************************************************************
* ����� GUI VFX ��������
* bool_t flg_crtcl : ����ƥ����뤫?
* return : ������Ƥ��ǡ���
***************************************************************/

gui_vfx_t	*alloc_gui_vfx_bash( bool_t flg_crtcl )
{
	gui_vfx_t	*vfx;

	vfx = alloc_gui_vfx();
	if( vfx == NULL )
		return NULL;

	vfx->kind = GUI_VFX_KIND_BASH;
	vfx->anim_rate = (rate_t)0;
	vfx->flg_crtcl = flg_crtcl;

	return vfx;
}

/***************************************************************
* ��� GUI VFX ��������
* long dir_n : ��θ��� (10 key)
* return : ������Ƥ��ǡ���
***************************************************************/

gui_vfx_t	*alloc_gui_vfx_arw( long dir_n )
{
	gui_vfx_t	*vfx;

	vfx = alloc_gui_vfx();
	if( vfx == NULL )
		return NULL;

	vfx->kind = GUI_VFX_KIND_ARW;
	vfx->dir_n = dir_n;

	return vfx;
}

/***************************************************************
* �ꤲ������ GUI VFX ��������
* char mjr : �᥸�㡼��ʸ��
* char mnr : �ޥ��ʡ���ʸ��
* return : ������Ƥ��ǡ���
***************************************************************/

gui_vfx_t	*alloc_gui_vfx_throw_item( char mjr, char mnr )
{
	gui_vfx_t	*vfx;

	vfx = alloc_gui_vfx();
	if( vfx == NULL )
		return NULL;

	vfx->kind = GUI_VFX_KIND_THROW_ITEM;
	vfx->mjr = mjr;
	vfx->mnr = mnr;

	return vfx;
}

/***************************************************************
* ��ʸ�� GUI VFX ��������
* resi_kind_t resi : �����μ���
* return : ������Ƥ��ǡ���
***************************************************************/

gui_vfx_t	*alloc_gui_vfx_spell( resi_kind_t resi )
{
	gui_vfx_t	*vfx;

	vfx = alloc_gui_vfx();
	if( vfx == NULL )
		return NULL;

	vfx->kind = GUI_VFX_KIND_SPELL;
	vfx->resi_kind = resi;

	return vfx;
}

/***************************************************************
* ������ GUI VFX ��������
* blast_kind_t blast : �����μ���
* return : ������Ƥ��ǡ���
***************************************************************/

gui_vfx_t	*alloc_gui_vfx_blast( blast_kind_t blast )
{
	gui_vfx_t	*vfx;

	vfx = alloc_gui_vfx();
	if( vfx == NULL )
		return NULL;

	vfx->kind = GUI_VFX_KIND_BLAST;
	vfx->blast_kind = blast;

	return vfx;
}

/***************************************************************
* Ǧ�Ѥ� GUI VFX ��������
* spell_kind_t spell : �����μ���
* return : ������Ƥ��ǡ���
***************************************************************/

gui_vfx_t	*alloc_gui_vfx_ninja( spell_kind_t spell )
{
	gui_vfx_t	*vfx;

	vfx = alloc_gui_vfx();
	if( vfx == NULL )
		return NULL;

	vfx->kind = GUI_VFX_KIND_NINJA;
	vfx->spell_kind = spell;
	vfx->anim_rate = gui_randm( _100_PERCENT );

	return vfx;
}

/***************************************************************
* GUI VFX ��������
* return : ������Ƥ��ǡ���
***************************************************************/

gui_vfx_t	*alloc_gui_vfx( void )
{
	long	i;

	for( i = 0; i < GUI_VFX_POOL_MAX_N; i++ ){
		if( g_gui_vfx_pool[i].flg_use )
			continue;

		g_gui_vfx_pool[i].flg_use = TRUE;
		g_gui_vfx_pool[i].kind = GUI_VFX_KIND_NULL;
		g_gui_vfx_pool[i].dir_n = 5;
		g_gui_vfx_pool[i].mjr = FACE_MJR_NULL;
		g_gui_vfx_pool[i].mnr = FACE_MNR_NULL;
		g_gui_vfx_pool[i].resi_kind = RESI_KIND_SLAS;
		g_gui_vfx_pool[i].blast_kind = BLAST_KIND_STD;
		g_gui_vfx_pool[i].spell_kind = SPELL_KIND_NULL;
		return &(g_gui_vfx_pool[i]);
	}

	return NULL;
}

/***************************************************************
* GUI VFX �����
* gui_vfx_t *vfx : ������Ƥ��ǡ���
***************************************************************/

void	free_gui_vfx( gui_vfx_t *vfx )
{
	if( vfx == NULL )
		return;

	vfx->flg_use = FALSE;
}

/***************************************************************
* �ޥåפ����Ƥ� GUI VFX �򥯥ꥢ
***************************************************************/

void	clr_gui_vfx_all( void )
{
	long	x, y;

	for( y = 0; y < MAP_MAX_Y; y++ )
		for( x = 0; x < MAP_MAX_X; x++ )
			clr_gui_vfx( x, y );
}

/***************************************************************
* �ޥåפ� GUI VFX �򥯥ꥢ
* long map_x : X ��ɸ
* long map_y : Y ��ɸ
***************************************************************/

void	clr_gui_vfx( long map_x, long map_y )
{
	dun_t	*dun;

	if( !clip_pos( map_x, map_y ) )
		return;

	dun = get_dun();
	dun->map.gui_vfx[map_y][map_x] = NULL;
}

/***************************************************************
* �ޥåפ� GUI VFX ������
* long map_x : X ��ɸ
* long map_y : Y ��ɸ
* gui_vfx_t *vfx : GUI VFX
***************************************************************/

void	set_gui_vfx( long map_x, long map_y, gui_vfx_t *vfx )
{
	dun_t	*dun;

	if( !clip_pos( map_x, map_y ) )
		return;

	dun = get_dun();
	dun->map.gui_vfx[map_y][map_x] = vfx;
}

/***************************************************************
* �ޥåפ� GUI VFX �����
* long map_x : X ��ɸ
* long map_y : Y ��ɸ
* return : GUI VFX
***************************************************************/

gui_vfx_t	*get_gui_vfx( long map_x, long map_y )
{
	dun_t	*dun;

	if( !clip_pos( map_x, map_y ) )
		return NULL;

	dun = get_dun();

	if( dun->map.gui_vfx[map_y][map_x] == NULL )
		return NULL;
	if( !dun->map.gui_vfx[map_y][map_x]->flg_use )
		return NULL;
	return( dun->map.gui_vfx[map_y][map_x] );
}

/***************************************************************
* ��θ�����ƥ󡦥����������֤�
* const pos_t *bgn : ����
* const pos_t *end : ����
* return : ��θ���
***************************************************************/

long	calc_dir_n( const pos_t *bgn, const pos_t *end )
{
	long	dx, dy;
	rate_t	rx, ry;

	if( bgn == NULL )
		return 5;
	if( end == NULL )
		return 5;

	dx = end->x - bgn->x;
	dy = end->y - bgn->y;

	if( dy == 0 )
		rx = _100_PERCENT;
	else
		rx = labs( dx ) * _100_PERCENT / labs( dy );
	if( dx == 0 )
		ry = _100_PERCENT;
	else
		ry = labs( dy ) * _100_PERCENT / labs( dx );

	if( rx < (rate_t)50 ){
		if( sgn_l( dy ) <= -1 )
			return 8;
		if( sgn_l( dy ) >= +1 )
			return 2;
	}
	if( ry < (rate_t)50 ){
		if( sgn_l( dx ) <= -1 )
			return 4;
		if( sgn_l( dx ) >= +1 )
			return 6;
	}
	if( (sgn_l( dy ) <= -1) ){
		if( sgn_l( dx ) <= -1 )
			return 7;
		if( sgn_l( dx ) >= +1 )
			return 9;
	}
	if( (sgn_l( dy ) >= +1) ){
		if( sgn_l( dx ) <= -1 )
			return 1;
		if( sgn_l( dx ) >= +1 )
			return 3;
	}

	return 5;
}

/***************************************************************
* ��ʸ�� VFX ������
* spell_tab_t *tab : ��ʸ
* long arw_n : ��ʸ�ο�
* pos_t bgn[] : ���ϰ���
* pos_t end[] : ��λ����
* return : ���褷����?
***************************************************************/

bool_t	vfx_spell( spell_tab_t *tab, long arw_n, pos_t bgn[], pos_t end[] )
{
	gui_vfx_t	*gui_vfx;
	resi_kind_t	resi;

	if( tab == NULL )
		return FALSE;

	switch( tab->vfx_kind ){
	case VFX_KIND_NULL:
		break;
	case VFX_KIND_ARW:
		if( bgn == NULL )
			return FALSE;
		if( end == NULL )
			return FALSE;

		resi = tab->resi_vfx;
		if( resi >= RESI_KIND_MAX_N )
			resi = tab->resi;

		gui_vfx = alloc_gui_vfx_spell( resi );
		vfx_arw_mul_line( arw_n, bgn, end,
				gui_vfx,
				get_spell_vfx_str( tab->kind ),
				ANIM_SPELL_LEN,
				ANIM_SPELL_FRAME_N,
				ANIM_SPELL_CLR_FRAME_N, TRUE );
		clr_gui_vfx_all();
		free_gui_vfx( gui_vfx );
		break;
	case VFX_KIND_TYPHOON:
		vfx_spell_typhoon();
		break;
	case VFX_KIND_CONFLAGRATION:
		vfx_spell_conflagration( arw_n, end );
		break;
	case VFX_KIND_EARTHQUAKE:
		vfx_spell_earthquake();
		break;
	case VFX_KIND_THUNDER:
		vfx_spell_thunder( arw_n, end );
		break;
	case VFX_KIND_INUNDATION:
		vfx_spell_inundation();
		break;
	case VFX_KIND_MAX_N:
		break;
	}

	return TRUE;
}

/***************************************************************
* �����νѤ� VFX ������
***************************************************************/

void	vfx_spell_typhoon( void )
{
	pos_t	*draw;
	const long	max_r = AREA_MAX_X / 2;
	long	r[TYPHOON_DUST_MAX_N], q[TYPHOON_DUST_MAX_N];
	long	x[TYPHOON_DUST_MAX_N], y[TYPHOON_DUST_MAX_N];
	gui_vfx_t	*gui_vfx[TYPHOON_DUST_MAX_N];
	double	rad;
	time_t	bgn_time;
	long	i, j;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	rad = DBL_PI / 2;
	for( j = 0; j < TYPHOON_DUST_MAX_N; j++ ){
		r[j] = randm( max_r );
		q[j] = randm( 360 );
		x[j] = 0;
		y[j] = 0;

		/* GUI */
		gui_vfx[j] = alloc_gui_vfx_ninja( SPELL_KIND_TYPHOON );
	}

	bgn_time = time( NULL );

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		for( j = 0; j < TYPHOON_DUST_MAX_N; j++ ){
			long	mx, my;
			long	vr;

			/* ���ꥢ */

			draw_map_force( draw->x + x[j] / 2,
					draw->y + y[j],
					1, 1 );

			/* GUI ���ꥢ */

			mx = draw->x + x[j] / 2;
			my = draw->y + y[j];
			clr_gui_vfx( mx, my );
			call_pcg_dun_draw( mx - 2, my - 2, 5, 5, TRUE );

			/* ��ɸ�׻� */

			vr = (TYPHOON_SPEED * 6) * (max_r - r[j]) / max_r;
			q[j] += TYPHOON_SPEED + vr;
			q[j] %= 360;

			x[j] = (long)(r[j] * cos( q[j] * rad / 90 ));
			x[j] += AREA_MAX_X / 2;
			x[j] *= 2;

			y[j] = (long)(r[j] * sin( q[j] * rad / 90 ));
			y[j] += AREA_MAX_Y / 2;

			/* ���� */

			print_vfx( FALSE, x[j], y[j], MSG_S, "@" );

			/* GUI ���� */

			mx = draw->x + x[j] / 2;
			my = draw->y + y[j];

			gui_vfx[j]->anim_rate += GUI_VFX_ANIM_RATE;
			gui_vfx[j]->anim_rate %= _100_PERCENT;

			set_gui_vfx( mx, my, gui_vfx[j] );
			call_pcg_dun_draw( mx - 2, my - 2, 5, 5, TRUE );
		}

		wait_clock( ANIM_TYPHOON_FRAME_N );

		if( difftime( time( NULL ), bgn_time )
				> ANIM_TYPHOON_SEC ){
			break;
		}
	}

	/* GUI �õ� */

	clr_gui_vfx_all();
	for( j = 0; j < TYPHOON_DUST_MAX_N; j++ )
		free_gui_vfx( gui_vfx[j] );

	/* �õ� */

	redraw_map_force();
}

/***************************************************************
* �кҤνѤ� VFX ������
* long arw_n : ����ο�
* pos_t end[] : ��λ����
***************************************************************/

void	vfx_spell_conflagration( long arw_n, pos_t end[] )
{
	static long	h[VFX_ARW_MAX_N], mh[VFX_ARW_MAX_N];
	time_t	bgn_time;
	long	i, j;
	gui_vfx_t	*gui_vfx[VFX_ARW_MAX_N];

	if( end == NULL )
		return;

	if( arw_n > VFX_ARW_MAX_N )
		arw_n = VFX_ARW_MAX_N;

	bgn_time = time( NULL );

	for( j = 0; j < arw_n; j++ ){
		h[j] = 0;
		mh[j] = 0;

		/* GUI */

		gui_vfx[j] = alloc_gui_vfx_ninja(
				SPELL_KIND_CONFLAGRATION );
	}

	for( i = 0; i < LOOP_MAX_100; i++ ){
		bool_t	flg_wait;

		flg_wait = FALSE;

		/* ���� */

		for( j = 0; j < arw_n; j++ ){
			if( mh[j] == h[j] )
				mh[j] = randm( ANIM_CONFLAGRATION_HEIGHT );
			h[j] += sgn_l( mh[j] - h[j] ) * 1;

			if( vfx_spell_conflagration_sub(
					end[j].x, end[j].y, h[j] ) ){
				flg_wait = TRUE;
			}
		}

		/* GUI ���� */

		for( j = 0; j < arw_n; j++ ){
			long	gx, gy, gw, gh;

			gui_vfx[j]->anim_rate += GUI_VFX_ANIM_RATE;
			gui_vfx[j]->anim_rate %= _100_PERCENT;

			set_gui_vfx( end[j].x / 2, end[j].y, gui_vfx[j] );
			gw = 7;
			gh = 10;
			gx = (end[j].x / 2) - (gw / 2);
			gy = end[j].y - (gh - 1);
			call_pcg_dun_draw( gx, gy, gw, gh, TRUE );
		}

		/* �Ԥ� */

		if( flg_wait )
			wait_clock( ANIM_CONFLAGRATION_FRAME_N );

		if( difftime( time( NULL ), bgn_time )
				> ANIM_CONFLAGRATION_SEC ){
			break;
		}
	}

	/* GUI �õ� */

	clr_gui_vfx_all();
	for( j = 0; j < arw_n; j++ )
		free_gui_vfx( gui_vfx[j] );

	/* �õ� */

	redraw_map_force();
}

/***************************************************************
* �кҤνѤβ��������
* long x : X��ɸ
* long y : Y��ɸ
* long height : �⤵
* return : �����Ԥ���ɬ�פ�ͭ�뤫?
***************************************************************/

bool_t	vfx_spell_conflagration_sub( long x, long y, long height )
{
	pos_t	*draw;
	bool_t	flg_wait;
	long	i;

	flg_wait = FALSE;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return FALSE;

	for( i = 0; i < height; i++ ){
		long	sx, sy;

		/* ����åԥ� */

		sx = x - (draw->x * 2);
		sy = y - draw->y;
		sy = sy - i;

		/* ���� */

		if( print_vfx( FALSE, sx, sy, MSG_S, "**" ) )
			flg_wait = TRUE;
	}

	for( ; i < ANIM_CONFLAGRATION_HEIGHT; i++ ){
		long	mx, my;

		/* ����åԥ� */

		mx = x / 2;
		my = y - i;
		if( !clip_pos( mx, my ) )
			continue;

		/* �õ� */

		flg_wait = TRUE;
		draw_map_force( mx, my, 1, 1 );
	}

	return flg_wait;
}

/***************************************************************
* �Ͽ̤νѤ� VFX ������
***************************************************************/

void	vfx_spell_earthquake( void )
{
	pos_t	*draw, pre_draw, base_draw;
	long	x, y;
	time_t	bgn_time;
	long	i;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;
	pre_draw.x = draw->x;
	pre_draw.y = draw->y;

	base_draw.x = draw->x;
	base_draw.y = draw->y;
	if( base_draw.x < 1 )
		base_draw.x = 1;
	if( base_draw.y < 1 )
		base_draw.y = 1;
	if( base_draw.x > (MAP_MAX_X - (get_map_col() / 2) - 1) )
		base_draw.x = (MAP_MAX_X - (get_map_col() / 2) - 1);
	if( base_draw.y > (MAP_MAX_Y - get_map_row() - 1) )
		base_draw.y = (MAP_MAX_Y - get_map_row() - 1);

	bgn_time = time( NULL );

	for( i = 0; i < LOOP_MAX_100; i++ ){
		/* ���̤��ɤ餹 */

		x = base_draw.x + randm( 5 ) - 2;
		y = base_draw.y + randm( 5 ) - 2;
		if( x < 0 )
			x = 0;
		if( y < 0 )
			y = 0;
		if( x > MAP_MAX_X - get_map_col() / 2 )
			x = MAP_MAX_X - get_map_col() / 2;
		if( y > MAP_MAX_Y - get_map_row() )
			y = MAP_MAX_Y - get_map_row();
		draw->x = x;
		draw->y = y;

		redraw_map_force();
		call_pcg_dun_scroll( draw->x, draw->y );

		wait_clock( ANIM_EARTHQUAKE_FRAME_N );

		if( difftime( time( NULL ), bgn_time )
				> ANIM_EARTHQUAKE_SEC ){
			break;
		}
	}

	/* ���̤ΰ��֤򸵤��᤹ */

	draw->x = pre_draw.x;
	draw->y = pre_draw.y;
	call_pcg_dun_scroll( draw->x, draw->y );

	redraw_map_force();
}

/***************************************************************
* ����νѤ� VFX ������
* long arw_n : ����ο�
* pos_t end[] : ��λ����
***************************************************************/

void	vfx_spell_thunder( long arw_n, pos_t end[] )
{
	static pos_t	thunder[VFX_ARW_MAX_N][ANIM_THUNDER_HEIGHT];
	pos_t	*draw;
	gui_vfx_t	*gui_vfx[VFX_ARW_MAX_N];
	rate_t	vfx_rate;
	long	i, j;

	if( end == NULL )
		return;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	if( arw_n > VFX_ARW_MAX_N )
		arw_n = VFX_ARW_MAX_N;

	/* ��ɸ���֤��鳫�ϰ��֤ޤǡ��ջ����ư��֤���Ƥ��� */

	for( i = 0; i < arw_n; i++ ){
		long	sx, sy;

		sx = end[i].x - (draw->x * 2);
		sy = end[i].y - draw->y;
		for( j = ANIM_THUNDER_HEIGHT - 1; j >= 0; j-- ){
			thunder[i][j].x = sx;
			thunder[i][j].y = sy;

			/* ���������ˤ��� */
			sx += randm( 3 ) - 1;
			sy--;
		}

		/* GUI */

		gui_vfx[i] = alloc_gui_vfx_ninja(
				SPELL_KIND_THUNDERCLOUD );
	}

	/* ���� */

	for( j = 0; j < ANIM_THUNDER_HEIGHT; j++ ){
		bool_t	flg_wait;

		flg_wait = FALSE;

		for( i = 0; i < arw_n; i++ ){
			char	*str;

			if( j <= 0 ){
				/* ���ϰ��֤�ʸ�� */
				str = "~";
			} else if( j >= ANIM_THUNDER_HEIGHT - 1 ){
				/* ��ɸ���֤�ʸ�� */
				str = "*";
			} else {
				long	dx;

				/* �ޤ�����ʸ�� */
				dx = thunder[i][j].x - thunder[i][j - 1].x;
				if( dx >= +1 )
					str = "\\";
				else if( dx <= -1 )
					str = "/";
				else
					str = "|";
			}

			/* ���� */

			if( print_vfx( FALSE,
					thunder[i][j].x,
					thunder[i][j].y,
					MSG_S, str ) ){
				flg_wait = TRUE;
			}
		}

		/* GUI ���� */

		for( i = 0; i < arw_n; i++ )
			draw_gui_vfx_spell_thunder( gui_vfx[i], &(end[i]) );

		/* �Ԥ� */

		if( flg_wait )
			wait_clock( ANIM_THUNDER_FRAME_N );
	}

	vfx_rate = 1;
	for( j = 0; j < _100_PERCENT; j += vfx_rate ){
		for( i = 0; i < arw_n; i++ )
			draw_gui_vfx_spell_thunder( gui_vfx[i], &(end[i]) );

		wait_clock( ANIM_THUNDER_CLR_FRAME_N
				* vfx_rate / _100_PERCENT );
	}

	/* GUI �õ� */

	clr_gui_vfx_all();
	for( i = 0; i < arw_n; i++ )
		free_gui_vfx( gui_vfx[i] );

	/* �õ� */

	redraw_map_force();
}

/***************************************************************
* ����νѤ� VFX ������
* long arw_n : ����ο�
* pos_t end[] : ��λ����
***************************************************************/

void	draw_gui_vfx_spell_thunder( gui_vfx_t *gui_vfx, pos_t *pos )
{
	long	gx, gy, gw, gh;

	gui_vfx->anim_rate += GUI_VFX_ANIM_RATE;
	gui_vfx->anim_rate %= _100_PERCENT;

	set_gui_vfx( pos->x / 2, pos->y, gui_vfx );

	gw = 7;
	gh = 10;
	gx = (pos->x / 2) - (gw / 2);
	gy = pos->y - (gh - 1);
	call_pcg_dun_draw( gx, gy, gw, gh, TRUE );
}

/***************************************************************
* ����νѤ� VFX ������
***************************************************************/

void	vfx_spell_inundation( void )
{
	static char	head[SCREEN_SIZE_MAX_COL + 1];
	static char	wave[SCREEN_SIZE_MAX_COL + 1];
	gui_vfx_t	*gui_vfx;
	rate_t	vfx_rate;
	pos_t	*draw;
	long	i, j;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	for( i = 0; i < get_map_col(); i++ )
		head[i] = '~';
	head[i] = '\0';

	/* GUI */

	gui_vfx = alloc_gui_vfx_ninja( SPELL_KIND_INUNDATION );

	for( i = 0; i < get_map_row(); i++ ){
		long	y;

		for( j = 0; j < get_map_col(); j++ ){
			if( per_randm( 3 ) )
				wave[j] = '~';
			else
				wave[j] = ' ';
		}
		wave[j] = '\0';

		y = i;
		print_vfx( FALSE, 0, y, MSG_S, wave );

		/* ���� */

		y = i + 1;
		if( y < get_map_row() )
			print_vfx( FALSE, 0, y, MSG_S, head );

		/* GUI ���� */

		gui_vfx->anim_rate += GUI_VFX_ANIM_RATE;
		gui_vfx->anim_rate %= _100_PERCENT;

		for( j = 0; j < get_map_col(); j++ )
			set_gui_vfx( draw->x + j, draw->y + i, gui_vfx );

		call_pcg_dun_draw( draw->x, draw->y,
				get_map_col(), i + 1, TRUE );

		/* �Ԥ� */

		wait_clock( ANIM_INUNDATION_FRAME_N );
	}

	vfx_rate = 2;
	for( i = 0; i < _100_PERCENT; i += vfx_rate ){
		gui_vfx->anim_rate += GUI_VFX_ANIM_RATE;
		gui_vfx->anim_rate %= _100_PERCENT;

		call_pcg_dun_draw( draw->x, draw->y,
				get_map_col(), get_map_row(), TRUE );

		wait_clock( ANIM_INUNDATION_CLR_FRAME_N
				* vfx_rate / _100_PERCENT );
	}

	/* GUI �õ� */

	clr_gui_vfx_all();
	free_gui_vfx( gui_vfx );

	/* �õ� */

	redraw_map_force();
}

/***************************************************************
* ����ҥåȤ� VFX ������
* chr_t *chr : ����饯��
* long x : X��ɸ
* long y : Y��ɸ
***************************************************************/

void	vfx_hit( chr_t *chr, long x, long y )
{
	long	r;
	long	len;
	pos_t	bgn, end;
	long	frame, clr_frame;
	curs_attr_t	prev_attr;
	gui_vfx_t	*gui_vfx;
	rate_t	anim_rate;

	if( chr == NULL )
		return;
	if( !clip_draw_pos( x, y ) )
		return;

	/* ���襢�ȥ�ӥ塼�Ȥ����� */

	get_vfx_attr( &prev_attr );

	if( is_mnstr( chr ) ){
		if( !chk_flg( get_flg_vfx_mnstr(),
				FLG_VFX_MNSTR_DAM ) ){
			/* �ե��륿�����ݤ��äƤ���ʤ����褷�ʤ� */
			return;
		}
		set_vfx_attr_n( CURS_ATTR_N_FX_MNSTR_MINUS );
	} else {
		if( !chk_flg( get_flg_vfx_mbr(),
				FLG_VFX_MBR_DAM ) ){
			/* �ե��륿�����ݤ��äƤ���ʤ����褷�ʤ� */
			return;
		}
		set_vfx_attr_n( CURS_ATTR_N_FX_MBR_MINUS );
	}

	/* ���� */

	r = ANIM_HIT_R;
	len = r * 2 + 1;
	len += 4;

	if( g_flg_cui ){
		frame = ANIM_HIT_FRAME_N;
		clr_frame = ANIM_HIT_CLR_FRAME_N;

		bgn.x = x * 2 + r;
		bgn.y = y - r;
		end.x = x * 2 - r;
		end.y = y + r;

		vfx_arw_line( &bgn, &end, NULL, STR_ANIM_HIT,
				len, frame, clr_frame, FALSE );

		wait_clock( ANIM_HIT_WAIT_CLOCK );
	}
	gui_vfx = NULL;
	while( g_flg_gui ){
		gui_vfx = alloc_gui_vfx_bash( FALSE );
		if( gui_vfx == NULL )
			break;
		set_gui_vfx( x, y, gui_vfx );

		for( anim_rate = 0; anim_rate < _100_PERCENT;
				anim_rate += GUI_VFX_ANIM_RATE ){
			gui_vfx->anim_rate = anim_rate;
			call_pcg_dun_draw( x - r, y - r,
					r * 2, r * 2, TRUE );

			wait_clock( ANIM_HIT_WAIT_CLOCK
					* GUI_VFX_ANIM_RATE
					/ _100_PERCENT );
		}

		break;
	}

	/* �õ� */

	set_vfx_attr( &prev_attr );

	clr_gui_vfx_all();
	if( g_flg_gui )
		free_gui_vfx( gui_vfx );

	draw_map_force( x - ((r + 1) / 2), y - r,
			r + 1, r * 2 + 1 );
}

/***************************************************************
* ����ƥ����롦�ҥåȤ� VFX ������
* chr_t *chr : ����饯��
* long x : X��ɸ
* long y : Y��ɸ
***************************************************************/

void	vfx_crtcl( chr_t *chr, long x, long y )
{
	long	r;
	long	len;
	pos_t	bgn, end;
	long	frame, clr_frame;
	curs_attr_t	prev_attr;
	gui_vfx_t	*gui_vfx;
	rate_t	anim_rate;

	if( chr == NULL )
		return;
	if( !clip_draw_pos( x, y ) )
		return;

	/* ���襢�ȥ�ӥ塼�Ȥ����� */

	get_vfx_attr( &prev_attr );

	if( is_mnstr( chr ) ){
		if( !chk_flg( get_flg_vfx_mnstr(),
				FLG_VFX_MNSTR_CRTCL ) ){
			/* �ե��륿�����ݤ��äƤ���ʤ����褷�ʤ� */
			return;
		}
		set_vfx_attr_n( CURS_ATTR_N_FX_MNSTR_CRTCL );
	} else {
		if( !chk_flg( get_flg_vfx_mbr(),
				FLG_VFX_MBR_CRTCL ) ){
			/* �ե��륿�����ݤ��äƤ���ʤ����褷�ʤ� */
			return;
		}
		set_vfx_attr_n( CURS_ATTR_N_FX_MBR_CRTCL );
	}

	/* ���� */

	r = ANIM_CRTCL_R;
	len = r * 2 + 1;
	len += 4;

	if( g_flg_cui ) {
		frame = ANIM_CRTCL_FRAME_N;
		clr_frame = ANIM_CRTCL_CLR_FRAME_N;

		bgn.x = x * 2 + r;
		bgn.y = y - r;
		end.x = x * 2 - r;
		end.y = y + r;
		vfx_arw_line( &bgn, &end, NULL, STR_ANIM_CRTCL_1,
				len, frame, clr_frame, FALSE );

		bgn.x = x * 2 - r;
		bgn.y = y - r;
		end.x = x * 2 + r;
		end.y = y + r;
		vfx_arw_line( &bgn, &end, NULL, STR_ANIM_CRTCL_2,
				len, frame, clr_frame, FALSE );

		wait_clock( ANIM_CRTCL_WAIT_CLOCK );
	}
	gui_vfx = NULL;
	while( g_flg_gui ) {
		gui_vfx = alloc_gui_vfx_bash( TRUE );
		if( gui_vfx == NULL )
			break;
		set_gui_vfx( x, y, gui_vfx );

		for( anim_rate = 0; anim_rate < _100_PERCENT;
				anim_rate += GUI_VFX_ANIM_RATE ){
			gui_vfx->anim_rate = anim_rate;
			call_pcg_dun_draw( x - r, y - r,
					r * 2, r * 2, TRUE );

			wait_clock( ANIM_CRTCL_WAIT_CLOCK
					* GUI_VFX_ANIM_RATE
					/ _100_PERCENT );
		}

		break;
	}

	/* �õ� */

	set_vfx_attr( &prev_attr );

	clr_gui_vfx_all();
	if( g_flg_gui )
		free_gui_vfx( gui_vfx );

	draw_map_force( x - ((r + 1) / 2), y - r,
			r + 1, r * 2 + 1 );
}

/***************************************************************
* Ǧ�Ԥμ��ڤ�� VFX ������
* chr_t *chr : ����饯��
* long x : X��ɸ
* long y : Y��ɸ
***************************************************************/

void	vfx_ninja_crtcl( chr_t *chr, long x, long y )
{
	blast_t	*blast;
	gui_vfx_t	*gui_vfx;

	if( chr == NULL )
		return;
	if( !clip_draw_pos( x, y ) )
		return;

	/* ���� */

	/* GUI */
	gui_vfx = alloc_gui_vfx_blast( BLAST_KIND_NINJA_CRTCL );

	blast = get_blast( BLAST_KIND_NINJA_CRTCL );
	draw_blast( chr->kind, x, y, blast, gui_vfx, NULL );

	/* �Ԥ� */

	wait_clock( ANIM_FRAME_N_BLAST_NINJA_CRTCL );

	/* �õ� */

	/* GUI */
	clr_gui_vfx_all();
	free_gui_vfx( gui_vfx );

	call_pcg_dun_redraw( TRUE );

	redraw_map_force();
}

/***************************************************************
* VFX �θ��ߤΥ��ȥ�ӥ塼�Ȥ��֤�
* curs_attr_t *attr : ���ȥ�ӥ塼�Ȥ��֤�
***************************************************************/

void	get_vfx_attr( curs_attr_t *attr )
{
	*attr = g_vfx_attr;
}

/***************************************************************
* VFX �θ��ߤΥ��ȥ�ӥ塼�Ȥ����ꤹ��
* curs_attr_t *attr : ���ꤹ�륢�ȥ�ӥ塼��
***************************************************************/

void	set_vfx_attr( const curs_attr_t *attr )
{
	g_vfx_attr = *attr;
}

/***************************************************************
* �ֹ�ǻ��ꤷ�ơ� VFX �θ��ߤΥ��ȥ�ӥ塼�Ȥ����ꤹ��
* curs_attr_n_t n : ���ꤹ�륢�ȥ�ӥ塼�Ȥ��ֹ�
***************************************************************/

void	set_vfx_attr_n( curs_attr_n_t n )
{
	curs_attr_t	*ls_attr;

	ls_attr = get_curs_attr();
	if( ls_attr == NULL )
		return;

	g_vfx_attr = ls_attr[n];
	g_vfx_attr.attr &= ~(A_REVERSE);
}

/***************************************************************
* ����ƻ��� VFX ������
* chr_kind_t kind : ����饯���μ���
* pos_t bgn[] : ���ϰ���
* pos_t end[] : ��λ����
* gui_vfx_t *gui_vfx : GUI ���ե�����
* char c : ���褹��ʸ��
* long len : ������Ĺ��
***************************************************************/

void	vfx_arw(
	chr_kind_t kind,
	pos_t bgn[], pos_t end[],
	gui_vfx_t *gui_vfx,
	char c, long len
)
{
	char	str[1 + 1];
	pos_t	bgn_scrn, end_scrn;
	long	frame, clr_frame;
	curs_attr_t	prev_attr;

	/* �ե��륿�����ݤ��äƤ���ʤ����褷�ʤ� */

	if( kind == CHR_KIND_MBR )
		if( !chk_flg( get_flg_vfx_mbr(), FLG_VFX_MBR_ARW ) )
			return;
	if( kind == CHR_KIND_MNSTR )
		if( !chk_flg( get_flg_vfx_mnstr(), FLG_VFX_MNSTR_ARW ) )
			return;

	str[0] = c;
	str[1] = '\0';

	frame = ANIM_ARW_FRAME_N;
	clr_frame = ANIM_ARW_CLR_FRAME_N;

	bgn_scrn.x = bgn->x * 2;
	bgn_scrn.y = bgn->y;
	end_scrn.x = end->x * 2;
	end_scrn.y = end->y;

	/* ���� */

	get_vfx_attr( &prev_attr );
	set_vfx_attr_n( CURS_ATTR_N_VFX );

	vfx_arw_line( &bgn_scrn, &end_scrn, gui_vfx, str,
			len, frame, clr_frame, TRUE );

	set_vfx_attr( &prev_attr );
}

/***************************************************************
* 1�ܤ�����ƻ��� VFX ������
* pos_t bgn[] : ���ϰ���
* pos_t end[] : ��λ����
* gui_vfx_t *gui_vfx : GUI ���ե�����
* const char *str : ���褹��ʸ����
* long len : ������Ĺ��
* long frame : ����Υե졼���
* long clr_frame : �õ�Υե졼���
* bool_t flg_clr : �Ǹ�˾õ�뤫?
***************************************************************/

void	vfx_arw_line(
	pos_t bgn[], pos_t end[],
	gui_vfx_t *gui_vfx,
	const char *str, long len,
	long frame, long clr_frame, bool_t flg_clr
)
{
	vfx_arw_mul_line( 1, bgn, end, gui_vfx, str, len,
			frame, clr_frame, flg_clr );
}

/***************************************************************
* ʣ��������ƻ��� VFX ������
* long arw_n : ���褹���ܿ�
* pos_t bgn[] : ���ϰ���
* pos_t end[] : ��λ����
* gui_vfx_t *gui_vfx : GUI ���ե�����
* const char *str : ���褹��ʸ����
* long len : ������Ĺ��
* long frame : ����Υե졼���
* long clr_frame : �õ�Υե졼���
* bool_t flg_clr : �Ǹ�˾õ�뤫?
***************************************************************/

void	vfx_arw_mul_line(
	long arw_n, pos_t bgn[], pos_t end[],
	gui_vfx_t *gui_vfx,
	const char *str, long len,
	long frame, long clr_frame, bool_t flg_clr
)
{
	long	i, j, k;
	static long	n[VFX_ARW_MAX_N], m[VFX_ARW_MAX_N];
	static long	clr_m[VFX_ARW_MAX_N], pre_m[VFX_ARW_MAX_N];
	static long	x[VFX_ARW_MAX_N][ANIM_LINE_LEN + 1];
	static long	y[VFX_ARW_MAX_N][ANIM_LINE_LEN + 1];
	static bool_t	flg_x[VFX_ARW_MAX_N], flg_y[VFX_ARW_MAX_N];
	long	len_clr;
	bool_t	flg_wait;

	if( bgn == NULL )
		return;
	if( end == NULL )
		return;

	/* �ϰϥ����å� */

	if( arw_n > VFX_ARW_MAX_N )
		arw_n = VFX_ARW_MAX_N;
	if( len > ANIM_LINE_LEN )
		len = ANIM_LINE_LEN;

	/* ������Ԥ����֤ǥե졼�����Ĵ�� */

	frame = frame * get_vfx_wait() / _100_PERCENT;
	if( frame < 1 )
		frame = 1;

	clr_frame = clr_frame * get_vfx_wait() / _100_PERCENT;
	if( clr_frame < 1 )
		clr_frame = 1;

	len_clr = str_len_draw( str ) / 2 + 1;

	for( j = 0; j < arw_n; j++ ){
		m[j] = 0;
		n[j] = 0;

		flg_x[j] = (labs( end[j].x - bgn[j].x )
				>= labs( end[j].y - bgn[j].y ));
		flg_y[j] = (labs( end[j].x - bgn[j].x )
				<= labs( end[j].y - bgn[j].y ));
		x[j][n[j]] = bgn[j].x;
		y[j][n[j]] = bgn[j].y;
	}

	/* ���� */

	for( i = 0; i <= frame; i++ ){
		flg_wait = FALSE;

		for( j = 0; j < arw_n; j++ ){
			long	dx, dy, sx, sy, nx, ny, xx, yy;

			dx = labs( end[j].x - bgn[j].x );
			dy = labs( end[j].y - bgn[j].y );
			sx = sgn_l( end[j].x - bgn[j].x );
			sy = sgn_l( end[j].y - bgn[j].y );

			nx = bgn[j].x;
			nx += (dx * i / frame) * sx;
			ny = bgn[j].y;
			ny += (dy * i / frame) * sy;
			do {
				if( flg_x[j] && (nx == x[j][n[j]]) )
					break;
				if( flg_y[j] && (ny == y[j][n[j]]) )
					break;

				m[j]++;
				n[j] = m[j] % (ANIM_LINE_LEN + 1);
				x[j][n[j]] = nx;
				y[j][n[j]] = ny;
				break;
			} while( 0 );

			if( clip_draw_pos( nx / 2, ny ) )
				flg_wait = TRUE;

			xx = x[j][n[j]] - (map_draw_pos.x * 2);
			yy = y[j][n[j]] - map_draw_pos.y;
			xx += WIN_MAP_DRAW_MIN_X;
			yy += WIN_MAP_DRAW_MIN_Y;

			/* GUI */
			set_gui_vfx( nx / 2, ny, gui_vfx );
			call_pcg_dun_draw( (nx / 2) - 1, ny - 1,
					3, 3, TRUE );

			curs_attrset_dir( &g_vfx_attr );
			print_vfx( FALSE, xx, yy, MSG_S, str );
			curs_attrset_dflt();

			if( flg_clr ){
				/* len���Ĺ���ʤä�����ָ���ä� */
				if( (m[j] - len) >= 0 ){
					long	n2;
					long	xx, yy;

					n2 = m[j] - len;
					n2 %= ANIM_LINE_LEN + 1;
					xx = x[j][n2] / 2;
					yy = y[j][n2];

					/* GUI */
					clr_gui_vfx( xx, yy );
					call_pcg_dun_draw( xx - 1, yy - 1,
							3, 3, TRUE );

					if( clip_draw_pos( xx, yy ) ){
						draw_map_force( xx, yy,
								len_clr, 1 );
						flg_wait = TRUE;
					}
				}
			}
		}

		call_pcg_dun_draw_turn( FALSE );

		if( flg_wait ){
			wait_frame( 1 );
		}
	}

	if( !flg_clr )
		return;	/* �õ�ʤ��ǽ�λ */

	for( j = 0; j < arw_n; j++ ){
		if( m[j] < len )
			clr_m[j] = m[j];
		else
			clr_m[j] = len;
		pre_m[j] = 0;
	}

	/* �õ� */

	for( ; i <= frame + clr_frame; i++ ){
		flg_wait = FALSE;
		for( j = 0; j < arw_n; j++ ){
			long	tmp_m;

			tmp_m = clr_m[j] * i / (frame + clr_frame);
			if( tmp_m > pre_m[j] ){
				pre_m[j]++;
				m[j]++;

				if( (m[j] - len) >= 0 ){
					long	n2;
					long	xx, yy;

					n2 = m[j] - len;
					n2 %= ANIM_LINE_LEN + 1;
					xx = x[j][n2] / 2;
					yy = y[j][n2];

					/* GUI */
					clr_gui_vfx( xx, yy );
					call_pcg_dun_draw( xx - 1, yy - 1,
							3, 3, TRUE );

					if( clip_draw_pos( xx, yy ) ){
						draw_map_force( xx, yy,
								len_clr, 1 );
						flg_wait = TRUE;
					}
				}
			}
		}

		if( flg_wait ){
			wait_frame( 1 );
		}
	}
	for( j = 0; j < arw_n; j++ ){
		for( k = 0; k < len + 1; k++ ){
			draw_map_force( x[j][k] / 2, y[j][k], len_clr, 1 );
		}
	}

	/* GUI */
	clr_gui_vfx_all();
	call_pcg_dun_redraw( TRUE );
}

/***************************************************************
* HP �� MP ���ο����� VFX ������
* chr_t *p : ����饯��
* long n : ���褹�����
***************************************************************/

void	vfx_num( chr_t *p, long n )
{
	if( p == NULL )
		return;

	if( is_mbr( p ) ){

		/* �ե��륿�����ݤ��äƤ���ʤ����褷�ʤ� */

		if( n <= -1 ){
			if( !chk_flg( get_flg_vfx_mbr(),
					FLG_VFX_MBR_DAM ) ){
				return;
			}
		} else if( n >= +1 ){
			if( !chk_flg( get_flg_vfx_mbr(),
					FLG_VFX_MBR_CURE ) ){
				return;
			}
		} else {
			if( !chk_flg( get_flg_vfx_mbr(),
					FLG_VFX_MBR_CURE ) ){
				return;
			}
		}

		/* ���� */

		if( g_flg_sync_vfx_num )
			p->work.sync_vfx_num += n;
		else
			draw_num( p->x, p->y, n, p );
	}

	if( p->kind == CHR_KIND_MNSTR ){

		/* �ե��륿�����ݤ��äƤ���ʤ����褷�ʤ� */

		if( n <= -1 ){
			if( !chk_flg( get_flg_vfx_mnstr(),
					FLG_VFX_MNSTR_DAM ) ){
				return;
			}
		} else if( n >= +1 ){
			if( !chk_flg( get_flg_vfx_mnstr(),
					FLG_VFX_MNSTR_CURE ) ){
				return;
			}
		} else {
			if( !chk_flg( get_flg_vfx_mnstr(),
					FLG_VFX_MNSTR_CURE ) ){
				return;
			}
		}

		/* ���� */

		if( g_flg_sync_vfx_num )
			p->work.sync_vfx_num += n;
		else
			draw_num( p->x, p->y, n, p );
	}
}

/***************************************************************
* ������ VFX �ΰ�������ν���
***************************************************************/

void	bgn_sync_vfx_num( void )
{
	party_t	*pty = get_party();
	pet_t	**party_pet = get_party_pet();
	mnstr_t	*mns_head, *mns_p;
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( pty->mbr[i] == NULL )
			continue;

		pty->mbr[i]->work.sync_vfx_num = 0;
		pty->mbr[i]->work.sync_vfx_x = pty->mbr[i]->x;
		pty->mbr[i]->work.sync_vfx_y = pty->mbr[i]->y;
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == NULL )
			continue;

		party_pet[i]->work.sync_vfx_num = 0;
		party_pet[i]->work.sync_vfx_x = party_pet[i]->x;
		party_pet[i]->work.sync_vfx_y = party_pet[i]->y;
	}

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next; mns_p != NULL; mns_p = mns_p->next ){
		if( mns_p == mns_head )
			break;

		mns_p->work.sync_vfx_num = 0;
		mns_p->work.sync_vfx_x = mns_p->x;
		mns_p->work.sync_vfx_y = mns_p->y;
	}

	g_flg_sync_vfx_num = TRUE;
}

/***************************************************************
* ������ VFX �ΰ�������
***************************************************************/

void	end_sync_vfx_num( void )
{
	long	len;
	long	frame;
	long	idx;

	if( !g_flg_sync_vfx_num )
		return;

	len = get_draw_num_sync_max_len();
	frame = get_draw_num_frame( len );

	for( idx = -1; idx < len + 1; idx++ ){
		if( draw_num_sync( idx ) )
			wait_clock( frame );
	}

	/* �õ� */
	redraw_map_force();

	g_flg_sync_vfx_num = FALSE;
}

/***************************************************************
* ������ VFX ���Ԥ��ե졼���׻�
* long len : ������ʸ�����Ĺ��
***************************************************************/

long	get_draw_num_frame( long len )
{
	long	frame;

	/* ������Ԥ����֤ǥե졼�����Ĵ�� */

	frame = ANIM_NUM_FRAME_N;
	frame = frame * get_vfx_wait() / _100_PERCENT;

	/* ʸ�����Ĺ���ǥե졼�����Ĵ�� */

	frame /= len + 2;
	if( frame < 1 )
		frame = 1;

	return frame;
}

/***************************************************************
* ������ VFX ��ʸ����κ���Ĺ��׻�
* return : ������ʸ�����Ĺ��
***************************************************************/

long	get_draw_num_sync_max_len( void )
{
	party_t	*pty = get_party();
	pet_t	**party_pet = get_party_pet();
	mnstr_t	*mns_head, *mns_p;
	long	n;
	char	buf[32 + 1];
	long	len, max_len;
	long	i;

	max_len = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( pty->mbr[i] == NULL )
			continue;

		n = pty->mbr[i]->work.sync_vfx_num;
		if( n == 0 )
			continue;

		sn_printf( buf, 32, "%-+ld", n );
		len = str_len_std( buf );
		max_len = max_l( len, max_len );
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == NULL )
			continue;

		n = party_pet[i]->work.sync_vfx_num;
		if( n == 0 )
			continue;

		sn_printf( buf, 32, "%-+ld", n );
		len = str_len_std( buf );
		max_len = max_l( len, max_len );
	}

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next; mns_p != NULL; mns_p = mns_p->next ){
		if( mns_p == mns_head )
			break;

		n = mns_p->work.sync_vfx_num;
		if( n == 0 )
			continue;

		sn_printf( buf, 32, "%-+ld", n );
		len = str_len_std( buf );
		max_len = max_l( len, max_len );
	}

	return max_len;
}

/***************************************************************
* ���ǤĿ����� VFX ������ (������饯��)
* return : �����ϰ�����ä���?
***************************************************************/

bool_t	draw_num_sync( long idx )
{
	party_t	*pty = get_party();
	pet_t	**party_pet = get_party_pet();
	mnstr_t	*mns_head, *mns_p;
	long	n;
	long	map_x, map_y;
	bool_t	flg_draw;
	long	i;

	flg_draw = FALSE;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( pty->mbr[i] == NULL )
			continue;

		n = pty->mbr[i]->work.sync_vfx_num;
		if( n == 0 )
			continue;
		map_x = pty->mbr[i]->work.sync_vfx_x;
		map_y = pty->mbr[i]->work.sync_vfx_y;
		if( clip_draw_pos( map_x, map_y ) )
			flg_draw = TRUE;

		draw_num_x_1( map_x, map_y, n, idx, pty->mbr[i] );
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		if( party_pet[i] == NULL )
			continue;

		n = party_pet[i]->work.sync_vfx_num;
		if( n == 0 )
			continue;
		map_x = party_pet[i]->work.sync_vfx_x;
		map_y = party_pet[i]->work.sync_vfx_y;
		if( clip_draw_pos( map_x, map_y ) )
			flg_draw = TRUE;

		draw_num_x_1( map_x, map_y, n, idx, party_pet[i] );
	}

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next; mns_p != NULL; mns_p = mns_p->next ){
		if( mns_p == mns_head )
			break;

		n = mns_p->work.sync_vfx_num;
		if( n == 0 )
			continue;
		map_x = mns_p->work.sync_vfx_x;
		map_y = mns_p->work.sync_vfx_y;
		if( clip_draw_pos( map_x, map_y ) )
			flg_draw = TRUE;

		draw_num_x_1( map_x, map_y, n, idx, mns_p );
	}

	return flg_draw;
}

/***************************************************************
* ���ǤĿ����� VFX ������
* long map_x : X��ɸ
* long map_y : Y��ɸ
* long n : ���褹�����
* chr_t *chr : ����饯��
***************************************************************/

void	draw_num( long map_x, long map_y, long n, chr_t *chr )
{
	char	buf[32 + 1];
	long	len;
	long	frame;
	long	idx;

	sn_printf( buf, 32, "%-+ld", n );
	len = str_len_std( buf );

	frame = get_draw_num_frame( len );

	for( idx = -1; idx < len + 1; idx++ ){
		draw_num_x_1( map_x, map_y, n, idx, chr );

		if( clip_draw_pos( map_x, map_y ) )
			wait_clock( frame );
	}

	/* �õ� */
	draw_map_force( map_x, map_y - 2, (len + 1) / 2, 2 );
}

/***************************************************************
* ���ǤĿ����� VFX ������ (1 �Ĥ���)
* long map_x : X��ɸ
* long map_y : Y��ɸ
* long n : ���褹�����
* long idx : ���ʤ�ķ�;�ä����褵���ʸ���Υ���ǥå���
* chr_t *chr : ����饯��
***************************************************************/

void	draw_num_x_1(
	long map_x, long map_y,
	long n, long idx,
	chr_t *chr
)
{
	char	buf[32 + 1], s1[32 + 1], s2[32 + 1];
	long	len;
	long	scrn_x, scrn_y;
	long	j;

	if( !clip_draw_pos( map_x, map_y ) )
		return;

	scrn_x = (map_x - map_draw_pos.x) * 2;
	scrn_y = map_y - map_draw_pos.y;

	/* ʸ��������Ǥ����� */

	sn_printf( buf, 32, "%-+ld", n );
	len = str_len_std( buf );

	for( j = 0; j < len; j++ ){
		if( j == idx ){
			s1[j] = buf[j];
			s2[j] = ' ';
		} else {
			s1[j] = ' ';
			s2[j] = buf[j];
		}
	}
	s1[len] = '\0';
	s2[len] = '\0';

	/* ���� */

	curs_attrset_chr( chr, n, FALSE );
	print_vfx( TRUE, scrn_x, scrn_y - 2, MSG_S, s1 );

	curs_attrset_chr( chr, n, FALSE );
	print_vfx( TRUE, scrn_x, scrn_y - 1, MSG_S, s2 );

	curs_attrset_dflt();
}

/***************************************************************
* ��٥�Υ��åפȥ������ VFX ������
* long map_x : X��ɸ
* long map_y : Y��ɸ
* long n : ���褹�����
* chr_t *chr : ����饯��
***************************************************************/

void	draw_lev_up( long map_x, long map_y, long n, chr_t *chr )
{
	static char	buf[WIN_MSG_DRAW_WIDTH + 1];
	static char	s1[WIN_MSG_DRAW_WIDTH + 1];
	static char	s2[WIN_MSG_DRAW_WIDTH + 1];
	long	len;
	long	scrn_x, scrn_y;
	long	i, j;
	long	frame;

	if( !clip_draw_pos( map_x, map_y ) )
		return;

	/* ������Ԥ����֤ǥե졼�����Ĵ�� */

	frame = ANIM_LEV_UP_FRAME_N;
	frame = frame * get_vfx_wait() / _100_PERCENT;
	if( frame < 1 )
		frame = 1;

	/* ���褹��ʸ��������� */

	len = sizeof( buf ) / sizeof( buf[0] ) - 1;
	if( n < 0 )
		str_nz_cpy( buf, MSG_VFX_LEV_DOWN, len );
	else
		str_nz_cpy( buf, MSG_VFX_LEV_UP, len );
	len = str_len_std( buf );

	/* ����åԥ� */

	scrn_x = (map_x - map_draw_pos.x) * 2;
	scrn_y = map_y - map_draw_pos.y;

	/* ʸ��������Ǥ����� */

	curs_attrset_chr( chr, n, FALSE );
	for( i = -1; i < len + 1; i++ ){
		for( j = 0; j < len; j++ ){
			if( j <= i ){
				s1[j] = buf[j];
				s2[j] = ' ';
			} else {
				s1[j] = ' ';
				s2[j] = buf[j];
			}
		}
		s1[len] = '\0';
		s2[len] = '\0';

		/* ���� */

		if( g_flg_text_mode )
			curs_attrset_chr( chr, n, FALSE );
		print_vfx( TRUE, scrn_x, scrn_y - 2, MSG_S, s1 );

		if( g_flg_text_mode )
			curs_attrset_chr( chr, n, FALSE );
		print_vfx( TRUE, scrn_x, scrn_y - 1, MSG_S, s2 );

		if( clip_draw_pos( map_x, map_y ) )
			wait_clock( frame / (len + 2) );
	}
	curs_attrset_dflt();

	/* �õ� */

	draw_map_force( map_x, map_y - 2, (len + 1) / 2, 2 );
}

/***************************************************************
* ��ȯ�� VFX ������
* chr_kind_t kind, : ��ȯ������륭��饯���μ���
* long map_x : X��ɸ
* long map_y : Y��ɸ
* blast_t *p : ��ȯ�Υǡ���
* gui_vfx_t *gui_vfx : GUI ���ե�����
* char *str : ���褹����ȯ��ʸ����
***************************************************************/

void	draw_blast(
	chr_kind_t kind,
	long map_x, long map_y,
	blast_t *p,
	gui_vfx_t *gui_vfx,
	char *str
)
{
	draw_blast_sub( FALSE, kind, map_x, map_y, p, gui_vfx, str );
}

/***************************************************************
* ��ȯ�� VFX ������
* chr_kind_t kind, : ��ȯ������륭��饯���μ���
* long map_x : X��ɸ
* long map_y : Y��ɸ
* blast_t *p : ��ȯ�Υǡ���
* gui_vfx_t *gui_vfx : GUI ���ե�����
* char *str : ���褹����ȯ��ʸ����
***************************************************************/

void	draw_blast_cui(
	chr_kind_t kind,
	long map_x, long map_y,
	blast_t *p,
	gui_vfx_t *gui_vfx,
	char *str
)
{
	draw_blast_sub( TRUE, kind, map_x, map_y, p, gui_vfx, str );
}

/***************************************************************
* ��ȯ�� VFX ������
* bool_t flg_cui : CUI �Τߤ����褫?
* chr_kind_t kind, : ��ȯ������륭��饯���μ���
* long map_x : X��ɸ
* long map_y : Y��ɸ
* blast_t *p : ��ȯ�Υǡ���
* gui_vfx_t *gui_vfx : GUI ���ե�����
* char *str : ���褹����ȯ��ʸ����
***************************************************************/

void	draw_blast_sub(
	bool_t flg_cui,
	chr_kind_t kind,
	long map_x, long map_y,
	blast_t *p,
	gui_vfx_t *gui_vfx,
	char *str
)
{
	long	str_len;
	long	x, y;
	long	scrn_x, scrn_y;
	curs_attr_t	prev_attr;
	bool_t	(*func)( bool_t flg_gui, long scrn_x, long scrn_y,
			const char *s, ... );

	if( p == NULL )
		return;

	str_len = 1;
	if( str != NULL )
		str_len = str_len_draw( str );
	if( str_len < 1 )
		str_len = 1;

	/* ���襢�ȥ�ӥ塼�Ȥ����� */

	get_vfx_attr( &prev_attr );

	if( kind == CHR_KIND_MBR ){
		if( !chk_flg( get_flg_vfx_mbr(),
				FLG_VFX_MBR_CRTCL ) ){
			/* �ե��륿�����ݤ��äƤ���ʤ����褷�ʤ� */
			return;
		}
		set_vfx_attr_n( CURS_ATTR_N_FX_MBR_CRTCL );
	} else if( kind == CHR_KIND_MNSTR ){
		if( !chk_flg( get_flg_vfx_mnstr(),
				FLG_VFX_MNSTR_CRTCL ) ){
			/* �ե��륿�����ݤ��äƤ���ʤ����褷�ʤ� */
			return;
		}
		set_vfx_attr_n( CURS_ATTR_N_FX_MNSTR_CRTCL );
	} else {
		set_vfx_attr_n( CURS_ATTR_N_VFX );
	}
	curs_attrset_dir( &g_vfx_attr );

	/* ���� */

	if( flg_cui && !g_flg_text_mode )
		func = print_vfx_cui;
	else
		func = print_vfx;

	for( y = 0; y < p->yl; y++ ){
		bool_t	flg_bgn;

		flg_bgn = TRUE;
		for( x = 0; x < p->xl; x++ ){
			/* Ʃ����ʸ���ϥ����å� */

			if( p->ptn[y][x] == p->transmit_chr )
				continue;

			/* ����åԥ� */

			scrn_x = (map_x - map_draw_pos.x) * 2;
			scrn_x += x - p->xr;
			scrn_y = (map_y - map_draw_pos.y) * 1;
			scrn_y += y - p->yr;

			/* ���� */

			if( g_flg_text_mode )
				curs_attrset_dir( &g_vfx_attr );

			if( str == NULL ){
				(*func)( FALSE, scrn_x, scrn_y,
						"%c", p->ptn[y][x] );
			} else {
				if( flg_bgn || ((x % str_len) == 0) ){
					(*func)( FALSE, scrn_x, scrn_y,
							"%s", str );
				}
			}

			flg_bgn = FALSE;
		}
	}

	/* ���襢�ȥ�ӥ塼�Ȥ򥯥ꥢ */

	set_vfx_attr( &prev_attr );

	/* GUI */

	set_gui_vfx( map_x, map_y, gui_vfx );
	call_pcg_dun_draw( (map_x - p->xr - 1), (map_y - p->yr - 1),
			p->xl + 2, p->yl + 2, TRUE );
}

/***************************************************************
* �����ɽ������
* request_t *req : ����Υǡ���
***************************************************************/

void	draw_request( request_t *req )
{
	if( req == NULL )
		return;

	draw_words( NULL, MSG_S, req->msg );
}

/***************************************************************
* ����ɽ������
* const char *name : ̾��
* const char *words : ���
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	draw_words( const char *name, const char *words, ... )
{
	va_list	argptr;
	static char	buf[PRINT_WORDS_BUF_SIZ * 12 + 1];
	static char	line[PRINT_BUF_SIZ + 1];
	static char	str_win[PRINT_BUF_SIZ + 1];
	const char	*head, *tail;
	long	len;
	long	scrn_x, scrn_y;
	long	bgn_x, bgn_y;
	long	len_corner, len_v_line;
	const long	len_shadow = 2;

	va_start( argptr, words );
	vsn_printf( buf, PRINT_WORDS_BUF_SIZ, words, argptr );
	va_end( argptr );

	if( g_flg_gui )
		call_gui_words_draw( name, buf );
	if( !g_flg_cui ){
#if	!defined( D_MFC )
		/* �������Ϥ��Ԥ� */
		if( g_flg_gui )
			wait_key( FALSE );
		call_gui_words_wipe();
#endif
		return;
	}

	len = WIN_REQUEST_DRAW_WIDTH;
	scrn_x = (get_screen_col() - len) / 2;
	scrn_y = WIN_REQUEST_DRAW_MIN_Y;
	bgn_x = scrn_x;
	bgn_y = scrn_y + 1;

	/* �Ȥγ� */

	str_nz_cpy( str_win, MSG_MENU_CORNER, PRINT_BUF_SIZ );
	strncat( str_win, MSG_MENU_FRAME, len );
	str_max_n_cat( str_win, MSG_MENU_CORNER, PRINT_BUF_SIZ );
	len_corner = str_len_std( MSG_MENU_CORNER );

	/* ��ľ���� */

	len_v_line = str_len_std( MSG_MENU_V_LINE );

	/* ���դ��ȤαƤ����� */
	print_str( scrn_x - len_corner - len_shadow, scrn_y,
			MSG_MENU_CLR_FMT,
			len + len_corner + len_shadow * 2, "" );
	/* ���դ��Ȥ����� */
	print_str( scrn_x - len_corner, scrn_y, MSG_S, str_win );
	scrn_y++;

	if( name != NULL ){
		sn_printf( line, PRINT_BUF_SIZ,
				MSG_FMT_DRAW_WORDS_NAME, name );

		/* ���߹ԤαƤ����� */
		print_str( scrn_x - len_v_line - len_shadow, scrn_y,
				MSG_MENU_CLR_FMT,
				len + len_corner + len_shadow * 2, "" );
		/* ���ο�ľ���Ȥ����� */
		print_str( scrn_x - len_v_line, scrn_y,
				MSG_S, MSG_MENU_V_LINE );
		/* ���߹Ԥ����� */
		print_str( scrn_x, scrn_y, MSG_S, line );
		/* ���ο�ľ���Ȥ����� */
		print_str( scrn_x + len, scrn_y,
				MSG_S, MSG_MENU_V_LINE );
		scrn_y++;
	}

	head = buf;
	while( 1 ){
		/* 1��ʬ�ڤ�Ф� */

		tail = get_words_line( head, len );
		if( tail == NULL )
			break;
		if( head[0] == '\n' )
			head++;

		/* 1��ʬ���ԡ� */

		str_nz_cpy( line, head, tail - head );
		line[tail - head] = '\0';

		/* ���߹ԤαƤ����� */
		print_str( scrn_x - len_v_line - len_shadow, scrn_y,
				MSG_MENU_CLR_FMT,
				len + len_corner + len_shadow * 2, "" );
		/* ���ο�ľ���Ȥ����� */
		print_str( scrn_x - len_v_line, scrn_y,
				MSG_S, MSG_MENU_V_LINE );
		/* ���߹Ԥ����� */
		print_str( scrn_x, scrn_y, MSG_S, line );
		/* ���ο�ľ���Ȥ����� */
		print_str( scrn_x + len, scrn_y,
				MSG_S, MSG_MENU_V_LINE );
		scrn_y++;

		head = tail;
	}

	/* ���դ��ȤαƤ����� */
	print_str( scrn_x - len_corner - len_shadow, scrn_y,
			MSG_MENU_CLR_FMT,
			len + len_corner + len_shadow * 2, "" );
	/* ���դ��Ȥ����� */
	print_str( scrn_x - len_corner, scrn_y, MSG_S, str_win );
	scrn_y++;

	/* �ޥ����Υϥ�ɥ������ */

	call_cui_mouse_reset_handler_tab();

	call_cui_mouse_add_handler(
			TRUE,
			bgn_x, bgn_y, len, (scrn_y - bgn_y - 1),
			NULL,
			cb_cui_mouse_click_words,
			NULL,
			0, "" );

#if	!defined( D_MFC )
	/* �������Ϥ��Ԥ� */
	wait_key( FALSE );
	call_gui_words_wipe();
#endif
}

/***************************************************************
* ���Υ���å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_words( long btn, long n, const char *macro )
{
	switch( btn ){
	case 0:
		set_key_buf_char_tail( '\n' );
		return TRUE;
	case 1:
		break;
	case 2:
		set_key_buf_char_tail( '0' );
		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* ���С��Υǡ������ɽ������
* mbr_t *org : ���С��ν������Υǡ���
* mbr_t *mbr : ���С��ν�����Υǡ���
* long page_n : �ڡ���
* mbr_data_edit_kind_t edit_kind : �Խ��⡼��
***************************************************************/

void	redraw_mbr_data(
	mbr_t *org, mbr_t *mbr,
	long page_n, mbr_data_edit_kind_t edit_kind
)
{
	call_gui_chr_sheet_redraw( org, mbr );
	draw_mbr_data_all_cui( org, mbr, page_n, edit_kind );
}

/***************************************************************
* ���С������ƤΥǡ�����ɽ������
* mbr_t *org : ���С��ν������Υǡ���
* mbr_t *mbr : ���С��ν�����Υǡ���
* long page_n : �ڡ���
* mbr_data_edit_kind_t edit_kind : �Խ��⡼��
***************************************************************/

void	draw_mbr_data_all(
	mbr_t *org, mbr_t *mbr,
	long page_n, mbr_data_edit_kind_t edit_kind
)
{
	call_gui_chr_sheet_draw( org, mbr );
	draw_mbr_data_all_cui( org, mbr, page_n, edit_kind );
}

/***************************************************************
* ���С������ƤΥǡ�����ɽ������ (CUI)
* mbr_t *org : ���С��ν������Υǡ���
* mbr_t *mbr : ���С��ν�����Υǡ���
* long page_n : �ڡ���
* mbr_data_edit_kind_t edit_kind : �Խ��⡼��
***************************************************************/

void	draw_mbr_data_all_cui(
	mbr_t *org, mbr_t *mbr,
	long page_n, mbr_data_edit_kind_t edit_kind
)
{
	long	i;

	flg_draw_menu = TRUE;

	if( !g_flg_cui )
		return;

	/* �ޥ����Υϥ�ɥ��ꥻ�å� */

	call_cui_mouse_reset_handler_tab();
	g_cui_mouse_mbr_data_cur_page_n = page_n;
	g_cui_mouse_mbr_data_edit_kind = edit_kind;

	/* ���̾õ� */

	wipe_all();
	redraw_msg();
	draw_stat_bar();

	/* ���������� */
	if( flg_mbr_data_draw_v_line[page_n] ){
		for( i = 0; i < WIN_MAP_DRAW_MAX_Y + 1; i++ ){
			print_str( WIN_MAP_DRAW_MAX_X + 1, i,
					MSG_S, MSG_V_LINE );
		}
	}
	/* ���������� */
	print_str( SCREEN_MIN_X, WIN_MAP_DRAW_MAX_Y + 1,
			MSG_S, MSG_H_FRAME );

	for( i = DATA_N_NULL + 1; i < DATA_N_MAX_N; i++ ){
		data_n_t	data;

		data = (data_n_t)i;

		/* ���ߤΥڡ��������褷�ʤ��ǡ����ϥ����å� */

		if( !chk_flg( data_page_n_tab[data], (1 << page_n) ) )
			continue;

		/* ���� */

		draw_mbr_data( org, mbr, data, FALSE, edit_kind, TRUE );
	}

	/* �ޥ������ۥ����� */
	set_cui_mouse_add_handler_common_scroll();
}

/***************************************************************
* ���С��λ���Υǡ�����ɽ������
* mbr_t *org : ���С��ν������Υǡ���
* mbr_t *mbr : ���С��ν�����Υǡ���
* data_n_t n : �ǡ����λ���
* bool_t flg_rev : ȿž���褹�뤫?
* mbr_data_edit_kind_t edit_kind : �Խ��⡼��
* bool_t flg_all : ���ǡ�����ɽ����?
***************************************************************/

void	draw_mbr_data(
	mbr_t *org, mbr_t *mbr,
	data_n_t n, bool_t flg_rev,
	mbr_data_edit_kind_t edit_kind,
	bool_t flg_all
)
{
	long	max_len = DRAW_MBR_DATA_MAX_LEN;
	static char	s[DRAW_MBR_DATA_MAX_LEN + 1];
	const char	*str_utf;
	const char	*sex_name;
	const char	*class_name;
	attack_t	attack;
	long	val1, val2;
	abl_kind_t	abl_kind;
	resi_kind_t	resi_kind;
	item_t	*item_head, *item;
	long	item_n;
	equip_kind_t	eq_k;
	char	*ttl;
	char	*str_lev_up_left, *str_lev_up_right;
	long	mbr_lev_n, mbr_lev_max;
	long	org_lev_n, org_lev_max;
	const long	max_len_add_lev = DRAW_MBR_DATA_MAX_LEN_ADD_LEV;
	static char	str_add_lev[DRAW_MBR_DATA_MAX_LEN_ADD_LEV + 1];
	rate_t	resi;
	long	x, y;
	fx_t	*fx;
	long	store_light_n;
	long	i;

	/* �ǥե�����ͤ򥻥å� */

	abl_kind = ABL_KIND_HP;
	ttl = MSG_MBR_DATA_HP_TTL;
	resi_kind = RESI_KIND_MAX_N;
	x = WIN_MBR_DATA_HP_TTL_DRAW_MIN_X;
	y = WIN_MBR_DATA_HP_TTL_DRAW_MIN_Y;

	/* ʸ����Ⱥ�ɸ�򥻥å� */

	switch( n ){
	case DATA_N_NAME:
		str_utf = cut_utf_str( mbr->name, MBR_NAME_MAX_LEN );
		sn_printf( s, max_len, "%s%s", MSG_MBR_DATA_NAME_TTL,
				str_utf );
		x = WIN_MBR_DATA_NAME_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_NAME_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_FACE:
		sn_printf( s, max_len, "%s%-1c%-1c", MSG_MBR_DATA_FACE_TTL,
				mbr->face.mjr, mbr->face.mnr );
		x = WIN_MBR_DATA_FACE_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_FACE_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RACE_STR:
		if( is_mbr( mbr ) ){
			str_utf = cut_utf_str(
					get_race_str( &(mbr->race) ),
					RACE_STR_MAX_LEN );
		} else {
			str_utf = cut_utf_str(
					get_mnstr_mjr_name( mbr->face.mjr ),
					RACE_STR_MAX_LEN );
		}
		sn_printf( s, max_len, "%s%s",
				MSG_MBR_DATA_RACE_STR_TTL,
				str_utf );
		x = WIN_MBR_DATA_RACE_STR_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RACE_STR_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RACE_NAME:
		if( is_mbr( mbr ) ){
			str_utf = cut_utf_str(
					get_race_name( &(mbr->race) ),
					RACE_NAME_MAX_LEN );
		} else {
			str_utf = cut_utf_str(
					get_mnstr_name( mbr->mnstr_kind ),
					RACE_STR_MAX_LEN );
		}

		sn_printf( s, max_len, "%s%s", MSG_MBR_DATA_RACE_NAME_TTL,
				str_utf );
		x = WIN_MBR_DATA_RACE_NAME_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RACE_NAME_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_SEX:
		sex_name = get_sex_name( mbr->mnstr_kind, mbr->sex.cur );
		sn_printf( s, max_len, "%s%s",
				MSG_MBR_DATA_SEX_TTL, sex_name );
		x = WIN_MBR_DATA_SEX_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SEX_TTL_DRAW_MIN_Y;
		break;

	/**/

	case DATA_N_HP_VAL:
		sn_printf( s, max_len, "%s%*ld/%*ld", MSG_MBR_DATA_HP_VAL,
				WIN_STAT_CURE_HP_DRAW_WIDTH,
				mbr->abl.hp.n,
				WIN_STAT_MAX_HP_DRAW_WIDTH,
				mbr->abl.hp.max );
		x = WIN_MBR_DATA_HP_VAL_DRAW_MIN_X;
		y = WIN_MBR_DATA_HP_VAL_DRAW_MIN_Y;
		break;
	case DATA_N_MP_VAL:
		sn_printf( s, max_len, "%s%*ld/%*ld", MSG_MBR_DATA_MP_VAL,
				WIN_STAT_CURE_MP_DRAW_WIDTH,
				mbr->abl.mp.n,
				WIN_STAT_MAX_MP_DRAW_WIDTH,
				mbr->abl.mp.max );
		x = WIN_MBR_DATA_MP_VAL_DRAW_MIN_X;
		y = WIN_MBR_DATA_MP_VAL_DRAW_MIN_Y;
		break;

	/**/

	case DATA_N_VAL_TTL:
		strcpy( s, MSG_MBR_DATA_VAL_TTL );
		x = WIN_MBR_DATA_VAL_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_VAL_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_HIT:
		if( is_mbr( mbr ) ){
			/* ���ܹ����� */

			if( set_attack_mbr_bash( mbr, &attack, 1, TRUE ) )
				val1 = get_hit( mbr, &attack );
			else
				val1 = get_hit( mbr, NULL );

			/* ��ֹ����� */

			if( set_attack_mbr_throw( mbr, &attack, 1, TRUE ) )
				val2 = get_hit( mbr, &attack );
			else
				val2 = get_hit( mbr, NULL );

			sn_printf( s, max_len, MSG_MBR_DATA_HIT,
					MSG_MBR_DATA_HIT_TTL,
					val1, val2 );
		} else if( is_pet( mbr ) ){
			/* ���ܹ����� */

			if( set_attack_mnstr_bash( mbr, &attack, 1, TRUE ) )
				val1 = get_hit( mbr, &attack );
			else
				val1 = get_hit( mbr, NULL );

			/* ��ֹ����� */

			if( set_attack_mnstr_throw( mbr, &attack, 1, TRUE ) )
				val2 = get_hit( mbr, &attack );
			else
				val2 = get_hit( mbr, NULL );

			sn_printf( s, max_len, MSG_MBR_DATA_HIT,
					MSG_MBR_DATA_HIT_TTL,
					val1, val2 );
		}

		x = WIN_MBR_DATA_HIT_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_HIT_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_WPN_CRTCL:
		if( is_mbr( mbr ) ){
			/* ���ܥ���ƥ����빶���� */

			if( set_attack_mbr_bash( mbr, &attack, 1, TRUE ) )
				val1 = get_wpn_crtcl( mbr, &attack );
			else
				val1 = get_wpn_crtcl( mbr, NULL );

			/* ��֥���ƥ����빶���� */

			if( set_attack_mbr_throw( mbr, &attack, 1, TRUE ) )
				val2 = get_wpn_crtcl( mbr, &attack );
			else
				val2 = get_wpn_crtcl( mbr, NULL );

			sn_printf( s, max_len, MSG_MBR_DATA_WPN_CRTCL,
					MSG_MBR_DATA_WPN_CRTCL_TTL,
					val1, val2 );
		} else if( is_pet( mbr ) ){
			/* ���ܥ���ƥ����빶���� */

			if( set_attack_mnstr_bash( mbr, &attack, 1, TRUE ) )
				val1 = get_wpn_crtcl( mbr, &attack );
			else
				val1 = get_wpn_crtcl( mbr, NULL );

			/* ��֥���ƥ����빶���� */

			if( set_attack_mnstr_throw( mbr, &attack, 1, TRUE ) )
				val2 = get_wpn_crtcl( mbr, &attack );
			else
				val2 = get_wpn_crtcl( mbr, NULL );

			sn_printf( s, max_len, MSG_MBR_DATA_WPN_CRTCL,
					MSG_MBR_DATA_WPN_CRTCL_TTL,
					val1, val2 );
		}
		x = WIN_MBR_DATA_WPN_CRTCL_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_WPN_CRTCL_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_DAM:
		if( is_mbr( mbr ) ){
			/* ���ܥ��᡼�� */

			if( set_attack_mbr_bash( mbr, &attack, 1, TRUE ) )
				val1 = get_dam( mbr, &attack );
			else
				val1 = get_dam( mbr, NULL );

			/* ��֥��᡼�� */

			if( set_attack_mbr_throw( mbr, &attack, 1, TRUE ) )
				val2 = get_dam( mbr, &attack );
			else
				val2 = get_dam( mbr, NULL );

			sn_printf( s, max_len, MSG_MBR_DATA_DAM,
					MSG_MBR_DATA_DAM_TTL,
					val1, val2 );
		} else if( is_pet( mbr ) ){
			/* ���ܥ��᡼�� */

			if( set_attack_mnstr_bash( mbr, &attack, 1, TRUE ) )
				val1 = get_dam( mbr, &attack );
			else
				val1 = get_dam( mbr, NULL );

			/* ��֥��᡼�� */

			if( set_attack_mnstr_throw( mbr, &attack, 1, TRUE ) )
				val2 = get_dam( mbr, &attack );
			else
				val2 = get_dam( mbr, NULL );

			sn_printf( s, max_len, MSG_MBR_DATA_DAM,
					MSG_MBR_DATA_DAM_TTL,
					val1, val2 );
		}
		x = WIN_MBR_DATA_DAM_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_DAM_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_DEF:
		sn_printf( s, max_len, MSG_MBR_DATA_DEF,
				MSG_MBR_DATA_DEF_TTL,
				get_def( mbr ) );
		x = WIN_MBR_DATA_DEF_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_DEF_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_ARMOR_CRTCL:
		sn_printf( s, max_len, MSG_MBR_DATA_ARMOR_CRTCL,
				MSG_MBR_DATA_ARMOR_CRTCL_TTL,
				get_armor_crtcl( mbr ) );
		x = WIN_MBR_DATA_ARMOR_CRTCL_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_ARMOR_CRTCL_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_AC:
		sn_printf( s, max_len, MSG_MBR_DATA_AC,
				MSG_MBR_DATA_AC_TTL,
				get_ac( mbr ) );
		x = WIN_MBR_DATA_AC_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_AC_TTL_DRAW_MIN_Y;
		break;

	/**/

	case DATA_N_GOLD:
		sn_printf( s, max_len, "%s%s", MSG_MBR_DATA_GOLD_TTL,
				fmt_gold( get_chr_gold( mbr ) ) );
		x = WIN_MBR_DATA_GOLD_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_GOLD_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_TURN:
		strcpy( s, get_calendar_str() );
		x = WIN_MBR_DATA_TURN_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_TURN_TTL_DRAW_MIN_Y;
		break;

	/**/

	case DATA_N_STAT_TTL:
		strcpy( s, MSG_MBR_DATA_STAT_TTL );
		x = WIN_MBR_DATA_STAT_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_DEAD:
		if( chk_flg( mbr->stat, FLG_STAT_DEAD ) )
			strcpy( s, MSG_MBR_DATA_STAT_DEAD );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_DEAD_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_DEAD_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_STONE:
		if( chk_flg( mbr->stat, FLG_STAT_STONE ) )
			strcpy( s, MSG_MBR_DATA_STAT_STONE );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_STONE_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_STONE_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_PARALYZE:
		if( chk_flg( mbr->stat, FLG_STAT_PARALYZE ) )
			strcpy( s, MSG_MBR_DATA_STAT_PARALYZE );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_PARALYZE_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_PARALYZE_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_POISON:
		if( chk_flg( mbr->stat, FLG_STAT_POISON ) )
			strcpy( s, MSG_MBR_DATA_STAT_POISON );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_POISON_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_POISON_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_CONFUSION:
		if( chk_flg( mbr->stat, FLG_STAT_CONFUSION ) )
			strcpy( s, MSG_MBR_DATA_STAT_CONFUSION );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_CONFUSION_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_CONFUSION_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_BLIND:
		if( chk_flg( mbr->stat, FLG_STAT_BLIND ) )
			strcpy( s, MSG_MBR_DATA_STAT_BLIND );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_BLIND_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_BLIND_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_SLEEP:
		if( chk_flg( mbr->stat, FLG_STAT_SLEEP ) )
			strcpy( s, MSG_MBR_DATA_STAT_SLEEP );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_SLEEP_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_SLEEP_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_SILENCE:
		if( chk_flg( mbr->stat, FLG_STAT_SILENCE ) )
			strcpy( s, MSG_MBR_DATA_STAT_SILENCE );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_SILENCE_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_SILENCE_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_CAUGHT:
		if( chk_flg( mbr->stat, FLG_STAT_CAUGHT ) )
			strcpy( s, MSG_MBR_DATA_STAT_CAUGHT );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_CAUGHT_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_CAUGHT_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_FEAR:
		if( chk_flg( mbr->stat, FLG_STAT_FEAR ) )
			strcpy( s, MSG_MBR_DATA_STAT_FEAR );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_FEAR_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_FEAR_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_HALLUCINATION:
		if( chk_flg( mbr->stat, FLG_STAT_HALLUCINATION ) )
			strcpy( s, MSG_MBR_DATA_STAT_HALLUCINATION );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_HALLUCINATION_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_HALLUCINATION_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_CHARM:
		if( chk_flg( mbr->stat, FLG_STAT_CHARM ) )
			strcpy( s, MSG_MBR_DATA_STAT_CHARM );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_CHARM_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_CHARM_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_FLY:
		if( chk_flg( mbr->stat, FLG_STAT_FLY ) )
			strcpy( s, MSG_MBR_DATA_STAT_FLY );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_FLY_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_FLY_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_HUNGRY:
		if( chk_flg( mbr->stat, FLG_STAT_STARVATION ) )
			strcpy( s, MSG_MBR_DATA_STAT_STARVATION );
		else if( chk_flg( mbr->stat, FLG_STAT_HUNGRY ) )
			strcpy( s, MSG_MBR_DATA_STAT_HUNGRY );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_HUNGRY_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_HUNGRY_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_FAINT:
		if( chk_flg( mbr->stat, FLG_STAT_FAINT ) )
			strcpy( s, MSG_MBR_DATA_STAT_FAINT );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_FAINT_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_FAINT_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_DRUNK:
		if( chk_flg( mbr->stat, FLG_STAT_DRUNK ) )
			strcpy( s, MSG_MBR_DATA_STAT_DRUNK );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_DRUNK_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_DRUNK_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_VANISH:
		if( chk_flg( mbr->stat, FLG_STAT_VANISH ) )
			strcpy( s, MSG_MBR_DATA_STAT_VANISH );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_VANISH_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_VANISH_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_IRON_BODY:
		if( chk_flg( mbr->stat, FLG_STAT_IRON_BODY ) )
			strcpy( s, MSG_MBR_DATA_STAT_IRON_BODY );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_IRON_BODY_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_IRON_BODY_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_PASSWALL:
		if( chk_flg( mbr->stat, FLG_STAT_PASSWALL ) )
			strcpy( s, MSG_MBR_DATA_STAT_PASSWALL );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_PASSWALL_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_PASSWALL_DRAW_MIN_Y;
		break;
	case DATA_N_STAT_SENSE_INVISIBLE:
		if( chk_flg( mbr->stat, FLG_STAT_SENSE_INVISIBLE ) )
			strcpy( s, MSG_MBR_DATA_STAT_SENSE_INVISIBLE );
		else
			strcpy( s, MSG_MBR_DATA_STAT_NULL );
		x = WIN_MBR_DATA_STAT_SENSE_INVISIBLE_DRAW_MIN_X;
		y = WIN_MBR_DATA_STAT_SENSE_INVISIBLE_DRAW_MIN_Y;
		break;

	/**/

	case DATA_N_STORE_LIGHT:
		fx = srch_fx( &(org->fx), FX_KIND_STORE_LIGHT );
		if( fx == NULL )
			store_light_n = 0;
		else
			store_light_n = fx->n;
		sn_printf( s, max_len, MSG_FMT_MBR_DATA_STORE_LIGHT,
				MSG_MBR_DATA_STORE_LIGHT_TTL,
				store_light_n );
		x = WIN_MBR_DATA_STORE_LIGHT_DRAW_MIN_X;
		y = WIN_MBR_DATA_STORE_LIGHT_DRAW_MIN_Y;
		break;
	case DATA_N_GRAPH_FILE:
		sn_printf( s, max_len, MSG_FMT_MBR_DATA_GRAPH_FILE,
				MSG_MBR_DATA_GRAPH_FILE_TTL,
				mbr->graph_name );
		x = WIN_MBR_DATA_GRAPH_FILE_DRAW_MIN_X;
		y = WIN_MBR_DATA_GRAPH_FILE_DRAW_MIN_Y;
		break;

	/**/

	case DATA_N_LEV_LEFT:
		strcpy( s, MSG_MBR_DATA_LEV_TTL );
		x = WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_X;;
		y = WIN_MBR_DATA_LEV_TTL_LEFT_DRAW_MIN_Y;
		break;
	case DATA_N_EXP_LEFT:
		strcpy( s, MSG_MBR_DATA_EXP_TTL );
		x = WIN_MBR_DATA_EXP_TTL_LEFT_DRAW_MIN_X;
		y = WIN_MBR_DATA_EXP_TTL_LEFT_DRAW_MIN_Y;
		break;
	case DATA_N_NEED_EXP_LEFT:
		strcpy( s, MSG_MBR_DATA_NEED_EXP_TTL );
		x = WIN_MBR_DATA_NEED_EXP_TTL_LEFT_DRAW_MIN_X;
		y = WIN_MBR_DATA_NEED_EXP_TTL_LEFT_DRAW_MIN_Y;
		break;

	case DATA_N_LEV_RIGHT:
		strcpy( s, MSG_MBR_DATA_LEV_TTL );
		x = WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_X;;
		y = WIN_MBR_DATA_LEV_TTL_RIGHT_DRAW_MIN_Y;
		break;
	case DATA_N_EXP_RIGHT:
		strcpy( s, MSG_MBR_DATA_EXP_TTL );
		x = WIN_MBR_DATA_EXP_TTL_RIGHT_DRAW_MIN_X;
		y = WIN_MBR_DATA_EXP_TTL_RIGHT_DRAW_MIN_Y;
		break;
	case DATA_N_NEED_EXP_RIGHT:
		strcpy( s, MSG_MBR_DATA_NEED_EXP_TTL );
		x = WIN_MBR_DATA_NEED_EXP_TTL_RIGHT_DRAW_MIN_X;
		y = WIN_MBR_DATA_NEED_EXP_TTL_RIGHT_DRAW_MIN_Y;
		break;
/* abl 1/2 */
	case DATA_N_HP:
		abl_kind = ABL_KIND_HP;
		ttl = MSG_MBR_DATA_HP_TTL;
		x = WIN_MBR_DATA_HP_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_HP_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_MP:
		abl_kind = ABL_KIND_MP,
		ttl = MSG_MBR_DATA_MP_TTL;
		x = WIN_MBR_DATA_MP_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_MP_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_DEX:
		abl_kind = ABL_KIND_DEX,
		ttl = MSG_MBR_DATA_DEX_TTL;
		x = WIN_MBR_DATA_DEX_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_DEX_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_STR:
		abl_kind = ABL_KIND_STR,
		ttl = MSG_MBR_DATA_STR_TTL;
		x = WIN_MBR_DATA_STR_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_STR_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_AGI:
		abl_kind = ABL_KIND_AGI,
		ttl = MSG_MBR_DATA_AGI_TTL;
		x = WIN_MBR_DATA_AGI_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_AGI_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_INT:
		abl_kind = ABL_KIND_INT,
		ttl = MSG_MBR_DATA_INT_TTL;
		x = WIN_MBR_DATA_INT_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_INT_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_WIS:
		abl_kind = ABL_KIND_WIS,
		ttl = MSG_MBR_DATA_WIS_TTL;
		x = WIN_MBR_DATA_WIS_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_WIS_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_CHA:
		abl_kind = ABL_KIND_CHA,
		ttl = MSG_MBR_DATA_CHA_TTL;
		x = WIN_MBR_DATA_CHA_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_CHA_TTL_DRAW_MIN_Y;
		break;
/* resi */
	case DATA_N_RESI_TTL:
		strcpy( s, MSG_MBR_DATA_RESI_TTL );
		x = WIN_MBR_DATA_RESI_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_TTL_DRAW_MIN_Y;
		break;

	case DATA_N_RESI_TTL_LAWFUL:
		strcpy( s, MSG_MBR_DATA_RESI_TTL_LAWFUL );
		x = WIN_MBR_DATA_RESI_TTL_LAWFUL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_TTL_LAWFUL_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_TTL_NEUTRAL_1:
		strcpy( s, MSG_MBR_DATA_RESI_TTL_NEUTRAL_1 );
		x = WIN_MBR_DATA_RESI_TTL_NEUTRAL_1_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_TTL_NEUTRAL_1_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_TTL_CHAOTIC:
		strcpy( s, MSG_MBR_DATA_RESI_TTL_CHAOTIC );
		x = WIN_MBR_DATA_RESI_TTL_CHAOTIC_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_TTL_CHAOTIC_DRAW_MIN_Y;
		break;

	case DATA_N_RESI_TTL_GOOD:
		strcpy( s, MSG_MBR_DATA_RESI_TTL_GOOD );
		x = WIN_MBR_DATA_RESI_TTL_GOOD_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_TTL_GOOD_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_TTL_NEUTRAL_2:
		strcpy( s, MSG_MBR_DATA_RESI_TTL_NEUTRAL_2 );
		x = WIN_MBR_DATA_RESI_TTL_NEUTRAL_2_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_TTL_NEUTRAL_2_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_TTL_EVIL:
		strcpy( s, MSG_MBR_DATA_RESI_TTL_EVIL );
		x = WIN_MBR_DATA_RESI_TTL_EVIL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_TTL_EVIL_DRAW_MIN_Y;
		break;

	case DATA_N_RESI_KNOC:
		resi_kind = RESI_KIND_KNOC;
		ttl = MSG_MBR_DATA_RESI_KNOC_TTL;
		x = WIN_MBR_DATA_RESI_KNOC_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_KNOC_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_SLAS:
		resi_kind = RESI_KIND_SLAS;
		ttl = MSG_MBR_DATA_RESI_SLAS_TTL;
		x = WIN_MBR_DATA_RESI_SLAS_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_SLAS_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_STIN:
		resi_kind = RESI_KIND_STIN;
		ttl = MSG_MBR_DATA_RESI_STIN_TTL;
		x = WIN_MBR_DATA_RESI_STIN_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_STIN_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_HEAT:
		resi_kind = RESI_KIND_HEAT;
		ttl = MSG_MBR_DATA_RESI_HEAT_TTL;
		x = WIN_MBR_DATA_RESI_HEAT_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_HEAT_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_COLD:
		resi_kind = RESI_KIND_COLD;
		ttl = MSG_MBR_DATA_RESI_COLD_TTL;
		x = WIN_MBR_DATA_RESI_COLD_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_COLD_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_MIND:
		resi_kind = RESI_KIND_MIND;
		ttl = MSG_MBR_DATA_RESI_MIND_TTL;
		x = WIN_MBR_DATA_RESI_MIND_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_MIND_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_ACID:
		resi_kind = RESI_KIND_ACID;
		ttl = MSG_MBR_DATA_RESI_ACID_TTL;
		x = WIN_MBR_DATA_RESI_ACID_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_ACID_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_ELEC:
		resi_kind = RESI_KIND_ELEC;
		ttl = MSG_MBR_DATA_RESI_ELEC_TTL;
		x = WIN_MBR_DATA_RESI_ELEC_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_ELEC_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_RESI_POIS:
		resi_kind = RESI_KIND_POIS;
		ttl = MSG_MBR_DATA_RESI_POIS_TTL;
		x = WIN_MBR_DATA_RESI_POIS_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_RESI_POIS_TTL_DRAW_MIN_Y;
		break;
/* abl 2/2 */
	case DATA_N_CLASS:
		if( is_mbr( mbr ) )
			class_name = get_class_tab()[mbr->class_n].name;
		else
			class_name = "----";

		sn_printf( s, max_len, MSG_MBR_DATA_CLASS,
				MSG_MBR_DATA_CLASS_TTL, class_name );
		x = WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_Y;
		break;

	case DATA_N_FIG:
		abl_kind = ABL_KIND_FIG,
		ttl = MSG_MBR_DATA_FIG_TTL;
		x = WIN_MBR_DATA_FIG_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_FIG_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_MON:
		abl_kind = ABL_KIND_MON,
		ttl = MSG_MBR_DATA_MON_TTL;
		x = WIN_MBR_DATA_MON_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_MON_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_HUN:
		abl_kind = ABL_KIND_HUN,
		ttl = MSG_MBR_DATA_HUN_TTL;
		x = WIN_MBR_DATA_HUN_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_HUN_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_THI:
		abl_kind = ABL_KIND_THI,
		ttl = MSG_MBR_DATA_THI_TTL;
		x = WIN_MBR_DATA_THI_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_THI_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_MAG:
		abl_kind = ABL_KIND_MAG,
		ttl = MSG_MBR_DATA_MAG_TTL;
		x = WIN_MBR_DATA_MAG_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_MAG_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_SOR:
		abl_kind = ABL_KIND_SOR,
		ttl = MSG_MBR_DATA_SOR_TTL;
		x = WIN_MBR_DATA_SOR_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SOR_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_ENC:
		abl_kind = ABL_KIND_ENC,
		ttl = MSG_MBR_DATA_ENC_TTL;
		x = WIN_MBR_DATA_ENC_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_ENC_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_SUM:
		abl_kind = ABL_KIND_SUM,
		ttl = MSG_MBR_DATA_SUM_TTL;
		x = WIN_MBR_DATA_SUM_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SUM_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_PRI:
		abl_kind = ABL_KIND_PRI,
		ttl = MSG_MBR_DATA_PRI_TTL;
		x = WIN_MBR_DATA_PRI_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_PRI_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_SHA:
		abl_kind = ABL_KIND_SHA,
		ttl = MSG_MBR_DATA_SHA_TTL;
		x = WIN_MBR_DATA_SHA_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SHA_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_BAR:
		abl_kind = ABL_KIND_BAR,
		ttl = MSG_MBR_DATA_BAR_TTL;
		x = WIN_MBR_DATA_BAR_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_BAR_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_NIN:
		abl_kind = ABL_KIND_NIN,
		ttl = MSG_MBR_DATA_NIN_TTL;
		x = WIN_MBR_DATA_NIN_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_NIN_TTL_DRAW_MIN_Y;
		break;

	case DATA_N_SKILL_NAME_A:
		strcpy( s, MSG_MBR_DATA_SKILL_NAME_A_TTL );
		x = WIN_MBR_DATA_SKILL_NAME_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SKILL_NAME_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_SKILL_NAME_B:
		strcpy( s, MSG_MBR_DATA_SKILL_NAME_B_TTL );
		x = WIN_MBR_DATA_SKILL_NAME_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SKILL_NAME_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_SKILL_LEV:
		strcpy( s, MSG_MBR_DATA_SKILL_LEV_TTL );
		x = WIN_MBR_DATA_SKILL_LEV_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SKILL_LEV_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_SKILL_EXP:
		strcpy( s, MSG_MBR_DATA_SKILL_EXP_TTL );
		x = WIN_MBR_DATA_SKILL_EXP_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SKILL_EXP_TTL_DRAW_MIN_Y;
		break;
	case DATA_N_SKILL_NEED_EXP:
		strcpy( s, MSG_MBR_DATA_SKILL_NEED_EXP_TTL );
		x = WIN_MBR_DATA_SKILL_NEED_EXP_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SKILL_NEED_EXP_TTL_DRAW_MIN_Y;
		break;

	case DATA_N_SKILL_A_00:
	case DATA_N_SKILL_A_01:
	case DATA_N_SKILL_A_02:
	case DATA_N_SKILL_A_03:
	case DATA_N_SKILL_A_04:
	case DATA_N_SKILL_A_05:
	case DATA_N_SKILL_A_06:
	case DATA_N_SKILL_A_07:
	case DATA_N_SKILL_A_08:
	case DATA_N_SKILL_A_09:
	case DATA_N_SKILL_B_00:
	case DATA_N_SKILL_B_01:
	case DATA_N_SKILL_B_02:
	case DATA_N_SKILL_B_03:
	case DATA_N_SKILL_B_04:
	case DATA_N_SKILL_B_05:
	case DATA_N_SKILL_B_06:
	case DATA_N_SKILL_B_07:
	case DATA_N_SKILL_B_08:
	case DATA_N_SKILL_B_09:
		if( is_mbr( mbr ) ){
			long	skill_n;
			skill_kind_t	kind;
			long	lev;
			long	exp, need_exp;
			const char	*name;
			long	dy;
			long	len;

			skill_n = n - DATA_N_SKILL_A_00;
			kind = get_skill_from_class(
					mbr->class_n, skill_n );
			lev = get_skill_lev_from_slot(
					mbr, skill_n );
			exp = get_skill_exp_from_slot(
					mbr, skill_n );
			need_exp = get_skill_need_exp_from_slot(
					mbr, skill_n );
			name = get_skill_name_from_slot(
					mbr, skill_n );

			dy = n - DATA_N_SKILL_A_00;
			dy %= SKILL_PER_PAGE_MAX_N;

			x = WIN_MBR_DATA_SKILL_LEV_DRAW_MIN_X;
			y = WIN_MBR_DATA_SKILL_LEV_DRAW_MIN_Y + dy;
			print_str( x, y, "%4ld", lev );

			x = WIN_MBR_DATA_SKILL_EXP_DRAW_MIN_X;
			y = WIN_MBR_DATA_SKILL_EXP_DRAW_MIN_Y + dy;
			print_str( x, y, "%10ld/", exp );

			x = WIN_MBR_DATA_SKILL_NEED_EXP_DRAW_MIN_X;
			y = WIN_MBR_DATA_SKILL_NEED_EXP_DRAW_MIN_Y + dy;
			print_str( x, y, "%10ld", need_exp );

			x = WIN_MBR_DATA_SKILL_HINT_DRAW_MIN_X;
			y = WIN_MBR_DATA_SKILL_HINT_DRAW_MIN_Y;
			if( flg_rev )
				print_skill_hint( x, y, kind );

			len = 30;
			sn_printf( s, max_len, MSG_FMT_MBR_DATA_SKILL_NAME,
					len, name );
			x = WIN_MBR_DATA_SKILL_NAME_DRAW_MIN_X;
			y = WIN_MBR_DATA_SKILL_NAME_DRAW_MIN_Y + dy;
		} else {
			s[0] = '\0';
		}
		break;

	case DATA_N_ITEM_00:
	case DATA_N_ITEM_01:
	case DATA_N_ITEM_02:
	case DATA_N_ITEM_03:
	case DATA_N_ITEM_04:
	case DATA_N_ITEM_05:
	case DATA_N_ITEM_06:
	case DATA_N_ITEM_07:
	case DATA_N_ITEM_08:
	case DATA_N_ITEM_09:
	case DATA_N_ITEM_10:
	case DATA_N_ITEM_11:
	case DATA_N_ITEM_12:
	case DATA_N_ITEM_13:
	case DATA_N_ITEM_14:
	case DATA_N_ITEM_15:
		item_n = n - DATA_N_ITEM_00;
		item_head = get_mbr_item_asgn( mbr );
		item = NULL;
		i = 0;
		if( item_head != NULL ){
			item = item_head->next;
			for( i = 0; i < item_n; i++, item = item->next )
				if( item == item_head )
					break;
		}

		if( (item_head == NULL) || (i != item_n)
				|| (item == item_head) ){
			sn_printf( s, max_len, "%c) %-*s",
					(char)(item_n + 'A'),
					ITEM_NAME_MAX_LEN,
					" " );
		} else {
			sn_printf( s, max_len, "%c) %-*s",
					(char)(item_n + 'A'),
					ITEM_NAME_MAX_LEN,
					item->name );
		}

		x = WIN_MBR_DATA_ITEM_DRAW_MIN_X;
		y = WIN_MBR_DATA_ITEM_DRAW_MIN_Y + item_n;
		break;

	case DATA_N_EQUIP_WIELDING:
	case DATA_N_EQUIP_SHIELD:
	case DATA_N_EQUIP_BOW:
	case DATA_N_EQUIP_ARW:
	case DATA_N_EQUIP_HEAD:
	case DATA_N_EQUIP_NECK:
	case DATA_N_EQUIP_BODY:
	case DATA_N_EQUIP_ABOUT_BODY:
	case DATA_N_EQUIP_ARM:
	case DATA_N_EQUIP_RIGHT_HAND:
	case DATA_N_EQUIP_LEFT_HAND:
	case DATA_N_EQUIP_FEET:
	case DATA_N_EQUIP_LIGHT_SOURCE:
		item = get_mbr_item_asgn_equip( mbr );
		eq_k = (equip_kind_t)(EQUIP_KIND_NULL
				+ (n - DATA_N_EQUIP_WIELDING));

		if( (item == NULL) || (item[eq_k].kind == ITEM_KIND_NULL) ){
			sn_printf( s, max_len, "%-*s: %-*s",
					(int)get_equip_ttl_max_len(),
					get_item_equip_name( eq_k ),
					(int)ITEM_NAME_MAX_LEN,
					" " );
		} else {
			sn_printf( s, max_len, "%-*s: %-*s",
					(int)get_equip_ttl_max_len(),
					get_item_equip_name( eq_k ),
					(int)ITEM_NAME_MAX_LEN,
					item[eq_k].name );
		}

		x = WIN_MBR_DATA_ITEM_DRAW_MIN_X;
		y = WIN_MBR_DATA_ITEM_DRAW_MIN_Y
				+ (n - DATA_N_EQUIP_WIELDING);
		break;

	case DATA_N_SWAP_PAGE_MBR:
		if( get_flg_mbr_data_change_page_is_crsr() )
			strcpy( s, MSG_MBR_DATA_SWAP_PAGE );
		else
			strcpy( s, MSG_MBR_DATA_SWAP_MBR );
		x = WIN_MBR_DATA_SWAP_PAGE_MBR_DRAW_MIN_X;
		y = WIN_MBR_DATA_SWAP_PAGE_MBR_DRAW_MIN_Y;
		break;
	case DATA_N_PREV_PAGE:
		if( get_flg_mbr_data_change_page_is_crsr() )
			strcpy( s, MSG_MBR_DATA_PREV_MBR );
		else
			strcpy( s, MSG_MBR_DATA_PREV_PAGE );
		x = WIN_MBR_DATA_PREV_PAGE_DRAW_MIN_X;
		y = WIN_MBR_DATA_PREV_PAGE_DRAW_MIN_Y;
		break;
	case DATA_N_NEXT_PAGE:
		if( get_flg_mbr_data_change_page_is_crsr() )
			strcpy( s, MSG_MBR_DATA_NEXT_MBR );
		else
			strcpy( s, MSG_MBR_DATA_NEXT_PAGE );
		x = WIN_MBR_DATA_NEXT_PAGE_DRAW_MIN_X;
		y = WIN_MBR_DATA_NEXT_PAGE_DRAW_MIN_Y;
		break;

	case DATA_N_MAX_N:
	case DATA_N_NULL:
		break;
	}

	/**/

	switch( n ){
	case DATA_N_HP:
	case DATA_N_MP:
	case DATA_N_DEX:
	case DATA_N_STR:
	case DATA_N_AGI:
	case DATA_N_INT:
	case DATA_N_WIS:
	case DATA_N_CHA:
	case DATA_N_FIG:
	case DATA_N_MON:
	case DATA_N_HUN:
	case DATA_N_THI:
	case DATA_N_MAG:
	case DATA_N_SOR:
	case DATA_N_ENC:
	case DATA_N_SUM:
	case DATA_N_PRI:
	case DATA_N_SHA:
	case DATA_N_BAR:
	case DATA_N_NIN:
		mbr_lev_n = get_lev( mbr, abl_kind );
		org_lev_n = get_lev( org, abl_kind );
		mbr_lev_max = get_lev_max( mbr, abl_kind );
		org_lev_max = get_lev_max( org, abl_kind );

		if( (mbr_lev_n != org_lev_n)
				|| (mbr_lev_max != org_lev_max) ){
			str_lev_up_left = MSG_LEV_UP_LEFT_ON;
			str_lev_up_right = MSG_LEV_UP_RIGHT_ON;
		} else {
			str_lev_up_left = MSG_LEV_UP_LEFT_OFF;
			str_lev_up_right = MSG_LEV_UP_RIGHT_OFF;
		}
		if( chk_modified_lev( mbr, abl_kind ) ){
			sn_printf( str_add_lev, max_len_add_lev,
					MSG_FMT_MBR_DATA_ADD_LEV,
					mbr_lev_n - mbr_lev_max );
		} else {
			str_add_lev[0] = '\0';
		}

		sn_printf( s, max_len, MSG_FMT_MBR_DATA_ABL,
				ttl, str_lev_up_left,
				mbr_lev_n, str_add_lev,
				mbr->abl.exp[abl_kind].n,
				calc_need_exp( mbr_lev_n + 1, abl_kind ),
				str_lev_up_right );
		break;
	case DATA_N_RESI_KNOC:
	case DATA_N_RESI_SLAS:
	case DATA_N_RESI_STIN:
	case DATA_N_RESI_HEAT:
	case DATA_N_RESI_COLD:
	case DATA_N_RESI_MIND:
	case DATA_N_RESI_ACID:
	case DATA_N_RESI_ELEC:
	case DATA_N_RESI_POIS:
		resi = get_resi( mbr, resi_kind );
		sn_printf( s, max_len, MSG_FMT_MBR_DATA_RESI, ttl, resi );
		break;
	default:
		break;
	}

	if( flg_rev ){
		/* ȿž���� */

		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
		print_str( x, y, MSG_MBR_DATA_SEL, s );
	} else {
		/* �̾����� */

		curs_attrset_n( CURS_ATTR_N_NORMAL );
		print_str( x, y, MSG_MBR_DATA_NOT_SEL, s );
	}
	curs_attrset_dflt();

	/* �ޥ����Υϥ�ɥ������ */

	if( flg_rev )
		g_cui_mouse_mbr_data_cur_n = n;

	if( flg_all ){
		call_cui_mouse_add_handler(
				chk_sel_data_n( n, edit_kind ),
				x, y, str_len_draw( s ), 1,
				cb_cui_mouse_point_mbr_data,
				cb_cui_mouse_click_mbr_data,
				NULL,
				n, "" );
	}
}

/***************************************************************
* ���С����ǡ����Υݥ���ȤΥޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_point_mbr_data( long btn, long n, const char *macro )
{
	long	dn;
	long	i;

	dn = calc_mbr_data_idx( (data_n_t)n, g_cui_mouse_mbr_data_cur_n );

	switch( btn ){
	case 0:
		for( i = 0; i < labs( dn ); i++ ){
			if( dn <= -1 )
				set_key_buf_char_tail( '8' );
			if( dn >= +1 )
				set_key_buf_char_tail( '2' );
		}
		return TRUE;
	case 1:
	case 2:
		break;
	}

	return FALSE;
}

/***************************************************************
* ���С����ǡ����Υ���å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_mbr_data( long btn, long n, const char *macro )
{
	switch( btn ){
	case 0:
		set_key_buf_char_tail( '\n' );
		return TRUE;
	case 1:
	case 2:
		break;
	}

	return FALSE;
}

/***************************************************************
* ���С��λ���Υǡ����ޤǤΥ���ǥå����������
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
***************************************************************/

long	calc_mbr_data_idx( data_n_t next_n, data_n_t cur_n )
{
	long	page_n;
	mbr_data_edit_kind_t	edit_kind;
	long	d, idx;
	data_n_t	n;
	long	i;

	page_n = g_cui_mouse_mbr_data_cur_page_n;
	edit_kind = g_cui_mouse_mbr_data_edit_kind;

	d = sgn_l( next_n - cur_n );
	idx = d;

	n = (data_n_t)(cur_n + d);
	if( d == 0 )
		d = +1;

	for( i = 0; i < LOOP_MAX_1000; i++, n = (data_n_t)(n + d) ){
		if( n == next_n )
			return idx;

		/* ���ơ������ */

		if( n < (data_n_t)(DATA_N_NULL + 1) )
			n = (data_n_t)(DATA_N_MAX_N - 1);
		if( n > (data_n_t)(DATA_N_MAX_N - 1) )
			n = (data_n_t)(DATA_N_NULL + 1);

		/* �ڡ������㤦���ϥ����å� */

		if( !chk_flg( data_page_n_tab[n], (1 << page_n) ) )
			continue;

		/* �ǡ���������Ǥ��ʤ��ʤ饹���å� */

		if( !chk_sel_data_n( n, edit_kind ) )
			continue;

		/* ������� */

		idx += d;
	}

	return 0;
}

/***************************************************************
* ���С��μ��Υǡ��������򤹤�
* long page_n : �ڡ���
* data_n_t n : �ǡ����μ����ֹ�
* long d : �ǡ����μ��˿ʤ�����
* mbr_data_edit_kind_t edit_kind : �Խ��⡼��
* return : ���Υǡ����μ����ֹ�
***************************************************************/

data_n_t	next_mbr_data(
	long page_n, data_n_t n, long d,
	mbr_data_edit_kind_t edit_kind
)
{
	long	i;

	n = (data_n_t)(n + d);
	if( d == 0 )
		d = +1;

	for( i = 0; i < LOOP_MAX_1000; i++, n = (data_n_t)(n + d) ){
		/* ���ơ������ */

		if( n < (data_n_t)(DATA_N_NULL + 1) )
			n = (data_n_t)(DATA_N_MAX_N - 1);
		if( n > (data_n_t)(DATA_N_MAX_N - 1) )
			n = (data_n_t)(DATA_N_NULL + 1);

		/* �ڡ������㤦���ϥ����å� */

		if( !chk_flg( data_page_n_tab[n], (1 << page_n) ) )
			continue;

		/* �ǡ���������Ǥ���ʤ��֤� */

		if( chk_sel_data_n( n, edit_kind ) )
			return n;
	}

	return DATA_N_NULL;
}

/***************************************************************
* ���С����ǡ���������Ǥ��뤫Ĵ�٤�
* data_n_t n : �ǡ����μ����ֹ�
* mbr_data_edit_kind_t edit_kind : �Խ��⡼��
* return : ����Ǥ��뤫?
***************************************************************/

bool_t	chk_sel_data_n( data_n_t n, mbr_data_edit_kind_t edit_kind )
{
	return flg_sel_data_n[edit_kind][n];
}

/***************************************************************
* ���С���̾�������Ϥ���
* mbr_t *mbr_p : ���С�
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	gets_mbr_name( mbr_t *mbr )
{
	long	x, y;
	char	buf[MBR_NAME_MAX_BYTE + 4 + 1];

	if( mbr == NULL )
		return FALSE;

	str_nz_cpy( buf,
			cut_utf_str( mbr->name, MBR_NAME_MAX_LEN ),
			MBR_NAME_MAX_BYTE );

	/* ����������֤򥻥å� */

	x = WIN_MBR_DATA_NAME_TTL_DRAW_MIN_X + 1;
	y = WIN_MBR_DATA_NAME_TTL_DRAW_MIN_Y;
	x += str_len_draw( MSG_MBR_DATA_NAME_TTL );

	if( !game_gets( x, y, MSG_MBR_DATA_NAME_TTL,
			buf, MBR_NAME_MAX_BYTE, TRUE ) ){
		return FALSE;
	}

	str_nz_cpy( mbr->name,
			cut_utf_str( buf, MBR_NAME_MAX_LEN ),
			MBR_NAME_MAX_BYTE );

	return TRUE;
}

/***************************************************************
* ���С��δ�ʸ�������Ϥ���
* mbr_t *mbr : ���С�
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	gets_mbr_face( mbr_t *mbr )
{
	long	x, y;
	char	buf[8 * 2 + 1];
	long	idx;

	if( mbr == NULL )
		return FALSE;

	buf[0] = mbr->face.mjr;
	buf[1] = mbr->face.mnr;
	buf[2] = '\0';

	/* ����������֤򥻥å� */

	x = WIN_MBR_DATA_FACE_TTL_DRAW_MIN_X + 1;
	y = WIN_MBR_DATA_FACE_TTL_DRAW_MIN_Y;
	x += str_len_draw( MSG_MBR_DATA_FACE_TTL );

	if( !game_gets( x, y, MSG_MBR_DATA_FACE_TTL, buf, 2, TRUE ) )
		return FALSE;

	if( buf[0] == '\0' )
		return FALSE;

	if( buf[1] == '\0' )
		idx = 0;
	else
		idx = 1;

	do {
		if( isalnum( buf[idx] ) )
			break;
		if( strchr( "@$+-*/", buf[idx] ) != NULL )
			break;

		return FALSE;
	} while( 0 );

	mbr->face.mnr = buf[idx];
	mbr->face.mnr_org = mbr->face.mnr;

	return TRUE;
}

/***************************************************************
* ���С��μ�²̾�����Ϥ���
* mbr_t *mbr : ���С�
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	gets_race_name( mbr_t *mbr )
{
	long	x, y;
	char	buf[RACE_NAME_MAX_BYTE + 4 + 1];

	if( mbr == NULL )
		return FALSE;

	str_nz_cpy( buf,
			cut_utf_str( mbr->race.name, RACE_NAME_MAX_LEN ),
			RACE_NAME_MAX_BYTE );

	/* ����������֤򥻥å� */

	x = WIN_MBR_DATA_RACE_NAME_TTL_DRAW_MIN_X + 1;
	y = WIN_MBR_DATA_RACE_NAME_TTL_DRAW_MIN_Y;
	x += str_len_draw( MSG_MBR_DATA_RACE_NAME_TTL );

	if( !game_gets( x, y, MSG_MBR_DATA_RACE_NAME_TTL,
			buf, RACE_NAME_MAX_BYTE, TRUE ) ){
		return FALSE;
	}

	str_nz_cpy( mbr->race.name,
			cut_utf_str( buf, RACE_NAME_MAX_LEN ),
			RACE_NAME_MAX_BYTE );

	return TRUE;
}

/***************************************************************
* �ڥåȤ�̾�������Ϥ���
* pet_t *pet : �ڥå�
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	gets_pet_name( pet_t *pet )
{
	long	x, y;
	char	buf[PET_NAME_MAX_BYTE + 1];

	if( pet == NULL )
		return FALSE;

	str_nz_cpy( buf,
			cut_utf_str( pet->name, PET_NAME_MAX_LEN ),
			PET_NAME_MAX_BYTE );

	/* ����������֤򥻥å� */

	x = WIN_PET_DATA_NAME_TTL_DRAW_MIN_X;
	y = WIN_PET_DATA_NAME_TTL_DRAW_MIN_Y;

	print_str( x, y, MSG_S, MSG_PET_DATA_NAME_TTL );
	x += str_len_draw( MSG_PET_DATA_NAME_TTL );

	if( !game_gets( x, y, MSG_PET_DATA_NAME_TTL,
			buf, PET_NAME_MAX_BYTE, TRUE ) ){
		return FALSE;
	}

	str_nz_cpy( pet->name,
			cut_utf_str( buf, PET_NAME_MAX_LEN ),
			PET_NAME_MAX_BYTE );

	return TRUE;
}

/***************************************************************
* ������Υҥ�Ȥ�ɽ��
* long x : X��ɸ
* long y : Y��ɸ
* skill_kind_t kind : ������μ���
***************************************************************/

void	print_skill_hint( long x, long y, skill_kind_t kind )
{
	const char	*hint, *head, *tail;
	char	line[SKILL_HINT_LINE_MAX_BYTE + 1];
	long	i;

	hint = get_skill_hint( kind );

	head = hint;
	for( i = 0; i < SKILL_HINT_MAX_LINE; i++ ){
		/* 1��ʬ�ڤ�Ф� */

		tail = get_words_line( head, SKILL_HINT_LINE_MAX_LEN );
		if( tail == NULL )
			break;
		if( head[0] == '\n' )
			head++;

		/* 1��ʬ���ԡ� */

		str_nz_cpy( line, head, tail - head );
		line[tail - head] = '\0';

		print_str( x, y, "%-*s", SKILL_HINT_LINE_MAX_LEN, line );

		y++;
		head = tail;
	}
	for( ; i < SKILL_HINT_MAX_LINE; i++ ){
		print_str( x, y, "%-*s", SKILL_HINT_LINE_MAX_LEN, " " );
		y++;
	}
}

/***************************************************************
* ���ƤΥ��饹�Υѥ�᡼�����Խ�
* class_t *org : ���饹�ν������Υѥ�᡼��
* class_t *dst : ���饹�ν�����Υѥ�᡼��
* edit_class_t sel_n : �ѥ�᡼��
* bool_t flg_sel_add : �ץ饹������?
***************************************************************/

void	draw_edit_class_all(
	class_t *org, class_t *dst,
	edit_class_t sel_n, bool_t flg_sel_add
)
{
	long	i;

	/* �ޥ����Υϥ�ɥ��ꥻ�å� */

	call_cui_mouse_reset_handler_tab();

	/* ���̾õ� */

	wipe_all();
	redraw_msg();
	draw_stat_bar();

	/* ���������� */
	for( i = 0; i < WIN_MAP_DRAW_MAX_Y + 1; i++ )
		print_str( WIN_MAP_DRAW_MAX_X + 1, i, MSG_V_LINE );
	/* ���������� */
	print_str( SCREEN_MIN_X, WIN_MAP_DRAW_MAX_Y + 1, MSG_H_FRAME );

	/* ���� */

	for( i = EDIT_CLASS_NULL + 1; i < EDIT_CLASS_MAX_N; i++ ){
		edit_class_t	n;

		n = (edit_class_t)i;
		if( n == sel_n ){
			draw_edit_class( org, dst, n,
					TRUE, flg_sel_add, TRUE );
		} else {
			draw_edit_class( org, dst, n,
					FALSE, flg_sel_add, TRUE );
		}
	}

	/* �ޥ������ۥ����� */
	set_cui_mouse_add_handler_common_scroll();
}

/***************************************************************
* ���饹�Υѥ�᡼�����Խ�
* class_t *org : ���饹�ν������Υѥ�᡼��
* class_t *dst : ���饹�ν�����Υѥ�᡼��
* edit_class_t n : �ѥ�᡼��
* bool_t flg_sel : �����椫?
* bool_t flg_sel_add : �ץ饹������?
* bool_t flg_all : ���ǡ�����ɽ����?
***************************************************************/

void	draw_edit_class(
	class_t *org, class_t *dst, edit_class_t n,
	bool_t flg_sel, bool_t flg_sel_add,
	bool_t flg_all
)
{
	const long	max_len = 80;
	char	str[80 + 1];
	bool_t	flg_add, flg_sub;
	char	*ttl;
	abl_kind_t	abl;
	long	x, y;
	long	abl_len, add_len, len;

	if( org == NULL )
		return;
	if( dst == NULL )
		return;

	if( flg_sel ){
		flg_add = flg_sel_add;
		flg_sub = !flg_sel_add;
	} else {
		flg_add = FALSE;
		flg_sub = FALSE;
	}

	ttl = NULL;
	abl = ABL_KIND_HP;
	x = 0;
	y = 0;

	switch( n ){
	case EDIT_CLASS_NULL:
	case EDIT_CLASS_MAX_N:
		return;
	case EDIT_CLASS_NAME:
		x = WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_Y;
		if( flg_sel ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			sn_printf( str, max_len, MSG_EDIT_CLASS_NAME_SEL,
					MSG_MBR_DATA_CLASS_TTL,
					CLASS_NAME_MAX_LEN,
					dst->name );
			print_str( x, y, "%s", str );
		} else {
			curs_attrset_n( CURS_ATTR_N_NORMAL );
			sn_printf( str, max_len, MSG_EDIT_CLASS_NAME_NOT_SEL,
					MSG_MBR_DATA_CLASS_TTL,
					CLASS_NAME_MAX_LEN,
					dst->name );
			print_str( x, y, "%s", str );
		}
		curs_attrset_dflt();
		break;
	case EDIT_CLASS_TOTAL:
		x = WIN_MBR_DATA_CHA_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_CHA_TTL_DRAW_MIN_Y + 2;
		if( flg_sel ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			sn_printf( str, max_len, MSG_EDIT_CLASS_TOTAL_SEL,
					(long)calc_abl_total( dst ) );
			print_str( x, y, "%s", str );
		} else {
			curs_attrset_n( CURS_ATTR_N_NORMAL );
			sn_printf( str, max_len, MSG_EDIT_CLASS_TOTAL_NOT_SEL,
					(long)calc_abl_total( dst ) );
			print_str( x, y, "%s", str );
		}
		curs_attrset_dflt();
		break;
	case EDIT_CLASS_PREV:
		x = WIN_EDIT_CLASS_PREV_DRAW_MIN_X;
		y = WIN_EDIT_CLASS_PREV_DRAW_MIN_Y;
		if( flg_sel ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			sn_printf( str, max_len, MSG_MBR_DATA_SEL,
					MSG_EDIT_CLASS_PREV );
			print_str( x, y, "%s", str );
		} else {
			curs_attrset_n( CURS_ATTR_N_NORMAL );
			sn_printf( str, max_len, MSG_MBR_DATA_NOT_SEL,
					MSG_EDIT_CLASS_PREV );
			print_str( x, y, "%s", str );
		}
		curs_attrset_dflt();
		break;
	case EDIT_CLASS_NEXT:
		x = WIN_EDIT_CLASS_NEXT_DRAW_MIN_X;
		y = WIN_EDIT_CLASS_NEXT_DRAW_MIN_Y;
		if( flg_sel ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			sn_printf( str, max_len, MSG_MBR_DATA_SEL,
					MSG_EDIT_CLASS_NEXT );
			print_str( x, y, "%s", str );
		} else {
			curs_attrset_n( CURS_ATTR_N_NORMAL );
			sn_printf( str, max_len, MSG_MBR_DATA_NOT_SEL,
					MSG_EDIT_CLASS_NEXT );
			print_str( x, y, "%s", str );
		}
		curs_attrset_dflt();
		break;
	case EDIT_CLASS_HP:
		ttl = MSG_MBR_DATA_HP_TTL;
		abl = ABL_KIND_HP;
		x = WIN_MBR_DATA_HP_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_HP_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_MP:
		ttl = MSG_MBR_DATA_MP_TTL;
		abl = ABL_KIND_MP;
		x = WIN_MBR_DATA_MP_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_MP_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_DEX:
		ttl = MSG_MBR_DATA_DEX_TTL;
		abl = ABL_KIND_DEX;
		x = WIN_MBR_DATA_DEX_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_DEX_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_STR:
		ttl = MSG_MBR_DATA_STR_TTL;
		abl = ABL_KIND_STR;
		x = WIN_MBR_DATA_STR_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_STR_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_AGI:
		ttl = MSG_MBR_DATA_AGI_TTL;
		abl = ABL_KIND_AGI;
		x = WIN_MBR_DATA_AGI_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_AGI_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_INT:
		ttl = MSG_MBR_DATA_INT_TTL;
		abl = ABL_KIND_INT;
		x = WIN_MBR_DATA_INT_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_INT_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_WIS:
		ttl = MSG_MBR_DATA_WIS_TTL;
		abl = ABL_KIND_WIS;
		x = WIN_MBR_DATA_WIS_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_WIS_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_CHA:
		ttl = MSG_MBR_DATA_CHA_TTL;
		abl = ABL_KIND_CHA;
		x = WIN_MBR_DATA_CHA_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_CHA_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_FIG:
		ttl = MSG_MBR_DATA_FIG_TTL;
		abl = ABL_KIND_FIG;
		x = WIN_MBR_DATA_FIG_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_FIG_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_MON:
		ttl = MSG_MBR_DATA_MON_TTL;
		abl = ABL_KIND_MON;
		x = WIN_MBR_DATA_MON_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_MON_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_HUN:
		ttl = MSG_MBR_DATA_HUN_TTL;
		abl = ABL_KIND_HUN;
		x = WIN_MBR_DATA_HUN_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_HUN_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_THI:
		ttl = MSG_MBR_DATA_THI_TTL;
		abl = ABL_KIND_THI;
		x = WIN_MBR_DATA_THI_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_THI_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_NIN:
		ttl = MSG_MBR_DATA_NIN_TTL;
		abl = ABL_KIND_NIN;
		x = WIN_MBR_DATA_NIN_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_NIN_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_PRI:
		ttl = MSG_MBR_DATA_PRI_TTL;
		abl = ABL_KIND_PRI;
		x = WIN_MBR_DATA_PRI_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_PRI_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_SHA:
		ttl = MSG_MBR_DATA_SHA_TTL;
		abl = ABL_KIND_SHA;
		x = WIN_MBR_DATA_SHA_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SHA_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_BAR:
		ttl = MSG_MBR_DATA_BAR_TTL;
		abl = ABL_KIND_BAR;
		x = WIN_MBR_DATA_BAR_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_BAR_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_MAG:
		ttl = MSG_MBR_DATA_MAG_TTL;
		abl = ABL_KIND_MAG;
		x = WIN_MBR_DATA_MAG_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_MAG_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_SOR:
		ttl = MSG_MBR_DATA_SOR_TTL;
		abl = ABL_KIND_SOR;
		x = WIN_MBR_DATA_SOR_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SOR_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_ENC:
		ttl = MSG_MBR_DATA_ENC_TTL;
		abl = ABL_KIND_ENC;
		x = WIN_MBR_DATA_ENC_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_ENC_TTL_DRAW_MIN_Y;
		break;
	case EDIT_CLASS_SUM:
		ttl = MSG_MBR_DATA_SUM_TTL;
		abl = ABL_KIND_SUM;
		x = WIN_MBR_DATA_SUM_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_SUM_TTL_DRAW_MIN_Y;
		break;
	}

	if( ttl == NULL ){
		/* �ޥ����Υϥ�ɥ������ */

		if( flg_sel )
			g_cui_mouse_edit_class_sel_n = n;

		if( flg_all ){
			len = str_len_draw( str );
			call_cui_mouse_add_handler(
					TRUE,
					x, y, len, 1,
					cb_cui_mouse_point_edit_class,
					cb_cui_mouse_click_edit_class,
					NULL,
					n, NULL );
		}
	} else {
		/* ����̾������ */

		print_str( x, y, MSG_EDIT_CLASS_TTL,
				ttl, (long)dst->abl_rate[abl] );

		/* �ץ饹�����ܥ�������� */

		abl_len = 10;
		if( flg_add ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			print_str( x + abl_len, y,
					MSG_EDIT_CLASS_ADD_SEL );
		} else {
			curs_attrset_n( CURS_ATTR_N_NORMAL );
			print_str( x + abl_len, y,
					MSG_EDIT_CLASS_ADD_NOT_SEL );
		}

		/* �ޥ��ʥ������ܥ�������� */

		add_len = str_len_draw( MSG_EDIT_CLASS_ADD_NOT_SEL );
		if( flg_sub ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			print_str( x + abl_len + add_len, y,
					MSG_EDIT_CLASS_SUB_SEL );
		} else {
			curs_attrset_n( CURS_ATTR_N_NORMAL );
			print_str( x + abl_len + add_len, y,
					MSG_EDIT_CLASS_SUB_NOT_SEL );
		}

		curs_attrset_dflt();

		/* �ޥ����Υϥ�ɥ������ */

		if( flg_sel )
			g_cui_mouse_edit_class_sel_n = n;

		if( flg_all ){
			len = str_len_draw( MSG_EDIT_CLASS_ADD_SEL );
			call_cui_mouse_add_handler(
					TRUE,
					(x + abl_len), y, len, 1,
					cb_cui_mouse_point_edit_class,
					cb_cui_mouse_click_edit_class,
					NULL,
					n, "4" );

			len = str_len_draw( MSG_EDIT_CLASS_SUB_SEL );
			call_cui_mouse_add_handler(
					TRUE,
					(x + abl_len + add_len), y, len, 1,
					cb_cui_mouse_point_edit_class,
					cb_cui_mouse_click_edit_class,
					NULL,
					n, "6" );
		}
	}
}

/***************************************************************
* ���饹���ѥ�᡼�����Խ��Υݥ���ȤΥޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_point_edit_class( long btn, long n, const char *macro )
{
	long	dn;
	long	i;

	dn = n - g_cui_mouse_edit_class_sel_n;

	switch( btn ){
	case 0:
		for( i = 0; i < labs( dn ); i++ ){
			if( dn <= -1 )
				set_key_buf_char_tail( '8' );
			if( dn >= +1 )
				set_key_buf_char_tail( '2' );
		}

		if( macro != NULL )
			set_key_buf_str_tail( macro );

		return TRUE;
	case 1:
	case 2:
		break;
	}

	return FALSE;
}

/***************************************************************
* ���饹���ѥ�᡼�����Խ��Υ���å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_edit_class( long btn, long n, const char *macro )
{
	switch( btn ){
	case 0:
		set_key_buf_char_tail( '\n' );
		return TRUE;
	case 1:
	case 2:
		break;
	}

	return FALSE;
}

/***************************************************************
* ���ƤΥ�����Υѥ�᡼�����Խ�
* class_t *org : ���饹�ν������Υѥ�᡼��
* class_t *dst : ���饹�ν�����Υѥ�᡼��
* edit_skill_t sel_n : �ѥ�᡼��
***************************************************************/

void	draw_edit_skill_all(
	class_t *org, class_t *dst,
	edit_skill_t sel_n
)
{
	long	i;

	/* �ޥ����Υϥ�ɥ��ꥻ�å� */

	call_cui_mouse_reset_handler_tab();

	/* ���̾õ� */

	wipe_all();
	redraw_msg();
	draw_stat_bar();

	/* ���������� */
	for( i = 0; i < WIN_MAP_DRAW_MAX_Y + 1; i++ )
		print_str( WIN_MAP_DRAW_MAX_X + 1, i, MSG_V_LINE );
	/* ���������� */
	print_str( SCREEN_MIN_X, WIN_MAP_DRAW_MAX_Y + 1, MSG_H_FRAME );

	/* ���� */

	for( i = EDIT_SKILL_NULL + 1; i < EDIT_SKILL_MAX_N; i++ ){
		edit_skill_t	n;

		n = (edit_skill_t)i;
		if( n == sel_n )
			draw_edit_skill( org, dst, n, TRUE, TRUE );
		else
			draw_edit_skill( org, dst, n, FALSE, TRUE );
	}

	/* �ޥ������ۥ����� */
	set_cui_mouse_add_handler_common_scroll();
}

/***************************************************************
* ������Υѥ�᡼�����Խ�
* class_t *org : ���饹�ν������Υѥ�᡼��
* class_t *dst : ���饹�ν�����Υѥ�᡼��
* edit_skill_t n : �ѥ�᡼��
* bool_t flg_sel : �����椫?
* bool_t flg_all : ���ǡ�����ɽ����?
***************************************************************/

void	draw_edit_skill(
	class_t *org, class_t *dst, edit_skill_t n,
	bool_t flg_sel, bool_t flg_all
)
{
	const char	*name;
	rate_t	rate;
	long	slot;
	long	x, y;
	long	len;
	char	str[127 + 1];
	const long	max_len = 127;

	if( org == NULL )
		return;
	if( dst == NULL )
		return;

	name = MSG_NULL;
	rate = 0;
	x = 0;
	y = 0;

	switch( n ){
	case EDIT_SKILL_NULL:
	case EDIT_SKILL_MAX_N:
		return;
	case EDIT_SKILL_CLASS_NAME:
		x = WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_X;
		y = WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_Y;
		if( flg_sel ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			print_str( x, y, MSG_EDIT_CLASS_NAME_SEL,
					MSG_MBR_DATA_CLASS_TTL,
					CLASS_NAME_MAX_LEN,
					dst->name );
		} else {
			curs_attrset_n( CURS_ATTR_N_NORMAL );
			print_str( x, y, MSG_EDIT_CLASS_NAME_NOT_SEL,
					MSG_MBR_DATA_CLASS_TTL,
					CLASS_NAME_MAX_LEN,
					dst->name );
		}
		curs_attrset_dflt();
		return;
	case EDIT_SKILL_PREV:
		x = WIN_EDIT_CLASS_PREV_DRAW_MIN_X;
		y = WIN_EDIT_CLASS_PREV_DRAW_MIN_Y;
		if( flg_sel ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			print_str( x, y, MSG_MBR_DATA_SEL,
					MSG_EDIT_CLASS_PREV );
		} else {
			curs_attrset_n( CURS_ATTR_N_NORMAL );
			print_str( x, y, MSG_MBR_DATA_NOT_SEL,
					MSG_EDIT_CLASS_PREV );
		}
		curs_attrset_dflt();
		return;
	case EDIT_SKILL_NEXT:
		x = WIN_EDIT_CLASS_NEXT_DRAW_MIN_X;
		y = WIN_EDIT_CLASS_NEXT_DRAW_MIN_Y;
		if( flg_sel ){
			curs_attrset_n( CURS_ATTR_N_MENU_SEL );
			print_str( x, y, MSG_MBR_DATA_SEL,
					MSG_EDIT_CLASS_NEXT );
		} else {
			curs_attrset_n( CURS_ATTR_N_NORMAL );
			print_str( x, y, MSG_MBR_DATA_NOT_SEL,
					MSG_EDIT_CLASS_NEXT );
		}
		curs_attrset_dflt();
		return;
	case EDIT_SKILL_A_00:
	case EDIT_SKILL_A_01:
	case EDIT_SKILL_A_02:
	case EDIT_SKILL_A_03:
	case EDIT_SKILL_A_04:
	case EDIT_SKILL_A_05:
	case EDIT_SKILL_A_06:
	case EDIT_SKILL_A_07:
	case EDIT_SKILL_A_08:
	case EDIT_SKILL_A_09:
		slot = n - EDIT_SKILL_A_00;

		x = WIN_MBR_DATA_SKILL_HINT_DRAW_MIN_X;
		y = WIN_MBR_DATA_SKILL_HINT_DRAW_MIN_Y;
		if( flg_sel )
			print_skill_hint( x, y, dst->skill[slot] );

		name = get_skill_name_from_kind( dst->skill[slot] );
		rate = calc_skill_exp_rate( dst, dst->skill[slot] );
		x = WIN_MBR_DATA_SKILL_NAME_DRAW_MIN_X;
		y = WIN_MBR_DATA_SKILL_NAME_DRAW_MIN_Y
				+ n - EDIT_SKILL_A_00;
		break;
	case EDIT_SKILL_B_00:
	case EDIT_SKILL_B_01:
	case EDIT_SKILL_B_02:
	case EDIT_SKILL_B_03:
	case EDIT_SKILL_B_04:
	case EDIT_SKILL_B_05:
	case EDIT_SKILL_B_06:
	case EDIT_SKILL_B_07:
	case EDIT_SKILL_B_08:
	case EDIT_SKILL_B_09:
		slot = n - EDIT_SKILL_B_00 + SKILL_PER_PAGE_MAX_N;

		x = WIN_MBR_DATA_SKILL_HINT_DRAW_MIN_X;
		y = WIN_MBR_DATA_SKILL_HINT_DRAW_MIN_Y;
		if( flg_sel )
			print_skill_hint( x, y, dst->skill[slot] );

		name = get_skill_name_from_kind( dst->skill[slot] );
		rate = calc_skill_exp_rate( dst, dst->skill[slot] );
		x = WIN_MBR_DATA_SKILL_NAME_DRAW_MIN_X
				+ WIN_MBR_DATA_DRAW_MID_X;
		y = WIN_MBR_DATA_SKILL_NAME_DRAW_MIN_Y
				+ n - EDIT_SKILL_B_00;
		break;
	}

	len = get_pading_len( name, SKILL_NAME_MAX_LEN );
	if( flg_sel ){
		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
		sn_printf( str, max_len, MSG_EDIT_SKILL_SEL,
				len, name, rate );
		print_str( x, y, "%s", str );
	} else {
		curs_attrset_n( CURS_ATTR_N_NORMAL );
		sn_printf( str, max_len, MSG_EDIT_SKILL_NOT_SEL,
				len, name, rate );
		print_str( x, y, "%s", str );
	}
	curs_attrset_dflt();

	/* �ޥ����Υϥ�ɥ������ */

	if( flg_sel )
		g_cui_mouse_edit_skill_sel_n = n;

	if( flg_all ){
		call_cui_mouse_add_handler(
				TRUE,
				x, y, str_len_draw( str ), 1,
				cb_cui_mouse_point_edit_skill,
				cb_cui_mouse_click_edit_skill,
				NULL,
				n, "" );
	}
}

/***************************************************************
* �����롦�ѥ�᡼�����Խ��Υݥ���ȤΥޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_point_edit_skill( long btn, long n, const char *macro )
{
	long	dn;
	long	i;

	dn = n - g_cui_mouse_edit_skill_sel_n;

	switch( btn ){
	case 0:
		for( i = 0; i < labs( dn ); i++ ){
			if( dn <= -1 )
				set_key_buf_char_tail( '8' );
			if( dn >= +1 )
				set_key_buf_char_tail( '2' );
		}
		return TRUE;
	case 1:
	case 2:
		break;
	}

	return FALSE;
}

/***************************************************************
* �����롦�ѥ�᡼�����Խ��Υ���å��Υޥ������ϥ�ɥ�
* long btn : �ܥ����ֹ�
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* return : ���٥�Ȥ������(���Ť����ʤ�)��?
***************************************************************/

bool_t	cb_cui_mouse_click_edit_skill( long btn, long n, const char *macro )
{
	switch( btn ){
	case 0:
		set_key_buf_char_tail( '\n' );
		return TRUE;
	case 1:
	case 2:
		break;
	}

	return FALSE;
}

/***************************************************************
* ���饹��̾�������Ϥ���
* char *name : ���饹��̾��
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	gets_class_name( char *name )
{
	long	x, y;

	if( name == NULL )
		return FALSE;

	/* ����������֤򥻥å� */

	x = WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_X;
	y = WIN_MBR_DATA_CLASS_TTL_DRAW_MIN_Y;
	x += str_len_draw( MSG_MBR_DATA_CLASS_TTL );

	return( game_gets( x, y, MSG_MBR_DATA_CLASS_TTL,
			name, CLASS_NAME_MAX_LEN, TRUE ) );
}

/***************************************************************
* �����ƥ��̾�������Ϥ���
* char *name : �����ƥ��̾��
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	gets_item_alias( char *name )
{
	long	x, y;

	if( name == NULL )
		return FALSE;

	/* ����������֤򥻥å� */

	x = WIN_MSG_DRAW_MIN_X;
	y = get_screen_row() - 1;

	print_msg( FLG_NULL, "%s%s", MSG_GETS_ITEM_ALIAS, name );
	x += str_len_draw( MSG_GETS_ITEM_ALIAS );

	return( game_gets( x, y, MSG_GETS_ITEM_ALIAS,
			name, CLASS_NAME_MAX_LEN, TRUE ) );
}

/***************************************************************
* �����˥塼�ξܺ�̾�����Ϥ���
* char *name : �ܺ�̾
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	gets_auto_mark_info( char *name )
{
	long	x, y;

	if( name == NULL )
		return FALSE;

	/* ����������֤򥻥å� */

	x = WIN_AUTO_MARK_INFO_TTL_DRAW_MIN_X;
	y = WIN_AUTO_MARK_INFO_TTL_DRAW_MIN_Y;

	print_str( x, y, MSG_GETS_AUTO_MARK_INFO_TTL, name );
	y++;
	print_str( x, y, MSG_S, MSG_GETS_AUTO_MARK_INFO_NAME );
	x += str_len_draw( MSG_GETS_AUTO_MARK_INFO_NAME );

	return( game_gets( x, y, MSG_GETS_AUTO_MARK_INFO_NAME,
			name, MSG_TTL_AUTO_MARK_INFO_MAX_LEN, TRUE ) );
}

/***************************************************************
* �����˥塼�Υҥ��̾(������)�����Ϥ���
* char *name : �ҥ��̾(������)
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	gets_auto_mark_hint( char *name )
{
	long	x, y;

	if( name == NULL )
		return FALSE;

	/* ����������֤򥻥å� */

	x = WIN_AUTO_MARK_HINT_TTL_DRAW_MIN_X;
	y = WIN_AUTO_MARK_HINT_TTL_DRAW_MIN_Y;

	print_str( x, y, MSG_GETS_AUTO_MARK_HINT_TTL, name );
	y++;
	print_str( x, y, MSG_S, MSG_GETS_AUTO_MARK_HINT_NAME );
	x += str_len_draw( MSG_GETS_AUTO_MARK_HINT_NAME );

	return( game_gets( x, y, MSG_GETS_AUTO_MARK_HINT_NAME,
			name, MSG_TTL_AUTO_MARK_HINT_MAX_LEN, TRUE ) );
}

/***************************************************************
* ��å������Ԥ� 1 �����Ϥ���
* char *s : ������
* const char *prompt : �ץ��ץ�
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	gets_line( const char *prompt, char *s, long max_len )
{
	long	x, y;

	if( s == NULL )
		return FALSE;

	/* �桼���ˤ�륭���ܡ��ɤ�������ϤǤʤ���� */
	/* �󥤥󥿡��饯�ƥ��֡��⡼�ɤ����� */

	if( chk_key_buf() ){
		char	c;
		long	i, j;

		for( i = 0, j = 0; LOOP_MAX_10000; i++ ){
			c = get_key( FALSE );

			if( c == '\n' )
				break;

			if( i < max_len ){
				s[j] = c;
				j++;
			}
		}
		s[j] = '\0';

		return TRUE;
	}

	/* ���󥿡��饯�ƥ��֡��⡼�ɤ����� */

	/* ����������֤򥻥å� */

	if( s == NULL )
		x = 0;
	else
		x = str_len_draw( prompt );

	y = get_screen_row() - 1;

	/* �ץ��ץȤ�ɽ�� */

	print_str( 0, y, "%*c", WIN_MSG_DRAW_WIDTH, ' ' );
	print_str( 0, y, "%s", prompt );

	/* ���� */

	if( !game_gets( x, y, prompt, s, max_len, TRUE ) )
		return FALSE;

	print_msg( FLG_NULL, "%s%s", prompt, s );

	return TRUE;
}

/***************************************************************
* ʸ�����1�����Ϥ���
* long x : ���������X��ɸ
* long y : ���������Y��ɸ
* char *ttl : �����ȥ�
* char *s : ʸ����Хåե�
* long len : �Хåե��κ���ʸ����
* bool_t flg_pick : ����ȥ��롦�����ɤ��������?
* return : ���Ϥ��������ä���?
***************************************************************/

bool_t	game_gets(
	long x, long y,
	const char *ttl, char *s, long len,
	bool_t flg_pick
)
{
	static char	buf[1023 + 1];
	bool_t	flg_draw_menu_pre;

	if( s == NULL )
		return FALSE;

	len = min_l( len, (sizeof( buf ) / sizeof( buf[0] ) - 1 - 1) );
	buf[0] = '\0';

	/* ����������֤򥻥å� */

	if( (x >= 0) && (y >= 0) )
		set_crsr( x, y );

	flg_draw_menu_pre = flg_draw_menu;
	flg_draw_menu = TRUE;
	if( g_flg_gui ){
		str_nz_cpy( buf, s, len );
		game_gets_gui_sub( ttl, buf, len );
	} else if( g_flg_cui ){
		/* �����ߥʥ�Υ⡼�ɤ���Ū���̾�ˤ��� */

		curs_echo();
		dis_term();
		curs_refresh();
		dis_curs();

		/* ʸ��������Ϥ��� */

		curs_getnstr( buf, len + 1 );

		/* �����ߥʥ�Υ⡼�ɤ��᤹ */

		ena_curs();
		curs_refresh();
		ena_term();
		curs_noecho();
	} else {
		flg_draw_menu = FALSE;
		return FALSE;
	}
	flg_draw_menu = flg_draw_menu_pre;

	/* ����ȥ��롦�����ɤ��������? */

	if( flg_pick )
		pick_cntrl_str( buf );
	if( buf[strlen( buf )] == '\n' )
		buf[strlen( buf )] = '\0';

	/* ���Ϥ��줿��? */
	if( str_len_std( buf ) <= 0 )
		return FALSE;

	/* ���Ϥ�Хåե��˥��ԡ����� */
	buf[len] = '\0';
	str_nz_cpy( s, buf, len );

	return TRUE;
}

/***************************************************************
* GUI ����ʸ�����1�����Ϥ���
* char *ttl : �����ȥ�
* char *s : ʸ����Хåե�
* long len : �Хåե��κ���ʸ����
***************************************************************/

void	game_gets_gui_sub( const char *ttl, char *s, long len )
{
	static char	buf[1023 + 1];
	long c;
	long n;

	len = min_l( len, (sizeof( buf ) / sizeof( buf[0] ) - 1 - 1) );

	buf[0] = '\0';
	c = '\0';
	n = 0;

	call_gui_input_string_draw( ttl, s, len );

	while( 1 ){
		c = get_key_buf_char();
		if( c == '\0' )
			if( read_char( &c ) <= 0 )
				continue;

		if( c == '\0' )
			continue;
		if( c == ('H' - '@') ){
			n--;
			if( n < 0 )
				n = 0;
			continue;
		}

		/* break �Ϥ��ʤ� */
		if( c == '\n' )
			;
		/* ���Ͻ�λ */
		if( c == '\r' )
			break;

		if( n < len )
			buf[n] = c;
		n++;
	}

	/* �����˲��Ԥ�ͭ���ȴ����Ƥ��ޤ��Τ�������֤� */

	if( n > (len - 1) )
		n = len - 1;
	if( n >= 0 )
		buf[n] = '\n';
	n++;

	if( n > len )
		n = len;
	buf[n] = '\0';

	str_nz_cpy( s, buf, len );

	call_gui_input_string_wipe();
}

/***************************************************************
* ʸ������Υ���ȥ��롦�����ɤ������
* char *s : ʸ����Хåե�
***************************************************************/

void	pick_cntrl_str( char *s )
{
	char	*dst;

	for( dst = s; *s != '\0'; s++ ){
#if FLAG_USE_ISCNTRL
		if( !iscntrl( *s ) ){
			*dst = *s;
			dst++;
		}
#else
		if( (*s < 0) || (0x20 <= *s) ){
			*dst = *s;
			dst++;
		}
#endif
	}

	*dst = '\0';
}

/***************************************************************
* ����������֤򥻥å�
* long x : ���������X��ɸ
* long y : ���������Y��ɸ
***************************************************************/

void	set_crsr( long x, long y )
{
	curs_move( y, x );
	curs_refresh();
}

/***************************************************************
* ���������ɽ�����֤������ΰ��֤˥��å�
***************************************************************/

void	reset_crsr( void )
{
	pos_t	*cur, *draw;

	draw = get_map_draw_pos();
	if( draw == NULL )
		return;

	cur = get_main_crsr();

	set_crsr( (cur->x - draw->x) * 2, (cur->y - draw->y) );
}

/***************************************************************
* �������������
***************************************************************/

void	draw_main_crsr( void )
{
	volatile pos_t	*main_crsr;
	pos_t	*pre_main_crsr;
	crsr_ptn_t	*ptn;
	long	gw, gh, gx1, gy1, gx2, gy2;
	long	cw, ch, cx1, cy1, cx2, cy2;
	long	x1, y1, x2, y2;
	long	new_x, new_y;
	long	pre_x, pre_y;

	main_crsr = get_main_crsr();
	pre_main_crsr = get_pre_main_crsr();
	ptn = get_main_crsr_ptn();

	/* volatile ���ѿ����ɤ߹��� */

	new_x = main_crsr->x;
	new_y = main_crsr->y;
	pre_x = pre_main_crsr->x;
	pre_y = pre_main_crsr->y;

	/* ��������θŤ����֤�õ� */

	gw = call_pcg_dun_get_crsr_width( FALSE );
	gh = call_pcg_dun_get_crsr_height( FALSE );
	gx1 = pre_x - (gw / 2);
	gy1 = pre_y - (gh / 2);
	gx2 = gx1 + gw;
	gy2 = gy1 + gh;

	cw = ptn->x_len;
	ch = ptn->y_len;
	cx1 = pre_x + ptn->x;
	cy1 = pre_y + ptn->y;
	cx2 = cx1 + cw;
	cy2 = cy1 + ch;

	x1 = min_l( gx1, cx1 );
	x2 = max_l( gx2, cx2 );
	y1 = min_l( gy1, cy1 );
	y2 = max_l( gy2, cy2 );

	draw_map_force( x1, y1, x2 - x1, y2 - y1 );

	/* ��������ο��������֤����� */

	gw = call_pcg_dun_get_crsr_width( FALSE );
	gh = call_pcg_dun_get_crsr_height( FALSE );
	gx1 = new_x - (gw / 2);
	gy1 = new_y - (gh / 2);
	gx2 = gx1 + gw;
	gy2 = gy1 + gh;

	cw = ptn->x_len;
	ch = ptn->y_len;
	cx1 = new_x + ptn->x;
	cy1 = new_y + ptn->y;
	cx2 = cx1 + cw;
	cy2 = cy1 + ch;

	x1 = min_l( gx1, cx1 );
	x2 = max_l( gx2, cx2 );
	y1 = min_l( gy1, cy1 );
	y2 = max_l( gy2, cy2 );

	draw_map_force( x1, y1, x2 - x1, y2 - y1 );

	/**/

	pre_main_crsr->x = new_x;
	pre_main_crsr->y = new_y;
}

/***************************************************************
* ���֡��������������
***************************************************************/

void	draw_sub_crsr( void )
{
	dun_t	*dun = get_dun();
	volatile pos_t	*main_crsr, *sub_crsr;
	pos_t	*pre_sub_crsr;
	crsr_ptn_t	*ptn;
	long	gw, gh, gx1, gy1, gx2, gy2;
	long	cw, ch, cx1, cy1, cx2, cy2;
	long	x1, y1, x2, y2;
	long	new_x, new_y;
	long	pre_x, pre_y;
	chr_t	*chr;

	main_crsr = get_main_crsr();
	sub_crsr = get_sub_crsr();
	pre_sub_crsr = get_pre_sub_crsr();
	ptn = get_sub_crsr_ptn();

	sub_crsr->x = MAP_DEL_X;
	sub_crsr->y = MAP_DEL_Y;

	/* �ᥤ�󡦥������뤬���С��ξ夫�����å� */

	chr = dun->map.chr_p[main_crsr->y][main_crsr->x];
	if( is_mbr( chr ) || is_pet( chr ) ){
		move_chr_trgt( chr );

		switch( chr->trgt.kind ){
		case TRGT_KIND_NULL:
		case TRGT_KIND_SQUARE:
		case TRGT_KIND_AUTO:
		case TRGT_KIND_MAX_N:
			break;
		case TRGT_KIND_MBR:
		case TRGT_KIND_MNSTR:
		case TRGT_KIND_MNSTR_NULL:
		case TRGT_KIND_ITEM:
		case TRGT_KIND_DOOR:
		case TRGT_KIND_TRAP:
		case TRGT_KIND_QUEUE:
		case TRGT_KIND_POS:
			/* ���֡���������򥻥å� */
			sub_crsr->x = chr->trgt.true_x;
			sub_crsr->y = chr->trgt.true_y;
			break;
		}
	}

	/* volatile ���ѿ����ɤ߹��� */

	new_x = sub_crsr->x;
	new_y = sub_crsr->y;
	pre_x = pre_sub_crsr->x;
	pre_y = pre_sub_crsr->y;

	/* ��������θŤ����֤�õ� */

	gw = call_pcg_dun_get_crsr_width( TRUE );
	gh = call_pcg_dun_get_crsr_height( TRUE );
	gx1 = pre_x - (gw / 2);
	gy1 = pre_y - (gh / 2);
	gx2 = gx1 + gw;
	gy2 = gy1 + gh;

	cw = ptn->x_len;
	ch = ptn->y_len;
	cx1 = pre_x + ptn->x;
	cy1 = pre_y + ptn->y;
	cx2 = cx1 + cw;
	cy2 = cy1 + ch;

	x1 = min_l( gx1, cx1 );
	x2 = max_l( gx2, cx2 );
	y1 = min_l( gy1, cy1 );
	y2 = max_l( gy2, cy2 );

	draw_map_force( x1, y1, x2 - x1, y2 - y1 );

	/* ��������ο��������֤����� */

	gw = call_pcg_dun_get_crsr_width( TRUE );
	gh = call_pcg_dun_get_crsr_height( TRUE );
	gx1 = new_x - (gw / 2);
	gy1 = new_y - (gh / 2);
	gx2 = gx1 + gw;
	gy2 = gy1 + gh;

	cw = ptn->x_len;
	ch = ptn->y_len;
	cx1 = new_x + ptn->x;
	cy1 = new_y + ptn->y;
	cx2 = cx1 + cw;
	cy2 = cy1 + ch;

	x1 = min_l( gx1, cx1 );
	x2 = max_l( gx2, cx2 );
	y1 = min_l( gy1, cy1 );
	y2 = max_l( gy2, cy2 );

	draw_map_force( x1, y1, x2 - x1, y2 - y1 );

	/**/

	pre_sub_crsr->x = new_x;
	pre_sub_crsr->y = new_y;
}

/***************************************************************
* �ޥåפΥ���������֤��֤�
* return : �ޥåפΥ����������
***************************************************************/

pos_t	*get_map_draw_pos( void )
{
	return &map_draw_pos;
}

/***************************************************************
* �ޥåפΥ���������֤��֤� (GUI)
* return : �ޥåפΥ����������
***************************************************************/

pos_t	*get_map_draw_pos_gui( void )
{
	if( g_flg_gui )
		return &map_draw_pos_gui;
	else
		return &map_draw_pos;
}

/***************************************************************
* ������Ԥ����֤��֤�
* return : �Ԥ�����
***************************************************************/

rate_t	get_vfx_wait( void )
{
	return vfx_wait;
}

/***************************************************************
* ������Ԥ����֤�����
* rate_t n : �Ԥ�����
* return : �������Ԥ�����
***************************************************************/

rate_t	set_vfx_wait( rate_t n )
{
	if( n < VFX_WAIT_MIN_N )
		n = VFX_WAIT_MIN_N;
	if( n > VFX_WAIT_MAX_N )
		n = VFX_WAIT_MAX_N;

	vfx_wait = n;

	return vfx_wait;
}

/***************************************************************
* ���С������褹�륨�ե����ȤΥե��륿�����֤�
* return : �ե��륿��
***************************************************************/

flg_vfx_mbr_t	get_flg_vfx_mbr( void )
{
	return flg_vfx_mbr;
}

/***************************************************************
* ���С������褹�륨�ե����ȤΥե��륿��������
* flg_vfx_mbr_t flg : �ե��륿��
* return : �����Υե��륿��
***************************************************************/

flg_vfx_mbr_t	set_flg_vfx_mbr( flg_vfx_mbr_t flg )
{
	flg_vfx_mbr = flg;

	return flg_vfx_mbr;
}

/***************************************************************
* ��󥹥��������褹�륨�ե����ȤΥե��륿�����֤�
* return : �ե��륿��
***************************************************************/

flg_vfx_mnstr_t	get_flg_vfx_mnstr( void )
{
	return flg_vfx_mnstr;
}

/***************************************************************
* ��󥹥��������褹�륨�ե����ȤΥե��륿��������
* flg_vfx_mnstr_t flg : �ե��륿��
* return : �����Υե��륿��
***************************************************************/

flg_vfx_mnstr_t	set_flg_vfx_mnstr( flg_vfx_mnstr_t flg )
{
	flg_vfx_mnstr = flg;

	return flg_vfx_mnstr;
}

/***************************************************************
* ���ꤷ���ե졼��δ֡������Ԥ�
* long frame : �ե졼��
***************************************************************/

void	wait_clock( long frame )
{
	/* ������Ԥ����֤ǥե졼�����Ĵ�� */

	if( frame <= 0 )
		return;

	frame = frame * get_vfx_wait() / _100_PERCENT;
	if( frame < 1 )
		frame = 1;

	wait_frame( frame );
}

/***************************************************************
* ���ꤷ���ե졼��δ֡������Ԥ� (Ĵ��̵��)
* long frame : �ե졼��
***************************************************************/

void	wait_frame( long frame )
{
	long	n;

	if( frame <= 0 )
		return;

	n = 1000 * frame / ANIM_FRAME_N;
	sleep_msec( n );
}

/***************************************************************
* �ߥ���ñ�̤ǥ��꡼��
* long n : �Ի��� (�ߥ���ñ��)
***************************************************************/

void	sleep_msec( long n )
{
#if	defined( D_MFC )
	call_sleep( n );
#elif	defined( D_DOS )
	wait_100_n_msec( n / 100 );
#elif	defined( HAVE_USLEEP )
	usleep( n * 1000 );
#elif	defined( HAVE_NANOSLEEP )
	{
		struct timespec	spec;

		spec.tv_sec = (time_t)(n / 1000);
		spec.tv_nsec = (n % 1000) * 1000 * 1000;

		nanosleep( &spec, NULL );
	}
#elif	defined( HAVE_SLEEP )
	sleep( n / 1000 );
	n %= 1000;
	wait_100_n_msec( n / 100 );
#else
	wait_100_n_msec( n / 100 );
#endif
}

/***************************************************************
* 100 �ߥ���ñ�̤ǻ����Ԥ�
* long n : �Ի��� (100 �ߥ���ñ��)
***************************************************************/

void	wait_100_n_msec( long n )
{
	long	i;

	for( i = 0; i < n; i++ )
		wait_100_msec();
}

/***************************************************************
* 100 �ߥ��äδ֡������Ԥ�
***************************************************************/

void	wait_100_msec( void )
{
#if	defined( D_MFC )
	call_sleep( 100 );
#elif	defined( D_DOS )
	{
		clock_t	end_clock;

		end_clock = clock() + (clock_t)(g_clk_tck * 100 / 1000);
		while( clock() < end_clock )
			;
	}
#elif	defined( HAVE_TERMIOS_H ) || defined( HAVE_TERMIO_H )
	{
		long	n;
		long	c;

		set_key_wait_vtime( 1 );
		n = read_char( &c );
		set_key_wait_vtime( 0 );

		if( (n > 0) && (c != '\0') )
			set_key_buf_char_head( c );
	}
#else
	{
		clock_t	end_clock;

		end_clock = clock() + (clock_t)(g_clk_tck * 100 / 1000);
		while( clock() < end_clock )
			;
	}
#endif
}

/***************************************************************
* �������Ϥ����Ǥ��뤫����
***************************************************************/

void	set_flg_break_key( bool_t flg_break )
{
	g_flg_break_key = flg_break;
}

/***************************************************************
* �������Ϥ����Ǥ��뤫�����å�
* return : �������Ϥ����Ǥ��뤫?
***************************************************************/

bool_t	chk_flg_break_key( void )
{
	if( g_flg_break_key ){
		g_flg_break_key = FALSE;

		return TRUE;
	}

	return FALSE;
}

/***************************************************************
* 1 ʸ����������
* long *p : ���Ϥ��줿�������֤�
* return : ���Ϥ��줿ʸ����
***************************************************************/

long	read_char( long *p )
{
	*p = curs_getch();

	/* �������Ѵ� */

	switch( *p ){
	case '\0':
	case -1:
		return 0;
	case '^':
		return read_ctrl( p );
	case 0x199:
		*p = call_cui_mouse_check_event( *p );
		if( (*p == '\0') || (*p <= -1) )
			return 0;
		break;
	case 0xe0:
		/* MS-Windows �б� */

		*p = curs_getch();
		switch( *p ){
		case 'H':
			*p = '8';
			break;
		case 'P':
			*p = '2';
			break;
		case 'M':
			*p = '6';
			break;
		case 'K':
			*p = '4';
			break;
		case 'R':
			*p = '/';
			break;
		case 'G':
			*p = '*';
			break;
		case 'I':
			*p = '-';
			break;
		case 'Q':
			*p = '+';
			break;
		case 'S':
			*p = 'H' - '@';
			break;
		case 'O':
			*p = '.';
			break;
		default:
			break;
		}
		break;
	case '\033':
		return read_esc( p );
		break;
	case 0x7f:
		*p = 'H' - '@';
		break;
	case KEY_BACKSPACE:
		*p = 'H' - '@';
		break;
	case KEY_ENTER:
		*p = 'M' - '@';
		break;
	case KEY_IC:
		*p = '/';
		break;
	case KEY_HOME:
		*p = '*';
		break;
	case KEY_PPAGE:
		*p = '-';
		break;
	case KEY_NPAGE:
		*p = '+';
		break;
	case KEY_DC:
		*p = 'H' - '@';
		break;
	case KEY_END:
		*p = '.';
		break;
	case KEY_UP:
		*p = '8';
		break;
	case KEY_DOWN:
		*p = '2';
		break;
	case KEY_RIGHT:
		*p = '6';
		break;
	case KEY_LEFT:
		*p = '4';
		break;
	}

	return 1;
}

/***************************************************************
* ���������Ϥ����ޤ��Ԥ�
* long *p : ���Ϥ��줿�������֤�
* return : ���Ϥ��줿ʸ����
***************************************************************/

long	read_char_wait( long *p )
{
	do {
		if( chk_flg_break_key() ){
			*p = '\0';
			return 1;
		}

		*p = curs_getch();
	} while( (*p == '\0') || (*p == -1) );

	return 1;
}

/***************************************************************
* '^' ������³�������򥳥�ȥ��롦�����ɤ��Ѵ�
* long *p : ���Ϥ��줿�������֤�
* return : ���Ϥ��줿ʸ����
***************************************************************/

long	read_ctrl( long *p )
{
	long	key;

	key = '\0';
	read_char_wait( &key );

	if( ('\100' <= key) && (key <= '\137') ){
		*p = key - '\100';
		return 1;
	}
	if( ('\140' <= key) && (key <= '\177') ){
		*p = key - '\140';
		return 1;
	}

	*p = key;
	return 1;
}

/***************************************************************
* ESC ������³�����������Ϥ���
* long *p : ���Ϥ��줿�������֤�
* return : ���Ϥ��줿ʸ����
***************************************************************/

long	read_esc( long *p )
{
	long	key, key2;

	key = '\0';
	key2 = '\0';

	read_char_wait( &key );
	if( key == '\033' ){
		;
	} else if( (key == '[') || (key == 'O') ){
		read_char_wait( &key );
		if( isdigit( key ) ){
			read_char_wait( &key2 );
		} else if( key == 'M' ){
			/* CUI mouse */
			read_char_wait( &key2 );
			read_char_wait( &key2 );
			read_char_wait( &key2 );
		}
	}

	/* �������Ѵ� */

	switch( key ){
	default:
		*p = '\0';
		return 0;
	case '\033':
		*p = '\033';
		break;
	case 'A':
		*p = '8';
		break;
	case 'B':
		*p = '2';
		break;
	case 'C':
		*p = '6';
		break;
	case 'D':
		*p = '4';
		break;
	case 'j':
		*p = '*';
		break;
	case 'k':
		*p = '+';
		break;
	case 'm':
		*p = '-';
		break;
	case 'o':
		*p = '/';
		break;
	case '1':
		*p = '*';
		break;
	case '2':
		*p = '/';
		break;
	case '3':
		*p = '0';
		break;
	case '4':
		*p = '.';
		break;
	case '5':
		*p = '-';
		break;
	case '6':
		*p = '+';
		break;
	}

	return 1;
}

/***************************************************************
* ��Ͽ�⡼�ɤ����ꤷ���ޥ�����֤�
* return : ��Ͽ�����ޥ���
***************************************************************/

char	*get_reg_macro( void )
{
	return cv_esc_ctrl_str( g_reg_macro_buf );
}

/***************************************************************
* �ޥ���ε�Ͽ�⡼�ɤ�����
* bool_t flg : �ޥ���ε�Ͽ�⡼��
***************************************************************/

void	set_reg_macro( bool_t flg )
{
	g_flg_reg_macro = flg;

	if( flg ){
		g_reg_macro_idx = 0;
		print_msg( FLG_NULL, MSG_REG_MACRO_BGN );
	} else {
		print_msg( FLG_NULL, MSG_REG_MACRO_END,
				cv_esc_ctrl_str( g_reg_macro_buf ) );
	}
}

/***************************************************************
* �ޥ���ε�Ͽ�⡼�ɤλ���ʸ�����Ͽ
* const char *s : ʸ����
***************************************************************/

void	reg_macro_str( const char *s )
{
	long	i;

	if( !g_flg_reg_macro )
		return;

	for( i = 0; s[i] != '\0'; i++ ){
		reg_macro( s[i] );
	}
}

/***************************************************************
* �ޥ���ε�Ͽ�⡼�ɤλ��˥������Ϥ�Ͽ
* long c : ��������
***************************************************************/

void	reg_macro( long c )
{
	if( !g_flg_reg_macro )
		return;

	if( g_reg_macro_idx >= REG_MACRO_LEN ){
		print_msg( FLG_MSG_ERR, MSG_ERR_REG_MACRO_BUF_OVERFLOW );
		return;
	}

	g_reg_macro_buf[g_reg_macro_idx] = c;
	g_reg_macro_idx++;
	g_reg_macro_buf[g_reg_macro_idx] = '\0';
}

/***************************************************************
* ��ץ쥤������ɽ��
***************************************************************/

void	draw_replay( bool_t flg_redraw )
{
	static char	pre_buf[16 + 1] = "";
	static char	buf[SCREEN_WIDTH + 4 + 1] = "";
	static char	tmp[SCREEN_WIDTH + 4 + 1] = "";
	long	pre_idx;
	long	idx;
	long	len;

	pre_idx = static_draw_replay__pre_idx;

	if( !get_flg_play_replay() ){
		return;
	}

	flg_redraw |= get_draw_replay( buf, &idx, &len );

	if( flg_redraw ){
		/* ��������� 1 �����ޤ����� */

		str_nz_cpy( tmp, &(buf[0]), idx );
		curs_attrset_n( CURS_ATTR_N_NORMAL );
		print_str( WIN_MSG_DRAW_MIN_X,
				get_map_row(),
				"%s", tmp );

		/* ������������� */

		str_nz_cpy( tmp, &(buf[idx]), len );
		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
		print_str( WIN_MSG_DRAW_MIN_X + idx,
				get_map_row(),
				"%s", tmp );

		/* ��������ξ��֤򵭲� */

		str_nz_cpy( pre_buf, &(buf[idx]), len );
		pre_idx = idx;

		/* ��������ʹߤ����� */

		str_nz_cpy( tmp, &(buf[idx + len]),
				SCREEN_WIDTH - idx - len );
		curs_attrset_n( CURS_ATTR_N_NORMAL );
		print_str( WIN_MSG_DRAW_MIN_X + idx + len,
				get_map_row(),
				"%-*s", SCREEN_WIDTH - idx, tmp );
	} else {
		/* 1 �����Υ��������ä� */

		curs_attrset_n( CURS_ATTR_N_NORMAL );
		print_str( WIN_MSG_DRAW_MIN_X + pre_idx,
				get_map_row(),
				"%s", pre_buf );

		/* ������������� */

		str_nz_cpy( tmp, &(buf[idx]), len );
		curs_attrset_n( CURS_ATTR_N_MENU_SEL );
		print_str( WIN_MSG_DRAW_MIN_X + idx,
				get_map_row(),
				"%s", tmp );

		/* ��������ξ��֤򵭲� */

		str_nz_cpy( pre_buf, &(buf[idx]), len );
		pre_idx = idx;
	}

	curs_attrset_dflt();
	curs_refresh();

	call_gui_replay_draw();

	static_draw_replay__pre_idx = pre_idx;
}

/***************************************************************
* ������������Ѵ��դ��κ�ɸ��������
* XnnYnn; YnnXnn; xx/yy; ���Ȼ��ꤹ��
* ����ϼ�ͳ
* �����ʳ���ʸ���Ƕ��ڤ�
* ��ץ쥤�����Υ����å�ͭ��
* �����ܡ��ɡ��ޥ���Υȥꥬ���������å�ͭ��
* return : ���Ϥ��줿����
***************************************************************/

bool_t	get_key_pos( pos_t *pos )
{
	long	c, cc;
	long	n;

	if( pos == NULL )
		return FALSE;

	pos->x = MAP_DEL_X;
	pos->y = MAP_DEL_Y;

	n = 0;
	while( 1 ){
		cc = get_key_no_null( FALSE );
		c = toupper( cc );

		/* ��üʸ�� */
		if( c == ';' )
			break;
		if( c == '\n' )
			break;
		if( c == '\r' )
			break;

		if( c == 'X' ){
			pos->x = get_key_num();
			continue;
		}
		if( c == 'Y' ){
			pos->y = get_key_num();
			continue;
		}
		if( isdigit( c ) || (c == '+') || (c == '-') ){
			un_get_key( cc );

			if( n == 0 ){
				pos->x = get_key_num();

				/* ���ڤ�ʸ�����ɤ߼Τ� */
				cc = get_key_no_null( FALSE );

				if( (cc == '+') || (cc == '-') ){
					un_get_key( cc );
				}
			} else {
				pos->y = get_key_num();
			}
			n++;

			continue;
		}
	}

	if( pos->x == MAP_DEL_X )
		return FALSE;
	if( pos->y == MAP_DEL_Y )
		return FALSE;
	return TRUE;
}

/***************************************************************
* ������������Ѵ��դ��ο��ͥ�������
* �����ʳ���ʸ���Ƕ��ڤ�
* ��ץ쥤�����Υ����å�ͭ��
* �����ܡ��ɡ��ޥ���Υȥꥬ���������å�ͭ��
* return : ���Ϥ��줿����
***************************************************************/

long	get_key_num( void )
{
	long	sgn_n, n;
	long	c;
	long	i;

	sgn_n = +1;
	n = 0;
	i = 0;

	while( 1 ){
		c = get_key_no_null( FALSE );

		if( i == 0 ){
			if( c == '+' ){
				sgn_n *= +1;
				i = 0;
				continue;
			}
			if( c == '-' ){
				sgn_n *= -1;
				i = 0;
				continue;
			}
		}

		if( !isdigit( c ) ){
			un_get_key( c );
			break;
		}

		n *= 10;
		n += c - '0';
		i++;
	}
	n *= sgn_n;

	return n;
}

/***************************************************************
* ������������Ѵ��դ��� 1 ʸ���������Ϥ������ᤷ
* long c : �����ᤷ����ʸ��
***************************************************************/

void	un_get_key( long c )
{
	g_un_get_key_c = c;
}

/***************************************************************
* �����������������ޤ��Ԥ�
* bool_t flg_clr_key_buf : �������Хåե��򥯥ꥢ���뤫?
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_no_null( bool_t flg_clr_key_buf )
{
	long	c;

	c = ' ';
	while( 1 ){
		c = get_key( flg_clr_key_buf );

		if( c == '\0' )
			continue;
		if( c == CMD_KEY_IDLE )
			continue;

		break;
	}

	return c;
}

/***************************************************************
* ������������Ѵ��դ��� 1 ʸ����������
* ��ץ쥤�����Υ����å�ͭ��
* �����ܡ��ɡ��ޥ���Υȥꥬ���������å�ͭ��
* bool_t flg_clr_key_buf : �������Хåե��򥯥ꥢ���뤫?
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key( bool_t flg_clr_key_buf )
{
	long	c, accel_key;
	bool_t	flg_set_rep;
	const long	max_len = GET_KEY_MAX_LEN;
	char	buf[GET_KEY_MAX_LEN + 1];

	if( g_flg_check_memory )
		check_memory_all();

	if( g_un_get_key_c != '\0' ){
		c = g_un_get_key_c;
		g_un_get_key_c = '\0';

		return c;
	}

	/* ��ץ쥤�κ��� */

	c = '\0';
	do {
		if( !get_flg_play_replay() ){
			c = get_key_sub( flg_clr_key_buf );
			break;
		}

		c = get_replay_key();
		if( c != '\0' )
			break;

		c = get_key_sub( flg_clr_key_buf );
		chk_replay_key( c );
		if( !get_flg_play_replay() ){
			print_msg( FLG_NULL, MSG_END_PLAY_REPLAY );
			c = '\0';
			break;
		}

		c = get_replay_key();
		if( c != '\0' )
			break;

		/* ��ץ쥤�����ν�λ */

		set_flg_play_replay( FALSE );
		print_msg( FLG_NULL, MSG_END_PLAY_REPLAY );
		print_msg( FLG_NULL, MSG_END_PLAY_REPLAY_WAIT_KEY );
		get_key_wait_cancel( flg_clr_key_buf );
		c = '\0';
		break;
	} while( 0 );

	if( c != '\0' )
		draw_replay( FALSE );

	/* ��ͳ��ư���Ƥ�����������ΰ��֤���ꤹ�� */

	flg_set_rep = FALSE;
	do {
		static long preX = MAP_DEL_X;
		static long preY = MAP_DEL_Y;
		pos_t *crsr;

		if( c == '\0' )
			break;
		if( c == CMD_KEY_IDLE )
			break;

		flg_set_rep = TRUE;

		if( !g_flg_gui )
			break;
		if( get_flg_play_replay() )
			break;

		crsr = get_main_crsr();
		if( crsr == NULL )
			break;
		if( (preX == crsr->x) && (preY == crsr->y) )
			break;
		preX = crsr->x;
		preY = crsr->y;

		/* ���ꤹ�� */

		sn_printf( buf, max_len, "%%X%ldY%ld;", crsr->x, crsr->y );
		set_replay_str( REPLAY_KIND_KEY, buf );
		break;
	} while( 0 );

	/* ��˥塼�����򥭡��򥢥��������������Ѵ� */

	accel_key = get_sel_menu_accel_key();
	if( accel_key != '\0' ){
		switch( c ){
		case ' ':
			if( get_flg_space_select() )
				c = accel_key;
			break;
		case CASE_ENTER:
			if( !get_flg_space_select() )
				c = accel_key;
			break;
		}
	}

	/* ��ץ쥤�ε�Ͽ */

	if( flg_set_rep )
		set_replay_char( REPLAY_KIND_KEY, c );

	/* �����ܡ��ɡ��ޥ���Υ����å� */

	switch( c ){
	case '\0':
	case CMD_KEY_IDLE:
		break;
	case '(':
		set_reg_macro( TRUE );
		reg_macro( '{' );
		set_flg_menu_dflt( FALSE );
		c = '\0';
		break;
	case ')':
		set_flg_menu_dflt( TRUE );
		reg_macro( '}' );
		set_reg_macro( FALSE );
		c = '\0';
		break;
	case '{':
		set_flg_menu_dflt( FALSE );
		c = '\0';
		break;
	case '}':
		set_flg_menu_dflt( TRUE );
		c = '\0';
		break;
	default:
		reg_macro( c );
		break;
	}

	return c;
}

/***************************************************************
* ����󥻥�Υ��������Ϥ����ޤ��Ԥ�
* bool_t flg_clr_key_buf : �������Хåե��򥯥ꥢ���뤫?
***************************************************************/

void	get_key_wait_cancel( bool_t flg_clr_key_buf )
{
	get_key_wait_cancel_sub( flg_clr_key_buf, FALSE );
}

/***************************************************************
* ����󥻥�ޤ��ϼ¹ԤΥ��������Ϥ����ޤ��Ԥ�
* bool_t flg_clr_key_buf : �������Хåե��򥯥ꥢ���뤫?
***************************************************************/

void	get_key_wait_cancel_or_exec( bool_t flg_clr_key_buf )
{
	get_key_wait_cancel_sub( flg_clr_key_buf, TRUE );
}

/***************************************************************
* ����󥻥�Υ��������Ϥ����ޤ��Ԥ�
* �¹ԤΥ���������ǽ
* bool_t flg_clr_key_buf : �������Хåե��򥯥ꥢ���뤫?
* bool_t flg_exec : �¹ԤΥ��������
***************************************************************/

void	get_key_wait_cancel_sub( bool_t flg_clr_key_buf, bool_t flg_exec )
{
	while( 1 ){
		switch( get_key_sub( flg_clr_key_buf ) ){
		case '\0':
		case CMD_KEY_IDLE:
			break;
		case CASE_CANCEL:
		case CASE_EXIT:
		case CMD_KEY_CONT_EXEC:
			return;
		case CASE_EXEC:
			if( g_flg_cui_mouse )
				return;
			if( flg_exec )
				return;
			break;
		default:
			if( g_flg_cui_mouse )
				return;
			break;
		}
	}
}

/***************************************************************
* ������������Ѵ��դ��� 1 ʸ����������
* Ϣ³�¹Ԥ���ߥ����å�����
* bool_t flg_clr_key_buf : �������Хåե��򥯥ꥢ���뤫?
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_sub( bool_t flg_clr_key_buf )
{
	long	c;
	bool_t	flg_cont_exec;

	flg_cont_exec = FALSE;
	c = get_key_sub_1( flg_clr_key_buf, &flg_cont_exec );

	/* �������Ϥ����ä���Ϣ³�¹Ԥ���� */

	if( (c != '\0') && !flg_cont_exec && get_continue_exec_mode() ){
		clr_continue_exec_mode();
		if( c == CMD_KEY_CONT_EXEC ){
			c = '\0';
		}
	}

	return c;
}

/***************************************************************
* ������������Ѵ��դ��� 1 ʸ����������
* bool_t flg_clr_key_buf : �������Хåե��򥯥ꥢ���뤫?
* bool_t *p_flg_cont_exec : Ϣ³�¹Ԥ���Υ������Ϥʤ� TRUE ���֤�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_sub_1( bool_t flg_clr_key_buf, bool_t *p_flg_cont_exec )
{
	long	c;

	/* �������Хåե������ޤäƤ��뤫�����å� */

	c = get_key_buf_char();
	if( c != '\0' )
		return c;

	/* �������� */

	c = get_key_sub_2( flg_clr_key_buf, p_flg_cont_exec );

	/* �ե��󥯥���󡦥����Υ����å� */

	if( (KEY_F(1) <= c) && (c <= KEY_F(KEY_N_FUNC_MAX_N)) ){
		char	str[31 + 1];
		const long	max_len = 31;

		/* �ե��󥯥���󡦥����򥭡����Хåե����ɲ� */
		sn_printf( str, max_len, "&f%ld;",
				(long)(c - KEY_F(1)) );
		set_key_buf_str_head( str );

		/* ������줿�������֤� */
		return get_key_buf_char();
	}

	/* ����������ϰϳ��������å� */

	if( ('\0' < c) && (c < KEY_TAB_MAX_N) ){
		/* ̤����ʤ�ǥե���ȤΥ������֤� */
		if( g_key_tab[c] == NULL )
			return c;

		/* ������줿�����򥭡����Хåե����ɲ� */
		set_key_buf_str_head( g_key_tab[c] );

		/* ������줿�������֤� */
		return get_key_buf_char();
	}

	return c;
}

/***************************************************************
* OS �˹�碌�� 1 ʸ����������
* bool_t flg_clr_key_buf : �������Хåե��򥯥ꥢ���뤫?
* bool_t *p_flg_cont_exec : Ϣ³�¹Ԥ���Υ������Ϥʤ� TRUE ���֤�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_sub_2( bool_t flg_clr_key_buf, bool_t *p_flg_cont_exec )
{
#ifdef	D_X68K
	return get_key_x68k( flg_clr_key_buf, p_flg_cont_exec );
#elif	defined( D_DOS )
	if( flg_clr_key_buf || g_flg_gui )
		return get_key_dos( p_flg_cont_exec );
	else
		return get_key_no_clr_dos( p_flg_cont_exec );
#else
	if( flg_clr_key_buf || g_flg_gui )
		return get_key_half_wait( p_flg_cont_exec );
	else
		return get_key_no_clr( p_flg_cont_exec );
#endif	/* D_X68K */

	return get_key_no_clr_default( p_flg_cont_exec );
}

/***************************************************************
* X680x0 �� 1 ʸ����������
* bool_t flg_clr_key_buf : �������Хåե��򥯥ꥢ���뤫?
* bool_t *p_flg_cont_exec : Ϣ³�¹Ԥ���Υ������Ϥʤ� TRUE ���֤�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_x68k( bool_t flg_clr_key_buf, bool_t *p_flg_cont_exec )
{
#ifdef	D_X68K
	static long	bc = -1;
	long	c;

	if( !flg_clr_key_buf || !g_flg_clr_key_buf ){
		/* �����Хåե��򥯥ꥢ���ʤ��� */
		c = K_KEYINP();

		return c;
	}

	c = K_KEYSNS();
	if( c == bc ){
		do {
			K_KEYINP();
			c = K_KEYSNS();
			if( c == '\0' ){
				break;
			}
		} while( c == bc );

		bc = K_KEYINP();

		return bc;
	}

	bc = K_KEYINP();

	return bc;
#else	/* D_X68K */
	return '\0';
#endif	/* D_X68K */
}

/***************************************************************
* �������Хåե������ꥢ�դ� 1 ʸ���������ϡ�MS-DOS �ѡ�
* bool_t *p_flg_cont_exec : Ϣ³�¹Ԥ���Υ������Ϥʤ� TRUE ���֤�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_dos( bool_t *p_flg_cont_exec )
{
#ifdef	D_DOS
	static long	bc = -1;
	long	c;

	c = '\0';

	if( kbhit() ){
		if( chk_flg_break_key() )
			return '\0';

		read_char( &c );
		if( c == bc ){
			do {
				if( chk_flg_break_key() )
					return '\0';

				read_char( &c );
				if( !kbhit() ){
					break;
				}
			} while( c == bc );
		}
	} else {
		if( !chk_continue_exec_mode( &c, p_flg_cont_exec ) ){
			if( g_flg_gui ){
				while( !kbhit() ){
					if( chk_flg_break_key() )
						return '\0';

					call_sleep( 1000 * 6 / 60 );
				}
			}

			read_char( &c );
		}
	}

	bc = c;

	return c;
#else	/* D_DOS */
	return get_key_no_clr_default( p_flg_cont_exec );
#endif	/* D_DOS */
}

/***************************************************************
* �������Хåե������ꥢ̵�� 1 ʸ���������ϡ�MS-DOS �ѡ�
* bool_t *p_flg_cont_exec : Ϣ³�¹Ԥ���Υ������Ϥʤ� TRUE ���֤�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_no_clr_dos( bool_t *p_flg_cont_exec )
{
#ifdef	D_DOS
	long	c;
	long	n;

	if( !kbhit() && chk_continue_exec_mode( &c, p_flg_cont_exec ) )
		return c;

	do {
		if( chk_flg_break_key() )
			return '\0';

		n = read_char( &c );
	} while( (n <= 0) || (c <= -1) );

	return c;
#else	/* D_DOS */
	return get_key_no_clr_default( p_flg_cont_exec );
#endif	/* D_DOS */
}

/***************************************************************
* �������Хåե������ꥢ�դ� 1 ʸ���������ϡ�������ǡ�
* bool_t *p_flg_cont_exec : Ϣ³�¹Ԥ���Υ������Ϥʤ� TRUE ���֤�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_half_wait( bool_t *p_flg_cont_exec )
{
#ifdef	D_DOS
	return get_key_no_clr_default( p_flg_cont_exec );
#else	/* D_DOS */
	static long	bc = -1;
	long	c;
	long	n;

	clr_key_wait();

	if( chk_flg_break_key() )
		return '\0';

	n = read_char( &c );

	if( (n <= 0) || (c <= -1) ){
		bc = -1;
		set_key_wait();
		if( chk_continue_exec_mode( &c, p_flg_cont_exec ) )
			return c;
		do {
			if( chk_flg_break_key() )
				return '\0';

			n = read_char( &c );
		} while( (n <= 0) || (c <= -1) );
	} else if( c == bc ){
		bool_t	flg_break;

		flg_break = FALSE;
		clr_key_wait();
		do {
			long	tmp_c;

			if( chk_flg_break_key() )
				return '\0';

			n = read_char( &tmp_c );
			if( tmp_c <= -1 )
				break;
			if( tmp_c != bc ){
				c = tmp_c;
				flg_break = TRUE;
				break;
			}
		} while( n > 0 );

		if( !flg_break ){
			set_key_wait();
			do {
				if( chk_flg_break_key() )
					return '\0';

				n = read_char( &c );
			} while( (n <= 0) || (c <= -1) );
		}
	}

	set_key_wait();
	bc = c;

	return c;
#endif	/* D_DOS */
}

/***************************************************************
* �������Хåե������ꥢ�դ� 1 ʸ���������ϡʹ�����ǡ�
* bool_t *p_flg_cont_exec : Ϣ³�¹Ԥ���Υ������Ϥʤ� TRUE ���֤�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_std( bool_t *p_flg_cont_exec )
{
	bool_t	flg_sync;
	static time_t	sync_time = 0;
	static clock_t	sync_clock = 0;
	static time_t	prev_time = 0;
	static clock_t	prev_clock = 0;
	clock_t	next_clock;
	const double	diff_time_sync = 1.5;
	const double	diff_time_1 = 0.5;
	const double	diff_time_2 = 0.2;
	const double	diff_clock_sync = 1.5;
	const double	diff_clock_1 = 0.5;
	const double	diff_clock_2 = 0.2;
	const long	loop_n = 16;
	static long	bc = -1;
	long	c;
	long	n;

	if( sync_time == 0 )
		sync_time = time( NULL );
	if( sync_clock == 0 )
		sync_clock = clock();
	if( prev_time == 0 )
		prev_time = time( NULL );
	if( prev_clock == 0 )
		prev_clock = clock();
	next_clock = clock();

	flg_sync = FALSE;
	do {
		if( g_flg_clr_key_buf ){
			if( difftime( time( NULL ), sync_time )
					> diff_time_sync ){
				flg_sync = TRUE;
				break;
			}
			if( next_clock < sync_clock ){
				flg_sync = TRUE;
				break;
			}
			if( (next_clock - sync_clock)
					> (diff_clock_sync * g_clk_tck) ){
				flg_sync = TRUE;
				break;
			}

			/**/

			if( difftime( time( NULL ), prev_time )
					> diff_time_1 ){
				break;
			}
			if( next_clock < prev_clock ){
				break;
			}
			if( (next_clock - prev_clock)
					> (diff_clock_1 * g_clk_tck) ){
				break;
			}
		}

		/* �����Хåե��򥯥ꥢ���ʤ��� */
		do {
			if( chk_flg_break_key() )
				return '\0';

			n = read_char( &c );
		} while( n <= 0 );

		bc = c;
		prev_time = time( NULL );
		prev_clock = clock();

		return c;
	} while( 0 );

	if( flg_sync ){
		sync_time = time( NULL );
		sync_clock = clock();
	}

	prev_time = time( NULL );
	prev_clock = clock();

	if( chk_flg_break_key() )
		return '\0';

	n = read_char( &c );
	if( n <= 0 ){
		do {
			if( chk_flg_break_key() )
				return '\0';

			n = read_char( &c );
		} while( n <= 0 );

		bc = -1;
		prev_time = time( NULL );
		prev_clock = clock();

		return c;
	}

	if( c == bc ){
		long	i;

		for( i = 0; i < loop_n; i++ ){
			long	tmp_c;

			if( chk_flg_break_key() )
				return '\0';

			n = read_char( &tmp_c );
			if( n <= 0 )
				break;
			if( tmp_c != bc ){
				c = tmp_c;
				break;
			}

			if( difftime( time( NULL ), prev_time )
					> diff_time_2 ){
				break;
			}
			if( (clock() - prev_clock)
					> (diff_clock_2 * g_clk_tck) ){
				break;
			}
		}
	}

	bc = c;
	prev_time = time( NULL );
	prev_clock = clock();

	return c;
}

/***************************************************************
* �������Хåե������ꥢ̵�� 1 ʸ����������
* bool_t *p_flg_cont_exec : Ϣ³�¹Ԥ���Υ������Ϥʤ� TRUE ���֤�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_no_clr( bool_t *p_flg_cont_exec )
{
#ifdef	D_DOS
	return get_key_no_clr_default( p_flg_cont_exec );
#else	/* D_DOS */
	long	c;
	long	n;

	clr_key_wait();
	if( chk_flg_break_key() )
		return '\0';
	n = read_char( &c );
	set_key_wait();

	if( (n <= 0) || (c <= -1) ){
		if( chk_continue_exec_mode( &c, p_flg_cont_exec ) ){
			return c;
		}
	} else {
		return c;
	}

	do {
		if( chk_flg_break_key() )
			return '\0';

		n = read_char( &c );
	} while( (n <= 0) || (c <= -1) );

	return c;
#endif	/* D_DOS */
}

/***************************************************************
* �������Хåե������ꥢ̵�� 1 ʸ���������ϡʥǥե���ȡ�
* bool_t *p_flg_cont_exec : Ϣ³�¹Ԥ���Υ������Ϥʤ� TRUE ���֤�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_no_clr_default( bool_t *p_flg_cont_exec )
{
	long	c;
	long	n;

	do {
		if( chk_flg_break_key() )
			return '\0';

		n = read_char( &c );

		if( (n <= 0) || (c <= -1) ){
			if( chk_continue_exec_mode(
					&c, p_flg_cont_exec ) ){
				return c;
			}
		}
	} while( (n <= 0) || (c <= -1) );

	return c;
}

/***************************************************************
* �����Ԥ�̵�� 1 ʸ����������
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_no_wait( void )
{
	long	c;

	c = '\0';

	c = get_key_buf_char();
	if( c != '\0' )
		return c;

#ifdef	D_DOS
	if( kbhit() ){
		long	n;

		n = read_char( &c );
		if( n > 0 )
			return c;
		else
			return '\0';
	}
#else	/* D_DOS */
	clr_key_wait();
	read_char( &c );
#endif	/* D_DOS */

	return c;
}

/***************************************************************
* �������Хåե���ʸ�������ޤäƤ��뤫Ĵ�٤�
* return : ���ޤäƤ��뤫?
***************************************************************/

bool_t	chk_key_buf( void )
{
	if( g_key_buf_head < g_key_buf_tail )
		return TRUE;
	else
		return FALSE;
}

/***************************************************************
* �������Хåե����� 1 ʸ���ɤ߽Ф��ʥ���ȥ��롦�������Ѵ�ͭ���
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_buf_char( void )
{
	long	c;

	while( 1 ){
		c = get_key_buf_char_sub();
		if( c == '\0' )
			return c;

		if( c == '\\' ){
			/* �᥿������饯�� */

			c = get_key_buf_char_sub();
			if( c == '\0' )
				return c;

			if( isalpha( c ) ){
				switch( c ){
				case 'n':
					return '\n';
				case 't':
					return '\t';
				}
				continue;
			} else {
				return c;
			}
		} else if( c == '^' ){
			/* ����ȥ��롦������ */

			c = get_key_buf_char_sub();
			if( c == '\0' )
				return c;

			if( isalpha( c ) ){
				return( toupper( c ) - '@' );
			} else {
				continue;
			}
		} else if( c == '&' ){
			const long	max_len = 127;
			static char	buf[127 + 1];
			long	i;

			/* �ե��󥯥���󡦥��� */

			for( i = 0; i < max_len; ){
				c = get_key_buf_char_sub();
				if( c == ';' )
					break;
				if( c == '\0' )
					continue;
				if( c == CMD_KEY_IDLE )
					continue;

				buf[i] = c;
				i++;
			}
			buf[i] = '\0';

			return get_key_n( buf );
		} else {
			/* �̾�ʸ�� */

			return c;
		}
	}

	return c;
}

/***************************************************************
* �������Хåե������ĥ�������ɤ߽Ф�
* const char *p : �������Хåե�
* return : ��ĥ����
***************************************************************/

long	get_key_n( const char *p )
{
	switch( *p ){
	case '\0':
	case '&':
		return '&';
	case 'a':
		return get_key_n_all( ++p );
	case 'f':
		return get_key_n_func( ++p );
	case 'm':
		return get_key_n_mouse( ++p );
	case 'j':
		return get_key_n_joystick( ++p );
	default:
		return '\0';
	}

	return '\0';
}

/***************************************************************
* �������Хåե������ĥ�������ɤ߽Ф�
* const char *p : �������Хåե�
* return : ��ĥ����
***************************************************************/

long	get_key_n_all( const char *p )
{
	long	c;

	c = get_key_n_num( p );

	if( c < KEY_N_0 )
		return '\0';
	if( c > KEY_N_MAX )
		return '\0';

	return c;
}

/***************************************************************
* �������Хåե������ĥ�������ɤ߽Ф��ʥե��󥯥���󡦥�����
* const char *p : �������Хåե�
* return : ��ĥ����
***************************************************************/

long	get_key_n_func( const char *p )
{
	long	n;
	long	c;

	n = get_key_n_num( p );
	c = KEY_N_FUNC( n );

	if( c < KEY_N_FUNC_0 )
		return '\0';
	if( c > KEY_N_FUNC_MAX )
		return '\0';

	return c;
}

/***************************************************************
* �������Хåե������ĥ�������ɤ߽Ф��ʥޥ�����
* const char *p : �������Хåե�
* return : ��ĥ����
***************************************************************/

long	get_key_n_mouse( const char *p )
{
	long	c, bgn, end;
	long	n;

	c = *p++;
	n = get_key_n_num( p );

	bgn = 0;
	end = 0;

	switch( c ){
	case 'c':
		c = KEY_N_MOUSE_CLICK( n );
		bgn = KEY_N_MOUSE_CLICK_0;
		end = KEY_N_MOUSE_CLICK_MAX;
		break;
	case 'd':
		c = KEY_N_MOUSE_D_CLICK( n );
		bgn = KEY_N_MOUSE_D_CLICK_0;
		end = KEY_N_MOUSE_D_CLICK_MAX;
		break;
	case 'b':
		c = KEY_N_MOUSE_P_CLICK( n );
		bgn = KEY_N_MOUSE_P_CLICK_0;
		end = KEY_N_MOUSE_P_CLICK_MAX;
		break;
	case 'p':
		c = KEY_N_MOUSE_PRESS( n );
		bgn = KEY_N_MOUSE_PRESS_0;
		end = KEY_N_MOUSE_PRESS_MAX;
		break;
	case 'r':
		c = KEY_N_MOUSE_RELEASE( n );
		bgn = KEY_N_MOUSE_RELEASE_0;
		end = KEY_N_MOUSE_RELEASE_MAX;
		break;
	case 'm':
		c = KEY_N_MOUSE_MOTION( n );
		bgn = KEY_N_MOUSE_MOTION_0;
		end = KEY_N_MOUSE_MOTION_MAX;
		break;
	default:
		return '\0';
	}

	if( c < bgn )
		return '\0';
	if( c > end )
		return '\0';

	return c;
}

/***************************************************************
* �������Хåե������ĥ�������ɤ߽Ф��ʥ��祤���ƥ��å����ܥ����
* const char *p : �������Хåե�
* return : ��ĥ����
***************************************************************/

long	get_key_n_joystick( const char *p )
{
	long	n;
	long	c;

	n = get_key_n_num( p );
	c = KEY_N_JOYSTICK( n );

	if( c < KEY_N_JOYSTICK_0 )
		return '\0';
	if( c > KEY_N_JOYSTICK_MAX )
		return '\0';

	return c;
}

/***************************************************************
* �������Хåե�������ͤ��ɤ߽Ф�
* const char *p : �������Хåե�
* return : ����
***************************************************************/

long	get_key_n_num( const char *p )
{
	long	c;

	c = *p;
	if( c == '0' ){
		p++;
		c = toupper( *p );
		if( c == 'X' )
			return get_key_n_hex_dec( ++p );
		if( ('0' <= c) && (c <= '7') )
			return get_key_n_oct( p );
	} else if( ('1' <= c) && (c <= '9') ){
		return get_key_n_dec( p );
	}

	return 0;
}

/***************************************************************
* �������Хåե����� 16 �ʿ����ɤ߽Ф�
* const char *p : �������Хåե�
* return : ����
***************************************************************/

long	get_key_n_hex_dec( const char *p )
{
	long	n;
	long	c;

	n = 0;

	while( 1 ) {
		c = toupper( *p++ );

		if( c == '\0' ){
			break;
		} else if( c == ';' ){
			break;
		} else if( isxdigit( c ) ){
			n *= 16;
			if( c <= '9' )
				n += c - '0';
			else
				n += c - 'A' + 10;
		} else {
			break;
		}
	}

	return n;
}

/***************************************************************
* �������Хåե����� 10 �ʿ����ɤ߽Ф�
* const char *p : �������Хåե�
* return : ����
***************************************************************/

long	get_key_n_dec( const char *p )
{
	long	n;
	long	c;

	n = 0;

	while( 1 ) {
		c = toupper( *p++ );

		if( c == '\0' ){
			break;
		} else if( c == ';' ){
			break;
		} else if( isdigit( c ) ){
			n *= 10;
			n += c - '0';
		} else {
			break;
		}
	}

	return n;
}

/***************************************************************
* �������Хåե����� 8 �ʿ����ɤ߽Ф�
* const char *p : �������Хåե�
* return : ����
***************************************************************/

long	get_key_n_oct( const char *p )
{
	long	n;
	long	c;

	n = 0;

	while( 1 ) {
		c = toupper( *p++ );

		if( c == '\0' ){
			break;
		} else if( c == ';' ){
			break;
		} else if( ('0' <= c) && (c <= '9') ){
			n *= 8;
			n += c - '0';
		} else {
			break;
		}
	}

	return n;
}

/***************************************************************
* �������Хåե����� 1 ʸ���ɤ߽Ф�
* return : ���Ϥ��줿ʸ��
***************************************************************/

long	get_key_buf_char_sub( void )
{
	long	c;

	key_buf_lock();

	if( g_key_buf_head >= g_key_buf_tail ){
		key_buf_unlock();
		return '\0';
	}

	c = g_key_buf[g_key_buf_head % KEY_BUF_MAX_LEN];
	g_key_buf_head++;

	key_buf_unlock();
	return c;
}

/***************************************************************
* �������Хåե�����Ƭ��ʸ���򥻥å�
* long c : ���åȤ���ʸ��
* return : ���åȽ��褿��?
***************************************************************/

bool_t	set_key_buf_char_head( long c )
{
	char	s[1 + 1];

	s[0] = c;
	s[1] = '\0';

	return set_key_buf_str_head( s );
}

/***************************************************************
* �������Хåե���������ʸ���򥻥å�
* long c : ���åȤ���ʸ��
* return : ���åȽ��褿��?
***************************************************************/

bool_t	set_key_buf_char_tail( long c )
{
	char	s[1 + 1];

	s[0] = c;
	s[1] = '\0';

	return set_key_buf_str_tail( s );
}

/***************************************************************
* �������Хåե�����Ƭ��ʸ����򥻥å�
* const char *s : ���åȤ���ʸ����
* return : ���åȽ��褿��?
***************************************************************/

bool_t	set_key_buf_str_head( const char *s )
{
	long	len, max_len;
	long	src, dst;
	long	i;

	key_buf_lock();

	len = str_len_std( s );
	max_len = KEY_BUF_MAX_LEN - (g_key_buf_tail - g_key_buf_head);
	if( len > max_len ){
		key_buf_unlock();
		return FALSE;
	}

	for( i = g_key_buf_tail - 1; i >= g_key_buf_head; i-- ){
		src = i % KEY_BUF_MAX_LEN;
		dst = (i + len) % KEY_BUF_MAX_LEN;
		g_key_buf[dst] = g_key_buf[src];
	}
	g_key_buf_tail += len;

	for( i = 0; i < len; i++ ){
		dst = (g_key_buf_head + i) % KEY_BUF_MAX_LEN;
		g_key_buf[dst] = s[i];
	}

	set_flg_break_key( TRUE );

	key_buf_unlock();
	return TRUE;
}

/***************************************************************
* �������Хåե���������ʸ����򥻥å�
* const char *s : ���åȤ���ʸ����
* return : ���åȽ��褿��?
***************************************************************/

bool_t	set_key_buf_str_tail( const char *s )
{
	long	max_len;
	long	i;

	key_buf_lock();

	max_len = KEY_BUF_MAX_LEN - (g_key_buf_tail - g_key_buf_head);
	if( max_len < str_len_std( s ) ){
		key_buf_unlock();
		return FALSE;
	}

	for( i = 0; i < KEY_BUF_MAX_LEN; i++ ){
		if( s[i] == '\0' )
			break;
		if( (g_key_buf_tail - g_key_buf_head) >= KEY_BUF_MAX_LEN ){
			set_flg_break_key( TRUE );

			key_buf_unlock();
			return FALSE;
		}

		g_key_buf[g_key_buf_tail % KEY_BUF_MAX_LEN] = s[i];
		g_key_buf_tail++;
	}

	set_flg_break_key( TRUE );

	key_buf_unlock();
	return TRUE;
}

/***************************************************************
* �������Хåե���������ʸ�����֤�������
* long dst : ����ʸ��
* long src : �֤�������ʸ��
* return : �֤��������褿��?
***************************************************************/

bool_t	cv_key_buf_char_tail( long dst, long src )
{
	long	idx;

	key_buf_lock();

	if( g_key_buf_head >= g_key_buf_tail ){
		key_buf_unlock();
		return FALSE;
	}

	idx = g_key_buf_tail - 1;
	idx = (idx + KEY_BUF_MAX_LEN) % KEY_BUF_MAX_LEN;

	if( g_key_buf[idx] != dst )
		return FALSE;

	g_key_buf[idx] = src;

	key_buf_unlock();
	return TRUE;
}

/***************************************************************
* ����ʸ���󤫤饭�����ơ��֥��ֹ���Ѵ�
* const char *key : ����ʸ����
* return : �������ơ��֥��ֹ�
***************************************************************/

long	get_key_tab_n( const char *key )
{
	unsigned long	c;

	if( key == NULL )
		return '\0';

	c = '\0';
	if( key[0] == '\\' ){
		/* �᥿������饯�� */

		if( key[1] == '\\' ){
			c = '\\';
		} else if( key[1] == '0' ){
			if( key[2] == 'x' ){
				sscanf( &(key[3]), "%lx", &c );
			} else {
				sscanf( &(key[2]), "%lo", &c );
			}
		} else if( key[1] == 'x' ){
			sscanf( &(key[2]), "%lx", &c );
		}
	} else if( key[0] == '^' ){
		/* ����ȥ��롦������ */

		if( isalpha( key[1] ) ){
			c = toupper( key[1] ) - '@';
		}
	} else {
		/* �̾�ʸ�� */

		c = key[0];
	}

	return c;
}

/***************************************************************
* ����ʸ���󤫤饭�������ޥ�ɤ��Ѵ�
* const char *key : ����ʸ����
* return : ���������ޥ��
***************************************************************/

char	*get_key_tab_cmd( const char *key )
{
	if( key == NULL )
		return NULL;

	return get_key_tab_cmd_char( get_key_tab_n( key ) );
}

/***************************************************************
* �������ơ��֥��ֹ椫�饭�������ޥ�ɤ��Ѵ�
* long c : ����ʸ����
* return : ���������ޥ��
***************************************************************/

char	*get_key_tab_cmd_char( long c )
{
	if( c == '\0' )
		return NULL;
	if( c <= 0 )
		return NULL;
	if( c >= KEY_TAB_MAX_N )
		return NULL;

	return( g_key_tab[c] );
}

/***************************************************************
* �������ơ��֥���֤�
* return : �������ơ��֥�
***************************************************************/

char	**get_key_tab( void )
{
	return g_key_tab;
}

/***************************************************************
* �������ơ��֥�˥��������ޥ�ɤ������Ƥ�
* const char *key : ����
* const char *str : ���������ޥ��
***************************************************************/

void	set_key_tab( const char *key, const char *str )
{
	if( key == NULL )
		return;

	set_key_tab_char( get_key_tab_n( key ), str );
}

/***************************************************************
* �����ֹ�ǻ��ꤷ���������ơ��֥�˥��������ޥ�ɤ������Ƥ�
* long c : �����ֹ�
* const char *str : ���������ޥ��
***************************************************************/

void	set_key_tab_char( long c, const char *str )
{
	if( c == '\0' )
		return;
	if( c <= 0 )
		return;
	if( c >= KEY_TAB_MAX_N )
		return;

	/* ���������ޥ�ɤγ�����Ƥ��� */

	if( g_key_tab[c] != NULL ){
		free_mem( g_key_tab[c] );
		g_key_tab[c] = NULL;
	}
	if( str == NULL )
		return;
	else if( str[0] == '\0' )
		return;

	/* ���������ޥ�ɤ������� */

	g_key_tab[c] = (char *)alloc_mem( str_len_std( str ) + 1, FALSE );

	if( g_key_tab[c] != NULL )
		strcpy( g_key_tab[c], str );
}

/***************************************************************
* �ե졼�ࡦ�졼�Ȥ��֤�
* return : �ե졼�ࡦ�졼��
***************************************************************/

long	*get_clk_tck( void )
{
	return &g_clk_tck;
}

/***************************************************************
* ��˥塼�����褵��ơ��ä�ɬ�פ����뤫���֤�
* return : �ä�ɬ�פ����뤫
***************************************************************/

bool_t	get_flg_draw_menu( void )
{
	return flg_draw_menu;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_draw_c( void )
{
	check_memory( check_memory_draw_c_g_stat_mode_n,
		"draw.c: g_stat_mode_n" );
	check_memory( check_memory_draw_c_g_ls_msg,
			"draw.c: g_ls_msg" );
	check_memory( check_memory_draw_c_g_ls_msg_idx,
			"draw.c: g_ls_msg_idx" );
	check_memory( check_memory_draw_c_g_flg_ls_msg,
			"draw.c: g_flg_ls_msg" );
	check_memory( check_memory_draw_c_g_flg_stat_bar_hint_chr,
			"draw.c: g_flg_stat_bar_hint_chr" );
	check_memory( check_memory_draw_c_flg_draw_menu,
			"draw.c: flg_draw_menu" );
	check_memory( check_memory_draw_c_g_cui_mouse_menu_sel_n,
			"draw.c: g_cui_mouse_menu_sel_n" );
	check_memory( check_memory_draw_c_map_draw_pos,
			"draw.c: map_draw_pos" );
	check_memory( check_memory_draw_c_flg_redraw_every_turn,
			"draw.c: flg_redraw_every_turn" );
	check_memory( check_memory_draw_c_vfx_wait,
			"draw.c: vfx_wait" );
	check_memory( check_memory_draw_c_flg_vfx_mbr,
			"draw.c: flg_vfx_mbr" );
	check_memory( check_memory_draw_c_g_vfx_attr,
			"draw.c: g_vfx_attr" );
	check_memory( check_memory_draw_c_g_clk_tck,
			"draw.c: g_clk_tck" );
	check_memory( check_memory_draw_c_g_flg_sync_vfx_num,
			"draw.c: g_flg_sync_vfx_num" );
	check_memory( check_memory_draw_c_g_gui_vfx_pool,
			"draw.c: g_gui_vfx_pool" );
	check_memory( check_memory_draw_c_g_un_get_key_c,
			"draw.c: g_un_get_key_c" );
	check_memory( check_memory_draw_c_g_key_buf_head,
			"draw.c: g_key_buf_head" );
	check_memory( check_memory_draw_c_g_key_buf,
			"draw.c: g_key_buf" );
	check_memory( check_memory_draw_c_g_key_tab,
			"draw.c: g_key_tab" );
	check_memory( check_memory_draw_c_g_flg_break_key,
			"draw.c: g_flg_break_key" );
	check_memory( check_memory_draw_c_g_flg_reg_macro,
			"draw.c: g_flg_reg_macro" );
	check_memory( check_memory_draw_c_g_reg_macro_buf,
			"draw.c: g_reg_macro_buf" );
	check_memory( check_memory_draw_c_g_flg_update_chr,
			"draw.c: g_flg_update_chr" );
	check_memory( check_memory_draw_c_g_cui_mouse_mbr_data_cur_n,
			"draw.c: g_cui_mouse_mbr_data_cur_n" );
	check_memory( check_memory_draw_c_prev_flg,
			"draw.c: prev_flg" );
}
