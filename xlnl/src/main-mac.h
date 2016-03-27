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
* $Id: main-mac.h,v 1.3 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef MAIN_MAC_H
#define MAIN_MAC_H	1

////////////////////////////////////////////////////////////////
// iPhone �ѤΥᥤ�����
////////////////////////////////////////////////////////////////

#ifdef D_MACjjj
//@@@

@interface MainMapView : NSView
{
}

@end

////////////////////////////////////////////////////////////////

@interface MainMapWin : UIViewController <UIScrollViewDelegate>
{
	UIScrollView *mapScrollView;
	MainMapView *mapView;
}

@property (nonatomic, retain) IBOutlet UIScrollView *mapScrollView;
@property (nonatomic, retain) IBOutlet MainMapView *mapView;

- (void)strategyButtonDidPush:(id)sender;
- (void)userButtonDidPush:(id)sender;
- (void)spellButtonDidPush:(id)sender;
- (void)anchorButtonDidPush:(id)sender;
- (void)statusButtonDidPush:(id)sender;
- (void)cancelButtonDidPush:(id)sender;
- (void)menuButtonDidPush:(id)sender;
- (void)execButtonDidPush:(id)sender;

@end

////////////////////////////////////////////////////////////////

@interface MainNaviCon : UINavigationController
{
}

@end

////////////////////////////////////////////////////////////////

@interface MacMain : NSObject
{
	BOOL flagDrawing;
	NSTimer *timerDrawMap;
}
@property (nonatomic) IBOutlet BOOL flagDrawing;
@property (nonatomic, retain) IBOutlet NSTimer *timerDrawMap;

- (void)enableTimer;
- (void)handleTimerDrawMap:(NSTimer *)timer;

@end

#endif //@@@

////////////////////////////////////////////////////////////////

#ifdef D_MAC

@interface MacMain : NSObject
{
	BOOL flagDrawing;
	NSTimer *timerDrawMap;
}
@property (nonatomic) IBOutlet BOOL flagDrawing;
@property (nonatomic, retain) IBOutlet NSTimer *timerDrawMap;

- (void)enableTimer;
- (void)handleTimerDrawMap:(NSTimer *)timer;

@end

#endif // D_MAC

#endif /* MAIN_MAC_H */
