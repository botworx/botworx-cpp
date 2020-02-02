/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrGrayscaleQuadMap_H
#define _VrGrayscaleQuadMap_H

#include "VrQuadMap.h"

namespace Ogre {
	class Image ;
}

class VrGrayscaleQuadMap : public VrQuadMap {
public:
	void loadImage(std::string imageName) ;
	virtual void alter(VrQuadTree *pTree) ;
	int getImageValue(const bwVector3& vector) ;
	void setPixelVertexRatio(int ratio) ;
	//Data
public:
	std::string m_imageName ;
	Ogre::Image *p_image ;
	unsigned char *p_imageData ;
	bwSize2 m_size ;
	int m_bytesPerPixel ;
	bwReal m_pixelVertexRatio ;
};

#endif //_VrGrayscaleQuadMap_H