#ifndef _BwxAgentBook_H
#define _BwxAgentBook_H

#include "wx/panel.h"
#include "wx/notebook.h"

class BwxContext ;
class BwxMindTv ;
class BwxAgentQueryCtrl ;

class BwAgentClient ;
class BwAgentSession ;

class BwxAgentBook : public wxPanel {
public:
	BwxAgentBook(wxWindow *parent, const BwxContext& context) ;
	virtual ~BwxAgentBook() ;
	//
	void setAgentSession(BwSession *pSession) { p_agentSession = pSession ; }
	//Data Members
	wxImageList *m_imageList;
	wxNotebook *m_notebook ;
	BwxMindTv* m_mindTv ;
	BwxAgentQueryCtrl* m_queryCtrl ;
	//
	BwSession *p_agentSession ;
	//
	DECLARE_EVENT_TABLE()
} ;


#endif// _BwxAgentBook_H
