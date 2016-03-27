/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2007 YOSHIMURA Tomohiko All rights reserved.
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
* $Id: Dir3d.h,v 1.12 2008/09/09 07:38:07 bowkenken Exp $
***************************************************************/

#ifndef DIR3D_H
#define DIR3D_H

#include <d3d9.h>
#include <d3dx9.h>

#include "../MfcWSDimage.h"
#include "Dir3dText.h"

class CDir3d {
public:
	LPDIRECT3DDEVICE9 pDir3dDevice;
	LONG nDir3dAlphaNestFlag;
	HANDLE hDir3dMutexDraw;
	HANDLE hDir3dMutexWork;
	UINT uFrameRate;
	long nTileSizeRate;
	long nSizeRate;

protected:
	LPDIRECT3D9 pDir3d;
	D3DPRESENT_PARAMETERS dir3dPresParam;

	static const bool REFRESH_FRAME_MODE = true;
	bool bFlagRefreshRequest;

public:
	CDir3d();
	~CDir3d();

	BOOL CreateDevices( HWND hWnd );
	void Destroy();

	bool FrameMove( float AppTime, float ElapsedTime );
	void Render();

	void BeginAlpha();
	void EndAlpha();

	void Draw(
		WSDimage *img,
		long srcX, long srcY,
		long dstX, long dstY,
		long w, long h );
	void Draw(
		WSDimage *img,
		long srcX, long srcY,
		long dstX, long dstY,
		long w, long h,
		D3DCOLOR color,
		bool flagAlpha );

	bool CheckRefreshFrameMode();
	bool CheckRefreshRequest();
	void SetRefreshRequest( bool flag );
	bool Refresh();

	void BeginDraw();
	void EndDraw();
	bool CheckDrawNestFlag();

	BOOL WindowProc(
		UINT uMsg, WPARAM wParam, LPARAM lParam,
		LRESULT *pResult );

	static D3DCOLOR CvDwordToColor( DWORD n );

private:
	bool ResetRenderSetting();
};

#endif // DIR3D_H
