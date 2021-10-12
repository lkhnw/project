
// MainFrm.h: CMainFrame 类的接口
//

#pragma once


class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileOpen2();
	afx_msg void OnFileOpen3();
	afx_msg void Ondialogfirst();
	afx_msg void OnDialogSecond();
//	afx_msg void OnBnClickedButtonNamechange();
	afx_msg void OnCanchangedlg();
	afx_msg void OnCtlNet();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCtlColor();
	afx_msg void OnCtlStudentList();
	afx_msg void OnCommandTest();
private:
	bool m_bTag;
public:
	afx_msg void OnMenuCheck();
	afx_msg void OnUpdateMenuCheck(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuDefault(CCmdUI* pCmdUI);
	afx_msg void OnMenuDefault();
private:
	CBitmap m_bitmap;
public:
	afx_msg void OnUpdateMenuPic(CCmdUI* pCmdUI);
private:
	CMenu m_menuMine;
public:
	afx_msg void OnMenuUpdate();
	afx_msg void OnMenuReturn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
protected:
	CToolBar m_wndToolBarMine;
private:
	bool m_bTagNewBar;
public:
	afx_msg void OnUpdateMenuUpdate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuReturn(CCmdUI* pCmdUI);
	afx_msg void On32788();
};




