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
* $Id: music-kind.h,v 1.6 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	MUSIC_KIND_KIND_H
#define	MUSIC_KIND_KIND_H

/* BGM (Back Ground Music) �μ��� */

typedef enum {
	MUSIC_KIND_NULL,

	MUSIC_KIND_TITLE,
	MUSIC_KIND_GAME_OVER,
	MUSIC_KIND_ENDING,
	MUSIC_KIND_THE_END,
	MUSIC_KIND_TOWN,
	MUSIC_KIND_SHOP,
	MUSIC_KIND_DUN,
	MUSIC_KIND_LAST_BOSS,
	MUSIC_KIND_BATTLE,
	MUSIC_KIND_BATTLE_BOSS,
	MUSIC_KIND_BATTLE_LAST_BOSS,
	MUSIC_KIND_EFFECT,

	MUSIC_KIND_MAX_N,
} music_kind_t;

/* ME (Music Effect) �μ��� */

typedef enum {
	ME_KIND_NULL,

	ME_KIND_INN,
	ME_KIND_TEMPLE,

	ME_KIND_MAX_N,
} me_kind_t;

#endif	/* MUSIC_KIND_KIND_H */
