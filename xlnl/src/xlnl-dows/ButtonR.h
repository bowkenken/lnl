#pragma once


// CButtonR

class CButtonR : public CButton
{
	DECLARE_DYNAMIC(CButtonR)

// bowkenken BEGIN
protected:
	int m_nID;
// bowkenken END

public:
	CButtonR();
	virtual ~CButtonR();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnBnClicked();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
};


