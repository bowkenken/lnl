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
* $Id: pet.h,v 1.19 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	PET_H
#define	PET_H

/***************************************************************
* �ڥåȡ��Ȥ��⡦������
***************************************************************/

#include	"mnstr.h"

/* �ѡ��ƥ���Ϣ��ƹԤ���� */
#define	PET_MAX_N	MBR_MAX_N

/* �ڥåȥ���åפ��¤��Ƥ���Ԥ�ޤ᤿��� */
#define	LS_PET_MAX_N	LS_MBR_MAX_N

/* �ڥå�̾�κ���ʸ���� */
#define	PET_NAME_MAX_LEN	MBR_NAME_MAX_LEN
#define	PET_NAME_MAX_BYTE	MBR_NAME_MAX_BYTE

/* �ڥåȥ���åפΥڥåȤΥ��󥸥���� */
#define	PET_DUN_LEV	10

/* �ڥåȤΥǡ����η���� */
typedef mnstr_t	pet_t;

/* �ڥåȤμ���η���� */
typedef mnstr_kind_t	pet_kind_t;

#endif	/* PET_H */
