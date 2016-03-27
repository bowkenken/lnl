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
* $Id: GameJoystick.cpp,v 1.17 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ���祤���ƥ��å��δ���
////////////////////////////////////////////////////////////////

#define GAME_JOYSTICK_CPP	1
#include "inc.h"

#ifdef D_MFC
# pragma comment( lib, "SDL.lib" )
# pragma comment( lib, "SDLmain.lib" )
#endif

////////////////////////////////////////////////////////////////

// ���������ư��ľ�ܹԤ�����
#define JOYSTICK_DIRECT_MOVE	1

// �ǥե���ȤΥ��祤���ƥ��å��ֹ�
static const long DEFAULT_JOYSTICK_N = 0;

// ���ʥ������ƥ��å��Τ�������
static const long AXIS_BORDER = 32767 / 10;
static const long MOVE_COUNT_MAX_X = 32767;
static const long MOVE_COUNT_MAX_Y = 32767;
static const long SCROLL_COUNT_MAX_X = 32767;
static const long SCROLL_COUNT_MAX_Y = 32767;

// �ܥ���򲡤��Ƥ����ԡ��Ȥ�������ޤǤΥե졼���
static const long BUTTON_REPEAT_FRAME = (long)(1.0 * TIMER_FRAME);

////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

GameJoystick::GameJoystick()
{
#ifdef	HAVE_SDL_SDL_H
	joystick = NULL;
#endif

	nCurrentJoystick = DEFAULT_JOYSTICK_N;
	joyKind = JOY_KIND_PS;

	nMoveCountX = 0;
	nMoveCountY = 0;
	nScrollCountX = 0;
	nScrollCountY = 0;

	flagContExecA = false;
	flagContExecB = false;
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

GameJoystick::~GameJoystick()
{
	closeJoy();
}

////////////////////////////////////////////////////////////////
// �����
////////////////////////////////////////////////////////////////

void GameJoystick::init()
{
	openJoy();
}

////////////////////////////////////////////////////////////////
// ���祤���ƥ��å��򥪡��ץ�
////////////////////////////////////////////////////////////////

void GameJoystick::openJoy()
{
#ifdef	HAVE_SDL_SDL_H
	if( joystick != NULL )
		closeJoy();
	if( joystick != NULL )
		return;

	if( SDL_NumJoysticks() >= 1 ){
		if( nCurrentJoystick > SDL_NumJoysticks() - 1 )
			nCurrentJoystick = SDL_NumJoysticks() - 1;

		SDL_JoystickEventState( SDL_ENABLE );
		joystick = SDL_JoystickOpen( nCurrentJoystick );
	}
#endif
}

////////////////////////////////////////////////////////////////
// ���祤���ƥ��å��򥯥���
////////////////////////////////////////////////////////////////

void GameJoystick::closeJoy()
{
#ifdef	HAVE_SDL_SDL_H
	if( joystick == NULL )
		return;

	SDL_JoystickClose( joystick );
	joystick = NULL;
#endif
}

////////////////////////////////////////////////////////////////
// ������Υ��祤���ƥ��å��ֹ���֤�
// return : ���祤���ƥ��å��ֹ�
////////////////////////////////////////////////////////////////

long GameJoystick::getJoy()
{
	return nCurrentJoystick;
}

////////////////////////////////////////////////////////////////
// ���祤���ƥ��å�������
// long n : ���祤���ƥ��å��ֹ�
////////////////////////////////////////////////////////////////

void GameJoystick::selJoy( long n )
{
	if( n < 0 )
		return;

#ifdef	HAVE_SDL_SDL_H
	if( n >= SDL_NumJoysticks() )
		return;
#endif

	closeJoy();
	nCurrentJoystick = n;
	openJoy();
}

////////////////////////////////////////////////////////////////
// ���祤���ƥ��å���̾�����֤�
// long n : ���祤���ƥ��å��ֹ�
// return : ���祤���ƥ��å���̾��
////////////////////////////////////////////////////////////////

const char *GameJoystick::getName( long n )
{
	if( n < 0 )
		return NULL;

#ifdef	HAVE_SDL_SDL_H
	if( n >= SDL_NumJoysticks() )
		return NULL;

	return SDL_JoystickName( n );
#endif

	return NULL;
}

////////////////////////////////////////////////////////////////
// ���祤���ƥ��å��μ�����֤�
// return : ���祤���ƥ��å��μ���
////////////////////////////////////////////////////////////////

joy_kind_t GameJoystick::getKind()
{
	return joyKind;
}

////////////////////////////////////////////////////////////////
// ���祤���ƥ��å��μ��������
// joy_kind_t kind : ���祤���ƥ��å��μ���
////////////////////////////////////////////////////////////////

void GameJoystick::setKind( joy_kind_t kind )
{
	joyKind = kind;
	closeJoy();
	openJoy();
}

////////////////////////////////////////////////////////////////
// ���٥�ȤΥ����å�
////////////////////////////////////////////////////////////////

void GameJoystick::checkEvent()
{
#ifdef	HAVE_SDL_SDL_H
	SDL_Event event;
	while( SDL_PollEvent( &event ) ){
		if( !g_flg_init )
			continue;
		if( chk_scene_group( SCENE_GROUP_N_INIT ) )
			continue;
		if( chk_scene_group( SCENE_GROUP_N_TITLE ) )
			continue;

		switch( event.type ){
		case SDL_JOYAXISMOTION:
			joyAxis( event.jaxis.axis, event.jaxis.value );
			break;
		case SDL_JOYHATMOTION:
			joyHat( event.jhat.hat );
			break;
		case SDL_JOYBUTTONDOWN:
			joyButtonOn( event.jbutton.button );
			break;
		case SDL_JOYBUTTONUP:
			joyButtonOff( event.jbutton.button );
			break;
		}
	}

	joyRepeat();
#endif
}

////////////////////////////////////////////////////////////////
// ���ƥ��å�
// long axis : ��
// long n : ����
////////////////////////////////////////////////////////////////

void GameJoystick::joyAxis( long axis, long n )
{
	if( (-AXIS_BORDER < n) && (n < +AXIS_BORDER) )
		n = 0;

	switch( axis ){
	case 0:
		joyMoveX( n );
		break;
	case 1:
		joyMoveY( n );
		break;
	case 2:
		if( joyKind == JOY_KIND_RAP3 )
			joyScrollX( n );
		else
			joyScrollY( n );
		break;
	case 3:
		if( joyKind == JOY_KIND_RAP3 )
			joyScrollY( n );
		else
			joyScrollX( n );
		break;
	case 4:
		joyMoveX( n );
		break;
	case 5:
		joyMoveY( n );
		break;
	}
}

////////////////////////////////////////////////////////////////
// ��ư���ƥ��å� X ��
// long n : X �����η���
////////////////////////////////////////////////////////////////

void GameJoystick::joyMoveX( long n )
{
	nMoveX = n;
}

////////////////////////////////////////////////////////////////
// ��ư���ƥ��å� Y ��
// long n : Y �����η���
////////////////////////////////////////////////////////////////

void GameJoystick::joyMoveY( long n )
{
	nMoveY = n;
}

////////////////////////////////////////////////////////////////
// �������롦���ƥ��å� X ��
// long n : X �����η���
////////////////////////////////////////////////////////////////

void GameJoystick::joyScrollX( long n )
{
	nScrollX = n;
}

////////////////////////////////////////////////////////////////
// �������롦���ƥ��å� Y ��
// long n : Y �����η���
////////////////////////////////////////////////////////////////

void GameJoystick::joyScrollY( long n )
{
	nScrollY = n;
}

////////////////////////////////////////////////////////////////
// �ϥåȡ������å�
// long n : �ϥåȡ������å�����
////////////////////////////////////////////////////////////////

void GameJoystick::joyHat( long n )
{
#ifdef	HAVE_SDL_SDL_H
	if( n & SDL_HAT_CENTERED ){
		nMoveX = 0;
		nMoveY = 0;
	}
	if( n & SDL_HAT_LEFT )
		nMoveX = -MOVE_COUNT_MAX_X;
	if( n & SDL_HAT_RIGHT )
		nMoveX = +MOVE_COUNT_MAX_X;
	if( n & SDL_HAT_UP )
		nMoveY = -MOVE_COUNT_MAX_Y;
	if( n & SDL_HAT_DOWN )
		nMoveY = +MOVE_COUNT_MAX_Y;
#endif
}

////////////////////////////////////////////////////////////////
// �ܥ��� ON
// long n : �ܥ����ֹ�
////////////////////////////////////////////////////////////////

void GameJoystick::joyButtonOn( long n )
{
	long btn = KEY_N_JOYSTICK_HEAD_N + n;
	char *macro = get_macro_str( btn );

	if( strcmp( macro, "0" ) == 0 ){
		flagContExecB = true;
		if( flagContExecA && flagContExecB ){
			gKey.setString( ".," );
			return;
		}
	}
	if( strcmp( macro, "." ) == 0 ){
		flagContExecA = true;
		if( flagContExecA && flagContExecB ){
			gKey.setString( ".," );
			return;
		}
	}

	gKey.setString( macro );
}

////////////////////////////////////////////////////////////////
// �ܥ��� OFF
// long n : �ܥ����ֹ�
////////////////////////////////////////////////////////////////

void GameJoystick::joyButtonOff( long n )
{
	long btn = KEY_N_JOYSTICK_HEAD_N + n;
	char *macro = get_macro_str( btn );

	if( strcmp( macro, "0" ) == 0 ){
		flagContExecB = false;
		gKey.setChar( '|' );
	}
	if( strcmp( macro, "." ) == 0 ){
		flagContExecA = false;
		gKey.setChar( '|' );
	}
}

////////////////////////////////////////////////////////////////
// ���ƥ��å���ܥ��������³�������Υ�ԡ���
////////////////////////////////////////////////////////////////

void GameJoystick::joyRepeat()
{
	joyMoveRepeat();
	joyScrollRepeat();
	joyButtonRepeat();
}

////////////////////////////////////////////////////////////////
// ��ư���ƥ��å����ݤ�³�������Υ�ԡ���
////////////////////////////////////////////////////////////////

void GameJoystick::joyMoveRepeat()
{
	nMoveCountX += nMoveX;
	nMoveCountY += nMoveY;

	long x = nMoveCountX / MOVE_COUNT_MAX_X;
	long y = nMoveCountY / MOVE_COUNT_MAX_Y;

	nMoveCountX %= MOVE_COUNT_MAX_X;
	nMoveCountY %= MOVE_COUNT_MAX_Y;

	bool flagMenu = !!get_flg_draw_menu();
	if( !JOYSTICK_DIRECT_MOVE )
		flagMenu = true;

	if( flagMenu ){
		for( long i = 0; i < x; i++ )
			gKey.setChar( '6', false, true );
		for( long i = 0; i < -x; i++ )
			gKey.setChar( '4', false, true );
		for( long i = 0; i < y; i++ )
			gKey.setChar( '2', false, true );
		for( long i = 0; i < -y; i++ )
			gKey.setChar( '8', false, true );
	} else {
		if( (x == 0) && (y == 0) )
			return;

		gKey.moveCrsrRel( x, y );
	}
}

////////////////////////////////////////////////////////////////
// �������롦���ƥ��å����ݤ�³�������Υ�ԡ���
////////////////////////////////////////////////////////////////

void GameJoystick::joyScrollRepeat()
{
	nScrollCountX += nScrollX;
	nScrollCountY += nScrollY;

	long x = nScrollCountX / SCROLL_COUNT_MAX_X;
	long y = nScrollCountY / SCROLL_COUNT_MAX_Y;

	nScrollCountX %= SCROLL_COUNT_MAX_X;
	nScrollCountY %= SCROLL_COUNT_MAX_Y;

	if( (x == 0) && (y == 0) )
		return;

	gKey.scrollRel( x, y );
}

////////////////////////////////////////////////////////////////
// �ܥ���򲡤�³�������Υ�ԡ���
////////////////////////////////////////////////////////////////

void GameJoystick::joyButtonRepeat()
{
	static bool flagContExecMode = false;
	static long nContExecFrame = 0;

	if( flagContExecA && !flagContExecB ){
		if( !flagContExecMode ){
			if( nContExecFrame < BUTTON_REPEAT_FRAME ){
				nContExecFrame++;
			} else {
				gKey.setChar( ',' );
				flagContExecMode = true;
			}
		}
	} else {
		flagContExecMode = false;
		nContExecFrame = 0;
	}
}
