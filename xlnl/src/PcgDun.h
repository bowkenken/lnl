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
* $Id: PcgDun.h,v 1.88 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef PCG_DUN_H
#define PCG_DUN_H	1

////////////////////////////////////////////////////////////////
// ダンジョンの描画管理
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

// デフォルトのディレクトリ
#define STR_DEFAULT_GRAPH_DIR_NAME	"xlnl-" VERSION "/"
// 共通ディレクトリ
#define STR_FIX_GRAPH_DIR_NAME	".xlnl/"

// パターンのファイル名の拡張子
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

// パターンのテーブル
struct PcgTab {
	// モンスターの場合の種類
	long	nKind;
	// 顏文字
	char mjr, mnr;
	// パターンの使われる割合
	ratio_t nRatio;

	// パターンのファイルのあるディレクトリ
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

	// パターンの拡大率
	rate_t nTileSizeRate;

	// キャラクタの向いている方向のパターン数
	NPtnDirChr nPtnDirMbr;
	NPtnDirChr nPtnDirMnstr;

private:
	//// タイル・モード ////

	// パターンの基準サイズ
	long nTileSizeX, nTileSizeY;

	// 空白のパターンのリスト
	Pcg pcgNullTown;
	Pcg pcgNullDun;
	// 床のパターンのリスト
	Pcg pcgFloorTown;
	Pcg pcgFloorDun;
	Pcg pcgFloorLast;
	// 奈落のパターンのリスト
	Pcg pcgHole;
	// 壁のパターンのリスト
	Pcg pcgWallTown;
	Pcg pcgWallDun;
	Pcg pcgWallLast;
	Pcg pcgStatue;
	Pcg pcgBootUnit;
	// 街灯のパターンのリスト
	Pcg pcgStreetlampOn;
	Pcg pcgStreetlampOff;
	// 看板のパターンのリスト
	Pcg pcgSignboard;
	// 水のパターンのリスト
	// 溶岩のパターンのリスト
	Pcg pcgLava;
	// 階段のパターンのリスト
	Pcg pcgStairsUpTown;
	Pcg pcgStairsUpDun;
	Pcg pcgStairsDownTown;
	Pcg pcgStairsDownDun;
	Pcg pcgStairsLastBoss;
	// ドアのパターンのリスト
	Pcg pcgDoorCloseTown;
	Pcg pcgDoorCloseDun;
	Pcg pcgDoorOpenTown;
	Pcg pcgDoorOpenDun;
	// 窓のパターンのリスト
	Pcg pcgWindowClose;
	Pcg pcgWindowOpen;

	// カーソルのパターンのリスト
	Pcg *aPcgCrsr[ATTITUDE_MAX_N];
	Pcg *aPcgCrsrSub[ATTITUDE_MAX_N];
	// アンカーのパターンのリスト
	Pcg pcgSquareParty;
	Pcg pcgSquareMbr;

	// アイテムのパターンのリスト
	Pcg pcgItem;
	// 罠のパターンのリスト
	Pcg pcgTrap;

	// メンバーのパターンのリスト
	Pcg *aPcgMbr[LS_MBR_MAX_N];
	// モンスターのパターンのリスト
	Pcg *aPcgMnstr[MNSTR_KIND_MAX_N];

	// 攻撃の VFX のパターンのリスト
	Pcg pcgGuiVfxBash;
	// クリティカル攻撃の VFX のパターンのリスト
	Pcg pcgGuiVfxBashCrtcl;
	// 矢の VFX のパターンのリスト
	Pcg pcgGuiVfxArw;
	// 呪文の VFX のパターンのリスト
	Pcg *aPcgGuiVfxSpell[RESI_KIND_MAX_N];
	// 爆風の VFX のパターンのリスト
	Pcg *aPcgGuiVfxBlast[BLAST_KIND_MAX_N];
	// 忍術の VFX のパターンのリスト
	Pcg pcgGuiVfxNinja;

	// ラスボス
	GuiLastBoss lastBossXX;

	// パターンのバリエーションの種類のマップ
	rate_t rateMap[MAP_MAX_Y][MAP_MAX_X];

	// 壁のパターン・タイプ
	WallPtnType nWallPtnTypeTown;
	WallPtnType nWallPtnTypeDun;
	WallPtnType nWallPtnTypeLast;

	// 水のアニメ・フレーム
	long nWaterAnimeN;

	// 再描画する必要があるキャラクタのマップ
	bool bFlgUpdate[MAP_MAX_Y][MAP_MAX_X];

	// ダブル・バッファ
	WSDmwindowDev *pWBuf;

	//// 看板のフォント ////

	// フォントのポイント
	long nSignboardPoint;

	// フォントの基準サイズ
	long nSignboardSizeX, nSignboardSizeY;

	// 文字間隔
	long nSignboardIntervalWidth, nSignboardIntervalHeight;

#ifdef D_GTK
	// フォントのスタイル
	GtkStyle *pSignboardStyle;

	// フォントのサイズ
	gint nSignboardLeftBearing, nSignboardRightBearing;
	gint nSignboardWidth, nSignboardAscent, nSignboardDescent;
#endif // D_GTK

#ifdef D_MAC
	// フォントのスタイル
	void *pSignboardStyle;
#endif // D_MAC

#ifdef D_IPHONE
	// フォントのスタイル
	void *pSignboardStyle;
#endif // D_IPHONE

#ifdef D_MFC
	// フォントのスタイル
	void *pSignboardStyle;
	LOGFONT mSignboardFontDesc;
	CFont *pSignboardFont;

	CDir3dText mD3Signboard;
#endif // D_MFC

	//// テキスト・モード ////

	// フォントのデフォルトのポイント
	long nTextModeDefaultPoint;

	// フォントの基準サイズ
	long nTextSizeX, nTextSizeY;

	// 文字間隔
	long nIntervalWidth, nIntervalHeight;

#ifdef D_GTK
	// フォントのスタイル
	GtkStyle *pStyle;
	GtkStyle *pStyleVfx;

	// フォントのサイズ
	gint nLeftBearing, nRightBearing;
	gint nWidth, nAscent, nDescent;
	gint nLeftBearingVfx, nRightBearingVfx;
	gint nWidthVfx, nAscentVfx, nDescentVfx;
#endif // D_GTK

#ifdef D_MAC
	// フォントのスタイル
	void *pStyle;
	void *pStyleVfx;
#endif // D_MAC

#ifdef D_IPHONE
	// フォントのスタイル
	void *pStyle;
	void *pStyleVfx;
#endif // D_IPHONE

#ifdef D_MFC
	// フォントのスタイル
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

	// ターン毎にマップを全描画するか?
	bool bFlgEnaDrawTurn;
	// 画面更新要求フラグ
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
