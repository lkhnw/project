// Crc4.cpp: 实现文件
//

#include "pch.h"
#include "单机加解密.h"
#include "Crc4.h"
#include "afxdialogex.h"
#include "function.h"

// Crc4 对话框

IMPLEMENT_DYNAMIC(Crc4, CDialogEx)

Crc4::Crc4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, txt0(_T(""))
	, key0(_T(""))
	, txt1(_T(""))
	, key1(_T(""))
{

}

Crc4::~Crc4()
{
}

void Crc4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, txt0);
	DDX_Text(pDX, IDC_EDIT2, key0);
	DDX_Control(pDX, IDC_EDIT3, result0);
	DDX_Text(pDX, IDC_EDIT4, txt1);
	DDX_Text(pDX, IDC_EDIT5, key1);
	DDX_Control(pDX, IDC_EDIT6, result1);
}


BEGIN_MESSAGE_MAP(Crc4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Crc4::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Crc4::OnBnClickedButton2)
END_MESSAGE_MAP()


// Crc4 消息处理程序


void Crc4::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt0;
	LPSTR key = (LPSTR)(LPCTSTR)key0;
	char* result = rc4en(txt, key);
	result0.SetWindowText(result);
}


void Crc4::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt1;
	LPSTR key = (LPSTR)(LPCTSTR)key1;
	char* result = rc4de(txt, key);
	result1.SetWindowText(result);
}
