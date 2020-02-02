#include "stdafx.h"
#include <bwwx/resource/icon/xpm/agent.xpm>
//
#include <bwbotworx/BwxAppFrame.h>

#include <bwbotworx/BwxAgentFrame.h>
#include <bwbotworx/BwxAgentChildFrame.h>
//
#include <bwbotworx/BwxAgentApplet.h>
#include <bwbotworx/BwxAgentDoc.h>
#include <bwbotworx/BwxAgentView.h>
#include <bwbotworx/BwxAgentBook.h>
#include <bwbotworx/BwxViewSwitcher.h>
//
#include <bwbotworx/BwxScintillaDoc.h>
#include <bwbotworx/BwxScintillaView.h>
#include <wx/ogl/ogl.h> // base header of OGL, includes and adjusts wx/deprecated/setup.h
//
#include <wx/splitter.h>
#include <wx/laywin.h>
//
#include <bwmessaging/BwMailSlot.h>

#include <bwagency/BwAgency.h>
#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

//#include <bwagency/BwMiaAgentSystem.h>

//////////
#define ID_WINDOW_TOP       100
#define ID_WINDOW_LEFT     101
#define ID_WINDOW_BOTTOM    102

//////////
IMPLEMENT_CLASS(BwxAgentFrame, wxDocMDIParentFrame)
BEGIN_EVENT_TABLE(BwxAgentFrame, wxDocMDIParentFrame)
	EVT_CLOSE(BwxAgentFrame::OnCloseWindow)
    EVT_MENU(wxID_ABOUT, BwxAgentFrame::OnAbout)
	EVT_SIZE(BwxAgentFrame::OnSize)
    EVT_SASH_DRAGGED_RANGE(ID_WINDOW_TOP, ID_WINDOW_BOTTOM, BwxAgentFrame::OnSashDrag)
END_EVENT_TABLE()

BwxAgentFrame::BwxAgentFrame() {
}
BwxAgentFrame::BwxAgentFrame(BwxAgentDocManager *manager, BwxAgentDoc *doc, BwxAgentView *view, wxWindowID id, const wxString& title,
                 const wxPoint& pos, const wxSize& size, const long type):
wxDocMDIParentFrame(manager, NULL, id, title, pos, size, type)
{
	m_docManager = manager ;
	m_docManager->SetFrame(this) ;
	p_agentDoc = doc ;
	p_agentView = view ;
	m_context = p_agentView->m_context ;
	SetIcon(wxICON(agent));
    //
    wxMenuBar *menu_bar = new wxMenuBar;
    //// Associate the menu bar with the frame
    SetMenuBar(menu_bar);
    
//
	p_appletSession = p_agentView->p_appletSession ;
	p_applet = p_agentView->p_applet ;
	m_context.setAppletSession(p_appletSession) ;
	p_docSession = p_agentDoc->getDocSession() ;
	m_context.setDocSession(p_docSession) ;
	p_agentSession = p_agentDoc->getAgentSession() ;
	m_context.setAgentSession(p_agentSession) ;
//
	wxSashLayoutWindow* win = NULL ;
	win = new wxSashLayoutWindow(this, ID_WINDOW_BOTTOM,
								wxDefaultPosition, wxSize(VERT_WIN_WIDTH, VERT_WIN_HEIGHT),
								wxNO_BORDER | wxSW_3D | wxCLIP_CHILDREN);
	win->SetDefaultSize(wxSize(VERT_WIN_WIDTH, VERT_WIN_HEIGHT));
	win->SetOrientation(wxLAYOUT_HORIZONTAL);
	win->SetAlignment(wxLAYOUT_BOTTOM);
	win->SetSashVisible(wxSASH_TOP, true);
	m_bottomWindow = win;

	// A window to the left of the client window
	win = new wxSashLayoutWindow(this, ID_WINDOW_LEFT,
								wxDefaultPosition, wxSize(HORZ_WIN_WIDTH, HORZ_WIN_HEIGHT),
								wxNO_BORDER | wxSW_3D | wxCLIP_CHILDREN);
	win->SetDefaultSize(wxSize(HORZ_WIN_WIDTH, HORZ_WIN_HEIGHT));
	win->SetOrientation(wxLAYOUT_VERTICAL);
	win->SetAlignment(wxLAYOUT_LEFT);
	win->SetSashVisible(wxSASH_RIGHT, true);
	m_leftWindow = win;

	p_viewSwitcher = new BwxViewSwitcher(manager, m_bottomWindow, m_context) ;
	p_agentBook = new BwxAgentBook(m_leftWindow, m_context) ;
}
BwxAgentFrame::~BwxAgentFrame() {
	p_agentView->SetDeleteFrame(false) ;
	//p_agentDoc->DeleteAllViews() ;
	wxGetApp().GetAppFrame()->OnChildFrameClose(this) ;
}
wxFrame *BwxAgentFrame::CreateChildFrame(wxDocument *doc, wxView *view, bool isAgent) {

	BwxAgentChildFrame *subframe = new BwxAgentChildFrame(doc, view, this) ;

	if(isAgent) {
		p_agentView = dynamic_cast<BwxAgentView*>(view) ;
		p_viewSwitcher->AddView(p_agentView, "Agent Console") ;
		m_docManager->CreateDocument(p_agentDoc->GetFilename(), wxDOC_SILENT) ;
	}
    
    return subframe;
}
void BwxAgentFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
    (void)wxMessageBox(_T("Botworx Agent Tester - wxWidgets "), _T("About BwxApp"));
}
void BwxAgentFrame::OnCloseWindow(wxCloseEvent& event) {
	//wxDocMDIParentFrame::OnCloseWindow(event) ;
    Destroy();
}
void BwxAgentFrame::OnSashDrag(wxSashEvent& event)
{
    if (event.GetDragStatus() == wxSASH_STATUS_OUT_OF_RANGE)
        return;

    switch (event.GetId())
    {
        case ID_WINDOW_LEFT:
        {
            m_leftWindow->SetDefaultSize(wxSize(event.GetDragRect().width, 1000));
            break;
        }
        case ID_WINDOW_BOTTOM:
        {
            m_bottomWindow->SetDefaultSize(wxSize(1000, event.GetDragRect().height));
            break;
        }
    }

//#if wxUSE_MDI_ARCHITECTURE
    wxLayoutAlgorithm layout;
    layout.LayoutMDIFrame(this);
//#endif // wxUSE_MDI_ARCHITECTURE

    // Leaves bits of itself behind sometimes
    GetClientWindow()->Refresh();
}

void BwxAgentFrame::OnSize(wxSizeEvent& 
                                  #ifdef __WXUNIVERSAL__
                                  event
                                  #else
                                  WXUNUSED(event)
                                  #endif
                                  )
{
//#if wxUSE_MDI_ARCHITECTURE
    wxLayoutAlgorithm layout;
    layout.LayoutMDIFrame(this);
//#endif // wxUSE_MDI_ARCHITECTURE

    // FIXME: On wxX11, we need the MDI frame to process this
    // event, but on other platforms this should not
    // be done.
#ifdef __WXUNIVERSAL__   
    event.Skip();
#endif
}

