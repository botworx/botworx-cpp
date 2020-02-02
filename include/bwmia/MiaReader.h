/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaReader_h
#define _MiaReader_h

#include <bwai/AiReader.h>

class MiaMind ;
class MiaDomain ;
typedef boost::intrusive_ptr<MiaDomain> MiaDomainPtr ;
class MiaMethodFactory ;
typedef boost::intrusive_ptr<MiaMethodFactory> MiaMethodFactoryPtr ;
//
class MiaSpace ;
//
#include "MiaRule.h"
//
//MiaReader
//
class MiaReader : public AiReader {
public:
	MiaReader(std::istream& in) ;
	void read() ;
	//Parser Access
	void setMethodFactory(MiaMethodFactory* pFactory) { p_methodFactory = pFactory ; }
	MiaMethodFactory* getMethodFactory() { return p_methodFactory.get() ; }
	void setRuleFactory(MiaRuleFactory* pFactory) { p_ruleFactory = pFactory ; }
	MiaRuleFactory* getRuleFactory() { return p_ruleFactory.get() ; }
	//
	void pushDomain(MiaDomain* pDomain) { m_domains.push(pDomain) ; }
	MiaDomain& getDomain() { return *m_domains.top() ; }
	void popDomain() { m_domains.pop() ; }
	//
	void pushMind(MiaMind* pMind) { m_minds.push(pMind) ; }
	MiaMind& getMind() { return *m_minds.top() ; }
	void popMind() { m_minds.pop() ; }
	//
protected:
	//Data Members
	MiaMethodFactoryPtr p_methodFactory ;
	MiaRuleFactoryPtr p_ruleFactory ;
	//
	std::stack<MiaMind*> m_minds ;
	std::stack<MiaDomain*> m_domains ;
} ;
#define asMiaReader(X) ((MiaReader*)X)


#endif //_MiaReader_h
