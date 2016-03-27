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
* $Id: key-item.h,v 1.5 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	KEY_ITEM_H
#define	KEY_ITEM_H

/***************************************************************
* �����������ƥ�
***************************************************************/

/* ���μ��μ��� */
typedef enum {
	STAR_DROP_KIND_ELEC,
	STAR_DROP_KIND_PHYS,
	STAR_DROP_KIND_HEAT,
	STAR_DROP_KIND_COLD,
	STAR_DROP_KIND_MIND,
	STAR_DROP_KIND_ACID,
	STAR_DROP_KIND_POIS,
	STAR_DROP_KIND_MAX_N,
} star_drop_kind_t;

/* �ѡ��ƥ������뵯ư���֤ο� */
#define	BOOT_UNIT_MAX_N	(STAR_DROP_KIND_MAX_N - 1)

#endif	/* KEY_ITEM_H */
