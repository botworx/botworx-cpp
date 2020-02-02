/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiFolderMode_H
#define _VrCeguiFolderMode_H

#include <bwvrcegui/VrCeguiUserMode.h>

class VrCeguiPathMode : public VrCeguiUserMode {
public:
	VrCeguiPathMode(VrCeguiUserMode* pParent, const bwPath& path) ;
	virtual ~VrCeguiPathMode() ;
	//Data Members
	bwPath m_path ;
} ;
///////////
class VrCeguiFileMode : public VrCeguiPathMode {
public:
	VrCeguiFileMode(VrCeguiUserMode* pParent, const bwPath& path) ;
	virtual ~VrCeguiFileMode() ;
} ;
///////////
class VrCeguiFolderMode : public VrCeguiPathMode {
public:
	VrCeguiFolderMode(VrCeguiUserMode* pParent, const bwPath& path) ;
	virtual ~VrCeguiFolderMode() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void activate() ;
	virtual void deactivate() ;
	virtual void createControlPanel() ;
	virtual void destroyControlPanel() ;
	//
	virtual void createFileMode(const bwPath& path) ;
	virtual void createFolderMode(const bwPath& path) ;
	/*Data Members*/
public:
};
//
#endif //_VrCeguiFolderMode_H