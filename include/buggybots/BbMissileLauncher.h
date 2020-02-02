/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbMissileLauncher_H
#define _BbMissileLauncher_H

#include <bwvr/VrGroup.h>
#include "BbGun.h"

class BbMissileLauncher : public BbGun {
public:
	BbMissileLauncher(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "BbMissileLauncher" ; }
	//
	virtual void onTrigger() ;
	/*Data Members*/
private:
	int m_inst_counter ; //instantiation counter for creating indices / name gen
};

#endif //_BbMissileLauncher_H
