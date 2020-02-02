/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwxUserMode_H
#define _BwxUserMode_H

#include <bwkernel/BwPart.h>

class BwxUser ;
class BwxCard ;
class BwxDeckFrame ;

class BwxUserMode ;
typedef std::deque<BwxUserMode*> BwxUserModeCollection ;
typedef std::deque<BwxUserMode*>::iterator BwxUserModeIter ;

class BwxUserMode : public BwPart {
public:
	BwxUserMode(BwxUserMode* pParent, bwString shortName) ;
	virtual ~BwxUserMode() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void activate() ;
	virtual BwxCard* createControlPanel(BwxDeckFrame *pFrame) ;
	void createMode(BwxUserMode *pMode) { pMode->create() ; }
	void addMode(BwxUserMode *pMode) { m_modes.push_back(pMode) ; }
	BwxCard* getControlPanel() { return p_controlPanel ; }
	bwString getName() { return m_name ; }
	bwString getShortName() { return m_shortName ; }
	void setUser(BwxUser *pUser) { p_user = pUser ; }
	BwxUser* getUser() { return p_user ; }
	/*Data Members*/
public:
	bwString m_name ;
	bwString m_shortName ;
	int m_state ;
	BwxUser *p_user ;
	BwxUserMode *p_parent ;
	BwxUserModeCollection m_modes ;
	BwxCard *p_controlPanel ;
	bool m_success ;
	bool m_isBusy ;
};
//
#endif //_BwxUserMode_H