#ifndef _BwxApp_H
#define _BwxApp_H

#include <wx/app.h>
#include <wx/mdi.h>
#include <wx/docview.h>
#include <wx/docmdi.h>

class BwxAppFrame ;
class BwxAgentFrame ;

#include "BwxDocManager.h"

typedef std::map<BwxAgentDocManager*, BwxAgentFrame*> BwxAgentFrameMap ;
typedef BwxAgentFrameMap::iterator BwxAgentFrameIter ;

// Define a new application type, each program should derive a class from wxApp
class BwxApp : public wxApp
{
public:
    BwxApp() { m_showImages = true; m_showButtons = false; }

    virtual bool OnInit();
	virtual int OnExit() ;

    void SetShowImages(bool show) { m_showImages = show; }
    bool ShowImages() const { return m_showImages; }

    void SetShowButtons(bool show) { m_showButtons = show; }
    bool ShowButtons() const { return m_showButtons; }
	//
	BwxAppFrame* GetAppFrame() { return p_frame ; }
	BwxAgencyDocManager* GetDocumentManager() { return m_docManager ; }
	wxDocTemplate* GetAgentDocTemplate() { return p_agentDocTemplate ; }
	//Data Members
public:
    BwxAgencyDocManager* m_docManager;
	wxDocTemplate* p_agentDocTemplate ;
	BwxAppFrame *p_frame ;

private:
    bool m_showImages, m_showButtons;

};

#endif //_BwxApp_H