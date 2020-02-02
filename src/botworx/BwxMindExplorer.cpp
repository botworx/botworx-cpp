// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <bwbotworx/BwxMindExplorer.h>
#include <bwbotworx/BwxMindTreeCtrl.h>
//
#include <wx/splitter.h>
//
#include <bwmessaging/BwMailSlot.h>
//
#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

BwxMindExplorer::BwxMindExplorer(wxWindow *parent, const BwxContext& context) 
	 : BwxVid(parent, context) {
	//Wx Stuff
	m_treeCtrl = new BwxMindTreeCtrl(this, context) ;

	wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
	//sizerTop->Add(m_notebook, 1, wxEXPAND | wxALL, 5);
	sizerTop->Add(m_treeCtrl, 1, wxEXPAND | wxALL, 5);

	/*wxStaticBox *staticBox = new wxStaticBox(this, wxID_ANY, wxT("Input")) ;
	wxStaticBoxSizer* staticSizer = new wxStaticBoxSizer(staticBox, wxVERTICAL) ;
	sizerTop->Add(staticSizer, 0, wxEXPAND | wxALL, 5) ;
	staticSizer->Add(m_inputCtrl, 0, wxEXPAND | wxALL, 5) ;*/

	//m_notebook->AddPage(m_treeCtrl, wxT("IO"), true, 0) ;

	SetSizer(sizerTop);
    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this);

}
BwxMindExplorer::~BwxMindExplorer() {
}
////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(BwxMindExplorer, wxPanel)
END_EVENT_TABLE()
////////////////////////////////////////////////////////////////////
