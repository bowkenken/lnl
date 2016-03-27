// InputLineDlg.cpp : �����ե�����
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "InputLineDlg.h"
#include ".\inputlinedlg.h"

#include "../GlobalVar.h"


// CInputLineDlg ��������

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


// CInputLineDlg ��å����� �ϥ�ɥ�

BOOL CInputLineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  �����˽�������ɲä��Ƥ�������

	gWinPos[WIN_KIND_INPUT_STRING].draw( WIN_KIND_INPUT_STRING, true );

	m_Edit.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �㳰 : OCX �ץ�ѥƥ� �ڡ�����ɬ�� FALSE ���֤��ޤ���
}

void CInputLineDlg::OnClose()
{
	// TODO : �����˥�å����� �ϥ�ɥ� �����ɤ��ɲä��뤫������ν�����ƤӽФ��ޤ���

	gWinPos[WIN_KIND_INPUT_STRING].wipe( WIN_KIND_INPUT_STRING, true );

	CDialog::OnClose();
}

void CInputLineDlg::OnOK()
{
	// TODO : ����������ʥ����ɤ��ɲä��뤫���⤷���ϴ��ܥ��饹��ƤӽФ��Ƥ���������

	gWinPos[WIN_KIND_INPUT_STRING].wipe( WIN_KIND_INPUT_STRING, true );

	CDialog::OnOK();
}

void CInputLineDlg::OnCancel()
{
	// TODO : ����������ʥ����ɤ��ɲä��뤫���⤷���ϴ��ܥ��饹��ƤӽФ��Ƥ���������

	gWinPos[WIN_KIND_INPUT_STRING].wipe( WIN_KIND_INPUT_STRING, true );

	CDialog::OnCancel();
}
