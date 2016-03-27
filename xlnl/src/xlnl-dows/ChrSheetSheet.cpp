// ChrSheetSheet.cpp : 実装ファイル
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "ChrSheetSheet.h"
#include ".\chrsheetsheet.h"


// CChrSheetSheet

IMPLEMENT_DYNAMIC(CChrSheetSheet, CPropertySheet)
CChrSheetSheet::CChrSheetSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPageTab();
}

CChrSheetSheet::CChrSheetSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPageTab();
}

CChrSheetSheet::~CChrSheetSheet()
{
}


BEGIN_MESSAGE_MAP(CChrSheetSheet, CPropertySheet)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CChrSheetSheet メッセージ ハンドラ

void CChrSheetSheet::AddPageTab(void)
{
	m_Page = NULL;

	AddPage( &m_Stat );
	AddPage( &m_Abl );
	AddPage( &m_SkillA );
	AddPage( &m_SkillB );
	AddPage( &m_Item );
	AddPage( &m_Equip );
}

BOOL CChrSheetSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO :  ここに特定なコードを追加してください。

	char *ttl[6] = {
		MSG_STAT,
		MSG_ABL,
		MSG_SKILL_A,
		MSG_SKILL_B,
		MSG_ITEM,
		MSG_EQUIP,
	};
	CTabCtrl *pTab = GetTabControl();
	TC_ITEM tabItem;
	for( long i = 0; i < 6; i++ ){
		tabItem.mask = TCIF_TEXT;
		tabItem.pszText = ttl[i];
		pTab->SetItem( i, &tabItem );
	}

	if( m_Page != NULL )
		SetActivePage( m_Page );

	return bResult;
}

void CChrSheetSheet::OnClose()
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	m_Page = GetActivePage();

	CPropertySheet::OnClose();
}
