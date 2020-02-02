#include "stdafx.h"
// ----------------------------------------------------------------------------
#include <buggybots/BbMarker.h>
#include <algorithm>

namespace BbSteer {
// ----------------------------------------------------------------------------
// serial numbers  (XXX should this be part of a "OpenSteerDemo vehicle mixin"?)
int BbMarker::serialNumberCounter = 0;
// ----------------------------------------------------------------------------
// constructor
BbMarker::BbMarker ()
{
	proximityToken = NULL;
	p_model = NULL ;
    // set inital state
    reset ();
    // maintain unique serial numbers
    serialNumber = serialNumberCounter++;
	clearCatIds() ;
	//
	m_isDestroyed = false ; //specifies the state of the object this marker represents.
}
void BbMarker::clearCatIds() {
	for(size_t i = 0 ; i < CAT_LEVELS ; ++i) {
		m_catId[i] = 0 ;
	}
}
void BbMarker::destroy() { 
	m_isDestroyed = true ; 
	clearCatIds() ;
	setModel(NULL) ;
}
// ----------------------------------------------------------------------------
// destructor
BbMarker::~BbMarker (void)
{
}
// ----------------------------------------------------------------------------
// the default version: keep FORWARD parallel to velocity, change UP as
// little as possible.
//
// parameter names commented out to prevent compiler warning from "-W"
void 
BbMarker::regenerateLocalSpace (const bwVector3& newVelocity,
                                                bwReal /* elapsedTime */)
{
    // adjust orthonormal basis vectors to be aligned with new velocity
    if (speed() > 0) regenerateOrthonormalBasisUF (newVelocity / speed());
}
// ----------------------------------------------------------------------------
// alternate version: keep FORWARD parallel to velocity, adjust UP according
// to a no-basis-in-reality "banking" behavior, something like what birds and
// airplanes do

// XXX experimental cwr 6-5-03


void 
BbMarker::regenerateLocalSpaceForBanking (const bwVector3& newVelocity,
                                                          bwReal elapsedTime)
{
    // the length of this global-upward-pointing vector controls the vehicle's
    // tendency to right itself as it is rolled over from turning acceleration
    const bwVector3 globalUp (0, 0.2f, 0);

    // acceleration points toward the center of local path curvature, the
    // length determines how much the vehicle will roll while turning
    const bwVector3 accelUp = _smoothedAcceleration * bwReal(0.05f) ;

    // combined banking, sum of UP due to turning and global UP
    const bwVector3 bankUp = accelUp + globalUp;

    // blend bankUp into vehicle's UP basis vector
    const float smoothRate = elapsedTime * 3;
    bwVector3 tempUp = up();
    blendIntoAccumulator (smoothRate, bankUp, tempUp);
    //setUp (tempUp.normalize());
	normalize(tempUp) ;
	setUp (tempUp);

//  annotationLine (position(), position() + (globalUp * 4), gWhite);  // XXX
//  annotationLine (position(), position() + (bankUp   * 4), gOrange); // XXX
//  annotationLine (position(), position() + (accelUp  * 4), gRed);    // XXX
//  annotationLine (position(), position() + (up ()    * 1), gYellow); // XXX

    // adjust orthonormal basis vectors to be aligned with new velocity
    if (speed() > 0) regenerateOrthonormalBasisUF (newVelocity / speed());
}


// ----------------------------------------------------------------------------
// measure path curvature (1/turning-radius), maintain smoothed version


void 
BbMarker::measurePathCurvature (bwReal elapsedTime)
{
    if (elapsedTime > 0)
    {
        const bwVector3 dP = _lastPosition - position ();
		const bwVector3 dF = (_lastForward - forward ()) / length (dP);
		const bwVector3 lateral = perpendicularComponent (dF, forward ());
		const float sign = (dot (lateral, side ()) < 0) ? 1.0f : -1.0f;
		_curvature = length(lateral) * sign;
        blendIntoAccumulator (elapsedTime * 4.0f,
                              _curvature,
                              _smoothedCurvature);
        _lastForward = forward ();
        _lastPosition = position ();
    }
}
// ----------------------------------------------------------------------------
// predict position of this vehicle at some time in the future
// (assumes velocity remains constant, hence path is a straight line)
//
// XXX Want to encapsulate this since eventually I want to investigate
// XXX non-linear predictors.  Maybe predictFutureLocalSpace ?
//
// XXX move to a vehicle utility mixin?


bwVector3 
BbMarker::predictFuturePosition (bwReal predictionTime) const
{
    return position() + (velocity() * predictionTime);
}
// ----------------------------------------------------------------------------
void BbMarker::validate() {
	if(proximityToken != NULL)
		proximityToken->updateForNewPosition (position());
}
} //namespace BbSteer {