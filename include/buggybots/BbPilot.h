#ifndef _BbPilot_H
#define _BbPilot_H

#include "BbMarker.h"

namespace BbSteer {
//
using namespace OpenSteer ;
typedef SteerLibraryMixin<BbMarker> BbPilot_3;
typedef bwParticle Particle  ;

typedef std::vector<bwParticle> Particles ;

typedef Particles::iterator ParticleIter ;
// ----------------------------------------------------------------------------
class BbPilot : public BbPilot_3
{
public:

    // constructor
    BbPilot ();

    // destructor
    virtual ~BbPilot ();

	//virtual void update (bwReal currentTime, bwReal elapsedTime) {}
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onStep(BwStepper& stepper) ;
	virtual bool invokeStep(BwStepper& stepper) { doStep(stepper) ; return onStep(stepper) ; }
	virtual void doPostStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual bool invokePostStep(BwStepper& stepper) { doPostStep(stepper) ; return onPostStep(stepper) ; }
    // reset vehicle state
    void reset (void)
    {
		BbPilot_3::reset ();
    }

    // apply a given steering force to our momentum,
    // adjusting our orientation to maintain velocity-alignment.
    void applySteeringForce (const bwVector3& force, bwReal deltaTime);

    // adjust the steering force passed to applySteeringForce.
    // allows a specific vehicle class to redefine this adjustment.
    // default is to disallow backward-facing steering at low speed.
    // xxx experimental 8-20-02
    virtual bwVector3 adjustRawSteeringForce (const bwVector3& force,
                                            bwReal deltaTime);

    // apply a given braking force (for a given dt) to our momentum.
    // xxx experimental 9-6-02
    void applyBrakingForce (bwReal rate, bwReal deltaTime);

    // draw lines from vehicle's position showing its velocity and acceleration
    void annotationVelocityAcceleration (bwReal maxLengthA, bwReal maxLengthV);
    void annotationVelocityAcceleration (bwReal maxLength)
        {annotationVelocityAcceleration (maxLength, maxLength);}
    void annotationVelocityAcceleration (void)
        {annotationVelocityAcceleration (3, 3);}

    // set a random "2D" heading: set local Up to global Y, then effectively
    // rotate about it by a random angle (pick random forward, derive side).
    void randomizeHeadingOnXZPlane (void)
    {
        //setUp (bwVector3::up);
		setUp (BW_UP);
        setForward (RandomUnitVectorOnXZPlane ());
        setSide (localRotateForwardToSide (forward()));
    }
//TODO:newstuff
	void addObstacle(bwReal r, const bwVector3& c) { 
		_spheres.push_back(SphericalObstacle (r, c)) ;
		_obstacles.push_back(&_spheres[_spheres.size()-1]) ;
	}
	void clearObstacles() { 
		_spheres.clear() ; 
		_obstacles.clear() ; 
	}
	//
	std::vector<SphericalObstacle> _spheres ;

	ObstacleGroup& obstacles() { return _obstacles ; }
	ObstacleGroup _obstacles ;
//
	bwVector3 steerToAvoidParticles(bwReal minTimeToCollision,
                       const Particles& particles) ;
	//
	void addParticle(const bwPoint3& pos, const bwVector3& dir) { 
		m_particles.push_back(Particle(pos, dir)) ;
	}
	void clearParticles() { 
		m_particles.clear() ; 
	}
	Particles m_particles ;

};

} // namespace OpenSteer
    
    
// ----------------------------------------------------------------------------
#endif //_BbPilot_H
