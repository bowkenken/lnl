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
* $Id: GuiChrSheet.h,v 1.19 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_CHR_SHEET_H
#define GUI_CHR_SHEET_H	1

////////////////////////////////////////////////////////////////
// ����饯���������ȡ�������ɥ�
////////////////////////////////////////////////////////////////

class GuiChrSheet {

	//////// �ץ饤�١��ȡ����С��ѿ� ////////
private:

#ifdef D_WS
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mName;
	GtkWidget *mNoteBook;
	GtkWidget *mButtonOk;
	GtkWidget *mButtonCancel;
	GtkWidget *mButtonNextChr;
	GtkWidget *mButtonPrevChr;

	// ���ơ����� (��)

	GtkWidget *mStatName;
	GtkWidget *mStatFace;
	GtkWidget *mStatRace;
	GtkWidget *mStatRaceName;
	GtkWidget *mStatSex;

	GtkWidget *mStatHp;
	GtkWidget *mStatMp;

	GtkWidget *mStatBash[6];
	GtkWidget *mStatThrow[6];

	GtkWidget *mStatGold;
	GtkWidget *mStatTurn;

	// ���ơ����� (��)

	GtkWidget *mStatStat[STAT_MAX_N];
	GtkWidget *mStatLight;
	GtkWidget *mStatTile;

	// ǽ����

	GtkWidget *mAblClass;

	GtkWidget *mAblLev[ABL_KIND_MAX_N];
	GtkWidget *mAblAddLev[ABL_KIND_MAX_N];
	GtkWidget *mAblExp[ABL_KIND_MAX_N];
	GtkWidget *mAblNeedExp[ABL_KIND_MAX_N];

	GtkWidget *mAblResi[3][3];

	// ������

	GtkWidget *mSkillClass;

	GtkWidget *mSkillName[SKILL_MAX_PAGE][SKILL_PER_PAGE_MAX_N];
	GtkWidget *mSkillLev[SKILL_MAX_PAGE][SKILL_PER_PAGE_MAX_N];
	GtkWidget *mSkillExp[SKILL_MAX_PAGE][SKILL_PER_PAGE_MAX_N];
	GtkWidget *mSkillNeedExp[SKILL_MAX_PAGE][SKILL_PER_PAGE_MAX_N];

	GtkWidget *mSkillTextScroll[SKILL_MAX_PAGE];
	GtkWidget *mSkillTextView[SKILL_MAX_PAGE];

	// �����ƥ�

	GtkWidget *mItemName[MBR_ITEM_MAX_N];

	// ����

	GtkWidget *mEquipName[MBR_ITEM_MAX_N];
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

	//////// �ѥ֥�å������С��ѿ� ////////
public:

	chr_t	*orgData;
	chr_t	*mbrData;

#ifdef D_WS
	void *mChrSheetWin;
#endif // D_WS

#ifdef D_GTK
	GtkWidget *mChrSheetWin;
#endif // D_GTK

#ifdef D_MAC
//@@@
	void *mChrSheetWin;
#endif // D_MAC
	
#ifdef D_IPHONE
//@@@
	void *mChrSheetWin;
#endif // D_IPHONE
	
#ifdef D_MFC
	class CChrSheetSheet *mChrSheetWin;
#endif // D_MFC

	//////// �ѥ֥�å������С��ؿ� ////////
public:

	GuiChrSheet();
	~GuiChrSheet();
	void init();
	void destroy();

	void draw( mbr_t *org, mbr_t *mbr );
	void redraw();
	void wipe();

	void okClicked();
	void cancelClicked();
	void nextChrClicked();
	void prevChrClicked();

	bool nameChanged();
	bool faceChanged();
	bool raceClicked();
	bool raceNameChanged();
	bool sexClicked();
	bool tileClicked();

	bool classClicked();
	bool skillClicked( long n );
	bool itemClicked( long n );
	bool equipClicked( long n );

	//////// �ץ饤�١��ȡ����С��ؿ� ////////
private:

	void newWin();
	void newWinMisc();
	void newWinStatTab();
	void newWinAblTab();
	void newWinSkillTab( long page );
	void newWinItemTab();
	void newWinEquipTab();

	void drawMisc( mbr_t *org, mbr_t *mbr );
	void drawStat( mbr_t *org, mbr_t *mbr );
	void drawAbl( mbr_t *org, mbr_t *mbr );
	void drawSkill( mbr_t *org, mbr_t *mbr, long page );
	void drawSkillHint( long nSlot );
	void drawItem( mbr_t *org, mbr_t *mbr );
	void drawEquip( mbr_t *org, mbr_t *mbr );

	void DdxToSheet();
	void DdxFromSheet();
};

#endif /* GUI_CHR_SHEET_H */
