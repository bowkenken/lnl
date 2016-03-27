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
* $Id: SelMbrGraph.cpp,v 1.11 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ���С��Υ���ե��å����ѥ����������
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
// ���󥹥ȥ饯��
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
// �ǥ��ȥ饯��
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
// ���򳫻�
// mbr_t *mbr : ���С�
// return : ���򳫻ϤǤ�����?
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

	// �ѥ������ɽ��������������

	nSizeX = gPcgDun.getTileSizeX( false ) * 3;
	nSizeY = gPcgDun.getTileSizeY( false ) * 3 + 16;
	nSizeMaxX = gPcgDun.getScrollBarMaxX()
			+ gPcgDun.getScrollBarW();
	nSizeMaxY = gPcgDun.getScrollBarMaxY()
			+ gPcgDun.getScrollBarH();

	// �������롦�С�������

	nPreMapX = gPcgDun.getScrollBarX();
	nPreMapY = gPcgDun.getScrollBarY();
	gPcgDun.setScrollBarX( 0 );
	gPcgDun.setScrollBarY( 0 );

	// �����������

	nPreScene = get_scene();
	change_scene_gui( SCENE_N_SEL_MBR_GRAPH );

	// �ѥ����󸡺�������

	WSCstring path = gPcgDun.pGraphConf->getDir();
	long w = path.getWords( "/" );
	WSCstring dir = path.getWord( w - 1, "/" );

	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList ls;
	ls.reset( tab->sDir, ext );

	// �ѥ������ꥹ�Ȥ���Ͽ

	Pcg *pre = NULL;
	pPtnHead = NULL;
	long i;
	for( i = 0; i < LOOP_MAX_1000; i++ ){
		// ����

		WSCstring file = ls.next();
		if( file.getChars() <= 0 )
			break;

		// ���꡼��������

		Pcg *p;
		p = new Pcg;
		if( p == NULL )
			break;

		if( pre == NULL )
			pPtnHead = p;
		else
			pre->next = p;
		pre = p;

		// �ɤ߹���

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
// �ѥ����������
// long sx : ����å����� X ��ɸ
// long sy : ����å����� Y ��ɸ
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
// �ѥ�������������
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
// �ѥ���������򥭥�󥻥�
////////////////////////////////////////////////////////////////

void SelMbrGraph::cancel()
{
	close();
}

////////////////////////////////////////////////////////////////
// �ѥ����������λ
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
// ���ѥ�����������
////////////////////////////////////////////////////////////////

void SelMbrGraph::redraw()
{
#ifdef D_MFC
	g_Dir3d.SetRefreshRequest( true );
	gPcgDun.setFlgUpdateRequest( true );
#endif // D_MFC

	// �������롦�С�������
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
// ���ѥ����������
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
// ������饯��������
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
// ����饯��������
// long x : X ��ɸ
// long y : Y ��ɸ
// long w : ��
// long h : �⤵
// Pcg *p : �ѥ�����
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

	// ���α���

	gPcgDun.drawRectangle(
			x, y,
			w, nSelBorderH,
			hr, hg, hb );
	gPcgDun.drawRectangle(
			x, y,
			nSelBorderW, h,
			hr, hg, hb );

	// �Ƥα���

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
// ����Υե�å���
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
