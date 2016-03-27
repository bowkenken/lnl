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
* $Id: main-iphone.h,v 1.5 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef MAIN_IPONE_H
#define MAIN_IPONE_H	1

////////////////////////////////////////////////////////////////
// iPhone 用のメイン処理
////////////////////////////////////////////////////////////////

#ifdef D_IPHONE

@interface MainMapView : UIView
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

@interface IPhoneMain : NSObject
{
	BOOL flagDrawing;
	NSTimer *timerDrawMap;
}
@property (nonatomic) IBOutlet BOOL flagDrawing;
@property (nonatomic, retain) IBOutlet NSTimer *timerDrawMap;

- (void)enableTimer;
- (void)handleTimerDrawMap:(NSTimer *)timer;

@end

#endif // D_IPHONE

#endif /* MAIN_IPONE_H */
