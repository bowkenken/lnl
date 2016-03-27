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
* $Id: gmain.h,v 1.79 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	GMAIN_H
#define	GMAIN_H

/***************************************************************
* �ᥤ�����
***************************************************************/

#if	defined( D_GTK )
/**/
#elif	defined( D_IPHONE )
# include	"config-iphone.h"
#elif	defined( D_WS )
# include	"config-win.h"
#elif	defined( D_MFC )
# include	"config-dows.h"
#elif	defined( D_DOS )
# include	"lnl-dos/config-dos.h"
#endif

#ifdef	HAVE_CONFIG_H
# include	"config.h"
#endif	/* HAVE_CONFIG_H */

#ifdef	HAVE_STDLIB_H
# include	<stdlib.h>
#endif	/* HAVE_STDLIB_H */

#ifdef	HAVE_STDDEF_H
# include	<stddef.h>
#endif	/* HAVE_STDDEF_H */

#ifdef	HAVE_STDIO_H
# include	<stdio.h>
#endif	/* HAVE_STDIO_H */

#ifdef	HAVE_STDARG_H
# include	<stdarg.h>
#endif	/* HAVE_STDARG_H */

#ifdef	HAVE_LIMITS_H
# include	<limits.h>
#endif	/* HAVE_LIMITS_H */

#ifdef	HAVE_STRING_H
# include	<string.h>
#endif	/* HAVE_STRING_H */

#ifdef	HAVE_STRINGS_H
# include	<strings.h>
#endif	/* HAVE_STRING_H */

#ifdef	HAVE_CTYPE_H
# include	<ctype.h>
#endif	/* HAVE_CTYPE_H */

#ifdef	HAVE_TIME_H
# include	<time.h>
#endif	/* HAVE_TIME_H */

#ifdef	HAVE_MATH_H
# include	<math.h>
#endif	/* HAVE_MATH_H */

#ifdef	HAVE_DIRECT_H
# include <direct.h>
#endif	/* HAVE_DIRECT_H */

#ifdef	HAVE_SYS_STAT_H
# include	<sys/stat.h>
#endif	/* HAVE_SYS_STAT_H */

#ifdef	HAVE_UNISTD_H
# include	<unistd.h>
#endif	/* HAVE_UNISTD_H */

#ifdef	HAVE_GPM_H
# include	<gpm.h>
#endif	/* HAVE_GPM_H */

#ifndef	EXIT_SUCCESS
# define	EXIT_SUCCESS	0
#endif	/* EXIT_SUCCESS */

#ifndef	EXIT_FAILURE
# define	EXIT_FAILURE	1
#endif	/* EXIT_FAILURE */

/***************************************************************/

#if	defined( D_WS ) \
	|| defined( D_GTK ) \
	|| defined( D_IPHONE ) \
	|| defined( D_MFC )
# define	D_ALL_GUI	1
#endif

/***************************************************************/

#include	"misc.h"
#include	"turn.h"
#include	"msg-t.h"

#include	"music-kind.h"
#include	"sound-kind.h"

/***************************************************************
* �����
***************************************************************/

/* �������Ϥ�ɤ������ɤफ? */

typedef enum {
	GUI_KEY_KIND_CONSOLE,
	GUI_KEY_KIND_CLASS_KEY,
	GUI_KEY_KIND_KEY_BUF_INTERRUPT,
	GUI_KEY_KIND_MAX_N,
} gui_key_kind_t;

/* ���꡼�������å� */

#define	CHECK_MEMORY_MAX_LEN	32
#define	CHECK_MEMORY_INIT	{ \
	0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, \
	0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, \
	0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, \
	0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, 0xbe, 0xef, \
}

typedef unsigned char	check_memory_t[CHECK_MEMORY_MAX_LEN];

#define	check_memory_def( var )	\
	static check_memory_t	var = CHECK_MEMORY_INIT;

/***************************************************************
* �ѿ����
***************************************************************/

#include	"extern.h"

#ifdef __cplusplus
extern "C" {
#endif

/* CUI �����⥸�塼�뤬������Ѥߤ�? */
EXTERN bool_t	g_flg_init;

/* CUI �⡼�� */
EXTERN bool_t	g_flg_cui;

/* GUI �⡼�� */
EXTERN bool_t	g_flg_gui;

/* CUI �ޥ������⡼�� */
EXTERN bool_t	g_flg_cui_mouse;

/* CUI �ޥ������⡼�ɻ��˱�����Υܥ���������ؤ��뤫? */
EXTERN bool_t	g_flg_cui_mouse_swap_btn;

/* �����ΥХåե�����������������򥪥ץ����ǻ��ꤵ�줿��? */
EXTERN long	g_audio_buf_siz_arg_overwrite;

/* �����ΥХåե�����������������򥪥ץ����ǻ��� */
EXTERN long	g_audio_buf_siz_arg;

/* �����ΥХåե����������������� */
EXTERN long g_audio_buf_siz;

/* ������ɥ���ɸ������򥪥ץ����ǻ��ꤵ�줿��? */
EXTERN bool_t	g_flg_win_pos_arg_overwrite;

/* ������ɥ����ޥ͡����㤬 GNOME ���򥪥ץ����ǻ��� */
EXTERN bool_t	g_flg_gnome_arg;

/* ������ɥ����ޥ͡����㤬 GNOME ��? */
EXTERN bool_t	g_flg_gnome;

/* ������ɥ���ɽ��������˰��֤����ꤹ�뤫�򥪥ץ����ǻ��� */
EXTERN bool_t	g_flg_set_win_pos_arg;

/* ������ɥ���ɽ��������˰��֤����ꤹ�뤫? */
EXTERN bool_t	g_flg_set_win_pos;

/* GUI �Υƥ�����ɽ���⡼�� */
EXTERN bool_t	g_flg_text_mode;

/* GUI �Υƥ�����ɽ���⡼�ɤΥե���ȡ������� */
EXTERN long	g_text_mode_point;

/* ����ե��å����̤γ���Ψ */
EXTERN rate_t	g_graph_scale_rate;

/* �������Ϥ�ɤ������ɤफ? */
EXTERN gui_key_kind_t	g_gui_key_kind;

/* ��å������θ��� */
EXTERN char	*g_language;

/* �������Хåե��Υ��ꥢ�򥪥ץ����ǻ��ꤵ�줿��? */
EXTERN bool_t	g_flg_clr_key_buf_arg_overwrite;

/* �������Хåե��Υ��ꥢ�򥪥ץ����ǻ��� */
EXTERN bool_t	g_flg_clr_key_buf_arg;

/* �������Хåե��򥯥ꥢ���� */
EXTERN bool_t	g_flg_clr_key_buf;

/* �������Хåե��򥯥ꥢ����ʥ�˥塼������� */
EXTERN bool_t	g_flg_clr_key_buf_menu;

/* ���Ϥ��줿������ɽ�� */
EXTERN bool_t	g_flg_echo_key;

/* ���̤������ curses �饤�֥�����Ѥ��� */
EXTERN bool_t	g_flg_use_curs;

/* �������롦����������Ѥ��� */
EXTERN bool_t	g_flg_use_keypad;

/* �ե졼�ࡦ�졼�Ȥ��¬���� */
EXTERN bool_t	g_flg_measure_clk_tck;

/* �����֡����ɻ�������μ� */
EXTERN long	g_randm_seed_save;

/* �����ƥ�μ����Ϥ��λ����������񤹤� */
EXTERN bool_t	g_flg_send_item_exec_turn;

/* ���åȡ�����Υǥ�򥹥��åפ��뤫? */
EXTERN bool_t	g_flg_skip_demo_cut_in;

/* ���ο� CUI */
EXTERN long	g_cui_star_n;

/* ���ο� GUI */
EXTERN long	g_gui_star_n;

/* �ǥХå����⡼�� */
EXTERN bool_t	g_flg_debug;

/* ���꡼�������å� */
EXTERN bool_t	g_flg_check_memory;

#ifdef __cplusplus
}
#endif

#endif	/* GMAIN_H */
