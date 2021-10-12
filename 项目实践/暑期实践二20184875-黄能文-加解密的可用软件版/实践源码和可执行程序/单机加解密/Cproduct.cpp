// Cproduct.cpp: 实现文件
//

#include "pch.h"
#include "单机加解密.h"
#include "Cproduct.h"
#include "afxdialogex.h"


// Cproduct 对话框

IMPLEMENT_DYNAMIC(Cproduct, CDialogEx)

Cproduct::Cproduct(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

Cproduct::~Cproduct()
{
}

void Cproduct::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cproduct, CDialogEx)
END_MESSAGE_MAP()


// Cproduct 消息处理程序
