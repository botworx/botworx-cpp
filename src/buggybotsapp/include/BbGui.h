/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbGui_H
#define _BbGui_H

#include <bwvrcegui/VrCeguiGui.h>
//
//BbGui
//
class BbGui : public VrCeguiGui {
public:
    BbGui(VrScene *pScene) ;
    virtual ~BbGui() ;
    virtual void doCreate(const BwPartInfo& info) ;
};

#endif //_BbGui_H