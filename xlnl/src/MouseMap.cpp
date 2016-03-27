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
* $Id: MouseMap.cpp,v 1.48 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// マウスのコール・バック
////////////////////////////////////////////////////////////////

#define	MOUSE_MAP_CPP	1
#include "inc.h"

////////////////////////////////////////////////////////////////

//マウス・ホイールのスクロール方法
// 1 : キー入力
// 0 : 直接スクロール
#define	FLAG_KEY_SCROLL	0

////////////////////////////////////////////////////////////////

#ifdef D_WS
extern WSCwindow* MenuWin;
extern WSCvscrBar *MapScrollX;
extern WSCvscrBar *MapScrollY;
#endif // D_WS

bool bFlagPressTimerRunning;
bool bFlagPressTimer[MouseMotion::nMouseButtonMaxN];

#ifdef D_GTK
gint nPressTimer;
#endif // D_GTK

////////////////////////////////////////////////////////////////
// マウスのコール・バックの初期化
////////////////////////////////////////////////////////////////

void initMouseMotionFunc()
{
	bFlagPressTimerRunning = false;
	for( long i = (long)MouseMotion::nMouseButtonMinN;
			i < (long)MouseMotion::nMouseButtonMaxN; i++ ){
		bFlagPressTimer[i] = false;
	}

#ifdef D_GTK
	nPressTimer = 0;
#endif // D_GTK

	// ポイント

	gMouseMotion.setFuncPoint(
			funcMotionPoint );

	// 左ドラッグ

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonL,
			MouseMotion::nMotionDrag,
			funcMotionDragL );

	// 右ボタンの左方向ドラッグのコール・バック

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonR,
			MouseMotion::nMotionLeft,
			funcMotionLeftR );

	// 右ボタンの右方向ドラッグのコール・バック

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonR,
			MouseMotion::nMotionRight,
			funcMotionRightR );

	// 右ボタンの上方向ドラッグのコール・バック

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonR,
			MouseMotion::nMotionUp,
			funcMotionUpR );

	// 右ボタンの下方向ドラッグのコール・バック

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonR,
			MouseMotion::nMotionDown,
			funcMotionDownR );

	// 左クリック

	gMouseMotion.setFuncClick(
			MouseMotion::nMouseButtonL,
			funcMotionClick );

	// 中クリック

	gMouseMotion.setFuncClick(
			MouseMotion::nMouseButtonM,
			funcMotionClick );

	// 右クリック

	gMouseMotion.setFuncClick(
			MouseMotion::nMouseButtonR,
			funcMotionClick );

	// クリック

	long btnMin = (long)MouseMotion::nMouseButton3;
	long btnMax = (long)MouseMotion::nMouseButtonMaxN;
	for( long i = btnMin; i < btnMax; i++ ){
		gMouseMotion.setFuncClick(
				(MouseMotion::MouseButtonN)i,
				funcMotionClick );
	}

	// 左ダブル・クリック

	gMouseMotion.setFuncDoubleClick(
			MouseMotion::nMouseButtonL,
			funcMotionDoubleClick );

	// 左プレス

	gMouseMotion.setFuncPress(
			MouseMotion::nMouseButtonL,
			funcMotionPress );

	// 中プレス

	gMouseMotion.setFuncPress(
			MouseMotion::nMouseButtonM,
			funcMotionPress );

	// 右プレス

	gMouseMotion.setFuncPress(
			MouseMotion::nMouseButtonR,
			funcMotionPress );

	// 左リリース

	gMouseMotion.setFuncRelease(
			MouseMotion::nMouseButtonL,
			funcMotionRelease );

	// 中リリース

	gMouseMotion.setFuncRelease(
			MouseMotion::nMouseButtonM,
			funcMotionRelease );

	// 右リリース

	gMouseMotion.setFuncRelease(
			MouseMotion::nMouseButtonR,
			funcMotionRelease );

	// 左プレス + 右クリック

	gMouseMotion.setFuncClickLR(
			MouseMotion::nMouseButtonL,
			funcMotionClickLR );

	// 右プレス + 左クリック

	gMouseMotion.setFuncClickLR(
			MouseMotion::nMouseButtonR,
			funcMotionClickLR );

	// 左スクロール

	gMouseMotion.setFuncScroll(
			MouseMotion::nScrollLeft,
			funcMotionScroll );

	// 右スクロール

	gMouseMotion.setFuncScroll(
			MouseMotion::nScrollRight,
			funcMotionScroll );

	// 上スクロール

	gMouseMotion.setFuncScroll(
			MouseMotion::nScrollUp,
			funcMotionScroll );

	// 下スクロール

	gMouseMotion.setFuncScroll(
			MouseMotion::nScrollDown,
			funcMotionScroll );
}

////////////////////////////////////////////////////////////////
// マウス・カーソルによるポイントのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionPoint(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	if( get_flg_draw_menu() )
		return;

	// マップ・カーソルの移動

#ifdef D_MFC
	if( g_flg_gui ){
		nCurX = nCurX * _100_PERCENT / g_Dir3d.nTileSizeRate;
		nCurY = nCurY * _100_PERCENT / g_Dir3d.nTileSizeRate;
	}
#endif // D_MFC

	long x = gPcgDun.getScrollBarX();
	long y = gPcgDun.getScrollBarY();
	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();

	if( nCurX < 0 )
		return;
	if( nCurY < 0 )
		return;
	if( nCurX >= w )
		return;
	if( nCurY >= h )
		return;

	long mapX = (x + nCurX) / gPcgDun.getTileSizeX( true );
	long mapY = (y + nCurY) / gPcgDun.getTileSizeY( true );
	long mapX2 = (x + w) / gPcgDun.getTileSizeX( true );
	long mapY2 = (y + h) / gPcgDun.getTileSizeY( true );

	if( mapX >= mapX2 )
		return;
	if( mapY >= mapY2 )
		return;

	gKey.moveCrsrAbs( mapX, mapY );

	// ステータス・バーにヒントを表示

	if( g_flg_gui )
		guiMapPrintStatBarHint();
}

////////////////////////////////////////////////////////////////
// 左ドラッグのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionDragL(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	long maxX = gPcgDun.getScrollBarMaxX();
	long maxY = gPcgDun.getScrollBarMaxY();
	long dx = nCurX - nBgnX;
	long dy = nCurY - nBgnY;
#ifdef D_MFC
	if( g_flg_gui ){
		dx = dx * _100_PERCENT / g_Dir3d.nTileSizeRate;
		dy = dy * _100_PERCENT / g_Dir3d.nTileSizeRate;
	}
#endif // D_MFC
	long x = gMapDragBgnX - dx;
	long y = gMapDragBgnY - dy;
	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();

	if( x < 0 )
		x = 0;
	if( y < 0 )
		y = 0;
	if( x > maxX)
		x = maxX;
	if( y > maxY)
		y = maxY;

	long sizX = gPcgDun.getTileSizeX( true );
	long sizY = gPcgDun.getTileSizeY( true );
	x = (x / sizX) * sizX;
	y = (y / sizY) * sizY;

	if( gPcgDun.chkScroll( x, y, w, h ) )
		gPcgDun.scrollMap( x, y );
}

////////////////////////////////////////////////////////////////
// 右ボタンの左方向ドラッグのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionLeftR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	callFuncKey( KEY_N_MOUSE_MOTION( KEY_N_MOUSE_MOTION_LEFT ) );
}

////////////////////////////////////////////////////////////////
// 右ボタンの右方向ドラッグのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionRightR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	callFuncKey( KEY_N_MOUSE_MOTION( KEY_N_MOUSE_MOTION_RIGHT ) );
}

////////////////////////////////////////////////////////////////
// 右ボタンの上方向ドラッグのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionUpR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	callFuncKey( KEY_N_MOUSE_MOTION( KEY_N_MOUSE_MOTION_UP ) );
}

////////////////////////////////////////////////////////////////
// 右ボタンの下方向ドラッグのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionDownR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	callFuncKey( KEY_N_MOUSE_MOTION( KEY_N_MOUSE_MOTION_DOWN ) );
}

////////////////////////////////////////////////////////////////
// クリックのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionClick(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	if( get_scene() == SCENE_N_GAME_OVER_END ){
		gKey.setChar( 'Q' - '@' );
		return;
	}

	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) ){
		if( n == MouseMotion::nMouseButtonL )
			gSelMbrGraph->sel( nBgnX, nBgnY );
		if( n == MouseMotion::nMouseButtonR )
			gSelMbrGraph->cancel();
	} else if( chk_scene_group( SCENE_GROUP_N_SPACE ) ){
		if( gPcgDun.pDemoEnding != NULL ){
			if( n == MouseMotion::nMouseButtonL )
				gPcgDun.pDemoEnding->space.addSpeedZ( +1 );
			if( n == MouseMotion::nMouseButtonR )
				gPcgDun.pDemoEnding->space.addSpeedZ( -1 );
		}
	} else {
		callFuncKey( KEY_N_MOUSE_CLICK( n ), true );
	}
}

////////////////////////////////////////////////////////////////
// ダブル・クリックのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionDoubleClick(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) ){
		if( n == MouseMotion::nMouseButtonL )
			gSelMbrGraph->ok();
	} else {
		if( n == MouseMotion::nMouseButtonL ){
			unset_square_pos();
			callFuncKey( KEY_N_MOUSE_D_CLICK( n ), true );
		}
	}
}

////////////////////////////////////////////////////////////////
// 左右同時クリックのコール・バック
// long m : 先にプレスしたマウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionClickLR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	if( get_flg_play_replay() ){
		gKey.setString( "," );
		return;
	}

	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	long fn = KEY_N_MOUSE_PRESS_L_CLICK_R;
	if( n == MouseMotion::nMouseButtonL )
		fn = KEY_N_MOUSE_PRESS_L_CLICK_R;
	else if( n == MouseMotion::nMouseButtonR )
		fn = KEY_N_MOUSE_PRESS_R_CLICK_L;
	else
		return;

	callFuncKey( KEY_N_MOUSE_P_CLICK( fn ) );
}

////////////////////////////////////////////////////////////////
// プレスのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionPress(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	beginPressTimer( n );
}

////////////////////////////////////////////////////////////////
// リリースのコール・バック
// long m : マウス・ボタン番号
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionRelease(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	endPressTimer( n );

	callFuncKey( KEY_N_MOUSE_RELEASE( n ) );
}

////////////////////////////////////////////////////////////////
// プレスのタイマーの開始
// MouseMotion::MouseButtonN n : マウス・ボタン番号
////////////////////////////////////////////////////////////////

void beginPressTimer( MouseMotion::MouseButtonN n )
{
	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	bFlagPressTimerRunning = false;

	if( bFlagPressTimerRunning ){
#ifdef D_GTK
		gtk_timeout_remove( nPressTimer );
#endif // D_GTK
#ifdef D_MFC
	::timeEndPeriod( theApp.m_pMainFrm->nPressTimer );
#endif // D_MFC
	}

	bFlagPressTimer[n] = true;
	bFlagPressTimerRunning = true;

#ifdef D_GTK
	nPressTimer = gtk_timeout_add(
			1000 * PRESS_TIMER_FRAME_RATE / 60,
			callBackPressTimerGtk, NULL );
#endif // D_GTK
#ifdef D_MFC
	::timeBeginPeriod( theApp.m_pMainFrm->nPressTimer );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// プレスのタイマーの終了
// MouseMotion::MouseButtonN n : マウス・ボタン番号
////////////////////////////////////////////////////////////////

void endPressTimer( MouseMotion::MouseButtonN n )
{
	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	bFlagPressTimer[n] = false;

	bool flagPress = false;
	for( long i = (long)MouseMotion::nMouseButtonMinN;
			i < (long)MouseMotion::nMouseButtonMaxN; i++ ){
		if( bFlagPressTimer[i] ){
			flagPress = true;
			break;
		}
	}

	if( !flagPress && bFlagPressTimerRunning ){
		bFlagPressTimerRunning = false;
#ifdef D_GTK
		gtk_timeout_remove( nPressTimer );
#endif // D_GTK
#ifdef D_MFC
		::timeEndPeriod( theApp.m_pMainFrm->nPressTimer );
#endif // D_MFC
	}
}

////////////////////////////////////////////////////////////////
// 一定時間プレスされた時の処理 (GTK+)
// gpointer data : コール・バックが登録された時のデータ
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint callBackPressTimerGtk( gpointer data )
{
	callBackPressTimer();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 一定時間プレスされた時の処理
////////////////////////////////////////////////////////////////

void callBackPressTimer( void )
{
#ifdef D_GTK
	gtk_timeout_remove( nPressTimer );
#endif // D_GTK
#ifdef D_MFC
	::timeEndPeriod( theApp.m_pMainFrm->nPressTimer );
#endif // D_MFC

	if( !bFlagPressTimerRunning )
		return;

	bFlagPressTimerRunning = false;

	for( long i = (long)MouseMotion::nMouseButtonMinN;
			i < (long)MouseMotion::nMouseButtonMaxN; i++ ){
		if( bFlagPressTimer[i] )
			callFuncKey( KEY_N_MOUSE_PRESS( i ) );

		bFlagPressTimer[i] = false;
	}
}

////////////////////////////////////////////////////////////////
// スクロールのコール・バック
// long m : スクロール方向
// long nBgnX : ドラッグ開始 X 座標
// long nBgnY : ドラッグ開始 Y 座標
// long nCurX : 現在の X 座標
// long nCurY : 現在の Y 座標
////////////////////////////////////////////////////////////////

void funcMotionScroll(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	const long scrollMax = 1;

	MouseMotion::ScrollKind dir = (MouseMotion::ScrollKind)m;

	if( dir < MouseMotion::nScrollKindMinN )
		return;
	if( dir >= MouseMotion::nScrollKindMaxN )
		return;

	if( gKey.chkBuf() )
		return;
	if( chk_key_buf() )
		return;
	if( chk_executing_menu() )
		return;

#if	FLAG_KEY_SCROLL
	for( long i = 0; i < scrollMax; i++) {
		switch( dir ){
		case MouseMotion::nScrollLeft:
			gKey.setString( ":/misc/cursor/cursor/scroll/"
					"west\n" );
			break;
		case MouseMotion::nScrollRight:
			gKey.setString( ":/misc/cursor/cursor/scroll/"
					"east\n" );
			break;
		case MouseMotion::nScrollUp:
			gKey.setString( ":/misc/cursor/cursor/scroll/"
					"north\n" );
			break;
		case MouseMotion::nScrollDown:
			gKey.setString( ":/misc/cursor/cursor/scroll/"
					"south\n" );
			break;
		default:
			break;
		}
	}

	gKey.setChar( CMD_KEY_IDLE );
#else
		switch( dir ){
		case MouseMotion::nScrollLeft:
			gPcgDun.scrollTileRel( -1 * scrollMax, +-0 );
			break;
		case MouseMotion::nScrollRight:
			gPcgDun.scrollTileRel( +1 * scrollMax, +-0 );
			break;
		case MouseMotion::nScrollUp:
			gPcgDun.scrollTileRel( +-0, -1 * scrollMax );
			break;
		case MouseMotion::nScrollDown:
			gPcgDun.scrollTileRel( +-0, +1 * scrollMax );
			break;
		default:
			break;
		}
#endif
}

////////////////////////////////////////////////////////////////
// マウス・モーションをファンクション・キーに変換
// long fn : ファンクション・キー番号
// bool flagCheckClear : キー・リピートをバッファにためないか？
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool callFuncKey( long fn, bool flagCheckClear )
{
	if( fn < KEY_N_0 )
		return false;
	if( fn > KEY_N_MAX )
		return false;

	do {
		if( !flagCheckClear )
			break;
		if( !g_flg_clr_key_buf )
			break;
		if( !chk_key_buf() )
			break;
		if( !chk_flg_run_exec_all_phase() )
			break;

		return true;
	} while( 0 );

	char str[63 + 1];
	sn_printf( str, 63, "&a0x%lx;", (long)fn );
	gKey.setString( str );

	return true;
}
