#ifndef _BwxAppFrame_H
#define _BwxAppFrame_H

#include <bwmessaging/BwPostOffice.h>

class BwxAppFrame ;
class MyPoCall : public BwPoCall {
public:
	MyPoCall(BwxAppFrame *pOwner) : p_frame(pOwner) {}
	virtual bool exec() ;
	//Data Members
	BwxAppFrame *p_frame ;
} ;
class BwxAppFrame: public wxDocMDIParentFrame
{
    DECLARE_CLASS(BwxAppFrame)
public:
    wxMenu *editMenu;
        
    BwxAppFrame(wxDocManager *manager, wxFrame *frame, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size,
        const long type);
	//
	wxFrame *CreateChildFrame(wxDocument *doc, wxView *view, bool isAgent = false);
	BwxAgentDocManager* CreateAgentDocManager() ;
	void OnChildFrameClose(BwxAgentFrame* pFrame) ;
//    
    void OnAbout(wxCommandEvent& event);
	void OnProcessCustom(wxCommandEvent& event) ;
    void OnQuit(wxCommandEvent& event);
    void OnCloseWindow(wxCloseEvent& event) ;
	void OnIdle( wxIdleEvent &event );
	//
	void OnRemoteOpen(wxCommandEvent& event);
	//
    DECLARE_EVENT_TABLE()
private:
	MyPoCall m_poCall ;
	bool m_isClosing ;
	BwxAgentFrameMap m_agentFrameMap ;
};

enum BwxAppMenuId {
	bwxID_CUT = 1,
	bwxID_REMOTE_OPEN
} ;

#endif //_BwxAppFrame_H