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
* $Id: IPhoneWSDmwindowDev.h,v 1.3 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef IPHONE_WSD_MWINDOW_DEV_H
#define IPHONE_WSD_MWINDOW_DEV_H	1

//#include <gtk/gtk.h>
//#include <gdk-pixbuf/gdk-pixbuf.h>

#include "IPhoneMisc.h"

class WSDmwindowDev
{
private:
	CGContextRef pPixMap;

public:
	WSDmwindowDev();
	static WSDmwindowDev *getNewInstance();

	void createPixmap( long nSizeX, long nSizeY );
	CGContextRef getPixMap();

	WSCbool getReady();

	void copyToWindow(
		WSDmwindowDev *dst,
		long srcX, long srcY,
		long w, long h,
		long dstX, long dstY );
};

#endif // IPHONE_WSD_MWINDOW_DEV_H
