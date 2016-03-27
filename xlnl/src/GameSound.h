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
* $Id: GameSound.h,v 1.12 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GAME_SOUND_H
#define GAME_SOUND_H	1

////////////////////////////////////////////////////////////////
// SE の管理
////////////////////////////////////////////////////////////////

#ifdef	HAVE_SDL_SDL_H
# include <SDL/SDL.h>
#endif
#ifdef	HAVE_SDL_SDL_MIXER_H
# include <SDL/SDL_mixer.h>
#endif

#include "sound-kind.h"

////////////////////////////////////////////////////////////////

// SE データ・ディレクトリ
#define STR_DEFAULT_SOUND_DIR_NAME	"xlnl-" VERSION "/"
// SE のファイル名の拡張子
#define	STR_SOUND_FILE_EXT	"ogg mp3 wav"

// SE のファイル名リスト
struct LsSound {
	// 次の SE
	LsSound *next;

	// SE のファイル名
	WSCstring name;

	// SE のデータ
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
