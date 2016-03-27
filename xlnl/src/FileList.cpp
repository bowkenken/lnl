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
// �ե����븡���Υ��󥹥ȥ饯��
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
// �ե����븡���Υǥ��ȥ饯��
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
// �����Υꥻ�å�
// WSCstring dirSub : ��फ������Хѥ�
// WSCstring ext : ��ĥ�ҤΥꥹ��
// return : ���顼��̵���ä�����
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
// ���Υե�����򸡺�
// ���Ĥ���ʤ��ä���ǥ��쥯�ȥ�򤵤��Τܤ�
// return : ���Ĥ��ä��ե���������Хѥ�
////////////////////////////////////////////////////////////////

WSCstring FileList::next()
{
	for( long i = 0; i < LOOP_MAX_100; i++ ){
		WSCstring path = nextNode();

		if( path.getChars() > 0 )
			return path;
		if( bFlagExist )
			return "";

		// �ǥ��쥯�ȥ�򺬤˸����ä��̤�

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
// ���Υե�����򸡺�
// return : ���Ĥ��ä��ե���������Хѥ�
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
// ���ǥ��쥯�ȥ���֤�
// return : ���ǥ��쥯�ȥ�
////////////////////////////////////////////////////////////////

WSCstring FileList::getBaseDir()
{
	WSCstring dir = jointDir( get_home_dir(), STR_DIR_BASE );
	dir = jointDir( dir, sDirBaseSelGraph );

	return dir;
}

////////////////////////////////////////////////////////////////
// ���ǥ��쥯�ȥ�����ꤹ�� (����)
// WSCstring dir : ���ǥ��쥯�ȥ�
// return : ���ǥ��쥯�ȥ�
////////////////////////////////////////////////////////////////

WSCstring FileList::setStrDirSelGraph( WSCstring dir )
{
	sDirBaseSelGraph = jointDir( "graph/", dir );

	return sDirBaseSelGraph;
}

////////////////////////////////////////////////////////////////
// ���ǥ��쥯�ȥ�����ꤹ�� (BGM)
// WSCstring dir : ���ǥ��쥯�ȥ�
// return : ���ǥ��쥯�ȥ�
////////////////////////////////////////////////////////////////

WSCstring FileList::setStrDirSelMusic( WSCstring dir )
{
	sDirBaseSelGraph = jointDir( "music/", dir );

	return sDirBaseSelGraph;
}

////////////////////////////////////////////////////////////////
// ���ǥ��쥯�ȥ�����ꤹ�� (SE)
// WSCstring dir : ���ǥ��쥯�ȥ�
// return : ���ǥ��쥯�ȥ�
////////////////////////////////////////////////////////////////

WSCstring FileList::setStrDirSelSound( WSCstring dir )
{
	sDirBaseSelGraph = jointDir( "sound/", dir );

	return sDirBaseSelGraph;
}

////////////////////////////////////////////////////////////////
// �ǥ��쥯�ȥ�ɤ����� "/" ����֤���Ϣ�뤹��
// WSCstring dir1 : �ǥ��쥯�ȥ�̾
// WSCstring dir2 : �ǥ��쥯�ȥ�̾
// return : ��ָ�Υǥ��쥯�ȥ�̾
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
// �ѥ�̾����ե�����̾���ڤ�Ф�
// WSCstring path : �ѥ�̾
// return : �ե�����̾
////////////////////////////////////////////////////////////////

WSCstring FileList::getFileName( WSCstring path )
{
	long w = path.getWords( "/" );
	WSCstring name = path.getWord( w - 1, "/" );

	return name;
}

////////////////////////////////////////////////////////////////
// �ե�����̾�γ�ĥ����ʬ���֤�
// WSCstring name : �ե�����̾
// return : ��ĥ��
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
