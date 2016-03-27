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
* $Id: Key.h,v 1.21 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef KEY_H
#define KEY_H	1

#ifdef D_WS
# include <WSCstring.h>
# include <WSDkeyboard.h>
#endif // D_WS

#ifdef D_GTK
# include <gtk/gtk.h>
# include <gdk/gdk.h>
# include <gdk/gdkkeysyms.h>
# include "GtkMisc.h"
# include "GtkWSCstring.h"
#endif // D_GTK

#ifdef D_MAC
# include "MacMisc.h"
# include "MacWSCstring.h"
#endif // D_MAC

#ifdef D_IPHONE
# include "IPhoneMisc.h"
# include "IPhoneWSCstring.h"
#endif // D_IPHONE

#ifdef D_MFC
# include "MfcWSCstring.h"
#endif // D_MFC

////////////////////////////////////////////////////////////////
// キー入力の管理
////////////////////////////////////////////////////////////////

class Key {
public:

private:
	// キー入力バッファ
	WSCstring buf;

public:
	Key()
	{
	}
	~Key()
	{
	}

	void init();

	long getChar();

	void setChar( long c, bool flagMacro = false,
		bool flagCheckClear = false );
	void setString( WSCstring s, bool flagMacro = false,
		bool flagCheckClear = false );
	void setStringKeyTab( WSCstring s, bool flagMacro );

	bool chkBuf();

	bool moveCrsrRel( long mapX, long mapY );
	bool moveCrsrAbs( long mapX, long mapY );
	void checkMoveCrsr();
	bool scrollRel( long mapX, long mapY );
	bool scrollAbs( long mapX, long mapY );
	void checkScroll();

#ifdef D_MFC
	void handleKeyDown(
		UINT nChar, UINT nRepCnt, UINT nFlags
	);
#endif // D_MFC
};

#ifdef D_GTK
gboolean handleKeyPress(
	GtkWidget *widget,
	GdkEventKey *event,
	gpointer user_data
);
#endif // D_GTK

#endif /* KEY_H */
