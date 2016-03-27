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
* $Id: item-kind.h,v 1.11 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	ITEM_KIND_H
#define	ITEM_KIND_H

/* �����ƥ�μ��� */

typedef enum {
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
	ITEM_KIND_BONE,
	ITEM_KIND_COIN,
	ITEM_KIND_JUNK,
	ITEM_KIND_MAX_N,
} item_kind_t;

#endif	/* ITEM_KIND_H */
