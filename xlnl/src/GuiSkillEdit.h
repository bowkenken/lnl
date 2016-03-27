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
* $Id: GuiSkillEdit.h,v 1.10 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_SKILL_EDIT_H
#define GUI_SKILL_EDIT_H

////////////////////////////////////////////////////////////////
// スキル・エディタ・ウィンドウ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////

class GuiSkillEdit {

private:

#ifdef D_GTK
	GtkWidget *mEntryName;

	GtkWidget *mButtonSkill[SKILL_MAX_N];
	GtkWidget *mLabelRate[SKILL_MAX_N];

	GtkWidget *mLabelHint;

	GtkWidget *mButtonPrev;
	GtkWidget *mButtonNext;
	GtkWidget *mButtonExit;
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

public:
	class_t *classData;

#ifdef D_WS
	void *mSkillEditWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mSkillEditWin;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mSkillEditWin;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	void *mSkillEditWin;
#endif // D_IPHONE

#ifdef D_MFC
	class CSkillEditDlg *mSkillEditWin;
#endif // D_MFC

public:
	GuiSkillEdit();
	~GuiSkillEdit();
	void init();
	void destroy();

	void draw( class_t *p );
	void redraw();
	void wipe();

	void	setClassName();

	void skillClicked( long nSlot );
	void prevClicked();
	void nextClicked();
	void exitClicked();

private:
	void newWin();
};

#endif // GUI_SKILL_EDIT_H
