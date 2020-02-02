/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvrcegui/VrCeguiFolderMode.h>
#include <bwvrcegui/VrCeguiUser.h>
#include <bwvrcegui/VrCeguiControlPanel.h>
//
#include <bwvr/VrGroup.h>
//
#include <boost/filesystem/operations.hpp>
using namespace boost::filesystem;
//
VrCeguiPathMode::VrCeguiPathMode(VrCeguiUserMode* pParent, const bwPath& path) : VrCeguiUserMode(pParent, path.leaf().string()) {
	m_path = path ;
}
VrCeguiPathMode::~VrCeguiPathMode() {
}
//////////////////
VrCeguiFileMode::VrCeguiFileMode(VrCeguiUserMode* pParent, const bwPath& path) : VrCeguiPathMode(pParent, path) {
}
VrCeguiFileMode::~VrCeguiFileMode() {
}
//////////////////
VrCeguiFolderMode::VrCeguiFolderMode(VrCeguiUserMode* pParent, const bwPath& path) : VrCeguiPathMode(pParent, path) {
}
VrCeguiFolderMode::~VrCeguiFolderMode() {
}
void VrCeguiFolderMode::doCreate(const BwPartInfo& info) {
	VrCeguiUserMode::doCreate(info) ;
	const path & dir_path = m_path ;

	directory_iterator end_itr; // default construction yields past-the-end
	for ( directory_iterator itr( dir_path );
		itr != end_itr;
		++itr )
	{
		if ( is_directory( *itr ) )
		{
			createFolderMode(*itr) ;
		}
		else
		{
			createFileMode(*itr) ;
		}
	}

}
void VrCeguiFolderMode::createControlPanel() {
	VrCeguiUserMode::createControlPanel() ;
}
void VrCeguiFolderMode::destroyControlPanel() {
	VrCeguiUserMode::destroyControlPanel() ;
}
void VrCeguiFolderMode::activate() {
	VrCeguiUserMode::activate() ;
}
void VrCeguiFolderMode::deactivate() {
	VrCeguiUserMode::deactivate() ;
}
void VrCeguiFolderMode::createFileMode(const bwPath& path) {
	createMode(new VrCeguiFileMode(this, path)) ;
}
void VrCeguiFolderMode::createFolderMode(const bwPath& path) {
	createMode(new VrCeguiFolderMode(this, path)) ;
}
