#pragma once


// CCANCHANGEDLG 对话框

class CCANCHANGEDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CCANCHANGEDLG)

public:
	CCANCHANGEDLG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCANCHANGEDLG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CANCHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 可改名的button
	CButton m_RelBtn;
	// 改下面button名的入口
	CEdit m_StrEdit;
	// 改下面button名的值
	CString m_StrEditValue;
	afx_msg void OnBnClickedButtonNamechange();
	//手动声明一个变量
	CButton m_Mine;
	afx_msg void OnBnClickedButtonCreatetext();
	// 提示动态按钮的信息
	CString m_StrTip;
	// 控件本身
	CStatic m_StrTipCtr;
	afx_msg void OnBnClickedButtonDeteltext();
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
