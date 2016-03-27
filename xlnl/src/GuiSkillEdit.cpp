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
* $Id: GuiSkillEdit.cpp,v 1.12 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// スキル・エディタ・ウィンドウ
////////////////////////////////////////////////////////////////

#define GUI_SKILL_EDIT_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// イベント・ハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_edit_destroy( GtkWidget *widget, gpointer user_data );

gint handle_skill_edit_skill_clicked(
	GtkButton *button, gpointer user_data );
gint handle_skill_edit_prev_clicked(
	GtkButton *button, gpointer user_data );
gint handle_skill_edit_next_clicked(
	GtkButton *button, gpointer user_data );
gint handle_skill_edit_exit_clicked(
	GtkButton *button, gpointer user_data );
#endif // D_GTK

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

GuiSkillEdit::GuiSkillEdit()
{
	classData = NULL;
	mSkillEditWin = NULL;
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

GuiSkillEdit::~GuiSkillEdit()
{
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void GuiSkillEdit::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// スキル・エディタ・ウィンドウの作成
////////////////////////////////////////////////////////////////

void GuiSkillEdit::newWin()
{
	if( mSkillEditWin != NULL )
		return;

#ifdef D_WS
	mSkillEditWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	// ウィンドウの作成

	mSkillEditWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mSkillEditWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mSkillEditWin ),
			MSG_GUI_SKILL_EDIT_TITLE );

	// ウィンドウへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mSkillEditWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_skill_edit_destroy ),
			this );

	// ボックスの作成

	GtkWidget *vBoxWin = gtk_vbox_new( FALSE, 0 );
	if( vBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_container_add( GTK_CONTAINER( mSkillEditWin ), vBoxWin );
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
	const long xn = 2 * 2;
	const long yn = SKILL_PER_PAGE_MAX_N;
	GtkWidget *pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	for( long i = 0; i < SKILL_MAX_N; i++ ){
		long x, y;
		x = 2 * (i / SKILL_PER_PAGE_MAX_N);
		y = i % SKILL_PER_PAGE_MAX_N;

		// スキル・ボタンの作成

		mButtonSkill[i] = gtk_button_new_with_label( "----" );
		if( mButtonSkill[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_button_new_with_label()" );
			return;
		}

		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mButtonSkill[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				0, 0 );
		x++;

		gtk_widget_show( mButtonSkill[i] );

		gtk_signal_connect( GTK_OBJECT( mButtonSkill[i] ),
				"clicked",
				GTK_SIGNAL_FUNC(
				handle_skill_edit_skill_clicked ),
				(gpointer)i );

		// 値ラベルの作成

		mLabelRate[i] = gtk_label_new( "100%" );
		if( mLabelRate[i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_label_new()" );
			return;
		}
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mLabelRate[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				4, 0 );
		x++;
		gtk_widget_show( mLabelRate[i] );
	}

	// ヒント・ラベルの作成

	mLabelHint = gtk_label_new( "" );
	if( mLabelHint == NULL ){
		print_msg( FLG_MSG_ERR,
				"gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mLabelHint,
			FALSE, TRUE, 2 );
	gtk_widget_show( mLabelHint );

	// ボックスの作成

	GtkWidget *hBox = gtk_hbox_new( FALSE, 0 );
	if( hBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), hBox,
			FALSE, TRUE, 0 );
	gtk_widget_show( hBox );

	// 前ボタンの作成

	mButtonPrev = gtk_button_new_with_label( MSG_EDIT_CLASS_PREV );
	if( mButtonPrev == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}

	gtk_box_pack_start( GTK_BOX( hBox ), mButtonPrev,
			TRUE, TRUE, 0 );
	gtk_widget_show( mButtonPrev );
	gtk_signal_connect( GTK_OBJECT( mButtonPrev ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_skill_edit_prev_clicked ),
			NULL );

	// 次ボタンの作成

	mButtonNext = gtk_button_new_with_label( MSG_EDIT_CLASS_NEXT );
	if( mButtonNext == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}

	gtk_box_pack_start( GTK_BOX( hBox ), mButtonNext,
			TRUE, TRUE, 0 );
	gtk_widget_show( mButtonNext );
	gtk_signal_connect( GTK_OBJECT( mButtonNext ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_skill_edit_next_clicked ),
			NULL );

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
			GTK_SIGNAL_FUNC( handle_skill_edit_exit_clicked ),
			NULL );
#endif	// D_GTK

#ifdef D_MFC
	mSkillEditWin = new CSkillEditDlg;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// スキル・エディタ・ウィンドウの削除
////////////////////////////////////////////////////////////////

void GuiSkillEdit::destroy()
{
	if( mSkillEditWin == NULL )
		return;

#ifdef D_GTK
	mSkillEditWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	delete ((CSkillEditDlg *)mSkillEditWin);
	mSkillEditWin = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// スキル・エディタ・ウィンドウの表示
////////////////////////////////////////////////////////////////

void GuiSkillEdit::draw( class_t *p )
{
	newWin();

	if( mSkillEditWin == NULL )
		return;
	if( p == NULL )
		return;

	classData = p;

#ifdef D_GTK
	gWinPos[WIN_KIND_SKILL_EDIT].draw( WIN_KIND_SKILL_EDIT );
	redraw();
#endif // D_GTK

#ifdef D_MFC
	mSkillEditWin->DoModal();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// スキル・エディタ・ウィンドウの再表示
////////////////////////////////////////////////////////////////

void GuiSkillEdit::redraw()
{
	newWin();

	if( mSkillEditWin == NULL )
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
	mSkillEditWin->mEditName = classData->name;
#endif // D_MFC

	// ability

	for( long i = 0; i < SKILL_MAX_N; i++ ){
		skill_kind_t skillKind = classData->skill[i];

		const char *skillName = get_skill_name_from_kind(
				skillKind );

		rate_t rate = calc_skill_exp_rate(
				classData, skillKind );
		char sRate[15 + 1];
		sn_printf( sRate, 15, "%ld%%", (long)rate );

#ifdef D_GTK
		set_label_text_button( GTK_BUTTON( mButtonSkill[i] ),
				skillName, 0.0, 0.5 );
		gtk_label_set_text( GTK_LABEL( mLabelRate[i] ), sRate );
#endif // D_GTK

#ifdef D_MFC
		CButton *btn = (CButton *)mSkillEditWin->GetDlgItem(
				IDC_SKILL_EDIT_SKILL_00 + i );
		btn->SetWindowText( skillName );

		CStatic *label = (CStatic *)mSkillEditWin->GetDlgItem(
				IDC_SKILL_EDIT_RATE_00 + i );
		label->SetWindowText( sRate );
#endif // D_MFC
	}

	// hint

	long nSlot = -1;
	edit_skill_t n = get_edit_skill_n();
	if( (EDIT_SKILL_A_00 <= n) && (n <= EDIT_SKILL_A_09) )
		nSlot = n - EDIT_SKILL_A_00;
	if( (EDIT_SKILL_B_00 <= n) && (n <= EDIT_SKILL_B_09) )
		nSlot = n - EDIT_SKILL_B_00 + SKILL_PER_PAGE_MAX_N;

	skill_kind_t mSkillKind = SKILL_KIND_NULL;
	if( nSlot > -1 )
		mSkillKind = classData->skill[nSlot];

#ifdef D_GTK
	gtk_label_set_text( GTK_LABEL( mLabelHint ),
			get_skill_hint( mSkillKind ) );
#endif // D_GTK

#ifdef D_MFC
	CStatic *label = (CStatic *)mSkillEditWin->GetDlgItem(
			IDC_SKILL_EDIT_HINT );
	label->SetWindowText( get_skill_hint( mSkillKind ) );
#endif // D_MFC

	// ページ切り替え

#ifdef D_MFC
	CButton *btn;

	btn = (CButton *)mSkillEditWin->GetDlgItem(
			IDC_SKILL_EDIT_PREV );
	btn->SetWindowText( MSG_EDIT_CLASS_PREV );

	btn = (CButton *)mSkillEditWin->GetDlgItem(
			IDC_SKILL_EDIT_NEXT );
	btn->SetWindowText( MSG_EDIT_CLASS_NEXT );
#endif // D_MFC

	// end

#ifdef D_MFC
	mSkillEditWin->UpdateData( false );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// スキル・エディタ・ウィンドウを閉じる
////////////////////////////////////////////////////////////////

void GuiSkillEdit::wipe()
{
#ifdef D_GTK
	gWinPos[WIN_KIND_SKILL_EDIT].wipe( WIN_KIND_SKILL_EDIT );
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 編集したクラス名を保存する
////////////////////////////////////////////////////////////////

void	GuiSkillEdit::setClassName()
{
#ifdef D_GTK
	const gchar *name = gtk_entry_get_text(
			GTK_ENTRY( mEntryName ) );

	str_nz_cpy( classData->name, name, CLASS_NAME_MAX_BYTE );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// スキル・ボタンのクリックの処理
// long nSlot : スロット番号
////////////////////////////////////////////////////////////////

void GuiSkillEdit::skillClicked( long nSlot )
{
	setClassName();

	long n;
	if( nSlot < SKILL_PER_PAGE_MAX_N )
		n = EDIT_SKILL_A_00 + (nSlot % SKILL_PER_PAGE_MAX_N);
	else
		n = EDIT_SKILL_B_00 + (nSlot % SKILL_PER_PAGE_MAX_N);

	set_edit_skill_n( (edit_skill_t)n );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );
}

////////////////////////////////////////////////////////////////
// 前ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiSkillEdit::prevClicked()
{
	setClassName();

	set_edit_skill_n( EDIT_SKILL_PREV );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );
}

////////////////////////////////////////////////////////////////
// 次ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiSkillEdit::nextClicked()
{
	setClassName();

	set_edit_skill_n( EDIT_SKILL_NEXT );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );
}

////////////////////////////////////////////////////////////////
// 終了ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiSkillEdit::exitClicked()
{
	setClassName();

	gKey.setChar( '0' );
}

////////////////////////////////////////////////////////////////
// スキル・エディタ・ウィンドウの終了処理のハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_edit_destroy( GtkWidget *widget, gpointer user_data )
{
	gGuiSkillEdit.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// スキル・ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_edit_skill_clicked(
	GtkButton *button, gpointer user_data )
{
	gGuiSkillEdit.skillClicked( (long)user_data );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 前ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_edit_prev_clicked(
	GtkButton *button, gpointer user_data )
{
	gGuiSkillEdit.prevClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 次ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_edit_next_clicked(
	GtkButton *button, gpointer user_data )
{
	gGuiSkillEdit.nextClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 終了ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ユーザ・データ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_edit_exit_clicked(
	GtkButton *button, gpointer user_data )
{
	gGuiSkillEdit.exitClicked();

	return 0;
}
#endif // D_GTK
