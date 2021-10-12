#pragma once


// Cvigenere 对话框

class Cvigenere : public CDialogEx
{
	DECLARE_DYNAMIC(Cvigenere)

public:
	Cvigenere(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cvigenere();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString txt0;
	CString key0;
	CEdit result0;
	CString txt1;
	CString key1;
	CEdit result1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
