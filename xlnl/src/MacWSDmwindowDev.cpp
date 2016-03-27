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
* $Id: MacWSDmwindowDev.cpp,v 1.3 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#include "MacWSDmwindowDev.h"
#include "GlobalVar.h"

WSDmwindowDev::WSDmwindowDev()
{
	pPixMap = NULL;
}

WSDmwindowDev *WSDmwindowDev::getNewInstance()
{
	return( new WSDmwindowDev );
}

void WSDmwindowDev::createPixmap( long nSizeX, long nSizeY )
{
	long w = nSizeX;
	long h = nSizeY;
#if 1
//@@@
	void *frameBuf = malloc( w * h * 4 );

	CGColorSpaceRef col = CGColorSpaceCreateDeviceRGB();
	pPixMap = CGBitmapContextCreate( frameBuf, w, h, 8, 4 * w, col, kCGImageAlphaPremultipliedFirst );
	CGColorSpaceRelease( col );

	//CGContextTranslateCTM( pPixMap, 0.0, rect.size.height );
	CGContextScaleCTM( pPixMap, 1.0, -1.0 );
#else
	pPixMap = [[NSImage alloc] initWithSize:NSMakeSize( w, h )];
#endif
}

CGContextRef WSDmwindowDev::getPixMap()
{
	return pPixMap;
}

WSCbool WSDmwindowDev::getReady()
{
	return true;
}

void WSDmwindowDev::copyToWindow(
	WSDmwindowDev *dst,
	long srcX, long srcY,
	long w, long h,
	long dstX, long dstY )
{
	if( dst == NULL )
		return;

	if( pPixMap == NULL )
		return;

#if	0
//@@@
	GdkGC *gc = gMapDrawingArea->style->fg_gc[GTK_STATE_NORMAL];

	gdk_draw_pixmap(
			dst->getPixMap(),
			gc,
			pPixMap,
			srcX, srcY,
			dstX, dstY,
			w, h );
#elif 0
	NSImage *dstImg = dst->getPixMap();
	[dstImg lockFocus];
	[pPixMap dissolveToPoint:NSMakePoint( dstX, dstY ) fromRect:NSMakeRect( srcX, srcY, w, h ) fraction:1.0];
	[dstImg unlockFocus];
#endif
}
