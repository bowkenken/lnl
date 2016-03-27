// MainFrm.h : CMainFrame クラスのインターフェイス
//


#pragma once

// bowkenken BEGIN
#define WM_USER_TIMER (WM_USER + 100)
// bowkenken END

#include "XlnlView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 属性
public:
// bowkenken BEGIN
	UINT uMs;
	UINT nPressTimer;
// bowkenken END

// bowkenken BEGIN
protected: 
	long m_TimerNestFlag;
// bowkenken END

// 操作
public:
	// bowkenken BEGIN
	HWND GetViewWnd()
	{
		return m_wndView.GetWnd();
	}
	CXlnlView *GetView()
	{
		return &m_wndView;
	}

	void OnUserTimerDir3d();
	void OnUserTimerMouseMap();

	void SetTimer();
	void StartTimer();
	void StopTimer();

	CStatusBar &GetStatusBar();

	void KeyCancel();
	void KeyOk();
	// bowkenken END

// オーバーライド
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 実装
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // コントロール バー用メンバ
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CXlnlView    m_wndView;

// 生成された、メッセージ割り当て関数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	// bowkenken BEGIN
	afx_msg LRESULT OnUserTimer(
		WPARAM wParam, LPARAM lParam );
	// bowkenken END
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
protected:
	// bowkenken BEGIN
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	// bowkenken END
public:
	afx_msg void OnCmdKeyExec();
	afx_msg void OnCmdKeyExecCont();
	afx_msg void OnUpdateCmdKeyExecCont(CCmdUI *pCmdUI);
	afx_msg void OnCmdKeyZ();
	afx_msg void OnCmdKeyX();
	afx_msg void OnCmdKeyC();
	afx_msg void OnCmdKeyV();
	afx_msg void OnCmdKeyCancel();
	afx_msg void OnCmdKeyOk();
};
