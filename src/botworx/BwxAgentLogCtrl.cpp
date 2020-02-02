// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxAgentLogCtrl.h>
//
#include <bwmessaging/BwMailSlot.h>
#include <bwmessaging/BwCmd.h>

#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

class BwxAgentLogCtrl ;

#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;

namespace _BwxAgentLogCtrl {
class MyClient : public BwAgentClient {
public:
	MyClient(BwxAgentLogCtrl *pOwner) : p_textCtrl(pOwner) {}
	virtual bwString getClassName() { return "MyClient" ; }
	virtual void onOutput(const BwMessage& msg) ;
	virtual void onLog(const BwMessage& msg) ;
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxAgentLogCtrl *p_textCtrl ;
};
} ; //namespace _BwxAgentLogCtrl
using namespace _BwxAgentLogCtrl ;

BwxAgentLogCtrl::BwxAgentLogCtrl(wxWindow *parent, const BwxContext& context) 
	: wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition,
	//wxDefaultSize, wxTE_MULTILINE|wxTE_RICH2) {
	wxDefaultSize, wxTE_MULTILINE) {
/*BwxAgentLogCtrl::BwxAgentLogCtrl(wxWindow *parent, const BwxContext& context) 
	: wxListBox(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize) {*/
	*m_buffer = 0 ;
	//Bw Stuff
	p_client = new MyClient(this) ;
	p_client->create() ;
	p_client->connect(context.getAgentSession()) ;
	//Wx Stuff
	wxFont font = GetFont();
	font.SetPointSize(10);
	SetFont(font) ;
}
BwxAgentLogCtrl::~BwxAgentLogCtrl() {
}
void BwxAgentLogCtrl::write(bwString& out) {
	AppendText(wxString(out.c_str())) ;
	//f6:newstuff:why does this speed things up?
	//wxCommandEvent event(wxEVT_SCROLLWIN_BOTTOM);
	//wxPostEvent(this, event);
}
/*void BwxAgentLogCtrl::write(bwString& out) {
	//AppendText(wxString(out.c_str())) ;
	char buffer[256] ;
	//restore
	strcpy(buffer, m_buffer) ;
	const char* read = out.c_str() ;
	char* write = buffer + strlen(m_buffer) ;
	//bool saveBuffer = true ;
	while(*read != 0) {
		if(*read == '\n') {
			read++ ;
			//if(*read == 0)
			//	saveBuffer = false ; //got all output
			*write = 0 ;
			Append(wxString(buffer)) ;
			write = buffer ;
			*buffer = 0 ;
			continue ;
		}
		*write++ = *read++ ;
	}
	//if(saveBuffer)
		strcpy(m_buffer, buffer) ;
}*/

/*void BwxAgentLogCtrl::OnChar(wxKeyEvent& event) {
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
}*/
////////////////////////////////////////////////////////////////////
/*BEGIN_EVENT_TABLE(BwxAgentLogCtrl, wxTextCtrl)
	EVT_CHAR(BwxAgentLogCtrl::OnChar)
    //EVT_KEY_DOWN(BwxAgentLogCtrl::OnKey)
    //EVT_KEY_UP(BwxAgentLogCtrl::OnKey)
    //EVT_TEXT(wxID_ANY, BwxAgentLogCtrl::OnText)
END_EVENT_TABLE()*/
////////////////////////////////////////////////////////////////////
void MyClient::onOutput(const BwMessage& msg) {
	/*std::string out ;
	out = msg.str("Output").get() ;
	p_textCtrl->write(out) ;*/
}
void MyClient::onLog(const BwMessage& msg) {
	std::string out ;
	msg()->findString("Output", out) ;
	p_textCtrl->write(out) ;
}
void MyClient::onResponse(const BwMessage& msg) {
}
void MyClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_STEP_ENDED :
			break ;
	}
	BwAgentClient::onEvent(msg) ;
}
///////////////////