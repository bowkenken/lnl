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
* $Id: MfcWSDimage.h,v 1.10 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef MFC_WSD_IMAGE_H
#define MFC_WSD_IMAGE_H	1

#include "xlnl-dows/stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>

class WSDimage
{
private:
	LPDIRECT3DTEXTURE9 pPixbuf;
	long texW, texH;
	long imgW, imgH;

public:
	WSDimage()
	{
		pPixbuf = (LPDIRECT3DTEXTURE9)NULL;
		texW = 0;
		texH = 0;
		imgW = 0;
		imgH = 0;
	}
	WSDimage( LPDIRECT3DTEXTURE9 buf, long w, long h )
	{
//@@@		pPixbuf = (LPDIRECT3DTEXTURE9)NULL;
		pPixbuf = buf;
		setTextureSize();
		setImageSize( w, h );
	}
	~WSDimage()
	{
		destroyImage();
	}
	void destroyImage()
	{
		pPixbuf = (LPDIRECT3DTEXTURE9)NULL;
		setTextureSize();
		setImageSize( 0, 0 );
	}

	LPDIRECT3DTEXTURE9 getPixbuf()
	{
		return pPixbuf;
	}
	LPDIRECT3DTEXTURE9 *getPixbufPtr()
	{
		return &pPixbuf;
	}

	void setTextureSize()
	{
		if( pPixbuf == NULL ){
			texW = 0;
			texH = 0;

			return;
		}

		D3DSURFACE_DESC desc;
		if( pPixbuf->GetLevelDesc( 0, &desc ) == D3D_OK ){
			texW = desc.Width;
			texH = desc.Height;
		}
	}
	long getTextureWidth()
	{
		if( texW <= 0 )
			setTextureSize();

		return texW;
	}
	long getTextureHeight()
	{
		if( texH <= 0 )
			setTextureSize();

		return texH;
	}

	void setImageSize( long w, long h )
	{
		imgW = w;
		imgH = h;
	}
	long getImageWidth()
	{
		return imgW;
	}
	long getImageHeight()
	{
		return imgH;
	}
};

#endif // MFC_WSD_IMAGE_H
