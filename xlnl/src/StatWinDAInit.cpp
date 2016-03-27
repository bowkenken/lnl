#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCvlabel.h>
#include <WSCvbtn.h>
#include <WSCvdrawingArea.h>
#include <WSCwindow.h>

#include "gmain.h"
#include "draw.h"
#include "menu.h"
#include "draw-prot.h"
#include "menu-prot.h"

#include "GlobalVar.h"
#include "StatWinIdx.h"

extern WSCwindow *StatWin;

////////////////////////////////////////////////////////////////
// 名前ボタンをクリックした時の処理
// WSCbase *object : ボタン
////////////////////////////////////////////////////////////////

void StatNameActivate( WSCbase *object )
{
	long n = object->getVariantData( "mbr_n" );

	char sCmdMbr[15 + 1];
	sCmdMbr[0] = 'A' + n;
	sCmdMbr[1] = '\0';

	WSCstring sCmd;
	sCmd << "0000@" << sCmdMbr << "^M";

	set_key_buf_str_tail( sCmd );
	set_flg_break_key( TRUE );
}

////////////////////////////////////////////////////////////////
// 状態ボタンをクリックした時の処理
// WSCbase *object : ボタン
////////////////////////////////////////////////////////////////

void StatCondActivate( WSCbase *object )
{
	long n = object->getVariantData( "mbr_n" );

	char sCmdMbr[15 + 1];
	sCmdMbr[0] = 'A' + n;
	sCmdMbr[1] = '\0';

	WSCstring sCmd;
	sCmd << "0000@" << sCmdMbr << "d";

	set_key_buf_str_tail( sCmd );
	set_flg_break_key( TRUE );
}

////////////////////////////////////////////////////////////////
// ボタンやラベル等の型に応じて new する
// WSCbase *object : 親のウィンドウ
// WSCstring name : 名前
// StatWinIdx idx : ステータス・ウィンドウ上の
//                  オブジェクトの番号
////////////////////////////////////////////////////////////////

WSCbase *newLabel( WSCbase *object, WSCstring name, StatWinIdx idx )
{
	WSCbase *lab = NULL;
	WSCprocedure *proc = NULL;

	switch( idx ){
	case STAT_WIN_IDX_NAME:
		proc = new WSCprocedure(
				"StatNameActivate",
				WSEV_ACTIVATE );
		proc->setFunction( StatNameActivate,
				"StatNameActivate" );

		lab = new WSCvbtn( object, name );
		lab->initialize();
		lab->addProcedure( proc );
		break;
	case STAT_WIN_IDX_COND:
		proc = new WSCprocedure(
				"StatCondActivate", WSEV_ACTIVATE );
		proc->setFunction( StatCondActivate,
				"StatCondActivate" );

		lab = new WSCvbtn( object, name );
		lab->initialize();
		lab->addProcedure( proc );
		break;
	case STAT_WIN_IDX_HP:
	case STAT_WIN_IDX_MP:
	case STAT_WIN_IDX_ACT:
		lab = new WSCvlabel( object, name );
		lab->initialize();
		break;
	case STAT_WIN_IDX_MAX_N:
		break;
	}

	lab->setProperty( WSNalignmentH, WS_LEFT );
	lab->setProperty( WSNalignmentV, WS_CENTER );

	return lab;
}

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void StatWinDAInit(WSCbase* object){
  //do something...

	if( !g_flg_gui )
		return;

	nCharWidth = 8;
	nCharHeight = 22;
	nMarginX = 2;
	nMarginY = 2;

	WSCstring name;

	for( long i = 0; i < MBR_MAX_N; i++ ){
		for( long j = 0; j < STAT_WIN_IDX_MAX_N; j++ ){
			name = "";
			name << "StatLabel_" << i << "_" << j;

			gStatLabel[i][j] = newLabel( object, name,
					(StatWinIdx)j );
			gStatLabel[i][j]->setVariantData( "mbr_n", i );
			gStatLabel[i][j]->setProperty( WSNx, 0 );
			gStatLabel[i][j]->setProperty( WSNy, 0 );
			gStatLabel[i][j]->setProperty( WSNwidth,
					nCharWidth );
			gStatLabel[i][j]->setProperty( WSNheight,
					nCharHeight );
			gStatLabel[i][j]->setProperty( WSNlabelString,
					name );
			gStatLabel[i][j]->setVisible( True );
		}

		long lenMax = 40;
		long lenName = 16;
		long lenHpOrMp = 2 + 4 + 1 + 4;

		gStatLabel[i][STAT_WIN_IDX_NAME]->setProperty(
				WSNwidth,
				nCharWidth * lenName );
		gStatLabel[i][STAT_WIN_IDX_HP]->setProperty(
				WSNwidth,
				nCharWidth * lenHpOrMp );
		gStatLabel[i][STAT_WIN_IDX_MP]->setProperty(
				WSNwidth,
				nCharWidth * lenHpOrMp );
		gStatLabel[i][STAT_WIN_IDX_ACT]->setProperty(
				WSNwidth,
				nCharWidth * (lenMax - lenName) );
		gStatLabel[i][STAT_WIN_IDX_COND]->setProperty(
				WSNwidth,
				nCharWidth * lenMax );
	}

	StatWin->execProcedure( WSEV_RESIZE );
}
static WSCfunctionRegister  op("StatWinDAInit",(void*)StatWinDAInit);
