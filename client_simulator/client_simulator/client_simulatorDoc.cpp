// client_simulatorDoc.cpp : implementation of the Cclient_simulatorDoc class
//

#include "stdafx.h"
#include "client_simulator.h"

#include "client_simulatorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cclient_simulatorDoc

IMPLEMENT_DYNCREATE(Cclient_simulatorDoc, CDocument)

BEGIN_MESSAGE_MAP(Cclient_simulatorDoc, CDocument)
END_MESSAGE_MAP()


// Cclient_simulatorDoc construction/destruction

Cclient_simulatorDoc::Cclient_simulatorDoc()
{
	// TODO: add one-time construction code here

}

Cclient_simulatorDoc::~Cclient_simulatorDoc()
{
}

BOOL Cclient_simulatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cclient_simulatorDoc serialization

void Cclient_simulatorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Cclient_simulatorDoc diagnostics

#ifdef _DEBUG
void Cclient_simulatorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cclient_simulatorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cclient_simulatorDoc commands
