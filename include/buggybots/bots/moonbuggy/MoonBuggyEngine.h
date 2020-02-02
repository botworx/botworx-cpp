#ifndef _BUGGYENGINE_H
#define _BUGGYENGINE_H

#include <bwvr/VrMotor.h>
#include <bwvr/VrMech.h>

namespace MoonBuggy {
class BuggyEngine : public VrMotor {
public:
	BuggyEngine(VrMech *pMech) ;
	void setPower(bwReal power) ;
};
}//end namespace BwVr::Bots::MoonBuggy
#endif //_BUGGYENGINE_H