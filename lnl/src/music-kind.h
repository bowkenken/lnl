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
* $Id: music-kind.h,v 1.6 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MUSIC_KIND_KIND_H
#define	MUSIC_KIND_KIND_H

/* BGM (Back Ground Music) の種類 */

typedef enum {
	MUSIC_KIND_NULL,

	MUSIC_KIND_TITLE,
	MUSIC_KIND_GAME_OVER,
	MUSIC_KIND_ENDING,
	MUSIC_KIND_THE_END,
	MUSIC_KIND_TOWN,
	MUSIC_KIND_SHOP,
	MUSIC_KIND_DUN,
	MUSIC_KIND_LAST_BOSS,
	MUSIC_KIND_BATTLE,
	MUSIC_KIND_BATTLE_BOSS,
	MUSIC_KIND_BATTLE_LAST_BOSS,
	MUSIC_KIND_EFFECT,

	MUSIC_KIND_MAX_N,
} music_kind_t;

/* ME (Music Effect) の種類 */

typedef enum {
	ME_KIND_NULL,

	ME_KIND_INN,
	ME_KIND_TEMPLE,

	ME_KIND_MAX_N,
} me_kind_t;

#endif	/* MUSIC_KIND_KIND_H */
