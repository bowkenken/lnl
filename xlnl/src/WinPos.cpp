/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* 本プログラムはフリー・ソフトウェアです。
* あなたは、 Free Software Foundation が公表した
*  GNU 一般公有使用許諾の「バージョン２」
* 或はそれ以降の各バージョンの中からいずれかを選択し、
* そのバージョンが定める条項に従って本プログラムを
* 再頒布または変更することができます。
* 
* 本プログラムは有用とは思いますが、頒布にあたっては、
* 市場性及び特定目的適合性についての暗黙の保証を含めて,
* いかなる保証も行ないません。
* 詳細については GNU 一般公有使用許諾書をお読みください。
* 
* あなたは、本プログラムと一緒に GNU 一般公有使用許諾書
* の写しを受け取っているはずです。そうでない場合は、
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* へ手紙を書いてください。
* 
* $Id: WinPos.cpp,v 1.23 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ウィンドウの座標とサイズの管理
////////////////////////////////////////////////////////////////

#include "gmain.h"
#include "gmain-prot.h"

#include "WinPos.h"
#include "GlobalVar.h"

////////////////////////////////////////////////////////////////
// コンストラクタ
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
// デストラクタ
////////////////////////////////////////////////////////////////

WinPos::~WinPos()
{
}

////////////////////////////////////////////////////////////////
// ウィンドウを返す
// win_kind_t kind : ウィンドウの種類
// return : ウィンドウ
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
// ウィンドウの座標の設定
// win_kind_t kind : ウィンドウの種類
// long *px : X 座標
// long *py : Y 座標
// long *pw : 幅
// long *ph : 高さ
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
// ウィンドウの座標の取得
// win_kind_t kind : ウィンドウの種類
// long *px : X 座標
// long *py : Y 座標
// long *pw : 幅
// long *ph : 高さ
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
// ウィンドウの座標を計算
// win_kind_t kind : ウィンドウの種類
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

	// 座標

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

	// サイズ

	gdk_window_get_size( win, &gw, &gh );

	// 記憶する

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
// ウィンドウを表示
// win_kind_t kind : ウィンドウの種類
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
// ウィンドウを閉じる
// win_kind_t kind : ウィンドウの種類
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
