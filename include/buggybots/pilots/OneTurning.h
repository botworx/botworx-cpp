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
// One vehicle turning way: a (near) minimal BwSteerApplet PlugIn
//
// 06-24-02 cwr: created 
//
//
// ----------------------------------------------------------------------------


#include <iomanip>
#include <sstream>
#include <buggybots/BbPilot.h>


using namespace BbSteer;


// ----------------------------------------------------------------------------


class OneTurning : public BbPilot
{
public:

    // constructor
    OneTurning () {reset ();}

    // reset state
    void reset (void)
    {
        BbPilot::reset (); // reset the vehicle 
        setSpeed (1.5f);         // speed along Forward direction.
        setMaxForce (0.3f);      // steering force is clipped to this magnitude
        setMaxSpeed (5);         // velocity is clipped to this magnitude
        //TODO:redo:clearTrailHistory ();    // prevent long streaks due to teleportation 
    }

    // per frame simulation update
    virtual bool onStep(BwStepper& stepper)
    {
		bwReal elapsedTime = stepper.getDeltaTime() ;
        applySteeringForce (bwVector3(-2, 0, -3), elapsedTime);
        annotationVelocityAcceleration ();
        //TODO:redo:recordTrailVertex (currentTime, position());
		return BbPilot::onStep(stepper) ;
    }

    // draw this character/vehicle into the scene
    /*TODO:redo:void draw (void)
    {
        drawBasic2dCircularVehicle (*this, gGray50);
        drawTrail ();
    }*/
};
