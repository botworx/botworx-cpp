#ifndef _BUGGYENGINE_H
#define _BUGGYENGINE_H

#include <bwvr/VrMotor.h>
#include <bwvr/VrMech.h>

namespace Jr {
class JrEngine : public VrMotor {
public:
	JrEngine(VrMech *pMech) ;
	void setPower(bwReal power) ;
};
}//end namespace BwVr::Bots::Jr
#endif //_BUGGYENGINE_H