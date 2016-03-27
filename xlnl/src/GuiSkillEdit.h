/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ����ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�����
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�����ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ����Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: GuiSkillEdit.h,v 1.10 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_SKILL_EDIT_H
#define GUI_SKILL_EDIT_H

////////////////////////////////////////////////////////////////
// �����롦���ǥ�����������ɥ�
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
