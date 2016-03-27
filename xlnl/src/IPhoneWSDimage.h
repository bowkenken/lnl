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
* $Id: IPhoneWSDimage.h,v 1.3 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef IPHONE_WSD_IMAGE_DEV_H
#define IPHONE_WSD_IMAGE_DEV_H	1

#import <UIKit/UIKit.h>

class WSDimage
{
private:
	UIImage *pPixbuf;

public:
	WSDimage()
	{
		pPixbuf = nil;
	}
	WSDimage( UIImage *buf )
	{
		pPixbuf = buf;
		[pPixbuf retain];
	}
	void destroyImage()
	{
		[pPixbuf release];
		pPixbuf = nil;
	}

	UIImage *getPixbuf()
	{
		return pPixbuf;
	}
	UIImage *setPixbuf( UIImage *buf )
	{
		pPixbuf = buf;
		[pPixbuf retain];

		return pPixbuf;
	}

	long getImageWidth()
	{
		if( pPixbuf )
			return( pPixbuf.size.width );
		else
			return 1;
	}
	long getImageHeight()
	{
		if( pPixbuf )
			return( pPixbuf.size.height );
		else
			return 1;
	}
};

#endif // IPHONE_WSD_IMAGE_DEV_H
