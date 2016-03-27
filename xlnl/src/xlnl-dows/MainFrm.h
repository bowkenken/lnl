// MainFrm.h : CMainFrame ���饹�Υ��󥿡��ե�����
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

// °��
public:
// bowkenken BEGIN
	UINT uMs;
	UINT nPressTimer;
// bowkenken END

// bowkenken BEGIN
protected: 
	long m_TimerNestFlag;
// bowkenken END

// ���
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

// �����С��饤��
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// ����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ����ȥ��� �С��ѥ���
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CXlnlView    m_wndView;

// �������줿����å�����������ƴؿ�
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
