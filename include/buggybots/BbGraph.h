#ifndef _BbGraph_H
#define _BbGraph_H

//boost typedefs
#include <boost/graph/adjacency_list.hpp>
//
struct location	{
float y, x; // lat, long
};
typedef float cost;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property,
	boost::property<boost::edge_weight_t, cost> > mygraph_t ;
typedef boost::property_map<mygraph_t, boost::edge_weight_t>::type WeightMap;
typedef mygraph_t::vertex_descriptor vertex;
typedef mygraph_t::edge_descriptor edge_descriptor;
typedef mygraph_t::vertex_iterator vertex_iterator;
typedef std::pair<int, int> edge;

class BbGraph {
public:
	//Data Members
} ;

#endif //_BbGraph_H