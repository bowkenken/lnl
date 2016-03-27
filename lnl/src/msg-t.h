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
* $Id: msg-t.h,v 1.13 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MSG_T_H
#define	MSG_T_H

/***************************************************************
* メッセージ
***************************************************************/

#define	CHAR_MAX_LEN_UTF_8	8

/* メッセージのインデックス */

typedef long	n_msg_idx_t;

/* 言語の種類 */

typedef enum {
	LANG_KIND_ENGLISH,
	LANG_KIND_JAPANESE_EUC,
	LANG_KIND_JAPANESE_UTF_8,
	LANG_KIND_JAPANESE_SJIS,
	LANG_KIND_MAX_N,
} lang_kind_t;

#endif	/* MSG_T_H */
