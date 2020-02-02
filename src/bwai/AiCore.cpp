#include "stdafx.h"

#include <bwai/AiPrinter.h>
#include <bwai/AiMulti.h>
#include <bwai/AiBlob.h>
#include <bwai/AiString.h>
#include <bwai/AiXString.h>
//#include <bwai/AiClass.h>
//#include <bwai/AiObject.h>
#include <bwai/AiInt.h>
#include <bwai/AiFloat.h>
//
#include <bwcore/BwFileKit.h>
#include <bwai/AiBuffer.h>
//
//AiCore
//
/**********Thread Local**************/
#if AI_OPTION_TLS_CORE
	boost::thread_specific_ptr<AiCore> g_core ;
#else
	AiCore* g_core ;
#endif

/************************************/
//Construction
AiCore::AiCore(AiKit* pSuperKit, AiKitInfo *pKitInfo)
: AiKit(KT_CORE, pSuperKit, pKitInfo) {
	#if AI_OPTION_TLS_CORE
	g_core.reset(this) ;
	#else
	g_core = this ;
	#endif
	p_typeDir = new AiTypeDescriptor[AITYPE_MAX] ;
	m_typeCount = TT_UNKNOWN ;
	m_ioMode = IO_CRT ;
	//need to create some kits up front
	p_fileKit = new BwFileKit(this) ; //TODO:when I move this down into the kernel. BwCore?
	BwKit::addKit(p_fileKit) ; //not safe to use aikit version ... move down into kernel.
	//
	p_bufferKit = new AiBufferKit(this) ; //TODO:when I move this down into the kernel. BwCore?
	BwKit::addKit(p_bufferKit) ; //not safe to use aikit version ... move down into kernel.
	//
	p_printer = NULL ;
	p_logger = NULL ;

	p_numberKit = NULL ;
	p_intKit = NULL ;
	p_floatKit = NULL ;
	p_pairKit = NULL ;
	p_multiKit = NULL ;
	p_symbolKit = NULL ;

	//p_classKit = NULL ;
	//p_objectKit = NULL ;
	p_stringKit = NULL ;
	p_xstringKit = NULL ;
	p_blobKit = NULL ;
	for(int i = 0 ; i < AITYPE_MAX ; ++i) {
		TYPEDIR(i) = NULL ;
	}
}
void AiCore::createPrinter() {
	p_printer = new AiPrinter(std::cout) ;
}
void AiCore::createLogger() {
	p_logger = new AiPrinter(std::cout) ;
}
void AiCore::doConfig() {
	AiKit::doConfig() ;
	createSymbols() ;
	initGlobals() ;
	//Io setup
	createPrinter() ;
	createLogger() ;
}
void AiCore::doPostConfig() {
	AiKit::doPostConfig() ;
	createMailCenter() ;
	changeIoMode() ; //sets the sinks on printer and logger depending on mode.
}
void AiCore::createSymbols() {
	SYM_QUOTE = intern("QUOTE") ;
	SYM_EOF = intern("EOF") ;
	SYM_EOL = intern("EOL") ;
	SYM_LAMBDA = intern("*LAMBDA*") ;
	SYM_MACRO = intern("*MACRO*") ;
	//
	SYM_NIL = intern("NIL") ;
	SYM_TRUE = intern("T") ;
	SYM_UNBOUND = intern("*UNBOUND*") ;
}
bool AiCore::initGlobals() {
	SetGlobalVal(SYM_NIL, SYM_NIL) ;
	SetGlobalVal(SYM_TRUE, SYM_TRUE) ;
	SetGlobalVal(SYM_UNBOUND, SYM_UNBOUND) ;
	return true ;
}
AiCore::~AiCore() {
	delete p_typeDir ;
}
void AiCore::doPostDisable(bool sleeping) {
	if(!sleeping) {
		delete p_printer ;
		delete p_logger ;
	}
	AiKit::doPostDisable(sleeping) ;
}
//
void AiCore::addKit(BwKit *pKit) {
	KitTT kitTypeID = static_cast<AiKit*>(pKit)->getKitTypeID() ;
	switch(kitTypeID) {
		case KT_SYMBOL :
			bwAssert(p_symbolKit == NULL) ;
			p_symbolKit = static_cast<AiSymbolKit*>(pKit) ;
			break ;
		case KT_STRING :
			bwAssert(p_stringKit == NULL) ;
			p_stringKit = static_cast<AiStringKit*>(pKit) ;
			break ;
		case KT_XSTRING :
			bwAssert(p_xstringKit == NULL) ;
			p_xstringKit = static_cast<AiXStringKit*>(pKit) ;
			break ;
		/*case KT_CLASS :
			bwAssert(p_classKit == NULL) ;
			p_classKit = static_cast<AiClassKit*>(pKit) ;
			break ;*/
		/*case KT_OBJECT :
			bwAssert(p_objectKit == NULL) ;
			p_objectKit = static_cast<AiObjectKit*>(pKit) ;
			break ;*/
		case KT_PAIR :
			bwAssert(p_pairKit == NULL) ;
			p_pairKit = static_cast<AiPairKit*>(pKit) ;
			break ;
		case KT_MULTI :
			bwAssert(p_multiKit == NULL) ;
			p_multiKit = static_cast<AiMultiKit*>(pKit) ;
			break ;
		case KT_NUMBER :
			bwAssert(p_numberKit == NULL) ;
			p_numberKit = static_cast<AiNumberKit*>(pKit) ;
			break ;
		case KT_INT :
			bwAssert(p_intKit == NULL) ;
			p_intKit = static_cast<AiIntKit*>(pKit) ;
			break ;
		case KT_FLOAT :
			bwAssert(p_floatKit == NULL) ;
			p_floatKit = static_cast<AiFloatKit*>(pKit) ;
			break ;
		case KT_BLOB :
			bwAssert(p_blobKit == NULL) ;
			p_blobKit = static_cast<AiBlobKit*>(pKit) ;
			break ;
		/*default:
			bwAssert(0) ;*/
	}
	AiKit::addKit(pKit) ;
}
AiMeta* AiCore::buildType(AiTypeInfo &pInfo) {
	AiType* pMeta = pInfo.produce(pInfo) ;
	return pMeta ;
}
void AiCore::initType(AiTypeInfo &pInfo) {
	ThingTT metaIndex = pInfo.m_thingTT ;
	AiType* pMeta = NULL ;
	if(isIntegralMb(pInfo)) {
		pMeta = TYPEDIR(metaIndex) ;
		bwAssert(pMeta != NULL) ;
	}
	else {
		char* name = getMbString(pInfo) ;
		pMeta = asType(GetGlobalVal(intern(name))) ;
		bwAssert(pMeta != NULL) ;
	}
	pMeta->init(pInfo) ;
}
size_t AiCore::registerType(AiType* pType, AiTypeInfo& pInfo) {
	size_t metaIndex = pInfo.m_thingTT ;
	if(isIntegralMb(pInfo)) {
		TYPEDIR(metaIndex) = pType ;
	}
	else {
		if(isIndexedMb(pInfo)) {
			metaIndex = ++m_typeCount ;
			TYPEDIR(metaIndex) = pType ;
		}
	}
	return metaIndex ;
}
