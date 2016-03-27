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
* $Id: Dir3d.cpp,v 1.24 2009/07/12 11:38:28 bowkenken Exp $
***************************************************************/

#include "StdAfx.h"
#include "Dir3d.h"

#include "../gmain.h"
#include "../scene.h"
#include "../gmain-prot.h"
#include "../scene-prot.h"
#include "../GlobalVar.h"

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

const UINT DEFAULT_FRAME_RATE = 4;

struct TLVertex {
	FLOAT x, y, z;
	FLOAT rhw;
	D3DCOLOR color;
	FLOAT tu, tv;
};

const DWORD VertexFVF = (
	D3DFVF_XYZRHW
	| D3DFVF_DIFFUSE
	| D3DFVF_TEX1
);

CDir3d::CDir3d()
{
	uFrameRate = DEFAULT_FRAME_RATE;
	pDir3d = NULL;
	pDir3dDevice = NULL;
	nTileSizeRate = 100;
	nSizeRate = 100;

	SetRefreshRequest( false );

	nDir3dAlphaNestFlag = 0;
	hDir3dMutexWork = NULL;
	hDir3dMutexDraw = ::CreateMutex( NULL, FALSE,
			"xlnl_map_mutex" );
	if( hDir3dMutexDraw == NULL )
		exit_game( EXIT_FAILURE );
}

CDir3d::~CDir3d()
{
	Destroy();
}

BOOL CDir3d::CreateDevices( HWND hWnd )
{
	pDir3d = Direct3DCreate9( D3D_SDK_VERSION );
	if( pDir3d == NULL ){
		::AfxMessageBox( MSG_ERR_DOWS_CREATE_DIRECT3D );

		return FALSE;
	}

	D3DDISPLAYMODE dispMode;
	if( FAILED( pDir3d->GetAdapterDisplayMode(
			D3DADAPTER_DEFAULT, &dispMode ) ) ){
		::AfxMessageBox( MSG_ERR_DOWS_GET_DISPLAY_MODE );

		return FALSE;
	}

	ZeroMemory( &dir3dPresParam, sizeof( dir3dPresParam ) );
	dir3dPresParam.Windowed = TRUE;
	dir3dPresParam.BackBufferCount = 1;
	dir3dPresParam.BackBufferFormat = dispMode.Format;
	dir3dPresParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	dir3dPresParam.MultiSampleType = D3DMULTISAMPLE_NONE;
	dir3dPresParam.MultiSampleQuality = 0;
	dir3dPresParam.EnableAutoDepthStencil = TRUE;
	dir3dPresParam.AutoDepthStencilFormat = D3DFMT_D16;
	dir3dPresParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	dir3dPresParam.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	dir3dPresParam.hDeviceWindow = hWnd;
	dir3dPresParam.Flags = 0;

	if( FAILED( pDir3d->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&dir3dPresParam, &pDir3dDevice ) ) ){
		if( FAILED( pDir3d->CreateDevice(
				D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&dir3dPresParam, &pDir3dDevice ) ) ){
			if( FAILED( pDir3d->CreateDevice(
					D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&dir3dPresParam, &pDir3dDevice ) ) ){
					::AfxMessageBox( MSG_ERR_DOWS_CREATE_DEVICE );

				return FALSE;
			}
		}
	}

	return TRUE;
}

void CDir3d::Destroy()
{
	if( pDir3d != NULL ){
		pDir3d->Release();
		pDir3d = NULL;
	}
	if( pDir3dDevice != NULL ){
		pDir3dDevice->Release();
		pDir3dDevice = NULL;
	}
}

bool CDir3d::FrameMove( float AppTime, float ElapsedTime )
{
	return true;
}

void CDir3d::Render()
{
	if( pDir3d == NULL )
		return;
	if( pDir3dDevice == NULL )
		return;

	if( get_scene() == SCENE_N_LAST_BOSS ){
		if( !gPcgDun.drawLastBoss() )
			gPcgDun.drawTurn( true );
	} else if( chk_scene_group( SCENE_GROUP_N_INIT ) ){
		return;
	} else if( chk_scene_group( SCENE_GROUP_N_TITLE ) ){
		gPcgDun.drawTitle();
	} else if( chk_scene_group( SCENE_GROUP_N_PLAYING ) ){
		gPcgDun.drawTurn( true );
	} else if( chk_scene_group( SCENE_GROUP_N_ENDING ) ){
		gPcgDun.drawEnding();
	} else if( chk_scene_group( SCENE_GROUP_N_GAME_OVER ) ){
		gPcgDun.drawGameOver();
	} else if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) ){
		if( gSelMbrGraph != NULL ){
			gSelMbrGraph->redraw();
		}
	}
}

bool CDir3d::ResetRenderSetting()
{
	if( pDir3d == NULL )
		return false;
	if( pDir3dDevice == NULL )
		return false;

	BeginDraw();
	pDir3dDevice->Reset( &dir3dPresParam );
	EndDraw();

	return true;
}

void CDir3d::BeginAlpha()
{
	if( pDir3d == NULL )
		return;
	if( pDir3dDevice == NULL )
		return;

	if( ::InterlockedExchangeAdd(
			&nDir3dAlphaNestFlag, 1 ) > 0 ){
		return;
	}

	BeginDraw();

	pDir3dDevice->SetRenderState(
			D3DRS_ALPHABLENDENABLE, TRUE );
	pDir3dDevice->SetRenderState(
			D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pDir3dDevice->SetRenderState(
			D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	EndDraw();
}

void CDir3d::EndAlpha()
{
	if( pDir3d == NULL )
		return;
	if( pDir3dDevice == NULL )
		return;

	if( ::InterlockedDecrement(
			&nDir3dAlphaNestFlag ) > 0 ){
		return;
	}

	BeginDraw();

	pDir3dDevice->SetRenderState(
			D3DRS_ALPHATESTENABLE, FALSE );
	pDir3dDevice->SetRenderState(
			D3DRS_ALPHABLENDENABLE, FALSE );

	EndDraw();
}

void CDir3d::Draw(
	WSDimage *img,
	long srcX, long srcY,
	long dstX, long dstY,
	long w, long h )
{
	D3DCOLOR color = D3DCOLOR_XRGB( 255, 255, 255 );
	Draw( img, srcX, srcY, dstX, dstY, w, h, color, false );
}

void CDir3d::Draw(
	WSDimage *img,
	long srcX, long srcY,
	long dstX, long dstY,
	long w, long h,
	D3DCOLOR color,
	bool flagAlpha )
{
	if( pDir3d == NULL )
		return;
	if( pDir3dDevice == NULL )
		return;
	if( img == NULL )
		return;

	LPDIRECT3DDEVICE9 pDev = pDir3dDevice;
	if( pDev == NULL )
		return;

	LPDIRECT3DTEXTURE9 pPixbuf = img->getPixbuf();
	if( pPixbuf == NULL )
		return;

	dstX -= gPcgDun.getScrollBarX();
	dstY -= gPcgDun.getScrollBarY();

	float dstX1 = (float)(dstX);
	float dstY1 = (float)(dstY);
	float dstX2 = (float)(dstX + w);
	float dstY2 = (float)(dstY + h);
	float srcX1 = (float)(srcX);
	float srcY1 = (float)(srcY);
	float srcX2 = (float)(srcX + w);
	float srcY2 = (float)(srcY + h);
	float texW = (float)img->getTextureWidth();
	float texH = (float)img->getTextureHeight();
	float r = (float)nTileSizeRate / 100.0f;
	dstX1 *= r;
	dstY1 *= r;
	dstX2 *= r;
	dstY2 *= r;

	float mr = (float)nSizeRate / 100.0f;
	float mw = (dstX2 - dstX1) / 2;
	float mh = (dstY2 - dstY1) / 2;
	float mx = dstX1 + mw;
	float my = dstY1 + mh;
	dstX1 = mx - (mw * mr);
	dstX2 = mx + (mw * mr);
	dstY1 = my - (mh * mr);
	dstY2 = my + (mh * mr);

#if 0
//@@@
	if( dstX2 < 0 )
		return;
	if( dstY2 < 0 )
		return;
	if( srcX2 < 0 )
		return;
	if( srcY2 < 0 )
		return;
	if( dstX2 <= dstX1 )
		return;
	if( dstY2 <= dstY1 )
		return;
	if( srcX2 <= srcX1 )
		return;
	if( srcY2 <= srcY1 )
		return;
	if( texW <= 0.0f )
		return;
	if( texH <= 0.0f )
		return;
#endif

#if 1
	TLVertex vt[] = {
		{
			dstX1 - 0.5f, dstY1 - 0.5f, 0,
			1, color,
			srcX1 / texW, srcY1 / texH,
		},
		{
			dstX2 - 0.5f, dstY1 - 0.5f, 0,
			1, color,
			srcX2 / texW, srcY1 / texH,
		},
		{
			dstX1 - 0.5f, dstY2 - 0.5f, 0,
			1, color,
			srcX1 / texW, srcY2 / texH,
		},
		{
			dstX2 - 0.5f, dstY2 - 0.5f, 0,
			1, color,
			srcX2 / texW, srcY2 / texH,
		},
	};
#else
//@@@
	IDirect3DVertexBuffer9 *pVtBuf;
	pDev->CreateVertexBuffer(
			4 * 2 * sizeof( TLVertex ), VertexFVF,
			D3DUSAGE_WRITEONLY,
			D3DPOOL_DEFAULT,
			&pVtBuf, NULL );

	TLVertex *vt;
	pVtBuf->Lock( 0, 0, (void **)&vt, 0 );

	vt[0].x = dstX1 - 0.0f;
	vt[0].y = dstY1 - 0.0f;
	vt[0].z = 0.0f;
	vt[0].rhw = 1.0f;
	vt[0].color = color;
	vt[0].tu = srcX1 / texW;
	vt[0].tv = srcY1 / texH;

	vt[1].x = dstX2 - 0.0f;
	vt[1].y = dstY1 - 0.0f;
	vt[1].z = 0.0f;
	vt[1].rhw = 1.0f;
	vt[1].color = color;
	vt[1].tu = srcX2 / texW;
	vt[1].tv = srcY1 / texH;

	vt[2].x = dstX1 - 0.0f;
	vt[2].y = dstY2 - 0.0f;
	vt[2].z = 0.0f;
	vt[2].rhw = 1.0f;
	vt[2].color = color;
	vt[2].tu = srcX1 / texW;
	vt[2].tv = srcY2 / texH;

	vt[3].x = dstX2 - 0.0f;
	vt[3].y = dstY2 - 0.0f;
	vt[3].z = 0.0f;
	vt[3].rhw = 1.0f;
	vt[3].color = color;
	vt[3].tu = srcX2 / texW;
	vt[3].tv = srcY2 / texH;

	pVtBuf->Unlock();
#endif

	BeginDraw();

#if 0
//@@@
#ifdef USE_DIR3D_VER_8
	pDev->SetTextureStageState(
			0, D3DTSS_MINFILTER, D3DTEXF_LINEAR );
#else
	pDev->SetSamplerState(
			0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
#endif
//@@@pDev->D3DXMatrixScaling( &Mat1, 1.5, 1, 1);
#endif

	TRY {
		if( flagAlpha ){
			pDir3dDevice->SetTextureStageState(
					0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
			pDir3dDevice->SetTextureStageState(
					0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
			pDir3dDevice->SetTextureStageState(
					0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
		}

		pDev->SetTexture( 0, pPixbuf );
		pDev->SetFVF( VertexFVF );
		pDev->DrawPrimitiveUP(
				D3DPT_TRIANGLESTRIP, 2,
				vt, sizeof( TLVertex ) );

		if( flagAlpha ){
			pDir3dDevice->SetTextureStageState(
					0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
		}
	} CATCH( CException, e ){
	} END_CATCH

	EndDraw();
}

bool CDir3d::CheckRefreshFrameMode()
{
	return REFRESH_FRAME_MODE;
}

bool CDir3d::CheckRefreshRequest()
{
	return bFlagRefreshRequest;
}

void CDir3d::SetRefreshRequest( bool flag )
{
	bFlagRefreshRequest = flag;
}

bool CDir3d::Refresh()
{
	if( g_flg_text_mode ){
		gPcgDun.drawTurn( true );
		return true;
	}

	if( pDir3d == NULL )
		return false;
	if( pDir3dDevice == NULL )
		return false;

	// 背景の色を設定

	const long maxRGB = 256;
	const long maxClrN = maxRGB * 2;
	const long sec = 2;

	static long clrN = 0;
	clrN += maxClrN / (60 / uFrameRate * sec);
	clrN %= maxClrN;

	long clrRGB;
	if( clrN < maxRGB )
		clrRGB = clrN;
	else
		clrRGB = maxClrN - clrN - 1;

	// 画面をクリア

	D3DCOLOR clr;
	if( chk_scene_group( SCENE_GROUP_N_TITLE ) )
		clr = D3DCOLOR_XRGB( 0x00, 0x00, 0x00 );
	else if( chk_scene_group( SCENE_GROUP_N_GAME_OVER ) )
		clr = D3DCOLOR_XRGB( 0x00, 0x00, 0x00 );
	else if( chk_scene_group( SCENE_GROUP_N_ENDING ) )
		clr = D3DCOLOR_XRGB( 0x00, 0x00, 0x00 );
	else
		clr = D3DCOLOR_XRGB( clrRGB, clrRGB, clrRGB );

	BeginDraw();
	pDir3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET,
			clr, 1.0, 0 );
	EndDraw();

	// 画面を描画

	if( SUCCEEDED( pDir3dDevice->BeginScene() ) ){
		Render();
		pDir3dDevice->EndScene();
	}

	BeginDraw();
	HRESULT hr = pDir3dDevice->Present( NULL, NULL, NULL, NULL );
	if( FAILED( hr ) ){
		for( long i = 0; i < LOOP_MAX_100; i++ ){
			hr = pDir3dDevice->TestCooperativeLevel();
			if( !FAILED( hr ) )
				break;

			if( hr == D3DERR_DEVICELOST )
				Sleep( 50 );
			else if( hr == D3DERR_DEVICENOTRESET )
				pDir3dDevice->Reset( &dir3dPresParam );
			else
				break;
		}
	}
	EndDraw();

	return true;
}

void CDir3d::BeginDraw()
{
	if( hDir3dMutexWork == NULL ){
		hDir3dMutexWork = ::OpenMutex(
				MUTEX_ALL_ACCESS, TRUE,
				"xlnl_map_mutex" );
	}

	::WaitForSingleObject( hDir3dMutexWork, INFINITE );
}

void CDir3d::EndDraw()
{
	if( hDir3dMutexWork == NULL )
		return;

	::ReleaseMutex( hDir3dMutexWork );
}

BOOL CDir3d::WindowProc(
	UINT uMsg, WPARAM wParam, LPARAM lParam,
	LRESULT *pResult
)
{
	static bool bFlagSizing = false;

	*pResult = 0;

	switch( uMsg ){
	case WM_SIZE:
#if 0
//@@@
		if( pDir3d == NULL )
			break;
		if( pDir3dDevice == NULL )
			break;

		if( (wParam != SIZE_RESTORED)
				&& (wParam != SIZE_MAXIMIZED) ){
			break;
		}

		theApp.m_pMainFrm->StopTimer();

		dir3dPresParam.BackBufferWidth
				= LOWORD( lParam );
//				= gPcgDun.getScrollBarW();
		dir3dPresParam.BackBufferHeight
				= HIWORD( lParam );
//				= gPcgDun.getScrollBarH();

//		if( !bFlagSizing )
			ResetRenderSetting();

		theApp.m_pMainFrm->StartTimer();
#endif
		break;
	case WM_ENTERSIZEMOVE:
		bFlagSizing = true;
		break;
	case WM_EXITSIZEMOVE:
#if 0
//@@@
		theApp.m_pMainFrm->StopTimer();
		Sleep( 100 );

		ResetRenderSetting();
		bFlagSizing = false;

		theApp.m_pMainFrm->StartTimer();
#elif 0
		theApp.m_pMainFrm->StopTimer();
		Sleep( 100 );

		dir3dPresParam.BackBufferWidth
				= LOWORD( lParam );
//				= gPcgDun.getScrollBarW();
		dir3dPresParam.BackBufferHeight
				= HIWORD( lParam );
//				= gPcgDun.getScrollBarH();
		ResetRenderSetting();

		theApp.m_pMainFrm->StartTimer();
#endif
		break;
	case WM_ENTERMENULOOP:
//@@@		theApp.m_pMainFrm->StopTimer();
		break;
	case WM_EXITMENULOOP:
//@@@		theApp.m_pMainFrm->StartTimer();
		break;
	case WM_ERASEBKGND:
		*pResult = 0;
		return TRUE;
	case WM_DESTROY:
		Destroy();
		break;
	}

	return FALSE;
}

D3DCOLOR CDir3d::CvDwordToColor( DWORD n )
{
	return( D3DCOLOR_XRGB(
			((n >> 16) & 0xff),
			((n >>  8) & 0xff),
			((n >>  0) & 0xff) ) );
}
