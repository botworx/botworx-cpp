#ifndef _MiaFactoid_H
#define _MiaFactoid_H

#include "MiaIdentifier.h"

class MiaFactoid {
public:
	MiaFactoid() { init(NULL, NULL, NULL, 1.0f) ; }
	MiaFactoid(MiaFact* pSubject, MiaFact* pLink, BwCell* pVal, float truth = 1.0f) 
		: p_subject(pSubject), p_link(pLink), p_value(pVal), m_truth(truth)
	{}
	MiaFactoid(const MiaFact& fact) 
		: p_subject(fact.getSubject()), 
		p_link(fact.getLink()), 
		p_value(fact.getValue()), 
		m_truth(fact.getTruth())
	{}
	MiaFactoid(const MiaFactoid& fact) 
		: p_subject(fact.getSubject()), 
		p_link(fact.getLink()), 
		p_value(fact.getValue()), 
		m_truth(fact.getTruth())
	{}
	void init(MiaFact* pSubject, MiaFact* pLink, BwCell* pVal, float truth) {
		setSubject(pSubject) ;
		setLink(pLink) ;
		setValue(pVal) ;
		setTruth(truth) ;
	}
	MiaFact* createFact() { return new MiaFact(getSubject(), getLink(), getValue(), getTruth()) ; }
	//
	void setSubject(MiaFact* pSubject) { p_subject = pSubject ; }
	MiaFact* getSubject() const { return p_subject ; }
	//
	void setLink(MiaFact* pLink) { p_link = pLink ; }
	MiaFact* getLink() const { return p_link ; }
	//
	void setValue(BwCell* pValue) { p_value = pValue ; }
	BwCell* getValue() const { return p_value ; }
	//
	void setTruth(float val) { m_truth = val ; }
	float getTruth() const { return m_truth ; }

	//Data Members
	MiaFact* p_subject ;
	MiaFact* p_link ;
	BwCell* p_value ;
	float m_truth ;
} ;


#endif //_MiaFactoid_H