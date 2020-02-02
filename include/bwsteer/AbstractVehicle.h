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
// AbstractVehicle: pure virtual base class for generic steerable vehicles
//
// 10-04-04 bk:  put everything into the OpenSteer namespace
// 01-30-03 cwr: created 
//
//
// ----------------------------------------------------------------------------

#ifndef OPENSTEER_ABSTRACTVEHICLE_H
#define OPENSTEER_ABSTRACTVEHICLE_H


#include "LocalSpace.h"


// STL vector containers
#include <vector>


// ----------------------------------------------------------------------------

namespace OpenSteer {


    class AbstractVehicle : public AbstractLocalSpace 
    {
    public:

        // mass (defaults to unity so acceleration=force)
        virtual bwReal mass (void) const = 0;
        virtual bwReal setMass (bwReal) = 0;

        // size of bounding sphere, for obstacle avoidance, etc.
        virtual bwReal radius (void) const = 0;
        virtual bwReal setRadius (bwReal) = 0;

        // velocity of vehicle
        virtual bwVector3 velocity (void) const = 0;

        // speed of vehicle  (may be faster than taking magnitude of velocity)
        virtual bwReal speed (void) const = 0;
        virtual bwReal setSpeed (bwReal) = 0;

        // groups of (pointers to) abstract vehicles, and iterators over them
        typedef std::vector<AbstractVehicle*> group;
        typedef group::const_iterator iterator;    

        // predict position of this vehicle at some time in the future
        // (assumes velocity remains constant)
        virtual bwVector3 predictFuturePosition (bwReal predictionTime) const = 0;

        // ----------------------------------------------------------------------
        // XXX this vehicle-model-specific functionality functionality seems out
        // XXX of place on the abstract base class, but for now it is expedient

        // the maximum steering force this vehicle can apply
        virtual bwReal maxForce (void) const = 0;
        virtual bwReal setMaxForce (bwReal) = 0;

        // the maximum speed this vehicle is allowed to move
        virtual bwReal maxSpeed (void) const = 0;
        virtual bwReal setMaxSpeed (bwReal) = 0;
    };


    // more convenient short names for AbstractVehicle group and iterator
    typedef AbstractVehicle::group AVGroup;
    typedef AbstractVehicle::iterator AVIterator;

} // namespace OpenSteer


// ----------------------------------------------------------------------------
#endif // OPENSTEER_ABSTRACTVEHICLE_H
