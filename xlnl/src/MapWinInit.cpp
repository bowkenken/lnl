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

	// GUI �⡼�ɤ� OFF ���ä��饦����ɥ����Ĥ���

	if( g_flg_gui ){
		object->setVisible( true );
	} else {
		object->setProperty( WSNwidth, 1 );
		object->setProperty( WSNheight, 1 );
		object->setProperty( WSNdet, false );
	}
}
static WSCfunctionRegister  op("MapWinInit",(void*)MapWinInit);
