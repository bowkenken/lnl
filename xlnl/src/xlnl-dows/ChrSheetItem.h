#pragma once
#include "afxwin.h"


// CChrSheetItem ダイアログ

class CChrSheetItem : public CPropertyPage
{
	DECLARE_DYNAMIC(CChrSheetItem)

public:
	CString m_StrName;
	CString m_StrItem[MBR_ITEM_MAX_N];

public:
	CChrSheetItem();
	virtual ~CChrSheetItem();

public:
	void ClickedChrSheetItemN( long n );

// ダイアログ データ
	enum { IDD = IDD_CHR_SHEET_ITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CButton m_Item_0;
	CButton m_Item_1;
	CButton m_Item_2;
	CButton m_Item_3;
	CButton m_Item_4;
	CButton m_Item_5;
	CButton m_Item_6;
	CButton m_Item_7;
	CButton m_Item_8;
	CButton m_Item_9;
	CButton m_Item_10;
	CButton m_Item_11;
	CButton m_Item_12;
	CButton m_Item_13;
	CButton m_Item_14;
	CButton m_Item_15;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChrSheetItem0();
	afx_msg void OnBnClickedChrSheetItem1();
	afx_msg void OnBnClickedChrSheetItem2();
	afx_msg void OnBnClickedChrSheetItem3();
	afx_msg void OnBnClickedChrSheetItem4();
	afx_msg void OnBnClickedChrSheetItem5();
	afx_msg void OnBnClickedChrSheetItem6();
	afx_msg void OnBnClickedChrSheetItem7();
	afx_msg void OnBnClickedChrSheetItem8();
	afx_msg void OnBnClickedChrSheetItem9();
	afx_msg void OnBnClickedChrSheetItem10();
	afx_msg void OnBnClickedChrSheetItem11();
	afx_msg void OnBnClickedChrSheetItem12();
	afx_msg void OnBnClickedChrSheetItem13();
	afx_msg void OnBnClickedChrSheetItem14();
	afx_msg void OnBnClickedChrSheetItem15();
	afx_msg void OnBnClickedChrSheetItemPrev();
	afx_msg void OnBnClickedChrSheetItemNext();
};
