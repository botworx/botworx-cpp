// ----------------------------------------------------------------------------
//
//
// OpenSteer -- Steering Behaviors for Autonomous Characters
//
// Copyright (c) 2002-2003, Sony Computer Entertainment America
// Original author: Craig Reynolds <craig_reynolds@playstation.sony.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
//
// ----------------------------------------------------------------------------
//
//
// Pathway and PolylinePathway, for path following.
//
// 10-04-04 bk:  put everything into the OpenSteer namespace
// 06-03-02 cwr: created
//
//
// ----------------------------------------------------------------------------


#ifndef OPENSTEER_PATHWAY_H
#define OPENSTEER_PATHWAY_H


#include "Vec3.h"

namespace OpenSteer {

    // ----------------------------------------------------------------------------
    // Pathway: a pure virtual base class for an abstract pathway in space, as for
    // example would be used in path following.


    class Pathway
    {
    public:
        // Given an arbitrary point ("A"), returns the nearest point ("P") on
        // this path.  Also returns, via output arguments, the path tangent at
        // P and a measure of how far A is outside the Pathway's "tube".  Note
        // that a negative distance indicates A is inside the Pathway.
        virtual bwVector3 mapPointToPath (const bwVector3& point,
                                     bwVector3& tangent,
                                     bwReal&  outside) = 0;

        // given a distance along the path, convert it to a point on the path
        virtual bwVector3 mapPathDistanceToPoint (bwReal pathDistance) = 0;

        // Given an arbitrary point, convert it to a distance along the path.
        virtual bwReal mapPointToPathDistance (const bwVector3& point) = 0;

        // is the given point inside the path tube?
        bool isInsidePath (const bwVector3& point)
        {
            bwReal outside; bwVector3 tangent;
            mapPointToPath (point, tangent, outside);
            return outside < 0;
        }

        // how far outside path tube is the given point?  (negative is inside)
        bwReal howFarOutsidePath (const bwVector3& point)
        {
            bwReal outside; bwVector3 tangent;
            mapPointToPath (point, tangent, outside);
            return outside;
        }
    };


    // ----------------------------------------------------------------------------
    // PolylinePathway: a simple implementation of the Pathway protocol.  The path
    // is a "polyline" a series of line segments between specified points.  A
    // radius defines a volume for the path which is the union of a sphere at each
    // point and a cylinder along each segment.


    class PolylinePathway: public virtual Pathway
    {
    public:
        PolylinePathway (void) {}

        // construct a PolylinePathway given the number of points (vertices),
        // an array of points, and a path radius.
        PolylinePathway (const int _pointCount,
                         const bwVector3 _points[],
                         bwReal _radius,
                         const bool _cyclic);

        // utility for constructors in derived classes
        void initialize (const int _pointCount,
                         const bwVector3 _points[],
                         bwReal _radius,
                         const bool _cyclic);

		void compute(bwReal _radius, const bool _cyclic) ;
		void clear() { m_points.clear() ; m_normals.clear() ; m_lengths.clear() ; }

        // Given an arbitrary point ("A"), returns the nearest point ("P") on
        // this path.  Also returns, via output arguments, the path tangent at
        // P and a measure of how far A is outside the Pathway's "tube".  Note
        // that a negative distance indicates A is inside the Pathway.
        bwVector3 mapPointToPath (const bwVector3& point, bwVector3& tangent, bwReal& outside);


        // given an arbitrary point, convert it to a distance along the path
        bwReal mapPointToPathDistance (const bwVector3& point);

        // given a distance along the path, convert it to a point on the path
        bwVector3 mapPathDistanceToPoint (bwReal pathDistance);

        // utility methods

        // compute minimum distance from a point to a line segment
        bwReal pointToSegmentDistance (const bwVector3& point,
                                      const bwVector3& ep0,
                                      const bwVector3& ep1);

        // assessor for total path length;
        bwReal getTotalPathLength (void) {return totalPathLength;};

		//
		void addPoint(const bwVector3& point) {
			m_points.push_back(point) ;
		}
    // XXX removed the "private" because it interfered with derived
    // XXX classes later this should all be rewritten and cleaned up
    // private:

        // xxx shouldn't these 5 just be local variables?
        // xxx or are they used to pass secret messages between calls?
        // xxx seems like a bad design
        bwReal segmentLength;
        bwReal segmentProjection;
        bwVector3 local;
        bwVector3 chosen;
        bwVector3 segmentNormal;

		std::vector<bwReal> m_lengths ;
		std::vector<bwVector3> m_normals ;
		std::vector<bwVector3> m_points ; //should be bwPoint3 but ... too much work.

		bwReal totalPathLength;

        int pointCount;
        bwReal radius;
        bool cyclic;

    };

} // namespace OpenSteer


// ----------------------------------------------------------------------------
#endif // OPENSTEER_PATHWAY_H
