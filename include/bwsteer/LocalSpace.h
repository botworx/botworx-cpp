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
// LocalSpace: a local coordinate system for 3d space
//
// Provide functionality such as transforming from local space to global
// space and vice versa.  Also regenerates a valid space from a perturbed
// "forward vector" which is the basis of abnstract vehicle turning.
//
// These are comparable to a 4x4 homogeneous transformation matrix where the
// 3x3 (R) portion is constrained to be a pure rotation (no shear or scale).
// The rows of the 3x3 R matrix are the basis vectors of the space.  They are
// all constrained to be mutually perpendicular and of unit length.  The top
// ("x") row is called "side", the middle ("y") row is called "up" and the
// bottom ("z") row is called forward.  The translation vector is called
// "position".  Finally the "homogeneous column" is always [0 0 0 1].
//
//     [ R R R  0 ]      [ Sx Sy Sz  0 ]
//     [ R R R  0 ]      [ Ux Uy Uz  0 ]
//     [ R R R  0 ]  ->  [ Fx Fy Fz  0 ]
//     [          ]      [             ]
//     [ T T T  1 ]      [ Tx Ty Tz  1 ]
//
// This file defines three classes:
//   AbstractLocalSpace:  pure virtual interface
//   LocalSpaceMixin:     mixin to layer LocalSpace functionality on any base
//   LocalSpace:          a concrete object (can be instantiated)
//
// 10-04-04 bk:  put everything into the OpenSteer namespace
// 06-05-02 cwr: created 
//
//
// ----------------------------------------------------------------------------


#ifndef OPENSTEER_LOCALSPACE_H
#define OPENSTEER_LOCALSPACE_H

// ----------------------------------------------------------------------------


namespace OpenSteer {


    class AbstractLocalSpace
    {
    public:

        // accessors (get and set) for side, up, forward and position
        virtual bwVector3 side (void) const = 0;
        virtual bwVector3 setSide (const bwVector3& s) = 0;
        virtual bwVector3 up (void) const = 0;
        virtual bwVector3 setUp (const bwVector3& u) = 0;
        virtual bwVector3 forward (void) const = 0;
        virtual bwVector3 setForward (const bwVector3& f) = 0;
        virtual bwVector3 position (void) const = 0;
        virtual bwVector3 setPosition (const bwVector3& p) = 0;

        // use right-(or left-)handed coordinate space
        virtual bool rightHanded (void) const = 0;

        // reset transform to identity
        virtual void resetLocalSpace (void) = 0;

        // transform a direction in global space to its equivalent in local space
        virtual bwVector3 localizeDirection (const bwVector3& globalDirection) const = 0;

        // transform a point in global space to its equivalent in local space
        virtual bwVector3 localizePosition (const bwVector3& globalPosition) const = 0;

        // transform a point in local space to its equivalent in global space
        virtual bwVector3 globalizePosition (const bwVector3& localPosition) const = 0;

        // transform a direction in local space to its equivalent in global space
        virtual bwVector3 globalizeDirection (const bwVector3& localDirection) const = 0;

        // set "side" basis vector to normalized cross product of forward and up
        virtual void setUnitSideFromForwardAndUp (void) = 0;

        // regenerate the orthonormal basis vectors given a new forward
        // (which is expected to have unit length)
        virtual void regenerateOrthonormalBasisUF (const bwVector3& newUnitForward) = 0;

        // for when the new forward is NOT of unit length
        virtual void regenerateOrthonormalBasis (const bwVector3& newForward) = 0;

        // for supplying both a new forward and and new up
        virtual void regenerateOrthonormalBasis (const bwVector3& newForward,
                                                 const bwVector3& newUp) = 0;

        // rotate 90 degrees in the direction implied by rightHanded()
        virtual bwVector3 localRotateForwardToSide (const bwVector3& v) const = 0;
        virtual bwVector3 globalRotateForwardToSide (const bwVector3& globalForward) const=0;
    };


    // ----------------------------------------------------------------------------
    // LocalSpaceMixin is a mixin layer, a class template with a paramterized base
    // class.  Allows "LocalSpace-ness" to be layered on any class.


    template <class Super>
    class LocalSpaceMixin : public Super
    {
        // transformation as three orthonormal unit basis vectors and the
        // origin of the local space.  These correspond to the "rows" of
        // a 3x4 transformation matrix with [0 0 0 1] as the final column

    private:

        bwVector3 _side;     //    side-pointing unit basis vector
        bwVector3 _up;       //  upward-pointing unit basis vector
        bwVector3 _forward;  // forward-pointing unit basis vector
        bwVector3 _position; // origin of local space

    public:

        // accessors (get and set) for side, up, forward and position
        bwVector3 side     (void) const {return _side;};
        bwVector3 up       (void) const {return _up;};
        bwVector3 forward  (void) const {return _forward;};
        bwVector3 position (void) const {return _position;};
        bwVector3 setSide     (const bwVector3& s) {return _side = s;};
        bwVector3 setUp       (const bwVector3& u) {return _up = u;};
        bwVector3 setForward  (const bwVector3& f) {return _forward = f;};
        bwVector3 setPosition (const bwVector3& p) {return _position = p;};
		bwVector3 setSide     (bwReal x, bwReal y, bwReal z){_side.set(x,y,z); return _side;};
		bwVector3 setUp       (bwReal x, bwReal y, bwReal z){_up.set(x,y,z); return _up;};
		bwVector3 setForward  (bwReal x, bwReal y, bwReal z){_forward.set (x,y,z); return _forward ;};
		bwVector3 setPosition (bwReal x, bwReal y, bwReal z){_position.set(x,y,z); return _position ;};


        // ------------------------------------------------------------------------
        // Global compile-time switch to control handedness/chirality: should
        // LocalSpace use a left- or right-handed coordinate system?  This can be
        // overloaded in derived types (e.g. vehicles) to change handedness.

        bool rightHanded (void) const {return true;}


        // ------------------------------------------------------------------------
        // constructors


        LocalSpaceMixin (void)
        {
            resetLocalSpace ();
        };

        LocalSpaceMixin (const bwVector3& Side,
                         const bwVector3& Up,
                         const bwVector3& Forward,
                         const bwVector3& Position)
        {
            _side = Side;
            _up = Up;
            _forward = Forward;
            _position = Position;
        };


        LocalSpaceMixin (const bwVector3& Up,
                         const bwVector3& Forward,
                         const bwVector3& Position)
        {
            _up = Up;
            _forward = Forward;
            _position = Position;
            setUnitSideFromForwardAndUp ();
        };


        // ------------------------------------------------------------------------
        // reset transform: set local space to its identity state, equivalent to a
        // 4x4 homogeneous transform like this:
        //
        //     [ X 0 0 0 ]
        //     [ 0 1 0 0 ]
        //     [ 0 0 1 0 ]
        //     [ 0 0 0 1 ]
        //
        // where X is 1 for a left-handed system and -1 for a right-handed system.

        void resetLocalSpace (void)
        {
            _forward.set (0, 0, 1);
            _side = localRotateForwardToSide (_forward);
            _up.set (0, 1, 0);
            _position.set (0, 0, 0);
        };


        // ------------------------------------------------------------------------
        // transform a direction in global space to its equivalent in local space


        bwVector3 localizeDirection (const bwVector3& globalDirection) const
        {
            // dot offset with local basis vectors to obtain local coordiantes
			return bwVector3 (dot (globalDirection, _side), dot (globalDirection, _up), dot (globalDirection, _forward));
        };


        // ------------------------------------------------------------------------
        // transform a point in global space to its equivalent in local space


        bwVector3 localizePosition (const bwVector3& globalPosition) const
        {
            // global offset from local origin
            bwVector3 globalOffset = globalPosition - _position;

            // dot offset with local basis vectors to obtain local coordiantes
            return localizeDirection (globalOffset);
        };


        // ------------------------------------------------------------------------
        // transform a point in local space to its equivalent in global space


        bwVector3 globalizePosition (const bwVector3& localPosition) const
        {
            return _position + globalizeDirection (localPosition);
        };


        // ------------------------------------------------------------------------
        // transform a direction in local space to its equivalent in global space


        bwVector3 globalizeDirection (const bwVector3& localDirection) const
        {
			return ((_side    * localDirection[0]) + (_up      * localDirection[1]) + (_forward * localDirection[2]));
        };


        // ------------------------------------------------------------------------
        // set "side" basis vector to normalized cross product of forward and up


        void setUnitSideFromForwardAndUp (void)
        {
            // derive new unit side basis vector from forward and up
            if (rightHanded())
				cross (_side, _forward, _up);
            else
				cross (_side, _up, _forward);
			normalize (_side) ;
        }


        // ------------------------------------------------------------------------
        // regenerate the orthonormal basis vectors given a new forward
        // (which is expected to have unit length)


        void regenerateOrthonormalBasisUF (const bwVector3& newUnitForward)
        {
            _forward = newUnitForward;

            // derive new side basis vector from NEW forward and OLD up
            setUnitSideFromForwardAndUp ();

            // derive new Up basis vector from new Side and new Forward
            // (should have unit length since Side and Forward are
            // perpendicular and unit length)
            if (rightHanded())
				cross (_up, _side, _forward);
            else
				cross (_up, _forward, _side);
        }


        // for when the new forward is NOT know to have unit length

        void regenerateOrthonormalBasis (const bwVector3& newForward)
        {
			bwVector3 temp = newForward ;
			normalize(temp) ;
			regenerateOrthonormalBasisUF (temp);
        }


        // for supplying both a new forward and and new up

        void regenerateOrthonormalBasis (const bwVector3& newForward,
                                         const bwVector3& newUp)
        {
            _up = newUp;
			bwVector3 temp = newForward ;
			normalize(temp) ;
			regenerateOrthonormalBasis (temp);
        }


        // ------------------------------------------------------------------------
        // rotate, in the canonical direction, a vector pointing in the
        // "forward" (+Z) direction to the "side" (+/-X) direction


        bwVector3 localRotateForwardToSide (const bwVector3& v) const
        {
			return bwVector3 (rightHanded () ? -v[2] : +v[2], v[1], v[0]);
        }

        // not currently used, just added for completeness

        bwVector3 globalRotateForwardToSide (const bwVector3& globalForward) const
        {
            const bwVector3 localForward = localizeDirection (globalForward);
            const bwVector3 localSide = localRotateForwardToSide (localForward);
            return globalizeDirection (localSide);
        }
    };


    // ----------------------------------------------------------------------------
    // Concrete LocalSpace class, and a global constant for the identity transform


    typedef LocalSpaceMixin<AbstractLocalSpace> LocalSpace;

    const LocalSpace gGlobalSpace;

} // namespace OpenSteer

// ----------------------------------------------------------------------------
#endif // OPENSTEER_LOCALSPACE_H
