#ifndef _BwxAgentView_H
#define _BwxAgentView_H

#include "wx/docview.h"

class BwxAgentApplet ;
class BwxAgentAppletSession ;
class BwxAgentDoc ;
class BwDocSession ;
class BwAgentSession ;
class BwxAgentConsole ;
class BwxAgentBook ;

class BwxAgentView: public wxView {
    DECLARE_DYNAMIC_CLASS(BwxAgentView)
public:
    BwxAgentView() ;
    ~BwxAgentView(void) {}
	//
	enum {
		MY_SASH_SIZE = 5,
		MY_SASH_X = 200,
		MY_SASH_GRAVITY = 1
	} ;
	//Events
    bool OnCreate(wxDocument *doc, long flags);
    void OnDraw(wxDC *dc);
    void OnUpdate(wxView *sender, wxObject *hint = (wxObject *) NULL);
    bool OnClose(bool deleteWindow = true);
	//
	void SetDeleteFrame(bool val) { m_deleteFrame = val ; }
	//Data Members
	BwxContext m_context ;
	//BwAgentSession* getAgentSession() { return p_agentSession ; }
	BwSession* getAgentSession() { return p_agentSession ; }
	//
	BwxAgentAppletSession* p_appletSession ;
	BwxAgentApplet* p_applet ;
	BwxAgentApplet& applet() { return *p_applet; }

    wxFrame *m_frame;
	BwxAgentConsole *m_console ;
	BwxAgentBook *m_agentBook ;
    BwxAgentDoc *p_doc ;
	BwDocSession *p_docSession ;
	//BwAgentSession *p_agentSession ;
	BwSession *p_agentSession ;
	bool m_deleteFrame ;
};

#endif
