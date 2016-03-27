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
* $Id: GameSound.cpp,v 1.13 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// SE の管理
////////////////////////////////////////////////////////////////

#define GAME_SOUND_CPP	1
#include "inc.h"

#ifdef D_MFC
# pragma comment( lib, "SDL.lib" )
# pragma comment( lib, "SDLmain.lib" )
# pragma comment( lib, "SDL_mixer.lib" )
#endif

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

GameSound::GameSound()
{
	flagEnable = false;

#ifdef	HAVE_SDL_SDL_MIXER_H
	nPhaserChannel = -1;

	lsTrapSafe.next = NULL;
	lsTrapDisarm.next = NULL;
	lsTrapCaught.next = NULL;

	lsSpellSor.next = NULL;
	lsSpellEnc.next = NULL;
	lsSpellNin.next = NULL;
	lsSpellBar.next = NULL;
	lsSpellMag.next = NULL;
	lsSpellSum.next = NULL;
	lsSpellSha.next = NULL;
	lsSpellPri.next = NULL;

	lsBlastMember.next = NULL;
	lsBlastMonster.next = NULL;
	lsBlastDestruction.next = NULL;

	lsMenuCancel.next = NULL;
	lsMenuSelect.next = NULL;

	lsFightDieMember.next = NULL;
	lsFightDieMonsterBossLast.next = NULL;
	lsFightDieMonsterBoss.next = NULL;
	lsFightDieMonster.next = NULL;
	lsFightDefenseMissMember.next = NULL;
	lsFightDefenseMissMonsterBossLast.next = NULL;
	lsFightDefenseMissMonster.next = NULL;
	lsFightDefenseHitMember.next = NULL;
	lsFightDefenseHitMonster.next = NULL;
	lsFightDefenseCriticalMember.next = NULL;
	lsFightDefenseCriticalMonster.next = NULL;
	lsFightFindMember.next = NULL;
	lsFightFindMonsterBoss.next = NULL;
	lsFightFindMonster.next = NULL;
	lsFightAttackLastBossAttack.next = NULL;
	lsFightAttackLastBossWeaken.next = NULL;
	lsFightAttackLastBossSlap.next = NULL;
	lsFightAttackThrowMember.next = NULL;
	lsFightAttackThrowMonster.next = NULL;

	lsRequestFinish.next = NULL;

	lsShopSale.next = NULL;
	lsShopBuyDrink.next = NULL;
	lsShopBuy.next = NULL;

	lsEventGate.next = NULL;
	lsEventDrive.next = NULL;
	lsEventEarthquake.next = NULL;

	lsLevelDown.next = NULL;
	lsLevelUp.next = NULL;

	lsDoorClose.next = NULL;
	lsDoorOpen.next = NULL;

	lsStairsDown.next = NULL;
	lsStairsUp.next = NULL;

	lsItemUse.next = NULL;
	lsItemOpen.next = NULL;
	lsItemSmoke.next = NULL;

	lsActionAppear.next = NULL;
	lsActionTeleportRecall.next = NULL;
	lsActionTeleportParty.next = NULL;
	lsActionTeleportShort.next = NULL;
	lsActionTeleportLong.next = NULL;
#endif
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

GameSound::~GameSound()
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	this->close();
#endif
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void GameSound::init()
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	initLsSound( &lsTrapSafe,
			"trap/safe/" );
	initLsSound( &lsTrapDisarm,
			"trap/disarm/" );
	initLsSound( &lsTrapCaught,
			"trap/caught/" );

	initLsSound( &lsSpellSor,
			"spell/sor/" );
	initLsSound( &lsSpellEnc,
			"spell/enc/" );
	initLsSound( &lsSpellNin,
			"spell/nin/" );
	initLsSound( &lsSpellBar,
			"spell/bar/" );
	initLsSound( &lsSpellMag,
			"spell/mag/" );
	initLsSound( &lsSpellSum,
			"spell/sum/" );
	initLsSound( &lsSpellSha,
			"spell/sha/" );
	initLsSound( &lsSpellPri,
			"spell/pri/" );

	initLsSound( &lsBlastMember,
			"blast/member/" );
	initLsSound( &lsBlastMonster,
			"blast/monster/" );
	initLsSound( &lsBlastDestruction,
			"blast/destruction/" );

	initLsSound( &lsMenuCancel,
			"menu/cancel/" );
	initLsSound( &lsMenuSelect,
			"menu/select/" );

	initLsSound( &lsFightDieMember,
			"fight/die/member/" );
	initLsSound( &lsFightDieMonsterBossLast,
			"fight/die/monster/boss/last/" );
	initLsSound( &lsFightDieMonsterBoss,
			"fight/die/monster/boss/" );
	initLsSound( &lsFightDieMonster,
			"fight/die/monster/" );
	initLsSound( &lsFightDefenseMissMember,
			"fight/defense/miss/member/" );
	initLsSound( &lsFightDefenseMissMonsterBossLast,
			"fight/defense/miss/monster/boss/last/" );
	initLsSound( &lsFightDefenseMissMonster,
			"fight/defense/miss/monster/" );
	initLsSound( &lsFightDefenseHitMember,
			"fight/defense/hit/member/" );
	initLsSound( &lsFightDefenseHitMonster,
			"fight/defense/hit/monster/" );
	initLsSound( &lsFightDefenseCriticalMember,
			"fight/defense/critical/member/" );
	initLsSound( &lsFightDefenseCriticalMonster,
			"fight/defense/critical/monster/" );
	initLsSound( &lsFightFindMember,
			"fight/find/member/" );
	initLsSound( &lsFightFindMonsterBoss,
			"fight/find/monster/boss/" );
	initLsSound( &lsFightFindMonster,
			"fight/find/monster/" );
	initLsSound( &lsFightAttackLastBossAttack,
			"fight/attack/last_boss/attack/" );
	initLsSound( &lsFightAttackLastBossWeaken,
			"fight/attack/last_boss/weaken/" );
	initLsSound( &lsFightAttackLastBossSlap,
			"fight/attack/last_boss/slap/" );
	initLsSound( &lsFightAttackThrowMember,
			"fight/attack/throw/member/" );
	initLsSound( &lsFightAttackThrowMonster,
			"fight/attack/throw/monster/" );

	initLsSound( &lsRequestFinish,
			"request/finish/" );

	initLsSound( &lsShopSale,
			"shop/sale/" );
	initLsSound( &lsShopBuyDrink,
			"shop/buy/drink/" );
	initLsSound( &lsShopBuy,
			"shop/buy/" );

	initLsSound( &lsEventGate,
			"event/gate/" );
	initLsSound( &lsEventDrive,
			"event/drive/" );
	initLsSound( &lsEventEarthquake,
			"event/earthquake/" );

	initLsSound( &lsLevelDown,
			"level/down/" );
	initLsSound( &lsLevelUp,
			"level/up/" );

	initLsSound( &lsDoorClose,
			"door/close/" );
	initLsSound( &lsDoorOpen,
			"door/open/" );

	initLsSound( &lsStairsDown,
			"stairs/down/" );
	initLsSound( &lsStairsUp,
			"stairs/up/" );

	initLsSound( &lsItemUse,
			"item/use/" );
	initLsSound( &lsItemOpen,
			"item/open/" );
	initLsSound( &lsItemSmoke,
			"item/smoke/" );

	initLsSound( &lsActionAppear,
			"action/appear/" );
	initLsSound( &lsActionTeleportRecall,
			"action/teleport/recall/" );
	initLsSound( &lsActionTeleportParty,
			"action/teleport/party/" );
	initLsSound( &lsActionTeleportShort,
			"action/teleport/short/" );
	initLsSound( &lsActionTeleportLong,
			"action/teleport/long/" );
#endif

	// 音量

	setVolume( get_sound_volume_rate() );

	flagEnable = true;
}

////////////////////////////////////////////////////////////////
// SE リストの初期化
// LsSound *ls : SE リスト
// WSCstring dir : SE ディレクトリ
////////////////////////////////////////////////////////////////

void GameSound::initLsSound( LsSound *ls, WSCstring dir )
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	// SEの検索を設定

	FileList::setStrDirSelSound( STR_DEFAULT_SOUND_DIR_NAME );
	FileList fls;

	//

	ls->next = NULL;
	LsSound *p = ls;
	fls.reset( dir, STR_SOUND_FILE_EXT );
	for( long n = 0; n < LOOP_MAX_1000; n++ ){
		WSCstring path = fls.next();
		if( path.getChars() <= 0 )
			break;

		p->next = new LsSound();
		if( p->next == NULL )
			break;
		p = p->next;

		p->next = NULL;
		p->name = path;

		p->chunk = Mix_LoadWAV( p->name );
	}
#endif
}

////////////////////////////////////////////////////////////////
// SE 処理を終了する
////////////////////////////////////////////////////////////////

void GameSound::close()
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	if( flagEnable ){
		Mix_HaltChannel( -1 );

# ifndef	D_MFC
		freeAll();
# endif
	}
#endif

	flagEnable = false;
}

////////////////////////////////////////////////////////////////
// 全ての SE を解放
////////////////////////////////////////////////////////////////

void GameSound::freeAll()
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	freeLsSound( &lsTrapSafe );
	freeLsSound( &lsTrapDisarm );
	freeLsSound( &lsTrapCaught );

	freeLsSound( &lsSpellSor );
	freeLsSound( &lsSpellEnc );
	freeLsSound( &lsSpellNin );
	freeLsSound( &lsSpellBar );
	freeLsSound( &lsSpellMag );
	freeLsSound( &lsSpellSum );
	freeLsSound( &lsSpellSha );
	freeLsSound( &lsSpellPri );

	freeLsSound( &lsBlastMember );
	freeLsSound( &lsBlastMonster );
	freeLsSound( &lsBlastDestruction );

	freeLsSound( &lsMenuCancel );
	freeLsSound( &lsMenuSelect );

	freeLsSound( &lsFightDieMember );
	freeLsSound( &lsFightDieMonsterBossLast );
	freeLsSound( &lsFightDieMonsterBoss );
	freeLsSound( &lsFightDieMonster );
	freeLsSound( &lsFightDefenseMissMember );
	freeLsSound( &lsFightDefenseMissMonsterBossLast );
	freeLsSound( &lsFightDefenseMissMonster );
	freeLsSound( &lsFightDefenseHitMember );
	freeLsSound( &lsFightDefenseHitMonster );
	freeLsSound( &lsFightDefenseCriticalMember );
	freeLsSound( &lsFightDefenseCriticalMonster );
	freeLsSound( &lsFightFindMember );
	freeLsSound( &lsFightFindMonsterBoss );
	freeLsSound( &lsFightFindMonster );
	freeLsSound( &lsFightAttackLastBossAttack );
	freeLsSound( &lsFightAttackLastBossWeaken );
	freeLsSound( &lsFightAttackLastBossSlap );
	freeLsSound( &lsFightAttackThrowMember );
	freeLsSound( &lsFightAttackThrowMonster );

	freeLsSound( &lsRequestFinish );

	freeLsSound( &lsShopSale );
	freeLsSound( &lsShopBuyDrink );
	freeLsSound( &lsShopBuy );

	freeLsSound( &lsEventGate );
	freeLsSound( &lsEventDrive );
	freeLsSound( &lsEventEarthquake );

	freeLsSound( &lsLevelDown );
	freeLsSound( &lsLevelUp );

	freeLsSound( &lsDoorClose );
	freeLsSound( &lsDoorOpen );

	freeLsSound( &lsStairsDown );
	freeLsSound( &lsStairsUp );

	freeLsSound( &lsItemUse );
	freeLsSound( &lsItemOpen );
	freeLsSound( &lsItemSmoke );

	freeLsSound( &lsActionAppear );
	freeLsSound( &lsActionTeleportRecall );
	freeLsSound( &lsActionTeleportParty );
	freeLsSound( &lsActionTeleportShort );
	freeLsSound( &lsActionTeleportLong );
#endif
}

////////////////////////////////////////////////////////////////
// 指定の SE を解放
// LsSound *ls : SE リスト
////////////////////////////////////////////////////////////////

void GameSound::freeLsSound( LsSound *ls )
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	if( ls == NULL )
		return;

	LsSound *p = ls->next;
	for( long n = 0; n < LOOP_MAX_1000; n++ ){
		if( p == NULL )
			break;
		LsSound *next_p = p->next;

		if( p->chunk != NULL )
			Mix_FreeChunk( p->chunk );
		delete p;

		p = next_p;
	}
#endif
}

////////////////////////////////////////////////////////////////
// SE の音量を設定
////////////////////////////////////////////////////////////////

void GameSound::setVolume( rate_t rate )
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	Mix_Volume( -1, MIX_MAX_VOLUME * rate / _100_PERCENT );
#endif
}

////////////////////////////////////////////////////////////////
// SE の再生
// sound_kind_t kind : SE の種類
// long nRepeat : 再生回数
////////////////////////////////////////////////////////////////

void GameSound::play( sound_kind_t kind, long nRepeat )
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	switch( kind ){
	case SOUND_KIND_NULL:
		break;
	case SOUND_KIND_TRAP_SAFE:
		playRandm( lsTrapSafe.next, nRepeat );
		break;
	case SOUND_KIND_TRAP_DISARM:
		playRandm( lsTrapDisarm.next, nRepeat );
		break;
	case SOUND_KIND_TRAP_CAUGHT:
		playRandm( lsTrapCaught.next, nRepeat );
		break;

	case SOUND_KIND_SPELL_SOR:
		playRandm( lsSpellSor.next, nRepeat );
		break;
	case SOUND_KIND_SPELL_ENC:
		playRandm( lsSpellEnc.next, nRepeat );
		break;
	case SOUND_KIND_SPELL_NIN:
		playRandm( lsSpellNin.next, nRepeat );
		break;
	case SOUND_KIND_SPELL_BAR:
		playRandm( lsSpellBar.next, nRepeat );
		break;
	case SOUND_KIND_SPELL_MAG:
		playRandm( lsSpellMag.next, nRepeat );
		break;
	case SOUND_KIND_SPELL_SUM:
		playRandm( lsSpellSum.next, nRepeat );
		break;
	case SOUND_KIND_SPELL_SHA:
		playRandm( lsSpellSha.next, nRepeat );
		break;
	case SOUND_KIND_SPELL_PRI:
		playRandm( lsSpellPri.next, nRepeat );
		break;

	case SOUND_KIND_BLAST_MEMBER:
		playRandm( lsBlastMember.next, nRepeat );
		break;
	case SOUND_KIND_BLAST_MONSTER:
		playRandm( lsBlastMonster.next, nRepeat );
		break;
	case SOUND_KIND_BLAST_DESTRUCTION:
		playRandm( lsBlastDestruction.next, nRepeat );
		break;

	case SOUND_KIND_MENU_CANCEL:
		playRandm( lsMenuCancel.next, nRepeat );
		break;
	case SOUND_KIND_MENU_SELECT:
		playRandm( lsMenuSelect.next, nRepeat );
		break;

	case SOUND_KIND_FIGHT_DIE_MEMBER:
		playRandm( lsFightDieMember.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DIE_MONSTER_BOSS_LAST:
		playRandm( lsFightDieMonsterBossLast.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DIE_MONSTER_BOSS:
		playRandm( lsFightDieMonsterBoss.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DIE_MONSTER:
		playRandm( lsFightDieMonster.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DEFENSE_MISS_MEMBER:
		playRandm( lsFightDefenseMissMember.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DEFENSE_MISS_MONSTER_BOSS_LAST:
		playRandm( lsFightDefenseMissMonsterBossLast.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DEFENSE_MISS_MONSTER:
		playRandm( lsFightDefenseMissMonster.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DEFENSE_HIT_MEMBER:
		playRandm( lsFightDefenseHitMember.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DEFENSE_HIT_MONSTER:
		playRandm( lsFightDefenseHitMonster.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DEFENSE_CRITICAL_MEMBER:
		playRandm( lsFightDefenseCriticalMember.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_DEFENSE_CRITICAL_MONSTER:
		playRandm( lsFightDefenseCriticalMonster.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_FIND_MEMBER:
		playRandm( lsFightFindMember.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_FIND_MONSTER_BOSS:
		playRandm( lsFightFindMonsterBoss.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_FIND_MONSTER:
		playRandm( lsFightFindMonster.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_ATTACK_LAST_BOSS_ATTACK:
		playRandm( lsFightAttackLastBossAttack.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_ATTACK_LAST_BOSS_WEAKEN:
		playRandm( lsFightAttackLastBossWeaken.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_ATTACK_LAST_BOSS_SLAP:
		playRandm( lsFightAttackLastBossSlap.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_ATTACK_THROW_MEMBER:
		playRandm( lsFightAttackThrowMember.next, nRepeat );
		break;
	case SOUND_KIND_FIGHT_ATTACK_THROW_MONSTER:
		playRandm( lsFightAttackThrowMonster.next, nRepeat );
		break;

	case SOUND_KIND_REQUEST_FINISH:
		playRandm( lsRequestFinish.next, nRepeat );
		break;

	case SOUND_KIND_SHOP_SALE:
		playRandm( lsShopSale.next, nRepeat );
		break;
	case SOUND_KIND_SHOP_BUY_DRINK:
		playRandm( lsShopBuyDrink.next, nRepeat );
		break;
	case SOUND_KIND_SHOP_BUY:
		playRandm( lsShopBuy.next, nRepeat );
		break;

	case SOUND_KIND_EVENT_GATE:
		playRandm( lsEventGate.next, nRepeat );
		break;
	case SOUND_KIND_EVENT_DRIVE:
		playRandm( lsEventDrive.next, nRepeat );
		break;
	case SOUND_KIND_EVENT_EARTHQUAKE:
		playRandm( lsEventEarthquake.next, nRepeat );
		break;

	case SOUND_KIND_LEVEL_DOWN:
		playRandm( lsLevelDown.next, nRepeat );
		break;
	case SOUND_KIND_LEVEL_UP:
		playRandm( lsLevelUp.next, nRepeat );
		break;

	case SOUND_KIND_DOOR_CLOSE:
		playRandm( lsDoorClose.next, nRepeat );
		break;
	case SOUND_KIND_DOOR_OPEN:
		playRandm( lsDoorOpen.next, nRepeat );
		break;

	case SOUND_KIND_STAIRS_DOWN:
		playRandm( lsStairsDown.next, nRepeat );
		break;
	case SOUND_KIND_STAIRS_UP:
		playRandm( lsStairsUp.next, nRepeat );
		break;

	case SOUND_KIND_ITEM_USE:
		playRandm( lsItemUse.next, nRepeat );
		break;
	case SOUND_KIND_ITEM_OPEN:
		playRandm( lsItemOpen.next, nRepeat );
		break;
	case SOUND_KIND_ITEM_SMOKE:
		playRandm( lsItemSmoke.next, nRepeat );
		break;

	case SOUND_KIND_ACTION_APPEAR:
		playRandm( lsActionAppear.next, nRepeat );
		break;
	case SOUND_KIND_ACTION_TELEPORT_RECALL:
		playRandm( lsActionTeleportRecall.next, nRepeat );
		break;
	case SOUND_KIND_ACTION_TELEPORT_PARTY:
		playRandm( lsActionTeleportParty.next, nRepeat );
		break;
	case SOUND_KIND_ACTION_TELEPORT_SHORT:
		playRandm( lsActionTeleportShort.next, nRepeat );
		break;
	case SOUND_KIND_ACTION_TELEPORT_LONG:
		playRandm( lsActionTeleportLong.next, nRepeat );
		break;

	case SOUND_KIND_MAX_N:
		break;
	}
#endif
}

////////////////////////////////////////////////////////////////
// リストからランダムに選んで SE を再生
// LsSound *p : SE のリスト
// long nRepeat : 再生回数
////////////////////////////////////////////////////////////////

void GameSound::playRandm( LsSound *p, long nRepeat )
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	stop();

	Mix_Chunk *playChunk = NULL;
	for( long i = 0; i < LOOP_MAX_1000; i++ ){
		if( p == NULL )
			break;

		if( gui_randm( i + 1 ) == 0 )
			playChunk = p->chunk;

		p = p->next;
	}
	if( playChunk == NULL )
		return;

	if( nRepeat > 0 )
		nRepeat--;
	else
		nRepeat = -1;

	nPhaserChannel = Mix_PlayChannel( -1, playChunk, nRepeat );
#endif
}

////////////////////////////////////////////////////////////////
// SE を停止
////////////////////////////////////////////////////////////////

void GameSound::stop()
{
#ifdef	HAVE_SDL_SDL_MIXER_H
	if( nPhaserChannel > -1 )
		Mix_HaltChannel( nPhaserChannel );

	nPhaserChannel = -1;
#endif
}
