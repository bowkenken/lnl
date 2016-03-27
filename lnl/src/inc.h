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
* $Id: inc.h,v 1.178 2014/03/15 00:50:40 bowkenken Exp $
***************************************************************/

#ifndef	INC_H
#define	INC_H

/***************************************************************
* インクルード・リスト
***************************************************************/

#ifdef	AMENU_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
#include	"item.h"
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
#include	"trap.h"
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
#include	"amenu.h"
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
#include	"item-prot.h"
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
#include	"amenu-prot.h"
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#include	"call-prot.h"

#endif	/* AMENU_C */

/***************************************************************/

#ifdef	CHR_C

#include	"gmain.h"
/*#include	"misc.h"*/
#include	"scene.h"
/*#include	"turn.h"*/
/*#include	"dun.h"*/
#include	"map-event.h"
#include	"town.h"
#include	"item.h"
#include	"spell.h"
#include	"chr.h"
#include	"skill.h"
#include	"party.h"
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
#include	"trap.h"
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
#include	"amenu.h"
#include	"request.h"
#include	"play-rep.h"
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
#include	"turn-prot.h"
#include	"dun-prot.h"
#include	"map-event-prot.h"
#include	"town-prot.h"
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
#include	"skill-prot.h"
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
#include	"fight-prot.h"
#include	"fx-prot.h"
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
#include	"amenu-prot.h"
#include	"request-prot.h"
#include	"play-rep-prot.h"
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"last-boss.h"
#include	"last-boss-prot.h"

#include	"win-kind.h"
#include	"call-prot.h"

#endif	/* CHR_C */

/***************************************************************/

#ifdef	SKILL_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
#include	"dun.h"
/*#include	"map-event.h"*/
/*#include	"town.h"*/
#include	"item.h"
/*#include	"spell.h"*/
#include	"chr.h"
#include	"skill.h"
#include	"party.h"
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
#include	"trap.h"
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
#include	"skill-prot.h"
#include	"party-prot.h"
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#endif	/* SKILL_C */

/***************************************************************/

#ifdef	CURS_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"win-kind.h"
#include	"call-prot.h"

# ifdef	D_DOS
#  ifndef	_WINDOWS_
#   include	<windows.h>
#  endif
#  include	<conio.h>
#  ifndef D_DOWS
#   include	"lnl-dos/stdafx.h"
#  endif
# endif /* D_DOS */

#endif	/* CURS_C */

/***************************************************************/

#ifdef	REPLAY_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
#include	"turn.h"
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
#include	"replay.h"
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
#include	"amenu.h"
/*#include	"request.h"*/
#include	"play-rep.h"
#include	"gfile.h"
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
#include	"turn-prot.h"
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
#include	"replay-prot.h"
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
#include	"gfile-prot.h"
#include	"msg-prot.h"

#include	"call-prot.h"

#endif	/* REPLAY_C */

/***************************************************************/

#ifdef	DRAW_C

#include	"gmain.h"
/*#include	"misc.h"*/
#include	"scene.h"
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
#include	"item.h"
#include	"spell.h"
#include	"chr.h"
#include	"skill.h"
/*#include	"party.h"*/
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
#include	"fx.h"
/*#include	"trap.h"*/
#include	"replay.h"
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
#include	"amenu.h"
/*#include	"request.h"*/
#include	"play-rep.h"
#include	"gfile.h"
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
#include	"skill-prot.h"
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
#include	"fight-prot.h"
#include	"fx-prot.h"
/*#include	"trap-prot.h"*/
#include	"replay-prot.h"
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
#include	"tmenu-prot.h"
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
#include	"gfile-prot.h"
#include	"msg-prot.h"

#include	"vfx-kind.h"
#include	"win-kind.h"
#include	"call-prot.h"

# ifdef	D_X68K
#  include	<doslib.h>
# endif

# ifdef	D_DOS
#  include	<conio.h>
# endif

#endif	/* DRAW_C */

/***************************************************************/

#ifdef	DUN_C

#include	"gmain.h"
/*#include	"misc.h"*/
#include	"scene.h"
/*#include	"turn.h"*/
#include	"dun.h"
#include	"map-event.h"
#include	"town.h"
#include	"item.h"
#include	"spell.h"
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
#include	"amenu.h"
#include	"request.h"
#include	"play-rep.h"
#include	"gfile.h"
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
#include	"map-event-prot.h"
#include	"town-prot.h"
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
#include	"trap-prot.h"
#include	"replay-prot.h"
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
#include	"request-prot.h"
/*#include	"play-rep-prot.h"*/
#include	"gfile-prot.h"
/*#include	"msg-prot.h"*/

#include	"key-item.h"
#include	"key-item-prot.h"
#include	"last-boss.h"
#include	"last-boss-prot.h"

#include	"nest-flg.h"
#include	"nest-flg-prot.h"

#include	"win-kind.h"
#include	"call-prot.h"

#endif	/* DUN_C */

/***************************************************************/

#ifdef	MAP_EVENT_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
#include	"dun.h"
#include	"map-event.h"
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
#include	"map-event-prot.h"
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#endif	/* MAP_EVENT_C */

/***************************************************************/

#ifdef	FIGHT_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
#include	"item.h"
#include	"spell.h"
/*#include	"chr.h"*/
#include	"skill.h"
#include	"party.h"
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
#include	"fight.h"
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
#include	"play-rep.h"
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
#include	"item-prot.h"
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
#include	"skill-prot.h"
#include	"party-prot.h"
#include	"mnstr-prot.h"
/*#include	"pet-prot.h"*/
#include	"fight-prot.h"
#include	"fx-prot.h"
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
#include	"play-rep-prot.h"
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"last-boss.h"
#include	"last-boss-prot.h"

#include	"call-prot.h"

#endif	/* FIGHT_C */

/***************************************************************/

#ifdef	FX_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
#include	"turn.h"
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
#include	"item.h"
#include	"spell.h"
/*#include	"chr.h"*/
/*#include	"skill.h"*/
#include	"party.h"
/*#include	"mnstr.h"*/
#include	"pet.h"
/*#include	"fight.h"*/
#include	"fx.h"
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
#include	"fight-prot.h"
#include	"fx-prot.h"
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#include	"call-prot.h"

#endif	/* FX_C */

/***************************************************************/

#ifdef	GFILE_C

# ifndef	EXTERN
#  define	EXTERN	extern
# endif	/* EXTERN */

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
#include	"turn.h"
#include	"dun.h"
/*#include	"map-event.h"*/
#include	"town.h"
#include	"item.h"
#include	"spell.h"
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
#include	"fx.h"
#include	"trap.h"
#include	"replay.h"
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
#include	"amenu.h"
#include	"request.h"
#include	"play-rep.h"
#include	"gfile.h"
#include	"msg.h"
#include	"ver.h"
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
#include	"town-prot.h"
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
#include	"trap-prot.h"
#include	"replay-prot.h"
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
#include	"amenu-prot.h"
#include	"request-prot.h"
#include	"play-rep-prot.h"
#include	"gfile-prot.h"
#include	"msg-prot.h"

#ifdef	D_ALL_GUI
# include	"GraphConfToken.h"
#endif

#include	"gfile-ver.h"

#include	"win-kind.h"
#include	"joy-kind.h"
#include	"call-prot.h"

#endif	/* GFILE_C */

/***************************************************************/

#ifdef	GMAIN_C

#include	"gmain.h"
#include	"misc.h"
#include	"scene.h"
#include	"turn.h"
#include	"dun.h"
#include	"map-event.h"
#include	"town.h"
#include	"item.h"
#include	"spell.h"
#include	"chr.h"
#include	"skill.h"
#include	"party.h"
#include	"mnstr.h"
#include	"pet.h"
#include	"fight.h"
#include	"fx.h"
#include	"trap.h"
#include	"replay.h"
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
#include	"amenu.h"
#include	"request.h"
#include	"play-rep.h"
#include	"gfile.h"
#include	"msg.h"
#include	"ver.h"
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
#include	"turn-prot.h"
#include	"dun-prot.h"
#include	"map-event-prot.h"
#include	"town-prot.h"
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
#include	"skill-prot.h"
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"mnstr-act-prot.h"
#include	"pet-prot.h"
#include	"fight-prot.h"
#include	"fx-prot.h"
#include	"trap-prot.h"
#include	"replay-prot.h"
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
#include	"tmenu-prot.h"
#include	"amenu-prot.h"
#include	"request-prot.h"
#include	"play-rep-prot.h"
#include	"gfile-prot.h"
#include	"msg-prot.h"

#include	"nest-flg.h"
#include	"nest-flg-prot.h"

#include	<signal.h>

#ifdef	HAVE_GETOPT_H
# include	<getopt.h>
#endif

#if	defined( HAVE_TERMIOS_H )
# include	<termios.h>
#elif	defined( HAVE_TERMIO_H )
# include	<termio.h>
#endif

#include	"key-item.h"
#include	"key-item-prot.h"
#include	"last-boss.h"
#include	"last-boss-prot.h"
#include	"ending-ep.h"
#include	"ending-ep-prot.h"
#include	"ending-space.h"
#include	"ending-space-prot.h"
#include	"win-kind.h"
#include	"call-prot.h"

#include	"main-prot.h"

#ifdef	D_WS
# include	"main-x-prot.h"
#endif	/* D_WS */

#ifdef	D_GTK
# include	"main-x-prot.h"
#endif	/* D_GTK */

#ifdef	D_IPHONE
void    gexit( long code );
#endif	/* D_IPHONE */

#ifdef	D_MFC
# include	"main-dows-prot.h"
#endif	/* D_MFC */

#endif	/* GMAIN_C */

/***************************************************************/

#ifdef	IMENU_C

#include	"gmain.h"
#include	"misc.h"
#include	"scene.h"
#include	"turn.h"
#include	"dun.h"
/*#include	"map-event.h"*/
#include	"town.h"
#include	"item.h"
#include	"spell.h"
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
#include	"fx.h"
#include	"trap.h"
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
#include	"amenu.h"
/*#include	"request.h"*/
#include	"play-rep.h"
#include	"gfile.h"
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
#include	"town-prot.h"
#include	"item-prot.h"
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
#include	"trap-prot.h"
#include	"replay-prot.h"
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
#include	"amenu-prot.h"
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
#include	"gfile-prot.h"
#include	"msg-prot.h"

#include	"key-item.h"
#include	"key-item-prot.h"

#include	"win-kind.h"
#include	"joy-kind.h"
#include	"call-prot.h"

#endif	/* IMENU_C */

/***************************************************************/

#ifdef	ITEM_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
#include	"item.h"
#include	"spell.h"
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
/*#include	"menu.h"*/
#include	"amenu.h"
#include	"request.h"
#include	"play-rep.h"
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
#include	"amenu-prot.h"
#include	"request-prot.h"
#include	"play-rep-prot.h"
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"last-boss.h"
#include	"last-boss-prot.h"

#endif	/* ITEM_C */

/***************************************************************/

#ifdef	MAIN_DOS_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
#include	"ver.h"
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"main-dos-prot.h"

#endif	/* MAIN_DOS_C */

/***************************************************************/

#ifdef	MAIN_UNIX_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
#include	"ver.h"
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"main-unix-prot.h"
#include	"win-kind.h"
#include	"call-prot.h"

# endif	/* MAIN_UNIX_C */

/***************************************************************/

#ifdef	MENU_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
#include	"party.h"
/*#include	"mnstr.h"*/
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
/*#include	"mnstr-prot.h"*/
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"nest-flg.h"
#include	"nest-flg-prot.h"

#include	"win-kind.h"
#include	"call-prot.h"

#endif	/* MENU_C */

/***************************************************************/

#ifdef	MISC_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

# ifdef D_GTK
#  include <gtk/gtk.h>
# endif /* D_GTK */

#endif	/* MISC_C */

/***************************************************************/

#ifdef	MMENU_C

#include	"gmain.h"
/*#include	"misc.h"*/
#include	"scene.h"
#include	"turn.h"
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
/*#include	"item.h"*/
#include	"spell.h"
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
#include	"replay.h"
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
#include	"amenu.h"
/*#include	"request.h"*/
#include	"play-rep.h"
#include	"gfile.h"
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
#include	"town-prot.h"
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
#include	"trap-prot.h"
#include	"replay-prot.h"
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
#include	"tmenu-prot.h"
#include	"amenu-prot.h"
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
#include	"gfile-prot.h"
#include	"msg-prot.h"

#include	"last-boss.h"
#include	"last-boss-prot.h"

#include	"win-kind.h"
#include	"call-prot.h"

#endif	/* MMENU_C */

/***************************************************************/

#ifdef	MNSTR_ACT_C

#include	"gmain.h"
#include	"misc.h"
#include	"scene.h"
#include	"turn.h"
#include	"dun.h"
/*#include	"map-event.h"*/
#include	"town.h"
#include	"item.h"
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
#include	"fx.h"
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
#include	"request.h"
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
#include	"town-prot.h"
#include	"item-prot.h"
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"mnstr-act-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
#include	"request-prot.h"
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#endif	/* MNSTR_ACT_C */

/***************************************************************/

#ifdef	MNSTR_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
#include	"item.h"
#include	"spell.h"
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
#include	"trap.h"
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
#include	"request.h"
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
#include	"fight-prot.h"
#include	"fx-prot.h"
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
#include	"request-prot.h"
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"key-item.h"
#include	"key-item-prot.h"

#include	"last-boss.h"
#include	"last-boss-prot.h"

#include	"call-prot.h"

#endif	/* MNSTR_C */

/***************************************************************/

#ifdef	MSG_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#ifdef	HAVE_LOCALE_H
# include	<locale.h>
#endif

#endif	/* MSG_C */

/***************************************************************/

#ifdef	PARTY_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
#include	"map-event.h"
#include	"town.h"
#include	"item.h"
#include	"spell.h"
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
#include	"amenu.h"
#include	"request.h"
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
#include	"map-event-prot.h"
#include	"town-prot.h"
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
#include	"fight-prot.h"
#include	"fx-prot.h"
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
/*#include	"mmenu-prot.h"*/
#include	"imenu-prot.h"
#include	"tmenu-prot.h"
#include	"amenu-prot.h"
#include	"request-prot.h"
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"last-boss.h"

#include	"call-prot.h"

#endif	/* PARTY_C */

/***************************************************************/

#ifdef	PET_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
#include	"dun.h"
/*#include	"map-event.h"*/
/*#include	"town.h"*/
#include	"item.h"
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
#include	"fx.h"
#include	"trap.h"
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"call-prot.h"

#endif	/* PET_C */

/***************************************************************/

#ifdef	PLAY_REP_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
#include	"play-rep.h"
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
#include	"play-rep-prot.h"
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#endif	/* PLAY_REP_C */

/***************************************************************/

#ifdef	REQUEST_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
#include	"turn.h"
#include	"dun.h"
/*#include	"map-event.h"*/
#include	"town.h"
#include	"item.h"
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
#include	"fx.h"
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
/*#include	"amenu.h"*/
#include	"request.h"
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
#include	"town-prot.h"
#include	"item-prot.h"
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
/*#include	"mmenu-prot.h"*/
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
#include	"request-prot.h"
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"call-prot.h"

#endif	/* REQUEST_C */

/***************************************************************/

#ifdef	SPELL_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
#include	"spell.h"
/*#include	"chr.h"*/
#include	"skill.h"
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
#include	"play-rep.h"
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
#include	"item-prot.h"
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
#include	"skill-prot.h"
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
#include	"play-rep-prot.h"
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#include	"last-boss.h"
#include	"last-boss-prot.h"

#include	"call-prot.h"

#endif	/* SPELL_C */

/***************************************************************/

#ifdef	TMENU_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
#include	"turn.h"
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
#include	"item.h"
#include	"spell.h"
/*#include	"chr.h"*/
#include	"skill.h"
/*#include	"party.h"*/
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
#include	"amenu.h"
/*#include	"request.h"*/
#include	"play-rep.h"
#include	"gfile.h"
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
#include	"town-prot.h"
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
#include	"skill-prot.h"
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
#include	"amenu-prot.h"
/*#include	"request-prot.h"*/
#include	"play-rep-prot.h"
#include	"gfile-prot.h"
#include	"msg-prot.h"

#include	"call-prot.h"

#endif	/* TMENU_C */

/***************************************************************/

#ifdef	TOWN_C

#include	"gmain.h"
/*#include	"misc.h"*/
#include	"scene.h"
#include	"turn.h"
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
#include	"item.h"
#include	"spell.h"
#include	"chr.h"
/*#include	"skill.h"*/
/*#include	"party.h"*/
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
#include	"amenu.h"
#include	"request.h"
#include	"play-rep.h"
#include	"gfile.h"
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
#include	"town-prot.h"
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
#include	"tmenu-prot.h"
/*#include	"amenu-prot.h"*/
#include	"request-prot.h"
#include	"play-rep-prot.h"
#include	"gfile-prot.h"
/*#include	"msg-prot.h"*/

#endif	/* TOWN_C */

/***************************************************************/

#ifdef	TRAP_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
#include	"dun.h"
/*#include	"map-event.h"*/
/*#include	"town.h"*/
#include	"item.h"
#include	"spell.h"
/*#include	"chr.h"*/
/*#include	"skill.h"*/
#include	"party.h"
/*#include	"mnstr.h"*/
#include	"pet.h"
#include	"fight.h"
#include	"fx.h"
#include	"trap.h"
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
#include	"item-prot.h"
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
/*#include	"mnstr-prot.h"*/
#include	"pet-prot.h"
#include	"fight-prot.h"
#include	"fx-prot.h"
#include	"trap-prot.h"
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
#include	"menu-prot.h"
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"call-prot.h"

#endif	/* TRAP_C */

/***************************************************************/

#ifdef	TURN_C

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
#include	"turn.h"
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
#include	"item.h"
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
#include	"pet.h"
/*#include	"fight.h"*/
#include	"fx.h"
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
#include	"request.h"
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
#include	"turn-prot.h"
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
#include	"town-prot.h"
#include	"item-prot.h"
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
#include	"mnstr-prot.h"
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
#include	"fx-prot.h"
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
#include	"request-prot.h"
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#endif	/* TURN_C */

/***************************************************************/

#ifdef	SCENE_C

#include	"gmain.h"
#include	"misc.h"
#include	"scene.h"
/*#include	"turn.h"*/
#include	"dun.h"
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"call-prot.h"

#endif	/* SCENE_C */

/***************************************************************/

#ifdef	KEY_ITEM_C

#include	"gmain.h"
/*#include	"misc.h"*/
#include	"scene.h"
/*#include	"turn.h"*/
#include	"dun.h"
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
#include	"play-rep.h"
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
#include	"scene-prot.h"
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"key-item.h"
#include	"key-item-prot.h"
#include	"last-boss.h"
#include	"last-boss-prot.h"
#include	"call-prot.h"

#endif	/* KEY_ITEM_C */

/***************************************************************/

#ifdef	LAST_BOSS_C

#include	"gmain.h"
#include	"misc.h"
#include	"scene.h"
/*#include	"turn.h"*/
#include	"dun.h"
#include	"map-event.h"
/*#include	"town.h"*/
/*#include	"item.h"*/
#include	"spell.h"
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
/*#include	"pet.h"*/
#include	"fight.h"
#include	"fx.h"
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
#include	"map-event-prot.h"
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
#include	"spell-prot.h"
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
/*#include	"pet-prot.h"*/
#include	"fight-prot.h"
#include	"fx-prot.h"
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"last-boss.h"
#include	"last-boss-prot.h"

#include	"call-prot.h"

#endif	/* LAST_BOSS_C */

/***************************************************************/

#ifdef	ENDING_EP_C

#include	"gmain.h"
#include	"misc.h"
#include	"scene.h"
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#include	"ending-ep.h"
#include	"ending-ep-prot.h"
#include	"ending-space.h"
#include	"ending-space-prot.h"

#endif	/* ENDING_EP_C */

/***************************************************************/

#ifdef	ENDING_SPACE_C

#include	"gmain.h"
#include	"misc.h"
#include	"scene.h"
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
#include	"curs.h"
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#include	"ending-space.h"
#include	"ending-space-prot.h"

#endif	/* ENDING_SPACE_C */

/***************************************************************
* xlnl
***************************************************************/

#ifdef	MAIN_X_C

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
#include	"ver.h"
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"main-x-prot.h"
#include	"win-kind.h"
#include	"call-prot.h"

#include	<gtk/gtk.h>

#endif	/* MAIN_X_C */

/***************************************************************/

#ifdef	MAIN_DOWS_CPP

#include	"gmain.h"
/*#include	"misc.h"*/
#include	"scene.h"
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
#include	"ver.h"
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
#include	"scene-prot.h"
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"MouseMap.h"
#include	"GlobalVar.h"

#include	"main-dows-prot.h"
#include	"win-kind.h"
#include	"call-prot.h"

#include	"xlnl-dows/stdafx.h"
#include	"xlnl-dows/xlnl-dows.h"
#include	"xlnl-dows/MainFrm.h"

#endif	/* MAIN_DOWS_CPP */

/***************************************************************/

#ifdef	MAIN_GTK_CPP

#include	"gmain.h"
/*#include	"misc.h"*/
#include	"scene.h"
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
#include	"scene-prot.h"
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#include	<gtk/gtk.h>
#include	<gdk-pixbuf/gdk-pixbuf.h>

#include	"CuiMouse.h"
#include	"MouseMap.h"
#include	"GraphConf.h"
#include	"GlobalVar.h"

#include	"main-x-prot.h"
#include	"main-gtk-prot.h"
#include	"win-kind.h"
#include	"call-prot.h"

#endif	/* MAIN_GTK_CPP */

/***************************************************************/

#ifdef	MAIN_IPHONE_CPP

#include	"gmain.h"
/*#include	"misc.h"*/
#include	"scene.h"
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
#include	"scene-prot.h"
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#include	"CuiMouse.h"
#include	"MouseMap.h"
#include	"GraphConf.h"
#include	"GlobalVar.h"

#include	"main-iphone-prot.h"
#include	"win-kind.h"
#include	"call-prot.h"

#endif	/* MAIN_IPHONE_CPP */

/***************************************************************/

#ifdef	CALL_CPP

# if	defined( D_WS )
#  include <WSDappDev.h>
#  include <WSCwindow.h>
#  include "gmain.h"
#  include "misc.h"
#  include "chr.h"
/*#include	"skill.h"*/
#  include "draw.h"
#  include "GameThread.h"
#  include "GuiMenu.h"
#  include "PcgDun.h"
#  include "GraphConfToken.h"
#  include "SelMbrGraph.h"
#  include "GlobalVar.h"
#  include "gmain-prot.h"
#  include "misc-prot.h"
#  include "chr-prot.h"
/*#include	"skill-prot.h"*/
#  include "draw-prot.h"
# elif	defined( D_GTK )
#  include "gmain.h"
#  include "misc.h"
#  include "chr.h"
/*#include	"skill.h"*/
#  include "draw.h"
#  include "GameThread.h"
#  include "GuiMenu.h"
#  include "PcgDun.h"
#  include "GraphConfToken.h"
#  include "SelMbrGraph.h"
#  include "GlobalVar.h"
#  include "gmain-prot.h"
#  include "misc-prot.h"
#  include "chr-prot.h"
/*#include	"skill-prot.h"*/
#  include "draw-prot.h"
#  include "main-gtk-prot.h"
# elif	defined( D_IPHONE )
#  include "gmain.h"
#  include "misc.h"
#  include "chr.h"
/*#include	"skill.h"*/
#  include "draw.h"
#  include "GameThread.h"
#  include "GuiMenu.h"
#  include "PcgDun.h"
#  include "GraphConfToken.h"
#  include "SelMbrGraph.h"
#  include "GlobalVar.h"
#  include "gmain-prot.h"
#  include "misc-prot.h"
#  include "chr-prot.h"
/*#include	"skill-prot.h"*/
#  include "draw-prot.h"
#  include "main-iphone-prot.h"
# elif	defined( D_MFC )
#  include "gmain.h"
#  include "misc.h"
#  include "chr.h"
/*#include	"skill.h"*/
#  include "draw.h"
#  include "GameThread.h"
#  include "GuiMenu.h"
#  include "PcgDun.h"
#  include "GraphConfToken.h"
#  include "SelMbrGraph.h"
#  include "GlobalVar.h"
#  include "gmain-prot.h"
#  include "misc-prot.h"
#  include "chr-prot.h"
/*#include	"skill-prot.h"*/
#  include "draw-prot.h"
#  include "main-dows-prot.h"
# else
#  include "gmain.h"
#  include "misc.h"
#  include "chr.h"
/*#include	"skill.h"*/
#  include "draw.h"
#  include "misc-prot.h"
#  include "chr-prot.h"
/*#include	"skill-prot.h"*/
# endif

# include "last-boss.h"

# include "win-kind.h"
# include "joy-kind.h"
# include "call-prot.h"

# if defined( D_DOS ) || defined( D_MFC )
#  include	<windows.h>
# endif /* D_MFC */

#endif	/* CALL_CPP */

/***************************************************************/

#ifdef	SEL_CONF_CPP

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
#include	"amenu.h"
/*#include	"request.h"*/
#include	"play-rep.h"
#include	"gfile.h"
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
#include	"gfile-prot.h"
/*#include	"msg-prot.h"*/

#include	"GraphConf.h"

#ifdef D_WS
# include <WSCwindow.h>
# include <WSCbase.h>
# include <WSCvbtn.h>
# include <WSDmouse.h>
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
# include <gdk/gdk.h>
# include "main-gtk-prot.h"
#endif /* D_GTK */

#ifdef D_IPHONE
# include "main-iphone-prot.h"
#endif /* D_IPHONE */

#include "SelConf.h"
#include "GlobalVar.h"

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/SelConfDlg.h"
# include "main-dows-prot.h"
#endif /* D_MFC */

#endif	/* SEL_CONF_CPP */

/***************************************************************/

#ifdef	GRAPH_CONF_CPP

#include	"GraphConf.h"
#include	"GlobalVar.h"

#endif	/* GRAPH_CONF_CPP */

/***************************************************************/

#ifdef	PCG_DUN_CPP
#include	"gmain.h"
#include	"misc.h"
#include	"scene.h"
#include	"turn.h"
#include	"dun.h"
/*#include	"map-event.h"*/
#include	"town.h"
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
#include	"trap.h"
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
#include	"amenu.h"
/*#include	"request.h"*/
#include	"play-rep.h"
#include	"gfile.h"
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
#include	"scene-prot.h"
#include	"turn-prot.h"
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
#include	"mnstr-prot.h"
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
#include	"trap-prot.h"
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
#include	"mmenu-prot.h"
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
#include	"gfile-prot.h"
#include	"msg-prot.h"

#include	"last-boss.h"
#include	"last-boss-prot.h"

#include "GuiMisc.h"
#include "PcgDun.h"
#include "DemoTitle.h"
#include "DemoLastBoss.h"
#include "DemoGameOver.h"
#include "FileList.h"
#include "GlobalVar.h"

#ifdef D_WS
# include <WSCform.h>
# include <WSCvscrBar.h>
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
# include <gdk-pixbuf/gdk-pixbuf.h>
#endif // D_GTK

#ifdef D_MFC
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/MainFrm.h"
#endif // D_GTK

#endif	/* PCG_DUN_CPP */

/***************************************************************/

#ifdef	DEMO_TITLE_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

#include "DemoTitle.h"
#include "GlobalVar.h"

#endif	/* DEMO_TITLE_CPP */

/***************************************************************/

#ifdef	DEMO_LAST_BOSS_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"call-prot.h"

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

#include "DemoLastBoss.h"
#include "GlobalVar.h"

#endif	/* DEMO_LAST_BOSS_CPP */

/***************************************************************/

#ifdef	DEMO_CUT_IN_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

#include "DemoCutIn.h"
#include "FileList.h"
#include "GlobalVar.h"

#endif	/* DEMO_CUT_IN_CPP */

/***************************************************************/

#ifdef	DEMO_GAME_OVER_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

#include "DemoGameOver.h"
#include "GlobalVar.h"

#endif	/* DEMO_GAME_OVER_CPP */

/***************************************************************/

#ifdef	DEMO_ENDING_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

#include "DemoEnding.h"
#include "GlobalVar.h"

#endif	/* DEMO_ENDING_CPP */

/***************************************************************/

#ifdef	DEMO_SPACE_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#include	"ending-space.h"

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
#endif // D_MFC

#include "DemoSpace.h"
#include "GlobalVar.h"

#endif	/* DEMO_SPACE_CPP */

/***************************************************************/

#ifdef	GUI_LAST_BOSS_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
#include	"dun.h"
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
#include	"mnstr.h"
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include	"last-boss.h"
#include	"last-boss-prot.h"

#include "GuiLastBoss.h"
#include "GlobalVar.h"

#endif	/* GUI_LAST_BOSS_CPP */

/***************************************************************/

#ifdef	GAME_MUSIC_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
#include	"dun.h"
/*#include	"map-event.h"*/
#include	"town.h"
#include	"item.h"
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
#include	"imenu-prot.h"
#include	"tmenu-prot.h"
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#include "FileList.h"
#include "GameMusic.h"
#include "GlobalVar.h"

#endif	/* GAME_MUSIC_CPP */

/***************************************************************/

#ifdef	GAME_SOUND_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include "FileList.h"
#include "GameSound.h"
#include "GlobalVar.h"

#endif	/* GAME_SOUND_CPP */

/***************************************************************/

#ifdef	GAME_JOYSTICK_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
/*#include	"curs-prot.h"*/
#include	"menu-prot.h"
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include "GameJoystick.h"
#include "GlobalVar.h"

#endif	/* GAME_JOYSTICK_CPP */

/***************************************************************/

#ifdef	GUI_MENU_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
#include	"menu-prot.h"
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_WS
# include <WSCwindow.h>
# include <WSCbase.h>
# include <WSCvbtn.h>
# include <WSDmouse.h>
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
# include <gdk/gdk.h>
# include <gdk/gdkx.h>
#endif // D_GTK

#include "GuiMenu.h"
#include "GlobalVar.h"

#ifdef D_GTK
# include "main-gtk-prot.h"
#endif // D_GTK

#ifdef D_IPHONE
# include "main-iphone-prot.h"
#endif /* D_IPHONE */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/MenuWnd.h"
#endif // D_MFC

#endif	/* GUI_MENU_CPP */

/***************************************************************/

#ifdef	GUI_MESSAGE_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
/*#include	"draw.h"*/
#include	"curs.h"
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
/*#include	"draw-prot.h"*/
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_GTK
# include <gtk/gtk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/MessageWnd.h"
#endif /* D_MFC */

#include "GuiMisc.h"
#include "GuiMessage.h"
#include "Key.h"
#include "GlobalVar.h"

#ifdef D_GTK
# include "main-gtk-prot.h"
#endif // D_GTK

#ifdef D_IPHONE
# include "main-iphone-prot.h"
#endif /* D_IPHONE */

#endif	/* GUI_MESSAGE_CPP */

/***************************************************************/

#ifdef	GUI_STAT_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
#include	"turn.h"
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
/*#include	"mnstr.h"*/
#include	"pet.h"
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
#include	"turn-prot.h"
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
#include	"town-prot.h"
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
/*#include	"mnstr-prot.h"*/
#include	"pet-prot.h"
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_GTK
# include <gtk/gtk.h>
# include <gdk/gdk.h>
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/StatWnd.h"
#endif /* D_MFC */

#include "GuiStat.h"
#include "Key.h"
#include "GlobalVar.h"

#ifdef D_GTK
# include "main-gtk-prot.h"
#endif /* D_GTK */

#ifdef D_IPHONE
# include "main-iphone-prot.h"
#endif /* D_IPHONE */

#endif	/* GUI_STAT_CPP */

/***************************************************************/

#ifdef	GUI_NUM_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GuiMisc.h"
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/InputNumDlg.h"
#endif // D_MFC

#endif	/* GUI_NUM_CPP */

/***************************************************************/

#ifdef	GUI_INPUT_STRING_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_WS
# include <WSCvifield.h>
# include "MapWin.h"
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GuiMisc.h"
#endif /* D_GTK */

#include "GuiInputString.h"
#include "GlobalVar.h"

#ifdef D_MFC
# include "xlnl-dows/InputLineDlg.h"
#endif // D_MFC

#endif	/* GUI_INPUT_STRING_CPP */

/***************************************************************/

#ifdef	GUI_WORDS_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GuiMisc.h"
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/WordsDlg.h"
# include "MfcWSCstring.h"
#endif // D_MFC

#include "GuiWords.h"
#include "GlobalVar.h"

#ifdef D_GTK
# include "main-gtk-prot.h"
#endif /* D_GTK */

#ifdef D_IPHONE
# include "main-iphone-prot.h"
#endif /* D_IPHONE */

#endif	/* GUI_WORDS_CPP */

/***************************************************************/

#ifdef	GUI_REPLAY_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
#include	"replay.h"
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
#include	"replay-prot.h"
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GuiMisc.h"
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/ReplayWnd.h"
#endif // D_MFC

#include "GuiReplay.h"
#include "GlobalVar.h"

#ifdef D_GTK
# include "main-gtk-prot.h"
#endif /* D_GTK */

#ifdef D_IPHONE
# include "main-iphone-prot.h"
#endif /* D_IPHONE */

#endif	/* GUI_REPLAY_CPP */

/***************************************************************/

#ifdef	GUI_CLASS_EDIT_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
#include	"tmenu-prot.h"
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GuiMisc.h"
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/ClassEditDlg.h"
#endif // D_MFC

#include "GuiClassEdit.h"
#include "GlobalVar.h"

#ifdef D_GTK
# include "main-gtk-prot.h"
#endif /* D_GTK */

#ifdef D_IPHONE
# include "main-iphone-prot.h"
#endif /* D_IPHONE */

#endif	/* GUI_CLASS_EDIT_CPP */

/***************************************************************/

#ifdef	GUI_SKILL_EDIT_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
#include	"town.h"
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
#include	"skill.h"
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
#include	"skill-prot.h"
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
#include	"menu-prot.h"
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
#include	"tmenu-prot.h"
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GuiMisc.h"
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/SkillEditDlg.h"
#endif // D_MFC

#include "GuiSkillEdit.h"
#include "GlobalVar.h"

#ifdef D_GTK
# include "main-gtk-prot.h"
#endif /* D_GTK */

#ifdef D_IPHONE
# include "main-iphone-prot.h"
#endif /* D_IPHONE */

#endif	/* GUI_SKILL_EDIT_CPP */

/***************************************************************/

#ifdef	GUI_CHR_SHEET_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
#include	"turn.h"
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
#include	"item.h"
/*#include	"spell.h"*/
#include	"chr.h"
#include	"skill.h"
#include	"party.h"
#include	"mnstr.h"
/*#include	"pet.h"*/
#include	"fight.h"
#include	"fx.h"
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
#include	"msg.h"
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
#include	"turn-prot.h"
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
#include	"item-prot.h"
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
#include	"skill-prot.h"
#include	"party-prot.h"
#include	"mnstr-prot.h"
/*#include	"pet-prot.h"*/
#include	"fight-prot.h"
#include	"fx-prot.h"
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
#include	"msg-prot.h"

#ifdef D_WS
#endif /* D_WS */

#ifdef D_GTK
# include <gtk/gtk.h>
# include "GuiMisc.h"
#endif /* D_GTK */

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/ChrSheetSheet.h"
#endif // D_MFC

#include "GuiChrSheet.h"
#include "GlobalVar.h"

#endif	/* GUI_CHR_SHEET_CPP */

/***************************************************************/

#ifdef	KEY_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
#include	"dun.h"
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
#include	"replay.h"
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
#include	"dun-prot.h"
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
#include	"replay-prot.h"
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include "Key.h"
#include "GlobalVar.h"

#endif	/* KEY_CPP */

/***************************************************************/

#ifdef	CUI_MOUSE_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
#include	"replay.h"
#include	"draw.h"
#include	"curs.h"
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
#include	"replay-prot.h"
#include	"draw-prot.h"
#include	"curs-prot.h"
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef	HAVE_SYS_FCNTL_H
# include <sys/fcntl.h>
#endif

#ifdef	HAVE_GPM_H
# include <gpm.h>
#endif

#include "CuiMouse.h"
#include "MouseMotion.h"
#include "GlobalVar.h"

#endif	/* CUI_MOUSE_CPP */

/***************************************************************/

#ifdef	MOUSE_MOTION_CPP

#include	"gmain.h"
/*#include	"misc.h"*/
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
/*#include	"chr.h"*/
/*#include	"skill.h"*/
/*#include	"party.h"*/
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
/*#include	"replay.h"*/
#include	"draw.h"
/*#include	"curs.h"*/
/*#include	"menu.h"*/
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
/*#include	"gmain-prot.h"*/
/*#include	"misc-prot.h"*/
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
/*#include	"chr-prot.h"*/
/*#include	"skill-prot.h"*/
/*#include	"party-prot.h"*/
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
/*#include	"replay-prot.h"*/
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
/*#include	"menu-prot.h"*/
/*#include	"mmenu-prot.h"*/
/*#include	"imenu-prot.h"*/
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#include "MouseMotion.h"
#include "GlobalVar.h"

#endif	/* MOUSE_MOTION_CPP */

/***************************************************************/

#ifdef	MOUSE_MAP_CPP

#include	"gmain.h"
#include	"misc.h"
/*#include	"scene.h"*/
/*#include	"turn.h"*/
/*#include	"dun.h"*/
/*#include	"map-event.h"*/
/*#include	"town.h"*/
/*#include	"item.h"*/
/*#include	"spell.h"*/
#include	"chr.h"
/*#include	"skill.h"*/
#include	"party.h"
/*#include	"mnstr.h"*/
/*#include	"pet.h"*/
/*#include	"fight.h"*/
/*#include	"fx.h"*/
/*#include	"trap.h"*/
#include	"replay.h"
#include	"draw.h"
/*#include	"curs.h"*/
#include	"menu.h"
/*#include	"amenu.h"*/
/*#include	"request.h"*/
/*#include	"play-rep.h"*/
/*#include	"gfile.h"*/
/*#include	"msg.h"*/
/*#include	"ver.h"*/
#include	"gmain-prot.h"
#include	"misc-prot.h"
/*#include	"scene-prot.h"*/
/*#include	"turn-prot.h"*/
/*#include	"dun-prot.h"*/
/*#include	"map-event-prot.h"*/
/*#include	"town-prot.h"*/
/*#include	"item-prot.h"*/
/*#include	"spell-prot.h"*/
#include	"chr-prot.h"
/*#include	"skill-prot.h"*/
#include	"party-prot.h"
/*#include	"mnstr-prot.h"*/
/*#include	"pet-prot.h"*/
/*#include	"fight-prot.h"*/
/*#include	"fx-prot.h"*/
/*#include	"trap-prot.h"*/
#include	"replay-prot.h"
#include	"draw-prot.h"
/*#include	"curs-prot.h"*/
#include	"menu-prot.h"
#include	"mmenu-prot.h"
#include	"imenu-prot.h"
/*#include	"tmenu-prot.h"*/
/*#include	"amenu-prot.h"*/
/*#include	"request-prot.h"*/
/*#include	"play-rep-prot.h"*/
/*#include	"gfile-prot.h"*/
/*#include	"msg-prot.h"*/

#ifdef D_WS
# include <WScom.h>
# include <WSCfunctionList.h>
# include <WSCbase.h>

# include <WSCvscrBar.h>
# include <WSCwindow.h>
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
#endif // D_GTK

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/MainFrm.h"
#endif // D_MFC

#include "GraphConf.h"
#include "MouseMap.h"
#include "Key.h"
#include "GlobalVar.h"

#ifdef D_GTK
# include "main-gtk-prot.h"
#endif // D_GTK

#ifdef D_IPHONE
# include "main-iphone-prot.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "main-dows-prot.h"
#endif // D_MFC

#endif	/* MOUSE_MAP_CPP */

/***************************************************************/

#if 0
#if	defined( D_WS )
# include	"main-ws-prot.h"
#elif	defined( D_DOWS )
# include	"main-dows-prot.h"
#elif	defined( D_DOS )
# include	"main-dos-prot.h"
#else
# include	"main-unix-prot.h"
#endif
#endif

/***************************************************************/

#endif	/* INC_H */
