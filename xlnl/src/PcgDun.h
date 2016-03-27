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
* $Id: PcgDun.h,v 1.88 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef PCG_DUN_H
#define PCG_DUN_H	1

////////////////////////////////////////////////////////////////
// ���󥸥����������
////////////////////////////////////////////////////////////////

#include "misc.h"
#include "mnstr-kind.h"
#include "item.h"
#include "trap.h"
#include "party.h"
#include "mnstr.h"

#include "GraphConf.h"
#include "DemoTitle.h"
#include "DemoLastBoss.h"
#include "DemoGameOver.h"
#include "DemoEnding.h"
#include "GuiLastBoss.h"
#include "Pcg.h"

#ifdef D_WS
# include <WSCstring.h>
#endif //D_WS

#ifdef D_GTK
# include "GtkWSCstring.h"
#endif //D_GTK

#ifdef D_MAC
# include "MacWSCstring.h"
#endif //D_MAC

#ifdef D_IPHONE
# include "IPhoneWSCstring.h"
#endif //D_IPHONE

#ifdef D_MFC
# include "MfcWSCstring.h"
# include "xlnl-dows/Dir3d.h"
#endif //D_MFC

////////////////////////////////////////////////////////////////

// �ǥե���ȤΥǥ��쥯�ȥ�
#define STR_DEFAULT_GRAPH_DIR_NAME	"xlnl-" VERSION "/"
// ���̥ǥ��쥯�ȥ�
#define STR_FIX_GRAPH_DIR_NAME	".xlnl/"

// �ѥ�����Υե�����̾�γ�ĥ��
#if	defined( D_WS )
# define	STR_GRAPH_FILE_EXT	\
		"png jpg jpeg bmp " \
		"PNG JPG JPEG BMP " \
		"Bmp"
#elif	defined( D_GTK )
# define	STR_GRAPH_FILE_EXT	\
		"png xpm jpg jpeg tif pnm bmp gif " \
		"PNG XPM JPG JPEG TIF PNM BMP GIF " \
		"Bmp"
#elif	defined( D_IPHONE )
# define	STR_GRAPH_FILE_EXT	\
		"png jpg jpeg bmp " \
		"PNG JPG JPEG BMP " \
		"Bmp"
#elif	defined( D_MFC )
# define	STR_GRAPH_FILE_EXT	\
		"png jpg jpeg bmp " \
		"PNG JPG JPEG BMP " \
		"Bmp"
#else
# define	STR_GRAPH_FILE_EXT	\
		"png jpg jpeg bmp " \
		"PNG JPG JPEG BMP " \
		"Bmp"
#endif

// �ѥ�����Υơ��֥�
struct PcgTab {
	// ��󥹥����ξ��μ���
	long	nKind;
	// ��ʸ��
	char mjr, mnr;
	// �ѥ�����λȤ�����
	ratio_t nRatio;

	// �ѥ�����Υե�����Τ���ǥ��쥯�ȥ�
	WSCstring sDir;
};

typedef enum {
	WALL_PTN_TYPE_TILE,
	WALL_PTN_TYPE_A,
	WALL_PTN_TYPE_B,
} WallPtnType;

typedef enum {
	N_PTN_DIR_CHR_1 = 1,
	N_PTN_DIR_CHR_4 = 4,
} NPtnDirChr;

const long CUI_TILE_SIZE_X = 32;
const long CUI_TILE_SIZE_Y = 32;

////////////////////////////////////////////////////////////////

class PcgDun {
public:
	GraphConf *pGraphConf;
	DemoTitle *pDemoTitle;
	DemoLastBoss *pDemoLastBoss;
	DemoGameOver *pDemoGameOver;
	DemoEnding *pDemoEnding;

	// �ѥ�����γ���Ψ
	rate_t nTileSizeRate;

	// ����饯���θ����Ƥ��������Υѥ������
	NPtnDirChr nPtnDirMbr;
	NPtnDirChr nPtnDirMnstr;

private:
	//// �����롦�⡼�� ////

	// �ѥ�����δ�ॵ����
	long nTileSizeX, nTileSizeY;

	// ����Υѥ�����Υꥹ��
	Pcg pcgNullTown;
	Pcg pcgNullDun;
	// ���Υѥ�����Υꥹ��
	Pcg pcgFloorTown;
	Pcg pcgFloorDun;
	Pcg pcgFloorLast;
	// ����Υѥ�����Υꥹ��
	Pcg pcgHole;
	// �ɤΥѥ�����Υꥹ��
	Pcg pcgWallTown;
	Pcg pcgWallDun;
	Pcg pcgWallLast;
	Pcg pcgStatue;
	Pcg pcgBootUnit;
	// �����Υѥ�����Υꥹ��
	Pcg pcgStreetlampOn;
	Pcg pcgStreetlampOff;
	// ���ĤΥѥ�����Υꥹ��
	Pcg pcgSignboard;
	// ��Υѥ�����Υꥹ��
	// �ϴ�Υѥ�����Υꥹ��
	Pcg pcgLava;
	// ���ʤΥѥ�����Υꥹ��
	Pcg pcgStairsUpTown;
	Pcg pcgStairsUpDun;
	Pcg pcgStairsDownTown;
	Pcg pcgStairsDownDun;
	Pcg pcgStairsLastBoss;
	// �ɥ��Υѥ�����Υꥹ��
	Pcg pcgDoorCloseTown;
	Pcg pcgDoorCloseDun;
	Pcg pcgDoorOpenTown;
	Pcg pcgDoorOpenDun;
	// ��Υѥ�����Υꥹ��
	Pcg pcgWindowClose;
	Pcg pcgWindowOpen;

	// ��������Υѥ�����Υꥹ��
	Pcg *aPcgCrsr[ATTITUDE_MAX_N];
	Pcg *aPcgCrsrSub[ATTITUDE_MAX_N];
	// ���󥫡��Υѥ�����Υꥹ��
	Pcg pcgSquareParty;
	Pcg pcgSquareMbr;

	// �����ƥ�Υѥ�����Υꥹ��
	Pcg pcgItem;
	// 櫤Υѥ�����Υꥹ��
	Pcg pcgTrap;

	// ���С��Υѥ�����Υꥹ��
	Pcg *aPcgMbr[LS_MBR_MAX_N];
	// ��󥹥����Υѥ�����Υꥹ��
	Pcg *aPcgMnstr[MNSTR_KIND_MAX_N];

	// ����� VFX �Υѥ�����Υꥹ��
	Pcg pcgGuiVfxBash;
	// ����ƥ����빶��� VFX �Υѥ�����Υꥹ��
	Pcg pcgGuiVfxBashCrtcl;
	// ��� VFX �Υѥ�����Υꥹ��
	Pcg pcgGuiVfxArw;
	// ��ʸ�� VFX �Υѥ�����Υꥹ��
	Pcg *aPcgGuiVfxSpell[RESI_KIND_MAX_N];
	// ������ VFX �Υѥ�����Υꥹ��
	Pcg *aPcgGuiVfxBlast[BLAST_KIND_MAX_N];
	// Ǧ�Ѥ� VFX �Υѥ�����Υꥹ��
	Pcg pcgGuiVfxNinja;

	// �饹�ܥ�
	GuiLastBoss lastBossXX;

	// �ѥ�����ΥХꥨ�������μ���Υޥå�
	rate_t rateMap[MAP_MAX_Y][MAP_MAX_X];

	// �ɤΥѥ����󡦥�����
	WallPtnType nWallPtnTypeTown;
	WallPtnType nWallPtnTypeDun;
	WallPtnType nWallPtnTypeLast;

	// ��Υ��˥ᡦ�ե졼��
	long nWaterAnimeN;

	// �����褹��ɬ�פ����륭��饯���Υޥå�
	bool bFlgUpdate[MAP_MAX_Y][MAP_MAX_X];

	// ���֥롦�Хåե�
	WSDmwindowDev *pWBuf;

	//// ���ĤΥե���� ////

	// �ե���ȤΥݥ����
	long nSignboardPoint;

	// �ե���Ȥδ�ॵ����
	long nSignboardSizeX, nSignboardSizeY;

	// ʸ���ֳ�
	long nSignboardIntervalWidth, nSignboardIntervalHeight;

#ifdef D_GTK
	// �ե���ȤΥ�������
	GtkStyle *pSignboardStyle;

	// �ե���ȤΥ�����
	gint nSignboardLeftBearing, nSignboardRightBearing;
	gint nSignboardWidth, nSignboardAscent, nSignboardDescent;
#endif // D_GTK

#ifdef D_MAC
	// �ե���ȤΥ�������
	void *pSignboardStyle;
#endif // D_MAC

#ifdef D_IPHONE
	// �ե���ȤΥ�������
	void *pSignboardStyle;
#endif // D_IPHONE

#ifdef D_MFC
	// �ե���ȤΥ�������
	void *pSignboardStyle;
	LOGFONT mSignboardFontDesc;
	CFont *pSignboardFont;

	CDir3dText mD3Signboard;
#endif // D_MFC

	//// �ƥ����ȡ��⡼�� ////

	// �ե���ȤΥǥե���ȤΥݥ����
	long nTextModeDefaultPoint;

	// �ե���Ȥδ�ॵ����
	long nTextSizeX, nTextSizeY;

	// ʸ���ֳ�
	long nIntervalWidth, nIntervalHeight;

#ifdef D_GTK
	// �ե���ȤΥ�������
	GtkStyle *pStyle;
	GtkStyle *pStyleVfx;

	// �ե���ȤΥ�����
	gint nLeftBearing, nRightBearing;
	gint nWidth, nAscent, nDescent;
	gint nLeftBearingVfx, nRightBearingVfx;
	gint nWidthVfx, nAscentVfx, nDescentVfx;
#endif // D_GTK

#ifdef D_MAC
	// �ե���ȤΥ�������
	void *pStyle;
	void *pStyleVfx;
#endif // D_MAC

#ifdef D_IPHONE
	// �ե���ȤΥ�������
	void *pStyle;
	void *pStyleVfx;
#endif // D_IPHONE

#ifdef D_MFC
	// �ե���ȤΥ�������
	void *pStyle;
	void *pStyleVfx;

	LOGFONT mTextFontDesc;
	CFont *pTextFont;
	CClientDC *pDc;

	LOGFONT mTextFontDescVfx;
	CFont *pTextFontVfx;
	CClientDC *pDcVfx;

	CDir3dText mD3Vfx;
#endif // D_MFC

	// ��������˥ޥåפ������褹�뤫?
	bool bFlgEnaDrawTurn;
	// ���̹����׵�ե饰
	bool bFlgUpdateRequest;
	bool bFlgUpdateRequestIPhone;

public:
	PcgDun();
	~PcgDun();

	void initTitle();
	void initLastBoss();
	void initGameOver();
	void initEnding();
	void init( GraphConf *cnf );
	void reset();
	void reloadAllMbr();
	bool reloadMbr( long nLsMbrN, WSCstring path );

	long getTileSizeX( bool flgText = false );
	long getTileSizeY( bool flgText = false );

	WSDmwindowDev *getWBuf();

	void scrollTileRel( long mapDX, long mapDY );
	void scrollTile( long mapX, long mapY );
	void scrollMap( long x, long y );
	bool chkScroll( long x, long y, long w, long h );
	bool drawScroll( long x, long y, long w, long h );

	long getScrollBarX();
	long getScrollBarY();
	long getScrollBarW();
	long getScrollBarH();
	long getScrollBarMaxX();
	long getScrollBarMaxY();
	void setScrollBarX( long x );
	void setScrollBarY( long y );

	bool clipWin( long mapX, long mapY );
	bool clipWinX( long mapX );
	bool clipWinY( long mapY );

	void redraw( bool flgForce = false );
	bool draw(
		long mapX, long mapY,
		long mapW, long mapH,
		bool flgForce = false
	);
	void drawTurn( bool flgForce = false );
	bool drawUpdate( long mapX, long mapY, long mapW, long mapH );
	void flush( long mapX, long mapY, long mapW, long mapH );
	bool drawString( long scrn_x, long scrn_y, const char *s, ... );
	bool drawVfx(
		long scrn_x, long scrn_y,
		long scrn_w, long scrn_h,
		bool flgForce );
	void setXxAttack( xx_act_kind_t kind, void *p );

	void setFlgUpdateRequest( bool flg );
	bool getFlgUpdateRequest();
	void setFlgUpdateRequestIPhone( bool flg );
	bool getFlgUpdateRequestIPhone();

	bool drawTitle();
	bool drawLastBoss();
	bool drawGameOver();
	bool drawEnding();

	void drawFade(
		long mapX, long mapY, long mapW, long mapH,
		long r, long g, long b, long a
	);

	Pcg *getChrPcg( chr_t *chr );
	long getChrDrawLeft( chr_t *chr, Pcg *pPcg, bool flagPre );
	long getChrDrawRight( chr_t *chr, Pcg *pPcg, bool flagPre );
	long getChrDrawTop( chr_t *chr, Pcg *pPcg, bool flagPre );
	long getChrDrawBottom( chr_t *chr, Pcg *pPcg, bool flagPre );
	long getObjDrawLeft( long mapX, Pcg *pPcg );
	long getObjDrawRight( long mapX, Pcg *pPcg );
	long getObjDrawWidth( long mapX, Pcg *pPcg );
	long getObjDrawTop( long mapY, Pcg *pPcg );
	long getObjDrawBottom( long mapY, Pcg *pPcg );
	long getObjDrawHeight( long mapY, Pcg *pPcg );

	Pcg *getCrsr( long mapX, long mapY, bool flagSub );
	long getCrsrWidth( bool flagSub );
	long getCrsrHeight( bool flagSub );

	PcgTab *getPcgTabMbr();

	void drawRectangle(
		long x, long y, long w, long h,
		long r, long g, long b
	);

private:
/*
	void initTitle();
	void initLastBoss();
	void initGameOver();
	void initEnding();
	void init( GraphConf *cnf );
*/
	void initPcgLsRandm( GraphConf *cnf, Pcg *ls, PcgTab tab[] );
	void initGraphConf( GraphConf *cnf );
/*
	void reset();
	void reloadAllMbr();
	bool reloadMbr( long nLsMbrN, WSCstring path );
*/
	void resetSignboardFont();
	bool setSignboardFont( long pnt, WSCstring *pFontName );
/*
	long getTileSizeX( bool flgText = false );
	long getTileSizeY( bool flgText = false );
*/
	long getTextModePoint();
	void resetMap();
/*
	WSDmwindowDev *getWBuf();
*/
	WSDmwindowDev *ReNewWBuf();
/*
	void scrollTileRel( long mapDX, long mapDY );
	void scrollTile( long mapX, long mapY );
	void scrollMap( long x, long y );
	bool chkScroll( long x, long y, long w, long h );
	bool drawScroll( long x, long y, long w, long h );
*/
#ifdef D_MFC
	void getScrollInfo( SCROLLINFO *info, int sb );
	void setScrollInfoPos( int sb, int pos );
#endif // D_MFC
/*
	long getScrollBarX();
	long getScrollBarY();
	long getScrollBarW();
	long getScrollBarH();
	long getScrollBarMaxX();
	long getScrollBarMaxY();
	void setScrollBarX( long x );
	void setScrollBarY( long y );
	bool clipWin( long mapX, long mapY );
	bool clipWinX( long mapX );
	bool clipWinY( long mapY );
	void redraw( bool flgForce = false );
	bool draw(
		long mapX, long mapY,
		long mapW, long mapH,
		bool flgForce = false
	);
	void drawTurn( bool flgForce = false );
*/
	void drawTurnSub();
	void drawTurnFlush();
/*
	bool drawUpdate( long mapX, long mapY, long mapW, long mapH );
*/
	bool drawSub(
		long mapX, long mapY, long mapW, long mapH,
		bool flgUpdateAll = false
	);
	/*
	void flush( long mapX, long mapY, long mapW, long mapH );
*/
	void initText();
	bool drawText( long mapX, long mapY, long mapW, long mapH );
/*
	bool drawString( long scrn_x, long scrn_y, const char *s, ... );
*/
	void initVfx();
/*
	bool drawVfx(
		long scrn_x, long scrn_y,
		long scrn_w, long scrn_h,
		bool flgForce );
	void setXxAttack( xx_act_kind_t kind, void *p );
*/
#ifdef D_GTK
	bool user_select_font( GdkFont **font );
#endif // D_GTK
/*
	void setFlgUpdateRequest( bool flg );
	bool getFlgUpdateRequest();
	void setFlgUpdateRequestIPhone( bool flg );
	bool getFlgUpdateRequestIPhone();
*/
	void resetUpdateFlg();
	void setUpdateFlgRange(
		long mapX, long mapY,
		long mapW, long mapH,
		bool flg
	);
	void setUpdateFlg( long mapX, long mapY, bool flg );
	bool getUpdateFlg( long mapX, long mapY );
/*
	bool drawTitle();
	bool drawLastBoss();
	bool drawGameOver();
	bool drawEnding();
*/
	bool drawTile( long mapX, long mapY, bool flgFlush );
	bool drawObj( long mapX, long mapY );
	bool drawItemAll( long mapX, long mapY );
	bool drawNull( long mapX, long mapY );
	bool drawFloor( long mapX, long mapY );
	bool drawHole( long mapX, long mapY );
	bool drawObjFix( long mapX, long mapY, Pcg *lsTown, Pcg *lsDun );
	Pcg *srchPcgLsMap(
		long mapX, long mapY,
		Pcg *lsTown, Pcg *lsDun
	);
	Pcg *srchPcgLsMapLast(
		long mapX, long mapY,
		Pcg *lsXX, Pcg *lsBone
	);
	bool drawWall( long mapX, long mapY );
	bool drawWallTypeTile( long mapX, long mapY );
	bool drawWallTypeA( long mapX, long mapY );
	bool drawWallTypeB( long mapX, long mapY );
	bool drawWallTypeBRoof( long mapX, long mapY );
	bool drawWallTypeBCommon(
		long mapX, long mapY,
		long idxX, long idxY,
		bool flagHalfX, bool flagHalfY
	);
	bool drawStatue( long mapX, long mapY );
	bool drawBootUnit( long mapX, long mapY );
	bool drawStreetlamp( long mapX, long mapY );
	bool drawSignboard( long mapX, long mapY );
	bool drawWater( long mapX, long mapY );
	bool drawStairsUp( long mapX, long mapY );
	bool drawStairsDown( long mapX, long mapY );
	bool drawDoorClose( long mapX, long mapY );
	bool drawDoorOpen( long mapX, long mapY );
	bool drawDoorIdx( long mapX, long mapY, bool flagOpen );
	bool drawWindowClose( long mapX, long mapY );
	bool drawWindowOpen( long mapX, long mapY );
	bool drawTrap( long mapX, long mapY );
	Pcg *srchPcgLsFace( char mjr, char mnr, Pcg *lsTown, Pcg *lsDun );
	bool drawTrapSanctuary( long mapX, long mapY, trap_t *trap, Pcg *p );
	bool drawCrsrAll( long mapX, long mapY );
	bool drawCrsr( long mapX, long mapY );
	bool drawCrsrSub( long mapX, long mapY );
	bool drawCrsrOffset( long mapX, long mapY, bool flagSub );
	bool drawSquareParty( long mapX, long mapY );
	bool drawSquareMbrAll( long mapX, long mapY );
	bool drawSquareMbr( long mapX, long mapY, long nMbr );
	Pcg *srchPcgLsSquareParty();
	bool drawItem( long mapX, long mapY, char mjr, char mnr );
	void drawChrListAll( long x, long y, long w, long h );
	bool drawChrList( long mapX, long mapY, bool flagOneTile );
	bool drawChr(
		long mapX, long mapY,
		chr_t *chr, Pcg *pPcg,
		bool flagOneTile
	);
	bool drawGuiVfx( long mapX, long mapY );
	bool drawGuiVfxBash( long mapX, long mapY, gui_vfx_t *vfx, Pcg *p );
	bool drawGuiVfxArw( long mapX, long mapY, gui_vfx_t *vfx, Pcg *p );
	bool drawGuiVfxCommon(
		long mapX, long mapY, gui_vfx_t *vfx, Pcg *p
	);
	Pcg *srchPcgLsNinja( spell_kind_t kind, Pcg *ls );
	bool drawGuiVfxNinja(
		long mapX, long mapY, gui_vfx_t *vfx, Pcg *p
	);
	void drawNight( long mapX, long mapY, long mapW, long mapH );
	void drawGameOverFade( long mapX, long mapY, long mapW, long mapH );
/*
	void drawFade(
		long mapX, long mapY, long mapW, long mapH,
		long r, long g, long b, long a
	);
*/
	bool getGlowColor( long *r, long *g, long *b, long *a );
/*
	Pcg *getChrPcg( chr_t *chr );
	long getChrDrawLeft( chr_t *chr, Pcg *pPcg, bool flagPre );
	long getChrDrawRight( chr_t *chr, Pcg *pPcg, bool flagPre );
	long getChrDrawTop( chr_t *chr, Pcg *pPcg, bool flagPre );
	long getChrDrawBottom( chr_t *chr, Pcg *pPcg, bool flagPre );
	long getObjDrawLeft( long mapX, Pcg *pPcg );
	long getObjDrawRight( long mapX, Pcg *pPcg );
	long getObjDrawWidth( long mapX, Pcg *pPcg );
	long getObjDrawTop( long mapY, Pcg *pPcg );
	long getObjDrawBottom( long mapY, Pcg *pPcg );
	long getObjDrawHeight( long mapY, Pcg *pPcg );
*/
	bool chkDrawWall( long mapX, long mapY );
	bool chkDrawStatue( long mapX, long mapY );
	bool chkDrawBootUnit( long mapX, long mapY );
	bool chkDrawStreetlamp( long mapX, long mapY );
	bool chkDrawSignboard( long mapX, long mapY );
	bool chkDrawSanctuary( long mapX, long mapY, trap_t *trap );
/*
	Pcg *getCrsr( long mapX, long mapY, bool flagSub );
	long getCrsrWidth( bool flagSub );
	long getCrsrHeight( bool flagSub );
*/
	bool chkDrawCrsr( long mapX, long mapY );
	bool chkDrawCrsrSub( long mapX, long mapY );
	bool chkDrawCrsrCommon( long mapX, long mapY, bool flagSub );
	bool chkDrawSquareParty( long mapX, long mapY );
	bool chkDrawSquareMbr( long mapX, long mapY, long nMbr );
	bool chkDrawChr( long mapX, long mapY, chr_t *chr );
	long getWidthChr( chr_t *chr, Pcg *pPcg );
	long getHeightChr( chr_t *chr, Pcg *pPcg );
/*
	PcgTab *getPcgTabMbr();
*/
};

#endif /* PCG_DUN_H */
