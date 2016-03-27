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
* $Id: curs.h,v 1.47 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	CURS_H
#define	CURS_H

/***************************************************************
* curses のラッパー
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
* キー
***************************************************************/

/* 端末のサイズ変更イベント */

#ifndef	KEY_RESIZE
# define KEY_RESIZE	0632		/* Terminal resize event */
#endif	/* KEY_RESIZE */

/***************************************************************
* 描画の属性
***************************************************************/

/* 列び順を変たら g_curs_attr も修整すること */

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
* 画面サイズ
***************************************************************/

#define	SCREEN_SIZE_MIN_COL	(2 + 1 + 1)
#define	SCREEN_SIZE_MAX_COL	(1024 * 2)
#define	SCREEN_SIZE_MIN_ROW	(1 + 1 + 1)
#define	SCREEN_SIZE_MAX_ROW	1024

#endif	/* CURS_H */
