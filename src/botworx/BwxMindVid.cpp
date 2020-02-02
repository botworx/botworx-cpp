// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxMindVid.h>

#include <bwagency/BwAgentClient.h>
#include <bwagency/BwStateClient.h>

#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;
#include <bwagency/_BwState.h>
using namespace _BwState ;

namespace _BwxMindVid {
/////////////
class MyClient : public BwStateClient {
public:
	MyClient(BwxMindVid *pOwner, bwHandle handle) : BwStateClient(handle), p_owner(pOwner) {}
	virtual bwString getClassName() { return "MyClient" ; }
	virtual void onEvent(const BwMessage& msg) ;
	virtual void onOutput(const BwMessage& msg) ;
	//
	BwxMindVid *p_owner ;
};
void MyClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_FACT_ADDED : {
			bwString fact ;
			msg()->findString("FACT", fact) ;
			p_owner->AddFact(fact) ;
								}
			break ;
		case EVENT_FACT_REMOVED : {
			bwString fact ;
			msg()->findString("FACT", fact) ;
			p_owner->RemoveFact(fact) ;
								  }
			break ;			
	}
	BwStateClient::onEvent(msg) ;
}
void MyClient::onOutput(const BwMessage& msg) {
	switch(msg.what()) {
		case OUTPUT_FACTS : {
			bwString facts ;
			msg()->findString("FACTS", facts) ;
			p_owner->RefreshFacts(facts) ;
								  }
			break ;
		case OUTPUT_LOG : {
			bwString log ;
			msg()->findString("LOG", log) ;
			p_owner->RefreshLog(log) ;
								  }
			break ;
	}
	//BwStateClient::onOutput(msg) ;
}
} //end namespace _BwxMindVid
///////////////
using namespace _BwxMindVid ;

BwxMindVid::BwxMindVid(wxWindow *parent, const BwxContext& context, bwHandle handle) : BwxVid(parent, context, handle) {
	p_client = new MyClient(this, handle) ;
	p_client->create() ;
	p_client->connect(context.getAgentClient()) ;

	const wxSize imageSize(32, 32);
	m_imageList = new wxImageList(imageSize.GetWidth(), imageSize.GetHeight());
	m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM | wxNB_NOPAGETHEME) ;
	m_notebook->SetImageList(m_imageList);

  p_factsListBox = new wxListBox(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	p_logListBox = new wxListBox(m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	wxBoxSizer *pMainSizer = new wxBoxSizer(wxVERTICAL) ;
	SetAutoLayout( true );
	SetSizer( pMainSizer );
	p_factsListBox->Show(true) ;
	pMainSizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);	
	m_notebook->AddPage(p_factsListBox, wxT("Facts"), true) ;
	m_notebook->AddPage(p_logListBox, wxT("Log"), false) ;
	////////
	pMainSizer->Fit(this) ;

}
void BwxMindVid::AddFact(const bwString& fact) {
	p_factsListBox->Append(fact.c_str()) ;
}
void BwxMindVid::RemoveFact(const bwString& fact) {
	int n = p_factsListBox->FindString(fact.c_str()) ;
	//f6:fixme:we have a major problem.
	//events are being sent before we hook up to the eventslot!!!
	if(n != -1)
		p_factsListBox->Delete(n) ;
}
void BwxMindVid::RefreshFacts(const bwString& facts) {
	FillListBox(p_factsListBox, facts) ;
}
void BwxMindVid::RefreshLog(const bwString& log) {
	FillListBox(p_logListBox, log) ;
}
void BwxMindVid::FillListBox(wxListBox* pListBox, const bwString& text) {
	pListBox->Clear() ;
	//f6:fixme:fixed buffer size IS a problem.
	char buffer[1024] ;
	const char* read = text.c_str() ;
	char* write = buffer ;
	while(*read != 0) {
		if(*read == '\t') {
			++read ; //skip char
			for(int i = 0 ; i < 4 ; i++) {
				*write++ = ' ' ;
			}
		}
		else
		if(*read == '\n') {
			++read ; //skip char
			*write = 0 ;
			pListBox->Append(wxString(buffer)) ;
			write = buffer ;
			*buffer = 0 ;
			continue ;
		}
		else
			*write++ = *read++ ;
	}
}
