#ifndef _BwxAgentChildFrame_H
#define _BwxAgentChildFrame_H

class wxSashLayoutWindow ;
class wxSashEvent ;

class BwxAgentView ;
class BwxAgentApplet ;
class BwxAgentAppletSession ;
class BwxAgentDoc ;
class BwDocSession ;
class BwAgentSession ;
class BwxAgentConsole ;
class BwxAgentBook ;
class BwxViewSwitcher ;

class BwxAgentChildFrame: public wxDocMDIChildFrame
{
    DECLARE_CLASS(BwxAgentChildFrame)
public:
    BwxAgentChildFrame(wxDocument *doc, 
				wxView *view, 
				BwxAgentFrame *frame, 
				wxWindowID id = wxID_ANY, 
				const wxString& title = "Agent Doc", 
				const wxPoint& pos = wxDefaultPosition,
				const wxSize& size = wxDefaultSize,
				//long style = wxCAPTION | wxCLIP_CHILDREN | wxRESIZE_BORDER,
				long style = wxCAPTION | wxCLIP_CHILDREN | wxRESIZE_BORDER | wxDEFAULT_FRAME_STYLE | wxMAXIMIZE,
				const wxString& name = "frame"
				);
	~BwxAgentChildFrame() ;
	//Data Members
	BwxAppFrame& appFrame() { return *wxGetApp().GetAppFrame() ; }
	//
	BwxContext m_context ;
	BwAgentSession* getAgentSession() { return p_agentSession ; }
	//
	BwxAgentAppletSession* p_appletSession ;
	BwxAgentApplet* p_applet ;
	BwxAgentApplet& applet() { return *p_applet; }

	BwDocSession *p_docSession ;
	BwAgentSession *p_agentSession ;
	//
    //DECLARE_EVENT_TABLE()
};

#endif //_BwxAgentChildFrame_H
