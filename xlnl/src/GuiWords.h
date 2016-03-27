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
* $Id: GuiWords.h,v 1.10 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_WORDS_H
#define GUI_WORDS_H	1

////////////////////////////////////////////////////////////////
// ��쥦����ɥ�
////////////////////////////////////////////////////////////////

class GuiWords {

	//////// �ץ饤�١��ȡ����С��ѿ� ////////
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

	//////// �ѥ֥�å������С��ѿ� ////////
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

	//////// �ѥ֥�å������С��ؿ� ////////
public:

	GuiWords();
	~GuiWords();
	void init();
	void destroy();

	void draw( const char *name, const char *str, long w = -1 );
	void redraw();
	void wipe();

	void okClicked();

	//////// �ץ饤�١��ȡ����С��ؿ� ////////
private:

	void newWin();
};

#endif /* GUI_WORDS_H */
