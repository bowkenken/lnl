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
* $Id: fx.h,v 1.61 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	FX_H
#define	FX_H

/***************************************************************
* ���ե�����
***************************************************************/

#include	"abl-kind.h"

/***************************************************************
* ���ե����Ȥλ�³�������
***************************************************************/

/* Ⱦ�ʵ� */
#define	FX_TURN_INFINITE_N	(-1)

/***************************************************************
* ���ե����Ȥμ���
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
* HP �� MP �β���
***************************************************************/

typedef struct {
	long	count;
	long	turn;
	rate_t	rate;
	long	n;
} cure_t;

/***************************************************************
* ��ʢ��
***************************************************************/

typedef struct {
	/* ���ߤ�Ψ */
	rate_t	rate;
	/* ��ʢ����Ψ */
	rate_t	full_rate;

	/* 1��������ξò��� */
	long	digest_p_day;
	/* �ò��� */
	long	digest_n;

	/* ��ʢ�ˤʤ�Ψ */
	rate_t	hungry_rate;
	/* ���䤹��Ψ */
	rate_t	starvation_rate;
} stomach_t;

/***************************************************************
* �˥������¸��
***************************************************************/

typedef struct {
	/* �˥�����η���ǻ�� */
	rate_t	rate;
	/* �˥������������ */
	rate_t	poisoning_rate;
	/* ����Ψ */
	rate_t	lost_rate;
} nicotine_t;

/***************************************************************
* ��μ���
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
* ˾��
***************************************************************/

/* ˾�ߤμ��� */
typedef enum {
	WISH_KIND_NULL,
	WISH_KIND_ARMAGEDDON,
	WISH_KIND_CURE_HP,
	WISH_KIND_CURE_MP,
	WISH_KIND_RESURRECTION,
	WISH_KIND_ARTIFACT,
	WISH_KIND_MAX_N,
} wish_kind_t;

/* ����μ��� */
typedef enum {
	WISH_LEVEL_NULL,
	WISH_LEVEL_ARMAGEDDON,
	WISH_LEVEL_DAEMON,
	WISH_LEVEL_DJINNI,
	WISH_LEVEL_GOD,
	WISH_LEVEL_MAX_N,
} wish_level_t;

/***************************************************************
* ���ե�����
***************************************************************/

typedef struct fx {
	/* ��� */
	struct fx	*next, *prev;

	/* ���� */
	fx_kind_t	kind;

	/* �Ĥ꥿����� */
	long	turn;

	/* �Ťͳݤ��� */
	long	n;

	/* �оݥ���顢�Ӿ������ */
	struct chr_t	*chr, *cast_chr;

	/* ������¦��ǽ���� */
	abl_kind_t	abl_kind;
} fx_t;

/***************************************************************
* ����
***************************************************************/

/* �����κ���Ⱦ�� */

#define	BLAST_MAX_X	64
#define	BLAST_MAX_Y	64

/* �����μ��� */

typedef enum {
	BLAST_KIND_STD,
	BLAST_KIND_NINJA_CRTCL,
	BLAST_KIND_WORD_OF_DESTRUCTION,
	BLAST_KIND_MAX_N
} blast_kind_t;

/* �����ǡ��� */

typedef struct {
	/* ľ�� */
	long	xl, yl;

	/* Ⱦ�� */
	long	xr, yr;

	/* Ʃ��ʸ�� */
	long	transmit_chr;

	/* �ѥ����� */
	char	ptn[BLAST_MAX_Y + 1][BLAST_MAX_X + 1];
} blast_t;

#endif	/* FX_H */

