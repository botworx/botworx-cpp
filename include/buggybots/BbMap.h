#ifndef _BbMap_H
#define _BbMap_H

//boost typedefs
#include <boost/graph/adjacency_list.hpp>
//
struct location	{
float y, x; // lat, long
};
typedef float cost;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property,
	boost::property<boost::edge_weight_t, cost> > mygraph_t ;
typedef boost::property_map<mygraph_t, boost::edge_weight_t>::type BbWeightMap ;
//typedef mygraph_t::vertex_descriptor vertex;
typedef mygraph_t::vertex_descriptor BbMapVertex ;
typedef mygraph_t::edge_descriptor edge_descriptor;
typedef mygraph_t::vertex_iterator vertex_iterator;
typedef std::pair<int, int> edge;

enum MapCellTypes {
	MCF_UNEXPLORED,
	MCF_OBSTACLE,
	MCF_PATH,
	MCF_NUMBER_OF_CELL_TYPES,
};
enum BbMapSide {
	SIDE_NORTH,
	SIDE_EAST,
	SIDE_SOUTH,
	SIDE_WEST,
	SIDE_TTL
} ;
class BbMapSector ;
class BbMapPortal ;

class BbMapCell {
public:
	BbMapCell() : m_isClosed(false), p_sector(NULL), m_type(MCF_UNEXPLORED) {
		for(int i = 0 ; i < SIDE_TTL ; ++i)
			m_portals[i] = NULL ;
	}
	void setIsClosed(bool value) { m_isClosed = value ; }
	bool isClosed() { return m_isClosed ; }
	//
	MapCellTypes	getCellType( )					{ return m_type; }
	void			setCellType( MapCellTypes type )	{ m_type = type; }
	bool			getAreaFree() { return p_sector == NULL ; }
	void setSector(BbMapSector* pSector) { p_sector = pSector ; }
	BbMapSector* getSector() { return p_sector ; }
	//
	bool isExplored() { return m_type !=  MCF_UNEXPLORED ; }
	//
	void setPortal(BbMapSide side, BbMapPortal* pPortal) { m_portals[side] = pPortal ; }
	BbMapPortal* getPortal(BbMapSide side) { return m_portals[side] ; }
private:
	bool m_isClosed ;
	MapCellTypes	m_type;
	BbMapSector* p_sector ;
	BbMapPortal* m_portals[SIDE_TTL] ;
};
//////////
class BbMapEdge {
public:
	void setPortal(size_t indice, BbMapPortal* pPortal) { m_portals[indice] = pPortal ; }
	BbMapPortal* getPortal(size_t indice) { return m_portals[indice] ; }
	void setWeight(float weight) { m_weight = weight ; }
	float getWeight() { return m_weight ; }
	BbMapPortal* m_portals[2] ;
	float m_weight ;
} ;
typedef std::vector<BbMapCell> BbMapCells ;
typedef BbMapCells::iterator BbMapCellIter ;
//
typedef std::vector<BbMapEdge*> BbMapEdges ;
typedef BbMapEdges::iterator BbMapEdgesIter ;
//
typedef std::vector<BbMapSector*> BbMapSectors ;
typedef BbMapSectors::iterator BbMapSectorsIter ;
//
typedef std::list<BbMapPortal*> BbMapPortalList ;
typedef BbMapPortalList::iterator BbMapPortalListIter ;
//
typedef std::list<BbMapSector*> BbMapPath ;
typedef BbMapPath::iterator BbMapPathIter ;
//
class BbMap {
public:
	BbMap() : m_sectorCount(0) {}
	void setSize(const bwSize3& size) {
		m_size = size ;
		//m_cells = new BbMapCell[getWidth() * getHeight()] ;
		m_cells.resize(getWidth() * getHeight()) ;
		//
		m_weightMap = get(boost::edge_weight, m_graph);
	}
	bwSize3 getSize() { return m_size ; }
	int getWidth() { return m_size[0] ; }
	int getHeight() { return m_size[2] ; }
	void sectorize( MapCellTypes type, int maxAreaSize );
	void addSector(BbMapSector *area ) ;
	BbMapSectors& sectors() { return m_sectors ; }
	BbMapCell& cellAt(int x, int y) { return m_cells[y * getWidth() + x] ; }
	//
	BbMapSector* getSector(BbMapVertex v) { return m_sectors[v] ; }
	BbMapSector* findSector(const bwPoint3& point) ;
	//
	void portalize(MapCellTypes type) ;
	void portalizeSector(BbMapSector& sector) ;
	void portalizeNorth(BbMapSector& sector, int start, int end) ;
	void portalizeEast(BbMapSector& sector, int start, int end) ;
	void portalizeSouth(BbMapSector& sector, int start, int end) ;
	void portalizeWest(BbMapSector& sector, int start, int end) ;
	BbMapPortalList& portals() { return m_portals ; }
	//AStar
	void edgize() ;
	void edgizeSector(BbMapSector& sector) ;
	void edgizePortal(BbMapPortal& portal) ;
	void addEdge(BbMapEdge* pEdge) ;
	BbMapPath findPath(BbMapSector* pStart, BbMapSector* pGoal) ;
	//Line of sight
	void addWall(BbMapPortal* pPortal) { m_walls.push_back(pPortal) ; }
	bool testLos(const bwPoint3& start, const bwPoint3& end) ;
	//
private:
	//BbMapCell* m_cells ;
	BbMapCells m_cells ;
	BbMapSectors m_sectors;
	size_t m_sectorCount ;
	BbMapPortalList m_portals ;
	//
	bwSize3 m_size ;
	//
	BbMapEdges m_edges ;
	mygraph_t m_graph ;
	BbWeightMap m_weightMap ;
	//
	BbMapPortalList m_walls ;
};
class BbMapRect {
public:
	void setPos(const bwPoint3& pos) { m_pos = pos ; }
	bwPoint3 getPos() { return m_pos ; }
	void setSize(const bwSize3& size) { m_size = size ; }
	bwSize3 getSize() { return m_size ; }
	//
	bwPoint3 m_pos ;
	bwSize3 m_size ;
	bwBounds3 m_bounds ;
} ;
/*
	This is the class for m_sectors of map cells, defined by a bounding rectangle
*/
class BbMapSector : public BbMapRect {
public:
	BbMapSector(BbMap* pMap) : p_map(pMap) {}
	void setBoundaries( int south, int west, int north, int east ) { 
		m_north = north; m_south = south; m_east = east, m_west = west; 
	}
	void setType( MapCellTypes type ) { m_type = type; }
	//
	void validate() ;
	//
	BbMapPortal* addPortal(BbMapSector* pNeighbor, BbMapSide side, int start, int end) ;
	BbMapPortal* findPortal(BbMapSide side, int start, int end) ;
	BbMapPortalList& portals() { return m_portals ; }
	//
	int				m_north, m_south, m_east, m_west;
	MapCellTypes	m_type;
	//
	BbMapPortalList m_portals ;
	//
	BbMap* p_map ;
	//void set_map(BbMap* pMap) { p_map = pMap ; }
	BbMap* getMap() { return p_map ; }
	void setIsExplored(bool val) { m_isExplored = val ; }
	bool isExplored() { return m_isExplored ; }
	bool m_isExplored ;
	//
	BbMapVertex m_vertex ;
	void setVertex(BbMapVertex v) { m_vertex = v ; }
	BbMapVertex getVertex() { return m_vertex ; }
};
///////////////////////////
class BbMapPortal : public BbMapRect {
public:
	BbMapPortal() : p_sector(NULL), p_neighbor(NULL), p_edge(NULL) {}
	void setSide(BbMapSide side) { m_side = side ; }
	BbMapSide getSide() { return m_side ; }
	void setSector(BbMapSector* pSector) { p_sector = pSector ; }
	BbMapSector* getSector() { return p_sector ; }
	void setNeighbor(BbMapSector* pSector) { p_neighbor = pSector ; }
	BbMapSector* getNeighbor() { return p_neighbor ; }
	void setExtent(int start, int end) { m_start = start, m_end = end ; }
	//
	void validate() ;
	//Data Members
	BbMapSector* p_sector ;
	BbMapSector* p_neighbor ;
	BbMapSide m_side ;
	int m_start ;
	int m_end ;
	//
	BbMapEdge* p_edge ;
	void setEdge(BbMapEdge* pEdge) { p_edge = pEdge ; }
	BbMapEdge* getEdge() { return p_edge ; }
};
#endif //_BbMap_H