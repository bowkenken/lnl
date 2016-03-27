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
* $Id: Key.cpp,v 1.32 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// GUI �������Ͻ���
////////////////////////////////////////////////////////////////

#define	KEY_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// WideStudio �Υ����Х롦�������եå��Υϥ�ɥ�
// long keyCode : ������������
// WSCbool flagOn : �����Υ��󡿥���
// return : false �ʤ饭�����Ϥ��˴�����
////////////////////////////////////////////////////////////////

#ifdef D_WS

static WSCbool handler( long keyCode, WSCbool flagOn )
{
	long key = '\0';

	if( !flagOn )
		return true;

	if( (WSK_a <= keyCode) && (keyCode <= WSK_z) ){
		if( WSGIappKeyboard()->withCntl() ){
			key = keyCode - WSK_a + 1;
		} else {
			key = keyCode;
		}

		gKey.setChar( key, true, true );
		return false;
	}
	if( (WSK_A <= keyCode) && (keyCode <= WSK_Z) ){
		if( WSGIappKeyboard()->withCntl() ){
			key = keyCode - WSK_A + 1;
		} else {
			key = keyCode;
		}

		gKey.setChar( key, true, true );
		return false;
	}

	switch( keyCode ){
	// �������롦����
	case WSK_Up:
		key = '8';
		break;
	case WSK_Down:
		key = '2';
		break;
	case WSK_Left:
		key = '4';
		break;
	case WSK_Right:
		key = '6';
		break;
	// �������롦��������
	case WSK_Insert:
		key = '/';
		break;
	case WSK_Home:
		key = '*';
		break;
	case WSK_Page_Up:
		key = '-';
		break;
	case WSK_Page_Down:
		key = '+';
		break;
	case WSK_Delete:
		key = 'H' - '@';
		break;
	case WSK_End:
		key = '.';
		break;
	// �ƥ󡦥���
	case WSK_KP_0:
		key = '0';
		break;
	case WSK_KP_1:
		key = '1';
		break;
	case WSK_KP_2:
		key = '2';
		break;
	case WSK_KP_3:
		key = '3';
		break;
	case WSK_KP_4:
		key = '4';
		break;
	case WSK_KP_5:
		key = '5';
		break;
	case WSK_KP_6:
		key = '6';
		break;
	case WSK_KP_7:
		key = '7';
		break;
	case WSK_KP_8:
		key = '8';
		break;
	case WSK_KP_9:
		key = '9';
		break;
	// �ƥ󡦥�������
	case WSK_KP_Enter:
		key = 'M' - '@';
		break;
	case WSK_KP_Decimal:
		key = '.';
		break;
	case WSK_KP_Divide:
		key = '/';
		break;
	case WSK_KP_Multiply:
		key = '*';
		break;
	case WSK_KP_Subtract:
		key = '-';
		break;
	case WSK_KP_Add:
		key = '+';
		break;
	// �ե��󥯥���󡦥���
	case WSK_F1:
		key = KEY_LNL_FUNC( 1 );
		break;
	case WSK_F2:
		key = KEY_LNL_FUNC( 2 );
		break;
	case WSK_F3:
		key = KEY_LNL_FUNC( 3 );
		break;
	case WSK_F4:
		key = KEY_LNL_FUNC( 4 );
		break;
	case WSK_F5:
		key = KEY_LNL_FUNC( 5 );
		break;
	case WSK_F6:
		key = KEY_LNL_FUNC( 6 );
		break;
	case WSK_F7:
		key = KEY_LNL_FUNC( 7 );
		break;
	case WSK_F8:
		key = KEY_LNL_FUNC( 8 );
		break;
	case WSK_F9:
		key = KEY_LNL_FUNC( 9 );
		break;
	case WSK_F10:
		key = KEY_LNL_FUNC( 10 );
		break;
	case WSK_F11:
		key = KEY_LNL_FUNC( 11 );
		break;
	case WSK_F12:
		key = KEY_LNL_FUNC( 12 );
		break;
	case WSK_F13:
		key = KEY_LNL_FUNC( 13 );
		break;
	case WSK_F14:
		key = KEY_LNL_FUNC( 14 );
		break;
	case WSK_F15:
		key = KEY_LNL_FUNC( 15 );
		break;
	// ����¾
	case WSK_bracketleft:
		if( WSGIappKeyboard()->withCntl() )
			key = 'H' - '@';
		else
			key = '[';
		break;
	case WSK_Tab:
		key = 'I' - '@';
		break;
	case WSK_Escape:
		key = 'H' - '@';
		break;
	case WSK_Shift_L:
	case WSK_Control_L:
	case WSK_Alt_L:
	case WSK_Meta_L:
		key = '\0';
		break;
	default:
		key = keyCode;
		break;
	}

	gKey.setChar( key, true, true );
	return false;
}

#endif // D_WS

////////////////////////////////////////////////////////////////
// GTK+ �Υ������ϥ�ɥ�
// GtkWidget *widget : ?
// GdkEventKey *event : ���٥��
// gpointer user_data : �ϥ�ɥ���Ͽ��������ǡ���
// return : ?
////////////////////////////////////////////////////////////////

#ifdef D_GTK

gboolean handleKeyPress(
	GtkWidget *widget,
	GdkEventKey *event,
	gpointer user_data
)
{
	long key = event->keyval;

	if( event->state & GDK_CONTROL_MASK ){
		if( (GDK_a <= key) && (key <= GDK_z) )
			key = key - GDK_a + 1;
		if( (GDK_A <= key) && (key <= GDK_Z) )
			key = key - GDK_A + 1;
	}

	switch( key ){
	case GDK_Shift_L:
	case GDK_Shift_R:
	case GDK_Control_L:
	case GDK_Control_R:
	case GDK_Caps_Lock:
	case GDK_Shift_Lock:
	case GDK_Meta_L:
	case GDK_Meta_R:
	case GDK_Alt_L:
	case GDK_Alt_R:
		return 1;
	case GDK_Escape:
		key = 'H' - '@';
		break;
	case GDK_BackSpace:
		key = 'H' - '@';
		break;
	case GDK_Linefeed:
		key = 'M' - '@';
		break;
	case GDK_Return:
		key = 'M' - '@';
		break;
	case GDK_Tab:
		key = 'I' - '@';
		break;
	// �������롦����
	case GDK_Up:
		key = '8';
		break;
	case GDK_Down:
		key = '2';
		break;
	case GDK_Left:
		key = '4';
		break;
	case GDK_Right:
		key = '6';
		break;
	// �������롦��������
	case GDK_Insert:
		key = '/';
		break;
	case GDK_Home:
		key = '*';
		break;
	case GDK_Page_Up:
		key = '-';
		break;
	case GDK_Page_Down:
		key = '+';
		break;
	case GDK_Delete:
		key = 'H' - '@';
		break;
	case GDK_End:
		key = '.';
		break;
	// �ƥ󡦥���
	case GDK_KP_0:
		key = '0';
		break;
	case GDK_KP_1:
		key = '1';
		break;
	case GDK_KP_2:
		key = '2';
		break;
	case GDK_KP_3:
		key = '3';
		break;
	case GDK_KP_4:
		key = '4';
		break;
	case GDK_KP_5:
		key = '5';
		break;
	case GDK_KP_6:
		key = '6';
		break;
	case GDK_KP_7:
		key = '7';
		break;
	case GDK_KP_8:
		key = '8';
		break;
	case GDK_KP_9:
		key = '9';
		break;
	// �ƥ󡦥�������
	case GDK_KP_Enter:
		key = 'M' - '@';
		break;
	case GDK_KP_Decimal:
		key = '.';
		break;
	case GDK_KP_Divide:
		key = '/';
		break;
	case GDK_KP_Multiply:
		key = '*';
		break;
	case GDK_KP_Subtract:
		key = '-';
		break;
	case GDK_KP_Add:
		key = '+';
		break;
	// �ƥ󡦥������դΥ������롦����
	case GDK_KP_Insert:
		key = '/';
		break;
	case GDK_KP_Home:
		key = '*';
		break;
	case GDK_KP_Page_Up:
		key = '-';
		break;
	case GDK_KP_Page_Down:
		key = '+';
		break;
	case GDK_KP_Delete:
		key = 'H' - '@';
		break;
	case GDK_KP_End:
		key = '.';
		break;
	case GDK_KP_Up:
		key = '8';
		break;
	case GDK_KP_Down:
		key = '2';
		break;
	case GDK_KP_Left:
		key = '4';
		break;
	case GDK_KP_Right:
		key = '6';
		break;
	case GDK_KP_Space:
		key = ' ';
		break;
	case GDK_KP_Tab:
		key = 'I' - '@';
		break;
	case GDK_KP_Equal:
		key = '=';
		break;
	case GDK_F1:
	case GDK_F2:
	case GDK_F3:
	case GDK_F4:
	case GDK_F5:
	case GDK_F6:
	case GDK_F7:
	case GDK_F8:
	case GDK_F9:
	case GDK_F10:
	case GDK_F11:
	case GDK_F12:
	case GDK_F13:
	case GDK_F14:
	case GDK_F15:
	case GDK_F16:
	case GDK_F17:
	case GDK_F18:
	case GDK_F19:
	case GDK_F20:
	case GDK_F21:
	case GDK_F22:
	case GDK_F23:
	case GDK_F24:
	case GDK_F25:
	case GDK_F26:
	case GDK_F27:
	case GDK_F28:
	case GDK_F29:
	case GDK_F30:
	case GDK_F31:
	case GDK_F32:
	case GDK_F33:
	case GDK_F34:
	case GDK_F35:
		char buf[15 + 1];
		sprintf( buf, "&f%ld;", key - GDK_F1 );
		gKey.setString( buf );

		return 1;
	}

	gKey.setChar( key, true, true );

	return 1;
}

#endif // D_GTK

////////////////////////////////////////////////////////////////
// MFC �Υ������ϥ�ɥ�
// UINT nChar : ���ۥ�����������
// UINT nRepCnt : ��������ԡ��Ȳ��
// UINT nFlags : �������֥ե饰
////////////////////////////////////////////////////////////////

#ifdef D_MFC

void Key::handleKeyDown(
	UINT nChar, UINT nRepCnt, UINT nFlags
)
{
	long key = '\0';

	switch( nChar ){
//	case VK_BACK:
//		key = 'H' - '@';
//		break;
//	case VK_TAB:
//		key = '\t';
//		break;

//	case VK_CLEAR:
//		break;
//	case VK_RETURN:
//		key = 'M' - '@';
//		break;

//	case VK_SHIFT
//	case VK_CONTROL
//	case VK_MENU
//	case VK_PAUSE
//	case VK_CAPITAL
//		break;

//	case VK_KANA:
//	case VK_HANGEUL:
//	case VK_HANGUL:
//	case VK_JUNJA:
//	case VK_FINAL:
//	case VK_HANJA:
//	case VK_KANJI:
//		break;

	case VK_ESCAPE:
		key = 'H' - '@';
		break;

//	case VK_CONVERT:
//	case VK_NONCONVERT:
//	case VK_ACCEPT:
//	case VK_MODECHANGE:
//		break;

//	case VK_SPACE:
//		key = ' ';
//		break;
	case VK_PRIOR:
		key = '-';
		break;
	case VK_NEXT:
		key = '+';
		break;
	case VK_END:
		key = '.';
		break;
	case VK_HOME:
		key = '*';
		break;
	case VK_LEFT:
		key = '4';
		break;
	case VK_UP:
		key = '8';
		break;
	case VK_RIGHT:
		key = '6';
		break;
	case VK_DOWN:
		key = '2';
		break;
//	case VK_SELECT:
//	case VK_PRINT:
//	case VK_EXECUTE:
//	case VK_SNAPSHOT:
//		break;
	case VK_INSERT:
		key = '/';
		break;
	case VK_DELETE:
		key = '0';
		break;
//	case VK_HELP:
//		break;

//	case VK_LWIN:
//	case VK_RWIN:
//	case VK_APPS:
//		break;

//	case VK_SLEEP:
//		break;

//	case VK_NUMPAD0:
//	case VK_NUMPAD1:
//	case VK_NUMPAD2:
//	case VK_NUMPAD3:
//	case VK_NUMPAD4:
//	case VK_NUMPAD5:
//	case VK_NUMPAD6:
//	case VK_NUMPAD7:
//	case VK_NUMPAD8:
//	case VK_NUMPAD9:
//		key = '0' + nChar - VK_NUMPAD0;
//		break;
//	case VK_MULTIPLY:
//		key = '*';
//		break;
//	case VK_ADD:
//		key = '+';
//		break;
//	case VK_SEPARATOR:
//		break;
//	case VK_SUBTRACT:
//		key = '-';
//		break;
//	case VK_DECIMAL:
//		break;
//	case VK_DIVIDE:
//		key = '/';
//		break;
	case VK_F1:
	case VK_F2:
	case VK_F3:
	case VK_F4:
	case VK_F5:
	case VK_F6:
	case VK_F7:
	case VK_F8:
	case VK_F9:
	case VK_F10:
	case VK_F11:
	case VK_F12:
	case VK_F13:
	case VK_F14:
	case VK_F15:
	case VK_F16:
	case VK_F17:
	case VK_F18:
	case VK_F19:
	case VK_F20:
	case VK_F21:
	case VK_F22:
	case VK_F23:
	case VK_F24:
		char buf[15 + 1];
		sprintf( buf, "&%02ld", key - VK_F1 + 1 );
		setString( buf );

		return;
	}

	if( key != '\0' )
		setChar( key, true );
}

#endif // D_MFC

////////////////////////////////////////////////////////////////
// �����Х롦�������եå��Υϥ�ɥ����Ͽ����
////////////////////////////////////////////////////////////////

void Key::init()
{
#ifdef D_WS
	WSGIappKeyboard()->setGlobalKeyHook( handler );
#endif // D_WS
}

////////////////////////////////////////////////////////////////
// �������Хåե����飱ʸ�����Ф�
// return : ����
////////////////////////////////////////////////////////////////

long Key::getChar()
{
	if( buf.getChars() <= 0 )
		return -1;

	long c = (long)(buf[0]);
	buf.deleteChar( 0 );

	return c;
}

////////////////////////////////////////////////////////////////
// �������Хåե��ˣ�ʸ���ɲ�
// long c : ����
// bool flagMacro : �ޥ����Ÿ�����뤫?
// bool flagCheckClear : ��������ԡ��Ȥ��Хåե���
//                       ���ޤ�ʤ��ͤˤ��뤫��
////////////////////////////////////////////////////////////////

void Key::setChar( long c, bool flagMacro, bool flagCheckClear )
{
	char s[4 + 1] = "";
	s[0] = (char)c;
	s[1] = '\0';

	setString( s, flagMacro, flagCheckClear );
}

////////////////////////////////////////////////////////////////
// �������Хåե���ʸ������ɲ�
// WSCstring s : ʸ����
// bool flagMacro : �ޥ����Ÿ�����뤫?
// bool flagCheckClear : ��������ԡ��Ȥ��Хåե���
//                       ���ޤ�ʤ��ͤˤ��뤫��
////////////////////////////////////////////////////////////////

void Key::setString( WSCstring s, bool flagMacro, bool flagCheckClear )
{
	if( flagCheckClear && g_flg_clr_key_buf ){
		static long gPreChar = -1;

		if( chk_key_buf() ){
			for( int i = 0; i < s.getChars(); i++ ){
				if( s[i] == gPreChar ){
					s.deleteChar( i );
					i--;
				} else {
					gPreChar = s[i];
				}
			}
		} else {
			gPreChar = -1;
		}
	}

	if( s.getChars() <= 0 )
		return;
	if( s[0] == '\0' )
		return;

	switch( g_gui_key_kind ){
	case GUI_KEY_KIND_CONSOLE:
	case GUI_KEY_KIND_KEY_BUF_INTERRUPT:
		setStringKeyTab( s, flagMacro );
		break;
	case GUI_KEY_KIND_CLASS_KEY:
		buf += s;
		break;
	case GUI_KEY_KIND_MAX_N:
		break;
	}
}

////////////////////////////////////////////////////////////////
// �������Хåե���ʸ������ɲ�
// bool flagMacro : �ޥ����Ÿ�����뤫?
// WSCstring s : ʸ����
////////////////////////////////////////////////////////////////

void Key::setStringKeyTab( WSCstring s, bool flagMacro )
{
	char **tab = get_key_tab();

	for( ; s.getChars() > 0; s.deleteChar( 0 ) ){
		long c;
		c = s[0];

		bool bFlgTab = true;

		if( c <= '\0' )
			bFlgTab = false;
		else if( c >= KEY_TAB_MAX_N )
			bFlgTab = false;
		else if( tab[c] == NULL )
			bFlgTab = false;
		else if( !flagMacro )
			bFlgTab = false;

		if( bFlgTab ){
			set_key_buf_str_tail( tab[c] );
		} else {
			WSCstring buf;
			buf = s;
			buf.cutString( 1 );

			set_key_buf_str_tail( buf );
		}
	}

	set_flg_break_key( TRUE );
}

////////////////////////////////////////////////////////////////
// �������Хåե��˥��������ޤäƤ��뤫Ĵ�٤�
// return : ���ޤäƤ��뤫?
////////////////////////////////////////////////////////////////

bool Key::chkBuf()
{
	return( buf.getChars() > 0 );
}

////////////////////////////////////////////////////////////////
// ����������ư����
// long mapX : X ��ư��
// long mapY : Y ��ư��
// return : ��ư�Ǥ�����?
////////////////////////////////////////////////////////////////

bool Key::moveCrsrRel( long mapX, long mapY )
{
	pos_t *crsr = get_main_crsr();
	if( crsr == NULL )
		return false;

	mapX = crsr->x + mapX;
	mapY = crsr->y + mapY;

	return gKey.moveCrsrAbs( mapX, mapY );
}

////////////////////////////////////////////////////////////////
// ���к�ɸ����ꤷ�ƥ���������ư����
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���ꤷ����ɸ�ޤǰ�ư�����줿��?
////////////////////////////////////////////////////////////////

bool Key::moveCrsrAbs( long mapX, long mapY )
{
	if( get_flg_play_replay() )
		return true;

#if	0
//@@@
	char buf[63 + 1];
	sn_printf( buf, 63, "%%X%ldY%ld;", mapX, mapY );
	setString( buf, false, false );

	return true;
#endif

	pos_t *crsr = get_main_crsr();
	if( crsr == NULL )
		return false;

	if( !clip_x( mapX ) )
		mapX = crsr->x;
	if( !clip_y( mapY ) )
		mapY = crsr->y;

	if( (crsr->x == mapX) && (crsr->y == mapY) )
		return true;

	crsr->x = mapX;
	crsr->y = mapY;
	checkMoveCrsr();
	setString( "|", false, true );

	return true;
}

////////////////////////////////////////////////////////////////
// �������뤬��ư�������˥ޥåפ򥹥����뤹��
////////////////////////////////////////////////////////////////

void Key::checkMoveCrsr()
{
	long a = 1;
#ifdef	D_MFC
	a = 0;
#endif	// D_MFC

	pos_t *crsr = get_main_crsr();
	if( crsr == NULL )
		return;

	pos_t *draw_gui = get_map_draw_pos_gui();
	if( draw_gui == NULL )
		return;

	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();
	w /= gPcgDun.getTileSizeX( true );
	h /= gPcgDun.getTileSizeY( true );

	if( draw_gui->x > crsr->x )
		draw_gui->x = crsr->x;
	if( draw_gui->y > crsr->y )
		draw_gui->y = crsr->y;
	if( draw_gui->x < (crsr->x - w + a) )
		draw_gui->x = (crsr->x - w + a);
	if( draw_gui->y < (crsr->y - h + a) )
		draw_gui->y = (crsr->y - h + a);
}

////////////////////////////////////////////////////////////////
// �������뤹��
// long mapX : X ��ư��
// long mapY : Y ��ư��
// return : ��������Ǥ�����?
////////////////////////////////////////////////////////////////

bool Key::scrollRel( long mapX, long mapY )
{
	pos_t *draw_gui = get_map_draw_pos_gui();
	if( draw_gui == NULL )
		return false;

	mapX += draw_gui->x;
	mapY += draw_gui->y;

	return scrollAbs( mapX, mapY );
}

////////////////////////////////////////////////////////////////
// ���к�ɸ����ꤷ�ƥ������뤹��
// long mapX : X ��ɸ
// long mapY : Y ��ɸ
// return : ���ꤷ����ɸ�ޤǥ������뤷���줿��?
////////////////////////////////////////////////////////////////

bool Key::scrollAbs( long mapX, long mapY )
{
	if( get_flg_play_replay() )
		return true;

	pos_t *draw_gui = get_map_draw_pos_gui();
	if( draw_gui == NULL )
		return false;

	if( !clip_x( mapX ) )
		mapX = draw_gui->x;
	if( !clip_y( mapY ) )
		mapY = draw_gui->y;

	if( (draw_gui->x == mapX) && (draw_gui->y == mapY) )
		return true;

	draw_gui->x = mapX;
	draw_gui->y = mapY;
	checkScroll();
	setString( "|", false, true );

	return true;
}

////////////////////////////////////////////////////////////////
// �ޥåפ��������뤷�����˥�������ΤϤ߽Ф�������å�
////////////////////////////////////////////////////////////////

void Key::checkScroll()
{
	pos_t *crsr = get_main_crsr();
	if( crsr == NULL )
		return;

	long x = gPcgDun.getScrollBarX();
	long y = gPcgDun.getScrollBarY();
	long w = gPcgDun.getScrollBarW();
	long h = gPcgDun.getScrollBarH();
	x /= gPcgDun.getTileSizeX( true );
	y /= gPcgDun.getTileSizeY( true );
	w /= gPcgDun.getTileSizeX( true );
	h /= gPcgDun.getTileSizeY( true );

	if( crsr->x < x )
		crsr->x = x;
	if( crsr->y < y )
		crsr->y = y;
	if( crsr->x > (x + w - 1) )
		crsr->x = (x + w - 1);
	if( crsr->y > (y + h - 1) )
		crsr->y = (y + h - 1);
}
