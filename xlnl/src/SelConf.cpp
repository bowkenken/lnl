/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ����ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�����
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�����ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ����Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: SelConf.cpp,v 1.20 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ����ե��å����������
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
// ����Υ��󥹥ȥ饯��
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
// ����Υǥ��ȥ饯��
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
// ����ν����
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
// ���򥦥���ɥ��κ���
////////////////////////////////////////////////////////////////

void SelConf::newWin()
{
#ifdef D_GTK
	if( mSelConfWin != NULL )
		return;

	// ���򥦥���ɥ��κ���

	mSelConfWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mSelConfWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mSelConfWin ),
			"Select configure" );

	// ���򥦥���ɥ��ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mSelConfWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_sel_conf_win_destroy ),
			this );

	// ��ľ�ܥå����κ���

	vBox = gtk_vbox_new( FALSE, 0 );
	gtk_container_add( GTK_CONTAINER( mSelConfWin ), vBox );
	gtk_widget_show( vBox );

	// ��٥�κ���

	labelList = gtk_label_new( MSG_SEL_CONF_LABEL );
	gtk_box_pack_start( GTK_BOX( vBox ), labelList, FALSE, TRUE, 0 );
	gtk_widget_show( labelList );

	// �������롦������ɥ������

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

	// �ꥹ�ȡ��ܥå����κ���

	lsList = gtk_list_new();
	gtk_scrolled_window_add_with_viewport(
			GTK_SCROLLED_WINDOW( scrollWin ), lsList );
	gtk_widget_show( lsList );

	// �ꥹ�ȡ��ܥå����ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( lsList ),
			"select-child",
			GTK_SIGNAL_FUNC( handle_sel_conf_select ),
			this );

	// ��ʿ�ܥå����κ���

	hBox = gtk_hbox_new( FALSE, 0 );
	gtk_box_pack_start( GTK_BOX( vBox ), hBox, FALSE, TRUE, 0 );
	gtk_widget_show( hBox );

	// ����ܥ���κ���

	btnSelConfOk = gtk_button_new_with_label(
			MSG_SEL_CONF_OK );
	btnSelConfCancel = gtk_button_new_with_label(
			MSG_SEL_CONF_CANCEL );

	// �ǥե���ȡ��ܥ��������
	GTK_WIDGET_SET_FLAGS( btnSelConfOk, GTK_CAN_DEFAULT );

	gtk_box_pack_end( GTK_BOX( hBox ), btnSelConfOk,
			FALSE, TRUE, 0 );
	gtk_box_pack_end( GTK_BOX( hBox ), btnSelConfCancel,
			FALSE, TRUE, 0 );

	// �ǥե���ȡ��ܥ��������
	gtk_widget_grab_default( btnSelConfOk );

	gtk_widget_show( btnSelConfOk );
	gtk_widget_show( btnSelConfCancel );

	// ����ܥ���ؤΥ��٥�ȡ��ϥ�ɥ������

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
// ���򥦥���ɥ��κ��
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
// ���򥦥���ɥ���ɽ��
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

			// �ᥤ������ν������³����
			init_main_sel_conf( pGraphConfSel );
		} else {
			exit_game( EXIT_FAILURE );
		}

		break;
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ���򥦥���ɥ����Ĥ���
////////////////////////////////////////////////////////////////

void SelConf::wipe()
{
#ifdef D_GTK
	gWinPos[WIN_KIND_SEL_CONF].wipe( WIN_KIND_SEL_CONF );
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// ����ե�����򸡺����ƥꥹ�Ȥ���
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
// ����Υꥹ�Ȥ� GUI ����Ͽ
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
// ����ǥ��쥯�ȥ���ֹ������
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
// ����ǥ��쥯�ȥ�򳫤�
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
// ����ǥ��쥯�ȥ���Ĥ���
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
// ��������ǥ��쥯�ȥ�򸡺�
// return : ���Ĥ��ä��ǥ��쥯�ȥ�����Хѥ�
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
// ����ե������ʸ���� (�֥�å�����)
// return : ���顼��̵���ä���?
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
// ����ե������ʸ���� (�֥�å���λ)
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool SelConf::evalBlockEnd()
{
	return true;
}

////////////////////////////////////////////////////////////////
// ����ե������ʸ���� (����)
// GraphConfToken token : �ȡ�����
// long n : ����
// return : ���顼��̵���ä���?
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
// ����ե������ʸ���� (ʸ����)
// GraphConfToken token : �ȡ�����
// WSCstring str : ʸ����
// return : ���顼��̵���ä���?
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
// ���򥦥���ɥ��κ�����Υ��٥�ȡ��ϥ�ɥ�
// GtkWidget *widget : ��˥塼��������ɥ�
// gpointer data : ��Ͽ�����Ϥ��줿����
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
// �ꥹ�Ȥ����򥤥٥�Ƚ���
// GtkList *list : �ꥹ��
// GtkWidget *widget : ���򤵤줿�����ƥ�
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
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
// OK �ܥ���Υ���å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
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
// ����󥻥롦�ܥ���Υ���å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
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
// �ꥹ�ȤΥ��֥롦����å������٥�Ƚ���
// GtkWidget *widget : �ꥹ�ȡ������ƥ�
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
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
// OK �ܥ���Υ���å�
// GtkWidget *data : ����֤������륦����ɥ�
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

	// �ᥤ������ν����

	init_main_sel_conf( gSelConf.pGraphConfSel );
}

#endif // D_GTK
