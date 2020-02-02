/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrTracer.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrBody.h>

VrModel& VrTracer::model() { 
	VrModel *pModel = ((VrModel*)((bwByte*)this - offsetof(VrModel, m_tracer))) ;
	return *pModel ;
}
VrGroup* VrTracer::getGroup() { return model().getGroup() ; }
VrBody* VrTracer::getBody() { return model().getBody() ; }
//
VrTracer::~VrTracer() {
}
void VrTracer::validate() {
}
