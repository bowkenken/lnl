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
* $Id: WinPos.h,v 1.8 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef WIN_POS_H
#define WIN_POS_H

////////////////////////////////////////////////////////////////
// ウィンドウの座標とサイズの管理
////////////////////////////////////////////////////////////////

#include "win-kind.h"

#ifdef D_WS
#endif //D_WS

#ifdef D_GTK
#include "gtk/gtk.h"
#endif //D_GTK

#ifdef D_MFC
#endif //D_MFC

class WinPos {

private:
	bool flagDraw;
	long mX, mY, mW, mH;

public:
	WinPos();
	~WinPos();

	void *getWin( win_kind_t kind );

	void set(
		win_kind_t kind,
		long *px, long *py,
		long *pw, long *ph );
	void get(
		win_kind_t kind,
		long *px, long *py,
		long *pw, long *ph );

	void calc( win_kind_t kind );

	void draw( win_kind_t kind, bool flagDlg = false );
	void wipe( win_kind_t kind, bool flagDlg = false );
};

#endif // WIN_POS_H
