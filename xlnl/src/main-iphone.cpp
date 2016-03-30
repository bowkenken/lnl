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
* $Id: main-iphone.cpp,v 1.11 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// iPhone �ѤΥᥤ�����
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
// �ᥤ�󡦥롼����
// int argc : �����ο�
// char **argv : �����Υꥹ��
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

	// �ᥤ������ν����

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
* ��λ����
* long code : ��λ������
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
* �ᥤ�󡦥���å�
* void *p : ����
* return : ����
***************************************************************/

void    *main_thread( void *p )
{
	game_main();

	return NULL;
}

/***************************************************************
* ��ư�����ס�������
***************************************************************/

void	alloc_autorelease_pool( void )
{
	gAutoreleasePool = [[NSAutoreleasePool alloc] init];
}

/***************************************************************
* ��ư�����ס������
***************************************************************/

void	release_autorelease_pool( void )
{
	[gAutoreleasePool release];
}

////////////////////////////////////////////////////////////////
// iPhone �ν���� (GUI)
// int argc : �����ο�
// char **argv : �����Υꥹ��
////////////////////////////////////////////////////////////////

void	init_iphone_gui( int argc, char **argv )
{
	// iPhone ������

	gMainLock = [[NSLock alloc] init];

	gPcgDun.nTileSizeRate = g_graph_scale_rate;

	gIPhoneMain = [[IPhoneMain alloc] init];

	init_main_win();

	// SDL ������

	gMusic.init();
	gSound.init();
	gJoystick.init();

	// �����ޡ�������

	ena_timer();

	// �����ȥ����������

	gPcgDun.initTitle();
	change_scene_gui( SCENE_N_TITLE );
	gPcgDun.drawTitle();

	// ����ե��å����������

	gSelConf.init();
	gSelConf.draw();
}

////////////////////////////////////////////////////////////////
// iPhone �ν���� (CUI)
// int argc : �����ο�
// char **argv : �����Υꥹ��
////////////////////////////////////////////////////////////////

void	init_iphone_cui( int argc, char **argv )
{
	// SDL ������

	gMusic.init();
	gSound.init();
	gJoystick.init();

	change_scene_gui( SCENE_N_TITLE );

	// ����åɤ��ڤ�

	call_game_thread_create( main_thread_cui );
}

////////////////////////////////////////////////////////////////
// iPhone �ν���� (CUI Mouse)
// int argc : �����ο�
// char **argv : �����Υꥹ��
////////////////////////////////////////////////////////////////

void	init_iphone_cui_mouse( int argc, char **argv )
{
	// iPhone ������

	gPcgDun.nTileSizeRate = g_graph_scale_rate;

	// SDL ������

	gMusic.init();
	gSound.init();
	gJoystick.init();

	// ���Ϥν����

	gKey.init();
	initMouseMotionFunc();

	change_scene_gui( SCENE_N_TITLE );

	// ����åɤ��ڤ�

	call_game_thread_create( main_thread_cui );
}

///////////////////////////////////////////////////////////////
// �����ޡ��ѤΥ��ߡ��Υᥤ�󡦥���å� (CUI)
// void *p : ����
// return : ����
////////////////////////////////////////////////////////////////

void	*main_thread_cui( void *p )
{
	return NULL;
}

////////////////////////////////////////////////////////////////
// �����ޡ���ͭ���ˤ���
////////////////////////////////////////////////////////////////

void	ena_timer( void )
{
	[gIPhoneMain enableTimer];
}

////////////////////////////////////////////////////////////////
// ����ե��å�����������ν����
////////////////////////////////////////////////////////////////

void	init_main_sel_conf( GraphConf *cnf )
{
	// �Ƽ�����

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
// �ᥤ�󡦥�����ɥ������
////////////////////////////////////////////////////////////////

void	init_main_win( void )
{
}

////////////////////////////////////////////////////////////////
// �����ཪλ���ν���
////////////////////////////////////////////////////////////////

void	closeGameGui()
{
	if( g_flg_cui_mouse )
		gCuiMouse.close();

	gMusic.close();
	gSound.close();
}

////////////////////////////////////////////////////////////////
// ���ơ��������С��˥���������֤Υҥ�Ȥ�ɽ��
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
// ���ơ��������С��˥�å�������ɽ��
// const char *s : �ե����ޥå�ʸ����
// ... : �ղð���
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
// �ޥåס�������ɥ��Υ������ѹ�
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
		// �ᥤ������ν����
		
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
	
	// �������롦�ӥ塼
	
	CGRect bounds = [[UIScreen mainScreen] applicationFrame];
	bounds.origin.x = 0;
	bounds.origin.y = 0;
	mapScrollView = [[UIScrollView alloc] initWithFrame:bounds];
	[self.view addSubview:mapScrollView];
	
	// �ӥ塼
	
	bounds.origin.x = 0;
	bounds.origin.y = 0;
	bounds.size.width = MAP_MAX_X * gPcgDun.getTileSizeX( true );
	bounds.size.height = MAP_MAX_Y * gPcgDun.getTileSizeY( true );
	mapView = [[MainMapView alloc] initWithFrame:bounds];
	[mapScrollView addSubview:mapView];
	
	// �������롦�ӥ塼������
	
	mapScrollView.contentSize = bounds.size;
	mapScrollView.maximumZoomScale = 4.0f;
	mapScrollView.minimumZoomScale = 0.1f;
	mapScrollView.zoomScale = 2.0f;
	[mapScrollView setZoomScale:0.25f animated:YES];
	mapScrollView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
	mapScrollView.delegate = self;
	
	// �ġ��롦�С�
	
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
