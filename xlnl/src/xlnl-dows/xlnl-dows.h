// xlnl-dows.h : xlnl-dows ���ץꥱ�������Υᥤ�� �إå��� �ե�����
//
#pragma once

#ifndef __AFXWIN_H__
	#error ���Υե������ PCH �˴ޤ�����ˡ�'stdafx.h' ��ޤ�Ƥ���������
#endif

#include "resource.h"       // �ᥤ�� ����ܥ�

//bowkenken BEGIN
#include "MainFrm.h"
#include "MessageWnd.h"
#include "MenuWnd.h"
#include "StatWnd.h"
#include "ReplayWnd.h"
//bowkenken END

// CxlnldowsApp:
// ���Υ��饹�μ����ˤĤ��Ƥϡ�xlnl-dows.cpp �򻲾Ȥ��Ƥ���������
//

class CxlnldowsApp : public CWinApp
{
//bowkenken BEGIN
public:
	CMainFrame *m_pMainFrm;
	CMessageWnd m_MesWnd;
	CMenuWnd m_MenuWnd;
	CStatWnd m_StatWnd;
	CReplayWnd m_ReplayWnd;
//bowkenken END

public:
	CxlnldowsApp();
	~CxlnldowsApp();
//bowkenken BEGIN
	void InitWin();
//bowkenken END

// �����С��饤��
public:
	virtual BOOL InitInstance();

// ����

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CxlnldowsApp theApp;
