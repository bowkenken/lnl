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
* $Id: call.cpp,v 1.132 2014/03/15 00:50:40 bowkenken Exp $
***************************************************************/

#define	CALL_CPP
#include	"inc.h"

#ifdef D_WS
extern WSCwindow *StatWin;
#endif

#ifdef D_GTK
# ifdef HAVE_G_THREAD_INIT
static GStaticMutex	g_key_buf_mutex = G_STATIC_MUTEX_INIT;
# else // HAVE_G_THREAD_INIT
static GMutex	g_key_buf_mutex;
# endif // HAVE_G_THREAD_INIT
#endif // D_GTK

static long g_joy_n = 0;
static joy_kind_t g_joy_kind = JOY_KIND_PS;

static long g_win_x[WIN_KIND_MAX_N];
static long g_win_y[WIN_KIND_MAX_N];
static long g_win_w[WIN_KIND_MAX_N];
static long g_win_h[WIN_KIND_MAX_N];

/***************************************************************
* GUI スレッドのロック
***************************************************************/

void	gui_begin( void )
{
#ifdef D_WS
	WSGIappDev()->lock();
#endif // D_WS

#ifdef D_GTK
	gdk_threads_enter();
#endif // D_GTK

#ifdef D_IPHONE
	[gMainLock lock];
#endif // D_IPHONE

#ifdef D_MFC
#endif // D_MFC
}

/***************************************************************
* GUI スレッドのアンロック
***************************************************************/

void	gui_end( void )
{
#ifdef D_WS
	WSGIappDev()->unlock();
#endif // D_WS

#ifdef D_GTK
	gdk_flush();
	gdk_threads_leave();
#endif // D_GTK

#ifdef D_IPHONE
	[gMainLock unlock];
#endif // D_IPHONE

#ifdef D_MFC
#endif // D_MFC
}

/***************************************************************
* 自動開放プールを作成
***************************************************************/

void	call_alloc_autorelease_pool( void )
{
#ifdef D_IPHONE
	alloc_autorelease_pool();
#endif // D_IPHONE
}

/***************************************************************
* 自動開放プールを開放
***************************************************************/

void	call_release_autorelease_pool( void )
{
#ifdef D_IPHONE
	release_autorelease_pool();
#endif // D_IPHONE
}

/***************************************************************
* 終了前の処理
***************************************************************/

void	call_close_game_gui( void )
{
#ifdef	D_ALL_GUI
	closeGameGui();
#endif
}

/***************************************************************
* キー・バッファのロック
***************************************************************/

void	key_buf_lock( void )
{
#ifdef D_GTK
# ifdef HAVE_G_THREAD_INIT
	g_static_mutex_lock( &g_key_buf_mutex );
# else // HAVE_G_THREAD_INIT
	g_mutex_lock( &g_key_buf_mutex );
# endif // HAVE_G_THREAD_INIT
#endif // D_GTK
}

/***************************************************************
* キー・バッファのアンロック
***************************************************************/

void	key_buf_unlock( void )
{
#ifdef D_GTK
# ifdef HAVE_G_THREAD_INIT
	g_static_mutex_unlock( &g_key_buf_mutex );
# else // HAVE_G_THREAD_INIT
	g_mutex_unlock( &g_key_buf_mutex );
# endif // HAVE_G_THREAD_INIT
#endif // D_GTK
}

/***************************************************************
* メイン・ループのスレッドを切る
* void *(*func)( void * ) : コール・バック関数
* return : エラーが無かったか？
***************************************************************/

bool_t	call_game_thread_create( void *(*func)( void * ) )
{
#ifdef		D_ALL_GUI
	if( GameThreadCreate( func ) )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* メイン・ループのスレッドを終了
* void *(*func)( void * ) : コール・バック関数
* long code : 終了コード
* return : エラーが無かったか？
***************************************************************/

bool_t	call_game_thread_exit(
	void *(*func)( void * ), long code
)
{
#ifdef		D_ALL_GUI
	if( GameThreadExit( func, code ) )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* カレント・ディレクトリを返す
* return : カレント・ディレクトリ
***************************************************************/

const char	*call_get_home_dir( void )
{
#ifdef D_IPHONE
	return [[NSString stringWithFormat:@"%@/Documents", NSHomeDirectory()] cString];
#endif // D_IPHONE

#if defined( D_DOS ) || defined( D_MFC )
	char strPath[_MAX_PATH + 1];
	char strDrive[_MAX_DRIVE + 1];
	char strDir[_MAX_DIR + 1];
	char strFName[_MAX_FNAME + 1];
	char strExt[_MAX_EXT + 1];

	int nLen = ::GetModuleFileName( NULL, (LPTSTR)strPath, _MAX_PATH );
	if( nLen <= 0 )
		return NULL;

	::_splitpath(
			strPath,
			strDrive,
			strDir,
			strFName,
			strExt);

	static char strRes[_MAX_PATH + 1];
	sn_printf( strRes, _MAX_PATH, "%s%s", strDrive, strDir );

	return strRes;
#endif // D_DOS || D_MFC

	return NULL;
}

/***************************************************************
* タイマーを有効にする
***************************************************************/

void	call_ena_timer( void )
{
#if	defined( D_GTK ) || defined( D_IPHONE )
	ena_timer();
#endif // D_GTK
}

/***************************************************************
* マップ・ウィンドウの連続実行ボタンのセット
* bool_t flagExec : 
***************************************************************/

void	call_gui_map_cont_exec_set( bool_t flagExec )
{
#ifdef D_GTK
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	if( flagExec ){
		set_label_text_button( GTK_BUTTON( gMapButtonContExec ),
				MSG_GUI_MAP_CONT_EXEC_ON, 0.5, 0.5 );
	} else {
		set_label_text_button( GTK_BUTTON( gMapButtonContExec ),
				MSG_GUI_MAP_CONT_EXEC_OFF, 0.5, 0.5 );
	}

	gui_end();
#endif // D_GTK
}

/***************************************************************
* ステータス・バーにヒントを表示
***************************************************************/

void	call_gui_map_print_stat_bar_hint( void )
{
#ifdef	D_ALL_GUI
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	guiMapPrintStatBarHint();

	gui_end();
#endif
}

/***************************************************************
* メニュー・ウィンドウを描画
* draw_menu_t *data : メニューの描画用データ
***************************************************************/

void	call_gui_menu_draw( draw_menu_t *data )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMenu.draw( data );

	gui_end();
#endif
}

/***************************************************************
* メニュー・ウィンドウを閉じる
***************************************************************/

void	call_gui_menu_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMenu.wipe();

	gui_end();
#endif
}

/***************************************************************
* キーをマウス・イベントに変換
* long c : キー
* return : キー
***************************************************************/

long	call_cui_mouse_check_event( long c )
{
#ifdef	D_GTK
	return gCuiMouse.checkEvent( c );
#endif

	return '\0';
}

/***************************************************************
* マウス・イベント・ハンドラーをリセット
***************************************************************/

void	call_cui_mouse_reset_handler_tab( void )
{
#ifdef	D_GTK
	gCuiMouse.resetHandlerTab();
#endif
}

/***************************************************************
* ハンドラー・テーブルに追加
* bool flagEnable : 有効／無効フラグ
* long x : クリックに反応する短形の開始 X 座標
* long y : クリックに反応する短形の開始 Y 座標
* long w : クリックに反応する短形の幅
* long h : クリックに反応する短形の高さ
* long n : ハンドラへの引数 (整数)
* const char *macro : ハンドラへの引数 (マクロ)
* bool_t (*funcPoint)( long btn, long n, const char *macro ) : 
*   ポイント時のハンドラ
* bool_t (*funcClick)( long btn, long n, const char *macro ) : 
*   クリック時のハンドラ
* bool_t (*funcScroll)( long btn, long n, const char *macro ) : 
*   クリック時のハンドラ
* return : ハンドラー・テーブル番号
***************************************************************/

long	call_cui_mouse_add_handler(
	bool_t flagEnable,
	long x, long y, long w, long h,
	bool_t (*funcPoint)( long btn, long n, const char *macro ),
	bool_t (*funcClick)( long btn, long n, const char *macro ),
	bool_t (*funcScroll)( long btn, long n, const char *macro ),
	long n,
	const char *macro
)
{
#ifdef	D_GTK
	return gCuiMouse.addHandler(
			flagEnable,
			x, y, w, h,
			funcPoint, funcClick, funcScroll,
			n, macro );
#endif
	return '\0';
}

/***************************************************************
* デフォルトの選択項目にマウス・カーソルを移動
* long sel_n : 選択項目
***************************************************************/

void	call_set_mouse_dflt_menu( long sel_n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMenu.setMouseDfltMenu( sel_n );

	gui_end();
#endif
}

/***************************************************************
* メッセージの続きマークの設定
***************************************************************/

void	call_gui_message_set_flag_more( bool_t flag )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMessage.setFlagMore( (bool)(flag != FALSE) );

	gui_end();
#endif
}

/***************************************************************
* メッセージ・ウィンドウを描画
***************************************************************/

void	call_gui_message_draw( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMessage.draw( false );
	gGuiMessage.drawScrollBar();

	gui_end();
#endif
}

/***************************************************************
* 数値入力ウィンドウを描画
***************************************************************/

void	call_gui_num_draw(
	volatile long *n, long min, long max, long figure
)
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiNum.draw( n, min, max, figure );

	gui_end();
#endif
}

/***************************************************************
* 数値入力ウィンドウを閉じる
***************************************************************/

void	call_gui_num_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiNum.wipe();

	gui_end();
#endif
}

/***************************************************************
* 文字列入力ウィンドウを描画
***************************************************************/

void	call_gui_input_string_draw(
	const char *ttl, const char *str, long len
)
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiInpStr.draw( ttl, str, len );

	gui_end();
#endif
}

/***************************************************************
* 文字列入力ウィンドウを閉じる
***************************************************************/

void	call_gui_input_string_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiInpStr.wipe();

	gui_end();
#endif
}

/***************************************************************
* 台詞ウィンドウを描画
* const char *name : 名前
* const char *str : 台詞
***************************************************************/

void	call_gui_words_draw( const char *name, const char *str )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiWords.draw( name, str );

	gui_end();
#endif
}

/***************************************************************
* 台詞ウィンドウを描画 (表示幅を指定)
* const char *name : 名前
* const char *str : 台詞
* long w : 表示幅
***************************************************************/

void	call_gui_words_draw_width(
	const char *name, const char *str,
	long w
)
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiWords.draw( name, str, w );

	gui_end();
#endif
}

/***************************************************************
* 台詞ウィンドウを閉じる
***************************************************************/

void	call_gui_words_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiWords.wipe();

	gui_end();
#endif
}

/***************************************************************
* リプレイ・ウィンドウを開始
***************************************************************/

void	call_gui_replay_bgn( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiReplay.bgn();

	gui_end();
#endif
}

/***************************************************************
* リプレイ・ウィンドウを終了
***************************************************************/

void	call_gui_replay_end( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiReplay.end();

	gui_end();
#endif
}

/***************************************************************
* リプレイ・ウィンドウを描画
***************************************************************/

void	call_gui_replay_draw( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiReplay.draw();

	gui_end();
#endif
}

/***************************************************************
* リプレイ・ウィンドウを閉じる
***************************************************************/

void	call_gui_replay_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiReplay.wipe();

	gui_end();
#endif
}

/***************************************************************
* クラス・エディタ・ウィンドウを描画
* class_t *p : クラス
***************************************************************/

void	call_gui_class_edit_draw( class_t *p )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiClassEdit.draw( p );

	gui_end();
#endif
}

/***************************************************************
* クラス・エディタ・ウィンドウを閉じる
***************************************************************/

void	call_gui_class_edit_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiClassEdit.wipe();

	gui_end();
#endif
}

/***************************************************************
* スキル・エディタ・ウィンドウを描画
* class_t *p : クラス
***************************************************************/

void	call_gui_skill_edit_draw( class_t *p )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiSkillEdit.draw( p );

	gui_end();
#endif
}

/***************************************************************
* スキル・エディタ・ウィンドウを閉じる
***************************************************************/

void	call_gui_skill_edit_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiSkillEdit.wipe();

	gui_end();
#endif
}

/***************************************************************
* キャラクタ・シート・ウィンドウを描画
***************************************************************/

void	call_gui_chr_sheet_draw( mbr_t *org, mbr_t *mbr )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiChrSheet.draw( org, mbr );

	gui_end();
#endif
}

/***************************************************************
* キャラクタ・シート・ウィンドウを再描画
* mbr_t *org : 元のキャラクタ・データ
* mbr_t *mbr : 編集中のキャラクタ・データ
***************************************************************/

void	call_gui_chr_sheet_redraw( mbr_t *org, mbr_t *mbr )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiChrSheet.redraw();

	gui_end();
#endif
}

/***************************************************************
* キャラクタ・シート・ウィンドウを閉じる
***************************************************************/

void	call_gui_chr_sheet_wipe()
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiChrSheet.wipe();

	gui_end();
#endif
}

/***************************************************************
* グラフィック設定のブロックを開始
* return : エラーが無かったか?
***************************************************************/

bool_t	call_sel_conf_eval_block_begin( void )
{
#ifdef		D_ALL_GUI
	if( gSelConf.evalBlockBegin() )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* グラフィック設定のブロックを終了
* return : エラーが無かったか?
***************************************************************/

bool_t	call_sel_conf_eval_block_end( void )
{
#ifdef		D_ALL_GUI
	if( gSelConf.evalBlockEnd() )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* グラフィック設定の数値を設定
* long token : トークン
* long n : 数値
* return : エラーが無かったか?
***************************************************************/

bool_t	call_sel_conf_eval_set_num( long token, long n )
{
#ifdef		D_ALL_GUI
	if( gSelConf.evalSetNum( (GraphConfToken)token, n ) )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* グラフィック設定の文字列を設定
* long token : トークン
* WSCstring str : 文字列
* return : エラーが無かったか?
***************************************************************/

bool_t	call_sel_conf_eval_set_str( long token, char *str )
{
#ifdef		D_ALL_GUI
	if( gSelConf.evalSetStr( (GraphConfToken)token, str ) )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* メンバーのグラフィック・パターンを選択開始
* mbr_t *mbr : メンバー
***************************************************************/

bool_t	call_sel_mbr_graph_begin( mbr_t *mbr )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	bool_t flgWait = FALSE;

	if( !g_flg_gui )
		return FALSE;

	gui_begin();

	if( gSelMbrGraph == NULL )
		gSelMbrGraph = new SelMbrGraph;
	flgWait = gSelMbrGraph->exec( mbr );

	gui_end();

	if( flgWait )
		return TRUE;
	else
		return FALSE;
#endif

	return FALSE;
}

/***************************************************************
* メンバーのグラフィック・パターンを選択終了
***************************************************************/

void	call_sel_mbr_graph_end( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_gui )
		return;

	gui_begin();

	delete gSelMbrGraph;
	gSelMbrGraph = NULL;

	gui_end();
#endif
}

/***************************************************************
* グラフィック・パターンのリセット
***************************************************************/

void	call_pcg_dun_reset( void )
{
#ifdef	D_ALL_GUI
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.reset();

	gui_end();
#endif
}

/***************************************************************
* メンバーのグラフィック・パターンのリセット
***************************************************************/

void	call_pcg_dun_reload_all_mbr( void )
{
#ifdef	D_ALL_GUI
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.reloadAllMbr();

	gui_end();
#endif
}

/***************************************************************
* ターン毎のマップの描画
***************************************************************/

void	call_pcg_dun_draw_turn( bool_t flg_first )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_IPHONE )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	if( flg_first )
		gPcgDun.setFlgUpdateRequest( true );

	gui_begin();

	gPcgDun.drawTurn();

	gui_end();
#endif

#ifdef D_MFC
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	if( flg_first )
		gPcgDun.setFlgUpdateRequest( true );

	TRY {
		if( g_Dir3d.CheckRefreshFrameMode() )
			g_Dir3d.SetRefreshRequest( true );
		else
			gPcgDun.drawTurn();
	} CATCH( CException, e ){
	} END_CATCH
#endif // D_MFC
}

/***************************************************************
* マップの再描画
***************************************************************/

void	call_pcg_dun_redraw( bool_t flgForce )
{
	bool bFlagForce;
	if( flgForce )
		bFlagForce = true;
	else
		bFlagForce = false;

#if	defined( D_WS ) || defined( D_GTK ) || defined( D_IPHONE )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.redraw( bFlagForce );

	gui_end();
#endif

#ifdef D_MFC
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	TRY {
		if( g_Dir3d.CheckRefreshFrameMode() )
			g_Dir3d.SetRefreshRequest( true );
		else
			gPcgDun.redraw( bFlagForce );
	} CATCH( CException, e ){
	} END_CATCH
#endif // D_MFC
}

/***************************************************************
* グラフィック・パターンの描画
* long map_x : マップの X 座標
* long map_y : マップの Y 座標
* long map_w : マップの幅
* long map_h : マップの高さ
* bool_t flagForce : 強制描画
***************************************************************/

void	call_pcg_dun_draw(
	long map_x, long map_y,
	long map_w, long map_h,
	bool_t flagForce
)
{
	bool bFlagForce;
	if( flagForce )
		bFlagForce = true;
	else
		bFlagForce = false;

#if	defined( D_WS ) || defined( D_GTK ) || defined( D_IPHONE )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.draw( map_x, map_y, map_w, map_h, bFlagForce );

	gui_end();
#endif

#ifdef D_MFC
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	TRY {
		if( g_Dir3d.CheckRefreshFrameMode() )
			g_Dir3d.SetRefreshRequest( true );
		else
			gPcgDun.draw( map_x, map_y, map_w, map_h, bFlagForce );
	} CATCH( CException, e ){
	} END_CATCH
#endif // D_MFC
}

/***************************************************************
* XX の攻撃の描画データを設定
* xx_act_kind_t kind : 攻撃の種類
* void *p : 攻撃のデータ
***************************************************************/

void	call_pcg_dun_set_xx_attack(
	long kind, void *p )
{
#ifdef	D_ALL_GUI
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gPcgDun.setXxAttack( (xx_act_kind_t)kind, p );
#endif
}

/***************************************************************
* テキスト・モードの時、マップへ文字列を描画
* long scrn_x : X 座標
* long scrn_y : Y 座標
* const char *s : フォーマット文字列
* ... : フォーマットの引数
***************************************************************/

void	call_pcg_dun_draw_string(
	long scrn_x, long scrn_y,
	const char *s, ... )
{
#ifdef	D_ALL_GUI
	va_list	argptr;
	static char	buf[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;

	va_start( argptr, s );
	vsn_printf( buf, max_len, s, argptr );
	va_end( argptr );

	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.drawString( scrn_x, scrn_y, MSG_S, buf );

	gui_end();
#endif
}

/***************************************************************
* VFX を描画
* long scrn_x : X 座標
* long scrn_y : Y 座標
* long scrn_w : 幅
* long scrn_h : 高さ
***************************************************************/

void	call_pcg_dun_draw_vfx(
	long scrn_x, long scrn_y,
	long scrn_w, long scrn_h )
{
#ifdef	D_ALL_GUI
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.drawVfx( scrn_x, scrn_y, scrn_w, scrn_h, false );

	gui_end();
#endif
}

/***************************************************************
* マップのスクロール
* long map_x : マップの X 座標
* long map_y : マップの Y 座標
***************************************************************/

void	call_pcg_dun_scroll( long map_x, long map_y )
{
#ifdef	D_ALL_GUI
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.scrollTile( map_x, map_y );

	gui_end();
#endif
}

/***************************************************************
* カーソル・パターンの幅を返す
* bool_t flagSub : サブ・カーソルか?
* return : 幅
***************************************************************/

long	call_pcg_dun_get_crsr_width( bool_t flagSub )
{
#ifdef	D_ALL_GUI
	gui_begin();

	long n = gPcgDun.getCrsrWidth( !!flagSub );

	gui_end();

	return n;
#endif

	return 0;
}

/***************************************************************
* カーソル・パターンの高さを返す
* bool_t flagSub : サブ・カーソルか?
* return : 高さ
***************************************************************/

long	call_pcg_dun_get_crsr_height( bool_t flagSub )
{
#ifdef	D_ALL_GUI
	gui_begin();

	long n = gPcgDun.getCrsrHeight( !!flagSub );

	gui_end();

	return n;
#endif

	return 0;
}

/***************************************************************
* キャラクタの左端の座標を返す
* chr_t *chr : キャラクタ
* bool_t flagPre : 1 つ前の座標
* return : 左端の座標
***************************************************************/

long	call_pcg_dun_get_chr_draw_left( chr_t *chr, bool_t flagPre )
{
#ifdef	D_ALL_GUI
	bool bFlagPre;
	if( flagPre )
		bFlagPre = true;
	else
		bFlagPre = false;

	if( g_flg_text_mode ){
		if( flagPre )
			return get_chr_left( chr->pre_draw_x, chr->dx );
		else
			return get_chr_left( chr->x, chr->dx );
	}

	gui_begin();

	Pcg *pPcg = gPcgDun.getChrPcg( chr );

	long n = gPcgDun.getChrDrawLeft( chr, pPcg, bFlagPre );
	n = n / gPcgDun.getTileSizeX();

	gui_end();

	return n;
#endif

	if( flagPre )
		return get_chr_left( chr->pre_draw_x, chr->dx );
	else
		return get_chr_left( chr->x, chr->dx );
}

/***************************************************************
* キャラクタの右端の座標を返す
* chr_t *chr : キャラクタ
* bool_t flagPre : 1 つ前の座標
* return : 右端の座標
***************************************************************/

long	call_pcg_dun_get_chr_draw_right( chr_t *chr, bool_t flagPre )
{
#ifdef	D_ALL_GUI
	bool bFlagPre;
	if( flagPre )
		bFlagPre = true;
	else
		bFlagPre = false;

	if( g_flg_text_mode ){
		if( flagPre )
			return get_chr_right( chr->pre_draw_x, chr->dx );
		else
			return get_chr_right( chr->x, chr->dx );
	}

	gui_begin();

	Pcg *pPcg = gPcgDun.getChrPcg( chr );

	long n = gPcgDun.getChrDrawRight( chr, pPcg, bFlagPre );
	n = (n + gPcgDun.getTileSizeX() - 1) / gPcgDun.getTileSizeX();

	gui_end();

	return n;
#endif

	if( flagPre )
		return get_chr_right( chr->pre_draw_x, chr->dx );
	else
		return get_chr_right( chr->x, chr->dx );
}

/***************************************************************
* キャラクタの上端の座標を返す
* chr_t *chr : キャラクタ
* bool_t flagPre : 1 つ前の座標
* return : 上端の座標
***************************************************************/

long	call_pcg_dun_get_chr_draw_top( chr_t *chr, bool_t flagPre )
{
#ifdef	D_ALL_GUI
	bool bFlagPre;
	if( flagPre )
		bFlagPre = true;
	else
		bFlagPre = false;

	if( g_flg_text_mode ){
		if( flagPre )
			return get_chr_top( chr->pre_draw_y, chr->dy );
		else
			return get_chr_top( chr->y, chr->dy );
	}

	gui_begin();

	Pcg *pPcg = gPcgDun.getChrPcg( chr );

	long n = gPcgDun.getChrDrawTop( chr, pPcg, bFlagPre );
	n = n / gPcgDun.getTileSizeY();

	gui_end();

	return n;
#endif

	if( flagPre )
		return get_chr_top( chr->pre_draw_y, chr->dy );
	else
		return get_chr_top( chr->y, chr->dy );
}

/***************************************************************
* キャラクタの下端の座標を返す
* chr_t *chr : キャラクタ
* bool_t flagPre : 1 つ前の座標
* return : 下端の座標
***************************************************************/

long	call_pcg_dun_get_chr_draw_bottom( chr_t *chr, bool_t flagPre )
{
#ifdef	D_ALL_GUI
	bool bFlagPre;
	if( flagPre )
		bFlagPre = true;
	else
		bFlagPre = false;

	if( g_flg_text_mode ){
		if( flagPre )
			return get_chr_bottom( chr->pre_draw_y, chr->dy );
		else
			return get_chr_bottom( chr->y, chr->dy );
	}

	gui_begin();

	Pcg *pPcg = gPcgDun.getChrPcg( chr );

	long n = gPcgDun.getChrDrawBottom( chr, pPcg, bFlagPre );
	n = (n + gPcgDun.getTileSizeY() - 1) / gPcgDun.getTileSizeY();

	gui_end();

	return n;
#endif

	if( flagPre )
		return get_chr_bottom( chr->pre_draw_y, chr->dy );
	else
		return get_chr_bottom( chr->y, chr->dy );
}

/***************************************************************
* 指定座標がマップ・ウィンドウの表示範囲内か調べる
* long mapX : X座標
* long mapY : Y座標
* bool_t flg_gui : GUI から呼ばれたか?
* return : マップ・ウィンドウの表示範囲内か?
***************************************************************/

bool_t	call_pcg_dun_clip_win( long mapX, long mapY, bool_t flg_gui )
{
#ifdef	D_ALL_GUI
	if( !flg_gui )
		gui_begin();

	bool_t flg = gPcgDun.clipWin( mapX, mapY );

	if( !flg_gui )
		gui_end();

	return flg;
#endif

	return TRUE;
}

/***************************************************************
* 指定 X 座標がマップ・ウィンドウの表示範囲内か調べる
* long mapX : X座標
* return : マップ・ウィンドウの表示範囲内か?
***************************************************************/

bool_t	call_pcg_dun_clip_win_x( long mapX, bool_t flg_gui )
{
#ifdef	D_ALL_GUI
	if( !flg_gui )
		gui_begin();

	bool_t flg = gPcgDun.clipWinX( mapX );

	if( !flg_gui )
		gui_end();

	return flg;
#endif

	return TRUE;
}

/***************************************************************
* 指定 Y 座標がマップ・ウィンドウの表示範囲内か調べる
* long mapY : Y座標
* return : マップ・ウィンドウの表示範囲内か?
***************************************************************/

bool_t	call_pcg_dun_clip_win_y( long mapY, bool_t flg_gui )
{
#ifdef	D_ALL_GUI
	if( !flg_gui )
		gui_begin();

	bool_t flg = gPcgDun.clipWinY( mapY );

	if( !flg_gui )
		gui_end();

	return flg;
#endif

	return TRUE;
}

/***************************************************************
* ラスボスのデモをリセット
***************************************************************/

void	call_demo_last_boss_reset( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	if( gPcgDun.pDemoLastBoss == NULL )
		return;

	gui_begin();

	gPcgDun.pDemoLastBoss->reset();

	gui_end();
#endif
}

/***************************************************************
* ラスボスのデモが終ったか調べる
* return : デモが終ったか?
***************************************************************/

bool_t	call_demo_last_boss_check_done( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return TRUE;
	if( !g_flg_gui )
		return TRUE;

	bool_t	flg = TRUE;

	// gui_begin();

	do {
		if( gPcgDun.pDemoLastBoss == NULL ){
			flg = TRUE;
			break;
		}

		if( gPcgDun.pDemoLastBoss->checkDone() ){
			flg = TRUE;
			break;
		} else {
			flg = FALSE;
			break;
		}

		break;
	} while( 0 );

	// gui_end();

	return flg;
#endif

	return TRUE;
}

/***************************************************************
* エンディングのシーンをスキップ
***************************************************************/

void	call_demo_ending_skip_scene( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	if( gPcgDun.pDemoEnding == NULL )
		return;

	gui_begin();

	gPcgDun.pDemoEnding->skipScene();

	gui_end();
#endif
}

/***************************************************************
* シーンに合せた BGM の再生
* bool_t flg_gui : GUI から呼ばれたか?
***************************************************************/

void	call_game_music_play_scene( bool_t flg_gui )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !flg_gui )
		gui_begin();

	gMusic.playScene();

	if( !flg_gui )
		gui_end();
#endif
}

/***************************************************************
* BGM の再生
* music_kind_t kind : BGM の種類
* long idx : BGM リストのインデックス
***************************************************************/

void	call_game_music_play( long kind, long idx )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gMusic.play( (music_kind_t)kind, idx );

	gui_end();
#endif
}

/***************************************************************
* BGM の再再生
***************************************************************/

void	call_game_music_replay( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gMusic.replay();

	gui_end();
#endif
}

/***************************************************************
* BGM の音量を設定
***************************************************************/

void	call_game_music_set_volume( rate_t rate )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;

	gui_begin();

	gMusic.setVolume( rate );

	gui_end();
#endif
}

/***************************************************************
* SE の再生
* sound_kind_t kind : SE の種類
* long n : 再生回数
***************************************************************/

void	call_game_sound_play( long kind, long n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gSound.play( (sound_kind_t)kind, n );

	gui_end();
#endif
}

/***************************************************************
* SE の停止
***************************************************************/

void	call_game_sound_stop( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gSound.stop();

	gui_end();
#endif
}

/***************************************************************
* SE の音量を設定
***************************************************************/

void	call_game_sound_set_volume( rate_t rate )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;

	gui_begin();

	gSound.setVolume( rate );

	gui_end();
#endif
}

/***************************************************************
* 選択中のジョイスティック番号を返す
* return : ジョイスティック番号
***************************************************************/

long	call_game_joystick_get_joy( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	long n = gJoystick.getJoy();

	gui_end();

	return n;
#endif

	return g_joy_n;
}

/***************************************************************
* ジョイスティックを選択
* long n : ジョイスティックの番号
***************************************************************/

void	call_game_joystick_sel_joy( long n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gJoystick.selJoy( n );

	gui_end();
#endif

	g_joy_n = n;
}

/***************************************************************
* ジョイスティックの名前を返す
* long n : ジョイスティック番号
* return : ジョイスティックの名前
***************************************************************/

const char	*call_game_joystick_get_name( long n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	const char	*s = gJoystick.getName( n );

	gui_end();

	return s;
#endif

	return NULL;
}

/***************************************************************
* ジョイスティックの種類を返す
* return : ジョイスティックの種類
***************************************************************/

long	call_game_joystick_get_kind( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	long n = gJoystick.getKind();

	gui_end();

	return n;
#endif

	return g_joy_kind;
}

/***************************************************************
* ジョイスティックの種類を設定
* joy_kind_t kind : ジョイスティックの種類
***************************************************************/

void	call_game_joystick_set_kind( long kind )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gJoystick.setKind( (joy_kind_t)kind );

	gui_end();
#endif

	g_joy_kind = (joy_kind_t)kind;
}

/***************************************************************
* ステータス・ウィンドウを再描画
***************************************************************/

void	call_gui_stat_redraw( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiStat.redraw();

	gui_end();
#endif
}

/***************************************************************
* ステータス・ウィンドウを描画
* long n : メンバーNo.
***************************************************************/

void	call_gui_stat_draw( long n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiStat.draw( n );

	gui_end();
#endif
}

/***************************************************************
* ウィンドウの座標の設定
* win_kind_t k : ウィンドウの種類
* long nx : X 座標
* long ny : Y 座標
* long nw : 幅
* long nh : 高さ
***************************************************************/

void	call_win_pos_set(
	win_kind_t k,
	long *px, long *py,
	long *pw, long *ph
)
{
	if( k < WIN_KIND_NULL )
		return;
	if( k >= WIN_KIND_MAX_N )
		return;

#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( g_flg_gui ){
		gui_begin();

		gWinPos[k].set( k, px, py, pw, ph );

		gui_end();

		return;
	}
#endif

	if( px != NULL )
		g_win_x[k] = *px;
	if( py != NULL )
		g_win_y[k] = *py;
	if( pw != NULL )
		g_win_w[k] = *pw;
	if( ph != NULL )
		g_win_h[k] = *ph;
}

/***************************************************************
* ウィンドウの座標の取得
* win_kind_t k : ウィンドウの種類
* long *px : X 座標
* long *py : Y 座標
* long *pw : 幅
* long *ph : 高さ
* return : 取得できたか?
***************************************************************/

bool_t	call_win_pos_get(
	win_kind_t k,
	long *px, long *py,
	long *pw, long *ph
)
{
	if( k < WIN_KIND_NULL )
		return FALSE;
	if( k >= WIN_KIND_MAX_N )
		return FALSE;

#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( g_flg_gui ){
		gui_begin();

		gWinPos[k].get( k, px, py, pw, ph );

		gui_end();

		return TRUE;
	}
#endif

	if( px != NULL )
		*px = g_win_x[k];
	if( py != NULL )
		*py = g_win_y[k];
	if( pw != NULL )
		*pw = g_win_w[k];
	if( ph != NULL )
		*ph = g_win_h[k];

	if( pw != NULL )
		if( *pw <= 0 )
			*pw = 256;
	if( ph != NULL )
		if( *ph <= 0 )
			*ph = 256;

	return TRUE;
}

/***************************************************************
* １文字キー入力
* return : 入力されたキー
***************************************************************/

long	call_key_get_char( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	long	c = '\0';

	if( !g_flg_init )
		return c;
	if( !g_flg_gui )
		return c;

	gui_begin();

	c = gKey.getChar();

	gui_end();

	return c;
#endif

	return '\0';
}

/***************************************************************
* カーソルが移動した時にマップをスクロールする
***************************************************************/

void	call_key_check_move_crsr( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gKey.checkMoveCrsr();

	gui_end();
#endif
}

/***************************************************************
* キー入力のウェイト
* long n : ウェイト (ミリ秒)
***************************************************************/

void	call_sleep( long n )
{
#ifdef	D_MFC
	::Sleep( n );
#endif	/* D_MFC */
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_gui( void )
{
#ifdef	D_ALL_GUI
	check_memory_GlobalVar_cpp();
#endif
}
