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
* $Id: gfile.h,v 1.29 2014/03/15 01:49:20 bowkenken Exp $
***************************************************************/

#ifndef	GFILE_H
#define	GFILE_H

/***************************************************************
* ファイル入出力
***************************************************************/

#include	"replay.h"
#include	"key-item.h"
#include	"key-item-prot.h"

#include	"win-kind.h"
#include	"joy-kind.h"

/***************************************************************
* ファイル名
***************************************************************/

#define	STR_FILE_NAME_GAME_RC	"lnlrc"
#define	STR_FILE_NAME_GAME_CONF	"lnl.conf"
#define	STR_FILE_NAME_TOWN_PTN	"town-ptn.xpm"
#define	STR_FILE_NAME_CRSR_PTN	"crsr-ptn.h"

#define	STR_DIR_NAME_GAME_DATA_SAVE	\
		STR_DIR_NAME_GAME STR_SLASH "save"
#define	STR_DIR_NAME_GAME_DATA_TXT	\
		STR_DIR_NAME_GAME_DATA_SAVE STR_SLASH "txt"
#define	STR_DIR_NAME_GAME_DATA_BIN	\
		STR_DIR_NAME_GAME_DATA_SAVE STR_SLASH "bin"
#define	STR_DIR_NAME_GAME_DATA_CNF	\
		STR_DIR_NAME_GAME_DATA_SAVE STR_SLASH "cnf"
#define	STR_DIR_NAME_GAME_DATA_REP	\
		STR_DIR_NAME_GAME_DATA_SAVE STR_SLASH "rep"
#define	STR_DIR_NAME_BUG_REPO	\
		STR_DIR_NAME_GAME STR_SLASH "bug-repo"
#define	STR_FILE_NAME_GAME_DATA_TXT	"save"
#define	STR_FILE_NAME_GAME_DATA_BIN	"save"
#define	STR_FILE_NAME_GAME_DATA_CNF	"conf"
#define	STR_FILE_NAME_GAME_DATA_REP	"rply"

#define	STR_FILE_NAME_BUG_REPO_TXT	"save-bug"
#define	STR_FILE_NAME_BUG_REPO_BIN	"save-bug"
#define	STR_FILE_NAME_BUG_REPO_CNF	"conf-bug"
#define	STR_FILE_NAME_BUG_REPO_REP	"rply-bug"

#define	STR_EXT_NAME_GAME_DATA_TXT	".txt"
#define	STR_EXT_NAME_GAME_DATA_BIN	".bin"
#define	STR_EXT_NAME_GAME_DATA_CNF	".txt"
#define	STR_EXT_NAME_GAME_DATA_REP	".txt"

#define	STR_EXT_NAME_BUG_REPO_TXT	".txt"
#define	STR_EXT_NAME_BUG_REPO_BIN	".bin"
#define	STR_EXT_NAME_BUG_REPO_CNF	".txt"
#define	STR_EXT_NAME_BUG_REPO_REP	".txt"

#if	defined( D_DOS ) || defined( D_MFC )
# define	STR_DIR_NAME_GAME	"_lnl"
#else
# define	STR_DIR_NAME_GAME	".lnl"
#endif

#define	STR_ENV_HOME	"HOME"
#define	STR_SLASH	"/"
#define	STR_DIR_NAME_CUR	"."
#define	STR_FILE_NAME_TMP	"tmp"

#define	STR_DIR_NAME_USR	"usr"
#define	STR_DIR_NAME_GAME_USR	\
		STR_DIR_NAME_GAME STR_SLASH STR_DIR_NAME_USR

#define	STR_DIR_NAME_BAK	"bak"
#define	STR_EXT_NAME_BAK_1	".%03ld"
#define	STR_EXT_NAME_BAK_2	".bak"
#define	STR_DIR_NAME_GAME_BAK	\
		STR_DIR_NAME_GAME STR_SLASH STR_DIR_NAME_BAK

#define	STR_DIR_NAME_OUT_MAP	"out"
#define	STR_FILE_NAME_OUT_MAP	"map"
#define	STR_EXT_NAME_OUT_MAP	".%03ld"
#define	STR_DIR_NAME_GAME_OUT_MAP	\
		STR_DIR_NAME_GAME STR_SLASH STR_DIR_NAME_OUT_MAP

#define	STR_CRSR_PTN_HEAD	"crsr_ptn_t"

/***************************************************************
* lex & parser
***************************************************************/

#define	BUF_LINE_LEN	1024
#define	MAX_TOKEN	10

/* セーブ・スロットの選択指定 */
#define	SAVE_N_SEL	-1
/* 自動セーブ・スロット */
#define	SAVE_N_AUTO	0
/* バグ・レポート用セーブ・スロット */
#define	SAVE_N_BUG_REPO	999

/* ファイル名の長さ */
#ifdef	D_IPHONE
# define	FILE_NAME_MAX_LEN	255
#else	/* D_IPHONE */
# define	FILE_NAME_MAX_LEN	127
#endif	/* D_IPHONE */

/* 字句解析のトークンの最大文字数 */
#define	TOKEN_MAX_LEN	4096

/* 字句解析のトークン */

typedef enum {
	RC_TOKEN_NULL = 0,
	RC_TOKEN_EOF = -1,	/* ファイル終端 */
	RC_TOKEN_NUM = 256,	/* 数値 */
	RC_TOKEN_ADD_OP,	/* '+', '-' */
	RC_TOKEN_EQ_OP,	/* '=' */
	RC_TOKEN_CHAR,	/* 文字 */
	RC_TOKEN_STR,	/* 文字列 */
	RC_TOKEN_ID,	/* 識別子 */
} rc_token_t;

/* 字句解析のスタック */

typedef union {
	long	n;	/* 数値 */
	long	c;	/* 文字 */
	char	str[TOKEN_MAX_LEN + 1];	/* 文字列 */
} rc_union_t;

/***************************************************************
* グローバル変数
***************************************************************/

/* ファイル名のグローバル変数 */

EXTERN char	dir_name_game[FILE_NAME_MAX_LEN + 1];
EXTERN char	dir_name_usr[FILE_NAME_MAX_LEN + 1];
EXTERN char	dir_name_game_data_txt[FILE_NAME_MAX_LEN + 1];
EXTERN char	dir_name_game_data_bin[FILE_NAME_MAX_LEN + 1];
EXTERN char	dir_name_game_data_cnf[FILE_NAME_MAX_LEN + 1];
EXTERN char	dir_name_game_data_rep[FILE_NAME_MAX_LEN + 1];
EXTERN char	dir_name_bug_repo[FILE_NAME_MAX_LEN + 1];
EXTERN char	path_name_game_conf[FILE_NAME_MAX_LEN + 1];
EXTERN char	path_name_town_ptn[FILE_NAME_MAX_LEN + 1];
EXTERN char	path_name_crsr_ptn[FILE_NAME_MAX_LEN + 1];

/***************************************************************/

EXTERN char	g_rc_lex_file_name[FILE_NAME_MAX_LEN + 1];
EXTERN long	g_rc_lex_line;
EXTERN bool_t	g_flg_rc_lex_err;
EXTERN long	g_tab_lev;
EXTERN long	g_randm_crypt_seed;
EXTERN unsigned char	g_crypt_sum;
EXTERN long	g_un_c;
EXTERN rc_token_t	g_un_token;
EXTERN rc_union_t	g_un_union;
EXTERN bool_t	g_flg_crypt_txt;

EXTERN long	g_rc_lex_num_mode;

EXTERN curs_attr_n_t	g_crnt_attr_n;

EXTERN long	g_game_data_save_n;
EXTERN replay_kind_t	g_replay_kind_cur;
EXTERN long	g_load_slot_n;
EXTERN bool_t	g_flg_exit_shop;

#endif	/* GFILE_H */
