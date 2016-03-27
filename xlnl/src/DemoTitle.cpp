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
* $Id: DemoTitle.cpp,v 1.22 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// �����ȥ롦�ǥ�
////////////////////////////////////////////////////////////////

#define DEMO_TITLE_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define DEMO_LOOP_TIME	15

// �����ȥ�����Υǥ��쥯�ȥ�
#define STR_TITLE_DIR_NAME	"title/"

#define TITLE_FONT_POINT	32
#define TITLE_FONT_DOT	32

typedef enum {
	DRAW_TITLE_KIND_0,
	DRAW_TITLE_KIND_1,
	DRAW_TITLE_KIND_2,
	DRAW_TITLE_KIND_3,
	DRAW_TITLE_KIND_4,
	DRAW_TITLE_KIND_5,
	DRAW_TITLE_KIND_6,
	DRAW_TITLE_KIND_MAX_N,
} drawTitleKindType;

static const char *gStrTitle[3] = {
	"Labyrinths",
	"    &     ",
	" Legends  ",
};

////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

DemoTitle::DemoTitle()
{
	pTitleStyle = NULL;
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

DemoTitle::~DemoTitle()
{
#ifdef D_MFC
	if( pTitleFont != NULL ){
		delete pTitleFont;
		pTitleFont = NULL;
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �����
////////////////////////////////////////////////////////////////

void DemoTitle::init()
{
	// �����ȥ�����θ���������

	WSCstring dir = STR_FIX_GRAPH_DIR_NAME;
	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList ls;

	// �����ȥ�����򸡺�

	{
		nTitleN = 0;

		ls.reset( STR_TITLE_DIR_NAME, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
			if( randm( j + 1 ) == 0 )
				nTitleN = j;
		}
		nTitleN = j;
	}

	// �����ȥ����������������

	if( nTitleN > 0 )
		nTitleRandmSelN = randm( nTitleN );
	else
		nTitleRandmSelN = -1;

	// �����ȥ�������ɤ߹���

	if( nTitleRandmSelN > -1 ){
		ls.reset( STR_TITLE_DIR_NAME, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
			if( j == nTitleRandmSelN ){
				pcgTitle.init( path );
				break;
			}
		}
	}

#ifdef D_GTK
	// �ǥե���ȤΥ������������

	if( pTitleStyle == NULL )
		pTitleStyle = gtk_style_copy( gtk_widget_get_default_style() );
	if( pTitleStyle->fg_gc[GTK_STATE_NORMAL] == NULL ){
		pTitleStyle->fg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}
	if( pTitleStyle->bg_gc[GTK_STATE_NORMAL] == NULL ){
		pTitleStyle->bg_gc[GTK_STATE_NORMAL]
				= gdk_gc_new( gMapDrawingArea->window );
	}

	// �ե���Ȥ�����

	WSCstring sFontPoint = TITLE_FONT_POINT * 10;
	WSCstring sFontName = "";
	sFontName += "-*-*-*-i-normal-*-*-";
	sFontName += sFontPoint;
	sFontName += "-*,-*";

	gtk_style_set_font( pTitleStyle, gdk_fontset_load( sFontName ) );
#endif // D_GTK

#ifdef D_MAC
	// �ǥե���ȤΥ������������

	if( pTitleStyle == NULL )
		pTitleStyle = (void *)1;

	// �ե���Ȥ�����

#endif // D_MAC

#ifdef D_IPHONE
	// �ǥե���ȤΥ������������

	if( pTitleStyle == NULL )
		pTitleStyle = (void *)1;

	// �ե���Ȥ�����

	CGContextRef context = gPcgDun.getWBuf()->getPixMap();
	CGContextSelectFont( context, "Arial", TITLE_FONT_POINT, kCGEncodingMacRoman );
#endif // D_IPHONE

#ifdef D_MFC
	// �ǥե���ȤΥ������������

	if( pTitleStyle == NULL )
		pTitleStyle = (void *)1;

	// �ե���Ȥ�����

	LONG h = TITLE_FONT_DOT;
	mTitleFontDesc.lfHeight = h;
	mTitleFontDesc.lfWidth = 0;
	mTitleFontDesc.lfEscapement = 0;
	mTitleFontDesc.lfOrientation = 0;
	mTitleFontDesc.lfWeight = FW_NORMAL;
	mTitleFontDesc.lfItalic = FALSE;
	mTitleFontDesc.lfUnderline = FALSE;
	mTitleFontDesc.lfStrikeOut = FALSE;
	mTitleFontDesc.lfCharSet = SHIFTJIS_CHARSET;
	mTitleFontDesc.lfOutPrecision
			= OUT_DEFAULT_PRECIS;
	mTitleFontDesc.lfClipPrecision
			= CLIP_DEFAULT_PRECIS;
	mTitleFontDesc.lfQuality = DEFAULT_QUALITY;
	mTitleFontDesc.lfPitchAndFamily
			= (FIXED_PITCH | FF_MODERN);
	strcpy( mTitleFontDesc.lfFaceName, "Pica" );

	pTitleFont = new CFont;
	pTitleFont->CreateFontIndirect(
			&mTitleFontDesc );

	mD3Title.Create( &mTitleFontDesc );
#endif // D_MFC

	initAnime();
}

////////////////////////////////////////////////////////////////
// �����
////////////////////////////////////////////////////////////////

void DemoTitle::initAnime()
{
	len = 1;
	for( long i = 0; i < 3; i++ )
		len = max_l( len, str_len_draw( gStrTitle[i] ) );

#ifdef D_GTK
	w = gMapDrawingArea->allocation.width;
	h = gMapDrawingArea->allocation.height;
#endif // D_GTK

#ifdef D_MAC
	w = gMainMapView.visibleRect.size.width;
	h = gMainMapView.visibleRect.size.height;
#endif // D_MAC

#ifdef D_IPHONE
	w = gMainMapWin.mapScrollView.frame.size.width;
	h = gMainMapWin.mapScrollView.frame.size.height;
#endif // D_IPHONE

#ifdef D_MFC
	CXlnlView *view = theApp.m_pMainFrm->GetView();
	CRect rect;
	view->GetClientRect( &rect );

	w = rect.Width();
	h = rect.Height();
#endif // D_MFC

	baseX = (w - (len * TITLE_FONT_DOT)) / 2;
	baseY = h / 2;

	for( long j = 0; j < len; j++ ){
		mx[0][j] = (baseX + (j * TITLE_FONT_DOT));
		mx[1][j] = (baseX + (j * TITLE_FONT_DOT));
		mx[2][j] = (baseX + (j * TITLE_FONT_DOT));
		my[0][j] = baseY - (TITLE_FONT_DOT * 120 / _100_PERCENT);
		my[1][j] = baseY;
		my[2][j] = baseY + (TITLE_FONT_DOT * 120 / _100_PERCENT);
	}
}

////////////////////////////////////////////////////////////////
// �����ȥ���̤�����
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoTitle::draw()
{
	if( nTitleRandmSelN <= -1 )
		return false;

	// �طʤ��ɤ�Ĥ֤�

#ifdef D_GTK
	GdkDrawable *d = gPcgDun.getWBuf()->getPixMap();
	GdkGC *gc = pTitleStyle->bg_gc[GTK_STATE_NORMAL];
	gdk_draw_rectangle( d, gc, TRUE,
			0, 0,
			gMapDrawingArea->allocation.width,
			gMapDrawingArea->allocation.height );
#endif // D_GTK

#ifdef D_MAC
#endif // D_MAC

#ifdef D_IPHONE
	CGContextRef context = gPcgDun.getWBuf()->getPixMap();
	CGRect rect = gMainMapWin.mapScrollView.bounds;
	rect.origin.y = -rect.origin.y - rect.size.height;

	CGContextSaveGState(context);

	CGContextClipToRect(context, rect);
	CGContextSetRGBFillColor( context, 0.0f, 0.0f, 0.0f, 1.0f );
	CGContextFillRect( context, rect );

	CGContextRestoreGState(context);
#endif // D_IPHONE

	// �طʲ���������

	long x = gPcgDun.getScrollBarX();
	long y = gPcgDun.getScrollBarY();
	long w = pcgTitle.getWidth();
	long h = pcgTitle.getHeight();
	pcgTitle.drawFix( gPcgDun.getWBuf(), x, y, w, h );

	// �����ȥ롦�͡��������

	static time_t t = 0;
	static long frame = 0;
	static drawTitleKindType kind = DRAW_TITLE_KIND_1;
	if( time( NULL ) >= t ){
		frame = 0;
		kind = (drawTitleKindType)randm( DRAW_TITLE_KIND_MAX_N );
	}
	if( frame <= 0 )
		t = time( NULL ) + DEMO_LOOP_TIME;

	switch( kind ){
	case DRAW_TITLE_KIND_0:
		drawTitle0( frame );
		break;
	case DRAW_TITLE_KIND_1:
		drawTitle1( frame );
		break;
	case DRAW_TITLE_KIND_2:
		drawTitle2( frame );
		break;
	case DRAW_TITLE_KIND_3:
		drawTitle3( frame );
		break;
	case DRAW_TITLE_KIND_4:
		drawTitle4( frame );
		break;
	case DRAW_TITLE_KIND_5:
		drawTitle5( frame );
		break;
	case DRAW_TITLE_KIND_6:
		drawTitle6( frame );
		break;
	case DRAW_TITLE_KIND_MAX_N:
		break;
	}

	frame++;

#ifdef D_MAC
	[gMainMapView setNeedsDisplay];
#endif // D_MAC
	
#ifdef D_IPHONE
	[gMainMapWin.view setNeedsDisplay];
	[gMainMapWin.mapView setNeedsDisplay];
#endif // D_IPHONE

	return true;
}

////////////////////////////////////////////////////////////////
// �����ȥ���̤����� No.0
// long frame : ���ߤΥե졼��
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitle0( long frame )
{
	if( pTitleStyle == NULL )
		init();

	const long bgnX = w;
	static long v = 64;
	if( frame == 0 )
		v = 16 + randm( 64 + 1 );

	long x[3], y[3];
	x[0] = bgnX;
	x[1] = bgnX;
	x[2] = bgnX;
	y[0] = baseY - (TITLE_FONT_DOT * 120 / _100_PERCENT);
	y[1] = baseY;
	y[2] = baseY + (TITLE_FONT_DOT * 120 / _100_PERCENT);

	long idx[3];
	for( long j = 0; j < 3; j++ )
		idx[j] = 0;

	for( long f = 0; f < frame; f++ ){
		if( (gStrTitle[0][idx[0]] == '\0')
				&& (gStrTitle[1][idx[1]] == '\0')
				&& (gStrTitle[2][idx[2]] == '\0') ){
			break;
		}

		for( long j = 0; j < 3; j++ ){
			x[j] -= v;
			if( x[j] < mx[j][idx[j]] ){
				x[j] = mx[j][idx[j]];
				char c;
				c = gStrTitle[j][idx[j]];
				if( c != '\0' ){
					drawTitleCharStd( x[j], y[j], c );
					idx[j]++;
					x[j] = bgnX;
				}
			}
		}
	}

	for( long j = 0; j < 3; j++ ){
		if( gStrTitle[j][idx[j]] != '\0' ){
			drawTitleCharStd( x[j], y[j],
					gStrTitle[j][idx[j]] );
		}
	}
}

////////////////////////////////////////////////////////////////
// �����ȥ���̤����� No.1
// long frame : ���ߤΥե졼��
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitle1( long frame )
{
	if( pTitleStyle == NULL )
		init();

	static long div_v = 16;
	if( frame == 0 )
		div_v = 8 + randm( 24 + 1 );

	for( long j = 0; j < len; j++ ){
		long xx = (w / 2) + ((len / 2 - j) * TITLE_FONT_DOT);
		x[0][j] = xx;
		x[1][j] = xx;
		x[2][j] = xx;
		y[0][j] = my[0][j] - (h / 2);
		y[1][j] = my[1][j];
		y[2][j] = my[2][j] + (h / 2);
	}

	for( long f = 0; f < frame; f++ ){
		for( long i = 0; i < 3; i++ ){
			for( long j = 0; j < len; j++ ){
				x[i][j] += (mx[i][j] - x[i][j]) / div_v;
				y[i][j] += (my[i][j] - y[i][j]) / div_v;
				x[i][j] += sgn_l( mx[i][j] - x[i][j] );
				y[i][j] += sgn_l( my[i][j] - y[i][j] );
			}
		}
	}

	drawTitleString();
}

////////////////////////////////////////////////////////////////
// �����ȥ���̤����� No.2
// long frame : ���ߤΥե졼��
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitle2( long frame )
{
	if( pTitleStyle == NULL )
		init();

	static long div_v = 16;
	if( frame == 0 )
		div_v = 4 + randm( 24 + 1 );

	for( long j = 0; j < len; j++ ){
		x[0][j] = mx[0][j] - (w * (j + 1));
		x[1][j] = mx[1][j] + (w * (j + 1) / 2);
		x[2][j] = mx[2][j] + (w * (len - j));
		y[0][j] = my[0][j];
		y[1][j] = my[1][j];
		y[2][j] = my[2][j];
	}

	for( long f = 0; f < frame; f++ ){
		for( long i = 0; i < 3; i++ ){
			for( long j = 0; j < len; j++ ){
				x[i][j] += (mx[i][j] - x[i][j]) / div_v;
				y[i][j] += (my[i][j] - y[i][j]) / div_v;
				x[i][j] += sgn_l( mx[i][j] - x[i][j] );
				y[i][j] += sgn_l( my[i][j] - y[i][j] );
			}
		}
	}

	drawTitleString();
}

////////////////////////////////////////////////////////////////
// �����ȥ���̤����� No.3
// long frame : ���ߤΥե졼��
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitle3( long frame )
{
	if( pTitleStyle == NULL )
		init();

	static long maxFrame = 100;
	if( frame == 0 )
		maxFrame = 50 + randm( 150 + 1 );

	for( long i = 0; i < 3; i++ ){
		for( long j = 0; j < len; j++ ){
			long ff;
			ff = maxFrame - frame;
			if( ff < 0 )
				ff = 0;
			long xx;
			xx = j - (len / 2);
			if( xx >= 0 )
				xx += 1;
			xx = xx * w * ff / maxFrame;
			x[i][j] = mx[i][j] + xx;
			y[i][j] = my[i][j];
		}
	}

	drawTitleString();
}

////////////////////////////////////////////////////////////////
// �����ȥ���̤����� No.4
// long frame : ���ߤΥե졼��
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitle4( long frame )
{
	if( pTitleStyle == NULL )
		init();

	// ��®��
	static long av = 1;
	if( frame == 0 )
		av = 1 + randm( 3 + 1 );

	// ȿȯΨ
	static rate_t repulsion = 50;
	if( frame == 0 )
		repulsion = 50 + randm( 25 + 1 );

	long v[3][16];
	for( long j = 0; j < len; j++ ){
		v[0][j] = - (j * av * 2);
		v[1][j] = + (j * av * 2);
		v[2][j] = + (j * av * 2);
	}

	for( long j = 0; j < len; j++ ){
		x[0][j] = mx[0][j] + 80;
		x[1][j] = mx[1][j] + (w / 2);
		x[2][j] = mx[2][j] + 80;

		y[0][j] = my[0][j] - (h / 2);
		y[1][j] = my[1][j];
		y[2][j] = my[2][j] + (h / 2);
	}

	for( long f = 0; f < frame; f++ ){
		for( long j = 0; j < len; j++ ){
			long i;

			// 0

			i = 0;
			v[i][j] += av;
			x[i][j] += 0;
			y[i][j] += v[i][j];
			if( y[i][j] > my[i][j] ){
				y[i][j] = my[i][j];
				v[i][j] *= -1;
				v[i][j] = v[i][j] * repulsion / _100_PERCENT;
			}
			x[i][j] += sgn_l( mx[i][j] - x[i][j] );
			y[i][j] += sgn_l( my[i][j] - y[i][j] );

			// 1

			i = 1;
			v[i][j] -= av;
			x[i][j] += v[i][j];
			y[i][j] += 0;
			if( x[i][j] < mx[i][j] ){
				x[i][j] = mx[i][j];
				v[i][j] *= -1;
				v[i][j] = v[i][j] * repulsion / _100_PERCENT;
			}
			x[i][j] += sgn_l( mx[i][j] - x[i][j] );
			y[i][j] += sgn_l( my[i][j] - y[i][j] );

			// 2

			i = 2;
			v[i][j] -= av;
			x[i][j] += 0;
			y[i][j] += v[i][j];
			if( y[i][j] < my[i][j] ){
				y[i][j] = my[i][j];
				v[i][j] *= -1;
				v[i][j] = v[i][j] * repulsion / _100_PERCENT;
			}
			x[i][j] += sgn_l( mx[i][j] - x[i][j] );
			y[i][j] += sgn_l( my[i][j] - y[i][j] );
		}
	}

	drawTitleString();
}

////////////////////////////////////////////////////////////////
// �����ȥ���̤����� No.5
// long frame : ���ߤΥե졼��
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitle5( long frame )
{
	// �饸����
	const double rad = DBL_PI / 180.0;

	// ��ž���
	static long rn = 2;
	if( frame == 0 )
		rn = 1 + randm( 4 + 1 );

	// ʸ����β�ž���٤�
	static long delay = 45;
	if( frame == 0 )
		delay = randm( 45 + 1 );

	const long maxFrame = 100;
	for( long i = 0; i < 3; i++ ){
		for( long j = 0; j < len; j++ ){
			long ff;
			ff = maxFrame - frame;
			if( ff < 0 )
				ff = 0;

			// Ⱦ��
			long r;
			r = w * ff / maxFrame;

			// ����
			long a;
			a = (rn * 360) * ff / maxFrame;
			a += delay * j;
			a %= 360;

			long xx, yy;
			xx = (long)(r * cos( (double)a * rad ));
			yy = (long)(r * sin( (double)a * rad ));

			x[i][j] = mx[i][j] + xx;
			y[i][j] = my[i][j] + yy;
		}
	}

	drawTitleString();
}

////////////////////////////////////////////////////////////////
// �����ȥ���̤����� No.6
// long frame : ���ߤΥե졼��
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitle6( long frame )
{
	const long maxX = 80;
	const long div = 4;

	static long delay = 4;
	if( frame == 0 )
		delay = 0 + randm( 8 + 1 );

	static long ay = 8;
	if( frame == 0 )
		ay = (2 * div) + randm( (4 * div) + 1 );

	static long vx = 2;
	if( frame == 0 )
		vx = 1 + randm( 3 + 1 );

	for( long i = 0; i < 3; i++ ){
		for( long j = 0; j < len; j++ ){
			long xx;
			xx = maxX - (vx * frame);
			xx += delay * j;
			if( xx < 0 )
				xx = 0;

			long yy;
			yy = (xx - ay) * (xx - ay) / div;

			x[i][j] = mx[i][j] + xx;
			y[i][j] = my[i][j] + yy - ((ay * ay) / div);
		}
	}

	drawTitleString();
}

////////////////////////////////////////////////////////////////
// �����ȥ�ʸ���������
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitleString()
{
	for( long i = 0; i < 3; i++ ){
		for( long j = 0; j < len; j++ ){
			if( gStrTitle[i][j] == '\0' )
				break;

			drawTitleCharStd( x[i][j], y[i][j],
					gStrTitle[i][j] );
		}
	}
}

////////////////////////////////////////////////////////////////
// �����ȥ�ʸ��������
// long x : X ��ɸ
// long y : Y ��ɸ
// char c : ʸ��
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitleCharStd( long x, long y, char c )
{
	// ��

	drawTitleChar( 0x38, 0x00, 0x00, x + 2, y + 2, c );
	drawTitleChar( 0x90, 0x58, 0x58, x - 2, y - 2, c );

	// ����

	drawTitleChar( 0x54, 0x00, 0x00, x, y, c );
}

////////////////////////////////////////////////////////////////
// �����ȥ�ʸ��������
// long r : �� (����ʬ)
// long g : �� (����ʬ)
// long b : �� (����ʬ)
// long x : X ��ɸ
// long y : Y ��ɸ
// char c : ʸ��
////////////////////////////////////////////////////////////////

void DemoTitle::drawTitleChar(
	long r, long g, long b,
	long x, long y, char c )
{
	char str[4 + 1];
	long	i = 0;
	str[i++] = c;
#ifdef D_MFC
	if( c == '&' )
		str[i++] = '&';
#endif // D_MFC
	str[i++] = '\0';

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
	GdkFont *font = gtk_style_get_font( pTitleStyle );
	GdkGC *gc = pTitleStyle->fg_gc[GTK_STATE_NORMAL];

	gdk_color_alloc( gdk_colormap_get_system(), &color );
	gdk_gc_set_foreground( gc, &color );

	gdk_draw_string( d, font, gc, x, y, str );
#endif // D_GTK

#ifdef D_MAC
//@@@
#endif // D_MAC

#ifdef D_IPHONE
	CGContextRef context = gPcgDun.getWBuf()->getPixMap();

	CGContextSaveGState(context);

	CGContextSetRGBFillColor( context, r / 255.0f, g / 255.0f, b / 255.0f, 255 / 255.0f );
	CGContextSetTextPosition( context, (CGFloat)x, (CGFloat)-y );

	CGContextShowText( context, str, str_len_std( str ) );
	CGContextDrawPath( context, kCGPathStroke );

	CGContextRestoreGState(context);
#endif // D_IPHONE

#ifdef D_MFC
	D3DCOLOR color = D3DCOLOR_XRGB( r, g, b );

	mD3Title.Begin();
	mD3Title.Draw( x, y, color, str );
	mD3Title.End();
#endif // D_MFC
}
