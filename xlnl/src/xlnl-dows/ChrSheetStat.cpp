// ChrSheetStat.cpp : �����ե�����
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


// CChrSheetStat ��������

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


// CChrSheetStat ��å����� �ϥ�ɥ�

BOOL CChrSheetStat::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO :  �����˽�������ɲä��Ƥ�������

	CStatic *label;
	CEdit *edit;
	CButton *btn;
	CString s;

	// ̾��

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

	// �����ȥ�

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

	// ��Ʈǽ��

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

	// �����

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_GOLD_TTL );
	label->SetWindowText( MSG_MBR_DATA_GOLD_TTL );
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_GOLD );
	label->SetWindowText( m_StrGold );

	// ����

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_CALENDER );
	label->SetWindowText( m_StrCalender );

	// ����

	for( long i = 0; i < STAT_MAX_N; i++ ){
		label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_STAT_0 + i );
		label->SetWindowText( m_StrStat[i] );
	}

	// ������

	s = MSG_MBR_DATA_STORE_LIGHT_TTL;
	s += " : ";
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_STORE_LIGHT_TTL );
	label->SetWindowText( s );

	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_STORE_LIGHT );
	label->SetWindowText( m_StrLight );

	// ������

	s = MSG_MBR_DATA_GRAPH_FILE_TTL;
	s += " : ";
	label = (CStatic *)GetDlgItem( IDC_CHR_SHEET_STAT_GRAPH_FILE_TTL );
	label->SetWindowText( s );

	btn = (CButton *)GetDlgItem( IDC_CHR_SHEET_STAT_GRAPH_FILE );
	btn->SetWindowText( m_StrGraphFile );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �㳰 : OCX �ץ�ѥƥ� �ڡ�����ɬ�� FALSE ���֤��ޤ���
}

void CChrSheetStat::OnBnClickedChrSheetStatRace()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	if( gGuiChrSheet.raceClicked() ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}

void CChrSheetStat::OnBnClickedChrSheetStatSex()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	if( gGuiChrSheet.sexClicked() ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}

void CChrSheetStat::OnEnChangeChrSheetStatNameEdit()
{
	// TODO :  ���줬 RICHEDIT ����ȥ���ξ�硢�ޤ���CPropertyPage::OnInitDialog() �ؿ��򥪡��С��饤�ɤ��ơ�
	// OR ���֤� ENM_CORRECTTEXT �ե饰��ޥ���������ơ�
	// CRichEditCtrl().SetEventMask() ��ƤӽФ��ʤ��¤ꡢ
	// ����ȥ���ϡ��������Τ��������ޤ���

	// TODO :  �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��Ƥ���������

	CEdit *edit = (CEdit *)GetDlgItem( IDC_CHR_SHEET_STAT_NAME_EDIT );
	CString s;
	edit->GetWindowText( s );
	if( s != "" ){
		str_nz_cpy( gGuiChrSheet.mbrData->name, s, MBR_NAME_MAX_LEN );
	}
}

void CChrSheetStat::OnEnChangeChrSheetStatFace()
{
	// TODO :  ���줬 RICHEDIT ����ȥ���ξ�硢�ޤ���CPropertyPage::OnInitDialog() �ؿ��򥪡��С��饤�ɤ��ơ�
	// OR ���֤� ENM_CORRECTTEXT �ե饰��ޥ���������ơ�
	// CRichEditCtrl().SetEventMask() ��ƤӽФ��ʤ��¤ꡢ
	// ����ȥ���ϡ��������Τ��������ޤ���

	// TODO :  �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��Ƥ���������

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
	// TODO :  ���줬 RICHEDIT ����ȥ���ξ�硢�ޤ���CPropertyPage::OnInitDialog() �ؿ��򥪡��С��饤�ɤ��ơ�
	// OR ���֤� ENM_CORRECTTEXT �ե饰��ޥ���������ơ�
	// CRichEditCtrl().SetEventMask() ��ƤӽФ��ʤ��¤ꡢ
	// ����ȥ���ϡ��������Τ��������ޤ���

	// TODO :  �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��Ƥ���������

	CEdit *edit = (CEdit *)GetDlgItem( IDC_CHR_SHEET_STAT_RACE_NAME );
	CString s;
	edit->GetWindowText( s );
	if( s != "" ){
		str_nz_cpy( gGuiChrSheet.mbrData->race.name, s, RACE_NAME_MAX_LEN );
	}
}

void CChrSheetStat::OnBnClickedChrSheetStatPrev()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	gGuiChrSheet.prevChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}

void CChrSheetStat::OnBnClickedChrSheetStatNext()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	gGuiChrSheet.nextChrClicked();
	gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
	GetParent()->SendMessage( WM_CLOSE, IDOK );
}

void CChrSheetStat::OnBnClickedChrSheetStatGraphFile()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���

	if( gGuiChrSheet.tileClicked() ){
		gGuiChrSheet.mChrSheetWin->m_FlagContinue = true;
		GetParent()->SendMessage( WM_CLOSE, IDOK );
	}
}
