#include "stdafx.h"

#include <bwmessaging/BwMailSlot.h>
#include <bwmessaging/BwCmd.h>

#include <bwagency/BwAgent.h>
#include <bwagency/BwAgentClient.h>

#include <bwbotworx/BwxAgentDoc.h>
#include <bwbotworx/BwxAgentView.h>

class BwxAgentConsole ;

class BwxAgentDocClient : public BwAgentClient {
public:
	BwxAgentDocClient(BwxAgentDoc *pOwner) : p_doc(pOwner) {}
	virtual bwString getClassName() { return "BwxAgentDocClient" ; }
	//Data Members
	BwxAgentDoc *p_doc ;
};
///////////
IMPLEMENT_DYNAMIC_CLASS(BwxAgentDoc, wxDocument)
BwxAgentDoc::BwxAgentDoc(void) {
	p_client = NULL ;
}
BwxAgentDoc::~BwxAgentDoc(void) {
}
/*This is very strange wxWidgets calls OnClose for New Docs and 
calls it twice when the main frame goes down!!!*/
bool BwxAgentDoc::OnCloseDocument() {
	if(!m_isNew && !m_isClosed) {
		p_client->close() ;
	}
	return BwxDocument::OnCloseDocument() ;
}
BwSession* BwxAgentDoc::getAgentSession() { 
	return p_client->getSession() ; 
}
void  BwxAgentDoc::createSession() {
	p_client = new BwxAgentDocClient(this) ;
	p_client->create() ;
	BwMessage params ;
	//p_client->createAsyncAgent(AGENT_DEFAULT, "MyAgent", params) ;
	if(!isRemote())
		p_client->createAgent(AGENT_DEFAULT, "MyAgent", params) ;
	else
		p_client->createRemoteAgent(AGENT_DEFAULT, "MyAgent", params) ;
}
bool  BwxAgentDoc::OnCreate(const wxString& path, long flags) {
	createSession() ;
	return BwxDocument::OnCreate(path, flags) ;
}
/* windoze
bwString convert_path(LPCTSTR pPath) {
	bwString path ;
	char c ;
	while( (c = *pPath++) ) {
		if(c == '\\')
			c = '/' ;
		path += c ;
	}
	return path ;
} */
bwString extract_name(bwString path) {
	bwString name ;
	size_t length = path.length() ;
	size_t i = length ;
	for(; path.at(i) != '.' ; i--) ;
	size_t j = i ;
	for(; path.at(j) != '/' ; j--) ;
	for(size_t z = j + 1; z < i ; ++z) 
		name += path.at(z) ;
	return name ;
}
bool BwxAgentDoc::OnNewDocument() {
	return BwxDocument::OnNewDocument() ;
}
bool BwxAgentDoc::OnOpenDocument(const wxString& filename)
{
    BwxAgentView *view = (BwxAgentView *)GetFirstView();
    SetFilename(filename, true);
	wxString pathOnly =  wxPathOnly(filename) ;
	wxString fileNameOnly = wxFileNameFromPath(filename) ;
	//looks like LUA is stripping out the slashes ... use convert_path
	//or just use linux/unix :)
	BwCmd dirCmd("chdir") ;
	if(!pathOnly.IsNull())
		//p_client->doCommand(dirCmd << quote << convert_path(pathOnly.GetData()) << endq ) ;
		p_client->doCommand(dirCmd << quote << bwString(pathOnly.GetData()) << endq ) ;

	BwCmd loadCmd("load") ;
	p_client->doCommand(loadCmd << quote << fileNameOnly.ToStdString() << endq ) ;

	UpdateAllViews();

	return BwxDocument::OnOpenDocument(filename) ;
}