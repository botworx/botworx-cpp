/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwmessaging/BwMessage.h>
#include <bwmessaging/BwMessaging.h>

////////////////////
/*
FIELD_STRING,
FIELD_INT32,
FIELD_HANDLE,
FIELD_INT64,
FIELD_FLOAT
*/

void BwMsgField::save(boost::archive::text_oarchive & ar, const unsigned int version) const {
    ar & m_name & m_fieldType ;
	//
	switch(m_fieldType) {
		case FIELD_STRING :
			ar & getString() ;
			break ;
		case FIELD_INT32 :
			ar & getInt32() ;
			break ;
		case FIELD_HANDLE :
			ar & getHandle() ;
			break ;
		case FIELD_BOOL :
			ar & getBool() ;
			break ;
		case FIELD_INT64 :
			ar & getInt64() ;
			break ;
		case FIELD_FLOAT :
			ar & getFloat() ;
			break ;
		default :
			bwAssert(0) ;
	}
	//if(p_next != nullptr)
		//TODO:!!!:How is this even working?
		ar & p_next ;
}
void BwMsgField::load(boost::archive::text_iarchive & ar, const unsigned int version) {
    //ar & m_name & m_fieldType ;
	ar & m_name & m_fieldType ;
	//
	switch(m_fieldType) {
		case FIELD_STRING : {
			bwString val ;
			ar & val ;
			m_val = val ;
			}
			break ;
		case FIELD_INT32 : {
			bwInt32 val ;
			ar & val ;
			m_val = val ;
			}
			break ;
		case FIELD_HANDLE : {
			bwHandle val ;
			ar & val ;
			m_val = val ;
			}
			break ;
		case FIELD_BOOL : {
			bwBool val ;
			ar & val ;
			m_val = val ;
			}
			break ;
		case FIELD_INT64 : {
			bwInt64 val ;
			ar & val ;
			m_val = val ;
			}
			break ;
		case FIELD_FLOAT : {
			bwFloat val ;
			ar & val ;
			m_val = val ;
			}
			break ;
		default :
			bwAssert(0) ;
	}
	//if(p_next != nullptr)
		ar & p_next ;
}
////////////////////
BwMsgData::~BwMsgData() {
	BwMsgField* pNextField = nullptr ;
	for(BwMsgField* pField = p_field ; pField != nullptr ; pField = pNextField) {
		pNextField = pField->p_next ;
		pField->BwMsgField::~BwMsgField() ;
		BwMessaging::singleton::get().p_msgFieldKit->release(pField) ;
	}
}
BwMsgField* BwMsgData::addField(const bwString& name) {
	BwMsgField* pField = static_cast<BwMsgField*>(BwMessaging::singleton::get().p_msgFieldKit->rent(sizeof(BwMsgField))) ;
	new (pField) BwMsgField() ;
	pField->setName(name) ;
	BwMsgField* pOldField = p_field ;
	p_field = pField ;
	pField->p_next = pOldField ;
	return pField ;
}
BwMsgField* BwMsgData::findField(const bwString& name) {
	BwMsgField* pField = p_field ;
	for(; pField != nullptr ; pField = pField->p_next) {
		if(strcmp(pField->m_name, name.c_str()) == 0)
			break ;
	}
	return pField ;
}
//
void BwMsgData::addString(const bwString& name, const bwString& val) {
	BwMsgField* pField = addField(name) ;
	pField->setFieldType(BwMsgField::FIELD_STRING) ;
	pField->setVal(val) ;
}
void BwMsgData::findString(const bwString& name, bwString& result) {
	BwMsgField* pField = findField(name) ;
	if(pField == nullptr)
		throw BwGeneralException("BwMsgData: Field not found") ;
	result = pField->getString() ;
}
//
void BwMsgData::addInt32(const bwString& name, bwInt32 val) {
	BwMsgField* pField = addField(name) ;
	pField->setFieldType(BwMsgField::FIELD_INT32) ;
	pField->m_val = val ;
}
void BwMsgData::findInt32(const bwString& name, bwInt32& result) {
	BwMsgField* pField = findField(name) ;
	if(pField == nullptr)
		throw BwGeneralException("BwMsgData: Field not found") ;
	result = pField->getInt32() ;
}
//
void BwMsgData::addHandle(const bwString& name, bwHandle val) {
	BwMsgField* pField = addField(name) ;
	pField->setFieldType(BwMsgField::FIELD_HANDLE) ;
	pField->m_val = val ;
}
void BwMsgData::findHandle(const bwString& name, bwHandle& result) {
	BwMsgField* pField = findField(name) ;
	if(pField == nullptr)
		throw BwGeneralException("BwMsgData: Field not found") ;
	result = pField->getHandle() ;
}
//
void BwMsgData::addBool(const bwString& name, bwBool val) {
	BwMsgField* pField = addField(name) ;
	pField->setFieldType(BwMsgField::FIELD_BOOL) ;
	pField->m_val = val ;
}
void BwMsgData::findBool(const bwString& name, bwBool& result) {
	BwMsgField* pField = findField(name) ;
	if(pField == nullptr)
		throw BwGeneralException("BwMsgData: Field not found") ;
	result = pField->getBool() ;
}
//
void BwMsgData::addInt64(const bwString& name, bwInt64 val) {
	BwMsgField* pField = addField(name) ;
	pField->setFieldType(BwMsgField::FIELD_INT64) ;
	pField->m_val = val ;
}
void BwMsgData::findInt64(const bwString& name, bwInt64& result) {
	BwMsgField* pField = findField(name) ;
	if(pField == nullptr)
		throw BwGeneralException("BwMsgData: Field not found") ;
	result = pField->getInt64() ;
}
//
void BwMsgData::addFloat(const bwString& name, bwFloat val) {
	BwMsgField* pField = addField(name) ;
	pField->setFieldType(BwMsgField::FIELD_FLOAT) ;
	pField->m_val = val ;
}
void BwMsgData::findFloat(const bwString& name, bwFloat& result) {
	BwMsgField* pField = findField(name) ;
	if(pField == nullptr)
		throw BwGeneralException("BwMsgData: Field not found") ;
	result = boost::any_cast<bwFloat>(pField->m_val) ;
}
//
//
//
BwMessage::BwMessage() {
	BwMsgData* pData = static_cast<BwMsgData*>(BwMessaging::singleton::get().p_msgDataKit->rent(sizeof(BwMsgData))) ;
	new (pData) BwMsgData() ;
	m_data = pData;
	addRef(getData()) ;
}
BwMessage::BwMessage(bwWhat what, bwHandle handle) {
	BwMsgData* pData = static_cast<BwMsgData*>(BwMessaging::singleton::get().p_msgDataKit->rent(sizeof(BwMsgData))) ;
	new (pData) BwMsgData() ;
	m_data = pData;
	m_data->m_what = what ;
	m_data->m_handle = handle ;
	addRef(getData()) ;
}
