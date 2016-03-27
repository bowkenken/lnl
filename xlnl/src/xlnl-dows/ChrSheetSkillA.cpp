// ChrSheetSkillA.cpp : 実装ファイル
//

#include "stdafx.h"
#include "../misc.h"
#include "../draw.h"
#include "../menu.h"
#include "../skill.h"
#include "../party.h"
#include "../misc-prot.h"
#include "../imenu-prot.h"
#include "../skill-prot.h"
#include "../party-prot.h"
#include "xlnl-dows.h"
#include "ChrSheetSkillA.h"
#include ".\chrsheetskilla.h"
#include "../GlobalVar.h"
#include "ChrSheetSheet.h"


// CChrSheetSkillA ダイアログ

IMPLEMENT_DYNAMIC(CChrSheetSkillA, CPropertyPage)
CChrSheetSkillA::CChrSheetSkillA()
	: CPropertyPage(CChrSheetSkillA::IDD)
{
}

CChrSheetSkillA::~CChrSheetSkillA()
{
}

void CChrSheetSkillA::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChrSheetSkillA, CPropertyPage)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_CLASS, OnBnClickedChrSheetSkillAClass)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_PREV, OnBnClickedChrSheetSkillAPrev)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_NEXT, OnBnClickedChrSheetSkillANext)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_0, OnBnClickedChrSheetSkillAKind0)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_1, OnBnClickedChrSheetSkillAKind1)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_2, OnBnClickedChrSheetSkillAKind2)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_3, OnBnClickedChrSheetSkillAKind3)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_4, OnBnClickedChrSheetSkillAKind4)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_5, OnBnClickedChrSheetSkillAKind5)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_6, OnBnClickedChrSheetSkillAKind6)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_7, OnBnClickedChrSheetSkillAKind7)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_8, OnBnClickedChrSheetSkillAKind8)
	ON_BN_CLICKED(IDC_CHR_SHEET_SKILL_A_KIND_9, OnBnClickedChrSheetSkillAKind9)
END_MESSAGE_MAP()


// CChrSheetSkillA メッセージ ハンドラ

BOOL CChrSheetSkillA::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO :  ここに初期化を追加してください

	CStatic *label;

	// 名前

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_NAME );
	label->SetWindowText( m_StrName );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_PREV );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_PREV_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_PREV_PAGE );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_NEXT );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_NEXT_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_NEXT_PAGE );

	// クラス

	CButton *btn = (CButton *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_CLASS );
	btn->SetWindowText( m_StrClass );

	// 能力値タイトル

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_LEV_TTL );
	label->SetWindowText( MSG_MBR_DATA_LEV_TTL );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_EXP_TTL );
	label->SetWindowText( MSG_MBR_DATA_EXP_TTL );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_NEED_EXP_TTL );
	label->SetWindowText( MSG_MBR_DATA_NEED_EXP_TTL );

	// 能力値

	for( long i = 0; i < SKILL_PER_PAGE_MAX_N; i++ ){
		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_KIND_0 + i );
		label->SetWindowText( m_StrKind[i] );

		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_LEV_0 + i );
		label->SetWindowText( m_StrLev[i] );

		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_EXP_0 + i );
		label->SetWindowText( m_StrExp[i] );

		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_NEED_EXP_0 + i );
		label->SetWindowText( m_StrNeedExp[i] );
	}

	// ヒント

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( "" );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAClass()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	if( gGuiChrSheet.classClicked() ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAPrev()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	gGuiChrSheet.prevChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillANext()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	gGuiChrSheet.nextChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind0()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 0] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind1()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 1] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind2()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 2] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind3()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 3] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind4()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 4] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind5()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 5] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind6()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 6] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind7()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 7] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind8()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 8] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}

void CChrSheetSkillA::OnBnClickedChrSheetSkillAKind9()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	if( m_pClassTab == NULL )
		return;

	const char *hint = get_skill_hint( m_pClassTab->skill[m_nSkillHead + 9] );
	CStatic *label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_SKILL_A_HINT );
	label->SetWindowText( hint );
}
