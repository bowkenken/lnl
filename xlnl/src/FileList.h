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
* $Id: FileList.h,v 1.31 2014/03/15 01:49:46 bowkenken Exp $
***************************************************************/

#ifndef FILE_LIST_H
#define FILE_LIST_H	1

#if HAVE_UNISTD_H
# include <unistd.h>
#endif // HAVE_UNISTD_H

#include <stdlib.h>
#include <stdio.h>

#if defined( D_WS ) \
	|| defined( D_GTK ) \
	|| defined( D_MAC) \
	|| defined( D_IPHONE )
# include <dirent.h>
# include <sys/stat.h>
#endif

#ifdef D_WS
# include <WSCstring.h>
#endif // D_WS

#ifdef D_GTK
# include "GtkWSCstring.h"
#endif // D_GTK

#ifdef D_MAC
# include "MacWSCstring.h"
#endif // D_MAC

#ifdef D_IPHONE
# include "IPhoneWSCstring.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "MfcWSCstring.h"
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ���ꤵ�줿��ĥ�ҤΥե�����򸡺�����
// ���Ĥ���ʤ��ä��顢�ǥ��쥯�ȥ곬�ؤ���ǥ��쥯�ȥ�
// �ޤǡ������Τܤ�
////////////////////////////////////////////////////////////////

#if	defined( D_DOS ) || defined( D_MFC )
# define	STR_DIR_BASE	"_lnl/xlnl/"
#else
# define	STR_DIR_BASE	".lnl/xlnl/"
#endif

#define	STR_DIR_BASE_GRAPH	STR_DIR_BASE "graph/"

static WSCstring sDirBaseSelGraph = "default/";

class FileList {
public:

private:
	// ���ǥ��쥯�ȥ�
	WSCstring sDirBase;
	// ���ǥ��쥯�ȥ꤫������Хѥ�
	WSCstring sDirSub;
	// �ե�ѥ�
	WSCstring sDirFullPath;

	// ��ĥ�ҤΥꥹ�ȡ����ڡ����Ƕ��ڤ�
	WSCstring sExt;

	// ���ĤǤ�ե����뤬���Ĥ��ä�����
	// ���Ĥ��ä���ǥ��쥯�ȥ�Ϥ����Τܤ�ʤ�
	bool bFlagExist;

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

public:
	FileList();
	~FileList();

	bool reset( WSCstring dir, WSCstring ext );
	WSCstring next();

	WSCstring getBaseDir();

	static WSCstring setStrDirSelGraph( WSCstring dir );
	static WSCstring setStrDirSelMusic( WSCstring dir );
	static WSCstring setStrDirSelSound( WSCstring dir );

	static WSCstring jointDir(
		WSCstring dir1, WSCstring dir2 );
	static WSCstring getFileName( WSCstring path );
	static WSCstring getExt( WSCstring name );

private:
	WSCstring nextNode();
};

#endif /* FILE_LIST_H */
