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
* $Id: class-tab.h,v 1.10 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	CLASS_TAB_H
#define	CLASS_TAB_H

/* ���饹 */

#include	"party.h"
#include	"msg.h"

/**/

/* �ǥե���ȤΥ��饹�μ��� */

enum {
	CLASS_N_FIGHTER,
	CLASS_N_MONK,
	CLASS_N_HUNTER,
	CLASS_N_THIEF,
	CLASS_N_WIZARD,
	CLASS_N_SUMMONER,
	CLASS_N_PRIEST,
	CLASS_N_SHAMAN,
	CLASS_N_BARD,
	CLASS_N_NINJA,
	CLASS_N_BISHOP,
};

/* ���饹���ǡ��� */

class_t	class_tab[CLASS_MAX_N + 1];

class_t	class_dflt_tab[] = {
#include	"class-dflt-tab.h"
};

#endif	/* CLASS_TAB_H */
