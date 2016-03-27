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
* $Id: MacWSCstring.cpp,v 1.2 2014/01/07 23:55:39 bowkenken Exp $
***************************************************************/

#include "MacWSCstring.h"

WSCstring::WSCstring()
{
}

WSCstring::WSCstring( char *str )
{
	if( str == NULL )
		*(string *)this = string( "" );
	else
		*(string *)this = string( str );
}

WSCstring::WSCstring( const char *str )
{
	if( str == NULL )
		*(string *)this = string( "" );
	else
		*(string *)this = string( str );
}

WSCstring::WSCstring( string str )
{
	*(string *)this = str;
}

WSCstring::WSCstring( long n )
{
	char str[32 + 1] = "";
	sprintf( str, "%ld", n );

	*(string *)this = string( str );
}

WSCstring::operator char *()
{
	return( (char *)(this->c_str()) );
}

WSCstring WSCstring::operator +( WSCstring str )
{
	return( WSCstring( string( *this ) + string( str ) ) );
}

WSCstring WSCstring::operator +( char *str )
{
	return( WSCstring( string( *this ) + string( str ) ) );
}

WSCstring &WSCstring::operator <<( WSCstring str )
{
	string( *this ) += string( str );

	return *this;
}

char WSCstring::operator []( int n )
{
	return( (char)(string( *this )[n]) );
}

long WSCstring::getChars()
{
	return( (long)(this->length()) );
}

void WSCstring::deleteChar( long pos )
{
	deleteChars( pos, 1 );
}

void WSCstring::deleteChars( long pos, long len )
{
	erase( pos, len );
}

long WSCstring::getWords(
	WSCstring str, long encoding )
{
	long n = 1;
	size_t pos = 0;

	if( str.length() <= 0 )
		return 0;

	for( n = 1; ; n++ ){
		pos = find( str, pos );
		if( pos == npos )
			break;

		pos += str.length();
	}

	return n;
}

long WSCstring::getWordCharPos(
	long n, WSCstring str, long encoding )
{
	size_t pos = 0;

	for( long i = 0; i < n; i++ ){
		pos = find( str, pos );
		if( pos == npos )
			return -1;

		pos += str.length();
	}

	return (long)pos;
}

void WSCstring::cutString( long pos, long encoding )
{
	erase( pos, npos );
}

WSCstring WSCstring::getWord(
	long n, WSCstring str, long encoding )
{
	long maxN = getWords( str, encoding ) - 1;
	if( n > maxN )
		return "";
	if( n < 0 )
		return "";

	long n1 = getWordCharPos( n, str );
	long n2 = getWordCharPos( n + 1, str );
	if( n1 <= -1 )
		n1 = 0;
	if( n2 <= -1 )
		n2 = this->getChars() + 1;

	return( substr( n1, n2 - n1 - 1 ) );
}
