// XlnlView.cpp : CXlnlView クラスの実装
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "XlnlView.h"
#include ".\xlnlview.h"

// bowkenken BEGIN
#include "../gmain.h"
#include "../Key.h"
#include "../GlobalVar.h"
// bowkenken END

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXlnlView

CXlnlView::CXlnlView()
{
}

CXlnlView::~CXlnlView()
{
}


BEGIN_MESSAGE_MAP(CXlnlView, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_NCLBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_NCMBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_NCRBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()



// CXlnlView メッセージ ハンドラ

BOOL CXlnlView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	// bowkenken BEGIN
	cs.style |= (WS_HSCROLL | WS_VSCROLL);
	// bowkenken END
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CXlnlView::OnPaint() 
{
	CPaintDC dc(this); // 描画のデバイス コンテキスト
	
	// TODO : ここにメッセージ ハンドラ コードを追加します。
	
	// メッセージの描画のために CWnd::OnPaint() を呼び出さないでください。

	// bowkenken BEGIN
	if( g_Dir3d.CheckRefreshFrameMode() )
		g_Dir3d.SetRefreshRequest( true );
	else
		gPcgDun.redraw( true );
	// bowkenken END
}

void CXlnlView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO : ここにメッセージ ハンドラ コードを追加します。

	// bowkenken BEGIN
	ResetScroll();
	// bowkenken END
}

void CXlnlView::ResetScroll()
{
	SCROLLINFO info;
	RECT rc;
	long np;

	// 水平スクロール・バーの現在値を取得

	GetClientRect( &rc );

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	GetScrollInfo( SB_HORZ, &info );

	// 水平スクロール・バーの初期化

	info.nMin = 0;
	info.nMax = MAP_MAX_X
			* gPcgDun.getTileSizeX( true ) - 1;

	info.nPage = rc.right - rc.left;
	np = info.nPage;
	if( g_Dir3d.nTileSizeRate > 0 ){
		np = np * 2 * (_100_PERCENT - g_Dir3d.nTileSizeRate)
				/ _100_PERCENT;
	}
	info.nMax -= np;

	if( info.nPage > (unsigned)(info.nMax + 1) )
		info.nPage = (unsigned)(info.nMax + 1);

	long maxX = (info.nMax + 1) - info.nPage;
	if( info.nPos > maxX )
		info.nPos = maxX;

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	SetScrollInfo( SB_HORZ, &info, TRUE );

	// 垂直スクロール・バーの現在値を取得

	GetClientRect( &rc );

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	GetScrollInfo( SB_VERT, &info );

	// 垂直スクロール・バーの初期化

	info.nMin = 0;
	info.nMax = MAP_MAX_Y
			* gPcgDun.getTileSizeY( true ) - 1;

	info.nPage = rc.bottom - rc.top;
	np = info.nPage;
	if( g_Dir3d.nTileSizeRate > 0 ){
		np = np * 2 * (_100_PERCENT - g_Dir3d.nTileSizeRate)
				/ _100_PERCENT;
	}
	info.nMax -= np;

	if( info.nPage > (unsigned)(info.nMax + 1) )
		info.nPage = (unsigned)(info.nMax + 1);

	long maxY = (info.nMax + 1) - info.nPage;
	if( info.nPos > maxY )
		info.nPos = maxY;

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	SetScrollInfo( SB_VERT, &info, TRUE );
}

void CXlnlView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN

	SCROLLINFO info;
	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	GetScrollInfo( SB_HORZ, &info );

	int pos = info.nPos;
	int minPos = info.nMin;
	int maxPos = info.nMax;
	int trackPos = info.nTrackPos;

	switch( nSBCode ){
	case SB_LEFT:
		pos = minPos;
		break;
	case SB_RIGHT:
		pos = maxPos;
		break;
	case SB_LINELEFT:
		pos -= gPcgDun.getTileSizeX( true ) * 1;
		break;
	case SB_LINERIGHT:
		pos += gPcgDun.getTileSizeX( true ) * 1;
		break;
	case SB_PAGELEFT:
		pos -= gPcgDun.getTileSizeX( true )
				* AREA_MAX_X / 2;
		break;
	case SB_PAGERIGHT:
		pos += gPcgDun.getTileSizeX( true )
				* AREA_MAX_X / 2;
		break;
	case SB_THUMBTRACK:
		pos = trackPos;
		break;
	case SB_ENDSCROLL:
		break;
	}

	gPcgDun.setScrollBarX( pos );
	gPcgDun.redraw( true );

	// bowkenken END

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CXlnlView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN

	SCROLLINFO info;
	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	GetScrollInfo( SB_VERT, &info );

	int pos = info.nPos;
	int minPos = info.nMin;
	int maxPos = info.nMax;
	int trackPos = info.nTrackPos;

	switch( nSBCode ){
	case SB_TOP:
		pos = minPos;
		break;
	case SB_BOTTOM:
		pos = maxPos;
		break;
	case SB_LINEUP:
		pos -= gPcgDun.getTileSizeY( true ) * 1;
		break;
	case SB_LINEDOWN:
		pos += gPcgDun.getTileSizeY( true ) * 1;
		break;
	case SB_PAGEUP:
		pos -= gPcgDun.getTileSizeY( true )
				* AREA_MAX_Y / 2;
		break;
	case SB_PAGEDOWN:
		pos += gPcgDun.getTileSizeY( true )
				* AREA_MAX_Y / 2;
		break;
	case SB_THUMBTRACK:
		pos = trackPos;
		break;
	case SB_ENDSCROLL:
		break;
	}

	gPcgDun.setScrollBarY( pos );
	gPcgDun.redraw( true );

	// bowkenken END

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CXlnlView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMouseMotion.move( (long)point.x, (long)point.y );
	// bowkenken END

	CWnd::OnMouseMove(nFlags, point);
}

void CXlnlView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	SetCapture();

	gMapDragBgnX = gPcgDun.getScrollBarX();
	gMapDragBgnY = gPcgDun.getScrollBarY();

	gMouseMotion.begin( MouseMotion::nMouseButtonL,
			(long)point.x, (long)point.y );
	// bowkenken END

	CWnd::OnLButtonDown(nFlags, point);
}

void CXlnlView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMapDragBgnX = -1;
	gMapDragBgnY = -1;

	gMouseMotion.end( MouseMotion::nMouseButtonL,
			(long)point.x, (long)point.y );

	::ReleaseCapture();
	// bowkenken END

	CWnd::OnLButtonUp(nFlags, point);
}

void CXlnlView::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMapDragBgnX = -1;
	gMapDragBgnY = -1;

	gMouseMotion.end( MouseMotion::nMouseButtonL,
			(long)point.x, (long)point.y );

	::ReleaseCapture();
	// bowkenken END

	CWnd::OnNcLButtonUp(nHitTest, point);
}

void CXlnlView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	SetCapture();

	gMapDragBgnX = gPcgDun.getScrollBarX();
	gMapDragBgnY = gPcgDun.getScrollBarY();

	gMouseMotion.begin( MouseMotion::nMouseButtonM,
			(long)point.x, (long)point.y );
	// bowkenken END

	CWnd::OnMButtonDown(nFlags, point);
}

void CXlnlView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMapDragBgnX = -1;
	gMapDragBgnY = -1;

	gMouseMotion.end( MouseMotion::nMouseButtonM,
			(long)point.x, (long)point.y );

	::ReleaseCapture();
	// bowkenken END

	CWnd::OnMButtonUp(nFlags, point);
}

void CXlnlView::OnNcMButtonUp(UINT nHitTest, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMapDragBgnX = -1;
	gMapDragBgnY = -1;

	gMouseMotion.end( MouseMotion::nMouseButtonM,
			(long)point.x, (long)point.y );

	::ReleaseCapture();
	// bowkenken END

	CWnd::OnNcMButtonUp(nHitTest, point);
}

void CXlnlView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	SetCapture();

	gMapDragBgnX = gPcgDun.getScrollBarX();
	gMapDragBgnY = gPcgDun.getScrollBarY();

	gMouseMotion.begin( MouseMotion::nMouseButtonR,
			(long)point.x, (long)point.y );
	// bowkenken END

	CWnd::OnRButtonDown(nFlags, point);
}

void CXlnlView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMapDragBgnX = -1;
	gMapDragBgnY = -1;

	gMouseMotion.end( MouseMotion::nMouseButtonR,
			(long)point.x, (long)point.y );

	::ReleaseCapture();
	// bowkenken END

	CWnd::OnRButtonUp(nFlags, point);
}

void CXlnlView::OnNcRButtonUp(UINT nHitTest, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMapDragBgnX = -1;
	gMapDragBgnY = -1;

	gMouseMotion.end( MouseMotion::nMouseButtonR,
			(long)point.x, (long)point.y );

	::ReleaseCapture();
	// bowkenken END

	CWnd::OnNcRButtonUp(nHitTest, point);
}

void CXlnlView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMouseMotion.doubleClick( MouseMotion::nMouseButtonL,
			(long)point.x, (long)point.y );
	// bowkenken END

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CXlnlView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMouseMotion.doubleClick( MouseMotion::nMouseButtonM,
			(long)point.x, (long)point.y );
	// bowkenken END

	CWnd::OnMButtonDblClk(nFlags, point);
}

void CXlnlView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gMouseMotion.doubleClick( MouseMotion::nMouseButtonR,
			(long)point.x, (long)point.y );
	// bowkenken END

	CWnd::OnRButtonDblClk(nFlags, point);
}

void CXlnlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.handleKeyDown( nChar, nRepCnt, nFlags );
	// bowkenken END

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CXlnlView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.setChar( nChar, true );
	// bowkenken END

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
