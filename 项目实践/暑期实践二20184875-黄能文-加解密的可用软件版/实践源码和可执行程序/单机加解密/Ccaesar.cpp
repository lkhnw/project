// Ccaesar.cpp: 实现文件
//

#include "pch.h"
#include "单机加解密.h"
#include "Ccaesar.h"
#include "afxdialogex.h"
#include "function.h"


// Ccaesar 对话框

IMPLEMENT_DYNAMIC(Ccaesar, CDialogEx)

Ccaesar::Ccaesar(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, txt0(_T(""))
	, key0(_T(""))
	, txt1(_T(""))
	, key1(_T(""))
{

}

Ccaesar::~Ccaesar()
{
}

void Ccaesar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, txt0);
	DDX_Text(pDX, IDC_EDIT2, key0);
	DDX_Control(pDX, IDC_EDIT3, result0);
	DDX_Text(pDX, IDC_EDIT4, txt1);
	DDX_Text(pDX, IDC_EDIT5, key1);
	DDX_Control(pDX, IDC_EDIT6, result1);
}


BEGIN_MESSAGE_MAP(Ccaesar, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Ccaesar::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Ccaesar::OnBnClickedButton2)
END_MESSAGE_MAP()


// Ccaesar 消息处理程序


void Ccaesar::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt0;
	int key = key0.GetLength();
	char* result = CaesarEncryption(txt, key);
	result0.SetWindowText(result);
}


void Ccaesar::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	LPSTR txt = (LPSTR)(LPCTSTR)txt1;
	int key = key1.GetLength();
	char* result = CaesarDecryption(txt, key);
	result1.SetWindowText(result);
}
