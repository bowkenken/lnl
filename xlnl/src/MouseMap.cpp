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
* $Id: MouseMap.cpp,v 1.48 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// �ޥ����Υ����롦�Хå�
////////////////////////////////////////////////////////////////

#define	MOUSE_MAP_CPP	1
#include "inc.h"

////////////////////////////////////////////////////////////////

//�ޥ������ۥ�����Υ���������ˡ
// 1 : ��������
// 0 : ľ�ܥ�������
#define	FLAG_KEY_SCROLL	0

////////////////////////////////////////////////////////////////

#ifdef D_WS
extern WSCwindow* MenuWin;
extern WSCvscrBar *MapScrollX;
extern WSCvscrBar *MapScrollY;
#endif // D_WS

bool bFlagPressTimerRunning;
bool bFlagPressTimer[MouseMotion::nMouseButtonMaxN];

#ifdef D_GTK
gint nPressTimer;
#endif // D_GTK

////////////////////////////////////////////////////////////////
// �ޥ����Υ����롦�Хå��ν����
////////////////////////////////////////////////////////////////

void initMouseMotionFunc()
{
	bFlagPressTimerRunning = false;
	for( long i = (long)MouseMotion::nMouseButtonMinN;
			i < (long)MouseMotion::nMouseButtonMaxN; i++ ){
		bFlagPressTimer[i] = false;
	}

#ifdef D_GTK
	nPressTimer = 0;
#endif // D_GTK

	// �ݥ����

	gMouseMotion.setFuncPoint(
			funcMotionPoint );

	// ���ɥ�å�

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonL,
			MouseMotion::nMotionDrag,
			funcMotionDragL );

	// ���ܥ���κ������ɥ�å��Υ����롦�Хå�

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonR,
			MouseMotion::nMotionLeft,
			funcMotionLeftR );

	// ���ܥ���α������ɥ�å��Υ����롦�Хå�

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonR,
			MouseMotion::nMotionRight,
			funcMotionRightR );

	// ���ܥ���ξ������ɥ�å��Υ����롦�Хå�

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonR,
			MouseMotion::nMotionUp,
			funcMotionUpR );

	// ���ܥ���β������ɥ�å��Υ����롦�Хå�

	gMouseMotion.setFunc(
			MouseMotion::nMouseButtonR,
			MouseMotion::nMotionDown,
			funcMotionDownR );

	// ������å�

	gMouseMotion.setFuncClick(
			MouseMotion::nMouseButtonL,
			funcMotionClick );

	// �楯��å�

	gMouseMotion.setFuncClick(
			MouseMotion::nMouseButtonM,
			funcMotionClick );

	// ������å�

	gMouseMotion.setFuncClick(
			MouseMotion::nMouseButtonR,
			funcMotionClick );

	// ����å�

	long btnMin = (long)MouseMotion::nMouseButton3;
	long btnMax = (long)MouseMotion::nMouseButtonMaxN;
	for( long i = btnMin; i < btnMax; i++ ){
		gMouseMotion.setFuncClick(
				(MouseMotion::MouseButtonN)i,
				funcMotionClick );
	}

	// �����֥롦����å�

	gMouseMotion.setFuncDoubleClick(
			MouseMotion::nMouseButtonL,
			funcMotionDoubleClick );

	// ���ץ쥹

	gMouseMotion.setFuncPress(
			MouseMotion::nMouseButtonL,
			funcMotionPress );

	// ��ץ쥹

	gMouseMotion.setFuncPress(
			MouseMotion::nMouseButtonM,
			funcMotionPress );

	// ���ץ쥹

	gMouseMotion.setFuncPress(
			MouseMotion::nMouseButtonR,
			funcMotionPress );

	// ����꡼��

	gMouseMotion.setFuncRelease(
			MouseMotion::nMouseButtonL,
			funcMotionRelease );

	// ���꡼��

	gMouseMotion.setFuncRelease(
			MouseMotion::nMouseButtonM,
			funcMotionRelease );

	// ����꡼��

	gMouseMotion.setFuncRelease(
			MouseMotion::nMouseButtonR,
			funcMotionRelease );

	// ���ץ쥹 + ������å�

	gMouseMotion.setFuncClickLR(
			MouseMotion::nMouseButtonL,
			funcMotionClickLR );

	// ���ץ쥹 + ������å�

	gMouseMotion.setFuncClickLR(
			MouseMotion::nMouseButtonR,
			funcMotionClickLR );

	// ����������

	gMouseMotion.setFuncScroll(
			MouseMotion::nScrollLeft,
			funcMotionScroll );

	// ����������

	gMouseMotion.setFuncScroll(
			MouseMotion::nScrollRight,
			funcMotionScroll );

	// �她������

	gMouseMotion.setFuncScroll(
			MouseMotion::nScrollUp,
			funcMotionScroll );

	// ����������

	gMouseMotion.setFuncScroll(
			MouseMotion::nScrollDown,
			funcMotionScroll );
}

////////////////////////////////////////////////////////////////
// �ޥ�������������ˤ��ݥ���ȤΥ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionPoint(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	if( get_flg_draw_menu() )
		return;

	// �ޥåס���������ΰ�ư

#ifdef D_MFC
	if( g_flg_gui ){
		nCurX = nCurX * _100_PERCENT / g_Dir3d.nTileSizeRate;
		nCurY = nCurY * _100_PERCENT / g_Dir3d.nTileSizeRate;
	}
#endif // D_MFC

	long x = gPcgDun.getScrollBarX();
	long y = gPcgDun.getScrollBarY();
	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();

	if( nCurX < 0 )
		return;
	if( nCurY < 0 )
		return;
	if( nCurX >= w )
		return;
	if( nCurY >= h )
		return;

	long mapX = (x + nCurX) / gPcgDun.getTileSizeX( true );
	long mapY = (y + nCurY) / gPcgDun.getTileSizeY( true );
	long mapX2 = (x + w) / gPcgDun.getTileSizeX( true );
	long mapY2 = (y + h) / gPcgDun.getTileSizeY( true );

	if( mapX >= mapX2 )
		return;
	if( mapY >= mapY2 )
		return;

	gKey.moveCrsrAbs( mapX, mapY );

	// ���ơ��������С��˥ҥ�Ȥ�ɽ��

	if( g_flg_gui )
		guiMapPrintStatBarHint();
}

////////////////////////////////////////////////////////////////
// ���ɥ�å��Υ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionDragL(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	long maxX = gPcgDun.getScrollBarMaxX();
	long maxY = gPcgDun.getScrollBarMaxY();
	long dx = nCurX - nBgnX;
	long dy = nCurY - nBgnY;
#ifdef D_MFC
	if( g_flg_gui ){
		dx = dx * _100_PERCENT / g_Dir3d.nTileSizeRate;
		dy = dy * _100_PERCENT / g_Dir3d.nTileSizeRate;
	}
#endif // D_MFC
	long x = gMapDragBgnX - dx;
	long y = gMapDragBgnY - dy;
	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();

	if( x < 0 )
		x = 0;
	if( y < 0 )
		y = 0;
	if( x > maxX)
		x = maxX;
	if( y > maxY)
		y = maxY;

	long sizX = gPcgDun.getTileSizeX( true );
	long sizY = gPcgDun.getTileSizeY( true );
	x = (x / sizX) * sizX;
	y = (y / sizY) * sizY;

	if( gPcgDun.chkScroll( x, y, w, h ) )
		gPcgDun.scrollMap( x, y );
}

////////////////////////////////////////////////////////////////
// ���ܥ���κ������ɥ�å��Υ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionLeftR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	callFuncKey( KEY_N_MOUSE_MOTION( KEY_N_MOUSE_MOTION_LEFT ) );
}

////////////////////////////////////////////////////////////////
// ���ܥ���α������ɥ�å��Υ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionRightR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	callFuncKey( KEY_N_MOUSE_MOTION( KEY_N_MOUSE_MOTION_RIGHT ) );
}

////////////////////////////////////////////////////////////////
// ���ܥ���ξ������ɥ�å��Υ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionUpR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	callFuncKey( KEY_N_MOUSE_MOTION( KEY_N_MOUSE_MOTION_UP ) );
}

////////////////////////////////////////////////////////////////
// ���ܥ���β������ɥ�å��Υ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionDownR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	callFuncKey( KEY_N_MOUSE_MOTION( KEY_N_MOUSE_MOTION_DOWN ) );
}

////////////////////////////////////////////////////////////////
// ����å��Υ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionClick(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	if( get_scene() == SCENE_N_GAME_OVER_END ){
		gKey.setChar( 'Q' - '@' );
		return;
	}

	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) ){
		if( n == MouseMotion::nMouseButtonL )
			gSelMbrGraph->sel( nBgnX, nBgnY );
		if( n == MouseMotion::nMouseButtonR )
			gSelMbrGraph->cancel();
	} else if( chk_scene_group( SCENE_GROUP_N_SPACE ) ){
		if( gPcgDun.pDemoEnding != NULL ){
			if( n == MouseMotion::nMouseButtonL )
				gPcgDun.pDemoEnding->space.addSpeedZ( +1 );
			if( n == MouseMotion::nMouseButtonR )
				gPcgDun.pDemoEnding->space.addSpeedZ( -1 );
		}
	} else {
		callFuncKey( KEY_N_MOUSE_CLICK( n ), true );
	}
}

////////////////////////////////////////////////////////////////
// ���֥롦����å��Υ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionDoubleClick(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) ){
		if( n == MouseMotion::nMouseButtonL )
			gSelMbrGraph->ok();
	} else {
		if( n == MouseMotion::nMouseButtonL ){
			unset_square_pos();
			callFuncKey( KEY_N_MOUSE_D_CLICK( n ), true );
		}
	}
}

////////////////////////////////////////////////////////////////
// ����Ʊ������å��Υ����롦�Хå�
// long m : ��˥ץ쥹�����ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionClickLR(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	if( get_flg_play_replay() ){
		gKey.setString( "," );
		return;
	}

	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	long fn = KEY_N_MOUSE_PRESS_L_CLICK_R;
	if( n == MouseMotion::nMouseButtonL )
		fn = KEY_N_MOUSE_PRESS_L_CLICK_R;
	else if( n == MouseMotion::nMouseButtonR )
		fn = KEY_N_MOUSE_PRESS_R_CLICK_L;
	else
		return;

	callFuncKey( KEY_N_MOUSE_P_CLICK( fn ) );
}

////////////////////////////////////////////////////////////////
// �ץ쥹�Υ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionPress(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	beginPressTimer( n );
}

////////////////////////////////////////////////////////////////
// ��꡼���Υ����롦�Хå�
// long m : �ޥ������ܥ����ֹ�
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionRelease(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	MouseMotion::MouseButtonN n = (MouseMotion::MouseButtonN)m;

	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	endPressTimer( n );

	callFuncKey( KEY_N_MOUSE_RELEASE( n ) );
}

////////////////////////////////////////////////////////////////
// �ץ쥹�Υ����ޡ��γ���
// MouseMotion::MouseButtonN n : �ޥ������ܥ����ֹ�
////////////////////////////////////////////////////////////////

void beginPressTimer( MouseMotion::MouseButtonN n )
{
	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	bFlagPressTimerRunning = false;

	if( bFlagPressTimerRunning ){
#ifdef D_GTK
		gtk_timeout_remove( nPressTimer );
#endif // D_GTK
#ifdef D_MFC
	::timeEndPeriod( theApp.m_pMainFrm->nPressTimer );
#endif // D_MFC
	}

	bFlagPressTimer[n] = true;
	bFlagPressTimerRunning = true;

#ifdef D_GTK
	nPressTimer = gtk_timeout_add(
			1000 * PRESS_TIMER_FRAME_RATE / 60,
			callBackPressTimerGtk, NULL );
#endif // D_GTK
#ifdef D_MFC
	::timeBeginPeriod( theApp.m_pMainFrm->nPressTimer );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �ץ쥹�Υ����ޡ��ν�λ
// MouseMotion::MouseButtonN n : �ޥ������ܥ����ֹ�
////////////////////////////////////////////////////////////////

void endPressTimer( MouseMotion::MouseButtonN n )
{
	if( n < MouseMotion::nMouseButton0 )
		return;
	if( n >= MouseMotion::nMouseButtonMaxN )
		return;

	bFlagPressTimer[n] = false;

	bool flagPress = false;
	for( long i = (long)MouseMotion::nMouseButtonMinN;
			i < (long)MouseMotion::nMouseButtonMaxN; i++ ){
		if( bFlagPressTimer[i] ){
			flagPress = true;
			break;
		}
	}

	if( !flagPress && bFlagPressTimerRunning ){
		bFlagPressTimerRunning = false;
#ifdef D_GTK
		gtk_timeout_remove( nPressTimer );
#endif // D_GTK
#ifdef D_MFC
		::timeEndPeriod( theApp.m_pMainFrm->nPressTimer );
#endif // D_MFC
	}
}

////////////////////////////////////////////////////////////////
// ������֥ץ쥹���줿���ν��� (GTK+)
// gpointer data : �����롦�Хå�����Ͽ���줿���Υǡ���
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK
gint callBackPressTimerGtk( gpointer data )
{
	callBackPressTimer();

	return 0;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ������֥ץ쥹���줿���ν���
////////////////////////////////////////////////////////////////

void callBackPressTimer( void )
{
#ifdef D_GTK
	gtk_timeout_remove( nPressTimer );
#endif // D_GTK
#ifdef D_MFC
	::timeEndPeriod( theApp.m_pMainFrm->nPressTimer );
#endif // D_MFC

	if( !bFlagPressTimerRunning )
		return;

	bFlagPressTimerRunning = false;

	for( long i = (long)MouseMotion::nMouseButtonMinN;
			i < (long)MouseMotion::nMouseButtonMaxN; i++ ){
		if( bFlagPressTimer[i] )
			callFuncKey( KEY_N_MOUSE_PRESS( i ) );

		bFlagPressTimer[i] = false;
	}
}

////////////////////////////////////////////////////////////////
// ��������Υ����롦�Хå�
// long m : ������������
// long nBgnX : �ɥ�å����� X ��ɸ
// long nBgnY : �ɥ�å����� Y ��ɸ
// long nCurX : ���ߤ� X ��ɸ
// long nCurY : ���ߤ� Y ��ɸ
////////////////////////////////////////////////////////////////

void funcMotionScroll(
	long m,
	long nBgnX, long nBgnY,
	long nCurX, long nCurY
)
{
	const long scrollMax = 1;

	MouseMotion::ScrollKind dir = (MouseMotion::ScrollKind)m;

	if( dir < MouseMotion::nScrollKindMinN )
		return;
	if( dir >= MouseMotion::nScrollKindMaxN )
		return;

	if( gKey.chkBuf() )
		return;
	if( chk_key_buf() )
		return;
	if( chk_executing_menu() )
		return;

#if	FLAG_KEY_SCROLL
	for( long i = 0; i < scrollMax; i++) {
		switch( dir ){
		case MouseMotion::nScrollLeft:
			gKey.setString( ":/misc/cursor/cursor/scroll/"
					"west\n" );
			break;
		case MouseMotion::nScrollRight:
			gKey.setString( ":/misc/cursor/cursor/scroll/"
					"east\n" );
			break;
		case MouseMotion::nScrollUp:
			gKey.setString( ":/misc/cursor/cursor/scroll/"
					"north\n" );
			break;
		case MouseMotion::nScrollDown:
			gKey.setString( ":/misc/cursor/cursor/scroll/"
					"south\n" );
			break;
		default:
			break;
		}
	}

	gKey.setChar( CMD_KEY_IDLE );
#else
		switch( dir ){
		case MouseMotion::nScrollLeft:
			gPcgDun.scrollTileRel( -1 * scrollMax, +-0 );
			break;
		case MouseMotion::nScrollRight:
			gPcgDun.scrollTileRel( +1 * scrollMax, +-0 );
			break;
		case MouseMotion::nScrollUp:
			gPcgDun.scrollTileRel( +-0, -1 * scrollMax );
			break;
		case MouseMotion::nScrollDown:
			gPcgDun.scrollTileRel( +-0, +1 * scrollMax );
			break;
		default:
			break;
		}
#endif
}

////////////////////////////////////////////////////////////////
// �ޥ������⡼������ե��󥯥���󡦥������Ѵ�
// long fn : �ե��󥯥���󡦥����ֹ�
// bool flagCheckClear : ��������ԡ��Ȥ�Хåե��ˤ���ʤ�����
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool callFuncKey( long fn, bool flagCheckClear )
{
	if( fn < KEY_N_0 )
		return false;
	if( fn > KEY_N_MAX )
		return false;

	do {
		if( !flagCheckClear )
			break;
		if( !g_flg_clr_key_buf )
			break;
		if( !chk_key_buf() )
			break;
		if( !chk_flg_run_exec_all_phase() )
			break;

		return true;
	} while( 0 );

	char str[63 + 1];
	sn_printf( str, 63, "&a0x%lx;", (long)fn );
	gKey.setString( str );

	return true;
}
