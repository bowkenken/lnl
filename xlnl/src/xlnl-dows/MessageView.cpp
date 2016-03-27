// MessageView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "MessageView.h"
#include ".\messageview.h"

// bowkenken BEGIN
#include "../draw.h"
#include "../draw-prot.h"

#include "../GlobalVar.h"
// bowkenken END


// CMessageView

IMPLEMENT_DYNCREATE(CMessageView, CView)

CMessageView::CMessageView()
{
}

CMessageView::~CMessageView()
{
}

BEGIN_MESSAGE_MAP(CMessageView, CView)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CMessageView 描画

void CMessageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 描画コードをここに追加してください。

	// bowkenken BEGIN
	gGuiMessage.redraw();
	gGuiMessage.drawScrollBar();
	// bowkenken END
}


// CMessageView 診断

#ifdef _DEBUG
void CMessageView::AssertValid() const
{
	CView::AssertValid();
}

void CMessageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CMessageView メッセージ ハンドラ

BOOL CMessageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	// bowkenken BEGIN
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.style |= (WS_HSCROLL | WS_VSCROLL);
	// bowkenken END

	return CView::PreCreateWindow(cs);
}

void CMessageView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO : ここにメッセージ ハンドラ コードを追加します。

	// bowkenken BEGIN

	SCROLLINFO info;
	RECT rc;

	CMessageView *view = &(theApp.m_MesWnd.m_wndView);
	CClientDC dc( view );

	static char tmp[WIN_MSG_DRAW_WIDTH + 1];
	long i;
	for( i = 0; i < WIN_MSG_DRAW_WIDTH; i++ )
		tmp[i] = 'X';
	tmp[i] = '\0';
	CSize size = dc.GetOutputTextExtent( CString( tmp ) );
	size.cy += GuiMessage::LINE_INTERVAL;

	// 水平スクロール・バーの現在値を取得

	GetClientRect( &rc );

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	GetScrollInfo( SB_HORZ, &info );

	// 水平スクロール・バーを調整

	info.nMin = 0;
	info.nMax = size.cx - 1;

	info.nPage = rc.right - rc.left;
	if( info.nPage < 1 )
		info.nPage = 1;
	if( info.nPage > (unsigned)(info.nMax + 1) )
		info.nPage = (unsigned)(info.nMax + 1);

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	SetScrollInfo( SB_HORZ, &info, FALSE );

	// 垂直スクロール・バーの現在値を取得

	GetClientRect( &rc );

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	GetScrollInfo( SB_VERT, &info );

	// 垂直スクロール・バーを調整

	long maxH = get_ls_msg_n() - 1;
	if( maxH < 0 )
		maxH = 0;

	long pageH = (rc.bottom - rc.top) / size.cy;
	if( pageH < 1 )
		pageH = 1;

	info.nMin = 0;
	info.nMax = maxH + pageH - 1;
	info.nPage = pageH;

	if( info.nPos < 0 )
		info.nPos = 0;
	if( info.nPos > maxH )
		info.nPos = maxH;

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	SetScrollInfo( SB_VERT, &info, FALSE );

	gGuiMessage.redraw();

	// bowkenken END
}

void CMessageView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN

	CMessageView *view = &(theApp.m_MesWnd.m_wndView);
	CClientDC dc( view );

	static char tmp[WIN_MSG_DRAW_WIDTH + 1];
	long i;
	for( i = 0; i < WIN_MSG_DRAW_WIDTH; i++ )
		tmp[i] = 'X';
	tmp[i] = '\0';
	CSize size = dc.GetOutputTextExtent( CString( tmp ) );
	size.cx /= WIN_MSG_DRAW_WIDTH;
	size.cy += GuiMessage::LINE_INTERVAL;

	RECT rc;
	GetClientRect( &rc );

	SCROLLINFO info;
	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	GetScrollInfo( SB_HORZ, &info );

	int pos = info.nPos;

	switch( nSBCode ){
	case SB_LEFT:
		pos = info.nMin;
		break;
	case SB_RIGHT:
		pos = info.nMax;
		break;
	case SB_LINELEFT:
		pos -= size.cx;
		break;
	case SB_LINERIGHT:
		pos += size.cx;
		break;
	case SB_PAGELEFT:
		pos -= (rc.right - rc.left) / 1;
		break;
	case SB_PAGERIGHT:
		pos += (rc.right - rc.left) / 1;
		break;
	case SB_THUMBTRACK:
		pos = info.nTrackPos;
		break;
	case SB_ENDSCROLL:
		break;
	}

	SetScrollPos( SB_HORZ, pos, TRUE );
	gGuiMessage.redraw();

	// bowkenken END

	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMessageView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN

	CMessageView *view = &(theApp.m_MesWnd.m_wndView);
	CClientDC dc( view );

	static char tmp[WIN_MSG_DRAW_WIDTH + 1];
	long i;
	for( i = 0; i < WIN_MSG_DRAW_WIDTH; i++ )
		tmp[i] = 'X';
	tmp[i] = '\0';
	CSize size = dc.GetOutputTextExtent( CString( tmp ) );
	size.cx /= WIN_MSG_DRAW_WIDTH;
	size.cy += GuiMessage::LINE_INTERVAL;

	RECT rc;
	GetClientRect( &rc );

	SCROLLINFO info;
	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	GetScrollInfo( SB_VERT, &info );

	int pos = info.nPos;

	switch( nSBCode ){
	case SB_TOP:
		pos = info.nMin;
		break;
	case SB_BOTTOM:
		pos = info.nMax;
		break;
	case SB_LINEUP:
		pos -= 1;
		break;
	case SB_LINEDOWN:
		pos += 1;
		break;
	case SB_PAGEUP:
		pos -= (rc.bottom - rc.top) / size.cy;
		break;
	case SB_PAGEDOWN:
		pos += (rc.bottom - rc.top) / size.cy;
		break;
	case SB_THUMBTRACK:
		pos = info.nTrackPos;
		break;
	case SB_ENDSCROLL:
		break;
	}

	SetScrollPos( SB_VERT, pos, TRUE );
	gGuiMessage.redraw();

	// bowkenken END

	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMessageView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.handleKeyDown( nChar, nRepCnt, nFlags );
	// bowkenken END

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMessageView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.setChar( nChar, true );
	// bowkenken END

	CView::OnChar(nChar, nRepCnt, nFlags);
}
