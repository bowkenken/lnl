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
* $Id: main-gtk.cpp,v 1.81 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// GTK+ 用のメイン処理
////////////////////////////////////////////////////////////////

#define	MAIN_GTK_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define	FLAG_BTN_MAP_LABEL_IS_NAME	1

#define	TILE_X_SIZE()	(gPcgDun.getTileSizeX( true ))
#define	TILE_Y_SIZE()	(gPcgDun.getTileSizeY( true ))

#define	MAP_PIX_MAX_X()	(MAP_MAX_X * TILE_X_SIZE())
#define	MAP_PIX_MAX_Y()	(MAP_MAX_Y * TILE_Y_SIZE())

#define	MAP_WIN_INIT_WIDTH()	(20 * TILE_X_SIZE())
#define	MAP_WIN_INIT_HEIGHT()	(20 * TILE_Y_SIZE())
#define	MAP_WIN_MIN_WIDTH()	(1 * TILE_X_SIZE())
#define	MAP_WIN_MIN_HEIGHT()	(1 * TILE_Y_SIZE())

////////////////////////////////////////////////////////////////

GtkWidget *btnMapExec;
GtkWidget *btnMapAutoMark;
GtkWidget *btnMapUserMenu;
GtkWidget *btnMapSpell;
GtkWidget *btnMapSquare;
GtkWidget *btnMapCancel;
GtkWidget *btnMapOk;

GtkWidget *statBarMap;
guint statBarMapContextId;
guint statBarMapMesId;

guint ghTimer;

////////////////////////////////////////////////////////////////
// メイン・ルーチン
// int argc : 引数の数
// char **argv : 引数のリスト
// return : 終了コード
////////////////////////////////////////////////////////////////

int	main( int argc, char **argv )
{
	init_arg();

	g_flg_gui = TRUE;
	g_flg_cui_mouse = TRUE;

#if	defined( NDEBUG )
	g_flg_cui = FALSE;
#elif	defined( DEBUG )
	g_flg_cui = TRUE;
#else
	g_flg_cui = FALSE;
#endif

	// メイン処理の初期化

	chk_arg( argc, argv );
	init_game();
	change_scene_gui( SCENE_N_INIT );

	if( g_flg_cui_mouse )
		gCuiMouse.init();

	if( g_flg_gui ){
		init_gtk_gui( argc, argv );

		// GUI のメイン・ループを開始

		gtk_main();

		// 終了

		close_game( EXIT_SUCCESS );

		gtk_exit( EXIT_SUCCESS );
	} else if( g_flg_cui_mouse ){
		init_gtk_cui_mouse( argc, argv );

		// CUI のメイン・ループを開始

		game_main();

		// 終了

		close_game( EXIT_SUCCESS );
	} else if( g_flg_cui ){
		init_gtk_cui( argc, argv );

		// CUI のメイン・ループを開始

		game_main();

		// 終了

		close_game( EXIT_SUCCESS );
	}

	exit_game( EXIT_SUCCESS );
	return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////
// GTK+ の初期化 (GUI)
// int argc : 引数の数
// char **argv : 引数のリスト
////////////////////////////////////////////////////////////////

void	init_gtk_gui( int argc, char **argv )
{
	// GTK+ を初期化

	gtk_set_locale();

#if	defined( HAVE_G_THREAD_INIT )
	g_thread_init( NULL );
#endif
	gdk_threads_init();

	gtk_init( &argc, &argv );
	gdk_rgb_init();

	gPcgDun.nTileSizeRate = g_graph_scale_rate;

	init_main_win();

	// SDL を初期化

	gMusic.init();
	gSound.init();
	gJoystick.init();

	// タイマーの設定

	ena_timer();

	// タイトル画像を描画

	gPcgDun.initTitle();
	change_scene_gui( SCENE_N_TITLE );
	gPcgDun.drawTitle();

	// グラフィック設定を選択

	gSelConf.init();
	gSelConf.draw();
}

////////////////////////////////////////////////////////////////
// GTK+ の初期化 (CUI)
// int argc : 引数の数
// char **argv : 引数のリスト
////////////////////////////////////////////////////////////////

void	init_gtk_cui( int argc, char **argv )
{
	// SDL を初期化

	gMusic.init();
	gSound.init();
	gJoystick.init();

	change_scene_gui( SCENE_N_TITLE );

	// スレッドを切る

	call_game_thread_create( main_thread_cui );
}

////////////////////////////////////////////////////////////////
// GTK+ の初期化 (CUI Mouse)
// int argc : 引数の数
// char **argv : 引数のリスト
////////////////////////////////////////////////////////////////

void	init_gtk_cui_mouse( int argc, char **argv )
{
	// GTK+ を初期化

	gtk_set_locale();

#if	defined( HAVE_G_THREAD_INIT )
	g_thread_init( NULL );
#endif
	gdk_threads_init();

	gtk_init( &argc, &argv );

	gPcgDun.nTileSizeRate = g_graph_scale_rate;

	// SDL を初期化

	gMusic.init();
	gSound.init();
	gJoystick.init();

	// 入力の初期化

	gKey.init();
	initMouseMotionFunc();

	change_scene_gui( SCENE_N_TITLE );

	// スレッドを切る

	call_game_thread_create( main_thread_cui );
}

////////////////////////////////////////////////////////////////
// タイマー用のダミーのメイン・スレッド (CUI)
// void *p : 引数
// return : 不明
////////////////////////////////////////////////////////////////

void	*main_thread_cui( void *p )
{
	gtk_main();

	return NULL;
}

////////////////////////////////////////////////////////////////
// タイマーを有効にする
////////////////////////////////////////////////////////////////

void	ena_timer( void )
{
	ghTimer = gtk_timeout_add( 1000 * TIMER_FRAME / 60,
			handle_map_draw,
			(gpointer)gMapDrawingArea );
}

////////////////////////////////////////////////////////////////
// グラフィック設定の選択後の初期化
////////////////////////////////////////////////////////////////

void	init_main_sel_conf( GraphConf *cnf )
{
	// 各種初期化

	gPcgDun.init( cnf );
	configure_map();

	change_scene_gui( SCENE_N_TOWN );

	gGuiMenu.init();
	gGuiMessage.init();
	gGuiStat.init();
	gGuiNum.init();
	gKey.init();
	initMouseMotionFunc();

	pos_t *draw = get_map_draw_pos();
	pos_t *draw_gui = get_map_draw_pos_gui();
	if( (draw != NULL) && (draw_gui != NULL) ){
		draw_gui->x = draw->x;
		draw_gui->y = draw->y;
		gPcgDun.scrollTile( draw_gui->x, draw_gui->y );
	}

	gPcgDun.redraw();

	if( !call_game_thread_create( main_thread ) )
		exit_game( EXIT_FAILURE );
}

////////////////////////////////////////////////////////////////
// メイン・ウィンドウを作成
////////////////////////////////////////////////////////////////

void	init_main_win( void )
{
	GtkAttachOptions xOpt, yOpt;

	gMapWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( gMapWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		exit_game( EXIT_FAILURE );
	}

	GtkWidget *vBox = gtk_vbox_new( FALSE, 0 );
	gtk_container_add( GTK_CONTAINER( gMapWin ), vBox );
	gtk_widget_show( vBox );

	// メイン・ウィンドウへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( gMapWin ),
			"delete_event",
			GTK_SIGNAL_FUNC( handle_delete ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( gMapWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_destroy ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( gMapWin ),
			"key-press-event",
			GTK_SIGNAL_FUNC( handleKeyPress ), NULL );

	// ツール・バーを作成

	GtkWidget *handleBox = gtk_handle_box_new();
	gtk_box_pack_start( GTK_BOX( vBox ), handleBox, FALSE, FALSE, 0 );
	gtk_widget_show( handleBox );

	GtkWidget *toolBar = gtk_toolbar_new();
	gtk_toolbar_set_orientation( GTK_TOOLBAR( toolBar ),
			GTK_ORIENTATION_HORIZONTAL );
	gtk_toolbar_set_style( GTK_TOOLBAR( toolBar ),
			GTK_TOOLBAR_ICONS );
	gtk_widget_show( toolBar );

	gtk_container_add( GTK_CONTAINER( handleBox ), toolBar );

	// ツール・バーのボタンを作成

	btnMapExec = gtk_button_new_with_label(
			MSG_GUI_MAP_EXEC );
	gMapButtonContExec = gtk_button_new_with_label(
			MSG_GUI_MAP_CONT_EXEC_OFF );

#if	FLAG_BTN_MAP_LABEL_IS_NAME
	btnMapAutoMark = gtk_button_new_with_label(
			MSG_GUI_MAP_AUTO_MARK );
	btnMapUserMenu = gtk_button_new_with_label(
			MSG_GUI_MAP_USER_MENU );
	btnMapSpell = gtk_button_new_with_label(
			MSG_GUI_MAP_SPELL );
	btnMapSquare = gtk_button_new_with_label(
			MSG_GUI_MAP_SQUARE );
#else
	btnMapAutoMark = gtk_button_new_with_label(
			"  /  " );
	btnMapUserMenu = gtk_button_new_with_label(
			"  *  " );
	btnMapSpell = gtk_button_new_with_label(
			"  -  " );
	btnMapSquare = gtk_button_new_with_label(
			"  +  " );
#endif

	btnMapCancel = gtk_button_new_with_label(
			MSG_GUI_MAP_CANCEL );
	btnMapOk = gtk_button_new_with_label(
			MSG_GUI_MAP_OK );

	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMapExec,
			MSG_GUI_MAP_TOOL_TIP_EXEC,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			gMapButtonContExec,
			MSG_GUI_MAP_TOOL_TIP_CONT_EXEC,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMapAutoMark,
			MSG_GUI_MAP_TOOL_TIP_AUTO_MARK,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMapUserMenu,
			MSG_GUI_MAP_TOOL_TIP_USER_MENU,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMapSpell,
			MSG_GUI_MAP_TOOL_TIP_SPELL,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMapSquare,
			MSG_GUI_MAP_TOOL_TIP_SQUARE,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMapCancel,
			MSG_GUI_MAP_TOOL_TIP_CANCEL,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMapOk,
			MSG_GUI_MAP_TOOL_TIP_OK,
			NULL );

	gtk_widget_show( btnMapExec );
	gtk_widget_show( gMapButtonContExec );
	gtk_widget_show( btnMapAutoMark );
	gtk_widget_show( btnMapUserMenu );
	gtk_widget_show( btnMapSpell );
	gtk_widget_show( btnMapSquare );
	gtk_widget_show( btnMapCancel );
	gtk_widget_show( btnMapOk );

	// ツール・バーへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( btnMapExec ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_exec_clicked ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( gMapButtonContExec ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_cont_exec_clicked ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( btnMapAutoMark ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_auto_mark_clicked ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( btnMapUserMenu ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_user_menu_clicked ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( btnMapSpell ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_spell_clicked ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( btnMapSquare ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_square_clicked ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( btnMapCancel ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_cancel_clicked ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( btnMapOk ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_ok_clicked ),
			NULL );

	// 描画エリアを作成

	GtkWidget *pTab = gtk_table_new( 2, 2, FALSE );
	gtk_box_pack_start( GTK_BOX( vBox ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	gMapDrawingArea = gtk_drawing_area_new();
	if( gMapDrawingArea == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_drawing_area_new()" );
		exit_game( EXIT_FAILURE );
	}
	gtk_drawing_area_size( GTK_DRAWING_AREA( gMapDrawingArea ),
			MAP_WIN_INIT_WIDTH(),
			MAP_WIN_INIT_HEIGHT() );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), gMapDrawingArea,
			0, 1, 0, 1,
			xOpt, yOpt,
			0, 0 );
	gtk_widget_show( gMapDrawingArea );

	// 描画エリアへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( gMapDrawingArea ),
			"expose_event",
			GTK_SIGNAL_FUNC( handle_map_expose ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( gMapDrawingArea ),
			"configure_event",
			GTK_SIGNAL_FUNC( handle_map_configure ),
			NULL );

	// 描画エリアのマウス・モーションのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( gMapDrawingArea ),
			"motion_notify_event",
			GTK_SIGNAL_FUNC( handle_map_motion_notify ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( gMapDrawingArea ),
			"button_press_event",
			GTK_SIGNAL_FUNC( handle_map_button_press ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( gMapDrawingArea ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_map_button_release ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( gMapDrawingArea ),
			"scroll_event",
			GTK_SIGNAL_FUNC( handle_map_scroll ),
			NULL );
	gtk_widget_set_events(
			gMapDrawingArea,
			(GDK_EXPOSURE_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_BUTTON_RELEASE_MASK
			| GDK_POINTER_MOTION_MASK
			| GDK_POINTER_MOTION_HINT_MASK
			| GDK_SCROLL_MASK) );

	// 水平スクロール・バーの調整を作成

	gMapHScrollBarAdjustment = gtk_adjustment_new(
			0,
			0, MAP_PIX_MAX_X(),
			1 * TILE_X_SIZE(),
			AREA_MAX_X * TILE_X_SIZE() / 2,
			AREA_MAX_X * TILE_X_SIZE() );
	if( gMapHScrollBarAdjustment == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_adjustment_new()" );
		exit_game( EXIT_FAILURE );
	}

	// 水平スクロール・バーの調整のイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( gMapHScrollBarAdjustment ),
			"changed",
			GTK_SIGNAL_FUNC( handle_map_scroll_changed ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( gMapHScrollBarAdjustment ),
			"value_changed",
			GTK_SIGNAL_FUNC( handle_map_scroll_changed ),
			NULL );

	// 水平スクロール・バーを作成

	gMapHScrollBar = gtk_hscrollbar_new(
			GTK_ADJUSTMENT( gMapHScrollBarAdjustment ) );
	if( gMapHScrollBar == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hscrollbar_new()" );
		exit_game( EXIT_FAILURE );
	}
	xOpt = (GtkAttachOptions)(GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ),
			gMapHScrollBar,
			0, 1, 1, 2,
			xOpt, yOpt,
			0, 0 );
	gtk_widget_show( gMapHScrollBar );

	// 垂直スクロール・バーの調整を作成

	gMapVScrollBarAdjustment = gtk_adjustment_new(
			0,
			0, MAP_PIX_MAX_Y(),
			1 * TILE_Y_SIZE(),
			AREA_MAX_Y * TILE_Y_SIZE() / 2,
			AREA_MAX_Y * TILE_Y_SIZE() );
	if( gMapVScrollBarAdjustment == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_adjustment_new()" );
		exit_game( EXIT_FAILURE );
	}

	// 垂直スクロール・バーの調整のイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( gMapVScrollBarAdjustment ),
			"changed",
			GTK_SIGNAL_FUNC( handle_map_scroll_changed ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( gMapVScrollBarAdjustment ),
			"value_changed",
			GTK_SIGNAL_FUNC( handle_map_scroll_changed ),
			NULL );

	// 垂直スクロール・バーを作成

	gMapVScrollBar = gtk_vscrollbar_new(
			GTK_ADJUSTMENT( gMapVScrollBarAdjustment ) );
	if( gMapVScrollBar == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vscrollbar_new()" );
		exit_game( EXIT_FAILURE );
	}
	xOpt = (GtkAttachOptions)(GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ),
			gMapVScrollBar,
			1, 2, 0, 1,
			xOpt, yOpt,
			0, 0 );
	gtk_widget_show( gMapVScrollBar );

	// ステータス・バーを作成

	statBarMap = gtk_statusbar_new();
	if( statBarMap == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_statusbar_new()" );
		exit_game( EXIT_FAILURE );
	}
	gtk_box_pack_start( GTK_BOX( vBox ), statBarMap, FALSE, FALSE, 0 );
	statBarMapContextId = gtk_statusbar_get_context_id(
			GTK_STATUSBAR( statBarMap ), "Status bar" );
	gtk_statusbar_set_has_resize_grip(
			GTK_STATUSBAR( statBarMap ), TRUE );
	statBarMapMesId = gtk_statusbar_push(
			GTK_STATUSBAR( statBarMap ),
			statBarMapContextId, "OK" );
	gtk_widget_show( statBarMap );

	// メイン・ウィンドウを表示

	gWinPos[WIN_KIND_MAP].draw( WIN_KIND_MAP );

	gtk_drawing_area_size( GTK_DRAWING_AREA( gMapDrawingArea ),
			MAP_WIN_MIN_WIDTH(),
			MAP_WIN_MIN_HEIGHT() );
}

////////////////////////////////////////////////////////////////
// ゲーム終了前の処理
////////////////////////////////////////////////////////////////

void	closeGameGui()
{
	if( g_flg_cui_mouse )
		gCuiMouse.close();

	if( g_flg_gui )
		gtk_timeout_remove( ghTimer );

	gMusic.close();
	gSound.close();
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

	gtk_statusbar_remove(
			GTK_STATUSBAR( statBarMap ),
			statBarMapContextId,
			statBarMapMesId );

	statBarMapMesId = gtk_statusbar_push(
			GTK_STATUSBAR( statBarMap ),
			statBarMapContextId,
			str );
}

////////////////////////////////////////////////////////////////
// GTK+ の終了要求のハンドラ
// GtkWidget *widget : メイン・ウィンドウ
// GdkEvent *event : イベント
// gpointer user_data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

gint	handle_delete(
	GtkWidget *widget, GdkEvent *event, gpointer user_data
)
{
	gKey.setChar( 'Q' );

	return TRUE;
}

////////////////////////////////////////////////////////////////
// GTK+ の終了処理のハンドラ
// GtkWidget *widget : メイン・ウィンドウ
// gpointer user_data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_destroy(
	GtkWidget *widget, gpointer user_data
)
{
	gtk_main_quit();
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウの描画イベントの処理
// GtkWidget *widget : マップのドローイング・エリア
// GdkEventExpose *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

gint	handle_map_expose(
	GtkWidget *widget, GdkEventExpose *event
)
{
	GtkAdjustment *hAdj = GTK_ADJUSTMENT( gMapHScrollBarAdjustment );
	GtkAdjustment *vAdj = GTK_ADJUSTMENT( gMapVScrollBarAdjustment );

	long srcX = (long)(hAdj->value + event->area.x);
	long srcY = (long)(vAdj->value + event->area.y);
	long dstX = (long)event->area.x;
	long dstY = (long)event->area.y;
	long w = (long)event->area.width;
	long h = (long)event->area.height;

	// 背景の描画

	GdkGC *gc = gMapDrawingArea->style->fg_gc[GTK_STATE_NORMAL];

	gdk_draw_pixmap(
			gMapDrawingArea->window,
			gc,
			gPcgDun.getWBuf()->getPixMap(),
			srcX, srcY,
			dstX, dstY,
			w, h );
	return TRUE;
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのサイズ変更イベントの処理
// GtkWidget *widget : マップのドローイング・エリア
// GdkEventConfigure *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

gint	handle_map_configure(
	GtkWidget *widget, GdkEventConfigure *event
)
{
	configure_map();

	return TRUE;
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのサイズ変更
////////////////////////////////////////////////////////////////

void	configure_map( void )
{
	// 水平スクロール・バーを調整

	long w = gMapDrawingArea->allocation.width;
	GtkAdjustment *hAdj = GTK_ADJUSTMENT( gMapHScrollBarAdjustment );

	hAdj->lower = 0;
	hAdj->upper = MAP_MAX_X * TILE_X_SIZE();
	hAdj->step_increment = 1 * TILE_X_SIZE();
	hAdj->page_increment = AREA_MAX_X * TILE_X_SIZE();
	hAdj->page_size = w;
	if( hAdj->value > hAdj->upper - w )
		hAdj->value = hAdj->upper - w;

	gtk_adjustment_changed( hAdj );

	// 垂直スクロール・バーを調整

	long h = gMapDrawingArea->allocation.height;
	GtkAdjustment *vAdj = GTK_ADJUSTMENT( gMapVScrollBarAdjustment );

	vAdj->lower = 0;
	vAdj->upper = MAP_MAX_Y * TILE_Y_SIZE();
	vAdj->step_increment = 1 * TILE_Y_SIZE();
	vAdj->page_increment = AREA_MAX_Y * TILE_Y_SIZE();
	vAdj->page_size = h;
	if( vAdj->value > vAdj->upper - h )
		vAdj->value = vAdj->upper - h;

	gtk_adjustment_changed( vAdj );
}

////////////////////////////////////////////////////////////////
// スクロール・バーの操作イベントの処理
// GtkAdjustment *adjustment : 水平・垂直スクロール・バーの調整
// gpointer user_data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_map_scroll_changed(
	GtkAdjustment *adjustment,
	gpointer user_data
)
{
	if( !g_flg_gui )
		return;

	GtkAdjustment *hAdj = GTK_ADJUSTMENT( gMapHScrollBarAdjustment );
	GtkAdjustment *vAdj = GTK_ADJUSTMENT( gMapVScrollBarAdjustment );

	if( chk_scene_group( SCENE_GROUP_N_DEMO ) ){
		hAdj->value = 0;
		vAdj->value = 0;
		return;
	}

	long x = (long)hAdj->value;
	long y = (long)vAdj->value;
	long w = (long)hAdj->page_size;
	long h = (long)vAdj->page_size;

	pos_t *draw_gui = get_map_draw_pos_gui();
	if( draw_gui != NULL ){
		draw_gui->x = x / gPcgDun.getTileSizeX( true );
		draw_gui->y = y / gPcgDun.getTileSizeY( true );
	}

	gPcgDun.drawScroll( x, y, w, h );
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのタイマー描画の処理
// gpointer p : マップのドローイング・エリア
// return : ?
////////////////////////////////////////////////////////////////

gint	handle_map_draw( gpointer p )
{
	static long	flagDrawing = false;

	if( flagDrawing )
		return TRUE;
	flagDrawing = true;
	gui_begin();

	gJoystick.checkEvent();

	if( get_scene() == SCENE_N_LAST_BOSS ){
		if( !gPcgDun.drawLastBoss() ){
			gui_end();
			flagDrawing = false;
			return TRUE;
		}
	} else if( chk_scene_group( SCENE_GROUP_N_TITLE ) ){
		gPcgDun.drawTitle();
	} else if( chk_scene_group( SCENE_GROUP_N_ENDING ) ){
		gPcgDun.drawEnding();
	} else if( chk_scene_group( SCENE_GROUP_N_GAME_OVER ) ){
		gPcgDun.drawGameOver();
#if	0
	} else if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) ){
		if( gSelMbrGraph != NULL )
			gSelMbrGraph->redraw();
#endif
	} else {
		gui_end();
		flagDrawing = false;
		return TRUE;
	}

	GtkWidget *drawingArea = (GtkWidget *)p;
	GdkRectangle rect;
	rect.x = 0;
	rect.y = 0;
	rect.width = drawingArea->allocation.width;
	rect.height = drawingArea->allocation.height;
	gtk_widget_draw( GTK_WIDGET( drawingArea ), &rect );

	gui_end();
	flagDrawing = false;
	return TRUE;
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのマウス・モーションのイベント処理
// GtkWidget *widget : マップのドローイング・エリア
// GdkEventMotion *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

gint	handle_map_motion_notify(
	GtkWidget *widget, GdkEventMotion *event
)
{
	gint x = 0;
	gint y = 0;
	GdkModifierType state = (GdkModifierType)0;

	if( event->is_hint ){
		gdk_window_get_pointer( event->window, &x, &y, &state );
	} else {
		x = (gint)(event->x);
		y = (gint)(event->y);
		state = (GdkModifierType)(event->state);
	}

	gMouseMotion.move( x, y );

	return TRUE;
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウの実行ボタンのクリック・イベント処理
// GtkWidget *widget : ボタン
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_exec_clicked(
	GtkWidget *widget, gpointer *data
)
{
	gKey.setChar( '.' );
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウの連続実行ボタンのトグル・イベント処理
// GtkToggleButton *togglebutton : 
// gpointer user_data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_cont_exec_clicked(
	GtkToggleButton *btn,
	gpointer user_data
)
{
	gKey.setChar( CMD_KEY_CONT_EXEC, false, false );
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのボタンのクリック・イベント処理
// GtkWidget *widget : ボタン
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_auto_mark_clicked(
	GtkWidget *widget, gpointer *data
)
{
	gKey.setChar( '/', true );
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのボタンのクリック・イベント処理
// GtkWidget *widget : ボタン
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_user_menu_clicked(
	GtkWidget *widget, gpointer *data
)
{
	gKey.setChar( '*', true );
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのボタンのクリック・イベント処理
// GtkWidget *widget : ボタン
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_spell_clicked(
	GtkWidget *widget, gpointer *data
)
{
	gKey.setChar( '-', true );
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのボタンのクリック・イベント処理
// GtkWidget *widget : ボタン
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_square_clicked(
	GtkWidget *widget, gpointer *data
)
{
	gKey.setChar( '+', true );
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのボタンのクリック・イベント処理
// GtkWidget *widget : ボタン
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_cancel_clicked(
	GtkWidget *widget, gpointer *data
)
{
	switch( get_lang_kind() ){
	case LANG_KIND_ENGLISH:
		exec_ok_clicked();
		break;
	case LANG_KIND_JAPANESE_EUC:
	case LANG_KIND_JAPANESE_UTF_8:
	case LANG_KIND_JAPANESE_SJIS:
	case LANG_KIND_MAX_N:
	default:
		exec_cancel_clicked();
		break;
	}
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのボタンのクリック・イベント処理
// GtkWidget *widget : ボタン
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

void	handle_ok_clicked(
	GtkWidget *widget, gpointer *data
)
{
	switch( get_lang_kind() ){
	case LANG_KIND_ENGLISH:
		exec_cancel_clicked();
		break;
	case LANG_KIND_JAPANESE_EUC:
	case LANG_KIND_JAPANESE_UTF_8:
	case LANG_KIND_JAPANESE_SJIS:
	case LANG_KIND_MAX_N:
	default:
		exec_ok_clicked();
		break;
	}
}

////////////////////////////////////////////////////////////////
// キャンセル・ボタンの処理
////////////////////////////////////////////////////////////////

void	exec_cancel_clicked( void )
{
	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) )
		gSelMbrGraph->cancel();
	else
		gKey.setChar( '0', true );
}

////////////////////////////////////////////////////////////////
// OK ボタンの処理
////////////////////////////////////////////////////////////////

void	exec_ok_clicked( void )
{
	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) )
		gSelMbrGraph->ok();
	else
		gKey.setChar( 'M' - '@', true );
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのマウス・プレス・イベント処理
// GtkWidget *widget : マップのドローイング・エリア
// GdkEventMotion *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

gint	handle_map_button_press(
	GtkWidget *widget, GdkEventMotion *event
)
{
	gint x = 0;
	gint y = 0;
	GdkModifierType state = (GdkModifierType)0;

	if( event->is_hint ){
		gdk_window_get_pointer( event->window, &x, &y, &state );
	} else {
		x = (gint)(event->x);
		y = (gint)(event->y);
		state = (GdkModifierType)(event->state);
	}

	if( state & (GDK_BUTTON1_MASK | GDK_BUTTON2_MASK
			| GDK_BUTTON3_MASK
			| GDK_BUTTON4_MASK | GDK_BUTTON5_MASK) ){
		GtkAdjustment *hAdj = GTK_ADJUSTMENT(
				gMapHScrollBarAdjustment );
		GtkAdjustment *vAdj = GTK_ADJUSTMENT(
				gMapVScrollBarAdjustment );
		gMapDragBgnX = (long)hAdj->value;
		gMapDragBgnY = (long)vAdj->value;
	}

	if( state & GDK_BUTTON1_MASK )
		gMouseMotion.begin( MouseMotion::nMouseButton0, x, y );
	if( state & GDK_BUTTON2_MASK )
		gMouseMotion.begin( MouseMotion::nMouseButton1, x, y );
	if( state & GDK_BUTTON3_MASK )
		gMouseMotion.begin( MouseMotion::nMouseButton2, x, y );
	if( state & GDK_BUTTON4_MASK )
		gMouseMotion.begin( MouseMotion::nMouseButton3, x, y );
	if( state & GDK_BUTTON5_MASK )
		gMouseMotion.begin( MouseMotion::nMouseButton4, x, y );

	if( event->type == GDK_2BUTTON_PRESS ){
		if( state & GDK_BUTTON1_MASK )
			gMouseMotion.doubleClick(
					MouseMotion::nMouseButton0, x, y );
		if( state & GDK_BUTTON2_MASK )
			gMouseMotion.doubleClick(
					MouseMotion::nMouseButton1, x, y );
		if( state & GDK_BUTTON3_MASK )
			gMouseMotion.doubleClick(
					MouseMotion::nMouseButton2, x, y );
		if( state & GDK_BUTTON4_MASK )
			gMouseMotion.doubleClick(
					MouseMotion::nMouseButton3, x, y );
		if( state & GDK_BUTTON5_MASK )
			gMouseMotion.doubleClick(
					MouseMotion::nMouseButton4, x, y );
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのマウス・リリース・イベント処理
// GtkWidget *widget : マップのドローイング・エリア
// GdkEventMotion *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

gint	handle_map_button_release(
	GtkWidget *widget, GdkEventMotion *event
)
{
	gint x = 0;
	gint y = 0;
	GdkModifierType state = (GdkModifierType)0;

	if( event->is_hint ){
		gdk_window_get_pointer( event->window, &x, &y, &state );
	} else {
		x = (gint)(event->x);
		y = (gint)(event->y);
		state = (GdkModifierType)(event->state);
	}

	if( !(state & GDK_BUTTON1_MASK) )
		gMouseMotion.end( MouseMotion::nMouseButton0, x, y );
	if( !(state & GDK_BUTTON2_MASK) )
		gMouseMotion.end( MouseMotion::nMouseButton1, x, y );
	if( !(state & GDK_BUTTON3_MASK) )
		gMouseMotion.end( MouseMotion::nMouseButton2, x, y );
	if( !(state & GDK_BUTTON4_MASK) )
		gMouseMotion.end( MouseMotion::nMouseButton3, x, y );
	if( !(state & GDK_BUTTON5_MASK) )
		gMouseMotion.end( MouseMotion::nMouseButton4, x, y );

	gMapDragBgnX = -1;
	gMapDragBgnY = -1;

	return TRUE;
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのマウス・スクロール・イベント処理
// GtkWidget *widget : マップのドローイング・エリア
// GdkEventMotion *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

gint	handle_map_scroll(
	GtkWidget *widget, GdkEventScroll *event
)
{
	GdkScrollDirection dir = event->direction;

	switch( dir ){
	case GDK_SCROLL_LEFT:
		gMouseMotion.mouseScroll( MouseMotion::nScrollLeft );
		break;
	case GDK_SCROLL_RIGHT:
		gMouseMotion.mouseScroll( MouseMotion::nScrollRight );
		break;
	case GDK_SCROLL_UP:
		gMouseMotion.mouseScroll( MouseMotion::nScrollUp );
		break;
	case GDK_SCROLL_DOWN:
		gMouseMotion.mouseScroll( MouseMotion::nScrollDown );
		break;
	}

	return TRUE;
}
