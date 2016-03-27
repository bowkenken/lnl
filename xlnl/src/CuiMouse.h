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
* $Id: CuiMouse.h,v 1.9 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef CUI_MOUSE_H
#define CUI_MOUSE_H	1

////////////////////////////////////////////////////////////////
// ���󥽡��롦�ޥ���
////////////////////////////////////////////////////////////////

#include	<stdio.h>

#ifdef	HAVE_GLIB_H
# include	<glib.h>
#else
typedef	unsigned int guint;
#endif

#include	"menu.h"

////////////////////////////////////////////////////////////////
// �ϥ�ɥ顦�ơ��֥�
////////////////////////////////////////////////////////////////

#define	CUI_MOUSE_HANDLER_TAB_MAX_N	80

struct CuiMouseHandlerTab {
	// ͭ����̵���ե饰
	bool flagEnable;
	// ����å���ȿ������û��
	long x, y, w, h;
	// �ݥ���Ȼ��Υϥ�ɥ�
	bool_t (*funcPoint)( long btn, long n, const char *macro );
	// ����å����Υϥ�ɥ�
	bool_t (*funcClick)( long btn, long n, const char *macro );
	// ����������Υϥ�ɥ�
	bool_t (*funcScroll)( long btn, long n, const char *macro );
	// �ϥ�ɥ�ؤΰ��� (����)
	long argN;
	// �ϥ�ɥ�ؤΰ��� (�ޥ���)
	char argMacro[MACRO_MAX_LEN + 1];
};

////////////////////////////////////////////////////////////////

class CuiMouse {

// �ץ饤�١��ȡ����С��ѿ�
private:

	bool flagReset;
	bool flagEnable;
	bool flagTerm;
	bool flagNoButtonRight;
	bool flagSwapButtonMiddleAndRight;
	const char *envTerm;
	const char *termName;
	FILE *ttyFP;

	guint doubleClickTimer;
	bool flagDoubleClickTime;

	long handlerTabCurN;
	CuiMouseHandlerTab handlerTab[CUI_MOUSE_HANDLER_TAB_MAX_N];

// �ѥ֥�å������С��ѿ�
public:

// �ѥ֥�å������С��ؿ�
public:

	CuiMouse();
	~CuiMouse();
	void init();
	void close();

	long checkEvent( long c );
	long getCharX();
	long getCharY();

	void enableTimer();
	void disableTimer();
	long getDoubleClickMsec();
	void setDoubleClickMsec( long msec );

	void resetHandlerTab();
	long addHandler(
		bool flagEnable,
		long x, long y, long w, long h,
		bool_t (*funcPoint)( long btn, long n, const char *macro ),
		bool_t (*funcClick)( long btn, long n, const char *macro ),
		bool_t (*funcScroll)( long btn, long n, const char *macro ),
		long argN,
		const char *argMacro
	);
	bool checkCallHandler(
		long nBtn,
		long x, long y,
		bool flagPoint,
		bool flagClick = false,
		bool flagScroll = false
	);

// �ץ饤�١��ȡ����С��ؿ�
private:
};

#endif /* CUI_MOUSE_H */
