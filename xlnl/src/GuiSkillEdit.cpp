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
* $Id: GuiSkillEdit.cpp,v 1.12 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// �����롦���ǥ�����������ɥ�
////////////////////////////////////////////////////////////////

#define GUI_SKILL_EDIT_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// ���٥�ȡ��ϥ�ɥ�
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
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

GuiSkillEdit::GuiSkillEdit()
{
	classData = NULL;
	mSkillEditWin = NULL;
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

GuiSkillEdit::~GuiSkillEdit()
{
}

////////////////////////////////////////////////////////////////
// �����
////////////////////////////////////////////////////////////////

void GuiSkillEdit::init()
{
	newWin();
}

////////////////////////////////////////////////////////////////
// �����롦���ǥ�����������ɥ��κ���
////////////////////////////////////////////////////////////////

void GuiSkillEdit::newWin()
{
	if( mSkillEditWin != NULL )
		return;

#ifdef D_WS
	mSkillEditWin = (void *)1;
#endif // D_WS

#ifdef D_GTK
	// ������ɥ��κ���

	mSkillEditWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mSkillEditWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	gtk_window_set_title( GTK_WINDOW( mSkillEditWin ),
			MSG_GUI_SKILL_EDIT_TITLE );

	// ������ɥ��ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mSkillEditWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_skill_edit_destroy ),
			this );

	// �ܥå����κ���

	GtkWidget *vBoxWin = gtk_vbox_new( FALSE, 0 );
	if( vBoxWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_container_add( GTK_CONTAINER( mSkillEditWin ), vBoxWin );
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

		// �����롦�ܥ���κ���

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

		// �ͥ�٥�κ���

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

	// �ҥ�ȡ���٥�κ���

	mLabelHint = gtk_label_new( "" );
	if( mLabelHint == NULL ){
		print_msg( FLG_MSG_ERR,
				"gtk_label_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), mLabelHint,
			FALSE, TRUE, 2 );
	gtk_widget_show( mLabelHint );

	// �ܥå����κ���

	GtkWidget *hBox = gtk_hbox_new( FALSE, 0 );
	if( hBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_hbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBoxWin ), hBox,
			FALSE, TRUE, 0 );
	gtk_widget_show( hBox );

	// ���ܥ���κ���

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

	// ���ܥ���κ���

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
			GTK_SIGNAL_FUNC( handle_skill_edit_exit_clicked ),
			NULL );
#endif	// D_GTK

#ifdef D_MFC
	mSkillEditWin = new CSkillEditDlg;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �����롦���ǥ�����������ɥ��κ��
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
// �����롦���ǥ�����������ɥ���ɽ��
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
// �����롦���ǥ�����������ɥ��κ�ɽ��
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

	// �ڡ����ڤ��ؤ�

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
// �����롦���ǥ�����������ɥ����Ĥ���
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
// �Խ��������饹̾����¸����
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
// �����롦�ܥ���Υ���å��ν���
// long nSlot : ����å��ֹ�
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
// ���ܥ���Υ���å��ν���
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
// ���ܥ���Υ���å��ν���
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
// ��λ�ܥ���Υ���å��ν���
////////////////////////////////////////////////////////////////

void GuiSkillEdit::exitClicked()
{
	setClassName();

	gKey.setChar( '0' );
}

////////////////////////////////////////////////////////////////
// �����롦���ǥ�����������ɥ��ν�λ�����Υϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_edit_destroy( GtkWidget *widget, gpointer user_data )
{
	gGuiSkillEdit.destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// �����롦�ܥ���Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer user_data : �桼�����ǡ���
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
// ���ܥ���Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer user_data : �桼�����ǡ���
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
// ���ܥ���Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer user_data : �桼�����ǡ���
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
// ��λ�ܥ���Υ���å��Υϥ�ɥ�
// GtkButton *button : �ܥ���
// gpointer user_data : �桼�����ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_skill_edit_exit_clicked(
	GtkButton *button, gpointer user_data )
{
	gGuiSkillEdit.exitClicked();

	return 0;
}
#endif // D_GTK
