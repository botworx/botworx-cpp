#ifndef _BwxAgentLogCtrl_H
#define _BwxAgentLogCtrl_H

#include "wx/textctrl.h"

class BwxContext ;
class BwAgentClient ;
class BwAgentSession ;

class BwxAgentLogCtrl : public wxTextCtrl {
//class BwxAgentLogCtrl : public wxListBox {
public:
	BwxAgentLogCtrl(wxWindow *parent, const BwxContext& context) ;
	virtual ~BwxAgentLogCtrl() ;
	void write(bwString& out) ;
	//void OnChar(wxKeyEvent& event) ;
	//
	void setAgentSession(BwAgentSession *pSession) { p_agentSession = pSession ; }
	//Data Members
	char m_buffer[256] ;
	BwAgentSession *p_agentSession ;
	BwAgentClient *p_client ;
	//
	//DECLARE_EVENT_TABLE()
} ;


#endif// _BwxAgentLogCtrl_H
