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
* $Id: DemoLastBoss.h,v 1.7 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_LAST_BOSS_H
#define DEMO_LAST_BOSS_H

////////////////////////////////////////////////////////////////
// �饹�ܥ��Υǥ�
////////////////////////////////////////////////////////////////

#ifdef D_GTK
# include "GtkWSCstring.h"
#endif /* D_GTK */

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif // D_MFC

#include "Pcg.h"
#include "DemoCutIn.h"

////////////////////////////////////////////////////////////////

class DemoLastBoss {
public:

private:
	DemoCutIn CutInExel;
	DemoCutIn CutInExeler;
	DemoCutIn CutInXex;

	long frame;
	bool flagDone;

public:
	DemoLastBoss();
	~DemoLastBoss();
	void init();
	void reset();

	bool draw();
	bool drawCutIn(
		bool flagExel, bool flagExeler, bool flagXex );
	bool drawCutOut(
		bool flagExel, bool flagExeler, bool flagXex );

	bool incFrame( long maxFrame );
	bool checkSkipFrame();

	bool checkDone();

private:
	bool drawCutIn();
};

#endif // DEMO_LAST_BOSS_H
