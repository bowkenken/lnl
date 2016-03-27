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
* $Id: play-rep.c,v 1.4 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ���ץǡ���
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

	/* ���С������ץǡ��� */

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

	/* �ѡ��ƥ������ץǡ��� */

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
* ���ץǡ����Ρֻ�ʧ���פ򹹿�
* long ls_mbr_n : ���С����ꥹ���ֹ�
* gold_t gold : ���
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
* ���ץǡ����Ρֽɲ��פ򹹿� (���С�)
* long ls_mbr_n : ���С����ꥹ���ֹ�
* stay_inn_kind_t kind : ����μ���
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
* ���ץǡ����Ρֽɲ��פ򹹿� (�ѡ��ƥ�)
* stay_inn_kind_t kind : ����μ���
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
* ���ץǡ����Ρ������פ򹹿�
* long ls_mbr_n : ���С����ꥹ���ֹ�
* equip_kind_t kind : �����μ���
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
* ���ץǡ����Ρ�Ϳ���᡼���פ򹹿�
* long ls_mbr_n : ���С����ꥹ���ֹ�
* resi_kind_t kind : ���ͤ�°���μ���
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
* ���ץǡ����Ρ�����᡼���פ򹹿�
* long ls_mbr_n : ���С����ꥹ���ֹ�
* resi_kind_t kind : ���ͤ�°���μ���
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
* ���ץǡ����Ρֻ��Ѥ�����ʸ�פ򹹿�
* long ls_mbr_n : ���С����ꥹ���ֹ�
* spell_kind_t kind : ��ʸ�μ���
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
* ���ץǡ����Ρֻ��Ѥ��줿��ʸ�פ򹹿�
* long ls_mbr_n : ���С����ꥹ���ֹ�
* spell_kind_t kind : ��ʸ�μ���
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
* ���ץǡ������¤Ӵ��� (1 ��ʬ)
* n : ���ϰ���
* long d : ��Ƭ(-1)/����(+1)
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
* ���ץǡ������¤Ӵ���
* long n : ���ϰ���
* long d : ��Ƭ(-1)/����(+1)
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
* ���С������ץǡ������֤�
* long ls_mbr_n : ���С����ꥹ���ֹ�
* return : ���ץǡ���
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
* �ѡ��ƥ������ץǡ������֤�
* return : ���ץǡ���
***************************************************************/

playing_report_t	*get_playing_report_party( void )
{
	return &playing_report_party;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_play_rep_c( void )
{
	check_memory( check_memory_play_rep_c_playing_report_ls_mbr,
			"play-rep.c: playing_report_ls_mbr" );
	check_memory( check_memory_play_rep_c_playing_report_party,
			"play-rep.c: playing_report_party" );
}
