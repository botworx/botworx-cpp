// TestChatWx.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <bwbotworx/BwxContext.h>
#include <bwbotworx/BwxMindTv.h>
#include <bwbotworx/BwxMindVid.h>

#include <bwapplet/BwAppletClient.h>
#include <bwagency/BwAgentClient.h>

#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;

#include <bwbotworx/_BwxAgentApplet.h>
using namespace _BwxAgentApplet ;

namespace _BwxMindTv {
class MyAppletClient : public BwAppletClient {
public:
	MyAppletClient(BwxMindTv *pOwner) : p_edit(pOwner) {}
	virtual void onEvent(const BwMessage& msg) {
		//bwAssert(0) ;
		switch(msg.what()) {
			case EVENT_STATE_SELECTED : {
				bwHandle handle ;
				msg()->findHandle("HANDLE", handle) ;
				p_edit->ChangeVid(handle) ;
			}
			break ;
		}
		BwAppletClient::onEvent(msg) ;
	}
	//
	BwxMindTv *p_edit ;
};
class MyAgentClient : public BwAgentClient {
public:
	MyAgentClient(BwxMindTv *pOwner) : p_owner(pOwner) {}
	virtual bwString getClassName() { return "MyAgentClient" ; }
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwxMindTv *p_owner ;
};
void MyAgentClient::onEvent(const BwMessage& msg) {
	switch(msg.what()) {
		case EVENT_STATE_ADDED : {
			bwHandle handle ;
			msg()->findHandle("HANDLE", handle) ;
			p_owner->AddVid(handle) ;
		}
			break ;
	}
	BwAgentClient::onEvent(msg) ;
}
} //end namespace _BwxMindTv
using namespace _BwxMindTv ;

BwxMindTv::BwxMindTv(wxWindow *parent, const BwxContext& context)
	: BwxTv(parent, context) {
   	p_appletClient = new MyAppletClient(this) ;
	p_appletClient->create() ;
	p_appletClient->connect(context.getAppletSession()) ;
	//
   	p_agentClient = new MyAgentClient(this) ;
	m_context.setAgentClient(p_agentClient) ;
	p_agentClient->create() ;
	p_agentClient->connect(context.getAgentSession()) ;
	//
	p_vid = NULL ;
	p_drawer = new wxPanel(this) ;
	p_drawer->Show(false) ;

	p_sizer = new wxBoxSizer( wxVERTICAL );
	SetSizer( p_sizer);
    SetAutoLayout( true );
}
BwxVid* BwxMindTv::CreateVid(wxWindow *pParent, const BwxContext& context, bwHandle handle) {
	BwxMindVid *pVid = new BwxMindVid(pParent, m_context, handle) ;
	pVid->SetIsShared(true) ; //set to false if you want one vid per state!
	return pVid ;
}
