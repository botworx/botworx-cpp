#ifndef _BwxCard_H
#define _BwxCard_H

#include "wx/panel.h"
#include <wx/scrolwin.h>

class BwxUserMode ;
class BwxDeckFrame ;

class BwxCard : public wxPanel {
public:
	BwxCard(BwxDeckFrame *pFrame) ;
	virtual ~BwxCard() ;
	virtual void createButton(BwxUserMode *pMode) ;
	virtual void setName(bwString name) {}
	//
	void OnButton(wxCommandEvent& event) ;
	//
	//Data Members
	std::map<wxObject*, BwxUserMode*> m_buttonMap ;
	//
	wxWindow *p_client ;
	wxBoxSizer *p_sizer ;
	//
	DECLARE_EVENT_TABLE()
} ;


#endif// _BwxCard_H
