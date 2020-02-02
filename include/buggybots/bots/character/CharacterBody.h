/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _CharacterBody_H
#define _CharacterBody_H

#include <bwvr/VrBox.h>
//#include <bwvr/VrCapsule.h>
namespace Character {

class CharacterBody : public VrBox {
//class CharacterBody : public VrCapsule {
public:
	CharacterBody(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "CharacterBody" ; }
	virtual void createBody() ;
	//Data Members
};

} //namespace Character

#endif //_CharacterBody_H
