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
// An autonomous "pedestrian":
// follows paths, avoids collisions with obstacles and other pedestrians
//
// 10-29-01 cwr: created
//
//
// ----------------------------------------------------------------------------


#include <iomanip>
#include <sstream>
#include <bwsteer/Pathway.h>
#include <buggybots/BbPilot.h>

using namespace BbSteer;
// ----------------------------------------------------------------------------
class Pedestrian : public BbPilot
{
public:

    // type for a group of Pedestrians
    typedef std::vector<Pedestrian*> groupType;

    // constructor
    Pedestrian (ProximityDatabase& pd)
    {
        // allocate a token for this boid in the proximity database
        setPd(pd);

        // reset Pedestrian state
        reset ();
    }

    // destructor
    virtual ~Pedestrian ()
    {
        // delete this boid's token in the proximity database
        delete proximityToken;
    }

    // reset all instance state
    void reset (void)
    {
        // reset the vehicle 
        BbPilot::reset ();
		//TODO:was global
		gTestPath = NULL ;
		gUseDirectedPathFollowing = true ;
		//gWanderSwitch = true;
		gWanderSwitch = false ;
        // max speed and max steering force (maneuverability) 
        setMaxSpeed (2.0);
        setMaxForce (8.0);

        // initially stopped
        setSpeed (0);

        // size of bounding sphere, for obstacle avoidance, etc.
        setRadius (1.5); // width = 0.7, add 0.3 margin, take half

        // set the path for this Pedestrian to follow
        path = getTestPath ();

        // set initial position
        // (random point on path + random horizontal offset)
        const bwReal d = path->getTotalPathLength() * frandom01();
        const bwReal r = path->radius;
        const bwVector3 randomOffset = randomVectorOnUnitRadiusXZDisk () * r;
        setPosition (path->mapPathDistanceToPoint (d) + randomOffset);

        // randomize 2D heading
        randomizeHeadingOnXZPlane ();

        // pick a random direction for path following (upstream or downstream)
        pathDirection = (frandom01() > 0.5) ? -1 : +1;

        // trail parameters: 3 seconds with 60 points along the trail
        //TODO:redo:setTrailParameters (3, 60);

        // notify proximity database that our position has changed
        proximityToken->updateForNewPosition (position());
    }

    // per frame simulation update
    virtual bool onStep(BwStepper& stepper)
    {
		bwReal elapsedTime = stepper.getDeltaTime() ;
        // apply steering force to our momentum
        applySteeringForce (determineCombinedSteering (elapsedTime),
                            elapsedTime);

        // reverse direction when we reach an endpoint
        if (gUseDirectedPathFollowing)
        {
            const bwVector3 darkRed (0.7f, 0, 0);

            //if (bwVector3::distance (position(), gEndpoint0) < path->radius)
			if (distance (position(), gEndpoint0) < path->radius)
            {
                pathDirection = +1;
                //TODO:redo:annotationXZCircle (path->radius, gEndpoint0, darkRed, 20);
            }
            //if (bwVector3::distance (position(), gEndpoint1) < path->radius)
			if (distance (position(), gEndpoint1) < path->radius)
            {
                pathDirection = -1;
                //TODO:redo:annotationXZCircle (path->radius, gEndpoint1, darkRed, 20);
            }
        }

        // annotation
        //TODO:redo:annotationVelocityAcceleration (5, 0);
        //TODO:redo:recordTrailVertex (currentTime, position());

        // notify proximity database that our position has changed
        proximityToken->updateForNewPosition (position());
		return BbPilot::onStep(stepper) ;
    }

    // compute combined steering force: move forward, avoid obstacles
    // or neighbors if needed, otherwise follow the path and wander
    bwVector3 determineCombinedSteering (bwReal elapsedTime)
    {
        // move forward
        bwVector3 steeringForce = forward();

        // probability that a lower priority behavior will be given a
        // chance to "drive" even if a higher priority behavior might
        // otherwise be triggered.
        const bwReal leakThrough = 0.1f;

        // determine if obstacle avoidance is required
        bwVector3 obstacleAvoidance;
		//if ( (!obstacles().empty()) && (leakThrough < frandom01()))
		if ( !obstacles().empty() )
        {
            const bwReal oTime = 6; // minTimeToCollision = 6 seconds
			//const float oTime = 2; // minTimeToCollision = 6 seconds
            //obstacleAvoidance = steerToAvoidObstacles (oTime, gObstacles);
			obstacleAvoidance = steerToAvoidObstacles (oTime, obstacles());
        }

        // if obstacle avoidance is needed, do it
        //if (obstacleAvoidance != bwVector3::zero)
		if (obstacleAvoidance != bwVector3())
        {
            steeringForce += obstacleAvoidance;
        }
        else
        {
            // otherwise consider avoiding collisions with others
            bwVector3 collisionAvoidance;
            const bwReal caLeadTime = 3;

            // find all neighbors within maxRadius using proximity database
            // (radius is largest distance between vehicles traveling head-on
            // where a collision is possible within caLeadTime seconds.)
            const bwReal maxRadius = caLeadTime * maxSpeed() * 2;
            neighbors.clear();
            proximityToken->findNeighbors (position(), maxRadius, neighbors);

            if (leakThrough < frandom01())
                collisionAvoidance =
                    steerToAvoidNeighbors (caLeadTime, neighbors) * bwReal(10.0f) ;

            // if collision avoidance is needed, do it
            //if (collisionAvoidance != bwVector3::zero)
			if (collisionAvoidance != bwVector3())
            {
                steeringForce += collisionAvoidance;
            }
            else
            {
                // add in wander component (according to user switch)
                if (gWanderSwitch)
                    steeringForce += steerForWander (elapsedTime);

                // do (interactively) selected type of path following
                const bwReal pfLeadTime = 3;
                const bwVector3 pathFollow =
                    (gUseDirectedPathFollowing ?
                     steerToFollowPath (pathDirection, pfLeadTime, *path) :
                     steerToStayOnPath (pfLeadTime, *path));

                // add in to steeringForce
                //steeringForce += pathFollow * 0.5;
				steeringForce += pathFollow * bwReal(0.5f) ;
            }
        }

        // return steering constrained to global XZ "ground" plane
        //return steeringForce.setYtoZero ();
		return setYtoZero (steeringForce);
    }
	//
PolylinePathway* getTestPath (void)
{
    if (gTestPath == NULL)
    {
        const bwReal pathRadius = 2;

        const int pathPointCount = 7;
        const bwReal size = 30;
        const bwReal top = 2 * size;
        const bwReal gap = 1.2f * size;
        const bwReal out = 2 * size;
        const bwReal h = 0.5;
		//
		bwVector3 pathPoints[pathPointCount] =
            {bwVector3 (h+gap-out,     0,  h+top-out),  // 0 a
             bwVector3 (h+gap,         0,  h+top),      // 1 b
             bwVector3 (h+gap+(top/2), 0,  h+top/2),    // 2 c
             bwVector3 (h+gap,         0,  h),          // 3 d
             bwVector3 (h,             0,  h),          // 4 e
             bwVector3 (h,             0,  h+top),      // 5 f
             bwVector3 (h+gap,         0,  h+top/2)};   // 6 g

		const bwVector3 pos = position() ;
		for(int i = 0 ; i < pathPointCount ; ++i) {
			pathPoints[i] += pos ;
		}
        gEndpoint0 = pathPoints[0];
        gEndpoint1 = pathPoints[pathPointCount-1];

        gTestPath = new PolylinePathway (pathPointCount,
                                         pathPoints,
                                         pathRadius,
                                         false);
    }
    return gTestPath;
}

    // allocate one and share amoung instances just to save memory usage
    // (change to per-instance allocation to be more MP-safe)
    //static AVGroup neighbors;
	AVGroup neighbors;

    // path to be followed by this pedestrian
    // XXX Ideally this should be a generic Pathway, but we use the
    // XXX getTotalPathLength and radius methods (currently defined only
    // XXX on PolylinePathway) to set random initial positions.  Could
    // XXX there be a "random position inside path" method on Pathway?
    PolylinePathway* path;

    // direction for path following (upstream or downstream)
    int pathDirection;
	//TODO:was global/static
	// creates a path for the PlugIn
	PolylinePathway* gTestPath ;
	//SphericalObstacle gObstacle1 ;
	//SphericalObstacle gObstacle2 ;
	//ObstacleGroup gObstacles ;
	bwVector3 gEndpoint0 ;
	bwVector3 gEndpoint1 ;
	bool gUseDirectedPathFollowing  ;

	// this was added for debugging tool, but I might as well leave it in
	bool gWanderSwitch ;

};


//AVGroup Pedestrian::neighbors;


// ----------------------------------------------------------------------------
// create path for PlugIn 
//
//
//        | gap |
//
//        f      b
//        |\    /\        -
//        | \  /  \       ^
//        |  \/    \      |
//        |  /\     \     |
//        | /  \     c   top
//        |/    \g  /     |
//        /        /      |
//       /|       /       V      z     y=0
//      / |______/        -      ^
//     /  e      d               |
//   a/                          |
//    |<---out-->|               o----> x
//