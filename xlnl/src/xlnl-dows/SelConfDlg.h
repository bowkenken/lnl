#pragma once
#include "afxwin.h"


// CSelConfDlg ��������

class CSelConfDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelConfDlg)

public:
	CSelConfDlg(CWnd* pParent = NULL);   // ɸ�ॳ�󥹥ȥ饯��
	virtual ~CSelConfDlg();

// �������� �ǡ���
	enum { IDD = IDD_SEL_CONF_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ���ݡ���

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
