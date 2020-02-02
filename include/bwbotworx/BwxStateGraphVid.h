#ifndef _BwxStateGraphVid_H
#define _BwxStateGraphVid_H

#include "BwxVid.h"

class BwxContext ;
class BwStateClient ;

class BwxStateGraphCtrl ;

class BwxStateGraphVid : public BwxVid
{
public:
    BwxStateGraphVid(wxWindow *parent, const BwxContext& context) ;
	void CreateGraphToolBar() ;
	virtual void Clear() ;
	//
	void OnZoomSel(wxCommandEvent& event);
	//Data Members
	BwxStateGraphCtrl* m_stateGraphCtrl ;
	wxToolBar* m_graphToolBar ;
	wxBoxSizer *p_sizer ;
	//
    wxComboBox*             m_pointSizeComboBox;
    wxComboBox*             m_zoomComboBox;
	//
	DECLARE_EVENT_TABLE()
};

#endif //_BwxStateGraphVid_H
