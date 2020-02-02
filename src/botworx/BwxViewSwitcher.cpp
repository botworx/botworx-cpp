// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <bwbotworx/BwxViewSwitcher.h>
#include <bwbotworx/BwxDocument.h>
#include <bwbotworx/BwxAgentScriptEdit.h>
#include <bwbotworx/BwxAgentInputCtrl.h>
#include <bwbotworx/BwxAgentTtyCtrl.h>
#include <bwbotworx/BwxAgentLogCtrl.h>
#include <bwbotworx/BwxStateGraphCtrl.h>
//
#include <wx/splitter.h>
#include <wx/button.h>
//
#include <bwmessaging/BwMailSlot.h>
//
#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

namespace _BwxViewSwitcher {
class MyClient : public BwAgentClient {
public:
	MyClient(BwxViewSwitcher *pOwner) : p_console(pOwner) {}
	virtual bwString getClassName() { return "MyClient" ; }
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxViewSwitcher *p_console ;
};
} ; //namespace _BwxViewSwitcher
using namespace _BwxViewSwitcher ;

BwxViewSwitcher::BwxViewSwitcher(BwxDocManager* pDocMan, wxWindow *parent, const BwxContext& context) 
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize) {
	//Bw Stuff
	p_client = new MyClient(this) ;
	p_client->create() ;
	p_client->connect(context.getAgentSession()) ;
	//Wx Stuff
	p_docMan = pDocMan ;
	pDocMan->SetSwitcher(this) ;
	//
	p_sizer = new wxBoxSizer(wxHORIZONTAL) ;
	SetAutoLayout( true );
	SetSizer( p_sizer );
}
BwxViewSwitcher::~BwxViewSwitcher() {
}
bool BwxViewSwitcher::AddView(wxView *view, const wxString& title)
{
	CreateButton(view, title) ;
	return true ;
}
bool BwxViewSwitcher::RemoveView(wxView *view)
{
	RemoveButton(view) ;
	return true ;
}
void BwxViewSwitcher::CreateButton(wxView *pView, const wxString& title) {
	//wxButton *pButton = new wxButton(p_client, wxID_ANY, wxString(pMode->getShortName().c_str())) ;
	BwxDocument* pDoc = dynamic_cast<BwxDocument*>(pView->GetDocument()) ;
	wxButton *pButton = 
		new wxButton(this, wxID_ANY, title != "" ? title : wxFileNameFromPath(pDoc->GetFilename())) ;
	m_viewMap[pButton] = pView ;
	m_buttonMap[pView] = pButton ;
	pButton->Show(true) ;
	p_sizer->Add(pButton,0, wxEXPAND) ;
	p_sizer->Fit(this) ;
}
void BwxViewSwitcher::RemoveButton(wxView *pView) {
	wxButton *pButton = m_buttonMap[pView] ;
	pButton->Show(false) ;
	//p_sizer->Remove(pButton) ; //deprecated
	p_sizer->Detach(pButton) ;
	p_sizer->Fit(this) ;
	m_buttonMap.erase(pView) ;
	m_viewMap.erase(pButton) ;
	delete pButton ;
}
void BwxViewSwitcher::OnButton(wxCommandEvent& event)
{
	wxView *pView = m_viewMap[event.GetEventObject()] ;
	//pView->Activate(true) ;
	pView->GetFrame()->SetFocus() ;
}
////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(BwxViewSwitcher, wxPanel)
    EVT_BUTTON(wxID_ANY, BwxViewSwitcher::OnButton)
END_EVENT_TABLE()
////////////////////////////////////////////////////////////////////
void MyClient::onResponse(const BwMessage& msg) {
	/*std::string out ;
	out = "\n" + msg.str("Response").get() + "\n" ;
	p_console->write(out) ;*/
}
void MyClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			//wxPostEvent(p_console, wxCommandEvent(wxEVT_CLOSE_WINDOW)) ;
			//wxPostEvent(p_console, wxCommandEvent(wxEVT_MENU_CLOSE)) ;
			break ;
	}
	BwAgentClient::onEvent(msg) ;
}
///////////////////