#pragma once


// Cdh 对话框

class Cdh : public CDialogEx
{
	DECLARE_DYNAMIC(Cdh)

public:
	Cdh(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cdh();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
