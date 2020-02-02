#ifndef _BwxAgentInputCtrl_H
#define _BwxAgentInputCtrl_H

#include "wx/textctrl.h"

class BwxContext ;
class BwAgentClient ;
class BwAgentSession ;

class BwxAgentInputCtrl : public wxTextCtrl {
public:
	BwxAgentInputCtrl(wxWindow *parent, const BwxContext& context) ;
	virtual ~BwxAgentInputCtrl() ;
	void write(bwString& out) {
		AppendText(wxString(out.c_str())) ;
	}
	void OnChar(wxKeyEvent& event) ;
	//
	void setAgentSession(BwAgentSession *pSession) { p_agentSession = pSession ; }
	//Data Members
	std::string m_buffer ;
	BwAgentSession *p_agentSession ;
	BwAgentClient *p_client ;
	//
	DECLARE_EVENT_TABLE()
} ;


#endif// _BwxAgentInputCtrl_H
