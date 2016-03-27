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
* $Id: GraphConf.cpp,v 1.9 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ����ե��å�����
////////////////////////////////////////////////////////////////

#define	GRAPH_CONF_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// ����ե��å�����Υ��󥹥ȥ饯��
////////////////////////////////////////////////////////////////

GraphConf::GraphConf()
{
	prev = NULL;
	next = NULL;

	sDir = "";

	title = "";
	scale = g_graph_scale_rate;
	tile_size_x = 32;
	tile_size_y = 32;
	character_patern = "";
	pc_patern = "";
	monster_patern = "";
	wall_patern = "";
	town_wall_patern = "";
	dungeon_wall_patern = "";
	door_patern = "";
	signboard_patern = "";
	text_mode = false;
	font_size_point = g_text_mode_point;
	font_size_dot = 16;
}

////////////////////////////////////////////////////////////////
// ����ե��å�����Υǥ��ȥ饯��
////////////////////////////////////////////////////////////////

GraphConf::~GraphConf()
{
}

////////////////////////////////////////////////////////////////
// �ꥹ�ȤΥإå��ˤ���
////////////////////////////////////////////////////////////////

void GraphConf::setHead()
{
	prev = this;
	next = this;
}

////////////////////////////////////////////////////////////////
// �ꥹ�Ȥ��������Ǥ��֤�
////////////////////////////////////////////////////////////////

GraphConf *GraphConf::getPrev()
{
	return prev;
}
////////////////////////////////////////////////////////////////
// �ꥹ�Ȥμ������Ǥ��֤�
////////////////////////////////////////////////////////////////

GraphConf *GraphConf::getNext()
{
	return next;
}

////////////////////////////////////////////////////////////////
// �ꥹ�Ȥ�����
// GraphConf *ls : ������Υꥹ��
////////////////////////////////////////////////////////////////

void GraphConf::insert( GraphConf *ls )
{
	if( this->prev != NULL )
		this->prev->next = this->next;
	if( this->next != NULL )
		this->next->prev = this->prev;

	if( ls == NULL ){
		this->prev = NULL;
		this->next = NULL;

		return;
	}

	this->prev = ls;
	this->next = ls->next;

	if( ls->next != NULL )
		ls->next->prev = this;
	ls->next = this;

	return;
}

////////////////////////////////////////////////////////////////
// ����ǥ��쥯�ȥ�̾������
// char *dir : ����ǥ��쥯�ȥ�̾
////////////////////////////////////////////////////////////////

void GraphConf::setDir( WSCstring dir )
{
	sDir = dir;
}

////////////////////////////////////////////////////////////////
// ����ǥ��쥯�ȥ�̾���֤�
// char *dir : ����ǥ��쥯�ȥ�̾
////////////////////////////////////////////////////////////////

WSCstring GraphConf::getDir()
{
	return sDir;
}

////////////////////////////////////////////////////////////////
// ���ͤ�����
// GraphConfToken token : �ȡ�����
// long n : ����
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool GraphConf::setNum( GraphConfToken token, long n )
{
	switch( token ){
	case GRAPH_CONF_TOKEN_NULL:
	case GRAPH_CONF_TOKEN_TITLE:
		break;
	case GRAPH_CONF_TOKEN_SCALE:
		scale = n;
		return true;
	case GRAPH_CONF_TOKEN_TILE_SIZE_X:
		tile_size_x = n;
		return true;
	case GRAPH_CONF_TOKEN_TILE_SIZE_Y:
		tile_size_y = n;
		return true;
	case GRAPH_CONF_TOKEN_CHARACTER_PATERN:
	case GRAPH_CONF_TOKEN_PC_PATERN:
	case GRAPH_CONF_TOKEN_MONSTER_PATERN:
	case GRAPH_CONF_TOKEN_WALL_PATERN:
	case GRAPH_CONF_TOKEN_TOWN_WALL_PATERN:
	case GRAPH_CONF_TOKEN_DUNGEON_WALL_PATERN:
	case GRAPH_CONF_TOKEN_DOOR_PATERN:
	case GRAPH_CONF_TOKEN_SIGNBOARD_PATERN:
		break;
	case GRAPH_CONF_TOKEN_TEXT_MODE:
		text_mode = (n != 0);
		return true;
	case GRAPH_CONF_TOKEN_FONT_SIZE_POINT:
		font_size_point = n;
	case GRAPH_CONF_TOKEN_FONT_SIZE_DOT:
		font_size_dot = n;
		return true;
	case GRAPH_CONF_TOKEN_MAX_N:
		break;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ʸ���������
// GraphConfToken token : �ȡ�����
// WSCstring str : ʸ����
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool GraphConf::setStr( GraphConfToken token, WSCstring str )
{
	switch( token ){
	case GRAPH_CONF_TOKEN_NULL:
		break;
	case GRAPH_CONF_TOKEN_TITLE:
		title = str;
		return true;
	case GRAPH_CONF_TOKEN_SCALE:
	case GRAPH_CONF_TOKEN_TILE_SIZE_X:
	case GRAPH_CONF_TOKEN_TILE_SIZE_Y:
		break;
	case GRAPH_CONF_TOKEN_CHARACTER_PATERN:
		character_patern = str;
		return true;
	case GRAPH_CONF_TOKEN_PC_PATERN:
		pc_patern = str;
		return true;
	case GRAPH_CONF_TOKEN_MONSTER_PATERN:
		monster_patern = str;
		return true;
	case GRAPH_CONF_TOKEN_WALL_PATERN:
		wall_patern = str;
		return true;
	case GRAPH_CONF_TOKEN_TOWN_WALL_PATERN:
		town_wall_patern = str;
		return true;
	case GRAPH_CONF_TOKEN_DUNGEON_WALL_PATERN:
		dungeon_wall_patern = str;
		return true;
	case GRAPH_CONF_TOKEN_DOOR_PATERN:
		door_patern = str;
		return true;
	case GRAPH_CONF_TOKEN_SIGNBOARD_PATERN:
		signboard_patern = str;
		return true;
	case GRAPH_CONF_TOKEN_TEXT_MODE:
	case GRAPH_CONF_TOKEN_FONT_SIZE_POINT:
	case GRAPH_CONF_TOKEN_FONT_SIZE_DOT:
		break;
	case GRAPH_CONF_TOKEN_MAX_N:
		break;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// �ѿ��ο��ͤ��֤�
// GraphConfToken token : �ȡ�����
// return : ����
////////////////////////////////////////////////////////////////

long GraphConf::getNum( GraphConfToken token )
{
	switch( token ){
	case GRAPH_CONF_TOKEN_NULL:
	case GRAPH_CONF_TOKEN_TITLE:
		break;
	case GRAPH_CONF_TOKEN_SCALE:
		return scale;
	case GRAPH_CONF_TOKEN_TILE_SIZE_X:
		return tile_size_x;
	case GRAPH_CONF_TOKEN_TILE_SIZE_Y:
		return tile_size_y;
	case GRAPH_CONF_TOKEN_CHARACTER_PATERN:
	case GRAPH_CONF_TOKEN_PC_PATERN:
	case GRAPH_CONF_TOKEN_MONSTER_PATERN:
	case GRAPH_CONF_TOKEN_WALL_PATERN:
	case GRAPH_CONF_TOKEN_TOWN_WALL_PATERN:
	case GRAPH_CONF_TOKEN_DUNGEON_WALL_PATERN:
	case GRAPH_CONF_TOKEN_DOOR_PATERN:
	case GRAPH_CONF_TOKEN_SIGNBOARD_PATERN:
		break;
	case GRAPH_CONF_TOKEN_TEXT_MODE:
		return text_mode;
	case GRAPH_CONF_TOKEN_FONT_SIZE_POINT:
		return font_size_point;
	case GRAPH_CONF_TOKEN_FONT_SIZE_DOT:
		return font_size_dot;
	case GRAPH_CONF_TOKEN_MAX_N:
		break;
	}

	return 0;
}

////////////////////////////////////////////////////////////////
// �ѿ���ʸ������֤�
// GraphConfToken token : �ȡ�����
// return : ʸ����
////////////////////////////////////////////////////////////////

WSCstring GraphConf::getStr( GraphConfToken token )
{
	switch( token ){
	case GRAPH_CONF_TOKEN_NULL:
		break;
	case GRAPH_CONF_TOKEN_TITLE:
		return title;
	case GRAPH_CONF_TOKEN_SCALE:
	case GRAPH_CONF_TOKEN_TILE_SIZE_X:
	case GRAPH_CONF_TOKEN_TILE_SIZE_Y:
		break;
	case GRAPH_CONF_TOKEN_CHARACTER_PATERN:
		return character_patern;
	case GRAPH_CONF_TOKEN_PC_PATERN:
		return pc_patern;
	case GRAPH_CONF_TOKEN_MONSTER_PATERN:
		return monster_patern;
	case GRAPH_CONF_TOKEN_WALL_PATERN:
		return wall_patern;
	case GRAPH_CONF_TOKEN_TOWN_WALL_PATERN:
		return town_wall_patern;
	case GRAPH_CONF_TOKEN_DUNGEON_WALL_PATERN:
		return dungeon_wall_patern;
	case GRAPH_CONF_TOKEN_DOOR_PATERN:
		return door_patern;
	case GRAPH_CONF_TOKEN_SIGNBOARD_PATERN:
		return signboard_patern;
	case GRAPH_CONF_TOKEN_TEXT_MODE:
	case GRAPH_CONF_TOKEN_FONT_SIZE_POINT:
	case GRAPH_CONF_TOKEN_FONT_SIZE_DOT:
		break;
	case GRAPH_CONF_TOKEN_MAX_N:
		break;
	}

	return "";
}
