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
* $Id: town.h,v 1.29 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	TOWN_H
#define	TOWN_H

#include	"dun.h"
#include	"party.h"
#include	"mnstr.h"

#define	SHOP_ADD_TURN_N	(15 * TURN_PER_MINUTE)
#define	NAVI_ADD_TURN_N	((MAP_MAX_X + MAP_MAX_Y) / 2)

typedef enum {
	SHOP_N_NULL,
	SHOP_N_BAR,
	SHOP_N_INN,
	SHOP_N_WPN,
	SHOP_N_ARMOR,
	SHOP_N_MAGIC,
	SHOP_N_TEMPLE,
	SHOP_N_ALCHEMY,
	SHOP_N_MUSIC,
	SHOP_N_GROCERY,
	SHOP_N_RESTAURANT,
	SHOP_N_TEAROOM,
	SHOP_N_TOBACCO,
	SHOP_N_PET_SHOP,
	SHOP_N_MAX_N,
} shop_n_t;

/* 割り引きセール */

#define	DISCOUNT_QUEUE_MAX_N	(32 + MBR_MAX_N)

typedef struct {
	shop_n_t	shop_n;
	door_t	*door;
	bool_t	flg_sold_out;	/* 売り切れフラグ */
	long	n;
	pos_t	pos[DISCOUNT_QUEUE_MAX_N];	/* 行列の人の位置 */
	chr_t	*chr[DISCOUNT_QUEUE_MAX_N];	/* 行列の人 */
} discount_queue_t;

/**/

#define	TOWN_PTN_COL_MAX_N	64

/* 街灯の照らす範囲 */

#define	STREETLAMP_R	2

/* 街のマップ・データ */

typedef struct {
	long	col_str_len;
	long	col_n;
	unsigned char	col_mjr[TOWN_PTN_COL_MAX_N];
	unsigned char	col_mnr[TOWN_PTN_COL_MAX_N];
	char	map_mjr[MAP_MAX_Y][MAP_MAX_X];
	char	map_mnr[MAP_MAX_Y][MAP_MAX_X];
} town_ptn_t;

typedef struct {
	long	col_code;
	char	mjr, mnr;
} town_ptn_col_tab_t;

/* ペット・ショップの商品リスト */

typedef struct {
	mnstr_kind_t	kind;
	gold_t	price;
} art_ls_pet_shop_t;

#endif	/* TOWN_H */
