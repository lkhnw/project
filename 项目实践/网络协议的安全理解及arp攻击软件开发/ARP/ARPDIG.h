#pragma once


// CARPDIG 对话框

class CARPDIG : public CDialogEx
{
	DECLARE_DYNAMIC(CARPDIG)

public:
	CARPDIG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CARPDIG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1_ARP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 源mac地址值
	CString srcmacvalue;
	// 源ip值
	CString srcipvalue;
	// 目的mac地址值
	CString desmacvalue;
	// 目的ip值
	CString desipvalue;
	// 循环次数,0是无线循环
	int num;
	// 发包的时间间隔
	int time;
	CEdit srcmac;
	CEdit srcip;
	CEdit desmac;
	CEdit desip;
	CEdit Num;
	CEdit Time;
	CButton okbutton;
	virtual void OnOK();
	// 展示
	CButton show;
	CStatic sh;
};
