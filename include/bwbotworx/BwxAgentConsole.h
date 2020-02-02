#ifndef _BwxAgentConsole_H
#define _BwxAgentConsole_H

#include "wx/panel.h"
#include "wx/notebook.h"

#include <bwmessaging/BwCmd.h>

class BwxContext ;

class BwxAgentScriptEdit ;
class BwxAgentInputCtrl ;
class BwxAgentTtyCtrl ;
class BwxAgentLogCtrl ;
class BwxStateGraphVid ;
class BwxMindExplorer ;
class BwDocSession ;

class BwAgentClient ;
class BwAgentSession ;

class BwxAgentConsole : public wxPanel {
public:
	BwxAgentConsole(wxWindow *parent, const BwxContext& context) ;
	virtual ~BwxAgentConsole() ;
	void CreateBitmaps() ;
	void CreateConsoleToolBar() ;
	void CreateStepsComboBox() ;
	void CreateQikCmdComboBox() ;
	//GUI Events
	void OnQikCmdSel(wxCommandEvent& event) ;
	void OnQikCmdText(wxCommandEvent& event) ;
	void OnQikCmdTextEnter(wxCommandEvent& event) ;
	void OnTool_Exec(wxCommandEvent& event) ;

	void OnStepsSel(wxCommandEvent& event) ;
	void OnTool_Step(wxCommandEvent& event) ;
	void OnTool_Run(wxCommandEvent& event) ;
	void OnTool_Pause(wxCommandEvent& event) ;
	void OnTool_Stop(wxCommandEvent& event) ;
	void OnTool_Reload(wxCommandEvent& event) ;
	void OnToolEnter(wxCommandEvent& event) ;
	//
	void setDocSession(BwDocSession *pSession) { p_docSession = pSession ; }
	void setAgentSession(BwAgentSession *pSession) { p_agentSession = pSession ; }
	//Data Members
	wxImageList *m_imageList;
	wxNotebook *m_notebook ;
	BwxAgentTtyCtrl *m_ttyCtrl ;
	BwxAgentLogCtrl *m_logCtrl ;
	BwxStateGraphVid *m_stateGraphVid ;
	BwxMindExplorer *m_mindExplorer ;
	//
	enum {
		BMP_GO,
		BMP_PLAY,
		BMP_PAUSE,
		BMP_STOP,
		BMP_REDO,
		BMP_MAX
	} ;
	wxBitmap* m_bitmaps[BMP_MAX] ;
	wxToolBar* m_consoleToolBar ;
	wxComboBox* m_stepsComboBox ;
	wxComboBox* m_qikCmdComboBox ;
	//
	std::string m_buffer ;
	BwDocSession *p_docSession ;
	BwAgentSession *p_agentSession ;
	BwAgentClient *p_client ;
	//
	enum {
		STEPS_DEFAULT = 5,
		STEPS_MIN = 5,
		STEPS_INCREMENT = 5,
		STEPS_MAX = 200
	} ;
	int m_steps ;
	//
	std::vector<bwString> m_qikCommands ;
	BwCmd m_qikCmd ;
	//
	DECLARE_EVENT_TABLE()
} ;


#endif// _BwxAgentConsole_H
