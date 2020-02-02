// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxAgentTtyCtrl.h>
//
#include <bwmessaging/BwMailSlot.h>
#include <bwmessaging/BwCmd.h>

#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

#include <bwapplet/BwAppletClient.h>
#include <bwbotworx/_BwxAgentApplet.h>
using namespace _BwxAgentApplet ;

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

namespace _BwxAgentTtyCtrl {
class MyAppletClient : public BwAppletClient {
public:
	MyAppletClient(BwxAgentTtyCtrl *pOwner) : p_ctrl(pOwner) {}
	virtual void onEvent(const BwMessage& msg) {
		switch(msg.what()) {
			case EVENT_QUERY : {
				bwString query ;
				msg()->findString("QUERY", query) ;
				p_ctrl->sendCommand(BwCmd("query") << quote << query << endq) ;
			}
			break ;
		}
		BwAppletClient::onEvent(msg) ;
	}
	//
	BwxAgentTtyCtrl *p_ctrl ;
};
class MyAgentClient : public BwAgentClient {
public:
	MyAgentClient(BwxAgentTtyCtrl *pOwner) : p_textCtrl(pOwner) {}
	virtual bwString getClassName() { return "MyAgentClient" ; }
	virtual void onOutput(const BwMessage& msg) ;
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxAgentTtyCtrl *p_textCtrl ;
};
} ; //namespace _BwxAgentTtyCtrl
using namespace _BwxAgentTtyCtrl ;

BwxAgentTtyCtrl::BwxAgentTtyCtrl(wxWindow *parent, const BwxContext& context) 
	: wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition,
	//wxDefaultSize, wxTE_MULTILINE|wxTE_RICH2) {
	wxDefaultSize, wxTE_MULTILINE) {
	//Applet Stuff
	p_appletClient = new MyAppletClient(this) ;
	p_appletClient->create() ;
	p_appletClient->connect(context.getAppletSession()) ;
	//Agent Stuff
	p_agentClient = new MyAgentClient(this) ;
	p_agentClient->create() ;
	p_agentClient->connect(context.getAgentSession()) ;
	BwCmd newsCmd("news") ;
	p_agentClient->doCommand(newsCmd << end) ; //this is the way to handle no params?
	//Wx Stuff
	SetBackgroundColour(*wxBLACK) ;
	SetForegroundColour(*wxGREEN) ;
	wxFont font = GetFont();
	font.SetPointSize(10);
	SetFont(font) ;
}
BwxAgentTtyCtrl::~BwxAgentTtyCtrl() {
}
void BwxAgentTtyCtrl::write(bwString& out) {
	//we want to process ascii codes here ...
	const char* pChar = out.c_str() ;
	bwString final ;
	char c ;
	while( (c = *pChar++) ) {
		if(c == '\b') {
			/*wxKeyEvent event ;
			event.m_keyCode = WXK_BACK ;
			OnChar(event) ;*/
			//SetInsertionPoint(GetInsertionPoint() - 1) ;
			Remove(GetLastPosition() - 1, GetLastPosition()) ;
		}
		else
			final += c ;
	}
	//
	AppendText(wxString(final.c_str())) ;
	//WriteText(wxString(final.c_str())) ;
}
void BwxAgentTtyCtrl::sendCommand(BwCmd& cmd) {
	write(cmd.m_cmd) ;
	AppendText(_T("\n")) ;
	p_agentClient->doCommand(cmd) ;
}

void BwxAgentTtyCtrl::OnChar(wxKeyEvent& event) {
	wxChar ch = (wxChar)event.GetKeyCode() ;
	switch ( ch  )
	{
		case WXK_BACK :
			if(!m_buffer.empty())
				m_buffer.erase(--m_buffer.end()) ;
			break ;
		case WXK_RETURN: {
			AppendText(_T("\n")) ;
			//p_agentClient->doCommand(m_buffer.c_str()) ;
			BwCmd cmd ; cmd.set(m_buffer.c_str()) ;
			p_agentClient->doCommand(cmd) ;
			m_buffer = "" ;
						 }
			break ;
		default :
			m_buffer += ch ;
	}

	event.Skip();
}
////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(BwxAgentTtyCtrl, wxTextCtrl)
	EVT_CHAR(BwxAgentTtyCtrl::OnChar)
    //EVT_KEY_DOWN(BwxAgentTtyCtrl::OnKey)
    //EVT_KEY_UP(BwxAgentTtyCtrl::OnKey)
    //EVT_TEXT(wxID_ANY, BwxAgentTtyCtrl::OnText)
END_EVENT_TABLE()
////////////////////////////////////////////////////////////////////
void MyAgentClient::onOutput(const BwMessage& msg) {
	std::string out ;
	msg()->findString("Output", out) ;
	p_textCtrl->write(out) ;
}
void MyAgentClient::onResponse(const BwMessage& msg) {
	/*std::string out ;
	out = "\n" + msg.str("Response").get() + "\n" ;
	p_textCtrl->write(out) ;*/
}
void MyAgentClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			//wxPostEvent(p_textCtrl, wxCommandEvent(wxEVT_CLOSE_WINDOW)) ;
			//wxPostEvent(p_textCtrl, wxCommandEvent(wxEVT_MENU_CLOSE)) ;
			break ;
	}
	BwAgentClient::onEvent(msg) ;
}
///////////////////