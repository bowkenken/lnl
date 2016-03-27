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
