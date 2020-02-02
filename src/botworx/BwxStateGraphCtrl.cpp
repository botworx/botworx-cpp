// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <wx/colourdata.h>

#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxStateGraphCtrl.h>
#include <bwbotworx/BwxGraph.h>
#include <bwbotworx/BwxGraphCanvas.h>

#include <bwbotworx/BwxGraphLayout.h>

#include <bwmessaging/BwCmd.h>
#include <bwapplet/BwAppletSession.h>
#include <bwbotworx/_BwxAgentApplet.h>
using namespace _BwxAgentApplet ;

#include <bwagency/BwAgentClient.h>
#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;

namespace _BwxStateGraphCtrl {
/////////////
class MyClient : public BwAgentClient {
public:
	MyClient(BwxStateGraphCtrl *pCtrl) : p_ctrl(pCtrl) {}
	virtual bwString getClassName() { return "MyClient" ; }
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxStateGraphCtrl *p_ctrl ;
};
void MyClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_STATE_ADDED : {
			bwString path ;
			bwHandle handle ;
			bwHandle parentHandle ;
			bwString arc ;
			msg()->findString("PATH", path) ;
			msg()->findHandle("HANDLE", handle) ;
			msg()->findHandle("PARENT", parentHandle) ;
			msg()->findString("ARC", arc) ;
			p_ctrl->AddState(path, handle, parentHandle, arc) ;
		}
		break ;
		case EVENT_STATE_SOLUTION : {
			bwHandle handle ;
			msg()->findHandle("HANDLE", handle) ;
			p_ctrl->OnSolution(handle) ;
		}
		break ;
		case EVENT_STATE_FAILED : {
			bwHandle handle ;
			msg()->findHandle("HANDLE", handle) ;
			p_ctrl->OnFailed(handle) ;
		}
		break ;
		case EVENT_RELOAD_ENDED :
			//p_ctrl->Clear() ;
		case EVENT_LOAD_ENDED :
		case EVENT_RUN_ENDED : {
			p_ctrl->DoLayout() ;
		}
			break ;
	}
	BwAgentClient::onEvent(msg) ;
}
/////////////////////////////////////////
class MyShapeEvtHandler: public BwxShapeEvtHandler {
	public:
		MyShapeEvtHandler(BwxStateGraphCtrl *pCtrl, wxShapeEvtHandler *prev = NULL, wxShape *shape = NULL, const wxString& lab = wxEmptyString, bwHandle handle = bwAnyHandle)
		:	BwxShapeEvtHandler(pCtrl, prev, shape, lab, handle)
	{
	}
	~MyShapeEvtHandler(void)
	{
	}
	/*virtual void OnLeftClick(double x, double y, int keys = 0, int attachment = 0);
	void OnBeginDragRight(double x, double y, int keys = 0, int attachment = 0);
	void OnDragRight(bool draw, double x, double y, int keys = 0, int attachment = 0);
	void OnEndDragRight(double x, double y, int keys = 0, int attachment = 0);
	void OnEndSize(double x, double y);*/
};

} //end namespace _BwxStateGraphCtrl
using namespace _BwxStateGraphCtrl ;

BwxStateGraphCtrl::BwxStateGraphCtrl(wxWindow *parent, const BwxContext& context)
	: BwxGraphCtrl(parent), m_context(context) {

   	p_client = new MyClient(this) ;
	p_client->create() ;
	p_client->connect(context.getAgentSession()) ;

	_Clear() ;
}
BwxStateGraphCtrl::~BwxStateGraphCtrl() {
	delete p_client ;
	delete p_layout ;
}
void BwxStateGraphCtrl::CreateLayout() {
	p_layout = new BwxTreeLayoutStored(65535) ;
	p_layout->SetMargins(20,20) ;
	p_layout->SetSpacing(120, 120) ;
}
void BwxStateGraphCtrl::Clear() {
	if(p_layout)
		delete p_layout ;
	GetGraph()->DeleteAllShapes() ;
	_Clear() ;
}
void BwxStateGraphCtrl::_Clear() {
  	m_childX = 100 ;
	m_childY = 100 ;
	//
	CreateLayout() ;
}
BwxShapeEvtHandler* BwxStateGraphCtrl::CreateEvtHandler(wxShapeEvtHandler *prev, wxShape *shape, const wxString& lab, bwHandle handle) {
	return new MyShapeEvtHandler(this, prev, shape, lab, handle) ;
}
void BwxStateGraphCtrl::OnShapeSelection(wxShape* pShape) {
	BwxGraphCtrl::OnShapeSelection(pShape) ;
	BwxShapeEvtHandler *myHandler = (BwxShapeEvtHandler *)pShape->GetEventHandler();
	m_context.getAppletSession()->getApplet()->getEventSlot().send(BwxStateSelectedEvent(myHandler->m_handle)) ;
	const size_t bufferSize = 16;
	char buffer[bufferSize] ;
	//_itoa(myHandler->m_handle, buffer, 10) ;
	snprintf(buffer, bufferSize, "%d", myHandler->m_handle);
	//bwItoa(myHandler->m_handle, buffer, bufferSize, 10);
	BwCmd cmd("selectMind");
	p_client->doCommand(cmd << bwString(buffer) << end) ;
}
void BwxStateGraphCtrl::AddState(const bwPath &path, bwHandle handle, bwHandle parentHandle, const bwString& arc) {
	wxClassInfo *info = NULL;
	info = CLASSINFO(wxRectangleShape);
	GetCommandProcessor()->Submit(
		new BwxGraphCommand( info->GetClassName(), path.string().c_str(), handle, OGLEDIT_ADD_SHAPE, this, info, m_childX, m_childY, false));

	m_childX += 10 ;
	m_childY += 10 ;
/////////
	//if(path.string() == "/") {
	if(parentHandle == bwAnyHandle) {
		SetRootItem(new BwxStateGraphItem(p_graph->GetAddedShape(),path.string().c_str(), handle)) ;
		p_layout->AddChild(p_graph->GetAddedShape(), path.string().c_str(), wxEmptyString) ;
		return ;
	}
	//else
	BwxStateGraphItem *idParent = NULL ;
	if(path.has_branch_path())
		idParent = m_itemMap[parentHandle] ;
	else
		idParent = GetRootItem() ;

	wxString str = path.leaf().c_str() ;
	BwxStateGraphItem * id = new BwxStateGraphItem(p_graph->GetAddedShape(),path.string().c_str(), handle) ;
	m_itemMap[handle] = id ;
	//
    GetCommandProcessor()->Submit(
	  new BwxGraphCommand(_T("wxLineShape"), arc.c_str(), handle, OGLEDIT_ADD_LINE, this, CLASSINFO(wxLineShape),
      0.0, 0.0, false, false, NULL, idParent->GetShape(), id->GetShape()));
	//
	p_layout->AddChild(id->GetShape(), path.string().c_str(), path.branch_path().string().c_str()) ;
}
void BwxStateGraphCtrl::OnSolution(bwHandle handle) {
	ColorState(handle, *wxRED) ;
}
void BwxStateGraphCtrl::OnFailed(bwHandle handle) {
	ColorState(handle, *wxLIGHT_GREY) ;
}
void BwxStateGraphCtrl::ColorState(bwHandle handle, const wxColour& colour) {
	BwxStateGraphItem * id = m_itemMap[handle] ;
	wxShape* theShape = id->GetShape() ;

    if (theShape)
    {
    wxColourData data;
    data.SetChooseFull(true);
    data.SetColour(theShape->GetBrush()->GetColour());
    wxBrush *theBrush = NULL;
    theBrush = wxTheBrushList->FindOrCreateBrush(colour, wxSOLID);
    if (theBrush)
        GetCommandProcessor()->Submit(new BwxGraphCommand(_T("Change colour"), OGLEDIT_CHANGE_BACKGROUND_COLOUR, this,
        theBrush, theShape));
    }
}
void BwxStateGraphCtrl::DoLayout() {
	wxClientDC dc(GetCanvas());
	p_layout->DoLayout(dc);

	long _x, _y ;
	p_layout->GetExtent(&_x, &_y) ;
	long scrollX = _x / 20 ;
	long scrollY = _y / 20 ;
	p_canvas->SetScrollbars(20, 20, scrollX, scrollY);
	p_graph->ShowAll(true) ;
	p_graph->Clear(dc) ;
	p_graph->Redraw(dc) ;
}
