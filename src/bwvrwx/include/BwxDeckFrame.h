#ifndef _BwxDeckFrame_H
#define _BwxDeckFrame_H

#include "wx/minifram.h"

class BwxUserMode ;
class BwxCard ;

// Define a new mini frame
class BwxDeckFrame: public wxMiniFrame
{
public:
    BwxDeckFrame(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString& title = _T("wxToolBar Sample"),
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );
    void OnCloseWindow(wxCloseEvent& event);
    //
	void setControlPanel(BwxUserMode *pMode) ;
	wxPanel *getDrawer() { return p_drawer ; }
	//Data Members
	BwxCard *p_controlPanel ;
	wxPanel *p_drawer ;
	wxBoxSizer *p_sizer ;
	DECLARE_EVENT_TABLE()
};

#endif //_BwxDeckFrame_H
