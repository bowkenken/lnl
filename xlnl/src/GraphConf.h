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
* $Id: GraphConf.h,v 1.10 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GRAPH_CONF_H
#define GRAPH_CONF_H	1

////////////////////////////////////////////////////////////////
// ����ե��å�����
////////////////////////////////////////////////////////////////

#ifdef D_WS
# include <WSCstring.h>
#endif // D_WS

#ifdef D_GTK
# include "GtkWSCstring.h"
#endif // D_GTK

#ifdef D_MAC
# include "MacWSCstring.h"
#endif // D_MAC

#ifdef D_IPHONE
# include "IPhoneWSCstring.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif // D_GTK

#include "GraphConfToken.h"

////////////////////////////////////////////////////////////////

class GraphConf {

	// �ץ饤�١��ȡ����С��ѿ�
private:

	GraphConf *prev;
	GraphConf *next;

	WSCstring sDir;

	WSCstring title;
	long scale;
	long tile_size_x;
	long tile_size_y;
	WSCstring character_patern;
	WSCstring pc_patern;
	WSCstring monster_patern;
	WSCstring wall_patern;
	WSCstring town_wall_patern;
	WSCstring dungeon_wall_patern;
	WSCstring door_patern;
	WSCstring signboard_patern;
	bool text_mode;
	long font_size_point;
	long font_size_dot;

	// �ѥ֥�å������С��ѿ�
public:

	// �ѥ֥�å������С��ؿ�
public:

	GraphConf();
	~GraphConf();

	void setHead();
	GraphConf *getPrev();
	GraphConf *getNext();
	void insert( GraphConf *ls );

	void setDir( WSCstring dir );
	WSCstring getDir();

	bool setNum( GraphConfToken token, long n );
	bool setStr( GraphConfToken token, WSCstring str );
	long getNum( GraphConfToken token );
	WSCstring getStr( GraphConfToken token );

	// �ץ饤�١��ȡ����С��ؿ�
private:

};

#endif /* GRAPH_CONF_H */
