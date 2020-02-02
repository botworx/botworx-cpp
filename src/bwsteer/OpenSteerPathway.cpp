#include "stdafx.h"
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


#include <bwsteer/Pathway.h>

// ----------------------------------------------------------------------------
// construct a PolylinePathway given the number of points (vertices),
// an array of points, and a path radius.


OpenSteer::PolylinePathway::PolylinePathway (const int _pointCount,
                                  const bwVector3 _points[],
                                  bwReal _radius,
                                  const bool _cyclic)
{
    initialize (_pointCount, _points, _radius, _cyclic);
}


// ----------------------------------------------------------------------------
// utility for constructors


void 
OpenSteer::PolylinePathway::initialize (const int _pointCount,
                                        const bwVector3 _points[],
                                        bwReal _radius,
                                        const bool _cyclic)
{
    // set data members, allocate arrays
    radius = _radius;
    cyclic = _cyclic;
    pointCount = _pointCount;
    totalPathLength = 0;
    if (cyclic) pointCount++;
    //lengths = new float    [pointCount];
	m_lengths.resize(pointCount) ;
    //points  = new bwVector3 [pointCount];
	m_points.resize(pointCount) ;
    //normals = new bwVector3 [pointCount];
	m_normals.resize(pointCount) ;
    // loop over all points
    for (int i = 0; i < pointCount; i++)
    {
        // copy in point locations, closing cycle when appropriate
        const bool closeCycle = cyclic && (i == pointCount-1);
        const int j = closeCycle ? 0 : i;
        m_points[i] = _points[j];

        // for the end of each segment
        if (i > 0)
        {
            // compute the segment length
            m_normals[i] = m_points[i] - m_points[i-1];
            //lengths[i] = normals[i].length ();
			m_lengths[i] = length(m_normals[i]);

            // find the normalized vector parallel to the segment
            m_normals[i] *= 1 / m_lengths[i];

            // keep running total of segment lengths
            totalPathLength += m_lengths[i];
        }
    }
}
void 
OpenSteer::PolylinePathway::compute(bwReal _radius, const bool _cyclic)
{
    // set data members, allocate arrays
    radius = _radius;
    cyclic = _cyclic;
    //pointCount = _pointCount;
	pointCount = m_points.size() ;
    totalPathLength = 0;
    if (cyclic) pointCount++;
	m_lengths.resize(pointCount) ;
	m_normals.resize(pointCount) ;
    // loop over all points
    for (int i = 0; i < pointCount; i++)
    {
        // copy in point locations, closing cycle when appropriate
        const bool closeCycle = cyclic && (i == pointCount-1);
        const int j = closeCycle ? 0 : i;

        // for the end of each segment
        if (i > 0)
        {
            // compute the segment length
            m_normals[i] = m_points[i] - m_points[i-1];
            //lengths[i] = normals[i].length ();
			m_lengths[i] = length(m_normals[i]);

            // find the normalized vector parallel to the segment
            m_normals[i] *= 1 / m_lengths[i];

            // keep running total of segment lengths
            totalPathLength += m_lengths[i];
        }
    }
}

// ----------------------------------------------------------------------------
// Given an arbitrary point ("A"), returns the nearest point ("P") on
// this path.  Also returns, via output arguments, the path tangent at
// P and a measure of how far A is outside the Pathway's "tube".  Note
// that a negative distance indicates A is inside the Pathway.


bwVector3 
OpenSteer::PolylinePathway::mapPointToPath (const bwVector3& point,
                                            bwVector3& tangent,
                                            bwReal& outside)
{
    bwReal d;
    bwReal minDistance = FLT_MAX;
    bwVector3 onPath;

    // loop over all segments, find the one nearest to the given point
    for (int i = 1; i < pointCount; i++)
    {
        segmentLength = m_lengths[i];
        segmentNormal = m_normals[i];
        d = pointToSegmentDistance (point, m_points[i-1], m_points[i]);
        if (d < minDistance)
        {
            minDistance = d;
            onPath = chosen;
            tangent = segmentNormal;
        }
    }

    // measure how far original point is outside the Pathway's "tube"
    //outside = bwVector3::distance (onPath, point) - radius;
	outside = distance (onPath, point) - radius;

    // return point on path
    return onPath;
}


// ----------------------------------------------------------------------------
// given an arbitrary point, convert it to a distance along the path


bwReal
OpenSteer::PolylinePathway::mapPointToPathDistance (const bwVector3& point)
{
    bwReal d;
    bwReal minDistance = FLT_MAX;
    bwReal segmentLengthTotal = 0;
    bwReal pathDistance = 0;

    for (int i = 1; i < pointCount; i++)
    {
        segmentLength = m_lengths[i];
        segmentNormal = m_normals[i];
        d = pointToSegmentDistance (point, m_points[i-1], m_points[i]);
        if (d < minDistance)
        {
            minDistance = d;
            pathDistance = segmentLengthTotal + segmentProjection;
        }
        segmentLengthTotal += segmentLength;
    }

    // return distance along path of onPath point
    return pathDistance;
}


// ----------------------------------------------------------------------------
// given a distance along the path, convert it to a point on the path


bwVector3 
OpenSteer::PolylinePathway::mapPathDistanceToPoint (bwReal pathDistance)
{
    // clip or wrap given path distance according to cyclic flag
    bwReal remaining = pathDistance;
    if (cyclic)
    {
        remaining = (bwReal ) fmod (pathDistance, totalPathLength);
    }
    else
    {
        if (pathDistance < 0) return m_points[0];
        if (pathDistance >= totalPathLength) return m_points[pointCount-1];
    }

    // step through segments, subtracting off segment lengths until
    // locating the segment that contains the original pathDistance.
    // Interpolate along that segment to find 3d point value to return.
    bwVector3 result;
    for (int i = 1; i < pointCount; i++)
    {
        segmentLength = m_lengths[i];
        if (segmentLength < remaining)
        {
            remaining -= segmentLength;
        }
        else
        {
            bwReal ratio = remaining / segmentLength;
            result = interpolate (ratio, m_points[i-1], m_points[i]);
            break;
        }
    }
    return result;
}


// ----------------------------------------------------------------------------
// computes distance from a point to a line segment 
//
// (I considered moving this to the vector library, but its too
// tangled up with the internal state of the PolylinePathway instance)


bwReal 
OpenSteer::PolylinePathway::pointToSegmentDistance (const bwVector3& point,
                                                    const bwVector3& ep0,
                                                    const bwVector3& ep1)
{
    // convert the test point to be "local" to ep0
    local = point - ep0;

    // find the projection of "local" onto "segmentNormal"
    //segmentProjection = segmentNormal.dot (local);
	segmentProjection = dot(segmentNormal,local) ;

    // handle boundary cases: when projection is not on segment, the
    // nearest point is one of the endpoints of the segment
    if (segmentProjection < 0)
    {
        chosen = ep0;
        segmentProjection = 0;
        //return bwVector3::distance (point, ep0);
		return distance (point, ep0);
    }
    if (segmentProjection > segmentLength)
    {
        chosen = ep1;
        segmentProjection = segmentLength;
        //return bwVector3::distance (point, ep1);
		return distance (point, ep1);
    }

    // otherwise nearest point is projection point on segment
    chosen = segmentNormal * bwReal(segmentProjection) ;
    chosen +=  ep0;
    //return bwVector3::distance (point, chosen);
	return distance (point, chosen);
}


// ----------------------------------------------------------------------------
