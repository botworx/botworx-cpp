/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbBunny_H
#define _BbBunny_H

#include <bwvr/VrConcaveMesh.h>

class BbBunny : public VrConcaveMesh {
public:
	BbBunny(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "BbBunny" ; }
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void generateMesh() ;
	//Data Members
};

#endif //_BbBunny_H
