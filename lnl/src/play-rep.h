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
* $Id: play-rep.h,v 1.3 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	PLAY_REP_H
#define	PLAY_REP_H

/* 統計データ */

#include	"stay-inn-kind.h"
#include	"item.h"
#include	"resi.h"
#include	"spell-kind.h"

typedef struct {
	gold_t	paying_gold;
	long	staying_inn[STAY_INN_KIND_MAX_N];
	long	wearing_equip[EQUIP_KIND_MAX_N];
	long	making_dam[RESI_KIND_MAX_N];
	long	made_dam[RESI_KIND_MAX_N];
	long	using_spell[SPELL_KIND_MAX_N];
	long	used_spell[SPELL_KIND_MAX_N];
} playing_report_t;

#endif	/* PLAY_REP_H */
