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
* $Id: GuiInputString.cpp,v 1.28 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ�
////////////////////////////////////////////////////////////////

#define GUI_INPUT_STRING_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// ���٥�ȡ��ϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_input_string_delete(
	GtkWidget *widget, gpointer user_data
);
gint handle_input_string_destroy(
	GtkWidget *widget, gpointer user_data
);
gint handle_input_string_cancel_clicked(
	GtkWidget *widget, gpointer user_data
);
gint handle_input_string_ok_clicked(
	GtkWidget *widget, gpointer user_data
);
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ��Υ��󥹥ȥ饯��
////////////////////////////////////////////////////////////////

GuiInputString::GuiInputString()
{
#ifdef D_GTK
	mWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	mInpStrWin = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ��Υǥ��ȥ饯��
////////////////////////////////////////////////////////////////

GuiInputString::~GuiInputString()
{
}

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ��ν����
////////////////////////////////////////////////////////////////

void GuiInputString::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ��κ���
////////////////////////////////////////////////////////////////

void GuiInputString::newWin()
{
#ifdef D_WS
	if( mWin != NULL )
		return;

	mWin = (void *)InpStrWin;
#endif // D_WS

#ifdef D_GTK
	if( mWin != NULL )
		return;

	// ʸ�������ϥ�����ɥ��κ���

	mWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mWin ),
			"InputString" );

	// ʸ�������ϥ�����ɥ��ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mWin ),
			"delete_event",
			GTK_SIGNAL_FUNC( handle_input_string_delete ),
			this );
	gtk_signal_connect( GTK_OBJECT( mWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_input_string_destroy ),
			this );

	//

	GtkWidget *pBox = gtk_vbox_new( FALSE, 0 );
	gtk_container_add( GTK_CONTAINER( mWin ), pBox );
	gtk_widget_show( pBox );

	// �����ȥ�����

	mTitle = gtk_label_new( "" );
	if( mTitle == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( pBox ), mTitle,
			FALSE, TRUE, 0 );
	gtk_widget_show( mTitle );

	// ����ȥ꡼�����

	mEntry = gtk_entry_new();
	if( mEntry == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_entry_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( pBox ), mEntry,
			FALSE, TRUE, 0 );
	gtk_widget_show( mEntry );

	// ����ȥ꡼�ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mEntry ),
			"activate",
			GTK_SIGNAL_FUNC(
			handle_input_string_ok_clicked ),
			this );

	// ����󥻥롦�ܥ�������

	GtkWidget *pBoxButton = gtk_hbox_new( FALSE, 0 );
	gtk_box_pack_start( GTK_BOX( pBox ), pBoxButton,
			FALSE, TRUE, 0 );
	gtk_widget_show( pBoxButton );

	GtkWidget *mCancelButton = gtk_button_new_with_label(
			MSG_GUI_INPUT_STRING_CANCEL );
	if( mCancelButton == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( pBoxButton ), mCancelButton,
			FALSE, FALSE, 0 );
	gtk_widget_show( mCancelButton );

	// ����󥻥롦�ܥ���ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mCancelButton ),
			"clicked",
			GTK_SIGNAL_FUNC(
			handle_input_string_cancel_clicked ),
			this );

	// OK �ܥ�������

	GtkWidget *mOkButton = gtk_button_new_with_label(
			MSG_GUI_INPUT_STRING_OK );
	if( mOkButton == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}

	// �ǥե���ȡ��ܥ��������
	GTK_WIDGET_SET_FLAGS( mOkButton, GTK_CAN_DEFAULT );

	gtk_box_pack_start( GTK_BOX( pBoxButton ), mOkButton,
			FALSE, FALSE, 0 );

	// �ǥե���ȡ��ܥ��������
	gtk_widget_grab_default( mOkButton );

	gtk_widget_show( mOkButton );

	// OK �ܥ���ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mOkButton ),
			"clicked",
			GTK_SIGNAL_FUNC(
			handle_input_string_ok_clicked ),
			this );
#endif	// D_GTK

#ifdef D_MFC
	if( mInpStrWin != NULL )
		return;

	mInpStrWin = new CInputLineDlg;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ��κ��
////////////////////////////////////////////////////////////////

void GuiInputString::destroy()
{
#ifdef D_WS
	if( mWin == NULL )
		return;

	mWin = NULL;
#endif // D_WS

#ifdef D_GTK
	if( mWin == NULL )
		return;

	mWin = NULL;
#endif	// D_GTK

#ifdef D_MFC
	if( mInpStrWin == NULL )
		return;

	mInpStrWin = NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ���ɽ��
////////////////////////////////////////////////////////////////

void GuiInputString::draw( const char *ttl, const char *str, long len )
{
	newWin();

#ifdef D_WS
	if( mWin == NULL )
		return;

	gWinPos[WIN_KIND_INPUT_STRING].draw( WIN_KIND_INPUT_STRING );
#endif // D_WS

#ifdef D_GTK
	if( mWin == NULL )
		return;

	GtkLabel *t;
	GtkWindow *w;

	t = GTK_LABEL( gGuiInpStr.mTitle );
	w = GTK_WINDOW( gGuiInpStr.mWin );
	if( ttl == NULL ){
		gtk_window_set_title( w, "" );
		gtk_label_set_text( t, "" );
	} else {
		gtk_window_set_title( w, ttl );
		gtk_label_set_text( t, ttl );
	}

	GtkEntry *e;

	e = GTK_ENTRY( gGuiInpStr.mEntry );
	if( str == NULL ){
		gtk_entry_set_text( e, "" );
	} else {
		gtk_entry_set_text( e, str );
	}

	gtk_widget_grab_focus( gGuiInpStr.mEntry );

	gWinPos[WIN_KIND_INPUT_STRING].draw( WIN_KIND_INPUT_STRING );
#endif // D_GTK

#ifdef D_MFC
	if( mInpStrWin == NULL )
		return;

	mInpStrWin->m_EditDdx = str;

	INT_PTR res = mInpStrWin->DoModal();

	if( res == IDOK )
		set_key_buf_str_tail( mInpStrWin->m_EditDdx );
	/* ���Ͻ�λʸ�� EOL */
	set_key_buf_str_tail( "\r" );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ����Ĥ���
////////////////////////////////////////////////////////////////

void GuiInputString::wipe()
{
#if ! defined( D_MFC )
	gWinPos[WIN_KIND_INPUT_STRING].wipe( WIN_KIND_INPUT_STRING );
#endif
}

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ����Ĥ�������Υϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_input_string_delete(
	GtkWidget *widget, gpointer user_data
)
{
	/* ���Ͻ�λʸ�� EOL */
	set_key_buf_str_tail( "\r" );

	gGuiInpStr.wipe();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ʸ�������ϥ�����ɥ��ν�λ�����Υϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_input_string_destroy(
	GtkWidget *widget, gpointer user_data
)
{
	gGuiInpStr.wipe();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ����󥻥롦�ܥ���Υ���å������Υϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_input_string_cancel_clicked(
	GtkWidget *widget, gpointer user_data
)
{
	/* ���Ͻ�λʸ�� EOL */
	set_key_buf_str_tail( "\r" );

	gGuiInpStr.wipe();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// OK �ܥ���Υ���å������Υϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_input_string_ok_clicked(
	GtkWidget *widget, gpointer user_data
)
{
	GtkEntry *w = GTK_ENTRY( gGuiInpStr.mEntry );

	if( w != NULL ){
		const gchar *buf = gtk_entry_get_text( w );

		set_key_buf_str_tail( (const char *)buf );
	}

	/* ���Ͻ�λʸ�� EOL */
	set_key_buf_str_tail( "\r" );

	gGuiInpStr.wipe();

	return 0;
}
#endif // D_GTK
