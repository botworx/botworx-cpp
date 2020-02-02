/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrGrayscaleQuadMap.h>
#include <bwvr/VrWorld.h>
#include <bwvr/VrQuadTree.h>

#include <bwvr/config/ogre.h>

void VrGrayscaleQuadMap::setPixelVertexRatio(int ratio) {
	m_pixelVertexRatio = ratio ;
}
void VrGrayscaleQuadMap::loadImage(std::string imageName){
	m_imageName = imageName ;
	p_image = new Ogre::Image();

    p_image->load(imageName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	m_size[0] = p_image->getWidth();
	m_size[1] = p_image->getHeight() ;

	m_bytesPerPixel = Ogre::PixelUtil::getNumElemBytes(p_image->getFormat ());
	bwAssert(m_bytesPerPixel == 1) ; //TODO:exception handling

	p_imageData = p_image->getData();

}
int VrGrayscaleQuadMap::getImageValue(const bwVector3& vector) {
	int pixelX = 0, pixelY = 0 ;
	int value = 0 ;
	bwReal tileUnit = p_tree->getTileUnit() ;
	//bwReal chunkSize = tileUnit * p_tree->getRowCount() ;
	pixelX = ((vector[0] / tileUnit) * m_pixelVertexRatio) + (m_size[0] * bwRealTraits::Half) ;
	//pixelX = vector[0] * m_pixelVertexRatio + (m_size[0] / 2) ;

	//pixelY = ((vector[2] / tileUnit) * m_pixelVertexRatio) + (m_size[2] / 2) ;
	pixelY = ((vector[2] / tileUnit) * m_pixelVertexRatio) + (m_size[0] * bwRealTraits::Half) ;
	//pixelY = vector[2] * m_pixelVertexRatio + (m_size[0] / 2) ;
	//int pixel = pixelX + (pixelY * m_size[1]) ;
	int pixel = pixelX + int(bwReal(pixelY) * m_size[0]) ;
	value = p_imageData[pixel] ;
	return value ;
}
void VrGrayscaleQuadMap::alter(VrQuadTree *pTree) {
	p_tree = pTree ;
	bwReal tileUnit = p_tree->getTileUnit() ;
	int rowCount = pTree->getRowCount() ;
	//m_pixelVertexRatio = m_size[0] / rowCount ;

	VrQuad *pQuadRow = pTree->getOuterQuad(VR_NW) ;
	VrQuad *pQuad = pQuadRow ;
	bwVector3 vector ;

	bwVector3 quadVector ;

	int rowCounter = 0, colCounter = 0 ;
	bwReal height = 0 ;
	while(pQuadRow != NULL) {
		while(pQuad != NULL) {
			quadVector = pQuad->getPos() ; //fixme
			vector[0] = quadVector[0] ;
			vector[1] = 0 ; //unknown still
			vector[2] = quadVector[2] ;
			height = bwReal( getImageValue(vector) / (double)(255+1) ) * m_scale ;
			vector[1] = height + quadVector[1] ; //y is defined by x & z

			pQuad->setPos(vector) ;

			pQuad = pQuad->p_east ;
			rowCounter = rowCounter + 1 ;
		}
		pQuad = pQuadRow = pQuadRow->p_south ;
		colCounter = colCounter + 1 ;
	}
}
