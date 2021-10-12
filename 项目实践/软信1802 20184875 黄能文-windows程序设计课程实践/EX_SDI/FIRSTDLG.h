#pragma once


// CFIRSTDLG 对话框

class CFIRSTDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CFIRSTDLG)

public:
	CFIRSTDLG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFIRSTDLG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIRST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
