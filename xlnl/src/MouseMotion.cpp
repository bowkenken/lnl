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
* $Id: MouseMotion.cpp,v 1.14 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// マウスのの管理
////////////////////////////////////////////////////////////////

#define	MOUSE_MOTION_CPP	1
#include "inc.h"

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

MouseMotion::MouseMotion()
{
	pFuncPoint = NULL;
	pFuncClickLR = NULL;
	pFuncClickRL = NULL;

	for( long i = nMouseButtonMinN; i < nMouseButtonMaxN; i++ ){
		nBgnX[i] = -1;
		nBgnY[i] = -1;

		for( long j = 0; j < nMotionKindMaxN; j++ ){
			pFunc[i][j] = NULL;
		}
		pFuncClick[i] = NULL;
		pFuncDoubleClick[i] = NULL;
		pFuncPress[i] = NULL;
		pFuncRelease[i] = NULL;
	}
	for( long i = nScrollKindMinN; i < nScrollKindMaxN; i++ )
		pFuncScroll[i] = NULL;

	nDragXR = nDefaultDragXR;
	nDragYR = nDefaultDragYR;
	nClickXR = nDefaultClickXR;
	nClickYR = nDefaultClickYR;
}

////////////////////////////////////////////////////////////////
// ポイントのコールバック関数の登録
// tFunc func : コールバック関数
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncPoint( tFunc func )
{
	pFuncPoint = func;
}

////////////////////////////////////////////////////////////////
// モーションのコールバック関数の登録
// MouseButtonN btn : ボタン番号
// MotionKind mot : モーションの種類
// tFunc func : コールバック関数
////////////////////////////////////////////////////////////////

void MouseMotion::setFunc(
		MouseButtonN btn, MotionKind mot,
		tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;
	if( mot < nMotionKindMinN )
		return;
	if( mot >= nMotionKindMaxN )
		return;

	pFunc[btn][mot] = func;
}

////////////////////////////////////////////////////////////////
// クリックのコールバック関数の登録
// MouseButtonN btn : ボタン番号
// tFunc func : コールバック関数
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncClick( MouseButtonN btn, tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;

	pFuncClick[btn] = func;
}

////////////////////////////////////////////////////////////////
// ダブル・クリックのコールバック関数の登録
// MouseButtonN btn : ボタン番号
// tFunc func : コールバック関数
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncDoubleClick( MouseButtonN btn, tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;

	pFuncDoubleClick[btn] = func;
}

////////////////////////////////////////////////////////////////
// 左右同時クリックのコールバック関数の登録
// MouseButtonN btnPress : 先にプレスするボタン番号
// tFunc func : コールバック関数
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncClickLR( MouseButtonN btnPress, tFunc func )
{
	if( btnPress < nMouseButtonMinN )
		return;
	if( btnPress >= nMouseButtonMaxN )
		return;

	if( btnPress == nMouseButtonL )
		pFuncClickLR = func;
	if( btnPress == nMouseButtonR )
		pFuncClickRL = func;
}

////////////////////////////////////////////////////////////////
// プレスのコールバック関数の登録
// MouseButtonN btn : ボタン番号
// tFunc func : コールバック関数
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncPress( MouseButtonN btn, tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;

	pFuncPress[btn] = func;
}

////////////////////////////////////////////////////////////////
// リリースのコールバック関数の登録
// MouseButtonN btn : ボタン番号
// tFunc func : コールバック関数
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncRelease( MouseButtonN btn, tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;

	pFuncRelease[btn] = func;
}

////////////////////////////////////////////////////////////////
// スクロールのコールバック関数の登録
// ScrollKind dir : モーションの種類
// tFunc func : コールバック関数
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncScroll( ScrollKind dir, tFunc func )
{
	if( dir < nScrollKindMinN )
		return;
	if( dir >= nScrollKindMaxN )
		return;

	pFuncScroll[dir] = func;
}

////////////////////////////////////////////////////////////////
// ドラッグやクリックを感知する半径の登録
// -1 で登録しない
// long dxr : ドラッグを感知する X 方向の半径
// long dyr : ドラッグを感知する Y 方向の半径
// long cxr : クリックを感知する X 方向の半径
// long cyr : クリックを感知する Y 方向の半径
////////////////////////////////////////////////////////////////

void MouseMotion::setRegionSize(
		long dxr, long dyr,
		long cxr, long cyr )
{
	if( dxr > 0 )
		nDragXR = dxr;
	if( dyr > 0 )
		nDragYR = dyr;
	if( cxr > 0 )
		nClickXR = cxr;
	if( cyr > 0 )
		nClickYR = cyr;
}

////////////////////////////////////////////////////////////////
// ドラッグやモーションの感知開始
// MouseButtonN n : ボタン番号
// long x : 開始 X 座標
// long y : 開始 Y 座標
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool MouseMotion::begin( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	nBgnX[n] = x;
	nBgnY[n] = y;

	for( long j = 0; j < nMotionKindMaxN; j++ )
		bFlagOnce[j] = false;

	press( n, x, y );

	return true;
}

////////////////////////////////////////////////////////////////
// ドラッグやモーションの感知終了
// MouseButtonN n : ボタン番号
// long x : 終了 X 座標
// long y : 終了 Y 座標
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool MouseMotion::end( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	release( n, x, y );

	do {
		if( nBgnX[n] <= -1 )
			break;
		if( nBgnY[n] <= -1 )
			break;
		if( labs( nBgnX[n] - x ) > nClickXR )
			break;
		if( labs( nBgnY[n] - y ) > nClickYR )
			break;

		if( checkPressAndClick( nMouseButtonL, n ) ){
			releaseAll( x, y );

			clickLR( nMouseButtonL, n, x, y );

			nBgnX[nMouseButtonL] = -1;
			nBgnY[nMouseButtonL] = -1;
		} else if( checkPressAndClick( nMouseButtonR, n ) ){
			releaseAll( x, y );

			clickLR( nMouseButtonR, n, x, y );

			nBgnX[nMouseButtonR] = -1;
			nBgnY[nMouseButtonR] = -1;
		} else {
			releaseAll( x, y );

			click( n, x, y );
		}
	} while( 0 );

	nBgnX[n] = -1;
	nBgnY[n] = -1;

	return true;
}

////////////////////////////////////////////////////////////////
// 左右同時クリックの感知
// MouseButtonN pressN : 先にプレスしたか調べるボタン番号
// MouseButtonN clickN : 後で実際にクリックしたボタン番号
// return : 左右同時クリックを感知したか？
////////////////////////////////////////////////////////////////

bool MouseMotion::checkPressAndClick(
	MouseButtonN pressN,
	MouseButtonN clickN
)
{
	if( pressN == clickN )
		return false;
	if( (pressN != nMouseButtonL)
			&& (pressN != nMouseButtonR) ){
		return false;
	}
	if( (clickN != nMouseButtonL)
			&& (clickN != nMouseButtonR) ){
		return false;
	}

	if( nBgnX[pressN] <= -1 )
		return false;
	if( nBgnY[pressN] <= -1 )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// カーソルの移動による、ドラッグやポイントの感知
// long x : 現在の X 座標
// long y : 現在の Y 座標
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool MouseMotion::move( long x, long y )
{
	bool flgRelease = false;
	for( long i = nMouseButtonMinN; i < nMouseButtonMaxN; i++ ){
		if( nBgnX[i] <= -1 )
			continue;
		if( nBgnY[i] <= -1 )
			continue;
		if( (labs( x - nBgnX[i] ) < nClickXR)
				&& (labs( y - nBgnY[i] ) < nClickYR) ){
			continue;
		}

		flgRelease = true;
		break;
	}
	if( flgRelease )
		releaseAll( x, y );

	bool flgPoint = true;
	for( long i = nMouseButtonMinN; i < nMouseButtonMaxN; i++ ){
		if( (nBgnX[i] > -1) && (nBgnY[i] > -1) ){
			drag( (MouseButtonN)i, x, y );
			flgPoint = false;
		}
	}
	if( flgPoint )
		point( x, y );

	return true;
}

////////////////////////////////////////////////////////////////
// ポイントのコールバック関数の呼び出し
// long x : 現在の X 座標
// long y : 現在の Y 座標
// return : コールバック関数を呼び出したか？
////////////////////////////////////////////////////////////////

bool MouseMotion::point( long x, long y )
{
	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();

	if( x >= w + 16 )
		return false;
	if( y >= h + 16 )
		return false;

	// ポイント
	if( pFuncPoint != NULL ){
		(*pFuncPoint)( (MouseButtonN)0, 0, 0, x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ドラッグとモーションのコールバック関数の呼び出し
// MouseButtonN n : ボタン番号
// long x : 現在の X 座標
// long y : 現在の Y 座標
// return : コールバック関数を呼び出したか？
////////////////////////////////////////////////////////////////

bool MouseMotion::drag( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	// ドラッグ
	if( pFunc[n][nMotionDrag] != NULL ){
		(*(pFunc[n][nMotionDrag]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	if( (labs( x - nBgnX[n] ) < nDragXR)
			&& (labs( y - nBgnY[n] ) < nDragYR) ){
		for( long j = 0; j < nMotionKindMaxN; j++ ){
			bFlagOnce[j] = false;
		}
	}

	// 左モーション
	do {
		if( labs( x - nBgnX[n] ) < labs( y - nBgnY[n] ) )
			break;
		if( (x - nBgnX[n]) > -nDragXR )
			break;
		if( bFlagOnce[nMotionLeft] )
			break;

		for( long j = 0; j < nMotionKindMaxN; j++ )
			bFlagOnce[j] = false;
		bFlagOnce[nMotionLeft] = true;

		if( pFunc[n][nMotionLeft] != NULL ){
			(*(pFunc[n][nMotionLeft]))(
					n, nBgnX[n], nBgnY[n], x, y );

			return true;
		}
	} while( 0 );

	// 右モーション
	do {
		if( labs( x - nBgnX[n] ) < labs( y - nBgnY[n] ) )
			break;
		if( (x - nBgnX[n]) < +nDragXR )
			break;
		if( bFlagOnce[nMotionRight] )
			break;

		for( long j = 0; j < nMotionKindMaxN; j++ )
			bFlagOnce[j] = false;
		bFlagOnce[nMotionRight] = true;

		if( pFunc[n][nMotionRight] != NULL ){
			(*(pFunc[n][nMotionRight]))(
					n, nBgnX[n], nBgnY[n], x, y );

			return true;
		}
	} while( 0 );

	// 上モーション
	do {
		if( labs( y - nBgnY[n] ) < labs( x - nBgnX[n] ) )
			break;
		if( (y - nBgnY[n]) > -nDragYR )
			break;
		if( bFlagOnce[nMotionUp] )
			break;

		for( long j = 0; j < nMotionKindMaxN; j++ )
			bFlagOnce[j] = false;
		bFlagOnce[nMotionUp] = true;

		if( pFunc[n][nMotionUp] != NULL ){
			(*(pFunc[n][nMotionUp]))(
					n, nBgnX[n], nBgnY[n], x, y );

			return true;
		}
	} while( 0 );

	// 下モーション
	do {
		if( labs( y - nBgnY[n] ) < labs( x - nBgnX[n] ) )
			break;
		if( (y - nBgnY[n]) < +nDragYR )
			break;
		if( bFlagOnce[nMotionDown] )
			break;

		for( long j = 0; j < nMotionKindMaxN; j++ )
			bFlagOnce[j] = false;
		bFlagOnce[nMotionDown] = true;

		if( pFunc[n][nMotionDown] != NULL ){
			(*(pFunc[n][nMotionDown]))(
					n, nBgnX[n], nBgnY[n], x, y );

			return true;
		}
	} while( 0 );

	return false;
}

////////////////////////////////////////////////////////////////
// クリックのコールバック関数の呼び出し
// MouseButtonN n : ボタン番号
// long x : 現在の X 座標
// long y : 現在の Y 座標
// return : コールバック関数を呼び出したか？
////////////////////////////////////////////////////////////////

bool MouseMotion::click( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	if( pFuncClick[n] != NULL ){
		(*(pFuncClick[n]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ダブル・クリックのコールバック関数の呼び出し
// MouseButtonN n : ボタン番号
// long x : 現在の X 座標
// long y : 現在の Y 座標
// return : コールバック関数を呼び出したか？
////////////////////////////////////////////////////////////////

bool MouseMotion::doubleClick( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	if( pFuncDoubleClick[n] != NULL ){
		(*(pFuncDoubleClick[n]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// 左右同時クリックのコールバック関数の呼び出し
// MouseButtonN pressN : 先にプレスしたボタン番号
// MouseButtonN clickN : 後でクリックしたボタン番号
// long x : 現在の X 座標
// long y : 現在の Y 座標
// return : コールバック関数を呼び出したか？
////////////////////////////////////////////////////////////////

bool MouseMotion::clickLR(
	MouseButtonN pressN,
	MouseButtonN clickN,
	long x, long y
)
{
	if( (pressN == nMouseButtonL) && (clickN == nMouseButtonR) ){
		if( pFuncClickLR != NULL ){
			(*pFuncClickLR)( pressN,
					nBgnX[pressN], nBgnY[pressN],
					x, y );

			return true;
		}
	}
	if( (pressN == nMouseButtonR) && (clickN == nMouseButtonL) ){
		if( pFuncClickRL != NULL ){
			(*pFuncClickRL)( pressN,
					nBgnX[pressN], nBgnY[pressN],
					x, y );

			return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////
// プレスのコールバック関数の呼び出し
// MouseButtonN n : ボタン番号
// long x : 現在の X 座標
// long y : 現在の Y 座標
// return : コールバック関数を呼び出したか？
////////////////////////////////////////////////////////////////

bool MouseMotion::press( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	bFlagPress[n] = true;

	if( pFuncPress[n] != NULL ){
		(*(pFuncPress[n]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// リリースのコールバック関数の呼び出し
// MouseButtonN n : ボタン番号
// long x : 現在の X 座標
// long y : 現在の Y 座標
// return : コールバック関数を呼び出したか？
////////////////////////////////////////////////////////////////

bool MouseMotion::release( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	if( !bFlagPress[n] )
		return false;
	bFlagPress[n] = false;

	if( pFuncRelease[n] != NULL ){
		(*(pFuncRelease[n]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// 全てのリリースのコールバック関数の呼び出し
// long x : 現在の X 座標
// long y : 現在の Y 座標
// return : コールバック関数を呼び出したか？
////////////////////////////////////////////////////////////////

void MouseMotion::releaseAll( long x, long y )
{
	for( long i = (long)nMouseButtonMinN;
			i < (long)nMouseButtonMaxN; i++ ){
		release( (MouseButtonN)i, x, y );
	}
}

////////////////////////////////////////////////////////////////
// スクロールのコールバック関数の呼び出し
// ScrollKind dir : モーションの種類
// return : コールバック関数を呼び出したか？
////////////////////////////////////////////////////////////////

bool MouseMotion::mouseScroll( ScrollKind dir )
{
	if( dir < nScrollKindMinN )
		return false;
	if( dir >= nScrollKindMaxN )
		return false;

	if( pFuncScroll[dir] != NULL ){
		(*(pFuncScroll[dir]))( (long)dir, 0, 0, 0, 0 );

		return true;
	}

	return false;
}
