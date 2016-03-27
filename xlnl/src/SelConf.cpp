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
* $Id: SelConf.cpp,v 1.20 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// グラフィック設定の選択
////////////////////////////////////////////////////////////////

#define	SEL_CONF_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define STR_GRAPH_CONF_FILE_NAME	"xlnl-conf.txt"

#define SEL_CONF_WIN_MODAL	0

////////////////////////////////////////////////////////////////

#ifdef D_GTK

void handle_sel_conf_win_destroy(
	GtkWidget *widget, gpointer data
);

void handle_sel_conf_select(
	GtkList *list, GtkWidget *widget, gpointer data
);
void handle_sel_conf_ok_clicked(
	GtkWidget *widget, gpointer data
);
void handle_sel_conf_cancel_clicked(
	GtkWidget *widget, gpointer data
);
gint handle_sel_conf_d_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);

void sel_conf_ok_clicked( GtkWidget *data );

#endif // D_GTK

////////////////////////////////////////////////////////////////
// 選択のコンストラクタ
////////////////////////////////////////////////////////////////

SelConf::SelConf()
{
	pGraphConfSel = NULL;

#ifdef D_GTK
	mSelConfWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	bFlagUseWin32ApiFind = true;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 選択のデストラクタ
////////////////////////////////////////////////////////////////

SelConf::~SelConf()
{
	GraphConf *next;

	for( GraphConf *p = mGraphConfHead.getNext();
			p != NULL; p = next ){
		if( p == &mGraphConfHead )
			break;

		next = p->getNext();

		delete p;
	}
}

////////////////////////////////////////////////////////////////
// 選択の初期化
////////////////////////////////////////////////////////////////

void SelConf::init()
{
	newWin();

	makeList();

#ifdef D_GTK
	setListGui();
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// 選択ウィンドウの作成
////////////////////////////////////////////////////////////////

void SelConf::newWin()
{
#ifdef D_GTK
	if( mSelConfWin != NULL )
		return;

	// 選択ウィンドウの作成

	mSelConfWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mSelConfWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mSelConfWin ),
			"Select configure" );

	// 選択ウィンドウへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( mSelConfWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_sel_conf_win_destroy ),
			this );

	// 垂直ボックスの作成

	vBox = gtk_vbox_new( FALSE, 0 );
	gtk_container_add( GTK_CONTAINER( mSelConfWin ), vBox );
	gtk_widget_show( vBox );

	// ラベルの作成

	labelList = gtk_label_new( MSG_SEL_CONF_LABEL );
	gtk_box_pack_start( GTK_BOX( vBox ), labelList, FALSE, TRUE, 0 );
	gtk_widget_show( labelList );

	// スクロール・ウィンドウを作成

	scrollWin = gtk_scrolled_window_new( NULL, NULL );
	if( scrollWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_scrolled_window_new()" );
		return;
	}
	gtk_scrolled_window_set_policy(
			GTK_SCROLLED_WINDOW( scrollWin ),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );
	gtk_scrolled_window_set_shadow_type(
			GTK_SCROLLED_WINDOW( scrollWin ),
			GTK_SHADOW_IN );
	gtk_box_pack_start( GTK_BOX( vBox ), scrollWin, TRUE, TRUE, 0 );
	gtk_widget_show( scrollWin );

	// リスト・ボックスの作成

	lsList = gtk_list_new();
	gtk_scrolled_window_add_with_viewport(
			GTK_SCROLLED_WINDOW( scrollWin ), lsList );
	gtk_widget_show( lsList );

	// リスト・ボックスへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( lsList ),
			"select-child",
			GTK_SIGNAL_FUNC( handle_sel_conf_select ),
			this );

	// 水平ボックスの作成

	hBox = gtk_hbox_new( FALSE, 0 );
	gtk_box_pack_start( GTK_BOX( vBox ), hBox, FALSE, TRUE, 0 );
	gtk_widget_show( hBox );

	// 選択ボタンの作成

	btnSelConfOk = gtk_button_new_with_label(
			MSG_SEL_CONF_OK );
	btnSelConfCancel = gtk_button_new_with_label(
			MSG_SEL_CONF_CANCEL );

	// デフォルト・ボタンに設定
	GTK_WIDGET_SET_FLAGS( btnSelConfOk, GTK_CAN_DEFAULT );

	gtk_box_pack_end( GTK_BOX( hBox ), btnSelConfOk,
			FALSE, TRUE, 0 );
	gtk_box_pack_end( GTK_BOX( hBox ), btnSelConfCancel,
			FALSE, TRUE, 0 );

	// デフォルト・ボタンに設定
	gtk_widget_grab_default( btnSelConfOk );

	gtk_widget_show( btnSelConfOk );
	gtk_widget_show( btnSelConfCancel );

	// 選択ボタンへのイベント・ハンドラを設定

	gtk_signal_connect( GTK_OBJECT( btnSelConfOk ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_sel_conf_ok_clicked ),
			mSelConfWin );
	gtk_signal_connect( GTK_OBJECT( btnSelConfCancel ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_sel_conf_cancel_clicked ),
			NULL );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// 選択ウィンドウの削除
////////////////////////////////////////////////////////////////

void SelConf::destroy()
{
#ifdef D_GTK
	gtk_widget_destroy( btnSelConfCancel );
	gtk_widget_destroy( btnSelConfOk );
	gtk_widget_destroy( hBox );
	gtk_widget_destroy( vBox );

	gtk_widget_destroy( mSelConfWin );
	mSelConfWin = NULL;
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// 選択ウィンドウの表示
////////////////////////////////////////////////////////////////

void SelConf::draw()
{
	newWin();

#ifdef D_GTK
	if( mSelConfWin == NULL )
		return;

	gtk_grab_add( mSelConfWin );
	gWinPos[WIN_KIND_SEL_CONF].draw( WIN_KIND_SEL_CONF );

# if SEL_CONF_WIN_MODAL
	gtk_main();
# endif // SEL_CONF_WIN_MODAL
#endif // D_GTK

#ifdef D_MFC
	while( 1 ){
		INT_PTR res = mDlg.DoModal();

		if( res == IDOK ){
			if( pGraphConfSel == NULL )
				continue;

			// メイン処理の初期化を続ける
			init_main_sel_conf( pGraphConfSel );
		} else {
			exit_game( EXIT_FAILURE );
		}

		break;
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 選択ウィンドウを閉じる
////////////////////////////////////////////////////////////////

void SelConf::wipe()
{
#ifdef D_GTK
	gWinPos[WIN_KIND_SEL_CONF].wipe( WIN_KIND_SEL_CONF );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// 設定ファイルを検索してリストを作る
////////////////////////////////////////////////////////////////

void SelConf::makeList()
{
	if( !openDir() )
		return;

	while( 1 ){
		WSCstring sConfName = nextDir();
		if( sConfName == "" )
			break;

		load_graph_conf( sConfName );
	}

	if( !closeDir() )
		return;
}

////////////////////////////////////////////////////////////////
// 設定のリストを GUI に登録
////////////////////////////////////////////////////////////////

void SelConf::setListGui()
{
	long n = 0;
	for( GraphConf *p = mGraphConfHead.getNext();
			p != NULL; p = p->getNext() ){
		if( p == &mGraphConfHead )
			break;

		WSCstring sDirTmp = p->getDir();
		long w = sDirTmp.getWords( "/" );
		WSCstring sDirName = sDirTmp.getWord( w - 1, "/" );

		WSCstring sNum( n );

		WSCstring sTitle = "";
		sTitle += sDirName;
		sTitle += STR_WORD_SEP_SEL_CONF;
		sTitle += sNum;
		sTitle += STR_WORD_SEP_SEL_CONF;
		sTitle += p->getStr( GRAPH_CONF_TOKEN_TITLE );

#ifdef D_GTK
		GtkWidget *wListItem;
		wListItem = gtk_list_item_new_with_label( sTitle );
		gtk_container_add( GTK_CONTAINER( lsList ), wListItem );

		gtk_signal_connect( GTK_OBJECT( wListItem ),
				"button_press_event",
				GTK_SIGNAL_FUNC( handle_sel_conf_d_clicked ),
				mSelConfWin );

		gtk_widget_show( wListItem );
#endif // D_GTK

#ifdef D_MFC
		mDlg.m_List.AddString( sTitle );
#endif // D_MFC

		n++;
	}

#ifdef D_GTK
	gtk_list_set_selection_mode( GTK_LIST( lsList ),
			GTK_SELECTION_SINGLE );
	if( n > 0 )
		gtk_list_select_item( GTK_LIST( lsList ), n - 1 );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// 設定ディレクトリを番号で選択
////////////////////////////////////////////////////////////////

void SelConf::select( long n )
{
	pGraphConfSel = NULL;

	GraphConf *p = mGraphConfHead.getNext();
	for( long i = 0; ; i++ ){
		if( p == NULL )
			break;
		if( p == &mGraphConfHead )
			break;

		if( i == n ){
			pGraphConfSel = p;
			break;
		}

		p = p->getNext();
	}
}

////////////////////////////////////////////////////////////////
// 設定ディレクトリを開く
////////////////////////////////////////////////////////////////

bool SelConf::openDir()
{
#ifdef D_MFC
	bFlagOpen = false;
#else // D_MFC
	dpFile = NULL;
#endif // D_MFC

	sDir = FileList::jointDir( get_home_dir(), STR_DIR_BASE_GRAPH );

#ifdef D_MFC
	WSCstring path = FileList::jointDir( sDir, "*.*" );
	path.replaceString( "/", "\\", 0 );

	if( bFlagUseWin32ApiFind ){
		ZeroMemory( &findData, sizeof( findData ) );
		hFindFile = ::FindFirstFile( path, &findData );
		if( hFindFile == INVALID_HANDLE_VALUE )
			return false;

		findData.dwFileAttributes = 0
				| FILE_ATTRIBUTE_DIRECTORY
				| FILE_ATTRIBUTE_READONLY
				;
	} else {
		if( !finder.FindFile( path ) )
			return false;

# if 0
//@@@
		finder.MatchesMask( 0
				| FILE_ATTRIBUTE_DIRECTORY
				| FILE_ATTRIBUTE_READONLY
		);
# endif
	}

	bFlagOpen = true;
#else // D_MFC
	dpFile = opendir( sDir );
	if( dpFile == NULL )
		return false;
#endif // D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// 設定ディレクトリを閉じる
////////////////////////////////////////////////////////////////

bool SelConf::closeDir()
{
#ifdef D_MFC
	if( bFlagOpen ){
		if( bFlagUseWin32ApiFind )
			::FindClose( hFindFile );
		else
			finder.Close();

		bFlagOpen = false;
	}
#else // D_MFC
	if( dpFile != NULL ){
		closedir( dpFile );
		dpFile = NULL;
	}
#endif // D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// 次の設定ディレクトリを検索
// return : 見つかったディレクトリの絶対パス
////////////////////////////////////////////////////////////////

WSCstring SelConf::nextDir()
{
#ifdef D_MFC
	if( !bFlagOpen )
		return "";
#else // D_MFC
	if( dpFile == NULL )
		return "";
#endif // D_MFC

	WSCstring sConfPath;

	while( 1 ){
		WSCstring name;

#ifdef D_MFC
		if( bFlagUseWin32ApiFind ){
			if( !::FindNextFile( hFindFile, &findData ) )
				return "";

			if( !(findData.dwFileAttributes
					& (FILE_ATTRIBUTE_DIRECTORY)) ){
				continue;
			}

			name = FileList::jointDir(
					sDir, findData.cFileName );
		} else {
			if( !finder.FindNextFile() )
				return "";

			if( !finder.IsDirectory() )
				continue;

			name = finder.GetFilePath();
		}
#else // D_MFC
		struct dirent *buf = readdir( dpFile );
		if( buf == NULL )
			return "";

		WSCstring fileName = buf->d_name;
		name = FileList::jointDir( sDir, fileName );

		struct stat statBuf;
		stat( name, &statBuf );
		if( !S_ISDIR( statBuf.st_mode ) )
			continue;
#endif // D_MFC

		sConfPath = FileList::jointDir(
				name, STR_GRAPH_CONF_FILE_NAME);

		FILE *fp;
		fp = fopen( sConfPath, "r" );
		if( fp == NULL )
			continue;
		fclose( fp );

		sDirName = name;
#ifdef D_MFC
		sDirName.replaceString( "\\", "/", 0 );
#endif // D_MFC

		break;
	}

#ifdef D_MFC
	sConfPath.replaceString( "\\", "/", 0 );
#endif // D_MFC
#ifdef D_DOWS
	sConfPath.replaceString( "\\", "/", 0 );
#endif // D_DOWS

	return sConfPath;
}

////////////////////////////////////////////////////////////////
// 設定ファイルの文を解釈 (ブロック開始)
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool SelConf::evalBlockBegin()
{
	if( pGraphConfCur == NULL ){
		mGraphConfHead.setHead();
		pGraphConfCur = &mGraphConfHead;
	}

	GraphConf *p = new GraphConf();
	if( p == NULL )
		return false;

	p->setDir( sDirName );

	p->insert( pGraphConfCur );
	pGraphConfCur = p;

	return true;
}

////////////////////////////////////////////////////////////////
// 設定ファイルの文を解釈 (ブロック終了)
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool SelConf::evalBlockEnd()
{
	return true;
}

////////////////////////////////////////////////////////////////
// 設定ファイルの文を解釈 (数値)
// GraphConfToken token : トークン
// long n : 数値
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool SelConf::evalSetNum( GraphConfToken token, long n )
{
	if( pGraphConfCur == NULL )
		evalBlockBegin();
	if( pGraphConfCur == NULL )
		return false;

	return pGraphConfCur->setNum( token, n );
}

////////////////////////////////////////////////////////////////
// 設定ファイルの文を解釈 (文字列)
// GraphConfToken token : トークン
// WSCstring str : 文字列
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool SelConf::evalSetStr( GraphConfToken token, WSCstring str )
{
	if( pGraphConfCur == NULL )
		evalBlockBegin();
	if( pGraphConfCur == NULL )
		return false;

	return pGraphConfCur->setStr( token, str );
}

////////////////////////////////////////////////////////////////
// 選択ウィンドウの削除時のイベント・ハンドラ
// GtkWidget *widget : メニュー・ウィンドウ
// gpointer data : 登録時に渡された引数
////////////////////////////////////////////////////////////////

#ifdef D_GTK

void handle_sel_conf_win_destroy(
	GtkWidget *widget, gpointer data
)
{
	exit_game( EXIT_SUCCESS );
	gtk_main_quit();
}

#endif // D_GTK

////////////////////////////////////////////////////////////////
// リストの選択イベント処理
// GtkList *list : リスト
// GtkWidget *widget : 選択されたアイテム
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

#ifdef D_GTK

void handle_sel_conf_select(
	GtkList *list, GtkWidget *widget, gpointer data
)
{
	if( GTK_BIN( widget )->child == NULL )
		return;
	gchar *lblStr;
	gtk_label_get( GTK_LABEL( GTK_BIN( widget )->child ), &lblStr );

	WSCstring str = (char *)lblStr;
	WSCstring w = str.getWord( 1, STR_WORD_SEP_SEL_CONF );

	SelConf *p = (SelConf *)data;
	if( p != NULL )
		p->select( strtol( w, NULL, 10 ) );
}

#endif // D_GTK

////////////////////////////////////////////////////////////////
// OK ボタンのクリック・イベント処理
// GtkWidget *widget : ボタン
// GdkEventButton *event : イベント
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

#ifdef D_GTK

void handle_sel_conf_ok_clicked(
	GtkWidget *widget, gpointer data
)
{
	sel_conf_ok_clicked( (GtkWidget *)data );
}

#endif // D_GTK

////////////////////////////////////////////////////////////////
// キャンセル・ボタンのクリック・イベント処理
// GtkWidget *widget : ボタン
// GdkEventButton *event : イベント
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

#ifdef D_GTK

void handle_sel_conf_cancel_clicked(
	GtkWidget *widget, gpointer data
)
{
	exit_game( EXIT_SUCCESS );
	gtk_main_quit();
}

#endif // D_GTK

////////////////////////////////////////////////////////////////
// リストのダブル・クリック・イベント処理
// GtkWidget *widget : リスト・アイテム
// GdkEventButton *event : イベント
// gpointer data : 登録時に渡されたデータ
////////////////////////////////////////////////////////////////

#ifdef D_GTK

gint handle_sel_conf_d_clicked(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	if( !GTK_IS_LIST_ITEM( widget ) )
		return FALSE;
	if( event->type != GDK_2BUTTON_PRESS )
		return FALSE;
	if( event->button != 1 )
		return FALSE;

	sel_conf_ok_clicked( (GtkWidget *)data );

	return FALSE;
}

#endif // D_GTK

////////////////////////////////////////////////////////////////
// OK ボタンのクリック
// GtkWidget *data : グロブを解除するウィンドウ
////////////////////////////////////////////////////////////////

#ifdef D_GTK

void sel_conf_ok_clicked( GtkWidget *data )
{
	if( gSelConf.pGraphConfSel == NULL )
		return;

	if( data != NULL )
		gtk_grab_remove( data );
	gSelConf.wipe();

#if SEL_CONF_WIN_MODAL
	gtk_main_quit();
#endif // SEL_CONF_WIN_MODAL

	// メイン処理の初期化

	init_main_sel_conf( gSelConf.pGraphConfSel );
}

#endif // D_GTK
