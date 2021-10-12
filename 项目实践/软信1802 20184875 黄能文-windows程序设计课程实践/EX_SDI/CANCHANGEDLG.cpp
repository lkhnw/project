// CANCHANGEDLG.cpp: 实现文件
//

#include "pch.h"
#include "EX_SDI.h"
#include "CANCHANGEDLG.h"
#include "afxdialogex.h"


// CCANCHANGEDLG 对话框

IMPLEMENT_DYNAMIC(CCANCHANGEDLG, CDialogEx)

CCANCHANGEDLG::CCANCHANGEDLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CANCHANGE, pParent)
	, m_StrEditValue(_T(""))
	, m_StrTip(_T(""))
{

}

CCANCHANGEDLG::~CCANCHANGEDLG()
{
}

void CCANCHANGEDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//这里是变量区，可以看见变量不仅仅声明了，还用函数合起对应的id和一个啥
	DDX_Control(pDX, IDC_BUTTON_NAMECHANGE, m_RelBtn);
	DDX_Control(pDX, IDC_EDIT_CHANGE, m_StrEdit);
	DDX_Text(pDX, IDC_EDIT_CHANGE, m_StrEditValue);
	DDV_MaxChars(pDX, m_StrEditValue, 20);
	DDX_Text(pDX, IDC_STATIC_CREATEBUTTONTEXT, m_StrTip);
	DDX_Control(pDX, IDC_STATIC_CREATEBUTTONTEXT, m_StrTipCtr);
}


BEGIN_MESSAGE_MAP(CCANCHANGEDLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_NAMECHANGE, &CCANCHANGEDLG::OnBnClickedButtonNamechange)
	ON_BN_CLICKED(IDC_BUTTON_CREATETEXT, &CCANCHANGEDLG::OnBnClickedButtonCreatetext)
	ON_BN_CLICKED(IDC_BUTTON_DETELTEXT, &CCANCHANGEDLG::OnBnClickedButtonDeteltext)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCANCHANGEDLG 消息处理程序


void CCANCHANGEDLG::OnBnClickedButtonNamechange()
{
	// TODO: 在此添加控件通知处理程序代码
	//具体做事件处理的时候用上了添加的变量，这个button本身的变量在点击的时候调用setwindowstext改名
	//updata更新后台数据，其实有点不太明白
	//调用updata了就把编辑框里的数据传给编辑框值变量吗？
	UpdateData(TRUE);
	m_RelBtn.SetWindowText(m_StrEditValue);
}


void CCANCHANGEDLG::OnBnClickedButtonCreatetext()
{
	// TODO: 在此添加控件通知处理程序代码
	/**
	if (m_Mine.m_hWnd == NULL)
	{
		m_Mine.Create(L"动态创建的按钮", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			CRect(20, 20, 300, 100), this, 2000);
		GetDlgItem(IDOK)->SetWindowText(L"删除动态创建的按钮");
	}
	else
	{
		m_Mine.DestroyWindow();
		GetDlgItem(IDOK)->SetWindowText(L"运行时创建按钮");
	}
	//CDialog::OnOK();
	*/
	///*
	if (m_Mine.m_hWnd == NULL)
	{
		m_Mine.Create(L"动态创建的按钮", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			CRect(430, 150, 670, 200), this, 2000);
		m_Mine.ShowWindow(2000);
		m_StrTipCtr.SetWindowTextW(L"创建成功");
	}
	else
	{
		m_StrTipCtr.SetWindowTextW(L"别点了QAQ，没有按钮能创建");
	}
	//*/
}


void CCANCHANGEDLG::OnBnClickedButtonDeteltext()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Mine.m_hWnd == NULL)
	{
		m_StrTipCtr.SetWindowTextW(L"别点了QAQ，没有按钮可以销毁");
	}
	else
	{
		m_Mine.DestroyWindow();
		m_StrTipCtr.SetWindowTextW(L"销毁成功");
	}
}


BOOL CCANCHANGEDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CStatic* pWnd;
	 pWnd = (CStatic*)GetDlgItem(IDC_STATIC_CREATEBUTTONTEXT);
	pWnd->SetWindowText(_T("点击创建试试吧！"));
	return TRUE;  // return TRUE unless you set the focus to a control
				// 异常: OCX 属性页应返回 FALSE
}


BOOL CCANCHANGEDLG::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	//在这里写动态创建的button的消息映射，就是为啥又冒出个word来用

	WORD  nCode = HIWORD(wParam);   // 控件的通知消息
	WORD  nID = LOWORD(wParam);	  // 控件的ID号
	if ((nID == 2000) && (nCode == BN_CLICKED))
		MessageBox(L"你按下了动态创建的按钮！");

	return CDialogEx::OnCommand(wParam, lParam);
}


HBRUSH CCANCHANGEDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//重载了wmcolor消息。可以在这里修改重画的时候已经定好的颜色。
	//针对统一画的，只能批量化吧好像
	if (nCtlColor == CTLCOLOR_STATIC)//这里是要设置颜色的控件类型

	{
		pDC->SetTextColor(RGB(255, 0, 0)); //字体颜色
		pDC->SetBkColor(RGB(0, 0, 255)); //字体背景色 

	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_CREATEBUTTONTEXT)
	{
		pDC->SetTextColor(RGB(128, 0, 0));   //设置字体颜色
		pDC->SetBkMode(TRANSPARENT); //设置字体背景为透明
		//上面画了下面又画了，好像只会同时存在，而不是一方顶替另一方
		return (HBRUSH)::GetStockObject(BLACK_BRUSH);   // 设置背景色
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
