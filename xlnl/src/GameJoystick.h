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
* $Id: GameJoystick.h,v 1.9 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GAME_JOYSTICK_H
#define GAME_JOYSTICK_H

////////////////////////////////////////////////////////////////
// ���祤���ƥ��å��δ���
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
