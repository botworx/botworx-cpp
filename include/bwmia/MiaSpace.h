/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaSpace_H
#define _MiaSpace_H

#include <bwcore/BwActor.h>
#include "MiaPattern.h"
#include <bwai/AiList.h>
#include "MiaBinder.h"

class MiaTopic ;

typedef boost::intrusive_ptr<MiaTopic> MiaTopicPtr ;
typedef std::pair<MiaFact*, MiaTopic*> MiaTopicMapPair ;
typedef std::vector<MiaTopicMapPair> MiaTopicMap ;
typedef MiaTopicMap::iterator MiaTopicMapIter ;
//
//MiaSpace
//
class MiaSpace  : public BwActor {
public:
	MiaSpace(MiaSpace* pParent, AiSymbol* pSymbol) ;
	virtual ~MiaSpace() ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	virtual BwCell* getPropertyVal(AiSymbol* pSymbol) { return NULL ; }
	//
	void copyTopics(MiaSpace* pSrc, bool deepCopy = true) ;
	void addTopic(MiaTopic* pTopic) ;
	void replaceTopic(MiaTopic* pTopic) ;
	AiPair* getTopics() const { return m_topics.get() ; }
	void addSubject(MiaFact* pSubject) { m_subjects.push_back(pSubject) ; }
	void setSubjects(AiPair* pSubjects) { m_subjects.set(pSubjects) ; }
	AiPair* getSubjects() { return m_subjects.get() ; }
	AiList m_subjects ;
	//
	MiaTopic* getIdTopic() { return p_idTopic.get() ; }
	MiaFactPtr p_id ;
	MiaFact* getId() { return p_id.get() ; }
	MiaTopic* lookup(MiaFact* pId) ;
	MiaTopic* lookup(AiPair* pFacts) ;
	MiaTopic* innerLookup(MiaFact* pId) ;
	MiaTopic* outerLookup(MiaFact* pId) ;
	//
	AiList findSubjects(AiPair* pFacts) ;
	AiList findSubjects(MiaPatterns& patterns) ;
	//TODO:are we going to use these?
	bool identicalExists(MiaTopic* pTopic) ;
	//Data
	enum {
		TOPIC_RESERVE = 16
	} ;
	MiaTopicPtr p_idTopic ;
	AiList m_topics ;
	MiaTopicMap m_topicMap ; //map subjects to topics
	//
	friend MiaPrinter& operator<<(MiaPrinter& printer, const MiaSpace& data) ;
	virtual void dump() ;
	void printBranch(MiaPrinter& printer) ;
	void print(MiaPrinter& printer) const ;
	void printFacts(MiaPrinter& printer) const ;
	//
	//bwString getPath() ;
	/////////
	void setName(const bwString& name) ;
	void setSymbol(AiSymbol* pSymbol) { p_symbol = pSymbol ; }
	AiSymbol* getSymbol() { return p_symbol.get() ; }
	MiaSpace* getParent() { return p_parent ; }
	bool hasParent() { return p_parent != NULL ; }
	bool isRoot() { return p_parent == NULL ; }
	//Data Members
	AiSymbolPtr p_symbol ; //name
	MiaSpace* p_parent ;
} ;

#endif //_MiaSpace_H
