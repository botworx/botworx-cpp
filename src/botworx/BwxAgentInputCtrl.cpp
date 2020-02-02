// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxAgentInputCtrl.h>
//
#include <bwmessaging/BwMailSlot.h>
#include <bwmessaging/BwCmd.h>

#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

namespace _BwxAgentInputCtrl {
class MyClient : public BwAgentClient {
public:
	MyClient(BwxAgentInputCtrl *pOwner) : p_textCtrl(pOwner) {}
	virtual bwString getClassName() { return "MyClient" ; }
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxAgentInputCtrl *p_textCtrl ;
};
} ; //namespace BwxAgentInputCtrl
using namespace _BwxAgentInputCtrl ;

BwxAgentInputCtrl::BwxAgentInputCtrl(wxWindow *parent, const BwxContext& context) 
	: wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition,
	wxDefaultSize, wxTE_MULTILINE) {
	//wxDefaultSize, wxTE_MULTILINE|wxTE_RICH2) {
	//Bw Stuff
	p_client = new MyClient(this) ;
	p_client->create() ;
	p_client->connect(context.getAgentSession()) ;
	//Wx Stuff
	wxFont font = GetFont();
	font.SetPointSize(10);
	SetFont(font) ;
}
BwxAgentInputCtrl::~BwxAgentInputCtrl() {
}
void BwxAgentInputCtrl::OnChar(wxKeyEvent& event) {
	wxChar ch = (wxChar)event.GetKeyCode() ;
	switch ( ch  )
	{
		case WXK_BACK :
			if(!m_buffer.empty())
				m_buffer.erase(--m_buffer.end()) ;
			break ;
		case WXK_RETURN: {
			AppendText(_T("\n")) ;
			BwCmd cmd ; cmd.set(m_buffer.c_str()) ;
			//p_client->doCommand(m_buffer.c_str()) ;
			p_client->doCommand(cmd) ;
			m_buffer = "" ;
						 }
			break ;
		default :
			m_buffer += ch ;
	}

	event.Skip();
}
////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(BwxAgentInputCtrl, wxTextCtrl)
	EVT_CHAR(BwxAgentInputCtrl::OnChar)
    //EVT_KEY_DOWN(BwxAgentInputCtrl::OnKey)
    //EVT_KEY_UP(BwxAgentInputCtrl::OnKey)
    //EVT_TEXT(wxID_ANY, BwxAgentInputCtrl::OnText)
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