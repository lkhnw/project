// Cdes.cpp: 实现文件
//

#include "pch.h"
#include "单机加解密.h"
#include "Cdes.h"
#include "afxdialogex.h"
#include "DES.h"

// Cdes 对话框

IMPLEMENT_DYNAMIC(Cdes, CDialogEx)

Cdes::Cdes(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, txt0(_T(""))
	, key0(_T(""))
	, txt1(_T(""))
	, key1(_T(""))
{

}

Cdes::~Cdes()
{
}

void Cdes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, txt0);
	DDX_Text(pDX, IDC_EDIT2, key0);
	DDX_Control(pDX, IDC_EDIT3, result0);
	DDX_Text(pDX, IDC_EDIT4, txt1);
	DDX_Text(pDX, IDC_EDIT5, key1);
	DDX_Control(pDX, IDC_EDIT6, result1);
}


BEGIN_MESSAGE_MAP(Cdes, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cdes::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cdes::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cdes 消息处理程序


void Cdes::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt0;
	LPSTR key = (LPSTR)(LPCTSTR)key0;
	char* result = ECB_encrypt(txt, key);
	result0.SetWindowText(result);
}


void Cdes::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt1;
	LPSTR key = (LPSTR)(LPCTSTR)key0;
	char* result = ECB_decrypt(txt, key);
	result1.SetWindowText(result);
}
