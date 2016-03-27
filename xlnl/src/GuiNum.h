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
* $Id: GuiNum.h,v 1.22 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_NUM_H
#define GUI_NUM_H	1

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウ
////////////////////////////////////////////////////////////////

#define GUI_NUM_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define GUI_NUM_BUTTON_MAX_N	20

////////////////////////////////////////////////////////////////

class GuiNum {

	//////// プライベート・メンバー変数 ////////
private:

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkObject *mHscaleAdjustment;
	GtkWidget *mHscale;

	GtkObject *mNumAdjustment;
	GtkWidget *mNumSpin;

	GtkWidget *mArrowUp[GUI_NUM_BUTTON_MAX_N];
	GtkWidget *mArrowDown[GUI_NUM_BUTTON_MAX_N];
	GtkWidget *mButtonUp[GUI_NUM_BUTTON_MAX_N];
	GtkWidget *mButtonDown[GUI_NUM_BUTTON_MAX_N];
	GtkWidget *mButtonLabel[GUI_NUM_BUTTON_MAX_N];

	GtkWidget *mButtonMin;
	GtkWidget *mButtonClear;
	GtkWidget *mButtonMax;
	GtkWidget *mButtonOk;
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

	//////// パブリック・メンバー変数 ////////
public:

#ifdef D_WS
	void *mNumWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mNumWin;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mNumWin;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *mNumWin;
#endif // D_IPHONE

#ifdef D_MFC
	class CInputNumDlg *mNumWin;
#endif // D_MFC

	bool mFlagInitDone;

	volatile long *mPN;
	long mOrg;
	long mMin;
	long mMax;
	long mFigure;

	//////// パブリック・メンバー関数 ////////
public:

	GuiNum();
	~GuiNum();
	void init();
	void destroy();

	void draw( volatile long *n, long min, long max, long figure );
	void redraw();
	void wipe();

	void valueChanged( long n );
	void up_down_num_label( long n, long d );
	char up_down_num_char( char c, long d );

	void cvUpDownToN();
	void cvUpDownFromN();
	void okClicked( menu_num_t n );

	//////// プライベート・メンバー関数 ////////
private:

	void newWin();
};

#endif /* GUI_NUM_H */
