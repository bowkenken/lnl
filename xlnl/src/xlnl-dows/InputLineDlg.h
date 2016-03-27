#pragma once
#include "afxwin.h"


// CInputLineDlg ダイアログ

class CInputLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputLineDlg)

public:
	CInputLineDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CInputLineDlg();

// ダイアログ データ
	enum { IDD = IDD_INPUT_LINE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit;
	CString m_EditDdx;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
