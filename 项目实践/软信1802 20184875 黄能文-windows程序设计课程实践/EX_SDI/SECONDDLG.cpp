// SECONDDLG.cpp: 实现文件
//

#include "pch.h"
#include "EX_SDI.h"
#include "SECONDDLG.h"
#include "afxdialogex.h"


// CSECONDDLG 对话框

IMPLEMENT_DYNAMIC(CSECONDDLG, CDialogEx)

CSECONDDLG::CSECONDDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_second, pParent)
{

}

CSECONDDLG::~CSECONDDLG()
{
}

void CSECONDDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSECONDDLG, CDialogEx)
END_MESSAGE_MAP()


// CSECONDDLG 消息处理程序


void CSECONDDLG::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}


void CSECONDDLG::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}
