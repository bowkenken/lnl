#pragma once

#include "stdafx.h"

// CStatWnd フレーム 

class CStatWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CStatWnd)

	//bowkenken BEGIN
public:
	CButton m_BtnName[MBR_MAX_N];
	CStatic m_LabelAct[MBR_MAX_N];
	CButton m_BtnStat[MBR_MAX_N];
	CStatic m_LabelHp[MBR_MAX_N];
	CStatic m_LabelMp[MBR_MAX_N];
	CStatic m_LabelDunLev;
	CStatic m_LabelTime;
	//bowkenken END

	//bowkenken BEGIN
protected:
	CRect m_RectAdj;
	bool mFlagAdj;
	//bowkenken END

	//bowkenken BEGIN
public:
	void ReSize();
	CRect ReSizeMbr( long mbr_n, CPoint pos );
	void AdjustWnd();
	//bowkenken END

protected:
//bowkenken BEGIN
public:
//bowkenken END
	CStatWnd();           // 動的生成で使用される protected コンストラクタ
	virtual ~CStatWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


