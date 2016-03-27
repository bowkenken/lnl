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
* $Id: main-x.c,v 1.14 2014/01/07 23:57:24 bowkenken Exp $
***************************************************************/

/***************************************************************
* X-Window 用のメイン処理
***************************************************************/

#define	MAIN_X_C
#include	"inc.h"

void	*(*g_main_thread_ptr)( void * );

/***************************************************************
* メイン・ルーチン
* int argc : 引数の数
* char **argv : 引数のリスト
* return : 終了コード
***************************************************************/

int	main_ws( int argc, char **argv )
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

	chk_arg( argc, argv );
	init_game();

	if( !call_game_thread_create( main_thread ) )
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

/***************************************************************
* 終了処理
* long code : 終了コード
***************************************************************/

void	gexit( long code )
{
#ifdef	D_GTK
	gtk_exit( code );
#else	/* D_GTK */
	exit( code );
#endif	/* D_GTK */
}

/***************************************************************
* メイン・スレッド
* void *p : 引数
* return : 不明
***************************************************************/

void	*main_thread( void *p )
{
	g_main_thread_ptr = main_thread;

	game_main();

	return NULL;
}
