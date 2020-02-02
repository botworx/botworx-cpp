#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxAgentBook.h>
#include <bwbotworx/BwxMindTv.h>
//
//
#include <bwbotworx/BwxAgentQueryCtrl.h>
//
#include <wx/splitter.h>

//
#include <bwmessaging/BwMailSlot.h>
//
#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

class BwxAgentBook ;

namespace _BwxAgentBook {
class MyClient : public BwAgentClient {
public:
	MyClient(BwxAgentBook *pOwner) : p_textCtrl(pOwner) {}
	virtual bwString getClassName() { return "MyClient" ; }
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxAgentBook *p_textCtrl ;
};
} ; //namespace _BwxAgentBook
using namespace _BwxAgentBook ;

BwxAgentBook::BwxAgentBook(wxWindow *parent, const BwxContext& context) 
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize) {
	//Bw Stuff
	p_agentSession = context.getAgentSession() ;
	//Wx Stuff
	// m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM | wxNB_NOPAGETHEME) ;
	const wxSize imageSize(32, 32);
	m_imageList = new wxImageList(imageSize.GetWidth(), imageSize.GetHeight());
	m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM) ;
	m_notebook->SetImageList(m_imageList);

	m_mindTv = new BwxMindTv(m_notebook, context) ;
	m_queryCtrl = new BwxAgentQueryCtrl(m_notebook, context) ;

	wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
	sizerTop->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

	m_notebook->AddPage(m_mindTv, wxT("Mind"), true) ;
	m_notebook->AddPage(m_queryCtrl, wxT("Query"), false) ;

	SetSizer(sizerTop);
    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this);

}
BwxAgentBook::~BwxAgentBook() {
}
////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(BwxAgentBook, wxPanel)
END_EVENT_TABLE()
////////////////////////////////////////////////////////////////////
void MyClient::onResponse(const BwMessage& msg) {
	/*std::string out ;
	out = "\n" + msg.str("Response").get() + "\n" ;
	p_textCtrl->write(out) ;*/
}
void MyClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			//wxPostEvent(p_textCtrl, wxCommandEvent(wxEVT_CLOSE_WINDOW)) ;
			//wxPostEvent(p_textCtrl, wxCommandEvent(wxEVT_MENU_CLOSE)) ;
			break ;
	}
	BwAgentClient::onEvent(msg) ;
}
///////////////////