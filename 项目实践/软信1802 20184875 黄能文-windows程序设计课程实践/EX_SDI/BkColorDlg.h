#pragma once


// CBkColorDlg 对话框

class CBkColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBkColorDlg)

public:
	CBkColorDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBkColorDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CScrollBar m_scrollRed;
	CSliderCtrl m_sliderGreen;
	int m_nGreen;
	CSliderCtrl m_sliderBlue;
	int m_nBlue;
private:
	int m_nRedValue;
	CBrush m_Brush;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
