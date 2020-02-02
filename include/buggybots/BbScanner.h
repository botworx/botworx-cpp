/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbScanner_H
#define _BbScanner_H

#include <bwvr/VrRay.h>

class BbScanner : public VrRay {
public:
	BbScanner(VrGroup *pGroup) ;
	virtual void createVu() ;
	virtual void createCollider() ;
	virtual bwString getClassName() { return "BbScanner" ; }
	virtual bool onPostStep(BwStepper& stepper) ;
	/*Data Members*/
};

#endif //_BbScanner_H
