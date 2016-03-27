// ChrSheetStat.cpp : 実装ファイル
//

#include "stdafx.h"
#include "../misc.h"
#include "../draw.h"
#include "../menu.h"
#include "../misc-prot.h"
#include "../imenu-prot.h"
#include "xlnl-dows.h"
#include "ChrSheetStat.h"
#include ".\chrsheetstat.h"
#include "ChrSheetSheet.h"
#include "../GlobalVar.h"


// CChrSheetStat ダイアログ

IMPLEMENT_DYNAMIC(CChrSheetStat, CPropertyPage)
CChrSheetStat::CChrSheetStat()
	: CPropertyPage(CChrSheetStat::IDD)
{
}

CChrSheetStat::~CChrSheetStat()
{
}

void CChrSheetStat::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChrSheetStat, CPropertyPage)
	ON_BN_CLICKED(IDC_CHR_SHEET_STAT_RACE, OnBnClickedChrSheetStatRace)
	ON_BN_CLICKED(IDC_CHR_SHEET_STAT_SEX, OnBnClickedChrSheetStatSex)
	ON_EN_CHANGE(IDC_CHR_SHEET_STAT_NAME_EDIT, OnEnChangeChrSheetStatNameEdit)
	ON_EN_CHANGE(IDC_CHR_SHEET_STAT_FACE, OnEnChangeChrSheetStatFace)
	ON_EN_CHANGE(IDC_CHR_SHEET_STAT_RACE_NAME, OnEnChangeChrSheetStatRaceName)
	ON_BN_CLICKED(IDC_CHR_SHEET_STAT_PREV, OnBnClickedChrSheetStatPrev)
	ON_BN_CLICKED(IDC_CHR_SHEET_STAT_NEXT, OnBnClickedChrSheetStatNext)
	ON_BN_CLICKED(IDC_CHR_SHEET_STAT_GRAPH_FILE, OnBnClickedChrSheetStatGraphFile)
END_MESSAGE_MAP()


// CChrSheetStat メッセージ ハンドラ

BOOL CChrSheetStat::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO :  ここに初期化を追加してください

	CStatic *label;
	CEdit *edit;
	CButton *btn;
	CString s;

	// 名前

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_NAME );
	label->SetWindowText( m_StrName );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_PREV );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_PREV_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_PREV_PAGE );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_NEXT );
	if( get_flg_mbr_data_change_page_is_crsr() )
		label->SetWindowText( MSG_MBR_DATA_NEXT_MBR );
	else
		label->SetWindowText( MSG_MBR_DATA_NEXT_PAGE );

	// タイトル

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_NAME_EDIT_TTL );
	label->SetWindowText( MSG_MBR_DATA_NAME_TTL );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_FACE_TTL );
	label->SetWindowText( MSG_MBR_DATA_FACE_TTL );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_RACE_TTL );
	label->SetWindowText( MSG_MBR_DATA_RACE_STR_TTL );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_RACE_NAME_TTL );
	label->SetWindowText( MSG_MBR_DATA_RACE_NAME_TTL );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_SEX_TTL );
	label->SetWindowText( MSG_MBR_DATA_SEX_TTL );

	// 

	edit = (CEdit *)GetDlgItem( IDC_CHR_SHEET_STAT_NAME_EDIT );
	edit->SetWindowText( m_StrNameEdit );

	edit = (CEdit *)GetDlgItem( IDC_CHR_SHEET_STAT_FACE );
	edit->SetWindowText( m_StrFace );

	btn = (CButton *)GetDlgItem( IDC_CHR_SHEET_STAT_RACE );
	btn->SetWindowText( m_StrRace );

	edit = (CEdit *)GetDlgItem( IDC_CHR_SHEET_STAT_RACE_NAME );
	edit->SetWindowText( m_StrRaceName );

	btn = (CButton *)GetDlgItem( IDC_CHR_SHEET_STAT_SEX );
	btn->SetWindowText( m_StrSex );

	// HP/MP

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_HP_TTL );
	label->SetWindowText( MSG_MBR_DATA_HP_VAL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_HP_N );
	label->SetWindowText( m_StrHp[0] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_HP_MAX );
	label->SetWindowText( m_StrHp[1] );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_MP_TTL );
	label->SetWindowText( MSG_MBR_DATA_MP_VAL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_MP_N );
	label->SetWindowText( m_StrMp[0] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_MP_MAX );
	label->SetWindowText( m_StrMp[1] );

	// 戦闘能力

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_HIT_TTL );
	label->SetWindowText( MSG_MBR_DATA_HIT_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_HIT_DIR );
	label->SetWindowText( m_StrHit[0] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_HIT_IND );
	label->SetWindowText( m_StrHit[1] );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_WPN_CRTCL_TTL );
	label->SetWindowText( MSG_MBR_DATA_WPN_CRTCL_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_WPN_CRTCL_DIR );
	label->SetWindowText( m_StrWpnCrtcl[0] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_WPN_CRTCL_IND );
	label->SetWindowText( m_StrWpnCrtcl[1] );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_DAM_TTL );
	label->SetWindowText( MSG_MBR_DATA_DAM_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_DAM_DIR );
	label->SetWindowText( m_StrDam[0] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_DAM_IND );
	label->SetWindowText( m_StrDam[1] );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_DEF_TTL );
	label->SetWindowText( MSG_MBR_DATA_DEF_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_DEF_DIR );
	label->SetWindowText( m_StrDef[0] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_DEF_IND );
	label->SetWindowText( m_StrDef[1] );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_ARMOR_CRTCL_TTL );
	label->SetWindowText( MSG_MBR_DATA_ARMOR_CRTCL_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_ARMOR_CRTCL_DIR );
	label->SetWindowText( m_StrArmorCrtcl[0] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_ARMOR_CRTCL_IND );
	label->SetWindowText( m_StrArmorCrtcl[1] );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_AC_TTL );
	label->SetWindowText( MSG_MBR_DATA_AC_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_AC_DIR );
	label->SetWindowText( m_StrAc[0] );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_F_AC_IND );
	label->SetWindowText( m_StrAc[1] );

	// 所持金

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_GOLD_TTL );
	label->SetWindowText( MSG_MBR_DATA_GOLD_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_GOLD );
	label->SetWindowText( m_StrGold );

	// 時間

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_CALENDER );
	label->SetWindowText( m_StrCalender );

	// 状態

	for( long i = 0; i < STAT_MAX_N; i++ ){
		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_STAT_0 + i );
		label->SetWindowText( m_StrStat[i] );
	}

	// 明かり

	s = MSG_MBR_DATA_STORE_LIGHT_TTL;
	s += " : ";
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_STORE_LIGHT_TTL );
	label->SetWindowText( s );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_STORE_LIGHT );
	label->SetWindowText( m_StrLight );

	// タイル

	s = MSG_MBR_DATA_GRAPH_FILE_TTL;
	s += " : ";
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_GRAPH_FILE_TTL );
	label->SetWindowText( s );

	btn = (CButton *)GetDlgItem( IDC_CHR_SHEET_STAT_GRAPH_FILE );
	btn->SetWindowText( m_StrGraphFile );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CChrSheetStat::OnBnClickedChrSheetStatRace()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	if( gGuiChrSheet.raceClicked() ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}

void CChrSheetStat::OnBnClickedChrSheetStatSex()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	if( gGuiChrSheet.sexClicked() ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}

void CChrSheetStat::OnEnChangeChrSheetStatNameEdit()
{
	// TODO :  これが RICHEDIT コントロールの場合、まず、CPropertyPage::OnInitDialog() 関数をオーバーライドして、
	// OR 状態の ENM_CORRECTTEXT フラグをマスクに入れて、
	// CRichEditCtrl().SetEventMask() を呼び出さない限り、
	// コントロールは、この通知を送信しません。

	// TODO :  ここにコントロール通知ハンドラ コードを追加してください。

	CEdit *edit = (CEdit *)GetDlgItem( IDC_CHR_SHEET_STAT_NAME_EDIT );
	CString s;
	edit->GetWindowText( s );
	if( s != "" ){
		str_nz_cpy( gGuiChrSheet.mbrData->name, s, MBR_NAME_MAX_LEN );
	}
}

void CChrSheetStat::OnEnChangeChrSheetStatFace()
{
	// TODO :  これが RICHEDIT コントロールの場合、まず、CPropertyPage::OnInitDialog() 関数をオーバーライドして、
	// OR 状態の ENM_CORRECTTEXT フラグをマスクに入れて、
	// CRichEditCtrl().SetEventMask() を呼び出さない限り、
	// コントロールは、この通知を送信しません。

	// TODO :  ここにコントロール通知ハンドラ コードを追加してください。

	CEdit *edit = (CEdit *)GetDlgItem( IDC_CHR_SHEET_STAT_FACE );
	CString s;
	edit->GetWindowText( s );
	if( s != "" ){
		gGuiChrSheet.mbrData->face.mnr = s[0];
		gGuiChrSheet.mbrData->face.mnr_org = s[0];
	}
}

void CChrSheetStat::OnEnChangeChrSheetStatRaceName()
{
	// TODO :  これが RICHEDIT コントロールの場合、まず、CPropertyPage::OnInitDialog() 関数をオーバーライドして、
	// OR 状態の ENM_CORRECTTEXT フラグをマスクに入れて、
	// CRichEditCtrl().SetEventMask() を呼び出さない限り、
	// コントロールは、この通知を送信しません。

	// TODO :  ここにコントロール通知ハンドラ コードを追加してください。

	CEdit *edit = (CEdit *)GetDlgItem( IDC_CHR_SHEET_STAT_RACE_NAME );
	CString s;
	edit->GetWindowText( s );
	if( s != "" ){
		str_nz_cpy( gGuiChrSheet.mbrData->race.name, s, RACE_NAME_MAX_LEN );
	}
}

void CChrSheetStat::OnBnClickedChrSheetStatPrev()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	gGuiChrSheet.prevChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}

void CChrSheetStat::OnBnClickedChrSheetStatNext()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	gGuiChrSheet.nextChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}

void CChrSheetStat::OnBnClickedChrSheetStatGraphFile()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	if( gGuiChrSheet.tileClicked() ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}
