#pragma once
#include "afxwin.h"


// CInputLineDlg ��������

class CInputLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputLineDlg)

public:
	CInputLineDlg(CWnd* pParent = NULL);   // ɸ�ॳ�󥹥ȥ饯��
	virtual ~CInputLineDlg();

// �������� �ǡ���
	enum { IDD = IDD_INPUT_LINE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ���ݡ���

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
