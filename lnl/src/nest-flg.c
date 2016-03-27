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
* $Id: nest-flg.c,v 1.13 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ネスト可能フラグ
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
* スタティック変数をリセット
***************************************************************/

void	reset_static_nest_flg( void )
{
}

/***************************************************************
* フラグの作成
* return : フラグ番号（return <= -1 エラー）
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
* ネスト開始
* long flg_n : フラグ番号
* return : ネストの深さ（return <= -1 エラー）
***************************************************************/

long	bgn_nest_flg( long flg_n )
{
	return set_nest_flg( flg_n, +1 );
}

/***************************************************************
* ネスト終了
* long flg_n : フラグ番号
* return : ネストの深さ（return <= -1 エラー）
***************************************************************/

long	end_nest_flg( long flg_n )
{
	return set_nest_flg( flg_n, -1 );
}

/***************************************************************
* ネスト設定
* long flg_n : フラグ番号
* long n : ネストの深さの修整値
* return : ネストの深さ（return <= -1 エラー）
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
* ネスト中か調べる
* long flg_n : フラグ番号
* return : ネスト中か?
***************************************************************/

long	chk_nest_flg( long flg_n )
{
	return g_nest_flg[flg_n];
}

/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_nest_flg_c( void )
{
	check_memory( check_memory_nest_flg_c_g_nest_flg,
			"nest-flg.c: g_nest_flg" );
	check_memory( check_memory_nest_flg_c_g_nest_flg_n,
			"nest-flg.c: g_nest_flg_n" );
}
