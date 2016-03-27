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
* $Id: party.h,v 1.28 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	PARTY_H
#define	PARTY_H

/* パーティとメンバー */

#include	"chr.h"
#include	"stay-inn-kind.h"

/* メンバー */

enum {
	LS_MBR_N_BLADE,
	LS_MBR_N_DRANK,
	LS_MBR_N_ELSIE,
	LS_MBR_N_CECILE,
	LS_MBR_N_HALLE,
	LS_MBR_N_BEAUT,
	LS_MBR_N_GOKOU,
	LS_MBR_N_EYE,
};

#define	MBR_MAX_N	6	/* 最大数 */
#define	MBR_N_NOT_JOIN	(-1)	/* パーティに加わっていない時 */
#define	MBR_NO_POS	(-1)	/* フォーメーションの空き */

/* パーティ */

#define	LS_MBR_MAX_N	64	/* メンバーの最大登録数 */

typedef unsigned long	flg_party_t;
#define	FLG_PARTY_ACTUAL_FIGHTING	(1 << 0)
#define	FLG_PARTY_SRCH_AUTO_OFF	(1 << 1)

typedef chr_t	mbr_t;

/* アンカー(パーティの移動の中心) */

typedef enum {
	SQUARE_DIR_NORTH,
	SQUARE_DIR_EAST,
	SQUARE_DIR_SOUTH,
	SQUARE_DIR_WEST,
	SQUARE_DIR_MAX_N,
} square_dir_t;

typedef struct {
	/* 座標 */
	long	x, y;
	/* 1つ前の座標 */
	long	pre_x, pre_y;
	/* 向いている方向 */
	square_dir_t	dir;
	/* 1つ前の向いている方向 */
	square_dir_t	pre_dir;

	/* 上を向いている時の設定上の向き */
	long	chr_pos_n[SQUARE_HEIGHT][SQUARE_WIDTH];

	/* 実際の向き */
	long	chr_dir[SQUARE_HEIGHT][SQUARE_WIDTH];

	/* キャラクタのアンカーからの相対座標 (全体アンカー) */
	pos_t	chr_rel_pos[MBR_MAX_N];
	/* キャラクタのマップ上の絶対座標 (全体アンカー) */
	pos_t	chr_abs_pos[MBR_MAX_N];
	/* キャラクタのマップ上の絶対座標 (個別アンカー) */
	pos_t	chr_ind_pos[MBR_MAX_N];
	/* 各キャラクタのアンカー座標 */
	pos_t	chr_map_pos[MBR_MAX_N];
	/* 各キャラクタの1つ前のアンカー座標 */
	pos_t	chr_pre_pos[MBR_MAX_N];
} square_t;

/* パーティ */

typedef struct {
	mbr_t	*mbr[MBR_MAX_N];	/* メンバー */
	square_t	square;	/* アンカー */
	flg_party_t	flg;	/* フラグ */
	act_t	act;	/* パーティ全体のアクション */
} party_t;

#endif	/* PARTY_H */
