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
* $Id: MouseMotion.h,v 1.11 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef MOUSE_MOTION_H
#define MOUSE_MOTION_H

////////////////////////////////////////////////////////////////
// �ޥ������⡼�����
////////////////////////////////////////////////////////////////

class MouseMotion {
private:
	// �ɥ�å����Τ��� X ������Ⱦ�¤Υǥե����
	static const long nDefaultDragXR = 32;
	// �ɥ�å����Τ��� Y ������Ⱦ�¤Υǥե����
	static const long nDefaultDragYR = 32;
	// ����å����Τ��� X ������Ⱦ�¤Υǥե����
	static const long nDefaultClickXR = 8;
	// ����å����Τ��� Y ������Ⱦ�¤Υǥե����
	static const long nDefaultClickYR = 8;

public:
	// �ܥ����ֹ�
	enum MouseButtonN {
		nMouseButton0,
		nMouseButton1,
		nMouseButton2,
		nMouseButton3,
		nMouseButton4,
		nMouseButton5,
		nMouseButton6,
		nMouseButton7,
		nMouseButton8,
		nMouseButton9,
		nMouseButton10,
		nMouseButton11,
		nMouseButton12,
		nMouseButton13,
		nMouseButton14,
		nMouseButton15,
		nMouseButtonMaxN,

		nMouseButtonMinN = nMouseButton0,
		nMouseButtonL = nMouseButton0,
		nMouseButtonM = nMouseButton1,
		nMouseButtonR = nMouseButton2,
	};

	// �⡼�����μ���
	enum MotionKind {
		// �ɥ�å�
		nMotionDrag,
		// �������Υɥ�å�
		nMotionLeft,
		// �������Υɥ�å�
		nMotionRight,
		// �������Υɥ�å�
		nMotionUp,
		// �������Υɥ�å�
		nMotionDown,

		nMotionKindMaxN,

		nMotionKindMinN = nMotionDrag,
	};

	// ��������μ���
	enum ScrollKind {
		// ����������
		nScrollLeft,
		// ����������
		nScrollRight,
		// �她������
		nScrollUp,
		// ����������
		nScrollDown,

		nScrollKindMaxN,

		nScrollKindMinN = nScrollLeft,
	};

	// ������Хå��ؿ��η�
	typedef void (*tFunc)(
			long n,
			long nBgnX, long nBgnY,
			long nCurX, long nCurY );

private:
	// �ɥ�å����Ϻ�ɸ
	long nBgnX[nMouseButtonMaxN], nBgnY[nMouseButtonMaxN];
	// �ɥ�å����Τ���Ⱦ��
	long nDragXR, nDragYR;
	// ����å����Τ���Ⱦ��
	long nClickXR, nClickYR;
	// Ϣ³���ƥ⡼���������ʤ��٤Υե饰
	bool bFlagOnce[nMotionKindMaxN];
	// �ץ쥹��Υե饰
	bool bFlagPress[nMouseButtonMaxN];

	// �ݥ���ȤΥ�����Хå��ؿ�
	tFunc pFuncPoint;
	// �⡼�����Υ�����Хå��ؿ�
	tFunc pFunc[nMouseButtonMaxN][nMotionKindMaxN];
	// ����å��Υ�����Хå��ؿ�
	tFunc pFuncClick[nMouseButtonMaxN];
	// ���֥롦����å��Υ�����Хå��ؿ�
	tFunc pFuncDoubleClick[nMouseButtonMaxN];
	// ��+������å��Υ�����Хå��ؿ�
	tFunc pFuncClickLR;
	// ��+������å��Υ�����Хå��ؿ�
	tFunc pFuncClickRL;
	// �ץ쥹�Υ�����Хå��ؿ�
	tFunc pFuncPress[nMouseButtonMaxN];
	// ��꡼���Υ�����Хå��ؿ�
	tFunc pFuncRelease[nMouseButtonMaxN];
	// ��������Υ�����Хå��ؿ�
	tFunc pFuncScroll[nScrollKindMaxN];

public:
	MouseMotion();

	void setFuncPoint( tFunc func );
	void setFunc(
			MouseButtonN btn, MotionKind mot,
			tFunc func );
	void setFuncClick( MouseButtonN btn, tFunc func );
	void setFuncDoubleClick( MouseButtonN btn, tFunc func );
	void setFuncClickLR(
			MouseButtonN btnPress,
			tFunc func );
	void setFuncPress( MouseButtonN btn, tFunc func );
	void setFuncRelease( MouseButtonN btn, tFunc func );
	void setFuncScroll( ScrollKind dir, tFunc func );

	void setRegionSize(
			long dxr, long dyr,
			long cxr, long cyr );

	bool begin( MouseButtonN n, long x, long y );
	bool end( MouseButtonN n, long x, long y );
	bool checkPressAndClick(
			MouseButtonN pressN,
			MouseButtonN clickN );
	bool move( long x, long y );

	bool point( long x, long y );
	bool drag( MouseButtonN n, long x, long y );
	bool click( MouseButtonN n, long x, long y );
	bool doubleClick( MouseButtonN n, long x, long y );
	bool clickLR(
			MouseButtonN pressN,
			MouseButtonN clickN,
			long x, long y );
	bool press( MouseButtonN n, long x, long y );
	bool release( MouseButtonN n, long x, long y );
	void releaseAll( long x, long y );
	bool mouseScroll( ScrollKind dir );
};

#endif /* MOUSE_MOTION_H */
