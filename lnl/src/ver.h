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
* $Id: ver.h,v 1.68 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	VER_H
#define	VER_H

#if	defined( D_WS ) || defined( D_GTK )
# define	STR_FILE_NAME_GAME	"xlnl"
#elif	defined( D_MFC )
# define	STR_FILE_NAME_GAME	"xlnl-dows"
#elif	defined( D_DOS )
# define	STR_FILE_NAME_GAME	"lnl-dos"
#else
# define	STR_FILE_NAME_GAME	"lnl"
#endif

#define	STR_GAME_TITLE	"L&L - Labyrinths & Legends"
#define	STR_VER_GAME	VERSION

#define	STR_SINCE	"1993"
#define	STR_LATEST	"2014"
#define	STR_AUTHOR	"YOSHIMURA, Tomohiko"

#define	STR_WEB	"http://lnl.sourceforge.jp/"
#define	STR_E_MAIL	"bowkenken@users.sourceforge.jp"

#define	STR_TITLE_1	"Created by"
#define	STR_HANDLE_1	"bowkenken"

#define	STR_TITLE_2	"Graphic Design"
#define	STR_HANDLE_2	"[RPG DOT], Whitecat, REFMAP"

#define	STR_TITLE_3	" "
#define	STR_HANDLE_3	"kokusi(yujyu), hiyo, moja"

#define	STR_TITLE_4	" "
#define	STR_HANDLE_4	"URARA, naramura and Denzi"

#define	STR_TITLE_5	"Photograph"
#define	STR_HANDLE_5	"Yoshinori Kamimura"

#define	STR_TITLE_6	"Music Production"
#define	STR_HANDLE_6	"Presence of Music"

#define	STR_TITLE_7	"Sound Effects"
#define	STR_HANDLE_7	"OSA at The Match Makers"

#define	STR_TITLE_THANKS	"Special Thanks"
#define	STR_HANDLE_THANKS	"t-oikawa, TeaMiKL, nnn, lu and you"

#define	STR_FMT_COPYRIGHT	\
		"\n" \
		"--------------------------------" \
		"--------------------------------\n" \
		"%s : version %s  \n" \
		"Copyright (c) %s-%s %s All rights reserved.\n" \
		"                                " \
		"                                \n" \
		"URL   : %-56s\n" \
		"E-mail: %-56s\n" \
		"                                " \
		"                                \n" \
		"%20s  %-42s\n" \
		"%20s  %-42s\n" \
		"%20s  %-42s\n" \
		"%20s  %-42s\n" \
		"%20s  %-42s\n" \
		"%20s  %-42s\n" \
		"%20s  %-42s\n" \
		"%20s  %-42s\n" \
		"--------------------------------" \
		"--------------------------------\n" \
		""

#define	LS_STR_COPYRIGHT	\
		STR_GAME_TITLE, STR_VER_GAME, \
		STR_SINCE, STR_LATEST, STR_AUTHOR, \
		STR_WEB, \
		STR_E_MAIL, \
		STR_TITLE_1, STR_HANDLE_1, \
		STR_TITLE_2, STR_HANDLE_2, \
		STR_TITLE_3, STR_HANDLE_3, \
		STR_TITLE_4, STR_HANDLE_4, \
		STR_TITLE_5, STR_HANDLE_5, \
		STR_TITLE_6, STR_HANDLE_6, \
		STR_TITLE_7, STR_HANDLE_7, \
		STR_TITLE_THANKS, STR_HANDLE_THANKS

#endif	/* VER_H */
