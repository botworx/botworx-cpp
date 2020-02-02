#ifndef _BwcImporter_H
#define _BwcImporter_H

#include <bwcore/BwPart.h>

class VrGroup ;
class BwcReader ;

class BwcImporter : public BwPart {
public:
	BwcImporter(BwPart* pOwner, VrGroup* pGroup, const bwString& name) ;
	void import(const bwPath& path) ;
	//Data Members
	BwcReader* p_reader ;
	VrGroup* p_rootGroup ;
} ;

#endif //_BwcImporter_H