#ifndef _BwxMindExplorer_H
#define _BwxMindExplorer_H

#include "BwxVid.h"

class BwxMindTreeCtrl ;

class BwAgentClient ;
class BwAgentSession ;

class BwxMindExplorer : public BwxVid {
public:
	BwxMindExplorer(wxWindow *parent, const BwxContext& context) ;
	virtual ~BwxMindExplorer() ;
	//Data Members
	BwxMindTreeCtrl *m_treeCtrl ;
	//
	DECLARE_EVENT_TABLE()
} ;


#endif// _BwxMindExplorer_H
