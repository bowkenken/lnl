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
* $Id: GameThread.cpp,v 1.17 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#if defined( D_MFC )
# include "xlnl-dows/stdafx.h"
#elif defined( D_DOWS )
# ifndef	_WINDOWS_
#  include	<windows.h>
# endif
#else // D_DOWS
# include <pthread.h>
#endif // D_DOWS

////////////////////////////////////////////////////////////////

#include "GameThread.h"

static void *(*gGameFunc)( void * ) = NULL;

#ifdef D_MFC
static CWinThread *thread = NULL;
#endif // D_MFC

////////////////////////////////////////////////////////////////
// MS-Windows 用のラッパー
////////////////////////////////////////////////////////////////

#if defined( D_MFC )

UINT __cdecl GameThread( LPVOID pParam )
{
	if( gGameFunc != NULL )
		gGameFunc( NULL );

	return 0;
}

#elif defined( D_DOWS )

DWORD WINAPI GameThread( void *arg )
{
	if( gGameFunc != NULL )
		gGameFunc( NULL );

	return 0;
}

#endif

////////////////////////////////////////////////////////////////
// スレッドを切る
// void *(*func)( void * ) : スレッドのエントリー関数
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GameThreadCreate( void *(*func)( void * ) )
{
	gGameFunc = func;

#if defined( D_MFC )
	thread = ::AfxBeginThread(
			(AFX_THREADPROC)GameThread, (LPVOID)NULL );
#elif defined( D_DOWS )
# if 0
	unsigned dmy = 0;
	int id = _beginthreadex( NULL, 0, func, (void *)1, 0, &dmy );
	if( id == 0 )
		return false;
# else
	DWORD id = 0;
	HANDLE status = CreateThread( NULL, 0, GameThread, NULL, 0, &id );
	if( status == FALSE )
		return false;
# endif
#else
	pthread_t id;
	int status = pthread_create( &id, NULL, func, (void *)NULL );
	if( status != 0 )
		return false;

	pthread_detach( id );
#endif

	return true;
}

////////////////////////////////////////////////////////////////
// スレッドを終了
// void *(*func)( void * ) : スレッドのエントリー関数
// long code : 終了コード
// return : エラーが無かったか？
////////////////////////////////////////////////////////////////

bool GameThreadExit( void *(*func)( void * ), long code )
{
	if( gGameFunc != func )
		return false;

#if defined( D_MFC )
	if( thread != NULL ){
		TRY {
			::AfxEndThread( (UINT)code, true );
		} CATCH( CException, e ){
		} END_CATCH

//@@@		delete thread;
		thread = NULL;
	}
#elif defined( D_DOWS )
	ExitThread( (DWORD)code );
#else
	pthread_exit( (void *)code );
#endif

	return true;
}
