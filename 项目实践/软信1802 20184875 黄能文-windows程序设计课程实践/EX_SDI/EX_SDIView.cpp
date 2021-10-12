
// EX_SDIView.cpp: CEXSDIView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "EX_SDI.h"
#endif

#include "EX_SDIDoc.h"
#include "EX_SDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEXSDIView

IMPLEMENT_DYNCREATE(CEXSDIView, CView)

BEGIN_MESSAGE_MAP(CEXSDIView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEXSDIView 构造/析构

CEXSDIView::CEXSDIView() noexcept
{
	// TODO: 在此处添加构造代码

}

CEXSDIView::~CEXSDIView()
{
}

BOOL CEXSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CEXSDIView 绘图

void CEXSDIView::OnDraw(CDC* /*pDC*/)
{
	CEXSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CEXSDIView 打印

BOOL CEXSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEXSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CEXSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CEXSDIView 诊断

#ifdef _DEBUG
void CEXSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CEXSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEXSDIDoc* CEXSDIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEXSDIDoc)));
	return (CEXSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CEXSDIView 消息处理程序
