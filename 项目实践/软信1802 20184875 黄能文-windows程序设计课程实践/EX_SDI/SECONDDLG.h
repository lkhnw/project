#pragma once


// CSECONDDLG 对话框

class CSECONDDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CSECONDDLG)

public:
	CSECONDDLG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSECONDDLG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_second };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
};
