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
* $Id: party.c,v 1.258 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* パーティ (プレイヤー・キャラクタ)
***************************************************************/

#define	PARTY_C
#include	"inc.h"

/***************************************************************/

/* 1 にすると煙草のニコチン中毒のテストをする */
#define	FLG_NICOTINE_TEST	0

/***************************************************************/

/* メンバーの初期データ */

#define	DFLT_EXP	500
#define	DFLT_GOLD	3000
#define	DFLT_GRAPH_NAME	"default.bmp"

/* 1 番近くのメンバーを探す時の同じ距離と判定する半径 */
#define	MBR_NEAR_R	4

/* 金銭をやり取り出来る様になるまでのターン数 */
#define	FRIEND_MAX_TURN	(6 * TURN_PER_HOUR)

/* メンバー・リストの空きデータ */
#define	LS_MBR_NULL	LS_MBR_MAX_N

/***************************************************************
* パーティのデータ
***************************************************************/

static mbr_t	*ls_mbr[LS_MBR_MAX_N + 1];
check_memory_def( check_memory_party_c_ls_mbr )
static mbr_t	ls_mbr_buf[LS_MBR_MAX_N + 1];
check_memory_def( check_memory_party_c_ls_mbr_buf )
static party_t	party;
check_memory_def( check_memory_party_c_party )

static long	abl_init[MAIN_RACE_MAX_N][ABL_KIND_MAX_N] = {

	/* HP  MP  DEX STR */
	/* QUI INT WIS CHA */
	/* FIG MON HUN THI */
	/* MAG SOR ENC SUM */
	/* PRI SHA BAR NIN */

	/* MAIN_RACE_HUMAN, */
	{
		2, 2, 2, 2,
		2, 2, 2, 2,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},

	/* MAIN_RACE_HALF_ELF, */
	{
		2, 2, 2, 1,
		3, 2, 2, 2,
		0, 0, 1, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},

	/* MAIN_RACE_ELF, */
	{
		1, 2, 2, 1,
		3, 2, 2, 3,
		0, 0, 1, 0,
		0, 0, 0, 0,
		0, 1, 0, 0,
	},

	/* MAIN_RACE_DWARF, */
	{
		3, 1, 3, 3,
		1, 2, 2, 1,
		1, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},

	/* MAIN_RACE_VIVID, */
	{
		1, 2, 3, 1,
		3, 2, 2, 2,
		0, 0, 0, 1,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
};
check_memory_def( check_memory_party_c_abl_init )

static rate_t	resi_init[MAIN_RACE_MAX_N][RESI_KIND_MAX_N] = {
	/* KNOC,SLAS,STIN,HEAT,COLD,MIND,ACID,ELEC,POIS, */
/* MAIN_RACE_HUMAN */
	{   100, 100, 100, 100, 100, 100, 100, 100, 100 },
/* MAIN_RACE_HALF_ELF */
	{    90,  90,  90, 110, 110, 110, 110, 100, 100 },
/* MAIN_RACE_ELF */
	{    80,  80,  80, 120, 120, 120, 120, 100, 100 },
/* MAIN_RACE_DWARF */
	{   120, 120, 120,  80,  80,  80, 120, 100, 200 },
/* MAIN_RACE_VIVID */
	{    90,  90,  90, 100, 100, 200, 100, 100, 100 },
};
check_memory_def( check_memory_party_c_resi_init )

static stomach_t	ave_stomach[MAIN_RACE_MAX_N] = {
#if	0
typedef struct {
	rate_t	rate;
	rate_t	full_rate;
	long	digest_p_day;
	rate_t	digest_rate;
	rate_t	hungry_rate, starvation_rate;
} stomach_t;
#endif
	{ 100, 100, 20, 0, 70, 30 },	/* MAIN_RACE_HUMAN, */
	{ 100,  80, 15, 0, 70, 30 },	/* MAIN_RACE_HALF_ELF, */
	{ 100,  50, 10, 0, 70, 30 },	/* MAIN_RACE_ELF, */
	{ 100, 200, 25, 0, 70, 30 },	/* MAIN_RACE_DWARF, */
	{ 100, 180, 25, 0, 70, 30 },	/* MAIN_RACE_VIVID, */
};
check_memory_def( check_memory_party_c_ave_stomach )

/* class */

#include	"class-tab.h"

/***************************************************************/

void	init_party( void )
{
	long	i, j, max_n;

	for( i = 0; i < LS_MBR_MAX_N + 1; i++ )
		ls_mbr[i] = &(ls_mbr_buf[i]);

	for( i = 0; i < MBR_MAX_N; i++ )
		party.mbr[i] = ls_mbr[i];

	for( i = 0; i < LS_MBR_MAX_N + 1; i++ ){
		ls_mbr[i]->stat = FLG_STAT_NOT_EXIST;
		ls_mbr[i]->mbr_n = MBR_N_NOT_JOIN;
		ls_mbr[i]->ls_mbr_n = i;
		ls_mbr[i]->x = MAP_DEL_X;
		ls_mbr[i]->y = MAP_DEL_Y;
		ls_mbr[i]->pre_x = MAP_DEL_X;
		ls_mbr[i]->pre_y = MAP_DEL_Y;
		ls_mbr[i]->flg_chr |= FLG_CHR_AUTO_FIGHT;
		ls_mbr[i]->fx.next = &(ls_mbr[i]->fx);
		ls_mbr[i]->fx.prev = &(ls_mbr[i]->fx);
	}

	max_n = sizeof( class_tab ) / sizeof( class_tab[0] );
	for( j = 0; j < max_n; j++ ){
		class_tab[j].n_name = N_MSG_NULL;
		class_tab[j].name[0] = '\0';
	}
	for( j = 0; j < CLASS_MAX_N; j++ ){
		class_tab[j] = class_dflt_tab[j];
		if( class_tab[j].n_name == N_MSG_NULL )
			break;

		str_nz_cpy( class_tab[j].name,
				MSG( class_tab[j].n_name ),
				CLASS_NAME_MAX_BYTE );
	}

	party.square.x = 1;
	party.square.y = 1;
	party.square.pre_x = 1;
	party.square.pre_y = 1;
	party.square.dir = SQUARE_DIR_NORTH;
	party.square.pre_dir = SQUARE_DIR_NORTH;
	party.square.chr_pos_n[0][0] = 0;
	party.square.chr_pos_n[0][1] = MBR_NO_POS;
	party.square.chr_pos_n[0][2] = 1;
	party.square.chr_pos_n[1][0] = 2;
	party.square.chr_pos_n[1][1] = MBR_NO_POS;
	party.square.chr_pos_n[1][2] = 3;
	party.square.chr_pos_n[2][0] = 4;
	party.square.chr_pos_n[2][1] = MBR_NO_POS;
	party.square.chr_pos_n[2][2] = 5;
	reset_mbr_dir();

	party.flg = FLG_NULL;
	party.flg |= FLG_PARTY_SRCH_AUTO_OFF;

	/**/

	if( g_flg_debug )
		init_party_debug();
	else
		init_party_dflt();
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_party( void )
{
}

/**/

void	init_party_dflt( void )
{
	race_t	race;
	item_kind_dat_t	sub_kind;
	long	i;

	i = 0;
	race.main = MAIN_RACE_HUMAN;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_HUMAN, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "<///BLADE//}===o", 'B', race,
			MALE, CLASS_N_FIGHTER, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-01.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	i = 1;
	race.main = MAIN_RACE_DWARF;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_DWARF, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], ")(==DRANK======>", 'D', race,
			MALE, CLASS_N_FIGHTER, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-02.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	i = 2;
	race.main = MAIN_RACE_HALF_ELF;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_HALF_ELF, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "<---ELSIE----<<<", 'E', race,
			MALE, CLASS_N_HUNTER, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-03.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_HALFBACK;

	i = 3;
	race.main = MAIN_RACE_HUMAN;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_HUMAN, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "+-==CECILE=====X", 'C', race,
			FEMALE, CLASS_N_PRIEST, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-04.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	i = 4;
	race.main = MAIN_RACE_VIVID;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_VIVID, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "m-o HALLE  <<<)=", 'H', race,
			MALE, CLASS_N_THIEF, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-05.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_BACK;

	i = 5;
	race.main = MAIN_RACE_ELF;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_ELF, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "O>==BEAUT====---", 'U', race,
			FEMALE, CLASS_N_WIZARD, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-06.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_BACK;

	i = 6;
	race.main = MAIN_RACE_HUMAN;
	race.sub = SUB_RACE_MONKEY;
	str_nz_cpy( race.name, MSG_RACE_NAME_VEGE, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "====GOKOU=======", 'G', race,
			MALE, CLASS_N_MONK, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-07.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	i = 7;
	race.main = MAIN_RACE_HUMAN;
	race.sub = SUB_RACE_CAT;
	str_nz_cpy( race.name, MSG_RACE_NAME_NEKOMIMI, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "----EYE-------|===", 'Y', race,
			FEMALE, CLASS_N_SUMMONER, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-08.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	/* item */

	for( i = 0; i < MBR_MAX_N; i++ ){
		sub_kind.light = LIGHT_KIND_TORCH;
		sub_kind.wish_level = WISH_LEVEL_NULL;
		init_mbr_item( ls_mbr[i], ITEM_KIND_LIGHT, &sub_kind,
				TRUE, FALSE, TRUE );
	}

	/* weapon */

	i = 0;
	sub_kind.wpn = WPN_KIND_SHORT_SWORD;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 1;
	sub_kind.wpn = WPN_KIND_SHORT_SWORD;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 2;
	sub_kind.wpn = WPN_KIND_KNIFE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, TRUE, TRUE );

	i = 3;
	sub_kind.wpn = WPN_KIND_LIGHT_MACE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 4;
	sub_kind.wpn = WPN_KIND_KNIFE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 5;
	sub_kind.wpn = WPN_KIND_WOODEN_CLUB;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 6;
	sub_kind.wpn = WPN_KIND_QUARTER_STAFF;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 7;
	sub_kind.wpn = WPN_KIND_KNIFE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	/* bow */

	i = 2;
	sub_kind.wpn = WPN_KIND_SHORT_BOW;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 2;
	sub_kind.wpn = WPN_KIND_ARW;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 3;
	sub_kind.wpn = WPN_KIND_SLING;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 3;
	sub_kind.wpn = WPN_KIND_STONE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 4;
	sub_kind.wpn = WPN_KIND_DAGGER;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	/* armor */

	i = 0;
	sub_kind.armor = ARMOR_KIND_SOFT_LEATHER_ARMOR;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 1;
	sub_kind.armor = ARMOR_KIND_SOFT_LEATHER_ARMOR;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 2;
	sub_kind.armor = ARMOR_KIND_SOFT_LEATHER_ARMOR;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 3;
	sub_kind.armor = ARMOR_KIND_SOFT_LEATHER_ARMOR;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 4;
	sub_kind.armor = ARMOR_KIND_SOFT_LEATHER_ARMOR;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 5;
	sub_kind.armor = ARMOR_KIND_ROBE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 6;
	sub_kind.armor = ARMOR_KIND_SOFT_LEATHER_ARMOR;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 7;
	sub_kind.armor = ARMOR_KIND_SOFT_LEATHER_ARMOR;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	/* scroll */

	i = 0;
	sub_kind.scroll = SCROLL_KIND_RECALL;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );

	/* potion */

	i = 1;
	sub_kind.potion = POTION_KIND_RUM;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			TRUE, FALSE, FALSE );

	/* stick */

	/* misc */

	i = 4;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SPIKE, NULL,
			TRUE, FALSE, FALSE );
}

/**/

void	init_party_debug( void )
{
	race_t	race;
	item_t	*item;
	item_kind_dat_t	sub_kind;
	long	i;

	i = 0;
	race.main = MAIN_RACE_HUMAN;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_HUMAN, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "<///BLADE//}===o", 'B', race,
			MALE, CLASS_N_NINJA, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-01.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	i = 1;
	race.main = MAIN_RACE_DWARF;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_DWARF, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], ")(==DRANK======>", 'D', race,
			MALE, CLASS_N_FIGHTER, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-02.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	i = 2;
	race.main = MAIN_RACE_HALF_ELF;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_HALF_ELF, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "<---ELSIE----<<<", 'E', race,
			MALE, CLASS_N_HUNTER, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-03.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_HALFBACK;

	i = 3;
	race.main = MAIN_RACE_HUMAN;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_HUMAN, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "+-==CECILE=====X", 'C', race,
			FEMALE, CLASS_N_PRIEST, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-04.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	i = 4;
	race.main = MAIN_RACE_VIVID;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_VIVID, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "m-o HALLE  <<<)=", 'H', race,
			MALE, CLASS_N_THIEF, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-05.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_BACK;

	i = 5;
	race.main = MAIN_RACE_ELF;
	race.sub = SUB_RACE_NULL;
	str_nz_cpy( race.name, MSG_MAIN_RACE_ELF, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "O>==BEAUT====---", 'U', race,
			FEMALE, CLASS_N_WIZARD, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-06.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_BACK;

	i = 6;
	race.main = MAIN_RACE_HUMAN;
	race.sub = SUB_RACE_MONKEY;
	str_nz_cpy( race.name, MSG_RACE_NAME_VEGE, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "====GOKOU=======", 'G', race,
			MALE, CLASS_N_MONK, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-07.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	i = 7;
	race.main = MAIN_RACE_HUMAN;
	race.sub = SUB_RACE_CAT;
	str_nz_cpy( race.name, MSG_RACE_NAME_NEKOMIMI, RACE_NAME_MAX_BYTE );
	new_mbr( ls_mbr[i], "----EYE-------|===", 'Y', race,
			FEMALE, CLASS_N_SUMMONER, i );
	str_nz_cpy( ls_mbr[i]->graph_name, "default-08.bmp",
			FILE_NAME_MAX_LEN );
	ls_mbr[i]->position_kind = POSITION_KIND_FORWARD;

	/* 到達階 */

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		ls_mbr[i]->dun_max_lev_floor = 0;
		ls_mbr[i]->dun_max_lev_base = DUN_MAX_LEV_BASE;

		ls_mbr[i]->fx_data.friend_turn = 0;
	}

	/* item */

	for( i = 0; i < MBR_MAX_N; i++ ){
		sub_kind.armor = ARMOR_KIND_SOFT_LEATHER_ARMOR;
		init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
				TRUE, FALSE, TRUE );

		sub_kind.light = LIGHT_KIND_LANTERN;
		sub_kind.wish_level = WISH_LEVEL_NULL;
		init_mbr_item( ls_mbr[i], ITEM_KIND_LIGHT, &sub_kind,
				TRUE, FALSE, TRUE );

		sub_kind.potion = POTION_KIND_CURE_HP_MAX;
		init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
				TRUE, FALSE, FALSE );

		sub_kind.potion = POTION_KIND_OIL;
		init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
				FALSE, FALSE, FALSE );
	}

	/* weapon */

	i = 0;
	sub_kind.wpn = WPN_KIND_GREAT_SWORD;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 0;
	sub_kind.wpn = WPN_KIND_GLAIVE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 0;
	sub_kind.wpn = WPN_KIND_KATANA;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 0;
	sub_kind.wpn = WPN_KIND_WAKIZASHI;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, FALSE );
	equip_item( ls_mbr[i], item, EQUIP_KIND_SHIELD );

	i = 1;
	sub_kind.wpn = WPN_KIND_GREAT_AXE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 2;
	sub_kind.wpn = WPN_KIND_SHORT_SWORD;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, TRUE, TRUE );

	i = 3;
	sub_kind.wpn = WPN_KIND_LIGHT_MACE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 4;
	sub_kind.wpn = WPN_KIND_KNIFE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 5;
	sub_kind.wpn = WPN_KIND_WOODEN_CLUB;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 6;
	sub_kind.wpn = WPN_KIND_QUARTER_STAFF;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 0;
	sub_kind.wpn = WPN_KIND_JAVELIN;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, FALSE );
	equip_item( ls_mbr[i], item, EQUIP_KIND_ARW );

	i = 1;
	sub_kind.wpn = WPN_KIND_BOOMERANG;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 2;
	sub_kind.wpn = WPN_KIND_LIGHT_CROSS_BOW;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 2;
	sub_kind.wpn = WPN_KIND_BOLT;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 3;
	sub_kind.wpn = WPN_KIND_SLING;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 3;
	sub_kind.wpn = WPN_KIND_STONE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 4;
	sub_kind.wpn = WPN_KIND_DAGGER;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 6;
	sub_kind.wpn = WPN_KIND_BOOMERANG;
	init_mbr_item( ls_mbr[i], ITEM_KIND_WPN, &sub_kind,
			TRUE, FALSE, TRUE );

	/* armor */

	i = 1;
	sub_kind.armor = ARMOR_KIND_SALLET;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 0;
	sub_kind.armor = ARMOR_KIND_MITHRIL_CHAIN;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 1;
	sub_kind.armor = ARMOR_KIND_CHAIN_MAIL;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 2;
	sub_kind.armor = ARMOR_KIND_ROUND_SHIELD;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 2;
	sub_kind.armor = ARMOR_KIND_SPEED_BOOTS;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 3;
	sub_kind.armor = ARMOR_KIND_ROUND_SHIELD;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 5;
	sub_kind.armor = ARMOR_KIND_ROBE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	/* scroll */

	i = 0;
	sub_kind.scroll = SCROLL_KIND_TYPHOON;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 0;
	sub_kind.scroll = SCROLL_KIND_CONFLAGRATION;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 0;
	sub_kind.scroll = SCROLL_KIND_EARTHQUAKE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 0;
	sub_kind.scroll = SCROLL_KIND_THUNDERCLOUD;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 0;
	sub_kind.scroll = SCROLL_KIND_INUNDATION;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 0;
	sub_kind.scroll = SCROLL_KIND_SUBSTITUTE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 0;
	sub_kind.scroll = SCROLL_KIND_BURNING_HANDS;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 0;
	sub_kind.scroll = SCROLL_KIND_MIND_READING;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 1;
	sub_kind.scroll = SCROLL_KIND_POW_UP_WPN_HIT;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +98 );

	i = 1;
	sub_kind.scroll = SCROLL_KIND_POW_UP_WPN_CRTCL;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +98 );

	i = 1;
	sub_kind.scroll = SCROLL_KIND_POW_UP_WPN_DAM;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +98 );

	i = 1;
	sub_kind.scroll = SCROLL_KIND_POW_UP_ARMOR_DEF;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +98 );

	i = 1;
	sub_kind.scroll = SCROLL_KIND_POW_UP_ARMOR_CRTCL;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +98 );

	i = 1;
	sub_kind.scroll = SCROLL_KIND_POW_UP_ARMOR_AC;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +98 );

	i = 2;
	sub_kind.scroll = SCROLL_KIND_IDENTIFY_ITEM;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 2;
	sub_kind.scroll = SCROLL_KIND_BOOMERANG;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 4;
	sub_kind.scroll = SCROLL_KIND_TELEPORT;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 4;
	sub_kind.scroll = SCROLL_KIND_POW_UP_WPN_HIT;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 4;
	sub_kind.scroll = SCROLL_KIND_POW_UP_WPN_DAM;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 5;
	sub_kind.scroll = SCROLL_KIND_REMOVE_CURSE;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 5;
	sub_kind.scroll = SCROLL_KIND_RECALL;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 5;
	sub_kind.scroll = SCROLL_KIND_SLEEP;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SCROLL, &sub_kind,
			TRUE, FALSE, FALSE );

	/* potion */

	i = 1;
	sub_kind.potion = POTION_KIND_RESI_PHYS;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			FALSE, FALSE, FALSE );
	inc_item( item, +5 );

	i = 1;
	sub_kind.potion = POTION_KIND_STRENGTH;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 1;
	sub_kind.potion = POTION_KIND_DULLNESS;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 1;
	sub_kind.potion = POTION_KIND_POISON;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 1;
	sub_kind.potion = POTION_KIND_RUM;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +16 );

	i = 2;
	sub_kind.potion = POTION_KIND_FLY;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 3;
	sub_kind.potion = POTION_KIND_RESI_PHYS;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 3;
	sub_kind.potion = POTION_KIND_STRENGTH;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 3;
	sub_kind.potion = POTION_KIND_DULLNESS;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 3;
	sub_kind.potion = POTION_KIND_POISON;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 3;
	sub_kind.potion = POTION_KIND_FLY;
	init_mbr_item( ls_mbr[i], ITEM_KIND_POTION, &sub_kind,
			FALSE, FALSE, FALSE );

	/* stick */

	i = 5;
	sub_kind.stick.kind = STICK_KIND_WAND;
	sub_kind.stick.spell_kind = SPELL_KIND_QUICKNESS;
	init_mbr_item( ls_mbr[i], ITEM_KIND_STICK, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 5;
	sub_kind.stick.kind = STICK_KIND_WAND;
	sub_kind.stick.spell_kind = SPELL_KIND_SLOWNESS;
	init_mbr_item( ls_mbr[i], ITEM_KIND_STICK, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 5;
	sub_kind.stick.kind = STICK_KIND_ROD;
	sub_kind.stick.spell_kind = SPELL_KIND_SLOWNESS;
	init_mbr_item( ls_mbr[i], ITEM_KIND_STICK, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 5;
	sub_kind.stick.kind = STICK_KIND_WAND;
	sub_kind.stick.spell_kind = SPELL_KIND_SLEEP;
	init_mbr_item( ls_mbr[i], ITEM_KIND_STICK, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 5;
	sub_kind.stick.kind = STICK_KIND_STAFF;
	sub_kind.stick.spell_kind = SPELL_KIND_SLEEP;
	init_mbr_item( ls_mbr[i], ITEM_KIND_STICK, &sub_kind,
			TRUE, FALSE, FALSE );

	/* stick */

	i = 5;
	sub_kind.mnstr = MNSTR_KIND_A_GOLD_DRAGON;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_BONE, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +1 );

	i = 5;
	sub_kind.mnstr = MNSTR_KIND_MORMIN_TROLL;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_BONE, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +1 );

	i = 7;
	sub_kind.mnstr = MNSTR_KIND_A_GOLD_DRAGON;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_BONE, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +1 );

	i = 7;
	sub_kind.mnstr = MNSTR_KIND_WOLF;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_BONE, &sub_kind,
			TRUE, FALSE, FALSE );
	inc_item( item, +1 );

	/* misc */

	i = 0;
	sub_kind.armor = ARMOR_KIND_GAUNTLETS_OF_POW_UP_HIT;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ARMOR, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 1;
	sub_kind.ring = RING_KIND_DRAIN_HP;
	sub_kind.amulet = AMULET_KIND_NULL;
	sub_kind.necklace = NECKLACE_KIND_NULL;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ACCE, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 5;
	sub_kind.ring = RING_KIND_CURE_MP;
	sub_kind.amulet = AMULET_KIND_NULL;
	sub_kind.necklace = NECKLACE_KIND_NULL;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ACCE, &sub_kind,
			TRUE, FALSE, TRUE );

	i = 4;
	sub_kind.inst = INST_KIND_FLUTE;
	item = init_mbr_item( ls_mbr[i], ITEM_KIND_INST, &sub_kind,
			TRUE, FALSE, FALSE );
	if( item != NULL ){
		item->dat.inst.flg_limit = TRUE;
		item->dat.inst.spell_kind = SPELL_KIND_SONG_CURE_MP;
	}
	set_item_name( item );

	i = 4;
	sub_kind.anthology = ANTHOLOGY_KIND_WEAKEN_ABL;
	init_mbr_item( ls_mbr[i], ITEM_KIND_ANTHOLOGY, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 4;
	init_mbr_item( ls_mbr[i], ITEM_KIND_SPIKE, NULL,
			TRUE, FALSE, FALSE );

	i = 0;
	sub_kind.tobacco.kind = TOBACCO_KIND_CIGAR;
	sub_kind.tobacco.brand = TOBACCO_BRAND_LUMBERJACK;
	init_mbr_item( ls_mbr[i], ITEM_KIND_TOBACCO, &sub_kind,
			TRUE, FALSE, FALSE );

	i = 2;
	init_mbr_item( ls_mbr[i], ITEM_KIND_CHEST, NULL,
			TRUE, FALSE, FALSE );

	i = 4;
	sub_kind.light = LIGHT_KIND_LAMP;
	sub_kind.wish_level = WISH_LEVEL_ARMAGEDDON;
	init_mbr_item( ls_mbr[i], ITEM_KIND_LIGHT, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 4;
	sub_kind.light = LIGHT_KIND_LAMP;
	sub_kind.wish_level = WISH_LEVEL_DAEMON;
	init_mbr_item( ls_mbr[i], ITEM_KIND_LIGHT, &sub_kind,
			FALSE, FALSE, FALSE );

	i = 4;
	sub_kind.light = LIGHT_KIND_LAMP;
	sub_kind.wish_level = WISH_LEVEL_DJINNI;
	init_mbr_item( ls_mbr[i], ITEM_KIND_LIGHT, &sub_kind,
			FALSE, FALSE, FALSE );

	/**/

	if( FLG_NICOTINE_TEST ){
		i = 0;
		ls_mbr[i]->fx_data.nicotine.poisoning_rate = _100_PERCENT;
		ls_mbr[i]->fx_data.nicotine.lost_rate = _100_PERCENT;
	}
}

/**/

item_t	*init_mbr_item(
	mbr_t *mbr, item_kind_t kind, item_kind_dat_t *sub_kind,
	bool_t flg_ident, bool_t curse, bool_t flg_eq
)
{
	long	lev;
	long	tab_n;
	item_t	*item;

	if( mbr == NULL )
		return NULL;
	if( !is_mbr( mbr ) )
		return NULL;

	lev = -10;

	switch( kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		break;
	case ITEM_KIND_WPN:
	case ITEM_KIND_ARMOR:
	case ITEM_KIND_POTION:
	case ITEM_KIND_SCROLL:
	case ITEM_KIND_STICK:
	case ITEM_KIND_ACCE:
	case ITEM_KIND_INST:
	case ITEM_KIND_ANTHOLOGY:
	case ITEM_KIND_LIGHT:
	case ITEM_KIND_FOOD:
	case ITEM_KIND_TOBACCO:
	case ITEM_KIND_PIPE:
	case ITEM_KIND_RARE_GOODS:
	case ITEM_KIND_BONE:
	case ITEM_KIND_COIN:
		if( sub_kind == NULL )
			return NULL;
		break;
	case ITEM_KIND_SPIKE:
	case ITEM_KIND_CHEST:
	case ITEM_KIND_DISPOSAL:
	case ITEM_KIND_JUNK:
		break;
	}

	/**/

	tab_n = 0;	/* -1 ではない */

	switch( kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		return NULL;
	case ITEM_KIND_WPN:
		tab_n = get_wpn_tab_n( get_wpn_tab(
				sub_kind->wpn ) );
		break;
	case ITEM_KIND_ARMOR:
		tab_n = get_armor_tab_n( get_armor_tab(
				sub_kind->armor ) );
		break;
	case ITEM_KIND_POTION:
		tab_n = get_potion_tab_n( get_potion_tab(
				sub_kind->potion ) );
		break;
	case ITEM_KIND_SCROLL:
		tab_n = get_scroll_tab_n( get_scroll_tab(
				sub_kind->scroll ) );
		break;
	case ITEM_KIND_STICK:
		tab_n = get_stick_tab_n( get_stick_tab(
				sub_kind->stick.kind,
				sub_kind->stick.spell_kind ) );
		break;
	case ITEM_KIND_ACCE:
		tab_n = get_acce_tab_n( get_acce_tab(
				sub_kind->ring,
				sub_kind->amulet,
				sub_kind->necklace ) );
		break;
	case ITEM_KIND_INST:
		tab_n = get_inst_tab_n( get_inst_tab(
				sub_kind->inst ) );
		break;
	case ITEM_KIND_ANTHOLOGY:
		tab_n = get_anthology_tab_n( get_anthology_tab(
				sub_kind->anthology ) );
		break;
	case ITEM_KIND_LIGHT:
		tab_n = get_light_tab_n( get_light_tab(
				sub_kind->light,
				sub_kind->wish_level ) );
		break;
	case ITEM_KIND_SPIKE:
		break;
	case ITEM_KIND_FOOD:
		tab_n = get_food_tab_n( get_food_tab(
				sub_kind->food ) );
		break;
	case ITEM_KIND_CHEST:
		break;
	case ITEM_KIND_TOBACCO:
		tab_n = get_tobacco_tab_n( get_tobacco_tab(
				sub_kind->tobacco.kind,
				sub_kind->tobacco.brand ) );
		break;
	case ITEM_KIND_PIPE:
		tab_n = get_pipe_tab_n( get_pipe_tab(
				sub_kind->pipe ) );
		break;
	case ITEM_KIND_DISPOSAL:
		break;
	case ITEM_KIND_RARE_GOODS:
		tab_n = get_rare_goods_tab_n( get_rare_goods_tab(
				sub_kind->rare_goods ) );
		break;
	case ITEM_KIND_BONE:
		break;
	case ITEM_KIND_COIN:
		tab_n = get_coin_tab_n( get_coin_tab(
				sub_kind->coin ) );
		break;
	case ITEM_KIND_JUNK:
		break;
	}

	if( tab_n < 0 )
		return NULL;

	/**/

	item = NULL;

	switch( kind ){
	case ITEM_KIND_NULL:
	case ITEM_KIND_MAX_N:
		return NULL;
	case ITEM_KIND_WPN:
		item = make_item_wpn( lev, tab_n, curse );
		break;
	case ITEM_KIND_ARMOR:
		item = make_item_armor( lev, tab_n, curse );
		break;
	case ITEM_KIND_POTION:
		item = make_item_potion( lev, tab_n );
		break;
	case ITEM_KIND_SCROLL:
		item = make_item_scroll( lev, tab_n );
		break;
	case ITEM_KIND_STICK:
		item = make_item_stick( lev, tab_n );
		break;
	case ITEM_KIND_ACCE:
		item = make_item_acce( lev, tab_n );
		break;
	case ITEM_KIND_INST:
		item = make_item_inst( lev, tab_n, curse );
		break;
	case ITEM_KIND_ANTHOLOGY:
		item = make_item_anthology( lev, tab_n );
		break;
	case ITEM_KIND_LIGHT:
		item = make_item_light( lev, tab_n );
		break;
	case ITEM_KIND_SPIKE:
		item = make_item_spike( lev );
		break;
	case ITEM_KIND_FOOD:
		item = make_item_food( lev, tab_n );
		break;
	case ITEM_KIND_CHEST:
		item = make_item_chest( lev, 4, TRUE );
		break;
	case ITEM_KIND_TOBACCO:
		item = make_item_tobacco( lev, tab_n );
		break;
	case ITEM_KIND_PIPE:
		item = make_item_pipe( lev, tab_n );
		break;
	case ITEM_KIND_DISPOSAL:
		item = make_item_disposal( lev );
		break;
	case ITEM_KIND_RARE_GOODS:
		item = make_item_rare_goods( lev, tab_n );
		break;
	case ITEM_KIND_BONE:
		item = make_item_bone( lev,
				get_mnstr_tab( sub_kind->mnstr, lev ) );
		break;
	case ITEM_KIND_COIN:
		item = make_item_coin( lev, tab_n );
		break;
	case ITEM_KIND_JUNK:
		item = make_item_junk( lev );
		break;
	}

	if( item == NULL )
		return NULL;

	/**/

	item->flg |= FLG_ITEM_DETECTED;
	if( flg_ident )
		item->flg |= FLG_ITEM_IDENTIFIED;
	set_item_name( item );

	if( !give_mbr_item( mbr, item, FALSE ) ){
		del_item( item );
		return NULL;
	}

	if( flg_eq )
		equip_item_sel( mbr, item );

	return item;
}

/**/

void	init_mbr_formation( void )
{
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		if( !chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			join_mbr( i, i );
}

/**/

void	new_mbr_reset( mbr_t *mbr )
{
	new_mbr( mbr, mbr->name, mbr->face.mnr, mbr->race, mbr->sex.cur,
			mbr->class_n, mbr->ls_mbr_n );
}

/**/

void	new_mbr(
	mbr_t *mbr, char *name, char face,
	race_t race, sex_t sex, long class_n, long ls_mbr_n
)
{
	long	lev;
	long	i;

	reset_modifier( &(mbr->modifier_equip) );
	reset_modifier( &(mbr->modifier_fx) );

	mbr->prev = NULL;
	mbr->next = NULL;
	mbr->sort_chr_next = NULL;

	mbr->kind = CHR_KIND_MBR;
	str_nz_cpy( mbr->name, name, MBR_NAME_MAX_BYTE );
	mbr->mbr_n = MBR_N_NOT_JOIN;
	mbr->ls_mbr_n = ls_mbr_n;
	mbr->position_kind = POSITION_KIND_FORWARD;
	mbr->face.mjr = FACE_MJR_MBR;
	mbr->face.mnr = face;
	mbr->face.mjr_org = FACE_MJR_MBR;
	mbr->face.mnr_org = face;
	mbr->race = race;
	mbr->sex.cur = sex;
	mbr->sex.org = sex;
	mbr->x = MAP_DEL_X;
	mbr->y = MAP_DEL_Y;
	mbr->pre_x = MAP_DEL_X;
	mbr->pre_y = MAP_DEL_Y;
	mbr->pre_turn_x = MAP_DEL_X;
	mbr->pre_turn_y = MAP_DEL_Y;
	mbr->pre_draw_x = MAP_DEL_X;
	mbr->pre_draw_y = MAP_DEL_Y;
	mbr->dx = 1;
	mbr->dy = 1;
	mbr->chr_dir_idx = CHR_DIR_IDX_NULL;

	mbr->move.speed.rate = _100_PERCENT;
	mbr->move.speed.rate_org = _100_PERCENT;
	mbr->move.speed.n = 0;
	mbr->move.force_kind = MOVE_KIND_NULL;
	for( i = 0; i < MOVE_LS_KIND_MAX_N; i++ ){
		long	j;

		j = 0;
		mbr->move.ls[i][j].kind = MOVE_KIND_STD;
		mbr->move.ls[i][j].ratio = 10;
		j++;
		mbr->move.ls[i][j].kind = MOVE_KIND_NULL;
		mbr->move.ls[i][j].ratio = 0;
		j++;
	}

	mbr->gold = DFLT_GOLD;
	mbr->dun_max_lev_floor = 0;
	mbr->dun_max_lev_base = 0;

	mbr->trgt.dist = DIST_NEAR;
	mbr->trgt.dflt_dist_mnstr = DIST_NEAR;
	mbr->act.dflt_kind_mnstr = ACT_KIND_MNSTR_FIGHT;
	str_nz_cpy( mbr->act.dflt_msg_mnstr,
			MSG_MENU_MARK_FIGHT, ACT_MSG_MAX_BYTE );
	clr_chr_trgt_act( mbr, TRUE );
	mbr->pre_act = mbr->act;

	mbr->flg_chr |= (FLG_CHR_AUTO_DOOR | FLG_CHR_AVOID_TRAP);
	mbr->flg_map |= FLG_MAP_CHR_FIND;
	mbr->attitude = ATTITUDE_MATE;
	mbr->owner = NULL;
	mbr->stat = FLG_NULL;

	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		lev = abl_init[mbr->race.main][i];

		mbr->abl.lev[i].max = lev;
		mbr->abl.exp[i].max = calc_lev_to_exp(
				lev, (abl_kind_t)i );

		mbr->abl.lev[i].n = mbr->abl.lev[i].max;
		mbr->abl.lev[i].add = 0;
		mbr->abl.exp[i].n = mbr->abl.exp[i].max;
	}
	for( ; i < ABL_SKILL_MAX_N; i++ ){
		lev = 0;

		mbr->abl.lev[i].max = lev;
		mbr->abl.exp[i].max = calc_lev_to_exp(
				lev, (abl_kind_t)i );

		mbr->abl.lev[i].n = mbr->abl.lev[i].max;
		mbr->abl.lev[i].add = 0;
		mbr->abl.exp[i].n = mbr->abl.exp[i].max;
	}
	mbr->abl.hp.max = calc_max_hp( mbr );
	mbr->abl.mp.max = calc_max_mp( mbr );
	mbr->abl.hp.n = mbr->abl.hp.max;
	mbr->abl.mp.n = mbr->abl.mp.max;

	mbr->class_n = class_n;

	for( i = 0; i < RESI_KIND_MAX_N; i++ ){
		mbr->resi[i].n = resi_init[mbr->race.main][i];
		mbr->resi[i].max = resi_init[mbr->race.main][i];
		mbr->resi[i].add_n = 0;
	}
	mbr->add_def = 0;
	mbr->add_crtcl = 0;
	mbr->add_ac = 0;

	mbr->fx.next = &(mbr->fx);
	mbr->fx.prev = &(mbr->fx);

	mbr->fx_data.wpn_hit = (rate_t)0;
	mbr->fx_data.wpn_crtcl = (rate_t)0;
	mbr->fx_data.wpn_dam = (rate_t)0;

	mbr->fx_data.armor_def = (rate_t)0;
	mbr->fx_data.armor_crtcl = (rate_t)0;
	mbr->fx_data.armor_ac = (rate_t)0;

	mbr->fx_data.cure_hp.turn = 0;
	mbr->fx_data.cure_hp.rate = 0;
	mbr->fx_data.cure_hp.n = 0;

	mbr->fx_data.cure_mp.turn = 0;
	mbr->fx_data.cure_mp.rate = 0;
	mbr->fx_data.cure_mp.n = 0;

	mbr->fx_data.infra_vision = 0;

	mbr->fx_data.stomach.rate = _100_PERCENT;
	mbr->fx_data.stomach.full_rate
			= ave_stomach[race.main].full_rate;
	mbr->fx_data.stomach.digest_p_day
			= ave_stomach[race.main].digest_p_day;
	mbr->fx_data.stomach.digest_n
			= ave_stomach[race.main].digest_n;
	mbr->fx_data.stomach.hungry_rate
			= ave_stomach[race.main].hungry_rate;
	mbr->fx_data.stomach.starvation_rate
			= ave_stomach[race.main].starvation_rate;

	mbr->fx_data.drunk_rate = 0;

	mbr->fx_data.nicotine.rate = 0;
	mbr->fx_data.nicotine.poisoning_rate = 0;

	mbr->fx_data.friend_turn = FRIEND_MAX_TURN;

	mbr->fx_data.bless = 0;

	mbr->contribution = 0;

	mbr->mnstr_kind = MNSTR_KIND_NULL;
	mbr->mnstr_tab = NULL;

	mbr->work.flg = FLG_NULL;
	mbr->work.hyper_boss = HYPER_BOSS_NULL;
	mbr->work.flg_hyper_boss = FALSE;
	mbr->work.caught = 0;
	mbr->work.catch_chr = NULL;
	mbr->work.link_chr = NULL;
	mbr->work.teleport_n = 0;
	mbr->work.teleport_party_n = 0;
	mbr->work.flg_can_wish = TRUE;
	mbr->work.request = NULL;
	mbr->work.towner_dx = 0;
	mbr->work.towner_dy = 0;
	mbr->work.enter_door = NULL;
	mbr->work.dismissal_turn = 0;
	mbr->work.flg_used_energy_drain = FALSE;
	mbr->work.sync_vfx_num = 0;
	mbr->work.sync_vfx_x = MAP_DEL_X;
	mbr->work.sync_vfx_y = MAP_DEL_Y;

	str_nz_cpy( mbr->graph_name, DFLT_GRAPH_NAME, FILE_NAME_MAX_LEN );

	set_chr_id( mbr, get_ls_mbr(), LS_MBR_MAX_N );

	/**/

	init_spell_new_mbr( mbr->ls_mbr_n );

	init_auto_mark_new_mbr( mbr->ls_mbr_n );

	exp_chr( mbr, DFLT_EXP, TRUE, FALSE, FALSE );
}

/**/

bool_t	reset_mbr_resi( mbr_t *mbr )
{
	long	k;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	for( k = 0; k < RESI_KIND_MAX_N; k++ )
		mbr->resi[k].max = resi_init[mbr->race.main][k];

	return TRUE;
}

/**/

void	reset_mbr_dir( void )
{
	square_t	*sq;
	long	i, j;

	sq = &(party.square);

	switch( sq->dir ){
	case SQUARE_DIR_NORTH:
		sq->chr_dir[0][0] = sq->chr_pos_n[0][0];
		sq->chr_dir[0][1] = sq->chr_pos_n[0][1];
		sq->chr_dir[0][2] = sq->chr_pos_n[0][2];
		sq->chr_dir[1][0] = sq->chr_pos_n[1][0];
		sq->chr_dir[1][1] = sq->chr_pos_n[1][1];
		sq->chr_dir[1][2] = sq->chr_pos_n[1][2];
		sq->chr_dir[2][0] = sq->chr_pos_n[2][0];
		sq->chr_dir[2][1] = sq->chr_pos_n[2][1];
		sq->chr_dir[2][2] = sq->chr_pos_n[2][2];
		break;
	case SQUARE_DIR_EAST:
		sq->chr_dir[0][0] = sq->chr_pos_n[2][0];
		sq->chr_dir[0][1] = sq->chr_pos_n[1][0];
		sq->chr_dir[0][2] = sq->chr_pos_n[0][0];
		sq->chr_dir[1][0] = sq->chr_pos_n[2][1];
		sq->chr_dir[1][1] = sq->chr_pos_n[1][1];
		sq->chr_dir[1][2] = sq->chr_pos_n[0][1];
		sq->chr_dir[2][0] = sq->chr_pos_n[2][2];
		sq->chr_dir[2][1] = sq->chr_pos_n[1][2];
		sq->chr_dir[2][2] = sq->chr_pos_n[0][2];
		break;
	case SQUARE_DIR_SOUTH:
		sq->chr_dir[0][0] = sq->chr_pos_n[2][2];
		sq->chr_dir[0][1] = sq->chr_pos_n[2][1];
		sq->chr_dir[0][2] = sq->chr_pos_n[2][0];
		sq->chr_dir[1][0] = sq->chr_pos_n[1][2];
		sq->chr_dir[1][1] = sq->chr_pos_n[1][1];
		sq->chr_dir[1][2] = sq->chr_pos_n[1][0];
		sq->chr_dir[2][0] = sq->chr_pos_n[0][2];
		sq->chr_dir[2][1] = sq->chr_pos_n[0][1];
		sq->chr_dir[2][2] = sq->chr_pos_n[0][0];
		break;
	case SQUARE_DIR_WEST:
		sq->chr_dir[0][0] = sq->chr_pos_n[0][2];
		sq->chr_dir[0][1] = sq->chr_pos_n[1][2];
		sq->chr_dir[0][2] = sq->chr_pos_n[2][2];
		sq->chr_dir[1][0] = sq->chr_pos_n[0][1];
		sq->chr_dir[1][1] = sq->chr_pos_n[1][1];
		sq->chr_dir[1][2] = sq->chr_pos_n[2][1];
		sq->chr_dir[2][0] = sq->chr_pos_n[0][0];
		sq->chr_dir[2][1] = sq->chr_pos_n[1][0];
		sq->chr_dir[2][2] = sq->chr_pos_n[2][0];
		break;
	case SQUARE_DIR_MAX_N:
		break;
	}

	for( i = 0; i < SQUARE_HEIGHT; i++ ){
		for( j = 0; j < SQUARE_WIDTH; j++ ){
			long	n;
			long	x, y;

			n = sq->chr_dir[i][j];
			if( n == MBR_NO_POS )
				continue;

			sq->chr_rel_pos[n].x = j - 1;
			sq->chr_rel_pos[n].y = i - 1;

			x = sq->x + sq->chr_rel_pos[n].x;
			y = sq->y + sq->chr_rel_pos[n].y;

			sq->chr_abs_pos[n].x = x;
			sq->chr_abs_pos[n].y = y;

			sq->chr_ind_pos[n].x = x;
			sq->chr_ind_pos[n].y = y;

			sq->chr_map_pos[n].x = x;
			sq->chr_map_pos[n].y = y;
		}
	}
}

/***************************************************************
* 各メンバーの個別のアンカー座標をリセットする
***************************************************************/

void	reset_square_mbr_ind_pos( void )
{
	long	n;

	for( n = 0; n < MBR_MAX_N; n++ ){
		party.square.chr_ind_pos[n].x
				= party.square.chr_abs_pos[n].x;
		party.square.chr_ind_pos[n].y
				= party.square.chr_abs_pos[n].y;
	}
}

/***************************************************************
* メンバーの個別のアンカー座標を設定する
***************************************************************/

void	set_square_mbr_ind_pos( long mbr_n, long x, long y )
{
	square_t	*sq;

	if( mbr_n < 0 )
		return;
	if( mbr_n >= MBR_MAX_N )
		return;

	sq = &(party.square);

	sq->chr_ind_pos[mbr_n].x = x;
	sq->chr_ind_pos[mbr_n].y = y;

	sq->chr_map_pos[mbr_n].x = x;
	sq->chr_map_pos[mbr_n].y = y;
}

/***************************************************************
* キャラクタのマップ上の絶対座標 (全体アンカー) を返す
***************************************************************/

void	get_square_mbr_abs_pos( long mbr_n, long *x, long *y )
{
	square_t	*sq;

	if( x != NULL )
		*x = 0;
	if( y != NULL )
		*y = 0;

	if( mbr_n < 0 )
		return;
	if( mbr_n >= MBR_MAX_N )
		return;

	sq = &(party.square);

	sq->chr_abs_pos[mbr_n].x = sq->x + sq->chr_rel_pos[mbr_n].x;
	sq->chr_abs_pos[mbr_n].y = sq->y + sq->chr_rel_pos[mbr_n].y;

	if( x != NULL )
		*x = sq->chr_abs_pos[mbr_n].x;
	if( y != NULL )
		*y = sq->chr_abs_pos[mbr_n].y;
}

/***************************************************************
* 各メンバーのアンカー座標を返す
***************************************************************/

void	get_square_mbr_map_pos( long mbr_n, long *x, long *y )
{
	if( x != NULL )
		*x = 0;
	if( y != NULL )
		*y = 0;

	if( mbr_n < 0 )
		return;
	if( mbr_n >= MBR_MAX_N )
		return;

	if( x != NULL )
		*x = party.square.chr_map_pos[mbr_n].x;
	if( y != NULL )
		*y = party.square.chr_map_pos[mbr_n].y;
}

/***************************************************************
* 迷宮と街を判別してメンバーをマップに出現させる
***************************************************************/

void	appear_party_auto( void )
{
	dun_t	*dun;

	dun = get_dun();

	if( dun->lev == 0 ){
		appear_party_town();
	} else {
		appear_party();
	}
}

/***************************************************************
* メンバーをマップに出現させる
***************************************************************/

void	appear_party( void )
{
	bool_t	flg_force;
	long	n;

	for( n = 0; n < MBR_MAX_N; n++ ){
		lost_trgt( party.mbr[n] );
		clr_chr_trgt_act( party.mbr[n], FALSE );
	}

	release_all_mbr();
	clr_map_all_mbr();

	flg_force = FALSE;
	do {
		if( appear_party_sub_randm() )
			break;
		if( appear_party_sub_srch() )
			break;
		appear_party_sub_force();
		flg_force = TRUE;
	} while( 0 );

	if( !flg_force )
		set_map_all_mbr();

	appear_all_pet();

	next_pos_square( 0 );
	scroll_center_appear_party();
	set_flg_find_all_mnstr();

	redraw_all();
}

/***************************************************************
* メンバーをマップに出現させる (ランダム)
* return : 成功か?
***************************************************************/

bool_t	appear_party_sub_randm( void )
{
	square_t	*sq;
	long	i, n;

	sq = get_square_mbr();
	if( sq == NULL )
		return FALSE;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		sq->x = 1 + randm( MAP_MAX_X - 2);
		sq->y = 1 + randm( MAP_MAX_Y - 2);
		sq->pre_x = sq->x;
		sq->pre_y = sq->y;

		for( n = 0; n < MBR_MAX_N; n++ ){
			long	nx, ny;

			if( chk_flg_or( party.mbr[n]->stat,
					FLG_STAT_NOT_EXIST
					| FLG_STAT_DEAD ) ){
				continue;
			}

			get_square_mbr_abs_pos( n, &nx, &ny );
			party.mbr[n]->x = nx;
			party.mbr[n]->y = ny;
			party.mbr[n]->pre_x = nx;
			party.mbr[n]->pre_y = ny;

			if( !can_move_chr( party.mbr[n], nx, ny ) ){
				/* 新しい位置に移動出来なければ */
				break;
			}
		}
		if( n >= MBR_MAX_N ){
			/* 全員移動出来たら */
			reset_mbr_dir();
			return TRUE;
		}
	}

	/* 全員移動出来なかった */
	reset_mbr_dir();
	return FALSE;
}

/***************************************************************
* メンバーをマップに出現させる (空き場所をサーチ)
* return : 成功か?
***************************************************************/

bool_t	appear_party_sub_srch( void )
{
	square_t	*sq;
	long	randm_x, randm_y;
	long	xx, yy;
	long	x, y;
	long	n;

	sq = get_square_mbr();
	if( sq == NULL )
		return FALSE;

	randm_x = randm( MAP_MAX_X );
	randm_y = randm( MAP_MAX_Y );

	for( yy = 0; yy < MAP_MAX_Y; yy++ ){
		for( xx = 0; xx < MAP_MAX_X; xx++ ){
			x = (randm_x + xx) % MAP_MAX_X;
			y = (randm_y + yy) % MAP_MAX_Y;
			if( x < 1 )
				continue;
			if( y < 1 )
				continue;
			if( x >= MAP_MAX_X - 1 )
				continue;
			if( y >= MAP_MAX_Y - 1 )
				continue;

			sq->x = x;
			sq->y = y;
			sq->pre_x = sq->x;
			sq->pre_y = sq->y;

			for( n = 0; n < MBR_MAX_N; n++ ){
				long	nx, ny;

				if( chk_flg_or( party.mbr[n]->stat,
						FLG_STAT_NOT_EXIST
						| FLG_STAT_DEAD ) ){
					continue;
				}

				get_square_mbr_abs_pos( n, &nx, &ny );
				party.mbr[n]->x = nx;
				party.mbr[n]->y = ny;
				party.mbr[n]->pre_x = nx;
				party.mbr[n]->pre_y = ny;

				if( !can_move_chr( party.mbr[n], nx, ny ) ){
					/* 新しい位置に移動出来なければ */
					break;
				}
			}
			if( n >= MBR_MAX_N ){
				/* 全員移動出来たら */
				reset_mbr_dir();
				return TRUE;
			}
		}
	}

	/* 全員移動出来なかった */
	reset_mbr_dir();
	return FALSE;
}

/***************************************************************
* メンバーをマップに出現させる (強制的)
***************************************************************/

void	appear_party_sub_force( void )
{
	long	x, y;
	long	n;

	x = 1 + randm( MAP_MAX_X - 2);
	y = 1 + randm( MAP_MAX_Y - 2);

	party.square.x = x;
	party.square.y = y;
	party.square.pre_x = party.square.x;
	party.square.pre_y = party.square.y;

	for( n = 0; n < MBR_MAX_N; n++ ){
		if( chk_flg_or( party.mbr[n]->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD ) ){
			continue;
		}

		put_chr( party.mbr[n], x, y );
	}

	reset_mbr_dir();
}

/***************************************************************
* メンバーをマップに出現させる (短距離)
* long bx : 基準 x 座標
* long by : 基準 y 座標
* return : 成功か?
***************************************************************/

bool_t	appear_party_short( long bx, long by )
{
	bool_t	flg_success;
	long	pre_x[MBR_MAX_N], pre_y[MBR_MAX_N];
	long	n;

	flg_success = FALSE;

	for( n = 0; n < MBR_MAX_N; n++ ){
		pre_x[n] = party.mbr[n]->x;
		pre_y[n] = party.mbr[n]->y;

		lost_trgt( party.mbr[n] );
		clr_chr_trgt_act( party.mbr[n], FALSE );
	}

	release_all_mbr();
	clr_map_all_mbr();

	if( appear_party_sub_area( bx, by ) ){
		flg_success = TRUE;
	} else {
		for( n = 0; n < MBR_MAX_N; n++ ){
			party.mbr[n]->x = pre_x[n];
			party.mbr[n]->y = pre_y[n];
		}
	}

	set_map_all_mbr();
	appear_all_pet();

	next_pos_square( 0 );
	scroll_center_appear_party();
	set_flg_find_all_mnstr();

	redraw_all();

	return flg_success;
}

/***************************************************************
* メンバーをマップに出現させる (同エリア)
* long bx : 基準 x 座標
* long by : 基準 y 座標
* return : 成功か?
***************************************************************/

bool_t	appear_party_sub_area( long bx, long by )
{
	long	ax, ay;
	square_t	*sq;
	long	i, n;

	sq = get_square_mbr();
	if( sq == NULL )
		return FALSE;

	ax = bx / AREA_MAX_X * AREA_MAX_X;
	ay = by / AREA_MAX_Y * AREA_MAX_Y;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		sq->x = ax + (1 + randm( AREA_MAX_X - 2));
		sq->y = ay + (1 + randm( AREA_MAX_Y - 2));
		sq->pre_x = sq->x;
		sq->pre_y = sq->y;

		for( n = 0; n < MBR_MAX_N; n++ ){
			long	nx, ny;

			if( chk_flg_or( party.mbr[n]->stat,
					FLG_STAT_NOT_EXIST
					| FLG_STAT_DEAD ) ){
				continue;
			}

			get_square_mbr_abs_pos( n, &nx, &ny );
			party.mbr[n]->x = nx;
			party.mbr[n]->y = ny;
			party.mbr[n]->pre_x = nx;
			party.mbr[n]->pre_y = ny;

			if( !can_move_chr( party.mbr[n], nx, ny ) ){
				/* 新しい位置に移動出来なければ */
				break;
			}
		}
		if( n >= MBR_MAX_N ){
			/* 全員移動出来たら */
			reset_mbr_dir();
			return TRUE;
		}
	}

	/* 全員移動出来なかった */
	reset_mbr_dir();
	return FALSE;
}

/***************************************************************
* メンバーをマップに出現させる (ラスボス)
***************************************************************/

void	appear_party_last_boss( void )
{
	appear_party_map_event( MAP_EVENT_LAST_BOSS_APPEAR_PARTY );
}

/***************************************************************
* メンバーをマップに出現させる (マップ・イベント位置)
* char mnr : マップ・イベント識別文字
***************************************************************/

void	appear_party_map_event( char mnr )
{
	square_t	*sq;
	pos_t	pos;
	long	x, y;
	long	n;

	sq = get_square_mbr();
	if( sq == NULL )
		return;

	for( n = 0; n < MBR_MAX_N; n++ ){
		lost_trgt( party.mbr[n] );
		clr_chr_trgt_act( party.mbr[n], FALSE );
	}

	release_all_mbr();
	clr_map_all_mbr();

	pos = get_map_event_pos( mnr );
	x = pos.x;
	y = pos.y;

	sq->x = x;
	sq->y = y;
	sq->pre_x = sq->x;
	sq->pre_y = sq->y;

	for( n = 0; n < MBR_MAX_N; n++ ){
		long	nx, ny;

		if( chk_flg_or( party.mbr[n]->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD ) ){
			continue;
		}

		get_square_mbr_abs_pos( n, &nx, &ny );

		party.mbr[n]->x = MAP_DEL_X;
		party.mbr[n]->y = MAP_DEL_Y;

		put_chr( party.mbr[n], nx, ny );
	}

	reset_mbr_dir();
	appear_all_pet();

	next_pos_square( 0 );
	scroll_center_appear_party();
	set_flg_find_all_mnstr();

	redraw_all();
}

/***************************************************************
* メンバーが降りた一番深い階数を数える
* return : 一番深い階数
***************************************************************/

long	get_party_dun_max_lev( void )
{
	party_t	*pty = get_party();
	long	max_lev;
	long	i;

	max_lev = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		long	lev;

		lev = labs( pty->mbr[i]->dun_max_lev_base );
		if( max_lev < lev )
			max_lev = lev;
	}

	return max_lev;
}

/**/

void	scroll_center_appear_party( void )
{
	pos_t	*draw;
	pos_t	*draw_gui;

	if( chk_flg_or( get_flg_scroll(),
			(FLG_SCROLL_CENTER | FLG_SCROLL_SMOOTH) ) ){
		scroll_center();
	} else {
		scroll_half_page();
	}

	draw = get_map_draw_pos();
	draw_gui = get_map_draw_pos_gui();
	if( (draw != NULL) && (draw_gui != NULL) ){
		draw_gui->x = draw->x;
		draw_gui->y = draw->y;
		call_pcg_dun_scroll( draw_gui->x, draw_gui->y );
	}
}

/**/

void	clr_map_all_mbr( void )
{
	long	n;

	for( n = 0; n < MBR_MAX_N; n++ )
		clr_map_chr( party.mbr[n] );
}

/**/

void	set_map_all_mbr( void )
{
	long	n;

	for( n = 0; n < MBR_MAX_N; n++ )
		set_map_chr( party.mbr[n] );
}

/**/

void	move_all_mbr_trgt( void )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		move_chr_trgt( pty->mbr[i] );
	}
}

/**/

void	move_phase_all_mbr( void )
{
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		move_phase_chr( party.mbr[i] );
}

/**/

void	act_phase_all_mbr( void )
{
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		act_phase_chr( party.mbr[i] );
		set_modifier( party.mbr[i] );
	}
}

/**/

void	act_phase_party( void )
{
	switch( party.act.kind ){
	default:
		break;
	case ACT_KIND_SHOP:
		enter_shop();
		break;
	case ACT_KIND_TELEPORT_PARTY:
		chk_teleport_party();
		break;
	case ACT_KIND_RECALL:
		chk_recall();
		break;
	}
}

/**/

bool_t	chk_party_no_mbr( bool_t flg_enter_bar )
{
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( !chk_flg( party.mbr[i]->stat,
				FLG_STAT_NOT_EXIST ) ){
			return TRUE;
		}
	}

	if( flg_enter_bar ){
		up_dun_town();
		party_enter_bar();
	}

	return FALSE;
}

/**/

void	chk_trap_party( void )
{
	long	i;
	mbr_t	*thief;

	thief = NULL;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( party.mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( thief == NULL ){
			thief = party.mbr[i];
		} else {
			long	thief_lev, mbr_lev;

			thief_lev = get_lev( thief, ABL_KIND_THI );
			thief_lev += get_lev( thief, ABL_KIND_AGI );
			mbr_lev = get_lev( party.mbr[i], ABL_KIND_THI );
			mbr_lev += get_lev( party.mbr[i], ABL_KIND_AGI );

			if( thief_lev < mbr_lev )
				thief = party.mbr[i];
		}
	}

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( party.mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		chk_trap( party.mbr[i], thief );
	}
}

/**/

bool_t	chk_auto_mnstr( mbr_t *mbr, long x1, long y1, long x2, long y2 )
{
	dun_t	*dun = get_dun();

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	if( !chk_flg( mbr->flg_chr, FLG_CHR_AUTO_FIGHT ) )
		return FALSE;

	if( dun->map.chr.mjr[y1][x1] != FACE_MJR_NULL ){
		if( dun->map.chr.mjr[y1][x1] != FACE_MJR_MBR ){
			if( set_mbr_act_auto_mnstr( mbr, x1, y1 ) )
				return TRUE;
		}
	}

	if( dun->map.chr.mjr[y2][x2] != FACE_MJR_NULL ){
		if( dun->map.chr.mjr[y2][x2] != FACE_MJR_MBR ){
			if( set_mbr_act_auto_mnstr( mbr, x2, y2 ) )
				return TRUE;
		}
	}

	return FALSE;
}

/**/

bool_t	chk_auto_door_mbr( mbr_t *mbr, long x1, long y1, long x2, long y2 )
{
	if( chk_auto_door_mbr_sub( mbr, x1, y1 ) )
		return TRUE;
	if( chk_auto_door_mbr_sub( mbr, x2, y2 ) )
		return TRUE;

	return FALSE;
}

/**/

bool_t	chk_auto_door_mbr_sub( mbr_t *mbr, long x, long y )
{
	dun_t	*dun = get_dun();

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	if( !chk_flg( mbr->flg_chr, FLG_CHR_AUTO_DOOR ) )
		return FALSE;
	if( !clip_pos( x, y ) )
		return FALSE;
	if( dun->map.obj.mjr[y][x] != FACE_MJR_DOOR_CLOSE )
		return FALSE;
	if( chk_flg( dun->map.obj.flg[y][x], FLG_MAP_OBJ_LOOK_WALL ) )
		return FALSE;

	act_chr_auto_door( mbr, x, y );
	return TRUE;
}

/**/

void	die_mbr( mbr_t *mbr, bool_t flg_msg, bool_t flg_chk_game_over )
{
	long	i;

	if( mbr == NULL )
		return;
	if( !is_mbr( mbr ) )
		return;

	if( flg_msg )
		call_game_sound_play( SOUND_KIND_FIGHT_DIE_MEMBER, 1 );

	if( !flg_chk_game_over )
		return;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( party.mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		break;
	}
	if( i >= MBR_MAX_N )
		game_over();
}

/**/

bool_t	chk_can_act_mbr( mbr_t *p )
{
	if( p == NULL )
		return FALSE;

	if( chk_flg_or( p->stat,
			FLG_STAT_NOT_EXIST | FLG_STAT_DEAD
			| FLG_STAT_STONE | FLG_STAT_PARALYZE
			| FLG_STAT_SLEEP | FLG_STAT_FAINT
			| FLG_STAT_IRON_BODY
			) ){
		return FALSE;
	}

	return TRUE;
}

/**/

bool_t	set_mbr_act_auto_mnstr( mbr_t *mbr, long x, long y )
{
	mnstr_t	*mnstr;

	if( mbr == NULL )
		return FALSE;

	mnstr = get_mnstr( x, y );
	if( mnstr == NULL )
		return FALSE;

	if( mnstr->attitude != ATTITUDE_ENEMY )
		return FALSE;

	mark_mnstr( mbr, mnstr, DIST_NEAR );
	set_chr_act( mbr, ACT_KIND_MNSTR_FIGHT, NULL, NULL, 0, 0 );

	return TRUE;
}

/**/

void	mbr_peep_door( mbr_t *mbr, long dr_n )
{
	dun_t	*dun;
	long	dx, dy;

	if( mbr == NULL )
		return;

	dun = get_dun();

	if( chk_flg( dun->door[dr_n].flg, FLG_DOOR_OPEN ) )
		return;

	for( dy = 0; dy < dun->door[dr_n].dy; dy++ ){
		for( dx = 0; dx < dun->door[dr_n].dx; dx++ ){
			long	x, y;

			x = dun->door[dr_n].x + dx;
			y = dun->door[dr_n].y + dy;
			dun->map.obj.flg[y][x] |= FLG_MAP_OBJ_LOOK;
		}
	}

	/**/

	set_flg_find_all_mnstr();
	draw_all_mnstr();

	wait_key_ex( TRUE, TRUE );

	/**/

	for( dy = 0; dy < dun->door[dr_n].dy; dy++ ){
		for( dx = 0; dx < dun->door[dr_n].dx; dx++ ){
			long	x, y;

			x = dun->door[dr_n].x + dx;
			y = dun->door[dr_n].y + dy;
			dun->map.obj.flg[y][x] &= ~(FLG_MAP_OBJ_LOOK);
		}
	}

	set_flg_find_all_mnstr();
	redraw_map();
}

/**/

void	clr_party_act( void )
{
	party.act.kind = ACT_KIND_NULL;
	str_nz_cpy( party.act.msg, "", ACT_MSG_MAX_BYTE );

	draw_misc_stat();
}

/**/

void	join_mbr( long ls_mbr_n, long mbr_n )
{
	long	x, y;

	if( mbr_n == MBR_N_NOT_JOIN )
		return;

	party.mbr[mbr_n] = ls_mbr[ls_mbr_n];
	ls_mbr[ls_mbr_n]->mbr_n = mbr_n;

	get_square_mbr_map_pos( mbr_n, &x, &y );
	put_chr( party.mbr[mbr_n], x, y );
}

/**/

void	not_join_mbr( long ls_mbr_n, long mbr_n )
{
	if( mbr_n == MBR_N_NOT_JOIN )
		return;

	clr_map_chr( party.mbr[mbr_n] );
	draw_chr( party.mbr[mbr_n] );

	party.mbr[mbr_n]->x = MAP_DEL_X;
	party.mbr[mbr_n]->y = MAP_DEL_Y;

	ls_mbr[ls_mbr_n]->mbr_n = MBR_N_NOT_JOIN;
	party.mbr[mbr_n] = ls_mbr[LS_MBR_NULL];
}

/**/

void	collect_gold( mbr_t *mbr )
{
	gold_t	gold;
	long	i;

	if( mbr == NULL )
		return;

	/* ペットや NPC は拒否 */

	if( !is_mbr( mbr ) ){
		print_msg( FLG_NULL, MSG_NOT_FRIEND_GOLD, mbr->name );
		return;
	}

	/* GOLD のやり取りを拒否 */

	if( mbr->fx_data.friend_turn > 0 ){
		print_msg( FLG_NULL, MSG_NOT_FRIEND_GOLD, mbr->name );
		return;
	}

	gold = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		/* GOLD のやり取りを拒否 */

		if( party.mbr[i]->fx_data.friend_turn > 0 ){
			print_msg( FLG_NULL, MSG_NOT_FRIEND_GOLD,
					party.mbr[i]->name );
			continue;
		}

		gold += get_chr_gold( party.mbr[i] );
		add_chr_gold( party.mbr[i], - party.mbr[i]->gold );
	}

	add_chr_gold( mbr, gold );

	print_msg( FLG_NULL, MSG_COLLECT_GOLD, mbr->name, fmt_gold( gold ) );
}

/**/

void	divide_gold( void )
{
	gold_t	sum, gold;
	long	i, n, mod_n;

	mod_n = 0;
	n = 0;
	sum = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		/* GOLD のやり取りを拒否 */

		if( party.mbr[i]->fx_data.friend_turn > 0 ){
			print_msg( FLG_NULL, MSG_NOT_FRIEND_GOLD,
					party.mbr[i]->name );
			continue;
		}

		sum += get_chr_gold( party.mbr[i] );
		add_chr_gold( party.mbr[i], - party.mbr[i]->gold );
		n++;
		if( per_randm( n ) )
			mod_n = i;
	}
	if( n <= 0 )
		return;

	gold = sum / n;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;
		if( party.mbr[i]->fx_data.friend_turn > 0 )
			continue;

		add_chr_gold( party.mbr[i], gold );
		sum -= gold;
	}

	add_chr_gold( party.mbr[mod_n], sum );

	print_msg( FLG_NULL, MSG_DIVIDE_GOLD, fmt_gold( gold ) );
}

/**/

void	give_gold( mbr_t *mbr_from, mbr_t *mbr_to, gold_t gold )
{
	bool_t	flg_force;
	gold_t	res_price, inn_price, max;

	if( mbr_from == NULL )
		return;
	if( mbr_to == NULL )
		return;

	flg_force = FALSE;

	/* 復活用の GOLD は拒否出来ない */

	res_price = get_price_temple_resurrection( mbr_to );
	if( (get_chr_gold( mbr_to ) + gold <= res_price)
			&& chk_flg( mbr_to->stat, FLG_STAT_DEAD ) ){
		flg_force = TRUE;
	}

	/* 宿代くらいの GOLD は拒否しない */

	inn_price = get_price_inn( FALSE );
	if( get_chr_gold( mbr_to ) + gold <= inn_price )
		flg_force = TRUE;

	/* 仲が良いかチェック */

	do {
		if( !flg_force ){
			if( mbr_from->fx_data.friend_turn > 0 )
				break;
			if( mbr_to->fx_data.friend_turn > 0 )
				break;
			if( is_pet( mbr_from ) )
				break;
			if( !is_mbr( mbr_to ) )
				break;
		}

		max = GOLD_MAX - get_chr_gold( mbr_to );
		if( gold > max )
			gold = max;

		add_chr_gold( mbr_from, -gold );
		add_chr_gold( mbr_to, +gold );

		print_msg( FLG_NULL, MSG_GIVE_GOLD,
				mbr_from->name, fmt_gold( gold ),
				mbr_to->name );

		return;
	} while( 0 );

	/* GOLD のやり取りを拒否 */

	print_msg( FLG_NULL, MSG_NOT_FRIEND_GOLD, mbr_to->name );
}

/**/

gold_t	get_party_gold( void )
{
	gold_t	gold;
	long	i;

	gold = 0;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		gold += get_chr_gold( party.mbr[i] );
	}

	return gold;
}

/**/

void	add_party_gold( gold_t gold )
{
	gold_t	div_gold;
	long	i, n, mod_n;

	if( gold < 0 ){
		sub_party_gold( -gold );
		return;
	}

	mod_n = 0;
	n = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		n++;
		if( per_randm( n ) )
			mod_n = i;
	}
	if( n <= 0 )
		return;

	curs_attrset_chr( party.mbr[mod_n], +1, FALSE );
	print_msg( FLG_NULL, MSG_ADD_PARTY_GOLD, fmt_gold( gold ) );
	curs_attrset_dflt();

	div_gold = gold / n;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		add_chr_gold( party.mbr[i], div_gold );
		gold -= div_gold;
	}

	party.mbr[mod_n]->gold += gold;
}

/**/

gold_t	sub_party_gold( gold_t gold )
{
	gold_t	div_gold, sub_gold;
	long	i, n;

	if( gold < 0 ){
		add_party_gold( -gold );
		return (gold_t)0;
	}

	n = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		n++;
	}
	if( n <= 0 )
		return gold;

	curs_attrset_chr( get_mbr_randm( MAP_DEL_X, MAP_DEL_Y ),
			-1, FALSE );
	print_msg( FLG_NULL, MSG_SUB_PARTY_GOLD, fmt_gold( gold ) );
	curs_attrset_dflt();

	div_gold = gold / n;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		/* 割り勘 (div_gold) */
		sub_gold = min_l( get_chr_gold( party.mbr[i] ),
				div_gold );

		add_chr_gold( party.mbr[i], -sub_gold );
		gold -= sub_gold;
	}

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		/* 先頭から減らせるだけ減らす (gold) */
		sub_gold = min_l( get_chr_gold( party.mbr[i] ),
				gold );

		add_chr_gold( party.mbr[i], -sub_gold );
		gold -= sub_gold;
	}

	return gold;
}

/**/

void	exp_party( long exp, bool_t flg_set_max, bool_t flg_draw )
{
	party_t	*pty = get_party();
	pet_t	**pet = get_party_pet();
	long	i, n, mod_n;
	flg_stat_t	flg;
	long	exp_add, exp_mod;

	flg = FLG_NULL;
	flg |= FLG_STAT_NOT_EXIST | FLG_STAT_DEAD | FLG_STAT_STONE;

	n = 0;
	mod_n = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( party.mbr[i]->stat, flg ) )
			continue;

		n++;
		if( per_randm( n ) )
			mod_n = i;
	}
	if( n <= 0 )
		return;

	exp_add = exp / n;
	exp_mod = exp % n;

	if( flg_draw ){
		curs_attrset_chr( get_mbr_randm( MAP_DEL_X, MAP_DEL_Y ),
				+1, FALSE );
		print_msg( FLG_NULL, MSG_EXP_PARTY, fmt_num( exp_add ) );
		curs_attrset_dflt();
	}

	/* メンバー */

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( party.mbr[i]->stat, flg ) )
			continue;

		if( mod_n == i ){
			exp_chr( pty->mbr[i], exp_add + exp_mod,
					flg_set_max,
					FALSE, TRUE );
		} else {
			exp_chr( pty->mbr[i], exp_add,
					flg_set_max,
					FALSE, TRUE );
		}
	}

	/* ペット */

	for( i = 0; i < PET_MAX_N; i++ ){
		bool_t	flg_print_lev;

		if( pet[i] == NULL )
			continue;
		if( chk_flg_or( pet[i]->stat, flg ) )
			continue;

		if( is_client( pet[i] ) )
			flg_print_lev = FALSE;
		else
			flg_print_lev = TRUE;

		exp_chr( pet[i], exp_add, flg_set_max, FALSE, flg_print_lev );
	}
}

/**/

long	get_mbr_race_exp( mbr_t *mbr, long exp, abl_kind_t abl )
{
	rate_t	rate;

	if( mbr == NULL )
		return exp;
	if( !is_mbr( mbr ) )
		return exp;

	rate = _100_PERCENT;

	switch( mbr->race.main ){
	case MAIN_RACE_HUMAN:
		break;
	case MAIN_RACE_HALF_ELF:
		if( abl == ABL_KIND_STR )
			rate -= 5;
		if( abl == ABL_KIND_CHA )
			rate += 5;
		break;
	case MAIN_RACE_ELF:
		if( abl == ABL_KIND_HP )
			rate -= 5;
		if( abl == ABL_KIND_STR )
			rate -= 5;
		if( abl == ABL_KIND_INT )
			rate += 5;
		if( abl == ABL_KIND_CHA )
			rate += 5;
		break;
	case MAIN_RACE_DWARF:
		if( abl == ABL_KIND_HP )
			rate += 5;
		if( abl == ABL_KIND_STR )
			rate += 5;
		if( abl == ABL_KIND_INT )
			rate -= 5;
		if( abl == ABL_KIND_CHA )
			rate -= 5;
		break;
	case MAIN_RACE_VIVID:
		if( abl == ABL_KIND_HP )
			rate -= 5;
		if( abl == ABL_KIND_MP )
			rate -= 5;
		if( abl == ABL_KIND_DEX )
			rate += 5;
		if( abl == ABL_KIND_AGI )
			rate += 5;
		break;
	case MAIN_RACE_MAX_N:
		break;
	}

	switch( mbr->race.sub ){
	case SUB_RACE_NULL:
		break;
	case SUB_RACE_CAT:
		if( abl == ABL_KIND_AGI )
			rate += 5;
		break;
	case SUB_RACE_DOG:
		if( abl == ABL_KIND_INT )
			rate += 5;
		break;
	case SUB_RACE_MOUSE:
		if( abl == ABL_KIND_WIS )
			rate += 5;
		break;
	case SUB_RACE_RABBIT:
		if( abl == ABL_KIND_CHA )
			rate += 5;
		break;
	case SUB_RACE_MONKEY:
		if( abl == ABL_KIND_DEX )
			rate += 5;
		break;
	case SUB_RACE_PIG:
		if( abl == ABL_KIND_HP )
			rate += 5;
		break;
	case SUB_RACE_BIRD:
		if( abl == ABL_KIND_MP )
			rate += 5;
		break;
	case SUB_RACE_LIZARD:
		if( abl == ABL_KIND_STR )
			rate += 5;
		break;
	case SUB_RACE_MAX_N:
		break;
	}

	exp = (exp * rate) / _100_PERCENT;

	return exp;
}

/**/

void	remove_mbr( mbr_t *mbr )
{
	long	mbr_n, ls_mbr_n;
	mbr_t	*p;

	if( mbr == NULL )
		return;

	/* リストをずらす */

	menu_bar_arrange( mbr, +1 );
	mbr = get_ls_mbr_tail();
	if( mbr == NULL )
		return;

	/**/

	mbr_n = mbr->mbr_n;
	ls_mbr_n = mbr->ls_mbr_n;

	/* 各データを削除 */

	remove_cast_tab( ls_mbr_n );
	remove_auto_mark_mbr( ls_mbr_n );
	remove_mbr_del_item( ls_mbr_n );

	/* mark */

	p = ls_mbr[ls_mbr_n];
	clr_map_chr( p );
	p->x = MAP_DEL_X;
	p->y = MAP_DEL_Y;
	draw_mbr( p );
	release_chr( p );
	free_fx_all( &(p->fx) );
	lost_trgt( p );
	lost_fx_chr( p );

	/* party.mbr */

	if( mbr_n != MBR_N_NOT_JOIN )
		party.mbr[mbr_n] = ls_mbr[LS_MBR_NULL];

	/* ls_mbr */

	ls_mbr[ls_mbr_n]->mbr_n = MBR_N_NOT_JOIN;
	ls_mbr[ls_mbr_n]->stat |= FLG_STAT_NOT_EXIST;
}

/**/

mbr_t	*get_mbr_nearest( long x, long y )
{
	mbr_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	long	i;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	n = 0;
	ret_p = NULL;

	for( i = 0; i < MBR_MAX_N; i++ ){
		pos_t	pos1, pos2;

		p = party.mbr[i];

		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		tmp_r = abs( p->x - x ) + abs( p->y - y );
		if( tmp_r > min_r )
			continue;

		pos1.x = p->x;
		pos1.y = p->y;
		pos2.x = x;
		pos2.y = y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( tmp_r < min_r ){
			n = 0;
			min_r = tmp_r;
		} else if( tmp_r == min_r ){
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/**/

mbr_t	*get_mbr_near( long x, long y )
{
	mbr_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	long	i;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	n = 0;
	ret_p = NULL;

	for( i = 0; i < MBR_MAX_N; i++ ){
		pos_t	pos1, pos2;

		p = party.mbr[i];

		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		tmp_r = abs( p->x - x ) + abs( p->y - y );
		if( tmp_r > min_r )
			continue;

		pos1.x = p->x;
		pos1.y = p->y;
		pos2.x = x;
		pos2.y = y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( tmp_r < min_r ){
			n = 0;
			min_r = tmp_r;
		} else if( (tmp_r - min_r) <= MBR_NEAR_R ){
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/**/

mbr_t	*get_mbr_disperse( mbr_t *mbr )
{
	mbr_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	long	x, y;
	long	i;

	if( mbr == NULL )
		return NULL;

	x = mbr->x;
	y = mbr->y;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	n = 0;
	ret_p = NULL;

	for( i = 0; i < MBR_MAX_N; i++ ){
		pos_t	pos1, pos2;

		p = party.mbr[i];

		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		tmp_r = abs( p->x - x ) + abs( p->y - y );
		if( tmp_r > min_r )
			continue;

		pos1.x = p->x;
		pos1.y = p->y;
		pos2.x = x;
		pos2.y = y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( tmp_r < min_r ){
			if( chk_already_mark( p, mbr ) )
				continue;
			n = 0;
			min_r = tmp_r;
		} else if( tmp_r == min_r ){
			if( chk_already_mark( p, mbr ) )
				continue;
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/**/

mbr_t	*get_mbr_randm( long x, long y )
{
	mbr_t	*p, *ret_p;
	long	n;
	long	i;

	n = 0;
	ret_p = NULL;

	for( i = 0; i < MBR_MAX_N; i++ ){
		pos_t	pos1, pos2;

		p = party.mbr[i];

		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( clip_pos( x, y ) ){
			pos1.x = p->x;
			pos1.y = p->y;
			pos2.x = x;
			pos2.y = y;
			if( !chk_find( &pos1, &pos2 ) )
				continue;
		}

		n++;
		if( per_randm( n ) )
			ret_p = p;
	}

	return ret_p;
}

/**/

mbr_t	*get_mbr_stagger( mbr_t *mbr )
{
	mbr_t	*p, *ret_p;
	long	min_r, tmp_r;
	long	n;
	long	x, y;
	long	i;

	if( mbr == NULL )
		return NULL;

	/* 自分がフラついていたらマークしない */
	if( chk_chr_stagger( mbr ) )
		return NULL;

	x = mbr->x;
	y = mbr->y;

	min_r = MAP_MAX_X + MAP_MAX_Y;
	n = 0;
	ret_p = NULL;

	for( i = 0; i < MBR_MAX_N; i++ ){
		pos_t	pos1, pos2;

		p = party.mbr[i];

		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( !chk_chr_stagger( p ) )
			continue;

		tmp_r = abs( p->x - x ) + abs( p->y - y );
		if( tmp_r > min_r )
			continue;

		pos1.x = p->x;
		pos1.y = p->y;
		pos2.x = x;
		pos2.y = y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( tmp_r < min_r ){
			if( chk_already_mark( p, mbr ) )
				continue;
			n = 0;
			min_r = tmp_r;
		} else if( tmp_r == min_r ){
			if( chk_already_mark( p, mbr ) )
				continue;
			n++;
			if( randm( n ) != 0 )
				continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/**/

mbr_t	*get_mbr_hp_min( void )
{
	return get_mbr_hp_mp_min_max( TRUE, -1 );
}

/**/

mbr_t	*get_mbr_hp_max( void )
{
	return get_mbr_hp_mp_min_max( TRUE, +1 );
}

/**/

mbr_t	*get_mbr_mp_min( void )
{
	return get_mbr_hp_mp_min_max( FALSE, -1 );
}

/**/

mbr_t	*get_mbr_mp_max( void )
{
	return get_mbr_hp_mp_min_max( FALSE, +1 );
}

/**/

mbr_t	*get_mbr_hp_mp_min_max( bool_t flg_hp, long min_max )
{
	mbr_t	*p, *ret_p;
	rate_t	min_max_rate, tmp_rate;
	long	min_max_n, tmp_n;
	long	n;
	long	i;

	if( min_max >= +1 ){
		min_max_rate = (rate_t)0;
		min_max_n = 0;
	} else if( min_max <= -1 ){
		min_max_rate = _100_PERCENT;
		min_max_n = 0x7fffffff;
	} else {
		return NULL;
	}
	n = 0;
	ret_p = NULL;

	for( i = 0; i < MBR_MAX_N; i++ ){
		p = party.mbr[i];

		if( chk_flg_or( p->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( flg_hp ){
			tmp_rate = p->abl.hp.n * _100_PERCENT
					/ p->abl.hp.max;
			tmp_n = p->abl.hp.n;
		} else {
			tmp_rate = p->abl.mp.n * _100_PERCENT
					/ p->abl.mp.max;
			tmp_n = p->abl.mp.n;
		}

		if( tmp_rate == min_max_rate ){
			if( (min_max >= +1) && (tmp_n > min_max_n) ){
				min_max_rate = tmp_rate;
				min_max_n = tmp_n;
				n = 1;
			} else if( (min_max <= -1) && (tmp_n < min_max_n) ){
				min_max_rate = tmp_rate;
				min_max_n = tmp_n;
				n = 1;
			} else if( tmp_n == min_max_n ){
				n++;
				if( randm( n ) == 0 ){
					min_max_rate = tmp_rate;
					min_max_n = tmp_n;
				} else {
					continue;
				}
			} else {
				continue;
			}
		} else if( (min_max >= +1) && (tmp_rate > min_max_rate) ){
			min_max_rate = tmp_rate;
			min_max_n = tmp_n;
			n = 1;
		} else if( (min_max <= -1) && (tmp_rate < min_max_rate) ){
			min_max_rate = tmp_rate;
			min_max_n = tmp_n;
			n = 1;
		} else {
			continue;
		}

		ret_p = p;
	}

	return ret_p;
}

/**/

bool_t	chk_already_mark( void *p, mbr_t *mbr )
{
	party_t	*pty;
	long	i;

	if( mbr == NULL )
		return FALSE;

	pty = get_party();

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}
		if( pty->mbr[i] == mbr )
			continue;
		if( pty->mbr[i]->trgt.kind == TRGT_KIND_SQUARE )
			continue;

		if( pty->mbr[i]->trgt.p == p )
			return TRUE;
	}

	return FALSE;
}

/**/

char	*get_race_str( race_t *race )
{
	static char	str_main[RACE_STR_MAX_BYTE + 1];
	static char	str_sub[RACE_STR_MAX_BYTE + 1];
	static char	str_tmp[RACE_STR_MAX_BYTE * 3 + 1];
	static char	str_name[RACE_STR_MAX_BYTE + 1];

	if( race == NULL )
		return MSG_NULL;

	str_main[0] = '\0';
	str_sub[0] = '\0';
	str_tmp[0] = '\0';
	str_name[0] = '\0';

	str_nz_cpy( str_main, get_race_str_main( race ),
			RACE_STR_MAX_BYTE );
	str_nz_cpy( str_sub, get_race_str_sub( race ),
			RACE_STR_MAX_BYTE );

	if( race->sub == SUB_RACE_NULL ){
		sn_printf( str_tmp, RACE_STR_MAX_BYTE,
				MSG_RACE_STR_PUREBRED, str_main );
	} else {
		sn_printf( str_tmp, RACE_STR_MAX_BYTE,
				MSG_RACE_STR_MIXED, str_main, str_sub );
	}

	str_nz_cpy( str_name, str_tmp, RACE_STR_MAX_BYTE );

	return str_name;
}

/**/

char	*get_race_str_main( race_t *race )
{
	if( race == NULL )
		return MSG_NULL;

	switch( race->main ){
	case MAIN_RACE_HUMAN:
		return MSG_MAIN_RACE_HUMAN;
	case MAIN_RACE_HALF_ELF:
		return MSG_MAIN_RACE_HALF_ELF;
	case MAIN_RACE_ELF:
		return MSG_MAIN_RACE_ELF;
	case MAIN_RACE_DWARF:
		return MSG_MAIN_RACE_DWARF;
	case MAIN_RACE_VIVID:
		return MSG_MAIN_RACE_VIVID;
	case MAIN_RACE_MAX_N:
		break;
	}

	return MSG_NULL;
}

/**/

char	*get_race_str_sub( race_t *race )
{
	if( race == NULL )
		return MSG_NULL;

	switch( race->sub ){
	case SUB_RACE_NULL:
		break;
	case SUB_RACE_CAT:
		return MSG_SUB_RACE_CAT;
	case SUB_RACE_DOG:
		return MSG_SUB_RACE_DOG;
	case SUB_RACE_MOUSE:
		return MSG_SUB_RACE_MOUSE;
	case SUB_RACE_RABBIT:
		return MSG_SUB_RACE_RABBIT;
	case SUB_RACE_MONKEY:
		return MSG_SUB_RACE_MONKEY;
	case SUB_RACE_PIG:
		return MSG_SUB_RACE_PIG;
	case SUB_RACE_BIRD:
		return MSG_SUB_RACE_BIRD;
	case SUB_RACE_LIZARD:
		return MSG_SUB_RACE_LIZARD;
	case SUB_RACE_MAX_N:
		break;
	}

	return MSG_NULL;
}

/**/

char	*get_race_name( race_t *race )
{
	if( race == NULL )
		return MSG_NULL;

	return race->name;
}

/**/

bool_t	chk_not_exist_all_mbr( void )
{
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		if( !chk_flg_or( party.mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			return FALSE;

	return TRUE;
}

/**/

mbr_t	**get_ls_mbr( void )
{
	return ls_mbr;
}

/**/

mbr_t	*get_ls_mbr_tail( void )
{
	long	i;

	for( i = LS_MBR_MAX_N - 1; i >= 0; i-- ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		return ls_mbr[i];
	}

	return NULL;
}

/**/

party_t	*get_party( void )
{
	return &party;
}

/**/

long	get_mbr_n( long x, long y )
{
	dun_t	*dun;
	mbr_t	*p;
	party_t	*pty;
	long	n;

	dun = get_dun();

	if( !clip_pos( x, y ) )
		return MBR_N_NOT_JOIN;

	if( dun->map.chr.mjr[y][x] == FACE_MJR_NULL )
		return MBR_N_NOT_JOIN;

	p = dun->map.chr_p[y][x];
	if( (p != NULL) && is_mbr( p ) )
		return( p->mbr_n );

	pty = get_party();
	for( n = 0; n < MBR_MAX_N; n++ ){
		mbr_t	*mbr;

		mbr = pty->mbr[n];
		if( chk_flg_or( mbr->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( x < get_chr_left( mbr->x, mbr->dx ) )
			continue;
		if( x > get_chr_right( mbr->x, mbr->dx ) )
			continue;
		if( y < get_chr_top( mbr->y, mbr->dy ) )
			continue;
		if( y > get_chr_bottom( mbr->y, mbr->dy ) )
			continue;

		return n;
	}

	return MBR_N_NOT_JOIN;
}

/**/

mbr_t	*get_mbr( long x, long y )
{
	long	mbr_n;

	mbr_n = get_mbr_n( x, y );

	if( mbr_n <= MBR_N_NOT_JOIN )
		return NULL;

	return( party.mbr[mbr_n] );
}

/**/

flg_party_t	get_flg_party( void )
{
	return party.flg;
}

/**/

flg_party_t	set_flg_party( flg_party_t flg )
{
	party.flg = flg;

	return party.flg;
}

/**/

long	next_mbr( long n, long add )
{
	pet_t	**pet;
	long	pet_n;
	long	i;

	if( add == 0 )
		return n;

	pet = get_party_pet();

	for( i = 0; i < MBR_MAX_N + PET_MAX_N; i++ ){
		n += add;
		n += MBR_MAX_N + PET_MAX_N;
		n %= MBR_MAX_N + PET_MAX_N;

		if( n < MBR_MAX_N ){
			if( !chk_flg( party.mbr[n]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}
		} else {
			pet_n = n - MBR_MAX_N;
			if( (pet[pet_n] != NULL)
					&& !chk_flg( pet[pet_n]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}
		}
	}

	return n;
}

/**/

long	next_ls_mbr( long ls_n, long add )
{
	long	i;

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		ls_n += add + LS_MBR_MAX_N;
		ls_n %= LS_MBR_MAX_N;
		if( !chk_flg( ls_mbr[ls_n]->stat, FLG_STAT_NOT_EXIST ) )
			break;
	}

	return ls_n;
}

/**/

class_t	*get_class_tab( void )
{
	return class_tab;
}

/**/

bool_t	remove_class( long class_n )
{
	mbr_t	**ls_mbr = get_ls_mbr();
	class_t	*p = get_class_tab();
	long	n, max_n;
	long	i;

	if( p[1].name[0] == '\0' ){
		print_msg( FLG_NULL, MSG_S, MSG_ERR_REMOVE_CLASS );
		return FALSE;
	}

	for( n = class_n; n < CLASS_MAX_N; n++ ){
		p[n] = p[n + 1];
		if( p[n + 1].name[0] == '\0' )
			break;
	}
	max_n = n - 1;

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i]->class_n > class_n )
			ls_mbr[i]->class_n--;
		else if( ls_mbr[i]->class_n > max_n )
			ls_mbr[i]->class_n = max_n;
	}

	return TRUE;
}

/**/

bool_t	cmp_class( class_t *org, class_t *dst )
{
	long	abl;
	long	i;

	if( strncmp( org->name, dst->name, CLASS_NAME_MAX_BYTE ) != 0 )
		return FALSE;

	for( abl = 0; abl < ABL_KIND_MAX_N; abl++ )
		if( org->abl_rate[abl] != dst->abl_rate[abl] )
			return FALSE;

	for( i = 0; i < SKILL_MAX_N; i++ )
		if( org->skill[i] != dst->skill[i] )
			return FALSE;

	return TRUE;
}

/**/

void	arrange_class_1( long class_n, long d )
{
	mbr_t	**ls_mbr = get_ls_mbr();
	class_t	*p = get_class_tab();
	class_t	tmp;
	long	i;

	if( (class_n + d) < 0 )
		return;
	if( (class_n + d) >= CLASS_MAX_N )
		return;

	tmp = p[class_n];
	p[class_n] = p[class_n + d];
	p[class_n + d] = tmp;

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i]->class_n == class_n )
			ls_mbr[i]->class_n = (class_n + d);
		else if( ls_mbr[i]->class_n == (class_n + d) )
			ls_mbr[i]->class_n = class_n;
	}
}

/**/

void	arrange_class( long class_n, long d )
{
	mbr_t	**ls_mbr = get_ls_mbr();
	class_t	*p = get_class_tab();
	class_t	tmp;
	long	n, tail;
	long	i;

	tail = 0;

	tmp = p[class_n];
	if( d <= -1 ){
		for( n = class_n - 1; n >= 0; n-- ){
			p[n + 1] = p[n];
		}

		p[0] = tmp;
	} else {
		for( n = class_n + 1; n < CLASS_MAX_N; n++ ){
			if( p[n].name[0] == '\0' )
				break;

			p[n - 1] = p[n];
		}

		p[n - 1] = tmp;
		tail = n - 1;
	}

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( d <= -1 ){
			if( ls_mbr[i]->class_n == class_n )
				ls_mbr[i]->class_n = 0;
			else if( ls_mbr[i]->class_n < class_n )
				ls_mbr[i]->class_n++;
		} else {
			if( ls_mbr[i]->class_n == class_n )
				ls_mbr[i]->class_n = tail;
			else if( ls_mbr[i]->class_n > class_n )
				ls_mbr[i]->class_n--;
		}
	}
}

/**/

square_t	*get_square_mbr( void )
{
	return &(party.square);
}

/**/

void	set_square_mbr( square_t *sq )
{
	party.square = *sq;
}

/**/

void	get_square_pos( long *x, long *y, bool_t flg_pre )
{
	if( x != NULL ){
		if( flg_pre ){
			*x = party.square.pre_x;
		} else {
			*x = party.square.x;
		}
	}
	if( y != NULL ){
		if( flg_pre ){
			*y = party.square.pre_y;
		} else {
			*y = party.square.y;
		}
	}
}

/**/

void	set_square_pos( long x, long y, bool_t flg_pre )
{
	if( !clip_pos( x, y ) )
		return;

	if( flg_pre ){
		party.square.pre_x = x;
		party.square.pre_y = y;
	} else {
		party.square.pre_x = party.square.x;
		party.square.pre_y = party.square.y;

		party.square.x = x;
		party.square.y = y;
	}

	reset_mbr_dir();
}

/**/

void	unset_square_pos( void )
{
	if( !clip_pos( party.square.pre_x, party.square.pre_y ) )
		return;

	party.square.x = party.square.pre_x;
	party.square.y = party.square.pre_y;
	party.square.dir = party.square.pre_dir;

	reset_mbr_dir();
}

/**/

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_party_c( void )
{
	check_memory( check_memory_party_c_ls_mbr,
			"party.c: ls_mbr" );
	check_memory( check_memory_party_c_ls_mbr_buf,
			"party.c: ls_mbr_buf" );
	check_memory( check_memory_party_c_party,
			"party.c: party" );
	check_memory( check_memory_party_c_abl_init,
			"party.c: abl_init" );
	check_memory( check_memory_party_c_resi_init,
			"party.c: resi_init" );
	check_memory( check_memory_party_c_ave_stomach,
			"party.c: ave_stomach" );
}
