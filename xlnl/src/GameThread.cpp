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
// MS-Windows �ѤΥ�åѡ�
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
// ����åɤ��ڤ�
// void *(*func)( void * ) : ����åɤΥ���ȥ꡼�ؿ�
// return : ���顼��̵���ä�����
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
// ����åɤ�λ
// void *(*func)( void * ) : ����åɤΥ���ȥ꡼�ؿ�
// long code : ��λ������
// return : ���顼��̵���ä�����
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
