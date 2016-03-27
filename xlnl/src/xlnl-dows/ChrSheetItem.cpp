// ChrSheetItem.cpp : �����ե�����
//

#include "stdafx.h"
#include "../misc.h"
#include "../draw.h"
#include "../menu.h"
#include "../misc-prot.h"
#include "../imenu-prot.h"
#include "xlnl-dows.h"
#include "ChrSheetItem.h"
#include ".\chrsheetitem.h"
#include "../GlobalVar.h"
#include "ChrSheetSheet.h"


// CChrSheetItem ��������

IMPLEMENT_DYNAMIC(CChrSheetItem, CPropertyPage)
CChrSheetItem::CChrSheetItem()
	: CPropertyPage(CChrSheetItem::IDD)
{
}

CChrSheetItem::~CChrSheetItem()
{
}

void CChrSheetItem::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_0, m_Item_0);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_1, m_Item_1);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_2, m_Item_2);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_3, m_Item_3);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_4, m_Item_4);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_5, m_Item_5);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_6, m_Item_6);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_7, m_Item_7);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_8, m_Item_8);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_9, m_Item_9);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_10, m_Item_10);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_11, m_Item_11);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_12, m_Item_12);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_13, m_Item_13);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_14, m_Item_14);
	DDX_Control(pDX, IDC_CHR_SHEET_ITEM_15, m_Item_15);
}


BEGIN_MESSAGE_MAP(CChrSheetItem, CPropertyPage)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_0, OnBnClickedChrSheetItem0)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_1, OnBnClickedChrSheetItem1)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_2, OnBnClickedChrSheetItem2)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_3, OnBnClickedChrSheetItem3)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_4, OnBnClickedChrSheetItem4)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_5, OnBnClickedChrSheetItem5)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_6, OnBnClickedChrSheetItem6)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_7, OnBnClickedChrSheetItem7)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_8, OnBnClickedChrSheetItem8)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_9, OnBnClickedChrSheetItem9)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_10, OnBnClickedChrSheetItem10)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_11, OnBnClickedChrSheetItem11)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_12, OnBnClickedChrSheetItem12)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_13, OnBnClickedChrSheetItem13)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_14, OnBnClickedChrSheetItem14)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_15, OnBnClickedChrSheetItem15)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_PREV, OnBnClickedChrSheetItemPrev)
	ON_BN_CLICKED(IDC_CHR_SHEET_ITEM_NEXT, OnBnClickedChrSheetItemNext)
END_MESSAGE_MAP()


// CChrSheetItem ��å����� �ϥ�ɥ�

BOOL CChrSheetItem::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO :  �����˽�������ɲä��Ƥ�������

	CStatic *label;

	// ̾��

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ITEM_NAME );
	label->SetWindowText( m_StrName );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ITEM_PREV );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_PREV_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_PREV_PAGE );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_ITEM_NEXT );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_NEXT_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_NEXT_PAGE );

	// �����ƥ�

	m_Item_0.SetWindowText( m_StrItem[0] );
	m_Item_1.SetWindowText( m_StrItem[1] );
	m_Item_2.SetWindowText( m_StrItem[2] );
	m_Item_3.SetWindowText( m_StrItem[3] );
	m_Item_4.SetWindowText( m_StrItem[4] );
	m_Item_5.SetWindowText( m_StrItem[5] );
	m_Item_6.SetWindowText( m_StrItem[6] );
	m_Item_7.SetWindowText( m_StrItem[7] );
	m_Item_8.SetWindowText( m_StrItem[8] );
	m_Item_9.SetWindowText( m_StrItem[9] );
	m_Item_10.SetWindowText( m_StrItem[10] );
	m_Item_11.SetWindowText( m_StrItem[11] );
	m_Item_12.SetWindowText( m_StrItem[12] );
	m_Item_13.SetWindowText( m_StrItem[13] );
	m_Item_14.SetWindowText( m_StrItem[14] );
	m_Item_15.SetWindowText( m_StrItem[15] );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �㳰 : OCX �ץ�ѥƥ� �ڡ�����ɬ�� FALSE ���֤��ޤ���
}

void CChrSheetItem::ClickedChrSheetItemN( long n )
{
	if( gGuiChrSheet.itemClicked( n ) ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}

void CChrSheetItem::OnBnClickedChrSheetItem0()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 0 );
}

void CChrSheetItem::OnBnClickedChrSheetItem1()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 1 );
}

void CChrSheetItem::OnBnClickedChrSheetItem2()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 2 );
}

void CChrSheetItem::OnBnClickedChrSheetItem3()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 3 );
}

void CChrSheetItem::OnBnClickedChrSheetItem4()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 4 );
}

void CChrSheetItem::OnBnClickedChrSheetItem5()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 5 );
}

void CChrSheetItem::OnBnClickedChrSheetItem6()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 6 );
}

void CChrSheetItem::OnBnClickedChrSheetItem7()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 7 );
}

void CChrSheetItem::OnBnClickedChrSheetItem8()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 8 );
}

void CChrSheetItem::OnBnClickedChrSheetItem9()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 9 );
}

void CChrSheetItem::OnBnClickedChrSheetItem10()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 10 );
}

void CChrSheetItem::OnBnClickedChrSheetItem11()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 11 );
}

void CChrSheetItem::OnBnClickedChrSheetItem12()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 12 );
}

void CChrSheetItem::OnBnClickedChrSheetItem13()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 13 );
}

void CChrSheetItem::OnBnClickedChrSheetItem14()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 14 );
}

void CChrSheetItem::OnBnClickedChrSheetItem15()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	ClickedChrSheetItemN( 15 );
}

void CChrSheetItem::OnBnClickedChrSheetItemPrev()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	gGuiChrSheet.prevChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}

void CChrSheetItem::OnBnClickedChrSheetItemNext()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	gGuiChrSheet.nextChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}
