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
* $Id: Pcg.h,v 1.24 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef PCG_H
#define PCG_H	1

////////////////////////////////////////////////////////////////
// グラフィック・パターン管理
////////////////////////////////////////////////////////////////

#ifdef D_WS
# include <WSCimageSet.h>
# include <WSDmwindowDev.h>
# include <WSCstring.h>
#endif // D_WS

#ifdef D_GTK
# include "GtkWSDimage.h"
# include "GtkWSDmwindowDev.h"
# include "GtkWSCstring.h"
#endif // D_GTK

#ifdef D_MAC
# include "MacWSDimage.h"
# include "MacWSDmwindowDev.h"
# include "MacWSCstring.h"
#endif // D_MAC

#ifdef D_IPHONE
# include "IPhoneWSDimage.h"
# include "IPhoneWSDmwindowDev.h"
# include "IPhoneWSCstring.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "MfcWSDimage.h"
# include "MfcWSDmwindowDev.h"
# include "MfcWSCstring.h"
#endif // D_MFC

class Pcg {
private:
	// 描画可能待ちの最大待ち時間のデフォルト（ミリ秒）
	static const long nWaitReadyMSecDflt = 100;

	// グラフィック・ファイルのパス名
	WSCstring sPath;
	// グラフィック・パターン
	WSDimage *pImage;

	// パターンのサイズ
	long	nWidth;
	long	nHeight;

public:
	// リストの次の項目
	Pcg *next;
	// 大型化した時のパターン
	Pcg *hyper_boss;
	// パターンのバリエーションの使用比率
	ratio_t nRatio;
	// パターンのバリエーションの使用率
	rate_t nRate;
	char mjr, mnr;

	// 描画可能待ちの最大待ち時間（ミリ秒）
	long nWaitReadyMSec;

public:
	Pcg()
	{
		nWaitReadyMSec = nWaitReadyMSecDflt;

		pImage = NULL;
		next = NULL;
		hyper_boss = NULL;
		nRatio = (ratio_t)1;
		nRate = _100_PERCENT;
		mjr = FACE_MJR_NULL;
		mnr = FACE_MNR_NULL;

		nWidth = 0;
		nHeight = 0;
	}
	~Pcg()
	{
		if( hyper_boss != NULL ){
			delete hyper_boss;
			hyper_boss = NULL;
		}

		if( pImage != NULL ){
			pImage->destroyImage();
			delete pImage;
			pImage = NULL;
		}
	}

	void init( WSCstring path );
	void load( WSCstring path );
	void ena();
	void dis();

	WSCstring getPath();
	WSCstring getName();

	long getWidth();
	long getHeight();

	bool waitReady( WSDmwindowDev *mDev );

	bool beginAlpha();
	bool endAlpha();

	bool draw( WSDmwindowDev *mDev,
			long x, long y, long dx, long dy );
	bool drawFix( WSDmwindowDev *mDev,
			long x, long y, long dx, long dy );
	bool drawIdx( WSDmwindowDev *mDev,
			long x, long y, long w, long h,
			long idxX, long idxY,
			long sizeX, long sizeY );
	bool drawOffset( WSDmwindowDev *mDev,
			long x, long y, long w, long h,
			long offsetX, long offsetY );

private:
};

#endif /* PCG_H */
