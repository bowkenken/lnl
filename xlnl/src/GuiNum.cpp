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
* $Id: GuiNum.cpp,v 1.36 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウ
////////////////////////////////////////////////////////////////

#include "gmain.h"
#include "menu.h"
#include "menu-prot.h"
#include "GuiNum.h"
#include "GlobalVar.h"

#ifdef D_MFC
# include "xlnl-dows/InputNumDlg.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////
// イベント・ハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_delete( GtkWidget *widget, gpointer data );
gint handle_num_destroy( GtkWidget *widget, gpointer data );
gint handle_num_expose( GtkWidget *widget, GdkEventExpose *event );

gint handle_num_hscale_changed( GtkAdjustment *adj, gpointer data );

gint handle_num_spin_changed( GtkAdjustment *adj, gpointer data );

gint handle_num_0_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);
gint handle_num_up_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);
gint handle_num_down_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);

gint handle_num_ok_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウのコンストラクタ
////////////////////////////////////////////////////////////////

GuiNum::GuiNum()
{
	mFlagInitDone = false;
	mNumWin = NULL;
	mPN = NULL;
	mOrg = 0;
	mMin = 0;
	mMax = 1;
	mFigure = 1;
}

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウのデストラクタ
////////////////////////////////////////////////////////////////

GuiNum::~GuiNum()
{
}

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウの初期化
////////////////////////////////////////////////////////////////

void GuiNum::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウの作成
////////////////////////////////////////////////////////////////

void GuiNum::newWin()
{
	if( mNumWin != NULL )
		return;

	mFlagInitDone = false;

#ifdef D_WS
	mNumWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	// 数値入力ウィンドウの作成

	mNumWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mNumWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mNumWin ),
			"Input number" );

	// 数値入力ウィンドウへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mNumWin ),
			"delete_event",
			GTK_SIGNAL_FUNC( handle_num_delete ),
			this );
	gtk_signal_connect( GTK_OBJECT( mNumWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_num_destroy ),
			this );
	gtk_signal_connect( GTK_OBJECT( mNumWin ),
			"key-press-event",
			GTK_SIGNAL_FUNC( handleKeyPress ), NULL );

	//

	GtkWidget *hBoxWin = gtk_hbox_new( FALSE, 0 );
	if( hBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_widget_show( hBoxWin );

	GtkWidget *vBoxWin = gtk_vbox_new( FALSE, 0 );
	if( vBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_widget_show( vBoxWin );

	// 水平スケールの調整の作成

	mHscaleAdjustment = gtk_adjustment_new(
			0, -100, +(100 + 10),
			+1, +10, 10 );
	if( mHscaleAdjustment == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_adjustment_new()" );
		return;
	}

	// 水平スケールの調整へのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mHscaleAdjustment ),
			"changed",
			GTK_SIGNAL_FUNC( handle_num_hscale_changed ),
			(gpointer)0 );
	gtk_signal_connect( GTK_OBJECT( mHscaleAdjustment ),
			"value-changed",
			GTK_SIGNAL_FUNC( handle_num_hscale_changed ),
			(gpointer)0 );

	// 水平スケールの作成

	mHscale = gtk_hscale_new(
			GTK_ADJUSTMENT( mHscaleAdjustment ) );
	if(mHscale  == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hscale_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mHscale,
			TRUE, TRUE, 0 );
	gtk_widget_show( mHscale );

	// スピン・ボタンの調整を作成

	mNumAdjustment = gtk_adjustment_new(
			0, -100, +100,
			+1, +10, 0 );
	if( mNumAdjustment == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_adjustment_new()" );
		return;
	}

	// スピン・ボタンの調整へのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mNumAdjustment ),
			"changed",
			GTK_SIGNAL_FUNC( handle_num_spin_changed ),
			(gpointer)0 );
	gtk_signal_connect( GTK_OBJECT( mNumAdjustment ),
			"value-changed",
			GTK_SIGNAL_FUNC( handle_num_spin_changed ),
			(gpointer)0 );

	// スピン・ボタンの作成

	mNumSpin = gtk_spin_button_new(
			GTK_ADJUSTMENT( mNumAdjustment ), 1.0, 0 );
	if( mNumSpin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_spin_button_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mNumSpin,
			TRUE, TRUE, 0 );
	gtk_widget_show( mNumSpin );

	// ボタン配列の作成

	GtkWidget *vBox[GUI_NUM_BUTTON_MAX_N];

	GtkWidget *hBox = gtk_hbox_new( FALSE, 0 );
	if( hBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_widget_show( hBox );

	for( long i = 0; i < GUI_NUM_BUTTON_MAX_N; i++ ){
		bool flagComma = ((i % 4) == 3);

		// 数字の配列の作成

		if( flagComma )
			mButtonLabel[i] = gtk_button_new_with_label( "," );
		else
			mButtonLabel[i] = gtk_button_new_with_label( "0" );
		if( mButtonLabel[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_button_new_with_label()" );
			return;
		}
		gtk_widget_show( mButtonLabel[i] );

		// 上矢印の配列の作成

		mArrowUp[i] = gtk_arrow_new(
				GTK_ARROW_UP, GTK_SHADOW_ETCHED_OUT );
		if( mArrowUp[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_arrow_new()" );
			return;
		}
		gtk_widget_show( mArrowUp[i] );

		// 上ボタンの配列の作成

		mButtonUp[i] = gtk_button_new();
		if( mButtonUp[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_button_new()" );
			return;
		}
		gtk_container_add( GTK_CONTAINER( mButtonUp[i] ),
				mArrowUp[i] );
		gtk_widget_show( mButtonUp[i] );

		// 下矢印の配列の作成

		mArrowDown[i] = gtk_arrow_new(
				GTK_ARROW_DOWN, GTK_SHADOW_OUT );
		if( mArrowDown[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_arrow_new()" );
			return;
		}
		gtk_widget_show( mArrowDown[i] );

		// 下ボタンの配列の作成

		mButtonDown[i] = gtk_button_new();
		if( mButtonDown[i]  == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_button_new()" );
			return;
		}
		gtk_container_add( GTK_CONTAINER( mButtonDown[i] ),
				mArrowDown[i] );
		gtk_widget_show( mButtonDown[i] );

		// ボタン配列へのイベント・ハンドラを設定

		long	n;
		if( flagComma )
			n = -1;
		else
			n = i;

		gtk_signal_connect( GTK_OBJECT( mButtonLabel[i] ),
				"button_release_event",
				GTK_SIGNAL_FUNC( handle_num_0_clicked ),
				(gpointer)n );

		gtk_signal_connect( GTK_OBJECT( mButtonUp[i] ),
				"button_release_event",
				GTK_SIGNAL_FUNC( handle_num_up_clicked ),
				(gpointer)n );

		gtk_signal_connect( GTK_OBJECT( mButtonDown[i] ),
				"button_release_event",
				GTK_SIGNAL_FUNC( handle_num_down_clicked ),
				(gpointer)n );

		// ボックスにのせる

		vBox[i] = gtk_vbox_new( FALSE, 0 );
		if( vBox[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
			return;
		}
		gtk_widget_show( vBox[i] );

		gtk_container_add( GTK_CONTAINER( vBox[i] ),
				mButtonLabel[i] );
		gtk_container_add( GTK_CONTAINER( vBox[i] ),
				mButtonUp[i] );
		gtk_container_add( GTK_CONTAINER( vBox[i] ),
				mButtonDown[i] );

		gtk_box_pack_end( GTK_BOX( hBox ), vBox[i],
				TRUE, TRUE, TRUE );
	}

	gtk_box_pack_start( GTK_BOX( vBoxWin ), hBox,
			TRUE, TRUE, 0 );

	// 最小ボタンの作成

	mButtonMin = gtk_button_new_with_label( "Min" );
	if( mButtonMin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonMin );

	// クリア・ボタンの作成

	mButtonClear = gtk_button_new_with_label( "Clear" );
	if( mButtonClear == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonClear );

	// 最大ボタンの作成

	mButtonMax = gtk_button_new_with_label( "Max" );
	if( mButtonMax == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonMax );

	// OK ボタンの作成

	mButtonOk = gtk_button_new_with_label( "Ok" );
	if( mButtonOk == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonOk );

	// 最小・最大ボタンへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mButtonMin ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_num_ok_clicked ),
			(gpointer)MENU_NUM_MIN );
	gtk_signal_connect( GTK_OBJECT( mButtonClear ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_num_ok_clicked ),
			(gpointer)MENU_NUM_CLR );
	gtk_signal_connect( GTK_OBJECT( mButtonMax ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_num_ok_clicked ),
			(gpointer)MENU_NUM_MAX );
	gtk_signal_connect( GTK_OBJECT( mButtonOk ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_num_ok_clicked ),
			(gpointer)MENU_NUM_OK );

	// ボックスにのせる

	GtkWidget *vBoxOk = gtk_vbox_new( FALSE, 0 );
	if( vBoxOk == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}

	gtk_box_pack_start( GTK_BOX( vBoxOk ), mButtonMin,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBoxOk ), mButtonClear,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBoxOk ), mButtonMax,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBoxOk ), mButtonOk,
			TRUE, TRUE, 0 );

	gtk_widget_show( vBoxOk );

	// ボックスにのせる

	gtk_box_pack_start( GTK_BOX( hBoxWin ), vBoxWin,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( hBoxWin ), vBoxOk,
			TRUE, TRUE, 0 );

	gtk_container_add( GTK_CONTAINER( mNumWin ), hBoxWin );
#endif	// D_GTK

#ifdef D_MFC
	mNumWin = new CInputNumDlg;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウの削除
////////////////////////////////////////////////////////////////

void GuiNum::destroy()
{
	if( mNumWin == NULL )
		return;

#ifdef D_GTK
	mNumWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	delete ((CInputNumDlg *)mNumWin);
	mNumWin = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウの表示
////////////////////////////////////////////////////////////////

void GuiNum::draw( volatile long *n, long min, long max, long figure )
{
	if( n == NULL )
		return;

	mPN = n;
	mOrg = *n;
	mMin = min;
	mMax = max;
	mFigure = figure;

	if( mNumWin == NULL )
		newWin();

#ifdef D_GTK
	redraw();

	gWinPos[WIN_KIND_INPUT_NUM].get( WIN_KIND_INPUT_NUM,
			NULL, NULL, NULL, NULL );
	gWinPos[WIN_KIND_INPUT_NUM].draw( WIN_KIND_INPUT_NUM );

	mFlagInitDone = true;
#endif // D_GTK

#ifdef D_MFC
	CInputNumDlg *dlg = (CInputNumDlg *)mNumWin;
	dlg->m_Min = mMin;
	dlg->m_Max = mMax;
	dlg->m_Org = *mPN;
	dlg->m_Cur = mPN;
	mFlagInitDone = true;

	dlg->DoModal();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウの再表示
////////////////////////////////////////////////////////////////

void GuiNum::redraw()
{
	if( mNumWin == NULL )
		newWin();

	if( mPN == NULL )
		return;

#ifdef D_GTK
	GtkAdjustment *adj;

	adj = GTK_ADJUSTMENT( mHscaleAdjustment );
	if( (long)(adj->value) != *mPN ){
		long incPage = 1;

		adj->value = (gfloat)*mPN;
		adj->lower = mMin;
		adj->upper = mMax + incPage;
		adj->step_increment = 1;
		adj->page_increment = incPage;
		adj->page_size = incPage;

		gtk_adjustment_value_changed( adj );
	}

	adj = GTK_ADJUSTMENT( mNumAdjustment );
	if( (long)(adj->value) != *mPN ){
		long incPage = 1;

		adj->value = (gfloat)*mPN;
		adj->lower = mMin;
		adj->upper = mMax + incPage;
		adj->step_increment = 1;
		adj->page_increment = incPage;
		adj->page_size = incPage;

		gtk_adjustment_value_changed( adj );
	}

	cvUpDownFromN();
#endif // D_GTK

#ifdef D_MFC
	CInputNumDlg *dlg = (CInputNumDlg *)mNumWin;

	WSCstring str;
	str = (long)*mPN;
	dlg->m_Edit.SetWindowText( str );

	dlg->SetSldrPos( *mPN );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウを閉じる
////////////////////////////////////////////////////////////////

void GuiNum::wipe()
{
#ifdef D_GTK
	if( mNumWin == NULL )
		return;

	gWinPos[WIN_KIND_INPUT_NUM].wipe( WIN_KIND_INPUT_NUM );
#endif // D_GTK

#ifdef D_MFC
	destroy();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 水平スケールとスピン・ボタンの調整の変化の処理
////////////////////////////////////////////////////////////////

void GuiNum::valueChanged( long n )
{
	if( mPN == NULL )
		return;

	if( *mPN == n )
		return;

	if( mFlagInitDone ){
		*mPN = n;
		gKey.setChar( '|' );
		redraw();
	}
}

////////////////////////////////////////////////////////////////
// ラベルの数値を増減する
// long n : ラベル番号
// long d : +1, -1 の場合は増減。0 の場合は 0 クリア
////////////////////////////////////////////////////////////////

void GuiNum::up_down_num_label( long n, long d )
{
	if( n <= -1 )
		return;
	if( n >= GUI_NUM_BUTTON_MAX_N )
		return;
	if( (n % 4) == 3 )
		return;

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	char *str = NULL;

	GtkLabel *lbl = get_label_from_button(
			GTK_BUTTON( mButtonLabel[n] ) );

	gtk_label_get( lbl, &str );
#endif // D_GTK

#ifdef D_MAC
//@@@
	char *str = NULL;
#endif // D_MAC

#ifdef D_IPHONE
//@@@
	char *str = NULL;
#endif // D_IPHONE

#ifdef D_MFC
	char str[4 + 1];

	((CInputNumDlg *)mNumWin)->m_Clr[n]
			.GetWindowText( str, 1 + 1 );
#endif // D_MFC

	if( str == NULL )
		return;

	char c = str[0];
	c = up_down_num_char( c, d );

	char num[1 + 1] = "";
	num[0] = c;
	num[1] = '\0';

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	gtk_label_set_text( lbl, num );

	if( (c == '+') || (c == '-') )
		gKey.setChar( KEY_MENU_NUM_SGN );
	else
		gKey.setChar( 'A' + (n - n / 4) );
	if( d >= +1 )
		gKey.setChar( '8' );
	else if( d <= -1 )
		gKey.setChar( '2' );
	else
		gKey.setChar( '5' );
#endif // D_GTK

#ifdef D_MFC
	((CInputNumDlg *)mNumWin)->m_Clr[n]
			.SetWindowText( num );

	cvUpDownToN();
	redraw();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 数値文字を増減する
// char c : 数値文字
// long d : +1, -1 の場合は増減。0 の場合は 0 クリア
// return : 数値文字
////////////////////////////////////////////////////////////////

char GuiNum::up_down_num_char( char c, long d )
{
	if( c == '+' ){
		c = '-';
	} else if( c == '-' ){
		c = '+';
	} else if( isdigit( c ) ){
		if( d == +-0 ){
			c = '0';
		} else {
			long n = c - '0';
			n = ((n + d) % 10 + 10) % 10;
			c = (char)n + '0';
		}
	} else {
		c = '0';
	}

	return c;
}

////////////////////////////////////////////////////////////////
// ボタン配列を数値に変換
////////////////////////////////////////////////////////////////

void GuiNum::cvUpDownToN()
{
	newWin();

	long n = 0;
	long f = 0;
	long base = 1;
	for( long i = 0; i < GUI_NUM_BUTTON_MAX_N; i++ ){
		if( f >= mFigure + 1 )
			break;
		if( (i % 4) == 3 )
			continue;
		else
			f++;

		char c;
		c = '0';

#ifdef D_GTK
		GtkLabel *lbl = get_label_from_button(
				GTK_BUTTON( mButtonLabel[i] ) );
		if( lbl == NULL )
			return;

		gchar *str = NULL;
		gtk_label_get( lbl, &str );
		if( str == NULL )
			return;
		c = str[0];
#endif // D_GTK

#ifdef D_MFC
		char str[1 + 1];
		((CInputNumDlg *)mNumWin)->m_Clr[i]
				.GetWindowText( str, 1 + 1 );
		c = str[0];
#endif // D_MFC

		if( c == '+' ){
			break;
		} else if( c == '-' ){
			n = -n;
			break;
		} else if( isdigit( c ) ){
			n += (c - '0') * base;
		}

		base *= 10;
	}

	if( mPN != NULL ){
		*mPN = n;
		gKey.setChar( '|' );
	}
}

////////////////////////////////////////////////////////////////
// ボタン配列に数値を設定
////////////////////////////////////////////////////////////////

void GuiNum::cvUpDownFromN()
{
	newWin();

	if( mPN == NULL )
		return;

#ifdef D_GTK
	GtkLabel *lbl;
	char str[1 + 1] = "";

	long n = labs( *mPN );
	long f = 0;
	long i = 0;
	for( ; i < GUI_NUM_BUTTON_MAX_N; i++ ){
		if( f >= mFigure )
			break;

		lbl = get_label_from_button(
				GTK_BUTTON( mButtonLabel[i] ) );
		if( lbl == NULL )
			continue;

		if( (i % 4) == 3 ){
			gtk_label_set_text( lbl, "," );
		} else {
			str[0] = '0' + (n % 10);
			str[1] = '\0';
			gtk_label_set_text( lbl, str );

			f++;
			n /= 10;
		}

		gtk_widget_show( mButtonLabel[i] );
		gtk_widget_show( mArrowUp[i] );
		gtk_widget_show( mButtonUp[i] );
		gtk_widget_show( mArrowDown[i] );
		gtk_widget_show( mButtonDown[i] );
	}

	if( i < GUI_NUM_BUTTON_MAX_N ){
		lbl = get_label_from_button(
				GTK_BUTTON( mButtonLabel[i] ) );
		if( lbl != NULL ){
			if( sgn_l( *mPN ) <= -1 )
				gtk_label_set_text( lbl, "-" );
			else
				gtk_label_set_text( lbl, "+" );

			gtk_widget_show( mButtonLabel[i] );
			gtk_widget_show( mArrowUp[i] );
			gtk_widget_show( mButtonUp[i] );
			gtk_widget_show( mArrowDown[i] );
			gtk_widget_show( mButtonDown[i] );

			i++;
		}
	}

	for( ; i < GUI_NUM_BUTTON_MAX_N; i++ ){
		lbl = get_label_from_button(
				GTK_BUTTON( mButtonLabel[i] ) );
		if( lbl == NULL )
			continue;
		gtk_label_set_text( lbl, "0" );

		gtk_widget_hide( mButtonLabel[i] );
		gtk_widget_hide( mArrowUp[i] );
		gtk_widget_hide( mButtonUp[i] );
		gtk_widget_hide( mArrowDown[i] );
		gtk_widget_hide( mButtonDown[i] );
	}
#endif // D_GTK

#ifdef D_MFC
	char str[1 + 1]  = "";
	CInputNumDlg *dlg = (CInputNumDlg *)mNumWin;

	long n = labs( *mPN );
	long f = 0;
	long i = 0;
	for( ; i < NUM_BTN_MAX; i++ ){
		if( f >= mFigure )
			break;

		if( (i % 4) == 3 ){
			dlg->m_Clr[i].SetWindowText( "," );
		} else {
			str[0] = '0' + (char)(n % 10);
			str[1] = '\0';
			dlg->m_Clr[i].SetWindowText( str );

			f++;
			n /= 10;
		}

		dlg->m_Clr[i].ShowWindow( SW_SHOW );
		dlg->m_Inc[i].ShowWindow( SW_SHOW );
		dlg->m_Dec[i].ShowWindow( SW_SHOW );
	}

	if( i < NUM_BTN_MAX ){
		if( sgn_l( *mPN ) <= -1 )
			dlg->m_Clr[i].SetWindowText( "-" );
		else
			dlg->m_Clr[i].SetWindowText( "+" );

		dlg->m_Clr[i].ShowWindow( SW_SHOW );
		dlg->m_Inc[i].ShowWindow( SW_SHOW );
		dlg->m_Dec[i].ShowWindow( SW_SHOW );

		i++;
	}

	for( ; i < NUM_BTN_MAX; i++ ){
		dlg->m_Clr[i].SetWindowText( "0" );

		dlg->m_Clr[i].ShowWindow( SW_HIDE );
		dlg->m_Inc[i].ShowWindow( SW_HIDE );
		dlg->m_Dec[i].ShowWindow( SW_HIDE );
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 最小・最大ボタンのクリックの処理
// menu_num_t n : ボタンの種類
////////////////////////////////////////////////////////////////

void GuiNum::okClicked( menu_num_t n )
{
	if( mPN == NULL )
		return;

	switch( n ){
	case MENU_NUM_MIN:
		*mPN = mMin;
		gKey.setChar( KEY_MENU_NUM_MIN );
		break;
	case MENU_NUM_CLR:
		*mPN = mOrg;
		gKey.setChar( KEY_MENU_NUM_CLR );
		break;
	case MENU_NUM_MAX:
		*mPN = mMax;
		gKey.setChar( KEY_MENU_NUM_MAX );
		break;
	case MENU_NUM_OK:
		gKey.setChar( '|' );
		gKey.setChar( KEY_MENU_NUM_OK );
		break;
	case MENU_NUM_MAX_N:
		return;
	}

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );

	redraw();
}

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウを閉じる処理のハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_delete( GtkWidget *widget, gpointer data )
{
	gKey.setChar( '0' );
	gGuiNum.wipe();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウの終了処理のハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_destroy( GtkWidget *widget, gpointer data )
{
	gGuiNum.wipe();
	gGuiNum.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 数値入力ウィンドウの描画イベントの処理
// GtkWidget *widget : メッセージのドローイング・エリア
// GdkEventExpose *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_expose( GtkWidget *widget, GdkEventExpose *event )
{
	gGuiNum.redraw();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 水平スケールの調整の変化のハンドラ
// GtkAdjustment *adj : 水平スケール
// gpointer data : ダミー
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_hscale_changed( GtkAdjustment *adj, gpointer data )
{
	if( adj == NULL )
		return 0;

	gGuiNum.valueChanged( (long)(adj->value) );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// スピン・ボタンの調整の変化のハンドラ
// GtkAdjustment *adj : 水平スケール
// gpointer data : ダミー
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_spin_changed( GtkAdjustment *adj, gpointer data )
{
	if( adj == NULL )
		return 0;

	gGuiNum.valueChanged( (long)(adj->value) );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// クリア・ボタン配列のクリックのハンドラ
// GtkButton *button : ボタン
// gpointer data : ボタン番号
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_0_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	if( event->button == GuiMenu::MOUSE_BUTTON_N_LEFT ){
		gGuiNum.up_down_num_label( (long)data, +-0 );
	} else if( event->button == GuiMenu::MOUSE_BUTTON_N_RIGHT ){
		gKey.setChar( '0' );
	}

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 上ボタン配列のクリックのハンドラ
// GtkButton *button : ボタン
// gpointer data : ボタン番号
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_up_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	if( event->button == GuiMenu::MOUSE_BUTTON_N_LEFT ){
		gGuiNum.up_down_num_label( (long)data, +1 );
	} else if( event->button == GuiMenu::MOUSE_BUTTON_N_RIGHT ){
		gKey.setChar( '0' );
	}

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 下ボタン配列のクリックのハンドラ
// GtkButton *button : ボタン
// gpointer data : ボタン番号
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_down_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	if( event->button == GuiMenu::MOUSE_BUTTON_N_LEFT ){
		gGuiNum.up_down_num_label( (long)data, -1 );
	} else if( event->button == GuiMenu::MOUSE_BUTTON_N_RIGHT ){
		gKey.setChar( '0' );
	}

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 最小・最大ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_num_ok_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	if( event->button == GuiMenu::MOUSE_BUTTON_N_LEFT ){
		gGuiNum.okClicked( (menu_num_t)(long)data );
	} else if( event->button == GuiMenu::MOUSE_BUTTON_N_RIGHT ){
		gKey.setChar( '0' );
	}

	return 0;
}
#endif // D_GTK
