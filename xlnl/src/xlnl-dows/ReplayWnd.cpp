// ReplayWnd.cpp : 実装ファイル
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "ReplayWnd.h"
#include ".\replaywnd.h"

// bowkenken BEGIN
#include "../GlobalVar.h"
// bowkenken END


// CReplayWnd

IMPLEMENT_DYNCREATE(CReplayWnd, CFrameWnd)

CReplayWnd::CReplayWnd()
{
}

CReplayWnd::~CReplayWnd()
{
}


BEGIN_MESSAGE_MAP(CReplayWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	// bowkenken BEGIN
	ON_COMMAND( IDC_REPLAY_WND_BTN_TURN, CReplayWnd::OnButtonTurn )
	ON_COMMAND( IDC_REPLAY_WND_BTN_KEY_1, CReplayWnd::OnButtonKey1 )
	ON_COMMAND( IDC_REPLAY_WND_BTN_KEY_10, CReplayWnd::OnButtonKey10 )
	ON_COMMAND( IDC_REPLAY_WND_BTN_CONT, CReplayWnd::OnButtonCont )
	ON_COMMAND( IDC_REPLAY_WND_BTN_EXIT, CReplayWnd::OnButtonExit )
	// bowkenken END
END_MESSAGE_MAP()


// CReplayWnd メッセージ ハンドラ

int CReplayWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO :  ここに特定な作成コードを追加してください。

	// bowkenken BEGIN

	const long w = nBtnWidth;
	const long h = nBtnHeight;
	long x = 0;
	long y = 0;

	m_TextReplay.Create(
			(WS_VISIBLE | ES_LEFT | ES_READONLY | ES_AUTOHSCROLL),
			CRect( x, y, x + w, y + h * 2 ),
			this, IDC_REPLAY_WND_TEXT_REPLAY );
	y += h * 2;

	m_BtnTurn.Create( "Turn",
			(BS_PUSHBUTTON | WS_VISIBLE),
			CRect( x, y, x + w, y + h ),
			this, IDC_REPLAY_WND_BTN_TURN );
	y += h;

	m_BtnKey1.Create( "Key 1",
			(BS_PUSHBUTTON | WS_VISIBLE),
			CRect( x, y, x + w, y + h ),
			this, IDC_REPLAY_WND_BTN_KEY_1 );
	y += h;

	m_BtnKey10.Create( "Key 10",
			(BS_PUSHBUTTON | WS_VISIBLE),
			CRect( x, y, x + w, y + h ),
			this, IDC_REPLAY_WND_BTN_KEY_10 );
	y += h;

	m_BtnCont.Create( "Cont",
			(BS_PUSHBUTTON | WS_VISIBLE),
			CRect( x, y, x + w, y + h ),
			this, IDC_REPLAY_WND_BTN_CONT );
	y += h;

	m_BtnExit.Create( "Exit",
			(BS_PUSHBUTTON | WS_VISIBLE),
			CRect( x, y, x + w, y + h ),
			this, IDC_REPLAY_WND_BTN_EXIT );
	y += h;

	// bowkenken END

	return 0;
}

void CReplayWnd::OnClose()
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	gWinPos[WIN_KIND_REPLAY].wipe( WIN_KIND_REPLAY );
	// bowkenken END

	// bowkenken
	// CFrameWnd::OnClose();
}

// bowkenken BEGIN
void CReplayWnd::OnButtonTurn()
{
	gGuiReplay.turnClicked();
}

void CReplayWnd::OnButtonKey1()
{
	gGuiReplay.key1Clicked();
}

void CReplayWnd::OnButtonKey10()
{
	gGuiReplay.key10Clicked();
}

void CReplayWnd::OnButtonCont()
{
	gGuiReplay.contClicked();
}

void CReplayWnd::OnButtonExit()
{
	gGuiReplay.exitClicked();
}
// bowkenken END
