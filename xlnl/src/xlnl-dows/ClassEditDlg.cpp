// ClassEditDlg.cpp : �����ե�����
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "ClassEditDlg.h"
#include ".\classeditdlg.h"

#include "../GlobalVar.h"


// CClassEditDlg ��������

IMPLEMENT_DYNAMIC(CClassEditDlg, CDialog)
CClassEditDlg::CClassEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClassEditDlg::IDD, pParent)
	, mEditName(_T(""))
	, mLabelTotalValue(_T(""))
{
}

CClassEditDlg::~CClassEditDlg()
{
}

void CClassEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CLASS_EDIT_TEXT, mEditName);
	DDX_Text(pDX, IDC_CLASS_EDIT_TOTAL, mLabelTotalValue);
}


BEGIN_MESSAGE_MAP(CClassEditDlg, CDialog)
	ON_BN_CLICKED(IDC_CLASS_EDIT_HP_P, OnBnClickedClassEditHpP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_MP_P, OnBnClickedClassEditMpP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_DEX_P, OnBnClickedClassEditDexP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_STR_P, OnBnClickedClassEditStrP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_AGI_P, OnBnClickedClassEditAgiP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_INT_P, OnBnClickedClassEditIntP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_WIS_P, OnBnClickedClassEditWisP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_CHA_P, OnBnClickedClassEditChaP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_FIG_P, OnBnClickedClassEditFigP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_MON_P, OnBnClickedClassEditMonP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_HUN_P, OnBnClickedClassEditHunP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_THI_P, OnBnClickedClassEditThiP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_MAG_P, OnBnClickedClassEditMagP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_SOR_P, OnBnClickedClassEditSorP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_ENC_P, OnBnClickedClassEditEncP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_SUM_P, OnBnClickedClassEditSumP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_PRI_P, OnBnClickedClassEditPriP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_SHA_P, OnBnClickedClassEditShaP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_BAR_P, OnBnClickedClassEditBarP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_NIN_P, OnBnClickedClassEditNinP)
	ON_BN_CLICKED(IDC_CLASS_EDIT_HP_M, OnBnClickedClassEditHpM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_MP_M, OnBnClickedClassEditMpM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_DEX_M, OnBnClickedClassEditDexM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_STR_M, OnBnClickedClassEditStrM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_AGI_M, OnBnClickedClassEditAgiM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_INT_M, OnBnClickedClassEditIntM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_WIS_M, OnBnClickedClassEditWisM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_CHA_M, OnBnClickedClassEditChaM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_FIG_M, OnBnClickedClassEditFigM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_MON_M, OnBnClickedClassEditMonM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_HUN_M, OnBnClickedClassEditHunM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_THI_M, OnBnClickedClassEditThiM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_MAG_M, OnBnClickedClassEditMagM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_SOR_M, OnBnClickedClassEditSorM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_ENC_M, OnBnClickedClassEditEncM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_SUM_M, OnBnClickedClassEditSumM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_PRI_M, OnBnClickedClassEditPriM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_SHA_M, OnBnClickedClassEditShaM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_BAR_M, OnBnClickedClassEditBarM)
	ON_BN_CLICKED(IDC_CLASS_EDIT_NIN_M, OnBnClickedClassEditNinM)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CClassEditDlg ��å����� �ϥ�ɥ�

BOOL CClassEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  �����˽�������ɲä��Ƥ�������

	gGuiClassEdit.redraw();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �㳰 : OCX �ץ�ѥƥ� �ڡ�����ɬ�� FALSE ���֤��ޤ���
}

void CClassEditDlg::OnBnClickedClassEditHpP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_HP );
}

void CClassEditDlg::OnBnClickedClassEditMpP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_MP );
}

void CClassEditDlg::OnBnClickedClassEditDexP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_DEX );
}

void CClassEditDlg::OnBnClickedClassEditStrP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_STR );
}

void CClassEditDlg::OnBnClickedClassEditAgiP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_AGI );
}

void CClassEditDlg::OnBnClickedClassEditIntP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_INT );
}

void CClassEditDlg::OnBnClickedClassEditWisP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_WIS );
}

void CClassEditDlg::OnBnClickedClassEditChaP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_CHA );
}

void CClassEditDlg::OnBnClickedClassEditFigP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_FIG );
}

void CClassEditDlg::OnBnClickedClassEditMonP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_MON );
}

void CClassEditDlg::OnBnClickedClassEditHunP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_HUN );
}

void CClassEditDlg::OnBnClickedClassEditThiP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_THI );
}

void CClassEditDlg::OnBnClickedClassEditMagP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_MAG );
}

void CClassEditDlg::OnBnClickedClassEditSorP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_SOR );
}

void CClassEditDlg::OnBnClickedClassEditEncP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_ENC );
}

void CClassEditDlg::OnBnClickedClassEditSumP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_SUM );
}

void CClassEditDlg::OnBnClickedClassEditPriP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_PRI );
}

void CClassEditDlg::OnBnClickedClassEditShaP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_SHA );
}

void CClassEditDlg::OnBnClickedClassEditBarP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_BAR );
}

void CClassEditDlg::OnBnClickedClassEditNinP()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.plusClicked( ABL_KIND_NIN );
}

void CClassEditDlg::OnBnClickedClassEditHpM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_HP );
}

void CClassEditDlg::OnBnClickedClassEditMpM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_MP );
}

void CClassEditDlg::OnBnClickedClassEditDexM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_DEX );
}

void CClassEditDlg::OnBnClickedClassEditStrM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_STR );
}

void CClassEditDlg::OnBnClickedClassEditAgiM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_AGI );
}

void CClassEditDlg::OnBnClickedClassEditIntM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_INT );
}

void CClassEditDlg::OnBnClickedClassEditWisM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_WIS );
}

void CClassEditDlg::OnBnClickedClassEditChaM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_CHA );
}

void CClassEditDlg::OnBnClickedClassEditFigM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_FIG );
}

void CClassEditDlg::OnBnClickedClassEditMonM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_MON );
}

void CClassEditDlg::OnBnClickedClassEditHunM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_HUN );
}

void CClassEditDlg::OnBnClickedClassEditThiM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_THI );
}

void CClassEditDlg::OnBnClickedClassEditMagM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_MAG );
}

void CClassEditDlg::OnBnClickedClassEditSorM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_SOR );
}

void CClassEditDlg::OnBnClickedClassEditEncM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_ENC );
}

void CClassEditDlg::OnBnClickedClassEditSumM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_SUM );
}

void CClassEditDlg::OnBnClickedClassEditPriM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_PRI );
}

void CClassEditDlg::OnBnClickedClassEditShaM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_SHA );
}

void CClassEditDlg::OnBnClickedClassEditBarM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_BAR );
}

void CClassEditDlg::OnBnClickedClassEditNinM()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.minusClicked( ABL_KIND_NIN );
}

void CClassEditDlg::OnBnClickedOk()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.exitClicked();
	OnOK();
}

void CClassEditDlg::OnBnClickedCancel()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	gGuiClassEdit.exitClicked();
	OnCancel();
}
