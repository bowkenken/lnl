#pragma once


// CMessageView �ӥ塼

class CMessageView : public CView
{
	DECLARE_DYNCREATE(CMessageView)

protected:
// bowkenken BEGIN
public:
// bowkenken END
	CMessageView();           // ưŪ�����ǻ��Ѥ���� protected ���󥹥ȥ饯��
	virtual ~CMessageView();

public:
	virtual void OnDraw(CDC* pDC);      // ���Υӥ塼�����褹�뤿��˥����С��饤�ɤ���ޤ���
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


