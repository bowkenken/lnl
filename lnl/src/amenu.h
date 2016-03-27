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
* $Id: amenu.h,v 1.26 2014/03/01 23:48:01 bowkenken Exp $
***************************************************************/

#ifndef	AMENU_H
#define	AMENU_H

/***************************************************************
* 自動マーク
***************************************************************/

/* 自動マークの最大数 */
#define	AUTO_MARK_N_PER_PAGE	10
#define	AUTO_MARK_PAGE_N	6
#define	AUTO_MARK_MAX_N		(AUTO_MARK_N_PER_PAGE * AUTO_MARK_PAGE_N)

/* タイトルの最大文字数 */
#define	MSG_TTL_AUTO_MARK_MAX_LEN	64
#define	MSG_TTL_AUTO_MARK_MAX_BYTE	\
	(MSG_TTL_AUTO_MARK_MAX_LEN * CHAR_MAX_LEN_UTF_8)
#define	MSG_TTL_AUTO_MARK_INFO_MAX_LEN	30
#define	MSG_TTL_AUTO_MARK_INFO_MAX_BYTE	\
	(MSG_TTL_AUTO_MARK_INFO_MAX_LEN * CHAR_MAX_LEN_UTF_8)
#define	MSG_TTL_AUTO_MARK_HINT_MAX_LEN	30
#define	MSG_TTL_AUTO_MARK_HINT_MAX_BYTE	\
	(MSG_TTL_AUTO_MARK_HINT_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* アイテムの種類の最大数 */
#define	AUTO_MARK_APPOINT_ITEM_MAX_N	64

/* メンバーの配置からセーブ用の自動マーク・スロット番号へ変換する時の下駄 */
#define	AUTO_MARK_POSITION_MUL	1000

/***************************************************************
* フラグ
* 順番を変える場合はセーブ・データも修整する
***************************************************************/

/* マーク解除時に再びマークしなおす */
#define	FLG_AUTO_MARK_EDIT_CONT	(1 << 0)

/* すでにマークしていても強制的にマークしなおす */
#define	FLG_AUTO_MARK_EDIT_PRIORITY	(1 << 1)

/***************************************************************
* 対象
***************************************************************/

typedef enum {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_TRGT_ITEM,
	AUTO_MARK_TRGT_DOOR,
	AUTO_MARK_TRGT_TRAP,
	AUTO_MARK_TRGT_MBR,
	AUTO_MARK_TRGT_UNCHANGE,
	AUTO_MARK_TRGT_CLEAR,
} auto_mark_trgt_t;

/***************************************************************
* 間合い
***************************************************************/

typedef enum {
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_DIST_MEDIUM,
	AUTO_MARK_DIST_FAR,
} auto_mark_dist_t;

/***************************************************************
* アクション
***************************************************************/

typedef enum {
	AUTO_MARK_ACT_FIGHT,
	AUTO_MARK_ACT_THROW,
	AUTO_MARK_ACT_STEAL,
	AUTO_MARK_ACT_TAIL,
	AUTO_MARK_ACT_PICK_UP,
	AUTO_MARK_ACT_BREAK,
	AUTO_MARK_ACT_OPEN,
	AUTO_MARK_ACT_CLOSE,
	AUTO_MARK_ACT_JAM,
	AUTO_MARK_ACT_DISARM,
	AUTO_MARK_ACT_PEEP,
	AUTO_MARK_ACT_CHK,
} auto_mark_act_t;

/***************************************************************
* 条件
***************************************************************/

typedef enum {
	/* もっとも近い物 */
	AUTO_MARK_COND_NEAREST,

	/* ばらける */
	AUTO_MARK_COND_DISPERSE,

	/* よろけているメンバー */
	AUTO_MARK_COND_STAGGER,

	/* 同じ物を持っている */
	AUTO_MARK_COND_OWN,

	/* 識別済 */
	AUTO_MARK_COND_IDENTIFIED,

	/* 未識別 */
	AUTO_MARK_COND_UN_IDENTIFIED,

	/* 1 番 HP の少ない */
	AUTO_MARK_COND_HP_MIN,

	/* 1 番 HP の多い */
	AUTO_MARK_COND_HP_MAX,

	/* 1 番 MP の少ない */
	AUTO_MARK_COND_MP_MIN,

	/* 1 番 MP の多い */
	AUTO_MARK_COND_MP_MAX,
} auto_mark_cond_t;

/***************************************************************
* デフォルトの自動マークの種類
***************************************************************/

typedef enum {
	DFLT_AUTO_MARK_NULL,

	/* 戦闘(追加) */
	DFLT_AUTO_MARK_FIGHT,
	/* 戦闘(全員) */
	DFLT_AUTO_MARK_FIGHT_PRIO,

	/* 接近戦闘(追加) */
	DFLT_AUTO_MARK_FIGHT_NO_THROW,
	/* 接近戦闘(全員) */
	DFLT_AUTO_MARK_FIGHT_NO_THROW_PRIO,

	/* 殲滅戦(追加) */
	DFLT_AUTO_MARK_FIGHT_ALL,
	/* 殲滅戦(全員) */
	DFLT_AUTO_MARK_FIGHT_ALL_PRIO,

	/* 全てのアイテム */
	DFLT_AUTO_MARK_ITEM_ALL,
	/* 持っているアイテム */
	DFLT_AUTO_MARK_ITEM_OWN,

	/* 退却 */
	DFLT_AUTO_MARK_RETREAT,
	/* 解除 */
	DFLT_AUTO_MARK_CLEAR,

	DFLT_AUTO_MARK_MAX_N,
	DFLT_AUTO_MARK_MIN_N = DFLT_AUTO_MARK_FIGHT,
} dflt_auto_mark_t;

/***************************************************************
* 自動マーク
***************************************************************/

typedef struct {
	auto_mark_trgt_t	trgt;
	auto_mark_dist_t	dist;
	auto_mark_act_t	act;
	auto_mark_cond_t	cond;
	char	macro[MACRO_MAX_LEN + 1];
	unsigned long	flg;

	dflt_auto_mark_t	dflt;
} auto_mark_t;

#endif	/* AMENU_H */
