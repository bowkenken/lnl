// xlnl-dows.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
// bowkenken BEGIN
#include "MessageWnd.h"
#include "MenuWnd.h"
// bowkenken END
#include "xlnl-dows.h"
#include "MainFrm.h"

// bowkenken BEGIN
#include "Dir3d.h"
#include "Dir3dText.h"
#include "../gmain.h"
#include "../gmain-prot.h"
#include "../GlobalVar.h"
#include "../main-dows-prot.h"
// bowkenken END

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CxlnldowsApp

BEGIN_MESSAGE_MAP(CxlnldowsApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()


// CxlnldowsApp コンストラクション

CxlnldowsApp::CxlnldowsApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。

	// bowkenken BEGIN
	gFlagInitMfcDone = false;
	gFlagExit = false;
	m_pMainWnd = NULL;
	// bowkenken END
}

CxlnldowsApp::~CxlnldowsApp()
{
	if( m_pMainWnd != NULL ){
		m_pMainWnd->DestroyWindow();
		delete m_pMainWnd;
		m_pMainWnd = NULL;
	}

	// bowkenken BEGIN
#ifdef D_MFC
	g_Dir3d.Destroy();
#endif // D_MFC

	close_game( EXIT_SUCCESS );
	// bowkenken END
}

// 唯一の CxlnldowsApp オブジェクトです。

CxlnldowsApp theApp;

// CxlnldowsApp 初期化

BOOL CxlnldowsApp::InitInstance()
{
	// アプリケーション　マニフェストが　visual スタイルを有効にするために、
	// ComCtl32.dll バージョン 6　以降の使用を指定する場合は、
	// Windows XP に　InitCommonControls() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	InitCommonControls();

	CWinApp::InitInstance();

	// 標準初期化
	// これらの機能を使わずに、最終的な実行可能ファイルのサイズを縮小したい場合は、
	// 以下から、不要な初期化ルーチンを
	// 削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: この文字列を、会社名または組織名などの、
	// 適切な文字列に変更してください。
	SetRegistryKey(_T("xlnl-dows"));
	// メイン ウインドウを作成するとき、このコードは新しいフレーム ウインドウ オブジェクトを作成し、
	// それをアプリケーションのメイン ウインドウにセットします
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// フレームをリソースからロードして作成します
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	// 接尾辞が存在する場合にのみ DragAcceptFiles を呼び出してください。
	//  SDI アプリケーションでは、ProcessShellCommand の直後にこの呼び出しが発生しなければなりません。

	// bowkenken BEGIN
	m_pMainFrm = (CMainFrame *)pFrame;
	m_MesWnd.Create( NULL, "Message",
			(WS_OVERLAPPEDWINDOW),
			CRect( 0, 0, AREA_MAX_X * 32, 8 * 32 ) );
	m_MenuWnd.Create( NULL, "Menu",
			(WS_OVERLAPPEDWINDOW),
			CRect( 0, 0, 32, 32 ) );
	m_StatWnd.Create( NULL, "Status",
			(WS_OVERLAPPEDWINDOW),
			CRect( 0, 0, 256, 64 * 6 ) );
	m_ReplayWnd.Create( NULL, "Replay",
			(WS_OVERLAPPEDWINDOW),
			CRect( 0, 0, 256, 32 * 8 ) );

	main_dows( __argc, __argv );

	m_pszExeName = NULL;
	m_pszHelpFilePath = NULL;
	// bowkenken END

	return TRUE;
}

//bowkenken BEGIN
void CxlnldowsApp::InitWin()
{
}
//bowkenken END

// CxlnldowsApp メッセージ ハンドラ



// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CxlnldowsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CxlnldowsApp メッセージ ハンドラ

