/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbMap.h>
//
#include <boost/graph/astar_search.hpp>
//

void BbMap::edgize() {
	for(BbMapSectorsIter iter = m_sectors.begin() ; iter != m_sectors.end() ; ++iter) {
		BbMapSector& sector = **iter ;
		edgizeSector(sector) ;
	}
}
void BbMap::edgizeSector(BbMapSector& sector) {
	for(BbMapPortalListIter iter = sector.portals().begin() ; iter != sector.portals().end() ; ++iter) {
		BbMapPortal& portal = **iter ;
		edgizePortal(portal) ;
	}
}
void BbMap::edgizePortal(BbMapPortal& portal) {
	if(portal.getNeighbor() == NULL) {
		//means this is a wall
		addWall(&portal) ;
		return ; 
	}
	if(portal.getEdge() != NULL)
		return ; //means edge was created and set by neighbor
	//else
	BbMapPortal* pOther = NULL ;
	//
	switch(portal.getSide()) {
		case SIDE_NORTH : {
			pOther = portal.getNeighbor()->findPortal(SIDE_SOUTH, portal.m_start, portal.m_end) ;
		}
		break ;
		case SIDE_EAST : {
			pOther = portal.getNeighbor()->findPortal(SIDE_WEST, portal.m_start, portal.m_end) ;
		}
		break ;
		case SIDE_SOUTH : {
			pOther = portal.getNeighbor()->findPortal(SIDE_NORTH, portal.m_start, portal.m_end) ;
		}
		break ;
		case SIDE_WEST : {
			pOther = portal.getNeighbor()->findPortal(SIDE_EAST, portal.m_start, portal.m_end) ;
		}
		break ;
	}
	if(pOther == NULL)
		return ;

	BbMapEdge* pEdge = new BbMapEdge() ;
	pEdge->setWeight(bwmath::distance(portal.getSector()->getPos(), pOther->getSector()->getPos())) ;
	portal.setEdge(pEdge) ;
	pEdge->setPortal(0, &portal) ;

	pOther->setEdge(pEdge) ;
	pEdge->setPortal(1, pOther) ;
	addEdge(pEdge) ;
}
void BbMap::addEdge(BbMapEdge* pEdge) { 
	m_edges.push_back(pEdge) ; 
    edge_descriptor e; bool inserted;
	tie(e, inserted) = boost::add_edge(
		pEdge->getPortal(0)->getSector()->getVertex(), 
		pEdge->getPortal(1)->getSector()->getVertex(), 
		m_graph) ;
    m_weightMap[e] = pEdge->getWeight() ;
}
///////
using namespace boost ;
// euclidean distance heuristic
template <class Graph, class CostType>
class distance_heuristic : public astar_heuristic<Graph, CostType>
{
public:
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  distance_heuristic(BbMap* pMap, Vertex goal)
    : p_map(pMap), m_goal(goal) {}
  CostType operator()(Vertex u)
  {
    //CostType dx = m_location[m_goal].x - m_location[u].x;
	  CostType dx = p_map->getSector(m_goal)->getPos()[0] - p_map->getSector(u)->getPos()[0] ;
    //CostType dy = m_location[m_goal].y - m_location[u].y;
	  CostType dy = p_map->getSector(m_goal)->getPos()[2] - p_map->getSector(u)->getPos()[2] ;
    return ::sqrt(dx * dx + dy * dy);
  }
private:
  BbMap* p_map ;
  Vertex m_goal;
};


struct found_goal {}; // exception for termination

// visitor that terminates when we find the goal
template <class Vertex>
class astar_goal_visitor : public boost::default_astar_visitor
{
public:
  astar_goal_visitor(Vertex goal) : m_goal(goal) {}
  template <class Graph>
  void examine_vertex(Vertex u, Graph& g) {
    if(u == m_goal)
      throw found_goal();
  }
private:
  Vertex m_goal;
};

BbMapPath BbMap::findPath(BbMapSector* pStart, BbMapSector* pGoal) {
	BbMapPath shortest_path ;
	if(pStart == NULL || pGoal == NULL)
		return shortest_path ;
	BbMapVertex start = pStart->getVertex() ;
	BbMapVertex goal = pGoal->getVertex() ;

	std::vector<BbMapVertex> p(num_vertices(m_graph));
	std::vector<cost> d(num_vertices(m_graph));

	try {
		// call astar named parameter interface
		astar_search(
			m_graph, 
			start,
			distance_heuristic<mygraph_t, cost>
				(this, goal),
			predecessor_map(&p[0]).distance_map(&d[0]).
		visitor(astar_goal_visitor<BbMapVertex>(goal)));
		
		
	} catch(found_goal fg) { // found a path to the goal
		//list<vertex> shortest_path;
		for(BbMapVertex v = goal;; v = p[v]) {
		//shortest_path.push_front(v);
		shortest_path.push_front(getSector(v)) ;
		if(p[v] == v)
			break;
		}
	}
	return shortest_path ;
}