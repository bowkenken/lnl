#pragma once
#include "../skill.h"
#include "../skill-prot.h"


// CChrSheetSkillA ダイアログ

class CChrSheetSkillA : public CPropertyPage
{
	DECLARE_DYNAMIC(CChrSheetSkillA)

public:
	CString m_StrName;
	CString m_StrClass;

	class_t *m_pClassTab;
	long m_nSkillHead;
	CString m_StrKind[SKILL_PER_PAGE_MAX_N];
	CString m_StrLev[SKILL_PER_PAGE_MAX_N];
	CString m_StrAddLev[SKILL_PER_PAGE_MAX_N];
	CString m_StrExp[SKILL_PER_PAGE_MAX_N];
	CString m_StrNeedExp[SKILL_PER_PAGE_MAX_N];

public:
	CChrSheetSkillA();
	virtual ~CChrSheetSkillA();

// ダイアログ データ
	enum { IDD = IDD_CHR_SHEET_SKILL_A };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChrSheetSkillAClass();
	afx_msg void OnBnClickedChrSheetSkillAPrev();
	afx_msg void OnBnClickedChrSheetSkillANext();
	afx_msg void OnBnClickedChrSheetSkillAKind0();
	afx_msg void OnBnClickedChrSheetSkillAKind1();
	afx_msg void OnBnClickedChrSheetSkillAKind2();
	afx_msg void OnBnClickedChrSheetSkillAKind3();
	afx_msg void OnBnClickedChrSheetSkillAKind4();
	afx_msg void OnBnClickedChrSheetSkillAKind5();
	afx_msg void OnBnClickedChrSheetSkillAKind6();
	afx_msg void OnBnClickedChrSheetSkillAKind7();
	afx_msg void OnBnClickedChrSheetSkillAKind8();
	afx_msg void OnBnClickedChrSheetSkillAKind9();
};
