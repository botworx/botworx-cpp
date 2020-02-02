#include "stdafx.h"

#include <bwcore/BwKernel.h>

#include <bwbotworx/BwxAppFrame.h>
#include <bwbotworx/BwxAgentFrame.h>
#include <bwbotworx/BwxAgentDoc.h>
#include <bwbotworx/BwxAgentView.h>
//
#include <wx/splitter.h>
#include <wx/ogl/ogl.h>
//
#include <bwmessaging/BwMailSlot.h>

#include <bwagency/BwAgency.h>
#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

#include <bwagency/BwMiaAgentSystem.h>

wxPrintData *g_printData = (wxPrintData*) NULL;
wxPageSetupData *g_pageSetupData = (wxPageSetupData*) NULL;

////////////////////////////////////////////////////////////////////
/*
    wxDocTemplate(wxDocManager *manager,
                  const wxString& descr,
                  const wxString& filter,
                  const wxString& dir,
                  const wxString& ext,
                  const wxString& docTypeName,
                  const wxString& viewTypeName,
                  wxClassInfo *docClassInfo = (wxClassInfo *) NULL,
                  wxClassInfo *viewClassInfo = (wxClassInfo *)NULL,
                  long flags = wxDEFAULT_TEMPLATE_FLAGS);
*/
IMPLEMENT_APP(BwxApp)

bool BwxApp::OnInit()
{
	wxOGLInitialize(); //hmmm...
    //
    BwKernel::startup() ;
	//hmmm ... maybe kernel creates this .. BwAgencyKernel???
	BwLocalAgency::singleton::get().addAgentSystem(new BwMiaAgentSystem(BwLocalAgency::singleton::getPtr())) ;

    //// Create a document manager
    m_docManager = new BwxAgencyDocManager;

	p_agentDocTemplate = new wxDocTemplate(m_docManager, _T("Mia"), _T("*.mia"), _T(""), _T("mia"), _T("Mia Source"), _T("Mia View"),
		CLASSINFO(BwxAgentDoc), CLASSINFO(BwxAgentView));

	/*(void) new wxDocTemplate(m_docManager, _T("Agent"), _T("*.bwa"), _T(""), _T("agent"), _T("Agent Doc"), _T("Agent View"),
		CLASSINFO(BwxAgentDoc), CLASSINFO(BwxAgentView));*/

    //// Create the main frame window
    p_frame = new BwxAppFrame(m_docManager, (wxFrame *) NULL, wxID_ANY, _T("BwxApp"), wxPoint(0, 0), wxSize(500, 400), wxDEFAULT_FRAME_STYLE);
	//frame = p_frame ;
    
	//
	#if wxUSE_PRINTING_ARCHITECTURE
		// initialize print data and setup
		g_printData = new wxPrintData;
		g_pageSetupData = new wxPageSetupDialogData;
	#endif // wxUSE_PRINTING_ARCHITECTURE

    //// Give it an icon (this is ignored in MDI mode: uses resources)
/*#ifdef __WXMSW__
    frame->SetIcon(wxIcon(_T("doc_icn")));
#endif*/
	//frame->SetIcon(wxIcon(_T("doc_icn")));
	//frame->SetIcon(wxICON(icon_agent));
    
    //// Make a menubar
	//The Menus
    wxMenu *file_menu = new wxMenu;
    file_menu->Append(wxID_NEW, _T("&New..."));
    file_menu->Append(wxID_OPEN, _T("&Open..."));    
    file_menu->Append(wxID_CLOSE, _T("&Close"));
    file_menu->Append(wxID_SAVE, _T("&Save"));
    file_menu->Append(wxID_SAVEAS, _T("Save &As..."));
    file_menu->AppendSeparator();
    file_menu->Append(wxID_PRINT, _T("&Print..."));
    file_menu->Append(wxID_PRINT_SETUP, _T("Print &Setup..."));
    file_menu->Append(wxID_PREVIEW, _T("Print Pre&view"));
    file_menu->AppendSeparator();
    file_menu->Append(wxID_EXIT, _T("E&xit"));

    wxMenu *remote_menu = new wxMenu;
    remote_menu->Append(bwxID_REMOTE_OPEN, _T("&Open..."));    

    wxMenu *edit_menu = new wxMenu;
    edit_menu->Append(wxID_UNDO, _T("&Undo"));
    edit_menu->Append(wxID_REDO, _T("&Redo"));
    edit_menu->AppendSeparator();
    edit_menu->Append(bwxID_CUT, _T("&Cut last segment"));
        
	p_frame->editMenu = edit_menu; //Need this to disable items on the menu
       
    // A nice touch: a history of files visited. Use this menu.
    m_docManager->FileHistoryUseMenu(file_menu);
    
    wxMenu *help_menu = new wxMenu;
    help_menu->Append(wxID_ABOUT, _T("&About"));
    
	//The Menu Bar Itself
    wxMenuBar *menu_bar = new wxMenuBar;
    
    menu_bar->Append(file_menu, _T("&File"));
	menu_bar->Append(remote_menu, _T("&Remote"));
    if (edit_menu)
        menu_bar->Append(edit_menu, _T("&Edit"));
    menu_bar->Append(help_menu, _T("&Help"));
    
    //// Associate the menu bar with the frame
    p_frame->SetMenuBar(menu_bar);
    
    p_frame->Centre(wxBOTH);
    p_frame->Show(true);
    
    SetTopWindow(p_frame);
    return true;
}
int BwxApp::OnExit() {
    BwKernel::shutdown();
	//destroyPart(BwLocalAgency::singleton::getPtr()) ;
	return wxApp::OnExit() ;
}