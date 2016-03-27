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
* $Id: Pcg.h,v 1.24 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef PCG_H
#define PCG_H	1

////////////////////////////////////////////////////////////////
// ����ե��å����ѥ��������
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
	// �����ǽ�Ԥ��κ����Ԥ����֤Υǥե���ȡʥߥ��á�
	static const long nWaitReadyMSecDflt = 100;

	// ����ե��å����ե�����Υѥ�̾
	WSCstring sPath;
	// ����ե��å����ѥ�����
	WSDimage *pImage;

	// �ѥ�����Υ�����
	long	nWidth;
	long	nHeight;

public:
	// �ꥹ�Ȥμ��ι���
	Pcg *next;
	// �緿���������Υѥ�����
	Pcg *hyper_boss;
	// �ѥ�����ΥХꥨ�������λ�����Ψ
	ratio_t nRatio;
	// �ѥ�����ΥХꥨ�������λ���Ψ
	rate_t nRate;
	char mjr, mnr;

	// �����ǽ�Ԥ��κ����Ԥ����֡ʥߥ��á�
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
