#include "stdafx.h"

#include "BwxDeckFrame.h"
#include "BwxCard.h"
#include "BwxUserMode.h"
// BwxDeckFrame

/*#include "Icon/Xpm/new.xpm"
#include "Icon/Xpm/open.xpm"
#include "Icon/Xpm/save.xpm"
#include "Icon/Xpm/copy.xpm"
#include "Icon/Xpm/cut.xpm"
#include "Icon/Xpm/paste.xpm"
#include "Icon/Xpm/print.xpm"
#include "Icon/Xpm/help.xpm"*/

BEGIN_EVENT_TABLE(BwxDeckFrame, wxMiniFrame)
    EVT_CLOSE  (              BwxDeckFrame::OnCloseWindow)
END_EVENT_TABLE()

BwxDeckFrame::BwxDeckFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
        const wxSize& size ) :
  wxMiniFrame(parent, id, title, pos, size )
{
	p_controlPanel = NULL ;
	p_drawer = new wxPanel(this) ;
	p_drawer->Show(false) ;
	//p_sizer = new wxBoxSizer(wxVERTICAL) ;
    SetAutoLayout( true );
    //SetSizer( p_sizer );
}
// IDs for the controls and the menu commands. Exluding those already defined
// by wxWidgets, such as wxID_NEW.
enum
{
    // timer
    ID_TIMER = wxID_HIGHEST,

    // file menu
    ID_SAMPLES,

    // view menu
    ID_SHOWNAV,
    ID_ORIGIN,
    ID_CENTER,
    ID_NORTH,
    ID_SOUTH,
    ID_EAST,
    ID_WEST,
    ID_INFO,

    // game menu
    ID_START,
    ID_STEP,
    ID_TOPSPEED,

    // speed selection slider
    ID_SLIDER
};
void BwxDeckFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
  // make it known that the miniframe is no more
  Destroy();
}
void BwxDeckFrame::setControlPanel(BwxUserMode *pMode) {
	if(p_controlPanel != NULL)
		//p_controlPanel->Show(false) ;
		p_controlPanel->Reparent(p_drawer) ;

	SetTitle(wxString(pMode->getShortName().c_str())) ;
	p_controlPanel = pMode->getControlPanel() ;
	p_controlPanel->Reparent(this) ;
	p_controlPanel->Show(true) ;
	Fit() ;
}