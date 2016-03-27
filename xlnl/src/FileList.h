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
// 指定された拡張子のファイルを検索する
// 見つからなかったら、ディレクトリ階層を基準ディレクトリ
// まで、さかのぼる
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
	// 基準ディレクトリ
	WSCstring sDirBase;
	// 基準ディレクトリからの相対パス
	WSCstring sDirSub;
	// フルパス
	WSCstring sDirFullPath;

	// 拡張子のリスト。スペースで区切る
	WSCstring sExt;

	// １つでもファイルが見つかったか？
	// 見つかったらディレクトリはさかのぼらない
	bool bFlagExist;

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
