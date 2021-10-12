
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "EX_SDI.h"
#include "FIRSTDLG.h"
#include"SECONDDLG.h"
#include "MainFrm.h"
#include "DlgNetQuestionary.h"
#include"CANCHANGEDLG.h"
#include "BkColorDlg.h"
#include "StuInfoDlg.h"
#include "ListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN_2, &CMainFrame::OnFileOpen2)
	ON_COMMAND(ID_FILE_OPEN_3, &CMainFrame::OnFileOpen3)
	ON_COMMAND(ID_dialog_first, &CMainFrame::Ondialogfirst)
	ON_COMMAND(ID_DIALOG_SECOND, &CMainFrame::OnDialogSecond)
	//ON_BN_CLICKED(IDC_BUTTON_NAMECHANGE, &CMainFrame::OnBnClickedButtonNamechange)
	ON_COMMAND(ID_CANCHANGEDLG, &CMainFrame::OnCanchangedlg)
	ON_COMMAND(IDM_CTL_NET, &CMainFrame::OnCtlNet)
	ON_COMMAND(IDM_CTL_COLOR, &CMainFrame::OnCtlColor)
	ON_COMMAND(IDM_CTL_STUDENT_LIST, &CMainFrame::OnCtlStudentList)
	//ON_COMMAND(IDM_CTL_PROP_SHEET, &CMainFrame::OnCtlPropSheet)
	ON_COMMAND(IDM_COMMAND_TEST, &CMainFrame::OnCommandTest)
	ON_COMMAND(IDM_MENU_CHECK, &CMainFrame::OnMenuCheck)
	ON_UPDATE_COMMAND_UI(IDM_MENU_CHECK, &CMainFrame::OnUpdateMenuCheck)
	ON_UPDATE_COMMAND_UI(IDM_MENU_DEFAULT, &CMainFrame::OnUpdateMenuDefault)
	ON_COMMAND(IDM_MENU_DEFAULT, &CMainFrame::OnMenuDefault)
	ON_UPDATE_COMMAND_UI(IDM_MENU_PIC, &CMainFrame::OnUpdateMenuPic)
	ON_COMMAND(IDM_MENU_UPDATE, &CMainFrame::OnMenuUpdate)
	ON_COMMAND(IDM_MENU_RETURN, &CMainFrame::OnMenuReturn)
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(IDM_MENU_UPDATE, &CMainFrame::OnUpdateMenuUpdate)
	ON_UPDATE_COMMAND_UI(IDM_MENU_RETURN, &CMainFrame::OnUpdateMenuReturn)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
	m_bTag = 1;
	m_bTagNewBar = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CMenu* pSysMenu = GetMenu(); // 获得程序菜单指针
	CMenu* pSubMenu = pSysMenu->GetSubMenu(1);
	// 获得第二个子菜单的指针
	CString StrMenuItem(L"新的菜单项");
	// 增加一水平分隔线
	pSubMenu->AppendMenu(MF_SEPARATOR);
	pSubMenu->AppendMenu
	(MF_STRING, ID_NEW_MENUITEM, StrMenuItem);
	// 在子菜单中增加一菜单项
	// 允许使用ON_UPDATE_COMMAND_UI或ON_COMMAND的菜单项
	m_bAutoMenuEnable = FALSE;     // 关闭系统自动更新菜单状态  
	pSysMenu->EnableMenuItem
	(ID_NEW_MENUITEM, MF_BYCOMMAND | MF_ENABLED);
	// 激活菜单项  
	DrawMenuBar();		     // 更新菜单


	GetMenu()->GetSubMenu(5)->SetDefaultItem(IDM_MENU_DEFAULT);

	m_bitmap.LoadBitmap(IDB_BITMAP1);
	GetMenu()->GetSubMenu(5)->SetMenuItemBitmaps(4, MF_BYPOSITION, &m_bitmap, &m_bitmap);


	if (!m_wndToolBarMine.CreateEx(this, TBSTYLE_FLAT, WS_CHILD
		| WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS
		| CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarMine.LoadToolBar(IDR_TOOLBAR_NEW))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBarMine.EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBarMine);
	ShowControlBar(&m_wndToolBarMine, FALSE, FALSE);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnFileOpen2()
{
	// TODO: 在此添加命令处理程序代码
	//这部分是文件对话框的一个标准格式提示形式：给用户看的提示，系统内部使用的字符等
	CString filter;
	filter = "文本文件(*.txt)|*.txt|C++文件(*.h,*.cpp)|*.h;*.cpp||";

	//这里就是创建了文件对话框了，填了个性质
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
	//如果点了ok
	if (dlg.DoModal() == IDOK) {
		//获取路径
		CString str;
		str = dlg.GetPathName();
		//窗口输出路径
		MessageBox(str);
	}

}


void CMainFrame::OnFileOpen3()
{
	// TODO: 在此添加命令处理程序代码
	CString filter;
	filter = "文本文件(*.txt)|*.txt|C++文件(*.h,*.cpp)|*.h;*.cpp||";

	//这里就是创建了文件对话框了，填了个性质
	//那么多性质里，AlloMultiselect是多选
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY| OFN_ALLOWMULTISELECT, filter);
	//如果点了ok
	if (dlg.DoModal() == IDOK) {
		//获取路径
		CString str;
		str = dlg.GetPathName();
		//多选的只能这么配合
		//这个是位置数据结构
		POSITION pos;
		//**只能用getstart函数，又**返回position
		pos = dlg.GetStartPosition();
		MessageBox(str);
		//好像pos会变一样，next后pos就往后移了，
		//是因为动态位置确定只能用pos吗，只有pos可以移。
		while (pos!=NULL) {
			//pos下移，返回路径名
			str = dlg.GetNextPathName(pos);
			MessageBox(str);
		}
	}
}


void CMainFrame::Ondialogfirst()
{
	// TODO: 在此添加命令处理程序代码
	CFIRSTDLG  dlg;
	dlg.DoModal();

}


void CMainFrame::OnDialogSecond()
{
	// TODO: 在此添加命令处理程序代码
	//If you wish to create a modeless dialog, call Create in the constructor of your dialog class.
	//本来模态就是特殊简化出来的，DOMODEL函数
	//用普通流程来的话构造实例，正常显示窗口，就是非模态的。不过设置属性应也能做到模态
	CSECONDDLG* pdlg = new CSECONDDLG;
	pdlg->Create(IDD_DIALOG_second);
	pdlg->ShowWindow(SW_SHOWNORMAL);
}

void CMainFrame::OnCanchangedlg()
{
	// TODO: 在此添加命令处理程序代码
	CCANCHANGEDLG dlg;
	dlg.DoModal();
}


void CMainFrame::OnCtlNet()
{
	// TODO: 在此添加命令处理程序代码
	CDlgNetQuestionary dlg;
	dlg.DoModal();
}


BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (LOWORD(wParam) == ID_NEW_MENUITEM)
		MessageBox(L"你选中了新的菜单项");
	return CFrameWnd::OnCommand(wParam, lParam);
}


void CMainFrame::OnCtlColor()
{
	// TODO: 在此添加命令处理程序代码
	CBkColorDlg dlg;
	dlg.DoModal();
}


void CMainFrame::OnCtlStudentList()
{
	// TODO: 在此添加命令处理程序代码
	CListDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnCommandTest()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(L"按下了命令响应菜单！");

}


void CMainFrame::OnMenuCheck()
{
	// TODO: 在此添加命令处理程序代码
	m_bTag = !m_bTag;

}


void CMainFrame::OnUpdateMenuCheck(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable();
	if (m_bTag)
		pCmdUI->SetCheck();
	else
		pCmdUI->SetCheck(0);

}


void CMainFrame::OnUpdateMenuDefault(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable();

}


void CMainFrame::OnMenuDefault()
{
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateMenuPic(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable();

}


void CMainFrame::OnMenuUpdate()
{
	// TODO: 在此添加命令处理程序代码
	if (m_menuMine.m_hMenu)
		m_menuMine.DestroyMenu();
	m_menuMine.LoadMenu(IDR_MENU_NEW);
	SetMenu(&m_menuMine);

	ShowControlBar(&m_wndToolBar, FALSE, FALSE);
	ShowControlBar(&m_wndToolBarMine, TRUE, FALSE);

	m_bTagNewBar = 1;


}


void CMainFrame::OnMenuReturn()
{
	// TODO: 在此添加命令处理程序代码
	if (m_menuMine.m_hMenu)
		m_menuMine.DestroyMenu();
	m_menuMine.LoadMenu(IDR_MAINFRAME);

	SetMenu(&m_menuMine);
	GetMenu()->GetSubMenu(4)->SetDefaultItem(IDM_MENU_DEFAULT);
	GetMenu()->GetSubMenu(4)->SetMenuItemBitmaps
	(3, MF_BYPOSITION, &m_bitmap, &m_bitmap);

	ShowControlBar(&m_wndToolBar, TRUE, FALSE);
	ShowControlBar(&m_wndToolBarMine, FALSE, FALSE);
	m_bTagNewBar = 0;

}


void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	CMenu* pSysMenu = GetMenu();
	int nCount = pSysMenu->GetMenuItemCount();
	if (nCount > 1)
	{
		pSysMenu->GetSubMenu(nCount - 1)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x, point.y, this);
	}
}


void CMainFrame::OnUpdateMenuUpdate(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_bTagNewBar) {
		pCmdUI->Enable(0);
	}
	else {
	pCmdUI->Enable(1);
	}
}


void CMainFrame::OnUpdateMenuReturn(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (m_bTagNewBar)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}
