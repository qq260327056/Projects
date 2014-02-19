// client_simulatorView.h : interface of the Cclient_simulatorView class
//


#pragma once


class Cclient_simulatorView : public CView
{
protected: // create from serialization only
	Cclient_simulatorView();
	DECLARE_DYNCREATE(Cclient_simulatorView)

// Attributes
public:
	Cclient_simulatorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cclient_simulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in client_simulatorView.cpp
inline Cclient_simulatorDoc* Cclient_simulatorView::GetDocument() const
   { return reinterpret_cast<Cclient_simulatorDoc*>(m_pDocument); }
#endif

