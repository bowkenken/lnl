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
* $Id: play-rep.h,v 1.3 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	PLAY_REP_H
#define	PLAY_REP_H

/* ���ץǡ��� */

#include	"stay-inn-kind.h"
#include	"item.h"
#include	"resi.h"
#include	"spell-kind.h"

typedef struct {
	gold_t	paying_gold;
	long	staying_inn[STAY_INN_KIND_MAX_N];
	long	wearing_equip[EQUIP_KIND_MAX_N];
	long	making_dam[RESI_KIND_MAX_N];
	long	made_dam[RESI_KIND_MAX_N];
	long	using_spell[SPELL_KIND_MAX_N];
	long	used_spell[SPELL_KIND_MAX_N];
} playing_report_t;

#endif	/* PLAY_REP_H */
