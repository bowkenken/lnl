/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* 本プログラムはフリー・ソフトウェアです。
* あなたは、 Free Software Foundation が公表した
*  GNU 一般公有使用許諾の「バージョン２」
* 或はそれ以降の各バージョンの中からいずれかを選択し、
* そのバージョンが定める条項に従って本プログラムを
* 再頒布または変更することができます。
* 
* 本プログラムは有用とは思いますが、頒布にあたっては、
* 市場性及び特定目的適合性についての暗黙の保証を含めて,
* いかなる保証も行ないません。
* 詳細については GNU 一般公有使用許諾書をお読みください。
* 
* あなたは、本プログラムと一緒に GNU 一般公有使用許諾書
* の写しを受け取っているはずです。そうでない場合は、
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* へ手紙を書いてください。
* 
* $Id: GameJoystick.cpp,v 1.17 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ジョイスティックの管理
////////////////////////////////////////////////////////////////

#define GAME_JOYSTICK_CPP	1
#include "inc.h"

#ifdef D_MFC
# pragma comment( lib, "SDL.lib" )
# pragma comment( lib, "SDLmain.lib" )
#endif

////////////////////////////////////////////////////////////////

// カーソル移動を直接行うか？
#define JOYSTICK_DIRECT_MOVE	1

// デフォルトのジョイスティック番号
static const long DEFAULT_JOYSTICK_N = 0;

// アナログ・スティックのしきい値
static const long AXIS_BORDER = 32767 / 10;
static const long MOVE_COUNT_MAX_X = 32767;
static const long MOVE_COUNT_MAX_Y = 32767;
static const long SCROLL_COUNT_MAX_X = 32767;
static const long SCROLL_COUNT_MAX_Y = 32767;

// ボタンを押してからリピートがかかるまでのフレーム数
static const long BUTTON_REPEAT_FRAME = (long)(1.0 * TIMER_FRAME);

////////////////////////////////////////////////////////////////
// コンストラクタ
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
// デストラクタ
////////////////////////////////////////////////////////////////

GameJoystick::~GameJoystick()
{
	closeJoy();
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void GameJoystick::init()
{
	openJoy();
}

////////////////////////////////////////////////////////////////
// ジョイスティックをオープン
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
// ジョイスティックをクローズ
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
// 選択中のジョイスティック番号を返す
// return : ジョイスティック番号
////////////////////////////////////////////////////////////////

long GameJoystick::getJoy()
{
	return nCurrentJoystick;
}

////////////////////////////////////////////////////////////////
// ジョイスティックを選択
// long n : ジョイスティック番号
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
// ジョイスティックの名前を返す
// long n : ジョイスティック番号
// return : ジョイスティックの名前
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
// ジョイスティックの種類を返す
// return : ジョイスティックの種類
////////////////////////////////////////////////////////////////

joy_kind_t GameJoystick::getKind()
{
	return joyKind;
}

////////////////////////////////////////////////////////////////
// ジョイスティックの種類を設定
// joy_kind_t kind : ジョイスティックの種類
////////////////////////////////////////////////////////////////

void GameJoystick::setKind( joy_kind_t kind )
{
	joyKind = kind;
	closeJoy();
	openJoy();
}

////////////////////////////////////////////////////////////////
// イベントのチェック
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
// スティック
// long axis : 軸
// long n : 傾き
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
// 移動スティック X 軸
// long n : X 方向の傾き
////////////////////////////////////////////////////////////////

void GameJoystick::joyMoveX( long n )
{
	nMoveX = n;
}

////////////////////////////////////////////////////////////////
// 移動スティック Y 軸
// long n : Y 方向の傾き
////////////////////////////////////////////////////////////////

void GameJoystick::joyMoveY( long n )
{
	nMoveY = n;
}

////////////////////////////////////////////////////////////////
// スクロール・スティック X 軸
// long n : X 方向の傾き
////////////////////////////////////////////////////////////////

void GameJoystick::joyScrollX( long n )
{
	nScrollX = n;
}

////////////////////////////////////////////////////////////////
// スクロール・スティック Y 軸
// long n : Y 方向の傾き
////////////////////////////////////////////////////////////////

void GameJoystick::joyScrollY( long n )
{
	nScrollY = n;
}

////////////////////////////////////////////////////////////////
// ハット・スイッチ
// long n : ハット・スイッチ状態
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
// ボタン ON
// long n : ボタン番号
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
// ボタン OFF
// long n : ボタン番号
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
// スティックやボタンを入れ続けた時のリピート
////////////////////////////////////////////////////////////////

void GameJoystick::joyRepeat()
{
	joyMoveRepeat();
	joyScrollRepeat();
	joyButtonRepeat();
}

////////////////////////////////////////////////////////////////
// 移動スティックを倒し続けた時のリピート
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
// スクロール・スティックを倒し続けた時のリピート
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
// ボタンを押し続けた時のリピート
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
