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
* $Id: main-iphone.cpp,v 1.11 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// iPhone 用のメイン処理
////////////////////////////////////////////////////////////////

#define	MAIN_IPHONE_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////

#define	FLAG_BTN_MAP_LABEL_IS_NAME	1

#define	TILE_X_SIZE()	(gPcgDun.getTileSizeX( true ))
#define	TILE_Y_SIZE()	(gPcgDun.getTileSizeY( true ))

#define	MAP_PIX_MAX_X()	(MAP_MAX_X * TILE_X_SIZE())
#define	MAP_PIX_MAX_Y()	(MAP_MAX_Y * TILE_Y_SIZE())

#define	MAP_WIN_INIT_WIDTH()	(20 * TILE_X_SIZE())
#define	MAP_WIN_INIT_HEIGHT()	(20 * TILE_Y_SIZE())
#define	MAP_WIN_MIN_WIDTH()	(1 * TILE_X_SIZE())
#define	MAP_WIN_MIN_HEIGHT()	(1 * TILE_Y_SIZE())

////////////////////////////////////////////////////////////////

#if	0
//@@@
GtkWidget *btnMapExec;
GtkWidget *btnMapAutoMark;
GtkWidget *btnMapUserMenu;
GtkWidget *btnMapSpell;
GtkWidget *btnMapSquare;
GtkWidget *btnMapCancel;
GtkWidget *btnMapOk;

GtkWidget *statBarMap;
guint statBarMapContextId;
guint statBarMapMesId;

guint ghTimer;
#endif

static IPhoneMain *gIPhoneMain;
static NSAutoreleasePool *gAutoreleasePool;

////////////////////////////////////////////////////////////////
// メイン・ルーチン
// int argc : 引数の数
// char **argv : 引数のリスト
////////////////////////////////////////////////////////////////

void	init_iphone( int argc, char **argv, UIWindow *window )
{
	gMainWindow = window;

	init_arg();

	g_flg_gui = TRUE;
	g_flg_cui_mouse = TRUE;

#if	defined( NDEBUG )
	g_flg_cui = FALSE;
#elif	defined( DEBUG )
	g_flg_cui = TRUE;
#else
	g_flg_cui = FALSE;
#endif

	// メイン処理の初期化

	chk_arg( argc, argv );
	init_game();
	change_scene_gui( SCENE_N_INIT );

	if( g_flg_cui_mouse )
		gCuiMouse.init();
	
	if( g_flg_gui ){
		init_iphone_gui( argc, argv );
	} else if( g_flg_cui_mouse ){
		init_iphone_cui_mouse( argc, argv );
	} else if( g_flg_cui ){
		init_iphone_cui( argc, argv );
	}
}

/***************************************************************
* 終了処理
* long code : 終了コード
***************************************************************/

void    gexit( long code )
{
#ifdef  D_GTK
	gtk_exit( code );
#else   /* D_GTK */
	exit( code );
#endif  /* D_GTK */
}

/***************************************************************
* メイン・スレッド
* void *p : 引数
* return : 不明
***************************************************************/

void    *main_thread( void *p )
{
	game_main();

	return NULL;
}

/***************************************************************
* 自動開放プールを作成
***************************************************************/

void	alloc_autorelease_pool( void )
{
	gAutoreleasePool = [[NSAutoreleasePool alloc] init];
}

/***************************************************************
* 自動開放プールを開放
***************************************************************/

void	release_autorelease_pool( void )
{
	[gAutoreleasePool release];
}

////////////////////////////////////////////////////////////////
// iPhone の初期化 (GUI)
// int argc : 引数の数
// char **argv : 引数のリスト
////////////////////////////////////////////////////////////////

void	init_iphone_gui( int argc, char **argv )
{
	// iPhone を初期化

	gMainLock = [[NSLock alloc] init];

	gPcgDun.nTileSizeRate = g_graph_scale_rate;

	gIPhoneMain = [[IPhoneMain alloc] init];

	init_main_win();

	// SDL を初期化

	gMusic.init();
	gSound.init();
	gJoystick.init();

	// タイマーの設定

	ena_timer();

	// タイトル画像を描画

	gPcgDun.initTitle();
	change_scene_gui( SCENE_N_TITLE );
	gPcgDun.drawTitle();

	// グラフィック設定を選択

	gSelConf.init();
	gSelConf.draw();
}

////////////////////////////////////////////////////////////////
// iPhone の初期化 (CUI)
// int argc : 引数の数
// char **argv : 引数のリスト
////////////////////////////////////////////////////////////////

void	init_iphone_cui( int argc, char **argv )
{
	// SDL を初期化

	gMusic.init();
	gSound.init();
	gJoystick.init();

	change_scene_gui( SCENE_N_TITLE );

	// スレッドを切る

	call_game_thread_create( main_thread_cui );
}

////////////////////////////////////////////////////////////////
// iPhone の初期化 (CUI Mouse)
// int argc : 引数の数
// char **argv : 引数のリスト
////////////////////////////////////////////////////////////////

void	init_iphone_cui_mouse( int argc, char **argv )
{
	// iPhone を初期化

	gPcgDun.nTileSizeRate = g_graph_scale_rate;

	// SDL を初期化

	gMusic.init();
	gSound.init();
	gJoystick.init();

	// 入力の初期化

	gKey.init();
	initMouseMotionFunc();

	change_scene_gui( SCENE_N_TITLE );

	// スレッドを切る

	call_game_thread_create( main_thread_cui );
}

///////////////////////////////////////////////////////////////
// タイマー用のダミーのメイン・スレッド (CUI)
// void *p : 引数
// return : 不明
////////////////////////////////////////////////////////////////

void	*main_thread_cui( void *p )
{
	return NULL;
}

////////////////////////////////////////////////////////////////
// タイマーを有効にする
////////////////////////////////////////////////////////////////

void	ena_timer( void )
{
	[gIPhoneMain enableTimer];
}

////////////////////////////////////////////////////////////////
// グラフィック設定の選択後の初期化
////////////////////////////////////////////////////////////////

void	init_main_sel_conf( GraphConf *cnf )
{
	// 各種初期化

	gPcgDun.init( cnf );
	configure_map();

	change_scene_gui( SCENE_N_TOWN );

	gGuiMenu.init();
	gGuiMessage.init();
	gGuiStat.init();
	gGuiNum.init();
	gKey.init();
	initMouseMotionFunc();

	pos_t *draw = get_map_draw_pos();
	pos_t *draw_gui = get_map_draw_pos_gui();
	if( (draw != NULL) && (draw_gui != NULL) ){
		draw_gui->x = draw->x;
		draw_gui->y = draw->y;
		gPcgDun.scrollTile( draw_gui->x, draw_gui->y );
	}

	gPcgDun.redraw();

	if( !call_game_thread_create( main_thread ) )
		exit_game( EXIT_FAILURE );
}

////////////////////////////////////////////////////////////////
// メイン・ウィンドウを作成
////////////////////////////////////////////////////////////////

void	init_main_win( void )
{
}

////////////////////////////////////////////////////////////////
// ゲーム終了前の処理
////////////////////////////////////////////////////////////////

void	closeGameGui()
{
	if( g_flg_cui_mouse )
		gCuiMouse.close();

	gMusic.close();
	gSound.close();
}

////////////////////////////////////////////////////////////////
// ステータス・バーにカーソル位置のヒントを表示
////////////////////////////////////////////////////////////////

void	guiMapPrintStatBarHint( void )
{
#if	0
//@@@
	pos_t *crsr = get_crsr();
	if( crsr == NULL )
		return;

	printMapStatBar( "%s    %s",
			get_str_map_hint_obj( crsr->x, crsr->y ),
			get_str_map_hint_chr( crsr->x, crsr->y ) );
#endif
}

////////////////////////////////////////////////////////////////
// ステータス・バーにメッセージを表示
// const char *s : フォーマット文字列
// ... : 付加引数
////////////////////////////////////////////////////////////////

void	printMapStatBar( const char *s, ... )
{
#if	0
//@@@
	static char	str[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;
	va_list	argptr;

	va_start( argptr, s );
	vsn_printf( str, max_len, s, argptr );
	va_end( argptr );

	gtk_statusbar_remove(
			GTK_STATUSBAR( statBarMap ),
			statBarMapContextId,
			statBarMapMesId );

	statBarMapMesId = gtk_statusbar_push(
			GTK_STATUSBAR( statBarMap ),
			statBarMapContextId,
			str );
#endif
}

////////////////////////////////////////////////////////////////
// マップ・ウィンドウのサイズ変更
////////////////////////////////////////////////////////////////

void	configure_map( void )
{
}

////////////////////////////////////////////////////////////////

@implementation MainMapView

- (id)init
{
	self = [super init];
	if( self == nil )
		return nil;
	
	self.userInteractionEnabled = YES;
	
	return self;
}

- (void)drawRect:(CGRect)rect
{
	CGContextRef curContext = UIGraphicsGetCurrentContext();
	
	gui_begin();
	CGImageRef img = CGBitmapContextCreateImage( gPcgDun.getWBuf()->getPixMap() );
	gui_end();
	
	CGContextDrawImage( curContext, rect, img );
	CGImageRelease( img );
}

- (void)dealloc
{
    [super dealloc];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch *touch = [touches anyObject];
	CGPoint loc = [touch locationInView:self];
	NSUInteger tapN = [touch tapCount];
	long btnN = [touches count];
	
	if( chk_scene_group( SCENE_GROUP_N_TITLE ) ){
		// メイン処理の初期化
		
		gSelConf.select( 0 );
		init_main_sel_conf( gSelConf.pGraphConfSel );
		gSelConf.wipe();
		
		gKey.setChar( '0' );//@@@
	} else {
		long mapX = (long)(loc.x / gPcgDun.getTileSizeX( true ));
		long mapY = (long)(loc.y / gPcgDun.getTileSizeY( true ));
		
		if( btnN == 1 ){
			if( tapN == 1 ){
				gKey.moveCrsrAbs( mapX, mapY );
			} else if( tapN == 2 ){
				MouseMotion::MouseButtonN btnL = MouseMotion::nMouseButtonL;
				callFuncKey( KEY_N_MOUSE_CLICK( btnL ), true );
			}
		}
	}
	
	[self.nextResponder touchesBegan:touches withEvent:event];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	if( chk_scene_group( SCENE_GROUP_N_PLAYING ) ){
		CGPoint pt = gMainMapWin.mapScrollView.contentOffset;
		gPcgDun.scrollMap( pt.x, pt.y );
	}
	
	[self.nextResponder touchesMoved:(NSSet *)touches withEvent:event];
}

@end

////////////////////////////////////////////////////////////////

@implementation MainMapWin

@synthesize mapScrollView;
@synthesize mapView;

- (void)setItemWithTitle:(NSString *)aTitle action:(SEL)aAction buttons:(NSMutableArray *)aButtons
{
	UIBarButtonItem *item;
	UIBarButtonItemStyle style = UIBarButtonItemStyleBordered;
	
	if( [aButtons count] <= 0 ){
		item = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace
															  target:nil
															  action:nil] autorelease];
		[aButtons addObject:item];
	}
	
	item = [[[UIBarButtonItem alloc] initWithTitle:aTitle
											 style:style
											target:self
											action:aAction] autorelease];
	[aButtons addObject:item];
	
	item = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace
														  target:nil
														  action:nil] autorelease];
	[aButtons addObject:item];
}

- (id)init
{
	self = [super init];
	if( self == nil )
		return nil;
	
	mapScrollView = nil;
	mapView = nil;
	
	// スクロール・ビュー
	
	CGRect bounds = [[UIScreen mainScreen] applicationFrame];
	bounds.origin.x = 0;
	bounds.origin.y = 0;
	mapScrollView = [[UIScrollView alloc] initWithFrame:bounds];
	[self.view addSubview:mapScrollView];
	
	// ビュー
	
	bounds.origin.x = 0;
	bounds.origin.y = 0;
	bounds.size.width = MAP_MAX_X * gPcgDun.getTileSizeX( true );
	bounds.size.height = MAP_MAX_Y * gPcgDun.getTileSizeY( true );
	mapView = [[MainMapView alloc] initWithFrame:bounds];
	[mapScrollView addSubview:mapView];
	
	// スクロール・ビューの設定
	
	mapScrollView.contentSize = bounds.size;
	mapScrollView.maximumZoomScale = 4.0f;
	mapScrollView.minimumZoomScale = 0.1f;
	mapScrollView.zoomScale = 2.0f;
	[mapScrollView setZoomScale:0.25f animated:YES];
	mapScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
	mapScrollView.delegate = self;
	
	// ツール・バー
	
	NSMutableArray *buttons = [[NSMutableArray alloc] init];
	
	[self setItemWithTitle:@"/"      action:@selector(strategyButtonDidPush:) buttons:buttons];
	[self setItemWithTitle:@"*"      action:@selector(userButtonDidPush:)     buttons:buttons];
	[self setItemWithTitle:@"-"      action:@selector(spellButtonDidPush:)    buttons:buttons];
	[self setItemWithTitle:@"+"      action:@selector(anchorButtonDidPush:)   buttons:buttons];
	[self setItemWithTitle:@"Stat"   action:@selector(statusButtonDidPush:)   buttons:buttons];
	[self setItemWithTitle:@"Cancel" action:@selector(cancelButtonDidPush:)   buttons:buttons];
	[self setItemWithTitle:@"Menu"   action:@selector(menuButtonDidPush:)     buttons:buttons];
	[self setItemWithTitle:@"Exec"   action:@selector(execButtonDidPush:)     buttons:buttons];
	
	[self setToolbarItems:buttons animated:YES];
	self.title = @"Map";
	
	return self;
}

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{
	return mapView;
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
	gui_begin();
	gPcgDun.drawUpdate( 0, 0, MAP_MAX_X, MAP_MAX_Y );
	gui_end();
}

- (void)strategyButtonDidPush:(id)sender
{
	gKey.setChar( '/', true );
}

- (void)userButtonDidPush:(id)sender
{
	gKey.setChar( '*', true );
}

- (void)spellButtonDidPush:(id)sender
{
	gKey.setChar( '-', true );
}

- (void)anchorButtonDidPush:(id)sender
{
	gKey.setChar( '+', true );
}

- (void)statusButtonDidPush:(id)sender
{
}

- (void)cancelButtonDidPush:(id)sender
{
	gKey.setChar( '0' );
}

- (void)menuButtonDidPush:(id)sender
{
	gKey.setChar( '\n' );
}

- (void)execButtonDidPush:(id)sender
{
	gKey.setChar( '.' );
}

@end

////////////////////////////////////////////////////////////////

@implementation MainNaviCon

- (id)init
{
	self = [super init];
	if( self == nil )
		return nil;
	
	[self setNavigationBarHidden:YES animated:YES];
	[self setToolbarHidden:NO animated:YES];
	
	return self;
}

@end

////////////////////////////////////////////////////////////////

@implementation IPhoneMain

@synthesize flagDrawing;
@synthesize timerDrawMap;

- (id)init
{
	self = [super init];
	if( self == nil )
		return self;
	
	flagDrawing = NO;
	timerDrawMap = nil;
	
	gMainMapWin = [[MainMapWin alloc] init];
	gMainNaviCon = [[MainNaviCon alloc] initWithRootViewController:gMainMapWin];
	[gMainWindow addSubview:gMainNaviCon.view];
	
	return self;
}

- (void)enableTimer
{
	timerDrawMap = [NSTimer scheduledTimerWithTimeInterval:(TIMER_FRAME / 60.0f)
													target:self
												  selector:@selector( handleTimerDrawMap: )
												  userInfo:nil
												   repeats:YES
					];
}

- (void)handleTimerDrawMap:(NSTimer *)timer
{
	if( flagDrawing )
		return;
	flagDrawing = YES;
	gui_begin();
	
	gJoystick.checkEvent();
	
	if( get_scene() == SCENE_N_LAST_BOSS ){
		if( !gPcgDun.drawLastBoss() ){
			gui_end();
			flagDrawing = NO;
			return;
		}
	} else if( chk_scene_group( SCENE_GROUP_N_TITLE ) ){
		gPcgDun.drawTitle();
	} else if( chk_scene_group( SCENE_GROUP_N_ENDING ) ){
		gPcgDun.drawEnding();
	} else if( chk_scene_group( SCENE_GROUP_N_GAME_OVER ) ){
		gPcgDun.drawGameOver();
	} else if( chk_scene_group( SCENE_GROUP_N_SEL_GRAPH ) ){
	} else if( chk_scene_group( SCENE_GROUP_N_PLAYING ) ){
		if( gPcgDun.getFlgUpdateRequestIPhone() ){
			[gMainMapWin.view setNeedsDisplay];
			[gMainMapWin.mapScrollView setNeedsDisplay];
			[gMainMapWin.mapView setNeedsDisplay];
			
			gPcgDun.setFlgUpdateRequestIPhone( false );
		}
	} else {
	}
	
	gui_end();
	flagDrawing = NO;
	return;
}

@end
