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
* $Id: CuiMouse.h,v 1.9 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef CUI_MOUSE_H
#define CUI_MOUSE_H	1

////////////////////////////////////////////////////////////////
// コンソール・マウス
////////////////////////////////////////////////////////////////

#include	<stdio.h>

#ifdef	HAVE_GLIB_H
# include	<glib.h>
#else
typedef	unsigned int guint;
#endif

#include	"menu.h"

////////////////////////////////////////////////////////////////
// ハンドラ・テーブル
////////////////////////////////////////////////////////////////

#define	CUI_MOUSE_HANDLER_TAB_MAX_N	80

struct CuiMouseHandlerTab {
	// 有効／無効フラグ
	bool flagEnable;
	// クリックに反応する短形
	long x, y, w, h;
	// ポイント時のハンドラ
	bool_t (*funcPoint)( long btn, long n, const char *macro );
	// クリック時のハンドラ
	bool_t (*funcClick)( long btn, long n, const char *macro );
	// スクロール時のハンドラ
	bool_t (*funcScroll)( long btn, long n, const char *macro );
	// ハンドラへの引数 (整数)
	long argN;
	// ハンドラへの引数 (マクロ)
	char argMacro[MACRO_MAX_LEN + 1];
};

////////////////////////////////////////////////////////////////

class CuiMouse {

// プライベート・メンバー変数
private:

	bool flagReset;
	bool flagEnable;
	bool flagTerm;
	bool flagNoButtonRight;
	bool flagSwapButtonMiddleAndRight;
	const char *envTerm;
	const char *termName;
	FILE *ttyFP;

	guint doubleClickTimer;
	bool flagDoubleClickTime;

	long handlerTabCurN;
	CuiMouseHandlerTab handlerTab[CUI_MOUSE_HANDLER_TAB_MAX_N];

// パブリック・メンバー変数
public:

// パブリック・メンバー関数
public:

	CuiMouse();
	~CuiMouse();
	void init();
	void close();

	long checkEvent( long c );
	long getCharX();
	long getCharY();

	void enableTimer();
	void disableTimer();
	long getDoubleClickMsec();
	void setDoubleClickMsec( long msec );

	void resetHandlerTab();
	long addHandler(
		bool flagEnable,
		long x, long y, long w, long h,
		bool_t (*funcPoint)( long btn, long n, const char *macro ),
		bool_t (*funcClick)( long btn, long n, const char *macro ),
		bool_t (*funcScroll)( long btn, long n, const char *macro ),
		long argN,
		const char *argMacro
	);
	bool checkCallHandler(
		long nBtn,
		long x, long y,
		bool flagPoint,
		bool flagClick = false,
		bool flagScroll = false
	);

// プライベート・メンバー関数
private:
};

#endif /* CUI_MOUSE_H */
