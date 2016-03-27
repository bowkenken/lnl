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
* $Id: MapWinInit.cpp,v 1.8 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSDappDev.h>

#include "main-x.h"
#include "draw.h"
#include "main-ws-prot.h"
#include "draw-prot.h"

#include "MouseMap.h"
#include "GlobalVar.h"

WSDappDev *WSGIappDev();

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MapWinInit(WSCbase* object){
  //do something...

	main_ws( WSGIappDev()->getArgc(), WSGIappDev()->getArgv() );
	gPcgDun.init();

	// GUI モードが OFF だったらウィンドウを閉じる

	if( g_flg_gui ){
		object->setVisible( true );
	} else {
		object->setProperty( WSNwidth, 1 );
		object->setProperty( WSNheight, 1 );
		object->setProperty( WSNdet, false );
	}
}
static WSCfunctionRegister  op("MapWinInit",(void*)MapWinInit);
