#ifndef _MiaBinder_H
#define _MiaBinder_H

#include <bwai/AiMulti.h>
//
//MiaBinder
//
class MiaMethod ;
class MiaState ;

//
class MiaBinder ;

struct MiaBinding {
	MiaBinding() {}
	MiaBinding(AiSymbol* pSym, BwCell* pVal) : p_symbol(pSym), p_value(pVal) {}
	AiSymbol* getSymbol() { return p_symbol.get() ; }
	BwCell* getValue() { return p_value.get() ; }
	//
	AiSymbolPtr p_symbol ;
	BwCellPtr p_value ;
} ;
//typedef std::vector<MiaBinding> MiaBindingVector ;
//typedef MiaBindingVector::iterator MiaBindingIter ;
typedef MiaBinding* MiaBindingIter ;

class MiaBinder {
public:
	MiaBinder() : m_size(0), m_isMulti(false), m_multiNdx(0), p_method(NULL) {}
	MiaBinder(MiaMethod* pMethod)
		: m_size(0), m_isMulti(false), m_multiNdx(0), p_method(pMethod) {}

	BwCell* setVal(AiSymbol* pSym, BwCell* pVal) {
		for(int i = 0 ; i < m_size ; ++i) {
			MiaBinding& binding = m_bindings[i] ;
			if(binding.p_symbol == pSym) {
				if(getTT(binding.p_value) == TT_MULTI) {
					asMulti(binding.getValue())->m_list.push_back(pVal) ;
				}
				else {
					bwAssert(!isMulti()) ; //can't be more than one multi per binder.
					m_multiNdx = i ;
					m_isMulti = true ;
					binding.p_value = new AiMulti(cons(binding.getValue(), pVal)) ;
				}
				return pVal ;
			}
		}
		if(getTT(pVal) == TT_MULTI) {
			bwAssert(!isMulti()) ; //can't be more than one multi per binder.
			m_multiNdx = m_size ;
			m_isMulti = true ;
		}
		m_bindings[m_size].p_symbol = pSym ;
		m_bindings[m_size].p_value = pVal ;
		m_size++ ;
		return pVal ;
	}
	BwCell* getVal(AiSymbol* pSym) {
		for(int i = 0 ; i < m_size ; ++i) {
			MiaBinding& binding = m_bindings[i] ;
			if(binding.getSymbol() == pSym)
				return binding.getValue() ;
		}
		//else
		return UNBOUND ;
	}
	bool exists(AiSymbol* pSym) {
		for(int i = 0 ; i < m_size ; ++i) {
			MiaBinding& binding = m_bindings[i] ;
			if(binding.getSymbol() == pSym)
				return true ;
		}
		//else
		return false ;
	}
	void copy(const MiaBinder& binder) {
		m_size = binder.m_size ;
		for(int i = 0 ; i < m_size ; ++i) {
			m_bindings[i] = binder.m_bindings[i] ;
		}
		p_method = binder.p_method ;
	}
	MiaBinding& bindings() { return m_bindings[0] ; }
	MiaBindingIter begin() { return &m_bindings[0] ; }
	MiaBindingIter end() { return &m_bindings[m_size] ; }
	//
	bool isMulti() { return m_isMulti ; }
//protected:
	enum { BINDINGS_MAX = 16 } ;
	MiaBinding m_bindings[BINDINGS_MAX] ;
	int m_size ;
	bool m_isMulti ;
	int m_multiNdx ;
	//
	void setMethod(MiaMethod* pMethod) { p_method = pMethod ; }
	MiaMethod* getMethod() { return p_method ; }
	friend MiaPrinter& operator<<(MiaPrinter &printer, MiaBinder& data) ;
//protected:
	MiaMethod* p_method ;
} ;

#endif//_MiaBinder_H
