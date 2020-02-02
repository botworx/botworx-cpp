/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbMap.h>

/*
	This function takes the map and produces a set of m_sectors of the parameter type
	The larger the initial square used to test the world, defined by maxAreaSize, the slower
	the algorithm but the better the rectangularisation. maxAreaSize = 1 is the fastest value
	but it is likely to produce many long thin rectangles. maxAreaSize = MAX_WIDTH_CELLS is
	the slowest value, but it will produce the optimal path traversal rectangle set.
*/
void BbMap::sectorize( MapCellTypes type, int maxAreaSize )
{
	int cellCount = 0;	// Used for counting the number of cells of a particular type
	int x,y;			// Used as counters for x and y rectangle start positions on the 2D grid
	int checkX, checkY;	// Used for checking cells inside the test rectangle

	// Count up the total number of map cells of the type we're about to rectangularise
	for(x=0;x<getWidth();++x)
	{
		for(y=0;y<getHeight();++y)
		{
			BbMapCell& cell = cellAt(x, y) ;
			// If this is the right type and it is not already used in an area
			//if(cellAt(x, y).getCellType()==type && cellAt(x, y).getAreaFree()==true)
			if(cell.getCellType()==type && cell.getAreaFree()==true)
			{
				++cellCount;
			}
		}
	}

	// If there are no cells of this type in the world, then early out
	if(cellCount==0)
	{
		return;
	}

	// If the cells were in one large square how big would it be, never look for size larger than this
	if(cellCount > 2 && cellCount - 1 < maxAreaSize * maxAreaSize)
	{
		//maxAreaSize = (int) (float) sqrt(cellCount - 1);
		maxAreaSize = (int) (float) sqrt((float)cellCount - 1);

	}

	// For all the possible sizes of squares, starting with the largest and working down
    for(int size = maxAreaSize;size>0;size--)
    {
		// This is a fail test, when this is set to true, a rectangle does not contain all free cells of the required type
		bool fail;
        // For the whole map, ensuring the rectangle stays on the map
		for(x=0;x+size <= getWidth();++x)
        {
			for(y=0;y+size <= getHeight();++y)
            {
				// Initialise the fail test
				fail = false;
				// For the entire rectangle being checked
                for(checkX = x;checkX<x+size;++checkX)
                {
					for(checkY = y;checkY<y+size;++checkY)
                    {
						// Grab the cell
						BbMapCell *cell = &cellAt(checkX, checkY) ;
                        // If the cell is not of the required type or it is in use by another bounded area
                        if(cell->getCellType()!=type || cell->getAreaFree()==false)
						{
						    // The fail test is set
	                        fail = true;
							// Break out of the inner for statements
							break;
						}
					}
					// If we've failed
					if(fail==true)
					{
						// Do no continue with this rectangle
						break;
	                }
                }
	            // If we managed to make it out without finding a fail
				if(fail==false)
				{
					// We're now going to try to expand the succesful rectangle
					// These are used to define the rectangle of the new untested area produced by
					// the expansion of the rectangle
					int tx1, tx2, ty1, ty2;
					// These are the guaranteed tested area boundaries, the size of the original rectangle
					int mx1 = x,my1 = y,mx2 = x+size, my2 = y+size;
					// This is a success test
					bool success;
					int failCount = 0;
					// These are the current test area boundaries
					int cx1, cy1, cx2, cy2;
					// Until we've failed to expand in all four directions
					while(failCount<4)
					{
						// For each direction of expansion
						for(int i=0;i<4;++i)
						{
							// This is working so far
							success = true;
							// Set up the test values to the actual values
							cx1 = mx1;cy1 = my1;cx2 = mx2; cy2 = my2;
							// Expand in one direction
							switch(i)
							{
								case 0:
									// Expand to the west
									cx1--;
									// Calculate the extra strip produced by this expansion
									tx1 = cx1; tx2 = cx1 + 1; ty1 = cy1; ty2 = cy2;
									break;
								case 1:
									// Expand to the south
									cy1--;
									// Calculate the extra strip produced by this expansion
									tx1 = cx1; tx2 = cx2; ty1 = cy1; ty2 = cy1 + 1;
									break;
								case 2:
									// Expand to the east
									++cx2;
									// Calculate the extra strip produced by this expansion
									tx1 = cx2 - 1; tx2 = cx2; ty1 = cy1; ty2 = cy2;
									break;
								case 3:
									// Expand to the north
									++cy2;
									// Calculate the extra strip produced by this expansion
									tx1 = cx1; tx2 = cx2; ty1 = cy2 - 1; ty2 = cy2;
									break;
							}
							// If we've expanded off the map
							//if(cx1 < 0 || cy1 < 0 || cx2 > MAP_WIDTH_CELLS || cy2 > MAP_HEIGHT_CELLS)
							if(cx1 < 0 || cy1 < 0 || cx2 > getWidth() || cy2 > getHeight())
							{
								success = false;
							}
							else
							{
								// For the rectangle defined by the new strip from the expansion of the main rectangle
								for(checkX = cx1;checkX<cx2;++checkX)
								{
									for(checkY = cy1;checkY<cy2;++checkY)
									{
										// Grab the cell
										BbMapCell *cell = &cellAt(checkX, checkY) ;
				                        // If the cell is not of the required type or it is in use by another bounded area
										if(cell->getCellType()!=type || cell->getAreaFree()==false){
											// The expansion has failed
											success = false;
											// Break out of the inner for statements
											break;
										}
									}
									// If we've failed
									if(success==false)
									{
										// Do not continue with checking the strip
										break;
									}
								}

							}
							// If we've failed
							if(success==false)
							{
								// Keep a count
								++failCount;
							}
							else
							{
								// We have succeeded, let's try another 4 expansions
								failCount = 0;
								// The actual values are set equal to the succesful test values
								mx1 = cx1; my1 = cy1; mx2 = cx2; my2 = cy2;
							}
						}
					}
					// The number of cells left free of this type is decreased
					cellCount -= (mx2 - mx1) * (my2 - my1);
					//cellCount -= (mx2 - mx1 +1) * (my2 - my1 +1);
					// Map a new area
					BbMapSector *area = new BbMapSector(this);
					//
					// Go through every cell inside this rectangle
					for(checkX=mx1;checkX<mx2;++checkX)
					{
						for(checkY=my1;checkY<my2;++checkY)
						{
							// Set the cell to "taken"
							cellAt(checkX, checkY).setSector(area);
						}
					}
					//
					// Set m_sectors's boundaries s,w,n,e
					//area->setBoundaries(mx1,my1,mx2,my2);
					area->setBoundaries(my2,mx1,my1,mx2);
					// Set its type
					area->setType(type);
					area->validate() ;
					// Add it to the map's area list
					addSector(area);
					// If we've no cells left of this type
					if(cellCount==0)
					{
						// Set up values so we quit out
						//finish = true; ??
						success = true ;
					}
					// Ensure that the number of cells hasn't fallen below zero
					bwAssert(cellCount >= 0);
				}
			}
		}
	}
}
void BbMap::addSector (BbMapSector *area ) {
	area->setVertex(m_sectorCount++) ;
	m_sectors.push_back(area);
}

void BbMap::portalize(MapCellTypes type) {
	for(BbMapSectorsIter iter = m_sectors.begin() ; iter != m_sectors.end() ; ++iter) {
		BbMapSector& sector = **iter ;
		portalizeSector(sector) ;
	}
}
void BbMap::portalizeSector(BbMapSector& sector) {
	//explore north
	if(sector.m_north != 0) {
		portalizeNorth(sector, sector.m_west, sector.m_east) ;
	}
	//explore east
	if(sector.m_east != getWidth()) {
		portalizeEast(sector, sector.m_north, sector.m_south) ;
	}
	//explore south
	if(sector.m_south != getHeight()) {
		portalizeSouth(sector, sector.m_west, sector.m_east) ;
	}
	//explore west
	if(sector.m_west != 0) {
		portalizeWest(sector, sector.m_north, sector.m_south) ;
	}
}
void BbMap::portalizeNorth(BbMapSector& sector, int start, int end) {
	BbMapSector* pNeighbor = NULL ;
	BbMapSector* pPrevNeighbor = cellAt(start, sector.m_north-1).getSector() ;
	BbMapPortal* pPortal = NULL ;
	for(int i = start ; i <= end ; ++i) {
		pNeighbor = cellAt(i, sector.m_north-1).getSector() ;
		if(pNeighbor != pPrevNeighbor) {
			portalizeNorth(sector, i, end) ;
			//pPortal = sector.addPortal(pNeighbor, SIDE_NORTH, start, i) ;
			pPortal = sector.addPortal(pPrevNeighbor, SIDE_NORTH, start, i) ;
			return ;
		}
	}
	pPortal = sector.addPortal(pNeighbor, SIDE_NORTH, start, end) ;
}
void BbMap::portalizeEast(BbMapSector& sector, int start, int end) {
	BbMapSector* pNeighbor = NULL ;
	BbMapSector* pPrevNeighbor = cellAt(sector.m_east+1, start).getSector() ;
	BbMapPortal* pPortal = NULL ;
	for(int i = start ; i <= end ; ++i) {
		pNeighbor = cellAt(sector.m_east+1, i).getSector() ;
		if(pNeighbor != pPrevNeighbor) {
			portalizeEast(sector, i, end) ;
			//pPortal = sector.addPortal(pNeighbor, SIDE_EAST, start, i) ;
			pPortal = sector.addPortal(pPrevNeighbor, SIDE_EAST, start, i) ;
			return ;
		}
	}
	pPortal = sector.addPortal(pNeighbor, SIDE_EAST, start, end) ;
}
void BbMap::portalizeSouth(BbMapSector& sector, int start, int end) {
	BbMapSector* pNeighbor = NULL ;
	BbMapSector* pPrevNeighbor = cellAt(start, sector.m_south+1).getSector() ;
	BbMapPortal* pPortal = NULL ;
	for(int i = start ; i <= end ; ++i) {
		pNeighbor = cellAt(i, sector.m_south+1).getSector() ;
		if(pNeighbor != pPrevNeighbor) {
			portalizeSouth(sector, i, end) ;
			//pPortal = sector.addPortal(pNeighbor, SIDE_SOUTH, start, i) ;
			pPortal = sector.addPortal(pPrevNeighbor, SIDE_SOUTH, start, i) ;
			return ;
		}
	}
	pPortal = sector.addPortal(pNeighbor, SIDE_SOUTH, start, end) ;
}
void BbMap::portalizeWest(BbMapSector& sector, int start, int end) {
	BbMapSector* pNeighbor = NULL ;
	BbMapSector* pPrevNeighbor = cellAt(sector.m_west-1, start).getSector() ;
	BbMapPortal* pPortal = NULL ;
	for(int i = start ; i <= end ; ++i) {
		pNeighbor = cellAt(sector.m_west-1, i).getSector() ;
		if(pNeighbor != pPrevNeighbor) {
			portalizeWest(sector, i, end) ;
			//pPortal = sector.addPortal(pNeighbor, SIDE_WEST, start, i) ;
			pPortal = sector.addPortal(pPrevNeighbor, SIDE_WEST, start, i) ;
			return ;
		}
	}
	pPortal = sector.addPortal(pNeighbor, SIDE_WEST, start, end) ;
}
//////////////
BbMapPortal* BbMapSector::addPortal(BbMapSector* pNeighbor, BbMapSide side, int start, int end) {
	BbMapPortal* pPortal = new BbMapPortal() ;
	m_portals.push_back(pPortal) ;
	pPortal->setSector(this) ;
	pPortal->setNeighbor(pNeighbor) ;
	pPortal->setSide(side) ;
	pPortal->setExtent(start, end) ;
	pPortal->validate() ;
	return pPortal ;
}
BbMapPortal* BbMapSector::findPortal(BbMapSide side, int start, int end) {
	for(BbMapPortalListIter iter = portals().begin() ; iter != portals().end() ; ++iter) {
		BbMapPortal& portal = **iter ;
		if(portal.getSide() != side)
			continue ;
		if(portal.m_start != start)
			continue ;
		if(portal.m_end != end)
			continue ;
		//else
		return &portal ;
	}
	return NULL ;
}
void BbMapSector::validate() {
	bwReal width = m_east - m_west ; //+ 1 ;
	bwReal halfWidth = width / 2 ;
	bwReal depth = m_south - m_north ; //+ 1 ;
	bwReal halfHeight = 1 ;
	bwReal halfDepth = depth / 2 ;
	m_size = bwSize3(width, 2, depth) ;
	//
	bwSize3 mapSize = getMap()->getSize() ;
	bwReal mapHalfWidth = mapSize[0]/2 ;
	bwReal mapHalfDepth = mapSize[2]/2 ;
	bwReal x = (-mapHalfWidth + (m_west + halfWidth)) ; //- .5f ;
	bwReal y = 1.1f ;
	bwReal z = (-mapHalfDepth + (m_north + halfDepth)) ; //- .5f ;
	m_pos = bwPoint3(x,  y, z) ;
	//
	m_bounds.setMin(bwPoint3(x - halfWidth, y - halfHeight, z - halfDepth)) ;
	m_bounds.setMax(bwPoint3(x + halfWidth, y + halfHeight, z + halfDepth)) ;
}
////////////////
void BbMapPortal::validate() {
	//
	bwPoint3 sectorPos = p_sector->getPos() ;
	bwSize3 sectorSize = p_sector->getSize() ;
	bwReal sectorHalfWidth = sectorSize[0]/2 ;
	bwReal sectorHalfDepth = sectorSize[2]/2 ;
	//
	bwSize3 mapSize = p_sector->getMap()->getSize() ;
	bwReal mapHalfWidth = mapSize[0]/2 ;
	bwReal mapHalfDepth =mapSize[2]/2 ;
//
	bwSize3 size(0,2,0) ;
	bwReal x, y, z ;
	y = 1.1f ;
	bwReal length = m_end - m_start ;
	bwReal girth = 1 ;
	switch(m_side) {
		case SIDE_NORTH :
		case SIDE_SOUTH : {
			size[0] = length ;
			size[2] = 1 ;
		}
		break ;
		case SIDE_EAST :
		case SIDE_WEST : {
			size[0] = 1 ;
			size[2] = length ;
		}
		break ;
	}
	setSize(size) ;
	bwReal halfWidth = size[0] / 2 ;
	bwReal halfHeight = size[1] / 2 ;
	bwReal halfDepth = size[2] / 2 ;
	//
	switch(m_side) {
		case SIDE_NORTH : {
			x = (-mapHalfWidth + (m_start + (length/2))) ; //- .5f ;
			z = (-mapHalfDepth + p_sector->m_north + (girth/2)) ; //- .5f ;
		}
		break ;
		case SIDE_EAST : {
			x = (-mapHalfWidth + p_sector->m_east - (girth/2)) ; //- .5f ;
			z = (-mapHalfDepth + (m_start + (length/2))) ; //- .5f ;
		}
		break ;
		case SIDE_SOUTH : {
			x = (-mapHalfWidth + (m_start + (length/2))) ; //- .5f ;
			z = (-mapHalfDepth + p_sector->m_south - (girth/2)) ; //- .5f ;
		}
		break ;
		case SIDE_WEST : {
			x = (-mapHalfWidth + p_sector->m_west + (girth/2)) ; //- .5f ;
			z = (-mapHalfDepth + (m_start + (length/2))) ; //- .5f ;
		}
		break ;
	}
	setPos(bwPoint3(x, y, z)) ;
	//
	m_bounds.setMin(bwPoint3(-halfWidth, -halfHeight, -halfDepth)) ;
	m_bounds.setMax(bwPoint3(halfWidth, halfHeight, halfDepth)) ;
	m_bounds = bwBounds3(m_bounds.getMin() + getPos(), m_bounds.getMax() + getPos()) ;
}
BbMapSector* BbMap::findSector(const bwPoint3& point) {
	bwSize3 mapSize = getSize() ;
	bwReal mapHalfWidth = mapSize[0]/2 ;
	bwReal mapHalfDepth = mapSize[2]/2 ;

	bwReal x = point[0] ;
	bwReal y = point[2] ;
	for(BbMapSectorsIter iter = sectors().begin() ; iter != sectors().end() ; ++iter) {
		BbMapSector& sector = **iter ;
		if(x < -mapHalfWidth + sector.m_west)
			continue ;
		if(x > -mapHalfWidth + sector.m_east)
			continue ;
		if(y < -mapHalfDepth + sector.m_north)
			continue ;
		if(y > -mapHalfDepth + sector.m_south)
			continue ;
		//else
		return &sector ;
	}
	return NULL ;
}
