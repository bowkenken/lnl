// ChrSheetAbl.cpp : �����ե�����
//

#include "stdafx.h"
#include "../misc.h"
#include "../draw.h"
#include "../menu.h"
#include "../misc-prot.h"
#include "../imenu-prot.h"
#include "xlnl-dows.h"
#include "ChrSheetAbl.h"
#include ".\chrsheetabl.h"
#include "../GlobalVar.h"
#include "ChrSheetSheet.h"


// CChrSheetAbl ��������

IMPLEMENT_DYNAMIC(CChrSheetAbl, CPropertyPage)
CChrSheetAbl::CChrSheetAbl()
	: CPropertyPage(CChrSheetAbl::IDD)
{
}

CChrSheetAbl::~CChrSheetAbl()
{
}

void CChrSheetAbl::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChrSheetAbl, CPropertyPage)
	ON_BN_CLICKED(IDC_CHR_SHEET_ABL_CLASS, OnBnClickedChrSheetAblClass)
	ON_BN_CLICKED(IDC_CHR_SHEET_ABL_PREV, OnBnClickedChrSheetAblPrev)
	ON_BN_CLICKED(IDC_CHR_SHEET_ABL_NEXT, OnBnClickedChrSheetAblNext)
END_MESSAGE_MAP()


// CChrSheetAbl ��å����� �ϥ�ɥ�

BOOL CChrSheetAbl::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO :  �����˽�������ɲä��Ƥ�������

	CStatic *label;

	// ̾��

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_NAME );
	label->SetWindowText( m_StrName );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_PREV );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_PREV_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_PREV_PAGE );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_NEXT );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_NEXT_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_NEXT_PAGE );

	// ���饹

	CButton *btn = (CButton *)GetDlgItem( IDC_CHR_SHEET_ABL_CLASS );
	btn->SetWindowText( m_StrClass );

	// ǽ���ͥ����ȥ�

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_LEV_TTL_1 );
	label->SetWindowText( MSG_MBR_DATA_LEV_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_LEV_TTL_2 );
	label->SetWindowText( MSG_MBR_DATA_LEV_TTL );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_EXP_TTL_1 );
	label->SetWindowText( MSG_MBR_DATA_EXP_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_EXP_TTL_2 );
	label->SetWindowText( MSG_MBR_DATA_EXP_TTL );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_NEED_EXP_TTL_1 );
	label->SetWindowText( MSG_MBR_DATA_NEED_EXP_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_NEED_EXP_TTL_2 );
	label->SetWindowText( MSG_MBR_DATA_NEED_EXP_TTL );

	// ǽ����

	for( long i = 0; i < ABL_KIND_MAX_N; i++ ){
		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_LEV_0 + i );
		label->SetWindowText( m_StrLev[i] );

		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_ADD_LEV_0 + i );
		label->SetWindowText( m_StrAddLev[i] );

		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_EXP_0 + i );
		label->SetWindowText( m_StrExp[i] );

		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_NEED_EXP_0 + i );
		label->SetWindowText( m_StrNeedExp[i] );
	}

	// �����ͥ����ȥ�

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI );
	label->SetWindowText( MSG_MBR_DATA_RESI_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_LAWFUL );
	label->SetWindowText( MSG_MBR_DATA_RESI_TTL_LAWFUL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_NEUTRAL_1 );
	label->SetWindowText( MSG_MBR_DATA_RESI_TTL_NEUTRAL_1 );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_CHAOTIC );
	label->SetWindowText( MSG_MBR_DATA_RESI_TTL_CHAOTIC );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_GOOD );
	label->SetWindowText( MSG_MBR_DATA_RESI_TTL_GOOD );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_NEUTRAL_2 );
	label->SetWindowText( MSG_MBR_DATA_RESI_TTL_NEUTRAL_2 );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_EVIL );
	label->SetWindowText( MSG_MBR_DATA_RESI_TTL_EVIL );

	// ������

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_KNOC );
	label->SetWindowText( m_StrResi[RESI_KIND_KNOC] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_SLAS );
	label->SetWindowText( m_StrResi[RESI_KIND_SLAS] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_STIN );
	label->SetWindowText( m_StrResi[RESI_KIND_STIN] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_HEAT );
	label->SetWindowText( m_StrResi[RESI_KIND_HEAT] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_COLD );
	label->SetWindowText( m_StrResi[RESI_KIND_COLD] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_MIND );
	label->SetWindowText( m_StrResi[RESI_KIND_MIND] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_ACID );
	label->SetWindowText( m_StrResi[RESI_KIND_ACID] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_ELEC );
	label->SetWindowText( m_StrResi[RESI_KIND_ELEC] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ABL_RESI_POIS );
	label->SetWindowText( m_StrResi[RESI_KIND_POIS] );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �㳰 : OCX �ץ�ѥƥ� �ڡ�����ɬ�� FALSE ���֤��ޤ���
}

void CChrSheetAbl::OnBnClickedChrSheetAblClass()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	if( gGuiChrSheet.classClicked() ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}

void CChrSheetAbl::OnBnClickedChrSheetAblPrev()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	gGuiChrSheet.prevChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}

void CChrSheetAbl::OnBnClickedChrSheetAblNext()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	gGuiChrSheet.nextChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}
