#pragma once
#include "afxwin.h"


// CChrSheetEquip ダイアログ

class CChrSheetEquip : public CPropertyPage
{
	DECLARE_DYNAMIC(CChrSheetEquip)

public:
	CString m_StrName;
	CString m_StrEquip[EQUIP_KIND_MAX_N];

public:
	CChrSheetEquip();
	virtual ~CChrSheetEquip();

public:
	void ClickedChrSheetEquipN( long n );

// ダイアログ データ
	enum { IDD = IDD_CHR_SHEET_EQUIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChrSheetEquip0();
	CButton m_Equip_0;
	CButton m_Equip_1;
	CButton m_Equip_2;
	CButton m_Equip_3;
	CButton m_Equip_4;
	CButton m_Equip_5;
	CButton m_Equip_6;
	CButton m_Equip_7;
	CButton m_Equip_8;
	CButton m_Equip_9;
	CButton m_Equip_10;
	CButton m_Equip_11;
	CButton m_Equip_12;

	afx_msg void OnBnClickedChrSheetEquip1();
	afx_msg void OnBnClickedChrSheetEquip2();
	afx_msg void OnBnClickedChrSheetEquip3();
	afx_msg void OnBnClickedChrSheetEquip4();
	afx_msg void OnBnClickedChrSheetEquip5();
	afx_msg void OnBnClickedChrSheetEquip6();
	afx_msg void OnBnClickedChrSheetEquip7();
	afx_msg void OnBnClickedChrSheetEquip8();
	afx_msg void OnBnClickedChrSheetEquip9();
	afx_msg void OnBnClickedChrSheetEquip10();
	afx_msg void OnBnClickedChrSheetEquip11();
	afx_msg void OnBnClickedChrSheetEquip12();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChrSheetEquipPrev();
	afx_msg void OnBnClickedChrSheetEquipNext();
};
