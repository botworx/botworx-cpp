/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwStepper_H
#define _BwStepper_H

class BwStepper {
public:
	BwStepper();
	virtual ~BwStepper();
	void setCurrentTime(bwDT deltaTime) { m_currentTime = deltaTime ; }
	bwDT getCurrentTime() { return m_currentTime ; }
	void setDeltaTime(bwDT deltaTime) { 
		m_deltaTime = deltaTime ; 
		if (deltaTime > 0.0f)
			m_invDt = 1.0f / deltaTime ;
		else
			m_invDt = 1.0e-30f ;
	}
	bwDT getDeltaTime() { return m_deltaTime ; }
	bwDT getInvDt() { return m_invDt ; }
	//Data Members
	bwDT m_currentTime ;
	bwDT m_deltaTime ;
	bwDT m_invDt ;
};

#endif //_BwStepper_H

