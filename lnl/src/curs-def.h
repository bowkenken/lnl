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
* $Id: curs-def.h,v 1.12 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	CURS_DEF_H
#define	CURS_DEF_H

/* curses のヘッダが無い時に include する */

#define NCURSES_ATTR_SHIFT       8
#define NCURSES_BITS(mask,shift) ((mask) << ((shift) + NCURSES_ATTR_SHIFT))

#define A_NORMAL	0L
#define A_ATTRIBUTES	NCURSES_BITS(~(1UL - 1UL),0)
#define A_CHARTEXT	(NCURSES_BITS(1UL,0) - 1UL)
#define A_COLOR		NCURSES_BITS(((1UL) << 8) - 1UL,0)
#define A_STANDOUT	NCURSES_BITS(1UL,8)
#define A_UNDERLINE	NCURSES_BITS(1UL,9)
#define A_REVERSE	NCURSES_BITS(1UL,10)
#define A_BLINK		NCURSES_BITS(1UL,11)
#define A_DIM		NCURSES_BITS(1UL,12)
#define A_BOLD		NCURSES_BITS(1UL,13)
#define A_ALTCHARSET	NCURSES_BITS(1UL,14)
#define A_INVIS		NCURSES_BITS(1UL,15)
#define A_PROTECT	NCURSES_BITS(1UL,16)
#define A_HORIZONTAL	NCURSES_BITS(1UL,17)
#define A_LEFT		NCURSES_BITS(1UL,18)
#define A_LOW		NCURSES_BITS(1UL,19)
#define A_RIGHT		NCURSES_BITS(1UL,20)
#define A_TOP		NCURSES_BITS(1UL,21)
#define A_VERTICAL	NCURSES_BITS(1UL,22)

#define COLOR_PAIR(n)	NCURSES_BITS(n, 0)
#define PAIR_NUMBER(a)	((int)(((a) & A_COLOR) >> NCURSES_ATTR_SHIFT))

#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7

/**/

#define KEY_CODE_YES	0400		/* A wchar_t contains a key code */
#define KEY_MIN		0401		/* Minimum curses key */
#define KEY_BREAK	0401		/* Break key (unreliable) */
#define KEY_SRESET	0530		/* Soft (partial) reset (unreliable) */
#define KEY_RESET	0531		/* Reset or hard reset (unreliable) */
#define KEY_DOWN	0402		/* down-arrow key */
#define KEY_UP		0403		/* up-arrow key */
#define KEY_LEFT	0404		/* left-arrow key */
#define KEY_RIGHT	0405		/* right-arrow key */
#define KEY_HOME	0406		/* home key */
#define KEY_BACKSPACE	0407		/* backspace key */
#define KEY_F0		0410		/* Function keys.  Space for 64 */
#define KEY_F(n)	(KEY_F0+(n))	/* Value of function key n */
#define KEY_DL		0510		/* delete-line key */
#define KEY_IL		0511		/* insert-line key */
#define KEY_DC		0512		/* delete-character key */
#define KEY_IC		0513		/* insert-character key */
#define KEY_EIC		0514
	/* sent by rmir or smir in insert mode */
#define KEY_CLEAR	0515		/* clear-screen or erase key */
#define KEY_EOS		0516		/* clear-to-end-of-screen key */
#define KEY_EOL		0517		/* clear-to-end-of-line key */
#define KEY_SF		0520		/* scroll-forward key */
#define KEY_SR		0521		/* scroll-backward key */
#define KEY_NPAGE	0522		/* next-page key */
#define KEY_PPAGE	0523		/* previous-page key */
#define KEY_STAB	0524		/* set-tab key */
#define KEY_CTAB	0525		/* clear-tab key */
#define KEY_CATAB	0526		/* clear-all-tabs key */
#define KEY_ENTER	0527		/* enter/send key */
#define KEY_PRINT	0532		/* print key */
#define KEY_LL		0533		/* lower-left key (home down) */
#define KEY_A1		0534		/* upper left of keypad */
#define KEY_A3		0535		/* upper right of keypad */
#define KEY_B2		0536		/* center of keypad */
#define KEY_C1		0537		/* lower left of keypad */
#define KEY_C3		0540		/* lower right of keypad */
#define KEY_BTAB	0541		/* back-tab key */
#define KEY_BEG		0542		/* begin key */
#define KEY_CANCEL	0543		/* cancel key */
#define KEY_CLOSE	0544		/* close key */
#define KEY_COMMAND	0545		/* command key */
#define KEY_COPY	0546		/* copy key */
#define KEY_CREATE	0547		/* create key */
#define KEY_END		0550		/* end key */
#define KEY_EXIT	0551		/* exit key */
#define KEY_FIND	0552		/* find key */
#define KEY_HELP	0553		/* help key */
#define KEY_MARK	0554		/* mark key */
#define KEY_MESSAGE	0555		/* message key */
#define KEY_MOVE	0556		/* move key */
#define KEY_NEXT	0557		/* next key */
#define KEY_OPEN	0560		/* open key */
#define KEY_OPTIONS	0561		/* options key */
#define KEY_PREVIOUS	0562		/* previous key */
#define KEY_REDO	0563		/* redo key */
#define KEY_REFERENCE	0564		/* reference key */
#define KEY_REFRESH	0565		/* refresh key */
#define KEY_REPLACE	0566		/* replace key */
#define KEY_RESTART	0567		/* restart key */
#define KEY_RESUME	0570		/* resume key */
#define KEY_SAVE	0571		/* save key */
#define KEY_SBEG	0572		/* shifted begin key */
#define KEY_SCANCEL	0573		/* shifted cancel key */
#define KEY_SCOMMAND	0574		/* shifted command key */
#define KEY_SCOPY	0575		/* shifted copy key */
#define KEY_SCREATE	0576		/* shifted create key */
#define KEY_SDC		0577		/* shifted delete-character key */
#define KEY_SDL		0600		/* shifted delete-line key */
#define KEY_SELECT	0601		/* select key */
#define KEY_SEND	0602		/* shifted end key */
#define KEY_SEOL	0603		/* shifted clear-to-end-of-line key */
#define KEY_SEXIT	0604		/* shifted exit key */
#define KEY_SFIND	0605		/* shifted find key */
#define KEY_SHELP	0606		/* shifted help key */
#define KEY_SHOME	0607		/* shifted home key */
#define KEY_SIC		0610		/* shifted insert-character key */
#define KEY_SLEFT	0611		/* shifted left-arrow key */
#define KEY_SMESSAGE	0612		/* shifted message key */
#define KEY_SMOVE	0613		/* shifted move key */
#define KEY_SNEXT	0614		/* shifted next key */
#define KEY_SOPTIONS	0615		/* shifted options key */
#define KEY_SPREVIOUS	0616		/* shifted previous key */
#define KEY_SPRINT	0617		/* shifted print key */
#define KEY_SREDO	0620		/* shifted redo key */
#define KEY_SREPLACE	0621		/* shifted replace key */
#define KEY_SRIGHT	0622		/* shifted right-arrow key */
#define KEY_SRSUME	0623		/* shifted resume key */
#define KEY_SSAVE	0624		/* shifted save key */
#define KEY_SSUSPEND	0625		/* shifted suspend key */
#define KEY_SUNDO	0626		/* shifted undo key */
#define KEY_SUSPEND	0627		/* suspend key */
#define KEY_UNDO	0630		/* undo key */
#define KEY_MOUSE	0631		/* Mouse event has occurred */
#define KEY_RESIZE	0632		/* Terminal resize event */

#ifndef	D_DOS
#define KEY_EVENT	0633		/* We were interrupted by an event */
#endif

#define KEY_MAX		0777		/* Maximum key value is 0633 */

/**/

#if	(! HAVE_NCURSES_H) && (! HAVE_CURSES_H)
typedef struct {
	int	n;
} WINDOW;
#endif	/* (! HAVE_NCURSES_H) && (! HAVE_CURSES_H) */

EXTERN WINDOW	*stdscr;

#endif	/* CURS_DEF_H */
