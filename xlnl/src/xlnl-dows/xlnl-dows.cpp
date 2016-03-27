// xlnl-dows.cpp : ���ץꥱ�������Υ��饹ư���������ޤ���
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


// CxlnldowsApp ���󥹥ȥ饯�����

CxlnldowsApp::CxlnldowsApp()
{
	// TODO: ���ΰ��֤˹����ѥ����ɤ��ɲä��Ƥ���������
	// ������ InitInstance ��ν��פʽ���������򤹤٤Ƶ��Ҥ��Ƥ���������

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

// ͣ��� CxlnldowsApp ���֥������ȤǤ���

CxlnldowsApp theApp;

// CxlnldowsApp �����

BOOL CxlnldowsApp::InitInstance()
{
	// ���ץꥱ������󡡥ޥ˥ե����Ȥ���visual ���������ͭ���ˤ��뤿��ˡ�
	// ComCtl32.dll �С������ 6���ʹߤλ��Ѥ���ꤹ����ϡ�
	// Windows XP �ˡ�InitCommonControls() ��ɬ�פǤ�������ʤ���С�������ɥ������Ϥ��٤Ƽ��Ԥ��ޤ���
	InitCommonControls();

	CWinApp::InitInstance();

	// ɸ������
	// �����ε�ǽ��Ȥ鷺�ˡ��ǽ�Ū�ʼ¹Բ�ǽ�ե�����Υ�������̾����������ϡ�
	// �ʲ����顢���פʽ�����롼�����
	// ������Ƥ���������
	// ���꤬��Ǽ����Ƥ���쥸���ȥ� �������ѹ����ޤ���
	// TODO: ����ʸ����򡢲��̾�ޤ����ȿ�̾�ʤɤΡ�
	// Ŭ�ڤ�ʸ������ѹ����Ƥ���������
	SetRegistryKey(_T("xlnl-dows"));
	// �ᥤ�� ������ɥ����������Ȥ������Υ����ɤϿ������ե졼�� ������ɥ� ���֥������Ȥ��������
	// ����򥢥ץꥱ�������Υᥤ�� ������ɥ��˥��åȤ��ޤ�
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// �ե졼���꥽����������ɤ��ƺ������ޤ�
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	// �ᥤ�� ������ɥ�����������줿�Τǡ�ɽ���ȹ�����Ԥ��ޤ���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	// ��������¸�ߤ�����ˤΤ� DragAcceptFiles ��ƤӽФ��Ƥ���������
	//  SDI ���ץꥱ�������Ǥϡ�ProcessShellCommand ��ľ��ˤ��θƤӽФ���ȯ�����ʤ���Фʤ�ޤ���

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

// CxlnldowsApp ��å����� �ϥ�ɥ�



// ���ץꥱ�������ΥС���������˻Ȥ��� CAboutDlg ��������

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �������� �ǡ���
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ���ݡ���

// ����
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

// ����������¹Ԥ��뤿��Υ��ץꥱ������� ���ޥ��
void CxlnldowsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CxlnldowsApp ��å����� �ϥ�ɥ�

