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
