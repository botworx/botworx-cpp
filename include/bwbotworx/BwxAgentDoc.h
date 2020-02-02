#ifndef _BwxAgentDoc_H
#define _BwxAgentDoc_H

#include "BwxDocument.h"

class BwAgentClient ;
class BwAgentSession ;

class BwxAgentDoc: public BwxDocument
{
    DECLARE_DYNAMIC_CLASS(BwxAgentDoc)
private:
public:
	//BwAgentSession* getAgentSession() ;
	BwSession* getAgentSession() ;
	void createSession() ;
	virtual bool OnCreate(const wxString& path, long flags);
	virtual bool OnNewDocument() ;
    virtual bool OnOpenDocument(const wxString& filename);
	virtual bool OnCloseDocument() ;

    BwxAgentDoc(void) ;
    ~BwxAgentDoc(void) ;
	//
	BwAgentClient *p_client ;
};


#endif
