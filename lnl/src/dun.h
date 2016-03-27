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
* $Id: dun.h,v 1.56 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	DUN_H
#define	DUN_H

/***************************************************************
* 迷宮
***************************************************************/

#include	"gmain.h"
#include	"curs.h"

/***************************************************************
* 最大階数
***************************************************************/

/* 地上の最大階数 */
#define	DUN_MAX_LEV_FLOOR	10000
/* 地下の最大階数 */
#define	DUN_MAX_LEV_BASE	10000

/* 各ステージの階層数 (中ボスが定期的に出現する階層数) */
#define	DUN_LEV_BOSS	10
/* 全ステージ数 */
#define	STAGE_MAX_N	10
/* ステージがループする階数 */
#define	DUN_LEV_LOOP	(DUN_LEV_BOSS * STAGE_MAX_N)

/* ラスボスの階層 */
#define	DUN_LEV_LAST_BOSS	-99999
/* ラスボスへの階段が出現する階層 */
#define	DUN_LEV_LAST_BOSS_STAIRS	DUN_LEV_LOOP

/***************************************************************
* マップの広さ
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
* デフォルトのセクション
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
* フラグ
***************************************************************/

typedef unsigned long	flg_map_t;

/* オブジェクトのフラグ */

#define	FLG_MAP_OBJ_FIND	(1 << 0)	/* 発見済 */
#define	FLG_MAP_OBJ_PASS	(1 << 1)	/* 通行可 */
#define	FLG_MAP_OBJ_LOOK	(1 << 2)	/* 視線が通る */
#define	FLG_MAP_OBJ_LOOK_FLOOR	(1 << 4)	/* 床に見える */
#define	FLG_MAP_OBJ_LOOK_WALL	(1 << 5)	/* 壁に見える */

/* キャラクタのフラグ */

#define	FLG_MAP_CHR_FIND	(1 << 0)	/* 発見済 */
#define	FLG_MAP_CHR_INVISIBLE	(1 << 1)	/* 透明 */
#define	FLG_MAP_CHR_NPC	(1 << 2)	/* NPC */

/* ドアのフラグ */

#define	FLG_DOOR_OPEN	(1 << 0)	/* 開いている */
#define	FLG_DOOR_JAMMED	(1 << 1)	/* 固定されている */
#define	FLG_DOOR_BROKEN	(1 << 2)	/* 壊れている */
#define	FLG_DOOR_SECRET	(1 << 3)	/* 隠れている */
#define	FLG_DOOR_CHKED	(1 << 4)	/* 調べ済 */
#define	FLG_DOOR_GATE	(1 << 8)	/* 街の門 */
#define	FLG_DOOR_SHOP	(1 << 9)	/* 店の出入口 */

/***************************************************************
* 顔文字
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
* その他
***************************************************************/

/* ドアの最大数 */

#define	DOOR_MAX_N	256

/* カーソル・パターン */

#define	CRSR_PTN_MAX_N	8
#define	CRSR_PTN_MAX_Y_LEN	16
#define	CRSR_PTN_MAX_X_LEN	16

/***************************************************************
* セクション
***************************************************************/

typedef char	sect_t;

/***************************************************************
* 部屋のパターン
***************************************************************/

typedef struct {
	/* 階層 */
	long	min_lev, max_lev, sgn_lev;
	/* 出現率 */
	rate_t	rate;
	/* パターン */
	char	ptn[AREA_MAX_Y][AREA_MAX_X * 2 + 1];
	/* セクション */
	sect_t	sect[AREA_MAX_Y][AREA_MAX_X + 1];
} room_ptn_t;

/***************************************************************
* ドア
***************************************************************/

typedef unsigned long	flg_door_t;

typedef struct {
	long	n;	/* ドア番号 */
	long	x, y;	/* 位置 */
	long	dx, dy;	/* サイズ */
	char	mjr, mnr;	/* 顔 */
	flg_door_t	flg;	/* フラグ */
} door_t;

/***************************************************************
* マップのレイヤー
***************************************************************/

typedef struct {
	char	mjr[MAP_MAX_Y][MAP_MAX_X];	/* major face */
	char	mnr[MAP_MAX_Y][MAP_MAX_X];	/* minor face */
	flg_map_t	flg[MAP_MAX_Y][MAP_MAX_X];
} map_t;

/***************************************************************
* マップ
***************************************************************/

struct chr_t;
struct gui_vfx_t;

typedef struct {
	/* オブジェクトのレイヤー */
	map_t	obj;
	/* キャラクタのレイヤー */
	map_t	chr;
	/* 綜合レイヤー */
	map_t	total;
	/* VFX のレイヤー */
	char	vfx[MAP_MAX_Y][MAP_MAX_X * 2];
	/* GUI VFX のレイヤー */
	struct gui_vfx_t	*gui_vfx[MAP_MAX_Y][MAP_MAX_X];

	/* セクション */
	sect_t	sect[MAP_MAX_Y][MAP_MAX_X];

	/* 場所の明かりレベル */
	long	light_depth_obj[MAP_MAX_Y][MAP_MAX_X];
	/* キャラクタによる明かりレベル */
	long	light_depth_chr[MAP_MAX_Y][MAP_MAX_X];

	/* キャラクタへのポインタ */
	struct chr_t	*chr_p[MAP_MAX_Y][MAP_MAX_X];

	/* 表示の属性 */
	curs_attr_t	attr[MAP_MAX_Y][MAP_MAX_X];
	/* VFXの属性 */
	curs_attr_t	attr_vfx[MAP_MAX_Y][MAP_MAX_X * 2];
} all_map_t;

/***************************************************************
* エリア
***************************************************************/

typedef short	area_t;

/***************************************************************
* 迷宮
***************************************************************/

typedef struct {
	/* マップ */
	all_map_t	map;
	/* エリア */
	area_t	area[AREA_MAP_MAX_Y][AREA_MAP_MAX_X];

	/* ドア */
	door_t	door[DOOR_MAX_N];
	/* ドアの数 */
	long	door_n;

	/* 現在の階数 */
	long	lev;
} dun_t;

/***************************************************************
* カーソル・パターン
***************************************************************/

typedef struct {
	/* 位置 */
	long	x, y;
	/* 幅と高さ */
	long	x_len, y_len;

	/* 透過文字 */
	long	transmit_chr;

	/* パターン */
	char	face[CRSR_PTN_MAX_Y_LEN][CRSR_PTN_MAX_X_LEN * 2 + 1];
} crsr_ptn_t;

#endif	/* DUN_H */
