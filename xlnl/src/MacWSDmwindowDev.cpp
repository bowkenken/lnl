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
