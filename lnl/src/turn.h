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
* $Id: turn.h,v 1.17 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	TURN_H
#define	TURN_H

/***************************************************************
* ターン
***************************************************************/

/* ターン数の誤差調整 */
#define	ADJUST_TURN	1

/* 昼のターン数 */
#define	TURN_DAYTIME	(TURN_A_DAY / 2)

/* 夜のターン数 */
#define	TURN_NIGHT	(TURN_A_DAY / 2)

/* １日のターン数 */
#define	TURN_A_DAY	(24 * TURN_PER_HOUR)

/* １時間のターン数 */
#define	TURN_PER_HOUR	(60 * TURN_PER_MINUTE)

/* １分のターン数 */
#define	TURN_PER_MINUTE	(60 / SECOND_PER_TURN)

/* １ターンの秒数 */
#define	SECOND_PER_TURN	10

/* 日の出の時間 */
#define	MORNING_HOUR	6

/* 日の入りの時間 */
#define	EVENING_HOUR	17

/* １週間 */
typedef enum {
	DAY_OF_WEEK_ELEC,
	DAY_OF_WEEK_PHYS,
	DAY_OF_WEEK_HEAT,
	DAY_OF_WEEK_COLD,
	DAY_OF_WEEK_WIND,
	DAY_OF_WEEK_ACID,
	DAY_OF_WEEK_POIS,
	DAY_OF_WEEK_MAX_N,
} day_of_week_t;

#endif	/* TURN_H */
