/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbProjection_H
#define _BbProjection_H

#include <bwvr/VrTetrahedron.h>

class BbProjection : public VrTetrahedron {
public:
	BbProjection(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "BbProjection" ; }
	virtual void createVu() ;
	//Data Members
};

#endif //_BbProjection_H
