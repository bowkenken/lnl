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
* $Id: GraphConfToken.h,v 1.8 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GRAPH_CONF_TOKEN_H
#define GRAPH_CONF_TOKEN_H	1

typedef enum {
	GRAPH_CONF_TOKEN_NULL,
	GRAPH_CONF_TOKEN_TITLE,
	GRAPH_CONF_TOKEN_SCALE,
	GRAPH_CONF_TOKEN_TILE_SIZE_X,
	GRAPH_CONF_TOKEN_TILE_SIZE_Y,
	GRAPH_CONF_TOKEN_CHARACTER_PATERN,
	GRAPH_CONF_TOKEN_PC_PATERN,
	GRAPH_CONF_TOKEN_MONSTER_PATERN,
	GRAPH_CONF_TOKEN_WALL_PATERN,
	GRAPH_CONF_TOKEN_TOWN_WALL_PATERN,
	GRAPH_CONF_TOKEN_DUNGEON_WALL_PATERN,
	GRAPH_CONF_TOKEN_DOOR_PATERN,
	GRAPH_CONF_TOKEN_SIGNBOARD_PATERN,
	GRAPH_CONF_TOKEN_TEXT_MODE,
	GRAPH_CONF_TOKEN_FONT_SIZE_POINT,
	GRAPH_CONF_TOKEN_FONT_SIZE_DOT,
	GRAPH_CONF_TOKEN_MAX_N,
} GraphConfToken;

#endif /* GRAPH_CONF_TOKEN_H */
