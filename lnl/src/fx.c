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
* $Id: fx.c,v 1.270 2014/03/12 19:57:13 bowkenken Exp $
***************************************************************/

/***************************************************************
* ���ե�����
***************************************************************/

#define	FX_C
#include	"inc.h"

/***************************************************************/

/* ���ե����ȡ��ǡ����κ���� */

#define	FX_MAX_N	(LS_MBR_MAX_N * 16)

/***************************************************************
* ���ե����Ȥθ��̤ζ���
***************************************************************/

#define	RESURRECTION_MIN_RATE	30
#define	RESURRECTION_MAX_RATE	90

#define	MAGIC_SHIELD_ADD_DEF_RATE	100
#define	MAGIC_SHIELD_MAX_N	1

#define	MAGE_ARMOR_ADD_AC_RATE	40
#define	MAGE_ARMOR_MAX_N	3

#define	SUBSTITUTE_ADD_DEF_RATE	40
#define	SUBSTITUTE_ADD_AC_RATE	40
#define	SUBSTITUTE_MAX_N	2

#define	BURNING_HANDS_ADD_HIT_RATE	40
#define	BURNING_HANDS_ADD_DAM_RATE	40
#define	BURNING_HANDS_MAX_N	2

#define	RALLY_ADD_HIT_RATE	40
#define	RALLY_ADD_DEF_RATE	40
#define	RALLY_MAX_N	2

#define	IRON_MAN_ADD_DAM_RATE	40
#define	IRON_MAN_ADD_AC_RATE	40
#define	IRON_MAN_MAX_N	2

#define	MIND_READING_ADD_WPN_CRTCL_RATE	40
#define	MIND_READING_ADD_ARMOR_CRTCL_RATE	40
#define	MIND_READING_MAX_N	2

/***************************************************************
* ���ե����Ȥ�ʿ�ѻ�³�������
***************************************************************/

#define	FX_AVE_TURN_STONE	FX_TURN_INFINITE_N
#define	FX_AVE_TURN_PARALYZE	2
#define	FX_AVE_TURN_POISON	(POISON_MAX_N * FX_AVE_TURN_POISON_DEC)
#define	FX_AVE_TURN_CONFUSION	8
#define	FX_AVE_TURN_BLIND	128
#define	FX_AVE_TURN_SLEEP	16
#define	FX_AVE_TURN_SILENCE	8
#define	FX_AVE_TURN_FEAR	8
#define	FX_AVE_TURN_HALLUCINATION	(FEAR_MAX_N * FX_AVE_TURN_FEAR_DEC)
#define	FX_AVE_TURN_CHARM	8
#define	FX_AVE_TURN_FLY	128
#define	FX_AVE_TURN_VANISH	128
#define	FX_AVE_TURN_IRON_BODY	16
#define	FX_AVE_TURN_PASSWALL	128
#define	FX_AVE_TURN_POLYMORPH	8
#define	FX_AVE_TURN_SENSE_INVISIBLE	128

#define	FX_AVE_TURN_MAGIC_SHIELD	64
#define	FX_AVE_TURN_MAGE_ARMOR	64
#define	FX_AVE_TURN_COUNTER_MAGIC	64

#define	FX_AVE_TURN_SUBSTITUTE	32
#define	FX_AVE_TURN_BURNING_HANDS	32
#define	FX_AVE_TURN_RALLY	32
#define	FX_AVE_TURN_IRON_MAN	32
#define	FX_AVE_TURN_MIND_READING	32

#define	FX_AVE_TURN_POW_UP_HP	64
#define	FX_AVE_TURN_POW_UP_ABL	64
#define	FX_AVE_TURN_POW_DOWN_ABL	64
#define	FX_AVE_TURN_POW_UP_RESI	64
#define	FX_AVE_TURN_SPEED_UP	128
#define	FX_AVE_TURN_SPEED_DOWN	128

#define	FX_AVE_TURN_STORE_LIGHT	FX_TURN_INFINITE_N
#define	FX_AVE_TURN_DARKVISION	128

#define	FX_AVE_TURN_TELEPORT_PARTY	10
#define	FX_AVE_TURN_RECALL	20

#define	FX_AVE_TURN_BLESS	64

#define	FX_AVE_TURN_FAINT	8
#define	FX_TURN_DRUNK	512

/***************************************************************
* ��������
***************************************************************/

#define	NATURAL_CURE_HP_TURN	(30 * TURN_PER_MINUTE)
#define	NATURAL_CURE_HP_RATE	((rate_t)5)
#define	NATURAL_CURE_HP_RATE_NOT_WARE	((rate_t)7)
#define	NATURAL_CURE_HP_MAX	10
#define	NATURAL_CURE_HP_MAX_NOT_WARE	14
#define	NATURAL_CURE_HP_MON_MUL	1
#define	NATURAL_CURE_HP_MON_ADD	0

#define	NATURAL_CURE_MP_TURN	(60 * TURN_PER_MINUTE)
#define	NATURAL_CURE_MP_RATE	((rate_t)5)
#define	NATURAL_CURE_MP_RATE_NOT_WARE	((rate_t)7)
#define	NATURAL_CURE_MP_MAX	10
#define	NATURAL_CURE_MP_MAX_NOT_WARE	14
#define	NATURAL_CURE_MP_MON_MUL	1
#define	NATURAL_CURE_MP_MON_ADD	0

#define	NATURAL_CURE_EXP_TURN	(30 * TURN_PER_MINUTE)

/***************************************************************
* ����ˤ�����
***************************************************************/

/* SPELL_MP_DD */
#define	CURE_HP_LIGHT_RATE	25

/* SPELL_MP_CC */
#define	CURE_HP_MODERATE_RATE	50

/* SPELL_MP_BB */
#define	CURE_HP_SERIOUS_RATE	75

/* ����ǥåɤؤε���θ��� */
#define	CURE_HP_UNDEAD_RATE	50
#define	DISPEL_UNDEAD_RATE	((rate_t)100)

/***************************************************************
* ��ʸ
***************************************************************/

#define	FX_TRANSFER_MP_RATE	((rate_t)80)

/* �˲��μ�ʸ�������ŷ���Ψ */
#define	WORD_OF_DESTRUCTION_WALL_RATE	30

/* �Ǥǲ���������� HP �����뤫? */
#define	FX_AVE_TURN_POISON_DEC	16
/* �Ǥˤ�� HP ���� */
#define	POISON_DEC_RATE	((rate_t)1)
#define	POISON_DEC_MAX_RATE	((rate_t)20)
#define	POISON_MAX_N	(POISON_DEC_MAX_RATE / POISON_DEC_RATE)

/* ���ݤǲ���������� MP �����뤫? */
#define	FX_AVE_TURN_FEAR_DEC	4
/* ���ݤˤ�� MP ���� */
#define	FEAR_DEC_RATE	((rate_t)5)
#define	FEAR_DEC_MAX_RATE	((rate_t)20)
#define	FEAR_MAX_N	(FEAR_DEC_MAX_RATE / FEAR_DEC_RATE)

/* �줤������� */
#define	SOBER_AVE_TURN	12
#define	SOBER_SUB_RATE	1

/* ��ʢ */
#define	HUNGRY_FEEL_RATE	10
#define	STARVATION_FEEL_RATE	10
#define	FAINT_FEEL_RATE	20

/* ����Ѥι��� */
#define	FX_WEAK_TURN	4
#define	FX_WEAK_RATE	((rate_t)40)

/* ���ͤν��� */
#define	ADD_RESI_MIN_N	-5
#define	ADD_RESI_MAX_N	+5

/* ������������׼�ʸ�������� */
#define	FX_STORE_LIGHT_ADD_N	10

/* ˾�ߤ���� */
#define	WISH_PRICE_EXP	(5000)
#define	WISH_PRICE_GOLD	((gold_t)10000)
#define	WISH_PRICE_CONTRIBUTION	((gold_t)20000)

/* ���Τˤ����� */
#define	SONG_CURE_HP_TURN	4
#define	SONG_CURE_HP_RATE	((rate_t)1)
#define	SONG_CURE_MP_TURN	16
#define	SONG_CURE_MP_RATE	((rate_t)1)

/***************************************************************
* ����
***************************************************************/

/* ����������εۤ������ʤ��ܿ� */
#define	SMOKING_PER_A_DAY	10

/* ����ζ��Ǿɾ� */
#define	TOBACCO_ABSTAIN_AVE_TURN	\
		(TURN_DAYTIME / SMOKING_PER_A_DAY / 10)
#define	TOBACCO_ABSTAIN_SUB_RATE	2

/* �˥�����������٤��Ѳ� */
#define	TOBACCO_POISONING_AVE_TURN	1
#define	TOBACCO_POISONING_ADD_RATE	1

/* �˥�����������٤β��� */
#define	TOBACCO_CURE_POISONING_AVE_TURN	(1 * TURN_PER_HOUR)
#define	TOBACCO_CURE_POISONING_SUB_RATE	1

/* �ۤ������ʤ륿���� */
#define	TOBACCO_FEEL_AVE_TURN	10
#define	TOBACCO_FEEL_MAX_RATE	50

/* �˥�����η���ǻ�٤��Ѳ� */
#define	ADD_NICOTINE_RATE_PER_TURN	\
		(_100_PERCENT / (5 * TURN_PER_MINUTE) + 1)

/* ����Ψ���Ѳ� */
#define	INC_NICOTINE_LOST_RATE_PER_DAY	((rate_t)100)
#define	INC_NICOTINE_LOST_RATE_POISONING_RATE	((rate_t)80)

/***************************************************************
* �����ࡦ�ƥ�ݡ���
***************************************************************/

#define	RANDM_TELEPORT_RATE	1
#define	RANDM_TELEPORT_PARTY_RATE	1

/***************************************************************
* õ��
***************************************************************/

#define	FX_DETECT_ITEM_R	(MAP_MAX_X / 3)
#define	FX_DETECT_DOOR_R	(MAP_MAX_X / 3)
#define	FX_DETECT_TRAP_R	(MAP_MAX_X / 3)

/***************************************************************
* ǽ���ͤν���
***************************************************************/

#define	FX_ABL_LEV_POW_UP_N	(+2)
#define	FX_ABL_LEV_POW_DOWN_N	(-1)
#define	FX_HP_LEV_POW_UP_N	(+2)

/***************************************************************
* �����ࡦ�����ƥ��ե�����
***************************************************************/

/* HP �ɥ쥤��εۼ�Ψ */
#define	WPN_RANDM_ART_DRAIN_HP_RATE	((rate_t)10)
/* MP �ɥ쥤��εۼ�Ψ */
#define	WPN_RANDM_ART_DRAIN_MP_RATE	((rate_t)5)
/* EXP �ɥ쥤��εۼ�Ψ */
#define	WPN_RANDM_ART_DRAIN_EXP_RATE	((rate_t)1)

/* HP �ҡ���󥰤β���Ψ */
#define	ARMOR_RANDM_ART_HEALING_HP_RATE	((rate_t)200)
/* MP �ҡ���󥰤β���Ψ */
#define	ARMOR_RANDM_ART_HEALING_MP_RATE	((rate_t)200)
/* EXP �ҡ���󥰤β���Ψ (max exp ���Ф���) */
#define	ARMOR_RANDM_ART_HEALING_EXP_RATE	((rate_t)10)

/***************************************************************
* ����¾
***************************************************************/

/* ��μ����μ�ʸ */
#define	DEATH_SPELL_RATE	30

/* �����β��������� */
#define	FX_REMOVE_CURSE_DIFFICULTY	4

/* ��ʡ */
#define	FX_BLESS_ADD_RATE	20

/* ��ư®�٤ν��� */
#define	MOVE_MIN_N	4
#define	MOVE_MAX_N	4

/***************************************************************
* ��ζ���
***************************************************************/

static short	liquor_proof[LIQUOR_KIND_MAX_N] = {
	20,	/* LIQUOR_KIND_RED_WINE, */
	20,	/* LIQUOR_KIND WHITE_WINE, */
	20,	/* LIQUOR_KIND_ROSE_WINE, */
	30,	/* LIQUOR_KIND_ALE, */
	30,	/* LIQUOR_KIND_BRANDY, */
	30,	/* LIQUOR_KIND_RUM, */
};
check_memory_def( check_memory_fx_c_liquor_proof )

/***************************************************************
* ����ʪ�Υ�å�����
***************************************************************/

static n_msg_t	drink_n_msg_ls[] = {
	N_MSG_FX_DRINK_A00,
	N_MSG_FX_DRINK_A01,
	N_MSG_FX_DRINK_A02,
	N_MSG_FX_DRINK_A03,
	N_MSG_FX_DRINK_A04,
	N_MSG_FX_DRINK_A05,
	N_MSG_FX_DRINK_B00,
	N_MSG_NULL,
};
check_memory_def( check_memory_fx_c_drink_n_msg_ls )

/***************************************************************
* ����ʪ�Υ�å�����
***************************************************************/

static n_msg_t	eat_food_n_msg_ls[] = {
	N_MSG_FX_EAT_FOOD_A00,
	N_MSG_FX_EAT_FOOD_A01,
	N_MSG_FX_EAT_FOOD_A02,
	N_MSG_FX_EAT_FOOD_A03,
	N_MSG_FX_EAT_FOOD_A04,
	N_MSG_FX_EAT_FOOD_A05,
	N_MSG_FX_EAT_FOOD_A06,
	N_MSG_FX_EAT_FOOD_A07,
	N_MSG_FX_EAT_FOOD_A08,
	N_MSG_FX_EAT_FOOD_B00,
	N_MSG_FX_EAT_FOOD_B01,
	N_MSG_FX_EAT_FOOD_B02,
	N_MSG_NULL,
};
check_memory_def( check_memory_fx_c_eat_food_n_msg_ls )

/***************************************************************
* ���ե����ȤΥǡ���
***************************************************************/

static fx_t	fx_buf[FX_MAX_N];
check_memory_def( check_memory_fx_c_fx_buf )
static fx_t	fx_free;
check_memory_def( check_memory_fx_c_fx_free )

/***************************************************************
* �����Υǡ���
***************************************************************/

static blast_t	g_blast_std = {
	0, 0, 0, 0,
	' ',
	{
		"    **    ",
		"  ******  ",
		"**********",
		"  ******  ",
		"    **    ",
		"",
	},
};
check_memory_def( check_memory_fx_c_g_blast_std )

/*
 * �� is NOT the Hakenkreuz.
 * It's a Manji.
 * The Manji is *HOLY SYMBOL*.
 * The Manji is symbol of temple in japan.
 * And it mean Ninja too.
 * The kubi-kiri mean a neck chop.
 */

static blast_t	g_blast_ninja_crtcl = {
	0, 0, 0, 0,
	'@',
	{
		"  --     ",
		"    |  | ",
		"  -- --  ",
		" |  |    ",
		"     --  ",
		"KUBI KIRI",
	},
};
check_memory_def( check_memory_fx_c_g_blast_ninja_crtcl )

static blast_t	g_blast_destruction = {
	0, 0, 0, 0,
	' ',
	{
		"                ******                ",
		"           ****************           ",
		"       ************************       ",
		"     ****************************     ",
		"   ********************************   ",
		"  **********************************  ",
		" ************************************ ",
		" ************************************ ",
		"**************************************",
		"**************************************",
		"**************************************",
		" ************************************ ",
		" ************************************ ",
		"  **********************************  ",
		"   ********************************   ",
		"     ****************************     ",
		"       ************************       ",
		"           ****************           ",
		"                ******                ",
		"",
	},
};
check_memory_def( check_memory_fx_c_g_blast_destruction )

/***************************************************************
* ���Τˤ�뽤��
***************************************************************/

modifier_t	g_modifier_song_mbr;
check_memory_def( check_memory_fx_c_g_modifier_song_mbr )
modifier_t	g_modifier_song_mnstr;
check_memory_def( check_memory_fx_c_g_modifier_song_mnstr )
modifier_t	g_modifier_song_pet;
check_memory_def( check_memory_fx_c_g_modifier_song_pet )

/***************************************************************
* ��˥塼
***************************************************************/

#include	"fx-menu-tab.h"

/* ���򤵤줿�� */
item_t	*g_sel_bone;
check_memory_def( check_memory_fx_c_g_sel_bone )

/* ���򤵤줿˾�� */
wish_kind_t	g_sel_wish;
check_memory_def( check_memory_fx_c_g_sel_wish )

/***************************************************************
* ���ե����Ȥν����
***************************************************************/

void	init_fx( void )
{
	long	i;

	fx_free.next = &fx_buf[0];
	fx_buf[0].prev = &fx_free;
	fx_buf[0].next = &fx_buf[1];
	for( i = 1; i < FX_MAX_N - 1; i++ ){
		fx_buf[i].prev = &fx_buf[i - 1];
		fx_buf[i].next = &fx_buf[i + 1];
	}
	fx_buf[i].prev = &fx_buf[i - 1];
	fx_buf[i].next = &fx_free;
	fx_free.prev = &fx_buf[i];

	reset_modifier_all_song();
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_fx( void )
{
}

/***************************************************************
* ���ե����Ȥθ��̤λ�³�������������å�
***************************************************************/

void	inc_turn_all_fx( void )
{
	party_t	*pty;
	pet_t	**pet;
	mnstr_t	*mns_head, *mns_p, *mns_pp;
	long	i;

	/* ���� */

	reset_modifier_all_song();

	pty = get_party();
	for( i = 0; i < MBR_MAX_N; i++ ){
		set_modifier_all_song( pty->mbr[i] );
	}

	pet = get_party_pet();
	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet[i] == NULL )
			continue;

		set_modifier_all_song( pet[i] );
	}

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next->next; mns_p != NULL;
			mns_p = mns_p->next ){
		mns_pp = mns_p->prev;
		if( mns_pp == mns_head )
			break;

		set_modifier_all_song( mns_pp );
	}

	/* �ƥ��С��Υ��ե����Ȥμ¹� */

	dec_turn_fx_all_mbr( 1 );
	for( i = 0; i < MBR_MAX_N; i++ ){
		mbr_t	*mbr;

		mbr = pty->mbr[i];

		if( chk_flg_or( mbr->stat, FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD ) ){
			continue;
		}

		/* HP �μ������� */
		natural_cure_hp_chr( mbr );
		/* HP �β������� */
		modifier_cure_hp_chr( mbr );

		/* MP �μ������� */
		natural_cure_mp_chr( mbr );
		/* MP �β������� */
		modifier_cure_mp_chr( mbr );

		/* �и��ͤμ������� */
		natural_cure_exp_chr( mbr );

		/* ��ä����ν��� */
		sober( mbr );

		/* ����ʪ��ò����� */
		digest( mbr );

		/* ���� */
		inc_turn_smoke( mbr );

		/* ����ζ��Ǿɾ� */
		abstain( mbr );

		/* ���ɤ��ʤ� */
		fraternize( mbr );

		/* �Ż�ǽ�ϸ��� */
		dec_infra_vision( mbr );

		/* �ƥ�ݡ��� */
		randm_teleport( mbr );
		randm_teleport_party( mbr );

		exec_all_fx( mbr );
	}

	/* �ƥڥåȤΥ��ե����Ȥμ¹� */

	dec_turn_fx_all_pet( 1 );
	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet[i] == NULL )
			continue;

		if( chk_flg_or( pet[i]->stat, FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD ) ){
			continue;
		}

		/* HP �μ������� */
		natural_cure_hp_chr( pet[i] );
		/* HP �β������� */
		modifier_cure_hp_chr( pet[i] );

		/* MP �μ������� */
		natural_cure_mp_chr( pet[i] );
		/* MP �β������� */
		modifier_cure_mp_chr( pet[i] );

		/* �и��ͤμ������� */
		natural_cure_exp_chr( pet[i] );

		/* ��ä����ν��� */
		sober( pet[i] );

		/* ����ʪ��ò����� */
		digest( pet[i] );

		/* ���� */
		inc_turn_smoke( pet[i] );

		/* ����ζ��Ǿɾ� */
		abstain( pet[i] );

		/* ���ɤ��ʤ� */
		fraternize( pet[i] );

		/* �Ż�ǽ�ϸ��� */
		dec_infra_vision( pet[i] );

		/* �ƥ�ݡ��� */
		randm_teleport( pet[i] );
		randm_teleport_party( pet[i] );

		exec_all_fx( pet[i] );
	}

	/* �ƥ�󥹥����Υ��ե����Ȥμ¹� */

	dec_turn_fx_all_mnstr( 1 );
	for( mns_p = mns_head->next->next; mns_p != NULL;
			mns_p = mns_p->next ){
		mns_pp = mns_p->prev;
		if( mns_pp == mns_head )
			break;

		/* ��ä����ν��� */
		sober( mns_pp );

		/* ����ζ��Ǿɾ� */
		abstain( mns_pp );

		/* �Ż�ǽ�ϸ��� */
		dec_infra_vision( mns_pp );

		/* �ƥ�ݡ��� */
		randm_teleport( mns_pp );

		exec_all_fx( mns_pp );
	}
}

/***************************************************************
* ������Υ��ե����Ȥθ���
***************************************************************/

void	inc_day_all_fx( void )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		inc_day_smoke( pty->mbr[i] );
		pty->mbr[i]->work.flg_can_wish = TRUE;
	}
}

/***************************************************************
* HP �μ�������
* chr_t *chr : ����饯��
***************************************************************/

void	natural_cure_hp_chr( chr_t *chr )
{
	fx_t	*fx;
	bool_t	flg_wear;
	rate_t	rate;
	long	n, max, mon;

	if( chr == NULL )
		return;
	if( (get_turn() % NATURAL_CURE_HP_TURN) != 0 )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	/* �Ǥˤ�������Ƥ�����ϲ������ʤ� */
	fx = srch_fx( &(chr->fx), FX_KIND_POISON );
	if( fx != NULL )
		return;

	/* ������æ���Ȳ������ᤤ */

	flg_wear = chk_wear_armor( chr );
	if( flg_wear )
		rate = NATURAL_CURE_HP_RATE;
	else
		rate = NATURAL_CURE_HP_RATE_NOT_WARE;

	/* �����̤κ����ͥ����å� */

	max = calc_max_hp( chr );
	n = (max * rate) / _100_PERCENT;
	if( n < 1 )
		n = 1;
	if( flg_wear ){
		if( n > NATURAL_CURE_HP_MAX )
			n = NATURAL_CURE_HP_MAX;
	} else {
		if( n > NATURAL_CURE_HP_MAX_NOT_WARE )
			n = NATURAL_CURE_HP_MAX_NOT_WARE;
	}

	/* ��󥯤β����� */

	mon = get_lev( chr, ABL_KIND_MON );
	mon *= NATURAL_CURE_HP_MON_MUL;
	mon += NATURAL_CURE_HP_MON_ADD;
	n += mon;

	/* �����ࡦ�����ƥ��ե����ȤΥҡ���� */

	if( chk_armor_randm_art( ARMOR_RANDM_ART_KIND_HEALING,
			ARMOR_RANDM_ART_MNR_HEALING_HP, NULL, chr ) ){
		n = n * ARMOR_RANDM_ART_HEALING_HP_RATE / _100_PERCENT;
	}

	/* ���� */

	add_hp( chr, +n, FALSE, FALSE );
}

/***************************************************************
* MP �μ�������
* chr_t *chr : ����饯��
***************************************************************/

void	natural_cure_mp_chr( chr_t *chr )
{
	bool_t	flg_wear;
	rate_t	rate;
	long	n, max, mon;

	if( chr == NULL )
		return;
	if( (get_turn() % NATURAL_CURE_MP_TURN) != 0 )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	/* ������æ���Ȳ������ᤤ */

	flg_wear = chk_wear_armor( chr );
	if( flg_wear )
		rate = NATURAL_CURE_MP_RATE;
	else
		rate = NATURAL_CURE_MP_RATE_NOT_WARE;

	/* �����̤κ����ͥ����å� */

	max = calc_max_mp( chr );
	n = (max * rate) / _100_PERCENT;
	if( n < 1 )
		n = 1;
	if( flg_wear ){
		if( n > NATURAL_CURE_MP_MAX )
			n = NATURAL_CURE_MP_MAX;
	} else {
		if( n > NATURAL_CURE_MP_MAX_NOT_WARE )
			n = NATURAL_CURE_MP_MAX_NOT_WARE;
	}

	/* ��󥯤β����� */

	mon = get_lev( chr, ABL_KIND_MON );
	mon *= NATURAL_CURE_MP_MON_MUL;
	mon += NATURAL_CURE_MP_MON_ADD;
	n += mon;

	/* �����ࡦ�����ƥ��ե����ȤΥҡ���� */

	if( chk_armor_randm_art( ARMOR_RANDM_ART_KIND_HEALING,
			ARMOR_RANDM_ART_MNR_HEALING_MP, NULL, chr ) ){
		n = n * ARMOR_RANDM_ART_HEALING_MP_RATE / _100_PERCENT;
	}

	/* ���� */

	add_mp( chr, +n, FALSE );
}

/***************************************************************
* �и��ͤμ�������
* chr_t *chr : ����饯��
***************************************************************/

void	natural_cure_exp_chr( chr_t *chr )
{
	long	n;
	long	i;

	if( chr == NULL )
		return;
	if( (get_turn() % NATURAL_CURE_EXP_TURN) != 0 )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	/* �����ࡦ�����ƥ��ե����ȤΥҡ���� */

	if( !chk_armor_randm_art( ARMOR_RANDM_ART_KIND_HEALING,
			ARMOR_RANDM_ART_MNR_HEALING_EXP, NULL, chr ) ){
		return;
	}

	for( i = 0; i < ABL_SKILL_MAX_N; i++ ){
		if( chr->abl.exp[i].n >= chr->abl.exp[i].max )
			continue;

		/* �����ࡦ�����ƥ��ե����ȤΥҡ���� */

		n = chr->abl.exp[i].max;
		n = n * ARMOR_RANDM_ART_HEALING_EXP_RATE / _100_PERCENT;

		/* ���� */

		chr->abl.exp[i].n += n;
		if( chr->abl.exp[i].n > chr->abl.exp[i].max )
			chr->abl.exp[i].n = chr->abl.exp[i].max;

		chk_lev_up( chr, TRUE, TRUE, TRUE );
	}
}

/***************************************************************
* HP �ν����ͤˤ�����
* chr_t *chr : ����饯��
***************************************************************/

void	modifier_cure_hp_chr( chr_t *chr )
{
	long	turn;
	long	n;
	rate_t	rate;

	if( chr == NULL )
		return;
	if( chr->fx_data.cure_hp.count <= 0 )
		return;
	if( chr->fx_data.cure_hp.turn <= 0 )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	turn = chr->fx_data.cure_hp.turn / chr->fx_data.cure_hp.count;
	if( turn <= 0 )
		return;
	if( (get_turn() % turn) != 0 )
		return;

	rate = chr->fx_data.cure_hp.rate;
	if( rate != 0 ){
		long	max;

		max = calc_max_hp( chr );
		n = max * rate / _100_PERCENT;
		if( labs( n ) < 1 ){
			n = sgn_l( rate );
		}
	} else {
		n = 0;
	}
	n += chr->fx_data.cure_hp.n;

	add_hp( chr, +n, FALSE, FALSE );
}

/***************************************************************
* MP �ν����ͤˤ�����
* chr_t *chr : ����饯��
***************************************************************/

void	modifier_cure_mp_chr( chr_t *chr )
{
	long	turn;
	long	n;
	rate_t	rate;

	if( chr == NULL )
		return;
	if( chr->fx_data.cure_mp.count <= 0 )
		return;
	if( chr->fx_data.cure_mp.turn <= 0 )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	turn = chr->fx_data.cure_mp.turn / chr->fx_data.cure_mp.count;
	if( turn <= 0 )
		return;
	if( (get_turn() % turn) != 0 )
		return;

	rate = chr->fx_data.cure_mp.rate;
	if( rate != 0 ){
		long	max;

		max = calc_max_mp( chr );
		n = max * rate / _100_PERCENT;
		if( labs( n ) < 1 ){
			n = sgn_l( rate );
		}
	} else {
		n = 0;
	}
	n += chr->fx_data.cure_mp.n;

	add_mp( chr, +n, FALSE );
}

/***************************************************************
* �줤�򤵤ޤ�
* chr_t *chr : ����饯��
***************************************************************/

void	sober( chr_t *chr )
{
	if( !per_randm( SOBER_AVE_TURN ) )
		return;

	chr->fx_data.drunk_rate -= SOBER_SUB_RATE;
	if( chr->fx_data.drunk_rate < 0 )
		chr->fx_data.drunk_rate = 0;
}

/***************************************************************
* �����С��Υ��ե����ȤΥ�������򸺤餹
* long turn : ���餹�������
***************************************************************/

void	dec_turn_fx_all_mbr( long turn )
{
	long	i;
	party_t	*pty;

	pty = get_party();

	for( i = 0; i < MBR_MAX_N; i++ )
		dec_turn_fx_chr( pty->mbr[i], turn );
}

/***************************************************************
* ���ڥåȤΥ��ե����ȤΥ�������򸺤餹
* long turn : ���餹�������
***************************************************************/

void	dec_turn_fx_all_pet( long turn )
{
	long	i;
	pet_t	**pet;

	pet = get_party_pet();

	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet[i] == NULL )
			continue;

		dec_turn_fx_chr( pet[i], turn );
	}
}

/***************************************************************
* ����󥹥����Υ��ե����ȤΥ�������򸺤餹
* long turn : ���餹�������
***************************************************************/

void	dec_turn_fx_all_mnstr( long turn )
{
	mnstr_t	*mns_head, *mns_p, *mns_pp;

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next->next; mns_p != NULL;
			mns_p = mns_p->next ){
		mns_pp = mns_p->prev;
		if( mns_pp == mns_head )
			break;

		dec_turn_fx_chr( mns_pp, turn );
	}
}

/***************************************************************
* ����饯���Υ��ե����ȤΥ�������򸺤餹
* chr_t *chr : ����饯��
* long turn : ���餹�������
***************************************************************/

void	dec_turn_fx_chr( chr_t *chr, long turn )
{
	fx_t	*fx, *end;

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat,
			FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) ){
		return;
	}

	end = chr->fx.prev->next;
	for( fx = end->next->next; fx->prev != end; fx = fx->next ){
		if( fx->prev->kind == FX_KIND_NULL )
			break;
		if( fx->prev->turn == FX_TURN_INFINITE_N )
			continue;
		if( fx->prev->turn > 0 )
			fx->prev->turn -= turn;
		if( fx->prev->turn > 0 )
			continue;

		clr_fx( fx->prev );
	}
}

/***************************************************************
* ���ե����Ȥμ��फ��ǽ���ͤ��Ѵ�
* fx_kind_t kind : ���ե����Ȥμ���
* return : ǽ����
***************************************************************/

abl_kind_t	get_fx_to_abl( fx_kind_t kind )
{
	switch( kind ){
	default:
		return ABL_KIND_MAX_N;
	case FX_KIND_SHARPNESS:
	case FX_KIND_DULLNESS:
		return ABL_KIND_DEX;
	case FX_KIND_STRENGTH:
	case FX_KIND_WEAKNESS:
		return ABL_KIND_STR;
	case FX_KIND_QUICKNESS:
	case FX_KIND_SLOWNESS:
		return ABL_KIND_AGI;
	case FX_KIND_BRAINY:
	case FX_KIND_BRAINLESS:
		return ABL_KIND_INT;
	case FX_KIND_WISE:
	case FX_KIND_FOOLISH:
		return ABL_KIND_WIS;
	case FX_KIND_ATTRACTIVE:
	case FX_KIND_UNATTRACTIVE:
		return ABL_KIND_CHA;
	}

	return ABL_KIND_MAX_N;
}

/***************************************************************
* ���ե����Ȥμ��फ�鶯���ͤ������ͤ��Ѵ�
* fx_kind_t kind : ���ե����Ȥμ���
* return : �����ͤ�������
***************************************************************/

long	get_fx_to_abl_add( fx_kind_t kind )
{
	switch( kind ){
	default:
		return 0;
	case FX_KIND_SHARPNESS:
	case FX_KIND_STRENGTH:
	case FX_KIND_QUICKNESS:
	case FX_KIND_BRAINY:
	case FX_KIND_WISE:
	case FX_KIND_ATTRACTIVE:
		return FX_ABL_LEV_POW_UP_N;
	case FX_KIND_DULLNESS:
	case FX_KIND_WEAKNESS:
	case FX_KIND_SLOWNESS:
	case FX_KIND_BRAINLESS:
	case FX_KIND_FOOLISH:
	case FX_KIND_UNATTRACTIVE:
		return FX_ABL_LEV_POW_DOWN_N;
	}

	return 0;
}

/***************************************************************
* ����饯���Υ��ե����Ȥ����Ƥθ��̤�¹�
* chr_t *chr : ����饯��
***************************************************************/

void	exec_all_fx( chr_t *chr )
{
	fx_t	*fx, *end;

	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	end = chr->fx.prev->next;
	for( fx = end->next->next; fx->prev != end; fx = fx->next ){
		if( chk_flg_or( chr->stat,
				FLG_STAT_NOT_EXIST
				| FLG_STAT_DEAD ) ){
			break;
		}

		exec_fx( fx->prev );
	}
}

/***************************************************************
* ����饯���Υ��ե����Ȥ�����
* chr_t *chr : ����饯��
* fx_kind_t kind : ���ե����Ȥμ���
* long turn : �������
* return : ���ե�����
***************************************************************/

fx_t	*set_fx( chr_t *chr, fx_kind_t kind, long turn )
{
	fx_t	*fx;
	char	*s;
	bool_t	flg_resi;
	bool_t	flg_asgn;
	bool_t	flg_success;
	long	bak_n;

	if( chr == NULL )
		return NULL;
	if( (kind == FX_KIND_NULL) || (kind == FX_KIND_MAX_N) )
		return NULL;

	/* ���Ǥ˥��ե����Ȥ����뤫�� */
	fx = srch_fx( &(chr->fx), kind );
	flg_asgn = FALSE;
	if( fx == NULL ){
		fx = asgn_fx( chr->fx.next );
		/* ���ե����Ȥ����äѤ����� */
		if( fx == NULL )
			return NULL;

		flg_asgn = TRUE;

		fx->kind = kind;
		fx->turn = 0;
		fx->n = 0;
		fx->chr = chr;
		fx->cast_chr = NULL;
		fx->abl_kind = ABL_KIND_HP;
	}

	if( turn == FX_TURN_INFINITE_N )
		fx->turn = FX_TURN_INFINITE_N;
	else
		fx->turn = roll_dice( turn, TRUE );

	if( fx->chr == NULL )
		s = MSG_MNSTR_UNKNOWN;
	else
		s = fx->chr->name;

	/**/

	flg_resi = FALSE;

	switch( fx->kind ){
	case FX_KIND_NULL:
	case FX_KIND_MAX_N:
		return fx;
	case FX_KIND_STONE:
		if( set_fx_stat( fx, FLG_STAT_STONE ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_STONE, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_PARALYZE:
		if( set_fx_stat( fx, FLG_STAT_PARALYZE ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_PARALYZE, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_POISON:
		if( set_fx_stat( fx, FLG_STAT_POISON ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_POISON, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_CONFUSION:
		if( set_fx_stat( fx, FLG_STAT_CONFUSION ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_CONFUSION, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_BLIND:
		if( set_fx_stat( fx, FLG_STAT_BLIND ) ){
			if( fx->chr != NULL )
				clr_chr_trgt_act( fx->chr, FALSE );
			print_msg_find( chr, FLG_NULL,
					MSG_FX_BLIND, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_SLEEP:
		if( set_fx_stat( fx, FLG_STAT_SLEEP ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_SLEEP, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_SILENCE:
		if( set_fx_stat( fx, FLG_STAT_SILENCE ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_SILENCE, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_FEAR:
		if( set_fx_stat( fx, FLG_STAT_FEAR ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_FEAR, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_HALLUCINATION:
		if( set_fx_stat( fx, FLG_STAT_HALLUCINATION ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_HALLUCINATION, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_CHARM:
		if( set_fx_stat( fx, FLG_STAT_CHARM ) ){
			if( fx->chr != NULL )
				clr_chr_trgt_act( chr, FALSE );
			print_msg_find( chr, FLG_NULL,
					MSG_FX_CHARM, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_FLY:
		if( set_fx_stat( fx, FLG_STAT_FLY ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_FLY, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_FAINT:
		if( set_fx_stat( fx, FLG_STAT_FAINT ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_FAINT, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_DRUNK:
		if( set_fx_stat( fx, FLG_STAT_DRUNK ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_DRUNK, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_VANISH:
		if( set_fx_stat( fx, FLG_STAT_VANISH ) ){
			if( fx->chr != NULL ){
				fx->chr->flg_map |= FLG_MAP_CHR_INVISIBLE;
				lost_trgt( fx->chr );
			}
			print_msg_find( chr, FLG_NULL,
					MSG_FX_VANISH, s );
		} else {
			flg_resi = TRUE;
		}

		set_map_chr_dun( fx->chr );
		draw_chr( fx->chr );

		break;
	case FX_KIND_IRON_BODY:
		if( set_fx_stat( fx, FLG_STAT_IRON_BODY ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_IRON_BODY, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_PASSWALL:
		if( set_fx_stat( fx, FLG_STAT_PASSWALL ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_PASSWALL, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_POLYMORPH:
		if( set_fx_polymorph( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_POLYMORPH, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_SENSE_INVISIBLE:
		if( set_fx_stat( fx, FLG_STAT_SENSE_INVISIBLE ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_SENSE_INVISIBLE, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_WEAK_HEAT:
		print_msg_find( chr, FLG_NULL,
				MSG_FX_WEAK_HEAT, s );
		break;
	case FX_KIND_WEAK_COLD:
		print_msg_find( chr, FLG_NULL,
				MSG_FX_WEAK_COLD, s );
		break;
	case FX_KIND_WEAK_MIND:
		print_msg_find( chr, FLG_NULL,
				MSG_FX_WEAK_MIND, s );
		break;
	case FX_KIND_WEAK_ACID:
		print_msg_find( chr, FLG_NULL,
				MSG_FX_WEAK_ACID, s );
		break;
	case FX_KIND_WEAK_ELEC:
		print_msg_find( chr, FLG_NULL,
				MSG_FX_WEAK_ELEC, s );
		break;
	case FX_KIND_WEAK_POIS:
		print_msg_find( chr, FLG_NULL,
				MSG_FX_WEAK_POIS, s );
		break;
	case FX_KIND_RESI_KNOC:
		if( set_fx_resi( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RESI_PHYS, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_RESI_SLAS:
		if( set_fx_resi( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RESI_PHYS, s );
		}
		break;
	case FX_KIND_RESI_STIN:
		if( set_fx_resi( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RESI_PHYS, s );
		}
		break;
	case FX_KIND_RESI_HEAT:
		if( set_fx_resi( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RESI_HEAT, s );
		}
		break;
	case FX_KIND_RESI_COLD:
		if( set_fx_resi( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RESI_COLD, s );
		}
		break;
	case FX_KIND_RESI_MIND:
		if( set_fx_resi( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RESI_MIND, s );
		}
		break;
	case FX_KIND_RESI_ACID:
		if( set_fx_resi( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RESI_ACID, s );
		}
		break;
	case FX_KIND_RESI_ELEC:
		if( set_fx_resi( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RESI_ELEC, s );
		}
		break;
	case FX_KIND_RESI_POIS:
		if( set_fx_resi( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RESI_POIS, s );
		}
		break;
	case FX_KIND_SHARPNESS:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_SHARPNESS, s );
		break;
	case FX_KIND_DULLNESS:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_DULLNESS, s );
		break;
	case FX_KIND_STRENGTH:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_STRENGTH, s );
		break;
	case FX_KIND_WEAKNESS:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_WEAKNESS, s );
		break;
	case FX_KIND_QUICKNESS:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_QUICKNESS, s );
		break;
	case FX_KIND_SLOWNESS:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_SLOWNESS, s );
		break;
	case FX_KIND_BRAINY:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_BRAINY, s );
		break;
	case FX_KIND_BRAINLESS:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_BRAINLESS, s );
		break;
	case FX_KIND_WISE:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_WISE, s );
		break;
	case FX_KIND_FOOLISH:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_FOOLISH, s );
		break;
	case FX_KIND_ATTRACTIVE:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_ATTRACTIVE, s );
		break;
	case FX_KIND_UNATTRACTIVE:
		set_fx_abl( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_UNATTRACTIVE, s );
		break;
	case FX_KIND_POW_UP_HP:
		set_fx_pow_up_hp( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_POW_UP_HP, s );
		break;
	case FX_KIND_MAGIC_SHIELD:
		if( set_fx_magic_armor( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_MAGIC_SHIELD, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_MAGE_ARMOR:
		if( set_fx_magic_armor( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_MAGE_ARMOR, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_COUNTER_MAGIC:
		print_msg_find( chr, FLG_NULL,
				MSG_FX_COUNTER_MAGIC, s );
		break;
	case FX_KIND_SUBSTITUTE:
		if( set_fx_magic_armor( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_SUBSTITUTE, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_BURNING_HANDS:
		if( set_fx_magic_wpn( fx ) ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_BURNING_HANDS, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_RALLY:
		flg_success = FALSE;

		bak_n = fx->n;
		if( set_fx_magic_wpn( fx ) )
			flg_success = TRUE;

		fx->n = bak_n;
		if( set_fx_magic_armor( fx ) )
			flg_success = TRUE;

		if( flg_success ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_RALLY, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_IRON_MAN:
		flg_success = FALSE;

		bak_n = fx->n;
		if( set_fx_magic_wpn( fx ) )
			flg_success = TRUE;

		fx->n = bak_n;
		if( set_fx_magic_armor( fx ) )
			flg_success = TRUE;

		if( flg_success ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_IRON_MAN, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_MIND_READING:
		flg_success = FALSE;

		bak_n = fx->n;
		if( set_fx_magic_wpn( fx ) )
			flg_success = TRUE;

		fx->n = bak_n;
		if( set_fx_magic_armor( fx ) )
			flg_success = TRUE;

		if( flg_success ){
			print_msg_find( chr, FLG_NULL,
					MSG_FX_MIND_READING, s );
		} else {
			flg_resi = TRUE;
		}
		break;
	case FX_KIND_SPEED_UP:
		set_fx_speed( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_SPEED_UP, s );
		break;
	case FX_KIND_SPEED_DOWN:
		set_fx_speed( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_SPEED_DOWN, s );
		break;
	case FX_KIND_BLESS:
		set_fx_bless( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_BLESS, s );
		break;
	case FX_KIND_STORE_LIGHT:
		set_fx_store_light( fx );
		print_msg_find( chr, FLG_NULL, MSG_FX_STORE_LIGHT, s );
		break;
	}

	if( flg_resi ){
		print_msg_find( chr, FLG_NULL, MSG_FX_RESI_STAT, s );

		if( flg_asgn ){
			free_fx( fx );
		}
	}

	draw_mbr_stat( chr );

	return fx;
}

/***************************************************************
* ���ե����Ȥ�¹�
* fx_t *p : ���ե�����
***************************************************************/

void	exec_fx( fx_t *p )
{
	if( p == NULL )
		return;

	switch( p->kind ){
	case FX_KIND_NULL:
	case FX_KIND_MAX_N:
		return;
	case FX_KIND_STONE:
	case FX_KIND_PARALYZE:
		break;
	case FX_KIND_POISON:
		exec_fx_poison( p );
		break;
	case FX_KIND_CONFUSION:
	case FX_KIND_BLIND:
	case FX_KIND_SLEEP:
	case FX_KIND_SILENCE:
		break;
	case FX_KIND_FEAR:
		exec_fx_fear( p );
		break;
	case FX_KIND_HALLUCINATION:
	case FX_KIND_CHARM:
	case FX_KIND_FLY:
	case FX_KIND_FAINT:
	case FX_KIND_DRUNK:
	case FX_KIND_VANISH:
	case FX_KIND_IRON_BODY:
	case FX_KIND_PASSWALL:
	case FX_KIND_POLYMORPH:
	case FX_KIND_SENSE_INVISIBLE:
		break;
	case FX_KIND_WEAK_HEAT:
	case FX_KIND_WEAK_COLD:
	case FX_KIND_WEAK_MIND:
	case FX_KIND_WEAK_ACID:
	case FX_KIND_WEAK_ELEC:
	case FX_KIND_WEAK_POIS:
		exec_fx_weak( p );
		break;
	case FX_KIND_RESI_KNOC:
	case FX_KIND_RESI_SLAS:
	case FX_KIND_RESI_STIN:
	case FX_KIND_RESI_HEAT:
	case FX_KIND_RESI_COLD:
	case FX_KIND_RESI_MIND:
	case FX_KIND_RESI_ACID:
	case FX_KIND_RESI_ELEC:
	case FX_KIND_RESI_POIS:
		break;
	case FX_KIND_SHARPNESS:
	case FX_KIND_DULLNESS:
	case FX_KIND_STRENGTH:
	case FX_KIND_WEAKNESS:
	case FX_KIND_QUICKNESS:
	case FX_KIND_SLOWNESS:
	case FX_KIND_BRAINY:
	case FX_KIND_BRAINLESS:
	case FX_KIND_WISE:
	case FX_KIND_FOOLISH:
	case FX_KIND_ATTRACTIVE:
	case FX_KIND_UNATTRACTIVE:
		break;
	case FX_KIND_POW_UP_HP:
		break;
	case FX_KIND_MAGIC_SHIELD:
	case FX_KIND_MAGE_ARMOR:
		break;
	case FX_KIND_COUNTER_MAGIC:
		break;
	case FX_KIND_SUBSTITUTE:
	case FX_KIND_BURNING_HANDS:
	case FX_KIND_RALLY:
	case FX_KIND_IRON_MAN:
	case FX_KIND_MIND_READING:
		break;
	case FX_KIND_SPEED_UP:
	case FX_KIND_SPEED_DOWN:
		break;
	case FX_KIND_BLESS:
		break;
	case FX_KIND_STORE_LIGHT:
		exec_fx_store_light( p );
		break;
	}
}

/***************************************************************
* ���ե����Ȥ���
* fx_t *fx : ���ե�����
***************************************************************/

void	clr_fx( fx_t *fx )
{
	char	*s;
	long	bak_n;

	if( fx == NULL )
		return;

	if( fx->chr == NULL )
		s = MSG_MNSTR_UNKNOWN;
	else
		s = fx->chr->name;

	switch( fx->kind ){
	case FX_KIND_NULL:
	case FX_KIND_MAX_N:
		break;
	case FX_KIND_STONE:
		clr_fx_stat( fx, FLG_STAT_STONE );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_STONE, s );
		break;
	case FX_KIND_PARALYZE:
		clr_fx_stat( fx, FLG_STAT_PARALYZE );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_PARALYZE, s );
		break;
	case FX_KIND_POISON:
		clr_fx_stat( fx, FLG_STAT_POISON );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_POISON, s );
		break;
	case FX_KIND_CONFUSION:
		clr_fx_stat( fx, FLG_STAT_CONFUSION );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_CONFUSION, s );
		break;
	case FX_KIND_BLIND:
		clr_fx_stat( fx, FLG_STAT_BLIND );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_BLIND, s );
		break;
	case FX_KIND_SLEEP:
		clr_fx_stat( fx, FLG_STAT_SLEEP );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_SLEEP, s );
		break;
	case FX_KIND_SILENCE:
		clr_fx_stat( fx, FLG_STAT_SILENCE );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_SILENCE, s );
		break;
	case FX_KIND_FEAR:
		clr_fx_stat( fx, FLG_STAT_FEAR );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_FEAR, s );
		break;
	case FX_KIND_HALLUCINATION:
		clr_fx_stat( fx, FLG_STAT_HALLUCINATION );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_HALLUCINATION, s );
		break;
	case FX_KIND_CHARM:
		clr_fx_stat( fx, FLG_STAT_CHARM );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_CHARM, s );
		break;
	case FX_KIND_FLY:
		clr_fx_stat( fx, FLG_STAT_FLY );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_FLY, s );
		break;
	case FX_KIND_FAINT:
		clr_fx_stat( fx, FLG_STAT_FAINT );
		break;
	case FX_KIND_DRUNK:
		clr_fx_stat( fx, FLG_STAT_DRUNK );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_DRUNK, s );
		break;
	case FX_KIND_VANISH:
		clr_fx_stat( fx, FLG_STAT_VANISH );
		if( fx->chr != NULL )
			fx->chr->flg_map &= ~(FLG_MAP_CHR_INVISIBLE);
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_VANISH, s );

		set_map_chr_dun( fx->chr );
		draw_chr( fx->chr );

		break;
	case FX_KIND_IRON_BODY:
		clr_fx_stat( fx, FLG_STAT_IRON_BODY );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_IRON_BODY, s );
		break;
	case FX_KIND_PASSWALL:
		clr_fx_stat( fx, FLG_STAT_PASSWALL );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_PASSWALL, s );
		break;
	case FX_KIND_POLYMORPH:
		clr_fx_polymorph( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_POLYMORPH, s );
		break;
	case FX_KIND_SENSE_INVISIBLE:
		clr_fx_stat( fx, FLG_STAT_SENSE_INVISIBLE );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_SENSE_INVISIBLE, s );
		break;
	case FX_KIND_WEAK_HEAT:
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_WEAK_HEAT, s );
		break;
	case FX_KIND_WEAK_COLD:
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_WEAK_COLD, s );
		break;
	case FX_KIND_WEAK_MIND:
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_WEAK_MIND, s );
		break;
	case FX_KIND_WEAK_ACID:
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_WEAK_ACID, s );
		break;
	case FX_KIND_WEAK_ELEC:
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_WEAK_ELEC, s );
		break;
	case FX_KIND_WEAK_POIS:
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_WEAK_POIS, s );
		break;
	case FX_KIND_RESI_KNOC:
		clr_fx_resi( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RESI_KNOC, s );
		break;
	case FX_KIND_RESI_SLAS:
		clr_fx_resi( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RESI_SLAS, s );
		break;
	case FX_KIND_RESI_STIN:
		clr_fx_resi( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RESI_STIN, s );
		break;
	case FX_KIND_RESI_HEAT:
		clr_fx_resi( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RESI_HEAT, s );
		break;
	case FX_KIND_RESI_COLD:
		clr_fx_resi( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RESI_COLD, s );
		break;
	case FX_KIND_RESI_MIND:
		clr_fx_resi( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RESI_MIND, s );
		break;
	case FX_KIND_RESI_ACID:
		clr_fx_resi( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RESI_ACID, s );
		break;
	case FX_KIND_RESI_ELEC:
		clr_fx_resi( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RESI_ELEC, s );
		break;
	case FX_KIND_RESI_POIS:
		clr_fx_resi( fx ); 
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RESI_POIS, s );
		break;
	case FX_KIND_SHARPNESS:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_SHARPNESS, s );
		break;
	case FX_KIND_DULLNESS:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_DULLNESS, s );
		break;
	case FX_KIND_STRENGTH:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_STRENGTH, s );
		break;
	case FX_KIND_WEAKNESS:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_WEAKNESS, s );
		break;
	case FX_KIND_QUICKNESS:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_QUICKNESS, s );
		break;
	case FX_KIND_SLOWNESS:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_SLOWNESS, s );
		break;
	case FX_KIND_BRAINY:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_BRAINY, s );
		break;
	case FX_KIND_BRAINLESS:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_BRAINLESS, s );
		break;
	case FX_KIND_WISE:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_WISE, s );
		break;
	case FX_KIND_FOOLISH:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_FOOLISH, s );
		break;
	case FX_KIND_ATTRACTIVE:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_ATTRACTIVE, s );
		break;
	case FX_KIND_UNATTRACTIVE:
		clr_fx_abl( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_UNATTRACTIVE, s );
		break;
	case FX_KIND_POW_UP_HP:
		clr_fx_pow_up_hp( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_POW_UP_HP, s );
		break;
	case FX_KIND_MAGIC_SHIELD:
		clr_fx_magic_armor( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_MAGIC_SHIELD, s );
		break;
	case FX_KIND_MAGE_ARMOR:
		clr_fx_magic_armor( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_MAGE_ARMOR, s );
		break;
	case FX_KIND_COUNTER_MAGIC:
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_COUNTER_MAGIC, s );
		break;
	case FX_KIND_SUBSTITUTE:
		clr_fx_magic_armor( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_SUBSTITUTE, s );
		break;
	case FX_KIND_BURNING_HANDS:
		clr_fx_magic_wpn( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_BURNING_HANDS, s );
		break;
	case FX_KIND_RALLY:
		bak_n = fx->n;
		clr_fx_magic_wpn( fx );

		fx->n = bak_n;
		clr_fx_magic_armor( fx );

		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_RALLY, s );
		break;
	case FX_KIND_IRON_MAN:
		bak_n = fx->n;
		clr_fx_magic_wpn( fx );

		fx->n = bak_n;
		clr_fx_magic_armor( fx );

		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_IRON_MAN, s );
		break;
	case FX_KIND_MIND_READING:
		bak_n = fx->n;
		clr_fx_magic_wpn( fx );

		fx->n = bak_n;
		clr_fx_magic_armor( fx );

		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_MIND_READING, s );
		break;
	case FX_KIND_SPEED_UP:
		clr_fx_speed( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_SPEED_UP, s );
		break;
	case FX_KIND_SPEED_DOWN:
		clr_fx_speed( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_SPEED_DOWN, s );
		break;
	case FX_KIND_BLESS:
		clr_fx_bless( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_BLESS, s );
		break;
	case FX_KIND_STORE_LIGHT:
		clr_fx_store_light( fx );
		print_msg_find( fx->chr, FLG_NULL,
				MSG_CLR_FX_STORE_LIGHT, s );
		break;
	}

	draw_mbr_stat( fx->chr );

	free_fx( fx );
}

/***************************************************************
* ���ơ������Ѳ��Υ��ե����Ȥ�����
* fx_t *fx : ���ե�����
* flg_stat_t flg : ���ơ�����
* return : ���ꤷ����?
***************************************************************/

bool_t	set_fx_stat( fx_t *fx, flg_stat_t flg )
{
	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	if( chk_resi_stat( fx->chr, flg ) )
		return FALSE;

	fx->chr->stat |= flg;

	if( chk_flg( flg, FLG_STAT_CHARM ) ){
		if( is_mbr( fx->chr ) ){
			fx->chr->attitude = ATTITUDE_ENEMY;
		} else if( is_pet( fx->chr ) ){
			fx->chr->attitude = ATTITUDE_ENEMY;
		} else if( fx->chr->kind == CHR_KIND_MNSTR ){
			fx->chr->attitude = ATTITUDE_FRIENDLY;
		}
	}

	return TRUE;
}

/***************************************************************
* ���ơ������Ѳ��Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
* flg_stat_t flg : ���ơ�����
* return : ���������?
***************************************************************/

bool_t	clr_fx_stat( fx_t *fx, flg_stat_t flg )
{
	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	fx->chr->stat &= ~(flg);

	if( chk_flg( flg, FLG_STAT_CHARM ) ){
		if( is_mbr( fx->chr ) ){
			fx->chr->attitude = ATTITUDE_MATE;
		} else if( is_pet( fx->chr ) ){
			fx->chr->attitude = ATTITUDE_MATE;
		} else if( fx->chr->kind == CHR_KIND_MNSTR ){
			if( fx->chr->mnstr_tab != NULL ){
				fx->chr->attitude = fx->chr->mnstr_tab
						->attitude;
			}
		}
	}

	return TRUE;
}

/***************************************************************
* ǽ�����Ѳ��Υ��ե����Ȥ�����
* fx_t *fx : ���ե�����
***************************************************************/

void	set_fx_abl( fx_t *fx )
{
	abl_kind_t	abl;
	long	n;
	modifier_t	m;

	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	abl = get_fx_to_abl( fx->kind );
	if( abl == ABL_KIND_MAX_N )
		return;

	n = get_fx_to_abl_add( fx->kind );

	get_modifier_fx( fx->chr, &m );
	m.add_lev[abl] += n;
	set_modifier_fx( fx->chr, &m );
}

/***************************************************************
* ǽ�����Ѳ��Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
***************************************************************/

void	clr_fx_abl( fx_t *fx )
{
	abl_kind_t	abl;
	modifier_t	m;

	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	abl = get_fx_to_abl( fx->kind );
	if( abl == ABL_KIND_MAX_N )
		return;

	get_modifier_fx( fx->chr, &m );
	m.add_lev[abl] = 0;
	set_modifier_fx( fx->chr, &m );
}

/***************************************************************
* ���Ͷ����Υ��ե����Ȥ�����
* fx_t *fx : ���ե�����
* return : ���ꤷ����?
***************************************************************/

bool_t	set_fx_resi( fx_t *fx )
{
	resi_kind_t	resi;

	switch( fx->kind ){
	default:
		return FALSE;
	case FX_KIND_RESI_KNOC:
		resi = RESI_KIND_KNOC;
		break;
	case FX_KIND_RESI_SLAS:
		resi = RESI_KIND_SLAS;
		break;
	case FX_KIND_RESI_STIN:
		resi = RESI_KIND_STIN;
		break;
	case FX_KIND_RESI_HEAT:
		resi = RESI_KIND_HEAT;
		break;
	case FX_KIND_RESI_COLD:
		resi = RESI_KIND_COLD;
		break;
	case FX_KIND_RESI_MIND:
		resi = RESI_KIND_MIND;
		break;
	case FX_KIND_RESI_ACID:
		resi = RESI_KIND_ACID;
		break;
	case FX_KIND_RESI_ELEC:
		resi = RESI_KIND_ELEC;
		break;
	case FX_KIND_RESI_POIS:
		resi = RESI_KIND_POIS;
		break;
	}

	return( pow_up_resi( fx->chr, resi ) );
}

/***************************************************************
* ���Ͷ����Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
* return : ���������?
***************************************************************/

bool_t	clr_fx_resi( fx_t *fx )
{
	resi_kind_t	resi;

	switch( fx->kind ){
	default:
		return FALSE;
	case FX_KIND_RESI_KNOC:
		resi = RESI_KIND_KNOC;
		break;
	case FX_KIND_RESI_SLAS:
		resi = RESI_KIND_SLAS;
		break;
	case FX_KIND_RESI_STIN:
		resi = RESI_KIND_STIN;
		break;
	case FX_KIND_RESI_HEAT:
		resi = RESI_KIND_HEAT;
		break;
	case FX_KIND_RESI_COLD:
		resi = RESI_KIND_COLD;
		break;
	case FX_KIND_RESI_MIND:
		resi = RESI_KIND_MIND;
		break;
	case FX_KIND_RESI_ACID:
		resi = RESI_KIND_ACID;
		break;
	case FX_KIND_RESI_ELEC:
		resi = RESI_KIND_ELEC;
		break;
	case FX_KIND_RESI_POIS:
		resi = RESI_KIND_POIS;
		break;
	}

	return( pow_down_resi( fx->chr, resi ) );
}

/***************************************************************
* HP �����Υ��ե����Ȥ�����
* fx_t *fx : ���ե�����
***************************************************************/

void	set_fx_pow_up_hp( fx_t *fx )
{
	pow_up_hp( fx, +FX_HP_LEV_POW_UP_N );
}

/***************************************************************
* HP �����Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
***************************************************************/

void	clr_fx_pow_up_hp( fx_t *fx )
{
	pow_up_hp( fx, -FX_HP_LEV_POW_UP_N );
}

/***************************************************************
* �����϶����Υ��ե����Ȥ�����
* fx_t *fx : ���ե�����
* return : ���ꤷ����?
***************************************************************/

bool_t	set_fx_magic_wpn( fx_t *fx )
{
	if( fx == NULL )
		return FALSE;

	return add_fx_magic_wpn( fx, +1 );
}

/***************************************************************
* �����϶����Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
* return : ���������?
***************************************************************/

bool_t	clr_fx_magic_wpn( fx_t *fx )
{
	if( fx == NULL )
		return FALSE;

	return add_fx_magic_wpn( fx, -fx->n );
}

/***************************************************************
* �����϶����Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
* long n : ������
* return : ����������?
***************************************************************/

bool_t	add_fx_magic_wpn( fx_t *fx, long n )
{
	rate_t	wpn_hit, wpn_crtcl, wpn_dam;
	long	max_n;

	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	wpn_hit = 0;
	wpn_crtcl = 0;
	wpn_dam = 0;
	max_n = 0;

	switch( fx->kind ){
	case FX_KIND_BURNING_HANDS:
		wpn_hit = n * BURNING_HANDS_ADD_HIT_RATE;
		wpn_dam = n * BURNING_HANDS_ADD_DAM_RATE;
		max_n = BURNING_HANDS_MAX_N;
		break;
	case FX_KIND_RALLY:
		wpn_hit = n * RALLY_ADD_HIT_RATE;
		max_n = RALLY_MAX_N;
		break;
	case FX_KIND_IRON_MAN:
		wpn_dam = n * IRON_MAN_ADD_DAM_RATE;
		max_n = IRON_MAN_MAX_N;
		break;
	case FX_KIND_MIND_READING:
		wpn_crtcl = n * MIND_READING_ADD_WPN_CRTCL_RATE;
		max_n = MIND_READING_MAX_N;
		break;
	default:
		return FALSE;
	}

	if( (fx->n + n) > +max_n )
		return FALSE;
	if( (fx->n + n) < -max_n )
		return FALSE;
	fx->n += n;

	return magic_wpn( fx, wpn_hit, wpn_crtcl, wpn_dam );
}

/***************************************************************
* �ɸ��϶����Υ��ե����Ȥ�����
* fx_t *fx : ���ե�����
* return : ���ꤷ����?
***************************************************************/

bool_t	set_fx_magic_armor( fx_t *fx )
{
	if( fx == NULL )
		return FALSE;

	return add_fx_magic_armor( fx, +1 );
}

/***************************************************************
* �ɸ��϶����Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
* return : ���������?
***************************************************************/

bool_t	clr_fx_magic_armor( fx_t *fx )
{
	if( fx == NULL )
		return FALSE;

	return add_fx_magic_armor( fx, -fx->n );
}

/***************************************************************
* �ɸ��϶����Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
* long n : ������
* return : ����������?
***************************************************************/

bool_t	add_fx_magic_armor( fx_t *fx, long n )
{
	rate_t	armor_def, armor_crtcl, armor_ac;
	long	max_n;

	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	armor_def = 0;
	armor_crtcl = 0;
	armor_ac = 0;
	max_n = 0;

	switch( fx->kind ){
	case FX_KIND_MAGIC_SHIELD:
		armor_def = n * MAGIC_SHIELD_ADD_DEF_RATE;
		max_n = MAGIC_SHIELD_MAX_N;
		break;
	case FX_KIND_MAGE_ARMOR:
		armor_ac = n * MAGE_ARMOR_ADD_AC_RATE;
		max_n = MAGE_ARMOR_MAX_N;
		break;
	case FX_KIND_SUBSTITUTE:
		armor_def = n * SUBSTITUTE_ADD_DEF_RATE;
		armor_ac = n * SUBSTITUTE_ADD_AC_RATE;
		max_n = SUBSTITUTE_MAX_N;
		break;
	case FX_KIND_RALLY:
		armor_def = n * RALLY_ADD_DEF_RATE;
		max_n = RALLY_MAX_N;
		break;
	case FX_KIND_IRON_MAN:
		armor_ac = n * IRON_MAN_ADD_AC_RATE;
		max_n = IRON_MAN_MAX_N;
		break;
	case FX_KIND_MIND_READING:
		armor_crtcl = n * MIND_READING_ADD_ARMOR_CRTCL_RATE;
		max_n = MIND_READING_MAX_N;
		break;
	default:
		return FALSE;
	}

	if( (fx->n + n) > +max_n )
		return FALSE;
	if( (fx->n + n) < -max_n )
		return FALSE;
	fx->n += n;

	return magic_armor( fx, armor_def, armor_crtcl, armor_ac );
}

/***************************************************************
* ��ư®�ٶ����Υ��ե����Ȥ�����
* fx_t *fx : ���ե�����
* return : ���ꤷ����?
***************************************************************/

bool_t	set_fx_speed( fx_t *fx )
{
	modifier_t	m;

	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	get_modifier_fx( fx->chr, &m );
	if( fx->kind == FX_KIND_SPEED_UP ){
		if( fx->n >= MOVE_MAX_N )
			return FALSE;
		fx->n++;
		m.add_move_speed++;
	} else if( fx->kind == FX_KIND_SPEED_DOWN ){
		if( fx->n <= MOVE_MIN_N )
			return FALSE;
		fx->n--;
		m.add_move_speed--;
	}
	set_modifier_fx( fx->chr, &m );

	return TRUE;
}

/***************************************************************
* ��ư®�ٶ����Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
* return : ���������?
***************************************************************/

bool_t	clr_fx_speed( fx_t *fx )
{
	modifier_t	m;

	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	get_modifier_fx( fx->chr, &m );
	m.add_move_speed -= fx->n;
	set_modifier_fx( fx->chr, &m );

	return TRUE;
}

/***************************************************************
* ����饯���Υե饰����
* fx_t *fx : ���ե�����
* flg_chr_t flg : �ե饰
* return : ���������?
***************************************************************/

bool_t	clr_fx_flg_chr( fx_t *fx, flg_chr_t flg )
{
	bool_t	flg_dis = FALSE;

	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	if( is_mbr( fx->chr ) ){
		flg_dis = TRUE;
	} else if( fx->chr->kind == CHR_KIND_MNSTR ){
		if( fx->chr->mnstr_tab == NULL ){
			return FALSE;
		} else {
			if( chk_flg( fx->chr->mnstr_tab->flg_chr, flg ) ){
				flg_dis = FALSE;
			} else {
				flg_dis = TRUE;
			}
		}
	} else {
		return FALSE;
	}

	if( flg_dis )
		fx->chr->flg_chr &= ~(flg);

	return TRUE;
}

/***************************************************************
* ��ʡ�Υ��ե����Ȥ�����
* fx_t *fx : ���ե�����
***************************************************************/

void	set_fx_bless( fx_t *fx )
{
	modifier_t	m;

	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	get_modifier_fx( fx->chr, &m );
	m.bless = FX_BLESS_ADD_RATE;
	set_modifier_fx( fx->chr, &m );
}

/***************************************************************
* ��ʡ�Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
***************************************************************/

void	clr_fx_bless( fx_t *fx )
{
	modifier_t	m;

	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	get_modifier_fx( fx->chr, &m );
	m.bless = 0;
	set_modifier_fx( fx->chr, &m );
}

/***************************************************************
* �����������륨�ե����Ȥ�����
* fx_t *fx : ���ե�����
***************************************************************/

void	set_fx_store_light( fx_t *fx )
{
	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	fx->n += FX_STORE_LIGHT_ADD_N;
}

/***************************************************************
* �����������륨�ե����Ȥ���
* fx_t *fx : ���ե�����
***************************************************************/

void	clr_fx_store_light( fx_t *fx )
{
	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	fx->n = 0;
	fx->turn = 0;
}

/***************************************************************
* ¾�ԡ������ѿȤΥ��ե����Ȥ�����
* fx_t *fx : ���ե�����
***************************************************************/

bool_t	set_fx_polymorph( fx_t *fx )
{
	mnstr_tab_t	*tab;
	modifier_t	m;

	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	tab = get_mnstr_tab_rand_dun_lev( get_dun_lev() );
	if( tab == NULL )
		return FALSE;

	get_modifier_fx( fx->chr, &m );
	m.face_mjr = tab->face_mjr;
	m.face_mnr = tab->face_mnr;
	set_modifier_fx( fx->chr, &m );

	fx->chr->face.mjr = tab->face_mjr;
	fx->chr->face.mnr = tab->face_mnr;
	fx->chr->mnstr_kind = tab->mnstr_kind;
	fx->chr->mnstr_tab = tab;

	draw_chr( fx->chr );

	return TRUE;
}

/***************************************************************
* ¾�ԡ������ѿȤΥ��ե����Ȥβ��
* fx_t *fx : ���ե�����
***************************************************************/

bool_t	clr_fx_polymorph( fx_t *fx )
{
	modifier_t	m;

	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	if( fx->chr->face.mjr_org == FACE_MJR_NULL )
		return FALSE;
	if( fx->chr->face.mnr_org == FACE_MNR_NULL )
		return FALSE;
	if( fx->chr->kind == CHR_KIND_MNSTR ){
		if( fx->chr->mnstr_kind_org == MNSTR_KIND_NULL )
			return FALSE;
		if( fx->chr->mnstr_tab_org == NULL )
			return FALSE;
	}

	get_modifier_fx( fx->chr, &m );
	m.face_mjr = fx->chr->face.mjr_org;
	m.face_mnr = fx->chr->face.mnr_org;
	set_modifier_fx( fx->chr, &m );

	fx->chr->face.mjr = fx->chr->face.mjr_org;
	fx->chr->face.mnr = fx->chr->face.mnr_org;
	fx->chr->mnstr_kind = fx->chr->mnstr_kind_org;
	fx->chr->mnstr_tab = fx->chr->mnstr_tab_org;

	draw_chr( fx->chr );

	return TRUE;
}

/***************************************************************
* Ʃ�����Υ��ե����Ȥ򥭥�󥻥�
* chr_t *chr : ����饯��
***************************************************************/

bool_t	cancel_fx_vanish( chr_t *chr )
{
	fx_t	*fx;

	if( chr == NULL )
		return FALSE;
	if( !is_mbr( chr ) && !is_mnstr_or_pet( chr ) )
		return FALSE;

	fx = srch_fx( &(chr->fx), FX_KIND_VANISH );
	if( fx == NULL )
		return FALSE;

	clr_fx( fx );

	return TRUE;
}

/***************************************************************
* �ǤΥ��ե����Ȥ�¹�
* fx_t *fx : ���ե�����
***************************************************************/

void	exec_fx_poison( fx_t *fx )
{
	long	sub_n;

	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	sub_n = fx->chr->abl.hp.max * POISON_DEC_RATE / _100_PERCENT;
	if( sub_n < 1 )
		sub_n = 1;

	if( (get_turn() % FX_AVE_TURN_POISON_DEC) == 0 )
		add_hp( fx->chr, -sub_n, TRUE, FALSE );
}

/***************************************************************
* �ǤΥ��ե����Ȥ�¹�
* fx_t *fx : ���ե�����
***************************************************************/

void	exec_fx_fear( fx_t *fx )
{
	long	sub_n;

	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	sub_n = fx->chr->abl.mp.max * FEAR_DEC_RATE / _100_PERCENT;
	if( sub_n < 1 )
		sub_n = 1;

	if( (get_turn() % FX_AVE_TURN_FEAR_DEC) == 0 )
		add_mp( fx->chr, -sub_n, TRUE );
}

/***************************************************************
* ���ΤΥ��ե����Ȥ�¹�
* fx_t *fx : ���ե�����
***************************************************************/

void	exec_fx_weak( fx_t *fx )
{
	resi_kind_t	resi;
	rate_t	rate;
	trgt_kind_t	trgt_kind;

	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	switch( fx->kind ){
	case FX_KIND_WEAK_HEAT:
		resi = RESI_KIND_HEAT;
		break;
	case FX_KIND_WEAK_COLD:
		resi = RESI_KIND_COLD;
		break;
	case FX_KIND_WEAK_MIND:
		resi = RESI_KIND_MIND;
		break;
	case FX_KIND_WEAK_ACID:
		resi = RESI_KIND_ACID;
		break;
	case FX_KIND_WEAK_ELEC:
		resi = RESI_KIND_ELEC;
		break;
	case FX_KIND_WEAK_POIS:
		resi = RESI_KIND_POIS;
		break;
	default:
		return;
	}

	rate = FX_WEAK_RATE;

	trgt_kind = get_trgt_kind_from_chr( fx->chr );

	fx_spell_attack( fx->cast_chr, trgt_kind, fx->chr, resi,
			fx->abl_kind, rate );
}

/***************************************************************
* ����Ƥ����������Ĥ���
* fx_t *fx : ���ե�����
***************************************************************/

void	exec_fx_store_light( fx_t *fx )
{
	dun_t	*dun = get_dun();

	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	/* �����̵꤬���ʤä��饨�ե����Ȥ��� */

	if( fx->n <= 0 ){
		fx->turn = 0;
		return;
	}

	/* �����꤬�����Ƥ����鲿�⤷�ʤ� */

	if( dun->map.light_depth_obj[fx->chr->y][fx->chr->x] > 0 )
		return;

	/* ������������� */

	fx->n--;
	fx_light( fx->chr->x, fx->chr->y );

	if( fx->n <= 0 )
		curs_attrset_chr( fx->chr, -1, FALSE );
	print_msg_find( fx->chr, FLG_NULL, MSG_FX_STORE_LIGHT_ON,
			fx->chr->name, fx->n );
	curs_attrset_dflt();

	/* �����̵꤬���ʤä��饨�ե����Ȥ��� */

	if( fx->n <= 0 )
		fx->turn = 0;
}

/***************************************************************
* ���С��μ��Τν����ǡ������֤�
* return : �����ǡ���
***************************************************************/

modifier_t	*get_modifier_song_mbr( void )
{
	return( &g_modifier_song_mbr );
}

/***************************************************************
* ��󥹥����μ��Τν����ǡ������֤�
* return : �����ǡ���
***************************************************************/

modifier_t	*get_modifier_song_mnstr( void )
{
	return( &g_modifier_song_mnstr );
}

/***************************************************************
* �ڥåȤμ��Τν����ǡ������֤�
* return : �����ǡ���
***************************************************************/

modifier_t	*get_modifier_song_pet( void )
{
	return( &g_modifier_song_pet );
}

/***************************************************************
* ������饯���μ��Τν����ǡ�����ꥻ�å�
***************************************************************/

void	reset_modifier_all_song( void )
{
	reset_modifier( &g_modifier_song_mbr );
	reset_modifier( &g_modifier_song_mnstr );
	reset_modifier( &g_modifier_song_pet );
}

/***************************************************************
* ����饯���μ��Τȳڴ�ν����ǡ���������
* chr_t *chr : ����饯��
***************************************************************/

void	set_modifier_all_song( chr_t *chr )
{
	spell_tab_t	*tab;
	extent_kind_t	extent;
	spell_kind_t	kind;

	if( chr == NULL )
		return;
	if( chr->act.kind != ACT_KIND_SPELL )
		return;

	extent = (extent_kind_t)(chr->act.n);

	tab = (spell_tab_t *)(chr->act.p);
	set_modifier_all_song_sub( chr, tab, extent );

	kind = get_inst_spell_kind( (mbr_t *)chr );
	if( kind != SPELL_KIND_NULL ){
		tab = get_spell_tab( kind );
		set_modifier_all_song_limit( chr, tab );
	}
}

/***************************************************************
* ����饯���μ��Τν����ǡ���������
* chr_t *chr : ����饯��
* spell_tab_t *tab : ���ΤΥǡ���
* extent_kind_t extent : ��ʸ�θ����ϰ�
***************************************************************/

void	set_modifier_all_song_sub(
	chr_t *chr,
	spell_tab_t *tab, extent_kind_t extent
)
{
	if( tab == NULL )
		return;
	if( tab->abl != ABL_KIND_BAR )
		return;

	switch( extent ){
	case EXTENT_KIND_NULL:
	case EXTENT_KIND_MAX_N:
		break;
	case EXTENT_KIND_NORMAL:
		set_modifier_song( &g_modifier_song_mbr, tab );
		set_modifier_song( &g_modifier_song_mnstr, tab );
		set_modifier_song( &g_modifier_song_pet, tab );
		break;
	case EXTENT_KIND_SPREAD:
	case EXTENT_KIND_MASS:
		break;
	case EXTENT_KIND_LIMIT:
		switch( chr->trgt.kind ){
		case TRGT_KIND_NULL:
			break;
		case TRGT_KIND_MBR:
			set_modifier_song( &g_modifier_song_mbr, tab );
			set_modifier_song( &g_modifier_song_pet, tab );
			break;
		case TRGT_KIND_MNSTR:
		case TRGT_KIND_MNSTR_NULL:
			if( is_pet( (mnstr_t *)(chr->trgt.p) ) ){
				set_modifier_song( &g_modifier_song_pet,
						tab );
			} else {
				set_modifier_song( &g_modifier_song_mnstr,
						tab );
			}
			break;
		case TRGT_KIND_ITEM:
		case TRGT_KIND_DOOR:
		case TRGT_KIND_TRAP:
		case TRGT_KIND_QUEUE:
		case TRGT_KIND_SQUARE:
		case TRGT_KIND_POS:
		case TRGT_KIND_AUTO:
		case TRGT_KIND_MAX_N:
			break;
		}
		break;
	case EXTENT_KIND_HALF:
	case EXTENT_KIND_DOUBLE:
		break;
	}
}

/***************************************************************
* ����饯���μ��Τν����ǡ���������
* chr_t *chr : ����饯��
* spell_tab_t *tab : ���ΤΥǡ���
***************************************************************/

void	set_modifier_all_song_limit( chr_t *chr, spell_tab_t *tab )
{
	if( tab == NULL )
		return;
	if( tab->abl != ABL_KIND_BAR )
		return;

	switch( get_inst_spell_chr_kind( chr, tab->kind ) ){
	case CHR_KIND_MBR:
		set_modifier_song( &g_modifier_song_mbr, tab );
		set_modifier_song( &g_modifier_song_pet, tab );
		break;
	case CHR_KIND_MNSTR:
		set_modifier_song( &g_modifier_song_mnstr, tab );
		break;
	default:
		break;
	}
}

/***************************************************************
* ���Τν����ǡ���������
* modifier_t *mod : �����ǡ���
* spell_tab_t *tab : ���ΤΥǡ���
***************************************************************/

void	set_modifier_song( modifier_t *mod, spell_tab_t *tab )
{
	fx_kind_t	fx_kind;
	flg_stat_t	resi_stat;
	abl_kind_t	abl;

	if( mod == NULL )
		return;
	if( tab == NULL )
		return;

	fx_kind = FX_KIND_NULL;
	resi_stat = FLG_NULL;

	switch( tab->kind ){
	case SPELL_KIND_NULL:
/* MAG */
	case SPELL_KIND_MAG_MIN_N:
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
	case SPELL_KIND_DISPEL_MAGIC:
	case SPELL_KIND_MIRROR_IMAGE:
	case SPELL_KIND_ANIMATE_OBJECTS:
	case SPELL_KIND_SHELTER:
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
	case SPELL_KIND_POLYMORPH_OTHER:
	case SPELL_KIND_POLYMORPH_SELF:
	case SPELL_KIND_STEALTH:
	case SPELL_KIND_MAG_MAX_N:
/* SOR */
	case SPELL_KIND_SOR_MIN_N:
	case SPELL_KIND_MAGIC_MISSILE:
	case SPELL_KIND_FIRE_BALL:
	case SPELL_KIND_ICE_BLIZZARD:
	case SPELL_KIND_MIND_STORM:
	case SPELL_KIND_ACID_RAIN:
	case SPELL_KIND_LIGHTNING_BOLT:
	case SPELL_KIND_POISON_CLOUD:
	case SPELL_KIND_DEATH_SPELL:
	case SPELL_KIND_WORD_OF_DESTRUCTION:
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
/* ENC */
	case SPELL_KIND_ENC_MIN_N:
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
	case SPELL_KIND_ENERGY_DRAIN:
	case SPELL_KIND_SLOW:
	case SPELL_KIND_HUNGER:
	case SPELL_KIND_CANCELLATION:
	case SPELL_KIND_ENC_MAX_N:
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
	case SPELL_KIND_DISMISSAL:
	case SPELL_KIND_SUM_MAX_N:
/* PRI */
	case SPELL_KIND_PRI_MIN_N:
	case SPELL_KIND_CURE_HP_LIGHT:
	case SPELL_KIND_CURE_HP_MODERATE:
	case SPELL_KIND_CURE_HP_SERIOUS:
	case SPELL_KIND_CURE_HP_MAX:
	case SPELL_KIND_REGENERATION:
	case SPELL_KIND_CURE_MP:
	case SPELL_KIND_TRANSFER_MP:
	case SPELL_KIND_RESTORE_EXPERIENCE:
	case SPELL_KIND_RESURRECTION:
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
	case SPELL_KIND_PROTECTION:
	case SPELL_KIND_RESIST_PHYSICAL:
	case SPELL_KIND_RESIST_HEAT:
	case SPELL_KIND_RESIST_COLD:
	case SPELL_KIND_RESIST_ACID:
	case SPELL_KIND_RESIST_MIND:
	case SPELL_KIND_RESIST_ELECTRICITY:
	case SPELL_KIND_RESIST_POISON:
	case SPELL_KIND_BLESS:
	case SPELL_KIND_REMOVE_CURSE:
	case SPELL_KIND_DISPEL_UNDEAD:
	case SPELL_KIND_ESCAPE:
	case SPELL_KIND_SANCTUARY:
	case SPELL_KIND_WISH:
	case SPELL_KIND_PRI_MAX_N:
/* SHA */
	case SPELL_KIND_SHA_MIN_N:
	case SPELL_KIND_WEAK_FIRE_ELEMENTAL:
	case SPELL_KIND_WEAK_WATER_ELEMENTAL:
	case SPELL_KIND_WEAK_AIR_ELEMENTAL:
	case SPELL_KIND_WEAK_EARTH_ELEMENTAL:
	case SPELL_KIND_WEAK_LIGHT_ELEMENTAL:
	case SPELL_KIND_WEAK_DARK_ELEMENTAL:
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
	case SPELL_KIND_DISMISSAL_ELEMENTAL:
	case SPELL_KIND_SHA_MAX_N:
		break;
/* BAR */
	case SPELL_KIND_BAR_MIN_N:
		break;
	case SPELL_KIND_SONG_CURE_HP:
		mod->cure_hp.count++;
		mod->cure_hp.turn += SONG_CURE_HP_TURN;
		mod->cure_hp.rate += SONG_CURE_HP_RATE;
		mod->cure_hp.n += 0;
		break;
	case SPELL_KIND_SONG_CURE_MP:
		mod->cure_mp.count++;
		mod->cure_mp.turn += SONG_CURE_MP_TURN;
		mod->cure_mp.rate += SONG_CURE_MP_RATE;
		mod->cure_mp.n += 0;
		break;
	case SPELL_KIND_SONG_SHARPNESS:
		fx_kind = FX_KIND_SHARPNESS;
		break;
	case SPELL_KIND_SONG_STRENGTH:
		fx_kind = FX_KIND_STRENGTH;
		break;
	case SPELL_KIND_SONG_QUICKNESS:
		fx_kind = FX_KIND_QUICKNESS;
		break;
	case SPELL_KIND_SONG_BRAINY:
		fx_kind = FX_KIND_BRAINY;
		break;
	case SPELL_KIND_SONG_WISE:
		fx_kind = FX_KIND_WISE;
		break;
	case SPELL_KIND_SONG_ATTRACTIVE:
		fx_kind = FX_KIND_ATTRACTIVE;
		break;
	case SPELL_KIND_SONG_DULLNESS:
		fx_kind = FX_KIND_DULLNESS;
		break;
	case SPELL_KIND_SONG_WEAKNESS:
		fx_kind = FX_KIND_WEAKNESS;
		break;
	case SPELL_KIND_SONG_SLOWNESS:
		fx_kind = FX_KIND_SLOWNESS;
		break;
	case SPELL_KIND_SONG_BRAINLESS:
		fx_kind = FX_KIND_BRAINLESS;
		break;
	case SPELL_KIND_SONG_FOOLISH:
		fx_kind = FX_KIND_FOOLISH;
		break;
	case SPELL_KIND_SONG_UNATTRACTIVE:
		fx_kind = FX_KIND_UNATTRACTIVE;
		break;
	case SPELL_KIND_SONG_RESI_STAT_STONE:
		resi_stat |= FLG_STAT_STONE;
		break;
	case SPELL_KIND_SONG_RESI_STAT_PARALYZE:
		resi_stat |= FLG_STAT_PARALYZE;
		break;
	case SPELL_KIND_SONG_RESI_STAT_POISON:
		resi_stat |= FLG_STAT_POISON;
		break;
	case SPELL_KIND_SONG_RESI_STAT_CONFUSION:
		resi_stat |= FLG_STAT_CONFUSION;
		break;
	case SPELL_KIND_SONG_RESI_STAT_BLIND:
		resi_stat |= FLG_STAT_BLIND;
		break;
	case SPELL_KIND_SONG_RESI_STAT_SLEEP:
		resi_stat |= FLG_STAT_SLEEP;
		break;
	case SPELL_KIND_SONG_RESI_STAT_SILENCE:
		resi_stat |= FLG_STAT_SILENCE;
		break;
	case SPELL_KIND_SONG_RESI_STAT_FEAR:
		resi_stat |= FLG_STAT_FEAR;
		break;
	case SPELL_KIND_SONG_RESI_STAT_HALLUCINATION:
		resi_stat |= FLG_STAT_HALLUCINATION;
		break;
	case SPELL_KIND_SONG_RESI_STAT_CHARM:
		resi_stat |= FLG_STAT_CHARM;
		break;
	case SPELL_KIND_SONG_RESI_STAT_DRUNK:
		resi_stat |= FLG_STAT_DRUNK;
		break;
	case SPELL_KIND_BAR_MAX_N:
		break;
/* NIN */
	case SPELL_KIND_NIN_MIN_N:
	case SPELL_KIND_TYPHOON:	/* ����-���� */
	case SPELL_KIND_CONFLAGRATION:	/* ����-�к� */
	case SPELL_KIND_EARTHQUAKE:	/* ����-�Ͽ� */
	case SPELL_KIND_THUNDERCLOUD:	/* ����-��� */
	case SPELL_KIND_INUNDATION:	/* ����-���� */

	case SPELL_KIND_SUBSTITUTE:	/* ����-���� */
	case SPELL_KIND_BURNING_HANDS:	/* ����-��� */
	case SPELL_KIND_RALLY:	/* ����-���ڽ��� */
	case SPELL_KIND_IRON_MAN:	/* ����-Ŵ�� */
	case SPELL_KIND_MIND_READING:	/* ����-�����߿� */
	case SPELL_KIND_NIN_MAX_N:
/* ANC */
	case SPELL_KIND_ANC_MIN_N:
	case SPELL_KIND_NOTHING:
	case SPELL_KIND_POLTERGEIST:
	case SPELL_KIND_ANC_MAX_N:
/* end */
	case SPELL_KIND_MAX_N:
		break;
	}

	if( fx_kind != FX_KIND_NULL ){
		abl = get_fx_to_abl( fx_kind );
		if( abl == ABL_KIND_MAX_N )
			return;
		mod->add_lev[abl] += get_fx_to_abl_add( fx_kind );
	}

	mod->resi_stat |= resi_stat;
}

/***************************************************************
* ����饯�����������
* chr_t *chr : ����饯��
* item_t *item : ��
* bool_t flg_dec : ���ο��򸺤餹��?
***************************************************************/

void	quaff_potion( chr_t *chr, item_t *item, bool_t flg_dec )
{
	item_t	tmp;
	long	i, n;
	char	*str_drink;

	if( chr == NULL )
		return;
	if( item == NULL )
		return;
	if( item->kind != ITEM_KIND_POTION )
		return;
	if( item->n <= 0 )
		return;

	print_msg_find( chr, FLG_NULL,
			MSG_FX_QUAFF_POTION, chr->name, item->name );

	if( is_mbr( chr ) )
		identify_potion( item );

	copy_item( &tmp, item );
	if( flg_dec )
		inc_item( item, -1 );

	n = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( drink_n_msg_ls[i] == N_MSG_NULL )
			break;
		if( randm( i + 1 ) == 0 )
			n = i;
	}
	str_drink = MSG( drink_n_msg_ls[n] );

	switch( tmp.dat.potion.kind ){
	case POTION_KIND_NULL:
	case POTION_KIND_MAX_N:
		break;
	case POTION_KIND_WATER:
		print_msg_find( chr, FLG_NULL, MSG_FX_WATER, chr->name );
		break;
	case POTION_KIND_RED_WINE:
		fx_drink_liquor( chr, &tmp, LIQUOR_KIND_RED_WINE );
		break;
	case POTION_KIND_WHITE_WINE:
		fx_drink_liquor( chr, &tmp, LIQUOR_KIND_WHITE_WINE );
		break;
	case POTION_KIND_ROSE_WINE:
		fx_drink_liquor( chr, &tmp, LIQUOR_KIND_ROSE_WINE );
		break;
	case POTION_KIND_ALE:
		fx_drink_liquor( chr, &tmp, LIQUOR_KIND_ALE );
		break;
	case POTION_KIND_BRANDY:
		fx_drink_liquor( chr, &tmp, LIQUOR_KIND_BRANDY );
		break;
	case POTION_KIND_RUM:
		fx_drink_liquor( chr, &tmp, LIQUOR_KIND_RUM );
		break;
	case POTION_KIND_MILK:
	case POTION_KIND_COFFE:
	case POTION_KIND_ICE_COFFE:
	case POTION_KIND_TEA:
	case POTION_KIND_MILK_TEA:
	case POTION_KIND_LEMON_TEA:
	case POTION_KIND_ICE_TEA:
	case POTION_KIND_ICE_MILK_TEA:
	case POTION_KIND_ICE_LEMON_TEA:
	case POTION_KIND_APPLE_JUICE:
	case POTION_KIND_GRAPE_JUICE:
	case POTION_KIND_ORANGE_JUICE:
	case POTION_KIND_BLACK_BERRY_JUICE:
	case POTION_KIND_CRAN_BERRY_JUICE:
	case POTION_KIND_RASP_BERRY_JUICE:
	case POTION_KIND_STRAW_BERRY_JUICE:
		print_msg_find( chr, FLG_NULL, str_drink,
				tmp.tab.potion->name );
		break;
	case POTION_KIND_OIL:
		print_msg_find( chr, FLG_NULL, MSG_S, MSG_FX_OIL );
		break;
	case POTION_KIND_STONE:
		quaff_potion_std( chr, FX_KIND_STONE );
		break;
	case POTION_KIND_PARALYZE:
		quaff_potion_std( chr, FX_KIND_PARALYZE );
		break;
	case POTION_KIND_POISON:
		quaff_potion_poison( chr );
		break;
	case POTION_KIND_CONFUSION:
		quaff_potion_std( chr, FX_KIND_CONFUSION );
		break;
	case POTION_KIND_BLIND:
		quaff_potion_std( chr, FX_KIND_BLIND );
		break;
	case POTION_KIND_SLEEP:
		quaff_potion_std( chr, FX_KIND_SLEEP );
		break;
	case POTION_KIND_SILENCE:
		quaff_potion_std( chr, FX_KIND_SILENCE );
		break;
	case POTION_KIND_FEAR:
		quaff_potion_std( chr, FX_KIND_FEAR );
		break;
	case POTION_KIND_HALLUCINATION:
		quaff_potion_std( chr, FX_KIND_HALLUCINATION );
		break;
	case POTION_KIND_CHARM:
		quaff_potion_std( chr, FX_KIND_CHARM );
		break;
	case POTION_KIND_FLY:
		quaff_potion_std( chr, FX_KIND_FLY );
		break;
	case POTION_KIND_VANISH:
		quaff_potion_std( chr, FX_KIND_VANISH );
		break;
	case POTION_KIND_IRON_BODY:
		quaff_potion_std( chr, FX_KIND_IRON_BODY );
		break;
	case POTION_KIND_PASSWALL:
		quaff_potion_std( chr, FX_KIND_PASSWALL );
		break;
	case POTION_KIND_SENSE_INVISIBLE:
		quaff_potion_std( chr, FX_KIND_SENSE_INVISIBLE );
		break;
	case POTION_KIND_RESI_PHYS:
		quaff_potion_resi( chr, FX_KIND_RESI_KNOC );
		quaff_potion_resi( chr, FX_KIND_RESI_SLAS );
		quaff_potion_resi( chr, FX_KIND_RESI_STIN );
		break;
	case POTION_KIND_RESI_HEAT:
		quaff_potion_resi( chr, FX_KIND_RESI_HEAT );
		break;
	case POTION_KIND_RESI_COLD:
		quaff_potion_resi( chr, FX_KIND_RESI_COLD );
		break;
	case POTION_KIND_RESI_MIND:
		quaff_potion_resi( chr, FX_KIND_RESI_MIND );
		break;
	case POTION_KIND_RESI_ACID:
		quaff_potion_resi( chr, FX_KIND_RESI_ACID );
		break;
	case POTION_KIND_RESI_ELEC:
		quaff_potion_resi( chr, FX_KIND_RESI_ELEC );
		break;
	case POTION_KIND_RESI_POIS:
		quaff_potion_resi( chr, FX_KIND_RESI_POIS );
		break;
	case POTION_KIND_SHARPNESS:
		quaff_potion_abl( chr, FX_KIND_SHARPNESS );
		break;
	case POTION_KIND_DULLNESS:
		quaff_potion_abl( chr, FX_KIND_DULLNESS );
		break;
	case POTION_KIND_STRENGTH:
		quaff_potion_abl( chr, FX_KIND_STRENGTH );
		break;
	case POTION_KIND_WEAKNESS:
		quaff_potion_abl( chr, FX_KIND_WEAKNESS );
		break;
	case POTION_KIND_QUICKNESS:
		quaff_potion_abl( chr, FX_KIND_QUICKNESS );
		break;
	case POTION_KIND_SLOWNESS:
		quaff_potion_abl( chr, FX_KIND_SLOWNESS );
		break;
	case POTION_KIND_BRAINY:
		quaff_potion_abl( chr, FX_KIND_BRAINY );
		break;
	case POTION_KIND_BRAINLESS:
		quaff_potion_abl( chr, FX_KIND_BRAINLESS );
		break;
	case POTION_KIND_WISE:
		quaff_potion_abl( chr, FX_KIND_WISE );
		break;
	case POTION_KIND_FOOLISH:
		quaff_potion_abl( chr, FX_KIND_FOOLISH );
		break;
	case POTION_KIND_ATTRACTIVE:
		quaff_potion_abl( chr, FX_KIND_ATTRACTIVE );
		break;
	case POTION_KIND_UNATTRACTIVE:
		quaff_potion_abl( chr, FX_KIND_UNATTRACTIVE );
		break;
	case POTION_KIND_POW_UP_HP:
		quaff_potion_pow_up_hp( chr );
		break;
	case POTION_KIND_SPEED_UP:
		quaff_potion_speed( chr, +1 );
		break;
	case POTION_KIND_SPEED_DOWN:
		quaff_potion_speed( chr, -1 );
		break;
	case POTION_KIND_CURE_LEV:
		quaff_potion_cure_lev( chr );
		break;
	case POTION_KIND_CURE_HP_LIGHT:
		quaff_potion_cure_hp_light( chr );
		break;
	case POTION_KIND_CURE_HP_MODERATE:
		quaff_potion_cure_hp_moderate( chr );
		break;
	case POTION_KIND_CURE_HP_SERIOUS:
		quaff_potion_cure_hp_serious( chr );
		break;
	case POTION_KIND_CURE_HP_MAX:
		quaff_potion_cure_hp_max( chr );
		break;
	case POTION_KIND_CURE_POISON:
		quaff_potion_cure_poison( chr );
		break;
	case POTION_KIND_CURE_STATUS:
		quaff_potion_cure_status( chr );
		break;
	case POTION_KIND_DETECT_MNSTR:
		quaff_potion_detect_mnstr( chr );
		break;
	}

	draw_mbr_stat( chr );
}

/***************************************************************
* ����饯����ɸ��Ū���������
* chr_t *chr : ����饯��
* fx_kind_t fx_k : ���ե����Ȥμ���
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_std( chr_t *chr, fx_kind_t fx_k )
{
	return set_fx_std( chr, fx_k );
}

/***************************************************************
* ����饯����ǽ�����Ѳ����������
* chr_t *chr : ����饯��
* fx_kind_t fx_k : ���ե����Ȥμ���
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_abl( chr_t *chr, fx_kind_t fx_k )
{
	return fx_abl( chr, fx_k );
}

/***************************************************************
* ����饯�������Ͷ������������
* chr_t *chr : ����饯��
* fx_kind_t fx_k : ���ե����Ȥμ���
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_resi( chr_t *chr, fx_kind_t fx_k )
{
	return fx_resi( chr, fx_k );
}

/***************************************************************
* ����饯������٥�������������
* chr_t *chr : ����饯��
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_cure_lev( chr_t *chr )
{
	return fx_cure_lev( chr );
}

/***************************************************************
* ����饯���� HP ���������������
* chr_t *chr : ����饯��
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_cure_hp_light( chr_t *chr )
{
	return fx_cure_hp_light( chr, get_lev( chr, ABL_KIND_HP ) );
}

/***************************************************************
* ����饯���� HP ��������������
* chr_t *chr : ����饯��
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_cure_hp_moderate( chr_t *chr )
{
	return fx_cure_hp_moderate( chr, get_lev( chr, ABL_KIND_HP ) );
}

/***************************************************************
* ����饯���� HP ��������������
* chr_t *chr : ����饯��
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_cure_hp_serious( chr_t *chr )
{
	return fx_cure_hp_serious( chr, get_lev( chr, ABL_KIND_HP ) );
}

/***************************************************************
* ����饯���� HP ���������������
* chr_t *chr : ����饯��
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_cure_hp_max( chr_t *chr )
{
	return fx_cure_hp_max( chr, get_lev( chr, ABL_KIND_HP ) );
}

/***************************************************************
* ����饯�����ǲ������������
* chr_t *chr : ����饯��
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_cure_poison( chr_t *chr )
{
	fx_t	*fx;

	if( chr == NULL )
		return FALSE;

	fx = &(chr->fx);

	fx = srch_fx( fx, FX_KIND_POISON );
	if( fx == NULL )
		return FALSE;

	clr_fx( fx );

	return TRUE;
}

/***************************************************************
* ����饯���������ơ������������������
* chr_t *chr : ����饯��
* return : ���ե����Ȥ����İʾ������褿��?
***************************************************************/

bool_t	quaff_potion_cure_status( chr_t *chr )
{
	return fx_cure_all_stat( chr );
}

/***************************************************************
* ����饯������󥹥������Τ��������
* chr_t *chr : ����饯��
* return : ����������?
***************************************************************/

bool_t	quaff_potion_detect_mnstr( chr_t *chr )
{
	return fx_detect_mnstr( chr );
}

/***************************************************************
* ����饯�������������
* chr_t *chr : ����饯��
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_poison( chr_t *chr )
{
	return fx_poison( chr );
}

/***************************************************************
* ����饯���� HP �������������
* chr_t *chr : ����饯��
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_pow_up_hp( chr_t *chr )
{
	return fx_pow_up_hp( chr );
}

/***************************************************************
* ����饯������ư®�ٶ������������
* chr_t *chr : ����饯��
* long sgn_n : ������
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	quaff_potion_speed( chr_t *chr, long sgn_n )
{
	return fx_speed_up( chr, chr, sgn_n );
}

/***************************************************************
* ���פ˵���
* mbr_t *mbr : ���С�
* item_t *potion : ��
***************************************************************/

void	fill_potion( mbr_t *mbr, item_t *potion )
{
	item_t	*lamp;
	light_tab_t	*tab;

	if( mbr == NULL )
		return;
	if( !is_mbr( mbr ) )
		return;
	if( potion == NULL )
		return;
	if( potion->kind != ITEM_KIND_POTION )
		return;
	if( potion->n <= 0 )
		return;

	lamp = get_mbr_item_asgn_equip( mbr );
	if( lamp == NULL ){
		tab = NULL;
	} else {
		lamp = &(lamp[EQUIP_KIND_LIGHT_SOURCE]);
		tab = lamp->tab.light;
	}
	if( (lamp == NULL) || (lamp->kind != ITEM_KIND_LIGHT)
			|| (!tab->flg_fill) ){
		print_msg_find( mbr, FLG_MSG_ERR, MSG_S, MSG_ERR_FILL_LAMP );
		return;
	}

	chr_light_up( mbr, FALSE );
	if( potion->dat.potion.kind == POTION_KIND_OIL ){
		identify_potion( potion );

		lamp->dat.light.turn = tab->max_turn;
		set_item_name( lamp );

		print_msg_find( mbr, FLG_NULL,
				MSG_FILL_LAMP_OIL,
				mbr->name, lamp->name );

		lamp->dat.light.turn += ADJUST_TURN;
		set_item_name( lamp );
	} else {
		lamp->dat.light.turn = 0;
		set_item_name( lamp );

		print_msg_find( mbr, FLG_MSG_ERR,
				MSG_ERR_FILL_LAMP_NON_OIL,
				mbr->name, lamp->name );
	}
	chr_light_up( mbr, TRUE );

	inc_item( potion, -1 );
}

/***************************************************************
* ����饯�����������̣�襤�Υ�å������դ���
* chr_t *chr : ����饯��
* item_t *item : ��
* liquor_kind_t kind : ��μ���
* return : ����饯������ä���?
***************************************************************/

bool_t	fx_drink_liquor( chr_t *chr, item_t *item, liquor_kind_t kind )
{
	if( chr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->tab.potion == NULL )
		return FALSE;
	if( item->n <= 0 )
		return FALSE;

	if( is_mbr( chr ) ){
		long	n, i;
		char	*str;

		/* ̣�襤�Υ�å����� */

		n = 0;
		for( i = 0; i < LOOP_MAX_1000; i++ ){
			if( drink_n_msg_ls[i] == N_MSG_NULL )
				break;
			if( randm( i + 1 ) == 0 )
				n = i;
		}
		str = MSG( drink_n_msg_ls[n] );

		print_msg_find( chr, FLG_NULL, str, item->tab.potion->name );
	}

	/* ���� */

	return drink_liquor( chr, LIQUOR_KIND_RED_WINE );
}

/***************************************************************
* ����饯����������
* chr_t *chr : ����饯��
* liquor_kind_t kind : ��μ���
* return : ����饯������ä���?
***************************************************************/

bool_t	drink_liquor( chr_t *chr, liquor_kind_t kind )
{
	fx_t	*fx;
	long	add;

	if( chr == NULL )
		return FALSE;

	add = liquor_proof[kind];
	add = calc_resi( get_resi( chr, RESI_KIND_POIS ), add );
	chr->fx_data.drunk_rate += add;
	if( chr->fx_data.drunk_rate < _100_PERCENT )
		return FALSE;

	fx = set_fx( chr, FX_KIND_DRUNK, FX_TURN_DRUNK );

	if( fx == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ����饯������ʪ���ɤ�
* chr_t *chr : ����饯��
* item_t *item : ��ʪ
***************************************************************/

void	read_scroll( chr_t *chr, item_t *item )
{
	bool_t	flg_dec = TRUE;

	if( chr == NULL )
		return;
	if( item == NULL )
		return;
	if( item->kind != ITEM_KIND_SCROLL )
		return;
	if( item->n <= 0 )
		return;

	if( calc_light_depth( chr->x, chr->y ) <= 0 ){
		print_msg_find( chr, FLG_NULL,
				MSG_READ_SCROLL_FAILURE, chr->name );
		return;
	}

	print_msg_find( chr, FLG_NULL,
			MSG_FX_READ_SCROLL, chr->name, item->name );

	identify_scroll( item );

	switch( item->dat.scroll.kind ){
	case SCROLL_KIND_NULL:
	case SCROLL_KIND_MAX_N:
		flg_dec = FALSE;
		break;
	case SCROLL_KIND_SLEEP:
		read_scroll_sleep( chr );
		break;
	case SCROLL_KIND_IDENTIFY_ITEM:
		if( !read_scroll_identify_item( chr ) ){
			flg_dec = FALSE;
			print_msg_find( chr, FLG_NULL, MSG_CANCEL );
		}
		wipe_menu();
		break;
	case SCROLL_KIND_IDENTIFY_ALL_ITEM:
		read_scroll_identify_all_item( chr );
		break;
	case SCROLL_KIND_DETECT_ITEM:
		read_scroll_detect_item( chr );
		break;
	case SCROLL_KIND_TELEPORT:
		read_scroll_teleport( chr );
		break;
	case SCROLL_KIND_POW_UP_WPN_HIT:
		read_scroll_pow_up_wpn_hit( chr );
		break;
	case SCROLL_KIND_POW_UP_WPN_CRTCL:
		read_scroll_pow_up_wpn_crtcl( chr );
		break;
	case SCROLL_KIND_POW_UP_WPN_DAM:
		read_scroll_pow_up_wpn_dam( chr );
		break;
	case SCROLL_KIND_POW_UP_ARMOR_DEF:
		read_scroll_pow_up_armor_def( chr );
		break;
	case SCROLL_KIND_POW_UP_ARMOR_CRTCL:
		read_scroll_pow_up_armor_crtcl( chr );
		break;
	case SCROLL_KIND_POW_UP_ARMOR_AC:
		read_scroll_pow_up_armor_ac( chr );
		break;
	case SCROLL_KIND_PROTECT_ARMOR:
		read_scroll_protect_armor( chr );
		break;
	case SCROLL_KIND_BOOMERANG:
		read_scroll_boomerang( chr );
		break;
	case SCROLL_KIND_REMOVE_CURSE:
		read_scroll_remove_curse( chr );
		break;
	case SCROLL_KIND_RECALL:
		flg_dec = read_scroll_recall();
		break;
	case SCROLL_KIND_TYPHOON:
	case SCROLL_KIND_CONFLAGRATION:
	case SCROLL_KIND_EARTHQUAKE:
	case SCROLL_KIND_THUNDERCLOUD:
	case SCROLL_KIND_INUNDATION:
	case SCROLL_KIND_SUBSTITUTE:
	case SCROLL_KIND_BURNING_HANDS:
	case SCROLL_KIND_RALLY:
	case SCROLL_KIND_IRON_MAN:
	case SCROLL_KIND_MIND_READING:
		read_scroll_nin( chr, item->dat.scroll.kind );
		flg_dec = FALSE;
		break;
	}

	if( flg_dec )
		inc_item( item, -1 );

	draw_mbr_stat( chr );
}

/***************************************************************
* ����饯������̲�δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_sleep( chr_t *chr )
{
	long	dx, dy;
	long	turn;
	fx_kind_t	kind;
	mnstr_t	*mnstr;
	bool_t	ret;

	if( chr == NULL )
		return FALSE;

	ret = FALSE;

	for( dy = -1; dy <= +1; dy++ ){
		for( dx = -1; dx <= +1; dx++ ){
			mnstr = get_mnstr(
					chr->x + dx,
					chr->y + dy );
			if( mnstr == NULL )
				continue;

			kind = FX_KIND_SLEEP;
			turn = FX_AVE_TURN_SLEEP;
			if( set_fx( mnstr, kind, turn )
					!= NULL ){
				ret = TRUE;
			}
		}
	}

	if( ret ){
		print_msg_find( chr, FLG_NULL,
				MSG_FX_SLEEP_SUCCESS, chr->name );
	} else {
		print_msg_find( chr, FLG_NULL,
				MSG_FX_SLEEP_FAILURE, chr->name );
	}

	return ret;
}

/***************************************************************
* ����饯���������ƥ༱�̤δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_identify_item( chr_t *chr )
{
	return exec_menu_identify_item( chr );
}

/***************************************************************
* ����饯�����������ƥ༱�̤δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_identify_all_item( chr_t *chr )
{
	return fx_identify_all_item( chr );
}

/***************************************************************
* ����饯���������ƥ�õ�Τδ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_detect_item( chr_t *chr )
{
	return fx_detect_mnstr( chr );
}

/***************************************************************
* ����饯�����ѡ��ƥ��ְִ�ư�δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_teleport( chr_t *chr )
{
	teleport_party();

	return TRUE;
}

/***************************************************************
* ����饯�������ι����϶����δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_pow_up_wpn_hit( chr_t *chr )
{
	return fx_pow_up_wpn_hit( chr );
}

/***************************************************************
* ����饯�������Υ���ƥ����붯���δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_pow_up_wpn_crtcl( chr_t *chr )
{
	return fx_pow_up_wpn_crtcl( chr );
}

/***************************************************************
* ����饯�������Υ��᡼�������δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_pow_up_wpn_dam( chr_t *chr )
{
	return fx_pow_up_wpn_dam( chr );
}

/***************************************************************
* ����饯�����ɶ���ɸ��϶����δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_pow_up_armor_def( chr_t *chr )
{
	return fx_pow_up_armor_def( chr );
}

/***************************************************************
* ����饯�����ɶ�Υ���ƥ����붯���δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_pow_up_armor_crtcl( chr_t *chr )
{
	return fx_pow_up_armor_crtcl( chr );
}

/***************************************************************
* ����饯�����ɶ�Υ����ޡ����饹�����δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_pow_up_armor_ac( chr_t *chr )
{
	return fx_pow_up_armor_ac( chr );
}

/***************************************************************
* ����饯�����ɶ���ݸ�δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_protect_armor( chr_t *chr )
{
	return fx_protect_armor( chr );
}

/***************************************************************
* ����饯�����֡�����δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_boomerang( chr_t *chr )
{
	return fx_boomerang( chr );
}

/***************************************************************
* ����饯��������δ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_remove_curse( chr_t *chr )
{
	return remove_curse( NULL, chr, 0 );
}

/***************************************************************
* ����饯�������Ԥδ�ʪ���ɤ�
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	read_scroll_recall( void )
{
	return recall();
}

/***************************************************************
* ����饯����Ǧ�Ѥδ�ʪ���ɤ�
* chr_t *chr : ����饯��
* scroll_kind_t kind : ��ʪ�μ���
***************************************************************/

void	read_scroll_nin( chr_t *chr, scroll_kind_t kind )
{
	print_msg_find( chr, FLG_NULL, MSG_FX_READ_SCROLL_NIN );
}

/***************************************************************
* ����饯������ˡ�ξ��Ȥ�
* chr_t *chr : ����饯��
* item_t *item : ��ˡ�ξ�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	zap_stick( chr_t *chr, item_t *item )
{
	spell_tab_t	*spell;
	curs_attr_t	prev_attr;

	if( chr == NULL )
		return FALSE;
	if( chr->trgt.p == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_STICK )
		return FALSE;
	if( item->n <= 0 )
		return FALSE;

	item->dat.stick.n--;
	if( item->dat.stick.n < 0 ){
		item->dat.stick.n = 0;
		print_msg_find( chr, FLG_NULL, MSG_S, MSG_STICK_FAILURE );
		return FALSE;
	}
	set_item_name( item );

	print_msg_find( chr, FLG_NULL,
			MSG_FX_ZAP_STICK, chr->name, item->name );

	spell = get_spell_tab( item->dat.stick.spell_kind );
	if( spell == NULL )
		return FALSE;

	get_vfx_attr( &prev_attr );
	set_vfx_attr_n( CURS_ATTR_N_VFX );

	switch( item->dat.stick.kind ){
	case STICK_KIND_NULL:
	case STICK_KIND_MAX_N:
		return FALSE;
	case STICK_KIND_WAND:
		chr_cast_spell_normal( chr, TRUE, spell, _100_PERCENT );
		break;
	case STICK_KIND_ROD:
		chr_cast_spell_spread( chr, TRUE, spell, _100_PERCENT );
		break;
	case STICK_KIND_STAFF:
		chr_cast_spell_mass( chr, TRUE, spell, _100_PERCENT );
		break;
	}

	set_vfx_attr( &prev_attr );

	return TRUE;
}

/***************************************************************
* ����饯���Υ��ե����Ȥ�����
* chr_t *chr : ����饯��
* fx_kind_t fx_k : ���ե����Ȥμ���
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	fx_std( chr_t *chr, fx_kind_t fx_k )
{
	return set_fx_std( chr, fx_k );
}

/***************************************************************
* ����饯����ɸ��Ū�ʥ��ե����Ȥ�����
* chr_t *chr : ����饯��
* fx_kind_t fx_k : ���ե����Ȥμ���
* return : ���ե����Ȥ�������褿��?
***************************************************************/

bool_t	set_fx_std( chr_t *chr, fx_kind_t fx_k )
{
	long	turn;

	if( chr == NULL )
		return FALSE;

	turn = 0;

	switch( fx_k ){
	default:
		return FALSE;
	case FX_KIND_STONE:
		turn = FX_AVE_TURN_STONE;
		break;
	case FX_KIND_PARALYZE:
		turn = FX_AVE_TURN_PARALYZE;
		break;
	case FX_KIND_POISON:
		return fx_poison( chr );
	case FX_KIND_CONFUSION:
		turn = FX_AVE_TURN_CONFUSION;
		break;
	case FX_KIND_BLIND:
		turn = FX_AVE_TURN_BLIND;
		break;
	case FX_KIND_SLEEP:
		turn = FX_AVE_TURN_SLEEP;
		break;
	case FX_KIND_SILENCE:
		turn = FX_AVE_TURN_SILENCE;
		break;
	case FX_KIND_FEAR:
		turn = FX_AVE_TURN_FEAR;
		break;
	case FX_KIND_HALLUCINATION:
		turn = FX_AVE_TURN_HALLUCINATION;
		break;
	case FX_KIND_CHARM:
		turn = FX_AVE_TURN_CHARM;
		break;
	case FX_KIND_FLY:
		turn = FX_AVE_TURN_FLY;
		break;
	case FX_KIND_VANISH:
		turn = FX_AVE_TURN_VANISH;
		break;
	case FX_KIND_IRON_BODY:
		turn = FX_AVE_TURN_IRON_BODY;
		break;
	case FX_KIND_PASSWALL:
		turn = FX_AVE_TURN_PASSWALL;
		break;
	case FX_KIND_SENSE_INVISIBLE:
		turn = FX_AVE_TURN_SENSE_INVISIBLE;
		break;
	case FX_KIND_COUNTER_MAGIC:
		turn = FX_AVE_TURN_COUNTER_MAGIC;
		break;
	}

	if( set_fx( chr, fx_k, turn ) == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* �������Ĥ���
* long x : X��ɸ
* long y : Y��ɸ
* return : �����꤬�Ĥ�����?
***************************************************************/

bool_t	fx_light( long x, long y )
{
	on_light_area( x, y, TRUE );
	set_flg_find_all_mnstr();
	redraw_map();

	return TRUE;
}

/***************************************************************
* �������ä�
* long x : X��ɸ
* long y : Y��ɸ
* return : �����꤬�ä�����?
***************************************************************/

bool_t	fx_darkness( long x, long y )
{
	off_light_area( x, y, TRUE );
	set_flg_find_all_mnstr();
	redraw_map();

	return TRUE;
}

/***************************************************************
* �ɥ��θ����������
* door_t *door : �ɥ�
* return : ������褿��?
***************************************************************/

bool_t	fx_knock( door_t *door )
{
	if( door == NULL )
		return FALSE;

	return disarm_door( door->n );
}

/***************************************************************
* �ɥ�����ꤹ��
* door_t *door : �ɥ�
* return : ������褿��?
***************************************************************/

bool_t	fx_lock( door_t *door )
{
	if( door == NULL )
		return FALSE;

	return jam_door( door->n );
}

/***************************************************************
* 櫤�������
* trap_t *trap : �
* chr_t *chr : ����饯��
* return : ������褿��?
***************************************************************/

bool_t	fx_disarm_trap( trap_t *trap, chr_t *chr )
{
	return( chr_disarm_trap_abl( chr, trap,
			ABL_KIND_MAG, ABL_KIND_INT ) );
}

/***************************************************************
* û��Υž�ܤΥ��ե�����
* long bx : ��� x ��ɸ
* long by : ��� y ��ɸ
* return : ž�ܽ��褿��?
***************************************************************/

bool_t	fx_short_teleport_party( long bx, long by )
{
	return short_teleport_party( bx, by );
}

/***************************************************************
* �ѡ��ƥ��ְִ�ư�Υ��ե����� (���㡼���Ԥ�ͭ��)
* return : �ְִ�ư���褿��?
***************************************************************/

bool_t	fx_teleport_party_charge( void )
{
	return teleport_party_charge();
}

/***************************************************************
* �ѡ��ƥ��ְִ�ư�Υ��ե�����
* return : �ְִ�ư���褿��?
***************************************************************/

bool_t	fx_teleport_party( void )
{
	return teleport_party();
}

/***************************************************************
* û��Υž�ܤθ���
* long bx : ��� x ��ɸ
* long by : ��� y ��ɸ
* return : ž�ܤ����褿��?
***************************************************************/

bool_t	short_teleport_party( long bx, long by )
{
	print_msg( FLG_NULL, MSG_FX_TELEPORT_PARTY );
	call_game_sound_play( SOUND_KIND_ACTION_TELEPORT_SHORT, 1 );

	return appear_party_short( bx, by );
}

/***************************************************************
* �ѡ��ƥ��ְִ�ư�θ��� (���㡼���Ԥ�ͭ��)
* return : �ְִ�ư���褿��?
***************************************************************/

bool_t	teleport_party_charge( void )
{
	party_t	*pty;

	pty = get_party();

	pty->act.kind = ACT_KIND_TELEPORT_PARTY;
	str_nz_cpy( pty->act.msg, MSG_SPELL_TELEPORT_PARTY,
			ACT_MSG_MAX_BYTE );
	pty->act.n = 0;
	pty->act.n2 = FX_AVE_TURN_TELEPORT_PARTY;

	print_msg( FLG_MSG_NO_MORE_PREV, MSG_FX_TELEPORT_PARTY_CHARGE );
	draw_misc_stat();

	return TRUE;
}

/***************************************************************
* �ѡ��ƥ��ְִ�ư�θ��̤Υ����å�
* return : �ѡ��ƥ��ְִ�ư�λ��֤��褿��?
***************************************************************/

bool_t	chk_teleport_party( void )
{
	party_t	*pty;

	pty = get_party();

	if( pty->act.kind != ACT_KIND_TELEPORT_PARTY )
		return FALSE;

	pty->act.n2--;

	if( pty->act.n2 > 0 )
		return FALSE;

	teleport_party();

	clr_party_act();

	return TRUE;
}

/***************************************************************
* �ѡ��ƥ��ְִ�ư�θ���
* return : �ְִ�ư���褿��?
***************************************************************/

bool_t	teleport_party( void )
{
	print_msg( FLG_NULL, MSG_FX_TELEPORT_PARTY );
	call_game_sound_play( SOUND_KIND_ACTION_TELEPORT_PARTY, 1 );

	appear_party();

	return TRUE;
}

/***************************************************************
* ���֥������Ȥνְִ�ư�Υ��ե�����
* trgt_kind_t trgt_kind : ���֥������Ȥμ���
* void *p : ���֥�������
* return : �ְִ�ư���褿��?
***************************************************************/

bool_t	fx_teleport( trgt_kind_t trgt_kind, void *p )
{
	switch( trgt_kind ){
	case TRGT_KIND_NULL:
		return FALSE;
	case TRGT_KIND_MBR:
	case TRGT_KIND_MNSTR:
		teleport_chr( (mbr_t *)p );
		return TRUE;
	case TRGT_KIND_MNSTR_NULL:
		return TRUE;
	case TRGT_KIND_ITEM:
		teleport_item( (item_t *)p );
		return TRUE;
	case TRGT_KIND_DOOR:
	case TRGT_KIND_TRAP:
	case TRGT_KIND_QUEUE:
	case TRGT_KIND_SQUARE:
	case TRGT_KIND_POS:
	case TRGT_KIND_AUTO:
	case TRGT_KIND_MAX_N:
		return FALSE;
	}

	return FALSE;
}

/***************************************************************
* ����饯���νְִ�ư�θ���
* chr_t *chr : ����饯��
* return : �ְִ�ư���褿��?
***************************************************************/

bool_t	teleport_chr( chr_t *chr )
{
	long	i;
	long	nx, ny;
	bool_t	ret = FALSE;

	if( chr == NULL )
		return FALSE;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return FALSE;

	if( chr->work.link_chr != NULL )
		return FALSE;

	print_msg_find( chr, FLG_NULL, MSG_FX_TELEPORT, chr->name );
	call_game_sound_play( SOUND_KIND_ACTION_TELEPORT_LONG, 1 );

	release_chr_all_ref( chr );
	clr_map_chr( chr );

	for( i = LOOP_MAX_1000; i > 0; i-- ){
		nx = 1 + randm( MAP_MAX_X - 2);
		ny = 1 + randm( MAP_MAX_Y - 2);

		if( can_move_chr( chr, nx, ny ) )
			break;	/* ���������֤˰�ư���褿�� */
	}
	if( i > 0 ){
		chr->x = nx;
		chr->y = ny;
		ret = TRUE;
	} else {
		chr->x = chr->pre_x;
		chr->y = chr->pre_y;
	}
	chr->pre_turn_x = chr->x;
	chr->pre_turn_y = chr->y;

	clr_chr_trgt_act( chr, FALSE );
	set_map_chr( chr );

	if( is_mbr( chr ) )
		set_flg_find_all_mnstr();

	draw_chr( chr );

	return ret;
}

/***************************************************************
* ���ԤΥ��ե�����
* return : ���Ԥ��Ѱդ����褿��?
***************************************************************/

bool_t	fx_recall( void )
{
	return recall();
}

/***************************************************************
* ���Ԥθ���
* return : ���Ԥ��Ѱդ����褿��?
***************************************************************/

bool_t	recall( void )
{
	long	i;
	party_t	*pty;
	dun_t	*dun;
	long	n, max_floor, max_base;
	char	*ret;

	pty = get_party();
	dun = get_dun();
	max_floor = 0;
	max_base = 0;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( pty->mbr[i]->dun_max_lev_floor > max_floor )
			max_floor = pty->mbr[i]->dun_max_lev_floor;
		if( pty->mbr[i]->dun_max_lev_base > max_base )
			max_base = pty->mbr[i]->dun_max_lev_base;
	}

	if( dun->lev == 0 )
		n = -max_base;
	else
		n = 0;

	print_msg( FLG_NULL, MSG_FX_RECALL_ASK );
	ret = exec_menu_sel_num( &n, -max_base, max_floor );
	redraw_all();
	if( ret != NULL )
		return FALSE;

	pty->act.kind = ACT_KIND_RECALL;
	str_nz_cpy( pty->act.msg, MSG_SPELL_RECALL,
			ACT_MSG_MAX_BYTE );
	pty->act.n = n;
	pty->act.n2 = FX_AVE_TURN_RECALL;

	print_msg( FLG_MSG_NO_MORE_PREV, MSG_FX_RECALL );
	draw_misc_stat();

	return TRUE;
}

/***************************************************************
* ���Ԥθ��̤Υ����å�
* return : ���Ԥλ��֤��褿��?
***************************************************************/

bool_t	chk_recall( void )
{
	party_t	*pty;

	pty = get_party();

	if( pty->act.kind != ACT_KIND_RECALL )
		return FALSE;

	pty->act.n2--;
	if( pty->act.n2 > 0 )
		return FALSE;

	exec_recall( pty->act.n );

	return TRUE;
}

/***************************************************************
* ���Ԥθ��̤�ȯư
* long n : �µܤγ���
***************************************************************/

void	exec_recall( long n )
{
	dun_t *dun;

	call_game_sound_play( SOUND_KIND_ACTION_TELEPORT_RECALL, 1 );

	dun = get_dun();
	up_dun( n - dun->lev );

	clr_party_act();
}

/***************************************************************
* �����륿�������Υ��ե�����
* long x : X��ɸ
* long y : Y��ɸ
* return : �����륿�����������褿��?
***************************************************************/

bool_t	fx_shelter( long x, long y )
{
	const long	r = 2;
	const long	s = r - 1;
	dun_t	*dun = get_dun();
	bool_t	flg_err;
	long	xx, yy;
	long	i;

	flg_err = TRUE;
	for( i = -r; i <= +r; i++ ){
		flg_err = TRUE;

		xx = x + i;
		yy = y - r;
		if( dun->map.obj.mjr[yy][xx] != FACE_MJR_FLOOR )
			break;
		if( dun->map.obj.mnr[yy][xx] != FACE_MNR_FLOOR )
			break;
		if( dun->map.chr.mjr[yy][xx] != FACE_MJR_NULL )
			break;
		xx = x + i;
		yy = y + r;
		if( dun->map.obj.mjr[yy][xx] != FACE_MJR_FLOOR )
			break;
		if( dun->map.obj.mnr[yy][xx] != FACE_MNR_FLOOR )
			break;
		if( dun->map.chr.mjr[yy][xx] != FACE_MJR_NULL )
			break;
		xx = x - r;
		yy = y + i;
		if( dun->map.obj.mjr[yy][xx] != FACE_MJR_FLOOR )
			break;
		if( dun->map.obj.mnr[yy][xx] != FACE_MNR_FLOOR )
			break;
		if( dun->map.chr.mjr[yy][xx] != FACE_MJR_NULL )
			break;
		xx = x + r;
		yy = y + i;
		if( dun->map.obj.mjr[yy][xx] != FACE_MJR_FLOOR )
			break;
		if( dun->map.obj.mnr[yy][xx] != FACE_MNR_FLOOR )
			break;
		if( dun->map.chr.mjr[yy][xx] != FACE_MJR_NULL )
			break;

		flg_err = FALSE;
	}

	if( flg_err ){
		print_msg( FLG_MSG_ERR, MSG_FX_SHELTER_ERR );

		return FALSE;
	}

	/* �� */

	make_door_flg( x - s, y - r, x + s, y - r,
			FACE_MNR_NULL, FLG_NULL );
	make_door_flg( x - s, y + r, x + s, y + r,
			FACE_MNR_NULL, FLG_NULL );
	make_door_flg( x - r, y - s, x - r, y + s,
			FACE_MNR_NULL, FLG_NULL );
	make_door_flg( x + r, y - s, x + r, y + s,
			FACE_MNR_NULL, FLG_NULL );

	/* �� */

	make_door_flg( x - r, y - r, x - r, y - r,
			FACE_MNR_NULL, FLG_NULL );
	make_door_flg( x + r, y - r, x + r, y - r,
			FACE_MNR_NULL, FLG_NULL );
	make_door_flg( x - r, y + r, x - r, y + r,
			FACE_MNR_NULL, FLG_NULL );
	make_door_flg( x + r, y + r, x + r, y + r,
			FACE_MNR_NULL, FLG_NULL );

	redraw_all();

	return TRUE;
}

/***************************************************************
* ���������Υ��ե�����
* chr_t *chr : ����饯��
* return : �������������褿��?
***************************************************************/

bool_t	fx_create_food( chr_t *chr )
{
	item_t	*food;

	if( chr == NULL )
		return FALSE;

	food = make_item_food( 10, FOOD_KIND_PRESERVED );
	if( food == NULL )
		return FALSE;

	if( is_mbr( chr ) ){
		if( !give_mbr_item( chr, food, FALSE ) ){
			if( !put_item( food, chr->x, chr->y, PUT_ITEM_R,
					TRUE ) ){
				free_item( food );
				return FALSE;
			}
		}
	} else {
		if( !put_item( food, chr->x, chr->y, PUT_ITEM_R, TRUE ) ){
			free_item( food );
			return FALSE;
		}
	}

	if( food->tab.food != NULL ){
		print_msg_find( chr, FLG_NULL, MSG_FX_CREATE_FOOD,
				chr->name, food->tab.food->name );
	}

	return TRUE;
}

/***************************************************************
* �������ƥ༱�̤Υ��ե�����
* mbr_t *mbr : ���С�
* return : ���̽��褿��?
***************************************************************/

bool_t	fx_identify_all_item( mbr_t *mbr )
{
	item_t	*head, *p, *item;
	long	i;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

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

		if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) )
			continue;

		identify_item( item );
	}

	p = get_mbr_item_asgn_equip( mbr );
	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		if( p == NULL )
			break;
		item = &(p[i]);

		if( chk_flg( item->flg, FLG_ITEM_IDENTIFIED ) )
			continue;

		identify_item( item );
	}

	return TRUE;
}

/***************************************************************
* �����ƥ�õ�ΤΥ��ե�����
* chr_t *chr : ����饯��
* return : õ�ν��褿��?
***************************************************************/

bool_t	fx_detect_item( chr_t *chr )
{
	long	x, y, r;

	x = chr->x;
	y = chr->y;
	r = FX_DETECT_ITEM_R;
	detect_item( x, y, r );

	return TRUE;
}

/***************************************************************
* �ɥ�õ�ΤΥ��ե�����
* chr_t *chr : ����饯��
* return : õ�ν��褿��?
***************************************************************/

bool_t	fx_detect_door( chr_t *chr )
{
	long	x, y, r;

	x = chr->x;
	y = chr->y;
	r = FX_DETECT_DOOR_R;
	detect_door( x, y, r );

	return TRUE;
}

/***************************************************************
* �õ�ΤΥ��ե�����
* chr_t *chr : ����饯��
* return : õ�ν��褿��?
***************************************************************/

bool_t	fx_detect_trap( chr_t *chr )
{
	long	x, y, r;

	x = chr->x;
	y = chr->y;
	r = FX_DETECT_TRAP_R;
	detect_trap( x, y, r );

	return TRUE;
}

/***************************************************************
* ��󥹥���õ�ΤΥ��ե�����
* chr_t *chr : ����饯��
* return : õ�ν��褿��?
***************************************************************/

bool_t	fx_detect_mnstr( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;
	if( !is_mbr( chr ) )
		return TRUE;

	print_msg_find( chr, FLG_NULL, MSG_FX_DETECT_MNSTR, chr->name );

	set_find_all_mnstr();
	redraw_all();
	wait_key( TRUE );
	set_flg_find_all_mnstr();

	return TRUE;
}

/***************************************************************
* �Ż�Υ��ե�����
* chr_t *chr : ����饯��
* return : �Ż�ǽ�Ϥ�����줿��?
***************************************************************/

bool_t	fx_darkvision( chr_t *chr )
{
	const long	turn = FX_AVE_TURN_DARKVISION;

	if( chr == NULL )
		return FALSE;

	clr_map_chr( chr );

	chr->fx_data.infra_vision += roll_dice( turn, TRUE );

	chr->x = chr->pre_x;
	chr->y = chr->pre_y;
	set_map_chr( chr );

	return TRUE;
}

/***************************************************************
* æ�ФΥ��ե�����
* long bx : ��� x ��ɸ
* long by : ��� y ��ɸ
* return : æ�Ф����褿��?
***************************************************************/

bool_t	fx_escape( long bx, long by )
{
	return short_teleport_party( bx, by );
}

/***************************************************************
* ����ε���Υ��ե�����
* chr_t *chr : �оݥ��֥�������
* abl_kind_t abl : ���Ѥ���ǽ����
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_sanctuary( chr_t *chr, abl_kind_t abl )
{
	long	lev;
	long	dun_lev;
	long	dx, dy;
	long	x, y;
	trap_t	*trap;

	if( (abl <= -1) || (ABL_KIND_MAX_N <= abl) )
		lev = get_specialist_lev( chr );
	else
		lev = get_lev( chr, abl );

	dun_lev = lev * _100_PERCENT / RATE_LEV_PER_DUN_LEV;

	for( dy = -1; dy <= +1; dy++ ){
		y = chr->y + dy;

		for( dx = -1; dx <= +1; dx++ ){
			x = chr->x + dx;

			if( !clip_pos( x, y ) )
				continue;

			trap = make_trap_std( TRAP_KIND_SANCTUARY,
					x, y, dun_lev );
			if( trap == NULL )
				continue;

			trap->cx = -dx;
			trap->cy = -dy;

			find_trap( trap );
			trap->flg_chked = TRUE;
			set_trap_face_mnr( trap );
		}
	}

	return TRUE;
}

/***************************************************************
* ���ι���Υ��ե�����
* chr_t *o_p : ����¦����饯��
* trgt_kind_t trgt_kind : �оݥ��֥������Ȥμ���
* void *d_p : �оݥ��֥�������
* fx_kind_t fx_kind : ���ι���μ���
* abl_kind_t abl : ������¦��ǽ����
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_weak_attack(
	chr_t *o_p, trgt_kind_t trgt_kind, void *d_p,
	fx_kind_t fx_kind, abl_kind_t abl
)
{
	fx_t	*fx;

	switch( trgt_kind ){
	case TRGT_KIND_MBR:
	case TRGT_KIND_MNSTR:
		fx = set_fx( (chr_t *)d_p, fx_kind, FX_WEAK_TURN );
		if( fx == NULL )
			return FALSE;

		fx->cast_chr = o_p;
		fx->abl_kind = abl;
		break;
	case TRGT_KIND_ITEM:
		break_item( (item_t *)d_p, TRUE );
		break;
	case TRGT_KIND_DOOR:
		if( break_door( o_p, ((door_t *)d_p)->n ) ){
			print_msg_find( o_p, FLG_NULL,
					MSG_DOOR_BREAK, o_p->name );
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ¾�ԡ������ѿȤΥ��ե����Ȥ�����
* chr_t *chr : ����饯��
***************************************************************/

void	fx_polymorph( chr_t *chr )
{
	set_fx( chr, FX_KIND_POLYMORPH, FX_AVE_TURN_POLYMORPH );
}

/***************************************************************
* ��ˡ�Υߥ�����Υ��ե�����
* chr_t *o_p : ����¦����饯��
* trgt_kind_t trgt_kind : �оݥ��֥������Ȥμ���
* void *d_p : �оݥ��֥�������
* rate_t rate : �����Ϥ�Ψ
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_magic_missile(
	chr_t *o_p,
	trgt_kind_t trgt_kind, void *d_p,
	rate_t rate
)
{
	resi_kind_t	resi;

	switch( randm( 3 ) ){
	case 0:
		resi = RESI_KIND_KNOC;
		break;
	case 1:
		resi = RESI_KIND_SLAS;
		break;
	case 2:
		resi = RESI_KIND_STIN;
		break;
	default:
		return FALSE;
	}

	return fx_spell_attack( o_p, trgt_kind, d_p,
			resi, ABL_KIND_SOR, rate );
}

/***************************************************************
* ��ˡ����Υ��ե�����
* chr_t *o_p : ����¦����饯��
* trgt_kind_t trgt_kind : �оݥ��֥������Ȥμ���
* void *d_p : �оݥ��֥�������
* resi_kind_t resi : ���ͤμ���
* abl_kind_t abl : �ݤ���¦��ǽ����
* rate_t rate : �����Ϥ�Ψ
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_spell_attack(
	chr_t *o_p, trgt_kind_t trgt_kind, void *d_p,
	resi_kind_t resi, abl_kind_t abl, rate_t rate
)
{
	switch( trgt_kind ){
	case TRGT_KIND_MBR:
	case TRGT_KIND_MNSTR:
		return spell_attack( o_p, (chr_t *)d_p,
				resi, FALSE, abl, rate );
	case TRGT_KIND_ITEM:
		break_item( (item_t *)d_p, TRUE );
		break;
	case TRGT_KIND_DOOR:
		if( break_door( o_p, ((door_t *)d_p)->n ) ){
			print_msg_find( o_p, FLG_NULL,
					MSG_DOOR_BREAK, o_p->name );
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ��μ����Υ��ե�����
* chr_t *o_p : ����¦����饯��
* trgt_kind_t trgt_kind : �оݥ��֥������Ȥμ���
* void *trgt_p : �оݥ��֥�������
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_death_spell( chr_t *o_p, trgt_kind_t trgt_kind, void *trgt_p )
{
	chr_t	*d_p;
	long	o_lev, d_lev;
	static char	o_name[CHR_NAME_MAX_BYTE + 1];
	static char	d_name[CHR_NAME_MAX_BYTE + 1];

	if( trgt_kind != TRGT_KIND_MBR )
		if( trgt_kind != TRGT_KIND_MNSTR )
			return FALSE;
	d_p = (chr_t *)trgt_p;
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( !rate_randm( DEATH_SPELL_RATE ) )
		return FALSE;

	if( chk_resi_stat( d_p, FLG_STAT_DEAD ) ){
		print_msg_find( d_p, FLG_NULL,
				MSG_FX_RESI_STAT, d_p->name );
		return FALSE;
	}

	o_lev = get_specialist_lev( o_p );
	d_lev = get_specialist_lev( d_p );
	if( o_lev <= d_lev )
		return FALSE;

	str_nz_cpy( o_name, o_p->name, CHR_NAME_MAX_BYTE );
	str_nz_cpy( d_name, d_p->name, CHR_NAME_MAX_BYTE );

	die_chr( d_p, TRUE, FALSE, TRUE );

	curs_attrset_chr( d_p, -1, TRUE );
	print_msg_find( o_p, FLG_NULL, MSG_FIGHT_KILL_STD, o_name, d_name );
	curs_attrset_dflt();

	return TRUE;
}

/***************************************************************
* ǽ�����Ѳ��Υ��ե�����
* chr_t *chr : ����饯��
* fx_kind_t fx_kind : ���ι���μ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_abl( chr_t *chr, fx_kind_t fx_kind )
{
	long	turn;
	fx_t	*fx;
	fx_kind_t	deny_kind;

	if( chr == NULL )
		return FALSE;

	switch( fx_kind ){
	default:
		return FALSE;
	case FX_KIND_SHARPNESS:
	case FX_KIND_STRENGTH:
	case FX_KIND_QUICKNESS:
	case FX_KIND_BRAINY:
	case FX_KIND_WISE:
	case FX_KIND_ATTRACTIVE:
		turn = FX_AVE_TURN_POW_UP_ABL;
		break;
	case FX_KIND_DULLNESS:
	case FX_KIND_WEAKNESS:
	case FX_KIND_SLOWNESS:
	case FX_KIND_BRAINLESS:
	case FX_KIND_FOOLISH:
	case FX_KIND_UNATTRACTIVE:
		turn = FX_AVE_TURN_POW_DOWN_ABL;
		break;
	}

	switch( fx_kind ){
	default:
		return FALSE;
	case FX_KIND_SHARPNESS:
		deny_kind = FX_KIND_DULLNESS;
		break;
	case FX_KIND_DULLNESS:
		deny_kind = FX_KIND_SHARPNESS;
		break;
	case FX_KIND_STRENGTH:
		deny_kind = FX_KIND_WEAKNESS;
		break;
	case FX_KIND_WEAKNESS:
		deny_kind = FX_KIND_STRENGTH;
		break;
	case FX_KIND_QUICKNESS:
		deny_kind = FX_KIND_SLOWNESS;
		break;
	case FX_KIND_SLOWNESS:
		deny_kind = FX_KIND_QUICKNESS;
		break;
	case FX_KIND_BRAINY:
		deny_kind = FX_KIND_BRAINLESS;
		break;
	case FX_KIND_BRAINLESS:
		deny_kind = FX_KIND_BRAINY;
		break;
	case FX_KIND_WISE:
		deny_kind = FX_KIND_FOOLISH;
		break;
	case FX_KIND_FOOLISH:
		deny_kind = FX_KIND_WISE;
		break;
	case FX_KIND_ATTRACTIVE:
		deny_kind = FX_KIND_UNATTRACTIVE;
		break;
	case FX_KIND_UNATTRACTIVE:
		deny_kind = FX_KIND_ATTRACTIVE;
		break;
	}

	fx = srch_fx( &(chr->fx), deny_kind );
	if( fx != NULL ){
		clr_fx( fx );

		/* FALSE �ǤϤʤ� */
		return TRUE;
	}

	if( set_fx( chr, fx_kind, turn ) == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* �ɶ���Ϥ������Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_acid( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	if( is_mbr( chr ) )
		return fx_acid_mbr( chr );
	if( chr->kind == CHR_KIND_MNSTR )
		return fx_acid_mnstr( chr );

	return FALSE;
}

/***************************************************************
* ���Υ��ե����Ȥǥ��С����ɶ���Ϥ���
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_acid_mbr( mbr_t *mbr )
{
	item_t	*eq;
	long	i;
	equip_kind_t	eq_kind;
	long	n;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;

	eq_kind = EQUIP_KIND_MAX_N;
	n = 0;
	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		if( eq[i].kind == ITEM_KIND_ARMOR ){
			n++;
			if( randm( n ) == 0 ){
				eq_kind = (equip_kind_t)i;
			}
		}
	}
	if( n <= 0 )
		return FALSE;

	if( chk_flg( eq[eq_kind].flg, FLG_ITEM_PROTECTED ) ){
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_PROTECTED_ARMOR, mbr->name );
		return FALSE;
	}
	if( chk_randm_art( &(eq[eq_kind]) ) ){
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_PROTECTED_ARMOR, mbr->name );
		return FALSE;
	}

	switch( randm( 3 ) ){
	case 0:
		eq[eq_kind].dat.armor.add_def--;
		break;
	case 1:
		eq[eq_kind].dat.armor.add_crtcl--;
		break;
	case 2:
		eq[eq_kind].dat.armor.add_ac--;
		break;
	}
	set_item_name( &(eq[eq_kind]) );

	print_msg_find( mbr, FLG_NULL, MSG_FX_POW_DOWN_ARMOR, mbr->name );
	print_msg_find( mbr, FLG_NULL, MSG_S, eq[eq_kind].name );

	return TRUE;
}

/***************************************************************
* ���Υ��ե����Ȥǥ�󥹥������ɶ���Ϥ���
* mnstr_t *mnstr : ��󥹥���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_acid_mnstr( mnstr_t *mnstr )
{
	if( mnstr == NULL )
		return FALSE;
	if( mnstr->kind != CHR_KIND_MNSTR )
		return FALSE;

	switch( randm( 3 ) ){
	case 0:
		mnstr->add_def--;
		break;
	case 1:
		mnstr->add_crtcl--;
		break;
	case 2:
		mnstr->add_ac--;
		break;
	}

	return TRUE;
}

/***************************************************************
* �ǤΥ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_poison( chr_t *chr )
{
	fx_kind_t	kind;
	long	turn;
	fx_t	*fx;

	if( chr == NULL )
		return FALSE;

	kind = FX_KIND_POISON;
	turn = FX_AVE_TURN_POISON;

	fx = set_fx( chr, kind, turn );
	if( fx == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* HP �����Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_pow_up_hp( chr_t *chr )
{
	fx_t	*fx;

	if( chr == NULL )
		return FALSE;

	fx = set_fx( chr, FX_KIND_POW_UP_HP, FX_AVE_TURN_POW_UP_HP );
	if( fx == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* HP �����Υ��ե����Ȥ���
* fx_t *fx : ���ե�����
* long add_lev : ���������٥��
* return : ���̤�ͭ�ä���?
***************************************************************/

void	pow_up_hp( fx_t *fx, long add_lev )
{
	modifier_t	m;

	if( fx == NULL )
		return;
	if( fx->chr == NULL )
		return;

	get_modifier_fx( fx->chr, &m );
	m.add_lev[ABL_KIND_HP] += add_lev;
	set_modifier_fx( fx->chr, &m );
}

/***************************************************************
* �ɸ涯���Υ��ե�����
* chr_t *chr : ����饯��
* fx_kind_t kind : ���ե����Ȥμ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_magic_wpn_armor( chr_t *chr, fx_kind_t kind )
{
	long	turn;
	fx_t	*fx;

	if( chr == NULL )
		return FALSE;

	turn = 0;

	switch( kind ){
	case FX_KIND_MAGIC_SHIELD:
		turn = FX_AVE_TURN_MAGIC_SHIELD;
		break;
	case FX_KIND_MAGE_ARMOR:
		turn = FX_AVE_TURN_MAGE_ARMOR;
		break;
	case FX_KIND_SUBSTITUTE:
		turn = FX_AVE_TURN_SUBSTITUTE;
		break;
	case FX_KIND_BURNING_HANDS:
		turn = FX_AVE_TURN_BURNING_HANDS;
		break;
	case FX_KIND_RALLY:
		turn = FX_AVE_TURN_RALLY;
		break;
	case FX_KIND_IRON_MAN:
		turn = FX_AVE_TURN_IRON_MAN;
		break;
	case FX_KIND_MIND_READING:
		turn = FX_AVE_TURN_MIND_READING;
		break;
	default:
		return FALSE;
	}

	fx = set_fx( chr, kind, turn );
	if( fx == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* �����϶����Υ��ե����Ȥν����ͤ�����
* fx_t *fx : ���ե�����
* rate_t wpn_hit : �����Ϥν�����
* rate_t wpn_crtcl : ����ƥ����빶���Ϥν�����
* rate_t wpn_dam : ���᡼���ν�����
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	magic_wpn(
	fx_t *fx,
	rate_t wpn_hit, rate_t wpn_crtcl, rate_t wpn_dam
)
{
	modifier_t	m;

	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	get_modifier_fx( fx->chr, &m );
	m.wpn_hit += wpn_hit;
	m.wpn_crtcl += wpn_crtcl;
	m.wpn_dam += wpn_dam;
	set_modifier_fx( fx->chr, &m );

	return TRUE;
}

/***************************************************************
* �ɸ��϶����Υ��ե����Ȥν����ͤ�����
* fx_t *fx : ���ե�����
* rate_t armor_def : �ɸ��� �ν�����
* rate_t armor_crtcl : ����ƥ������ɸ��Ϥν�����
* rate_t armor_ac : �����ޡ����饹�ν�����
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	magic_armor(
	fx_t *fx,
	rate_t armor_def, rate_t armor_crtcl, rate_t armor_ac
)
{
	modifier_t	m;

	if( fx == NULL )
		return FALSE;
	if( fx->chr == NULL )
		return FALSE;

	get_modifier_fx( fx->chr, &m );
	m.armor_def += armor_def;
	m.armor_crtcl += armor_crtcl;
	m.armor_ac += armor_ac;
	set_modifier_fx( fx->chr, &m );

	return TRUE;
}

/***************************************************************
* ��ư®���Ѳ��Υ��ե�����
* chr_t *chr1 : �ݤ���¦�Υ���饯��
* chr_t *chr2 : �оݤΥ���饯��
* long add : ��ư®�٤��Ѳ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_speed_up( chr_t *chr1, chr_t *chr2, long add )
{
	abl_kind_t	max_abl2;
	fx_t	*fx;

	if( chr1->kind != chr2->kind ){
		max_abl2 = get_specialist_abl( chr2 );
		if( !roll( chr1, ABL_KIND_ENC, ABL_KIND_INT,
				chr2, max_abl2, max_abl2 ) ){
			return FALSE;
		}
	}

	if( add >= +1 ){
		fx = set_fx( chr2, FX_KIND_SPEED_UP,
				FX_AVE_TURN_SPEED_UP );
	} else if( add <= -1 ){
		fx = set_fx( chr2, FX_KIND_SPEED_DOWN,
				FX_AVE_TURN_SPEED_DOWN );
	} else {
		fx = NULL;
	}

	if( fx == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ��̿�ϵۼ��Υ��ե����Ȥ������С��˳ݤ���
* bool_t flg_set_max : �и��ͤ������ǽ�ˤ��뤫
***************************************************************/

void	fx_energy_drain_all_mbr( bool_t flg_set_max )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		fx_energy_drain( pty->mbr[i], flg_set_max );
}

/***************************************************************
* ��̿�ϵۼ��Υ��ե����Ȥ򥭥�饯���˳ݤ���
* chr_t *chr : ����饯��
* bool_t flg_set_max : �и��ͤ������ǽ�ˤ��뤫
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_energy_drain( chr_t *chr, bool_t flg_set_max )
{
	long	i;
	abl_kind_t	head, n;
	long	exp;

	if( chr == NULL )
		return FALSE;

	n = ABL_KIND_HP;
	head = (abl_kind_t)randm( ABL_KIND_MAX_N );
	for( i = 0; i < ABL_KIND_MAX_N; i++ ){
		n = (abl_kind_t)((head + i) % ABL_KIND_MAX_N);
		if( chr->abl.lev[n].n > 0 )
			break;
	}
	if( i >= ABL_KIND_MAX_N )
		return FALSE;

	/* get_lev() �Ǥʤ����ǤΥ�٥� */
	exp = calc_need_exp( chr->abl.lev[n].n, n ) - 1;
	if( exp < 0 )
		exp = 0;

	chr->abl.exp[n].n = exp;
	chk_lev_up( chr, flg_set_max, TRUE, TRUE );

	return TRUE;
}

/***************************************************************
* ����饯�������Ͷ����Υ��ե����Ȥ�����
* chr_t *chr : ����饯��
* fx_kind_t fx_kind : ���Ͷ����μ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_resi( chr_t *chr, fx_kind_t fx_kind )
{
	fx_t	*fx;

	if( chr == NULL )
		return FALSE;

	fx = set_fx( chr, fx_kind, FX_AVE_TURN_POW_UP_RESI );
	if( fx == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ����饯�������ͤ򶯲�
* chr_t *chr : ����饯��
* resi_kind_t resi : ���ͤμ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	pow_up_resi( chr_t *chr, resi_kind_t resi )
{
	return pow_up_down_resi( chr, resi, +1 );
}

/***************************************************************
* ����饯�������ͤ���β�
* chr_t *chr : ����饯��
* resi_kind_t resi : ���ͤμ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	pow_down_resi( chr_t *chr, resi_kind_t resi )
{
	return pow_up_down_resi( chr, resi, -1 );
}

/***************************************************************
* ����饯�������ͤ���
* chr_t *chr : ����饯��
* resi_kind_t resi : ���ͤμ���
* long n : ������
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	pow_up_down_resi( chr_t *chr, resi_kind_t resi, long n )
{
	modifier_t	m;
	long	prev_n;

	if( chr == NULL )
		return FALSE;

	get_modifier_fx( chr, &m );

	prev_n = m.add_resi_n[resi];
	m.add_resi_n[resi] += n;
	if( m.add_resi_n[resi] < ADD_RESI_MIN_N )
		m.add_resi_n[resi] = ADD_RESI_MIN_N;
	if( m.add_resi_n[resi] > ADD_RESI_MAX_N )
		m.add_resi_n[resi] = ADD_RESI_MAX_N;

	set_modifier_fx( chr, &m );

	return( prev_n != m.add_resi_n[resi] );
}

/***************************************************************
* ��󥹥����ξ����Υ��ե�����
* chr_t *chr : ����饯��
* pet_kind_t kind : �����äμ���
* long n : �����äο�
* long turn : �������
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_summon_monster( chr_t *chr, pet_kind_t kind, long n, long turn )
{
	abl_kind_t	abl_main, abl_sub;
	long	dun_lev;
	pet_t	*pet;
	bool_t	flg_mbr_pet;
	long	i;

	if( chr == NULL )
		return FALSE;

	flg_mbr_pet = FALSE;
	if( is_mbr( chr ) )
		flg_mbr_pet = TRUE;
	else if( is_pet( chr ) )
		flg_mbr_pet = TRUE;

	abl_main = ABL_KIND_SUM;
	abl_sub = get_sub_abl( abl_main );
	dun_lev = 0;
	dun_lev += get_lev( chr, abl_main );
	dun_lev += get_lev( chr, abl_sub );
	dun_lev /= 2;
	dun_lev = dun_lev * _100_PERCENT / RATE_LEV_PER_DUN_LEV;

	for( i = 0; i < n; i++ ){
		if( flg_mbr_pet ){
			pet = make_pet( dun_lev, kind, chr );
		} else {
			pet = make_mnstr( MAP_DEL_X, MAP_DEL_Y, FALSE,
					dun_lev, kind );
		}
		if( pet == NULL )
			break;

		pet->owner = chr;
		pet->flg_chr |= FLG_CHR_CAN_DISMISSAL;
		pet->work.dismissal_turn = turn;

		if( flg_mbr_pet ){
			if( !join_pet( pet ) ){
				dismissal( pet );
				break;
			}
		} else {
			appear_pet( pet );
		}

		draw_chr( pet );

		print_msg_find( pet, FLG_NULL,
				MSG_FX_SUMMON_MONSTER,
				pet->name );
	}
	if( i <= 0 )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ��󥹥��������ԤΥ��ե�����
* chr_t *chr : ������
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_dismissal( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;
	if( chr->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( !chk_flg( chr->flg_chr, FLG_CHR_CAN_DISMISSAL ) )
		return FALSE;

	print_msg_find( chr, FLG_NULL, MSG_FX_DISMISSAL, chr->name );

	return dismissal( chr );
}

/***************************************************************
* ������Υ�󥹥����ξ����Υ��ե�����
* chr_t *chr : ����饯��
* long turn : �������
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_summon_bone( chr_t *chr, long turn )
{
	if( chr == NULL )
		return FALSE;

	if( is_mbr( chr ) )
		return fx_summon_bone_mbr( chr, turn );
	else
		return fx_summon_bone_mnstr( chr, turn );
}

/***************************************************************
* ������Υ�󥹥����ξ���(���С�)
* mbr_t *mbr : ����饯��
* long turn : �������
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_summon_bone_mbr( mbr_t *mbr, long turn )
{
	item_t	*bone;
	mnstr_kind_t	kind;

	if( mbr == NULL )
		return FALSE;

	bone = exec_menu_sel_bone( mbr );
	if( bone == NULL )
		return FALSE;

	if( bone->dat.bone.mnstr_tab == NULL )
		return FALSE;
	kind = bone->dat.bone.mnstr_tab->mnstr_kind;
	if( kind == MNSTR_KIND_NULL )
		return FALSE;

	if( !fx_summon_monster( mbr, kind, 1, turn ) )
		return FALSE;

	inc_item( bone, -1 );

	return TRUE;
}

/***************************************************************
* ������Υ�󥹥����ξ���(��󥹥���)
* mnstr_t *mnstr : ����饯��
* long turn : �������
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_summon_bone_mnstr( mnstr_t *mnstr, long turn )
{
	if( mnstr == NULL )
		return FALSE;

	if( !fx_summon_monster( mnstr, mnstr->mnstr_kind, 1, turn ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* �����Ѥι�������
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

item_t	*exec_menu_sel_bone( mbr_t *mbr )
{
	menu_t	*ls;
	long	bone_n;
	item_t	*item, *p;
	long	j, k;

	if( mbr == NULL )
		return NULL;
	if( !is_mbr( mbr ) )
		return NULL;

	bone_n = 0;

	ls = ls_menu_summon_bone;
	k = 0;

	str_nz_cpy( ls[k].path, "/bone", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Branch>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	ls[k].msg[0] = '\0';
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	str_nz_cpy( ls[k].path, "/bone/--", MENU_PATH_MAX_LEN );
	str_nz_cpy( ls[k].kind, "<Title>", MENU_KIND_MAX_LEN );
	ls[k].accel_key = '\0';
	ls[k].short_key[0] = '\0';
	ls[k].n_msg = N_MSG_NULL;
	str_nz_cpy( ls[k].msg, mbr->name, MENU_MSG_MAX_BYTE );
	ls[k].call_back = NULL;
	ls[k].arg = NULL;
	ls[k].flg = FLG_NULL;
	k++;

	item = get_mbr_item_asgn( mbr );
	if( item == NULL )
		p = NULL;
	else
		p = item->next;
	for( j = 0; j < MBR_ITEM_MAX_N; j++, p = p->next ){
		if( p == NULL )
			break;
		if( p == item )
			break;

		if( p->kind == ITEM_KIND_BONE )
			bone_n++;
		else
			continue;

		sn_printf( ls[k].path, MENU_PATH_MAX_LEN,
				"/bone/%c",
				(char)('A' + j) );
		str_nz_cpy( ls[k].kind, "<Item>",
				MENU_KIND_MAX_LEN );
		ls[k].accel_key = (char)('A' + j);
		ls[k].short_key[0] = '\0';
		ls[k].n_msg = N_MSG_NULL;
		sn_printf( ls[k].msg, MENU_PATH_MAX_LEN,
				" %s", p->name );
		ls[k].call_back = cb_menu_sel_bone;
		ls[k].arg = (void *)p;
		ls[k].flg = FLG_NULL;
		k++;
	}

	ls[k].path[0] = '\0';

	if( bone_n <= 0 ){
		print_msg_find( mbr, FLG_MSG_ERR,
				MSG_FX_SUMMON_BONE_SEL_ERR,
				mbr->name );
		return NULL;
	}

	g_sel_bone = NULL;

	if( exec_menu( ls, NULL, NULL ) != NULL )
		return NULL;

	return g_sel_bone;
}

/***************************************************************
* �����Ѥι��������
* menu_t **pp : ��˥塼���ꥹ��
* menu_t **dflt : ��˥塼�Υǥե���Ȥ��������
* return : ��ư��Υ�˥塼���ѥ�
***************************************************************/

char	*cb_menu_sel_bone( menu_t **pp, menu_t **dflt )
{
	g_sel_bone = (item_t *)((*pp)->arg);

	return NULL;
}

/***************************************************************
* HP �������Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_hp_light( chr_t *chr, long lev )
{
	if( chr == NULL )
		return FALSE;

	if( !fx_cure_hp( chr, lev, CURE_HP_LIGHT_RATE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* HP ������Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_hp_moderate( chr_t *chr, long lev )
{
	if( chr == NULL )
		return FALSE;

	if( !fx_cure_hp( chr, lev, CURE_HP_MODERATE_RATE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* HP ������Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_hp_serious( chr_t *chr, long lev )
{
	if( chr == NULL )
		return FALSE;

	if( !fx_cure_hp( chr, lev, CURE_HP_SERIOUS_RATE ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* HP �������Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_hp_max( chr_t *chr, long lev )
{
	if( chr == NULL )
		return FALSE;

	curs_attrset_chr( chr, +1, TRUE );
	print_msg_find( chr, FLG_NULL, MSG_FX_CURE_HP_MAX, chr->name );
	curs_attrset_dflt();

	if( !fx_cure_hp( chr, lev, _100_PERCENT ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* HP �����Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_hp( chr_t *chr, long lev, rate_t rate )
{
	long	cure_n = 0;

	if( chr == NULL )
		return FALSE;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return FALSE;

	cure_n = calc_lev_to_val( lev, ABL_KIND_HP );
	cure_n = cure_n * rate / _100_PERCENT;
	if( cure_n == 0 )
		return FALSE;

	if( chr->face.mjr == FACE_MJR_MNSTR_UNDEAD ){
		cure_n = cure_n * CURE_HP_UNDEAD_RATE / _100_PERCENT;
		cure_n = -cure_n;
	}

	curs_attrset_chr( chr, +1, FALSE );
	print_msg_find( chr, FLG_NULL, MSG_FX_CURE_HP, chr->name, cure_n );
	curs_attrset_dflt();

	add_hp( chr, +cure_n, TRUE, FALSE );

	return TRUE;
}

/***************************************************************
* MP �������Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_mp_max( chr_t *chr, long lev )
{
	if( chr == NULL )
		return FALSE;

	curs_attrset_chr( chr, +1, TRUE );
	print_msg_find( chr, FLG_NULL, MSG_FX_CURE_MP_MAX, chr->name );
	curs_attrset_dflt();

	if( !fx_cure_mp( chr, lev, _100_PERCENT ) )
		return FALSE;

	return TRUE;
}

/***************************************************************
* MP �����Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_mp( chr_t *chr, long lev, rate_t rate )
{
	long	cure_n = 0;

	if( chr == NULL )
		return FALSE;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return FALSE;

	cure_n = calc_lev_to_val( lev, ABL_KIND_MP );
	cure_n = cure_n * rate / _100_PERCENT;
	if( cure_n == 0 )
		return FALSE;

	curs_attrset_chr( chr, +1, FALSE );
	print_msg_find( chr, FLG_NULL, MSG_FX_CURE_MP, chr->name, cure_n );
	curs_attrset_dflt();

	add_mp( chr, +cure_n, TRUE );

	return TRUE;
}

/***************************************************************
* ����ž���Υ��ե�����
* chr_t *chr : ����饯��
* spell_tab_t *tab : ��ʸ�Υǡ���
* rate_t rate : �����Ϥ�Ψ
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_transfer_mp( chr_t *chr, spell_tab_t *tab, rate_t rate )
{
	long	n;

	if( chr == NULL )
		return FALSE;
	if( tab == NULL )
		return FALSE;

	n = tab->mp;
	n = n * FX_TRANSFER_MP_RATE / _100_PERCENT;
	n = n * rate / _100_PERCENT;

	curs_attrset_chr( chr, +1, FALSE );
	print_msg_find( chr, FLG_NULL, MSG_FX_TRANSFER_MP,
			chr->name, n );
	curs_attrset_dflt();

	add_mp( chr, +n, FALSE );

	return TRUE;
}

/***************************************************************
* ��٥�����Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_lev( chr_t *chr )
{
	long	i;

	if( chr == NULL )
		return FALSE;

	for( i = 0; i < ABL_SKILL_MAX_N; i++ )
		chr->abl.lev[i].n = chr->abl.lev[i].max;

	curs_attrset_chr( chr, +1, FALSE );
	print_msg_find( chr, FLG_NULL, MSG_FX_CURE_LEV, chr->name );
	curs_attrset_dflt();

	return TRUE;
}

/***************************************************************
* �ѡ��ƥ��ηи��Ͳ����Υ��ե�����
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_exp_party( void )
{
	party_t	*pty = get_party();
	bool_t	flg_cure;
	long	i;

	flg_cure = FALSE;
	for( i = 0; i < MBR_MAX_N; i++ ){
		if( fx_cure_exp( pty->mbr[i] ) )
			flg_cure = TRUE;
	}

	return flg_cure;
}

/***************************************************************
* �и��Ͳ����Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_exp( chr_t *chr )
{
	long	i;

	if( chr == NULL )
		return FALSE;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return FALSE;

	curs_attrset_chr( chr, +1, FALSE );
	print_msg_find( chr, FLG_NULL, MSG_FX_CURE_EXP, chr->name );
	curs_attrset_dflt();

	for( i = 0; i < ABL_SKILL_MAX_N; i++ ){
		chr->abl.exp[i].n = chr->abl.exp[i].max;
		chk_lev_up( chr, TRUE, TRUE, TRUE );
	}

	return TRUE;
}

/***************************************************************
* �����Υ��ե�����
* chr_t *chr : ����饯��
* bool_t flg_put : ����饯����ޥåפ˽и������뤫?
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_resurrection( chr_t *chr, bool_t flg_put )
{
	rate_t	rate;

	if( chr == NULL )
		return FALSE;

	rate = _100_PERCENT - chr->fx_data.nicotine.poisoning_rate;
	rate *= (RESURRECTION_MAX_RATE - RESURRECTION_MIN_RATE);
	rate /= _100_PERCENT;
	rate += RESURRECTION_MIN_RATE;

	if( !rate_randm( rate ) ){
		print_msg( FLG_NULL, MSG_FX_RESURRECTION_FAILURE,
				chr->name );
		return FALSE;
	}

	if( !resurrection( chr, flg_put ) ){
		print_msg( FLG_NULL, MSG_FX_RESURRECTION_FAILURE,
				chr->name );
		return FALSE;
	}

	curs_attrset_chr( chr, +1, TRUE );
	print_msg( FLG_NULL, MSG_FX_RESURRECTION, chr->name );
	curs_attrset_dflt();

	return TRUE;
}

/***************************************************************
* ����饯��������
* chr_t *chr : ����饯��
* bool_t flg_put : ����饯����ޥåפ˽и������뤫?
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	resurrection( chr_t *chr, bool_t flg_put )
{
	if( chr == NULL )
		return FALSE;

	if( !chk_flg( chr->stat, FLG_STAT_DEAD ) )
		return FALSE;
	if( rate_randm( chr->fx_data.nicotine.lost_rate ) )
		return FALSE;

	chr->stat &= ~(FLG_STAT_DEAD);
	chr->abl.hp.n = chr->abl.hp.max;

	if( is_mbr( chr ) ){
		if( chr->mbr_n != MBR_N_NOT_JOIN ){
			if( flg_put ){
				pos_t	pos;

				get_square_mbr_map_pos( chr->mbr_n,
						&(pos.x), &(pos.y) );
				put_chr( chr, pos.x, pos.y );
			}
		}
	} else if( is_pet( chr ) ){
		long	x, y;

		if( chr->owner == NULL ){
			x = chr->pre_x;
			y = chr->pre_y;
		} else {
			x = chr->owner->x;
			y = chr->owner->y;
		}
		if( flg_put )
			put_chr( chr, x, y );
	} else {
		if( flg_put )
			put_chr( chr, chr->pre_x, chr->pre_y );
	}
	chr->pre_turn_x = chr->x;
	chr->pre_turn_y = chr->y;

	draw_mbr_stat( chr );

	return TRUE;
}

/***************************************************************
* ���������Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_heal( chr_t *chr )
{
	bool_t	flg;

	flg = FALSE;

	if( fx_cure_hp_max( chr, get_lev( chr, ABL_KIND_HP ) ) )
		flg = TRUE;
	if( fx_cure_all_stat( chr ) )
		flg = TRUE;

	return flg;
}

/***************************************************************
* ���ֲ����Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_all_stat( chr_t *chr )
{
	bool_t	flg;

	flg = FALSE;

	if( fx_cure_stat( chr, FX_KIND_STONE ) )
		flg = TRUE;
	if( fx_cure_stat( chr, FX_KIND_PARALYZE ) )
		flg = TRUE;
	if( fx_cure_stat( chr, FX_KIND_POISON ) )
		flg = TRUE;
	if( fx_cure_stat( chr, FX_KIND_CONFUSION ) )
		flg = TRUE;
	if( fx_cure_stat( chr, FX_KIND_BLIND ) )
		flg = TRUE;
	if( fx_cure_stat( chr, FX_KIND_SLEEP ) )
		flg = TRUE;
	if( fx_cure_stat( chr, FX_KIND_SILENCE ) )
		flg = TRUE;
	if( fx_cure_stat( chr, FX_KIND_FEAR ) )
		flg = TRUE;
	if( fx_cure_stat( chr, FX_KIND_HALLUCINATION ) )
		flg = TRUE;
	if( fx_cure_stat( chr, FX_KIND_CHARM ) )
		flg = TRUE;

	if( flg )
		draw_mbr_stat( chr );

	return flg;
}

/***************************************************************
* �ƾ��ֲ����Υ��ե�����
* chr_t *chr : ����饯��
* fx_kind_t fx_kind : ���ֲ����μ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_cure_stat( chr_t *chr, fx_kind_t fx_kind )
{
	fx_t	*fx, *fx_head;

	if( chr == NULL )
		return FALSE;

	fx_head = &(chr->fx);

	fx = srch_fx( fx_head, fx_kind );
	if( fx == NULL )
		return FALSE;

	clr_fx( fx );
	return TRUE;
}

/***************************************************************
* ��ʡ�Υ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_bless( chr_t *chr )
{
	fx_t	*fx;

	if( chr == NULL )
		return FALSE;

	fx = set_fx( chr, FX_KIND_BLESS, FX_AVE_TURN_BLESS );
	if( fx == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* �����������륨�ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_store_light( chr_t *chr )
{
	fx_t	*fx;

	if( chr == NULL )
		return FALSE;

	fx = set_fx( chr, FX_KIND_STORE_LIGHT, FX_AVE_TURN_STORE_LIGHT );
	if( fx == NULL )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ����Υ��ե�����
* chr_t *chr1 : �ݤ���¦�Υ���饯����NULL �Ǥ��ɤ���
* chr_t *chr2 : �оݤΥ���饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_remove_curse( chr_t *chr1, chr_t *chr2 )
{
	rate_t	difficulty;

	if( chr2 == NULL )
		return FALSE;

	difficulty = FX_REMOVE_CURSE_DIFFICULTY;

	return remove_curse( chr1, chr2, difficulty );
}

/***************************************************************
* ����Υ��ե�����
* chr_t *chr1 : �ݤ���¦�Υ���饯����NULL �Ǥ��ɤ���
* mbr_t *mbr2 : �оݤΥ��С�
* difficulty : �����
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	remove_curse( chr_t *chr1, mbr_t *mbr2, rate_t difficulty )
{
	abl_kind_t	abl_main, abl_sub;
	item_t	*head, *p;
	bool_t	flg;
	long	i;

	if( mbr2 == NULL )
		return FALSE;
	if( !is_mbr( mbr2 ) )
		return FALSE;

	flg = FALSE;

	abl_main = ABL_KIND_PRI;
	abl_sub = ABL_KIND_WIS;

	head = get_mbr_item_asgn( mbr2 );
	if( head == NULL )
		p = NULL;
	else
		p = head->next;
	for( ; p != head; p = p->next ){
		if( p == NULL )
			break;

		if( chk_flg( p->flg, FLG_ITEM_CURSED ) ){
			if( chr1 != NULL ){
				if( !chr_roll( chr1, abl_main, abl_sub,
						difficulty ) ){
					continue;
				}
			}

			flg = TRUE;
			p->flg &= ~(FLG_ITEM_CURSED);
			set_item_name( p );
		}
	}

	p = get_mbr_item_asgn_equip( mbr2 );
	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		if( p == NULL )
			break;

		if( chk_flg( p[i].flg, FLG_ITEM_CURSED ) ){
			if( chr1 != NULL ){
				if( !chr_roll( chr1, abl_main, abl_sub,
						difficulty ) ){
					continue;
				}
			}

			flg = TRUE;
			p[i].flg &= ~(FLG_ITEM_CURSED);
			set_item_name( &(p[i]) );
		}
	}

	if( flg ){
		curs_attrset_chr( mbr2, +1, FALSE );
		print_msg_find( mbr2, FLG_NULL,
				MSG_FX_REMOVE_CURSE_SUCCESS, mbr2->name );
	} else {
		curs_attrset_chr( mbr2, -1, FALSE );
		print_msg_find( mbr2, FLG_NULL,
				MSG_FX_REMOVE_CURSE_FAILURE, mbr2->name );
	}
	curs_attrset_dflt();

	return flg;
}

/***************************************************************
* ����ǥå��໶�Υ��ե�����
* chr_t *o_p : ����¦����饯��
* trgt_kind_t trgt_kind : �оݥ��֥������Ȥμ���
* void *d_p : �оݥ��֥�������
* rate_t rate : �����Ϥ�Ψ
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_dispel_undead(
	chr_t *o_p,
	trgt_kind_t trgt_kind, void *d_p,
	rate_t rate
)
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( trgt_kind != TRGT_KIND_MBR )
		if( trgt_kind != TRGT_KIND_MNSTR )
			return FALSE;

	if( ((chr_t *)d_p)->face.mjr != FACE_MJR_MNSTR_UNDEAD )
		return FALSE;

	rate = rate * DISPEL_UNDEAD_RATE / _100_PERCENT;
	return( fx_spell_attack( o_p, trgt_kind, d_p,
			RESI_KIND_ELEC, ABL_KIND_PRI, rate ) );
}

/***************************************************************
* �ݥ륿���������ȤΥ��ե�����
* chr_t *chr : ����饯��
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_poltergeist( chr_t *chr )
{
	dun_t	*dun = get_dun();
	item_t	*item, *head, *p;

	if( chr == NULL )
		return FALSE;
	if( !clip_pos( chr->x, chr->y ) )
		return FALSE;

	head = get_dun_item_asgn();
	for( item = head->next->next; item->prev != head;
			item = item->next ){
		long	i;

		p = item->prev;

		if( !clip_pos( p->x, p->y ) )
			continue;
		if( labs( chr->x - p->x ) > AREA_MAX_X )
			continue;
		if( labs( chr->y - p->y ) > AREA_MAX_Y )
			continue;

		dun->map.obj.mjr[p->y][p->x] = FACE_MJR_FLOOR;
		dun->map.obj.mnr[p->y][p->x] = FACE_MNR_FLOOR;
		draw_map( p->x, p->y, 1, 1 );

		for( i = 0; i < LOOP_MAX_4000; i++ ){
			long	x, y;

			x = p->x + randm( 3 ) - 1;
			y = p->y + randm( 3 ) - 1;
			if( !clip_pos( x, y ) )
				continue;
			if( dun->map.obj.mjr[y][x] != FACE_MJR_FLOOR )
				continue;
			if( dun->map.obj.mnr[y][x] != FACE_MNR_FLOOR )
				continue;

			p->x = x;
			p->y = y;
			break;
		}

		dun->map.obj.mjr[p->y][p->x] = p->mjr;
		dun->map.obj.mnr[p->y][p->x] = p->mnr;
		draw_item( p );
	}

	return TRUE;
}

/***************************************************************
* ���ι����϶����Υ��ե�����
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_pow_up_wpn_hit( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( (eq != NULL) && pow_up_wpn_hit( randm_wpn( eq ) ) ){
		curs_attrset_chr( mbr, +1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_WPN_HIT_SUCCESS,
				mbr->name );
		curs_attrset_dflt();

		return TRUE;
	} else {
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_WPN_HIT_FAILURE,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}
}

/***************************************************************
* ���Υ���ƥ����붯���Υ��ե�����
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_pow_up_wpn_crtcl( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( (eq != NULL) && pow_up_wpn_crtcl( randm_wpn( eq ) ) ){
		curs_attrset_chr( mbr, +1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_WPN_CRTCL_SUCCESS,
				mbr->name );
		curs_attrset_dflt();

		return TRUE;
	} else {
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_WPN_CRTCL_FAILURE,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}
}

/***************************************************************
* ���Υ��᡼�������Υ��ե�����
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_pow_up_wpn_dam( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( (eq != NULL) && pow_up_wpn_dam( randm_wpn( eq ) ) ){
		curs_attrset_chr( mbr, +1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_WPN_DAM_SUCCESS,
				mbr->name );
		curs_attrset_dflt();

		return TRUE;
	} else {
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_WPN_DAM_FAILURE,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}
}

/***************************************************************
* �ɶ���ɸ��϶����Υ��ե�����
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_pow_up_armor_def( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( (eq != NULL) && pow_up_armor_def( randm_armor( eq ) ) ){
		curs_attrset_chr( mbr, +1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_ARMOR_DEF_SUCCESS,
				mbr->name );
		curs_attrset_dflt();

		return TRUE;
	} else {
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_ARMOR_DEF_FAILURE,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}
}

/***************************************************************
* �ɶ�Υ���ƥ����붯���Υ��ե�����
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_pow_up_armor_crtcl( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( (eq != NULL) && pow_up_armor_crtcl( randm_armor( eq ) ) ){
		curs_attrset_chr( mbr, +1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_ARMOR_CRTCL_SUCCESS,
				mbr->name );
		curs_attrset_dflt();

		return TRUE;
	} else {
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_ARMOR_CRTCL_FAILURE,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}
}

/***************************************************************
* �ɶ�Υ����ޡ����饹�����Υ��ե�����
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_pow_up_armor_ac( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( (eq != NULL) && pow_up_armor_ac( randm_armor( eq ) ) ){
		curs_attrset_chr( mbr, +1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_ARMOR_AC_SUCCESS,
				mbr->name );
		curs_attrset_dflt();

		return TRUE;
	} else {
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_POW_UP_ARMOR_AC_FAILURE,
				mbr->name );
		curs_attrset_dflt();

		return FALSE;
	}
}

/***************************************************************
* �ɶ���ݸ�Υ��ե�����
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_protect_armor( mbr_t *mbr )
{
	item_t	*eq;
	bool_t	ret = FALSE;
	long	head, k, kk;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL ){
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_PROTECT_ARMOR_FAILURE,
				mbr->name );
		return FALSE;
	}

	head = randm( EQUIP_KIND_MAX_N );
	for( k = 0; k < EQUIP_KIND_MAX_N; k++ ){
		kk = (head + k) % EQUIP_KIND_MAX_N;

		if( protect_armor( &(eq[kk]) ) ){
			ret = TRUE;
			break;
		}
	}

	if( ret ){
		curs_attrset_chr( mbr, +1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_PROTECT_ARMOR_SUCCESS,
				mbr->name );
	} else {
		curs_attrset_chr( mbr, -1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_PROTECT_ARMOR_FAILURE,
				mbr->name );
	}
	curs_attrset_dflt();

	return ret;
}

/***************************************************************
* �֡�����Υ��ե�����
* mbr_t *mbr : ���С�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	fx_boomerang( mbr_t *mbr )
{
	item_t	*eq;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;

	eq = get_mbr_item_asgn_equip( mbr );

	do {
		if( eq == NULL )
			break;
		if( eq[EQUIP_KIND_ARW].kind != ITEM_KIND_WPN )
			break;
		if( chk_flg( eq[EQUIP_KIND_ARW].dat.wpn.flg,
				FLG_WPN_TAB_RET ) ){
			break;
		}

		eq[EQUIP_KIND_ARW].dat.wpn.flg |= FLG_WPN_TAB_RET;
		set_item_name( &(eq[EQUIP_KIND_ARW]) );

		curs_attrset_chr( mbr, +1, FALSE );
		print_msg_find( mbr, FLG_NULL,
				MSG_FX_BOOMERANG_SUCCESS, mbr->name );
		curs_attrset_dflt();

		return TRUE;
	} while( 0 );

	curs_attrset_chr( mbr, -1, FALSE );
	print_msg_find( mbr, FLG_NULL,
			MSG_FX_BOOMERANG_FAILURE, mbr->name );
	curs_attrset_dflt();

	return FALSE;
}

/***************************************************************
* ���ι����϶���
* item_t *wpn : ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	pow_up_wpn_hit( item_t *wpn )
{
	long	per;

	if( wpn == NULL )
		return FALSE;
	if( wpn->kind != ITEM_KIND_WPN )
		return FALSE;

	per = calc_per_pow_up_wpn_hit( wpn );
	if( !per_randm( per ) )
		return FALSE;

	wpn->dat.wpn.add_hit++;
	set_item_name( wpn );

	return TRUE;
}

/***************************************************************
* ���Υ���ƥ����붯��
* item_t *wpn : ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	pow_up_wpn_crtcl( item_t *wpn )
{
	long	per;

	if( wpn == NULL )
		return FALSE;
	if( wpn->kind != ITEM_KIND_WPN )
		return FALSE;

	per = calc_per_pow_up_wpn_crtcl( wpn );
	if( !per_randm( per ) )
		return FALSE;

	wpn->dat.wpn.add_crtcl++;
	set_item_name( wpn );

	return TRUE;
}

/***************************************************************
* ���Υ��᡼������
* item_t *wpn : ���
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	pow_up_wpn_dam( item_t *wpn )
{
	long	per;

	if( wpn == NULL )
		return FALSE;
	if( wpn->kind != ITEM_KIND_WPN )
		return FALSE;

	per = calc_per_pow_up_wpn_dam( wpn );
	if( !per_randm( per ) )
		return FALSE;

	wpn->dat.wpn.add_dam++;
	set_item_name( wpn );

	return TRUE;
}

/***************************************************************
* �ɶ���ɸ��϶���
* item_t *armor : �ɶ�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	pow_up_armor_def( item_t *armor )
{
	long	per;

	if( armor == NULL )
		return FALSE;
	if( armor->kind != ITEM_KIND_ARMOR )
		return FALSE;

	per = calc_per_pow_up_armor_def( armor );
	if( !per_randm( per ) )
		return FALSE;

	armor->dat.armor.add_def++;
	set_item_name( armor );

	return TRUE;
}

/***************************************************************
* �ɶ�Υ���ƥ����붯��
* item_t *armor : �ɶ�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	pow_up_armor_crtcl( item_t *armor )
{
	long	per;

	if( armor == NULL )
		return FALSE;
	if( armor->kind != ITEM_KIND_ARMOR )
		return FALSE;

	per = calc_per_pow_up_armor_crtcl( armor );
	if( !per_randm( per ) )
		return FALSE;

	armor->dat.armor.add_crtcl++;
	set_item_name( armor );

	return TRUE;
}

/***************************************************************
* �ɶ�Υ����ޡ����饹����
* item_t *armor : �ɶ�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	pow_up_armor_ac( item_t *armor )
{
	long	per;

	if( armor == NULL )
		return FALSE;
	if( armor->kind != ITEM_KIND_ARMOR )
		return FALSE;

	per = calc_per_pow_up_armor_ac( armor );
	if( !per_randm( per ) )
		return FALSE;

	armor->dat.armor.add_ac++;
	set_item_name( armor );

	return TRUE;
}

/***************************************************************
* ���ι����϶�����������Ψ���֤�
* item_t *wpn : ���
* return : ������Ψ
***************************************************************/

long	calc_per_pow_up_wpn_hit( item_t *wpn )
{
	return calc_per_pow_up_wpn( wpn );
}

/***************************************************************
* ���Υ���ƥ����붯����������Ψ���֤�
* item_t *wpn : ���
* return : ������Ψ
***************************************************************/

long	calc_per_pow_up_wpn_crtcl( item_t *wpn )
{
	return calc_per_pow_up_wpn( wpn );
}

/***************************************************************
* ���Υ��᡼��������������Ψ���֤�
* item_t *wpn : ���
* return : ������Ψ
***************************************************************/

long	calc_per_pow_up_wpn_dam( item_t *wpn )
{
	return calc_per_pow_up_wpn( wpn );
}

/***************************************************************
* ���ζ�����������Ψ���֤�
* item_t *wpn : ���
* return : ������Ψ
***************************************************************/

long	calc_per_pow_up_wpn( item_t *wpn )
{
	long	per;

	if( wpn == NULL )
		return 1;
	if( wpn->kind != ITEM_KIND_WPN )
		return 1;

	per = 0;
	per += wpn->dat.wpn.add_hit;
	per += wpn->dat.wpn.add_crtcl;
	per += wpn->dat.wpn.add_dam;

	per = per * per;
	per /= 3 * 3;

	if( per < 1 )
		per = 1;

	return per;
}

/***************************************************************
* �ɶ���ɸ��϶�����������Ψ���֤�
* item_t *armor : �ɶ�
* return : ������Ψ
***************************************************************/

long	calc_per_pow_up_armor_def( item_t *armor )
{
	return calc_per_pow_up_armor( armor );
}

/***************************************************************
* �ɶ�Υ���ƥ����붯����������Ψ���֤�
* item_t *armor : �ɶ�
* return : ������Ψ
***************************************************************/

long	calc_per_pow_up_armor_crtcl( item_t *armor )
{
	return calc_per_pow_up_armor( armor );
}

/***************************************************************
* �ɶ�Υ����ޡ����饹������������Ψ���֤�
* item_t *armor : �ɶ�
* return : ������Ψ
***************************************************************/

long	calc_per_pow_up_armor_ac( item_t *armor )
{
	return calc_per_pow_up_armor( armor );
}

/***************************************************************
* �ɶ�ζ�����������Ψ���֤�
* item_t *armor : �ɶ�
* return : ������Ψ
***************************************************************/

long	calc_per_pow_up_armor( item_t *armor )
{
	long	per;

	if( armor == NULL )
		return 1;
	if( armor->kind != ITEM_KIND_ARMOR )
		return 1;

	per = 0;
	per += armor->dat.armor.add_def;
	per += armor->dat.armor.add_crtcl;
	per += armor->dat.armor.add_ac;

	per = per * per;
	per /= 3 * 3;

	if( per < 1 )
		per = 1;

	return per;
}

/***************************************************************
* �ɶ���ݸ�
* item_t *armor : �ɶ�
* return : ���̤�ͭ�ä���?
***************************************************************/

bool_t	protect_armor( item_t *armor )
{
	if( armor == NULL )
		return FALSE;
	if( armor->kind != ITEM_KIND_ARMOR )
		return FALSE;
	if( chk_flg( armor->flg, FLG_ITEM_PROTECTED ) )
		return FALSE;

	armor->flg |= FLG_ITEM_PROTECTED;
	set_item_name( armor );

	return TRUE;
}

/***************************************************************
* ��ʸ���ɲäθ���
* chr_t *chr : ����饯��
* spell_tab_t *tab : ��ʸ�Υǡ���
***************************************************************/

void	fx_cast_spell( chr_t *chr, spell_tab_t *tab )
{
	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	if( tab->kind == SPELL_KIND_WORD_OF_DESTRUCTION )
		fx_word_of_destruction( chr, tab );
}

/***************************************************************
* �˲��μ�ʸ���ɲäθ���
* chr_t *chr : ����饯��
* spell_tab_t *tab : ��ʸ�Υǡ���
***************************************************************/

void	fx_word_of_destruction( chr_t *chr, spell_tab_t *tab )
{
	dun_t	*dun = get_dun();
	blast_t	*blast;
	char	*blast_str;
	gui_vfx_t	*gui_vfx;
	long	nx, ny;
	long	xx, yy;
	chr_kind_t	kind;

	if( chr == NULL )
		return;
	if( tab == NULL )
		return;

	if( is_mbr( chr ) )
		kind = CHR_KIND_MNSTR;
	else if( is_pet( chr ) )
		kind = CHR_KIND_MNSTR;
	else if( chr->kind == CHR_KIND_MNSTR )
		kind = CHR_KIND_MBR;
	else
		kind = CHR_KIND_NULL;

	call_game_sound_play( SOUND_KIND_BLAST_DESTRUCTION, 1 );

	/* ���� */

	/* GUI */
	gui_vfx = alloc_gui_vfx_blast( BLAST_KIND_WORD_OF_DESTRUCTION );

	blast = get_blast_spell( tab->kind );
	blast_str = get_spell_vfx_str( tab->kind );
	draw_blast( kind, chr->x, chr->y, blast, gui_vfx, blast_str );

	wait_clock( ANIM_FRAME_N_BLAST_DESTRUCTION );

	/* ���줿������֤��� */

	for( ny = 0; ny < blast->yl; ny++ ){
		for( nx = 0; nx < blast->xl / 2; nx++ ){
			if( blast->ptn[ny][nx * 2] == blast->transmit_chr )
				continue;

			xx = chr->x + nx - (blast->xr / 2);
			yy = chr->y + ny - blast->yr;

			dun->map.obj.flg[yy][xx] &= ~(FLG_MAP_OBJ_FIND);
			dun->map.light_depth_obj[yy][xx] = 0;

			if( (nx % 2) == (ny % 2) )
				continue;
			if( !rate_randm( WORD_OF_DESTRUCTION_WALL_RATE ) )
				continue;
			if( dun->map.obj.mjr[yy][xx] != FACE_MJR_FLOOR )
				continue;
			if( dun->map.obj.mnr[yy][xx] != FACE_MNR_FLOOR )
				continue;
			if( dun->map.chr.mjr[yy][xx] != FACE_MJR_NULL )
				continue;

			dun->map.obj.mjr[yy][xx] = FACE_MJR_WALL;
			dun->map.obj.mnr[yy][xx] = FACE_MNR_WALL;
			dun->map.obj.flg[yy][xx] &=
					~(FLG_MAP_OBJ_PASS
					| FLG_MAP_OBJ_LOOK);
		}
	}

	/* GUI */
	clr_gui_vfx_all();
	free_gui_vfx( gui_vfx );
	call_pcg_dun_redraw( TRUE );

	redraw_map_force();
}

/***************************************************************
* ����饯�������פ򤳤���
* chr_t *chr : ����饯��
* item_t *item : ����
* return : �����줿��?
***************************************************************/

bool_t	rub_lamp( chr_t *chr, item_t *item )
{
	if( chr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_LIGHT )
		return FALSE;
	if( item->dat.light.kind != LIGHT_KIND_LAMP )
		return FALSE;

	print_msg_find( chr, FLG_NULL,
			MSG_RUB_LAMP, chr->name, item->name );

	if( item->dat.light.wish_level == WISH_LEVEL_NULL ){
		print_msg_find( chr, FLG_NULL,
				MSG_FX_RUB_LAMP_FAILURE, item->name );
	} else {
		print_msg_find( chr, FLG_NULL,
				MSG_FX_RUB_LAMP_SUCCESS, item->name );

		fx_wish( chr, item->dat.light.wish_level );
	}

	return TRUE;
}

/***************************************************************
* ˾��
* chr_t *chr : ����饯��
* wish_level_t wish_level : ����μ���
* return : ˾�ߤ��𤨤�줿��?
***************************************************************/

bool_t	fx_wish( chr_t *chr, wish_level_t wish_level )
{
	wish_kind_t	kind;

	if( !is_mbr( chr ) )
		return TRUE;

	kind = exec_menu_wish( (mbr_t *)chr, wish_level );
	if( kind == WISH_KIND_NULL )
		return FALSE;

	if( !fx_wish_chk_price( chr, wish_level, kind ) )
		return FALSE;
	if( !fx_wish_exec( chr, wish_level, kind ) )
		return FALSE;
	if( !fx_wish_pay_price( chr, wish_level, kind ) )
		return TRUE;	/* FALSE */

	return TRUE;
}

/***************************************************************
* ˾�ߤ������ʧ���뤫Ĵ�٤�
* chr_t *chr : ����饯��
* wish_level_t wish_level : ����μ���
* wish_kind_t kind : ˾�ߤμ���
* return : ˾�ߤ��𤨤�줿��?
***************************************************************/

bool_t	fx_wish_chk_price(
	chr_t *chr,
	wish_level_t wish_level,
	wish_kind_t kind
)
{
	switch( wish_level ){
	case WISH_LEVEL_NULL:
	case WISH_LEVEL_ARMAGEDDON:
		break;
	case WISH_LEVEL_DAEMON:
		if( !chk_wish_price_exp( chr, kind ) )
			return FALSE;
		break;
	case WISH_LEVEL_DJINNI:
		if( !chk_wish_price_gold( chr, kind ) )
			return FALSE;
		break;
	case WISH_LEVEL_GOD:
		if( !chk_wish_price_contribution( chr, kind ) )
			return FALSE;
		break;
	case WISH_LEVEL_MAX_N:
		break;
	}

	return TRUE;
}

/***************************************************************
* ˾�ߤ�𤨤�
* chr_t *chr : ����饯��
* wish_level_t wish_level : ����μ���
* wish_kind_t kind : ˾�ߤμ���
* return : ˾�ߤ��𤨤�줿��?
***************************************************************/

bool_t	fx_wish_exec(
	chr_t *chr,
	wish_level_t wish_level,
	wish_kind_t kind
)
{
	switch( kind ){
	case WISH_KIND_NULL:
	case WISH_KIND_ARMAGEDDON:
		if( !fx_wish_armageddon( chr, wish_level ) )
			return FALSE;
		break;
	case WISH_KIND_CURE_HP:
		if( !fx_wish_cure_hp( chr, wish_level ) )
			return FALSE;
		break;
	case WISH_KIND_CURE_MP:
		if( !fx_wish_cure_mp( chr, wish_level ) )
			return FALSE;
		break;
	case WISH_KIND_RESURRECTION:
		if( !fx_wish_resurrection( chr, wish_level ) )
			return FALSE;
		break;
	case WISH_KIND_ARTIFACT:
		if( !fx_wish_artifact( chr, wish_level ) )
			return FALSE;
		break;
	case WISH_KIND_MAX_N:
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ˾�ߤ������ʧ��
* chr_t *chr : ����饯��
* wish_level_t wish_level : ����μ���
* wish_kind_t kind : ˾�ߤμ���
* return : ˾�ߤ��𤨤�줿��?
***************************************************************/

bool_t	fx_wish_pay_price(
	chr_t *chr,
	wish_level_t wish_level,
	wish_kind_t kind
)
{
	switch( wish_level ){
	case WISH_LEVEL_NULL:
	case WISH_LEVEL_ARMAGEDDON:
		break;
	case WISH_LEVEL_DAEMON:
		pay_wish_price_exp( chr, kind );
		break;
	case WISH_LEVEL_DJINNI:
		pay_wish_price_gold( chr, kind );
		break;
	case WISH_LEVEL_GOD:
		pay_wish_price_contribution( chr, kind );
		break;
	case WISH_LEVEL_MAX_N:
		break;
	}

	return TRUE;
}

/***************************************************************
* ˾�ߤ������и��ͤǻ�ʧ���뤫Ĵ�٤�
* chr_t *chr : ����饯��
* wish_kind_t kind : ˾�ߤμ���
* return : ��ʧ���뤫?
***************************************************************/

bool_t	chk_wish_price_exp( chr_t *chr, wish_kind_t kind )
{
	long	price, exp;

	if( chr == NULL )
		return FALSE;

	price = calc_wish_price_exp( chr, kind );
	exp = get_exp( chr, get_specialist_abl( chr ) );

	if( exp < price ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_EXP_SHORT,
				chr->name, price - exp );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ˾�ߤ�������ǻ�ʧ���뤫Ĵ�٤�
* chr_t *chr : ����饯��
* wish_kind_t kind : ˾�ߤμ���
* return : ��ʧ���뤫?
***************************************************************/

bool_t	chk_wish_price_gold( chr_t *chr, wish_kind_t kind )
{
	gold_t	price, gold;

	if( chr == NULL )
		return FALSE;

	price = calc_wish_price_gold( chr, kind );
	gold = get_chr_gold( chr );

	if( gold < price ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_GOLD_SHORT,
				chr->name, price - gold );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ˾�ߤ��������դǻ�ʧ���뤫Ĵ�٤�
* chr_t *chr : ����饯��
* wish_kind_t kind : ˾�ߤμ���
* return : ��ʧ���뤫?
***************************************************************/

bool_t	chk_wish_price_contribution( chr_t *chr, wish_kind_t kind )
{
	gold_t	price, gold;

	if( chr == NULL )
		return FALSE;

	price = calc_wish_price_gold( chr, kind );
	gold = chr->contribution;

	if( gold < price ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_CONTRIBUTION_SHORT,
				chr->name, price - gold );
		return FALSE;
	}

	if( !chr->work.flg_can_wish ){
		print_msg_mbr( chr, FLG_NULL, MSG_ERR_CONTRIBUTION_DAY,
				chr->name );
		return FALSE;
	}

	return TRUE;
}

/***************************************************************
* ˾�ߤ������и��ͤǻ�ʧ��
* chr_t *chr : ����饯��
* wish_kind_t kind : ˾�ߤμ���
***************************************************************/

void	pay_wish_price_exp( chr_t *chr, wish_kind_t kind )
{
	long	price;

	if( chr == NULL )
		return;

	price = calc_wish_price_exp( chr, kind );
	exp_chr( chr, -price, TRUE, TRUE, TRUE );
}

/***************************************************************
* ˾�ߤ�������ǻ�ʧ��
* chr_t *chr : ����饯��
* wish_kind_t kind : ˾�ߤμ���
***************************************************************/

void	pay_wish_price_gold( chr_t *chr, wish_kind_t kind )
{
	gold_t	price;

	if( chr == NULL )
		return;

	price = calc_wish_price_gold( chr, kind );
	add_chr_gold( chr, -price );
}

/***************************************************************
* ˾�ߤ��������դǻ�ʧ��
* chr_t *chr : ����饯��
* wish_kind_t kind : ˾�ߤμ���
***************************************************************/

void	pay_wish_price_contribution( chr_t *chr, wish_kind_t kind )
{
	gold_t	price;

	if( chr == NULL )
		return;

	price = calc_wish_price_contribution( chr, kind );
	chr->contribution -= price;

	chr->work.flg_can_wish = FALSE;
}

/***************************************************************
* ˾�ߤ�����ηи��ͤ�׻�
* chr_t *chr : ����饯��
* wish_kind_t kind : ˾�ߤμ���
* return : �и���
***************************************************************/

long	calc_wish_price_exp( chr_t *chr, wish_kind_t kind )
{
	if( chr == NULL )
		return 0;

	return WISH_PRICE_EXP;
}

/***************************************************************
* ˾�ߤ�����ζ�ۤ�׻�
* chr_t *chr : ����饯��
* wish_kind_t kind : ˾�ߤμ���
* return : ���
***************************************************************/

gold_t	calc_wish_price_gold( chr_t *chr, wish_kind_t kind )
{
	if( chr == NULL )
		return 0;

	return WISH_PRICE_GOLD;
}

/***************************************************************
* ˾�ߤ�����δ��ճۤ�׻�
* chr_t *chr : ����饯��
* wish_kind_t kind : ˾�ߤμ���
* return : ���ճ�
***************************************************************/

gold_t	calc_wish_price_contribution( chr_t *chr, wish_kind_t kind )
{
	if( chr == NULL )
		return 0;

	return WISH_PRICE_CONTRIBUTION;
}

/***************************************************************
* ˾�ߤ�����
* mbr_t *mbr : ���С�
* wish_level_t wish_level : ����μ���
* return : ���򤵤줿˾�ߤμ���
***************************************************************/

wish_kind_t	exec_menu_wish( mbr_t *mbr, wish_level_t wish_level )
{
	menu_t	*ls;
	ask_t	ask;

	if( mbr == NULL )
		return WISH_KIND_NULL;
	if( !is_mbr( mbr ) )
		return WISH_KIND_NULL;

	ls = NULL;
	switch( wish_level ){
	case WISH_LEVEL_NULL:
		break;
	case WISH_LEVEL_ARMAGEDDON:
		print_words( MSG_MNSTR_DJINNI, MALE,
				MSG_WORDS_WISH_ARMAGEDDON,
				MSG_WORDS_WISH_ARMAGEDDON );

		ask = exec_menu_ask(
				MSG_TTL_MENU_WISH_ARMAGEDDON,
				ASK_NO, FALSE );
		if( ask == ASK_YES ){
			print_words( MSG_MNSTR_DJINNI, MALE,
					MSG_WORDS_WISH_ARMAGEDDON_YES,
					MSG_WORDS_WISH_ARMAGEDDON_YES );
			return WISH_KIND_ARMAGEDDON;
		} else {
			print_words( MSG_MNSTR_DJINNI, MALE,
					MSG_WORDS_WISH_ARMAGEDDON_NO,
					MSG_WORDS_WISH_ARMAGEDDON_NO );
			return WISH_KIND_NULL;
		}
		break;
	case WISH_LEVEL_DAEMON:
		ls = ls_menu_wish;
		print_words( MSG_MNSTR_DJINNI, MALE,
				MSG_WORDS_WISH_DAEMON,
				MSG_WORDS_WISH_DAEMON );
		break;
	case WISH_LEVEL_DJINNI:
		ls = ls_menu_wish;
		print_words( MSG_MNSTR_DJINNI, MALE,
				MSG_WORDS_WISH_DJINNI,
				MSG_WORDS_WISH_DJINNI );
		break;
	case WISH_LEVEL_GOD:
		ls = ls_menu_wish;
		print_words( MSG_MNSTR_DJINNI, MALE,
				MSG_WORDS_WISH_GOD,
				MSG_WORDS_WISH_GOD );
		break;
	case WISH_LEVEL_MAX_N:
		break;
	}
	if( ls == NULL )
		return WISH_KIND_NULL;

	g_sel_wish = WISH_KIND_NULL;

	while( 1 ){
		char	*str;

		str = exec_menu( ls, NULL, NULL );

		if( str == NULL )
			return g_sel_wish;

		if( strcmp( str, STR_MENU_CANCEL ) == 0 ){
			ask_t	ask;

			ask = exec_menu_ask(
					MSG_TTL_MENU_WISH_ASK_CANCEL,
					ASK_NO, TRUE );
			if( ask == ASK_YES )
				return WISH_KIND_NULL;
		}

		if( strcmp( str, STR_MENU_ERR ) == 0 )
			return WISH_KIND_NULL;
	}

	return WISH_KIND_NULL;
}

/***************************************************************
* ���򤷤�˾�ߤ򵭲�
* menu_t **pp : ��˥塼���ꥹ��
* menu_t **dflt : ��˥塼�Υǥե���Ȥ��������
* return : ��ư��Υ�˥塼���ѥ�
***************************************************************/

char	*cb_menu_sel_wish( menu_t **pp, menu_t **dflt )
{
	g_sel_wish = (wish_kind_t)(long)((*pp)->arg);

	return NULL;
}

/***************************************************************
* HP ������˾��
* chr_t *chr : ����饯��
* wish_level_t wish_level : ����μ���
* return : ˾�ߤ��𤨤�줿��?
***************************************************************/

bool_t	fx_wish_armageddon( chr_t *chr, wish_level_t wish_level )
{
	/*@@@*/
	print_msg( FLG_MSG_ERR, MSG_INCOMPLETE );
	return FALSE;
}

/***************************************************************
* HP ������˾��
* chr_t *chr : ����饯��
* wish_level_t wish_level : ����μ���
* return : ˾�ߤ��𤨤�줿��?
***************************************************************/

bool_t	fx_wish_cure_hp( chr_t *chr, wish_level_t wish_level )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		fx_cure_hp_max( pty->mbr[i], get_lev( chr, ABL_KIND_HP ) );
		fx_cure_all_stat( pty->mbr[i] );
	}

	return TRUE;
}

/***************************************************************
* MP ������˾��
* chr_t *chr : ����饯��
* wish_level_t wish_level : ����μ���
* return : ˾�ߤ��𤨤�줿��?
***************************************************************/

bool_t	fx_wish_cure_mp( chr_t *chr, wish_level_t wish_level )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		fx_cure_mp_max( pty->mbr[i], get_lev( chr, ABL_KIND_MP ) );
	}

	return TRUE;
}

/***************************************************************
* ������˾��
* chr_t *chr : ����饯��
* wish_level_t wish_level : ����μ���
* return : ˾�ߤ��𤨤�줿��?
***************************************************************/

bool_t	fx_wish_resurrection( chr_t *chr, wish_level_t wish_level )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ ){
		fx_resurrection( pty->mbr[i], TRUE );
	}

	return TRUE;
}

/***************************************************************
* �����ƥ��ե����Ȥ�˾��
* chr_t *chr : ����饯��
* wish_level_t wish_level : ����μ���
* return : ˾�ߤ��𤨤�줿��?
***************************************************************/

bool_t	fx_wish_artifact( chr_t *chr, wish_level_t wish_level )
{
	if( rate_randm( 50 ) )
		return fx_wish_artifact_wpn( chr, wish_level );
	else
		return fx_wish_artifact_armor( chr, wish_level );
}

/***************************************************************
* Ϳ���᡼���ΰ����� HP ��ۼ�
* chr_t *o_p : ����¦����饯��
* chr_t *d_p : �ɸ�¦����饯��
* long o_dam : ���᡼��
* bool_t flg_throw : ����ƻ��?
* return : �ۼ�������?
***************************************************************/

bool_t	fx_wpn_randm_art_drain(
	char mnr,
	chr_t *o_p, chr_t *d_p,
	long o_dam, bool_t flg_throw
)
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( !is_mbr( o_p ) )
		return FALSE;
	if( is_mbr( d_p ) )
		return FALSE;
	if( is_pet( d_p ) )
		return FALSE;

	/* ����ǥåȤʤ�ۼ��Ǥ��ʤ� */

	if( d_p->mnstr_tab == NULL )
		return FALSE;
	if( d_p->mnstr_tab->face_mjr == FACE_MJR_MNSTR_UNDEAD )
		return FALSE;

	switch( mnr ){
	case WPN_RANDM_ART_MNR_DRAIN_HP:
		if( fx_wpn_randm_art_drain_hp(
				o_p, d_p, o_dam, flg_throw ) ){
			return TRUE;
		}
		break;
	case WPN_RANDM_ART_MNR_DRAIN_MP:
		if( fx_wpn_randm_art_drain_mp(
				o_p, d_p, o_dam, flg_throw ) ){
			return TRUE;
		}
		break;
	case WPN_RANDM_ART_MNR_DRAIN_EXP:
		if( fx_wpn_randm_art_drain_exp(
				o_p, d_p, o_dam, flg_throw ) ){
			return TRUE;
		}
		break;
	}

	return FALSE;
}

/***************************************************************
* Ϳ���᡼���ΰ����� HP ��ۼ�
* chr_t *o_p : ����¦����饯��
* chr_t *d_p : �ɸ�¦����饯��
* long o_dam : ���᡼��
* item_t *item : ���Ѥ������
* return : �ۼ�������?
***************************************************************/

bool_t	fx_wpn_randm_art_drain_hp(
	chr_t *o_p, chr_t *d_p,
	long o_dam, bool_t flg_throw
)
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( !is_mbr( o_p ) )
		return FALSE;
	if( is_mbr( d_p ) )
		return FALSE;
	if( is_pet( d_p ) )
		return FALSE;

	if( o_dam <= 0 )
		return FALSE;

	if( !chk_wpn_randm_art( WPN_RANDM_ART_KIND_DRAIN,
			WPN_RANDM_ART_MNR_DRAIN_HP, o_p, d_p,
			flg_throw ) ){
		return FALSE;
	}

	o_dam = o_dam * WPN_RANDM_ART_DRAIN_HP_RATE / _100_PERCENT;
	if( o_dam < 1 )
		o_dam = 1;
	o_dam = randm( o_dam + 1 );
	if( o_dam <= 0 )
		return FALSE;

	curs_attrset_chr( o_p, +1, FALSE );
	print_msg( FLG_NULL, MSG_FX_WPN_RANDM_ART_DRAIN_HP,
			o_p->name, o_dam );
	curs_attrset_dflt();

	add_hp( o_p, +o_dam, TRUE, FALSE );

	return TRUE;
}

/***************************************************************
* Ϳ���᡼���� MP ��ۼ�
* chr_t *o_p : ����¦����饯��
* chr_t *d_p : �ɸ�¦����饯��
* long o_dam : ���᡼��
* item_t *item : ���Ѥ������
* return : �ۼ�������?
***************************************************************/

bool_t	fx_wpn_randm_art_drain_mp(
	chr_t *o_p, chr_t *d_p,
	long o_dam, bool_t flg_throw
)
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( !is_mbr( o_p ) )
		return FALSE;
	if( is_mbr( d_p ) )
		return FALSE;
	if( is_pet( d_p ) )
		return FALSE;

	if( o_dam <= 0 )
		return FALSE;

	if( !chk_wpn_randm_art( WPN_RANDM_ART_KIND_DRAIN,
			WPN_RANDM_ART_MNR_DRAIN_MP, o_p, d_p,
			flg_throw ) ){
		return FALSE;
	}

	o_dam = o_dam * WPN_RANDM_ART_DRAIN_MP_RATE / _100_PERCENT;
	if( o_dam < 1 )
		o_dam = 1;
	o_dam = randm( o_dam + 1 );
	if( o_dam <= 0 )
		return FALSE;

	curs_attrset_chr( o_p, +1, FALSE );
	print_msg( FLG_NULL, MSG_FX_WPN_RANDM_ART_DRAIN_MP,
			o_p->name, o_dam );
	curs_attrset_dflt();

	add_mp( d_p, -o_dam, FALSE );
	add_mp( o_p, +o_dam, TRUE );

	return TRUE;
}

/***************************************************************
* Ϳ���᡼���� EXP ��ۼ�
* chr_t *o_p : ����¦����饯��
* chr_t *d_p : �ɸ�¦����饯��
* long o_dam : ���᡼��
* item_t *item : ���Ѥ������
* return : �ۼ�������?
***************************************************************/

bool_t	fx_wpn_randm_art_drain_exp(
	chr_t *o_p, chr_t *d_p,
	long o_dam, bool_t flg_throw
)
{
	if( o_p == NULL )
		return FALSE;
	if( d_p == NULL )
		return FALSE;

	if( !is_mbr( o_p ) )
		return FALSE;
	if( is_mbr( d_p ) )
		return FALSE;
	if( is_pet( d_p ) )
		return FALSE;

	if( o_dam <= 0 )
		return FALSE;

	if( !chk_wpn_randm_art( WPN_RANDM_ART_KIND_DRAIN,
			WPN_RANDM_ART_MNR_DRAIN_EXP, o_p, d_p,
			flg_throw ) ){
		return FALSE;
	}

	o_dam = o_dam * WPN_RANDM_ART_DRAIN_EXP_RATE / _100_PERCENT;
	if( o_dam < 1 )
		o_dam = 1;
	o_dam = randm( o_dam + 1 );
	if( o_dam <= 0 )
		return FALSE;

	curs_attrset_chr( o_p, +1, FALSE );
	print_msg( FLG_NULL, MSG_FX_WPN_RANDM_ART_DRAIN_EXP,
			o_p->name, o_dam );
	curs_attrset_dflt();

	exp_chr( o_p, +o_dam, FALSE, FALSE, FALSE );

	return TRUE;
}

/***************************************************************
* ����饯���������򿩤٤�
* chr_t *chr : ����饯��
* item_t *item : ����
* return : ���٤줿��?
***************************************************************/

bool_t	eat_food( chr_t *chr, item_t *item )
{
	long	n, i;

	if( chr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_FOOD )
		return FALSE;

	print_msg_find( chr, FLG_NULL,
			MSG_EAT_FOOD, chr->name, item->name );

	n = 0;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		if( eat_food_n_msg_ls[i] == N_MSG_NULL )
			break;
		if( randm( i + 1 ) == 0 )
			n = i;
	}
	if( item->tab.food != NULL ){
		print_msg_find( chr, FLG_NULL,
				MSG( eat_food_n_msg_ls[n] ),
				item->tab.food->name );

		take_meal_chr( chr, item->tab.food->fill_rate );
	}

	inc_item( item, -1 );

	return TRUE;
}

/***************************************************************
* ����饯�����¤򥭥�å����ƿ��٤뤫�����å�
* chr_t *chr : ����饯��
* item_t *item : ����
* return : ���٤뤫?
***************************************************************/

bool_t	chk_mnstr_catch_food( chr_t *chr, item_t *item )
{
	if( chr == NULL )
		return FALSE;
	if( item == NULL )
		return FALSE;

	if( chr->kind != CHR_KIND_MNSTR )
		return FALSE;
	if( item->kind != ITEM_KIND_FOOD )
		return FALSE;

	if( chr->attitude == ATTITUDE_ENEMY )
		return FALSE;

	return TRUE;
}

/***************************************************************
* ����饯�����¤򥭥�å����ƿ��٤�
* chr_t *chr : ����饯��
* item_t *item : ����
* return : ���٤���?
***************************************************************/

bool_t	fx_mnstr_catch_food( chr_t *chr, item_t *item )
{
	if( !chk_mnstr_catch_food( chr, item ) )
		return FALSE;

	print_msg( FLG_NULL, MSG_MNSTR_CATCH_FOOD, chr->name );
	take_meal_chr( chr, item->tab.food->fill_rate );

	return TRUE;
}

/***************************************************************
* ���С��������ۤ�
* mbr_t *mbr : ���С�
* item_t *item : ����
* return : �ۤ�����?
***************************************************************/

bool_t	smoke_tobacco( mbr_t *mbr, item_t *item )
{
	item_t	*eq;
	bool_t	flg_use_pipe;

	if( mbr == NULL )
		return FALSE;
	if( !is_mbr( mbr ) )
		return FALSE;
	if( item == NULL )
		return FALSE;
	if( item->kind != ITEM_KIND_TOBACCO )
		return TRUE;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return FALSE;
	eq = &(eq[EQUIP_KIND_HEAD]);

	flg_use_pipe = FALSE;
	if( chk_flg( item->tab.tobacco->flg, FLG_TOBACCO_USE_PIPE ) ){
		if( eq->kind != ITEM_KIND_PIPE ){
			print_msg_find( mbr, FLG_NULL,
					MSG_S, MSG_SMOKE_FAILURE );
			return FALSE;
		} else if( eq->tab.pipe->tobacco_kind
				!= item->tab.tobacco->kind ){
			print_msg_find( mbr, FLG_NULL,
					MSG_S, MSG_SMOKE_FAILURE );
			return FALSE;
		}
		flg_use_pipe = TRUE;
	}
	if( chk_flg( item->tab.tobacco->flg, FLG_TOBACCO_CAN_USE_PIPE )
			&& (eq->kind == ITEM_KIND_PIPE)
			&& (eq->dat.pipe.consume_turn > 0)
			&& (eq->tab.pipe->tobacco_kind
			== item->tab.tobacco->kind) ){
		flg_use_pipe = TRUE;
	}

	if( flg_use_pipe ){
		eq->dat.pipe.turn = item->dat.tobacco.turn;
		inc_item( item, -1 );
	}

	call_game_sound_play( SOUND_KIND_ITEM_SMOKE, 1 );

	curs_attrset_chr( mbr, -1, FALSE );
	print_msg_find( mbr, FLG_NULL, MSG_S, MSG_FX_SMOKE_TOBACCO );
	curs_attrset_dflt();

	return !flg_use_pipe;	/* �ѥ��פ�Ȥ�ʤ��ʤ��������� */
}

/***************************************************************
* ���С����ۤäƤ�������ǳ�䤹�ʾ��񤷤Ƹ��餹��
* mbr_t *mbr : ���С�
***************************************************************/

void	inc_turn_smoke( mbr_t *mbr )
{
	item_t	*eq;
	nicotine_t	*nico;

	if( mbr == NULL )
		return;
	if( chk_flg_or( mbr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	eq = get_mbr_item_asgn_equip( mbr );
	if( eq == NULL )
		return;
	eq = &(eq[EQUIP_KIND_HEAD]);

	if( eq->kind == ITEM_KIND_PIPE ){
		if( eq->dat.pipe.consume_turn <= 0 )
			return;
		if( eq->dat.pipe.turn <= 0 )
			return;

		eq->dat.pipe.turn--;
		eq->dat.pipe.consume_turn--;
		set_item_name( eq );
		if( eq->dat.pipe.turn <= 0 ){
			print_msg_find( mbr, FLG_NULL,
					MSG_FX_SMOKE_END,
					mbr->name );
		}
		if( eq->dat.pipe.consume_turn <= 0 ){
			print_msg_find( mbr, FLG_NULL,
					MSG_FX_BREAK_PIPE,
					mbr->name, eq->name );
		}
	} else if( eq->kind == ITEM_KIND_TOBACCO ){
		if( eq->dat.tobacco.turn <= 0 )
			return;

		eq->dat.tobacco.turn--;
		set_item_name( eq );
		if( eq->dat.tobacco.turn <= 0 ){
			print_msg_find( mbr, FLG_NULL,
					MSG_FX_SMOKE_END,
					mbr->name );
		}
	} else {
		return;
	}

	nico = &(mbr->fx_data.nicotine);

	nico->rate += ADD_NICOTINE_RATE_PER_TURN;
	if( nico->rate > _100_PERCENT )
		nico->rate = _100_PERCENT;

	if( per_randm( TOBACCO_POISONING_AVE_TURN ) ){
		nico->poisoning_rate += TOBACCO_POISONING_ADD_RATE;
		if( nico->poisoning_rate > _100_PERCENT )
			nico->poisoning_rate = _100_PERCENT;
	}
}

/***************************************************************
* �˥��������Ǥ��ä����٤��������
* mbr_t *mbr : ���С�
***************************************************************/

void	inc_day_smoke( mbr_t *mbr )
{
	long	n;
	rate_t	rate;

	if( mbr == NULL )
		return;
	if( chk_flg_or( mbr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return;

	if( mbr->fx_data.nicotine.poisoning_rate <= 0 ){
		n = -1;
	} else if( mbr->fx_data.nicotine.poisoning_rate
			>= INC_NICOTINE_LOST_RATE_POISONING_RATE ){
		n = +1;
	} else {
		n = +-0;
	}

	rate = INC_NICOTINE_LOST_RATE_PER_DAY;
	for( ; rate >= _100_PERCENT; rate -= _100_PERCENT )
		mbr->fx_data.nicotine.lost_rate += n;
	if( rate_randm( rate ) )
		mbr->fx_data.nicotine.lost_rate += n;

	if( mbr->fx_data.nicotine.lost_rate < 0 )
		mbr->fx_data.nicotine.lost_rate = 0;
	if( mbr->fx_data.nicotine.lost_rate > _100_PERCENT )
		mbr->fx_data.nicotine.lost_rate = _100_PERCENT;
}

/***************************************************************
* ����ε۳̤����Ƥ���������
* mbr_t *mbr : ���С�
* item_t *item : ����
***************************************************************/

void	dispose_tobacco( mbr_t *mbr, item_t *item )
{
	item_t	*head, *p;
	long	i;

	if( mbr == NULL )
		return;
	if( !is_mbr( mbr ) )
		return;
	if( item == NULL )
		return;
	if( item->kind != ITEM_KIND_DISPOSAL )
		return;

	head = get_mbr_item_asgn( mbr );
	if( head == NULL )
		p = NULL;
	else
		p = head->next->next;
	for( i = 0; i < MBR_ITEM_MAX_N; i++, p = p->next ){
		if( p == NULL )
			break;
		if( p->prev == head )
			break;

		if( item->dat.disposal.n >= item->dat.disposal.max_n )
			break;

		dispose_tobacco_sub( item, p->prev );
	}

	p = get_mbr_item_asgn_equip( mbr );
	for( i = 0; i < EQUIP_KIND_MAX_N; i++ ){
		if( p == NULL )
			break;

		if( item->dat.disposal.n >= item->dat.disposal.max_n )
			break;

		dispose_tobacco_sub( item, &(p[i]) );
	}
}

/***************************************************************
* ����ε۳̤򤫤�������
* item_t *disposal : �۳�����
* item_t *tobacco : ����
***************************************************************/

void	dispose_tobacco_sub( item_t *disposal, item_t *tobacco )
{
	long	n;

	if( disposal == NULL )
		return;
	if( disposal->kind != ITEM_KIND_DISPOSAL )
		return;
	if( disposal->dat.disposal.n >= disposal->dat.disposal.max_n )
		return;

	if( tobacco == NULL )
		return;
	if( tobacco->kind != ITEM_KIND_TOBACCO )
		return;
	if( tobacco->dat.tobacco.turn > 0 )
		return;

	n = disposal->dat.disposal.max_n - disposal->dat.disposal.n;
	n = min_l( n, tobacco->n );

	inc_item( tobacco, -n );
	disposal->dat.disposal.n += n;

	set_item_name( disposal );
}

/***************************************************************
* �����˴��դ���
* chr_t *chr : ����饯��
* gold_t gold : ���դ�����
* gold_t spell_gold : ��ʸ��Ф�������
***************************************************************/

void	contribution( chr_t *chr, gold_t gold, gold_t spell_gold )
{
	if( gold >= spell_gold )
		if( learn_spell_pri( chr ) )
			return;

	if( chr->contribution < GOLD_MAX )
		chr->contribution += gold;
	if( chr->contribution > GOLD_MAX )
		chr->contribution = GOLD_MAX;
}

/***************************************************************
* ��ʢ�٤ˤ�äƾ��֤����ꡦ���
* chr_t *chr : ����饯��
***************************************************************/

void	set_stomach( chr_t *chr )
{
	stomach_t	*st;

	if( chr == NULL )
		return;

	st = &(chr->fx_data.stomach);

	if( chk_flg( chr->stat, FLG_STAT_HUNGRY ) ){
		/* ��ʢ�Ǥʤ��ʤä�����֤��� */

		if( st->rate >= st->hungry_rate ){
			chr->stat &= ~FLG_STAT_HUNGRY;
			draw_mbr_stat( chr );
		}
	} else {
		/* ��ʢ�򴶤�������֤����� */

		if( st->rate < st->hungry_rate ){
			if( per_randm( HUNGRY_FEEL_RATE ) ){
				chr->stat |= FLG_STAT_HUNGRY;
				draw_mbr_stat( chr );
			}
		}
	}

	if( chk_flg( chr->stat, FLG_STAT_STARVATION ) ){
		/* ����Ǥʤ��ʤä�����֤��� */

		if( st->rate >= st->starvation_rate ){
			chr->stat &= ~FLG_STAT_STARVATION;
			draw_mbr_stat( chr );
		}
	} else {
		/* ����򴶤�������֤����� */

		if( st->rate < st->starvation_rate ){
			if( per_randm( STARVATION_FEEL_RATE ) ){
				chr->stat |= FLG_STAT_STARVATION;
				draw_mbr_stat( chr );
			}
		}
	}

	if( st->rate <= 0 ){
		st->rate = 0;

		/* �ߤ����ˤʤä��顢��ޤ��ξ��֤����� */

		if( per_randm( FAINT_FEEL_RATE ) ){
			faint( chr );
		}
	} else {
		fx_t	*fx;

		/* �������٤��顢��ޤ��ξ��֤��� */

		fx = srch_fx( &(chr->fx), FX_KIND_FAINT );
		if( fx != NULL ){
			clr_fx( fx );
			draw_mbr_stat( chr );
		}
	}
}

/***************************************************************
* ����ʪ��ò�
* chr_t *chr : ����饯��
***************************************************************/

void	digest( chr_t *chr )
{
	rate_t	rate;
	long	n;

	if( chr == NULL )
		return;

	rate = modified_rate( _100_PERCENT, chr->fx_data.stomach.digest_n );
	n = chr->fx_data.stomach.digest_p_day * rate / _100_PERCENT;

	if( per_randm( TURN_A_DAY / n ) ){
		chr->fx_data.stomach.rate--;
		set_stomach( chr );
	}
}

/***************************************************************
* ����ʪ�򿩤٤�
* chr_t *chr : ����饯��
* rate_t rate : ��ʢ��
***************************************************************/

void	take_meal_chr( chr_t *chr, rate_t rate )
{
	rate = rate * _100_PERCENT / chr->fx_data.stomach.full_rate;

	chr->fx_data.stomach.rate += rate;
	if( chr->fx_data.stomach.rate >= _100_PERCENT ){
		chr->fx_data.stomach.rate = _100_PERCENT;
		print_msg_find( chr, FLG_NULL,
				MSG_STOMACH_FULL, chr->name );
	}

	set_stomach( chr );
}

/***************************************************************
* ����饯������ʢ�ˤ���
* chr_t *chr : ����饯��
***************************************************************/

void	take_meal_fill_chr( chr_t *chr )
{
	chr->fx_data.stomach.rate = _100_PERCENT;
	set_stomach( chr );
}

/***************************************************************
* ����饯���Τ�ޤ�������
* chr_t *chr : ����饯��
* return : ������褿��?
***************************************************************/

bool_t	faint( chr_t *chr )
{
	if( set_fx( chr, FX_KIND_FAINT, FX_AVE_TURN_FAINT ) == NULL )
		return FALSE;
	else
		return TRUE;
}

/***************************************************************
* ����饯���ζر�
* chr_t *chr : ����饯��
***************************************************************/

void	abstain( chr_t *chr )
{
	nicotine_t	*nico;

	if( chr == NULL )
		return;

	nico = &(chr->fx_data.nicotine);

	if( per_randm( TOBACCO_ABSTAIN_AVE_TURN ) )
		nico->rate -= TOBACCO_ABSTAIN_SUB_RATE;
	if( nico->rate < 0 )
		nico->rate = 0;

	if( chk_flg( chr->stat, FLG_STAT_SLEEP ) )
		return;

	if( per_randm( TOBACCO_FEEL_AVE_TURN ) ){
		rate_t	rate;

		rate = _100_PERCENT - nico->rate;
		rate = rate * rate / _100_PERCENT;
		rate = rate * TOBACCO_FEEL_MAX_RATE / _100_PERCENT;
		rate = rate * nico->poisoning_rate / _100_PERCENT;
		if( rate_randm( rate ) ){
			if( is_mbr( chr ) ){
				print_msg_find( chr, FLG_MSG_MORE,
						MSG_FX_TOBACCO_ABSTAIN,
						chr->name );
			}
		}
	}

	if( nico->rate <= 0 ){
		if( per_randm( TOBACCO_CURE_POISONING_AVE_TURN ) ){
			rate_t	rate;

			rate = TOBACCO_CURE_POISONING_SUB_RATE;
			nico->poisoning_rate -= rate;
			if( nico->poisoning_rate < 0 )
				nico->poisoning_rate = 0;
		}
	}
}

/***************************************************************
* ����饯�������ɤ��ʤ�
* chr_t *chr : ����饯��
***************************************************************/

void	fraternize( chr_t *chr )
{
	dun_t	*dun = get_dun();

	if( chr == NULL )
		return;
	if( dun->lev == 0 )
		return;

	chr->fx_data.friend_turn--;
	if( chr->fx_data.friend_turn < 0 )
		chr->fx_data.friend_turn = 0;
}

/***************************************************************
* �Ż�ǽ�Ϥ򸺾�������
* chr_t *chr : ����饯��
***************************************************************/

bool_t	dec_infra_vision( chr_t *chr )
{
	if( chr == NULL )
		return FALSE;

	clr_map_chr( chr );

	chr->fx_data.infra_vision--;
	if( chr->fx_data.infra_vision < 0 )
		chr->fx_data.infra_vision = 0;

	chr->x = chr->pre_x;
	chr->y = chr->pre_y;
	set_map_chr( chr );

	return( chr->fx_data.infra_vision > 0 );
}

/***************************************************************
* ����饯���Υ����ࡦ�ƥ�ݡ���
* chr_t *chr : ����饯��
***************************************************************/

void	randm_teleport( chr_t *chr )
{
	rate_t	rate;

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST ) )
		return;
	if( chr->work.teleport_n <= 0 )
		return;

	rate = modified_rate( RANDM_TELEPORT_RATE,
			chr->work.teleport_n );
	if( rate_randm( rate ) )
		teleport_chr( chr );
}

/***************************************************************
* �ѡ��ƥ��Υ����ࡦ�ƥ�ݡ���
* chr_t *chr : ����饯��
***************************************************************/

void	randm_teleport_party( chr_t *chr )
{
	rate_t	rate;

	if( chr == NULL )
		return;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST ) )
		return;
	if( chr->work.teleport_party_n <= 0 )
		return;

	rate = modified_rate( RANDM_TELEPORT_PARTY_RATE,
			chr->work.teleport_party_n );
	if( rate_randm( rate ) )
		teleport_party();
}

/***************************************************************
* ������
* chr_t *o_p : ���¦�Υ���饯��
* chr_t *d_p : ��ޤ��¦�Υ���饯��
* rate_t rate : ����ۤ�Ψ
* long max_n : ����ۤκ�����
* return : �������
***************************************************************/

gold_t	fx_pick_gold( chr_t *o_p, chr_t *d_p, rate_t rate, long max_n )
{
	gold_t	n;

	if( o_p == NULL )
		return 0;
	if( d_p == NULL )
		return 0;

	max_n = min_l( max_n, get_chr_gold( d_p ) );

	n = get_chr_gold( d_p ) * rate / _100_PERCENT;
	if( n > max_n )
		n = max_n;

	print_msg_find( d_p, FLG_NULL,
			MSG_FX_PICK_GOLD, o_p->name, d_p->name );

	add_chr_gold( d_p, -n );
	add_chr_gold( o_p, +n );

	return n;
}

/***************************************************************
* ��󥹥��������С���«
* mnstr_t *mnstr : ��󥹥���
* chr_t *chr : ����饯��
***************************************************************/

void	catch_chr( mnstr_t *mnstr, chr_t *chr )
{
	if( mnstr == NULL )
		return;
	if( chr == NULL )
		return;

	if( mnstr->work.catch_chr != NULL )
		release_chr( mnstr );

	if( mnstr->work.catch_chr != chr )
		mnstr->work.catch_chr = chr;

	/* ��«���ʿ������� */
	inc_chr_caught( chr, +1 );
}

/***************************************************************
* ��󥹥��������С��ι�«����
* mnstr_t *mnstr : ��󥹥���
***************************************************************/

void	release_chr( mnstr_t *mnstr )
{
	if( mnstr == NULL )
		return;
	if( mnstr->work.catch_chr == NULL )
		return;

	/* ��«������������ */
	inc_chr_caught( mnstr->work.catch_chr, -1 );

	mnstr->work.catch_chr = NULL;
}

/***************************************************************
* ���С������ι�«�����Ʋ��
***************************************************************/

void	release_all_mbr( void )
{
	party_t	*pty = get_party();
	long	i;

	for( i = 0; i < MBR_MAX_N; i++ )
		release_chr_all_ref( pty->mbr[i] );
}

/***************************************************************
* ���ͤΥ���饯���ι�«�����Ʋ��
***************************************************************/

void	release_chr_all_ref( chr_t *chr )
{
	mnstr_t	*mns_head, *mns_p, *mns_pp;

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next->next; mns_p != NULL;
			mns_p = mns_p->next ){
		mns_pp = mns_p->prev;
		if( mns_pp == mns_head )
			break;

		if( mns_pp->work.catch_chr == chr )
			mns_pp->work.catch_chr = NULL;
	}

	/* ��«�ο�����ꥻ�å� */
	inc_chr_caught( chr, 0 );
}

/***************************************************************
* ��«�ο���������
* chr_t *chr : ����饯��
* long n : + �ʤ鿼����- �ʤ�������0 �ʤ�ꥻ�å�
***************************************************************/

void	inc_chr_caught( chr_t *chr, long n )
{
	if( chr == NULL )
		return;

	if( n == 0 )
		chr->work.caught = 0;
	else
		chr->work.caught += n;

	if( chr->work.caught > 0 )
		chr->stat |= FLG_STAT_CAUGHT;
	else
		chr->stat &= ~FLG_STAT_CAUGHT;

	draw_mbr_stat( chr );
}

/***************************************************************
* ��ʸ�˱����������Υǡ������֤�
* spell_kind_t kind : ��ʸ�μ���
* return : �����Υǡ���
***************************************************************/

blast_t	*get_blast_spell( spell_kind_t kind )
{
	if( kind == SPELL_KIND_WORD_OF_DESTRUCTION )
		return get_blast( BLAST_KIND_WORD_OF_DESTRUCTION );
	else
		return get_blast( BLAST_KIND_STD );
}

/***************************************************************
* �����Υǡ������֤�
* spell_kind_t kind : �����μ���
* return : �����Υǡ���
***************************************************************/

blast_t	*get_blast( blast_kind_t kind )
{
	blast_t	*p;

	p = &g_blast_std;

	switch( kind ){
	case BLAST_KIND_MAX_N:
	case BLAST_KIND_STD:
		p = &g_blast_std;
		break;
	case BLAST_KIND_NINJA_CRTCL:
		p = &g_blast_ninja_crtcl;
		break;
	case BLAST_KIND_WORD_OF_DESTRUCTION:
		p = &g_blast_destruction;
		break;
	/* default: */
	}

	set_blast_size( p );

	return p;
}

/***************************************************************
* �����Υǡ������֤�
* spell_kind_t kind : �����μ���
* return : �����Υǡ���
***************************************************************/

void	set_blast_size( blast_t *p )
{
	long	xl, yl, xr, yr;

	if( p == NULL )
		return;
	if( p->xl > 0 )
		return;

	xl = 1;
	for( yl = 0; yl < BLAST_MAX_Y; yl++ ){
		long	len;

		if( p->ptn[yl][0] == '\0' )
			break;

		len = str_len_draw( p->ptn[yl] );
		xl = max_l( xl, len );
	}

	xr = xl / 2;
	yr = yl / 2;

	xr /= 2;
	xr *= 2;

	p->xl = xl;
	p->yl = yl;
	p->xr = xr;
	p->yr = yr;
}

/***************************************************************
* ���ե����Ȥμ�����б����륹�ơ������Υե饰���֤�
* fx_kind_t fx_kind : ���ե����Ȥμ���
* return : ���ơ������Υե饰
***************************************************************/

flg_stat_t	cv_fx_kind_to_flg_stat( fx_kind_t fx_kind )
{
	switch( fx_kind ){
	case FX_KIND_STONE:
		return FLG_STAT_STONE;
	case FX_KIND_PARALYZE:
		return FLG_STAT_PARALYZE;
	case FX_KIND_POISON:
		return FLG_STAT_POISON;
	case FX_KIND_CONFUSION:
		return FLG_STAT_CONFUSION;
	case FX_KIND_BLIND:
		return FLG_STAT_BLIND;
	case FX_KIND_SLEEP:
		return FLG_STAT_SLEEP;
	case FX_KIND_SILENCE:
		return FLG_STAT_SILENCE;
	case FX_KIND_FEAR:
		return FLG_STAT_FEAR;
	case FX_KIND_HALLUCINATION:
		return FLG_STAT_HALLUCINATION;
	case FX_KIND_CHARM:
		return FLG_STAT_CHARM;
	case FX_KIND_FLY:
		return FLG_STAT_FLY;
	case FX_KIND_VANISH:
		return FLG_STAT_VANISH;
	case FX_KIND_IRON_BODY:
		return FLG_STAT_IRON_BODY;
	case FX_KIND_PASSWALL:
		return FLG_STAT_PASSWALL;
	case FX_KIND_SENSE_INVISIBLE:
		return FLG_STAT_SENSE_INVISIBLE;
	default:
		return FLG_STAT_NULL;
	}

	return FLG_STAT_NULL;
}

/***************************************************************
* ���ե����Ȥμ�����б��������ͤμ�����֤�
* fx_kind_t fx_kind : ���ե����Ȥμ���
* return : ���ͤμ���
***************************************************************/

resi_kind_t	cv_fx_kind_to_resi_kind( fx_kind_t fx_kind )
{
	switch( fx_kind ){
	case FX_KIND_STONE:
		return RESI_KIND_MIND;
	case FX_KIND_PARALYZE:
		return RESI_KIND_ELEC;
	case FX_KIND_POISON:
		return RESI_KIND_POIS;
	case FX_KIND_CONFUSION:
		return RESI_KIND_MIND;
	case FX_KIND_BLIND:
		return RESI_KIND_POIS;
	case FX_KIND_SLEEP:
		return RESI_KIND_MIND;
	case FX_KIND_SILENCE:
		return RESI_KIND_ELEC;
	case FX_KIND_FEAR:
		return RESI_KIND_MIND;
	case FX_KIND_HALLUCINATION:
		return RESI_KIND_MIND;
	case FX_KIND_CHARM:
		return RESI_KIND_ELEC;
	case FX_KIND_FLY:
		return RESI_KIND_MIND;
	case FX_KIND_VANISH:
		return RESI_KIND_POIS;
	case FX_KIND_IRON_BODY:
		return RESI_KIND_KNOC;
	case FX_KIND_PASSWALL:
		return RESI_KIND_ACID;
	case FX_KIND_SENSE_INVISIBLE:
		return RESI_KIND_MIND;
	default:
		return RESI_KIND_MIND;
	}

	return RESI_KIND_MIND;
}

/***************************************************************
* ����饯���򻲾Ȥ��Ƥ��륨�ե����Ȥ����Ʋ�������
* chr_t *chr : ����饯��
***************************************************************/

void	lost_fx_chr( chr_t *chr )
{
	mbr_t	**ls_mbr;
	pet_t	**pet;
	mnstr_t	*mns_head, *mns_p, *mns_pp;
	long	i;

	if( chr == NULL )
		return;

	ls_mbr = get_ls_mbr();
	for( i = 0; i < LS_MBR_MAX_N; i++ ){
		if( ls_mbr[i] == NULL )
			continue;

		lost_fx_chr_sub( chr, &(ls_mbr[i]->fx) );
		draw_mbr_stat( ls_mbr[i] );
	}

	pet = get_party_pet();
	for( i = 0; i < PET_MAX_N; i++ ){
		if( pet[i] == NULL )
			continue;

		lost_fx_chr_sub( chr, &(pet[i]->fx) );
	}

	mns_head = get_mnstr_used();
	for( mns_p = mns_head->next->next; mns_p != NULL;
			mns_p = mns_p->next ){
		mns_pp = mns_p->prev;
		if( mns_pp == mns_head )
			break;

		lost_fx_chr_sub( chr, &(mns_pp->fx) );
	}
}

/***************************************************************
* ����饯���򻲾Ȥ��Ƥ��륨�ե����ȤΥꥹ�Ȥ��������
* chr_t *chr : ����饯��
* fx_t *fx : ���ե����ȤΥꥹ��
***************************************************************/

void	lost_fx_chr_sub( chr_t *chr, fx_t *fx )
{
	fx_t	*p, *pp;

	if( chr == NULL )
		return;
	if( fx == NULL )
		return;

	for( p = fx->next->next; p != NULL; p = p->next ){
		pp = p->prev;
		if( pp == fx )
			break;

		if( pp->cast_chr == chr ){
			clr_fx( pp );
		}
	}
}

/***************************************************************
* ���ե����Ȥ������Ƥ�
* fx_t *p : �����Υ��ե����ȤΥꥹ��
* return : ������Ƥ����ե�����
***************************************************************/

fx_t	*asgn_fx( fx_t *p )
{
	fx_t	*fx;

	fx = fx_free.next;
	if( fx == &fx_free )
		return NULL;

	fx->kind = FX_KIND_NULL;

	ins_ls_fx( p->next, fx );

	return fx;
}

/***************************************************************
* ���ե����Ȥ��������
* fx_t *p : �������륨�ե�����
***************************************************************/

void	free_fx( fx_t *p )
{
	if( p != NULL )
		ins_ls_fx( &fx_free, p );
}

/***************************************************************
* �ꥹ�Ȥ����ƤΥ��ե����Ȥ��������
* fx_t *p : �������륨�ե����ȤΥꥹ��
***************************************************************/

void	free_fx_all( fx_t *p )
{
	fx_t	*fx;

	if( p == NULL )
		return;

	for( fx = p->next->next; fx->prev != p; fx = fx->next )
		ins_ls_fx( &fx_free, fx->prev );
}

/***************************************************************
* ���ե����ȤΥ�󥯤��̤Υꥹ�Ȥˤ֤鲼����
* fx_t *ls : �̤Υꥹ��
* fx_t *p : ���ե�����
***************************************************************/

void	ins_ls_fx( fx_t *ls, fx_t *p )
{
	p->next->prev = p->prev;
	p->prev->next = p->next;

	p->prev = ls->prev;
	p->next = ls;

	ls->prev->next = p;
	ls->prev = p;
}

/***************************************************************
* ����Υ��ե����Ȥ�ꥹ�Ȥ��鸡������
* fx_t *ls : ���ե����ȤΥꥹ��
* fx_kind_t kind : �������륨�ե����Ȥμ���
* return : ������̤Υ��ե�����
***************************************************************/

fx_t	*srch_fx( fx_t *ls, fx_kind_t kind )
{
	fx_t	*p, *end;

	if( ls == NULL )
		return NULL;
	if( ls->next == NULL )
		return NULL;
	if( ls->prev == NULL )
		return NULL;

	end = ls->prev->next;

	for( p = ls->next; p != end; p = p->next ){
		if( p == NULL )
			return NULL;

		if( p->kind == kind )
			return p;

		if( p->next == NULL )
			return NULL;
	}

	return NULL;
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_fx_c( void )
{
	check_memory( check_memory_fx_c_liquor_proof,
			"fx.c: liquor_proof" );
	check_memory( check_memory_fx_c_drink_n_msg_ls,
			"fx.c: drink_n_msg_ls" );
	check_memory( check_memory_fx_c_eat_food_n_msg_ls,
			"fx.c: eat_food_n_msg_ls" );
	check_memory( check_memory_fx_c_fx_buf,
			"fx.c: fx_buf" );
	check_memory( check_memory_fx_c_fx_free,
			"fx.c: fx_free" );
	check_memory( check_memory_fx_c_g_blast_std,
			"fx.c: g_blast_std" );
	check_memory( check_memory_fx_c_g_blast_ninja_crtcl,
			"fx.c: g_blast_ninja_crtcl" );
	check_memory( check_memory_fx_c_g_blast_destruction,
			"fx.c: g_blast_destruction" );
	check_memory( check_memory_fx_c_g_modifier_song_mbr,
			"fx.c: g_modifier_song_mbr" );
	check_memory( check_memory_fx_c_g_modifier_song_mnstr,
			"fx.c: g_modifier_song_mnstr" );
	check_memory( check_memory_fx_c_g_modifier_song_pet,
			"fx.c: g_modifier_song_pet" );
	check_memory( check_memory_fx_c_g_sel_bone,
			"fx.c: g_sel_bone" );
	check_memory( check_memory_fx_c_g_sel_wish,
			"fx.c: g_sel_wish" );
}
