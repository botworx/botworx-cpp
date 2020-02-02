/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrQuadMap_H
#define _VrQuadMap_H

class VrQuadTree ;

class VrQuadMap {
public:
	virtual void alter(VrQuadTree *pTree) {}
	void setScale(bwReal scale) { m_scale = scale ; }
	//Data
public:
	VrQuadTree *p_tree ;
	bwReal m_scale ;
};

#endif //_VrQuadMap_H