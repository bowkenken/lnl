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
* $Id: GameSound.h,v 1.12 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GAME_SOUND_H
#define GAME_SOUND_H	1

////////////////////////////////////////////////////////////////
// SE �δ���
////////////////////////////////////////////////////////////////

#ifdef	HAVE_SDL_SDL_H
# include <SDL/SDL.h>
#endif
#ifdef	HAVE_SDL_SDL_MIXER_H
# include <SDL/SDL_mixer.h>
#endif

#include "sound-kind.h"

////////////////////////////////////////////////////////////////

// SE �ǡ������ǥ��쥯�ȥ�
#define STR_DEFAULT_SOUND_DIR_NAME	"xlnl-" VERSION "/"
// SE �Υե�����̾�γ�ĥ��
#define	STR_SOUND_FILE_EXT	"ogg mp3 wav"

// SE �Υե�����̾�ꥹ��
struct LsSound {
	// ���� SE
	LsSound *next;

	// SE �Υե�����̾
	WSCstring name;

	// SE �Υǡ���
#ifdef	HAVE_SDL_SDL_MIXER_H
	Mix_Chunk *chunk;
#endif
};

////////////////////////////////////////////////////////////////

class GameSound {
private:
	bool flagEnable;

	int nPhaserChannel;

	LsSound lsTrapSafe;
	LsSound lsTrapDisarm;
	LsSound lsTrapCaught;

	LsSound lsSpellSor;
	LsSound lsSpellEnc;
	LsSound lsSpellNin;
	LsSound lsSpellBar;
	LsSound lsSpellMag;
	LsSound lsSpellSum;
	LsSound lsSpellSha;
	LsSound lsSpellPri;

	LsSound lsBlastMember;
	LsSound lsBlastMonster;
	LsSound lsBlastDestruction;

	LsSound lsMenuCancel;
	LsSound lsMenuSelect;

	LsSound lsFightDieMember;
	LsSound lsFightDieMonsterBossLast;
	LsSound lsFightDieMonsterBoss;
	LsSound lsFightDieMonster;
	LsSound lsFightDefenseMissMember;
	LsSound lsFightDefenseMissMonsterBossLast;
	LsSound lsFightDefenseMissMonster;
	LsSound lsFightDefenseHitMember;
	LsSound lsFightDefenseHitMonster;
	LsSound lsFightDefenseCriticalMember;
	LsSound lsFightDefenseCriticalMonster;
	LsSound lsFightFindMember;
	LsSound lsFightFindMonsterBoss;
	LsSound lsFightFindMonster;
	LsSound lsFightAttackLastBossAttack;
	LsSound lsFightAttackLastBossWeaken;
	LsSound lsFightAttackLastBossSlap;
	LsSound lsFightAttackThrowMember;
	LsSound lsFightAttackThrowMonster;

	LsSound lsRequestFinish;

	LsSound lsShopSale;
	LsSound lsShopBuyDrink;
	LsSound lsShopBuy;

	LsSound lsEventGate;
	LsSound lsEventDrive;
	LsSound lsEventEarthquake;

	LsSound lsLevelDown;
	LsSound lsLevelUp;

	LsSound lsDoorClose;
	LsSound lsDoorOpen;

	LsSound lsStairsDown;
	LsSound lsStairsUp;

	LsSound lsItemUse;
	LsSound lsItemOpen;
	LsSound lsItemSmoke;

	LsSound lsActionAppear;
	LsSound lsActionTeleportRecall;
	LsSound lsActionTeleportParty;
	LsSound lsActionTeleportShort;
	LsSound lsActionTeleportLong;

public:
	GameSound();
	~GameSound();
	void init();
	void close();

	void setVolume( rate_t rate );

	void play( sound_kind_t kind, long nRepeat );
	void stop();

private:
	void initLsSound( LsSound *ls, WSCstring dir );

	void freeAll();
	void freeLsSound( LsSound *ls );

	void playRandm( LsSound *p, long nRepeat );
};

#endif /* GAME_SOUND_H */
