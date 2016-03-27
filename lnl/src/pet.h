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
* $Id: pet.h,v 1.19 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	PET_H
#define	PET_H

/***************************************************************
* ペット・使い魔・召喚獣
***************************************************************/

#include	"mnstr.h"

/* パーティが連れて行ける数 */
#define	PET_MAX_N	MBR_MAX_N

/* ペットショップに預けている者も含めた総数 */
#define	LS_PET_MAX_N	LS_MBR_MAX_N

/* ペット名の最大文字数 */
#define	PET_NAME_MAX_LEN	MBR_NAME_MAX_LEN
#define	PET_NAME_MAX_BYTE	MBR_NAME_MAX_BYTE

/* ペットショップのペットのダンジョン階層 */
#define	PET_DUN_LEV	10

/* ペットのデータの型定義 */
typedef mnstr_t	pet_t;

/* ペットの種類の型定義 */
typedef mnstr_kind_t	pet_kind_t;

#endif	/* PET_H */
