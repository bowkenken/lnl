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
* $Id: DemoSpace.cpp,v 1.22 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// 宇宙デモ
////////////////////////////////////////////////////////////////

#define DEMO_SPACE_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// 宇宙
////////////////////////////////////////////////////////////////

// 宇宙の背景画像のディレクトリ
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
// スタッフ・ロール
////////////////////////////////////////////////////////////////

#define STAFF_ROLL_SPEED_CUI	2
#define STAFF_ROLL_SPEED	1

#define SPACE_FONT_POINT	14
#define SPACE_FONT_DOT	14

// 文字間隔
static const long nStaffRollIntervalWidth = SPACE_FONT_DOT;
static const long nStaffRollIntervalHeight = SPACE_FONT_DOT * 2;

#define gStrStaffRoll	g_str_staff_roll
#define gStrTheEnd	g_str_the_end

////////////////////////////////////////////////////////////////
// コンストラクタ
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
// デストラクタ
////////////////////////////////////////////////////////////////

DemoSpace::~DemoSpace()
{
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void DemoSpace::init()
{
	g_gui_star_n = GUI_STAR_DFLT_N;

	// 宇宙の背景画像の検索を設定

	WSCstring dir = STR_DEFAULT_GRAPH_DIR_NAME;
	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList ls;

	// 宇宙の背景画像を検索

	nMaxFile = 0;
	ls.reset( STR_ENDING_SPACE_DIR_NAME, ext );
	long j = 0;
	for( j = 0; j < LOOP_MAX_1000; j++ ){
		WSCstring path = ls.next();
		if( path.getChars() <= 0 )
			break;
	}
	nMaxFile = j;

	// 宇宙の背景画像をランダムに選択

	if( nMaxFile > 0 )
		nRandmSel = randm( nMaxFile );
	else
		nRandmSel = -1;

	// 宇宙の背景画像を読み込む

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
	// 星雲の画像を検索して読み込む

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

	// スタッフ・ロール

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
	// デフォルトのスタイルを設定

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

	// フォントを初期化

	WSCstring sFontPoint = SPACE_FONT_POINT * 10;
	WSCstring sFontName = "";
	sFontName += "-*-*-*-i-normal-*-*-";
	sFontName += sFontPoint;
	sFontName += "-*,-*";

	gtk_style_set_font( pStyle, gdk_fontset_load( sFontName ) );
#endif // D_GTK

#ifdef D_MFC
	// デフォルトのスタイルを設定

	if( pStyle == NULL )
		pStyle = (void *)1;

	// フォントを初期化

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
// アニメーションの初期化
////////////////////////////////////////////////////////////////

void DemoSpace::initAnime()
{
#ifdef D_GTK
	// 色テーブルを設定

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
	// 色テーブルを設定

	const UINT txW = 1;
	const UINT txH = 1;
	for( long i = 0; i < COLOR_TAB_MAX_N; i++ ){
		long col = 128 + (128 * i / COLOR_TAB_MAX_N);

		// テクスチャを生成

		g_Dir3d.BeginDraw();
		HRESULT result = g_Dir3d.pDir3dDevice->CreateTexture(
				txW, txH, 0,
				D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&(texture[i]), NULL );
		g_Dir3d.EndDraw();

		if( FAILED( result ) )
			continue;

		// テクスチャを塗りつぶす

		D3DCOLOR clr = D3DCOLOR_XRGB( col, col, col );

		// 塗りつぶし開始

		g_Dir3d.BeginDraw();

		IDirect3DSurface9 *sf = NULL;
		texture[i]->GetSurfaceLevel( 0, &sf );

		IDirect3DSurface9 *preTrgt = NULL;
		g_Dir3d.pDir3dDevice->GetRenderTarget( 0, &preTrgt );
		g_Dir3d.pDir3dDevice->SetRenderTarget( 0, sf );

		// 塗りつぶし

		g_Dir3d.pDir3dDevice->Clear(
				0, NULL, D3DCLEAR_TARGET,
				clr, 1.0, 0 );

		// 塗りつぶし終了

		g_Dir3d.pDir3dDevice->SetRenderTarget( 0, preTrgt );

		g_Dir3d.EndDraw();

		// イメージ生成

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
// 宇宙の移動
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
// 宇宙の描画
// bool flagDrawStaffRoll : スタッフ・ロールを描画するか?
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool DemoSpace::draw( bool flagDrawStaffRoll )
{
	move();

	// 背景を塗りつぶす

#ifdef D_GTK
	GdkDrawable *d = gPcgDun.getWBuf()->getPixMap();
	GdkGC *gc = pStyle->bg_gc[GTK_STATE_NORMAL];
	gdk_draw_rectangle( d, gc, TRUE,
			0, 0,
			gMapDrawingArea->allocation.width,
			gMapDrawingArea->allocation.height );
#endif // D_GTK

	// 背景画像を描画

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

	// 星雲を描画

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

	// 星を描画

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
// 星の描画
// long x : X 座標
// long y : Y 座標
// long z : Z 座標
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
// 星雲の描画
// Pcg *p : 星雲の画像
// long x : X 座標
// long y : Y 座標
// long z : Z 座標
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
// スタッフ・ロールの描画
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
// The End の描画
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
// スタッフ・ロールの 1 行を描画
// long x : X 座標
// long y : Y 座標
// const char *str : 1 行分のスタッフ・ロール
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
// 文字の描画(陰付き)
// long x : X 座標
// long y : Y 座標
// const char *str : 文字
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
// 文字の描画
// long r : r 色
// long g : g 色
// long b : b 色
// long x : X 座標
// long y : Y 座標
// const char *str : 文字
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
// Z 方向に加速
// long zav : 加速度
////////////////////////////////////////////////////////////////

void DemoSpace::addSpeedZ( long zav )
{
	zv += zav;
}

////////////////////////////////////////////////////////////////
// 星の数を返す
// return : 星の数
////////////////////////////////////////////////////////////////

long DemoSpace::getStarN()
{
	if( g_gui_star_n <= 0 )
		return GUI_STAR_DFLT_N;
	if( g_gui_star_n > GUI_STAR_MAX_N )
		return GUI_STAR_MAX_N;

	return g_gui_star_n;
}
