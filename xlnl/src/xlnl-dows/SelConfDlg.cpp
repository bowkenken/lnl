// SelConfDlg.cpp : �����ե�����
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "SelConfDlg.h"
#include ".\selconfdlg.h"

//bowkenken BEGIN
#include "../GlobalVar.h"
#include "../SelConf.h"
//bowkenken END


// CSelConfDlg ��������

IMPLEMENT_DYNAMIC(CSelConfDlg, CDialog)
CSelConfDlg::CSelConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelConfDlg::IDD, pParent)
	, m_ListDdx(_T(""))
{
}

CSelConfDlg::~CSelConfDlg()
{
}

void CSelConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEL_CONF_LIST, m_List);
	DDX_LBString(pDX, IDC_SEL_CONF_LIST, m_ListDdx);
	DDX_Control(pDX, IDC_SEL_CONF_TITLE, m_stTitle);
}


BEGIN_MESSAGE_MAP(CSelConfDlg, CDialog)
	ON_LBN_SELCHANGE(IDC_SEL_CONF_LIST, OnLbnSelchangeSelConfList)
	ON_LBN_DBLCLK(IDC_SEL_CONF_LIST, OnLbnDblclkSelConfList)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSelConfDlg ��å����� �ϥ�ɥ�

BOOL CSelConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  �����˽�������ɲä��Ƥ�������

	//bowkenken BEGIN
	gSelConf.setListGui();
	m_stTitle.SetWindowText( MSG_SEL_CONF_LABEL );

	m_List.SetCurSel( m_List.GetCount() - 1 );
	OnLbnSelchangeSelConfList();
	//bowkenken END

	return TRUE;  // return TRUE unless you set the focus to a control
	// �㳰 : OCX �ץ�ѥƥ� �ڡ�����ɬ�� FALSE ���֤��ޤ���
}

void CSelConfDlg::OnLbnSelchangeSelConfList()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	//bowkenken BEGIN
	int n = m_List.GetCurSel();
	if( n == LB_ERR )
		return;

	CString tmp;
	m_List.GetText( n, tmp );
	WSCstring str = tmp;
	WSCstring w = str.getWord( 1, STR_WORD_SEP_SEL_CONF );

	gSelConf.select( strtol( w, NULL, 10 ) );
	//bowkenken END
}

void CSelConfDlg::OnLbnDblclkSelConfList()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	OnOK();
}

void CSelConfDlg::OnBnClickedOk()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	OnOK();
}
