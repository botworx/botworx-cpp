#ifndef _BwxMindVid_H
#define _BwxMindVid_H

#include <wx/notebook.h>

#include "BwxVid.h"

class BwStateClient ;

class BwxMindVid : public BwxVid
{
public:
    //BwxMindVid(wxWindow *parent, const BwxContext& context, const bwString& name) ;
	BwxMindVid(wxWindow *parent, const BwxContext& context, bwHandle handle) ;
	//
	void AddFact(const bwString& fact) ;
	void RemoveFact(const bwString& fact) ;
	void RefreshFacts(const bwString& facts) ;
	void RefreshLog(const bwString& log) ;
	void FillListBox(wxListBox* pListBox, const bwString& text) ;
	//Data Members
	wxImageList *m_imageList;
	wxNotebook* m_notebook ;
	wxListBox* p_factsListBox ;
	wxListBox* p_logListBox ;
	BwStateClient* p_client ;
};

#endif //_BwxMindVid_H
