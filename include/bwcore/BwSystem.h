/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwSystem_H
#define _BwSystem_H

#include "BwKit.h" 
#include <bwmessaging/BwMessage.h>

class BwMailSlot ;

class BwSystem : public BwKit {
public:
	BwSystem(BwPart *pPart) ;
	~BwSystem() ;
} ;

#endif //_BwSystem_H
