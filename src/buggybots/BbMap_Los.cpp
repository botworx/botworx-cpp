/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbMap.h>

class Ray : public bwRay {
  public:
    Ray() { }
	Ray(const bwVector3& o, const bwVector3& d) : bwRay(o, d) {
      //mOrigin = o;
      //direction = d;
      inv_direction = bwVector3(1/d[0], 1/d[1], 1/d[2]);

      sign[0] = (inv_direction[0] < 0);
      sign[1] = (inv_direction[1] < 0);
      sign[2] = (inv_direction[2] < 0);
    }
    /*Ray(const Ray &r) {
      mOrigin = r.mOrigin;
      direction = r.direction;
      inv_direction = r.inv_direction;
      sign[0] = r.sign[0]; sign[1] = r.sign[1]; sign[2] = r.sign[2];
    }*/

    //bwVector3 mOrigin;
    //bwVector3 direction;
    bwVector3 inv_direction;
    int sign[3];
};

class Box : public bwBounds3 {
  public:
    Box() { }
	Box(const bwVector3& min, const bwVector3& max) : bwBounds3(min, max) {
    }
	bwPoint3& operator[]( const int x ) {
		if(x == 0)
			return mMin ;
		//else
			return mMax ;
   }
};
inline bool intersect(Box& box, const Ray &r, float t0, float t1) {
  float tmin, tmax, tymin, tymax, tzmin, tzmax;

  tmin = (box[r.sign[0]][0] - r.mOrigin[0]) * r.inv_direction[0];
  tmax = (box[1-r.sign[0]][0] - r.mOrigin[0]) * r.inv_direction[0];
  tymin = (box[r.sign[1]][1] - r.mOrigin[1]) * r.inv_direction[1];
  tymax = (box[1-r.sign[1]][1] - r.mOrigin[1]) * r.inv_direction[1];
  if ( (tmin > tymax) || (tymin > tmax) ) 
    return false;
  if (tymin > tmin)
    tmin = tymin;
  if (tymax < tmax)
    tmax = tymax;
  tzmin = (box[r.sign[2]][2] - r.mOrigin[2]) * r.inv_direction[2];
  tzmax = (box[1-r.sign[2]][2] - r.mOrigin[2]) * r.inv_direction[2];
  if ( (tmin > tzmax) || (tzmin > tmax) ) 
    return false;
  if (tzmin > tmin)
    tmin = tzmin;
  if (tzmax < tmax)
    tmax = tzmax;
  return ( (tmin < t1) && (tmax > t0) );
}

bool BbMap::testLos(const bwPoint3& start, const bwPoint3& end) {
	Ray ray(start, (end - start)) ;
	float t0  = 0.0000001f ; float t1 = .99999f ;

	for(BbMapPortalListIter iter = m_walls.begin() ; iter != m_walls.end() ; ++iter) {
		BbMapPortal& portal = **iter ;
		Box box(portal.m_bounds.getMin(), portal.m_bounds.getMax()) ;
		if(intersect(box, ray, t0, t1))
			return false ;
	}
	//else
	return true ;
}

/*bool BbMap::testLos(const bwPoint3& start, const bwPoint3& end) {
	bwLineSeg seg(start, end) ;
	unsigned int numhits ; float t0 ; float t1 ;

	for(BbMapPortalListIter iter = m_walls.begin() ; iter != m_walls.end() ; ++iter) {
		BbMapPortal& portal = **iter ;
		if(gmtl::intersect(portal.m_bounds, seg, numhits, t0, t1))
			return false ;
	}
	//else
	return true ;
}*/