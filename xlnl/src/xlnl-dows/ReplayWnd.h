#pragma once


// CReplayWnd フレーム 

class CReplayWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CReplayWnd)
protected:
	//bowkenken BEGIN
public:
	//bowkenken END
	CReplayWnd();           // 動的生成で使用される protected コンストラクタ
	virtual ~CReplayWnd();

	//bowkenken BEGIN
protected:
	static const long nBtnWidth = 180;
	static const long nBtnHeight = 30;

public:
	CEdit m_TextReplay;
	CButton m_BtnTurn, m_BtnKey1, m_BtnKey10, m_BtnCont, m_BtnExit;
	//bowkenken END

protected:
	DECLARE_MESSAGE_MAP()
	// bowkenken BEGIN
	afx_msg void OnButtonTurn();
	afx_msg void OnButtonKey1();
	afx_msg void OnButtonKey10();
	afx_msg void OnButtonCont();
	afx_msg void OnButtonExit();
	// bowkenken END
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
};


