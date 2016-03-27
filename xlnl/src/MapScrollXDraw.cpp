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
* $Id: MapScrollXDraw.cpp,v 1.8 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCvscrBar.h>
#include <WSCform.h>

#include "dun.h"

#include "GlobalVar.h"

extern WSCform *MapForm;

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MapScrollXDraw(WSCbase* object){
  //do something...
	// スクロール・バーの設定

	WSCvscrBar *scr = (WSCvscrBar *)object->cast( "WSCvscrBar" );

	long maxX = MAP_MAX_X * gPcgDun.getTileSizeX();
	long w = (long)MapForm->getProperty( WSNwidth );

	scr->setProperty( WSNmaximum, maxX );
	scr->setProperty( WSNsliderSize, w );
	scr->setProperty( WSNincrement, gPcgDun.getTileSizeX() );
	scr->setProperty( WSNpageIncrement,
			gPcgDun.getTileSizeX() * AREA_MAX_X / 2 );

	// 描画

	MapForm->execProcedure( "MapFormDraw" );
}
static WSCfunctionRegister  op("MapScrollXDraw",(void*)MapScrollXDraw);
