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
* $Id: fight.h,v 1.39 2014/03/02 00:40:47 bowkenken Exp $
***************************************************************/

#ifndef	FIGHT_H
#define	FIGHT_H

/***************************************************************
* 戦闘
***************************************************************/

#include	"spell-kind.h"
#include	"fx.h"
#include	"resi.h"

/***************************************************************/

/* 攻撃データの最大数 */

#define	CHR_ATACK_MAX_N	(4 + 1)

/* 攻撃の種類 */

typedef enum {
	ATTACK_KIND_NULL,
	ATTACK_KIND_SPELL,	/* 魔法 */
	ATTACK_KIND_SPELL_SELF,	/* 魔法 */
	ATTACK_KIND_SPELL_FRIEND,	/* 魔法 */
	ATTACK_KIND_PUNCH,	/* 殴る */
	ATTACK_KIND_KICK,	/* 蹴る */
	ATTACK_KIND_KNOCK,	/* 叩く */
	ATTACK_KIND_SLASH,	/* 切る */
	ATTACK_KIND_STING,	/* 刺す */
	ATTACK_KIND_MOW,	/* 薙払う */
	ATTACK_KIND_SHOOT,	/* 射る */
	ATTACK_KIND_THROW,	/* 投げつける */
	ATTACK_KIND_BITE,	/* 噛む */
	ATTACK_KIND_PECK,	/* 突っつく */
	ATTACK_KIND_CLAW,	/* 引っ掻く */
	ATTACK_KIND_NIP,	/* 挟む */
	ATTACK_KIND_STRANGLE,	/* 締めつける */
	ATTACK_KIND_TACKLE,	/* ぶつかる */
	ATTACK_KIND_TOUCH,	/* 触れる */
	ATTACK_KIND_INDICATE,	/* 指さす */
	ATTACK_KIND_KISS,	/* キス */
	ATTACK_KIND_SEDUCE,	/* 誘惑する */
	ATTACK_KIND_CARESS_BUST,	/* 胸を触る */
	ATTACK_KIND_CARESS_HIP,	/* 腰を撫でる */
	ATTACK_KIND_CARESS_CROTCH,	/* 股間を撫でる */
	ATTACK_KIND_CYBERN_PUNCH,	/* 光子パンチ */
	ATTACK_KIND_CYBERN_KICK,	/* 光子キック */
	ATTACK_KIND_XX_SLAP,	/* 平手打ち攻撃 */
	ATTACK_KIND_MAX_N,
} attack_kind_t;

/* 攻撃にMON技能を使うフラグ */
#define	FLG_ATTACK_MONK	TRUE

/* 攻撃にHUN技能を使うフラグ */
#define	FLG_ATTACK_THROW	TRUE

/* 攻撃データ */

typedef struct {
	/* 種類 */
	attack_kind_t	kind;

	/* 率 */
	ratio_t	ratio;

	/* 投げフラグ、格闘フラグ */
	bool_t	flg_throw, flg_monk;

	/* 攻撃力 */
	rate_t	hit, crtcl, dam;

	/* 抵抗の種類 */
	resi_kind_t	resi_kind;

	/* 攻撃半径 */
	long	range_bash, range_throw;

	/* エフェクト */
	fx_kind_t	fx_kind;
	/* エフェクトのターン数 */
	long	fx_turn;

	/* 発動する呪文 */
	spell_kind_t	spell;
	/* 呪文の効果範囲 */
	extent_kind_t	extent;
	/* 呪文の別名 */
	n_msg_t	spell_fmt;
} attack_t;

#endif	/* FIGHT_H */
