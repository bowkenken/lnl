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
* $Id: main-dows.cpp,v 1.41 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// MS-Windows 用のメイン処理
////////////////////////////////////////////////////////////////

#define	MAIN_DOWS_CPP
#include	"inc.h"

extern "C" {
	int PASCAL WinMain( HINSTANCE, HINSTANCE, LPSTR, int );
};

static void	*(*g_main_thread_ptr)( void *p ) = NULL;

////////////////////////////////////////////////////////////////
// メイン・ルーチン
// int argc : 引数の数
// char **argv : 引数のリスト
// return : 終了コード
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

		// タイトル画像を描画

		gPcgDun.initTitle();
		change_scene_gui( SCENE_N_TITLE );
		gPcgDun.drawTitle();

		// グラフィック設定を選択

		gSelConf.init();
		gSelConf.draw();
	}

	return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////
// グラフィック設定の選択後の初期化
////////////////////////////////////////////////////////////////

void	init_main_sel_conf( void *cnf )
{
	// 各種初期化

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
// ゲーム終了前の処理
////////////////////////////////////////////////////////////////

void	closeGameGui()
{
	if( g_flg_cui )
		gCuiMouse.close();

	gSound.close();
	gMusic.close();
}

////////////////////////////////////////////////////////////////
// ステータス・バーにカーソル位置のヒントを表示
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
// ステータス・バーにメッセージを表示
// const char *s : フォーマット文字列
// ... : 付加引数
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
// 終了処理
// long code : 終了コード
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
// メイン・スレッド
// void *p : 引数
// return : 不明
////////////////////////////////////////////////////////////////

void	*main_thread( void *p )
{
	g_main_thread_ptr = main_thread;

	game_main();

	return NULL;
}

////////////////////////////////////////////////////////////////
// エントリー・ルーチン
// プロジェクトのプロパティ-リンク-システム-サブシステムを
// コンソールに設定した場合によばれる。
// int argc : 引数の数
// char **argv : 引数のリスト
// return : 終了コード
////////////////////////////////////////////////////////////////

int	main( int argc, char **argv )
{
	HINSTANCE mod = (HINSTANCE)GetModuleHandle( NULL );

	return WinMain( mod, NULL, GetCommandLine(), SW_SHOWNORMAL );
}
