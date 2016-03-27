#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define NUM_BTN_MAX	(1 + 10 + 3)
#define SLDR_FIGURE	2

// CInputNumDlg ダイアログ

class CInputNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputNumDlg)

	// bowkenken BEGIN
protected:
	bool m_FlagInit;
	// bowkenken END

	// bowkenken BEGIN
public:
	long m_Min, m_Max, m_Org;
	volatile long *m_Cur;

	CButton m_Clr[NUM_BTN_MAX];
	CButton m_Inc[NUM_BTN_MAX];
	CButton m_Dec[NUM_BTN_MAX];
	// bowkenken END

public:
	CInputNumDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CInputNumDlg();

// ダイアログ データ
	enum { IDD = IDD_INPUT_NUM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// bowkenken BEGIN
	void SetSldrPos( long n );
	// bowkenken END

protected:
	// bowkenken BEGIN
	void OnBtnClickRange( UINT id );
	// bowkenken END
	virtual void OnOK();
	virtual void OnCancel();
public:
	CEdit m_Edit;
	CSpinButtonCtrl m_Spn;
	CSliderCtrl m_Sldr;
	afx_msg void OnBnClickedNumBtnMin();
	afx_msg void OnBnClickedNumBtnClr();
	afx_msg void OnBnClickedNumBtnMax();
	afx_msg void OnEnChangeNumEdit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClose();
};
