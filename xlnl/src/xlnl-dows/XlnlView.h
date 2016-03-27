// XlnlView.h : CXlnlView ���饹�Υ��󥿡��ե�����
//


#pragma once


// CXlnlView ������ɥ�

class CXlnlView : public CWnd
{
// ���󥹥ȥ饯�����
public:
	CXlnlView();

// °��
public:

// ���
public:
	// bowkenken BEGIN
	HWND GetWnd()
	{
		return this->m_hWnd;
	}

	void ResetScroll();
	void getScrollInfo( SCROLLINFO *info, int sb );
	void getScrollInfoPos( int sb, int pos );
	// bowkenken END

// �����С��饤��
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CXlnlView();

	// �������줿����å�����������ƴؿ�
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcMButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
};

