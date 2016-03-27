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
* $Id: GuiMisc.cpp,v 1.23 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ����¾�ν���
////////////////////////////////////////////////////////////////

#include "gmain.h"
#include "gmain-prot.h"

#include "GuiMisc.h"

#define FLG_CHK_ALLOC_COLOR_MAP	0

const int PEN_WIDTH_BOLD = 2;
const int PEN_WIDTH_NORMAL = 1;

////////////////////////////////////////////////////////////////
// �ڥ��°�������ꤹ��
// GdkGC *fgGc : ���ʿ��Υ���ե��å�������ƥ�����
// GdkGC *bgGc : �طʿ��Υ���ե��å�������ƥ�����
// curs_attr_t *attr : °��
////////////////////////////////////////////////////////////////

#ifdef D_GTK
void SetPenAttr( GdkGC *fgGc, GdkGC *bgGc, curs_attr_t *attr )
{
	if( attr == NULL )
		return;

	GdkColor colorFg;
	GdkColor colorBg;

	CvColorRGB( &colorFg, attr->fg );
	CvColorRGB( &colorBg, attr->bg );

	if( (attr->attr) & A_REVERSE ){
		if( fgGc != NULL ){
			gdk_gc_set_foreground( fgGc, &colorBg );
			gdk_gc_set_background( fgGc, &colorFg );
		}
		if( bgGc != NULL ){
			gdk_gc_set_foreground( bgGc, &colorFg );
			gdk_gc_set_background( bgGc, &colorBg );
		}
	} else {
		if( fgGc != NULL ){
			gdk_gc_set_foreground( fgGc, &colorFg );
			gdk_gc_set_background( fgGc, &colorBg );
		}
		if( bgGc != NULL ){
			gdk_gc_set_foreground( bgGc, &colorBg );
			gdk_gc_set_background( bgGc, &colorFg );
		}
	}
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// ���ʿ���°�������ꤹ��
// CDC *dc : �ǥХ���������ƥ�����
// CBrush *br : �֥饷
// curs_attr_t *attr : °��
////////////////////////////////////////////////////////////////

#ifdef D_MFC
void SetPenAttrFg(
	CDC *dc, CPen *pen, CBrush *br, curs_attr_t *attr
)
{
	if( attr == NULL )
		return;

	static COLORREF colorFg;
	static COLORREF colorBg;

	CvColorRGB( &colorFg, attr->fg );
	CvColorRGB( &colorBg, attr->bg );

	int penWidth = PEN_WIDTH_NORMAL;
	if( (attr->attr) & A_BOLD )
		penWidth = PEN_WIDTH_BOLD;
	else
		penWidth = PEN_WIDTH_NORMAL;

	if( (attr->attr) & A_REVERSE ){
		if( dc != NULL ){
			if( pen != NULL ){
				pen->CreatePen( PS_SOLID, penWidth, colorBg );
				dc->SelectObject( pen );
			}
			dc->SetTextColor( colorBg );
			dc->SetBkColor( colorFg );
		}

		if( br != NULL )
			br->CreateSolidBrush( colorBg );
	} else {
		if( dc != NULL ){
			if( pen != NULL ){
				pen->CreatePen( PS_SOLID, penWidth, colorFg );
				dc->SelectObject( pen );
			}
			dc->SetTextColor( colorFg );
			dc->SetBkColor( colorBg );
		}

		if( br != NULL )
			br->CreateSolidBrush( colorFg );
	}
}
#endif // D_MFC

////////////////////////////////////////////////////////////////
// �طʿ���°�������ꤹ��
// CDC *dc : �ǥХ���������ƥ�����
// CBrush *br : �֥饷
// curs_attr_t *attr : °��
////////////////////////////////////////////////////////////////

#ifdef D_MFC
void SetPenAttrBg(
	CDC *dc, CPen *pen, CBrush *br, curs_attr_t *attr
)
{
	if( attr == NULL )
		return;

	static COLORREF colorFg;
	static COLORREF colorBg;

	CvColorRGB( &colorFg, attr->fg );
	CvColorRGB( &colorBg, attr->bg );

	int penWidth = PEN_WIDTH_NORMAL;
	if( (attr->attr) & A_BOLD )
		penWidth = PEN_WIDTH_BOLD;
	else
		penWidth = PEN_WIDTH_NORMAL;

	if( (attr->attr) & A_REVERSE ){
		if( dc != NULL ){
			if( pen != NULL ){
				pen->CreatePen( PS_SOLID, penWidth, colorFg );
				dc->SelectObject( pen );
			}
			dc->SetTextColor( colorFg );
			dc->SetBkColor( colorBg );
		}

		if( br != NULL )
			br->CreateSolidBrush( colorFg );
	} else {
		if( dc != NULL ){
			if( pen != NULL ){
				pen->CreatePen( PS_SOLID, penWidth, colorBg );
				dc->SelectObject( pen );
			}
			dc->SetTextColor( colorBg );
			dc->SetBkColor( colorFg );
		}

		if( br != NULL )
			br->CreateSolidBrush( colorBg );
	}
}
#endif // D_MFC

////////////////////////////////////////////////////////////////
// curses �ο��ֹ椫�� GDK �ο����Ѵ�
// GdkColor *color : GDK �ο�
// int n : ���ֹ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
void CvColorRGB( GdkColor *color, int n )
{
	if( color == NULL )
		return;

	long map_n = -1;

	switch( n ){
	case COLOR_BLACK:
		color->red = 0x0000;
		color->green = 0x0000;
		color->blue = 0x0000;
		map_n = 0;
		break;
	case COLOR_RED:
		color->red = 0xffff;
		color->green = 0x0000;
		color->blue = 0x0000;
		map_n = 1;
		break;
	case COLOR_GREEN:
		color->red = 0x0000;
		color->green = 0xffff;
		color->blue = 0x0000;
		map_n = 2;
		break;
	case COLOR_YELLOW:
		color->red = 0xffff;
		color->green = 0xffff;
		color->blue = 0x0000;
		map_n = 3;
		break;
	case COLOR_BLUE:
		color->red = 0x0000;
		color->green = 0x0000;
		color->blue = 0xffff;
		map_n = 4;
		break;
	case COLOR_MAGENTA:
		color->red = 0xffff;
		color->green = 0x0000;
		color->blue = 0xffff;
		map_n = 5;
		break;
	case COLOR_CYAN:
		color->red = 0x0000;
		color->green = 0xffff;
		color->blue = 0xffff;
		map_n = 6;
		break;
	case COLOR_WHITE:
		color->red = 0xffff;
		color->green = 0xffff;
		color->blue = 0xffff;
		map_n = 7;
		break;
	default:
		return;
	}

#if FLG_CHK_ALLOC_COLOR_MAP
	static bool flg_alloc_color_map[8] = {
		false, false, false, false,
		false, false, false, false,
	};

	if( (map_n > -1) && !flg_alloc_color_map[map_n] ){
		gdk_color_alloc( gdk_colormap_get_system(), color );
		flg_alloc_color_map[map_n] = true;
	}
#else //FLG_CHK_ALLOC_COLOR_MAP
	if( map_n > -1 )
		gdk_color_alloc( gdk_colormap_get_system(), color );
#endif //FLG_CHK_ALLOC_COLOR_MAP
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// curses �ο��ֹ椫�� MFC �ο����Ѵ�
// COLORREF *color : MFC �ο�
// int n : ���ֹ�
////////////////////////////////////////////////////////////////

#ifdef D_MFC
void CvColorRGB( COLORREF *color, int n )
{
	if( color == NULL )
		return;

	switch( n ){
	default:
	case COLOR_BLACK:
		*color = RGB( 0x0000, 0x0000, 0x0000 );
		break;
	case COLOR_RED:
		*color = RGB( 0xffff, 0x0000, 0x0000 );
		break;
	case COLOR_GREEN:
		*color = RGB( 0x0000, 0xffff, 0x0000 );
		break;
	case COLOR_YELLOW:
		*color = RGB( 0xffff, 0xffff, 0x0000 );
		break;
	case COLOR_BLUE:
		*color = RGB( 0x0000, 0x0000, 0xffff );
		break;
	case COLOR_MAGENTA:
		*color = RGB( 0xffff, 0x0000, 0xffff );
		break;
	case COLOR_CYAN:
		*color = RGB( 0x0000, 0xffff, 0xffff );
		break;
	case COLOR_WHITE:
		*color = RGB( 0xffff, 0xffff, 0xffff );
		break;
	}
}
#endif // D_MFC

////////////////////////////////////////////////////////////////
// curses �ο��ֹ椫�� DirectX �ο����Ѵ�
// D3DCOLOR *color : DirectX �ο�
// int n : ���ֹ�
////////////////////////////////////////////////////////////////

#ifdef D_MFC
void CvColorRGBD3( D3DCOLOR *color, int n )
{
	if( color == NULL )
		return;

	switch( n ){
	default:
	case COLOR_BLACK:
		*color = D3DCOLOR_XRGB( 0x00, 0x00, 0x00 );
		break;
	case COLOR_RED:
		*color = D3DCOLOR_XRGB( 0xff, 0x00, 0x00 );
		break;
	case COLOR_GREEN:
		*color = D3DCOLOR_XRGB( 0x00, 0xff, 0x00 );
		break;
	case COLOR_YELLOW:
		*color = D3DCOLOR_XRGB( 0xff, 0xff, 0x00 );
		break;
	case COLOR_BLUE:
		*color = D3DCOLOR_XRGB( 0x00, 0x00, 0xff );
		break;
	case COLOR_MAGENTA:
		*color = D3DCOLOR_XRGB( 0xff, 0x00, 0xff );
		break;
	case COLOR_CYAN:
		*color = D3DCOLOR_XRGB( 0x00, 0xff, 0xff );
		break;
	case COLOR_WHITE:
		*color = D3DCOLOR_XRGB( 0xff, 0xff, 0xff );
		break;
	}
}
#endif // D_MFC

////////////////////////////////////////////////////////////////
// ���ʿ������ꤹ��
// GdkGC *gc : ���ꤹ�륰��ե��å�������ƥ�����
// long r : ��
// long g : ��
// long b : ��
////////////////////////////////////////////////////////////////

#ifdef D_GTK
void SetFgColor( GdkGC *gc, long r, long g, long b )
{
	GdkColor color;
	color.red = r;
	color.green = g;
	color.blue = b;

	gdk_color_alloc( gdk_colormap_get_system(), &color );
	gdk_gc_set_foreground( gc, &color );
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// �طʿ������ꤹ��
// GdkGC *gc : ���ꤹ�륰��ե��å�������ƥ�����
// long r : ��
// long g : ��
// long b : ��
////////////////////////////////////////////////////////////////

#ifdef D_GTK
void SetBgColor( GdkGC *gc, long r, long g, long b )
{
	GdkColor color;
	color.red = r;
	color.green = g;
	color.blue = b;

	gdk_color_alloc( gdk_colormap_get_system(), &color );
	gdk_gc_set_background( gc, &color );
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// �ܥ����Υ�٥���֤�
// GtkButton *btn : �ܥ���
////////////////////////////////////////////////////////////////

#ifdef D_GTK
GtkLabel *get_label_from_button( GtkButton *btn )
{
	if( btn == NULL )
		return NULL;

	GList *ls = gtk_container_children( GTK_CONTAINER( btn ) );
	if( ls == NULL )
		return NULL;

	GList *p = g_list_nth( ls, 0 );
	if( p == NULL )
		return NULL;

	GtkLabel *label = GTK_LABEL( p->data );
	if( label == NULL )
		return NULL;

	return label;
}
#endif // D_GTK

////////////////////////////////////////////////////////////////
// �ܥ����Υƥ����Ȥ����ꤹ��
// GtkButton *btn : �ܥ���
// const char *str : �ƥ����Ȥ����ꤹ��ʸ����
// double HAlignment : �ƥ����Ȥο�ʿ�� 0.0 �� 1.0 �δ�
// double VAlignment : �ƥ����Ȥο�ľ�� 0.0 �� 1.0 �δ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
void set_label_text_button(
	GtkButton *btn, const char *str,
	double HAlignment, double VAlignment
)
{
	if( btn == NULL )
		return;

	GList *ls = gtk_container_children(
			GTK_CONTAINER( btn ) );
	if( ls == NULL )
		return;

	GList *p = g_list_nth( ls, 0 );
	if( p == NULL )
		return;

	GtkLabel *label = GTK_LABEL( p->data );
	if( label == NULL )
		return;

	gtk_misc_set_alignment( GTK_MISC( label ), HAlignment, VAlignment );
	if( str == NULL )
		gtk_label_set_text( label, "" );
	else
		gtk_label_set_text( label, str );
}
#endif // D_GTK
