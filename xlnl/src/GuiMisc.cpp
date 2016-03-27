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
* $Id: GuiMisc.cpp,v 1.23 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// その他の処理
////////////////////////////////////////////////////////////////

#include "gmain.h"
#include "gmain-prot.h"

#include "GuiMisc.h"

#define FLG_CHK_ALLOC_COLOR_MAP	0

const int PEN_WIDTH_BOLD = 2;
const int PEN_WIDTH_NORMAL = 1;

////////////////////////////////////////////////////////////////
// ペンの属性を設定する
// GdkGC *fgGc : 前景色のグラフィック・コンテキスト
// GdkGC *bgGc : 背景色のグラフィック・コンテキスト
// curs_attr_t *attr : 属性
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
// 前景色の属性を設定する
// CDC *dc : デバイス・コンテキスト
// CBrush *br : ブラシ
// curs_attr_t *attr : 属性
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
// 背景色の属性を設定する
// CDC *dc : デバイス・コンテキスト
// CBrush *br : ブラシ
// curs_attr_t *attr : 属性
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
// curses の色番号から GDK の色に変換
// GdkColor *color : GDK の色
// int n : 色番号
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
// curses の色番号から MFC の色に変換
// COLORREF *color : MFC の色
// int n : 色番号
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
// curses の色番号から DirectX の色に変換
// D3DCOLOR *color : DirectX の色
// int n : 色番号
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
// 前景色を設定する
// GdkGC *gc : 設定するグラフィック・コンテキスト
// long r : 赤
// long g : 緑
// long b : 青
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
// 背景色を設定する
// GdkGC *gc : 設定するグラフィック・コンテキスト
// long r : 赤
// long g : 緑
// long b : 青
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
// ボタン上のラベルを返す
// GtkButton *btn : ボタン
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
// ボタン上のテキストを設定する
// GtkButton *btn : ボタン
// const char *str : テキストに設定する文字列
// double HAlignment : テキストの水平寄せ 0.0 〜 1.0 の間
// double VAlignment : テキストの垂直寄せ 0.0 〜 1.0 の間
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
