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
* $Id: gfile.h,v 1.29 2014/03/15 01:49:20 bowkenken Exp $
***************************************************************/

#ifndef	GFILE_H
#define	GFILE_H

/***************************************************************
* �ե�����������
***************************************************************/

#include	"replay.h"
#include	"key-item.h"
#include	"key-item-prot.h"

#include	"win-kind.h"
#include	"joy-kind.h"

/***************************************************************
* �ե�����̾
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

/* �����֡�����åȤ�������� */
#define	SAVE_N_SEL	-1
/* ��ư�����֡�����å� */
#define	SAVE_N_AUTO	0
/* �Х�����ݡ����ѥ����֡�����å� */
#define	SAVE_N_BUG_REPO	999

/* �ե�����̾��Ĺ�� */
#ifdef	D_IPHONE
# define	FILE_NAME_MAX_LEN	255
#else	/* D_IPHONE */
# define	FILE_NAME_MAX_LEN	127
#endif	/* D_IPHONE */

/* ������ϤΥȡ�����κ���ʸ���� */
#define	TOKEN_MAX_LEN	4096

/* ������ϤΥȡ����� */

typedef enum {
	RC_TOKEN_NULL = 0,
	RC_TOKEN_EOF = -1,	/* �ե����뽪ü */
	RC_TOKEN_NUM = 256,	/* ���� */
	RC_TOKEN_ADD_OP,	/* '+', '-' */
	RC_TOKEN_EQ_OP,	/* '=' */
	RC_TOKEN_CHAR,	/* ʸ�� */
	RC_TOKEN_STR,	/* ʸ���� */
	RC_TOKEN_ID,	/* ���̻� */
} rc_token_t;

/* ������ϤΥ����å� */

typedef union {
	long	n;	/* ���� */
	long	c;	/* ʸ�� */
	char	str[TOKEN_MAX_LEN + 1];	/* ʸ���� */
} rc_union_t;

/***************************************************************
* �����Х��ѿ�
***************************************************************/

/* �ե�����̾�Υ����Х��ѿ� */

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
