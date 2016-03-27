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
* $Id: FileList.cpp,v 1.27 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#ifdef D_WS
# include <WSDenv.h>
#endif //D_WS

#include "spell.h"
#include "menu.h"
#include "amenu.h"

#include "FileList.h"

#include "draw.h"
#include "town.h"
#include "gfile.h"
#include "play-rep.h"
#include "draw-prot.h"
#include "gfile-prot.h"
#include "play-rep-prot.h"

////////////////////////////////////////////////////////////////
// ファイル検索のコンストラクタ
////////////////////////////////////////////////////////////////

FileList::FileList()
{
	sDirBase = "";
	sDirSub = "";
	sDirFullPath = "";
	sExt = "";
	bFlagExist = false;

#ifdef D_MFC
	bFlagUseWin32ApiFind = true;
	bFlagOpen = false;
#else // D_MFC
	dpFile = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ファイル検索のデストラクタ
////////////////////////////////////////////////////////////////

FileList::~FileList()
{
#ifndef D_MFC
	if( dpFile != NULL ){
		closedir( dpFile );
		dpFile = NULL;
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 検索のリセット
// WSCstring dirSub : 基準からの相対パス
// WSCstring ext : 拡張子のリスト
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool FileList::reset( WSCstring dirSub, WSCstring ext )
{
#ifdef D_MFC
	if( bFlagOpen ){
		if( bFlagUseWin32ApiFind )
			::FindClose( hFindFile );
		else
			finder.Close();

		bFlagOpen = false;
	}
#else // D_MFC
	if( dpFile != NULL ){
		closedir( dpFile );
		dpFile = NULL;
	}
#endif // D_MFC

	sDirBase = jointDir( getBaseDir(), "" );
	sDirSub = jointDir( dirSub, "" );
	sDirFullPath = jointDir( sDirBase, sDirSub );

	make_dir( sDirFullPath );

	sExt = ext;
	bFlagExist = false;

#ifdef D_MFC
	WSCstring path = jointDir( sDirFullPath, "*.*" );
	path.replaceString( "/", "\\", 0 );

	if( bFlagUseWin32ApiFind ){
		ZeroMemory( &findData, sizeof( findData ) );
		hFindFile = ::FindFirstFile( path, &findData );
		if( hFindFile == INVALID_HANDLE_VALUE )
			return false;

		findData.dwFileAttributes = 0
				| FILE_ATTRIBUTE_ARCHIVE
				| FILE_ATTRIBUTE_COMPRESSED
				| FILE_ATTRIBUTE_READONLY
				;
	} else {
		if( !finder.FindFile( path ) )
			return false;

# if 0
//@@@
		finder.MatchesMask( 0
				| FILE_ATTRIBUTE_ARCHIVE
				| FILE_ATTRIBUTE_COMPRESSED
				| FILE_ATTRIBUTE_READONLY
		);
# endif
	}

	bFlagOpen = true;
#else // D_MFC
	dpFile = opendir( sDirFullPath );
	if( dpFile == NULL )
		return false;
#endif // D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// 次のファイルを検索
// 見つからなかったらディレクトリをさかのぼる
// return : 見つかったファイルの絶対パス
////////////////////////////////////////////////////////////////

WSCstring FileList::next()
{
	for( long i = 0; i < LOOP_MAX_100; i++ ){
		WSCstring path = nextNode();

		if( path.getChars() > 0 )
			return path;
		if( bFlagExist )
			return "";

		// ディレクトリを根に向かって遡る

		for( long j = 0; j < LOOP_MAX_100; j++ ){
			long nWords = sDirSub.getWords( "/" );
			if( nWords <= 1 )
				return "";

			long nPos = sDirSub.getWordCharPos( nWords - 2, "/" );
			if( nPos > -1 )
				sDirSub.cutString( nPos );
			if( reset( sDirSub, sExt ) )
				break;
		}
	}

	return "";
}

////////////////////////////////////////////////////////////////
// 次のファイルを検索
// return : 見つかったファイルの絶対パス
////////////////////////////////////////////////////////////////

WSCstring FileList::nextNode()
{
#ifdef D_MFC
	if( !bFlagOpen )
		return "";
#else // D_MFC
	if( dpFile == NULL )
		return "";
#endif // D_MFC

	while( 1 ){
#ifdef D_MFC
		WSCstring name;

		if( bFlagUseWin32ApiFind ){
			if( !::FindNextFile( hFindFile, &findData ) )
				break;

			if( findData.dwFileAttributes
					& (FILE_ATTRIBUTE_DIRECTORY) ){
				continue;
			}

			name = jointDir( sDirFullPath,
					findData.cFileName );
		} else {
			if( !finder.FindNextFile() )
				break;

			if( finder.IsDirectory() )
				continue;

			name = finder.GetFilePath();
		}
		name.replaceString( "\\", "/", 0 );
#else // D_MFC
		struct dirent *buf = readdir( dpFile );
		if( buf == NULL )
			break;

		WSCstring fileName = buf->d_name;
# ifdef D_DOWS
		fileName.replaceString( "\\", "/", 0 );
# endif // D_DOWS
		WSCstring name = jointDir( sDirFullPath, fileName );

		struct stat statBuf;
		stat( name, &statBuf );
		if( S_ISDIR( statBuf.st_mode ) )
			continue;
#endif // D_MFC

		WSCstring ext = getExt( name );
		long nExtMaxN = sExt.getWords();
		for( long i = 0; i < nExtMaxN; i++ ){
			WSCstring curExt = sExt.getWord( i, " " );

			if( curExt == ext ){
				bFlagExist = true;
				return name;
			}
		}
	}

#ifdef D_MFC
	if( bFlagUseWin32ApiFind )
		::FindClose( hFindFile );
	else
		finder.Close();

	bFlagOpen = false;
#endif // D_MFC

	return "";
}

////////////////////////////////////////////////////////////////
// 基準ディレクトリを返す
// return : 基準ディレクトリ
////////////////////////////////////////////////////////////////

WSCstring FileList::getBaseDir()
{
	WSCstring dir = jointDir( get_home_dir(), STR_DIR_BASE );
	dir = jointDir( dir, sDirBaseSelGraph );

	return dir;
}

////////////////////////////////////////////////////////////////
// 基準ディレクトリを設定する (画像)
// WSCstring dir : 基準ディレクトリ
// return : 基準ディレクトリ
////////////////////////////////////////////////////////////////

WSCstring FileList::setStrDirSelGraph( WSCstring dir )
{
	sDirBaseSelGraph = jointDir( "graph/", dir );

	return sDirBaseSelGraph;
}

////////////////////////////////////////////////////////////////
// 基準ディレクトリを設定する (BGM)
// WSCstring dir : 基準ディレクトリ
// return : 基準ディレクトリ
////////////////////////////////////////////////////////////////

WSCstring FileList::setStrDirSelMusic( WSCstring dir )
{
	sDirBaseSelGraph = jointDir( "music/", dir );

	return sDirBaseSelGraph;
}

////////////////////////////////////////////////////////////////
// 基準ディレクトリを設定する (SE)
// WSCstring dir : 基準ディレクトリ
// return : 基準ディレクトリ
////////////////////////////////////////////////////////////////

WSCstring FileList::setStrDirSelSound( WSCstring dir )
{
	sDirBaseSelGraph = jointDir( "sound/", dir );

	return sDirBaseSelGraph;
}

////////////////////////////////////////////////////////////////
// ディレクトリどうしを "/" を補間して連結する
// WSCstring dir1 : ディレクトリ名
// WSCstring dir2 : ディレクトリ名
// return : 補間後のディレクトリ名
////////////////////////////////////////////////////////////////

WSCstring FileList::jointDir(
	WSCstring dir1, WSCstring dir2 )
{
	const WSCstring sSlash = "/";

	int n = dir1.getChars() - 1;
	if( n < 0 )
		return( dir2 );

	if( dir1[n] == '/' )
		return( dir1 + dir2 );
	else
		return( dir1 + sSlash + dir2 );
}

////////////////////////////////////////////////////////////////
// パス名からファイル名を切り出す
// WSCstring path : パス名
// return : ファイル名
////////////////////////////////////////////////////////////////

WSCstring FileList::getFileName( WSCstring path )
{
	long w = path.getWords( "/" );
	WSCstring name = path.getWord( w - 1, "/" );

	return name;
}

////////////////////////////////////////////////////////////////
// ファイル名の拡張子部分を返す
// WSCstring name : ファイル名
// return : 拡張子
////////////////////////////////////////////////////////////////

WSCstring FileList::getExt( WSCstring name )
{
	for( long i = name.getChars() - 1; i >= 0; i-- ){
		if( name[i] == '.' ){
			name.deleteChars( 0, i + 1 );

			return name;
		}
	}

	return "";
}
