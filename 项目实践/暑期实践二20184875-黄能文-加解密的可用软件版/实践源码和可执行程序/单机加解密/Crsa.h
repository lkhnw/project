﻿#pragma once


// Crsa 对话框

class Crsa : public CDialogEx
{
	DECLARE_DYNAMIC(Crsa)

public:
	Crsa(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Crsa();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
