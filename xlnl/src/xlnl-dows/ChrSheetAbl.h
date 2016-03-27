#pragma once


// CChrSheetAbl ダイアログ

class CChrSheetAbl : public CPropertyPage
{
	DECLARE_DYNAMIC(CChrSheetAbl)

public:
	CString m_StrName;

	CString m_StrClass;

	CString m_StrLev[ABL_KIND_MAX_N];
	CString m_StrAddLev[ABL_KIND_MAX_N];
	CString m_StrExp[ABL_KIND_MAX_N];
	CString m_StrNeedExp[ABL_KIND_MAX_N];

	CString m_StrResi[RESI_KIND_MAX_N];

public:
	CChrSheetAbl();
	virtual ~CChrSheetAbl();

// ダイアログ データ
	enum { IDD = IDD_CHR_SHEET_ABL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChrSheetAblClass();
	afx_msg void OnBnClickedChrSheetAblPrev();
	afx_msg void OnBnClickedChrSheetAblNext();
};
