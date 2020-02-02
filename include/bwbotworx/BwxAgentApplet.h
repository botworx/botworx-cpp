/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BwxAgentApplet_H
#define _BwxAgentApplet_H

#include "BwxApplet.h"

class BwxAgentApplet : public BwxApplet {
public:
	BwxAgentApplet();
	virtual ~BwxAgentApplet();
};
#include <bwapplet/BwAppletSession.h>
//f6:fixme:need BwAppletSessionT to avoid casting? Like factories.
class BwxAgentAppletSession : public BwAppletSession {
public:
	virtual BwApplet* produce() { return new BwxAgentApplet() ; }
} ;

#endif

