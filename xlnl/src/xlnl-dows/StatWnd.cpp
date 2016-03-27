// StatWnd.cpp : 実装ファイル
//

// bowkenken BEGIN
#include "../party.h"
#include "../draw.h"
#include "../draw-tab.h"
#include "../misc.h"
#include "../misc-prot.h"
// bowkenken END

#include "stdafx.h"
#include "xlnl-dows.h"
#include "StatWnd.h"
#include ".\statwnd.h"

// bowkenken BEGIN
#include "../GlobalVar.h"
// bowkenken END


// CStatWnd

IMPLEMENT_DYNCREATE(CStatWnd, CFrameWnd)

CStatWnd::CStatWnd()
{
	m_RectAdj = CRect( 0, 0, 1, 1 );
	mFlagAdj = false;
}

CStatWnd::~CStatWnd()
{
}


BEGIN_MESSAGE_MAP(CStatWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()


// bowkenken BEGIN
void CStatWnd::ReSize()
{
	if( mFlagAdj ){
		mFlagAdj = false;
		return;
	}

	long x = 0;
	long y = 0;
	long adjW = 0;
	CRect rect;

	for( long i = 0; i < MBR_MAX_N; i++ ){
		rect = ReSizeMbr( i, CPoint( x, y ) );

		CRect rectWnd;
		this->GetWindowRect( &rectWnd );
		adjW = max_l( adjW, x + rect.Width() );
		if( rectWnd.Width() < (x + rect.Width() * 2) ){
			x = 0;
			y += rect.Height();
		} else {
			x += rect.Width();
		}
	}

	long ySpc = 1;
	long yBorder = 2 * 2;
	CDC *dc = this->GetDC();
	CSize fontSize = dc->GetTextExtent( "M", 1 );
	long h = fontSize.cy + yBorder;

	m_LabelDunLev.MoveWindow( x, y, rect.Width(), h, TRUE );
	y += h + ySpc;
	m_LabelTime.MoveWindow( x, y, rect.Width(), h, TRUE );
	y += h + ySpc;

	m_RectAdj = CRect( 0, 0, x + adjW, y );
	UpdateWindow();
}
// bowkenken END

// bowkenken BEGIN
CRect CStatWnd::ReSizeMbr( long mbr_n, CPoint pos )
{
	gGuiStat.draw( mbr_n );

	// コントロールのサイズを計算

	CString str;

	long xSpc = 1;
	long ySpc = 1;
	long xBorder = 2 * 2;
	long yBorder = 2 * 2;
	long x = pos.x + xSpc;
	long y = pos.y + ySpc;
	long w = 0;
	long h = 0;
	long wHpMp;
	long maxLen = max_l( MBR_NAME_MAX_LEN,
			WIN_STAT_ACT_DRAW_WIDTH );

	CDC *dc = this->GetDC();
	CSize fontSize = dc->GetTextExtent( "M", 1 );
	w = (fontSize.cx * maxLen) + xBorder;
	h = fontSize.cy + yBorder;

	m_LabelHp[mbr_n].GetWindowText( str );
	fontSize = dc->GetTextExtent( str );
	wHpMp = fontSize.cx + xBorder;

	m_LabelMp[mbr_n].GetWindowText( str );
	fontSize = dc->GetTextExtent( str );
	wHpMp = max_l( wHpMp, fontSize.cx + xBorder );

	// コントロールのサイズを設定

	m_BtnName[mbr_n].MoveWindow( x, y, w, h, TRUE );
	y += h;

	m_BtnStat[mbr_n].MoveWindow( x, y, w, h, TRUE );
	y += h;

	m_LabelAct[mbr_n].MoveWindow( x, y, w, h, TRUE );
	y += h;

	m_LabelHp[mbr_n].MoveWindow( x, y, wHpMp, h, TRUE );
	y += h;

	m_LabelMp[mbr_n].MoveWindow( x, y, wHpMp, h, TRUE );
	y += h;

	x += xSpc + max_l( w, wHpMp );
	y += ySpc;

	gGuiStat.draw( mbr_n );

	return CRect( pos.x, pos.y, x, y );
}
// bowkenken END

// bowkenken BEGIN
void CStatWnd::AdjustWnd()
{
	mFlagAdj = true;

	CRect rectAdj = m_RectAdj;

	CRect rectWnd;
	this->GetWindowRect( &rectWnd );
	::AdjustWindowRectEx( &rectAdj,
			this->GetStyle(), FALSE,
			this->GetExStyle() );

	this->MoveWindow(
			rectWnd.left,
			rectWnd.top,
			rectAdj.Width(),
			rectAdj.Height(),
			TRUE );
}
// bowkenken END

// CStatWnd メッセージ ハンドラ

int CStatWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO :  ここに特定な作成コードを追加してください。

	DWORD btnStyle = (WS_VISIBLE | BS_LEFT | BS_VCENTER
			| BS_PUSHBUTTON);
	DWORD lblStyle = (WS_VISIBLE | BS_LEFT | BS_VCENTER);

	for( long i = 0; i < MBR_MAX_N; i++ ){
		m_BtnName[i].Create( "Name",
				btnStyle,
				CRect( 0, 0, 16, 16 ),
				this, IDC_STAT_WND_NAME_BGN + i );
		m_LabelAct[i].Create( "Action",
				lblStyle,
				CRect( 0, 0, 16, 16 ),
				this, IDC_STAT_WND_ACT_BGN + i );
		m_BtnStat[i].Create( "Status",
				btnStyle,
				CRect( 0, 0, 16, 16 ),
				this, IDC_STAT_WND_STAT_BGN + i );
		m_LabelHp[i].Create( "HP",
				lblStyle,
				CRect( 0, 0, 16, 16 ),
				this, IDC_STAT_WND_HP_BGN + i );
		m_LabelMp[i].Create( "MP",
				lblStyle,
				CRect( 0, 0, 16, 16 ),
				this, IDC_STAT_WND_MP_BGN + i );
	}

	m_LabelDunLev.Create( "DunLev",
				lblStyle,
				CRect( 0, 0, 16, 16 ),
				this, IDC_STAT_WND_DUN_LEV );
	m_LabelTime.Create( "Time",
				lblStyle,
				CRect( 0, 0, 16, 16 ),
				this, IDC_STAT_WND_TIME );

	return 0;
}

void CStatWnd::OnClose()
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gWinPos[WIN_KIND_STAT].wipe( WIN_KIND_STAT );
	// bowkenken END

	// bowkenken
	// CFrameWnd::OnClose();
}

void CStatWnd::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO : ここにメッセージ ハンドラ コードを追加します。

	ReSize();
}

void CStatWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO : ここにメッセージ ハンドラ コードを追加します。
	// 描画メッセージで CFrameWnd::OnPaint() を呼び出さないでください。

	gGuiStat.redraw( false );
}

void CStatWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.handleKeyDown( nChar, nRepCnt, nFlags );
	// bowkenken END

	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CStatWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.setChar( nChar, true );
	// bowkenken END

	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}
