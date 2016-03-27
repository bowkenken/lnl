// ClassEditDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "ClassEditDlg.h"
#include ".\classeditdlg.h"

#include "../GlobalVar.h"


// CClassEditDlg ダイアログ

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


// CClassEditDlg メッセージ ハンドラ

BOOL CClassEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  ここに初期化を追加してください

	gGuiClassEdit.redraw();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CClassEditDlg::OnBnClickedClassEditHpP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_HP );
}

void CClassEditDlg::OnBnClickedClassEditMpP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_MP );
}

void CClassEditDlg::OnBnClickedClassEditDexP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_DEX );
}

void CClassEditDlg::OnBnClickedClassEditStrP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_STR );
}

void CClassEditDlg::OnBnClickedClassEditAgiP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_AGI );
}

void CClassEditDlg::OnBnClickedClassEditIntP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_INT );
}

void CClassEditDlg::OnBnClickedClassEditWisP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_WIS );
}

void CClassEditDlg::OnBnClickedClassEditChaP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_CHA );
}

void CClassEditDlg::OnBnClickedClassEditFigP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_FIG );
}

void CClassEditDlg::OnBnClickedClassEditMonP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_MON );
}

void CClassEditDlg::OnBnClickedClassEditHunP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_HUN );
}

void CClassEditDlg::OnBnClickedClassEditThiP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_THI );
}

void CClassEditDlg::OnBnClickedClassEditMagP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_MAG );
}

void CClassEditDlg::OnBnClickedClassEditSorP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_SOR );
}

void CClassEditDlg::OnBnClickedClassEditEncP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_ENC );
}

void CClassEditDlg::OnBnClickedClassEditSumP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_SUM );
}

void CClassEditDlg::OnBnClickedClassEditPriP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_PRI );
}

void CClassEditDlg::OnBnClickedClassEditShaP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_SHA );
}

void CClassEditDlg::OnBnClickedClassEditBarP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_BAR );
}

void CClassEditDlg::OnBnClickedClassEditNinP()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.plusClicked( ABL_KIND_NIN );
}

void CClassEditDlg::OnBnClickedClassEditHpM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_HP );
}

void CClassEditDlg::OnBnClickedClassEditMpM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_MP );
}

void CClassEditDlg::OnBnClickedClassEditDexM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_DEX );
}

void CClassEditDlg::OnBnClickedClassEditStrM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_STR );
}

void CClassEditDlg::OnBnClickedClassEditAgiM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_AGI );
}

void CClassEditDlg::OnBnClickedClassEditIntM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_INT );
}

void CClassEditDlg::OnBnClickedClassEditWisM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_WIS );
}

void CClassEditDlg::OnBnClickedClassEditChaM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_CHA );
}

void CClassEditDlg::OnBnClickedClassEditFigM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_FIG );
}

void CClassEditDlg::OnBnClickedClassEditMonM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_MON );
}

void CClassEditDlg::OnBnClickedClassEditHunM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_HUN );
}

void CClassEditDlg::OnBnClickedClassEditThiM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_THI );
}

void CClassEditDlg::OnBnClickedClassEditMagM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_MAG );
}

void CClassEditDlg::OnBnClickedClassEditSorM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_SOR );
}

void CClassEditDlg::OnBnClickedClassEditEncM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_ENC );
}

void CClassEditDlg::OnBnClickedClassEditSumM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_SUM );
}

void CClassEditDlg::OnBnClickedClassEditPriM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_PRI );
}

void CClassEditDlg::OnBnClickedClassEditShaM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_SHA );
}

void CClassEditDlg::OnBnClickedClassEditBarM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_BAR );
}

void CClassEditDlg::OnBnClickedClassEditNinM()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.minusClicked( ABL_KIND_NIN );
}

void CClassEditDlg::OnBnClickedOk()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.exitClicked();
	OnOK();
}

void CClassEditDlg::OnBnClickedCancel()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	gGuiClassEdit.exitClicked();
	OnCancel();
}
