/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#ifndef _JrBody_H
#define _JrBody_H

#include <bwvr/VrBox.h>
class VrGroup ;

namespace Jr {

class Jr ;
class JrFactory ;

class JrBody : public VrBox {
public:
	JrBody(VrGroup *pGroup, Jr *pRoot) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createVu() ;
	virtual bwString getClassName() { return "JrBody" ; }
	virtual void createGeom() ;
	//virtual bool doStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	/*Data Members*/
	Jr *p_jr ;
} ;
}//end namespace Jr
#endif //_JrBody_H
