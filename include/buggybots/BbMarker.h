#ifndef _BbMarker_H
#define _BbMarker_H

#include <bwsteer/AbstractVehicle.h>
#include <bwsteer/SteerLibrary.h>
#include <bwsteer/Proximity.h>

namespace BbSteer {
using namespace OpenSteer ;
typedef AbstractProximityDatabase<AbstractVehicle*> ProximityDatabase;
typedef AbstractTokenForProximityDatabase<AbstractVehicle*> ProximityToken;

// ----------------------------------------------------------------------------

#define CAT_LEVELS 4

class BbMarker : public LocalSpaceMixin<AbstractVehicle>
{
public:
    // constructor
    BbMarker() ;
	//
	void setModel(VrModel* pModel) { p_model = pModel ; }
	VrModel* getModel() { return p_model ; }
	VrModel* p_model ;
	//
	//void set_isDestroyed(bool val) { m_isDestroyed = val ; }
	void destroy() ;
	bool isDestroyed() { return m_isDestroyed ; }
	bool m_isDestroyed ;
	//
	typedef unsigned int catId ;
	void setCatId(catId id, size_t level = 0) { m_catId[level] = id ; }
	catId getCatId(size_t level = 0) { return m_catId[level] ; }
	void clearCatIds() ;
	catId m_catId[CAT_LEVELS] ;
	//
	ProximityToken* proximityToken ;
	// switch to new proximity database -- just for demo purposes
	void setPd(ProximityDatabase& pd)
	{
		// delete this boid's token in the old proximity database
		delete proximityToken;

		// allocate a token for this boid in the proximity database
		proximityToken = pd.allocateToken (this);
	}
	virtual void validate() ;
    // destructor
    virtual ~BbMarker ();

    // reset vehicle state
    void reset (void)
    {
        // reset LocalSpace state
        resetLocalSpace ();

        setMass (1);          // mass (defaults to 1 so acceleration=force)
        setSpeed (0);         // speed along Forward direction.

        setRadius (0.5f);     // size of bounding sphere

        setMaxForce (0.1f);   // steering force is clipped to this magnitude
        setMaxSpeed (1.0f);   // velocity is clipped to this magnitude
    }

    // get/set mass
    bwReal mass (void) const {return _mass;}
    bwReal setMass (bwReal m) {return _mass = m;}

    // get velocity of vehicle
    bwVector3 velocity (void) const {return forward() * bwReal(_speed) ;}

    // get/set speed of vehicle  (may be faster than taking mag of velocity)
    bwReal speed (void) const {return _speed;}
    bwReal setSpeed (bwReal s) {return _speed = s;}

    // size of bounding sphere, for obstacle avoidance, etc.
    bwReal radius (void) const {return _radius;}
    bwReal setRadius (bwReal m) {return _radius = m;}

    // get/set maxForce
    bwReal maxForce (void) const {return _maxForce;}
    bwReal setMaxForce (bwReal mf) {return _maxForce = mf;}

    // get/set maxSpeed
    bwReal maxSpeed (void) const {return _maxSpeed;}
    bwReal setMaxSpeed (bwReal ms) {return _maxSpeed = ms;}


    // the default version: keep FORWARD parallel to velocity, change
    // UP as little as possible.
    virtual void regenerateLocalSpace (const bwVector3& newVelocity,
                                        bwReal elapsedTime);

    // alternate version: keep FORWARD parallel to velocity, adjust UP
    // according to a no-basis-in-reality "banking" behavior, something
    // like what birds and airplanes do.  (XXX experimental cwr 6-5-03)
    void regenerateLocalSpaceForBanking (const bwVector3& newVelocity,
                                            bwReal elapsedTime);

    // predict position of this vehicle at some time in the future
    // (assumes velocity remains constant)
    bwVector3 predictFuturePosition (bwReal predictionTime) const;

    // get instantaneous curvature (since last update)
    bwReal curvature (void) {return _curvature;}

    // get/reset smoothedCurvature, smoothedAcceleration and smoothedPosition
    bwReal smoothedCurvature (void) {return _smoothedCurvature;}
    bwReal resetSmoothedCurvature (float value = 0)
    {
        //_lastForward = bwVector3::zero;
		_lastForward = bwVector3() ;
        //_lastPosition = bwVector3::zero;
		_lastPosition = bwVector3();
        return _smoothedCurvature = _curvature = value;
    }
    bwVector3 smoothedAcceleration (void) {return _smoothedAcceleration;}
    //bwVector3 resetSmoothedAcceleration (const bwVector3& value = bwVector3::zero)
	bwVector3 resetSmoothedAcceleration (const bwVector3& value = bwVector3())
    {
        return _smoothedAcceleration = value;
    }
    bwVector3 smoothedPosition (void) {return _smoothedPosition;}
    //bwVector3 resetSmoothedPosition (const bwVector3& value = bwVector3::zero)
	bwVector3 resetSmoothedPosition (const bwVector3& value = bwVector3())
    {
        return _smoothedPosition = value;
    }

    // give each vehicle a unique number
    int serialNumber;
    static int serialNumberCounter;

    // draw lines from vehicle's position showing its velocity and acceleration
    void annotationVelocityAcceleration (bwReal maxLengthA, bwReal maxLengthV);
    void annotationVelocityAcceleration (bwReal maxLength)
        {annotationVelocityAcceleration (maxLength, maxLength);}
    void annotationVelocityAcceleration (void)
        {annotationVelocityAcceleration (3, 3);}

//
protected:

    bwReal _mass;       // mass (defaults to unity so acceleration=force)

    bwReal _radius;     // size of bounding sphere, for obstacle avoidance, etc.

    bwReal _speed;      // speed along Forward direction.  Because local space
                        // is velocity-aligned, velocity = Forward * Speed

    bwReal _maxForce;   // the maximum steering force this vehicle can apply
                        // (steering force is clipped to this magnitude)

    bwReal _maxSpeed;   // the maximum speed this vehicle is allowed to move
                        // (velocity is clipped to this magnitude)

    bwReal _curvature;
    bwVector3 _lastForward;
    bwVector3 _lastPosition;
    bwVector3 _smoothedPosition;
    bwReal _smoothedCurvature;
    bwVector3 _smoothedAcceleration;

    // measure path curvature (1/turning-radius), maintain smoothed version
    void measurePathCurvature (bwReal elapsedTime);
};


} // namespace OpenSteer


// ----------------------------------------------------------------------------
#endif //_BbMarker_H
