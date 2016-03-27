// SkillEditDlg.cpp : �����ե�����
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "SkillEditDlg.h"
#include ".\skilleditdlg.h"

#include "../misc.h"
#include "../misc-prot.h"
#include "../GlobalVar.h"


// CSkillEditDlg ��������

IMPLEMENT_DYNAMIC(CSkillEditDlg, CDialog)
CSkillEditDlg::CSkillEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkillEditDlg::IDD, pParent)
	, mEditName(_T(""))
{
}

CSkillEditDlg::~CSkillEditDlg()
{
}

void CSkillEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SKILL_EDIT_CLASS, mEditName);
}


BEGIN_MESSAGE_MAP(CSkillEditDlg, CDialog)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_00, OnBnClickedSkillEditSkill00)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_01, OnBnClickedSkillEditSkill01)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_02, OnBnClickedSkillEditSkill02)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_03, OnBnClickedSkillEditSkill03)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_04, OnBnClickedSkillEditSkill04)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_05, OnBnClickedSkillEditSkill05)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_06, OnBnClickedSkillEditSkill06)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_07, OnBnClickedSkillEditSkill07)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_08, OnBnClickedSkillEditSkill08)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_09, OnBnClickedSkillEditSkill09)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_10, OnBnClickedSkillEditSkill10)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_11, OnBnClickedSkillEditSkill11)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_12, OnBnClickedSkillEditSkill12)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_13, OnBnClickedSkillEditSkill13)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_14, OnBnClickedSkillEditSkill14)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_15, OnBnClickedSkillEditSkill15)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_16, OnBnClickedSkillEditSkill16)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_17, OnBnClickedSkillEditSkill17)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_18, OnBnClickedSkillEditSkill18)
	ON_BN_CLICKED(IDC_SKILL_EDIT_SKILL_19, OnBnClickedSkillEditSkill19)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SKILL_EDIT_PREV, OnBnClickedSkillEditPrev)
	ON_BN_CLICKED(IDC_SKILL_EDIT_NEXT, OnBnClickedSkillEditNext)
END_MESSAGE_MAP()


// CSkillEditDlg ��å����� �ϥ�ɥ�

BOOL CSkillEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  �����˽�������ɲä��Ƥ�������

	gGuiSkillEdit.redraw();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �㳰 : OCX �ץ�ѥƥ� �ڡ�����ɬ�� FALSE ���֤��ޤ���
}

void CSkillEditDlg::SetClassName()
{
	UpdateData( TRUE );

	class_t *p = gGuiSkillEdit.classData;
	if( p != NULL )
		str_nz_cpy( p->name, mEditName, CLASS_NAME_MAX_LEN );
}

void CSkillEditDlg::OnBnClickedSkillEditSkill00()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 0 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill01()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 1 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill02()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 2 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill03()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 3 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill04()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 4 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill05()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 5 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill06()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 6 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill07()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 7 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill08()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 8 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill09()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 9 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill10()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 10 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill11()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 11 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill12()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 12 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill13()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 13 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill14()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 14 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill15()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 15 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill16()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 16 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill17()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 17 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill18()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 18 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditSkill19()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.skillClicked( 19 );
	OnOK();
}

void CSkillEditDlg::OnBnClickedOk()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.exitClicked();
	OnOK();
}

void CSkillEditDlg::OnBnClickedCancel()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.exitClicked();
	OnCancel();
}

void CSkillEditDlg::OnBnClickedSkillEditPrev()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.prevClicked();
	OnOK();
}

void CSkillEditDlg::OnBnClickedSkillEditNext()
{
	// TODO : �����˥���ȥ������Υϥ�ɥ� �����ɤ��ɲä��ޤ���
	SetClassName();
	gGuiSkillEdit.nextClicked();
	OnOK();
}
