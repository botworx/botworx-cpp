#ifndef _BwxViewSwitcher_H
#define _BwxViewSwitcher_H

#include "wx/panel.h"
#include "wx/notebook.h"

class BwxContext ;

class BwxAgentScriptEdit ;
class BwxAgentInputCtrl ;
class BwxAgentTtyCtrl ;
class BwxAgentLogCtrl ;
class BwxStateGraphCtrl ;
class BwDocSession ;

class BwAgentClient ;
class BwAgentSession ;

class BwxViewSwitcher : public wxPanel {
public:
	BwxViewSwitcher(BwxDocManager* pDocMan, wxWindow *parent, const BwxContext& context) ;
	virtual ~BwxViewSwitcher() ;
    virtual bool AddView(wxView *view, const wxString& title = "");
    virtual bool RemoveView(wxView *view);
	//
	void setDocSession(BwDocSession *pSession) { p_docSession = pSession ; }
	void setAgentSession(BwAgentSession *pSession) { p_agentSession = pSession ; }
	//Data Members
	BwxDocManager* p_docMan ;
	//
	BwDocSession *p_docSession ;
	BwAgentSession *p_agentSession ;
	BwAgentClient *p_client ;
	//
	virtual void CreateButton(wxView* pView, const wxString& title) ;
	virtual void RemoveButton(wxView *pView) ;
	//
	void OnButton(wxCommandEvent& event) ;
	//
	//Data Members
	std::map<wxObject*, wxView*> m_viewMap ;
	std::map<wxView*, wxButton*> m_buttonMap ;
	//
	wxBoxSizer *p_sizer ;
	wxBookCtrlBase *p_book ;
	//
	DECLARE_EVENT_TABLE()
} ;


#endif// _BwxViewSwitcher_H
