/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaFact_H
#define _MiaFact_H

class AiValue ;

class MiaTopic ;
class MiaFactory ;
class MiaFact ;
class MiaPrinter ;

typedef boost::intrusive_ptr<MiaFact> MiaFactPtr ;

inline bool isFact(const BwCell* cell) { return cell->getTypeId() == MIA_TT_FACT ; }
inline bool ofFact(const BwCell* cell) { return ofTT(cell->getTypeId(), MIA_TT_FACT) ; }
//
//MiaFact
//
class MiaFact : public BwCell {
public:
	MiaFact(MiaFact& fact) : BwCell(MIA_TT_FACT) {
		init(fact.getSubject(),
			fact.getLink(),
			fact.getValue(),
			fact.getTruth()) ;
	}
	MiaFact(MiaFact* pSubject, MiaFact* pLink, BwCell* pVal, float truth = 1)
		: BwCell(MIA_TT_FACT) {
		init(pSubject, pLink, pVal, truth) ;
	}
	//
	MiaFact(ThingTT cellType = MIA_TT_FACT)
		: BwCell(cellType) {
		init(NULL, NULL, NULL, 1) ;
	}
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	void init(MiaFact* pSubject, MiaFact* pLink, BwCell* pVal, float truth) {
		setSubject(pSubject) ;
		setLink(pLink) ;
		setValue(pVal) ;
		setTruth(truth) ;
		m_isCopyable = true ;
	}
	bool equal(MiaFact* pFact) {
		if( (pFact->getSubject() == getSubject()) &&
			(pFact->getLink() == getLink()) &&
			(pFact->getValue() == getValue()) ) {
			return true ;
			}
		else
			return false ;
	}
	bool identical(MiaFact* pFact) {
		if( (pFact->getLink() == getLink()) &&
			(pFact->getValue() == getValue()) ) {
			return true ;
			}
		else
			return false ;
	}
	MiaFact* clone() ;
	void setPropertyVal(AiSymbol* pSymbol, BwCell* pVal) ;
	BwCell* getPropertyVal(AiSymbol* pSymbol) ;
	//
	void setSubject(MiaFact* pSubject) {
		p_subject = pSubject ;
	}
	MiaFact* getSubject() const { return p_subject ; }
	MiaFact& subject() const { return *getSubject() ; }
	//
	void setLink(MiaFact* pLink) {
		p_link = pLink ;
	}
	MiaFact* getLink() const { return p_link.get() ; }
	MiaFact& link() { return *getLink() ; }
	//
	void setValue(BwCell* pValue) {
		p_value = pValue ;
	}
	BwCell* getValue() const { return p_value.get() ; }
	BwCell& value() const { return *getValue() ; }
	//
	void setTruth(float val) { m_truth = val ; }
	float getTruth() const { return m_truth ; }
	//
	void setIsCopyable(bool val) { m_isCopyable = val ; }
	bool isCopyable() const { return m_isCopyable ; }
	bool isIdentifier() const { return p_subject == NULL ; }
	//Data
private:
	//MiaFactPtr p_subject ; //subject
	MiaFact* p_subject ; //subject
	MiaFactPtr p_link ; //linking topic ... (<x> HAS <y>), (<x> IS_A <y>)
	BwCellPtr p_value ;
	float m_truth ;
	bool m_isCopyable ;
public:
	friend MiaPrinter& operator<<(MiaPrinter &printer, const MiaFact& data) ;
} ;
typedef std::list<MiaFact*> MiaFacts ;
typedef std::list<MiaFact*>::iterator MiaFactIter ;
//
inline MiaFact* asFact(BwCell* pCell) {
	bwAssert( (pCell == NULL || pCell == UNBOUND) ? true : ofTT(pCell->getTypeId(), MIA_TT_FACT ) ) ;
	return static_cast<MiaFact*>(pCell) ;
}
inline const MiaFact* asConstFact(const BwCell* pCell) {
	bwAssert( (pCell == NULL || pCell == UNBOUND) ? true : ofTT(pCell->getTypeId(), MIA_TT_FACT ) ) ;
	return static_cast<const MiaFact*>(pCell) ;
}
//
//MiaFactKit
//
#include <bwai/AiKit.h>

class MiaFactKit : public AiPoolKitT<AiKit, MiaFact> {
public:
	MiaFactKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo)
		: AiPoolKitT<AiKit, MiaFact>(MIA_KT_FACT, pSuperKit, pKitInfo) {}
} ;

DECLARE_KITINFO(MiaFactKit) ;
//
//MiaFact
//
inline void* MiaFact::operator new(size_t size) throw() {
#if AI_OPTION_POOLING
	return k_fact().rent() ;
#else
	return BW_USERMALLOC(size, MIA_TT_FACT) ;
#endif
}

#endif //_MiaFact_H

