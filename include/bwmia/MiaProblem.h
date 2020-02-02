#ifndef _MiaProblem_H
#define _MiaProblem_H

#include <bwcore/BwActor.h>

class MiaDomain ;
class MiaExplorer ;
class MiaState ;
class BwScript ;

typedef std::vector<MiaState*> MiaStateContainer ;
typedef MiaStateContainer::iterator MiaStateIter ;

class MiaProblem : public BwActor {
public:
	MiaProblem(MiaDomain* pDomain) ;
	virtual ~MiaProblem();
	MiaState* getRoot() { return p_root ; }
	MiaExplorer* getExplorer() { return p_explorer ; }
	//
	void createRoot() ;
	void destroyRoot() ;
	//
	void createExplorer() ;
	//
	void addSolution(MiaState* pState) { m_solutions.push_back(pState) ; }
	virtual BwScript* makeScript() ;
	MiaState* chooseSolution() ;
	void clearSolutions() { m_solutions.clear() ; }
	//Data Members
	MiaDomain* p_domain ;
	MiaState* p_root ;
	MiaExplorer* p_explorer ;
	MiaStateContainer m_solutions ;
};

#endif //_MiaProblem_H

