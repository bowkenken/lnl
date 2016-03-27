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
* $Id: GuiClassEdit.h,v 1.10 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_CLASS_EDIT_H
#define GUI_CLASS_EDIT_H

////////////////////////////////////////////////////////////////
// ���饹�����ǥ�����������ɥ�
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
