#ifndef _BwxTv_H
#define _BwxTv_H

class BwxContext ;
class BwAppletClient ;
class BwAgentClient ;

class BwxVid ;

class BwxTv : public wxPanel
{
public:
    BwxTv(wxWindow *parent, const BwxContext& context) ;
	//
	//virtual void AddVid(const bwString& path) ;
	virtual void AddVid(bwHandle handle) ;
	//virtual BwxVid* CreateVid(wxWindow *parent, const BwxContext& context, const bwString& name) { return NULL ; }
	virtual BwxVid* CreateVid(wxWindow *parent, const BwxContext& context, bwHandle handle) { return NULL ; }
	//virtual void ChangeVid(const bwString& name) ;
	virtual void ChangeVid(bwHandle handle) ;
	wxPanel *GetDrawer() { return p_drawer ; }
	void SetIsSharedVid(bool val) { m_isSharedVid = val ; }
	bool IsSharedVid() { return m_isSharedVid ; }
	//Data Members
	bool m_isSharedVid ;
	//Data Members
	BwAppletClient* p_appletClient ;
	BwAgentClient* p_agentClient ;
	//Data Members
	BwxContext m_context ;
	BwxVid* p_vid ;
	//std::map<bwString, BwxVid*> m_vidMap ;
	std::map<bwHandle, BwxVid*> m_vidMap ;
	wxPanel *p_drawer ;
	wxSizer *p_sizer ;
};

#endif //_BwxTv_H