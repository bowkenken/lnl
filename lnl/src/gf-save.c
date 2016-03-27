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
* $Id: gf-save.c,v 1.48 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* ファイル入出力 (ゲーム・データ)
***************************************************************/

#define	GFILE_C
#include	"inc.h"

/***************************************************************
* ゲーム・データのロード
* bool_t flg_txt : テキスト・モードか?
* long n : データ・スロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data( bool_t flg_txt, long n )
{
	FILE	*fp;
	ver_t	ver;
	dun_t	*dun;

	reset_static();

	g_load_slot_n = n;
	set_flg_exit_shop( TRUE );

	/* ファイルのオープン */

	fp = open_game_data( 'r', n, flg_txt );
	if( fp == NULL )
		return FALSE;

	/* ヘッダの読み込み */

	set_flg_crypt_txt( TRUE );
	load_game_data_head_ver_1( fp, &ver, flg_txt );
	set_flg_crypt_txt( flg_txt );

	/* バージョンのチェック */

	if( chk_ver_new( &ver,
			GAME_DATA_VER_MJR,
			GAME_DATA_VER_MNR,
			GAME_DATA_VER_PAT ) ){
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_A,
				ver.mjr, ver.mnr, ver.pat );
		print_msg( FLG_MSG_ERR, MSG_ERR_FILE_VER_B );

		fclose( fp );
		return FALSE;
	}

	/* データの初期化 */

	reset_load_game_data();

	/* データの読み込み */

	switch( ver.mjr ){
	case 1:
		if( !load_game_data_ver_1( fp, &ver, flg_txt ) ){
			fclose( fp );
			return FALSE;
		}
		break;
	default:
		fclose( fp );

		print_lex_err( MSG_ERR_FILE_VER_A,
				ver.mjr, ver.mnr, ver.pat );
		print_lex_err( MSG_ERR_FILE_VER_B );

		exit_game( EXIT_FAILURE );
		return FALSE;
		break;
	}

	/* ファイルのクローズ */

	if( fclose( fp ) == EOF )
		return FALSE;

	/* バージョナップ */

	if( chk_ver_old( &ver, 1, 0, 4 ) )
		ver_up_game_data_1_0_4();

	if( chk_ver_old( &ver, 1, 1, 1 ) )
		ver_up_game_data_1_1_1();

	if( chk_ver_old( &ver, 1, 2, 6 ) )
		ver_up_game_data_1_2_6();

	if( chk_ver_old( &ver, 1, 2, 12 ) )
		ver_up_game_data_1_2_12();

	if( chk_ver_old( &ver, 1, 2, 27 ) )
		ver_up_game_data_1_2_27();

	/* データが正しいかチェック */

	if( !chk_load_game_data() )
		return FALSE;

	/* ゲーム設定のロード */

	if( chk_ver_new_match( &ver, 1, 1, 0 ) ){
		if( !load_game_data_cnf( n ) ){
			return FALSE;
		}
	} else {
		ver_up_auto_mark_1_1_3();
	}

	/* バージョナップ */

	if( chk_ver_old( &ver, 1, 2, 35 ) )
		ver_up_game_data_1_2_35();

	if( chk_ver_old( &ver, 1, 2, 36 ) )
		ver_up_game_data_1_2_36();

	call_pcg_dun_reload_all_mbr();

	bgn_reg_replay( n );

	up_dun_msg();

	dun = get_dun();
	if( (n != SAVE_N_AUTO) && (dun->lev == 0) )
		set_flg_exit_shop( TRUE );
	else
		set_flg_exit_shop( FALSE );

	return TRUE;
}

/***************************************************************
* ロード後に店から出る処理を実行するかのフラグを設定
* bool_t flg : 店から出るか?
***************************************************************/

void	set_flg_exit_shop( bool_t flg )
{
	g_flg_exit_shop = flg;
}

/***************************************************************
* ロード後に店から出る処理を実行するかのフラグを返す
* return : 店から出るか?
***************************************************************/

bool_t	get_flg_exit_shop( void )
{
	return g_flg_exit_shop;
}

/***************************************************************
* メンバーを酒場に出現させる
***************************************************************/

void	appear_load_game_data( long slot_n )
{
	party_t	*pty = get_party();
	pet_t	**pty_pet = get_party_pet();
	long	i;

	if( slot_n == SAVE_N_AUTO ){
		bool_t	flg_appear;

		flg_appear = FALSE;

		for( i = 0; i < MBR_MAX_N; i++ ){
			if( pty->mbr[i] == NULL )
				continue;
			if( chk_flg( pty->mbr[i]->stat,
					FLG_STAT_NOT_EXIST ) ){
				continue;
			}

			if( pty->mbr[i]->x == MAP_DEL_X ){
				flg_appear = TRUE;
				break;
			}
			if( pty->mbr[i]->y == MAP_DEL_Y ){
				flg_appear = TRUE;
				break;
			}
		}

		for( i = 0; i < PET_MAX_N; i++ ){
			if( pty_pet[i] == NULL )
				continue;

			if( pty_pet[i]->x == MAP_DEL_X ){
				flg_appear = TRUE;
				break;
			}
			if( pty_pet[i]->y == MAP_DEL_Y ){
				flg_appear = TRUE;
				break;
			}
		}

		if( flg_appear ){
			appear_party_auto();
		}
	} else {
		/* 自動セーブ以外は酒場の中に出現する */

		for( i = 0; i < MBR_MAX_N; i++ ){
			if( pty->mbr[i] == NULL )
				continue;

			pty->mbr[i]->x = MAP_DEL_X;
			pty->mbr[i]->y = MAP_DEL_Y;
		}

		for( i = 0; i < PET_MAX_N; i++ ){
			if( pty_pet[i] == NULL )
				continue;

			pty_pet[i]->x = MAP_DEL_X;
			pty_pet[i]->y = MAP_DEL_Y;
		}
	}
}

/***************************************************************
* ゲーム・データのバージョン変換
***************************************************************/

void	ver_up_game_data_1_0_4( void )
{
	mbr_t	**ls_mbr = get_ls_mbr();
	long	i;

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		ver_up_auto_mark_1_0_4( i );
	}
}

/***************************************************************
* ゲーム・データのバージョン変換
***************************************************************/

void	ver_up_game_data_1_1_1( void )
{
	mbr_t	**ls_mbr = get_ls_mbr();
	long	i;

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		ver_up_auto_mark_1_1_1( i );
	}
}

/***************************************************************
* ゲーム・データのバージョン変換
***************************************************************/

void	ver_up_game_data_1_1_3( void )
{
	ver_up_auto_mark_1_1_3();
}

/***************************************************************
* ゲーム・データのバージョン変換
***************************************************************/

void	ver_up_game_data_1_2_6( void )
{
	mbr_t	**ls_mbr = get_ls_mbr();
	long	i;

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		long	a;
		modifier_t	m;

		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		get_modifier_fx( ls_mbr[i], &m );
		for( a = 0; a < ABL_KIND_MAX_N; a++ )
			m.add_lev[a] = 0;
		set_modifier_fx( ls_mbr[i], &m );
	}
}

/***************************************************************
* ゲーム・データのバージョン変換
***************************************************************/

void	ver_up_game_data_1_2_12( void )
{
	char	*info;
	long	i;

	for( i = 0; i < AUTO_MARK_MAX_N; i++ ){
		info = get_msg_ttl_auto_mark_info( i );
		if( strcmp( info, MSG_NAME_DFLT_AUTO_MARK_CLEAR ) == 0 ){
			break;
		}
	}
	i++;
	for( ; i < AUTO_MARK_MAX_N; i++ ){
		info = get_msg_ttl_auto_mark_info( i );
		if( strcmp( info, MSG_NAME_DFLT_AUTO_MARK_CLEAR ) == 0 ){
			set_flg_ena_auto_mark( i, FALSE );
		}
	}
}

/***************************************************************
* ゲーム・データのバージョン変換
***************************************************************/

void	ver_up_game_data_1_2_27( void )
{
	pet_t	**ls_pet = get_ls_pet();
	mnstr_kind_t	k;
	long	i;

	for( i = 0; i < LS_PET_MAX_N; i++ ){
		if( ls_pet[i] == NULL )
			continue;
		if( chk_flg( ls_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		k = get_mnstr_kind_from_face(
				ls_pet[i]->face.mjr_org,
				ls_pet[i]->face.mnr_org );
		ls_pet[i]->mnstr_kind = k;
		ls_pet[i]->mnstr_kind_org = k;
	}
}

/***************************************************************
* ゲーム・データのバージョン変換
***************************************************************/

void	ver_up_game_data_1_2_35( void )
{
	ver_up_auto_mark_1_2_35();
}

/***************************************************************
* ゲーム・データのバージョン変換
***************************************************************/

void	ver_up_game_data_1_2_36( void )
{
	ver_up_auto_mark_1_2_36();
}

/***************************************************************
* ゲーム・データのロード前の初期化
***************************************************************/

void	reset_load_game_data( void )
{
	mbr_t	**ls_mbr = get_ls_mbr();
	pet_t	**ls_pet = get_ls_pet();
	long	i;

	/* 日付とターンの初期化 */

	set_game_day( 0 );
	set_turn( 0 );

	/* キャラクタ・データの初期化 */

	for( i = LS_MBR_MAX_N - 1; i >= 0; i-- ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		remove_mbr( ls_mbr[i] );
	}

	for( i = LS_PET_MAX_N - 1; i >= 0; i-- ){
		if( ls_pet[i] == NULL )
			continue;
		if( chk_flg( ls_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		remove_pet( ls_pet[i] );
	}

	/* 作戦の初期化 */

	reset_ls_flg_ena_auto_mark();

	/* アイテムの初期化 */

	reset_item();
}

/***************************************************************
* ゲーム・データのロード時のチェック
* return : データに異常が無かったか?
***************************************************************/

bool_t	chk_load_game_data( void )
{
	mbr_t	**ls_mbr = get_ls_mbr();
	pet_t	**ls_pet = get_ls_pet();
	long	i, j;

	/* PC のデータを複製していないかチェック */

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		for( j = 0; j < LS_MBR_MAX_N; j++ ){
			if( ls_mbr[j] == NULL )
				continue;
			if( chk_flg( ls_mbr[j]->stat, FLG_STAT_NOT_EXIST ) )
				continue;
			if( i == j )
				continue;

			if( ls_mbr[i]->id1 != ls_mbr[j]->id1 )
				continue;
			if( ls_mbr[i]->id2 != ls_mbr[j]->id2 )
				continue;

			print_lex_err( MSG_S, MSG_ERR_RC_PARSE_CHR_ID );
			exit_game( EXIT_FAILURE );
			return FALSE;
		}
	}

	/* ペットのデータを複製していないかチェック */

	for( i = 0; i < LS_PET_MAX_N; i++ ){
		if( ls_pet[i] == NULL )
			continue;
		if( chk_flg( ls_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		for( j = 0; j < LS_PET_MAX_N; j++ ){
			if( ls_pet[j] == NULL )
				continue;
			if( chk_flg( ls_pet[j]->stat, FLG_STAT_NOT_EXIST ) )
				continue;
			if( i == j )
				continue;

			if( ls_pet[i]->id1 != ls_pet[j]->id1 )
				continue;
			if( ls_pet[i]->id2 != ls_pet[j]->id2 )
				continue;

			print_lex_err( MSG_S, MSG_ERR_RC_PARSE_CHR_ID );
			exit_game( EXIT_FAILURE );
			return FALSE;
		}
	}

	/* 顔文字がおかしくなるバグ対策 */

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		if( ls_mbr[i]->face.mjr == ' ' )
			ls_mbr[i]->face.mjr = '@';
		if( ls_mbr[i]->face.mjr == '\0' )
			ls_mbr[i]->face.mjr = '@';

		if( ls_mbr[i]->face.mnr == ' ' )
			ls_mbr[i]->face.mnr = '@';
		if( ls_mbr[i]->face.mnr == '\0' )
			ls_mbr[i]->face.mnr = '@';

		if( ls_mbr[i]->face.mjr_org == ' ' )
			ls_mbr[i]->face.mjr_org = '@';
		if( ls_mbr[i]->face.mjr_org == '\0' )
			ls_mbr[i]->face.mjr_org = '@';

		if( ls_mbr[i]->face.mnr_org == ' ' )
			ls_mbr[i]->face.mnr_org = '@';
		if( ls_mbr[i]->face.mnr_org == '\0' )
			ls_mbr[i]->face.mnr_org = '@';
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データのヘッダのロード(バージョン 1)
* FILE *fp : ファイル
* ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_head_ver_1( FILE *fp, ver_t *ver, bool_t flg_txt )
{
	const long	len_head = str_len_std( STR_GAME_DATA_HEAD );
	char	*s;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	ver->mjr = 0;
	ver->mnr = 0;
	ver->pat = 0;

	s = load_line( fp, TRUE );
	if( strncmp( s, STR_GAME_DATA_HEAD, len_head ) != 0 ){
		print_lex_err( MSG_S, MSG_ERR_LOAD_GAME_HEAD );
		return FALSE;
	}

	/* バージョン・チェック */

	if( str_len_std( s ) < len_head )
		return FALSE;
	s = &(s[len_head]);

	sscanf( s, " %ld.%ld.%ld ", &(ver->mjr), &(ver->mnr), &(ver->pat) );

	if( (ver->mjr == 0) && (ver->mnr == 0) && (ver->pat == 0) )
		return FALSE;

	/**/

	s = load_line( fp, TRUE );
	sscanf( s, "%ld:", &g_game_data_save_n );

	reset_load_crypt( fp, flg_txt );

	return TRUE;
}

/***************************************************************
* ゲーム・データのロード(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_ver_1( FILE *fp, const ver_t *ver, bool_t flg_txt )
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	clr_map_all_mbr();
	clr_map_all_pet();

	while( 1 ){
		if( !load_game_data_parse_ver_1( fp, ver, flg_txt ) )
			break;
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : パースを続けるか?
***************************************************************/

bool_t	load_game_data_parse_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	rc_token_t	t[MAX_TOKEN];
	rc_union_t	u[MAX_TOKEN];
	bool_t	flg_err_exit, flg_err;
	long	i, j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	flg_err_exit = TRUE;

	for( i = 0; i < MAX_TOKEN; i++ )
		t[i] = RC_TOKEN_EOF;

	for( i = 0; i < MAX_TOKEN; i++ ){
		t[i] = rc_lex( fp, &(u[i]), flg_err_exit );
		if( t[i] == RC_TOKEN_EOF )
			break;
		if( t[i] == '\n' )
			break;
		if( t[i] == RC_TOKEN_ADD_OP ){
			long	sign_n = +1;

			for( j = i + 1; j < MAX_TOKEN; j++ ){
				if( u[i].c == '-' )
					sign_n = -sign_n;

				t[i] = rc_lex( fp, &(u[i]), flg_err_exit );
				if( t[i] != RC_TOKEN_ADD_OP ){
					break;
				}
			}

			if( t[i] == RC_TOKEN_NUM ){
				u[i].n *= sign_n;
			}
		}
	}
	if( i >= MAX_TOKEN ){
		for( i = 0; i < LOOP_MAX_100; i++ ){
			rc_token_t	t;
			rc_union_t	u;

			t = rc_lex( fp, &u, flg_err_exit );
			if( t == RC_TOKEN_EOF )
				break;
			if( t == '\n' )
				break;
		}
	}

	flg_err = FALSE;

	if( t[0] == RC_TOKEN_EOF ){
		return FALSE;
	} else if( t[0] == '\n' ){
		return TRUE;
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == RC_TOKEN_NUM)
			&& (t[3] == '\n') ){
		/* foo = n */

		if( !load_game_data_id_eq_num_ver_1(
				fp, ver, flg_txt,
				u[0].str, u[2].n ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_NUM)
			&& (t[2] == RC_TOKEN_EQ_OP)
			&& (t[3] == RC_TOKEN_STR)
			&& (t[4] == '\n') ){
		/* foo n = "bar" */

		if( !load_game_data_id_num_eq_str_ver_1(
				fp, ver, flg_txt,
				u[0].str, u[1].n, u[3].str ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_EQ_OP)
			&& (t[2] == '{')
			&& (t[3] == '\n') ){
		/* foo = { */

		if( !load_game_data_block_ver_1(
				fp, ver, flg_txt,
				u[0].str, 0 ) ){
			flg_err = TRUE;
		}
	} else if( (t[0] == RC_TOKEN_ID)
			&& (t[1] == RC_TOKEN_NUM)
			&& (t[2] == RC_TOKEN_EQ_OP)
			&& (t[3] == '{')
			&& (t[4] == '\n') ){
		/* foo n = { */

		if( !load_game_data_block_ver_1(
				fp, ver, flg_txt,
				u[0].str, u[1].n ) ){
			flg_err = TRUE;
		}
	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
		flg_err = TRUE;
	}

	if( flg_err ){
		if( flg_err_exit )
			exit_game( EXIT_FAILURE );
		return FALSE;
	} else {
		return TRUE;
	}
}

/***************************************************************
* ゲーム・データのパース(識別子 = 値 : バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* char *id : 識別子
* long n : 値
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_id_eq_num_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *id, long n
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( id == NULL )
		return FALSE;

	if( strcmp( id, "randm_seed" ) == 0 ){
		srandm( n );
		g_randm_seed_save = n;
		return TRUE;
	} else if( strcmp( id, "dun_lev" ) == 0 ){
		dun_t	*dun;

		dun = get_dun();
		dun->lev = n;
		return TRUE;
	} else if( strcmp( id, "day" ) == 0 ){
		set_game_day( n );
		return TRUE;
	} else if( strcmp( id, "turn" ) == 0 ){
		set_turn( n );
		return TRUE;
	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );

		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ゲーム・データのパース(識別子 値 = 文字列 : バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* char *id : 識別子
* long n : 値
* char *str : 文字列
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_id_num_eq_str_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *id, long n, char *str
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( id == NULL )
		return FALSE;
	if( str == NULL )
		return FALSE;

	if( strcmp( id, "auto_mark_title" ) == 0 ){
		return( load_game_data_auto_mark_ttl_ver_1(
				fp, ver, flg_txt, n, str ) );
	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );

		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ゲーム・データの自動マークのタイトルのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long n : 自動マークの番号
* char *ttl : タイトル
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_auto_mark_ttl_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long n, char *ttl
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( ttl == NULL )
		return FALSE;

	if( n < 0 )
		return FALSE;
	if( n > AUTO_MARK_MAX_N - 1 )
		n = AUTO_MARK_MAX_N - 1;

	str_nz_cpy( get_msg_ttl_auto_mark_code( n ), ttl,
			MSG_TTL_AUTO_MARK_MAX_BYTE );

	return TRUE;
}

/***************************************************************
* ゲーム・データのブロックのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* char *id : 識別子
* long n : 値
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_block_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *id, long n
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( id == NULL )
		return FALSE;

	if( strcmp( id, "square" ) == 0 ){
		return( load_game_data_square_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "class" ) == 0 ){
		return( load_game_data_class_ver_1(
				fp, ver, flg_txt, n ) );

	} else if( strcmp( id, "member" ) == 0 ){
		return( load_game_data_mbr_ver_1(
				fp, ver, flg_txt, n ) );

	} else if( strcmp( id, "pet" ) == 0 ){
		return( load_game_data_pet_ver_1(
				fp, ver, flg_txt, n ) );

	} else if( strcmp( id, "potion_color" ) == 0 ){
		return( load_game_data_potion_color_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "scroll_ttl_syllable" ) == 0 ){
		return( load_game_data_scroll_ttl_syllable_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "wand_material" ) == 0 ){
		return( load_game_data_stick_material_ver_1(
				fp, ver, flg_txt, STICK_KIND_WAND ) );

	} else if( strcmp( id, "rod_material" ) == 0 ){
		return( load_game_data_stick_material_ver_1(
				fp, ver, flg_txt, STICK_KIND_ROD ) );

	} else if( strcmp( id, "staff_material" ) == 0 ){
		return( load_game_data_stick_material_ver_1(
				fp, ver, flg_txt, STICK_KIND_STAFF ) );

	} else if( strcmp( id, "ring_material" ) == 0 ){
		return( load_game_data_acce_material_ver_1(
				fp, ver, flg_txt, ACCE_KIND_RING ) );

	} else if( strcmp( id, "amulet_material" ) == 0 ){
		return( load_game_data_acce_material_ver_1(
				fp, ver, flg_txt, ACCE_KIND_AMULET ) );

	} else if( strcmp( id, "necklace_material" ) == 0 ){
		return( load_game_data_acce_material_ver_1(
				fp, ver, flg_txt, ACCE_KIND_NECKLACE ) );

	} else if( strcmp( id, "potion_identified" ) == 0 ){
		return( load_game_data_potion_identified_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "scroll_identified" ) == 0 ){
		return( load_game_data_scroll_identified_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "member_item" ) == 0 ){
		return( load_game_data_item_mbr_ver_1(
				fp, ver, flg_txt, n ) );

	} else if( strcmp( id, "key_item" ) == 0 ){
		return( load_game_data_key_item_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "auto_mark" ) == 0 ){
		return( load_game_data_auto_mark_ls_ver_1(
				fp, ver, flg_txt, n ) );

	} else if( strcmp( id, "auto_mark_appoint_item" ) == 0 ){
		return( load_game_data_auto_mark_appoint_item_ls_ver_1(
				fp, ver, flg_txt, n ) );

	} else if( strcmp( id, "flg_srch" ) == 0 ){
		return( load_game_data_flg_srch_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "spell" ) == 0 ){
		return( load_game_data_spell_ls_ver_1(
				fp, ver, flg_txt, n ) );

	} else if( strcmp( id, "member_formation" ) == 0 ){
		return( load_game_data_mbr_formation_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "pet_formation" ) == 0 ){
		return( load_game_data_pet_formation_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "request" ) == 0 ){
		return( load_game_data_request_ver_1(
				fp, ver, flg_txt ) );

	} else if( strcmp( id, "playing_report_member" ) == 0 ){
		return( load_game_data_playing_report_mbr_ver_1(
				fp, ver, flg_txt, n ) );

	} else if( strcmp( id, "playing_report_party" ) == 0 ){
		return( load_game_data_playing_report_party_ver_1(
				fp, ver, flg_txt, n ) );

	} else {
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_DEF_ID );

		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ゲーム・データのクラスのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_square_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	square_t	*sq;
	long	idx;

	sq = get_square_mbr();
	if( sq == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &(sq->x) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(sq->y) ) )
		return FALSE;

	if( !load_game_data_n( fp, &idx ) )
		return FALSE;
	sq->dir = trans_idx_to_square_dir( idx );

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	reset_mbr_dir();

	return TRUE;
}

/***************************************************************
* ゲーム・データのクラスのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long n : 値
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_class_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long n
)
{
	class_t	*p;
	abl_kind_t	abl_n;
	skill_kind_t	skill_n;
	long	tmp_n;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( n < 0 )
		return FALSE;
	if( n >= CLASS_MAX_N )
		return FALSE;

	p = get_class_tab();
	if( p == NULL )
		return FALSE;

	p[n].n_name = N_MSG_NULL;

	if( !load_game_data_s( fp, p[n].name, CLASS_NAME_MAX_BYTE ) )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	p[n].dflt = (class_dflt_t)tmp_n;


	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		abl_n = trans_idx_to_abl_kind( i );
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p[n].abl_rate[abl_n] = tmp_n;
	}
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( chk_ver_new_match( ver, 1, 2, 19 ) ){
		if( !load_game_data_skip_c( fp, '{', TRUE ) )
			return FALSE;
		for( i = 0; i < SKILL_MAX_N; i++ ){
			if( load_game_data_skip_c( fp, '}', FALSE ) )
				break;

			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;
			abl_n = trans_idx_to_abl_kind( tmp_n );
			skill_n = (skill_kind_t)(abl_n - ABL_KIND_MAX_N);
			p[n].skill[i] = skill_n;
		}
		for( ; i < SKILL_MAX_N; i++ )
			p[n].skill[i] = SKILL_KIND_NULL;

		load_game_data_skip_c( fp, '}', FALSE );
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データのメンバーのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long n : 値
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long n
)
{
	mbr_t	**ls_mbr = get_ls_mbr();

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( n < 0 )
		return FALSE;
	if( n >= LS_MBR_MAX_N )
		return FALSE;

	return( load_game_data_chr_ver_1( fp, ver, flg_txt, ls_mbr[n] ) );
}

/***************************************************************
* ゲーム・データのペットのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long n : 値
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_pet_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long n
)
{
	pet_t	**ls_pet = get_ls_pet();

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	if( n < 0 )
		return FALSE;
	if( n >= LS_PET_MAX_N )
		return FALSE;
	if( ls_pet[n] == NULL )
		return FALSE;

	make_pet_alloc( ls_pet[n], 10, MNSTR_KIND_PYON_PYON );

	return( load_game_data_chr_ver_1( fp, ver, flg_txt, ls_pet[n] ) );
}

/***************************************************************
* ゲーム・データのキャラクタのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long n : 値
* chr_t *chr : キャラクタ
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_chr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
)
{
	mbr_t	**ls_mbr = get_ls_mbr();
	long	tmp_n;
	char	tmp_c;
	long	i, j;
	move_ls_kind_t	k;
	long	max_idx;
	abl_kind_t	abl_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( chr == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->kind = trans_idx_to_chr_kind( tmp_n );

	if( !load_game_data_s( fp, chr->name, CHR_NAME_MAX_BYTE ) )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->id1 = tmp_n;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->id2 = tmp_n;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->mbr_n = tmp_n;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->ls_mbr_n = tmp_n;

	if( chk_ver_old( ver, 1, 2, 33 ) ){
		chr->position_kind = POSITION_KIND_FORWARD;
	} else {
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		chr->position_kind = trans_idx_to_position_kind( tmp_n );
	}

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_c( fp, &tmp_c ) )
		return FALSE;
	chr->face.mjr = tmp_c;
	if( !load_game_data_c( fp, &tmp_c ) )
		return FALSE;
	chr->face.mnr = tmp_c;
	if( !load_game_data_c( fp, &tmp_c ) )
		return FALSE;
	chr->face.mjr_org = tmp_c;
	if( !load_game_data_c( fp, &tmp_c ) )
		return FALSE;
	chr->face.mnr_org = tmp_c;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->race.main = trans_idx_to_main_race_kind( tmp_n );
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->race.sub = trans_idx_to_sub_race_kind( tmp_n );
	if( !load_game_data_s( fp, chr->race.name, RACE_NAME_MAX_BYTE ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->sex.cur = trans_idx_to_sex_kind( tmp_n );
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->sex.org = trans_idx_to_sex_kind( tmp_n );
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->x = MAP_DEL_X;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->y = MAP_DEL_Y;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->pre_x = MAP_DEL_X;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->pre_y = MAP_DEL_Y;

	if( !load_game_data_n( fp, &(chr->dx) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->dy) ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->move.speed.rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->move.speed.rate_org) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->move.speed.n) ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->move.force_kind = trans_idx_to_move_kind( tmp_n );

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;

	max_idx = get_move_ls_trans_tab_max_n();
	for( i = 0; i < max_idx; i++ ){
		if( !load_game_data_skip_c( fp, '{', FALSE ) )
			break;

		k = trans_idx_to_move_ls_kind( i );

		for( j = 0; j < MOVE_LS_MAX_N; j++ ){
			if( !load_game_data_skip_c( fp, '{', FALSE ) )
				break;

			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;
			chr->move.ls[k][j].kind = trans_idx_to_move_kind(
					tmp_n );

			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;
			chr->move.ls[k][j].ratio = tmp_n;

			if( !load_game_data_skip_c( fp, '}', TRUE ) )
				return FALSE;
			if( !load_game_data_skip_c( fp, ',', TRUE ) )
				return FALSE;
		}

		/* バージョナップで多くなった場合、足りない分を補う */

		for( ; j < MOVE_LS_MAX_N; j++ ){
			chr->move.ls[k][j].kind = MOVE_KIND_NULL;
			chr->move.ls[k][j].ratio = (ratio_t)0;
		}

		/* バージョナップで少くなった場合、多い分を読み飛ばす */

		for( j = 0; j < LOOP_MAX_100; j++ ){
			if( !load_game_data_skip_c( fp, '{', FALSE ) )
				break;

			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;
			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;

			if( !load_game_data_skip_c( fp, '}', TRUE ) )
				return FALSE;
			if( !load_game_data_skip_c( fp, ',', TRUE ) )
				return FALSE;
		}

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	/* バージョナップで多くなった場合、足りない分を補う */

	for( ; i < max_idx; i++ ){
		k = trans_idx_to_move_ls_kind( i );

		for( j = 0; j < MOVE_LS_MAX_N; j++ ){
			chr->move.ls[k][j].kind = MOVE_KIND_NULL;
			chr->move.ls[k][j].ratio = (ratio_t)0;
		}
	}

	/* バージョナップで少くなった場合、多い分を読み飛ばす */

	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( !load_game_data_skip_c( fp, '{', FALSE ) )
			break;

		for( j = 0; j < LOOP_MAX_100; j++ ){
			if( !load_game_data_skip_c( fp, '{', FALSE ) )
				break;

			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;
			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;

			if( !load_game_data_skip_c( fp, '}', TRUE ) )
				return FALSE;
			if( !load_game_data_skip_c( fp, ',', TRUE ) )
				return FALSE;
		}

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &(chr->gold) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(chr->dun_max_lev_floor) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->dun_max_lev_base) ) )
		return FALSE;

	/* trgt_t	trgt; */
	/* act_t	act, pre_act; */

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->flg_chr = tmp_n;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->flg_map = tmp_n;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->attitude = trans_idx_to_attitude_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	if( tmp_n > -1 )
		chr->owner = ls_mbr[tmp_n];
	else
		chr->owner = NULL;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->stat = tmp_n;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		abl_n = trans_idx_to_abl_kind( i );
		if( !load_game_data_skip_c( fp, '{', TRUE ) )
			return FALSE;
		if( !load_game_data_n( fp, &(chr->abl.exp[abl_n].n) ) )
			return FALSE;
		if( !load_game_data_n( fp, &(chr->abl.exp[abl_n].max) ) )
			return FALSE;

		if( !load_game_data_n( fp, &(chr->abl.lev[abl_n].n) ) )
			return FALSE;
		if( !load_game_data_n( fp, &(chr->abl.lev[abl_n].max) ) )
			return FALSE;
		if( !load_game_data_n( fp, &(chr->abl.lev[abl_n].add) ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->abl.hp.n) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->abl.hp.max) ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->abl.mp.n) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->abl.mp.max) ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &(chr->class_n) ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < RESI_KIND_MAX_N; i++ ){
		if( !load_game_data_skip_c( fp, '{', TRUE ) )
			return FALSE;

		if( !load_game_data_n( fp, &(chr->resi[i].n) ) )
			return FALSE;
		if( !load_game_data_n( fp, &(chr->resi[i].max) ) )
			return FALSE;
		if( !load_game_data_n( fp, &(chr->resi[i].add_n) ) )
			return FALSE;

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &(chr->add_def) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->add_crtcl) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->add_ac) ) )
		return FALSE;

	if( !load_game_data_chr_fx_all_ver_1(
			fp, ver, flg_txt, chr ) ){
		return FALSE;
	}

	if( !load_game_data_fx_data_ver_1(
			fp, ver, flg_txt, &(chr->fx_data) ) ){
		return FALSE;
	}

	if( !load_game_data_modifier_ver_1(
			fp, ver, flg_txt, &(chr->modifier_equip) ) ){
		return FALSE;
	}
	if( !load_game_data_modifier_ver_1(
			fp, ver, flg_txt, &(chr->modifier_fx) ) ){
		return FALSE;
	}

	if( chk_ver_new_match( ver, 1, 2, 10 ) ){
		if( !load_game_data_n( fp, &(chr->contribution) ) )
			return FALSE;
	}

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->mnstr_kind = trans_idx_to_mnstr_kind( tmp_n );

	if( chk_ver_old( ver, 1, 2, 27 ) ){
		chr->mnstr_kind_org = chr->mnstr_kind;
	} else {
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		chr->mnstr_kind_org = trans_idx_to_mnstr_kind( tmp_n );
	}

	if( chr->kind == CHR_KIND_MBR ){
		chr->mnstr_tab = NULL;
	} else {
		chr->mnstr_tab = get_mnstr_tab(
				chr->mnstr_kind, 0 );
		chr->mnstr_tab_org = get_mnstr_tab(
				chr->mnstr_kind_org, 0 );
	}

	/* その他ワーク */

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	chr->work.flg = tmp_n;

	if( !load_game_data_n( fp, &(chr->work.caught) ) )
		return FALSE;

	chr->work.catch_chr = NULL;
	chr->work.link_chr = NULL;

	if( !load_game_data_n( fp, &(chr->work.teleport_n) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->work.teleport_party_n) ) )
		return FALSE;

	if( chk_ver_new_match( ver, 1, 2, 10 ) ){
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		chr->work.flg_can_wish = tmp_n;
	}

	if( chk_ver_new_match( ver, 1, 1, 4 ) ){
		request_t	*req_ls = get_request_ls();

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;

		if( tmp_n <= -1 )
			chr->work.request = NULL;
		else if( tmp_n >= REQUEST_MAX_N )
			chr->work.request = NULL;
		else
			chr->work.request = &(req_ls[tmp_n]);
	}

	if( !load_game_data_n( fp, &(chr->work.towner_dx) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(chr->work.towner_dy) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(chr->work.dismissal_turn) ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( chk_ver_new_match( ver, 1, 2, 7 ) ){
		if( !load_game_data_s( fp, chr->graph_name,
				FILE_NAME_MAX_LEN ) ){
			return FALSE;
		}
	}

	/**/

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	clr_chr_trgt_act( chr, TRUE );

	return TRUE;
}

/***************************************************************
* ゲーム・データのキャラクタの全ての効果のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* chr_t *chr : キャラクタ
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_chr_fx_all_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( chr == NULL )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;

	if( load_game_data_skip_c( fp, '}', FALSE ) ){
		/* データが空の場合 */

		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;

		return TRUE;
	}

	while( 1 ){
		if( !load_game_data_skip_c( fp, '{', FALSE ) )
			break;

		if( !load_game_data_chr_fx_ver_1( fp, ver, flg_txt, chr ) )
			return FALSE;

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データのキャラクタの各々の効果のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* chr_t *chr : キャラクタ
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_chr_fx_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
)
{
	fx_t	*fx;
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( chr == NULL )
		return FALSE;

	fx = asgn_fx( chr->fx.next );
	if( fx == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	fx->kind = trans_idx_to_fx_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	fx->turn = tmp_n;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	fx->n = tmp_n;

	fx->chr = chr;
	fx->cast_chr = NULL;

	/* セーブ・ファイルが読み込めないバグの応急処置 */

	if( !load_game_data_n( fp, &tmp_n ) ){
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;

		tmp_n = ABL_KIND_HP;
	}
	fx->abl_kind = (abl_kind_t)tmp_n;

	return TRUE;
}

/***************************************************************
* ゲーム・データの効果のデータのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* fx_data_t *fx_data : 効果の記憶先
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_fx_data_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	fx_data_t *fx_data
)
{
	long	pre_num_mode;
	long	tmp_n;

	pre_num_mode = 0;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( fx_data == NULL )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &(fx_data->wpn_hit) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->wpn_crtcl) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->wpn_dam) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(fx_data->armor_def) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->armor_crtcl) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->armor_ac) ) )
		return FALSE;

	if( chk_ver_old( ver, 1, 2, 21 ) ){
		pre_num_mode = g_rc_lex_num_mode;
		g_rc_lex_num_mode = 16;
	}
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	fx_data->resi_stat = tmp_n;
	if( chk_ver_old( ver, 1, 2, 21 ) )
		g_rc_lex_num_mode = pre_num_mode;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->cure_hp.count) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->cure_hp.turn) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->cure_hp.rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->cure_hp.n) ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->cure_mp.count) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->cure_mp.turn) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->cure_mp.rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->cure_mp.n) ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &(fx_data->infra_vision) ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->stomach.rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->stomach.full_rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->stomach.digest_p_day) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->stomach.digest_n) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->stomach.hungry_rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->stomach.starvation_rate) ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &(fx_data->drunk_rate) ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->nicotine.rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->nicotine.poisoning_rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(fx_data->nicotine.lost_rate) ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &(fx_data->friend_turn) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(fx_data->bless) ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの修正値のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* modifier_t *m : 修正値の記憶先
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_modifier_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	modifier_t *m
)
{
	abl_kind_t	abl_n;
	long	tmp_n;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( m == NULL )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;

	if( !load_game_data_c( fp, &(m->face_mjr) ) )
		return FALSE;
	if( !load_game_data_c( fp, &(m->face_mnr) ) )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	m->sex = trans_idx_to_sex_kind( tmp_n );

	if( !load_game_data_n( fp, &(m->wpn_hit) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->wpn_crtcl) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->wpn_dam) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(m->armor_def) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->armor_crtcl) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->armor_ac) ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < LOOP_MAX_100; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		abl_n = trans_idx_to_abl_kind( i );
		if( !load_game_data_n( fp, &(m->add_lev[abl_n]) ) )
			return FALSE;
	}
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < RESI_KIND_MAX_N; i++ ){
		if( !load_game_data_n( fp, &(m->add_resi_n[i]) ) )
			return FALSE;
	}
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	m->resi_stat = tmp_n;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->cure_hp.count) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->cure_hp.turn) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->cure_hp.rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->cure_hp.n) ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->cure_mp.count) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->cure_mp.turn) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->cure_mp.rate) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->cure_mp.n) ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	if( !load_game_data_n( fp, &(m->add_move_speed) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(m->stomach_digest_n) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(m->teleport_n) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(m->teleport_party_n) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(m->bless) ) )
		return FALSE;

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの薬の色のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_potion_color_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	ls_identified_t	*tab;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	tab = get_color_tab();

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( !load_game_data_n( fp, &(tab[i].name_idx) ) )
			return FALSE;

		tab[i].flg_used = FALSE;

		if( tab[i].name_idx <= -1 )
			break;
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	reset_potion_tab();
	reset_potion_color();

	return TRUE;
}

/***************************************************************
* ゲーム・データの巻物のタイトルのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_scroll_ttl_syllable_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	scroll_tab_t	*tab;
	long	i, j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	tab = get_scroll_tab_head();

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		long	ttl_n;
		long	tmp_n;

		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_skip_c( fp, '{', TRUE ) )
			return FALSE;

		ttl_n = 0;
		for( j = 0; j < SCROLL_TTL_SYLLABLE_MAX_N; j++ ){
			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;

			tab[i].ttl_idx[j] = tmp_n;
			if( tmp_n > -1 )
				ttl_n++;
		}
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;

		tab[i].ttl_idx[j] = -1;
		tab[i].ttl_n = ttl_n;

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	reset_scroll_ttl_syllable();

	return TRUE;
}

/***************************************************************
* ゲーム・データの杖の材質のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* stick_kind_t kind : 杖の種類
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_stick_material_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	stick_kind_t kind
)
{
	ls_identified_t	*tab;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	tab = NULL;

	switch( kind ){
	case STICK_KIND_NULL:
	case STICK_KIND_MAX_N:
		break;
	case STICK_KIND_WAND:
		tab = get_wand_material_tab();
		break;
	case STICK_KIND_ROD:
		tab = get_rod_material_tab();
		break;
	case STICK_KIND_STAFF:
		tab = get_staff_material_tab();
		break;
	}
	if( tab == NULL )
		return FALSE;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( !load_game_data_n( fp, &(tab[i].name_idx) ) )
			return FALSE;

		tab[i].flg_used = FALSE;

		if( tab[i].name_idx <= -1 )
			break;
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	switch( kind ){
	case STICK_KIND_NULL:
	case STICK_KIND_MAX_N:
		break;
	case STICK_KIND_WAND:
		reset_wand_tab();
		reset_wand_material();
		break;
	case STICK_KIND_ROD:
		reset_rod_tab();
		reset_rod_material();
		break;
	case STICK_KIND_STAFF:
		reset_staff_tab();
		reset_staff_material();
		break;
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データのアクセサリの材質のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* acce_kind_t kind : アクセサリの種類
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_acce_material_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	acce_kind_t kind
)
{
	ls_identified_t	*tab;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	tab = NULL;

	switch( kind ){
	case ACCE_KIND_NULL:
	case ACCE_KIND_MAX_N:
		break;
	case ACCE_KIND_RING:
		tab = get_ring_material_tab();
		break;
	case ACCE_KIND_AMULET:
		tab = get_amulet_material_tab();
		break;
	case ACCE_KIND_NECKLACE:
		tab = get_necklace_material_tab();
		break;
	}
	if( tab == NULL )
		return FALSE;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( !load_game_data_n( fp, &(tab[i].name_idx) ) )
			return FALSE;

		tab[i].flg_used = FALSE;

		if( tab[i].name_idx <= -1 )
			break;
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	switch( kind ){
	case ACCE_KIND_NULL:
	case ACCE_KIND_MAX_N:
		break;
	case ACCE_KIND_RING:
		reset_ring_tab();
		reset_ring_material();
		break;
	case ACCE_KIND_AMULET:
		reset_amulet_tab();
		reset_amulet_material();
		break;
	case ACCE_KIND_NECKLACE:
		reset_necklace_tab();
		reset_necklace_material();
		break;
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データの薬の識別フラグのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_potion_identified_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	potion_tab_t	*tab;
	potion_kind_t	kind;
	long	flg;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	tab = get_potion_tab_head();

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &flg ) )
			return FALSE;

		kind = trans_idx_to_potion_kind( i );
		tab[kind].flg_identified = (bool_t)flg;
	}

	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの巻物の識別フラグのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_scroll_identified_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	scroll_tab_t	*tab;
	scroll_kind_t	kind;
	long	flg;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	tab = get_scroll_tab_head();

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &flg ) )
			return FALSE;

		kind = trans_idx_to_scroll_kind( i );
		tab[kind].flg_identified = (bool_t)flg;
	}

	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データのメンバーのアイテムのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
)
{
	mbr_t	**ls_mbr;
	mbr_t	*mbr;
	rc_token_t	t;
	rc_union_t	u;
	item_t	*item;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( ls_mbr_n < 0 )
		return FALSE;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return FALSE;

	ls_mbr = get_ls_mbr();
	mbr = ls_mbr[ls_mbr_n];

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		bool_t	flg_eq;

		/* アイテムの識別子をチェック */

		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		t = rc_lex( fp, &u, TRUE );
		if( t == '}' )
			break;
		if( t != RC_TOKEN_ID ){
			print_lex_err( MSG_S, MSG_ERR_RC_PARSE );
			return FALSE;
		}

		flg_eq = TRUE;
		if( strcmp( u.str, "item" ) == 0 ){
			flg_eq = FALSE;

			if( !load_game_data_skip_token(
					fp, RC_TOKEN_EQ_OP, TRUE ) ){
				return FALSE;
			}
			if( !load_game_data_skip_c( fp, '{', TRUE ) )
				return FALSE;

			item = alloc_item();
			if( item == NULL )
				return FALSE;
		} else if( strcmp( u.str, "equip" ) == 0 ){
			rc_token_t	t;
			rc_union_t	u;

			flg_eq = TRUE;

			t = rc_lex( fp, &u, TRUE );
			if( t != RC_TOKEN_NUM ){
				return FALSE;
			}

			if( !load_game_data_skip_token(
					fp, RC_TOKEN_EQ_OP, TRUE ) ){
				return FALSE;
			}
			if( !load_game_data_skip_c( fp, '{', TRUE ) )
				return FALSE;

			item = get_mbr_item_asgn_equip( mbr );
			if( item == NULL )
				return FALSE;
			item = &(item[u.n]);
		} else {
			return FALSE;
		}

		/* データのロード */

		if( !load_game_data_item_ver_1(
				fp, ver, flg_txt, mbr, item ) ){
			return FALSE;
		}

		/* データ・ブロックの終端をチェック */

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;

		/* アイテムをキャラクタに持たせる */

		if( !flg_eq ){
			if( !give_mbr_item( mbr, item, TRUE ) ){
				return FALSE;
			}
		}
	}

	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データのアイテムのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;
	char	tmp_c;
	bool_t	flg_success;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->kind = trans_idx_to_item_kind( tmp_n );

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;

	flg_success = FALSE;

	switch( item->kind ){
	case ITEM_KIND_NULL:
		return FALSE;
	case ITEM_KIND_WPN:
		flg_success = load_game_data_item_wpn_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_ARMOR:
		flg_success = load_game_data_item_armor_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_POTION:
		flg_success = load_game_data_item_potion_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_SCROLL:
		flg_success = load_game_data_item_scroll_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_STICK:
		flg_success = load_game_data_item_stick_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_ACCE:
		flg_success = load_game_data_item_acce_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_INST:
		flg_success = load_game_data_item_inst_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_ANTHOLOGY:
		flg_success = load_game_data_item_anthology_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_LIGHT:
		flg_success = load_game_data_item_light_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_SPIKE:
		flg_success = load_game_data_item_spike_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_FOOD:
		flg_success = load_game_data_item_food_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_CHEST:
		flg_success = load_game_data_item_chest_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_TOBACCO:
		flg_success = load_game_data_item_tobacco_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_PIPE:
		flg_success = load_game_data_item_pipe_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_DISPOSAL:
		flg_success = load_game_data_item_disposal_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_RARE_GOODS:
		flg_success = load_game_data_item_rare_goods_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_BONE:
		flg_success = load_game_data_item_bone_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_COIN:
		flg_success = load_game_data_item_coin_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_JUNK:
		flg_success = load_game_data_item_junk_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_MAX_N:
		return FALSE;
	}
	if( !flg_success )
		return FALSE;

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	/* item->next, item->prev */

	if( !load_game_data_s( fp, item->name,
			ITEM_NAME_MAX_BYTE ) ){
		return FALSE;
	}
	if( !load_game_data_s( fp, item->art_name,
			ITEM_ART_NAME_MAX_BYTE ) ){
		return FALSE;
	}
	if( chk_ver_new_match( ver, 1, 2, 25 ) ){
		if( !load_game_data_s( fp, item->alias,
				ITEM_NAME_MAX_BYTE ) ){
			return FALSE;
		}
	}

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->equip_kind = (equip_kind_t)tmp_n;

	if( !load_game_data_c( fp, &tmp_c ) )
		return FALSE;
	item->mjr = tmp_c;
	if( !load_game_data_c( fp, &tmp_c ) )
		return FALSE;
	item->mnr = tmp_c;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->x = tmp_n;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->y = tmp_n;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->n = tmp_n;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->stock = tmp_n;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->flg = tmp_n;

	if( !load_game_data_modifier_ver_1(
			fp, ver, flg_txt, &(item->modifier) ) ){
		return FALSE;
	}

	/* 名前をリセット */

	set_item_name( item );

	return TRUE;
}

/***************************************************************
* ゲーム・データの武器のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_wpn_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	wpn_randm_art_kind_t	art;
	long	tmp_n;
	char	tmp_c;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.wpn.kind = trans_idx_to_wpn_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.wpn.add_hit = tmp_n;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.wpn.add_crtcl = tmp_n;
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.wpn.add_dam = tmp_n;

	if( !load_game_data_c( fp, &tmp_c ) )
		return FALSE;
	item->dat.wpn.slayer = tmp_c;

	if( chk_ver_new_match( ver, 1, 2, 17 ) ){
		if( !load_game_data_skip_c( fp, '{', TRUE ) )
			return FALSE;

		for( i = 0; i < WPN_RANDM_ART_LS_MAX_N; i++ ){
			if( !load_game_data_skip_c( fp, '{', FALSE ) )
				break;

			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;
			art = trans_idx_to_wpn_randm_art_kind( tmp_n );
			item->dat.wpn.randm_art[i].kind = art;

			if( !load_game_data_c( fp, &tmp_c ) )
				return FALSE;
			item->dat.wpn.randm_art[i].mjr = tmp_c;

			if( !load_game_data_c( fp, &tmp_c ) )
				return FALSE;
			item->dat.wpn.randm_art[i].mnr = tmp_c;

			if( !load_game_data_skip_c( fp, '}', TRUE ) )
				return FALSE;
			if( !load_game_data_skip_c( fp, ',', TRUE ) )
				return FALSE;
		}
		item->dat.wpn.randm_art[i].kind
				= WPN_RANDM_ART_KIND_NULL;
		item->dat.wpn.randm_art[i].mjr = ' ';
		item->dat.wpn.randm_art[i].mnr = ' ';

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.wpn.flg = tmp_n;

	item->tab.wpn = get_wpn_tab( item->dat.wpn.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの防具のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_armor_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	armor_randm_art_kind_t	art;
	long	tmp_n;
	char	tmp_c;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.armor.kind = trans_idx_to_armor_kind( tmp_n );

	if( !load_game_data_n( fp, &(item->dat.armor.add_def) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(item->dat.armor.add_crtcl) ) )
		return FALSE;
	if( !load_game_data_n( fp, &(item->dat.armor.add_ac) ) )
		return FALSE;

	if( chk_ver_new_match( ver, 1, 2, 17 ) ){
		if( !load_game_data_skip_c( fp, '{', TRUE ) )
			return FALSE;

		for( i = 0; i < ARMOR_RANDM_ART_LS_MAX_N; i++ ){
			if( !load_game_data_skip_c( fp, '{', FALSE ) )
				break;

			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;
			art = trans_idx_to_armor_randm_art_kind( tmp_n );
			item->dat.armor.randm_art[i].kind = art;

			if( !load_game_data_c( fp, &tmp_c ) )
				return FALSE;
			item->dat.armor.randm_art[i].mjr = tmp_c;

			if( !load_game_data_c( fp, &tmp_c ) )
				return FALSE;
			item->dat.armor.randm_art[i].mnr = tmp_c;

			if( !load_game_data_skip_c( fp, '}', TRUE ) )
				return FALSE;
			if( !load_game_data_skip_c( fp, ',', TRUE ) )
				return FALSE;
		}
		item->dat.armor.randm_art[i].kind
				= ARMOR_RANDM_ART_KIND_NULL;
		item->dat.armor.randm_art[i].mjr = ' ';
		item->dat.armor.randm_art[i].mnr = ' ';

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	item->tab.armor = get_armor_tab( item->dat.armor.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの薬のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_potion_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.potion.kind = trans_idx_to_potion_kind( tmp_n );

	item->tab.potion = get_potion_tab( item->dat.potion.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの巻物のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_scroll_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.scroll.kind = trans_idx_to_scroll_kind( tmp_n );

	item->tab.scroll = get_scroll_tab( item->dat.scroll.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの杖のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_stick_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.stick.kind = trans_idx_to_stick_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.stick.spell_kind = trans_idx_to_spell_kind( tmp_n );

	if( !load_game_data_n( fp, &(item->dat.stick.n) ) )
		return FALSE;

	item->tab.stick = get_stick_tab(
			item->dat.stick.kind,
			item->dat.stick.spell_kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データのアクセサリのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_acce_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.acce.kind = trans_idx_to_acce_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.acce.ring_kind = trans_idx_to_ring_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.acce.amulet_kind = trans_idx_to_amulet_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.acce.necklace_kind = trans_idx_to_necklace_kind( tmp_n );

	item->tab.acce = get_acce_tab(
			item->dat.acce.ring_kind,
			item->dat.acce.amulet_kind,
			item->dat.acce.necklace_kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの楽器のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_inst_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.inst.kind = trans_idx_to_inst_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.inst.flg_limit = (bool_t)tmp_n;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.inst.spell_kind = trans_idx_to_spell_kind( tmp_n );

	item->tab.inst = get_inst_tab( item->dat.inst.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの詩集のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_anthology_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.anthology.kind = trans_idx_to_anthology_kind( tmp_n );

	item->tab.anthology = get_anthology_tab( item->dat.anthology.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの明かりのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_light_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.light.kind = trans_idx_to_light_kind( tmp_n );

	if( !load_game_data_n( fp, &(item->dat.light.turn) ) )
		return FALSE;

	if( chk_ver_new_match( ver, 1, 2, 9 ) ){
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		item->dat.light.wish_level
				= trans_idx_to_wish_level( tmp_n );

		if( !load_game_data_n( fp, &(item->dat.light.wish_n) ) )
			return FALSE;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		item->dat.light.flg_used = (bool_t)tmp_n;
	}

	item->tab.light = get_light_tab(
			item->dat.light.kind,
			item->dat.light.wish_level );

	return TRUE;
}

/***************************************************************
* ゲーム・データの釘のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_spike_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	item->tab.wpn = NULL;

	return TRUE;
}

/***************************************************************
* ゲーム・データの食料のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_food_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.food.kind = trans_idx_to_food_kind( tmp_n );

	item->tab.food = get_food_tab( item->dat.food.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの宝箱のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_chest_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	item_t	*contents;
	trap_t	trap, *p_trap;
	long	tmp_n;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	item = make_item_chest_alloc( item, 0, 0, FALSE );
	if( item == NULL )
		return FALSE;

	/* chest->contents */

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		contents = alloc_item();
		if( contents == NULL )
			return FALSE;

		if( !load_game_data_skip_c( fp, '{', TRUE ) )
			return FALSE;

		load_game_data_item_ver_1(
				fp, ver, flg_txt, mbr, contents );

		ins_ls_item( item->dat.chest.contents, contents );

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	/* chest->trap */

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;

	trap.next = NULL;
	trap.prev = NULL;

	if( !load_game_data_skip_c( fp, '}', FALSE ) ){
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		trap.kind = trans_idx_to_trap_kind( tmp_n );

		if( !load_game_data_n( fp, &(trap.x) ) )
			return FALSE;
		if( !load_game_data_n( fp, &(trap.y) ) )
			return FALSE;

		if( !load_game_data_n( fp, &(trap.lev) ) )
			return FALSE;

		if( !load_game_data_n( fp, &(trap.difficulty) ) )
			return FALSE;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		trap.flg_chked = (bool_t)tmp_n;

		trap.tab = get_trap_tab( trap.kind );

		/* 罠のメモリーを割り当てる */

		p_trap = alloc_trap();
		if( p_trap == NULL )
			return FALSE;

		*p_trap = trap;
		item->dat.chest.trap = p_trap;

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	/* chest->ref */

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.chest.contents->dat.chest.ref = tmp_n;

	/* chest->tab */

	item->tab.wpn = NULL;

	return TRUE;
}

/***************************************************************
* ゲーム・データの煙草のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_tobacco_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.tobacco.kind = trans_idx_to_tobacco_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.tobacco.brand = trans_idx_to_tobacco_brand( tmp_n );

	if( !load_game_data_n( fp, &(item->dat.tobacco.turn) ) )
		return FALSE;

	item->tab.tobacco = get_tobacco_tab(
			item->dat.tobacco.kind,
			item->dat.tobacco.brand );

	return TRUE;
}

/***************************************************************
* ゲーム・データのパイプのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_pipe_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.pipe.kind = trans_idx_to_pipe_kind( tmp_n );

	if( !load_game_data_n( fp, &(item->dat.pipe.turn) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(item->dat.pipe.consume_turn) ) )
		return FALSE;

	item->tab.pipe = get_pipe_tab( item->dat.pipe.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの吸い殻入れのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_disposal_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &(item->dat.disposal.n) ) )
		return FALSE;

	if( !load_game_data_n( fp, &(item->dat.disposal.max_n) ) )
		return FALSE;

	item->tab.wpn = NULL;

	return TRUE;
}

/***************************************************************
* ゲーム・データのレア・グッズのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_rare_goods_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.rare_goods.kind = trans_idx_to_rare_goods_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.rare_goods.mnstr_kind = trans_idx_to_mnstr_kind( tmp_n );

	item->tab.rare_goods = get_rare_goods_tab(
			item->dat.rare_goods.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データの骨のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_bone_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	mnstr_kind_t	kind;
	long	lev;
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	kind = trans_idx_to_mnstr_kind( tmp_n );

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	lev = tmp_n;

	item->dat.bone.mnstr_tab = get_mnstr_tab( kind, lev );
	item->dat.bone.dun_lev = lev;

	return TRUE;
}

/***************************************************************
* ゲーム・データの金貨のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_coin_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	item->dat.coin.kind = trans_idx_to_coin_kind( tmp_n );

	item->tab.coin = get_coin_tab( item->dat.coin.kind );

	return TRUE;
}

/***************************************************************
* ゲーム・データのゴミのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_item_junk_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データのキー・アイテムのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_key_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	long	idx, flg;
	star_drop_kind_t	kind;
	bool_t	flg_have;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( !load_game_data_skip_c( fp, '{', FALSE ) )
			break;

		if( !load_game_data_n( fp, &idx ) )
			return FALSE;
		if( !load_game_data_n( fp, &flg ) )
			return FALSE;

		kind = trans_idx_to_key_item_kind( idx );
		flg_have = !!flg;
		set_key_item( kind, flg_have );

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの自動マーク・リストのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_auto_mark_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
)
{
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( ls_mbr_n < 0 )
		return FALSE;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return FALSE;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( !load_game_data_skip_c( fp, '{', FALSE ) )
			break;

		if( !load_game_data_auto_mark_ver_1(
				fp, ver, flg_txt, ls_mbr_n, i ) ){
			return FALSE;
		}

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの自動マークのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* long auto_mark_n : 自動マークのスロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_auto_mark_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n, long auto_mark_n
)
{
	mbr_t	**ls_mbr = get_ls_mbr();
	auto_mark_t	*am;
	position_kind_t	position_kind;
	long	tmp_n;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( ls_mbr == NULL )
		return FALSE;
	if( ls_mbr_n < 0 )
		return FALSE;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return FALSE;

	/* 誤作動の防止 */
	if( ls_mbr[ls_mbr_n] != NULL )
		ls_mbr[ls_mbr_n]->flg_chr &= ~FLG_CHR_AUTO_MARK_CONT;

	/* no. */
	if( chk_ver_new_match( ver, 1, 2, 12 ) ){
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		auto_mark_n = tmp_n;
	}

	tmp_n = auto_mark_n / AUTO_MARK_POSITION_MUL;
	position_kind = trans_idx_to_position_kind( tmp_n );
	auto_mark_n %= AUTO_MARK_POSITION_MUL;

	if( auto_mark_n < 0 )
		return FALSE;
	if( auto_mark_n > AUTO_MARK_MAX_N - 1 )
		auto_mark_n = AUTO_MARK_MAX_N - 1;

	am = get_auto_mark( ls_mbr_n, auto_mark_n, position_kind );
	if( am == NULL )
		return FALSE;

	/* trgt */
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	am->trgt = trans_idx_to_am_trgt( tmp_n );

	/* dist */
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	am->dist = trans_idx_to_am_dist( tmp_n );

	/* act */
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	am->act = trans_idx_to_am_act( tmp_n );

	/* cond */
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	am->cond = trans_idx_to_am_cond( tmp_n );

	/* macro */
	if( chk_ver_old( ver, 1, 1, 1 ) ){
		am->macro[0] = '\0';
	} else {
		if( !load_game_data_s( fp, am->macro,
				MACRO_MAX_LEN ) ){
			return FALSE;
		}
	}

	/* flg */
	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	am->flg = tmp_n;

	/* dflt */
	if( chk_ver_old( ver, 1, 2, 33 ) ){
		am->dflt = DFLT_AUTO_MARK_NULL;
	} else {
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		am->dflt = trans_idx_to_am_dflt( tmp_n );
	}

	set_flg_ena_auto_mark( auto_mark_n, TRUE );

	return TRUE;
}

/***************************************************************
* ゲーム・データの自動マークのアイテム・リストのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_auto_mark_appoint_item_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
)
{
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( ls_mbr_n < 0 )
		return FALSE;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return FALSE;

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_auto_mark_appoint_item_ver_1(
				fp, ver, flg_txt, ls_mbr_n, i ) ){
			return FALSE;
		}
	}

	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの自動マークのアイテムのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* long auto_mark_n : 自動マークのスロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_auto_mark_appoint_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n, long auto_mark_n
)
{
	auto_mark_appoint_item_t	*ls;
	long	tmp_n;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( ls_mbr_n < 0 )
		return FALSE;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return FALSE;

	/* no. */

	if( chk_ver_new_match( ver, 1, 2, 12 ) ){
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		auto_mark_n = tmp_n;
	}

	if( auto_mark_n < 0 )
		return FALSE;
	if( auto_mark_n > AUTO_MARK_MAX_N - 1 )
		auto_mark_n = AUTO_MARK_MAX_N - 1;

	/**/

	if( !load_game_data_skip_c( fp, '{', FALSE ) )
		return FALSE;

	for( i = 0; i < AUTO_MARK_APPOINT_ITEM_MAX_N; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		ls = get_ls_auto_mark_appoint_item( ls_mbr_n, auto_mark_n );
		if( ls == NULL )
			continue;

		if( !load_game_data_c( fp, &(ls[i].mjr) ) )
			return FALSE;

		if( !load_game_data_c( fp, &(ls[i].mnr) ) )
			return FALSE;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		ls[i].flg_ena = (bool_t)tmp_n;
	}

	if( i >= AUTO_MARK_APPOINT_ITEM_MAX_N )
		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データのサーチ・モード・フラグのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_flg_srch_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	bool_t	*ls;
	long	tmp_n;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	ls = get_ls_flg_srch();
	if( ls == NULL )
		return FALSE;

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		ls[i] = (bool_t)tmp_n;
	}

	if( i >= LS_MBR_MAX_N )
		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの呪文リストのパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_spell_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
)
{
	mbr_t	**ls_mbr = get_ls_mbr();
	cast_tab_t	*tab;
	spell_kind_t	kind;
	long	tmp_n;
	long	j, adjust;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( ls_mbr_n < 0 )
		return FALSE;
	if( ls_mbr_n >= LS_MBR_MAX_N )
		return FALSE;

	if( chk_ver_old( ver, 1, 0, 2 ) )
		adjust = 1;
	else
		adjust = 0;

	for( j = 0 + adjust; j < SPELL_KIND_MAX_N; j++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;

		kind = trans_idx_to_spell_kind( j );
		if( kind >= SPELL_KIND_MAX_N )
			continue;

		tab = get_cast_tab( ls_mbr[ls_mbr_n], kind );
		if( tab == NULL )
			continue;

		tab->flg_cast = (bool_t)tmp_n;
	}
	if( j >= SPELL_KIND_MAX_N )
		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
	for( ; j < SPELL_KIND_MAX_N; j++ ){
		kind = trans_idx_to_spell_kind( j );

		tab = get_cast_tab( ls_mbr[ls_mbr_n], kind );
		if( tab == NULL )
			continue;

		tab->flg_cast = FALSE;
	}
	tab = get_cast_tab( ls_mbr[ls_mbr_n], SPELL_KIND_NULL );
	if( tab != NULL )
		tab->flg_cast = FALSE;

	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データのメンバーの隊列のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_mbr_formation_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	party_t	*pty = get_party();
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	for( i = 0; i < MBR_MAX_N; i++ )
		not_join_mbr( pty->mbr[i]->ls_mbr_n, i );

	for( i = 0; i < MBR_MAX_N; i++ ){
		long	ls_mbr_n;

		if( !load_game_data_n( fp, &ls_mbr_n ) )
			return FALSE;

		if( ls_mbr_n <= -1 )
			continue;
		if( ls_mbr_n >= LS_MBR_MAX_N )
			continue;

		join_mbr( ls_mbr_n, i );
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データのペットの隊列のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_pet_formation_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	pet_t	**pty_pet = get_party_pet();
	pet_t	**ls_pet = get_ls_pet();
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	for( i = 0; i < PET_MAX_N; i++ ){
		if( pty_pet[i] == NULL )
			continue;

		not_join_pet( pty_pet[i] );
	}

	for( i = 0; i < PET_MAX_N; i++ ){
		long	ls_pet_n;
		pet_t	*p;

		if( !load_game_data_n( fp, &ls_pet_n ) )
			return FALSE;

		if( ls_pet_n <= -1 )
			continue;
		if( ls_pet_n >= LS_PET_MAX_N )
			continue;

		p = ls_pet[ls_pet_n];
		if( p == NULL )
			continue;

		clr_map_chr( p );
		draw_pet( p );

		join_pet( p );
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの依頼のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_request_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	request_t	*req, *p;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	req = get_request_ls();
	if( req == NULL )
		return FALSE;

	for( i = 0; i < REQUEST_MAX_N; i++ )
		req[i].kind = REQUEST_KIND_NULL;

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		long	tmp_n;

		if( !load_game_data_skip_c( fp, '{', FALSE ) )
			break;

		if( chk_ver_old( ver, 1, 1, 5 ) ){
			p = &(req[i]);
		} else {
			if( !load_game_data_n( fp, &tmp_n ) )
				return FALSE;
			p = &(req[tmp_n]);
		}

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->kind = trans_idx_to_request_kind( tmp_n );
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->dun_min_lev = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->dun_max_lev = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->dun_true_lev = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->prize = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->exp = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->limit = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->flg_contract = (bool_t)tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->flg_contract_mbr = (bool_t)tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_contract_name = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->contract_sex = trans_idx_to_sex_kind( tmp_n );
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->flg_finish = (bool_t)tmp_n;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->rare_goods_kind
				= trans_idx_to_rare_goods_kind( tmp_n );

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->flg_mnstr_is_npc = (bool_t)tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->mnstr_kind = trans_idx_to_mnstr_kind( tmp_n );
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->mnstr_n = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->mnstr_exterminate_n = tmp_n;

		if( !load_game_data_s( fp, p->heading,
				MENU_MSG_MAX_BYTE ) )
			return FALSE;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_fmt = tmp_n;
		if( !load_game_data_s( fp, p->msg,
				REQUEST_MSG_MAX_BYTE ) )
			return FALSE;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_client_name = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_mnstr_name = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_rescue_trgt_name = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_client_family_name = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_client_mate_name = tmp_n;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->client_sex = trans_idx_to_sex_kind( tmp_n );
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->mnstr_sex = trans_idx_to_sex_kind( tmp_n );
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->rescue_trgt_sex = trans_idx_to_sex_kind( tmp_n );
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->client_family_sex = trans_idx_to_sex_kind( tmp_n );
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->client_mate_sex = trans_idx_to_sex_kind( tmp_n );

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->rescue_trgt_kind = trans_idx_to_mnstr_kind( tmp_n );

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_when_1 = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_when_2 = tmp_n;
		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->idx_weapon = tmp_n;

		if( !load_game_data_skip_c( fp, '}', TRUE ) )
			return FALSE;
		if( !load_game_data_skip_c( fp, ',', TRUE ) )
			return FALSE;
	}

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データのメンバーの統計のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_playing_report_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
)
{
	playing_report_t	*p;

	p = get_playing_report_mbr( ls_mbr_n );
	return load_game_data_playing_report_ver_1( fp, ver, flg_txt, p );
}

/***************************************************************
* ゲーム・データのパーティの統計のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_playing_report_party_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
)
{
	playing_report_t	*p;

	p = get_playing_report_party();
	return load_game_data_playing_report_ver_1( fp, ver, flg_txt, p );
}

/***************************************************************
* ゲーム・データの統計のパース(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_playing_report_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	playing_report_t *p
)
{
	long	tmp_n;
	long	i, max_idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( p == NULL )
		return FALSE;

	/* 初期化 */

	p->paying_gold = 0;
	for( i = 0; i < STAY_INN_KIND_MAX_N; i++ )
		p->staying_inn[i] = 0;
	for( i = 0; i < EQUIP_KIND_MAX_N; i++ )
		p->wearing_equip[i] = 0;
	for( i = 0; i < RESI_KIND_MAX_N; i++ ){
		p->making_dam[i] = 0;
		p->made_dam[i] = 0;
	}
	for( i = 0; i < SPELL_KIND_MAX_N; i++ ){
		p->using_spell[i] = 0;
		p->used_spell[i] = 0;
	}

	/* paying_gold */

	if( !load_game_data_n( fp, &tmp_n ) )
		return FALSE;
	p->paying_gold = tmp_n;

	/* staying_inn */

	max_idx = get_stay_inn_kind_trans_tab_max_n();
	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < max_idx + 1; i++ ){
		stay_inn_kind_t	kind;

		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		kind = trans_idx_to_stay_inn_kind( i );
		p->staying_inn[kind] = tmp_n;
	}
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	/* wearing_equip */

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < EQUIP_KIND_MAX_N + 1; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->wearing_equip[i] = tmp_n;
	}
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	/* making_dam */

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < RESI_KIND_MAX_N + 1; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->making_dam[i] = tmp_n;
	}
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	/* made_dam */

	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < RESI_KIND_MAX_N + 1; i++ ){
		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		p->made_dam[i] = tmp_n;
	}
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	/* using_spell */

	max_idx = get_spell_kind_trans_tab_max_n();
	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < max_idx + 1; i++ ){
		spell_kind_t	kind;

		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		kind = trans_idx_to_spell_kind( i );
		p->using_spell[kind] = tmp_n;
	}
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	/* used_spell */

	max_idx = get_spell_kind_trans_tab_max_n();
	if( !load_game_data_skip_c( fp, '{', TRUE ) )
		return FALSE;
	for( i = 0; i < max_idx + 1; i++ ){
		spell_kind_t	kind;

		if( load_game_data_skip_c( fp, '}', FALSE ) )
			break;

		if( !load_game_data_n( fp, &tmp_n ) )
			return FALSE;
		kind = trans_idx_to_spell_kind( i );
		p->used_spell[kind] = tmp_n;
	}
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	/**/

	if( !load_game_data_skip_c( fp, '}', TRUE ) )
		return FALSE;
	if( !load_game_data_skip_c( fp, ',', TRUE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ファイルの数値のパース
* FILE *fp : ファイル
* long *n : 数値の返す先
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_n( FILE *fp, long *n )
{
	long	sign_n;
	rc_token_t	t;
	rc_union_t	u;

	if( fp == NULL )
		return FALSE;
	if( n == NULL )
		return FALSE;

	sign_n = +1;
	do {
		do {
			t = rc_lex( fp, &u, TRUE );
			if( t != '\n' )
				break;
		} while( 1 );

		if( t == RC_TOKEN_ADD_OP ){
			if( u.c == '-' )
				sign_n = -sign_n;
			continue;
		}

		break;
	} while( 1 );

	if( t != RC_TOKEN_NUM ){
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_NUM );
		return FALSE;
	}

	*n = sign_n * u.n;

	t = rc_lex( fp, &u, TRUE );
	if( t != ',' ){
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_COMMA );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ファイルの文字列のパース
* FILE *fp : ファイル
* char *s : 文字列の返す先
* long len : 文字列の最大長
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_s( FILE *fp, char *s, long len )
{
	rc_token_t	t;
	rc_union_t	u;

	if( fp == NULL )
		return FALSE;
	if( s == NULL )
		return FALSE;

	do {
		t = rc_lex( fp, &u, TRUE );
		if( t != '\n' )
			break;
	} while( 1 );

	if( t != RC_TOKEN_STR ){
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_STR );
		return FALSE;
	}

	str_nz_cpy( s, u.str, len );

	t = rc_lex( fp, &u, TRUE );
	if( t != ',' ){
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_COMMA );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ファイルの文字のパース
* FILE *fp : ファイル
* char *c : 文字の返す先
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_c( FILE *fp, char *c )
{
	rc_token_t	t;
	rc_union_t	u;

	if( fp == NULL )
		return FALSE;
	if( c == NULL )
		return FALSE;

	do {
		t = rc_lex( fp, &u, TRUE );
		if( t != '\n' )
			break;
	} while( 1 );

	if( t != RC_TOKEN_CHAR ){
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_CHAR );
		return FALSE;
	}

	*c = (char)(u.c);

	t = rc_lex( fp, &u, TRUE );
	if( t != ',' ){
		print_lex_err( MSG_S, MSG_ERR_RC_PARSE_COMMA );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ファイルの文字を読み飛ばす(違う文字に当ったらエラー)
* FILE *fp : ファイル
* rc_token_t c : 文字
* bool_t flg_draw : エラーを表示するか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_skip_c( FILE *fp, char c, bool_t flg_draw )
{
	return load_game_data_skip_token( fp, (rc_token_t)c, flg_draw );
}

/***************************************************************
* ファイルのトークンを読み飛ばす(違うトークンに当ったらエラー)
* FILE *fp : ファイル
* rc_token_t c : 文字
* bool_t flg_draw : エラーを表示するか?
* return : エラーが無かったか?
***************************************************************/

bool_t	load_game_data_skip_token( FILE *fp, rc_token_t c, bool_t flg_draw )
{
	rc_token_t	t;
	rc_union_t	u;

	if( fp == NULL )
		return FALSE;

	do {
		t = rc_lex( fp, &u, TRUE );
		if( (t != '\n') && (t != '\r') )
			break;
	} while( 1 );

	if( t != c ){
		if( flg_draw ){
			print_lex_err( MSG_ERR_RC_PARSE_SKIP_CHAR, c );
		}

		rc_unlex( fp, &u, t );

		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データのセーブ
* bool_t flg_txt : テキスト・モードか?
* long n : データ・スロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data( bool_t flg_txt, long n )
{
	bool_t	flg_success = TRUE;

	reset_static();

	g_randm_seed_save = get_randm_seed();

	if( (n != SAVE_N_AUTO) && (n != SAVE_N_BUG_REPO) )
		g_game_data_save_n++;

	if( flg_txt ){
		/* デバッグ用のテキスト・セーブ */
		flg_success = save_game_data_sub( flg_txt, n );
	} else {
		/* デバッグ用のテキスト・セーブ */
		if( !save_game_data_sub( TRUE, n ) )
			flg_success = FALSE;

		/* 通常のバイナリー・セーブ */
		if( !save_game_data_sub( FALSE, n ) )
			flg_success = FALSE;
	}

	remove_replay_file( n );
	bgn_reg_replay( n );

	return flg_success;
}

/***************************************************************
* ゲーム・データのセーブ
* bool_t flg_txt : テキスト・モードか?
* long n : データ・スロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_sub( bool_t flg_txt, long n )
{
	ver_t	ver;

	ver.mjr = GAME_DATA_VER_MJR;
	ver.mnr = GAME_DATA_VER_MNR;
	ver.pat = GAME_DATA_VER_PAT;

	switch( ver.mjr ){
	case 1:
		return save_game_data_ver_1( &ver, flg_txt, n );
		break;
	default:
		return FALSE;
		break;
	}

	return FALSE;
}

/***************************************************************
* ゲーム・データのセーブ(バージョン 1)
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long n : データ・スロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_ver_1( const ver_t *ver, bool_t flg_txt, long n )
{
	FILE	*fp;
	time_t	save_time_buf;
	struct tm	*save_time;

	if( ver == NULL )
		return FALSE;

	fp = open_game_data( 'w', n, flg_txt );
	if( fp == NULL )
		return FALSE;

	/* header */

	fprintf( fp, "%s%ld.%ld.%ld\n",
			STR_GAME_DATA_HEAD,
			ver->mjr, ver->mnr, ver->pat );

	time( &save_time_buf );
	save_time = localtime( &save_time_buf );
	if( save_time == NULL )
		return FALSE;
	fprintf( fp, "%04ld: %04d/%02d/%02d  %02d:%02d:%02d\n",
			g_game_data_save_n,
			save_time->tm_year + 1900,
			save_time->tm_mon + 1,
			save_time->tm_mday,
			save_time->tm_hour,
			save_time->tm_min,
			save_time->tm_sec );

	reset_save_crypt( fp, flg_txt );
	reset_save_crypt_tab();

	/* contents */

	if( !save_game_data_contents( fp, ver, flg_txt ) ){
		fclose( fp );
		return FALSE;
	}

	/* footer */

	save_crypt_str( fp, "\n" );
	save_crypt_tab( fp, "// end\n" );

	/* end */

	if( fclose( fp ) == EOF )
		return FALSE;

	/* config */

	if( chk_ver_new_match( ver, 1, 1, 0 ) )
		if( !save_game_data_cnf_ver_1( ver, n ) )
			return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの内容のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_contents(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	bool_t	flg_err = FALSE;

	/* misc */

	flg_err |= !save_game_data_randm_seed_ver_1( fp, ver, flg_txt );
	flg_err |= !save_game_data_dun_lev_ver_1( fp, ver, flg_txt );
	flg_err |= !save_game_data_turn_ver_1( fp, ver, flg_txt );

	/* member */

	flg_err |= !save_game_data_square_ver_1( fp, ver, flg_txt );
	flg_err |= !save_game_data_class_ver_1( fp, ver, flg_txt );
	flg_err |= !save_game_data_mbr_ver_1( fp, ver, flg_txt );

	/* potion */

	flg_err |= !save_game_data_potion_color_ver_1( fp, ver, flg_txt );
	flg_err |= !save_game_data_potion_identified_ver_1(
			fp, ver, flg_txt );

	/* scroll */

	flg_err |= !save_game_data_scroll_ttl_syllable_ver_1(
			fp, ver, flg_txt );
	flg_err |= !save_game_data_scroll_identified_ver_1(
			fp, ver, flg_txt );

	/* stick */

	flg_err |= !save_game_data_stick_material_ver_1(
			fp, ver, flg_txt, STICK_KIND_WAND );
	flg_err |= !save_game_data_stick_material_ver_1(
			fp, ver, flg_txt, STICK_KIND_ROD );
	flg_err |= !save_game_data_stick_material_ver_1(
			fp, ver, flg_txt, STICK_KIND_STAFF );

	/* acce */

	flg_err |= !save_game_data_acce_material_ver_1(
			fp, ver, flg_txt, ACCE_KIND_RING );
	flg_err |= !save_game_data_acce_material_ver_1(
			fp, ver, flg_txt, ACCE_KIND_AMULET );
	flg_err |= !save_game_data_acce_material_ver_1(
			fp, ver, flg_txt, ACCE_KIND_NECKLACE );

	/* members item */

	flg_err |= !save_game_data_item_all_mbr_ver_1( fp, ver, flg_txt );

	/* key item */

	flg_err |= !save_game_data_key_item_ver_1( fp, ver, flg_txt );

	/* misc */

	flg_err |= !save_game_data_auto_mark_ls_ver_1( fp, ver, flg_txt );
	flg_err |= !save_game_data_flg_srch_ver_1( fp, ver, flg_txt );
	flg_err |= !save_game_data_spell_ls_ver_1( fp, ver, flg_txt );
	flg_err |= !save_game_data_mbr_formation_ver_1( fp, ver, flg_txt );
	flg_err |= !save_game_data_pet_formation_ver_1( fp, ver, flg_txt );

	/* request */

	flg_err |= !save_game_data_request_ver_1( fp, ver, flg_txt );

	/* playing report */

	flg_err |= !save_game_data_playing_report_mbr_ver_1(
			fp, ver, flg_txt );
	flg_err |= !save_game_data_playing_report_party_ver_1(
			fp, ver, flg_txt );

	/**/

	if( flg_err )
		return FALSE;
	else
		return TRUE;
}

/***************************************************************
* ゲーム・データの乱数の種のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_randm_seed_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// random seed\n" );
	save_crypt_tab( fp, "randm_seed = %ld\n", g_randm_seed_save );

	return TRUE;
}

/***************************************************************
* ゲーム・データの迷宮の階層のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_dun_lev_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// dungeon level\n" );
	save_crypt_tab( fp, "dun_lev = %ld\n", get_dun_lev() );

	return TRUE;
}

/***************************************************************
* ゲーム・データのターン数のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_turn_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// day\n" );
	save_crypt_tab( fp, "day = %ld\n", get_game_day() );
	save_crypt_tab( fp, "// turn\n" );
	save_crypt_tab( fp, "turn = %ld\n", get_turn() );

	return TRUE;
}

/***************************************************************
* ゲーム・データのアンカーのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_square_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	square_t	*sq;
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	sq = get_square_mbr();
	if( sq == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// square\n" );

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "square = " );
	set_save_crypt_tab( fp, +1 );

	save_crypt_tab( fp, "// x\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(sq->x) );
	save_crypt_tab( fp, "// y\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(sq->y) );

	save_crypt_tab( fp, "// dir\n" );
	idx = trans_square_dir_to_idx( sq->dir );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データのクラスのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_class_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	class_t	*p;
	abl_kind_t	abl_n;
	long	idx;
	long	i, j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// class\n" );

	p = get_class_tab();
	if( p == NULL )
		return FALSE;

	for( i = 0; i < CLASS_MAX_N; i++ ){
		if( p[i].name[0] == '\0' )
			break;

		save_crypt_tab( fp, "\n" );
		save_crypt_tab( fp, "class %ld = ", i );

		set_save_crypt_tab( fp, +1 );

		/* n_name */

		save_crypt_tab( fp, "// name\n" );
		save_crypt_tab( fp, "\"%s\",\n",
				cv_esc_quote_str( p[i].name ) );

		save_crypt_tab( fp, "// dflt\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(p[i].dflt) );

		save_crypt_tab( fp, "// abl_rate\n" );
		set_save_crypt_tab( fp, +1 );
		for( j = 0; j < ABL_KIND_MAX_N; j++ ){
			abl_n = trans_idx_to_abl_kind( j );
			save_crypt_tab( fp, "// %s\n",
					get_abl_name( abl_n ) );
			save_crypt_tab( fp, "%ld,\n",
					(long)(p[i].abl_rate[abl_n]) );
		}
		set_save_crypt_tab( fp, -1 );

		save_crypt_tab( fp, "// skill\n" );
		set_save_crypt_tab( fp, +1 );
		for( j = 0; j < SKILL_MAX_N; j++ ){
			abl_n = (abl_kind_t)(p[i].skill[j] + ABL_KIND_MAX_N);
			idx = trans_abl_kind_to_idx( abl_n );

			save_crypt_tab( fp, "// %s\n",
					get_abl_name( abl_n ) );
			save_crypt_tab( fp, "%ld,\n", (long)idx );
		}
		set_save_crypt_tab( fp, -1 );

		set_save_crypt_tab( fp, -1 );
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データのメンバーとペットのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	mbr_t	**ls_mbr;
	pet_t	**ls_pet;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	/* メンバー */

	ls_mbr = get_ls_mbr();
	if( ls_mbr == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// mbr\n" );

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		save_crypt_tab( fp, "\n" );
		save_crypt_tab( fp, "member %ld = ", i );
		save_game_data_chr_ver_1( fp, ver, flg_txt, ls_mbr[i] );
	}

	/* ペット */

	ls_pet = get_ls_pet();
	if( ls_pet == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// pet\n" );

	for( i = 0; i < LS_PET_MAX_N; i++ ){
		if( ls_pet[i] == NULL )
			continue;
		if( chk_flg( ls_pet[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		save_crypt_tab( fp, "\n" );
		save_crypt_tab( fp, "pet %ld = ", i );
		save_game_data_chr_ver_1( fp, ver, flg_txt, ls_pet[i] );
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データのキャラクタのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* chr_t *chr : キャラクタ
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_chr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
)
{
	fx_t	*fx, *end;
	abl_kind_t	abl_n;
	long	idx;
	long	max_idx;
	long	i, j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( chr == NULL )
		return FALSE;
	if( chk_flg( chr->stat, FLG_STAT_NOT_EXIST ) )
		return FALSE;

	set_save_crypt_tab( fp, +1 );

	idx = trans_chr_kind_to_idx( chr->kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", idx );

	save_crypt_tab( fp, "// name\n" );
	save_crypt_tab( fp, "\"%s\",\n", cv_esc_quote_str( chr->name ) );

	save_crypt_tab( fp, "// id1, id2\n" );
	save_crypt_tab( fp, "%ld, %ld,\n", chr->id1, chr->id2 );

	save_crypt_tab( fp, "// mbr_n, ls_mbr_n\n" );
	save_crypt_tab( fp, "%ld, %ld,\n",
			chr->mbr_n, chr->ls_mbr_n );

	idx = trans_position_kind_to_idx( chr->position_kind );
	save_crypt_tab( fp, "%ld,\n", idx );

	save_crypt_tab( fp, "// face\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "\'%s\',\n",
			cv_esc_quote_c( chr->face.mjr ) );
	save_crypt_tab( fp, "\'%s\',\n",
			cv_esc_quote_c( chr->face.mnr ) );
	save_crypt_tab( fp, "\'%s\',\n",
			cv_esc_quote_c( chr->face.mjr_org ) );
	save_crypt_tab( fp, "\'%s\',\n",
			cv_esc_quote_c( chr->face.mnr_org ) );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// race\n" );
	set_save_crypt_tab( fp, +1 );
	idx = trans_main_race_kind_to_idx( chr->race.main );
	save_crypt_tab( fp, "%ld,\n", idx );
	idx = trans_sub_race_kind_to_idx( chr->race.sub );
	save_crypt_tab( fp, "%ld,\n", idx );
	save_crypt_tab( fp, "\"%s\",\n",
			cv_esc_quote_str( chr->race.name ) );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// sex\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "%ld, %ld,\n",
			trans_sex_kind_to_idx( chr->sex.cur ),
			trans_sex_kind_to_idx( chr->sex.org ) );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// x, y\n" );
	save_crypt_tab( fp, "%ld, %ld,\n", chr->x, chr->y );

	save_crypt_tab( fp, "// pre_x, pre_y\n" );
	save_crypt_tab( fp, "%ld, %ld,\n",
			chr->pre_x, chr->pre_y );

	save_crypt_tab( fp, "// dx, dy\n" );
	save_crypt_tab( fp, "%ld, %ld,\n", chr->dx, chr->dy );

	save_crypt_tab( fp, "// move\n" );
	set_save_crypt_tab( fp, +1 );

	save_crypt_tab( fp, "// speed\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "%ld, %ld,\n",
			chr->move.speed.rate,
			chr->move.speed.rate_org );
	save_crypt_tab( fp, "%ld,\n", chr->move.speed.n );
	set_save_crypt_tab( fp, -1 );

	idx = trans_move_kind_to_idx( chr->move.force_kind );
	save_crypt_tab( fp, "// force_kind\n" );
	save_crypt_tab( fp, "%ld,\n", idx );

	save_crypt_tab( fp, "// ls\n" );
	set_save_crypt_tab( fp, +1 );

	max_idx = get_move_ls_trans_tab_max_n();
	for( i = 0; i < max_idx; i++ ){
		move_ls_kind_t	k;

		k = trans_idx_to_move_ls_kind( i );

		set_save_crypt_tab( fp, +1 );
		for( j = 0; j < MOVE_LS_MAX_N; j++ ){
			idx = trans_move_kind_to_idx(
					chr->move.ls[k][j].kind );

			set_save_crypt_tab( fp, +1 );
			save_crypt_tab( fp, "%ld,\n", idx );
			save_crypt_tab( fp, "%ld,\n",
					chr->move.ls[k][j].ratio );
			set_save_crypt_tab( fp, -1 );
		}
		set_save_crypt_tab( fp, -1 );
	}
	set_save_crypt_tab( fp, -1 );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// gold\n" );
	save_crypt_tab( fp, "%ld,\n", chr->gold );

	save_crypt_tab( fp, "// dun_max_lev_floor, "
			"dun_max_lev_base\n" );
	save_crypt_tab( fp, "%ld, %ld,\n",
			chr->dun_max_lev_floor,
			chr->dun_max_lev_base );

	/* trgt_t	trgt; */
	/* act_t	act, pre_act; */

	save_crypt_tab( fp, "// flg_chr\n" );
	save_crypt_tab( fp, "0x%08lx,\n", chr->flg_chr );

	save_crypt_tab( fp, "// flg_map\n" );
	save_crypt_tab( fp, "0x%08lx,\n", chr->flg_map );

	idx = trans_attitude_kind_to_idx( chr->attitude );
	save_crypt_tab( fp, "// attitude\n" );
	save_crypt_tab( fp, "%ld,\n", idx );

	save_crypt_tab( fp, "// owner_ls_mbr_n\n" );
	if( (chr->owner != NULL) && is_mbr( chr->owner ) ){
		save_crypt_tab( fp, "%ld,\n", chr->ls_mbr_n );
	} else {
		save_crypt_tab( fp, "-1,\n" );
	}

	save_crypt_tab( fp, "// stat\n" );
	save_crypt_tab( fp, "%ld,\n", chr->stat );

	save_crypt_tab( fp, "// abl\n" );
	set_save_crypt_tab( fp, +1 );
	max_idx = get_abl_kind_trans_tab_max_n();
	for( i = 0; i < max_idx; i++ ){
		abl_n = trans_idx_to_abl_kind( i );
		save_crypt_tab( fp, "// %s\n",
				get_abl_name( abl_n ) );
		set_save_crypt_tab( fp, +1 );

		save_crypt_tab( fp, "// exp_n, exp_max\n" );
		save_crypt_tab( fp, "%ld, %ld,\n",
				chr->abl.exp[abl_n].n,
				chr->abl.exp[abl_n].max );

		save_crypt_tab( fp, "// lev_n, lev_max\n" );
		save_crypt_tab( fp, "%ld, %ld, %ld,\n",
				chr->abl.lev[abl_n].n,
				chr->abl.lev[abl_n].max,
				chr->abl.lev[abl_n].add );
		set_save_crypt_tab( fp, -1 );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// hp\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "// n, max\n" );
	save_crypt_tab( fp, "%ld, %ld,\n",
			chr->abl.hp.n,
			chr->abl.hp.max );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// mp\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "// n, max\n" );
	save_crypt_tab( fp, "%ld, %ld,\n",
			chr->abl.mp.n,
			chr->abl.mp.max );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// class_n\n" );
	save_crypt_tab( fp, "%ld,\n", chr->class_n );

	save_crypt_tab( fp, "// resi\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "// n, max_n, add_n\n" );
	for( i = 0; i < RESI_KIND_MAX_N; i++ ){
		set_save_crypt_tab( fp, +1 );
		save_crypt_tab( fp, "%ld, %ld, %ld,\n",
				chr->resi[i].n,
				chr->resi[i].max,
				chr->resi[i].add_n );
		set_save_crypt_tab( fp, -1 );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// add_def, add_crtcl, add_ac\n" );
	save_crypt_tab( fp, "%ld, %ld, %ld,\n",
			chr->add_def,
			chr->add_crtcl,
			chr->add_ac );

	save_crypt_tab( fp, "// fx\n" );
	set_save_crypt_tab( fp, +1 );
	end = &(chr->fx);
	for( fx = end->next->next; fx->prev != end; fx = fx->next ){
		save_game_data_fx_ver_1( fp, ver, flg_txt, fx->prev );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// fx_data\n" );
	save_game_data_fx_data_ver_1( fp, ver, flg_txt, &(chr->fx_data) );

	save_crypt_tab( fp, "// modifier_equip\n" );
	save_game_data_modifier_ver_1(
			fp, ver, flg_txt,
			&(chr->modifier_equip) );

	save_crypt_tab( fp, "// modifier_fx\n" );
	save_game_data_modifier_ver_1(
			fp, ver, flg_txt,
			&(chr->modifier_fx) );

	save_crypt_tab( fp, "// contribution\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(chr->contribution) );

	idx = trans_mnstr_kind_to_idx( chr->mnstr_kind );
	save_crypt_tab( fp, "// mnstr_kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	idx = trans_mnstr_kind_to_idx( chr->mnstr_kind_org );
	save_crypt_tab( fp, "// mnstr_kind_org\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	/* mnstr_tab_t	*mnstr_tab; */

	save_game_data_work_ver_1( fp, ver, flg_txt, chr );

	save_crypt_tab( fp, "// graph_name\n" );
	save_crypt_tab( fp, "\"%s\",\n",
			cv_esc_quote_str( chr->graph_name ) );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データのキャラクタの効果のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* fx_t *fx : 効果
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_fx_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	fx_t *fx
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( fx == NULL )
		return FALSE;

	if( fx->cast_chr != NULL )
		return TRUE;

	set_save_crypt_tab( fp, +1 );

	idx = trans_fx_kind_to_idx( fx->kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// turn\n" );
	save_crypt_tab( fp, "%ld,\n", fx->turn );

	save_crypt_tab( fp, "// n\n" );
	save_crypt_tab( fp, "%ld,\n", fx->n );

	/* fx->chr, fx->cast_chr */

	idx = trans_abl_kind_to_idx( fx->abl_kind );
	save_crypt_tab( fp, "// abl_kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データのキャラクタの効果のデータのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* fx_data_t *fx_data : 効果のデータ
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_fx_data_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	fx_data_t *fx_data
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( fx_data == NULL )
		return FALSE;

	set_save_crypt_tab( fp, +1 );

	save_crypt_tab( fp, "// wpn_hit, wpn_crtcl, wpn_dam\n" );
	save_crypt_tab( fp, "%ld, %ld, %ld,\n",
			fx_data->wpn_hit,
			fx_data->wpn_crtcl,
			fx_data->wpn_dam );

	save_crypt_tab( fp, "// armor_def, armor_crtcl, armor_ac\n" );
	save_crypt_tab( fp, "%ld, %ld, %ld,\n",
			fx_data->armor_def,
			fx_data->armor_crtcl,
			fx_data->armor_ac );

	save_crypt_tab( fp, "// resi_stat\n" );
	save_crypt_tab( fp, "0x%08lx,\n", fx_data->resi_stat );

	save_crypt_tab( fp, "// cure_hp\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "// count\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->cure_hp.count );
	save_crypt_tab( fp, "// turn\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->cure_hp.turn );
	save_crypt_tab( fp, "// rate\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->cure_hp.rate );
	save_crypt_tab( fp, "// n\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->cure_hp.n );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// cure_mp\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "// count\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->cure_mp.count );
	save_crypt_tab( fp, "// turn\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->cure_mp.turn );
	save_crypt_tab( fp, "// rate\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->cure_mp.rate );
	save_crypt_tab( fp, "// n\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->cure_mp.n );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// infra_vision\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->infra_vision );

	save_crypt_tab( fp, "// stomach\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "// rate\n" );
	save_crypt_tab( fp, "%ld,\n",
			fx_data->stomach.rate );
	save_crypt_tab( fp, "// full_rate\n" );
	save_crypt_tab( fp, "%ld,\n",
			fx_data->stomach.full_rate );
	save_crypt_tab( fp, "// digest_p_day\n" );
	save_crypt_tab( fp, "%ld,\n",
			fx_data->stomach.digest_p_day );
	save_crypt_tab( fp, "// digest_n\n" );
	save_crypt_tab( fp, "%ld,\n",
			fx_data->stomach.digest_n );
	save_crypt_tab( fp, "// hungry_rate, starvation_rate\n" );
	save_crypt_tab( fp, "%ld, %ld, \n",
			fx_data->stomach.hungry_rate,
			fx_data->stomach.starvation_rate );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// drunk_rate\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->drunk_rate );

	save_crypt_tab( fp, "// nicotine\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "// rate\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->nicotine.rate );
	save_crypt_tab( fp, "// poisoning_rate\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->nicotine.poisoning_rate );
	save_crypt_tab( fp, "// lost_rate\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->nicotine.lost_rate );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// friend_turn\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->friend_turn );

	save_crypt_tab( fp, "// bless\n" );
	save_crypt_tab( fp, "%ld,\n", fx_data->bless );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの修正値のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* const modifier_t *m : 修正値
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_modifier_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	const modifier_t *m
)
{
	abl_kind_t	abl_n;
	long	max_idx;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( m == NULL )
		return FALSE;

	set_save_crypt_tab( fp, +1 );

	save_crypt_tab( fp, "// face_mjr, face_mnr\n" );
	save_crypt_tab( fp, "\'%s\',\n",
			cv_esc_quote_c( m->face_mjr ) );
	save_crypt_tab( fp, "\'%s\',\n",
			cv_esc_quote_c( m->face_mnr ) );

	save_crypt_tab( fp, "// sex\n" );
	save_crypt_tab( fp, "%ld,\n",
			trans_sex_kind_to_idx( m->sex ) );

	save_crypt_tab( fp, "// wpn_hit, wpn_crtcl, wpn_dam\n" );
	save_crypt_tab( fp, "%ld, %ld, %ld,\n",
			m->wpn_hit, m->wpn_crtcl, m->wpn_dam );

	save_crypt_tab( fp, "// armor_def, armor_crtcl, armor_ac\n" );
	save_crypt_tab( fp, "%ld, %ld, %ld,\n",
			m->armor_def, m->armor_crtcl, m->armor_ac );

	save_crypt_tab( fp, "// abl_lev\n" );
	set_save_crypt_tab( fp, +1 );
	max_idx = get_abl_kind_trans_tab_max_n();
	for( i = 0; i < max_idx; i++ ){
		abl_n = trans_idx_to_abl_kind( i );
		save_crypt_tab( fp, "// %s\n",
				get_abl_name( abl_n ) );
		save_crypt_tab( fp, "%ld,\n", m->add_lev[abl_n] );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// add_resi_n\n" );
	set_save_crypt_tab( fp, +1 );
	for( i = 0; i < RESI_KIND_MAX_N; i++ ){
		save_crypt_tab( fp, "%ld,\n", m->add_resi_n[i] );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// resi_stat\n" );
	save_crypt_tab( fp, "0x%08lx,\n", m->resi_stat );

	save_crypt_tab( fp, "// cure_hp\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "%ld, %ld, %ld, %ld,\n",
			m->cure_hp.count, m->cure_hp.turn,
			m->cure_hp.rate, m->cure_hp.n );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// cure_mp\n" );
	set_save_crypt_tab( fp, +1 );
	save_crypt_tab( fp, "%ld, %ld, %ld, %ld,\n",
			m->cure_mp.count, m->cure_mp.turn,
			m->cure_mp.rate, m->cure_mp.n );
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// add_move_speed\n" );
	save_crypt_tab( fp, "%ld,\n", m->add_move_speed );

	save_crypt_tab( fp, "// stomach_digest_n\n" );
	save_crypt_tab( fp, "%ld,\n", m->stomach_digest_n );

	save_crypt_tab( fp, "// teleport_n, teleport_party_n\n" );
	save_crypt_tab( fp, "%ld, %ld,\n",
			m->teleport_n, m->teleport_party_n );

	save_crypt_tab( fp, "// bless\n" );
	save_crypt_tab( fp, "%ld,\n", m->bless );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの作業データのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* chr_t *chr : キャラクタ
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_work_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( chr == NULL )
		return FALSE;

	save_crypt_tab( fp, "// work\n" );
	set_save_crypt_tab( fp, +1 );

	save_crypt_tab( fp, "// flg\n" );
	save_crypt_tab( fp, "0x%08lx,\n", chr->work.flg );

	save_crypt_tab( fp, "// caught\n" );
	save_crypt_tab( fp, "%ld,\n", chr->work.caught );

	/* struct chr_t	*catch_chr; */

	/* struct chr_t	*link_chr; */

	save_crypt_tab( fp, "// teleport_n\n" );
	save_crypt_tab( fp, "%ld,\n", chr->work.teleport_n );

	save_crypt_tab( fp, "// teleport_party_n\n" );
	save_crypt_tab( fp, "%ld,\n", chr->work.teleport_party_n );

	save_crypt_tab( fp, "// flg_can_wish\n" );
	save_crypt_tab( fp, "%ld,\n", chr->work.flg_can_wish );

	if( chk_ver_new_match( ver, 1, 1, 4 ) ){
		long	n;

		if( chr->work.request == NULL ){
			n = -1;
		} else {
			request_t	*req_ls = get_request_ls();

			n = chr->work.request - req_ls;
		}

		save_crypt_tab( fp, "// request\n" );
		save_crypt_tab( fp, "%ld,\n", n );
	}

	save_crypt_tab( fp, "// towner_dx, towner_dy\n" );
	save_crypt_tab( fp, "%ld, %ld,\n",
			chr->work.towner_dx,
			chr->work.towner_dy );

	/* door_t	*enter_door; */

	save_crypt_tab( fp, "// dismissal_turn\n" );
	save_crypt_tab( fp, "%ld,\n", chr->work.dismissal_turn );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの全てのメンバーのアイテムのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_all_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	mbr_t	**ls_mbr;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	ls_mbr = get_ls_mbr();
	if( ls_mbr == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// item\n" );

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		save_crypt_tab( fp, "\n" );
		save_crypt_tab( fp, "member_item %ld = ", i );
		save_game_data_item_mbr_ver_1( fp, ver, flg_txt, ls_mbr[i] );
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データのメンバーのアイテムのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr
)
{
	item_t	*head, *p, *item;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( chk_flg( mbr->stat, FLG_STAT_NOT_EXIST ) )
		return FALSE;

	set_save_crypt_tab( fp, +1 );

	head = get_mbr_item_asgn( mbr );
	if( head == NULL )
		p = NULL;
	else
		p = head->next->next;
	for( i = 0; i < MBR_ITEM_MAX_N; i++, p = p->next ){
		if( p == NULL )
			break;

		item = p->prev;
		if( item == head )
			break;
		if( item->kind == ITEM_KIND_NULL )
			continue;

		save_crypt_tab( fp, "\n" );
		save_crypt_tab( fp, "item = " );
		save_game_data_item_ver_1( fp, ver, flg_txt, mbr, item );
	}

	p = get_mbr_item_asgn_equip( mbr );
	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		if( p == NULL )
			break;

		item = &(p[i]);

		if( item->kind == ITEM_KIND_NULL )
			continue;

		save_crypt_tab( fp, "\n" );
		save_crypt_tab( fp, "equip %ld = ", i );
		save_game_data_item_ver_1( fp, ver, flg_txt, mbr, item );
	}

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データのアイテムのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	bool_t	flg_success;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	set_save_crypt_tab( fp, +1 );

	save_crypt_tab( fp, "// %s\n", get_item_mjr_name( item->mjr ) );
	save_crypt_tab( fp, "// %s\n",
			get_item_mnr_name( item->mjr, item->mnr ) );
	save_crypt_tab( fp, "\n" );

	idx = trans_item_kind_to_idx( item->kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// dat\n" );
	set_save_crypt_tab( fp, +1 );

	flg_success = FALSE;

	switch( item->kind ){
	case ITEM_KIND_NULL:
		return FALSE;
	case ITEM_KIND_WPN:
		flg_success = save_game_data_item_wpn_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_ARMOR:
		flg_success = save_game_data_item_armor_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_POTION:
		flg_success = save_game_data_item_potion_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_SCROLL:
		flg_success = save_game_data_item_scroll_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_STICK:
		flg_success = save_game_data_item_stick_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_ACCE:
		flg_success = save_game_data_item_acce_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_INST:
		flg_success = save_game_data_item_inst_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_ANTHOLOGY:
		flg_success = save_game_data_item_anthology_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_LIGHT:
		flg_success = save_game_data_item_light_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_SPIKE:
		flg_success = save_game_data_item_spike_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_FOOD:
		flg_success = save_game_data_item_food_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_CHEST:
		flg_success = save_game_data_item_chest_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_TOBACCO:
		flg_success = save_game_data_item_tobacco_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_PIPE:
		flg_success = save_game_data_item_pipe_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_DISPOSAL:
		flg_success = save_game_data_item_disposal_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_RARE_GOODS:
		flg_success = save_game_data_item_rare_goods_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_BONE:
		flg_success = save_game_data_item_bone_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_COIN:
		flg_success = save_game_data_item_coin_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_JUNK:
		flg_success = save_game_data_item_junk_ver_1(
				fp, ver, flg_txt, mbr, item );
		break;
	case ITEM_KIND_MAX_N:
		return FALSE;
	}
	if( !flg_success )
		return FALSE;

	set_save_crypt_tab( fp, -1 );

	/* item->next, item->prev */

	save_crypt_tab( fp, "// name\n" );
	save_crypt_tab( fp, "\"%s\",\n",
			cv_esc_quote_str( item->name ) );
	save_crypt_tab( fp, "// art_name\n" );
	save_crypt_tab( fp, "\"%s\",\n",
			cv_esc_quote_str( item->art_name ) );
	save_crypt_tab( fp, "// alias\n" );
	save_crypt_tab( fp, "\"%s\",\n",
			cv_esc_quote_str( item->alias ) );

	save_crypt_tab( fp, "// equip_kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->equip_kind) );

	save_crypt_tab( fp, "// mjr\n" );
	save_crypt_tab( fp, "'%s',\n", cv_esc_quote_c( item->mjr ) );

	save_crypt_tab( fp, "// mnr\n" );
	save_crypt_tab( fp, "'%s',\n", cv_esc_quote_c( item->mnr ) );

	save_crypt_tab( fp, "// x\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->x) );
	save_crypt_tab( fp, "// y\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->y) );

	save_crypt_tab( fp, "// n\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->n) );
	save_crypt_tab( fp, "// stock\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->stock) );

	save_crypt_tab( fp, "// flg\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->flg) );

	save_game_data_modifier_ver_1(
			fp, ver, flg_txt, &(item->modifier) );

	/* tab */

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの武器のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_wpn_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_WPN )
		return FALSE;

	idx = trans_wpn_kind_to_idx( item->dat.wpn.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// add_hit\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.wpn.add_hit) );

	save_crypt_tab( fp, "// add_crtcl\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.wpn.add_crtcl) );

	save_crypt_tab( fp, "// add_dam\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.wpn.add_dam) );

	save_crypt_tab( fp, "// slayer\n" );
	save_crypt_tab( fp, "'%s',\n",
			cv_esc_quote_c( item->dat.wpn.slayer ) );

	save_crypt_tab( fp, "// randm_art\n" );
	set_save_crypt_tab( fp, +1 );
	for( i = 0; i < WPN_RANDM_ART_LS_MAX_N; i++ ){
		if( item->dat.wpn.randm_art[i].kind
				== WPN_RANDM_ART_KIND_NULL ){
			break;
		}

		set_save_crypt_tab( fp, +1 );

		idx = trans_wpn_randm_art_kind_to_idx(
				item->dat.wpn.randm_art[i].kind );
		save_crypt_tab( fp, "// kind\n" );
		save_crypt_tab( fp, "%ld,\n", (long)idx );

		save_crypt_tab( fp, "// mjr\n" );
		save_crypt_tab( fp, "'%c',\n",
				(char)item->dat.wpn.randm_art[i].mjr );

		save_crypt_tab( fp, "// mnr\n" );
		save_crypt_tab( fp, "'%c',\n",
				(char)item->dat.wpn.randm_art[i].mnr );

		set_save_crypt_tab( fp, -1 );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// flg\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.wpn.flg) );

	return TRUE;
}

/***************************************************************
* ゲーム・データの防具のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_armor_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_ARMOR )
		return FALSE;

	idx = trans_armor_kind_to_idx( item->dat.armor.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// add_def\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.armor.add_def) );

	save_crypt_tab( fp, "// add_crtcl\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.armor.add_crtcl) );

	save_crypt_tab( fp, "// add_ac\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.armor.add_ac) );

	save_crypt_tab( fp, "// randm_art\n" );
	set_save_crypt_tab( fp, +1 );
	for( i = 0; i < ARMOR_RANDM_ART_LS_MAX_N; i++ ){
		if( item->dat.armor.randm_art[i].kind
				== ARMOR_RANDM_ART_KIND_NULL ){
			break;
		}

		set_save_crypt_tab( fp, +1 );

		idx = trans_armor_randm_art_kind_to_idx(
				item->dat.armor.randm_art[i].kind );
		save_crypt_tab( fp, "// kind\n" );
		save_crypt_tab( fp, "%ld,\n", (long)idx );

		save_crypt_tab( fp, "// mjr\n" );
		save_crypt_tab( fp, "'%c',\n",
				(char)item->dat.armor.randm_art[i].mjr );

		save_crypt_tab( fp, "// mnr\n" );
		save_crypt_tab( fp, "'%c',\n",
				(char)item->dat.armor.randm_art[i].mnr );

		set_save_crypt_tab( fp, -1 );
	}
	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの薬のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_potion_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_POTION )
		return FALSE;

	idx = trans_potion_kind_to_idx( item->dat.potion.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	return TRUE;
}

/***************************************************************
* ゲーム・データの巻物のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_scroll_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_SCROLL )
		return FALSE;

	idx = trans_scroll_kind_to_idx( item->dat.scroll.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	return TRUE;
}

/***************************************************************
* ゲーム・データの杖のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_stick_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_STICK )
		return FALSE;

	idx = trans_stick_kind_to_idx( item->dat.stick.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	idx = trans_spell_kind_to_idx( item->dat.stick.spell_kind );
	save_crypt_tab( fp, "// spell_kind_idx\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// n\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.stick.n) );

	return TRUE;
}

/***************************************************************
* ゲーム・データのアクセサリのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_acce_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_ACCE )
		return FALSE;

	idx = trans_acce_kind_to_idx( item->dat.acce.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	idx = trans_ring_kind_to_idx( item->dat.acce.ring_kind );
	save_crypt_tab( fp, "// ring_kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	idx = trans_amulet_kind_to_idx( item->dat.acce.amulet_kind );
	save_crypt_tab( fp, "// amulet_kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	idx = trans_necklace_kind_to_idx( item->dat.acce.necklace_kind );
	save_crypt_tab( fp, "// necklace_kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	return TRUE;
}

/***************************************************************
* ゲーム・データの楽器のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_inst_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_INST )
		return FALSE;

	idx = trans_inst_kind_to_idx( item->dat.inst.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// flg_limit\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.inst.flg_limit) );

	idx = trans_spell_kind_to_idx( item->dat.inst.spell_kind );
	save_crypt_tab( fp, "// spell_kind_idx\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	return TRUE;
}

/***************************************************************
* ゲーム・データの詩集のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_anthology_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_ANTHOLOGY )
		return FALSE;

	idx = trans_anthology_kind_to_idx( item->dat.anthology.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	return TRUE;
}

/***************************************************************
* ゲーム・データの明かりのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_light_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_LIGHT )
		return FALSE;

	idx = trans_light_kind_to_idx( item->dat.light.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// turn\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.light.turn) );

	idx = trans_wish_level_to_idx( item->dat.light.wish_level );
	save_crypt_tab( fp, "// wish_level\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// wish_n\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.light.wish_n) );

	save_crypt_tab( fp, "// flg_used\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.light.flg_used) );

	return TRUE;
}

/***************************************************************
* ゲーム・データの釘のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_spike_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_SPIKE )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの食料のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_food_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_FOOD )
		return FALSE;

	idx = trans_food_kind_to_idx( item->dat.food.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	return TRUE;
}

/***************************************************************
* ゲーム・データの宝箱のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_chest_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;
	item_t	*end, *p;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_CHEST )
		return FALSE;

	/* chest->contents */

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// contents item\n" );
	set_save_crypt_tab( fp, +1 );

	end = item->dat.chest.contents;
	if( end != NULL ){
		for( p = end->next; p != end; p = p->next ){
			if( end == NULL )
				break;

			save_crypt_tab( fp, "\n" );
			save_game_data_item_ver_1( fp, ver, flg_txt,
					mbr, p );
		}
	}

	set_save_crypt_tab( fp, -1 );

	/* chest->trap */

	save_crypt_tab( fp, "// trap\n" );
	set_save_crypt_tab( fp, +1 );

	/* chest->next, chest->prev */

	do {
		if( item->dat.chest.trap == NULL )
			break;
		if( item->dat.chest.trap->kind  != TRAP_KIND_NULL )
			break;

		idx = trans_trap_kind_to_idx( item->dat.chest.trap->kind );
		save_crypt_tab( fp, "// kind\n" );
		save_crypt_tab( fp, "%ld,\n", (long)idx );

		save_crypt_tab( fp, "// x,\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(item->dat.chest.trap->x) );

		save_crypt_tab( fp, "// y\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(item->dat.chest.trap->y) );

		save_crypt_tab( fp, "// lev\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(item->dat.chest.trap->lev) );

		save_crypt_tab( fp, "// difficulty\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(item->dat.chest.trap->difficulty) );

		save_crypt_tab( fp, "// flg_chked\n" );
		save_crypt_tab( fp, "0x%08lx,\n",
				(long)(item->dat.chest.trap->flg_chked) );
	} while( 0 );

	/* tab */

	set_save_crypt_tab( fp, -1 );

	/* chest->ref */

	save_crypt_tab( fp, "// ref\n" );
	save_crypt_tab( fp, "%ld,\n",
			(long)(item->dat.chest.contents->dat.chest.ref) );

	return TRUE;
}

/***************************************************************
* ゲーム・データの煙草のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_tobacco_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_TOBACCO )
		return FALSE;

	idx = trans_tobacco_kind_to_idx( item->dat.tobacco.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	idx = trans_tobacco_brand_to_idx( item->dat.tobacco.brand );
	save_crypt_tab( fp, "// brand\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// turn\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.tobacco.turn) );

	return TRUE;
}

/***************************************************************
* ゲーム・データのパイプのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_pipe_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_PIPE )
		return FALSE;

	idx = trans_pipe_kind_to_idx( item->dat.pipe.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// turn\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.pipe.turn) );

	save_crypt_tab( fp, "// consume_turn\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.pipe.consume_turn) );

	return TRUE;
}

/***************************************************************
* ゲーム・データの吸い殻入れのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_disposal_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_DISPOSAL )
		return FALSE;

	save_crypt_tab( fp, "// n\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.disposal.n) );

	save_crypt_tab( fp, "// max_n\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.disposal.max_n) );

	return TRUE;
}

/***************************************************************
* ゲーム・データのレア・グッズのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_rare_goods_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_RARE_GOODS )
		return FALSE;

	idx = trans_rare_goods_kind_to_idx( item->dat.rare_goods.kind );
	save_crypt_tab( fp, "// kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	idx = trans_mnstr_kind_to_idx( item->dat.rare_goods.mnstr_kind );
	save_crypt_tab( fp, "// mnstr_kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	return TRUE;
}

/***************************************************************
* ゲーム・データの骨のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_bone_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_BONE )
		return FALSE;
	if( item->dat.bone.mnstr_tab == NULL )
		return FALSE;

	idx = trans_mnstr_kind_to_idx(
			item->dat.bone.mnstr_tab->mnstr_kind );
	save_crypt_tab( fp, "// mnstr_kind\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	save_crypt_tab( fp, "// dun_lev\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(item->dat.bone.dun_lev) );

	return TRUE;
}

/***************************************************************
* ゲーム・データの金貨のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_coin_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_COIN )
		return FALSE;

	idx = trans_coin_kind_to_idx( item->dat.coin.kind );
	save_crypt_tab( fp, "// coin\n" );
	save_crypt_tab( fp, "%ld,\n", (long)idx );

	return TRUE;
}

/***************************************************************
* ゲーム・データのゴミのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* mbr_t *mbr : メンバー
* item_t *item : アイテム
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_item_junk_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
)
{
	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( mbr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_JUNK )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの薬の色のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_potion_color_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	ls_identified_t	*tab;
	n_msg_t	*idx_tab;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	tab = get_color_tab();
	idx_tab = get_color_idx_tab();

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// item color\n" );
	save_crypt_tab( fp, "potion_color = " );
	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		n_msg_t	name_n;

		if( tab[i].name_idx <= -1 )
			break;

		name_n = idx_tab[tab[i].name_idx];
		save_crypt_tab( fp, "// %s\n", MSG( name_n ) );
		save_crypt_tab( fp, "%ld,\n", tab[i].name_idx );
	}

	save_crypt_tab( fp, "// end\n" );
	save_crypt_tab( fp, "%ld,\n", (long)-1 );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの巻物のタイトルのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_scroll_ttl_syllable_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	scroll_tab_t	*tab;
	n_msg_t	*idx_tab;
	long	i, j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	tab = get_scroll_tab_head();
	idx_tab = get_ttl_syllable_idx_tab();

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// item title syllable\n" );
	save_crypt_tab( fp, "scroll_ttl_syllable = " );
	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( tab[i].name_n == N_MSG_NULL )
			break;

		save_crypt_tab( fp, "// %s\n", tab[i].name );

		set_save_crypt_tab( fp, +1 );

		for( j = 0; j < SCROLL_TTL_SYLLABLE_MAX_N; j++ ){
			n_msg_idx_t	idx;

			idx = tab[i].ttl_idx[j];

			if( idx > -1 ){
				save_crypt_tab( fp, "// %s\n",
						MSG( idx_tab[idx] ) );
			} else {
				save_crypt_tab( fp, "// ----\n" );
			}

			save_crypt_tab( fp, "%ld,\n", idx );
		}

		save_crypt_tab( fp, "// end\n" );
		save_crypt_tab( fp, "%ld,\n", (long)-1 );

		set_save_crypt_tab( fp, -1 );
	}

	save_crypt_tab( fp, "// end\n" );
	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの杖の材質のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* stick_kind_t kind : 杖の種類
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_stick_material_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	stick_kind_t kind
)
{
	ls_identified_t	*tab;
	n_msg_t	*idx_tab;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// item material\n" );

	idx_tab = get_stick_material_idx_tab();
	tab = NULL;

	switch( kind ){
	case STICK_KIND_NULL:
	case STICK_KIND_MAX_N:
		break;
	case STICK_KIND_WAND:
		save_crypt_tab( fp, "wand_material = " );

		tab = get_wand_material_tab();
		break;
	case STICK_KIND_ROD:
		save_crypt_tab( fp, "rod_material = " );

		tab = get_rod_material_tab();
		break;
	case STICK_KIND_STAFF:
		save_crypt_tab( fp, "staff_material = " );

		tab = get_staff_material_tab();
		break;
	}
	if( tab == NULL )
		return FALSE;

	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		n_msg_t	name_n;

		if( tab[i].name_idx <= -1 )
			break;

		name_n = idx_tab[tab[i].name_idx];
		save_crypt_tab( fp, "// %s\n", MSG( name_n ) );
		save_crypt_tab( fp, "%ld,\n", tab[i].name_idx );
	}

	save_crypt_tab( fp, "// end\n" );
	save_crypt_tab( fp, "%ld,\n", (long)-1 );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データのアクセサリの材質のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* acce_kind_t kind : アクセサリの種類
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_acce_material_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	acce_kind_t kind
)
{
	ls_identified_t	*tab;
	n_msg_t	*idx_tab;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// item material\n" );

	idx_tab = get_acce_material_idx_tab();
	tab = NULL;

	switch( kind ){
	case ACCE_KIND_NULL:
	case ACCE_KIND_MAX_N:
		break;
	case ACCE_KIND_RING:
		save_crypt_tab( fp, "ring_material = " );

		tab = get_ring_material_tab();
		break;
	case ACCE_KIND_AMULET:
		save_crypt_tab( fp, "amulet_material = " );

		tab = get_amulet_material_tab();
		break;
	case ACCE_KIND_NECKLACE:
		save_crypt_tab( fp, "necklace_material = " );

		tab = get_necklace_material_tab();
		break;
	}
	if( tab == NULL )
		return FALSE;

	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < LOOP_MAX_1000; i++ ){
		n_msg_t	name_n;

		if( tab[i].name_idx <= -1 )
			break;

		name_n = idx_tab[tab[i].name_idx];
		save_crypt_tab( fp, "// %s\n", MSG( name_n ) );
		save_crypt_tab( fp, "%ld,\n", tab[i].name_idx );
	}

	save_crypt_tab( fp, "// end\n" );
	save_crypt_tab( fp, "%ld,\n", (long)-1 );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの薬の識別フラグのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_potion_identified_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	potion_tab_t	*tab;
	potion_kind_t	kind;
	long	max_idx;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// identified flags potion\n" );
	save_crypt_tab( fp, "potion_identified = " );
	set_save_crypt_tab( fp, +1 );

	max_idx = get_potion_trans_tab_max_n();
	for( i = 0; i < max_idx; i++ ){
		kind = trans_idx_to_potion_kind( i );
		tab = get_potion_tab( kind );

		if( tab == NULL ){
			save_crypt_tab( fp, "// NULL\n" );
			save_crypt_tab( fp, "0,\n" );
		} else {
			save_crypt_tab( fp, "// %s\n", tab->name );
			save_crypt_tab( fp, "%ld,\n",
					(long)(tab->flg_identified) );
		}
	}

	save_crypt_tab( fp, "// end\n" );
	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの巻物の識別フラグのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_scroll_identified_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	scroll_tab_t	*tab;
	scroll_kind_t	kind;
	long	max_idx;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// identified flags scroll\n" );
	save_crypt_tab( fp, "scroll_identified = " );
	set_save_crypt_tab( fp, +1 );

	max_idx = get_scroll_trans_tab_max_n();
	for( i = 0; i < max_idx; i++ ){
		kind = trans_idx_to_scroll_kind( i );
		tab = get_scroll_tab( kind );

		if( tab == NULL ){
			save_crypt_tab( fp, "// NULL\n" );
			save_crypt_tab( fp, "0,\n" );
		} else {
			save_crypt_tab( fp, "// %s\n", tab->name );
			save_crypt_tab( fp, "%ld,\n",
					(long)(tab->flg_identified) );
		}
	}

	save_crypt_tab( fp, "// end\n" );
	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データのキー・アイテムのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_key_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	long	idx;
	long	n;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// key item\n" );
	save_crypt_tab( fp, "key_item = " );
	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < STAR_DROP_KIND_MAX_N; i++ ){
		set_save_crypt_tab( fp, +1 );

		idx = trans_key_item_kind_to_idx( (star_drop_kind_t)i );
		save_crypt_tab( fp, "// kind\n" );
		save_crypt_tab( fp, "%ld,\n", (long)idx );

		n = (long)chk_key_item( (star_drop_kind_t)i );
		save_crypt_tab( fp, "// flg_have\n" );
		save_crypt_tab( fp, "%ld,\n", (long)n );

		set_save_crypt_tab( fp, -1 );
	}

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの自動マーク・リストのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_auto_mark_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	mbr_t	**ls_mbr;
	auto_mark_t	*am;
	long	auto_mark_n;
	long	idx;
	long	i, j, k;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	ls_mbr = get_ls_mbr();
	if( ls_mbr == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// auto mark\n" );

	save_crypt_tab( fp, "\n" );
	for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
		char	*ttl;

		if( !chk_flg_ena_auto_mark( j ) )
			continue;

		ttl = get_msg_ttl_auto_mark_code( j );
		if( ttl == NULL )
			continue;

		save_crypt_tab( fp, "auto_mark_title %ld = \"%s\"\n",
				j, cv_esc_quote_str( ttl ) );
	}

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		save_crypt_tab( fp, "\n" );
		save_crypt_tab( fp, "auto_mark %ld = ", i );
		set_save_crypt_tab( fp, +1 );

		for( j = 0; j < AUTO_MARK_MAX_N; j++ ){
			if( !chk_flg_ena_auto_mark( j ) )
				continue;

			for( k = 0; k < POSITION_KIND_MAX_N; k++ ){
				am = get_auto_mark( i, j,
						(position_kind_t)k );
				if( am == NULL )
					continue;

				idx = trans_position_kind_to_idx(
						(position_kind_t)k );
				auto_mark_n = (idx * AUTO_MARK_POSITION_MUL)
						+ j;

				if( !save_game_data_auto_mark_ver_1(
						fp, ver, flg_txt,
						am, auto_mark_n ) ){
					return FALSE;
				}
			}
		}

		set_save_crypt_tab( fp, -1 );
	}

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		if( !save_game_data_auto_mark_appoint_item_ver_1(
				fp, ver, flg_txt, i ) ){
			return FALSE;
		}
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データの自動マークのアイテムのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* long ls_mbr_n : メンバー・リスト番号
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_auto_mark_appoint_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
)
{
	mbr_t	**ls_mbr;
	auto_mark_appoint_item_t	*ls;
	long	i, j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	ls_mbr = get_ls_mbr();
	if( ls_mbr == NULL )
		return FALSE;
	if( ls_mbr[ls_mbr_n] == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// %s\n", ls_mbr[ls_mbr_n]->name );
	save_crypt_tab( fp, "auto_mark_appoint_item %ld = ", ls_mbr_n );
	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < AUTO_MARK_MAX_N; i++ ){
		if( !chk_flg_ena_auto_mark( i ) )
			continue;

		ls = get_ls_auto_mark_appoint_item( ls_mbr_n, i );
		if( ls == NULL )
			continue;

		save_crypt_tab( fp, "// %s\n",
				get_msg_ttl_auto_mark_name( i ) );
		save_crypt_tab( fp, "%ld,\n", (long)i );

		set_save_crypt_tab( fp, +1 );

		for( j = 0; j < AUTO_MARK_APPOINT_ITEM_MAX_N; j++ ){
			if( ls[j].mjr == FACE_MJR_NULL )
				break;

			save_crypt_tab( fp, "\n" );
			save_crypt_tab( fp, "// %s\n",
					get_item_mnr_name( ls[j].mjr,
					ls[j].mnr ) );

			save_crypt_tab( fp, "// mjr\n" );
			save_crypt_tab( fp, "\'%s\',\n",
					cv_esc_quote_c( ls[j].mjr ) );

			save_crypt_tab( fp, "// mnr\n" );
			save_crypt_tab( fp, "\'%s\',\n",
					cv_esc_quote_c( ls[j].mnr ) );

			save_crypt_tab( fp, "// flg_ena\n" );
			save_crypt_tab( fp, "%ld,\n",
					(long)(ls[j].flg_ena) );
		}

		set_save_crypt_tab( fp, -1 );
	}

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データのサーチ・モード・フラグのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_flg_srch_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	mbr_t	**ls_mbr;
	bool_t	*ls;
	long	i;

	ls_mbr = get_ls_mbr();
	if( ls_mbr == NULL )
		return FALSE;

	ls = get_ls_flg_srch();
	if( ls == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// list flag search\n" );
	save_crypt_tab( fp, "flg_srch = " );
	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		do {
			if( ls_mbr[i] == NULL )
				break;
			if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
				break;

			save_crypt_tab( fp, "//%s\n", ls_mbr[i]->name );
		} while( 0 );

		save_crypt_tab( fp, "%ld, //%ld\n", (long)(ls[i]), i );
	}

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの自動マークのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* const auto_mark_t *a : 自動マーク
* long auto_mark_n : 自動マークのスロット番号
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_auto_mark_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	const auto_mark_t *a, long auto_mark_n
)
{
	long	idx;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( a == NULL )
		return FALSE;

	set_save_crypt_tab( fp, +1 );

	idx = auto_mark_n;
	save_crypt_tab( fp, "// no.\n" );
	save_crypt_tab( fp, "%ld,\n", idx );

	idx = trans_am_trgt_to_idx( a->trgt );
	save_crypt_tab( fp, "// target\n" );
	save_crypt_tab( fp, "%ld,\n", idx );

	idx = trans_am_dist_to_idx( a->dist );
	save_crypt_tab( fp, "// distance\n" );
	save_crypt_tab( fp, "%ld,\n", idx );

	idx = trans_am_act_to_idx( a->act );
	save_crypt_tab( fp, "// action\n" );
	save_crypt_tab( fp, "%ld,\n", idx );

	idx = trans_am_cond_to_idx( a->cond );
	save_crypt_tab( fp, "// condition\n" );
	save_crypt_tab( fp, "%ld,\n", idx );

	save_crypt_tab( fp, "// macro\n" );
	save_crypt_tab( fp, "\"%s\",\n", cv_esc_quote_str( a->macro ) );

	save_crypt_tab( fp, "// flag\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(a->flg) );

	idx = trans_am_dflt_to_idx( a->dflt );
	save_crypt_tab( fp, "// kind of default\n" );
	save_crypt_tab( fp, "%ld,\n", idx );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの呪文リストのセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_spell_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	mbr_t	**ls_mbr;
	long	i, j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	ls_mbr = get_ls_mbr();
	if( ls_mbr == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// spell\n" );

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		save_crypt_tab( fp, "\n" );
		save_crypt_tab( fp, "spell %ld = ", i );
		set_save_crypt_tab( fp, +1 );

		for( j = 0; j < SPELL_KIND_MAX_N; j++ ){
			spell_kind_t	kind;
			cast_tab_t	*tab;

			kind = trans_idx_to_spell_kind( j );

			tab = get_cast_tab( ls_mbr[i], kind );
			if( tab == NULL )
				continue;

			if( !save_game_data_spell_ver_1(
					fp, ver, flg_txt, tab ) ){
				return FALSE;
			}
		}

		set_save_crypt_tab( fp, -1 );
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データの呪文のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* cast_tab_t *tab : 呪文の使用可・不可のリスト
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_spell_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	cast_tab_t *tab
)
{
	char	*name;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( tab == NULL )
		return FALSE;

	name = get_spell_name( tab->kind );
	if( name == NULL )
		name = "";

	save_crypt_tab( fp, "// %s\n", name );
	save_crypt_tab( fp, "%ld,\n", tab->flg_cast );

	return TRUE;
}

/***************************************************************
* ゲーム・データのメンバーの隊列のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_mbr_formation_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	party_t	*pty = get_party();
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "member_formation = " );
	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < MBR_MAX_N; i++ ){
		bool_t	flg_null;

		flg_null = FALSE;

		if( pty->mbr[i] == NULL ){
			flg_null = TRUE;
		} else if( pty->mbr[i]->mbr_n == MBR_N_NOT_JOIN ){
			flg_null = TRUE;
		} else if( chk_flg( pty->mbr[i]->stat,
				FLG_STAT_NOT_EXIST ) ){
			flg_null = TRUE;
		}

		if( flg_null ){
			save_crypt_tab( fp, "// NULL\n" );
			save_crypt_tab( fp, "-1,\n" );
		} else {
			save_crypt_tab( fp, "// %s\n",
					pty->mbr[i]->name );
			save_crypt_tab( fp, "%ld,\n",
					pty->mbr[i]->ls_mbr_n );
		}
	}

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データのペットの隊列のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_pet_formation_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	pet_t	**pet = get_party_pet();
	pet_t	**ls_pet = get_ls_pet();
	long	i, j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "pet_formation = " );
	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < PET_MAX_N; i++ ){
		bool_t	flg_null;

		flg_null = FALSE;

		if( pet[i] == NULL ){
			flg_null = TRUE;
		} else if( chk_flg( pet[i]->stat, FLG_STAT_NOT_EXIST ) ){
			flg_null = TRUE;
		}

		if( flg_null ){
			save_crypt_tab( fp, "// NULL\n" );
			save_crypt_tab( fp, "-1,\n" );
		} else {
			for( j = 0; j < LS_PET_MAX_N; j++ )
				if( ls_pet[j] == pet[i] )
					break;

			if( j < LS_PET_MAX_N ){
				save_crypt_tab( fp, "// %s\n",
						pet[i]->name );
				save_crypt_tab( fp, "%ld,\n", j );
			}
		}
	}

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データの依頼のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_request_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	request_t	*req;
	long	idx;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	req = get_request_ls();
	if( req == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "request = " );
	set_save_crypt_tab( fp, +1 );

	for( i = 0; i < REQUEST_MAX_N; i++ ){
		if( req[i].kind == REQUEST_KIND_NULL )
			continue;

		set_save_crypt_tab( fp, +1 );

		if( chk_ver_new_match( ver, 1, 1, 5 ) ){
			save_crypt_tab( fp, "// n\n" );
			save_crypt_tab( fp, "%ld,\n", i );
		}

		idx = trans_request_kind_to_idx( req[i].kind );
		save_crypt_tab( fp, "// kind\n" );
		save_crypt_tab( fp, "%ld,\n", idx );

		save_crypt_tab( fp, "// dun_min_lev\n" );
		save_crypt_tab( fp, "%ld,\n", req[i].dun_min_lev );
		save_crypt_tab( fp, "// dun_max_lev\n" );
		save_crypt_tab( fp, "%ld,\n", req[i].dun_max_lev );
		save_crypt_tab( fp, "// dun_true_lev\n" );
		save_crypt_tab( fp, "%ld,\n", req[i].dun_true_lev );

		save_crypt_tab( fp, "// prize\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(req[i].prize) );
		save_crypt_tab( fp, "// exp\n" );
		save_crypt_tab( fp, "%ld,\n", req[i].exp );
		save_crypt_tab( fp, "// limit\n" );
		save_crypt_tab( fp, "%ld,\n", req[i].limit );

		save_crypt_tab( fp, "// flg_contract\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(req[i].flg_contract) );
		save_crypt_tab( fp, "// flg_contract_mbr\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(req[i].flg_contract_mbr) );
		save_crypt_tab( fp, "// contract_name\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(req[i].idx_contract_name) );
		idx = trans_sex_kind_to_idx( (sex_t)(req[i].contract_sex) );
		save_crypt_tab( fp, "// contract_sex\n" );
		save_crypt_tab( fp, "%ld,\n", idx );
		save_crypt_tab( fp, "// flg_finish\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(req[i].flg_finish) );

		idx = trans_rare_goods_kind_to_idx( req[i].rare_goods_kind );
		save_crypt_tab( fp, "// rare_goods_kind\n" );
		save_crypt_tab( fp, "%ld,\n", idx );

		save_crypt_tab( fp, "// flg_mnstr_is_npc\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(req[i].flg_mnstr_is_npc) );

		idx = trans_mnstr_kind_to_idx( req[i].mnstr_kind );
		save_crypt_tab( fp, "// mnstr_kind\n" );
		save_crypt_tab( fp, "%ld,\n", idx );

		save_crypt_tab( fp, "// mnstr_n\n" );
		save_crypt_tab( fp, "%ld,\n", req[i].mnstr_n );
		save_crypt_tab( fp, "// mnstr_exterminate_n\n" );
		save_crypt_tab( fp, "%ld,\n", req[i].mnstr_exterminate_n );

		save_crypt_tab( fp, "// heading\n" );
		save_crypt_tab( fp, "\"%s\",\n", req[i].heading );
		save_crypt_tab( fp, "// idx_fmt\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(req[i].idx_fmt) );
		save_crypt_tab( fp, "// msg\n" );
		save_crypt_tab( fp, "\"%s\",\n",
				cv_esc_quote_str( req[i].msg ) );

		save_crypt_tab( fp, "// idx_client_name\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(req[i].idx_client_name) );
		save_crypt_tab( fp, "// idx_mnstr_name\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(req[i].idx_mnstr_name) );
		save_crypt_tab( fp, "// idx_rescue_trgt_name\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(req[i].idx_rescue_trgt_name) );
		save_crypt_tab( fp, "// idx_client_family_name\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(req[i].idx_client_family_name) );
		save_crypt_tab( fp, "// idx_client_mate_name\n" );
		save_crypt_tab( fp, "%ld,\n",
				(long)(req[i].idx_client_mate_name) );

		idx = trans_sex_kind_to_idx( req[i].client_sex );
		save_crypt_tab( fp, "// client_sex\n" );
		save_crypt_tab( fp, "%ld,\n", idx );

		idx = trans_sex_kind_to_idx( req[i].mnstr_sex );
		save_crypt_tab( fp, "// mnstr_sex\n" );
		save_crypt_tab( fp, "%ld,\n", idx );

		idx = trans_sex_kind_to_idx( req[i].rescue_trgt_sex );
		save_crypt_tab( fp, "// rescue_trgt_sex\n" );
		save_crypt_tab( fp, "%ld,\n", idx );

		idx = trans_sex_kind_to_idx( req[i].client_family_sex );
		save_crypt_tab( fp, "// client_family_sex\n" );
		save_crypt_tab( fp, "%ld,\n", idx );

		idx = trans_sex_kind_to_idx( req[i].client_mate_sex );
		save_crypt_tab( fp, "// client_mate_sex\n" );
		save_crypt_tab( fp, "%ld,\n", idx );

		idx = trans_mnstr_kind_to_idx( req[i].rescue_trgt_kind );
		save_crypt_tab( fp, "// rescue_trgt_kind\n" );
		save_crypt_tab( fp, "%ld,\n", idx );

		save_crypt_tab( fp, "// when_1\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(req[i].idx_when_1) );
		save_crypt_tab( fp, "// when_2\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(req[i].idx_when_2) );
		save_crypt_tab( fp, "// weapon\n" );
		save_crypt_tab( fp, "%ld,\n", (long)(req[i].idx_weapon) );

		set_save_crypt_tab( fp, -1 );
	}

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データのメンバーの統計のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_playing_report_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	mbr_t	**ls_mbr = get_ls_mbr();
	playing_report_t	*p;
	long	i;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// playing report of members\n" );

	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;
		if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			continue;

		save_crypt_tab( fp, "\n" );
		save_crypt_tab( fp, "// %s\n", ls_mbr[i]->name );
		save_crypt_tab( fp, "playing_report_member %ld = ", i );

		p = get_playing_report_mbr( i );
		if( !save_game_data_playing_report_ver_1(
				fp, ver, flg_txt, p ) ){
			return FALSE;
		}
	}

	return TRUE;
}

/***************************************************************
* ゲーム・データのパーティの統計のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_playing_report_party_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
)
{
	playing_report_t	*p;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;

	save_crypt_tab( fp, "\n" );
	save_crypt_tab( fp, "// playing report of party\n" );

	save_crypt_tab( fp, "playing_report_party = " );

	p = get_playing_report_party();
	if( !save_game_data_playing_report_ver_1( fp, ver, flg_txt, p ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ゲーム・データの統計のセーブ(バージョン 1)
* FILE *fp : ファイル
* const ver_t *ver : ファイルのバージョン
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	save_game_data_playing_report_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	playing_report_t *p
)
{
	long	max_idx;
	long	j;

	if( fp == NULL )
		return FALSE;
	if( ver == NULL )
		return FALSE;
	if( p == NULL )
		return FALSE;

	set_save_crypt_tab( fp, +1 );

	save_crypt_tab( fp, "// paying gold\n" );
	save_crypt_tab( fp, "%ld,\n", (long)(p->paying_gold) );

	save_crypt_tab( fp, "// staying inn\n" );
	set_save_crypt_tab( fp, +1 );
	max_idx = get_stay_inn_kind_trans_tab_max_n();
	for( j = 0; j < max_idx; j++ ){
		stay_inn_kind_t	kind;

		kind = trans_idx_to_stay_inn_kind( j );
		save_crypt_tab( fp, "%ld,\n",
				(long)(p->staying_inn[kind]) );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// wearing equip\n" );
	set_save_crypt_tab( fp, +1 );
	for( j = 0; j < EQUIP_KIND_MAX_N; j++ ){
		save_crypt_tab( fp, "%ld,\n",
				(long)(p->wearing_equip[j]) );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// making dam\n" );
	set_save_crypt_tab( fp, +1 );
	for( j = 0; j < RESI_KIND_MAX_N; j++ ){
		save_crypt_tab( fp, "%ld,\n",
				(long)(p->making_dam[j]) );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// made dam\n" );
	set_save_crypt_tab( fp, +1 );
	for( j = 0; j < RESI_KIND_MAX_N; j++ ){
		save_crypt_tab( fp, "%ld,\n",
				(long)(p->made_dam[j]) );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// using spell\n" );
	set_save_crypt_tab( fp, +1 );
	max_idx = get_spell_kind_trans_tab_max_n();
	for( j = 0; j < max_idx; j++ ){
		spell_kind_t	kind;

		kind = trans_idx_to_spell_kind( j );
		save_crypt_tab( fp, "// %s\n",
				get_spell_name( kind ) );
		save_crypt_tab( fp, "%ld,\n",
				(long)(p->using_spell[kind]) );
	}
	set_save_crypt_tab( fp, -1 );

	save_crypt_tab( fp, "// used spell\n" );
	set_save_crypt_tab( fp, +1 );
	max_idx = get_spell_kind_trans_tab_max_n();
	for( j = 0; j < max_idx; j++ ){
		spell_kind_t	kind;

		kind = trans_idx_to_spell_kind( j );
		save_crypt_tab( fp, "// %s\n",
				get_spell_name( kind ) );
		save_crypt_tab( fp, "%ld,\n",
				(long)(p->used_spell[kind]) );
	}
	set_save_crypt_tab( fp, -1 );

	set_save_crypt_tab( fp, -1 );

	return TRUE;
}

/***************************************************************
* ゲーム・データ・ファイルのタイトルを返す
* char *msg : タイトルの返す先
* long n : データ・スロット番号
* bool_t flg_txt : テキスト・モードか?
* return : すでにファイルが有るか?
***************************************************************/

bool_t	get_save_load_ttl(
	char *msg, long n,
	bool_t flg_txt, bool_t flg_replay
)
{
	static char	buf[BUF_LINE_LEN + 1];
	const char	str_auto[] = "AUTO";

	if( get_game_data_head_time( buf, n, flg_txt, flg_replay ) ){
		if( n == SAVE_N_AUTO )
			strncpy( buf, str_auto, str_len_std( str_auto ) );

		sn_printf( msg, MENU_MSG_MAX_BYTE,
				MSG_SAVE_LOAD_TTL_FMT, n, buf );

		return TRUE;
	} else {
		sn_printf( msg, MENU_MSG_MAX_BYTE,
				MSG_SAVE_LOAD_TTL_FMT, n,
				MSG_SAVE_LOAD_TTL_NULL );

		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ゲーム・データ・ファイルのセーブ日時を読み込む
* char *str : セーブ日時の返す先
* long n : データ・スロット番号
* bool_t flg_txt : テキスト・モードか?
* return : エラーが無かったか?
***************************************************************/

bool_t	get_game_data_head_time(
	char *str, long n,
	bool_t flg_txt, bool_t flg_replay
)
{
	FILE	*fp;
	char	*s;
	size_t	idx;
	bool_t	flg_pre_txt;

	if( str == NULL )
		return FALSE;

	if( flg_replay )
		fp = open_game_replay( 'r', n );
	else
		fp = open_game_data( 'r', n, flg_txt );
	if( fp == NULL )
		return FALSE;

	flg_pre_txt = g_flg_crypt_txt;
	g_flg_crypt_txt = TRUE;

	if( load_line( fp, FALSE ) == NULL )
		return FALSE;
	s = load_line( fp, FALSE );
	if( s == NULL )
		return FALSE;

	g_flg_crypt_txt = flg_pre_txt;

	str_nz_cpy( str, s, BUF_LINE_LEN );

	idx = strcspn( str, "\n\r" );
	if( idx >= 0 )
		str[idx] = '\0';

	return TRUE;
}
/***************************************************************
* メモリー・チェック
***************************************************************/

void	check_memory_gf_save_c( void )
{
}
