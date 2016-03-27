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
* $Id: DemoCutIn.h,v 1.6 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_CUT_IN_H
#define DEMO_CUT_IN_H

////////////////////////////////////////////////////////////////
// ���åȥ��󡦥ǥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include "GtkWSCstring.h"
#endif /* D_GTK */

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif // D_MFC

#include "Pcg.h"

////////////////////////////////////////////////////////////////

class DemoCutIn {
public:

private:
	// ����������Ф줿���åȥ�������Υե������ֹ�
	long nFileSelN;
	// ���åȥ�������Υե������
	long nFileMaxN;
	// ���åȥ���β���
	Pcg pcg;

	// �������
	// ��(��)ü�� -100%
	// �濴�� 0%
	// ��(��)ü�� +100%
	rate_t rateBgnX;
	rate_t rateBgnY;
	rate_t rateEndX;
	rate_t rateEndY;

public:
	DemoCutIn();
	~DemoCutIn();
	void init( WSCstring dirName );

	void setPos( rate_t bx, rate_t by, rate_t ex, rate_t ey );

	bool drawCutIn( long frame, long maxFrame );
	bool drawCutOut( long frame, long maxFrame );
	bool draw( long frame, long maxFrame, bool flagCutIn );

private:
};

#endif // DEMO_CUT_IN_H
