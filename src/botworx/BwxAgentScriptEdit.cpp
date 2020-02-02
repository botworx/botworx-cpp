#include "stdafx.h"

#include <bwbotworx/BwxAgentScriptEdit.h>
#include <bwbotworx/BwxContext.h>

#include <bwdocument/BwDocClient.h>
#include <bwdocument/_BwDocument.h>
using namespace _BwDocument ;

class BwxAgentScriptEdit ;

namespace _BwxAgentScriptEdit {
class MyClient : public BwDocClient {
public:
	MyClient(BwxAgentScriptEdit *pOwner) : p_edit(pOwner) {}
	virtual void onEvent(const BwMessage& msg) {
		//bwAssert(0) ;
		switch(msg.what()) {
			case EVENT_OPEN : {
				bwString filename ;
				msg()->findString("FILENAME", filename) ;
				p_edit->LoadFile(filename.c_str()) ;
							  }
				break ;
			case EVENT_SAVE :
				break ;
			case EVENT_CLOSE :
				break ;
		}
		BwDocClient::onEvent(msg) ;
	}
	//
	BwxAgentScriptEdit *p_edit ;
};
} ; //namespace BwxAgentScriptEdit
using namespace _BwxAgentScriptEdit ;

BwxAgentScriptEdit::BwxAgentScriptEdit(wxWindow *parent, const BwxContext& context)
		: wxStyledTextCtrl(parent)
{
    m_container = parent ;
	p_client = new MyClient(this) ;
	p_client->create() ;
	p_client->connect(context.getDocSession()) ;
}
