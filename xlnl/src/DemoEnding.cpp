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
* $Id: DemoEnding.cpp,v 1.21 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ����ǥ��󥰡��ǥ�
////////////////////////////////////////////////////////////////

#define DEMO_ENDING_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define	ENDING_EPILOGUE_TIME	48
#define	ENDING_SPACE_TIME	(5 * 60)

// ����ǥ��󥰲����Υǥ��쥯�ȥ�
#define STR_ENDING_EPILOGUE_DIR_NAME	"ending/epilogue/"

#define ENDING_FONT_POINT	24
#define ENDING_FONT_DOT	24

static const char *gStrEnding[EPILOGUE_LINE_MAX_N + 1];

static const long FRAME_PER_CHAR = 6;
static const long WAIT_FRAME_CHAR = 18;

#ifdef	D_MFC
static const long skipFrameEpilogue = 1;
static const long skipFrameSpace = 1;
#else
static const long skipFrameEpilogue = 6;
static const long skipFrameSpace = 1;
#endif

////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

DemoEnding::DemoEnding()
{
	pStyle = NULL;
	flagSkipScene = false;
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

DemoEnding::~DemoEnding()
{
#ifdef D_MFC
	if( pFont != NULL ){
		delete pFont;
		pFont = NULL;
	}
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// �����
////////////////////////////////////////////////////////////////

void DemoEnding::init()
{
	space.init();

	// ����ǥ��󥰲����θ���������

	WSCstring dir = STR_DEFAULT_GRAPH_DIR_NAME;
	WSCstring ext = STR_GRAPH_FILE_EXT;

	FileList::setStrDirSelGraph( dir );
	FileList ls;

	// ����ǥ��󥰲����򸡺�

	nMaxFile = 0;
	ls.reset( STR_ENDING_EPILOGUE_DIR_NAME, ext );
	long j = 0;
	for( j = 0; j < LOOP_MAX_1000; j++ ){
		WSCstring path = ls.next();
		if( path.getChars() <= 0 )
			break;
	}
	nMaxFile = j;

	// ����ǥ��󥰲���������������

	if( nMaxFile > 0 )
		nRandmSel = randm( nMaxFile );
	else
		nRandmSel = -1;

	// ����ǥ��󥰲������ɤ߹���

	if( nRandmSel > -1 ){
		ls.reset( STR_ENDING_EPILOGUE_DIR_NAME, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
			if( j == nRandmSel ){
				pcgEpilogue.init( path );
				break;
			}
		}
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

	WSCstring sFontPoint = ENDING_FONT_POINT * 10;
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

	LONG h = ENDING_FONT_DOT;
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
#endif // D_MFC

	initAnime();
}

////////////////////////////////////////////////////////////////
// ���˥᡼�����ν����
////////////////////////////////////////////////////////////////

void DemoEnding::initAnime()
{
	waitTime = 0;
	frame = 0;

	if( get_lang_kind() == LANG_KIND_ENGLISH ){
		x_dot = ENDING_FONT_DOT / 2;
		y_dot = ENDING_FONT_DOT;
	} else {
		x_dot = ENDING_FONT_DOT;
		y_dot = ENDING_FONT_DOT;
	}

	long k = 0;
	for( long i = 0; i < EPILOGUE_LINE_MAX_N; i++ ){
		gStrEnding[i] = &(MSG_EPILOGUE[k]);
		gStrEnding[i + 1] = NULL;

		for( long j = 0; j < EPILOGUE_MAX_LEN; j++ ){
			if( MSG_EPILOGUE[k] == '\0' )
				break;
			if( MSG_EPILOGUE[k] == '\n' ){
				k++;
				break;
			}
			k++;
		}
		if( MSG_EPILOGUE[k] == '\0' )
			break;
	}

	len = 1;
	for( long i = 0; i < EPILOGUE_LINE_MAX_N; i++ ){
		if( gStrEnding[i] == NULL )
			break;

		long k = 0;
		long j = 0;
		for( ; j < EPILOGUE_MAX_LEN; j++ ){
			if( gStrEnding[i][k] == '\0' )
				break;
			if( gStrEnding[i][k] == '\n' ){
				k++;
				break;
			}

			k += get_next_char_len( &(gStrEnding[i][k]) );
		}

		baseX[i] = j * x_dot;

		len = max_l( len, j );
	}
}

////////////////////////////////////////////////////////////////
// ����ǥ��󥰲��̤�����
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoEnding::draw()
{
	frame++;

	if( get_scene() == SCENE_N_ENDING ){
		gPcgDun.scrollTile( 0, 0 );

		// �������ڤ��ؤ�
		waitTime = 0;
		change_scene_gui( SCENE_N_ENDING_EPILOGUE );
	}

	// ���ԥ���

	if( get_scene() == SCENE_N_ENDING_EPILOGUE ){
		// �����
		if( waitTime <= 0 ){
			waitTime = time( NULL ) + ENDING_EPILOGUE_TIME;
			frame = 0;
		}

		// �ե졼���ְ���
		if( (frame % skipFrameEpilogue) != 0 )
			return true;

		if( !flagSkipScene && (time( NULL ) < waitTime) ){
			// ����
			return drawEpilogue();
		} else {
			flagSkipScene = false;

			// �������ڤ��ؤ�
			waitTime = 0;
			change_scene_gui( SCENE_N_ENDING_SPACE );
		}
	}

	// ����

	if( get_scene() == SCENE_N_ENDING_SPACE ){
		// �����
		if( waitTime <= 0 ){
			waitTime = time( NULL ) + ENDING_SPACE_TIME;
			frame = 0;
		}

		// �ե졼���ְ���
		if( (frame % skipFrameSpace) != 0 )
			return true;

		if( !flagSkipScene && (time( NULL ) < waitTime) ){
			// ����
			return drawSpace( false );
		} else {
			flagSkipScene = false;

			// �������ڤ��ؤ�
			waitTime = 0;
			change_scene_gui( SCENE_N_ENDING_STAFF_ROLL );
		}
	}

	// �����åա�����

	if( get_scene() == SCENE_N_ENDING_STAFF_ROLL ){
		// �ե졼���ְ���
		if( (frame % skipFrameSpace) != 0 )
			return true;

		if( !flagSkipScene ){
			// ����
			return drawSpace( true );
		} else {
			flagSkipScene = false;

			// �������ڤ��ؤ�
			waitTime = 0;
			change_scene_gui( SCENE_N_ENDING_END );
		}
	}

	// The End

	if( get_scene() == SCENE_N_ENDING_END ){
		// �ե졼���ְ���
		if( (frame % skipFrameSpace) != 0 )
			return true;

		// ����
		return drawSpace( true );
	}

	return true;
}

////////////////////////////////////////////////////////////////
// ���ԥ���������
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoEnding::drawEpilogue()
{
	if( nRandmSel <= -1 )
		return false;

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

	long ww = pcgEpilogue.getWidth();
	long hh = pcgEpilogue.getHeight();
	long xx = sx + (sw - ww) / 2;
	long yy = sy + sh - hh;

	pcgEpilogue.draw( gPcgDun.getWBuf(), xx, yy, ww, hh );

	// ���ȡ��꡼������

	drawEpilogueStory( frame );

	return true;
}

////////////////////////////////////////////////////////////////
// ���������
// bool flagDrawStaffRoll : �����åա���������褹�뤫?
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoEnding::drawSpace( bool flagDrawStaffRoll )
{
	return space.draw( flagDrawStaffRoll );
}

////////////////////////////////////////////////////////////////
// ���ԥ��������� (���ȡ��꡼)
// long frame : ���ߤΥե졼��
////////////////////////////////////////////////////////////////

void DemoEnding::drawEpilogueStory( long frame )
{
	if( pStyle == NULL )
		init();

	long n = 0;
	long nDraw;
	if( get_lang_kind() == LANG_KIND_ENGLISH )
		nDraw = (2 * frame / FRAME_PER_CHAR) - WAIT_FRAME_CHAR;
	else
		nDraw = (frame / FRAME_PER_CHAR) - WAIT_FRAME_CHAR;

	long sw = gPcgDun.getScrollBarW();
	long sh = gPcgDun.getScrollBarH();

	for( long i = 0; i < EPILOGUE_LINE_MAX_N; i++ ){
		if( gStrEnding[i] == NULL )
			break;

		long k = 0;
		for( long j = 0; j < len; j++ ){
			if( gStrEnding[i][k] == '\0' )
				break;
			if( gStrEnding[i][k] == '\n' ){
				k++;
				break;
			}

			if( n < nDraw ){
				long bx = (sw - baseX[i]) / 2;
				long by = sh / 2;
				long mx = bx + (j * x_dot);
				long my = by + (i * y_dot);
				x[i][j] = mx;
				y[i][j] = my;
			} else {
				x[i][j] = sw * 2;
				y[i][j] = sh * 2;
			}

			n++;
			k += get_next_char_len( &(gStrEnding[i][k]) );
		}
	}

	drawString();
}

////////////////////////////////////////////////////////////////
// ����ǥ���ʸ���������
////////////////////////////////////////////////////////////////

void DemoEnding::drawString()
{
	for( long i = 0; i < EPILOGUE_LINE_MAX_N; i++ ){
		if( gStrEnding[i] == NULL )
			break;

		long k = 0;
		for( long j = 0; j < len; j++ ){
			if( gStrEnding[i][k] == '\0' )
				break;
			if( gStrEnding[i][k] == '\n' ){
				k++;
				break;
			}

			const char *p = &(gStrEnding[i][k]);

			drawCharStd( x[i][j], y[i][j],
					get_next_char_str( p ) );

			k += get_next_char_len( p );
		}
	}
}

////////////////////////////////////////////////////////////////
// ����ǥ���ʸ��������
////////////////////////////////////////////////////////////////

void DemoEnding::drawCharStd( long x, long y, const char *str )
{
	drawChar( 0x00, 0x00, 0x00, x + 1, y + 1, str );
	drawChar( 0x00, 0x00, 0x00, x - 1, y - 1, str );
	drawChar( 0xff, 0xff, 0xff, x, y, str );
}

////////////////////////////////////////////////////////////////
// ����ǥ���ʸ��������
////////////////////////////////////////////////////////////////

void DemoEnding::drawChar(
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
	D3DCOLOR color = D3DCOLOR_XRGB( r, g, b );

	mD3.Begin();
	mD3.Draw( x, y, color, str );
	mD3.End();
#endif // D_MFC
}

////////////////////////////////////////////////////////////////
// ����ǥ��󥰤Υ�����򥹥��å�
////////////////////////////////////////////////////////////////

void DemoEnding::skipScene()
{
	flagSkipScene = true;
}
