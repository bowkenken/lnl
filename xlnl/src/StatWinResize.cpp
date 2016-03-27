#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCvlabel.h>
#include <WSCvdrawingArea.h>

#include "party.h"
#include "GlobalVar.h"
#include "StatWinIdx.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void StatWinResize(WSCbase* object){
  //do something...
	long nWinWidth = (long)(object->getProperty( WSNwidth ))
			- (nMarginX * 2);
	long w = nWinWidth;
	long h = nCharHeight + nMarginY;
	long x = nMarginX;
	long y = nMarginY;

	for( long i = 0; i < MBR_MAX_N; i++ ){
		long wName, wHp, wMp, wAct, wCond;

		if( gStatLabel[i][STAT_WIN_IDX_NAME] == NULL )
			continue;

		wName = (long)(gStatLabel[i][STAT_WIN_IDX_NAME]
				->getProperty( WSNwidth ));
		wHp = (long)(gStatLabel[i][STAT_WIN_IDX_HP]
				->getProperty( WSNwidth ));
		wMp = (long)(gStatLabel[i][STAT_WIN_IDX_MP]
				->getProperty( WSNwidth ));
		wAct = (long)(gStatLabel[i][STAT_WIN_IDX_ACT]
				->getProperty( WSNwidth ));
		wCond = (long)(gStatLabel[i][STAT_WIN_IDX_COND]
				->getProperty( WSNwidth ));
		wName += nMarginX;
		wHp += nMarginX;
		wMp += nMarginX;
		wAct += nMarginX;
		wCond += nMarginX;

		long wClm1 = wName + wAct;
		long wClm2 = wCond;
		long wClmMax;
		if( wClm1 > wClm2 )
			wClmMax = wClm1;
		else
			wClmMax = wClm2;

		long nRowMax = 4;

		if( (w != nWinWidth) && (w < wClmMax) ){
			w = nWinWidth;
			x = nMarginX;
			y += h * nRowMax;
		}

		gStatLabel[i][STAT_WIN_IDX_NAME]
				->setProperty( WSNx, x );
		gStatLabel[i][STAT_WIN_IDX_NAME]
				->setProperty( WSNy, y + (h * 0) );

		gStatLabel[i][STAT_WIN_IDX_ACT]
				->setProperty( WSNx, x + wName );
		gStatLabel[i][STAT_WIN_IDX_ACT]
				->setProperty( WSNy, y + (h * 0) );

		gStatLabel[i][STAT_WIN_IDX_COND]
				->setProperty( WSNx, x );
		gStatLabel[i][STAT_WIN_IDX_COND]
				->setProperty( WSNy, y + (h * 1) );

		gStatLabel[i][STAT_WIN_IDX_HP]
				->setProperty( WSNx, x );
		gStatLabel[i][STAT_WIN_IDX_HP]
				->setProperty( WSNy, y + (h * 2) );

		gStatLabel[i][STAT_WIN_IDX_MP]
				->setProperty( WSNx, x );
		gStatLabel[i][STAT_WIN_IDX_MP]
				->setProperty( WSNy, y + (h * 3) );

		w -= wClmMax;
		x += wClmMax;
	}
}
static WSCfunctionRegister  op("StatWinResize",(void*)StatWinResize);
