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
// OpenSteer Boids
// 
// 09-26-02 cwr: created 
//
//
// ----------------------------------------------------------------------------


#include <sstream>
#include <buggybots/BbPilot.h>

// Include names declared in the OpenSteer namespace into the namemodels to search to find names.
using namespace BbSteer ;

// ----------------------------------------------------------------------------

class Boid : public BbPilot
{
public:

    // type for a flock: an STL vector of Boid pointers
    typedef std::vector<Boid*> groupType;


    // constructor
    Boid (ProximityDatabase& pd)
    {
		//
		worldRadius = 250 ;
		boundaryCondition = 0 ;
        // allocate a token for this boid in the proximity database
        setPd(pd);

        // reset all boid state
        reset ();
    }


    // destructor
    virtual ~Boid ()
    {
        // delete this boid's token in the proximity database
        delete proximityToken;
    }


    // reset state
    void reset (void)
    {
        // reset the vehicle
        BbPilot::reset ();

        // steering force is clipped to this magnitude
        setMaxForce (27);

        // velocity is clipped to this magnitude
        setMaxSpeed (9);

        // initial slow speed
        setSpeed (maxSpeed() * 0.3f);

        // randomize initial orientation
        //regenerateOrthonormalBasisUF (RandomUnitVector ());

        // randomize initial position
        //setPosition (RandomVectorInUnitRadiusSphere () * 20);

        // notify proximity database that our position has changed
        proximityToken->updateForNewPosition (position());
    }


    // draw this boid into the scene
    /*TODO:redo:void draw (void)
    {
        drawBasic3dSphericalVehicle (*this, gGray70);
        drawTrail ();
    }*/


    // per frame simulation update
    virtual bool onStep(BwStepper& stepper)
    {
		bwReal elapsedTime = stepper.getDeltaTime() ;
        // steer to flock and perhaps to stay within the spherical boundary
        applySteeringForce (steerToFlock () + handleBoundary(), elapsedTime);

        // notify proximity database that our position has changed
        proximityToken->updateForNewPosition (position());
		return BbPilot::onStep(stepper) ;
    }


    // basic flocking
    bwVector3 steerToFlock (void)
    {
        const bwReal separationRadius =  5.0f;
        const bwReal separationAngle  = -0.707f;
        const bwReal separationWeight =  12.0f;

        const bwReal alignmentRadius = 7.5f;
        const bwReal alignmentAngle  = 0.7f;
        const bwReal alignmentWeight = 8.0f;

        const bwReal cohesionRadius = 9.0f;
        const bwReal cohesionAngle  = -0.15f;
        const bwReal cohesionWeight = 8.0f;

        const bwReal maxRadius = maxXXX (separationRadius,
                                        maxXXX (alignmentRadius,
                                                cohesionRadius));

        // find all flockmates within maxRadius using proximity database
        neighbors.clear();
        proximityToken->findNeighbors (position(), maxRadius, neighbors);

        // determine each of the three component behaviors of flocking
        const bwVector3 separation = steerForSeparation (separationRadius,
                                                    separationAngle,
                                                    neighbors);
        const bwVector3 alignment  = steerForAlignment  (alignmentRadius,
                                                    alignmentAngle,
                                                    neighbors);
        const bwVector3 cohesion   = steerForCohesion   (cohesionRadius,
                                                    cohesionAngle,
                                                    neighbors);

        // apply weights to components (save in variables for annotation)
        const bwVector3 separationW = separation * separationWeight;
        const bwVector3 alignmentW = alignment * alignmentWeight;
        const bwVector3 cohesionW = cohesion * cohesionWeight;

        // annotation
        // const bwReal s = 0.1;
        // annotationLine (position, position + (separationW * s), gRed);
        // annotationLine (position, position + (alignmentW  * s), gOrange);
        // annotationLine (position, position + (cohesionW   * s), gYellow);

        return separationW + alignmentW + cohesionW;
    }


    // Take action to stay within sphereical boundary.  Returns steering
    // value (which is normally zero) and may take other side-effecting
    // actions such as kinematically changing the Boid's position.
    bwVector3 handleBoundary (void)
    {
        // while inside the sphere do noting
        //if (position().length() < worldRadius) return bwVector3::zero;
		if (length(position()) < worldRadius) return bwVector3() ;

        // once outside, select strategy
        switch (boundaryCondition)
        {
        case 0:
            {
                // steer back when outside
                //const bwVector3 seek = xxxsteerForSeek (bwVector3::zero);
				const bwVector3 seek = xxxsteerForSeek (bwVector3());
                //const bwVector3 lateral = seek.perpendicularComponent (forward ());
				const bwVector3 lateral = perpendicularComponent (seek, forward ());
                return lateral;
            }
        case 1:
            {
                // wrap around (teleport)
                //setPosition (position().sphericalWrapAround (bwVector3::zero, worldRadius));
				setPosition (sphericalWrapAround (position(), bwVector3(), worldRadius));
                //return bwVector3::zero;
				return bwVector3();
            }
        }
        //return bwVector3::zero; // should not reach here
		return bwVector3(); // should not reach here
    }


    // make boids "bank" as they fly
    void regenerateLocalSpace (const bwVector3& newVelocity,
                               bwReal elapsedTime)
    {
        regenerateLocalSpaceForBanking (newVelocity, elapsedTime);
    }

    // cycle through various boundary conditions
    //static void nextBoundaryCondition (void)
	void nextBoundaryCondition (void)
    {
        const int max = 2;
        boundaryCondition = (boundaryCondition + 1) % max;
    }
    //static int boundaryCondition;
	int boundaryCondition;

    // allocate one and share amoung instances just to save memory usage
    // (change to per-instance allocation to be more MP-safe)
    //static AVGroup neighbors;
	AVGroup neighbors;

	bwReal worldRadius;
};





// ----------------------------------------------------------------------------
