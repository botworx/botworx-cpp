/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _JrChassis_H
#define _JrChassis_H

#include <bwvr/VrFixedAssembly.h>

namespace Jr {
class Jr ;
class JrFactory ;
class JrBrain ;
class JrEngine ;
class JrBody ;
class JrWheel ;

class JrChassis : public VrFixedAssembly {
public:
	JrChassis(Jr *pJr) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bwString getClassName() { return "JrChassis" ; }
	JrBody* getJrBody() { return p_jrBody ; }
	/*Data Members*/
	Jr *p_jr ;
	JrBody *p_jrBody ;
};
}//end namespace Jr

#endif //_JrChassis_H
