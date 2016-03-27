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
* $Id: GtkWSDimage.h,v 1.10 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GTK_WSD_IMAGE_DEV_H
#define GTK_WSD_IMAGE_DEV_H	1

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

class WSDimage
{
private:
	GdkPixbuf *pPixbuf;

public:
	WSDimage()
	{
		pPixbuf = NULL;
	}
	WSDimage( GdkPixbuf *buf )
	{
		pPixbuf = buf;
	}
	void destroyImage()
	{
		g_object_unref( pPixbuf );
	}

	GdkPixbuf *getPixbuf()
	{
		return pPixbuf;
	}
	GdkPixbuf *setPixbuf( GdkPixbuf *buf )
	{
		pPixbuf = buf;

		return pPixbuf;
	}

	long getImageWidth()
	{
		return gdk_pixbuf_get_width( pPixbuf );
	}
	long getImageHeight()
	{
		return gdk_pixbuf_get_height( pPixbuf );
	}
};

#endif // GTK_WSD_IMAGE_DEV_H
