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
* $Id: replay.h,v 1.9 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	REPLAY_H
#define	REPLAY_H

/***************************************************************
* ��ץ쥤
***************************************************************/

#define	REPLAY_BUF_MAX_LEN	50

typedef enum {
	REPLAY_KIND_KEY,
	REPLAY_KIND_GETS,
	REPLAY_KIND_MAX_N,
} replay_kind_t;

typedef enum {
	REPLAY_SLOT_NULL,
	REPLAY_SLOT_AUTO = REPLAY_SLOT_NULL,
	REPLAY_SLOT_BUG_REPO,
	REPLAY_SLOT_STD,
	REPLAY_SLOT_PLAY,
	REPLAY_SLOT_MAX_N,
} replay_slot_t;

typedef struct replay_t {
	struct replay_t	*next;
	replay_kind_t	kind;
	long	n;
	char	buf[REPLAY_BUF_MAX_LEN + 1];
} replay_t;

#endif	/* REPLAY_H */
