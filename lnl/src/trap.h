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
* $Id: trap.h,v 1.40 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	TRAP_H
#define	TRAP_H

/***************************************************************
* 罠
***************************************************************/

#include	"gmain.h"
#include	"msg.h"

/***************************************************************
* デバッグ用スイッチ
***************************************************************/

/* 1 にすると罠を大量につくる(デバッグ用) */

#if	0
# ifndef	D_TEST_TRAP
#  define	D_TEST_TRAP
# endif
#endif

#ifdef	D_TEST_TRAP
# define	TRAP_AVE_N	512
# define	TRAP_MAX_N	1024
#else
# define	TRAP_AVE_N	12
# define	TRAP_MAX_N	128
#endif

/***************************************************************
* 罠の種類
***************************************************************/

typedef enum {
	TRAP_KIND_NULL,
	/* 眠りの罠 */
	TRAP_KIND_SLEEP,
	/* 弓矢の罠 */
	TRAP_KIND_ARW,
	/* 毒ダーツの罠 */
	TRAP_KIND_POISON_DARTS,
	/* 爆弾の罠 */
	TRAP_KIND_BOMB,
	/* パーティ瞬間移動の罠 */
	TRAP_KIND_TELEPORT_PARTY,
	/* 瞬間移動の罠 */
	TRAP_KIND_TELEPORT,
	/* 落し穴 */
	TRAP_KIND_PIT,
	/* シュート */
	TRAP_KIND_CHUTE,
	/* 聖域 */
	TRAP_KIND_SANCTUARY,
	TRAP_KIND_MAX_N
} trap_kind_t;

/***************************************************************
* 罠のデータ・テーブル
***************************************************************/

typedef struct {
	/* 種類 */
	trap_kind_t	kind;
	/* 名前の ID */
	n_msg_t	name_n;
	/* 名前 */
	char	*name;
	/* 出現率 */
	rate_t	rate;
	/* マイナーの顏文字 */
	char	mnr;
	/* 出現階 */
	long	min_lev, max_lev, sgn_lev;
	/* メッセージを表示するか? */
	bool_t	flg_draw_msg;
} trap_tab_t;

/***************************************************************
* 罠のデータ
***************************************************************/

typedef struct trap_t {
	/* リンク・ポインタ */
	struct trap_t	*next, *prev;

	/* 種類 */
	trap_kind_t	kind;
	/* 座標 */
	long	x, y;

	/* 罠のレベル */
	long	lev;
	/* 解除の難しさ */
	long	difficulty;
	/* 調べられているか? */
	bool_t	flg_chked;
	/* 罠の中心への相対座標 */
	bool_t	cx, cy;

	/* データ・テーブル */
	trap_tab_t	*tab;
} trap_t;

#endif	/* TRAP_H */
