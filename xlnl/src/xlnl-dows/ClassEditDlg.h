#pragma once


// CClassEditDlg ダイアログ

class CClassEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CClassEditDlg)

public:
	CClassEditDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CClassEditDlg();

// ダイアログ データ
	enum { IDD = IDD_CLASS_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString mEditName;
	CString mLabelTotalValue;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedClassEditHpP();
	afx_msg void OnBnClickedClassEditMpP();
	afx_msg void OnBnClickedClassEditDexP();
	afx_msg void OnBnClickedClassEditStrP();
	afx_msg void OnBnClickedClassEditAgiP();
	afx_msg void OnBnClickedClassEditIntP();
	afx_msg void OnBnClickedClassEditWisP();
	afx_msg void OnBnClickedClassEditChaP();
	afx_msg void OnBnClickedClassEditFigP();
	afx_msg void OnBnClickedClassEditMonP();
	afx_msg void OnBnClickedClassEditHunP();
	afx_msg void OnBnClickedClassEditThiP();
	afx_msg void OnBnClickedClassEditMagP();
	afx_msg void OnBnClickedClassEditSorP();
	afx_msg void OnBnClickedClassEditEncP();
	afx_msg void OnBnClickedClassEditSumP();
	afx_msg void OnBnClickedClassEditPriP();
	afx_msg void OnBnClickedClassEditShaP();
	afx_msg void OnBnClickedClassEditBarP();
	afx_msg void OnBnClickedClassEditNinP();
	afx_msg void OnBnClickedClassEditHpM();
	afx_msg void OnBnClickedClassEditMpM();
	afx_msg void OnBnClickedClassEditDexM();
	afx_msg void OnBnClickedClassEditStrM();
	afx_msg void OnBnClickedClassEditAgiM();
	afx_msg void OnBnClickedClassEditIntM();
	afx_msg void OnBnClickedClassEditWisM();
	afx_msg void OnBnClickedClassEditChaM();
	afx_msg void OnBnClickedClassEditFigM();
	afx_msg void OnBnClickedClassEditMonM();
	afx_msg void OnBnClickedClassEditHunM();
	afx_msg void OnBnClickedClassEditThiM();
	afx_msg void OnBnClickedClassEditMagM();
	afx_msg void OnBnClickedClassEditSorM();
	afx_msg void OnBnClickedClassEditEncM();
	afx_msg void OnBnClickedClassEditSumM();
	afx_msg void OnBnClickedClassEditPriM();
	afx_msg void OnBnClickedClassEditShaM();
	afx_msg void OnBnClickedClassEditBarM();
	afx_msg void OnBnClickedClassEditNinM();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
