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
* $Id: GameJoystick.h,v 1.9 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GAME_JOYSTICK_H
#define GAME_JOYSTICK_H

////////////////////////////////////////////////////////////////
// ジョイスティックの管理
////////////////////////////////////////////////////////////////

#ifdef	HAVE_SDL_SDL_H
# include <SDL/SDL.h>
#endif

#include "joy-kind.h"

////////////////////////////////////////////////////////////////

class GameJoystick {
private:
#ifdef	HAVE_SDL_SDL_H
	SDL_Joystick *joystick;
#endif

	long nCurrentJoystick;
	joy_kind_t joyKind;

	long nMoveX, nMoveY;
	long nMoveCountX, nMoveCountY;
	long nScrollX, nScrollY;
	long nScrollCountX, nScrollCountY;

	bool flagContExecA, flagContExecB;

public:

public:
	GameJoystick();
	~GameJoystick();
	void init();

	void openJoy();
	void closeJoy();

	long getJoy();
	void selJoy( long n );

	const char *getName( long n );

	joy_kind_t getKind();
	void setKind( joy_kind_t kind );

	void checkEvent();

private:
	void joyAxis( long axis, long n );
	void joyMoveX( long n );
	void joyMoveY( long n );
	void joyScrollX( long n );
	void joyScrollY( long n );

	void joyHat( long n );

	void joyButtonOn( long n );
	void joyButtonOff( long n );

	void joyRepeat();
	void joyMoveRepeat();
	void joyScrollRepeat();
	void joyButtonRepeat();
};

#endif // GAME_JOYSTICK_H
