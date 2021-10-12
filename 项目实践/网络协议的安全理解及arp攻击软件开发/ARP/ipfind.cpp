// ipfind.cpp: 实现文件
//

#include "pch.h"
#include "ARP.h"
#include "ipfind.h"
#include "afxdialogex.h"


// Cipfind 对话框

IMPLEMENT_DYNAMIC(Cipfind, CDialogEx)

Cipfind::Cipfind(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Cipfind::~Cipfind()
{
}

void Cipfind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cipfind, CDialogEx)
END_MESSAGE_MAP()


// Cipfind 消息处理程序
