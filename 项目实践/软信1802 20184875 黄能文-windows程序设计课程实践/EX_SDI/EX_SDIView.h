
// EX_SDIView.h: CEXSDIView 类的接口
//

#pragma once


class CEXSDIView : public CView
{
protected: // 仅从序列化创建
	CEXSDIView() noexcept;
	DECLARE_DYNCREATE(CEXSDIView)

// 特性
public:
	CEXSDIDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CEXSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // EX_SDIView.cpp 中的调试版本
inline CEXSDIDoc* CEXSDIView::GetDocument() const
   { return reinterpret_cast<CEXSDIDoc*>(m_pDocument); }
#endif

