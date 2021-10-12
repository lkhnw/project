// Crsa.cpp: 实现文件
//

#include "pch.h"
#include "单机加解密.h"
#include "Crsa.h"
#include "afxdialogex.h"


// Crsa 对话框

IMPLEMENT_DYNAMIC(Crsa, CDialogEx)

Crsa::Crsa(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG8, pParent)
{

}

Crsa::~Crsa()
{
}

void Crsa::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Crsa, CDialogEx)
END_MESSAGE_MAP()


// Crsa 消息处理程序
