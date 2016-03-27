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
* $Id: MapFormMouseRellease.cpp,v 1.7 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSDmouse.h>

#include "MouseMotion.h"
#include "GlobalVar.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MapFormMouseRellease(WSCbase* object){
  //do something...
	WSDmouse *mouse = WSGIappMouse();
	short x = 0, y = 0;
	mouse->getMousePosition( &x, &y, object );

	if( !(mouse->getMouseStatus() & WS_MOUSE_BTN1) )
		gMouseMotion.end( MouseMotion::nMouseButton0, x, y );
	if( !(mouse->getMouseStatus() & WS_MOUSE_BTN2) )
		gMouseMotion.end( MouseMotion::nMouseButton1, x, y );
	if( !(mouse->getMouseStatus() & WS_MOUSE_BTN3) )
		gMouseMotion.end( MouseMotion::nMouseButton2, x, y );
	if( !(mouse->getMouseStatus() & WS_MOUSE_BTN4) )
		gMouseMotion.end( MouseMotion::nMouseButton3, x, y );
	if( !(mouse->getMouseStatus() & WS_MOUSE_BTN5) )
		gMouseMotion.end( MouseMotion::nMouseButton4, x, y );
}
static WSCfunctionRegister  op("MapFormMouseRellease",(void*)MapFormMouseRellease);
