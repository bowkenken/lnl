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
* $Id: GuiClassEdit.h,v 1.10 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_CLASS_EDIT_H
#define GUI_CLASS_EDIT_H

////////////////////////////////////////////////////////////////
// クラス・エディタ・ウィンドウ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////

class GuiClassEdit {

private:
	class_t *classData;

#ifdef D_GTK
	GtkWidget *mEntryName;

	GtkWidget *mLabelAbl[ABL_KIND_MAX_N];
	GtkWidget *mLabelValue[ABL_KIND_MAX_N];
	GtkWidget *mButtonPlus[ABL_KIND_MAX_N];
	GtkWidget *mButtonMinus[ABL_KIND_MAX_N];

	GtkWidget *mLabelTotal;
	GtkWidget *mLabelTotalValue;

	GtkWidget *mButtonExit;
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

public:
#ifdef D_WS
	void *mClassEditWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mClassEditWin;
#endif // D_GTK
	
#ifdef D_MAC
//@@@
	void *mClassEditWin;
#endif // D_MAC
	
#ifdef D_IPHONE
//@@@
	void *mClassEditWin;
#endif // D_IPHONE
	
#ifdef D_MFC
	class CClassEditDlg *mClassEditWin;
#endif // D_MFC

public:
	GuiClassEdit();
	~GuiClassEdit();
	void init();
	void destroy();

	void draw( class_t *p );
	void redraw();
	void wipe();

	void	setClassName();

	void plusClicked( abl_kind_t kind );
	void minusClicked( abl_kind_t kind );
	void exitClicked();
private:
	void newWin();
	void add( abl_kind_t kind, long n );
};

#endif // GUI_CLASS_EDIT_H
