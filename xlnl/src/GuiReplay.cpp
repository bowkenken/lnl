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
* $Id: GuiReplay.cpp,v 1.9 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// リプレイ・ウィンドウ
////////////////////////////////////////////////////////////////

#define GUI_REPLAY_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// イベント・ハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_replay_destroy( GtkWidget *widget, gpointer user_data );

gint handle_replay_turn_clicked( GtkButton *button, gpointer user_data );
gint handle_replay_key1_clicked( GtkButton *button, gpointer user_data );
gint handle_replay_key10_clicked( GtkButton *button, gpointer user_data );
gint handle_replay_cont_clicked( GtkButton *button, gpointer user_data );
gint handle_replay_exit_clicked( GtkButton *button, gpointer user_data );
#endif // D_GTK

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

GuiReplay::GuiReplay()
{
	mReplayWin = NULL;
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

GuiReplay::~GuiReplay()
{
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void GuiReplay::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// リプレイ・ウィンドウの作成
////////////////////////////////////////////////////////////////

void GuiReplay::newWin()
{
	if( mReplayWin != NULL )
		return;

#ifdef D_WS
	mReplayWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	// ウィンドウの作成

	mReplayWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mReplayWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mReplayWin ),
			MSG_GUI_REPLAY_TITLE );

	// ウィンドウへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mReplayWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_replay_destroy ),
			this );

	// ボックスの作成

	GtkWidget *vBoxWin = gtk_vbox_new( FALSE, 0 );
	if( vBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_widget_show( vBoxWin );

	// テキストのスクロール・ウィンドウを作成

	mReplayTextScroll = gtk_scrolled_window_new( NULL, NULL );
	if( mReplayTextScroll == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_scrolled_window_new()" );
		return;
	}
	gtk_scrolled_window_set_policy(
			GTK_SCROLLED_WINDOW( mReplayTextScroll ),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );
	gtk_scrolled_window_set_shadow_type(
			GTK_SCROLLED_WINDOW( mReplayTextScroll ),
			GTK_SHADOW_IN );
	gtk_widget_show( mReplayTextScroll );

	// テキストのビューを作成

	mReplayTextView = gtk_text_view_new();
	if( mReplayTextView == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_text_view_new()" );
		return;
	}
	gtk_widget_show( mReplayTextView );
	gtk_container_add( GTK_CONTAINER( mReplayTextScroll ),
			mReplayTextView );

	// ボタンの作成

	mButtonTurn = gtk_button_new_with_label( MSG_GUI_REPLAY_TURN );
	if( mButtonTurn == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}

	mButtonKey1 = gtk_button_new_with_label( MSG_GUI_REPLAY_KEY_1 );
	if( mButtonKey1 == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}

	mButtonKey10 = gtk_button_new_with_label( MSG_GUI_REPLAY_KEY_10 );
	if( mButtonKey10 == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}

	mButtonCont = gtk_button_new_with_label( MSG_GUI_REPLAY_CONT );
	if( mButtonCont == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}

	mButtonExit = gtk_button_new_with_label( MSG_GUI_REPLAY_EXIT );
	if( mButtonExit == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}

	// ボタンの表示

	gtk_widget_show( mButtonTurn );
	gtk_widget_show( mButtonKey1 );
	gtk_widget_show( mButtonKey10 );
	gtk_widget_show( mButtonCont );
	gtk_widget_show( mButtonExit );

	// ボタンへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mButtonTurn ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_replay_turn_clicked ),
			NULL );

	gtk_signal_connect( GTK_OBJECT( mButtonKey1 ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_replay_key1_clicked ),
			NULL );

	gtk_signal_connect( GTK_OBJECT( mButtonKey10 ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_replay_key10_clicked ),
			NULL );

	gtk_signal_connect( GTK_OBJECT( mButtonCont ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_replay_cont_clicked ),
			NULL );

	gtk_signal_connect( GTK_OBJECT( mButtonExit ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_replay_exit_clicked ),
			NULL );

	// ボックスにのせる

	gtk_box_pack_start( GTK_BOX( vBoxWin ), mReplayTextScroll,
			TRUE, TRUE, 0 );

	gtk_box_pack_start( GTK_BOX( vBoxWin ), mButtonTurn,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mButtonKey1,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mButtonKey10,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mButtonCont,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mButtonExit,
			TRUE, TRUE, 0 );

	gtk_container_add( GTK_CONTAINER( mReplayWin ), vBoxWin );
#endif	// D_GTK

#ifdef D_MFC
	mReplayWin = &(theApp.m_ReplayWnd);
	CReplayWnd *p = mReplayWin;
	p->m_BtnTurn.SetWindowText( MSG_GUI_REPLAY_TURN );
	p->m_BtnKey1.SetWindowText( MSG_GUI_REPLAY_KEY_1 );
	p->m_BtnKey10.SetWindowText( MSG_GUI_REPLAY_KEY_10 );
	p->m_BtnCont.SetWindowText( MSG_GUI_REPLAY_CONT );
	p->m_BtnExit.SetWindowText( MSG_GUI_REPLAY_EXIT );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// リプレイ・ウィンドウの削除
////////////////////////////////////////////////////////////////

void GuiReplay::destroy()
{
	if( mReplayWin == NULL )
		return;

#ifdef D_GTK
	mReplayWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	delete ((CReplayWnd *)mReplayWin);
	mReplayWin = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// リプレイの開始
////////////////////////////////////////////////////////////////

void GuiReplay::bgn()
{
	draw();
}

////////////////////////////////////////////////////////////////
// リプレイの終了
////////////////////////////////////////////////////////////////

void GuiReplay::end()
{
	gKey.setChar( '0' );
	wipe();
}

////////////////////////////////////////////////////////////////
// リプレイ・ウィンドウの表示
////////////////////////////////////////////////////////////////

void GuiReplay::draw()
{
	newWin();

	const long len = SCREEN_WIDTH * 2;
	char str[SCREEN_WIDTH * 2 + 1] = "";
	get_draw_replay_gui( str, len );

#ifdef D_GTK
	GtkTextBuffer *buf = gtk_text_view_get_buffer(
			GTK_TEXT_VIEW( mReplayTextView ) );

	// 古いテキストを削除

	GtkTextIter cur, bgn, end;
	gtk_text_buffer_get_start_iter( buf, &bgn );
	gtk_text_buffer_get_end_iter( buf, &end );
	gtk_text_buffer_delete( buf, &bgn, &end );

	// テキストを追加

	gtk_text_buffer_get_end_iter( buf, &cur );
	gtk_text_buffer_insert( buf, &cur, str, str_len_std( str ) );
#endif // D_GTK

#ifdef D_MFC
	if( mReplayWin == NULL )
		return;

	mReplayWin->m_TextReplay.SetWindowText( str );
#endif // D_MFC

	redraw();
}

////////////////////////////////////////////////////////////////
// リプレイ・ウィンドウの再表示
////////////////////////////////////////////////////////////////

void GuiReplay::redraw()
{
	newWin();

	gWinPos[WIN_KIND_REPLAY].draw( WIN_KIND_REPLAY, false );
}

////////////////////////////////////////////////////////////////
// リプレイ・ウィンドウを閉じる
////////////////////////////////////////////////////////////////

void GuiReplay::wipe()
{
	gWinPos[WIN_KIND_REPLAY].wipe( WIN_KIND_REPLAY, false );
}

////////////////////////////////////////////////////////////////
// 1 ターン実行ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiReplay::turnClicked()
{
	gKey.setChar( '.' );
}

////////////////////////////////////////////////////////////////
// 1 キー実行ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiReplay::key1Clicked()
{
	gKey.setChar( '\n' );
}

////////////////////////////////////////////////////////////////
// 10 キー実行ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiReplay::key10Clicked()
{
	gKey.setChar( ' ' );
}

////////////////////////////////////////////////////////////////
// 連続実行ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiReplay::contClicked()
{
	gKey.setChar( CMD_KEY_CONT_EXEC );
}

////////////////////////////////////////////////////////////////
// 終了ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiReplay::exitClicked()
{
	end();
}

////////////////////////////////////////////////////////////////
// リプレイ・ウィンドウの終了処理のハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_replay_destroy( GtkWidget *widget, gpointer user_data )
{
	gGuiReplay.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 1 ターン実行ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_replay_turn_clicked( GtkButton *button, gpointer user_data )
{
	gGuiReplay.turnClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 1 キー実行ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_replay_key1_clicked( GtkButton *button, gpointer user_data )
{
	gGuiReplay.key1Clicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 10 キー実行ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_replay_key10_clicked( GtkButton *button, gpointer user_data )
{
	gGuiReplay.key10Clicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 連続実行ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_replay_cont_clicked( GtkButton *button, gpointer user_data )
{
	gGuiReplay.contClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 終了ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_replay_exit_clicked( GtkButton *button, gpointer user_data )
{
	gGuiReplay.exitClicked();

	return 0;
}
#endif // D_GTK
