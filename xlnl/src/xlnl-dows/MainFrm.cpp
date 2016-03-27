// MainFrm.cpp : CMainFrame クラスの実装
//

#include "stdafx.h"
#include "xlnl-dows.h"

// bowkenken BEGIN
#include "../msg-t.h"
#include "../draw.h"
#include "../menu.h"
#include "../msg-prot.h"
#include "../imenu-prot.h"

#include "Dir3d.h"
#include "../GlobalVar.h"
#include "../scene.h"
#include "../scene-prot.h"
#include "../MouseMap.h"
// bowkenken END

#include "MainFrm.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// bowkenken BEGIN
static void CALLBACK MMTimerFunc(
	UINT uID, UINT dmy1, DWORD_PTR dwpUser,
	DWORD_PTR dmy2, DWORD_PTR dmy3
);
static void CALLBACK MMTimerFuncMousePress(
	UINT uID, UINT dmy1, DWORD_PTR dwpUser,
	DWORD_PTR dmy2, DWORD_PTR dmy3
);
// bowkenken END

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	// bowkenken BEGIN
	ON_MESSAGE( WM_USER_TIMER, OnUserTimer )
	// bowkenken END
	ON_WM_CLOSE()
	ON_COMMAND(ID_CMD_KEY_EXEC, OnCmdKeyExec)
	ON_COMMAND(ID_CMD_KEY_EXEC_CONT, OnCmdKeyExecCont)
	ON_UPDATE_COMMAND_UI(ID_CMD_KEY_EXEC_CONT, OnUpdateCmdKeyExecCont)
	ON_COMMAND(ID_CMD_KEY_Z, OnCmdKeyZ)
	ON_COMMAND(ID_CMD_KEY_X, OnCmdKeyX)
	ON_COMMAND(ID_CMD_KEY_C, OnCmdKeyC)
	ON_COMMAND(ID_CMD_KEY_V, OnCmdKeyV)
	ON_COMMAND(ID_CMD_KEY_CANCEL, OnCmdKeyCancel)
	ON_COMMAND(ID_CMD_KEY_OK, OnCmdKeyOk)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケータ
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame コンストラクション/デストラクション

CMainFrame::CMainFrame()
{
	// TODO: メンバ初期化コードをここに追加してください。

	// bowkenken BEGIN
	m_TimerNestFlag = 0;
	// bowkenken END
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// フレームのクライアント領域全体を占めるビューを作成します。
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0(MSG_ERR_DOWS_CREATE_VIEW);
		return -1;
	}
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT,
		WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS
		| CBRS_FLYBY | CBRS_SIZE_DYNAMIC)
		|| !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0(MSG_ERR_DOWS_CREATE_TOOL_BAR);
		return -1;      // 作成できませんでした。
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0(MSG_ERR_DOWS_CREATE_STATUS_BAR);
		return -1;      // 作成できませんでした。
	}
	// TODO: ツール バーをドッキング可能にしない場合は、これらの 3 行を削除してください。
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// bowkenken BEGIN

	gWinPos[WIN_KIND_MAP].draw( WIN_KIND_MAP );

	// マルチ・メディア・タイマー
	SetTimer();

	//
	PostMessage(WM_PAINT);

	// bowkenken END

	return 0;
}

void CMainFrame::SetTimer()
{
	uMs = 1000 * g_Dir3d.uFrameRate / 60;
	TIMECAPS tc;
	::timeGetDevCaps( &tc, sizeof( TIMECAPS ) );

	if( uMs < tc.wPeriodMin )
		uMs = tc.wPeriodMin;
	if( uMs > tc.wPeriodMax )
		uMs = tc.wPeriodMax;

	m_TimerNestFlag = 1;
	::timeBeginPeriod( uMs );
	MMRESULT nTimId = ::timeSetEvent(
			uMs, 1, MMTimerFunc,
			(DWORD_PTR)GetSafeHwnd(), TIME_PERIODIC );

	if( nTimId == NULL ){
		::timeEndPeriod( uMs );
		::AfxMessageBox( MSG_ERR_DOWS_CREATE_TIMER );

		m_TimerNestFlag = 0;

		return;
	}

	// マウス・プレス

	nPressTimer = 1000 * PRESS_TIMER_FRAME_RATE / 60;

	if( nPressTimer < tc.wPeriodMin )
		nPressTimer = tc.wPeriodMin;
	if( nPressTimer > tc.wPeriodMax )
		nPressTimer = tc.wPeriodMax;

	::timeBeginPeriod( nPressTimer );
	nTimId = ::timeSetEvent(
			nPressTimer, 1, MMTimerFuncMousePress,
			(DWORD_PTR)GetSafeHwnd(), TIME_PERIODIC );

	if( nTimId == NULL ){
		::timeEndPeriod( nPressTimer );
		::AfxMessageBox( MSG_ERR_DOWS_CREATE_TIMER );

		return;
	}

	::timeEndPeriod( nPressTimer );
}

void CMainFrame::StartTimer()
{
	m_TimerNestFlag++;
	if( m_TimerNestFlag > 1 )
		return;

	if( !gFlagExit )
		::timeBeginPeriod( uMs );
}

void CMainFrame::StopTimer()
{
	m_TimerNestFlag--;
	if( m_TimerNestFlag > 0 )
		return;

	::timeEndPeriod( uMs );
}

CStatusBar &CMainFrame::GetStatusBar()
{
	return m_wndStatusBar;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	// bowkenken BEGIN
	cs.cx = AREA_MAX_X * 32;
	cs.cy = AREA_MAX_Y * 32;
	// bowkenken END

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}


// CMainFrame 診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame メッセージ ハンドラ

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// ビュー ウィンドウにフォーカスを与えます。
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ビューに最初にコマンドを処理する機会を与えます。
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// それ以外の場合は、既定の処理を行います。
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	// bowkenken BEGIN
	LRESULT resMain = CFrameWnd::WindowProc(
			message, wParam, lParam );

	LRESULT resDir3d;
	if( g_Dir3d.WindowProc(
			message, wParam, lParam, &resDir3d ) ){
		return resDir3d;
	}

	return resMain;
	// bowkenken END

	// bowkenken
	// return CFrameWnd::WindowProc(message, wParam, lParam);
}

// bowkenken BEGIN

static volatile LONG nTimerNestFlag = 0;

static void CALLBACK MMTimerFunc(
	UINT uID, UINT dmy1, DWORD_PTR dwpUser,
	DWORD_PTR dmy2, DWORD_PTR dmy3
)
{
	if( theApp.m_pMainFrm == NULL )
		return;

	if( ::InterlockedExchangeAdd( &nTimerNestFlag, 1 ) > 0 ){
		theApp.m_pMainFrm->StopTimer();
		Sleep( 50 );
		theApp.m_pMainFrm->StartTimer();
	}

	if( gFlagExit )
		return;

	if( !::PostMessage( (HWND)dwpUser, WM_USER_TIMER,
			(WPARAM)theApp.m_pMainFrm->uMs, 0 ) ){
		TRACE( "Error: MMTimerFunc: "
				"\"::PostMessage\"\n" );
	}
}

static void CALLBACK MMTimerFuncMousePress(
	UINT uID, UINT dmy1, DWORD_PTR dwpUser,
	DWORD_PTR dmy2, DWORD_PTR dmy3
)
{
	if( theApp.m_pMainFrm == NULL )
		return;
	if( gFlagExit )
		return;

	if( !::PostMessage( (HWND)dwpUser, WM_USER_TIMER,
			(WPARAM)theApp.m_pMainFrm->nPressTimer, 0 ) ){
		TRACE( "Error: MMTimerFuncMousePress: "
				"\"::PostMessage\"\n" );
	}
}

LRESULT CMainFrame::OnUserTimer(
	WPARAM wParam, LPARAM lParam
)
{
	if( gFlagExit )
		return 0;

	if( wParam == uMs )
		OnUserTimerDir3d();
	if( wParam == nPressTimer )
		OnUserTimerMouseMap();

	return 0;
}

void CMainFrame::OnUserTimerDir3d()
{
	gJoystick.checkEvent();

	if( ::InterlockedDecrement( &nTimerNestFlag ) > 0 )
		return;

	TRY {
		if( get_scene() == SCENE_N_LAST_BOSS ){
			g_Dir3d.Refresh();
		} else if( chk_scene_group( SCENE_GROUP_N_TITLE ) ){
			g_Dir3d.Refresh();
		} else if( chk_scene_group( SCENE_GROUP_N_ENDING ) ){
			g_Dir3d.Refresh();
		} else if( chk_scene_group( SCENE_GROUP_N_GAME_OVER ) ){
			g_Dir3d.Refresh();
		} else {
			if( g_Dir3d.CheckRefreshRequest() ){
				g_Dir3d.SetRefreshRequest( false );

				g_Dir3d.Refresh();
			}
		}
	} CATCH( CException, e ){
	} END_CATCH

	return;
}

void CMainFrame::OnUserTimerMouseMap()
{
	callBackPressTimer();
}

// bowkenken END

void CMainFrame::OnClose()
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	// bowkenken BEGIN
	if( gFlagExit ){
		StopTimer();
		::timeEndPeriod( uMs );

		::Sleep( uMs * 2 );
		CFrameWnd::OnClose();
	} else {
		gKey.setChar( 'Q', TRUE );
	}
	// bowkenken END

	// bowkenken
	// CFrameWnd::OnClose();
}

void CMainFrame::OnCmdKeyExec()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	// bowkenken BEGIN
	gKey.setChar( '.', TRUE );
	// bowkenken END
}

void CMainFrame::OnCmdKeyExecCont()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	// bowkenken BEGIN
	if( get_continue_exec_mode() ){
		gKey.setChar( '0', TRUE );
		gKey.setChar( '0', FALSE );
	} else {
		gKey.setChar( CMD_KEY_CONT_EXEC, TRUE );
	}
	// bowkenken END
}

void CMainFrame::OnUpdateCmdKeyExecCont(CCmdUI *pCmdUI)
{
	// TODO : ここにコマンド更新 UI ハンドラ コードを追加します。

	// bowkenken BEGIN
#if 0
//@@@
	if( !get_continue_exec_mode() )
		pCmdUI->SetCheck( !!get_continue_exec_mode() );
#endif
	// bowkenken END
}

void CMainFrame::OnCmdKeyZ()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	// bowkenken BEGIN
	gKey.setChar( '/', TRUE );
	// bowkenken END
}

void CMainFrame::OnCmdKeyX()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	// bowkenken BEGIN
	gKey.setChar( '*', TRUE );
	// bowkenken END
}

void CMainFrame::OnCmdKeyC()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	// bowkenken BEGIN
	gKey.setChar( '-', TRUE );
	// bowkenken END
}

void CMainFrame::OnCmdKeyV()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	// bowkenken BEGIN
	gKey.setChar( '+', TRUE );
	// bowkenken END
}

void CMainFrame::OnCmdKeyCancel()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	// bowkenken BEGIN
	switch( get_lang_kind() ){
	case LANG_KIND_ENGLISH:
		KeyOk();
		break;
	case LANG_KIND_JAPANESE_EUC:
	case LANG_KIND_JAPANESE_UTF_8:
	case LANG_KIND_JAPANESE_SJIS:
	case LANG_KIND_MAX_N:
	default:
		KeyCancel();
		break;
	}
	// bowkenken END
}

void CMainFrame::OnCmdKeyOk()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	// bowkenken BEGIN
	switch( get_lang_kind() ){
	case LANG_KIND_ENGLISH:
		KeyCancel();
		break;
	case LANG_KIND_JAPANESE_EUC:
	case LANG_KIND_JAPANESE_UTF_8:
	case LANG_KIND_JAPANESE_SJIS:
	case LANG_KIND_MAX_N:
	default:
		KeyOk();
		break;
	}
	// bowkenken END
}

void CMainFrame::KeyCancel()
{
	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) )
		gSelMbrGraph->cancel();
	else
		gKey.setChar( '0' );
}

void CMainFrame::KeyOk()
{
	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) )
		gSelMbrGraph->ok();
	else
		gKey.setChar( 'M' - '@' );
}
