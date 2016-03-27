#pragma once

// bowkenken BEGIN
#include "../menu.h"
#include "ButtonR.h"
// bowkenken END

// CMenuWnd フレーム 

class CMenuWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMenuWnd)

	//bowkenken BEGIN
protected:
	static const long nBtnWidth = 60;
	static const long nBtnHeight = 30;

public:
	CEdit m_LblPage;
	CButtonR m_BtnPrevPage, m_BtnNextPage;
	CButtonR m_BtnCancel, m_BtnCancelAll;
	CButtonR m_aBtn[MENU_MAX_N_PER_PAGE + 1];
	//bowkenken END

protected:
	//bowkenken BEGIN
public:
	//bowkenken END
	CMenuWnd();           // 動的生成で使用される protected コンストラクタ
	virtual ~CMenuWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};
