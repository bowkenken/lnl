#pragma once

// bowkenken BEGIN
#include "MessageView.h"
// bowkenken END

// CMessageWnd �ե졼�� 

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
	CMessageWnd();           // ưŪ�����ǻ��Ѥ���� protected ���󥹥ȥ饯��
	virtual ~CMessageWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


