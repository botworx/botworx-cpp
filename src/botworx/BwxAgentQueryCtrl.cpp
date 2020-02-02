#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxAgentQueryCtrl.h>
#include <bwbotworx/BwxAgentScriptEdit.h>
#include <bwbotworx/BwxAgentInputCtrl.h>
#include <bwbotworx/BwxAgentTtyCtrl.h>
#include <bwbotworx/BwxAgentLogCtrl.h>
#include <bwbotworx/BwxStateGraphVid.h>
//
//
#include <wx/splitter.h>
#include <wx/statbox.h>
#include <wx/toolbar.h>
//
#include <bwwx/resource/icon/xpm/go.xpm>
#include <bwwx/resource/icon/xpm/play.xpm>
#include <bwwx/resource/icon/xpm/pause.xpm>
#include <bwwx/resource/icon/xpm/stop.xpm>
#include <bwwx/resource/icon/xpm/redo.xpm>

//
#include <bwmessaging/BwMailSlot.h>
//
#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

#include <bwapplet/BwAppletSession.h>
#include <bwbotworx/_BwxAgentApplet.h>
using namespace _BwxAgentApplet ;

#include <bwagency/BwAgentClient.h>
#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;

#include <bwcore/_BwPart.h>
using namespace _BwPart ;

namespace _BwxAgentQueryCtrl {
class MyClient : public BwAgentClient {
public:
	MyClient(BwxAgentQueryCtrl *pOwner) : p_ctrl(pOwner) {}
	virtual bwString getClassName() { return "MyClient" ; }
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxAgentQueryCtrl *p_ctrl ;
};
} ; //namespace _BwxAgentQueryCtrl
using namespace _BwxAgentQueryCtrl ;

BwxAgentQueryCtrl::BwxAgentQueryCtrl(wxWindow *parent, const BwxContext& context) 
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), m_context(context) {
	//Init
	//Bw Stuff
	p_client = new MyClient(this) ;
	p_client->create() ;
	p_client->connect(context.getAgentSession()) ;
	//Wx Stuff
	m_topSizer = new wxBoxSizer(wxVERTICAL);
	//
	CreateBitmaps() ;
	CreateQueryToolBar() ;
	m_topSizer->Add(m_queryToolBar, 0, wxEXPAND | wxALL, 5) ;
	//
	CreateConditionCombos() ;
	CreateActionCombos() ;
	//
	SetSizer(m_topSizer);
    m_topSizer->SetSizeHints(this);
    m_topSizer->Fit(this);
}
BwxAgentQueryCtrl::~BwxAgentQueryCtrl() {
}
void BwxAgentQueryCtrl::CreateConditionCombos() {
	m_conditionsBox = new wxStaticBox(this, wxID_ANY, wxT("Conditions")) ;
	m_conditionsSizer = new wxStaticBoxSizer(m_conditionsBox, wxVERTICAL) ;
	m_topSizer->Add(m_conditionsSizer, 0, wxEXPAND | wxALL, 5) ;

	for(int i = 0 ; i < CONDITION_COMBO_TTL ; i++) {
		CreateConditionComboBox(i) ;
	} ;
}
void BwxAgentQueryCtrl::CreateConditionComboBox(int index) {
	std::vector<bwString> m_history ;
	m_history.push_back("news()") ;
	m_history.push_back("printMind()") ;
    // Steps ComboBox
	size_t stringTtl =  m_history.size() ;
    wxString *strings = new wxString[stringTtl] ;
    for (size_t i = 0; i < stringTtl ; ++i) {
		strings[i] = m_history[i].c_str() ;
    }
	//
    int pointSizeW = 256 ;
    int pointSizeH = 22;
	//
	BwxConditionComboBox *pComboBox = new BwxConditionComboBox() ;
	pComboBox->Create(this, ID_CONDITION_COMBO + index,
        wxEmptyString, wxDefaultPosition, wxSize(pointSizeW, pointSizeH), stringTtl, strings);
	m_conditionCombos.push_back(pComboBox) ;

    delete[] strings ;
	m_conditionsSizer->Add(pComboBox, 0, wxEXPAND | wxALL, 5) ;
}
//
void BwxAgentQueryCtrl::CreateActionCombos() {
	m_actionsBox = new wxStaticBox(this, wxID_ANY, wxT("Actions")) ;
	m_actionsSizer = new wxStaticBoxSizer(m_actionsBox, wxVERTICAL) ;
	m_topSizer->Add(m_actionsSizer, 0, wxEXPAND | wxALL, 5) ;

	for(int i = 0 ; i < ACTION_COMBO_TTL ; i++) {
		CreateActionComboBox(i) ;
	} ;
	m_actionCombos[0]->SetSelection(0);
}
void BwxAgentQueryCtrl::CreateActionComboBox(int index) {
	std::vector<bwString> m_history ;
	m_history.push_back("print") ;
    // Steps ComboBox
	size_t stringTtl =  m_history.size() ;
    wxString *strings = new wxString[stringTtl] ;
    for (size_t i = 0; i < stringTtl ; ++i) {
		strings[i] = m_history[i].c_str() ;
    }
	//
    int pointSizeW = 256 ;
    int pointSizeH = 22;
	//
	BwxActionComboBox *pComboBox = new BwxActionComboBox() ;
	pComboBox->Create(this, ID_ACTION_COMBO + index,
        wxEmptyString, wxDefaultPosition, wxSize(pointSizeW, pointSizeH), stringTtl, strings);
	m_actionCombos.push_back(pComboBox) ;

    delete[] strings ;
	m_actionsSizer->Add(pComboBox, 0, wxEXPAND | wxALL, 5) ;
}

///////////////////
void BwxAgentQueryCtrl::CreateBitmaps() {
    m_bitmaps[BMP_GO] = new wxBitmap( go_xpm );
    m_bitmaps[BMP_PLAY] = new wxBitmap( play_back_xpm );
    m_bitmaps[BMP_PAUSE] = new wxBitmap( pause_xpm );
    m_bitmaps[BMP_STOP] = new wxBitmap( stop_back_xpm );
    m_bitmaps[BMP_REDO] = new wxBitmap( redo_xpm );
}
void BwxAgentQueryCtrl::CreateQueryToolBar() {
    m_queryToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER|wxTB_FLAT);

    m_queryToolBar->AddTool(TOOL_EXEC, *m_bitmaps[BMP_GO], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Execute"));
    m_queryToolBar->AddTool(TOOL_RELOAD, *m_bitmaps[BMP_REDO], wxNullBitmap, false, wxDefaultCoord, wxDefaultCoord, NULL, _T("Reload"));

	m_queryToolBar->Realize();
}
////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(BwxAgentQueryCtrl, wxPanel)

EVT_TOOL(TOOL_EXEC, BwxAgentQueryCtrl::OnTool_Exec)
EVT_TOOL(TOOL_RELOAD, BwxAgentQueryCtrl::OnTool_Reload)

END_EVENT_TABLE()
//
void BwxAgentQueryCtrl::OnTool_Exec(wxCommandEvent& event) {
	bwString query ;
	for(int i = 0 ; i < CONDITION_COMBO_TTL ; i++) {
		wxString string = m_conditionCombos[i]->GetValue() ;
		if(!string.IsEmpty())
			query += "(" + bwString(string.c_str()) + ")" ;
	}
	query += "-->" ;
	for(int i = 0 ; i < ACTION_COMBO_TTL ; i++) {
		wxString string = m_actionCombos[i]->GetValue() ;
		if(!string.IsEmpty())
			query += "(" + bwString(string.c_str()) + ")" ;
	}

	m_context.getAppletSession()->getApplet()->getEventSlot().send(BwxQueryEvent(query)) ;
}
void BwxAgentQueryCtrl::OnTool_Reload(wxCommandEvent& event) {
}
////////////////////////////////////////////////////////////////////
void MyClient::onResponse(const BwMessage& msg) {
}
void MyClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			//wxPostEvent(p_ctrl, wxCommandEvent(wxEVT_CLOSE_WINDOW)) ;
			//wxPostEvent(p_ctrl, wxCommandEvent(wxEVT_MENU_CLOSE)) ;
			break ;
	}
	BwAgentClient::onEvent(msg) ;
}
///////////////////
