/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

BwPart::BwPart(BwPart *pParent) {
	p_owner = pParent ;
	p_factory = nullptr ;
	m_serial = 0 ;
	m_handle = bwAnyHandle ;
	m_isInitialised = false ;
	m_isConfigured = false ;
	m_isEnabled = false ;
	m_isOperational = false ;
}
BwPart::~BwPart() {
}
bool BwPart::create(const BwPartInfo& info) {
	bwAssert(!m_isInitialised) ;
	doCreate(info) ;
	return onCreate(info) ;
}
void BwPart::config() {
	doConfig() ;
	doPostConfig() ;
}
void BwPart::enable(bool sleeping) {
	doEnable(sleeping) ;
	doPostEnable(sleeping) ;
}
void BwPart::disable(bool sleeping) {
	doDisable(sleeping) ;
	doPostDisable(sleeping) ;
}
void BwPart::doCreate(const BwPartInfo& info) {
	bwAssert(!m_isInitialised) ;
	//bwAssert(p_factory != nullptr) ;
}
bool BwPart::onCreate(const BwPartInfo& info) {
	return m_isInitialised = true ;
}
void BwPart::doConfig() {
	bwAssert(!m_isConfigured) ;
}
void BwPart::doPostConfig() {
	m_isConfigured = true ;
	onConfig() ;
}
void BwPart::doEnable(bool sleeping) {
	//bwAssert(!m_isEnabled) ;
}
void BwPart::doPostEnable(bool sleeping) {
	m_isEnabled = !sleeping ;
	if(!m_isOperational)
		m_isOperational = true ;
	onEnable(sleeping) ;
}
void BwPart::doDisable(bool sleeping) {
	//bwAssert(m_isEnabled) ;
}
void BwPart::doPostDisable(bool sleeping) {
	m_isEnabled = !sleeping ;
	if(!sleeping) {
		m_isOperational = false ;
	}
	onDisable(sleeping) ;
}

///////
void BwPart::createAndConfig() {
	create() ;
	config() ;
}
void BwPart::configAndEnable() {
	config() ;
	enable() ;
}
void BwPart::createEnabled() {
	create() ;
	config() ;
	enable() ;
}
void BwPart::setFactory(BwFactory *pFactory) {
	bwAssert(!m_isInitialised) ; //you can only set the factory before calling a create method!
	//bwAssert(p_factory == nullptr) ; //you cannot change a part's factory once set!
	//had to rethink ... setting factory in base constructor then ... in derived.
	p_factory = pFactory ;
}
bwString BwPart::makeName() {
	bwString name ;
	/*if(p_factory != nullptr)
		name = getFactory()->getName() ;
	else*/
	name = getClassName() ;

    const size_t bufferSize = 64;
	char buffer[bufferSize] ;

	//_itoa(m_serial, buffer, 10) ;
	//snprintf(buffer, bufferSize, "%d", m_serial);
	bwItoa(m_serial, buffer, bufferSize, 10);

	name = name + "_" + buffer ;

	return name ;
}
bwString BwPart::makeThingName(const bwString& thingName, bwIndex index) {
    const size_t bufferSize = 64;
	char buffer[bufferSize] ;
	//_itoa(index, buffer, 10) ;
    //snprintf(buffer, bufferSize, "%d", m_serial);
    bwItoa(index, buffer, bufferSize, 10);

	bwString name = getName() + "_" + thingName + "_" + buffer ;

	return name ;
}
//
/*void* BwPart::operator new(size_t count) {
	//return ::malloc(count) ;
	return _aligned_malloc(count, 16);
}
void BwPart::operator delete(void* object) {
	//::free(object) ;
	if (object == nullptr)
		return ;
	_aligned_free(object) ;
}
//
void* BwPart::operator new(size_t count, void * object) {
	return object ;
}
void BwPart::operator delete(void *object, void *memory) {
	bwAssert(0) ; //hmmm...
}
//
void* BwPart::operator new[](size_t count) {
	//void* object = _aligned_malloc(count + 64, 16); //+64???
	void* object = _aligned_malloc(count, 16) ;
	return object ;
}
void BwPart::operator delete[](void* object) {
	_aligned_free(object);
}*/

/*TODO:do we need to implement this?
void operator delete(
   void* _Ptr,
   const std::nothrow_t&
) throw( );
*/
