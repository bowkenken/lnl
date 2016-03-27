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
* $Id: request.h,v 1.40 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	REQUEST_H
#define	REQUEST_H

/***************************************************************
* 酒場の依頼
***************************************************************/

#include	"item.h"
#include	"chr.h"
#include	"menu.h"

/***************************************************************
* 依頼の数
***************************************************************/

/* 最大数 */
#define	REQUEST_MAX_N	64
/* 平均数 */
#define	REQUEST_AVE_N	32

/* 依頼メッセージの最大長 */
#define	REQUEST_MSG_MAX_LEN	4096
#define	REQUEST_MSG_MAX_BYTE	\
	(REQUEST_MSG_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/***************************************************************
* 依頼の種類
***************************************************************/

typedef enum {
	REQUEST_KIND_NULL,

	/* アイテム探索 */
	REQUEST_KIND_RARE_GOODS,
	/* キャプモン */
	REQUEST_KIND_TAME_MNSTR,
	/* 救助 */
	REQUEST_KIND_RESCUE,
	/* 観光案内 */
	REQUEST_KIND_TOUR_GUIDE,
	/* モンスター退治 */
	REQUEST_KIND_EXTERMINATE,
	/* 仇討ち */
	REQUEST_KIND_REVENGE,
	/* 賞金首 */
	REQUEST_KIND_WANTED_CRIMINAL,

	REQUEST_KIND_MAX_N,
} request_kind_t;

/***************************************************************
* 依頼のデータ型
***************************************************************/

typedef struct request_t {
	/* 種類 */
	request_kind_t	kind;
	/* 最小階, 最大階, 目的の階 */
	long	dun_min_lev, dun_max_lev, dun_true_lev;
	/* 賞金額 */
	gold_t	prize;
	/* 報酬経験値 */
	long	exp;
	/* 期限日数 */
	long	limit;

	/* 引き受けフラグ */
	bool_t	flg_contract;
	/* メンバーの引き受けフラグ */
	bool_t	flg_contract_mbr;
	/* 引き受けたキャラの名前 */
	n_msg_idx_t	idx_contract_name;
	/* 引き受けたキャラの性別 */
	sex_t	contract_sex;
	/* 達成フラグ */
	bool_t	flg_finish;

	/* 探索するアイテムの種類 */
	rare_goods_kind_t	rare_goods_kind;

	/* 目標の敵が NPC か? */
	bool_t	flg_mnstr_is_npc;
	/* 目標のモンスターの種類 */
	mnstr_kind_t	mnstr_kind;
	/* 目標のモンスターの数 */
	long	mnstr_n;
	/* 倒したモンスターの数 */
	long	mnstr_exterminate_n;

	/* リスト上の見出し */
	char	heading[MENU_MSG_MAX_BYTE + 1];
	/* 依頼メッセージのインデックス */
	n_msg_idx_t	idx_fmt;
	/* 依頼メッセージ */
	char	msg[REQUEST_MSG_MAX_BYTE + 1];

	/* 依頼主の名前のインデックス */
	n_msg_idx_t	idx_client_name;
	/* モンスターの名前のインデックス */
	n_msg_idx_t	idx_mnstr_name;
	/* 救助する NPC の名前のインデックス */
	n_msg_idx_t	idx_rescue_trgt_name;
	/* 依頼主の家族の名前のインデックス */
	n_msg_idx_t	idx_client_family_name;
	/* 依頼主の仲間の名前のインデックス */
	n_msg_idx_t	idx_client_mate_name;
	/* 依頼主の性別 */
	sex_t	client_sex;
	/* モンスターの性別 */
	sex_t	mnstr_sex;
	/* 救助する NPC の性別 */
	sex_t	rescue_trgt_sex;
	/* 依頼主の家族の性別 */
	sex_t	client_family_sex;
	/* 依頼主の仲間の性別 */
	sex_t	client_mate_sex;
	/* 救助する NPC の種類 */
	mnstr_kind_t	rescue_trgt_kind;

	/* 依頼の時間のインデックス */
	n_msg_idx_t	idx_when_1, idx_when_2;
	/* 依頼の武器のインデックス */
	n_msg_idx_t	idx_weapon;
} request_t;

#endif	/* REQUEST_H */
