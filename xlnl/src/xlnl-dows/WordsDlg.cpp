// WordsDlg.cpp : �����ե�����
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "WordsDlg.h"
#include ".\wordsdlg.h"

#include "../GlobalVar.h"


// CWordsDlg ��������

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


// CWordsDlg ��å����� �ϥ�ɥ�

BOOL CWordsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  �����˽�������ɲä��Ƥ�������

	gWinPos[WIN_KIND_WORDS].draw( WIN_KIND_WORDS, true );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �㳰 : OCX �ץ�ѥƥ� �ڡ�����ɬ�� FALSE ���֤��ޤ���
}

void CWordsDlg::OnClose()
{
	// TODO : �����˥�å����� �ϥ�ɥ� �����ɤ��ɲä��뤫������ν�����ƤӽФ��ޤ���

	gWinPos[WIN_KIND_WORDS].wipe( WIN_KIND_WORDS, true );

	CDialog::OnClose();
}

void CWordsDlg::OnOK()
{
	// TODO : ����������ʥ����ɤ��ɲä��뤫���⤷���ϴ��ܥ��饹��ƤӽФ��Ƥ���������

	gWinPos[WIN_KIND_WORDS].wipe( WIN_KIND_WORDS, true );

	CDialog::OnOK();
}

void CWordsDlg::OnCancel()
{
	// TODO : ����������ʥ����ɤ��ɲä��뤫���⤷���ϴ��ܥ��饹��ƤӽФ��Ƥ���������

	gWinPos[WIN_KIND_WORDS].wipe( WIN_KIND_WORDS, true );

	CDialog::OnCancel();
}
