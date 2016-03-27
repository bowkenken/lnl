// xlnl-dows.h : xlnl-dows アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"       // メイン シンボル

//bowkenken BEGIN
#include "MainFrm.h"
#include "MessageWnd.h"
#include "MenuWnd.h"
#include "StatWnd.h"
#include "ReplayWnd.h"
//bowkenken END

// CxlnldowsApp:
// このクラスの実装については、xlnl-dows.cpp を参照してください。
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

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CxlnldowsApp theApp;
