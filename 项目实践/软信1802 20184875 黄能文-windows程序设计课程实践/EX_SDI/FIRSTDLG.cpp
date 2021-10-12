// FIRSTDLG.cpp: 实现文件
//

#include "pch.h"
#include "EX_SDI.h"
#include "FIRSTDLG.h"
#include "afxdialogex.h"


// CFIRSTDLG 对话框

IMPLEMENT_DYNAMIC(CFIRSTDLG, CDialogEx)

CFIRSTDLG::CFIRSTDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FIRST, pParent)
{

}

CFIRSTDLG::~CFIRSTDLG()
{
}

void CFIRSTDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFIRSTDLG, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFIRSTDLG::OnBnClickedOk)
END_MESSAGE_MAP()


// CFIRSTDLG 消息处理程序


void CFIRSTDLG::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CFIRSTDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CDialogEx::OnInitDialog();
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC_2);
	pWnd->SetWindowText(_T("这是我的第一个对话框！"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
