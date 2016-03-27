#pragma once


// CChrSheetStat ダイアログ

class CChrSheetStat : public CPropertyPage
{
	DECLARE_DYNAMIC(CChrSheetStat)

public:
	CString m_StrName;

	CString m_StrNameEdit;
	CString m_StrFace;
	CString m_StrRace;
	CString m_StrRaceName;
	CString m_StrSex;

	CString m_StrHp[2];
	CString m_StrMp[2];

	CString m_StrHit[2];
	CString m_StrWpnCrtcl[2];
	CString m_StrDam[2];
	CString m_StrDef[2];
	CString m_StrArmorCrtcl[2];
	CString m_StrAc[2];

	CString m_StrGold;
	CString m_StrCalender;

	CString m_StrStat[STAT_MAX_N];

	CString m_StrLight;
	CString m_StrGraphFile;

public:
	CChrSheetStat();
	virtual ~CChrSheetStat();

// ダイアログ データ
	enum { IDD = IDD_CHR_SHEET_STAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChrSheetStatRace();
	afx_msg void OnBnClickedChrSheetStatSex();
	afx_msg void OnEnChangeChrSheetStatNameEdit();
	afx_msg void OnEnChangeChrSheetStatFace();
	afx_msg void OnEnChangeChrSheetStatRaceName();
	afx_msg void OnBnClickedChrSheetStatPrev();
	afx_msg void OnBnClickedChrSheetStatNext();
	afx_msg void OnBnClickedChrSheetStatGraphFile();
};
