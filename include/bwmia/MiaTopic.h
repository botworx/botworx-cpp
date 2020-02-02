/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaTopic_H
#define _MiaTopic_H

#include "MiaIdentifier.h"
#include "MiaPattern.h"
#include <bwai/AiList.h>

class MiaFact ;
class MiaSpace ;
//
//MiaTopic
//
class MiaTopic : public BwCell {
public:
	MiaTopic(MiaSpace& space, MiaFact* pSubject, ThingTT cellType = MIA_TT_TOPIC) ;
	~MiaTopic() ;
	void *operator new(size_t count) throw() ;
	virtual void purge() ;
	//
	bool equal(MiaTopic* pTopic) ;
	bool identical(MiaTopic* pTopic) ;
	bool exists(MiaFact* pFact) ;
	bool identicalExists(AiPair* pFacts) ;
	bool identicalExists(MiaFact* pFact) ;

	MiaTopic* copyTo(MiaSpace& space, bool override = false, bool replace = false) ;

	MiaFact* getSubject() const { return p_subject.get() ; }
	MiaFact* getId() const { return p_id.get() ; }

	void assertFact(MiaSpace* pRequester, MiaFact* pFact) ;
	void addFact(MiaFact* pFact) ;
	void retractFact(MiaFact* pFact) ;
	AiPair* getFacts() const { return m_facts.get() ; }
	bool match(MiaPattern& pattern) ;
	bool outerMatch(MiaPattern& pattern) ;
	bool match(MiaPatterns& patterns) ;
	void seek(MiaSearch& search) ;
	void outerSeek(MiaSearch& search) ;
	//make private
	void seekValues(MiaSearch& search) ;
	//
	MiaSpace* getSpace() { return p_space ; }
	MiaSpace* p_space ;
	//
	void setIsCopyable(bool val) { m_isCopyable = val ; }
	bool isCopyable() { return m_isCopyable ; }
	//
	void printFacts(MiaPrinter& printer) ;
	//Data
	MiaFactPtr p_subject ;
	MiaFactPtr p_id ;
	AiList m_facts ;
	bool m_isCopyable ;
	//Serialization
	friend MiaPrinter& operator<<(MiaPrinter& printer, const MiaTopic& data) ;
} ;
typedef boost::intrusive_ptr<MiaTopic> MiaTopicPtr ;
#define isTopic(C) (C->getTypeId() == TT_FLOAT)
#define asTopic(C) ((MiaTopic*)C)
//
//MiaTopicKit
//
#include <bwai/AiKit.h>

class MiaTopicKit : public AiPoolKitT<AiKit, MiaTopic> {
public:
	MiaTopicKit(AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiPoolKitT<AiKit, MiaTopic>(MIA_KT_TOPIC, pSuperKit, pKitInfo) {}
} ;
DECLARE_KITINFO(MiaTopicKit) ;
//
//MiaTopic
//
inline void* MiaTopic::operator new(size_t size) throw() {
#if AI_OPTION_POOLING
	return k_topic().rent() ;
#else
	return BW_USERMALLOC(size, MIA_TT_TOPIC) ;
#endif
}

#endif //_MiaTopic_H
