#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxAgentConsole.h>
#include <bwbotworx/BwxAgentScriptEdit.h>
#include <bwbotworx/BwxAgentInputCtrl.h>
#include <bwbotworx/BwxAgentTtyCtrl.h>
#include <bwbotworx/BwxAgentLogCtrl.h>
#include <bwbotworx/BwxStateGraphVid.h>
#include <bwbotworx/BwxMindExplorer.h>
//
#include <wx/splitter.h>
#include <wx/toolbar.h>
//
#include <bwwx/resource/icon/xpm/go.xpm>
#include <bwwx/resource/icon/xpm/play.xpm>
#include <bwwx/resource/icon/xpm/pause.xpm>
#include <bwwx/resource/icon/xpm/stop.xpm>
#include <bwwx/resource/icon/xpm/redo.xpm>

enum {
	ID_TOOLBAR = 300,
	ID_STEPS_COMBO,
	ID_QIKCMD_COMBO
} ;
//
enum {
	TOOL_EXEC = 500,
	TOOL_STEP,
	TOOL_RUN,
	TOOL_STOP,
	TOOL_PAUSE,
	TOOL_RELOAD,
	TOOL_MAX
} ;
//
#include <bwmessaging/BwMailSlot.h>
//
#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

namespace _BwxAgentConsole {
class MyClient : public BwAgentClient {
public:
	MyClient(BwxAgentConsole *pOwner) : p_console(pOwner) {}
	virtual bwString getClassName() { return "MyClient" ; }
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxAgentConsole *p_console ;
};
} ; //namespace _BwxAgentConsole
using namespace _BwxAgentConsole ;

BwxAgentConsole::BwxAgentConsole(wxWindow *parent, const BwxContext& context) 
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize) {
	//Init
	m_steps = STEPS_DEFAULT ;
	//Bw Stuff
	p_client = new MyClient(this) ;
	p_client->create() ;
	p_client->connect(context.getAgentSession()) ;
	//Wx Stuff
	const wxSize imageSize(32, 32);
	m_imageList = new wxImageList(imageSize.GetWidth(), imageSize.GetHeight());
	m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM | wxNB_NOPAGETHEME) ;
	m_notebook->SetImageList(m_imageList);
	//wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY) ;
	//m_inputCtrl = new BwxAgentInputCtrl(this, context) ;
	//m_scriptEdit = new BwxAgentScriptEdit(m_notebook, context) ;
	m_ttyCtrl = new BwxAgentTtyCtrl(m_notebook, context) ;
	m_logCtrl = new BwxAgentLogCtrl(m_notebook, context) ;
	//m_stateGraphVid = new BwxStateGraphVid(m_notebook, context, "State Graph") ;
	m_stateGraphVid = new BwxStateGraphVid(m_notebook, context) ;
	m_mindExplorer = new BwxMindExplorer(m_notebook, context) ;

	wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
	sizerTop->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

	/*wxStaticBox *staticBox = new wxStaticBox(this, wxID_ANY, wxT("Input")) ;
	wxStaticBoxSizer* staticSizer = new wxStaticBoxSizer(staticBox, wxVERTICAL) ;
	sizerTop->Add(staticSizer, 0, wxEXPAND | wxALL, 5) ;
	staticSizer->Add(m_inputCtrl, 0, wxEXPAND | wxALL, 5) ;*/

	CreateBitmaps() ;
	CreateConsoleToolBar() ;
	sizerTop->Add(m_consoleToolBar, 0, wxEXPAND | wxALL, 5) ;

	//m_notebook->AddPage(m_scriptEdit, wxT("Script"), true, 0) ;
	m_notebook->AddPage(m_ttyCtrl, wxT("Output"), false) ;
	m_notebook->AddPage(m_logCtrl, wxT("Log"), false) ;
	m_notebook->AddPage(m_stateGraphVid, wxT("State Graph"), false) ;
	m_notebook->AddPage(m_mindExplorer, wxT("Mind Explorer"), false) ;

	SetSizer(sizerTop);
    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this);

	//splitter->SplitHorizontally(m_inputCtrl, m_ttyCtrl, 100);
}
BwxAgentConsole::~BwxAgentConsole() {
}
void BwxAgentConsole::CreateBitmaps() {
    m_bitmaps[BMP_GO] = new wxBitmap( go_xpm );
    m_bitmaps[BMP_PLAY] = new wxBitmap( play_back_xpm );
    m_bitmaps[BMP_PAUSE] = new wxBitmap( pause_xpm );
    m_bitmaps[BMP_STOP] = new wxBitmap( stop_back_xpm );
    m_bitmaps[BMP_REDO] = new wxBitmap( redo_xpm );
}
void BwxAgentConsole::CreateConsoleToolBar() {
    m_consoleToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER|wxTB_FLAT);

	CreateStepsComboBox() ;

    m_consoleToolBar->AddTool(TOOL_STEP, _T("Step"), *m_bitmaps[BMP_GO], wxNullBitmap);
    m_consoleToolBar->AddTool(TOOL_RUN,  _T("Run"), *m_bitmaps[BMP_PLAY], wxNullBitmap);
    m_consoleToolBar->AddTool(TOOL_PAUSE,  _T("Pause"), *m_bitmaps[BMP_PAUSE], wxNullBitmap);
    m_consoleToolBar->AddTool(TOOL_STOP, _T("Stop"), *m_bitmaps[BMP_STOP], wxNullBitmap);
    m_consoleToolBar->AddTool(TOOL_RELOAD, _T("Reload"), *m_bitmaps[BMP_REDO], wxNullBitmap);

	m_consoleToolBar->AddSeparator() ;

	CreateQikCmdComboBox() ;

	m_consoleToolBar->Realize();
}
void BwxAgentConsole::CreateStepsComboBox() {
    // Steps ComboBox
    int stringTtl = (STEPS_MAX - STEPS_MIN) / STEPS_INCREMENT ;
    wxString *stepStrings = new wxString[stringTtl];
    for (int i = 0; i < stringTtl ; ++i) {
        stepStrings[i].Printf(_T("%d"), (i*STEPS_INCREMENT + STEPS_MIN));
    }
	//
    int pointSizeW = 60;
    int pointSizeH = 22;
	//
    m_stepsComboBox = new wxComboBox(m_consoleToolBar, ID_STEPS_COMBO,
        wxEmptyString, wxDefaultPosition, wxSize(pointSizeW, pointSizeH), stringTtl, stepStrings);
    m_stepsComboBox->SetSelection(0);
    delete[] stepStrings ;
	m_consoleToolBar->AddControl(m_stepsComboBox) ;
}
void BwxAgentConsole::CreateQikCmdComboBox() {
	m_qikCommands.push_back("news()") ;
	m_qikCommands.push_back("printMind()") ;
    // Steps ComboBox
	size_t stringTtl =  m_qikCommands.size() ;
    wxString *strings = new wxString[stringTtl] ;
    for (size_t i = 0; i < stringTtl ; ++i) {
		strings[i] = m_qikCommands[i].c_str() ;
    }
	//
    int pointSizeW = 256 ;
    int pointSizeH = 22;
	//
    m_qikCmdComboBox = new wxComboBox(m_consoleToolBar, ID_QIKCMD_COMBO,
        wxEmptyString, wxDefaultPosition, wxSize(pointSizeW, pointSizeH), stringTtl, strings);
    //m_qikCmdComboBox->SetSelection(0);
    delete[] strings ;
	m_consoleToolBar->AddControl(m_qikCmdComboBox) ;
	m_consoleToolBar->AddTool(TOOL_EXEC, _T("Execute"), *m_bitmaps[BMP_GO], wxNullBitmap);
}
////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(BwxAgentConsole, wxPanel)
EVT_COMBOBOX(ID_QIKCMD_COMBO, BwxAgentConsole::OnQikCmdSel)
EVT_TEXT(ID_QIKCMD_COMBO, BwxAgentConsole::OnQikCmdText)
EVT_TEXT_ENTER(ID_QIKCMD_COMBO, BwxAgentConsole::OnQikCmdTextEnter)
EVT_TOOL(TOOL_EXEC, BwxAgentConsole::OnTool_Exec)

EVT_COMBOBOX(ID_STEPS_COMBO, BwxAgentConsole::OnStepsSel)
EVT_TOOL(TOOL_STEP, BwxAgentConsole::OnTool_Step)
EVT_TOOL(TOOL_RUN, BwxAgentConsole::OnTool_Run)
EVT_TOOL(TOOL_PAUSE, BwxAgentConsole::OnTool_Pause)
EVT_TOOL(TOOL_STOP, BwxAgentConsole::OnTool_Stop)
EVT_TOOL(TOOL_RELOAD, BwxAgentConsole::OnTool_Reload)
EVT_TOOL_ENTER(ID_TOOLBAR, BwxAgentConsole::OnToolEnter)
END_EVENT_TABLE()
//
void BwxAgentConsole::OnStepsSel(wxCommandEvent& event) {
    wxComboBox* combo = (wxComboBox*) event.GetEventObject();
    wxASSERT( combo );
	m_steps = ((int)combo->GetSelection()+1) * STEPS_INCREMENT ;
}
void BwxAgentConsole::OnQikCmdSel(wxCommandEvent& event) {
    wxComboBox* combo = (wxComboBox*) event.GetEventObject();
    wxASSERT( combo );
	wxString cmdString = combo->GetStringSelection() ;
	m_qikCmd.set(cmdString.ToStdString()) ;
}
void BwxAgentConsole::OnQikCmdText(wxCommandEvent& event) {
    wxComboBox* combo = (wxComboBox*) event.GetEventObject();
    wxASSERT( combo );
	wxString cmdString = combo->GetValue() ;
	m_qikCmd.set(cmdString.ToStdString()) ;
}
void BwxAgentConsole::OnQikCmdTextEnter(wxCommandEvent& event) {
    wxComboBox* combo = (wxComboBox*) event.GetEventObject();
    wxASSERT( combo );
	wxString cmdString = combo->GetValue() ;
	m_qikCmd.set(cmdString.ToStdString()) ;
	m_ttyCtrl->sendCommand(m_qikCmd) ;
}
void BwxAgentConsole::OnTool_Exec(wxCommandEvent& event) {
	m_ttyCtrl->sendCommand(m_qikCmd) ;
}
void BwxAgentConsole::OnTool_Step(wxCommandEvent& event) {
	BwCmd stepCmd("step") ;
	m_ttyCtrl->sendCommand(stepCmd << m_steps << end ) ;
}
void BwxAgentConsole::OnTool_Run(wxCommandEvent& event) {
	m_ttyCtrl->sendCommand(BwCmd("run") << end) ;
}
void BwxAgentConsole::OnTool_Pause(wxCommandEvent& event) {
	m_ttyCtrl->sendCommand(BwCmd("pause") << end) ;
}
void BwxAgentConsole::OnTool_Stop(wxCommandEvent& event) {
	m_ttyCtrl->sendCommand(BwCmd("stop") << end) ;
}
void BwxAgentConsole::OnTool_Reload(wxCommandEvent& event) {
	m_stateGraphVid->Clear() ;
	m_ttyCtrl->sendCommand(BwCmd("reload") << end) ;
}
void BwxAgentConsole::OnToolEnter(wxCommandEvent& event) {
}
////////////////////////////////////////////////////////////////////
void MyClient::onResponse(const BwMessage& msg) {
}
void MyClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			//wxPostEvent(p_console, wxCommandEvent(wxEVT_CLOSE_WINDOW)) ;
			//wxPostEvent(p_console, wxCommandEvent(wxEVT_MENU_CLOSE)) ;
			break ;
	}
	BwAgentClient::onEvent(msg) ;
}
///////////////////
