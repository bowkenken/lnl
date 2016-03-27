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
* $Id: DemoGameOver.cpp,v 1.14 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ゲーム・オーバー・デモ
////////////////////////////////////////////////////////////////

#define DEMO_GAME_OVER_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define GAME_OVER_WAIT_TIME	5

// ゲーム・オーバー画像のディレクトリ
#define STR_GAME_OVER_DIR_NAME	"game_over/"

#define GAME_OVER_FONT_POINT	64
#define GAME_OVER_FONT_DOT	64

#define GAME_OVER_STR_N	2
static const char *gStrGameOver[GAME_OVER_STR_N] = {
	"GAME",
	"OVER",
};

static long maxFrameEnd = 24;

#ifdef	D_MFC
static long skipFrame = 1;
#else
static long skipFrame = 60;
#endif

////////////////////////////////////////////////////////////////
// コンストラクタ
////////////////////////////////////////////////////////////////

DemoGameOver::DemoGameOver()
{
	pGameOverStyle = NULL;
}

////////////////////////////////////////////////////////////////
// デストラクタ
////////////////////////////////////////////////////////////////

DemoGameOver::~DemoGameOver()
{
#ifdef D_MFC
	if( pGameOverFont != NULL ){
		delete pGameOverFont;
		pGameOverFont = NULL;
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// 初期化
////////////////////////////////////////////////////////////////

void DemoGameOver::init()
{
	// ゲーム・オーバー画像の検索を設定

	WSCstring dir = STR_DEFAULT_GRAPH_DIR_NAME;
	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList ls;

	// ゲーム・オーバー画像を検索

	{
		nGameOverN = 0;

		ls.reset( STR_GAME_OVER_DIR_NAME, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
		}
		nGameOverN = j;
	}

	// ゲーム・オーバー画像をランダムに選択

	if( nGameOverN > 0 )
		nGameOverRandmSelN = randm( nGameOverN );
	else
		nGameOverRandmSelN = -1;

	// ゲーム・オーバー画像を読み込む

	if( nGameOverRandmSelN > -1 ){
		ls.reset( STR_GAME_OVER_DIR_NAME, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
			if( j == nGameOverRandmSelN ){
				pcgGameOver.init( path );
				break;
			}
		}
	}

#ifdef D_GTK
	// デフォルトのスタイルを設定

	if( pGameOverStyle == NULL ){
		pGameOverStyle = gtk_style_copy(
				gtk_widget_get_default_style() );
	}
	if( pGameOverStyle->fg_gc[GTK_STATE_NORMAL] == NULL ){
		pGameOverStyle->fg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}
	if( pGameOverStyle->bg_gc[GTK_STATE_NORMAL] == NULL ){
		pGameOverStyle->bg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}

	// フォントを初期化

	WSCstring sFontPoint = GAME_OVER_FONT_POINT * 10;
	WSCstring sFontName = "";
	sFontName += "-*-*-*-i-normal-*-*-";
	sFontName += sFontPoint;
	sFontName += "-*,-*";

	gtk_style_set_font( pGameOverStyle, gdk_fontset_load( sFontName ) );
#endif // D_GTK

#ifdef D_MFC
	// デフォルトのスタイルを設定

	if( pGameOverStyle == NULL )
		pGameOverStyle = (void *)1;

	// フォントを初期化

	LONG h = GAME_OVER_FONT_DOT;
	mGameOverFontDesc.lfHeight = h;
	mGameOverFontDesc.lfWidth = 0;
	mGameOverFontDesc.lfEscapement = 0;
	mGameOverFontDesc.lfOrientation = 0;
	mGameOverFontDesc.lfWeight = FW_NORMAL;
	mGameOverFontDesc.lfItalic = FALSE;
	mGameOverFontDesc.lfUnderline = FALSE;
	mGameOverFontDesc.lfStrikeOut = FALSE;
	mGameOverFontDesc.lfCharSet = SHIFTJIS_CHARSET;
	mGameOverFontDesc.lfOutPrecision
			= OUT_DEFAULT_PRECIS;
	mGameOverFontDesc.lfClipPrecision
			= CLIP_DEFAULT_PRECIS;
	mGameOverFontDesc.lfQuality = DEFAULT_QUALITY;
	mGameOverFontDesc.lfPitchAndFamily
			= (FIXED_PITCH | FF_MODERN);
	strcpy( mGameOverFontDesc.lfFaceName, "Pica" );

	pGameOverFont = new CFont;
	pGameOverFont->CreateFontIndirect(
			&mGameOverFontDesc );

	mD3GameOver.Create( &mGameOverFontDesc );
#endif // D_MFC

	initAnime();
}

////////////////////////////////////////////////////////////////
// アニメーションの初期化
////////////////////////////////////////////////////////////////

void DemoGameOver::initAnime()
{
	wait_time = 0;
	frame = 0;

	len = 1;
	for( long i = 0; i < GAME_OVER_STR_N; i++ )
		len = max_l( len, str_len_draw( gStrGameOver[i] ) );

#ifdef D_GTK
	w = gMapDrawingArea->allocation.width;
	h = gMapDrawingArea->allocation.height;
#endif // D_GTK

#ifdef D_MFC
	CXlnlView *view = theApp.m_pMainFrm->GetView();
	CRect rect;
	view->GetClientRect( &rect );

	w = rect.Width();
	h = rect.Height();
#endif // D_MFC

	baseX = (w - (len * GAME_OVER_FONT_DOT)) / 2;
	baseY = h / 2;

	for( long j = 0; j < len; j++ ){
		mx[0][j] = (baseX + (j * GAME_OVER_FONT_DOT));
		mx[1][j] = (baseX + (j * GAME_OVER_FONT_DOT));
		my[0][j] = baseY;
		my[1][j] = baseY + (GAME_OVER_FONT_DOT * 120 / _100_PERCENT);
	}
}

////////////////////////////////////////////////////////////////
// ゲーム・オーバー画面の描画
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool DemoGameOver::draw()
{
	frame++;

	if( get_scene() == SCENE_N_GAME_OVER ){
		// シーン切り替え
		wait_time = time( NULL ) + GAME_OVER_WAIT_TIME;
		frame = 0;
		change_scene_gui( SCENE_N_GAME_OVER_WAIT );
	}

	if( get_scene() == SCENE_N_GAME_OVER_WAIT ){
		// フレームを間引く
		if( (frame % skipFrame) != 0 )
			return true;

		if( time( NULL ) < wait_time ){
			// 描画
			return drawWait();
		} else {
			// シーン切り替え
			gPcgDun.scrollTile( 0, 0 );
			frame = 0;
			change_scene_gui( SCENE_N_GAME_OVER_END );
		}
	}

	if( get_scene() == SCENE_N_GAME_OVER_END ){
		// フレームを間引く
		if( frame > maxFrameEnd )
			if( (frame % skipFrame) != 0 )
				return true;

		// 描画
		return drawEnd();
	}

	return true;
}

////////////////////////////////////////////////////////////////
// ゲーム・オーバー画面の描画 (クリック無効中)
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool DemoGameOver::drawWait()
{
	gPcgDun.drawTurn( true );

	return true;
}

////////////////////////////////////////////////////////////////
// ゲーム・オーバー画面の描画 (クリックで終了)
// return : エラーが無かったか?
////////////////////////////////////////////////////////////////

bool DemoGameOver::drawEnd()
{
	if( nGameOverRandmSelN <= -1 )
		return false;

	// 背景を塗りつぶす

#ifdef D_GTK
	GdkDrawable *d = gPcgDun.getWBuf()->getPixMap();
	GdkGC *gc = pGameOverStyle->bg_gc[GTK_STATE_NORMAL];
	gdk_draw_rectangle( d, gc, TRUE,
			0, 0,
			gMapDrawingArea->allocation.width,
			gMapDrawingArea->allocation.height );
#endif // D_GTK

	// 背景画像を描画

	long sx = gPcgDun.getScrollBarX();
	long sy = gPcgDun.getScrollBarY();
	long sw = w;
	long sh = h;

	long ww = pcgGameOver.getWidth();
	long hh = pcgGameOver.getHeight();
	long xx = sx + (sw - ww) / 2;
	long yy = sy + (sh - hh) / 2;

	pcgGameOver.draw( gPcgDun.getWBuf(), xx, yy, ww, hh );

	// ゲーム・オーバーを描画

	drawGameOver( frame );

	return true;
}

////////////////////////////////////////////////////////////////
// ゲーム・オーバー画面の描画
// long frame : 現在のフレーム
////////////////////////////////////////////////////////////////

void DemoGameOver::drawGameOver( long frame )
{
	if( pGameOverStyle == NULL )
		init();

	long ff;
	ff = maxFrameEnd - frame;
	if( ff < 0 )
		ff = 0;

	for( long j = 0; j < len; j++ ){
		long xx;
		xx = w * ff / maxFrameEnd;

		x[0][j] = mx[0][j] - xx;
		y[0][j] = my[0][j];
		x[1][j] = mx[1][j] + xx;
		y[1][j] = my[1][j];
	}

	drawGameOverString();
}

////////////////////////////////////////////////////////////////
// ゲーム・オーバー文字列の描画
////////////////////////////////////////////////////////////////

void DemoGameOver::drawGameOverString()
{
	for( long i = 0; i < GAME_OVER_STR_N; i++ ){
		for( long j = 0; j < len; j++ ){
			if( gStrGameOver[i][j] == '\0' )
				break;

			drawGameOverCharStd( x[i][j], y[i][j],
					gStrGameOver[i][j] );
		}
	}
}

////////////////////////////////////////////////////////////////
// ゲーム・オーバー文字の描画
////////////////////////////////////////////////////////////////

void DemoGameOver::drawGameOverCharStd( long x, long y, char c )
{
	drawGameOverChar( 0xff, 0x00, 0x00, x, y, c );
}

////////////////////////////////////////////////////////////////
// ゲーム・オーバー文字の描画
////////////////////////////////////////////////////////////////

void DemoGameOver::drawGameOverChar(
	long r, long g, long b,
	long x, long y, char c )
{
	char str[4 + 1];
	str[0] = c;
	str[1] = '\0';

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
	GdkFont *font = gtk_style_get_font( pGameOverStyle );
	GdkGC *gc = pGameOverStyle->fg_gc[GTK_STATE_NORMAL];

	gdk_color_alloc( gdk_colormap_get_system(), &color );
	gdk_gc_set_foreground( gc, &color );

	gdk_draw_string( d, font, gc, x, y, str );
#endif // D_GTK

#ifdef D_MFC
	D3DCOLOR color = D3DCOLOR_XRGB( r, g, b );

	mD3GameOver.Begin();
	mD3GameOver.Draw( x, y, color, str );
	mD3GameOver.End();
#endif // D_MFC
}
