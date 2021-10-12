// Cvigenere.cpp: 实现文件
//

#include "pch.h"
#include "单机加解密.h"
#include "Cvigenere.h"
#include "afxdialogex.h"
#include "function.h"


// Cvigenere 对话框

IMPLEMENT_DYNAMIC(Cvigenere, CDialogEx)

Cvigenere::Cvigenere(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, txt0(_T(""))
	, key0(_T(""))
	, txt1(_T(""))
	, key1(_T(""))
{

}

Cvigenere::~Cvigenere()
{
}

void Cvigenere::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, txt0);
	DDX_Text(pDX, IDC_EDIT2, key0);
	DDX_Control(pDX, IDC_EDIT3, result0);
	DDX_Text(pDX, IDC_EDIT4, txt1);
	DDX_Text(pDX, IDC_EDIT5, key1);
	DDX_Control(pDX, IDC_EDIT6, result1);
}


BEGIN_MESSAGE_MAP(Cvigenere, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cvigenere::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cvigenere::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cvigenere 消息处理程序


void Cvigenere::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt0;
	LPSTR key = (LPSTR)(LPCTSTR)key0;
	char* result = VigenereEncryption(txt, key);
	result0.SetWindowText(result);
}


void Cvigenere::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt1;
	LPSTR key = (LPSTR)(LPCTSTR)key1;
	char* result = VigenereDecryption(txt, key);
	result1.SetWindowText(result);
}
