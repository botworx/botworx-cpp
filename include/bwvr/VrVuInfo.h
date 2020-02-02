/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrVuInfo_H
#define _VrVuInfo_H

class VrVuInfo {
public:
	VrVuInfo() : m_isAutoScaler(true) {}
	void setMeshName(const bwString& name) { m_meshName = name ; }
	const bwString& getMeshName() { return m_meshName ; }
	void setMeshSize(const bwSize3& size) { m_meshSize = size ; }
	const bwSize3& getMeshSize() { return m_meshSize ; }
	void setMaterialName(const bwString& name) { m_materialName = name ; }
	const bwString& getMaterialName() { return m_materialName ; }
	//
	void setSkeletonName(const bwString& name) { m_skeletonName = name ; }
	const bwString& getSkeletonName() { return m_skeletonName ; }
	//Offsets
	void setMeshPos(const bwPoint3& pos) { m_meshPos = pos ; }
	const bwPoint3& getMeshPos() { return m_meshPos ; }
	void setMeshQuat(const bwQuat& quat) { m_meshQuat = quat ; }
	const bwQuat& getMeshQuat() { return m_meshQuat ; }
	//
	void setIsAutoScaler(bool val) { m_isAutoScaler = val ; }
	bool getIsAutoScaler() { return m_isAutoScaler ; }
	//Data Members
	bwString m_meshName ;
	bwSize3 m_meshSize ;
	bwString m_materialName ;
	//
	bwString m_skeletonName ;
	bwPoint3 m_meshPos ;
	bwQuat m_meshQuat ;
	//
	bool m_isAutoScaler ;
} ;

#endif //_VrVuInfo_H