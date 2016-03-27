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
* $Id: GuiInputString.h,v 1.18 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_INPUT_STRING_H
#define GUI_INPUT_STRING_H	1

////////////////////////////////////////////////////////////////
// ʸ�������ϡ�������ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/InputLineDlg.h"
#endif // D_MFC

class GuiInputString {

	//////// �ץ饤�١��ȡ����С��ѿ� ////////
private:

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mTitle;
#endif // D_GTK

	//////// �ѥ֥�å������С��ѿ� ////////
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

	//////// �ѥ֥�å������С��ؿ� ////////
public:

	GuiInputString();
	~GuiInputString();
	void init();
	void destroy();

	void draw( const char *ttl, const char *str, long len );
	void wipe();

	//////// �ץ饤�١��ȡ����С��ؿ� ////////
private:

	void newWin();
};

#endif /* GUI_INPUT_STRING_H */
