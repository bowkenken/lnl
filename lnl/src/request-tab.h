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
* $Id: request-tab.h,v 1.11 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	REQUEST_TAB_H
#define	REQUEST_TAB_H

/***************************************************************
* 酒場の依頼
***************************************************************/

/* アイテム探索の依頼のリスト */

n_msg_t	g_rare_goods_tab[] = {
	N_MSG_REQUEST_RARE_GOODS_00,
	N_MSG_REQUEST_RARE_GOODS_01,
	N_MSG_REQUEST_RARE_GOODS_02,

	N_MSG_NULL,
};

/* キャプモンの依頼のリスト */

n_msg_t	g_tame_mnstr_tab[] = {
	N_MSG_REQUEST_TAME_MNSTR_00,
	N_MSG_REQUEST_TAME_MNSTR_01,

	N_MSG_NULL,
};

/* 救助の依頼のリスト */

n_msg_t	g_rescue_tab[] = {
	N_MSG_REQUEST_RESCUE_00,

	N_MSG_NULL,
};

/* 観光案内の依頼のリスト */

n_msg_t	g_tour_guide_tab[] = {
	N_MSG_REQUEST_TOUR_GUIDE_00,

	N_MSG_NULL,
};

/* モンスター退治の依頼のリスト */

n_msg_t	g_exterminate_tab[] = {
	N_MSG_REQUEST_EXTERMINATE_00,
	N_MSG_REQUEST_EXTERMINATE_01,

	N_MSG_NULL,
};

/* 仇討ちの依頼のリスト */

n_msg_t	g_revenge_tab[] = {
	N_MSG_REQUEST_REVENGE_00,
	N_MSG_REQUEST_REVENGE_01,
	N_MSG_REQUEST_REVENGE_02,
	N_MSG_REQUEST_REVENGE_03,

	N_MSG_NULL,
};

/* 賞金首の依頼のリスト */

n_msg_t	g_wanted_criminal_tab[] = {
	N_MSG_REQUEST_WANTED_CRIMINAL_00,
	N_MSG_REQUEST_WANTED_CRIMINAL_01,
	N_MSG_REQUEST_WANTED_CRIMINAL_02,
	N_MSG_REQUEST_WANTED_CRIMINAL_03,

	N_MSG_NULL,
};

/* 依頼メッセージの変数展開用の関数テーブル */

typedef struct {
	char	*name;
	void	(*func)( request_t *req, char *buf, char *arg );
} request_msg_var_t;

request_msg_var_t	g_request_msg_var[] = {
	{
		"dungeon_min_level",
		set_request_msg_var_dun_min_lev,
	},
	{
		"dungeon_max_level",
		set_request_msg_var_dun_max_lev,
	},
	{
		"dungeon_level_range",
		set_request_msg_var_dun_lev_range,
	},
	{
		"client",
		set_request_msg_var_client,
	},
	{
		"rare_goods",
		set_request_msg_var_rare_goods,
	},
	{
		"rescue_target",
		set_request_msg_var_rescue_trgt,
	},
	{
		"monster",
		set_request_msg_var_mnstr,
	},
	{
		"monster_number",
		set_request_msg_var_mnstr_n,
	},
	{
		"client_family",
		set_request_msg_var_client_family,
	},
	{
		"client_mate",
		set_request_msg_var_client_mate,
	},
	{
		"when",
		set_request_msg_var_when_1,
	},
	{
		"when_1",
		set_request_msg_var_when_1,
	},
	{
		"when_2",
		set_request_msg_var_when_2,
	},
	{
		"weapon",
		set_request_msg_var_weapon,
	},
	{
		NULL,
		NULL,
	},
};

/* 時間グループ A の変数のリスト */

n_msg_t	g_ls_when_a[] = {
	N_MSG_WHEN_A00,
	N_MSG_WHEN_A01,
	N_MSG_WHEN_A02,
	N_MSG_WHEN_A03,

	N_MSG_NULL,
};

/* 時間グループ B の変数のリスト */

n_msg_t	g_ls_when_b[] = {
	N_MSG_WHEN_B00,
	N_MSG_WHEN_B01,
	N_MSG_WHEN_B02,
	N_MSG_WHEN_B03,
	N_MSG_WHEN_B04,
	N_MSG_WHEN_B05,
	N_MSG_WHEN_B06,

	N_MSG_NULL,
};

/* 依頼に関係する武器の変数のリスト */

n_msg_t	g_ls_weapon[] = {
	N_MSG_WEAPON_00,
	N_MSG_WEAPON_01,
	N_MSG_WEAPON_02,

	N_MSG_NULL,
};

/* 依頼の女性 NPC の変数のリスト */

n_msg_t	g_ls_npc_name_female[] = {

/* 女性 */
/* NPC name female begin */

	N_MSG_NPC_NAME_ABIGAIL,
	N_MSG_NPC_NAME_ADA,
	N_MSG_NPC_NAME_ADELA,
	N_MSG_NPC_NAME_ADELAIDE,
	N_MSG_NPC_NAME_ADELE,
	N_MSG_NPC_NAME_ADELINE,
	N_MSG_NPC_NAME_AGATHA,
	N_MSG_NPC_NAME_AGGIE,
	N_MSG_NPC_NAME_AGNES,
	N_MSG_NPC_NAME_ALBERTA,
	N_MSG_NPC_NAME_ALDA,
	N_MSG_NPC_NAME_ALETHEA,
	N_MSG_NPC_NAME_ALEXANDRA,
	N_MSG_NPC_NAME_ALICE,
	N_MSG_NPC_NAME_ALISON,
	N_MSG_NPC_NAME_ALMA,
	N_MSG_NPC_NAME_ALPHA,
	N_MSG_NPC_NAME_ALTHEA,
	N_MSG_NPC_NAME_AMANDA,
	N_MSG_NPC_NAME_AMELIA,
	N_MSG_NPC_NAME_AMY,
	N_MSG_NPC_NAME_ANABEL,
	N_MSG_NPC_NAME_ANASTASIA,
	N_MSG_NPC_NAME_ANGELA,
	N_MSG_NPC_NAME_ANGELIA,
	N_MSG_NPC_NAME_ANGELICA,
	N_MSG_NPC_NAME_ANGELINA,
	N_MSG_NPC_NAME_ANGELINE,
	N_MSG_NPC_NAME_ANITA,
	N_MSG_NPC_NAME_ANN,
	N_MSG_NPC_NAME_ANNA,
	N_MSG_NPC_NAME_ANNABELLA,
	N_MSG_NPC_NAME_ANNIE,
	N_MSG_NPC_NAME_ANTOINETTE,
	N_MSG_NPC_NAME_ANTONIA,
	N_MSG_NPC_NAME_APOLLONIA,
	N_MSG_NPC_NAME_APRIL,
	N_MSG_NPC_NAME_ARABELLA,
	N_MSG_NPC_NAME_ARLENE,
	N_MSG_NPC_NAME_ARTEMISIA,
	N_MSG_NPC_NAME_AUDREY,
	N_MSG_NPC_NAME_AUGUSTA,
	N_MSG_NPC_NAME_AURELIA,
	N_MSG_NPC_NAME_AVERIL,
	N_MSG_NPC_NAME_AZALEA,
	N_MSG_NPC_NAME_BAB,
	N_MSG_NPC_NAME_BABETTE,
	N_MSG_NPC_NAME_BARBARA,
	N_MSG_NPC_NAME_BEATRICE,
	N_MSG_NPC_NAME_BEATRIX,
	N_MSG_NPC_NAME_BECKY,
	N_MSG_NPC_NAME_BELINDA,
	N_MSG_NPC_NAME_BELL,
	N_MSG_NPC_NAME_BELLA,
	N_MSG_NPC_NAME_BERNICE,
	N_MSG_NPC_NAME_BERTHA,
	N_MSG_NPC_NAME_BERYL,
	N_MSG_NPC_NAME_BETTINA,
	N_MSG_NPC_NAME_BIANCA,
	N_MSG_NPC_NAME_BLANCHE,
	N_MSG_NPC_NAME_BONNIE,
	N_MSG_NPC_NAME_BRENDA,
	N_MSG_NPC_NAME_BRIDGET,
	N_MSG_NPC_NAME_CAMILLA,
	N_MSG_NPC_NAME_CANDICE,
	N_MSG_NPC_NAME_CARMELLA,
	N_MSG_NPC_NAME_CAROLINA,
	N_MSG_NPC_NAME_CAROLINE,
	N_MSG_NPC_NAME_CATHERINE,
	N_MSG_NPC_NAME_CECILIA,
	N_MSG_NPC_NAME_CECILY,
	N_MSG_NPC_NAME_CELESTE,
	N_MSG_NPC_NAME_CELIA,
	N_MSG_NPC_NAME_CHARITY,
	N_MSG_NPC_NAME_CHARLEEN,
	N_MSG_NPC_NAME_CHARLOTTE,
	N_MSG_NPC_NAME_CHARMIAN,
	N_MSG_NPC_NAME_CHERE,
	N_MSG_NPC_NAME_CHERRY,
	N_MSG_NPC_NAME_CHERYL,
	N_MSG_NPC_NAME_CHLOE,
	N_MSG_NPC_NAME_CHRISTIANA,
	N_MSG_NPC_NAME_CHRISTINE,
	N_MSG_NPC_NAME_CINDY,
	N_MSG_NPC_NAME_CLAIRE,
	N_MSG_NPC_NAME_CLARA,
	N_MSG_NPC_NAME_CLARISSA,
	N_MSG_NPC_NAME_CLAUDIA,
	N_MSG_NPC_NAME_COLLEEN,
	N_MSG_NPC_NAME_CONNIE,
	N_MSG_NPC_NAME_CONSTANCE,
	N_MSG_NPC_NAME_CONSUELO,
	N_MSG_NPC_NAME_CORA,
	N_MSG_NPC_NAME_CORDELIA,
	N_MSG_NPC_NAME_CORINNA,
	N_MSG_NPC_NAME_CORINNE,
	N_MSG_NPC_NAME_CORNELIA,
	N_MSG_NPC_NAME_CYNTHIA,
	N_MSG_NPC_NAME_DAISY,
	N_MSG_NPC_NAME_DAMARIS,
	N_MSG_NPC_NAME_DANA,
	N_MSG_NPC_NAME_DAPHNE,
	N_MSG_NPC_NAME_DARLA,
	N_MSG_NPC_NAME_DARLENE,
	N_MSG_NPC_NAME_DARYL,
	N_MSG_NPC_NAME_DAWN,
	N_MSG_NPC_NAME_DEANNA,
	N_MSG_NPC_NAME_DEBORAH,
	N_MSG_NPC_NAME_DEIRDRE,
	N_MSG_NPC_NAME_DELIA,
	N_MSG_NPC_NAME_DELLA,
	N_MSG_NPC_NAME_DELORIS,
	N_MSG_NPC_NAME_DENISE,
	N_MSG_NPC_NAME_DIANA,
	N_MSG_NPC_NAME_DIANE,
	N_MSG_NPC_NAME_DINAH,
	N_MSG_NPC_NAME_DIXIE,
	N_MSG_NPC_NAME_DOLL,
	N_MSG_NPC_NAME_DOLLY,
	N_MSG_NPC_NAME_DONNA,
	N_MSG_NPC_NAME_DORA,
	N_MSG_NPC_NAME_DOREEN,
	N_MSG_NPC_NAME_DORIS,
	N_MSG_NPC_NAME_DOROTHY,
	N_MSG_NPC_NAME_DOTTY,
	N_MSG_NPC_NAME_DRUSILLA,
	N_MSG_NPC_NAME_DULCIE,
	N_MSG_NPC_NAME_EDITH,
	N_MSG_NPC_NAME_EDNA,
	N_MSG_NPC_NAME_EFFIE,
	N_MSG_NPC_NAME_EILEEN,
	N_MSG_NPC_NAME_ELAINE,
	N_MSG_NPC_NAME_ELEANOR,
	N_MSG_NPC_NAME_ELEANORA,
	N_MSG_NPC_NAME_ELIZA,
	N_MSG_NPC_NAME_ELIZABETH,
	N_MSG_NPC_NAME_ELLEN,
	N_MSG_NPC_NAME_ELMA,
	N_MSG_NPC_NAME_ELOISE,
	N_MSG_NPC_NAME_ELSIE,
	N_MSG_NPC_NAME_ELVIRA,
	N_MSG_NPC_NAME_EM,
	N_MSG_NPC_NAME_EMANUEL,
	N_MSG_NPC_NAME_EMILY,
	N_MSG_NPC_NAME_EMMA,
	N_MSG_NPC_NAME_EMMELINA,
	N_MSG_NPC_NAME_EMMELINE,
	N_MSG_NPC_NAME_EMMY,
	N_MSG_NPC_NAME_ENID,
	N_MSG_NPC_NAME_ENOLA,
	N_MSG_NPC_NAME_EPPIE,
	N_MSG_NPC_NAME_ERICA,
	N_MSG_NPC_NAME_ERMENTRUDE,
	N_MSG_NPC_NAME_ERNESTINE,
	N_MSG_NPC_NAME_ESTELLE,
	N_MSG_NPC_NAME_ESTHER,
	N_MSG_NPC_NAME_ETHEL,
	N_MSG_NPC_NAME_ETTA,
	N_MSG_NPC_NAME_EUNICE,
	N_MSG_NPC_NAME_EUPHEMIA,
	N_MSG_NPC_NAME_EVA,
	N_MSG_NPC_NAME_EVADNE,
	N_MSG_NPC_NAME_EVANGELINE,
	N_MSG_NPC_NAME_EVE,
	N_MSG_NPC_NAME_EVELYN,
	N_MSG_NPC_NAME_FAITH,
	N_MSG_NPC_NAME_FANNIE,
	N_MSG_NPC_NAME_FAY,
	N_MSG_NPC_NAME_FIONA,
	N_MSG_NPC_NAME_FLORA,
	N_MSG_NPC_NAME_FLORENCE,
	N_MSG_NPC_NAME_FRANCES,
	N_MSG_NPC_NAME_FRANCINE,
	N_MSG_NPC_NAME_FREDA,
	N_MSG_NPC_NAME_GAIL,
	N_MSG_NPC_NAME_GENEVIEVE,
	N_MSG_NPC_NAME_GEORGIANA,
	N_MSG_NPC_NAME_GEORGIE,
	N_MSG_NPC_NAME_GEORGINA,
	N_MSG_NPC_NAME_GERALDINE,
	N_MSG_NPC_NAME_GERDA,
	N_MSG_NPC_NAME_GERTIE,
	N_MSG_NPC_NAME_GERTRUDE,
	N_MSG_NPC_NAME_GILLIAN,
	N_MSG_NPC_NAME_GINEVRA,
	N_MSG_NPC_NAME_GLADYS,
	N_MSG_NPC_NAME_GLORIA,
	N_MSG_NPC_NAME_GLORIANA,
	N_MSG_NPC_NAME_GRACE,
	N_MSG_NPC_NAME_GRETA,
	N_MSG_NPC_NAME_GRETCHEN,
	N_MSG_NPC_NAME_GRISELDA,
	N_MSG_NPC_NAME_GRIZEL,
	N_MSG_NPC_NAME_GUENDOLEN,
	N_MSG_NPC_NAME_GUINEVERE,
	N_MSG_NPC_NAME_GWENEVERE,
	N_MSG_NPC_NAME_HANNAH,
	N_MSG_NPC_NAME_HARRIET,
	N_MSG_NPC_NAME_HAZEL,
	N_MSG_NPC_NAME_HEATHER,
	N_MSG_NPC_NAME_HELEN,
	N_MSG_NPC_NAME_HELOISE,
	N_MSG_NPC_NAME_HENRIETTA,
	N_MSG_NPC_NAME_HENRIETTE,
	N_MSG_NPC_NAME_HERMIONE,
	N_MSG_NPC_NAME_HESTER,
	N_MSG_NPC_NAME_HETTIE,
	N_MSG_NPC_NAME_HILDA,
	N_MSG_NPC_NAME_HILDEGARD,
	N_MSG_NPC_NAME_HOLLY,
	N_MSG_NPC_NAME_HONOR,
	N_MSG_NPC_NAME_IDA,
	N_MSG_NPC_NAME_IMOGEN,
	N_MSG_NPC_NAME_INA,
	N_MSG_NPC_NAME_INEZ,
	N_MSG_NPC_NAME_INGRID,
	N_MSG_NPC_NAME_IONE,
	N_MSG_NPC_NAME_IRIS,
	N_MSG_NPC_NAME_IRMA,
	N_MSG_NPC_NAME_ISABEL,
	N_MSG_NPC_NAME_ISADORA,
	N_MSG_NPC_NAME_JACQUELINE,
	N_MSG_NPC_NAME_JAEL,
	N_MSG_NPC_NAME_JANE,
	N_MSG_NPC_NAME_JANET,
	N_MSG_NPC_NAME_JANICE,
	N_MSG_NPC_NAME_JANIE,
	N_MSG_NPC_NAME_JASMINE,
	N_MSG_NPC_NAME_JEAN,
	N_MSG_NPC_NAME_JEMIMA,
	N_MSG_NPC_NAME_JENNIFER,
	N_MSG_NPC_NAME_JENNY,
	N_MSG_NPC_NAME_JESSAMINE,
	N_MSG_NPC_NAME_JESSICA,
	N_MSG_NPC_NAME_JESSIE,
	N_MSG_NPC_NAME_JILL,
	N_MSG_NPC_NAME_JOAN,
	N_MSG_NPC_NAME_JOANNA,
	N_MSG_NPC_NAME_JOHANNA,
	N_MSG_NPC_NAME_JOSEPHINE,
	N_MSG_NPC_NAME_JOY,
	N_MSG_NPC_NAME_JOYCE,
	N_MSG_NPC_NAME_JUDITH,
	N_MSG_NPC_NAME_JULIA,
	N_MSG_NPC_NAME_JULIANA,
	N_MSG_NPC_NAME_JULIET,
	N_MSG_NPC_NAME_JUNE,
	N_MSG_NPC_NAME_JUSTINA,
	N_MSG_NPC_NAME_JUSTINE,
	N_MSG_NPC_NAME_KAREN,
	N_MSG_NPC_NAME_KATE,
	N_MSG_NPC_NAME_KATHLEEN,
	N_MSG_NPC_NAME_KATHLYN,
	N_MSG_NPC_NAME_KATHY,
	N_MSG_NPC_NAME_KATINA,
	N_MSG_NPC_NAME_KATRINA,
	N_MSG_NPC_NAME_KAY,
	N_MSG_NPC_NAME_KEZIA,
	N_MSG_NPC_NAME_KITTY,
	N_MSG_NPC_NAME_LAETITIA,
	N_MSG_NPC_NAME_LAILA,
	N_MSG_NPC_NAME_LANA,
	N_MSG_NPC_NAME_LAURA,
	N_MSG_NPC_NAME_LAUREL,
	N_MSG_NPC_NAME_LAUREN,
	N_MSG_NPC_NAME_LAVINIA,
	N_MSG_NPC_NAME_LEAH,
	N_MSG_NPC_NAME_LEILA,
	N_MSG_NPC_NAME_LENA,
	N_MSG_NPC_NAME_LENORE,
	N_MSG_NPC_NAME_LEONOR,
	N_MSG_NPC_NAME_LEONORA,
	N_MSG_NPC_NAME_LETITIA,
	N_MSG_NPC_NAME_LIB,
	N_MSG_NPC_NAME_LIBBY,
	N_MSG_NPC_NAME_LILLIAN,
	N_MSG_NPC_NAME_LILY,
	N_MSG_NPC_NAME_LINDA,
	N_MSG_NPC_NAME_LISA,
	N_MSG_NPC_NAME_LOLA,
	N_MSG_NPC_NAME_LOLITA,
	N_MSG_NPC_NAME_LORETTA,
	N_MSG_NPC_NAME_LORNA,
	N_MSG_NPC_NAME_LOTTIE,
	N_MSG_NPC_NAME_LOUISA,
	N_MSG_NPC_NAME_LOUISE,
	N_MSG_NPC_NAME_LUANA,
	N_MSG_NPC_NAME_LUCILLE,
	N_MSG_NPC_NAME_LUCINDA,
	N_MSG_NPC_NAME_LUCRETIA,
	N_MSG_NPC_NAME_LUCY,
	N_MSG_NPC_NAME_LUDMILLA,
	N_MSG_NPC_NAME_LULU,
	N_MSG_NPC_NAME_LYDIA,
	N_MSG_NPC_NAME_LYNETTE,
	N_MSG_NPC_NAME_MABEL,
	N_MSG_NPC_NAME_MADELEINE,
	N_MSG_NPC_NAME_MADELYN,
	N_MSG_NPC_NAME_MAGDALEN,
	N_MSG_NPC_NAME_MAISIE,
	N_MSG_NPC_NAME_MAL,
	N_MSG_NPC_NAME_MALVINA,
	N_MSG_NPC_NAME_MARCIA,
	N_MSG_NPC_NAME_MARGARET,
	N_MSG_NPC_NAME_MARGERY,
	N_MSG_NPC_NAME_MARGO,
	N_MSG_NPC_NAME_MARGOT,
	N_MSG_NPC_NAME_MARIA,
	N_MSG_NPC_NAME_MARIAN,
	N_MSG_NPC_NAME_MARIE,
	N_MSG_NPC_NAME_MARILYN,
	N_MSG_NPC_NAME_MARION,
	N_MSG_NPC_NAME_MARJORIE,
	N_MSG_NPC_NAME_MARLENE,
	N_MSG_NPC_NAME_MARTHA,
	N_MSG_NPC_NAME_MARTINA,
	N_MSG_NPC_NAME_MARY,
	N_MSG_NPC_NAME_MATILDA,
	N_MSG_NPC_NAME_MAUD,
	N_MSG_NPC_NAME_MAUDLIN,
	N_MSG_NPC_NAME_MAUREEN,
	N_MSG_NPC_NAME_MAVIS,
	N_MSG_NPC_NAME_MAXINE,
	N_MSG_NPC_NAME_MAY,
	N_MSG_NPC_NAME_MELINDA,
	N_MSG_NPC_NAME_MELISSA,
	N_MSG_NPC_NAME_MELODY,
	N_MSG_NPC_NAME_MELVINA,
	N_MSG_NPC_NAME_MERCEDES,
	N_MSG_NPC_NAME_MERCY,
	N_MSG_NPC_NAME_MERIEL,
	N_MSG_NPC_NAME_MICHELLE,
	N_MSG_NPC_NAME_MILDRED,
	N_MSG_NPC_NAME_MILLICENT,
	N_MSG_NPC_NAME_MINNIE,
	N_MSG_NPC_NAME_MIRABEL,
	N_MSG_NPC_NAME_MIRANDA,
	N_MSG_NPC_NAME_MIRIAM,
	N_MSG_NPC_NAME_MOIRA,
	N_MSG_NPC_NAME_MOLLY,
	N_MSG_NPC_NAME_MONA,
	N_MSG_NPC_NAME_MONICA,
	N_MSG_NPC_NAME_MURIEL,
	N_MSG_NPC_NAME_MYRA,
	N_MSG_NPC_NAME_MYRTLE,
	N_MSG_NPC_NAME_NADINE,
	N_MSG_NPC_NAME_NAN,
	N_MSG_NPC_NAME_NANCY,
	N_MSG_NPC_NAME_NATALIA,
	N_MSG_NPC_NAME_NATALIE,
	N_MSG_NPC_NAME_NATASHA,
	N_MSG_NPC_NAME_NELLIE,
	N_MSG_NPC_NAME_NINA,
	N_MSG_NPC_NAME_NORA,
	N_MSG_NPC_NAME_NOREEN,
	N_MSG_NPC_NAME_NORMA,
	N_MSG_NPC_NAME_OLIVE,
	N_MSG_NPC_NAME_OLIVIA,
	N_MSG_NPC_NAME_OLYMPIA,
	N_MSG_NPC_NAME_OPHELIA,
	N_MSG_NPC_NAME_ORIANA,
	N_MSG_NPC_NAME_PAMELA,
	N_MSG_NPC_NAME_PANSY,
	N_MSG_NPC_NAME_PATRICIA,
	N_MSG_NPC_NAME_PATSY,
	N_MSG_NPC_NAME_PATTY,
	N_MSG_NPC_NAME_PEARL,
	N_MSG_NPC_NAME_PENELOPE,
	N_MSG_NPC_NAME_PERSIS,
	N_MSG_NPC_NAME_PHILIPPA,
	N_MSG_NPC_NAME_PHOEBE,
	N_MSG_NPC_NAME_PHYLLIS,
	N_MSG_NPC_NAME_POLL,
	N_MSG_NPC_NAME_POLLY,
	N_MSG_NPC_NAME_PRISCILLA,
	N_MSG_NPC_NAME_PRISSY,
	N_MSG_NPC_NAME_RACHEL,
	N_MSG_NPC_NAME_RACHELLE,
	N_MSG_NPC_NAME_RAMONA,
	N_MSG_NPC_NAME_REBECCA,
	N_MSG_NPC_NAME_REGINA,
	N_MSG_NPC_NAME_RHODA,
	N_MSG_NPC_NAME_RITA,
	N_MSG_NPC_NAME_ROBERTA,
	N_MSG_NPC_NAME_ROMY,
	N_MSG_NPC_NAME_ROSE,
	N_MSG_NPC_NAME_ROSEMARY,
	N_MSG_NPC_NAME_ROWENA,
	N_MSG_NPC_NAME_RUBY,
	N_MSG_NPC_NAME_RUTH,
	N_MSG_NPC_NAME_SADIE,
	N_MSG_NPC_NAME_SALLIE,
	N_MSG_NPC_NAME_SAMANTHA,
	N_MSG_NPC_NAME_SARAH,
	N_MSG_NPC_NAME_SELINA,
	N_MSG_NPC_NAME_SELMA,
	N_MSG_NPC_NAME_SERAPHINA,
	N_MSG_NPC_NAME_SHARON,
	N_MSG_NPC_NAME_SHEILA,
	N_MSG_NPC_NAME_SIBYL,
	N_MSG_NPC_NAME_SILVIA,
	N_MSG_NPC_NAME_SONIA,
	N_MSG_NPC_NAME_SOPHIA,
	N_MSG_NPC_NAME_SOPHIE,
	N_MSG_NPC_NAME_STELLA,
	N_MSG_NPC_NAME_STEPHANIE,
	N_MSG_NPC_NAME_SUKEY,
	N_MSG_NPC_NAME_SUSAN,
	N_MSG_NPC_NAME_SUSANNA,
	N_MSG_NPC_NAME_SUSIE,
	N_MSG_NPC_NAME_SUZANNE,
	N_MSG_NPC_NAME_TABITHA,
	N_MSG_NPC_NAME_TALIA,
	N_MSG_NPC_NAME_TALLULAH,
	N_MSG_NPC_NAME_TAMAR,
	N_MSG_NPC_NAME_THELMA,
	N_MSG_NPC_NAME_THERESA,
	N_MSG_NPC_NAME_TIFFANY,
	N_MSG_NPC_NAME_TRIXIE,
	N_MSG_NPC_NAME_UNA,
	N_MSG_NPC_NAME_URSULA,
	N_MSG_NPC_NAME_VALERIA,
	N_MSG_NPC_NAME_VALERIE,
	N_MSG_NPC_NAME_VENUS,
	N_MSG_NPC_NAME_VERA,
	N_MSG_NPC_NAME_VERONICA,
	N_MSG_NPC_NAME_VICTORIA,
	N_MSG_NPC_NAME_VIOLA,
	N_MSG_NPC_NAME_VIOLET,
	N_MSG_NPC_NAME_VIRGINIA,
	N_MSG_NPC_NAME_VIVIEN,
	N_MSG_NPC_NAME_WANDA,
	N_MSG_NPC_NAME_WENDY,
	N_MSG_NPC_NAME_WINIFRED,
	N_MSG_NPC_NAME_XANTHIPPE,
	N_MSG_NPC_NAME_YOLANDA,
	N_MSG_NPC_NAME_YVONNE,
	N_MSG_NPC_NAME_ZELDA,
	N_MSG_NPC_NAME_ZENOBIA,
	N_MSG_NPC_NAME_ZILLAH,

/* NPC name female end */

/* 男女共通 */
/* NPC name male or female begin */

	N_MSG_NPC_NAME_ADRIAN,
	N_MSG_NPC_NAME_ARIEL,
	N_MSG_NPC_NAME_CAROL,
	N_MSG_NPC_NAME_CHRISTIAN,
	N_MSG_NPC_NAME_FREDDIE,
	N_MSG_NPC_NAME_HILARY,
	N_MSG_NPC_NAME_JACKIE,
	N_MSG_NPC_NAME_JODY,
	N_MSG_NPC_NAME_JULIAN,
	N_MSG_NPC_NAME_KIM,
	N_MSG_NPC_NAME_PAT,
	N_MSG_NPC_NAME_RAY,
	N_MSG_NPC_NAME_SIDNEY,
	N_MSG_NPC_NAME_TERRY,
	N_MSG_NPC_NAME_VIVIAN,

	N_MSG_NPC_NAME_ANDREA,
	N_MSG_NPC_NAME_CLAIR,
	N_MSG_NPC_NAME_SHIRLEY,
	N_MSG_NPC_NAME_JOCELYN,
	N_MSG_NPC_NAME_BEVERLY,
	N_MSG_NPC_NAME_HOPE,
	N_MSG_NPC_NAME_MERLE,
	N_MSG_NPC_NAME_LEE,
	N_MSG_NPC_NAME_LYNN,
	N_MSG_NPC_NAME_LINDSAY,
	N_MSG_NPC_NAME_LESLIE,
	N_MSG_NPC_NAME_ROBIN,

/* NPC name male or female end */

	N_MSG_NULL,
};

/* 依頼の男性 NPC の変数のリスト */

n_msg_t	g_ls_npc_name_male[] = {

/* 男性 */
/* NPC name male begin */

	N_MSG_NPC_NAME_AARON,
	N_MSG_NPC_NAME_ABNER,
	N_MSG_NPC_NAME_ABRAHAM,
	N_MSG_NPC_NAME_ABRAM,
	N_MSG_NPC_NAME_ADALBERT,
	N_MSG_NPC_NAME_ADAM,
	N_MSG_NPC_NAME_ADLAI,
	N_MSG_NPC_NAME_ADOLF,
	N_MSG_NPC_NAME_ADOLPHUS,
	N_MSG_NPC_NAME_AENEAS,
	N_MSG_NPC_NAME_ALAN,
	N_MSG_NPC_NAME_ALBERT,
	N_MSG_NPC_NAME_ALBIN,
	N_MSG_NPC_NAME_ALDHELM,
	N_MSG_NPC_NAME_ALDO,
	N_MSG_NPC_NAME_ALDOUS,
	N_MSG_NPC_NAME_ALEC,
	N_MSG_NPC_NAME_ALEX,
	N_MSG_NPC_NAME_ALEXANDER,
	N_MSG_NPC_NAME_ALEXIS,
	N_MSG_NPC_NAME_ALFRED,
	N_MSG_NPC_NAME_ALGERNON,
	N_MSG_NPC_NAME_ALLEN,
	N_MSG_NPC_NAME_ALMON,
	N_MSG_NPC_NAME_ALVAH,
	N_MSG_NPC_NAME_ALVIN,
	N_MSG_NPC_NAME_AMBROSE,
	N_MSG_NPC_NAME_ANDREW,
	N_MSG_NPC_NAME_ANDY,
	N_MSG_NPC_NAME_ANGUS,
	N_MSG_NPC_NAME_ANSEL,
	N_MSG_NPC_NAME_ANSELM,
	N_MSG_NPC_NAME_ANTHONY,
	N_MSG_NPC_NAME_ARCHIBALD,
	N_MSG_NPC_NAME_ARCHIE,
	N_MSG_NPC_NAME_ARNOLD,
	N_MSG_NPC_NAME_ARTHUR,
	N_MSG_NPC_NAME_ASA,
	N_MSG_NPC_NAME_AUBREY,
	N_MSG_NPC_NAME_AUGUST,
	N_MSG_NPC_NAME_AUGUSTUS,
	N_MSG_NPC_NAME_AYLMER,
	N_MSG_NPC_NAME_BARNABAS,
	N_MSG_NPC_NAME_BARNABY,
	N_MSG_NPC_NAME_BARRY,
	N_MSG_NPC_NAME_BARTHOLOMEW,
	N_MSG_NPC_NAME_BASIL,
	N_MSG_NPC_NAME_BENJAMIN,
	N_MSG_NPC_NAME_BENNET,
	N_MSG_NPC_NAME_BERNARD,
	N_MSG_NPC_NAME_BERNHARD,
	N_MSG_NPC_NAME_BERT,
	N_MSG_NPC_NAME_BERTRAM,
	N_MSG_NPC_NAME_BERTRAND,
	N_MSG_NPC_NAME_BOB,
	N_MSG_NPC_NAME_BORIS,
	N_MSG_NPC_NAME_BRENDAN,
	N_MSG_NPC_NAME_BRIAN,
	N_MSG_NPC_NAME_BRUCE,
	N_MSG_NPC_NAME_BUD,
	N_MSG_NPC_NAME_BUDDY,
	N_MSG_NPC_NAME_CALVIN,
	N_MSG_NPC_NAME_CAMERON,
	N_MSG_NPC_NAME_CARL,
	N_MSG_NPC_NAME_CASSANDRA,
	N_MSG_NPC_NAME_CASSIUS,
	N_MSG_NPC_NAME_CECIL,
	N_MSG_NPC_NAME_CEDRIC,
	N_MSG_NPC_NAME_CEPHAS,
	N_MSG_NPC_NAME_CHAD,
	N_MSG_NPC_NAME_CHARLES,
	N_MSG_NPC_NAME_CHESTER,
	N_MSG_NPC_NAME_CHRISTOPHER,
	N_MSG_NPC_NAME_CLARENCE,
	N_MSG_NPC_NAME_CLARK,
	N_MSG_NPC_NAME_CLAUD,
	N_MSG_NPC_NAME_CLEMENT,
	N_MSG_NPC_NAME_CLIFFORD,
	N_MSG_NPC_NAME_CLYDE,
	N_MSG_NPC_NAME_COLIN,
	N_MSG_NPC_NAME_CONRAD,
	N_MSG_NPC_NAME_CONSTANT,
	N_MSG_NPC_NAME_CORNELIUS,
	N_MSG_NPC_NAME_CURTIS,
	N_MSG_NPC_NAME_CYRIL,
	N_MSG_NPC_NAME_CYRUS,
	N_MSG_NPC_NAME_DALE,
	N_MSG_NPC_NAME_DAMON,
	N_MSG_NPC_NAME_DAN,
	N_MSG_NPC_NAME_DANIEL,
	N_MSG_NPC_NAME_DARIUS,
	N_MSG_NPC_NAME_DATUS,
	N_MSG_NPC_NAME_DAVID,
	N_MSG_NPC_NAME_DEAN,
	N_MSG_NPC_NAME_DENNIS,
	N_MSG_NPC_NAME_DEREK,
	N_MSG_NPC_NAME_DICK,
	N_MSG_NPC_NAME_DONALD,
	N_MSG_NPC_NAME_DOUGAL,
	N_MSG_NPC_NAME_DOUGLAS,
	N_MSG_NPC_NAME_DUANE,
	N_MSG_NPC_NAME_DUDLEY,
	N_MSG_NPC_NAME_DUGALD,
	N_MSG_NPC_NAME_DUKE,
	N_MSG_NPC_NAME_DUNCAN,
	N_MSG_NPC_NAME_DWAYNE,
	N_MSG_NPC_NAME_DWIGHT,
	N_MSG_NPC_NAME_EARL,
	N_MSG_NPC_NAME_EDGAR,
	N_MSG_NPC_NAME_EDMUND,
	N_MSG_NPC_NAME_EDWARD,
	N_MSG_NPC_NAME_EDWIN,
	N_MSG_NPC_NAME_EGBERT,
	N_MSG_NPC_NAME_ELBERT,
	N_MSG_NPC_NAME_ELIAS,
	N_MSG_NPC_NAME_ELIPHALET,
	N_MSG_NPC_NAME_ELLA,
	N_MSG_NPC_NAME_ELMER,
	N_MSG_NPC_NAME_ENOCH,
	N_MSG_NPC_NAME_ENOS,
	N_MSG_NPC_NAME_ERIC,
	N_MSG_NPC_NAME_ERNEST,
	N_MSG_NPC_NAME_ETHELBERT,
	N_MSG_NPC_NAME_EUGENE,
	N_MSG_NPC_NAME_EWEN,
	N_MSG_NPC_NAME_EZRA,
	N_MSG_NPC_NAME_FABIAN,
	N_MSG_NPC_NAME_FELIX,
	N_MSG_NPC_NAME_FRANCIS,
	N_MSG_NPC_NAME_FRANK,
	N_MSG_NPC_NAME_FRANKLIN,
	N_MSG_NPC_NAME_FREDERICK,
	N_MSG_NPC_NAME_GABRIEL,
	N_MSG_NPC_NAME_GAD,
	N_MSG_NPC_NAME_GAMALIEL,
	N_MSG_NPC_NAME_GARY,
	N_MSG_NPC_NAME_GEOFFREY,
	N_MSG_NPC_NAME_GEORGE,
	N_MSG_NPC_NAME_GERALD,
	N_MSG_NPC_NAME_GERARD,
	N_MSG_NPC_NAME_GERRY,
	N_MSG_NPC_NAME_GILBERT,
	N_MSG_NPC_NAME_GILES,
	N_MSG_NPC_NAME_GLENN,
	N_MSG_NPC_NAME_GODFREY,
	N_MSG_NPC_NAME_GORDON,
	N_MSG_NPC_NAME_GREGORY,
	N_MSG_NPC_NAME_GRIFFIN,
	N_MSG_NPC_NAME_GRIFFITH,
	N_MSG_NPC_NAME_GUS,
	N_MSG_NPC_NAME_GUSTAVUS,
	N_MSG_NPC_NAME_GUY,
	N_MSG_NPC_NAME_HAMILTON,
	N_MSG_NPC_NAME_HANNIBAL,
	N_MSG_NPC_NAME_HAROLD,
	N_MSG_NPC_NAME_HARRY,
	N_MSG_NPC_NAME_HARVEY,
	N_MSG_NPC_NAME_HECTOR,
	N_MSG_NPC_NAME_HENRY,
	N_MSG_NPC_NAME_HERBERT,
	N_MSG_NPC_NAME_HERCULES,
	N_MSG_NPC_NAME_HERMAN,
	N_MSG_NPC_NAME_HIRAM,
	N_MSG_NPC_NAME_HOMER,
	N_MSG_NPC_NAME_HORACE,
	N_MSG_NPC_NAME_HORATIO,
	N_MSG_NPC_NAME_HOSEA,
	N_MSG_NPC_NAME_HOWARD,
	N_MSG_NPC_NAME_HOWELL,
	N_MSG_NPC_NAME_HUBERT,
	N_MSG_NPC_NAME_HUGH,
	N_MSG_NPC_NAME_HUGO,
	N_MSG_NPC_NAME_HUMPHREY,
	N_MSG_NPC_NAME_IAN,
	N_MSG_NPC_NAME_ION,
	N_MSG_NPC_NAME_IRA,
	N_MSG_NPC_NAME_IRVINE,
	N_MSG_NPC_NAME_IRVING,
	N_MSG_NPC_NAME_ISAAC,
	N_MSG_NPC_NAME_ISADOR,
	N_MSG_NPC_NAME_ISHMAEL,
	N_MSG_NPC_NAME_IVAN,
	N_MSG_NPC_NAME_IVY,
	N_MSG_NPC_NAME_JABEZ,
	N_MSG_NPC_NAME_JACK,
	N_MSG_NPC_NAME_JACKSON,
	N_MSG_NPC_NAME_JACOB,
	N_MSG_NPC_NAME_JAIR,
	N_MSG_NPC_NAME_JAIRUS,
	N_MSG_NPC_NAME_JAMES,
	N_MSG_NPC_NAME_JAMIE,
	N_MSG_NPC_NAME_JASON,
	N_MSG_NPC_NAME_JASPER,
	N_MSG_NPC_NAME_JEDIDIAH,
	N_MSG_NPC_NAME_JEHU,
	N_MSG_NPC_NAME_JEREMIAH,
	N_MSG_NPC_NAME_JEREMY,
	N_MSG_NPC_NAME_JEROBOAM,
	N_MSG_NPC_NAME_JEROME,
	N_MSG_NPC_NAME_JESSE,
	N_MSG_NPC_NAME_JIM,
	N_MSG_NPC_NAME_JIMMY,
	N_MSG_NPC_NAME_JOB,
	N_MSG_NPC_NAME_JOEL,
	N_MSG_NPC_NAME_JOHN,
	N_MSG_NPC_NAME_JOHNNY,
	N_MSG_NPC_NAME_JONAS,
	N_MSG_NPC_NAME_JONATHAN,
	N_MSG_NPC_NAME_JOSEPH,
	N_MSG_NPC_NAME_JOSHUA,
	N_MSG_NPC_NAME_JUDE,
	N_MSG_NPC_NAME_JULIUS,
	N_MSG_NPC_NAME_JUNIUS,
	N_MSG_NPC_NAME_JUSTIN,
	N_MSG_NPC_NAME_KENNETH,
	N_MSG_NPC_NAME_KEVIN,
	N_MSG_NPC_NAME_LAURENCE,
	N_MSG_NPC_NAME_LAZARUS,
	N_MSG_NPC_NAME_LEO,
	N_MSG_NPC_NAME_LEON,
	N_MSG_NPC_NAME_LEONARD,
	N_MSG_NPC_NAME_LEOPOLD,
	N_MSG_NPC_NAME_LESTER,
	N_MSG_NPC_NAME_LEVI,
	N_MSG_NPC_NAME_LEWIS,
	N_MSG_NPC_NAME_LINUS,
	N_MSG_NPC_NAME_LIONEL,
	N_MSG_NPC_NAME_LLOYD,
	N_MSG_NPC_NAME_LUKE,
	N_MSG_NPC_NAME_LUTHER,
	N_MSG_NPC_NAME_MALACHI,
	N_MSG_NPC_NAME_MANFRED,
	N_MSG_NPC_NAME_MARK,
	N_MSG_NPC_NAME_MARMADUKE,
	N_MSG_NPC_NAME_MARTIN,
	N_MSG_NPC_NAME_MATTHEW,
	N_MSG_NPC_NAME_MAURICE,
	N_MSG_NPC_NAME_MAX,
	N_MSG_NPC_NAME_MELVIN,
	N_MSG_NPC_NAME_MICHAEL,
	N_MSG_NPC_NAME_MICK,
	N_MSG_NPC_NAME_MICKY,
	N_MSG_NPC_NAME_MILES,
	N_MSG_NPC_NAME_MILTON,
	N_MSG_NPC_NAME_MORGAN,
	N_MSG_NPC_NAME_MOSES,
	N_MSG_NPC_NAME_NAAMAN,
	N_MSG_NPC_NAME_NAHUM,
	N_MSG_NPC_NAME_NATHAN,
	N_MSG_NPC_NAME_NATHANIEL,
	N_MSG_NPC_NAME_NEAL,
	N_MSG_NPC_NAME_NICHOLAS,
	N_MSG_NPC_NAME_NOAH,
	N_MSG_NPC_NAME_NOEL,
	N_MSG_NPC_NAME_NORMAN,
	N_MSG_NPC_NAME_OLIVER,
	N_MSG_NPC_NAME_ONESIMUS,
	N_MSG_NPC_NAME_ONESIPHORUS,
	N_MSG_NPC_NAME_OSBORN,
	N_MSG_NPC_NAME_OSCAR,
	N_MSG_NPC_NAME_OSWALD,
	N_MSG_NPC_NAME_OTTO,
	N_MSG_NPC_NAME_OWEN,
	N_MSG_NPC_NAME_OZIAS,
	N_MSG_NPC_NAME_PATRICK,
	N_MSG_NPC_NAME_PAUL,
	N_MSG_NPC_NAME_PENUEL,
	N_MSG_NPC_NAME_PERCEVAL,
	N_MSG_NPC_NAME_PERCY,
	N_MSG_NPC_NAME_PETER,
	N_MSG_NPC_NAME_PHILANDER,
	N_MSG_NPC_NAME_PHILIP,
	N_MSG_NPC_NAME_QUENTIN,
	N_MSG_NPC_NAME_QUINCY,
	N_MSG_NPC_NAME_RAFE,
	N_MSG_NPC_NAME_RALPH,
	N_MSG_NPC_NAME_RANDAL,
	N_MSG_NPC_NAME_RANDOLPH,
	N_MSG_NPC_NAME_RAYMOND,
	N_MSG_NPC_NAME_REGGIE,
	N_MSG_NPC_NAME_REGINALD,
	N_MSG_NPC_NAME_REX,
	N_MSG_NPC_NAME_RICHARD,
	N_MSG_NPC_NAME_RICK,
	N_MSG_NPC_NAME_ROB,
	N_MSG_NPC_NAME_ROBERT,
	N_MSG_NPC_NAME_RODERICK,
	N_MSG_NPC_NAME_ROGER,
	N_MSG_NPC_NAME_ROLAND,
	N_MSG_NPC_NAME_RONALD,
	N_MSG_NPC_NAME_ROSS,
	N_MSG_NPC_NAME_ROY,
	N_MSG_NPC_NAME_RUDOLF,
	N_MSG_NPC_NAME_RUFUS,
	N_MSG_NPC_NAME_RUPERT,
	N_MSG_NPC_NAME_RUSSEL,
	N_MSG_NPC_NAME_SAM,
	N_MSG_NPC_NAME_SAMMY,
	N_MSG_NPC_NAME_SAMUEL,
	N_MSG_NPC_NAME_SANDY,
	N_MSG_NPC_NAME_SAUL,
	N_MSG_NPC_NAME_SCOTT,
	N_MSG_NPC_NAME_SHERRY,
	N_MSG_NPC_NAME_SI,
	N_MSG_NPC_NAME_SILAS,
	N_MSG_NPC_NAME_SIMON,
	N_MSG_NPC_NAME_STANLEY,
	N_MSG_NPC_NAME_STEPHEN,
	N_MSG_NPC_NAME_STEVE,
	N_MSG_NPC_NAME_STEVIE,
	N_MSG_NPC_NAME_STEWART,
	N_MSG_NPC_NAME_TED,
	N_MSG_NPC_NAME_TEDDY,
	N_MSG_NPC_NAME_TERENCE,
	N_MSG_NPC_NAME_THADDEUS,
	N_MSG_NPC_NAME_THEODORE,
	N_MSG_NPC_NAME_THEOPHILUS,
	N_MSG_NPC_NAME_THERON,
	N_MSG_NPC_NAME_THOMAS,
	N_MSG_NPC_NAME_TIMOTHY,
	N_MSG_NPC_NAME_TITUS,
	N_MSG_NPC_NAME_TOBIAS,
	N_MSG_NPC_NAME_TOBY,
	N_MSG_NPC_NAME_TOM,
	N_MSG_NPC_NAME_TONY,
	N_MSG_NPC_NAME_TRISTRAM,
	N_MSG_NPC_NAME_TROY,
	N_MSG_NPC_NAME_ULYSSES,
	N_MSG_NPC_NAME_URIAH,
	N_MSG_NPC_NAME_URIAN,
	N_MSG_NPC_NAME_URIEL,
	N_MSG_NPC_NAME_VICTOR,
	N_MSG_NPC_NAME_VINCENT,
	N_MSG_NPC_NAME_WALLACE,
	N_MSG_NPC_NAME_WALT,
	N_MSG_NPC_NAME_WALTER,
	N_MSG_NPC_NAME_WARREN,
	N_MSG_NPC_NAME_WAT,
	N_MSG_NPC_NAME_WILFRED,
	N_MSG_NPC_NAME_WILLAM,
	N_MSG_NPC_NAME_ZANTIPPY,
	N_MSG_NPC_NAME_ZURIEL,

/* NPC name male end */

/* 男女共通 */
/* NPC name male or female begin */

	N_MSG_NPC_NAME_ADRIAN,
	N_MSG_NPC_NAME_ARIEL,
	N_MSG_NPC_NAME_CAROL,
	N_MSG_NPC_NAME_CHRISTIAN,
	N_MSG_NPC_NAME_FREDDIE,
	N_MSG_NPC_NAME_HILARY,
	N_MSG_NPC_NAME_JACKIE,
	N_MSG_NPC_NAME_JODY,
	N_MSG_NPC_NAME_JULIAN,
	N_MSG_NPC_NAME_KIM,
	N_MSG_NPC_NAME_PAT,
	N_MSG_NPC_NAME_RAY,
	N_MSG_NPC_NAME_SIDNEY,
	N_MSG_NPC_NAME_TERRY,
	N_MSG_NPC_NAME_VIVIAN,

	N_MSG_NPC_NAME_ANDREA,
	N_MSG_NPC_NAME_CLAIR,
	N_MSG_NPC_NAME_SHIRLEY,
	N_MSG_NPC_NAME_JOCELYN,
	N_MSG_NPC_NAME_BEVERLY,
	N_MSG_NPC_NAME_HOPE,
	N_MSG_NPC_NAME_MERLE,
	N_MSG_NPC_NAME_LEE,
	N_MSG_NPC_NAME_LYNN,
	N_MSG_NPC_NAME_LINDSAY,
	N_MSG_NPC_NAME_LESLIE,
	N_MSG_NPC_NAME_ROBIN,

/* NPC name male or female end */

	N_MSG_NULL,
};

/* 依頼の女性の家族の変数のリスト */

n_msg_t	g_ls_family_female[] = {
	N_MSG_NPC_NAME_FAMILY,
	N_MSG_NPC_NAME_GRAND_MOTHER,
	N_MSG_NPC_NAME_GRAND_FATHER,
	N_MSG_NPC_NAME_MOTHER,
	N_MSG_NPC_NAME_FATHER,
	N_MSG_NPC_NAME_OLDER_SISTER,
	N_MSG_NPC_NAME_OLDER_BROTHER,
	N_MSG_NPC_NAME_YOUNGER_SISTER,
	N_MSG_NPC_NAME_YOUNGER_BROTHER,
	N_MSG_NPC_NAME_DAUGHTER,
	N_MSG_NPC_NAME_SON,
	N_MSG_NPC_NAME_HUSBAND,
	N_MSG_NPC_NAME_BOY_FRIEND,
	N_MSG_NULL,
};

/* 依頼の男性の家族の変数のリスト */

n_msg_t	g_ls_family_male[] = {
	N_MSG_NPC_NAME_FAMILY,
	N_MSG_NPC_NAME_GRAND_MOTHER,
	N_MSG_NPC_NAME_GRAND_FATHER,
	N_MSG_NPC_NAME_MOTHER,
	N_MSG_NPC_NAME_FATHER,
	N_MSG_NPC_NAME_OLDER_SISTER,
	N_MSG_NPC_NAME_OLDER_BROTHER,
	N_MSG_NPC_NAME_YOUNGER_SISTER,
	N_MSG_NPC_NAME_YOUNGER_BROTHER,
	N_MSG_NPC_NAME_DAUGHTER,
	N_MSG_NPC_NAME_SON,
	N_MSG_NPC_NAME_WIFE,
	N_MSG_NPC_NAME_GIRL_FRIEND,
	N_MSG_NULL,
};

#endif	/* REQUEST_TAB_H */
