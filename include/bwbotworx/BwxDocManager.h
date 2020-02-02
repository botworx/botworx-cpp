#ifndef _BwxDocManager_H
#define _BwxDocManager_H

#include "wx/docmdi.h"

class BwxAppFrame ;
class BwxAgentFrame ;
class BwxViewSwitcher ;

class BwxDocManager : public wxDocManager {
public:
	BwxDocManager() : p_switcher(NULL) {}
	void SetSwitcher(BwxViewSwitcher* pSwitcher) {	p_switcher = pSwitcher ; }
	BwxViewSwitcher* GetSwitcher() { return	p_switcher ; }
	//virtual void ActivateView(wxView *view, bool activate = true) {}
	//Data Members
	BwxViewSwitcher* p_switcher ;
} ;

class BwxAgencyDocManager : public BwxDocManager {
public:
	//virtual void ActivateView(wxView *view, bool activate = true) {}
} ;
class BwxAgentDocManager : public BwxDocManager {
public:
	BwxAgentDocManager() {}
	void SetFrame(BwxAgentFrame* pFrame) {
		p_frame = pFrame ;
	}
	//virtual void ActivateView(wxView *view, bool activate = true) {}
	//Data Members
	BwxAgentFrame* p_frame ;
} ;

#endif //_BwxDocManager_H