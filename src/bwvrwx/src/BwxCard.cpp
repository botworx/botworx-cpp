// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "BwxCard.h"
#include "BwxDeckFrame.h"
#include "BwxUserMode.h"

#include <wx/button.h>

namespace _BwxCard {
} ; //namespace _BwxCard
using namespace _BwxCard ;

BwxCard::BwxCard(BwxDeckFrame *pFrame)
	: wxPanel(pFrame->getDrawer(), wxID_ANY, wxDefaultPosition, wxDefaultSize) {
	p_sizer = new wxBoxSizer(wxVERTICAL) ;
	SetAutoLayout( true );
	SetSizer( p_sizer );
}
BwxCard::~BwxCard() {
}
void BwxCard::createButton(BwxUserMode *pMode) {
	//wxButton *pButton = new wxButton(p_client, wxID_ANY, wxString(pMode->getShortName().c_str())) ;
	wxButton *pButton = new wxButton(this, wxID_ANY, wxString(pMode->getShortName().c_str())) ;
	m_buttonMap[pButton] = pMode ;
	pButton->Show(true) ;
	p_sizer->Add(pButton,0, wxEXPAND) ;
	p_sizer->Fit(this) ;
}
void BwxCard::OnButton(wxCommandEvent& event)
{
	BwxUserMode *pMode = m_buttonMap[event.GetEventObject()] ;
	pMode->activate() ;
}
////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(BwxCard, wxPanel)
    EVT_BUTTON(wxID_ANY, BwxCard::OnButton)
END_EVENT_TABLE()
////////////////////////////////////////////////////////////////////