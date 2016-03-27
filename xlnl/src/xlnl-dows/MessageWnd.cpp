// MessageWnd.cpp : 実装ファイル
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "MessageWnd.h"

#include "../GlobalVar.h"
#include ".\messagewnd.h"


// CMessageWnd

IMPLEMENT_DYNCREATE(CMessageWnd, CFrameWnd)

CMessageWnd::CMessageWnd()
{
}

CMessageWnd::~CMessageWnd()
{
}


BEGIN_MESSAGE_MAP(CMessageWnd, CFrameWnd)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CMessageWnd メッセージ ハンドラ

int CMessageWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO :  ここに特定な作成コードを追加してください。

	// bowkenken BEGIN
	if( !m_wndView.Create( NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect( 0, 0, 0, 0 ), this, AFX_IDW_PANE_FIRST, NULL ) )
	{
		TRACE0(MSG_ERR_DOWS_CREATE_VIEW);
		return -1;
	}
	// bowkenken END

	return 0;
}

void CMessageWnd::OnClose()
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gWinPos[WIN_KIND_MESSAGE].wipe( WIN_KIND_MESSAGE );
	// bowkenken END

	// bowkenken
	// CFrameWnd::OnClose();
}

void CMessageWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.handleKeyDown( nChar, nRepCnt, nFlags );
	// bowkenken END

	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMessageWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.setChar( nChar, true );
	// bowkenken END

	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}
