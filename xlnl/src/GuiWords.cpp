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
* $Id: GuiWords.cpp,v 1.15 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// 台詞ウィンドウ
////////////////////////////////////////////////////////////////

#define GUI_WORDS_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// 定数定義
////////////////////////////////////////////////////////////////

// デフォルトのウィンドウ・サイズ

#define	DEFAULT_WIN_WIDTH	320
#define	DEFAULT_WIN_HEIGHT	320

////////////////////////////////////////////////////////////////
// イベント・ハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_words_destroy( GtkWidget *widget, gpointer user_data );
gint handle_words_expose( GtkWidget *widget, GdkEventExpose *event );

gint handle_words_ok_clicked( GtkButton *button, gpointer user_data );
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 台詞ウィンドウのコンストラクタ
////////////////////////////////////////////////////////////////

GuiWords::GuiWords()
{
	mWordsWin = NULL;
}

////////////////////////////////////////////////////////////////
// 台詞ウィンドウのデストラクタ
////////////////////////////////////////////////////////////////

GuiWords::~GuiWords()
{
}

////////////////////////////////////////////////////////////////
// 台詞ウィンドウの初期化
////////////////////////////////////////////////////////////////

void GuiWords::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// 台詞ウィンドウの作成
////////////////////////////////////////////////////////////////

void GuiWords::newWin()
{
	if( mWordsWin != NULL )
		return;

#ifdef D_WS
	mWordsWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	// 台詞ウィンドウの作成

	mWordsWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mWordsWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mWordsWin ),
			"Words" );

	// 台詞ウィンドウへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mWordsWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_words_destroy ),
			this );
	gtk_signal_connect( GTK_OBJECT( mWordsWin ),
			"key-press-event",
			GTK_SIGNAL_FUNC( handleKeyPress ), NULL );

	// ボックスの作成

	GtkWidget *vBoxWin = gtk_vbox_new( FALSE, 0 );
	if( vBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_widget_show( vBoxWin );

	GtkWidget *hBoxWin = gtk_hbox_new( FALSE, 0 );
	if( hBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_widget_show( hBoxWin );

	// 台詞テキストのスクロール・ウィンドウを作成

	mWordsTextScroll = gtk_scrolled_window_new( NULL, NULL );
	if( mWordsTextScroll == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_scrolled_window_new()" );
		return;
	}
	gtk_scrolled_window_set_policy(
			GTK_SCROLLED_WINDOW( mWordsTextScroll ),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );
	gtk_scrolled_window_set_shadow_type(
			GTK_SCROLLED_WINDOW( mWordsTextScroll ),
			GTK_SHADOW_IN );
	gtk_widget_show( mWordsTextScroll );

	// 台詞テキストのビューを作成

	mWordsTextView = gtk_text_view_new();
	if( mWordsTextView == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_text_view_new()" );
		return;
	}
	gtk_widget_show( mWordsTextView );
	gtk_container_add( GTK_CONTAINER( mWordsTextScroll ),
			mWordsTextView );

	// OK ボタンの作成

	mButtonOk = gtk_button_new_with_label( "Ok" );
	if( mButtonOk == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonOk );

	// OK ボタンへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mButtonOk ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_words_ok_clicked ),
			NULL );

	// ボックスにのせる

	gtk_box_pack_start( GTK_BOX( vBoxWin ), mWordsTextScroll,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( hBoxWin ), mButtonOk,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBoxWin ), hBoxWin,
			FALSE, FALSE, 0 );

	gtk_container_add( GTK_CONTAINER( mWordsWin ), vBoxWin );

	// ウィンドウ・サイズを設定

	gtk_widget_show( GTK_WIDGET( mWordsWin ) );
	gdk_window_resize( GTK_WIDGET( mWordsWin )->window,
			DEFAULT_WIN_WIDTH,
			DEFAULT_WIN_HEIGHT );
#endif	// D_GTK

#ifdef D_MFC
	mWordsWin = new CWordsDlg;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 台詞ウィンドウの削除
////////////////////////////////////////////////////////////////

void GuiWords::destroy()
{
	if( mWordsWin == NULL )
		return;

#ifdef D_GTK
	mWordsWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	delete ((CWordsDlg *)mWordsWin);
	mWordsWin = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 台詞ウィンドウの表示
// const char *name : 名前
// const char *str : 台詞
// long w : 表示幅
////////////////////////////////////////////////////////////////

void GuiWords::draw( const char *name, const char *str, long w )
{
	newWin();

	if( w <= 0 )
		w = WIN_REQUEST_DRAW_WIDTH;

#ifdef D_GTK
	GtkTextBuffer *buf = gtk_text_view_get_buffer(
			GTK_TEXT_VIEW( mWordsTextView ) );

	// 古いテキストを削除

	GtkTextIter cur, bgn, end;
	gtk_text_buffer_get_start_iter( buf, &bgn );
	gtk_text_buffer_get_end_iter( buf, &end );
	gtk_text_buffer_delete( buf, &bgn, &end );

	// 名前を追加

	gtk_text_buffer_get_end_iter( buf, &cur );
	static char line[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long nLineMaxLen = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;

	if( name != NULL ){
		sn_printf( line, nLineMaxLen,
				MSG_FMT_DRAW_WORDS_NAME, name );
		gtk_text_buffer_insert( buf, &cur,
				line, str_len_std( line ) );
		gtk_text_buffer_insert( buf, &cur, "\n", 1 );
	}

	// テキストを追加

	const char *head, *tail;
	for( head = str; ; head = tail ){
		tail = get_words_line( head, w );
		if( tail == NULL )
			break;
		if( head[0] == '\n' )
			head++;

		str_nz_cpy( line, head, tail - head );
		line[tail - head] = '\0';

		gtk_text_buffer_insert( buf, &cur,
				line, str_len_std( line ) );
		gtk_text_buffer_insert( buf, &cur, "\n", 1 );
	}
#endif // D_GTK

#ifdef D_MFC
	if( mWordsWin == NULL )
		return;

	CString buf;
	static char line[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long nLineMaxLen = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;

	if( name != NULL ){
		sn_printf( line, nLineMaxLen,
				MSG_FMT_DRAW_WORDS_NAME, name );
		buf += line;
		buf += "\r\n";
	}

	const char *head, *tail;
	head = str;
	for( long i = 0; i < LOOP_MAX_1000; i++ ){
		tail = get_words_line( head, w );
		if( tail == NULL )
			break;
		if( head[0] == '\n' )
			head++;

		str_nz_cpy( line, head, (long)(tail - head) );
		line[tail - head] = '\0';

		buf += line;
		buf += "\r\n";

		head = tail;
	}

	mWordsWin->m_EditDdx = buf;
#endif // D_MFC

	redraw();
}

////////////////////////////////////////////////////////////////
// 台詞ウィンドウの再表示
////////////////////////////////////////////////////////////////

void GuiWords::redraw()
{
	newWin();

	if( mWordsWin == NULL )
		return;

#ifdef D_GTK
	gWinPos[WIN_KIND_WORDS].draw( WIN_KIND_WORDS );
#endif // D_GTK

#ifdef D_MFC
	mWordsWin->DoModal();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 台詞ウィンドウを閉じる
////////////////////////////////////////////////////////////////

void GuiWords::wipe()
{
#ifdef D_GTK
	gWinPos[WIN_KIND_WORDS].wipe( WIN_KIND_WORDS );
#endif // D_GTK

#ifdef D_MFC
	destroy();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// OK ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiWords::okClicked()
{
	wipe();

	gKey.setChar( '\n' );
}

////////////////////////////////////////////////////////////////
// 台詞ウィンドウの終了処理のハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_words_destroy( GtkWidget *widget, gpointer user_data )
{
	gGuiWords.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 台詞ウィンドウの描画イベントの処理
// GtkWidget *widget : メッセージのドローイング・エリア
// GdkEventExpose *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_words_expose( GtkWidget *widget, GdkEventExpose *event )
{
	gGuiWords.redraw();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// OK ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_words_ok_clicked( GtkButton *button, gpointer user_data )
{
	gGuiWords.okClicked();

	return 0;
}
#endif // D_GTK
