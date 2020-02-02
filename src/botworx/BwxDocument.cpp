#include "stdafx.h"

#include <bwmessaging/BwMailSlot.h>

#include <bwbotworx/BwxDocument.h>
#include <bwbotworx/BwxViewSwitcher.h>
#include <bwdocument/BwDocSession.h>

////////////
class BwxDocumentInSlot : public BwMailSlot {
public:
	BwxDocumentInSlot(BwxDocument *pDoc, const bwString& name) : BwMailSlot(NULL, name) {
		p_document = pDoc ;
	}
	virtual void dispatch(const BwMessage& msg) {
		bwWhat what = msg.what() ;
		bwAssert(0) ; //f6:fixme:implement
	}
	//Data Members
	BwxDocument *p_document ;
} ;
////////////////
//EventSlot
class BwxDocumentEventSlot : public BwMailSlot {
public:
	BwxDocumentEventSlot(BwxDocument *pDoc, const bwString& name) : p_document(pDoc), BwMailSlot(NULL, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		bwAssert(0) ; //f6:fixme:implement
	}
	//Data Members
	BwxDocument *p_document ;
} ;

////////////
BwxDocument::BwxDocument(void) {
	m_isNew = true ;
	m_isClosed = false ;
	m_isRemote = false ;
	p_docSession = new BwDocSession() ;
	p_inner = p_docSession->createDocument() ;
}
BwxDocument::~BwxDocument(void) {
}
/*This is very strange wxWidgets calls OnClose for New Docs and
calls it twice when the main frame goes down!!!*/
bool BwxDocument::OnCloseDocument() {
	if(!m_isNew && !m_isClosed) {
		m_isClosed = true ;
	}
	m_isNew = false ;
	return wxDocument::OnCloseDocument() ;
}
//Need to override goofy implementation of wxDocument::Save()
bool BwxDocument::Save()
{
    if (!IsModified() && m_savedYet)
        return true;

    //if ( m_documentFile.empty() || !m_savedYet )
	if ( m_documentFile.empty())
        return SaveAs();

    return OnSaveDocument(m_documentFile);
}
// Since text windows have their own method for saving to/loading from files,
// we override OnSave/OpenDocument instead of Save/LoadObject
bool BwxDocument::OnSaveDocument(const wxString& filename) {
    Modify(false);
#ifdef __WXMAC__
    wxFileName fn(filename) ;
    fn.MacSetDefaultTypeAndCreator() ;
#endif
    return true;
}
bool  BwxDocument::OnCreate(const wxString& path, long flags) {
	return wxDocument::OnCreate(path, flags) ;
}
bool BwxDocument::OnNewDocument() {
	return wxDocument::OnNewDocument() ;
}
bool BwxDocument::OnOpenDocument(const wxString& filename)
{
	inner().onOpen(filename.ToStdString()) ;
	m_isNew = false ;
    SetFilename(filename, true);
    Modify(false);
    UpdateAllViews(); //f6:fixme:is this necessary with new messaging?
    return true;
}

bool BwxDocument::IsModified(void) const {
	return wxDocument::IsModified();
}

void BwxDocument::Modify(bool mod) {
	m_isNew = true ;
    wxDocument::Modify(mod);
}
bool BwxDocument::AddView(wxView *view)
{
	BwxDocManager* pDocMan = static_cast<BwxDocManager*>(GetDocumentManager()) ;
	BwxViewSwitcher* pSwitcher = pDocMan->GetSwitcher() ;
	if(pSwitcher)
		pSwitcher->AddView(view) ;
    return wxDocument::AddView(view) ;
}
bool BwxDocument::RemoveView(wxView *view)
{
	BwxDocManager* pDocMan = static_cast<BwxDocManager*>(GetDocumentManager()) ;
	BwxViewSwitcher* pSwitcher = pDocMan->GetSwitcher() ;
	if(pSwitcher)
		pSwitcher->RemoveView(view) ;
    return wxDocument::RemoveView(view) ;
}
