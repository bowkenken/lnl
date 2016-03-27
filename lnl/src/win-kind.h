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
* $Id: win-kind.h,v 1.10 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef WIN_KIND_H
#define WIN_KIND_H

typedef enum {
	WIN_KIND_NULL,
	WIN_KIND_MAP,
	WIN_KIND_SEL_CONF,
	WIN_KIND_MENU,
	WIN_KIND_MESSAGE,
	WIN_KIND_STAT,
	WIN_KIND_STAT_1,
	WIN_KIND_STAT_2,
	WIN_KIND_STAT_3,
	WIN_KIND_STAT_4,
	WIN_KIND_STAT_5,
	WIN_KIND_STAT_6,
	WIN_KIND_INPUT_NUM,
	WIN_KIND_INPUT_STRING,
	WIN_KIND_WORDS,
	WIN_KIND_REPLAY,
	WIN_KIND_CLASS_EDIT,
	WIN_KIND_SKILL_EDIT,
	WIN_KIND_CHR_SHEET,
	WIN_KIND_MAX_N,
} win_kind_t;

#endif /* WIN_KIND_H */
