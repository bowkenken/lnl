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
* $Id: DemoGameOver.cpp,v 1.14 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// �����ࡦ�����С����ǥ�
////////////////////////////////////////////////////////////////

#define DEMO_GAME_OVER_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define GAME_OVER_WAIT_TIME	5

// �����ࡦ�����С������Υǥ��쥯�ȥ�
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
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

DemoGameOver::DemoGameOver()
{
	pGameOverStyle = NULL;
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
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
// �����
////////////////////////////////////////////////////////////////

void DemoGameOver::init()
{
	// �����ࡦ�����С������θ���������

	WSCstring dir = STR_DEFAULT_GRAPH_DIR_NAME;
	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList ls;

	// �����ࡦ�����С������򸡺�

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

	// �����ࡦ�����С�����������������

	if( nGameOverN > 0 )
		nGameOverRandmSelN = randm( nGameOverN );
	else
		nGameOverRandmSelN = -1;

	// �����ࡦ�����С��������ɤ߹���

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
	// �ǥե���ȤΥ������������

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

	// �ե���Ȥ�����

	WSCstring sFontPoint = GAME_OVER_FONT_POINT * 10;
	WSCstring sFontName = "";
	sFontName += "-*-*-*-i-normal-*-*-";
	sFontName += sFontPoint;
	sFontName += "-*,-*";

	gtk_style_set_font( pGameOverStyle, gdk_fontset_load( sFontName ) );
#endif // D_GTK

#ifdef D_MFC
	// �ǥե���ȤΥ������������

	if( pGameOverStyle == NULL )
		pGameOverStyle = (void *)1;

	// �ե���Ȥ�����

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
// ���˥᡼�����ν����
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
// �����ࡦ�����С����̤�����
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoGameOver::draw()
{
	frame++;

	if( get_scene() == SCENE_N_GAME_OVER ){
		// �������ڤ��ؤ�
		wait_time = time( NULL ) + GAME_OVER_WAIT_TIME;
		frame = 0;
		change_scene_gui( SCENE_N_GAME_OVER_WAIT );
	}

	if( get_scene() == SCENE_N_GAME_OVER_WAIT ){
		// �ե졼���ְ���
		if( (frame % skipFrame) != 0 )
			return true;

		if( time( NULL ) < wait_time ){
			// ����
			return drawWait();
		} else {
			// �������ڤ��ؤ�
			gPcgDun.scrollTile( 0, 0 );
			frame = 0;
			change_scene_gui( SCENE_N_GAME_OVER_END );
		}
	}

	if( get_scene() == SCENE_N_GAME_OVER_END ){
		// �ե졼���ְ���
		if( frame > maxFrameEnd )
			if( (frame % skipFrame) != 0 )
				return true;

		// ����
		return drawEnd();
	}

	return true;
}

////////////////////////////////////////////////////////////////
// �����ࡦ�����С����̤����� (����å�̵����)
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoGameOver::drawWait()
{
	gPcgDun.drawTurn( true );

	return true;
}

////////////////////////////////////////////////////////////////
// �����ࡦ�����С����̤����� (����å��ǽ�λ)
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoGameOver::drawEnd()
{
	if( nGameOverRandmSelN <= -1 )
		return false;

	// �طʤ��ɤ�Ĥ֤�

#ifdef D_GTK
	GdkDrawable *d = gPcgDun.getWBuf()->getPixMap();
	GdkGC *gc = pGameOverStyle->bg_gc[GTK_STATE_NORMAL];
	gdk_draw_rectangle( d, gc, TRUE,
			0, 0,
			gMapDrawingArea->allocation.width,
			gMapDrawingArea->allocation.height );
#endif // D_GTK

	// �طʲ���������

	long sx = gPcgDun.getScrollBarX();
	long sy = gPcgDun.getScrollBarY();
	long sw = w;
	long sh = h;

	long ww = pcgGameOver.getWidth();
	long hh = pcgGameOver.getHeight();
	long xx = sx + (sw - ww) / 2;
	long yy = sy + (sh - hh) / 2;

	pcgGameOver.draw( gPcgDun.getWBuf(), xx, yy, ww, hh );

	// �����ࡦ�����С�������

	drawGameOver( frame );

	return true;
}

////////////////////////////////////////////////////////////////
// �����ࡦ�����С����̤�����
// long frame : ���ߤΥե졼��
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
// �����ࡦ�����С�ʸ���������
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
// �����ࡦ�����С�ʸ��������
////////////////////////////////////////////////////////////////

void DemoGameOver::drawGameOverCharStd( long x, long y, char c )
{
	drawGameOverChar( 0xff, 0x00, 0x00, x, y, c );
}

////////////////////////////////////////////////////////////////
// �����ࡦ�����С�ʸ��������
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
