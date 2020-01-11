
// MFCView.cpp : implementation of the CMFCView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC.h"
#endif

#include "MFCDoc.h"
#include "MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCView

IMPLEMENT_DYNCREATE(CMFCView, CView)

BEGIN_MESSAGE_MAP(CMFCView, CView)
	ON_COMMAND(ID_FILE_WRITEFILE, &CMFCView::OnFileWritefile)
	ON_COMMAND(ID_FILE_READFILE, &CMFCView::OnFileReadfile)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMFCView construction/destruction

CMFCView::CMFCView() noexcept
{
	// TODO: add construction code here
	
}

CMFCView::~CMFCView()
{
}

BOOL CMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCView drawing

void CMFCView::OnDraw(CDC* pDC)
{
	CMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	const CArray<CPoint>& points = pDoc->points.getPoints();
	int len = points.GetSize();
	for (int i = 0; i < len; i++) {
		CPoint point1 = points.GetAt(i);
		pDC->MoveTo(point1);
		if (i + 1 < len) {
			CPoint point2 = points.GetAt(i + 1);
			if (point1 == point2) {
				i++;
				continue;
			}
			pDC->LineTo(point2);
		}
	}
}


// CMFCView diagnostics

#ifdef _DEBUG
void CMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDoc* CMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDoc)));
	return (CMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCView message handlers


void CMFCView::OnFileWritefile()
{
	// TODO: Add your command handler code here
	CString str = CString("Hello World!");
	CFileDialog dialog(FALSE);
	if (IDOK == dialog.DoModal()) {
		CString path = dialog.GetPathName();
		CFile file(path, CFile::modeWrite | CFile::modeCreate);
		int len = str.GetLength() * sizeof(TCHAR);
		file.Write(str, len);
		file.Close();
	}
}


void CMFCView::OnFileReadfile()
{
	// TODO: Add your command handler code here
	CFileDialog dialog(TRUE);
	if (IDOK == dialog.DoModal()) {
		TCHAR* buf = NULL;
		CString path = dialog.GetPathName();
		CFile file(path, CFile::modeRead);
		ULONGLONG len = file.GetLength() / sizeof(TCHAR);
		buf = new TCHAR[len + 1];
		buf[len] = 0;
		file.Read(buf, file.GetLength());
		MessageBox(buf);
		delete[] buf;
		file.Close();
	}
}


void CMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMFCDoc* pDoc = GetDocument();
	pDoc->isDraw = TRUE;
	pDoc->begin = point;
	pDoc->points.addPoint(point);

	CView::OnLButtonDown(nFlags, point);
}


void CMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMFCDoc* pDoc = GetDocument();
	if (pDoc->isDraw) {
		CClientDC cdc(this);
		cdc.MoveTo(pDoc->begin);
		cdc.LineTo(point);
		pDoc->begin = point;
		pDoc->points.addPoint(point);
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CMFCDoc* pDoc = GetDocument();
	pDoc->isDraw = FALSE;
	pDoc->points.addPoint(point);

	CView::OnLButtonUp(nFlags, point);
}
