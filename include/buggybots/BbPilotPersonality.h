#ifndef _BbPilotPersonality_H
#define _BbPilotPersonality_H

#include "BbPersonality.h"
#include "BbPilotBrain.h"

class BbPilotPersonality : public BbPersonality {
public:
	BbPilotPersonality(BbPilotBrain* pBrain) : BbPersonality(pBrain) {
		m_isStaticAvoiding = false ;
		m_isDynamicAvoiding = false ;
	}
	BbPilotBrain& brain() { return *static_cast<BbPilotBrain*>(getBrain()) ; }
	BbSteer::BbPilot& pilot() { return *getPilot() ; }
	BbSteer::BbPilot* getPilot() { return brain().getPilot() ; }
	//
	void setIsStaticAvoiding(bool val) { m_isStaticAvoiding = val ; }
	bool isStaticAvoiding() { return m_isStaticAvoiding ; }
	void setIsDynamicAvoiding(bool val) { m_isDynamicAvoiding = val ; }
	bool isDynamicAvoiding() { return m_isDynamicAvoiding ; }
	bool isAvoiding() { return m_isStaticAvoiding || m_isDynamicAvoiding ; }
	//Data Members
	bool m_isStaticAvoiding ;
	bool m_isDynamicAvoiding ;
} ;

#endif //_BbPilotPersonality_H
