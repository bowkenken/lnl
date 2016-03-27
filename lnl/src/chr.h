/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ����ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�����
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�����ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ����Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: chr.h,v 1.130 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	CHR_H
#define	CHR_H

/***************************************************************
* ����饯��
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
* �и��ͤȥ�٥�
***************************************************************/

#define	ABL_SKILL_MAX_N	(ABL_KIND_MAX_N + SKILL_KIND_MAX_N)

/* ��٥�κǹ��� */
#define	ABL_MAX_LEV	9999

/* �и��ͤκ����� */
#define	EXP_MAX	99999999
#define	NEED_EXP_MAX	(EXP_MAX + 1)

/* ����饯���Υ�٥�ȡ��µܤΥ�٥�Ȥ���Ψ */
#define	RATE_LEV_PER_DUN_LEV	((rate_t)30)

/***************************************************************
* ̾���κ���ʸ����
***************************************************************/

/* ����饯�� */
#define	CHR_NAME_MAX_LEN	80
#define	CHR_NAME_MAX_BYTE	(CHR_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)
/* ���С� */
#define	MBR_NAME_MAX_LEN	16
#define	MBR_NAME_MAX_BYTE	(MBR_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)
/* ��󥹥��� */
#define	MNSTR_NAME_MAX_LEN	CHR_NAME_MAX_LEN
#define	MNSTR_NAME_MAX_BYTE	CHR_NAME_MAX_BYTE

/* �ݤ���碌��ޤ᤿��²̾ */
#define	RACE_STR_MAX_LEN	32
#define	RACE_STR_MAX_BYTE	(RACE_STR_MAX_LEN * CHAR_MAX_LEN_UTF_8)
/* ��²̾ */
#define	RACE_NAME_MAX_LEN	16
#define	RACE_NAME_MAX_BYTE	(RACE_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/***************************************************************
* ����饯����ǽ��
***************************************************************/

#define	MOVE_LS_MAX_N	3	/* ����饯���ΰ�ư�μ���κ���� */

#define	ABL_RATE_MIN_N	((rate_t)0)	/* �и��ͤγ�꿶��κ����� */
#define	ABL_RATE_MAX_N	((rate_t)20)	/* �и��ͤγ�꿶��κǹ��� */

/***************************************************************
* ����饯���Υե饰
* ���֤��Ѥ�����ϥ����֡��ǡ����⽤������
***************************************************************/

typedef unsigned long	flg_chr_t;
#define	FLG_CHR_AUTO_FIGHT	(1 << 0)	/* Ũ�ˤ֤Ĥ��ä��鹶�⤹�� */
#define	FLG_CHR_AUTO_DOOR	(1 << 1)	/* ��ư�ǥɥ��򳫤��� */
#define	FLG_CHR_AVOID_TRAP	(1 << 2)	/* 櫤��򤱤� */
#define	FLG_CHR_AUTO_RELOAD	(1 << 3)	/* ���ư���佼 */
#define	FLG_CHR_AUTO_MARK_CONT	(1 << 4)	/* Ϣ³�Ǽ�ư�ޡ������� */
#define	FLG_CHR_NO_MARK_MNSTR	(1 << 8)	/* ��Ʈ�˻��ä��ʤ�(NPC��) */
#define	FLG_CHR_CAN_OPEN_DOOR	(1 << 9)	/* �ɥ��򳫤���� */
#define	FLG_CHR_CAN_BREAK_DOOR	(1 << 10)	/* �ɥ�������� */
#define	FLG_CHR_LIGHT	(1 << 11)	/* ���äƤ��� */
#define	FLG_CHR_DARK	(1 << 12)	/* �Ǥ����äƤ��� */
#define	FLG_CHR_MAGIC_PROTECT	(1 << 13)	/* ��ˡ����路�������ʤ� */
#define	FLG_CHR_HYPER	(1 << 14)	/* �緿������ */
#define	FLG_CHR_CAN_DEL	(1 << 20)	/*  */
#define	FLG_CHR_CAN_DISMISSAL	(1 << 21)	/* ���Խ���� */

/***************************************************************
* ����饯���Υ��ơ�����
* ���֤��Ѥ�����ϥ����֡��ǡ����⽤������
***************************************************************/

typedef unsigned long	flg_stat_t;
#define	FLG_STAT_NULL	0
#define	FLG_STAT_NOT_EXIST	(1 << 0)	/* ���� */
#define	FLG_STAT_DEAD	(1 << 1)	/* ��˴ */
#define	FLG_STAT_STONE	(1 << 2)	/* �в� */
#define	FLG_STAT_PARALYZE	(1 << 3)	/* ���� */
#define	FLG_STAT_POISON	(1 << 4)	/* �� */
#define	FLG_STAT_CONFUSION	(1 << 5)	/* ���� */
#define	FLG_STAT_BLIND	(1 << 6)	/* ���� */
#define	FLG_STAT_SLEEP	(1 << 7)	/* ̲�� */
#define	FLG_STAT_SILENCE	(1 << 8)	/* ���� */
#define	FLG_STAT_CAUGHT	(1 << 9)	/* ��« */
#define	FLG_STAT_FEAR	(1 << 10)	/* ���� */
#define	FLG_STAT_HALLUCINATION	(1 << 11)	/* ���� */
#define	FLG_STAT_CHARM	(1 << 12)	/* ̥λ */
#define	FLG_STAT_FLY	(1 << 13)	/* ��ͷ */
#define	FLG_STAT_HUNGRY	(1 << 14)	/* ��ʢ */
#define	FLG_STAT_STARVATION	(1 << 15)	/* ���� */
#define	FLG_STAT_FAINT	(1 << 16)	/* ��ޤ� */
#define	FLG_STAT_DRUNK	(1 << 17)	/* �줤 */
#define	FLG_STAT_VANISH	(1 << 18)	/* Ʃ���� */
#define	FLG_STAT_IRON_BODY	(1 << 19)	/* ��Ŵ�� */
#define	FLG_STAT_PASSWALL	(1 << 20)	/* ��ȴ�� */
#define	FLG_STAT_SENSE_INVISIBLE	(1 << 21)	/* �ԲĻ봶�� */

#define STAT_MAX_N	22

/***************************************************************
* ����饯���Υ�����ե饰
* ���֤��Ѥ�����ϥ����֡��ǡ����⽤������
***************************************************************/

typedef unsigned long	flg_work_t;

/* ��󥹥��������С���ȯ�����Ƥ��� */
#define	FLG_WORK_FIND_MBR	(1 << 0)

/* ��󥹥���������˥����ƥ�����Ǥ��� */
#define	FLG_WORK_STEAL_END	(1 << 1)

/* 2x2 �������ʾ�Υ�󥹥����������� 1 �٤�������̵���ͤˤ���ե饰 */
#define	FLG_WORK_BLAST_END	(1 << 2)

/***************************************************************
* ���饹
***************************************************************/

/* ����� */
#define	CLASS_MAX_N	99

/* ̾���κ���ʸ���� */
#define	CLASS_NAME_MAX_LEN	20
#define	CLASS_NAME_MAX_BYTE	\
	(CLASS_NAME_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/***************************************************************
* ���󥫡�
***************************************************************/

#define	SQUARE_WIDTH	3	/* �� */
#define	SQUARE_HEIGHT	3	/* �⤵ */

/***************************************************************
* ����¾
***************************************************************/

/* ������������� */
#define	ROLL_BASE	10

/* ���������κ���ʸ���� */
#define	ACT_MSG_MAX_LEN	64
#define	ACT_MSG_MAX_BYTE	(ACT_MSG_MAX_LEN * CHAR_MAX_LEN_UTF_8)

/* �դ�Ĥ�Ψ */
#define	STAGGER_RATE_CHR_CONFUSION	((rate_t)70)	/* ����� */
#define	STAGGER_RATE_CHR_BLIND	((rate_t)30)	/* �ܤ������ʤ��� */
#define	STAGGER_RATE_CHR_DRUNK	((rate_t)50)	/* ��äƤ���� */

/* ��󥹥����λ��äƤ��륢���ƥ�κ���� */
#define	MNSTR_ITEM_N_MAX_N	3

/***************************************************************
* ����饯���μ���
***************************************************************/

typedef enum {
	CHR_KIND_NULL,
	CHR_KIND_MBR,	/* ���С�(PC) */
	CHR_KIND_MNSTR,	/* ��󥹥��� */
} chr_kind_t;

/***************************************************************
* ���̤�ɽ������ʸ��(��)
***************************************************************/

typedef struct {
	char	mjr, mnr;
	char	mjr_org, mnr_org;
} chr_face_t;

/***************************************************************
* ��²
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
* ����
***************************************************************/

typedef enum {
	SEX_NULL,

	/* �� */
	FEMALE,

	/* �� */
	MALE,
} sex_t;

typedef struct {
	sex_t	cur, org;
} sex_dat_t;

/***************************************************************
* ����饯���θ���
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
* ��ư®��
***************************************************************/

typedef struct {
	rate_t	rate, rate_org;
	long	n;
} move_speed_t;

/***************************************************************
* �⤭���μ���
***************************************************************/

typedef enum {
	MOVE_KIND_NULL,
	MOVE_KIND_STOP,	/* ���� */
	MOVE_KIND_STD,	/* ����(STanDard) */
	MOVE_KIND_STAGGER,	/* �ե�Ĥ� */
	MOVE_KIND_WANDER,	/* ���� */
	MOVE_KIND_TOWNER,	/* ���ν�̱ */
	MOVE_KIND_MAX_N,
} move_kind_t;

/***************************************************************
* �⤭���Υǡ���
***************************************************************/

typedef struct {
	/* �⤭�� */
	move_kind_t	kind;

	/* ��Ψ */
	ratio_t	ratio;
} move_ls_t;

/* �⤭���ǡ����μ��� */

typedef enum {
	/* ���С���ȯ�������� */
	MOVE_LS_KIND_FIND,

	/* ���С���ȯ�������� */
	MOVE_LS_KIND_NOT_FIND,

	MOVE_LS_KIND_MAX_N,
} move_ls_kind_t;

typedef struct {
	move_speed_t	speed;
	move_kind_t	force_kind;
	move_ls_t	ls[MOVE_LS_KIND_MAX_N][MOVE_LS_MAX_N];
} move_t;

/***************************************************************
* ǽ����
***************************************************************/

/* �и��� */
typedef struct {
	long	n, max;
} abl_exp_t;

/* ��٥� */
typedef struct {
	long	n, max, add;
} abl_lev_t;

/* �� */
typedef struct {
	long	n, max;
} abl_val_t;

/* ǽ���� */
typedef struct {
	abl_exp_t	exp[ABL_SKILL_MAX_N];
	abl_lev_t	lev[ABL_SKILL_MAX_N];
	abl_val_t	hp, mp;
} abl_t;

/* ��٥뤫��и��ͤ�׻�������Υǡ��� */
typedef struct {
	rate_t	mul_lev;
	long	add_lev;
} lev_to_exp_t;

/* ��٥뤫���ͤ�׻�������Υǡ��� */
typedef struct {
	rate_t	mul_lev;
	long	add_lev;
} lev_to_val_t;

/***************************************************************
* ���ե������ѤΥ��
***************************************************************/

typedef struct fx_data {
	/* ������ */
	rate_t	wpn_hit, wpn_crtcl, wpn_dam;
	/* �ɸ��� */
	rate_t	armor_def, armor_crtcl, armor_ac;
	/* ������ */
	flg_stat_t	resi_stat;

	/* �������� */
	cure_t	cure_hp, cure_mp;

	/* �ֳ������� */
	long	infra_vision;
	/* ��ʢ�� */
	stomach_t	stomach;
	/* �줤��Ψ */
	rate_t	drunk_rate;
	/* �˥������¸�� */
	nicotine_t	nicotine;
	/* ��֤��ꤹ��ޤǤΥ������ */
	long	friend_turn;
	/* ��ʡ��Ψ */
	rate_t	bless;
} fx_data_t;

/***************************************************************
* �����ˤ�뽤��
***************************************************************/

typedef struct {
	/* �� */
	char	face_mjr, face_mnr;
	/* ���� */
	sex_t	sex;

	/* ������ */
	rate_t	wpn_hit, wpn_crtcl, wpn_dam;
	/* �ɸ��� */
	rate_t	armor_def, armor_crtcl, armor_ac;

	/* ��٥� */
	long	add_lev[ABL_SKILL_MAX_N];
	/* ���� */
	long	add_resi_n[RESI_KIND_MAX_N];
	/* ������ */
	flg_stat_t	resi_stat;

	/* ���� */
	cure_t	cure_hp, cure_mp;

	/* ��ư���ԡ��� */
	long	add_move_speed;
	/* ��ʢ */
	long	stomach_digest_n;
	/* �ƥ�ݡ��� */
	long	teleport_n, teleport_party_n;
	/* ��ʡ */
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
* �ǥե���ȤΥ��饹(����)
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
* ���饹(����)
***************************************************************/

typedef struct {
	/* ̾�� */
	n_msg_t	n_name;
	char	name[CLASS_NAME_MAX_BYTE + 1];

	/* �ǥե���ȤΥ��饹 */
	class_dflt_t	dflt;

	/* �и��ͤ���ʬ */
	rate_t	abl_rate[ABL_KIND_MAX_N];
	/* ���åȤ���Ƥ��륹���� */
	skill_kind_t	skill[SKILL_MAX_N];
} class_t;

/***************************************************************
* ���������
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

	/* �ѡ��ƥ��Υ�������� */
	ACT_KIND_SHOP,
	ACT_KIND_TELEPORT_PARTY,
	ACT_KIND_RECALL,
	ACT_KIND_MAX_N,
} act_kind_t;

typedef struct {
	/* ���� */
	act_kind_t	kind;

	/* ����ѥݥ��� */
	void	*p, *p2;
	/* ������ѿ� */
	long	n, n2;

	/* ɽ��ʸ���� */
	char	msg[ACT_MSG_MAX_BYTE + 1];

	act_kind_t	dflt_kind_mnstr;
	/* ɽ��ʸ���� */
	char	dflt_msg_mnstr[ACT_MSG_MAX_BYTE + 1];
} act_t;

/***************************************************************
* �������å�
***************************************************************/

/* �������åȤμ��� */

typedef enum {
	TRGT_KIND_NULL,
	TRGT_KIND_MBR,
	TRGT_KIND_MNSTR,
	TRGT_KIND_MNSTR_NULL,	/* ��󥹥����Τ��ʤ����ޡ��������Ȥ� */
	TRGT_KIND_ITEM,
	TRGT_KIND_DOOR,
	TRGT_KIND_TRAP,
	TRGT_KIND_QUEUE,
	TRGT_KIND_SQUARE,
	TRGT_KIND_POS,
	TRGT_KIND_AUTO,
	TRGT_KIND_MAX_N,
} trgt_kind_t;

/* �ֹ礤 */

typedef enum {
	/* �᤯ */
	DIST_NEAR,
	/* ��� */
	DIST_MEDIUM,
	/* �� */
	DIST_FAR,
} dist_t;

/* ��ɸ */

typedef struct {
	/* ���� */
	trgt_kind_t	kind;

	/* �ݥ��� */
	void	*p;
	long	n;

	/* �������åȤˤ�äƤϽ��������� */
	long	x, y;
	/* ����̵���������κ�ɸ */
	long	true_x, true_y;

	/* �ֹ礤 */
	dist_t	dist, dflt_dist_mnstr;
} trgt_t;

/***************************************************************
* ���С�������
***************************************************************/

typedef enum {
	POSITION_KIND_NULL,

	/* ���� */
	POSITION_KIND_FORWARD,
	/* ��� */
	POSITION_KIND_HALFBACK,
	/* ��� */
	POSITION_KIND_BACK,

	POSITION_KIND_MAX_N,
} position_kind_t;

/***************************************************************
* ���١�ȿ��
***************************************************************/

typedef enum {
	/* ��� */
	ATTITUDE_MATE,
	/* ͧ��Ū */
	ATTITUDE_FRIENDLY,
	/* ��Ω */
	ATTITUDE_NEUTRAL,
	/* Ũ��Ū */
	ATTITUDE_ENEMY,

	ATTITUDE_MAX_N,
} attitude_t;

/***************************************************************
* ����饯�����緿��
***************************************************************/

/* NULL, NORMAL, PERFECT �ʳ��Ͻ��֤��¤��Ѥ��Ƥ�OK */

typedef enum {
	/* �緿��̵�� */
	HYPER_BOSS_NULL,
	/* �̾�� */
	HYPER_BOSS_NORMAL,
	/* ������緿�� */
	HYPER_BOSS_NW,
	/* �������緿�� */
	HYPER_BOSS_SE,
	/* ������緿�� */
	HYPER_BOSS_NE,
	/* �������緿�� */
	HYPER_BOSS_SW,
	/* �緿����λ */
	HYPER_BOSS_PERFECT,
} hyper_boss_t;

/***************************************************************
* ���
***************************************************************/

typedef struct {
	/* �ե饰 */
	flg_work_t	flg;

	/* ����饯�����緿������ */
	hyper_boss_t	hyper_boss;
	/* ����饯�����緿���ե饰 (GUI) */
	bool_t	flg_hyper_boss;

	/* ���� PC ����ޤ��Ƥ��륭���οͿ� */
	long	caught;

	/* ��ޤäư�ư�Ǥ��ʤ�PC */
	struct chr_t	*catch_chr;

	/* ����Ĥʤ���1���� */
	struct chr_t	*link_chr;

	/* �����ࡦ�ƥ�ݡ��Ȥε����륫����� */
	long	teleport_n, teleport_party_n;

	/* ��˾�ߡפμ�ʸ���Ȥ��뤫? */
	bool_t	flg_can_wish;

	/* �ط����Ƥ������ */
	struct request_t	*request;

	/* ���ν��ͤΰ�ư®�٤Υ٥��ȥ� */
	long	towner_dx, towner_dy;
	/* �������äƤ���Ź�Υɥ� */
	door_t	*enter_door;

	/* �����ä����ԥ����� */
	long	dismissal_turn;

	/* ��󥹥��������С�����̿�ϵۼ���Ȥä���? */
	bool_t	flg_used_energy_drain;

	/* ���ǤĿ����� VFX ��������褹��ݤΥ��᡼���� */
	long	sync_vfx_num;
	long	sync_vfx_x, sync_vfx_y;
} chr_work_t;

/***************************************************************
* ��󥹥�����������ƥ�
***************************************************************/

typedef struct {
	/* ���� */
	item_kind_t	kind;
	/* �� */
	long	n;
	/* Ψ */
	rate_t	rate;

	/* �ѥ�᡼�� */
	long	k1, k2, k3;
} mnstr_item_n_t;

/***************************************************************
* ��󥹥����Υǡ������ơ��֥�
***************************************************************/

typedef struct {
	/* ��󥹥����μ��� */
	mnstr_kind_t	mnstr_kind;

	/* ��󥹥�����̾�� */
	char	*name;
	n_msg_t	name_n;

	/* �Ĳ��Υ����� */
	long	dx, dy;

	/* ����ʿ�Ѥο� */
	long	group;

	/* ���̤�ɽ������� */
	char	face_mjr, face_mnr;

	/* �ܥ����ե饰 */
	bool_t	flg_boss;

	/* ��ưŪ�˷׻������и��ͤν����� */
	rate_t	exp;

	/* �ݤ����Ȥ����������ɤγ�� */
	rate_t	gold_rate;

	/* �ݤ����Ȥ���������ࡦ�����ƥ�ο� */
	long	item_max_n;

	/* �ݤ����Ȥ������(�����ƥ�)�ο� */
	long	bone_ave_n;

	/* �ݤ����Ȥ�������ꥢ���ƥ� */
	mnstr_item_n_t	item_n[MNSTR_ITEM_N_MAX_N + 1];

	/* �׹ͥ롼���� */
	void	(*func)( struct chr_t *p );

	/* ���١�ȿ�� */
	attitude_t	attitude;

	/* ǽ���� */
	rate_t	abl_lev_rate[ABL_KIND_MAX_N];

	/* ���� */
	rate_t	resi[RESI_KIND_MAX_N];

	/* ������ˡ */
	attack_t	attack[CHR_ATACK_MAX_N + 1];

	/* �ɸ�ξ�ꤵ������ƥ�����������������ޡ����饹 */
	rate_t	def, armor_crtcl, ac;

	/* ��ư */
	move_t	move;

	/* ����¾�ü�ư��Υե饰 */
	flg_chr_t	flg_chr;

	/* �ǥե���ȤΥ��ơ����� */
	flg_stat_t	stat;

	/* ���ְ۾���񹳥ե饰 */
	flg_stat_t	resi_stat;
} mnstr_tab_t;

/***************************************************************
* ����饯��(PC,NPC,��󥹥���)
***************************************************************/

typedef struct chr_t {
	/* �ꥹ�Ȥ����� */
	struct chr_t	*prev, *next;
	/* �ޥåױ����饽���Ȥ�������饯���Υꥹ�� */
	struct chr_t	*sort_chr_next;

	/* �����μ��� */
	chr_kind_t	kind;
	char	name[CHR_NAME_MAX_BYTE + 1];

	/* ���ԡ��ɻ� ID */
	long	id1, id2;

	/* ���С����¤ӽ� */
	long	mbr_n, ls_mbr_n;
	/* ���С������� */
	position_kind_t	position_kind;

	/* �� */
	chr_face_t	face;
	/* ��² */
	race_t	race;
	/* ���� */
	sex_dat_t	sex;

	/* ���� */
	long	x, y;
	/* �����ΰ��� */
	long	pre_x, pre_y;
	/* �����Υ�����ΰ��� */
	long	pre_turn_x, pre_turn_y;
	/* ������������� */
	long	pre_draw_x, pre_draw_y;
	/* ������ */
	long	dx, dy;
	/* ���� */
	chr_dir_idx_t	chr_dir_idx;
	/* ��ư�λ��� */
	move_t	move;

	/* ����� */
	gold_t	gold;
	/* �Ԥä����Τ��볬���Ͼ塢�ϲ� */
	long	dun_max_lev_floor, dun_max_lev_base;

	/* �������å� */
	trgt_t	trgt;
	/* ��������� */
	act_t	act, pre_act;

	/* �ե饰 */
	flg_chr_t	flg_chr;
	flg_map_t	flg_map;

	/* ���١�ȿ�� */
	attitude_t	attitude;
	/* ���� */
	struct chr_t	*owner;

	/* ���ơ�����(����) */
	flg_stat_t	stat;
	/* ǽ���� */
	abl_t	abl;
	/* ���ߤΥ��饹 */
	long	class_n;
	/* ���� */
	resi_t	resi[RESI_KIND_MAX_N];
	/* �ɸ���(��󥹥����λ��Τ�) */
	long	add_def, add_crtcl, add_ac;

	/* ���߳ݤ��äƤ�����ˡ�ʤɤΥ��ե����� */
	fx_t	fx;
	/* ���ե����ȤǻȤ���� */
	fx_data_t	fx_data;
	/* �������ü���� */
	modifier_t	modifier_equip;
	/* ���ե����Ȥ��ü���� */
	modifier_t	modifier_fx;

	/* ���դ������ */
	gold_t	contribution;

	/* ��󥹥����μ��� */
	mnstr_kind_t	mnstr_kind, mnstr_kind_org;
	/* ��󥹥������ǡ������ơ��֥� */
	mnstr_tab_t	*mnstr_tab, *mnstr_tab_org;

	/* �ڥåȤ��ɤ��� */
	bool_t	flg_pet;

	/* ����¾��� */
	chr_work_t	work;

	/* xlnl �����ե�����̾ */
	char	graph_name[FILE_NAME_MAX_LEN + 1];
} chr_t;

#endif	/* CHR_H */
