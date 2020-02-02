/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwTaskFactory_H
#define _BwTaskFactory_H

#include <bwcore/BwFactory.h>

class BwTask ;
class BwBrain ;

class BwTaskFactory : public BwFactory {
public:
	BwTaskFactory(BwPart* pOwner, BwKit *pKit = nullptr) : BwFactory(pOwner, pKit) {}
	virtual BwTask* produce(BwBrain *pBrain) { return nullptr ; }
public:
	//Data
} ;

typedef std::list<BwTaskFactory*> BwTaskFactoryContainer ;
typedef BwTaskFactoryContainer::iterator BwTaskFactoryIter ;
typedef std::map<std::string, BwTaskFactory*> BwTaskFactoryMap ;

#endif //_BwTaskFactory_H
