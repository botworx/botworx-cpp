#ifndef _MiaExplorer_H
#define _MiaExplorer_H

#include <bwcore/BwStepper.h>

class MiaState ;

class MiaExplorer : public BwStepper {
public:
	MiaExplorer(MiaState* pRoot) ;
	virtual ~MiaExplorer();
	bool doStep() ;
	MiaState* getRoot() { return p_root ; }
	//
	enum explorationStyle_E {
		EXPLORE_HORIZONTAL = 0,
		EXPLORE_VERTICAL,
		EXPLORE_DIAGONAL
	} ;
	typedef explorationStyle_E explorationStyle ;
	void setExplorationStyle(explorationStyle style) { m_explorationStyle = style ; }
	explorationStyle getExplorationStyle() { return m_explorationStyle ; }
	//
	void setMaxDepth(int maxDepth) { m_maxDepth = maxDepth ; }
	int getMaxDepth() { return m_maxDepth ; }
	//Data Members
	MiaState* p_root ;
	explorationStyle m_explorationStyle ;
	int m_maxDepth ;
};

#endif //_MiaExplorer_H

