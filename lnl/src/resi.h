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
* $Id: resi.h,v 1.25 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	RESI_H
#define	RESI_H

/* 耐性値 */

#define	RESI_300	300
#define	RESI_200	200
#define	RESI_150	150
#define	RESI_120	120
#define	RESI_100	100
#define	RESI__80	80
#define	RESI__50	50
#define	RESI__30	30
#define	RESI_PRF	30000	/* 完全耐性 */
#define	RESI_PERFECT_N	(RESI_PRF)	/* 完全耐性 */
#define	RESI_MAX_N	(RESI_PERFECT_N - 1)	/* 最大値 */

/* 順番を変える場合はセーブ・データも修整する */
typedef enum {
	RESI_KIND_KNOC,	/* 殴打 */
	RESI_KIND_SLAS,	/* 斬撃 */
	RESI_KIND_STIN,	/* 刺突 */
	RESI_KIND_HEAT,	/* 火熱 */
	RESI_KIND_COLD,	/* 水冷 */
	RESI_KIND_MIND,	/* 風心 */
	RESI_KIND_ACID,	/* 土酸 */
	RESI_KIND_ELEC,	/* 光雷 */
	RESI_KIND_POIS,	/* 闇毒 */
	RESI_KIND_MAX_N,
} resi_kind_t;


typedef struct {
	rate_t	n;	/* 現在値 */
	rate_t	max;	/* 最大値 */
	rate_t	add_n;	/* 修正値 */
} resi_t;

#endif	/* RESI_H */
