/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcore/BwFactory.h>

BwFactory::BwFactory(BwPart* pOwner, BwKit *pKit) : BwPart(pOwner) {
	p_kit = pKit ;
	m_serialCounter = 0 ;
}
void* BwFactory::rent(size_t size) {
	bwAssert(size != 0) ;
	void *object = nullptr ;
	if(p_kit != nullptr) {
		object =  p_kit->rent(size) ;
		bwAssert(object != nullptr) ;
		return object ;
	}
	//else
	//return ::malloc(size) ;
	return BW_MALLOC(size) ;
}
void BwFactory::release(void *pCell) {
	bwAssert(pCell != nullptr) ;
	if(p_kit != nullptr)
		p_kit->release(pCell) ;
	else
		//::free(pCell) ;
		BW_FREE(pCell) ;
}
