/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"
#include <bwvr/VrGear.h>

VrGear::VrGear(BwPart *pOwner, VrRod *pRod, bwReal radius) : VrRod(pOwner) {
	p_rod = pRod ;
	m_radius = radius ;
}
VrGear* VrGear::addGear(VrRod *pRod, bwReal radius) {
	m_gears.push_front(new VrGear(this, pRod, radius)) ;
	return *(m_gears.begin()) ;
}
void VrGear::setAngle(bwReal value) {
	VrRod::setAngle(value) ;

	if(p_rod != NULL)
		p_rod->setAngle(value) ;

	if(m_gears.empty())
		return ;
	//else
	for (VrGearContainer::iterator iter = m_gears.begin();
			iter != m_gears.end(); ++iter)	{
		(*iter)->setAngle(value) ;
	}
}
void VrGear::setVelocity(bwReal value) {
	VrRod::setVelocity(value) ;
	if(p_rod != NULL)
		p_rod->setVelocity(value) ;

	if(m_gears.empty())
		return ;
	//else
	for (VrGearContainer::iterator iter = m_gears.begin();
			iter != m_gears.end(); ++iter)	{
		(*iter)->setVelocity(value) ;
	}
}
void VrGear::setForceMax(bwReal value) {
	VrRod::setForceMax(value) ;
	if(p_rod != NULL)
		p_rod->setForceMax(value) ;

	if(m_gears.empty())
		return ;
	//else
	for (VrGearContainer::iterator iter = m_gears.begin();
			iter != m_gears.end(); ++iter)	{
		(*iter)->setForceMax(value) ;
	}
}
void VrGear::addTorque(bwReal value) {
	VrRod::addTorque(value) ;
	if(p_rod != NULL)
		p_rod->addTorque(value) ;

	if(m_gears.empty())
		return ;
	//else
	for (VrGearContainer::iterator iter = m_gears.begin();
			iter != m_gears.end(); ++iter)	{
		(*iter)->addTorque(value) ;
	}
}