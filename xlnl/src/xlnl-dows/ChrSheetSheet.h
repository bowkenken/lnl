#pragma once
#include "chrsheetstat.h"
#include "chrsheetabl.h"
#include "chrsheetskilla.h"
#include "chrsheetitem.h"
#include "chrsheetequip.h"



// CChrSheetSheet

class CChrSheetSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CChrSheetSheet)

public:
	CPropertyPage *m_Page;
	bool m_FlagContinue;

public:
	CChrSheetSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CChrSheetSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CChrSheetSheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CChrSheetStat m_Stat;
	CChrSheetAbl m_Abl;
	CChrSheetSkillA m_SkillA;
	CChrSheetSkillA m_SkillB;
	CChrSheetItem m_Item;
	CChrSheetEquip m_Equip;
	void AddPageTab(void);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
};


