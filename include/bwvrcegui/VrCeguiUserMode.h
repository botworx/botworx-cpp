/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiUserMode_H
#define _VrCeguiUserMode_H

#include <bwcore/BwPart.h>
//class VrUser ;
class VrCeguiUser ;
class VrCeguiWindow ;
class VrCeguiControlPanel ;

class VrCeguiUserMode ;
typedef std::list<VrCeguiUserMode*> VrCeguiUserModeContainer ;
typedef VrCeguiUserModeContainer::iterator VrCeguiUserModeIter ;

class VrCeguiUserMode : public BwPart {
public:
	VrCeguiUserMode(VrCeguiUserMode* pParent, const bwString& shortName) ;
	virtual ~VrCeguiUserMode() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void activate() ;
	virtual void deactivate() ;
	virtual void createControlPanel() ;
	virtual void destroyControlPanel() ;
	void createMode(VrCeguiUserMode *pMode) { pMode->create() ; }
	void addMode(VrCeguiUserMode *pMode) { m_modes.push_back(pMode) ; }
	VrCeguiControlPanel* getControlPanel() { return p_controlPanel ; }
	bwString getShortName() { return m_shortName ; }
	void setUser(VrCeguiUser *pUser) { p_user = pUser ; }
	VrCeguiUser& user() { return *getUser() ; }
	VrCeguiUser* getUser() { return p_user ; }
	/*Data Members*/
public:
	bwString m_shortName ;
	//VrUser *p_user ;
	VrCeguiUser *p_user ;
	VrCeguiUserMode *p_parent ;
	VrCeguiUserModeContainer m_modes ;
	VrCeguiControlPanel *p_controlPanel ;
};
//
#endif //_VrCeguiUserMode_H