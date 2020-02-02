/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrSurfaceInfo_H
#define _VrSurfaceInfo_H

class VrSurfaceInfo {
public:
	VrSurfaceInfo() ;
	virtual ~VrSurfaceInfo() ;
	void setMode(int mode) {m_mode = mode ; }
	int getMode() { return m_mode ; }
	void setMu(bwReal value) {m_mu = value ; }
	bwReal getMu() { return m_mu ; }
	bwReal getMuAdjusted() { 
		bwReal adjustedMu = m_mu * bwRealTraits::PosInfinity ;
		if(adjustedMu > bwRealTraits::PosInfinity)
			adjustedMu = bwRealTraits::PosInfinity ;
		return adjustedMu ;
	}
	bwReal getSecondMuAdjusted() { 
		bwReal adjustedMu = m_secondMu * bwRealTraits::PosInfinity ;
		if(adjustedMu > bwRealTraits::PosInfinity)
			adjustedMu = bwRealTraits::PosInfinity ;
		return adjustedMu ;
	}
	void setSecondMu(bwReal value) { m_secondMu = value ; }
	bwReal getSecondMu() { return m_secondMu ; }
	void setBounce(bwReal value) {m_bounce = value ; }
	bwReal getBounce() { return m_bounce ; }
	void setBounceVel(bwReal value) {m_bounceVel = value ; }
	bwReal getBounceVel() { return m_bounceVel ; }
	//
	void setFirstFrictionDir(const bwVector3& frictionDir) { m_firstFrictionDir = frictionDir ; }
	bwVector3 getFirstFrictionDir() { return m_firstFrictionDir ; }
protected:
	/*Data Members*/
protected:
	int m_mode ;
	bwReal m_mu ;
	bwReal m_secondMu ;
	bwReal m_bounce ;
	bwReal m_bounceVel ;
	bwVector3 m_firstFrictionDir ;
} ;

#endif //_VrSurfaceInfo_H