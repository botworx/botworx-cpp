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
// SteerLibraryMixin
//
// This mixin (class with templated superclass) adds the "steering library"
// functionality to a given base class.  SteerLibraryMixin assumes its base
// class supports the AbstractVehicle interface.
//
// 10-04-04 bk:  put everything into the OpenSteer namespace
// 02-06-03 cwr: create mixin (from "SteerMass")
// 06-03-02 cwr: removed TS dependencies
// 11-21-01 cwr: created
//
//
// ----------------------------------------------------------------------------


#ifndef OPENSTEER_STEERLIBRARY_H
#define OPENSTEER_STEERLIBRARY_H

#include "AbstractVehicle.h"
#include "Pathway.h"
#include "Obstacle.h"

namespace OpenSteer {

    // ----------------------------------------------------------------------------


    template <class Super>
    class SteerLibraryMixin : public Super
    {
    public:
        using Super::velocity;
        using Super::maxSpeed;
        using Super::speed;
        using Super::radius;
        using Super::maxForce;
        using Super::forward;
        using Super::position;
        using Super::side;
        using Super::up;
        using Super::predictFuturePosition;
    public:

        // Constructor: initializes state
        SteerLibraryMixin ()
        {
            // set inital state
            reset ();
        }

        // reset state
        void reset (void)
        {
            // initial state of wander behavior
            WanderSide = 0;
            WanderUp = 0;

            // default to non-gaudyPursuitAnnotation
            gaudyPursuitAnnotation = false;
        }

        // -------------------------------------------------- steering behaviors

        // Wander behavior
		bwReal WanderSide;
		bwReal WanderUp;
        bwVector3 steerForWander (bwReal dt);

        // Seek behavior
        bwVector3 steerForSeek (const bwVector3& target);

        // Flee behavior
        bwVector3 steerForFlee (const bwVector3& target);

        // xxx proposed, experimental new seek/flee [cwr 9-16-02]
        bwVector3 xxxsteerForFlee (const bwVector3& target);
        bwVector3 xxxsteerForSeek (const bwVector3& target);

        // Path Following behaviors
        bwVector3 steerToFollowPath (const int direction,
                                bwReal predictionTime,
                                Pathway& path);
        bwVector3 steerToStayOnPath (bwReal predictionTime, Pathway& path);

        // ------------------------------------------------------------------------
        // Obstacle Avoidance behavior
        //
        // Returns a steering force to avoid a given obstacle.  The purely
        // lateral steering force will turn our vehicle towards a silhouette edge
        // of the obstacle.  Avoidance is required when (1) the obstacle
        // intersects the vehicle's current path, (2) it is in front of the
        // vehicle, and (3) is within minTimeToCollision seconds of travel at the
        // vehicle's current velocity.  Returns a zero vector value (bwVector3::zero)
        // when no avoidance is required.


        bwVector3 steerToAvoidObstacle (bwReal minTimeToCollision,
                                   const Obstacle& obstacle);


        // avoids all obstacles in an ObstacleGroup

        bwVector3 steerToAvoidObstacles (bwReal minTimeToCollision,
                                    const ObstacleGroup& obstacles);


        // ------------------------------------------------------------------------
        // Unaligned collision avoidance behavior: avoid colliding with other
        // nearby vehicles moving in unconstrained directions.  Determine which
        // (if any) other other vehicle we would collide with first, then steers
        // to avoid the site of that potential collision.  Returns a steering
        // force vector, which is zero length if there is no impending collision.


        bwVector3 steerToAvoidNeighbors (bwReal minTimeToCollision,
                                    const AVGroup& others);


        // Given two vehicles, based on their current positions and velocities,
        // determine the time until nearest approach
        bwReal predictNearestApproachTime (AbstractVehicle& other);

        // Given the time until nearest approach (predictNearestApproachTime)
        // determine position of each vehicle at that time, and the distance
        // between them
        bwReal computeNearestApproachPositions (AbstractVehicle& other,
                                               bwReal time);


        /// XXX globals only for the sake of graphical annotation
        bwVector3 hisPositionAtNearestApproach;
        bwVector3 ourPositionAtNearestApproach;


        // ------------------------------------------------------------------------
        // avoidance of "close neighbors" -- used only by steerToAvoidNeighbors
        //
        // XXX  Does a hard steer away from any other agent who comes withing a
        // XXX  critical distance.  Ideally this should be replaced with a call
        // XXX  to steerForSeparation.


        bwVector3 steerToAvoidCloseNeighbors (bwReal minSeparationDistance,
                                         const AVGroup& others);


        // ------------------------------------------------------------------------
        // used by boid behaviors


        bool inBoidNeighborhood (const AbstractVehicle& other,
                                 bwReal minDistance,
                                 bwReal maxDistance,
                                 bwReal cosMaxAngle);


        // ------------------------------------------------------------------------
        // Separation behavior -- determines the direction away from nearby boids


        bwVector3 steerForSeparation (bwReal maxDistance,
                                 bwReal cosMaxAngle,
                                 const AVGroup& flock);


        // ------------------------------------------------------------------------
        // Alignment behavior

        bwVector3 steerForAlignment (bwReal maxDistance,
                                bwReal cosMaxAngle,
                                const AVGroup& flock);


        // ------------------------------------------------------------------------
        // Cohesion behavior


        bwVector3 steerForCohesion (bwReal maxDistance,
                               bwReal cosMaxAngle,
                               const AVGroup& flock);


		//TODO:addin
		bwVector3 xxxsteerForPursuit (const bwVector3& quarryPos, const bwVector3& quarryVel,
                 bwReal maxPredictionTime = FLT_MAX) ;
        // ------------------------------------------------------------------------
        // pursuit of another vehicle (& version with ceiling on prediction time)
        bwVector3 steerForPursuit (const AbstractVehicle& quarry);

        bwVector3 steerForPursuit (const AbstractVehicle& quarry,
                              bwReal maxPredictionTime);

        // for annotation
        bool gaudyPursuitAnnotation;


        // ------------------------------------------------------------------------
        // evasion of another vehicle


        bwVector3 steerForEvasion (const AbstractVehicle& menace,
                              bwReal maxPredictionTime);


        // ------------------------------------------------------------------------
        // tries to maintain a given speed, returns a maxForce-clipped steering
        // force along the forward/backward axis


        bwVector3 steerForTargetSpeed (bwReal targetSpeed);


        // ----------------------------------------------------------- utilities
        // XXX these belong somewhere besides the steering library
        // XXX above AbstractVehicle, below SimpleVehicle
        // XXX ("utility vehicle"?)

        // xxx cwr experimental 9-9-02 -- names OK?
        bool isAhead (const bwVector3& target) const {return isAhead (target, 0.707f);};
        bool isAside (const bwVector3& target) const {return isAside (target, 0.707f);};
        bool isBehind (const bwVector3& target) const {return isBehind (target, -0.707f);};

        bool isAhead (const bwVector3& target, bwReal cosThreshold) const
        {
            const bwVector3 targetDirection = (target - position ()).normalize ();
            return forward().dot(targetDirection) > cosThreshold;
        };
        bool isAside (const bwVector3& target, bwReal cosThreshold) const
        {
            const bwVector3 targetDirection = (target - position ()).normalize ();
            const bwReal dp = forward().dot(targetDirection);
            return (dp < cosThreshold) && (dp > -cosThreshold);
        };
        bool isBehind (const bwVector3& target, bwReal cosThreshold) const
        {
            const bwVector3 targetDirection = (target - position()).normalize ();
            return forward().dot(targetDirection) < cosThreshold;
        };


        // xxx cwr 9-6-02 temporary to support old code
        typedef struct {
            int intersect;
            bwReal distance;
            bwVector3 surfacePoint;
            bwVector3 surfaceNormal;
            SphericalObstacle* obstacle;
        } PathIntersection;

        // xxx experiment cwr 9-6-02
        void findNextIntersectionWithSphere (SphericalObstacle& obs,
                                             PathIntersection& intersection);


        // ------------------------------------------------ graphical annotation
        // (parameter names commented out to prevent compiler warning from "-W")


        // called when steerToAvoidObstacles decides steering is required
        // (default action is to do nothing, layered classes can overload it)
        virtual void annotateAvoidObstacle (bwReal /*minDistanceToCollision*/)
        {
        }

        // called when steerToFollowPath decides steering is required
        // (default action is to do nothing, layered classes can overload it)
        virtual void annotatePathFollowing (const bwVector3& /*future*/,
                                            const bwVector3& /*onPath*/,
                                            const bwVector3& /*target*/,
                                            bwReal /*outside*/)
        {
        }

        // called when steerToAvoidCloseNeighbors decides steering is required
        // (default action is to do nothing, layered classes can overload it)
        virtual void annotateAvoidCloseNeighbor (const AbstractVehicle& /*other*/,
                                                 bwReal /*additionalDistance*/)
        {
        }

        // called when steerToAvoidNeighbors decides steering is required
        // (default action is to do nothing, layered classes can overload it)
        virtual void annotateAvoidNeighbor (const AbstractVehicle& /*threat*/,
                                            bwReal /*steer*/,
                                            const bwVector3& /*ourFuture*/,
                                            const bwVector3& /*threatFuture*/)
        {
        }
    };


} // namespace OpenSteer

// ----------------------------------------------------------------------------


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForWander (bwReal dt)
{
    // random walk WanderSide and WanderUp between -1 and +1
    const bwReal speed = 12 * dt; // maybe this (12) should be an argument?
    WanderSide = scalarRandomWalk (WanderSide, speed, -1, +1);
    WanderUp   = scalarRandomWalk (WanderUp,   speed, -1, +1);

    // return a pure lateral steering vector: (+/-Side) + (+/-Up)
    return (side() * WanderSide) + (up() * WanderUp);
}


// ----------------------------------------------------------------------------
// Seek behavior


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForSeek (const bwVector3& target)
{
    const bwVector3 desiredVelocity = target - position();
    return desiredVelocity - velocity();
}


// ----------------------------------------------------------------------------
// Flee behavior


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForFlee (const bwVector3& target)
{
    const bwVector3 desiredVelocity = position() - target;
    return desiredVelocity - velocity();
}


// ----------------------------------------------------------------------------
// xxx proposed, experimental new seek/flee [cwr 9-16-02]


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
xxxsteerForFlee (const bwVector3& target)
{
    const bwVector3 offset = position() - target;
	const bwVector3 desiredVelocity = truncateLength (offset, maxSpeed ()); //xxxnew
    return desiredVelocity - velocity();
}


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
xxxsteerForSeek (const bwVector3& target)
{
    const bwVector3 offset = target - position();
	const bwVector3 desiredVelocity = truncateLength (offset, maxSpeed ()); //xxxnew
    return desiredVelocity - velocity();
}


// ----------------------------------------------------------------------------
// Path Following behaviors


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerToStayOnPath (bwReal predictionTime, Pathway& path)
{
    // predict our future position
    const bwVector3 futurePosition = predictFuturePosition (predictionTime);

    // find the point on the path nearest the predicted future position
    bwVector3 tangent;
    bwReal outside;
    const bwVector3 onPath = path.mapPointToPath (futurePosition,
                                             tangent,     // output argument
                                             outside);    // output argument

    if (outside < 0)
    {
        // our predicted future position was in the path,
        // return zero steering.
        return bwVector3();
    }
    else
    {
        // our predicted future position was outside the path, need to
        // steer towards it.  Use onPath projection of futurePosition
        // as seek target
        annotatePathFollowing (futurePosition, onPath, onPath, outside);
        return steerForSeek (onPath);
    }
}


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerToFollowPath (const int direction,
                   bwReal predictionTime,
                   Pathway& path)
{
    // our goal will be offset from our path distance by this amount
    const bwReal pathDistanceOffset = direction * predictionTime * speed();

    // predict our future position
    const bwVector3 futurePosition = predictFuturePosition (predictionTime);

    // measure distance along path of our current and predicted positions
    const bwReal nowPathDistance =
        path.mapPointToPathDistance (position ());
    const bwReal futurePathDistance =
        path.mapPointToPathDistance (futurePosition);

    // are we facing in the correction direction?
    const bool rightway = ((pathDistanceOffset > 0) ?
                           (nowPathDistance < futurePathDistance) :
                           (nowPathDistance > futurePathDistance));

    // find the point on the path nearest the predicted future position
    // XXX need to improve calling sequence, maybe change to return a
    // XXX special path-defined object which includes two bwVector3s and a
    // XXX bool (onPath,tangent (ignored), withinPath)
    bwVector3 tangent;
    bwReal outside;
    const bwVector3 onPath = path.mapPointToPath (futurePosition,
                                             // output arguments:
                                             tangent,
                                             outside);

    // no steering is required if (a) our future position is inside
    // the path tube and (b) we are facing in the correct direction
    if ((outside < 0) && rightway)
    {
        // all is well, return zero steering
        return bwVector3();
    }
    else
    {
        // otherwise we need to steer towards a target point obtained
        // by adding pathDistanceOffset to our current path position

        bwReal targetPathDistance = nowPathDistance + pathDistanceOffset;
        bwVector3 target = path.mapPathDistanceToPoint (targetPathDistance);

        annotatePathFollowing (futurePosition, onPath, target, outside);

        // return steering to seek target on path
        return steerForSeek (target);
    }
}


// ----------------------------------------------------------------------------
// Obstacle Avoidance behavior
//
// Returns a steering force to avoid a given obstacle.  The purely lateral
// steering force will turn our vehicle towards a silhouette edge of the
// obstacle.  Avoidance is required when (1) the obstacle intersects the
// vehicle's current path, (2) it is in front of the vehicle, and (3) is
// within minTimeToCollision seconds of travel at the vehicle's current
// velocity.  Returns a zero vector value (bwVector3::zero) when no avoidance is
// required.
//
// XXX The current (4-23-03) scheme is to dump all the work on the various
// XXX Obstacle classes, making them provide a "steer vehicle to avoid me"
// XXX method.  This may well change.
//
// XXX 9-12-03: this routine is probably obsolete: its name is too close to
// XXX the new steerToAvoidObstacles and the arguments are reversed
// XXX (perhaps there should be another version of steerToAvoidObstacles
// XXX whose second arg is "const Obstacle& obstacle" just in case we want
// XXX to avoid a non-grouped obstacle)

template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerToAvoidObstacle (bwReal minTimeToCollision,
                      const Obstacle& obstacle)
{
    const bwVector3 avoidance = obstacle.steerToAvoid (*this, minTimeToCollision);

    // XXX more annotation modularity problems (assumes spherical obstacle)
    if (avoidance != bwVector3())
        annotateAvoidObstacle (minTimeToCollision * speed());

    return avoidance;
}


// this version avoids all of the obstacles in an ObstacleGroup
//
// XXX 9-12-03: note this does NOT use the Obstacle::steerToAvoid protocol
// XXX like the older steerToAvoidObstacle does/did.  It needs to be fixed

template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerToAvoidObstacles (bwReal minTimeToCollision,
                       const ObstacleGroup& obstacles)
{
    bwVector3 avoidance;
    PathIntersection nearest, next;
    const bwReal minDistanceToCollision = minTimeToCollision * speed();

    next.intersect = false;
    nearest.intersect = false;

    // test all obstacles for intersection with my forward axis,
    // select the one whose point of intersection is nearest
    for (ObstacleIterator o = obstacles.begin(); o != obstacles.end(); o++)
    {
        // xxx this should be a generic call on Obstacle, rather than
        // xxx this code which presumes the obstacle is spherical
        findNextIntersectionWithSphere ((SphericalObstacle&)**o, next);

        if ((nearest.intersect == false) ||
            ((next.intersect != false) &&
             (next.distance < nearest.distance)))
            nearest = next;
    }

    // when a nearest intersection was found
    if ((nearest.intersect != false) &&
        (nearest.distance < minDistanceToCollision))
    {
        // show the corridor that was checked for collisions
        annotateAvoidObstacle (minDistanceToCollision);

        // compute avoidance steering force: take offset from obstacle to me,
        // take the component of that which is lateral (perpendicular to my
        // forward direction), set length to maxForce, add a bit of forward
        // component (in capture the flag, we never want to slow down)
        const bwVector3 offset = position() - nearest.obstacle->center;
		avoidance = perpendicularComponent (offset, forward());
		normalize (avoidance );
        avoidance *= maxForce ();
        avoidance += forward() * bwReal(maxForce () * 0.75f) ;
    }

    return avoidance;
}


// ----------------------------------------------------------------------------
// Unaligned collision avoidance behavior: avoid colliding with other nearby
// vehicles moving in unconstrained directions.  Determine which (if any)
// other other vehicle we would collide with first, then steers to avoid the
// site of that potential collision.  Returns a steering force vector, which
// is zero length if there is no impending collision.


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerToAvoidNeighbors (bwReal minTimeToCollision,
                       const AVGroup& others)
{
    // first priority is to prevent immediate interpenetration
    const bwVector3 separation = steerToAvoidCloseNeighbors (0, others);
    //if (separation != bwVector3::zero) return separation;
	if (separation != bwVector3()) return separation;

    // otherwise, go on to consider potential future collisions
    bwReal steer = 0;
    AbstractVehicle* threat = NULL;

    // Time (in seconds) until the most immediate collision threat found
    // so far.  Initial value is a threshold: don't look more than this
    // many frames into the future.
    bwReal minTime = minTimeToCollision;

    // xxx solely for annotation
    bwVector3 xxxThreatPositionAtNearestApproach;
    bwVector3 xxxOurPositionAtNearestApproach;

    // for each of the other vehicles, determine which (if any)
    // pose the most immediate threat of collision.
    for (AVIterator i = others.begin(); i != others.end(); i++)
    {
        AbstractVehicle& other = **i;
        if (&other != this)
        {
            // avoid when future positions are this close (or less)
            const bwReal collisionDangerThreshold = radius() * 2;

            // predicted time until nearest approach of "this" and "other"
            const bwReal time = predictNearestApproachTime (other);

            // If the time is in the future, sooner than any other
            // threatened collision...
            if ((time >= 0) && (time < minTime))
            {
                // if the two will be close enough to collide,
                // make a note of it
                if (computeNearestApproachPositions (other, time)
                    < collisionDangerThreshold)
                {
                    minTime = time;
                    threat = &other;
                    xxxThreatPositionAtNearestApproach
                        = hisPositionAtNearestApproach;
                    xxxOurPositionAtNearestApproach
                        = ourPositionAtNearestApproach;
                }
            }
        }
    }

    // if a potential collision was found, compute steering to avoid
    if (threat != NULL)
    {
        // parallel: +1, perpendicular: 0, anti-parallel: -1
		bwReal parallelness = dot(forward(), threat->forward());
        bwReal angle = 0.707f;

        if (parallelness < -angle)
        {
            // anti-parallel "head on" paths:
            // steer away from future threat position
            bwVector3 offset = xxxThreatPositionAtNearestApproach - position();
			bwReal sideDot = dot(offset, side());
            steer = (sideDot > 0) ? -1.0f : 1.0f;
        }
        else
        {
            if (parallelness > angle)
            {
                // parallel paths: steer away from threat
                bwVector3 offset = threat->position() - position();
				bwReal sideDot = dot(offset, side());
                steer = (sideDot > 0) ? -1.0f : 1.0f;
            }
            else
            {
                // perpendicular paths: steer behind threat
                // (only the slower of the two does this)
                if (threat->speed() <= speed())
                {
					bwReal sideDot = dot(side(), threat->velocity());
                    steer = (sideDot > 0) ? -1.0f : 1.0f;
                }
            }
        }

        annotateAvoidNeighbor (*threat,
                               steer,
                               xxxOurPositionAtNearestApproach,
                               xxxThreatPositionAtNearestApproach);
    }

    return side() * bwReal(steer) ;
}



// Given two vehicles, based on their current positions and velocities,
// determine the time until nearest approach
//
// XXX should this return zero if they are already in contact?

template<class Super>
bwReal
OpenSteer::SteerLibraryMixin<Super>::
predictNearestApproachTime (AbstractVehicle& other)
{
    // imagine we are at the origin with no velocity,
    // compute the relative velocity of the other vehicle
    const bwVector3 myVelocity = velocity();
    const bwVector3 otherVelocity = other.velocity();
    const bwVector3 relVelocity = otherVelocity - myVelocity;
	const bwReal relSpeed = length(relVelocity);

    // for parallel paths, the vehicles will always be at the same distance,
    // so return 0 (aka "now") since "there is no time like the present"
    if (relSpeed == 0) return 0;

    // Now consider the path of the other vehicle in this relative
    // space, a line defined by the relative position and velocity.
    // The distance from the origin (our vehicle) to that line is
    // the nearest approach.

    // Take the unit tangent along the other vehicle's path
    const bwVector3 relTangent = relVelocity / relSpeed;

    // find distance from its path to origin (compute offset from
    // other to us, find length of projection onto path)
    const bwVector3 relPosition = position() - other.position();
	const bwReal projection = dot(relTangent, relPosition);

    return projection / relSpeed;
}


// Given the time until nearest approach (predictNearestApproachTime)
// determine position of each vehicle at that time, and the distance
// between them


template<class Super>
bwReal
OpenSteer::SteerLibraryMixin<Super>::
computeNearestApproachPositions (AbstractVehicle& other,
                                 bwReal time)
{
    const bwVector3    myTravel = forward () * bwReal(speed () * time) ;
    const bwVector3 otherTravel = other.forward () * bwReal(other.speed () * time) ;

    const bwVector3    myFinal = position () + myTravel;
    const bwVector3 otherFinal = other.position () + otherTravel;

    // xxx for annotation
    ourPositionAtNearestApproach = myFinal;
    hisPositionAtNearestApproach = otherFinal;

    //return bwVector3::distance (myFinal, otherFinal);
	return distance (myFinal, otherFinal);
}



// ----------------------------------------------------------------------------
// avoidance of "close neighbors" -- used only by steerToAvoidNeighbors
//
// XXX  Does a hard steer away from any other agent who comes withing a
// XXX  critical distance.  Ideally this should be replaced with a call
// XXX  to steerForSeparation.


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerToAvoidCloseNeighbors (bwReal minSeparationDistance,
                            const AVGroup& others)
{
    // for each of the other vehicles...
    for (AVIterator i = others.begin(); i != others.end(); i++)
    {
        AbstractVehicle& other = **i;
        if (&other != this)
        {
            const bwReal sumOfRadii = radius() + other.radius();
            const bwReal minCenterToCenter = minSeparationDistance + sumOfRadii;
            const bwVector3 offset = other.position() - position();
			const bwReal currentDistance = length(offset);

            if (currentDistance < minCenterToCenter)
            {
                annotateAvoidCloseNeighbor (other, minSeparationDistance);
				return perpendicularComponent ((-offset), forward());
            }
        }
    }

    // otherwise return zero
	return bwVector3() ;
}


// ----------------------------------------------------------------------------
// used by boid behaviors: is a given vehicle within this boid's neighborhood?


template<class Super>
bool
OpenSteer::SteerLibraryMixin<Super>::
inBoidNeighborhood (const AbstractVehicle& other,
                    bwReal minDistance,
                    bwReal maxDistance,
                    bwReal cosMaxAngle)
{
    if (&other == this)
    {
        return false;
    }
    else
    {
        const bwVector3 offset = other.position() - position();
		const bwReal distanceSquared = lengthSquared (offset);

        // definitely in neighborhood if inside minDistance sphere
        if (distanceSquared < (minDistance * minDistance))
        {
            return true;
        }
        else
        {
            // definitely not in neighborhood if outside maxDistance sphere
            if (distanceSquared > (maxDistance * maxDistance))
            {
                return false;
            }
            else
            {
                // otherwise, test angular offset from forward axis
				const bwVector3 unitOffset = offset / gmtl::Math::sqrt (distanceSquared);
				const bwReal forwardness = dot (forward(), unitOffset);
                return forwardness > cosMaxAngle;
            }
        }
    }
}


// ----------------------------------------------------------------------------
// Separation behavior: steer away from neighbors


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForSeparation (bwReal maxDistance,
                    bwReal cosMaxAngle,
                    const AVGroup& flock)
{
    // steering accumulator and count of neighbors, both initially zero
    bwVector3 steering;
    int neighbors = 0;

    // for each of the other vehicles...
    for (AVIterator other = flock.begin(); other != flock.end(); other++)
    {
        if (inBoidNeighborhood (**other, radius()*3, maxDistance, cosMaxAngle))
        {
            // add in steering contribution
            // (opposite of the offset direction, divided once by distance
            // to normalize, divided another time to get 1/d falloff)
            const bwVector3 offset = (**other).position() - position();
			const bwReal distanceSquared = dot(offset, offset);
            steering += (offset / -distanceSquared);

            // count neighbors
            neighbors++;
        }
    }

    // divide by neighbors, then normalize to pure direction
    //if (neighbors > 0) steering = (steering / (bwReal)neighbors).normalize();
	bwVector3 temp = (steering / (bwReal)neighbors) ;
	normalize(temp) ;
	if (neighbors > 0) steering = temp ;

    return steering;
}


// ----------------------------------------------------------------------------
// Alignment behavior: steer to head in same direction as neighbors


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForAlignment (bwReal maxDistance,
                   bwReal cosMaxAngle,
                   const AVGroup& flock)
{
    // steering accumulator and count of neighbors, both initially zero
    bwVector3 steering;
    int neighbors = 0;

    // for each of the other vehicles...
    for (AVIterator other = flock.begin(); other != flock.end(); other++)
    {
        if (inBoidNeighborhood (**other, radius()*3, maxDistance, cosMaxAngle))
        {
            // accumulate sum of neighbor's heading
            steering += (**other).forward();

            // count neighbors
            neighbors++;
        }
    }

    // divide by neighbors, subtract off current heading to get error-
    // correcting direction, then normalize to pure direction
    //if (neighbors > 0) steering = ((steering / (bwReal)neighbors) - forward()).normalize();
	bwVector3 temp = (steering / (bwReal)neighbors) - forward() ;
	normalize(temp) ;
	if (neighbors > 0) steering = temp ;

    return steering;
}


// ----------------------------------------------------------------------------
// Cohesion behavior: to to move toward center of neighbors



template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForCohesion (bwReal maxDistance,
                  bwReal cosMaxAngle,
                  const AVGroup& flock)
{
    // steering accumulator and count of neighbors, both initially zero
    bwVector3 steering;
    int neighbors = 0;

    // for each of the other vehicles...
    for (AVIterator other = flock.begin(); other != flock.end(); other++)
    {
        if (inBoidNeighborhood (**other, radius()*3, maxDistance, cosMaxAngle))
        {
            // accumulate sum of neighbor's positions
            steering += (**other).position();

            // count neighbors
            neighbors++;
        }
    }

    // divide by neighbors, subtract off current position to get error-
    // correcting direction, then normalize to pure direction
    //if (neighbors > 0) steering = ((steering / (bwReal)neighbors) - position()).normalize();
	bwVector3 temp = (steering / (bwReal)neighbors) - position() ;
	normalize(temp) ;
	if (neighbors > 0) steering = temp ;

    return steering;
}

/*TODO:addin*/
template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
xxxsteerForPursuit (const bwVector3& quarryPos, const bwVector3& quarryVel,
                 bwReal maxPredictionTime)
{
    // offset from this to quarry, that distance, unit vector toward quarry
    const bwVector3 offset = quarryPos - position();
	const bwReal distance = length (offset);
    const bwVector3 unitOffset = offset / distance;

    // how parallel are the paths of "this" and the quarry
    // (1 means parallel, 0 is pependicular, -1 is anti-parallel)
    //const float parallelness = forward().dot (quarryForward);
	//const float parallelness = forward().dot (quarryVel.normalize());
	bwVector3 temp = quarryVel ;
	normalize(temp) ;
	const bwReal parallelness = dot (forward(), temp);

    // how "forward" is the direction to the quarry
    // (1 means dead ahead, 0 is directly to the side, -1 is straight back)
    //const float forwardness = forward().dot (unitOffset);
	const bwReal forwardness = dot (forward(), unitOffset);

    const bwReal directTravelTime = distance / speed ();
    const int f = intervalComparison (forwardness,  -0.707f, 0.707f);
    const int p = intervalComparison (parallelness, -0.707f, 0.707f);

    bwReal timeFactor = 0; // to be filled in below
    //TODO:fixme:seenote:bwVector3 color;           // to be filled in below (xxx just for debugging)

    // Break the pursuit into nine cases, the cross product of the
    // quarry being [ahead, aside, or behind] us and heading
    // [parallel, perpendicular, or anti-parallel] to us.
    switch (f)
    {
    case +1:
        switch (p)
        {
        case +1:          // ahead, parallel
            timeFactor = 4;
            //TODO:fixme:seenote:color = gBlack;
            break;
        case 0:           // ahead, perpendicular
            timeFactor = 1.8f;
            //TODO:fixme:seenote:color = gGray50;
            break;
        case -1:          // ahead, anti-parallel
            timeFactor = 0.85f;
            //TODO:fixme:seenote:color = gWhite;
            break;
        }
        break;
    case 0:
        switch (p)
        {
        case +1:          // aside, parallel
            timeFactor = 1;
            //TODO:fixme:seenote:color = gRed;
            break;
        case 0:           // aside, perpendicular
            timeFactor = 0.8f;
            //TODO:fixme:seenote:color = gYellow;
            break;
        case -1:          // aside, anti-parallel
            timeFactor = 4;
            //TODO:fixme:seenote:color = gGreen;
            break;
        }
        break;
    case -1:
        switch (p)
        {
        case +1:          // behind, parallel
            timeFactor = 0.5f;
            //TODO:fixme:seenote:color= gCyan;
            break;
        case 0:           // behind, perpendicular
            timeFactor = 2;
            //TODO:fixme:seenote:color= gBlue;
            break;
        case -1:          // behind, anti-parallel
            timeFactor = 2;
            //TODO:fixme:seenote:color = gMagenta;
            break;
        }
        break;
    }

    // estimated time until intercept of quarry
    const bwReal et = directTravelTime * timeFactor;

    // xxx experiment, if kept, this limit should be an argument
    const bwReal etl = (et > maxPredictionTime) ? maxPredictionTime : et;

    // estimated position of quarry at intercept
    //const bwVector3 target = quarry.predictFuturePosition (etl);
	const bwVector3 target = quarryPos + (quarryVel * etl);

    // annotation
    /*TODO:fixme:seenote:annotationLine (position(),
                    target,
                    gaudyPursuitAnnotation ? color : gGray40);*/

    return steerForSeek (target);
}

// ----------------------------------------------------------------------------
// pursuit of another vehicle (& version with ceiling on prediction time)
template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForPursuit (const AbstractVehicle& quarry)
{
    return steerForPursuit (quarry, FLT_MAX);
}

/*TODO:fixme:note
	Authors original version depends on AnnotationMixin!  Had to modify.
*/
template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForPursuit (const AbstractVehicle& quarry,
                 bwReal maxPredictionTime)
{
    // offset from this to quarry, that distance, unit vector toward quarry
    const bwVector3 offset = quarry.position() - position();
	const bwReal distance = length (offset);
    const bwVector3 unitOffset = offset / distance;

    // how parallel are the paths of "this" and the quarry
    // (1 means parallel, 0 is pependicular, -1 is anti-parallel)
	const bwReal parallelness = dot (forward(), quarry.forward());

    // how "forward" is the direction to the quarry
    // (1 means dead ahead, 0 is directly to the side, -1 is straight back)
	const bwReal forwardness = dot (forward(), unitOffset);
	//TODO:fix for div by 0
	bwReal s = speed ();
	if(s == 0) s = .001f ;
	const bwReal directTravelTime = distance / s ;
    const int f = intervalComparison (forwardness,  -0.707f, 0.707f);
    const int p = intervalComparison (parallelness, -0.707f, 0.707f);

    bwReal timeFactor = 0; // to be filled in below
    //TODO:fixme:seenote:bwVector3 color;           // to be filled in below (xxx just for debugging)

    // Break the pursuit into nine cases, the cross product of the
    // quarry being [ahead, aside, or behind] us and heading
    // [parallel, perpendicular, or anti-parallel] to us.
    switch (f)
    {
    case +1:
        switch (p)
        {
        case +1:          // ahead, parallel
            timeFactor = 4;
            //TODO:fixme:seenote:color = gBlack;
            break;
        case 0:           // ahead, perpendicular
            timeFactor = 1.8f;
            //TODO:fixme:seenote:color = gGray50;
            break;
        case -1:          // ahead, anti-parallel
            timeFactor = 0.85f;
            //TODO:fixme:seenote:color = gWhite;
            break;
        }
        break;
    case 0:
        switch (p)
        {
        case +1:          // aside, parallel
            timeFactor = 1;
            //TODO:fixme:seenote:color = gRed;
            break;
        case 0:           // aside, perpendicular
            timeFactor = 0.8f;
            //TODO:fixme:seenote:color = gYellow;
            break;
        case -1:          // aside, anti-parallel
            timeFactor = 4;
            //TODO:fixme:seenote:color = gGreen;
            break;
        }
        break;
    case -1:
        switch (p)
        {
        case +1:          // behind, parallel
            timeFactor = 0.5f;
            //TODO:fixme:seenote:color= gCyan;
            break;
        case 0:           // behind, perpendicular
            timeFactor = 2;
            //TODO:fixme:seenote:color= gBlue;
            break;
        case -1:          // behind, anti-parallel
            timeFactor = 2;
            //TODO:fixme:seenote:color = gMagenta;
            break;
        }
        break;
    }

    // estimated time until intercept of quarry
    const bwReal et = directTravelTime * timeFactor;

    // xxx experiment, if kept, this limit should be an argument
    const bwReal etl = (et > maxPredictionTime) ? maxPredictionTime : et;

    // estimated position of quarry at intercept
    const bwVector3 target = quarry.predictFuturePosition (etl);

    // annotation
    /*TODO:fixme:seenote:annotationLine (position(),
                    target,
                    gaudyPursuitAnnotation ? color : gGray40);*/

    return steerForSeek (target);
}

// ----------------------------------------------------------------------------
// evasion of another vehicle


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForEvasion (const AbstractVehicle& menace,
                 bwReal maxPredictionTime)
{
    // offset from this to menace, that distance, unit vector toward menace
    const bwVector3 offset = menace.position() - position;
    const bwReal distance = length(offset);

    const bwReal roughTime = distance / menace.speed();
    const bwReal predictionTime = ((roughTime > maxPredictionTime) ?
                                  maxPredictionTime :
                                  roughTime);

    const bwVector3 target = menace.predictFuturePosition (predictionTime);

    return steerForFlee (target);
}


// ----------------------------------------------------------------------------
// tries to maintain a given speed, returns a maxForce-clipped steering
// force along the forward/backward axis


template<class Super>
bwVector3
OpenSteer::SteerLibraryMixin<Super>::
steerForTargetSpeed (bwReal targetSpeed)
{
    const bwReal mf = maxForce ();
    const bwReal speedError = targetSpeed - speed ();
    return forward () * clip (speedError, -mf, +mf);
}


// ----------------------------------------------------------------------------
// xxx experiment cwr 9-6-02


/*template<class Super>
void
OpenSteer::SteerLibraryMixin<Super>::
findNextIntersectionWithSphere (SphericalObstacle& obs,
                                PathIntersection& intersection)
{
    // xxx"SphericalObstacle& obs" should be "const SphericalObstacle&
    // obs" but then it won't let me store a pointer to in inside the
    // PathIntersection

    // This routine is based on the Paul Bourke's derivation in:
    //   Intersection of a Line and a Sphere (or circle)
    //   http://www.swin.edu.au/astronomy/pbourke/geometry/sphereline/

    bwReal b, c, d, p, q, s;
    bwVector3 lc;

    // initialize pathIntersection object
    intersection.intersect = false;
    intersection.obstacle = &obs;

    // find "local center" (lc) of sphere in boid's coordinate space
    lc = localizePosition (obs.center);

    // computer line-sphere intersection parameters
    b = -2 * lc.z;
    c = square (lc.x) + square (lc.y) + square (lc.z) -
        square (obs.radius + radius());
    d = (b * b) - (4 * c);

    // when the path does not intersect the sphere
    if (d < 0) return;

    // otherwise, the path intersects the sphere in two points with
    // parametric coordinates of "p" and "q".
    // (If "d" is zero the two points are coincident, the path is tangent)
    s = sqrtXXX (d);
    p = (-b + s) / 2;
    q = (-b - s) / 2;

    // both intersections are behind us, so no potential collisions
    if ((p < 0) && (q < 0)) return;

    // at least one intersection is in front of us
    intersection.intersect = true;
    intersection.distance =
        ((p > 0) && (q > 0)) ?
        // both intersections are in front of us, find nearest one
        ((p < q) ? p : q) :
        // otherwise only one intersections is in front, select it
        ((p > 0) ? p : q);
    return;
}*/

template<class Super>
void
OpenSteer::SteerLibraryMixin<Super>::
findNextIntersectionWithSphere (SphericalObstacle& obs,
                                PathIntersection& intersection)
{

    // initialize pathIntersection object
    intersection.intersect = false;
    intersection.obstacle = &obs;
	bwVector3 pos = position() ;
	gmtl::Spheref sph1(gmtl::Point3f(pos[0],pos[1],pos[2]), radius());
	gmtl::Spheref sph2(gmtl::Point3f(obs.center[0],obs.center[1],obs.center[2]), obs.radius);
	bwVector3 fwd = forward() ;
	gmtl::Vec3f path1(fwd[0],fwd[1],fwd[2]);
    gmtl::Vec3f path2(0,0,0);

    float first, second;
    intersection.intersect = gmtl::intersect(sph1, path1, sph2, path2, first, second) ;
	intersection.distance = first ;
	return;
}



// ----------------------------------------------------------------------------
#endif // OPENSTEER_STEERLIBRARY_H
