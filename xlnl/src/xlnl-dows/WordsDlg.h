#pragma once
#include "afxwin.h"


// CWordsDlg ダイアログ

class CWordsDlg : public CDialog
{
	DECLARE_DYNAMIC(CWordsDlg)

public:
	CWordsDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CWordsDlg();

// ダイアログ データ
	enum { IDD = IDD_WORDS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString m_EditDdx;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
