// WordsDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "WordsDlg.h"
#include ".\wordsdlg.h"

#include "../GlobalVar.h"


// CWordsDlg ダイアログ

IMPLEMENT_DYNAMIC(CWordsDlg, CDialog)
CWordsDlg::CWordsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWordsDlg::IDD, pParent)
	, m_EditDdx(_T(""))
{
}

CWordsDlg::~CWordsDlg()
{
}

void CWordsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WORDS_EDIT, m_EditDdx);
}


BEGIN_MESSAGE_MAP(CWordsDlg, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CWordsDlg メッセージ ハンドラ

BOOL CWordsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  ここに初期化を追加してください

	gWinPos[WIN_KIND_WORDS].draw( WIN_KIND_WORDS, true );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CWordsDlg::OnClose()
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	gWinPos[WIN_KIND_WORDS].wipe( WIN_KIND_WORDS, true );

	CDialog::OnClose();
}

void CWordsDlg::OnOK()
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	gWinPos[WIN_KIND_WORDS].wipe( WIN_KIND_WORDS, true );

	CDialog::OnOK();
}

void CWordsDlg::OnCancel()
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	gWinPos[WIN_KIND_WORDS].wipe( WIN_KIND_WORDS, true );

	CDialog::OnCancel();
}
