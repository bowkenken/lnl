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
* $Id: DemoLastBoss.h,v 1.7 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DEMO_LAST_BOSS_H
#define DEMO_LAST_BOSS_H

////////////////////////////////////////////////////////////////
// ラスボスのデモ
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
