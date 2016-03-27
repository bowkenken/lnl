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
* $Id: PcgDun.cpp,v 1.149 2014/03/07 09:15:21 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ���󥸥����������
////////////////////////////////////////////////////////////////

#define	PCG_DUN_CPP	1
#include "inc.h"

////////////////////////////////////////////////////////////////

#include "PcgDunTab.h"

////////////////////////////////////////////////////////////////

// �ѥ�����Υ��������ޥå׾�����襵������Ϥ߽ФƤ��ɤ�;��
#define MAP_DRAW_ADD_R	1

// ���Ĥ�ʸ���� TextOut() ��Ȥä����褹�뤫��
#define FLAG_USE_TEXT_OUT	0

// �����롦��������ե���ȡ��������˹�碌�뤫��
#define FLAG_FONT_TO_TEXT_SIZE	0

// ����������˺����褹�뤫��
# define FLAG_REDRAW_SCROLL	1

////////////////////////////////////////////////////////////////
// �ѥ����󡦥���ǥå����Υơ��֥�
////////////////////////////////////////////////////////////////

const long gBitIdxWallN = 1 << 0;
const long gBitIdxWallS = 1 << 1;
const long gBitIdxWallE = 1 << 2;
const long gBitIdxWallW = 1 << 3;

pos_t gIdxWall[2 * 2 * 2 * 2] = {
	{ +3, +3 }, //....
	{ +3, +2 }, //...N
	{ +3, +0 }, //..S.
	{ +3, +1 }, //..SN

	{ +0, +3 }, //.E.
	{ +0, +2 }, //.E.N
	{ +0, +0 }, //.ES.
	{ +0, +1 }, //.ESN

	{ +2, +3 }, //W...
	{ +2, +2 }, //W..N
	{ +2, +0 }, //W.S.
	{ +2, +1 }, //W.SN

	{ +1, +3 }, //WE..
	{ +1, +2 }, //WE.N
	{ +1, +0 }, //WES.
	{ +1, +1 }, //WESN
};

const long gBitIdxWallNE = 1 << 0;
const long gBitIdxWallNW = 1 << 1;
const long gBitIdxWallSE = 1 << 2;
const long gBitIdxWallSW = 1 << 3;

pos_t gIdxWallDiagonal[2 * 2 * 2 * 2] = {
	{ +1, +1 }, //.. .. .. ..
	{ +1, +1 }, //.. .. .. NE
	{ +1, +1 }, //.. .. NW ..
	{ +1, +1 }, //.. .. NW NE

	{ +1, +1 }, //.. SE .. ..
	{ +1, +1 }, //.. SE .. NE
	{ +1, +1 }, //.. SE NW ..
	{ +1, +4 }, //.. SE NW NE

	{ +1, +1 }, //SW .. .. ..
	{ +1, +1 }, //SW .. .. NE
	{ +1, +1 }, //SW .. NW ..
	{ +0, +4 }, //SW .. NW NE

	{ +1, +1 }, //SW SE .. ..
	{ +3, +4 }, //SW SE .. NE
	{ +2, +4 }, //SW SE NW ..
	{ +1, +1 }, //SW SE NW NE
};

////////////////////////////////////////////////////////////////
// ��Υ��˥�
////////////////////////////////////////////////////////////////

static const long nWaterAnimeMaxX = 4;
static const long nWaterAnimeMaxY = 4;
static const long nWaterAnimeMaxN = nWaterAnimeMaxX * nWaterAnimeMaxY;

////////////////////////////////////////////////////////////////

#ifdef D_WS
extern WSCform *MapForm;
extern WSCvscrBar *MapScrollX;
extern WSCvscrBar *MapScrollY;
#endif // D_WS

#ifdef D_GTK
static GdkFont *gSelFont;

static void handle_sel_font_destroy(
	GtkWidget *widget, gpointer user_data
);
static void handle_sel_font_ok(
	GtkWidget *widget, gpointer *data
);
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

PcgDun::PcgDun()
{
	pGraphConf = NULL;
	pDemoTitle = NULL;
	pDemoLastBoss = NULL;
	pDemoGameOver = NULL;
	pDemoEnding = NULL;

	pWBuf = NULL;

	nTileSizeX = 32;
	nTileSizeY = 32;
	nTileSizeRate = _100_PERCENT;

	nPtnDirMbr = N_PTN_DIR_CHR_1;
	nPtnDirMnstr = N_PTN_DIR_CHR_1;

	nWaterAnimeN = 0;

	nTextModeDefaultPoint = 16;

	pStyle = NULL;
	nTextSizeX = 16;
	nTextSizeY = 16;
	nIntervalWidth = 1;
	nIntervalHeight = 1;

	bFlgEnaDrawTurn = false;

#ifdef D_MFC
	pDc = NULL;
	pSignboardFont = NULL;

	pDcVfx = NULL;
#endif // D_MFC

	resetUpdateFlg();
	setFlgUpdateRequest( true );
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

PcgDun::~PcgDun()
{
	if( pWBuf != NULL ){
		delete pWBuf;
		pWBuf = NULL;
	}

#ifdef D_MFC
	if( pSignboardFont != NULL ){
		delete pSignboardFont;
		pSignboardFont = NULL;
	}

	if( pDc != NULL ){
		delete pDc;
		pDc = NULL;
	}

	if( pDcVfx != NULL ){
		delete pDcVfx;
		pDcVfx = NULL;
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �����ȥ�ν����
////////////////////////////////////////////////////////////////

void PcgDun::initTitle()
{
	if( !g_flg_gui )
		return;

	if( pDemoTitle != NULL )
		return;

	pDemoTitle = new DemoTitle;
	pDemoTitle->init();
}

////////////////////////////////////////////////////////////////
// �饹�ܥ��ν����
////////////////////////////////////////////////////////////////

void PcgDun::initLastBoss()
{
	if( !g_flg_gui )
		return;

	if( pDemoLastBoss != NULL )
		return;

	pDemoLastBoss = new DemoLastBoss;
	pDemoLastBoss->init();

	lastBossXX.init();
}

////////////////////////////////////////////////////////////////
// �����ࡦ�����С��ν����
////////////////////////////////////////////////////////////////

void PcgDun::initGameOver()
{
	if( !g_flg_gui )
		return;

	if( pDemoGameOver != NULL )
		return;

	pDemoGameOver = new DemoGameOver;
	pDemoGameOver->init();
}

////////////////////////////////////////////////////////////////
// ����ǥ��󥰤ν����
////////////////////////////////////////////////////////////////

void PcgDun::initEnding()
{
	if( !g_flg_gui )
		return;

	if( pDemoEnding != NULL )
		return;

	pDemoEnding = new DemoEnding;
	pDemoEnding->init();
}

////////////////////////////////////////////////////////////////
// �����
// GraphConf *cnf : ����ե��å�����
////////////////////////////////////////////////////////////////

void PcgDun::init( GraphConf *cnf )
{
	if( !g_flg_gui )
		return;

	if( cnf == NULL )
		exit_game( EXIT_FAILURE );

	pGraphConf = cnf;
	initGraphConf( cnf );

	resetSignboardFont();

	initLastBoss();
	initGameOver();
	initEnding();

	// �������롦�С���Ĵ��

#ifdef D_MFC
	CXlnlView *view = theApp.m_pMainFrm->GetView();
	view->ResetScroll();
#endif // D_MFC

	if( g_flg_text_mode ){
		resetUpdateFlg();
		return;
	}

	// �ѥ����󸡺�������

	WSCstring path = cnf->getDir();
	long w = path.getWords( "/" );
	WSCstring dir = path.getWord( w - 1, "/" );

	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList fls;

	// ̤õ��
	initPcgLsRandm( cnf, &pcgNullTown, gPcgTabNullTown );
	initPcgLsRandm( cnf, &pcgNullDun, gPcgTabNullTown );

	// ��
	initPcgLsRandm( cnf, &pcgFloorTown, gPcgTabFloorTown );
	initPcgLsRandm( cnf, &pcgFloorDun, gPcgTabFloorDun );
	initPcgLsRandm( cnf, &pcgFloorLast, gPcgTabFloorLast );

	// ����

	initPcgLsRandm( cnf, &pcgHole, gPcgTabHole );

	// ��
	initPcgLsRandm( cnf, &pcgWallTown, gPcgTabWallTown );
	initPcgLsRandm( cnf, &pcgWallDun, gPcgTabWallDun );
	initPcgLsRandm( cnf, &pcgWallLast, gPcgTabWallLast );
	initPcgLsRandm( cnf, &pcgStatue, gPcgTabStatue );
	initPcgLsRandm( cnf, &pcgBootUnit, gPcgTabBootUnit );

	// ����
	initPcgLsRandm( cnf, &pcgStreetlampOn, gPcgTabStreetlampOn );
	initPcgLsRandm( cnf, &pcgStreetlampOff, gPcgTabStreetlampOff );

	// ����
	initPcgLsRandm( cnf, &pcgSignboard, gPcgTabSignboard );

	// ��
	// �ϴ�
	initPcgLsRandm( cnf, &pcgLava, gPcgTabLava );

	// ��곬��
	initPcgLsRandm( cnf, &pcgStairsUpTown, gPcgTabStairsUpTown );
	initPcgLsRandm( cnf, &pcgStairsUpDun, gPcgTabStairsUpDun );

	// ���곬��
	initPcgLsRandm( cnf, &pcgStairsDownTown, gPcgTabStairsDownTown );
	initPcgLsRandm( cnf, &pcgStairsDownDun, gPcgTabStairsDownDun );
	initPcgLsRandm( cnf, &pcgStairsLastBoss, gPcgTabStairsLastBoss );

	// �Ĥޤä��ɥ�
	initPcgLsRandm( cnf, &pcgDoorCloseTown, gPcgTabDoorCloseTown );
	initPcgLsRandm( cnf, &pcgDoorCloseDun, gPcgTabDoorCloseDun );

	// �������ɥ�
	initPcgLsRandm( cnf, &pcgDoorOpenTown, gPcgTabDoorOpenTown );
	initPcgLsRandm( cnf, &pcgDoorOpenDun, gPcgTabDoorOpenDun );

	// �Ĥޤä���
	initPcgLsRandm( cnf, &pcgWindowClose, gPcgTabWindowClose );

	// ��������
	initPcgLsRandm( cnf, &pcgWindowOpen, gPcgTabWindowOpen );

	// �
	initPcgLsRandm( cnf, &pcgTrap, gPcgTabTrap );

	// ��������

	for( long i = 0; i < ATTITUDE_MAX_N; i++ )
		aPcgCrsr[i] = NULL;
	for( long i = 0; i < LOOP_MAX_100; i++ ){
		if( gPcgTabCrsr[i].nRatio <= -1 )
			break;

		attitude_t kind = (attitude_t)
				(gPcgTabCrsr[i].nKind);

		WSCstring sLoadPath = "";
		fls.reset( gPcgTabCrsr[i].sDir, ext );
		for( long n = 0; n < LOOP_MAX_100; n++ ){
			WSCstring path = fls.next();
			if( path.getChars() <= 0 )
				break;

			if( per_randm( n + 1 ) )
				sLoadPath = path;
		}
		if( sLoadPath.getChars() <= 0 )
			continue;

		aPcgCrsr[kind] = new Pcg;
		if( aPcgCrsr[kind] == NULL )
			continue;
		aPcgCrsr[kind]->init( sLoadPath );
		// aPcgCrsr[kind]->dis();
	}

	// ���֡���������

	for( long i = 0; i < ATTITUDE_MAX_N; i++ )
		aPcgCrsrSub[i] = NULL;
	for( long i = 0; i < LOOP_MAX_100; i++ ){
		if( gPcgTabCrsrSub[i].nRatio <= -1 )
			break;

		attitude_t kind = (attitude_t)
				(gPcgTabCrsrSub[i].nKind);

		WSCstring sLoadPath = "";
		fls.reset( gPcgTabCrsrSub[i].sDir, ext );
		for( long n = 0; n < LOOP_MAX_100; n++ ){
			WSCstring path = fls.next();
			if( path.getChars() <= 0 )
				break;

			if( per_randm( n + 1 ) )
				sLoadPath = path;
		}
		if( sLoadPath.getChars() <= 0 )
			continue;

		aPcgCrsrSub[kind] = new Pcg;
		if( aPcgCrsrSub[kind] == NULL )
			continue;
		aPcgCrsrSub[kind]->init( sLoadPath );
		// aPcgCrsrSub[kind]->dis();
	}

	// ���󥫡�
	initPcgLsRandm( cnf, &pcgSquareParty, gPcgTabSquareParty );
	initPcgLsRandm( cnf, &pcgSquareMbr, gPcgTabSquareMbr );

	// �����ƥ�
	initPcgLsRandm( cnf, &pcgItem, gPcgTabItem );

	// ���С�

	for( long i = 0; i < LS_MBR_MAX_N; i++ )
		aPcgMbr[i] = NULL;

	reloadAllMbr();

	// ��󥹥���

	for( long i = 0; i < MNSTR_KIND_MAX_N; i++ )
		aPcgMnstr[i] = NULL;
	for( long i = 0; i < LOOP_MAX_1000; i++ ){
		if( gPcgTabMnstr[i].nRatio <= -1 )
			break;

		mnstr_kind_t kind = (mnstr_kind_t)
				(gPcgTabMnstr[i].nKind);

		WSCstring sLoadPath = "";
		fls.reset( gPcgTabMnstr[i].sDir, ext );
		for( long n = 0; n < LOOP_MAX_100; n++ ){
			WSCstring path = fls.next();
			if( path.getChars() <= 0 )
				break;

			if( per_randm( n + 1 ) )
				sLoadPath = path;
		}
		if( sLoadPath.getChars() <= 0 )
			continue;

		aPcgMnstr[kind] = new Pcg;
		if( aPcgMnstr[kind] == NULL )
			continue;
		aPcgMnstr[kind]->init( sLoadPath );
		aPcgMnstr[kind]->dis();
	}
	for( long i = 0; i < LOOP_MAX_1000; i++ ){
		if( gPcgTabMnstrHyper[i].nRatio <= -1 )
			break;

		mnstr_kind_t kind = (mnstr_kind_t)
				gPcgTabMnstrHyper[i].nKind;
		if( aPcgMnstr[kind] == NULL )
			continue;

		WSCstring sLoadPath = "";
		fls.reset( gPcgTabMnstrHyper[i].sDir, ext );
		for( long n = 0; n < LOOP_MAX_100; n++ ){
			WSCstring path = fls.next();
			if( path.getChars() <= 0 )
				break;

			if( per_randm( n + 1 ) )
				sLoadPath = path;
		}
		if( sLoadPath.getChars() <= 0 )
			continue;

		aPcgMnstr[kind]->hyper_boss = new Pcg;
		if( aPcgMnstr[kind]->hyper_boss == NULL )
			continue;
		aPcgMnstr[kind]->hyper_boss->init( sLoadPath );
		aPcgMnstr[kind]->hyper_boss->dis();
	}

	// ����� VFX
	initPcgLsRandm( cnf, &pcgGuiVfxBash, gPcgTabGuiVfxBash );
	// ����ƥ����빶��� VFX
	initPcgLsRandm( cnf, &pcgGuiVfxBashCrtcl, gPcgTabGuiVfxBashCrtcl );
	// ��� VFX
	initPcgLsRandm( cnf, &pcgGuiVfxArw, gPcgTabGuiVfxArw );

	// ��ʸ�� VFX
	for( long i = 0; i < RESI_KIND_MAX_N; i++ )
		aPcgGuiVfxSpell[i] = NULL;
	for( long i = 0; i < LOOP_MAX_100; i++ ){
		if( gPcgTabGuiVfxSpell[i].nRatio <= -1 )
			break;

		resi_kind_t kind = (resi_kind_t)
				(gPcgTabGuiVfxSpell[i].nKind);

		WSCstring sLoadPath = "";
		fls.reset( gPcgTabGuiVfxSpell[i].sDir, ext );
		for( long n = 0; n < LOOP_MAX_100; n++ ){
			WSCstring path = fls.next();
			if( path.getChars() <= 0 )
				break;

			if( per_randm( n + 1 ) )
				sLoadPath = path;
		}
		if( sLoadPath.getChars() <= 0 )
			continue;

		aPcgGuiVfxSpell[kind] = new Pcg;
		if( aPcgGuiVfxSpell[kind] == NULL )
			continue;
		aPcgGuiVfxSpell[kind]->init( sLoadPath );
		// aPcgGuiVfxSpell[kind]->dis();
	}

	// ������ VFX
	for( long i = 0; i < BLAST_KIND_MAX_N; i++ )
		aPcgGuiVfxBlast[i] = NULL;
	for( long i = 0; i < LOOP_MAX_100; i++ ){
		if( gPcgTabGuiVfxBlast[i].nRatio <= -1 )
			break;

		blast_kind_t kind = (blast_kind_t)
				(gPcgTabGuiVfxBlast[i].nKind);

		WSCstring sLoadPath = "";
		fls.reset( gPcgTabGuiVfxBlast[i].sDir, ext );
		for( long n = 0; n < LOOP_MAX_100; n++ ){
			WSCstring path = fls.next();
			if( path.getChars() <= 0 )
				break;

			if( per_randm( n + 1 ) )
				sLoadPath = path;
		}
		if( sLoadPath.getChars() <= 0 )
			continue;

		aPcgGuiVfxBlast[kind] = new Pcg;
		if( aPcgGuiVfxBlast[kind] == NULL )
			continue;
		aPcgGuiVfxBlast[kind]->init( sLoadPath );
		// aPcgGuiVfxBlast[kind]->dis();
	}

	// Ǧ��
	initPcgLsRandm( cnf, &pcgGuiVfxNinja, gPcgTabGuiVfxNinja );
}

////////////////////////////////////////////////////////////////
// �ѥ�����Υե������������ 1 ������ǽ����
// GraphConf *cnf : ����ե��å�����
// Pcg *p : �ꥹ�Ȥ���Ƭ
// PcgTab tab[] : �ѥ�����Υơ��֥�
////////////////////////////////////////////////////////////////

void PcgDun::initPcgLsRandm( GraphConf *cnf, Pcg *ls, PcgTab tab[] )
{
	if( !g_flg_gui )
		return;

	if( cnf == NULL )
		return;
	if( ls == NULL )
		return;
	if( tab == NULL )
		return;

	// �ѥ����󸡺�������

	WSCstring basePath = cnf->getDir();
	long w = basePath.getWords( "/" );
	WSCstring dir = basePath.getWord( w - 1, "/" );

	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList fls;

	//

	ls->next = NULL;
	Pcg *p = ls;
	ratio_t nRatioSum = (ratio_t)0;
	for( long i = 0; i < LOOP_MAX_100; i++ ){
		if( tab[i].nRatio <= -1 )
			break;

		WSCstring sLoadPath = "";
		fls.reset( tab[i].sDir, ext );
		for( long n = 0; n < LOOP_MAX_100; n++ ){
			WSCstring path = fls.next();
			if( path.getChars() <= 0 )
				break;

			if( per_randm( n + 1 ) )
				sLoadPath = path;
		}
		if( sLoadPath.getChars() <= 0 )
			continue;

		p->next = new Pcg();
		if( p->next == NULL )
			break;
		p = p->next;

		p->init( sLoadPath );
		p->mjr = tab[i].mjr;
		p->mnr = tab[i].mnr;
		p->nRatio = tab[i].nRatio;

		nRatioSum += tab[i].nRatio;
	}

	ratio_t ratio = (ratio_t)0;
	rate_t preRate = (rate_t)0;
	for( p = ls->next; p != NULL; p = p->next ){
		ratio += p->nRatio;
		rate_t rate = (rate_t)1;
		if( nRatioSum > 0 )
			rate = ratio * _100_PERCENT / nRatioSum;
		if( rate <= preRate )
			rate = preRate + 1;
		if( p->next == NULL )
			rate = _100_PERCENT;

		p->nRate = rate;
		preRate = rate;
	}
}

////////////////////////////////////////////////////////////////
// ����ե��å�����ǽ����
// GraphConf *cnf : ����ե��å�����
////////////////////////////////////////////////////////////////

void PcgDun::initGraphConf( GraphConf *cnf )
{
	if( !g_flg_gui )
		return;

//@@@	WSCstring door_patern;
//	WSCstring signboard_patern;

	// �����롦������

	nTileSizeX = cnf->getNum( GRAPH_CONF_TOKEN_TILE_SIZE_X );
	nTileSizeY = cnf->getNum( GRAPH_CONF_TOKEN_TILE_SIZE_Y );

#ifdef D_GTK
	// ����Ψ
	nTileSizeRate = cnf->getNum( GRAPH_CONF_TOKEN_SCALE );
	g_graph_scale_rate = nTileSizeRate;
#endif // D_GTK

#ifdef D_MAC
	// ����Ψ
	nTileSizeRate = _100_PERCENT;
	g_graph_scale_rate = nTileSizeRate;
#endif // D_MAC

#ifdef D_IPHONE
	// ����Ψ
	nTileSizeRate = _100_PERCENT;
	g_graph_scale_rate = nTileSizeRate;
#endif // D_IPHONE

#ifdef D_MFC
	// ����Ū�ʳ���Ψ
	nTileSizeRate = _100_PERCENT;
	g_graph_scale_rate = nTileSizeRate;
	// �ºݤγ���Ψ
	g_Dir3d.nTileSizeRate
			= cnf->getNum( GRAPH_CONF_TOKEN_SCALE );
#endif // D_MFC

	WSCstring pt;

	// �ɤΥѥ����󡦥�����
	nWallPtnTypeTown = WALL_PTN_TYPE_TILE;
	nWallPtnTypeDun = WALL_PTN_TYPE_TILE;
	nWallPtnTypeLast = WALL_PTN_TYPE_B;

	pt = cnf->getStr( GRAPH_CONF_TOKEN_WALL_PATERN );
	if( pt == "tile" ){
		nWallPtnTypeTown = WALL_PTN_TYPE_TILE;
		nWallPtnTypeDun = WALL_PTN_TYPE_TILE;
		nWallPtnTypeLast = WALL_PTN_TYPE_TILE;
	}
	if( pt == "type_a" ){
		nWallPtnTypeTown = WALL_PTN_TYPE_A;
		nWallPtnTypeDun = WALL_PTN_TYPE_A;
		nWallPtnTypeLast = WALL_PTN_TYPE_A;
	}
	if( pt == "type_b" ){
		nWallPtnTypeTown = WALL_PTN_TYPE_B;
		nWallPtnTypeDun = WALL_PTN_TYPE_B;
		nWallPtnTypeLast = WALL_PTN_TYPE_B;
	}

	pt = cnf->getStr( GRAPH_CONF_TOKEN_TOWN_WALL_PATERN );
	if( pt == "tile" ){
		nWallPtnTypeTown = WALL_PTN_TYPE_TILE;
	}
	if( pt == "type_a" ){
		nWallPtnTypeTown = WALL_PTN_TYPE_A;
	}
	if( pt == "type_b" ){
		nWallPtnTypeTown = WALL_PTN_TYPE_B;
	}

	pt = cnf->getStr( GRAPH_CONF_TOKEN_DUNGEON_WALL_PATERN );
	if( pt == "tile" ){
		nWallPtnTypeDun = WALL_PTN_TYPE_TILE;
	}
	if( pt == "type_a" ){
		nWallPtnTypeDun = WALL_PTN_TYPE_A;
	}
	if( pt == "type_b" ){
		nWallPtnTypeDun = WALL_PTN_TYPE_B;
	}

	// ����饯���Υѥ����󡦥�����

	nPtnDirMbr = N_PTN_DIR_CHR_1;
	nPtnDirMnstr = N_PTN_DIR_CHR_1;

	pt = cnf->getStr( GRAPH_CONF_TOKEN_CHARACTER_PATERN );
	if( pt == "tile" ){
		nPtnDirMbr = N_PTN_DIR_CHR_1;
		nPtnDirMnstr = N_PTN_DIR_CHR_1;
	}
	if( pt == "RPG_XP" ){
		nPtnDirMbr = N_PTN_DIR_CHR_4;
		nPtnDirMnstr = N_PTN_DIR_CHR_4;
	}
	if( pt == "RPG_2000" ){
		nPtnDirMbr = N_PTN_DIR_CHR_4;
		nPtnDirMnstr = N_PTN_DIR_CHR_4;
	}

	// PC �Υѥ����󡦥����פǾ��

	pt = cnf->getStr( GRAPH_CONF_TOKEN_PC_PATERN );
	if( pt == "tile" )
		nPtnDirMbr = N_PTN_DIR_CHR_1;
	if( pt == "RPG_XP" )
		nPtnDirMbr = N_PTN_DIR_CHR_4;
	if( pt == "RPG_2000" )
		nPtnDirMbr = N_PTN_DIR_CHR_4;

	// ��󥹥����Υѥ����󡦥����פǾ��

	pt = cnf->getStr( GRAPH_CONF_TOKEN_MONSTER_PATERN );
	if( pt == "tile" )
		nPtnDirMnstr = N_PTN_DIR_CHR_1;
	if( pt == "RPG_XP" )
		nPtnDirMnstr = N_PTN_DIR_CHR_4;
	if( pt == "RPG_2000" )
		nPtnDirMnstr = N_PTN_DIR_CHR_4;

	// �ƥ����ȡ��⡼��

	if( cnf->getNum( GRAPH_CONF_TOKEN_TEXT_MODE ) != 0 )
		g_flg_text_mode = TRUE;
	else
		g_flg_text_mode = FALSE;

	// �ƥ����ȡ��⡼�ɻ��Υե���ȥ�����

#ifdef D_GTK
	nTextModeDefaultPoint = cnf->getNum(
			GRAPH_CONF_TOKEN_FONT_SIZE_POINT );
#endif // D_GTK

#ifdef D_MAC
	nTextModeDefaultPoint = _100_PERCENT;
#endif // D_MAC

#ifdef D_IPHONE
	nTextModeDefaultPoint = _100_PERCENT;
#endif // D_IPHONE

#ifdef D_MFC
	nTextModeDefaultPoint = cnf->getNum(
			GRAPH_CONF_TOKEN_FONT_SIZE_DOT );
#endif // D_MFC

	g_text_mode_point = nTextModeDefaultPoint;

	nTextSizeX = nTileSizeX;
	nTextSizeY = nTileSizeY;

	if( g_flg_text_mode )
		bFlgEnaDrawTurn = false;
	else
		bFlgEnaDrawTurn = true;
	
#ifdef D_MAC
//@@@
	bFlgEnaDrawTurn = true;
#endif // D_MAC
}

////////////////////////////////////////////////////////////////
// �ꥻ�å�
////////////////////////////////////////////////////////////////

void PcgDun::reset()
{
	if( !g_flg_gui )
		return;

	resetUpdateFlg();

	if( g_flg_text_mode )
		return;

	resetMap();

	for( long i = 0; i < MNSTR_KIND_MAX_N; i++ )
		if( aPcgMnstr[i] != NULL )
			aPcgMnstr[i]->dis();
}

////////////////////////////////////////////////////////////////
// �����С��Υѥ��������ɹ�
////////////////////////////////////////////////////////////////

void PcgDun::reloadAllMbr()
{
	if( !g_flg_gui )
		return;

	long seed = get_randm_seed();

	mbr_t **ls_mbr = get_ls_mbr();
	GraphConf *cnf = pGraphConf;

	// �ѥ����󸡺�������

	WSCstring path = cnf->getDir();
	long w = path.getWords( "/" );
	WSCstring dir = path.getWord( w - 1, "/" );

	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList fls;

	for( long i = 0; i < LS_MBR_MAX_N; i++ ){
		if( aPcgMbr[i] != NULL ){
			delete aPcgMbr[i];
			aPcgMbr[i] = NULL;
		}
	}

	for( long i = 0; i < LS_MBR_MAX_N; i++ ){
		fls.reset( gPcgTabMbrDflt.sDir, ext );
		WSCstring sFixPath = fls.jointDir( fls.getBaseDir(),
				gPcgTabMbrDflt.sDir );

		// ���С����ǡ����ǥե����뤬���ꤵ��Ƥ��뤫�����å�

		bool flagExist = true;
		if( ls_mbr[i] == NULL )
			flagExist = false;
		else if( chk_flg( ls_mbr[i]->stat, FLG_STAT_NOT_EXIST ) )
			flagExist = false;
		else if( ls_mbr[i]->graph_name[0] == '\0' )
			flagExist = false;

		// ���ꤵ��Ƥ���Х���

		if( flagExist ){
			sFixPath = fls.jointDir( sFixPath,
					ls_mbr[i]->graph_name );

			// �ե����뤬����Х���

			if( chk_exist_file( sFixPath ) ){
				if( !reloadMbr( i, sFixPath ) )
					break;
				continue;
			}
		}

		// ���ꤵ��Ƥ��ʤ���Х�����ǥ���

		WSCstring sLoadPath = "";
		fls.reset( gPcgTabMbrNull.sDir, ext );
		for( long n = 0; n < LOOP_MAX_1000; n++ ){
			WSCstring path = fls.next();
			if( path.getChars() <= 0 )
				break;

			if( per_randm( n + 1 ) )
				sLoadPath = path;
		}
		if( sLoadPath.getChars() <= 0 )
			continue;

		if( !reloadMbr( i, sLoadPath ) )
			break;
	}

	srandm( seed );
}

////////////////////////////////////////////////////////////////
// ���С��Υѥ��������ɹ�
// long nLsMbrN : ���С����ꥹ�ȤΥ���ǥå���
// WSCstring path : �ѥ����󡦥ե�����Υѥ�̾
////////////////////////////////////////////////////////////////

bool PcgDun::reloadMbr( long nLsMbrN, WSCstring path )
{
	if( !g_flg_gui )
		return false;

	if( nLsMbrN < 0 )
		return false;
	if( nLsMbrN >= LS_MBR_MAX_N )
		return false;

	// �ե����뤬����Х���

	if( !chk_exist_file( path ) )
		return false;

	if( aPcgMbr[nLsMbrN] != NULL )
		delete aPcgMbr[nLsMbrN];
	aPcgMbr[nLsMbrN] = new Pcg;
	if( aPcgMbr[nLsMbrN] == NULL )
		return false;

	aPcgMbr[nLsMbrN]->load( path );

	return true;
}

////////////////////////////////////////////////////////////////
// ���ĤΥե���Ȥ�ꥻ�å�
////////////////////////////////////////////////////////////////

void PcgDun::resetSignboardFont()
{
	if( !g_flg_gui )
		return;

	nSignboardIntervalWidth = (4 * 2) * nTileSizeRate / _100_PERCENT;
	nSignboardIntervalHeight = (4 * 2) * nTileSizeRate / _100_PERCENT;

#ifdef D_GTK
	// �ǥե���ȤΥ������������

	if( pSignboardStyle == NULL ){
		pSignboardStyle = gtk_style_copy(
				gtk_widget_get_default_style() );
	}
	if( pSignboardStyle->fg_gc[GTK_STATE_NORMAL] == NULL ){
		pSignboardStyle->fg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}
	if( pSignboardStyle->bg_gc[GTK_STATE_NORMAL] == NULL ){
		pSignboardStyle->bg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}

	// �ե���ȤΥ���������ݥ���ȿ����Ѵ�

	nSignboardPoint = 80;
	WSCstring sFontName;

	// �����롦�������˹礦�ե���ȡ�����������ʬõ��

	long pntMin = 80;
	long pntMax = 320;
	long pnt = pntMin;
	while( (pntMin + 1) < pntMax ){
		pnt = (pntMin + pntMax) / 2;
		if( setSignboardFont( pnt, &sFontName ) )
			pntMin = pnt;
		else
			pntMax = pnt;
	}
	nSignboardPoint = pntMin;

	setSignboardFont( nSignboardPoint, &sFontName );
#endif // D_GTK

#ifdef D_MAC
//@@@
#endif // D_MAC

#ifdef D_IPHONE
//@@@
#endif // D_IPHONE

#ifdef D_MFC
	LONG h = getTileSizeY() - nSignboardIntervalHeight;
	h = h * g_Dir3d.nTileSizeRate / _100_PERCENT;
	mSignboardFontDesc.lfHeight = h;
	mSignboardFontDesc.lfWidth = 0;
	mSignboardFontDesc.lfEscapement = 0;
	mSignboardFontDesc.lfOrientation = 0;
	mSignboardFontDesc.lfWeight = FW_NORMAL;
	mSignboardFontDesc.lfItalic = FALSE;
	mSignboardFontDesc.lfUnderline = FALSE;
	mSignboardFontDesc.lfStrikeOut = FALSE;
	mSignboardFontDesc.lfCharSet = SHIFTJIS_CHARSET;
	mSignboardFontDesc.lfOutPrecision
			= OUT_DEFAULT_PRECIS;
	mSignboardFontDesc.lfClipPrecision
			= CLIP_DEFAULT_PRECIS;
	mSignboardFontDesc.lfQuality = DEFAULT_QUALITY;
	mSignboardFontDesc.lfPitchAndFamily
			= (FIXED_PITCH | FF_MODERN);
	strcpy( mSignboardFontDesc.lfFaceName, "Pica" );

	pSignboardFont = new CFont;
	pSignboardFont->CreateFontIndirect(
			&mSignboardFontDesc );

	mD3Signboard.Create( &mSignboardFontDesc );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ���ĤΥե���Ȥ�����
// long pnt : �ե���ȤΥݥ���ȿ�
// return : �ե���Ȥ���ॿ���륵�����˼��ޤä���?
////////////////////////////////////////////////////////////////

bool PcgDun::setSignboardFont( long pnt, WSCstring *pFontName )
{
	if( !g_flg_gui )
		return false;

#ifdef D_GTK
	WSCstring sFontPoint = pnt;
	WSCstring sFontName = "";
	sFontName += "-*-*-*-r-normal-*-*-";
	sFontName += sFontPoint;
	sFontName += "-*,-*";

	*pFontName = sFontName;

	gtk_style_set_font( pSignboardStyle, gdk_fontset_load( sFontName ) );

	// �ե���ȡ�������������

	GdkFont *font = gtk_style_get_font( pSignboardStyle );
	if( font == NULL )
		return false;
	gdk_string_extents( font, "M",
			&nSignboardLeftBearing, &nSignboardRightBearing,
			&nSignboardWidth,
			&nSignboardAscent, &nSignboardDescent );

	nSignboardSizeX = nSignboardLeftBearing + nSignboardRightBearing
			+ nSignboardIntervalWidth;
	nSignboardSizeY = nSignboardAscent + nSignboardDescent
			+ nSignboardIntervalHeight;

	// �ե���ȡ�������������å�

	if( nSignboardSizeX > getTileSizeX( false ) )
		return false;
	if( nSignboardSizeY > getTileSizeY( false ) )
		return false;
#endif // D_GTK

	return true;
}

////////////////////////////////////////////////////////////////
// �ѥ�����ο�ʿ�����δ�ॵ�������֤�
// return : ��ॵ����
////////////////////////////////////////////////////////////////

long PcgDun::getTileSizeX( bool flgText )
{
	if( !g_flg_gui )
		return CUI_TILE_SIZE_X;

	long n = 1;

	if( g_flg_text_mode && flgText )
		n = nTextSizeX * nTileSizeRate / _100_PERCENT;
	else
		n = nTileSizeX * nTileSizeRate / _100_PERCENT;

	if( n < 1 )
		n = 1;

	return n;
}

////////////////////////////////////////////////////////////////
// �ѥ�����ο�ľ�����δ�ॵ�������֤�
// return : ��ॵ����
////////////////////////////////////////////////////////////////

long PcgDun::getTileSizeY( bool flgText )
{
	if( !g_flg_gui )
		return CUI_TILE_SIZE_Y;

	long n = 1;

	if( g_flg_text_mode && flgText )
		n = nTextSizeY * nTileSizeRate / _100_PERCENT;
	else
		n = nTileSizeY * nTileSizeRate / _100_PERCENT;

	if( n < 1 )
		n = 1;

	return n;
}

////////////////////////////////////////////////////////////////
// �ƥ����ȡ��⡼�ɤΥե���ȡ����������֤�
// return : �ե���ȡ�������
////////////////////////////////////////////////////////////////

long PcgDun::getTextModePoint()
{
	if( !g_flg_gui )
		return 1;

	long n = g_text_mode_point * nTileSizeRate / _100_PERCENT;

	if( n < 1 )
		n = 1;

	return n;
}

////////////////////////////////////////////////////////////////
// �ѥ�����ΥХꥨ������󡦥ޥåפΥꥻ�å�
////////////////////////////////////////////////////////////////

void PcgDun::resetMap()
{
	if( !g_flg_gui )
		return;

	for( long y = 0; y < MAP_MAX_Y; y++ )
		for( long x = 0; x < MAP_MAX_X; x++ )
			rateMap[y][x] = gui_randm( _100_PERCENT );
}

////////////////////////////////////////////////////////////////
// ���֥롦�Хåե����֤�
// return : �ե졼�ࡦ�Хåե�
////////////////////////////////////////////////////////////////

WSDmwindowDev *PcgDun::getWBuf()
{
	if( !g_flg_gui )
		return NULL;

	if( pWBuf == NULL ){
		pWBuf = WSDmwindowDev::getNewInstance();
		pWBuf->createPixmap(
				MAP_MAX_X * getTileSizeX( true ),
				MAP_MAX_Y * getTileSizeY( true ) );
	}

	return pWBuf;
}

////////////////////////////////////////////////////////////////
// ���֥롦�Хåե�����ݤ��ʤ���
// return : �ե졼�ࡦ�Хåե�
////////////////////////////////////////////////////////////////

WSDmwindowDev *PcgDun::ReNewWBuf()
{
	if( !g_flg_gui )
		return NULL;

#ifdef D_GTK
	if( pWBuf == NULL ){
		getWBuf();
		return pWBuf;
	}

	gdk_pixmap_unref( pWBuf->getPixMap() );

	pWBuf->createPixmap(
			MAP_MAX_X * getTileSizeX( true ),
			MAP_MAX_Y * getTileSizeY( true ) );
#endif // D_GTK

	return pWBuf;
}

////////////////////////////////////////////////////////////////
// �ޥåפ����Х�������ʥ�����κ�ɸ�ǻ��ꤹ���
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
////////////////////////////////////////////////////////////////

void PcgDun::scrollTileRel( long mapDX, long mapDY )
{
	pos_t *draw_gui = get_map_draw_pos_gui();
	if( draw_gui == NULL )
		return;

	scrollTile( draw_gui->x + mapDX, draw_gui->y + mapDY );
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ�������ʥ�����κ�ɸ�ǻ��ꤹ���
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
////////////////////////////////////////////////////////////////

void PcgDun::scrollTile( long mapX, long mapY )
{
	scrollMap(
			mapX * getTileSizeX( true ),
			mapY * getTileSizeY( true ) );
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ�������ʥɥåȤκ�ɸ�ǻ��ꤹ���
// long x : X ��ɸ
// long y : Y ��ɸ
////////////////////////////////////////////////////////////////

void PcgDun::scrollMap( long x, long y )
{
	long maxX = getScrollBarMaxX();
	long maxY = getScrollBarMaxY();
	long w = getScrollBarW();
	long h = getScrollBarH();

	if( x < 0 )
		x = 0;
	if( y < 0 )
		y = 0;
	if( x > maxX )
		x = maxX;
	if( y > maxY )
		y = maxY;

#if	defined( D_MAC )
//@@@
	//@@@gMainMapView.visibleRect.origin.x = x;
	//@@@gMainMapView.visibleRect.origin.y = y;
NSLog( @"scr y:%ld x:%ld\n", x, y );//@@@
	setScrollBarX( x );
	setScrollBarY( y );
#elif	defined( D_IPHONE )
	CGPoint pt;
	pt.x = x;
	pt.y = y;
	[gMainMapWin.mapScrollView setContentOffset:pt animated:YES];
#else	// D_IPHONE
	setScrollBarX( x );
	setScrollBarY( y );
#endif	// D_IPHONE

	drawScroll( x, y, w, h );

#ifdef D_MFC
	if( g_flg_gui )
		g_Dir3d.SetRefreshRequest( true );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �ޥåפ��������뤷�����褹��ɬ�פ�ͭ�뤫�����å�
// long x : X ��ɸ
// long y : Y ��ɸ
// long w : ��
// long h : �⤵
// return : ���褹��ɬ�פ�ͭ�뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::chkScroll( long x, long y, long w, long h )
{
	x /= getTileSizeX( true );
	y /= getTileSizeY( true );

	static long preX = -1;
	static long preY = -1;
	static long preW = -1;
	static long preH = -1;

	if( (x == preX) && (y == preY) && (w == preW) && (h == preH) )
		return false;

	preX = x;
	preY = y;
	preW = w;
	preH = h;

	return true;
}

////////////////////////////////////////////////////////////////
// �ޥåפ��������뤷����������
// long x : X ��ɸ
// long y : Y ��ɸ
// long w : ��
// long h : �⤵
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawScroll( long x, long y, long w, long h )
{
	if( !g_flg_gui ){
		redraw_map();
		return true;
	}

	setFlgUpdateRequest( true );

	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) ){
		if( gSelMbrGraph != NULL )
			gSelMbrGraph->draw();
		return true;
	}
	if( chk_scene_group( SCENE_GROUP_N_DEMO ) )
		return true;

	if( chk_nest_flg_dun() )
		return false;

#if FLAG_REDRAW_SCROLL || defined( D_MFC )
	redraw( true );
	return true;
#else
	sort_all_chr( TRUE );

	long sizX = getTileSizeX( true );
	long sizY = getTileSizeY( true );

	long mapX1 = x / sizX;
	long mapY1 = y / sizY;
	long mapX2 = (x + w + sizX - 1) / sizX;
	long mapY2 = (y + h + sizY - 1) / sizY;
	long mapW = mapX2 - mapX1;
	long mapH = mapY2 - mapY1;

	dun_t *dun = get_dun();
	bool flg_chk = true;
	if( (dun->lev == 0) && !chk_day() )
		flg_chk = false;

	for( long yy = mapY1; yy < mapY2; yy++ ){
		for( long xx = mapX1; xx < mapX2; xx++ ){
			if( flg_chk )
				if( !getUpdateFlg( xx, yy ) )
					continue;

			if( !drawTile( xx, yy, false ) )
				return false;
		}
	}

	flush( mapX1, mapY1, mapW, mapH );

	return true;
#endif
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��ξ�����֤�
// SCROLLINFO *info : ������֤���
// int sb : �������롦�С��μ���
////////////////////////////////////////////////////////////////

#ifdef D_MFC
void PcgDun::getScrollInfo( SCROLLINFO *info, int sb )
{
	if( !g_flg_gui )
		return;

	if( info == NULL )
		return;
	if( theApp.m_pMainFrm == NULL )
		return;

	HWND hWnd = theApp.m_pMainFrm->GetViewWnd();

	info->cbSize = sizeof( *info );
	info->fMask = SIF_ALL;
	::GetScrollInfo( hWnd, sb, info );
}
#endif // D_MFC

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��ΰ��֤�����
// int sb : �������롦�С��μ���
// int pos : �������롦�С��ΰ���
////////////////////////////////////////////////////////////////

#ifdef D_MFC
void PcgDun::setScrollInfoPos( int sb, int pos )
{
	if( !g_flg_gui )
		return;

	if( theApp.m_pMainFrm == NULL )
		return;

	HWND hWnd = theApp.m_pMainFrm->GetViewWnd();

	SCROLLINFO info;
	info.cbSize = sizeof( info );
	info.fMask = SIF_POS;
	info.nPos = pos;

	SetScrollInfo( hWnd, sb, &info, TRUE );

	g_Dir3d.SetRefreshRequest( true );
}
#endif // D_MFC

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��� X ��ɸ���֤�
// return : X ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getScrollBarX()
{
	if( !g_flg_gui ){
		pos_t *draw_gui = get_map_draw_pos_gui();
		if( draw_gui == NULL )
			return 0;
		else
			return( draw_gui->x * getTileSizeX( true ) );
	}

	long x = 0;

#ifdef D_WS
	x = (long)MapScrollX->getProperty( WSNvalue );
#endif // D_WS

#ifdef D_GTK
	GtkAdjustment *hAdj = GTK_ADJUSTMENT( gMapHScrollBarAdjustment );

	x = (long)hAdj->value;
#endif // D_GTK

#ifdef D_MAC
	double cx = (long)(gMainMapScrollView.contentView.bounds.origin.x);
	double dx = (long)(((NSView *)(gMainMapScrollView.documentView)).frame.origin.x);
	x = cx - dx;
#endif // D_MAC

#ifdef D_IPHONE
	x = gMainMapWin.mapScrollView.contentOffset.x;
#endif // D_IPHONE

#ifdef D_MFC
	SCROLLINFO info;
	getScrollInfo( &info, SB_HORZ );

	x = info.nPos;
#endif // D_MFC

	return x;
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��� Y ��ɸ���֤�
// return : Y ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getScrollBarY()
{
	if( !g_flg_gui ){
		pos_t *draw_gui = get_map_draw_pos_gui();
		if( draw_gui == NULL )
			return 0;
		else
			return( draw_gui->y * getTileSizeY( true ) );
	}

	long y = 0;

#ifdef D_WS
	y = (long)MapScrollY->getProperty( WSNvalue );
#endif // D_WS

#ifdef D_GTK
	GtkAdjustment *vAdj = GTK_ADJUSTMENT( gMapVScrollBarAdjustment );

	y = (long)vAdj->value;
#endif // D_GTK

#ifdef D_MAC
	double cy = (long)(gMainMapScrollView.contentView.bounds.origin.y);
	double dy = (long)(((NSView *)(gMainMapScrollView.documentView)).frame.origin.y);
	y = cy - dy;
#endif // D_MAC

#ifdef D_IPHONE
	y = gMainMapWin.mapScrollView.contentOffset.y;
#endif // D_IPHONE

#ifdef D_MFC
	SCROLLINFO info;
	getScrollInfo( &info, SB_VERT );

	y = info.nPos;
#endif // D_MFC

	return y;
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��������֤�
// return : ��
////////////////////////////////////////////////////////////////

long PcgDun::getScrollBarW()
{
	if( !g_flg_gui )
		return( get_map_col() / 2 * getTileSizeX( true ) );
	
	long w = 1;

#ifdef D_WS
	w = (long)MapScrollX->getProperty( WSNsliderSize );
#endif // D_WS

#ifdef D_GTK
	GtkAdjustment *hAdj = GTK_ADJUSTMENT( gMapHScrollBarAdjustment );

	w = (long)hAdj->page_size;
#endif // D_GTK

#ifdef D_MAC
//@@@
	//@@@w = gMainMapView.visibleRect.size.width;
	w = gMainMapView.bounds.size.width;
#endif // D_MAC

#ifdef D_IPHONE
	UIScrollView *v = gMainMapWin.mapScrollView;
	w = (long)(v.bounds.size.width * v.zoomScale);
#endif // D_IPHONE

#ifdef D_MFC
	SCROLLINFO info;
	getScrollInfo( &info, SB_HORZ );

	w = info.nPage;
	if( g_Dir3d.nTileSizeRate > 0 )
		w = w * _100_PERCENT / g_Dir3d.nTileSizeRate;
#endif // D_MFC

	return w;
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��ι⤵���֤�
// return : �⤵
////////////////////////////////////////////////////////////////

long PcgDun::getScrollBarH()
{
	if( !g_flg_gui )
		return( get_map_row() * getTileSizeY( true ) );

	long h = 1;

#ifdef D_WS
	h = (long)MapScrollY->getProperty( WSNsliderSize );
#endif // D_WS

#ifdef D_GTK
	GtkAdjustment *vAdj = GTK_ADJUSTMENT( gMapVScrollBarAdjustment );

	h = (long)vAdj->page_size;
#endif // D_GTK

#ifdef D_MAC
//@@@
	//@@@h = gMainMapView.visibleRect.size.height;
	h = gMainMapView.bounds.size.height;
#endif // D_MAC

#ifdef D_IPHONE
	UIScrollView *v = gMainMapWin.mapScrollView;
	h = (long)(v.bounds.size.height * v.zoomScale);
#endif // D_IPHONE

#ifdef D_MFC
	SCROLLINFO info;
	getScrollInfo( &info, SB_VERT );

	h = info.nPage;
	if( g_Dir3d.nTileSizeRate > 0 )
		h = h * _100_PERCENT / g_Dir3d.nTileSizeRate;
#endif // D_MFC

	return h;
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��κ��� X ��ɸ���֤�
// return : ���� X ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getScrollBarMaxX()
{
	long maxX = 1;

	if( !g_flg_gui ){
		maxX = MAP_MAX_X * getTileSizeX( true );
		maxX -= getScrollBarW();
		return maxX;
	}

	long w = 1;

#ifdef D_WS
	maxX = (long)MapScrollX->getProperty( WSNmaximum );
#endif // D_WS

#ifdef D_GTK
	GtkAdjustment *hAdj = GTK_ADJUSTMENT( gMapHScrollBarAdjustment );

	w = (long)hAdj->page_size;
	maxX = (long)hAdj->upper - w;
#endif // D_GTK

#ifdef D_MAC
	w = getScrollBarW();
	maxX = (MAP_MAX_X * getTileSizeX( true )) - w;
#endif // D_MAC

#ifdef D_IPHONE
	w = getScrollBarW();
	maxX = (MAP_MAX_X * getTileSizeX( true )) - w;
#endif // D_IPHONE

#ifdef D_MFC
	SCROLLINFO info;
	getScrollInfo( &info, SB_HORZ );

	maxX = info.nMax - info.nPage + 2;
#endif // D_MFC

	return maxX;
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��κ��� Y ��ɸ���֤�
// return : ���� Y ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getScrollBarMaxY()
{
	long maxY = 1;

	if( !g_flg_gui ){
		maxY = MAP_MAX_Y * getTileSizeY( true );
		maxY -= getScrollBarH();
		return maxY;
	}

	long h = 1;

#ifdef D_WS
	maxY = (long)MapScrollY->getProperty( WSNmaximum );
#endif // D_WS

#ifdef D_GTK
	GtkAdjustment *vAdj = GTK_ADJUSTMENT( gMapVScrollBarAdjustment );

	h = (long)vAdj->page_size;
	maxY = (long)vAdj->upper - h;
#endif // D_GTK

#ifdef D_MAC
	h = getScrollBarH();
	maxY = (MAP_MAX_Y * getTileSizeY( true )) - h;
#endif // D_MAC

#ifdef D_IPHONE
	h = getScrollBarH();
	maxY = (MAP_MAX_Y * getTileSizeY( true )) - h;
#endif // D_IPHONE

#ifdef D_MFC
	SCROLLINFO info;
	getScrollInfo( &info, SB_VERT );

	maxY = info.nMax - info.nPage + 1;
#endif // D_MFC

	return maxY;
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��� X ��ɸ������
////////////////////////////////////////////////////////////////

void PcgDun::setScrollBarX( long x )
{
	pos_t *draw_gui = get_map_draw_pos_gui();
	if( draw_gui != NULL )
		draw_gui->x = x / getTileSizeX( true );

	if( !g_flg_gui )
		return;

#ifdef D_WS
	MapScrollX->setProperty( WSNvalue, x );
#endif // D_WS

#ifdef D_GTK
	GtkAdjustment *hAdj = GTK_ADJUSTMENT( gMapHScrollBarAdjustment );
	hAdj->value = x;
	gtk_adjustment_value_changed( hAdj );
#endif // D_GTK

#ifdef D_MAC
	NSPoint p = NSMakePoint( x, getScrollBarY() );
	[gMainMapScrollView.documentView scrollPoint:p];
	setFlgUpdateRequest( true );
#endif // D_MAC

#ifdef D_IPHONE
	CGPoint pt = gMainMapWin.mapScrollView.contentOffset;
	pt.x = x;
	[gMainMapWin.mapScrollView setContentOffset:pt];

	setFlgUpdateRequestIPhone( true );
#endif // D_IPHONE

#ifdef D_MFC
	setScrollInfoPos( SB_HORZ, x );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �ޥåפΥ������롦�С��� Y ��ɸ������
////////////////////////////////////////////////////////////////

void PcgDun::setScrollBarY( long y )
{
	pos_t *draw_gui = get_map_draw_pos_gui();
	if( draw_gui != NULL )
		draw_gui->y = y / getTileSizeY( true );

	if( !g_flg_gui )
		return;

#ifdef D_WS
	MapScrollY->setProperty( WSNvalue, y );
#endif // D_WS

#ifdef D_GTK
	GtkAdjustment *vAdj = GTK_ADJUSTMENT( gMapVScrollBarAdjustment );
	vAdj->value = y;
	gtk_adjustment_value_changed( vAdj );
#endif // D_GTK

#ifdef D_MAC
	NSPoint p = NSMakePoint( getScrollBarX(), y );
	[gMainMapScrollView.documentView scrollPoint:p];
	setFlgUpdateRequest( true );
#endif // D_MAC

#ifdef D_IPHONE
	CGPoint pt = gMainMapWin.mapScrollView.contentOffset;
	pt.y = y;
	[gMainMapWin.mapScrollView setContentOffset:pt];

	setFlgUpdateRequestIPhone( true );
#endif // D_IPHONE

#ifdef D_MFC
	setScrollInfoPos( SB_VERT, y );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ���ޥåפΥ�����ɥ����ϰ��⤫Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : �ϰ��⤫��
////////////////////////////////////////////////////////////////

bool PcgDun::clipWin( long mapX, long mapY )
{
	return( clipWinX( mapX ) && clipWinY( mapY ) );
}

////////////////////////////////////////////////////////////////
// ����� X ��ɸ���ޥåפΥ�����ɥ����ϰ��⤫Ĵ�٤�
// long mapX : X ��ɸ
// return : �ϰ��⤫��
////////////////////////////////////////////////////////////////

bool PcgDun::clipWinX( long mapX )
{
	long minX = getScrollBarX();
	long maxX = (getScrollBarW() - 1) + minX;
	long x1 = mapX * getTileSizeX( true );
	long x2 = x1 + (getTileSizeX( true ) - 1);

	if( x2 < minX )
		return false;
	if( x1 > maxX )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ����� Y ��ɸ���ޥåפΥ�����ɥ����ϰ��⤫Ĵ�٤�
// long mapX : Y ��ɸ
// return : �ϰ��⤫��
////////////////////////////////////////////////////////////////

bool PcgDun::clipWinY( long mapY )
{
	long minY = getScrollBarY();
	long maxY = (getScrollBarH() - 1) + minY;
	long y1 = mapY * getTileSizeY( true );
	long y2 = y1 + (getTileSizeY( true ) - 1);

	if( y2 < minY )
		return false;
	if( y1 > maxY )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// �ޥåפκ�����
// bool flgForce : ��������
////////////////////////////////////////////////////////////////

void PcgDun::redraw( bool flgForce )
{
	if( !g_flg_gui )
		return;

	setFlgUpdateRequest( true );

	if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) ){
		if( gSelMbrGraph != NULL )
			gSelMbrGraph->draw();
		return;
	}

	if( bFlgEnaDrawTurn && !flgForce )
		return;

	sort_all_chr( TRUE );

	setUpdateFlgRange( 0, 0, MAP_MAX_X, MAP_MAX_Y, true );
	drawTurn( true );

#ifdef	D_MAC
	drawUpdate( 0, 0, MAP_MAX_X, MAP_MAX_Y );
#endif	// D_MAC

#if	D_IPHONE
	drawUpdate( 0, 0, MAP_MAX_X, MAP_MAX_Y );
#endif	// D_IPHONE
}

////////////////////////////////////////////////////////////////
// �ޥåפ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long mapW : ��
// long mapH : �⤵
// bool flgForce : ��������
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::draw(
	long mapX, long mapY,
	long mapW, long mapH,
	bool flgForce
)
{
	if( !g_flg_gui )
		return true;

	setFlgUpdateRequest( true );

	setUpdateFlgRange( mapX, mapY, mapW, mapH, true );

	if( bFlgEnaDrawTurn && !flgForce )
		return true;
	if( chk_nest_flg_dun() )
		return false;

	drawSub( mapX, mapY, mapW, mapH );
	flush( mapX, mapY, mapW, mapH );

	return true;
}

////////////////////////////////////////////////////////////////
// ��������Υޥåפ�����
// bool flgForce : ��������
////////////////////////////////////////////////////////////////

void PcgDun::drawTurn( bool flgForce )
{
	if( !g_flg_gui )
		return;

	if( !getFlgUpdateRequest() && !flgForce )
		return;
	if( !bFlgEnaDrawTurn && !flgForce )
		return;
	if( chk_nest_flg_dun() ){
		resetUpdateFlg();

		return;
	}

	drawTurnSub();
	drawTurnFlush();
}

////////////////////////////////////////////////////////////////
// ��������Υޥåפ����� (�ե�å���̵��)
////////////////////////////////////////////////////////////////

void PcgDun::drawTurnSub()
{
	if( !g_flg_gui )
		return;

	long x = getScrollBarX();
	long y = getScrollBarY();
	long w = getScrollBarW();
	long h = getScrollBarH();
	long sizX = getTileSizeX( true );
	long sizY = getTileSizeY( true );

	long mapX1 = x / sizX;
	long mapY1 = y / sizY;
	long mapX2 = (x + w + (sizX - 1)) / sizX;
	long mapY2 = (y + h + (sizY - 1)) / sizY;
	long mapW = mapX2 - mapX1;
	long mapH = mapY2 - mapY1;

	nWaterAnimeN++;
	nWaterAnimeN %= nWaterAnimeMaxN;

	drawSub( mapX1, mapY1, mapW, mapH );
}

////////////////////////////////////////////////////////////////
// ��������Υޥåפ�����Υե�å���
////////////////////////////////////////////////////////////////

void PcgDun::drawTurnFlush()
{
	if( !g_flg_gui )
		return;

	long x = getScrollBarX();
	long y = getScrollBarY();
	long w = getScrollBarW();
	long h = getScrollBarH();

	long sizX = getTileSizeX( true );
	long sizY = getTileSizeY( true );

	long mapX1 = x / sizX;
	long mapY1 = y / sizY;
	long mapX2 = (x + w + (sizX - 1)) / sizX;
	long mapY2 = (y + h + (sizY - 1)) / sizY;
	long mapW = mapX2 - mapX1;
	long mapH = mapY2 - mapY1;

	flush( mapX1, mapY1, mapW, mapH );
}

////////////////////////////////////////////////////////////////
// �ޥåפ�̤�����ϰϤΤ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long mapW : ��
// long mapH : �⤵
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawUpdate( long mapX, long mapY, long mapW, long mapH )
{
	drawSub( mapX, mapY, mapW, mapH, true );
	flush( mapX, mapY, mapW, mapH );
	setUpdateFlgRange( mapX, mapY, mapW, mapH, false );

	return true;
}

////////////////////////////////////////////////////////////////
// �ޥåפ�����ζ��̴ؿ�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long mapW : ��
// long mapH : �⤵
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawSub(
	long mapX, long mapY, long mapW, long mapH,
	bool flgUpdateAll
)
{
	if( !g_flg_gui )
		return true;

	if( g_flg_text_mode )
		return drawText( mapX, mapY, mapW, mapH );

#ifdef D_IPHONE
	setFlgUpdateRequestIPhone( false );
#endif // D_IPHONE

	static long preAnime = 0;
	static long preTurn = 0;
	if( (preAnime == nWaterAnimeN) && preTurn != get_turn() ){
		nWaterAnimeN++;
		nWaterAnimeN %= nWaterAnimeMaxN;

		preAnime = nWaterAnimeN;
		preTurn = get_turn();
	}

//@@@	setFlgUpdateRequest( true );

	long mapX1 = mapX - MAP_DRAW_ADD_R;
	long mapY1 = mapY - MAP_DRAW_ADD_R;
	long mapX2 = mapX + mapW + MAP_DRAW_ADD_R;
	long mapY2 = mapY + mapH + MAP_DRAW_ADD_R;

	long objX1 = mapX;
	long objY1 = mapY;
	long objX2 = mapX + mapW;
	long objY2 = mapY + mapH;

	long sx = mapX1 * getTileSizeX();
	long sy = mapY1 * getTileSizeY();
	long sw = (mapX2 - mapX1) * getTileSizeX();
	long sh = (mapY2 - mapY1) * getTileSizeY();

	dun_t *dun = get_dun();

	// �����ƥ����ե饰������

	if( !flgUpdateAll ){
		for( long y = mapY1; y < mapY2; y++ ){
			for( long x = mapX1; x < mapX2; x++ ){
				if( !clipWin( x, y ) ){
					setUpdateFlg( x, y, true );
				}
			}
		}
	}

	// �������

	for( long y = objY1; y < objY2; y++ ){
		for( long x = objX1; x < objX2; x++ ){
			if( !flgUpdateAll && !clipWin( x, y ) )
				continue;
			if( flgUpdateAll && !getUpdateFlg( x, y ) )
				continue;

			if( !drawWater( x, y ) )
				setUpdateFlg( x, y, true );
		}
	}

	// �饹�ܥ����ط�¦������

	lastBossXX.drawBg();

	// ���֥������Ȥ�����

	bool flg_chk = true;
	if( (dun->lev == 0) && !chk_day() )
		flg_chk = false;

	for( long y = objY1; y < objY2; y++ ){
		for( long x = objX1; x < objX2; x++ ){
			if( flg_chk )
				if( !getUpdateFlg( x, y ) )
					continue;
			if( !flgUpdateAll && !clipWin( x, y ) )
				continue;
			if( flgUpdateAll && !getUpdateFlg( x, y ) )
				continue;

#ifdef D_MFC
			drawObj( x, y );
			setUpdateFlg( x, y, true );
#else // D_MFC
			if( drawObj( x, y ) && !bFlgEnaDrawTurn ){
				if( !flgUpdateAll ){
					setUpdateFlg( x, y, false );
				}
			} else {
				setUpdateFlg( x, y, true );
			}
#endif // D_MFC
		}
	}

	// 櫤�����

	for( long y = mapY1; y < mapY2; y++ ){
		for( long x = mapX1; x < mapX2; x++ ){
			if( !flgUpdateAll && !clipWin( x, y ) )
				continue;
			if( flgUpdateAll && !getUpdateFlg( x, y ) )
				continue;

			if( !drawTrap( x, y ) )
				setUpdateFlg( x, y, true );
		}
	}

	// ���ʤ�����

	for( long y = mapY1; y < mapY2; y++ ){
		for( long x = mapX1; x < mapX2; x++ ){
			if( !flgUpdateAll && !clipWin( x, y ) )
				continue;
			if( flgUpdateAll && !getUpdateFlg( x, y ) )
				continue;

			if( !drawStairsUp( x, y ) )
				setUpdateFlg( x, y, true );
			if( !drawStairsDown( x, y ) )
				setUpdateFlg( x, y, true );
		}
	}

	// �ѡ��ƥ������󥫡�������

	for( long y = mapY1; y < mapY2; y++ ){
		for( long x = mapX1; x < mapX2; x++ ){
			if( !flgUpdateAll && !clipWin( x, y ) )
				continue;
			if( flgUpdateAll && !getUpdateFlg( x, y ) )
				continue;

			if( !drawSquareParty( x, y ) )
				setUpdateFlg( x, y, true );
		}
	}

	// ���С������󥫡�������

	for( long y = mapY1; y < mapY2; y++ ){
		for( long x = mapX1; x < mapX2; x++ ){
			if( !flgUpdateAll && !clipWin( x, y ) )
				continue;
			if( flgUpdateAll && !getUpdateFlg( x, y ) )
				continue;

			if( !drawSquareMbrAll( x, y ) )
				setUpdateFlg( x, y, true );
		}
	}

	// �����ƥ������

	for( long y = mapY1; y < mapY2; y++ ){
		for( long x = mapX1; x < mapX2; x++ ){
			if( !flgUpdateAll && !clipWin( x, y ) )
				continue;
			if( flgUpdateAll && !getUpdateFlg( x, y ) )
				continue;

			if( !drawItemAll( x, y ) )
				setUpdateFlg( x, y, true );
		}
	}

	// ����������

	for( long y = mapY1; y < mapY2; y++ ){
		for( long x = mapX1; x < mapX2; x++ ){
			if( !flgUpdateAll && !clipWin( x, y ) )
				continue;
			if( flgUpdateAll && !getUpdateFlg( x, y ) )
				continue;

			if( !drawStatue( x, y ) )
				setUpdateFlg( x, y, true );
		}
	}

	// ��ư���֤�����

	if( get_scene() == SCENE_N_LAST_BOSS ){
		for( long y = mapY1; y < mapY2; y++ ){
			for( long x = mapX1; x < mapX2; x++ ){
				if( !flgUpdateAll && !clipWin( x, y ) )
					continue;
				if( flgUpdateAll && !getUpdateFlg( x, y ) )
					continue;

				if( !drawBootUnit( x, y ) )
					setUpdateFlg( x, y, true );
			}
		}
	}

	// ����饯��������

	drawChrListAll( sx, sy, sw, sh );

	// �饹�ܥ�������¦������

	lastBossXX.drawFg();

	// GUI VFX ������

	for( long y = mapY1; y < mapY2; y++ )
		for( long x = mapX1; x < mapX2; x++ )
			if( !drawGuiVfx( x, y ) )
				setUpdateFlg( x, y, true );

	// ͼ������Υ��ե����Ȥ�����

	drawNight( mapX, mapY, mapW, mapH );

	// ����������

	if( (dun->lev == 0) && chk_night() ){
		for( long y = objY1; y < objY2; y++ ){
			for( long x = objX1; x < objX2; x++ ){
				if( !flgUpdateAll && !clipWin( x, y ) )
					continue;
				if( flgUpdateAll && !getUpdateFlg( x, y ) )
					continue;

				drawStreetlamp( x, y );
			}
		}
	}

	// �������������

	for( long y = mapY1; y < mapY2; y++ ){
		for( long x = mapX1; x < mapX2; x++ ){
			if( !flgUpdateAll && !clipWin( x, y ) )
				continue;
			if( flgUpdateAll && !getUpdateFlg( x, y ) )
				continue;

			if( !drawCrsrAll( x, y ) )
				setUpdateFlg( x, y, true );
		}
	}

	// VFX������

	drawVfx( (mapX1 * 2), mapY1,
			 ((mapX2 - mapX1) * 2), (mapY2 - mapY1),
			true );

	lastBossXX.drawXxAttack( mapX, mapY, mapW, mapH );

	// �����ࡦ�����С�

	drawGameOverFade( mapX, mapY, mapW, mapH );

	//

//@@@	setFlgUpdateRequest( false );
	setFlgUpdateRequest( true );

	return true;
}

////////////////////////////////////////////////////////////////
// �ե졼�ࡦ�Хåե����饦����ɥ��ؤ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long mapW : ��
// long mapH : �⤵
////////////////////////////////////////////////////////////////

void PcgDun::flush( long mapX, long mapY, long mapW, long mapH )
{
	if( !g_flg_gui )
		return;

	if( chk_nest_flg_dun() )
		return;

#ifdef D_IPHONE
	setFlgUpdateRequestIPhone( true );
	return;
#endif // D_IPHONE

	long sizX = getTileSizeX( true );
	long sizY = getTileSizeY( true );

	long x1 = mapX * sizX;
	long y1 = mapY * sizY;
	long w = mapW * sizX;
	long h = mapH * sizY;
	long x2 = x1 + w;
	long y2 = y1 + h;

	long minX = getScrollBarX();
	long minY = getScrollBarY();
	long maxX = minX + getScrollBarW();
	long maxY = minY + getScrollBarH();

	if( x1 < minX )
		x1 = minX;
	if( y1 < minY )
		y1 = minY;
	if( x1 > maxX )
		x1 = maxX;
	if( y1 > maxY )
		y1 = maxY;

	if( x2 < minX )
		x2 = minX;
	if( y2 < minY )
		y2 = minY;
	if( x2 > maxX )
		x2 = maxX;
	if( y2 > maxY )
		y2 = maxY;

	w = x2 - x1;
	h = y2 - y1;
	if( w <= 0 )
		return;
	if( h <= 0 )
		return;

	if( !getWBuf()->getReady() )
		return;
#ifdef D_WS
	if( !MapForm->getdev()->getReady() )
		return;

	getWBuf()->copyToWindow( MapForm->getdev(),
			x1, y1, w, h,
			x1 - minX, y1 - minY );
#endif // D_WS

#ifdef D_GTK
	GdkRectangle updateRect;
	updateRect.x = x1 - minX;
	updateRect.y = y1 - minY;
	updateRect.width = w;
	updateRect.height = h;
	gtk_widget_draw( gMapDrawingArea, &updateRect );
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �ƥ����ȡ��⡼�ɤν����
////////////////////////////////////////////////////////////////

void PcgDun::initText()
{
	if( !g_flg_gui )
		return;

#ifdef D_GTK
	if( g_text_mode_point <= 0 )
		g_text_mode_point = nTextModeDefaultPoint;

	// �ǥե���ȤΥ������������

	if( pStyle == NULL )
		pStyle = gtk_style_copy( gtk_widget_get_default_style() );
	if( pStyle->fg_gc[GTK_STATE_NORMAL] == NULL ){
		pStyle->fg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}
	if( pStyle->bg_gc[GTK_STATE_NORMAL] == NULL ){
		pStyle->bg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}

	// �ե���Ȥ�����

	WSCstring sFontPoint = getTextModePoint() * 10;
	WSCstring sFontName = "";
	sFontName += "-*-*-*-r-normal-*-*-";
	sFontName += sFontPoint;
	sFontName += "-*,-*";

	gtk_style_set_font( pStyle, gdk_fontset_load( sFontName ) );

	// �ե���ȡ�������������

	GdkFont *font = gtk_style_get_font( pStyle );
	gdk_string_extents( font, "M",
			&nLeftBearing, &nRightBearing,
			&nWidth, &nAscent, &nDescent );

#if FLAG_FONT_TO_TEXT_SIZE
	nTextSizeX = nLeftBearing + nRightBearing + nIntervalWidth;
	nTextSizeX *= 2;
	nTextSizeY = nAscent + nDescent + nIntervalHeight;

	nTextSizeX = nTextSizeX * _100_PERCENT / nTileSizeRate;
	nTextSizeY = nTextSizeY * _100_PERCENT / nTileSizeRate;
#endif

	// �������롦�С���Ĵ��

	GtkAdjustment *adj;
	long sizX = getTileSizeX( true );
	long sizY = getTileSizeY( true );
	long w = gMapDrawingArea->allocation.width;
	long h = gMapDrawingArea->allocation.height;

	adj = GTK_ADJUSTMENT( gMapHScrollBarAdjustment );
	adj->lower = 0;
	adj->upper = MAP_MAX_X * sizX;
	adj->step_increment = 1 * sizX;
	adj->page_increment = AREA_MAX_X / 2 * sizX;
	adj->page_size = w;
	gtk_adjustment_changed( adj );

	adj = GTK_ADJUSTMENT( gMapVScrollBarAdjustment );
	adj->lower = 0;
	adj->upper = MAP_MAX_Y * sizY;
	adj->step_increment = 1 * sizY;
	adj->page_increment = AREA_MAX_Y / 2 * sizY;
	adj->page_size = h;
	gtk_adjustment_changed( adj );
#endif // D_GTK

#ifdef D_IPHONE
//@@@
#endif // D_IPHONE

#ifdef D_MFC
	// �ǥե���ȤΥ������������

	if( pStyle == NULL )
		pStyle = (void *)1;

	if( g_text_mode_point <= 0 )
		g_text_mode_point = nTextModeDefaultPoint;

	CXlnlView *view = theApp.m_pMainFrm->GetView();

	// �ե���ȡ�������������

#if FLAG_FONT_TO_TEXT_SIZE
	CClientDC dc( view );

	CSize siz = dc.GetTextExtent( "M", 1 );

	nTextSizeX = siz.cx;
	nTextSizeX *= 2;
	nTextSizeY = siz.cy;

	nTextSizeX = nTextSizeX * _100_PERCENT / nTileSizeRate;
	nTextSizeY = nTextSizeY * _100_PERCENT / nTileSizeRate;
#endif

	// �ե���Ȥ�����

	LONG h = g_text_mode_point;
	h = h * g_Dir3d.nTileSizeRate / _100_PERCENT;
	mTextFontDesc.lfHeight = h;
	mTextFontDesc.lfWidth = 0;
	mTextFontDesc.lfEscapement = 0;
	mTextFontDesc.lfOrientation = 0;
	mTextFontDesc.lfWeight = FW_NORMAL;
	mTextFontDesc.lfItalic = FALSE;
	mTextFontDesc.lfUnderline = FALSE;
	mTextFontDesc.lfStrikeOut = FALSE;
	mTextFontDesc.lfCharSet = SHIFTJIS_CHARSET;
	mTextFontDesc.lfOutPrecision
			= OUT_DEFAULT_PRECIS;
	mTextFontDesc.lfClipPrecision
			= CLIP_DEFAULT_PRECIS;
	mTextFontDesc.lfQuality = DEFAULT_QUALITY;
	mTextFontDesc.lfPitchAndFamily
			= (FIXED_PITCH | FF_MODERN);
	strcpy( mTextFontDesc.lfFaceName, "Pica" );

	pTextFont = new CFont;
	pTextFont->CreateFontIndirect(
			&mTextFontDesc );

	// �������롦�С���Ĵ��

	view->ResetScroll();
#endif // MFC
}

////////////////////////////////////////////////////////////////
// �ƥ����ȡ��⡼�ɤΥޥåפ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long mapW : ��
// long mapH : �⤵
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawText( long mapX, long mapY, long mapW, long mapH )
{
	if( !g_flg_gui )
		return true;

	if( !g_flg_text_mode )
		return true;

#ifdef D_GTK
	if( pStyle == NULL )
		initText();
	dun_t *dun = get_dun();
	if( dun == NULL )
		return false;
	if( chk_nest_flg_dun() )
		return true;
	if( gMapDrawingArea == NULL )
		return false;

	GdkDrawable *d = getWBuf()->getPixMap();
	GdkFont *font = gtk_style_get_font( pStyle );
	GdkGC *fgGc = pStyle->fg_gc[GTK_STATE_NORMAL];
	GdkGC *bgGc = pStyle->bg_gc[GTK_STATE_NORMAL];

	char s[4 + 1];
	s[0] = ' ';
	s[1] = '\0';

	long bx = mapX;
	long by = mapY;
	long ex = mapX + mapW - 1;
	long ey = mapY + mapH - 1;
	if( bx < 0 )
		bx = 0;
	if( by < 0 )
		by = 0;
	if( ex > MAP_MAX_X - 1 )
		ex = MAP_MAX_X - 1;
	if( ey > MAP_MAX_Y - 1 )
		ey = MAP_MAX_Y - 1;

	setUpdateFlgRange( bx, by, ex - bx + 1, ey - by + 1, true );

	long sizeX = getTileSizeX( true );
	long sizeY = getTileSizeY( true );
	long winMinX = getScrollBarX() / sizeX;
	long winMinY = getScrollBarY() / sizeY;
	long winMaxX = (getScrollBarW() - 1) / sizeX + winMinX;
	long winMaxY = (getScrollBarH() - 1) / sizeY + winMinY;
	if( bx < winMinX )
		bx = winMinX;
	if( by < winMinY )
		by = winMinY;
	if( ex > winMaxX )
		ex = winMaxX;
	if( ey > winMaxY )
		ey = winMaxY;

	set_map_total( bx, by, ex - bx + 1, ey - by + 1 );

	// ����°��������

	curs_attr_t preAttr;
	preAttr = dun->map.attr[bx][by];
	curs_attrset_dir( &preAttr );
	SetPenAttr( fgGc, bgGc, &preAttr );

	for( long my = by; my <= ey; my++ ){
		for( long mx = bx; mx <= ex; mx++ ){
			// ��ɸ�׻�

			long mjrX = mx * sizeX;
			long mnrX = mjrX + (sizeX / 2);
			long y = my * sizeY;

			// ����°��������

			curs_attr_t attr = dun->map.attr[my][mx];

			if( dun->map.vfx[my][mx * 2 + 1] != MAP_VFX_NULL )
				attr = dun->map.attr_vfx[my][mx * 2 + 1];

			if( dun->map.vfx[my][mx * 2 + 0] != MAP_VFX_NULL )
				attr = dun->map.attr_vfx[my][mx * 2 + 0];

			if( !cmp_attr( &attr, &preAttr ) ){
				curs_attrset_dir( &attr );
				SetPenAttr( fgGc, bgGc, &attr );
				preAttr = attr;
			}

			// �طʤ��ɤ�Ĥ֤�

			gdk_draw_rectangle( d, bgGc, TRUE,
					mjrX, y,
					sizeX, sizeY );

			// ����������饤�������

			if( attr.attr & A_UNDERLINE ){
				long uy = y + sizeY - 1;
				long uw = sizeX;
				gdk_draw_line( d, fgGc,
						mjrX, uy,
						(mjrX + uw), uy );
			}

			// ��ɸ����

			mjrX += nLeftBearing;
			mnrX += nLeftBearing;
			y += nAscent + 1;

			// �᥸�㡼ʸ��������

			char c;

			c = dun->map.vfx[my][mx * 2 + 0];
			if( c == MAP_VFX_NULL )
				s[0] = dun->map.total.mjr[my][mx];
			else
				s[0] = c;
			gdk_draw_string( d, font, fgGc, mjrX, y, s );

			// �ޥ��ʡ�ʸ��������

			c = dun->map.vfx[my][mx * 2 + 1];
			if( c == MAP_VFX_NULL )
				s[0] = dun->map.total.mnr[my][mx];
			else
				s[0] = c;
			gdk_draw_string( d, font, fgGc, mnrX, y, s );

			setUpdateFlg( mx, my, false );
		}
	}

	curs_attrset_dflt();
#endif // D_GTK

#ifdef D_IPHONE
//@@@
#endif // D_IPHONE

#ifdef D_MFC
	if( !gFlagInitMfcDone )
		return true;
	if( pStyle == NULL )
		initText();
	dun_t *dun = get_dun();
	if( dun == NULL )
		return false;
	if( chk_nest_flg_dun() )
		return true;
	if( pDc == NULL ){
		CXlnlView *view = theApp.m_pMainFrm->GetView();
		pDc = new CClientDC( view );
	}

	long bx = mapX;
	long by = mapY;
	long ex = mapX + mapW - 1;
	long ey = mapY + mapH - 1;
	if( bx < 0 )
		bx = 0;
	if( by < 0 )
		by = 0;
	if( ex > MAP_MAX_X - 1 )
		ex = MAP_MAX_X - 1;
	if( ey > MAP_MAX_Y - 1 )
		ey = MAP_MAX_Y - 1;

	setUpdateFlgRange( bx, by, ex - bx + 1, ey - by + 1, true );

	long sizeX = getTileSizeX( true );
	long sizeY = getTileSizeY( true );
	long winMinX = getScrollBarX() / sizeX;
	long winMinY = getScrollBarY() / sizeY;
	long winMaxX = (getScrollBarW() - 1) / sizeX + winMinX;
	long winMaxY = (getScrollBarH() - 1) / sizeY + winMinY;
	if( bx < winMinX )
		bx = winMinX;
	if( by < winMinY )
		by = winMinY;
	if( ex > winMaxX )
		ex = winMaxX;
	if( ey > winMaxY )
		ey = winMaxY;

	set_map_total( bx, by, ex - bx + 1, ey - by + 1 );

	long offsetX = winMinX;
	long offsetY = winMinY;

	char s[4 + 1];
	s[0] = ' ';
	s[1] = '\0';

	g_Dir3d.BeginDraw();

	for( long my = by; my <= ey; my++ ){
		for( long mx = bx; mx <= ex; mx++ ){
			// ��ɸ�׻�

			long mjrX = mx - offsetX;
			mjrX *= getTileSizeX( true );

			long mnrX = mjrX + (getTileSizeX( true ) / 2);

			long y = my - offsetY;
			y *= getTileSizeY( true );

			mjrX *= g_Dir3d.nTileSizeRate;
			mjrX /= _100_PERCENT;
			mnrX *= g_Dir3d.nTileSizeRate;
			mnrX /= _100_PERCENT;
			y *= g_Dir3d.nTileSizeRate;
			y /= _100_PERCENT;

			long tw = getTileSizeX( true );
			tw *= g_Dir3d.nTileSizeRate;
			tw /= _100_PERCENT;

			long th = getTileSizeY( true );
			th *= g_Dir3d.nTileSizeRate;
			th /= _100_PERCENT;

			// ����°��������

			curs_attr_t attr = dun->map.attr[my][mx];

			if( dun->map.vfx[my][mx * 2 + 1] != MAP_VFX_NULL )
				attr = dun->map.attr_vfx[my][mx * 2 + 1];

			if( dun->map.vfx[my][mx * 2 + 0] != MAP_VFX_NULL )
				attr = dun->map.attr_vfx[my][mx * 2 + 0];

			curs_attrset_dir( &attr );
			COLORREF colorBg;
			CvColorRGB( &colorBg, attr.bg );

			// �طʤ��ɤ�Ĥ֤�

			CRect rect( mjrX, y, mjrX + tw, y + th );
			pDc->FillSolidRect( rect, colorBg );

			// ����������饤�������

			if( attr.attr & A_UNDERLINE ){
				long uy = y + th - 1;
				CPen *pen = new CPen();
				SetPenAttrFg( pDc, pen, NULL, &attr );

				pDc->MoveTo( mjrX, uy );
				pDc->LineTo( mjrX + tw, uy );

				delete pen;
			}

			// ��ɸ����

			// ���賫��

			CPen *pen = new CPen();
			SetPenAttrFg( pDc, pen, NULL, &attr );
			CFont *pPrevFont = pDc->SelectObject( pTextFont );

			// �᥸�㡼ʸ��������

			char c;

			c = dun->map.vfx[my][mx * 2 + 0];
			if( c == MAP_VFX_NULL )
				s[0] = dun->map.total.mjr[my][mx];
			else
				s[0] = c;
			pDc->TextOut( mjrX, y, s );

			// �ޥ��ʡ�ʸ��������

			c = dun->map.vfx[my][mx * 2 + 1];
			if( c == MAP_VFX_NULL )
				s[0] = dun->map.total.mnr[my][mx];
			else
				s[0] = c;
			pDc->TextOut( mnrX, y, s );

			// ���轪λ

			pDc->SelectObject( pPrevFont );
			delete pen;

			setUpdateFlg( mx, my, false );
		}
	}

	g_Dir3d.EndDraw();

	curs_attrset_dflt();
#endif // D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// �ƥ����ȡ��⡼�ɤλ����ޥåפ�ʸ���������
// long scrn_x : X ��ɸ
// long scrn_y : Y ��ɸ
// const char *s : �ե����ޥå�ʸ����
// ... : �ե����ޥåȤΰ���
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawString( long scrn_x, long scrn_y, const char *s, ... )
{
	if( !g_flg_gui )
		return true;

	va_list	argptr;
	static char	buf[SCREEN_WIDTH * 2 + 1];

	va_start( argptr, s );
	vsprintf( buf, s, argptr );
	va_end( argptr );

	if( !g_flg_text_mode )
		return true;

	pos_t *pos = get_map_draw_pos();
	long x = scrn_x + (pos->x * 2);
	long y = scrn_y + pos->y;
	long len = 0;

#ifdef D_GTK
	if( pStyle == NULL )
		initText();
	if( chk_nest_flg_dun() )
		return true;
	if( gMapDrawingArea == NULL )
		return false;

	GdkDrawable *d = getWBuf()->getPixMap();
	GdkFont *font = gtk_style_get_font( pStyle );
	GdkGC *fgGc = pStyle->fg_gc[GTK_STATE_NORMAL];
	GdkGC *bgGc = pStyle->bg_gc[GTK_STATE_NORMAL];

	for( ; buf[len] != '\0'; len++, x++ ){
		long mx = x / 2;
		long my = y;

		if( !clip_pos( mx, my ) )
			continue;

		setUpdateFlg( mx, my, true );

		if( !clipWin( mx, my ) )
			continue;

		// ��ɸ�׻�

		long xx = x * getTileSizeX( true ) / 2;
		long yy = y * getTileSizeY( true );
		long ww = getTileSizeX( true ) / 2;
		long hh = getTileSizeY( true );

		// ����°��������

		curs_attr_t attr = get_current_attr();
		SetPenAttr( fgGc, bgGc, &attr );

		// �طʤ��ɤ�Ĥ֤�

		gdk_draw_rectangle( d, bgGc, TRUE, xx, yy, ww, hh );

		// ����������饤�������

		if( attr.attr & A_UNDERLINE ){
			long uy = y + getTileSizeY() - 1;
			gdk_draw_line( d, fgGc, xx, uy, (xx + ww), uy );
		}

		// ��ɸ����

		xx += nLeftBearing;
		yy += nAscent + 1;

		// ʸ��������

		char str[4 + 1];
		str[0] = buf[len];
		str[1] = '\0';
		gdk_draw_string( d, font, fgGc, xx, yy, str );

		setUpdateFlg( mx, my, false );
	}
#endif // D_GTK

#ifdef D_IPHONE
//@@@
#endif // D_IPHONE

#ifdef D_MFC
	if( !gFlagInitMfcDone )
		return true;
	if( pStyle == NULL )
		initText();
	if( chk_nest_flg_dun() )
		return true;
	if( pDc == NULL ){
		CXlnlView *view = theApp.m_pMainFrm->GetView();
		pDc = new CClientDC( view );
	}

	long scrollX = getScrollBarX();
	long scrollY = getScrollBarY();

	g_Dir3d.BeginDraw();

	for( ; buf[len] != '\0'; len++, x++ ){
		long mx = x / 2;
		long my = y;

		if( !clip_pos( mx, my ) )
			continue;

		setUpdateFlg( mx, my, true );

		if( !clipWin( mx, my ) )
			continue;

		// ��ɸ�׻�

		long xx = x * getTileSizeX( true );
		long yy = y * getTileSizeY( true );
		xx /= 2;
		xx -= scrollX;
		yy -= scrollY;

		xx *= g_Dir3d.nTileSizeRate;
		yy *= g_Dir3d.nTileSizeRate;
		xx /= _100_PERCENT;
		yy /= _100_PERCENT;

		long tw = getTileSizeX( true );
		long th = getTileSizeY( true );
		tw *= g_Dir3d.nTileSizeRate;
		th *= g_Dir3d.nTileSizeRate;
		tw /= _100_PERCENT;
		th /= _100_PERCENT;
		tw /= 2;

		// ����°��������

		curs_attr_t attr = get_current_attr();
		COLORREF colorBg;
		CvColorRGB( &colorBg, attr.bg );

		// �طʤ��ɤ�Ĥ֤�

		CRect rect( xx, yy, (xx + tw), (yy + th) );
		pDc->FillSolidRect( rect, colorBg );

		// ����������饤�������

		if( attr.attr & A_UNDERLINE ){
			long uy = y + th - 1;
			CPen *pen = new CPen();
			SetPenAttrFg( pDc, pen, NULL, &attr );

			pDc->MoveTo( xx, uy );
			pDc->LineTo( (xx + tw), uy );

			delete pen;
		}

		// ��ɸ����

		// ���賫��

		CPen *pen = new CPen();
		SetPenAttrFg( pDc, pen, NULL, &attr );
		CFont *pPrevFont = pDc->SelectObject( pTextFont );

		// ʸ��������

		char str[4 + 1];
		str[0] = buf[len];
		str[1] = '\0';
		pDc->TextOut( xx, yy, str );

		// ���轪λ

		pDc->SelectObject( pPrevFont );
		delete pen;

		setUpdateFlg( mx, my, false );
	}

	g_Dir3d.EndDraw();
#endif // D_MFC

	if( len > 0 ){
		long mx = scrn_x + (pos->x * 2);
		long my = scrn_y + pos->y;
		mx /= 2;
		long mw = (len + 2 - 1) / 2;
		long mh = 1;

		flush( mx, my, mw, mh );
	}

	return true;
}

////////////////////////////////////////////////////////////////
// VFX �ν����
////////////////////////////////////////////////////////////////

void PcgDun::initVfx()
{
	if( !g_flg_gui )
		return;

#ifdef D_GTK
	if( g_text_mode_point <= 0 )
		g_text_mode_point = nTextModeDefaultPoint;

	// �ǥե���ȤΥ������������

	if( pStyleVfx == NULL ){
		pStyleVfx = gtk_style_copy(
				gtk_widget_get_default_style() );
	}
	if( pStyleVfx->fg_gc[GTK_STATE_NORMAL] == NULL ){
		pStyleVfx->fg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}
	if( pStyleVfx->bg_gc[GTK_STATE_NORMAL] == NULL ){
		pStyleVfx->bg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}

	// �ե���Ȥ�����

	WSCstring sFontPoint = getTextModePoint() * 10;
	WSCstring sFontName = "";
	sFontName += "-*-*-*-r-normal-*-*-";
	sFontName += sFontPoint;
	sFontName += "-*,-*";

	gtk_style_set_font( pStyleVfx, gdk_fontset_load( sFontName ) );

	// �ե���ȡ�������������

	GdkFont *font = gtk_style_get_font( pStyleVfx );
	gdk_string_extents( font, "M",
			&nLeftBearingVfx, &nRightBearingVfx,
			&nWidthVfx, &nAscentVfx, &nDescentVfx );
#endif // D_GTK

#ifdef D_IPHONE
//@@@
#endif // D_IPHONE

#ifdef D_MFC
	// �ǥե���ȤΥ������������

	if( pStyleVfx == NULL )
		pStyleVfx = (void *)1;

	if( g_text_mode_point <= 0 )
		g_text_mode_point = nTextModeDefaultPoint;

	CXlnlView *view = theApp.m_pMainFrm->GetView();

	// �ե���ȡ�������������

#if FLAG_FONT_TO_TEXT_SIZE
	CClientDC dc( view );

	CSize siz = dc.GetTextExtent( "M", 1 );

	nTextSizeX = siz.cx;
	nTextSizeX *= 2;
	nTextSizeY = siz.cy;

	nTextSizeX = nTextSizeX * _100_PERCENT / nTileSizeRate;
	nTextSizeY = nTextSizeY * _100_PERCENT / nTileSizeRate;
#endif

	// �ե���Ȥ�����

	LONG h = g_text_mode_point;
	h = h * g_Dir3d.nTileSizeRate / _100_PERCENT;
	mTextFontDescVfx.lfHeight = h;
	mTextFontDescVfx.lfWidth = 0;
	mTextFontDescVfx.lfEscapement = 0;
	mTextFontDescVfx.lfOrientation = 0;
	mTextFontDescVfx.lfWeight = FW_NORMAL;
	mTextFontDescVfx.lfItalic = FALSE;
	mTextFontDescVfx.lfUnderline = FALSE;
	mTextFontDescVfx.lfStrikeOut = FALSE;
	mTextFontDescVfx.lfCharSet = SHIFTJIS_CHARSET;
	mTextFontDescVfx.lfOutPrecision
			= OUT_DEFAULT_PRECIS;
	mTextFontDescVfx.lfClipPrecision
			= CLIP_DEFAULT_PRECIS;
	mTextFontDescVfx.lfQuality = DEFAULT_QUALITY;
	mTextFontDescVfx.lfPitchAndFamily
			= (FIXED_PITCH | FF_MODERN);
	strcpy( mTextFontDescVfx.lfFaceName, "Pica" );

	pTextFontVfx = new CFont;
	pTextFontVfx->CreateFontIndirect(
			&mTextFontDescVfx );

	mD3Vfx.Create( &mTextFontDescVfx );

	// �������롦�С���Ĵ��

	view->ResetScroll();
#endif // MFC
}

////////////////////////////////////////////////////////////////
// �ޥåפ� VFX ������
// long scrn_x : X ��ɸ
// long scrn_y : Y ��ɸ
// long scrn_w : ��
// long scrn_h : �⤵
// bool flgForce : ��������
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawVfx(
	long scrn_x, long scrn_y,
	long scrn_w, long scrn_h,
	bool flgForce )
{
	if( !g_flg_gui )
		return true;

	dun_t *dun = get_dun();

	long bgnX = scrn_x;
	long bgnY = scrn_y;
	long endX = bgnX + scrn_w;
	long endY = bgnY + scrn_h;

#ifdef D_GTK
	if( pStyleVfx == NULL )
		initVfx();
	if( chk_nest_flg_dun() )
		return true;
	if( gMapDrawingArea == NULL )
		return false;

	GdkDrawable *d = getWBuf()->getPixMap();
	GdkFont *font = gtk_style_get_font( pStyleVfx );
	GdkGC *fgGc = pStyleVfx->fg_gc[GTK_STATE_NORMAL];
	GdkGC *bgGc = pStyleVfx->bg_gc[GTK_STATE_NORMAL];

	for( long y = bgnY; y < endY; y++ ){
		for( long x = bgnX; x < endX; x++ ){
			long mx = x / 2;
			long my = y;

			if( !clip_pos( mx, my ) )
				continue;

			long c = dun->map.vfx[y][x];
			if( c == MAP_VFX_NULL )
				continue;

			if( !clipWin( mx, my ) )
				continue;

			// ��ɸ�׻�

			long xx = x * getTileSizeX( true ) / 2;
			long yy = y * getTileSizeY( true );
			long ww = getTileSizeX( true ) / 2;

			// ����°��������

			curs_attr_t attr = dun->map.attr_vfx[y][x];
			SetPenAttr( fgGc, bgGc, &attr );

			// ����������饤�������

			if( attr.attr & A_UNDERLINE ){
				long uy = y + getTileSizeY() - 1;
				gdk_draw_line( d, fgGc,
						xx, uy,
						(xx + ww), uy );
			}

			// ��ɸ����

			xx += nLeftBearingVfx;
			yy += nAscentVfx + 1;

			// ʸ��������

			char str[4 + 1];
			str[0] = c;
			str[1] = '\0';
			gdk_draw_string( d, font, fgGc, xx, yy, str );
		}
	}
#endif // D_GTK

#ifdef D_IPHONE
//@@@
#endif // D_IPHONE

#ifdef D_MFC
	if( !gFlagInitMfcDone )
		return true;
	if( pStyleVfx == NULL )
		initVfx();
	if( chk_nest_flg_dun() )
		return true;
	if( pDcVfx == NULL ){
		CXlnlView *view = theApp.m_pMainFrm->GetView();
		pDcVfx = new CClientDC( view );
	}

	for( long y = bgnY; y < endY; y++ ){
		for( long x = bgnX; x < endX; x++ ){
			long mx = x / 2;
			long my = y;

			if( !clip_pos( mx, my ) )
				continue;

			char c = dun->map.vfx[y][x];
			if( c == MAP_VFX_NULL )
				continue;
			if( !clipWin( mx, my ) )
				continue;

			// ��ɸ�׻�

			long xx = x * getTileSizeX( true ) / 2;
			long yy = y * getTileSizeY( true );
			long ww = getTileSizeX( true ) / 2;
			long scrollX = getScrollBarX();
			long scrollY = getScrollBarY();
			xx -= scrollX;
			yy -= scrollY;
			xx = xx * g_Dir3d.nTileSizeRate / _100_PERCENT;
			yy = yy * g_Dir3d.nTileSizeRate / _100_PERCENT;

			// ����°��������

			curs_attr_t attr = dun->map.attr_vfx[y][x];

			// ����������饤�������

			if( attr.attr & A_UNDERLINE ){
				long uy = y + getTileSizeY() - 1;
				CPen *pen = new CPen();
				SetPenAttrFg( pDcVfx, pen, NULL, &attr );

				pDcVfx->MoveTo( xx, uy );
				pDcVfx->LineTo( (xx + ww), uy );

				delete pen;
			}

			// ��ɸ����

# if FLAG_USE_TEXT_OUT
			// ���賫��

			CPen *pen = new CPen();
			SetPenAttrFg( pDcVfx, pen, NULL, &attr );
			CFont *pPrevFont = pDcVfx->SelectObject( pTextFont );

			// ʸ��������

			char str[4 + 1];
			str[0] = (char)c;
			str[1] = '\0';

			pDcVfx->TextOut( xx, yy, str );

			// ���轪λ

			pDcVfx->SelectObject( pPrevFont );
			delete pen;
# else
			// ���賫��

			mD3Vfx.Begin();

			D3DCOLOR d3color;
			CvColorRGBD3( &d3color, attr.fg );

			// ʸ��������

			char str[4 + 1];
			str[0] = (char)c;
			str[1] = '\0';
			mD3Vfx.Draw( xx, yy, d3color, str );

			// ���轪λ

			mD3Vfx.End();
# endif
		}
	}
#endif // D_MFC

	return true;
}

////////////////////////////////////////////////////////////////
// XX �ι��������ǡ���������
// xx_act_kind_t kind : ����μ���
// void *p : ����Υǡ���
////////////////////////////////////////////////////////////////

void PcgDun::setXxAttack( xx_act_kind_t kind, void *p )
{
	if( !g_flg_gui )
		return;

	lastBossXX.setXxAttack( kind, p );
}

////////////////////////////////////////////////////////////////
// �ե���ȡ����쥯����󡦥��������μ¹�
// GdkFont **font : ���Ф줿�ե���Ȥ��֤�
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

#ifdef D_GTK
bool PcgDun::user_select_font( GdkFont **font )
{
	if( !g_flg_gui )
		return true;

	if( font == NULL )
		return false;

	GtkWidget *dlg = gtk_font_selection_dialog_new( "Select font" );
	GtkFontSelectionDialog *fontSelDlg
			= GTK_FONT_SELECTION_DIALOG( dlg );

	gtk_signal_connect(
			GTK_OBJECT( fontSelDlg ),
			"destroy",
			GTK_SIGNAL_FUNC( handle_sel_font_destroy ),
			GTK_OBJECT( fontSelDlg ) );
	gtk_signal_connect_object(
			GTK_OBJECT( fontSelDlg->cancel_button ),
			"clicked",
			GTK_SIGNAL_FUNC( gtk_widget_destroy ),
			GTK_OBJECT( fontSelDlg ) );
	gtk_signal_connect(
			GTK_OBJECT( fontSelDlg->ok_button ),
			"clicked",
			GTK_SIGNAL_FUNC( handle_sel_font_ok ),
			GTK_OBJECT( fontSelDlg ) );

	gtk_grab_add( GTK_WIDGET( dlg ) );
	gtk_widget_show( GTK_WIDGET( dlg ) );

	gtk_main();

	if( *font != NULL )
		gdk_font_unref( *font );
	*font = gSelFont;

	return true;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// GTK+ �ν�λ�����Υϥ�ɥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
static void handle_sel_font_destroy(
	GtkWidget *widget, gpointer user_data
)
{
	gtk_main_quit();
	gtk_grab_remove( GTK_WIDGET( user_data ) );
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// �ե���ȡ����쥯����󡦥���������
// OK �ܥ���Υ���å������٥�Ƚ���
// GtkWidget *widget : �ܥ���
// gpointer data : ��Ͽ�����Ϥ��줿�ǡ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
static void handle_sel_font_ok(
	GtkWidget *widget, gpointer *data
)
{
	gSelFont = gtk_font_selection_dialog_get_font(
			GTK_FONT_SELECTION_DIALOG( data ) );

	gdk_font_ref( gSelFont );

	gtk_widget_destroy( GTK_WIDGET( data ) );
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ���̹����׵�ե饰������
// bool flg : �����׵᤹�뤫��
////////////////////////////////////////////////////////////////

void PcgDun::setFlgUpdateRequest( bool flg )
{
	bFlgUpdateRequest = flg;
}

////////////////////////////////////////////////////////////////
// ���̹����׵�ե饰�μ���
// return : �����׵᤹�뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::getFlgUpdateRequest()
{
	return bFlgUpdateRequest;
}

////////////////////////////////////////////////////////////////
// ���̹����׵�ե饰������ (iPhone)
// bool flg : �����׵᤹�뤫��
////////////////////////////////////////////////////////////////

void PcgDun::setFlgUpdateRequestIPhone( bool flg )
{
	bFlgUpdateRequestIPhone = flg;
}

////////////////////////////////////////////////////////////////
// ���̹����׵�ե饰�μ��� (iPhone)
// return : �����׵᤹�뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::getFlgUpdateRequestIPhone()
{
	return bFlgUpdateRequestIPhone;
}

////////////////////////////////////////////////////////////////
// ������ե饰�Υꥻ�å�
////////////////////////////////////////////////////////////////

void PcgDun::resetUpdateFlg()
{
	if( !g_flg_gui )
		return;

	setUpdateFlgRange( 0, 0, MAP_MAX_X, MAP_MAX_Y, true );
}

////////////////////////////////////////////////////////////////
// �����ϰϤκ�����ե饰������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long mapW : ��
// long mapH : �⤵
// bool flg : �����褹��ɬ�פ����뤫��
////////////////////////////////////////////////////////////////

void PcgDun::setUpdateFlgRange(
	long mapX, long mapY,
	long mapW, long mapH,
	bool flg
)
{
	if( !g_flg_gui )
		return;

	for( long dy = 0; dy < mapH; dy++ )
		for( long dx = 0; dx < mapW; dx++ )
			setUpdateFlg( mapX + dx, mapY + dy, flg );
}

////////////////////////////////////////////////////////////////
// ������ե饰������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// bool flg : �����褹��ɬ�פ����뤫��
////////////////////////////////////////////////////////////////

void PcgDun::setUpdateFlg( long mapX, long mapY, bool flg )
{
	if( !g_flg_gui )
		return;

	if( !clip_pos( mapX, mapY ) )
		return;

	bFlgUpdate[mapY][mapX] = flg;
}

////////////////////////////////////////////////////////////////
// ������ե饰�μ���
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : �����褹��ɬ�פ����뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::getUpdateFlg( long mapX, long mapY )
{
	if( !g_flg_gui )
		return false;

	if( !clip_pos( mapX, mapY ) )
		return false;

	return bFlgUpdate[mapY][mapX];
}

////////////////////////////////////////////////////////////////
// �����ȥ���̤�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawTitle()
{
	if( !g_flg_gui )
		return true;

	if( pDemoTitle == NULL )
		return false;

	return pDemoTitle->draw();
}

////////////////////////////////////////////////////////////////
// �饹�ܥ����̤�����
// return : �ǥ�������椫��
////////////////////////////////////////////////////////////////

bool PcgDun::drawLastBoss()
{
	if( !g_flg_gui )
		return false;

	if( pDemoLastBoss == NULL )
		return false;

	if( !chk_draw_last_boss() ){
		if( !pDemoLastBoss->checkSkipFrame() ){
			drawTurnSub();
			pDemoLastBoss->draw();
			drawTurnFlush();
		}
		return true;
	} else {
		pDemoLastBoss->draw();
		return false;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// �����ࡦ�����С����̤�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawGameOver()
{
	if( !g_flg_gui )
		return true;

	if( pDemoGameOver == NULL )
		return false;

	return pDemoGameOver->draw();
}

////////////////////////////////////////////////////////////////
// ����ǥ��󥰲��̤�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawEnding()
{
	if( !g_flg_gui )
		return true;

	if( pDemoEnding == NULL )
		return false;

	return pDemoEnding->draw();
}

////////////////////////////////////////////////////////////////
// ������饯��������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// bool flgFlush : �ե졼�ࡦ�Хåե����饦����ɥ���
//     ���褹�뤫��
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawTile( long mapX, long mapY, bool flgFlush )
{
	if( !g_flg_gui )
		return true;

	if( g_flg_text_mode )
		return drawText( mapX, mapY, 1, 1 );

	setUpdateFlg( mapX, mapY, true );

	if( chk_nest_flg_dun() )
		return true;
	if( !clipWin( mapX, mapY ) )
		return true;

	dun_t *dun = get_dun();

	bool result = true;
	if( !drawWater( mapX, mapY ) )
		result = false;
	if( !drawObj( mapX, mapY ) )
		result = false;
	if( !drawTrap( mapX, mapY ) )
		result = false;
	if( !drawStairsUp( mapX, mapY ) )
		result = false;
	if( !drawStairsDown( mapX, mapY ) )
		result = false;
	if( !drawSquareParty( mapX, mapY ) )
		result = false;
	if( !drawSquareMbrAll( mapX, mapY ) )
		result = false;
	if( !drawItemAll( mapX, mapY ) )
		result = false;
	if( !drawStatue( mapX, mapY ) )
		result = false;
	if( get_scene() == SCENE_N_LAST_BOSS )
		if( !drawBootUnit( mapX, mapY ) )
			result = false;
	if( !drawChrList( mapX, mapY, true ) )
		result = false;
	if( !drawGuiVfx( mapX, mapY ) )
		result = false;
	drawNight( mapX, mapY, 1, 1 );
	if( (dun->lev == 0) && chk_night() )
		if( !drawStreetlamp( mapX, mapY ) )
			result = false;
	if( !drawCrsrAll( mapX, mapY ) )
		result = false;
	if( !drawVfx( (mapX * 2), mapY, 2, 1, true ) )
		result = false;
	drawGameOverFade( mapX, mapY, 1, 1 );

	if( flgFlush )
		flush( mapX, mapY, 1, 1 );

	setUpdateFlg( mapX, mapY, false );

	return result;
}

////////////////////////////////////////////////////////////////
// ���֥������Ȥ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawObj( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	bool flgSuccess = false;

	if( !clip_pos( mapX, mapY ) )
		return true;

	if( !getWBuf()->getReady() )
		return false;
#ifdef D_WS
	if( !MapForm->getdev()->getReady() )
		return false;
#endif // D_WS

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( TRUE, mapX, mapY, &mjr, &mnr, TRUE );

	switch( mjr ){
	default:
	case FACE_MJR_NULL:
		flgSuccess = drawNull( mapX, mapY );
		break;
	case FACE_MJR_FLOOR:
		if( mnr == FACE_MNR_HOLE )
			flgSuccess = drawHole( mapX, mapY );
		else
			flgSuccess = drawFloor( mapX, mapY );
		break;
	case FACE_MJR_WALL:
		switch( mnr ){
		case FACE_MNR_WALL:
			flgSuccess = drawWall( mapX, mapY );
			break;
		case FACE_MNR_STATUE:
			flgSuccess = drawFloor( mapX, mapY );
			break;
		case FACE_MNR_BOOT_UNIT:
			flgSuccess = drawFloor( mapX, mapY );
			break;
		case FACE_MNR_STREETLAMP:
			flgSuccess = drawWall( mapX, mapY );
			flgSuccess = drawStreetlamp( mapX, mapY );
			break;
		default:
			flgSuccess = drawWall( mapX, mapY );
			if( ('A' <= mnr) && (mnr <= 'Z') )
				flgSuccess = drawSignboard( mapX, mapY );
			break;
		}
		break;
	case FACE_MJR_WATER:
		flgSuccess = true;
		break;
	case FACE_MJR_DOOR_CLOSE:
		flgSuccess = drawWall( mapX, mapY );
		if( mnr == FACE_MNR_WINDOW )
			flgSuccess = drawWindowClose( mapX, mapY );
		else
			flgSuccess = drawDoorClose( mapX, mapY );
		break;
	case FACE_MJR_DOOR_OPEN:
		flgSuccess = drawWall( mapX, mapY );
		if( mnr == FACE_MNR_WINDOW )
			flgSuccess = drawWindowOpen( mapX, mapY );
		else
			flgSuccess = drawDoorOpen( mapX, mapY );
		break;
	case FACE_MJR_STAIRS_UP:
	case FACE_MJR_STAIRS_DOWN:
	case FACE_MJR_TRAP:
		flgSuccess = drawFloor( mapX, mapY );
		break;
	case FACE_MJR_WEAPON:
	case FACE_MJR_ARMOR:
	case FACE_MJR_POTION:
	case FACE_MJR_SCROLL:
	case FACE_MJR_STICK:
	case FACE_MJR_ACCESSORY:
	case FACE_MJR_FOOD:
	case FACE_MJR_CHEST:
	case FACE_MJR_COIN:
	case FACE_MJR_GEM:
	case FACE_MJR_MISC:
		flgSuccess = drawFloor( mapX, mapY );
		break;
	}

	return flgSuccess;
}

////////////////////////////////////////////////////////////////
// ������Υ����ƥ������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawItemAll( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	bool flgSuccess = false;

	if( !clip_pos( mapX, mapY ) )
		return true;

	if( !getWBuf()->getReady() )
		return false;
#ifdef D_WS
	if( !MapForm->getdev()->getReady() )
		return false;
#endif // D_WS

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( TRUE, mapX, mapY, &mjr, &mnr, TRUE );

	switch( mjr ){
	default:
	case FACE_MJR_NULL:
		flgSuccess = true;
		break;
	case FACE_MJR_WEAPON:
	case FACE_MJR_ARMOR:
	case FACE_MJR_POTION:
	case FACE_MJR_SCROLL:
	case FACE_MJR_STICK:
	case FACE_MJR_ACCESSORY:
	case FACE_MJR_FOOD:
	case FACE_MJR_CHEST:
	case FACE_MJR_COIN:
	case FACE_MJR_GEM:
	case FACE_MJR_MISC:
		flgSuccess = drawItem( mapX, mapY, mjr, mnr );
		break;
	}

	return flgSuccess;
}

////////////////////////////////////////////////////////////////
// ���������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawNull( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	return drawObjFix( mapX, mapY, &pcgNullTown, &pcgNullDun );
}

////////////////////////////////////////////////////////////////
// ��������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawFloor( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( get_scene() == SCENE_N_LAST_BOSS ){
		return drawObjFix( mapX, mapY,
				&pcgFloorLast, &pcgFloorLast );
	} else {
		return drawObjFix( mapX, mapY,
				&pcgFloorTown, &pcgFloorDun );
	}
}

////////////////////////////////////////////////////////////////
// ���������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawHole( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	return drawObjFix( mapX, mapY, &pcgHole, &pcgHole );
}

////////////////////////////////////////////////////////////////
// ���֥������Ȥ�����ʥѥ���������к�ɸ�������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// Pcg *lsTown : ���λ��Υѥ����󡦥ꥹ��
// Pcg *lsDun : �µܤλ��Υѥ����󡦥ꥹ��
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawObjFix( long mapX, long mapY, Pcg *lsTown, Pcg *lsDun )
{
	if( !g_flg_gui )
		return true;

	Pcg *p = srchPcgLsMap( mapX, mapY, lsTown, lsDun );
	if( p == NULL )
		return false;

	return p->drawFix( getWBuf(),
			mapX * getTileSizeX(),
			mapY * getTileSizeY(),
			1 * getTileSizeX(),
			1 * getTileSizeY() );
}

////////////////////////////////////////////////////////////////
// �ѥ�����Υꥹ�Ȥ���Хꥨ�������ˤ��ä��ѥ�����򸡺�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// Pcg *lsTown : ���λ��Υѥ����󡦥ꥹ��
// Pcg *lsDun : �µܤλ��Υѥ����󡦥ꥹ��
// return : �ѥ�����
////////////////////////////////////////////////////////////////

Pcg *PcgDun::srchPcgLsMap(
	long mapX, long mapY,
	Pcg *lsTown, Pcg *lsDun
)
{
	if( !g_flg_gui )
		return NULL;

	if( lsTown == NULL )
		return NULL;
	if( lsDun == NULL )
		return NULL;
	if( !clip_pos( mapX, mapY ) )
		return NULL;

	rate_t rate = rateMap[mapY][mapX];

	Pcg *ls = NULL;
	if( get_dun()->lev == 0 )
		ls = lsTown;
	else
		ls = lsDun;

	for( Pcg *p = ls->next; p != NULL; p = p->next )
		if( rate < p->nRate )
			return p;

	return NULL;
}

////////////////////////////////////////////////////////////////
// �ѥ�����Υꥹ�Ȥ���Хꥨ�������ˤ��ä��ѥ�����򸡺� (�饹�ܥ�)
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// Pcg *lsTown : ���λ��Υѥ����󡦥ꥹ��
// Pcg *lsDun : �µܤλ��Υѥ����󡦥ꥹ��
// return : �ѥ�����
////////////////////////////////////////////////////////////////

Pcg *PcgDun::srchPcgLsMapLast(
	long mapX, long mapY,
	Pcg *lsXX, Pcg *lsBone
)
{
	if( !g_flg_gui )
		return NULL;

	if( lsXX == NULL )
		return NULL;
	if( lsBone == NULL )
		return NULL;
	if( !clip_pos( mapX, mapY ) )
		return NULL;

	rate_t rate = rateMap[mapY][mapX];

	Pcg *ls = NULL;
	ls = lsXX;

	for( Pcg *p = ls->next; p != NULL; p = p->next )
		if( rate < p->nRate )
			return p;

	return NULL;
}

////////////////////////////////////////////////////////////////
// �ɤ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawWall( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( get_scene() == SCENE_N_LAST_BOSS ){
		switch( nWallPtnTypeLast ){
		case WALL_PTN_TYPE_TILE:
			return drawWallTypeTile( mapX, mapY );
		case WALL_PTN_TYPE_A:
			return drawWallTypeA( mapX, mapY );
		case WALL_PTN_TYPE_B:
			return drawWallTypeB( mapX, mapY );
		}
	} else if( get_dun()->lev == 0 ){
		switch( nWallPtnTypeTown ){
		case WALL_PTN_TYPE_TILE:
			return drawWallTypeTile( mapX, mapY );
		case WALL_PTN_TYPE_A:
			return drawWallTypeA( mapX, mapY );
		case WALL_PTN_TYPE_B:
			return drawWallTypeB( mapX, mapY );
		}
	} else {
		switch( nWallPtnTypeDun ){
		case WALL_PTN_TYPE_TILE:
			return drawWallTypeTile( mapX, mapY );
		case WALL_PTN_TYPE_A:
			return drawWallTypeA( mapX, mapY );
		case WALL_PTN_TYPE_B:
			return drawWallTypeB( mapX, mapY );
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////
// �ɤ����� (tile)
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawWallTypeTile( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	Pcg *p;
	if( get_scene() == SCENE_N_LAST_BOSS ){
		p = srchPcgLsMapLast( mapX, mapY,
				&pcgWallLast, &pcgWallLast );
	} else {
		p = srchPcgLsMap( mapX, mapY,
				&pcgWallTown, &pcgWallDun );
	}
	if( p == NULL )
		return false;

	return p->drawFix( getWBuf(),
			mapX * getTileSizeX(), mapY * getTileSizeX(),
			1 * getTileSizeX(), 1 * getTileSizeY() );
}

////////////////////////////////////////////////////////////////
// �ɤ����� (type_a)
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawWallTypeA( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	long bit = 0;

	// ���������Τդ�������ȹ礻

	if( chkDrawWall( mapX + 0, mapY - 1 ) )
		bit |= gBitIdxWallN;

	if( chkDrawWall( mapX + 0, mapY + 1 ) )
		bit |= gBitIdxWallS;

	if( chkDrawWall( mapX + 1, mapY + 0 ) )
		bit |= gBitIdxWallE;

	if( chkDrawWall( mapX - 1, mapY + 0 ) )
		bit |= gBitIdxWallW;

	long idxX = gIdxWall[bit].x;
	long idxY = gIdxWall[bit].y;

	// �������������Ƥդ����äƤ��뤫?

	long bitAll = (gBitIdxWallN | gBitIdxWallS
			| gBitIdxWallE | gBitIdxWallW);
	if( (bit & bitAll) == bitAll ){
		// �Ф������Τդ�������ȹ礻

		long bitDiagonal = 0;

		if( chkDrawWall( mapX - 1, mapY - 1 ) )
			bitDiagonal |= gBitIdxWallNW;

		if( chkDrawWall( mapX + 1, mapY - 1 ) )
			bitDiagonal |= gBitIdxWallNE;

		if( chkDrawWall( mapX - 1, mapY + 1 ) )
			bitDiagonal |= gBitIdxWallSW;

		if( chkDrawWall( mapX + 1, mapY + 1 ) )
			bitDiagonal |= gBitIdxWallSE;

		idxX = gIdxWallDiagonal[bitDiagonal].x;
		idxY = gIdxWallDiagonal[bitDiagonal].y;
	}

	Pcg *p;
	if( get_scene() == SCENE_N_LAST_BOSS ){
		p = srchPcgLsMapLast( mapX, mapY,
				&pcgWallLast, &pcgWallLast );
	} else {
		p = srchPcgLsMap( mapX, mapY,
				&pcgWallTown, &pcgWallDun );
	}
	if( p == NULL )
		return false;

	return p->drawIdx( getWBuf(),
			mapX * getTileSizeX(),
			mapY * getTileSizeY(),
			1 * getTileSizeX(),
			1 * getTileSizeY(),
			idxX,
			idxY,
			getTileSizeX(),
			getTileSizeY() );
}

////////////////////////////////////////////////////////////////
// �ɤ����� (type_b)
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawWallTypeB( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	long baseY = mapY;
	bool flagHalfX = false;
	bool flagHalfY = false;
	long idxX = 0;
	long idxY = 0;

	// Y

	if( !chkDrawWall( mapX, mapY + 1 ) ){
		baseY = mapY + 0;

		if( !chkDrawWall( mapX, mapY - 1 ) ){
			flagHalfY = true;
		} else {
			idxY = 2;
		}
	} else if( !chkDrawWall( mapX, mapY + 2 ) ){
		baseY = mapY + 1;

		if( !chkDrawWall( mapX, mapY - 1 ) ){
			idxY = 0;
		} else {
			idxY = 1;
		}
	} else if( !chkDrawWall( mapX, mapY + 3 ) ){
		baseY = mapY + 2;

		idxY = 0;
	} else {
		return drawWallTypeBRoof( mapX, mapY );
	}

	// X

	if( !chkDrawWall( mapX - 1, baseY ) ){
		if( !chkDrawWall( mapX + 1, baseY ) ){
			flagHalfX = true;
		} else {
			idxX = 0;
		}
	} else if( !chkDrawWall( mapX + 1, baseY ) ){
		if( !chkDrawWall( mapX - 1, baseY ) ){
			flagHalfX = true;
		} else {
			idxX = 2;
		}
	} else {
		idxX = 1;
	}

	// ����

	idxX += 3;
	idxY += 1;

	return drawWallTypeBCommon(
			mapX, mapY,
			idxX, idxY,
			flagHalfX, flagHalfY );
}

////////////////////////////////////////////////////////////////
// ���������� (type_b)
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawWallTypeBRoof( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	long baseY = mapY + 3;
	bool flagHalfX = false;
	bool flagHalfY = false;
	long idxX = 0;
	long idxY = 0;

	// Y

	if( !chkDrawWall( mapX, baseY + 1 ) ){
		if( !chkDrawWall( mapX, mapY - 1 ) ){
			flagHalfY = true;
		} else {
			idxY = 2;
		}
	} else {
		if( !chkDrawWall( mapX, mapY - 1 ) ){
			idxY = 0;
		} else {
			idxY = 1;
		}
	}

	// X

	if( !chkDrawWall( mapX - 1, mapY )
			|| !chkDrawWall( mapX - 1, baseY ) ){
		if( !chkDrawWall( mapX + 1, mapY )
				|| !chkDrawWall( mapX + 1, baseY ) ){
			flagHalfX = true;
		} else {
			idxX = 0;
		}
	} else if( !chkDrawWall( mapX + 1, mapY )
			|| !chkDrawWall( mapX + 1, baseY ) ){
		if( !chkDrawWall( mapX - 1, mapY )
				|| !chkDrawWall( mapX - 1, baseY ) ){
			flagHalfX = true;
		} else {
			idxX = 2;
		}
	} else {
		idxX = 1;
	}

	// ��

	bool flagCornerNW = false;
	bool flagCornerNE = false;
	bool flagCornerSW = false;
	bool flagCornerSE = false;
	if( chkDrawWall( mapX, mapY - 1 ) ){
		if( chkDrawWall( mapX - 1, mapY ) ){
			if( !chkDrawWall( mapX - 1, mapY - 1 ) ){
				flagCornerNW = true;
			}
		}
		if( chkDrawWall( mapX + 1, mapY ) ){
			if( !chkDrawWall( mapX + 1, mapY - 1 ) ){
				flagCornerNE = true;
			}
		}
	}
	if( chkDrawWall( mapX, baseY + 1 ) ){
		if( chkDrawWall( mapX - 1, baseY ) ){
			if( !chkDrawWall( mapX - 1, baseY + 1 ) ){
				flagCornerSW = true;
			}
		}
		if( chkDrawWall( mapX + 1, baseY ) ){
			if( !chkDrawWall( mapX + 1, baseY + 1 ) ){
				flagCornerSE = true;
			}
		}
	}

	// ����

	idxX += 0;
	idxY += 1;

	drawWallTypeBCommon(
			mapX, mapY,
			idxX, idxY,
			flagHalfX, flagHalfY );

	long mSizeX = getTileSizeX() / 2;
	long mSizeY = getTileSizeY() / 2;
	long offsetX = 2 * getTileSizeX();
	long offsetY = 0 * getTileSizeY();

	Pcg *p;
	if( get_scene() == SCENE_N_LAST_BOSS ){
		p = srchPcgLsMapLast( mapX, mapY,
				&pcgWallLast, &pcgWallLast );
	} else {
		p = srchPcgLsMap( mapX, mapY,
				&pcgWallTown, &pcgWallDun );
	}
	if( p == NULL )
		return false;

	if( flagCornerNW ){
		p->drawOffset( getWBuf(),
				(mapX * getTileSizeX()) + (mSizeX * 0),
				(mapY * getTileSizeY()) + (mSizeY * 0),
				1 * mSizeX,
				1 * mSizeY,
				offsetX + (mSizeX * 0),
				offsetY + (mSizeY * 0) );
	}
	if( flagCornerNE ){
		p->drawOffset( getWBuf(),
				(mapX * getTileSizeX()) + (mSizeX * 1),
				(mapY * getTileSizeY()) + (mSizeY * 0),
				1 * mSizeX,
				1 * mSizeY,
				offsetX + (mSizeX * 1),
				offsetY + (mSizeY * 0) );
	}
	if( flagCornerSW ){
		p->drawOffset( getWBuf(),
				(mapX * getTileSizeX()) + (mSizeX * 0),
				(mapY * getTileSizeY()) + (mSizeY * 1),
				1 * mSizeX,
				1 * mSizeY,
				offsetX + (mSizeX * 0),
				offsetY + (mSizeY * 1) );
	}
	if( flagCornerSE ){
		p->drawOffset( getWBuf(),
				(mapX * getTileSizeX()) + (mSizeX * 1),
				(mapY * getTileSizeY()) + (mSizeY * 1),
				1 * mSizeX,
				1 * mSizeY,
				offsetX + (mSizeX * 1),
				offsetY + (mSizeY * 1) );
	}

	return true;
}

////////////////////////////////////////////////////////////////
// �ɤȲ����ζ��̤����� (type_b)
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long idxX : �ѥ�����Υ���ǥå��� X
// long idxY : �ѥ�����Υ���ǥå��� Y
// bool flagHalfX : ���� 1/2 �Υ�������?
// bool flagHalfY : �⤵�� 1/2 �Υ�������?
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawWallTypeBCommon(
	long mapX, long mapY,
	long idxX, long idxY,
	bool flagHalfX, bool flagHalfY
)
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	long mSizeX = getTileSizeX() / 2;
	long mSizeY = getTileSizeY() / 2;
	long offsetX = idxX / 3 * 3;

	Pcg *p;
	if( get_scene() == SCENE_N_LAST_BOSS ){
		p = srchPcgLsMapLast( mapX, mapY,
				&pcgWallLast, &pcgWallLast );
	} else {
		p = srchPcgLsMap( mapX, mapY,
				&pcgWallTown, &pcgWallDun );
	}
	if( p == NULL )
		return false;

	if( flagHalfX && flagHalfY ){
		// ����⤵�� 1/2 �Υ�����

		p->drawOffset( getWBuf(),
				mapX * getTileSizeX() + 0,
				mapY * getTileSizeY() + 0,
				1 * mSizeX,
				1 * mSizeY,
				(offsetX + 0) * getTileSizeX() + 0,
				1 * getTileSizeY() );
		p->drawOffset( getWBuf(),
				mapX * getTileSizeX() + mSizeX,
				mapY * getTileSizeY() + 0,
				1 * mSizeX,
				1 * mSizeY,
				(offsetX + 2) * getTileSizeX() + mSizeX,
				1 * getTileSizeY() );
		p->drawOffset( getWBuf(),
				mapX * getTileSizeX() + 0,
				mapY * getTileSizeY() + mSizeY,
				1 * mSizeX,
				1 * mSizeY,
				(offsetX + 0) * getTileSizeX() + 0,
				3 * getTileSizeY() + mSizeY );
		p->drawOffset( getWBuf(),
				mapX * getTileSizeX() + mSizeX,
				mapY * getTileSizeY() + mSizeY,
				1 * mSizeX,
				1 * mSizeY,
				(offsetX + 2) * getTileSizeX() + mSizeX,
				3 * getTileSizeY() + mSizeY );

		return true;
	} else if( flagHalfX ){
		// ������ 1/2 �Υ�����

		p->drawOffset( getWBuf(),
				mapX * getTileSizeX() + 0,
				mapY * getTileSizeY() + 0,
				1 * mSizeX,
				1 * getTileSizeY(),
				(offsetX + 0) * getTileSizeX() + 0,
				idxY * getTileSizeY() );
		p->drawOffset( getWBuf(),
				mapX * getTileSizeX() + mSizeX,
				mapY * getTileSizeY() + 0,
				1 * mSizeX,
				1 * getTileSizeY(),
				(offsetX + 2) * getTileSizeX() + mSizeX,
				idxY * getTileSizeY() );

		return true;
	} else if( flagHalfY ){
		// �⤵���� 1/2 �Υ�����

		p->drawOffset( getWBuf(),
				mapX * getTileSizeX() + 0,
				mapY * getTileSizeY() + 0,
				1 * getTileSizeX(),
				1 * mSizeY,
				idxX * getTileSizeX(),
				1 * getTileSizeY() );
		p->drawOffset( getWBuf(),
				mapX * getTileSizeX() + 0,
				mapY * getTileSizeY() + mSizeY,
				1 * getTileSizeX(),
				1 * mSizeY,
				idxX * getTileSizeX(),
				3 * getTileSizeY() + mSizeY );

		return true;
	} else {
		// ����⤵���̾�Υ�����

		p->drawIdx( getWBuf(),
				mapX * getTileSizeX(),
				mapY * getTileSizeY(),
				1 * getTileSizeX(),
				1 * getTileSizeY(),
				idxX,
				idxY,
				getTileSizeX(),
				getTileSizeY() );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// �Фˤ��줿�ʹ֤�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawStatue( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	if( !chkDrawStatue( mapX, mapY ) )
		return true;

	Pcg *p = srchPcgLsMap( mapX, mapY, &pcgStatue, &pcgStatue );
	if( p == NULL )
		return false;

	long w = p->getWidth();
	long h = p->getHeight();

	long x = mapX * getTileSizeX() + (getTileSizeX() - w) / 2;
	long y = (mapY + 1) * getTileSizeY() - h;

	return p->draw( getWBuf(), x, y, w, h );
}

////////////////////////////////////////////////////////////////
// ��ư���֤�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawBootUnit( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	if( !chkDrawBootUnit( mapX, mapY ) )
		return true;

	Pcg *p = srchPcgLsMap( mapX, mapY, &pcgBootUnit, &pcgBootUnit );
	if( p == NULL )
		return false;

	long w = p->getWidth();
	long h = p->getHeight();

	long x = mapX * getTileSizeX() + (getTileSizeX() - w) / 2;
	long y = (mapY + 1) * getTileSizeY() - h;

	return p->draw( getWBuf(), x, y, w, h );
}

////////////////////////////////////////////////////////////////
// ����������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawStreetlamp( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	if( !chkDrawStreetlamp( mapX, mapY ) )
		return true;

	if( chk_night() ){
		return drawObjFix( mapX, mapY, &pcgStreetlampOn,
				&pcgStreetlampOn );
	} else {
		return drawObjFix( mapX, mapY, &pcgStreetlampOff,
				&pcgStreetlampOff );
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ���Ĥ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawSignboard( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	// ���������Ĥ�ü��?

	long dx = 0;
	if( !chkDrawSignboard( mapX - 1, mapY ) )
		dx--;
	if( !chkDrawSignboard( mapX + 1, mapY ) )
		dx++;
	long idxX = dx + 1;

	Pcg *p = srchPcgLsMap( mapX, mapY, &pcgSignboard, &pcgSignboard );
	if( p == NULL )
		return false;

	bool result = p->drawIdx(
			getWBuf(),
			mapX * getTileSizeX(),
			mapY * getTileSizeY(),
			1 * getTileSizeX(),
			1 * getTileSizeY(),
			idxX,
			0,
			getTileSizeX(),
			getTileSizeY() );
	if( !result )
		return result;

	dun_t *dun = get_dun();

#ifdef D_GTK
	GdkDrawable *d = getWBuf()->getPixMap();
	GdkFont *font = gtk_style_get_font( pSignboardStyle );
	GdkGC *gc = pSignboardStyle->fg_gc[GTK_STATE_NORMAL];

	// �طʿ�������

	GdkColor color;

	color.red = 0x0000;
	color.green = 0x0000;
	color.blue = 0x0000;
	gdk_color_alloc( gdk_colormap_get_system(), &color );
	gdk_gc_set_background( gc, &color );

	// ��ɸ�׻�

	long x = mapX * getTileSizeX();
	long y = mapY * getTileSizeY();
	x += (nSignboardIntervalWidth / 2) + nSignboardLeftBearing;
	y += (nSignboardIntervalHeight / 2) + nSignboardAscent;

	// ����

	char s[4 + 1];
	s[0] = dun->map.obj.mnr[mapY][mapX];
	s[1] = '\0';

	// ��

	color.red = 0x4444;
	color.green = 0x4444;
	color.blue = 0x4444;
	gdk_color_alloc( gdk_colormap_get_system(), &color );
	gdk_gc_set_foreground( gc, &color );

	gdk_draw_string( d, font, gc, x + 2, y + 2, s );

	// ����

	color.red = 0xffff;
	color.green = 0xffff;
	color.blue = 0xffff;
	gdk_color_alloc( gdk_colormap_get_system(), &color );
	gdk_gc_set_foreground( gc, &color );

	gdk_draw_string( d, font, gc, x, y, s );

	//

	return true;
#endif // D_GTK

#ifdef D_IPHONE
//@@@
#endif // D_IPHONE

#ifdef D_MFC
	// �طʿ�������

# if FLAG_USE_TEXT_OUT
	CXlnlView *view = theApp.m_pMainFrm->GetView();
	CClientDC dc( view );

	COLORREF color;
	color = RGB( 0x0000, 0x0000, 0x0000 );
	dc.SetBkColor( color );
# else
	D3DCOLOR d3color;
# endif

	// ��ɸ�׻�

	long scrollX = getScrollBarX();
	long scrollY = getScrollBarY();
	long sizX = getTileSizeX( true );
	long sizY = getTileSizeY( true );
	long offsetX = scrollX / sizX;
	long offsetY = scrollY / sizY;
	long x = (mapX * sizX) - scrollX;
	long y = (mapY * sizY) - scrollY;
	x += nSignboardIntervalWidth / 2;
	y += nSignboardIntervalHeight / 2;
	x = x * g_Dir3d.nTileSizeRate / _100_PERCENT;
	y = y * g_Dir3d.nTileSizeRate / _100_PERCENT;

	// ����

	char s[4 + 1];
	s[0] = dun->map.obj.mnr[mapY][mapX];
	s[1] = '\0';

	if( pSignboardFont == NULL )
		return false;

	// ��

# if FLAG_USE_TEXT_OUT
	CFont *pPrevFont = dc.SelectObject( pSignboardFont );

	color = RGB( 0x4444, 0x4444, 0x4444 );
	dc.SetTextColor( color );
	dc.TextOut( x + 2, y + 2, s );
# else
	mD3Signboard.Begin();

	d3color = 0xff444444;
	mD3Signboard.Draw( x + 2, y + 2, d3color, s );
# endif

	// ����

# if FLAG_USE_TEXT_OUT
	color = RGB( 0xffff, 0xffff, 0xffff );
	dc.SetTextColor( color );
	dc.TextOut( x, y, s );

	dc.SelectObject( pPrevFont );
# else
	d3color = 0xffffffff;
	mD3Signboard.Draw( x, y, d3color, s );

	mD3Signboard.End();
# endif

	return true;
#endif // D_MFC

	return false;
}

////////////////////////////////////////////////////////////////
// �������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawWater( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	dun_t *dun = get_dun();

	if( dun->map.obj.mjr[mapY][mapX] == FACE_MJR_WATER ){
		if( dun->map.obj.mnr[mapY][mapX] == FACE_MNR_LAVA ){
			rate_t rate = rateMap[mapY][mapX];
			long n = (nWaterAnimeN + rate) % nWaterAnimeMaxN;

			long drawX = mapX * getTileSizeX();
			long drawY = mapY * getTileSizeY();
			long drawW = getTileSizeX();
			long drawH = getTileSizeY();
			long offsetX = (n / nWaterAnimeMaxY)
					% nWaterAnimeMaxX;
			long offsetY = (n % nWaterAnimeMaxY);
			offsetX *= getTileSizeX();
			offsetY *= getTileSizeY();

			return( pcgLava.next->drawOffset( getWBuf(),
					drawX, drawY, drawW, drawH,
					offsetX, offsetY ) );
		} else {
			return drawFloor( mapX, mapY );
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////
// ��곬�ʤ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawStairsUp( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( TRUE, mapX, mapY, &mjr, &mnr, TRUE );
	if( mjr != FACE_MJR_STAIRS_UP )
		return true;

	return drawObjFix( mapX, mapY, &pcgStairsUpTown,
			&pcgStairsUpDun );
}

////////////////////////////////////////////////////////////////
// ���곬�ʤ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawStairsDown( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( TRUE, mapX, mapY, &mjr, &mnr, TRUE );
	if( mjr != FACE_MJR_STAIRS_DOWN )
		return true;

	if( mnr == FACE_MNR_STAIRS_LAST_BOSS ){
		return drawObjFix( mapX, mapY, &pcgStairsLastBoss,
				&pcgStairsLastBoss );
	} else {
		return drawObjFix( mapX, mapY, &pcgStairsDownTown,
				&pcgStairsDownDun );
	}
}

////////////////////////////////////////////////////////////////
// �Ĥ����ɥ�������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawDoorClose( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	return drawDoorIdx( mapX, mapY, false );
}

////////////////////////////////////////////////////////////////
// �������ɥ�������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawDoorOpen( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	return drawDoorIdx( mapX, mapY, true );
}

////////////////////////////////////////////////////////////////
// �ɥ�������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// bool flagOpen : �������ɥ�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawDoorIdx( long mapX, long mapY, bool flagOpen )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	long idxX = +1;
	long idxY = +1;
	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	char mjrFace;
	if( flagOpen )
		mjrFace = FACE_MJR_DOOR_OPEN;
	else
		mjrFace = FACE_MJR_DOOR_CLOSE;

	set_face_from_map_obj( FALSE, mapX - 1, mapY, &mjr, &mnr, TRUE );
	if( mjr != mjrFace )
		idxX += -1;
	set_face_from_map_obj( FALSE, mapX + 1, mapY, &mjr, &mnr, TRUE );
	if( mjr != mjrFace )
		idxX += +1;

	set_face_from_map_obj( FALSE, mapX, mapY - 1, &mjr, &mnr, TRUE );
	if( mjr != mjrFace )
		idxY += -1;
	set_face_from_map_obj( FALSE, mapX, mapY + 1, &mjr, &mnr, TRUE );
	if( mjr != mjrFace )
		idxY += +1;

	Pcg *p = NULL;
	if( mjrFace == FACE_MJR_DOOR_OPEN ){
		p = srchPcgLsMap( mapX, mapY,
				&pcgDoorOpenTown, &pcgDoorOpenDun );
	} else {
		p = srchPcgLsMap( mapX, mapY,
				&pcgDoorCloseTown, &pcgDoorCloseDun );
	}
	if( p == NULL )
		return false;

	return p->drawIdx( getWBuf(),
			mapX * getTileSizeX(),
			mapY * getTileSizeY(),
			1 * getTileSizeX(),
			1 * getTileSizeY(),
			idxX, idxY,
			getTileSizeX(), getTileSizeY() );
}

////////////////////////////////////////////////////////////////
// �Ĥ����������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawWindowClose( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	return drawObjFix( mapX, mapY, &pcgWindowClose, &pcgWindowClose );
}

////////////////////////////////////////////////////////////////
// �������������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawWindowOpen( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	return drawObjFix( mapX, mapY, &pcgWindowOpen, &pcgWindowOpen );
}

////////////////////////////////////////////////////////////////
// 櫤�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawTrap( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	trap_t *trap = get_trap( mapX, mapY );
	if( trap == NULL )
		return true;

	trap_tab_t *tab = get_trap_tab( trap->kind );
	if( tab == NULL )
		return false;

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( TRUE, mapX, mapY, &mjr, &mnr, TRUE );
	if( mjr != FACE_MJR_TRAP )
		return true;

	Pcg *p = NULL;
	if( trap->flg_chked )
		p = srchPcgLsFace( mjr, mnr, &pcgTrap, &pcgTrap );
	else
		p = pcgTrap.next;
	if( p == NULL )
		return false;

	if( trap->flg_chked && (trap->kind == TRAP_KIND_SANCTUARY) )
		return drawTrapSanctuary( mapX, mapY, trap, p );

	long x = getObjDrawLeft( mapX, p );
	long y = getObjDrawTop( mapY, p );
	long w = getObjDrawWidth( mapX, p );
	long h = getObjDrawHeight( mapY, p );

	return( p->draw( getWBuf(), x, y, w, h ) );
}

////////////////////////////////////////////////////////////////
// �ѥ�����Υꥹ�Ȥ����ʸ���˥ޥå�����ѥ�����򸡺�
// char mjr : �᥸�㡼��ʸ��
// char mnr : �ޥ��ʡ���ʸ��
// Pcg *lsTown : ���λ��Υѥ����󡦥ꥹ��
// Pcg *lsDun : �µܤλ��Υѥ����󡦥ꥹ��
// return : �ѥ�����
////////////////////////////////////////////////////////////////

Pcg *PcgDun::srchPcgLsFace( char mjr, char mnr, Pcg *lsTown, Pcg *lsDun )
{
	if( !g_flg_gui )
		return NULL;

	if( lsTown == NULL )
		return NULL;
	if( lsDun == NULL )
		return NULL;

	Pcg *ls = NULL;
	if( get_dun()->lev == 0 )
		ls = lsTown;
	else
		ls = lsDun;

	Pcg *retPcg = NULL;
	for( Pcg *p = ls->next; p != NULL; p = p->next ){
		if( p->mjr == mjr ){
			if( retPcg == NULL )
				retPcg = p;

			if( p->mnr == mnr ){
				retPcg = p;
				break;
			}
		}
	}

	if( retPcg == NULL )
		retPcg = ls->next;

	return retPcg;
}

////////////////////////////////////////////////////////////////
// ���������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// trap_t *trap : ����
// Pcg *p : �ѥ�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawTrapSanctuary( long mapX, long mapY, trap_t *trap, Pcg *p )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;
	if( trap == NULL )
		return false;
	if( trap->kind != TRAP_KIND_SANCTUARY )
		return false;
	if( p == NULL )
		return false;

	mapX += trap->cx;
	mapY += trap->cy;

	long x = getObjDrawLeft( mapX, p );
	long y = getObjDrawTop( mapY, p );
	long w = getObjDrawWidth( mapX, p );
	long h = getObjDrawHeight( mapY, p );

	return( p->draw( getWBuf(), x, y, w, h ) );
}

////////////////////////////////////////////////////////////////
// �ᥤ��ȥ��֤Υ������������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawCrsrAll( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	bool flagNoErr = true;

	if( !drawCrsrSub( mapX, mapY ) )
		flagNoErr = false;

	if( !drawCrsr( mapX, mapY ) )
		flagNoErr = false;

	return flagNoErr;
}

////////////////////////////////////////////////////////////////
// �ᥤ�󡦥������������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawCrsr( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	return drawCrsrOffset( mapX, mapY, false );
}

////////////////////////////////////////////////////////////////
// ���֡��������������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawCrsrSub( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	return drawCrsrOffset( mapX, mapY, true );
}

////////////////////////////////////////////////////////////////
// �ᥤ�� / ���֡��������������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// bool flagSub : ���֡��������뤫��
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawCrsrOffset( long mapX, long mapY, bool flagSub )
{
	if( !g_flg_gui )
		return true;

	if( !clipWin( mapX, mapY ) )
		return true;

	pos_t *crsr = NULL;
	if( flagSub )
		crsr = get_sub_crsr();
	else
		crsr = get_main_crsr();
	if( crsr == NULL )
		return true;

	if( !clip_pos( crsr->x, crsr->y ) )
		return true;
	if( !clipWin( crsr->x, crsr->y ) )
		return true;

	if( flagSub ){
		if( !chkDrawCrsrSub( mapX, mapY ) )
			return true;
	} else {
		if( !chkDrawCrsr( mapX, mapY ) )
			return true;
	}

	Pcg *p = getCrsr( crsr->x, crsr->y, flagSub );
	if( p == NULL )
		return true;

	long crsrW = p->getWidth();
	long crsrH = p->getHeight();
	long crsrX = (crsr->x * getTileSizeX());
	long crsrY = (crsr->y * getTileSizeY());
	crsrX += (getTileSizeX() / 2) - (crsrW / 2);
	crsrY += (getTileSizeY() / 2) - (crsrH / 2);

	long drawW = getTileSizeX();
	long drawH = getTileSizeY();
	long drawX = mapX * getTileSizeX();
	long drawY = mapY * getTileSizeY();

	long w = (drawX + drawW) - (crsrX + crsrW);
	long h = (drawY + drawH) - (crsrY + crsrH);
	if( w > 0 )
		drawW -= w;
	if( h > 0 )
		drawH -= h;
	if( drawW < 1 )
		return true;
	if( drawH < 1 )
		return true;

	long offsetX = drawX - crsrX;
	long offsetY = drawY - crsrY;

	return( p->drawOffset( getWBuf(),
			drawX, drawY, drawW, drawH, offsetX, offsetY ) );
}

////////////////////////////////////////////////////////////////
// �ѡ��ƥ������󥫡�������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawSquareParty( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	if( !clipWin( mapX, mapY ) )
		return true;

	square_t *square = get_square_mbr();
	if( square == NULL )
		return false;

	if( !clip_pos( square->x, square->y ) )
		return true;
	if( !clipWin( square->x, square->y ) )
		return true;
	if( !chkDrawSquareParty( mapX, mapY ) )
		return true;

	Pcg *p = srchPcgLsSquareParty();
	if( p == NULL )
		return false;

	long squareW = p->getWidth();
	long squareH = p->getHeight();
	long squareX = (square->x * getTileSizeX());
	long squareY = (square->y * getTileSizeY());
	squareX += (getTileSizeX() / 2) - (squareW / 2);
	squareY += (getTileSizeY() / 2) - (squareH / 2);

	long drawW = getTileSizeX();
	long drawH = getTileSizeY();
	long drawX = mapX * getTileSizeX();
	long drawY = mapY * getTileSizeY();

	long w = (drawX + drawW) - (squareX + squareW);
	long h = (drawY + drawH) - (squareY + squareH);
	if( w > 0 )
		drawW -= w;
	if( h > 0 )
		drawH -= h;
	if( drawW < 1 )
		return true;
	if( drawH < 1 )
		return true;

	long offsetX = drawX - squareX;
	long offsetY = drawY - squareY;

	return( p->drawOffset( getWBuf(),
			drawX, drawY, drawW, drawH, offsetX, offsetY ) );
}

////////////////////////////////////////////////////////////////
// �����С������󥫡�������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawSquareMbrAll( long mapX, long mapY )
{
	if( !g_flg_gui )
		return true;

	bool flgSuccess = true;
	for( long i = 0; i < MBR_MAX_N; i++ )
		if( !drawSquareMbr( mapX, mapY, i ) )
			flgSuccess = false;

	return flgSuccess;
}

////////////////////////////////////////////////////////////////
// ���С������󥫡�������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long nMbr : ���С��ֹ�
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawSquareMbr( long mapX, long mapY, long nMbr )
{
	if( !g_flg_gui )
		return true;

	if( !clipWin( mapX, mapY ) )
		return true;
	if( nMbr < 0 )
		return false;
	if( nMbr >= MBR_MAX_N )
		return false;

	square_t *square = get_square_mbr();
	if( square == NULL )
		return false;

	long sqIndX = square->chr_ind_pos[nMbr].x;
	long sqIndY = square->chr_ind_pos[nMbr].y;
	long sqAbsX = square->chr_abs_pos[nMbr].x;
	long sqAbsY = square->chr_abs_pos[nMbr].y;
	if( (sqIndX == sqAbsX) && (sqIndY == sqAbsY) )
		return true;
	if( !clip_pos( sqIndX, sqIndY ) )
		return true;
	if( !clipWin( sqIndX, sqIndY ) )
		return true;
	if( !chkDrawSquareMbr( mapX, mapY, nMbr ) )
		return true;

	Pcg *p = pcgSquareMbr.next;
	if( p == NULL )
		return false;

	long squareW = p->getWidth();
	long squareH = p->getHeight();
	long squareX = (sqIndX * getTileSizeX());
	long squareY = (sqIndY * getTileSizeY());
	squareX += (getTileSizeX() / 2) - (squareW / 2);
	squareY += (getTileSizeY() / 2) - (squareH / 2);

	long drawW = getTileSizeX();
	long drawH = getTileSizeY();
	long drawX = mapX * getTileSizeX();
	long drawY = mapY * getTileSizeY();

	long w = (drawX + drawW) - (squareX + squareW);
	long h = (drawY + drawH) - (squareY + squareH);
	if( w > 0 )
		drawW -= w;
	if( h > 0 )
		drawH -= h;
	if( drawW < 1 )
		return true;
	if( drawH < 1 )
		return true;

	long offsetX = drawX - squareX;
	long offsetY = drawY - squareY;

	return( p->drawOffset( getWBuf(),
			drawX, drawY, drawW, drawH, offsetX, offsetY ) );
}

////////////////////////////////////////////////////////////////
// �ѥ�����Υꥹ�Ȥ���ѡ��ƥ������󥫡��Υѥ�����򸡺�
// return : �ѥ�����
////////////////////////////////////////////////////////////////

Pcg *PcgDun::srchPcgLsSquareParty()
{
	if( !g_flg_gui )
		return NULL;

	square_t *square = get_square_mbr();
	if( square == NULL )
		return NULL;

	char mnr = 'N';
	switch( square->dir ){
	case SQUARE_DIR_NORTH:
		mnr = 'N';
		break;
	case SQUARE_DIR_EAST:
		mnr = 'E';
		break;
	case SQUARE_DIR_SOUTH:
		mnr = 'S';
		break;
	case SQUARE_DIR_WEST:
		mnr = 'W';
		break;
	case SQUARE_DIR_MAX_N:
		break;
	}

	Pcg *p = srchPcgLsFace( FACE_MJR_SQUARE, mnr,
			&pcgSquareParty, &pcgSquareParty );

	return p;
}

////////////////////////////////////////////////////////////////
// �����ƥ������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawItem( long mapX, long mapY, char mjr, char mnr )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	Pcg *p = srchPcgLsFace( mjr, mnr, &pcgItem, &pcgItem );

	long x = getObjDrawLeft( mapX, p );
	long y = getObjDrawTop( mapY, p );
	long w = getObjDrawWidth( mapX, p );
	long h = getObjDrawHeight( mapY, p );

	return p->draw( getWBuf(), x, y, w, h );
}

////////////////////////////////////////////////////////////////
// �������������饯��������
// long x : ���̤� X ��ɸ
// long y : ���̤� Y ��ɸ
// long w : ���̤���
// long h : ���̤ι⤵
////////////////////////////////////////////////////////////////

void PcgDun::drawChrListAll( long x, long y, long w, long h )
{
	if( !g_flg_gui )
		return;

	chr_t *chr = get_sort_chr_head();

	for( long i = 0; i < LOOP_MAX_10000;
			i++, chr = chr->sort_chr_next ){
		if( chr == NULL )
			break;

		Pcg *pPcg = getChrPcg( chr );
		if( pPcg == NULL )
			continue;

		long x1 = getChrDrawLeft( chr, pPcg, false );
		if( x1 >= x + w )
			continue;

		long y1 = getChrDrawTop( chr, pPcg, false );
		if( y1 >= y + h )
			continue;

		long x2 = getChrDrawRight( chr, pPcg, false );
		if( x2 < x )
			continue;

		long y2 = getChrDrawBottom( chr, pPcg, false );
		if( y2 < y )
			continue;

		drawChr( chr->x, chr->y, chr, pPcg, false );
	}
}

////////////////////////////////////////////////////////////////
// �����ɸ���ϰ����������饯��������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// bool flagOneTile : 1 ������ʬ�������褹�뤫��
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawChrList( long mapX, long mapY, bool flagOneTile )
{
	if( !g_flg_gui )
		return true;

	if( !clipWin( mapX, mapY ) )
		return true;

	chr_t *chr = get_sort_chr_head();

	for( long i = 0; i < LOOP_MAX_10000;
			i++, chr = chr->sort_chr_next ){
		if( chr == NULL )
			break;

		if( !chkDrawChr( mapX, mapY, chr ) )
			continue;

		Pcg *pPcg = getChrPcg( chr );
		if( !drawChr( mapX, mapY, chr, pPcg, flagOneTile ) ){
			return false;
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////
// �����ɸ�Υ���饯��������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// chr_t *chr : ����饯��
// Pcg *pPcg : �ѥ�����
// bool flagOneTile : 1 ������ʬ�������褹�뤫��
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawChr(
	long mapX, long mapY,
	chr_t *chr, Pcg *pPcg,
	bool flagOneTile
)
{
	if( !g_flg_gui )
		return true;

	if( chr == NULL )
		return false;
	if( pPcg == NULL )
		return false;

	if( flagOneTile && !clipWin( mapX, mapY ) )
		return true;

	if( chr->work.flg_hyper_boss )
		if( pPcg->hyper_boss != NULL )
			pPcg = pPcg->hyper_boss;

	long x1 = getChrDrawLeft( chr, pPcg, false );
	long y1 = getChrDrawTop( chr, pPcg, false );
	long x2 = getChrDrawRight( chr, pPcg, false );
	long y2 = getChrDrawBottom( chr, pPcg, false );

	long xx1 = x1;
	long yy1 = y1;
	long xx2 = x2;
	long yy2 = y2;

	if( flagOneTile ){
		if( xx1 < ((mapX + 0) * getTileSizeX()) )
			xx1 = ((mapX + 0) * getTileSizeX());
		if( yy1 < ((mapY + 0) * getTileSizeY()) )
			yy1 = ((mapY + 0) * getTileSizeY());

		if( xx2 > ((mapX + 1) * getTileSizeX()) )
			xx2 = ((mapX + 1) * getTileSizeX());
		if( yy2 > ((mapY + 1) * getTileSizeY()) )
			yy2 = ((mapY + 1) * getTileSizeY());
	}

	long w = xx2 - xx1;
	long h = yy2 - yy1;
	if( w < 1 )
		return true;
	if( h < 1 )
		return true;

	long offsetX = xx1 - x1;
	long offsetY = yy1 - y1;

	bool flgDir4 = false;
	if( (chr->kind == CHR_KIND_MBR)
			&& (nPtnDirMbr == N_PTN_DIR_CHR_4) ){
		flgDir4 = true;
	}
	if( (chr->kind == CHR_KIND_MNSTR)
			&& (nPtnDirMnstr == N_PTN_DIR_CHR_4) ){
		flgDir4 = true;
	}
	if( flgDir4 ){
		long dirIdx = get_chr_dir_idx( chr );
		dirIdx *= getHeightChr( chr, pPcg );
		offsetY += dirIdx;
	}

	return( pPcg->drawOffset( getWBuf(),
			xx1, yy1, w, h, offsetX, offsetY ) );
}

////////////////////////////////////////////////////////////////
// GUI VFX ������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawGuiVfx( long mapX, long mapY )
{
	resi_kind_t	resi;

	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;

	gui_vfx_t *vfx = get_gui_vfx( mapX, mapY );
	if( vfx == NULL )
		return true;

	Pcg *p = NULL;
	switch( vfx->kind ){
	case GUI_VFX_KIND_NULL:
	case GUI_VFX_KIND_MAX_N:
		return false;
	case GUI_VFX_KIND_BASH:
		if( vfx->flg_crtcl )
			p = pcgGuiVfxBashCrtcl.next;
		else
			p = pcgGuiVfxBash.next;
		break;
	case GUI_VFX_KIND_ARW:
		p = pcgGuiVfxArw.next;
		break;
	case GUI_VFX_KIND_THROW_ITEM:
		p = srchPcgLsFace( vfx->mjr, vfx->mnr,
				&pcgItem, &pcgItem );
		break;
	case GUI_VFX_KIND_SPELL:
		resi = vfx->resi_kind;
		if( resi < 0 )
			resi = RESI_KIND_SLAS;
		if( resi >= RESI_KIND_MAX_N )
			resi = RESI_KIND_SLAS;

		p = aPcgGuiVfxSpell[resi];
		break;
	case GUI_VFX_KIND_BLAST:
		p = aPcgGuiVfxBlast[vfx->blast_kind];
		break;
	case GUI_VFX_KIND_NINJA:
		p = srchPcgLsNinja( vfx->spell_kind, &pcgGuiVfxNinja );
		break;
	}
	if( p == NULL )
		return false;

	switch( vfx->kind ){
	case GUI_VFX_KIND_NULL:
	case GUI_VFX_KIND_MAX_N:
		return false;
	case GUI_VFX_KIND_BASH:
		return drawGuiVfxBash( mapX, mapY, vfx, p );
	case GUI_VFX_KIND_ARW:
		return drawGuiVfxArw( mapX, mapY, vfx, p );
	case GUI_VFX_KIND_THROW_ITEM:
	case GUI_VFX_KIND_SPELL:
	case GUI_VFX_KIND_BLAST:
		return drawGuiVfxCommon( mapX, mapY, vfx, p );
	case GUI_VFX_KIND_NINJA:
		return drawGuiVfxNinja( mapX, mapY, vfx, p );
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ����� GUI VFX ������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// gui_vfx_t *vfx : VFX �ǡ���
// Pcg *p : �ѥ�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawGuiVfxBash(
	long mapX, long mapY, gui_vfx_t *vfx, Pcg *p
)
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;
	if( vfx == NULL )
		return false;
	if( p == NULL )
		return false;

	long animMaxN = 1;
	if( vfx->flg_crtcl )
		animMaxN = nGuiVfxBashCrtclAnimMax;
	else
		animMaxN = nGuiVfxBashAnimMax;
	long animN = animMaxN * vfx->anim_rate / _100_PERCENT;

	long	idxX = animN;
	long	idxY = 0;

	long w = p->getWidth();
	long h = p->getHeight();
	w /= animMaxN;
	long x = (mapX * getTileSizeX()) + (getTileSizeX() - w) / 2;
	long y = (mapY * getTileSizeY()) + (getTileSizeY() - h) / 2;

	return( p->drawIdx( getWBuf(), x, y, w, h, idxX, idxY, w, h ) );
}

////////////////////////////////////////////////////////////////
// ��� GUI VFX ������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// gui_vfx_t *vfx : VFX �ǡ���
// Pcg *p : �ѥ�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawGuiVfxArw( long mapX, long mapY, gui_vfx_t *vfx, Pcg *p )
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;
	if( vfx == NULL )
		return false;
	if( p == NULL )
		return false;

	long w = p->getWidth();
	long h = p->getHeight();
	w /= 3;
	h /= 4;
	long x = (mapX * getTileSizeX()) + (getTileSizeX() - w) / 2;
	long y = (mapY * getTileSizeY()) + (getTileSizeY() - h) / 2;

	long idxX = 0;
	long idxY = 0;

	switch( vfx->dir_n ){
	case 1:
		idxX = 0;
		idxY = 3;
		break;
	case 2:
		idxX = 1;
		idxY = 3;
		break;
	case 3:
		idxX = 2;
		idxY = 3;
		break;
	case 4:
		idxX = 0;
		idxY = 2;
		break;
	case 5:
		idxX = 1;
		idxY = 2;
		break;
	case 6:
		idxX = 2;
		idxY = 2;
		break;
	case 7:
		idxX = 0;
		idxY = 1;
		break;
	case 8:
		idxX = 1;
		idxY = 1;
		break;
	case 9:
		idxX = 2;
		idxY = 1;
		break;
	default:
		return false;
	}

	return( p->drawIdx( getWBuf(), x, y, w, h, idxX, idxY, w, h ) );
}

////////////////////////////////////////////////////////////////
// ���̤� GUI VFX ������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// gui_vfx_t *vfx : VFX �ǡ���
// Pcg *p : �ѥ�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawGuiVfxCommon(
	long mapX, long mapY, gui_vfx_t *vfx, Pcg *p
)
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;
	if( vfx == NULL )
		return false;
	if( p == NULL )
		return false;

	long x = getObjDrawLeft( mapX, p );
	long y = getObjDrawTop( mapY, p );
	long w = getObjDrawWidth( mapX, p );
	long h = getObjDrawHeight( mapY, p );

	return( p->draw( getWBuf(), x, y, w, h ) );
}

////////////////////////////////////////////////////////////////
// �ѥ�����Υꥹ�Ȥ���Ǧ�ѤΥѥ�����򸡺�
// spell_kind_t kind : ��ʸ�μ���
// Pcg *ls : �ѥ�����Υꥹ��
// return : �ѥ�����
////////////////////////////////////////////////////////////////

Pcg *PcgDun::srchPcgLsNinja( spell_kind_t kind, Pcg *ls )
{
	if( !g_flg_gui )
		return NULL;

	if( ls == NULL )
		return NULL;

	long i = 0;
	for( Pcg *p = ls->next; p != NULL; p = p->next ){
		if( gPcgTabGuiVfxNinja[i].nKind == kind )
			return p;
		i++;
	}

	return ls->next;
}

////////////////////////////////////////////////////////////////
// Ǧ�Ѥ� GUI VFX ������
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// gui_vfx_t *vfx : VFX �ǡ���
// Pcg *p : �ѥ�����
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool PcgDun::drawGuiVfxNinja(
	long mapX, long mapY, gui_vfx_t *vfx, Pcg *p
)
{
	if( !g_flg_gui )
		return true;

	if( !clip_pos( mapX, mapY ) )
		return true;
	if( vfx == NULL )
		return false;
	if( p == NULL )
		return false;

	long animMaxN = 1;
	switch( vfx->spell_kind ){
	default:
		return false;
	case SPELL_KIND_TYPHOON:
		animMaxN = nGuiVfxNinjaTyphoonAnimMax;
		break;
	case SPELL_KIND_CONFLAGRATION:
		animMaxN = nGuiVfxNinjaConflagrationAnimMax;
		break;
	case SPELL_KIND_THUNDERCLOUD:
		animMaxN = nGuiVfxNinjaThundercloudAnimMax;
		break;
	case SPELL_KIND_INUNDATION:
		animMaxN = nGuiVfxNinjaInundationAnimMax;
		break;
	}

	long animN = animMaxN * vfx->anim_rate / _100_PERCENT;

	long	idxX = animN;
	long	idxY = 0;

	long w = p->getWidth();
	long h = p->getHeight();
	w /= animMaxN;
	long x = (mapX * getTileSizeX()) + (getTileSizeX() - w) / 2;
	long y = (mapY * getTileSizeY()) + getTileSizeY() - h;

	return( p->drawIdx( getWBuf(), x, y, w, h, idxX, idxY, w, h ) );
}

////////////////////////////////////////////////////////////////
// ͼ������Υ��ե����Ȥ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long mapW : ��
// long mapH : �⤵
////////////////////////////////////////////////////////////////

void PcgDun::drawNight( long mapX, long mapY, long mapW, long mapH )
{
	if( !g_flg_gui )
		return;

	if( get_dun()->lev != 0 )
		return;
	if( !chk_scene_group( SCENE_GROUP_N_PLAYING ) )
		return;
	if( !chk_night() && !chk_morning() && !chk_evening() )
		return;

	long r = 0x00;
	long g = 0x00;
	long b = 0x00;
	long a = 0x80;
	if( !getGlowColor( &r, &g, &b, &a ) )
		return;

	drawFade( mapX, mapY, mapW, mapH, r, g, b, a );
}

////////////////////////////////////////////////////////////////
// �����ࡦ�����С����Υ��ե����Ȥ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long mapW : ��
// long mapH : �⤵
////////////////////////////////////////////////////////////////

void PcgDun::drawGameOverFade( long mapX, long mapY, long mapW, long mapH )
{
	if( !g_flg_gui )
		return;

	if( get_scene() != SCENE_N_GAME_OVER_WAIT )
		return;

	long r = 0xff;
	long g = 0x00;
	long b = 0x00;
	long a = 0x80;

	drawFade( mapX, mapY, mapW, mapH, r, g, b, a );
}

////////////////////////////////////////////////////////////////
// �ե����ɡ����󡿥����ȤΥ��ե����Ȥ�����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long mapW : ��
// long mapH : �⤵
// long r : ��
// long g : ��
// long b : ��
////////////////////////////////////////////////////////////////

void PcgDun::drawFade(
	long mapX, long mapY, long mapW, long mapH,
	long r, long g, long b, long a
)
{
	if( !g_flg_gui )
		return;

	static long br = -1;
	static long bg = -1;
	static long bb = -1;
	static long ba = -1;

#ifdef D_GTK
	static GdkPixbuf *buf = NULL;
	if( buf == NULL ){
		buf = gdk_pixbuf_new( GDK_COLORSPACE_RGB,
				TRUE, 8,
				getTileSizeX(), getTileSizeY() );
		if( buf == NULL )
			return;
	}

	if( (r != br) || (g != bg) || (b != bb) || (a != ba) ){
		br = r;
		bg = g;
		bb = b;
		ba = a;

		long w = gdk_pixbuf_get_width( buf );
		long h = gdk_pixbuf_get_height( buf );
		for( long y = 0; y < h; y++ ){
			long idxY = gdk_pixbuf_get_rowstride( buf );
			idxY *= y;

			for( long x = 0; x < w; x++ ){
				long idxX = gdk_pixbuf_get_n_channels( buf );
				idxX *= x;

				long idx = idxY + idxX;
				gdk_pixbuf_get_pixels( buf )[idx + 0] = r;
				gdk_pixbuf_get_pixels( buf )[idx + 1] = g;
				gdk_pixbuf_get_pixels( buf )[idx + 2] = b;
				gdk_pixbuf_get_pixels( buf )[idx + 3] = a;
			}
		}
	}

	GdkDrawable *d = getWBuf()->getPixMap();

	for( long yy = mapY; yy < mapY + mapH; yy++ ){
		for( long xx = mapX; xx < mapX + mapW; xx++ ){
			if( !clipWin( xx, yy ) )
				continue;

			long x = xx * getTileSizeX();
			long y = yy * getTileSizeY();

			gdk_pixbuf_render_to_drawable_alpha( buf, d,
					0, 0, x, y,
					getTileSizeX(), getTileSizeY(),
					GDK_PIXBUF_ALPHA_BILEVEL, 0,
					GDK_RGB_DITHER_NORMAL, 0, 0 );
		}
	}
#endif // D_GTK

#ifdef D_IPHONE
//@@@
#endif // D_IPHONE

#ifdef D_MFC
	static long preW = -1;
	static long preH = -1;
	long w = getTileSizeX();
	long h = getTileSizeY();

	// �ƥ������������

	static LPDIRECT3DTEXTURE9 tx = NULL;
	if( (w != preW) || (h != preH) ){
		if( tx != NULL ){
			delete tx;
			tx = NULL;
		}

		HRESULT result = g_Dir3d.pDir3dDevice->CreateTexture(
				w, h, 0,
				D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&tx, NULL );
		if( FAILED( result ) )
			return;

		preW = w;
		preH = h;
	}

	// �ƥ���������ɤ�Ĥ֤�

	IDirect3DSurface9 *sf = NULL;
	tx->GetSurfaceLevel( 0, &sf );

	IDirect3DSurface9 *preTrgt = NULL;
	g_Dir3d.pDir3dDevice->GetRenderTarget( 0, &preTrgt );

	D3DCOLOR clr = D3DCOLOR_XRGB( r, g, b );

	// �ɤ�Ĥ֤�����

	g_Dir3d.pDir3dDevice->SetRenderTarget( 0, sf );
	g_Dir3d.BeginDraw();

	// �ɤ�Ĥ֤�

	g_Dir3d.pDir3dDevice->Clear(
			0, NULL, D3DCLEAR_TARGET,
			clr, 1.0, 0 );

	// �ɤ�Ĥ֤���λ

	g_Dir3d.EndDraw();
	g_Dir3d.pDir3dDevice->SetRenderTarget( 0, preTrgt );

	// �ƥ��������ȾƩ��������

	static WSDimage *img = NULL;
	if( img == NULL )
		img = new WSDimage( tx, w, h );

	D3DCOLOR color = D3DCOLOR_ARGB( a, 0xff, 0xff, 0xff );

	g_Dir3d.BeginAlpha();
	g_Dir3d.BeginDraw();
	for( long yy = mapY; yy < mapY + mapH; yy++ ){
		for( long xx = mapX; xx < mapX + mapW; xx++ ){
			if( !clipWin( xx, yy ) )
				continue;

			long x = xx * getTileSizeX();
			long y = yy * getTileSizeY();

			g_Dir3d.Draw( img, 0, 0, x, y, w, h, color, true );
		}
	}
	g_Dir3d.EndDraw();
	g_Dir3d.EndAlpha();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ���ۤθ��ο������ꤹ��
// long *r : Red
// long *g : Green
// long *b : Blue
// long *a : Alpha
// return : ��ְʳ���? (��������ɬ�פ�ͭ�뤫?)
////////////////////////////////////////////////////////////////

bool PcgDun::getGlowColor( long *r, long *g, long *b, long *a )
{
	if( !g_flg_gui )
		return false;

	*r = 0x00;
	*g = 0x00;
	*b = 0x00;
	*a = 0x00;

	if( chk_morning() ){
		rate_t rate = get_morning_rate();

		*r = 0x00;
		*g = 0x00;
		*b = 0x00;
		*a = 0x80 * (_100_PERCENT - rate) / _100_PERCENT;

		return true;
	}

	if( chk_evening() ){
		rate_t rate = get_evening_rate();
		rate_t rateNight = _100_PERCENT * (rate - 80) / 20;
		if( rateNight < 0 )
			rateNight = 0;

		*r = 0xff * (_100_PERCENT - rateNight) / _100_PERCENT;
		*g = 0x44 * (_100_PERCENT - rateNight) / _100_PERCENT;
		*b = 0x00 * (_100_PERCENT - rateNight) / _100_PERCENT;
		*a = 0x80 * rate / _100_PERCENT;

		return true;
	}

	if( chk_night() ){
		*r = 0x00;
		*g = 0x00;
		*b = 0x00;
		*a = 0x80;

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ����饯���Υѥ�������֤�
// chr_t *chr : ����饯��
// return : �ѥ�����
////////////////////////////////////////////////////////////////

Pcg *PcgDun::getChrPcg( chr_t *chr )
{
	if( !g_flg_gui )
		return NULL;

	if( chr == NULL )
		return NULL;

	if( chr->kind == CHR_KIND_MBR ){
		Pcg *p = aPcgMbr[chr->ls_mbr_n];
		if( p == NULL )
			p = aPcgMbr[0];

		return p;
	}
	if( chr->kind == CHR_KIND_MNSTR ){
		Pcg *p = aPcgMnstr[chr->mnstr_kind];
		if( p == NULL )
			p = aPcgMnstr[0];

		return p;
	}

	return NULL;
}

////////////////////////////////////////////////////////////////
// ����饯���κ�ü�κ�ɸ���֤�
// chr_t *chr : ����饯��
// Pcg *pPcg : �ѥ�����
// bool flagPre : 1 �����κ�ɸ
// return : ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getChrDrawLeft( chr_t *chr, Pcg *pPcg, bool flagPre )
{
	if( !g_flg_gui )
		return MAP_DEL_X;

	if( chr == NULL )
		return MAP_DEL_X;
	if( pPcg == NULL )
		return MAP_DEL_X;

	long bx = 0;
	long ex = 0;
	if( flagPre ){
		bx = get_chr_left( chr->pre_draw_x, chr->dx );
		ex = (get_chr_right( chr->pre_draw_x, chr->dx ) + 1);
	} else {
		bx = get_chr_left( chr->x, chr->dx );
		ex = (get_chr_right( chr->x, chr->dx ) + 1);
	}
	bx *= getTileSizeX();
	ex *= getTileSizeX();

	long x1 = ((ex + bx) / 2) - (getWidthChr( chr, pPcg ) / 2);

	return x1;
}

////////////////////////////////////////////////////////////////
// ����饯���α�ü�κ�ɸ���֤�
// chr_t *chr : ����饯��
// Pcg *pPcg : �ѥ�����
// bool flagPre : 1 �����κ�ɸ
// return : ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getChrDrawRight( chr_t *chr, Pcg *pPcg, bool flagPre )
{
	if( !g_flg_gui )
		return MAP_DEL_X;

	if( chr == NULL )
		return MAP_DEL_X;
	if( pPcg == NULL )
		return MAP_DEL_X;

	long bx = 0;
	long ex = 0;
	if( flagPre ){
		bx = get_chr_left( chr->pre_draw_x, chr->dx );
		ex = (get_chr_right( chr->pre_draw_x, chr->dx ) + 1);
	} else {
		bx = get_chr_left( chr->x, chr->dx );
		ex = (get_chr_right( chr->x, chr->dx ) + 1);
	}
	bx *= getTileSizeX();
	ex *= getTileSizeX();

	long x2 = ((ex + bx) / 2) + (getWidthChr( chr, pPcg ) / 2);

	return x2;
}

////////////////////////////////////////////////////////////////
// ����饯���ξ�ü�κ�ɸ���֤�
// chr_t *chr : ����饯��
// Pcg *pPcg : �ѥ�����
// bool flagPre : 1 �����κ�ɸ
// return : ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getChrDrawTop( chr_t *chr, Pcg *pPcg, bool flagPre )
{
	if( !g_flg_gui )
		return MAP_DEL_Y;

	if( chr == NULL )
		return MAP_DEL_Y;
	if( pPcg == NULL )
		return MAP_DEL_Y;

	long ey = 0;
	if( flagPre ){
		ey = (get_chr_bottom( chr->pre_draw_y, chr->dy ) + 1);
		ey = (get_chr_bottom( chr->pre_draw_y, chr->dy ) + 1);
	} else {
		ey = (get_chr_bottom( chr->y, chr->dy ) + 1);
		ey = (get_chr_bottom( chr->y, chr->dy ) + 1);
	}
	ey *= getTileSizeY();

	long y1 = ey - getHeightChr( chr, pPcg );

	return y1;
}

////////////////////////////////////////////////////////////////
// ����饯���β�ü�κ�ɸ���֤�
// chr_t *chr : ����饯��
// Pcg *pPcg : �ѥ�����
// bool flagPre : 1 �����κ�ɸ
// return : ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getChrDrawBottom( chr_t *chr, Pcg *pPcg, bool flagPre )
{
	if( !g_flg_gui )
		return MAP_DEL_Y;

	if( chr == NULL )
		return MAP_DEL_Y;
	if( pPcg == NULL )
		return MAP_DEL_Y;

	long ey = 0;
	if( flagPre ){
		ey = (get_chr_bottom( chr->pre_draw_y, chr->dy ) + 1);
		ey = (get_chr_bottom( chr->pre_draw_y, chr->dy ) + 1);
	} else {
		ey = (get_chr_bottom( chr->y, chr->dy ) + 1);
		ey = (get_chr_bottom( chr->y, chr->dy ) + 1);
	}
	ey *= getTileSizeY();

	long y2 = ey;

	return y2;
}

////////////////////////////////////////////////////////////////
// ���֥������Ȥκ�ü�κ�ɸ���֤�
// long mapX : �ޥåפκ�ɸ
// Pcg *pPcg : �ѥ�����
// return : ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getObjDrawLeft( long mapX, Pcg *pPcg )
{
	if( !g_flg_gui )
		return( mapX * getTileSizeX() );

	long tileSize = getTileSizeX();

	long w = pPcg->getWidth();
	long x = mapX * tileSize;
	long dx = (tileSize - w) / 2;

	return( x + dx );
}

////////////////////////////////////////////////////////////////
// ���֥������Ȥα�ü�κ�ɸ���֤�
// long mapX : �ޥåפκ�ɸ
// Pcg *pPcg : �ѥ�����
// return : ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getObjDrawRight( long mapX, Pcg *pPcg )
{
	if( !g_flg_gui )
		return( mapX * getTileSizeX() );

	long left = getObjDrawLeft( mapX, pPcg );

	return( left + pPcg->getWidth() );
}

////////////////////////////////////////////////////////////////
// ���֥������Ȥ������֤�
// long mapX : �ޥåפκ�ɸ
// Pcg *pPcg : �ѥ�����
// return : ��
////////////////////////////////////////////////////////////////

long PcgDun::getObjDrawWidth( long mapX, Pcg *pPcg )
{
	if( !g_flg_gui )
		return( 1 * getTileSizeX() );

	return( pPcg->getWidth() );
}

////////////////////////////////////////////////////////////////
// ���֥������Ȥξ�ü�κ�ɸ���֤�
// long mapY : �ޥåפκ�ɸ
// Pcg *pPcg : �ѥ�����
// return : ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getObjDrawTop( long mapY, Pcg *pPcg )
{
	if( !g_flg_gui )
		return( mapY * getTileSizeY() );

	long tileSize = getTileSizeY();

	long h = pPcg->getHeight();
	long y = mapY * tileSize;
	long dy = (tileSize - h) / 2;

	return( y + dy );
}

////////////////////////////////////////////////////////////////
// ���֥������Ȥβ�ü�κ�ɸ���֤�
// long mapY : �ޥåפκ�ɸ
// Pcg *pPcg : �ѥ�����
// return : ��ɸ
////////////////////////////////////////////////////////////////

long PcgDun::getObjDrawBottom( long mapY, Pcg *pPcg )
{
	if( !g_flg_gui )
		return( mapY * getTileSizeY() );

	long top = getObjDrawTop( mapY, pPcg );

	return( top + pPcg->getHeight() );
}

////////////////////////////////////////////////////////////////
// ���֥������Ȥι⤵���֤�
// long mapY : �ޥåפκ�ɸ
// Pcg *pPcg : �ѥ�����
// return : �⤵
////////////////////////////////////////////////////////////////

long PcgDun::getObjDrawHeight( long mapY, Pcg *pPcg )
{
	if( !g_flg_gui )
		return( 1 * getTileSizeY() );

	return( pPcg->getHeight() );
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ���ɤ�Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : �ɤ���
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawWall( long mapX, long mapY )
{
	if( !clip_pos( mapX, mapY ) )
		return true;

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( FALSE, mapX, mapY, &mjr, &mnr, TRUE );

	switch( mjr ){
	case FACE_MJR_WALL:
	case FACE_MJR_DOOR_OPEN:
	case FACE_MJR_DOOR_CLOSE:
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ��������Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ��������
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawStatue( long mapX, long mapY )
{
	if( !clip_pos( mapX, mapY ) )
		return true;

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( TRUE, mapX, mapY, &mjr, &mnr, TRUE );

	if( mjr != FACE_MJR_WALL )
		return false;
	if( mnr != FACE_MNR_STATUE )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ����ư���֤�Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ��ư���֤���
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawBootUnit( long mapX, long mapY )
{
	if( !clip_pos( mapX, mapY ) )
		return true;

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( TRUE, mapX, mapY, &mjr, &mnr, TRUE );

	if( mjr != FACE_MJR_WALL )
		return false;
	if( mnr != FACE_MNR_BOOT_UNIT )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ��������Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ��������
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawStreetlamp( long mapX, long mapY )
{
	if( !clip_pos( mapX, mapY ) )
		return true;

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( TRUE, mapX, mapY, &mjr, &mnr, TRUE );

	if( mjr != FACE_MJR_WALL )
		return false;
	if( mnr != FACE_MNR_STREETLAMP )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ�����Ĥ�Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���Ĥ���
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawSignboard( long mapX, long mapY )
{
	if( !clip_pos( mapX, mapY ) )
		return true;

	char mjr = FACE_MJR_NULL;
	char mnr = FACE_MNR_NULL;
	set_face_from_map_obj( FALSE, mapX, mapY, &mjr, &mnr, TRUE );

	if( mjr != FACE_MJR_WALL )
		return false;
	if( mnr < 'A' )
		return false;
	if( mnr > 'Z' )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ�����褬���뤫Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���褬���뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawSanctuary( long mapX, long mapY, trap_t *trap )
{
	if( !g_flg_gui )
		return false;

	if( trap == NULL )
		return false;
	if( !clip_pos( mapX, mapY ) )
		return false;
	if( !clip_pos( trap->x, trap->y ) )
		return false;

	Pcg *p = srchPcgLsFace( FACE_MJR_TRAP, FACE_MNR_TRAP_SANCTUARY,
			&pcgTrap, &pcgTrap );
	if( p == NULL )
		return false;

	long x = mapX * getTileSizeX();
	long y = mapY * getTileSizeY();
	long w = p->getWidth();
	long h = p->getHeight();

	long bx = (trap->x * getTileSizeX()) - (w / 2);
	long by = (trap->y * getTileSizeY()) - (h / 2);
	long ex = bx + w;
	long ey = by + h;

	if( x < bx )
		return false;
	if( y < by )
		return false;
	if( x > ex )
		return false;
	if( y > ey )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ���б�������������Υѥ�������֤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// bool flagSub : ���֡��������뤫��
// return : ��������Υѥ�����
////////////////////////////////////////////////////////////////

Pcg *PcgDun::getCrsr( long mapX, long mapY, bool flagSub )
{
	if( !g_flg_gui )
		return NULL;

	if( !clip_pos( mapX, mapY ) )
		return NULL;

	// ����饯��

	attitude_t kind = ATTITUDE_NEUTRAL;
	dun_t *dun = get_dun();
	chr_t *chr = dun->map.chr_p[mapY][mapX];

	if( chr != NULL ){
		kind = chr->attitude;
		if( kind == ATTITUDE_NEUTRAL ){
			kind = ATTITUDE_FRIENDLY;
		}
	}

	// �����Ƥ��뤫?

	flg_map_t flg = dun->map.chr.flg[mapY][mapX];

	if( !chk_flg( flg, FLG_MAP_CHR_FIND ) )
		kind = ATTITUDE_NEUTRAL;
	else if( chk_flg( flg, FLG_MAP_CHR_INVISIBLE ) )
		kind = ATTITUDE_NEUTRAL;

	//

	if( flagSub )
		return aPcgCrsrSub[kind];
	else
		return aPcgCrsr[kind];

	return NULL;
}

////////////////////////////////////////////////////////////////
// �������롦�ѥ�����������֤�
// bool flagSub : ���֡��������뤫?
// return : ��
////////////////////////////////////////////////////////////////

long PcgDun::getCrsrWidth( bool flagSub )
{
	if( !g_flg_gui )
		return( 1 * getTileSizeX() );

	long size = getTileSizeX();

	Pcg **p = NULL;
	if( flagSub )
		p = aPcgCrsrSub;
	else
		p = aPcgCrsr;
	if( p == NULL )
		return size;

	long nMax = size;
	for( long i = 0; i < ATTITUDE_MAX_N; i++ ){
		if( p[i] == NULL )
			continue;

		long n = p[i]->getWidth();
		if( nMax < n )
			nMax = n;
	}

	long n = nMax;
	n = (n + size - 1) / size;
	n = (n / 2) * 2 + 1;

	return n;
}

////////////////////////////////////////////////////////////////
// �������롦�ѥ�����ι⤵���֤�
// bool flagSub : ���֡��������뤫?
// return : �⤵
////////////////////////////////////////////////////////////////

long PcgDun::getCrsrHeight( bool flagSub )
{
	if( !g_flg_gui )
		return( 1 * getTileSizeY() );

	long size = getTileSizeY();

	Pcg **p = NULL;
	if( flagSub )
		p = aPcgCrsrSub;
	else
		p = aPcgCrsr;
	if( p == NULL )
		return size;

	long nMax = size;
	for( long i = 0; i < ATTITUDE_MAX_N; i++ ){
		if( p[i] == NULL )
			continue;

		long n = p[i]->getHeight();
		if( nMax < n )
			nMax = n;
	}

	long n = nMax;
	n = (n + size - 1) / size;
	n = (n / 2) * 2 + 1;

	return n;
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ�˥ᥤ�󡦥������뤬���뤫Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : �������뤬���뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawCrsr( long mapX, long mapY )
{
	return chkDrawCrsrCommon( mapX, mapY, false );
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ�˥��֡��������뤬���뤫Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : �������뤬���뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawCrsrSub( long mapX, long mapY )
{
	return chkDrawCrsrCommon( mapX, mapY, true );
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ�˥ᥤ�� / ���֡��������뤬���뤫Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// bool flagSub : ���֡��������뤫��
// return : �������뤬���뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawCrsrCommon( long mapX, long mapY, bool flagSub )
{
	if( !g_flg_gui )
		return false;

	if( !clip_pos( mapX, mapY ) )
		return false;

	pos_t *crsr = NULL;
	if( flagSub )
		crsr = get_sub_crsr();
	else
		crsr = get_main_crsr();
	if( crsr == NULL )
		return false;
	if( !clip_pos( crsr->x, crsr->y ) )
		return false;

	Pcg *p = getCrsr( crsr->x, crsr->y, flagSub );
	if( p == NULL )
		return false;

	long x = mapX * getTileSizeX();
	long y = mapY * getTileSizeY();
	long w = p->getWidth();
	long h = p->getHeight();

	long bx = (crsr->x * getTileSizeX()) - (w / 2);
	long by = (crsr->y * getTileSizeY()) - (h / 2);
	long ex = bx + w;
	long ey = by + h;

	if( x < bx )
		return false;
	if( y < by )
		return false;
	if( x > ex )
		return false;
	if( y > ey )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ�˥ѡ��ƥ������󥫡������뤫Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���󥫡������뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawSquareParty( long mapX, long mapY )
{
	if( !g_flg_gui )
		return false;

	if( !clip_pos( mapX, mapY ) )
		return false;

	square_t *square = get_square_mbr();
	if( square == NULL )
		return false;
	if( !clip_pos( square->x, square->y ) )
		return false;

	Pcg *p = srchPcgLsSquareParty();
	if( p == NULL )
		return false;

	long x = mapX * getTileSizeX();
	long y = mapY * getTileSizeY();
	long w = p->getWidth();
	long h = p->getHeight();

	long bx = (square->x * getTileSizeX()) - (w / 2);
	long by = (square->y * getTileSizeY()) - (h / 2);
	long ex = bx + w;
	long ey = by + h;

	if( x < bx )
		return false;
	if( y < by )
		return false;
	if( x > ex )
		return false;
	if( y > ey )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ����κ�ɸ�˥��С������󥫡������뤫Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// long nMbr : ���С��ֹ�
// return : ���󥫡������뤫��
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawSquareMbr( long mapX, long mapY, long nMbr )
{
	if( !g_flg_gui )
		return false;

	if( !clip_pos( mapX, mapY ) )
		return false;
	if( nMbr < 0 )
		return false;
	if( nMbr >= MBR_MAX_N )
		return false;

	square_t *square = get_square_mbr();
	if( square == NULL )
		return false;
	if( !clip_pos( square->x, square->y ) )
		return false;

	Pcg *p = pcgSquareMbr.next;
	if( p == NULL )
		return false;

	long sqIndX = square->chr_ind_pos[nMbr].x;
	long sqIndY = square->chr_ind_pos[nMbr].y;
	long sqAbsX = square->chr_abs_pos[nMbr].x;
	long sqAbsY = square->chr_abs_pos[nMbr].y;
	if( (sqIndX == sqAbsX) && (sqIndY == sqAbsY) )
		return false;

	long x = mapX * getTileSizeX();
	long y = mapY * getTileSizeY();
	long w = p->getWidth();
	long h = p->getHeight();

	long bx = (sqIndX * getTileSizeX()) - (w / 2);
	long by = (sqIndY * getTileSizeY()) - (h / 2);

	long ex = bx + w;
	long ey = by + h;

	if( x < bx )
		return false;
	if( y < by )
		return false;
	if( x > ex )
		return false;
	if( y > ey )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ����饯���Υѥ����󤬻���κ�ɸ���ϰ��⤫Ĵ�٤�
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// chr_t *chr : ����饯��
// return : �ϰ��⤫��
////////////////////////////////////////////////////////////////

bool PcgDun::chkDrawChr( long mapX, long mapY, chr_t *chr )
{
	if( !g_flg_gui )
		return false;

	if( chr == NULL )
		return false;

	if( !clip_pos( mapX, mapY ) )
		return false;
	if( !clipWin( mapX, mapY ) )
		return false;
	if( chr->kind == CHR_KIND_MNSTR )
		if( !chk_flg( chr->flg_map, FLG_MAP_CHR_FIND ) )
			return false;
	if( chk_flg_or( chr->stat, FLG_STAT_NOT_EXIST | FLG_STAT_DEAD ) )
		return false;

	Pcg *pPcg = getChrPcg( chr );

	long x1 = getChrDrawLeft( chr, pPcg, false );
	long y1 = getChrDrawTop( chr, pPcg, false );
	long x2 = getChrDrawRight( chr, pPcg, false );
	long y2 = getChrDrawBottom( chr, pPcg, false );

	long sx = getTileSizeX();
	long sy = getTileSizeY();

	if( x1 >= ((mapX + 1) * sx) )
		return false;
	if( y1 >= ((mapY + 1) * sy) )
		return false;

	if( x2 < ((mapX + 0) * sx) )
		return false;
	if( y2 < ((mapY + 0) * sy) )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// 1 ����饯��ʬ�Υ���ե��å����ѥ�����������֤�
// chr_t *chr : ����饯��
// Pcg *pPcg : �ѥ�����
// return : ��
////////////////////////////////////////////////////////////////

long PcgDun::getWidthChr( chr_t *chr, Pcg *pPcg )
{
	if( !g_flg_gui )
		return( 1 * getTileSizeX() );

	if( chr == NULL )
		return 0;
	if( pPcg == NULL )
		return 0;

	long n = 1;
	if( chr->kind == CHR_KIND_MBR )
		n = nPtnDirMbr;
	if( chr->kind == CHR_KIND_MNSTR )
		n = nPtnDirMnstr;

	return( pPcg->getWidth() / n );
}

////////////////////////////////////////////////////////////////
// 1 ����饯��ʬ�Υ���ե��å����ѥ�����ι⤵���֤�
// chr_t *chr : ����饯��
// Pcg *pPcg : �ѥ�����
// return : �⤵
////////////////////////////////////////////////////////////////

long PcgDun::getHeightChr( chr_t *chr, Pcg *pPcg )
{
	if( !g_flg_gui )
		return( 1 * getTileSizeY() );

	if( chr == NULL )
		return 0;
	if( pPcg == NULL )
		return 0;

	long n = 1;
	if( chr->kind == CHR_KIND_MBR )
		n = nPtnDirMbr;
	if( chr->kind == CHR_KIND_MNSTR )
		n = nPtnDirMnstr;

	return( pPcg->getHeight() / n );
}

////////////////////////////////////////////////////////////////
// ���С��Υ���ե��å����ѥ�����Υơ��֥���֤�
// return : �ơ��֥�
////////////////////////////////////////////////////////////////

PcgTab *PcgDun::getPcgTabMbr()
{
	if( !g_flg_gui )
		return NULL;

	return &gPcgTabMbrDflt;
}

////////////////////////////////////////////////////////////////
// Ĺ���������褹��
// long x : X ��ɸ
// long y : Y ��ɸ
// long w : ��
// long h : �⤵
// long r : ��
// long g : ��
// long b : ��
////////////////////////////////////////////////////////////////

void PcgDun::drawRectangle(
	long x, long y, long w, long h,
	long r, long g, long b
)
{
	if( !g_flg_gui )
		return;

#ifdef D_GTK
	GdkDrawable *d = getWBuf()->getPixMap();
	static GdkGC *gc = NULL;
	if( gc == NULL )
		gc = gdk_gc_new( gMapDrawingArea->window );

	GdkColor colorFg;
	colorFg.red = r;
	colorFg.green = g;
	colorFg.blue = b;
	gdk_color_alloc( gdk_colormap_get_system(), &colorFg );
	gdk_gc_set_foreground( gc, &colorFg );

	GdkColor colorBg;
	colorBg.red = 0x0000;
	colorBg.green = 0x0000;
	colorBg.blue = 0x0000;
	gdk_color_alloc( gdk_colormap_get_system(), &colorBg );
	gdk_gc_set_background( gc, &colorBg );

	gdk_draw_rectangle( d, gc, TRUE, x, y, w, h );
#endif // D_GTK

#ifdef D_IPHONE
//@@@
#endif // D_IPHONE

#ifdef D_MFC
	long x2 = x + w;
	long y2 = y + h;
	if( x < 0 )
		x = 0;
	if( y < 0 )
		y = 0;
	if( x2 < 0 )
		x2 = 0;
	if( y2 < 0 )
		y2 = 0;
	long maxX = gPcgDun.getScrollBarX() + getScrollBarW();
	long maxY = gPcgDun.getScrollBarY() + getScrollBarH();
	if( x > maxX )
		x = maxX;
	if( y > maxY )
		y = maxY;
	if( x2 > maxX )
		x2 = maxX;
	if( y2 > maxY )
		y2 = maxY;
	w = x2 - x;
	h = y2 - y;
	if( w <= 0 )
		return;
	if( h <= 0 )
		return;

	// �ƥ������������

	const long txW = 32;
	const long txH = 32;
	static LPDIRECT3DTEXTURE9 tx = NULL;
	if( tx == NULL ){
		g_Dir3d.BeginDraw();
		HRESULT result = g_Dir3d.pDir3dDevice->CreateTexture(
				txW, txH, 0,
				D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&tx, NULL );
		g_Dir3d.EndDraw();

		if( FAILED( result ) )
			return;
	}

	static long preR = -1;
	static long preG = -1;
	static long preB = -1;
	r = ((r >> 8) & 0xff);
	g = ((g >> 8) & 0xff);
	b = ((b >> 8) & 0xff);
	D3DCOLOR clr = D3DCOLOR_XRGB( r, g, b );

	// �ƥ���������ɤ�Ĥ֤�

	if( (r != preR) || (g != preG) || (b != preB) ){
		preR = r;
		preG = g;
		preB = b;

		// �ɤ�Ĥ֤�����

		g_Dir3d.BeginDraw();

		IDirect3DSurface9 *sf = NULL;
		tx->GetSurfaceLevel( 0, &sf );

		IDirect3DSurface9 *preTrgt = NULL;
		g_Dir3d.pDir3dDevice->GetRenderTarget( 0, &preTrgt );
		g_Dir3d.pDir3dDevice->SetRenderTarget( 0, sf );

		// �ɤ�Ĥ֤�

		g_Dir3d.pDir3dDevice->Clear(
				0, NULL, D3DCLEAR_TARGET,
				clr, 1.0, 0 );

		// �ɤ�Ĥ֤���λ

		g_Dir3d.pDir3dDevice->SetRenderTarget( 0, preTrgt );

		g_Dir3d.EndDraw();
	}

	// �ƥ������������

	static WSDimage *img = NULL;
	if( img == NULL )
		img = new WSDimage( tx, txW, txH );

	g_Dir3d.BeginDraw();
	for( long yy = y; yy < y + h; yy += txH ){
		for( long xx = x; xx < x + w; xx += txW ){
			long ww, hh;
			ww = (x + w) - xx;
			if( ww > txW )
				ww = txW;
			hh = (y + h) - yy;
			if( hh > txH )
				hh = txH;

			g_Dir3d.Draw( img, 0, 0, xx, yy, ww, hh );
		}
	}
	g_Dir3d.EndDraw();
#endif // D_MFC
}
