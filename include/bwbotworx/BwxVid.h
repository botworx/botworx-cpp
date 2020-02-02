#ifndef _BwxVid_H
#define _BwxVid_H

class BwxContext ;
class BwStateClient ;

class BwxVid : public wxPanel
{
public:
    //BwxVid(wxWindow *parent, const BwxContext& context, const bwString& name) ;
	BwxVid(wxWindow *parent, const BwxContext& context, bwHandle handle = bwAnyHandle) ;
	//
	void FillListBox(wxListBox* pListBox, const bwString& text) ;
	void SetIsShared(bool val) { m_isShared = val ; }
	bool IsShared() { return m_isShared ; }
	//Data Members
	bool m_isShared ;
};

#endif //_BwxVid_H
