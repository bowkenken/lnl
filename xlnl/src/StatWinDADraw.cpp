#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCvlabel.h>
#include <WSCvdrawingArea.h>

#include "misc.h"
#include "draw.h"
#include "party.h"
#include "item.h"
#include "misc-prot.h"
#include "party-prot.h"

#include "GlobalVar.h"
#include "StatWinIdx.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void StatWinDADraw(WSCbase* object){
  //do something...
	party_t *pty = get_party();
	WSCvdrawingArea *drawArea = (WSCvdrawingArea *)object;

	for( long i = 0; i < MBR_MAX_N; i++ ){
		mbr_t *mbr = pty->mbr[i];

		if( gStatLabel[i][STAT_WIN_IDX_NAME] == NULL )
			continue;

		bool flgJoin;
		if( (mbr == NULL) || (mbr->mbr_n == MBR_N_NOT_JOIN) )
			flgJoin = false;
		else
			flgJoin = true;

		char buf[127 + 1];
		WSCstring sName, sHp, sMp, sAct, sCond;
		sName = "";
		sHp = "";
		sMp = "";
		sAct = "";
		sCond = "";

		// 名前

		if( flgJoin )
			sName << mbr->name;
		else
			sName << "";

		// HP

		if( flgJoin ){
			sprintf( buf, "%4ld", mbr->abl.hp.n );
			sHp << "HP" << buf;
			sprintf( buf, "%4ld", mbr->abl.hp.max );
			sHp << "/" << buf;
		} else {
			sHp = "";
		}

		// MP

		if( flgJoin ){
			sprintf( buf, "%4ld", mbr->abl.mp.n );
			sMp << "MP" << buf;
			sprintf( buf, "%4ld", mbr->abl.mp.max );
			sMp << "/" << buf;
		} else {
			sMp = "";
		}

		// 行動

		if( flgJoin )
			sAct << mbr->act.msg;
		else
			sAct << "";

		// 状態

		if( flgJoin ){
			if( chk_flg( mbr->stat,
					FLG_STAT_DEAD ) ){
				sCond << MSG_STAT_DEAD << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_STONE ) ){
				sCond << MSG_STAT_STONE << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_FAINT ) ){
				sCond << MSG_STAT_FAINT << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_PARALYZE ) ){
				sCond << MSG_STAT_PARALYZE << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_POISON ) ){
				sCond << MSG_STAT_POISON << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_CONFUSION ) ){
				sCond << MSG_STAT_CONFUSION << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_BLIND ) ){
				sCond << MSG_STAT_BLIND << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_SLEEP ) ){
				sCond << MSG_STAT_SLEEP << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_SILENCE ) ){
				sCond << MSG_STAT_SILENCE << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_CAUGHT ) ){
				sCond << MSG_STAT_CAUGHT << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_FEAR ) ){
				sCond << MSG_STAT_FEAR << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_HALLUCINATION ) ){
				sCond << MSG_STAT_HALLUCINATION << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_CHARM ) ){
				sCond << MSG_STAT_CHARM << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_DRUNK ) ){
				sCond << MSG_STAT_DRUNK << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_FLY ) ){
				sCond << MSG_STAT_FLY << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_VANISH ) ){
				sCond << MSG_STAT_VANISH << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_IRON_BODY ) ){
				sCond << MSG_STAT_IRON_BODY << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_PASSWALL ) ){
				sCond << MSG_STAT_PASSWALL << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_SENSE_INVISIBLE ) ){
				sCond << MSG_STAT_SENSE_INVISIBLE << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_STARVATION ) ){
				sCond << MSG_STAT_STARVATION << " ";
			}
			if( chk_flg( mbr->stat,
					FLG_STAT_HUNGRY ) ){
				sCond << MSG_STAT_HUNGRY << " ";
			}
		} else {
			sCond << "";
		}

		// 名前の色

		WSCstring sColor = "#000000";

		if( flgJoin ){
			switch( i ){
			case 0:
				sColor = "#cc0000";
				break;
			case 1:
				sColor = "#00cc00";
				break;
			case 2:
				sColor = "#0000cc";
				break;
			case 3:
				sColor = "#00cccc";
				break;
			case 4:
				sColor = "#cc00cc";
				break;
			case 5:
				sColor = "#888800";
				break;
			}
		} else {
			sColor = "#000000";
		}

		gStatLabel[i][STAT_WIN_IDX_NAME]
				->setProperty( WSNforeColor, sColor );

		// HPの色

		WSCstring sColorHp;
		WSCstring sColorHpFore1;
		WSCstring sColorHpFore2;
		WSCstring sColorHpFore3;
		WSCstring sColorHpBack;

		rate_t nHpRate;
		if( flgJoin ){
			nHpRate = mbr->abl.hp.n * _100_PERCENT;
			nHpRate /= mbr->abl.hp.max;
		} else {
			nHpRate = 0;
		}

		if( flgJoin )
			sColorHpBack = "#000000";
		else
			sColorHpBack = "#888888";

		if( nHpRate <= WARNING_HP_RATE_RED ){
			sColorHp = "#cc0000";
			sColorHpFore1 = "#ee0000";
			sColorHpFore2 = "#cc0000";
			sColorHpFore3 = "#aa0000";
		} else if( nHpRate <= WARNING_HP_RATE_YELLOW ){
			sColorHp = "#888800";
			sColorHpFore1 = "#aaaa00";
			sColorHpFore2 = "#888800";
			sColorHpFore3 = "#666600";
		} else if( nHpRate <= WARNING_HP_RATE_GREEN ){
			sColorHp = "#00aa00";
			sColorHpFore1 = "#00cc00";
			sColorHpFore2 = "#00aa00";
			sColorHpFore3 = "#008800";
		} else {
			sColorHp = "#000000";
			sColorHpFore1 = "#ffffff";
			sColorHpFore2 = "#ffffff";
			sColorHpFore3 = "#ffffff";
		}

		gStatLabel[i][STAT_WIN_IDX_HP]
				->setProperty( WSNforeColor, sColorHp );

		// MPの色

		WSCstring sColorMp;
		WSCstring sColorMpFore1;
		WSCstring sColorMpFore2;
		WSCstring sColorMpFore3;
		WSCstring sColorMpBack;

		rate_t nMpRate;
		if( flgJoin ){
			nMpRate = mbr->abl.mp.n * _100_PERCENT;
			nMpRate /= mbr->abl.mp.max;
		} else {
			nMpRate = 0;
		}

		if( flgJoin )
			sColorMpBack = "#000000";
		else
			sColorMpBack = "#888888";

		if( nMpRate <= WARNING_MP_RATE_RED ){
			sColorMp = "#cc0000";
			sColorMpFore1 = "#ee0000";
			sColorMpFore2 = "#cc0000";
			sColorMpFore3 = "#aa0000";
		} else if( nMpRate <= WARNING_MP_RATE_YELLOW ){
			sColorMp = "#888800";
			sColorMpFore1 = "#aaaa00";
			sColorMpFore2 = "#888800";
			sColorMpFore3 = "#666600";
		} else if( nMpRate <= WARNING_MP_RATE_GREEN ){
			sColorMp = "#00aaaa";
			sColorMpFore1 = "#00cccc";
			sColorMpFore2 = "#00aaaa";
			sColorMpFore3 = "#008888";
		} else {
			sColorMp = "#000000";
			sColorMpFore1 = "#ffffff";
			sColorMpFore2 = "#ffffff";
			sColorMpFore3 = "#ffffff";
		}

		gStatLabel[i][STAT_WIN_IDX_MP]
				->setProperty( WSNforeColor, sColorMp );

		// ステータスを描画

		gStatLabel[i][STAT_WIN_IDX_NAME]
				->setProperty( WSNlabelString, sName );
		gStatLabel[i][STAT_WIN_IDX_HP]
				->setProperty( WSNlabelString, sHp );
		gStatLabel[i][STAT_WIN_IDX_MP]
				->setProperty( WSNlabelString, sMp );
		gStatLabel[i][STAT_WIN_IDX_ACT]
				->setProperty( WSNlabelString, sAct );
		gStatLabel[i][STAT_WIN_IDX_COND]
				->setProperty( WSNlabelString, sCond );

		// HPのバーを描画

		long xHp = (long)gStatLabel[i][STAT_WIN_IDX_HP]
				->getProperty( WSNx );
		xHp += (long)gStatLabel[i][STAT_WIN_IDX_HP]
				->getProperty( WSNwidth );

		long yHp = (long)gStatLabel[i][STAT_WIN_IDX_HP]
				->getProperty( WSNy );
		yHp += nMarginY + 4;

		long wHp = 0;
		wHp += (long)gStatLabel[i][STAT_WIN_IDX_NAME]
				->getProperty( WSNwidth );
		wHp += (long)gStatLabel[i][STAT_WIN_IDX_ACT]
				->getProperty( WSNwidth );
		wHp -= (long)gStatLabel[i][STAT_WIN_IDX_HP]
				->getProperty( WSNwidth );

		drawArea->setForeColor( sColorHpBack );
		drawArea->drawFillRect(
				xHp + 4, yHp + 4 - 2,
				wHp - (4 * 2), 2 );
		drawArea->drawFillRect(
				xHp + 4, yHp + 4 + 0,
				wHp - (4 * 2), 2 );
		drawArea->drawFillRect(
				xHp + 4, yHp + 4 + 2,
				wHp - (4 * 2), 2 );

		if( nHpRate > 0 ){
			wHp = wHp * nHpRate / _100_PERCENT;

			drawArea->setForeColor( sColorHpFore1 );
			drawArea->drawFillRect(
					xHp + 4, yHp + 4 - 2,
					wHp - (4 * 2), 2 );
			drawArea->setForeColor( sColorHpFore2 );
			drawArea->drawFillRect(
					xHp + 4, yHp + 4 + 0,
					wHp - (4 * 2), 2 );
			drawArea->setForeColor( sColorHpFore3 );
			drawArea->drawFillRect(
					xHp + 4, yHp + 4 + 2,
					wHp - (4 * 2), 2 );
		}

		// MPのバーを描画

		long xMp = (long)gStatLabel[i][STAT_WIN_IDX_MP]
				->getProperty( WSNx );
		xMp += (long)gStatLabel[i][STAT_WIN_IDX_MP]
				->getProperty( WSNwidth );

		long yMp = (long)gStatLabel[i][STAT_WIN_IDX_MP]
				->getProperty( WSNy );
		yMp += nMarginY + 4;

		long wMp = 0;
		wMp += (long)gStatLabel[i][STAT_WIN_IDX_NAME]
				->getProperty( WSNwidth );
		wMp += (long)gStatLabel[i][STAT_WIN_IDX_ACT]
				->getProperty( WSNwidth );
		wMp -= (long)gStatLabel[i][STAT_WIN_IDX_MP]
				->getProperty( WSNwidth );

		drawArea->setForeColor( sColorMpBack );
		drawArea->drawFillRect(
				xMp + 4, yMp + 4 - 2,
				wMp - (4 * 2), 2 );
		drawArea->drawFillRect(
				xMp + 4, yMp + 4 + 0,
				wMp - (4 * 2), 2 );
		drawArea->drawFillRect(
				xMp + 4, yMp + 4 + 2,
				wMp - (4 * 2), 2 );

		if( nMpRate > 0 ){
			wMp = wMp * nMpRate / _100_PERCENT;

			drawArea->setForeColor( sColorMpFore1 );
			drawArea->drawFillRect(
					xMp + 4, yMp + 4 - 2,
					wMp - (4 * 2), 2 );
			drawArea->setForeColor( sColorMpFore2 );
			drawArea->drawFillRect(
					xMp + 4, yMp + 4 + 0,
					wMp - (4 * 2), 2 );
			drawArea->setForeColor( sColorMpFore3 );
			drawArea->drawFillRect(
					xMp + 4, yMp + 4 + 2,
					wMp - (4 * 2), 2 );
		}
	}
}
static WSCfunctionRegister  op("StatWinDADraw",(void*)StatWinDADraw);
