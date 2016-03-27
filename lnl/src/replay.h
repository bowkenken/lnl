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
* $Id: replay.h,v 1.9 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	REPLAY_H
#define	REPLAY_H

/***************************************************************
* リプレイ
***************************************************************/

#define	REPLAY_BUF_MAX_LEN	50

typedef enum {
	REPLAY_KIND_KEY,
	REPLAY_KIND_GETS,
	REPLAY_KIND_MAX_N,
} replay_kind_t;

typedef enum {
	REPLAY_SLOT_NULL,
	REPLAY_SLOT_AUTO = REPLAY_SLOT_NULL,
	REPLAY_SLOT_BUG_REPO,
	REPLAY_SLOT_STD,
	REPLAY_SLOT_PLAY,
	REPLAY_SLOT_MAX_N,
} replay_slot_t;

typedef struct replay_t {
	struct replay_t	*next;
	replay_kind_t	kind;
	long	n;
	char	buf[REPLAY_BUF_MAX_LEN + 1];
} replay_t;

#endif	/* REPLAY_H */
