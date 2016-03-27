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
* $Id: MouseMotion.cpp,v 1.14 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// �ޥ����Τδ���
////////////////////////////////////////////////////////////////

#define	MOUSE_MOTION_CPP	1
#include "inc.h"

////////////////////////////////////////////////////////////////
// ���󥹥ȥ饯��
////////////////////////////////////////////////////////////////

MouseMotion::MouseMotion()
{
	pFuncPoint = NULL;
	pFuncClickLR = NULL;
	pFuncClickRL = NULL;

	for( long i = nMouseButtonMinN; i < nMouseButtonMaxN; i++ ){
		nBgnX[i] = -1;
		nBgnY[i] = -1;

		for( long j = 0; j < nMotionKindMaxN; j++ ){
			pFunc[i][j] = NULL;
		}
		pFuncClick[i] = NULL;
		pFuncDoubleClick[i] = NULL;
		pFuncPress[i] = NULL;
		pFuncRelease[i] = NULL;
	}
	for( long i = nScrollKindMinN; i < nScrollKindMaxN; i++ )
		pFuncScroll[i] = NULL;

	nDragXR = nDefaultDragXR;
	nDragYR = nDefaultDragYR;
	nClickXR = nDefaultClickXR;
	nClickYR = nDefaultClickYR;
}

////////////////////////////////////////////////////////////////
// �ݥ���ȤΥ�����Хå��ؿ�����Ͽ
// tFunc func : ������Хå��ؿ�
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncPoint( tFunc func )
{
	pFuncPoint = func;
}

////////////////////////////////////////////////////////////////
// �⡼�����Υ�����Хå��ؿ�����Ͽ
// MouseButtonN btn : �ܥ����ֹ�
// MotionKind mot : �⡼�����μ���
// tFunc func : ������Хå��ؿ�
////////////////////////////////////////////////////////////////

void MouseMotion::setFunc(
		MouseButtonN btn, MotionKind mot,
		tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;
	if( mot < nMotionKindMinN )
		return;
	if( mot >= nMotionKindMaxN )
		return;

	pFunc[btn][mot] = func;
}

////////////////////////////////////////////////////////////////
// ����å��Υ�����Хå��ؿ�����Ͽ
// MouseButtonN btn : �ܥ����ֹ�
// tFunc func : ������Хå��ؿ�
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncClick( MouseButtonN btn, tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;

	pFuncClick[btn] = func;
}

////////////////////////////////////////////////////////////////
// ���֥롦����å��Υ�����Хå��ؿ�����Ͽ
// MouseButtonN btn : �ܥ����ֹ�
// tFunc func : ������Хå��ؿ�
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncDoubleClick( MouseButtonN btn, tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;

	pFuncDoubleClick[btn] = func;
}

////////////////////////////////////////////////////////////////
// ����Ʊ������å��Υ�����Хå��ؿ�����Ͽ
// MouseButtonN btnPress : ��˥ץ쥹����ܥ����ֹ�
// tFunc func : ������Хå��ؿ�
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncClickLR( MouseButtonN btnPress, tFunc func )
{
	if( btnPress < nMouseButtonMinN )
		return;
	if( btnPress >= nMouseButtonMaxN )
		return;

	if( btnPress == nMouseButtonL )
		pFuncClickLR = func;
	if( btnPress == nMouseButtonR )
		pFuncClickRL = func;
}

////////////////////////////////////////////////////////////////
// �ץ쥹�Υ�����Хå��ؿ�����Ͽ
// MouseButtonN btn : �ܥ����ֹ�
// tFunc func : ������Хå��ؿ�
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncPress( MouseButtonN btn, tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;

	pFuncPress[btn] = func;
}

////////////////////////////////////////////////////////////////
// ��꡼���Υ�����Хå��ؿ�����Ͽ
// MouseButtonN btn : �ܥ����ֹ�
// tFunc func : ������Хå��ؿ�
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncRelease( MouseButtonN btn, tFunc func )
{
	if( btn < nMouseButtonMinN )
		return;
	if( btn >= nMouseButtonMaxN )
		return;

	pFuncRelease[btn] = func;
}

////////////////////////////////////////////////////////////////
// ��������Υ�����Хå��ؿ�����Ͽ
// ScrollKind dir : �⡼�����μ���
// tFunc func : ������Хå��ؿ�
////////////////////////////////////////////////////////////////

void MouseMotion::setFuncScroll( ScrollKind dir, tFunc func )
{
	if( dir < nScrollKindMinN )
		return;
	if( dir >= nScrollKindMaxN )
		return;

	pFuncScroll[dir] = func;
}

////////////////////////////////////////////////////////////////
// �ɥ�å��䥯��å����Τ���Ⱦ�¤���Ͽ
// -1 ����Ͽ���ʤ�
// long dxr : �ɥ�å����Τ��� X ������Ⱦ��
// long dyr : �ɥ�å����Τ��� Y ������Ⱦ��
// long cxr : ����å����Τ��� X ������Ⱦ��
// long cyr : ����å����Τ��� Y ������Ⱦ��
////////////////////////////////////////////////////////////////

void MouseMotion::setRegionSize(
		long dxr, long dyr,
		long cxr, long cyr )
{
	if( dxr > 0 )
		nDragXR = dxr;
	if( dyr > 0 )
		nDragYR = dyr;
	if( cxr > 0 )
		nClickXR = cxr;
	if( cyr > 0 )
		nClickYR = cyr;
}

////////////////////////////////////////////////////////////////
// �ɥ�å���⡼�����δ��γ���
// MouseButtonN n : �ܥ����ֹ�
// long x : ���� X ��ɸ
// long y : ���� Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool MouseMotion::begin( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	nBgnX[n] = x;
	nBgnY[n] = y;

	for( long j = 0; j < nMotionKindMaxN; j++ )
		bFlagOnce[j] = false;

	press( n, x, y );

	return true;
}

////////////////////////////////////////////////////////////////
// �ɥ�å���⡼�����δ��ν�λ
// MouseButtonN n : �ܥ����ֹ�
// long x : ��λ X ��ɸ
// long y : ��λ Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool MouseMotion::end( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	release( n, x, y );

	do {
		if( nBgnX[n] <= -1 )
			break;
		if( nBgnY[n] <= -1 )
			break;
		if( labs( nBgnX[n] - x ) > nClickXR )
			break;
		if( labs( nBgnY[n] - y ) > nClickYR )
			break;

		if( checkPressAndClick( nMouseButtonL, n ) ){
			releaseAll( x, y );

			clickLR( nMouseButtonL, n, x, y );

			nBgnX[nMouseButtonL] = -1;
			nBgnY[nMouseButtonL] = -1;
		} else if( checkPressAndClick( nMouseButtonR, n ) ){
			releaseAll( x, y );

			clickLR( nMouseButtonR, n, x, y );

			nBgnX[nMouseButtonR] = -1;
			nBgnY[nMouseButtonR] = -1;
		} else {
			releaseAll( x, y );

			click( n, x, y );
		}
	} while( 0 );

	nBgnX[n] = -1;
	nBgnY[n] = -1;

	return true;
}

////////////////////////////////////////////////////////////////
// ����Ʊ������å��δ���
// MouseButtonN pressN : ��˥ץ쥹������Ĵ�٤�ܥ����ֹ�
// MouseButtonN clickN : ��Ǽºݤ˥���å������ܥ����ֹ�
// return : ����Ʊ������å����Τ�������
////////////////////////////////////////////////////////////////

bool MouseMotion::checkPressAndClick(
	MouseButtonN pressN,
	MouseButtonN clickN
)
{
	if( pressN == clickN )
		return false;
	if( (pressN != nMouseButtonL)
			&& (pressN != nMouseButtonR) ){
		return false;
	}
	if( (clickN != nMouseButtonL)
			&& (clickN != nMouseButtonR) ){
		return false;
	}

	if( nBgnX[pressN] <= -1 )
		return false;
	if( nBgnY[pressN] <= -1 )
		return false;

	return true;
}

////////////////////////////////////////////////////////////////
// ��������ΰ�ư�ˤ�롢�ɥ�å���ݥ���Ȥδ���
// long x : ���ߤ� X ��ɸ
// long y : ���ߤ� Y ��ɸ
// return : ���顼��̵���ä�����
////////////////////////////////////////////////////////////////

bool MouseMotion::move( long x, long y )
{
	bool flgRelease = false;
	for( long i = nMouseButtonMinN; i < nMouseButtonMaxN; i++ ){
		if( nBgnX[i] <= -1 )
			continue;
		if( nBgnY[i] <= -1 )
			continue;
		if( (labs( x - nBgnX[i] ) < nClickXR)
				&& (labs( y - nBgnY[i] ) < nClickYR) ){
			continue;
		}

		flgRelease = true;
		break;
	}
	if( flgRelease )
		releaseAll( x, y );

	bool flgPoint = true;
	for( long i = nMouseButtonMinN; i < nMouseButtonMaxN; i++ ){
		if( (nBgnX[i] > -1) && (nBgnY[i] > -1) ){
			drag( (MouseButtonN)i, x, y );
			flgPoint = false;
		}
	}
	if( flgPoint )
		point( x, y );

	return true;
}

////////////////////////////////////////////////////////////////
// �ݥ���ȤΥ�����Хå��ؿ��θƤӽФ�
// long x : ���ߤ� X ��ɸ
// long y : ���ߤ� Y ��ɸ
// return : ������Хå��ؿ���ƤӽФ�������
////////////////////////////////////////////////////////////////

bool MouseMotion::point( long x, long y )
{
	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();

	if( x >= w + 16 )
		return false;
	if( y >= h + 16 )
		return false;

	// �ݥ����
	if( pFuncPoint != NULL ){
		(*pFuncPoint)( (MouseButtonN)0, 0, 0, x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// �ɥ�å��ȥ⡼�����Υ�����Хå��ؿ��θƤӽФ�
// MouseButtonN n : �ܥ����ֹ�
// long x : ���ߤ� X ��ɸ
// long y : ���ߤ� Y ��ɸ
// return : ������Хå��ؿ���ƤӽФ�������
////////////////////////////////////////////////////////////////

bool MouseMotion::drag( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	// �ɥ�å�
	if( pFunc[n][nMotionDrag] != NULL ){
		(*(pFunc[n][nMotionDrag]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	if( (labs( x - nBgnX[n] ) < nDragXR)
			&& (labs( y - nBgnY[n] ) < nDragYR) ){
		for( long j = 0; j < nMotionKindMaxN; j++ ){
			bFlagOnce[j] = false;
		}
	}

	// ���⡼�����
	do {
		if( labs( x - nBgnX[n] ) < labs( y - nBgnY[n] ) )
			break;
		if( (x - nBgnX[n]) > -nDragXR )
			break;
		if( bFlagOnce[nMotionLeft] )
			break;

		for( long j = 0; j < nMotionKindMaxN; j++ )
			bFlagOnce[j] = false;
		bFlagOnce[nMotionLeft] = true;

		if( pFunc[n][nMotionLeft] != NULL ){
			(*(pFunc[n][nMotionLeft]))(
					n, nBgnX[n], nBgnY[n], x, y );

			return true;
		}
	} while( 0 );

	// ���⡼�����
	do {
		if( labs( x - nBgnX[n] ) < labs( y - nBgnY[n] ) )
			break;
		if( (x - nBgnX[n]) < +nDragXR )
			break;
		if( bFlagOnce[nMotionRight] )
			break;

		for( long j = 0; j < nMotionKindMaxN; j++ )
			bFlagOnce[j] = false;
		bFlagOnce[nMotionRight] = true;

		if( pFunc[n][nMotionRight] != NULL ){
			(*(pFunc[n][nMotionRight]))(
					n, nBgnX[n], nBgnY[n], x, y );

			return true;
		}
	} while( 0 );

	// ��⡼�����
	do {
		if( labs( y - nBgnY[n] ) < labs( x - nBgnX[n] ) )
			break;
		if( (y - nBgnY[n]) > -nDragYR )
			break;
		if( bFlagOnce[nMotionUp] )
			break;

		for( long j = 0; j < nMotionKindMaxN; j++ )
			bFlagOnce[j] = false;
		bFlagOnce[nMotionUp] = true;

		if( pFunc[n][nMotionUp] != NULL ){
			(*(pFunc[n][nMotionUp]))(
					n, nBgnX[n], nBgnY[n], x, y );

			return true;
		}
	} while( 0 );

	// ���⡼�����
	do {
		if( labs( y - nBgnY[n] ) < labs( x - nBgnX[n] ) )
			break;
		if( (y - nBgnY[n]) < +nDragYR )
			break;
		if( bFlagOnce[nMotionDown] )
			break;

		for( long j = 0; j < nMotionKindMaxN; j++ )
			bFlagOnce[j] = false;
		bFlagOnce[nMotionDown] = true;

		if( pFunc[n][nMotionDown] != NULL ){
			(*(pFunc[n][nMotionDown]))(
					n, nBgnX[n], nBgnY[n], x, y );

			return true;
		}
	} while( 0 );

	return false;
}

////////////////////////////////////////////////////////////////
// ����å��Υ�����Хå��ؿ��θƤӽФ�
// MouseButtonN n : �ܥ����ֹ�
// long x : ���ߤ� X ��ɸ
// long y : ���ߤ� Y ��ɸ
// return : ������Хå��ؿ���ƤӽФ�������
////////////////////////////////////////////////////////////////

bool MouseMotion::click( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	if( pFuncClick[n] != NULL ){
		(*(pFuncClick[n]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ���֥롦����å��Υ�����Хå��ؿ��θƤӽФ�
// MouseButtonN n : �ܥ����ֹ�
// long x : ���ߤ� X ��ɸ
// long y : ���ߤ� Y ��ɸ
// return : ������Хå��ؿ���ƤӽФ�������
////////////////////////////////////////////////////////////////

bool MouseMotion::doubleClick( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	if( pFuncDoubleClick[n] != NULL ){
		(*(pFuncDoubleClick[n]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ����Ʊ������å��Υ�����Хå��ؿ��θƤӽФ�
// MouseButtonN pressN : ��˥ץ쥹�����ܥ����ֹ�
// MouseButtonN clickN : ��ǥ���å������ܥ����ֹ�
// long x : ���ߤ� X ��ɸ
// long y : ���ߤ� Y ��ɸ
// return : ������Хå��ؿ���ƤӽФ�������
////////////////////////////////////////////////////////////////

bool MouseMotion::clickLR(
	MouseButtonN pressN,
	MouseButtonN clickN,
	long x, long y
)
{
	if( (pressN == nMouseButtonL) && (clickN == nMouseButtonR) ){
		if( pFuncClickLR != NULL ){
			(*pFuncClickLR)( pressN,
					nBgnX[pressN], nBgnY[pressN],
					x, y );

			return true;
		}
	}
	if( (pressN == nMouseButtonR) && (clickN == nMouseButtonL) ){
		if( pFuncClickRL != NULL ){
			(*pFuncClickRL)( pressN,
					nBgnX[pressN], nBgnY[pressN],
					x, y );

			return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////
// �ץ쥹�Υ�����Хå��ؿ��θƤӽФ�
// MouseButtonN n : �ܥ����ֹ�
// long x : ���ߤ� X ��ɸ
// long y : ���ߤ� Y ��ɸ
// return : ������Хå��ؿ���ƤӽФ�������
////////////////////////////////////////////////////////////////

bool MouseMotion::press( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	bFlagPress[n] = true;

	if( pFuncPress[n] != NULL ){
		(*(pFuncPress[n]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ��꡼���Υ�����Хå��ؿ��θƤӽФ�
// MouseButtonN n : �ܥ����ֹ�
// long x : ���ߤ� X ��ɸ
// long y : ���ߤ� Y ��ɸ
// return : ������Хå��ؿ���ƤӽФ�������
////////////////////////////////////////////////////////////////

bool MouseMotion::release( MouseButtonN n, long x, long y )
{
	if( n < nMouseButtonMinN )
		return false;
	if( n >= nMouseButtonMaxN )
		return false;

	if( !bFlagPress[n] )
		return false;
	bFlagPress[n] = false;

	if( pFuncRelease[n] != NULL ){
		(*(pFuncRelease[n]))( n, nBgnX[n], nBgnY[n], x, y );

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////
// ���ƤΥ�꡼���Υ�����Хå��ؿ��θƤӽФ�
// long x : ���ߤ� X ��ɸ
// long y : ���ߤ� Y ��ɸ
// return : ������Хå��ؿ���ƤӽФ�������
////////////////////////////////////////////////////////////////

void MouseMotion::releaseAll( long x, long y )
{
	for( long i = (long)nMouseButtonMinN;
			i < (long)nMouseButtonMaxN; i++ ){
		release( (MouseButtonN)i, x, y );
	}
}

////////////////////////////////////////////////////////////////
// ��������Υ�����Хå��ؿ��θƤӽФ�
// ScrollKind dir : �⡼�����μ���
// return : ������Хå��ؿ���ƤӽФ�������
////////////////////////////////////////////////////////////////

bool MouseMotion::mouseScroll( ScrollKind dir )
{
	if( dir < nScrollKindMinN )
		return false;
	if( dir >= nScrollKindMaxN )
		return false;

	if( pFuncScroll[dir] != NULL ){
		(*(pFuncScroll[dir]))( (long)dir, 0, 0, 0, 0 );

		return true;
	}

	return false;
}
