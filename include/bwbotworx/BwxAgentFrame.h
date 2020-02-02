#ifndef _BwxAgentFrame_H
#define _BwxAgentFrame_H

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

class BwxAgentFrame: public wxDocMDIParentFrame
{
    DECLARE_CLASS(BwxAgentFrame)
public:
	BwxAgentFrame() ;
	/*bool BwxAgentFrame::Create(BwxAgentDocManager *manager, BwxAgentDoc *doc, BwxAgentView *view, wxWindowID id, const wxString& title,
                 const wxPoint& pos, const wxSize& size, const long type) ;*/
    BwxAgentFrame(BwxAgentDocManager *manager, BwxAgentDoc *doc, BwxAgentView *view, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size,
        const long type);
	~BwxAgentFrame() ;
	//virtual wxMDIClientWindow* OnCreateClient() ;
	wxFrame* CreateChildFrame(wxDocument *doc, wxView *view, bool isAgent = false) ;
    void OnAbout(wxCommandEvent& event);
	void OnProcessCustom(wxCommandEvent& event) ;
    void OnCloseWindow(wxCloseEvent& event) ;
	void OnSashDrag(wxSashEvent& event);
	void OnSize(wxSizeEvent& event);
	//
	enum {
		HORZ_WIN_WIDTH = 256,
		HORZ_WIN_HEIGHT = 1024,
		VERT_WIN_WIDTH = 1024,
		VERT_WIN_HEIGHT = 32
	} ;
	//Data Members
	wxMenu *editMenu;
	wxSashLayoutWindow* m_topWindow ;
	wxSashLayoutWindow* m_leftWindow ;
	wxSashLayoutWindow* m_bottomWindow ;
	wxMDIClientWindow* m_clientWindow ;
	BwxAgentDocManager* m_docManager;
	BwxAppFrame& appFrame() { return *wxGetApp().GetAppFrame() ; }
	wxDocMDIChildFrame* m_agentDocFrame ;
	//
	BwxContext m_context ;
	//BwAgentSession* getAgentSession() { return p_agentSession ; }
	BwSession* getAgentSession() { return p_agentSession ; }
	//
	BwxAgentAppletSession* p_appletSession ;
	BwxAgentApplet* p_applet ;
	BwxAgentApplet& applet() { return *p_applet; }

	BwxAgentConsole *p_console ;
	BwxAgentBook *p_agentBook ;
	BwxViewSwitcher* p_viewSwitcher ;
	BwxAgentView* p_agentView ;
    BwxAgentDoc *p_agentDoc ;
	BwDocSession *p_docSession ;
	//BwAgentSession *p_agentSession ;
	BwSession *p_agentSession ;
	//
    DECLARE_EVENT_TABLE()
};

#endif //_BwxAgentFrame_H
