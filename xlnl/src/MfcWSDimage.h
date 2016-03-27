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
