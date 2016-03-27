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
* $Id: play-rep.c,v 1.4 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* 統計データ
***************************************************************/

#define	PLAY_REP_C
#include	"inc.h"

playing_report_t	playing_report_ls_mbr[LS_MBR_MAX_N + 1];
check_memory_def( check_memory_play_rep_c_playing_report_ls_mbr )

playing_report_t	playing_report_party;
check_memory_def( check_memory_play_rep_c_playing_report_party )

void	init_playing_report( void )
{
	playing_report_t	*rep;
	long	i, j;

	/* メンバーの統計データ */

	for( i = 0; i < LS_MBR_MAX_N + 1; i++ ){
		rep = &(playing_report_ls_mbr[i]);

		rep->paying_gold = 0;
		for( j = 0; j < STAY_INN_KIND_MAX_N; j++ ){
			rep->staying_inn[j] = 0;
		}
		for( j = 0; j < EQUIP_KIND_MAX_N; j++ ){
			rep->wearing_equip[j] = 0;
		}
		for( j = 0; j < RESI_KIND_MAX_N; j++ ){
			rep->making_dam[j] = 0;
			rep->made_dam[j] = 0;
		}
		for( j = 0; j < SPELL_KIND_MAX_N; j++ ){
			rep->using_spell[j] = 0;
			rep->used_spell[j] = 0;
		}
	}

	/* パーティの統計データ */

	rep = &playing_report_party;

	rep->paying_gold = 0;
	for( j = 0; j < STAY_INN_KIND_MAX_N; j++ ){
		rep->staying_inn[j] = 0;
	}
	for( j = 0; j < EQUIP_KIND_MAX_N; j++ ){
		rep->wearing_equip[j] = 0;
	}
	for( j = 0; j < RESI_KIND_MAX_N; j++ ){
		rep->making_dam[j] = 0;
		rep->made_dam[j] = 0;
	}
	for( j = 0; j < SPELL_KIND_MAX_N; j++ ){
		rep->using_spell[j] = 0;
		rep->used_spell[j] = 0;
	}
}

/***************************************************************
* 統計データの「支払い」を更新
* long ls_mbr_n : メンバー・リスト番号
* gold_t gold : 金額
***************************************************************/

void	update_playing_report_paying_gold(
	long ls_mbr_n, gold_t gold
)
{
	if( ls_mbr_n < 0 )
		return;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return;

	playing_report_ls_mbr[ls_mbr_n].paying_gold += gold;
	playing_report_party.paying_gold += gold;
}

/***************************************************************
* 統計データの「宿屋」を更新 (メンバー)
* long ls_mbr_n : メンバー・リスト番号
* stay_inn_kind_t kind : 宿泊の種類
***************************************************************/

void	update_playing_report_staying_inn_mbr(
	long ls_mbr_n, stay_inn_kind_t kind
)
{
	if( ls_mbr_n < 0 )
		return;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return;
	if( kind < 0 )
		return;
	if( kind >= STAY_INN_KIND_MAX_N )
		return;

	playing_report_ls_mbr[ls_mbr_n].staying_inn[kind]++;
}

/***************************************************************
* 統計データの「宿屋」を更新 (パーティ)
* stay_inn_kind_t kind : 宿泊の種類
***************************************************************/

void	update_playing_report_staying_inn_party(
	stay_inn_kind_t kind
)
{
	if( kind < 0 )
		return;
	if( kind >= STAY_INN_KIND_MAX_N )
		return;

	playing_report_party.staying_inn[kind]++;
}

/***************************************************************
* 統計データの「装備」を更新
* long ls_mbr_n : メンバー・リスト番号
* equip_kind_t kind : 装備の種類
***************************************************************/

void	update_playing_report_wearing_equip(
	long ls_mbr_n, equip_kind_t kind
)
{
	if( ls_mbr_n < 0 )
		return;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return;
	if( kind < 0 )
		return;
	if( kind >= EQUIP_KIND_MAX_N )
		return;

	playing_report_ls_mbr[ls_mbr_n].wearing_equip[kind]++;
	playing_report_party.wearing_equip[kind]++;
}

/***************************************************************
* 統計データの「与ダメージ」を更新
* long ls_mbr_n : メンバー・リスト番号
* resi_kind_t kind : 抵抗値の属性の種類
***************************************************************/

void	update_playing_report_making_dam(
	long ls_mbr_n, resi_kind_t kind, long dam
)
{
	if( ls_mbr_n < 0 )
		return;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return;
	if( kind < 0 )
		return;
	if( kind >= RESI_KIND_MAX_N )
		return;

	playing_report_ls_mbr[ls_mbr_n].making_dam[kind] += dam;
	playing_report_party.making_dam[kind] += dam;
}

/***************************************************************
* 統計データの「被ダメージ」を更新
* long ls_mbr_n : メンバー・リスト番号
* resi_kind_t kind : 抵抗値の属性の種類
***************************************************************/

void	update_playing_report_made_dam(
	long ls_mbr_n, resi_kind_t kind, long dam
)
{
	if( ls_mbr_n < 0 )
		return;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return;
	if( kind < 0 )
		return;
	if( kind >= RESI_KIND_MAX_N )
		return;

	playing_report_ls_mbr[ls_mbr_n].made_dam[kind] += dam;
	playing_report_party.made_dam[kind] += dam;
}

/***************************************************************
* 統計データの「使用した呪文」を更新
* long ls_mbr_n : メンバー・リスト番号
* spell_kind_t kind : 呪文の種類
***************************************************************/

void	update_playing_report_using_spell(
	long ls_mbr_n, spell_kind_t kind
)
{
	if( ls_mbr_n < 0 )
		return;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return;
	if( kind < 0 )
		return;
	if( kind >= SPELL_KIND_MAX_N )
		return;

	playing_report_ls_mbr[ls_mbr_n].using_spell[kind]++;
	playing_report_party.using_spell[kind]++;
}

/***************************************************************
* 統計データの「使用された呪文」を更新
* long ls_mbr_n : メンバー・リスト番号
* spell_kind_t kind : 呪文の種類
***************************************************************/

void	update_playing_report_used_spell(
	long ls_mbr_n, spell_kind_t kind
)
{
	if( ls_mbr_n < 0 )
		return;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return;
	if( kind < 0 )
		return;
	if( kind >= SPELL_KIND_MAX_N )
		return;

	playing_report_ls_mbr[ls_mbr_n].used_spell[kind]++;
	playing_report_party.used_spell[kind]++;
}

/***************************************************************
* 統計データの並び換え (1 つ分)
* n : 開始位置
* long d : 先頭(-1)/末尾(+1)
***************************************************************/

void	arrange_playing_report_1( long n, long d )
{
	playing_report_t	tmp;

	if( n < 0 )
		return;
	if( n >= LS_MBR_MAX_N )
		return;

	tmp = playing_report_ls_mbr[n];
	playing_report_ls_mbr[n]
			= playing_report_ls_mbr[n + d];
	playing_report_ls_mbr[n + d] = tmp;
}

/***************************************************************
* 統計データの並び換え
* long n : 開始位置
* long d : 先頭(-1)/末尾(+1)
***************************************************************/

void	arrange_playing_report( long n, long d )
{
	playing_report_t	tmp;
	long	i;

	if( n < 0 )
		return;
	if( n >= LS_MBR_MAX_N )
		return;

	tmp = playing_report_ls_mbr[n];
	if( d <= -1 ){
		for( i = n - 1; i >= 0; i-- ){
			playing_report_ls_mbr[i + 1]
					= playing_report_ls_mbr[i];
		}

		playing_report_ls_mbr[0] = tmp;
	} else {
		mbr_t	**ls_mbr;

		ls_mbr = get_ls_mbr();
		for( i = n + 1; i < LS_MBR_MAX_N; i++ ){
			if( chk_flg( ls_mbr[i]->stat,
					FLG_STAT_NOT_EXIST ) ){
				break;
			}

			playing_report_ls_mbr[i - 1]
					= playing_report_ls_mbr[i];
		}

		playing_report_ls_mbr[i - 1] = tmp;
	}
}

/***************************************************************
* メンバーの統計データを返す
* long ls_mbr_n : メンバー・リスト番号
* return : 統計データ
***************************************************************/

playing_report_t	*get_playing_report_mbr( long ls_mbr_n )
{
	if( ls_mbr_n < 0 )
		return NULL;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return NULL;

	return &(playing_report_ls_mbr[ls_mbr_n]);
}

/***************************************************************
* パーティの統計データを返す
* return : 統計データ
***************************************************************/

playing_report_t	*get_playing_report_party( void )
{
	return &playing_report_party;
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_play_rep_c( void )
{
	check_memory( check_memory_play_rep_c_playing_report_ls_mbr,
			"play-rep.c: playing_report_ls_mbr" );
	check_memory( check_memory_play_rep_c_playing_report_party,
			"play-rep.c: playing_report_party" );
}
