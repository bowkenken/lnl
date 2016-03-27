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
* $Id: GuiMessage.h,v 1.28 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_MESSAGE_H
#define GUI_MESSAGE_H	1

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GtkWSCstring.h"
#endif // D_GTK

#ifdef D_IPHONE
# include "IPhoneWSCstring.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////

class GuiMessage {

	//////// プライベート・メンバー変数 ////////
private:

	bool flagMore;

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mMessageDrawingArea;
	GtkWidget *mMessageHScrollBar;
	GtkWidget *mMessageVScrollBar;
	GtkObject *mMessageHScrollBarAdjustment;
	GtkObject *mMessageVScrollBarAdjustment;

	GdkGC *mFgGc;
	GdkGC *mBgGc;
	GtkStyle *mStyle;
#endif // D_GTK

#ifdef D_MFC
	CClientDC *pDc;
#endif // D_MFC

	//////// パブリック・メンバー変数 ////////
public:

	// 行間隔
	static const long LINE_INTERVAL = 1;
	long mLsMessageDrawBeginN;
	long mLsMessageDrawN;

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mMessageWin;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mMessageWin;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *mMessageWin;
#endif // D_IPHONE

#ifdef D_MFC
	class CMessageWnd *mMessageWin;
#endif // D_MFC

	//////// パブリック・メンバー関数 ////////
public:

	GuiMessage();
	~GuiMessage();

	void init();
	void destroy();

	void setFlagMore( bool flag );

	void redraw();
	void draw( bool flagRedraw );
	void wipe();
	void drawScrollBar();

	void hScroll( long n );
	void vScroll( long n );

	//////// プライベート・メンバー関数 ////////
private:

	void newWin();
};

#endif /* GUI_MESSAGE_H */
