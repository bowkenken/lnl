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
* $Id: MfcWSCstring.h,v 1.11 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef DOWS_WSC_STRING_H
#define DOWS_WSC_STRING_H	1

#include <string>

#include "xlnl-dows/stdafx.h"

using namespace std;

enum {
	WS_EN_DEFAULT = 0,
};

class WSCstring : public string
{
public:
	WSCstring();
	WSCstring( char *str );
	WSCstring( const char *str );
	WSCstring( string str );
	WSCstring( CString str );
	WSCstring( long n );

	operator char *();
	WSCstring operator +( WSCstring str );
	WSCstring operator +( char *str );
	WSCstring &operator <<( WSCstring str );
	char operator []( int n );
	char operator []( long n );

	long getChars();
	void deleteChar( long pos );
	void deleteChars( long pos, long len );

	long getWords(
		WSCstring str = " ",
		long encoding = WS_EN_DEFAULT );
	long getWordCharPos(
		long n, WSCstring str,
		long encoding = WS_EN_DEFAULT );
	void cutString( long pos,
		long encoding = WS_EN_DEFAULT );
	WSCstring getWord(
		long n, WSCstring str,
		long encoding = WS_EN_DEFAULT );
	long replaceString(
		char *src, char *dst, long n,
		long encoding = WS_EN_DEFAULT );
};

#endif // DOWS_WSC_STRING_H
