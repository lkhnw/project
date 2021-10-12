// ARPDIG.cpp: 实现文件
//

#include "pch.h"
#include "ARP.h"
#include "ARPDIG.h"
#include "afxdialogex.h"
#include "ARPbuild.h"


// CARPDIG 对话框

IMPLEMENT_DYNAMIC(CARPDIG, CDialogEx)

CARPDIG::CARPDIG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1_ARP, pParent)
	, srcmacvalue(_T(""))
	, srcipvalue(_T(""))
	, desmacvalue(_T(""))
	, desipvalue(_T(""))
	, num(0)
	, time(0)
{

}

CARPDIG::~CARPDIG()
{
}

void CARPDIG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, srcmacvalue);
	DDX_Text(pDX, IDC_EDIT2, srcipvalue);
	DDX_Text(pDX, IDC_EDIT3, desmacvalue);
	DDX_Text(pDX, IDC_EDIT4, desipvalue);
	DDX_Text(pDX, IDC_EDIT5, num);
	DDV_MinMaxInt(pDX, num, 0, INT_MAX);
	DDX_Text(pDX, IDC_EDIT6, time);
	DDV_MinMaxInt(pDX, time, 1, 60);
	DDX_Control(pDX, IDC_EDIT1, srcmac);
	DDX_Control(pDX, IDC_EDIT2, srcip);
	DDX_Control(pDX, IDC_EDIT3, desmac);
	DDX_Control(pDX, IDC_EDIT4, desip);
	DDX_Control(pDX, IDC_EDIT5, Num);
	DDX_Control(pDX, IDC_EDIT6, Time);
	DDX_Control(pDX, IDOK, okbutton);
	DDX_Control(pDX, IDCANCEL, show);
	DDX_Control(pDX, IDC_STATIC_9, sh);
}


BEGIN_MESSAGE_MAP(CARPDIG, CDialogEx)
END_MESSAGE_MAP()


// CARPDIG 消息处理程序


BOOL CARPDIG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	srcmac.SetWindowTextW(L"ff:ff:ff:ff:ff:ff");
	srcip.SetWindowTextW(L"0.0.0.0");
	desmac.SetWindowTextW(L"ff:ff:ff:ff:ff:ff");
	desip.SetWindowTextW(L"0.0.0.0");
	Num.SetWindowTextW(L"60");
	Time.SetWindowTextW(L"1");
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CARPDIG::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	ARPbuild* a = new ARPbuild();
	USES_CONVERSION;
	sh.SetWindowTextW(L"正在发送");
	a->sendarp(T2A(srcmacvalue),T2A(srcipvalue),T2A(desmacvalue),T2A(desipvalue),num,time);
	sh.SetWindowTextW(L"发送结束");
	//CDialogEx::OnOK();
}
