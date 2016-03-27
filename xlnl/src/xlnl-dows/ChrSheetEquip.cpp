// ChrSheetEquip.cpp : 実装ファイル
//

#include "stdafx.h"
#include "../misc.h"
#include "../draw.h"
#include "../menu.h"
#include "../misc-prot.h"
#include "../imenu-prot.h"
#include "xlnl-dows.h"
#include "ChrSheetEquip.h"
#include ".\chrsheetequip.h"
#include "../GlobalVar.h"
#include "ChrSheetSheet.h"


// CChrSheetEquip ダイアログ

IMPLEMENT_DYNAMIC(CChrSheetEquip, CPropertyPage)
CChrSheetEquip::CChrSheetEquip()
	: CPropertyPage(CChrSheetEquip::IDD)
{
}

CChrSheetEquip::~CChrSheetEquip()
{
}

void CChrSheetEquip::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_0, m_Equip_0);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_1, m_Equip_1);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_2, m_Equip_2);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_3, m_Equip_3);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_4, m_Equip_4);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_5, m_Equip_5);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_6, m_Equip_6);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_7, m_Equip_7);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_8, m_Equip_8);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_9, m_Equip_9);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_10, m_Equip_10);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_11, m_Equip_11);
	DDX_Control(pDX, IDC_CHR_SHEET_EQUIP_12, m_Equip_12);
}


BEGIN_MESSAGE_MAP(CChrSheetEquip, CPropertyPage)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_0, OnBnClickedChrSheetEquip0)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_1, OnBnClickedChrSheetEquip1)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_2, OnBnClickedChrSheetEquip2)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_3, OnBnClickedChrSheetEquip3)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_4, OnBnClickedChrSheetEquip4)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_5, OnBnClickedChrSheetEquip5)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_6, OnBnClickedChrSheetEquip6)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_7, OnBnClickedChrSheetEquip7)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_8, OnBnClickedChrSheetEquip8)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_9, OnBnClickedChrSheetEquip9)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_10, OnBnClickedChrSheetEquip10)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_11, OnBnClickedChrSheetEquip11)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_12, OnBnClickedChrSheetEquip12)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_PREV, OnBnClickedChrSheetEquipPrev)
	ON_BN_CLICKED(IDC_CHR_SHEET_EQUIP_NEXT, OnBnClickedChrSheetEquipNext)
END_MESSAGE_MAP()


// CChrSheetEquip メッセージ ハンドラ

BOOL CChrSheetEquip::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO :  ここに初期化を追加してください

	CStatic *label;

	// 名前

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_EQUIP_NAME );
	label->SetWindowText( m_StrName );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_EQUIP_PREV );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_PREV_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_PREV_PAGE );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_EQUIP_NEXT );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_NEXT_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_NEXT_PAGE );

	// 装備

	m_Equip_0.SetWindowText( m_StrEquip[0] );
	m_Equip_1.SetWindowText( m_StrEquip[1] );
	m_Equip_2.SetWindowText( m_StrEquip[2] );
	m_Equip_3.SetWindowText( m_StrEquip[3] );
	m_Equip_4.SetWindowText( m_StrEquip[4] );
	m_Equip_5.SetWindowText( m_StrEquip[5] );
	m_Equip_6.SetWindowText( m_StrEquip[6] );
	m_Equip_7.SetWindowText( m_StrEquip[7] );
	m_Equip_8.SetWindowText( m_StrEquip[8] );
	m_Equip_9.SetWindowText( m_StrEquip[9] );
	m_Equip_10.SetWindowText( m_StrEquip[10] );
	m_Equip_11.SetWindowText( m_StrEquip[11] );
	m_Equip_12.SetWindowText( m_StrEquip[12] );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CChrSheetEquip::ClickedChrSheetEquipN( long n )
{
	if( gGuiChrSheet.equipClicked( n ) ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}

void CChrSheetEquip::OnBnClickedChrSheetEquip0()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 0 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip1()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 1 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip2()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 2 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip3()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 3 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip4()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 4 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip5()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 5 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip6()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 6 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip7()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 7 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip8()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 8 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip9()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 9 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip10()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 10 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip11()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 11 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquip12()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	ClickedChrSheetEquipN( 12 );
}

void CChrSheetEquip::OnBnClickedChrSheetEquipPrev()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	gGuiChrSheet.prevChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}

void CChrSheetEquip::OnBnClickedChrSheetEquipNext()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	gGuiChrSheet.nextChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}
