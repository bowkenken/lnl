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
* $Id: chr.h,v 1.130 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	CHR_H
#define	CHR_H

/***************************************************************
* キャラクタ
***************************************************************/

#include	"dun.h"
#include	"fight.h"
#include	"fx.h"
#include	"skill.h"
#include	"misc.h"

#include	"resi.h"
#include	"abl-kind.h"
#include	"mnstr-kind.h"
#include	"item-kind.h"

#include	"gfile.h"

/***************************************************************
* 経験値とレベル
***************************************************************/

#define	ABL_SKILL_MAX_N	(ABL_KIND_MAX_N + SKILL_KIND_MAX_N)

/* レベルの最高値 */
#define	ABL_MAX_LEV	9999

/* 経験値の最大値 */
#define	EXP_MAX	99999999
#define	NEED_EXP_MAX	(EXP_MAX + 1)

/* キャラクタのレベルと、迷宮のレベルとの比率 */
#define	RATE_LEV_PER_DUN_LEV	((rate_t)30)

/***************************************************************
* 名前の最大文字数
***************************************************************/

/* キャラクタ */
#define	CHR_NAME_MAX_LEN	80
#define	CHR_NAME_MAX_BYTE	(CHR_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)
/* メンバー */
#define	MBR_NAME_MAX_LEN	16
#define	MBR_NAME_MAX_BYTE	(MBR_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)
/* モンスター */
#define	MNSTR_NAME_MAX_LEN	CHR_NAME_MAX_LEN
#define	MNSTR_NAME_MAX_BYTE	CHR_NAME_MAX_BYTE

/* 掛け合わせも含めた種族名 */
#define	RACE_STR_MAX_LEN	32
#define	RACE_STR_MAX_BYTE	(RACE_STR_MAX_LEN * CHAR_MAX_LEN_UTF_8)
/* 種族名 */
#define	RACE_NAME_MAX_LEN	16
#define	RACE_NAME_MAX_BYTE	(RACE_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/***************************************************************
* キャラクタの能力
***************************************************************/

#define	MOVE_LS_MAX_N	3	/* キャラクタの移動の種類の最大数 */

#define	ABL_RATE_MIN_N	((rate_t)0)	/* 経験値の割り振りの最低値 */
#define	ABL_RATE_MAX_N	((rate_t)20)	/* 経験値の割り振りの最高値 */

/***************************************************************
* キャラクタのフラグ
* 順番を変える場合はセーブ・データも修整する
***************************************************************/

typedef unsigned long	flg_chr_t;
#define	FLG_CHR_AUTO_FIGHT	(1 << 0)	/* 敵にぶつかったら攻撃する */
#define	FLG_CHR_AUTO_DOOR	(1 << 1)	/* 自動でドアを開ける */
#define	FLG_CHR_AVOID_TRAP	(1 << 2)	/* 罠を避ける */
#define	FLG_CHR_AUTO_RELOAD	(1 << 3)	/* 矢を自動で補充 */
#define	FLG_CHR_AUTO_MARK_CONT	(1 << 4)	/* 連続で自動マークする */
#define	FLG_CHR_NO_MARK_MNSTR	(1 << 8)	/* 戦闘に参加しない(NPC用) */
#define	FLG_CHR_CAN_OPEN_DOOR	(1 << 9)	/* ドアを開けれる */
#define	FLG_CHR_CAN_BREAK_DOOR	(1 << 10)	/* ドアを壊せる */
#define	FLG_CHR_LIGHT	(1 << 11)	/* 光っている */
#define	FLG_CHR_DARK	(1 << 12)	/* 闇を放っている */
#define	FLG_CHR_MAGIC_PROTECT	(1 << 13)	/* 魔法の武器しか効かない */
#define	FLG_CHR_HYPER	(1 << 14)	/* 大型化する */
#define	FLG_CHR_CAN_DEL	(1 << 20)	/*  */
#define	FLG_CHR_CAN_DISMISSAL	(1 << 21)	/* 送還出来る */

/***************************************************************
* キャラクタのステータス
* 順番を変える場合はセーブ・データも修整する
***************************************************************/

typedef unsigned long	flg_stat_t;
#define	FLG_STAT_NULL	0
#define	FLG_STAT_NOT_EXIST	(1 << 0)	/* 空き */
#define	FLG_STAT_DEAD	(1 << 1)	/* 死亡 */
#define	FLG_STAT_STONE	(1 << 2)	/* 石化 */
#define	FLG_STAT_PARALYZE	(1 << 3)	/* 麻痺 */
#define	FLG_STAT_POISON	(1 << 4)	/* 毒 */
#define	FLG_STAT_CONFUSION	(1 << 5)	/* 混乱 */
#define	FLG_STAT_BLIND	(1 << 6)	/* 盲目 */
#define	FLG_STAT_SLEEP	(1 << 7)	/* 眠り */
#define	FLG_STAT_SILENCE	(1 << 8)	/* 沈黙 */
#define	FLG_STAT_CAUGHT	(1 << 9)	/* 拘束 */
#define	FLG_STAT_FEAR	(1 << 10)	/* 恐怖 */
#define	FLG_STAT_HALLUCINATION	(1 << 11)	/* 幻覚 */
#define	FLG_STAT_CHARM	(1 << 12)	/* 魅了 */
#define	FLG_STAT_FLY	(1 << 13)	/* 浮遊 */
#define	FLG_STAT_HUNGRY	(1 << 14)	/* 空腹 */
#define	FLG_STAT_STARVATION	(1 << 15)	/* 飢餓 */
#define	FLG_STAT_FAINT	(1 << 16)	/* めまい */
#define	FLG_STAT_DRUNK	(1 << 17)	/* 酔い */
#define	FLG_STAT_VANISH	(1 << 18)	/* 透明化 */
#define	FLG_STAT_IRON_BODY	(1 << 19)	/* 鋼鉄化 */
#define	FLG_STAT_PASSWALL	(1 << 20)	/* 壁抜け */
#define	FLG_STAT_SENSE_INVISIBLE	(1 << 21)	/* 不可視感知 */

#define STAT_MAX_N	22

/***************************************************************
* キャラクタのワーク・フラグ
* 順番を変える場合はセーブ・データも修整する
***************************************************************/

typedef unsigned long	flg_work_t;

/* モンスターがメンバーを発見している */
#define	FLG_WORK_FIND_MBR	(1 << 0)

/* モンスターから既にアイテムを盗んでいる */
#define	FLG_WORK_STEAL_END	(1 << 1)

/* 2x2 サイズ以上のモンスターが爆風に 1 度しか当ら無い様にするフラグ */
#define	FLG_WORK_BLAST_END	(1 << 2)

/***************************************************************
* クラス
***************************************************************/

/* 最大数 */
#define	CLASS_MAX_N	99

/* 名前の最大文字数 */
#define	CLASS_NAME_MAX_LEN	20
#define	CLASS_NAME_MAX_BYTE	\
	(CLASS_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/***************************************************************
* アンカー
***************************************************************/

#define	SQUARE_WIDTH	3	/* 幅 */
#define	SQUARE_HEIGHT	3	/* 高さ */

/***************************************************************
* その他
***************************************************************/

/* サイコロの底値 */
#define	ROLL_BASE	10

/* アクションの最大文字数 */
#define	ACT_MSG_MAX_LEN	64
#define	ACT_MSG_MAX_BYTE	(ACT_MSG_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* ふらつき率 */
#define	STAGGER_RATE_CHR_CONFUSION	((rate_t)70)	/* 混乱時 */
#define	STAGGER_RATE_CHR_BLIND	((rate_t)30)	/* 目が見えない時 */
#define	STAGGER_RATE_CHR_DRUNK	((rate_t)50)	/* 酔っている時 */

/* モンスターの持っているアイテムの最大数 */
#define	MNSTR_ITEM_N_MAX_N	3

/***************************************************************
* キャラクタの種類
***************************************************************/

typedef enum {
	CHR_KIND_NULL,
	CHR_KIND_MBR,	/* メンバー(PC) */
	CHR_KIND_MNSTR,	/* モンスター */
} chr_kind_t;

/***************************************************************
* 画面に表示する文字(顔)
***************************************************************/

typedef struct {
	char	mjr, mnr;
	char	mjr_org, mnr_org;
} chr_face_t;

/***************************************************************
* 種族
***************************************************************/

typedef enum {
	MAIN_RACE_HUMAN,
	MAIN_RACE_HALF_ELF,
	MAIN_RACE_ELF,
	MAIN_RACE_DWARF,
	MAIN_RACE_VIVID,
	MAIN_RACE_MAX_N,
} main_race_t;

typedef enum {
	SUB_RACE_NULL,
	SUB_RACE_CAT,
	SUB_RACE_DOG,
	SUB_RACE_MOUSE,
	SUB_RACE_RABBIT,
	SUB_RACE_MONKEY,
	SUB_RACE_PIG,
	SUB_RACE_BIRD,
	SUB_RACE_LIZARD,
	SUB_RACE_MAX_N,
} sub_race_t;

typedef struct {
	main_race_t	main;
	sub_race_t	sub;
	char	name[RACE_NAME_MAX_BYTE + 1];
} race_t;

/***************************************************************
* 性別
***************************************************************/

typedef enum {
	SEX_NULL,

	/* 女 */
	FEMALE,

	/* 男 */
	MALE,
} sex_t;

typedef struct {
	sex_t	cur, org;
} sex_dat_t;

/***************************************************************
* キャラクタの向き
***************************************************************/

typedef enum {
	CHR_DIR_IDX_S,
	CHR_DIR_IDX_W,
	CHR_DIR_IDX_E,
	CHR_DIR_IDX_N,
	CHR_DIR_IDX_MAX_N,
	CHR_DIR_IDX_NULL = CHR_DIR_IDX_S,
} chr_dir_idx_t;

/***************************************************************
* 移動速度
***************************************************************/

typedef struct {
	rate_t	rate, rate_org;
	long	n;
} move_speed_t;

/***************************************************************
* 歩き方の種類
***************************************************************/

typedef enum {
	MOVE_KIND_NULL,
	MOVE_KIND_STOP,	/* 制止 */
	MOVE_KIND_STD,	/* 普通(STanDard) */
	MOVE_KIND_STAGGER,	/* フラつき */
	MOVE_KIND_WANDER,	/* 徘徊 */
	MOVE_KIND_TOWNER,	/* 街の住民 */
	MOVE_KIND_MAX_N,
} move_kind_t;

/***************************************************************
* 歩き方のデータ
***************************************************************/

typedef struct {
	/* 歩き方 */
	move_kind_t	kind;

	/* 比率 */
	ratio_t	ratio;
} move_ls_t;

/* 歩き方データの種類 */

typedef enum {
	/* メンバーを発見した後 */
	MOVE_LS_KIND_FIND,

	/* メンバーを発見する前 */
	MOVE_LS_KIND_NOT_FIND,

	MOVE_LS_KIND_MAX_N,
} move_ls_kind_t;

typedef struct {
	move_speed_t	speed;
	move_kind_t	force_kind;
	move_ls_t	ls[MOVE_LS_KIND_MAX_N][MOVE_LS_MAX_N];
} move_t;

/***************************************************************
* 能力値
***************************************************************/

/* 経験値 */
typedef struct {
	long	n, max;
} abl_exp_t;

/* レベル */
typedef struct {
	long	n, max, add;
} abl_lev_t;

/* 値 */
typedef struct {
	long	n, max;
} abl_val_t;

/* 能力値 */
typedef struct {
	abl_exp_t	exp[ABL_SKILL_MAX_N];
	abl_lev_t	lev[ABL_SKILL_MAX_N];
	abl_val_t	hp, mp;
} abl_t;

/* レベルから経験値を計算する時のデータ */
typedef struct {
	rate_t	mul_lev;
	long	add_lev;
} lev_to_exp_t;

/* レベルから値を計算する時のデータ */
typedef struct {
	rate_t	mul_lev;
	long	add_lev;
} lev_to_val_t;

/***************************************************************
* エフェクト用のワーク
***************************************************************/

typedef struct fx_data {
	/* 攻撃力 */
	rate_t	wpn_hit, wpn_crtcl, wpn_dam;
	/* 防御力 */
	rate_t	armor_def, armor_crtcl, armor_ac;
	/* 状態抵抗 */
	flg_stat_t	resi_stat;

	/* 回復効果 */
	cure_t	cure_hp, cure_mp;

	/* 赤外線視力 */
	long	infra_vision;
	/* 空腹度 */
	stomach_t	stomach;
	/* 酔いの率 */
	rate_t	drunk_rate;
	/* ニコチン依存度 */
	nicotine_t	nicotine;
	/* 仲間を信頼するまでのターン数 */
	long	friend_turn;
	/* 祝福の率 */
	rate_t	bless;
} fx_data_t;

/***************************************************************
* 装備による修正
***************************************************************/

typedef struct {
	/* 顔 */
	char	face_mjr, face_mnr;
	/* 性別 */
	sex_t	sex;

	/* 攻撃力 */
	rate_t	wpn_hit, wpn_crtcl, wpn_dam;
	/* 防御力 */
	rate_t	armor_def, armor_crtcl, armor_ac;

	/* レベル */
	long	add_lev[ABL_SKILL_MAX_N];
	/* 抵抗力 */
	long	add_resi_n[RESI_KIND_MAX_N];
	/* 状態抵抗 */
	flg_stat_t	resi_stat;

	/* 回復 */
	cure_t	cure_hp, cure_mp;

	/* 移動スピード */
	long	add_move_speed;
	/* 空腹 */
	long	stomach_digest_n;
	/* テレポート */
	long	teleport_n, teleport_party_n;
	/* 祝福 */
	rate_t	bless;
} modifier_t;

#define	WPN_ALL_0	(rate_t)0, (rate_t)0, (rate_t)0
#define	ARMOR_ALL_0	(rate_t)0, (rate_t)0, (rate_t)0
#define	ADD_LEV_ALL_0	\
	{\
		0, 0,\
		0, 0, 0, 0, 0, 0,\
		0, 0, 0, 0,\
		0, 0, 0, 0,\
		0, 0, 0, 0,\
	},
#define	ADD_RESI_N_ALL_0	\
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, },

/***************************************************************
* デフォルトのクラス(職業)
***************************************************************/

typedef enum {
	CLASS_DFLT_NULL,
	CLASS_DFLT_FIGHTER,
	CLASS_DFLT_MONK,
	CLASS_DFLT_HUNTER,
	CLASS_DFLT_THIEF,
	CLASS_DFLT_WIZARD,
	CLASS_DFLT_SUMMONER,
	CLASS_DFLT_PRIEST,
	CLASS_DFLT_SHAMAN,
	CLASS_DFLT_BARD,
	CLASS_DFLT_NINJA,
	CLASS_DFLT_BISHOP,
} class_dflt_t;

/***************************************************************
* クラス(職業)
***************************************************************/

typedef struct {
	/* 名前 */
	n_msg_t	n_name;
	char	name[CLASS_NAME_MAX_BYTE + 1];

	/* デフォルトのクラス */
	class_dflt_t	dflt;

	/* 経験値の配分 */
	rate_t	abl_rate[ABL_KIND_MAX_N];
	/* セットされているスキル */
	skill_kind_t	skill[SKILL_MAX_N];
} class_t;

/***************************************************************
* アクション
***************************************************************/

typedef enum {
	ACT_KIND_NULL,
	ACT_KIND_MNSTR_FIGHT,
	ACT_KIND_MNSTR_THROW,
	ACT_KIND_MNSTR_STEAL,
	ACT_KIND_MNSTR_TAIL,
	ACT_KIND_MBR_FIGHT,
	ACT_KIND_MBR_THROW,
	ACT_KIND_MBR_STEAL,
	ACT_KIND_MBR_TAIL,
	ACT_KIND_DOOR_OPEN,
	ACT_KIND_DOOR_CLOSE,
	ACT_KIND_DOOR_JAM,
	ACT_KIND_DOOR_DISARM,
	ACT_KIND_DOOR_BREAK,
	ACT_KIND_DOOR_PEEP,
	ACT_KIND_DOOR_CHK,
	ACT_KIND_TRAP_DISARM,
	ACT_KIND_TRAP_BREAK,
	ACT_KIND_TRAP_CHK,
	ACT_KIND_ITEM_PICK_UP,
	ACT_KIND_ITEM_OPEN,
	ACT_KIND_ITEM_DISARM,
	ACT_KIND_ITEM_BREAK,
	ACT_KIND_ITEM_CHK,
	ACT_KIND_ITEM_SEND,
	ACT_KIND_ITEM_DROP,
	ACT_KIND_ITEM_RECEIVE,
	ACT_KIND_EQUIP_SEL,
	ACT_KIND_EQUIP,
	ACT_KIND_TAKE_OFF,
	ACT_KIND_EQUIP_MBR,
	ACT_KIND_TAKE_OFF_MBR,
	ACT_KIND_POTION_QUAFF,
	ACT_KIND_POTION_FILL,
	ACT_KIND_SCROLL_READ,
	ACT_KIND_STICK_ZAP,
	ACT_KIND_LAMP_RUB,
	ACT_KIND_FOOD_EAT,
	ACT_KIND_TOBACCO_DISPOSE,
	ACT_KIND_SRCH,
	ACT_KIND_SPELL,

	/* パーティのアクション */
	ACT_KIND_SHOP,
	ACT_KIND_TELEPORT_PARTY,
	ACT_KIND_RECALL,
	ACT_KIND_MAX_N,
} act_kind_t;

typedef struct {
	/* 種類 */
	act_kind_t	kind;

	/* ワーク用ポインタ */
	void	*p, *p2;
	/* ワーク用変数 */
	long	n, n2;

	/* 表示文字列 */
	char	msg[ACT_MSG_MAX_BYTE + 1];

	act_kind_t	dflt_kind_mnstr;
	/* 表示文字列 */
	char	dflt_msg_mnstr[ACT_MSG_MAX_BYTE + 1];
} act_t;

/***************************************************************
* ターゲット
***************************************************************/

/* ターゲットの種類 */

typedef enum {
	TRGT_KIND_NULL,
	TRGT_KIND_MBR,
	TRGT_KIND_MNSTR,
	TRGT_KIND_MNSTR_NULL,	/* モンスターのいない所をマークしたとき */
	TRGT_KIND_ITEM,
	TRGT_KIND_DOOR,
	TRGT_KIND_TRAP,
	TRGT_KIND_QUEUE,
	TRGT_KIND_SQUARE,
	TRGT_KIND_POS,
	TRGT_KIND_AUTO,
	TRGT_KIND_MAX_N,
} trgt_kind_t;

/* 間合い */

typedef enum {
	/* 近く */
	DIST_NEAR,
	/* 中間 */
	DIST_MEDIUM,
	/* 遠く */
	DIST_FAR,
} dist_t;

/* 目標 */

typedef struct {
	/* 種類 */
	trgt_kind_t	kind;

	/* ポインタ */
	void	*p;
	long	n;

	/* ターゲットによっては修正が入る */
	long	x, y;
	/* 修正無しの本当の座標 */
	long	true_x, true_y;

	/* 間合い */
	dist_t	dist, dflt_dist_mnstr;
} trgt_t;

/***************************************************************
* メンバーの配置
***************************************************************/

typedef enum {
	POSITION_KIND_NULL,

	/* 前衛 */
	POSITION_KIND_FORWARD,
	/* 中衛 */
	POSITION_KIND_HALFBACK,
	/* 後衛 */
	POSITION_KIND_BACK,

	POSITION_KIND_MAX_N,
} position_kind_t;

/***************************************************************
* 態度、反応
***************************************************************/

typedef enum {
	/* 仲間 */
	ATTITUDE_MATE,
	/* 友好的 */
	ATTITUDE_FRIENDLY,
	/* 中立 */
	ATTITUDE_NEUTRAL,
	/* 敵対的 */
	ATTITUDE_ENEMY,

	ATTITUDE_MAX_N,
} attitude_t;

/***************************************************************
* キャラクタの大型化
***************************************************************/

/* NULL, NORMAL, PERFECT 以外は順番を並べ変えてもOK */

typedef enum {
	/* 大型化無し */
	HYPER_BOSS_NULL,
	/* 通常時 */
	HYPER_BOSS_NORMAL,
	/* 左上の大型化 */
	HYPER_BOSS_NW,
	/* 右下の大型化 */
	HYPER_BOSS_SE,
	/* 右上の大型化 */
	HYPER_BOSS_NE,
	/* 左下の大型化 */
	HYPER_BOSS_SW,
	/* 大型化完了 */
	HYPER_BOSS_PERFECT,
} hyper_boss_t;

/***************************************************************
* ワーク
***************************************************************/

typedef struct {
	/* フラグ */
	flg_work_t	flg;

	/* キャラクタの大型化状態 */
	hyper_boss_t	hyper_boss;
	/* キャラクタの大型化フラグ (GUI) */
	bool_t	flg_hyper_boss;

	/* この PC を捕まえているキャラの人数 */
	long	caught;

	/* 捕まって移動できないPC */
	struct chr_t	*catch_chr;

	/* 数珠つなぎの1つ前 */
	struct chr_t	*link_chr;

	/* ランダム・テレポートの起きるカウント */
	long	teleport_n, teleport_party_n;

	/* 「望み」の呪文が使えるか? */
	bool_t	flg_can_wish;

	/* 関係している依頼 */
	struct request_t	*request;

	/* 街の住人の移動速度のベクトル */
	long	towner_dx, towner_dy;
	/* 現在入っている店のドア */
	door_t	*enter_door;

	/* 召喚獣の送還ターン */
	long	dismissal_turn;

	/* モンスターがメンバーに生命力吸収を使ったか? */
	bool_t	flg_used_energy_drain;

	/* 波打つ数字の VFX を一斉描画する際のダメージ等 */
	long	sync_vfx_num;
	long	sync_vfx_x, sync_vfx_y;
} chr_work_t;

/***************************************************************
* モンスターの落すアイテム
***************************************************************/

typedef struct {
	/* 種類 */
	item_kind_t	kind;
	/* 数 */
	long	n;
	/* 率 */
	rate_t	rate;

	/* パラメータ */
	long	k1, k2, k3;
} mnstr_item_n_t;

/***************************************************************
* モンスターのデータ・テーブル
***************************************************************/

typedef struct {
	/* モンスターの種類 */
	mnstr_kind_t	mnstr_kind;

	/* モンスターの名前 */
	char	*name;
	n_msg_t	name_n;

	/* 縦横のサイズ */
	long	dx, dy;

	/* 群の平均の数 */
	long	group;

	/* 画面に表示する顔 */
	char	face_mjr, face_mnr;

	/* ボス・フラグ */
	bool_t	flg_boss;

	/* 自動的に計算される経験値の修正値 */
	rate_t	exp;

	/* 倒したときに落すゴールドの割合 */
	rate_t	gold_rate;

	/* 倒したときに落すランダム・アイテムの数 */
	long	item_max_n;

	/* 倒したときに落す骨(アイテム)の数 */
	long	bone_ave_n;

	/* 倒したときに落す固定アイテム */
	mnstr_item_n_t	item_n[MNSTR_ITEM_N_MAX_N + 1];

	/* 思考ルーチン */
	void	(*func)( struct chr_t *p );

	/* 態度、反応 */
	attitude_t	attitude;

	/* 能力値 */
	rate_t	abl_lev_rate[ABL_KIND_MAX_N];

	/* 抵抗力 */
	rate_t	resi[RESI_KIND_MAX_N];

	/* 攻撃方法 */
	attack_t	attack[CHR_ATACK_MAX_N + 1];

	/* 防御の上手さ、クリティカルの耐性、アーマ・クラス */
	rate_t	def, armor_crtcl, ac;

	/* 移動 */
	move_t	move;

	/* その他特殊動作のフラグ */
	flg_chr_t	flg_chr;

	/* デフォルトのステータス */
	flg_stat_t	stat;

	/* 状態異常の抵抗フラグ */
	flg_stat_t	resi_stat;
} mnstr_tab_t;

/***************************************************************
* キャラクタ(PC,NPC,モンスター)
***************************************************************/

typedef struct chr_t {
	/* リストの前後 */
	struct chr_t	*prev, *next;
	/* マップ奥からソートしたキャラクタのリスト */
	struct chr_t	*sort_chr_next;

	/* キャラの種類 */
	chr_kind_t	kind;
	char	name[CHR_NAME_MAX_BYTE + 1];

	/* コピー防止 ID */
	long	id1, id2;

	/* メンバーの並び順 */
	long	mbr_n, ls_mbr_n;
	/* メンバーの配置 */
	position_kind_t	position_kind;

	/* 顔 */
	chr_face_t	face;
	/* 種族 */
	race_t	race;
	/* 性別 */
	sex_dat_t	sex;

	/* 位置 */
	long	x, y;
	/* 以前の位置 */
	long	pre_x, pre_y;
	/* 以前のターンの位置 */
	long	pre_turn_x, pre_turn_y;
	/* 以前の描画位置 */
	long	pre_draw_x, pre_draw_y;
	/* サイズ */
	long	dx, dy;
	/* 向き */
	chr_dir_idx_t	chr_dir_idx;
	/* 移動の仕方 */
	move_t	move;

	/* 所持金 */
	gold_t	gold;
	/* 行った事のある階の地上、地下 */
	long	dun_max_lev_floor, dun_max_lev_base;

	/* ターゲット */
	trgt_t	trgt;
	/* アクション */
	act_t	act, pre_act;

	/* フラグ */
	flg_chr_t	flg_chr;
	flg_map_t	flg_map;

	/* 態度、反応 */
	attitude_t	attitude;
	/* 飼主 */
	struct chr_t	*owner;

	/* ステータス(状態) */
	flg_stat_t	stat;
	/* 能力値 */
	abl_t	abl;
	/* 現在のクラス */
	long	class_n;
	/* 抵抗値 */
	resi_t	resi[RESI_KIND_MAX_N];
	/* 防御力(モンスターの時のみ) */
	long	add_def, add_crtcl, add_ac;

	/* 現在掛かっている魔法などのエフェクト */
	fx_t	fx;
	/* エフェクトで使うワーク */
	fx_data_t	fx_data;
	/* 装備の特殊効果 */
	modifier_t	modifier_equip;
	/* エフェクトの特殊効果 */
	modifier_t	modifier_fx;

	/* 寄付した金額 */
	gold_t	contribution;

	/* モンスターの種類 */
	mnstr_kind_t	mnstr_kind, mnstr_kind_org;
	/* モンスター・データ・テーブル */
	mnstr_tab_t	*mnstr_tab, *mnstr_tab_org;

	/* ペットかどうか */
	bool_t	flg_pet;

	/* その他ワーク */
	chr_work_t	work;

	/* xlnl 画像ファイル名 */
	char	graph_name[FILE_NAME_MAX_LEN + 1];
} chr_t;

#endif	/* CHR_H */
