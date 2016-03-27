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
* $Id: GuiMessage.cpp,v 1.54 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウ
////////////////////////////////////////////////////////////////

#define GUI_MESSAGE_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define MESSAGE_WIN_INIT_WIDTH	(80 * 8)
#define MESSAGE_WIN_INIT_HEIGHT	(3 * 16)
#define MESSAGE_WIN_MIN_WIDTH	(1 * 8)
#define MESSAGE_WIN_MIN_HEIGHT	(1 * 16)

////////////////////////////////////////////////////////////////
// イベント・ハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_message_delete(
	GtkWidget *widget, gpointer user_data
);
gint handle_message_destroy(
	GtkWidget *widget, gpointer user_data
);
gint handle_message_expose(
	GtkWidget *widget, GdkEventExpose *event
);
gint handle_message_configure(
	GtkWidget *widget, GdkEventConfigure *event
);
gint handle_message_da_expose(
	GtkWidget *widget, GdkEventExpose *event
);
gint handle_message_da_configure(
	GtkWidget *widget, GdkEventConfigure *event
);
gint handle_message_scroll_wheel(
	GtkWidget *widget, GdkEventScroll *event
);
gint handle_message_scroll_changed(
	GtkAdjustment *adjustment,
	gpointer user_data
);
#endif // D_GTK

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウのコンストラクタ
////////////////////////////////////////////////////////////////

GuiMessage::GuiMessage()
{
	mMessageWin = NULL;

	flagMore = FALSE;
	mLsMessageDrawBeginN = 0;
	mLsMessageDrawN = 0;

#ifdef D_GTK
	mMessageDrawingArea = NULL;
	mMessageHScrollBarAdjustment = NULL;
	mMessageVScrollBarAdjustment = NULL;

	mFgGc = NULL;
	mBgGc = NULL;
	mStyle = NULL;
#endif // D_GTK

#ifdef D_MFC
	pDc = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウのデストラクタ
////////////////////////////////////////////////////////////////

GuiMessage::~GuiMessage()
{
#ifdef D_MFC
	if( pDc != NULL ){
		delete pDc;
		pDc = NULL;
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウの初期化
////////////////////////////////////////////////////////////////

void GuiMessage::init()
{
	newWin();
	redraw();

#ifdef D_GTK
	gtk_drawing_area_size( GTK_DRAWING_AREA( mMessageDrawingArea ),
			MESSAGE_WIN_MIN_WIDTH, MESSAGE_WIN_MIN_HEIGHT );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウの作成
////////////////////////////////////////////////////////////////

void GuiMessage::newWin()
{
	if( mMessageWin != NULL )
		return;

#ifdef D_WS
	mMessageWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	// フォントを初期化

	if( mStyle == NULL )
		mStyle = gtk_style_copy( gtk_widget_get_default_style() );

	GdkFont *font = gdk_fontset_load(
			"-adobe-helvetica-medium-r-normal-*-*"
			"-140-*,-*" );
	gtk_style_set_font( mStyle, font );

	// メッセージ・ウィンドウの作成

	mMessageWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mMessageWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mMessageWin ),
			"Message" );

	// メッセージ・ウィンドウへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mMessageWin ),
			"delete_event",
			GTK_SIGNAL_FUNC( handle_message_delete ),
			this );
	gtk_signal_connect( GTK_OBJECT( mMessageWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_message_destroy ),
			this );
	gtk_signal_connect( GTK_OBJECT( mMessageWin ),
			"expose_event",
			GTK_SIGNAL_FUNC( handle_message_expose ),
			this );
	gtk_signal_connect( GTK_OBJECT( mMessageWin ),
			"key-press-event",
			GTK_SIGNAL_FUNC( handleKeyPress ), NULL );

	// 描画エリアを作成

	GtkWidget *pTab = gtk_table_new( 2, 2, FALSE );
	gtk_container_add( GTK_CONTAINER( mMessageWin ), pTab );
	gtk_widget_show( pTab );

	mMessageDrawingArea = gtk_drawing_area_new();
	if( mMessageDrawingArea == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_drawing_area_new()" );
		return;
	}
	gtk_drawing_area_size( GTK_DRAWING_AREA( mMessageDrawingArea ),
			MESSAGE_WIN_INIT_WIDTH, MESSAGE_WIN_INIT_HEIGHT );

	GtkAttachOptions xOpt, yOpt;
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), mMessageDrawingArea,
			0, 1, 0, 1,
			xOpt, yOpt,
			0, 0 );
	gtk_widget_show( mMessageDrawingArea );

	// 描画エリアへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mMessageDrawingArea ),
			"expose_event",
			GTK_SIGNAL_FUNC( handle_message_da_expose ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( mMessageDrawingArea ),
			"configure_event",
			GTK_SIGNAL_FUNC( handle_message_da_configure ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( mMessageDrawingArea ),
			"scroll_event",
			GTK_SIGNAL_FUNC( handle_message_scroll_wheel ),
			NULL );
	gtk_widget_set_events(
			mMessageDrawingArea,
			(GDK_EXPOSURE_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_BUTTON_RELEASE_MASK
			| GDK_SCROLL_MASK) );

	// 水平スクロール・バーの調整を作成

	long w = WIN_MSG_DRAW_WIDTH * 32;
	mMessageHScrollBarAdjustment = gtk_adjustment_new(
			0, 0, w,
			1, w, w );
	if( mMessageHScrollBarAdjustment == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_adjustment_new()" );
		return;
	}

	// 水平スクロール・バーの調整のイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mMessageHScrollBarAdjustment ),
			"changed",
			GTK_SIGNAL_FUNC( handle_message_scroll_changed ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( mMessageHScrollBarAdjustment ),
			"value_changed",
			GTK_SIGNAL_FUNC( handle_message_scroll_changed ),
			NULL );

	// 水平スクロール・バーを作成

	mMessageHScrollBar = gtk_hscrollbar_new(
			GTK_ADJUSTMENT( mMessageHScrollBarAdjustment ) );
	if( mMessageHScrollBar == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hscrollbar_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ),
			mMessageHScrollBar,
			0, 1, 1, 2,
			xOpt, yOpt,
			0, 0 );
	gtk_widget_show( mMessageHScrollBar );

	// 垂直スクロール・バーの調整を作成

	mMessageVScrollBarAdjustment = gtk_adjustment_new(
			0, 0, LS_MSG_MAX_N,
			1, 3, 3 );
	if( mMessageVScrollBarAdjustment == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_adjustment_new()" );
		return;
	}

	// 垂直スクロール・バーの調整のイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mMessageVScrollBarAdjustment ),
			"changed",
			GTK_SIGNAL_FUNC( handle_message_scroll_changed ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( mMessageVScrollBarAdjustment ),
			"value_changed",
			GTK_SIGNAL_FUNC( handle_message_scroll_changed ),
			NULL );

	// 垂直スクロール・バーを作成

	mMessageVScrollBar = gtk_vscrollbar_new(
			GTK_ADJUSTMENT( mMessageVScrollBarAdjustment ) );
	if( mMessageVScrollBar == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vscrollbar_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ),
			mMessageVScrollBar,
			1, 2, 0, 1,
			xOpt, yOpt,
			0, 0 );
	gtk_widget_show( mMessageVScrollBar );
#endif	// D_GTK

#ifdef D_MFC
	mMessageWin = &(theApp.m_MesWnd);
#endif // D_MFC

	gWinPos[WIN_KIND_MESSAGE].get( WIN_KIND_MESSAGE,
			NULL, NULL, NULL, NULL );
	gWinPos[WIN_KIND_MESSAGE].draw( WIN_KIND_MESSAGE );
}

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウの削除
////////////////////////////////////////////////////////////////

void GuiMessage::destroy()
{
	if( mMessageWin == NULL )
		return;

#ifdef D_GTK
	mMessageWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	delete mMessageWin;
	mMessageWin = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// メッセージの続きマークの設定
////////////////////////////////////////////////////////////////

void GuiMessage::setFlagMore( bool flag )
{
	flagMore = flag;
	redraw();
}

////////////////////////////////////////////////////////////////
// メッセージの再表示
////////////////////////////////////////////////////////////////

void GuiMessage::redraw()
{
	draw( true );
}

////////////////////////////////////////////////////////////////
// メッセージの表示
////////////////////////////////////////////////////////////////

void GuiMessage::draw( bool flagRedraw )
{
	newWin();

	if( !g_flg_init )
		return;

#ifdef D_WS
	// メッセージ・ウィンドウを表示
	MessageWin->setVisible( true );
#endif // D_WS

#ifdef D_GTK
	// 描画の色・スタイルを設定

	if( mMessageDrawingArea->window == NULL )
		return;

	if( mFgGc == NULL )
		mFgGc = gdk_gc_new( mMessageDrawingArea->window );
	if( mBgGc == NULL )
		mBgGc = gdk_gc_new( mMessageDrawingArea->window );
	if( mStyle == NULL )
		mStyle = gtk_style_copy( gtk_widget_get_default_style() );

	if( mFgGc == NULL )
		return;
	if( mBgGc == NULL )
		return;
	if( mStyle == NULL )
		return;

	GdkDrawable *gd = GDK_DRAWABLE( mMessageDrawingArea->window );
	if( gd == NULL )
		return;

	// 描画開始座標

	long x = 0;
	long y = mMessageDrawingArea->allocation.height - 1;

	// 水平スクロール・バー

	GtkAdjustment *hAdj = GTK_ADJUSTMENT(
			mMessageHScrollBarAdjustment );
	x -= (long)hAdj->value;

	// 垂直スクロール・バー

	GtkAdjustment *vAdj = GTK_ADJUSTMENT(
			mMessageVScrollBarAdjustment );
	long maxN = (long)(vAdj->upper - vAdj->page_size);

	if( !flagRedraw )
		if( (long)(vAdj->value) >= maxN )
			vAdj->value = maxN + 1;

	mLsMessageDrawBeginN = maxN - (long)(vAdj->value);

	if( mLsMessageDrawBeginN > maxN )
		mLsMessageDrawBeginN = maxN;
	if( mLsMessageDrawBeginN < 0 )
		mLsMessageDrawBeginN = 0;

	// 描画

	long i;
	for( i = mLsMessageDrawBeginN; i < LS_MSG_MAX_N; i++ ){
		ls_msg_t *ls = get_ls_msg( i );
		if( ls == NULL )
			break;

		// フォント・サイズを取得

		gint leftBearing, rightBearing;
		gint width, ascent, descent;

		gdk_string_extents( gtk_style_get_font( mStyle ),
				ls->msg,
				&leftBearing, &rightBearing,
				&width, &ascent, &descent );

		long h = ascent + descent + LINE_INTERVAL;
		long w = mMessageDrawingArea->allocation.width;

		// 背景を塗りつぶす

		SetPenAttr( mFgGc, mBgGc, &(ls->attr) );
		gdk_draw_rectangle( gd, mBgGc, TRUE, 0, y - h, w, h );

		// メッセージを描画

		gdk_draw_string( gd, gtk_style_get_font( mStyle ),
				mFgGc,
				x, y - descent, ls->msg );

		if( (i == 0) && flagMore ){
			long w = gdk_string_width(
					gtk_style_get_font( mStyle ),
					MSG_MORE );
			long moreX = mMessageDrawingArea
					->allocation.width - w;

			gdk_draw_string( gd, gtk_style_get_font( mStyle ),
					mFgGc,
					moreX, y - descent, MSG_MORE );
		}

		// アンダー・ラインを描画

		if( ls->attr.attr & A_UNDERLINE )
			gdk_draw_line( gd, mFgGc, 0, y, w, y );

		y -= h;
		if( y < 0 )
			break;
	}

	mLsMessageDrawN = i - mLsMessageDrawBeginN;

	// 背景の残りの部分を塗りつぶす

	curs_attrset_n( CURS_ATTR_N_NORMAL );
	curs_attr_t attr = get_current_attr();
	SetPenAttr( NULL, mBgGc, &attr );

	long w = mMessageDrawingArea->allocation.width;
	if( (y + 1) > 0 )
		gdk_draw_rectangle( gd, mBgGc, TRUE, 0, 0, w, y + 1 );
#endif // D_GTK

#ifdef D_MFC
	CMessageView *view = &(theApp.m_MesWnd.m_wndView);

	// 描画の色・スタイルを設定

	if( pDc == NULL )
		pDc = new CClientDC( view );

	SCROLLINFO info;
	CRect rcView;
	CRect rcFill;

	// 描画開始座標

	view->GetClientRect( &rcView );

	long x = 0;
	long y = rcView.Height();

	// 水平スクロール・バー

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	view->GetScrollInfo( SB_HORZ, &info );

	x -= (long)info.nPos;

	// 垂直スクロール・バー

	info.cbSize = sizeof( info );
	info.fMask = SIF_ALL;
	view->GetScrollInfo( SB_VERT, &info );

	long maxN = (long)(info.nMax - info.nPage + 1);

	if( !flagRedraw && info.nPos != (get_ls_msg_n() - 1) ){
		info.nPos = get_ls_msg_n() - 1;
		if( maxN < info.nPos )
			info.nMax++;
		view->SetScrollInfo( SB_VERT, &info, FALSE );
	}

	mLsMessageDrawBeginN = maxN - (long)info.nPos;

	if( mLsMessageDrawBeginN > maxN )
		mLsMessageDrawBeginN = maxN;
	if( mLsMessageDrawBeginN < 0 )
		mLsMessageDrawBeginN = 0;

	// 描画開始

	g_Dir3d.BeginDraw();

	// 描画

	long i;
	for( i = mLsMessageDrawBeginN; i < LS_MSG_MAX_N; i++ ){
		ls_msg_t *ls = get_ls_msg( i );
		if( ls == NULL )
			break;

		// フォント・サイズを取得

		CSize size = pDc->GetOutputTextExtent(
				CString( ls->msg ) );

		view->GetClientRect( &rcView );

		long h = size.cy + LINE_INTERVAL;
		long w = rcView.Width();

		// 背景を塗りつぶす

		CPen *pen = new CPen();
		CBrush *brush = new CBrush();
		SetPenAttrBg( pDc, pen, brush, &(ls->attr) );

		rcFill.SetRect( 0, y - h, w, y );
		pDc->FillRect( rcFill, brush );

		delete pen;
		delete brush;

		// メッセージを描画

		pen = new CPen();
		SetPenAttrFg( pDc, pen, NULL, &(ls->attr) );

		pDc->TextOut( x, y - h, CString( ls->msg ) );

		delete pen;

		if( (i == 0) && flagMore ){
			CSize size = pDc->GetOutputTextExtent(
					CString( MSG_MORE ) );
			long w = size.cx;
			long moreX = rcView.Width() - w;

			pen = new CPen();
			SetPenAttrFg( pDc, pen, NULL, &(ls->attr) );

			pDc->TextOut( moreX, y, CString( MSG_MORE ) );

			delete pen;
		}

		// アンダー・ラインを描画

		if( ls->attr.attr & A_UNDERLINE ){
			pen = new CPen();
			SetPenAttrFg( pDc, pen, NULL, &(ls->attr) );

			pDc->MoveTo( 0, y - LINE_INTERVAL - 1 );
			pDc->LineTo( w, y - LINE_INTERVAL - 1 );

			delete pen;
		}

		y -= h;
		if( y < 0 )
			break;
	}

	mLsMessageDrawN = i - mLsMessageDrawBeginN;

	// 背景の残りの部分を塗りつぶす

	curs_attrset_n( CURS_ATTR_N_NORMAL );
	curs_attr_t attr = get_current_attr();
	CPen *pen = new CPen();
	CBrush *brush = new CBrush();
	SetPenAttrBg( pDc, pen, brush, &attr );

	if( (y + 1) > 0 ){
		long w = rcView.Width();
		rcFill.SetRect( 0, 0, w, y + 1 );
		pDc->FillRect( rcFill, brush );
	}

	// 描画終了

	g_Dir3d.EndDraw();
	delete pen;
	delete brush;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウを閉じる
////////////////////////////////////////////////////////////////

void GuiMessage::wipe()
{
	gWinPos[WIN_KIND_MESSAGE].wipe( WIN_KIND_MESSAGE );
}

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウのスクロール・バーを描画
////////////////////////////////////////////////////////////////

void GuiMessage::drawScrollBar()
{
	if( !g_flg_init )
		return;

#ifdef D_GTK
	// 水平スクロール・バーを調整

	GtkAdjustment *hAdj = GTK_ADJUSTMENT(
			mMessageHScrollBarAdjustment );

	static char tmp[WIN_MSG_DRAW_WIDTH + 1];
	long i;
	for( i = 0; i < WIN_MSG_DRAW_WIDTH; i++ )
		tmp[i] = 'X';
	tmp[i] = '\0';
	long maxW = gdk_string_width( gtk_style_get_font( mStyle ), tmp );
	long pageW = mMessageDrawingArea->allocation.width;
	long incPageW = pageW / 2;
	if( incPageW < 1 )
		incPageW = 1;

	hAdj->lower = 0;
	hAdj->upper = maxW;
	hAdj->step_increment = maxW / WIN_MSG_DRAW_WIDTH;
	hAdj->page_increment = pageW;
	hAdj->page_size = pageW;

	gtk_adjustment_changed( hAdj );

	// 垂直スクロール・バーを調整

	GtkAdjustment *vAdj = GTK_ADJUSTMENT(
			mMessageVScrollBarAdjustment );

	long maxH = get_ls_msg_n() - 1;
	if( maxH < 0 )
		maxH = 0;

	long pageH = mLsMessageDrawN;
	if( pageH < 1 )
		pageH = 1;

	long incPageH = pageH / 1;
	if( incPageH < 1 )
		incPageH = 1;

	vAdj->lower = 0;
	vAdj->upper = maxH + pageH;
	vAdj->step_increment = 1;
	vAdj->page_increment = incPageH;
	vAdj->page_size = pageH;

	gtk_adjustment_changed( vAdj );
#endif // D_GTK

#ifdef D_MFC
	theApp.m_MesWnd.m_wndView.PostMessage( WM_SIZE, 0, 0 );
	theApp.m_MesWnd.m_wndView.UpdateWindow();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウを水平スクロール
// long n : スクロール量
////////////////////////////////////////////////////////////////

void GuiMessage::hScroll( long n )
{
#ifdef D_GTK
	GtkAdjustment *adj = GTK_ADJUSTMENT(
			mMessageHScrollBarAdjustment );

	adj->value += n * adj->step_increment;

	if( adj->value < adj->lower )
		adj->value = adj->lower;
	if( adj->value > adj->upper - adj->page_size )
		adj->value = adj->upper - adj->page_size;

	gtk_adjustment_value_changed( adj );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウを垂直スクロール
// long n : スクロール量
////////////////////////////////////////////////////////////////

void GuiMessage::vScroll( long n )
{
#ifdef D_GTK
	GtkAdjustment *adj = GTK_ADJUSTMENT(
			mMessageVScrollBarAdjustment );

	adj->value += n * adj->step_increment;

	if( adj->value < adj->lower )
		adj->value = adj->lower;
	if( adj->value > adj->upper - adj->page_size )
		adj->value = adj->upper - adj->page_size;

	gtk_adjustment_value_changed( adj );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウを閉じる処理のハンドラ
// GtkWidget *widget : ステータス・ウィンドウ
// gpointer data : 登録時に渡された引数
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_message_delete(
	GtkWidget *widget, gpointer data
)
{
	gGuiMessage.wipe();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウの終了処理のハンドラ
// GtkWidget *widget : ステータス・ウィンドウ
// gpointer data : 登録時に渡された引数
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_message_destroy(
	GtkWidget *widget, gpointer data
)
{
	gGuiMessage.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウの描画イベントの処理
// GtkWidget *widget : メッセージのドローイング・エリア
// GdkEventExpose *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_message_expose(
	GtkWidget *widget, GdkEventExpose *event
)
{
	gWinPos[WIN_KIND_MESSAGE].get( WIN_KIND_MESSAGE,
			NULL, NULL, NULL, NULL );
	gWinPos[WIN_KIND_MESSAGE].draw( WIN_KIND_MESSAGE );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウのサイズ変更イベントの処理
// GtkWidget *widget : メッセージのドローイング・エリア
// GdkEventConfigure *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_message_configure(
	GtkWidget *widget, GdkEventConfigure *event
)
{
	gGuiMessage.redraw();
	gGuiMessage.drawScrollBar();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウの描画イベントの処理
// GtkWidget *widget : メッセージのドローイング・エリア
// GdkEventExpose *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_message_da_expose(
	GtkWidget *widget, GdkEventExpose *event
)
{
	gGuiMessage.redraw();
	gGuiMessage.drawScrollBar();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// メッセージ・ウィンドウのサイズ変更イベントの処理
// GtkWidget *widget : メッセージのドローイング・エリア
// GdkEventConfigure *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_message_da_configure(
	GtkWidget *widget, GdkEventConfigure *event
)
{
	gGuiMessage.redraw();
	gGuiMessage.drawScrollBar();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// マウス・ホイールでのスクロール・イベント処理
// GtkWidget *widget : ボタン
// GdkEventScroll *event : イベント
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_message_scroll_wheel(
	GtkWidget *widget, GdkEventScroll *event
)
{
	GdkScrollDirection dir = event->direction;

	switch( dir ){
	case GDK_SCROLL_LEFT:
		gGuiMessage.hScroll( -1 );
		break;
	case GDK_SCROLL_RIGHT:
		gGuiMessage.hScroll( +1 );
		break;
	case GDK_SCROLL_UP:
		gGuiMessage.vScroll( -1 );
		break;
	case GDK_SCROLL_DOWN:
		gGuiMessage.vScroll( +1 );
		break;
	}

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// スクロール・バーの操作イベントの処理
// GtkAdjustment *adjustment : 水平・垂直スクロール・バーの調整
// gpointer user_data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_message_scroll_changed(
	GtkAdjustment *adjustment,
	gpointer user_data
)
{
	gGuiMessage.redraw();

	return 0;
}
#endif // D_GTK
