#pragma once

// bowkenken BEGIN
#include "MessageView.h"
// bowkenken END

// CMessageWnd フレーム 

class CMessageWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMessageWnd)

// bowkenken BEGIN
public:
	CMessageView m_wndView;
// bowkenken END

protected:
// bowkenken BEGIN
public:
// bowkenken END
	CMessageWnd();           // 動的生成で使用される protected コンストラクタ
	virtual ~CMessageWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


