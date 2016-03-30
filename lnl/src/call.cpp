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
* $Id: call.cpp,v 1.132 2014/03/15 00:50:40 bowkenken Exp $
***************************************************************/

#define	CALL_CPP
#include	"inc.h"

#ifdef D_WS
extern WSCwindow *StatWin;
#endif

#ifdef D_GTK
# ifdef HAVE_G_THREAD_INIT
static GStaticMutex	g_key_buf_mutex = G_STATIC_MUTEX_INIT;
# else // HAVE_G_THREAD_INIT
static GMutex	g_key_buf_mutex;
# endif // HAVE_G_THREAD_INIT
#endif // D_GTK

static long g_joy_n = 0;
static joy_kind_t g_joy_kind = JOY_KIND_PS;

static long g_win_x[WIN_KIND_MAX_N];
static long g_win_y[WIN_KIND_MAX_N];
static long g_win_w[WIN_KIND_MAX_N];
static long g_win_h[WIN_KIND_MAX_N];

/***************************************************************
* GUI ����åɤΥ�å�
***************************************************************/

void	gui_begin( void )
{
#ifdef D_WS
	WSGIappDev()->lock();
#endif // D_WS

#ifdef D_GTK
	gdk_threads_enter();
#endif // D_GTK

#ifdef D_IPHONE
	[gMainLock lock];
#endif // D_IPHONE

#ifdef D_MFC
#endif // D_MFC
}

/***************************************************************
* GUI ����åɤΥ����å�
***************************************************************/

void	gui_end( void )
{
#ifdef D_WS
	WSGIappDev()->unlock();
#endif // D_WS

#ifdef D_GTK
	gdk_flush();
	gdk_threads_leave();
#endif // D_GTK

#ifdef D_IPHONE
	[gMainLock unlock];
#endif // D_IPHONE

#ifdef D_MFC
#endif // D_MFC
}

/***************************************************************
* ��ư�����ס�������
***************************************************************/

void	call_alloc_autorelease_pool( void )
{
#ifdef D_IPHONE
	alloc_autorelease_pool();
#endif // D_IPHONE
}

/***************************************************************
* ��ư�����ס������
***************************************************************/

void	call_release_autorelease_pool( void )
{
#ifdef D_IPHONE
	release_autorelease_pool();
#endif // D_IPHONE
}

/***************************************************************
* ��λ���ν���
***************************************************************/

void	call_close_game_gui( void )
{
#ifdef	D_ALL_GUI
	closeGameGui();
#endif
}

/***************************************************************
* �������Хåե��Υ�å�
***************************************************************/

void	key_buf_lock( void )
{
#ifdef D_GTK
# ifdef HAVE_G_THREAD_INIT
	g_static_mutex_lock( &g_key_buf_mutex );
# else // HAVE_G_THREAD_INIT
	g_mutex_lock( &g_key_buf_mutex );
# endif // HAVE_G_THREAD_INIT
#endif // D_GTK
}

/***************************************************************
* �������Хåե��Υ����å�
***************************************************************/

void	key_buf_unlock( void )
{
#ifdef D_GTK
# ifdef HAVE_G_THREAD_INIT
	g_static_mutex_unlock( &g_key_buf_mutex );
# else // HAVE_G_THREAD_INIT
	g_mutex_unlock( &g_key_buf_mutex );
# endif // HAVE_G_THREAD_INIT
#endif // D_GTK
}

/***************************************************************
* �ᥤ�󡦥롼�פΥ���åɤ��ڤ�
* void *(*func)( void * ) : �����롦�Хå��ؿ�
* return : ���顼��̵���ä�����
***************************************************************/

bool_t	call_game_thread_create( void *(*func)( void * ) )
{
#ifdef		D_ALL_GUI
	if( GameThreadCreate( func ) )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* �ᥤ�󡦥롼�פΥ���åɤ�λ
* void *(*func)( void * ) : �����롦�Хå��ؿ�
* long code : ��λ������
* return : ���顼��̵���ä�����
***************************************************************/

bool_t	call_game_thread_exit(
	void *(*func)( void * ), long code
)
{
#ifdef		D_ALL_GUI
	if( GameThreadExit( func, code ) )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* �����ȡ��ǥ��쥯�ȥ���֤�
* return : �����ȡ��ǥ��쥯�ȥ�
***************************************************************/

const char	*call_get_home_dir( void )
{
#ifdef D_IPHONE
	return [[NSString stringWithFormat:@"%@/Documents", NSHomeDirectory()] cString];
#endif // D_IPHONE

#if defined( D_DOS ) || defined( D_MFC )
	char strPath[_MAX_PATH + 1];
	char strDrive[_MAX_DRIVE + 1];
	char strDir[_MAX_DIR + 1];
	char strFName[_MAX_FNAME + 1];
	char strExt[_MAX_EXT + 1];

	int nLen = ::GetModuleFileName( NULL, (LPTSTR)strPath, _MAX_PATH );
	if( nLen <= 0 )
		return NULL;

	::_splitpath(
			strPath,
			strDrive,
			strDir,
			strFName,
			strExt);

	static char strRes[_MAX_PATH + 1];
	sn_printf( strRes, _MAX_PATH, "%s%s", strDrive, strDir );

	return strRes;
#endif // D_DOS || D_MFC

	return NULL;
}

/***************************************************************
* �����ޡ���ͭ���ˤ���
***************************************************************/

void	call_ena_timer( void )
{
#if	defined( D_GTK ) || defined( D_IPHONE )
	ena_timer();
#endif // D_GTK
}

/***************************************************************
* �ޥåס�������ɥ���Ϣ³�¹ԥܥ���Υ��å�
* bool_t flagExec : 
***************************************************************/

void	call_gui_map_cont_exec_set( bool_t flagExec )
{
#ifdef D_GTK
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	if( flagExec ){
		set_label_text_button( GTK_BUTTON( gMapButtonContExec ),
				MSG_GUI_MAP_CONT_EXEC_ON, 0.5, 0.5 );
	} else {
		set_label_text_button( GTK_BUTTON( gMapButtonContExec ),
				MSG_GUI_MAP_CONT_EXEC_OFF, 0.5, 0.5 );
	}

	gui_end();
#endif // D_GTK
}

/***************************************************************
* ���ơ��������С��˥ҥ�Ȥ�ɽ��
***************************************************************/

void	call_gui_map_print_stat_bar_hint( void )
{
#ifdef	D_ALL_GUI
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	guiMapPrintStatBarHint();

	gui_end();
#endif
}

/***************************************************************
* ��˥塼��������ɥ�������
* draw_menu_t *data : ��˥塼�������ѥǡ���
***************************************************************/

void	call_gui_menu_draw( draw_menu_t *data )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMenu.draw( data );

	gui_end();
#endif
}

/***************************************************************
* ��˥塼��������ɥ����Ĥ���
***************************************************************/

void	call_gui_menu_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMenu.wipe();

	gui_end();
#endif
}

/***************************************************************
* ������ޥ��������٥�Ȥ��Ѵ�
* long c : ����
* return : ����
***************************************************************/

long	call_cui_mouse_check_event( long c )
{
#ifdef	D_GTK
	return gCuiMouse.checkEvent( c );
#endif

	return '\0';
}

/***************************************************************
* �ޥ��������٥�ȡ��ϥ�ɥ顼��ꥻ�å�
***************************************************************/

void	call_cui_mouse_reset_handler_tab( void )
{
#ifdef	D_GTK
	gCuiMouse.resetHandlerTab();
#endif
}

/***************************************************************
* �ϥ�ɥ顼���ơ��֥���ɲ�
* bool flagEnable : ͭ����̵���ե饰
* long x : ����å���ȿ������û���γ��� X ��ɸ
* long y : ����å���ȿ������û���γ��� Y ��ɸ
* long w : ����å���ȿ������û������
* long h : ����å���ȿ������û���ι⤵
* long n : �ϥ�ɥ�ؤΰ��� (����)
* const char *macro : �ϥ�ɥ�ؤΰ��� (�ޥ���)
* bool_t (*funcPoint)( long btn, long n, const char *macro ) : 
*   �ݥ���Ȼ��Υϥ�ɥ�
* bool_t (*funcClick)( long btn, long n, const char *macro ) : 
*   ����å����Υϥ�ɥ�
* bool_t (*funcScroll)( long btn, long n, const char *macro ) : 
*   ����å����Υϥ�ɥ�
* return : �ϥ�ɥ顼���ơ��֥��ֹ�
***************************************************************/

long	call_cui_mouse_add_handler(
	bool_t flagEnable,
	long x, long y, long w, long h,
	bool_t (*funcPoint)( long btn, long n, const char *macro ),
	bool_t (*funcClick)( long btn, long n, const char *macro ),
	bool_t (*funcScroll)( long btn, long n, const char *macro ),
	long n,
	const char *macro
)
{
#ifdef	D_GTK
	return gCuiMouse.addHandler(
			flagEnable,
			x, y, w, h,
			funcPoint, funcClick, funcScroll,
			n, macro );
#endif
	return '\0';
}

/***************************************************************
* �ǥե���Ȥ�������ܤ˥ޥ���������������ư
* long sel_n : �������
***************************************************************/

void	call_set_mouse_dflt_menu( long sel_n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMenu.setMouseDfltMenu( sel_n );

	gui_end();
#endif
}

/***************************************************************
* ��å�������³���ޡ���������
***************************************************************/

void	call_gui_message_set_flag_more( bool_t flag )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMessage.setFlagMore( (bool)(flag != FALSE) );

	gui_end();
#endif
}

/***************************************************************
* ��å�������������ɥ�������
***************************************************************/

void	call_gui_message_draw( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiMessage.draw( false );
	gGuiMessage.drawScrollBar();

	gui_end();
#endif
}

/***************************************************************
* �������ϥ�����ɥ�������
***************************************************************/

void	call_gui_num_draw(
	volatile long *n, long min, long max, long figure
)
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiNum.draw( n, min, max, figure );

	gui_end();
#endif
}

/***************************************************************
* �������ϥ�����ɥ����Ĥ���
***************************************************************/

void	call_gui_num_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiNum.wipe();

	gui_end();
#endif
}

/***************************************************************
* ʸ�������ϥ�����ɥ�������
***************************************************************/

void	call_gui_input_string_draw(
	const char *ttl, const char *str, long len
)
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiInpStr.draw( ttl, str, len );

	gui_end();
#endif
}

/***************************************************************
* ʸ�������ϥ�����ɥ����Ĥ���
***************************************************************/

void	call_gui_input_string_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiInpStr.wipe();

	gui_end();
#endif
}

/***************************************************************
* ��쥦����ɥ�������
* const char *name : ̾��
* const char *str : ���
***************************************************************/

void	call_gui_words_draw( const char *name, const char *str )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiWords.draw( name, str );

	gui_end();
#endif
}

/***************************************************************
* ��쥦����ɥ������� (ɽ���������)
* const char *name : ̾��
* const char *str : ���
* long w : ɽ����
***************************************************************/

void	call_gui_words_draw_width(
	const char *name, const char *str,
	long w
)
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiWords.draw( name, str, w );

	gui_end();
#endif
}

/***************************************************************
* ��쥦����ɥ����Ĥ���
***************************************************************/

void	call_gui_words_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiWords.wipe();

	gui_end();
#endif
}

/***************************************************************
* ��ץ쥤��������ɥ��򳫻�
***************************************************************/

void	call_gui_replay_bgn( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiReplay.bgn();

	gui_end();
#endif
}

/***************************************************************
* ��ץ쥤��������ɥ���λ
***************************************************************/

void	call_gui_replay_end( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiReplay.end();

	gui_end();
#endif
}

/***************************************************************
* ��ץ쥤��������ɥ�������
***************************************************************/

void	call_gui_replay_draw( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiReplay.draw();

	gui_end();
#endif
}

/***************************************************************
* ��ץ쥤��������ɥ����Ĥ���
***************************************************************/

void	call_gui_replay_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiReplay.wipe();

	gui_end();
#endif
}

/***************************************************************
* ���饹�����ǥ�����������ɥ�������
* class_t *p : ���饹
***************************************************************/

void	call_gui_class_edit_draw( class_t *p )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiClassEdit.draw( p );

	gui_end();
#endif
}

/***************************************************************
* ���饹�����ǥ�����������ɥ����Ĥ���
***************************************************************/

void	call_gui_class_edit_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiClassEdit.wipe();

	gui_end();
#endif
}

/***************************************************************
* �����롦���ǥ�����������ɥ�������
* class_t *p : ���饹
***************************************************************/

void	call_gui_skill_edit_draw( class_t *p )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiSkillEdit.draw( p );

	gui_end();
#endif
}

/***************************************************************
* �����롦���ǥ�����������ɥ����Ĥ���
***************************************************************/

void	call_gui_skill_edit_wipe( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiSkillEdit.wipe();

	gui_end();
#endif
}

/***************************************************************
* ����饯���������ȡ�������ɥ�������
***************************************************************/

void	call_gui_chr_sheet_draw( mbr_t *org, mbr_t *mbr )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiChrSheet.draw( org, mbr );

	gui_end();
#endif
}

/***************************************************************
* ����饯���������ȡ�������ɥ��������
* mbr_t *org : ���Υ���饯�����ǡ���
* mbr_t *mbr : �Խ���Υ���饯�����ǡ���
***************************************************************/

void	call_gui_chr_sheet_redraw( mbr_t *org, mbr_t *mbr )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiChrSheet.redraw();

	gui_end();
#endif
}

/***************************************************************
* ����饯���������ȡ�������ɥ����Ĥ���
***************************************************************/

void	call_gui_chr_sheet_wipe()
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiChrSheet.wipe();

	gui_end();
#endif
}

/***************************************************************
* ����ե��å�����Υ֥�å��򳫻�
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	call_sel_conf_eval_block_begin( void )
{
#ifdef		D_ALL_GUI
	if( gSelConf.evalBlockBegin() )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* ����ե��å�����Υ֥�å���λ
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	call_sel_conf_eval_block_end( void )
{
#ifdef		D_ALL_GUI
	if( gSelConf.evalBlockEnd() )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* ����ե��å�����ο��ͤ�����
* long token : �ȡ�����
* long n : ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	call_sel_conf_eval_set_num( long token, long n )
{
#ifdef		D_ALL_GUI
	if( gSelConf.evalSetNum( (GraphConfToken)token, n ) )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* ����ե��å������ʸ���������
* long token : �ȡ�����
* WSCstring str : ʸ����
* return : ���顼��̵���ä���?
***************************************************************/

bool_t	call_sel_conf_eval_set_str( long token, char *str )
{
#ifdef		D_ALL_GUI
	if( gSelConf.evalSetStr( (GraphConfToken)token, str ) )
		return TRUE;
	else
		return FALSE;
#endif

	return TRUE;
}

/***************************************************************
* ���С��Υ���ե��å����ѥ���������򳫻�
* mbr_t *mbr : ���С�
***************************************************************/

bool_t	call_sel_mbr_graph_begin( mbr_t *mbr )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	bool_t flgWait = FALSE;

	if( !g_flg_gui )
		return FALSE;

	gui_begin();

	if( gSelMbrGraph == NULL )
		gSelMbrGraph = new SelMbrGraph;
	flgWait = gSelMbrGraph->exec( mbr );

	gui_end();

	if( flgWait )
		return TRUE;
	else
		return FALSE;
#endif

	return FALSE;
}

/***************************************************************
* ���С��Υ���ե��å����ѥ����������λ
***************************************************************/

void	call_sel_mbr_graph_end( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_gui )
		return;

	gui_begin();

	delete gSelMbrGraph;
	gSelMbrGraph = NULL;

	gui_end();
#endif
}

/***************************************************************
* ����ե��å����ѥ�����Υꥻ�å�
***************************************************************/

void	call_pcg_dun_reset( void )
{
#ifdef	D_ALL_GUI
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.reset();

	gui_end();
#endif
}

/***************************************************************
* ���С��Υ���ե��å����ѥ�����Υꥻ�å�
***************************************************************/

void	call_pcg_dun_reload_all_mbr( void )
{
#ifdef	D_ALL_GUI
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.reloadAllMbr();

	gui_end();
#endif
}

/***************************************************************
* ��������Υޥåפ�����
***************************************************************/

void	call_pcg_dun_draw_turn( bool_t flg_first )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_IPHONE )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	if( flg_first )
		gPcgDun.setFlgUpdateRequest( true );

	gui_begin();

	gPcgDun.drawTurn();

	gui_end();
#endif

#ifdef D_MFC
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	if( flg_first )
		gPcgDun.setFlgUpdateRequest( true );

	TRY {
		if( g_Dir3d.CheckRefreshFrameMode() )
			g_Dir3d.SetRefreshRequest( true );
		else
			gPcgDun.drawTurn();
	} CATCH( CException, e ){
	} END_CATCH
#endif // D_MFC
}

/***************************************************************
* �ޥåפκ�����
***************************************************************/

void	call_pcg_dun_redraw( bool_t flgForce )
{
	bool bFlagForce;
	if( flgForce )
		bFlagForce = true;
	else
		bFlagForce = false;

#if	defined( D_WS ) || defined( D_GTK ) || defined( D_IPHONE )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.redraw( bFlagForce );

	gui_end();
#endif

#ifdef D_MFC
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	TRY {
		if( g_Dir3d.CheckRefreshFrameMode() )
			g_Dir3d.SetRefreshRequest( true );
		else
			gPcgDun.redraw( bFlagForce );
	} CATCH( CException, e ){
	} END_CATCH
#endif // D_MFC
}

/***************************************************************
* ����ե��å����ѥ����������
* long map_x : �ޥåפ� X ��ɸ
* long map_y : �ޥåפ� Y ��ɸ
* long map_w : �ޥåפ���
* long map_h : �ޥåפι⤵
* bool_t flagForce : ��������
***************************************************************/

void	call_pcg_dun_draw(
	long map_x, long map_y,
	long map_w, long map_h,
	bool_t flagForce
)
{
	bool bFlagForce;
	if( flagForce )
		bFlagForce = true;
	else
		bFlagForce = false;

#if	defined( D_WS ) || defined( D_GTK ) || defined( D_IPHONE )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.draw( map_x, map_y, map_w, map_h, bFlagForce );

	gui_end();
#endif

#ifdef D_MFC
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	TRY {
		if( g_Dir3d.CheckRefreshFrameMode() )
			g_Dir3d.SetRefreshRequest( true );
		else
			gPcgDun.draw( map_x, map_y, map_w, map_h, bFlagForce );
	} CATCH( CException, e ){
	} END_CATCH
#endif // D_MFC
}

/***************************************************************
* XX �ι��������ǡ���������
* xx_act_kind_t kind : ����μ���
* void *p : ����Υǡ���
***************************************************************/

void	call_pcg_dun_set_xx_attack(
	long kind, void *p )
{
#ifdef	D_ALL_GUI
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gPcgDun.setXxAttack( (xx_act_kind_t)kind, p );
#endif
}

/***************************************************************
* �ƥ����ȡ��⡼�ɤλ����ޥåפ�ʸ���������
* long scrn_x : X ��ɸ
* long scrn_y : Y ��ɸ
* const char *s : �ե����ޥå�ʸ����
* ... : �ե����ޥåȤΰ���
***************************************************************/

void	call_pcg_dun_draw_string(
	long scrn_x, long scrn_y,
	const char *s, ... )
{
#ifdef	D_ALL_GUI
	va_list	argptr;
	static char	buf[SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8 + 1];
	const long	max_len = SCREEN_WIDTH * CHAR_MAX_LEN_UTF_8;

	va_start( argptr, s );
	vsn_printf( buf, max_len, s, argptr );
	va_end( argptr );

	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.drawString( scrn_x, scrn_y, MSG_S, buf );

	gui_end();
#endif
}

/***************************************************************
* VFX ������
* long scrn_x : X ��ɸ
* long scrn_y : Y ��ɸ
* long scrn_w : ��
* long scrn_h : �⤵
***************************************************************/

void	call_pcg_dun_draw_vfx(
	long scrn_x, long scrn_y,
	long scrn_w, long scrn_h )
{
#ifdef	D_ALL_GUI
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.drawVfx( scrn_x, scrn_y, scrn_w, scrn_h, false );

	gui_end();
#endif
}

/***************************************************************
* �ޥåפΥ�������
* long map_x : �ޥåפ� X ��ɸ
* long map_y : �ޥåפ� Y ��ɸ
***************************************************************/

void	call_pcg_dun_scroll( long map_x, long map_y )
{
#ifdef	D_ALL_GUI
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gPcgDun.scrollTile( map_x, map_y );

	gui_end();
#endif
}

/***************************************************************
* �������롦�ѥ�����������֤�
* bool_t flagSub : ���֡��������뤫?
* return : ��
***************************************************************/

long	call_pcg_dun_get_crsr_width( bool_t flagSub )
{
#ifdef	D_ALL_GUI
	gui_begin();

	long n = gPcgDun.getCrsrWidth( !!flagSub );

	gui_end();

	return n;
#endif

	return 0;
}

/***************************************************************
* �������롦�ѥ�����ι⤵���֤�
* bool_t flagSub : ���֡��������뤫?
* return : �⤵
***************************************************************/

long	call_pcg_dun_get_crsr_height( bool_t flagSub )
{
#ifdef	D_ALL_GUI
	gui_begin();

	long n = gPcgDun.getCrsrHeight( !!flagSub );

	gui_end();

	return n;
#endif

	return 0;
}

/***************************************************************
* ����饯���κ�ü�κ�ɸ���֤�
* chr_t *chr : ����饯��
* bool_t flagPre : 1 �����κ�ɸ
* return : ��ü�κ�ɸ
***************************************************************/

long	call_pcg_dun_get_chr_draw_left( chr_t *chr, bool_t flagPre )
{
#ifdef	D_ALL_GUI
	bool bFlagPre;
	if( flagPre )
		bFlagPre = true;
	else
		bFlagPre = false;

	if( g_flg_text_mode ){
		if( flagPre )
			return get_chr_left( chr->pre_draw_x, chr->dx );
		else
			return get_chr_left( chr->x, chr->dx );
	}

	gui_begin();

	Pcg *pPcg = gPcgDun.getChrPcg( chr );

	long n = gPcgDun.getChrDrawLeft( chr, pPcg, bFlagPre );
	n = n / gPcgDun.getTileSizeX();

	gui_end();

	return n;
#endif

	if( flagPre )
		return get_chr_left( chr->pre_draw_x, chr->dx );
	else
		return get_chr_left( chr->x, chr->dx );
}

/***************************************************************
* ����饯���α�ü�κ�ɸ���֤�
* chr_t *chr : ����饯��
* bool_t flagPre : 1 �����κ�ɸ
* return : ��ü�κ�ɸ
***************************************************************/

long	call_pcg_dun_get_chr_draw_right( chr_t *chr, bool_t flagPre )
{
#ifdef	D_ALL_GUI
	bool bFlagPre;
	if( flagPre )
		bFlagPre = true;
	else
		bFlagPre = false;

	if( g_flg_text_mode ){
		if( flagPre )
			return get_chr_right( chr->pre_draw_x, chr->dx );
		else
			return get_chr_right( chr->x, chr->dx );
	}

	gui_begin();

	Pcg *pPcg = gPcgDun.getChrPcg( chr );

	long n = gPcgDun.getChrDrawRight( chr, pPcg, bFlagPre );
	n = (n + gPcgDun.getTileSizeX() - 1) / gPcgDun.getTileSizeX();

	gui_end();

	return n;
#endif

	if( flagPre )
		return get_chr_right( chr->pre_draw_x, chr->dx );
	else
		return get_chr_right( chr->x, chr->dx );
}

/***************************************************************
* ����饯���ξ�ü�κ�ɸ���֤�
* chr_t *chr : ����饯��
* bool_t flagPre : 1 �����κ�ɸ
* return : ��ü�κ�ɸ
***************************************************************/

long	call_pcg_dun_get_chr_draw_top( chr_t *chr, bool_t flagPre )
{
#ifdef	D_ALL_GUI
	bool bFlagPre;
	if( flagPre )
		bFlagPre = true;
	else
		bFlagPre = false;

	if( g_flg_text_mode ){
		if( flagPre )
			return get_chr_top( chr->pre_draw_y, chr->dy );
		else
			return get_chr_top( chr->y, chr->dy );
	}

	gui_begin();

	Pcg *pPcg = gPcgDun.getChrPcg( chr );

	long n = gPcgDun.getChrDrawTop( chr, pPcg, bFlagPre );
	n = n / gPcgDun.getTileSizeY();

	gui_end();

	return n;
#endif

	if( flagPre )
		return get_chr_top( chr->pre_draw_y, chr->dy );
	else
		return get_chr_top( chr->y, chr->dy );
}

/***************************************************************
* ����饯���β�ü�κ�ɸ���֤�
* chr_t *chr : ����饯��
* bool_t flagPre : 1 �����κ�ɸ
* return : ��ü�κ�ɸ
***************************************************************/

long	call_pcg_dun_get_chr_draw_bottom( chr_t *chr, bool_t flagPre )
{
#ifdef	D_ALL_GUI
	bool bFlagPre;
	if( flagPre )
		bFlagPre = true;
	else
		bFlagPre = false;

	if( g_flg_text_mode ){
		if( flagPre )
			return get_chr_bottom( chr->pre_draw_y, chr->dy );
		else
			return get_chr_bottom( chr->y, chr->dy );
	}

	gui_begin();

	Pcg *pPcg = gPcgDun.getChrPcg( chr );

	long n = gPcgDun.getChrDrawBottom( chr, pPcg, bFlagPre );
	n = (n + gPcgDun.getTileSizeY() - 1) / gPcgDun.getTileSizeY();

	gui_end();

	return n;
#endif

	if( flagPre )
		return get_chr_bottom( chr->pre_draw_y, chr->dy );
	else
		return get_chr_bottom( chr->y, chr->dy );
}

/***************************************************************
* �����ɸ���ޥåס�������ɥ���ɽ���ϰ��⤫Ĵ�٤�
* long mapX : X��ɸ
* long mapY : Y��ɸ
* bool_t flg_gui : GUI ����ƤФ줿��?
* return : �ޥåס�������ɥ���ɽ���ϰ��⤫?
***************************************************************/

bool_t	call_pcg_dun_clip_win( long mapX, long mapY, bool_t flg_gui )
{
#ifdef	D_ALL_GUI
	if( !flg_gui )
		gui_begin();

	bool_t flg = gPcgDun.clipWin( mapX, mapY );

	if( !flg_gui )
		gui_end();

	return flg;
#endif

	return TRUE;
}

/***************************************************************
* ���� X ��ɸ���ޥåס�������ɥ���ɽ���ϰ��⤫Ĵ�٤�
* long mapX : X��ɸ
* return : �ޥåס�������ɥ���ɽ���ϰ��⤫?
***************************************************************/

bool_t	call_pcg_dun_clip_win_x( long mapX, bool_t flg_gui )
{
#ifdef	D_ALL_GUI
	if( !flg_gui )
		gui_begin();

	bool_t flg = gPcgDun.clipWinX( mapX );

	if( !flg_gui )
		gui_end();

	return flg;
#endif

	return TRUE;
}

/***************************************************************
* ���� Y ��ɸ���ޥåס�������ɥ���ɽ���ϰ��⤫Ĵ�٤�
* long mapY : Y��ɸ
* return : �ޥåס�������ɥ���ɽ���ϰ��⤫?
***************************************************************/

bool_t	call_pcg_dun_clip_win_y( long mapY, bool_t flg_gui )
{
#ifdef	D_ALL_GUI
	if( !flg_gui )
		gui_begin();

	bool_t flg = gPcgDun.clipWinY( mapY );

	if( !flg_gui )
		gui_end();

	return flg;
#endif

	return TRUE;
}

/***************************************************************
* �饹�ܥ��Υǥ��ꥻ�å�
***************************************************************/

void	call_demo_last_boss_reset( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	if( gPcgDun.pDemoLastBoss == NULL )
		return;

	gui_begin();

	gPcgDun.pDemoLastBoss->reset();

	gui_end();
#endif
}

/***************************************************************
* �饹�ܥ��Υǥ⤬���ä���Ĵ�٤�
* return : �ǥ⤬���ä���?
***************************************************************/

bool_t	call_demo_last_boss_check_done( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return TRUE;
	if( !g_flg_gui )
		return TRUE;

	bool_t	flg = TRUE;

	// gui_begin();

	do {
		if( gPcgDun.pDemoLastBoss == NULL ){
			flg = TRUE;
			break;
		}

		if( gPcgDun.pDemoLastBoss->checkDone() ){
			flg = TRUE;
			break;
		} else {
			flg = FALSE;
			break;
		}

		break;
	} while( 0 );

	// gui_end();

	return flg;
#endif

	return TRUE;
}

/***************************************************************
* ����ǥ��󥰤Υ�����򥹥��å�
***************************************************************/

void	call_demo_ending_skip_scene( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	if( gPcgDun.pDemoEnding == NULL )
		return;

	gui_begin();

	gPcgDun.pDemoEnding->skipScene();

	gui_end();
#endif
}

/***************************************************************
* ������˹礻�� BGM �κ���
* bool_t flg_gui : GUI ����ƤФ줿��?
***************************************************************/

void	call_game_music_play_scene( bool_t flg_gui )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !flg_gui )
		gui_begin();

	gMusic.playScene();

	if( !flg_gui )
		gui_end();
#endif
}

/***************************************************************
* BGM �κ���
* music_kind_t kind : BGM �μ���
* long idx : BGM �ꥹ�ȤΥ���ǥå���
***************************************************************/

void	call_game_music_play( long kind, long idx )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gMusic.play( (music_kind_t)kind, idx );

	gui_end();
#endif
}

/***************************************************************
* BGM �κƺ���
***************************************************************/

void	call_game_music_replay( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gMusic.replay();

	gui_end();
#endif
}

/***************************************************************
* BGM �β��̤�����
***************************************************************/

void	call_game_music_set_volume( rate_t rate )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;

	gui_begin();

	gMusic.setVolume( rate );

	gui_end();
#endif
}

/***************************************************************
* SE �κ���
* sound_kind_t kind : SE �μ���
* long n : �������
***************************************************************/

void	call_game_sound_play( long kind, long n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gSound.play( (sound_kind_t)kind, n );

	gui_end();
#endif
}

/***************************************************************
* SE �����
***************************************************************/

void	call_game_sound_stop( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gSound.stop();

	gui_end();
#endif
}

/***************************************************************
* SE �β��̤�����
***************************************************************/

void	call_game_sound_set_volume( rate_t rate )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;

	gui_begin();

	gSound.setVolume( rate );

	gui_end();
#endif
}

/***************************************************************
* ������Υ��祤���ƥ��å��ֹ���֤�
* return : ���祤���ƥ��å��ֹ�
***************************************************************/

long	call_game_joystick_get_joy( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	long n = gJoystick.getJoy();

	gui_end();

	return n;
#endif

	return g_joy_n;
}

/***************************************************************
* ���祤���ƥ��å�������
* long n : ���祤���ƥ��å����ֹ�
***************************************************************/

void	call_game_joystick_sel_joy( long n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gJoystick.selJoy( n );

	gui_end();
#endif

	g_joy_n = n;
}

/***************************************************************
* ���祤���ƥ��å���̾�����֤�
* long n : ���祤���ƥ��å��ֹ�
* return : ���祤���ƥ��å���̾��
***************************************************************/

const char	*call_game_joystick_get_name( long n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	const char	*s = gJoystick.getName( n );

	gui_end();

	return s;
#endif

	return NULL;
}

/***************************************************************
* ���祤���ƥ��å��μ�����֤�
* return : ���祤���ƥ��å��μ���
***************************************************************/

long	call_game_joystick_get_kind( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	long n = gJoystick.getKind();

	gui_end();

	return n;
#endif

	return g_joy_kind;
}

/***************************************************************
* ���祤���ƥ��å��μ��������
* joy_kind_t kind : ���祤���ƥ��å��μ���
***************************************************************/

void	call_game_joystick_set_kind( long kind )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	gui_begin();

	gJoystick.setKind( (joy_kind_t)kind );

	gui_end();
#endif

	g_joy_kind = (joy_kind_t)kind;
}

/***************************************************************
* ���ơ�������������ɥ��������
***************************************************************/

void	call_gui_stat_redraw( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiStat.redraw();

	gui_end();
#endif
}

/***************************************************************
* ���ơ�������������ɥ�������
* long n : ���С�No.
***************************************************************/

void	call_gui_stat_draw( long n )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gGuiStat.draw( n );

	gui_end();
#endif
}

/***************************************************************
* ������ɥ��κ�ɸ������
* win_kind_t k : ������ɥ��μ���
* long nx : X ��ɸ
* long ny : Y ��ɸ
* long nw : ��
* long nh : �⤵
***************************************************************/

void	call_win_pos_set(
	win_kind_t k,
	long *px, long *py,
	long *pw, long *ph
)
{
	if( k < WIN_KIND_NULL )
		return;
	if( k >= WIN_KIND_MAX_N )
		return;

#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( g_flg_gui ){
		gui_begin();

		gWinPos[k].set( k, px, py, pw, ph );

		gui_end();

		return;
	}
#endif

	if( px != NULL )
		g_win_x[k] = *px;
	if( py != NULL )
		g_win_y[k] = *py;
	if( pw != NULL )
		g_win_w[k] = *pw;
	if( ph != NULL )
		g_win_h[k] = *ph;
}

/***************************************************************
* ������ɥ��κ�ɸ�μ���
* win_kind_t k : ������ɥ��μ���
* long *px : X ��ɸ
* long *py : Y ��ɸ
* long *pw : ��
* long *ph : �⤵
* return : �����Ǥ�����?
***************************************************************/

bool_t	call_win_pos_get(
	win_kind_t k,
	long *px, long *py,
	long *pw, long *ph
)
{
	if( k < WIN_KIND_NULL )
		return FALSE;
	if( k >= WIN_KIND_MAX_N )
		return FALSE;

#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( g_flg_gui ){
		gui_begin();

		gWinPos[k].get( k, px, py, pw, ph );

		gui_end();

		return TRUE;
	}
#endif

	if( px != NULL )
		*px = g_win_x[k];
	if( py != NULL )
		*py = g_win_y[k];
	if( pw != NULL )
		*pw = g_win_w[k];
	if( ph != NULL )
		*ph = g_win_h[k];

	if( pw != NULL )
		if( *pw <= 0 )
			*pw = 256;
	if( ph != NULL )
		if( *ph <= 0 )
			*ph = 256;

	return TRUE;
}

/***************************************************************
* ��ʸ����������
* return : ���Ϥ��줿����
***************************************************************/

long	call_key_get_char( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	long	c = '\0';

	if( !g_flg_init )
		return c;
	if( !g_flg_gui )
		return c;

	gui_begin();

	c = gKey.getChar();

	gui_end();

	return c;
#endif

	return '\0';
}

/***************************************************************
* �������뤬��ư�������˥ޥåפ򥹥����뤹��
***************************************************************/

void	call_key_check_move_crsr( void )
{
#if	defined( D_WS ) || defined( D_GTK ) || defined( D_MFC )
	if( !g_flg_init )
		return;
	if( !g_flg_gui )
		return;

	gui_begin();

	gKey.checkMoveCrsr();

	gui_end();
#endif
}

/***************************************************************
* �������ϤΥ�������
* long n : �������� (�ߥ���)
***************************************************************/

void	call_sleep( long n )
{
#ifdef	D_MFC
	::Sleep( n );
#endif	/* D_MFC */
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_gui( void )
{
#ifdef	D_ALL_GUI
	check_memory_GlobalVar_cpp();
#endif
}
