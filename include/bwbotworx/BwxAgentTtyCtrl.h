#ifndef _BwxAgentTtyCtrl_H
#define _BwxAgentTtyCtrl_H

#include "wx/textctrl.h"

class BwxContext ;
class BwAgentClient ;
class BwAgentSession ;
class BwAppletClient ;

class BwxAgentTtyCtrl : public wxTextCtrl {
public:
	BwxAgentTtyCtrl(wxWindow *parent, const BwxContext& context) ;
	virtual ~BwxAgentTtyCtrl() ;
	void sendCommand(BwCmd& cmd) ;
	void write(bwString& out) ;
	void OnChar(wxKeyEvent& event) ;
	//
	void setAgentSession(BwAgentSession *pSession) { p_agentSession = pSession ; }
	//Data Members
	BwAppletClient* p_appletClient ;
	//
	std::string m_buffer ;
	BwAgentSession *p_agentSession ;
	BwAgentClient *p_agentClient ;
	//
	DECLARE_EVENT_TABLE()
} ;


#endif// _BwxAgentTtyCtrl_H
