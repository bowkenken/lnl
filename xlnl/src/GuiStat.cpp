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
* $Id: GuiStat.cpp,v 1.36 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#define GUI_STAT_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define	STR_GUI_STAT_HP	"HP: %4ld/%4ld"
#define	STR_GUI_STAT_MP	"MP: %4ld/%4ld"

#define	GUI_STAT_HP_MP_X	4
#define	GUI_STAT_HP_MP_Y	8
#define	GUI_STAT_HP_MP_WIDTH	128
#define	GUI_STAT_HP_MP_HEIGHT	2
#define	GUI_STAT_HP_MP_MAX_WIDTH	\
		(GUI_STAT_HP_MP_X * 2 + GUI_STAT_HP_MP_WIDTH)
#define	GUI_STAT_HP_MP_MAX_HEIGHT	16

////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_win_delete(
	GtkWidget *widget, gpointer data
);
gint handle_stat_win_destroy(
	GtkWidget *widget, gpointer data
);
gint handle_stat_win_expose(
	GtkWidget *widget, GdkEventExpose *event
);
gint handle_stat_win_configure(
	GtkWidget *widget, GdkEventConfigure *event
);

gint handle_stat_name_clicked(
	GtkWidget *widget, gpointer data
);
gint handle_stat_stat_clicked(
	GtkWidget *widget, gpointer data
);
gint handle_stat_mode_clicked(
	GtkWidget *widget, gpointer data
);
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ���ơ������Υ��󥹥ȥ饯��
////////////////////////////////////////////////////////////////

GuiStat::GuiStat()
{
	mStatWin = NULL;

#ifdef D_GTK
	vBox = NULL;
	for( long i = 0; i < MBR_MAX_N; i++ ){
		mFgGcHp[i] = NULL;
		mBgGcHp[i] = NULL;
		mFgGcMp[i] = NULL;
		mBgGcMp[i] = NULL;
	}
	mFgGcHpMp = NULL;
	mBgGcHpMp = NULL;
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// ���ơ������Υǥ��ȥ饯��
////////////////////////////////////////////////////////////////

GuiStat::~GuiStat()
{
}

////////////////////////////////////////////////////////////////
// ���ơ������ν����
////////////////////////////////////////////////////////////////

void GuiStat::init()
{
	newWin();
	redraw();
}

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ��κ���
////////////////////////////////////////////////////////////////

void GuiStat::newWin()
{
	if( mStatWin != NULL )
		return;

	mStrPreDunLev[0] = '\0';
	mStrPreTime[0] = '\0';
	mPreMode = STAT_MODE_MBR;

#ifdef D_GTK
	// ���ơ�������������ɥ��κ���

	mStatWin = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	if( mStatWin == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_window_new()" );
		return;
	}
	g_object_set( GTK_WINDOW( mStatWin ),
			"allow-shrink", FALSE,
			"allow-grow", FALSE,
			NULL );
	gtk_window_set_title( GTK_WINDOW( mStatWin ),
			"Stat" );

	// ���ơ�������������ɥ��ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( mStatWin ),
			"delete_event",
			GTK_SIGNAL_FUNC( handle_stat_win_delete ),
			this );
	gtk_signal_connect( GTK_OBJECT( mStatWin ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_stat_win_destroy ),
			this );
	gtk_signal_connect( GTK_OBJECT( mStatWin ),
			"expose_event",
			GTK_SIGNAL_FUNC( handle_stat_win_expose ),
			this );
	gtk_signal_connect( GTK_OBJECT( mStatWin ),
			"configure_event",
			GTK_SIGNAL_FUNC( handle_stat_win_configure ),
			this );
	gtk_signal_connect( GTK_OBJECT( mStatWin ),
			"key-press-event",
			GTK_SIGNAL_FUNC( handleKeyPress ), NULL );

	// ��ľ�ܥå����κ���

	vBox = gtk_vbox_new( FALSE, 0 );
	if( vBox == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_container_add( GTK_CONTAINER( mStatWin ), vBox );
	gtk_widget_show( vBox );

	// �ƥ��С������

	party_t *pty = get_party();
	for( long i = 0; i < MBR_MAX_N; i++ )
		newWinMbr( pty->mbr[i], vBox );

	// ����¾�ξ�������

	vBoxMisc = gtk_vbox_new( FALSE, 0 );
	if( vBoxMisc == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_vbox_new()" );
		return;
	}
	gtk_box_pack_start( GTK_BOX( vBox ),
			vBoxMisc, FALSE, FALSE, 0 );
	gtk_widget_show( vBoxMisc );

	// ���ؤ����

	labelDunLev = gtk_label_new( "Floor : 9999" );
	gtk_box_pack_start( GTK_BOX( vBoxMisc ),
			labelDunLev, FALSE, FALSE, 0 );
	gtk_widget_show( labelDunLev );

	// ���դ����

	labelTime = gtk_label_new( "12::00::" );
	gtk_box_pack_start( GTK_BOX( vBoxMisc ),
			labelTime, FALSE, FALSE, 0 );
	gtk_widget_show( labelTime );

	// �⡼���ڤ괹�������

	btnMode = gtk_button_new_with_label( MSG_STAT_MODE_MBR );
	gtk_signal_connect( GTK_OBJECT( btnMode ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_stat_mode_clicked ),
			NULL );
	gtk_box_pack_start( GTK_BOX( vBoxMisc ),
			btnMode, FALSE, FALSE, 0 );
	gtk_widget_show( btnMode );
#endif // D_GTK

#ifdef D_MFC
	mStatWin = &(theApp.m_StatWnd);
#endif // D_MFC

	gWinPos[WIN_KIND_STAT].get( WIN_KIND_STAT,
			NULL, NULL, NULL, NULL );
	gWinPos[WIN_KIND_STAT].draw( WIN_KIND_STAT );
}

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ��γƥ��С������
// mbr_t *mbr : ���С�
// GtkWidget *vBox : ������
////////////////////////////////////////////////////////////////

#ifdef D_GTK
void GuiStat::newWinMbr( mbr_t *mbr, GtkWidget *vBox )
{
	if( mbr == NULL )
		return;
	if( vBox == NULL )
		return;

	long n = mbr->mbr_n;

	// �ġ��롦�С������

	handleBox[n] = gtk_handle_box_new();
	gtk_box_pack_start( GTK_BOX( vBox ), handleBox[n], FALSE, FALSE, 0 );
	gtk_widget_show( handleBox[n] );

	toolBar[n] = gtk_toolbar_new();
	gtk_toolbar_set_orientation( GTK_TOOLBAR( toolBar[n] ),
			GTK_ORIENTATION_HORIZONTAL );
	gtk_toolbar_set_style( GTK_TOOLBAR( toolBar[n] ),
			GTK_TOOLBAR_ICONS );
	gtk_widget_show( toolBar[n] );

	gtk_container_add( GTK_CONTAINER( handleBox[n] ), toolBar[n] );

	vBox2[n] = gtk_vbox_new( FALSE, 0 );
	gtk_container_add( GTK_CONTAINER( toolBar[n] ), vBox2[n] );
	gtk_widget_show( vBox2[n] );

	// ���ơ����������ܥ���κ���

	WSCstring sName, sAct, sStat, sHp, sMp;
	long nHp, nMp, nMaxHp, nMaxMp;
	static char buf[80 * 8 + 1];

	sprintf( buf, "%*c", MBR_NAME_MAX_LEN, ' ' );
	sName = buf;

	sprintf( buf, "%*c", ACT_MSG_MAX_LEN, ' ' );
	sAct = buf;

	sprintf( buf, "%*c", WIN_STAT_DRAW_WIDTH, ' ' );
	sStat = buf;

	nHp = 0;
	nMp = 0;
	nMaxHp = 0;
	nMaxMp = 0;

	char bufHp[31 + 1];
	char bufMp[31 + 1];
	sprintf( bufHp, STR_GUI_STAT_HP, nHp, nMaxHp );
	sprintf( bufMp, STR_GUI_STAT_MP, nMp, nMaxMp );
	sHp = bufHp;
	sMp = bufMp;

	btnName[n] = gtk_button_new_with_label( sName );
	labelAct[n] = gtk_label_new( sAct );
	btnStat[n] = gtk_button_new_with_label( sStat );
	labelHp[n] = gtk_label_new( sHp );
	labelMp[n] = gtk_label_new( sMp );

	gtk_widget_show( btnName[n] );
	gtk_widget_show( labelAct[n] );
	gtk_widget_show( btnStat[n] );
	gtk_widget_show( labelHp[n] );
	gtk_widget_show( labelMp[n] );

	hBox1[n] = gtk_hbox_new( FALSE, 0 );
	gtk_box_pack_start( GTK_BOX( hBox1[n] ),
			btnName[n], FALSE, FALSE, 0 );
	gtk_box_pack_start( GTK_BOX( hBox1[n] ),
			labelAct[n], FALSE, FALSE, 0 );
	gtk_widget_show( hBox1[n] );

	// ���襨�ꥢ����� HP

	mDrawingAreaHp[n] = gtk_drawing_area_new();
	if( mDrawingAreaHp[n] == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_drawing_area_new()" );
		return;
	}
	gtk_drawing_area_size( GTK_DRAWING_AREA( mDrawingAreaHp[n] ),
			GUI_STAT_HP_MP_MAX_WIDTH,
			GUI_STAT_HP_MP_MAX_HEIGHT );
	gtk_widget_show( mDrawingAreaHp[n] );

	// ���襨�ꥢ����� MP

	mDrawingAreaMp[n] = gtk_drawing_area_new();
	if( mDrawingAreaMp[n] == NULL ){
		print_msg( FLG_MSG_ERR, "gtk_drawing_area_new()" );
		return;
	}
	gtk_drawing_area_size( GTK_DRAWING_AREA( mDrawingAreaMp[n] ),
			GUI_STAT_HP_MP_MAX_WIDTH,
			GUI_STAT_HP_MP_MAX_HEIGHT );
	gtk_widget_show( mDrawingAreaMp[n] );

	// HP

	hBoxHp[n] = gtk_hbox_new( FALSE, 0 );
	gtk_box_pack_start( GTK_BOX( hBoxHp[n] ), labelHp[n],
			FALSE, FALSE, 0 );
	gtk_box_pack_start( GTK_BOX( hBoxHp[n] ), mDrawingAreaHp[n],
			FALSE, FALSE, 0 );
	gtk_widget_show( hBoxHp[n] );

	// MP

	hBoxMp[n] = gtk_hbox_new( FALSE, 0 );
	gtk_box_pack_start( GTK_BOX( hBoxMp[n] ), labelMp[n],
			FALSE, FALSE, 0 );
	gtk_box_pack_start( GTK_BOX( hBoxMp[n] ), mDrawingAreaMp[n],
			FALSE, FALSE, 0 );
	gtk_widget_show( hBoxMp[n] );

	//

	gtk_box_pack_start( GTK_BOX( vBox2[n] ), hBox1[n], FALSE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBox2[n] ), btnStat[n], FALSE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBox2[n] ), hBoxHp[n], FALSE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vBox2[n] ), hBoxMp[n], FALSE, TRUE, 0 );

	// ���ơ��������ܥ���ؤΥ��٥�ȡ��ϥ�ɥ������

	gtk_signal_connect( GTK_OBJECT( btnName[n] ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_stat_name_clicked ),
			(gpointer)n );
	gtk_signal_connect( GTK_OBJECT( btnStat[n] ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_stat_stat_clicked ),
			(gpointer)n );
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ��κ��
////////////////////////////////////////////////////////////////

void GuiStat::destroy()
{
	if( mStatWin == NULL )
		return;

#ifdef D_GTK
	for( long i = 0; i < MBR_MAX_N; i++ ){
		gtk_widget_destroy( btnName[i] );
		gtk_widget_destroy( labelAct[i] );
		gtk_widget_destroy( btnStat[i] );
		gtk_widget_destroy( labelHp[i] );
		gtk_widget_destroy( labelMp[i] );

		btnName[i] = NULL;
		labelAct[i] = NULL;
		btnStat[i] = NULL;
		labelHp[i] = NULL;
		labelMp[i] = NULL;
	}

	gtk_widget_destroy( labelDunLev );
	gtk_widget_destroy( labelTime );
	gtk_widget_destroy( btnMode );
	labelDunLev = NULL;
	labelTime = NULL;
	btnMode = NULL;

	gtk_widget_destroy( vBox );

	mStatWin = NULL;
#endif // D_GTK

#ifdef D_MFC
	mStatWin = (CStatWnd *)NULL;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ����ɽ��
// bool flagAdj : 
// bool flagExpose : 
////////////////////////////////////////////////////////////////

void GuiStat::redraw( bool flagAdj, bool flagExpose )
{
	switch( get_stat_mode() ){
	case STAT_MODE_MAX_N:
	case STAT_MODE_MBR:
		for( long i = 0; i < MBR_MAX_N; i++ )
			draw( i, flagExpose );
		break;
	case STAT_MODE_PET:
		for( long i = 0; i < PET_MAX_N; i++ )
			draw( MBR_MAX_N + i, flagExpose );
		break;
	}

	drawMisc();

	gWinPos[WIN_KIND_STAT].get( WIN_KIND_STAT,
			NULL, NULL, NULL, NULL );
	if( !flagExpose )
		gWinPos[WIN_KIND_STAT].draw( WIN_KIND_STAT );

#ifdef D_GTK
	gtk_widget_show( vBox );
#endif // D_GTK

#ifdef D_MFC
	if( mStatWin != NULL ){
		if( flagAdj ){
			mStatWin->AdjustWnd();
		}
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ��γƥ��С���ɽ��
// long mbrN : ���С��ֹ�
// bool flagExpose : ������ɥ����¤��ؤ����٥�Ȥ�?
////////////////////////////////////////////////////////////////

void GuiStat::draw( long n, bool flagExpose )
{
	newWin();

	party_t *pty = get_party();
	pet_t **pty_pet = get_party_pet();
	mbr_t *mbr = NULL;
	if( n < 0 ){
		return;
	} else if( n < MBR_MAX_N ){
		mbr = pty->mbr[n];
	} else if( n < (MBR_MAX_N + PET_MAX_N) ){
		n -= MBR_MAX_N;
		mbr = pty_pet[n];
	} else {
		return;
	}

	/* ���С��������å� */

	if( mbr != NULL ){
		switch( get_stat_mode() ){
		case STAT_MODE_MAX_N:
		case STAT_MODE_MBR:
			if( !is_mbr( mbr ) )
				return;
			break;
		case STAT_MODE_PET:
			if( !is_pet( mbr ) )
				return;
			break;
		}
	}

	WSCstring sName, sAct, sStat, sHp, sMp;
	long nHp, nMp, nMaxHp, nMaxMp;

	if( (mbr == NULL) || chk_flg( mbr->stat, FLG_STAT_NOT_EXIST ) ){
		sName = "";
		sAct = "";
		sStat = "";
		nHp = 0;
		nMp = 0;
		nMaxHp = 0;
		nMaxMp = 0;
	} else {
		sName = mbr->name;
		sAct = mbr->act.msg;
		sStat = getStatStr( mbr );
		nHp = mbr->abl.hp.n;
		nMp = mbr->abl.mp.n;
		nMaxHp = mbr->abl.hp.max;
		nMaxMp = mbr->abl.mp.max;
	}

	char bufHp[31 + 1];
	char bufMp[31 + 1];
	sprintf( bufHp, STR_GUI_STAT_HP, nHp, nMaxHp );
	sprintf( bufMp, STR_GUI_STAT_MP, nMp, nMaxMp );
	sHp = bufHp;
	sMp = bufMp;

#ifdef D_GTK
	// ��٥������

	set_label_text_button( GTK_BUTTON( btnName[n] ),
			sName, 0.5, 0.5 );

	gtk_misc_set_alignment( GTK_MISC( labelAct[n] ), 0.0, 0.5 );
	gtk_label_set_text( GTK_LABEL( labelAct[n] ), (char *)sAct );

	set_label_text_button( GTK_BUTTON( btnStat[n] ),
			sStat, 0.5, 0.5 );

	gtk_misc_set_alignment( GTK_MISC( labelHp[n] ), 0.0, 0.5 );
	gtk_label_set_text( GTK_LABEL( labelHp[n] ), (char *)sHp );

	gtk_misc_set_alignment( GTK_MISC( labelMp[n] ), 0.0, 0.5 );
	gtk_label_set_text( GTK_LABEL( labelMp[n] ), (char *)sMp );

	gtk_widget_show( handleBox[n] );
	gtk_widget_show( toolBar[n] );
	gtk_widget_show( vBox2[n] );
	gtk_widget_show( hBox1[n] );
	gtk_widget_show( btnName[n] );
	gtk_widget_show( labelAct[n] );
	gtk_widget_show( btnStat[n] );

	// HP/MP �ΥС�������

	drawHpMp( n, true );
	drawHpMp( n, false );
#endif // D_GTK

#ifdef D_MFC
	// ��٥������

	mStatWin->m_BtnName[n].SetWindowText( sName );
	mStatWin->m_LabelAct[n].SetWindowText( sAct );
	mStatWin->m_BtnStat[n].SetWindowText( sStat );
	mStatWin->m_LabelHp[n].SetWindowText( sHp );
	mStatWin->m_LabelMp[n].SetWindowText( sMp );

	// HP/MP �ΥС�������

	drawHpMp( n, true );
	drawHpMp( n, false );
#endif // D_MFC

	gWinPos[WIN_KIND_STAT].get( WIN_KIND_STAT,
			NULL, NULL, NULL, NULL );
	if( !flagExpose )
		gWinPos[WIN_KIND_STAT].draw( WIN_KIND_STAT );
}

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ��Τ���¾�ξ����ɽ��
////////////////////////////////////////////////////////////////

void GuiStat::drawMisc()
{
	newWin();

	long maxLen = 40;
	const char *sDunLev = get_stat_dun_lev_str();
	const char *sTime = get_stat_time_str();
	stat_mode_t nMode = (stat_mode_t)get_stat_mode();

#ifdef D_GTK
	if( strcmp( sDunLev, mStrPreDunLev ) != 0 ){
		gtk_misc_set_alignment( GTK_MISC( labelDunLev ),
				0.0, 0.5 );
		gtk_label_set_text( GTK_LABEL( labelDunLev ),
				(char *)sDunLev );

		str_nz_cpy( mStrPreDunLev, sDunLev, maxLen );
	}

	if( strcmp( sTime, mStrPreTime ) != 0 ){
		gtk_misc_set_alignment( GTK_MISC( labelTime ),
				0.0, 0.5 );
		gtk_label_set_text( GTK_LABEL( labelTime ),
				(char *)sTime );

		str_nz_cpy( mStrPreTime, sTime, maxLen );
	}

	if( nMode != mPreMode ){
		const char *sMode = "----";

		switch( get_stat_mode() ){
		case STAT_MODE_MAX_N:
		case STAT_MODE_MBR:
			sMode = MSG_STAT_MODE_MBR;
			break;
		case STAT_MODE_PET:
			sMode = MSG_STAT_MODE_PET;
			break;
		}

		set_label_text_button( GTK_BUTTON( btnMode ),
				sMode, 0.5, 0.5 );

		mPreMode = nMode;
	}

	gtk_widget_show( labelDunLev );
	gtk_widget_show( labelTime );
	gtk_widget_show( btnMode );
#endif // D_GTK

#ifdef D_MFC
	if( strcmp( sDunLev, mStrPreDunLev ) != 0 ){
		mStatWin->m_LabelDunLev.SetWindowText( sDunLev );
	}

	if( strcmp( sTime, mStrPreTime ) != 0 ){
		mStatWin->m_LabelTime.SetWindowText( sTime );
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ��� HP/MP �ΥС�������
// long n : ���С��ֹ�
// bool flagHp : HP �����褫? : true => HP, false => MP
////////////////////////////////////////////////////////////////

void GuiStat::drawHpMp( long n, bool flagHp )
{
	party_t *pty = get_party();
	mbr_t *mbr = pty->mbr[n];

	long nHpMp, nMaxHpMp;
	if( flagHp ){
		nHpMp = mbr->abl.hp.n;
		nMaxHpMp = mbr->abl.hp.max;
	} else {
		nHpMp = mbr->abl.mp.n;
		nMaxHpMp = mbr->abl.mp.max;
	}

#ifdef D_GTK
	if( mDrawingAreaHp[n] == NULL)
		return;
	if( mDrawingAreaMp[n] == NULL)
		return;
	if( mDrawingAreaHp[n]->window == NULL)
		return;
	if( mDrawingAreaMp[n]->window == NULL)
		return;

	if( mFgGcHp[n] == NULL )
		mFgGcHp[n] = gdk_gc_new( mDrawingAreaHp[n]->window );
	if( mBgGcHp[n] == NULL )
		mBgGcHp[n] = gdk_gc_new( mDrawingAreaHp[n]->window );

	if( mFgGcMp[n] == NULL )
		mFgGcMp[n] = gdk_gc_new( mDrawingAreaMp[n]->window );
	if( mBgGcMp[n] == NULL )
		mBgGcMp[n] = gdk_gc_new( mDrawingAreaMp[n]->window );

	GdkDrawable *gdHpMp = NULL;
	if( flagHp ){
		mFgGcHpMp = mFgGcHp[n];
		mBgGcHpMp = mBgGcHp[n];
		gdHpMp = GDK_DRAWABLE( mDrawingAreaHp[n]->window );
	} else {
		mFgGcHpMp = mFgGcMp[n];
		mBgGcHpMp = mBgGcMp[n];
		gdHpMp = GDK_DRAWABLE( mDrawingAreaMp[n]->window );
	}

	GdkColor colorFg[3];
	GdkColor colorBg;
	long maxW = 1;
	long w = 1;

	// ��������

	rate_t nHpMpRate = 0;

	if( nMaxHpMp > 0 ){
		nHpMpRate = nHpMp * 100;
		nHpMpRate /= nMaxHpMp;

		colorBg.red = 0x0000;
		colorBg.green = 0x0000;
		colorBg.blue = 0x0000;
	} else {
		nHpMpRate = 0;

		colorBg.red = 0x8888;
		colorBg.green = 0x8888;
		colorBg.blue = 0x8888;
	}

	long nRateRed, nRateYellow, nRateGreen;
	if( flagHp ){
		nRateRed = WARNING_HP_RATE_RED;
		nRateYellow = WARNING_HP_RATE_YELLOW;
		nRateGreen = WARNING_HP_RATE_GREEN;
	} else {
		nRateRed = WARNING_MP_RATE_RED;
		nRateYellow = WARNING_MP_RATE_YELLOW;
		nRateGreen = WARNING_MP_RATE_GREEN;
	}

	if( nHpMpRate <= nRateRed ){
		colorFg[0].red = 0xeeee;
		colorFg[0].green = 0x0000;
		colorFg[0].blue = 0x0000;

		colorFg[1].red = 0xcccc;
		colorFg[1].green = 0x0000;
		colorFg[1].blue = 0x0000;

		colorFg[2].red = 0xaaaa;
		colorFg[2].green = 0x0000;
		colorFg[2].blue = 0x0000;
	} else if( nHpMpRate <= nRateYellow ){
		colorFg[0].red = 0xaaaa;
		colorFg[0].green = 0xaaaa;
		colorFg[0].blue = 0x0000;

		colorFg[1].red = 0x8888;
		colorFg[1].green = 0x8888;
		colorFg[1].blue = 0x0000;

		colorFg[2].red = 0x6666;
		colorFg[2].green = 0x6666;
		colorFg[2].blue = 0x0000;
	} else if( nHpMpRate <= nRateGreen ){
		if( flagHp ){
			colorFg[0].red = 0x0000;
			colorFg[0].green = 0xcccc;
			colorFg[0].blue = 0x0000;

			colorFg[1].red = 0x0000;
			colorFg[1].green = 0xaaaa;
			colorFg[1].blue = 0x0000;

			colorFg[2].red = 0x0000;
			colorFg[2].green = 0x8888;
			colorFg[2].blue = 0x0000;
		} else {
			colorFg[0].red = 0x0000;
			colorFg[0].green = 0xcccc;
			colorFg[0].blue = 0xcccc;

			colorFg[1].red = 0x0000;
			colorFg[1].green = 0xaaaa;
			colorFg[1].blue = 0xaaaa;

			colorFg[2].red = 0x0000;
			colorFg[2].green = 0x8888;
			colorFg[2].blue = 0x8888;
		}
	} else {
		colorFg[0].red = 0xffff;
		colorFg[0].green = 0xffff;
		colorFg[0].blue = 0xffff;

		colorFg[1].red = 0xffff;
		colorFg[1].green = 0xffff;
		colorFg[1].blue = 0xffff;

		colorFg[2].red = 0xffff;
		colorFg[2].green = 0xffff;
		colorFg[2].blue = 0xffff;
	}

	// HP/MP �ΥС�������

	gdk_color_alloc( gdk_colormap_get_system(), &colorBg );
	gdk_gc_set_background( mBgGcHpMp, &colorBg );

	maxW = 128;
	w = maxW * nHpMpRate / _100_PERCENT;

	gdk_color_alloc( gdk_colormap_get_system(), &colorBg );
	gdk_gc_set_foreground( mBgGcHpMp, &colorBg );
	gdk_draw_rectangle( gdHpMp, mBgGcHpMp, TRUE,
			GUI_STAT_HP_MP_X,
			GUI_STAT_HP_MP_Y,
			maxW,
			GUI_STAT_HP_MP_HEIGHT * 3 );

	for( long i = 0; i < 3; i++ ){
		gdk_color_alloc( gdk_colormap_get_system(),
				&colorFg[i] );
		gdk_gc_set_foreground( mFgGcHpMp, &colorFg[i] );
		gdk_draw_rectangle( gdHpMp, mFgGcHpMp, TRUE,
				GUI_STAT_HP_MP_X,
				GUI_STAT_HP_MP_Y + GUI_STAT_HP_MP_HEIGHT * i,
				w,
				GUI_STAT_HP_MP_HEIGHT );
	}
#endif // D_GTK

#ifdef D_MFC
	COLORREF colorFg[3];
	COLORREF colorBg;
	CClientDC dc( mStatWin );
	CRect rcWin, rcAct, rcHpMp, rcBase, rcBg, rc;
	long x = 0;
	long y = 0;
	long w = 1;
	long h = 1;
	long maxW = 1;

	// ��������

	rate_t nHpMpRate = 0;

	if( nMaxHpMp > 0 ){
		nHpMpRate = nHpMp * 100;
		nHpMpRate /= nMaxHpMp;

		colorBg = RGB( 0x0000, 0x0000, 0x0000 );
	} else {
		nHpMpRate = 0;

		colorBg = RGB( 0x8888, 0x8888, 0x8888 );
	}

	long nRateRed, nRateYellow, nRateGreen;
	if( flagHp ){
		nRateRed = WARNING_HP_RATE_RED;
		nRateYellow = WARNING_HP_RATE_YELLOW;
		nRateGreen = WARNING_HP_RATE_GREEN;
	} else {
		nRateRed = WARNING_MP_RATE_RED;
		nRateYellow = WARNING_MP_RATE_YELLOW;
		nRateGreen = WARNING_MP_RATE_GREEN;
	}

	if( nHpMpRate <= nRateRed ){
		colorFg[0] = RGB( 0xeeee, 0x0000, 0x0000 );
		colorFg[1] = RGB( 0xcccc, 0x0000, 0x0000 );
		colorFg[2] = RGB( 0xaaaa, 0x0000, 0x0000 );
	} else if( nHpMpRate <= nRateYellow ){
		colorFg[0] = RGB( 0xaaaa, 0xaaaa, 0x0000 );
		colorFg[1] = RGB( 0x8888, 0x8888, 0x0000 );
		colorFg[2] = RGB( 0x6666, 0x6666, 0x0000 );
	} else if( nHpMpRate <= nRateGreen ){
		if( flagHp ){
			colorFg[0] = RGB( 0x0000, 0xcccc, 0x0000 );
			colorFg[1] = RGB( 0x0000, 0xaaaa, 0x0000 );
			colorFg[2] = RGB( 0x0000, 0x8888, 0x0000 );
		} else {
			colorFg[0] = RGB( 0x0000, 0xcccc, 0xcccc );
			colorFg[1] = RGB( 0x0000, 0xaaaa, 0xaaaa );
			colorFg[2] = RGB( 0x0000, 0x8888, 0x8888 );
		}
	} else {
		colorFg[0] = RGB( 0xffff, 0xffff, 0xffff );
		colorFg[1] = RGB( 0xffff, 0xffff, 0xffff );
		colorFg[2] = RGB( 0xffff, 0xffff, 0xffff );
	}

	// �����ϰϤ����

	mStatWin->GetWindowRect( &rcWin );
	mStatWin->m_LabelAct[n].GetWindowRect( &rcAct );
	if( flagHp ){
		mStatWin->m_LabelHp[n].GetWindowRect( &rcHpMp );
		mStatWin->m_LabelHp[n].GetWindowRect( &rcBase );
	} else {
		mStatWin->m_LabelMp[n].GetWindowRect( &rcHpMp );
		mStatWin->m_LabelMp[n].GetWindowRect( &rcBase );
	}

	// �طʤ򥯥ꥢ

	x = rcHpMp.right;
	y = rcHpMp.top;
	w = rcAct.Width() - rcHpMp.Width();
	h = rcHpMp.Height();
	rcBg.SetRect( x, y, x + w, y + h );

	::AdjustWindowRectEx( &rcBg,
			mStatWin->GetStyle(), FALSE,
			mStatWin->GetExStyle() );
	rcBg.left -= rcWin.left;
	rcBg.top -= rcWin.top;
	rcBg.right = rcBg.left + w;
	rcBg.bottom = rcBg.top + h;
	dc.FillSolidRect( rcBg,
			::GetSysColor( COLOR_BTNFACE ) );

	// HP/MP �ΥС�������

	w = rcBase.Width();
	h = rcBase.Height();
	::AdjustWindowRectEx( &rcBase,
			mStatWin->GetStyle(), FALSE,
			mStatWin->GetExStyle() );
	rcBase.left -= rcWin.left;
	rcBase.top -= rcWin.top;
	rcBase.right = rcBase.left + w;
	rcBase.bottom = rcBase.top + h;

	x = rcBase.right + GUI_STAT_HP_MP_X;
	y = rcBase.top + GUI_STAT_HP_MP_Y;

	maxW = rcAct.Width() - rcHpMp.Width();
	maxW -= GUI_STAT_HP_MP_X * 2;
	w = maxW * nHpMpRate / _100_PERCENT;

	h = GUI_STAT_HP_MP_HEIGHT * 3;
	rc.SetRect( x, y, x + maxW, y + h );
	dc.FillSolidRect( rc, colorBg );

	h = GUI_STAT_HP_MP_HEIGHT;
	for( long i = 0; i < 3; i++ ){
		long yy = y + GUI_STAT_HP_MP_HEIGHT * i;
		rc.SetRect( x, yy, x + w, yy + h );
		dc.FillSolidRect( rc, colorFg[i] );
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ���ơ�������ʸ��������
// mbr_t *mbr : ���С�
// return : ���ơ�������ʸ����
////////////////////////////////////////////////////////////////

WSCstring GuiStat::getStatStr( mbr_t *mbr )
{
	WSCstring str;
	WSCstring strSplit = "  ";

	if( chk_flg( mbr->stat, FLG_STAT_DEAD ) ){
		str += MSG_STAT_DEAD;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_STONE ) ){
		str += MSG_STAT_STONE;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_FAINT ) ){
		str += MSG_STAT_FAINT;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_PARALYZE ) ){
		str += MSG_STAT_PARALYZE;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_POISON ) ){
		str += MSG_STAT_POISON;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_CONFUSION ) ){
		str += MSG_STAT_CONFUSION;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_BLIND ) ){
		str += MSG_STAT_BLIND;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_SLEEP ) ){
		str += MSG_STAT_SLEEP;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_SILENCE ) ){
		str += MSG_STAT_SILENCE;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_CAUGHT ) ){
		str += MSG_STAT_CAUGHT;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_FEAR ) ){
		str += MSG_STAT_FEAR;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_HALLUCINATION ) ){
		str += MSG_STAT_HALLUCINATION;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_CHARM ) ){
		str += MSG_STAT_CHARM;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_DRUNK ) ){
		str += MSG_STAT_DRUNK;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_FLY ) ){
		str += MSG_STAT_FLY;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_VANISH ) ){
		str += MSG_STAT_VANISH;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_IRON_BODY ) ){
		str += MSG_STAT_IRON_BODY;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_PASSWALL ) ){
		str += MSG_STAT_PASSWALL;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_SENSE_INVISIBLE ) ){
		str += MSG_STAT_SENSE_INVISIBLE;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_STARVATION ) ){
		str += MSG_STAT_STARVATION;
		str += strSplit;
	}

	if( chk_flg( mbr->stat, FLG_STAT_HUNGRY ) ){
		str += MSG_STAT_HUNGRY;
		str += strSplit;
	}

	return str;
}

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ����Ĥ�������Υϥ�ɥ�
// GtkWidget *widget : ���ơ�������������ɥ�
// gpointer data : ��Ͽ�����Ϥ��줿����
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_win_delete(
	GtkWidget *widget, gpointer data
)
{
	gWinPos[WIN_KIND_STAT].wipe( WIN_KIND_STAT );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ��κ�����Υ��٥�ȡ��ϥ�ɥ�
// GtkWidget *widget : ���ơ�������������ɥ�
// gpointer data : ��Ͽ�����Ϥ��줿����
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_win_destroy(
	GtkWidget *widget, gpointer data
)
{
	if( data == NULL )
		return 0;

	((GuiStat *)data)->destroy();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ������襤�٥�Ȥν���
// GtkWidget *widget : ��å������Υɥ����󥰡����ꥢ
// GdkEventExpose *event : ���٥��
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_win_expose(
	GtkWidget *widget, GdkEventExpose *event
)
{
	gGuiStat.redraw( true );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ���ơ�������������ɥ��Υ������ѹ����٥�Ȥν���
// GtkWidget *widget : ��å������Υɥ����󥰡����ꥢ
// GdkEventConfigure *event : ���٥��
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_win_configure(
	GtkWidget *widget, GdkEventConfigure *event
)
{
	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ����饯��̾�ܥ���κ�����å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_name_clicked(
	GtkWidget *widget, gpointer data
)
{
	if( chk_party_in_shop() )
		return 0;

	long n = (long)data;
	switch( get_stat_mode() ){
	case STAT_MODE_MAX_N:
	case STAT_MODE_MBR:
		break;
	case STAT_MODE_PET:
		n += MBR_MAX_N;
		break;
	}

	char sCmdMbr[15 + 1];
	sCmdMbr[0] = 'A' + n;
	sCmdMbr[1] = '\0';

	// ��˥塼�򳫤��Ƥ������Ĥ���

	WSCstring sCmd = "";
	sCmd = "00000000000000000000";

	// ���С��ΰ��֤˥���������ư

	sCmd += ":/misc/cursor/cursor/move member\n";
	sCmd += sCmdMbr;

	// ��˥塼�򳫤�

	sCmd += "^M";

	// ���ޥ�ɤ�����

	set_key_buf_str_tail( sCmd );
	set_flg_break_key( TRUE );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ����饯���Υ��ơ��������ܥ���κ�����å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_stat_clicked(
	GtkWidget *widget, gpointer data
)
{
	if( chk_party_in_shop() )
		return 0;

	long n = (long)data;
	switch( get_stat_mode() ){
	case STAT_MODE_MAX_N:
	case STAT_MODE_MBR:
		break;
	case STAT_MODE_PET:
		n += MBR_MAX_N;
		break;
	}

	char sCmdMbr[15 + 1];
	sCmdMbr[0] = 'A' + n;
	sCmdMbr[1] = '\0';

	// ��˥塼�򳫤��Ƥ������Ĥ���

	WSCstring sCmd = "";
	sCmd = "00000000000000000000";

	// ���С��ΰ��֤˥���������ư

	sCmd += ":/misc/cursor/cursor/move member\n";
	sCmd += sCmdMbr;

	// ����饯���������Ȥ�ɽ��

	sCmd += ":/misc/info/char data\n";

	// ���ޥ�ɤ�����

	set_key_buf_str_tail( sCmd );
	set_flg_break_key( TRUE );

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// �⡼���ڤ괹���ܥ���κ�����å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint handle_stat_mode_clicked(
	GtkWidget *widget, gpointer data
)
{
	if( chk_party_in_shop() )
		return 0;

	// ��˥塼�򳫤��Ƥ������Ĥ���

	WSCstring sCmd = "";
	sCmd = "00000000000000000000";

	// �⡼�ɤ��ڤ괹��

	sCmd += ":/misc/info/switch status mode\n";

	// ���ޥ�ɤ�����

	set_key_buf_str_tail( sCmd );
	set_flg_break_key( TRUE );

	return 0;
}
#endif // D_GTK
