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
* $Id: DemoLastBoss.cpp,v 1.14 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// �饹�ܥ��Υǥ�
////////////////////////////////////////////////////////////////

#define DEMO_LAST_BOSS_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

// ���åȥ�������Υǥ��쥯�ȥ�
#define STR_CUT_IN_DIR_NAME_EXEL	"exel/"
#define STR_CUT_IN_DIR_NAME_EXELER	"exeler/"
#define STR_CUT_IN_DIR_NAME_XEX	"xex/"

static const long nCutInMaxFrame = TIMER_FRAME * 60 / 60;
static const long nCutOutMaxFrame = TIMER_FRAME * 60 / 60;

#ifdef	D_MFC
static const long skipFrameLastBoss = 1;
#else
static const long skipFrameLastBoss = 6;
#endif

////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

DemoLastBoss::DemoLastBoss()
{
	frame = 0;
	flagDone = false;
}

////////////////////////////////////////////////////////////////
// �ǥ��ȥ饯��
////////////////////////////////////////////////////////////////

DemoLastBoss::~DemoLastBoss()
{
}

////////////////////////////////////////////////////////////////
// �����
////////////////////////////////////////////////////////////////

void DemoLastBoss::init()
{
	// ���åȥ���������ɤ߹���

	CutInExel.init( STR_CUT_IN_DIR_NAME_EXEL );
	CutInExeler.init( STR_CUT_IN_DIR_NAME_EXELER );
	CutInXex.init( STR_CUT_IN_DIR_NAME_XEX );

	CutInExel.setPos( -125, 0, -50, 0 );
	CutInExeler.setPos( +125, 0, +50, 0 );
	CutInXex.setPos( 0, -125, 0, -50 );

	reset();
}

////////////////////////////////////////////////////////////////
// �ǥ�Υꥻ�å�
////////////////////////////////////////////////////////////////

void DemoLastBoss::reset()
{
	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
	case LAST_SCENE_N_ENCOUNTER:
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	//case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
	case LAST_SCENE_N_EXEL:
	case LAST_SCENE_N_EXEL_ENTER:
	case LAST_SCENE_N_EXEL_CUT_IN:
	//case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_CUT_OUT:
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
	case LAST_SCENE_N_EXEL_BATTLE:
	//case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER:
	case LAST_SCENE_N_EXELER_CUT_IN:
	//case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_CUT_OUT:
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
	case LAST_SCENE_N_EXELER_BATTLE:
	//case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX:
	case LAST_SCENE_N_XEX_CUT_IN:
	//case LAST_SCENE_N_XEX_WORDS:
	case LAST_SCENE_N_XEX_CUT_OUT:
	case LAST_SCENE_N_XEX_CUT_END:
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
	case LAST_SCENE_N_XX_BATTLE:
	case LAST_SCENE_N_XX_DIE:
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		frame = 0;
		break;
	case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX_WORDS:
		frame = nCutInMaxFrame;
		break;
	}

	flagDone = false;
}

////////////////////////////////////////////////////////////////
// �ǥ������
// return : ���褬��λ������?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::draw()
{
	// 1 �٤����¹Ԥ��ʤ��������ɬ�� true ���֤�
	bool flag = true;

	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
	case LAST_SCENE_N_ENCOUNTER:
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
		flag = drawCutIn( true, true, true );
		break;
	case LAST_SCENE_N_ENCOUNTER_WORDS:
		drawCutIn( true, true, true );
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
		flag = drawCutOut( true, true, true );
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
	case LAST_SCENE_N_EXEL:
	case LAST_SCENE_N_EXEL_ENTER:
		break;
	case LAST_SCENE_N_EXEL_CUT_IN:
		flag = drawCutIn( true, false, false );
		break;
	case LAST_SCENE_N_EXEL_WORDS:
		drawCutIn( true, false, false );
		break;
	case LAST_SCENE_N_EXEL_CUT_OUT:
		flag = drawCutOut( true, false, false );
		break;
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
	case LAST_SCENE_N_EXEL_BATTLE:
	case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER:
		break;
	case LAST_SCENE_N_EXELER_CUT_IN:
		flag = drawCutIn( false, true, false );
		break;
	case LAST_SCENE_N_EXELER_WORDS:
		drawCutIn( false, true, false );
		break;
	case LAST_SCENE_N_EXELER_CUT_OUT:
		flag = drawCutOut( false, true, false );
		break;
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
	case LAST_SCENE_N_EXELER_BATTLE:
	case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX:
		break;
	case LAST_SCENE_N_XEX_CUT_IN:
		flag = drawCutIn( false, false, true );
		break;
	case LAST_SCENE_N_XEX_WORDS:
		drawCutIn( false, false, true );
		break;
	case LAST_SCENE_N_XEX_CUT_OUT:
		flag = drawCutOut( false, false, true );
		break;
	case LAST_SCENE_N_XEX_CUT_END:
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
	case LAST_SCENE_N_XX_BATTLE:
	case LAST_SCENE_N_XX_DIE:
		break;
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		break;
	}

	flagDone = flag;
	return flagDone;
}

////////////////////////////////////////////////////////////////
// ���åȥ��������
// return : ���褬��λ������?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::drawCutIn(
	bool flagExel, bool flagExeler, bool flagXex
)
{
	if( flagExel )
		CutInExel.drawCutIn( frame, nCutInMaxFrame );
	if( flagExeler )
		CutInExeler.drawCutIn( frame, nCutInMaxFrame );
	if( flagXex )
		CutInXex.drawCutIn( frame, nCutInMaxFrame );

	return incFrame( nCutInMaxFrame );
}

////////////////////////////////////////////////////////////////
// ���åȥ����Ȥ�����
// return : ���褬��λ������?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::drawCutOut(
	bool flagExel, bool flagExeler, bool flagXex
)
{
	if( flagExel )
		CutInExel.drawCutOut( frame, nCutOutMaxFrame );
	if( flagExeler )
		CutInExeler.drawCutOut( frame, nCutOutMaxFrame );
	if( flagXex )
		CutInXex.drawCutOut( frame, nCutOutMaxFrame );

	return incFrame( nCutOutMaxFrame );
}

////////////////////////////////////////////////////////////////
// �ե졼���ʤ��
// long maxFrame : �Ǹ�Υե졼��
// return : �Ǹ�Υե졼���ã������?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::incFrame( long maxFrame )
{
	frame++;

	if( frame > maxFrame ){
		frame = maxFrame;
		return true;
	} else {
		return false;
	}
}

////////////////////////////////////////////////////////////////
// �ե졼���ְ�����Ĵ�٤�
// return : �ְ�����?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::checkSkipFrame()
{
	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
	case LAST_SCENE_N_ENCOUNTER:
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	//case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
	case LAST_SCENE_N_EXEL:
	case LAST_SCENE_N_EXEL_ENTER:
	case LAST_SCENE_N_EXEL_CUT_IN:
	//case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_CUT_OUT:
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
	case LAST_SCENE_N_EXEL_BATTLE:
	//case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER:
	case LAST_SCENE_N_EXELER_CUT_IN:
	//case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_CUT_OUT:
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
	case LAST_SCENE_N_EXELER_BATTLE:
	//case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX:
	case LAST_SCENE_N_XEX_CUT_IN:
	//case LAST_SCENE_N_XEX_WORDS:
	case LAST_SCENE_N_XEX_CUT_OUT:
	case LAST_SCENE_N_XEX_CUT_END:
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
	case LAST_SCENE_N_XX_BATTLE:
	case LAST_SCENE_N_XX_DIE:
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		break;
	case LAST_SCENE_N_ENCOUNTER_WORDS:
	case LAST_SCENE_N_EXEL_WORDS:
	case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER_WORDS:
	case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX_WORDS:
		if( (frame % skipFrameLastBoss) != 0 )
			return true;
		else
			return false;
		break;
	}
	return false;
}

////////////////////////////////////////////////////////////////
// �ǥ�����褬��λ������Ĵ�٤�
// return : �ǥ�����褬��λ������?
////////////////////////////////////////////////////////////////

bool DemoLastBoss::checkDone()
{
	switch( get_last_scene() ){
	case LAST_SCENE_N_NULL:
	case LAST_SCENE_N_ENTER:
	case LAST_SCENE_N_ENCOUNTER:
	//case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	case LAST_SCENE_N_ENCOUNTER_WORDS:
	//case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
	case LAST_SCENE_N_ENCOUNTER_CUT_END:
	case LAST_SCENE_N_EXEL:
	case LAST_SCENE_N_EXEL_ENTER:
	//case LAST_SCENE_N_EXEL_CUT_IN:
	case LAST_SCENE_N_EXEL_WORDS:
	//case LAST_SCENE_N_EXEL_CUT_OUT:
	case LAST_SCENE_N_EXEL_CUT_END:
	case LAST_SCENE_N_EXEL_HYPER:
	case LAST_SCENE_N_EXEL_BATTLE:
	case LAST_SCENE_N_EXEL_DIE:
	case LAST_SCENE_N_EXELER:
	//case LAST_SCENE_N_EXELER_CUT_IN:
	case LAST_SCENE_N_EXELER_WORDS:
	//case LAST_SCENE_N_EXELER_CUT_OUT:
	case LAST_SCENE_N_EXELER_CUT_END:
	case LAST_SCENE_N_EXELER_ENTER:
	case LAST_SCENE_N_EXELER_HYPER:
	case LAST_SCENE_N_EXELER_BATTLE:
	case LAST_SCENE_N_EXELER_DIE:
	case LAST_SCENE_N_XEX:
	//case LAST_SCENE_N_XEX_CUT_IN:
	case LAST_SCENE_N_XEX_WORDS:
	//case LAST_SCENE_N_XEX_CUT_OUT:
	case LAST_SCENE_N_XEX_CUT_END:
	case LAST_SCENE_N_XX_ENTER:
	case LAST_SCENE_N_XX_WORDS:
	case LAST_SCENE_N_XX_BATTLE:
	case LAST_SCENE_N_XX_DIE:
	case LAST_SCENE_N_END:
	case LAST_SCENE_N_MAX_N:
		flagDone = true;
		break;
	case LAST_SCENE_N_ENCOUNTER_CUT_IN:
	case LAST_SCENE_N_ENCOUNTER_CUT_OUT:
	case LAST_SCENE_N_EXEL_CUT_IN:
	case LAST_SCENE_N_EXEL_CUT_OUT:
	case LAST_SCENE_N_EXELER_CUT_IN:
	case LAST_SCENE_N_EXELER_CUT_OUT:
	case LAST_SCENE_N_XEX_CUT_IN:
	case LAST_SCENE_N_XEX_CUT_OUT:
		break;
	}

	return flagDone;
}
