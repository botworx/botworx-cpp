#ifndef _BwxMindTreeCtrl_H
#define _BwxMindTreeCtrl_H

#include "BwxTreeCtrl.h"

class BwAgentClient ;
class BwAgentSession ;

class BwxMindTreeItemData : public BwxTreeItemData {
public:
    //BwxTreeItemData(const wxString& desc) : m_desc(desc) { }
	BwxMindTreeItemData(const bwPath &path, bwHandle handle, bwHandle parentHandle, const bwString& arc) 
		: BwxTreeItemData (path.leaf().c_str()) {
		m_handle = handle ;
		m_parentHandle = parentHandle ;
		m_arc = arc ;
	}
    void ShowInfo(wxTreeCtrl *tree);
    const wxChar *GetDesc() const { return m_desc.c_str(); }
	//Data Members
	bwHandle m_handle ;
	bwHandle m_parentHandle ;
	bwString m_arc ;
};

class BwxMindTreeCtrl : public BwxTreeCtrl {
public:
	BwxMindTreeCtrl(wxWindow *parent, const BwxContext& context) ;
    BwxMindTreeCtrl() { }
    virtual ~BwxMindTreeCtrl(){};
	//
	void CreateItem(const bwPath &path, bwHandle handle, bwHandle parentHandle, const bwString& arc) ;
	//Event Handlers
	void OnItemActivated(wxTreeEvent& event);
    // NB: due to an ugly wxMSW hack you _must_ use DECLARE_DYNAMIC_CLASS()
    //     if you want your overloaded OnCompareItems() to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default (alphabetical) sorting much faster under wxMSW.
    DECLARE_DYNAMIC_CLASS(BwxMindTreeCtrl)
    DECLARE_EVENT_TABLE()
	//Bw Stuff
public:
	BwAgentClient *p_client ;
	BwxContext m_context ;
};


#endif// _BwxMindTreeCtrl_H
