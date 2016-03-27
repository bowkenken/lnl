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
* $Id: GuiWords.cpp,v 1.15 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ��쥦����ɥ�
////////////////////////////////////////////////////////////////

#define GUI_WORDS_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// ������
////////////////////////////////////////////////////////////////

// �ǥե���ȤΥ�����ɥ���������

#define	DEFAULT_WIN_WIDTH	320
#define	DEFAULT_WIN_HEIGHT	320

////////////////////////////////////////////////////////////////
// ���٥�ȡ��ϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_words_destroy( GtkWidget *widget, gpointer user_data );
gint handle_words_expose( GtkWidget *widget, GdkEventExpose *event );

gint handle_words_ok_clicked( GtkButton *button, gpointer user_data );
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��쥦����ɥ��Υ��󥹥ȥ饯��
////////////////////////////////////////////////////////////////

GuiWords::GuiWords()
{
	mWordsWin = NULL;
}

////////////////////////////////////////////////////////////////
// ��쥦����ɥ��Υǥ��ȥ饯��
////////////////////////////////////////////////////////////////

GuiWords::~GuiWords()
{
}

////////////////////////////////////////////////////////////////
// ��쥦����ɥ��ν����
////////////////////////////////////////////////////////////////

void GuiWords::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// ��쥦����ɥ��κ���
////////////////////////////////////////////////////////////////

void GuiWords::newWin()
{
	if( mWordsWin != NULL )
		return;

#ifdef D_WS
	mWordsWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	// ��쥦����ɥ��κ���

	mWordsWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mWordsWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mWordsWin ),
			"Words" );

	// ��쥦����ɥ��ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mWordsWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_words_destroy ),
			this );
	gtk_signal_connect( GTK_OBJECT( mWordsWin ),
			"key-press-event",
			GTK_SIGNAL_FUNC( handleKeyPress ), NULL );

	// �ܥå����κ���

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

	// ���ƥ����ȤΥ������롦������ɥ������

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

	// ���ƥ����ȤΥӥ塼�����

	mWordsTextView = gtk_text_view_new();
	if( mWordsTextView == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_text_view_new()" );
		return;
	}
	gtk_widget_show( mWordsTextView );
	gtk_container_add( GTK_CONTAINER( mWordsTextScroll ),
			mWordsTextView );

	// OK �ܥ���κ���

	mButtonOk = gtk_button_new_with_label( "Ok" );
	if( mButtonOk == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonOk );

	// OK �ܥ���ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mButtonOk ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_words_ok_clicked ),
			NULL );

	// �ܥå����ˤΤ���

	gtk_box_pack_start( GTK_BOX( vBoxWin ), mWordsTextScroll,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( hBoxWin ), mButtonOk,
			TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBoxWin ), hBoxWin,
			FALSE, FALSE, 0 );

	gtk_container_add( GTK_CONTAINER( mWordsWin ), vBoxWin );

	// ������ɥ���������������

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
// ��쥦����ɥ��κ��
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
// ��쥦����ɥ���ɽ��
// const char *name : ̾��
// const char *str : ���
// long w : ɽ����
////////////////////////////////////////////////////////////////

void GuiWords::draw( const char *name, const char *str, long w )
{
	newWin();

	if( w <= 0 )
		w = WIN_REQUEST_DRAW_WIDTH;

#ifdef D_GTK
	GtkTextBuffer *buf = gtk_text_view_get_buffer(
			GTK_TEXT_VIEW( mWordsTextView ) );

	// �Ť��ƥ����Ȥ���

	GtkTextIter cur, bgn, end;
	gtk_text_buffer_get_start_iter( buf, &bgn );
	gtk_text_buffer_get_end_iter( buf, &end );
	gtk_text_buffer_delete( buf, &bgn, &end );

	// ̾�����ɲ�

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

	// �ƥ����Ȥ��ɲ�

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
// ��쥦����ɥ��κ�ɽ��
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
// ��쥦����ɥ����Ĥ���
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
// OK �ܥ���Υ���å��ν���
////////////////////////////////////////////////////////////////

void GuiWords::okClicked()
{
	wipe();

	gKey.setChar( '\n' );
}

////////////////////////////////////////////////////////////////
// ��쥦����ɥ��ν�λ�����Υϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_words_destroy( GtkWidget *widget, gpointer user_data )
{
	gGuiWords.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��쥦����ɥ������襤�٥�Ȥν���
// GtkWidget *widget : ��å������Υɥ����󥰡����ꥢ
// GdkEventExpose *event : ���٥��
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
// OK �ܥ���Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer user_data : �ܥ���μ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_words_ok_clicked( GtkButton *button, gpointer user_data )
{
	gGuiWords.okClicked();

	return 0;
}
#endif // D_GTK
