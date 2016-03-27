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
* $Id: curs.h,v 1.47 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	CURS_H
#define	CURS_H

/***************************************************************
* curses �Υ�åѡ�
***************************************************************/

#include	"extern.h"
#include	"msg.h"

#if	defined( HAVE_NCURSESW_H )
# include	<ncursesw.h>
# ifndef	COLOR_WHITE
#  include	"curs-def.h"
# endif
#elif	defined( HAVE_NCURSES_H )
# include	<ncurses.h>
# ifndef	COLOR_WHITE
#  include	"curs-def.h"
# endif
#elif	defined( HAVE_CURSES_H )
# include	<curses.h>
# ifndef	COLOR_WHITE
#  include	"curs-def.h"
# endif
#else
# include	"curs-def.h"
#endif

/***************************************************************
* ����
***************************************************************/

/* ü���Υ������ѹ����٥�� */

#ifndef	KEY_RESIZE
# define KEY_RESIZE	0632		/* Terminal resize event */
#endif	/* KEY_RESIZE */

/***************************************************************
* �����°��
***************************************************************/

/* ��ӽ���Ѥ��� g_curs_attr �⽤�����뤳�� */

typedef enum {
	CURS_ATTR_N_NORMAL,
	CURS_ATTR_N_REV,
	CURS_ATTR_N_ERR,

	CURS_ATTR_N_MENU_NORMAL,
	CURS_ATTR_N_MENU_DIS,
	CURS_ATTR_N_MENU_SEL,

	CURS_ATTR_N_MAP_CRSR,
	CURS_ATTR_N_MAP_SQUARE,
	CURS_ATTR_N_MAP_WALL,
	CURS_ATTR_N_MAP_FLOOR,
	CURS_ATTR_N_MAP_DOOR,
	CURS_ATTR_N_MAP_STAIRS,
	CURS_ATTR_N_MAP_TRAP,
	CURS_ATTR_N_MAP_MNSTR,
	CURS_ATTR_N_MAP_NPC,
	CURS_ATTR_N_MAP_PET,

	CURS_ATTR_N_MAP_ITEM,
	CURS_ATTR_N_MAP_ITEM_WPN,
	CURS_ATTR_N_MAP_ITEM_ARMOR,
	CURS_ATTR_N_MAP_ITEM_POTION,
	CURS_ATTR_N_MAP_ITEM_SCROLL,
	CURS_ATTR_N_MAP_ITEM_STICK,
	CURS_ATTR_N_MAP_ITEM_ACCE,
	CURS_ATTR_N_MAP_ITEM_INST,
	CURS_ATTR_N_MAP_ITEM_LIGHT,
	CURS_ATTR_N_MAP_ITEM_SPIKE,
	CURS_ATTR_N_MAP_ITEM_FOOD,
	CURS_ATTR_N_MAP_ITEM_CHEST,
	CURS_ATTR_N_MAP_ITEM_RARE_GOODS,
	CURS_ATTR_N_MAP_ITEM_BONE,
	CURS_ATTR_N_MAP_ITEM_COIN,
	CURS_ATTR_N_MAP_ITEM_JUNK,

	CURS_ATTR_N_MBR_1,
	CURS_ATTR_N_MBR_2,
	CURS_ATTR_N_MBR_3,
	CURS_ATTR_N_MBR_4,
	CURS_ATTR_N_MBR_5,
	CURS_ATTR_N_MBR_6,

	CURS_ATTR_N_FX_MBR_PLUS,
	CURS_ATTR_N_FX_MBR_MINUS,
	CURS_ATTR_N_FX_MBR_CRTCL,
	CURS_ATTR_N_FX_MNSTR_PLUS,
	CURS_ATTR_N_FX_MNSTR_MINUS,
	CURS_ATTR_N_FX_MNSTR_CRTCL,
	CURS_ATTR_N_VFX,

	CURS_ATTR_N_HEAT,
	CURS_ATTR_N_COLD,
	CURS_ATTR_N_MIND,
	CURS_ATTR_N_ACID,

	CURS_ATTR_N_MAX_N,

	CURS_ATTR_N_MAP_NORMAL = CURS_ATTR_N_NORMAL,
} curs_attr_n_t;

typedef unsigned long	chtype_t;

typedef struct {
	short	color_pair_n;
	n_msg_t	name_n;
	int	fg, bg;
	chtype_t	attr;
} curs_attr_t;

/***************************************************************
* ���̥�����
***************************************************************/

#define	SCREEN_SIZE_MIN_COL	(2 + 1 + 1)
#define	SCREEN_SIZE_MAX_COL	(1024 * 2)
#define	SCREEN_SIZE_MIN_ROW	(1 + 1 + 1)
#define	SCREEN_SIZE_MAX_ROW	1024

#endif	/* CURS_H */
