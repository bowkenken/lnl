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
* $Id: Key.cpp,v 1.32 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

////////////////////////////////////////////////////////////////
// GUI キー入力処理
////////////////////////////////////////////////////////////////

#define	KEY_CPP
#include "inc.h"

////////////////////////////////////////////////////////////////
// WideStudio のグローバル・キー・フックのハンドラ
// long keyCode : キー・コード
// WSCbool flagOn : キーのオン／オフ
// return : false ならキー入力を破棄する
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
	// カーソル・キー
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
	// カーソル・キー周辺
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
	// テン・キー
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
	// テン・キー周辺
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
	// ファンクション・キー
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
	// その他
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
// GTK+ のキー・ハンドラ
// GtkWidget *widget : ?
// GdkEventKey *event : イベント
// gpointer user_data : ハンドラ登録時の設定データ
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
	// カーソル・キー
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
	// カーソル・キー周辺
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
	// テン・キー
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
	// テン・キー周辺
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
	// テン・キー周辺のカーソル・キー
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
// MFC のキー・ハンドラ
// UINT nChar : 仮想キー・コード
// UINT nRepCnt : キー・リピート回数
// UINT nFlags : キー状態フラグ
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
// グローバル・キー・フックのハンドラを登録する
////////////////////////////////////////////////////////////////

void Key::init()
{
#ifdef D_WS
	WSGIappKeyboard()->setGlobalKeyHook( handler );
#endif // D_WS
}

////////////////////////////////////////////////////////////////
// キー・バッファから１文字取り出す
// return : キー
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
// キー・バッファに１文字追加
// long c : キー
// bool flagMacro : マクロを展開するか?
// bool flagCheckClear : キー・リピートがバッファに
//                       たまらない様にするか？
////////////////////////////////////////////////////////////////

void Key::setChar( long c, bool flagMacro, bool flagCheckClear )
{
	char s[4 + 1] = "";
	s[0] = (char)c;
	s[1] = '\0';

	setString( s, flagMacro, flagCheckClear );
}

////////////////////////////////////////////////////////////////
// キー・バッファに文字列を追加
// WSCstring s : 文字列
// bool flagMacro : マクロを展開するか?
// bool flagCheckClear : キー・リピートがバッファに
//                       たまらない様にするか？
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
// キー・バッファに文字列を追加
// bool flagMacro : マクロを展開するか?
// WSCstring s : 文字列
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
// キー・バッファにキーがたまっているか調べる
// return : たまっているか?
////////////////////////////////////////////////////////////////

bool Key::chkBuf()
{
	return( buf.getChars() > 0 );
}

////////////////////////////////////////////////////////////////
// カーソルを移動する
// long mapX : X 移動量
// long mapY : Y 移動量
// return : 移動できたか?
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
// 絶対座標を指定してカーソルを移動する
// long mapX : X 座標
// long mapY : Y 座標
// return : 指定した座標まで移動しきれたか?
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
// カーソルが移動した時にマップをスクロールする
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
// カーソルする
// long mapX : X 移動量
// long mapY : Y 移動量
// return : スクロールできたか?
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
// 絶対座標を指定してスクロールする
// long mapX : X 座標
// long mapY : Y 座標
// return : 指定した座標までスクロールしきれたか?
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
// マップがスクロールした時にカーソルのはみ出しをチェック
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
