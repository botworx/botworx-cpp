/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _Character_H
#define _Character_H

#include <bwvr/VrDynamicAssembly.h>
#include "CharacterBrain.h"

class BbScanner ;

namespace Character {

class CharacterBody ;

class Character : public VrDynamicAssembly {
public:
	Character(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "Character" ; }
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createBrain() ;
	virtual void createVu() ;
	//
	CharacterBody* getChassis() { return p_chassis ; }
	BbScanner* getScanner() { return p_scanner ; }
	//
	CharacterBrain& brain() { return *static_cast<CharacterBrain*>(getBrain()) ; }
	void setUsesScanner(bool val) { m_usesScanner = val ; }
	bool usesScanner() { return m_usesScanner ; }
	//Data Members
protected:
	//
	CharacterBody* p_chassis ;
	BbScanner* p_scanner ;
	bool m_usesScanner ;
};
//
//CharacterFactory
//
class CharacterFactory : public VrModelFactory {
public:
	CharacterFactory(BwKit *pKit) ;
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) ;
	//Data Members
	VrVuInfo m_vuInfo ;
} ;

} //namespace Character {
#endif //_Character_H
