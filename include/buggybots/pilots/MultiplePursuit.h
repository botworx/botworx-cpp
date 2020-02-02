#ifndef _MultiplePursuit_H
#define _MultiplePursuit_H
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
// Multiple pursuit (for testing pursuit)
//
// 08-22-02 cwr: created 
//
//
// ----------------------------------------------------------------------------


#include <buggybots/BbPilot.h>

using namespace BbSteer;

// ----------------------------------------------------------------------------
// This PlugIn uses two vehicle types: MpWanderer and MpPursuer.  They have
// a common base class, MpBase, which is a specialization of BbPilot.


class MpBase : public BbPilot
{
public:

    // constructor
    MpBase () {reset ();}

    // reset state
    void reset (void)
    {
        BbPilot::reset (); // reset the vehicle 
        setSpeed (0);            // speed along Forward direction.
        setMaxForce (5.0);       // steering force is clipped to this magnitude
        setMaxSpeed (3.0);       // velocity is clipped to this magnitude
		setPosition(0,1,0) ;
        //TODO:redo:clearTrailHistory ();    // prevent long streaks due to teleportation 
        //TODO:redo:gaudyPursuitAnnotation = true; // select use of 9-color annotation
    }
	//
	void setAvatar(VrModel* pAvatar) { p_avatar = pAvatar ; }
	VrModel* p_avatar ;
} ;


class MpWanderer : public MpBase
{
public:

    // constructor
    MpWanderer () {reset ();}

    // reset state
    void reset (void)
    {
        MpBase::reset ();
        //bodyColor.set (0.4f, 0.6f, 0.4f); // greenish
    }

    // one simulation step
    virtual bool onStep(BwStepper& stepper)
    {
		bwReal elapsedTime = stepper.getDeltaTime() ;
        //const bwVector3 wander2d = steerForWander (elapsedTime).setYtoZero ();
		const bwVector3 wander2d = setYtoZero (steerForWander (elapsedTime));
        const bwVector3 steer = forward() + (wander2d * bwReal(3.0f));
        applySteeringForce (steer, elapsedTime);

        // for annotation
        //TODO:redo:recordTrailVertex (currentTime, position());
		return BbPilot::onStep(stepper) ;
    }

};


class MpPursuer : public MpBase
{
public:

    // constructor
    MpPursuer (MpWanderer* w) {wanderer = w; reset ();}

    // reset state
    void reset (void)
    {
        MpBase::reset ();
        //bodyColor.set (0.6f, 0.4f, 0.4f); // redish
        //randomizeStartingPositionAndHeading ();
    }

    // one simulation step
    virtual bool onStep(BwStepper& stepper)
    {
		bwReal elapsedTime = stepper.getDeltaTime() ;
        // when pursuer touches quarry ("wanderer"), reset its position
        const float d = distance (position(), wanderer->position());
        const float r = radius() + wanderer->radius();
        if (d < r) reset ();

        const float maxTime = 20; // xxx hard-to-justify value
        applySteeringForce (steerForPursuit (*wanderer, maxTime), elapsedTime);

        // for annotation
        //TODO:redo:recordTrailVertex (currentTime, position());
		return BbPilot::onStep(stepper) ;
    }

    // reset position
    void randomizeStartingPositionAndHeading (void)
    {
        // randomize position on a ring between inner and outer radii
        // centered around the home base
        const bwReal inner = 20;
        const bwReal outer = 30;
        const bwReal radius = frandom2 (inner, outer);
        const bwVector3 randomOnRing = RandomUnitVectorOnXZPlane () * radius;
        setPosition (wanderer->position() + randomOnRing);

        // randomize 2D heading
        randomizeHeadingOnXZPlane ();
    }

    BbPilot* wanderer;
};



// ----------------------------------------------------------------------------
#endif //_MultiplePursuit_H