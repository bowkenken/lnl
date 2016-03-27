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
* $Id: DemoSpace.cpp,v 1.22 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ����ǥ�
////////////////////////////////////////////////////////////////

#define DEMO_SPACE_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// ����
////////////////////////////////////////////////////////////////

// ������طʲ����Υǥ��쥯�ȥ�
#define STR_ENDING_SPACE_DIR_NAME	"ending/space/"
#define STR_ENDING_NEBULA_DIR_NAME	"ending/nebula/"

static const long XR = 16300;
static const long YR = 16300;
static const long ZR = 250;
static const long NXR = 1020;
static const long NYR = 1020;
static const long NZR = 120;
static const long Z_SPEED = -1;

////////////////////////////////////////////////////////////////
// �����åա�����
////////////////////////////////////////////////////////////////

#define STAFF_ROLL_SPEED_CUI	2
#define STAFF_ROLL_SPEED	1

#define SPACE_FONT_POINT	14
#define SPACE_FONT_DOT	14

// ʸ���ֳ�
static const long nStaffRollIntervalWidth = SPACE_FONT_DOT;
static const long nStaffRollIntervalHeight = SPACE_FONT_DOT * 2;

#define gStrStaffRoll	g_str_staff_roll
#define gStrTheEnd	g_str_the_end

////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

DemoSpace::DemoSpace()
{
	pcgNebula.next = NULL;

	pStyle = NULL;

#ifdef D_MFC
	for( long i = 0; i < COLOR_TAB_MAX_N; i++ ){
		texture[i] = NULL;
		img[i] = NULL;
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

DemoSpace::~DemoSpace()
{
}

////////////////////////////////////////////////////////////////
// �����
////////////////////////////////////////////////////////////////

void DemoSpace::init()
{
	g_gui_star_n = GUI_STAR_DFLT_N;

	// ������طʲ����θ���������

	WSCstring dir = STR_DEFAULT_GRAPH_DIR_NAME;
	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList ls;

	// ������طʲ����򸡺�

	nMaxFile = 0;
	ls.reset( STR_ENDING_SPACE_DIR_NAME, ext );
	long j = 0;
	for( j = 0; j < LOOP_MAX_1000; j++ ){
		WSCstring path = ls.next();
		if( path.getChars() <= 0 )
			break;
	}
	nMaxFile = j;

	// ������طʲ���������������

	if( nMaxFile > 0 )
		nRandmSel = randm( nMaxFile );
	else
		nRandmSel = -1;

	// ������طʲ������ɤ߹���

	if( nRandmSel > -1 ){
		ls.reset( STR_ENDING_SPACE_DIR_NAME, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
			if( j == nRandmSel ){
				pcgSpace.init( path );
				break;
			}
		}
	}

#ifdef D_MFC
	// �����β����򸡺������ɤ߹���

	Pcg *p = &pcgNebula;
	ls.reset( STR_ENDING_NEBULA_DIR_NAME, ext );
	for( long i = 0; i < NEBULA_MAX_N; i++ ){
		WSCstring path = ls.next();
		if( path.getChars() <= 0 )
			break;
		p->next = new Pcg;
		p = p->next;
		p->next = NULL;
		p->init( path );
	}
#endif // D_MFC

	// �����åա�����

#ifdef	D_MFC
	staffRollY = -gPcgDun.getScrollBarH() * 10 / 16;
#else
	staffRollY = -gPcgDun.getScrollBarH();
#endif

	nStaffRollMaxLen = 1;
	for( long i = 0; i < LOOP_MAX_1000; i++ ){
		if( gStrStaffRoll[i] == NULL )
			break;
		if( gStrStaffRoll[i][0] == '\0' )
			break;

		long len = str_len_draw( gStrStaffRoll[i] );
		if( nStaffRollMaxLen < len )
			nStaffRollMaxLen = len;
	}

#ifdef D_GTK
	// �ǥե���ȤΥ������������

	if( pStyle == NULL ){
		pStyle = gtk_style_copy(
				gtk_widget_get_default_style() );
	}
	if( pStyle->fg_gc[GTK_STATE_NORMAL] == NULL ){
		pStyle->fg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}
	if( pStyle->bg_gc[GTK_STATE_NORMAL] == NULL ){
		pStyle->bg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}

	// �ե���Ȥ�����

	WSCstring sFontPoint = SPACE_FONT_POINT * 10;
	WSCstring sFontName = "";
	sFontName += "-*-*-*-i-normal-*-*-";
	sFontName += sFontPoint;
	sFontName += "-*,-*";

	gtk_style_set_font( pStyle, gdk_fontset_load( sFontName ) );
#endif // D_GTK

#ifdef D_MFC
	// �ǥե���ȤΥ������������

	if( pStyle == NULL )
		pStyle = (void *)1;

	// �ե���Ȥ�����

	LONG h = SPACE_FONT_DOT;
	mFontDesc.lfHeight = h;
	mFontDesc.lfWidth = 0;
	mFontDesc.lfEscapement = 0;
	mFontDesc.lfOrientation = 0;
	mFontDesc.lfWeight = FW_NORMAL;
	mFontDesc.lfItalic = FALSE;
	mFontDesc.lfUnderline = FALSE;
	mFontDesc.lfStrikeOut = FALSE;
	mFontDesc.lfCharSet = SHIFTJIS_CHARSET;
	mFontDesc.lfOutPrecision = OUT_DEFAULT_PRECIS;
	mFontDesc.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	mFontDesc.lfQuality = DEFAULT_QUALITY;
	mFontDesc.lfPitchAndFamily = (FIXED_PITCH | FF_MODERN);
	strcpy( mFontDesc.lfFaceName, "Pica" );

	pFont = new CFont;
	pFont->CreateFontIndirect( &mFontDesc );

	mD3.Create( &mFontDesc );

	staffRollIdx = 0;
#endif // D_MFC

	initAnime();
}

////////////////////////////////////////////////////////////////
// ���˥᡼�����ν����
////////////////////////////////////////////////////////////////

void DemoSpace::initAnime()
{
#ifdef D_GTK
	// ���ơ��֥������

	for( long i = 0; i < COLOR_TAB_MAX_N; i++ ){
		long col = 128 + (128 * i / COLOR_TAB_MAX_N);
		colorTab[i].red = ((col << 8) | col);
		colorTab[i].green = ((col << 8) | col);
		colorTab[i].blue = ((col << 8) | col);
	}
	gdk_colormap_alloc_colors(
			gdk_colormap_get_system(),
			colorTab, COLOR_TAB_MAX_N,
			FALSE, TRUE, colorResult );
#endif // D_GTK

#ifdef D_MFC
	// ���ơ��֥������

	const UINT txW = 1;
	const UINT txH = 1;
	for( long i = 0; i < COLOR_TAB_MAX_N; i++ ){
		long col = 128 + (128 * i / COLOR_TAB_MAX_N);

		// �ƥ������������

		g_Dir3d.BeginDraw();
		HRESULT result = g_Dir3d.pDir3dDevice->CreateTexture(
				txW, txH, 0,
				D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&(texture[i]), NULL );
		g_Dir3d.EndDraw();

		if( FAILED( result ) )
			continue;

		// �ƥ���������ɤ�Ĥ֤�

		D3DCOLOR clr = D3DCOLOR_XRGB( col, col, col );

		// �ɤ�Ĥ֤�����

		g_Dir3d.BeginDraw();

		IDirect3DSurface9 *sf = NULL;
		texture[i]->GetSurfaceLevel( 0, &sf );

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

		// ���᡼������

		img[i] = new WSDimage( texture[i], txW, txH );
	}
#endif // D_MFC

	zv = Z_SPEED;
	for( long i = 0; i < GUI_STAR_MAX_N; i++ ){
		x[i] = randm( XR * 2 + 1 ) - XR;
		y[i] = randm( YR * 2 + 1 ) - YR;
		z[i] = randm( ZR - 1 ) + 1;
	}
	for( long i = 0; i < NEBULA_MAX_N; i++ ){
		nx[i] = randm( NXR * 2 + 1 ) - NXR;
		ny[i] = randm( NYR * 2 + 1 ) - NYR;
		nz[i] = randm( NZR - 1 ) + 1;
	}
}

////////////////////////////////////////////////////////////////
// ����ΰ�ư
////////////////////////////////////////////////////////////////

void DemoSpace::move()
{
	long nMax = getStarN();
	for( long i = 0; i < nMax; i++ ){
		z[i] = ((z[i] - zv) % ZR + ZR) % ZR;
	}
	for( long i = 0; i < NEBULA_MAX_N; i++ ){
		nz[i] -= zv;
		if( (nz[i] < 0) || (nz[i] >= NZR)){
			nx[i] = randm( NXR * 2 ) - NXR;
			ny[i] = randm( NYR * 2 ) - NYR;
			nz[i] = (nz[i] % NZR + NZR) % NZR;
		}
	}
}

////////////////////////////////////////////////////////////////
// ���������
// bool flagDrawStaffRoll : �����åա���������褹�뤫?
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoSpace::draw( bool flagDrawStaffRoll )
{
	move();

	// �طʤ��ɤ�Ĥ֤�

#ifdef D_GTK
	GdkDrawable *d = gPcgDun.getWBuf()->getPixMap();
	GdkGC *gc = pStyle->bg_gc[GTK_STATE_NORMAL];
	gdk_draw_rectangle( d, gc, TRUE,
			0, 0,
			gMapDrawingArea->allocation.width,
			gMapDrawingArea->allocation.height );
#endif // D_GTK

	// �طʲ���������

	long sx = gPcgDun.getScrollBarX();
	long sy = gPcgDun.getScrollBarY();
	long sw = gPcgDun.getScrollBarW();
	long sh = gPcgDun.getScrollBarH();

	if( nRandmSel > -1 ){
		long ww = pcgSpace.getWidth();
		long hh = pcgSpace.getHeight();
		long xx = sx + (sw - ww) / 2;
		long yy = sy + (sh - hh) / 2;

		pcgSpace.draw( gPcgDun.getWBuf(), xx, yy, ww, hh );
	}

	// ����������

	Pcg *p = pcgNebula.next;
	for( long i = 0; i < NEBULA_MAX_N; i++ ){
		if( p == NULL )
			break;

		long drx = sx + sw / 2;
		long dry = sy + sh / 2;
		long zz = nz[i] + 1;
		drx += nx[i] / zz;
		dry += ny[i] / zz;

		drawNebula( p, drx, dry, zz );

		p = p->next;
	}

	// ��������

	long nMax = getStarN();
	long mx = sx + sw / 2;
	long my = sy + sh / 2;
	long zz = 1;
	long drx = 0;
	long dry = 0;
	for( long i = 0; i < nMax; i++ ){
		zz = z[i] + 1;
		drx = mx + (x[i] / zz);
		dry = my + (y[i] / zz);

		drawStar( drx, dry, zz );
	}

	if( flagDrawStaffRoll ){
		if( get_scene() == SCENE_N_ENDING_END ){
			drawTheEnd();
		} else {
			drawStaffRoll();
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////
// ��������
// long x : X ��ɸ
// long y : Y ��ɸ
// long z : Z ��ɸ
////////////////////////////////////////////////////////////////

void DemoSpace::drawStar( long x, long y, long z )
{
#ifdef D_GTK
	GdkDrawable *d = gPcgDun.getWBuf()->getPixMap();
	GdkGC *gc = pStyle->fg_gc[GTK_STATE_NORMAL];

	long idx = COLOR_TAB_MAX_N * (ZR - z) / ZR;
	if( idx < 0 )
		idx = 0;
	if( idx > COLOR_TAB_MAX_N - 1 )
		idx = COLOR_TAB_MAX_N - 1;
	gdk_gc_set_foreground( gc, &colorTab[idx] );

	gdk_draw_point( d, gc, x, y );
#endif // D_GTK

#ifdef D_MFC
	long idx = COLOR_TAB_MAX_N * (ZR - z) / ZR;
	if( idx < 0 )
		idx = 0;
	if( idx > COLOR_TAB_MAX_N - 1 )
		idx = COLOR_TAB_MAX_N - 1;

	if( img[idx] == NULL )
		return;

	g_Dir3d.BeginDraw();
	g_Dir3d.Draw( img[idx], 0, 0, x, y, 1, 1 );
	g_Dir3d.EndDraw();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ����������
// Pcg *p : �����β���
// long x : X ��ɸ
// long y : Y ��ɸ
// long z : Z ��ɸ
////////////////////////////////////////////////////////////////

void DemoSpace::drawNebula( Pcg *p, long x, long y, long z )
{
#ifdef D_MFC
	if( p == NULL )
		return;

	long w = p->getWidth();
	long h = p->getHeight();

	long preSize = g_Dir3d.nSizeRate;
	g_Dir3d.nSizeRate = 100 / z;

	long ww = w * g_Dir3d.nTileSizeRate / 100;
	long hh = h * g_Dir3d.nTileSizeRate / 100;
	if( g_Dir3d.nTileSizeRate > 0 ){
		long xx = x - (ww / 2);
		long yy = y - (hh / 2);

		p->draw( gPcgDun.getWBuf(), xx, yy, ww, hh );
	}

	g_Dir3d.nSizeRate = preSize;
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �����åա����������
////////////////////////////////////////////////////////////////

void DemoSpace::drawStaffRoll()
{
	long sx = gPcgDun.getScrollBarX();
	long sw = gPcgDun.getScrollBarW();
	long sh = gPcgDun.getScrollBarH();

	long x = (sw - (nStaffRollIntervalWidth * nStaffRollMaxLen))
			/ 2 + sx;
	long y = 0;

	if( g_flg_cui )
		staffRollY += STAFF_ROLL_SPEED_CUI;
	else
		staffRollY += STAFF_ROLL_SPEED;

	for( long i = 0; i < LOOP_MAX_1000; i++ ){
		if( gStrStaffRoll[i] == NULL )
			break;
		if( gStrStaffRoll[i][0] == '\0' )
			break;

		y = (i * nStaffRollIntervalHeight) - staffRollY;

		if( y < (-1 * SPACE_FONT_DOT) )
			continue;
		if( y > sh )
			break;

#ifdef	D_MFC
		if( y < (sh * 6 / 16) )
			continue;
		if( y > (sh * 10 / 16) )
			continue;
#endif

		drawStaffRollLine( x, y, gStrStaffRoll[i] );
	}

	if( y < (sh / 2) )
		if( get_scene() != SCENE_N_ENDING_END )
			change_scene_gui( SCENE_N_ENDING_END );
}

////////////////////////////////////////////////////////////////
// The End ������
////////////////////////////////////////////////////////////////

void DemoSpace::drawTheEnd()
{
	long sx = gPcgDun.getScrollBarX();
	long sw = gPcgDun.getScrollBarW();
	long sh = gPcgDun.getScrollBarH();

	long x = (sw - (nStaffRollIntervalWidth * nStaffRollMaxLen))
			/ 2 + sx;
	long y = sh / 2;

	drawStaffRollLine( x, y, gStrTheEnd );
}

////////////////////////////////////////////////////////////////
// �����åա������ 1 �Ԥ�����
// long x : X ��ɸ
// long y : Y ��ɸ
// const char *str : 1 ��ʬ�Υ����åա�����
////////////////////////////////////////////////////////////////

void DemoSpace::drawStaffRollLine( long x, long y, const char *str )
{
	if( str == NULL )
		return;

	long sw = gPcgDun.getScrollBarW();
	long sh = gPcgDun.getScrollBarH();

	if( x > sw )
		return;
	if( y > sh )
		return;
	if( y < (-1 * SPACE_FONT_DOT) )
		return;

#ifdef D_MFC
	mD3.Begin();
#endif

	long k = 0;
	for( long j = 0; j < LOOP_MAX_100; j++ ){
		const char *p = &(str[k]);
		if( *p == '\0' )
			break;

		drawCharStd( x, y, get_next_char_str( p ) );

		x += nStaffRollIntervalWidth;
		k += get_next_char_len( p );
	}

#ifdef D_MFC
	mD3.End();
#endif
}

////////////////////////////////////////////////////////////////
// ʸ��������(���դ�)
// long x : X ��ɸ
// long y : Y ��ɸ
// const char *str : ʸ��
////////////////////////////////////////////////////////////////

void DemoSpace::drawCharStd( long x, long y, const char *str )
{
#ifndef D_MFC
	drawChar( 0x00, 0x00, 0x00, x + 1, y + 1, str );
	drawChar( 0x00, 0x00, 0x00, x - 1, y - 1, str );
#endif
	drawChar( 0xff, 0xff, 0xff, x, y, str );
}

////////////////////////////////////////////////////////////////
// ʸ��������
// long r : r ��
// long g : g ��
// long b : b ��
// long x : X ��ɸ
// long y : Y ��ɸ
// const char *str : ʸ��
////////////////////////////////////////////////////////////////

void DemoSpace::drawChar(
	long r, long g, long b,
	long x, long y, const char *str )
{
	r &= 0xff;
	g &= 0xff;
	b &= 0xff;

#ifdef D_GTK
	GdkColor color;
	color.pixel = 0;
	color.red = (r << 8) | r;
	color.green = (g << 8) | g;
	color.blue = (b << 8) | b;

	GdkDrawable *d = gPcgDun.getWBuf()->getPixMap();
	GdkFont *font = gtk_style_get_font( pStyle );
	GdkGC *gc = pStyle->fg_gc[GTK_STATE_NORMAL];

	gdk_color_alloc( gdk_colormap_get_system(), &color );
	gdk_gc_set_foreground( gc, &color );

	gdk_draw_string( d, font, gc, x, y, str );
#endif // D_GTK

#ifdef D_MFC
	if( str[0] == '&' )
		str = "&&";

	D3DCOLOR color = D3DCOLOR_XRGB( r, g, b );

	mD3.Draw( x, y, color, str );
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// Z �����˲�®
// long zav : ��®��
////////////////////////////////////////////////////////////////

void DemoSpace::addSpeedZ( long zav )
{
	zv += zav;
}

////////////////////////////////////////////////////////////////
// ���ο����֤�
// return : ���ο�
////////////////////////////////////////////////////////////////

long DemoSpace::getStarN()
{
	if( g_gui_star_n <= 0 )
		return GUI_STAR_DFLT_N;
	if( g_gui_star_n > GUI_STAR_MAX_N )
		return GUI_STAR_MAX_N;

	return g_gui_star_n;
}
