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
* $Id: GuiChrSheet.h,v 1.19 2014/01/07 23:44:46 bowkenken Exp $
***************************************************************/

#ifndef GUI_CHR_SHEET_H
#define GUI_CHR_SHEET_H	1

////////////////////////////////////////////////////////////////
// キャラクタ・シート・ウィンドウ
////////////////////////////////////////////////////////////////

class GuiChrSheet {

	//////// プライベート・メンバー変数 ////////
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

	// ステータス (左)

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

	// ステータス (右)

	GtkWidget *mStatStat[STAT_MAX_N];
	GtkWidget *mStatLight;
	GtkWidget *mStatTile;

	// 能力値

	GtkWidget *mAblClass;

	GtkWidget *mAblLev[ABL_KIND_MAX_N];
	GtkWidget *mAblAddLev[ABL_KIND_MAX_N];
	GtkWidget *mAblExp[ABL_KIND_MAX_N];
	GtkWidget *mAblNeedExp[ABL_KIND_MAX_N];

	GtkWidget *mAblResi[3][3];

	// スキル

	GtkWidget *mSkillClass;

	GtkWidget *mSkillName[SKILL_MAX_PAGE][SKILL_PER_PAGE_MAX_N];
	GtkWidget *mSkillLev[SKILL_MAX_PAGE][SKILL_PER_PAGE_MAX_N];
	GtkWidget *mSkillExp[SKILL_MAX_PAGE][SKILL_PER_PAGE_MAX_N];
	GtkWidget *mSkillNeedExp[SKILL_MAX_PAGE][SKILL_PER_PAGE_MAX_N];

	GtkWidget *mSkillTextScroll[SKILL_MAX_PAGE];
	GtkWidget *mSkillTextView[SKILL_MAX_PAGE];

	// アイテム

	GtkWidget *mItemName[MBR_ITEM_MAX_N];

	// 装備

	GtkWidget *mEquipName[MBR_ITEM_MAX_N];
#endif // D_GTK

#ifdef D_MFC
#endif // D_MFC

	//////// パブリック・メンバー変数 ////////
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

	//////// パブリック・メンバー関数 ////////
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

	//////// プライベート・メンバー関数 ////////
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
