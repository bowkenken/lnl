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
* $Id: scene.h,v 1.22 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	SCENE_H
#define	SCENE_H

/***************************************************************
* �������ڤ��ؤ�
***************************************************************/

/* ������μ��� */

typedef enum {
	SCENE_N_NULL,

	SCENE_N_INIT,
	SCENE_N_TITLE,
	SCENE_N_OPENING,

	SCENE_N_TOWN,
	SCENE_N_SHOP,

	SCENE_N_DUN,
	SCENE_N_BATTLE,
	SCENE_N_BATTLE_BOSS,

	SCENE_N_LAST_BOSS,

	SCENE_N_GAME_OVER,
	SCENE_N_GAME_OVER_WAIT,
	SCENE_N_GAME_OVER_END,

	SCENE_N_ENDING,
	SCENE_N_ENDING_EPILOGUE,
	SCENE_N_ENDING_SPACE,
	SCENE_N_ENDING_STAFF_ROLL,
	SCENE_N_ENDING_END,

	SCENE_N_SEL_MBR_GRAPH,

	SCENE_N_MAX_N,
} scene_n_t;

typedef enum {
	SCENE_GROUP_N_NULL,

	SCENE_GROUP_N_INIT,
	SCENE_GROUP_N_TITLE,

	SCENE_GROUP_N_PLAYING,
	SCENE_GROUP_N_BATTLE,

	SCENE_GROUP_N_GAME_OVER,
	SCENE_GROUP_N_ENDING,
	SCENE_GROUP_N_SPACE,
	SCENE_GROUP_N_GAME_END,

	SCENE_GROUP_N_SEL_GRAPH,

	SCENE_GROUP_N_DEMO,

	SCENE_GROUP_N_CAN_SKIP,
	SCENE_GROUP_N_CAN_NOT_SKIP,

	SCENE_GROUP_N_MAX_N,
} scene_group_n_t;

typedef enum {
	LAST_SCENE_N_NULL,

	LAST_SCENE_N_ENTER,

	LAST_SCENE_N_ENCOUNTER,
	LAST_SCENE_N_ENCOUNTER_CUT_IN,
	LAST_SCENE_N_ENCOUNTER_WORDS,
	LAST_SCENE_N_ENCOUNTER_CUT_OUT,
	LAST_SCENE_N_ENCOUNTER_CUT_END,

	LAST_SCENE_N_EXEL,
	LAST_SCENE_N_EXEL_ENTER,
	LAST_SCENE_N_EXEL_CUT_IN,
	LAST_SCENE_N_EXEL_WORDS,
	LAST_SCENE_N_EXEL_CUT_OUT,
	LAST_SCENE_N_EXEL_CUT_END,
	LAST_SCENE_N_EXEL_HYPER,
	LAST_SCENE_N_EXEL_BATTLE,
	LAST_SCENE_N_EXEL_DIE,

	LAST_SCENE_N_EXELER,
	LAST_SCENE_N_EXELER_CUT_IN,
	LAST_SCENE_N_EXELER_WORDS,
	LAST_SCENE_N_EXELER_CUT_OUT,
	LAST_SCENE_N_EXELER_CUT_END,
	LAST_SCENE_N_EXELER_ENTER,
	LAST_SCENE_N_EXELER_HYPER,
	LAST_SCENE_N_EXELER_BATTLE,
	LAST_SCENE_N_EXELER_DIE,

	LAST_SCENE_N_XEX,
	LAST_SCENE_N_XEX_CUT_IN,
	LAST_SCENE_N_XEX_WORDS,
	LAST_SCENE_N_XEX_CUT_OUT,
	LAST_SCENE_N_XEX_CUT_END,

	LAST_SCENE_N_XX_ENTER,
	LAST_SCENE_N_XX_WORDS,
	LAST_SCENE_N_XX_BATTLE,
	LAST_SCENE_N_XX_DIE,

	LAST_SCENE_N_END,

	LAST_SCENE_N_MAX_N,
} last_scene_n_t;

#endif	/* SCENE_H */
