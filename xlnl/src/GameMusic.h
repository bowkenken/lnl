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
* $Id: GameMusic.h,v 1.18 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GAME_MUSIC_H
#define GAME_MUSIC_H	1

////////////////////////////////////////////////////////////////
// BGM の管理
////////////////////////////////////////////////////////////////

#ifdef	HAVE_SDL_SDL_H
# include <SDL/SDL.h>
#endif
#ifdef	HAVE_SDL_SDL_MIXER_H
# include <SDL/SDL_mixer.h>
#endif

#include "town.h"
#include "music-kind.h"

////////////////////////////////////////////////////////////////

// BGM データ・ディレクトリ
#define STR_DEFAULT_MUSIC_DIR_NAME	"xlnl-" VERSION "/"
// BGM のファイル名の拡張子
#define	STR_MUSIC_FILE_EXT	"ogg mp3"

#define	LS_MUSIC_DUN_MAX_N	10
#define	LS_MUSIC_BATTLE_MAX_N	LS_MUSIC_DUN_MAX_N

// BGM のファイル名リスト
struct LsMusic {
	// 次の BGM
	LsMusic *next;

	// BGM のファイル名
	WSCstring name;
};

////////////////////////////////////////////////////////////////

class GameMusic {
public:
private:
#ifdef	HAVE_SDL_SDL_MIXER_H
	Mix_Music *music;
#endif

	int audioRate;
	unsigned short audioFormat;
	int audioChannels;
	int audioBuffers;

	music_kind_t currentKind;
	music_kind_t prevKind;
	long currentIdx;
	long prevIdx;
	WSCstring currentName;

	LsMusic lsTitle;
	LsMusic lsGameOver;
	LsMusic lsEnding;
	LsMusic lsTheEnd;
	LsMusic lsTown;
	LsMusic lsShop[SHOP_N_MAX_N];
	LsMusic lsDun[LS_MUSIC_DUN_MAX_N];
	LsMusic lsLastBoss;
	LsMusic lsBattle[LS_MUSIC_BATTLE_MAX_N];
	LsMusic lsBattleBoss;
	LsMusic lsBattleLastBoss;
	LsMusic lsEffect[ME_KIND_MAX_N];

public:
	GameMusic();
	~GameMusic();
	void init();
	void initLsMusic( LsMusic *ls, WSCstring dir );
	void close();

	void setVolume( rate_t rate );

	void playScene();
	void playLastScene();
	void play( music_kind_t kind, long idx = -1 );
	void replayPrev();
	void replay();
	WSCstring playTitle( long idx );
	WSCstring playGameOver( long idx );
	WSCstring playEnding( long idx );
	WSCstring playTheEnd( long idx );
	WSCstring playTown( long idx );
	WSCstring playShop( long idx );
	WSCstring playDun( long idx );
	WSCstring playLastBoss( long idx );
	WSCstring playBattle( long idx );
	WSCstring playBattleBoss( long idx );
	WSCstring playBattleLastBoss( long idx );
	WSCstring playEffect( long idx );

private:
	void setCurrent( music_kind_t kind, long idx );
	WSCstring playRandm(
		LsMusic *p, long nRepeat = -1,
		void (*func)() = NULL );
};

#endif /* GAME_MUSIC_H */
