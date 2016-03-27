/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* �ܥץ������ϥե꡼�����եȥ������Ǥ���
* ���ʤ��ϡ� Free Software Foundation ����ɽ����
*  GNU ���̸�ͭ���ѵ����Ρ֥С�����󣲡�
* ���Ϥ���ʹߤγƥС��������椫�餤���줫�����򤷡�
* ���ΥС������������˽��ä��ܥץ�������
* �����ۤޤ����ѹ����뤳�Ȥ��Ǥ��ޤ���
* 
* �ܥץ�������ͭ�ѤȤϻפ��ޤ��������ۤˤ����äƤϡ�
* �Ծ����ڤ�������ŪŬ�����ˤĤ��Ƥΰ��ۤ��ݾڤ�ޤ��,
* �����ʤ��ݾڤ�Ԥʤ��ޤ���
* �ܺ٤ˤĤ��Ƥ� GNU ���̸�ͭ���ѵ�������ɤߤ���������
* 
* ���ʤ��ϡ��ܥץ������Ȱ��� GNU ���̸�ͭ���ѵ�����
* �μ̤��������äƤ���Ϥ��Ǥ��������Ǥʤ����ϡ�
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* �ؼ���񤤤Ƥ���������
* 
* $Id: main-dos.c,v 1.22 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

/***************************************************************
* DOS ���ѤΥᥤ�����
***************************************************************/

#define	MAIN_DOS_C
#include	"inc.h"

/***************************************************************
* �ᥤ�󡦥롼����
* int argc : �����ο�
* char **argv : �����Υꥹ��
* return : ��λ������
***************************************************************/

int	main_dos( int argc, char **argv )
{
	init_arg();
	chk_arg( argc, argv );

	init_game();
	game_main();

	return EXIT_FAILURE;
}

/***************************************************************
* �����ƥ��å��ѿ���ꥻ�å�
***************************************************************/

void	reset_static_main_dos( void )
{
}

/***************************************************************
* ��λ����
* long code : ��λ������
***************************************************************/

void	gexit( long code )
{
	exit( code );
}

/***************************************************************
* ���꡼�������å�
***************************************************************/

void	check_memory_main_dos_c( void )
{
}