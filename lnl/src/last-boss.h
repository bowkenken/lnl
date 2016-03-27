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
* $Id: last-boss.h,v 1.15 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	LAST_BOSS_H
#define	LAST_BOSS_H

/***************************************************************
* �饹�ܥ�
***************************************************************/

/* �ޥåס����٥�� */

#define	MAP_EVENT_LAST_BOSS_APPEAR_PARTY	'a'
#define	MAP_EVENT_LAST_BOSS_BATTLE_PARTY	'b'
#define	MAP_EVENT_LAST_BOSS_SCROLL_MAP	'c'
#define	MAP_EVENT_LAST_BOSS_BATTLE_BOSS	'z'
#define	MAP_EVENT_LAST_BOSS_WORDS	'y'

/* ���������˻Ĥ뾲�Υ�������� */
#define	LAST_BOSS_SAFE_SECT	'S'

#define	JOINT_MAX_N	4

typedef struct {
	char	joint_mnr, mjr, mnr;
	long	x, y;
} last_boss_joint_t;

typedef struct {
	last_boss_joint_t	joint[JOINT_MAX_N + 1];
	const char	*ptn[MAP_MAX_Y];
} last_boss_parts_t;

typedef struct {
	char	transmit_chr;

	char	mjr[MAP_MAX_Y][MAP_MAX_X];
	char	mnr[MAP_MAX_Y][MAP_MAX_X];
	flg_map_t	flg[MAP_MAX_Y][MAP_MAX_X];
	curs_attr_t	attr[MAP_MAX_Y][MAP_MAX_X];
} last_boss_ptn_t;

/***************************************************************
* XX �Υ��������
***************************************************************/

typedef enum {
	XX_ACT_KIND_NULL,

	XX_ACT_KIND_HEAT,
	XX_ACT_KIND_COLD,
	XX_ACT_KIND_MIND,
	XX_ACT_KIND_ACID,

	XX_ACT_KIND_PARALYZE,
	XX_ACT_KIND_POISON,
	XX_ACT_KIND_SLEEP,

	XX_ACT_KIND_SLAP,

	XX_ACT_KIND_MAX_N,
} xx_act_kind_t;

/***************************************************************
* XX �β�Ǯ����
***************************************************************/

/* �����κ���� */
#define	XX_HEAT_MAX_N	8

typedef struct {
	long	head_x, head_y;
	long	blast_x[XX_HEAT_MAX_N];
	long	blast_y[XX_HEAT_MAX_N];
	long	blast_n[XX_HEAT_MAX_N];
	long	blast_m[XX_HEAT_MAX_N];
} xx_heat_t;

/***************************************************************
* XX �ο��乶��
***************************************************************/

typedef struct {
	long	laser_len;
	long	bit_x[MBR_MAX_N], bit_y[MBR_MAX_N];
	long	bit_mx[MBR_MAX_N], bit_my[MBR_MAX_N];
} xx_cold_t;

/***************************************************************
* XX ����������
***************************************************************/

#define	XX_MIND_IMAGE_MAX_N	5

typedef struct {
	long	rate;
	long	anime_n;
	long	refract_idx;
	long	refract_x[MBR_MAX_N][XX_MIND_IMAGE_MAX_N];
	long	refract_y[MBR_MAX_N][XX_MIND_IMAGE_MAX_N];
	long	refract_bgn_x[MBR_MAX_N];
	long	refract_bgn_y[MBR_MAX_N];
	long	refract_end_x[MBR_MAX_N];
	long	refract_end_y[MBR_MAX_N];
} xx_mind_t;

/***************************************************************
* XX ���ڻ�����
***************************************************************/

#define	XX_ACID_IMAGE_MAX_N	5
#define	XX_ACID_HOMING_FIX_POINT	256

typedef struct {
	long	homing_idx;
	long	homing_vx[MBR_MAX_N];
	long	homing_vy[MBR_MAX_N];
	long	homing_mx[MBR_MAX_N];
	long	homing_my[MBR_MAX_N];
	long	homing_x[MBR_MAX_N][XX_ACID_IMAGE_MAX_N];
	long	homing_y[MBR_MAX_N][XX_ACID_IMAGE_MAX_N];
} xx_acid_t;

/***************************************************************
* XX �β�ž�ƹ���
***************************************************************/

#define	XX_ROTATION_Q	30
#define	XX_ROTATION_VQ	10
#define	XX_ROTATION_VR	1
#define	XX_ROTATION_RING_MAX_N	4
#define	XX_ROTATION_MAX_N	(360 / XX_ROTATION_Q)
#define	XX_ROTATION_MAX_R	20
#define	XX_ROTATION_NEXT_R	(XX_ROTATION_MAX_R / XX_ROTATION_RING_MAX_N)

typedef struct {
	bool_t	flg_move[XX_ROTATION_RING_MAX_N];
	long	q[XX_ROTATION_RING_MAX_N];
	long	r[XX_ROTATION_RING_MAX_N];
	long	x[XX_ROTATION_RING_MAX_N][XX_ROTATION_MAX_N];
	long	y[XX_ROTATION_RING_MAX_N][XX_ROTATION_MAX_N];
} xx_rotation_t;

/***************************************************************
* XX �α������ƹ���
***************************************************************/

#define	XX_WHIRL_Q	10
#define	XX_WHIRL_VR	1
#define	XX_WHIRL_MAX_N	(360 / XX_WHIRL_Q)
#define	XX_WHIRL_MAX_R	15

typedef struct {
	long	head_n;
	bool_t	flg_move[XX_WHIRL_MAX_N];
	long	q[XX_WHIRL_MAX_N];
	long	r[XX_WHIRL_MAX_N];
	long	x[XX_WHIRL_MAX_N];
	long	y[XX_WHIRL_MAX_N];
} xx_whirl_t;

/***************************************************************
* XX �����ƹ���
***************************************************************/

#define	XX_FAN_Q	10
#define	XX_FAN_MAX_WAY	9
#define	XX_FAN_MAX_Q	(XX_FAN_Q * XX_FAN_MAX_WAY)
#define	XX_FAN_VR	1
#define	XX_FAN_DR	3
#define	XX_FAN_MAX_R	20
#define	XX_FAN_MAX_N	(XX_FAN_MAX_R / XX_FAN_VR / XX_FAN_DR)

typedef struct {
	long	head_n;
	bool_t	flg_move[XX_FAN_MAX_N];
	long	q[XX_FAN_MAX_WAY];
	long	r[XX_FAN_MAX_N];
	long	x[XX_FAN_MAX_N][XX_FAN_MAX_WAY];
	long	y[XX_FAN_MAX_N][XX_FAN_MAX_WAY];
} xx_fan_t;

/***************************************************************
* XX ��ʿ���Ǥ�����
***************************************************************/

#endif	/* LAST_BOSS_H */
