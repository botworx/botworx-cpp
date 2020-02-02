#include "stdafx.h"
// ----------------------------------------------------------------------------
#include <buggybots/BbPilot.h>
#include <algorithm>


namespace BbSteer {

BbPilot::BbPilot ()
{
    // set inital state
    reset ();

    // maintain unique serial numbers
    //serialNumber = serialNumberCounter++;
}
BbPilot::~BbPilot (void)
{
}
void BbPilot::doStep(BwStepper& stepper) {}
bool BbPilot::onStep(BwStepper& stepper) { return true ; }
void BbPilot::doPostStep(BwStepper& stepper) {}
bool BbPilot::onPostStep(BwStepper& stepper) { return true ; }


// ----------------------------------------------------------------------------
// adjust the steering force passed to applySteeringForce.
//
// allows a specific vehicle class to redefine this adjustment.
// default is to disallow backward-facing steering at low speed.
//
// xxx should the default be this ad-hocery, or no adjustment?
// xxx experimental 8-20-02
//
// parameter names commented out to prevent compiler warning from "-W"


bwVector3 
BbPilot::adjustRawSteeringForce (const bwVector3& force,
                                                  bwReal /* deltaTime */)
{
	const bwReal s = speed () ;
    const bwReal maxAdjustedSpeed = 0.2f * maxSpeed ();

	if ((s > maxAdjustedSpeed) || (force == bwVector3()))
    {
        return force;
    }
    else
    {
        const bwReal range = s / maxAdjustedSpeed;
        // const float cosine = interpolate (pow (range, 6), 1.0f, -1.0f);
        // const float cosine = interpolate (pow (range, 10), 1.0f, -1.0f);
        // const float cosine = interpolate (pow (range, 20), 1.0f, -1.0f);
        // const float cosine = interpolate (pow (range, 100), 1.0f, -1.0f);
        // const float cosine = interpolate (pow (range, 50), 1.0f, -1.0f);
        const bwReal cosine = interpolate (pow (range, 20), 1.0f, -1.0f);
        return limitMaxDeviationAngle (force, cosine, forward());
    }
}


// ----------------------------------------------------------------------------
// xxx experimental 9-6-02
//
// apply a given braking force (for a given dt) to our momentum.
//
// (this is intended as a companion to applySteeringForce, but I'm not sure how
// well integrated it is.  It was motivated by the fact that "braking" (as in
// "capture the flag" endgame) by using "forward * speed * -rate" as a steering
// force was causing problems in adjustRawSteeringForce.  In fact it made it
// get NAN, but even if it had worked it would have defeated the braking.
//
// maybe the guts of applySteeringForce should be split off into a subroutine
// used by both applySteeringForce and applyBrakingForce?


void 
BbPilot::applyBrakingForce (bwReal rate, bwReal deltaTime)
{
    const bwReal rawBraking = speed () * rate;
    const bwReal clipBraking = ((rawBraking < maxForce ()) ?
                               rawBraking :
                               maxForce ());

    setSpeed (speed () - (clipBraking * deltaTime));
}


// ----------------------------------------------------------------------------
// apply a given steering force to our momentum,
// adjusting our orientation to maintain velocity-alignment.


void 
BbPilot::applySteeringForce (const bwVector3& force,
                                              bwReal elapsedTime)
{

    const bwVector3 adjustedForce = adjustRawSteeringForce (force, elapsedTime);

    // enforce limit on magnitude of steering force
	const bwVector3 clippedForce = truncateLength (adjustedForce, maxForce ());

    // compute acceleration and velocity
    bwVector3 newAcceleration = (clippedForce / mass());
    bwVector3 newVelocity = velocity();

    // damp out abrupt changes and oscillations in steering acceleration
    // (rate is proportional to time step, then clipped into useful range)
    if (elapsedTime > 0)
    {
        const bwReal smoothRate = clip (9 * elapsedTime, 0.15f, 0.4f);
        blendIntoAccumulator (smoothRate,
                              newAcceleration,
                              _smoothedAcceleration);
    }

    // Euler integrate (per frame) acceleration into velocity
    newVelocity += _smoothedAcceleration * elapsedTime;

    // enforce speed limit
	newVelocity = truncateLength (newVelocity, maxSpeed ());

    // update Speed
	setSpeed (length(newVelocity));

    // Euler integrate (per frame) velocity into position
    setPosition (position() + (newVelocity * elapsedTime));

    // regenerate local space (by default: align vehicle's forward axis with
    // new velocity, but this behavior may be overridden by derived classes.)
    regenerateLocalSpace (newVelocity, elapsedTime);

    // maintain path curvature information
    measurePathCurvature (elapsedTime);

    // running average of recent positions
    blendIntoAccumulator (elapsedTime * 0.06f, // QQQ
                          position (),
                          _smoothedPosition);
}


// ----------------------------------------------------------------------------
// draw lines from vehicle's position showing its velocity and acceleration
void 
BbPilot::annotationVelocityAcceleration (bwReal maxLengthA, bwReal maxLengthV)
{
    const bwReal desat = 0.4f;
    const bwReal aScale = maxLengthA / maxForce ();
    const bwReal vScale = maxLengthV / maxSpeed ();
    const bwVector3& p = position();
    const bwVector3 aColor (desat, desat, 1); // bluish
    const bwVector3 vColor (    1, desat, 1); // pinkish

    //TODO:redo:annotationLine (p, p + (velocity ()           * vScale), vColor);
    //TODO:redo:annotationLine (p, p + (_smoothedAcceleration * aScale), aColor);
}

// ----------------------------------------------------------------------------
bwVector3 BbPilot::steerToAvoidParticles(bwReal minTimeToCollision,
                       const Particles& particles)
{
    bwVector3 avoidance;
    const bwReal minDistanceToCollision = minTimeToCollision * speed();
	Particle nearest  ;
	bwReal nearestDist = minDistanceToCollision ;

    // test all obstacles for intersection with my forward axis,
    // select the one whose point of intersection is nearest
    for (ParticleIter iter = m_particles.begin(); iter != m_particles.end(); ++iter)
    {
		const Particle& particle = *iter ;
		bwReal dist = OpenSteer::distance(position(), particle.getOrigin()) ;
		if(dist < nearestDist) {
            nearest = particle ;
			nearestDist = dist ;
		}
    }

    // when a nearest intersection was found
    if (nearestDist < minDistanceToCollision)
    {
        // show the corridor that was checked for collisions
        annotateAvoidObstacle (minDistanceToCollision);

        // compute avoidance steering force: take offset from obstacle to me,
        // take the component of that which is lateral (perpendicular to my
        // forward direction), set length to maxForce, add a bit of forward
        // component (in capture the flag, we never want to slow down)
		const bwVector3 offset = position() - nearest.getOrigin() ;
		avoidance = perpendicularComponent (offset, forward());
		normalize (avoidance );
        avoidance *= maxForce ();
        avoidance += forward() * maxForce () * bwReal(0.75f) ;
    }

    return avoidance;
}

} //namespace BbSteer {