#pragma once


// CSkillEditDlg ダイアログ

class CSkillEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CSkillEditDlg)

public:
	CSkillEditDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSkillEditDlg();

public:
	void SetClassName();

// ダイアログ データ
	enum { IDD = IDD_SKILL_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString mEditName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSkillEditSkill00();
	afx_msg void OnBnClickedSkillEditSkill01();
	afx_msg void OnBnClickedSkillEditSkill02();
	afx_msg void OnBnClickedSkillEditSkill03();
	afx_msg void OnBnClickedSkillEditSkill04();
	afx_msg void OnBnClickedSkillEditSkill05();
	afx_msg void OnBnClickedSkillEditSkill06();
	afx_msg void OnBnClickedSkillEditSkill07();
	afx_msg void OnBnClickedSkillEditSkill08();
	afx_msg void OnBnClickedSkillEditSkill09();
	afx_msg void OnBnClickedSkillEditSkill10();
	afx_msg void OnBnClickedSkillEditSkill11();
	afx_msg void OnBnClickedSkillEditSkill12();
	afx_msg void OnBnClickedSkillEditSkill13();
	afx_msg void OnBnClickedSkillEditSkill14();
	afx_msg void OnBnClickedSkillEditSkill15();
	afx_msg void OnBnClickedSkillEditSkill16();
	afx_msg void OnBnClickedSkillEditSkill17();
	afx_msg void OnBnClickedSkillEditSkill18();
	afx_msg void OnBnClickedSkillEditSkill19();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSkillEditPrev();
	afx_msg void OnBnClickedSkillEditNext();
};
