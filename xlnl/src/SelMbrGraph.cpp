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
* $Id: SelMbrGraph.cpp,v 1.11 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// メンバーのグラフィック・パターンを選択
////////////////////////////////////////////////////////////////

#include	"gmain.h"
#include	"misc.h"
//#include	"turn.h"
//#include	"dun.h"
//#include	"town.h"
//#include	"item.h"
//#include	"spell.h"
//#include	"chr.h"
//#include	"party.h"
//#include	"mnstr.h"
//#include	"pet.h"
//#include	"fight.h"
//#include	"fx.h"
//#include	"trap.h"
//#include	"draw.h"
//#include	"curs.h"
//#include	"menu.h"
//#include	"amenu.h"
//#include	"request.h"
//#include	"gfile.h"
//#include	"msg.h"
//#include	"ver.h"
//#include	"gmain-prot.h"
#include	"misc-prot.h"
//#include	"turn-prot.h"
//#include	"dun-prot.h"
//#include	"town-prot.h"
//#include	"item-prot.h"
//#include	"spell-prot.h"
//#include	"chr-prot.h"
//#include	"party-prot.h"
//#include	"mnstr-prot.h"
//#include	"pet-prot.h"
//#include	"fight-prot.h"
//#include	"fx-prot.h"
//#include	"trap-prot.h"
//#include	"draw-prot.h"
//#include	"curs-prot.h"
//#include	"menu-prot.h"
//#include	"mmenu-prot.h"
//#include	"imenu-prot.h"
//#include	"tmenu-prot.h"
//#include	"amenu-prot.h"
//#include	"request-prot.h"
//#include	"gfile-prot.h"
//#include	"msg-prot.h"

#include	"scene.h"
#include	"scene-prot.h"

#include "PcgDun.h"
#include "FileList.h"
#include "GlobalVar.h"

#ifdef D_WS
# include <WSCform.h>
# include <WSCvscrBar.h>
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
# include <gdk-pixbuf/gdk-pixbuf.h>
#endif // D_GTK

#ifdef D_MFC
# include "xlnl-dows/xlnl-dows.h"
# include "xlnl-dows/MainFrm.h"
#endif // D_GTK

#ifdef D_WS
extern WSCform *MapForm;
extern WSCvscrBar *MapScrollX;
extern WSCvscrBar *MapScrollY;
#endif // D_WS

////////////////////////////////////////////////////////////////

#define NAME_FONT_POINT	32
#define NAME_FONT_DOT	32

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

SelMbrGraph::SelMbrGraph()
{
	pMbr = NULL;

	pPtnHead = NULL;
	nPtnMaxN = 0;
	nPtnSelN = -1;

	nPreScene = SCENE_N_NULL;
	nPreMapX = -1;
	nPreMapY = -1;

	nSizeX = 32;
	nSizeY = 32;
	nSizeMaxX = 32;
	nSizeMaxY = 32;

#ifdef D_GTK
	font = NULL;
#endif // D_GTK
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

SelMbrGraph::~SelMbrGraph()
{
	if( nPreScene != SCENE_N_NULL )
		change_scene_gui( nPreScene );

	if( nPreMapX > -1 )
		gPcgDun.setScrollBarX( nPreMapX );
	if( nPreMapY > -1 )
		gPcgDun.setScrollBarY( nPreMapY );
}

////////////////////////////////////////////////////////////////
// 選択開始
// mbr_t *mbr : メンバー
// return : 選択開始できたか?
////////////////////////////////////////////////////////////////

bool SelMbrGraph::exec( mbr_t *mbr )
{
	if( mbr == NULL )
		return false;
	if( pMbr != NULL )
		return false;
	if( gPcgDun.pGraphConf == NULL )
		return false;

	PcgTab *tab = gPcgDun.getPcgTabMbr();
	if( tab == NULL )
		return false;

	pMbr = mbr;
	nPtnSelN = -1;
	WSCstring sSelName = pMbr->graph_name;

	// パターンの表示サイズを設定

	nSizeX = gPcgDun.getTileSizeX( false ) * 3;
	nSizeY = gPcgDun.getTileSizeY( false ) * 3 + 16;
	nSizeMaxX = gPcgDun.getScrollBarMaxX()
			+ gPcgDun.getScrollBarW();
	nSizeMaxY = gPcgDun.getScrollBarMaxY()
			+ gPcgDun.getScrollBarH();

	// スクロール・バーを設定

	nPreMapX = gPcgDun.getScrollBarX();
	nPreMapY = gPcgDun.getScrollBarY();
	gPcgDun.setScrollBarX( 0 );
	gPcgDun.setScrollBarY( 0 );

	// シーンを設定

	nPreScene = get_scene();
	change_scene_gui( SCENE_N_SEL_MBR_GRAPH );

	// パターン検索を設定

	WSCstring path = gPcgDun.pGraphConf->getDir();
	long w = path.getWords( "/" );
	WSCstring dir = path.getWord( w - 1, "/" );

	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList ls;
	ls.reset( tab->sDir, ext );

	// パターンをリストに登録

	Pcg *pre = NULL;
	pPtnHead = NULL;
	long i;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		// 検索

		WSCstring file = ls.next();
		if( file.getChars() <= 0 )
			break;

		// メモリーを割り当て

		Pcg *p;
		p = new Pcg;
		if( p == NULL )
			break;

		if( pre == NULL )
			pPtnHead = p;
		else
			pre->next = p;
		pre = p;

		// 読み込む

		p->init( file );

		WSCstring name = FileList::getFileName( file );
		if( name == sSelName )
			nPtnSelN = i;
	}
	nPtnMaxN = i;

	if( pre == NULL )
		pPtnHead = NULL;
	else
		pre->next = NULL;

	redraw();

	return true;
}

////////////////////////////////////////////////////////////////
// パターンを選択
// long sx : クリックした X 座標
// long sy : クリックした Y 座標
////////////////////////////////////////////////////////////////

long SelMbrGraph::sel( long sx, long sy )
{
	long x = gPcgDun.getScrollBarX() + sx;
	long y = gPcgDun.getScrollBarY() + sy;

	long xn = nSizeMaxX / nSizeX;
	long idx = (y / nSizeY) * xn;
	idx += x / nSizeX;

	if( x >= (xn * nSizeX) )
		return -1;
	if( idx < 0 )
		return -1;
	if( idx >= nPtnMaxN )
		return -1;

	nPtnSelN = idx;

	redraw();

	return nPtnSelN;
}

////////////////////////////////////////////////////////////////
// パターン選択を決定
////////////////////////////////////////////////////////////////

void SelMbrGraph::ok()
{
	if( nPtnSelN < 0 )
		nPtnSelN = -1;
	if( nPtnSelN >= nPtnMaxN )
		nPtnSelN = -1;

	Pcg *p = pPtnHead;
	for( long i = 0; i < nPtnSelN; i++ ){
		if( p == NULL )
			break;

		p = p->next;
	}

	do {
		if( p == NULL )
			break;
		if( pMbr == NULL )
			break;

		WSCstring name = p->getName();
		if( name.getChars() <= 0 )
			break;

		str_nz_cpy( pMbr->graph_name,
				(const char *)name,
				FILE_NAME_MAX_LEN );
		gPcgDun.reloadMbr( pMbr->ls_mbr_n, p->getPath() );
	} while( 0 );

	close();
}

////////////////////////////////////////////////////////////////
// パターン選択をキャンセル
////////////////////////////////////////////////////////////////

void SelMbrGraph::cancel()
{
	close();
}

////////////////////////////////////////////////////////////////
// パターン選択を終了
////////////////////////////////////////////////////////////////

void SelMbrGraph::close()
{
	if( nPreScene != SCENE_N_NULL )
		change_scene_gui( nPreScene );
	nPreScene = SCENE_N_NULL;

	gPcgDun.redraw();
	gKey.setChar( '0' );
}

////////////////////////////////////////////////////////////////
// 全パターンを再描画
////////////////////////////////////////////////////////////////

void SelMbrGraph::redraw()
{
#ifdef D_MFC
	g_Dir3d.SetRefreshRequest( true );
	gPcgDun.setFlgUpdateRequest( true );
#endif // D_MFC

	// スクロール・バーを設定
	if( nPreMapX <= -1 ){
		nPreMapX = gPcgDun.getScrollBarX();
		gPcgDun.setScrollBarX( 0 );
	}
	if( nPreMapY <= -1 ){
		nPreMapY = gPcgDun.getScrollBarY();
		gPcgDun.setScrollBarY( 0 );
	}

	long scrnW = gPcgDun.getScrollBarMaxX() + gPcgDun.getScrollBarW();
	long scrnH = gPcgDun.getScrollBarMaxY() + gPcgDun.getScrollBarH();
	gPcgDun.drawRectangle(
			0, 0, scrnW, scrnH,
			nBaseColorR, nBaseColorG, nBaseColorB );

	drawAllChr();
	flush();
}

////////////////////////////////////////////////////////////////
// 全パターンを描画
////////////////////////////////////////////////////////////////

void SelMbrGraph::draw()
{
#ifdef D_GTK
	drawAllChr();
	flush();
#endif // D_GTK

#ifdef D_MFC
	redraw();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 全キャラクタを描画
////////////////////////////////////////////////////////////////

void SelMbrGraph::drawAllChr()
{
	long x = 0;
	long y = 0;
	Pcg *p = pPtnHead;
	for( long i = 0; i < nPtnMaxN; i++ ){
		if( p == NULL )
			break;

		bool flagSel = true;
		if( i == nPtnSelN )
			flagSel = true;
		else
			flagSel = false;

		drawChr( x, y, nSizeX, nSizeY, p, flagSel );

		x += nSizeX;
		if( (x + nSizeX) > nSizeMaxX ){
			x = 0;
			y += nSizeY;
			if( y >= nSizeMaxY )
				break;
		}

		p = p->next;
	}
}

////////////////////////////////////////////////////////////////
// キャラクタを描画
// long x : X 座標
// long y : Y 座標
// long w : 幅
// long h : 高さ
// Pcg *p : パターン
////////////////////////////////////////////////////////////////

void SelMbrGraph::drawChr(
	long x, long y, long w, long h,
	Pcg *p, bool flagSel )
{
	if( p == NULL )
		return;

	long bgnX = gPcgDun.getScrollBarX();
	long bgnY = gPcgDun.getScrollBarY();
	long endX = gPcgDun.getScrollBarX() + gPcgDun.getScrollBarW();
	long endY = gPcgDun.getScrollBarY() + gPcgDun.getScrollBarH();

	if( (x + w) < bgnX )
		return;
	if( (y + h) < bgnY )
		return;
	if( x > endX )
		return;
	if( y > endY )
		return;

	long ptnW = p->getWidth() / gPcgDun.nPtnDirMbr;
	long ptnH = p->getHeight() / gPcgDun.nPtnDirMbr;
	long xx = x + ((w - ptnW) / 2);
	long yy = y + h - ptnH - nSelBorderH;

	long hr, hg, hb;
	long lr, lg, lb;
	if( flagSel ){
		hr = nLowColorR;
		hg = nLowColorG;
		hb = nLowColorB;

		lr = nHighColorR;
		lg = nHighColorG;
		lb = nHighColorB;
	} else {
		hr = nHighColorR;
		hg = nHighColorG;
		hb = nHighColorB;

		lr = nLowColorR;
		lg = nLowColorG;
		lb = nLowColorB;
	}

	if( flagSel ){
		gPcgDun.drawRectangle(
				x + nSelBorderW,
				y + nSelBorderH,
				w - (nSelBorderW * 2),
				h - (nSelBorderH * 2),
				nSelColorR, nSelColorG, nSelColorB );
	}

	// 光の縁取り

	gPcgDun.drawRectangle(
			x, y,
			w, nSelBorderH,
			hr, hg, hb );
	gPcgDun.drawRectangle(
			x, y,
			nSelBorderW, h,
			hr, hg, hb );

	// 影の縁取り

	gPcgDun.drawRectangle(
			x, y + h - nSelBorderH,
			w, nSelBorderH,
			lr, lg, lb );
	gPcgDun.drawRectangle(
			x + w - nSelBorderW, y,
			nSelBorderW, h,
			lr, lg, lb );

	p->drawOffset( gPcgDun.getWBuf(),
			xx, yy, ptnW, ptnH, 0, 0 );
}

////////////////////////////////////////////////////////////////
// 描画のフラッシュ
////////////////////////////////////////////////////////////////

void SelMbrGraph::flush()
{
	long tileSizeX = gPcgDun.getTileSizeX( false );
	long tileSizeY = gPcgDun.getTileSizeY( false );
	long mapX = gPcgDun.getScrollBarX() / tileSizeX;
	long mapY = gPcgDun.getScrollBarY() / tileSizeY;
	long mapW = (gPcgDun.getScrollBarW() + tileSizeX) / tileSizeX;
	long mapH = (gPcgDun.getScrollBarH() + tileSizeY) / tileSizeY;

	gPcgDun.flush( mapX, mapY, mapW, mapH );
}
