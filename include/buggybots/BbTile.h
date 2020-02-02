/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbTile_H
#define _BbTile_H

#include <bwvr/VrBox.h>

class BbTile : public VrBox {
public:
	BbTile(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "BbTile" ; }
	//Data Members
};

#endif //_BbTile_H
