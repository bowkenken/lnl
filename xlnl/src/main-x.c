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
* $Id: main-x.c,v 1.14 2014/01/07 23:57:24 bowkenken Exp $
***************************************************************/

/***************************************************************
* X-Window �ѤΥᥤ�����
***************************************************************/

#define	MAIN_X_C
#include	"inc.h"

void	*(*g_main_thread_ptr)( void * );

/***************************************************************
* �ᥤ�󡦥롼����
* int argc : �����ο�
* char **argv : �����Υꥹ��
* return : ��λ������
***************************************************************/

int	main_ws( int argc, char **argv )
{
	g_main_thread_ptr = NULL;

	init_arg();

	g_flg_gui = TRUE;

#if	defined( NDEBUG )
	g_flg_cui = FALSE;
#elif	defined( DEBUG )
	g_flg_cui = TRUE;
#else
	g_flg_cui = FALSE;
#endif

	chk_arg( argc, argv );
	init_game();

	if( !call_game_thread_create( main_thread ) )
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

/***************************************************************
* ��λ����
* long code : ��λ������
***************************************************************/

void	gexit( long code )
{
#ifdef	D_GTK
	gtk_exit( code );
#else	/* D_GTK */
	exit( code );
#endif	/* D_GTK */
}

/***************************************************************
* �ᥤ�󡦥���å�
* void *p : ����
* return : ����
***************************************************************/

void	*main_thread( void *p )
{
	g_main_thread_ptr = main_thread;

	game_main();

	return NULL;
}
