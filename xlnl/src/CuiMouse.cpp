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
* $Id: CuiMouse.cpp,v 1.18 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// コンソール・マウス
////////////////////////////////////////////////////////////////

#define CUI_MOUSE_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#ifdef	D_CUI_MOUSE
gint handleDoubleClickTimer( gpointer p );
#endif	// D_CUI_MOUSE

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

CuiMouse::CuiMouse()
{
	flagEnable = false;
	flagTerm = false;
	flagNoButtonRight = false;
	envTerm = NULL;
	termName = "term";
	ttyFP = NULL;

	flagDoubleClickTime = false;
	doubleClickTimer = -1;

	handlerTabCurN = 0;
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

CuiMouse::~CuiMouse()
{
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void CuiMouse::init()
{
#ifdef	D_CUI_MOUSE
	if( !g_flg_cui_mouse )
		return;
	if( flagEnable )
		return;

#ifdef	HAVE_GPM_H
	Gpm_Connect connect;
	connect.eventMask = ~0;
	connect.defaultMask = 0;
	connect.maxMod = 0;
	connect.minMod = 0;

	if( Gpm_Open( &connect, 0 ) == -2 ){
		Gpm_Close();
		flagTerm = true;
	} else {
		flagTerm = false;
	}
#else	// HAVE_GPM_H
	flagTerm = true;
#endif	// HAVE_GPM_H

	envTerm = getenv( "TERM" );
	if( envTerm == NULL )
		termName = "term";
	else
		termName = envTerm;

	if( flagTerm ){
		int fd = -1;
#ifdef	HAVE_SYS_FCNTL_H
		fd = open( "/dev/tty", O_RDWR );
#endif	// HAVE_SYS_FCNTL_H
		if( fd <= -1 )
			fd = 2;
		ttyFP = fdopen( fd, "w" );

		if( ttyFP != NULL ){
			fputs( "\033[?1001s", ttyFP );
			fputs( "\033[?1000h", ttyFP );
			fflush( ttyFP );
		}
	} else {
		termName = "gpm";
	}

	print_msg( FLG_MSG_DEBUG | FLG_MSG_NO_MORE,
			"CUI Mouse [%s]", termName );

	flagEnable = true;

	resetHandlerTab();
#endif	// D_CUI_MOUSE
}

////////////////////////////////////////////////////////////////
// 終了
////////////////////////////////////////////////////////////////

void CuiMouse::close()
{
#ifdef	D_CUI_MOUSE
	if( !g_flg_cui_mouse )
		return;
	if( !flagEnable )
		return;

	if( flagTerm ){
		if( ttyFP != NULL ){
			fputs( "\033[?1000l", ttyFP );
			fputs( "\033[?1001r", ttyFP );
			fflush( ttyFP );

			ttyFP = NULL;
		}

		flagTerm = false;
	} else {
#ifdef	HAVE_GPM_H
		Gpm_Close();
#endif	// HAVE_GPM_H
	}

	flagEnable = false;
#endif	// D_CUI_MOUSE
}

////////////////////////////////////////////////////////////////
// キーをマウス・イベントに変換
// long c : キー
// return : キー
////////////////////////////////////////////////////////////////

long CuiMouse::checkEvent( long c )
{
#ifdef	D_CUI_MOUSE
	if( !g_flg_cui_mouse )
		return '\0';

	long event = curs_getch() - 32;

	static MouseMotion::MouseButtonN nPreBtn
			= MouseMotion::nMouseButton0;

	MouseMotion::MouseButtonN nBtn = MouseMotion::nMouseButton0;
	if( flagNoButtonRight ){
		if( event == 0 )
			nBtn = MouseMotion::nMouseButton0;
		if( event == 1 )
			nBtn = MouseMotion::nMouseButton2;
		if( event == 2 )
			nBtn = MouseMotion::nMouseButton2;
	} else if( g_flg_cui_mouse_swap_btn ){
		if( event == 0 )
			nBtn = MouseMotion::nMouseButton0;
		if( event == 1 )
			nBtn = MouseMotion::nMouseButton2;
		if( event == 2 )
			nBtn = MouseMotion::nMouseButton1;
	} else {
		if( event == 0 )
			nBtn = MouseMotion::nMouseButton0;
		if( event == 1 )
			nBtn = MouseMotion::nMouseButton1;
		if( event == 2 )
			nBtn = MouseMotion::nMouseButton2;
	}

	MouseMotion::ScrollKind nScroll = MouseMotion::nScrollDown;
	if( event == 0x40 )
		nScroll = MouseMotion::nScrollUp;
	if( event == 0x41 )
		nScroll = MouseMotion::nScrollDown;
	if( event == 0x42 )
		nScroll = MouseMotion::nScrollLeft;
	if( event == 0x43 )
		nScroll = MouseMotion::nScrollRight;

	static bool flagDoubleClick = false;
	bool flagCalled = false;

	static long preX = 0;
	static long preY = 0;

	long x = getCharX();
	long y = getCharY();
	long xx = x * CUI_TILE_SIZE_X / 2;
	long yy = y * CUI_TILE_SIZE_Y;

	if( (0 <= event) && (event <= 2) ){
		gMapDragBgnX = gPcgDun.getScrollBarX();
		gMapDragBgnY = gPcgDun.getScrollBarY();

		if( !get_flg_play_replay() ){
			flagCalled = checkCallHandler( nBtn, x, y,
					true, false );
			if( !flagCalled ){
				gMouseMotion.move( xx, yy );
				gMouseMotion.begin( nBtn, xx, yy );
			}

			if( flagDoubleClickTime ){
				disableTimer();

				flagCalled = checkCallHandler( nBtn, x, y,
						true, false );
				if( !flagCalled && (nBtn == nPreBtn) ){
					flagDoubleClick = true;

					gMouseMotion.doubleClick(
							nBtn, xx, yy );
				}
			} else {
				enableTimer();
			}
		}

		nPreBtn = nBtn;
		preX = x;
		preY = y;
	}

	if( event == 3 ){
		if( get_flg_play_replay() ){
			if( nPreBtn == MouseMotion::nMouseButton0 )
				return '\n';
			if( nPreBtn == MouseMotion::nMouseButton2 )
				return '5';
		} else {
			flagCalled = false;
			if( (x == preX) && (y == preY)
					&& !flagDoubleClick ){
				flagCalled = checkCallHandler( nPreBtn, x, y,
						false, true );
			}
			if( !flagCalled ){
				gMouseMotion.move( xx, yy );
				gMouseMotion.end( nPreBtn, xx, yy );
			}

			flagDoubleClick = false;
		}
	}

	if( (0x40 <= event) && (event <= 0x43) ){
		if( get_flg_play_replay() ){
			if( nScroll == MouseMotion::nScrollUp )
				return '\n';
			if( nScroll == MouseMotion::nScrollDown )
				return '5';
		} else {
			flagCalled = checkCallHandler( nScroll, x, y,
					false, false, true );
			if( !flagCalled )
				gMouseMotion.mouseScroll( nScroll );
		}
	}
#endif	// D_CUI_MOUSE

	return '\0';
}

////////////////////////////////////////////////////////////////
// X 座標のキーの読み込み
// return : X 座標
////////////////////////////////////////////////////////////////

long CuiMouse::getCharX()
{
#ifdef	D_CUI_MOUSE
	if( !g_flg_cui_mouse )
		return 0;

	long x = curs_getch() - 32 - 1;

	return x;
#endif	// D_CUI_MOUSE

	return 0;
}

////////////////////////////////////////////////////////////////
// Y 座標のキーの読み込み
// return : Y 座標
////////////////////////////////////////////////////////////////

long CuiMouse::getCharY()
{
#ifdef	D_CUI_MOUSE
	if( !g_flg_cui_mouse )
		return 0;

	long y = curs_getch() - 32 - 1;

	return y;
#endif	// D_CUI_MOUSE

	return 0;
}

////////////////////////////////////////////////////////////////
// ダブル・クリックのタイマーを有効にする
////////////////////////////////////////////////////////////////

void CuiMouse::enableTimer()
{
#ifdef	D_CUI_MOUSE
	if( !flagDoubleClickTime ){
		doubleClickTimer = gtk_timeout_add(
				get_cui_mouse_double_click_msec(),
				handleDoubleClickTimer, NULL );

		flagDoubleClickTime = true;
	}
#endif	// D_CUI_MOUSE
}

////////////////////////////////////////////////////////////////
// ダブル・クリックのタイマーを無効にする
////////////////////////////////////////////////////////////////

void CuiMouse::disableTimer()
{
#ifdef	D_CUI_MOUSE
	if( flagDoubleClickTime ){
		flagDoubleClickTime = false;

		gtk_timeout_remove( doubleClickTimer );
	}
#endif	// D_CUI_MOUSE
}

////////////////////////////////////////////////////////////////
// ダブル・クリックのタイマー処理
// gpointer p : 引数
// return : ?
////////////////////////////////////////////////////////////////

#ifdef	D_GTK
gint handleDoubleClickTimer( gpointer p )
{
#ifdef	D_CUI_MOUSE
	gCuiMouse.disableTimer();
#endif	// D_CUI_MOUSE

	return 0;
}
#endif	// D_GTK

////////////////////////////////////////////////////////////////
// マウス・イベント・ハンドラをリセット
////////////////////////////////////////////////////////////////

void CuiMouse::resetHandlerTab()
{
#ifdef	D_CUI_MOUSE
	handlerTabCurN = 0;
	for( long n = 0; n < CUI_MOUSE_HANDLER_TAB_MAX_N; n++ )
		handlerTab[n].flagEnable = false;
#endif	// D_CUI_MOUSE
}

////////////////////////////////////////////////////////////////
// ハンドラ・テーブルに追加
// bool flagEnable : 有効／無効フラグ
// long x : クリックに反応する短形の開始 X 座標
// long y : クリックに反応する短形の開始 Y 座標
// long w : クリックに反応する短形の幅
// long h : クリックに反応する短形の高さ
// bool_t (*funcPoint)( long btn, long n, const char *macro ) : 
//   ポイント時のハンドラ
// bool_t (*funcClick)( long btn, long n, const char *macro ) : 
//   クリック時のハンドラ
// bool_t (*funcScroll)( long btn, long n, const char *macro ) : 
//   スクロール時のハンドラ
// long argN : ハンドラへの引数 (整数)
// const char *argMacro : ハンドラへの引数 (マクロ)
// return : ハンドラ・テーブル番号
////////////////////////////////////////////////////////////////

long CuiMouse::addHandler(
	bool flagEnable,
	long x, long y, long w, long h,
	bool_t (*funcPoint)( long btn, long n, const char *macro ),
	bool_t (*funcClick)( long btn, long n, const char *macro ),
	bool_t (*funcScroll)( long btn, long n, const char *macro ),
	long argN,
	const char *argMacro
)
{
#ifdef	D_CUI_MOUSE
	if( !g_flg_cui_mouse )
		return -1;

	if( handlerTabCurN >= CUI_MOUSE_HANDLER_TAB_MAX_N )
		return -1;
	long n = handlerTabCurN;
	handlerTabCurN++;

	handlerTab[n].flagEnable = false;
	handlerTab[n].x = x;
	handlerTab[n].y = y;
	handlerTab[n].w = w;
	handlerTab[n].h = h;
	handlerTab[n].funcPoint = funcPoint;
	handlerTab[n].funcClick = funcClick;
	handlerTab[n].funcScroll = funcScroll;
	handlerTab[n].argN = argN;
	if( argMacro == NULL ){
		str_nz_cpy( handlerTab[n].argMacro, "",
				MACRO_MAX_LEN );
	} else {
		str_nz_cpy( handlerTab[n].argMacro, argMacro,
				MACRO_MAX_LEN );
	}
	handlerTab[n].flagEnable = flagEnable;

	return n;
#endif	// D_CUI_MOUSE

	return -1;
}

////////////////////////////////////////////////////////////////
// クリック時のハンドラをチェックして呼び出す
// long nBtn : ボタン番号
// long x : クリックされた X 座標
// long y : クリックされた Y 座標
// bool flagPoint : ポイント・ハンドラを呼ぶか?
// bool flagClick : クリック・ハンドラを呼ぶか?
// bool flagScroll : スクロール・ハンドラを呼ぶか?
// return : ハンドラを読んだか?
////////////////////////////////////////////////////////////////

bool CuiMouse::checkCallHandler(
	long nBtn,
	long x, long y,
	bool flagPoint,
	bool flagClick,
	bool flagScroll
)
{
	bool flagCalled = false;

#ifdef	D_CUI_MOUSE
	if( !g_flg_cui_mouse )
		return false;

	for( long n = 0; n < handlerTabCurN; n++ ){
		if( !handlerTab[n].flagEnable )
			continue;

		if( x < handlerTab[n].x )
			continue;
		if( y < handlerTab[n].y )
			continue;
		if( x >= (handlerTab[n].x + handlerTab[n].w) )
			continue;
		if( y >= (handlerTab[n].y + handlerTab[n].h) )
			continue;

		if( flagPoint && (handlerTab[n].funcPoint != NULL) ){
			flagCalled = (*(handlerTab[n].funcPoint))(
					nBtn,
					handlerTab[n].argN,
					handlerTab[n].argMacro );
		}
		if( flagCalled )
			break;

		if( flagClick && (handlerTab[n].funcClick != NULL) ){
			flagCalled = (*(handlerTab[n].funcClick))(
					nBtn,
					handlerTab[n].argN,
					handlerTab[n].argMacro );
		}
		if( flagCalled )
			break;

		if( flagScroll && (handlerTab[n].funcScroll != NULL) ){
			flagCalled = (*(handlerTab[n].funcScroll))(
					nBtn,
					handlerTab[n].argN,
					handlerTab[n].argMacro );
		}
		if( flagCalled )
			break;
	}
#endif	// D_CUI_MOUSE

	return flagCalled;
}
