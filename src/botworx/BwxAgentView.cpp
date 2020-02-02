#include "stdafx.h"

#include <bwbotworx/BwxAgentApplet.h>
#include <bwbotworx/BwxAgentDoc.h>
#include <bwbotworx/BwxAgentView.h>
#include <bwbotworx/BwxAgentConsole.h>
#include <bwbotworx/BwxAgentBook.h>
//
#include <bwbotworx/BwxAppFrame.h>
//
#include <wx/splitter.h>

IMPLEMENT_DYNAMIC_CLASS(BwxAgentView, wxView)

BwxAgentView::BwxAgentView() 
	: wxView() { 
	m_frame = NULL; 
	m_console = NULL ;
	m_agentBook = NULL ;
	m_deleteFrame = true ;
}
bool BwxAgentView::OnCreate(wxDocument *doc, long WXUNUSED(flags) )
{
	p_appletSession = new BwxAgentAppletSession() ;
	p_applet = dynamic_cast<BwxAgentApplet*>(p_appletSession->create_applet()) ;
	m_context.setAppletSession(p_appletSession) ;
	p_doc = dynamic_cast<BwxAgentDoc*>(doc) ;
	p_docSession = p_doc->getDocSession() ;
	m_context.setDocSession(p_docSession) ;
	p_agentSession = p_doc->getAgentSession() ;
	m_context.setAgentSession(p_agentSession) ;

    m_frame = wxGetApp().GetAppFrame()->CreateChildFrame(doc, this, true) ;
	//m_frame->CreateStatusBar(2);
    int width, height;
    m_frame->GetClientSize(&width, &height);
	m_frame->SetTitle(_T("BwxAgentView"));

	/*wxSplitterWindow *splitter = new wxSplitterWindow(m_frame, wxID_ANY,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxSP_3D | wxSP_LIVE_UPDATE |
                                   wxCLIP_CHILDREN ) ; // | wxSP_NO_XP_THEME*/
	//splitter->SetSashSize(MY_SASH_SIZE) ;
	//m_console = new BwxAgentConsole(splitter, m_context) ;
	m_console = new BwxAgentConsole(m_frame, m_context) ;

	//splitter->SplitVertically(m_agentBook, m_console, MY_SASH_X);

	//m_frame->SetStatusText(_T("Min pane size = 0"), 1);

	m_console->Show(true) ;

    m_frame->Show(true);
    Activate(true);
    
    return true;
}
void BwxAgentView::OnDraw(wxDC *WXUNUSED(dc) ) {
}

void BwxAgentView::OnUpdate(wxView *WXUNUSED(sender), wxObject *WXUNUSED(hint) ) {
}

bool BwxAgentView::OnClose(bool deleteWindow) {
    if (!GetDocument()->Close())
        return false;
    
    Activate(false);
    
    if (deleteWindow) {
		if(m_deleteFrame)
			delete m_frame;
    }
    return true;
}