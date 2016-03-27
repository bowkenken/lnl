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
* $Id: nest-flg.c,v 1.13 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* �ͥ��Ȳ�ǽ�ե饰
***************************************************************/

#include	"gmain.h"
#include	"nest-flg.h"
#include	"gmain-prot.h"
#include	"nest-flg-prot.h"

/***************************************************************/

static long	g_nest_flg[NEST_FLG_MAX_N];
check_memory_def( check_memory_nest_flg_c_g_nest_flg )
static long	g_nest_flg_n;
check_memory_def( check_memory_nest_flg_c_g_nest_flg_n )

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_nest_flg( void )
{
}

/***************************************************************
* �ե饰�κ���
* return : �ե饰�ֹ��return <= -1 ���顼��
***************************************************************/

long	make_nest_flg( void )
{
	if( g_nest_flg_n + 1 > NEST_FLG_MAX_N )
		return -1;

	g_nest_flg[g_nest_flg_n] = 0;

	g_nest_flg_n++;

	return( g_nest_flg_n - 1 );
}

/***************************************************************
* �ͥ��ȳ���
* long flg_n : �ե饰�ֹ�
* return : �ͥ��Ȥο�����return <= -1 ���顼��
***************************************************************/

long	bgn_nest_flg( long flg_n )
{
	return set_nest_flg( flg_n, +1 );
}

/***************************************************************
* �ͥ��Ƚ�λ
* long flg_n : �ե饰�ֹ�
* return : �ͥ��Ȥο�����return <= -1 ���顼��
***************************************************************/

long	end_nest_flg( long flg_n )
{
	return set_nest_flg( flg_n, -1 );
}

/***************************************************************
* �ͥ�������
* long flg_n : �ե饰�ֹ�
* long n : �ͥ��Ȥο����ν�����
* return : �ͥ��Ȥο�����return <= -1 ���顼��
***************************************************************/

long	set_nest_flg( long flg_n, long n )
{
	if( g_nest_flg_n < 0 )
		return -1;
	if( g_nest_flg_n >= NEST_FLG_MAX_N )
		return -1;

	g_nest_flg[flg_n] += n;

	return g_nest_flg[flg_n];
}

/***************************************************************
* �ͥ����椫Ĵ�٤�
* long flg_n : �ե饰�ֹ�
* return : �ͥ����椫?
***************************************************************/

long	chk_nest_flg( long flg_n )
{
	return g_nest_flg[flg_n];
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_nest_flg_c( void )
{
	check_memory( check_memory_nest_flg_c_g_nest_flg,
			"nest-flg.c: g_nest_flg" );
	check_memory( check_memory_nest_flg_c_g_nest_flg_n,
			"nest-flg.c: g_nest_flg_n" );
}
