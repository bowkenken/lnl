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
* $Id: spell.c,v 1.226 2014/03/15 00:50:40 bowkenken Exp $
***************************************************************/

#define	SPELL_C
#include	"inc.h"

/**/

/* 階層移動などでメニューをリセットするか? */
#define	FLG_RESET_MENU	0

/* 聖域の上で祈り以外がとどくか? */
#define	FLG_SPELL_SANCTUARY	TRUE

#define	CHK_SPELL_LEV_RATE	((rate_t)100)
#define	CHK_SPELL_LEV_RATE_BASE	((rate_t)90)

#define	SPELL_PRICE_LEV_MUL	((rate_t)500)

#define	WORD_OF_DESTRUCTION_RATE	300

#define	SKELETON_WARRIOR_STD_N	2

#define	DISMISSAL_TURN_BONE	128
#define	DISMISSAL_TURN_SKELETON	128
#define	DISMISSAL_TURN_UNICORN	128
#define	DISMISSAL_TURN_EFREET	128
#define	DISMISSAL_TURN_DJINNI	128
#define	DISMISSAL_TURN_PHOENIX	128
#define	DISMISSAL_TURN_ELEMENTAL	64

#define	SPELL_NIN_RATE	((rate_t)80)
#define	SPELL_SHA_RESI_DIV_RATE	((rate_t)400)

#define	BAR_LIMIT_LEV	30

#define	ACCEL_KEY_REG_SPELL	'X'
#define	ACCEL_KEY_REG_SPELL_REMARK	'Y'
#define	ACCEL_KEY_NO_LEARN	'Z'

/**/

static cast_tab_t	cast_tab[LS_MBR_MAX_N][SPELL_KIND_MAX_N];
check_memory_def( check_memory_spell_c_cast_tab )

static mbr_t	*g_sel_mbr;
static mbr_t	*g_pre_sel_mbr;
static spell_tab_t	*g_sel_spell;
check_memory_def( check_memory_spell_c_g_sel_mbr )

static menu_t	*g_dflt_spell_abl[LS_MBR_MAX_N];
check_memory_def( check_memory_spell_c_g_dflt_spell_abl )
static menu_t	*g_dflt_spell[LS_MBR_MAX_N][ABL_KIND_MAX_N];
check_memory_def( check_memory_spell_c_g_dflt_spell )
static menu_t	*g_dflt_spell_extent[LS_MBR_MAX_N][ABL_KIND_MAX_N];
check_memory_def( check_memory_spell_c_g_dflt_spell_extent )
static abl_kind_t	g_sel_spell_abl;
check_memory_def( check_memory_spell_c_g_sel_spell_abl )

static long	g_vfx_n;
check_memory_def( check_memory_spell_c_g_vfx_n )
static pos_t	g_vfx_bgn[VFX_ARW_MAX_N], g_vfx_end[VFX_ARW_MAX_N];
check_memory_def( check_memory_spell_c_g_vfx_bgn )

/**/

reg_spell_t	g_reg_spell[MBR_MAX_N];
check_memory_def( check_memory_spell_c_g_reg_spell )

/**/

#include	"spell-tab.h"

/**/

void	init_spell( void )
{
	long	m;
	long	k;
	menu_t	*ls;
	long	max_len;
	int	min_len;
	long	i;

	g_pre_sel_mbr = NULL;

	for( m = 0; m < LS_MBR_MAX_N; m++ )
		init_spell_new_mbr( m );

	for( k = SPELL_KIND_NULL + 1; k < SPELL_KIND_MAX_N; k++ ){
		if( spell_tab[k].kind == SPELL_KIND_NULL )
			break;
		if( spell_tab[k].kind == SPELL_KIND_MAX_N )
			break;

		spell_tab[k].name = MSG( spell_tab[k].n_name );
	}

	for( m = 0; m < LS_MBR_MAX_N; m++ ){
		long	k;

		g_dflt_spell_abl[m] = NULL;
		for( k = 0; k < ABL_KIND_MAX_N; k++ ){
			g_dflt_spell[m][k] = NULL;
			g_dflt_spell_extent[m][k] = NULL;
		}
	}

	ls = ls_menu_spell;

	max_len = 1;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( ls[i].path[0] == '\0' )
			break;
		if( ls[i].arg == NULL )
			continue;

		max_len = max_l( max_len, str_len_draw(
				MSG( ls[i].n_msg ) ) );
	}

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		spell_tab_t	*tab;

		if( ls[i].path[0] == '\0' )
			break;
		if( ls[i].arg == NULL )
			continue;

		tab = get_spell_tab( (spell_kind_t)(long)(ls[i].arg) );
		if( tab == NULL )
			continue;

		min_len = get_pading_len( MSG( ls[i].n_msg ), max_len );

		sn_printf( ls[i].msg, MENU_MSG_MAX_BYTE,
				MSG_MENU_SPELL_LS,
				min_len,
				MSG( ls[i].n_msg ),
				tab->mp, tab->hp, tab->gold );
	}

	for( m = 0; m < MBR_MAX_N; m++ ){
		g_reg_spell[m].tab = NULL;
		g_reg_spell[m].extent_kind = EXTENT_KIND_NORMAL;
		g_reg_spell[m].trgt.kind = TRGT_KIND_NULL;
		g_reg_spell[m].trgt.p = NULL;
	}
}

/***************************************************************
* スタティック変数をリセット
***************************************************************/

void	reset_static_spell( void )
{
	/* cast_tab */

#if	FLG_RESET_MENU
	g_sel_mbr = NULL;
	g_pre_sel_mbr = NULL;
	g_sel_spell = NULL;

	{
		long	m;

		for( m = 0; m < LS_MBR_MAX_N; m++ ){
			long	k;

			g_dflt_spell_abl[m] = NULL;
			for( k = 0; k < ABL_KIND_MAX_N; k++ ){
				g_dflt_spell[m][k] = NULL;
				g_dflt_spell_extent[m][k] = NULL;
			}
		}
	}
	g_sel_spell_abl = ABL_KIND_HP;
#endif

	/* g_vfx_n = 0; */
	/* g_vfx_bgn, g_vfx_end */;
}

/**/

void	init_spell_debug( void )
{
	long	m;
	long	k;

	m = LS_MBR_N_BLADE;
	for( k = SPELL_KIND_NIN_MIN_N + 1; k < SPELL_KIND_NIN_MAX_N; k++ )
		cast_tab[m][k].flg_cast = TRUE;

	m = LS_MBR_N_CECILE;
	for( k = SPELL_KIND_PRI_MIN_N + 1; k < SPELL_KIND_PRI_MAX_N; k++ ){
#if	0
		if( k == SPELL_KIND_CURE_PARALYZE )
			continue;
		if( k == SPELL_KIND_CURE_BLINDNESS )
			continue;
#endif

		cast_tab[m][k].flg_cast = TRUE;
	}

	m = LS_MBR_N_HALLE;
	for( k = SPELL_KIND_BAR_MIN_N + 1; k < SPELL_KIND_BAR_MAX_N; k++ ){
#if	0
		if( k == SPELL_KIND_SONG_DULLNESS )
			continue;
#endif

		cast_tab[m][k].flg_cast = TRUE;
	}

	m = LS_MBR_N_BEAUT;
	for( k = SPELL_KIND_NULL + 1; k < SPELL_KIND_MAX_N; k++ ){
#if	0
		if( k == SPELL_KIND_CREATE_FOOD )
			continue;
		if( k == SPELL_KIND_CREATE_UNDEAD )
			continue;
#endif

		cast_tab[m][k].flg_cast = TRUE;
	}

	m = LS_MBR_N_BEAUT;
	for( k = SPELL_KIND_SHA_MIN_N + 1; k < SPELL_KIND_SHA_MAX_N; k++ )
		cast_tab[m][k].flg_cast = FALSE;

	m = LS_MBR_N_EYE;
	for( k = SPELL_KIND_SUM_MIN_N + 1; k < SPELL_KIND_SUM_MAX_N; k++ )
		cast_tab[m][k].flg_cast = TRUE;
}

/**/

void	init_spell_new_mbr( long ls_mbr_n )
{
	long	k;

	for( k = 0; k < SPELL_KIND_MAX_N; k++ ){
		cast_tab[ls_mbr_n][k].kind = (spell_kind_t)k;
		cast_tab[ls_mbr_n][k].flg_cast = FALSE;
	}
}

/**/

void	init_spell_dflt( void )
{
	long	m;

	m = LS_MBR_N_CECILE;
	cast_tab[m][SPELL_KIND_CURE_HP_LIGHT].flg_cast = TRUE;

	m = LS_MBR_N_BEAUT;
	cast_tab[m][SPELL_KIND_LIGHT].flg_cast = TRUE;
}

/**/

void	init_spell_nin( void )
{
	chr_t	*chr;
	long	k;

	chr = get_mbr_randm( MAP_DEL_X, MAP_DEL_Y );

	for( k = SPELL_KIND_NIN_MIN_N + 1; k < SPELL_KIND_NIN_MAX_N; k++ )
		chk_chr_learned_spell_nin( chr, (spell_kind_t)k, TRUE );
}

/**/

void	reset_spell( void )
{
	long	m;

	for( m = 0; m < MBR_MAX_N; m++ ){
		g_reg_spell[m].tab = NULL;
		g_reg_spell[m].extent_kind = EXTENT_KIND_NORMAL;
		g_reg_spell[m].trgt.kind = TRGT_KIND_NULL;
		g_reg_spell[m].trgt.p = NULL;
	}
}

/**/

char	*cb_menu_sel_spell( menu_t **pp, menu_t **dflt )
{
	pos_t	*crsr;
	bool_t	flg_sel_mbr;
	char	*str_goto;

	set_menu_dflt_main( *pp );

	crsr = get_main_crsr();
	g_sel_mbr = get_mbr( crsr->x, crsr->y );
	if( g_sel_mbr == NULL )
		flg_sel_mbr = TRUE;
	else
		flg_sel_mbr = FALSE;

	do {
		if( flg_sel_mbr ){
			char	*str;

			g_sel_mbr = g_pre_sel_mbr;

			str = exec_menu_sel_mbr( &g_sel_mbr, NULL,
					FALSE, FALSE );
			if( str != NULL )
				return STR_MENU_ERR;
		}
		if( g_sel_mbr == NULL )
			return STR_MENU_ERR;

		g_pre_sel_mbr = g_sel_mbr;

		str_goto = menu_sel_spell( g_sel_mbr );
		if( str_goto == NULL )
			return NULL;
		if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
			continue;
		if( strcmp( str_goto, STR_MENU_ERR ) == 0 )
			return str_goto;
	} while( flg_sel_mbr );

	return NULL;
}

/**/

char	*menu_sel_spell( mbr_t *mbr )
{
	menu_t *dflt;
	menu_t	*ls;
	unsigned char	key;
	bool_t	flg;
	bool_t	flg_learn;
	reg_spell_t	*reg;
	long	i;

	if( mbr == NULL )
		return STR_MENU_ERR;

	if( !chk_can_chr_cast_stat( mbr ) ){
		print_msg( FLG_NULL, MSG_ERR_SPELL, mbr->name );
		return STR_MENU_CANCEL;
	}

	ls = ls_menu_spell;
	clr_flg_menu( ls, NULL, FLG_MENU_ALL );

	reg = get_reg_spell( mbr->mbr_n );

	flg_learn = FALSE;
	key = 'A';
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		spell_kind_t	kind;

		if( ls[i].path[0] == '\0' )
			break;
		if( strcmp( ls[i].kind, "<PageSeparator>" ) == 0 ){
			key = 'A';
			continue;
		}
		if( ls[i].accel_key == ACCEL_KEY_REG_SPELL ){
			if( (reg != NULL) && (reg->tab != NULL)
					&& (reg->trgt.p != NULL) ){
				sn_printf( ls[i].msg,
						MENU_MSG_MAX_BYTE,
						MSG_MENU_REG_SPELL,
						reg->tab->name );
			} else {
				sn_printf( ls[i].msg,
						MENU_MSG_MAX_BYTE,
						MSG_MENU_REG_SPELL_NULL );
			}
			continue;
		}
		if( ls[i].accel_key == ACCEL_KEY_REG_SPELL_REMARK ){
			if( (reg != NULL) && (reg->tab != NULL) ){
				sn_printf( ls[i].msg,
						MENU_MSG_MAX_BYTE,
						MSG_MENU_REG_SPELL_REMARK,
						reg->tab->name );
			} else {
				sn_printf( ls[i].msg,
						MENU_MSG_MAX_BYTE,
						MSG_MENU_REG_SPELL_NULL );
			}
			continue;
		}
		if( ls[i].accel_key == ACCEL_KEY_NO_LEARN ){
			if( flg_learn )
				ls[i].flg |= FLG_MENU_HIDDEN;
			else
				ls[i].flg &= ~FLG_MENU_HIDDEN;
			flg_learn = FALSE;

			continue;
		}
		if( ls[i].arg == NULL )	/* 注意 */
			continue;

		ls[i].accel_key = key;
		key++;

		kind = (spell_kind_t)(long)(ls[i].arg);
		if( chk_can_chr_cast_lev( mbr, kind ) ){
			ls[i].flg &= ~FLG_MENU_HIDDEN;
			flg_learn = TRUE;
		} else {
			ls[i].flg |= FLG_MENU_HIDDEN;
		}
	}

	flg = FALSE;

	if( get_lev( mbr, ABL_KIND_MAG ) > 0 ){
		clr_flg_menu( ls, "MAG", FLG_MENU_HIDDEN );
		flg = TRUE;
	} else {
		set_flg_menu( ls, "MAG", FLG_MENU_HIDDEN );
	}

	if( get_lev( mbr, ABL_KIND_SOR ) > 0 ){
		clr_flg_menu( ls, "SOR", FLG_MENU_HIDDEN );
		flg = TRUE;
	} else {
		set_flg_menu( ls, "SOR", FLG_MENU_HIDDEN );
	}

	if( get_lev( mbr, ABL_KIND_ENC ) > 0 ){
		clr_flg_menu( ls, "ENC", FLG_MENU_HIDDEN );
		flg = TRUE;
	} else {
		set_flg_menu( ls, "ENC", FLG_MENU_HIDDEN );
	}

	if( get_lev( mbr, ABL_KIND_SUM ) > 0 ){
		clr_flg_menu( ls, "SUM", FLG_MENU_HIDDEN );
		flg = TRUE;
	} else {
		set_flg_menu( ls, "SUM", FLG_MENU_HIDDEN );
	}

	if( get_lev( mbr, ABL_KIND_PRI ) > 0 ){
		clr_flg_menu( ls, "PRI", FLG_MENU_HIDDEN );
		flg = TRUE;
	} else {
		set_flg_menu( ls, "PRI", FLG_MENU_HIDDEN );
	}

	if( get_lev( mbr, ABL_KIND_SHA ) > 0 ){
		clr_flg_menu( ls, "SHA", FLG_MENU_HIDDEN );
		flg = TRUE;
	} else {
		set_flg_menu( ls, "SHA", FLG_MENU_HIDDEN );
	}

	if( get_lev( mbr, ABL_KIND_BAR ) > 0 ){
		clr_flg_menu( ls, "BAR", FLG_MENU_HIDDEN );
		flg = TRUE;
	} else {
		set_flg_menu( ls, "BAR", FLG_MENU_HIDDEN );
	}

	if( get_lev( mbr, ABL_KIND_NIN ) > 0 ){
		clr_flg_menu( ls, "NIN", FLG_MENU_HIDDEN );
		flg = TRUE;
	} else {
		set_flg_menu( ls, "NIN", FLG_MENU_HIDDEN );
	}

	if( !flg ){
		print_msg( FLG_NULL, MSG_ERR_SPELL, mbr->name );
		return STR_MENU_CANCEL;
	}

	dflt = g_dflt_spell_abl[mbr->ls_mbr_n];
	return exec_menu( ls, dflt, NULL );
}

/**/

char	*cb_menu_reg_spell( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;
	long	mbr_n;
	void	*p;

	mbr = g_sel_mbr;
	if( mbr == NULL )
		return STR_MENU_CANCEL;

	mbr_n = mbr->mbr_n;
	if( mbr_n < 0 )
		return STR_MENU_CANCEL;
	if( mbr_n >= MBR_MAX_N )
		return STR_MENU_CANCEL;

	p = g_reg_spell[mbr_n].trgt.p;
	if( p == NULL )
		return STR_MENU_CANCEL;

	if( g_reg_spell[mbr_n].tab == NULL )
		return STR_MENU_CANCEL;
	if( g_reg_spell[mbr_n].trgt.kind == TRGT_KIND_NULL )
		return STR_MENU_CANCEL;

	/* メニューのデフォルトに設定 */

	g_dflt_spell_abl[mbr->ls_mbr_n] = *pp;

	/* ターゲットをマーク */

	switch( g_reg_spell[mbr_n].trgt.kind ){
	case TRGT_KIND_NULL:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		return STR_MENU_ERR;
	case TRGT_KIND_MBR:
		mark_mbr( mbr, (mbr_t *)p, DIST_FAR );
		break;
	case TRGT_KIND_MNSTR:
		mark_mnstr( mbr, (mnstr_t *)p, DIST_FAR );
		break;
	case TRGT_KIND_MNSTR_NULL:
		mark_mnstr_null( mbr,
				g_reg_spell[mbr_n].trgt.x,
				g_reg_spell[mbr_n].trgt.y,
				DIST_FAR );
		break;
	case TRGT_KIND_POS:
		mark_pos( mbr,
				g_reg_spell[mbr_n].trgt.x,
				g_reg_spell[mbr_n].trgt.y,
				DIST_FAR );
		break;
	case TRGT_KIND_ITEM:
		mark_item( mbr, (item_t *)p, DIST_FAR );
		break;
	case TRGT_KIND_DOOR:
		mark_door( mbr, (door_t *)p, DIST_FAR );
		break;
	case TRGT_KIND_TRAP:
		mark_trap( mbr, (trap_t *)p, DIST_FAR );
		break;
	case TRGT_KIND_QUEUE:
		return STR_MENU_ERR;
	case TRGT_KIND_SQUARE:
		mark_square( mbr );
		break;
	}

	/* アクションを設定 */

	set_chr_act( mbr, ACT_KIND_SPELL,
			g_reg_spell[mbr_n].tab, NULL,
			g_reg_spell[mbr_n].extent_kind, 0 );

	return NULL;
}

/**/

char	*cb_menu_reg_spell_remark( menu_t **pp, menu_t **dflt )
{
	mbr_t	*mbr;
	long	mbr_n;

	mbr = g_sel_mbr;
	if( mbr == NULL )
		return STR_MENU_CANCEL;

	mbr_n = mbr->mbr_n;
	if( mbr_n < 0 )
		return STR_MENU_CANCEL;
	if( mbr_n >= MBR_MAX_N )
		return STR_MENU_CANCEL;

	if( g_reg_spell[mbr_n].tab == NULL )
		return STR_MENU_CANCEL;
	if( g_reg_spell[mbr_n].trgt.kind == TRGT_KIND_NULL )
		return STR_MENU_CANCEL;

	/* メニューのデフォルトに設定 */

	g_dflt_spell_abl[mbr->ls_mbr_n] = *pp;

	/* ターゲットをマーク */

	if( get_spell_flg_trgt( g_sel_spell,
			g_reg_spell[mbr_n].extent_kind ) ){
		char	*str_goto;

		str_goto = menu_spell_trgt( g_sel_mbr );
		if( str_goto != NULL )
			return str_goto;
	}

	/* アクションを設定 */

	set_chr_act( mbr, ACT_KIND_SPELL,
			g_reg_spell[mbr_n].tab, NULL,
			g_reg_spell[mbr_n].extent_kind, 0 );

	return NULL;
}

/**/

char	*cb_menu_dflt_spell_mag( menu_t **pp, menu_t **dflt )
{
	return menu_dflt_spell( pp, dflt, ABL_KIND_MAG );
}

/**/

char	*cb_menu_dflt_spell_sor( menu_t **pp, menu_t **dflt )
{
	return menu_dflt_spell( pp, dflt, ABL_KIND_SOR );
}

/**/

char	*cb_menu_dflt_spell_enc( menu_t **pp, menu_t **dflt )
{
	return menu_dflt_spell( pp, dflt, ABL_KIND_ENC );
}

/**/

char	*cb_menu_dflt_spell_sum( menu_t **pp, menu_t **dflt )
{
	return menu_dflt_spell( pp, dflt, ABL_KIND_SUM );
}

/**/

char	*cb_menu_dflt_spell_pri( menu_t **pp, menu_t **dflt )
{
	return menu_dflt_spell( pp, dflt, ABL_KIND_PRI );
}

/**/

char	*cb_menu_dflt_spell_sha( menu_t **pp, menu_t **dflt )
{
	return menu_dflt_spell( pp, dflt, ABL_KIND_SHA );
}

/**/

char	*cb_menu_dflt_spell_bar( menu_t **pp, menu_t **dflt )
{
	return menu_dflt_spell( pp, dflt, ABL_KIND_BAR );
}

/**/

char	*cb_menu_dflt_spell_nin( menu_t **pp, menu_t **dflt )
{
	return menu_dflt_spell( pp, dflt, ABL_KIND_NIN );
}

/**/

char	*menu_dflt_spell( menu_t **pp, menu_t **dflt, abl_kind_t kind )
{
	g_dflt_spell_abl[g_sel_mbr->ls_mbr_n] = *pp;
	*dflt = g_dflt_spell[g_sel_mbr->ls_mbr_n][kind];
	g_sel_spell_abl = kind;

	return NULL;
}

/**/

char	*cb_menu_spell_no_learn( menu_t **pp, menu_t **dflt )
{
	return STR_MENU_CANCEL;
}

/**/

char	*cb_menu_spell( menu_t **pp, menu_t **dflt )
{
	menu_t	*ls;

	if( g_sel_mbr == NULL )
		return STR_MENU_ERR;

	ls = ls_menu_spell_extent;

	g_sel_spell = get_spell_tab( (spell_kind_t)(long)((*pp)->arg) );
	if( g_sel_spell == NULL )
		return STR_MENU_ERR;

	if( !chk_can_chr_cast_lev( g_sel_mbr, g_sel_spell->kind ) ){
		curs_attrset_chr( g_sel_mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_MENU_SPELL_LEV,
				g_sel_mbr->name );
		curs_attrset_dflt();

		return STR_MENU_CANCEL;
	}

	if( !chk_last_boss_can_spell( g_sel_spell->kind ) ){
		curs_attrset_chr( g_sel_mbr, -1, FALSE );
		print_msg( FLG_NULL, MSG_ERR_MENU_SPELL_LAST_BOSS );
		curs_attrset_dflt();

		return STR_MENU_CANCEL;
	}

	g_dflt_spell[g_sel_mbr->ls_mbr_n][g_sel_spell_abl] = *pp;

	if( chk_flg( g_sel_spell->flg_extent, FLG_EXTENT_NORMAL ) )
		clr_flg_menu( ls, "normal", FLG_MENU_HIDDEN );
	else
		set_flg_menu( ls, "normal", FLG_MENU_HIDDEN );

	if( chk_flg( g_sel_spell->flg_extent, FLG_EXTENT_SPREAD ) )
		clr_flg_menu( ls, "spread", FLG_MENU_HIDDEN );
	else
		set_flg_menu( ls, "spread", FLG_MENU_HIDDEN );

	if( chk_flg( g_sel_spell->flg_extent, FLG_EXTENT_MASS ) )
		clr_flg_menu( ls, "mass", FLG_MENU_HIDDEN );
	else
		set_flg_menu( ls, "mass", FLG_MENU_HIDDEN );

	if( chk_flg( g_sel_spell->flg_extent, FLG_EXTENT_LIMIT ) )
		clr_flg_menu( ls, "limit", FLG_MENU_HIDDEN );
	else
		set_flg_menu( ls, "limit", FLG_MENU_HIDDEN );

	if( chk_flg( g_sel_spell->flg_extent, FLG_EXTENT_HALF ) )
		clr_flg_menu( ls, "half", FLG_MENU_HIDDEN );
	else
		set_flg_menu( ls, "half", FLG_MENU_HIDDEN );

	if( chk_flg( g_sel_spell->flg_extent, FLG_EXTENT_DOUBLE ) )
		clr_flg_menu( ls, "double", FLG_MENU_HIDDEN );
	else
		set_flg_menu( ls, "double", FLG_MENU_HIDDEN );

	*pp = ls;
	*dflt = g_dflt_spell_extent[g_sel_mbr->ls_mbr_n][g_sel_spell_abl];

	return NULL;
}

/**/

char	*cb_menu_spell_extent( menu_t **pp, menu_t **dflt )
{
	extent_kind_t	ex;

	if( g_sel_mbr == NULL )
		return STR_MENU_ERR;
	if( g_sel_spell == NULL )
		return STR_MENU_ERR;

	g_dflt_spell_extent[g_sel_mbr->ls_mbr_n][g_sel_spell_abl] = *pp;

	ex = (extent_kind_t)(long)((*pp)->arg);

	if( get_spell_flg_trgt( g_sel_spell, ex ) ){
		char	*str_goto;

		str_goto = menu_spell_trgt( g_sel_mbr );
		if( str_goto != NULL )
			return str_goto;
	}

	/* アクションを設定 */

	set_chr_act( g_sel_mbr, ACT_KIND_SPELL, g_sel_spell, NULL, ex, 0 );

	return NULL;
}

/**/

bool_t	get_spell_flg_trgt( spell_tab_t *tab, extent_kind_t ex )
{
	if( tab == NULL )
		return FALSE;

	do {
		if( tab->kind < SPELL_KIND_BAR_MIN_N )
			break;
		if( tab->kind > SPELL_KIND_BAR_MAX_N )
			break;
		if( ex != EXTENT_KIND_NORMAL )
			break;

		return FALSE;
	} while( 0 );

	return( tab->flg_trgt );
}

/**/

char	*menu_spell_trgt( mbr_t *mbr )
{
	pos_t	*crsr;
	trgt_kind_t	trgt_kind;
	char	*str_goto;
	mbr_t	*mbr2;
	mnstr_t	*mnstr;
	item_t	*item;
	door_t	*door;
	trap_t	*trap;

	if( mbr == NULL )
		return STR_MENU_ERR;

	/* 以前のターゲットにカーソルを移動 */

	crsr = get_main_crsr();
	if( crsr == NULL )
		return STR_MENU_ERR;
	if( mbr->trgt.kind != TRGT_KIND_SQUARE ){
		crsr->x = mbr->trgt.true_x;
		crsr->y = mbr->trgt.true_y;
	}

	/* ターゲットにカーソルを移動 */

	while( 1 ){
		str_goto = exec_menu_point_crsr();
		if( str_goto != NULL )
			return str_goto;

		/* ターゲットを選択 */

		str_goto = exec_menu_sel_obj( &trgt_kind, *crsr );
		if( str_goto == NULL ){
			if( trgt_kind == TRGT_KIND_AUTO )
				continue;
			break;
		}
		if( strcmp( str_goto, STR_MENU_CANCEL ) == 0 )
			continue;
		if( strcmp( str_goto, STR_MENU_ERR ) == 0 )
			return str_goto;
	}

	/* ターゲットをマーク */
	switch( trgt_kind ){
	case TRGT_KIND_NULL:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		return STR_MENU_ERR;
	case TRGT_KIND_MBR:
		mbr2 = get_mbr( crsr->x, crsr->y );
		if( mbr2 == NULL )
			return STR_MENU_ERR;
		mark_mbr( mbr, mbr2, DIST_FAR );
		break;
	case TRGT_KIND_MNSTR:
		mnstr = get_mnstr( crsr->x, crsr->y );
		if( mnstr == NULL )
			return STR_MENU_ERR;
		mark_mnstr( mbr, mnstr, DIST_FAR );
		break;
	case TRGT_KIND_MNSTR_NULL:
		mark_mnstr_null( mbr, crsr->x, crsr->y, DIST_FAR );
		break;
	case TRGT_KIND_POS:
		mark_pos( mbr, crsr->x, crsr->y, DIST_FAR );
		break;
	case TRGT_KIND_ITEM:
		item = get_item( crsr->x, crsr->y );
		if( item == NULL )
			return STR_MENU_ERR;
		mark_item( mbr, item, DIST_FAR );
		break;
	case TRGT_KIND_DOOR:
		door = get_door( crsr->x, crsr->y );
		if( door == NULL )
			return STR_MENU_ERR;
		mark_door( mbr, door, DIST_FAR );
		break;
	case TRGT_KIND_TRAP:
		trap = get_trap( crsr->x, crsr->y );
		if( trap == NULL )
			return STR_MENU_ERR;
		mark_trap( mbr, trap, DIST_FAR );
		break;
	case TRGT_KIND_QUEUE:
		return STR_MENU_ERR;
	case TRGT_KIND_SQUARE:
		mark_square( mbr );
		break;
	}

	return NULL;
}

/**/

void	chr_cast_spell( chr_t *chr, spell_tab_t *tab, const char *fmt )
{
	long	hp, mp;
	rate_t	resi;
	bool_t	flg_msg;
	const char	*inst_spell_name;
	curs_attr_t	prev_attr;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	if( !chk_can_chr_cast_stat( chr ) )
		return;
	if( !chk_can_chr_cast_lev( chr, tab->kind ) )
		return;
	if( !chk_last_boss_can_spell( tab->kind ) )
		return;

	if( is_mbr( chr ) ){
		set_reg_spell( chr->mbr_n, tab,
				(extent_kind_t)(chr->act.n), chr->trgt );
	}

	hp = tab->hp;
	mp = tab->mp;
	resi = tab->resi_down;

	switch( (extent_kind_t)(chr->act.n) ){
	case EXTENT_KIND_NULL:
	case EXTENT_KIND_MAX_N:
		return;
	case EXTENT_KIND_NORMAL:
		hp *= 1;
		mp *= 1;
		resi *= 1;
		break;
	case EXTENT_KIND_SPREAD:
		hp *= 2;
		mp *= 2;
		resi *= 2;
		break;
	case EXTENT_KIND_MASS:
		hp *= 3;
		mp *= 3;
		resi *= 3;
		break;
	case EXTENT_KIND_LIMIT:
		if( !chk_bar_limit( chr ) ){
			clr_chr_trgt_act( chr, FALSE );
			return;
		}

		hp *= 2;
		mp *= 2;
		resi *= 2;
		break;
	case EXTENT_KIND_HALF:
		hp /= 2;
		mp /= 2;
		resi /= 2;
		break;
	case EXTENT_KIND_DOUBLE:
		hp *= 2;
		mp *= 2;
		resi *= 2;
		break;
	}
	if( (tab->hp > 0) && (hp < 1) )
		hp = 1;
	if( (tab->mp > 0) && (mp < 1) )
		mp = 1;
	if( (tab->resi_down > 0) && (resi < 1) )
		resi = 1;

	if( resi > 0 ){
		long	resi_div;

		resi_div = get_lev( chr, ABL_KIND_SHA )
				+ get_lev( chr, ABL_KIND_CHA );
		resi_div *= SPELL_SHA_RESI_DIV_RATE;
		resi_div /= _100_PERCENT;
		resi_div += _100_PERCENT;
		if( resi_div < _100_PERCENT )
			resi_div = _100_PERCENT;

		resi *= _100_PERCENT;
		resi /= resi_div;
		if( resi < 1 )
			resi = 1;
	}

	if( chr->abl.hp.n < hp ){
		clr_chr_trgt_act( chr, TRUE );
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_HP_SHORT, chr->name,
				hp - chr->abl.hp.n );
		return;
	}
	if( chr->abl.mp.n < mp ){
		clr_chr_trgt_act( chr, TRUE );
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_MP_SHORT, chr->name,
				mp - chr->abl.mp.n );
		return;
	}
	if( resi > 0 ){
		resi_kind_t	kind;
		rate_t	d;

		kind = tab->resi_vfx;
		if( kind >= RESI_KIND_MAX_N )
			kind = tab->resi;

		if( kind < 0 )
			return;
		if( kind >= RESI_KIND_MAX_N )
			return;

		d = chr->resi[kind].n - resi;
		if( d <= 0 ){
			clr_chr_trgt_act( chr, TRUE );
			print_msg_mbr( chr, FLG_NULL,
					MSG_ERR_RESI_SHORT,
					chr->name, (long)-d + 1 );
			return;
		}

		add_resi( chr, kind, -resi, TRUE );
	}

	add_mp( chr, -mp, TRUE );
	if( add_hp( chr, -hp, TRUE, FALSE ) <= 0 )
		return;

	draw_mbr_stat( chr );

	flg_msg = TRUE;
	do {
		spell_tab_t	*pre_tab;

		pre_tab = (spell_tab_t *)(chr->pre_act.p);

		if( tab->abl != ABL_KIND_BAR )
			break;
		if( chr->pre_act.kind != ACT_KIND_SPELL )
			break;
		if( pre_tab == NULL )
			break;
		if( pre_tab->abl != ABL_KIND_BAR )
			break;
		if( tab->kind != pre_tab->kind )
			break;

		/* 呪歌のメッセージは初めだけ */

		flg_msg = FALSE;
	} while( 0 );

	inst_spell_name = NULL;
	if( tab->abl == ABL_KIND_BAR ){
		spell_kind_t	kind;

		kind = get_inst_spell_kind( (mbr_t *)chr );
		if( kind != SPELL_KIND_NULL ){
			inst_spell_name = get_spell_name( kind );
		}
	}

	if( flg_msg ){
		play_sound_spell( chr, tab->kind );

		if( fmt == NULL ){
			print_msg( FLG_NULL, MSG_SPELL,
					chr->name, tab->name );
			if( inst_spell_name != NULL ){
				print_msg( FLG_NULL, MSG_SPELL,
						chr->name,
						inst_spell_name );
			}
		} else {
			print_msg( FLG_NULL, fmt,
					chr->name );
		}
	}

	get_vfx_attr( &prev_attr );
	set_vfx_attr_n( CURS_ATTR_N_VFX );

	switch( (extent_kind_t)(chr->act.n) ){
	case EXTENT_KIND_NULL:
	case EXTENT_KIND_MAX_N:
		break;
	case EXTENT_KIND_NORMAL:
		if( (SPELL_KIND_BAR_MIN_N <= tab->kind)
				&& (tab->kind <= SPELL_KIND_BAR_MAX_N) ){
			break;
		}
		chr_cast_spell_normal( chr, FALSE, tab, _100_PERCENT );
		break;
	case EXTENT_KIND_SPREAD:
		chr_cast_spell_spread( chr, FALSE, tab, _100_PERCENT );
		break;
	case EXTENT_KIND_MASS:
		chr_cast_spell_mass( chr, FALSE, tab, _100_PERCENT );
		break;
	case EXTENT_KIND_LIMIT:
		break;
	case EXTENT_KIND_HALF:
		chr_cast_spell_normal( chr, FALSE, tab, (rate_t)50 );
		break;
	case EXTENT_KIND_DOUBLE:
		chr_cast_spell_normal( chr, FALSE, tab, (rate_t)200 );
		break;
	}

	fx_cast_spell( chr, tab );

	set_vfx_attr( &prev_attr );

	/* 統計を取る */

	if( is_mbr( chr ) ){
		update_playing_report_using_spell(
				chr->ls_mbr_n, tab->kind );
	}
	if( chr->trgt.kind == TRGT_KIND_MBR){
		mbr_t	*mbr;

		mbr = (mbr_t *)(chr->trgt.p);
		update_playing_report_used_spell(
				mbr->ls_mbr_n, tab->kind );
	}
}

/**/

void	play_sound_spell( chr_t *chr, spell_kind_t kind )
{
	if( (SPELL_KIND_MAG_MIN_N < kind)
			&& (kind < SPELL_KIND_MAG_MAX_N) ){
		call_game_sound_play( SOUND_KIND_SPELL_MAG, 1 );
	}
	if( (SPELL_KIND_SOR_MIN_N < kind)
			&& (kind < SPELL_KIND_SOR_MAX_N) ){
		call_game_sound_play( SOUND_KIND_SPELL_SOR, 1 );
	}
	if( (SPELL_KIND_ENC_MIN_N < kind)
			&& (kind < SPELL_KIND_ENC_MAX_N) ){
		call_game_sound_play( SOUND_KIND_SPELL_ENC, 1 );
	}
	if( (SPELL_KIND_SUM_MIN_N < kind)
			&& (kind < SPELL_KIND_SUM_MAX_N) ){
		call_game_sound_play( SOUND_KIND_SPELL_SUM, 1 );
	}
	if( (SPELL_KIND_PRI_MIN_N < kind)
			&& (kind < SPELL_KIND_PRI_MAX_N) ){
		call_game_sound_play( SOUND_KIND_SPELL_PRI, 1 );
	}
	if( (SPELL_KIND_SHA_MIN_N < kind)
			&& (kind < SPELL_KIND_SHA_MAX_N) ){
		call_game_sound_play( SOUND_KIND_SPELL_SHA, 1 );
	}
	if( (SPELL_KIND_BAR_MIN_N < kind)
			&& (kind < SPELL_KIND_BAR_MAX_N) ){
		call_game_sound_play( SOUND_KIND_SPELL_BAR, 1 );
	}
	if( (SPELL_KIND_NIN_MIN_N < kind)
			&& (kind < SPELL_KIND_NIN_MAX_N) ){
		call_game_sound_play( SOUND_KIND_SPELL_NIN, 1 );
	}
}

/**/

void	chr_cast_spell_normal(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
)
{
	long	x, y;
	trgt_kind_t	trgt_kind;
	void	*p;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	if( tab->flg_trgt ){
		x = chr->trgt.true_x;
		y = chr->trgt.true_y;
		trgt_kind = chr->trgt.kind;
		p = chr->trgt.p;
	} else {
		x = chr->x;
		y = chr->y;
		trgt_kind = TRGT_KIND_NULL;
		p = NULL;
	}

	g_vfx_n = 1;
	g_vfx_bgn[0].x = chr->x * 2;
	g_vfx_bgn[0].y = chr->y;
	g_vfx_end[0].x = x * 2;
	g_vfx_end[0].y = y;
	if( trgt_kind != TRGT_KIND_NULL )
		vfx_spell( tab, g_vfx_n, g_vfx_bgn, g_vfx_end );

	chr_cast_spell_sub( chr, flg_item, tab, rate,
			x, y, trgt_kind, p );
}

/**/

void	chr_cast_spell_spread(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
)
{
	long	x, y;
	trgt_kind_t	trgt_kind;
	void	*p;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	if( tab->flg_trgt ){
		x = chr->trgt.true_x;
		y = chr->trgt.true_y;
		trgt_kind = chr->trgt.kind;
		p = chr->trgt.p;
	} else {
		x = chr->x;
		y = chr->y;
		trgt_kind = TRGT_KIND_NULL;
		p = NULL;
	}

	g_vfx_n = 1;
	g_vfx_bgn[0].x = chr->x * 2;
	g_vfx_bgn[0].y = chr->y;
	g_vfx_end[0].x = x * 2;
	g_vfx_end[0].y = y;
	if( trgt_kind != TRGT_KIND_NULL )
		vfx_spell( tab, g_vfx_n, g_vfx_bgn, g_vfx_end );

	chr_cast_spell_blast( chr, flg_item, tab, rate,
			x, y, trgt_kind, p );
}

/**/

void	chr_cast_spell_blast(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate,
	long x, long y, trgt_kind_t trgt_kind, void *p
)
{
	blast_t	*blast;
	char	*blast_str;
	gui_vfx_t	*gui_vfx;
	long	nx, ny;
	long	xx, yy;
	bool_t	flg_actual;
	bool_t	flg_pet;
	chr_kind_t	kind;
	chr_t	*trgt_chr;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	if( trgt_kind == TRGT_KIND_MBR )
		kind = CHR_KIND_MBR;
	else if( trgt_kind == TRGT_KIND_MNSTR )
		kind = CHR_KIND_MNSTR;
	else if( trgt_kind == TRGT_KIND_MNSTR_NULL )
		kind = CHR_KIND_MNSTR;
	else
		kind = CHR_KIND_NULL;

	if( is_pet( (pet_t *)(chr->trgt.p) ) )
		flg_pet = TRUE;
	else
		flg_pet = FALSE;

	if( is_mnstr( chr ) ){
		if( chk_flg( chr->flg_map, FLG_MAP_CHR_FIND ) ){
			call_game_sound_play(
					SOUND_KIND_BLAST_MONSTER, 1 );
		}
	} else if( is_mbr( chr ) ){
		if( chk_flg( chr->flg_map, FLG_MAP_CHR_FIND ) ){
			call_game_sound_play(
					SOUND_KIND_BLAST_MEMBER, 1 );
		}
	}

	/* GUI */
	gui_vfx = alloc_gui_vfx_blast( BLAST_KIND_STD );

	blast = get_blast_spell( tab->kind );
	blast_str = get_spell_vfx_str( tab->kind );
	draw_blast( kind, x, y, blast, gui_vfx, blast_str );
	if( clip_draw_pos( x, y ) )
		wait_clock( ANIM_FRAME_N_BLAST_STD );

	flg_actual = chk_flg( get_flg_party(), FLG_PARTY_ACTUAL_FIGHTING );

	clr_all_chr_flg_blast();
	bgn_sync_vfx_num();

	for( ny = 0; ny < blast->yl; ny++ ){
		for( nx = 0; nx < blast->xl / 2; nx++ ){
			if( blast->ptn[ny][nx * 2] == ' ' )
				continue;

			xx = x + nx - (blast->xr / 2);
			yy = y + ny - blast->yr;

			trgt_chr = NULL;
			p = NULL;

			switch( trgt_kind ){
			case TRGT_KIND_MBR:
				trgt_chr = get_mbr( xx, yy );
				p = trgt_chr;
				break;
			case TRGT_KIND_NULL:
			case TRGT_KIND_MNSTR:
			case TRGT_KIND_MNSTR_NULL:
			case TRGT_KIND_SQUARE:
			case TRGT_KIND_POS:
				trgt_kind = TRGT_KIND_MNSTR;

				trgt_chr = get_mnstr( xx, yy );
				p = trgt_chr;
				if( p == NULL )
					break;
				if( p == chr )
					continue;

				if( flg_pet )
					break;
				if( flg_actual )
					break;
				if( is_mnstr( chr ) )
					break;
				if( ((mnstr_t *)p)->attitude
						== ATTITUDE_ENEMY ){
					break;
				}
				continue;

				break;
			case TRGT_KIND_ITEM:
				p = get_item( xx, yy );
				break;
			case TRGT_KIND_DOOR:
				p = get_door( xx, yy );
				break;
			case TRGT_KIND_TRAP:
				p = get_trap( xx, yy );
				break;
			case TRGT_KIND_QUEUE:
			case TRGT_KIND_AUTO:
			case TRGT_KIND_MAX_N:
				continue;
			}
			if( p == NULL )
				continue;

			/* 既に爆風に当っていたら無効 */

			if( trgt_chr != NULL ){
				if( chk_flg( trgt_chr->work.flg,
						FLG_WORK_BLAST_END ) ){
					continue;
				}

				trgt_chr->work.flg |= FLG_WORK_BLAST_END;
			}

			draw_blast( kind, x, y, blast,
					gui_vfx, blast_str );
			draw_map( xx, yy, 1, 1 );

			chr_cast_spell_sub( chr, flg_item, tab, rate,
					xx, yy, trgt_kind, p );
		}
	}

	end_sync_vfx_num();
	clr_all_chr_flg_blast();

	draw_blast( kind, x, y, blast, gui_vfx, blast_str );
	if( clip_draw_pos( x, y ) )
		wait_clock( ANIM_FRAME_N_BLAST_STD );

	/* GUI */
	clr_gui_vfx_all();
	free_gui_vfx( gui_vfx );
	call_pcg_dun_redraw( TRUE );

	xx = x - (blast->xr / 2);
	yy = y - blast->yr;
	nx = (blast->xl + str_len_draw( blast_str )) / 2;
	ny = blast->yl;
	draw_map_force( xx, yy, nx, ny );
}

/**/

void	chr_cast_spell_mass(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
)
{
	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	if( !tab->flg_trgt ){
		chr_cast_spell_normal( chr, flg_item, tab, rate );
		return;
	}

	bgn_sync_vfx_num();

	switch( chr->trgt.kind ){
	case TRGT_KIND_NULL:
	case TRGT_KIND_SQUARE:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		break;
	case TRGT_KIND_MBR:
		chr_cast_spell_mass_mbr( chr, flg_item, tab, rate );
		break;
	case TRGT_KIND_MNSTR:
	case TRGT_KIND_MNSTR_NULL:
	case TRGT_KIND_POS:
		if( is_pet( (pet_t *)(chr->trgt.p) ) ){
			chr_cast_spell_mass_pet(
					chr, flg_item, tab, rate );
		} else {
			chr_cast_spell_mass_mnstr(
					chr, flg_item, tab, rate );
		}
		break;
	case TRGT_KIND_ITEM:
		chr_cast_spell_mass_item( chr, flg_item, tab, rate );
		break;
	case TRGT_KIND_DOOR:
		chr_cast_spell_mass_door( chr, flg_item, tab, rate );
		break;
	case TRGT_KIND_TRAP:
		chr_cast_spell_mass_trap( chr, flg_item, tab, rate );
		break;
	case TRGT_KIND_QUEUE:
		break;
	}

	end_sync_vfx_num();
}

/**/

void	chr_cast_spell_mass_mbr(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
)
{
	party_t	*pty = get_party();
	long	i;
	pos_t	pos1, pos2;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	g_vfx_n = 0;

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		pos1.x = chr->x;
		pos1.y = chr->y;
		pos2.x = pty->mbr[i]->x;
		pos2.y = pty->mbr[i]->y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( g_vfx_n < VFX_ARW_MAX_N ){
			g_vfx_bgn[g_vfx_n].x = pos1.x * 2;
			g_vfx_bgn[g_vfx_n].y = pos1.y;
			g_vfx_end[g_vfx_n].x = pos2.x * 2;
			g_vfx_end[g_vfx_n].y = pos2.y;
			g_vfx_n++;
		}
	}

	vfx_spell( tab, g_vfx_n, g_vfx_bgn, g_vfx_end );

	for( i = 0; i < MBR_MAX_N; i++ ){
		if( chk_flg_or( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		pos1.x = chr->x;
		pos1.y = chr->y;
		pos2.x = pty->mbr[i]->x;
		pos2.y = pty->mbr[i]->y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		chr_cast_spell_sub( chr, flg_item, tab, rate,
				pty->mbr[i]->x, pty->mbr[i]->y,
				TRGT_KIND_MBR, pty->mbr[i] );
	}
}

/**/

void	chr_cast_spell_mass_pet(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
)
{
	pet_t	**pet = get_party_pet();
	long	i;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	g_vfx_n = 0;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet[i] == NULL )
			continue;
		if( chk_flg_or( pet[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( !chk_find_chr( chr, pet[i] ) )
			continue;

		if( g_vfx_n < VFX_ARW_MAX_N ){
			g_vfx_bgn[g_vfx_n].x = chr->x * 2;
			g_vfx_bgn[g_vfx_n].y = chr->y;
			g_vfx_end[g_vfx_n].x = pet[i]->x * 2;
			g_vfx_end[g_vfx_n].y = pet[i]->y;
			g_vfx_n++;
		}
	}

	vfx_spell( tab, g_vfx_n, g_vfx_bgn, g_vfx_end );

	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet[i] == NULL )
			continue;
		if( chk_flg_or( pet[i]->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( !chk_find_chr( chr, pet[i] ) )
			continue;

		chr_cast_spell_sub( chr, flg_item, tab, rate,
				pet[i]->x, pet[i]->y,
				TRGT_KIND_MNSTR, pet[i] );
	}
}

/**/

void	chr_cast_spell_mass_mnstr(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
)
{
	mnstr_t	*mns_head, *mns_p, *mns_pp;
	bool_t	flg_actual;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	flg_actual = chk_flg( get_flg_party(), FLG_PARTY_ACTUAL_FIGHTING );

	g_vfx_n = 0;

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next->next; mns_p != NULL;
			mns_p = mns_p->next ){
		mns_pp = mns_p->prev;
		if( mns_pp == mns_head )
			break;

		if( chk_flg_or( mns_pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( !chk_find_chr( chr, mns_pp ) )
			continue;
		if( !flg_actual && !is_mnstr( chr ) )
			if( mns_pp->attitude != ATTITUDE_ENEMY )
				continue;

		if( g_vfx_n < VFX_ARW_MAX_N ){
			g_vfx_bgn[g_vfx_n].x = chr->x * 2;
			g_vfx_bgn[g_vfx_n].y = chr->y;
			g_vfx_end[g_vfx_n].x = mns_pp->x * 2;
			g_vfx_end[g_vfx_n].y = mns_pp->y;
			g_vfx_n++;
		}
	}

	vfx_spell( tab, g_vfx_n, g_vfx_bgn, g_vfx_end );

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next->next; mns_p != NULL;
			mns_p = mns_p->next ){
		mns_pp = mns_p->prev;
		if( mns_pp == mns_head )
			break;

		if( chk_flg_or( mns_pp->stat,
				FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
			continue;
		}

		if( !chk_find_chr( chr, mns_pp ) )
			continue;
		if( !flg_actual && !is_mnstr( chr ) )
			if( mns_pp->attitude != ATTITUDE_ENEMY )
				continue;

		chr_cast_spell_sub( chr, flg_item, tab, rate,
				mns_pp->x, mns_pp->y,
				TRGT_KIND_MNSTR, mns_pp );
	}
}

/**/

void	chr_cast_spell_mass_item(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
)
{
	item_t	*item, *head, *p;
	pos_t	pos1, pos2;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	g_vfx_n = 0;

	head = get_dun_item_asgn();
	for( item = head->next->next; item->prev != head;
			item = item->next ){
		p = item->prev;

		pos1.x = chr->x;
		pos1.y = chr->y;
		pos2.x = p->x;
		pos2.y = p->y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( g_vfx_n < VFX_ARW_MAX_N ){
			g_vfx_bgn[g_vfx_n].x = pos1.x * 2;
			g_vfx_bgn[g_vfx_n].y = pos1.y;
			g_vfx_end[g_vfx_n].x = pos2.x * 2;
			g_vfx_end[g_vfx_n].y = pos2.y;
			g_vfx_n++;
		}
	}

	vfx_spell( tab, g_vfx_n, g_vfx_bgn, g_vfx_end );

	for( item = head->next->next; item->prev != head;
			item = item->next ){
		p = item->prev;

		pos1.x = chr->x;
		pos1.y = chr->y;
		pos2.x = p->x;
		pos2.y = p->y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		chr_cast_spell_sub( chr, flg_item, tab, rate,
				p->x, p->y, TRGT_KIND_ITEM, p );
	}
}

/**/

void	chr_cast_spell_mass_door(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
)
{
	dun_t	*dun = get_dun();
	long	i;
	pos_t	pos1, pos2;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	g_vfx_n = 0;

	for( i = 0; i < dun->door_n; i++ ){
		pos1.x = chr->x;
		pos1.y = chr->y;
		pos2.x = dun->door[i].x;
		pos2.y = dun->door[i].y;
		get_near_pos_door( &pos2, &(dun->door[i]), chr );

		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( g_vfx_n < VFX_ARW_MAX_N ){
			g_vfx_bgn[g_vfx_n].x = pos1.x * 2;
			g_vfx_bgn[g_vfx_n].y = pos1.y;
			g_vfx_end[g_vfx_n].x = pos2.x * 2;
			g_vfx_end[g_vfx_n].y = pos2.y;
			g_vfx_n++;
		}
	}

	vfx_spell( tab, g_vfx_n, g_vfx_bgn, g_vfx_end );

	for( i = 0; i < dun->door_n; i++ ){
		pos1.x = chr->x;
		pos1.y = chr->y;
		pos2.x = dun->door[i].x;
		pos2.y = dun->door[i].y;
		get_near_pos_door( &pos2, &(dun->door[i]), chr );

		if( !chk_find( &pos1, &pos2 ) )
			continue;

		chr_cast_spell_sub( chr, flg_item, tab, rate,
				dun->door[i].x, dun->door[i].y,
				TRGT_KIND_DOOR, &(dun->door[i]) );
	}
}

/**/

void	chr_cast_spell_mass_trap(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
)
{
	trap_t	*trap, *head, *p;
	pos_t	pos1, pos2;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	g_vfx_n = 0;

	head = get_dun_trap_asgn();
	for( trap = head->next->next; trap->prev != head;
			trap = trap->next ){
		p = trap->prev;

		pos1.x = chr->x;
		pos1.y = chr->y;
		pos2.x = p->x;
		pos2.y = p->y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		if( g_vfx_n < VFX_ARW_MAX_N ){
			g_vfx_bgn[g_vfx_n].x = pos1.x * 2;
			g_vfx_bgn[g_vfx_n].y = pos1.y;
			g_vfx_end[g_vfx_n].x = pos2.x * 2;
			g_vfx_end[g_vfx_n].y = pos2.y;
			g_vfx_n++;
		}
	}

	vfx_spell( tab, g_vfx_n, g_vfx_bgn, g_vfx_end );

	for( trap = head->next->next; trap->prev != head;
			trap = trap->next ){
		p = trap->prev;

		pos1.x = chr->x;
		pos1.y = chr->y;
		pos2.x = p->x;
		pos2.y = p->y;
		if( !chk_find( &pos1, &pos2 ) )
			continue;

		chr_cast_spell_sub( chr, flg_item, tab, rate,
				p->x, p->y, TRGT_KIND_TRAP, p );
	}
}

/**/

void	chr_cast_spell_sub(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate,
	long x, long y, trgt_kind_t trgt_kind, void *p
)
{
	bool_t	flg_chr;
	chr_t	*d_p;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;
	if( !chk_cast_spell_trgt( tab->kind, trgt_kind ) )
		return;

	if( (trgt_kind == TRGT_KIND_MBR)
			|| (trgt_kind == TRGT_KIND_MNSTR) ){
		flg_chr = TRUE;
		d_p = (chr_t *)p;
	} else {
		flg_chr = FALSE;
		d_p = (chr_t *)NULL;
	}

#if	(! FLG_SPELL_SANCTUARY)
	/* 聖域の上では祈り以外はとどかない */

	do {
		if( get_scene() == SCENE_N_LAST_BOSS )
			break;
		if( tab->abl == ABL_KIND_PRI )
			break;

		if( chk_map_sanctuary( chr->x, chr->y ) ){
			if( is_mbr( chr ) ){
				curs_attrset_chr( chr, -1, FALSE );
				print_msg( FLG_NULL,
						MSG_FAIL_SPELL_SANCTUARY,
						chr->name );
				curs_attrset_dflt();
			}

			return;
		}
		if( chk_map_sanctuary( x, y ) )
			return;

		break;
	} while( 0 );
#endif	/* ENABLE_SPELL_SANCTUARY */

	/* 目標に視線が通っているかチェック */

	if( trgt_kind == TRGT_KIND_DOOR ){
		;/**/
	} else if( !flg_chr || (trgt_kind == TRGT_KIND_MNSTR_NULL)
			||  (trgt_kind == TRGT_KIND_POS) ){
		pos_t	pos1, pos2;

		pos1.x = chr->x;
		pos1.y = chr->y;
		pos2.x = x;
		pos2.y = y;
		if( !chk_find( &pos1, &pos2 ) )
			return;
	} else {
		if( !chk_find_chr( chr, d_p ) )
			return;
	}

	/* 見えないモンスターがいるかチェック */

	if( (trgt_kind == TRGT_KIND_MNSTR_NULL)
			|| (trgt_kind == TRGT_KIND_POS) ){
		mnstr_t	*mnstr;

		mnstr = get_mnstr( x, y );
		if( mnstr != NULL ){
			trgt_kind = TRGT_KIND_MNSTR;
			p = mnstr;
		}
	}

	/* 金貨を消費する呪文 */

	if( flg_chr ){
		if( d_p->gold < tab->gold ){
			clr_chr_trgt_act( chr, TRUE );
			print_msg_mbr( d_p, FLG_NULL, MSG_ERR_GOLD_SHORT,
					d_p->name, tab->gold - d_p->gold );

			return;
		} else {
			d_p->gold -= tab->gold;
		}
	}

	/* 呪文が成功するかチェック */

	if( flg_chr && !chk_spell( chr, tab, flg_item ) ){
		curs_attrset_chr( chr, -1, FALSE );
		print_msg_find( chr, FLG_NULL, MSG_FAIL_SPELL,
				chr->name, tab->name );
		curs_attrset_dflt();

		return;
	}

	/* 呪文が抵抗されるかチェック */

	if( flg_chr && (tab->resi != RESI_KIND_MAX_N)
			&& resi_roll( chr, tab->abl, d_p, tab->resi ) ){
		curs_attrset_chr( d_p, +1, FALSE );
		print_msg_find( d_p, FLG_NULL, MSG_RESI_SPELL,
				d_p->name, tab->name );
		curs_attrset_dflt();

		counter_magic( chr, flg_item, tab, rate,
				x, y, trgt_kind, d_p );

		return;
	}

	/* 呪文がはじかれるかチェック */

	if( flg_chr && chk_flg( d_p->stat, FLG_STAT_IRON_BODY ) ){
		curs_attrset_chr( d_p, +1, FALSE );
		print_msg_find( d_p, FLG_NULL, MSG_REPEL_SPELL,
				d_p->name, tab->name );
		curs_attrset_dflt();

		return;
	}

	/* 呪文がスキルで抵抗されるかチェック */

	do {
		flg_stat_t	stat;
		skill_kind_t	skill;
		long	per;

		stat = cv_spell_to_stat( tab->kind );
		if( stat == FLG_STAT_NULL )
			break;

		skill = cv_stat_to_skill_stat( stat );
		if( skill == SKILL_KIND_NULL )
			break;

		if( !chk_ena_skill( d_p, skill ) )
			break;

		per = calc_skill_rate( d_p, skill );
		if( per_randm( per ) )
			break;

		curs_attrset_chr( d_p, +1, FALSE );
		print_msg_find( d_p, FLG_NULL,
				MSG_RESI_SPELL_SKILL,
				d_p->name, tab->name );
		curs_attrset_dflt();

		return;
	} while( 0 );

	switch( tab->kind ){
	case SPELL_KIND_NULL:
		break;
/* MAG */
	case SPELL_KIND_MAG_MIN_N:
		break;
	case SPELL_KIND_LIGHT:
		fx_light( x, y );
		break;
	case SPELL_KIND_DARKNESS:
		fx_darkness( x, y );
		break;
	case SPELL_KIND_STORE_LIGHT:
		fx_store_light( chr );
		break;
	case SPELL_KIND_SHORT_TELEPORT_PARTY:
		fx_short_teleport_party( chr->x, chr->y );
		break;
	case SPELL_KIND_TELEPORT_PARTY:
		fx_teleport_party_charge();
		break;
	case SPELL_KIND_TELEPORT:
		fx_teleport( trgt_kind, p );
		break;
	case SPELL_KIND_RECALL:
		fx_recall();
		break;
	case SPELL_KIND_KNOCK:
		if( trgt_kind == TRGT_KIND_ITEM )
			chr_open_item( chr, get_item( x, y ) );
		else
			fx_knock( get_door( x, y ) );
		break;
	case SPELL_KIND_LOCK:
		fx_lock( get_door( x, y ) );
		break;
	case SPELL_KIND_DISARM_TRAP:
		if( trgt_kind == TRGT_KIND_ITEM ){
			chr_disarm_item_abl( chr, get_item( x, y ),
					ABL_KIND_MAG, ABL_KIND_INT );
		} else {
			fx_disarm_trap( get_trap( x, y ), chr );
		}
		break;
	case SPELL_KIND_ANIMATE_OBJECTS:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_SHELTER:
		fx_shelter( x, y );
		break;
	case SPELL_KIND_CREATE_FOOD:
		fx_create_food( chr );
		break;
	case SPELL_KIND_IDENTIFY_ITEM:
		exec_menu_identify_item( chr );
		break;
	case SPELL_KIND_IDENTIFY_ALL_ITEM:
		fx_identify_all_item( (chr_t *)p );
		break;
	case SPELL_KIND_SEARCHING:
		fx_detect_item( chr );
		fx_detect_door( chr );
		fx_detect_trap( chr );
		break;
	case SPELL_KIND_ANALYZE_DWEOMER:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_DETECT_MAGIC:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_DETECT_ITEM:
		fx_detect_item( chr );
		break;
	case SPELL_KIND_DETECT_DOORS:
		fx_detect_door( chr );
		break;
	case SPELL_KIND_DETECT_TRAPS:
		fx_detect_trap( chr );
		break;
	case SPELL_KIND_DETECT_MONSTER:
		fx_detect_mnstr( chr );
		break;
	case SPELL_KIND_SENSE_INVISIBLE:
	case SPELL_KIND_FLY:
		fx_std( (chr_t *)p, cv_spell_to_fx( tab->kind ) );
		break;
	case SPELL_KIND_FEATHER_FALL:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_VANISH:
		fx_std( (chr_t *)p, cv_spell_to_fx( tab->kind ) );
		break;
	case SPELL_KIND_DARKVISION:
		fx_darkvision( (chr_t *)p );
		break;
	case SPELL_KIND_PASSWALL:
		fx_std( (chr_t *)p, cv_spell_to_fx( tab->kind ) );
		break;
	case SPELL_KIND_DISPEL_MAGIC:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_MIRROR_IMAGE:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_POLYMORPH_OTHER:
		fx_polymorph( (chr_t *)p );
		break;
	case SPELL_KIND_POLYMORPH_SELF:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_STEALTH:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_MAG_MAX_N:
		break;
/* SOR */
	case SPELL_KIND_SOR_MIN_N:
		break;
	case SPELL_KIND_MAGIC_MISSILE:
		fx_magic_missile( chr, trgt_kind, (chr_t *)p, rate );
		break;
	case SPELL_KIND_FIRE_BALL:
		fx_spell_attack( chr, trgt_kind, (chr_t *)p, RESI_KIND_HEAT,
				ABL_KIND_SOR, rate );
		break;
	case SPELL_KIND_ICE_BLIZZARD:
		fx_spell_attack( chr, trgt_kind, (chr_t *)p, RESI_KIND_COLD,
				ABL_KIND_SOR, rate );
		break;
	case SPELL_KIND_MIND_STORM:
		fx_spell_attack( chr, trgt_kind, (chr_t *)p, RESI_KIND_MIND,
				ABL_KIND_SOR, rate );
		break;
	case SPELL_KIND_ACID_RAIN:
		fx_spell_attack( chr, trgt_kind, (chr_t *)p, RESI_KIND_ACID,
				ABL_KIND_SOR, rate );
		break;
	case SPELL_KIND_LIGHTNING_BOLT:
		fx_spell_attack( chr, trgt_kind, (chr_t *)p, RESI_KIND_ELEC,
				ABL_KIND_SOR, rate );
		break;
	case SPELL_KIND_POISON_CLOUD:
		fx_spell_attack( chr, trgt_kind, (chr_t *)p, RESI_KIND_POIS,
				ABL_KIND_SOR, rate );
		break;
	case SPELL_KIND_DEATH_SPELL:
		fx_death_spell( chr, trgt_kind, p );
		break;
	case SPELL_KIND_WORD_OF_DESTRUCTION:
		rate = rate * WORD_OF_DESTRUCTION_RATE / _100_PERCENT;
		fx_magic_missile( chr, trgt_kind, (chr_t *)p, rate );
		break;
	case SPELL_KIND_MAGIC_SHIELD:
		fx_magic_wpn_armor( (chr_t *)p, FX_KIND_MAGIC_SHIELD );
		break;
	case SPELL_KIND_MAGE_ARMOR:
		fx_magic_wpn_armor( (chr_t *)p, FX_KIND_MAGE_ARMOR );
		break;
	case SPELL_KIND_STONESKIN:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_IRON_BODY:
		fx_std( (chr_t *)p, cv_spell_to_fx( tab->kind ) );
		break;
	case SPELL_KIND_SPELL_RESISTANCE:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_COUNTER_MAGIC:
		fx_std( (chr_t *)p, FX_KIND_COUNTER_MAGIC );
		break;
	case SPELL_KIND_STONE:
	case SPELL_KIND_PARALYZE:
	case SPELL_KIND_POISON:
	case SPELL_KIND_CONFUSION:
	case SPELL_KIND_BLINDNESS:
	case SPELL_KIND_SLEEP:
	case SPELL_KIND_SILENCE:
	case SPELL_KIND_FEAR:
	case SPELL_KIND_HALLUCINATION:
	case SPELL_KIND_CHARM:
		fx_std( (chr_t *)p, cv_spell_to_fx( tab->kind ) );
		break;
	case SPELL_KIND_SOR_MAX_N:
		break;
/* ENC */
	case SPELL_KIND_ENC_MIN_N:
		break;
	case SPELL_KIND_SHARPNESS:
		fx_abl( (chr_t *)p, FX_KIND_SHARPNESS );
		break;
	case SPELL_KIND_STRENGTH:
		fx_abl( (chr_t *)p, FX_KIND_STRENGTH );
		break;
	case SPELL_KIND_QUICKNESS:
		fx_abl( (chr_t *)p, FX_KIND_QUICKNESS );
		break;
	case SPELL_KIND_BRAINY:
		fx_abl( (chr_t *)p, FX_KIND_BRAINY );
		break;
	case SPELL_KIND_WISE:
		fx_abl( (chr_t *)p, FX_KIND_WISE );
		break;
	case SPELL_KIND_ATTRACTIVE:
		fx_abl( (chr_t *)p, FX_KIND_ATTRACTIVE );
		break;
	case SPELL_KIND_POWER_UP_HP:
		fx_pow_up_hp( (chr_t *)p );
		break;
	case SPELL_KIND_HASTE:
		fx_speed_up( chr, (chr_t *)p, +1 );
		break;
	case SPELL_KIND_DULLNESS:
		fx_abl( (chr_t *)p, FX_KIND_DULLNESS );
		break;
	case SPELL_KIND_WEAKNESS:
		fx_abl( (chr_t *)p, FX_KIND_WEAKNESS );
		break;
	case SPELL_KIND_SLOWNESS:
		fx_abl( (chr_t *)p, FX_KIND_SLOWNESS );
		break;
	case SPELL_KIND_BRAINLESS:
		fx_abl( (chr_t *)p, FX_KIND_BRAINLESS );
		break;
	case SPELL_KIND_FOOLISH:
		fx_abl( (chr_t *)p, FX_KIND_FOOLISH );
		break;
	case SPELL_KIND_UNATTRACTIVE:
		fx_abl( (chr_t *)p, FX_KIND_UNATTRACTIVE );
		break;
	case SPELL_KIND_ENERGY_DRAIN:
		fx_energy_drain( (chr_t *)p, FALSE );

		if( chr->kind != CHR_KIND_MNSTR )
			break;
		if( is_pet( chr ) )
			break;
		if( !is_mbr( (chr_t *)p ) )
			break;
		chr->work.flg_used_energy_drain = TRUE;

		break;
	case SPELL_KIND_SLOW:
		fx_speed_up( chr, (chr_t *)p, -1 );
		break;
	case SPELL_KIND_HUNGER:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_CANCELLATION:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_ENC_MAX_N:
		break;
/* SUM */
	case SPELL_KIND_SUM_MIN_N:
		break;
	case SPELL_KIND_SKELETON_WARRIOR:
		fx_summon_monster( chr, MNSTR_KIND_SKELETON,
				SKELETON_WARRIOR_STD_N,
				DISMISSAL_TURN_SKELETON );
		break;
	case SPELL_KIND_SUMMON_UNICORN:
		fx_summon_monster( chr, MNSTR_KIND_UNICORN, 1,
				DISMISSAL_TURN_UNICORN );
		break;
	case SPELL_KIND_SUMMON_EFREET:
		fx_summon_monster( chr, MNSTR_KIND_EFREET, 1,
				DISMISSAL_TURN_EFREET );
		break;
	case SPELL_KIND_SUMMON_DJINNI:
		fx_summon_monster( chr, MNSTR_KIND_DJINNI, 1,
				DISMISSAL_TURN_DJINNI );
		break;
	case SPELL_KIND_SUMMON_PHOENIX:
		fx_summon_monster( chr, MNSTR_KIND_PHOENIX, 1,
				DISMISSAL_TURN_PHOENIX );
		break;
	case SPELL_KIND_SUMMON_BONE:
		fx_summon_bone( chr, DISMISSAL_TURN_BONE );
		break;
	case SPELL_KIND_SUMMON_RANDOM:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_CREATE_UNDEAD:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_DISMISSAL:
		fx_dismissal( (chr_t *)p );
		break;
	case SPELL_KIND_SUM_MAX_N:
		break;
/* PRI */
	case SPELL_KIND_PRI_MIN_N:
		break;
	case SPELL_KIND_CURE_HP_LIGHT:
		fx_cure_hp_light( (chr_t *)p, get_lev( chr, ABL_KIND_PRI ) );
		break;
	case SPELL_KIND_CURE_HP_MODERATE:
		fx_cure_hp_moderate( (chr_t *)p,
				get_lev( chr, ABL_KIND_PRI ) );
		break;
	case SPELL_KIND_CURE_HP_SERIOUS:
		fx_cure_hp_serious( (chr_t *)p, get_lev( chr, ABL_KIND_PRI ) );
		break;
	case SPELL_KIND_CURE_HP_MAX:
		fx_cure_hp_max( (chr_t *)p, get_lev( chr, ABL_KIND_PRI ) );
		break;
	case SPELL_KIND_CURE_MP:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_TRANSFER_MP:
		fx_transfer_mp( (chr_t *)p, tab, rate );
		break;
	case SPELL_KIND_REGENERATION:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_RESTORE_EXPERIENCE:
		fx_cure_exp( (chr_t *)p );
		break;
	case SPELL_KIND_RESURRECTION:
		exec_menu_resurrection( chr );
		break;
	case SPELL_KIND_HEAL:
		fx_heal( (chr_t *)p );
		break;
	case SPELL_KIND_CURE_STATUS:
		fx_cure_all_stat( (chr_t *)p );
		break;
	case SPELL_KIND_CURE_STONE:
		fx_cure_stat( (chr_t *)p, FX_KIND_STONE );
		break;
	case SPELL_KIND_CURE_PARALYZE:
		fx_cure_stat( (chr_t *)p, FX_KIND_PARALYZE );
		break;
	case SPELL_KIND_CURE_POISON:
		fx_cure_stat( (chr_t *)p, FX_KIND_POISON );
		break;
	case SPELL_KIND_CURE_CONFUSION:
		fx_cure_stat( (chr_t *)p, FX_KIND_CONFUSION );
		break;
	case SPELL_KIND_CURE_BLINDNESS:
		fx_cure_stat( (chr_t *)p, FX_KIND_BLIND );
		break;
	case SPELL_KIND_CURE_SLEEP:
		fx_cure_stat( (chr_t *)p, FX_KIND_SLEEP );
		break;
	case SPELL_KIND_CURE_SILENCE:
		fx_cure_stat( (chr_t *)p, FX_KIND_SILENCE );
		break;
	case SPELL_KIND_CURE_FEAR:
		fx_cure_stat( (chr_t *)p, FX_KIND_FEAR );
		break;
	case SPELL_KIND_CURE_HALLUCINATION:
		fx_cure_stat( (chr_t *)p, FX_KIND_HALLUCINATION );
		break;
	case SPELL_KIND_CURE_CHARM:
		fx_cure_stat( (chr_t *)p, FX_KIND_CHARM );
		break;
	case SPELL_KIND_PROTECTION:
/*@@@*/
		print_msg( FLG_NULL, MSG_INCOMPLETE );
		break;
	case SPELL_KIND_RESIST_PHYSICAL:
		fx_resi( (chr_t *)p, FX_KIND_RESI_KNOC );
		fx_resi( (chr_t *)p, FX_KIND_RESI_SLAS );
		fx_resi( (chr_t *)p, FX_KIND_RESI_STIN );
		break;
	case SPELL_KIND_RESIST_HEAT:
		fx_resi( (chr_t *)p, FX_KIND_RESI_HEAT );
		break;
	case SPELL_KIND_RESIST_COLD:
		fx_resi( (chr_t *)p, FX_KIND_RESI_COLD );
		break;
	case SPELL_KIND_RESIST_MIND:
		fx_resi( (chr_t *)p, FX_KIND_RESI_MIND );
		break;
	case SPELL_KIND_RESIST_ACID:
		fx_resi( (chr_t *)p, FX_KIND_RESI_ACID );
		break;
	case SPELL_KIND_RESIST_ELECTRICITY:
		fx_resi( (chr_t *)p, FX_KIND_RESI_ELEC );
		break;
	case SPELL_KIND_RESIST_POISON:
		fx_resi( (chr_t *)p, FX_KIND_RESI_POIS );
		break;
	case SPELL_KIND_BLESS:
		fx_bless( (chr_t *)p );
		break;
	case SPELL_KIND_REMOVE_CURSE:
		fx_remove_curse( chr, (chr_t *)p );
		break;
	case SPELL_KIND_DISPEL_UNDEAD:
		fx_dispel_undead( chr, trgt_kind, (chr_t *)p, rate );
		break;
	case SPELL_KIND_ESCAPE:
		fx_escape( chr->x, chr->y );
		break;
	case SPELL_KIND_SANCTUARY:
		fx_sanctuary( chr, ABL_KIND_PRI );
		break;
	case SPELL_KIND_WISH:
		fx_wish( chr, WISH_LEVEL_GOD );
		break;
	case SPELL_KIND_PRI_MAX_N:
		break;
/* SHA */
	case SPELL_KIND_SHA_MIN_N:
		break;
	case SPELL_KIND_WEAK_FIRE_ELEMENTAL:
		fx_weak_attack( chr, trgt_kind, (chr_t *)p,
				FX_KIND_WEAK_HEAT, ABL_KIND_SHA );
		break;
	case SPELL_KIND_WEAK_WATER_ELEMENTAL:
		fx_weak_attack( chr, trgt_kind, (chr_t *)p,
				FX_KIND_WEAK_COLD, ABL_KIND_SHA );
		break;
	case SPELL_KIND_WEAK_AIR_ELEMENTAL:
		fx_weak_attack( chr, trgt_kind, (chr_t *)p,
				FX_KIND_WEAK_MIND, ABL_KIND_SHA );
		break;
	case SPELL_KIND_WEAK_EARTH_ELEMENTAL:
		fx_weak_attack( chr, trgt_kind, (chr_t *)p,
				FX_KIND_WEAK_ACID, ABL_KIND_SHA );
		break;
	case SPELL_KIND_WEAK_LIGHT_ELEMENTAL:
		fx_weak_attack( chr, trgt_kind, (chr_t *)p,
				FX_KIND_WEAK_ELEC, ABL_KIND_SHA );
		break;
	case SPELL_KIND_WEAK_DARK_ELEMENTAL:
		fx_weak_attack( chr, trgt_kind, (chr_t *)p,
				FX_KIND_WEAK_POIS, ABL_KIND_SHA );
		break;
	case SPELL_KIND_SUMMON_FIRE_ELEMENTAL:
		fx_summon_monster( chr, MNSTR_KIND_FIRE_ELEMENTAL, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_SUMMON_SALAMANDER:
		fx_summon_monster( chr, MNSTR_KIND_SALAMANDER, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_SUMMON_WATER_ELEMENTAL:
		fx_summon_monster( chr, MNSTR_KIND_WATER_ELEMENTAL, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_SUMMON_UNDINE:
		fx_summon_monster( chr, MNSTR_KIND_UNDINE, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_SUMMON_AIR_ELEMENTAL:
		fx_summon_monster( chr, MNSTR_KIND_AIR_ELEMENTAL, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_SUMMON_SYLPH:
		fx_summon_monster( chr, MNSTR_KIND_SYLPH, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_SUMMON_EARTH_ELEMENTAL:
		fx_summon_monster( chr, MNSTR_KIND_EARTH_ELEMENTAL, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_SUMMON_GNOME:
		fx_summon_monster( chr, MNSTR_KIND_GNOME, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_SUMMON_WILL_O_WISP:
		fx_summon_monster( chr, MNSTR_KIND_WILL_O_WISP, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_SUMMON_SHADE:
		fx_summon_monster( chr, MNSTR_KIND_SHADE, 1,
				DISMISSAL_TURN_ELEMENTAL );
		break;
	case SPELL_KIND_DISMISSAL_ELEMENTAL:
		fx_dismissal( (chr_t *)p );
		break;
	case SPELL_KIND_SHA_MAX_N:
		break;
/* BAR */
	case SPELL_KIND_BAR_MIN_N:
		break;
	case SPELL_KIND_SONG_CURE_HP:
	case SPELL_KIND_SONG_CURE_MP:
	case SPELL_KIND_SONG_SHARPNESS:
	case SPELL_KIND_SONG_STRENGTH:
	case SPELL_KIND_SONG_QUICKNESS:
	case SPELL_KIND_SONG_BRAINY:
	case SPELL_KIND_SONG_WISE:
	case SPELL_KIND_SONG_ATTRACTIVE:
	case SPELL_KIND_SONG_DULLNESS:
	case SPELL_KIND_SONG_WEAKNESS:
	case SPELL_KIND_SONG_SLOWNESS:
	case SPELL_KIND_SONG_BRAINLESS:
	case SPELL_KIND_SONG_FOOLISH:
	case SPELL_KIND_SONG_UNATTRACTIVE:
	case SPELL_KIND_SONG_RESI_STAT_STONE:
	case SPELL_KIND_SONG_RESI_STAT_PARALYZE:
	case SPELL_KIND_SONG_RESI_STAT_POISON:
	case SPELL_KIND_SONG_RESI_STAT_CONFUSION:
	case SPELL_KIND_SONG_RESI_STAT_BLIND:
	case SPELL_KIND_SONG_RESI_STAT_SLEEP:
	case SPELL_KIND_SONG_RESI_STAT_SILENCE:
	case SPELL_KIND_SONG_RESI_STAT_FEAR:
	case SPELL_KIND_SONG_RESI_STAT_HALLUCINATION:
	case SPELL_KIND_SONG_RESI_STAT_CHARM:
	case SPELL_KIND_SONG_RESI_STAT_DRUNK:
		/* inc_turn_all_fx() で実行 */
		break;
	case SPELL_KIND_BAR_MAX_N:
		break;
/* NIN */
	case SPELL_KIND_NIN_MIN_N:
		break;
	case SPELL_KIND_TYPHOON:
		rate = rate * SPELL_NIN_RATE / _100_PERCENT;
		fx_spell_attack( chr, trgt_kind, (chr_t *)p,
				RESI_KIND_MIND, ABL_KIND_NIN, rate );
		break;
	case SPELL_KIND_CONFLAGRATION:
		rate = rate * SPELL_NIN_RATE / _100_PERCENT;
		fx_spell_attack( chr, trgt_kind, (chr_t *)p,
				RESI_KIND_HEAT, ABL_KIND_NIN, rate );
		break;
	case SPELL_KIND_EARTHQUAKE:
		rate = rate * SPELL_NIN_RATE / _100_PERCENT;
		fx_spell_attack( chr, trgt_kind, (chr_t *)p,
				RESI_KIND_ACID, ABL_KIND_NIN, rate );
		break;
	case SPELL_KIND_THUNDERCLOUD:
		rate = rate * SPELL_NIN_RATE / _100_PERCENT;
		fx_spell_attack( chr, trgt_kind, (chr_t *)p,
				RESI_KIND_ELEC, ABL_KIND_NIN, rate );
		break;
	case SPELL_KIND_INUNDATION:
		rate = rate * SPELL_NIN_RATE / _100_PERCENT;
		fx_spell_attack( chr, trgt_kind, (chr_t *)p,
				RESI_KIND_COLD, ABL_KIND_NIN, rate );
		break;
	case SPELL_KIND_SUBSTITUTE:
		fx_magic_wpn_armor( chr, FX_KIND_SUBSTITUTE );
		break;
	case SPELL_KIND_BURNING_HANDS:
		fx_magic_wpn_armor( chr, FX_KIND_BURNING_HANDS );
		break;
	case SPELL_KIND_RALLY:
		fx_magic_wpn_armor( chr, FX_KIND_RALLY );
		break;
	case SPELL_KIND_IRON_MAN:
		fx_magic_wpn_armor( chr, FX_KIND_IRON_MAN );
		break;
	case SPELL_KIND_MIND_READING:
		fx_magic_wpn_armor( chr, FX_KIND_MIND_READING );
		break;
	case SPELL_KIND_NIN_MAX_N:
		break;
/* ANC */
	case SPELL_KIND_ANC_MIN_N:
		break;
	case SPELL_KIND_NOTHING:
		break;
	case SPELL_KIND_POLTERGEIST:
		fx_poltergeist( chr );
		break;
	case SPELL_KIND_ANC_MAX_N:
		break;
/* end */
	case SPELL_KIND_MAX_N:
		break;
	}
}

/**/

void	counter_magic(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate,
	long x, long y, trgt_kind_t trgt_kind, void *p
)
{
	fx_t	*fx;
	trgt_kind_t	d_trgt_kind;

	if( chr == NULL )
		return;
	if( p == NULL )
		return;

	if( !is_mbr( chr ) && !is_mnstr_or_pet( chr ) )
		return;

	fx = srch_fx( &(chr->fx), FX_KIND_COUNTER_MAGIC );
	if( fx == NULL )
		return;

	switch( trgt_kind ){
	case TRGT_KIND_MBR:
		if( is_mbr( chr ) )
			return;
		break;
	case TRGT_KIND_MNSTR:
		if( chr->kind == CHR_KIND_MNSTR )
			return;
		break;
	default:
		return;
	}

	g_vfx_n = 1;
	g_vfx_bgn[0].x = x * 2;
	g_vfx_bgn[0].y = y;
	g_vfx_end[0].x = chr->x * 2;
	g_vfx_end[0].y = chr->y;
	if( trgt_kind != TRGT_KIND_NULL )
		vfx_spell( tab, g_vfx_n, g_vfx_bgn, g_vfx_end );

	d_trgt_kind = get_trgt_kind_from_chr( chr );

	chr_cast_spell_sub( chr, flg_item, tab, rate,
			chr->x, chr->y, d_trgt_kind, chr );
}

/**/

reg_spell_t	*get_reg_spell( long mbr_n )
{
	if( mbr_n < 0 )
		return NULL;
	if( mbr_n >= MBR_MAX_N )
		return NULL;

	return &(g_reg_spell[mbr_n]);
}

/**/

void	set_reg_spell(
	long mbr_n,
	spell_tab_t *tab,
	extent_kind_t extent_kind,
	trgt_t trgt
)
{
	if( mbr_n < 0 )
		return;
	if( mbr_n >= MBR_MAX_N )
		return;

	g_reg_spell[mbr_n].tab = tab;
	g_reg_spell[mbr_n].extent_kind = extent_kind;
	g_reg_spell[mbr_n].trgt = trgt;
}

/**/

void	lost_trgt_reg_spell( void *p )
{
	long	m;

	for( m = 0; m < MBR_MAX_N; m++ )
		if( g_reg_spell[m].trgt.p == p )
			g_reg_spell[m].trgt.p = NULL;
}

/**/

bool_t	chk_spell( chr_t *o_p, spell_tab_t *tab, bool_t flg_item )
{
	abl_kind_t	o_abl, o_sub_abl;
	rate_t	rate;

	if( o_p == NULL )
		return FALSE;
	if( tab == NULL )
		return FALSE;

	if( flg_item )
		o_abl = get_specialist_abl( o_p );
	else
		o_abl = tab->abl;

	o_sub_abl = get_sub_abl( o_abl );

	/* キャラクタのレベルによる修整 */

	rate = get_lev( o_p, o_abl ) - tab->lev;
	rate += get_lev( o_p, o_sub_abl ) - tab->lev;
	rate /= 2;
	rate = rate * CHK_SPELL_LEV_RATE / _100_PERCENT;
	rate += CHK_SPELL_LEV_RATE_BASE;

	/* 装備による修整 */

	if( o_p->kind != CHR_KIND_NULL ){
		rate *= calc_rate_equip( o_p, o_abl, o_sub_abl );
		rate /= _100_PERCENT;
	}

	print_msg_find( o_p, FLG_MSG_DEBUG,
			"chk_spell() rate %ld", rate );

	return rate_randm( rate );
}

/**/

bool_t	chk_cast_spell_trgt( spell_kind_t spell, trgt_kind_t trgt )
{
	switch( spell ){
	case SPELL_KIND_NULL:
		break;
/* MAG */
	case SPELL_KIND_MAG_MIN_N:
		break;
	case SPELL_KIND_LIGHT:
	case SPELL_KIND_DARKNESS:
	case SPELL_KIND_STORE_LIGHT:
	case SPELL_KIND_SHORT_TELEPORT_PARTY:
	case SPELL_KIND_TELEPORT_PARTY:
	case SPELL_KIND_TELEPORT:
	case SPELL_KIND_RECALL:
	case SPELL_KIND_KNOCK:
	case SPELL_KIND_LOCK:
	case SPELL_KIND_DISARM_TRAP:
	case SPELL_KIND_ANIMATE_OBJECTS:
	case SPELL_KIND_SHELTER:
	case SPELL_KIND_CREATE_FOOD:
	case SPELL_KIND_IDENTIFY_ITEM:
		break;
	case SPELL_KIND_IDENTIFY_ALL_ITEM:
		if( trgt != TRGT_KIND_MBR )
			return FALSE;
		break;
	case SPELL_KIND_SEARCHING:
	case SPELL_KIND_ANALYZE_DWEOMER:
	case SPELL_KIND_DETECT_MAGIC:
	case SPELL_KIND_DETECT_ITEM:
	case SPELL_KIND_DETECT_DOORS:
	case SPELL_KIND_DETECT_TRAPS:
	case SPELL_KIND_DETECT_MONSTER:
		break;
	case SPELL_KIND_SENSE_INVISIBLE:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_FLY:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_FEATHER_FALL:
		break;
	case SPELL_KIND_VANISH:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_DARKVISION:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_PASSWALL:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_DISPEL_MAGIC:
	case SPELL_KIND_MIRROR_IMAGE:
	case SPELL_KIND_POLYMORPH_OTHER:
	case SPELL_KIND_POLYMORPH_SELF:
	case SPELL_KIND_STEALTH:
		break;
	case SPELL_KIND_MAG_MAX_N:
		break;
/* SOR */
	case SPELL_KIND_SOR_MIN_N:
		break;
	case SPELL_KIND_MAGIC_MISSILE:
	case SPELL_KIND_FIRE_BALL:
	case SPELL_KIND_ICE_BLIZZARD:
	case SPELL_KIND_MIND_STORM:
	case SPELL_KIND_ACID_RAIN:
	case SPELL_KIND_LIGHTNING_BOLT:
	case SPELL_KIND_POISON_CLOUD:
	case SPELL_KIND_DEATH_SPELL:
	case SPELL_KIND_WORD_OF_DESTRUCTION:
	case SPELL_KIND_MAGIC_SHIELD:
	case SPELL_KIND_MAGE_ARMOR:
	case SPELL_KIND_STONESKIN:
	case SPELL_KIND_IRON_BODY:
	case SPELL_KIND_SPELL_RESISTANCE:
	case SPELL_KIND_COUNTER_MAGIC:
		break;
	case SPELL_KIND_STONE:
	case SPELL_KIND_PARALYZE:
	case SPELL_KIND_POISON:
	case SPELL_KIND_CONFUSION:
	case SPELL_KIND_BLINDNESS:
	case SPELL_KIND_SLEEP:
	case SPELL_KIND_SILENCE:
	case SPELL_KIND_FEAR:
	case SPELL_KIND_HALLUCINATION:
	case SPELL_KIND_CHARM:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_SOR_MAX_N:
		break;
/* ENC */
	case SPELL_KIND_ENC_MIN_N:
		break;
	case SPELL_KIND_SHARPNESS:
	case SPELL_KIND_STRENGTH:
	case SPELL_KIND_QUICKNESS:
	case SPELL_KIND_BRAINY:
	case SPELL_KIND_WISE:
	case SPELL_KIND_ATTRACTIVE:
	case SPELL_KIND_POWER_UP_HP:
	case SPELL_KIND_HASTE:
	case SPELL_KIND_DULLNESS:
	case SPELL_KIND_WEAKNESS:
	case SPELL_KIND_SLOWNESS:
	case SPELL_KIND_BRAINLESS:
	case SPELL_KIND_FOOLISH:
	case SPELL_KIND_UNATTRACTIVE:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_ENERGY_DRAIN:
	case SPELL_KIND_SLOW:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_HUNGER:
	case SPELL_KIND_CANCELLATION:
		break;
	case SPELL_KIND_ENC_MAX_N:
		break;
/* SUM */
	case SPELL_KIND_SUM_MIN_N:
		break;
	case SPELL_KIND_SKELETON_WARRIOR:
	case SPELL_KIND_SUMMON_UNICORN:
	case SPELL_KIND_SUMMON_EFREET:
	case SPELL_KIND_SUMMON_DJINNI:
	case SPELL_KIND_SUMMON_PHOENIX:
	case SPELL_KIND_SUMMON_BONE:
	case SPELL_KIND_SUMMON_RANDOM:
	case SPELL_KIND_CREATE_UNDEAD:
		break;
	case SPELL_KIND_DISMISSAL:
		if( trgt != TRGT_KIND_MNSTR )
			return FALSE;
		break;
	case SPELL_KIND_SUM_MAX_N:
		break;
/* PRI */
	case SPELL_KIND_PRI_MIN_N:
		break;
	case SPELL_KIND_CURE_HP_LIGHT:
	case SPELL_KIND_CURE_HP_MODERATE:
	case SPELL_KIND_CURE_HP_SERIOUS:
	case SPELL_KIND_CURE_HP_MAX:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_CURE_MP:
		break;
	case SPELL_KIND_TRANSFER_MP:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_REGENERATION:
	case SPELL_KIND_RESTORE_EXPERIENCE:
	case SPELL_KIND_RESURRECTION:
		break;
	case SPELL_KIND_HEAL:
	case SPELL_KIND_CURE_STATUS:
	case SPELL_KIND_CURE_STONE:
	case SPELL_KIND_CURE_PARALYZE:
	case SPELL_KIND_CURE_POISON:
	case SPELL_KIND_CURE_CONFUSION:
	case SPELL_KIND_CURE_BLINDNESS:
	case SPELL_KIND_CURE_SLEEP:
	case SPELL_KIND_CURE_SILENCE:
	case SPELL_KIND_CURE_FEAR:
	case SPELL_KIND_CURE_HALLUCINATION:
	case SPELL_KIND_CURE_CHARM:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_PROTECTION:
		break;
	case SPELL_KIND_RESIST_PHYSICAL:
	case SPELL_KIND_RESIST_HEAT:
	case SPELL_KIND_RESIST_COLD:
	case SPELL_KIND_RESIST_MIND:
	case SPELL_KIND_RESIST_ACID:
	case SPELL_KIND_RESIST_ELECTRICITY:
	case SPELL_KIND_RESIST_POISON:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_BLESS:
		break;
	case SPELL_KIND_REMOVE_CURSE:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_DISPEL_UNDEAD:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_ESCAPE:
	case SPELL_KIND_SANCTUARY:
	case SPELL_KIND_WISH:
		break;
	case SPELL_KIND_PRI_MAX_N:
		break;
/* SHA */
	case SPELL_KIND_SHA_MIN_N:
		break;
	case SPELL_KIND_WEAK_FIRE_ELEMENTAL:
	case SPELL_KIND_WEAK_WATER_ELEMENTAL:
	case SPELL_KIND_WEAK_AIR_ELEMENTAL:
	case SPELL_KIND_WEAK_EARTH_ELEMENTAL:
	case SPELL_KIND_WEAK_LIGHT_ELEMENTAL:
	case SPELL_KIND_WEAK_DARK_ELEMENTAL:
		break;
	case SPELL_KIND_SUMMON_FIRE_ELEMENTAL:
	case SPELL_KIND_SUMMON_SALAMANDER:
	case SPELL_KIND_SUMMON_WATER_ELEMENTAL:
	case SPELL_KIND_SUMMON_UNDINE:
	case SPELL_KIND_SUMMON_AIR_ELEMENTAL:
	case SPELL_KIND_SUMMON_SYLPH:
	case SPELL_KIND_SUMMON_EARTH_ELEMENTAL:
	case SPELL_KIND_SUMMON_GNOME:
	case SPELL_KIND_SUMMON_WILL_O_WISP:
	case SPELL_KIND_SUMMON_SHADE:
		break;
	case SPELL_KIND_DISMISSAL_ELEMENTAL:
		if( trgt != TRGT_KIND_MNSTR )
			return FALSE;
		break;
	case SPELL_KIND_SHA_MAX_N:
		break;
/* BAR */
	case SPELL_KIND_BAR_MIN_N:
		break;
	case SPELL_KIND_SONG_CURE_HP:
	case SPELL_KIND_SONG_CURE_MP:
	case SPELL_KIND_SONG_SHARPNESS:
	case SPELL_KIND_SONG_STRENGTH:
	case SPELL_KIND_SONG_QUICKNESS:
	case SPELL_KIND_SONG_BRAINY:
	case SPELL_KIND_SONG_WISE:
	case SPELL_KIND_SONG_ATTRACTIVE:
	case SPELL_KIND_SONG_DULLNESS:
	case SPELL_KIND_SONG_WEAKNESS:
	case SPELL_KIND_SONG_SLOWNESS:
	case SPELL_KIND_SONG_BRAINLESS:
	case SPELL_KIND_SONG_FOOLISH:
	case SPELL_KIND_SONG_UNATTRACTIVE:
	case SPELL_KIND_SONG_RESI_STAT_STONE:
	case SPELL_KIND_SONG_RESI_STAT_PARALYZE:
	case SPELL_KIND_SONG_RESI_STAT_POISON:
	case SPELL_KIND_SONG_RESI_STAT_CONFUSION:
	case SPELL_KIND_SONG_RESI_STAT_BLIND:
	case SPELL_KIND_SONG_RESI_STAT_SLEEP:
	case SPELL_KIND_SONG_RESI_STAT_SILENCE:
	case SPELL_KIND_SONG_RESI_STAT_FEAR:
	case SPELL_KIND_SONG_RESI_STAT_HALLUCINATION:
	case SPELL_KIND_SONG_RESI_STAT_CHARM:
	case SPELL_KIND_SONG_RESI_STAT_DRUNK:
		if( (trgt != TRGT_KIND_MBR) && (trgt != TRGT_KIND_MNSTR) )
			return FALSE;
		break;
	case SPELL_KIND_BAR_MAX_N:
		break;
/* NIN */
	case SPELL_KIND_NIN_MIN_N:
		break;
	case SPELL_KIND_TYPHOON:
	case SPELL_KIND_CONFLAGRATION:
	case SPELL_KIND_EARTHQUAKE:
	case SPELL_KIND_THUNDERCLOUD:
	case SPELL_KIND_INUNDATION:
	case SPELL_KIND_SUBSTITUTE:
	case SPELL_KIND_BURNING_HANDS:
	case SPELL_KIND_RALLY:
	case SPELL_KIND_IRON_MAN:
	case SPELL_KIND_MIND_READING:
		break;
	case SPELL_KIND_NIN_MAX_N:
		break;
/* ANC */
	case SPELL_KIND_ANC_MIN_N:
		break;
	case SPELL_KIND_NOTHING:
	case SPELL_KIND_POLTERGEIST:
		break;
	case SPELL_KIND_ANC_MAX_N:
		break;
/* end */
	case SPELL_KIND_MAX_N:
		break;
	}

	return TRUE;
}

/**/

fx_kind_t	cv_spell_to_fx( spell_kind_t spell )
{
	switch( spell ){
	case SPELL_KIND_SENSE_INVISIBLE:
		return FX_KIND_SENSE_INVISIBLE;
	case SPELL_KIND_FLY:
		return FX_KIND_FLY;
	case SPELL_KIND_VANISH:
		return FX_KIND_VANISH;
	case SPELL_KIND_PASSWALL:
		return FX_KIND_PASSWALL;
	case SPELL_KIND_IRON_BODY:
		return FX_KIND_IRON_BODY;
	case SPELL_KIND_COUNTER_MAGIC:
		return FX_KIND_COUNTER_MAGIC;
	case SPELL_KIND_STONE:
		return FX_KIND_STONE;
	case SPELL_KIND_PARALYZE:
		return FX_KIND_PARALYZE;
	case SPELL_KIND_POISON:
		return FX_KIND_POISON;
	case SPELL_KIND_CONFUSION:
		return FX_KIND_CONFUSION;
	case SPELL_KIND_BLINDNESS:
		return FX_KIND_BLIND;
	case SPELL_KIND_SLEEP:
		return FX_KIND_SLEEP;
	case SPELL_KIND_SILENCE:
		return FX_KIND_SILENCE;
	case SPELL_KIND_FEAR:
		return FX_KIND_FEAR;
	case SPELL_KIND_HALLUCINATION:
		return FX_KIND_HALLUCINATION;
	case SPELL_KIND_CHARM:
		return FX_KIND_CHARM;
	default:
		break;
	}

	return FX_KIND_NULL;
}

/**/

flg_stat_t	cv_spell_to_stat( spell_kind_t spell )
{
	switch( spell ){
	case SPELL_KIND_SENSE_INVISIBLE:
		return FLG_STAT_SENSE_INVISIBLE;
	case SPELL_KIND_FLY:
		return FLG_STAT_FLY;
	case SPELL_KIND_VANISH:
		return FLG_STAT_VANISH;
	case SPELL_KIND_PASSWALL:
		return FLG_STAT_PASSWALL;
	case SPELL_KIND_DEATH_SPELL:
		return FLG_STAT_DEAD;
	case SPELL_KIND_IRON_BODY:
		return FLG_STAT_IRON_BODY;
	case SPELL_KIND_STONE:
		return FLG_STAT_STONE;
	case SPELL_KIND_PARALYZE:
		return FLG_STAT_PARALYZE;
	case SPELL_KIND_POISON:
		return FLG_STAT_POISON;
	case SPELL_KIND_CONFUSION:
		return FLG_STAT_CONFUSION;
	case SPELL_KIND_BLINDNESS:
		return FLG_STAT_BLIND;
	case SPELL_KIND_SLEEP:
		return FLG_STAT_SLEEP;
	case SPELL_KIND_SILENCE:
		return FLG_STAT_SILENCE;
	case SPELL_KIND_FEAR:
		return FLG_STAT_FEAR;
	case SPELL_KIND_HALLUCINATION:
		return FLG_STAT_HALLUCINATION;
	case SPELL_KIND_CHARM:
		return FLG_STAT_CHARM;
	default:
		break;
	}

	return FLG_STAT_NULL;
}

/**/

bool_t	chk_bar_limit( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( !is_mbr( chr ) )
		return TRUE;

	if( chk_bar_limit_lev( chr ) )
		return TRUE;
	if( chk_bar_limit_inst( chr ) )
		return TRUE;

	/* 限定不可 */

	curs_attrset_chr( chr, -1, FALSE );
	print_msg_find( chr, FLG_NULL,
			MSG_ERR_MENU_SPELL_INST_LIMIT,
			chr->name );
	curs_attrset_dflt();

	return FALSE;
}

/**/

bool_t	chk_bar_limit_lev( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( !is_mbr( chr ) )
		return TRUE;

	if( get_lev( chr, ABL_KIND_BAR ) < BAR_LIMIT_LEV )
		return FALSE;

	return TRUE;
}

/**/

chr_kind_t	get_inst_spell_chr_kind( chr_t *chr, spell_kind_t kind )
{
	switch( kind ){
	default:
		break;
	case SPELL_KIND_SONG_CURE_HP:
	case SPELL_KIND_SONG_CURE_MP:
	case SPELL_KIND_SONG_SHARPNESS:
	case SPELL_KIND_SONG_STRENGTH:
	case SPELL_KIND_SONG_QUICKNESS:
	case SPELL_KIND_SONG_BRAINY:
	case SPELL_KIND_SONG_WISE:
	case SPELL_KIND_SONG_ATTRACTIVE:
	case SPELL_KIND_SONG_RESI_STAT_STONE:
	case SPELL_KIND_SONG_RESI_STAT_PARALYZE:
	case SPELL_KIND_SONG_RESI_STAT_POISON:
	case SPELL_KIND_SONG_RESI_STAT_CONFUSION:
	case SPELL_KIND_SONG_RESI_STAT_BLIND:
	case SPELL_KIND_SONG_RESI_STAT_SLEEP:
	case SPELL_KIND_SONG_RESI_STAT_SILENCE:
	case SPELL_KIND_SONG_RESI_STAT_FEAR:
	case SPELL_KIND_SONG_RESI_STAT_HALLUCINATION:
	case SPELL_KIND_SONG_RESI_STAT_CHARM:
	case SPELL_KIND_SONG_RESI_STAT_DRUNK:
		/* 支援系 */
		if( is_mbr( chr ) || is_pet( chr ) )
			return CHR_KIND_MBR;
		else
			return CHR_KIND_MNSTR;
		break;
	case SPELL_KIND_SONG_DULLNESS:
	case SPELL_KIND_SONG_WEAKNESS:
	case SPELL_KIND_SONG_SLOWNESS:
	case SPELL_KIND_SONG_BRAINLESS:
	case SPELL_KIND_SONG_FOOLISH:
	case SPELL_KIND_SONG_UNATTRACTIVE:
		/* 妨害系 */
		if( is_mbr( chr ) || is_pet( chr ) )
			return CHR_KIND_MNSTR;
		else
			return CHR_KIND_MBR;
		break;
	}

	return CHR_KIND_NULL;
}

/**/

bool_t	chk_can_chr_cast_stat( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( chk_flg_or( chr->stat,
			FLG_STAT_NOT_EXIST
			| FLG_STAT_DEAD
			| FLG_STAT_STONE
			| FLG_STAT_PARALYZE
			| FLG_STAT_CONFUSION
			| FLG_STAT_SLEEP
			| FLG_STAT_SILENCE
			) ){
		return FALSE;
	}

	return TRUE;
}

/**/

bool_t	chk_can_chr_cast_lev( chr_t *chr, spell_kind_t kind )
{
	spell_tab_t	*spell_tab;

	if( chr == NULL )
		return FALSE;

	/* レベルチェック */

	spell_tab = get_spell_tab( kind );
	if( spell_tab == NULL )
		return FALSE;

	if( get_lev( chr, spell_tab->abl ) < spell_tab->lev )
		return FALSE;

	if( chk_chr_learned_spell( chr, kind ) )
		return TRUE;
	if( chk_chr_learned_spell_nin( chr, kind, FALSE ) )
		return TRUE;

	return FALSE;
}

/**/

bool_t	chk_chr_learned_spell( chr_t *chr, spell_kind_t kind )
{
	cast_tab_t	*cast_tab;

	if( chr == NULL )
		return FALSE;

	if( !is_mbr( chr ) )
		return TRUE;	/* FALSE ではない */

	cast_tab = get_cast_tab( chr, kind );
	if( cast_tab == NULL )
		return FALSE;

	return( cast_tab->flg_cast );
}

/**/

bool_t	set_chr_learned_spell( chr_t *chr, spell_kind_t kind, bool_t flg )
{
	cast_tab_t	*tab;

	if( chr == NULL )
		return FALSE;

	if( !is_mbr( chr ) )
		return TRUE;	/* FALSE ではない */

	tab = get_cast_tab( chr, kind );
	if( tab == NULL )
		return FALSE;

	if( tab->flg_cast && flg )
		return TRUE;	/* FALSE ではない */
	if( !tab->flg_cast && !flg )
		return FALSE;
	tab->flg_cast = flg;

	if( g_flg_init ){
		if( flg ){
			curs_attrset_chr( chr, +1, TRUE );
			print_msg( FLG_NULL, MSG_LEARN_SPELL,
					chr->name,
					get_spell_name( kind ) );
			curs_attrset_dflt();
		} else {
			curs_attrset_chr( chr, -1, TRUE );
			print_msg( FLG_NULL, MSG_FORGET_SPELL,
					chr->name,
					get_spell_name( kind ) );
			curs_attrset_dflt();
		}
	}

	return tab->flg_cast;
}

/**/

bool_t	learn_spell_pri( chr_t *chr )
{
	long	lev;
	spell_kind_t	kind;
	long	k;
	long	n;

	lev = get_lev( chr, ABL_KIND_PRI );

	n = 0;
	kind = SPELL_KIND_NULL;

	for( k = SPELL_KIND_PRI_MIN_N + 1; k < SPELL_KIND_PRI_MAX_N; k++ ){
		spell_tab_t	*spell_tab;

		if( is_mbr( chr ) )
			if( cast_tab[chr->ls_mbr_n][k].flg_cast )
				continue;

		spell_tab = get_spell_tab( (spell_kind_t)k );
		if( spell_tab == NULL )
			continue;

		if( lev >= spell_tab->lev ){
			n++;
			if( per_randm( n ) ){
				kind = (spell_kind_t)k;
			}
		}
	}

	if( kind == SPELL_KIND_NULL )
		return FALSE;

	set_chr_learned_spell( chr, kind, TRUE );

	return TRUE;
}

/**/

void	learn_spell_sha( chr_t *chr )
{
	long	lev;
	long	k;

	lev = get_lev( chr, ABL_KIND_SHA );

	for( k = SPELL_KIND_SHA_MIN_N + 1; k < SPELL_KIND_SHA_MAX_N; k++ ){
		spell_tab_t	*spell_tab;

		if( is_mbr( chr ) )
			if( cast_tab[chr->ls_mbr_n][k].flg_cast )
				continue;

		spell_tab = get_spell_tab( (spell_kind_t)k );
		if( spell_tab == NULL )
			continue;

		if( lev >= spell_tab->lev ){
			set_chr_learned_spell( chr,
					(spell_kind_t)k, TRUE );
		}
	}
}

/**/

void	learn_spell_bar( chr_t *chr )
{
	long	lev;
	spell_kind_t	kind;
	long	k;
	long	n;

	lev = get_lev( chr, ABL_KIND_BAR );

	n = 0;
	kind = SPELL_KIND_NULL;

	for( k = SPELL_KIND_BAR_MIN_N + 1; k < SPELL_KIND_BAR_MAX_N; k++ ){
		spell_tab_t	*spell_tab;

		if( is_mbr( chr ) )
			if( cast_tab[chr->ls_mbr_n][k].flg_cast )
				continue;

		if( !chk_learn_spell_item( chr, (spell_kind_t)k ) )
			continue;

		spell_tab = get_spell_tab( (spell_kind_t)k );
		if( spell_tab == NULL )
			continue;

		if( lev >= spell_tab->lev ){
			n++;
			if( per_randm( n ) ){
				kind = (spell_kind_t)k;
			}
		}
	}

	if( kind != SPELL_KIND_NULL )
		set_chr_learned_spell( chr, kind, TRUE );
}

/**/

bool_t	chk_chr_learned_spell_nin(
	chr_t *chr, spell_kind_t kind,
	bool_t flg_test
)
{
	item_t	*eq;
	scroll_tab_t	*tab;
	bool_t	flg_learn;

	if( chr == NULL )
		return FALSE;

	if( !is_mbr( chr ) )
		return TRUE;	/* FALSE ではない */

	if( kind <= SPELL_KIND_NIN_MIN_N )
		return FALSE;
	if( kind >= SPELL_KIND_NIN_MAX_N )
		return FALSE;

	flg_learn = FALSE;

	switch( kind ){
	default:
		if( flg_test ){
			print_err( MSG_ERR_SPELL_NIN_LEARNED,
					get_spell_name( kind ) );
			exit_game( EXIT_FAILURE );
		} else {
			print_msg( FLG_MSG_ERR, MSG_ERR_SPELL_NIN_LEARNED,
					get_spell_name( kind ) );
		}
		return FALSE;
	case SPELL_KIND_NIN_MIN_N:
	case SPELL_KIND_TYPHOON:
	case SPELL_KIND_CONFLAGRATION:
	case SPELL_KIND_EARTHQUAKE:
	case SPELL_KIND_THUNDERCLOUD:
	case SPELL_KIND_INUNDATION:
	case SPELL_KIND_SUBSTITUTE:
	case SPELL_KIND_BURNING_HANDS:
	case SPELL_KIND_RALLY:
	case SPELL_KIND_IRON_MAN:
	case SPELL_KIND_MIND_READING:
	case SPELL_KIND_NIN_MAX_N:
		break;
	}

	eq = get_mbr_item_asgn_equip( chr );
	if( eq == NULL )
		return FALSE;
	eq = &(eq[EQUIP_KIND_HEAD]);
	if( eq->kind != ITEM_KIND_SCROLL )
		return FALSE;

	tab = eq->tab.scroll;
	if( tab == NULL )
		return FALSE;

	switch( kind ){
	default:
		break;
	case SPELL_KIND_NIN_MIN_N:
		break;
	case SPELL_KIND_TYPHOON:
		if( tab->kind == SCROLL_KIND_TYPHOON )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_CONFLAGRATION:
		if( tab->kind == SCROLL_KIND_CONFLAGRATION )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_EARTHQUAKE:
		if( tab->kind == SCROLL_KIND_EARTHQUAKE )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_THUNDERCLOUD:
		if( tab->kind == SCROLL_KIND_THUNDERCLOUD )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_INUNDATION:
		if( tab->kind == SCROLL_KIND_INUNDATION )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_SUBSTITUTE:
		if( tab->kind == SCROLL_KIND_SUBSTITUTE )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_BURNING_HANDS:
		if( tab->kind == SCROLL_KIND_BURNING_HANDS )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_RALLY:
		if( tab->kind == SCROLL_KIND_RALLY )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_IRON_MAN:
		if( tab->kind == SCROLL_KIND_IRON_MAN )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_MIND_READING:
		if( tab->kind == SCROLL_KIND_MIND_READING )
			flg_learn = TRUE;
		break;
	case SPELL_KIND_NIN_MAX_N:
		break;
	}

	if( flg_learn && !flg_test )
		set_chr_learned_spell( chr, kind, TRUE );

	return flg_learn;
}

/**/

bool_t	chk_learn_spell_item( chr_t *chr, spell_kind_t kind )
{
	item_t	*item;

	if( chr == NULL )
		return FALSE;

	if( !is_mbr( chr ) )
		return TRUE;	/* FALSE ではない */

	item = NULL;

	switch( kind ){
	/* BAR */
	case SPELL_KIND_BAR_MIN_N:
		break;
	case SPELL_KIND_SONG_CURE_HP:
	case SPELL_KIND_SONG_CURE_MP:
		item = get_item_mbr_anthology(
				chr, ANTHOLOGY_KIND_CURE );
		break;
	case SPELL_KIND_SONG_SHARPNESS:
	case SPELL_KIND_SONG_STRENGTH:
	case SPELL_KIND_SONG_QUICKNESS:
	case SPELL_KIND_SONG_BRAINY:
	case SPELL_KIND_SONG_WISE:
	case SPELL_KIND_SONG_ATTRACTIVE:
		item = get_item_mbr_anthology(
				chr, ANTHOLOGY_KIND_STRENGTHEN_ABL );
		break;
	case SPELL_KIND_SONG_DULLNESS:
	case SPELL_KIND_SONG_WEAKNESS:
	case SPELL_KIND_SONG_SLOWNESS:
	case SPELL_KIND_SONG_BRAINLESS:
	case SPELL_KIND_SONG_FOOLISH:
	case SPELL_KIND_SONG_UNATTRACTIVE:
		item = get_item_mbr_anthology(
				chr, ANTHOLOGY_KIND_WEAKEN_ABL );
		break;
	case SPELL_KIND_SONG_RESI_STAT_STONE:
	case SPELL_KIND_SONG_RESI_STAT_PARALYZE:
	case SPELL_KIND_SONG_RESI_STAT_POISON:
	case SPELL_KIND_SONG_RESI_STAT_CONFUSION:
	case SPELL_KIND_SONG_RESI_STAT_BLIND:
	case SPELL_KIND_SONG_RESI_STAT_SLEEP:
	case SPELL_KIND_SONG_RESI_STAT_SILENCE:
	case SPELL_KIND_SONG_RESI_STAT_FEAR:
	case SPELL_KIND_SONG_RESI_STAT_HALLUCINATION:
	case SPELL_KIND_SONG_RESI_STAT_CHARM:
	case SPELL_KIND_SONG_RESI_STAT_DRUNK:
		item = get_item_mbr_anthology(
				chr, ANTHOLOGY_KIND_RESI_STAT );
		break;
	case SPELL_KIND_BAR_MAX_N:
		break;
	default:
		break;
	}

	if( item == NULL )
		return FALSE;
	else
		return TRUE;
}

/**/

void	arrange_cast_tab_1( long trgt_ls_mbr_n, long d )
{
	mbr_t	**ls_mbr;
	cast_tab_t	tmp_cast_tab[SPELL_KIND_MAX_N];

	ls_mbr = get_ls_mbr();

	if( (trgt_ls_mbr_n + d) < 0 )
		return;
	if( (trgt_ls_mbr_n + d) >= LS_MBR_MAX_N )
		return;
	if( chk_flg( ls_mbr[trgt_ls_mbr_n + d]->stat,
			FLG_STAT_NOT_EXIST ) ){
		return;
	}

	copy_cast_tab( tmp_cast_tab, cast_tab[trgt_ls_mbr_n] );
	copy_cast_tab( cast_tab[trgt_ls_mbr_n],
			cast_tab[trgt_ls_mbr_n + d] );
	copy_cast_tab( cast_tab[trgt_ls_mbr_n + d], tmp_cast_tab );
}

/**/

void	arrange_cast_tab( long trgt_ls_mbr_n, long d )
{
	mbr_t	**ls_mbr;
	cast_tab_t	tmp_cast_tab[SPELL_KIND_MAX_N];
	long	i;

	ls_mbr = get_ls_mbr();

	copy_cast_tab( tmp_cast_tab, cast_tab[trgt_ls_mbr_n] );

	if( d <= -1 ){
		for( i = trgt_ls_mbr_n - 1; i >= 0; i-- )
			copy_cast_tab( cast_tab[i + 1], cast_tab[i] );

		copy_cast_tab( cast_tab[0], tmp_cast_tab );
	} else {
		for( i = trgt_ls_mbr_n + 1; i < LS_MBR_MAX_N; i++ ){
			if( chk_flg( ls_mbr[i]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}

			copy_cast_tab( cast_tab[i - 1], cast_tab[i] );
		}

		copy_cast_tab( cast_tab[i - 1], tmp_cast_tab );
	}
}

/**/

void	remove_cast_tab( long trgt_ls_mbr_n )
{
	arrange_cast_tab( trgt_ls_mbr_n, +1 );
}

/**/

bool_t	copy_cast_tab( cast_tab_t dst[], cast_tab_t src[] )
{
	long	k;

	if( dst == NULL )
		return FALSE;
	if( src == NULL )
		return FALSE;

	for( k = SPELL_KIND_NULL + 1; k < SPELL_KIND_MAX_N; k++ )
		dst[k] = src[k];

	return TRUE;
}

/**/

char	*get_spell_vfx_str( spell_kind_t spell_kind )
{
	switch( spell_kind ){
	case SPELL_KIND_NULL:
		break;
/* MAG */
	case SPELL_KIND_MAG_MIN_N:
	case SPELL_KIND_LIGHT:
	case SPELL_KIND_DARKNESS:
	case SPELL_KIND_STORE_LIGHT:
	case SPELL_KIND_SHORT_TELEPORT_PARTY:
	case SPELL_KIND_TELEPORT_PARTY:
	case SPELL_KIND_TELEPORT:
	case SPELL_KIND_RECALL:
		break;
	case SPELL_KIND_KNOCK:
		return "+'";
	case SPELL_KIND_LOCK:
		return "+^";
	case SPELL_KIND_DISARM_TRAP:
		return "^*";
	case SPELL_KIND_ANIMATE_OBJECTS:
		break;
	case SPELL_KIND_SHELTER:
		return "++";
	case SPELL_KIND_CREATE_FOOD:
	case SPELL_KIND_IDENTIFY_ITEM:
	case SPELL_KIND_IDENTIFY_ALL_ITEM:
	case SPELL_KIND_SEARCHING:
	case SPELL_KIND_ANALYZE_DWEOMER:
	case SPELL_KIND_DETECT_ITEM:
	case SPELL_KIND_DETECT_DOORS:
	case SPELL_KIND_DETECT_TRAPS:
	case SPELL_KIND_DETECT_MAGIC:
	case SPELL_KIND_DETECT_MONSTER:
	case SPELL_KIND_SENSE_INVISIBLE:
	case SPELL_KIND_FLY:
	case SPELL_KIND_FEATHER_FALL:
	case SPELL_KIND_VANISH:
	case SPELL_KIND_DARKVISION:
	case SPELL_KIND_PASSWALL:
	case SPELL_KIND_DISPEL_MAGIC:
	case SPELL_KIND_MIRROR_IMAGE:
	case SPELL_KIND_POLYMORPH_OTHER:
	case SPELL_KIND_POLYMORPH_SELF:
	case SPELL_KIND_STEALTH:
	case SPELL_KIND_MAG_MAX_N:
		break;
/* SOR */
	case SPELL_KIND_SOR_MIN_N:
		break;
	case SPELL_KIND_MAGIC_MISSILE:
		return "||";
	case SPELL_KIND_FIRE_BALL:
		return "oo";
	case SPELL_KIND_ICE_BLIZZARD:
		return "~~";
	case SPELL_KIND_MIND_STORM:
		return "@@";
	case SPELL_KIND_ACID_RAIN:
		return "//";
	case SPELL_KIND_LIGHTNING_BOLT:
		return "<<";
	case SPELL_KIND_POISON_CLOUD:
		return "Oo";
	case SPELL_KIND_DEATH_SPELL:
		return "XX";
	case SPELL_KIND_WORD_OF_DESTRUCTION:
		return "##";
	case SPELL_KIND_MAGE_ARMOR:
	case SPELL_KIND_MAGIC_SHIELD:
	case SPELL_KIND_STONESKIN:
	case SPELL_KIND_IRON_BODY:
	case SPELL_KIND_SPELL_RESISTANCE:
	case SPELL_KIND_COUNTER_MAGIC:
	case SPELL_KIND_STONE:
	case SPELL_KIND_PARALYZE:
	case SPELL_KIND_POISON:
	case SPELL_KIND_CONFUSION:
	case SPELL_KIND_BLINDNESS:
	case SPELL_KIND_SLEEP:
	case SPELL_KIND_SILENCE:
	case SPELL_KIND_FEAR:
	case SPELL_KIND_HALLUCINATION:
	case SPELL_KIND_CHARM:
	case SPELL_KIND_SOR_MAX_N:
		break;
/* ENC */
	case SPELL_KIND_ENC_MIN_N:
		break;
	case SPELL_KIND_SHARPNESS:
	case SPELL_KIND_STRENGTH:
	case SPELL_KIND_QUICKNESS:
	case SPELL_KIND_BRAINY:
	case SPELL_KIND_WISE:
	case SPELL_KIND_ATTRACTIVE:
	case SPELL_KIND_POWER_UP_HP:
	case SPELL_KIND_HASTE:
		return "@+";
	case SPELL_KIND_DULLNESS:
	case SPELL_KIND_WEAKNESS:
	case SPELL_KIND_SLOWNESS:
	case SPELL_KIND_BRAINLESS:
	case SPELL_KIND_FOOLISH:
	case SPELL_KIND_UNATTRACTIVE:
	case SPELL_KIND_ENERGY_DRAIN:
	case SPELL_KIND_SLOW:
		return "@-";
	case SPELL_KIND_HUNGER:
	case SPELL_KIND_CANCELLATION:
	case SPELL_KIND_ENC_MAX_N:
		break;
/* SUM */
	case SPELL_KIND_SUM_MIN_N:
	case SPELL_KIND_SKELETON_WARRIOR:
	case SPELL_KIND_SUMMON_UNICORN:
	case SPELL_KIND_SUMMON_EFREET:
	case SPELL_KIND_SUMMON_DJINNI:
	case SPELL_KIND_SUMMON_PHOENIX:
	case SPELL_KIND_SUMMON_BONE:
	case SPELL_KIND_SUMMON_RANDOM:
	case SPELL_KIND_CREATE_UNDEAD:
		break;
	case SPELL_KIND_DISMISSAL:
		return "><";
	case SPELL_KIND_SUM_MAX_N:
		break;
/* PRI */
	case SPELL_KIND_PRI_MIN_N:
		break;
	case SPELL_KIND_CURE_HP_LIGHT:
		return "+";
	case SPELL_KIND_CURE_HP_MODERATE:
		return "+!";
	case SPELL_KIND_CURE_HP_SERIOUS:
		return "+!!";
	case SPELL_KIND_CURE_HP_MAX:
		return "+!!!";
	case SPELL_KIND_REGENERATION:
	case SPELL_KIND_CURE_MP:
	case SPELL_KIND_TRANSFER_MP:
	case SPELL_KIND_RESTORE_EXPERIENCE:
		return "+?";
	case SPELL_KIND_RESURRECTION:
		break;
	case SPELL_KIND_HEAL:
	case SPELL_KIND_CURE_STATUS:
	case SPELL_KIND_CURE_STONE:
	case SPELL_KIND_CURE_PARALYZE:
	case SPELL_KIND_CURE_POISON:
	case SPELL_KIND_CURE_CONFUSION:
	case SPELL_KIND_CURE_BLINDNESS:
	case SPELL_KIND_CURE_SLEEP:
	case SPELL_KIND_CURE_SILENCE:
	case SPELL_KIND_CURE_FEAR:
	case SPELL_KIND_CURE_HALLUCINATION:
	case SPELL_KIND_CURE_CHARM:
		return "+%";
	case SPELL_KIND_PROTECTION:
	case SPELL_KIND_RESIST_PHYSICAL:
	case SPELL_KIND_RESIST_HEAT:
	case SPELL_KIND_RESIST_COLD:
	case SPELL_KIND_RESIST_MIND:
	case SPELL_KIND_RESIST_ACID:
	case SPELL_KIND_RESIST_ELECTRICITY:
	case SPELL_KIND_RESIST_POISON:
		return "+[";
	case SPELL_KIND_BLESS:
	case SPELL_KIND_REMOVE_CURSE:
		break;
	case SPELL_KIND_DISPEL_UNDEAD:
		return "+Z";
	case SPELL_KIND_ESCAPE:
	case SPELL_KIND_SANCTUARY:
	case SPELL_KIND_WISH:
	case SPELL_KIND_PRI_MAX_N:
		break;
/* SHA */
	case SPELL_KIND_SHA_MIN_N:
		break;
	case SPELL_KIND_WEAK_FIRE_ELEMENTAL:
		return "Ef";
	case SPELL_KIND_WEAK_WATER_ELEMENTAL:
		return "Ew";
	case SPELL_KIND_WEAK_AIR_ELEMENTAL:
		return "Ea";
	case SPELL_KIND_WEAK_EARTH_ELEMENTAL:
		return "Ee";
	case SPELL_KIND_WEAK_LIGHT_ELEMENTAL:
		return "Eo";
	case SPELL_KIND_WEAK_DARK_ELEMENTAL:
		return "Ed";
	case SPELL_KIND_SUMMON_FIRE_ELEMENTAL:
	case SPELL_KIND_SUMMON_SALAMANDER:
	case SPELL_KIND_SUMMON_WATER_ELEMENTAL:
	case SPELL_KIND_SUMMON_UNDINE:
	case SPELL_KIND_SUMMON_AIR_ELEMENTAL:
	case SPELL_KIND_SUMMON_SYLPH:
	case SPELL_KIND_SUMMON_EARTH_ELEMENTAL:
	case SPELL_KIND_SUMMON_GNOME:
	case SPELL_KIND_SUMMON_WILL_O_WISP:
	case SPELL_KIND_SUMMON_SHADE:
		break;
	case SPELL_KIND_DISMISSAL_ELEMENTAL:
		return "><";
	case SPELL_KIND_SHA_MAX_N:
		break;
/* BAR */
	case SPELL_KIND_BAR_MIN_N:
		break;
	case SPELL_KIND_SONG_CURE_HP:
	case SPELL_KIND_SONG_CURE_MP:
	case SPELL_KIND_SONG_SHARPNESS:
	case SPELL_KIND_SONG_STRENGTH:
	case SPELL_KIND_SONG_QUICKNESS:
	case SPELL_KIND_SONG_BRAINY:
	case SPELL_KIND_SONG_WISE:
	case SPELL_KIND_SONG_ATTRACTIVE:
	case SPELL_KIND_SONG_DULLNESS:
	case SPELL_KIND_SONG_WEAKNESS:
	case SPELL_KIND_SONG_SLOWNESS:
	case SPELL_KIND_SONG_BRAINLESS:
	case SPELL_KIND_SONG_FOOLISH:
	case SPELL_KIND_SONG_UNATTRACTIVE:
	case SPELL_KIND_SONG_RESI_STAT_STONE:
	case SPELL_KIND_SONG_RESI_STAT_PARALYZE:
	case SPELL_KIND_SONG_RESI_STAT_POISON:
	case SPELL_KIND_SONG_RESI_STAT_CONFUSION:
	case SPELL_KIND_SONG_RESI_STAT_BLIND:
	case SPELL_KIND_SONG_RESI_STAT_SLEEP:
	case SPELL_KIND_SONG_RESI_STAT_SILENCE:
	case SPELL_KIND_SONG_RESI_STAT_FEAR:
	case SPELL_KIND_SONG_RESI_STAT_HALLUCINATION:
	case SPELL_KIND_SONG_RESI_STAT_CHARM:
	case SPELL_KIND_SONG_RESI_STAT_DRUNK:
		break;
	case SPELL_KIND_BAR_MAX_N:
		break;
/* NIN */
	case SPELL_KIND_NIN_MIN_N:
	case SPELL_KIND_TYPHOON:
	case SPELL_KIND_CONFLAGRATION:
	case SPELL_KIND_EARTHQUAKE:
	case SPELL_KIND_THUNDERCLOUD:
	case SPELL_KIND_INUNDATION:
	case SPELL_KIND_SUBSTITUTE:
	case SPELL_KIND_BURNING_HANDS:
	case SPELL_KIND_RALLY:
	case SPELL_KIND_IRON_MAN:
	case SPELL_KIND_MIND_READING:
	case SPELL_KIND_NIN_MAX_N:
		break;
/* ANC */
	case SPELL_KIND_ANC_MIN_N:
	case SPELL_KIND_NOTHING:
	case SPELL_KIND_POLTERGEIST:
	case SPELL_KIND_ANC_MAX_N:
		break;
/* end */
	case SPELL_KIND_MAX_N:
		break;
	}

	return "**";
}

/**/

cast_tab_t	*get_cast_tab( chr_t *chr, spell_kind_t kind )
{
	long	m;
	long	k;

	if( chr == NULL )
		return NULL;

	m = chr->ls_mbr_n;
	for( k = SPELL_KIND_NULL; k < SPELL_KIND_MAX_N; k++ ){
		if( cast_tab[m][k].kind == SPELL_KIND_MAX_N )
			break;

		if( cast_tab[m][k].kind == kind )
			return &(cast_tab[m][k]);
	}

	return NULL;
}

/**/

char	*get_spell_name( spell_kind_t kind )
{
	spell_tab_t	*tab;

	tab = get_spell_tab( kind );
	if( tab == NULL )
		return( MSG_NULL );

	return( tab->name );
}

/**/

spell_tab_t	*get_spell_tab( spell_kind_t kind )
{
	long	n;

	for( n = SPELL_KIND_NULL + 1; n < SPELL_KIND_MAX_N; n++ ){
		if( spell_tab[n].kind == SPELL_KIND_NULL )
			break;
		if( spell_tab[n].kind == SPELL_KIND_MAX_N )
			break;

		if( spell_tab[n].kind == kind )
			return &(spell_tab[n]);
	}

	return NULL;
}

/**/

gold_t	get_price_spell( spell_kind_t kind )
{
	gold_t	price;
	spell_tab_t	*tab;

	price = 0;

	tab = get_spell_tab( kind );
	if( tab == NULL )
		return( (gold_t)0 );

	price += tab->lev * SPELL_PRICE_LEV_MUL;
	price += tab->add_price;

	return price;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_spell_c( void )
{
	check_memory( check_memory_spell_c_cast_tab,
			"spell.c: cast_tab" );
	check_memory( check_memory_spell_c_g_sel_mbr,
			"spell.c: g_sel_mbr" );
	check_memory( check_memory_spell_c_g_dflt_spell_abl,
			"spell.c: g_dflt_spell_abl" );
	check_memory( check_memory_spell_c_g_dflt_spell,
			"spell.c: g_dflt_spell" );
	check_memory( check_memory_spell_c_g_dflt_spell_extent,
			"spell.c: g_dflt_spell_extent" );
	check_memory( check_memory_spell_c_g_sel_spell_abl,
			"spell.c: g_sel_spell_abl" );
	check_memory( check_memory_spell_c_g_vfx_n,
			"spell.c: g_vfx_n" );
	check_memory( check_memory_spell_c_g_vfx_bgn,
			"spell.c: g_vfx_bgn" );
	check_memory( check_memory_spell_c_g_reg_spell,
			"spell.c: g_reg_spell" );
}

/**/
