#ifndef _BwxDocument_H
#define _BwxDocument_H

//wxWidgets
#include "wx/docview.h"
#include "wx/cmdproc.h"
//Botworx
class BwDocSession ;
class BwDocument ;
#include <bwmessaging/BwMailBox.h>
class BwCmd ;
class BwMailSlot ;

class BwxDocument: public wxDocument {
public:
    BwxDocument(void) ;
    ~BwxDocument(void) ;

	virtual bool OnCreate(const wxString& path, long flags);
	virtual bool OnNewDocument() ;
	virtual bool Save();
    virtual bool OnSaveDocument(const wxString& filename);
    virtual bool OnOpenDocument(const wxString& filename);
	virtual bool OnCloseDocument() ;
    virtual bool IsModified(void) const;
    virtual void Modify(bool mod);
    virtual bool AddView(wxView *view);
    virtual bool RemoveView(wxView *view);
	//
	void setIsRemote(bool val) { m_isRemote = val ; }
	bool isRemote() { return m_isRemote ; }
	/*Messaging*/
	BwDocSession* getDocSession() { return p_docSession ; }
	BwDocSession* p_docSession ;
	BwDocument* p_inner ;
	BwDocument& inner() { return *p_inner ; }
	//Data Members
	bool m_isNew ;
	bool m_isClosed ;
	bool m_isRemote ;
};


#endif
