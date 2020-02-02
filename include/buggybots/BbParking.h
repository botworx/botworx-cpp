/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbParking_H
#define _BbParking_H

#include <bwvr/VrPlace.h>

class BbParking : public VrPlace
{
public:
	BbParking(VrGroup *pGroup);
	virtual ~BbParking();
	virtual bool onCreate(const BwPartInfo& info) ;
	//
	void addRamps() ;
private:
};

#endif //_BbParking_H

