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
* $Id: WinPos.h,v 1.8 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef WIN_POS_H
#define WIN_POS_H

////////////////////////////////////////////////////////////////
// ������ɥ��κ�ɸ�ȥ������δ���
////////////////////////////////////////////////////////////////

#include "win-kind.h"

#ifdef D_WS
#endif //D_WS

#ifdef D_GTK
#include "gtk/gtk.h"
#endif //D_GTK

#ifdef D_MFC
#endif //D_MFC

class WinPos {

private:
	bool flagDraw;
	long mX, mY, mW, mH;

public:
	WinPos();
	~WinPos();

	void *getWin( win_kind_t kind );

	void set(
		win_kind_t kind,
		long *px, long *py,
		long *pw, long *ph );
	void get(
		win_kind_t kind,
		long *px, long *py,
		long *pw, long *ph );

	void calc( win_kind_t kind );

	void draw( win_kind_t kind, bool flagDlg = false );
	void wipe( win_kind_t kind, bool flagDlg = false );
};

#endif // WIN_POS_H
