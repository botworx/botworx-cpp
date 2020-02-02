/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbEnergy_H
#define _BbEnergy_H

#include <bwvr/VrBall.h>
//
//BbEnergy
//
class BbEnergy : public VrBall {
public:
	BbEnergy(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "BbEnergy" ; }
	/*Data Members*/
};
//
//BbEnergyFactory
//
#include <bwvr/VrModelFactory.h>

class BbEnergyFactory : public VrModelFactory {
public:
	BbEnergyFactory (BwKit *pKit) : VrModelFactory(pKit) {
		setName("Energy") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) ;
} ;

#endif //_BbEnergy_H
