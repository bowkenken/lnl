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
* $Id: GuiNum.cpp,v 1.36 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// �������ϥ�����ɥ�
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
// ���٥�ȡ��ϥ�ɥ�
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
// �������ϥ�����ɥ��Υ��󥹥ȥ饯��
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
// �������ϥ�����ɥ��Υǥ��ȥ饯��
////////////////////////////////////////////////////////////////

GuiNum::~GuiNum()
{
}

////////////////////////////////////////////////////////////////
// �������ϥ�����ɥ��ν����
////////////////////////////////////////////////////////////////

void GuiNum::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// �������ϥ�����ɥ��κ���
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
	// �������ϥ�����ɥ��κ���

	mNumWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mNumWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mNumWin ),
			"Input number" );

	// �������ϥ�����ɥ��ؤΥ��٥�ȡ��ϥ�ɥ������

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

	// ��ʿ���������Ĵ���κ���

	mHscaleAdjustment = gtk_adjustment_new(
			0, -100, +(100 + 10),
			+1, +10, 10 );
	if( mHscaleAdjustment == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_adjustment_new()" );
		return;
	}

	// ��ʿ���������Ĵ���ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mHscaleAdjustment ),
			"changed",
			GTK_SIGNAL_FUNC( handle_num_hscale_changed ),
			(gpointer)0 );
	gtk_signal_connect( GTK_OBJECT( mHscaleAdjustment ),
			"value-changed",
			GTK_SIGNAL_FUNC( handle_num_hscale_changed ),
			(gpointer)0 );

	// ��ʿ��������κ���

	mHscale = gtk_hscale_new(
			GTK_ADJUSTMENT( mHscaleAdjustment ) );
	if(mHscale  == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hscale_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mHscale,
			TRUE, TRUE, 0 );
	gtk_widget_show( mHscale );

	// ���ԥ󡦥ܥ����Ĵ�������

	mNumAdjustment = gtk_adjustment_new(
			0, -100, +100,
			+1, +10, 0 );
	if( mNumAdjustment == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_adjustment_new()" );
		return;
	}

	// ���ԥ󡦥ܥ����Ĵ���ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mNumAdjustment ),
			"changed",
			GTK_SIGNAL_FUNC( handle_num_spin_changed ),
			(gpointer)0 );
	gtk_signal_connect( GTK_OBJECT( mNumAdjustment ),
			"value-changed",
			GTK_SIGNAL_FUNC( handle_num_spin_changed ),
			(gpointer)0 );

	// ���ԥ󡦥ܥ���κ���

	mNumSpin = gtk_spin_button_new(
			GTK_ADJUSTMENT( mNumAdjustment ), 1.0, 0 );
	if( mNumSpin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_spin_button_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mNumSpin,
			TRUE, TRUE, 0 );
	gtk_widget_show( mNumSpin );

	// �ܥ�������κ���

	GtkWidget *vBox[GUI_NUM_BUTTON_MAX_N];

	GtkWidget *hBox = gtk_hbox_new( FALSE, 0 );
	if( hBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_widget_show( hBox );

	for( long i = 0; i < GUI_NUM_BUTTON_MAX_N; i++ ){
		bool flagComma = ((i % 4) == 3);

		// ����������κ���

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

		// �����������κ���

		mArrowUp[i] = gtk_arrow_new(
				GTK_ARROW_UP, GTK_SHADOW_ETCHED_OUT );
		if( mArrowUp[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_arrow_new()" );
			return;
		}
		gtk_widget_show( mArrowUp[i] );

		// ��ܥ��������κ���

		mButtonUp[i] = gtk_button_new();
		if( mButtonUp[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_button_new()" );
			return;
		}
		gtk_container_add( GTK_CONTAINER( mButtonUp[i] ),
				mArrowUp[i] );
		gtk_widget_show( mButtonUp[i] );

		// �����������κ���

		mArrowDown[i] = gtk_arrow_new(
				GTK_ARROW_DOWN, GTK_SHADOW_OUT );
		if( mArrowDown[i] == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_arrow_new()" );
			return;
		}
		gtk_widget_show( mArrowDown[i] );

		// ���ܥ��������κ���

		mButtonDown[i] = gtk_button_new();
		if( mButtonDown[i]  == NULL ){
			print_msg( FLG_MSG_ERR, "gtk_button_new()" );
			return;
		}
		gtk_container_add( GTK_CONTAINER( mButtonDown[i] ),
				mArrowDown[i] );
		gtk_widget_show( mButtonDown[i] );

		// �ܥ�������ؤΥ��٥�ȡ��ϥ�ɥ������

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

		// �ܥå����ˤΤ���

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

	// �Ǿ��ܥ���κ���

	mButtonMin = gtk_button_new_with_label( "Min" );
	if( mButtonMin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonMin );

	// ���ꥢ���ܥ���κ���

	mButtonClear = gtk_button_new_with_label( "Clear" );
	if( mButtonClear == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonClear );

	// ����ܥ���κ���

	mButtonMax = gtk_button_new_with_label( "Max" );
	if( mButtonMax == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonMax );

	// OK �ܥ���κ���

	mButtonOk = gtk_button_new_with_label( "Ok" );
	if( mButtonOk == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_button_new_with_label()" );
		return;
	}
	gtk_widget_show( mButtonOk );

	// �Ǿ�������ܥ���ؤΥ��٥�ȡ��ϥ�ɥ������

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

	// �ܥå����ˤΤ���

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

	// �ܥå����ˤΤ���

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
// �������ϥ�����ɥ��κ��
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
// �������ϥ�����ɥ���ɽ��
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
// �������ϥ�����ɥ��κ�ɽ��
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
// �������ϥ�����ɥ����Ĥ���
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
// ��ʿ��������ȥ��ԥ󡦥ܥ����Ĵ�����Ѳ��ν���
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
// ��٥�ο��ͤ���������
// long n : ��٥��ֹ�
// long d : +1, -1 �ξ���������0 �ξ��� 0 ���ꥢ
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
// ����ʸ������������
// char c : ����ʸ��
// long d : +1, -1 �ξ���������0 �ξ��� 0 ���ꥢ
// return : ����ʸ��
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
// �ܥ����������ͤ��Ѵ�
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
// �ܥ�������˿��ͤ�����
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
// �Ǿ�������ܥ���Υ���å��ν���
// menu_num_t n : �ܥ���μ���
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
// �������ϥ�����ɥ����Ĥ�������Υϥ�ɥ�
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
// �������ϥ�����ɥ��ν�λ�����Υϥ�ɥ�
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
// �������ϥ�����ɥ������襤�٥�Ȥν���
// GtkWidget *widget : ��å������Υɥ����󥰡����ꥢ
// GdkEventExpose *event : ���٥��
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
// ��ʿ���������Ĵ�����Ѳ��Υϥ�ɥ�
// GtkAdjustment *adj : ��ʿ��������
// gpointer data : ���ߡ�
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
// ���ԥ󡦥ܥ����Ĵ�����Ѳ��Υϥ�ɥ�
// GtkAdjustment *adj : ��ʿ��������
// gpointer data : ���ߡ�
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
// ���ꥢ���ܥ�������Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer data : �ܥ����ֹ�
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
// ��ܥ�������Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer data : �ܥ����ֹ�
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
// ���ܥ�������Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer data : �ܥ����ֹ�
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
// �Ǿ�������ܥ���Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer data : �ܥ���μ���
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
