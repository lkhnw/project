
// ARPView.cpp: CARPView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ARP.h"
#endif

#include "ARPDoc.h"
#include "ARPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CARPView

IMPLEMENT_DYNCREATE(CARPView, CView)

BEGIN_MESSAGE_MAP(CARPView, CView)
END_MESSAGE_MAP()

// CARPView 构造/析构

CARPView::CARPView() noexcept
{
	// TODO: 在此处添加构造代码

}

CARPView::~CARPView()
{
}

BOOL CARPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CARPView 绘图

void CARPView::OnDraw(CDC* /*pDC*/)
{
	CARPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CARPView 诊断

#ifdef _DEBUG
void CARPView::AssertValid() const
{
	CView::AssertValid();
}

void CARPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CARPDoc* CARPView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARPDoc)));
	return (CARPDoc*)m_pDocument;
}
#endif //_DEBUG


// CARPView 消息处理程序
