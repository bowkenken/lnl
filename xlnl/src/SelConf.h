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
* $Id: SelConf.h,v 1.17 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef SEL_CONF_H
#define SEL_CONF_H	1

////////////////////////////////////////////////////////////////
// ����ե��å����������
////////////////////////////////////////////////////////////////

#if HAVE_UNISTD_H
# include <unistd.h>
#endif // HAVE_UNISTD_H

#include <stdlib.h>
#include <stdio.h>

#if defined( D_WS ) \
	|| defined( D_GTK ) \
	|| defined( D_MAC ) \
	|| defined( D_IPHONE )
# include <dirent.h>
# include <sys/stat.h>
#endif

#ifdef D_WS
# include <WSCvbtn.h>
# include <WSCstring.h>
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GtkWSCstring.h"
#endif // D_GTK

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/SelConfDlg.h"
# include "MfcWSCstring.h"
#endif // D_GTK

#include	"GraphConfToken.h"
#include	"GraphConf.h"

////////////////////////////////////////////////////////////////

#define STR_WORD_SEP_SEL_CONF	" : "

////////////////////////////////////////////////////////////////

class SelConf {

	// �ץ饤�١��ȡ����С��ѿ�
private:

	GraphConf mGraphConfHead;
	GraphConf *pGraphConfCur;

	WSCstring sDir;
	WSCstring sDirName;
#ifdef D_MFC
	// �ե����롦������

	bool bFlagUseWin32ApiFind;

	WIN32_FIND_DATA findData;
	HANDLE hFindFile;

	CFileFind finder;

	bool bFlagOpen;
#else // D_MFC
	// ��������Υǥ��쥯�ȥ�
	DIR *dpFile;
#endif // D_MFC

#ifdef D_GTK
	GtkWidget *vBox;
	GtkWidget *hBox;
	GtkWidget *labelList;
	GtkWidget *scrollWin;
	GtkWidget *lsList;
	GtkWidget *btnSelConfOk;
	GtkWidget *btnSelConfCancel;
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

	// �ѥ֥�å������С��ѿ�
public:

#ifdef D_GTK
	GtkWidget *mSelConfWin;
#endif // D_GTK

#ifdef D_MFC
	CSelConfDlg mDlg;
#endif // D_MFC

	GraphConf *pGraphConfSel;

	// �ѥ֥�å������С��ؿ�
public:

	SelConf();
	~SelConf();

	void init();
	void destroy();

	void draw();
	void wipe();

	void setListGui();

	void select( long n );

	bool evalBlockBegin();
	bool evalBlockEnd();
	bool evalSetNum( GraphConfToken token, long n );
	bool evalSetStr( GraphConfToken token, WSCstring str );

	// �ץ饤�١��ȡ����С��ؿ�
private:

	void newWin();

	void makeList();

	bool openDir();
	bool closeDir();
	WSCstring nextDir();
};

#endif /* SEL_CONF_H */
