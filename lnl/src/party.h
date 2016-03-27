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
* $Id: party.h,v 1.28 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	PARTY_H
#define	PARTY_H

/* �ѡ��ƥ��ȥ��С� */

#include	"chr.h"
#include	"stay-inn-kind.h"

/* ���С� */

enum {
	LS_MBR_N_BLADE,
	LS_MBR_N_DRANK,
	LS_MBR_N_ELSIE,
	LS_MBR_N_CECILE,
	LS_MBR_N_HALLE,
	LS_MBR_N_BEAUT,
	LS_MBR_N_GOKOU,
	LS_MBR_N_EYE,
};

#define	MBR_MAX_N	6	/* ����� */
#define	MBR_N_NOT_JOIN	(-1)	/* �ѡ��ƥ��˲ä�äƤ��ʤ��� */
#define	MBR_NO_POS	(-1)	/* �ե����᡼�����ζ��� */

/* �ѡ��ƥ� */

#define	LS_MBR_MAX_N	64	/* ���С��κ�����Ͽ�� */

typedef unsigned long	flg_party_t;
#define	FLG_PARTY_ACTUAL_FIGHTING	(1 << 0)
#define	FLG_PARTY_SRCH_AUTO_OFF	(1 << 1)

typedef chr_t	mbr_t;

/* ���󥫡�(�ѡ��ƥ��ΰ�ư���濴) */

typedef enum {
	SQUARE_DIR_NORTH,
	SQUARE_DIR_EAST,
	SQUARE_DIR_SOUTH,
	SQUARE_DIR_WEST,
	SQUARE_DIR_MAX_N,
} square_dir_t;

typedef struct {
	/* ��ɸ */
	long	x, y;
	/* 1�����κ�ɸ */
	long	pre_x, pre_y;
	/* �����Ƥ������� */
	square_dir_t	dir;
	/* 1�����θ����Ƥ������� */
	square_dir_t	pre_dir;

	/* �������Ƥ�����������θ��� */
	long	chr_pos_n[SQUARE_HEIGHT][SQUARE_WIDTH];

	/* �ºݤθ��� */
	long	chr_dir[SQUARE_HEIGHT][SQUARE_WIDTH];

	/* ����饯���Υ��󥫡���������к�ɸ (���Υ��󥫡�) */
	pos_t	chr_rel_pos[MBR_MAX_N];
	/* ����饯���Υޥå׾�����к�ɸ (���Υ��󥫡�) */
	pos_t	chr_abs_pos[MBR_MAX_N];
	/* ����饯���Υޥå׾�����к�ɸ (���̥��󥫡�) */
	pos_t	chr_ind_pos[MBR_MAX_N];
	/* �ƥ���饯���Υ��󥫡���ɸ */
	pos_t	chr_map_pos[MBR_MAX_N];
	/* �ƥ���饯����1�����Υ��󥫡���ɸ */
	pos_t	chr_pre_pos[MBR_MAX_N];
} square_t;

/* �ѡ��ƥ� */

typedef struct {
	mbr_t	*mbr[MBR_MAX_N];	/* ���С� */
	square_t	square;	/* ���󥫡� */
	flg_party_t	flg;	/* �ե饰 */
	act_t	act;	/* �ѡ��ƥ����ΤΥ�������� */
} party_t;

#endif	/* PARTY_H */
