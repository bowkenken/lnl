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
* $Id: dun.h,v 1.56 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	DUN_H
#define	DUN_H

/***************************************************************
* �µ�
***************************************************************/

#include	"gmain.h"
#include	"curs.h"

/***************************************************************
* ���糬��
***************************************************************/

/* �Ͼ�κ��糬�� */
#define	DUN_MAX_LEV_FLOOR	10000
/* �ϲ��κ��糬�� */
#define	DUN_MAX_LEV_BASE	10000

/* �ƥ��ơ����γ��ؿ� (��ܥ������Ū�˽и����볬�ؿ�) */
#define	DUN_LEV_BOSS	10
/* �����ơ����� */
#define	STAGE_MAX_N	10
/* ���ơ������롼�פ��볬�� */
#define	DUN_LEV_LOOP	(DUN_LEV_BOSS * STAGE_MAX_N)

/* �饹�ܥ��γ��� */
#define	DUN_LEV_LAST_BOSS	-99999
/* �饹�ܥ��ؤγ��ʤ��и����볬�� */
#define	DUN_LEV_LAST_BOSS_STAIRS	DUN_LEV_LOOP

/***************************************************************
* �ޥåפι���
***************************************************************/

#define	AREA_MAX_X	20
#define	AREA_MAX_Y	20
#define	AREA_MAP_MAX_X	4
#define	AREA_MAP_MAX_Y	4
#define	MAP_MAX_X	(AREA_MAX_X * AREA_MAP_MAX_X)
#define	MAP_MAX_Y	(AREA_MAX_Y * AREA_MAP_MAX_Y)
#define	MAP_DEL_X	-1
#define	MAP_DEL_Y	-1

/***************************************************************
* �ǥե���ȤΥ��������
***************************************************************/

#define	SECT_NULL	'a'
#define	SECT_PATH_DFLT	' '
#define	SECT_PATH_H	'H'
#define	SECT_PATH_V	'V'
#define	SECT_PATH_N	'N'
#define	SECT_PATH_S	'S'
#define	SECT_PATH_E	'E'
#define	SECT_PATH_W	'W'

/***************************************************************
* �ե饰
***************************************************************/

typedef unsigned long	flg_map_t;

/* ���֥������ȤΥե饰 */

#define	FLG_MAP_OBJ_FIND	(1 << 0)	/* ȯ���� */
#define	FLG_MAP_OBJ_PASS	(1 << 1)	/* �̹Բ� */
#define	FLG_MAP_OBJ_LOOK	(1 << 2)	/* �������̤� */
#define	FLG_MAP_OBJ_LOOK_FLOOR	(1 << 4)	/* ���˸����� */
#define	FLG_MAP_OBJ_LOOK_WALL	(1 << 5)	/* �ɤ˸����� */

/* ����饯���Υե饰 */

#define	FLG_MAP_CHR_FIND	(1 << 0)	/* ȯ���� */
#define	FLG_MAP_CHR_INVISIBLE	(1 << 1)	/* Ʃ�� */
#define	FLG_MAP_CHR_NPC	(1 << 2)	/* NPC */

/* �ɥ��Υե饰 */

#define	FLG_DOOR_OPEN	(1 << 0)	/* �����Ƥ��� */
#define	FLG_DOOR_JAMMED	(1 << 1)	/* ���ꤵ��Ƥ��� */
#define	FLG_DOOR_BROKEN	(1 << 2)	/* ����Ƥ��� */
#define	FLG_DOOR_SECRET	(1 << 3)	/* ����Ƥ��� */
#define	FLG_DOOR_CHKED	(1 << 4)	/* Ĵ�ٺ� */
#define	FLG_DOOR_GATE	(1 << 8)	/* ������ */
#define	FLG_DOOR_SHOP	(1 << 9)	/* Ź�ν����� */

/***************************************************************
* ��ʸ��
***************************************************************/

#define	FACE_MJR_WALL	'#'
#define	FACE_MNR_WALL	'#'
#define	FACE_MNR_STATUE	'@'
#define	FACE_MNR_STREETLAMP	'*'
#define	FACE_MNR_BOOT_UNIT	'&'

#define	FACE_MJR_FLOOR	'.'
#define	FACE_MNR_FLOOR	' '
#define	FACE_MNR_HOLE	'^'

#define	FACE_MJR_WATER	'~'
#define	FACE_MNR_PUDDLE	'.'
#define	FACE_MNR_SHALLOWS	' '
#define	FACE_MNR_OFFING	'~'
#define	FACE_MNR_LAVA	'^'

#define	FACE_MJR_MOUNTAIN	'/'
#define	FACE_MNR_MOUNTAIN	'\\'
#define	FACE_MNR_HILL	')'

#define	FACE_MJR_ITEM	'$'

#define	FACE_MJR_DOOR_CLOSE	'+'
#define	FACE_MJR_DOOR_OPEN	'\''
#define	FACE_MNR_DOOR_NORM	' '
#define	FACE_MNR_DOOR_JAMMED	'^'
#define	FACE_MNR_DOOR_BROKEN	'*'
#define	FACE_MNR_DOOR_SECRET	'#'
#define	FACE_MNR_GATE	'+'
#define	FACE_MNR_SHOP_INN	'i'
#define	FACE_MNR_SHOP_BAR	'b'
#define	FACE_MNR_SHOP_WPN	'w'
#define	FACE_MNR_SHOP_ARMOR	'a'
#define	FACE_MNR_SHOP_MAGIC	'm'
#define	FACE_MNR_SHOP_TEMPLE	't'
#define	FACE_MNR_SHOP_ALCHEMY	'l'
#define	FACE_MNR_SHOP_MUSIC	'u'
#define	FACE_MNR_SHOP_GROCERY	'g'
#define	FACE_MNR_SHOP_RESTAURANT	'r'
#define	FACE_MNR_SHOP_TEAROOM	'c'
#define	FACE_MNR_SHOP_TOBACCO	's'
#define	FACE_MNR_SHOP_PET_SHOP	'p'
#define	FACE_MNR_WINDOW	'-'

#define	FACE_MJR_STAIRS_UP	'<'
#define	FACE_MNR_STAIRS_UP	'u'
#define	FACE_MJR_STAIRS_DOWN	'>'
#define	FACE_MNR_STAIRS_DOWN	'd'
#define	FACE_MJR_STAIRS_LAST_BOSS	'>'
#define	FACE_MNR_STAIRS_LAST_BOSS	'X'

#define	FACE_MJR_TRAP	'^'
#define	FACE_MNR_TRAP_SLEEP	's'
#define	FACE_MNR_TRAP_ARW	'a'
#define	FACE_MNR_TRAP_POISON_DARTS	'd'
#define	FACE_MNR_TRAP_BOMB	'b'
#define	FACE_MNR_TRAP_TELEPORT_PARTY	'l'
#define	FACE_MNR_TRAP_TELEPORT	't'
#define	FACE_MNR_TRAP_PIT	'p'
#define	FACE_MNR_TRAP_CHUTE	'c'
#define	FACE_MNR_TRAP_SANCTUARY	'+'

#define	FACE_MJR_MBR	'@'

#define	FACE_MJR_SQUARE	'%'

/***************************************************************
* ����¾
***************************************************************/

/* �ɥ��κ���� */

#define	DOOR_MAX_N	256

/* �������롦�ѥ����� */

#define	CRSR_PTN_MAX_N	8
#define	CRSR_PTN_MAX_Y_LEN	16
#define	CRSR_PTN_MAX_X_LEN	16

/***************************************************************
* ���������
***************************************************************/

typedef char	sect_t;

/***************************************************************
* �����Υѥ�����
***************************************************************/

typedef struct {
	/* ���� */
	long	min_lev, max_lev, sgn_lev;
	/* �и�Ψ */
	rate_t	rate;
	/* �ѥ����� */
	char	ptn[AREA_MAX_Y][AREA_MAX_X * 2 + 1];
	/* ��������� */
	sect_t	sect[AREA_MAX_Y][AREA_MAX_X + 1];
} room_ptn_t;

/***************************************************************
* �ɥ�
***************************************************************/

typedef unsigned long	flg_door_t;

typedef struct {
	long	n;	/* �ɥ��ֹ� */
	long	x, y;	/* ���� */
	long	dx, dy;	/* ������ */
	char	mjr, mnr;	/* �� */
	flg_door_t	flg;	/* �ե饰 */
} door_t;

/***************************************************************
* �ޥåפΥ쥤�䡼
***************************************************************/

typedef struct {
	char	mjr[MAP_MAX_Y][MAP_MAX_X];	/* major face */
	char	mnr[MAP_MAX_Y][MAP_MAX_X];	/* minor face */
	flg_map_t	flg[MAP_MAX_Y][MAP_MAX_X];
} map_t;

/***************************************************************
* �ޥå�
***************************************************************/

struct chr_t;
struct gui_vfx_t;

typedef struct {
	/* ���֥������ȤΥ쥤�䡼 */
	map_t	obj;
	/* ����饯���Υ쥤�䡼 */
	map_t	chr;
	/* ���쥤�䡼 */
	map_t	total;
	/* VFX �Υ쥤�䡼 */
	char	vfx[MAP_MAX_Y][MAP_MAX_X * 2];
	/* GUI VFX �Υ쥤�䡼 */
	struct gui_vfx_t	*gui_vfx[MAP_MAX_Y][MAP_MAX_X];

	/* ��������� */
	sect_t	sect[MAP_MAX_Y][MAP_MAX_X];

	/* �����������٥� */
	long	light_depth_obj[MAP_MAX_Y][MAP_MAX_X];
	/* ����饯���ˤ���������٥� */
	long	light_depth_chr[MAP_MAX_Y][MAP_MAX_X];

	/* ����饯���ؤΥݥ��� */
	struct chr_t	*chr_p[MAP_MAX_Y][MAP_MAX_X];

	/* ɽ����°�� */
	curs_attr_t	attr[MAP_MAX_Y][MAP_MAX_X];
	/* VFX��°�� */
	curs_attr_t	attr_vfx[MAP_MAX_Y][MAP_MAX_X * 2];
} all_map_t;

/***************************************************************
* ���ꥢ
***************************************************************/

typedef short	area_t;

/***************************************************************
* �µ�
***************************************************************/

typedef struct {
	/* �ޥå� */
	all_map_t	map;
	/* ���ꥢ */
	area_t	area[AREA_MAP_MAX_Y][AREA_MAP_MAX_X];

	/* �ɥ� */
	door_t	door[DOOR_MAX_N];
	/* �ɥ��ο� */
	long	door_n;

	/* ���ߤγ��� */
	long	lev;
} dun_t;

/***************************************************************
* �������롦�ѥ�����
***************************************************************/

typedef struct {
	/* ���� */
	long	x, y;
	/* ���ȹ⤵ */
	long	x_len, y_len;

	/* Ʃ��ʸ�� */
	long	transmit_chr;

	/* �ѥ����� */
	char	face[CRSR_PTN_MAX_Y_LEN][CRSR_PTN_MAX_X_LEN * 2 + 1];
} crsr_ptn_t;

#endif	/* DUN_H */
