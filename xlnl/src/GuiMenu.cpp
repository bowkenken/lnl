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
* $Id: GuiMenu.cpp,v 1.52 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ��˥塼��������ɥ�
////////////////////////////////////////////////////////////////

#define GUI_MENU_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// �ѿ����
////////////////////////////////////////////////////////////////

#define	GUI_MENU_BTN_MARGIN_X	4
#define	GUI_MENU_BTN_MARGIN_Y	4
#define	GUI_MENU_BTN_HEIGHT	24

#ifdef D_WS
extern WSCwindow *MenuWin;
extern WSCvbtn *MenuBtnPrevPage, *MenuBtnNextPage;
extern WSCvlabel *MenuLabelPage;
#endif // D_WS

////////////////////////////////////////////////////////////////
// ���٥�ȡ��ϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_WS

void EpGuiMenuSel( WSCbase *obj );

#endif // D_WS

#ifdef D_GTK

gint handle_menu_win_delete(
	GtkWidget *widget, gpointer data
);

gint handle_menu_win_destroy(
	GtkWidget *widget, gpointer data
);

gint handle_menu_page_release(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);
gint handle_menu_cancel_release(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);
gint handle_menu_cancel_all_release(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);

gint handle_menu_button_clicked(
	GtkWidget *widget, gpointer data
);
gint handle_menu_button_press(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);
gint handle_menu_button_release(
	GtkWidget *widget, GdkEventButton *event, gpointer data
);
gint handle_menu_button_enter(
	GtkWidget *widget, gpointer data
);
gint handle_menu_button_leave(
	GtkWidget *widget, gpointer data
);

#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼��������ɥ��Υ��󥹥ȥ饯��
////////////////////////////////////////////////////////////////

GuiMenu::GuiMenu()
{
	mMenuWin = NULL;

	nSelN = 0;

#ifdef D_GTK
	vBox = NULL;

	nClickedButton = 0;
	bFlagEnter = FALSE;
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// ��˥塼��������ɥ��Υǥ��ȥ饯��
////////////////////////////////////////////////////////////////

GuiMenu::~GuiMenu()
{
}

////////////////////////////////////////////////////////////////
// ��˥塼�ν����
////////////////////////////////////////////////////////////////

void GuiMenu::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// ��˥塼��������ɥ��κ���
////////////////////////////////////////////////////////////////

void GuiMenu::newWin()
{
	if( mMenuWin != NULL )
		return;

#ifdef D_WS
	mMenuWin = (void *)1;

	for( long i = 0; i < MENU_MAX_N_PER_PAGE; i++ ){
		WSCstring name;
		name << "NAME" << i;

		WSCbase *base = WSCbase::getNewInstance(
				"WSCvbtn", MenuWin, name );
		base->initialize();
		base->clear();

		aBtnMenu[i] = (WSCvbtn *)base->cast( "WSCvbtn" );

		aBtnMenu[i]->setVariantData( "accel_key", '\0' );

		aBtnMenu[i]->setProperty( WSNx, GUI_MENU_BTN_MARGIN_X );
		aBtnMenu[i]->setProperty( WSNy, GUI_MENU_BTN_MARGIN_Y
				+ ((long)MenuLabelPage->getProperty(
				WSNheight ))
				+ (GUI_MENU_BTN_HEIGHT * i) );
		aBtnMenu[i]->setProperty( WSNheight, GUI_MENU_BTN_HEIGHT );

		aBtnMenu[i]->setProperty( WSNalignmentV, WS_CENTER );
		aBtnMenu[i]->setProperty( WSNalignmentH, WS_LEFT );

		aBtnMenu[i]->setProperty( WSNanchorTopFlag, (WSCbool)0 );
		aBtnMenu[i]->setProperty( WSNanchorBottomFlag, (WSCbool)0 );
		aBtnMenu[i]->setProperty( WSNanchorLeftFlag, (WSCbool)1 );
		aBtnMenu[i]->setProperty( WSNanchorRightFlag, (WSCbool)1 );
		aBtnMenu[i]->setProperty( WSNanchorTop,
				GUI_MENU_BTN_MARGIN_Y );
		aBtnMenu[i]->setProperty( WSNanchorBottom,
				GUI_MENU_BTN_MARGIN_Y );
		aBtnMenu[i]->setProperty( WSNanchorLeft,
				GUI_MENU_BTN_MARGIN_X );
		aBtnMenu[i]->setProperty( WSNanchorRight,
				GUI_MENU_BTN_MARGIN_X );

		aBtnMenu[i]->setVisible( false );
		aBtnMenu[i]->setSensitive( false );

		WSCprocedure *ep = new WSCprocedure( "EP", WSEV_ACTIVATE );
		ep->setFunction( EpGuiMenuSel, "EpGuiMenuSel" );
		aBtnMenu[i]->addProcedure( ep );
	}

	MenuWin->setVisible( false );
#endif // D_WS

#ifdef D_GTK
	// ��˥塼��������ɥ��κ���

	mMenuWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mMenuWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mMenuWin ),
			"Menu" );

	// ��˥塼��������ɥ��ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mMenuWin ),
			"delete_event",
			GTK_SIGNAL_FUNC( handle_menu_win_delete ),
			this );
	gtk_signal_connect( GTK_OBJECT( mMenuWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_menu_win_destroy ),
			this );
	gtk_signal_connect( GTK_OBJECT( mMenuWin ),
			"key-press-event",
			GTK_SIGNAL_FUNC( handleKeyPress ), NULL );

	// ��ľ�ܥå����κ���

	vBox = gtk_vbox_new( FALSE, 0 );
	gtk_container_add( GTK_CONTAINER( mMenuWin ), vBox );
	gtk_widget_show( vBox );

	// �ġ��롦�С��κ���

	GtkWidget *handleBox = gtk_handle_box_new();
	gtk_widget_show( handleBox );

	GtkWidget *toolBar = gtk_toolbar_new();
	gtk_toolbar_set_orientation( GTK_TOOLBAR( toolBar ),
			GTK_ORIENTATION_HORIZONTAL );
	gtk_toolbar_set_style( GTK_TOOLBAR( toolBar ),
			GTK_TOOLBAR_ICONS );
	gtk_widget_show( toolBar );

	gtk_container_add( GTK_CONTAINER( handleBox ), toolBar );

	// ��˥塼�����ܥ���κ���

	btnMenuPrevPage = gtk_button_new_with_label(
			MSG_GUI_MENU_PREV_PAGE_ON );
	btnMenuNextPage = gtk_button_new_with_label(
			MSG_GUI_MENU_NEXT_PAGE_ON );
	btnMenuCancel = gtk_button_new_with_label(
			MSG_GUI_MENU_CANCEL_ON );
	btnMenuCancelAll = gtk_button_new_with_label(
			MSG_GUI_MENU_CANCEL_ALL_ON );
	labelMenuPageN = gtk_label_new( "0/0" );

	gtk_misc_set_alignment( GTK_MISC( labelMenuPageN ), 0, 0.5 );

	gtk_widget_show( btnMenuPrevPage );
	gtk_widget_show( btnMenuNextPage );
	gtk_widget_show( btnMenuCancel );
	gtk_widget_show( btnMenuCancelAll );
	gtk_widget_show( labelMenuPageN );

	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMenuPrevPage,
			MSG_GUI_MENU_TOOL_TIP_PREV_PAGE,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			labelMenuPageN,
			MSG_GUI_MENU_TOOL_TIP_PAGE_N,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMenuNextPage,
			MSG_GUI_MENU_TOOL_TIP_NEXT_PAGE,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMenuCancel,
			MSG_GUI_MENU_TOOL_TIP_CANCEL,
			NULL );
	gtk_toolbar_append_widget( GTK_TOOLBAR( toolBar ),
			btnMenuCancelAll,
			MSG_GUI_MENU_TOOL_TIP_CANCEL_ALL,
			NULL );

	gtk_box_pack_start( GTK_BOX( vBox ), handleBox, FALSE, TRUE, 0 );

	// ��˥塼�����ܥ���ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( btnMenuPrevPage ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_menu_page_release ),
			(gpointer)-1 );
	gtk_signal_connect( GTK_OBJECT( btnMenuNextPage ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_menu_page_release ),
			(gpointer)+1 );
	gtk_signal_connect( GTK_OBJECT( btnMenuCancel ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_menu_cancel_release ),
			NULL );
	gtk_signal_connect( GTK_OBJECT( btnMenuCancelAll ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_menu_cancel_all_release ),
			NULL );

	// ��˥塼���ܥ���κ���

	for( long i = 0; i < MENU_MAX_N_PER_PAGE; i++ ){
		aBtnMenu[i] = gtk_button_new_with_label( "Menu" );
		gtk_box_pack_start( GTK_BOX( vBox ), aBtnMenu[i],
				FALSE, TRUE, 0 );
		gtk_widget_show( aBtnMenu[i] );

		cAccelKey[i] = '\0';
	}

	// ��˥塼���ܥ���ؤΥ��٥�ȡ��ϥ�ɥ������

	for( long i = 0; i < MENU_MAX_N_PER_PAGE; i++ ){
		gtk_signal_connect( GTK_OBJECT( aBtnMenu[i] ),
			"button_press_event",
			GTK_SIGNAL_FUNC( handle_menu_button_press ),
			(gpointer)i );
		gtk_signal_connect( GTK_OBJECT( aBtnMenu[i] ),
			"button_release_event",
			GTK_SIGNAL_FUNC( handle_menu_button_release ),
			(gpointer)i );
		gtk_signal_connect( GTK_OBJECT( aBtnMenu[i] ),
			"enter",
			GTK_SIGNAL_FUNC( handle_menu_button_enter ),
			(gpointer)i );
		gtk_signal_connect( GTK_OBJECT( aBtnMenu[i] ),
			"leave",
			GTK_SIGNAL_FUNC( handle_menu_button_leave ),
			(gpointer)i );
	}
#endif // D_GTK

#ifdef D_MFC
	mMenuWin = &(theApp.m_MenuWnd);

	for( long i = IDC_MENU_WND_BTN_BGN;
			i < IDC_MENU_WND_BTN_END; i++ ){
		long n = i - IDC_MENU_WND_BTN_BGN;

		if( n >= MENU_MAX_N_PER_PAGE ){
			aBtnMenu[n] = NULL;
			break;
		}

		aBtnMenu[n] = &(mMenuWin->m_aBtn[n]);
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ��˥塼��������ɥ��κ��
////////////////////////////////////////////////////////////////

void GuiMenu::destroy()
{
	if( mMenuWin == NULL )
		return;

#ifdef D_GTK
	for( long i = 0; i < MENU_MAX_N_PER_PAGE; i++ )
		gtk_widget_destroy( aBtnMenu[i] );

	gtk_widget_destroy( vBox );

	mMenuWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	delete mMenuWin;
	mMenuWin = (CMenuWnd *)NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ��˥塼�����򳫻�
// draw_menu_t *data : ��˥塼�������ѥǡ���
////////////////////////////////////////////////////////////////

void GuiMenu::draw( draw_menu_t *data )
{
	newWin();

	static char tmp[1024 + 1];

	if( data == NULL )
		return;

	nSelN = data->sel_n;

	// �����ȥ�

	WSCstring msgTitle = data->ttl;
	if( msgTitle.getChars() <= 0 )
		msgTitle = "Menu";

#ifdef D_WS
	MenuWin->setProperty( WSNtitleString, (char *)msgTitle );
#endif // D_WS

#ifdef D_GTK
	gtk_window_set_title( GTK_WINDOW( mMenuWin ),
			(char *)msgTitle );

	g_object_set( GTK_WINDOW( mMenuWin ),
			"allow-shrink", FALSE,
			"allow-grow", FALSE,
			NULL );
#endif // D_GTK

#ifdef D_MFC
	mMenuWin->SetWindowText( (LPCTSTR)msgTitle );
#endif // D_MFC

	// �ڡ����ڤ��ؤ��ܥ���� ON/OFF

#ifdef D_WS
	if( data->flg_min_page ){
		MenuBtnPrevPage->setProperty(
				WSNlabelString,
				(char *)MSG_GUI_MENU_PREV_PAGE_OFF );
	} else {
		MenuBtnPrevPage->setProperty(
				WSNlabelString,
				(char *)MSG_GUI_MENU_PREV_PAGE_ON );
	}
	if( data->flg_max_page ){
		MenuBtnNextPage->setProperty(
				WSNlabelString,
				(char *)MSG_GUI_MENU_NEXT_PAGE_OFF );
	} else {
		MenuBtnNextPage->setProperty(
				WSNlabelString,
				(char *)MSG_GUI_MENU_NEXT_PAGE_ON );
	}
#endif // D_WS

#ifdef D_GTK
	if( data->flg_min_page ){
		set_label_text_button( GTK_BUTTON( btnMenuPrevPage ),
				MSG_GUI_MENU_PREV_PAGE_OFF, 0.5, 0.5 );
	} else {
		set_label_text_button( GTK_BUTTON( btnMenuPrevPage ),
				MSG_GUI_MENU_PREV_PAGE_ON, 0.5, 0.5 );
	}
	if( data->flg_max_page ){
		set_label_text_button( GTK_BUTTON( btnMenuNextPage ),
				MSG_GUI_MENU_NEXT_PAGE_OFF, 0.5, 0.5 );
	} else {
		set_label_text_button( GTK_BUTTON( btnMenuNextPage ),
				MSG_GUI_MENU_NEXT_PAGE_ON, 0.5, 0.5 );
	}
#endif // D_GTK

#ifdef D_MFC
	if( data->flg_min_page ){
		mMenuWin->m_BtnPrevPage.SetWindowText(
				MSG_GUI_MENU_PREV_PAGE_OFF );
	} else {
		mMenuWin->m_BtnPrevPage.SetWindowText(
				MSG_GUI_MENU_PREV_PAGE_ON );
	}
	if( data->flg_max_page ){
		mMenuWin->m_BtnNextPage.SetWindowText(
				MSG_GUI_MENU_NEXT_PAGE_OFF );
	} else {
		mMenuWin->m_BtnNextPage.SetWindowText(
				MSG_GUI_MENU_NEXT_PAGE_ON );
	}
#endif // D_MFC

	// �ڡ�����������

	WSCstring strPage = "";
	strPage += " ";
	strPage += WSCstring( data->page_sel_n + 1 );
	strPage += "/";
	strPage += WSCstring( data->page_max_n );
	strPage += " ";

#ifdef D_WS
	MenuLabelPage->setProperty( WSNlabelString, (char *)strPage );
#endif // D_WS

#ifdef D_GTK
	gtk_misc_set_alignment( GTK_MISC( labelMenuPageN ), 0.5, 0.5 );
	gtk_label_set_text( GTK_LABEL( labelMenuPageN ), (char *)strPage );
#endif // D_GTK

#ifdef D_MFC
	mMenuWin->m_LblPage.SetWindowText( (char *)strPage );

	mMenuWin->m_BtnCancel.SetWindowText(
			MSG_GUI_MENU_CANCEL_ON );
	mMenuWin->m_BtnCancelAll.SetWindowText(
			MSG_GUI_MENU_CANCEL_ALL_ON );
#endif // D_MFC

	// �����å����ޡ��������褹�뤫Ĵ�٤�

	long i = 0;
	bool FlagUseOnOff = false;
	for( i = 0; i < MENU_MAX_N_PER_PAGE; i++ ){
		if( data->ls[i] == NULL )
			break;

		if( strcmp( data->ls[i]->kind, "<CheckItem>" ) == 0 ){
			FlagUseOnOff = true;
		} else if( strcmp( data->ls[i]->kind, "<RadioItem>" ) == 0 ){
			FlagUseOnOff = true;
		}
	}

#ifdef D_MFC
	bool flgGroup = false;
	bool flgGroupSwitch = false;

	CRect rectBgn, rectEnd;
	mMenuWin->m_BtnPrevPage.GetWindowRect( &rectBgn );
	mMenuWin->m_BtnCancelAll.GetWindowRect( &rectEnd );

	long maxW = rectEnd.right - rectBgn.left;
#endif // D_MFC

	// ��˥塼����̾��ܥ��������

	for( i = 0; i < MENU_MAX_N_PER_PAGE; i++ ){
		if( data->ls[i] == NULL )
			break;
		if( data->ls[i]->msg == NULL )
			continue;
		if( aBtnMenu[i] == NULL )
			continue;

		// ��˥塼����

		WSCstring msgContents = data->ls[i]->msg;

		// �������

		WSCstring msgSelectLeft = " ";
		WSCstring msgSelectRight = " ";
		if( i == data->sel_n ){
			msgSelectLeft = MSG_MENU_SELECT_GUI_LEFT;
			msgSelectRight = MSG_MENU_SELECT_GUI_RIGHT;
		} else {
			msgSelectLeft = MSG_MENU_NOT_SELECT_GUI_LEFT;
			msgSelectRight = MSG_MENU_NOT_SELECT_GUI_RIGHT;
		}

		// ��������졼��������

		WSCstring msgAccel = "";
		if( data->ls[i]->accel_key != '\0' ){
			sprintf( tmp, MSG_MENU_ACCEL_KEY_FMT,
					data->ls[i]->accel_key );
			msgAccel = tmp;
		}

		// ���硼�ȥ��åȡ�����

		WSCstring msgShort = "";
		if( data->ls[i]->short_key[0] != '\0' ){
			sprintf( tmp, MSG_MENU_SHORT_CUT_KEY_FMT,
					data->ls[i]->short_key );
			msgShort = tmp;
		}

		// �����å����ܥå���

		WSCstring msgChk = "";
		if( !FlagUseOnOff )
			msgChk = MSG_NULL;
		else if( chk_flg( data->ls[i]->flg, FLG_MENU_CHK_ON ) )
			msgChk = MSG_MENU_FLG_LS_CHK_ON;
		else if( chk_flg( data->ls[i]->flg, FLG_MENU_CHK_OFF ) )
			msgChk = MSG_MENU_FLG_LS_CHK_OFF;
		else
			msgChk = MSG_MENU_FLG_LS_CHK_NULL;

		// <Branch>

		WSCstring msgBranch = "";
		if( strcmp( data->ls[i]->kind, "<Branch>" ) == 0 )
			msgBranch = MSG_MENU_KIND_BRANCH;
		else
			msgBranch = MSG_NULL;

		// <OpenWinItem>

		WSCstring msgOpenWin = "";
		if( strcmp( data->ls[i]->kind, "<OpenWinItem>" ) == 0 )
			msgOpenWin = MSG_MENU_KIND_OPEN_WIN_ITEM;
		else
			msgOpenWin = MSG_NULL;

		// ��˥塼���ܥ���Υ�٥�

		WSCstring msg = "";
		msg += msgSelectLeft;
		msg += msgChk + msgAccel;
		msg += msgContents;
		msg += WSCstring( " " ) + msgOpenWin;
		msg += WSCstring( " " ) + msgShort;
		msg += WSCstring( " " ) + msgBranch;
		msg += msgSelectRight;

		// �ȥ��롦�ܥ���Υץ�ѥƥ�

#ifdef D_MFC
		aBtnMenu[i]->SetCheck( false );

		flgGroupSwitch = false;
		ULONG flgBtn = WS_VISIBLE;

		if( strcmp( data->ls[i]->kind, "<CheckItem>" ) == 0 )
			flgBtn |= BS_CHECKBOX;
		else if( strcmp( data->ls[i]->kind, "<RadioItem>" ) == 0 )
			flgBtn |= BS_RADIOBUTTON;
		else
			flgBtn |= BS_PUSHBUTTON;

		if( strcmp( data->ls[i]->kind, "<RadioItem>" ) == 0 ){
			if( !flgGroup )
				flgGroupSwitch = true;
			flgGroup = true;
		} else {
			if( flgGroup )
				flgGroupSwitch = true;
			flgGroup = false;
		}
		if( flgGroupSwitch )
			flgBtn |= WS_GROUP;

		aBtnMenu[i]->SetButtonStyle( flgBtn, TRUE );

		if( chk_flg( data->ls[i]->flg, FLG_MENU_CHK_ON ) )
			aBtnMenu[i]->SetCheck( true );
		else if( chk_flg( data->ls[i]->flg, FLG_MENU_CHK_OFF ) )
			aBtnMenu[i]->SetCheck( false );
		else
			aBtnMenu[i]->SetCheck( false );
#endif // D_MFC

		// ��˥塼���ܥ���Υץ�ѥƥ�

#ifdef D_WS
		aBtnMenu[i]->setVariantData( "accel_key",
				data->ls[i]->accel_key );

		aBtnMenu[i]->setProperty( WSNlabelString, msg );
		aBtnMenu[i]->setVisible( true );
		aBtnMenu[i]->setSensitive( true );
#endif // D_WS

#ifdef D_GTK
		cAccelKey[i] = data->ls[i]->accel_key;

		set_label_text_button( GTK_BUTTON( aBtnMenu[i] ), msg,
				0.0, 0.5 );

		gtk_widget_show( aBtnMenu[i] );
#endif // D_GTK

#ifdef D_MFC
		cAccelKey[i] = data->ls[i]->accel_key;

		aBtnMenu[i]->SetWindowText( msg );

		CClientDC dc( aBtnMenu[i] );
		CSize size = dc.GetOutputTextExtent(
				(char *)msg );
		maxW = max_l( maxW, (long)(size.cx) );

		aBtnMenu[i]->ShowWindow( SW_SHOW );
#endif // D_MFC

		// �ǥե���Ȥι��ܤ˥ե����������ư

		if( i == data->sel_n ){
#ifdef D_WS
			aBtnMenu[i]->setFocus();
#endif // D_WS

#ifdef D_GTK
			gtk_widget_grab_focus( aBtnMenu[i] );
#endif // D_GTK

#ifdef D_MFC
			aBtnMenu[i]->SetFocus();
#endif // D_MFC
		}
	}

#ifdef D_MFC
	long n = i;
#endif // D_MFC

	for( ; i < MENU_MAX_N_PER_PAGE; i++ ){
		// ;�ä��ܥ������ɽ���ˤ���

		if( aBtnMenu[i] == NULL )
			continue;

#ifdef D_WS
		aBtnMenu[i]->setVisible( false );
		aBtnMenu[i]->setSensitive( false );
#endif // D_WS

#ifdef D_GTK
		gtk_widget_hide( aBtnMenu[i] );
#endif // D_GTK

#ifdef D_MFC
		aBtnMenu[i]->ShowWindow( SW_HIDE );
#endif // D_MFC
	}

	// �ܥ�������򤽤���

#ifdef D_MFC
	long y = 0;

	CRect rect;
	mMenuWin->m_BtnPrevPage.GetWindowRect( &rect );
	y += rect.Height();

	for( long j = 0; j < n; j++ ){
		if( data->ls[j] == NULL )
			break;
		if( data->ls[j]->msg == NULL )
			continue;
		if( aBtnMenu[j] == NULL )
			continue;

		CRect rect;
		aBtnMenu[j]->GetWindowRect( &rect );
		aBtnMenu[j]->MoveWindow(
				0, y,
				maxW, rect.Height(),
				TRUE );
		y += rect.Height();
	}
#endif // D_MFC

	// ��˥塼��������ɥ���ɽ��

	gWinPos[WIN_KIND_MENU].get( WIN_KIND_MENU,
			NULL, NULL, NULL, NULL );
	gWinPos[WIN_KIND_MENU].draw( WIN_KIND_MENU );

	// ������ɥ��Υ�������ܥ�����˹�碌��

#ifdef D_MFC
	if( n > 0 ){
		CRect rectPrev, rectBtn, rectWnd;

		mMenuWin->m_BtnPrevPage
				.GetWindowRect( &rectPrev );
		aBtnMenu[n - 1]->GetWindowRect( &rectBtn );
		mMenuWin->GetWindowRect( &rectWnd );

		CRect rectAdj( 0, 0,
				maxW, (rectBtn.bottom - rectPrev.top) );
		::AdjustWindowRectEx( &rectAdj,
				mMenuWin->GetStyle(), FALSE,
				mMenuWin->GetExStyle() );

		mMenuWin->MoveWindow(
				rectWnd.left,
				rectWnd.top,
				rectAdj.Width(),
				rectAdj.Height(),
				TRUE );
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ��˥塼���Ĥ���
////////////////////////////////////////////////////////////////

void GuiMenu::wipe()
{
	gWinPos[WIN_KIND_MENU].wipe( WIN_KIND_MENU );
}

////////////////////////////////////////////////////////////////
// �ǥե���Ȥ�������ܤ˥ޥ���������������ư
// long sel_n : �������
////////////////////////////////////////////////////////////////

void GuiMenu::setMouseDfltMenu( long sel_n )
{
	newWin();

	if( sel_n <= -1 )
		return;
	if( sel_n >= MENU_MAX_N_PER_PAGE )
		return;
	if( !get_flg_move_crsr_dflt() )
		return;

	long x = 0;
	long y = 0;
	long w = 0;
	long h = 0;

#ifdef D_WS
	x = (long)(MenuWin->getProperty( WSNx ));
	y = (long)(MenuWin->getProperty( WSNy ));
	y += (long)(MenuWin->getProperty( WSNbarThickness ));
	x += (long)(aBtnMenu[sel_n]->getProperty( WSNx ));
	y += (long)(aBtnMenu[sel_n]->getProperty( WSNy ));
	w = (long)(aBtnMenu[sel_n]->getProperty( WSNwidth ));
	h = (long)(aBtnMenu[sel_n]->getProperty( WSNheight ));

	x += w * 4 / 5;
	y += h / 2;

	WSDmouse *mouse = WSGIappMouse();
	mouse->setMousePosition( x, y );
#endif // D_WS

#ifdef D_GTK
	gint menuX = 0;
	gint menuY = 0;
	gdk_window_get_position( mMenuWin->window, &menuX, &menuY );
	if( (menuX <= 32) && (menuY <= 32) )
		return;

	x = aBtnMenu[sel_n]->allocation.x + menuX;
	y = aBtnMenu[sel_n]->allocation.y + menuY;
	w = aBtnMenu[sel_n]->allocation.width;
	h = aBtnMenu[sel_n]->allocation.height;

	int crsrX = 0;
	int crsrY = 0;
	Window rootWin, childWin;
	int winX, winY;
	unsigned int mask;
	XQueryPointer( gdk_x11_get_default_xdisplay(),
			GDK_ROOT_WINDOW(), &rootWin, &childWin,
			&crsrX, &crsrY, &winX, &winY, &mask );

	x -= crsrX;
	y -= crsrY;

	x += w * 4 / 5;
	y += h / 2;

	XWarpPointer( gdk_x11_get_default_xdisplay(),
			None, None,
			0, 0, 0, 0, x, y );
#endif // D_GTK

#ifdef D_MFC
	RECT rect;
	aBtnMenu[sel_n]->GetWindowRect( &rect );
	x = rect.left;
	y = rect.top;
	w = rect.right - rect.left;
	h = rect.bottom - rect.top;

	x += w * 4 / 5;
	y += h / 2;

	::SetCursorPos( x, y );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ��˥塼�Υ��������ܥ���˰�ư
// long nBtn : ��˥塼�Υܥ�����ֹ�
////////////////////////////////////////////////////////////////

void GuiMenu::moveMenuCrsr( long nBtn )
{
	long nSel = gGuiMenu.getSelN();
	if( nBtn < nSel ){
		for( long i = 0; i < nSel - nBtn; i++ )
			gKey.setChar( '8' );
	} else if( nBtn > nSel ){
		for( long i = 0; i < nBtn - nSel; i++ )
			gKey.setChar( '2' );
	}
}

////////////////////////////////////////////////////////////////
// ��˥塼�Υܥ�����ֹ椫�饢������졼�����������Ѵ�
// long n : ��˥塼�Υܥ�����ֹ�
////////////////////////////////////////////////////////////////

char GuiMenu::getAccelKey( long n )
{
	if( n < 0 )
		return '\0';
	if( n >= MENU_MAX_N_PER_PAGE )
		return '\0';

	return cAccelKey[n];
}

////////////////////////////////////////////////////////////////
// ��������Τ����˥塼�ֹ���֤�
// long n : ��˥塼�ֹ�
////////////////////////////////////////////////////////////////

long GuiMenu::getSelN()
{
	return nSelN;
}

////////////////////////////////////////////////////////////////
// ��˥塼�Υܥ���򥯥�å� (WideStudio)
// WSCbase *obj : ����å����줿�ܥ���
////////////////////////////////////////////////////////////////

#ifdef D_WS
void EpGuiMenuSel( WSCbase *obj )
{
	WSDmouse *mouse = WSGIappMouse();

	if( mouse->getTargetBtn() & WS_MOUSE_BTN1 ){
		gKey.setChar( (char)(obj->getVariantData( "accel_key" )) );
	} else if( mouse->getTargetBtn() & WS_MOUSE_BTN3 ){
		gKey.setChar( '0' );
	}
}
#endif // D_WS

////////////////////////////////////////////////////////////////
// ��˥塼��������ɥ����Ĥ�������Υϥ�ɥ�
// GtkWidget *widget : ��˥塼��������ɥ�
// gpointer data : ��Ͽ�����Ϥ��줿����
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_win_delete(
	GtkWidget *widget, gpointer data
)
{
	gKey.setChar( '0' );

	return 1;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼��������ɥ��κ�����Υ��٥�ȡ��ϥ�ɥ�
// GtkWidget *widget : ��˥塼��������ɥ�
// gpointer data : ��Ͽ�����Ϥ��줿����
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_win_destroy(
	GtkWidget *widget, gpointer data
)
{
	if( data == NULL )
		return 0;

	((GuiMenu *)data)->destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼�����ܥ���Υ���å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_page_release(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	long d = (long)data;

	if( event->button == GuiMenu::MOUSE_BUTTON_N_LEFT ){
		if( d <= -1 )
			gKey.setChar( '4' );
		if( d >= +1 )
			gKey.setChar( '6' );
	} else if( event->button == GuiMenu::MOUSE_BUTTON_N_RIGHT ){
		if( d <= -1 )
			gKey.setChar( '6' );
		if( d >= +1 )
			gKey.setChar( '4' );
	}

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼�Υ���󥻥롦�ܥ���Υ���å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_cancel_release(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	gKey.setChar( '0' );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼��������󥻥롦�ܥ���Υ���å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_cancel_all_release(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	gKey.setChar( '/' );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼�Υܥ���κ�����å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_button_clicked(
	GtkWidget *widget, gpointer data
)
{
	gKey.setChar( gGuiMenu.getAccelKey( (long)data ) );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼�Υܥ���Υޥ������ץ쥹�����٥�Ƚ���
// GtkWidget *widget : �ܥ���
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_button_press(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	gGuiMenu.nClickedButton = (long)data;
	gGuiMenu.bFlagEnter = TRUE;

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼�Υܥ���Υޥ�������꡼�������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_button_release(
	GtkWidget *widget, GdkEventButton *event, gpointer data
)
{
	if( !gGuiMenu.bFlagEnter )
		return 0;

	if( event->button == GuiMenu::MOUSE_BUTTON_N_LEFT ){
		gKey.setChar( gGuiMenu.getAccelKey( (long)data ) );
	} else if( event->button == GuiMenu::MOUSE_BUTTON_N_MIDDLE ){
		gGuiMenu.moveMenuCrsr( (long)data );
		gKey.setChar( MENU_COMMAND_KEY_CHAR );
	} else if( event->button == GuiMenu::MOUSE_BUTTON_N_RIGHT ){
		gKey.setChar( '0' );
	}

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼�Υܥ���Υޥ��������󥿡������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_button_enter(
	GtkWidget *widget, gpointer data
)
{
	if( gGuiMenu.nClickedButton == (long)data )
		gGuiMenu.bFlagEnter = TRUE;

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ��˥塼�Υܥ���Υޥ������꡼�֡����٥�Ƚ���
// GtkWidget *widget : �ܥ���
// GdkEventButton *event : ���٥��
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_menu_button_leave(
	GtkWidget *widget, gpointer data
)
{
	gGuiMenu.bFlagEnter = FALSE;

	return 0;
}
#endif // D_GTK
