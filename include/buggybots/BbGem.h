/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbGem_H
#define _BbGem_H

#include <bwvr/VrConvexMesh.h>
//
//BbGem
//
class BbGem : public VrConvexMesh {
public:
	BbGem(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "BbGem" ; }
	/*Data Members*/
};
//
//BbGemFactory
//
#include <bwvr/VrModelFactory.h>

class BbGemFactory : public VrModelFactory {
public:
	BbGemFactory (BwKit *pKit) : VrModelFactory(pKit) {
		setName("Gem") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		BbGem *pGem = new BbGem(pGroup) ;
		pGem->setFactory(this) ;
		pGem->setSize(.5, .5, .5) ;
		pGem->create(style) ;
		return pGem ; 
	}
} ;

#endif //_BbGem_H