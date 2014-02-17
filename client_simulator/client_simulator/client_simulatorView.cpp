// client_simulatorView.cpp : implementation of the Cclient_simulatorView class
//

#include "stdafx.h"
#include "client_simulator.h"

#include "client_simulatorDoc.h"
#include "client_simulatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cclient_simulatorView

IMPLEMENT_DYNCREATE(Cclient_simulatorView, CView)

BEGIN_MESSAGE_MAP(Cclient_simulatorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Cclient_simulatorView construction/destruction

Cclient_simulatorView::Cclient_simulatorView()
{
	// TODO: add construction code here

}

Cclient_simulatorView::~Cclient_simulatorView()
{
}

BOOL Cclient_simulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cclient_simulatorView drawing

void Cclient_simulatorView::OnDraw(CDC* /*pDC*/)
{
	Cclient_simulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Cclient_simulatorView printing

BOOL Cclient_simulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cclient_simulatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cclient_simulatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Cclient_simulatorView diagnostics

#ifdef _DEBUG
void Cclient_simulatorView::AssertValid() const
{
	CView::AssertValid();
}

void Cclient_simulatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cclient_simulatorDoc* Cclient_simulatorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cclient_simulatorDoc)));
	return (Cclient_simulatorDoc*)m_pDocument;
}
#endif //_DEBUG


// Cclient_simulatorView message handlers
