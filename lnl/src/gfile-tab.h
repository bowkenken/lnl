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
* $Id: gfile-tab.h,v 1.43 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	GFILE_TAB_H
#define	GFILE_TAB_H

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
***************************************************************/

#include	"item-kind.h"
#include	"spell-kind.h"

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������󥫡��������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ���󥫡������������������� SQUARE_DIR_NORTH �ǡ����롣
***************************************************************/

square_dir_t	g_square_dir_trans_tab[] = {
	SQUARE_DIR_NORTH,
	SQUARE_DIR_EAST,
	SQUARE_DIR_SOUTH,
	SQUARE_DIR_WEST,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ����������饯���μ���������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����饯���μ�������������� CHR_KIND_NULL �ǡ����롣
***************************************************************/

chr_kind_t	g_chr_trans_tab[] = {
	CHR_KIND_NULL,
	CHR_KIND_MBR,	/* ���С�(PC) */
	CHR_KIND_MNSTR,	/* ��󥹥��� */

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������С������֤������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ���С������֤����������� POSITION_KIND_NULL �ǡ����롣
***************************************************************/

position_kind_t	g_position_kind_trans_tab[] = {
	POSITION_KIND_NULL,

	/* ���� */
	POSITION_KIND_FORWARD,
	/* ��� */
	POSITION_KIND_HALFBACK,
	/* ��� */
	POSITION_KIND_BACK,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������²�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ���²������������ MAIN_RACE_HUMAN �ǡ����롣
***************************************************************/

main_race_t	g_main_race_trans_tab[] = {
	MAIN_RACE_HUMAN,
	MAIN_RACE_HALF_ELF,
	MAIN_RACE_ELF,
	MAIN_RACE_DWARF,
	MAIN_RACE_VIVID,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ����������²�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����²������������ SUB_RACE_NULL �ǡ����롣
***************************************************************/

sub_race_t	g_sub_race_trans_tab[] = {
	SUB_RACE_NULL,
	SUB_RACE_CAT,
	SUB_RACE_DOG,
	SUB_RACE_MOUSE,
	SUB_RACE_RABBIT,
	SUB_RACE_MONKEY,
	SUB_RACE_PIG,
	SUB_RACE_BIRD,
	SUB_RACE_LIZARD,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������̤������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ���̤����������� SEX_NULL �ǡ����롣
***************************************************************/

sex_t	g_sex_trans_tab[] = {
	SEX_NULL,

	/* �� */
	FEMALE,

	/* �� */
	MALE,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ������ǽ���ͤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ǽ���ͤ����������� ABL_KIND_MAX_N �ǡ����롣
***************************************************************/

abl_kind_t	g_abl_trans_tab[] = {
	ABL_KIND_HP,
	ABL_KIND_MP,
	ABL_KIND_DEX,
	ABL_KIND_STR,
	ABL_KIND_AGI,
	ABL_KIND_INT,
	ABL_KIND_WIS,
	ABL_KIND_CHA,
	ABL_KIND_FIG,
	ABL_KIND_MON,
	ABL_KIND_HUN,
	ABL_KIND_THI,
	ABL_KIND_MAG,
	ABL_KIND_SOR,
	ABL_KIND_ENC,
	ABL_KIND_SUM,
	ABL_KIND_PRI,
	ABL_KIND_SHA,
	ABL_KIND_BAR,
	ABL_KIND_NIN,
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_NULL),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_ATTACKER),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_BERSERKER),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DEFENDER),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_SENTINEL),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_ASSASSIN),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_AEGIS),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_SIEGE),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_PHALANX),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DOUBLE_ATTACK),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_COMBO),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RAPID_SHOOT),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_COUNTER),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_TWO_SWORD_FENCING),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DAM_KNOC),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DAM_SLAS),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DAM_STIN),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DAM_HEAT),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DAM_COLD),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DAM_MIND),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DAM_ACID),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DAM_ELEC),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_DAM_POIS),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RESI_KNOC),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RESI_SLAS),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RESI_STIN),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RESI_HEAT),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RESI_COLD),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RESI_MIND),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RESI_ACID),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RESI_ELEC),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RESI_POIS),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_DEAD),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_STONE),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_PARALYZE),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_POISON),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_CONFUSION),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_BLIND),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_SLEEP),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_SILENCE),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_CAUGHT),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_FEAR),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_HALLUCINATION),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_CHARM),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_FLY),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_HUNGRY),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_STARVATION),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_FAINT),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_DRUNK),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_VANISH),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_IRON_BODY),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_PASSWALL),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_STAT_SENSE_INVISIBLE),
	(abl_kind_t)(ABL_KIND_MAX_N + SKILL_KIND_RUN_AWAY),

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �������⤭���������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �⤭�������������� MOVE_KIND_NULL �ǡ����롣
***************************************************************/

move_kind_t	g_move_trans_tab[] = {
	MOVE_KIND_NULL,
	MOVE_KIND_STOP,	/* ���� */
	MOVE_KIND_STD,	/* ����(STanDard) */
	MOVE_KIND_STAGGER,	/* �ե�Ĥ� */
	MOVE_KIND_WANDER,	/* ���� */
	MOVE_KIND_TOWNER,	/* ���ν�̱ */

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �������������������� ACT_KIND_NULL �ǡ����롣
***************************************************************/

act_kind_t	g_act_trans_tab[] = {
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
	ACT_KIND_FOOD_EAT,
	ACT_KIND_TOBACCO_DISPOSE,
	ACT_KIND_SRCH,
	ACT_KIND_SPELL,

	/* �ѡ��ƥ��Υ�������� */
	ACT_KIND_SHOP,
	ACT_KIND_RECALL,

	/* �ɲ� */
	ACT_KIND_TELEPORT_PARTY,
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �������������åȤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �������åȤ����������� TRGT_KIND_NULL �ǡ����롣
***************************************************************/

trgt_kind_t	g_trgt_trans_tab[] = {
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

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������ܤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����������� DIST_NEAR �ǡ����롣
***************************************************************/

dist_t	g_dist_trans_tab[] = {
	DIST_NEAR,	/* �᤯ */
	DIST_MEDIUM,	/* ��� */
	DIST_FAR,	/* �� */

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������ܤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����������� AUTO_MARK_TRGT_CLEAR �ǡ����롣
***************************************************************/

auto_mark_trgt_t	g_am_trgt_trans_tab[] = {
	AUTO_MARK_TRGT_MNSTR,
	AUTO_MARK_TRGT_ITEM,
	AUTO_MARK_TRGT_DOOR,
	AUTO_MARK_TRGT_TRAP,
	AUTO_MARK_TRGT_MBR,
	AUTO_MARK_TRGT_UNCHANGE,
	AUTO_MARK_TRGT_CLEAR,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������ܤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����������� AUTO_MARK_DIST_NEAR �ǡ����롣
***************************************************************/

auto_mark_dist_t	g_am_dist_trans_tab[] = {
	AUTO_MARK_DIST_NEAR,
	AUTO_MARK_DIST_MEDIUM,
	AUTO_MARK_DIST_FAR,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������ܤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����������� AUTO_MARK_ACT_FIGHT �ǡ����롣
***************************************************************/

auto_mark_act_t	g_am_act_trans_tab[] = {
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

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������ܤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����������� AUTO_MARK_COND_NEAREST �ǡ����롣
***************************************************************/

auto_mark_cond_t	g_am_cond_trans_tab[] = {
	/* ��äȤ�ᤤʪ */
	AUTO_MARK_COND_NEAREST,

	/* �Ф餱�� */
	AUTO_MARK_COND_DISPERSE,

	/* ����Ƥ�����С� */
	AUTO_MARK_COND_STAGGER,

	/* Ʊ��ʪ����äƤ��� */
	AUTO_MARK_COND_OWN,

	/* 1 �� HP �ξ��ʤ� */
	AUTO_MARK_COND_HP_MIN,

	/* 1 �� HP ��¿�� */
	AUTO_MARK_COND_HP_MAX,

	/* 1 �� MP �ξ��ʤ� */
	AUTO_MARK_COND_MP_MIN,

	/* 1 �� MP ��¿�� */
	AUTO_MARK_COND_MP_MAX,

	/* ���̺� */
	AUTO_MARK_COND_IDENTIFIED,

	/* ̤���� */
	AUTO_MARK_COND_UN_IDENTIFIED,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������ܤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����������� DFLT_AUTO_MARK_NULL �ǡ����롣
***************************************************************/

dflt_auto_mark_t	g_am_dflt_trans_tab[] = {
	DFLT_AUTO_MARK_NULL,

	/* ��Ʈ(�ɲ�) */
	DFLT_AUTO_MARK_FIGHT,
	/* ��Ʈ(����) */
	DFLT_AUTO_MARK_FIGHT_PRIO,

	/* �ܶ���Ʈ(�ɲ�) */
	DFLT_AUTO_MARK_FIGHT_NO_THROW,
	/* �ܶ���Ʈ(����) */
	DFLT_AUTO_MARK_FIGHT_NO_THROW_PRIO,

	/* ������(�ɲ�) */
	DFLT_AUTO_MARK_FIGHT_ALL,
	/* ������(����) */
	DFLT_AUTO_MARK_FIGHT_ALL_PRIO,

	/* ���ƤΥ����ƥ� */
	DFLT_AUTO_MARK_ITEM_ALL,
	/* ���äƤ��륢���ƥ� */
	DFLT_AUTO_MARK_ITEM_OWN,

	/* ��� */
	DFLT_AUTO_MARK_RETREAT,
	/* ��� */
	DFLT_AUTO_MARK_CLEAR,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �������⤭���ǡ����μ���������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �⤭���ǡ����μ�������������� MOVE_LS_KIND_FIND �ǡ����롣
***************************************************************/

move_ls_kind_t	g_move_ls_trans_tab[] = {
	/* ���С���ȯ�������� */
	MOVE_LS_KIND_FIND,

	/* ���С���ȯ�������� */
	MOVE_LS_KIND_NOT_FIND,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������١�ȿ���������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ���١�ȿ�������������� ATTITUDE_MATE �ǡ����롣
***************************************************************/

attitude_t	g_attitude_trans_tab[] = {
	/* ��� */
	ATTITUDE_MATE,
	/* ͧ��Ū */
	ATTITUDE_FRIENDLY,
	/* ��Ω */
	ATTITUDE_NEUTRAL,
	/* Ũ��Ū */
	ATTITUDE_ENEMY,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �����������ƥ�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �����ƥ������������ ITEM_KIND_NULL �ǡ����롣
***************************************************************/

item_kind_t	g_item_trans_tab[] = {
	ITEM_KIND_NULL,
	ITEM_KIND_WPN,
	ITEM_KIND_ARMOR,
	ITEM_KIND_POTION,
	ITEM_KIND_SCROLL,
	ITEM_KIND_STICK,
	ITEM_KIND_ACCE,
	ITEM_KIND_INST,
	ITEM_KIND_ANTHOLOGY,
	ITEM_KIND_LIGHT,
	ITEM_KIND_SPIKE,
	ITEM_KIND_FOOD,
	ITEM_KIND_CHEST,
	ITEM_KIND_TOBACCO,
	ITEM_KIND_PIPE,
	ITEM_KIND_DISPOSAL,
	ITEM_KIND_RARE_GOODS,
	ITEM_KIND_COIN,
	ITEM_KIND_JUNK,
	ITEM_KIND_BONE,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �������������� WPN_KIND_NULL �ǡ����롣
***************************************************************/

wpn_kind_t	g_wpn_trans_tab[] = {
	WPN_KIND_NULL,
/* �ʥ��� */
	WPN_KIND_KNIFE,
	WPN_KIND_KRIS_KNIFE,
	WPN_KIND_MAIN_GAUCHE,
	WPN_KIND_SWORD_BREAKER,
	WPN_KIND_KATAR,
	WPN_KIND_JAMADHAR,
	WPN_KIND_KUKRI,
/* ���硼�ȡ������� */
	WPN_KIND_SHORT_SWORD,
	WPN_KIND_GLADIUS,
/* ��󥰡������� */
	WPN_KIND_LONG_SWORD,
	WPN_KIND_BROAD_SWORD,
	WPN_KIND_BASTARD_SWORD,
	WPN_KIND_CLAYMORE,
	WPN_KIND_GREAT_SWORD,
/* �����٥� */
	WPN_KIND_SABRE,
	WPN_KIND_SHAMSHIR,
	WPN_KIND_TALWAR,
	WPN_KIND_FALCHION,
	WPN_KIND_CUTLASS,
	WPN_KIND_SHOTEL,
	WPN_KIND_KATANA,
/* �쥤�ԥ� */
	WPN_KIND_RAPIER,
	WPN_KIND_ESTOC,
/* �ϥ�ɡ����å��� */
	WPN_KIND_HAND_AXE,
	WPN_KIND_FRANCISCA,
	WPN_KIND_BHUJ,
/* �Хȥ롦���å��� */
	WPN_KIND_BATTLE_AXE,
	WPN_KIND_BROAD_AXE,
	WPN_KIND_GREAT_AXE,
/* ���ԥ� */
	WPN_KIND_SPEAR,
	WPN_KIND_PILUM,
	WPN_KIND_PIKE,
	WPN_KIND_JAVELIN,
	WPN_KIND_TRIDENT,
/* ��� */
	WPN_KIND_LANCE,
	WPN_KIND_LANCE_OF_LONGINUS,
/* �ᥤ�� */
	WPN_KIND_QUARTER_STAFF,
/* �ե쥤�� */
	WPN_KIND_LIGHT_FLAIL,
	WPN_KIND_HEAVY_FLAIL,
	WPN_KIND_MORNINGSTAR,
/* �ᥤ�� */
	WPN_KIND_WOODEN_CLUB,
	WPN_KIND_LIGHT_MACE,
	WPN_KIND_HEAVY_MACE,
/* �ϥ�ޡ� */
	WPN_KIND_WAR_HAMMER,
	WPN_KIND_WAR_PICK,
	WPN_KIND_ZAGHNOL,
	WPN_KIND_BEC_DE_CORBIN,
/* ���쥤�� */
	WPN_KIND_PARTIZAN,
	WPN_KIND_POLEAXE,
	WPN_KIND_GLAIVE,
	WPN_KIND_HALBERD,
	WPN_KIND_CHAUVE_SOURIS,
	WPN_KIND_CORSESCA,
	WPN_KIND_SCYTHE,
	WPN_KIND_FAUCHARD,
	WPN_KIND_GUISARME,
/* �ʥå��� */
	WPN_KIND_BRASS_KNUCKLE,
	WPN_KIND_BAGH_NAKH,
/* �� */
	WPN_KIND_SLING,
	WPN_KIND_SHORT_BOW,
	WPN_KIND_LONG_BOW,
	WPN_KIND_COMPOSITE_BOW,
	WPN_KIND_LIGHT_CROSS_BOW,
	WPN_KIND_HEAVY_CROSS_BOW,
	WPN_KIND_BLOW_GUN,
/* �� */
	WPN_KIND_STONE,
	WPN_KIND_BULLET,
	WPN_KIND_ARW,
	WPN_KIND_BOLT,
	WPN_KIND_NEEDLE,
/* ������ */
	WPN_KIND_DAGGER,
	WPN_KIND_DARTS,
	WPN_KIND_SHURIKEN,
	WPN_KIND_BOOMERANG,

/* �ɲ� */

/* ��󥰡�������(�����ƥ��ե�����) */
	WPN_KIND_EXCALIBUR,
/* �ᥤ�� */
	WPN_KIND_NUNCHAKUS,
/* �����٥� */
	WPN_KIND_WAKIZASHI,
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �������ݤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �ݤ����������� BOW_KIND_NULL �ǡ����롣
***************************************************************/

bow_kind_t	g_bow_trans_tab[] = {
	BOW_KIND_NULL,
	BOW_KIND_BOW,
	BOW_KIND_CROSS_BOW,
	BOW_KIND_SLING,
	BOW_KIND_BLOW_GUN,
	BOW_KIND_DAGGER,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �������ɶ�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �ɶ������������ ARMOR_KIND_NULL �ǡ����롣
***************************************************************/

armor_kind_t	g_armor_trans_tab[] = {
	ARMOR_KIND_NULL,
/* �� */
	ARMOR_KIND_BUCKLER_SHIELD,
	ARMOR_KIND_ROUND_SHIELD,
	ARMOR_KIND_KITE_SHIELD,
	ARMOR_KIND_HEATER_SHIELD,
/* Ƭ������ */
	ARMOR_KIND_LEATHER_CAP,
	ARMOR_KIND_METAL_CAP,
	ARMOR_KIND_SALLET,
	ARMOR_KIND_CLOSE_HELMET,
	ARMOR_KIND_SILVER_CROWN,
	ARMOR_KIND_GOLDEN_CROWN,
	ARMOR_KIND_JEWELED_CROWN,
/* ƹ�Τ����� */
	ARMOR_KIND_ROBE,
	ARMOR_KIND_SOFT_LEATHER_ARMOR,
	ARMOR_KIND_HARD_LEATHER_ARMOR,
	ARMOR_KIND_RING_MAIL,
	ARMOR_KIND_SCALE_MAIL,
	ARMOR_KIND_LAMELLAR_ARMOR,
	ARMOR_KIND_CHAIN_MAIL,
	ARMOR_KIND_PLATE_ARMOR,
/* �Ӥ����� */
	ARMOR_KIND_LEATHER_GLOVES,
	ARMOR_KIND_GAUNTLETS,
/* ­������ */
	ARMOR_KIND_LEATHER_BOOTS,
	ARMOR_KIND_GREAVE,
/* ��������� */
	ARMOR_KIND_CLOAK,
/* ƹ�Τ�����(�����ƥ��ե�����) */
	ARMOR_KIND_RED_DRAGON_SCALE,
	ARMOR_KIND_BLUE_DRAGON_SCALE,
	ARMOR_KIND_YELLOW_DRAGON_SCALE,
	ARMOR_KIND_GREEN_DRAGON_SCALE,
	ARMOR_KIND_WHITE_DRAGON_SCALE,
	ARMOR_KIND_BLACK_DRAGON_SCALE,
	ARMOR_KIND_COPPER_DRAGON_SCALE,
	ARMOR_KIND_SILVER_DRAGON_SCALE,
	ARMOR_KIND_GOLD_DRAGON_SCALE,
	ARMOR_KIND_MITHRIL_CHAIN,
/* �Ӥ�����(�����ƥ��ե�����) */
	ARMOR_KIND_GAUNTLETS_OF_POW_UP_HIT,
	ARMOR_KIND_GAUNTLETS_OF_POW_DOWN_HIT,
	ARMOR_KIND_GAUNTLETS_OF_POW_UP_WPN_CRTCL,
	ARMOR_KIND_GAUNTLETS_OF_POW_DOWN_WPN_CRTCL,
	ARMOR_KIND_GAUNTLETS_OF_POW_UP_DAM,
	ARMOR_KIND_GAUNTLETS_OF_POW_DOWN_DAM,
/* ­������(�����ƥ��ե�����) */
	ARMOR_KIND_SPEED_BOOTS,
	ARMOR_KIND_SLOW_BOOTS,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ������ RAF ���������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* RAF �������������� WPN_RANDM_ART_KIND_NULL �ǡ����롣
***************************************************************/

wpn_randm_art_kind_t	g_wpn_randm_art_trans_tab[] = {
	WPN_RANDM_ART_KIND_BANE,
	WPN_RANDM_ART_KIND_KILLER,
	WPN_RANDM_ART_KIND_SLAYER,
	WPN_RANDM_ART_KIND_ADD_STAT,
	WPN_RANDM_ART_KIND_DRAIN,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ������ RAF �ɶ�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* RAF �ɶ������������ ARMOR_RANDM_ART_KIND_NULL �ǡ����롣
***************************************************************/

armor_randm_art_kind_t	g_armor_randm_art_trans_tab[] = {
	ARMOR_RANDM_ART_KIND_GUARD,
	ARMOR_RANDM_ART_KIND_BLOCK,
	ARMOR_RANDM_ART_KIND_PROTECT,
	ARMOR_RANDM_ART_KIND_RESI_STAT,
	ARMOR_RANDM_ART_KIND_HEALING,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �������������� POTION_KIND_NULL �ǡ����롣
***************************************************************/

potion_kind_t	g_potion_trans_tab[] = {
	POTION_KIND_NULL,
	POTION_KIND_WATER,
	POTION_KIND_MILK,
	POTION_KIND_RED_WINE,
	POTION_KIND_WHITE_WINE,
	POTION_KIND_ROSE_WINE,
	POTION_KIND_ALE,
	POTION_KIND_BRANDY,
	POTION_KIND_RUM,
	POTION_KIND_COFFE,
	POTION_KIND_ICE_COFFE,
	POTION_KIND_TEA,
	POTION_KIND_MILK_TEA,
	POTION_KIND_LEMON_TEA,
	POTION_KIND_ICE_TEA,
	POTION_KIND_ICE_MILK_TEA,
	POTION_KIND_ICE_LEMON_TEA,
	POTION_KIND_APPLE_JUICE,
	POTION_KIND_GRAPE_JUICE,
	POTION_KIND_ORANGE_JUICE,
	POTION_KIND_BLACK_BERRY_JUICE,
	POTION_KIND_CRAN_BERRY_JUICE,
	POTION_KIND_RASP_BERRY_JUICE,
	POTION_KIND_STRAW_BERRY_JUICE,
	POTION_KIND_OIL,
	POTION_KIND_STONE,
	POTION_KIND_PARALYZE,
	POTION_KIND_POISON,
	POTION_KIND_CONFUSION,
	POTION_KIND_BLIND,
	POTION_KIND_SLEEP,
	POTION_KIND_SILENCE,
	POTION_KIND_FEAR,
	POTION_KIND_HALLUCINATION,
	POTION_KIND_CHARM,
	POTION_KIND_FLY,
	POTION_KIND_VANISH,
	POTION_KIND_IRON_BODY,
	POTION_KIND_PASSWALL,
	POTION_KIND_RESI_PHYS,
	POTION_KIND_RESI_HEAT,
	POTION_KIND_RESI_COLD,
	POTION_KIND_RESI_ACID,
	POTION_KIND_RESI_MIND,
	POTION_KIND_RESI_ELEC,
	POTION_KIND_RESI_POIS,
	POTION_KIND_SHARPNESS,
	POTION_KIND_DULLNESS,
	POTION_KIND_STRENGTH,
	POTION_KIND_WEAKNESS,
	POTION_KIND_QUICKNESS,
	POTION_KIND_SLOWNESS,
	POTION_KIND_BRAINY,
	POTION_KIND_BRAINLESS,
	POTION_KIND_WISE,
	POTION_KIND_FOOLISH,
	POTION_KIND_ATTRACTIVE,
	POTION_KIND_UNATTRACTIVE,
	POTION_KIND_SENSE_INVISIBLE,
	POTION_KIND_POW_UP_HP,
	POTION_KIND_SPEED_UP,
	POTION_KIND_SPEED_DOWN,
	POTION_KIND_CURE_LEV,
	POTION_KIND_CURE_HP_LIGHT,
	POTION_KIND_CURE_HP_MODERATE,
	POTION_KIND_CURE_HP_SERIOUS,
	POTION_KIND_CURE_HP_MAX,
	POTION_KIND_CURE_POISON,
	POTION_KIND_CURE_STATUS,
	POTION_KIND_DETECT_MNSTR,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ��������ʪ�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ��ʪ������������ SCROLL_KIND_NULL �ǡ����롣
***************************************************************/

scroll_kind_t	g_scroll_trans_tab[] = {
	SCROLL_KIND_NULL,
	SCROLL_KIND_SLEEP,
	SCROLL_KIND_IDENTIFY_ITEM,
	SCROLL_KIND_DETECT_ITEM,
	SCROLL_KIND_TELEPORT,
	SCROLL_KIND_POW_UP_WPN_HIT,
	SCROLL_KIND_POW_UP_WPN_CRTCL,
	SCROLL_KIND_POW_UP_WPN_DAM,
	SCROLL_KIND_POW_UP_ARMOR_DEF,
	SCROLL_KIND_POW_UP_ARMOR_CRTCL,
	SCROLL_KIND_POW_UP_ARMOR_AC,
	SCROLL_KIND_PROTECT_ARMOR,
	SCROLL_KIND_REMOVE_CURSE,
	SCROLL_KIND_RECALL,
	SCROLL_KIND_TYPHOON,
	SCROLL_KIND_CONFLAGRATION,
	SCROLL_KIND_EARTHQUAKE,
	SCROLL_KIND_THUNDERCLOUD,
	SCROLL_KIND_INUNDATION,
	SCROLL_KIND_SUBSTITUTE,
	SCROLL_KIND_BURNING_HANDS,
	SCROLL_KIND_MIND_READING,

/* �ɲ� */
	SCROLL_KIND_IDENTIFY_ALL_ITEM,
	SCROLL_KIND_RALLY,
	SCROLL_KIND_IRON_MAN,
	SCROLL_KIND_BOOMERANG,
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ��������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ������������� STICK_KIND_NULL �ǡ����롣
***************************************************************/

stick_kind_t	g_stick_trans_tab[] = {
	STICK_KIND_NULL,
	STICK_KIND_WAND,
	STICK_KIND_ROD,
	STICK_KIND_STAFF,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ����������������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ��������������������� ACCE_KIND_NULL �ǡ����롣
***************************************************************/

acce_kind_t	g_acce_trans_tab[] = {
	ACCE_KIND_NULL,
	ACCE_KIND_RING,
	ACCE_KIND_AMULET,
	ACCE_KIND_NECKLACE,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������ؤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ���ؤ����������� RING_KIND_NULL �ǡ����롣
***************************************************************/

ring_kind_t	g_ring_trans_tab[] = {
	RING_KIND_NULL,
	RING_KIND_SLOW_DIGESTION,
	RING_KIND_TELEPORT_PARTY,
	RING_KIND_TELEPORT,
	RING_KIND_SHARPNESS,
	RING_KIND_DULLNESS,
	RING_KIND_STRENGTH,
	RING_KIND_WEAKNESS,
	RING_KIND_QUICKNESS,
	RING_KIND_SLOWNESS,
	RING_KIND_BRAINY,
	RING_KIND_BRAINLESS,
	RING_KIND_WISE,
	RING_KIND_FOOLISH,
	RING_KIND_ATTRACTIVE,
	RING_KIND_UNATTRACTIVE,
	RING_KIND_CURE_HP,
	RING_KIND_CURE_MP,
	RING_KIND_DRAIN_HP,
	RING_KIND_DRAIN_MP,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ����������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ��������������� AMULET_KIND_NULL �ǡ����롣
***************************************************************/

amulet_kind_t	g_amulet_trans_tab[] = {
	AMULET_KIND_NULL,
	AMULET_KIND_RESI_STAT_DEAD,
	AMULET_KIND_RESI_STAT_STONE,
	AMULET_KIND_RESI_STAT_PARALYZE,
	AMULET_KIND_RESI_STAT_POISON,
	AMULET_KIND_RESI_STAT_CONFUSION,
	AMULET_KIND_RESI_STAT_BLIND,
	AMULET_KIND_RESI_STAT_SLEEP,
	AMULET_KIND_RESI_STAT_SILENCE,
	AMULET_KIND_RESI_STAT_FEAR,
	AMULET_KIND_RESI_STAT_HALLUCINATION,
	AMULET_KIND_RESI_STAT_CHARM,
	AMULET_KIND_RESI_STAT_DRUNK,
	AMULET_KIND_RESI_STAT_FLY,
	AMULET_KIND_RESI_STAT_VANISH,
	AMULET_KIND_RESI_STAT_IRON_BODY,
	AMULET_KIND_RESI_STAT_PASSWALL,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������ؤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ���ؤ����������� NECKLACE_KIND_NULL �ǡ����롣
***************************************************************/

necklace_kind_t	g_necklace_trans_tab[] = {
	NECKLACE_KIND_NULL,
	NECKLACE_KIND_RESI_PHYS,
	NECKLACE_KIND_RESI_HEAT,
	NECKLACE_KIND_RESI_COLD,
	NECKLACE_KIND_RESI_ACID,
	NECKLACE_KIND_RESI_MIND,
	NECKLACE_KIND_RESI_ELEC,
	NECKLACE_KIND_RESI_POIS,
	NECKLACE_KIND_CURSE_PHYS,
	NECKLACE_KIND_CURSE_HEAT,
	NECKLACE_KIND_CURSE_COLD,
	NECKLACE_KIND_CURSE_ACID,
	NECKLACE_KIND_CURSE_MIND,
	NECKLACE_KIND_CURSE_ELEC,
	NECKLACE_KIND_CURSE_POIS,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �������ڴ�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �ڴ������������ INST_KIND_NULL �ǡ����롣
***************************************************************/

inst_kind_t	g_inst_trans_tab[] = {
	INST_KIND_NULL,
	INST_KIND_TRUMPET,
	INST_KIND_TROMBONE,
	INST_KIND_FLUGELHORN,
	INST_KIND_CORNET,
	INST_KIND_HORN,
	INST_KIND_TUBA,
	INST_KIND_SOUSAPHONE,
	INST_KIND_BUGLE,
	INST_KIND_FLUTE,
	INST_KIND_CLARINET,
	INST_KIND_BASS_CLARINET,
	INST_KIND_PICCOLO,
	INST_KIND_OBOE,
	INST_KIND_BASSOON,
	INST_KIND_SAXOPHONE,
	INST_KIND_VIOLIN,
	INST_KIND_VIOLA,
	INST_KIND_CELLO,
	INST_KIND_DOUBLEBASS,
	INST_KIND_HARP,
	INST_KIND_MANDOLIN,
	INST_KIND_BANJO,
	INST_KIND_SITAR,
	INST_KIND_BASS_DRUM,
	INST_KIND_TENOR_DRUM,
	INST_KIND_SNARE_DRUM,
	INST_KIND_TOM_TOM,
	INST_KIND_CONGAS,
	INST_KIND_TIMPANI,
	INST_KIND_CYMBAL,
	INST_KIND_GONG,
	INST_KIND_MARACA,
	INST_KIND_TRIANGLE,
	INST_KIND_CASTANETS,
	INST_KIND_TUBULAR_BELLS,
	INST_KIND_XYLOPHONE,
	INST_KIND_ACCORDION,
	INST_KIND_BAGPIPE,
	INST_KIND_HARMONICA,
	INST_KIND_KAZOO,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �������������� ANTHOLOGY_KIND_NULL �ǡ����롣
***************************************************************/

anthology_kind_t	g_anthology_trans_tab[] = {
	ANTHOLOGY_KIND_NULL,
	ANTHOLOGY_KIND_CURE,
	ANTHOLOGY_KIND_STRENGTHEN_ABL,
	ANTHOLOGY_KIND_WEAKEN_ABL,
	ANTHOLOGY_KIND_RESI_STAT,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ������������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����������������� LIGHT_KIND_NULL �ǡ����롣
***************************************************************/

light_kind_t	g_light_trans_tab[] = {
	LIGHT_KIND_NULL,
	LIGHT_KIND_TORCH,
	LIGHT_KIND_LANTERN,
	LIGHT_KIND_LAMP,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �����������������ƥ�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �����������ƥ������������ STAR_DROP_KIND_ELEC �ǡ����롣
***************************************************************/

star_drop_kind_t	g_key_item_trans_tab[] = {
	STAR_DROP_KIND_ELEC,
	STAR_DROP_KIND_PHYS,
	STAR_DROP_KIND_HEAT,
	STAR_DROP_KIND_COLD,
	STAR_DROP_KIND_MIND,
	STAR_DROP_KIND_ACID,
	STAR_DROP_KIND_POIS,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ������˾�ߤ�����������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ˾�ߤ���������������� WISH_LEVEL_NULL �ǡ����롣
***************************************************************/

wish_level_t	g_wish_level_trans_tab[] = {
	WISH_LEVEL_NULL,
	WISH_LEVEL_ARMAGEDDON,
	WISH_LEVEL_DAEMON,
	WISH_LEVEL_DJINNI,
	WISH_LEVEL_GOD,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �����������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ���������������� FOOD_KIND_NULL �ǡ����롣
***************************************************************/

food_kind_t	g_food_trans_tab[] = {
	FOOD_KIND_NULL,
	FOOD_KIND_PRESERVED,
	FOOD_KIND_SAUSAGE,
	FOOD_KIND_BACON,
	FOOD_KIND_CHIPPED_BEEF,
	FOOD_KIND_CORNED_BEEF,
	FOOD_KIND_BREAD,
	FOOD_KIND_BROWN_BREAD,
	FOOD_KIND_TOAST,
	FOOD_KIND_PANCAKE,
	FOOD_KIND_SALAD,
	FOOD_KIND_POTATO_SALAD,
	FOOD_KIND_SCRAMBLED_EGGS,
	FOOD_KIND_FRIED_EGGS,
	FOOD_KIND_HARD_BOILED_EGGS,
	FOOD_KIND_SOFT_BOILED_EGGS,
	FOOD_KIND_BEEF_STEAK,
	FOOD_KIND_PORK_SAUTE,
	FOOD_KIND_FRIED_CHICKEN,
	FOOD_KIND_FRIED_FISH,
	FOOD_KIND_FRIED_POTATO,
	FOOD_KIND_STEWED_BEEF,
	FOOD_KIND_CONSOMME,
	FOOD_KIND_POTAGE,
	FOOD_KIND_APPLE_PIE,
	FOOD_KIND_APPLE,
	FOOD_KIND_GRAPE,
	FOOD_KIND_ORANGE,
	FOOD_KIND_PEAR,
	FOOD_KIND_GRAPEFRUIT,
	FOOD_KIND_PLUM,
	FOOD_KIND_PEACH,
	FOOD_KIND_APRICOT,
	FOOD_KIND_BLACK_BERRY,
	FOOD_KIND_CRAN_BERRY,
	FOOD_KIND_RASP_BERRY,
	FOOD_KIND_STRAW_BERRY,
	FOOD_KIND_POTAGE,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ����������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ��������������� TOBACCO_KIND_NULL �ǡ����롣
***************************************************************/

tobacco_kind_t	g_tobacco_trans_tab[] = {
	TOBACCO_KIND_NULL,
	TOBACCO_KIND_CIGARET,
	TOBACCO_KIND_CIGAR,
	TOBACCO_KIND_CUT_TOBACCO,
	TOBACCO_KIND_SNUFF_TOBACCO,
	TOBACCO_KIND_CHEWING_TOBACCO,
	TOBACCO_KIND_ABSTAIN_GUM,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ����������Υ֥��ɤ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����Υ֥��ɤ����������� TOBACCO_BRAND_NULL �ǡ����롣
***************************************************************/

tobacco_brand_t	g_tobacco_brand_trans_tab[] = {
	TOBACCO_BRAND_NULL,

	/* CIGARET */
	TOBACCO_BRAND_HELLO,
	TOBACCO_BRAND_SUN_SHINE,
	TOBACCO_BRAND_CHERRY_TREE,
	TOBACCO_BRAND_GOLDEN_RAT,
	TOBACCO_BRAND_AIR_SHIT,
	TOBACCO_BRAND_HOP,
	TOBACCO_BRAND_PIECE,
	TOBACCO_BRAND_HARPY,
	TOBACCO_BRAND_HIGH_LIGHT,
	TOBACCO_BRAND_SHOOTING_STARS,
	TOBACCO_BRAND_WILD_NINE,
	TOBACCO_BRAND_WILD_NINE_MENTHOL,
	TOBACCO_BRAND_LODGE,
	TOBACCO_BRAND_LODGE_MENTHOL,
	TOBACCO_BRAND_CANCER,
	TOBACCO_BRAND_CANCER_MENTHOL,
	TOBACCO_BRAND_FRONT_LINE,
	TOBACCO_BRAND_FRONT_LINE_MENTHOL,
	TOBACCO_BRAND_MARCO_POLO,
	TOBACCO_BRAND_CAMELLIA,
	TOBACCO_BRAND_GOOD_LUCK,
	TOBACCO_BRAND_BAD_GUY,

	/* CIGAR */
	TOBACCO_BRAND_ARCADIA,
	TOBACCO_BRAND_GLORIA,
	TOBACCO_BRAND_VULCAN,
	TOBACCO_BRAND_PONY,
	TOBACCO_BRAND_KEITH,
	TOBACCO_BRAND_LUMBERJACK,
	TOBACCO_BRAND_CORONA,
	TOBACCO_BRAND_HALF_CORONA,
	TOBACCO_BRAND_CRYSTAL,

	/* CUT TOBACCO */
	TOBACCO_BRAND_FOREST_BRANDY,
	TOBACCO_BRAND_SILK_ROAD,
	TOBACCO_BRAND_PROMENADE,
	TOBACCO_BRAND_BIG_HORN,
	TOBACCO_BRAND_ROCKING_CHAIR,
	TOBACCO_BRAND_VANILLA,
	TOBACCO_BRAND_WILD_MANGO,
	TOBACCO_BRAND_KENTUCKY_BIRD,
	TOBACCO_BRAND_ORIENT,
	TOBACCO_BRAND_FUJI,

	/* SNUFF TOBACCO */
	TOBACCO_BRAND_DOGGY_APRICOT,
	TOBACCO_BRAND_DOGGY_WHISKY,
	TOBACCO_BRAND_DOGGY_HONEY,
	TOBACCO_BRAND_DOGGY_SPEARMINT,
	TOBACCO_BRAND_DOGGY_PEPPERMINT,
	TOBACCO_BRAND_DOGGY_VANILLA,
	TOBACCO_BRAND_DOGGY_MENTHOL,
	TOBACCO_BRAND_DOGGY_CITRUS,
	TOBACCO_BRAND_DOGGY_SHERRY,

	/* CHEWING TOBACCO */
	TOBACCO_BRAND_ROSE_PREMIUM,
	TOBACCO_BRAND_ROSE_VANILLA,
	TOBACCO_BRAND_ROSE_MENTHOL,

	/* ABSTAIN GUM */
	TOBACCO_BRAND_NICOTIME,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* �������ѥ��פ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* �ѥ��פ����������� PIPE_KIND_NULL �ǡ����롣
***************************************************************/

pipe_kind_t	g_pipe_trans_tab[] = {
	PIPE_KIND_NULL,
	PIPE_KIND_PIPE,
	PIPE_KIND_KISEL,
	PIPE_KIND_CIGARET_HOLDER,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ������õ�������ƥ�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* õ�������ƥ������������ RARE_GOODS_KIND_NULL �ǡ����롣
***************************************************************/

rare_goods_kind_t	g_rare_goods_trans_tab[] = {
	RARE_GOODS_KIND_NULL,
	RARE_GOODS_KIND_DAEMON_SCORE,
	RARE_GOODS_KIND_VAMPIRES_CROSS,
	RARE_GOODS_KIND_SCHWARZSCHILD_DAEMON,
	RARE_GOODS_KIND_REASON_OF_DECLINE,
	RARE_GOODS_KIND_GARGOYLES_TEARS,
	RARE_GOODS_KIND_FLUTE_OF_MADONNA,
	RARE_GOODS_KIND_THE_ART_OF_WAR,
	RARE_GOODS_KIND_TICKET_TO_PARADISE,
	RARE_GOODS_KIND_CALL_OF_HADES,
	RARE_GOODS_KIND_MEMORIES_OF_THE_GOLDEN_AGE,
	RARE_GOODS_KIND_ISNT_REALIZED,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ������������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ����������������� COIN_KIND_NULL �ǡ����롣
***************************************************************/

coin_kind_t	g_coin_trans_tab[] = {
	COIN_KIND_NULL,
	COIN_KIND_GOLD,
	COIN_KIND_SILVER,
	COIN_KIND_COPPER,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ��������ˡ�������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ��ˡ������������ SPELL_KIND_NULL �ǡ����롣
***************************************************************/

spell_kind_t	g_spell_trans_tab[] = {
	SPELL_KIND_NULL,
/* MAG */
	SPELL_KIND_MAG_MIN_N,
	SPELL_KIND_LIGHT,
	SPELL_KIND_DARKNESS,
	SPELL_KIND_TELEPORT_PARTY,
	SPELL_KIND_TELEPORT,
	SPELL_KIND_RECALL,
	SPELL_KIND_KNOCK,
	SPELL_KIND_LOCK,
	SPELL_KIND_DISARM_TRAP,
	SPELL_KIND_DISPEL_MAGIC,
	SPELL_KIND_MIRROR_IMAGE,
	SPELL_KIND_ANIMATE_OBJECTS,
	SPELL_KIND_SHELTER,
	SPELL_KIND_CREATE_FOOD,
	SPELL_KIND_IDENTIFY_ITEM,
	SPELL_KIND_SEARCHING,
	SPELL_KIND_ANALYZE_DWEOMER,
	SPELL_KIND_DETECT_ITEM,
	SPELL_KIND_DETECT_DOORS,
	SPELL_KIND_DETECT_TRAPS,
	SPELL_KIND_DETECT_MAGIC,
	SPELL_KIND_DETECT_MONSTER,
	SPELL_KIND_SENSE_INVISIBLE,
	SPELL_KIND_FLY,
	SPELL_KIND_FEATHER_FALL,
	SPELL_KIND_VANISH,
	SPELL_KIND_DARKVISION,
	SPELL_KIND_PASSWALL,
	SPELL_KIND_POLYMORPH_OTHER,
	SPELL_KIND_POLYMORPH_SELF,
	SPELL_KIND_STEALTH,
	SPELL_KIND_MAG_MAX_N,
/* SOR */
	SPELL_KIND_SOR_MIN_N,
	SPELL_KIND_MAGIC_MISSILE,
	SPELL_KIND_FIRE_BALL,
	SPELL_KIND_ICE_BLIZZARD,
	SPELL_KIND_MIND_STORM,
	SPELL_KIND_ACID_RAIN,
	SPELL_KIND_LIGHTNING_BOLT,
	SPELL_KIND_POISON_CLOUD,
	SPELL_KIND_DEATH_SPELL,
	SPELL_KIND_WORD_OF_DESTRUCTION,
	SPELL_KIND_MAGE_ARMOR,
	SPELL_KIND_MAGIC_SHIELD,
	SPELL_KIND_STONESKIN,
	SPELL_KIND_IRON_BODY,
	SPELL_KIND_SPELL_RESISTANCE,
	SPELL_KIND_COUNTER_MAGIC,
	SPELL_KIND_STONE,
	SPELL_KIND_PARALYZE,
	SPELL_KIND_POISON,
	SPELL_KIND_CONFUSION,
	SPELL_KIND_BLINDNESS,
	SPELL_KIND_SLEEP,
	SPELL_KIND_SILENCE,
	SPELL_KIND_FEAR,
	SPELL_KIND_HALLUCINATION,
	SPELL_KIND_CHARM,
	SPELL_KIND_SOR_MAX_N,
/* ENC */
	SPELL_KIND_ENC_MIN_N,
	SPELL_KIND_SHARPNESS,
	SPELL_KIND_STRENGTH,
	SPELL_KIND_QUICKNESS,
	SPELL_KIND_BRAINY,
	SPELL_KIND_WISE,
	SPELL_KIND_ATTRACTIVE,
	SPELL_KIND_POWER_UP_HP,
	SPELL_KIND_HASTE,
	SPELL_KIND_DULLNESS,
	SPELL_KIND_WEAKNESS,
	SPELL_KIND_SLOWNESS,
	SPELL_KIND_BRAINLESS,
	SPELL_KIND_FOOLISH,
	SPELL_KIND_UNATTRACTIVE,
	SPELL_KIND_ENERGY_DRAIN,
	SPELL_KIND_SLOW,
	SPELL_KIND_HUNGER,
	SPELL_KIND_CANCELLATION,
	SPELL_KIND_ENC_MAX_N,
/* SUM */
	SPELL_KIND_SUM_MIN_N,
	SPELL_KIND_SKELETON_WARRIOR,
	SPELL_KIND_SUMMON_UNICORN,
	SPELL_KIND_SUMMON_EFREET,
	SPELL_KIND_SUMMON_DJINNI,
	SPELL_KIND_SUMMON_PHOENIX,
	SPELL_KIND_SUMMON_RANDOM,
	SPELL_KIND_CREATE_UNDEAD,
	SPELL_KIND_DISMISSAL,
	SPELL_KIND_SUM_MAX_N,
/* PRI */
	SPELL_KIND_PRI_MIN_N,
	SPELL_KIND_CURE_HP_LIGHT,
	SPELL_KIND_CURE_HP_MODERATE,
	SPELL_KIND_CURE_HP_SERIOUS,
	SPELL_KIND_CURE_HP_MAX,
	SPELL_KIND_REGENERATION,
	SPELL_KIND_CURE_MP,
	SPELL_KIND_TRANSFER_MP,
	SPELL_KIND_RESTORE_EXPERIENCE,
	SPELL_KIND_RESURRECTION,
	SPELL_KIND_HEAL,
	SPELL_KIND_CURE_STATUS,
	SPELL_KIND_CURE_STONE,
	SPELL_KIND_CURE_PARALYZE,
	SPELL_KIND_CURE_POISON,
	SPELL_KIND_CURE_CONFUSION,
	SPELL_KIND_CURE_BLINDNESS,
	SPELL_KIND_CURE_SLEEP,
	SPELL_KIND_CURE_SILENCE,
	SPELL_KIND_CURE_FEAR,
	SPELL_KIND_CURE_HALLUCINATION,
	SPELL_KIND_CURE_CHARM,
	SPELL_KIND_PROTECTION,
	SPELL_KIND_RESIST_PHYSICAL,
	SPELL_KIND_RESIST_HEAT,
	SPELL_KIND_RESIST_COLD,
	SPELL_KIND_RESIST_ACID,
	SPELL_KIND_RESIST_MIND,
	SPELL_KIND_RESIST_ELECTRICITY,
	SPELL_KIND_RESIST_POISON,
	SPELL_KIND_BLESS,
	SPELL_KIND_REMOVE_CURSE,
	SPELL_KIND_DISPEL_UNDEAD,
	SPELL_KIND_ESCAPE,
	SPELL_KIND_SANCTUARY,
	SPELL_KIND_WISH,
	SPELL_KIND_PRI_MAX_N,
/* SHA */
	SPELL_KIND_SHA_MIN_N,
	SPELL_KIND_WEAK_FIRE_ELEMENTAL,
	SPELL_KIND_WEAK_WATER_ELEMENTAL,
	SPELL_KIND_WEAK_AIR_ELEMENTAL,
	SPELL_KIND_WEAK_EARTH_ELEMENTAL,
	SPELL_KIND_WEAK_LIGHT_ELEMENTAL,
	SPELL_KIND_WEAK_DARK_ELEMENTAL,
	SPELL_KIND_SUMMON_FIRE_ELEMENTAL,
	SPELL_KIND_SUMMON_SALAMANDER,
	SPELL_KIND_SUMMON_WATER_ELEMENTAL,
	SPELL_KIND_SUMMON_UNDINE,
	SPELL_KIND_SUMMON_AIR_ELEMENTAL,
	SPELL_KIND_SUMMON_SYLPH,
	SPELL_KIND_SUMMON_EARTH_ELEMENTAL,
	SPELL_KIND_SUMMON_GNOME,
	SPELL_KIND_SUMMON_WILL_O_WISP,
	SPELL_KIND_SUMMON_SHADE,
	SPELL_KIND_SHA_MAX_N,
/* BAR */
	SPELL_KIND_BAR_MIN_N,
	SPELL_KIND_SONG_CURE_HP,
	SPELL_KIND_SONG_CURE_MP,
	SPELL_KIND_SONG_SHARPNESS,
	SPELL_KIND_SONG_STRENGTH,
	SPELL_KIND_SONG_QUICKNESS,
	SPELL_KIND_SONG_BRAINY,
	SPELL_KIND_SONG_WISE,
	SPELL_KIND_SONG_ATTRACTIVE,
	SPELL_KIND_SONG_DULLNESS,
	SPELL_KIND_SONG_WEAKNESS,
	SPELL_KIND_SONG_SLOWNESS,
	SPELL_KIND_SONG_BRAINLESS,
	SPELL_KIND_SONG_FOOLISH,
	SPELL_KIND_SONG_UNATTRACTIVE,
	SPELL_KIND_SONG_RESI_STAT_STONE,
	SPELL_KIND_SONG_RESI_STAT_PARALYZE,
	SPELL_KIND_SONG_RESI_STAT_POISON,
	SPELL_KIND_SONG_RESI_STAT_CONFUSION,
	SPELL_KIND_SONG_RESI_STAT_BLIND,
	SPELL_KIND_SONG_RESI_STAT_SLEEP,
	SPELL_KIND_SONG_RESI_STAT_SILENCE,
	SPELL_KIND_SONG_RESI_STAT_FEAR,
	SPELL_KIND_SONG_RESI_STAT_HALLUCINATION,
	SPELL_KIND_SONG_RESI_STAT_CHARM,
	SPELL_KIND_SONG_RESI_STAT_DRUNK,
	SPELL_KIND_BAR_MAX_N,
/* NIN */
	SPELL_KIND_NIN_MIN_N,
	SPELL_KIND_TYPHOON,	/* ����-���� */
	SPELL_KIND_CONFLAGRATION,	/* ����-�к� */
	SPELL_KIND_EARTHQUAKE,	/* ����-�Ͽ� */
	SPELL_KIND_THUNDERCLOUD,	/* ����-��� */
	SPELL_KIND_INUNDATION,	/* ����-���� */

	SPELL_KIND_SUBSTITUTE,	/* ����-���� */
	SPELL_KIND_BURNING_HANDS,	/* ����-��� */
	SPELL_KIND_RALLY,	/* ����-���ڽ��� */
	SPELL_KIND_IRON_MAN,	/* ����-Ŵ�� */
	SPELL_KIND_MIND_READING,	/* ����-�����߿� */
	SPELL_KIND_NIN_MAX_N,
/* ANC */
	SPELL_KIND_ANC_MIN_N,
	SPELL_KIND_NOTHING,
	SPELL_KIND_POLTERGEIST,
	SPELL_KIND_ANC_MAX_N,

/* �ɲ� */
	SPELL_KIND_IDENTIFY_ALL_ITEM,
	SPELL_KIND_SUMMON_BONE,
	SPELL_KIND_STORE_LIGHT,
	SPELL_KIND_DISMISSAL_ELEMENTAL,
	SPELL_KIND_SHORT_TELEPORT_PARTY,
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ��������󥹥����������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ��󥹥��������������� MNSTR_KIND_NULL �ǡ����롣
***************************************************************/

mnstr_kind_t	g_mnstr_trans_tab[] = {
	MNSTR_KIND_NULL,
	/* �� */
	/* �ɥ饴�� */
	MNSTR_KIND_A_GOLD_DRAGON,
	MNSTR_KIND_A_SILVER_DRAGON,
	MNSTR_KIND_A_COPPER_DRAGON,
	MNSTR_KIND_A_RED_DRAGON,
	MNSTR_KIND_A_BLUE_DRAGON,
	MNSTR_KIND_A_YELLOW_DRAGON,
	MNSTR_KIND_A_GREEN_DRAGON,
	MNSTR_KIND_A_WHITE_DRAGON,
	MNSTR_KIND_A_BLACK_DRAGON,
	MNSTR_KIND_M_GOLD_DRAGON,
	MNSTR_KIND_M_SILVER_DRAGON,
	MNSTR_KIND_M_COPPER_DRAGON,
	MNSTR_KIND_M_RED_DRAGON,
	MNSTR_KIND_M_BLUE_DRAGON,
	MNSTR_KIND_M_YELLOW_DRAGON,
	MNSTR_KIND_M_GREEN_DRAGON,
	MNSTR_KIND_M_WHITE_DRAGON,
	MNSTR_KIND_M_BLACK_DRAGON,
	/* ���� */
	MNSTR_KIND_PHOENIX,
	MNSTR_KIND_UNICORN,
	MNSTR_KIND_PYON_PYON,
	/* ���� */
	MNSTR_KIND_LEPRECHAUN,
	/* ���� */
	MNSTR_KIND_FIRE_ELEMENTAL,
	MNSTR_KIND_SALAMANDER,
	MNSTR_KIND_WATER_ELEMENTAL,
	MNSTR_KIND_UNDINE,
	MNSTR_KIND_AIR_ELEMENTAL,
	MNSTR_KIND_SYLPH,
	MNSTR_KIND_EARTH_ELEMENTAL,
	MNSTR_KIND_GNOME,
	MNSTR_KIND_WILL_O_WISP,
	MNSTR_KIND_SHADE,
	/* ��ʪ */
	MNSTR_KIND_VENUS_FLY_TRAP,
	MNSTR_KIND_SLIME,
	MNSTR_KIND_SPORE,
	/* ưʪ */
	MNSTR_KIND_GIANT_BAT,
	MNSTR_KIND_GIANT_RAT,
	MNSTR_KIND_GIANT_SNAKE,
	MNSTR_KIND_VIPER_SNAKE,
	MNSTR_KIND_CAT,
	MNSTR_KIND_DOG,
	MNSTR_KIND_WOLF,
	/* ���� */
	MNSTR_KIND_GIANT_CENTIPEDE,
	MNSTR_KIND_GIANT_BEE,
	MNSTR_KIND_GIANT_SCORPION,
	MNSTR_KIND_GIANT_ANT,
	MNSTR_KIND_GIANT_SPIDER,
	MNSTR_KIND_ACID_FLY,
	MNSTR_KIND_GIANT_BEETLE,
	/* �ʹ� */
	MNSTR_KIND_FIGHTER,
	MNSTR_KIND_MONK,
	MNSTR_KIND_HUNTER,
	MNSTR_KIND_THIEF,
	MNSTR_KIND_WIZARD,
	MNSTR_KIND_SUMMONER,
	MNSTR_KIND_PRIEST,
	MNSTR_KIND_SHAMAN,
	MNSTR_KIND_BARD,
	MNSTR_KIND_NINJA,
	MNSTR_KIND_BISHOP,
	MNSTR_KIND_FARMER,
	MNSTR_KIND_CRAFTSMAN,
	MNSTR_KIND_MERCHANT,
	/* Ⱦ�� */
	MNSTR_KIND_HARPY,
	MNSTR_KIND_ANDRO_SCORPION,
	MNSTR_KIND_LAMIA,
	MNSTR_KIND_CENTAUR,
	MNSTR_KIND_BIRD_MAN,
	MNSTR_KIND_WEREWOLF,
	MNSTR_KIND_MINOTAUR,
	MNSTR_KIND_MEDUSA,
	/* ��� */
	MNSTR_KIND_YETI,
	MNSTR_KIND_OGRE,
	MNSTR_KIND_TROLL,
	MNSTR_KIND_MORMIN_TROLL,
	MNSTR_KIND_FIRE_GIANT,
	MNSTR_KIND_FROST_GIANT,
	MNSTR_KIND_CLOUD_GIANT,
	MNSTR_KIND_MOUNTAIN_GIANT,
	MNSTR_KIND_CYCLOPS,
	/* ������ʪ */
	/* ������ʪ */
	/* ��ˡ��ʪ */
	MNSTR_KIND_INVISIBLE_STALKER,
	MNSTR_KIND_GARGOYLE,
	MNSTR_KIND_MIMIC,
	MNSTR_KIND_WOOD_GOLEM,
	MNSTR_KIND_BONE_GOLEM,
	MNSTR_KIND_FLESH_GOLEM,
	MNSTR_KIND_STONE_GOLEM,
	MNSTR_KIND_IRON_GOLEM,
	MNSTR_KIND_GAS_CLOUD,
	/* ������ */
	MNSTR_KIND_HIPPOGRIFF,
	MNSTR_KIND_GRIFFON,
	MNSTR_KIND_MANTICORE,
	MNSTR_KIND_CHIMERA,
	/* ����ǥå� */
	MNSTR_KIND_POLTERGEIST,
	MNSTR_KIND_SKELETON,
	MNSTR_KIND_ZOMBIE,
	MNSTR_KIND_GHOUL,
	MNSTR_KIND_GHOST,
	MNSTR_KIND_WIGHT,
	MNSTR_KIND_MUMMY,
	MNSTR_KIND_DURAHAN,
	MNSTR_KIND_BANSHEE,
	MNSTR_KIND_WRAITH,
	MNSTR_KIND_VAMPIRE,
	MNSTR_KIND_SPIRIT,
	/* ���� */
	MNSTR_KIND_KOBOLD,
	MNSTR_KIND_GOBLIN,
	MNSTR_KIND_GREMLIN,
	MNSTR_KIND_HOBGOBLIN,
	MNSTR_KIND_ORK,
	MNSTR_KIND_GNOLL,
	MNSTR_KIND_INCUBUS,
	MNSTR_KIND_SUCCUBUS,
	MNSTR_KIND_EFREET,
	MNSTR_KIND_DJINNI,
	/* ��� */
	MNSTR_KIND_RUST_MONSTER,
	MNSTR_KIND_HELLHOUND,
	MNSTR_KIND_HYDRA,
	MNSTR_KIND_COCKATRICE,
	MNSTR_KIND_WYVERN,
	MNSTR_KIND_CERBERUS,
	MNSTR_KIND_GORGON,
	MNSTR_KIND_BASILISK,
	/* ���� */
	MNSTR_KIND_IMP,
	MNSTR_KIND_JACK_O_LANTERN,
	MNSTR_KIND_LESSER_DAEMON,
	MNSTR_KIND_GREATER_DAEMON,
	/* �ܥ� */
	MNSTR_KIND_GREAT_MINOTAUR,
	MNSTR_KIND_HIGH_RE_HOO,
	MNSTR_KIND_MEDUSA_ZOMBIE,
	MNSTR_KIND_BLACK_UNICORN,
	MNSTR_KIND_VAMPIRE_LORD,
	MNSTR_KIND_GIGANTIC_CENTIPEDE,

	/* �ɲ� */
	MNSTR_KIND_BILLION_ELEMENTAL,
	MNSTR_KIND_CYBERN,
	MNSTR_KIND_RELATIVISTIC_DAEMON,
	MNSTR_KIND_ETERNAL_DRAGON,
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ������櫤������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* 櫤����������� TRAP_KIND_NULL �ǡ����롣
***************************************************************/

trap_kind_t	g_trap_trans_tab[] = {
	TRAP_KIND_NULL,
	TRAP_KIND_SLEEP,
	TRAP_KIND_ARW,
	TRAP_KIND_POISON_DARTS,
	TRAP_KIND_BOMB,
	TRAP_KIND_TELEPORT_PARTY,
	TRAP_KIND_TELEPORT,
	TRAP_KIND_PIT,
	TRAP_KIND_CHUTE,
	TRAP_KIND_SANCTUARY,

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ���������ե����Ȥ������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ���ե����Ȥ����������� FX_KIND_NULL �ǡ����롣
***************************************************************/

fx_kind_t	g_fx_trans_tab[] = {
	FX_KIND_NULL,
	FX_KIND_STONE,
	FX_KIND_PARALYZE,
	FX_KIND_POISON,
	FX_KIND_CONFUSION,
	FX_KIND_BLIND,
	FX_KIND_SLEEP,
	FX_KIND_SILENCE,
	FX_KIND_FEAR,
	FX_KIND_HALLUCINATION,
	FX_KIND_CHARM,
	FX_KIND_FLY,
	FX_KIND_FAINT,
	FX_KIND_DRUNK,
	FX_KIND_VANISH,
	FX_KIND_IRON_BODY,
	FX_KIND_PASSWALL,
	FX_KIND_WEAK_HEAT,
	FX_KIND_WEAK_COLD,
	FX_KIND_WEAK_MIND,
	FX_KIND_WEAK_ACID,
	FX_KIND_WEAK_ELEC,
	FX_KIND_WEAK_POIS,
	FX_KIND_RESI_KNOC,
	FX_KIND_RESI_SLAS,
	FX_KIND_RESI_STIN,
	FX_KIND_RESI_HEAT,
	FX_KIND_RESI_COLD,
	FX_KIND_RESI_MIND,
	FX_KIND_RESI_ACID,
	FX_KIND_RESI_ELEC,
	FX_KIND_RESI_POIS,
	FX_KIND_SHARPNESS,
	FX_KIND_DULLNESS,
	FX_KIND_STRENGTH,
	FX_KIND_WEAKNESS,
	FX_KIND_QUICKNESS,
	FX_KIND_SLOWNESS,
	FX_KIND_BRAINY,
	FX_KIND_BRAINLESS,
	FX_KIND_WISE,
	FX_KIND_FOOLISH,
	FX_KIND_ATTRACTIVE,
	FX_KIND_UNATTRACTIVE,
	FX_KIND_SENSE_INVISIBLE,
	FX_KIND_POW_UP_HP,
	FX_KIND_MAGIC_SHIELD,
	FX_KIND_MAGE_ARMOR,
	FX_KIND_SUBSTITUTE,
	FX_KIND_BURNING_HANDS,
	FX_KIND_MIND_READING,
	FX_KIND_SPEED_UP,
	FX_KIND_SPEED_DOWN,
	FX_KIND_BLESS,
	FX_KIND_STORE_LIGHT,
	FX_KIND_COUNTER_MAGIC,
	FX_KIND_POLYMORPH,

/* �ɲ� */
	FX_KIND_RALLY,
	FX_KIND_IRON_MAN,
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ����������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ��������������� REQUEST_KIND_NULL �ǡ����롣
***************************************************************/

request_kind_t	g_request_trans_tab[] = {
	REQUEST_KIND_NULL,
	REQUEST_KIND_RARE_GOODS,	/* �����ƥ�õ�� */
	REQUEST_KIND_TAME_MNSTR,	/* ����ץ�� */
	REQUEST_KIND_RESCUE,	/* �߽� */
	REQUEST_KIND_TOUR_GUIDE,	/* �Ѹ����� */
	REQUEST_KIND_EXTERMINATE,	/* ��󥹥����༣ */
	REQUEST_KIND_REVENGE,	/* ��Ƥ�� */
	REQUEST_KIND_WANTED_CRIMINAL,	/* �޶�� */

	/* �ɲ� */
};

/***************************************************************
* �����֡��ǡ����򥻡��֡����ɤ������
* �ߴ�����ݻ����뤿����Ѵ��ơ��֥롣
* 
* ���� ���Ф˽��֤��ѹ����ʤ��ͤˡ��� ����
* 
* ����������������������ɬ���ơ��֥���������ɲä��ơ�
* �����֡��ե�����ΥС��������Ѥ��롣
* 
* ��������������� STAY_INN_KIND_LONG �ǡ����롣
***************************************************************/

stay_inn_kind_t	g_stay_inn_kind_trans_tab[] = {
	STAY_INN_KIND_LONG,
	STAY_INN_KIND_SHORT,
	STAY_INN_KIND_MEWS,

	/* �ɲ� */
};

#endif	/* GFILE_TAB_H */
