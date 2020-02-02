/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiCore_H
#define _AiCore_H

#include "AiKit.h"

class AiCore : public AiKit {
public:
	AiCore(AiKit*  pSuperKit, AiKitInfo *pKitInfo) ;
	virtual ~AiCore() ;
	virtual void doPostDisable(bool sleeping = true) ;
	virtual void doConfig() ;
	virtual void doPostConfig() ;
	bool initGlobals() ;
	virtual void createSymbols() ; //upcall
	//Destruction
	virtual void addKit(BwKit *pKit) ;
	//Cell helpers
	static void dumpBlock(void *ptr, size_t blockSize) ;
	//Kit helpers
	AiMeta* buildType(AiTypeInfo &pInfo) ;
	void initType(AiTypeInfo &pInfo) ;
	size_t registerType(AiType* pType, AiTypeInfo& pTypeInfo) ;
	//IO
	enum ioModes_E {
		IO_CRT = 0,
		IO_MESSAGING
	} ;
	typedef ioModes_E ioMode ;
	void setIoMode(ioMode mode) { m_ioMode = mode ; }
	ioMode getIoMode() { return m_ioMode ; }
	ioMode m_ioMode ;
	virtual void createMailCenter() {}
	virtual void createPrinter() ; //upcall
	virtual void createLogger() ; //upcall
	virtual void changeIoMode() {}
	//Data Members
	AiTypeDescriptor *p_typeDir ;
	size_t m_typeCount ;
	//Kits
	BwFileKit* p_fileKit ;
	AiBufferKit* p_bufferKit ; //TODO:gotta be a way to move meta into kernel proper!!!  merge AiKit into BwKit!!!
	//
	AiNumberKit *p_numberKit ;
	AiIntKit *p_intKit ;
	AiFloatKit *p_floatKit ;
	AiPairKit *p_pairKit ;
	AiMultiKit *p_multiKit ;
	AiSymbolKit *p_symbolKit ;
	
	//AiClassKit *p_classKit ;
	//AiObjectKit *p_objectKit ;
	AiStringKit *p_stringKit ;
	AiXStringKit *p_xstringKit ;
	AiBlobKit *p_blobKit ;

	//Symbols
	AiSymbol* p_sym_nil ;
	AiSymbol* p_sym_true ;
	AiSymbol* p_sym_unbound ;
	AiSymbol* p_sym_quote ;
	AiSymbol* p_sym_eof ;
	AiSymbol* p_sym_eol ;
	AiSymbol* p_sym_lambda ;
	AiSymbol* p_sym_macro ;
	//
	AiPrinter *p_printer ;
	AiPrinter *p_logger ;
} ;

//Symbols
#define SYM_NIL (k_core().p_sym_nil)
#define SYM_TRUE (k_core().p_sym_true)
#define SYM_UNBOUND (k_core().p_sym_unbound)
#define SYM_QUOTE (k_core().p_sym_quote)
#define SYM_EOF (k_core().p_sym_eof)
#define SYM_EOL (k_core().p_sym_eol)
#define SYM_LAMBDA (k_core().p_sym_lambda)
#define SYM_MACRO (k_core().p_sym_macro)

#endif //_AiCore_H
