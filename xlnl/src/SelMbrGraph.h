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
* $Id: SelMbrGraph.h,v 1.8 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef SEL_MBR_GRAPH_H
#define SEL_MBR_GRAPH_H	1

////////////////////////////////////////////////////////////////
// ���С��Υ���ե��å����ѥ����������
////////////////////////////////////////////////////////////////

#include "misc.h"
#include "party.h"
#include "scene.h"
#include "scene-prot.h"

#include "PcgDun.h"

#ifdef D_WS
# include <WSCstring.h>
#endif //D_WS

#ifdef D_GTK
# include "GtkWSCstring.h"
#endif //D_GTK

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif //D_MFC

////////////////////////////////////////////////////////////////

class SelMbrGraph {

private:
	static const long nBaseColorR = 0xdddd;
	static const long nBaseColorG = 0xdddd;
	static const long nBaseColorB = 0xdddd;

	static const long nSelColorR = 0x0000;
	static const long nSelColorG = 0xdddd;
	static const long nSelColorB = 0xdddd;

	static const long nHighColorR = 0xffff;
	static const long nHighColorG = 0xffff;
	static const long nHighColorB = 0xffff;

	static const long nLowColorR = 0xbbbb;
	static const long nLowColorG = 0xbbbb;
	static const long nLowColorB = 0xbbbb;

	static const long nSelBorderW = 3;
	static const long nSelBorderH = 3;

	// ������Υ��С�
	mbr_t *pMbr;

	// �ѥ����󡦥ꥹ�Ȥ���Ƭ
	Pcg *pPtnHead;
	// �ѥ�����κ����
	long nPtnMaxN;
	// ������Υѥ����󡦥���ǥå���
	long nPtnSelN;

	// �ڤ��ؤ������Υ�����ΥХå��å�
	scene_n_t nPreScene;
	// �ڤ��ؤ������Υޥå�ɽ����ɸ
	long nPreMapX;
	long nPreMapY;

	// �ѥ������ɽ��������
	long nSizeX, nSizeY;
	long nSizeMaxX, nSizeMaxY;

	// �ѥ�����̾�Υե����
#ifdef D_GTK
	GdkFont *font;
#endif // D_GTK

public:
	SelMbrGraph();
	~SelMbrGraph();

	bool exec( mbr_t *mbr );
	long sel( long sx, long sy );
	void ok();
	void cancel();

	void redraw();
	void draw();

private:
	void close();

	void drawAllChr();
	void drawChr(
		long x, long y, long w, long h,
		Pcg *p, bool flagSel );
	void flush();
};

#endif /* SEL_MBR_GRAPH_H */
