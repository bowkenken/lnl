/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ����ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�����
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�����ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ����Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: WinPos.cpp,v 1.23 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ������ɥ��κ�ɸ�ȥ������δ���
////////////////////////////////////////////////////////////////

#include "gmain.h"
#include "gmain-prot.h"

#include "WinPos.h"
#include "GlobalVar.h"

////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

WinPos::WinPos()
{
	flagDraw = false;
	mX = 0;
	mY = 0;
	mW = -1;
	mH = -1;
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

WinPos::~WinPos()
{
}

////////////////////////////////////////////////////////////////
// ������ɥ����֤�
// win_kind_t kind : ������ɥ��μ���
// return : ������ɥ�
////////////////////////////////////////////////////////////////

void *WinPos::getWin( win_kind_t kind )
{
#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	switch( kind ){
	case WIN_KIND_NULL:
		break;
	case WIN_KIND_MAP:
		return gMapWin;
	case WIN_KIND_SEL_CONF:
		return gSelConf.mSelConfWin;
	case WIN_KIND_MENU:
		return gGuiMenu.mMenuWin;
	case WIN_KIND_MESSAGE:
		return gGuiMessage.mMessageWin;
	case WIN_KIND_STAT:
		return gGuiStat.mStatWin;
	case WIN_KIND_STAT_1:
	case WIN_KIND_STAT_2:
	case WIN_KIND_STAT_3:
	case WIN_KIND_STAT_4:
	case WIN_KIND_STAT_5:
	case WIN_KIND_STAT_6:
		break;
	case WIN_KIND_INPUT_NUM:
		return gGuiNum.mNumWin;
	case WIN_KIND_INPUT_STRING:
		return gGuiInpStr.mWin;
	case WIN_KIND_WORDS:
		return gGuiWords.mWordsWin;
	case WIN_KIND_REPLAY:
		return gGuiReplay.mReplayWin;
	case WIN_KIND_CLASS_EDIT:
		return gGuiClassEdit.mClassEditWin;
	case WIN_KIND_SKILL_EDIT:
		return gGuiSkillEdit.mSkillEditWin;
	case WIN_KIND_CHR_SHEET:
		return gGuiChrSheet.mChrSheetWin;
	case WIN_KIND_MAX_N:
		break;
	}
#endif //D_GTK

#ifdef D_MFC
	switch( kind ){
	case WIN_KIND_NULL:
		break;
	case WIN_KIND_MAP:
		return theApp.m_pMainWnd;
	case WIN_KIND_SEL_CONF:
		return gSelConf.mDlg;
	case WIN_KIND_MENU:
		return gGuiMenu.mMenuWin;
	case WIN_KIND_MESSAGE:
		return gGuiMessage.mMessageWin;
	case WIN_KIND_STAT:
		return gGuiStat.mStatWin;
	case WIN_KIND_STAT_1:
	case WIN_KIND_STAT_2:
	case WIN_KIND_STAT_3:
	case WIN_KIND_STAT_4:
	case WIN_KIND_STAT_5:
	case WIN_KIND_STAT_6:
		break;
	case WIN_KIND_INPUT_NUM:
		return gGuiNum.mNumWin;
	case WIN_KIND_INPUT_STRING:
		return gGuiInpStr.mInpStrWin;
	case WIN_KIND_WORDS:
		return gGuiWords.mWordsWin;
	case WIN_KIND_REPLAY:
		return gGuiReplay.mReplayWin;
	case WIN_KIND_CLASS_EDIT:
		return gGuiClassEdit.mClassEditWin;
	case WIN_KIND_CHR_SHEET:
		return gGuiChrSheet.mChrSheetWin;
	case WIN_KIND_MAX_N:
		break;
	}
#endif //D_MFC

	return NULL;
}

////////////////////////////////////////////////////////////////
// ������ɥ��κ�ɸ������
// win_kind_t kind : ������ɥ��μ���
// long *px : X ��ɸ
// long *py : Y ��ɸ
// long *pw : ��
// long *ph : �⤵
////////////////////////////////////////////////////////////////

void WinPos::set(
	win_kind_t kind,
	long *px, long *py,
	long *pw, long *ph )
{
	if( px != NULL )
		mX = *px;
	if( py != NULL )
		mY = *py;
	if( pw != NULL )
		mW = *pw;
	if( ph != NULL )
		mH = *ph;

	if( flagDraw )
		draw( kind );
}

////////////////////////////////////////////////////////////////
// ������ɥ��κ�ɸ�μ���
// win_kind_t kind : ������ɥ��μ���
// long *px : X ��ɸ
// long *py : Y ��ɸ
// long *pw : ��
// long *ph : �⤵
////////////////////////////////////////////////////////////////

void WinPos::get(
	win_kind_t kind,
	long *px, long *py,
	long *pw, long *ph )
{
	if( flagDraw )
		calc( kind );

	if( px != NULL )
		*px = mX;
	if( py != NULL )
		*py = mY;
	if( pw != NULL )
		*pw = mW;
	if( ph != NULL )
		*ph = mH;
}

////////////////////////////////////////////////////////////////
// ������ɥ��κ�ɸ��׻�
// win_kind_t kind : ������ɥ��μ���
////////////////////////////////////////////////////////////////

void WinPos::calc( win_kind_t kind )
{
	if( !flagDraw )
		return;

	void *pWin = getWin( kind );
	if( pWin == NULL )
		return;

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	gint gx, gy, gw, gh;
	gint fx, fy, fd;
	gint posX, posY, bgnX, bgnY, endX, endY;

	GdkWindow *win = GTK_WIDGET( pWin )->window;

	// ��ɸ

	gdk_window_get_position( win, &posX, &posY );
	gdk_window_get_deskrelative_origin( win, &fx, &fy );
	gdk_window_get_root_origin( win, &bgnX, &bgnY );
	gdk_window_get_origin( win, &endX, &endY );

	if( g_flg_gnome )
		fd = 0;
	else
		fd = fx - bgnX;

	gx = posX - (endX - bgnX - fd);
	gy = posY - (endY - bgnY - fd);

	// ������

	gdk_window_get_size( win, &gw, &gh );

	// ��������

	mX = gx;
	mY = gy;
	mW = gw;
	mH = gh;
#endif //D_GTK

#ifdef D_MFC
	CRect rect;
	((CWnd *)pWin)->GetWindowRect( &rect );

	mX = rect.left;
	mY = rect.top;
	mW = rect.Width();
	mH = rect.Height();
#endif //D_MFC
}

////////////////////////////////////////////////////////////////
// ������ɥ���ɽ��
// win_kind_t kind : ������ɥ��μ���
////////////////////////////////////////////////////////////////

void WinPos::draw( win_kind_t kind, bool flagDlg )
{
#ifdef D_GTK
	if( flagDraw )
		return;
#endif //D_GTK

	void *pWin = getWin( kind );
	if( pWin == NULL )
		return;

#ifdef D_WS
	pWin->setVisible( true );
#endif // D_WS

#ifdef D_GTK
	gtk_widget_show( GTK_WIDGET( pWin ) );

	if( g_flg_set_win_pos ){
		if( (mW > 0) && (mH > 0) ){
			gdk_window_move( GTK_WIDGET( pWin )->window,
					mX, mY );
			gdk_window_resize( GTK_WIDGET( pWin )->window,
					mW, mH );
		}
	}

	gdk_window_raise( GTK_WIDGET( pWin )->window );
#endif //D_GTK

#ifdef D_MFC
	if( flagDlg ){
		CRect rect;
		((CWnd *)pWin)->GetWindowRect( &rect );

		mW = rect.Width();
		mH = rect.Height();

		if( g_flg_set_win_pos ){
			if( (mW > 0) && (mH > 0) ){
				((CDialog *)pWin)->MoveWindow(
						mX, mY, mW, mH );
			}
		}
	} else {
		((CWnd *)pWin)->ShowWindow( SW_SHOW );
		if( g_flg_set_win_pos ){
			if( (mW > 0) && (mH > 0) ){
				((CWnd *)pWin)->MoveWindow(
						mX, mY, mW, mH );
			}
		}
		((CWnd *)pWin)->BringWindowToTop();
		((CWnd *)pWin)->UpdateWindow();
	}
#endif //D_MFC

	flagDraw = true;
}

////////////////////////////////////////////////////////////////
// ������ɥ����Ĥ���
// win_kind_t kind : ������ɥ��μ���
////////////////////////////////////////////////////////////////

void WinPos::wipe( win_kind_t kind, bool flagDlg )
{
#ifdef D_GTK
	if( !flagDraw )
		return;
#endif //D_GTK

	void *pWin = getWin( kind );
	if( pWin == NULL )
		return;

	calc( kind );

#ifdef D_WS
	pWin->setVisible( false );
#endif // D_WS

#ifdef D_GTK
	gtk_widget_hide( GTK_WIDGET( pWin ) );
#endif //D_GTK

#ifdef D_MFC
	if( !flagDlg )
		((CWnd *)pWin)->ShowWindow( SW_HIDE );
#endif //D_MFC

	flagDraw = false;
}
