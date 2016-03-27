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
