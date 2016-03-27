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
* $Id: GuiInputString.h,v 1.18 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_INPUT_STRING_H
#define GUI_INPUT_STRING_H	1

////////////////////////////////////////////////////////////////
// 文字列入力・ウィンドウ
////////////////////////////////////////////////////////////////

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/InputLineDlg.h"
#endif // D_MFC

class GuiInputString {

	//////// プライベート・メンバー変数 ////////
private:

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mTitle;
#endif // D_GTK

	//////// パブリック・メンバー変数 ////////
public:

#ifdef D_WS
	void *mWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mWin;
	GtkWidget *mEntry;
#endif // D_GTK

#ifdef D_MFC
	CInputLineDlg *mInpStrWin;
#endif // D_MFC

	//////// パブリック・メンバー関数 ////////
public:

	GuiInputString();
	~GuiInputString();
	void init();
	void destroy();

	void draw( const char *ttl, const char *str, long len );
	void wipe();

	//////// プライベート・メンバー関数 ////////
private:

	void newWin();
};

#endif /* GUI_INPUT_STRING_H */
