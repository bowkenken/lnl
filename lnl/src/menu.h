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
* $Id: menu.h,v 1.56 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MENU_H
#define	MENU_H

/* ��˥塼 */

#include	"item.h"
#include	"party.h"
#include	"msg.h"

/***************************************************************/

/**** ����� ****/

#define	STR_MENU_ERR	"# Error"
#define	STR_MENU_CANCEL	".."

/**** ��˥塼����ѤΥ��� ****/

#define	CASE_ENTER	\
		'M' - '@': case 'J' - '@'
#define	CASE_CANCEL	\
		'G' - '@': case 'H' - '@': case '0': case '\033'
#define	CASE_EXEC	\
		'5': case '.'
#define	CASE_EXIT	\
		'Q': case 'Q' - '@': case 'C' - '@'
#define	CASE_SQUARE	\
		'v': case '+'

#define	CASE_CRSR_UP	\
		'8': case 'k': case 'w': case 'P' - '@'
#define	CASE_CRSR_DOWN	\
		'2': case 'j': case 's': case 'N' - '@'
#define	CASE_CRSR_LEFT	\
		'4': case 'h': case 'a': case 'B' - '@'
#define	CASE_CRSR_RIGHT	\
		'6': case 'l': case 'd': case 'F' - '@'
#define	CASE_CRSR_UP_LEFT	\
		'7': case 'y'
#define	CASE_CRSR_UP_RIGHT	\
		'9': case 'u'
#define	CASE_CRSR_DOWN_LEFT	\
		'1': case 'b'
#define	CASE_CRSR_DOWN_RIGHT	\
		'3': case 'n'

/* ���ܤκ���ʸ���� */
#define	MENU_MAX_LEN	(SCREEN_WIDTH - 4)
#define	MENU_MAX_BYTE	(MENU_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* �ڡ���������κ�����ܿ� */
#define	MENU_MAX_N_PER_PAGE	18

/* ����ڡ����� */
#define	MENU_MAX_PAGE	32

/* ������ܿ� */
#define	MENU_MAX_N	(MENU_MAX_N_PER_PAGE * MENU_MAX_PAGE)

/**** �ե饰 ****/

typedef unsigned long	flg_menu_t;

/* ̵�� */
#define	FLG_MENU_DIS	(1 << 0)

/* ��ɽ�� */
#define	FLG_MENU_HIDDEN	(1 << 1)

/* �����å������� */
#define	FLG_MENU_CHK_ON	(1 << 4)

/* �����å������� */
#define	FLG_MENU_CHK_OFF	(1 << 5)

#define	FLG_MENU_ALL	\
	(FLG_MENU_DIS | FLG_MENU_HIDDEN \
	| FLG_MENU_CHK_ON | FLG_MENU_CHK_OFF)

/****  ****/

/* ��˥塼���ѥ��κ���ʸ���� */
#define	MENU_PATH_MAX_LEN	80

/* ���ܤμ���κ���ʸ���� */
#define	MENU_KIND_MAX_LEN	16

/* �ޥ���κ���ʸ���� */
#define	MACRO_MAX_LEN	256

/* ���硼�ȡ����åȡ������κ���ʸ���� */
#define	MENU_SHORT_KEY_MAX_LEN	16

/* ���ܤκ���ʸ���� */
#define	MENU_MSG_MAX_LEN	80
#define	MENU_MSG_MAX_BYTE	(MENU_MSG_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/**** �����֡����� ****/

#define	MENU_SAVE_LOAD_MAX_N	40
#define	MENU_SAVE_LOAD_N_PER_PAGE	10

/**** ����饯���������� ****/

/* ����饯���������Ȥκ���ڡ����� */
#define	MBR_DATA_PAGE_MAX_N	6

/**** �桼������˥塼 ****/

/* �桼������˥塼�κ�����ܿ� */
#define	USER_MENU_MAX_N	(MENU_MAX_N_PER_PAGE * 4)

/**** ���ޥ�ɡ���˥塼 ****/

#define	MENU_COMMAND_KEY_CHAR	':'
#define	MENU_COMMAND_KEY_STR	":"
#define	MENU_COMMAND_MAX_LEN	2048

/**** ��˥塼������Υ����롦�Хå��ؿ� ****/

struct menu_t;
typedef char	*(*menu_call_back_t)(
	struct menu_t **pp, struct menu_t **dflt );

/**** �ޥåפΥ������� ****/

typedef unsigned long	flg_scroll_t;
#define	FLG_SCROLL_SMOOTH	(1 << 0)
#define	FLG_SCROLL_CENTER	(1 << 1)

/***************************************************************/

/* ��˥塼 */

typedef struct menu_t {
	/* �ڹ�¤�Υѥ� */
	char	path[MENU_PATH_MAX_LEN + 1];
	/* ���ܤμ��� */
	char	kind[MENU_KIND_MAX_LEN + 1];

	/* ��������졼�������� */
	unsigned char	accel_key;
	/* ���硼�ȡ����åȡ����� */
	char	short_key[MENU_SHORT_KEY_MAX_LEN + 1];

	/* ����̾ */
	n_msg_t	n_msg;
	char	msg[MENU_MSG_MAX_BYTE + 1];

	/* �����롦�Хå��ؿ� */
	menu_call_back_t	call_back;
	/* �����롦�Хå��ؿ��ؤΰ��� */
	void	*arg;

	/* �ե饰 */
	flg_menu_t	flg;
} menu_t;

typedef struct {
	/* �����ȥ� */
	char	*ttl;

	/* ���Υ�˥塼�Υꥹ�� */
	menu_t	*ls[MENU_MAX_N_PER_PAGE + 1];

	/* ���򤵤�Ƥ�����ܤ��ֹ� */
	long	sel_n, prev_sel_n;

	/* �ڡ����� */
	long	page_sel_n, page_max_n;

	/* ��Ƭ���ǽ��ڡ����Ǥ���Я�Υե饰 */
	bool_t	flg_min_page, flg_max_page;

	/* ������ե饰 */
	bool_t	flg_redraw;
} draw_menu_t;

/* �Ϥ��������� */

typedef enum {
	ASK_NO,
	ASK_YES,
	ASK_CANCEL,
	ASK_ERR,
} ask_t;

/* �������μ��� */

typedef enum {
	DEAL_KIND_BUY,	/* �㤦 */
	DEAL_KIND_SALE_ITEM,	/* �����ƥ����� */
	DEAL_KIND_SALE_EQUIP,	/* ��������� */
} deal_kind_t;

/* �������� */

typedef enum {
	MENU_NUM_MIN,
	MENU_NUM_MAX,
	MENU_NUM_CLR,
	MENU_NUM_OK,
	MENU_NUM_MAX_N
} menu_num_t;

/* �������ϥ��� */

#define	KEY_MENU_NUM_OK	'Z'
#define	KEY_MENU_NUM_CLR	'Y'
#define	KEY_MENU_NUM_MAX	'X'
#define	KEY_MENU_NUM_MIN	'W'
#define	KEY_MENU_NUM_SGN	'V'

/* ���֥����������� */

typedef enum {
	NEXT_POS_KIND_SQUARE,
	NEXT_POS_KIND_MBR,
	NEXT_POS_KIND_MNSTR,
	NEXT_POS_KIND_DOOR,
	NEXT_POS_KIND_OBJ,
} next_pos_kind_t;

typedef struct {
	next_pos_kind_t	kind;
	void	*p;
	long	n;
	int	x, y;
} next_pos_t;

/* ���С����ǡ������Խ��⡼�� */

typedef enum {
	MBR_DATA_EDIT_KIND_SHOW,	/* ɽ���Τ� */
	MBR_DATA_EDIT_KIND_EDIT,	/* �Խ� */
	MBR_DATA_EDIT_KIND_NEW,	/* ���� */
	MBR_DATA_EDIT_KIND_MAX_N,
} mbr_data_edit_kind_t;

#endif	/* MENU_H */
