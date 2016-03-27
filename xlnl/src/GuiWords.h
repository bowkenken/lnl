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
* $Id: GuiWords.h,v 1.10 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_WORDS_H
#define GUI_WORDS_H	1

////////////////////////////////////////////////////////////////
// 台詞ウィンドウ
////////////////////////////////////////////////////////////////

class GuiWords {

	//////// プライベート・メンバー変数 ////////
private:

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mWordsTextScroll;
	GtkWidget *mWordsTextView;
	GtkWidget *mButtonOk;
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

	//////// パブリック・メンバー変数 ////////
public:

#ifdef D_WS
	void *mWordsWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mWordsWin;
#endif // D_GTK

#ifdef D_MAC
	void *mWordsWin;
#endif // D_MAC

#ifdef D_IPHONE
	void *mWordsWin;
#endif // D_IPHONE

#ifdef D_MFC
	class CWordsDlg *mWordsWin;
#endif // D_MFC

	//////// パブリック・メンバー関数 ////////
public:

	GuiWords();
	~GuiWords();
	void init();
	void destroy();

	void draw( const char *name, const char *str, long w = -1 );
	void redraw();
	void wipe();

	void okClicked();

	//////// プライベート・メンバー関数 ////////
private:

	void newWin();
};

#endif /* GUI_WORDS_H */
