/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbControlFrame_H
#define _BbControlFrame_H

#include <bwvrcegui/VrCeguiControlFrame.h>

//////////////////////////

class BbControlFrame : public VrCeguiControlFrame {
public:
	/*Data Members*/
	//////////////////
public:
    BbControlFrame(VrCeguiGui *pGui) ;
    virtual ~BbControlFrame() {
    }
};
#endif //_BbControlFrame_H