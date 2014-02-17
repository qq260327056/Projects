// client_simulatorDoc.h : interface of the Cclient_simulatorDoc class
//


#pragma once


class Cclient_simulatorDoc : public CDocument
{
protected: // create from serialization only
	Cclient_simulatorDoc();
	DECLARE_DYNCREATE(Cclient_simulatorDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Cclient_simulatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


