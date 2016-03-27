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
* $Id: GuiChrSheet.cpp,v 1.34 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウ
////////////////////////////////////////////////////////////////

#define GUI_CHR_SHEET_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// イベント・ハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_destroy( GtkWidget *widget, gpointer user_data );
gint handle_expose( GtkWidget *widget, GdkEventExpose *event );

gint handle_ok_clicked(
	GtkButton *button, gpointer user_data );
gint handle_cancel_clicked(
	GtkButton *button, gpointer user_data );
gint handle_next_chr_clicked(
	GtkButton *button, gpointer user_data );
gint handle_prev_chr_clicked(
	GtkButton *button, gpointer user_data );

gint handle_stat_name_changed(
	GtkWidget *widget, GtkWidget *entry );
gint handle_stat_face_changed(
	GtkWidget *widget, GtkWidget *entry );
gint handle_stat_race_clicked(
	GtkButton *button, gpointer user_data );
gint handle_stat_race_name_changed(
	GtkWidget *widget, GtkWidget *entry );
gint handle_stat_sex_clicked(
	GtkButton *button, gpointer user_data );
gint handle_stat_tile_clicked(
	GtkButton *button, gpointer user_data );

gint handle_abl_class_clicked(
	GtkButton *button, gpointer user_data );

gint handle_skill_class_clicked(
	GtkButton *button, gpointer user_data );
gint handle_skill_name_clicked(
	GtkButton *button, gpointer user_data );
#endif // D_GTK

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウのコンストラクタ
////////////////////////////////////////////////////////////////

GuiChrSheet::GuiChrSheet()
{
	orgData = NULL;
	mbrData = NULL;
	mChrSheetWin = NULL;
}

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウのデストラクタ
////////////////////////////////////////////////////////////////

GuiChrSheet::~GuiChrSheet()
{
}

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウの初期化
////////////////////////////////////////////////////////////////

void GuiChrSheet::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウの作成
////////////////////////////////////////////////////////////////

void GuiChrSheet::newWin()
{
	if( mChrSheetWin != NULL )
		return;

#ifdef D_WS
	mChrSheetWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	newWinMisc();
	newWinStatTab();
	newWinAblTab();
	for( long i = 0; i < SKILL_MAX_PAGE; i++ )
		newWinSkillTab( i );
	newWinItemTab();
	newWinEquipTab();
#endif	// D_GTK

#ifdef D_MFC
	mChrSheetWin = new CChrSheetSheet( "Character Sheet" );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ウィンドウの作成
////////////////////////////////////////////////////////////////

void GuiChrSheet::newWinMisc()
{
#ifdef D_GTK
	// キャラクタ・シート・ウィンドウの作成

	mChrSheetWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mChrSheetWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mChrSheetWin ),
			"Character Sheet" );

	// キャラクタ・シート・ウィンドウへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mChrSheetWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_destroy ),
			this );

	// ボックスの作成

	GtkWidget *vBoxWin = gtk_vbox_new( FALSE, 0 );
	if( vBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_container_add( GTK_CONTAINER( mChrSheetWin ), vBoxWin );
	gtk_widget_show( vBoxWin );

	// 名前

	static char name[16 + MBR_NAME_MAX_BYTE + 1];
	sn_printf( name, 16 + MBR_NAME_MAX_BYTE, "name : %*s",
			MBR_NAME_MAX_LEN, " " );

	mName = gtk_label_new( name );
	if( mName == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mName,
			TRUE, TRUE, 0 );
	gtk_widget_show( mName );

	// ノートブックの作成

	mNoteBook = gtk_notebook_new();
	if( mNoteBook == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_notebook_new()" );
		return;
	}
	gtk_notebook_set_tab_pos( GTK_NOTEBOOK( mNoteBook ), GTK_POS_TOP );
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mNoteBook,
			TRUE, TRUE, 0 );
	gtk_widget_show( mNoteBook );

	// ボックスの作成

	GtkWidget *hBox = gtk_hbox_new( FALSE, 0 );
	if( hBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), hBox,
			TRUE, TRUE, 0 );
	gtk_widget_show( hBox );

	// prev chr ボタン

	mButtonPrevChr = gtk_button_new_with_label(
			MSG_MBR_DATA_PREV_MBR );
	if( mButtonPrevChr == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_signal_connect( GTK_OBJECT( mButtonPrevChr ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_prev_chr_clicked ),
			this );
	gtk_box_pack_start( GTK_BOX( hBox ), mButtonPrevChr,
			TRUE, TRUE, 0 );
	gtk_widget_show( mButtonPrevChr );

	// next chr ボタン

	mButtonNextChr = gtk_button_new_with_label(
			MSG_MBR_DATA_NEXT_MBR );
	if( mButtonNextChr == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_signal_connect( GTK_OBJECT( mButtonNextChr ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_next_chr_clicked ),
			this );
	gtk_box_pack_start( GTK_BOX( hBox ), mButtonNextChr,
			TRUE, TRUE, 0 );
	gtk_widget_show( mButtonNextChr );

	// cancel ボタン

	mButtonCancel = gtk_button_new_with_label( MSG_GUI_CANCEL );
	if( mButtonCancel == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_signal_connect( GTK_OBJECT( mButtonCancel ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_cancel_clicked ),
			this );
	gtk_box_pack_start( GTK_BOX( hBox ), mButtonCancel,
			TRUE, TRUE, 0 );
	gtk_widget_show( mButtonCancel );

	// OK ボタン

	mButtonOk = gtk_button_new_with_label( MSG_GUI_OK );
	if( mButtonOk == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_signal_connect( GTK_OBJECT( mButtonOk ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_ok_clicked ),
			this );
	gtk_box_pack_start( GTK_BOX( hBox ), mButtonOk,
			TRUE, TRUE, 0 );
	gtk_widget_show( mButtonOk );
#endif	// D_GTK
}

////////////////////////////////////////////////////////////////
// ステータス・タブの作成
////////////////////////////////////////////////////////////////

void GuiChrSheet::newWinStatTab()
{
#ifdef D_GTK
	GtkWidget *label;
	GtkWidget *sep;

	// タブのラベルを作成

	label = gtk_label_new( MSG_STAT );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_widget_show( label );

	// ボックスの作成

	GtkWidget *hBox = gtk_hbox_new( FALSE, 0 );
	if( hBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_notebook_append_page( GTK_NOTEBOOK( mNoteBook ),
			hBox, label );
	gtk_widget_show( hBox );

	// 左側のボックスの作成

	GtkWidget *vBoxLeft = gtk_vbox_new( FALSE, 0 );
	if( vBoxLeft == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( hBox ), vBoxLeft,
			TRUE, TRUE, 0 );
	gtk_widget_show( vBoxLeft );

	// セパレータの作成

	sep = gtk_vseparator_new();
	gtk_box_pack_start( GTK_BOX( hBox ), sep, TRUE, TRUE, 0 );
	gtk_widget_show( sep );

	// 右側のボックスの作成

	GtkWidget *vBoxRight = gtk_vbox_new( FALSE, 0 );
	if( vBoxRight == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( hBox ), vBoxRight,
			TRUE, TRUE, 0 );
	gtk_widget_show( vBoxRight );

	//////// 左側

	////

	long xn, yn;
	GtkWidget *pTab;
	long x, y;
	GtkAttachOptions xOpt, yOpt;

	xn = 2;
	yn = 5;
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxLeft ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	// 名前

	x = 0;
	y = 0;

	label = gtk_label_new( MSG_MBR_DATA_NAME_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( label );
	x++;

	mStatName = gtk_entry_new();
	if( mStatName == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_entry_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), mStatName,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_signal_connect( GTK_OBJECT( mStatName ),
			"changed",
			GTK_SIGNAL_FUNC( handle_stat_name_changed ),
			this );
	gtk_widget_show( mStatName );
	x++;

	y++;

	// 顔

	x = 0;

	label = gtk_label_new( MSG_MBR_DATA_FACE_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( label );
	x++;

	mStatFace = gtk_entry_new();
	if( mStatFace == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_entry_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), mStatFace,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_signal_connect( GTK_OBJECT( mStatFace ),
			"changed",
			GTK_SIGNAL_FUNC( handle_stat_face_changed ),
			this );
	gtk_widget_show( mStatFace );
	x++;

	y++;

	// 種族

	x = 0;

	label = gtk_label_new( MSG_MBR_DATA_RACE_STR_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( label );
	x++;

	static char str[RACE_STR_MAX_BYTE + 1];
	sn_printf( str, RACE_STR_MAX_BYTE, "%*s",
			RACE_STR_MAX_LEN, " " );
	mStatRace = gtk_button_new_with_label( str );
	if( mStatRace == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_signal_connect( GTK_OBJECT( mStatRace ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_stat_race_clicked ),
			this );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), mStatRace,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( mStatRace );
	x++;

	y++;

	// 種族名

	x = 0;

	label = gtk_label_new( MSG_MBR_DATA_RACE_NAME_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( label );
	x++;

	mStatRaceName = gtk_entry_new();
	if( mStatRaceName == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_entry_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), mStatRaceName,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_signal_connect( GTK_OBJECT( mStatRaceName ),
			"changed",
			GTK_SIGNAL_FUNC( handle_stat_race_name_changed ),
			this );
	gtk_widget_show( mStatRaceName );
	x++;

	y++;

	// 性別

	x = 0;

	label = gtk_label_new( MSG_MBR_DATA_SEX_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( label );
	x++;

	static char strSex[16 + 1];
	sn_printf( strSex, 16, "%*s",
			16, " " );
	mStatSex = gtk_button_new_with_label( strSex );
	if( mStatSex == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_signal_connect( GTK_OBJECT( mStatSex ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_stat_sex_clicked ),
			this );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), mStatSex,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( mStatSex );
	x++;

	y++;

	sep = gtk_hseparator_new();
	gtk_box_pack_start( GTK_BOX( vBoxLeft ), sep, TRUE, TRUE, 0 );
	gtk_widget_show( sep );

	//// HP/MP

	xn = 2;
	yn = 2;
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxLeft ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	// HP

	x = 0;

	label = gtk_label_new( MSG_MBR_DATA_HP_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( label );
	x++;

	static char strHp[10 + 1 + 10 + 1];
	sn_printf( strHp, 10 + 1 + 10, "%*s",
			10 + 1 + 10, " " );
	mStatHp = gtk_label_new( strHp );
	if( mStatHp == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), mStatHp,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( mStatHp );
	x++;

	y++;

	// MP

	x = 0;

	label = gtk_label_new( MSG_MBR_DATA_MP_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( label );
	x++;

	static char strMp[10 + 1 + 10 + 1];
	sn_printf( strMp, 10 + 1 + 10, "%*s",
			10 + 1 + 10, " " );
	mStatMp = gtk_label_new( strMp );
	if( mStatMp == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), mStatMp,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( mStatMp );
	x++;

	y++;

	sep = gtk_hseparator_new();
	gtk_box_pack_start( GTK_BOX( vBoxLeft ), sep, TRUE, TRUE, 0 );
	gtk_widget_show( sep );

	//// 戦闘能力

	xn = 3;
	yn = 1 + 3 + 3;
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxLeft ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	// タイトル

	x = 1;
	y = 0;

	label = gtk_label_new( MSG_MBR_DATA_VAL_BASH_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( label );
	x++;

	label = gtk_label_new( MSG_MBR_DATA_VAL_THROW_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
	gtk_widget_show( label );
	x++;

	n_msg_t ttl[] = {
		N_MSG_MBR_DATA_HIT_TTL,
		N_MSG_MBR_DATA_WPN_CRTCL_TTL,
		N_MSG_MBR_DATA_DAM_TTL,
		N_MSG_MBR_DATA_DEF_TTL,
		N_MSG_MBR_DATA_ARMOR_CRTCL_TTL,
		N_MSG_MBR_DATA_AC_TTL,
		N_MSG_NULL,
	};
	x = 0;
	y = 1;
	for( long i = 0; i < LOOP_MAX_100; i++ ){
		if( ttl[i] == N_MSG_NULL )
			break;

		x = 0;

		label = gtk_label_new( MSG( ttl[i] ) );
		if( label == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), label,
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				4, 0 );
		gtk_widget_show( label );
		x++;

		static char strBash[10 + 1];
		sn_printf( strBash, 10, "%*s", 10, " " );
		mStatBash[i] = gtk_label_new( strBash );
		if( mStatBash[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mStatBash[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				4, 0 );
		gtk_widget_show( mStatBash[i] );
		x++;

		if( i >= 3 ){
			y++;
			continue;
		}

		static char strThrow[10 + 1];
		sn_printf( strThrow, 10, "%*s", 10, " " );
		mStatThrow[i] = gtk_label_new( strThrow );
		if( mStatThrow[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mStatThrow[i],
				x, x + 1, y, y + 1,
				xOpt, yOpt,
				4, 0 );
		gtk_widget_show( mStatThrow[i] );
		x++;

		y++;
	}

	sep = gtk_hseparator_new();
	gtk_box_pack_start( GTK_BOX( vBoxLeft ), sep, TRUE, TRUE, 0 );
	gtk_widget_show( sep );

	//// 所持金

	static char strGold[80 + 1];
	sn_printf( strGold, 80, "%*s", 40, " " );
	mStatGold = gtk_label_new( strGold );
	if( mStatGold == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxLeft ), mStatGold, TRUE, TRUE, 0 );
	gtk_widget_show( mStatGold );

	//// 時間

	static char strTurn[80 + 1];
	sn_printf( strTurn, 80, "%*s", 40, " " );
	mStatTurn = gtk_label_new( strTurn );
	if( mStatTurn == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxLeft ), mStatTurn, TRUE, TRUE, 0 );
	gtk_widget_show( mStatTurn );

	//////// 右側

	//// 状態

	label = gtk_label_new( MSG_MBR_DATA_STAT_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxRight ), label, TRUE, TRUE, 0 );
	gtk_widget_show( label );

	//

	xn = 2;
	yn = 10;
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxRight ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	// 各状態

	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);

	long k = 0;
	for( long yy = 0; yy < STAT_MAX_N; yy++ ){
		for( long xx = 0; xx < 2; xx++ ){
			if( k >= STAT_MAX_N )
				break;

			x = xx;
			mStatStat[k] = gtk_label_new(
					MSG_MBR_DATA_STAT_NULL );
			if( mStatStat[k] == NULL ){
				print_msg( FLG_MSG_ERR, "gtk_label_new()" );
				return;
			}
			gtk_table_attach( GTK_TABLE( pTab ), mStatStat[k],
					x, x + 1, y, y + 1,
					xOpt, yOpt,
					4, 0 );
			gtk_widget_show( mStatStat[k] );

			k++;
		}
		y++;
	}

	// 明かり

	static char strLight[80 + 1];
	sn_printf( strLight, 80, "%*s", 40, " " );

	mStatLight = gtk_label_new( strLight );
	if( mStatLight == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxRight ), mStatLight,
			TRUE, TRUE, 0 );
	gtk_widget_show( mStatLight );

	// タイル

	hBox = gtk_hbox_new( FALSE, 0 );
	if( hBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxRight ), hBox, TRUE, TRUE, 0 );
	gtk_widget_show( hBox );

	label = gtk_label_new( MSG_MBR_DATA_GRAPH_FILE_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( hBox ), label, TRUE, TRUE, 0 );
	gtk_widget_show( label );

	static char strTile[80 + 1];
	sn_printf( strTile, 80, "%*s", 40, " " );
	mStatTile = gtk_button_new_with_label( strTile );
	if( mStatTile == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_signal_connect( GTK_OBJECT( mStatTile ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_stat_tile_clicked ),
			this );
	gtk_box_pack_start( GTK_BOX( hBox ), mStatTile,
			TRUE, TRUE, 0 );
	gtk_widget_show( mStatTile );
#endif	// D_GTK
}

////////////////////////////////////////////////////////////////
// 能力値タブの作成
////////////////////////////////////////////////////////////////

void GuiChrSheet::newWinAblTab()
{
#ifdef D_GTK
	GtkWidget *label;
	GtkWidget *sep;
	long xn, yn;
	GtkWidget *pTab;
	long x, y;
	GtkAttachOptions xOpt, yOpt;
	static char str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];

	// タブのラベルを作成

	label = gtk_label_new( MSG_ABL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_widget_show( label );

	// ボックスの作成

	GtkWidget *vBox = gtk_vbox_new( FALSE, 0 );
	if( vBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_notebook_append_page( GTK_NOTEBOOK( mNoteBook ),
			vBox, label );
	gtk_widget_show( vBox );

	// クラス

	sn_printf( str, CLASS_NAME_MAX_BYTE, "%*s",
			CLASS_NAME_MAX_LEN, " " );
	mAblClass = gtk_button_new_with_label( str );
	if( mAblClass == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_signal_connect( GTK_OBJECT( mAblClass ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_abl_class_clicked ),
			this );
	gtk_box_pack_start( GTK_BOX( vBox ), mAblClass, TRUE, TRUE, 0 );
	gtk_widget_show( mAblClass );

	// ボックスの作成

	GtkWidget *hBox = gtk_hbox_new( FALSE, 0 );
	if( hBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBox ), hBox, TRUE, TRUE, 0 );
	gtk_widget_show( hBox );

	//// 左側

	// ボックスの作成

	GtkWidget *vBoxLeft = gtk_vbox_new( FALSE, 0 );
	if( vBoxLeft == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( hBox ), vBoxLeft, TRUE, TRUE, 0 );
	gtk_widget_show( vBoxLeft );

	// テーブルの作成

	xn = 5;
	yn = 1 + (ABL_KIND_CHA - ABL_KIND_HP + 1);
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxLeft ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	x = 1;
	y = 0;

	// レベル

	label = gtk_label_new( MSG_MBR_DATA_LEV_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	x++;

	// 経験値

	label = gtk_label_new( MSG_MBR_DATA_EXP_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	x++;

	// 必要経験値

	label = gtk_label_new( MSG_MBR_DATA_NEED_EXP_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// 能力値

	x = 0;
	y = 0;
	for( long i = ABL_KIND_HP; i <= ABL_KIND_CHA; i++ ){
		x = 0;
		y = 1 + (i - ABL_KIND_HP);

		// 能力名

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%3s: ",
				get_abl_name( (abl_kind_t)i ) );
		label = gtk_label_new( str );
		if( label == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( label ), 0.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( label );
		x++;

		// レベル

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%4s", " " );
		mAblLev[i] = gtk_label_new( str );
		if( mAblLev[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mAblLev[i] ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mAblLev[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mAblLev[i] );
		x++;

		// レベル修整値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%6s", " " );
		mAblAddLev[i] = gtk_label_new( str );
		if( mAblAddLev[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mAblAddLev[i] ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mAblAddLev[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mAblAddLev[i] );
		x++;

		// 経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%10s", " " );
		mAblExp[i] = gtk_label_new( str );
		if( mAblExp[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mAblExp[i] ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mAblExp[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mAblExp[i] );
		x++;

		// 区切り

		label = gtk_label_new( "/" );
		if( label == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( label );
		x++;

		// 必要経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%10s", " " );
		mAblNeedExp[i] = gtk_label_new( str );
		if( mAblNeedExp[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mAblNeedExp[i] ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mAblNeedExp[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mAblNeedExp[i] );
		x++;

		y++;
	}

	//// セパレータの作成

	sep = gtk_vseparator_new();
	gtk_box_pack_start( GTK_BOX( hBox ), sep, TRUE, TRUE, 0 );
	gtk_widget_show( sep );

	//// 右側

	// ボックスの作成

	GtkWidget *vBoxRight = gtk_vbox_new( FALSE, 0 );
	if( vBoxRight == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( hBox ), vBoxRight, TRUE, TRUE, 0 );
	gtk_widget_show( vBoxRight );

	// テーブルの作成

	xn = 5;
	yn = 1 + (ABL_KIND_NIN - ABL_KIND_FIG + 1);
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxRight ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	x = 1;
	y = 0;

	// レベル

	label = gtk_label_new( MSG_MBR_DATA_LEV_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// レベルの修整値

	x++;

	// 経験値

	label = gtk_label_new( MSG_MBR_DATA_EXP_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// 区切り

	x++;

	// 必要経験値

	label = gtk_label_new( MSG_MBR_DATA_NEED_EXP_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// 能力値

	x = 0;
	y = 0;
	for( long i = ABL_KIND_FIG; i <= ABL_KIND_NIN; i++ ){
		x = 0;
		y = 1 + (i - ABL_KIND_FIG);

		// 能力名

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%3s: ",
				get_abl_name( (abl_kind_t)i ) );
		label = gtk_label_new( str );
		if( label == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( label ), 0.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( label );
		x++;

		// レベル

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%4s", " " );
		mAblLev[i] = gtk_label_new( str );
		if( mAblLev[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mAblLev[i] ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mAblLev[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mAblLev[i] );
		x++;

		// レベル修整値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%6s", " " );
		mAblAddLev[i] = gtk_label_new( str );
		if( mAblAddLev[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mAblAddLev[i] ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mAblAddLev[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mAblAddLev[i] );
		x++;

		// 経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%10s", " " );
		mAblExp[i] = gtk_label_new( str );
		if( mAblExp[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mAblExp[i] ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mAblExp[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mAblExp[i] );
		x++;

		// 区切り

		label = gtk_label_new( "/" );
		if( label == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( label );
		x++;

		// 必要経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%10s", " " );
		mAblNeedExp[i] = gtk_label_new( str );
		if( mAblNeedExp[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mAblNeedExp[i] ), 1.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mAblNeedExp[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mAblNeedExp[i] );
		x++;

		y++;
	}

	//// セパレータの作成

	sep = gtk_hseparator_new();
	gtk_box_pack_start( GTK_BOX( vBox ), sep, TRUE, TRUE, 0 );
	gtk_widget_show( sep );

	//// テーブルの作成

	xn = 1 + 3;
	yn = 1 + 3;
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBox ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	// 耐性値

	x = 0;
	y = 0;

	// -耐性-

	label = gtk_label_new( MSG_MBR_DATA_RESI_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 0.5, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );

	x = 1;
	y = 0;

	// 秩序

	label = gtk_label_new( MSG_MBR_DATA_RESI_TTL_LAWFUL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 0.5, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// 中立

	label = gtk_label_new( MSG_MBR_DATA_RESI_TTL_NEUTRAL_1 );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 0.5, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// 混沌

	label = gtk_label_new( MSG_MBR_DATA_RESI_TTL_CHAOTIC );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 0.5, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	x = 0;
	y = 1;

	// 善

	label = gtk_label_new( MSG_MBR_DATA_RESI_TTL_GOOD );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 0.5, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	y++;

	// 中立

	label = gtk_label_new( MSG_MBR_DATA_RESI_TTL_NEUTRAL_2 );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 0.5, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	y++;

	// 悪

	label = gtk_label_new( MSG_MBR_DATA_RESI_TTL_EVIL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 0.5, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	y++;

	char strResi[3][3][15 + 1];

	sn_printf( strResi[0][2], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_KNOC_TTL, 0 );
	sn_printf( strResi[1][1], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_SLAS_TTL, 0 );
	sn_printf( strResi[2][0], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_STIN_TTL, 0 );

	sn_printf( strResi[2][1], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_HEAT_TTL, 0 );
	sn_printf( strResi[0][1], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_COLD_TTL, 0 );
	sn_printf( strResi[1][2], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_MIND_TTL, 0 );
	sn_printf( strResi[1][0], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_ACID_TTL, 0 );

	sn_printf( strResi[0][0], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_ELEC_TTL, 0 );
	sn_printf( strResi[2][2], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_POIS_TTL, 0 );

	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	for( long yy = 0; yy < 3; yy++ ){
		for( long xx = 0; xx < 3; xx++ ){
			x = xx + 1;
			y = yy + 1;

			mAblResi[yy][xx] = gtk_label_new( strResi[yy][xx] );
			if( mAblResi[yy][xx] == NULL ){
				print_msg( FLG_MSG_ERR, "gtk_label_new()" );
				return;
			}
			gtk_misc_set_alignment(
					GTK_MISC( mAblResi[yy][xx] ),
					0.5, 0.5 );
			gtk_table_attach( GTK_TABLE( pTab ),
					mAblResi[yy][xx],
					x, x + 1, y, y + 1,
					xOpt, yOpt,
					4, 0 );
			gtk_widget_show( mAblResi[yy][xx] );
		}
	}
#endif	// D_GTK
}

////////////////////////////////////////////////////////////////
// スキル・タブの作成
////////////////////////////////////////////////////////////////

void GuiChrSheet::newWinSkillTab( long page )
{
#ifdef D_GTK
	GtkWidget *label;
	long xn, yn;
	GtkWidget *pTab;
	long x, y;
	GtkAttachOptions xOpt, yOpt;
	static char str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];

	// タブのラベルを作成

	if( page == 0 )
		label = gtk_label_new( MSG_SKILL_A );
	else
		label = gtk_label_new( MSG_SKILL_B );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_widget_show( label );

	// ボックスの作成

	GtkWidget *vBox = gtk_vbox_new( FALSE, 0 );
	if( vBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_notebook_append_page( GTK_NOTEBOOK( mNoteBook ),
			vBox, label );
	gtk_widget_show( vBox );

	// クラス

	sn_printf( str, CLASS_NAME_MAX_BYTE, "%*s",
			CLASS_NAME_MAX_LEN, " " );
	mSkillClass = gtk_button_new_with_label( str );
	if( mSkillClass == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_signal_connect( GTK_OBJECT( mSkillClass ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_skill_class_clicked ),
			this );
	gtk_box_pack_start( GTK_BOX( vBox ), mSkillClass, TRUE, TRUE, 0 );
	gtk_widget_show( mSkillClass );

	// テーブルの作成

	xn = 5;
	yn = 1 + SKILL_PER_PAGE_MAX_N;
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBox ), pTab, TRUE, TRUE, 0 );
	gtk_widget_show( pTab );

	x = 0;
	y = 0;

	// スキル名

	if( page == 0 )
		label = gtk_label_new( MSG_MBR_DATA_SKILL_NAME_A_TTL );
	else
		label = gtk_label_new( MSG_MBR_DATA_SKILL_NAME_B_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 0.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// レベル

	label = gtk_label_new( MSG_MBR_DATA_SKILL_LEV_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// 経験値

	label = gtk_label_new( MSG_MBR_DATA_SKILL_EXP_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// 区切り

	x++;

	// 必要経験値

	label = gtk_label_new( MSG_MBR_DATA_SKILL_NEED_EXP_TTL );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_misc_set_alignment( GTK_MISC( label ), 1.0, 0.5 );
	xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
	gtk_table_attach( GTK_TABLE( pTab ), label,
		x, x + 1, y, y + 1,
		xOpt, yOpt,
		4, 0 );
	gtk_widget_show( label );
	x++;

	// 能力値

	x = 0;
	y = 0;
	for( long i = 0; i < SKILL_PER_PAGE_MAX_N; i++ ){
		x = 0;
		y = 1 + i;

		// スキル名

		long nSlot = page * SKILL_PER_PAGE_MAX_N + i;

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%*s",
				SKILL_NAME_MAX_LEN, " " );
		mSkillName[page][i] = gtk_button_new_with_label( str );
		if( mSkillName[page][i] == NULL ){
			print_msg( FLG_MSG_ERR,
					"gtk_button_new_with_label()" );
			return;
		}
		gtk_signal_connect( GTK_OBJECT( mSkillName[page][i] ),
				"clicked",
				GTK_SIGNAL_FUNC( handle_skill_name_clicked ),
				(gpointer)nSlot );
		xOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mSkillName[page][i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mSkillName[page][i] );
		x++;

		// レベル

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%4s", " " );
		mSkillLev[page][i] = gtk_label_new( str );
		if( mSkillLev[page][i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mSkillLev[page][i] ),
				1.0, 0.5 );
		xOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mSkillLev[page][i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mSkillLev[page][i] );
		x++;

		// 経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%10s", " " );
		mSkillExp[page][i] = gtk_label_new( str );
		if( mSkillExp[page][i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mSkillExp[page][i] ),
				1.0, 0.5 );
		xOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mSkillExp[page][i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mSkillExp[page][i] );
		x++;

		// 区切り

		label = gtk_label_new( "/" );
		if( label == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( label ),
				1.0, 0.5 );
		xOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( label );
		x++;

		// 必要経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%10s", " " );
		mSkillNeedExp[page][i] = gtk_label_new( str );
		if( mSkillNeedExp[page][i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mSkillNeedExp[page][i] ),
				1.0, 0.5 );
		xOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)
				(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mSkillNeedExp[page][i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mSkillNeedExp[page][i] );
		x++;

		y++;
	}

	// ヒントのスクロール・ウィンドウを作成

	mSkillTextScroll[page] = gtk_scrolled_window_new( NULL, NULL );
	if( mSkillTextScroll[page] == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_scrolled_window_new()" );
		return;
	}
	gtk_scrolled_window_set_policy(
			GTK_SCROLLED_WINDOW( mSkillTextScroll[page] ),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );
	gtk_scrolled_window_set_shadow_type(
			GTK_SCROLLED_WINDOW( mSkillTextScroll[page] ),
			GTK_SHADOW_IN );
	gtk_box_pack_start( GTK_BOX( vBox ), mSkillTextScroll[page],
			TRUE, TRUE, 0 );
	gtk_widget_show( mSkillTextScroll[page] );

	// ヒントのビューを作成

	mSkillTextView[page] = gtk_text_view_new();
	if( mSkillTextView[page] == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_text_view_new()" );
		return;
	}
	gtk_widget_show( mSkillTextView[page] );
	gtk_container_add( GTK_CONTAINER( mSkillTextScroll[page] ),
			mSkillTextView[page] );
#endif	// D_GTK
}

////////////////////////////////////////////////////////////////
// アイテム・タブの作成
////////////////////////////////////////////////////////////////

void GuiChrSheet::newWinItemTab()
{
#ifdef D_GTK
	GtkWidget *label;

	// タブのラベルを作成

	label = gtk_label_new( MSG_ITEM );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_widget_show( label );

	// テーブルの作成

	long xn, yn;
	GtkWidget *pTab;
	long x, y;
	GtkAttachOptions xOpt, yOpt;

	xn = 2;
	yn = MBR_ITEM_MAX_N;
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_notebook_append_page( GTK_NOTEBOOK( mNoteBook ),
			pTab, label );
	gtk_widget_show( pTab );

	// アイテム

	x = 0;
	y = 0;
	static char str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	for( long i = 0; i < MBR_ITEM_MAX_N; i++ ){
		x = 0;
		y = i;

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%c)", 'A' + i );
		label = gtk_label_new( str );
		if( label == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( label ), 0.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( label );
		x++;

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%*s",
				ITEM_NAME_MAX_LEN, " " );
		mItemName[i] = gtk_label_new( str );
		if( mItemName[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mItemName[i] ), 0.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mItemName[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mItemName[i] );
		x++;

		y++;
	}
#endif	// D_GTK
}

////////////////////////////////////////////////////////////////
// 装備タブの作成
////////////////////////////////////////////////////////////////

void GuiChrSheet::newWinEquipTab()
{
#ifdef D_GTK
	GtkWidget *label;

	// タブのラベルを作成

	label = gtk_label_new( MSG_EQUIP );
	if( label == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_widget_show( label );

	// テーブルの作成

	long xn, yn;
	GtkWidget *pTab;
	long x, y;
	GtkAttachOptions xOpt, yOpt;

	xn = 3;
	yn = EQUIP_KIND_MAX_N;
	pTab = gtk_table_new( xn, yn, FALSE );
	if( pTab == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_table_new()" );
		return;
	}
	gtk_notebook_append_page( GTK_NOTEBOOK( mNoteBook ),
			pTab, label );
	gtk_widget_show( pTab );

	// 装備

	x = 0;
	y = 0;
	static char str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	for( long i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		x = 0;
		y = i;

		// 装備個所

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%s",
				get_item_equip_name( (equip_kind_t)i ) );
		label = gtk_label_new( str );
		if( label == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( label ), 0.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( label );
		x++;

		// 区切り

		label = gtk_label_new( ":");
		if( label == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( label ), 0.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), label,
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( label );
		x++;

		// 装備名

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%*s",
				ITEM_NAME_MAX_LEN, " " );
		mEquipName[i] = gtk_label_new( str );
		if( mEquipName[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_label_new()" );
			return;
		}
		gtk_misc_set_alignment( GTK_MISC( mEquipName[i] ), 0.0, 0.5 );
		xOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		yOpt = (GtkAttachOptions)(GTK_EXPAND | GTK_SHRINK | GTK_FILL);
		gtk_table_attach( GTK_TABLE( pTab ), mEquipName[i],
			x, x + 1, y, y + 1,
			xOpt, yOpt,
			4, 0 );
		gtk_widget_show( mEquipName[i] );
		x++;

		y++;
	}
#endif	// D_GTK
}

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウの削除
////////////////////////////////////////////////////////////////

void GuiChrSheet::destroy()
{
	if( mChrSheetWin == NULL )
		return;

	gKey.setChar( '0' );

#ifdef D_GTK
	mChrSheetWin = NULL;
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウの表示
// mbr_t *org : キャラクタの元データ
// mbr_t *mbr : キャラクタ
////////////////////////////////////////////////////////////////

void GuiChrSheet::draw( mbr_t *org, mbr_t *mbr )
{
	newWin();

	if( mChrSheetWin == NULL )
		return;
	if( org == NULL )
		return;
	if( mbr == NULL )
		return;

	orgData = org;
	mbrData = mbr;

#ifdef D_GTK
	gWinPos[WIN_KIND_CHR_SHEET].draw( WIN_KIND_CHR_SHEET );
	redraw();
#endif // D_GTK

#ifdef D_MFC
	DdxToSheet();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウの再表示
////////////////////////////////////////////////////////////////

void GuiChrSheet::redraw()
{
	newWin();

	if( mChrSheetWin == NULL )
		return;
	if( orgData == NULL )
		return;
	if( mbrData == NULL )
		return;

	drawMisc( orgData, mbrData );
	drawStat( orgData, mbrData );
	drawAbl( orgData, mbrData );
	for( long i = 0; i < SKILL_MAX_PAGE; i++ )
		drawSkill( orgData, mbrData, i );
	drawItem( orgData, mbrData );
	drawEquip( orgData, mbrData );

#ifdef D_GTK
#endif // D_GTK

#ifdef D_MFC
	DdxToSheet();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// DDX 変数のやり取り
////////////////////////////////////////////////////////////////

void GuiChrSheet::DdxToSheet()
{
#ifdef D_MFC
	if( mChrSheetWin == NULL )
		return;

	//// ステータス

	mChrSheetWin->m_Stat.m_StrName = mbrData->name;

	mChrSheetWin->m_Stat.m_StrNameEdit = mbrData->name;
	char strFace[8 * 2 + 1];
	strFace[0] = mbrData->face.mjr;
	strFace[1] = mbrData->face.mnr;
	strFace[0] = '\0';
	mChrSheetWin->m_Stat.m_StrFace = strFace;
	if( is_mbr( mbrData ) ){
		mChrSheetWin->m_Stat.m_StrRace
				= get_race_str( &(mbrData->race) );
		mChrSheetWin->m_Stat.m_StrRaceName
				= mbrData->race.name;
	} else {
		mChrSheetWin->m_Stat.m_StrRace
				= get_mnstr_mjr_name( mbrData->face.mjr );
		mChrSheetWin->m_Stat.m_StrRaceName
				= get_mnstr_name( mbrData->mnstr_kind );
	}
	mChrSheetWin->m_Stat.m_StrSex = get_sex_name(
			mbrData->mnstr_kind, mbrData->sex.cur );

	//// HP/MP

	const long nHpMpMaxLen = 20;
	static char strHpMp[20 + 1];

	// HP

	sn_printf( strHpMp, nHpMpMaxLen, "%4ld", mbrData->abl.hp.n );
	mChrSheetWin->m_Stat.m_StrHp[0] = strHpMp;
	sn_printf( strHpMp, nHpMpMaxLen, "%4ld", mbrData->abl.hp.max );
	mChrSheetWin->m_Stat.m_StrHp[1] = strHpMp;

	// MP

	sn_printf( strHpMp, nHpMpMaxLen, "%4ld", mbrData->abl.mp.n );
	mChrSheetWin->m_Stat.m_StrMp[0] = strHpMp;
	sn_printf( strHpMp, nHpMpMaxLen, "%4ld", mbrData->abl.mp.max );
	mChrSheetWin->m_Stat.m_StrMp[1] = strHpMp;

	//// 戦闘能力

	attack_t attack;
	long val;
	char strFight[12 + 1];

	// 近接攻撃力

	if( set_attack_mbr_bash( mbrData, &attack, 1, TRUE ) )
		val = get_hit( mbrData, &attack );
	else
		val = get_hit( mbrData, NULL );
	sn_printf( strFight, 12, "%4ld", val );
	mChrSheetWin->m_Stat.m_StrHit[0] = strFight;

	// 遠隔攻撃力

	if( set_attack_mbr_throw( mbrData, &attack, 1, TRUE ) )
		val = get_hit( mbrData, &attack );
	else
		val = get_hit( mbrData, NULL );
	sn_printf( strFight, 12, "(%4ld)", val );
	mChrSheetWin->m_Stat.m_StrHit[1] = strFight;

	// 近接クリティカル攻撃力

	if( set_attack_mbr_bash( mbrData, &attack, 1, TRUE ) )
		val = get_wpn_crtcl( mbrData, &attack );
	else
		val = get_wpn_crtcl( mbrData, NULL );
	sn_printf( strFight, 12, "%4ld", val );
	mChrSheetWin->m_Stat.m_StrWpnCrtcl[0] = strFight;

	// 遠隔クリティカル攻撃力

	if( set_attack_mbr_throw( mbrData, &attack, 1, TRUE ) )
		val = get_wpn_crtcl( mbrData, &attack );
	else
		val = get_wpn_crtcl( mbrData, NULL );
	sn_printf( strFight, 12, "(%4ld)", val );
	mChrSheetWin->m_Stat.m_StrWpnCrtcl[1] = strFight;

	// 近接ダメージ

	if( set_attack_mbr_bash( mbrData, &attack, 1, TRUE ) )
		val = get_dam( mbrData, &attack );
	else
		val = get_dam( mbrData, NULL );
	sn_printf( strFight, 12, "%4ld", val );
	mChrSheetWin->m_Stat.m_StrDam[0] = strFight;

	// 遠隔ダメージ

	if( set_attack_mbr_throw( mbrData, &attack, 1, TRUE ) )
		val = get_dam( mbrData, &attack );
	else
		val = get_dam( mbrData, NULL );
	sn_printf( strFight, 12, "(%4ld)", val );
	mChrSheetWin->m_Stat.m_StrDam[1] = strFight;

	// 防御力

	val = get_def( mbrData );
	sn_printf( strFight, 12, "%4ld", val );
	mChrSheetWin->m_Stat.m_StrDef[0] = strFight;

	// クリティカル防御力

	val = get_armor_crtcl( mbrData );
	sn_printf( strFight, 12, "%4ld", val );
	mChrSheetWin->m_Stat.m_StrArmorCrtcl[0] = strFight;

	// アーマー・クラス

	val = get_ac( mbrData );
	sn_printf( strFight, 12, "%4ld", val );
	mChrSheetWin->m_Stat.m_StrAc[0] = strFight;

	//// 所持金

	mChrSheetWin->m_Stat.m_StrGold = fmt_gold( get_chr_gold( mbrData ) );

	//// 時間

	mChrSheetWin->m_Stat.m_StrCalender = get_calendar_str();

	//// 状態

	long k = 0;

	mChrSheetWin->m_Stat.m_StrStat[k] = MSG_MBR_DATA_STAT_NULL;
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_DEAD ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_DEAD;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_STONE ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_STONE;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_PARALYZE ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_PARALYZE;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_POISON ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_POISON;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_CONFUSION ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_CONFUSION;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_BLIND ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_BLIND;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_SLEEP ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_SLEEP;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_SILENCE ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_SILENCE;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_CAUGHT ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_CAUGHT;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_FEAR ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_FEAR;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_HALLUCINATION ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_HALLUCINATION;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_CHARM ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_CHARM;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_FLY ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_FLY;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_HUNGRY ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_HUNGRY;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_STARVATION ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_STARVATION;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_FAINT ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_FAINT;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_DRUNK ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_DRUNK;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_VANISH ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_VANISH;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_IRON_BODY ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_IRON_BODY;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_PASSWALL ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_PASSWALL;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	if( chk_flg( mbrData->stat, FLG_STAT_SENSE_INVISIBLE ) ){
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_SENSE_INVISIBLE;
	} else {
		mChrSheetWin->m_Stat.m_StrStat[k]
				= MSG_MBR_DATA_STAT_NULL;
	}
	k++;

	// 明かり

	fx_t *fx = srch_fx( &(orgData->fx), FX_KIND_STORE_LIGHT );
	long store_light_n = 0;
	if( fx != NULL )
		store_light_n = fx->n;
	static char strLight[80 + 1];
	sn_printf( strLight, 40, "%ld", store_light_n );

	mChrSheetWin->m_Stat.m_StrLight = strLight;

	// タイル

	mChrSheetWin->m_Stat.m_StrGraphFile = mbrData->graph_name;

	//// 能力値

	mChrSheetWin->m_Abl.m_StrName = mbrData->name;

	if( is_mbr( mbrData ) ){
		mChrSheetWin->m_Abl.m_StrClass
				= get_class_tab()[mbrData->class_n].name;
	} else {
		mChrSheetWin->m_Abl.m_StrClass = "----";
	}

	for( long i = 0; i < ABL_KIND_MAX_N; i++ ){
		abl_kind_t kind = (abl_kind_t)i;
		long nMbrLev = get_lev( mbrData, kind );
		long nOrgLev = get_lev( orgData, kind );
		long nMbrLevMax = get_lev_max( mbrData, kind );
		long nOrgLevMax = get_lev_max( orgData, kind );

		char strAddLev[32 + 1];
		if( chk_modified_lev( mbrData, kind ) ){
			sn_printf( strAddLev, 32,
					MSG_FMT_MBR_DATA_ADD_LEV,
					nMbrLev - nMbrLevMax );
		} else {
			strAddLev[0] = '\0';
		}

		char s[32 + 1];

		sn_printf( s, 32, "%4ld", nMbrLev );
		mChrSheetWin->m_Abl.m_StrLev[i] = s;

		mChrSheetWin->m_Abl.m_StrAddLev[i] = strAddLev;

		sn_printf( s, 32, "%4ld",
				(long)(mbrData->abl.exp[i].n) );
		mChrSheetWin->m_Abl.m_StrExp[i] = s;

		sn_printf( s, 32, "%4ld",
				(long)(calc_need_exp( nMbrLev + 1, kind )) );
		mChrSheetWin->m_Abl.m_StrNeedExp[i] = s;
	}

	for( long i = 0; i < RESI_KIND_MAX_N; i++ ){
		resi_kind_t kind = (resi_kind_t)i;

		char s[32 + 1];
		sn_printf( s, 32, "%4s:%4ld", get_resi_name( kind ),
				(long)(mbrData->resi[i].n) );
		mChrSheetWin->m_Abl.m_StrResi[i] = s;
	}

	//// スキル A

	if( is_mbr( mbrData ) ){
		class_t *tab = get_class_tab();
		mChrSheetWin->m_SkillA.m_pClassTab
				= &(tab[mbrData->class_n]);
		mChrSheetWin->m_SkillA.m_nSkillHead
				= SKILL_PER_PAGE_MAX_N * 0;
		mChrSheetWin->m_SkillA.m_StrName
				= mbrData->name;
		mChrSheetWin->m_SkillA.m_StrClass
				= tab[mbrData->class_n].name;
	}

	for( long i = 0; i < SKILL_PER_PAGE_MAX_N; i++ ){
		if( !is_mbr( mbrData ) ){
			mChrSheetWin->m_SkillA.m_StrKind[i] = "";
			mChrSheetWin->m_SkillA.m_StrLev[i] = "";
			mChrSheetWin->m_SkillA.m_StrExp[i] = "";
			mChrSheetWin->m_SkillA.m_StrNeedExp[i] = "";
			continue;
		}

		long nSlot = (SKILL_PER_PAGE_MAX_N * 0) + i;
		long nLev = get_skill_lev_from_slot( mbrData, nSlot );
		long nExp = get_skill_exp_from_slot( mbrData, nSlot );
		long nNeedExp = get_skill_need_exp_from_slot( mbrData, nSlot );

		char s[32 + 1];

		mChrSheetWin->m_SkillA.m_StrKind[i]
				= get_skill_name_from_slot( mbrData, nSlot );

		sn_printf( s, 32, "%4ld", nLev );
		mChrSheetWin->m_SkillA.m_StrLev[i] = s;

		sn_printf( s, 32, "%4ld", nExp );
		mChrSheetWin->m_SkillA.m_StrExp[i] = s;

		sn_printf( s, 32, "%4ld", nNeedExp );
		mChrSheetWin->m_SkillA.m_StrNeedExp[i] = s;
	}

	//// スキル B

	if( is_mbr( mbrData ) ){
		class_t *tab = get_class_tab();
		mChrSheetWin->m_SkillB.m_pClassTab
				= &(tab[mbrData->class_n]);
		mChrSheetWin->m_SkillB.m_nSkillHead
				= SKILL_PER_PAGE_MAX_N * 1;
		mChrSheetWin->m_SkillB.m_StrName
				= mbrData->name;
		mChrSheetWin->m_SkillB.m_StrClass
				= tab[mbrData->class_n].name;
	}

	for( long i = 0; i < SKILL_PER_PAGE_MAX_N; i++ ){
		if( !is_mbr( mbrData ) ){
			mChrSheetWin->m_SkillB.m_StrKind[i] = "";
			mChrSheetWin->m_SkillB.m_StrLev[i] = "";
			mChrSheetWin->m_SkillB.m_StrExp[i] = "";
			mChrSheetWin->m_SkillB.m_StrNeedExp[i] = "";
			continue;
		}

		long nSlot = (SKILL_PER_PAGE_MAX_N * 1) + i;
		long nLev = get_skill_lev_from_slot( mbrData, nSlot );
		long nExp = get_skill_exp_from_slot( mbrData, nSlot );
		long nNeedExp = get_skill_need_exp_from_slot( mbrData, nSlot );

		char s[32 + 1];

		mChrSheetWin->m_SkillB.m_StrKind[i]
				= get_skill_name_from_slot( mbrData, nSlot );

		sn_printf( s, 32, "%4ld", nLev );
		mChrSheetWin->m_SkillB.m_StrLev[i] = s;

		sn_printf( s, 32, "%4ld", nExp );
		mChrSheetWin->m_SkillB.m_StrExp[i] = s;

		sn_printf( s, 32, "%4ld", nNeedExp );
		mChrSheetWin->m_SkillB.m_StrNeedExp[i] = s;
	}

	// アイテム

	mChrSheetWin->m_Item.m_StrName = mbrData->name;

	item_t *item;

	for( long i = 0; i < MBR_ITEM_MAX_N; i++ )
		mChrSheetWin->m_Item.m_StrItem[i] = "";

	item_t *item_head = get_mbr_item_asgn( mbrData );
	if( item_head != NULL ){
		item = item_head->next;

		for( long i = 0; i < MBR_ITEM_MAX_N; i++ ){
			if( item == NULL )
				break;
			if( item == item_head )
				break;

			mChrSheetWin->m_Item.m_StrItem[i] = item->name;

			item = item->next;
		}
	}

	// 装備

	mChrSheetWin->m_Equip.m_StrName = mbrData->name;

	for( long i = 0; i < EQUIP_KIND_MAX_N; i++ )
		mChrSheetWin->m_Equip.m_StrEquip[i] = "";

	item = get_mbr_item_asgn_equip( mbrData );
	if( item != NULL ){
		const long max_len = 80;
		char s[80 + 1];
		char *name;
		for( long i = 0; i < EQUIP_KIND_MAX_N; i++ ){
			if( item[i].kind == ITEM_KIND_NULL )
				name = "";
			else
				name = item[i].name;

			sn_printf( s, max_len, "%-*s: %-*s",
					(int)get_equip_ttl_max_len(),
					get_item_equip_name( (equip_kind_t)i ),
					(int)ITEM_NAME_MAX_LEN,
					name );

			mChrSheetWin->m_Equip.m_StrEquip[i] = s;
		}
	}

	// 表示

	mChrSheetWin->m_FlagContinue = false;

	INT_PTR res = mChrSheetWin->DoModal();

	if( !mChrSheetWin->m_FlagContinue ){
		if( res == IDCANCEL )
			*mbrData = *orgData;

		gKey.setChar( '0' );
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// DDX 変数の更新
////////////////////////////////////////////////////////////////

void GuiChrSheet::DdxFromSheet()
{
}

////////////////////////////////////////////////////////////////
// その他の項目の表示
// mbr_t *org : オリジナルのメンバー
// mbr_t *mbr : 編集中のメンバー
////////////////////////////////////////////////////////////////

void GuiChrSheet::drawMisc( mbr_t *org, mbr_t *mbr )
{
	if( org == NULL )
		return;
	if( mbr == NULL )
		return;

#ifdef D_GTK
	gtk_label_set_text( GTK_LABEL( mName ), mbr->name );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// ステータス・タブの表示
// mbr_t *org : オリジナルのメンバー
// mbr_t *mbr : 編集中のメンバー
////////////////////////////////////////////////////////////////

void GuiChrSheet::drawStat( mbr_t *org, mbr_t *mbr )
{
	if( org == NULL )
		return;
	if( mbr == NULL )
		return;

#ifdef D_GTK
	long k = 0;

	////

	static char face[8 * 2 + 1];
	face[0] = mbr->face.mjr;
	face[1] = mbr->face.mnr;
	face[2] = '\0';

	gtk_entry_set_text( GTK_ENTRY( mStatName ), mbr->name );
	gtk_entry_set_text( GTK_ENTRY( mStatFace ), face );
	if( is_mbr( mbrData ) ){
		set_label_text_button( GTK_BUTTON( mStatRace ),
				get_race_str( &(mbr->race) ),
				0.0, 0.5 );
		gtk_entry_set_text( GTK_ENTRY( mStatRaceName ),
			get_race_name( &(mbr->race) ) );
	} else {
		set_label_text_button( GTK_BUTTON( mStatRace ),
				get_mnstr_mjr_name( mbr->face.mjr ),
				0.0, 0.5 );
		gtk_entry_set_text( GTK_ENTRY( mStatRaceName ),
				get_mnstr_name( mbrData->mnstr_kind ) );
	}
	set_label_text_button( GTK_BUTTON( mStatSex ),
			get_sex_name( mbr->mnstr_kind, mbr->sex.cur ),
			0.0, 0.5 );

	//// HP/MP

	const long nHpMpMaxLen = 20;
	static char strHpMp[20 + 1];

	// HP

	sn_printf( strHpMp, nHpMpMaxLen, "%*ld/%*ld",
			4, mbr->abl.hp.n,
			4, mbr->abl.hp.max );
	gtk_label_set_text( GTK_LABEL( mStatHp ), strHpMp );

	// MP

	sn_printf( strHpMp, nHpMpMaxLen, "%*ld/%*ld",
			4, mbr->abl.mp.n,
			4, mbr->abl.mp.max );
	gtk_label_set_text( GTK_LABEL( mStatMp ), strHpMp );

	//// 戦闘能力

	k = 0;

	attack_t attack;
	long val;
	char strFight[12 + 1];

	// 近接攻撃力

	if( set_attack_mbr_bash( mbr, &attack, 1, TRUE ) )
		val = get_hit( mbr, &attack );
	else
		val = get_hit( mbr, NULL );
	sn_printf( strFight, 12, "(%4ld)", val );
	gtk_label_set_text( GTK_LABEL( mStatBash[k] ), strFight );

	// 遠隔攻撃力

	if( set_attack_mbr_throw( mbr, &attack, 1, TRUE ) )
		val = get_hit( mbr, &attack );
	else
		val = get_hit( mbr, NULL );
	sn_printf( strFight, 12, "(%4ld)", val );
	gtk_label_set_text( GTK_LABEL( mStatThrow[k] ), strFight );

	k++;

	// 近接クリティカル攻撃力

	if( set_attack_mbr_bash( mbr, &attack, 1, TRUE ) )
		val = get_wpn_crtcl( mbr, &attack );
	else
		val = get_wpn_crtcl( mbr, NULL );
	sn_printf( strFight, 12, "(%4ld)", val );
	gtk_label_set_text( GTK_LABEL( mStatBash[k] ), strFight );

	// 遠隔クリティカル攻撃力

	if( set_attack_mbr_throw( mbr, &attack, 1, TRUE ) )
		val = get_wpn_crtcl( mbr, &attack );
	else
		val = get_wpn_crtcl( mbr, NULL );
	sn_printf( strFight, 12, "(%4ld)", val );
	gtk_label_set_text( GTK_LABEL( mStatThrow[k] ), strFight );

	k++;

	// 近接ダメージ

	if( set_attack_mbr_bash( mbr, &attack, 1, TRUE ) )
		val = get_dam( mbr, &attack );
	else
		val = get_dam( mbr, NULL );
	sn_printf( strFight, 12, "(%4ld)", val );
	gtk_label_set_text( GTK_LABEL( mStatBash[k] ), strFight );

	// 遠隔ダメージ

	if( set_attack_mbr_throw( mbr, &attack, 1, TRUE ) )
		val = get_dam( mbr, &attack );
	else
		val = get_dam( mbr, NULL );
	sn_printf( strFight, 12, "(%4ld)", val );
	gtk_label_set_text( GTK_LABEL( mStatThrow[k] ), strFight );

	k++;

	// 防御力

	val = get_def( mbr );
	sn_printf( strFight, 12, "(%4ld)", val );
	gtk_label_set_text( GTK_LABEL( mStatBash[k] ), strFight );

	k++;

	// クリティカル防御力

	val = get_armor_crtcl( mbr );
	sn_printf( strFight, 12, "(%4ld)", val );
	gtk_label_set_text( GTK_LABEL( mStatBash[k] ), strFight );

	k++;

	// アーマー・クラス

	val = get_ac( mbr );
	sn_printf( strFight, 12, "(%4ld)", val );
	gtk_label_set_text( GTK_LABEL( mStatBash[k] ), strFight );

	k++;

	//// 所持金

	static char strGold[80 + 1];
	sn_printf( strGold, 40, "%s%s", MSG_MBR_DATA_GOLD_TTL,
			fmt_gold( get_chr_gold( mbr ) ) );
	gtk_label_set_text( GTK_LABEL( mStatGold ), strGold );

	//// 時間

	gtk_label_set_text( GTK_LABEL( mStatTurn ), get_calendar_str() );

	//// 状態

	k = 0;

	gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
			MSG_MBR_DATA_STAT_NULL );
	k++;

	if( chk_flg( mbr->stat, FLG_STAT_DEAD ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_DEAD );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_STONE ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_STONE );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_PARALYZE ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_PARALYZE );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_POISON ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_POISON );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_CONFUSION ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_CONFUSION );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_BLIND ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_BLIND );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_SLEEP ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_SLEEP );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_SILENCE ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_SILENCE );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_CAUGHT ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_CAUGHT );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_FEAR ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_FEAR );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_HALLUCINATION ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_HALLUCINATION );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_CHARM ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_CHARM );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_FLY ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_FLY );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_HUNGRY ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_HUNGRY );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_STARVATION ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_STARVATION );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_FAINT ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_FAINT );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_DRUNK ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_DRUNK );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_VANISH ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_VANISH );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_IRON_BODY ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_IRON_BODY );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_PASSWALL ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_PASSWALL );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 

	if( chk_flg( mbr->stat, FLG_STAT_SENSE_INVISIBLE ) ){
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_SENSE_INVISIBLE );
	} else {
		gtk_label_set_text( GTK_LABEL( mStatStat[k] ),
				MSG_MBR_DATA_STAT_NULL );
	}
	k++;

	// 明かり

	static char strLight[80 + 1];
	long store_light_n = 0;
	fx_t *fx = srch_fx( &(org->fx), FX_KIND_STORE_LIGHT );
	if( fx == NULL )
		store_light_n = 0;
	else
		store_light_n = fx->n;
	sn_printf( strLight, 40, MSG_FMT_MBR_DATA_STORE_LIGHT,
			MSG_MBR_DATA_STORE_LIGHT_TTL,
			store_light_n );

	gtk_label_set_text( GTK_LABEL( mStatLight ), strLight );

	// タイル

	set_label_text_button(
			GTK_BUTTON( mStatTile ),
			mbr->graph_name,
			0.0, 0.5 );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// 能力値タブの表示
// mbr_t *org : オリジナルのメンバー
// mbr_t *mbr : 編集中のメンバー
////////////////////////////////////////////////////////////////

void GuiChrSheet::drawAbl( mbr_t *org, mbr_t *mbr )
{
	if( org == NULL )
		return;
	if( mbr == NULL )
		return;

#ifdef D_GTK
	if( is_mbr( mbr ) ){
		class_t *class_tab = get_class_tab();
		if( class_tab != NULL ){
			set_label_text_button(
					GTK_BUTTON( mAblClass ),
					class_tab[mbr->class_n].name,
					0.5, 0.5 );
		}
	} else {
		set_label_text_button(
				GTK_BUTTON( mAblClass ),
				"----",
				0.5, 0.5 );
	}

	for( long i = 0; i < ABL_KIND_MAX_N; i++ ){
		abl_kind_t abl_kind = (abl_kind_t)i;
		long mbr_lev_n = get_lev( mbr, abl_kind );
		long mbr_lev_max = get_lev_max( mbr, abl_kind );
		static char str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
		static char str_add_lev[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];

		if( chk_modified_lev( mbr, abl_kind ) ){
			sn_printf( str_add_lev,
					SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
					MSG_FMT_MBR_DATA_ADD_LEV,
					mbr_lev_n - mbr_lev_max );
		} else {
			str_add_lev[0] = '\0';
		}

		// レベル

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%ld", mbr_lev_n );
		gtk_label_set_text( GTK_LABEL( mAblLev[i] ),
				str );

		// 修整値

		gtk_label_set_text( GTK_LABEL( mAblAddLev[i] ),
				str_add_lev );

		// 経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%ld",
				mbr->abl.exp[abl_kind].n );
		gtk_label_set_text( GTK_LABEL( mAblExp[i] ),
				str );

		// 必要経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%ld",
				calc_need_exp( mbr_lev_n + 1, abl_kind ) );
		gtk_label_set_text( GTK_LABEL( mAblNeedExp[i] ),
				str );
	}

	char strResi[3][3][15 + 1];

	sn_printf( strResi[0][2], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_KNOC_TTL,
			get_resi( mbr, RESI_KIND_KNOC ) );
	sn_printf( strResi[1][1], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_SLAS_TTL,
			get_resi( mbr, RESI_KIND_SLAS ) );
	sn_printf( strResi[2][0], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_STIN_TTL,
			get_resi( mbr, RESI_KIND_STIN ) );

	sn_printf( strResi[2][1], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_HEAT_TTL,
			get_resi( mbr, RESI_KIND_HEAT ) );
	sn_printf( strResi[0][1], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_COLD_TTL,
			get_resi( mbr, RESI_KIND_COLD ) );
	sn_printf( strResi[1][2], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_MIND_TTL,
			get_resi( mbr, RESI_KIND_MIND ) );
	sn_printf( strResi[1][0], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_ACID_TTL,
			get_resi( mbr, RESI_KIND_ACID ) );

	sn_printf( strResi[0][0], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_ELEC_TTL,
			get_resi( mbr, RESI_KIND_ELEC ) );
	sn_printf( strResi[2][2], 15, MSG_FMT_MBR_DATA_RESI,
			MSG_MBR_DATA_RESI_POIS_TTL,
			get_resi( mbr, RESI_KIND_POIS ) );

	for( long yy = 0; yy < 3; yy++ ){
		for( long xx = 0; xx < 3; xx++ ){
			gtk_label_set_text( GTK_LABEL( mAblResi[yy][xx] ),
					strResi[yy][xx] );
		}
	}
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// スキル・タブの表示
// mbr_t *org : オリジナルのメンバー
// mbr_t *mbr : 編集中のメンバー
// long page : ページ
////////////////////////////////////////////////////////////////

void GuiChrSheet::drawSkill( mbr_t *org, mbr_t *mbr, long page )
{
	if( org == NULL )
		return;
	if( mbr == NULL )
		return;

#ifdef D_GTK
	class_t *class_tab = get_class_tab();
	if( class_tab == NULL )
		return;
	if( is_mbr( mbr ) ){
		set_label_text_button(
				GTK_BUTTON( mSkillClass ),
				class_tab[mbr->class_n].name,
				0.5, 0.5 );
	} else {
		set_label_text_button(
				GTK_BUTTON( mSkillClass ),
				"----",
				0.5, 0.5 );
	}

	for( long i = 0; i < SKILL_PER_PAGE_MAX_N; i++ ){
		long nSlot = page * SKILL_PER_PAGE_MAX_N + i;

		skill_kind_t skill_kind = SKILL_KIND_NULL;
		if( is_mbr( mbr ) )
			skill_kind = class_tab[mbr->class_n].skill[nSlot];
		abl_kind_t abl_kind = (abl_kind_t)
				(ABL_KIND_MAX_N + skill_kind);
		long mbr_lev = 0;
		long mbr_exp = 0;
		long mbr_need_exp = 0;
		if( skill_kind != SKILL_KIND_NULL ){
			mbr_lev = get_lev( mbr, abl_kind );
			mbr_exp = mbr->abl.exp[abl_kind].n;
			mbr_need_exp = calc_need_exp( mbr_lev + 1,
					abl_kind );
		}
		static char str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];

		// スキル名

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%s",
				get_skill_name_from_kind( skill_kind ) );
		set_label_text_button(
				GTK_BUTTON( mSkillName[page][i] ),
				str, 0.0, 0.5 );

		// レベル

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%ld",
				mbr_lev );
		gtk_label_set_text( GTK_LABEL( mSkillLev[page][i] ),
				str );

		// 経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%ld",
				mbr_exp );
		gtk_label_set_text( GTK_LABEL( mSkillExp[page][i] ),
				str );

		// 必要経験値

		sn_printf( str, SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8,
				"%ld",
				mbr_need_exp );
		gtk_label_set_text( GTK_LABEL( mSkillNeedExp[page][i] ),
				str );
	}
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// スキルのヒントを表示
// long nSlot : スキルのスロット番号
////////////////////////////////////////////////////////////////

void GuiChrSheet::drawSkillHint( long nSlot )
{
	if( mbrData == NULL )
		return;

	class_t *class_tab = get_class_tab();
	if( class_tab == NULL )
		return;

#ifdef D_GTK
	long page = nSlot / SKILL_PER_PAGE_MAX_N;
	GtkTextBuffer *buf = gtk_text_view_get_buffer(
			GTK_TEXT_VIEW( mSkillTextView[page] ) );

	// 古いテキストを削除

	GtkTextIter cur, bgn, end;
	gtk_text_buffer_get_start_iter( buf, &bgn );
	gtk_text_buffer_get_end_iter( buf, &end );
	gtk_text_buffer_delete( buf, &bgn, &end );

	// テキストを追加

	skill_kind_t skill_kind = SKILL_KIND_NULL;
	if( is_mbr( mbrData ) )
		skill_kind = class_tab[mbrData->class_n].skill[nSlot];
	if( skill_kind == SKILL_KIND_NULL )
		return;

	const char *hint = get_skill_hint( skill_kind );
	if( hint == NULL )
		return;

	gtk_text_buffer_get_end_iter( buf, &cur );
	gtk_text_buffer_insert( buf, &cur, hint, str_len_std( hint ) );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// アイテム・タブの表示
// mbr_t *org : オリジナルのメンバー
// mbr_t *mbr : 編集中のメンバー
////////////////////////////////////////////////////////////////

void GuiChrSheet::drawItem( mbr_t *org, mbr_t *mbr )
{
	if( org == NULL )
		return;
	if( mbr == NULL )
		return;

#ifdef D_GTK
	item_t *item_head = get_mbr_item_asgn( mbr );
	if( item_head == NULL ){
		for( long i = 0; i < MBR_ITEM_MAX_N; i++ )
			gtk_label_set_text( GTK_LABEL( mItemName[i] ), "" );

		return;
	}

	item_t *item = item_head->next;

	long i;
	for( i = 0; i < MBR_ITEM_MAX_N; i++ ){
		if( item == NULL )
			break;
		if( item == item_head )
			break;

		gtk_label_set_text( GTK_LABEL( mItemName[i] ),
				item->name );

		item = item->next;
	}
	for( ; i < MBR_ITEM_MAX_N; i++ ){
		gtk_label_set_text( GTK_LABEL( mItemName[i] ), "" );
	}
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// 装備タブの表示
// mbr_t *org : オリジナルのメンバー
// mbr_t *mbr : 編集中のメンバー
////////////////////////////////////////////////////////////////

void GuiChrSheet::drawEquip( mbr_t *org, mbr_t *mbr )
{
	if( org == NULL )
		return;
	if( mbr == NULL )
		return;

#ifdef D_GTK
	item_t *item = get_mbr_item_asgn_equip( mbr );
	if( item == NULL ){
		for( long i = 0; i < EQUIP_KIND_MAX_N; i++ )
			gtk_label_set_text( GTK_LABEL( mEquipName[i] ), "" );

		return;
	}

	for( long i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		if( item[i].kind == ITEM_KIND_NULL ){
			gtk_label_set_text( GTK_LABEL( mEquipName[i] ),
					"" );
		} else {
			gtk_label_set_text( GTK_LABEL( mEquipName[i] ),
					item[i].name );
		}
	}
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウを閉じる
////////////////////////////////////////////////////////////////

void GuiChrSheet::wipe()
{
#ifdef D_GTK
	gWinPos[WIN_KIND_CHR_SHEET].wipe( WIN_KIND_CHR_SHEET );
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// OK ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiChrSheet::okClicked()
{
	gKey.setChar( '0' );
}

////////////////////////////////////////////////////////////////
// キャンセル・ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiChrSheet::cancelClicked()
{
	*mbrData = *orgData;

	gKey.setChar( '0' );
}

////////////////////////////////////////////////////////////////
// 次のキャラクタ・ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiChrSheet::nextChrClicked()
{
	gKey.setChar( '+' );
}

////////////////////////////////////////////////////////////////
// 前のキャラクタ・ボタンのクリックの処理
////////////////////////////////////////////////////////////////

void GuiChrSheet::prevChrClicked()
{
	gKey.setChar( '-' );
}

////////////////////////////////////////////////////////////////
// 名前エントリの変更の処理
////////////////////////////////////////////////////////////////

bool GuiChrSheet::nameChanged()
{
	if( mbrData == NULL )
		return false;
	if( !chk_sel_data_n( DATA_N_NAME, get_mbr_data_edit_kind() ) )
		return false;

	const char *s;

#ifdef D_GTK
	s = cut_utf_str( gtk_entry_get_text( GTK_ENTRY( mStatName ) ),
			MBR_NAME_MAX_LEN );
	str_nz_cpy( mbrData->name, s, MBR_NAME_MAX_BYTE );
#endif // D_GTK

#ifdef	D_MFC
	s = cut_utf_str( mChrSheetWin->m_Stat.m_StrNameEdit,
			MBR_NAME_MAX_LEN );
	str_nz_cpy( mbrData->name, s, MBR_NAME_MAX_BYTE );
#endif //D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// 顔エントリの変更の処理
////////////////////////////////////////////////////////////////

bool GuiChrSheet::faceChanged()
{
	if( mbrData == NULL )
		return false;
	if( !chk_sel_data_n( DATA_N_FACE, get_mbr_data_edit_kind() ) )
		return false;

#ifdef D_GTK
	const gchar *sg = gtk_entry_get_text( GTK_ENTRY( mStatFace ) );
	if( (sg != NULL) && (sg[0] != '\0') ){
		if( sg[1] == '\0' )
			mbrData->face.mnr = sg[0];
		else
			mbrData->face.mnr = sg[1];
	}
#endif // D_GTK

#ifdef	D_MFC
	const char *sm = mChrSheetWin->m_Stat.m_StrFace;
	if( (sm != NULL) && (sm[0] != '\0') ){
		if( sm[1] == '\0' )
			mbrData->face.mnr = sm[0];
		else
			mbrData->face.mnr = sm[1];
	}
#endif //D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// 種族ボタンのクリックの処理
////////////////////////////////////////////////////////////////

bool GuiChrSheet::raceClicked()
{
	if( !chk_sel_data_n( DATA_N_RACE_STR, get_mbr_data_edit_kind() ) )
		return false;

	DdxFromSheet();

	set_data_n( DATA_N_RACE_STR );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );

	return true;
}

////////////////////////////////////////////////////////////////
// 種族名エントリの変更の処理
////////////////////////////////////////////////////////////////

bool GuiChrSheet::raceNameChanged()
{
	if( mbrData == NULL )
		return false;
	if( !chk_sel_data_n( DATA_N_RACE_NAME, get_mbr_data_edit_kind() ) )
		return false;

	const char *s;

#ifdef D_GTK
	s = cut_utf_str( gtk_entry_get_text( GTK_ENTRY( mStatRaceName ) ),
			RACE_NAME_MAX_LEN );
	str_nz_cpy( mbrData->race.name, s, RACE_NAME_MAX_BYTE );
#endif // D_GTK

#ifdef	D_MFC
	s = cut_utf_str( mChrSheetWin->m_Stat.m_StrRaceName,
			RACE_NAME_MAX_LEN );
	str_nz_cpy( mbrData->race.name, s, RACE_NAME_MAX_BYTE );
#endif //D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// 性別・ボタンのクリックの処理
////////////////////////////////////////////////////////////////

bool GuiChrSheet::sexClicked()
{
	if( !chk_sel_data_n( DATA_N_SEX, get_mbr_data_edit_kind() ) )
		return false;

	DdxFromSheet();

	set_data_n( DATA_N_SEX );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );

	return true;
}

////////////////////////////////////////////////////////////////
// タイル・ボタンのクリックの処理
////////////////////////////////////////////////////////////////

bool GuiChrSheet::tileClicked()
{
	if( !chk_sel_data_n( DATA_N_GRAPH_FILE, get_mbr_data_edit_kind() ) )
		return false;

	DdxFromSheet();

	set_data_n( DATA_N_GRAPH_FILE );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );

	return true;
}

////////////////////////////////////////////////////////////////
// クラス・ボタンのクリックの処理
// return : 選択できたか?
////////////////////////////////////////////////////////////////

bool GuiChrSheet::classClicked()
{
	if( !chk_sel_data_n( DATA_N_CLASS, get_mbr_data_edit_kind() ) )
		return false;

	DdxFromSheet();

	set_data_n( DATA_N_CLASS );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );

	return true;
}

////////////////////////////////////////////////////////////////
// スキル・ボタンのクリックの処理
// long n : スキルのスロット番号
// return : 選択できたか?
////////////////////////////////////////////////////////////////

bool GuiChrSheet::skillClicked( long n )
{
	drawSkillHint( n );

	data_n_t data = (data_n_t)(DATA_N_SKILL_A_00 + n);

	DdxFromSheet();

	set_data_n( data );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );

	return true;
}

////////////////////////////////////////////////////////////////
// アイテム・ボタンのクリックの処理
// long n : アイテム番号
// return : 選択できたか?
////////////////////////////////////////////////////////////////

bool GuiChrSheet::itemClicked( long n )
{
	data_n_t data = (data_n_t)(DATA_N_ITEM_00 + n);
	if( !chk_sel_data_n( data, get_mbr_data_edit_kind() ) )
		return false;

	DdxFromSheet();

	set_data_n( data );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );

	return true;
}

////////////////////////////////////////////////////////////////
// アイテム・ボタンのクリックの処理
// long n : アイテム番号
// return : 選択できたか?
////////////////////////////////////////////////////////////////

bool GuiChrSheet::equipClicked( long n )
{
	data_n_t data = (data_n_t)(DATA_N_EQUIP_WIELDING + n);
	if( !chk_sel_data_n( data, get_mbr_data_edit_kind() ) )
		return false;

	DdxFromSheet();

	set_data_n( data );

	if( get_flg_space_select() )
		gKey.setChar( ' ' );
	else
		gKey.setChar( '\n' );

	return true;
}

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウの終了処理のハンドラ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_destroy( GtkWidget *widget, gpointer user_data )
{
	gGuiChrSheet.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウの描画イベントの処理
// GtkWidget *widget : メッセージのドローイング・エリア
// GdkEventExpose *event : イベント
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_expose( GtkWidget *widget, GdkEventExpose *event )
{
	gGuiChrSheet.redraw();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// OK ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_ok_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.okClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// キャンセル・ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_cancel_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.cancelClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 次のキャラクタ・ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_next_chr_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.nextChrClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 前のキャラクタ・ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_prev_chr_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.prevChrClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 名前エントリの変更のハンドラ
// GtkWidget *widget : ?
// GtkWidget *entry : エントリ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_name_changed(
	GtkWidget *widget, GtkWidget *entry
)
{
	gGuiChrSheet.nameChanged();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 顔エントリの変更のハンドラ
// GtkWidget *widget : ?
// GtkWidget *entry : エントリ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_face_changed(
	GtkWidget *widget, GtkWidget *entry
)
{
	gGuiChrSheet.faceChanged();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 種族ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_race_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.raceClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 種族名エントリの変更のハンドラ
// GtkWidget *widget : ?
// GtkWidget *entry : エントリ
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_race_name_changed(
	GtkWidget *widget, GtkWidget *entry
)
{
	gGuiChrSheet.raceNameChanged();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// 性別ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_sex_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.sexClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// タイル・ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_tile_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.tileClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// クラス・ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_abl_class_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.classClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// スキル・タブのクラス・ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_class_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.classClicked();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// スキル・ボタンのクリックのハンドラ
// GtkButton *button : ボタン
// gpointer user_data : ボタンの種類
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_name_clicked(
	GtkButton *button, gpointer user_data
)
{
	gGuiChrSheet.skillClicked( (long)user_data );

	return 0;
}
#endif // D_GTK
