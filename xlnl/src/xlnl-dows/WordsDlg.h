#pragma once
#include "afxwin.h"


// CWordsDlg ��������

class CWordsDlg : public CDialog
{
	DECLARE_DYNAMIC(CWordsDlg)

public:
	CWordsDlg(CWnd* pParent = NULL);   // ɸ�ॳ�󥹥ȥ饯��
	virtual ~CWordsDlg();

// �������� �ǡ���
	enum { IDD = IDD_WORDS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ���ݡ���

	DECLARE_MESSAGE_MAP()
public:
	CString m_EditDdx;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
