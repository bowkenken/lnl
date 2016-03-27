// MenuWnd.cpp : 実装ファイル
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "MenuWnd.h"
#include ".\menuwnd.h"

// bowkenken BEGIN
#include "../GuiMenu.h"
#include "../Key.h"
#include "../GlobalVar.h"
// bowkenken END

// CMenuWnd

IMPLEMENT_DYNCREATE(CMenuWnd, CFrameWnd)

CMenuWnd::CMenuWnd()
{
}

CMenuWnd::~CMenuWnd()
{
}


BEGIN_MESSAGE_MAP(CMenuWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CMenuWnd メッセージ ハンドラ

int CMenuWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO :  ここに特定な作成コードを追加してください。

	// bowkenken BEGIN

	const long w = nBtnWidth;
	const long h = nBtnHeight;
	long x = 0;
	long y = 0;

	m_BtnPrevPage.Create( " << ",
			(BS_PUSHBUTTON | WS_VISIBLE),
			CRect( x, y, x + w, y + h ),
			this, IDC_MENU_WND_BTN_PREV_PAGE );
	x += w;

	m_LblPage.Create(
			(WS_VISIBLE | ES_CENTER | ES_READONLY),
			CRect( x, y, x + w, y + h ),
			this, IDC_MENU_WND_LABEL_PAGE );
	x += w;

	m_BtnNextPage.Create( " >> ",
			(BS_PUSHBUTTON | WS_VISIBLE),
			CRect( x, y, x + w, y + h ),
			this, IDC_MENU_WND_BTN_NEXT_PAGE );
	x += w;

	m_BtnCancel.Create( MSG_GUI_MENU_CANCEL_ON,
			(BS_PUSHBUTTON | WS_VISIBLE),
			CRect( x, y, x + w, y + h ),
			this, IDC_MENU_WND_BTN_CANCEL );
	x += w;

	m_BtnCancelAll.Create( MSG_GUI_MENU_CANCEL_ALL_ON,
			(BS_PUSHBUTTON | WS_VISIBLE),
			CRect( x, y, x + w, y + h ),
			this, IDC_MENU_WND_BTN_CANCEL_ALL );
	x += w;

	x = 0;
	y += h;

	for( long i = IDC_MENU_WND_BTN_BGN;
			i <= IDC_MENU_WND_BTN_END; i++ ){
		long n = i - IDC_MENU_WND_BTN_BGN;
		if( n >= MENU_MAX_N_PER_PAGE )
			break;

		m_aBtn[n].Create( "button",
				(BS_PUSHBUTTON | BS_LEFT | WS_VISIBLE),
				CRect( x, y, x + 128, y + h ),
				this, i );

		y += h;
	}

	// bowkenken END

	return 0;
}

void CMenuWnd::OnClose()
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gWinPos[WIN_KIND_MENU].wipe( WIN_KIND_MENU );
	// bowkenken END

	// bowkenken
	// CFrameWnd::OnClose();
}

void CMenuWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.handleKeyDown( nChar, nRepCnt, nFlags );
	// bowkenken END

	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMenuWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gKey.setChar( nChar, true );
	// bowkenken END

	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}
