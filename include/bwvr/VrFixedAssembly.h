/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrFixedAssembly_H
#define _VrFixedAssembly_H

#include "VrAssembly.h"
#include "VrShape.h"

class VrFixedAssembly : public VrAssembly {
public:
	VrFixedAssembly(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrFixedAssembly" ; }
	virtual void createBody() ;
	virtual void onModelAddition(VrModel *pModel) ;
	virtual void onLayout() ;
	//Data Members
};

#endif //_VrFixedAssembly_H
