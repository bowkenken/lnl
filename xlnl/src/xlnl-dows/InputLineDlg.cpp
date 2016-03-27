// InputLineDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "InputLineDlg.h"
#include ".\inputlinedlg.h"

#include "../GlobalVar.h"


// CInputLineDlg ダイアログ

IMPLEMENT_DYNAMIC(CInputLineDlg, CDialog)
CInputLineDlg::CInputLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputLineDlg::IDD, pParent)
	, m_EditDdx(_T(""))
{
}

CInputLineDlg::~CInputLineDlg()
{
}

void CInputLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT_LINE_EDIT, m_Edit);
	DDX_Text(pDX, IDC_INPUT_LINE_EDIT, m_EditDdx);
}


BEGIN_MESSAGE_MAP(CInputLineDlg, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CInputLineDlg メッセージ ハンドラ

BOOL CInputLineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  ここに初期化を追加してください

	gWinPos[WIN_KIND_INPUT_STRING].draw( WIN_KIND_INPUT_STRING, true );

	m_Edit.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CInputLineDlg::OnClose()
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	gWinPos[WIN_KIND_INPUT_STRING].wipe( WIN_KIND_INPUT_STRING, true );

	CDialog::OnClose();
}

void CInputLineDlg::OnOK()
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	gWinPos[WIN_KIND_INPUT_STRING].wipe( WIN_KIND_INPUT_STRING, true );

	CDialog::OnOK();
}

void CInputLineDlg::OnCancel()
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	gWinPos[WIN_KIND_INPUT_STRING].wipe( WIN_KIND_INPUT_STRING, true );

	CDialog::OnCancel();
}
