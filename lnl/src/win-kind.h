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
* $Id: win-kind.h,v 1.10 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef WIN_KIND_H
#define WIN_KIND_H

typedef enum {
	WIN_KIND_NULL,
	WIN_KIND_MAP,
	WIN_KIND_SEL_CONF,
	WIN_KIND_MENU,
	WIN_KIND_MESSAGE,
	WIN_KIND_STAT,
	WIN_KIND_STAT_1,
	WIN_KIND_STAT_2,
	WIN_KIND_STAT_3,
	WIN_KIND_STAT_4,
	WIN_KIND_STAT_5,
	WIN_KIND_STAT_6,
	WIN_KIND_INPUT_NUM,
	WIN_KIND_INPUT_STRING,
	WIN_KIND_WORDS,
	WIN_KIND_REPLAY,
	WIN_KIND_CLASS_EDIT,
	WIN_KIND_SKILL_EDIT,
	WIN_KIND_CHR_SHEET,
	WIN_KIND_MAX_N,
} win_kind_t;

#endif /* WIN_KIND_H */
