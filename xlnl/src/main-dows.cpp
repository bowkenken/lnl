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
* $Id: main-dows.cpp,v 1.41 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// MS-Windows �ѤΥᥤ�����
////////////////////////////////////////////////////////////////

#define	MAIN_DOWS_CPP
#include	"inc.h"

extern "C" {
	int PASCAL WinMain( HINSTANCE, HINSTANCE, LPSTR, int );
};

static void	*(*g_main_thread_ptr)( void *p ) = NULL;

////////////////////////////////////////////////////////////////
// �ᥤ�󡦥롼����
// int argc : �����ο�
// char **argv : �����Υꥹ��
// return : ��λ������
////////////////////////////////////////////////////////////////

int	main_dows( int argc, char **argv )
{
	g_main_thread_ptr = NULL;

	init_arg();

	g_flg_gui = TRUE;

#if	defined( NDEBUG )
	g_flg_cui = FALSE;
#elif	defined( DEBUG )
	g_flg_cui = TRUE;
#else
	g_flg_cui = FALSE;
#endif
	g_flg_cui = FALSE;

	chk_arg( argc, argv );

	if( g_flg_cui ){
		::AllocConsole();
		freopen( "CONIN$", "r", stdin );
		freopen( "CONOUT$", "w", stdout );
		freopen( "CONOUT$", "w", stderr );
	}

	init_game();
	change_scene_gui( SCENE_N_INIT );

	theApp.InitWin();

	if( g_flg_gui ){
		if( !g_Dir3d.CreateDevices(
				theApp.m_pMainFrm->GetViewWnd() ) ){
			exit_game( EXIT_FAILURE );
		}

		gMusic.init();
		gSound.init();
		gJoystick.init();

		// �����ȥ����������

		gPcgDun.initTitle();
		change_scene_gui( SCENE_N_TITLE );
		gPcgDun.drawTitle();

		// ����ե��å����������

		gSelConf.init();
		gSelConf.draw();
	}

	return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////
// ����ե��å�����������ν����
////////////////////////////////////////////////////////////////

void	init_main_sel_conf( void *cnf )
{
	// �Ƽ�����

	gPcgDun.init( (GraphConf *)cnf );

	change_scene_gui( SCENE_N_TOWN );

	gGuiMenu.init();
	gGuiMessage.init();
	gGuiStat.init();
	gKey.init();
	initMouseMotionFunc();

	gFlagInitMfcDone = true;

	if( !call_game_thread_create( main_thread ) )
		exit_game( EXIT_FAILURE );
}

////////////////////////////////////////////////////////////////
// �����ཪλ���ν���
////////////////////////////////////////////////////////////////

void	closeGameGui()
{
	if( g_flg_cui )
		gCuiMouse.close();

	gSound.close();
	gMusic.close();
}

////////////////////////////////////////////////////////////////
// ���ơ��������С��˥���������֤Υҥ�Ȥ�ɽ��
////////////////////////////////////////////////////////////////

void	guiMapPrintStatBarHint( void )
{
	pos_t *crsr = get_main_crsr();
	if( crsr == NULL )
		return;

	printMapStatBar( "%s    %s",
			get_str_map_hint_obj( crsr->x, crsr->y ),
			get_str_map_hint_chr( crsr->x, crsr->y ) );
}

////////////////////////////////////////////////////////////////
// ���ơ��������С��˥�å�������ɽ��
// const char *s : �ե����ޥå�ʸ����
// ... : �ղð���
////////////////////////////////////////////////////////////////

void	printMapStatBar( const char *s, ... )
{
	static char	str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;
	va_list	argptr;

	va_start( argptr, s );
	vsn_printf( str, max_len, s, argptr );
	va_end( argptr );

	if( theApp.m_pMainFrm == NULL )
		return;

	if( g_flg_init ){
		CStatusBar &bar = theApp.m_pMainFrm->GetStatusBar();
		bar.SetWindowText( str );
	}
}

////////////////////////////////////////////////////////////////
// ��λ����
// long code : ��λ������
////////////////////////////////////////////////////////////////

void	gexit( long code )
{
	if( gFlagExit )
		return;
	else
		gFlagExit = true;

	closeGameGui();

	theApp.m_pMainFrm->PostMessage(
			WM_CLOSE, (WPARAM)code, (LPARAM)code );

	if( g_main_thread_ptr != NULL )
		call_game_thread_exit( g_main_thread_ptr, code );
}

////////////////////////////////////////////////////////////////
// �ᥤ�󡦥���å�
// void *p : ����
// return : ����
////////////////////////////////////////////////////////////////

void	*main_thread( void *p )
{
	g_main_thread_ptr = main_thread;

	game_main();

	return NULL;
}

////////////////////////////////////////////////////////////////
// ����ȥ꡼���롼����
// �ץ������ȤΥץ�ѥƥ�-���-�����ƥ�-���֥����ƥ��
// ���󥽡�������ꤷ�����ˤ�Ф�롣
// int argc : �����ο�
// char **argv : �����Υꥹ��
// return : ��λ������
////////////////////////////////////////////////////////////////

int	main( int argc, char **argv )
{
	HINSTANCE mod = (HINSTANCE)GetModuleHandle( NULL );

	return WinMain( mod, NULL, GetCommandLine(), SW_SHOWNORMAL );
}
