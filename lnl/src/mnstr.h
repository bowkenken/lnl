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
* $Id: mnstr.h,v 1.42 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MNSTR_H
#define	MNSTR_H

/***************************************************************
* モンスター
***************************************************************/

#include	"chr.h"
#include	"mnstr-kind.h"

/* モンスターの数 */

/* 最大数 */
#define	MNSTR_MAX_N	128
/* 平均出現数 */
#define	MNSTR_AVE_N	16

/* モンスターが行動する、距離の差 */
#define	MNSTR_MOVE_MAX_X	(AREA_MAX_X * 4 + 0)
#define	MNSTR_MOVE_MAX_Y	(AREA_MAX_Y * 4 + 0)

/* 近いと判断する距離 */
#define	MNSTR_NEAR_R	4

/* モンスターを何匹倒すとメンバーのレベルが上がるかの目安 */
#define	EXP_NEED_KILL_MNSTR_N	20

/* モンスターがアイテムを落す確率 */
#define	ITEM_DROP_RATE_100	((rate_t)100)

#define	ITEM_DROP_RATE_AAA	((rate_t)90)
#define	ITEM_DROP_RATE_AA	((rate_t)80)
#define	ITEM_DROP_RATE_A	((rate_t)70)

#define	ITEM_DROP_RATE_BBB	((rate_t)60)
#define	ITEM_DROP_RATE_BB	((rate_t)50)
#define	ITEM_DROP_RATE_B	((rate_t)40)

#define	ITEM_DROP_RATE_CCC	((rate_t)30)
#define	ITEM_DROP_RATE_CC	((rate_t)20)
#define	ITEM_DROP_RATE_C	((rate_t)10)

#define	ITEM_DROP_RATE_DDD	((rate_t)5)
#define	ITEM_DROP_RATE_DD	((rate_t)3)
#define	ITEM_DROP_RATE_D	((rate_t)1)

#define	ITEM_DROP_RATE_0	((rate_t)0)

/***************************************************************
* データ型の定義
***************************************************************/

/* モンスターのデータ */

typedef chr_t	mnstr_t;

/* モンスターのいない場所を攻撃した時のダミー */

typedef struct {
	long	x, y;
} mnstr_null_t;

/* モンスターの出現階数のデータ */

typedef struct {
	/* モンスターの種類 */
	mnstr_kind_t	kind;

	/* 発生する階の最小・最大の差分 */
	long	add_lev, range_lev;

	/* 発生する階の最小・最大 */
	/* 初期化関数で自動計算する */
	long	min_lev, max_lev;
} mnstr_lev_tab_t;

/* ラスボスの種類 */

typedef enum {
	LAST_BOSS_KIND_NULL,
	LAST_BOSS_KIND_EXEL,
	LAST_BOSS_KIND_EXELER,
	LAST_BOSS_KIND_XEX,
	LAST_BOSS_KIND_XX,
	LAST_BOSS_KIND_MAX_N,
} last_boss_kind_t;

#endif	/* MNSTR_H */
