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
* $Id: item-kind.h,v 1.11 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	ITEM_KIND_H
#define	ITEM_KIND_H

/* アイテムの種類 */

typedef enum {
	ITEM_KIND_NULL,
	ITEM_KIND_WPN,
	ITEM_KIND_ARMOR,
	ITEM_KIND_POTION,
	ITEM_KIND_SCROLL,
	ITEM_KIND_STICK,
	ITEM_KIND_ACCE,
	ITEM_KIND_INST,
	ITEM_KIND_ANTHOLOGY,
	ITEM_KIND_LIGHT,
	ITEM_KIND_SPIKE,
	ITEM_KIND_FOOD,
	ITEM_KIND_CHEST,
	ITEM_KIND_TOBACCO,
	ITEM_KIND_PIPE,
	ITEM_KIND_DISPOSAL,
	ITEM_KIND_RARE_GOODS,
	ITEM_KIND_BONE,
	ITEM_KIND_COIN,
	ITEM_KIND_JUNK,
	ITEM_KIND_MAX_N,
} item_kind_t;

#endif	/* ITEM_KIND_H */
