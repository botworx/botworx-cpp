#ifndef _BwxAgentScriptEdit_H
#define _BwxAgentScriptEdit_H

#include <wx/stc/stc.h>

class BwxContext ;
class BwDocClient ;

class BwxAgentScriptEdit: public wxStyledTextCtrl
{
public:   
    BwxAgentScriptEdit (wxWindow *parent, const BwxContext& context);
	//Data Members
	wxWindow *m_container ;
	BwDocClient *p_client ;
};

#endif //_BwxAgentScriptEdit_H