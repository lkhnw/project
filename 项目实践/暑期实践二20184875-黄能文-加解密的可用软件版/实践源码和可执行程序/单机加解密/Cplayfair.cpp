// Cplayfair.cpp: 实现文件
//

#include "pch.h"
#include "单机加解密.h"
#include "Cplayfair.h"
#include "afxdialogex.h"
#include "function.h"


// Cplayfair 对话框

IMPLEMENT_DYNAMIC(Cplayfair, CDialogEx)

Cplayfair::Cplayfair(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, txt0(_T(""))
	, key0(_T(""))
	, txt1(_T(""))
	, key1(_T(""))
{

}

Cplayfair::~Cplayfair()
{
}

void Cplayfair::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, txt0);
	DDX_Text(pDX, IDC_EDIT2, key0);
	DDX_Control(pDX, IDC_EDIT3, result0);
	DDX_Text(pDX, IDC_EDIT4, txt1);
	DDX_Text(pDX, IDC_EDIT5, key1);
	DDX_Control(pDX, IDC_EDIT6, result1);
}


BEGIN_MESSAGE_MAP(Cplayfair, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cplayfair::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cplayfair::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cplayfair 消息处理程序


void Cplayfair::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt0;
	LPSTR key = (LPSTR)(LPCTSTR)key0;
	char* result = PlayfairEncryption(txt, key);
	result0.SetWindowText(result);
}


void Cplayfair::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt1;
	LPSTR key = (LPSTR)(LPCTSTR)key1;
	char* result = PlayfairDecryption(txt, key);
	result1.SetWindowText(result);

}
