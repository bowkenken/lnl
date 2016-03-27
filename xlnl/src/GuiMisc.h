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
* $Id: GuiMisc.h,v 1.18 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_MISC_H
#define GUI_MISC_H	1

////////////////////////////////////////////////////////////////
// ����¾�ν���
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
