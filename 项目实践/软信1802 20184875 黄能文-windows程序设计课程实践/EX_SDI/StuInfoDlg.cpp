// StuInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "EX_SDI.h"
#include "StuInfoDlg.h"
#include "afxdialogex.h"


// CStuInfoDlg 对话框

IMPLEMENT_DYNAMIC(CStuInfoDlg, CDialogEx)

CStuInfoDlg::CStuInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUINFO, pParent)
	, m_strName(_T(""))
	, m_strNo(_T(""))
	, m_tBirth(COleDateTime::GetCurrentTime())
	, m_strSpecial(_T(""))
{

}

CStuInfoDlg::~CStuInfoDlg()
{
}

void CStuInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 10);
	DDX_Text(pDX, IDC_EDIT_NO, m_strNo);
	DDV_MaxChars(pDX, m_strNo, 10);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_tBirth);
	DDX_Control(pDX, IDC_COMBO_SPECIAL, m_comboSpecial);
	DDX_CBString(pDX, IDC_COMBO_SPECIAL, m_strSpecial);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_tBirth);
}


BEGIN_MESSAGE_MAP(CStuInfoDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_SPECIAL, &CStuInfoDlg::OnCbnSelchangeComboSpecial)
	ON_BN_CLICKED(IDOK, &CStuInfoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CStuInfoDlg 消息处理程序


void CStuInfoDlg::OnCbnSelchangeComboSpecial()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CStuInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CDialog::OnInitDialog();
	m_tBirth =  CTime(1986, 1, 1, 0, 0, 0);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CStuInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strName.TrimLeft();
	m_strNo.TrimLeft();
	if (m_strName.IsEmpty())
		MessageBox(L"必须要有姓名！");
	else if (m_strNo.IsEmpty())
		MessageBox(L"必须要有学号！");
	else
		CDialog::OnOK();

}
