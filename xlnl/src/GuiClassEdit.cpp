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
* $Id: GuiClassEdit.cpp,v 1.14 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// クラス・エディタ・ウィンドウ
////////////////////////////////////////////////////////////////

#define GUI_CLASS_EDIT_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// イベント・ハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_class_edit_destroy( GtkWidget *widget, gpointer user_data );

gint handle_class_edit_plus_clicked(
	GtkButton *button, gpointer user_data );
gint handle_class_edit_minus_clicked(
	GtkButton *button, gpointer user_data );
gint handle_class_edit_exit_clicked(
	GtkButton *button, gpointer user_data );
#endif // D_GTK

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

GuiClassEdit::GuiClassEdit()
{
	classData = NULL;
	mClassEditWin = NULL;
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

GuiClassEdit::~GuiClassEdit()
{
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void GuiClassEdit::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// クラス・エディタ・ウィンドウの作成
////////////////////////////////////////////////////////////////

void GuiClassEdit::newWin()
{
	if( mClassEditWin != NULL )
		return;

#ifdef D_WS
	mClassEditWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	// ウィンドウの作成

	mClassEditWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mClassEditWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mClassEditWin ),
			MSG_GUI_CLASS_EDIT_TITLE );

	// ウィンドウへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mClassEditWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_class_edit_destroy ),
			this );

	// ボックスの作成

	GtkWidget *vBoxWin = gtk_vbox_new( FALSE, 0 );
	if( vBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_container_add( GTK_CONTAINER( mClassEditWin ), vBoxWin );
	gtk_widget_show( vBoxWin );

	// エントリーを作成

	mEntryName = gtk_entry_new();
	if( mEntryName == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_entry_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mEntryName,
			FALSE, TRUE, 0 );
	gtk_widget_show( mEntryName );

	//

	GtkAttachOptions xOpt, yOpt;
	const long xn = 4 * 2;
	const long yn = ABL_KIND_MAX_N - ABL_KIND_FIG;
	GtkWidget *pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	for( long i = ABL_KIND_HP; i <= ABL_KIND_CHA; i++ ){
		long x, y;
		x = 0;
		y = i - ABL_KIND_HP;

		// 能力値ラベルの作成

		mLabelAbl[i] = gtk_label_new( get_abl_name( (abl_kind_t)i ) );
		if( mLabelAbl[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_label_new()" );
			return;
		}
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mLabelAbl[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				4, 0 );
		x++;
		gtk_widget_show( mLabelAbl[i] );

		// 値ラベルの作成

		mLabelValue[i] = gtk_label_new( "100%" );
		if( mLabelValue[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_label_new()" );
			return;
		}
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mLabelValue[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				4, 0 );
		x++;
		gtk_widget_show( mLabelValue[i] );

		// ボタンの作成

		mButtonPlus[i] = gtk_button_new_with_label( "+" );
		if( mButtonPlus[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_button_new_with_label()" );
			return;
		}

		mButtonMinus[i] = gtk_button_new_with_label( "-" );
		if( mButtonMinus[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_button_new_with_label()" );
			return;
		}

		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mButtonPlus[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				0, 0 );
		x++;
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mButtonMinus[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				0, 0 );
		x++;

		gtk_widget_show( mButtonPlus[i] );
		gtk_widget_show( mButtonMinus[i] );

		gtk_signal_connect( GTK_OBJECT( mButtonPlus[i] ),
				"clicked",
				GTK_SIGNAL_FUNC(
				handle_class_edit_plus_clicked ),
				(gpointer)i );
		gtk_signal_connect( GTK_OBJECT( mButtonMinus[i] ),
				"clicked",
				GTK_SIGNAL_FUNC(
				handle_class_edit_minus_clicked ),
				(gpointer)i );
	}
	for( long i = ABL_KIND_FIG; i <= ABL_KIND_NIN; i++ ){
		long x, y;
		x = 4;
		y = i - ABL_KIND_FIG;

		// 能力値ラベルの作成

		mLabelAbl[i] = gtk_label_new( get_abl_name( (abl_kind_t)i ) );
		if( mLabelAbl[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_label_new()" );
			return;
		}
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mLabelAbl[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				4, 0 );
		x++;
		gtk_widget_show( mLabelAbl[i] );

		// 値ラベルの作成

		mLabelValue[i] = gtk_label_new( "100%" );
		if( mLabelValue[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_label_new()" );
			return;
		}
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mLabelValue[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				4, 0 );
		x++;
		gtk_widget_show( mLabelValue[i] );

		// ボタンの作成

		mButtonPlus[i] = gtk_button_new_with_label( "+" );
		if( mButtonPlus[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_button_new_with_label()" );
			return;
		}

		mButtonMinus[i] = gtk_button_new_with_label( "-" );
		if( mButtonMinus[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_button_new_with_label()" );
			return;
		}

		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mButtonPlus[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				0, 0 );
		x++;
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mButtonMinus[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				0, 0 );
		x++;

		gtk_widget_show( mButtonPlus[i] );
		gtk_widget_show( mButtonMinus[i] );

		gtk_signal_connect( GTK_OBJECT( mButtonPlus[i] ),
				"clicked",
				GTK_SIGNAL_FUNC(
				handle_class_edit_plus_clicked ),
				(gpointer)i );
		gtk_signal_connect( GTK_OBJECT( mButtonMinus[i] ),
				"clicked",
				GTK_SIGNAL_FUNC(
				handle_class_edit_minus_clicked ),
				(gpointer)i );
	}

	// ボックスの作成

	GtkWidget *hBoxTotal = gtk_hbox_new( FALSE, 0 );
	if( hBoxTotal == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), hBoxTotal, TRUE, TRUE, 0 );
	gtk_widget_show( hBoxTotal );

	// 合計値タイトルの作成

	mLabelTotal = gtk_label_new( "Total" );
	if( mLabelTotal == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( hBoxTotal ), mLabelTotal,
			FALSE, TRUE, 4 );
	gtk_widget_show( mLabelTotal );

	// 合計値ラベルの作成

	mLabelTotalValue = gtk_label_new( "100%" );
	if( mLabelTotalValue == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( hBoxTotal ), mLabelTotalValue,
			FALSE, TRUE, 4 );
	gtk_widget_show( mLabelTotalValue );

	// 終了ボタンの作成

	mButtonExit = gtk_button_new_with_label( MSG_EDIT_CLASS_EXIT );
	if( mButtonExit == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}

	gtk_box_pack_start( GTK_BOX( vBoxWin ), mButtonExit,
			FALSE, TRUE, 0 );
	gtk_widget_show( mButtonExit );
	gtk_signal_connect( GTK_OBJECT( mButtonExit ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_class_edit_exit_clicked ),
			NULL );
#endif	// D_GTK

#ifdef D_MFC
	mClassEditWin = new CClassEditDlg;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// クラス・エディタ・ウィンドウの削除
////////////////////////////////////////////////////////////////

void GuiClassEdit::destroy()
{
	if( mClassEditWin == NULL )
		return;

#ifdef D_GTK
	mClassEditWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	delete ((CClassEditDlg *)mClassEditWin);
	mClassEditWin = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// クラス・エディタ・ウィンドウの表示
////////////////////////////////////////////////////////////////

void GuiClassEdit::draw( class_t *p )
{
	newWin();

	if( mClassEditWin == NULL )
		return;
	if( p == NULL )
		return;

	classData = p;

#ifdef D_GTK
	gWinPos[WIN_KIND_CLASS_EDIT].draw( WIN_KIND_CLASS_EDIT );
	redraw();
#endif // D_GTK

#ifdef D_MFC
	mClassEditWin->DoModal();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// クラス・エディタ・ウィンドウの再表示
////////////////////////////////////////////////////////////////

void GuiClassEdit::redraw()
{
	newWin();

	if( mClassEditWin == NULL )
		return;
	if( classData == NULL )
		return;

	// class name

#ifdef D_GTK
	GtkEntry *e;
	e = GTK_ENTRY( mEntryName );
	gtk_entry_set_text( e, classData->name );
#endif // D_GTK

#ifdef D_MFC
	mClassEditWin->mEditName = classData->name;
#endif // D_MFC

	// ability

	char str[15 + 1];
	for( long i = ABL_KIND_HP; i < ABL_KIND_MAX_N; i++ ){
		sn_printf( str, 15, "%ld%%",
				(long)(classData->abl_rate[i]) );
#ifdef D_GTK
		gtk_label_set_text( GTK_LABEL( mLabelValue[i] ), str );
#endif // D_GTK

#ifdef D_MFC
		CStatic *label = (CStatic *)mClassEditWin->GetDlgItem(
				IDC_CLASS_EDIT_HP_LABEL + i );
		label->SetWindowText( str );
#endif // D_MFC
	}

	// total

	sn_printf( str, 15, "%ld%%",
			(long)calc_abl_total( classData ) );
#ifdef D_GTK
	gtk_label_set_text( GTK_LABEL( mLabelTotalValue ), str );
#endif // D_GTK

#ifdef D_MFC
	mClassEditWin->mLabelTotalValue = str;
#endif // D_MFC

	//

#ifdef D_MFC
	mClassEditWin->UpdateData( false );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// クラス・エディタ・ウィンドウを閉じる
////////////////////////////////////////////////////////////////

void GuiClassEdit::wipe()
{
#ifdef D_GTK
	gWinPos[WIN_KIND_CLASS_EDIT].wipe( WIN_KIND_CLASS_EDIT );
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 編集したクラス名を保存する
////////////////////////////////////////////////////////////////

void	GuiClassEdit::setClassName()
{
#ifdef D_GTK
	const gchar *name = cut_utf_str( gtk_entry_get_text( GTK_ENTRY( mEntryName ) ),
			CLASS_NAME_MAX_LEN );
	str_nz_cpy( classData->name, name, CLASS_NAME_MAX_BYTE );
#endif // D_GTK

#ifdef D_MFC
	mClassEditWin->UpdateData( TRUE );
	const char *sName = cut_utf_str( mClassEditWin->mEditName,
			MBR_NAME_MAX_LEN );
	str_nz_cpy( classData->name, sName, CLASS_NAME_MAX_BYTE );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// + ボタンのクリックの処理
// abl_kind_t kind : 能力値の種類
////////////////////////////////////////////////////////////////

void GuiClassEdit::plusClicked( abl_kind_t kind )
{
	add( kind, +1 );
}

////////////////////////////////////////////////////////////////
// - ボタンのクリックの処理
// abl_kind_t kind : 能力値の種類
////////////////////////////////////////////////////////////////

void GuiClassEdit::minusClicked( abl_kind_t kind )
{
	add( kind, -1 );
}

////////////////////////////////////////////////////////////////
// 値の増減
// abl_kind_t kind : 能力値の種類
// long n : 増減数
////////////////////////////////////////////////////////////////

void GuiClassEdit::add( abl_kind_t kind, long n )
{
	setClassName();

	edit_class_t ec;
	if( kind < ABL_KIND_FIG )
		ec = (edit_class_t)(EDIT_CLASS_HP + (kind - ABL_KIND_HP));
	else
		ec = (edit_class_t)(EDIT_CLASS_FIG + (kind - ABL_KIND_FIG));

	menu_edit_class_inc_abl( classData, ec, n );

	redraw();
}

////////////////////////////////////////////////////////////////
// 終了ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiClassEdit::exitClicked()
{
	setClassName();

	gKey.setChar( '0' );
}

////////////////////////////////////////////////////////////////
// クラス・エディタ・ウィンドウの終了処理のハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_class_edit_destroy( GtkWidget *widget, gpointer user_data )
{
	gGuiClassEdit.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// + ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_class_edit_plus_clicked(
	GtkButton *button, gpointer user_data )
{
	gGuiClassEdit.plusClicked( (abl_kind_t)(long)user_data );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// - ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_class_edit_minus_clicked(
	GtkButton *button, gpointer user_data )
{
	gGuiClassEdit.minusClicked( (abl_kind_t)(long)user_data );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 終了ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_class_edit_exit_clicked(
	GtkButton *button, gpointer user_data )
{
	gGuiClassEdit.exitClicked();

	return 0;
}
#endif // D_GTK
