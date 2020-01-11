
// MFCDoc.h : interface of the CMFCDoc class
//


#pragma once

#include "Line.h"


class CMFCDoc : public CDocument
{
protected: // create from serialization only
	CMFCDoc() noexcept;
	DECLARE_DYNCREATE(CMFCDoc)

// Attributes
public:
	CPoint begin;
	BOOL isDraw;
	Points points;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
