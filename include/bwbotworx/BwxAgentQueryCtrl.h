#ifndef _BwxAgentQueryCtrl_H
#define _BwxAgentQueryCtrl_H

#include "wx/panel.h"
#include "wx/notebook.h"
#include "wx/combobox.h"

#include <bwmessaging/BwCmd.h>

class BwxContext ;
class BwDocSession ;

class BwAgentClient ;
class BwAgentSession ;

class BwxRuleNodeComboBox : public wxComboBox {
public:
	BwxRuleNodeComboBox() : wxComboBox() {}
} ;
class BwxConditionComboBox : public BwxRuleNodeComboBox {
public:
	BwxConditionComboBox() : BwxRuleNodeComboBox() {}
} ;
class BwxActionComboBox : public BwxRuleNodeComboBox {
public:
	BwxActionComboBox() : BwxRuleNodeComboBox() {}
} ;

class BwxAgentQueryCtrl : public wxPanel {
public:
	BwxAgentQueryCtrl(wxWindow *parent, const BwxContext& context) ;
	virtual ~BwxAgentQueryCtrl() ;
	void CreateBitmaps() ;
	void CreateQueryToolBar() ;
	//
	void CreateConditionCombos() ;
	void CreateConditionComboBox(int index) ;
	//
	void CreateActionCombos() ;
	void CreateActionComboBox(int index) ;
	//
	//GUI Events
	void OnTool_Exec(wxCommandEvent& event) ;
	void OnTool_Reload(wxCommandEvent& event) ;
	//
	//Data Members
	enum {
		CONDITION_COMBO_TTL = 5,
		ACTION_COMBO_TTL = 5
	} ;
	//
	enum {
		BMP_GO,
		BMP_PLAY,
		BMP_PAUSE,
		BMP_STOP,
		BMP_REDO,
		BMP_MAX
	} ;
	enum {
		ID_TOOLBAR = 300,
		ID_CONDITION_COMBO,
		ID_ACTION_COMBO = ID_CONDITION_COMBO + CONDITION_COMBO_TTL
	} ;
	//
	enum {
		TOOL_EXEC = 500,
		TOOL_RELOAD,
		TOOL_MAX
	} ;
	//
	wxBoxSizer* m_topSizer ;
	//Condition Combos
	wxStaticBox* m_conditionsBox ;
	wxStaticBoxSizer* m_conditionsSizer ;
	//Action Combos
	wxStaticBox* m_actionsBox ;
	wxStaticBoxSizer* m_actionsSizer ;

	wxBitmap* m_bitmaps[BMP_MAX] ;
	wxToolBar* m_queryToolBar ;
	//
	BwxContext m_context ;
	BwAgentClient *p_client ;
	//
	std::vector<BwxConditionComboBox*> m_conditionCombos ;
	std::vector<BwxActionComboBox*> m_actionCombos ;
	//
	DECLARE_EVENT_TABLE()
} ;


#endif// _BwxAgentQueryCtrl_H
