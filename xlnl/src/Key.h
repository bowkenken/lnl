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
* $Id: Key.h,v 1.21 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef KEY_H
#define KEY_H	1

#ifdef D_WS
# include <WSCstring.h>
# include <WSDkeyboard.h>
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
# include <gdk/gdk.h>
# include <gdk/gdkkeysyms.h>
# include "GtkMisc.h"
# include "GtkWSCstring.h"
#endif // D_GTK

#ifdef D_MAC
# include "MacMisc.h"
# include "MacWSCstring.h"
#endif // D_MAC

#ifdef D_IPHONE
# include "IPhoneMisc.h"
# include "IPhoneWSCstring.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////
// �������Ϥδ���
////////////////////////////////////////////////////////////////

class Key {
public:

private:
	// �������ϥХåե�
	WSCstring buf;

public:
	Key()
	{
	}
	~Key()
	{
	}

	void init();

	long getChar();

	void setChar( long c, bool flagMacro = false,
		bool flagCheckClear = false );
	void setString( WSCstring s, bool flagMacro = false,
		bool flagCheckClear = false );
	void setStringKeyTab( WSCstring s, bool flagMacro );

	bool chkBuf();

	bool moveCrsrRel( long mapX, long mapY );
	bool moveCrsrAbs( long mapX, long mapY );
	void checkMoveCrsr();
	bool scrollRel( long mapX, long mapY );
	bool scrollAbs( long mapX, long mapY );
	void checkScroll();

#ifdef D_MFC
	void handleKeyDown(
		UINT nChar, UINT nRepCnt, UINT nFlags
	);
#endif // D_MFC
};

#ifdef D_GTK
gboolean handleKeyPress(
	GtkWidget *widget,
	GdkEventKey *event,
	gpointer user_data
);
#endif // D_GTK

#endif /* KEY_H */
