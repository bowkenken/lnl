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
	// �������롦�С�������

	WSCvscrBar *scr = (WSCvscrBar *)object->cast( "WSCvscrBar" );

	long maxX = MAP_MAX_X * gPcgDun.getTileSizeX();
	long w = (long)MapForm->getProperty( WSNwidth );

	scr->setProperty( WSNmaximum, maxX );
	scr->setProperty( WSNsliderSize, w );
	scr->setProperty( WSNincrement, gPcgDun.getTileSizeX() );
	scr->setProperty( WSNpageIncrement,
			gPcgDun.getTileSizeX() * AREA_MAX_X / 2 );

	// ����

	MapForm->execProcedure( "MapFormDraw" );
}
static WSCfunctionRegister  op("MapScrollXDraw",(void*)MapScrollXDraw);
