#include "stdafx.h"

#include <bwwx/resource/icon/xpm/agent.xpm>

#include <bwbotworx/BwxAgentChildFrame.h>
#include <bwbotworx/BwxAgentFrame.h>
//
IMPLEMENT_CLASS(BwxAgentChildFrame, wxDocMDIChildFrame)
//
BwxAgentChildFrame::BwxAgentChildFrame(wxDocument *doc, wxView *view, BwxAgentFrame *frame, wxWindowID id, const wxString& title,
                 const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxDocMDIChildFrame(doc, view, frame, id, title, pos, size, style, name)
{
	m_context = frame->m_context ;
	p_appletSession = frame->p_appletSession ;
	p_applet = frame->p_applet ;
	///////////
	SetIcon(wxICON(agent));
    
    //// Make a menubar
    wxMenu *file_menu = new wxMenu;
    
    file_menu->Append(wxID_NEW, _T("&New..."));
    file_menu->Append(wxID_OPEN, _T("&Open..."));
    //file_menu->Append(wxID_CLOSE, _T("&Close"));
    //file_menu->Append(wxID_SAVE, _T("&Save"));
    //file_menu->Append(wxID_SAVEAS, _T("Save &As..."));
        
    wxMenu *edit_menu = (wxMenu *) NULL;
        
    wxMenu *help_menu = new wxMenu;
    help_menu->Append(wxID_ABOUT, _T("&About"));
    
    wxMenuBar *menu_bar = new wxMenuBar;
    
    menu_bar->Append(file_menu, _T("&File"));
    menu_bar->Append(help_menu, _T("&Help"));
    
    //// Associate the menu bar with the frame
    SetMenuBar(menu_bar);

}
BwxAgentChildFrame::~BwxAgentChildFrame() {
}

