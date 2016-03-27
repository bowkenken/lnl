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
* $Id: class-tab.h,v 1.10 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	CLASS_TAB_H
#define	CLASS_TAB_H

/* クラス */

#include	"party.h"
#include	"msg.h"

/**/

/* デフォルトのクラスの種類 */

enum {
	CLASS_N_FIGHTER,
	CLASS_N_MONK,
	CLASS_N_HUNTER,
	CLASS_N_THIEF,
	CLASS_N_WIZARD,
	CLASS_N_SUMMONER,
	CLASS_N_PRIEST,
	CLASS_N_SHAMAN,
	CLASS_N_BARD,
	CLASS_N_NINJA,
	CLASS_N_BISHOP,
};

/* クラス・データ */

class_t	class_tab[CLASS_MAX_N + 1];

class_t	class_dflt_tab[] = {
#include	"class-dflt-tab.h"
};

#endif	/* CLASS_TAB_H */
