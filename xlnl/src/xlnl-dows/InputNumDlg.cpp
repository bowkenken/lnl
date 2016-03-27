// InputNumDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "xlnl-dows.h"
#include "InputNumDlg.h"

#include "../misc.h"
#include "../misc-prot.h"
#include "../GlobalVar.h"
#include ".\inputnumdlg.h"


// CInputNumDlg ダイアログ

IMPLEMENT_DYNAMIC(CInputNumDlg, CDialog)
CInputNumDlg::CInputNumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputNumDlg::IDD, pParent)
{
	m_FlagInit = false;
}

CInputNumDlg::~CInputNumDlg()
{
}

void CInputNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NUM_EDIT, m_Edit);
	DDX_Control(pDX, IDC_NUM_SPN, m_Spn);
	DDX_Control(pDX, IDC_NUM_SLDR, m_Sldr);
}


BEGIN_MESSAGE_MAP(CInputNumDlg, CDialog)
	ON_CONTROL_RANGE( BN_CLICKED, IDC_NUM_CLR_BGN, IDC_NUM_DEC_END, OnBtnClickRange )
	ON_BN_CLICKED(IDC_NUM_BTN_MIN, OnBnClickedNumBtnMin)
	ON_BN_CLICKED(IDC_NUM_BTN_CLR, OnBnClickedNumBtnClr)
	ON_BN_CLICKED(IDC_NUM_BTN_MAX, OnBnClickedNumBtnMax)
	ON_EN_CHANGE(IDC_NUM_EDIT, OnEnChangeNumEdit)
	ON_WM_HSCROLL()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CInputNumDlg メッセージ ハンドラ

BOOL CInputNumDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  ここに初期化を追加してください

	// インクリメント・ボタンの座標

	gWinPos[WIN_KIND_INPUT_NUM].draw( WIN_KIND_INPUT_NUM, true );

	long max;
	max = IDC_NUM_CLR_END - IDC_NUM_CLR_BGN + 1;
	max = min_l( max, NUM_BTN_MAX );

	const long w = 29;
	const long h = 29;
	const long xOffset = 10;
	const long yOffset = 10;
	const long xSpc = 0;
	const long ySpc = 0;

	CRect rectClr, rectInc, rectDec;

	rectClr.top = (yOffset + h) * 1 + yOffset;
	rectClr.bottom = rectClr.top + h;
	rectClr.left = 10;

	rectInc.top = rectClr.top + h + ySpc;
	rectInc.bottom = rectInc.top + h;
	rectInc.left = 10;

	rectDec.top = rectInc.top + h + ySpc;
	rectDec.bottom = rectDec.top + h;
	rectDec.left = 10;

	// インクリメント・ボタンの初期化

	for( long i = max - 1; i >= 0; i-- ){
		rectClr.right = rectClr.left + w;
		rectInc.right = rectInc.left + w;
		rectDec.right = rectDec.left + w;

		m_Clr[i].Create( "", 0, rectClr, this,
				IDC_NUM_CLR_BGN + i );
		m_Clr[i].SetWindowText( "0" );
		m_Clr[i].ShowWindow( SW_SHOW );

		m_Inc[i].Create( "", 0, rectInc, this,
				IDC_NUM_INC_BGN + i );
		m_Inc[i].SetWindowText( "+" );
		m_Inc[i].ShowWindow( SW_SHOW );

		m_Dec[i].Create( "", 0, rectDec, this,
				IDC_NUM_DEC_BGN + i );
		m_Dec[i].SetWindowText( "-" );
		m_Dec[i].ShowWindow( SW_SHOW );

		rectClr.left += w + xSpc;
		rectInc.left += w + xSpc;
		rectDec.left += w + xSpc;
	}

	// スピン

	m_Spn.SetRange( (short)m_Min, (short)m_Max );
	m_Spn.SetPos( *m_Cur );

	// スライダー

	long sldrMin = m_Min;
	long sldrMax = m_Max;
	long sldrCur = *m_Cur;

	for( long i = 0; i < gGuiNum.mFigure - SLDR_FIGURE; i++ ){
		sldrMin /= 10;
		sldrMax /= 10;
		sldrCur /= 10;
	}
	sldrMin += -1;
	sldrMax += +1;

	m_Sldr.SetRange( (short)sldrMin, (short)sldrMax );
	m_Sldr.SetPageSize( 1 );
	m_Sldr.SetLineSize( 1 );
	m_Sldr.SetPos( sldrCur );

	//

	gGuiNum.cvUpDownFromN();

	m_FlagInit = true;

	gGuiNum.redraw();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CInputNumDlg::OnBtnClickRange( UINT id )
{
	if( (IDC_NUM_CLR_BGN <= id)
			&& (id <= IDC_NUM_CLR_END) ){
		long n = id - IDC_NUM_CLR_BGN;
		gGuiNum.up_down_num_label( n, +-0 );
	}
	if( (IDC_NUM_INC_BGN <= id)
			&& (id <= IDC_NUM_INC_END) ){
		long n = id - IDC_NUM_INC_BGN;
		gGuiNum.up_down_num_label( n, +1 );
	}
	if( (IDC_NUM_DEC_BGN <= id)
			&& (id <= IDC_NUM_DEC_END) ){
		long n = id - IDC_NUM_DEC_BGN;
		gGuiNum.up_down_num_label( n, -1 );
	}
}

void CInputNumDlg::OnBnClickedNumBtnMin()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	*m_Cur = m_Min;
	gGuiNum.cvUpDownFromN();
	gGuiNum.redraw();
}

void CInputNumDlg::OnBnClickedNumBtnClr()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	*m_Cur = m_Org;
	gGuiNum.cvUpDownFromN();
	gGuiNum.redraw();
}

void CInputNumDlg::OnBnClickedNumBtnMax()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。

	*m_Cur = m_Max;
	gGuiNum.cvUpDownFromN();
	gGuiNum.redraw();
}

void CInputNumDlg::OnOK()
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	gWinPos[WIN_KIND_INPUT_NUM].wipe( WIN_KIND_INPUT_NUM, true );

	m_FlagInit = true;
	OnEnChangeNumEdit();

	gGuiNum.okClicked( MENU_NUM_OK );

	CDialog::OnOK();
}

void CInputNumDlg::OnCancel()
{
	// TODO : ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	gWinPos[WIN_KIND_INPUT_NUM].wipe( WIN_KIND_INPUT_NUM, true );

	gKey.setChar( '0' );

	CDialog::OnCancel();
}

void CInputNumDlg::OnEnChangeNumEdit()
{
	// TODO :  これが RICHEDIT コントロールの場合、まず、CDialog::OnInitDialog() 関数をオーバーライドして、
	// OR 状態の ENM_CORRECTTEXT フラグをマスクに入れて、
	// CRichEditCtrl().SetEventMask() を呼び出さない限り、
	// コントロールは、この通知を送信しません。

	if( m_FlagInit ){
		CString str;
		m_Edit.GetWindowText( str );
		long n = un_fmt_num( str );

		if( *m_Cur == n )
			return;
		*m_Cur = n;

		gGuiNum.cvUpDownFromN();

		SetSldrPos( n );
	}

	// TODO :  ここにコントロール通知ハンドラ コードを追加してください。
}

void CInputNumDlg::SetSldrPos( long n )
{
	long f = gGuiNum.mFigure - SLDR_FIGURE;
	for( long i = 0; i < f; i++ )
		n /= 10;

	m_Sldr.SetPos( n );
}

void CInputNumDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	if( (CSliderCtrl *)pScrollBar == &m_Sldr ){
		long n = m_Sldr.GetPos();
		long f = gGuiNum.mFigure - SLDR_FIGURE;
		for( long i = 0; i < f; i++ )
			n *= 10;

		if( n < m_Min )
			n = m_Min;
		if( n > m_Max)
			n = m_Max;

		if( *m_Cur == n )
			return;
		*m_Cur = n;

		gGuiNum.cvUpDownFromN();

		m_Edit.SetWindowText( fmt_num( n ) );
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CInputNumDlg::OnClose()
{
	// TODO : ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	gWinPos[WIN_KIND_INPUT_NUM].wipe( WIN_KIND_INPUT_NUM, true );

	CDialog::OnClose();
}
