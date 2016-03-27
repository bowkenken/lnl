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
* $Id: skill.h,v 1.9 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	SKILL_H
#define	SKILL_H

/***************************************************************
* スキル
***************************************************************/

#include	"msg.h"

#define	SKILL_MAX_N	(SKILL_PER_PAGE_MAX_N * SKILL_MAX_PAGE)
#define	SKILL_PER_PAGE_MAX_N	10
#define	SKILL_MAX_PAGE	2

#define	SKILL_PER_GROUP_MAX_N	30

#define	SKILL_NAME_MAX_LEN	30
#define	SKILL_NAME_MAX_BYTE	(SKILL_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)

#define	SKILL_HINT_MAX_LEN	\
	(SKILL_HINT_LINE_MAX_LEN * SKILL_HINT_MAX_LINE)
#define	SKILL_HINT_MAX_BYTE	(SKILL_HINT_MAX_LEN * CHAR_MAX_LEN_UTF_8)

#define	SKILL_HINT_LINE_MAX_LEN	30
#define	SKILL_HINT_LINE_MAX_BYTE	\
	(SKILL_HINT_LINE_MAX_LEN * CHAR_MAX_LEN_UTF_8)

#define	SKILL_HINT_MAX_LINE	4

/***************************************************************
* レベルによるスキルの発動確率の変化
***************************************************************/

#define	SKILL_FIGHT_A_BASE_RATE	((rate_t)150)
#define	SKILL_FIGHT_A_ADD_RATE	((rate_t)1)
#define	SKILL_FIGHT_A_SUB_BASE_RATE	((rate_t)80)
#define	SKILL_FIGHT_B_BASE_RATE	((rate_t)120)
#define	SKILL_FIGHT_B_ADD_RATE	((rate_t)1)
#define	SKILL_FIGHT_C_MUL_RATE	((rate_t)10)
#define	SKILL_FIGHT_C_ADD_RATE	((rate_t)1)

#define	SIEGE_R	8
#define	PHALANX_R	4

#define	SKILL_FIG_BASE_RATE	((rate_t)120)
#define	SKILL_FIG_ADD_RATE	((rate_t)2)
#define	SKILL_MON_BASE_RATE	((rate_t)220)
#define	SKILL_MON_ADD_RATE	((rate_t)3)
#define	SKILL_HUN_BASE_RATE	((rate_t)120)
#define	SKILL_HUN_ADD_RATE	((rate_t)2)

#define	SKILL_COUNTER_BASE_RATE	((rate_t)80)
#define	SKILL_COUNTER_ADD_RATE	((rate_t)2)

#define	SKILL_TWO_SWORD_FENCING_BASE_RATE	((rate_t)80)
#define	SKILL_TWO_SWORD_FENCING_ADD_RATE	((rate_t)2)

#define	SKILL_COMBO_MIN_N	1
#define	SKILL_COUNTER_MIN_N	0
#define	SKILL_TWO_SWORD_FENCING_MIN_N	0

#define	SKILL_DAM_BASE_RATE	((rate_t)120)
#define	SKILL_DAM_ADD_RATE	((rate_t)1)
#define	SKILL_RESI_BASE_RATE	((rate_t)120)
#define	SKILL_RESI_ADD_RATE	((rate_t)1)
#define	SKILL_STAT_BASE_N	1
#define	SKILL_STAT_ADD_N	1

#define	SKILL_RUN_AWAY_BASE_N	((rate_t)120)
#define	SKILL_RUN_AWAY_ADD_N	((rate_t)1)

/***************************************************************
* スキルの種類
***************************************************************/

/* スキルのグループの種類 */

typedef enum {
	SKILL_GROUP_KIND_NULL,

	SKILL_GROUP_KIND_FIGHT,
	SKILL_GROUP_KIND_COMBO,
	SKILL_GROUP_KIND_DAM,
	SKILL_GROUP_KIND_RESI,
	SKILL_GROUP_KIND_RESI_STAT_1,
	SKILL_GROUP_KIND_RESI_STAT_2,
	SKILL_GROUP_KIND_MISC,

	SKILL_GROUP_KIND_MAX_N,
} skill_group_kind_t;

/* スキルの種類 */

typedef enum {
	SKILL_KIND_NULL,

	/* SKILL_GROUP_KIND_FIGHT, */
	SKILL_KIND_ATTACKER,
	SKILL_KIND_BERSERKER,
	SKILL_KIND_DEFENDER,
	SKILL_KIND_SENTINEL,
	SKILL_KIND_ASSASSIN,
	SKILL_KIND_AEGIS,
	SKILL_KIND_SIEGE,
	SKILL_KIND_PHALANX,

	/* SKILL_GROUP_KIND_COMBO, */
	SKILL_KIND_DOUBLE_ATTACK,
	SKILL_KIND_COMBO,
	SKILL_KIND_RAPID_SHOOT,
	SKILL_KIND_COUNTER,
	SKILL_KIND_TWO_SWORD_FENCING,

	/* SKILL_GROUP_KIND_DAM, */
	SKILL_KIND_DAM_KNOC,
	SKILL_KIND_DAM_SLAS,
	SKILL_KIND_DAM_STIN,
	SKILL_KIND_DAM_HEAT,
	SKILL_KIND_DAM_COLD,
	SKILL_KIND_DAM_MIND,
	SKILL_KIND_DAM_ACID,
	SKILL_KIND_DAM_ELEC,
	SKILL_KIND_DAM_POIS,

	/* SKILL_GROUP_KIND_RESI, */
	SKILL_KIND_RESI_KNOC,
	SKILL_KIND_RESI_SLAS,
	SKILL_KIND_RESI_STIN,
	SKILL_KIND_RESI_HEAT,
	SKILL_KIND_RESI_COLD,
	SKILL_KIND_RESI_MIND,
	SKILL_KIND_RESI_ACID,
	SKILL_KIND_RESI_ELEC,
	SKILL_KIND_RESI_POIS,

	/* SKILL_GROUP_KIND_RESI_STAT, */
	SKILL_KIND_STAT_DEAD,
	SKILL_KIND_STAT_STONE,
	SKILL_KIND_STAT_PARALYZE,
	SKILL_KIND_STAT_POISON,
	SKILL_KIND_STAT_CONFUSION,
	SKILL_KIND_STAT_BLIND,
	SKILL_KIND_STAT_SLEEP,
	SKILL_KIND_STAT_SILENCE,
	SKILL_KIND_STAT_CAUGHT,
	SKILL_KIND_STAT_FEAR,
	SKILL_KIND_STAT_HALLUCINATION,
	SKILL_KIND_STAT_CHARM,
	SKILL_KIND_STAT_FLY,
	SKILL_KIND_STAT_HUNGRY,
	SKILL_KIND_STAT_STARVATION,
	SKILL_KIND_STAT_FAINT,
	SKILL_KIND_STAT_DRUNK,
	SKILL_KIND_STAT_VANISH,
	SKILL_KIND_STAT_IRON_BODY,
	SKILL_KIND_STAT_PASSWALL,
	SKILL_KIND_STAT_SENSE_INVISIBLE,

	/* SKILL_GROUP_KIND_MISC, */
	SKILL_KIND_RUN_AWAY,

	SKILL_KIND_MAX_N,
} skill_kind_t;

/* スキルの発動条件の種類 */

typedef enum {
	SKILL_COND_NULL,

	SKILL_COND_ALWAYS,

	SKILL_COND_HP_FEW,
	SKILL_COND_MP_FEW,
	SKILL_COND_HP_LOT,
	SKILL_COND_MP_LOT,

	SKILL_COND_FIG,
	SKILL_COND_MON,
	SKILL_COND_HUN,

	SKILL_COND_TWO_SWORD,

	SKILL_COND_COMBI_ATTACK,
	SKILL_COND_COMBI_DEFENSE,

	SKILL_COND_MAX_N,
} skill_cond_t;

/* スキル・データ */

typedef struct {
	/* 種類 */
	skill_kind_t	kind;
	skill_group_kind_t	group;

	/* 名前 */
	n_msg_t	n_name;
	char	*name;

	/* 発動条件 */
	skill_cond_t	cond;
	void	*cond_arg;

	/* 有効フラグ */
	bool_t	flg_ena;
} skill_tab_t;

#endif	/* SKILL_H */
