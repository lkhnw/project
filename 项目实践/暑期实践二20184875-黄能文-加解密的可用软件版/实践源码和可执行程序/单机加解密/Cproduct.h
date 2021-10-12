#pragma once


// Cproduct 对话框

class Cproduct : public CDialogEx
{
	DECLARE_DYNAMIC(Cproduct)

public:
	Cproduct(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cproduct();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
