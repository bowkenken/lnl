/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* 本プログラムはフリー・ソフトウェアです。
* あなたは、 Free Software Foundation が公表した
*  GNU 一般公有使用許諾の「バージョン２」
* 或はそれ以降の各バージョンの中からいずれかを選択し、
* そのバージョンが定める条項に従って本プログラムを
* 再頒布または変更することができます。
* 
* 本プログラムは有用とは思いますが、頒布にあたっては、
* 市場性及び特定目的適合性についての暗黙の保証を含めて,
* いかなる保証も行ないません。
* 詳細については GNU 一般公有使用許諾書をお読みください。
* 
* あなたは、本プログラムと一緒に GNU 一般公有使用許諾書
* の写しを受け取っているはずです。そうでない場合は、
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* へ手紙を書いてください。
* 
* $Id: GraphConf.cpp,v 1.9 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// グラフィック設定
////////////////////////////////////////////////////////////////

#define	GRAPH_CONF_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// グラフィック設定のコンストラクタ
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
// グラフィック設定のデストラクタ
////////////////////////////////////////////////////////////////

GraphConf::~GraphConf()
{
}

////////////////////////////////////////////////////////////////
// リストのヘッダにする
////////////////////////////////////////////////////////////////

void GraphConf::setHead()
{
	prev = this;
	next = this;
}

////////////////////////////////////////////////////////////////
// リストの前の要素を返す
////////////////////////////////////////////////////////////////

GraphConf *GraphConf::getPrev()
{
	return prev;
}
////////////////////////////////////////////////////////////////
// リストの次の要素を返す
////////////////////////////////////////////////////////////////

GraphConf *GraphConf::getNext()
{
	return next;
}

////////////////////////////////////////////////////////////////
// リストへ挿入
// GraphConf *ls : 挿入先のリスト
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
// 設定ディレクトリ名を設定
// char *dir : 設定ディレクトリ名
////////////////////////////////////////////////////////////////

void GraphConf::setDir( WSCstring dir )
{
	sDir = dir;
}

////////////////////////////////////////////////////////////////
// 設定ディレクトリ名を返す
// char *dir : 設定ディレクトリ名
////////////////////////////////////////////////////////////////

WSCstring GraphConf::getDir()
{
	return sDir;
}

////////////////////////////////////////////////////////////////
// 数値を設定
// GraphConfToken token : トークン
// long n : 数値
// return : エラーが無かったか?
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
// 文字列を設定
// GraphConfToken token : トークン
// WSCstring str : 文字列
// return : エラーが無かったか?
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
// 変数の数値を返す
// GraphConfToken token : トークン
// return : 数値
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
// 変数の文字列を返す
// GraphConfToken token : トークン
// return : 文字列
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
