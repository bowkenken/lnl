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
* $Id: DemoCutIn.cpp,v 1.10 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// ���åȥ��󡦥ǥ�
////////////////////////////////////////////////////////////////

#define DEMO_CUT_IN_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

// ���åȥ�������Υǥ��쥯�ȥ�
#define STR_CUT_IN_DIR_NAME	"cut_in/"

////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

DemoCutIn::DemoCutIn()
{
	nFileSelN = 0;
	nFileMaxN = 0;

	rateBgnX = (rate_t)0;
	rateBgnY = (rate_t)0;
	rateEndX = (rate_t)0;
	rateEndY = (rate_t)0;
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

DemoCutIn::~DemoCutIn()
{
}

////////////////////////////////////////////////////////////////
// �����
// WSCstring dirName : �����Υǥ��쥯�ȥ�̾
////////////////////////////////////////////////////////////////

void DemoCutIn::init( WSCstring dirName )
{
	// ���åȥ�������θ���������

	WSCstring dir = STR_DEFAULT_GRAPH_DIR_NAME;
	WSCstring ext = STR_GRAPH_FILE_EXT;
	WSCstring pcgPath = FileList::jointDir(
			STR_CUT_IN_DIR_NAME, dirName );

	FileList::setStrDirSelGraph( dir );
	FileList ls;

	// ���åȥ�������򸡺�

	{
		nFileMaxN = 0;

		ls.reset( pcgPath, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
		}

		nFileMaxN = j;
	}

	// ���åȥ������������������

	if( nFileMaxN > 0 )
		nFileSelN = gui_randm( nFileMaxN );
	else
		nFileSelN = -1;

	// ���åȥ���������ɤ߹���

	if( nFileSelN > -1 ){
		ls.reset( pcgPath, ext );
		long j = 0;
		for( j = 0; j < LOOP_MAX_1000; j++ ){
			WSCstring path = ls.next();
			if( path.getChars() <= 0 )
				break;
			if( j == nFileSelN ){
				pcg.init( path );
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////
// ���åȥ��󳫻ϡ���λ��ɸ������
// rate_t bx : ���� X ��ɸ��Ψ
// rate_t by : ���� Y ��ɸ��Ψ
// rate_t ex : ��λ X ��ɸ��Ψ
// rate_t ey : ��λ Y ��ɸ��Ψ
////////////////////////////////////////////////////////////////

void DemoCutIn::setPos( rate_t bx, rate_t by, rate_t ex, rate_t ey )
{
	rateBgnX = bx;
	rateBgnY = by;
	rateEndX = ex;
	rateEndY = ey;
}

////////////////////////////////////////////////////////////////
// ���åȥ��������
// long frame : ���ߤΥե졼��
// long maxFrame : ��λ�ե졼��
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoCutIn::drawCutIn( long frame, long maxFrame )
{
	return draw( frame, maxFrame, true );
}

////////////////////////////////////////////////////////////////
// ���åȥ����Ȥ�����
// long frame : ���ߤΥե졼��
// long maxFrame : ��λ�ե졼��
// return : ���顼��̵���ä���?
////////////////////////////////////////////////////////////////

bool DemoCutIn::drawCutOut( long frame, long maxFrame )
{
	return draw( frame, maxFrame, false );
}

////////////////////////////////////////////////////////////////
// ���åȥ��󡿥����Ȥ�����
// long frame : ���ߤΥե졼��
// long maxFrame : ��λ�ե졼��
// return : ���åȥ��󡿥����Ȥ���λ������?
////////////////////////////////////////////////////////////////

bool DemoCutIn::draw( long frame, long maxFrame, bool flagCutIn )
{
	bool flagDone = false;

	if( g_flg_skip_demo_cut_in )
		return true;

	if( frame < 0 )
		frame = 0;
	if( frame > maxFrame ){
		frame = maxFrame;
		flagDone = true;
	}

	if( !flagCutIn )
		frame = maxFrame - frame;

	long x = gPcgDun.getScrollBarX();
	long y = gPcgDun.getScrollBarY();
	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();

	long pcgW = pcg.getWidth();
	long pcgH = pcg.getHeight();
	rate_t rateX = ((rateEndX - rateBgnX) * frame / maxFrame)
			+ rateBgnX;
	rate_t rateY = ((rateEndY - rateBgnY) * frame / maxFrame)
			+ rateBgnY;
	long xx = ((w / 2) * rateX / _100_PERCENT) + ((w - pcgW) / 2);
	long yy = ((h / 2) * rateY / _100_PERCENT) + ((h - pcgH) / 2);
	xx += x;
	yy += y;

	pcg.draw( gPcgDun.getWBuf(), xx, yy, pcgW, pcgH );

	return flagDone;
}
