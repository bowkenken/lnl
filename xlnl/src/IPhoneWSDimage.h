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
