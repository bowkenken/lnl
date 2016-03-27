// ButtonR.cpp : �����ե�����
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "ButtonR.h"
#include ".\buttonr.h"

// bowkenken BEGIN
#include "../Key.h"
#include "../GlobalVar.h"
// bowkenken END

// CButtonR

IMPLEMENT_DYNAMIC(CButtonR, CButton)
CButtonR::CButtonR()
{
	m_nID = 0;
}

CButtonR::~CButtonR()
{
}


BEGIN_MESSAGE_MAP(CButtonR, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnBnClicked)
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONUP()
END_MESSAGE_MAP()



// CButtonR ��å����� �ϥ�ɥ�


BOOL CButtonR::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO : ����������ʥ����ɤ��ɲä��뤫���⤷���ϴ��ܥ��饹��ƤӽФ��Ƥ���������

	// bowkenken BEGIN
	m_nID = nID;
	// bowkenken END

	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}

void CButtonR::OnBnClicked()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	// bowkenken BEGIN
	if( m_nID == IDC_MENU_WND_BTN_PREV_PAGE ){
		gKey.setString( "4" );

		return;
	}
	if( m_nID == IDC_MENU_WND_BTN_NEXT_PAGE ){
		gKey.setString( "6" );

		return;
	}
	if( m_nID == IDC_MENU_WND_BTN_CANCEL ){
		gKey.setString( "0" );

		return;
	}
	if( m_nID == IDC_MENU_WND_BTN_CANCEL_ALL ){
		gKey.setString( "/" );

		return;
	}
	if( (IDC_MENU_WND_BTN_BGN <= m_nID)
			&& (m_nID <= IDC_MENU_WND_BTN_END) ){
		long n = m_nID - IDC_MENU_WND_BTN_BGN;
		gKey.setChar( gGuiMenu.getAccelKey( n ) );

		return;
	}
	// bowkenken END
}

void CButtonR::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO : �����˥�å����� �ϥ�ɥ� �����ɤ��ɲä��뤫������ν�����ƤӽФ��ޤ���

	// bowkenken BEGIN
	if( m_nID == IDC_MENU_WND_BTN_PREV_PAGE ){
		gKey.setString( "6" );

		return;
	}
	if( m_nID == IDC_MENU_WND_BTN_NEXT_PAGE ){
		gKey.setString( "4" );

		return;
	}
	if( (IDC_MENU_WND_BTN_BGN <= m_nID)
			&& (m_nID <= IDC_MENU_WND_BTN_END) ){
		gKey.setString( "0" );

		return;
	}
	// bowkenken END

	CButton::OnRButtonUp(nFlags, point);
}

void CButtonR::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO : �����˥�å����� �ϥ�ɥ� �����ɤ��ɲä��뤫������ν�����ƤӽФ��ޤ���

	// bowkenken BEGIN
	if( (IDC_MENU_WND_BTN_BGN <= m_nID)
			&& (m_nID <= IDC_MENU_WND_BTN_END) ){
		gGuiMenu.moveMenuCrsr( (long)(m_nID - IDC_MENU_WND_BTN_BGN) );
		gKey.setChar( MENU_COMMAND_KEY_CHAR );

		return;
	}
	// bowkenken END

	CButton::OnMButtonUp(nFlags, point);
}
