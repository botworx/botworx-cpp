/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrBodyInfo_H
#define _VrBodyInfo_H

//TODO:and implement something more Bw like.
class VrBodyInfo {
public:
	VrBodyInfo() ;
	void zero() { dMassSetZero (&m_dMass) ; }
	// VrBodyInfo(const VrBodyInfo& src) { memcpy(this, &src, sizeof(this)) ; }
	bwReal add(const VrBodyInfo& m2) {
		if(m2.m_dMass.mass != 0) dMassAdd(&m_dMass, &m2.m_dMass) ;
		return getMass() ;
	}
	void translate(const bwPoint3& point) ;
	void rotate(const bwQuat& quat) ;
	//
	void setSphere(bwReal radius) ;
	void setBox(const bwSize3& size) ;
	void setCapsule(const bwSize3& size) ;
	//Density
	void setSolidity(bwReal solidity) { m_solidity = solidity ; }
	bwReal getSolidity() { return m_solidity ; }
	void setDensity(bwReal density) ;
	bwReal getDensity() { return m_density ; }
	bwReal getDensityMin() const { return DENSITY_MIN ; }
	bwReal getDensityMax() const { return DENSITY_MAX ; }
	bwReal getDensityDefault() const { return DENSITY_DEFAULT ; }
	void setInvDensity(bwReal density) ;
	bwReal getInvDensity() { return m_invDensity ; }
	//Mass
	void setCenter(const bwPoint3& point) {
		m_dMass.c[0] = point[0] ; m_dMass.c[1] = point[1] ; m_dMass.c[2] = point[2] ; 
	}
	bwPoint3 getCenter() { return bwPoint3( m_dMass.c[0], m_dMass.c[1], m_dMass.c[2]) ; }
	void _setMass(bwReal mass) { m_dMass.mass = mass ; }
	void setMass(bwReal mass) ;
	bwReal getMass() const { return m_dMass.mass ; } //use ODE mass ...
	void setInvMass(bwReal mass) ;
	bwReal getInvMass() { return m_invMass ; }
	bwReal getMassMin() const { return MASS_MIN ; }
	bwReal getMassMax() const { return MASS_MAX ; }
	bwReal getMassDefault() const { return MASS_DEFAULT ; }
	//??? needed to go somewhere ... seemed weird in VrModel proper.
	void setDrag(bwReal val) { m_linearDrag = m_angularDrag = val ; }
	bwReal getDragDefault() { return DRAG_DEFAULT ; }
	void setLinearDrag(bwReal val) { m_linearDrag = val ; }
	bwReal getLinearDrag() { return m_linearDrag ; }
	void setAngularDrag(bwReal val) { m_angularDrag = val ; }
	bwReal getAngularDrag() { return m_angularDrag ; }
	//
	//Data Members
	static const bwReal DENSITY_MIN ;
	static const bwReal DENSITY_MAX ;
	static const bwReal DENSITY_DEFAULT ;
	dMass m_dMass ;
	bwReal m_solidity ;
	bwReal m_density ;
	bwReal m_invDensity ;
	static const bwReal MASS_MIN ;
	static const bwReal MASS_MAX ;
	static const bwReal MASS_DEFAULT ;
	//bwReal m_mass ;
	bwReal m_invMass ;
	//
	static const bwReal DRAG_DEFAULT ;
	bwReal m_linearDrag ;
	bwReal m_angularDrag ;
} ;

#endif //_VrBodyInfo_H