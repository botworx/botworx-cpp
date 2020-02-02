#ifndef _BwxStateGraphCtrl_H
#define _BwxStateGraphCtrl_H

#include "BwxGraphCtrl.h"
class BwxTreeLayoutStored ;

class BwxContext ;
class BwAgentClient ;

class BwxStateGraphItem {
public:
	BwxStateGraphItem(wxShape* pShape, const bwString& name, bwHandle handle) 
		: p_shape(pShape) , m_handle(handle), m_name(name) {
	}
	wxShape* GetShape() { return p_shape ; }
	bwHandle GetHandle() { return m_handle ; }
	bwString GetName() { return m_name ; }
	//Data Members
	wxShape* p_shape ;
	bwHandle m_handle ;
	bwString m_name ;
} ;
class BwxStateGraphCtrl : public BwxGraphCtrl
{
public:
    BwxStateGraphCtrl(wxWindow *parent, const BwxContext& context) ;
	virtual ~BwxStateGraphCtrl() ;
	void CreateLayout() ;
	virtual void Clear() ;
	void _Clear() ;
	//
	virtual BwxShapeEvtHandler* CreateEvtHandler(wxShapeEvtHandler *prev = NULL, wxShape *shape = NULL, const wxString& lab = wxEmptyString, bwHandle handle = bwAnyHandle) ;
	void SetRootItem(BwxStateGraphItem* pItem) { p_rootItem = pItem ; m_itemMap[pItem->GetHandle()] = pItem ; }
	BwxStateGraphItem* GetRootItem() { return p_rootItem ; }
	void AddState(const bwPath &path, bwHandle handle, bwHandle parentHandle, const bwString& arc) ;
	void OnSolution(bwHandle handle) ;
	void OnFailed(bwHandle handle) ;
	void ColorState(bwHandle handle, const wxColour& colour) ;
	virtual void OnShapeSelection(wxShape* pShape) ;
	virtual void DoLayout() ;
	//Data Members
	BwxContext m_context ;
	BwxStateGraphItem* p_rootItem ;
	std::map<bwHandle, BwxStateGraphItem*> m_itemMap ;
	BwAgentClient* p_client ;
	int m_childX ;
	int m_childY ;
	//
	BwxTreeLayoutStored *p_layout ;
};

#endif //_BwxStateGraphCtrl_H