/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ������ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�������
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�������ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ������Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: MapFormMousePress.cpp,v 1.7 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCvscrBar.h>
#include <WSDmouse.h>

#include "MouseMotion.h"
#include "GlobalVar.h"

extern WSCvscrBar *MapScrollX;
extern WSCvscrBar *MapScrollY;

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MapFormMousePress(WSCbase* object){
  //do something...
	gMapDragBgnX = MapScrollX->getProperty( WSNvalue );
	gMapDragBgnY = MapScrollY->getProperty( WSNvalue );

	WSDmouse *mouse = WSGIappMouse();
	short x = 0, y = 0;
	mouse->getMousePosition( &x, &y, object );

	if( mouse->getMouseStatus() & WS_MOUSE_BTN1 )
		gMouseMotion.begin( MouseMotion::nMouseButton0, x, y );
	if( mouse->getMouseStatus() & WS_MOUSE_BTN2 )
		gMouseMotion.begin( MouseMotion::nMouseButton1, x, y );
	if( mouse->getMouseStatus() & WS_MOUSE_BTN3 )
		gMouseMotion.begin( MouseMotion::nMouseButton2, x, y );
	if( mouse->getMouseStatus() & WS_MOUSE_BTN4 )
		gMouseMotion.begin( MouseMotion::nMouseButton3, x, y );
	if( mouse->getMouseStatus() & WS_MOUSE_BTN5 )
		gMouseMotion.begin( MouseMotion::nMouseButton4, x, y );
}
static WSCfunctionRegister  op("MapFormMousePress",(void*)MapFormMousePress);