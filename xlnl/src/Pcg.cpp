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
* $Id: Pcg.cpp,v 1.35 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#include <time.h>

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/MainFrm.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/Dir3d.h"
#endif // D_MFC

#include "gmain.h"
#include "misc.h"
#include "draw.h"
#include "town.h"
#include "amenu.h"
#include "spell.h"
#include "gfile.h"
#include "play-rep.h"
#include "gmain-prot.h"
#include "misc-prot.h"
#include "draw-prot.h"
#include "gfile-prot.h"
#include "play-rep-prot.h"

#include "Pcg.h"
#include "GlobalVar.h"

////////////////////////////////////////////////////////////////
// �����
// WSCstring path : ����ե��å����ե���������Хѥ�
////////////////////////////////////////////////////////////////

void Pcg::init( WSCstring path )
{
	load( path );
}

////////////////////////////////////////////////////////////////
// ����ե��å����ե�������ɤ߹���
// WSCstring path : ����ե��å����ե���������Хѥ�
////////////////////////////////////////////////////////////////

void Pcg::load( WSCstring path )
{
	if( pImage != NULL ){
		pImage->destroyImage();
		delete pImage;
		pImage = NULL;
	}

	dis();

	sPath = path;

	WSCstring dir = path;
	long pos = dir.getWordCharPos(
			dir.getWords( "/" ), "/" ) - 1;
	if( pos > 0 ){
		dir.cutString( pos );
		make_dir( dir );
	}

#ifdef D_WS
	pImage = WSGIappImageSet()->getImage( path );
#endif // D_WS

#ifdef D_GTK
	GdkPixbuf *buf = gdk_pixbuf_new_from_file( path, NULL );
	long w = gdk_pixbuf_get_width( buf );
	long h = gdk_pixbuf_get_height( buf );
	w = w * gPcgDun.nTileSizeRate / _100_PERCENT;
	h = h * gPcgDun.nTileSizeRate / _100_PERCENT;
	buf = gdk_pixbuf_scale_simple( buf, w, h, GDK_INTERP_BILINEAR );

	pImage = new WSDimage( buf );

	// ����Ѥο���ȴ�����ˤ���

	WSCstring ext = FileList::getExt( path );
	do {
		if( (ext != "bmp") && (ext != "BMP") )
			break;

		guchar *pix = gdk_pixbuf_get_pixels( buf );
		if( pix == NULL )
			break;
		guchar r = pix[0];
		guchar g = pix[1];
		guchar b = pix[2];

		GdkPixbuf *oldBuf = buf;
		buf = gdk_pixbuf_add_alpha( buf, TRUE, r, g, b );
		if( buf == NULL )
			break;
		pImage->setPixbuf( buf );
		g_object_unref( oldBuf );

		break;
	} while( 0 );
#endif // D_GTK

#ifdef D_MAC
#if 0
	NSString *pathStr = [NSString stringWithUTF8String:(const char *)path];
	CGImageRef buf = [[CGImage alloc] initWithContentsOfFile:pathStr];
#elif 1
	NSString *pathStr = [NSString stringWithUTF8String:(const char *)path];
	NSImage *tmpUIImg = [[NSImage alloc] initWithContentsOfFile:pathStr];
	CGImageRef tmpCGImg = [tmpUIImg CGImageForProposedRect:nil context:nil hints:nil];
	
	NSImage *buf = tmpUIImg;
#elif 0
	NSString *pathStr = [NSString stringWithUTF8String:(const char *)path];
	NSImage *tmpUIImg = [[NSImage alloc] initWithContentsOfFile:pathStr];
	CGImageRef tmpCGImg = tmpUIImg.CGImage;
	
	UIImage *buf = tmpUIImg;
#else
	NSString *pathStr = [NSString stringWithUTF8String:(const char *)path];
	NSImage *tmpUIImg = [[NSImage alloc] initWithContentsOfFile:pathStr];

	NSImage *buf = tmpUIImg;
#endif

	// ����Ѥο���ȴ�����ˤ���

#if 0
//@@@
	WSCstring ext = FileList::getExt( path );
	do {
		if( (ext != "bmp") && (ext != "BMP") )
			break;

		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

		long w = CGImageGetWidth(tmpCGImg);
		long h = CGImageGetHeight(tmpCGImg);
		unsigned char *frameBuf = (unsigned char*)malloc(w * h * 4);

		CGContextRef tmpContext = CGBitmapContextCreate(frameBuf, w, h, 8, w * 4, colorSpace, kCGImageAlphaPremultipliedLast);
		CGContextDrawImage(tmpContext, CGRectMake(0, 0, w, h), tmpCGImg);
		CGContextRelease(tmpContext);

		CGColorSpaceRelease(colorSpace);

		CGFloat compo[4];
		compo[0] = (CGFloat)(frameBuf[0] / 255.0f);
		compo[1] = (CGFloat)(frameBuf[1] / 255.0f);
		compo[2] = (CGFloat)(frameBuf[2] / 255.0f);
		compo[3] = (CGFloat)255.0f;
		
		CGImageRef tmpCGImg2 = CGImageCreateWithMaskingColors(tmpCGImg, compo);
		[buf release];
		buf = [UIImage imageWithCGImage:tmpCGImg2];

		break;
	} while( 0 );

	pImage = new WSDimage( buf );
#else
	WSCstring ext = FileList::getExt( path );
	do {
		if( (ext != "bmp") && (ext != "BMP") )
			break;
		
		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
		
		long w = CGImageGetWidth(tmpCGImg);
		long h = CGImageGetHeight(tmpCGImg);
		unsigned char *frameBuf = (unsigned char*)malloc(w * h * 4);
		
		CGContextRef tmpContext = CGBitmapContextCreate(frameBuf, w, h, 8, w * 4, colorSpace, kCGImageAlphaPremultipliedLast);
		CGContextDrawImage(tmpContext, CGRectMake(0, 0, w, h), tmpCGImg);
		CGContextRelease(tmpContext);
		
		CGColorSpaceRelease(colorSpace);
		
		CGFloat compo[4];
		compo[0] = (CGFloat)(frameBuf[0] / 255.0f);
		compo[1] = (CGFloat)(frameBuf[1] / 255.0f);
		compo[2] = (CGFloat)(frameBuf[2] / 255.0f);
		compo[3] = (CGFloat)255.0f;
		
		CGImageRef tmpCGImg2 = CGImageCreateWithMaskingColors(tmpCGImg, compo);
		[buf release];
		buf = [[NSImage alloc] initWithCGImage:tmpCGImg2 size:NSZeroSize];
		
		break;
	} while( 0 );
	
	pImage = new WSDimage( buf );
#endif //@@@
#endif // D_MAC

#ifdef D_IPHONE
	NSString *pathStr = [NSString stringWithUTF8String:(const char *)path];
	UIImage *tmpUIImg = [[UIImage alloc] initWithContentsOfFile:pathStr];
	CGImageRef tmpCGImg = tmpUIImg.CGImage;

	UIImage *buf = tmpUIImg;

	// ����Ѥο���ȴ�����ˤ���

	WSCstring ext = FileList::getExt( path );
	do {
		if( (ext != "bmp") && (ext != "BMP") )
			break;

		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

		long w = CGImageGetWidth(tmpCGImg);
		long h = CGImageGetHeight(tmpCGImg);
		unsigned char *frameBuf = (unsigned char*)malloc(w * h * 4);

		CGContextRef tmpContext = CGBitmapContextCreate(frameBuf, w, h, 8, w * 4, colorSpace, kCGImageAlphaPremultipliedLast);
		CGContextDrawImage(tmpContext, CGRectMake(0, 0, w, h), tmpCGImg);
		CGContextRelease(tmpContext);

		CGColorSpaceRelease(colorSpace);

		CGFloat compo[4];
		compo[0] = (CGFloat)(frameBuf[0] / 255.0f);
		compo[1] = (CGFloat)(frameBuf[1] / 255.0f);
		compo[2] = (CGFloat)(frameBuf[2] / 255.0f);
		compo[3] = (CGFloat)255.0f;
		
		CGImageRef tmpCGImg2 = CGImageCreateWithMaskingColors(tmpCGImg, compo);
		[buf release];
		buf = [UIImage imageWithCGImage:tmpCGImg2];

		break;
	} while( 0 );

	pImage = new WSDimage( buf );
#endif // D_IPHONE

#ifdef D_MFC
	pImage = NULL;

	LPDIRECT3DDEVICE9 pDev = g_Dir3d.pDir3dDevice;
	if( pDev == NULL )
		return;

	D3DXIMAGE_INFO info;
	pImage = new WSDimage();
	LPDIRECT3DTEXTURE9 *ppPixbuf = pImage->getPixbufPtr();
	D3DCOLOR color = 0;

	// *.bmp ���ɤߤ��ƺ���Ѥο���ȴ�����ˤ���

	WSCstring ext = FileList::getExt( path );
	do {
		if( (ext != "bmp") && (ext != "BMP") )
			break;

		HRESULT hResult = ::D3DXCreateTextureFromFileEx(
				pDev, path, D3DX_DEFAULT, D3DX_DEFAULT,
				1, 0,
				D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
				D3DX_FILTER_NONE, D3DX_DEFAULT,
				0, &info, 0, ppPixbuf );
		if( FAILED( hResult ) )
			break;

		LPDIRECT3DTEXTURE9 pPixbuf = pImage->getPixbuf();
		D3DSURFACE_DESC desc;
		if( pPixbuf->GetLevelDesc( 0, &desc ) != D3D_OK )
			break;

		// ��å�
		D3DLOCKED_RECT rect;
		pPixbuf->LockRect( 0, &rect, NULL, 0 );

		// �ԥ���������
		DWORD *buf = (DWORD *)(rect.pBits);
		color = CDir3d::CvDwordToColor( buf[0] );

		// �����å�
		pPixbuf->UnlockRect( 0 );
		pPixbuf->Release();

		break;
	} while( 0 );

	// ���ɤ�
	HRESULT hResult = ::D3DXCreateTextureFromFileEx(
			pDev, path, D3DX_DEFAULT, D3DX_DEFAULT,
			1, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
			D3DX_FILTER_NONE, D3DX_DEFAULT,
			color, &info, 0, ppPixbuf );
	if( FAILED( hResult ) ){
		delete pImage;
		pImage = NULL;

		return;
	}
	pImage->setTextureSize();
	pImage->setImageSize( info.Width, info.Height );
#endif // D_MFC

#ifdef D_WS
	nWidth = pImage->getImageWidth();
	nHeight = pImage->getImageHeight();
#endif // D_WS

#ifdef D_GTK
	nWidth = pImage->getImageWidth();
	nHeight = pImage->getImageHeight();
#endif // D_GTK

#ifdef D_MAC
	nWidth = pImage->getImageWidth();
	nHeight = pImage->getImageHeight();
#endif // D_MAC

#ifdef D_IPHONE
	nWidth = pImage->getImageWidth();
	nHeight = pImage->getImageHeight();
#endif // D_IPHONE

#ifdef D_MFC
	nWidth = pImage->getImageWidth();
	nHeight = pImage->getImageHeight();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ����ե��å����ǡ�����ͭ����
////////////////////////////////////////////////////////////////

void Pcg::ena()
{
}

////////////////////////////////////////////////////////////////
// ����ե��å����ǡ�����̵����
////////////////////////////////////////////////////////////////

void Pcg::dis()
{
return;//@@@
	if( pImage != NULL ){
		pImage->destroyImage();
	}
}

////////////////////////////////////////////////////////////////
// ����ե��å����ѥ�����Υѥ�̾���֤�
// return : �ѥ�̾
////////////////////////////////////////////////////////////////

WSCstring Pcg::getPath()
{
	return sPath;
}

////////////////////////////////////////////////////////////////
// ����ե��å����ѥ�����Υե�����̾���֤�
// return : �ե�����̾
////////////////////////////////////////////////////////////////

WSCstring Pcg::getName()
{
	return( FileList::getFileName( sPath ) );
}

////////////////////////////////////////////////////////////////
// ����ե��å����ѥ�����������֤�
// return : ��
////////////////////////////////////////////////////////////////

long Pcg::getWidth()
{
	if( pImage == NULL )
		return 0;

	return nWidth;
}

////////////////////////////////////////////////////////////////
// ����ե��å����ѥ�����ι⤵���֤�
// return : �⤵
////////////////////////////////////////////////////////////////

long Pcg::getHeight()
{
	if( pImage == NULL )
		return 0;

	return nHeight;
}

////////////////////////////////////////////////////////////////
// �����ǽ�Ԥ�
// WSDmwindowDev *mDev : �ե졼�ࡦ�Хåե��ʥ�����ɥ�����
// return : false �ʤ�����ڤ�
////////////////////////////////////////////////////////////////

bool Pcg::waitReady( WSDmwindowDev *mDev )
{
return true;//@@@
	if( mDev == NULL )
		return false;

	double frame = (double)*get_clk_tck();
	frame = frame * (double)nWaitReadyMSec / 1000.0;
	clock_t end_clock = clock() + (clock_t)frame;

	while( clock() < end_clock ){
		if( mDev->getReady() )
			return true;
	}

//@@@	mDev->endDraw();

	return false;
}

////////////////////////////////////////////////////////////////
// ����ե����֥��ɤγ���
// return : ����ե����֥��ɤ�ɬ�פ�ͭ��ѥ����󤫡�
////////////////////////////////////////////////////////////////

bool Pcg::beginAlpha()
{
#ifdef D_MFC
	g_Dir3d.BeginAlpha();
#endif // D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// ����ե����֥��ɤν�λ
// return : ����ե����֥��ɤ�ɬ�פ�ͭ��ѥ����󤫡�
////////////////////////////////////////////////////////////////

bool Pcg::endAlpha()
{
#ifdef D_MFC
	g_Dir3d.EndAlpha();
#endif // D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// ����ե��å����ѥ����������
// WSDmwindowDev *mDev : �ե졼�ࡦ�Хåե��ʥ�����ɥ�����
// long x : X ��ɸ
// long y : Y ��ɸ
// long w : W ��
// long h : H �⤵
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool Pcg::draw( WSDmwindowDev *mDev,
		long x, long y, long w, long h )
{
	ena();

	if( mDev == NULL )
		return false;
	if( pImage == NULL )
		return false;
	if( w < 1 )
		return true;
	if( h < 1 )
		return true;

	beginAlpha();

#ifdef D_WS
	mDev->beginDraw( x, y, w, h );
	mDev->drawImage( x, y, w, h, pImage, WS_LEFT_TOP );
	mDev->endDraw();
#endif // D_WS

#ifdef D_GTK
	GdkGC *gc = gMapDrawingArea->style->fg_gc[GTK_STATE_NORMAL];

	gdk_pixbuf_render_to_drawable(
			pImage->getPixbuf(),
			mDev->getPixMap(),
			gc,
			0, 0,
			x, y,
			w, h,
			GDK_RGB_DITHER_NONE,
			0, 0 );
#endif // D_GTK

#ifdef D_MAC
#if 0
//@@@
	y = MAP_MAX_Y * 32 - y - h;
	long srcY = pImage->getImageHeight() - h;
	
	NSImage *pcgCGImage = pImage->getPixbuf();
	NSImage *context = mDev->getPixMap();
	
	[context lockFocus];
	[pcgCGImage dissolveToPoint:NSMakePoint( x, y ) fromRect:NSMakeRect( 0.0, srcY, w, h ) fraction:1.0];
	[context unlockFocus];
#else
	NSImage *pcgUIImage = pImage->getPixbuf();
	CGImageRef pcgCGImage = [pcgUIImage CGImageForProposedRect:nil context:nil hints:nil];
	CGContextRef context = mDev->getPixMap();

	CGRect pcgRect;
	pcgRect.size.width = [pcgUIImage size].width;
	pcgRect.size.height = [pcgUIImage size].height;

	CGRect clipRect;
	clipRect.origin.x = x;
	clipRect.origin.y = -y - h;
	clipRect.size.width = w;
	clipRect.size.height = h;

	pcgRect.origin.x = x;
	pcgRect.origin.y = -y - h;

	CGContextSaveGState(context);
	CGContextClipToRect(context, clipRect);
	CGContextDrawImage(context, pcgRect, pcgCGImage);
	CGContextRestoreGState(context);
#endif //@@@
#endif // D_MAC

#ifdef D_IPHONE
	UIImage *pcgUIImage = pImage->getPixbuf();
	CGImageRef pcgCGImage = pcgUIImage.CGImage;
	CGContextRef context = mDev->getPixMap();
	
	CGRect pcgRect;
	pcgRect.size = pcgUIImage.size;

	CGRect clipRect;
	clipRect.origin.x = x;
	clipRect.origin.y = -y - h;
	clipRect.size.width = w;
	clipRect.size.height = h;

	pcgRect.origin.x = x;
	pcgRect.origin.y = -y - h;

	CGContextSaveGState(context);
	CGContextClipToRect(context, clipRect);
	CGContextDrawImage(context, pcgRect, pcgCGImage);
	CGContextRestoreGState(context);
#endif // D_IPHONE

#ifdef D_MFC
	g_Dir3d.Draw(
			pImage,
			0, 0,
			x, y,
			w, h );
#endif // D_MFC

	endAlpha();

	return true;
}

////////////////////////////////////////////////////////////////
// ����ե��å����ѥ����������
// �ʥѥ���������к�ɸ�������
// WSDmwindowDev *mDev : �ե졼�ࡦ�Хåե��ʥ�����ɥ�����
// long x : X ��ɸ
// long y : Y ��ɸ
// long w : W ��
// long h : H �⤵
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool Pcg::drawFix( WSDmwindowDev *mDev,
		long x, long y, long w, long h )
{
	ena();

	if( mDev == NULL )
		return false;
	if( pImage == NULL )
		return false;
	if( w < 1 )
		return true;
	if( h < 1 )
		return true;

	long iw = pImage->getImageWidth();
	long ih = pImage->getImageHeight();
	if( iw < 1 )
		return false;
	if( ih < 1 )
		return false;
	long bgnX = (x / iw) * iw;
	long bgnY = (y / ih) * ih;

	beginAlpha();

	long drawH = ih - (y - bgnY);
	for( long yy = bgnY; yy < y + h; yy += ih ){
		if( drawH > (y + h - yy) )
			drawH = (y + h - yy);

		long drawW = iw - (x - bgnX);
		for( long xx = bgnX; xx < x + w; xx += iw ){
			if( drawW > (x + w - xx) )
				drawW = (x + w - xx);

			if( !waitReady( mDev ) ){
				endAlpha();

				return false;
			}

#ifdef D_WS
			mDev->beginDraw( xx, yy, drawW, drawH );
			mDev->drawImage( xx, yy, drawW, drawH,
					pImage, WS_LEFT_TOP );
			mDev->endDraw();
#endif // D_WS

#ifdef D_GTK
			GdkGC	*gc;
			gc = gMapDrawingArea->style->fg_gc
					[GTK_STATE_NORMAL];

			gdk_pixbuf_render_to_drawable(
					pImage->getPixbuf(),
					mDev->getPixMap(),
					gc,
					0, 0,
					xx, yy,
					drawW, drawH,
					GDK_RGB_DITHER_NONE,
					0, 0 );
#endif // D_GTK

#ifdef D_MAC
#if 0
//@@@
			long yyy = MAP_MAX_Y * 32 - yy - drawH;
			long srcY = pImage->getImageHeight() - drawH;
			
			NSImage *pcgCGImage = pImage->getPixbuf();
			NSImage *context = mDev->getPixMap();
			
			[context lockFocus];
			[pcgCGImage dissolveToPoint:NSMakePoint( xx, yyy ) fromRect:NSMakeRect( 0.0, srcY, drawW, drawH ) fraction:1.0];
			[context unlockFocus];
#else
			NSImage *pcgUIImage = pImage->getPixbuf();
			CGImageRef pcgCGImage = [pcgUIImage CGImageForProposedRect:nil context:nil hints:nil];
			CGContextRef context = mDev->getPixMap();
			
			CGRect pcgRect;
			pcgRect.size.width = pcgUIImage.size.width;
			pcgRect.size.height = pcgUIImage.size.height;
			
			CGRect clipRect;
			clipRect.origin.x = xx;
			clipRect.origin.y = -yy - ih;
			clipRect.size.width = drawW;
			clipRect.size.height = drawH;
			
			pcgRect.origin.x = xx;
			pcgRect.origin.y = -yy - ih;
			
			CGContextSaveGState(context);
			CGContextClipToRect(context, clipRect);
			CGContextDrawImage(context, pcgRect, pcgCGImage);
			CGContextRestoreGState(context);
#endif //@@@
#endif // D_MAC

#ifdef D_IPHONE
			UIImage *pcgUIImage = pImage->getPixbuf();
			CGImageRef pcgCGImage = pcgUIImage.CGImage;
			CGContextRef context = mDev->getPixMap();
			
			CGRect pcgRect;
			pcgRect.size = pcgUIImage.size;
			
			CGRect clipRect;
			clipRect.origin.x = xx;
			clipRect.origin.y = -yy - ih;
			clipRect.size.width = drawW;
			clipRect.size.height = drawH;
			
			pcgRect.origin.x = xx;
			pcgRect.origin.y = -yy - ih;
			
			CGContextSaveGState(context);
			CGContextClipToRect(context, clipRect);
			CGContextDrawImage(context, pcgRect, pcgCGImage);
			CGContextRestoreGState(context);
#endif // D_IPHONE

#ifdef D_MFC
			g_Dir3d.Draw(
					pImage,
					0, 0,
					xx, yy,
					drawW, drawH );
#endif // D_MFC

			drawW = iw;
		}

		drawH = ih;
	}

	endAlpha();

	return true;
}

////////////////////////////////////////////////////////////////
// ����ե��å����ѥ����������
// �ʥѥ���������Υ���ǥå����դ���
// WSDmwindowDev *mDev : �ե졼�ࡦ�Хåե��ʥ�����ɥ�����
// long x : X ��ɸ
// long y : Y ��ɸ
// long w : W ��
// long h : H �⤵
// long idxX : X �����Υѥ���������Υ���ǥå���
// long idxY : Y �����Υѥ���������Υ���ǥå���
// long sizeX : X �����Υѥ�����Υ�����
// long sizeY : Y �����Υѥ�����Υ�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool Pcg::drawIdx( WSDmwindowDev *mDev,
		long x, long y, long w, long h,
		long idxX, long idxY,
		long sizeX, long sizeY )
{
	ena();

	if( mDev == NULL )
		return false;
	if( pImage == NULL )
		return false;
	if( w < 1 )
		return true;
	if( h < 1 )
		return true;

	long iw = pImage->getImageWidth();
	long ih = pImage->getImageHeight();
	if( iw < 1 )
		return false;
	if( ih < 1 )
		return false;

	beginAlpha();

#ifdef D_WS
	mDev->beginDraw( x, y, sizeX, sizeY );
	mDev->drawImage(
			x - (idxX * sizeX),
			y - (idxY * sizeY),
			iw, ih,
			pImage, WS_LEFT_TOP );
	mDev->endDraw();
#endif // D_WS

#ifdef D_GTK
	GdkGC	*gc = gMapDrawingArea->style->fg_gc[GTK_STATE_NORMAL];

	gdk_pixbuf_render_to_drawable(
			pImage->getPixbuf(),
			mDev->getPixMap(),
			gc,
			idxX * sizeX,
			idxY * sizeY,
			x, y,
			sizeX, sizeY,
			GDK_RGB_DITHER_NONE,
			0, 0 );
#endif // D_GTK

#ifdef D_MAC
#if 0
//@@@
	y = MAP_MAX_Y * 32 - y - sizeY;
	long iy = pImage->getImageHeight() - (idxY * sizeY) - sizeY;
	
	NSImage *pcgCGImage = pImage->getPixbuf();
	NSImage *context = mDev->getPixMap();
	
	[context lockFocus];
	[pcgCGImage dissolveToPoint:NSMakePoint( x, y ) fromRect:NSMakeRect( idxX * sizeX, iy, sizeX, sizeY ) fraction:1.0];
	[context unlockFocus];
#else
	NSImage *pcgUIImage = pImage->getPixbuf();
	CGImageRef pcgCGImage = [pcgUIImage CGImageForProposedRect:nil context:nil hints:nil];
	CGContextRef context = mDev->getPixMap();
	
	CGRect pcgRect;
	pcgRect.size.width = pcgUIImage.size.width;
	pcgRect.size.height = pcgUIImage.size.height;
	
	CGRect clipRect;
	clipRect.origin.x = x;
	clipRect.origin.y = -y - sizeY;
	clipRect.size.width = sizeX;
	clipRect.size.height = sizeY;
	
	pcgRect.origin.x = x - (idxX * sizeX);
	pcgRect.origin.y = -y - pcgRect.size.height + (idxY * sizeY);
	
	CGContextSaveGState(context);
	CGContextClipToRect(context, clipRect);
	CGContextDrawImage(context, pcgRect, pcgCGImage);
	CGContextRestoreGState(context);
#endif //@@@
#endif // D_MAC

#ifdef D_IPHONE
	UIImage *pcgUIImage = pImage->getPixbuf();
	CGImageRef pcgCGImage = pcgUIImage.CGImage;
	CGContextRef context = mDev->getPixMap();
	
	CGRect pcgRect;
	pcgRect.size = pcgUIImage.size;
	
	CGRect clipRect;
	clipRect.origin.x = x;
	clipRect.origin.y = -y - sizeY;
	clipRect.size.width = sizeX;
	clipRect.size.height = sizeY;
	
	pcgRect.origin.x = x - (idxX * sizeX);
	pcgRect.origin.y = -y - pcgRect.size.height + (idxY * sizeY);
	
	CGContextSaveGState(context);
	CGContextClipToRect(context, clipRect);
	CGContextDrawImage(context, pcgRect, pcgCGImage);
	CGContextRestoreGState(context);
#endif // D_IPHONE
	
#ifdef D_MFC
	g_Dir3d.Draw(
			pImage,
			idxX * sizeX,
			idxY * sizeY,
			x, y,
			sizeX, sizeY );
#endif // D_MFC

	endAlpha();

	return true;
}

////////////////////////////////////////////////////////////////
// ����饯��������
// WSDmwindowDev *mDev : �ե졼�ࡦ�Хåե��ʥ�����ɥ�����
// long x : X ��ɸ
// long y : Y ��ɸ
// long w : W ��
// long h : H �⤵
// long offsetX : X ���ե��å�
// long offsetY : Y ���ե��å�
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool Pcg::drawOffset( WSDmwindowDev *mDev,
		long x, long y, long w, long h,
		long offsetX, long offsetY )
{
	ena();

	if( mDev == NULL )
		return false;
	if( pImage == NULL )
		return false;
	if( w < 1 )
		return true;
	if( h < 1 )
		return true;

	beginAlpha();

#ifdef D_WS
	long xx = x - offsetX;
	long yy = y - offsetY;
	long ww = w + offsetX;
	long hh = h + offsetY;
	if( ww > pImage->getImageWidth() )
		ww = pImage->getImageWidth();
	if( hh > pImage->getImageHeight() )
		hh = pImage->getImageHeight();

	mDev->beginDraw( x, y, w, h );
	mDev->drawImage( xx, yy, ww, hh, pImage, WS_LEFT_TOP );
	mDev->endDraw();
#endif // D_WS

#ifdef D_GTK
	if( x < 0 )
		x = 0;
	if( y < 0 )
		y = 0;
	if( w > pImage->getImageWidth() )
		w = pImage->getImageWidth();
	if( h > pImage->getImageHeight() )
		h = pImage->getImageHeight();
	GdkGC	*gc = gMapDrawingArea->style->fg_gc[GTK_STATE_NORMAL];

	gdk_pixbuf_render_to_drawable(
			pImage->getPixbuf(),
			mDev->getPixMap(),
			gc,
			offsetX, offsetY,
			x, y,
			w, h,
			GDK_RGB_DITHER_NONE,
			0, 0 );
#endif // D_GTK

#ifdef D_MAC
	if( x < 0 )
		x = 0;
	if( y < 0 )
		y = 0;
	if( w > pImage->getImageWidth() )
		w = pImage->getImageWidth();
	if( h > pImage->getImageHeight() )
		h = pImage->getImageHeight();

#if 0
//@@@
	y = MAP_MAX_Y * 32 - y - h;
	offsetY = pImage->getImageHeight() - offsetY - h;
	
	NSImage *pcgCGImage = pImage->getPixbuf();
	NSImage *context = mDev->getPixMap();

	[context lockFocus];
	[pcgCGImage dissolveToPoint:NSMakePoint( x, y ) fromRect:NSMakeRect( offsetX, offsetY, w, h ) fraction:1.0];
	[context unlockFocus];
#else
	NSImage *pcgUIImage = pImage->getPixbuf();
	CGImageRef pcgCGImage = [pcgUIImage CGImageForProposedRect:nil context:nil hints:nil];
	CGContextRef context = mDev->getPixMap();
	
	CGRect pcgRect;
	pcgRect.size.width = pcgUIImage.size.width;
	pcgRect.size.height = pcgUIImage.size.height;
	
	CGRect clipRect;
	clipRect.origin.x = x;
	clipRect.origin.y = -y - h;
	clipRect.size.width = w;
	clipRect.size.height = h;
	
	pcgRect.origin.x = x - offsetX;
	pcgRect.origin.y = -y - pcgRect.size.height + offsetY;
	
	CGContextSaveGState(context);
	CGContextClipToRect(context, clipRect);
	CGContextDrawImage(context, pcgRect, pcgCGImage);
	CGContextRestoreGState(context);
#endif //@@@
#endif // D_MAC

#ifdef D_IPHONE
	if( x < 0 )
		x = 0;
	if( y < 0 )
		y = 0;
	if( w > pImage->getImageWidth() )
		w = pImage->getImageWidth();
	if( h > pImage->getImageHeight() )
		h = pImage->getImageHeight();

	UIImage *pcgUIImage = pImage->getPixbuf();
	CGImageRef pcgCGImage = pcgUIImage.CGImage;
	CGContextRef context = mDev->getPixMap();
	
	CGRect pcgRect;
	pcgRect.size = pcgUIImage.size;
	
	CGRect clipRect;
	clipRect.origin.x = x;
	clipRect.origin.y = -y - h;
	clipRect.size.width = w;
	clipRect.size.height = h;
	
	pcgRect.origin.x = x - offsetX;
	pcgRect.origin.y = -y - pcgRect.size.height + offsetY;
	
	CGContextSaveGState(context);
	CGContextClipToRect(context, clipRect);
	CGContextDrawImage(context, pcgRect, pcgCGImage);
	CGContextRestoreGState(context);
#endif // D_IPHONE

#ifdef D_MFC
	if( w > pImage->getImageWidth() )
		w = pImage->getImageWidth();
	if( h > pImage->getImageHeight() )
		h = pImage->getImageHeight();

	g_Dir3d.Draw(
			pImage,
			offsetX, offsetY,
			x, y,
			w, h );
#endif // D_MFC

	endAlpha();

	return true;
}
