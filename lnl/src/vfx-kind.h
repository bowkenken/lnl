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
* $Id: vfx-kind.h,v 1.10 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	VFX_KIND_H
#define	VFX_KIND_H

/* 画面効果 */

typedef enum {
	VFX_KIND_NULL,
	VFX_KIND_ARW,
	VFX_KIND_TYPHOON,
	VFX_KIND_CONFLAGRATION,
	VFX_KIND_EARTHQUAKE,
	VFX_KIND_THUNDER,
	VFX_KIND_INUNDATION,
	VFX_KIND_MAX_N,
} vfx_kind_t;

#endif	/* VFX_KIND_H */
