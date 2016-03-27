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
* $Id: GuiClassEdit.cpp,v 1.14 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ���饹�����ǥ�����������ɥ�
////////////////////////////////////////////////////////////////

#define GUI_CLASS_EDIT_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// ���٥�ȡ��ϥ�ɥ�
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
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

GuiClassEdit::GuiClassEdit()
{
	classData = NULL;
	mClassEditWin = NULL;
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

GuiClassEdit::~GuiClassEdit()
{
}

////////////////////////////////////////////////////////////////
// �����
////////////////////////////////////////////////////////////////

void GuiClassEdit::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// ���饹�����ǥ�����������ɥ��κ���
////////////////////////////////////////////////////////////////

void GuiClassEdit::newWin()
{
	if( mClassEditWin != NULL )
		return;

#ifdef D_WS
	mClassEditWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	// ������ɥ��κ���

	mClassEditWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mClassEditWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mClassEditWin ),
			MSG_GUI_CLASS_EDIT_TITLE );

	// ������ɥ��ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mClassEditWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_class_edit_destroy ),
			this );

	// �ܥå����κ���

	GtkWidget *vBoxWin = gtk_vbox_new( FALSE, 0 );
	if( vBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_container_add( GTK_CONTAINER( mClassEditWin ), vBoxWin );
	gtk_widget_show( vBoxWin );

	// ����ȥ꡼�����

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

		// ǽ���ͥ�٥�κ���

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

		// �ͥ�٥�κ���

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

		// �ܥ���κ���

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

		// ǽ���ͥ�٥�κ���

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

		// �ͥ�٥�κ���

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

		// �ܥ���κ���

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

	// �ܥå����κ���

	GtkWidget *hBoxTotal = gtk_hbox_new( FALSE, 0 );
	if( hBoxTotal == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), hBoxTotal, TRUE, TRUE, 0 );
	gtk_widget_show( hBoxTotal );

	// ����ͥ����ȥ�κ���

	mLabelTotal = gtk_label_new( "Total" );
	if( mLabelTotal == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( hBoxTotal ), mLabelTotal,
			FALSE, TRUE, 4 );
	gtk_widget_show( mLabelTotal );

	// ����ͥ�٥�κ���

	mLabelTotalValue = gtk_label_new( "100%" );
	if( mLabelTotalValue == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( hBoxTotal ), mLabelTotalValue,
			FALSE, TRUE, 4 );
	gtk_widget_show( mLabelTotalValue );

	// ��λ�ܥ���κ���

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
// ���饹�����ǥ�����������ɥ��κ��
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
// ���饹�����ǥ�����������ɥ���ɽ��
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
// ���饹�����ǥ�����������ɥ��κ�ɽ��
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
// ���饹�����ǥ�����������ɥ����Ĥ���
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
// �Խ��������饹̾����¸����
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
// + �ܥ���Υ���å��ν���
// abl_kind_t kind : ǽ���ͤμ���
////////////////////////////////////////////////////////////////

void GuiClassEdit::plusClicked( abl_kind_t kind )
{
	add( kind, +1 );
}

////////////////////////////////////////////////////////////////
// - �ܥ���Υ���å��ν���
// abl_kind_t kind : ǽ���ͤμ���
////////////////////////////////////////////////////////////////

void GuiClassEdit::minusClicked( abl_kind_t kind )
{
	add( kind, -1 );
}

////////////////////////////////////////////////////////////////
// �ͤ�����
// abl_kind_t kind : ǽ���ͤμ���
// long n : ������
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
// ��λ�ܥ���Υ���å��ν���
////////////////////////////////////////////////////////////////

void GuiClassEdit::exitClicked()
{
	setClassName();

	gKey.setChar( '0' );
}

////////////////////////////////////////////////////////////////
// ���饹�����ǥ�����������ɥ��ν�λ�����Υϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_class_edit_destroy( GtkWidget *widget, gpointer user_data )
{
	gGuiClassEdit.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// + �ܥ���Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer user_data : �桼�����ǡ���
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
// - �ܥ���Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer user_data : �桼�����ǡ���
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
// ��λ�ܥ���Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer user_data : �桼�����ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_class_edit_exit_clicked(
	GtkButton *button, gpointer user_data )
{
	gGuiClassEdit.exitClicked();

	return 0;
}
#endif // D_GTK
