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
* $Id: SelConf.h,v 1.17 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef SEL_CONF_H
#define SEL_CONF_H	1

////////////////////////////////////////////////////////////////
// グラフィック設定の選択
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

	// プライベート・メンバー変数
private:

	GraphConf mGraphConfHead;
	GraphConf *pGraphConfCur;

	WSCstring sDir;
	WSCstring sDirName;
#ifdef D_MFC
	// ファイル・サーチ

	bool bFlagUseWin32ApiFind;

	WIN32_FIND_DATA findData;
	HANDLE hFindFile;

	CFileFind finder;

	bool bFlagOpen;
#else // D_MFC
	// サーチ中のディレクトリ
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

	// パブリック・メンバー変数
public:

#ifdef D_GTK
	GtkWidget *mSelConfWin;
#endif // D_GTK

#ifdef D_MFC
	CSelConfDlg mDlg;
#endif // D_MFC

	GraphConf *pGraphConfSel;

	// パブリック・メンバー関数
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

	// プライベート・メンバー関数
private:

	void newWin();

	void makeList();

	bool openDir();
	bool closeDir();
	WSCstring nextDir();
};

#endif /* SEL_CONF_H */
