#include "stdafx.h"

#include <bwwx/resource/icon/xpm/agent.xpm>

#include <bwbotworx/BwxAppFrame.h>
#include <bwbotworx/BwxAgentFrame.h>
#include <bwbotworx/BwxAgentDoc.h>
#include <bwbotworx/BwxAgentView.h>
//
#include <bwbotworx/BwxScintillaDoc.h>
#include <bwbotworx/BwxScintillaView.h>
#include <wx/ogl/ogl.h> // base header of OGL, includes and adjusts wx/deprecated/setup.h
//
#include "wx/splitter.h"
//
#include <bwmessaging/BwMailSlot.h>

#include <bwagency/BwAgency.h>
#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

////////////////////////////////////////////////////////////////////

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_MY_CUSTOM_COMMAND, 7777)
END_DECLARE_EVENT_TYPES()

DEFINE_EVENT_TYPE(wxEVT_MY_CUSTOM_COMMAND)

// it may also be convenient to define an event table macro for this event type
#define EVT_MY_CUSTOM_COMMAND(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
        wxEVT_MY_CUSTOM_COMMAND, id, wxID_ANY, \
        (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
        (wxObject *) NULL \
    ),

bool MyPoCall::exec() {
	wxCommandEvent eventCustom(wxEVT_MY_CUSTOM_COMMAND);
	wxPostEvent(p_frame, eventCustom);
	return true ;
}
wxFrame *BwxAppFrame::CreateChildFrame(wxDocument *doc, wxView *view, bool isAgent)
{
	BwxAgentFrame* agentFrame = NULL ;
	BwxAgentDocManager* agentDocManager = NULL ;
	if(isAgent) {
		agentDocManager = CreateAgentDocManager() ;
		agentFrame = new BwxAgentFrame(agentDocManager, dynamic_cast<BwxAgentDoc*>(doc), dynamic_cast<BwxAgentView*>(view), wxID_ANY, _T("Agent"),
			wxPoint(10, 10), wxSize(300, 300), wxDEFAULT_FRAME_STYLE | wxMAXIMIZE);
		agentFrame->Show(true) ;
		m_agentFrameMap[agentDocManager] = agentFrame ;
	}
	else {
		agentFrame = m_agentFrameMap[static_cast<BwxAgentDocManager*>(doc->GetDocumentManager())]  ;
	}
	return agentFrame->CreateChildFrame(doc, view, isAgent) ;
}
void BwxAppFrame::OnChildFrameClose(BwxAgentFrame* pFrame) {
	BwxAgentDocManager* agentDocManager = static_cast<BwxAgentDocManager*>(pFrame->GetDocumentManager()) ;
	m_agentFrameMap.erase(agentDocManager) ;
	m_docManager->RemoveDocument(pFrame->p_agentDoc) ;
}
BwxAgentDocManager* BwxAppFrame::CreateAgentDocManager() {
	BwxAgentDocManager* agentDocManager = new BwxAgentDocManager ;
	(void) new wxDocTemplate(agentDocManager, _T("Mia"), _T("*.mia"), _T(""), _T("mia"), _T("Mia Source"), _T("Mia View"),
		CLASSINFO(bwxscintilla::BwxScintillaDoc), CLASSINFO(bwxscintilla::BwxScintillaView));

	(void) new wxDocTemplate(agentDocManager, _T("Soar"), _T("*.soar"), _T(""), _T("soar"), _T("Soar Source"), _T("Soar View"),
		CLASSINFO(bwxscintilla::BwxScintillaDoc), CLASSINFO(bwxscintilla::BwxScintillaView));

	(void) new wxDocTemplate(agentDocManager, _T("XML"), _T("*.xml"), _T(""), _T("xml"), _T("XML"), _T("Xml View"),
		CLASSINFO(bwxscintilla::BwxScintillaDoc), CLASSINFO(bwxscintilla::BwxScintillaView));

	(void) new wxDocTemplate(agentDocManager, _T("C++"), _T("*.cpp;*.h"), _T(""), _T("cpp"), _T("C++ Source"), _T("C++ View"),
		CLASSINFO(bwxscintilla::BwxScintillaDoc), CLASSINFO(bwxscintilla::BwxScintillaView));

	return agentDocManager ;
}
////////////
IMPLEMENT_CLASS(BwxAppFrame, wxDocMDIParentFrame)
BEGIN_EVENT_TABLE(BwxAppFrame, wxDocMDIParentFrame)
	EVT_MY_CUSTOM_COMMAND(wxID_ANY, BwxAppFrame::OnProcessCustom)
	EVT_CLOSE(BwxAppFrame::OnCloseWindow)
    EVT_MENU(wxID_ABOUT, BwxAppFrame::OnAbout)
    EVT_MENU(wxID_EXIT,  BwxAppFrame::OnQuit)
	//
	EVT_MENU(bwxID_REMOTE_OPEN,  BwxAppFrame::OnRemoteOpen)
END_EVENT_TABLE()

BwxAppFrame::BwxAppFrame(wxDocManager *manager, wxFrame *frame, wxWindowID id, const wxString& title,
                 const wxPoint& pos, const wxSize& size, const long type):
wxDocMDIParentFrame(manager, frame, id, title, pos, size, type), m_poCall(this)
{
	m_isClosing = false ;
	BwPostOffice::singleton::get().setCall(&m_poCall) ;
    // This pointer only needed if in single window mode
    //canvas = (MyCanvas *) NULL;
    editMenu = (wxMenu *) NULL;
	SetIcon(wxICON(agent));
}
void BwxAppFrame::OnProcessCustom(wxCommandEvent& WXUNUSED(event))
{
	if(!m_isClosing)
		BwPostOffice::singleton::get().deliver() ;
}
void BwxAppFrame::OnIdle( wxIdleEvent &event ) {
	if(!m_isClosing)
		BwPostOffice::singleton::get().deliver() ;
}
void BwxAppFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
    (void)wxMessageBox(_T("Botworx Agent Tester - wxWidgets "), _T("About BwxApp"));
}
void BwxAppFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{    // true is to force the frame to close
    Close(true);
}
void BwxAppFrame::OnCloseWindow(wxCloseEvent& event) {
	if(!m_agentFrameMap.empty()) {
		for(BwxAgentFrameIter iter = m_agentFrameMap.begin() ; iter != m_agentFrameMap.end() ; ++iter) {
			BwxAgentFrame* pFrame = (*iter).second ;
			pFrame->Close() ;
		}
	}

	m_isClosing = true ;
	BwPostOffice::singleton::get().setCall(NULL) ; //might as well ...
	//wxDocMDIParentFrame::OnCloseWindow(event) ;
    Destroy();
}
//(void)wxMessageBox(_T("OnRemoteOpen"), _T("OnRemoteOpen"));
void BwxAppFrame::OnRemoteOpen(wxCommandEvent& WXUNUSED(event) ) {
	wxString path("Blox.mia");
	BwxAgentDoc* pDoc = new BwxAgentDoc() ;
	pDoc->setIsRemote(true) ;
    pDoc->SetFilename(path);
    pDoc->SetDocumentTemplate(wxGetApp().GetAgentDocTemplate());
    wxGetApp().GetDocumentManager()->AddDocument(pDoc);
    pDoc->SetCommandProcessor(pDoc->OnCreateCommandProcessor());

	pDoc->OnCreate(path, wxDOC_MDI) ;

    if (!pDoc->OnOpenDocument(path))
    {
        pDoc->DeleteAllViews();
        // delete newDoc; // Implicitly deleted by DeleteAllViews
        //return (wxDocument *) NULL;
    }
}