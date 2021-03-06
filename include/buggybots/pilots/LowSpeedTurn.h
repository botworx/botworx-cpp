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
// "Low Speed Turn" test fixture
//
// Used to evaluate vehicle response at low speed to backward-directed
// steering force
//
// 08-20-02 cwr: created 
//
//
// ----------------------------------------------------------------------------


#include <iomanip>
#include <sstream>
#include <buggybots/BbPilot.h>



using namespace BbSteer ;


// ----------------------------------------------------------------------------


class LowSpeedTurn : public BbPilot
{
public:

    // constructor
    LowSpeedTurn () {reset ();}

    // reset state
    void reset (void)
    {
        // reset vehicle state
        BbPilot::reset ();

        // speed along Forward direction.
		//startSpeed = 0.15f;
		startSpeed = 1.0f;
        setSpeed (startSpeed);

        // initial position along X axis
        //setPosition (startX, 0, 0);

        // steering force clip magnitude
        setMaxForce (0.3f);

        // velocity  clip magnitude
        setMaxSpeed (1.5f);

        // for next instance: step starting location
        //startX += 2;

        // for next instance: step speed
        startSpeed += 0.15f;

        // 15 seconds and 150 points along the trail
        //TODO:redo:setTrailParameters (15, 150);
    }

    // draw into the scene
    void draw (void)
    {
        //TODO:redo:drawBasic2dCircularVehicle (*this, gGray50);
        //TODO:redo:drawTrail ();
    }

    // per frame simulation update
    virtual bool onStep(BwStepper& stepper)
    {
		bwReal elapsedTime = stepper.getDeltaTime() ;
        applySteeringForce (steering (), elapsedTime);

        // annotation
        //TODO:redo:annotationVelocityAcceleration ();
        //TODO:redo:recordTrailVertex (currentTime, position());
		return BbPilot::onStep(stepper) ;
    }

    // reset starting positions
    void resetStarts (void)
    {
        startX = 0;
        startSpeed = 0;
    }

    // constant steering force
    bwVector3 steering (void) {return bwVector3 (1, 0, -1);}

    // for stepping the starting conditions for next vehicle
    bwReal startX;
    bwReal startSpeed;
};