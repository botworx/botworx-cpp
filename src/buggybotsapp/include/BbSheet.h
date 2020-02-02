/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbSheet_H
#define _BbSheet_H

#include <bwvrcegui/VrCeguiWindow.h>

//////////////////////////

class BbSheet : public VrCeguiWindow {
public:
	/*Data Members*/
	//////////////////
public:
    BbSheet(VrCeguiGui *pGui) ;
    virtual ~BbSheet() {
    }
};
#endif //_BbSheet_H