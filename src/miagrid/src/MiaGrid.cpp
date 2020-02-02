// TestEdit.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MiaGrid.h"

#include <MouseScenario/MouseScenario.h>
#include "MgScene.h"

#include <bwkernel/BwKernel.h>

MgScene* MgScene::g_singleton = NULL;
// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
	virtual bool OnInit() ;
	virtual int OnExit() {
		BwKernel::shutdown() ;
		return wxApp::OnExit() ;
	}
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
	~MyFrame() ;
    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void OnRenderTimer(wxTimerEvent& event) ;
private:
	wxTextCtrl *m_textCtrl;
	wxGrid* grid ;
	MgScenario *p_scenario ;
	wxTimer	m_timer ;
    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

bool MyApp::OnInit() {
	BwKernel::startup() ;
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
const long ID_RENDERTIMER = wxNewId();

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
	EVT_TIMER( ID_RENDERTIMER, MyFrame::OnRenderTimer )
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

/////////
class MyGridCellRenderer : public wxGridCellStringRenderer
{
public:
    virtual void Draw(wxGrid& grid,
                      wxGridCellAttr& attr,
                      wxDC& dc,
                      const wxRect& rect,
                      int row, int col,
                      bool isSelected)
	{
		wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

		dc.SetPen(*wxGREEN_PEN);
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawEllipse(rect);
	}
};
// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title), m_timer(this, ID_RENDERTIMER)
{
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
    /*m_textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
            wxDefaultSize, wxTE_MULTILINE|wxTE_RICH2);
   wxFont font = m_textCtrl->GetFont();
   font.SetPointSize(10);
	m_textCtrl->SetFont(font) ;*/
    grid = new wxGrid( this,
                       wxID_ANY,
                       wxPoint( 0, 0 ),
                       wxSize( 400, 300 ) );
 
	MgScene::g_singleton = new MgScene() ;
	MgScene::g_singleton->p_grid = grid ;

    grid->CreateGrid( 0, 0 );
    grid->AppendRows(16);
    grid->AppendCols(16);

	int rowCount = grid->GetNumberRows();
	int colCount = grid->GetNumberCols();

	for(int i = 0 ; i < rowCount ; i++) {
		grid->SetRowSize(i, 40);
		for(int j = 0 ; j < colCount ; j++) {
			grid->SetColSize(j, 40);
			//grid->SetCellRenderer(i, j, new MyGridCellRenderer());
		}
	}
/////////////////
	//p_scenario = new MgScenario() ;
	p_scenario = new MouseScenario() ;
	p_scenario->set_rowCount(16) ;
	p_scenario->set_colCount(16) ;
	p_scenario->createEnabled() ;
/////////////////
	m_timer.Start(10);
}
MyFrame::~MyFrame() {
	m_timer.Stop() ;
	destroyPart(p_scenario) ;
}
// event handlers
void MyFrame::OnRenderTimer(wxTimerEvent& event)
{
	BwStepper stepper ;
	//p_scenario->doStep(stepper) ;
	p_scenario->invokeStep(stepper) ;
	//p_scenario->doPostStep(stepper) ;
	p_scenario->invokePostStep(stepper) ;
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
