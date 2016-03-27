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
* $Id: GuiMisc.h,v 1.18 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_MISC_H
#define GUI_MISC_H	1

////////////////////////////////////////////////////////////////
// その他の処理
////////////////////////////////////////////////////////////////

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
#endif // D_GTK

#ifdef D_MFC
# include "xlnl-dows/stdafx.h"
# include "xlnl-dows/Dir3d.h"
#endif // D_MFC

#include "curs.h"

////////////////////////////////////////////////////////////////

#ifdef D_GTK
void SetPenAttr( GdkGC *fgGc, GdkGC *bgGc, curs_attr_t *attr );
void CvColorRGB( GdkColor *color, int n );
void SetFgColor( GdkGC *gc, long r, long g, long b );
void SetBgColor( GdkGC *gc, long r, long g, long b );

GtkLabel *get_label_from_button( GtkButton *btn );
void set_label_text_button(
	GtkButton *btn, const char *str,
	double HAlignment, double VAlignment
);
#endif // D_GTK

#ifdef D_MFC
void SetPenAttrFg(
	CDC *dc, CPen *pen, CBrush *br, curs_attr_t *attr
);
void SetPenAttrBg(
	CDC *dc, CPen *pen, CBrush *br, curs_attr_t *attr
);
void CvColorRGB( COLORREF *color, int n );
void CvColorRGBD3( D3DCOLOR *color, int n );
#endif // D_MFC

#endif /* GUI_MISC_H */
