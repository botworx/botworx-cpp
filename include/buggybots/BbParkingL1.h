/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbParkingL1_H
#define _BbParkingL1_H

#include <bwvr/VrPlace.h>

class BbParkingL1 : public VrPlace
{
public:
	BbParkingL1(VrGroup *pGroup);
	virtual ~BbParkingL1();
	virtual bool onCreate(const BwPartInfo& info) ;
private:
	void addTiles() ;
};

#endif //_BbParkingL1_H

