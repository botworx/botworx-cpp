#ifndef _BwxMindTv_H
#define _BwxMindTv_H

#include "BwxTv.h"

class BwxMindVid ;

class BwxMindTv : public BwxTv
{
public:
    BwxMindTv(wxWindow *parent, const BwxContext& context) ;
	//
	//virtual BwxVid* CreateVid(wxWindow *parent, const BwxContext& context, const bwString& name) ;
	virtual BwxVid* CreateVid(wxWindow *parent, const BwxContext& context, bwHandle = bwAnyHandle) ;
	//Data Members
};

#endif //_BwxMindTv_H
