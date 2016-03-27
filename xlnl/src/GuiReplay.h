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
* $Id: GuiReplay.h,v 1.8 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_REPLAY_H
#define GUI_REPLAY_H

////////////////////////////////////////////////////////////////
// リプレイ・ウィンドウ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////

class GuiReplay {

private:
#ifdef D_GTK
	GtkWidget *mReplayTextScroll;
	GtkWidget *mReplayTextView;

	GtkWidget *mButtonTurn;
	GtkWidget *mButtonKey1;
	GtkWidget *mButtonKey10;
	GtkWidget *mButtonCont;
	GtkWidget *mButtonExit;
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

public:
#ifdef D_WS
	void *mReplayWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mReplayWin;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mReplayWin;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *mReplayWin;
#endif // D_IPHONE

#ifdef D_MFC
	class CReplayWnd *mReplayWin;
#endif // D_MFC

public:
	GuiReplay();
	~GuiReplay();
	void init();
	void destroy();

	void bgn();
	void end();

	void draw();
	void redraw();
	void wipe();

	void turnClicked();
	void key1Clicked();
	void key10Clicked();
	void contClicked();
	void exitClicked();

private:
	void newWin();
};

#endif // GUI_REPLAY_H
