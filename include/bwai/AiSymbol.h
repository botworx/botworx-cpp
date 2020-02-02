/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiSymbol_H
#define _AiSymbol_H

#include "AiString.h"
#include <unordered_map>

enum AiSymbolTT_E {
	SYMTYP_NORMAL,
	SYMTYP_PROPERTY,
	SYMTYP_LOGIC
} ;
typedef AiSymbolTT_E AiSymbolTT ;

class AiSymbol : public AiString {
public:
	AiSymbol(const bwString& string) : AiString(TT_SYMBOL, string) {
		if(string[0] == '.')
			m_symType = SYMTYP_PROPERTY ;
		else if (string[0] == '$')
			m_symType = SYMTYP_LOGIC ;
		else
			m_symType = SYMTYP_NORMAL ;

		m_isInterned = false ;
	}
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	AiSymbolTT getSymType() { return m_symType ; }
	bool isProperty() { return m_symType == SYMTYP_PROPERTY ; }
	bool isLogic() { return m_symType == SYMTYP_LOGIC ; }
	bool isNormal() { return m_symType == SYMTYP_NORMAL ; }
	//Data
public:
	void setVal(BwCell* pVal) { p_val = pVal ; }
	BwCell* getVal() { return p_val.get() ; }
	BwCellPtr p_val ;

	AiSymbolTT m_symType ;
	void setIsInterned(bool val) { m_isInterned = val ; }
	bool isInterned() { return m_isInterned ; }
	bool m_isInterned ;
} ;
#define isSymbol(C) (C->getTypeId() == TT_SYMBOL)
#define asSymbol(C) (static_cast<AiSymbol*>(C))
#define asConstSymbol(C) (static_cast<const AiSymbol*>(C))

typedef std::unordered_map<bwString, AiSymbol*> AiSymbolHashMap ;

#include "AiKit.h"

class AiSymbolKit : public AiPoolKitT<AiKit, AiSymbol> {
public:
	AiSymbolKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo)
		: AiPoolKitT<AiKit, AiSymbol>(KT_SYMBOL, pSuperKit, pKitInfo), m_genSymCounter(0) {}
	virtual void doPostDisable(bool sleeping = true) ;
	AiSymbol* internalize(const bwString& string) ;
	void uninternalize(AiSymbol* pSym) ;
	AiSymbol* generateSymbol(const bwString& string) ;
	//Data
	AiSymbolHashMap m_map ;
	//
	int m_genSymCounter ;
} ;
#define asSymbolKit(C) ((AiSymbolKit*)C)
DECLARE_KITINFO(AiSymbolKit) ;
//
inline void* AiSymbol::operator new(size_t count) throw() {
#if AI_OPTION_POOLING
	return k_symbol().rent() ;
#else
	return BW_USERMALLOC(sizeof(AiSymbol), TT_SYMBOL) ;
#endif
}
////////////////
inline AiSymbol* intern(const bwString& string) {
	return k_symbol().internalize(string) ;
}
inline AiSymbol* genSym(const bwString& string) {
	return k_symbol().generateSymbol(string) ;
}
inline AiSymbol* genSym(const AiSymbol* pSymbol) {
	return k_symbol().generateSymbol(pSymbol->getString()) ;
}
inline BwCell* SetGlobalVal(AiSymbol* pSym, BwCell* pVal) {
	pSym->setVal(pVal) ;
	return pVal ;
}
inline BwCell* GetGlobalVal(AiSymbol* pSym) {
	BwCell* pVal = pSym->getVal() ;
	if(pVal == NULL)
		pVal = UNBOUND ;
	return pVal ;
}

#endif //_AiSymbol_H
