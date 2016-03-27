#pragma once
#include "afxwin.h"


// CSelConfDlg ダイアログ

class CSelConfDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelConfDlg)

public:
	CSelConfDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSelConfDlg();

// ダイアログ データ
	enum { IDD = IDD_SEL_CONF_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_stTitle;
	CListBox m_List;
	CString m_ListDdx;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeSelConfList();
	afx_msg void OnLbnDblclkSelConfList();
	afx_msg void OnBnClickedOk();
};
