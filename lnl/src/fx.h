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
* $Id: fx.h,v 1.61 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	FX_H
#define	FX_H

/***************************************************************
* エフェクト
***************************************************************/

#include	"abl-kind.h"

/***************************************************************
* エフェクトの持続ターン数
***************************************************************/

/* 半永久 */
#define	FX_TURN_INFINITE_N	(-1)

/***************************************************************
* エフェクトの種類
***************************************************************/

typedef enum {
	FX_KIND_NULL,
	FX_KIND_STONE,
	FX_KIND_PARALYZE,
	FX_KIND_POISON,
	FX_KIND_CONFUSION,
	FX_KIND_BLIND,
	FX_KIND_SLEEP,
	FX_KIND_SILENCE,
	FX_KIND_FEAR,
	FX_KIND_HALLUCINATION,
	FX_KIND_CHARM,
	FX_KIND_FLY,
	FX_KIND_FAINT,
	FX_KIND_DRUNK,
	FX_KIND_VANISH,
	FX_KIND_IRON_BODY,
	FX_KIND_PASSWALL,
	FX_KIND_POLYMORPH,
	FX_KIND_SENSE_INVISIBLE,
	FX_KIND_WEAK_HEAT,
	FX_KIND_WEAK_COLD,
	FX_KIND_WEAK_MIND,
	FX_KIND_WEAK_ACID,
	FX_KIND_WEAK_ELEC,
	FX_KIND_WEAK_POIS,
	FX_KIND_RESI_KNOC,
	FX_KIND_RESI_SLAS,
	FX_KIND_RESI_STIN,
	FX_KIND_RESI_HEAT,
	FX_KIND_RESI_COLD,
	FX_KIND_RESI_MIND,
	FX_KIND_RESI_ACID,
	FX_KIND_RESI_ELEC,
	FX_KIND_RESI_POIS,
	FX_KIND_SHARPNESS,
	FX_KIND_DULLNESS,
	FX_KIND_STRENGTH,
	FX_KIND_WEAKNESS,
	FX_KIND_QUICKNESS,
	FX_KIND_SLOWNESS,
	FX_KIND_BRAINY,
	FX_KIND_BRAINLESS,
	FX_KIND_WISE,
	FX_KIND_FOOLISH,
	FX_KIND_ATTRACTIVE,
	FX_KIND_UNATTRACTIVE,
	FX_KIND_POW_UP_HP,
	FX_KIND_MAGIC_SHIELD,
	FX_KIND_MAGE_ARMOR,
	FX_KIND_COUNTER_MAGIC,
	FX_KIND_SUBSTITUTE,
	FX_KIND_BURNING_HANDS,
	FX_KIND_RALLY,
	FX_KIND_IRON_MAN,
	FX_KIND_MIND_READING,
	FX_KIND_SPEED_UP,
	FX_KIND_SPEED_DOWN,
	FX_KIND_BLESS,
	FX_KIND_STORE_LIGHT,
	FX_KIND_MAX_N,
} fx_kind_t;

/***************************************************************
* HP や MP の回復
***************************************************************/

typedef struct {
	long	count;
	long	turn;
	rate_t	rate;
	long	n;
} cure_t;

/***************************************************************
* 空腹度
***************************************************************/

typedef struct {
	/* 現在の率 */
	rate_t	rate;
	/* 満腹時の率 */
	rate_t	full_rate;

	/* 1日あたりの消化数 */
	long	digest_p_day;
	/* 消化数 */
	long	digest_n;

	/* 空腹になる率 */
	rate_t	hungry_rate;
	/* 気絶する率 */
	rate_t	starvation_rate;
} stomach_t;

/***************************************************************
* ニコチン依存度
***************************************************************/

typedef struct {
	/* ニコチンの血中濃度 */
	rate_t	rate;
	/* ニコチンの中毒度 */
	rate_t	poisoning_rate;
	/* ロスト率 */
	rate_t	lost_rate;
} nicotine_t;

/***************************************************************
* 酒の種類
***************************************************************/

typedef enum {
	LIQUOR_KIND_RED_WINE,
	LIQUOR_KIND_WHITE_WINE,
	LIQUOR_KIND_ROSE_WINE,
	LIQUOR_KIND_ALE,
	LIQUOR_KIND_BRANDY,
	LIQUOR_KIND_RUM,
	LIQUOR_KIND_MAX_N
} liquor_kind_t;

/***************************************************************
* 望み
***************************************************************/

/* 望みの種類 */
typedef enum {
	WISH_KIND_NULL,
	WISH_KIND_ARMAGEDDON,
	WISH_KIND_CURE_HP,
	WISH_KIND_CURE_MP,
	WISH_KIND_RESURRECTION,
	WISH_KIND_ARTIFACT,
	WISH_KIND_MAX_N,
} wish_kind_t;

/* 魔神の種類 */
typedef enum {
	WISH_LEVEL_NULL,
	WISH_LEVEL_ARMAGEDDON,
	WISH_LEVEL_DAEMON,
	WISH_LEVEL_DJINNI,
	WISH_LEVEL_GOD,
	WISH_LEVEL_MAX_N,
} wish_level_t;

/***************************************************************
* エフェクト
***************************************************************/

typedef struct fx {
	/* リンク */
	struct fx	*next, *prev;

	/* 種類 */
	fx_kind_t	kind;

	/* 残りターン数 */
	long	turn;

	/* 重ね掛け数 */
	long	n;

	/* 対象キャラ、詠唱キャラ */
	struct chr_t	*chr, *cast_chr;

	/* かけた側の能力値 */
	abl_kind_t	abl_kind;
} fx_t;

/***************************************************************
* 爆風
***************************************************************/

/* 爆風の最大半径 */

#define	BLAST_MAX_X	64
#define	BLAST_MAX_Y	64

/* 爆風の種類 */

typedef enum {
	BLAST_KIND_STD,
	BLAST_KIND_NINJA_CRTCL,
	BLAST_KIND_WORD_OF_DESTRUCTION,
	BLAST_KIND_MAX_N
} blast_kind_t;

/* 爆風データ */

typedef struct {
	/* 直径 */
	long	xl, yl;

	/* 半径 */
	long	xr, yr;

	/* 透過文字 */
	long	transmit_chr;

	/* パターン */
	char	ptn[BLAST_MAX_Y + 1][BLAST_MAX_X + 1];
} blast_t;

#endif	/* FX_H */

