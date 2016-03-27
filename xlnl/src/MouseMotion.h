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
* $Id: MouseMotion.h,v 1.11 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef MOUSE_MOTION_H
#define MOUSE_MOTION_H

////////////////////////////////////////////////////////////////
// マウス・モーション
////////////////////////////////////////////////////////////////

class MouseMotion {
private:
	// ドラッグを感知する X 方向の半径のデフォルト
	static const long nDefaultDragXR = 32;
	// ドラッグを感知する Y 方向の半径のデフォルト
	static const long nDefaultDragYR = 32;
	// クリックを感知する X 方向の半径のデフォルト
	static const long nDefaultClickXR = 8;
	// クリックを感知する Y 方向の半径のデフォルト
	static const long nDefaultClickYR = 8;

public:
	// ボタン番号
	enum MouseButtonN {
		nMouseButton0,
		nMouseButton1,
		nMouseButton2,
		nMouseButton3,
		nMouseButton4,
		nMouseButton5,
		nMouseButton6,
		nMouseButton7,
		nMouseButton8,
		nMouseButton9,
		nMouseButton10,
		nMouseButton11,
		nMouseButton12,
		nMouseButton13,
		nMouseButton14,
		nMouseButton15,
		nMouseButtonMaxN,

		nMouseButtonMinN = nMouseButton0,
		nMouseButtonL = nMouseButton0,
		nMouseButtonM = nMouseButton1,
		nMouseButtonR = nMouseButton2,
	};

	// モーションの種類
	enum MotionKind {
		// ドラッグ
		nMotionDrag,
		// 左方向のドラッグ
		nMotionLeft,
		// 右方向のドラッグ
		nMotionRight,
		// 上方向のドラッグ
		nMotionUp,
		// 下方向のドラッグ
		nMotionDown,

		nMotionKindMaxN,

		nMotionKindMinN = nMotionDrag,
	};

	// スクロールの種類
	enum ScrollKind {
		// 左スクロール
		nScrollLeft,
		// 右スクロール
		nScrollRight,
		// 上スクロール
		nScrollUp,
		// 下スクロール
		nScrollDown,

		nScrollKindMaxN,

		nScrollKindMinN = nScrollLeft,
	};

	// コールバック関数の型
	typedef void (*tFunc)(
			long n,
			long nBgnX, long nBgnY,
			long nCurX, long nCurY );

private:
	// ドラッグ開始座標
	long nBgnX[nMouseButtonMaxN], nBgnY[nMouseButtonMaxN];
	// ドラッグを感知する半径
	long nDragXR, nDragYR;
	// クリックを感知する半径
	long nClickXR, nClickYR;
	// 連続してモーションが入らない為のフラグ
	bool bFlagOnce[nMotionKindMaxN];
	// プレス中のフラグ
	bool bFlagPress[nMouseButtonMaxN];

	// ポイントのコールバック関数
	tFunc pFuncPoint;
	// モーションのコールバック関数
	tFunc pFunc[nMouseButtonMaxN][nMotionKindMaxN];
	// クリックのコールバック関数
	tFunc pFuncClick[nMouseButtonMaxN];
	// ダブル・クリックのコールバック関数
	tFunc pFuncDoubleClick[nMouseButtonMaxN];
	// 左+右クリックのコールバック関数
	tFunc pFuncClickLR;
	// 右+左クリックのコールバック関数
	tFunc pFuncClickRL;
	// プレスのコールバック関数
	tFunc pFuncPress[nMouseButtonMaxN];
	// リリースのコールバック関数
	tFunc pFuncRelease[nMouseButtonMaxN];
	// スクロールのコールバック関数
	tFunc pFuncScroll[nScrollKindMaxN];

public:
	MouseMotion();

	void setFuncPoint( tFunc func );
	void setFunc(
			MouseButtonN btn, MotionKind mot,
			tFunc func );
	void setFuncClick( MouseButtonN btn, tFunc func );
	void setFuncDoubleClick( MouseButtonN btn, tFunc func );
	void setFuncClickLR(
			MouseButtonN btnPress,
			tFunc func );
	void setFuncPress( MouseButtonN btn, tFunc func );
	void setFuncRelease( MouseButtonN btn, tFunc func );
	void setFuncScroll( ScrollKind dir, tFunc func );

	void setRegionSize(
			long dxr, long dyr,
			long cxr, long cyr );

	bool begin( MouseButtonN n, long x, long y );
	bool end( MouseButtonN n, long x, long y );
	bool checkPressAndClick(
			MouseButtonN pressN,
			MouseButtonN clickN );
	bool move( long x, long y );

	bool point( long x, long y );
	bool drag( MouseButtonN n, long x, long y );
	bool click( MouseButtonN n, long x, long y );
	bool doubleClick( MouseButtonN n, long x, long y );
	bool clickLR(
			MouseButtonN pressN,
			MouseButtonN clickN,
			long x, long y );
	bool press( MouseButtonN n, long x, long y );
	bool release( MouseButtonN n, long x, long y );
	void releaseAll( long x, long y );
	bool mouseScroll( ScrollKind dir );
};

#endif /* MOUSE_MOTION_H */
