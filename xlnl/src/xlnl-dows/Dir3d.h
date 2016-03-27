/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2007 YOSHIMURA Tomohiko All rights reserved.
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
