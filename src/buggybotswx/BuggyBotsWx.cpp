#include "stdafx.h"
#include "BuggyBotsWx.h"

#include "BwxVrCtrl.h"

#include "Applet.h"
#include "Scene.h"
#include "User.h"

#include <BwxInjector.h>
#include <BwxGui.h>
#include <BwxDeckFrame.h>
//
#include "BbKernel.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
	virtual int OnExit() ;
};
class MyVrCtrlInfo : public BwxVrCtrlInfo {
public:
	virtual VrApplet* produceApplet(BwxVrCtrl* pCtrl) {
		//f6:fixme:frame cast is hack
		return new Applet((wxFrame*)pCtrl->GetParent(), pCtrl) ;
	}
} ;
// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnCloseWindow(wxCloseEvent& event) ;
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
	BwxVrCtrl *p_vrCtrl;
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_CLOSE(MyFrame::OnCloseWindow)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
	BbKernel::startup() ;
    // create the main application window
    MyFrame *frame = new MyFrame(_T("Minimal wxWidgets App"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}
int MyApp::OnExit() {
	BbKernel::shutdown() ;
	return wxApp::OnExit() ;
}
// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
	SetSize(800,600) ;
    // set the frame icon
    SetIcon(wxICON(sample));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    fileMenu->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWidgets!"));
#endif // wxUSE_STATUSBAR
	//
	p_vrCtrl = new BwxVrCtrl( this, // parent is of type 'wxWindow*'
						MyVrCtrlInfo(),
						wxID_ANY,
						//wxPoint(0,0),//or wxDefaultPosition,
						wxDefaultPosition,
						//wxSize(400,300), //or wxDefaultSize
						wxDefaultSize,
						0 );
	// pass preferred minimum time for a single frame in milliseconds
	p_vrCtrl->startRendering(10); 
}


// event handlers
void MyFrame::OnCloseWindow(wxCloseEvent& event) {
	p_vrCtrl->startRendering() ; //f6:note:Frame won't close without doing this!
	wxFrame::OnCloseWindow(event) ;
}
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the About dialog of the minimal sample.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, _T("About Minimal"), wxOK | wxICON_INFORMATION, this);
}
